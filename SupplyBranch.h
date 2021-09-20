#ifndef SUPPLYBRANCH_H_70d17a397ca7
#define SUPPLYBRANCH_H_70d17a397ca7

#include <cstdint>

class SupplyBranch;

class SupplyBranchHandle
{
    public:
        SupplyBranchHandle(SupplyBranch * branch, uint8_t id);
        SupplyBranchHandle();
        bool Request();
        void Release();
    private:
        SupplyBranch * supplyBranch;
        uint8_t id;
};

//The purpose of this class is to switch of high power parts of circuit to save the battery
class SupplyBranch
{
    public:
        SupplyBranch(uint8_t enablePin);
        SupplyBranchHandle GetHandle();

        friend class SupplyBranchHandle;

    private:
        bool Request(uint8_t handle);
        void Release(uint8_t handle);
        void UpdateBranchState();
        uint8_t enablePin;
        uint16_t activeHandles;
        uint8_t handlesCount;

        SupplyBranch(SupplyBranch const &) = delete;
        SupplyBranch(SupplyBranch &&) = delete;
        SupplyBranch &operator=(SupplyBranch const &) = delete;
        SupplyBranch &operator=(SupplyBranch &&) = delete;
};

#endif
