#include "TimeslotManager.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_delay.h"
#include "nrf_nvic.h"
#include "app_scheduler.h"
#include "app_timer.h"
#include "boards.h"

#ifdef __cplusplus
}
#endif

APP_TIMER_DEF(waitingTimer);

TS::TimeslotInfo::TimeslotInfo(uint32_t timeslotDuration, uint32_t invocationTime) : timeslotDuration(timeslotDuration - TimeslotManager::C_SpanBeforeEnd), invocationTime(invocationTime)
{}

uint32_t TS::TimeslotInfo::GetRemaingTime()
{
  uint32_t ticks = TimeslotManager::Timer0Capture1();
  uint32_t remainingTime = this->timeslotDuration - ticks;
  if(remainingTime > this->timeslotDuration)
  {
    //underflow
    return 0;
  }
  else
  {
    return remainingTime;
  }
}

bool TS::TimeslotInfo::IsEnoughTime(uint32_t duration, TS::DoWorkResult & res)
{
  if(this->IsEnoughTime(duration))
  {
    return true;
  }
  else
  {
    res.type = TS::DoWorkResultType::NotEnoughTime;
    return false;
  }
}

bool TS::TimeslotInfo::IsEnoughTime(uint32_t duration)
{
  return this->GetRemaingTime() > duration;
}

TS::DoWorkResult TS::TimeslotInfo::Completed()
{
  TS::DoWorkResult retVal;
  retVal.type = TS::DoWorkResultType::Completed;
  return retVal;
}

TS::DoWorkResult TS::TimeslotInfo::WaitFromNow(uint32_t waitingDuration)
{
  TS::DoWorkResult retVal;
  retVal.type = TS::DoWorkResultType::ShortWaiting;
  retVal.waiting = waitingDuration + TimeslotManager::Timer0Capture1();
  return retVal;
}

TS::DoWorkResult TS::TimeslotInfo::WaitFromTaskInvocation(uint32_t waitingDuration)
{
  TS::DoWorkResult retVal;
  retVal.type = TS::DoWorkResultType::ShortWaiting;
  retVal.waiting = waitingDuration + this->invocationTime;
  return retVal;
}

TS::DoWorkResult TS::TimeslotInfo::WaitForLongTime(uint32_t waitingDuration, uint32_t timeslotDuration)
{
  TS::DoWorkResult retVal;
  retVal.type = TS::DoWorkResultType::LongWaiting;
  retVal.waiting = waitingDuration;
  return retVal;
}

uint32_t TS::TimeslotInfo::GetTicks()
{
  return TimeslotManager::Timer0Capture1();
}

void TS::TimeslotInfo::SpinDelayTill(uint32_t ticks)
{
  while(TimeslotManager::Timer0Capture1() < ticks);
}

void TS::TimeslotInfo::SpinDelay(uint32_t duration)
{
  uint32_t end = duration + TimeslotManager::Timer0Capture1();
  while(TimeslotManager::Timer0Capture1() < end);
}

void TS::TestTimeslotTask::Init()
{
  state = 0;
  TS::TimeslotManager::Instance().RequestTimeslot(this);
}

uint32_t TS::TestTimeslotTask::GetRequestedDuration()
{
  return 10000;
}

TS::DoWorkResult TS::TestTimeslotTask::DoWork(TimeslotInfo & timeslotInfo)
{

  if(state == 0)
  {
    bsp_board_led_invert(1);
    state++;
    return timeslotInfo.WaitForLongTime(1000000, 1000);
  }
  else if(state == 1)
  {
    bsp_board_led_invert(1);
    state++;
    return timeslotInfo.WaitFromTaskInvocation(80);
  }
  else if(state == 2)
  {
    bsp_board_led_invert(1);
    state++;
    return timeslotInfo.WaitFromTaskInvocation(15);
  }
  else if(state == 3)
  {
    bsp_board_led_invert(1);
    state = 4;
    return timeslotInfo.WaitFromTaskInvocation(15);
  }
  else if(state == 4)
  {
    bsp_board_led_invert(1);
    bsp_board_led_invert(1);
    state = 0;
    return timeslotInfo.WaitFromNow(15);
  }
  else
  {
    state = 0;
    return timeslotInfo.WaitFromTaskInvocation(1);
  }
}

TS::TimeslotManager::TimeslotManager() : tasks({}), currentTask(nullptr), timeslotLength(0), state(TimeslotManagerState::Ready), requestedDuration(0), shortWaitingEndTime(0)
{}

void TS::TimeslotManager::Init()
{
  for(int i=0; (i < TimeslotManager::C_MaxTasksCount && this->tasks[i].task); i++)
  {
    this->tasks[i].task->Init();
  }

  app_timer_create(&waitingTimer, APP_TIMER_MODE_SINGLE_SHOT, TimerElapsedHandlerStatic);
  sd_radio_session_open(RadioSessionSignalCallbackStatic);
}

void TS::TimerElapsedHandlerStatic(void * p_context)
{
  return TimeslotManager::Instance().TimerElapsedHandler(p_context);
}

void TS::TimeslotManager::TimerElapsedHandler(void * p_context)
{
  ASSERT(this->state == TimeslotManagerState::LongWaiting);
  this->state = TimeslotManagerState::Ready;
}

nrf_radio_signal_callback_return_param_t * TS::RadioSessionSignalCallbackStatic(uint8_t signal_type)
{
  return TimeslotManager::Instance().RadioSessionSignalCallback(signal_type);
}

nrf_radio_signal_callback_return_param_t * TS::TimeslotManager::RadioSessionSignalCallback(uint8_t signal_type)
{
  static nrf_radio_signal_callback_return_param_t retVal;
  retVal.callback_action = NRF_RADIO_SIGNAL_CALLBACK_ACTION_NONE;

  if(signal_type == NRF_RADIO_CALLBACK_SIGNAL_TYPE_START || signal_type == NRF_RADIO_CALLBACK_SIGNAL_TYPE_TIMER0 || signal_type == NRF_RADIO_CALLBACK_SIGNAL_TYPE_EXTEND_SUCCEEDED)
  {
    ASSERT(this->currentTask != nullptr);
    if(signal_type == NRF_RADIO_CALLBACK_SIGNAL_TYPE_START)
    {
      // Timeslot started
      ASSERT(this->state == TimeslotManagerState::TimeslotRequested);
      this->timeslotLength = this->requestedDuration;
      this->requestedDuration = 0;
    }
    if(signal_type == NRF_RADIO_CALLBACK_SIGNAL_TYPE_TIMER0)
    {
      // Short waiting elapsed
      ASSERT(this->state == TimeslotManagerState::ShortWaiting);
      NRF_TIMER0->EVENTS_COMPARE[0] = 0;
    }
    if (signal_type == NRF_RADIO_CALLBACK_SIGNAL_TYPE_EXTEND_SUCCEEDED)
    {
      // Timeslot extension succeeded
      ASSERT(this->state == TimeslotManagerState::ExtendRequested)
      this->timeslotLength += this->requestedDuration;
      this->requestedDuration = 0;
    }
      

    retVal.callback_action = this->RunTask();
    if(retVal.callback_action == NRF_RADIO_SIGNAL_CALLBACK_ACTION_EXTEND)
      retVal.params.extend.length_us = this->requestedDuration;
  }
  else if (signal_type == NRF_RADIO_CALLBACK_SIGNAL_TYPE_RADIO)
  {/*nothing to do*/}
  else if (signal_type == NRF_RADIO_CALLBACK_SIGNAL_TYPE_EXTEND_FAILED)
  {
    ASSERT(this->state == TimeslotManagerState::ExtendRequested);
      
                                

    static nrf_radio_request_t request;
    this->GetTimeslotRequest(request);
    retVal.params.request.p_next = &request;
    retVal.callback_action = NRF_RADIO_SIGNAL_CALLBACK_ACTION_REQUEST_AND_END;
    this->state = TimeslotManagerState::TimeslotRequested;
  }
  else
  {
    NRF_LOG_ERROR("Unexpected signal type: %d\r\n", static_cast<int>(signal_type));
    ASSERT(false);
  }

  uint32_t ticks = TS::TimeslotManager::Timer0Capture1();
  ASSERT(this->timeslotLength > ticks);

  return &retVal;
}

void DoWorkStatic(void * p_event_data, uint16_t event_size)
{
  TS::TimeslotManager::Instance().DoWork();
}

uint8_t TS::TimeslotManager::RunTask()
{
  bool repeat = true;
  ASSERT(this->currentTask);

  while(TS::TimeslotManager::Timer0Capture1() < this->shortWaitingEndTime);
  this->shortWaitingEndTime = 0;
  while(repeat)
  {
    repeat = false;
    uint32_t ticks = TS::TimeslotManager::Timer0Capture1();
    TimeslotInfo timeslotInfo(this->timeslotLength, ticks);
    DoWorkResult result = this->currentTask->task->DoWork(timeslotInfo);

    if (result.type == DoWorkResultType::Completed)
    {
      this->currentTask->requestedDuration = 0;
      this->currentTask = nullptr;
      this->state = TimeslotManagerState::Ready;
      TS::TimeslotManager::DisableTimerInterrupt();
      return NRF_RADIO_SIGNAL_CALLBACK_ACTION_END;
    }
    else if (result.type == DoWorkResultType::ShortWaiting)
    {
      this->currentTask->requestedDuration = 0;

      uint32_t end = result.waiting;;
      ticks = TS::TimeslotManager::Timer0Capture1();
      uint32_t remaining = end - ticks;
      if (remaining > end)
      {
        // overflow... to late, execute as soon as posible
        repeat = true;
      }
      else if(remaining <= C_ActiveWaitingLimit)
      {
        repeat = true;
        while(TS::TimeslotManager::Timer0Capture1() < end);
      }
      else
      {
        TS::TimeslotManager::SetTimerInterrupt(ticks + remaining - C_ActiveWaitingLimit + 4);
        this->state = TimeslotManagerState::ShortWaiting;
        this->shortWaitingEndTime = end;
        return NRF_RADIO_SIGNAL_CALLBACK_ACTION_NONE;
      }
    }
    else if (result.type == DoWorkResultType::LongWaiting)
    {
      this->currentTask->requestedDuration = this->currentTask->task->GetRequestedDuration();
      this->state = TimeslotManagerState::LongWaiting;
      app_timer_start(waitingTimer, APP_TIMER_TICKS((result.waiting + 999) / 1000, TIMER_LIB_PRESCALER), nullptr);
      TS::TimeslotManager::DisableTimerInterrupt();
      return NRF_RADIO_SIGNAL_CALLBACK_ACTION_END;
    }
    else if (result.type == DoWorkResultType::NotEnoughTime)
    {
      this->state = TimeslotManagerState::ExtendRequested;
      this->currentTask->requestedDuration = this->currentTask->task->GetRequestedDuration();
      return NRF_RADIO_SIGNAL_CALLBACK_ACTION_EXTEND;
    }
    else
    {
      NRF_LOG_ERROR("Unknown value of result.type=%d\r\n", static_cast<uint32_t>(result.type));
      ASSERT(false);
      return 0;
    }
  }
  NRF_LOG_ERROR("Control reached end\r\n");
  return NRF_RADIO_SIGNAL_CALLBACK_ACTION_NONE;
}

void TS::TimeslotManager::GetTimeslotRequest(nrf_radio_request_t & request)
{
  ASSERT(this->currentTask);
  request.request_type = NRF_RADIO_REQ_TYPE_EARLIEST;
  request.params.earliest.hfclk = NRF_RADIO_HFCLK_CFG_XTAL_GUARANTEED;
  request.params.earliest.priority = NRF_RADIO_PRIORITY_NORMAL;
  request.params.earliest.timeout_us = NRF_RADIO_EARLIEST_TIMEOUT_MAX_US;
  request.params.earliest.length_us = this->currentTask->requestedDuration + C_SpanBeforeEnd;
  this->state = TimeslotManagerState::TimeslotRequested;
  this->requestedDuration = request.params.earliest.length_us;
}

void TS::TimeslotManager::DoWork()
{
  if(this->state == TimeslotManagerState::Ready)
  {
    if(!this->currentTask)
    {
      this->SelectNextTask();
    }
    if(this->currentTask)
    {
      nrf_radio_request_t request;
      GetTimeslotRequest(request);
      uint32_t err_code = sd_radio_request(&request);
      APP_ERROR_CHECK(err_code);
    }
  }
  else
  {
    if(this->state == TimeslotManagerState::LongWaiting)
    {
            
    }

  }
}

bool TS::TimeslotManager::SelectNextTask()
{
  for(int16_t i = 0; i < C_MaxTasksCount; i++)
  {
    if (this->tasks[i].task != nullptr && this->tasks[i].requestedDuration)
    {
      this->currentTask = this->tasks + i;
      return true;
    }
  }
  this->currentTask = nullptr;
  return false;
}

void TS::TimeslotManager::AddTask(ITimeslotTask * task)
{
  for(int16_t i = 0; i < C_MaxTasksCount; i++)
  {
    if (this->tasks[i].task == nullptr)
    {
      tasks[i].task = task;
      tasks[i].requestedDuration = 0;
      return;
    }
  }
  NRF_LOG_ERROR("Too many tasks.\r\n");
}

void TS::TimeslotManager::RequestTimeslot(ITimeslotTask * task)
{
  for(int i=0; (i < TimeslotManager::C_MaxTasksCount && this->tasks[i].task); i++)
  {
    if(this->tasks[i].task == task)
    {
      this->tasks[i].requestedDuration = this->tasks[i].task->GetRequestedDuration();;
      return;
    }
  }
  NRF_LOG_WARNING("Unknown task\r\n");
}

void TS::TimeslotManager::ProcessSystemEvent(int32_t event)
{
  if(event == NRF_EVT_RADIO_SESSION_IDLE)
  {
  }
  else if(event == NRF_EVT_RADIO_SESSION_CLOSED)
  {
  }
  else if(event == NRF_EVT_RADIO_BLOCKED or event == NRF_EVT_RADIO_CANCELED)
  {
    ASSERT(this->state == TimeslotManagerState::TimeslotRequested);
    this->state = TimeslotManagerState::Ready;
  }
}

bool TS::TimeslotManager::OnTimerTaskElapsed(app_timer_timeout_handler_t timeout_handler, void * p_context)
{
  if(timeout_handler == TimerElapsedHandlerStatic)
  {
    this->TimerElapsedHandler(p_context);
    //handled, do not append to queueu;
    return true;
  }
  else
  {
    return false;
  }
}

uint32_t TS::TimeslotManager::Timer0Capture1()
{
  NRF_TIMER0->TASKS_CAPTURE[1] = 1;
  return NRF_TIMER0->CC[1];
}
void TS::TimeslotManager::SetTimerInterrupt(uint32_t ticks)
{
  NRF_TIMER0->CC[0] = ticks;
  NRF_TIMER0->INTENSET = TIMER_INTENSET_COMPARE0_Msk;
  NVIC_EnableIRQ(TIMER0_IRQn);

}

void TS::TimeslotManager::DisableTimerInterrupt()
{
  NRF_TIMER0->INTENCLR = TIMER_INTENSET_COMPARE0_Msk;
  NVIC_DisableIRQ(TIMER0_IRQn);
}

TS::TimeslotManager & TS::TimeslotManager::Instance()
{
  static TimeslotManager instance;
  return instance;
}
