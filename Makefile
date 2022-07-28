##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [3.17.1] date: [Wed Jul 27 23:48:47 CST 2022] 
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = f412_exp


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Core/Src/syscalls.c \
Core/Src/main.c \
Core/Src/user_utils.c \
Core/Src/crypt.c \
Core/Src/stm32f4xx_it.c \
Core/Src/stm32f4xx_hal_msp.c \
Core/Src/stm32f4xx_hal_timebase_tim.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
Core/Src/system_stm32f4xx.c \
Core/Src/freertos.c \
Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
Middlewares/Third_Party/FreeRTOS/Source/list.c \
Middlewares/Third_Party/FreeRTOS/Source/queue.c \
Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c \
Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
Middlewares/Third_Party/FreeRTOS/Source/timers.c \
Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/crl.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/internal.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/keys.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ocsp.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/sniffer.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/ssl.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/tls.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/tls13.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/src/wolfio.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/IDE/STM32Cube/wolfssl_example.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/test/test.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/benchmark/benchmark.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/aes.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/arc4.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/asm.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/asn.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/blake2b.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/blake2s.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/camellia.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/chacha.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/chacha20_poly1305.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/cmac.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/coding.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/compress.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/cpuid.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/curve448.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/curve25519.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/des3.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/dh.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/dsa.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/ecc_fp.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/ecc.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/eccsi.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/ed448.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/ed25519.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/error.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/fe_448.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/fe_low_mem.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/fe_operations.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/ge_448.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/ge_low_mem.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/ge_operations.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/hash.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/hc128.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/hmac.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/integer.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/logging.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/md2.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/md4.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/md5.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/memory.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/pkcs7.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/pkcs12.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/poly1305.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/pwdbased.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/rabbit.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/random.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/rc2.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/ripemd.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/rsa.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/sakke.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/sha.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/sha256.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/sha3.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/sha512.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/signature.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/sp_arm32.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/sp_arm64.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/sp_armthumb.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/sp_c32.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/sp_c64.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/sp_cortexm.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/sp_dsp32.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/sp_int.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/sp_x86_64.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/srp.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/tfm.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/wc_dsp.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/wc_encrypt.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/wc_pkcs11.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/wc_port.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/wolfevent.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/wolfmath.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/port/arm/armv8-32-curve25519.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/port/arm/armv8-32-sha512-asm.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/port/arm/armv8-aes.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/port/arm/armv8-chacha.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/port/arm/armv8-curve25519.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/port/arm/armv8-poly1305.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/port/arm/armv8-sha256.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/port/arm/armv8-sha512.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/port/atmel/atmel.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/port/st/stm32.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/port/st/stsafe.c \
Middlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/wolfcrypt/src/port/nrf51.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rng.c

# ASM sources
ASM_SOURCES =  \
startup_stm32f412zx.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F412Zx


# AS includes
AS_INCLUDES =  \
-ICore/Inc

# C includes
C_INCLUDES =  \
-ICore/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc \
-IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy \
-IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
-IDrivers/CMSIS/Include \
-IMiddlewares/Third_Party/FreeRTOS/Source/include \
-IMiddlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 \
-IMiddlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F \
-IwolfSSL \
-IMiddlewares/Third_Party/wolfSSL_wolfSSL_wolfSSL/wolfssl/


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -std=c99

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F412ZGTx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
