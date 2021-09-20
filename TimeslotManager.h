#ifndef TIMESLOTMANAGER_H_1199bf0bac6e414
#define TIMESLOTMANAGER_H_1199bf0bac6e414

#include <cstdint>

extern "C"
{
#include "nrf.h"
#include "nrf_drv_timer.h"
#include "nrf_soc.h"
#include "app_timer.h"
}

#include "app_global.h"

// All time values are in MICROSECONDS
namespace TS //Timeslots
{
enum class DoWorkResultType
{
  Completed,    // Completed, do not schedule further timeslots
  ShortWaiting, // Waiting proceeded during the timeslot. Task will be invoked when TIMER0 = waiting
  LongWaiting,  // End timeslot and wait. Ask for another slot after waiting time elapsed
  NotEnoughTime // The remaining time is not sufficient to continue. Extend timeslot or ask for another one
};

struct DoWorkResult
{
  DoWorkResultType type;
  uint32_t waiting;  // Waiting duration (long waiting) or invocation time (short waiting)
};

class TimeslotInfo
{
private:
  uint32_t timeslotDuration; // total time of timeslot
  uint32_t invocationTime;

public:
  TimeslotInfo(uint32_t timeslotDuration, uint32_t taskInvocationTime);
  bool IsEnoughTime(uint32_t duration);
  bool IsEnoughTime(uint32_t duration, TS::DoWorkResult & res);
  uint32_t GetRemaingTime();
  uint32_t GetTicks();
  TS::DoWorkResult WaitFromNow(uint32_t waitingDuration);
  TS::DoWorkResult Completed();
  TS::DoWorkResult WaitFromTaskInvocation(uint32_t waitingDuration);
  TS::DoWorkResult WaitForLongTime(uint32_t waitingDuration, uint32_t timeslotDuration);
  void SpinDelay(uint32_t duration);
  void SpinDelayTill(uint32_t ticks); 
};

class ITimeslotTask
{
public:
  virtual void Init() = 0;
  virtual DoWorkResult DoWork(TimeslotInfo &timeslotInfo) = 0;
  virtual uint32_t GetRequestedDuration() = 0;
};

class TestTimeslotTask : public ITimeslotTask
{
private:
  uint16_t state;

public:
  virtual void Init() override;
  virtual DoWorkResult DoWork(TimeslotInfo &timeslotInfo) override;
  virtual uint32_t GetRequestedDuration() override;
};

struct TaskInfo
{
  ITimeslotTask *task = nullptr;
  uint32_t requestedDuration = 0;
};

enum class TimeslotManagerState
{
  Ready, // No timeslot
  TimeslotRequested, //No timeslot
  ExtendRequested, // no timeslot
  ShortWaiting, //timeslot granted and running
  LongWaiting //no timeslot
};

class TimeslotManager
{
private:
  static const uint32_t C_SpanBeforeEnd = 200; //microsecond
  static const int C_MaxTasksCount = 3;
  static const uint32_t C_ActiveWaitingLimit = 30; //microsecond

  TimeslotManager();
  TimeslotManager(TimeslotManager const &) = delete;
  TimeslotManager(TimeslotManager &&) = delete;
  TimeslotManager &operator=(TimeslotManager const &) = delete;
  TimeslotManager &operator=(TimeslotManager &&) = delete;

  TaskInfo tasks[C_MaxTasksCount];
  volatile TaskInfo *currentTask;
  volatile uint32_t timeslotLength;
  volatile TimeslotManagerState state;
  volatile uint32_t requestedDuration;
  volatile uint32_t shortWaitingEndTime;

  static uint32_t Timer0Capture1();
  static void SetTimerInterrupt(uint32_t ticks);
  static void DisableTimerInterrupt();

  friend nrf_radio_signal_callback_return_param_t *RadioSessionSignalCallbackStatic(uint8_t signal_type);
  nrf_radio_signal_callback_return_param_t *RadioSessionSignalCallback(uint8_t signal_type);
  friend void TimerElapsedHandlerStatic(void *p_context);
  void TimerElapsedHandler(void *p_context);
  friend void DoWorkStatic(void *p_event_data, uint16_t event_size);
  
  bool SelectNextTask();
  uint8_t RunTask();
  void GetTimeslotRequest(nrf_radio_request_t & request);


public:
  static TimeslotManager & Instance();

  void Init();
  void DoWork();
  void AddTask(ITimeslotTask *task);
  void RequestTimeslot(ITimeslotTask *task);
  void ProcessSystemEvent(int32_t event);
  bool OnTimerTaskElapsed(app_timer_timeout_handler_t timeout_handler, void * p_context);

  friend class TimeslotInfo;
};

nrf_radio_signal_callback_return_param_t *RadioSessionSignalCallbackStatic(uint8_t signal_type);
void DoWorkStatic(void *p_event_data, uint16_t event_size);
void TimerElapsedHandlerStatic(void *p_context);

}
#endif
