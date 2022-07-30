# TOTP Token
A hardware [TOTP](https://en.wikipedia.org/wiki/Time-based_one-time_password) token gadget, made with STM32 and ESP32. 

---
- [TOTP Token](#totp-token)
  - [Getting Started](#getting-started)
    - [Software Requirements](#software-requirements)
    - [Hardware Requirements](#hardware-requirements)
    - [Wiring](#wiring)
  - [Notes](#notes)
    - [Interfacing with ESP32 (AT Firmware)](#interfacing-with-esp32-at-firmware)
      - [Hardware Connection](#hardware-connection)
      - [Samples](#samples)
    - [Nucleo-F412ZG Pinout Reference](#nucleo-f412zg-pinout-reference)
---
## Getting Started
This project is primarily set up with STM32CubeMX and can be built with `gcc` and `make`. 

### Software Requirements
- arm-none-eabi-gcc
- make
- STM32CubeMX (Development only)
- openocd (Development only)

As an example, development is done on an Arch Linux system, with the following packages installed for cross-compilation and debugging: 
- arm-none-eabi-binutils 
- arm-none-eabi-gcc 
- arm-none-eabi-gdb 
- arm-none-eabi-newlib
- make
- openocd
- picocom
- stm32cubemx (AUR package)

Additionally, [`bear`](https://github.com/rizsotto/Bear) can be used to generate `compile_commands.json` for VSCode C/C++ extension's IntelliSense. 

### Hardware Requirements
- [STM32 Nucleo-F412ZG](https://www.st.com/en/evaluation-tools/nucleo-f412zg.html)
- [ESP32-C3-DevKit](https://github.com/wuxx/nanoESP32-C3) (should work with any ESP32-C3 modules)
- ST7735S TFT Display (1.8 inch, 160x128) from AliExpress/Taobao
- Breadboard for wiring

### Wiring
<!-- TODO -->
---
## Notes
- ESP32 (AT Firmware) echoes serial input. 
- AT command responses end with CR+LF. 

### Interfacing with ESP32 (AT Firmware)
#### Hardware Connection
STM32 communicates with ESP32 over its USART2 interface. USART2, as of the time this document is written, uses the GPIOs PA2/3. 

![](.assets/Screenshot_20220728_135106.png)

| STM32                   | Opt.1: ESP32 | Opt.2: USB-TTL (PC) |
| ----------------------- | ------------ | ------------------- |
| CN9 - A0(RX, PA3)       | D7(USART1TX) | TX                  |
| CN10 - ADC1/2 (TX, PA2) | D6(USART1RX) | RX                  |

#### Samples
```
at

OK
at+gmr
AT version:2.4.0.0(4c6eb5e - ESP32C3 - May 20 2022 03:11:59)
SDK version:qa-test-v4.3.3-20220423
compile time(5641e0a):May 20 2022 11:13:44
Bin version:2.4.0(MINI-1)

OK
```

### Nucleo-F412ZG Pinout Reference
![](.assets/pinout_CN8_CN9.png)

![](.assets/pinout_CN7_CN10.png)