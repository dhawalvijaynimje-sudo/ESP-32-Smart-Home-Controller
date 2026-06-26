# ESP32 Smart Home Controller

A WiFi based smart home controller built using ESP32 with web-based device control.

## Version

Current Version: v1.2.0


## Features

- Control devices using ESP32 web server
- WiFi Access Point mode
- LED ON/OFF control
- LED brightness control using PWM
- DC motor / fan control
- Fan speed control using PWM
- L298N motor driver support
- OLED display status
- Real-time device status monitoring


## Hardware Used

- ESP32 DevKit V1
- SSD1306 OLED Display
- L298N Motor Driver
- LED Module
- DC Motor / Fan


## Pin Configuration

### LED

| Component | ESP32 Pin |
|---|---|
| LED PWM | GPIO 4 |


### L298N Motor Driver

| L298N | ESP32 |
|---|---|
| ENA | GPIO 5 |
| IN1 | GPIO 18 |
| IN2 | GPIO 19 |


### OLED

| OLED | ESP32 |
|---|---|
| SDA | GPIO 21 |
| SCL | GPIO 22 |


## How To Use

1. Upload code to ESP32
2. Connect phone to:
