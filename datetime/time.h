#ifndef TIME_H_INCLUDE
#define TIME_H_INCLUDE

#include <stdint.h>


struct Time
{
  Time(const uint16_t h, const uint8_t m, const uint8_t s) : hours(h), minutes(m), seconds(s) {}


  inline bool is_am() const { return hours < 12; }
  inline bool is_pm() const { return hours >= 12; }


  // operators
  inline bool operator==(const Time& rhs) const
  {
    return hours == rhs.hours &&
      minutes == rhs.minutes &&
      seconds == rhs.seconds;
  }

  inline bool operator<(const Time& rhs) const
  {
    if (hours < rhs.hours)
      return true;
    else if (hours > rhs.hours)
      return false;
    if (minutes < rhs.minutes)
      return true;
    else if (minutes > rhs.minutes)
      return false;
    return seconds < rhs.seconds;
  }

  // members
  const uint8_t hours;
  const uint8_t minutes;
  const uint8_t seconds;
};

#endif
