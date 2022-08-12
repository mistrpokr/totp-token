#include "time_rtc.h"

extern RTC_HandleTypeDef hrtc;

time_t
time_from_rtc(RTC_TimeTypeDef rtc_time, RTC_DateTypeDef rtc_date)
{
  struct tm time_tm;
  time_t time_epoch;

  time_tm.tm_hour = rtc_time.Hours;
  time_tm.tm_min = rtc_time.Minutes;
  time_tm.tm_sec = rtc_time.Seconds;

  /* STM32 RTC Year starts from 2000; tm.tm_year starts from 1900;
   * tm.tm_mon ranges from 0 to 11
   */
  time_tm.tm_mday = rtc_date.Date;
  time_tm.tm_mon = rtc_date.Month - 1;
  time_tm.tm_year = rtc_date.Year + (2000 - 1900);

  struct tm* tm_test;
  time_t time_test = 1660303800;
  tm_test = localtime(&time_test);

  time_epoch = mktime(&time_tm);
  // 2022.8.12, Fri, 19:30:00
  return time_epoch;
}

void
rtc_demo()
{
  RTC_TimeTypeDef rtc_time_set;
  rtc_time_set.Hours = 19;
  rtc_time_set.Minutes = 30;
  rtc_time_set.Seconds = 0;
  RTC_DateTypeDef rtc_date_set;
  rtc_date_set.WeekDay = RTC_WEEKDAY_FRIDAY;
  rtc_date_set.Date = 12;
  rtc_date_set.Month = RTC_MONTH_AUGUST;
  rtc_date_set.Year = 22;

  HAL_RTC_SetTime(&hrtc, &rtc_time_set, RTC_FORMAT_BIN);
  HAL_RTC_SetDate(&hrtc, &rtc_date_set, RTC_FORMAT_BIN);

  RTC_TimeTypeDef rtc_time;
  RTC_DateTypeDef rtc_date;
  time_t t;

  while (1) {
    HAL_RTC_GetTime(&hrtc, &rtc_time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &rtc_date, RTC_FORMAT_BIN);
    t = time_from_rtc(rtc_time, rtc_date);

    printf("Time: %d:%d:%d, %d, %d, %d\n",
           rtc_time.Hours,
           rtc_time.Minutes,
           rtc_time.Seconds,
           rtc_date.Date,
           rtc_date.Month,
           rtc_date.Year + 2000);
    printf(
      "UNIX Time: %ld\n",
      (long)
        t); // Conversion to long (32 bit) should be sufficient for debugging

    osDelay(1000);
  }
}