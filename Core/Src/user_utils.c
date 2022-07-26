#include "user_utils.h"

#define BUFFER_SIZE 32

void util_usart_printstr(char *str) {
  HAL_UART_Transmit(&huart3, str, strlen((char *)str), HAL_MAX_DELAY);
}

void util_usart_readline(char *str) {
  int p = 0;
  char buf[1] = {'\0'};

  while (*buf != '\n' && *buf != '\r') {
    int res = HAL_UART_Receive(&huart3, buf, 1, HAL_MAX_DELAY);

    str[p++] = *buf;
    HAL_UART_Transmit(&huart3, buf, 1, HAL_MAX_DELAY);
  }

  str[p + 1] = '\0';
}

void hash_print(byte *hash, int hash_size) {
  char hex_repr[2] = ""; // 1 Byte -> 2-char hexadecimal representation
  for (int i = 0; i < hash_size; i++) {
    if (sprintf(hex_repr, "%02x", hash[i]) >= 0) // If sprintf doesn't fail
      util_usart_printstr(hex_repr);
  }
}

int hash_print_str(byte *hash, int hash_size, char *str) {
  char hex_repr[2] = "";
  for (int i = 0; i < hash_size; i++) {
    if (sprintf(hex_repr, "%02x", hash[i]) < 0) {
      return -1;
    }
    str[i + 0] = hex_repr[0];
    str[i + 1] = hex_repr[1];
  }
  return 0;
}

void hash_md5(char *in, int size) {
  byte md5sum[MD5_DIGEST_SIZE];

  wc_Md5Hash((byte *)in, (word32)size, md5sum);
  hash_print(md5sum, sizeof(md5sum));
}

int hash_sha256(char *in, int in_size, byte *out, int out_size) {
  if (out_size != SHA256_DIGEST_SIZE) {
    return -1; // Digest buffer size mismatch
  }
  wc_Sha256Hash((byte *)in, (word32)in_size, out);
}