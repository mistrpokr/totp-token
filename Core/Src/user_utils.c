#include "user_utils.h"

#define BUFFER_SIZE 32

void util_usart_print(char *str) {
  HAL_UART_Transmit(&huart3, str, strlen((char *)str), HAL_MAX_DELAY);
}

void hash_print(byte *hash, int hash_size) {
  char hex_repr[2] = ""; // 1 Byte -> 2-char hexadecimal representation
  util_usart_print("\n");
  for (int i = 0; i < hash_size; i++) {
    if (sprintf(hex_repr, "%02x", hash[i]) >= 0) // If sprintf doesn't fail
      util_usart_print(hex_repr);
  }
}

void hash_md5(char *in, int size) {
  byte md5sum[MD5_DIGEST_SIZE];

  wc_Md5Hash((byte *)in, (word32)size, md5sum);
  hash_print(md5sum, sizeof(md5sum));
}

void hash_sha256(char *in, int size) {
  byte sha256sum[SHA256_DIGEST_SIZE];

  wc_Sha256Hash((byte *)in, (word32)size, sha256sum);
  hash_print(sha256sum, sizeof(sha256sum));
}