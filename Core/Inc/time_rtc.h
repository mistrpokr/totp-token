#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_rtc.h"
#include <time.h>

time_t
time_from_rtc(RTC_TimeTypeDef rtc_time, RTC_DateTypeDef rtc_date);