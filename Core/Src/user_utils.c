#include "user_utils.h"

#define LINE_BUFFER_SIZE 1024
#define ESP_BUFFER_SIZE 1024

#define STR_ENDS_WITH_OK_CRLF(str) util_str_ends_with(str, "OK\r\n")
#define STR_ENDS_WITH_ERROR_CRLF(str) util_str_ends_with(str, "ERROR\r\n")
#define STR_ENDS_WITH_READY_CRLF(str) util_str_ends_with(str, "ready\r\n")

char uart_line_buffer[LINE_BUFFER_SIZE] = "";
char uart_1char_buffer[1] = "";
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
  } else if (huart == &huart3) {
    cb_put(&uart_c_buffer, 1, uart_1char_buffer);
    HAL_UART_Receive_IT(huart, uart_1char_buffer, 1);
  }
}

void
util_usart_printstr(char* str)
{
  HAL_UART_Transmit_IT(&huart3, str, strlen((char*)str));
}

void
util_usart_readline(char* str)
{
  HAL_UART_Receive_IT(&huart3, uart_1char_buffer, 1);

  while (!(cb_empty(&uart_c_buffer) != 1 &&
           (cb_read(&uart_c_buffer, uart_c_buffer.tail - 1) == '\n' ||
            cb_read(&uart_c_buffer, uart_c_buffer.tail - 1) == '\r'))) {
    /* Wait until: circular buffer ends with a EOL character AND buffer is not
     * empty */
  }

  int len = cb_len(&uart_c_buffer);
  cb_get(&uart_c_buffer, len, str);
  str[len] = '\0';
  util_usart_printf("%s\n", str);
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
util_str_ends_with(char* str, char* pattern)
{
  /* e.g. Look for "OK\r\n"
   * Reference:
   * https://stackoverflow.com/questions/4770985/how-to-check-if-a-string-starts-with-another-string-in-c
   */
  return strcmp(str + strlen(pattern) - 1, pattern) == 0 ? 0 : -1;
  // Truncate & align to last characters
}

int
util_str_starts_with(char* str, char* pattern)
{
  return strncmp(str, pattern, strlen(pattern)) == 0 ? 0 : -1;
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
util_display_totp(int totp, int time, long epoch)
{
  char totp_text[6] = "";
  /* Pad 0 if only 5-digit */
  sprintf(totp_text, (totp < 100000 ? "0%d" : "%d"), totp);

  /* Draw countdown bar */
  // TODO Fill bar only on 30s cycle reset, skip this expensive operation during
  // cycles
  setColor(0, 255, 0);
  filledRect(19, 100, 19 + 90 - time * (90 / 30), 110);
  /* Drawing another rectangle to truncate bar on the right end */
  setColor(0, 0, 0);
  filledRect(19 + 90 - time * (90 / 30), 100, 19 + 90, 110);

  setColor(255, 255, 255);
  setFont(ter_u24b);
  drawText(30, 70, totp_text);

  setFont(ter_u12b);
  char time_text[32] = "";
  sprintf(time_text, "%lu", epoch);
  drawText(40, 20, time_text);

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

void
util_parse_conf(char* raw, int str_len)
{
  // ?time=1034134&service=github,1431jck3&service=weibo,jk13k4k;
  int p = 0;
  int last = 0;
  while (raw[p++] != ';') {
    if (raw[p] == '&') {
      util_parse_segment(raw, last, p - 1);
      last = p + 1;
    }
  }
  util_parse_segment(raw, last, p - 2);
};

void
util_parse_segment(char* raw, int start, int end)
{
  char* segment = raw + start;

  if (util_str_starts_with(segment, "time") == 0) {
    segment[end + 1] = '\0'; // ‘&’ => '\0'
    long epoch = atol(strchr(segment, '=') + 1);
    printf("Epoch=%lu", epoch);
  } else if (util_str_starts_with(segment, "service") == 0) {
    char* split_equal = strchr(segment, '=');
    char* split_comma = strchr(segment, ',');

    totp_service service;
    int name_len = split_comma - split_equal - 1;
    int key_len = (end - start) - (split_comma - (raw + start)) - 1;

    strncpy(service.name, split_equal + 1, name_len);
    strncpy(service.key, split_comma + 1, key_len);
    service.name[name_len + 1] = '\0';
    service.key[key_len + 1] = '\0';

    printf("Service: %s,%s;", service.name, service.key);
  }

  printf("\n");
}