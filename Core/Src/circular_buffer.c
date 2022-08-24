#include "circular_buffer.h"

circular_buffer uart_c_buffer;

int
cb_init(circular_buffer* cb)
{
  cb->head = 0;
  cb->tail = 0;
}
int
cb_len(circular_buffer* cb)
{
  return cb->tail - cb->head;
}
int
cb_get(circular_buffer* cb, int bytes, uint8_t* dest_addr)
{
  for (int i = 0; i < bytes; i++) {
    if ((cb->head) % CIRCULAR_BUFFER_SIZE == cb->tail % CIRCULAR_BUFFER_SIZE) {
      // Buffer empty
      break;
    }

    *(dest_addr + i) = cb->buffer[(cb->head++) % CIRCULAR_BUFFER_SIZE];
  }
  return 1;
}
int
cb_put(circular_buffer* cb, int bytes, uint8_t* src_addr)
{
  int csize = CIRCULAR_BUFFER_SIZE;
  for (int i = 0; i < bytes; i++) {
    if (((cb->tail + 1) % CIRCULAR_BUFFER_SIZE ==
         cb->head % CIRCULAR_BUFFER_SIZE)) {
      // Buffer full, drop further data
      break;
    }

    cb->buffer[(cb->tail++) % CIRCULAR_BUFFER_SIZE] = *(src_addr + i);
  }
  return 1;
}
