#include "crypt.h"

const char* HMAC_DEFAULT_KEY = "hello";

void
hash_print(byte* hash, int hash_size)
{
  char hex_repr[2] = ""; // 1 Byte -> 2-char hexadecimal representation
  for (int i = 0; i < hash_size; i++) {
    if (sprintf(hex_repr, "%02x", hash[i]) >= 0) // If sprintf doesn't fail
      util_usart_printstr(hex_repr);
  }
}

int
hash_print_str(byte* hash, int hash_size, char* str)
{
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

int
hash_md5(char* in, int in_size, byte* out, int out_size)
{
  if (out_size != MD5_DIGEST_SIZE) {
    return -1; // Digest buffer size mismatch
  }
  wc_Md5Hash((byte*)in, (word32)in_size, out);
}

int
hash_sha256(char* in, int in_size, byte* out, int out_size)
{
  if (out_size != SHA256_DIGEST_SIZE) {
    return -1; // Digest buffer size mismatch
  }
  wc_Sha256Hash((byte*)in, (word32)in_size, out);
}

int
hash_hmac256(char* in,
             int in_size,
             char* key,
             int key_size,
             byte* out,
             int out_size)
{
  if (out_size != SHA256_DIGEST_SIZE) {
    return -1;
  }

  Hmac hmac;
  if (wc_HmacSetKey(&hmac, WC_HASH_TYPE_SHA256, key, key_size) != 0) {
    return -1; // Error initializing Hmac
  }
  if (wc_HmacUpdate(&hmac, in, in_size) != 0) {
    return -1; // Error updating Hmac
  }
  if (wc_HmacFinal(&hmac, out) != 0) {
    return -1; // Error computing Hmac hash}
  }
}
int
hash_hmac1(char* in,
           int in_size,
           char* key,
           int key_size,
           byte* out,
           int out_size)
{
  if (out_size != SHA_DIGEST_SIZE) {
    return -1;
  }

  Hmac hmac;
  if (wc_HmacSetKey(&hmac, WC_HASH_TYPE_SHA, key, key_size) != 0) {
    return -1; // Error initializing Hmac
  }
  if (wc_HmacUpdate(&hmac, in, in_size) != 0) {
    return -1; // Error updating Hmac
  }
  if (wc_HmacFinal(&hmac, out) != 0) {
    return -1; // Error computing Hmac hash}
  }
}

int
hash_hotp_sha1(char* hmac_result, int hmac_digest_size, int digits)
{
  /* Step 1: Retrieve offset */
  int offset = hmac_result[hmac_digest_size - 1] & 0xf;
  /* Step 2: Truncate 31 bits from digest[offset...offset+3] */
  int bin_code = (hmac_result[offset] & 0x7f) << 24 | // MSB is dropped
                 (hmac_result[offset + 1] & 0xff) << 16 |
                 (hmac_result[offset + 2] & 0xff) << 8 |
                 (hmac_result[offset + 3] & 0xff);
  /* Step 3: Result = P Mod 10^digits */
  int hotp_res = bin_code % ((int)pow(10, digits));

  return hotp_res;
}

int
hash_totp_sha1(int time)
{
  /* Floor based on time step, e.g. 51 secs => 1 step * 30 secs */
  /* TODO: Inspect floor()'s performance on MCUs, can be substituted with
   * non-floating point number operation */
  int64_t steps = (int)floor(time / TIME_STEP);
  printf("%d\n", (int)steps);

  byte hmac_result[SHA_DIGEST_SIZE] = "";

  /* Convert steps (int64, 64 bits) to byte (8 bits) array with a length of 8 */
  byte steps_in_bytes[8];
  for (int i = 0; i < 8; i++) {
    steps_in_bytes[7 - i] = ((steps >> 8 * i) & 0xff);
  }

  hash_hmac1(steps_in_bytes,
             8,
             HMAC_DEFAULT_KEY,
             strlen(HMAC_DEFAULT_KEY),
             hmac_result,
             SHA_DIGEST_SIZE);
  // hash_print(hmac_result, SHA_DIGEST_SIZE);

  return hash_hotp_sha1(hmac_result, SHA_DIGEST_SIZE, TOTP_DIGITS);
}