#include "user_utils.h"

void util_usart_print(char *str) {
  HAL_UART_Transmit(&huart3, str, strlen((char *)str), HAL_MAX_DELAY);
}
