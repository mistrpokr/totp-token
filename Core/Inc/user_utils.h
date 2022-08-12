#ifndef USER_UTILS_H
#define USER_UTILS_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_uart.h"
#include <stdio.h>
#include <string.h>

#include "esp_at.h"
#include "fonts.h"
#include "gfx.h"
#include "st7735s.h"

#define util_usart_printf printf

typedef enum AT_RES_ENUM
{
  AT_OK = 0,
  AT_ERROR = 1,
  AT_READY = 2,
} AT_RES;

extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart2;

void
util_usart_printstr(char* str);
void
util_usart_readline(char* str);
void
util_esp_send(char* str);
void
util_esp_send_raw(char* str);
char*
util_esp_read_to_end(AT_RES res);
int
util_str_check_startswith(char* str, char* key, int key_size);
int
util_str_ends_with(char* str, int str_size, char* pattern, int pattern_size);
void
util_display_init();
void
util_display_totp(int totp, int time);
void
util_display_example(void);

#endif