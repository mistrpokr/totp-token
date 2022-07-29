#include <math.h>
#include <stdio.h>

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_uart.h"

#include <wolfssl/wolfcrypt/hash.h>
#include <wolfssl/wolfcrypt/hmac.h>
#include <wolfssl/wolfcrypt/md5.h>

#define HMAC_DEFAULT_KEY "hello"
#define TIME_STEP 30
#define TOTP_DIGITS 6

void
hash_print(byte* hash, int hash_size);
int
hash_print_str(byte* hash, int hash_size, char* str);
int
hash_md5(char* in, int in_size, byte* out, int out_size);
int
hash_sha256(char* in, int in_size, byte* out, int out_size);
int
hash_hmac256(char* in,
             int in_size,
             char* key,
             int key_size,
             byte* out,
             int out_size);
int
hash_hmac1(char* in,
           int in_size,
           char* key,
           int key_size,
           byte* out,
           int out_size);

int
hash_hotp_sha1(char* hmac_result, int hmac_digest_size, int digits);

int
hash_totp_sha1(int time);