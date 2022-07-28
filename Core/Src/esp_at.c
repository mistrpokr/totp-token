#include "esp_at.h"

extern char* line_buf;

void
at_rst()
{
  util_esp_send("at+rst");
}

void
at_gmr()
{
  util_esp_send("at+gmr");

  while (strstr(line_buf, "OK") == NULL) {
    line_buf = util_esp_readline();
  }
  util_usart_printf("GOT OK\n");
}