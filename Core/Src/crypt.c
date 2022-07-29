#include "crypt.h"

byte md5sum[MD5_DIGEST_SIZE];
byte sha256sum[SHA256_DIGEST_SIZE];
byte hmac256sum[SHA256_DIGEST_SIZE];

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
  // byte hmac_result[] = { 0x1f, 0x86, 0x98, 0x69, 0x0e, 0x02, 0xca,
  //                        0x16, 0x61, 0x85, 0x50, 0xef, 0x7f, 0x19,
  //                        0xda, 0x8e, 0x94, 0x5b, 0x55, 0x5a };
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