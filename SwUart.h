#ifndef SWUART_H_407237a5e49f
#define SWUART_H_407237a5e49f

#include <cstdint>
#include "TimeslotManager.h"

namespace SwUart
{
    // Software-only implementation of UART transmitter (using Timeslot API). Can be useful for logging if HW UART is in use.
    class Transmitter : public TS::ITimeslotTask
    {
        public:
            static const uint16_t C_bufferLength = 128;
            static const uint16_t C_safetySpan = 500;

            Transmitter(TS::TimeslotManager & timeslotManager, uint8_t pinNumber, uint32_t baudRate);
            uint16_t Write(uint8_t * buffer, uint16_t offset, uint16_t length);
            bool IsEmpty();
            bool IsFull();
            uint16_t GetQueueLength();
            bool IsEnoughSpace(uint16_t length);

            virtual void Init() override;
            virtual TS::DoWorkResult DoWork(TS::TimeslotInfo &timeslotInfo) override;
            virtual uint32_t GetRequestedDuration() override;

        private:
            void SetOutput(bool value);

            TS::TimeslotManager & timeslotManager;
            uint8_t pinNumber;
            uint32_t baudRate;
            uint16_t head;
            uint16_t tail;
            bool lastWasEnqueue;
            uint32_t baudDuration;
            uint8_t buffer[C_bufferLength];
    };

    class LoggerSink
    {
        public:
            static void SetSwUart(Transmitter * transmitter);
            static Transmitter * transmitter;
        private:
            static bool nrf_log_std_handler(uint8_t severity_level, const uint32_t * const p_timestamp, const char * const p_str, uint32_t * p_args, uint32_t nargs);
            static uint32_t nrf_log_hexdump_handler(uint8_t severity_level, const uint32_t * const p_timestamp, const char * const p_str, uint32_t offset, const uint8_t * const  p_buf0, uint32_t buf0_length, const uint8_t * const  p_buf1, uint32_t buf1_length);
    };
};

#endif