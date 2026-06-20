# ESP32 Smart Home Controller

An IoT based smart home controller using ESP32 WebServer.  
This project allows controlling LEDs wirelessly using a mobile/PC browser through ESP32 WiFi.

## Features

- WiFi based control using ESP32 SoftAP
- Web based LED control
- Multiple LED control
- LED ON/OFF switching
- PWM brightness control using sliders
- OLED display for ESP32 IP address
- No external WiFi router required

## Hardware Used

- ESP32 DevKit V1
- OLED Display (128x64 I2C)
- LEDs
- Resistors
- Jumper wires
- Breadboard

## Libraries Used

### ESP32 Built-in Libraries

- `WiFi.h`
  - Creates ESP32 WiFi Access Point

- `WebServer.h`
  - Creates web server for controlling devices

### External Libraries

- `Adafruit_GFX.h`
  - Graphics library for OLED

- `Adafruit_SSD1306.h`
  - OLED display driver

- `Wire.h`
  - I2C communication

## Pin Configuration

| Component | ESP32 Pin |
|---|---|
| LED 1 | GPIO 4 |
| LED 2 | GPIO 5 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |

## How It Works

1. ESP32 creates its own WiFi network.
2. User connects phone/laptop to ESP32 WiFi.
3. Open ESP32 IP address in browser.
4. Control LEDs from the webpage.
5. PWM slider changes LED brightness.

## Circuit Diagram

![Circuit Diagram](docs/circuitdiagram.png)
