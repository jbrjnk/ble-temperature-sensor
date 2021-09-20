#include "SupplyBranch.h"
extern "C"
{
    #include "nrf_gpio.h"
    #include "nrf_assert.h"
}

bool SupplyBranchHandle::Request()
{
    if(this->supplyBranch)
        return this->supplyBranch->Request(this->id);
    else
        return false;
}

void SupplyBranchHandle::Release()
{
    if(this->supplyBranch)
        this->supplyBranch->Release(this->id);
}

SupplyBranchHandle::SupplyBranchHandle(SupplyBranch * branch, uint8_t id) : supplyBranch(branch), id(id)
{}

SupplyBranchHandle::SupplyBranchHandle() : supplyBranch(nullptr), id(0)
{}

SupplyBranch::SupplyBranch(uint8_t enablePin) : enablePin(enablePin), activeHandles(0), handlesCount(0)
{
    nrf_gpio_cfg_output(this->enablePin);
}

SupplyBranchHandle SupplyBranch::GetHandle()
{
    ASSERT(this->handlesCount < 16);
    SupplyBranchHandle handle(this, this->handlesCount++);
    return handle;
}

bool SupplyBranch::Request(uint8_t handle)
{
    bool wasActive =  !!(this->activeHandles);
    this->activeHandles |= (1 << handle);
    bool isActive =  !!(this->activeHandles);
    this->UpdateBranchState();
    return !wasActive && isActive;
}

void SupplyBranch::Release(uint8_t handle)
{
    this->activeHandles &= ~(1 << handle);
    this->UpdateBranchState();
}

void SupplyBranch::UpdateBranchState()
{
    if(this->activeHandles)
        nrf_gpio_pin_set(this->enablePin);
    else
        nrf_gpio_pin_clear(this->enablePin);
}
