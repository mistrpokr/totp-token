#include "esp_at.h"

extern char* esp_read_buf;

void
at_rst()
{
  util_esp_send("at+rst");
}

void
at_gmr()
{
  util_esp_send("at+gmr");

  esp_read_buf = util_esp_read_to_end();
  util_usart_printf("GOT OK\n");
}