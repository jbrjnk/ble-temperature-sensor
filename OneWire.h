#ifndef TIMESLOTMANAGER_H_749ac65c9f6f
#define TIMESLOTMANAGER_H_749ac65c9f6f

#include "TimeslotManager.h"

namespace W1
{
    class BitBlock
    {
        public:
            static const uint8_t C_BytesCount = 12;
            static const uint8_t C_BitsCount = C_BytesCount * 8;

            BitBlock();
            BitBlock(uint8_t value);
            uint8_t Data[C_BytesCount];
            void Set(uint8_t index, bool value);
            void SetOne(uint8_t index);
            void SetZero(uint8_t index);
            bool IsOne(uint8_t index);
            bool IsZero(uint8_t index);
            void Clear();

            uint64_t ToUInt64(uint8_t byteIndex);
            void FromUInt64(uint64_t value, uint8_t byteIndex);
    };

    class Crc
    {
    public:
        static uint8_t Compute(uint8_t * data, uint16_t length);
        static uint8_t Compute(BitBlock & data, uint8_t firstByte, uint8_t length);
        static const uint8_t lookupTable[];
    };

    class OneWirePhysicalLayer
    {
        public:
            static const bool C_driveDebugPin = true;
            static const uint8_t C_debugPinNumber = 3;

            OneWirePhysicalLayer(uint8_t pinNumber);
            void PullDown();
            void Release();
            bool Read(); //true = high, false = low
        private:
            uint8_t pinNumber;
    };

    enum class OneWireResetSequenceState
    {
        Idle,
        Begin,
        ResetPulse,
        WaitingForPresencePulse,
        Delay
    };

    class OneWireResetSequence
    {
        public:
            OneWireResetSequence(W1::OneWirePhysicalLayer & w1);
            bool IsReady();
            void Run();
            TS::DoWorkResult DoWork(TS::TimeslotInfo timeslotInfo);
            bool IsSlavePresent();
        private:
            OneWireResetSequenceState state;
            OneWirePhysicalLayer & w1;
            bool isSlavePresent;
    };

    enum class OneWireReadWriteSequenceState
    {
        Idle,
        Working
    };

    class OneWireReadWriteSequence
    {
        public:
            OneWireReadWriteSequence(OneWirePhysicalLayer & w1);
            bool IsReady();
            void Run(BitBlock & writeData, BitBlock & writeMask, uint8_t length);
            TS::DoWorkResult DoWork(TS::TimeslotInfo timeslotInfo);
            BitBlock & GetReceivedData();
            uint8_t GetReadWriteLength();
        private:
            OneWirePhysicalLayer & w1;
            OneWireReadWriteSequenceState state;
            uint8_t bitIndex;
            BitBlock writeData;
            BitBlock writeMask;
            BitBlock readData;
            uint8_t length;
    };

    enum class OneWireBusState
    {
        Idle,
        Reset,
        ReadWrite,
        ResetAndReadWrite
    };

    class OneWireBus
    {
        public:
            OneWireBus(uint8_t pinNumber);
            TS::DoWorkResult DoWork(TS::TimeslotInfo timeslotInfo);

            void Reset();
            void ReadWrite(bool reset, BitBlock & writeData, BitBlock & writeMask, uint8_t length);
            void ReadWrite(bool reset, uint16_t writeData, uint16_t  writeMask, uint8_t length);
            void Read(bool reset, uint8_t length);

            bool IsReady();
            void Disable();
            bool IsSlavePresent();
            BitBlock & GetReceivedData();
            uint8_t GetReadWriteLength();
        private:
            OneWireBusState state;
            OneWirePhysicalLayer w1;
            OneWireResetSequence resetSequence;
            OneWireReadWriteSequence readWriteSequence;
    };

    enum class SearchRomHelperState
    {
        Idle,
        ResetCmd,
        Search,
    };

    class SearchRomHelper
    {
        public:
            static const uint8_t C_maxDeviceCount = 8; // maximal number of 1-wire devices

            SearchRomHelper(OneWireBus & bus);
            void Run();
            TS::DoWorkResult DoWork(TS::TimeslotInfo timeslotInfo);
            bool IsReady();
            uint8_t GetDeviceCount();
            uint64_t GetDeviceAddress(uint8_t index);            

        private:
            static const uint8_t C_UnsetIndex = 255;

            OneWireBus bus;
            SearchRomHelperState state;
            uint8_t deviceCount;
            uint64_t devices[C_maxDeviceCount];

            uint8_t bitIndex;
            BitBlock currentAddress;
            uint8_t lastDiscrepancy;
            uint8_t lastZero;
    };

    class RomCommand
    {
    public:
        static const uint8_t SearchRom = 0xF0;
        static const uint8_t ReadRom = 0x33;
        static const uint8_t MatchRom = 0x55;
        static const uint8_t SkipRom = 0xCC;
        static const uint8_t AlarmSearch = 0xEC;
    };
}
#endif
