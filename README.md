# Experimenting with STM32 Nucleo F412 Development Board
---

## Interfacing with ESP32 (AT Firmware)
### Hardware Connection
STM32 communicates with ESP32 over its USART2 interface. USART2, as of the time this document is written, uses the GPIOs PA2/3. 

![](.assets/Screenshot_20220728_135106.png)

| STM32                   | Opt.1: ESP32 | Opt.2: USB-TTL (PC) |
| ----------------------- | ------------ | ------------------- |
| CN9 - A0(RX, PA3)       | D7(USART1TX) | TX                  |
| CN10 - ADC1/2 (TX, PA2) | D6(USART1RX) | RX                  |

### Samples
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

### Notes

- ESP32 echoes serial input. 
- AT command responses end with CR+LF. 

---
## Pinout Reference
![](.assets/pinout_CN8_CN9.png)

![](.assets/pinout_CN7_CN10.png)