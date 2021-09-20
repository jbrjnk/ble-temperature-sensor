#ifndef ADVERTISER_H_ed1b2f259578
#define ADVERTISER_H_ed1b2f259578

#include <cstdint>
#include <ble_advertising.h>

class BleAdvertiser
{
private:
    BleAdvertiser();
    BleAdvertiser(BleAdvertiser const &) = delete;
    BleAdvertiser(BleAdvertiser &&) = delete;
    BleAdvertiser &operator=(BleAdvertiser const &) = delete;
    BleAdvertiser &operator=(BleAdvertiser &&) = delete;

    static void OnAdvertisingEvent(ble_adv_evt_t ble_adv_evt);

    void StartInternal();
    void StopInternal();

    uint32_t temperatureData;
    uint8_t batteryData;
    uint32_t manufacturerData;
    bool advertiseTemperature;
    bool advertisingEnabled;

public:
    static BleAdvertiser & Instance();

    void Start();
    void Stop();
    void SetTemperature(int32_t sensor1, int32_t sensor2, int8_t exponent);
    void SetVoltage(uint16_t milliVolts);
    void Update();
};

#endif