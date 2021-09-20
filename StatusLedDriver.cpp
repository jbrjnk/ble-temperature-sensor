#ifdef __cplusplus
extern "C" {
#endif
  #include "app_timer.h"
  #include "nrf_gpio.h"
  #include "nrf_log.h"
#ifdef __cplusplus
}
#endif

#include "StatusLedDriver.h"
#include "app_global.h"

APP_TIMER_DEF(delayTimer);

StatusLedDriver::StatusLedDriver(SupplyBranchHandle supplyBranchHandle, uint8_t pinIndex)
    : supplyBranchHandle(supplyBranchHandle), pinIndex(pinIndex), currentPosition(0)
{
    this->togglePeriods[0] = 0;
    nrf_gpio_cfg_output(this->pinIndex);
    nrf_gpio_pin_clear(this->pinIndex);
    app_timer_create(&delayTimer, APP_TIMER_MODE_SINGLE_SHOT, TimerElapsedHandlerStatic);
    this->Play(1, 30, 10);
}

void StatusLedDriver::TimerElapsedHandlerStatic(void * p_context)
{
    StatusLedDriver * instance = static_cast<StatusLedDriver *>(p_context);
    instance->TimerElapsedHandler();
}

void StatusLedDriver::TimerElapsedHandler()
{
    this->currentPosition++;
    this->GoToNextState();
}

void StatusLedDriver::GoToNextState()
{
    if(IsPlaying())
    {
        if((this->currentPosition % 2) == 1)
        {
            this->supplyBranchHandle.Release();
            nrf_gpio_pin_clear(this->pinIndex);
        }
        else
        {
            this->supplyBranchHandle.Request();
            nrf_gpio_pin_set(this->pinIndex);
        }
        uint32_t durationMs = this->togglePeriods[this->currentPosition] * 100;
        app_timer_start(delayTimer, APP_TIMER_TICKS(durationMs, TIMER_LIB_PRESCALER), this);
    }
    else
    {
        this->currentPosition = C_MaxTogglePeriodsCount;
        nrf_gpio_pin_clear(this->pinIndex);
    }
}

bool StatusLedDriver::IsPlaying()
{
    return this->currentPosition < C_MaxTogglePeriodsCount && this->togglePeriods[this->currentPosition];
}

void StatusLedDriver::Play(uint8_t count, uint8_t onDuration, uint8_t offDuration)
{
    ASSERT(this->IsPlaying() == false);
    ASSERT(count <= C_MaxTogglePeriodsCount / 2);
    NRF_LOG_DEBUG("Status LED Play (count: %d, onDuration: %d, offDuration: %d) \r\n", count, onDuration, offDuration);
    for(uint8_t i = 0; i < count * 2; i+=2)
    {
        this->togglePeriods[i] = onDuration;
        this->togglePeriods[i + 1] = offDuration;
    }

    // insert terminating zero 
    if(count < C_MaxTogglePeriodsCount / 2)
    {
        this->togglePeriods[count * 2] = 0;
    }
    this->currentPosition = 0;
    this->GoToNextState();
}