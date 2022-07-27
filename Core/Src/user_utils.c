#include "user_utils.h"

#define BUFFER_SIZE 32

void util_usart_printstr(char *str) {
  HAL_UART_Transmit(&huart3, str, strlen((char *)str), HAL_MAX_DELAY);
}

void util_usart_readline(char *str) {
  int p = 0;
  char buf[1] = {'\0'};

  *str = '\0';
  *(str + 1) = '\0';
  while (*buf != '\n' && *buf != '\r') {
    int res = HAL_UART_Receive(&huart3, buf, 1, HAL_MAX_DELAY);

    str[p++] = *buf;
    HAL_UART_Transmit(&huart3, buf, 1, HAL_MAX_DELAY);
  }

  str[p - 1] = '\0'; // Remove CR/LF
}
