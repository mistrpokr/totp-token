#ifndef USER_UTILS_H
#define USER_UTILS_h

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_uart.h"
#include <stdio.h>
#include <string.h>

#define util_usart_printf printf

extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart2;

void
util_usart_printstr(char* str);
void
util_usart_readline(char* str);
void
util_esp_send(char* str);
char*
util_esp_readline();
int
util_str_check_startswith(char* str, char* key, int key_size);

#endif