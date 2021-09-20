# ble-temperature-sensor
Bluetooth low energy temeperature sensor (using NRF51822 and DS18B20)

ble-tempearature-sensor is a low power temperature sensor which transmits measured value over BLE. The core of this design is Nordic NRF51822 Core Board. As a temperature sensor is used Dallas DS18B20. The communication with DS18B20 over 1-wire bus is fully implemented in software using Timeslot API. Timeslot API allows to achive time accurate driving of the bus which doesn't conflict with softdevice interrupts.

This repository contains also a Dockerfile with build environment and VS Code configuration file which integrates build and flash commands to VS Code.

SDK: 12.3.0
Softdevice: S130

![Photo](/images/photo1.jpg)

![Photo](/images/photo2.jpg)

![PCB](/images/board.png)

![Screenshot](/images/screenshot.jpg)
