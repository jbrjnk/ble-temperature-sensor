#define NRF_LOG_MODULE_NAME "APP"

#ifdef __cplusplus
extern "C"
{
#endif
#include "app_uart.h"
#include "app_scheduler.h"
#include "app_timer_appsh.h"
#include "app_timer.h"
#include "softdevice_handler.h"
#include "ble.h"
#include "boards.h"
#include "nrf_delay.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_assert.h"
#include "nrf_sdm.h"
#include "nrf_drv_adc.h"
#include "nrf_drv_uart.h"

  typedef __uint32_t uint32_t;
  void __cxa_pure_virtual()
  {
    while (1)
      ;
  }

#ifdef __cplusplus
}
#endif

#include "app_global.h"

#include <cstdio>
#include <cstdlib>

#include "TimeslotManager.h"
#include "DS18B20.h"
#include "SupplyBranch.h"
#include "BleAdvertiser.h"
#include "SwUart.h"
#include "StatusLedDriver.h"

//#define USE_SW_UART_LOGGING

static const uint8_t C_oneWireBusPin = 18;
static const uint8_t C_supplyBranchEnPin = 21; // pin enabling high consumption supply branch
static const uint8_t C_blinkPin = 16; // status LED

static const uint8_t C_SwUartLogPin = 23; //SW Uart log (can be same as )

void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
  unsigned int tmp = id;
  NRF_LOG_ERROR("app_error_print():\r\n");
  NRF_LOG_ERROR("Fault identifier:  0x%X\r\n", tmp);
  NRF_LOG_ERROR("Program counter:   0x%X\r\n", tmp = pc);
  NRF_LOG_ERROR("Fault information: 0x%X\r\n", tmp = info);

  const char *fileName = nullptr;
  switch (id)
  {
  case NRF_FAULT_ID_SDK_ASSERT:
    NRF_LOG_ERROR("Line Number: %u\r\n", tmp = ((assert_info_t *)(info))->line_num);
    fileName = reinterpret_cast<const char *>(((assert_info_t *)(info))->p_file_name);
    break;

  case NRF_FAULT_ID_SDK_ERROR:
    NRF_LOG_ERROR("Line Number: %u\r\n", tmp = ((error_info_t *)(info))->line_num);
    fileName = reinterpret_cast<const char *>(((error_info_t *)(info))->p_file_name);
    NRF_LOG_ERROR("Error Code:  0x%X\r\n", tmp = ((error_info_t *)(info))->err_code);
    break;
  }
  nrf_log_frontend_std_0(NRF_LOG_LEVEL_ERROR, fileName);
  NRF_LOG_FINAL_FLUSH();

  app_error_save_and_stop(id, pc, info);
}

static void sys_evt_dispatch(uint32_t evt_id)
{
  TS::TimeslotManager::Instance().ProcessSystemEvent(evt_id);
}

struct AppContext
{
  AppContext()
  {
    temperatureUpdated = false;
    swUart = nullptr;
    ds18b20Driver = nullptr;
  }

  DS18B20::Driver *ds18b20Driver;
  SwUart::Transmitter *swUart;
  bool temperatureUpdated = false;
};

AppContext appContext;

void InitSoftdevice()
{
  // Init
  uint32_t err_code;
  nrf_clock_lf_cfg_t clock_lf_cfg = NRF_CLOCK_LFCLKSRC;
  SOFTDEVICE_HANDLER_INIT(&clock_lf_cfg, NULL);

  // Enable
  ble_enable_params_t ble_enable_params;
  err_code = softdevice_enable_get_default_config(0, 1, &ble_enable_params);
  APP_ERROR_CHECK(err_code);
  CHECK_RAM_START_ADDR(0, 1);
  err_code = softdevice_enable(&ble_enable_params);

  // Register with the SoftDevice handler module for System events.
  err_code = softdevice_sys_evt_handler_set((sys_evt_handler_t)sys_evt_dispatch);
  APP_ERROR_CHECK(err_code);
  NRF_LOG_INFO("Softdevice initialized\r\n");
  NRF_LOG_FLUSH();
}

void InitGap()
{
  uint32_t err_code;
  ble_gap_conn_sec_mode_t sec_mode;

  BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);

  const char *gapDeviceName = BLE_GAP_DEVICE_NAME;
  uint8_t gapDeviceNameLen = strlen(gapDeviceName);
  err_code = sd_ble_gap_device_name_set(&sec_mode, (const uint8_t *)gapDeviceName, gapDeviceNameLen);
  APP_ERROR_CHECK(err_code);

  err_code = sd_ble_gap_tx_power_set(BLE_GAP_TX_POWER);
  APP_ERROR_CHECK(err_code);
}

void StartMeasurementHandler(void *p_context)
{
  NRF_LOG_DEBUG("Start temperature measurement DS18B20 \r\n");
  AppContext *appContext = static_cast<AppContext *>(p_context);
  if (appContext->ds18b20Driver)
  {
    appContext->ds18b20Driver->StartConversion();
    appContext->temperatureUpdated = false;
  }
}

void UpdateData(void *p_context)
{
  AppContext *appContext = static_cast<AppContext *>(p_context);
  if (appContext->ds18b20Driver && appContext->ds18b20Driver->IsConversionCompleted() & !appContext->temperatureUpdated)
  {
    appContext->temperatureUpdated = true;
    // Update temperature data
    {
      NRF_LOG_INFO("Temperature conversion completed \r\n");
      uint8_t sensorsCount = appContext->ds18b20Driver->GetSensorsCount();
      for (uint8_t i = 0; i < sensorsCount; i++)
      {
        uint64_t address = appContext->ds18b20Driver->GetResult()[i].address;
        uint32_t temperature = appContext->ds18b20Driver->GetResult()[i].temperature;
        bool isValid = appContext->ds18b20Driver->GetResult()[i].dataValid;
        NRF_LOG_INFO("  Address (hex): %x %x \r\n", address >> 32, address & 0xFFFFFFFF);
        NRF_LOG_INFO("  Temperature: %d.%d °C \r\n", temperature / 10000, temperature % 10000);
        if (isValid)
        {
          NRF_LOG_INFO("  OK\r\n");
        }
        else
        {
          NRF_LOG_INFO("  Value is not up to date\r\n");
        }
      }
      int32_t temperature1 = sensorsCount >= 1 ? appContext->ds18b20Driver->GetResult()[0].temperature : 0;
      int32_t temperature2 = sensorsCount >= 2 ? appContext->ds18b20Driver->GetResult()[1].temperature : 0;
      BleAdvertiser::Instance().SetTemperature(temperature1, temperature2, -4);
    }

    // Update battery voltage
    {
      nrf_drv_adc_channel_t channelConfig;
      memset(&channelConfig, 0, sizeof(channelConfig));
      channelConfig.config.config.ain = NRF_ADC_CONFIG_INPUT_DISABLED;
      channelConfig.config.config.reference = NRF_ADC_CONFIG_REF_VBG;
      channelConfig.config.config.input = NRF_ADC_CONFIG_SCALING_SUPPLY_ONE_THIRD;
      channelConfig.config.config.resolution = NRF_ADC_CONFIG_RES_8BIT;
      channelConfig.p_next = nullptr;
      nrf_adc_value_t value = 0;
      nrf_drv_adc_sample_convert(&channelConfig, &value);
      uint16_t mV = value * (3 * 1200 + 128) / 286;
      NRF_LOG_INFO("ADC Battery voltage. Voltage: %d mV\r\n", mV);
      BleAdvertiser::Instance().SetVoltage(mV);
    }

    //Print temperature from internal temperature sensor
    {
      int32_t temp;
      sd_temp_get(&temp);
      temp *= 25;
      NRF_LOG_INFO("Internal temperature sensor: %d.%d \r\n", temp / 100, temp % 100);
    }
    BleAdvertiser::Instance().Update();
  }
}

void InitAdc()
{
  ret_code_t ret_code;
  nrf_drv_adc_config_t config = NRF_DRV_ADC_DEFAULT_CONFIG;

  ret_code = nrf_drv_adc_init(&config, nullptr);
  APP_ERROR_CHECK(ret_code);
  NRF_LOG_INFO("ADC Initialized \r\n");
}

APP_TIMER_DEF(startMeasurementTimer);

uint32_t OnTimerTaskElapsed(app_timer_timeout_handler_t timeout_handler, void *p_context)
{
  bool handled = false;
  handled = TS::TimeslotManager::Instance().OnTimerTaskElapsed(timeout_handler, p_context);

  if (!handled)
  {
    return app_timer_evt_schedule(timeout_handler, p_context);
  }
  else
  {
    return NRF_SUCCESS;
  }
}

int main(void)
{

  // Prepare logges
  NRF_LOG_INIT(NULL);

  //Init soft device
  InitSoftdevice();
  NRF_LOG_FLUSH();

  //Prepare task scheduler and timer library
  APP_SCHED_INIT(8, 12);
  APP_TIMER_INIT(TIMER_LIB_PRESCALER, 12, OnTimerTaskElapsed);

  InitGap();
  NRF_LOG_FLUSH();
  InitAdc();
  NRF_LOG_FLUSH();

  BleAdvertiser::Instance().Start();
  app_timer_create(&startMeasurementTimer, APP_TIMER_MODE_REPEATED, StartMeasurementHandler);

  NRF_LOG_FLUSH();

  SupplyBranch highConsumptionBranch(C_supplyBranchEnPin);

  StatusLedDriver statusLed(highConsumptionBranch.GetHandle(), C_blinkPin);

  W1::OneWireBus oneWireBus(C_oneWireBusPin);
  DS18B20::Driver driver(TS::TimeslotManager::Instance(), oneWireBus, highConsumptionBranch.GetHandle());
  appContext.ds18b20Driver = &driver;

  //disable HW uart and reuse same pin for SW uart
#ifdef USE_SW_UART_LOGGING
  nrf_drv_uart_t uartInstance = {
      .reg = {(NRF_UART_Type *)NRF_DRV_UART_PERIPHERAL(0)},
      .drv_inst_idx = CONCAT_3(UART, 0, _INSTANCE_INDEX),
  };
  nrf_drv_uart_uninit(&uartInstance);
  SwUart::Transmitter swUart(TS::TimeslotManager::Instance(), C_SwUartLogPin, 115200);
  appContext.swUart = &swUart;
#endif

  TS::TimeslotManager::Instance().Init();
#ifdef USE_SW_UART_LOGGING
  SwUart::LoggerSink::SetSwUart(&swUart);
#endif

  // Start timers
  app_timer_start(startMeasurementTimer, APP_TIMER_TICKS(MEASUREMENT_INTERVAL_MS, TIMER_LIB_PRESCALER), static_cast<void *>(&appContext));

  while (true)
  {
    app_sched_execute();

    NRF_LOG_FLUSH();

    TS::TimeslotManager::Instance().DoWork();
    UpdateData(&appContext);
    NRF_LOG_FLUSH();
    sd_app_evt_wait();

    NRF_LOG_FLUSH();
  }
}
