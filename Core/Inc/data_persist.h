#include "main.h"
#include <stdio.h>

int
eeprom_store_key(totp_service* service);

int
eeprom_read_key(totp_service* service);

int
eeprom_data_init();

int
eeprom_test();
