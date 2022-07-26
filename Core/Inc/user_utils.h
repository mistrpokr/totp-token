#ifndef USER_UTILS_H
#define USER_UTILS_h

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_uart.h"
#include <stdio.h>
#include <string.h>

#include <wolfssl/wolfcrypt/md5.h>
// #include <wolfssl/wolfcrypt/sha256.h>
#include <wolfssl/wolfcrypt/hash.h>

#define util_usart_printf printf

extern UART_HandleTypeDef huart3;

void util_usart_printstr(char *str);
void util_usart_readline(char *str);
void hash_print(byte *hash, int hash_size);
void hash_md5(char *in, int size);
int hash_sha256(char *in, int size, byte *out, int out_size);

#endif