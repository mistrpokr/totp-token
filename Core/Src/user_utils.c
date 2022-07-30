#include "user_utils.h"
#include "esp_at.h"

#define LINE_BUFFER_SIZE 1024
#define ESP_BUFFER_SIZE 1024

#define STR_ENDS_WITH_OK_CRLF(str)                                             \
  util_str_ends_with(str, strlen(str), "OK\r\n", strlen("OK\r\n"))

#define STR_ENDS_WITH_ERROR_CRLF(str)                                          \
  util_str_ends_with(str, strlen(str), "ERROR\r\n", strlen("ERROR\r\n"))

#define STR_ENDS_WITH_READY_CRLF(str)                                          \
  util_str_ends_with(str, strlen(str), "ready\r\n", strlen("ready\r\n"))

char uart_line_buffer[LINE_BUFFER_SIZE] = "";
char uart_esp_1char_buffer[1] = "";
char uart_esp_stream_buffer[ESP_BUFFER_SIZE] = "";
int uart_esp_stream_ptr = 0;
char* esp_read_buf; // Pointer to buffer returned by util_esp_read*

const char crlf[] = "\r\n";

void
HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
  /* UART Rx Complete Callback */
  if (huart == &huart2) {
    uart_esp_stream_buffer[uart_esp_stream_ptr++] = *uart_esp_1char_buffer;

    // /* Debug hook */
    // if (uart_esp_stream_buffer[uart_esp_stream_ptr - 1] == '\n') {
    //   if (uart_esp_stream_buffer[uart_esp_stream_ptr - 2] == '\r') {
    //     if (uart_esp_stream_buffer[uart_esp_stream_ptr - 3] == 'K') {
    //       __NOP();
    //     }
    //   }
    // }
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
  HAL_UART_Transmit(&huart2, crlf, strlen((char*)crlf), HAL_MAX_DELAY);
}

void
util_esp_send_raw(char* str)
{
  HAL_UART_Transmit(&huart2, str, strlen((char*)str), HAL_MAX_DELAY);
}

char*
util_esp_read_to_end(AT_RES res)
{
  /* Invalidate buffer */
  for (int i = 0; i < uart_esp_stream_ptr; i++) {
    uart_esp_stream_buffer[i] = '\0';
  }
  uart_esp_stream_ptr = 0;

  /* Start receiving 1 byte */
  if (HAL_UART_Receive_IT(&huart2, uart_esp_1char_buffer, 1) != HAL_OK) {
    printf("UART2 RX ERROR\n");
    for (;;)
      ;
  }

  while ((res == AT_OK
            ? STR_ENDS_WITH_OK_CRLF(uart_esp_stream_buffer)
            : (res == AT_ERROR
                 ? STR_ENDS_WITH_ERROR_CRLF(uart_esp_stream_buffer)
                 : STR_ENDS_WITH_READY_CRLF(uart_esp_stream_buffer))) != 0) {
    __NOP();
  }
  /* Got what we need, stop receiving with interrupt */
  HAL_UART_AbortReceive_IT(&huart2);
  /* Reset character buffer */
  *uart_esp_1char_buffer = '\0';
  /* Zero-terminate line buffer string */
  uart_esp_stream_buffer[uart_esp_stream_ptr - 2] = '\0';

  return uart_esp_stream_buffer;
}

int
util_str_ends_with(char* str, int str_size, char* pattern, int pattern_size)
{
  /* e.g. Look for "OK\r\n" */
  for (int i = 0; i < pattern_size; i++) {
    if (str[str_size - i] != pattern[pattern_size - i]) {
      return -1;
    }
  }
  return 0;
}

void
util_display_init()
{
  /* Init driver struct */
  ST7735S_Init();
  setOrientation(R270);

  /* Clear buffer with white background */
  setColor(0, 0, 0);
  fillScreen();

  /* Flush buffer to display */
  flushBuffer();
}

void
util_display_totp(int totp)
{
  char totp_text[6] = "";
  sprintf(totp_text, "%d", totp);

  setColor(255, 255, 255);
  setFont(ter_u24b);
  drawText(40, 70, totp_text);

  flushBuffer();
}

void
util_display_example(void)
{
  ST7735S_Init();
  setOrientation(R180);

  uint8_t f = 0;

  setColor(0, 0, 0);
  fillScreen();
  setColor(255, 255, 255);
  drawLine(0, 0, WIDTH, HEIGHT);
  drawLine(WIDTH / 2, 0, WIDTH / 2, HEIGHT);

  setFont(ter_u24b);
  drawText(50, 50, "Hi! ");

  flushBuffer();
  for (;;)
    ;

  while (1) {

    f = 1 - f;
    if (f) {
      setColor(0, 0, 0);
      fillScreen();
    } else {

      uint8_t r = 0, g = 0, b = 0;
      for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++) {
          setColor(r, g, b);
          setPixel(x, y);
          r = x % 32;
          g = (x + y) % 64;
          b = y % 32;
        }
    }

    for (int i = 0; i < 32; i++) {
      setColor(i, i, i);
      drawLine(0, i, WIDTH - 1, i);
    }
    setColor(31, 63, 31);
    setbgColor(0, 0, 0);
    setFont(ter_u24b);
    drawText(4, 33, "Hi World!");
    for (int i = 0; i < 64; i++) {
      setColor(i / 2, 63 - i, i / 2);
      drawLine(WIDTH - 1 - i, 0, WIDTH - 1 - i, HEIGHT - 1);
    }
    for (int i = 0; i < 64; i++) {
      setColor(i / 2, i, i / 2);
      drawLine(0, HEIGHT - 1 - i, WIDTH - 1, HEIGHT - 1 - i);
    }

    setColor(10, 20, 30);
    drawCircle(80, 50, 30);

    setColor(30, 10, 30);
    drawCircle(40, 10, 90);

    setColor(30, 0, 30);
    drawLine(0, 0, WIDTH - 1, HEIGHT - 1);

    flushBuffer();
  }
}
