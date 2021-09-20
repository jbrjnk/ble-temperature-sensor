#include "OneWire.h"
#include "TimeslotManager.h"

extern "C"
{
    #include "nrf_gpio.h"
    #include "nrf_assert.h"
    #include "nrf_log.h"
    #include "nrf_log_ctrl.h"
}

W1::BitBlock::BitBlock()
{
    this->Clear();
}

W1::BitBlock::BitBlock(uint8_t value)
{   
    this->Clear();
    this->Data[0] = value;
}

void W1::BitBlock::Set(uint8_t index, bool value)
{
    if (value)
        SetOne(index);
    else
        SetZero(index);
}

void W1::BitBlock::SetOne(uint8_t index)
{
    ASSERT(index < C_BitsCount);
    this->Data[index / 8] |= (1 << (index % 8));
}

void W1::BitBlock::SetZero(uint8_t index)
{
    ASSERT(index < C_BitsCount);
    this->Data[index / 8] &= ~(1 << (index % 8));
}

bool W1::BitBlock::IsOne(uint8_t index)
{
    ASSERT(index < C_BitsCount);
    return this->Data[index / 8] & (1 << (index % 8));
}

bool W1::BitBlock::IsZero(uint8_t index)
{
    ASSERT(index < C_BitsCount);
    return !this->IsOne(index);
}

void W1::BitBlock::Clear()
{
    for (int8_t i = 0; i < C_BytesCount; i++)
        this->Data[i] = 0;
}

uint64_t W1::BitBlock::ToUInt64(uint8_t byteIndex)
{
    ASSERT(byteIndex + 8 <= C_BytesCount);
    ASSERT(C_BytesCount < 128);
    uint64_t retVal = 0;
    for(int8_t i = 7; i >= 0; i--)
    {
        retVal = retVal << 8;
        retVal = retVal | this->Data[i + byteIndex];
    }
    return retVal;
}

void W1::BitBlock::FromUInt64(uint64_t value, uint8_t byteIndex)
{
    ASSERT(byteIndex + 8 <= C_BytesCount);
    for(uint8_t i = 0; i < 8; i++)
    {
        this->Data[i + byteIndex] = value & 0xFF;
        value = value >> 8;
    }
}

uint8_t W1::Crc::Compute(uint8_t * data, uint16_t length)
{
    uint8_t crc = 0;

    while (length--) {
        crc = lookupTable[(crc ^ *data++)];
    }
	return crc;
}

uint8_t W1::Crc::Compute(BitBlock & data, uint8_t firstByte, uint8_t length)
{
    return W1::Crc::Compute(data.Data + firstByte, length);
}

const uint8_t  W1::Crc::lookupTable[] = {
      0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
    157,195, 33,127,252,162, 64, 30, 95,  1,227,189, 62, 96,130,220,
     35,125,159,193, 66, 28,254,160,225,191, 93,  3,128,222, 60, 98,
    190,224,  2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
     70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89,  7,
    219,133,103, 57,186,228,  6, 88, 25, 71,165,251,120, 38,196,154,
    101, 59,217,135,  4, 90,184,230,167,249, 27, 69,198,152,122, 36,
    248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91,  5,231,185,
    140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
     17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
    175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
     50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
    202,148,118, 40,171,245, 23, 73,  8, 86,180,234,105, 55,213,139,
     87,  9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
    233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
    116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53
    };

W1::OneWirePhysicalLayer::OneWirePhysicalLayer(uint8_t pinNumber) : pinNumber(pinNumber)
{
    this->Release();
    nrf_gpio_cfg(this->pinNumber, NRF_GPIO_PIN_DIR_OUTPUT, NRF_GPIO_PIN_INPUT_CONNECT, NRF_GPIO_PIN_NOPULL, NRF_GPIO_PIN_H0D1,NRF_GPIO_PIN_NOSENSE);
    if (C_driveDebugPin)
    {
        nrf_gpio_cfg_output(C_debugPinNumber);
    }
}

void W1::OneWirePhysicalLayer::PullDown()
{
    nrf_gpio_pin_clear(this->pinNumber);
    if (C_driveDebugPin)
    {
        nrf_gpio_pin_clear(C_debugPinNumber);
    }
}

void W1::OneWirePhysicalLayer::Release()
{
    nrf_gpio_pin_set(this->pinNumber);
    //nrf_gpio_cfg_input(this->pinNumber, NRF_GPIO_PIN_NOPULL);
    if (C_driveDebugPin)
    {
        nrf_gpio_pin_set(C_debugPinNumber);
    }
}

bool W1::OneWirePhysicalLayer::Read()
{
    return nrf_gpio_pin_read(this->pinNumber) != 0;
}

W1::OneWireResetSequence::OneWireResetSequence(W1::OneWirePhysicalLayer &w1) : state(W1::OneWireResetSequenceState::Idle), w1(w1), isSlavePresent(false)
{
}

bool W1::OneWireResetSequence::IsReady()
{
    return this->state == W1::OneWireResetSequenceState::Idle;
}

void W1::OneWireResetSequence::Run()
{
    ASSERT(this->IsReady());
    this->state = W1::OneWireResetSequenceState::Begin;
}

bool W1::OneWireResetSequence::IsSlavePresent()
{
    return this->isSlavePresent;
}

TS::DoWorkResult W1::OneWireResetSequence::DoWork(TS::TimeslotInfo timeslotInfo)
{
    const uint32_t resetLowLength = 480;
    const uint32_t resetHighLength = 480;
    const uint32_t presencePulseDelay = 90;
    const uint32_t safetySpan = 200;
    TS::DoWorkResult res;

    if (this->state == W1::OneWireResetSequenceState::Idle)
    {
        return timeslotInfo.Completed();
    }
    else if (this->state == W1::OneWireResetSequenceState::Begin)
    {
        if (!timeslotInfo.IsEnoughTime(resetLowLength + resetHighLength + safetySpan, res))
            return res;

        this->state = W1::OneWireResetSequenceState::ResetPulse;
        this->w1.PullDown();
        return timeslotInfo.WaitFromNow(resetLowLength);
    }
    else if (this->state == W1::OneWireResetSequenceState::ResetPulse)
    {
        this->w1.Release();
        this->state = W1::OneWireResetSequenceState::WaitingForPresencePulse;
        return timeslotInfo.WaitFromNow(presencePulseDelay);
    }
    else if (this->state == W1::OneWireResetSequenceState::WaitingForPresencePulse)
    {
        this->isSlavePresent = !this->w1.Read();
        this->state = W1::OneWireResetSequenceState::Delay;
        return timeslotInfo.WaitFromNow(resetHighLength - presencePulseDelay);
    }
    else if (this->state == W1::OneWireResetSequenceState::Delay)
    {
        this->state = W1::OneWireResetSequenceState::Idle;
        return timeslotInfo.Completed();
    }
    else
    {
        // not implemented state
        ASSERT(false);
        return timeslotInfo.Completed();
    }
}

W1::OneWireReadWriteSequence::OneWireReadWriteSequence(W1::OneWirePhysicalLayer &w1) : w1(w1), state(OneWireReadWriteSequenceState::Idle)
{
}

bool W1::OneWireReadWriteSequence::IsReady()
{
    return this->state == W1::OneWireReadWriteSequenceState::Idle;
}

W1::BitBlock &W1::OneWireReadWriteSequence::GetReceivedData()
{
    return this->readData;
}

uint8_t W1::OneWireReadWriteSequence::GetReadWriteLength()
{
    return this->length;
}

void W1::OneWireReadWriteSequence::Run(W1::BitBlock &writeData, W1::BitBlock &writeMask, uint8_t length)
{
    this->bitIndex = 0;
    this->writeData = writeData;
    this->writeMask = writeMask;
    this->length = length;
    this->readData.Clear();
    this->state = W1::OneWireReadWriteSequenceState::Working;
}

TS::DoWorkResult W1::OneWireReadWriteSequence::DoWork(TS::TimeslotInfo timeslotInfo)
{
    const uint32_t write0LowTime = 80;
    const uint32_t write1LowTime = 2;
    const uint32_t initReadTime = 2;
    const uint32_t readDelay = 4;
    const uint32_t slotLengthMax = 120;
    const uint32_t slotLengthMin = 60;
    const uint32_t recoveryTime = 2;
    const uint32_t safetySpan = 50; 
    TS::DoWorkResult res;

    if (this->state == W1::OneWireReadWriteSequenceState::Idle)
    {   
        return timeslotInfo.Completed();
    }
    else if (this->state == W1::OneWireReadWriteSequenceState::Working)
    {
        while (this->bitIndex < this->length)
        {
            if (!timeslotInfo.IsEnoughTime(write1LowTime + recoveryTime + safetySpan, res))
                return res;

            if (this->writeMask.IsOne(bitIndex))
            {
                // write bit
                bool value = this->writeData.IsOne(bitIndex);
                this->w1.PullDown();
                timeslotInfo.SpinDelay(value ? write1LowTime : write0LowTime);
                this->w1.Release();
                timeslotInfo.SpinDelay(value ? slotLengthMin : recoveryTime);
            }
            else
            {
                // read bit
                this->w1.PullDown();
                timeslotInfo.SpinDelay(initReadTime);
                this->w1.Release();
                timeslotInfo.SpinDelay(readDelay);
                if (w1.Read())
                {
                    this->readData.SetOne(bitIndex);
                }
                // else: readData is initialized to zeros at the begining of read/write transaction
                timeslotInfo.SpinDelay(slotLengthMax - readDelay - initReadTime);
                timeslotInfo.SpinDelay(recoveryTime);
            }
            bitIndex++;
        }

        this->state = W1::OneWireReadWriteSequenceState::Idle;
        return timeslotInfo.Completed();
    }
    else
    {
        // notimplemented (unknown) state
        ASSERT(false);
        return timeslotInfo.Completed();
    }
}

W1::OneWireBus::OneWireBus(uint8_t pinNumber) : state(W1::OneWireBusState::Idle), w1(pinNumber), resetSequence(w1), readWriteSequence(w1)
{
}

void W1::OneWireBus::Reset()
{
    ASSERT(this->state == W1::OneWireBusState::Idle);
    this->state = W1::OneWireBusState::Reset;
    this->resetSequence.Run();
}

void W1::OneWireBus::ReadWrite(bool reset, W1::BitBlock &writeData, W1::BitBlock &writeMask, uint8_t length)
{
    ASSERT(this->state == W1::OneWireBusState::Idle);
    this->state = reset ? W1::OneWireBusState::ResetAndReadWrite : W1::OneWireBusState::ReadWrite;
    if(reset)
        this->resetSequence.Run();
    this->readWriteSequence.Run(writeData, writeMask, length);
}

void W1::OneWireBus::ReadWrite(bool reset, uint16_t writeData, uint16_t writeMask, uint8_t length)
{
    ASSERT(this->state == W1::OneWireBusState::Idle);
    W1::BitBlock writeDataBlock;
    W1::BitBlock writeMaskBlock;
    writeDataBlock.Data[0] = writeData & 0xFF;
    writeDataBlock.Data[1] = (writeData & 0xFF00) >> 8;
    writeMaskBlock.Data[0] = writeMask & 0xFF;
    writeMaskBlock.Data[1] = (writeMask & 0xFF00) >> 8;
    this->ReadWrite(reset, writeDataBlock, writeMaskBlock, length);
}

void W1::OneWireBus::Read(bool reset, uint8_t length)
{
    W1::BitBlock writeData = 0;
    W1::BitBlock writeMask = 0;
    this->ReadWrite(reset, writeData, writeMask, length);
}

bool W1::OneWireBus::IsReady()
{
    return this->state == W1::OneWireBusState::Idle;
}

bool W1::OneWireBus::IsSlavePresent()
{
    return this->resetSequence.IsSlavePresent();
}

W1::BitBlock &W1::OneWireBus::GetReceivedData()
{
    return this->readWriteSequence.GetReceivedData();
}

uint8_t W1::OneWireBus::GetReadWriteLength()
{
    return this->readWriteSequence.GetReadWriteLength();
}

TS::DoWorkResult W1::OneWireBus::DoWork(TS::TimeslotInfo timeslotInfo)
{
    while (true)
    {
        if (this->state == W1::OneWireBusState::Idle)
        {
            return timeslotInfo.Completed();
        }
        else if (this->state == W1::OneWireBusState::Reset || this->state == W1::OneWireBusState::ResetAndReadWrite)
        {
            TS::DoWorkResult res = this->resetSequence.DoWork(timeslotInfo);
            if (res.type == TS::DoWorkResultType::Completed)
            {
                if (this->state == W1::OneWireBusState::ResetAndReadWrite)
                {
                    this->state = W1::OneWireBusState::ReadWrite;
                    continue;
                }
                else
                {
                    this->state = W1::OneWireBusState::Idle;
                }
            }
            return res;
        }
        else if (this->state == W1::OneWireBusState::ReadWrite)
        {
            TS::DoWorkResult res = this->readWriteSequence.DoWork(timeslotInfo);
            if (res.type == TS::DoWorkResultType::Completed)
            {
                this->state = W1::OneWireBusState::Idle;
            }
            return res;
        }
        else
        {
            ASSERT(false);
            return timeslotInfo.Completed();
        }
    }
}

W1::SearchRomHelper::SearchRomHelper(OneWireBus &bus) : bus(bus), state(W1::SearchRomHelperState::Idle), deviceCount(0)
{
}

void W1::SearchRomHelper::Run()
{
    ASSERT(this->bus.IsReady());

    this->bitIndex = 0;
    this->state = W1::SearchRomHelperState::ResetCmd;
    this->currentAddress.Clear();
    this->lastDiscrepancy = 0;
    this->lastZero = C_UnsetIndex;
    this->deviceCount = 0;
    bus.Reset();
}

TS::DoWorkResult W1::SearchRomHelper::DoWork(TS::TimeslotInfo timeslotInfo)
{
    if (this->state == W1::SearchRomHelperState::Idle)
    {
        return timeslotInfo.Completed();
    }

    while (true)
    {
        TS::DoWorkResult doWorkRes = this->bus.DoWork(timeslotInfo);

        if (doWorkRes.type == TS::DoWorkResultType::Completed)
        {
            if (this->state == W1::SearchRomHelperState::ResetCmd)
            {
                if (bus.IsSlavePresent())
                {
                    bus.ReadWrite(false, W1::RomCommand::SearchRom, 0xFF, 10); //write command (8 bits), read address bit (bit + complement, 2 bits)
                    this->state = W1::SearchRomHelperState::Search;
                }
                else
                {
                    this->deviceCount = 0;
                    this->state = W1::SearchRomHelperState::Idle;
                }
            }
            else if (this->state == W1::SearchRomHelperState::Search)
            {
                W1::BitBlock receivedData = bus.GetReceivedData();
                bool bit1 = receivedData.IsOne(bus.GetReadWriteLength() - 2);
                bool bit2 = receivedData.IsOne(bus.GetReadWriteLength() - 1);

                if (bit1 && !bit2)
                {
                    this->currentAddress.Set(this->bitIndex, true);
                }
                else if (!bit1 && bit2)
                {
                    this->currentAddress.Set(this->bitIndex, false);
                }
                else if (bit1 && bit2)
                {
                    // no response => no slave device
                    this->state = W1::SearchRomHelperState::Idle;
                }
                else
                {
                    //discrepancy
                    if (this->bitIndex < this->lastDiscrepancy)
                    {
                        // do nothing, use same value as in previous iteration
                    }
                    else if (this->bitIndex == this->lastDiscrepancy)
                    {
                        this->currentAddress.Set(this->bitIndex, true);
                    }
                    else
                    {
                        //this->bitIndex > this->lastDiscrepancy => set to zero and store index of discrepancy
                        this->currentAddress.Set(this->bitIndex, false);
                        this->lastZero = this->bitIndex;
                    }
                }

                // Prepare for next iteration
                if (this->bitIndex == 63)
                {
                    this->bitIndex = 0;
                    bool crcError = W1::Crc::Compute(this->currentAddress, 0, 7) != this->currentAddress.Data[7];
                    if (this->deviceCount < C_maxDeviceCount && !crcError)
                        this->devices[this->deviceCount++] = this->currentAddress.ToUInt64(0);
                    this->lastDiscrepancy = this->lastZero;
                    if (this->lastZero == C_UnsetIndex || crcError)
                    {
                        this->state = W1::SearchRomHelperState::Idle;
                    }
                    else
                    {
                        bus.Reset();
                        this->state = W1::SearchRomHelperState::ResetCmd;
                    }
                    this->lastZero = C_UnsetIndex;
                }
                else
                {
                    bool direction = this->currentAddress.IsOne(this->bitIndex);
                    this->bus.ReadWrite(false, direction ? 0x1 : 0x0, 0x1, 3);
                    this->bitIndex++;
                }
            }
            else if (this->state == W1::SearchRomHelperState::Idle)
            {
                return timeslotInfo.Completed();
            }
        }
        else
        {
            return doWorkRes;
        }
    }
}

bool W1::SearchRomHelper::IsReady()
{
    return this->state == W1::SearchRomHelperState::Idle;
}

uint8_t W1::SearchRomHelper::GetDeviceCount()
{
    return this->deviceCount;
}

uint64_t W1::SearchRomHelper::GetDeviceAddress(uint8_t index)
{
    return this->devices[index];
}

