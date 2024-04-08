//  -*- Mode: C++ -*-

// date-time.hh

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


namespace stella {

// Class definitions:
class DecodedDateTime : public StandardObject {
// A data structure for holding decoded time values with fields
// for easy access of the components.
public:
  double dateTimeMillis;
  int dateTimeSecond;
  int dateTimeMinute;
  int dateTimeHour;
  int dateTimeDay;
  int dateTimeMonth;
  int dateTimeYear;
  double dateTimeZone;
  Keyword* dateTimeDow;
public:
  virtual CalendarDate* encodeCalendarDate();
  virtual void mergeSuperiorNullFields(DecodedDateTime* defaulT);
  virtual void mergeNullFields(DecodedDateTime* defaulT);
  virtual const char* decodedDateTimeToIso8601String();
  virtual void setCurrentDateTime();
  virtual void setCurrentDate();
  virtual void setCurrentTime();
  virtual int hashCode();
  virtual Surrogate* primaryType();
public:
  virtual void helpMergeNullFields(DecodedDateTime* defaulT, int index);
  virtual void setConsistentDow();
};

class DecodedTimeDuration : public StandardObject {
// A data structure for holding decoded time duration values with
// fields for easy access of the components.  Note that all non-zero values
// should have the same sign.
public:
  double durationMillis;
  int durationSeconds;
  int durationMinutes;
  int durationHours;
  int durationDays;
public:
  virtual TimeDuration* encodeTimeDuration();
  virtual int hashCode();
  virtual Surrogate* primaryType();
};

class DateTimeObject : public Quantity {
};

class CalendarDate : public DateTimeObject {
// Representation of Date and Time with the date represented
// as a modified Julian day (starting at midnight instead of noon) and the
// time as the offset in milliseconds from midnight, UTC
public:
  int modifiedJulianDay;
  int timeMillis;
public:
  virtual void printObject(std::ostream* stream);
  virtual boolean greaterEqualP(Object* t2);
  virtual boolean lessEqualP(Object* t2);
  virtual boolean greaterP(Object* t2);
  virtual boolean lessP(Object* t2);
  virtual boolean objectEqlP(Object* t2);
  virtual DecodedDateTime* decodeCalendarDate(double timezone);
  virtual int getTime(double timezone, int& _Return1, int& _Return2, int& _Return3);
  virtual int getCalendarDate(double timezone, int& _Return1, int& _Return2, Keyword*& _Return3);
  virtual void printCalendarDate(std::ostream* stream);
  virtual time_t calendarDateToNativeDateTime();
  virtual const char* calendarDateToIso8601String(double timezone, boolean includeTimezoneP);
  virtual const char* calendarDateToString(double timezone, boolean numericMonthP, boolean includeTimezoneP);
  virtual const char* calendarDateToTimeString(double timezone, boolean includeTimezoneP, boolean includeMillisP, boolean padHoursP);
  virtual const char* calendarDateToDateString(double timezone, boolean numericMonthP);
  virtual int hashCode();
  virtual Quantity* coerceTo(Object* y);
  virtual Surrogate* primaryType();
};

class TimeDuration : public DateTimeObject {
// Representation of Relative Days and Time with the date represented
// as a number of days and the time in milliseconds.
public:
  int days;
  int millis;
public:
  virtual void printObject(std::ostream* stream);
  virtual boolean greaterEqualP(Object* t2);
  virtual boolean lessEqualP(Object* t2);
  virtual boolean greaterP(Object* t2);
  virtual boolean lessP(Object* t2);
  virtual boolean objectEqlP(Object* t2);
  virtual DecodedTimeDuration* decodeTimeDuration();
  virtual void printTimeDuration(std::ostream* stream);
  virtual const char* timeDurationToString();
  virtual int hashCode();
  virtual Quantity* coerceTo(Object* y);
  virtual Surrogate* primaryType();
};


// Global declarations:
extern int MILLIS_PER_DAY;
extern int MILLIS_PER_HOUR;
extern Vector* oMONTH_NAME_VECTORo;
extern Vector* oMONTH_ABBREVIATION_VECTORo;
extern DecodedDateTime* oDEFAULT_DECODED_DATE_TIMEo;
extern DecodedDateTime* oNULL_DECODED_DATE_TIMEo;
extern Vector* oFORMAT_DATE_HANDLERSo;

// Function signatures:
int computeJulianDay(int yyyy, int mm, int dd);
int julianDayToModifiedJulianDay(int julianDay);
int modifiedJulianDayToJulianDay(int modifiedJulianDay);
Keyword* computeDayOfWeekJulian(int julianDay);
Keyword* computeDayOfWeek(int yyyy, int mm, int dd);
int computeNextMoonPhase(int n, Keyword* phase, double& _Return1);
int computeCalendarDate(int julianDay, int& _Return1, int& _Return2, Keyword*& _Return3);
int getCurrentDateTime(int& _Return1, int& _Return2, Keyword*& _Return3, int& _Return4, int& _Return5, int& _Return6, int& _Return7);
double getLocalTimeZone();
double getLocalStandardTimeZone();
double getLocalTimeZoneForDate(int year, int month, int day, int hour, int minute, int second);
const char* timeZoneFormat60(double timezone, boolean includeColonP);
DecodedDateTime* newDecodedDateTime();
Object* accessDecodedDateTimeSlotValue(DecodedDateTime* self, Symbol* slotname, Object* value, boolean setvalueP);
DecodedTimeDuration* newDecodedTimeDuration();
Object* accessDecodedTimeDurationSlotValue(DecodedTimeDuration* self, Symbol* slotname, Object* value, boolean setvalueP);
CalendarDate* newCalendarDate();
Object* accessCalendarDateSlotValue(CalendarDate* self, Symbol* slotname, Object* value, boolean setvalueP);
CalendarDate* nativeDateTimeToCalendarDate(time_t date);
TimeDuration* newTimeDuration();
Object* accessTimeDurationSlotValue(TimeDuration* self, Symbol* slotname, Object* value, boolean setvalueP);
TimeDuration* stringToTimeDuration(const char* duration);
CalendarDate* makeDateTime(int year, int month, int day, int hour, int minute, int second, int millis, double timezone);
CalendarDate* makeCurrentDateTime();
CalendarDate* makeCalendarDate(int day, int time);
TimeDuration* makeTimeDuration(int days, int millis);
int decodeTimeInMillis(int time, int& _Return1, int& _Return2, int& _Return3);
DateTimeObject* timeAdd(DateTimeObject* t1, DateTimeObject* t2);
DateTimeObject* timeSubtract(DateTimeObject* t1, DateTimeObject* t2);
TimeDuration* timeMultiply(Object* t1, Object* t2);
Object* timeDivide(TimeDuration* t1, Object* t2);
Object* defineTimeComparison(Symbol* name, Symbol* operatoR, Symbol* errorP);
void fillInDateSubstitution(KeyValueList* substitutionList);
void addDateSubstitution(CalendarDate* date, KeyValueList* substitutionList);
void addCurrentDateSubstitution(KeyValueList* substitutionList);
void formatDatePrintString(const char* string, char flag, int start, int end, OutputStream* stream);
void formatDatePrintTwoDigitNumber(int number, char flag, OutputStream* stream);
void formatDateAbbreviatedWeekdayHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDateFullWeekdayHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDateAbbreviatedMonthHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDateFullMonthHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDateDayOfMonthHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDateFullDateHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDate24HourHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDate12HourHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDateMonthHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDateMinuteHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDateAmPmHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDate12HourClockTimeHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDate24HourAndMinuteTimeHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDateSecondHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDateFullTimeHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDateTwoDigitYearHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDateYearHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDateNumericTimeZoneHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDateTimeAlphabeticZoneHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDateErrorHandler(DecodedDateTime* date, char cont, char flag, OutputStream* stream);
void formatDateToStream(Object* date, Object* timezone, const char* control, OutputStream* stream);
const char* formatDate(Object* date, Object* timezone, const char* control);
void helpStartupDateTime1();
void helpStartupDateTime2();
void startupDateTime();

// Auxiliary global declarations:
extern Keyword* KWD_DATE_TIME_MONDAY;
extern Keyword* KWD_DATE_TIME_TUESDAY;
extern Keyword* KWD_DATE_TIME_WEDNESDAY;
extern Keyword* KWD_DATE_TIME_THURSDAY;
extern Keyword* KWD_DATE_TIME_FRIDAY;
extern Keyword* KWD_DATE_TIME_SATURDAY;
extern Keyword* KWD_DATE_TIME_SUNDAY;
extern Keyword* KWD_DATE_TIME_NEW_MOON;
extern Keyword* KWD_DATE_TIME_FIRST_QUARTER;
extern Keyword* KWD_DATE_TIME_FULL_MOON;
extern Keyword* KWD_DATE_TIME_LAST_QUARTER;
extern Keyword* KWD_DATE_TIME_RIGHT;
extern Surrogate* SGT_DATE_TIME_STELLA_DECODED_DATE_TIME;
extern Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_MILLIS;
extern Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_SECOND;
extern Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_MINUTE;
extern Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_HOUR;
extern Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_DAY;
extern Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_MONTH;
extern Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_YEAR;
extern Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_ZONE;
extern Symbol* SYM_DATE_TIME_STELLA_DATE_TIME_DOW;
extern Keyword* KWD_DATE_TIME_PRESERVE;
extern Surrogate* SGT_DATE_TIME_STELLA_DECODED_TIME_DURATION;
extern Symbol* SYM_DATE_TIME_STELLA_DURATION_MILLIS;
extern Symbol* SYM_DATE_TIME_STELLA_DURATION_SECONDS;
extern Symbol* SYM_DATE_TIME_STELLA_DURATION_MINUTES;
extern Symbol* SYM_DATE_TIME_STELLA_DURATION_HOURS;
extern Symbol* SYM_DATE_TIME_STELLA_DURATION_DAYS;
extern Surrogate* SGT_DATE_TIME_STELLA_CALENDAR_DATE;
extern Symbol* SYM_DATE_TIME_STELLA_MODIFIED_JULIAN_DAY;
extern Symbol* SYM_DATE_TIME_STELLA_TIME_MILLIS;
extern Surrogate* SGT_DATE_TIME_STELLA_TIME_DURATION;
extern Symbol* SYM_DATE_TIME_STELLA_DAYS;
extern Symbol* SYM_DATE_TIME_STELLA_MILLIS;
extern Surrogate* SGT_DATE_TIME_STELLA_NUMBER_WRAPPER;
extern Symbol* SYM_DATE_TIME_STELLA_TRUE;
extern Symbol* SYM_DATE_TIME_STELLA_SIGNAL;
extern Symbol* SYM_DATE_TIME_STELLA_INCOMPATIBLE_QUANTITY_EXCEPTION;
extern Symbol* SYM_DATE_TIME_STELLA_T1;
extern Symbol* SYM_DATE_TIME_STELLA_T2;
extern Symbol* SYM_DATE_TIME_STELLA_RETURN;
extern Symbol* SYM_DATE_TIME_STELLA_FALSE;
extern Symbol* SYM_DATE_TIME_STELLA_PROGN;
extern Symbol* SYM_DATE_TIME_STELLA_DEFMETHOD;
extern Symbol* SYM_DATE_TIME_STELLA_BOOLEAN;
extern Symbol* SYM_DATE_TIME_STELLA_CALENDAR_DATE;
extern Symbol* SYM_DATE_TIME_STELLA_OBJECT;
extern Symbol* SYM_DATE_TIME_STELLA_TYPECASE;
extern Symbol* SYM_DATE_TIME_STELLA_IF;
extern Symbol* SYM_DATE_TIME_STELLA_e;
extern Symbol* SYM_DATE_TIME_STELLA_OTHERWISE;
extern Symbol* SYM_DATE_TIME_STELLA_TIME_DURATION;
extern Keyword* KWD_DATE_TIME_LETTER;
extern Symbol* SYM_DATE_TIME_STELLA_STARTUP_DATE_TIME;
extern Symbol* SYM_DATE_TIME_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
