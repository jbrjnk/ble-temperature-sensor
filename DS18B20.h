#ifndef DS18B20_H_0bce026928cb
#define DS18B20_H_0bce026928cb

#include "TimeslotManager.h"
#include "OneWire.h"
#include "SupplyBranch.h"

namespace DS18B20
{
    enum class DriverState
    {
        Init,
        SearchRom,
        WriteScratchpad,
        WriteToEeprom,
        EepromOverlap, // time overlap
        Idle,
        BeforeConversion,
        StartConversion,
        Conversion,
        ReadResult
    };

    class Command
    {
    public:
        static const uint8_t Convert = 0x44;
        static const uint8_t WriteScratchpad = 0x4E;
        static const uint8_t ReadScratchpad = 0xBE;
        static const uint8_t CopyScratchpad = 0x48;
        static const uint8_t ReacalllEeprom = 0xB8;
        static const uint8_t ReadPowerSupply = 0xB4;
    };

    struct TemperatureInfo
    {
        uint64_t address;
        int32_t temperature;
        bool dataValid;
    };

    enum class SensorResolution
    {
        Bits9  = 0,  // [+-] 0.5    °C
        Bits10 = 1,  // [+-] 0.25   °C
        Bits11 = 2,  // [+-] 0.125  °C
        Bits12 = 3   // [+-] 0.0625 °C 
    };

    class Driver : public TS::ITimeslotTask
    {
        public:            
            static const bool C_DoSensorInitialization = true;
            static const SensorResolution C_SensorResolution = SensorResolution::Bits11;
            static const uint32_t C_EepromOverlapUs = 10000;
            static const uint32_t C_DelayAfterPowerOn = 10000;
            static const uint32_t C_TimeslotLengthUs = 2000;

            Driver(TS::TimeslotManager & timeslotManager, W1::OneWireBus & bus, SupplyBranchHandle supplyBranch);
            bool IsReady();
            const TemperatureInfo * GetResult();
            uint8_t GetSensorsCount();
            void StartConversion();
            bool IsConversionCompleted();

            virtual TS::DoWorkResult DoWork(TS::TimeslotInfo &timeslotInfo) override;
            virtual void Init() override;
            virtual uint32_t GetRequestedDuration() override;
            TS::DoWorkResult DoWorkInternal(TS::TimeslotInfo &timeslotInfo);

        private:
            uint32_t GetConversionTimeUs();
            void ReadResult(uint8_t sensorIndex);
            bool SetSupplyBranchState();

            TS::TimeslotManager & timeslotManager;
            W1::OneWireBus & oneWireBus;
            TemperatureInfo sensors[W1::SearchRomHelper::C_maxDeviceCount];
            uint8_t sensorsCount;
            uint8_t currentSensorIndex;
            bool isConversionCompleted;
            DriverState state;
            W1::SearchRomHelper searchRomHelper;
            SupplyBranchHandle supplyBranch;
    };
}

#endif //DS18B20_H_0bce026928cb

