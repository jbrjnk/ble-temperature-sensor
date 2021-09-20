#ifndef STATUSLEDDRIVER_H_925d8ecbe601
#define STATUSLEDDRIVER_H_925d8ecbe601

#include "SupplyBranch.h"


class StatusLedDriver
{
public:
    StatusLedDriver(SupplyBranchHandle supplyBranchHandle, uint8_t pinIndex);
    void Play(uint8_t count, uint8_t onDuration, uint8_t offDuration);
    bool IsPlaying();
    static const uint8_t C_MaxTogglePeriodsCount = 16;
private:
    void GoToNextState();
    static void TimerElapsedHandlerStatic(void * p_context);
    void TimerElapsedHandler();
    SupplyBranchHandle supplyBranchHandle;
    uint8_t pinIndex;
    uint8_t togglePeriods[C_MaxTogglePeriodsCount];
    uint8_t currentPosition;
};

#endif