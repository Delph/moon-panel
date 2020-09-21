#ifndef DATE_H_INCLUDE
#define DATE_H_INCLUDE

#include <stdint.h>
#include <math.h>

#include "time.h"

inline float sin_d(const float a) { return sin(radians(a)); }
inline float cos_d(const float a) { return cos(radians(a)); }
inline float tan_d(const float a) { return tan(radians(a)); }

inline float asin_d(const float a) { return degrees(asin(a)); }
inline float acos_d(const float a) { return degrees(acos(a)); }
inline float atan_d(const float a) { return degrees(atan(a)); }


struct Date
{
  Date(const uint16_t y, const uint8_t m, const uint8_t d) : year(y), month(m), day(d) {}

  // calendar functions
  inline uint16_t day_of_year() const
  {
    return ((275 * month) / 9) - (((month + 9) / 12) * (1 + (year - 4 * (year / 4) + 2) / 3)) + day - 30;
  }

  inline uint8_t week_of_year() const
  {
    return day_of_year() / 7;
  }

  inline uint8_t day_of_week() const
  {
    return (3 + (year - 1970) + (year - 1968) / 4 + day_of_year()) % 7;
  }

  // solar and lunar computations
  static inline bool is_leap_year(const uint16_t year)
  {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
  }

  inline bool is_leap_year() const
  {
    return Date::is_leap_year(year);
  }

  Time sunrise(const float latitude, const float longitude, const float tzOffset) const
{
  const float lngHour = longitude / 15.0f;
  const float t = day_of_year() + ((6 - lngHour) / 24.0f);

  const float M = (0.9856f * t) - 3.289f;
  float L = M + (1.916 * sin_d(M)) + (0.020 * sin_d(2 * M)) + 282.634;
  while (L < 0.0f)
    L += 360.0f;
  while (L >= 360.0f)
    L -= 360.0f;

  float RA = atan_d(0.91764 * tan_d(L));

  const int16_t LQuad = floor(L / 90) * 90;
  const int16_t RAquad = floor(RA / 90) * 90;
  RA = (RA + (LQuad - RAquad)) / 15.0f;

  const float sinDec = 0.39782 * sin_d(L);
  const float cosDec = cos_d(asin_d(sinDec));

  const float zenith = 90.8333333;
  const float cosH = (cos_d(zenith) - (sinDec * sin_d(latitude))) / (cosDec * cos_d(latitude));

  if (cosH > 1.0f)
    return Time(24, 0, 0);
  else if (cosH < -1.0f)
    return Time(0, 0, 0);

  const float H = (360.0f - acos_d(cosH)) / 15.0f;

  const float T = H + RA - (0.06571 * t) - 6.622;
  float UT = T - lngHour;
  while (UT < 0.0f)
    UT += 24.0f;
  while (UT >= 24.0f)
    UT -= 24.0f;

  const float local = UT + tzOffset;
  const uint8_t hours = floor(local);
  const uint8_t minutes = (local - hours) * 60;
  const uint8_t seconds = ((local - hours) * 60 - minutes) * 60;
  return Time(hours, minutes, seconds);
}

  Time sunset(const float latitude, const float longitude, const float tzOffset) const
{
  const float lngHour = longitude / 15.0f;
  const float t = day_of_year() + ((18 - lngHour) / 24.0f);

  const float M = (0.9856f * t) - 3.289f;
  float L = M + (1.916 * sin_d(M)) + (0.020 * sin_d(2 * M)) + 282.634;
  while (L < 0.0f)
    L += 360.0f;
  while (L >= 360.0f)
    L -= 360.0f;

  float RA = atan_d(0.91764 * tan_d(L));

  const int16_t LQuad = floor(L / 90) * 90;
  const int16_t RAquad = floor(RA / 90) * 90;
  RA = (RA + (LQuad - RAquad)) / 15.0f;

  const float sinDec = 0.39782 * sin_d(L);
  const float cosDec = cos_d(asin_d(sinDec));

  const float zenith = 90.8333333;
  const float cosH = (cos_d(zenith) - (sinDec * sin_d(latitude))) / (cosDec * cos_d(latitude));

  if (cosH > 1.0f)
    return Time(24, 0, 0);
  else if (cosH < -1.0f)
    return Time(0, 0, 0);

  const float H = acos_d(cosH) / 15.0f;

  const float T = H + RA - (0.06571 * t) - 6.622;
  float UT = T - lngHour;
  while (UT < 0.0f)
    UT += 24.0f;
  while (UT >= 24.0f)
    UT -= 24.0f;

  const float local = UT + tzOffset;
  const uint8_t hours = floor(local);
  const uint8_t minutes = (local - hours) * 60;
  const uint8_t seconds = ((local - hours) * 60 - minutes) * 60;
  return Time(hours, minutes, seconds);
}



  // operators
  inline bool operator==(const Date& rhs) const
  {
    return year == rhs.year &&
      month == rhs.month &&
      day == rhs.day;
  }

  inline bool operator<(const Date& rhs) const
  {
    if (year < rhs.year)
      return true;
    else if (year > rhs.year)
      return false;
    if (month < rhs.month)
      return true;
    else if (month > rhs.month)
      return false;
    return day < rhs.day;
  }

  inline bool operator>(const Date& rhs) const
  {
    return !(*this == rhs || *this < rhs);
  }
  // members
  const uint16_t year;
  const uint8_t month;
  const uint8_t day;
};

#endif
