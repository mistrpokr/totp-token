#include "time_rtc.h"

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