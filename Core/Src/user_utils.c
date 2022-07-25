#include "user_utils.h"

byte md5sum[MD5_DIGEST_SIZE];
byte buffer[32];
/*fill buffer with data to hash*/

Md5 md5;

void util_usart_print(char *str) {
  HAL_UART_Transmit(&huart3, str, strlen((char *)str), HAL_MAX_DELAY);
}

void hash_md5(int rep) {
  for (int i = 0; i < 32; i++) {
    buffer[i] = (unsigned char)'a';
  }

  wc_InitMd5(&md5);
  while (rep--) {
    wc_Md5Update(&md5, buffer,
                 sizeof(buffer)); /*can be called again and again*/
  }

  wc_Md5Final(&md5, md5sum);

  // char *hash_repr = "";
  // sprintf(hash_repr, "%s", (char *)md5sum);
  // util_usart_print(hash_repr);

  char hex_repr[2] = "";
  for (int i = 0; i < MD5_DIGEST_SIZE; i++) {
    int ret = sprintf(hex_repr, "%02x", md5sum[i]);
    if (ret >= 0)
      util_usart_print(hex_repr);
  }
}