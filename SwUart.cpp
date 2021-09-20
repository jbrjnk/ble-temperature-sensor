#include "SwUart.h"
#include <cstring>
#include <cstdio>

extern "C"
{
#include "nrf.h"
#include "nrf_soc.h"
#include "app_util_platform.h"
#include "nrf_gpio.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
}


SwUart::Transmitter::Transmitter(TS::TimeslotManager & timeslotManager, uint8_t pinNumber, uint32_t baudRate) : timeslotManager(timeslotManager), pinNumber(pinNumber), baudRate(baudRate), head(0), tail(0), lastWasEnqueue(false)
{
    this->baudDuration = (1000000 + (baudRate / 2)) / (baudRate);
    nrf_gpio_cfg(this->pinNumber, NRF_GPIO_PIN_DIR_OUTPUT, NRF_GPIO_PIN_INPUT_CONNECT, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_S0S1, NRF_GPIO_PIN_NOSENSE);
    timeslotManager.AddTask(this);
}

bool SwUart::Transmitter::IsEmpty()
{
    return this->GetQueueLength() == 0;
}

bool SwUart::Transmitter::IsFull()
{
    return this->GetQueueLength() >= C_bufferLength;
}

uint16_t SwUart::Transmitter::GetQueueLength()
{
    uint16_t used;
    CRITICAL_REGION_ENTER();
    used = (this->tail - this->head) % C_bufferLength;
    if(used == 0 && lastWasEnqueue){used = C_bufferLength;}
    CRITICAL_REGION_EXIT();
    return used;
}

bool SwUart::Transmitter::IsEnoughSpace(uint16_t length)
{
    return C_bufferLength - this->GetQueueLength() >= length;
}

uint16_t SwUart::Transmitter::Write(uint8_t * buffer, uint16_t offset, uint16_t length)
{
    uint16_t freeSpace  = (C_bufferLength - this->GetQueueLength());
    uint16_t sent = 0;

    if(freeSpace)
    {
        for(uint16_t i = 0; i < freeSpace && i < length; i++)
        {
            this->buffer[(this->tail + i) % C_bufferLength] = buffer[offset + i];
            sent++;
        }

        CRITICAL_REGION_ENTER();
        this->tail = (this->tail + sent) % C_bufferLength;
        this->lastWasEnqueue = true;
        CRITICAL_REGION_EXIT();

        TS::TimeslotManager::Instance().RequestTimeslot(this);
    }
    return sent;
}

void SwUart::Transmitter::Init()
{/* inherited from interface, nothing to do */}

TS::DoWorkResult SwUart::Transmitter::DoWork(TS::TimeslotInfo &timeslotInfo)
{
    while(true)
    {
        TS::DoWorkResult res;
        bool isEnoughTime = timeslotInfo.IsEnoughTime(10 * this->baudDuration + C_safetySpan, res);

        bool isEmpty;
        uint8_t byte;
        isEmpty = this->IsEmpty();
        if(isEnoughTime && !isEmpty)
        {
            CRITICAL_REGION_ENTER();
            byte = this->buffer[this->head];
            this->head = (this->head + 1) % C_bufferLength;;
            this->lastWasEnqueue = false;
            CRITICAL_REGION_EXIT();
        }

        if (isEmpty)
        {
            return timeslotInfo.Completed();
        }
        else if(!isEnoughTime)
        {
            return res;
        }

        uint32_t ticks = timeslotInfo.GetTicks();
        nrf_gpio_pin_clear(this->pinNumber); // start bit
        uint8_t mask = 1;

        for(uint8_t i=0; i < 8; i++ )
        {
            timeslotInfo.SpinDelayTill(ticks += this->baudDuration);
            nrf_gpio_pin_write(this->pinNumber, byte & mask);
            mask = mask << 1;
        }

        timeslotInfo.SpinDelayTill(ticks += this->baudDuration);
        nrf_gpio_pin_set(this->pinNumber); // stop bit
        timeslotInfo.SpinDelayTill(ticks += this->baudDuration);
    }
}

uint32_t SwUart::Transmitter::GetRequestedDuration()
{
    return 3000;
}

void SwUart::LoggerSink::SetSwUart(Transmitter * transmitter)
{
    SwUart::LoggerSink::transmitter = transmitter;
    NRF_LOG_HANDLERS_SET(SwUart::LoggerSink::nrf_log_std_handler, SwUart::LoggerSink::nrf_log_hexdump_handler);
}

bool SwUart::LoggerSink::nrf_log_std_handler(uint8_t severity_level, const uint32_t * const p_timestamp, const char * const p_str, uint32_t * p_args, uint32_t nargs)
{
    char str[SwUart::Transmitter::C_bufferLength];
    uint16_t len = 0;

    switch (nargs)
    {
        case 0:
        {
            len = strlen(p_str);
            if (len > SwUart::Transmitter::C_bufferLength)
            {
                len = SwUart::Transmitter::C_bufferLength;
            }
            {
                memcpy(str, p_str, len);
            }
            break;
        }

        case 1:
            len = snprintf(str, SwUart::Transmitter::C_bufferLength, p_str, p_args[0]);
            break;

        case 2:
            len = snprintf(str, SwUart::Transmitter::C_bufferLength, p_str, p_args[0], p_args[1]);
            break;

        case 3:
            len = snprintf(str, SwUart::Transmitter::C_bufferLength, p_str, p_args[0], p_args[1], p_args[2]);
            break;

        case 4:
            len = snprintf(str, SwUart::Transmitter::C_bufferLength, p_str, p_args[0], p_args[1], p_args[2], p_args[3]);
            break;

        case 5:
            len = snprintf(str, SwUart::Transmitter::C_bufferLength, p_str, p_args[0], p_args[1], p_args[2], p_args[3], p_args[4]);
            break;

        case 6:
            len = snprintf(str, SwUart::Transmitter::C_bufferLength, p_str, p_args[0], p_args[1], p_args[2], p_args[3], p_args[4], p_args[5]);
            break;

        default:
            break;
    }

    //Transmitt pending data
    while(!SwUart::LoggerSink::transmitter->IsEnoughSpace(len))
    {
        TS::TimeslotManager::Instance().DoWork();
    }

    //Send data
    uint16_t sent = SwUart::LoggerSink::transmitter->Write(reinterpret_cast<uint8_t*>(str), 0, len);
    ASSERT(sent == len);

    //Transmitt current log
    while(!SwUart::LoggerSink::transmitter->IsEmpty())
    {
        TS::TimeslotManager::Instance().DoWork();
    }

    return true;
}


uint32_t SwUart::LoggerSink::nrf_log_hexdump_handler(uint8_t severity_level, const uint32_t * const p_timestamp, const char * const p_str, uint32_t offset, const uint8_t * const  p_buf0, uint32_t buf0_length, const uint8_t * const  p_buf1, uint32_t buf1_length)
{
    //not implemented
    return buf0_length + buf1_length;
}

SwUart::Transmitter *  SwUart::LoggerSink::transmitter = nullptr;
