#include <stdint.h>

#define CIRCULAR_BUFFER_SIZE 16

/* Circular Buffer
 * Buffer is empty when head == tail
 * 1 element is always left empty: actual_size = total_size - 1
 */
typedef struct circular_buffer_t
{
  uint8_t buffer[CIRCULAR_BUFFER_SIZE];
  int head;
  int tail;
} circular_buffer;

extern circular_buffer uart_c_buffer;

int
cb_init(circular_buffer* cb);
int
cb_len(circular_buffer* cb);
int
cb_get(circular_buffer* cb, int bytes, uint8_t* dest_addr);
int
cb_put(circular_buffer* cb, int bytes, uint8_t* src_addr);