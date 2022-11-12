#ifndef USER_UTILS_H
#define USER_UTILS_H

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_uart.h"
#include <stdio.h>
#include <string.h>

#include "circular_buffer.h"
#include "crypt.h"
#include "fonts.h"
#include "gfx.h"
#include "st7735s.h"

/* Data must be flushed with LF(\n) to be actually printed to stdout(serial)! */
#define util_usart_printf printf

#define SERVICE_DISP_LEN 24

typedef enum AT_RES_ENUM
{
  AT_OK = 0,
  AT_ERROR = 1,
  AT_READY = 2,
} AT_RES;

typedef struct totp_service_t
{
  char name[16];
  char key[16];
} totp_service;

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
util_str_ends_with(char* str, char* pattern);
int
util_str_starts_with(char* str, char* pattern);
void
util_display_init();
void
util_display_totp(int totp, int time, long epoch);
void
util_display_totp_multi(totp_service* service_list, int count);
void
util_display_example(void);
void
util_parse_conf(char* raw, int str_len);
void
util_parse_segment(char* raw, int start, int end);
int
util_totp_from_service(totp_service* service);
#endif