#include <stdio.h>

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_uart.h"

#include <wolfssl/wolfcrypt/hash.h>
#include <wolfssl/wolfcrypt/hmac.h>
#include <wolfssl/wolfcrypt/md5.h>

void hash_print(byte *hash, int hash_size);
int hash_print_str(byte *hash, int hash_size, char *str);
int hash_md5(char *in, int in_size, byte *out, int out_size);
int hash_sha256(char *in, int in_size, byte *out, int out_size);
int hash_hmac256(char *in, int in_size, char *key, int key_size, byte *out,
                 int out_size);