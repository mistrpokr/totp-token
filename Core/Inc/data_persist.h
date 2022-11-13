#include "eeprom.h"
#include "main.h"
#include <stdio.h>

/**
 * @brief Store service struct data to emulated EEPROM
 *
 * @param service
 * @return int
 */
int
eeprom_store_service(totp_service* service);

/**
 * @brief Read service struct data from emulated EEPROM.
 *
 * @param service_restored
 * @return int
 */
int
eeprom_read_service(totp_service* service_restored);

int
eeprom_data_init();

int
eeprom_test();
