#include <Arduino.h>

#include "datetime/date.h"
#include "datetime/time.h"
#include "datetime/datetime.h"

void setup()
{
  Serial.begin(9600);

  // 2020-09-16 norwich 6:31 -- 19:06
  Date date = Date(2020, 9, 17);
  Time sunrise = date.sunrise(52.63333333333333f, 1.3f, 1.0f);
  Serial.print("Sunrise in Norwich is at ");
  Serial.print(sunrise.hours);
  Serial.print(":");
  Serial.print(sunrise.minutes);
  Serial.print(":");
  Serial.println(sunrise.seconds);

  Time sunset = date.sunset(52.63333333333333, 1.3f, 1.0f);
  Serial.print("Sunset in Norwich is at ");
  Serial.print(sunset.hours);
  Serial.print(":");
  Serial.print(sunset.minutes);
  Serial.print(":");
  Serial.println(sunset.seconds);

  DateTime datetime = DateTime(2020, 9, 18, 9, 59, 44);
  float phase = datetime.moon_phase();
  float days = phase * 29.53058770576f;
  Serial.print("Lunar phase for right now is: ");
  Serial.println(days);
}

void loop()
{
}
