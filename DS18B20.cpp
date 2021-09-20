#include "DS18B20.h"

extern "C"
{
#include "nrf_gpio.h"
#include "nrf_log.h"
}

DS18B20::Driver::Driver(TS::TimeslotManager &timeslotManager, W1::OneWireBus &bus, SupplyBranchHandle supplyBranch)
    : timeslotManager(timeslotManager), oneWireBus(bus), sensorsCount(0), isConversionCompleted(false),
      state(DS18B20::DriverState::Init), searchRomHelper(bus), supplyBranch(supplyBranch)
{
    timeslotManager.AddTask(this);
}

bool DS18B20::Driver::IsReady()
{
    return this->state == DS18B20::DriverState::Idle;
}

const DS18B20::TemperatureInfo *DS18B20::Driver::GetResult()
{
    return this->sensors;
}

uint8_t DS18B20::Driver::GetSensorsCount()
{
    return this->sensorsCount;
}

void DS18B20::Driver::StartConversion()
{
    ASSERT(this->IsReady());
    this->state = DS18B20::DriverState::BeforeConversion;
    this->isConversionCompleted = false;
    this->timeslotManager.RequestTimeslot(this);
}

bool DS18B20::Driver::IsConversionCompleted()
{
    return this->isConversionCompleted;
}

uint32_t DS18B20::Driver::GetConversionTimeUs()
{
    switch (C_SensorResolution)
    {
    case DS18B20::SensorResolution::Bits9:
        return 94 * 1000;
    case DS18B20::SensorResolution::Bits10:
        return 188 * 1000;
    case DS18B20::SensorResolution::Bits11:
        return 375 * 1000;
    case DS18B20::SensorResolution::Bits12:
    default:
        return 750 * 1000;
    }
}

bool DS18B20::Driver::SetSupplyBranchState()
{
    if (this->IsReady())
    {
        supplyBranch.Release();
        return false;
    }
    else
    {
        return supplyBranch.Request();
    }
}

void DS18B20::Driver::ReadResult(uint8_t sensorIndex)
{
    W1::BitBlock writeData;
    W1::BitBlock writeMask;
    writeData.Data[0] = W1::RomCommand::MatchRom;                // [0]
    writeData.FromUInt64(this->sensors[sensorIndex].address, 1); // [1:8]
    writeData.Data[9] = DS18B20::Command::ReadScratchpad;        // [9]

    for (uint8_t i = 0; i < 10; i++)
    {
        writeMask.Data[i] = 0xFF;
    }

    // write 80 bits (2 bytes command, 8 bytes address)
    // read 16 bits (temperature)
    this->oneWireBus.ReadWrite(true, writeData, writeMask, 96);
}

TS::DoWorkResult DS18B20::Driver::DoWork(TS::TimeslotInfo &timeslotInfo)
{
    this->SetSupplyBranchState();

    TS::DoWorkResult doWorkRes = this->DoWorkInternal(timeslotInfo);

    this->SetSupplyBranchState();

    return doWorkRes;
}

TS::DoWorkResult DS18B20::Driver::DoWorkInternal(TS::TimeslotInfo &timeslotInfo)
{
    while (true)
    {
        TS::DoWorkResult doWorkRes;
        if (this->state == DS18B20::DriverState::SearchRom)
        {
            doWorkRes = this->searchRomHelper.DoWork(timeslotInfo);
            if (doWorkRes.type == TS::DoWorkResultType::Completed)
            {
                // search ROM comlpeted, store addresses
                this->sensorsCount = this->searchRomHelper.GetDeviceCount();
                for (uint8_t i = 0; i < this->sensorsCount; i++)
                {
                    this->sensors[i].address = this->searchRomHelper.GetDeviceAddress(i);
                    this->sensors[i].dataValid = false;
                }

                // write configuration if enabled
                if (this->sensorsCount && C_DoSensorInitialization)
                {
                    uint8_t configReg = (static_cast<uint8_t>(C_SensorResolution) << 5) | 0x1F;
                    this->state = DS18B20::DriverState::WriteScratchpad;
                    W1::BitBlock writeData;
                    W1::BitBlock writeMask;
                    writeData.Data[0] = W1::RomCommand::SkipRom; //write all DS18B20 sensors
                    writeMask.Data[0] = 0xFF;
                    writeData.Data[1] = DS18B20::Command::WriteScratchpad;
                    writeMask.Data[1] = 0xFF;
                    writeData.Data[2] = 0x00;
                    writeMask.Data[2] = 0xFF;
                    writeData.Data[3] = 0x00;
                    writeMask.Data[3] = 0xFF;
                    writeData.Data[4] = configReg;
                    writeMask.Data[4] = 0xFF;
                    this->oneWireBus.ReadWrite(true, writeData, writeMask, 40);
                }
                else
                {
                    this->state = DS18B20::DriverState::Idle;
                }
            }
            else
            {
                return doWorkRes;
            }
        }
        else
        {
            TS::DoWorkResult doWorkRes = this->oneWireBus.DoWork(timeslotInfo);
            if (doWorkRes.type == TS::DoWorkResultType::Completed)
            {
                if (this->state == DS18B20::DriverState::Init)
                {
                    this->searchRomHelper.Run();
                    this->state = DS18B20::DriverState::SearchRom;
                }
                else if (this->state == DS18B20::DriverState::SearchRom)
                {
                    // this state is handled in the branch above
                    ASSERT(false);
                }
                else if (this->state == DS18B20::DriverState::WriteScratchpad)
                {
                    this->state = DS18B20::DriverState::WriteToEeprom;
                    W1::BitBlock writeData;
                    W1::BitBlock writeMask;
                    writeData.Data[0] = W1::RomCommand::SkipRom;
                    writeMask.Data[0] = 0xFF;
                    writeData.Data[1] = DS18B20::Command::CopyScratchpad;
                    writeMask.Data[1] = 0xFF;
                    this->oneWireBus.ReadWrite(true, writeData, writeMask, 16);
                }
                else if (this->state == DS18B20::DriverState::WriteToEeprom)
                {
                    this->state = DS18B20::DriverState::EepromOverlap;
                    return timeslotInfo.WaitForLongTime(C_EepromOverlapUs, C_TimeslotLengthUs);
                }
                else if (this->state == DS18B20::DriverState::EepromOverlap)
                {
                    this->state = DS18B20::DriverState::Idle;
                }
                else if (this->state == DS18B20::DriverState::Idle)
                {
                    return timeslotInfo.Completed();
                }
                else if (this->state == DS18B20::DriverState::BeforeConversion)
                {
                    if (this->sensorsCount > 0)
                    {
                        this->state = DS18B20::DriverState::StartConversion;
                        W1::BitBlock writeData;
                        W1::BitBlock writeMask;
                        writeData.Data[0] = W1::RomCommand::SkipRom;
                        writeMask.Data[0] = 0xFF;
                        writeData.Data[1] = DS18B20::Command::Convert;
                        writeMask.Data[1] = 0xFF;
                        this->oneWireBus.ReadWrite(true, writeData, writeMask, 16);
                    }
                    else
                    {
                        //no sensors, nothing to do
                        this->state = DS18B20::DriverState::Idle;
                        this->isConversionCompleted = true;
                        return timeslotInfo.Completed();
                    }
                }
                else if (this->state == DS18B20::DriverState::StartConversion)
                {
                    this->state = DS18B20::DriverState::Conversion;
                    this->currentSensorIndex = 0;
                    return timeslotInfo.WaitForLongTime(this->GetConversionTimeUs(), C_TimeslotLengthUs); // wait until sensor completes conversion
                }
                else if (this->state == DS18B20::DriverState::Conversion)
                {
                    this->state = DS18B20::DriverState::ReadResult;
                    this->ReadResult(this->currentSensorIndex);
                }
                else if (this->state == DS18B20::DriverState::ReadResult)
                {
                    W1::BitBlock receivedData = this->oneWireBus.GetReceivedData();
                    uint8_t hByte = receivedData.Data[this->oneWireBus.GetReadWriteLength() / 8 - 1];
                    uint8_t lByte = receivedData.Data[this->oneWireBus.GetReadWriteLength() / 8 - 2];
                    this->sensors[this->currentSensorIndex].dataValid = true;
                    int16_t temperature16Bits = ((hByte << 8) | lByte);
                    int32_t temperature = temperature16Bits * 10000 / 16;
                    this->sensors[this->currentSensorIndex].temperature = temperature;

                    this->currentSensorIndex++;
                    if (this->currentSensorIndex < this->sensorsCount)
                    {
                        this->ReadResult(this->currentSensorIndex);
                    }
                    else
                    {
                        this->state = DS18B20::DriverState::Idle;
                        this->isConversionCompleted = true;
                        return timeslotInfo.Completed();
                    }
                }
                else
                {
                    // unknown state
                    ASSERT(false);
                }
            }
            else
            {
                return doWorkRes;
            }
        }
    }
}

void DS18B20::Driver::Init()
{
    this->timeslotManager.RequestTimeslot(this);
}

uint32_t DS18B20::Driver::GetRequestedDuration()
{
    return C_TimeslotLengthUs;
}
