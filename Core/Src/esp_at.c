#include "esp_at.h"

extern char* esp_read_buf;

void
at()
{
  util_esp_send("at");
  esp_read_buf = util_esp_read_to_end(AT_OK);
  util_usart_printf("[ESP32]%s\n", esp_read_buf);
}

void
at_rst()
{
  util_esp_send("at+rst");
  esp_read_buf = util_esp_read_to_end(AT_READY);
  util_usart_printf("[ESP32]%s\n", esp_read_buf);
}

void
at_gmr()
{
  util_esp_send("at+gmr");
  esp_read_buf = util_esp_read_to_end(AT_OK);
  util_usart_printf("[ESP32]%s\n", esp_read_buf);
}