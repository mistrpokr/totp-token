#include "data_persist.h"
#include "eeprom.h"

#define VIRT_ADDR_OFFSET 0x5000
#define INDEX_VAR_VIRT_ADDR 0xfff0

#define upper_16(x) ((x & 0xff00) >> 8)
#define lower_16(x) (x & 0x00ff)
#define merge_8_to_16(upper, lower) ((upper << 8) + lower)

/* Virtual address defined by the user: 0xFFFF value is prohibited */
/* Note:
 * 1. Virtual address is actually a "tag" to identify data segments.
 * 2. Virtual addresses must be pre-allocated before all write/read operations,
 * since in the power failure recovery process (in EE_Init) the virtual
 * addresses defined in VirtAddVarTab will be used to identify saved data
 * segments in flash.
 */
uint16_t VirtAddVarTab[NB_OF_VAR] = {};
uint16_t VarDataTab[NB_OF_VAR] = {};
uint16_t VarValue, VarDataTmp = 0;

uint16_t test_addr = 0xfff0;
uint16_t test_value = 0x0102;
uint16_t test_tmp = 0U;

int service_stored = 0; // Number of services stored in EEPROM

int
eeprom_store_key(totp_service* service)
{
  HAL_FLASH_Unlock();
  /* EEPROM Init */
  if (EE_Init() != EE_OK) {
    Error_Handler();
  }

  /* Current service name/key size limit is 16 bytes / 8 halfwords */
  HAL_StatusTypeDef res = HAL_OK;

  printf("Storing service: %s, %s\n", service->name, service->key);
  for (int i = 0; i < 8; i++) {
    if (EE_WriteVariable(VIRT_ADDR_OFFSET + service_stored * 16 + i,
                         merge_8_to_16(service->name[i * 2 + 0],
                                       service->name[i * 2 + 1])) != HAL_OK ||
        EE_WriteVariable(VIRT_ADDR_OFFSET + service_stored * 16 + 8 + i,
                         merge_8_to_16(service->key[i * 2 + 0],
                                       service->key[i * 2 + 1])) != HAL_OK) {
      printf("Store key error! \n");
      for (;;)
        ;
    }

    printf("Written to 0x%x and 0x%x\n",
           VIRT_ADDR_OFFSET + service_stored * 16 + i,
           VIRT_ADDR_OFFSET + service_stored * 16 + 8 + i);
  }
  service_stored++;

  HAL_FLASH_Lock();
}

int
eeprom_read_key(totp_service* service_restored)
{
  HAL_FLASH_Unlock();
  /* EEPROM Init */
  if (EE_Init() != EE_OK) {
    Error_Handler();
  }

  uint16_t name_tmp = 0;
  uint16_t key_tmp = 0;
  char upper = 0, lower = 0;

  HAL_StatusTypeDef res = HAL_OK;
  for (int idx = 0; idx < service_stored; idx++) {
    for (int i = 0; i < 8; i++) {
      if (EE_ReadVariable(VIRT_ADDR_OFFSET + idx * 16 + i, &name_tmp) !=
            HAL_OK ||
          EE_ReadVariable(VIRT_ADDR_OFFSET + idx * 16 + 8 + i, &key_tmp) !=
            HAL_OK) {
        printf("Read key error! \n");
      }
      printf("Read from 0x%x and 0x%x\n",
             VIRT_ADDR_OFFSET + idx * 16 + i,
             VIRT_ADDR_OFFSET + idx * 16 + 8 + i);

      service_restored->name[i * 2] = upper_16(name_tmp);
      service_restored->name[i * 2 + 1] = lower_16(name_tmp);
      service_restored->key[i * 2] = upper_16(key_tmp);
      service_restored->key[i * 2 + 1] = lower_16(key_tmp);
    }
    printf("Recovered service: %s, %s\n",
           service_restored->name,
           service_restored->key);
  }

  HAL_FLASH_Lock();
}

int
eeprom_data_init()
{
  uint16_t alloc_addr = 0x00;
  for (int i = 0; i < NB_OF_VAR - 1; i++) {
    VirtAddVarTab[i] = alloc_addr;
    alloc_addr += 0x0010;
  }
  /* Finally, format the index variable */
  VirtAddVarTab[NB_OF_VAR - 1] = INDEX_VAR_VIRT_ADDR;

  for (int i = 0; i < NB_OF_VAR; i++) {
    printf("Allocated Virt Addr: ");
    printf("0x%x, ", VirtAddVarTab[i]);
    printf("\n");
  }

  HAL_FLASH_Unlock();

  /* EEPROM Init */
  if (EE_Init() != EE_OK) {
    Error_Handler();
  }

  HAL_FLASH_Lock();
}

int
eeprom_test()
{
  HAL_FLASH_Unlock();
  /* EEPROM Init */
  if (EE_Init() != EE_OK) {
    Error_Handler();
  }

  if ((EE_ReadVariable(test_addr, &test_tmp)) != HAL_OK) {
    printf("Didn't find valid data at virtual EEPROM address 0x%x\n",
           test_addr);
  } else {
    printf("0xffff = 0x%x, Expected 0x%x\n", test_tmp, test_value);
  }

  if ((EE_WriteVariable(test_addr, test_value)) != HAL_OK) {
    printf("Write failed! \n");
  }

  if ((EE_ReadVariable(test_addr, &test_tmp)) != HAL_OK) {
    printf("Failed to read 0x%x\n", test_addr);
  } else {
    printf("0xffff = 0x%x, Expected 0x%x\n", test_tmp, test_value);
  }

  HAL_FLASH_Lock();
}
