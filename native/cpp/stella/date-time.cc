//  -*- Mode: C++ -*-

// date-time.cc

/*
+---------------------------- BEGIN LICENSE BLOCK ---------------------------+
|                                                                            |
| Version: MPL 1.1/GPL 2.0/LGPL 2.1                                          |
|                                                                            |
| The contents of this file are subject to the Mozilla Public License        |
| Version 1.1 (the "License"); you may not use this file except in           |
| compliance with the License. You may obtain a copy of the License at       |
| http://www.mozilla.org/MPL/                                                |
|                                                                            |
| Software distributed under the License is distributed on an "AS IS" basis, |
| WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License   |
| for the specific language governing rights and limitations under the       |
| License.                                                                   |
|                                                                            |
| The Original Code is the STELLA Programming Language.                      |
|                                                                            |
| The Initial Developer of the Original Code is                              |
| UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |
| 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |
|                                                                            |
| Portions created by the Initial Developer are Copyright (C) 1996-2023      |
| the Initial Developer. All Rights Reserved.                                |
|                                                                            |
| Contributor(s):                                                            |
|                                                                            |
| Alternatively, the contents of this file may be used under the terms of    |
| either the GNU General Public License Version 2 or later (the "GPL"), or   |
| the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),   |
| in which case the provisions of the GPL or the LGPL are applicable instead |
| of those above. If you wish to allow use of your version of this file only |
| under the terms of either the GPL or the LGPL, and not to allow others to  |
| use your version of this file under the terms of the MPL, indicate your    |
| decision by deleting the provisions above and replace them with the notice |
| and other provisions required by the GPL or the LGPL. If you do not delete |
| the provisions above, a recipient may use your version of this file under  |
| the terms of any one of the MPL, the GPL or the LGPL.                      |
|                                                                            |
+---------------------------- END LICENSE BLOCK -----------------------------+
*/

#include "stella/stella-system.hh"

namespace stella {

int computeJulianDay(int yyyy, int mm, int dd) {
  // Returns the Julian day that starts at noon on yyyy-mm-dd.
  // `yyyy' is the year.  `mm' is the month.  `dd' is the day of month.
  // Negative years are B.C.  Remember there is no year zero.
  { int jul = 0;
    int ja = 0;
    int jy = 0;
    int jm = 0;

    if (yyyy == 0) {
      throw *newStellaException("There is no year zero.");
    }
    if (mm > 12) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Month " << "`" << mm << "'" << " must be <= 12";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    if (mm < 0) {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "Month " << "`" << mm << "'" << " must be > zero.";
        throw *newStellaException(stream001->theStringReader());
      }
    }
    if (dd > 31) {
      { OutputStringStream* stream002 = newOutputStringStream();

        *(stream002->nativeStream) << "Day " << "`" << dd << "'" << " must be <= 31";
        throw *newStellaException(stream002->theStringReader());
      }
    }
    if (dd < 0) {
      { OutputStringStream* stream003 = newOutputStringStream();

        *(stream003->nativeStream) << "Day " << "`" << dd << "'" << " must be > zero.";
        throw *newStellaException(stream003->theStringReader());
      }
    }
    if (yyyy < 0) {
      yyyy = yyyy + 1;
    }
    if (mm > 2) {
      {
        jy = yyyy;
        jm = mm + 1;
      }
    }
    else {
      {
        jy = yyyy - 1;
        jm = mm + 13;
      }
    }
    jul = stella::floor(365.25 * jy) + stella::floor(30.6001 * jm) + dd + 1720995;
    if ((dd + (31 * (mm + (12 * yyyy)))) >= (15 + (31 * (10 + (12 * 1582))))) {
      ja = ((int)(0.01 * jy));
      jul = jul + (2 - ja) + ((int)(0.25 * ja));
    }
    return (jul);
  }
}

int julianDayToModifiedJulianDay(int julianDay) {
  // Returns the modified Julian day during which `julian-day'starts at noon.
  return (julianDay - 2400000);
}

int modifiedJulianDayToJulianDay(int modifiedJulianDay) {
  // Returns the modified Julian day during which `julian-day'starts at noon.
  return (modifiedJulianDay + 2400000);
}

Keyword* computeDayOfWeekJulian(int julianDay) {
  // Returns the day of the week for julian-day
  switch ((julianDay % 7)) {
    case 0: 
      return (KWD_DATE_TIME_MONDAY);
    case 1: 
      return (KWD_DATE_TIME_TUESDAY);
    case 2: 
      return (KWD_DATE_TIME_WEDNESDAY);
    case 3: 
      return (KWD_DATE_TIME_THURSDAY);
    case 4: 
      return (KWD_DATE_TIME_FRIDAY);
    case 5: 
      return (KWD_DATE_TIME_SATURDAY);
    case 6: 
      return (KWD_DATE_TIME_SUNDAY);
    default:
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << (julianDay % 7) << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
      break;
  }
}

Keyword* computeDayOfWeek(int yyyy, int mm, int dd) {
  // Returns the day of the week for yyyy-mm-dd.
  return (computeDayOfWeekJulian(computeJulianDay(yyyy, mm, dd)));
}

int computeNextMoonPhase(int n, Keyword* phase, double& _Return1) {
  // Returns the Julian Day and fraction of day of the Nth occurence
  // since January 1, 1900 of moon PHASE.  PHASE is one of :NEW-MOON, :FIRST-QUARTER,
  // :FULL-MOON, :LAST-QUARTER
  { int i = 0;
    double am = 0.0;
    double as = 0.0;
    double c = 0.0;
    double x = 0.0;
    double x2 = 0.0;
    double extra = 0.0;
    double rad = PI / 180.0;
    int julianDay = 0;

    if (phase == KWD_DATE_TIME_NEW_MOON) {
      c = ((double)(n));
      julianDay = 0;
    }
    else if (phase == KWD_DATE_TIME_FIRST_QUARTER) {
      c = n + 0.25;
      julianDay = 7;
    }
    else if (phase == KWD_DATE_TIME_FULL_MOON) {
      c = n + 0.5;
      julianDay = 14;
    }
    else if (phase == KWD_DATE_TIME_LAST_QUARTER) {
      c = n + 0.75;
      julianDay = 21;
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << phase << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    x = c / 1236.85;
    x2 = x * x;
    as = 359.2242 + (29.105356 * c);
    am = 306.0253 + (385.816918 * c) + (0.01073 * x2);
    julianDay = 2415020 + (28 * n) + julianDay;
    extra = 0.75933 + (1.53058868 * c) + ((1.178e-4 - (1.55e-7 * x)) * x2);
    if ((phase == KWD_DATE_TIME_NEW_MOON) ||
        (phase == KWD_DATE_TIME_FULL_MOON)) {
      extra = extra + (((0.1734 - (3.93e-4 * x)) * ::sin((as * rad))) - (0.4068 * ::sin((am * rad))));
    }
    else if ((phase == KWD_DATE_TIME_FIRST_QUARTER) ||
        (phase == KWD_DATE_TIME_LAST_QUARTER)) {
      extra = extra + (((0.1721 - (4.0e-4 * x)) * ::sin((as * rad))) - (0.628 * ::sin((am * rad))));
    }
    else {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "`" << phase << "'" << " is not a valid case option";
        throw *newStellaException(stream001->theStringReader());
      }
    }
    i = ((extra >= 0.0) ? stella::floor(extra) : ceiling(extra - 1.0));
    { int _Return0 = julianDay + i;

      _Return1 = extra - i;
      return (_Return0);
    }
  }
}

int computeCalendarDate(int julianDay, int& _Return1, int& _Return2, Keyword*& _Return3) {
  // Returns the YEAR, MONTH, DAY, DAY-OF-WEEK on which the given
  // `julian-day' begins at noon.
  { int ja = julianDay;
    int jalpha = 0;
    int jb = 0;
    int jc = 0;
    int jd = 0;
    int je = 0;
    int igreg = 2299161;
    int yyyy = 0;
    int mm = 0;
    int dd = 0;

    if (julianDay >= igreg) {
      jalpha = ((int)(((julianDay - 1867216) - 0.25) / 36524.25));
      ja = julianDay + 1 + jalpha + ((int)(-0.25 * jalpha));
    }
    jb = ja + 1524;
    jc = ((int)(6680.0 + (((jb - 2439870) - 122.1) / 365.25)));
    jd = ((int)((365 * jc) + (0.25 * jc)));
    je = ((int)((jb - jd) / 30.6001));
    dd = (jb - jd) - ((int)(30.6001 * je));
    mm = je - 1;
    if (mm > 12) {
      mm = mm - 12;
    }
    yyyy = jc - 4715;
    if (mm > 2) {
      yyyy = yyyy - 1;
    }
    if (yyyy <= 0) {
      yyyy = yyyy - 1;
    }
    { int _Return0 = yyyy;

      _Return1 = mm;
      _Return2 = dd;
      _Return3 = computeDayOfWeekJulian(julianDay);
      return (_Return0);
    }
  }
}

# include <time.h>
int getCurrentDateTime(int& _Return1, int& _Return2, Keyword*& _Return3, int& _Return4, int& _Return5, int& _Return6, int& _Return7) {
  // Returns the current time in UTC as multiple values of
  // year month day day-of-week hour minute second millisecond.  Currently
  // millisecond will always be zero (even in Java where it is technically available).
  { int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;
    int second = 0;
    int millisecond = 0;

    time_t now = time(0);
      if (now > 0) {
        struct tm* time = gmtime(&now);
        year  = time->tm_year + 1900;
        month = time->tm_mon + 1;
        day   = time->tm_mday;
        hour  = time->tm_hour;
        minute = time->tm_min;
        second = time->tm_sec;
      };
    { int _Return0 = year;

      _Return1 = month;
      _Return2 = day;
      _Return3 = computeDayOfWeek(year, month, day);
      _Return4 = hour;
      _Return5 = minute;
      _Return6 = second;
      _Return7 = millisecond;
      return (_Return0);
    }
  }
}

double getLocalTimeZone() {
  // Returns the current time zone offset from UTC as a float,
  // considering the effects of daylight savings time.
  { double offset = 0.0;

    tzset();
#if defined(__APPLE__)
   time_t now = time(0);
   if (now > 0) {
       struct tm* time = gmtime(&now);
       offset = time->tm_gmtoff  / (60.0 * 60.0);
     }
#elif defined(__CYGWIN__)
    offset = - _timezone / (60.0 * 60.0);
    if (daylight > 0) offset += 1.0;
#else
    offset = - timezone / (60.0 * 60.0);
    if (daylight > 0) offset += 1.0;
#endif
;
    return (offset);
  }
}

double getLocalStandardTimeZone() {
  // Returns the standard time zone offset from UTC as a float,
  // without considering the effects of daylight savings time.
  { double offset = 0.0;

    tzset();
#if defined(__APPLE__)
   time_t now = time(0);
   if (now > 0) {
       struct tm* time = gmtime(&now);
       offset = time->tm_gmtoff  / (60.0 * 60.0);
       if (time->tm_isdst > 0) offset -= 1.0;
     }
#elif defined(__CYGWIN__)
    offset = - _timezone / (60.0 * 60.0);
#else
    offset = - timezone / (60.0 * 60.0);
#endif
;
    return (offset);
  }
}

double getLocalTimeZoneForDate(int year, int month, int day, int hour, int minute, int second) {
  // Returns the time zone offset from UTC (as a float)
  // that is applicable to the given date.  Assumes that the date is one
  // that is valid for the underlying programming language.  If not, then
  // returns 0.0
  { double offset = 0.0;

    if ((year > 1970) && (year < 2038)) {
        struct tm time;
        time.tm_year = year - 1900;
        time.tm_mon = month - 1;
        time.tm_mday = day;
        time.tm_hour = hour;
        time.tm_min = minute;
        time.tm_sec = second;
        time.tm_isdst = -1;    // Flag to have mktime determine DST

        mktime(&time);  // Executed for normalization effect only!

        tzset();

#if defined(__APPLE__)
        offset = time.tm_gmtoff / (60.0 * 60.0);
#elif defined(__CYGWIN__)
        offset = - _timezone / (60.0 * 60.0);
        if (time.tm_isdst > 0) offset += 1.0;
#else 
        offset = - timezone / (60.0 * 60.0);
        if (time.tm_isdst > 0) offset += 1.0;
#endif
  };
    return (offset);
  }
}

const char* timeZoneFormat60(double timezone, boolean includeColonP) {
  // Format `zone' as an hh:mm or hhmm string depending on `include-colon?'
  { const char* sign = "+";
    int hours = 0;

    if (timezone < 0) {
      sign = "-";
      timezone = 0 - timezone;
    }
    hours = stella::round(timezone);
    return (stringConcatenate(sign, formatWithPadding(integerToString(((long long int)(hours))), 2, '0', KWD_DATE_TIME_RIGHT, false), 2, (includeColonP ? ":" : ""), formatWithPadding(integerToString(((long long int)(stella::round((timezone - hours) * 60.0)))), 2, '0', KWD_DATE_TIME_RIGHT, false)));
  }
}

int MILLIS_PER_DAY = NULL_INTEGER;

int MILLIS_PER_HOUR = NULL_INTEGER;

// A vector of month names for printing dates
Vector* oMONTH_NAME_VECTORo = NULL;

// A vector of month abbreviations for printing dates
Vector* oMONTH_ABBREVIATION_VECTORo = NULL;

DecodedDateTime* newDecodedDateTime() {
  { DecodedDateTime* self = NULL;

    self = new DecodedDateTime();
    self->dateTimeDow = KWD_DATE_TIME_SUNDAY;
    self->dateTimeZone = 0.0;
    self->dateTimeYear = 1900;
    self->dateTimeMonth = 1;
    self->dateTimeDay = 1;
    self->dateTimeHour = 0;
    self->dateTimeMinute = 0;
    self->dateTimeSecond = 0;
    self->dateTimeMillis = 0.0;
    return (self);
  }
}

Surrogate* DecodedDateTime::primaryType() {
  { DecodedDateTime* self = this;

    return (SGT_DATE_TIME_STELLA_DECODED_DATE_TIME);
  }
}

Object* accessDecodedDateTimeSlotValue(DecodedDateTime* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_DATE_TIME_STELLA_DATE_TIME_MILLIS) {
    if (setvalueP) {
      self->dateTimeMillis = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->dateTimeMillis);
    }
  }
  else if (slotname == SYM_DATE_TIME_STELLA_DATE_TIME_SECOND) {
    if (setvalueP) {
      self->dateTimeSecond = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->dateTimeSecond);
    }
  }
  else if (slotname == SYM_DATE_TIME_STELLA_DATE_TIME_MINUTE) {
    if (setvalueP) {
      self->dateTimeMinute = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->dateTimeMinute);
    }
  }
  else if (slotname == SYM_DATE_TIME_STELLA_DATE_TIME_HOUR) {
    if (setvalueP) {
      self->dateTimeHour = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->dateTimeHour);
    }
  }
  else if (slotname == SYM_DATE_TIME_STELLA_DATE_TIME_DAY) {
    if (setvalueP) {
      self->dateTimeDay = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->dateTimeDay);
    }
  }
  else if (slotname == SYM_DATE_TIME_STELLA_DATE_TIME_MONTH) {
    if (setvalueP) {
      self->dateTimeMonth = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->dateTimeMonth);
    }
  }
  else if (slotname == SYM_DATE_TIME_STELLA_DATE_TIME_YEAR) {
    if (setvalueP) {
      self->dateTimeYear = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->dateTimeYear);
    }
  }
  else if (slotname == SYM_DATE_TIME_STELLA_DATE_TIME_ZONE) {
    if (setvalueP) {
      self->dateTimeZone = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->dateTimeZone);
    }
  }
  else if (slotname == SYM_DATE_TIME_STELLA_DATE_TIME_DOW) {
    if (setvalueP) {
      self->dateTimeDow = ((Keyword*)(value));
    }
    else {
      value = self->dateTimeDow;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

int DecodedDateTime::hashCode() {
  { DecodedDateTime* self = this;

    return (((((((((self->dateTimeYear) << 9)) | (((self->dateTimeMonth) << 5)))) | (self->dateTimeDay))) ^ (((((((self->dateTimeHour) << 12)) | (((self->dateTimeMinute) << 6)))) | (self->dateTimeSecond)))));
  }
}

void DecodedDateTime::setCurrentTime() {
  // Sets the current time into `values-structure'
  { DecodedDateTime* valuesStructure = this;

    { int year = NULL_INTEGER;
      int mon = NULL_INTEGER;
      int day = NULL_INTEGER;
      Keyword* dow = NULL;
      int hour = NULL_INTEGER;
      int min = NULL_INTEGER;
      int sec = NULL_INTEGER;
      int millis = NULL_INTEGER;

      year = getCurrentDateTime(mon, day, dow, hour, min, sec, millis);
      {
        year = year;
        mon = mon;
        day = day;
        dow = dow;
      }
      valuesStructure->dateTimeMillis = ((double)(millis));
      valuesStructure->dateTimeSecond = sec;
      valuesStructure->dateTimeMinute = min;
      valuesStructure->dateTimeHour = hour;
    }
  }
}

void DecodedDateTime::setCurrentDate() {
  // Sets the current date into `values-structure'
  { DecodedDateTime* valuesStructure = this;

    { int year = NULL_INTEGER;
      int mon = NULL_INTEGER;
      int day = NULL_INTEGER;
      Keyword* dow = NULL;
      int hour = NULL_INTEGER;
      int min = NULL_INTEGER;
      int sec = NULL_INTEGER;
      int millis = NULL_INTEGER;

      year = getCurrentDateTime(mon, day, dow, hour, min, sec, millis);
      {
        hour = hour;
        min = min;
        sec = sec;
        millis = millis;
      }
      valuesStructure->dateTimeDow = dow;
      valuesStructure->dateTimeDay = day;
      valuesStructure->dateTimeMonth = mon;
      valuesStructure->dateTimeYear = year;
    }
  }
}

void DecodedDateTime::setCurrentDateTime() {
  // Sets the current date and time into `values-structure'
  { DecodedDateTime* valuesStructure = this;

    { int year = NULL_INTEGER;
      int mon = NULL_INTEGER;
      int day = NULL_INTEGER;
      Keyword* dow = NULL;
      int hour = NULL_INTEGER;
      int min = NULL_INTEGER;
      int sec = NULL_INTEGER;
      int millis = NULL_INTEGER;

      year = getCurrentDateTime(mon, day, dow, hour, min, sec, millis);
      valuesStructure->dateTimeMillis = ((double)(millis));
      valuesStructure->dateTimeSecond = sec;
      valuesStructure->dateTimeMinute = min;
      valuesStructure->dateTimeHour = hour;
      valuesStructure->dateTimeDow = dow;
      valuesStructure->dateTimeDay = day;
      valuesStructure->dateTimeMonth = mon;
      valuesStructure->dateTimeYear = year;
    }
  }
}

const char* DecodedDateTime::decodedDateTimeToIso8601String() {
  // Returns an ISO-8601 string representation of `date'
  // The Format is YYYY-MM-DDThh:mm:ss+zz:zz, with the string stopping at
  // when a null value is first encountered.  The time zone will only
  // be included (if present) if a time value is given.
  { DecodedDateTime* date = this;

    { char* buffer = makeRawMutableString(25);
      int index = 0;

      if (date->dateTimeYear != NULL_INTEGER) {
        index = insertString(integerToString(((long long int)(date->dateTimeYear))), 0, NULL_INTEGER, buffer, index, KWD_DATE_TIME_PRESERVE);
        if (date->dateTimeMonth != NULL_INTEGER) {
          index = insertString("-", 0, NULL_INTEGER, buffer, index, KWD_DATE_TIME_PRESERVE);
          index = insertString(formatWithPadding(integerToString(((long long int)(date->dateTimeMonth))), 2, '0', KWD_DATE_TIME_RIGHT, false), 0, NULL_INTEGER, buffer, index, KWD_DATE_TIME_PRESERVE);
          if (date->dateTimeDay != NULL_INTEGER) {
            index = insertString("-", 0, NULL_INTEGER, buffer, index, KWD_DATE_TIME_PRESERVE);
            index = insertString(formatWithPadding(integerToString(((long long int)(date->dateTimeDay))), 2, '0', KWD_DATE_TIME_RIGHT, false), 0, NULL_INTEGER, buffer, index, KWD_DATE_TIME_PRESERVE);
            if (date->dateTimeHour != NULL_INTEGER) {
              index = insertString("T", 0, NULL_INTEGER, buffer, index, KWD_DATE_TIME_PRESERVE);
              index = insertString(formatWithPadding(integerToString(((long long int)(date->dateTimeHour))), 2, '0', KWD_DATE_TIME_RIGHT, false), 0, NULL_INTEGER, buffer, index, KWD_DATE_TIME_PRESERVE);
              if (date->dateTimeMinute != NULL_INTEGER) {
                index = insertString(":", 0, NULL_INTEGER, buffer, index, KWD_DATE_TIME_PRESERVE);
                index = insertString(formatWithPadding(integerToString(((long long int)(date->dateTimeMinute))), 2, '0', KWD_DATE_TIME_RIGHT, false), 0, NULL_INTEGER, buffer, index, KWD_DATE_TIME_PRESERVE);
                if (date->dateTimeSecond != NULL_INTEGER) {
                  index = insertString(":", 0, NULL_INTEGER, buffer, index, KWD_DATE_TIME_PRESERVE);
                  index = insertString(formatWithPadding(integerToString(((long long int)(date->dateTimeSecond))), 2, '0', KWD_DATE_TIME_RIGHT, false), 0, NULL_INTEGER, buffer, index, KWD_DATE_TIME_PRESERVE);
                }
              }
              if (date->dateTimeZone != NULL_FLOAT) {
                if (date->dateTimeZone == 0.0) {
                  index = insertString("Z", 0, NULL_INTEGER, buffer, index, KWD_DATE_TIME_PRESERVE);
                }
                else {
                  index = insertString(timeZoneFormat60(date->dateTimeZone, true), 0, NULL_INTEGER, buffer, index, KWD_DATE_TIME_PRESERVE);
                }
              }
            }
          }
        }
      }
      return (mutableStringSubsequence(buffer, 0, index));
    }
  }
}

void DecodedDateTime::setConsistentDow() {
  { DecodedDateTime* self = this;

    if ((self->dateTimeYear != NULL_INTEGER) &&
        ((self->dateTimeMonth != NULL_INTEGER) &&
         (self->dateTimeDay != NULL_INTEGER))) {
      self->dateTimeDow = computeDayOfWeek(self->dateTimeYear, self->dateTimeMonth, self->dateTimeDay);
    }
  }
}

void DecodedDateTime::helpMergeNullFields(DecodedDateTime* defaulT, int index) {
  { DecodedDateTime* self = this;

    if ((self->dateTimeYear == NULL_INTEGER) &&
        (index >= 0)) {
      self->dateTimeYear = defaulT->dateTimeYear;
    }
    if ((self->dateTimeMonth == NULL_INTEGER) &&
        (index >= 1)) {
      self->dateTimeMonth = defaulT->dateTimeMonth;
    }
    if ((self->dateTimeDay == NULL_INTEGER) &&
        (index >= 2)) {
      self->dateTimeDay = defaulT->dateTimeDay;
    }
    if ((self->dateTimeHour == NULL_INTEGER) &&
        (index >= 3)) {
      self->dateTimeHour = defaulT->dateTimeHour;
    }
    if ((self->dateTimeMinute == NULL_INTEGER) &&
        (index >= 4)) {
      self->dateTimeMinute = defaulT->dateTimeMinute;
    }
    if ((self->dateTimeSecond == NULL_INTEGER) &&
        (index >= 5)) {
      self->dateTimeSecond = defaulT->dateTimeSecond;
    }
    if ((self->dateTimeMillis == NULL_FLOAT) &&
        (index >= 6)) {
      self->dateTimeMillis = defaulT->dateTimeMillis;
    }
    if (self->dateTimeZone == NULL_FLOAT) {
      self->dateTimeZone = defaulT->dateTimeZone;
    }
    self->setConsistentDow();
  }
}

void DecodedDateTime::mergeNullFields(DecodedDateTime* defaulT) {
  // Replace any null valued fields in `self' with values from `default'.
  // The day of the week will be set consistently, if possible.
  { DecodedDateTime* self = this;

    self->helpMergeNullFields(defaulT, 6);
  }
}

void DecodedDateTime::mergeSuperiorNullFields(DecodedDateTime* defaulT) {
  // Replace only null valued fields in `self' that represent larger
  // time units than the smallest non-null in `self' with values from `default'.
  // The day of the week will be set consistently, if possible.
  // Example: if `self' just has the month being non-null, then only the year
  // will be filled in from `default'.  If the day and minute were non-null,
  // then hour, month and year will be filled.
  // 
  // This can be useful when one doesn't want to extend the precision
  // of the answer.
  { DecodedDateTime* self = this;

    if (self->dateTimeMillis != NULL_FLOAT) {
      self->helpMergeNullFields(defaulT, 6);
    }
    else if (self->dateTimeSecond != NULL_INTEGER) {
      self->helpMergeNullFields(defaulT, 5);
    }
    else if (self->dateTimeMinute != NULL_INTEGER) {
      self->helpMergeNullFields(defaulT, 4);
    }
    else if (self->dateTimeHour != NULL_INTEGER) {
      self->helpMergeNullFields(defaulT, 3);
    }
    else if (self->dateTimeDay != NULL_INTEGER) {
      self->helpMergeNullFields(defaulT, 2);
    }
    else if (self->dateTimeMonth != NULL_INTEGER) {
      self->helpMergeNullFields(defaulT, 1);
    }
    else {
      self->helpMergeNullFields(defaulT, 0);
    }
  }
}

DecodedTimeDuration* newDecodedTimeDuration() {
  { DecodedTimeDuration* self = NULL;

    self = new (PointerFreeGC)DecodedTimeDuration;
    self->durationDays = 0;
    self->durationHours = 0;
    self->durationMinutes = 0;
    self->durationSeconds = 0;
    self->durationMillis = 0.0;
    return (self);
  }
}

Surrogate* DecodedTimeDuration::primaryType() {
  { DecodedTimeDuration* self = this;

    return (SGT_DATE_TIME_STELLA_DECODED_TIME_DURATION);
  }
}

Object* accessDecodedTimeDurationSlotValue(DecodedTimeDuration* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_DATE_TIME_STELLA_DURATION_MILLIS) {
    if (setvalueP) {
      self->durationMillis = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->durationMillis);
    }
  }
  else if (slotname == SYM_DATE_TIME_STELLA_DURATION_SECONDS) {
    if (setvalueP) {
      self->durationSeconds = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->durationSeconds);
    }
  }
  else if (slotname == SYM_DATE_TIME_STELLA_DURATION_MINUTES) {
    if (setvalueP) {
      self->durationMinutes = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->durationMinutes);
    }
  }
  else if (slotname == SYM_DATE_TIME_STELLA_DURATION_HOURS) {
    if (setvalueP) {
      self->durationHours = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->durationHours);
    }
  }
  else if (slotname == SYM_DATE_TIME_STELLA_DURATION_DAYS) {
    if (setvalueP) {
      self->durationDays = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->durationDays);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

int DecodedTimeDuration::hashCode() {
  { DecodedTimeDuration* self = this;

    return (((self->durationDays) ^ (((((((self->durationHours) << 12)) | (((self->durationMinutes) << 6)))) | (self->durationSeconds)))));
  }
}

CalendarDate* newCalendarDate() {
  { CalendarDate* self = NULL;

    self = new (PointerFreeGC)CalendarDate;
    self->timeMillis = NULL_INTEGER;
    self->modifiedJulianDay = NULL_INTEGER;
    return (self);
  }
}

Surrogate* CalendarDate::primaryType() {
  { CalendarDate* self = this;

    return (SGT_DATE_TIME_STELLA_CALENDAR_DATE);
  }
}

Object* accessCalendarDateSlotValue(CalendarDate* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_DATE_TIME_STELLA_MODIFIED_JULIAN_DAY) {
    if (setvalueP) {
      self->modifiedJulianDay = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->modifiedJulianDay);
    }
  }
  else if (slotname == SYM_DATE_TIME_STELLA_TIME_MILLIS) {
    if (setvalueP) {
      self->timeMillis = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->timeMillis);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

void CalendarDate::printObject(std::ostream* stream) {
  { CalendarDate* self = this;

    self->printCalendarDate(stream);
  }
}

Quantity* CalendarDate::coerceTo(Object* y) {
  { CalendarDate* x = this;

    if (subtypeOfP(safePrimaryType(y), SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
      { Object* y000 = y;
        CalendarDate* y = ((CalendarDate*)(y000));

        return (y);
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't coerce " << "`" << y << "'" << " to a CALENDAR-DATE";
        throw *newIncompatibleQuantityException(stream000->theStringReader());
      }
    }
  }
}

int CalendarDate::hashCode() {
  { CalendarDate* self = this;

    return (((self->modifiedJulianDay) ^ (self->timeMillis)));
  }
}

const char* CalendarDate::calendarDateToDateString(double timezone, boolean numericMonthP) {
  // Returns the date part of the string representation of `date' 
  // adjusted for `timezone'.  Format is YYYY-MMM-DD, where MMM is a three letter
  // English abbreviation of the month if `numeric-month?' is `false' and a two
  // digit numeric value if `numeric-month?' is `true'.  The value `false' is
  // recommended.
  { CalendarDate* date = this;

    { int year = NULL_INTEGER;
      int month = NULL_INTEGER;
      int day = NULL_INTEGER;
      Keyword* dow = NULL;

      year = date->getCalendarDate(timezone, month, day, dow);
      dow = dow;
      { const char* yearString = ((year < 0) ? stringConcatenate(integerToString(((long long int)(0 - year))), "BC", 0) : integerToString(((long long int)(year))));
        const char* monthString = (numericMonthP ? formatWithPadding(integerToString(((long long int)(month))), 2, '0', KWD_DATE_TIME_RIGHT, false) : unwrapString(((StringWrapper*)((oMONTH_ABBREVIATION_VECTORo->theArray)[month]))));

        return (stringConcatenate(yearString, "-", 3, monthString, "-", formatWithPadding(integerToString(((long long int)(day))), 2, '0', KWD_DATE_TIME_RIGHT, false)));
      }
    }
  }
}

const char* CalendarDate::calendarDateToTimeString(double timezone, boolean includeTimezoneP, boolean includeMillisP, boolean padHoursP) {
  // Returns the time part of the string representation of `date'
  // adjusted for `timezone'.  The timezone is included in the string if
  // `include-timezone?' is `true'.  The value `true' is recommended.
  // Milliseconds will be included if `include-millis?' is `true'.
  // Hours will be zero-padded to length 2 if `pad-hours?' is `true'.
  // 
  { CalendarDate* date = this;

    { int hours = NULL_INTEGER;
      int minutes = NULL_INTEGER;
      int seconds = NULL_INTEGER;
      int milli = NULL_INTEGER;

      hours = date->getTime(timezone, minutes, seconds, milli);
      { const char* timezoneString = (includeTimezoneP ? (((timezone == 0.0) ? " UTC" : stringConcatenate(" ", floatToString(timezone), 0))) : "");
        const char* milliString = (includeMillisP ? stringConcatenate(".", formatWithPadding(integerToString(((long long int)(milli))), 3, '0', KWD_DATE_TIME_RIGHT, false), 0) : "");

        return (stringConcatenate((padHoursP ? formatWithPadding(integerToString(((long long int)(hours))), 2, '0', KWD_DATE_TIME_RIGHT, false) : integerToString(((long long int)(hours)))), ":", 5, formatWithPadding(integerToString(((long long int)(minutes))), 2, '0', KWD_DATE_TIME_RIGHT, false), ":", formatWithPadding(integerToString(((long long int)(seconds))), 2, '0', KWD_DATE_TIME_RIGHT, false), milliString, timezoneString));
      }
    }
  }
}

const char* CalendarDate::calendarDateToString(double timezone, boolean numericMonthP, boolean includeTimezoneP) {
  // Returns a string representation of `date' adjusted for `timezone'.
  // The Format is YYYY-MMM-DD hh:mm:ss z.z, where MMM is a three letter
  // English abbreviation of the month if `numeric-month?' is `false' and a two
  // digit numeric value if `numeric-month?' is `true'.  The timezone as a
  // float offset z.z is included if `include-timezone?' is `true'.
  // 
  // Recommended values for the flags are `false' and `true' respectively.
  { CalendarDate* date = this;

    return (stringConcatenate(date->calendarDateToDateString(timezone, numericMonthP), " ", 1, date->calendarDateToTimeString(timezone, includeTimezoneP, true, false)));
  }
}

const char* CalendarDate::calendarDateToIso8601String(double timezone, boolean includeTimezoneP) {
  // Returns an ISO-8601 string representation of `date' adjusted for `timezone'.
  // The Format is YYYY-MM-DDThh:mm:ss z:zz.  The timezone as an offset
  // hh:mm is included if `include-timezone?' is `true'.
  // 
  // Recommended values for the flag is `true'.
  { CalendarDate* date = this;

    { const char* tzString = "";

      if (includeTimezoneP) {
        if (timezone == 0.0) {
          tzString = "Z";
        }
        else {
          tzString = timeZoneFormat60(timezone, true);
        }
      }
      return (stringConcatenate(date->calendarDateToDateString(timezone, true), "T", 2, date->calendarDateToTimeString(timezone, false, false, true), tzString));
    }
  }
}

time_t CalendarDate::calendarDateToNativeDateTime() {
  { CalendarDate* date = this;

    { int mjd = date->modifiedJulianDay;
      int millis = date->timeMillis;

      return ((((time_t)mjd - 40588) * 86400) + ((time_t)millis / 1000));
    }
  }
}

CalendarDate* nativeDateTimeToCalendarDate(time_t date) {
  { int mjd = 0;
    int millis = 0;

    mjd =  (int) ((date / 86400) + 40588);
      millis = (int) ((date % 86400) * 1000);
    return (makeCalendarDate(mjd, millis));
  }
}

void CalendarDate::printCalendarDate(std::ostream* stream) {
  { CalendarDate* date = this;

    if (oPRINTREADABLYpo) {
      *(stream) << "\"";
    }
    else {
      *(stream) << "<" << date->modifiedJulianDay << " ";
    }
    *(stream) << date->calendarDateToString(0.0, false, false);
    if (oPRINTREADABLYpo) {
      *(stream) << " UTC\"";
    }
    else {
      *(stream) << " UTC>";
    }
  }
}

TimeDuration* newTimeDuration() {
  { TimeDuration* self = NULL;

    self = new (PointerFreeGC)TimeDuration;
    self->millis = NULL_INTEGER;
    self->days = NULL_INTEGER;
    return (self);
  }
}

Surrogate* TimeDuration::primaryType() {
  { TimeDuration* self = this;

    return (SGT_DATE_TIME_STELLA_TIME_DURATION);
  }
}

Object* accessTimeDurationSlotValue(TimeDuration* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_DATE_TIME_STELLA_DAYS) {
    if (setvalueP) {
      self->days = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->days);
    }
  }
  else if (slotname == SYM_DATE_TIME_STELLA_MILLIS) {
    if (setvalueP) {
      self->millis = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->millis);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

void TimeDuration::printObject(std::ostream* stream) {
  { TimeDuration* self = this;

    self->printTimeDuration(stream);
  }
}

Quantity* TimeDuration::coerceTo(Object* y) {
  { TimeDuration* x = this;

    if (subtypeOfP(safePrimaryType(y), SGT_DATE_TIME_STELLA_TIME_DURATION)) {
      { Object* y000 = y;
        TimeDuration* y = ((TimeDuration*)(y000));

        return (y);
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't coerce " << "`" << y << "'" << " to a TIME-DURATION";
        throw *newIncompatibleQuantityException(stream000->theStringReader());
      }
    }
  }
}

int TimeDuration::hashCode() {
  { TimeDuration* self = this;

    return (((self->days) ^ (self->millis)));
  }
}

const char* TimeDuration::timeDurationToString() {
  // Returns a string representation of `date'
  { TimeDuration* date = this;

    { int nDays = date->days;
      int nMillis = date->millis;

      if (nDays < 0) {
        if (nMillis <= 0) {
          return (stringConcatenate("minus ", integerToString(((long long int)(0 - nDays))), 3, " days; ", integerToString(((long long int)(0 - nMillis))), " ms"));
        }
        else {
          return (stringConcatenate("minus ", integerToString(((long long int)(0 - (nDays + 1)))), 3, " days; ", integerToString(((long long int)(MILLIS_PER_DAY - nMillis))), " ms"));
        }
      }
      else {
        if (nMillis < 0) {
          if (nDays > 0) {
            return (stringConcatenate("plus ", integerToString(((long long int)(nDays - 1))), 3, " days; ", integerToString(((long long int)(MILLIS_PER_DAY + nMillis))), " ms"));
          }
          else {
            return (stringConcatenate("minus 0 days; ", integerToString(((long long int)(0 - nMillis))), 1, " ms"));
          }
        }
        else {
          return (stringConcatenate("plus ", integerToString(((long long int)(nDays))), 3, " days; ", integerToString(((long long int)(nMillis))), " ms"));
        }
      }
    }
  }
}

TimeDuration* stringToTimeDuration(const char* duration) {
  // Parses and returns an time-duration object corresponding to `duration'.
  // The syntax for time duration strings is "{plus|minus} N days[; M ms]" where N and M are
  // integer values for days and milliseconds.  If no valid parse is found, `null' is returned.
  { int nDays = 0;
    int nMillis = 0;
    boolean negativeP = stringSearch(duration, "minus", 0) != NULL_INTEGER;
    int dayStartPosition = 0;
    int dayEndPosition = 0;
    int msStartPosition = 0;
    int msEndPosition = 0;

    if (negativeP) {
      dayStartPosition = 6;
    }
    else if (stringSearch(duration, "plus", 0) != NULL_INTEGER) {
      dayStartPosition = 5;
    }
    else {
      dayStartPosition = 0;
    }
    dayEndPosition = stringSearch(duration, "days", dayStartPosition);
    if (dayEndPosition == NULL_INTEGER) {
      return (NULL);
    }
    else {
      nDays = ((int)(stringToInteger(stringSubsequence(duration, dayStartPosition, dayEndPosition - 1))));
    }
    msStartPosition = stringPosition(duration, ' ', dayEndPosition);
    if (msStartPosition != NULL_INTEGER) {
      msEndPosition = stringSearch(duration, "ms", msStartPosition);
      if (msEndPosition != NULL_INTEGER) {
        nMillis = ((int)(stringToInteger(stringSubsequence(duration, msStartPosition + 1, msEndPosition - 1))));
      }
    }
    if (negativeP) {
      return (makeTimeDuration(0 - nDays, 0 - nMillis));
    }
    else {
      return (makeTimeDuration(nDays, nMillis));
    }
  }
}

void TimeDuration::printTimeDuration(std::ostream* stream) {
  { TimeDuration* date = this;

    *(stream) << "<" << date->timeDurationToString() << ">";
  }
}

CalendarDate* makeDateTime(int year, int month, int day, int hour, int minute, int second, int millis, double timezone) {
  // Create a calendar date with the specified components.  `year' must be
  // the complete year (i.e., a year of 98 is 98 A.D in the 1st century).
  // `timezone' is a real number in the range -12.0 to +14.0 where UTC is zone 0.0;  The number
  // is the number of hours to add to UTC to arrive at local time.
  { int time = (hour * MILLIS_PER_HOUR) + (minute * 60000) + (second * 1000) + millis;

    time = ((int)(time - (timezone * MILLIS_PER_HOUR)));
    return (makeCalendarDate(julianDayToModifiedJulianDay(computeJulianDay(year, month, day)), time));
  }
}

CalendarDate* makeCurrentDateTime() {
  // Create a calendar date with current time and date.
  { int year = NULL_INTEGER;
    int month = NULL_INTEGER;
    int day = NULL_INTEGER;
    Keyword* dow = NULL;
    int hour = NULL_INTEGER;
    int minute = NULL_INTEGER;
    int second = NULL_INTEGER;
    int millisecond = NULL_INTEGER;

    year = getCurrentDateTime(month, day, dow, hour, minute, second, millisecond);
    dow = dow;
    return (makeDateTime(year, month, day, hour, minute, second, millisecond, 0.0));
  }
}

CalendarDate* makeCalendarDate(int day, int time) {
  while (time < 0) {
    time = time + MILLIS_PER_DAY;
    day = day - 1;
  }
  while (time > MILLIS_PER_DAY) {
    time = time - MILLIS_PER_DAY;
    day = day + 1;
  }
  { CalendarDate* self000 = newCalendarDate();

    self000->modifiedJulianDay = day;
    self000->timeMillis = time;
    { CalendarDate* value000 = self000;

      return (value000);
    }
  }
}

TimeDuration* makeTimeDuration(int days, int millis) {
  while (millis < (0 - MILLIS_PER_DAY)) {
    millis = millis + MILLIS_PER_DAY;
    days = days - 1;
  }
  while (millis > MILLIS_PER_DAY) {
    millis = millis - MILLIS_PER_DAY;
    days = days + 1;
  }
  if (days < 0) {
    if (!(millis <= 0)) {
      days = days + 1;
      millis = millis - MILLIS_PER_DAY;
    }
  }
  else if (days > 0) {
    if (!(millis >= 0)) {
      days = days - 1;
      millis = millis + MILLIS_PER_DAY;
    }
  }
  else {
  }
  { TimeDuration* self000 = newTimeDuration();

    self000->days = days;
    self000->millis = millis;
    { TimeDuration* value000 = self000;

      return (value000);
    }
  }
}

int decodeTimeInMillis(int time, int& _Return1, int& _Return2, int& _Return3) {
  // Returns multiple values of hours, minutes, seconds, milliseconds for
  // `time' specified in milliseconds.
  { int millis = (time % 1000);
    int secs = (((time / 1000)) % 60);
    int mins = (((time / 60000)) % 60);
    int hours = (time / MILLIS_PER_HOUR);

    _Return1 = mins;
    _Return2 = secs;
    _Return3 = millis;
    return (hours);
  }
}

int CalendarDate::getCalendarDate(double timezone, int& _Return1, int& _Return2, Keyword*& _Return3) {
  // Returns multiple values of year, month, day and day of week for `date'
  // in `timezone'.  `timezone' is the number of hours added to UTC to get local time.  It
  // is in the range -12.0 to +14.0 where UTC is zone 0.0
  { CalendarDate* date = this;

    if (timezone == NULL_FLOAT) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Timezone not specified in GET-CALENDAR-DATE  Using local zone." << std::endl;
      { int year = NULL_INTEGER;
        int month = NULL_INTEGER;
        int day = NULL_INTEGER;
        Keyword* dow = NULL;

        year = computeCalendarDate(modifiedJulianDayToJulianDay(date->modifiedJulianDay), month, day, dow);
        dow = dow;
        timezone = getLocalTimeZoneForDate(year, month, day, 12, 0, 0);
      }
    }
    { int time = date->timeMillis;
      int timezoneAdjustedTime = ((int)(time + (timezone * MILLIS_PER_HOUR)));
      int dayOffset = 0;

      if (timezoneAdjustedTime < 0) {
        dayOffset = -1;
      }
      else if (timezoneAdjustedTime > MILLIS_PER_DAY) {
        dayOffset = 1;
      }
      else {
      }
      return (computeCalendarDate(modifiedJulianDayToJulianDay(date->modifiedJulianDay + dayOffset), _Return1, _Return2, _Return3));
    }
  }
}

int CalendarDate::getTime(double timezone, int& _Return1, int& _Return2, int& _Return3) {
  // Returns multiple values of hours, minutes, seconds, milliseconds for
  // the calendar date `date' in `timezone'.  `timezone' is the number of hours added to UTC
  // to get local time.  It is in the range -12.0 to +14.0 where UTC is zone 0.0
  { CalendarDate* date = this;

    if (timezone == NULL_FLOAT) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Timezone not specified in GET-TIME.  Using local zone." << std::endl;
      { int year = NULL_INTEGER;
        int month = NULL_INTEGER;
        int day = NULL_INTEGER;
        Keyword* dow = NULL;

        year = computeCalendarDate(modifiedJulianDayToJulianDay(date->modifiedJulianDay), month, day, dow);
        dow = dow;
        timezone = getLocalTimeZoneForDate(year, month, day, 12, 0, 0);
      }
    }
    if (timezone == 0.0) {
      return (decodeTimeInMillis(date->timeMillis, _Return1, _Return2, _Return3));
    }
    else if (timezone < 0.0) {
      return (decodeTimeInMillis(((((int)(date->timeMillis + MILLIS_PER_DAY + (timezone * MILLIS_PER_HOUR)))) % MILLIS_PER_DAY), _Return1, _Return2, _Return3));
    }
    else {
      return (decodeTimeInMillis(((((int)(date->timeMillis + (timezone * MILLIS_PER_HOUR)))) % MILLIS_PER_DAY), _Return1, _Return2, _Return3));
    }
  }
}

DecodedDateTime* CalendarDate::decodeCalendarDate(double timezone) {
  // Returns a decoded time object for `date' interpreted in `timezone'
  // `timezone' is the number of hours added to UTC to get local time.  It is 
  // in the range -12.0 to +14.0 where UTC is zone 0.0
  { CalendarDate* date = this;

    { int hour = NULL_INTEGER;
      int min = NULL_INTEGER;
      int sec = NULL_INTEGER;
      int millis = NULL_INTEGER;

      hour = date->getTime(timezone, min, sec, millis);
      { int year = NULL_INTEGER;
        int month = NULL_INTEGER;
        int day = NULL_INTEGER;
        Keyword* dow = NULL;

        year = date->getCalendarDate(timezone, month, day, dow);
        { DecodedDateTime* self000 = newDecodedDateTime();

          self000->dateTimeMillis = ((double)(millis));
          self000->dateTimeSecond = sec;
          self000->dateTimeMinute = min;
          self000->dateTimeHour = hour;
          self000->dateTimeDay = day;
          self000->dateTimeMonth = month;
          self000->dateTimeYear = year;
          self000->dateTimeZone = timezone;
          self000->dateTimeDow = dow;
          { DecodedDateTime* value000 = self000;

            return (value000);
          }
        }
      }
    }
  }
}

DecodedDateTime* oDEFAULT_DECODED_DATE_TIMEo = NULL;

DecodedDateTime* oNULL_DECODED_DATE_TIMEo = NULL;

CalendarDate* DecodedDateTime::encodeCalendarDate() {
  // Returns a calendar date object for `time-structure'.
  { DecodedDateTime* timeStructure = this;

    return (makeDateTime(((timeStructure->dateTimeYear != NULL_INTEGER) ? timeStructure->dateTimeYear : oDEFAULT_DECODED_DATE_TIMEo->dateTimeYear), ((timeStructure->dateTimeMonth != NULL_INTEGER) ? timeStructure->dateTimeMonth : oDEFAULT_DECODED_DATE_TIMEo->dateTimeMonth), ((timeStructure->dateTimeDay != NULL_INTEGER) ? timeStructure->dateTimeDay : oDEFAULT_DECODED_DATE_TIMEo->dateTimeDay), ((timeStructure->dateTimeHour != NULL_INTEGER) ? timeStructure->dateTimeHour : oDEFAULT_DECODED_DATE_TIMEo->dateTimeHour), ((timeStructure->dateTimeMinute != NULL_INTEGER) ? timeStructure->dateTimeMinute : oDEFAULT_DECODED_DATE_TIMEo->dateTimeMinute), ((timeStructure->dateTimeSecond != NULL_INTEGER) ? timeStructure->dateTimeSecond : oDEFAULT_DECODED_DATE_TIMEo->dateTimeSecond), ((timeStructure->dateTimeMillis != NULL_FLOAT) ? stella::round(timeStructure->dateTimeMillis) : stella::round(oDEFAULT_DECODED_DATE_TIMEo->dateTimeMillis)), ((timeStructure->dateTimeZone != NULL_FLOAT) ? timeStructure->dateTimeZone : oDEFAULT_DECODED_DATE_TIMEo->dateTimeZone)));
  }
}

DecodedTimeDuration* TimeDuration::decodeTimeDuration() {
  { TimeDuration* duration = this;

    if (duration->millis > 0) {
      { DecodedTimeDuration* self000 = newDecodedTimeDuration();

        self000->durationDays = duration->days;
        self000->durationHours = ((duration->millis) / MILLIS_PER_HOUR);
        self000->durationMinutes = ((((duration->millis) % MILLIS_PER_HOUR)) / 60000);
        self000->durationSeconds = ((((duration->millis) % 60000)) / 1000);
        self000->durationMillis = ((double)(((duration->millis) % 1000)));
        { DecodedTimeDuration* value000 = self000;

          return (value000);
        }
      }
    }
    else {
      { DecodedTimeDuration* self001 = newDecodedTimeDuration();

        self001->durationDays = duration->days;
        self001->durationHours = 0 - ((0 - duration->millis) / MILLIS_PER_HOUR);
        self001->durationMinutes = 0 - ((((0 - duration->millis) % MILLIS_PER_HOUR)) / 60000);
        self001->durationSeconds = 0 - ((((0 - duration->millis) % 60000)) / 1000);
        self001->durationMillis = ((double)(0 - ((0 - duration->millis) % 1000)));
        { DecodedTimeDuration* value001 = self001;

          return (value001);
        }
      }
    }
  }
}

TimeDuration* DecodedTimeDuration::encodeTimeDuration() {
  { DecodedTimeDuration* timeStructure = this;

    return (makeTimeDuration(timeStructure->durationDays, ((int)((timeStructure->durationHours * MILLIS_PER_HOUR) + (timeStructure->durationMinutes * 60000) + (timeStructure->durationSeconds * 1000) + timeStructure->durationMillis))));
  }
}

DateTimeObject* timeAdd(DateTimeObject* t1, DateTimeObject* t2) {
  // Add `t1' to `t2'.
  // If one of `t1' or `t2' is a calendar date, then the result is a calendar date.
  // If both `t1' and `t2' are relative dates, then the result is a relative date.
  // `t1' and `t2' cannot both be calendar dates.
  { Surrogate* testValue000 = safePrimaryType(t1);

    if (subtypeOfP(testValue000, SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
      { DateTimeObject* t1000 = t1;
        CalendarDate* t1 = ((CalendarDate*)(t1000));

        { Surrogate* testValue001 = safePrimaryType(t2);

          if (subtypeOfP(testValue001, SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
            { DateTimeObject* t2000 = t2;
              CalendarDate* t2 = ((CalendarDate*)(t2000));

              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "You can't add two calendar dates: " << "`" << t1 << "'" << "  " << "`" << t2 << "'";
                throw *newStellaException(stream000->theStringReader());
              }
            }
          }
          else if (subtypeOfP(testValue001, SGT_DATE_TIME_STELLA_TIME_DURATION)) {
            { DateTimeObject* t2001 = t2;
              TimeDuration* t2 = ((TimeDuration*)(t2001));

              return (makeCalendarDate(t1->modifiedJulianDay + t2->days, t1->timeMillis + t2->millis));
            }
          }
          else {
            { OutputStringStream* stream001 = newOutputStringStream();

              *(stream001->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
              throw *newStellaException(stream001->theStringReader());
            }
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_DATE_TIME_STELLA_TIME_DURATION)) {
      { DateTimeObject* t1001 = t1;
        TimeDuration* t1 = ((TimeDuration*)(t1001));

        { Surrogate* testValue002 = safePrimaryType(t2);

          if (subtypeOfP(testValue002, SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
            { DateTimeObject* t2002 = t2;
              CalendarDate* t2 = ((CalendarDate*)(t2002));

              return (makeCalendarDate(t1->days + t2->modifiedJulianDay, t1->millis + t2->timeMillis));
            }
          }
          else if (subtypeOfP(testValue002, SGT_DATE_TIME_STELLA_TIME_DURATION)) {
            { DateTimeObject* t2003 = t2;
              TimeDuration* t2 = ((TimeDuration*)(t2003));

              return (makeTimeDuration(t1->days + t2->days, t1->millis + t2->millis));
            }
          }
          else {
            { OutputStringStream* stream002 = newOutputStringStream();

              *(stream002->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
              throw *newStellaException(stream002->theStringReader());
            }
          }
        }
      }
    }
    else {
      { OutputStringStream* stream003 = newOutputStringStream();

        *(stream003->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream003->theStringReader());
      }
    }
  }
}

DateTimeObject* timeSubtract(DateTimeObject* t1, DateTimeObject* t2) {
  // Subtract `t2' from `t1'.  If `t1' is a calendar date, then `t2' can
  // be either a calendar date (in which case the return value is a relative date) or it
  // can be a relative date (in which case the return value is a calendar date).  If `t1'
  // is a relative date, then `t2' must also be a relative date and a relative date is returned.
  { Surrogate* testValue000 = safePrimaryType(t1);

    if (subtypeOfP(testValue000, SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
      { DateTimeObject* t1000 = t1;
        CalendarDate* t1 = ((CalendarDate*)(t1000));

        { Surrogate* testValue001 = safePrimaryType(t2);

          if (subtypeOfP(testValue001, SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
            { DateTimeObject* t2000 = t2;
              CalendarDate* t2 = ((CalendarDate*)(t2000));

              return (makeTimeDuration(t1->modifiedJulianDay - t2->modifiedJulianDay, t1->timeMillis - t2->timeMillis));
            }
          }
          else if (subtypeOfP(testValue001, SGT_DATE_TIME_STELLA_TIME_DURATION)) {
            { DateTimeObject* t2001 = t2;
              TimeDuration* t2 = ((TimeDuration*)(t2001));

              return (makeCalendarDate(t1->modifiedJulianDay - t2->days, t1->timeMillis - t2->millis));
            }
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_DATE_TIME_STELLA_TIME_DURATION)) {
      { DateTimeObject* t1001 = t1;
        TimeDuration* t1 = ((TimeDuration*)(t1001));

        { Surrogate* testValue002 = safePrimaryType(t2);

          if (subtypeOfP(testValue002, SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
            { DateTimeObject* t2002 = t2;
              CalendarDate* t2 = ((CalendarDate*)(t2002));

              { OutputStringStream* stream001 = newOutputStringStream();

                *(stream001->nativeStream) << "You can't subtract a calendar date from a relative date: " << "`" << t1 << "'" << "  " << "`" << t2 << "'";
                throw *newStellaException(stream001->theStringReader());
              }
            }
          }
          else if (subtypeOfP(testValue002, SGT_DATE_TIME_STELLA_TIME_DURATION)) {
            { DateTimeObject* t2003 = t2;
              TimeDuration* t2 = ((TimeDuration*)(t2003));

              return (makeTimeDuration(t1->days - t2->days, t1->millis - t2->millis));
            }
          }
          else {
            { OutputStringStream* stream002 = newOutputStringStream();

              *(stream002->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
              throw *newStellaException(stream002->theStringReader());
            }
          }
        }
      }
    }
    else {
      { OutputStringStream* stream003 = newOutputStringStream();

        *(stream003->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream003->theStringReader());
      }
    }
  }
}

TimeDuration* timeMultiply(Object* t1, Object* t2) {
  // Multiplies a relative date by a wrapped number.  One of `t1' or `t2'
  // must be a relative date and the other a wrapped number.
  { Surrogate* testValue000 = safePrimaryType(t1);

    if (subtypeOfP(testValue000, SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
      { Object* t1000 = t1;
        CalendarDate* t1 = ((CalendarDate*)(t1000));

        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Calendar dates cannot be involved in multiplication:  " << "`" << t1 << "'" << "  " << "`" << t2 << "'";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_DATE_TIME_STELLA_TIME_DURATION)) {
      { Object* t1001 = t1;
        TimeDuration* t1 = ((TimeDuration*)(t1001));

        { Surrogate* testValue001 = safePrimaryType(t2);

          if (subtypeOfP(testValue001, SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
            { Object* t2000 = t2;
              CalendarDate* t2 = ((CalendarDate*)(t2000));

              { OutputStringStream* stream001 = newOutputStringStream();

                *(stream001->nativeStream) << "Calendar dates cannot be involved in multiplication:  " << "`" << t1 << "'" << "  " << "`" << t2 << "'";
                throw *newStellaException(stream001->theStringReader());
              }
            }
          }
          else if (subtypeOfP(testValue001, SGT_DATE_TIME_STELLA_TIME_DURATION)) {
            { Object* t2001 = t2;
              TimeDuration* t2 = ((TimeDuration*)(t2001));

              { OutputStringStream* stream002 = newOutputStringStream();

                *(stream002->nativeStream) << "You can't multiply two relative dates: " << "`" << t1 << "'" << "  " << "`" << t2 << "'";
                throw *newStellaException(stream002->theStringReader());
              }
            }
          }
          else if (subtypeOfIntegerP(testValue001)) {
            { Object* t2002 = t2;
              IntegerWrapper* t2 = ((IntegerWrapper*)(t2002));

              return (makeTimeDuration(t1->days * t2->wrapperValue, t1->millis * t2->wrapperValue));
            }
          }
          else if (subtypeOfFloatP(testValue001)) {
            { Object* t2003 = t2;
              FloatWrapper* t2 = ((FloatWrapper*)(t2003));

              return (makeTimeDuration(stella::round(t1->days * t2->wrapperValue), stella::round(t1->millis * t2->wrapperValue)));
            }
          }
          else {
            { OutputStringStream* stream003 = newOutputStringStream();

              *(stream003->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
              throw *newStellaException(stream003->theStringReader());
            }
          }
        }
      }
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { Object* t1002 = t1;
        IntegerWrapper* t1 = ((IntegerWrapper*)(t1002));

        { Surrogate* testValue002 = safePrimaryType(t2);

          if (subtypeOfP(testValue002, SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
            { Object* t2004 = t2;
              CalendarDate* t2 = ((CalendarDate*)(t2004));

              { OutputStringStream* stream004 = newOutputStringStream();

                *(stream004->nativeStream) << "Calendar dates cannot be involved in multiplication:  " << "`" << t1 << "'" << "  " << "`" << t2 << "'";
                throw *newStellaException(stream004->theStringReader());
              }
            }
          }
          else if (subtypeOfP(testValue002, SGT_DATE_TIME_STELLA_TIME_DURATION)) {
            { Object* t2005 = t2;
              TimeDuration* t2 = ((TimeDuration*)(t2005));

              return (makeTimeDuration(t1->wrapperValue * t2->days, t1->wrapperValue * t2->millis));
            }
          }
          else if (subtypeOfP(testValue002, SGT_DATE_TIME_STELLA_NUMBER_WRAPPER)) {
            { Object* t2006 = t2;
              NumberWrapper* t2 = ((NumberWrapper*)(t2006));

              { OutputStringStream* stream005 = newOutputStringStream();

                *(stream005->nativeStream) << "One argument must be a relative date:  " << "`" << t1 << "'" << "  " << "`" << t2 << "'";
                throw *newStellaException(stream005->theStringReader());
              }
            }
          }
          else {
            { OutputStringStream* stream006 = newOutputStringStream();

              *(stream006->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
              throw *newStellaException(stream006->theStringReader());
            }
          }
        }
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { Object* t1003 = t1;
        FloatWrapper* t1 = ((FloatWrapper*)(t1003));

        { Surrogate* testValue003 = safePrimaryType(t2);

          if (subtypeOfP(testValue003, SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
            { Object* t2007 = t2;
              CalendarDate* t2 = ((CalendarDate*)(t2007));

              { OutputStringStream* stream007 = newOutputStringStream();

                *(stream007->nativeStream) << "Calendar dates cannot be involved in multiplication:  " << "`" << t1 << "'" << "  " << "`" << t2 << "'";
                throw *newStellaException(stream007->theStringReader());
              }
            }
          }
          else if (subtypeOfP(testValue003, SGT_DATE_TIME_STELLA_TIME_DURATION)) {
            { Object* t2008 = t2;
              TimeDuration* t2 = ((TimeDuration*)(t2008));

              return (makeTimeDuration(stella::round(t1->wrapperValue * t2->days), stella::round(t1->wrapperValue * t2->millis)));
            }
          }
          else if (subtypeOfP(testValue003, SGT_DATE_TIME_STELLA_NUMBER_WRAPPER)) {
            { Object* t2009 = t2;
              NumberWrapper* t2 = ((NumberWrapper*)(t2009));

              { OutputStringStream* stream008 = newOutputStringStream();

                *(stream008->nativeStream) << "One argument must be a relative date:  " << "`" << t1 << "'" << "  " << "`" << t2 << "'";
                throw *newStellaException(stream008->theStringReader());
              }
            }
          }
          else {
            { OutputStringStream* stream009 = newOutputStringStream();

              *(stream009->nativeStream) << "`" << testValue003 << "'" << " is not a valid case option";
              throw *newStellaException(stream009->theStringReader());
            }
          }
        }
      }
    }
    else {
      { OutputStringStream* stream010 = newOutputStringStream();

        *(stream010->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream010->theStringReader());
      }
    }
  }
}

Object* timeDivide(TimeDuration* t1, Object* t2) {
  // Divides the relative date `t1' by `t2'.  `t2' must be
  // either a relative date or a wrapped number.  If `t2' is a relative date,
  // then the return value will be a wrapped float.  If `t2' is a wrapped number,
  // then the reutrn value will be a relative date.
  { Surrogate* testValue000 = safePrimaryType(t2);

    if (subtypeOfP(testValue000, SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
      { Object* t2000 = t2;
        CalendarDate* t2 = ((CalendarDate*)(t2000));

        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Calendar dates cannot be involved in division:  " << "`" << t1 << "'" << "  " << "`" << t2 << "'";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_DATE_TIME_STELLA_TIME_DURATION)) {
      { Object* t2001 = t2;
        TimeDuration* t2 = ((TimeDuration*)(t2001));

        return (wrapFloat((t1->days + (((double)(t1->millis)) / MILLIS_PER_DAY)) / (t2->days + (((double)(t2->millis)) / MILLIS_PER_DAY))));
      }
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { Object* t2002 = t2;
        IntegerWrapper* t2 = ((IntegerWrapper*)(t2002));

        return (makeTimeDuration(stella::round(((double)(t1->days)) / t2->wrapperValue), stella::round(((double)(t1->millis)) / t2->wrapperValue)));
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { Object* t2003 = t2;
        FloatWrapper* t2 = ((FloatWrapper*)(t2003));

        return (makeTimeDuration(stella::round(t1->days / t2->wrapperValue), stella::round(t1->millis / t2->wrapperValue)));
      }
    }
    else {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream001->theStringReader());
      }
    }
  }
}

Object* defineTimeComparison(Symbol* name, Symbol* operatoR, Symbol* errorP) {
  { Cons* otherwiseClause = ((errorP == SYM_DATE_TIME_STELLA_TRUE) ? listO(7, SYM_DATE_TIME_STELLA_SIGNAL, SYM_DATE_TIME_STELLA_INCOMPATIBLE_QUANTITY_EXCEPTION, wrapString("Can't compare calendar date "), SYM_DATE_TIME_STELLA_T1, wrapString(" with object "), SYM_DATE_TIME_STELLA_T2, NIL) : listO(3, SYM_DATE_TIME_STELLA_RETURN, SYM_DATE_TIME_STELLA_FALSE, NIL));

    return (listO(4, SYM_DATE_TIME_STELLA_PROGN, listO(5, SYM_DATE_TIME_STELLA_DEFMETHOD, cons(name, cons(SYM_DATE_TIME_STELLA_BOOLEAN, NIL)), listO(3, listO(3, SYM_DATE_TIME_STELLA_T1, SYM_DATE_TIME_STELLA_CALENDAR_DATE, NIL), listO(3, SYM_DATE_TIME_STELLA_T2, SYM_DATE_TIME_STELLA_OBJECT, NIL), NIL), listO(5, SYM_DATE_TIME_STELLA_TYPECASE, SYM_DATE_TIME_STELLA_T2, listO(3, SYM_DATE_TIME_STELLA_CALENDAR_DATE, listO(5, SYM_DATE_TIME_STELLA_IF, listO(4, SYM_DATE_TIME_STELLA_e, listO(3, SYM_DATE_TIME_STELLA_MODIFIED_JULIAN_DAY, SYM_DATE_TIME_STELLA_T1, NIL), listO(3, SYM_DATE_TIME_STELLA_MODIFIED_JULIAN_DAY, SYM_DATE_TIME_STELLA_T2, NIL), NIL), listO(3, SYM_DATE_TIME_STELLA_RETURN, cons(operatoR, listO(3, listO(3, SYM_DATE_TIME_STELLA_TIME_MILLIS, SYM_DATE_TIME_STELLA_T1, NIL), listO(3, SYM_DATE_TIME_STELLA_TIME_MILLIS, SYM_DATE_TIME_STELLA_T2, NIL), NIL)), NIL), listO(3, SYM_DATE_TIME_STELLA_RETURN, cons(operatoR, listO(3, listO(3, SYM_DATE_TIME_STELLA_MODIFIED_JULIAN_DAY, SYM_DATE_TIME_STELLA_T1, NIL), listO(3, SYM_DATE_TIME_STELLA_MODIFIED_JULIAN_DAY, SYM_DATE_TIME_STELLA_T2, NIL), NIL)), NIL), NIL), NIL), listO(3, SYM_DATE_TIME_STELLA_OTHERWISE, copyConsList(otherwiseClause), NIL), NIL), NIL), listO(5, SYM_DATE_TIME_STELLA_DEFMETHOD, cons(name, cons(SYM_DATE_TIME_STELLA_BOOLEAN, NIL)), listO(3, listO(3, SYM_DATE_TIME_STELLA_T1, SYM_DATE_TIME_STELLA_TIME_DURATION, NIL), listO(3, SYM_DATE_TIME_STELLA_T2, SYM_DATE_TIME_STELLA_OBJECT, NIL), NIL), listO(5, SYM_DATE_TIME_STELLA_TYPECASE, SYM_DATE_TIME_STELLA_T2, listO(3, SYM_DATE_TIME_STELLA_TIME_DURATION, listO(5, SYM_DATE_TIME_STELLA_IF, listO(4, SYM_DATE_TIME_STELLA_e, listO(3, SYM_DATE_TIME_STELLA_DAYS, SYM_DATE_TIME_STELLA_T1, NIL), listO(3, SYM_DATE_TIME_STELLA_DAYS, SYM_DATE_TIME_STELLA_T2, NIL), NIL), listO(3, SYM_DATE_TIME_STELLA_RETURN, cons(operatoR, listO(3, listO(3, SYM_DATE_TIME_STELLA_MILLIS, SYM_DATE_TIME_STELLA_T1, NIL), listO(3, SYM_DATE_TIME_STELLA_MILLIS, SYM_DATE_TIME_STELLA_T2, NIL), NIL)), NIL), listO(3, SYM_DATE_TIME_STELLA_RETURN, cons(operatoR, listO(3, listO(3, SYM_DATE_TIME_STELLA_DAYS, SYM_DATE_TIME_STELLA_T1, NIL), listO(3, SYM_DATE_TIME_STELLA_DAYS, SYM_DATE_TIME_STELLA_T2, NIL), NIL)), NIL), NIL), NIL), listO(3, SYM_DATE_TIME_STELLA_OTHERWISE, copyConsList(otherwiseClause), NIL), NIL), NIL), NIL));
  }
}

boolean CalendarDate::objectEqlP(Object* t2) {
  { CalendarDate* t1 = this;

    if (subtypeOfP(safePrimaryType(t2), SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
      { Object* t2000 = t2;
        CalendarDate* t2 = ((CalendarDate*)(t2000));

        if (t1->modifiedJulianDay == t2->modifiedJulianDay) {
          return (t1->timeMillis == t2->timeMillis);
        }
        else {
          return (t1->modifiedJulianDay == t2->modifiedJulianDay);
        }
      }
    }
    else {
      return (false);
    }
  }
}

boolean TimeDuration::objectEqlP(Object* t2) {
  { TimeDuration* t1 = this;

    if (subtypeOfP(safePrimaryType(t2), SGT_DATE_TIME_STELLA_TIME_DURATION)) {
      { Object* t2000 = t2;
        TimeDuration* t2 = ((TimeDuration*)(t2000));

        if (t1->days == t2->days) {
          return (t1->millis == t2->millis);
        }
        else {
          return (t1->days == t2->days);
        }
      }
    }
    else {
      return (false);
    }
  }
}

boolean CalendarDate::lessP(Object* t2) {
  { CalendarDate* t1 = this;

    if (subtypeOfP(safePrimaryType(t2), SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
      { Object* t2000 = t2;
        CalendarDate* t2 = ((CalendarDate*)(t2000));

        if (t1->modifiedJulianDay == t2->modifiedJulianDay) {
          return (t1->timeMillis < t2->timeMillis);
        }
        else {
          return (t1->modifiedJulianDay < t2->modifiedJulianDay);
        }
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't compare calendar date " << "`" << t1 << "'" << " with object " << "`" << t2 << "'";
        throw *newIncompatibleQuantityException(stream000->theStringReader());
      }
    }
  }
}

boolean TimeDuration::lessP(Object* t2) {
  { TimeDuration* t1 = this;

    if (subtypeOfP(safePrimaryType(t2), SGT_DATE_TIME_STELLA_TIME_DURATION)) {
      { Object* t2000 = t2;
        TimeDuration* t2 = ((TimeDuration*)(t2000));

        if (t1->days == t2->days) {
          return (t1->millis < t2->millis);
        }
        else {
          return (t1->days < t2->days);
        }
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't compare calendar date " << "`" << t1 << "'" << " with object " << "`" << t2 << "'";
        throw *newIncompatibleQuantityException(stream000->theStringReader());
      }
    }
  }
}

boolean CalendarDate::greaterP(Object* t2) {
  { CalendarDate* t1 = this;

    if (subtypeOfP(safePrimaryType(t2), SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
      { Object* t2000 = t2;
        CalendarDate* t2 = ((CalendarDate*)(t2000));

        if (t1->modifiedJulianDay == t2->modifiedJulianDay) {
          return (t1->timeMillis > t2->timeMillis);
        }
        else {
          return (t1->modifiedJulianDay > t2->modifiedJulianDay);
        }
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't compare calendar date " << "`" << t1 << "'" << " with object " << "`" << t2 << "'";
        throw *newIncompatibleQuantityException(stream000->theStringReader());
      }
    }
  }
}

boolean TimeDuration::greaterP(Object* t2) {
  { TimeDuration* t1 = this;

    if (subtypeOfP(safePrimaryType(t2), SGT_DATE_TIME_STELLA_TIME_DURATION)) {
      { Object* t2000 = t2;
        TimeDuration* t2 = ((TimeDuration*)(t2000));

        if (t1->days == t2->days) {
          return (t1->millis > t2->millis);
        }
        else {
          return (t1->days > t2->days);
        }
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't compare calendar date " << "`" << t1 << "'" << " with object " << "`" << t2 << "'";
        throw *newIncompatibleQuantityException(stream000->theStringReader());
      }
    }
  }
}

boolean CalendarDate::lessEqualP(Object* t2) {
  { CalendarDate* t1 = this;

    if (subtypeOfP(safePrimaryType(t2), SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
      { Object* t2000 = t2;
        CalendarDate* t2 = ((CalendarDate*)(t2000));

        if (t1->modifiedJulianDay == t2->modifiedJulianDay) {
          return (t1->timeMillis <= t2->timeMillis);
        }
        else {
          return (t1->modifiedJulianDay <= t2->modifiedJulianDay);
        }
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't compare calendar date " << "`" << t1 << "'" << " with object " << "`" << t2 << "'";
        throw *newIncompatibleQuantityException(stream000->theStringReader());
      }
    }
  }
}

boolean TimeDuration::lessEqualP(Object* t2) {
  { TimeDuration* t1 = this;

    if (subtypeOfP(safePrimaryType(t2), SGT_DATE_TIME_STELLA_TIME_DURATION)) {
      { Object* t2000 = t2;
        TimeDuration* t2 = ((TimeDuration*)(t2000));

        if (t1->days == t2->days) {
          return (t1->millis <= t2->millis);
        }
        else {
          return (t1->days <= t2->days);
        }
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't compare calendar date " << "`" << t1 << "'" << " with object " << "`" << t2 << "'";
        throw *newIncompatibleQuantityException(stream000->theStringReader());
      }
    }
  }
}

boolean CalendarDate::greaterEqualP(Object* t2) {
  { CalendarDate* t1 = this;

    if (subtypeOfP(safePrimaryType(t2), SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
      { Object* t2000 = t2;
        CalendarDate* t2 = ((CalendarDate*)(t2000));

        if (t1->modifiedJulianDay == t2->modifiedJulianDay) {
          return (t1->timeMillis >= t2->timeMillis);
        }
        else {
          return (t1->modifiedJulianDay >= t2->modifiedJulianDay);
        }
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't compare calendar date " << "`" << t1 << "'" << " with object " << "`" << t2 << "'";
        throw *newIncompatibleQuantityException(stream000->theStringReader());
      }
    }
  }
}

boolean TimeDuration::greaterEqualP(Object* t2) {
  { TimeDuration* t1 = this;

    if (subtypeOfP(safePrimaryType(t2), SGT_DATE_TIME_STELLA_TIME_DURATION)) {
      { Object* t2000 = t2;
        TimeDuration* t2 = ((TimeDuration*)(t2000));

        if (t1->days == t2->days) {
          return (t1->millis >= t2->millis);
        }
        else {
          return (t1->days >= t2->days);
        }
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't compare calendar date " << "`" << t1 << "'" << " with object " << "`" << t2 << "'";
        throw *newIncompatibleQuantityException(stream000->theStringReader());
      }
    }
  }
}

void fillInDateSubstitution(KeyValueList* substitutionList) {
  // Fill in `substitution-list' with template variable substitions
  // for the names YEAR and DATE which correspond to the current year and date.
  // These substitutions can then be used with `substitute-template-variables-in-string'
  // DEPRECATED.  Use `add-date-subsitution' or `add-current-date-substitution' instead.
  { int year = NULL_INTEGER;
    int month = NULL_INTEGER;
    int day = NULL_INTEGER;
    Keyword* dow = NULL;

    year = makeCurrentDateTime()->getCalendarDate(getLocalTimeZone(), month, day, dow);
    dow = dow;
    substitutionList->insertAt(wrapString("YEAR"), wrapString(integerToString(((long long int)(year)))));
    substitutionList->insertAt(wrapString("DATE"), wrapString(stringConcatenate(formatWithPadding(integerToString(((long long int)(day))), 2, '0', KWD_DATE_TIME_RIGHT, false), "-", 3, ((StringWrapper*)((oMONTH_ABBREVIATION_VECTORo->theArray)[month]))->wrapperValue, "-", integerToString(((long long int)(year))))));
  }
}

void addDateSubstitution(CalendarDate* date, KeyValueList* substitutionList) {
  // Fill in `substitution-list' with template variable substitions
  // for the names YEAR, MONTH, MON, DAY, HOUR, MINUTE, SECOND, TIMEZONE,
  // DAY-OF-WEEK, DOW with their values for `date'.  Also, pre-formatted
  // DATE, TIME and ISO8601 variables are set.
  // 
  // TIMEZONE is in the format "{+|-}hhmm".  MONTH is the full English
  // month name and MON is the numeric month.  DAY-OF-WEEK is an English
  // string and DOW is the first three letters.  Minutes and seconds are
  // zero-padded.
  // 
  // These substitutions can be used with `substitute-template-variables-in-string'
  { double tz = getLocalTimeZone();

    { int year = NULL_INTEGER;
      int month = NULL_INTEGER;
      int day = NULL_INTEGER;
      Keyword* dow = NULL;

      year = date->getCalendarDate(tz, month, day, dow);
      substitutionList->insertAt(wrapString("YEAR"), wrapString(integerToString(((long long int)(year)))));
      substitutionList->insertAt(wrapString("MONTH"), ((StringWrapper*)((oMONTH_NAME_VECTORo->theArray)[month])));
      substitutionList->insertAt(wrapString("MON"), wrapString(integerToString(((long long int)(month)))));
      substitutionList->insertAt(wrapString("DAY"), wrapString(integerToString(((long long int)(day)))));
      substitutionList->insertAt(wrapString("DAY-OF-WEEK"), wrapString(stringCapitalize(dow->symbolName)));
      substitutionList->insertAt(wrapString("DOW"), wrapString(stringCapitalize(stringSubsequence(dow->symbolName, 0, 3))));
      substitutionList->insertAt(wrapString("DATE"), wrapString(stringConcatenate(formatWithPadding(integerToString(((long long int)(day))), 2, '0', KWD_DATE_TIME_RIGHT, false), "-", 3, ((StringWrapper*)((oMONTH_ABBREVIATION_VECTORo->theArray)[month]))->wrapperValue, "-", integerToString(((long long int)(year))))));
    }
    { int hour = NULL_INTEGER;
      int min = NULL_INTEGER;
      int sec = NULL_INTEGER;
      int millis = NULL_INTEGER;

      hour = date->getTime(tz, min, sec, millis);
      millis = millis;
      substitutionList->insertAt(wrapString("HOUR"), wrapString(integerToString(((long long int)(hour)))));
      substitutionList->insertAt(wrapString("MINUTE"), wrapString(formatWithPadding(integerToString(((long long int)(min))), 2, '0', KWD_DATE_TIME_RIGHT, false)));
      substitutionList->insertAt(wrapString("SECOND"), wrapString(formatWithPadding(integerToString(((long long int)(sec))), 2, '0', KWD_DATE_TIME_RIGHT, false)));
      substitutionList->insertAt(wrapString("TIME"), wrapString(stringConcatenate(integerToString(((long long int)(hour))), ":", 3, formatWithPadding(integerToString(((long long int)(min))), 2, '0', KWD_DATE_TIME_RIGHT, false), ":", formatWithPadding(integerToString(((long long int)(sec))), 2, '0', KWD_DATE_TIME_RIGHT, false))));
    }
    substitutionList->insertAt(wrapString("TIMEZONE"), wrapString(timeZoneFormat60(tz, false)));
    substitutionList->insertAt(wrapString("IOS8601"), wrapString(date->calendarDateToIso8601String(tz, true)));
  }
}

void addCurrentDateSubstitution(KeyValueList* substitutionList) {
  // Fill in `substitution-list' with date information for the current
  // date and time.  See `add-date-substitution' for details.
  addDateSubstitution(makeCurrentDateTime(), substitutionList);
}

// Handler functions indexed by the character code of their control character.
Vector* oFORMAT_DATE_HANDLERSo = NULL;

void formatDatePrintString(const char* string, char flag, int start, int end, OutputStream* stream) {
  if (end < 0) {
    end = strlen(string);
  }
  end = end - 1;
  switch (flag) {
    case '^': 
      { int i = NULL_INTEGER;
        int iter000 = start;
        int upperBound000 = end;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter000 <= upperBound000); 
              iter000 = iter000 + 1) {
          i = iter000;
          *(stream->nativeStream) << oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) (string[i]))];
        }
      }
      break;
    case ',': 
      { int i = NULL_INTEGER;
        int iter001 = start;
        int upperBound001 = end;
        boolean unboundedP001 = upperBound001 == NULL_INTEGER;

        for  (; unboundedP001 ||
                  (iter001 <= upperBound001); 
              iter001 = iter001 + 1) {
          i = iter001;
          *(stream->nativeStream) << oCHARACTER_DOWNCASE_TABLEo[((int)(unsigned char) (string[i]))];
        }
      }
      break;
    default:
      *(stream->nativeStream) << oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) (string[start]))];
      { int i = NULL_INTEGER;
        int iter002 = start + 1;
        int upperBound002 = end;
        boolean unboundedP002 = upperBound002 == NULL_INTEGER;

        for  (; unboundedP002 ||
                  (iter002 <= upperBound002); 
              iter002 = iter002 + 1) {
          i = iter002;
          *(stream->nativeStream) << oCHARACTER_DOWNCASE_TABLEo[((int)(unsigned char) (string[i]))];
        }
      }
      break;
  }
}

void formatDatePrintTwoDigitNumber(int number, char flag, OutputStream* stream) {
  if (number <= 9) {
    if (flag == NULL_CHARACTER) {
      flag = '0';
    }
    switch (flag) {
      case '_': 
        *(stream->nativeStream) << " ";
        break;
      case '0': 
      case '\0': 
        *(stream->nativeStream) << "0";
        break;
      default:
        break;
    }
  }
  *(stream->nativeStream) << number;
}

void formatDateAbbreviatedWeekdayHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  cont = cont;
  formatDatePrintString(date->dateTimeDow->symbolName, flag, 0, 3, stream);
}

void formatDateFullWeekdayHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  cont = cont;
  formatDatePrintString(date->dateTimeDow->symbolName, flag, 0, -1, stream);
}

void formatDateAbbreviatedMonthHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  cont = cont;
  formatDatePrintString(((StringWrapper*)((oMONTH_ABBREVIATION_VECTORo->theArray)[(date->dateTimeMonth)]))->wrapperValue, flag, 0, -1, stream);
}

void formatDateFullMonthHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  cont = cont;
  formatDatePrintString(((StringWrapper*)((oMONTH_NAME_VECTORo->theArray)[(date->dateTimeMonth)]))->wrapperValue, flag, 0, -1, stream);
}

void formatDateDayOfMonthHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  cont = cont;
  formatDatePrintTwoDigitNumber(date->dateTimeDay, flag, stream);
}

void formatDateFullDateHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  {
    cont = cont;
    flag = flag;
  }
  formatDateMonthHandler(date, 'm', '0', stream);
  *(stream->nativeStream) << "/";
  formatDateDayOfMonthHandler(date, 'd', '0', stream);
  *(stream->nativeStream) << "/";
  formatDateTwoDigitYearHandler(date, 'y', '0', stream);
}

void formatDate24HourHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  cont = cont;
  formatDatePrintTwoDigitNumber(date->dateTimeHour, flag, stream);
}

void formatDate12HourHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  cont = cont;
  { int hour = integerMod(date->dateTimeHour - 1, 12) + 1;

    formatDatePrintTwoDigitNumber(hour, flag, stream);
  }
}

void formatDateMonthHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  cont = cont;
  formatDatePrintTwoDigitNumber(date->dateTimeMonth, flag, stream);
}

void formatDateMinuteHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  cont = cont;
  formatDatePrintTwoDigitNumber(date->dateTimeMinute, flag, stream);
}

void formatDateAmPmHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  cont = cont;
  { const char* ampm = ((date->dateTimeHour < 12) ? "AM" : "PM");

    if (flag == NULL_CHARACTER) {
      flag = '^';
    }
    formatDatePrintString(ampm, flag, 0, 2, stream);
  }
}

void formatDate12HourClockTimeHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  {
    cont = cont;
    flag = flag;
  }
  formatDate12HourHandler(date, 'I', '0', stream);
  *(stream->nativeStream) << ":";
  formatDateMinuteHandler(date, 'M', '0', stream);
  *(stream->nativeStream) << ":";
  formatDateSecondHandler(date, 'S', '0', stream);
  *(stream->nativeStream) << " ";
  formatDateAmPmHandler(date, 'p', '^', stream);
}

void formatDate24HourAndMinuteTimeHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  {
    cont = cont;
    flag = flag;
  }
  formatDate24HourHandler(date, 'H', '0', stream);
  *(stream->nativeStream) << ":";
  formatDateMinuteHandler(date, 'M', '0', stream);
}

void formatDateSecondHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  cont = cont;
  formatDatePrintTwoDigitNumber(date->dateTimeSecond, flag, stream);
}

void formatDateFullTimeHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  {
    cont = cont;
    flag = flag;
  }
  formatDate24HourHandler(date, 'H', '0', stream);
  *(stream->nativeStream) << ":";
  formatDateMinuteHandler(date, 'M', '0', stream);
  *(stream->nativeStream) << ":";
  formatDateSecondHandler(date, 'S', '0', stream);
}

void formatDateTwoDigitYearHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  {
    cont = cont;
    flag = flag;
  }
  { int year = integerMod(date->dateTimeYear, 100);

    formatDatePrintTwoDigitNumber(year, '0', stream);
  }
}

void formatDateYearHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  cont = cont;
  if (date->dateTimeYear < 1000) {
    if (flag == NULL_CHARACTER) {
      flag = '0';
    }
    switch (flag) {
      case '_': 
        *(stream->nativeStream) << formatWithPadding(integerToString(((long long int)(date->dateTimeYear))), 4, ' ', KWD_DATE_TIME_RIGHT, false);
        return;
      case '0': 
      case '\0': 
        *(stream->nativeStream) << formatWithPadding(integerToString(((long long int)(date->dateTimeYear))), 4, '0', KWD_DATE_TIME_RIGHT, false);
        return;
      default:
        break;
    }
  }
  *(stream->nativeStream) << date->dateTimeYear;
}

void formatDateNumericTimeZoneHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  cont = cont;
  *(stream->nativeStream) << timeZoneFormat60(date->dateTimeZone, flag == ':');
}

void formatDateTimeAlphabeticZoneHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  {
    stream = stream;
    flag = flag;
    date = date;
  }
  { OutputStringStream* stream000 = newOutputStringStream();

    *(stream000->nativeStream) << "format-date: control not yet implemented: " << "`" << cont << "'";
    throw *newStellaException(stream000->theStringReader());
  }
}

void formatDateErrorHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream) {
  {
    stream = stream;
    flag = flag;
    date = date;
  }
  { OutputStringStream* stream000 = newOutputStringStream();

    *(stream000->nativeStream) << "format-date: illegal control character: " << "`" << cont << "'";
    throw *newStellaException(stream000->theStringReader());
  }
}

void formatDateToStream(Object* date, Object* timezone, const char* control, OutputStream* stream) {
  // Perform formatted printing of `date' relative to `timezone' onto `stream'.  `date'
  // has to be either a calendar-date or a decoded-date-time object.  `timezone' can be null to indicate
  // the local timezone, or a float or supported timezone name.  `control' is a format control string whose
  // characters are printed literally, unless they are a %-code such as one of these (inspired by the codes
  // supported by the Unix `date' command):
  //        %%     a literal %
  //        %a     abbreviated weekday name (e.g., Sun)
  //        %A     full weekday name (e.g., Sunday)
  //        %b     abbreviated month name (e.g., Jan)
  //        %B     full month name (e.g., January)
  //        %d     day of month (e.g., 01)
  //        %D     date; same as %m/%d/%y
  //        %F     full date; same as %Y-%m-%d
  //        %H     hour (00..23)
  //        %I     hour (01..12)
  //        %m     month (01..12)
  //        %M     minute (00..59)
  //        %p     either AM or PM
  //        %r     12-hour clock time (e.g., 11:11:04 PM)
  //        %R     24-hour hour and minute; same as %H:%M
  //        %S     second (00..60)
  //        %T     time; same as %H:%M:%S
  //        %y     last two digits of year (00..99)
  //        %Y     year
  //        %z     +hhmm numeric time zone (e.g., -0400)
  //        %:z    +hhmm numeric time zone (e.g., -04:00)
  //        %Z     alphabetic time zone abbreviation (e.g., EDT)
  // By default, numeric fields are padded with zeroes. The following optional flags may follow '%':
  //        -      (hyphen) do not pad the field
  //        _      (underscore) pad with spaces
  //        0      (zero) pad with zeros
  //        ^      use upper case if possible
  //        ,      use lower case if possible
  { double decodedzone = getLocalTimeZone();
    DecodedDateTime* decodeddate = NULL;
    int end = strlen(control) - 1;
    int i = 0;
    char ch = NULL_CHARACTER;
    char flag = NULL_CHARACTER;

    if (((boolean)(timezone))) {
      { FloatWrapper* deczone = zone(timezone);

        if ((!((boolean)(deczone))) &&
            stringP(timezone)) {
          deczone = zone(wrapString(stringDowncase(((StringWrapper*)(timezone))->wrapperValue)));
        }
        if (((boolean)(deczone))) {
          decodedzone = deczone->wrapperValue;
        }
      }
    }
    { Surrogate* testValue000 = safePrimaryType(date);

      if (subtypeOfP(testValue000, SGT_DATE_TIME_STELLA_CALENDAR_DATE)) {
        { Object* date000 = date;
          CalendarDate* date = ((CalendarDate*)(date000));

          decodeddate = date->decodeCalendarDate(decodedzone);
        }
      }
      else if (subtypeOfP(testValue000, SGT_DATE_TIME_STELLA_DECODED_DATE_TIME)) {
        { Object* date001 = date;
          DecodedDateTime* date = ((DecodedDateTime*)(date001));

          decodeddate = date;
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "format-date: unsupported date type: " << "`" << date->primaryType() << "'";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    while (i <= end) {
      ch = control[i];
      if (ch == '%') {
        if (i == end) {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "format-date: end of control string encountered: " << "`" << control << "'";
            throw *newStellaException(stream001->theStringReader());
          }
        }
        i = i + 1;
        flag = NULL_CHARACTER;
        ch = control[i];
        if (ch == '%') {
          *(stream->nativeStream) << "%";
          i = i + 1;
          continue;
        }
        if (!(oCHARACTER_TYPE_TABLEo[(int)(unsigned char) ch] == KWD_DATE_TIME_LETTER)) {
          if (i == end) {
            { OutputStringStream* stream002 = newOutputStringStream();

              *(stream002->nativeStream) << "format-date: end of control string encountered: " << "`" << control << "'";
              throw *newStellaException(stream002->theStringReader());
            }
          }
          i = i + 1;
          flag = ch;
          ch = control[i];
          if (stringPosition("-_0^,:", flag, 0) == NULL_INTEGER) {
            { OutputStringStream* stream003 = newOutputStringStream();

              *(stream003->nativeStream) << "format-date: illegal control flag: " << "`" << flag << "'";
              throw *newStellaException(stream003->theStringReader());
            }
          }
          if (!(oCHARACTER_TYPE_TABLEo[(int)(unsigned char) ch] == KWD_DATE_TIME_LETTER)) {
            { OutputStringStream* stream004 = newOutputStringStream();

              *(stream004->nativeStream) << "format-date: illegal control character: " << "`" << ch << "'";
              throw *newStellaException(stream004->theStringReader());
            }
          }
        }
        ((void  (*) (DecodedDateTime*, char, char, OutputStream*))((FunctionCodeWrapper*)((oFORMAT_DATE_HANDLERSo->theArray)[((int)(unsigned char) ch)]))->wrapperValue)(decodeddate, ch, flag, stream);
      }
      else {
        *(stream->nativeStream) << ch;
      }
      i = i + 1;
    }
  }
}

const char* formatDate(Object* date, Object* timezone, const char* control) {
  // Format `date' just like `format-date-to-stream' (which see), but return the result as a string.
  { OutputStringStream* out = newOutputStringStream();

    formatDateToStream(date, timezone, control, out);
    return (out->theStringReader());
  }
}

void helpStartupDateTime1() {
  {
    KWD_DATE_TIME_MONDAY = ((Keyword*)(internRigidSymbolWrtModule("MONDAY", NULL, 2)));
    KWD_DATE_TIME_TUESDAY = ((Keyword*)(internRigidSymbolWrtModule("TUESDAY", NULL, 2)));
    KWD_DATE_TIME_WEDNESDAY = ((Keyword*)(internRigidSymbolWrtModule("WEDNESDAY", NULL, 2)));
    KWD_DATE_TIME_THURSDAY = ((Keyword*)(internRigidSymbolWrtModule("THURSDAY", NULL, 2)));
    KWD_DATE_TIME_FRIDAY = ((Keyword*)(internRigidSymbolWrtModule("FRIDAY", NULL, 2)));
    KWD_DATE_TIME_SATURDAY = ((Keyword*)(internRigidSymbolWrtModule("SATURDAY", NULL, 2)));
    KWD_DATE_TIME_SUNDAY = ((Keyword*)(internRigidSymbolWrtModule("SUNDAY", NULL, 2)));
    KWD_DATE_TIME_NEW_MOON = ((Keyword*)(internRigidSymbolWrtModule("NEW-MOON", NULL, 2)));
    KWD_DATE_TIME_FIRST_QUARTER = ((Keyword*)(internRigidSymbolWrtModule("FIRST-QUARTER", NULL, 2)));
    KWD_DATE_TIME_FULL_MOON = ((Keyword*)(internRigidSymbolWrtModule("FULL-MOON", NULL, 2)));
    KWD_DATE_TIME_LAST_QUARTER = ((Keyword*)(internRigidSymbolWrtModule("LAST-QUARTER", NULL, 2)));
    KWD_DATE_TIME_RIGHT = ((Keyword*)(internRigidSymbolWrtModule("RIGHT", NULL, 2)));
    SGT_DATE_TIME_STELLA_DECODED_DATE_TIME = ((Surrogate*)(internRigidSymbolWrtModule("DECODED-DATE-TIME", NULL, 1)));
    SYM_DATE_TIME_STELLA_DATE_TIME_MILLIS = ((Symbol*)(internRigidSymbolWrtModule("DATE-TIME-MILLIS", NULL, 0)));
    SYM_DATE_TIME_STELLA_DATE_TIME_SECOND = ((Symbol*)(internRigidSymbolWrtModule("DATE-TIME-SECOND", NULL, 0)));
    SYM_DATE_TIME_STELLA_DATE_TIME_MINUTE = ((Symbol*)(internRigidSymbolWrtModule("DATE-TIME-MINUTE", NULL, 0)));
    SYM_DATE_TIME_STELLA_DATE_TIME_HOUR = ((Symbol*)(internRigidSymbolWrtModule("DATE-TIME-HOUR", NULL, 0)));
    SYM_DATE_TIME_STELLA_DATE_TIME_DAY = ((Symbol*)(internRigidSymbolWrtModule("DATE-TIME-DAY", NULL, 0)));
    SYM_DATE_TIME_STELLA_DATE_TIME_MONTH = ((Symbol*)(internRigidSymbolWrtModule("DATE-TIME-MONTH", NULL, 0)));
    SYM_DATE_TIME_STELLA_DATE_TIME_YEAR = ((Symbol*)(internRigidSymbolWrtModule("DATE-TIME-YEAR", NULL, 0)));
    SYM_DATE_TIME_STELLA_DATE_TIME_ZONE = ((Symbol*)(internRigidSymbolWrtModule("DATE-TIME-ZONE", NULL, 0)));
    SYM_DATE_TIME_STELLA_DATE_TIME_DOW = ((Symbol*)(internRigidSymbolWrtModule("DATE-TIME-DOW", NULL, 0)));
    KWD_DATE_TIME_PRESERVE = ((Keyword*)(internRigidSymbolWrtModule("PRESERVE", NULL, 2)));
    SGT_DATE_TIME_STELLA_DECODED_TIME_DURATION = ((Surrogate*)(internRigidSymbolWrtModule("DECODED-TIME-DURATION", NULL, 1)));
    SYM_DATE_TIME_STELLA_DURATION_MILLIS = ((Symbol*)(internRigidSymbolWrtModule("DURATION-MILLIS", NULL, 0)));
    SYM_DATE_TIME_STELLA_DURATION_SECONDS = ((Symbol*)(internRigidSymbolWrtModule("DURATION-SECONDS", NULL, 0)));
    SYM_DATE_TIME_STELLA_DURATION_MINUTES = ((Symbol*)(internRigidSymbolWrtModule("DURATION-MINUTES", NULL, 0)));
    SYM_DATE_TIME_STELLA_DURATION_HOURS = ((Symbol*)(internRigidSymbolWrtModule("DURATION-HOURS", NULL, 0)));
    SYM_DATE_TIME_STELLA_DURATION_DAYS = ((Symbol*)(internRigidSymbolWrtModule("DURATION-DAYS", NULL, 0)));
    SGT_DATE_TIME_STELLA_CALENDAR_DATE = ((Surrogate*)(internRigidSymbolWrtModule("CALENDAR-DATE", NULL, 1)));
    SYM_DATE_TIME_STELLA_MODIFIED_JULIAN_DAY = ((Symbol*)(internRigidSymbolWrtModule("MODIFIED-JULIAN-DAY", NULL, 0)));
    SYM_DATE_TIME_STELLA_TIME_MILLIS = ((Symbol*)(internRigidSymbolWrtModule("TIME-MILLIS", NULL, 0)));
    SGT_DATE_TIME_STELLA_TIME_DURATION = ((Surrogate*)(internRigidSymbolWrtModule("TIME-DURATION", NULL, 1)));
    SYM_DATE_TIME_STELLA_DAYS = ((Symbol*)(internRigidSymbolWrtModule("DAYS", NULL, 0)));
    SYM_DATE_TIME_STELLA_MILLIS = ((Symbol*)(internRigidSymbolWrtModule("MILLIS", NULL, 0)));
    SGT_DATE_TIME_STELLA_NUMBER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER-WRAPPER", NULL, 1)));
    SYM_DATE_TIME_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    SYM_DATE_TIME_STELLA_SIGNAL = ((Symbol*)(internRigidSymbolWrtModule("SIGNAL", NULL, 0)));
    SYM_DATE_TIME_STELLA_INCOMPATIBLE_QUANTITY_EXCEPTION = ((Symbol*)(internRigidSymbolWrtModule("INCOMPATIBLE-QUANTITY-EXCEPTION", NULL, 0)));
    SYM_DATE_TIME_STELLA_T1 = ((Symbol*)(internRigidSymbolWrtModule("T1", NULL, 0)));
    SYM_DATE_TIME_STELLA_T2 = ((Symbol*)(internRigidSymbolWrtModule("T2", NULL, 0)));
    SYM_DATE_TIME_STELLA_RETURN = ((Symbol*)(internRigidSymbolWrtModule("RETURN", NULL, 0)));
    SYM_DATE_TIME_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", NULL, 0)));
    SYM_DATE_TIME_STELLA_PROGN = ((Symbol*)(internRigidSymbolWrtModule("PROGN", NULL, 0)));
    SYM_DATE_TIME_STELLA_DEFMETHOD = ((Symbol*)(internRigidSymbolWrtModule("DEFMETHOD", NULL, 0)));
    SYM_DATE_TIME_STELLA_BOOLEAN = ((Symbol*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 0)));
    SYM_DATE_TIME_STELLA_CALENDAR_DATE = ((Symbol*)(internRigidSymbolWrtModule("CALENDAR-DATE", NULL, 0)));
    SYM_DATE_TIME_STELLA_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("OBJECT", NULL, 0)));
    SYM_DATE_TIME_STELLA_TYPECASE = ((Symbol*)(internRigidSymbolWrtModule("TYPECASE", NULL, 0)));
    SYM_DATE_TIME_STELLA_IF = ((Symbol*)(internRigidSymbolWrtModule("IF", NULL, 0)));
    SYM_DATE_TIME_STELLA_e = ((Symbol*)(internRigidSymbolWrtModule("=", NULL, 0)));
    SYM_DATE_TIME_STELLA_OTHERWISE = ((Symbol*)(internRigidSymbolWrtModule("OTHERWISE", NULL, 0)));
    SYM_DATE_TIME_STELLA_TIME_DURATION = ((Symbol*)(internRigidSymbolWrtModule("TIME-DURATION", NULL, 0)));
    KWD_DATE_TIME_LETTER = ((Keyword*)(internRigidSymbolWrtModule("LETTER", NULL, 2)));
    SYM_DATE_TIME_STELLA_STARTUP_DATE_TIME = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-DATE-TIME", NULL, 0)));
    SYM_DATE_TIME_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupDateTime2() {
  {
    defineFunctionObject("COMPUTE-JULIAN-DAY", "(DEFUN (COMPUTE-JULIAN-DAY INTEGER) ((YYYY INTEGER) (MM INTEGER) (DD INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the Julian day that starts at noon on yyyy-mm-dd.\n`yyyy' is the year.  `mm' is the month.  `dd' is the day of month.\nNegative years are B.C.  Remember there is no year zero.\")", ((cpp_function_code)(&computeJulianDay)), NULL);
    defineFunctionObject("JULIAN-DAY-TO-MODIFIED-JULIAN-DAY", "(DEFUN (JULIAN-DAY-TO-MODIFIED-JULIAN-DAY INTEGER) ((JULIAN-DAY INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the modified Julian day during which `julian-day'starts at noon.\")", ((cpp_function_code)(&julianDayToModifiedJulianDay)), NULL);
    defineFunctionObject("MODIFIED-JULIAN-DAY-TO-JULIAN-DAY", "(DEFUN (MODIFIED-JULIAN-DAY-TO-JULIAN-DAY INTEGER) ((MODIFIED-JULIAN-DAY INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the modified Julian day during which `julian-day'starts at noon.\")", ((cpp_function_code)(&modifiedJulianDayToJulianDay)), NULL);
    defineFunctionObject("COMPUTE-DAY-OF-WEEK-JULIAN", "(DEFUN (COMPUTE-DAY-OF-WEEK-JULIAN KEYWORD) ((JULIAN-DAY INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the day of the week for julian-day\")", ((cpp_function_code)(&computeDayOfWeekJulian)), NULL);
    defineFunctionObject("COMPUTE-DAY-OF-WEEK", "(DEFUN (COMPUTE-DAY-OF-WEEK KEYWORD) ((YYYY INTEGER) (MM INTEGER) (DD INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the day of the week for yyyy-mm-dd.\")", ((cpp_function_code)(&computeDayOfWeek)), NULL);
    defineFunctionObject("COMPUTE-NEXT-MOON-PHASE", "(DEFUN (COMPUTE-NEXT-MOON-PHASE INTEGER FLOAT) ((N INTEGER) (PHASE KEYWORD)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the Julian Day and fraction of day of the Nth occurence\nsince January 1, 1900 of moon PHASE.  PHASE is one of :NEW-MOON, :FIRST-QUARTER,\n:FULL-MOON, :LAST-QUARTER\")", ((cpp_function_code)(&computeNextMoonPhase)), NULL);
    defineFunctionObject("COMPUTE-CALENDAR-DATE", "(DEFUN (COMPUTE-CALENDAR-DATE INTEGER INTEGER INTEGER KEYWORD) ((JULIAN-DAY INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the YEAR, MONTH, DAY, DAY-OF-WEEK on which the given\n`julian-day' begins at noon.\")", ((cpp_function_code)(&computeCalendarDate)), NULL);
    defineFunctionObject("GET-CURRENT-DATE-TIME", "(DEFUN (GET-CURRENT-DATE-TIME INTEGER INTEGER INTEGER KEYWORD INTEGER INTEGER INTEGER INTEGER) () :PUBLIC? TRUE :DOCUMENTATION \"Returns the current time in UTC as multiple values of\nyear month day day-of-week hour minute second millisecond.  Currently\nmillisecond will always be zero (even in Java where it is technically available).\")", ((cpp_function_code)(&getCurrentDateTime)), NULL);
    defineFunctionObject("GET-LOCAL-TIME-ZONE", "(DEFUN (GET-LOCAL-TIME-ZONE FLOAT) () :PUBLIC? TRUE :DOCUMENTATION \"Returns the current time zone offset from UTC as a float,\nconsidering the effects of daylight savings time.\")", ((cpp_function_code)(&getLocalTimeZone)), NULL);
    defineFunctionObject("GET-LOCAL-STANDARD-TIME-ZONE", "(DEFUN (GET-LOCAL-STANDARD-TIME-ZONE FLOAT) () :PUBLIC? TRUE :DOCUMENTATION \"Returns the standard time zone offset from UTC as a float,\nwithout considering the effects of daylight savings time.\")", ((cpp_function_code)(&getLocalStandardTimeZone)), NULL);
    defineFunctionObject("GET-LOCAL-TIME-ZONE-FOR-DATE", "(DEFUN (GET-LOCAL-TIME-ZONE-FOR-DATE FLOAT) ((YEAR INTEGER) (MONTH INTEGER) (DAY INTEGER) (HOUR INTEGER) (MINUTE INTEGER) (SECOND INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the time zone offset from UTC (as a float)\nthat is applicable to the given date.  Assumes that the date is one\nthat is valid for the underlying programming language.  If not, then\nreturns 0.0\")", ((cpp_function_code)(&getLocalTimeZoneForDate)), NULL);
    defineFunctionObject("TIME-ZONE-FORMAT60", "(DEFUN (TIME-ZONE-FORMAT60 STRING) ((TIMEZONE FLOAT) (INCLUDE-COLON? BOOLEAN)) :PUBLIC? FALSE :DOCUMENTATION \"Format `zone' as an hh:mm or hhmm string depending on `include-colon?'\")", ((cpp_function_code)(&timeZoneFormat60)), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF DECODED-DATE-TIME)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (LOGXOR (LOGOR (LOGOR (SHIFT-LEFT (DATE-TIME-YEAR SELF) 9) (SHIFT-LEFT (DATE-TIME-MONTH SELF) 5)) (DATE-TIME-DAY SELF)) (LOGOR (LOGOR (SHIFT-LEFT (DATE-TIME-HOUR SELF) 12) (SHIFT-LEFT (DATE-TIME-MINUTE SELF) 6)) (DATE-TIME-SECOND SELF)))))", wrapMethodCode(((cpp_method_code)(&DecodedDateTime::hashCode))), NULL);
    defineMethodObject("(DEFMETHOD SET-CURRENT-TIME ((VALUES-STRUCTURE DECODED-DATE-TIME)) :PUBLIC? TRUE :DOCUMENTATION \"Sets the current time into `values-structure'\")", wrapMethodCode(((cpp_method_code)(&DecodedDateTime::setCurrentTime))), NULL);
    defineMethodObject("(DEFMETHOD SET-CURRENT-DATE ((VALUES-STRUCTURE DECODED-DATE-TIME)) :PUBLIC? TRUE :DOCUMENTATION \"Sets the current date into `values-structure'\")", wrapMethodCode(((cpp_method_code)(&DecodedDateTime::setCurrentDate))), NULL);
    defineMethodObject("(DEFMETHOD SET-CURRENT-DATE-TIME ((VALUES-STRUCTURE DECODED-DATE-TIME)) :PUBLIC? TRUE :DOCUMENTATION \"Sets the current date and time into `values-structure'\")", wrapMethodCode(((cpp_method_code)(&DecodedDateTime::setCurrentDateTime))), NULL);
    defineMethodObject("(DEFMETHOD (DECODED-DATE-TIME-TO-ISO8601-STRING STRING) ((DATE DECODED-DATE-TIME)) :PUBLIC? TRUE :DOCUMENTATION \"Returns an ISO-8601 string representation of `date'\nThe Format is YYYY-MM-DDThh:mm:ss+zz:zz, with the string stopping at\nwhen a null value is first encountered.  The time zone will only\nbe included (if present) if a time value is given.\")", wrapMethodCode(((cpp_method_code)(&DecodedDateTime::decodedDateTimeToIso8601String))), NULL);
    defineMethodObject("(DEFMETHOD SET-CONSISTENT-DOW ((SELF DECODED-DATE-TIME)) :PUBLIC? FALSE)", wrapMethodCode(((cpp_method_code)(&DecodedDateTime::setConsistentDow))), NULL);
    defineMethodObject("(DEFMETHOD HELP-MERGE-NULL-FIELDS ((SELF DECODED-DATE-TIME) (DEFAULT DECODED-DATE-TIME) (INDEX INTEGER)) :PUBLIC? FALSE)", wrapMethodCode(((cpp_method_code)(&DecodedDateTime::helpMergeNullFields))), NULL);
    defineMethodObject("(DEFMETHOD MERGE-NULL-FIELDS ((SELF DECODED-DATE-TIME) (DEFAULT DECODED-DATE-TIME)) :PUBLIC? TRUE :DOCUMENTATION \"Replace any null valued fields in `self' with values from `default'.\nThe day of the week will be set consistently, if possible.\")", wrapMethodCode(((cpp_method_code)(&DecodedDateTime::mergeNullFields))), NULL);
    defineMethodObject("(DEFMETHOD MERGE-SUPERIOR-NULL-FIELDS ((SELF DECODED-DATE-TIME) (DEFAULT DECODED-DATE-TIME)) :PUBLIC? TRUE :DOCUMENTATION \"Replace only null valued fields in `self' that represent larger\ntime units than the smallest non-null in `self' with values from `default'.\nThe day of the week will be set consistently, if possible.\nExample: if `self' just has the month being non-null, then only the year\nwill be filled in from `default'.  If the day and minute were non-null,\nthen hour, month and year will be filled.\n\nThis can be useful when one doesn't want to extend the precision\nof the answer.\")", wrapMethodCode(((cpp_method_code)(&DecodedDateTime::mergeSuperiorNullFields))), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF DECODED-TIME-DURATION)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (LOGXOR (DURATION-DAYS SELF) (LOGOR (LOGOR (SHIFT-LEFT (DURATION-HOURS SELF) 12) (SHIFT-LEFT (DURATION-MINUTES SELF) 6)) (DURATION-SECONDS SELF)))))", wrapMethodCode(((cpp_method_code)(&DecodedTimeDuration::hashCode))), NULL);
    defineMethodObject("(DEFMETHOD (COERCE-TO CALENDAR-DATE) ((X CALENDAR-DATE) (Y OBJECT)))", wrapMethodCode(((cpp_method_code)(&CalendarDate::coerceTo))), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF CALENDAR-DATE)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (LOGXOR (MODIFIED-JULIAN-DAY SELF) (TIME-MILLIS SELF))))", wrapMethodCode(((cpp_method_code)(&CalendarDate::hashCode))), NULL);
    defineMethodObject("(DEFMETHOD (CALENDAR-DATE-TO-DATE-STRING STRING) ((DATE CALENDAR-DATE) (TIMEZONE FLOAT) (NUMERIC-MONTH? BOOLEAN)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the date part of the string representation of `date' \nadjusted for `timezone'.  Format is YYYY-MMM-DD, where MMM is a three letter\nEnglish abbreviation of the month if `numeric-month?' is `false' and a two\ndigit numeric value if `numeric-month?' is `true'.  The value `false' is\nrecommended.\")", wrapMethodCode(((cpp_method_code)(&CalendarDate::calendarDateToDateString))), NULL);
    defineMethodObject("(DEFMETHOD (CALENDAR-DATE-TO-TIME-STRING STRING) ((DATE CALENDAR-DATE) (TIMEZONE FLOAT) (INCLUDE-TIMEZONE? BOOLEAN) (INCLUDE-MILLIS? BOOLEAN) (PAD-HOURS? BOOLEAN)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the time part of the string representation of `date'\nadjusted for `timezone'.  The timezone is included in the string if\n`include-timezone?' is `true'.  The value `true' is recommended.\nMilliseconds will be included if `include-millis?' is `true'.\nHours will be zero-padded to length 2 if `pad-hours?' is `true'.\n\")", wrapMethodCode(((cpp_method_code)(&CalendarDate::calendarDateToTimeString))), NULL);
    defineMethodObject("(DEFMETHOD (CALENDAR-DATE-TO-STRING STRING) ((DATE CALENDAR-DATE) (TIMEZONE FLOAT) (NUMERIC-MONTH? BOOLEAN) (INCLUDE-TIMEZONE? BOOLEAN)) :PUBLIC? TRUE :DOCUMENTATION \"Returns a string representation of `date' adjusted for `timezone'.\nThe Format is YYYY-MMM-DD hh:mm:ss z.z, where MMM is a three letter\nEnglish abbreviation of the month if `numeric-month?' is `false' and a two\ndigit numeric value if `numeric-month?' is `true'.  The timezone as a\nfloat offset z.z is included if `include-timezone?' is `true'.\n\nRecommended values for the flags are `false' and `true' respectively.\")", wrapMethodCode(((cpp_method_code)(&CalendarDate::calendarDateToString))), NULL);
    defineMethodObject("(DEFMETHOD (CALENDAR-DATE-TO-ISO8601-STRING STRING) ((DATE CALENDAR-DATE) (TIMEZONE FLOAT) (INCLUDE-TIMEZONE? BOOLEAN)) :PUBLIC? TRUE :DOCUMENTATION \"Returns an ISO-8601 string representation of `date' adjusted for `timezone'.\nThe Format is YYYY-MM-DDThh:mm:ss z:zz.  The timezone as an offset\nhh:mm is included if `include-timezone?' is `true'.\n\nRecommended values for the flag is `true'.\")", wrapMethodCode(((cpp_method_code)(&CalendarDate::calendarDateToIso8601String))), NULL);
    defineMethodObject("(DEFMETHOD (CALENDAR-DATE-TO-NATIVE-DATE-TIME NATIVE-DATE-TIME) ((DATE CALENDAR-DATE)))", wrapMethodCode(((cpp_method_code)(&CalendarDate::calendarDateToNativeDateTime))), NULL);
    defineFunctionObject("NATIVE-DATE-TIME-TO-CALENDAR-DATE", "(DEFUN (NATIVE-DATE-TIME-TO-CALENDAR-DATE CALENDAR-DATE) ((DATE NATIVE-DATE-TIME)) :CONSTRUCTOR? TRUE)", ((cpp_function_code)(((CalendarDate*  (*) (time_t))(&nativeDateTimeToCalendarDate)))), NULL);
    defineMethodObject("(DEFMETHOD PRINT-CALENDAR-DATE ((DATE CALENDAR-DATE) (STREAM NATIVE-OUTPUT-STREAM)))", wrapMethodCode(((cpp_method_code)(&CalendarDate::printCalendarDate))), NULL);
    defineMethodObject("(DEFMETHOD (COERCE-TO TIME-DURATION) ((X TIME-DURATION) (Y OBJECT)))", wrapMethodCode(((cpp_method_code)(&TimeDuration::coerceTo))), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF TIME-DURATION)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (LOGXOR (DAYS SELF) (MILLIS SELF))))", wrapMethodCode(((cpp_method_code)(&TimeDuration::hashCode))), NULL);
    defineMethodObject("(DEFMETHOD (TIME-DURATION-TO-STRING STRING) ((DATE TIME-DURATION)) :PUBLIC? TRUE :DOCUMENTATION \"Returns a string representation of `date'\")", wrapMethodCode(((cpp_method_code)(&TimeDuration::timeDurationToString))), NULL);
    defineFunctionObject("STRING-TO-TIME-DURATION", "(DEFUN (STRING-TO-TIME-DURATION TIME-DURATION) ((DURATION STRING)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE :DOCUMENTATION \"Parses and returns an time-duration object corresponding to `duration'.\nThe syntax for time duration strings is \\\"{plus|minus} N days[; M ms]\\\" where N and M are\ninteger values for days and milliseconds.  If no valid parse is found, `null' is returned.\")", ((cpp_function_code)(((TimeDuration*  (*) (const char*))(&stringToTimeDuration)))), NULL);
    defineMethodObject("(DEFMETHOD PRINT-TIME-DURATION ((DATE TIME-DURATION) (STREAM NATIVE-OUTPUT-STREAM)))", wrapMethodCode(((cpp_method_code)(&TimeDuration::printTimeDuration))), NULL);
    defineFunctionObject("MAKE-DATE-TIME", "(DEFUN (MAKE-DATE-TIME CALENDAR-DATE) ((YEAR INTEGER) (MONTH INTEGER) (DAY INTEGER) (HOUR INTEGER) (MINUTE INTEGER) (SECOND INTEGER) (MILLIS INTEGER) (TIMEZONE FLOAT)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE :DOCUMENTATION \"Create a calendar date with the specified components.  `year' must be\nthe complete year (i.e., a year of 98 is 98 A.D in the 1st century).\n`timezone' is a real number in the range -12.0 to +14.0 where UTC is zone 0.0;  The number\nis the number of hours to add to UTC to arrive at local time.\")", ((cpp_function_code)(&makeDateTime)), NULL);
    defineFunctionObject("MAKE-CURRENT-DATE-TIME", "(DEFUN (MAKE-CURRENT-DATE-TIME CALENDAR-DATE) () :PUBLIC? TRUE :CONSTRUCTOR? TRUE :DOCUMENTATION \"Create a calendar date with current time and date.\")", ((cpp_function_code)(&makeCurrentDateTime)), NULL);
    defineFunctionObject("MAKE-CALENDAR-DATE", "(DEFUN (MAKE-CALENDAR-DATE CALENDAR-DATE) ((DAY INTEGER) (TIME INTEGER)) :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&makeCalendarDate)), NULL);
    defineFunctionObject("MAKE-TIME-DURATION", "(DEFUN (MAKE-TIME-DURATION TIME-DURATION) ((DAYS INTEGER) (MILLIS INTEGER)) :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&makeTimeDuration)), NULL);
    defineFunctionObject("DECODE-TIME-IN-MILLIS", "(DEFUN (DECODE-TIME-IN-MILLIS INTEGER INTEGER INTEGER INTEGER) ((TIME INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Returns multiple values of hours, minutes, seconds, milliseconds for\n`time' specified in milliseconds.\")", ((cpp_function_code)(&decodeTimeInMillis)), NULL);
    defineMethodObject("(DEFMETHOD (GET-CALENDAR-DATE INTEGER INTEGER INTEGER KEYWORD) ((DATE CALENDAR-DATE) (TIMEZONE FLOAT)) :PUBLIC? TRUE :DOCUMENTATION \"Returns multiple values of year, month, day and day of week for `date'\nin `timezone'.  `timezone' is the number of hours added to UTC to get local time.  It\nis in the range -12.0 to +14.0 where UTC is zone 0.0\")", wrapMethodCode(((cpp_method_code)(&CalendarDate::getCalendarDate))), NULL);
    defineMethodObject("(DEFMETHOD (GET-TIME INTEGER INTEGER INTEGER INTEGER) ((DATE CALENDAR-DATE) (TIMEZONE FLOAT)) :PUBLIC? TRUE :DOCUMENTATION \"Returns multiple values of hours, minutes, seconds, milliseconds for\nthe calendar date `date' in `timezone'.  `timezone' is the number of hours added to UTC\nto get local time.  It is in the range -12.0 to +14.0 where UTC is zone 0.0\")", wrapMethodCode(((cpp_method_code)(&CalendarDate::getTime))), NULL);
    defineMethodObject("(DEFMETHOD (DECODE-CALENDAR-DATE DECODED-DATE-TIME) ((DATE CALENDAR-DATE) (TIMEZONE FLOAT)) :PUBLIC? TRUE :DOCUMENTATION \"Returns a decoded time object for `date' interpreted in `timezone'\n`timezone' is the number of hours added to UTC to get local time.  It is \nin the range -12.0 to +14.0 where UTC is zone 0.0\")", wrapMethodCode(((cpp_method_code)(&CalendarDate::decodeCalendarDate))), NULL);
    defineMethodObject("(DEFMETHOD (ENCODE-CALENDAR-DATE CALENDAR-DATE) ((TIME-STRUCTURE DECODED-DATE-TIME)) :PUBLIC? TRUE :DOCUMENTATION \"Returns a calendar date object for `time-structure'.\")", wrapMethodCode(((cpp_method_code)(&DecodedDateTime::encodeCalendarDate))), NULL);
    defineMethodObject("(DEFMETHOD (DECODE-TIME-DURATION DECODED-TIME-DURATION) ((DURATION TIME-DURATION)))", wrapMethodCode(((cpp_method_code)(&TimeDuration::decodeTimeDuration))), NULL);
    defineMethodObject("(DEFMETHOD (ENCODE-TIME-DURATION TIME-DURATION) ((TIME-STRUCTURE DECODED-TIME-DURATION)))", wrapMethodCode(((cpp_method_code)(&DecodedTimeDuration::encodeTimeDuration))), NULL);
    defineFunctionObject("TIME-ADD", "(DEFUN (TIME-ADD DATE-TIME-OBJECT) ((T1 DATE-TIME-OBJECT) (T2 DATE-TIME-OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Add `t1' to `t2'.\nIf one of `t1' or `t2' is a calendar date, then the result is a calendar date.\nIf both `t1' and `t2' are relative dates, then the result is a relative date.\n`t1' and `t2' cannot both be calendar dates.\")", ((cpp_function_code)(&timeAdd)), NULL);
    defineFunctionObject("TIME-SUBTRACT", "(DEFUN (TIME-SUBTRACT DATE-TIME-OBJECT) ((T1 DATE-TIME-OBJECT) (T2 DATE-TIME-OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Subtract `t2' from `t1'.  If `t1' is a calendar date, then `t2' can\nbe either a calendar date (in which case the return value is a relative date) or it\ncan be a relative date (in which case the return value is a calendar date).  If `t1'\nis a relative date, then `t2' must also be a relative date and a relative date is returned.\")", ((cpp_function_code)(&timeSubtract)), NULL);
    defineFunctionObject("TIME-MULTIPLY", "(DEFUN (TIME-MULTIPLY TIME-DURATION) ((T1 OBJECT) (T2 OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Multiplies a relative date by a wrapped number.  One of `t1' or `t2'\nmust be a relative date and the other a wrapped number.\")", ((cpp_function_code)(&timeMultiply)), NULL);
    defineFunctionObject("TIME-DIVIDE", "(DEFUN (TIME-DIVIDE OBJECT) ((T1 TIME-DURATION) (T2 OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Divides the relative date `t1' by `t2'.  `t2' must be\neither a relative date or a wrapped number.  If `t2' is a relative date,\nthen the return value will be a wrapped float.  If `t2' is a wrapped number,\nthen the reutrn value will be a relative date.\")", ((cpp_function_code)(&timeDivide)), NULL);
    defineFunctionObject("DEFINE-TIME-COMPARISON", "(DEFUN DEFINE-TIME-COMPARISON ((NAME SYMBOL) (OPERATOR SYMBOL) (ERROR? SYMBOL)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? FALSE)", ((cpp_function_code)(&defineTimeComparison)), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((T1 CALENDAR-DATE) (T2 OBJECT)))", wrapMethodCode(((cpp_method_code)(&CalendarDate::objectEqlP))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((T1 TIME-DURATION) (T2 OBJECT)))", wrapMethodCode(((cpp_method_code)(&TimeDuration::objectEqlP))), NULL);
    defineMethodObject("(DEFMETHOD (LESS? BOOLEAN) ((T1 CALENDAR-DATE) (T2 OBJECT)))", wrapMethodCode(((cpp_method_code)(&CalendarDate::lessP))), NULL);
    defineMethodObject("(DEFMETHOD (LESS? BOOLEAN) ((T1 TIME-DURATION) (T2 OBJECT)))", wrapMethodCode(((cpp_method_code)(&TimeDuration::lessP))), NULL);
    defineMethodObject("(DEFMETHOD (GREATER? BOOLEAN) ((T1 CALENDAR-DATE) (T2 OBJECT)))", wrapMethodCode(((cpp_method_code)(&CalendarDate::greaterP))), NULL);
    defineMethodObject("(DEFMETHOD (GREATER? BOOLEAN) ((T1 TIME-DURATION) (T2 OBJECT)))", wrapMethodCode(((cpp_method_code)(&TimeDuration::greaterP))), NULL);
    defineMethodObject("(DEFMETHOD (LESS-EQUAL? BOOLEAN) ((T1 CALENDAR-DATE) (T2 OBJECT)))", wrapMethodCode(((cpp_method_code)(&CalendarDate::lessEqualP))), NULL);
    defineMethodObject("(DEFMETHOD (LESS-EQUAL? BOOLEAN) ((T1 TIME-DURATION) (T2 OBJECT)))", wrapMethodCode(((cpp_method_code)(&TimeDuration::lessEqualP))), NULL);
  }
}

void startupDateTime() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupDateTime1();
    }
    if (currentStartupTimePhaseP(4)) {
      MILLIS_PER_DAY = 1000 * 60 * 60 * 24;
      MILLIS_PER_HOUR = 1000 * 60 * 60;
      oMONTH_NAME_VECTORo = stella::newVector(13);
      { int i = NULL_INTEGER;
        int iter036 = 0;
        int upperBound037 = 12;
        Object* abbreviation = NULL;
        Cons* iter038 = getQuotedTree("((\"NUL\" \"January\" \"February\" \"March\" \"April\" \"May\" \"June\" \"July\" \"August\" \"September\" \"October\" \"November\" \"December\") \"/STELLA\")", "/STELLA");

        for  (; (iter036 <= upperBound037) &&
                  (!(iter038 == NIL)); 
              iter036 = iter036 + 1,
              iter038 = iter038->rest) {
          i = iter036;
          abbreviation = iter038->value;
          (oMONTH_NAME_VECTORo->theArray)[i] = (((StringWrapper*)(abbreviation)));
        }
      }
      oMONTH_ABBREVIATION_VECTORo = stella::newVector(13);
      { int i = NULL_INTEGER;
        int iter040 = 0;
        int upperBound041 = 12;
        Object* abbreviation = NULL;
        Cons* iter042 = getQuotedTree("((\"NUL\" \"JAN\" \"FEB\" \"MAR\" \"APR\" \"MAY\" \"JUN\" \"JUL\" \"AUG\" \"SEP\" \"OCT\" \"NOV\" \"DEC\") \"/STELLA\")", "/STELLA");

        for  (; (iter040 <= upperBound041) &&
                  (!(iter042 == NIL)); 
              iter040 = iter040 + 1,
              iter042 = iter042->rest) {
          i = iter040;
          abbreviation = iter042->value;
          (oMONTH_ABBREVIATION_VECTORo->theArray)[i] = (((StringWrapper*)(abbreviation)));
        }
      }
      oDEFAULT_DECODED_DATE_TIMEo = newDecodedDateTime();
      { DecodedDateTime* self044 = newDecodedDateTime();

        self044->dateTimeMillis = NULL_FLOAT;
        self044->dateTimeSecond = NULL_INTEGER;
        self044->dateTimeMinute = NULL_INTEGER;
        self044->dateTimeHour = NULL_INTEGER;
        self044->dateTimeDay = NULL_INTEGER;
        self044->dateTimeMonth = NULL_INTEGER;
        self044->dateTimeYear = NULL_INTEGER;
        self044->dateTimeZone = NULL_FLOAT;
        self044->dateTimeDow = NULL;
        oNULL_DECODED_DATE_TIMEo = self044;
      }
      oFORMAT_DATE_HANDLERSo = stella::newVector(128);
    }
    if (currentStartupTimePhaseP(5)) {
      defineClassFromStringifiedSource("NATIVE-DATE-TIME", "(DEFCLASS NATIVE-DATE-TIME () :PUBLIC? TRUE :DOCUMENTATION \"A data type that is used to hold the native date and time\ninformation.   It is opaque to the Stella users.  It is provided so that\nStella `calendar-date' objects can be translated into and out of native format.\nNote that there is no way to initialize a variable holding a `native-date-time'\nexcept by such a translation.\" :CPP-NATIVE-TYPE \"time_t\" :CL-NATIVE-TYPE \"INTEGER\" :JAVA-NATIVE-TYPE \"long\")");
      { Class* clasS = defineClassFromStringifiedSource("DECODED-DATE-TIME", "(DEFCLASS DECODED-DATE-TIME (STANDARD-OBJECT) :PUBLIC? TRUE :DOCUMENTATION \"A data structure for holding decoded time values with fields\nfor easy access of the components.\" :PUBLIC-SLOTS ((DATE-TIME-MILLIS :INITIALLY 0.0 :TYPE FLOAT) (DATE-TIME-SECOND :INITIALLY 0 :TYPE INTEGER) (DATE-TIME-MINUTE :INITIALLY 0 :TYPE INTEGER) (DATE-TIME-HOUR :INITIALLY 0 :TYPE INTEGER) (DATE-TIME-DAY :INITIALLY 1 :TYPE INTEGER) (DATE-TIME-MONTH :INITIALLY 1 :TYPE INTEGER) (DATE-TIME-YEAR :INITIALLY 1900 :TYPE INTEGER) (DATE-TIME-ZONE :INITIALLY 0.0 :TYPE FLOAT) (DATE-TIME-DOW :INITIALLY :SUNDAY :TYPE KEYWORD)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newDecodedDateTime));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessDecodedDateTimeSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("DECODED-TIME-DURATION", "(DEFCLASS DECODED-TIME-DURATION (STANDARD-OBJECT) :PUBLIC? TRUE :DOCUMENTATION \"A data structure for holding decoded time duration values with\nfields for easy access of the components.  Note that all non-zero values\nshould have the same sign.\" :PUBLIC-SLOTS ((DURATION-MILLIS :INITIALLY 0.0 :TYPE FLOAT) (DURATION-SECONDS :INITIALLY 0 :TYPE INTEGER) (DURATION-MINUTES :INITIALLY 0 :TYPE INTEGER) (DURATION-HOURS :INITIALLY 0 :TYPE INTEGER) (DURATION-DAYS :INITIALLY 0 :TYPE INTEGER)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newDecodedTimeDuration));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessDecodedTimeDurationSlotValue));
      }
      defineClassFromStringifiedSource("DATE-TIME-OBJECT", "(DEFCLASS DATE-TIME-OBJECT (QUANTITY) :ABSTRACT? TRUE)");
      { Class* clasS = defineClassFromStringifiedSource("CALENDAR-DATE", "(DEFCLASS CALENDAR-DATE (DATE-TIME-OBJECT) :PUBLIC? TRUE :DOCUMENTATION \"Representation of Date and Time with the date represented\nas a modified Julian day (starting at midnight instead of noon) and the\ntime as the offset in milliseconds from midnight, UTC\" :PUBLIC-SLOTS ((MODIFIED-JULIAN-DAY :TYPE INTEGER) (TIME-MILLIS :TYPE INTEGER)) :PRINT-FORM (PRINT-CALENDAR-DATE SELF STREAM))");

        clasS->classConstructorCode = ((cpp_function_code)(&newCalendarDate));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessCalendarDateSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("TIME-DURATION", "(DEFCLASS TIME-DURATION (DATE-TIME-OBJECT) :PUBLIC? TRUE :DOCUMENTATION \"Representation of Relative Days and Time with the date represented\nas a number of days and the time in milliseconds.\" :PUBLIC-SLOTS ((DAYS :TYPE INTEGER) (MILLIS :TYPE INTEGER)) :PRINT-FORM (PRINT-TIME-DURATION SELF STREAM))");

        clasS->classConstructorCode = ((cpp_function_code)(&newTimeDuration));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessTimeDurationSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupDateTime2();
      defineMethodObject("(DEFMETHOD (GREATER-EQUAL? BOOLEAN) ((T1 CALENDAR-DATE) (T2 OBJECT)))", wrapMethodCode(((cpp_method_code)(&CalendarDate::greaterEqualP))), NULL);
      defineMethodObject("(DEFMETHOD (GREATER-EQUAL? BOOLEAN) ((T1 TIME-DURATION) (T2 OBJECT)))", wrapMethodCode(((cpp_method_code)(&TimeDuration::greaterEqualP))), NULL);
      defineFunctionObject("FILL-IN-DATE-SUBSTITUTION", "(DEFUN FILL-IN-DATE-SUBSTITUTION ((SUBSTITUTION-LIST (KEY-VALUE-LIST OF STRING-WRAPPER STRING-WRAPPER))) :DOCUMENTATION \"Fill in `substitution-list' with template variable substitions\nfor the names YEAR and DATE which correspond to the current year and date.\nThese substitutions can then be used with `substitute-template-variables-in-string'\nDEPRECATED.  Use `add-date-subsitution' or `add-current-date-substitution' instead.\" :PUBLIC? TRUE)", ((cpp_function_code)(&fillInDateSubstitution)), NULL);
      defineFunctionObject("ADD-DATE-SUBSTITUTION", "(DEFUN ADD-DATE-SUBSTITUTION ((DATE CALENDAR-DATE) (SUBSTITUTION-LIST (KEY-VALUE-LIST OF STRING-WRAPPER STRING-WRAPPER))) :DOCUMENTATION \"Fill in `substitution-list' with template variable substitions\nfor the names YEAR, MONTH, MON, DAY, HOUR, MINUTE, SECOND, TIMEZONE,\nDAY-OF-WEEK, DOW with their values for `date'.  Also, pre-formatted\nDATE, TIME and ISO8601 variables are set.\n\nTIMEZONE is in the format \\\"{+|-}hhmm\\\".  MONTH is the full English\nmonth name and MON is the numeric month.  DAY-OF-WEEK is an English\nstring and DOW is the first three letters.  Minutes and seconds are\nzero-padded.\n\nThese substitutions can be used with `substitute-template-variables-in-string'\" :PUBLIC? TRUE)", ((cpp_function_code)(&addDateSubstitution)), NULL);
      defineFunctionObject("ADD-CURRENT-DATE-SUBSTITUTION", "(DEFUN ADD-CURRENT-DATE-SUBSTITUTION ((SUBSTITUTION-LIST (KEY-VALUE-LIST OF STRING-WRAPPER STRING-WRAPPER))) :DOCUMENTATION \"Fill in `substitution-list' with date information for the current\ndate and time.  See `add-date-substitution' for details.\" :PUBLIC? TRUE)", ((cpp_function_code)(&addCurrentDateSubstitution)), NULL);
      defineFunctionObject("FORMAT-DATE-PRINT-STRING", "(DEFUN FORMAT-DATE-PRINT-STRING ((STRING STRING) (FLAG CHARACTER) (START INTEGER) (END INTEGER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDatePrintString)), NULL);
      defineFunctionObject("FORMAT-DATE-PRINT-TWO-DIGIT-NUMBER", "(DEFUN FORMAT-DATE-PRINT-TWO-DIGIT-NUMBER ((NUMBER INTEGER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDatePrintTwoDigitNumber)), NULL);
      defineFunctionObject("FORMAT-DATE-ABBREVIATED-WEEKDAY-HANDLER", "(DEFUN FORMAT-DATE-ABBREVIATED-WEEKDAY-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDateAbbreviatedWeekdayHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-FULL-WEEKDAY-HANDLER", "(DEFUN FORMAT-DATE-FULL-WEEKDAY-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDateFullWeekdayHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-ABBREVIATED-MONTH-HANDLER", "(DEFUN FORMAT-DATE-ABBREVIATED-MONTH-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDateAbbreviatedMonthHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-FULL-MONTH-HANDLER", "(DEFUN FORMAT-DATE-FULL-MONTH-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDateFullMonthHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-DAY-OF-MONTH-HANDLER", "(DEFUN FORMAT-DATE-DAY-OF-MONTH-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDateDayOfMonthHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-FULL-DATE-HANDLER", "(DEFUN FORMAT-DATE-FULL-DATE-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDateFullDateHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-24-HOUR-HANDLER", "(DEFUN FORMAT-DATE-24-HOUR-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDate24HourHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-12-HOUR-HANDLER", "(DEFUN FORMAT-DATE-12-HOUR-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDate12HourHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-MONTH-HANDLER", "(DEFUN FORMAT-DATE-MONTH-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDateMonthHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-MINUTE-HANDLER", "(DEFUN FORMAT-DATE-MINUTE-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDateMinuteHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-AM-PM-HANDLER", "(DEFUN FORMAT-DATE-AM-PM-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDateAmPmHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-12-HOUR-CLOCK-TIME-HANDLER", "(DEFUN FORMAT-DATE-12-HOUR-CLOCK-TIME-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDate12HourClockTimeHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-24-HOUR-AND-MINUTE-TIME-HANDLER", "(DEFUN FORMAT-DATE-24-HOUR-AND-MINUTE-TIME-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDate24HourAndMinuteTimeHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-SECOND-HANDLER", "(DEFUN FORMAT-DATE-SECOND-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDateSecondHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-FULL-TIME-HANDLER", "(DEFUN FORMAT-DATE-FULL-TIME-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDateFullTimeHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-TWO-DIGIT-YEAR-HANDLER", "(DEFUN FORMAT-DATE-TWO-DIGIT-YEAR-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDateTwoDigitYearHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-YEAR-HANDLER", "(DEFUN FORMAT-DATE-YEAR-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDateYearHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-NUMERIC-TIME-ZONE-HANDLER", "(DEFUN FORMAT-DATE-NUMERIC-TIME-ZONE-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDateNumericTimeZoneHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-TIME-ALPHABETIC-ZONE-HANDLER", "(DEFUN FORMAT-DATE-TIME-ALPHABETIC-ZONE-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDateTimeAlphabeticZoneHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-ERROR-HANDLER", "(DEFUN FORMAT-DATE-ERROR-HANDLER ((DATE DECODED-DATE-TIME) (CONT CHARACTER) (FLAG CHARACTER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&formatDateErrorHandler)), NULL);
      defineFunctionObject("FORMAT-DATE-TO-STREAM", "(DEFUN FORMAT-DATE-TO-STREAM ((DATE OBJECT) (TIMEZONE OBJECT) (CONTROL STRING) (STREAM OUTPUT-STREAM)) :DOCUMENTATION \"Perform formatted printing of `date' relative to `timezone' onto `stream'.  `date'\nhas to be either a calendar-date or a decoded-date-time object.  `timezone' can be null to indicate\nthe local timezone, or a float or supported timezone name.  `control' is a format control string whose\ncharacters are printed literally, unless they are a %-code such as one of these (inspired by the codes\nsupported by the Unix `date' command):\n       %%     a literal %\n       %a     abbreviated weekday name (e.g., Sun)\n       %A     full weekday name (e.g., Sunday)\n       %b     abbreviated month name (e.g., Jan)\n       %B     full month name (e.g., January)\n       %d     day of month (e.g., 01)\n       %D     date; same as %m/%d/%y\n       %F     full date; same as %Y-%m-%d\n       %H     hour (00..23)\n       %I     hour (01..12)\n       %m     month (01..12)\n       %M     minute (00..59)\n       " "%p     either AM or PM\n       %r     12-hour clock time (e.g., 11:11:04 PM)\n       %R     24-hour hour and minute; same as %H:%M\n       %S     second (00..60)\n       %T     time; same as %H:%M:%S\n       %y     last two digits of year (00..99)\n       %Y     year\n       %z     +hhmm numeric time zone (e.g., -0400)\n       %:z    +hhmm numeric time zone (e.g., -04:00)\n       %Z     alphabetic time zone abbreviation (e.g., EDT)\nBy default, numeric fields are padded with zeroes. The following optional flags may follow '%':\n       -      (hyphen) do not pad the field\n       _      (underscore) pad with spaces\n       0      (zero) pad with zeros\n       ^      use upper case if possible\n       ,      use lower case if possible\" :PUBLIC? TRUE)", ((cpp_function_code)(&formatDateToStream)), NULL);
      defineFunctionObject("FORMAT-DATE", "(DEFUN (FORMAT-DATE STRING) ((DATE OBJECT) (TIMEZONE OBJECT) (CONTROL STRING)) :DOCUMENTATION \"Format `date' just like `format-date-to-stream' (which see), but return the result as a string.\" :PUBLIC? TRUE)", ((cpp_function_code)(&formatDate)), NULL);
      defineFunctionObject("STARTUP-DATE-TIME", "(DEFUN STARTUP-DATE-TIME () :PUBLIC? TRUE)", ((cpp_function_code)(&startupDateTime)), NULL);
      { MethodSlot* function = lookupFunction(SYM_DATE_TIME_STELLA_STARTUP_DATE_TIME);

        setDynamicSlotValue(function->dynamicSlots, SYM_DATE_TIME_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupDateTime"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFCONSTANT MILLIS-PER-DAY INTEGER (* 1000 60 60 24) :PUBLIC? FALSE)", &MILLIS_PER_DAY);
      defineGlobalVariableObject("(DEFCONSTANT MILLIS-PER-HOUR INTEGER (* 1000 60 60) :PUBLIC? FALSE)", &MILLIS_PER_HOUR);
      defineGlobalVariableObject("(DEFGLOBAL *MONTH-NAME-VECTOR* (VECTOR OF STRING-WRAPPER) NULL :DOCUMENTATION \"A vector of month names for printing dates\")", &oMONTH_NAME_VECTORo);
      defineGlobalVariableObject("(DEFGLOBAL *MONTH-ABBREVIATION-VECTOR* (VECTOR OF STRING-WRAPPER) NULL :DOCUMENTATION \"A vector of month abbreviations for printing dates\")", &oMONTH_ABBREVIATION_VECTORo);
      defineGlobalVariableObject("(DEFCONSTANT *DEFAULT-DECODED-DATE-TIME* DECODED-DATE-TIME (NEW DECODED-DATE-TIME))", &oDEFAULT_DECODED_DATE_TIMEo);
      defineGlobalVariableObject("(DEFCONSTANT *NULL-DECODED-DATE-TIME* DECODED-DATE-TIME (NEW DECODED-DATE-TIME :DATE-TIME-MILLIS NULL :DATE-TIME-SECOND NULL :DATE-TIME-MINUTE NULL :DATE-TIME-HOUR NULL :DATE-TIME-DAY NULL :DATE-TIME-MONTH NULL :DATE-TIME-YEAR NULL :DATE-TIME-ZONE NULL :DATE-TIME-DOW NULL))", &oNULL_DECODED_DATE_TIMEo);
      defineGlobalVariableObject("(DEFGLOBAL *FORMAT-DATE-HANDLERS* (VECTOR OF FUNCTION-CODE-WRAPPER) (NEW VECTOR :ARRAY-SIZE 128) :DOCUMENTATION \"Handler functions indexed by the character code of their control character.\")", &oFORMAT_DATE_HANDLERSo);
      { Vector* table = oFORMAT_DATE_HANDLERSo;

        { int i = NULL_INTEGER;
          int iter046 = 0;
          int upperBound047 = table->length() - 1;

          for  (; iter046 <= upperBound047; 
                iter046 = iter046 + 1) {
            i = iter046;
            (oFORMAT_DATE_HANDLERSo->theArray)[i] = (wrapFunctionCode(((cpp_function_code)(&formatDateErrorHandler))));
          }
        }
        (table->theArray)[((int)(unsigned char) 'a')] = (wrapFunctionCode(((cpp_function_code)(&formatDateAbbreviatedWeekdayHandler))));
        (table->theArray)[((int)(unsigned char) 'A')] = (wrapFunctionCode(((cpp_function_code)(&formatDateFullWeekdayHandler))));
        (table->theArray)[((int)(unsigned char) 'b')] = (wrapFunctionCode(((cpp_function_code)(&formatDateAbbreviatedMonthHandler))));
        (table->theArray)[((int)(unsigned char) 'B')] = (wrapFunctionCode(((cpp_function_code)(&formatDateFullMonthHandler))));
        (table->theArray)[((int)(unsigned char) 'd')] = (wrapFunctionCode(((cpp_function_code)(&formatDateDayOfMonthHandler))));
        (table->theArray)[((int)(unsigned char) 'D')] = (wrapFunctionCode(((cpp_function_code)(&formatDateFullDateHandler))));
        (table->theArray)[((int)(unsigned char) 'H')] = (wrapFunctionCode(((cpp_function_code)(&formatDate24HourHandler))));
        (table->theArray)[((int)(unsigned char) 'I')] = (wrapFunctionCode(((cpp_function_code)(&formatDate12HourHandler))));
        (table->theArray)[((int)(unsigned char) 'm')] = (wrapFunctionCode(((cpp_function_code)(&formatDateMonthHandler))));
        (table->theArray)[((int)(unsigned char) 'M')] = (wrapFunctionCode(((cpp_function_code)(&formatDateMinuteHandler))));
        (table->theArray)[((int)(unsigned char) 'p')] = (wrapFunctionCode(((cpp_function_code)(&formatDateAmPmHandler))));
        (table->theArray)[((int)(unsigned char) 'r')] = (wrapFunctionCode(((cpp_function_code)(&formatDate12HourClockTimeHandler))));
        (table->theArray)[((int)(unsigned char) 'R')] = (wrapFunctionCode(((cpp_function_code)(&formatDate24HourAndMinuteTimeHandler))));
        (table->theArray)[((int)(unsigned char) 'S')] = (wrapFunctionCode(((cpp_function_code)(&formatDateSecondHandler))));
        (table->theArray)[((int)(unsigned char) 'T')] = (wrapFunctionCode(((cpp_function_code)(&formatDateFullTimeHandler))));
        (table->theArray)[((int)(unsigned char) 'y')] = (wrapFunctionCode(((cpp_function_code)(&formatDateTwoDigitYearHandler))));
        (table->theArray)[((int)(unsigned char) 'Y')] = (wrapFunctionCode(((cpp_function_code)(&formatDateYearHandler))));
        (table->theArray)[((int)(unsigned char) 'z')] = (wrapFunctionCode(((cpp_function_code)(&formatDateNumericTimeZoneHandler))));
        (table->theArray)[((int)(unsigned char) 'Z')] = (wrapFunctionCode(((cpp_function_code)(&formatDateTimeAlphabeticZoneHandler))));
      }
    }
  }
}

Keyword* KWD_DATE_TIME_MONDAY = NULL;

Keyword* KWD_DATE_TIME_TUESDAY = NULL;

Keyword* KWD_DATE_TIME_WEDNESDAY = NULL;

Keyword* KWD_DATE_TIME_THURSDAY = NULL;

Keyword* KWD_DATE_TIME_FRIDAY = NULL;

Keyword* KWD_DATE_TIME_SATURDAY = NULL;

Keyword* KWD_DATE_TIME_SUNDAY = NULL;

Keyword* KWD_DATE_TIME_NEW_MOON = NULL;

Keyword* KWD_DATE_TIME_FIRST_QUARTER = NULL;

Keyword* KWD_DATE_TIME_FULL_MOON = NULL;

Keyword* KWD_DATE_TIME_LAST_QUARTER = NULL;

Keyword* KWD_DATE_TIME_RIGHT = NULL;

Surrogate* SGT_DATE_TIME_STELLA_DECODED_DATE_TIME = NULL;

Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_MILLIS = NULL;

Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_SECOND = NULL;

Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_MINUTE = NULL;

Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_HOUR = NULL;

Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_DAY = NULL;

Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_MONTH = NULL;

Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_YEAR = NULL;

Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_ZONE = NULL;

Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_DOW = NULL;

Keyword* KWD_DATE_TIME_PRESERVE = NULL;

Surrogate* SGT_DATE_TIME_STELLA_DECODED_TIME_DURATION = NULL;

Symbol* SYM_DATE_TIME_STELLA_DURATION_MILLIS = NULL;

Symbol* SYM_DATE_TIME_STELLA_DURATION_SECONDS = NULL;

Symbol* SYM_DATE_TIME_STELLA_DURATION_MINUTES = NULL;

Symbol* SYM_DATE_TIME_STELLA_DURATION_HOURS = NULL;

Symbol* SYM_DATE_TIME_STELLA_DURATION_DAYS = NULL;

Surrogate* SGT_DATE_TIME_STELLA_CALENDAR_DATE = NULL;

Symbol* SYM_DATE_TIME_STELLA_MODIFIED_JULIAN_DAY = NULL;

Symbol* SYM_DATE_TIME_STELLA_TIME_MILLIS = NULL;

Surrogate* SGT_DATE_TIME_STELLA_TIME_DURATION = NULL;

Symbol* SYM_DATE_TIME_STELLA_DAYS = NULL;

Symbol* SYM_DATE_TIME_STELLA_MILLIS = NULL;

Surrogate* SGT_DATE_TIME_STELLA_NUMBER_WRAPPER = NULL;

Symbol* SYM_DATE_TIME_STELLA_TRUE = NULL;

Symbol* SYM_DATE_TIME_STELLA_SIGNAL = NULL;

Symbol* SYM_DATE_TIME_STELLA_INCOMPATIBLE_QUANTITY_EXCEPTION = NULL;

Symbol* SYM_DATE_TIME_STELLA_T1 = NULL;

Symbol* SYM_DATE_TIME_STELLA_T2 = NULL;

Symbol* SYM_DATE_TIME_STELLA_RETURN = NULL;

Symbol* SYM_DATE_TIME_STELLA_FALSE = NULL;

Symbol* SYM_DATE_TIME_STELLA_PROGN = NULL;

Symbol* SYM_DATE_TIME_STELLA_DEFMETHOD = NULL;

Symbol* SYM_DATE_TIME_STELLA_BOOLEAN = NULL;

Symbol* SYM_DATE_TIME_STELLA_CALENDAR_DATE = NULL;

Symbol* SYM_DATE_TIME_STELLA_OBJECT = NULL;

Symbol* SYM_DATE_TIME_STELLA_TYPECASE = NULL;

Symbol* SYM_DATE_TIME_STELLA_IF = NULL;

Symbol* SYM_DATE_TIME_STELLA_e = NULL;

Symbol* SYM_DATE_TIME_STELLA_OTHERWISE = NULL;

Symbol* SYM_DATE_TIME_STELLA_TIME_DURATION = NULL;

Keyword* KWD_DATE_TIME_LETTER = NULL;

Symbol* SYM_DATE_TIME_STELLA_STARTUP_DATE_TIME = NULL;

Symbol* SYM_DATE_TIME_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
