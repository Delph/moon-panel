#ifndef DATETIME_H_INCLUDE
#define DATETIME_H_INCLUDE

#include <stdint.h>

#include "date.h"
#include "time.h"

struct DateTime : public Date, public Time
{
  DateTime(const uint16_t y, const uint8_t m, const uint8_t d, const uint8_t h, const uint8_t min, const uint8_t s) :
  Date(y, m, d),
  Time(h, min, s) {}

  float moon_phase() const
  {
    const float LUNAR_DAYS = 29.53058770576f;
    const float LUNAR_SECONDS = LUNAR_DAYS * 86400;
    DateTime new2000 = DateTime(2000, 1, 8, 18, 14, 0);

    float elapsed = fmod(now() - new2000.now(), LUNAR_SECONDS);
    while (elapsed < 0.0f)
      elapsed += LUNAR_SECONDS;

    return elapsed / LUNAR_SECONDS;
  }

  float tide() const;

  // conversion
  inline Date date() const
  {
    return Date(year, month, day);
  }

  inline Time time() const
  {
    return Time(hours, minutes, seconds);
  }

  inline int64_t now() const
  {
    return (year - 1970) * (365 * 86400) + (day_of_year() + (year - 1972) / 4) * 86400 + hours * 3600 + minutes * 60 + seconds;
  }

  // operators
  inline bool operator==(const DateTime& rhs) const
  {
    return (*static_cast<const Date*>(this)) == (*static_cast<const Date*>(&rhs)) &&
      (*static_cast<const Time*>(this)) == (*static_cast<const Time*>(&rhs));
  }

  inline bool operator<(const DateTime& rhs) const
  {
    if ((*static_cast<const Date*>(this)) < (*static_cast<const Date*>(&rhs)))
      return true;
    else if ((*static_cast<const Date*>(this)) > (*static_cast<const Date*>(&rhs)))
      return false;
    return (*static_cast<const Time*>(this)) < (*static_cast<const Time*>(&rhs));
  }

  // no members!
};

#endif
