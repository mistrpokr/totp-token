#include "user_utils.h"

#define LINE_BUFFER_SIZE 1024

int total_received_lines = 0;

char uart_esp_1char_buffer[1] = "";
char uart_esp_line_buffer[LINE_BUFFER_SIZE] = "";
int uart_esp_line_ptr = 0;

char str_response[] = "\nGot";
char str_crlf[] = "\r\n";

char* line_buf; // Pointer to buffer returned by util_esp_readline

void
HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
  /* UART Rx Complete Callback */
  if (huart == &huart2) {
    /* Drop CR and accept LF as the only EOL, as terminals might send different
     * EOL symbols */
    if (*uart_esp_1char_buffer != '\r') {
      uart_esp_line_buffer[uart_esp_line_ptr++] = *uart_esp_1char_buffer;
    }

    /* Receive next character */
    HAL_UART_Receive_IT(huart, uart_esp_1char_buffer, 1);
  }
}

void
util_usart_printstr(char* str)
{
  HAL_UART_Transmit(&huart3, str, strlen((char*)str), HAL_MAX_DELAY);
}

void
util_usart_readline(char* str)
{
  int p = 0;
  char buf[1] = { '\0' };

  *str = '\0';
  *(str + 1) = '\0';
  while (*buf != '\n' && *buf != '\r') {
    int res = HAL_UART_Receive(&huart3, buf, 1, HAL_MAX_DELAY);

    str[p++] = *buf;
    HAL_UART_Transmit(&huart3, buf, 1, HAL_MAX_DELAY);
  }

  str[p - 1] = '\0'; // Remove CR/LF
}

void
util_esp_send(char* str)
{
  HAL_UART_Transmit(&huart2, str, strlen((char*)str), HAL_MAX_DELAY);
  HAL_UART_Transmit(&huart2, str_crlf, strlen((char*)str_crlf), HAL_MAX_DELAY);
}

void
util_esp_send_raw(char* str)
{
  HAL_UART_Transmit(&huart2, str, strlen((char*)str), HAL_MAX_DELAY);
}

char*
util_esp_readline()
{
  /* Start receiving 1 byte */
  HAL_UART_Receive_IT(&huart2, uart_esp_1char_buffer, 1);

  while (*uart_esp_1char_buffer != '\n') {
    __NOP();
  }
  *uart_esp_1char_buffer = '\0';

  /* Remove LF character, zero-terminate line buffer string and reset pointer */
  uart_esp_line_buffer[uart_esp_line_ptr - 1] = '\0';
  uart_esp_line_ptr = 0;

  // printf("LINE#%d\n", total_received_lines++);
  return uart_esp_line_buffer;
}

int
util_str_check_startswith(char* str, char* key, int key_size)
{
  for (int i = 0; i < key_size; i++) {
    if (str[i] != key[i]) {
      /* Negative */
      return -1;
    }
  }

  /* Positive */
  return 0;
}