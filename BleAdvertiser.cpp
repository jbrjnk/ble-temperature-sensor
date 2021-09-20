extern "C"
{
#include "BleAdvertiser.h"
#include "ble_srv_common.h"
#include "nrf.h"
#include "nrf_soc.h"
#include "boards.h"
#include "nrf_log.h"
}

#include "app_global.h"

BleAdvertiser &BleAdvertiser::Instance()
{
    static BleAdvertiser instance;
    return instance;
}

BleAdvertiser::BleAdvertiser() : temperatureData(0), batteryData(0), manufacturerData(0), advertiseTemperature(false), advertisingEnabled(false)
{
}

void BleAdvertiser::OnAdvertisingEvent(ble_adv_evt_t ble_adv_evt)
{
    NRF_LOG_INFO("Advertising event %d\r\n", ble_adv_evt);
}

void BleAdvertiser::Start()
{
    if (!this->advertisingEnabled)
    {
        uint32_t errCode;
        ble_gap_adv_params_t adv_params;

        memset(&adv_params, 0, sizeof(adv_params));
        adv_params.type = BLE_GAP_ADV_TYPE_ADV_NONCONN_IND;
        adv_params.p_peer_addr = NULL;
        adv_params.fp = BLE_GAP_ADV_FP_ANY;
        adv_params.interval = MSEC_TO_UNITS(ADVERTISING_INTERVAL_MS, UNIT_0_625_MS);

        errCode = sd_ble_gap_adv_start(&adv_params);
        APP_ERROR_CHECK(errCode);

        ble_advdata_t advData;
        ble_advdata_service_data_t serviceData[2];
        ble_advdata_manuf_data_t manufData;

        serviceData[0].service_uuid = BLE_UUID_HEALTH_THERMOMETER_SERVICE;
        serviceData[0].data.size = sizeof(this->temperatureData);
        serviceData[0].data.p_data = (uint8_t *)&this->temperatureData;

        serviceData[1].service_uuid = BLE_UUID_BATTERY_SERVICE;
        serviceData[1].data.size = 1;
        serviceData[1].data.p_data = &batteryData;

        manufData.company_identifier = 0xFFFF;
        manufData.data.size = 4;
        manufData.data.p_data = reinterpret_cast<uint8_t *>(&manufacturerData);

        memset(&advData, 0, sizeof(advData));
        advData.name_type = BLE_ADVDATA_FULL_NAME;
        advData.include_appearance = false;
        advData.flags = BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED;
        advData.service_data_count = 2;
        advData.p_service_data_array = serviceData;
        advData.p_manuf_specific_data = &manufData;

        errCode = ble_advdata_set(&advData, nullptr);
        APP_ERROR_CHECK(errCode);
    }
    this->advertisingEnabled = true;
}

void BleAdvertiser::Stop()
{
    if (this->advertisingEnabled)
    {
        sd_ble_gap_adv_stop();
    }
    this->advertisingEnabled = false;
}

void BleAdvertiser::SetVoltage(uint16_t milliVolts)
{
    batteryData = (milliVolts + 15) / 30;
}

void BleAdvertiser::Update()
{
    if (this->advertisingEnabled)
    {
        this->Stop();
        this->Start();
    }
}

void BleAdvertiser::SetTemperature(int32_t sensor1, int32_t sensor2, int8_t exponent)
{
    temperatureData = ((exponent & 0xFF) << 24) | (sensor1 & 0x00FFFFFF);

    manufacturerData = 0;
    manufacturerData |= ((sensor2 / 1) % 10) << 24;
    manufacturerData |= ((sensor2 / 10) % 10) << 28;
    manufacturerData |= ((sensor2 / 100) % 10) << 16;
    manufacturerData |= ((sensor2 / 1000) % 10) << 20;
    manufacturerData |= ((sensor2 / 10000) % 10) << 8;
    manufacturerData |= ((sensor2 / 100000) % 10) << 12;
    advertiseTemperature = true;
}
