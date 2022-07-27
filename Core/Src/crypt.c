#include "crypt.h"

void hash_print(byte *hash, int hash_size) {
  char hex_repr[2] = ""; // 1 Byte -> 2-char hexadecimal representation
  for (int i = 0; i < hash_size; i++) {
    if (sprintf(hex_repr, "%02x", hash[i]) >= 0) // If sprintf doesn't fail
      util_usart_printstr(hex_repr);
  }
}

int hash_print_str(byte *hash, int hash_size, char *str) {
  char hex_repr[2] = "";
  int i = 0;
  for (i = 0; i < hash_size; i++) {
    if (sprintf(hex_repr, "%02x", hash[i]) < 0) {
      return -1;
    }
    str[2 * i + 0] = hex_repr[0];
    str[2 * i + 1] = hex_repr[1];
  }
  str[2 * i] = '\0';
  return 0;
}

void hash_md5(char *in, int in_size, byte *out, int out_size) {
  if (out_size != MD5_DIGEST_SIZE) {
    return -1; // Digest buffer size mismatch
  }
  wc_Md5Hash((byte *)in, (word32)in_size, out);
}

int hash_sha256(char *in, int in_size, byte *out, int out_size) {
  if (out_size != SHA256_DIGEST_SIZE) {
    return -1; // Digest buffer size mismatch
  }
  wc_Sha256Hash((byte *)in, (word32)in_size, out);
}