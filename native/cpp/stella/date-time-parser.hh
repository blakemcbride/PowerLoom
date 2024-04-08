//  -*- Mode: C++ -*-

// date-time-parser.hh

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

// Global declarations:
extern Cons* WHITESPACE_CHARS;
extern Cons* TIME_DIVIDERS;
extern Cons* DATE_DIVIDERS;
extern Cons* DATE_TIME_DIVIDERS;
extern DECLARE_STELLA_SPECIAL(oERROR_ON_MISMATCHo, boolean );
extern DECLARE_STELLA_SPECIAL(oWEEKDAY_STRINGSo, StringHashTable* );
extern DECLARE_STELLA_SPECIAL(oMONTH_STRINGSo, StringToIntegerHashTable* );
extern DECLARE_STELLA_SPECIAL(oZONE_STRINGSo, StringHashTable* );
extern DECLARE_STELLA_SPECIAL(oERA_STRINGSo, StringHashTable* );
extern DECLARE_STELLA_SPECIAL(oSPECIAL_STRINGSo, StringHashTable* );
extern DECLARE_STELLA_SPECIAL(oSPECIAL_SYMBOLSo, Cons* );
extern DECLARE_STELLA_SPECIAL(oDATE_TIME_PATTERNSo, Cons* );

// Function signatures:
Object* hashlist(Object* list, Object* table);
void yesterday(DecodedDateTime* parsedValues, DecodedDateTime* defaultValues);
void today(DecodedDateTime* parsedValues, DecodedDateTime* defaultValues);
void tomorrow(DecodedDateTime* parsedValues, DecodedDateTime* defaultValues);
void now(DecodedDateTime* parsedValues, DecodedDateTime* defaultValues);
Symbol* amPm(Object* string);
Symbol* era(Object* string);
Symbol* noonMidn(Object* string);
Keyword* weekday(Object* thing);
IntegerWrapper* month(Object* thing);
FloatWrapper* zone(Object* thing);
Symbol* specialp(Object* string);
BooleanWrapper* secondp(Object* number);
BooleanWrapper* minute(Object* number);
BooleanWrapper* zoneMinute(Object* number);
BooleanWrapper* hour(Object* number);
BooleanWrapper* day(Object* number);
BooleanWrapper* year(Object* number);
BooleanWrapper* timeDivider(Object* thecharacter);
BooleanWrapper* dateDivider(Object* thecharacter);
BooleanWrapper* dateTimeDivider(Object* thecharacter);
Cons* matchSubstring(const char* substring, boolean parsingTimeP);
int digitValue(char chaR);
Cons* decomposeDateTimeString(const char* string, int start, int end);
Cons* matchPatternElement(Symbol* patternElement, Object* datumElement);
Cons* matchPattern(Cons* pattern, Cons* datum, int datumLength);
void dealWithNoonMidn(Object* formValue, DecodedDateTime* parsedValues);
void dealWithAmPm(Object* formValue, DecodedDateTime* parsedValues);
void dealWithEra(Object* formValue, DecodedDateTime* parsedValues);
void setTimeValues(Cons* stringForm, DecodedDateTime* parsedValues, DecodedDateTime* defaultValues);
Cons* matchDateTimePatterns(const char* dateTimeString, int start, int end, boolean errorOnMismatchP);
DecodedDateTime* helpParseDateTimeRelativeToBase(const char* dateTimeString, DecodedDateTime* baseDateTime, int start, int end, boolean errorOnMismatchP, boolean mergeNullFieldsP);
DecodedDateTime* parseDateTimeRelativeToBase(const char* dateTimeString, DecodedDateTime* baseDateTime, int start, int end, boolean errorOnMismatchP, boolean mergeNullFieldsP);
DecodedDateTime* parseDateTimeInTimeZone(const char* dateTimeString, double timeZone, int start, int end, boolean errorOnMismatchP);
DecodedDateTime* parseDateTime(const char* dateTimeString, int start, int end, boolean errorOnMismatchP);
DecodedDateTime* stringToDecodedDateTime(const char* input);
CalendarDate* stringToCalendarDate(const char* input);
CalendarDate* stringToCalendarDateWithDefault(const char* inputDate, DecodedDateTime* defaultDate);
void helpStartupDateTimeParser1();
void helpStartupDateTimeParser2();
void startupDateTimeParser();

// Auxiliary global declarations:
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_FOREACH;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_ITEM;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_IN;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_CAST;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_CONS;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_OF;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_DO;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_INSERT_AT;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_FIRST;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_SECOND;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_YESTERDAY;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_TODAY;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_TOMORROW;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_NOW;
extern Keyword* KWD_DATE_TIME_PARSER_MONDAY;
extern Keyword* KWD_DATE_TIME_PARSER_TUESDAY;
extern Keyword* KWD_DATE_TIME_PARSER_WEDNESDAY;
extern Keyword* KWD_DATE_TIME_PARSER_THURSDAY;
extern Keyword* KWD_DATE_TIME_PARSER_FRIDAY;
extern Keyword* KWD_DATE_TIME_PARSER_SATURDAY;
extern Keyword* KWD_DATE_TIME_PARSER_SUNDAY;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_BCE;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_CE;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_YEAR;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_MONTH;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_DAY;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_WEEKDAY;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_HOUR;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_MINUTE;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_SECONDP;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_AM_PM;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_ZONE;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_AM;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_PM;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_NOON;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_MIDN;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_SPECIAL;
extern Keyword* KWD_DATE_TIME_PARSER_LETTER;
extern Keyword* KWD_DATE_TIME_PARSER_DIGIT;
extern Surrogate* SGT_DATE_TIME_PARSER_STELLA_CONS;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_ERA;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_STARTUP_DATE_TIME_PARSER;
extern Symbol* SYM_DATE_TIME_PARSER_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
