#ifndef USER_UTILS_H
#define USER_UTILS_h

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_uart.h"
#include <string.h>

#include <wolfssl/wolfcrypt/md5.h>

extern UART_HandleTypeDef huart3;

void util_usart_print(char *str);
void hash_md5(int rep);

#endif