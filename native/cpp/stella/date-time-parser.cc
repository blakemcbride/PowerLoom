//  -*- Mode: C++ -*-

// date-time-parser.cc

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

Cons* WHITESPACE_CHARS = NULL;

Cons* TIME_DIVIDERS = NULL;

Cons* DATE_DIVIDERS = NULL;

Cons* DATE_TIME_DIVIDERS = NULL;

// If TRUE, an error will be signalled if parse-date-time is unable
//    to determine the time/date format of the string.
DEFINE_STELLA_SPECIAL(oERROR_ON_MISMATCHo, boolean , false);

Object* hashlist(Object* list, Object* table) {
  return (listO(7, SYM_DATE_TIME_PARSER_STELLA_FOREACH, SYM_DATE_TIME_PARSER_STELLA_ITEM, SYM_DATE_TIME_PARSER_STELLA_IN, listO(3, SYM_DATE_TIME_PARSER_STELLA_CAST, list, cons(listO(4, SYM_DATE_TIME_PARSER_STELLA_CONS, SYM_DATE_TIME_PARSER_STELLA_OF, SYM_DATE_TIME_PARSER_STELLA_CONS, NIL), NIL)), SYM_DATE_TIME_PARSER_STELLA_DO, listO(3, SYM_DATE_TIME_PARSER_STELLA_INSERT_AT, table, listO(3, listO(3, SYM_DATE_TIME_PARSER_STELLA_FIRST, SYM_DATE_TIME_PARSER_STELLA_ITEM, NIL), listO(3, SYM_DATE_TIME_PARSER_STELLA_SECOND, SYM_DATE_TIME_PARSER_STELLA_ITEM, NIL), NIL)), NIL));
}

DEFINE_STELLA_SPECIAL(oWEEKDAY_STRINGSo, StringHashTable* , NULL);

DEFINE_STELLA_SPECIAL(oMONTH_STRINGSo, StringToIntegerHashTable* , NULL);

DEFINE_STELLA_SPECIAL(oZONE_STRINGSo, StringHashTable* , NULL);

DEFINE_STELLA_SPECIAL(oERA_STRINGSo, StringHashTable* , NULL);

DEFINE_STELLA_SPECIAL(oSPECIAL_STRINGSo, StringHashTable* , NULL);

DEFINE_STELLA_SPECIAL(oSPECIAL_SYMBOLSo, Cons* , NULL);

DEFINE_STELLA_SPECIAL(oDATE_TIME_PATTERNSo, Cons* , NULL);

void yesterday(DecodedDateTime* parsedValues, DecodedDateTime* defaultValues) {
  today(parsedValues, defaultValues);
  if ((parsedValues->dateTimeYear != NULL_INTEGER) &&
      ((parsedValues->dateTimeMonth != NULL_INTEGER) &&
       (parsedValues->dateTimeDay != NULL_INTEGER))) {
    { int jd = computeJulianDay(parsedValues->dateTimeYear, parsedValues->dateTimeMonth, parsedValues->dateTimeDay);

      { int year = NULL_INTEGER;
        int month = NULL_INTEGER;
        int day = NULL_INTEGER;
        Keyword* dow = NULL;

        year = computeCalendarDate(jd - 1, month, day, dow);
        parsedValues->dateTimeDay = day;
        parsedValues->dateTimeMonth = month;
        parsedValues->dateTimeYear = year;
        parsedValues->dateTimeDow = dow;
      }
    }
  }
}

void today(DecodedDateTime* parsedValues, DecodedDateTime* defaultValues) {
  parsedValues->dateTimeDay = defaultValues->dateTimeDay;
  if (parsedValues->dateTimeMonth == NULL_INTEGER) {
    parsedValues->dateTimeMonth = defaultValues->dateTimeMonth;
  }
  if (parsedValues->dateTimeYear == NULL_INTEGER) {
    parsedValues->dateTimeYear = defaultValues->dateTimeYear;
  }
  parsedValues->setConsistentDow();
  return;
}

void tomorrow(DecodedDateTime* parsedValues, DecodedDateTime* defaultValues) {
  today(parsedValues, defaultValues);
  if ((parsedValues->dateTimeYear != NULL_INTEGER) &&
      ((parsedValues->dateTimeMonth != NULL_INTEGER) &&
       (parsedValues->dateTimeDay != NULL_INTEGER))) {
    { int jd = computeJulianDay(parsedValues->dateTimeYear, parsedValues->dateTimeMonth, parsedValues->dateTimeDay);

      { int year = NULL_INTEGER;
        int month = NULL_INTEGER;
        int day = NULL_INTEGER;
        Keyword* dow = NULL;

        year = computeCalendarDate(jd + 1, month, day, dow);
        parsedValues->dateTimeDay = day;
        parsedValues->dateTimeMonth = month;
        parsedValues->dateTimeYear = year;
        parsedValues->dateTimeDow = dow;
      }
    }
  }
}

void now(DecodedDateTime* parsedValues, DecodedDateTime* defaultValues) {
  { double timeZone = parsedValues->dateTimeZone;

    if (timeZone == NULL_FLOAT) {
      timeZone = defaultValues->dateTimeZone;
      if (timeZone == NULL_FLOAT) {
        timeZone = getLocalTimeZone();
      }
    }
    { int hour = NULL_INTEGER;
      int minute = NULL_INTEGER;
      int second = NULL_INTEGER;
      int millis = NULL_INTEGER;

      hour = makeCurrentDateTime()->getTime(timeZone, minute, second, millis);
      parsedValues->dateTimeMillis = ((double)(millis));
      parsedValues->dateTimeSecond = second;
      parsedValues->dateTimeMinute = minute;
      parsedValues->dateTimeHour = hour;
    }
  }
}

Symbol* amPm(Object* string) {
  if (subtypeOfStringP(safePrimaryType(string))) {
    { Object* string000 = string;
      StringWrapper* string = ((StringWrapper*)(string000));

      if (stringEqlP(string->wrapperValue, "am")) {
        return (SYM_DATE_TIME_PARSER_STELLA_AM);
      }
      else if (stringEqlP(string->wrapperValue, "pm")) {
        return (SYM_DATE_TIME_PARSER_STELLA_PM);
      }
      else {
        return (NULL);
      }
    }
  }
  else {
    return (NULL);
  }
}

Symbol* era(Object* string) {
  if (subtypeOfStringP(safePrimaryType(string))) {
    { Object* string000 = string;
      StringWrapper* string = ((StringWrapper*)(string000));

      return (((Symbol*)(oERA_STRINGSo->lookup(string->wrapperValue))));
    }
  }
  else {
    return (NULL);
  }
}

Symbol* noonMidn(Object* string) {
  if (subtypeOfStringP(safePrimaryType(string))) {
    { Object* string000 = string;
      StringWrapper* string = ((StringWrapper*)(string000));

      if (stringEqlP(string->wrapperValue, "noon")) {
        return (SYM_DATE_TIME_PARSER_STELLA_NOON);
      }
      else if (stringEqlP(string->wrapperValue, "midnight")) {
        return (SYM_DATE_TIME_PARSER_STELLA_MIDN);
      }
      else {
        return (NULL);
      }
    }
  }
  else {
    return (NULL);
  }
}

Keyword* weekday(Object* thing) {
  if (subtypeOfStringP(safePrimaryType(thing))) {
    { Object* thing000 = thing;
      StringWrapper* thing = ((StringWrapper*)(thing000));

      return (((Keyword*)(oWEEKDAY_STRINGSo->lookup(thing->wrapperValue))));
    }
  }
  else {
    return (NULL);
  }
}

IntegerWrapper* month(Object* thing) {
  { Surrogate* testValue000 = safePrimaryType(thing);

    if (subtypeOfStringP(testValue000)) {
      { Object* thing000 = thing;
        StringWrapper* thing = ((StringWrapper*)(thing000));

        { int monthNumber = oMONTH_STRINGSo->lookup(thing->wrapperValue);

          if (monthNumber != NULL_INTEGER) {
            return (wrapInteger(monthNumber));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { Object* thing001 = thing;
        IntegerWrapper* thing = ((IntegerWrapper*)(thing001));

        if ((1 <= thing->wrapperValue) &&
            (thing->wrapperValue <= 12)) {
          return (thing);
        }
        else {
          return (NULL);
        }
      }
    }
    else {
      return (NULL);
    }
  }
}

FloatWrapper* zone(Object* thing) {
  { Surrogate* testValue000 = safePrimaryType(thing);

    if (subtypeOfStringP(testValue000)) {
      { Object* thing000 = thing;
        StringWrapper* thing = ((StringWrapper*)(thing000));

        if (stringEqualP(thing->wrapperValue, "local")) {
          return (wrapFloat(NULL_FLOAT));
        }
        { FloatWrapper* zoneNumber = ((FloatWrapper*)(oZONE_STRINGSo->lookup(thing->wrapperValue)));

          if (((boolean)(zoneNumber))) {
            return (zoneNumber);
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { Object* thing001 = thing;
        FloatWrapper* thing = ((FloatWrapper*)(thing001));

        if ((-12.0 <= thing->wrapperValue) &&
            (thing->wrapperValue <= 14.0)) {
          return (thing);
        }
        else {
          return (NULL);
        }
      }
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { Object* thing002 = thing;
        IntegerWrapper* thing = ((IntegerWrapper*)(thing002));

        { int offset = thing->wrapperValue;

          if ((-12 <= offset) &&
              (offset <= 14)) {
            return (wrapFloat(((double)(offset))));
          }
          else if ((-1200 <= offset) &&
              (offset <= 1400)) {
            return (wrapFloat((offset / 100) + ((offset % 100) / 60.0)));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else {
      return (NULL);
    }
  }
}

Symbol* specialp(Object* string) {
  if (subtypeOfStringP(safePrimaryType(string))) {
    { Object* string000 = string;
      StringWrapper* string = ((StringWrapper*)(string000));

      return (((Symbol*)(oSPECIAL_STRINGSo->lookup(string->wrapperValue))));
    }
  }
  else {
    return (NULL);
  }
}

BooleanWrapper* secondp(Object* number) {
  { Surrogate* testValue000 = safePrimaryType(number);

    if (subtypeOfIntegerP(testValue000)) {
      { Object* number000 = number;
        IntegerWrapper* number = ((IntegerWrapper*)(number000));

        return ((((0 <= number->wrapperValue) &&
            (number->wrapperValue <= 59)) ? TRUE_WRAPPER : FALSE_WRAPPER));
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { Object* number001 = number;
        FloatWrapper* number = ((FloatWrapper*)(number001));

        return ((((0.0 <= number->wrapperValue) &&
            (number->wrapperValue < 60.0)) ? TRUE_WRAPPER : FALSE_WRAPPER));
      }
    }
    else {
      return (FALSE_WRAPPER);
    }
  }
}

BooleanWrapper* minute(Object* number) {
  if (subtypeOfIntegerP(safePrimaryType(number))) {
    { Object* number000 = number;
      IntegerWrapper* number = ((IntegerWrapper*)(number000));

      return ((((0 <= number->wrapperValue) &&
          (number->wrapperValue <= 59)) ? TRUE_WRAPPER : FALSE_WRAPPER));
    }
  }
  else {
    return (FALSE_WRAPPER);
  }
}

BooleanWrapper* zoneMinute(Object* number) {
  if (subtypeOfIntegerP(safePrimaryType(number))) {
    { Object* number000 = number;
      IntegerWrapper* number = ((IntegerWrapper*)(number000));

      return ((((0 <= number->wrapperValue) &&
          (number->wrapperValue <= 59)) ? TRUE_WRAPPER : FALSE_WRAPPER));
    }
  }
  else {
    return (FALSE_WRAPPER);
  }
}

BooleanWrapper* hour(Object* number) {
  if (subtypeOfIntegerP(safePrimaryType(number))) {
    { Object* number000 = number;
      IntegerWrapper* number = ((IntegerWrapper*)(number000));

      return ((((0 <= number->wrapperValue) &&
          (number->wrapperValue <= 23)) ? TRUE_WRAPPER : FALSE_WRAPPER));
    }
  }
  else {
    return (FALSE_WRAPPER);
  }
}

BooleanWrapper* day(Object* number) {
  if (subtypeOfIntegerP(safePrimaryType(number))) {
    { Object* number000 = number;
      IntegerWrapper* number = ((IntegerWrapper*)(number000));

      return ((((1 <= number->wrapperValue) &&
          (number->wrapperValue <= 31)) ? TRUE_WRAPPER : FALSE_WRAPPER));
    }
  }
  else {
    return (FALSE_WRAPPER);
  }
}

BooleanWrapper* year(Object* number) {
  if (subtypeOfIntegerP(safePrimaryType(number))) {
    { Object* number000 = number;
      IntegerWrapper* number = ((IntegerWrapper*)(number000));

      return ((((-4713 <= number->wrapperValue) ||
          (number->wrapperValue <= 5000)) ? TRUE_WRAPPER : FALSE_WRAPPER));
    }
  }
  else {
    return (FALSE_WRAPPER);
  }
}

BooleanWrapper* timeDivider(Object* thecharacter) {
  if (subtypeOfCharacterP(safePrimaryType(thecharacter))) {
    { Object* thecharacter000 = thecharacter;
      CharacterWrapper* thecharacter = ((CharacterWrapper*)(thecharacter000));

      return ((TIME_DIVIDERS->memberP(thecharacter) ? TRUE_WRAPPER : FALSE_WRAPPER));
    }
  }
  else {
    return (FALSE_WRAPPER);
  }
}

BooleanWrapper* dateDivider(Object* thecharacter) {
  if (subtypeOfCharacterP(safePrimaryType(thecharacter))) {
    { Object* thecharacter000 = thecharacter;
      CharacterWrapper* thecharacter = ((CharacterWrapper*)(thecharacter000));

      return ((DATE_DIVIDERS->memberP(thecharacter) ? TRUE_WRAPPER : FALSE_WRAPPER));
    }
  }
  else {
    return (FALSE_WRAPPER);
  }
}

BooleanWrapper* dateTimeDivider(Object* thecharacter) {
  if (subtypeOfCharacterP(safePrimaryType(thecharacter))) {
    { Object* thecharacter000 = thecharacter;
      CharacterWrapper* thecharacter = ((CharacterWrapper*)(thecharacter000));

      return ((DATE_TIME_DIVIDERS->memberP(thecharacter) ? TRUE_WRAPPER : FALSE_WRAPPER));
    }
  }
  else {
    return (FALSE_WRAPPER);
  }
}

Cons* matchSubstring(const char* substring, boolean parsingTimeP) {
  { const char* teststring = stringDowncase(substring);
    Object* testValue = NULL;

    if ((!parsingTimeP) &&
        ((strlen(substring) == 1) &&
         coerceWrappedBooleanToBoolean(((BooleanWrapper*)(testValue = dateTimeDivider(wrapCharacter(substring[0]))))))) {
      return (consList(2, SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER, testValue));
    }
    if (((boolean)(((IntegerWrapper*)(testValue = month(wrapString(teststring))))))) {
      return (consList(2, SYM_DATE_TIME_PARSER_STELLA_MONTH, testValue));
    }
    if (((boolean)(((Keyword*)(testValue = weekday(wrapString(teststring))))))) {
      return (consList(2, SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, testValue));
    }
    if (((boolean)(((Symbol*)(testValue = amPm(wrapString(teststring))))))) {
      return (consList(2, SYM_DATE_TIME_PARSER_STELLA_AM_PM, testValue));
    }
    if (((boolean)(((Symbol*)(testValue = noonMidn(wrapString(teststring))))))) {
      return (consList(2, SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, testValue));
    }
    if (((boolean)(((FloatWrapper*)(testValue = zone(wrapString(teststring))))))) {
      return (consList(2, SYM_DATE_TIME_PARSER_STELLA_ZONE, testValue));
    }
    if (((boolean)(((Symbol*)(testValue = specialp(wrapString(teststring))))))) {
      return (consList(2, SYM_DATE_TIME_PARSER_STELLA_SPECIAL, testValue));
    }
    if (oERROR_ON_MISMATCHo) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "\"~A\" is not a recognized word or abbreviation." << "`" << substring << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    else {
      return (NIL);
    }
  }
}

int digitValue(char chaR) {
  return ((int)(unsigned char) chaR - (int)(unsigned char) '0');
}

Cons* decomposeDateTimeString(const char* string, int start, int end) {
  { int stringIndex = start;
    boolean nextNegativeP = false;
    boolean parsingTimeP = false;
    Cons* partsList = NIL;
    char nextChar = NULL_CHARACTER;
    char prevChar = NULL_CHARACTER;

    if (end == NULL_INTEGER) {
      end = strlen(string);
    }
    while (stringIndex < end) {
      nextChar = string[stringIndex];
      prevChar = ((stringIndex == start) ? NULL_CHARACTER : string[(stringIndex - 1)]);
      if (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) nextChar] == KWD_DATE_TIME_PARSER_LETTER) {
        parsingTimeP = false;
        { int scanIndex = NULL_INTEGER;
          int iter000 = stringIndex + 1;

          for (; true; iter000 = iter000 + 1) {
            scanIndex = iter000;
            if ((scanIndex == end) ||
                (!(oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (string[scanIndex])] == KWD_DATE_TIME_PARSER_LETTER))) {
              { Cons* matchSymbol = matchSubstring(stringSubsequence(string, stringIndex, scanIndex), parsingTimeP);

                if (matchSymbol == NIL) {
                  return (NIL);
                }
                else {
                  partsList = cons(matchSymbol, partsList);
                }
              }
              stringIndex = scanIndex;
              break;
            }
          }
        }
      }
      else if (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) nextChar] == KWD_DATE_TIME_PARSER_DIGIT) {
        { int numericValue = digitValue(nextChar);
          int fractionalValue = 0;
          double fractionalDivisor = 1.0;
          boolean inFractionP = false;

          { int scanIndex = NULL_INTEGER;
            int iter001 = stringIndex + 1;

            for (; true; iter001 = iter001 + 1) {
              scanIndex = iter001;
              if ((scanIndex == end) ||
                  (!((oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (string[scanIndex])] == KWD_DATE_TIME_PARSER_DIGIT) ||
                  ((!inFractionP) &&
                   (string[scanIndex] == '.'))))) {
                if (nextNegativeP) {
                  nextNegativeP = false;
                  numericValue = 0 - numericValue;
                  fractionalValue = 0 - fractionalValue;
                }
                if (inFractionP) {
                  partsList = cons(wrapFloat(numericValue + (fractionalValue / fractionalDivisor)), partsList);
                }
                else {
                  partsList = cons(wrapInteger(numericValue), partsList);
                }
                stringIndex = scanIndex;
                break;
              }
              if (inFractionP) {
                fractionalValue = (fractionalValue * 10) + digitValue(string[scanIndex]);
                fractionalDivisor = fractionalDivisor * 10.0;
              }
              else if (string[scanIndex] == '.') {
                inFractionP = true;
              }
              else {
                numericValue = (numericValue * 10) + digitValue(string[scanIndex]);
              }
            }
          }
        }
      }
      else if ((nextChar == '-') &&
          ((prevChar == NULL_CHARACTER) ||
           (WHITESPACE_CHARS->memberP(wrapCharacter(prevChar)) ||
            (DATE_DIVIDERS->memberP(wrapCharacter(prevChar)) ||
             (parsingTimeP &&
              (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) prevChar] == KWD_DATE_TIME_PARSER_DIGIT)))))) {
        nextNegativeP = true;
        stringIndex = stringIndex + 1;
      }
      else if (TIME_DIVIDERS->memberP(wrapCharacter(nextChar))) {
        partsList = cons(consList(2, SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, wrapCharacter(nextChar)), partsList);
        parsingTimeP = true;
        stringIndex = stringIndex + 1;
      }
      else if (DATE_DIVIDERS->memberP(wrapCharacter(nextChar))) {
        partsList = cons(consList(2, SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, wrapCharacter(nextChar)), partsList);
        parsingTimeP = false;
        stringIndex = stringIndex + 1;
      }
      else if (DATE_TIME_DIVIDERS->memberP(wrapCharacter(nextChar))) {
        partsList = cons(consList(2, SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER, wrapCharacter(nextChar)), partsList);
        parsingTimeP = true;
        stringIndex = stringIndex + 1;
      }
      else if (WHITESPACE_CHARS->memberP(wrapCharacter(nextChar))) {
        parsingTimeP = false;
        stringIndex = stringIndex + 1;
      }
      else if (nextChar == '+') {
        partsList = cons(consList(2, SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, wrapCharacter(nextChar)), partsList);
        stringIndex = stringIndex + 1;
      }
      else if (nextChar == '(') {
        while ((!(stringIndex == end)) &&
            (!(string[stringIndex] == ')'))) {
          parsingTimeP = false;
          stringIndex = stringIndex + 1;
        }
      }
      else {
        if (oERROR_ON_MISMATCHo) {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << ">>> Bogus character at position " << "`" << stringIndex << "'" << " in \"" << "`" << string << "'" << "\"";
            throw *newStellaException(stream000->theStringReader());
          }
        }
        else {
          return (NIL);
        }
      }
    }
    return (partsList->reverse());
  }
}

Cons* matchPatternElement(Symbol* patternElement, Object* datumElement) {
  if (isaP(datumElement, SGT_DATE_TIME_PARSER_STELLA_CONS)) {
    { Object* datumType = ((((Cons*)(datumElement))->value == SYM_DATE_TIME_PARSER_STELLA_SPECIAL) ? ((Cons*)(datumElement))->rest->value : ((Cons*)(datumElement))->value);

      if (datumType == patternElement) {
        return (((Cons*)(datumElement)));
      }
      else {
        return (NIL);
      }
    }
  }
  else if (oSPECIAL_SYMBOLSo->memberP(patternElement)) {
    return (NIL);
  }
  else {
    { cpp_function_code function = lookupFunction(patternElement)->functionCode;
      Object* match = ((Object*  (*) (Object*))function)(datumElement);

      if (subtypeOfBooleanP(safePrimaryType(match))) {
        { Object* match000 = match;
          BooleanWrapper* match = ((BooleanWrapper*)(match000));

          if (coerceWrappedBooleanToBoolean(match)) {
            return (consList(2, patternElement, datumElement));
          }
          else {
            return (NIL);
          }
        }
      }
      else {
        if (((boolean)(match))) {
          return (consList(2, patternElement, match));
        }
        else {
          return (NIL);
        }
      }
    }
  }
}

Cons* matchPattern(Cons* pattern, Cons* datum, int datumLength) {
  if (pattern->length() < datumLength) {
    return (NIL);
  }
  else {
    { Cons* formList = NIL;
      Cons* patternCursor = pattern;
      Cons* datumCursor = datum;
      Object* patternElement = NULL;
      Object* datumElement = NULL;
      boolean optionalP = false;
      Cons* matching = NIL;

      while (!((patternCursor == NIL) ||
          (datumCursor == NIL))) {
        patternElement = patternCursor->value;
        datumElement = datumCursor->value;
        optionalP = isaP(patternElement, SGT_DATE_TIME_PARSER_STELLA_CONS);
        matching = matchPatternElement((optionalP ? ((Symbol*)(((Cons*)(patternElement))->value)) : ((Symbol*)(patternElement))), datumElement);
        if (!(matching == NIL)) {
          { Object* formType = matching->value;

            if (!((formType == SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER) ||
                ((formType == SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER) ||
                 (formType == SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER)))) {
              formList = cons(matching, formList);
            }
          }
        }
        else if (optionalP) {
          datumCursor = cons(datumElement, datumCursor);
        }
        else {
          return (NIL);
        }
        patternCursor = patternCursor->rest;
        datumCursor = datumCursor->rest;
      }
      if ((patternCursor == NIL) &&
          (datumCursor == NIL)) {
        return (formList->reverse());
      }
      else if (patternCursor == NIL) {
        return (NIL);
      }
      else if (datumCursor == NIL) {
        { Object* element = NULL;
          Cons* iter000 = patternCursor;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            element = iter000->value;
            if (!isaP(element, SGT_DATE_TIME_PARSER_STELLA_CONS)) {
              return (NIL);
            }
          }
        }
        return (formList->reverse());
      }
      else {
        throw *newStellaException("Shouldn't get here!");
      }
    }
  }
}

void dealWithNoonMidn(Object* formValue, DecodedDateTime* parsedValues) {
  if (formValue == SYM_DATE_TIME_PARSER_STELLA_NOON) {
    parsedValues->dateTimeHour = 12;
  }
  else if (formValue == SYM_DATE_TIME_PARSER_STELLA_MIDN) {
    parsedValues->dateTimeHour = 0;
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "Unrecognized symbol: ~A" << "`" << formValue << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  parsedValues->dateTimeMinute = 0;
  parsedValues->dateTimeSecond = 0;
}

void dealWithAmPm(Object* formValue, DecodedDateTime* parsedValues) {
  { int hour = parsedValues->dateTimeHour;

    if (formValue == SYM_DATE_TIME_PARSER_STELLA_AM) {
      if (hour == 12) {
        parsedValues->dateTimeHour = 0;
      }
      else if (!((0 <= hour) &&
          (hour <= 12))) {
        if (oERROR_ON_MISMATCHo) {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << hour << "'" << " is not an AM hour.";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
    else if (formValue == SYM_DATE_TIME_PARSER_STELLA_PM) {
      if ((0 <= hour) &&
          (hour <= 11)) {
        parsedValues->dateTimeHour = hour + 12;
      }
    }
    else {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "`" << formValue << "'" << "isn't AM/PM - this shouldn't happen.";
        throw *newStellaException(stream001->theStringReader());
      }
    }
  }
}

void dealWithEra(Object* formValue, DecodedDateTime* parsedValues) {
  if (formValue == SYM_DATE_TIME_PARSER_STELLA_BCE) {
    parsedValues->dateTimeYear = 0 - parsedValues->dateTimeYear;
  }
  else {
    if (!(formValue == SYM_DATE_TIME_PARSER_STELLA_CE)) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << formValue << "'" << "isn't BCE/CE - this shouldn't happen.";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

void setTimeValues(Cons* stringForm, DecodedDateTime* parsedValues, DecodedDateTime* defaultValues) {
  { Object* formType = NULL;
    Object* formValue = NULL;

    { Cons* formPart = NULL;
      Cons* iter000 = stringForm;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        formPart = ((Cons*)(iter000->value));
        formType = formPart->value;
        formValue = formPart->rest->value;
        { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(formType));

          if (testValue000 == SYM_DATE_TIME_PARSER_STELLA_SECONDP) {
            { Surrogate* testValue001 = safePrimaryType(formValue);

              if (subtypeOfIntegerP(testValue001)) {
                { Object* formValue000 = formValue;
                  IntegerWrapper* formValue = ((IntegerWrapper*)(formValue000));

                  parsedValues->dateTimeSecond = formValue->wrapperValue;
                }
              }
              else if (subtypeOfFloatP(testValue001)) {
                { Object* formValue001 = formValue;
                  FloatWrapper* formValue = ((FloatWrapper*)(formValue001));

                  parsedValues->dateTimeSecond = stella::floor(formValue->wrapperValue);
                  parsedValues->dateTimeMillis = 1000.0 * (formValue->wrapperValue - stella::floor(formValue->wrapperValue));
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
          else if (testValue000 == SYM_DATE_TIME_PARSER_STELLA_MINUTE) {
            parsedValues->dateTimeMinute = ((IntegerWrapper*)(formValue))->wrapperValue;
          }
          else if (testValue000 == SYM_DATE_TIME_PARSER_STELLA_HOUR) {
            parsedValues->dateTimeHour = ((IntegerWrapper*)(formValue))->wrapperValue;
          }
          else if (testValue000 == SYM_DATE_TIME_PARSER_STELLA_DAY) {
            parsedValues->dateTimeDay = ((IntegerWrapper*)(formValue))->wrapperValue;
          }
          else if (testValue000 == SYM_DATE_TIME_PARSER_STELLA_MONTH) {
            parsedValues->dateTimeMonth = ((IntegerWrapper*)(formValue))->wrapperValue;
          }
          else if (testValue000 == SYM_DATE_TIME_PARSER_STELLA_YEAR) {
            parsedValues->dateTimeYear = ((IntegerWrapper*)(formValue))->wrapperValue;
          }
          else if (testValue000 == SYM_DATE_TIME_PARSER_STELLA_ZONE) {
            parsedValues->dateTimeZone = ((FloatWrapper*)(formValue))->wrapperValue;
          }
          else if (testValue000 == SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE) {
            if (parsedValues->dateTimeZone > 0) {
              parsedValues->dateTimeZone = parsedValues->dateTimeZone + (((NumberWrapper*)(formValue))->numberWrapperToFloat() / 60.0);
            }
            else {
              parsedValues->dateTimeZone = parsedValues->dateTimeZone + (((NumberWrapper*)(formValue))->numberWrapperToFloat() / -60.0);
            }
          }
          else if (testValue000 == SYM_DATE_TIME_PARSER_STELLA_WEEKDAY) {
            parsedValues->dateTimeDow = ((Keyword*)(formValue));
          }
          else if (testValue000 == SYM_DATE_TIME_PARSER_STELLA_AM_PM) {
            dealWithAmPm(formValue, parsedValues);
          }
          else if (testValue000 == SYM_DATE_TIME_PARSER_STELLA_ERA) {
            dealWithEra(formValue, parsedValues);
          }
          else if (testValue000 == SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN) {
            dealWithNoonMidn(formValue, parsedValues);
          }
          else if (testValue000 == SYM_DATE_TIME_PARSER_STELLA_SPECIAL) {
            ((void  (*) (DecodedDateTime*, DecodedDateTime*))lookupFunction(((Symbol*)(formValue)))->functionCode)(parsedValues, defaultValues);
          }
          else {
            { OutputStringStream* stream001 = newOutputStringStream();

              *(stream001->nativeStream) << "Unrecognized symbol in form list: ~A." << "`" << formType << "'";
              throw *newStellaException(stream001->theStringReader());
            }
          }
        }
      }
    }
  }
}

Cons* matchDateTimePatterns(const char* dateTimeString, int start, int end, boolean errorOnMismatchP) {
  { 
    BIND_STELLA_SPECIAL(oERROR_ON_MISMATCHo, boolean, errorOnMismatchP);
    { Cons* stringParts = decomposeDateTimeString(dateTimeString, start, end);
      int partsLength = stringParts->length();
      Cons* stringForm = NIL;

      { Object* pattern = NULL;
        Cons* iter000 = oDATE_TIME_PATTERNSo;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          pattern = iter000->value;
          stringForm = matchPattern(((Cons*)(pattern)), stringParts, partsLength);
          if (!(stringForm == NIL)) {
            break;
          }
        }
      }
      if (stringForm == NIL) {
        if (errorOnMismatchP) {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "\"" << "`" << dateTimeString << "'" << "\" is not a recognized time/date format.";
            throw *newStellaException(stream000->theStringReader());
          }
        }
        else {
          return (NULL);
        }
      }
      else {
        return (stringForm);
      }
    }
  }
}

DecodedDateTime* helpParseDateTimeRelativeToBase(const char* dateTimeString, DecodedDateTime* baseDateTime, int start, int end, boolean errorOnMismatchP, boolean mergeNullFieldsP) {
  { 
    BIND_STELLA_SPECIAL(oERROR_ON_MISMATCHo, boolean, errorOnMismatchP);
    { Cons* stringForm = matchDateTimePatterns(dateTimeString, start, end, errorOnMismatchP);

      { DecodedDateTime* self000 = newDecodedDateTime();

        self000->dateTimeMillis = NULL_FLOAT;
        self000->dateTimeSecond = NULL_INTEGER;
        self000->dateTimeMinute = NULL_INTEGER;
        self000->dateTimeHour = NULL_INTEGER;
        self000->dateTimeDay = NULL_INTEGER;
        self000->dateTimeMonth = NULL_INTEGER;
        self000->dateTimeYear = NULL_INTEGER;
        self000->dateTimeZone = NULL_FLOAT;
        self000->dateTimeDow = NULL;
        { DecodedDateTime* parsedValues = self000;

          if (!((boolean)(stringForm))) {
            return (NULL);
          }
          setTimeValues(stringForm, parsedValues, baseDateTime);
          if (parsedValues->dateTimeZone == NULL_FLOAT) {
            parsedValues->dateTimeZone = baseDateTime->dateTimeZone;
            if (parsedValues->dateTimeZone == NULL_FLOAT) {
              parsedValues->dateTimeZone = getLocalTimeZoneForDate(baseDateTime->dateTimeYear, baseDateTime->dateTimeMonth, baseDateTime->dateTimeDay, baseDateTime->dateTimeHour, baseDateTime->dateTimeMinute, baseDateTime->dateTimeSecond);
            }
          }
          if (mergeNullFieldsP) {
            parsedValues->mergeNullFields(baseDateTime);
          }
          return (parsedValues);
        }
      }
    }
  }
}

DecodedDateTime* parseDateTimeRelativeToBase(const char* dateTimeString, DecodedDateTime* baseDateTime, int start, int end, boolean errorOnMismatchP, boolean mergeNullFieldsP) {
  // Tries very hard to make sense out of the argument `date-time-string' and
  // returns a time structure if successful.  If not, it returns `null'.
  // If `error-on-mismatch?' is true, parse-date-time will signal an error instead of
  // returning `null'.
  // Default values are passed in via `base-date-time'.  If the timezone field that
  // is passed in is NULL, then the local time zone for the parsed date/time will
  // be used.
  // If `merge-null-fields?' is `true', then default values from `base-time-date'
  // will be merged into missing components.  If `false', then they won't be merged
  // in for null components but can still be used as a basis for interpreatation of
  // relative time strings like "now" or "yesterday"
  return (helpParseDateTimeRelativeToBase(dateTimeString, baseDateTime, start, end, errorOnMismatchP, mergeNullFieldsP));
}

DecodedDateTime* parseDateTimeInTimeZone(const char* dateTimeString, double timeZone, int start, int end, boolean errorOnMismatchP) {
  // Tries very hard to make sense out of the argument `date-time-string' and
  // returns a time structure if successful.  If not, it returns `null'.
  // If `error-on-mismatch?' is true, parse-date-time will signal an error instead of
  // returning `null'.  
  // Default values are 00:00:00 in the given timezone on the current date.  If the
  // given `time-zone' value is `null', then the local time zone for the given date
  // and time will be used as determined by the operating system.
  { DecodedDateTime* defaultValues = makeCurrentDateTime()->decodeCalendarDate(((timeZone == NULL_FLOAT) ? getLocalTimeZone() : timeZone));

    defaultValues->dateTimeMillis = 0.0;
    defaultValues->dateTimeSecond = 0;
    defaultValues->dateTimeMinute = 0;
    defaultValues->dateTimeHour = 0;
    defaultValues->dateTimeZone = timeZone;
    return (helpParseDateTimeRelativeToBase(dateTimeString, defaultValues, start, end, errorOnMismatchP, true));
  }
}

DecodedDateTime* parseDateTime(const char* dateTimeString, int start, int end, boolean errorOnMismatchP) {
  // Tries very hard to make sense out of the argument `date-time-string' and
  // returns a time structure if successful.  If not, it returns `null'.
  // If `error-on-mismatch?' is true, parse-date-time will signal an error instead of
  // returning `null'.  
  // Default values are 00:00:00 local time on the current date
  return (parseDateTimeInTimeZone(dateTimeString, NULL_FLOAT, start, end, errorOnMismatchP));
}

DecodedDateTime* stringToDecodedDateTime(const char* input) {
  // Returns a decoded date-time object representing the date
  // and time parsed from the `input' string.  If no valid parse is found,
  // `null' is returned.
  return (parseDateTimeInTimeZone(input, NULL_FLOAT, 0, NULL_INTEGER, false));
}

CalendarDate* stringToCalendarDate(const char* input) {
  // Returns a calendar date object representing the date and time
  // parsed from the `input' string.  If no valid parse is found,
  // `null' is returned.
  { DecodedDateTime* dateTime = parseDateTimeInTimeZone(input, NULL_FLOAT, 0, NULL_INTEGER, false);

    if (!((boolean)(dateTime))) {
      return (NULL);
    }
    else {
      return (dateTime->encodeCalendarDate());
    }
  }
}

CalendarDate* stringToCalendarDateWithDefault(const char* inputDate, DecodedDateTime* defaultDate) {
  // Returns a calendar date object representing the date and time
  // parsed from the `input-date' string.  Default values for missing fields and
  // the interpretation of relative references come from `default-date'.  If the
  // `default-date' is `null', the current date will be used.  If a null set of
  // defaults is desired, use `*NULL-DECODED-DATE-TIME*'.
  // If no valid parse is found, `null' is returned.
  if (!((boolean)(defaultDate))) {
    return (stringToCalendarDate(inputDate));
  }
  else {
    { DecodedDateTime* dateTime = parseDateTimeRelativeToBase(inputDate, defaultDate, 0, NULL_INTEGER, false, true);

      if (!((boolean)(dateTime))) {
        return (NULL);
      }
      else {
        return (dateTime->encodeCalendarDate());
      }
    }
  }
}

void helpStartupDateTimeParser1() {
  {
    SYM_DATE_TIME_PARSER_STELLA_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("FOREACH", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_ITEM = ((Symbol*)(internRigidSymbolWrtModule("ITEM", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_IN = ((Symbol*)(internRigidSymbolWrtModule("IN", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_CAST = ((Symbol*)(internRigidSymbolWrtModule("CAST", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_CONS = ((Symbol*)(internRigidSymbolWrtModule("CONS", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_OF = ((Symbol*)(internRigidSymbolWrtModule("OF", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_DO = ((Symbol*)(internRigidSymbolWrtModule("DO", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_INSERT_AT = ((Symbol*)(internRigidSymbolWrtModule("INSERT-AT", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_FIRST = ((Symbol*)(internRigidSymbolWrtModule("FIRST", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_SECOND = ((Symbol*)(internRigidSymbolWrtModule("SECOND", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_YESTERDAY = ((Symbol*)(internRigidSymbolWrtModule("YESTERDAY", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_TODAY = ((Symbol*)(internRigidSymbolWrtModule("TODAY", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_TOMORROW = ((Symbol*)(internRigidSymbolWrtModule("TOMORROW", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_NOW = ((Symbol*)(internRigidSymbolWrtModule("NOW", NULL, 0)));
    KWD_DATE_TIME_PARSER_MONDAY = ((Keyword*)(internRigidSymbolWrtModule("MONDAY", NULL, 2)));
    KWD_DATE_TIME_PARSER_TUESDAY = ((Keyword*)(internRigidSymbolWrtModule("TUESDAY", NULL, 2)));
    KWD_DATE_TIME_PARSER_WEDNESDAY = ((Keyword*)(internRigidSymbolWrtModule("WEDNESDAY", NULL, 2)));
    KWD_DATE_TIME_PARSER_THURSDAY = ((Keyword*)(internRigidSymbolWrtModule("THURSDAY", NULL, 2)));
    KWD_DATE_TIME_PARSER_FRIDAY = ((Keyword*)(internRigidSymbolWrtModule("FRIDAY", NULL, 2)));
    KWD_DATE_TIME_PARSER_SATURDAY = ((Keyword*)(internRigidSymbolWrtModule("SATURDAY", NULL, 2)));
    KWD_DATE_TIME_PARSER_SUNDAY = ((Keyword*)(internRigidSymbolWrtModule("SUNDAY", NULL, 2)));
    SYM_DATE_TIME_PARSER_STELLA_BCE = ((Symbol*)(internRigidSymbolWrtModule("BCE", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_CE = ((Symbol*)(internRigidSymbolWrtModule("CE", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_YEAR = ((Symbol*)(internRigidSymbolWrtModule("YEAR", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER = ((Symbol*)(internRigidSymbolWrtModule("DATE-DIVIDER", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_MONTH = ((Symbol*)(internRigidSymbolWrtModule("MONTH", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_DAY = ((Symbol*)(internRigidSymbolWrtModule("DAY", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN = ((Symbol*)(internRigidSymbolWrtModule("NOON-MIDN", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_WEEKDAY = ((Symbol*)(internRigidSymbolWrtModule("WEEKDAY", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER = ((Symbol*)(internRigidSymbolWrtModule("DATE-TIME-DIVIDER", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_HOUR = ((Symbol*)(internRigidSymbolWrtModule("HOUR", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER = ((Symbol*)(internRigidSymbolWrtModule("TIME-DIVIDER", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_MINUTE = ((Symbol*)(internRigidSymbolWrtModule("MINUTE", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_SECONDP = ((Symbol*)(internRigidSymbolWrtModule("SECONDP", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_AM_PM = ((Symbol*)(internRigidSymbolWrtModule("AM-PM", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_ZONE = ((Symbol*)(internRigidSymbolWrtModule("ZONE", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE = ((Symbol*)(internRigidSymbolWrtModule("ZONE-MINUTE", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_AM = ((Symbol*)(internRigidSymbolWrtModule("AM", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_PM = ((Symbol*)(internRigidSymbolWrtModule("PM", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_NOON = ((Symbol*)(internRigidSymbolWrtModule("NOON", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_MIDN = ((Symbol*)(internRigidSymbolWrtModule("MIDN", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_SPECIAL = ((Symbol*)(internRigidSymbolWrtModule("SPECIAL", NULL, 0)));
    KWD_DATE_TIME_PARSER_LETTER = ((Keyword*)(internRigidSymbolWrtModule("LETTER", NULL, 2)));
    KWD_DATE_TIME_PARSER_DIGIT = ((Keyword*)(internRigidSymbolWrtModule("DIGIT", NULL, 2)));
    SGT_DATE_TIME_PARSER_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SYM_DATE_TIME_PARSER_STELLA_ERA = ((Symbol*)(internRigidSymbolWrtModule("ERA", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_STARTUP_DATE_TIME_PARSER = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-DATE-TIME-PARSER", NULL, 0)));
    SYM_DATE_TIME_PARSER_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupDateTimeParser2() {
  {
    WHITESPACE_CHARS = listO(9, wrapCharacter(' '), wrapCharacter('\t'), wrapCharacter('\n'), wrapCharacter('\r'), wrapCharacter('\f'), wrapCharacter(','), wrapCharacter('\''), wrapCharacter('`'), NIL);
    TIME_DIVIDERS = listO(3, wrapCharacter(':'), wrapCharacter('.'), NIL);
    DATE_DIVIDERS = listO(5, wrapCharacter('\\'), wrapCharacter('/'), wrapCharacter('-'), wrapCharacter('+'), NIL);
    DATE_TIME_DIVIDERS = cons(wrapCharacter('T'), NIL);
    oWEEKDAY_STRINGSo = newStringHashTable();
    oMONTH_STRINGSo = newStringToIntegerHashTable();
    oZONE_STRINGSo = newStringHashTable();
    oERA_STRINGSo = newStringHashTable();
    oSPECIAL_STRINGSo = newStringHashTable();
    oSPECIAL_SYMBOLSo = listO(5, SYM_DATE_TIME_PARSER_STELLA_YESTERDAY, SYM_DATE_TIME_PARSER_STELLA_TODAY, SYM_DATE_TIME_PARSER_STELLA_TOMORROW, SYM_DATE_TIME_PARSER_STELLA_NOW, NIL);
    { Cons* item = NULL;
      Cons* iter053 = ((Cons*)(listO(18, listO(3, wrapString("monday"), KWD_DATE_TIME_PARSER_MONDAY, NIL), listO(3, wrapString("mon"), KWD_DATE_TIME_PARSER_MONDAY, NIL), listO(3, wrapString("tuesday"), KWD_DATE_TIME_PARSER_TUESDAY, NIL), listO(3, wrapString("tues"), KWD_DATE_TIME_PARSER_TUESDAY, NIL), listO(3, wrapString("tue"), KWD_DATE_TIME_PARSER_TUESDAY, NIL), listO(3, wrapString("wednesday"), KWD_DATE_TIME_PARSER_WEDNESDAY, NIL), listO(3, wrapString("wednes"), KWD_DATE_TIME_PARSER_WEDNESDAY, NIL), listO(3, wrapString("wed"), KWD_DATE_TIME_PARSER_WEDNESDAY, NIL), listO(3, wrapString("thursday"), KWD_DATE_TIME_PARSER_THURSDAY, NIL), listO(3, wrapString("thurs"), KWD_DATE_TIME_PARSER_THURSDAY, NIL), listO(3, wrapString("thu"), KWD_DATE_TIME_PARSER_THURSDAY, NIL), listO(3, wrapString("friday"), KWD_DATE_TIME_PARSER_FRIDAY, NIL), listO(3, wrapString("fri"), KWD_DATE_TIME_PARSER_FRIDAY, NIL), listO(3, wrapString("saturday"), KWD_DATE_TIME_PARSER_SATURDAY, NIL), listO(3, wrapString("sat"), KWD_DATE_TIME_PARSER_SATURDAY, NIL), listO(3, wrapString("sunday"), KWD_DATE_TIME_PARSER_SUNDAY, NIL), listO(3, wrapString("sun"), KWD_DATE_TIME_PARSER_SUNDAY, NIL), NIL)));

      for (; !(iter053 == NIL); iter053 = iter053->rest) {
        item = ((Cons*)(iter053->value));
        oWEEKDAY_STRINGSo->insertAt(((StringWrapper*)(item->value))->wrapperValue, item->rest->value);
      }
    }
    { Cons* item = NULL;
      Cons* iter054 = ((Cons*)(listO(25, listO(3, wrapString("january"), wrapInteger(1), NIL), listO(3, wrapString("jan"), wrapInteger(1), NIL), listO(3, wrapString("february"), wrapInteger(2), NIL), listO(3, wrapString("feb"), wrapInteger(2), NIL), listO(3, wrapString("march"), wrapInteger(3), NIL), listO(3, wrapString("mar"), wrapInteger(3), NIL), listO(3, wrapString("april"), wrapInteger(4), NIL), listO(3, wrapString("apr"), wrapInteger(4), NIL), listO(3, wrapString("may"), wrapInteger(5), NIL), listO(3, wrapString("june"), wrapInteger(6), NIL), listO(3, wrapString("jun"), wrapInteger(6), NIL), listO(3, wrapString("july"), wrapInteger(7), NIL), listO(3, wrapString("jul"), wrapInteger(7), NIL), listO(3, wrapString("august"), wrapInteger(8), NIL), listO(3, wrapString("aug"), wrapInteger(8), NIL), listO(3, wrapString("september"), wrapInteger(9), NIL), listO(3, wrapString("sept"), wrapInteger(9), NIL), listO(3, wrapString("sep"), wrapInteger(9), NIL), listO(3, wrapString("october"), wrapInteger(10), NIL), listO(3, wrapString("oct"), wrapInteger(10), NIL), listO(3, wrapString("november"), wrapInteger(11), NIL), listO(3, wrapString("nov"), wrapInteger(11), NIL), listO(3, wrapString("december"), wrapInteger(12), NIL), listO(3, wrapString("dec"), wrapInteger(12), NIL), NIL)));

      for (; !(iter054 == NIL); iter054 = iter054->rest) {
        item = ((Cons*)(iter054->value));
        oMONTH_STRINGSo->insertAt(((StringWrapper*)(item->value))->wrapperValue, ((IntegerWrapper*)(item->rest->value))->wrapperValue);
      }
    }
    { Cons* item = NULL;
      Cons* iter055 = ((Cons*)(listO(49, listO(3, wrapString("gmt"), wrapFloat(0.0), NIL), listO(3, wrapString("utc"), wrapFloat(0.0), NIL), listO(3, wrapString("zulu"), wrapFloat(0.0), NIL), listO(3, wrapString("est"), wrapFloat(-5.0), NIL), listO(3, wrapString("edt"), wrapFloat(-4.0), NIL), listO(3, wrapString("cst"), wrapFloat(-6.0), NIL), listO(3, wrapString("cdt"), wrapFloat(-5.0), NIL), listO(3, wrapString("mst"), wrapFloat(-7.0), NIL), listO(3, wrapString("mdt"), wrapFloat(-6.0), NIL), listO(3, wrapString("pst"), wrapFloat(-8.0), NIL), listO(3, wrapString("pdt"), wrapFloat(-7.0), NIL), listO(3, wrapString("a"), wrapFloat(1.0), NIL), listO(3, wrapString("b"), wrapFloat(2.0), NIL), listO(3, wrapString("c"), wrapFloat(3.0), NIL), listO(3, wrapString("c*"), wrapFloat(3.5), NIL), listO(3, wrapString("d"), wrapFloat(4.0), NIL), listO(3, wrapString("d*"), wrapFloat(4.5), NIL), listO(3, wrapString("e"), wrapFloat(5.0), NIL), listO(3, wrapString("e*"), wrapFloat(4.5), NIL), listO(3, wrapString("f"), wrapFloat(6.0), NIL), listO(3, wrapString("f*"), wrapFloat(6.5), NIL), listO(3, wrapString("g"), wrapFloat(7.0), NIL), listO(3, wrapString("h"), wrapFloat(7.0), NIL), listO(3, wrapString("i"), wrapFloat(9.0), NIL), listO(3, wrapString("i*"), wrapFloat(9.5), NIL), listO(3, wrapString("k"), wrapFloat(10.0), NIL), listO(3, wrapString("k*"), wrapFloat(10.5), NIL), listO(3, wrapString("l"), wrapFloat(11.0), NIL), listO(3, wrapString("l*"), wrapFloat(11.5), NIL), listO(3, wrapString("m"), wrapFloat(12.0), NIL), listO(3, wrapString("m*"), wrapFloat(13.0), NIL), listO(3, wrapString("m%"), wrapFloat(14.0), NIL), listO(3, wrapString("n"), wrapFloat(-1.0), NIL), listO(3, wrapString("o"), wrapFloat(-2.0), NIL), listO(3, wrapString("p"), wrapFloat(-3.0), NIL), listO(3, wrapString("p*"), wrapFloat(-3.5), NIL), listO(3, wrapString("q"), wrapFloat(-4.0), NIL), listO(3, wrapString("r"), wrapFloat(-5.0), NIL), listO(3, wrapString("s"), wrapFloat(-6.0), NIL), listO(3, wrapString("t"), wrapFloat(-7.0), NIL), listO(3, wrapString("u"), wrapFloat(-8.0), NIL), listO(3, wrapString("u*"), wrapFloat(-8.5), NIL), listO(3, wrapString("v"), wrapFloat(-9.0), NIL), listO(3, wrapString("v*"), wrapFloat(-9.5), NIL), listO(3, wrapString("w"), wrapFloat(-10.0), NIL), listO(3, wrapString("x"), wrapFloat(-11.0), NIL), listO(3, wrapString("y"), wrapFloat(-12.0), NIL), listO(3, wrapString("z"), wrapFloat(0.0), NIL), NIL)));

      for (; !(iter055 == NIL); iter055 = iter055->rest) {
        item = ((Cons*)(iter055->value));
        oZONE_STRINGSo->insertAt(((StringWrapper*)(item->value))->wrapperValue, item->rest->value);
      }
    }
    { Cons* item = NULL;
      Cons* iter056 = ((Cons*)(listO(5, listO(3, wrapString("bc"), SYM_DATE_TIME_PARSER_STELLA_BCE, NIL), listO(3, wrapString("bce"), SYM_DATE_TIME_PARSER_STELLA_BCE, NIL), listO(3, wrapString("ad"), SYM_DATE_TIME_PARSER_STELLA_CE, NIL), listO(3, wrapString("ce"), SYM_DATE_TIME_PARSER_STELLA_CE, NIL), NIL)));

      for (; !(iter056 == NIL); iter056 = iter056->rest) {
        item = ((Cons*)(iter056->value));
        oERA_STRINGSo->insertAt(((StringWrapper*)(item->value))->wrapperValue, item->rest->value);
      }
    }
    { Symbol* symbol = NULL;
      Cons* iter057 = oSPECIAL_SYMBOLSo;

      for (; !(iter057 == NIL); iter057 = iter057->rest) {
        symbol = ((Symbol*)(iter057->value));
        oSPECIAL_STRINGSo->insertAt(stringDowncase(symbol->symbolName), symbol);
      }
    }
    oDATE_TIME_PATTERNSo = listO(51, listO(7, SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), NIL), listO(8, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, NIL), listO(8, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, NIL), listO(6, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, NIL), listO(7, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, NIL), listO(5, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, NIL), listO(5, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, NIL), listO(12, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(6, SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(4, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), NIL), listO(17, SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(11, SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(7, SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, SYM_DATE_TIME_PARSER_STELLA_NOW, NIL), listO(18, cons(SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(18, cons(SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(16, cons(SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(15, SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(15, SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(12, cons(SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(12, cons(SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(10, cons(SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(9, SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(9, SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(18, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, NIL), listO(18, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, NIL), listO(16, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, NIL), listO(17, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, NIL), listO(15, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, NIL), listO(15, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, NIL), listO(14, SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, SYM_DATE_TIME_PARSER_STELLA_MONTH, SYM_DATE_TIME_PARSER_STELLA_DAY, SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MINUTE, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_SECONDP, cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, NIL), listO(17, cons(SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MINUTE, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(17, cons(SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_DAY, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), SYM_DATE_TIME_PARSER_STELLA_MINUTE, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(4, SYM_DATE_TIME_PARSER_STELLA_YEAR, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MONTH, NIL), NIL), listO(4, SYM_DATE_TIME_PARSER_STELLA_MONTH, cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_YEAR, NIL), NIL), listO(10, cons(SYM_DATE_TIME_PARSER_STELLA_WEEKDAY, NIL), SYM_DATE_TIME_PARSER_STELLA_MONTH, SYM_DATE_TIME_PARSER_STELLA_DAY, SYM_DATE_TIME_PARSER_STELLA_HOUR, SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, SYM_DATE_TIME_PARSER_STELLA_MINUTE, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), SYM_DATE_TIME_PARSER_STELLA_YEAR, NIL), listO(3, SYM_DATE_TIME_PARSER_STELLA_NOW, cons(SYM_DATE_TIME_PARSER_STELLA_YESTERDAY, NIL), NIL), listO(3, cons(SYM_DATE_TIME_PARSER_STELLA_YESTERDAY, NIL), SYM_DATE_TIME_PARSER_STELLA_NOW, NIL), listO(3, SYM_DATE_TIME_PARSER_STELLA_NOW, cons(SYM_DATE_TIME_PARSER_STELLA_TODAY, NIL), NIL), listO(3, cons(SYM_DATE_TIME_PARSER_STELLA_TODAY, NIL), SYM_DATE_TIME_PARSER_STELLA_NOW, NIL), listO(3, SYM_DATE_TIME_PARSER_STELLA_NOW, cons(SYM_DATE_TIME_PARSER_STELLA_TOMORROW, NIL), NIL), listO(3, cons(SYM_DATE_TIME_PARSER_STELLA_TOMORROW, NIL), SYM_DATE_TIME_PARSER_STELLA_NOW, NIL), listO(3, SYM_DATE_TIME_PARSER_STELLA_YESTERDAY, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), NIL), listO(3, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), SYM_DATE_TIME_PARSER_STELLA_YESTERDAY, NIL), listO(3, SYM_DATE_TIME_PARSER_STELLA_TODAY, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), NIL), listO(3, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), SYM_DATE_TIME_PARSER_STELLA_TODAY, NIL), listO(3, SYM_DATE_TIME_PARSER_STELLA_TOMORROW, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), NIL), listO(3, cons(SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN, NIL), SYM_DATE_TIME_PARSER_STELLA_TOMORROW, NIL), listO(12, SYM_DATE_TIME_PARSER_STELLA_YESTERDAY, SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(12, SYM_DATE_TIME_PARSER_STELLA_TOMORROW, SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), listO(12, SYM_DATE_TIME_PARSER_STELLA_TODAY, SYM_DATE_TIME_PARSER_STELLA_HOUR, cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_MINUTE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_SECONDP, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_AM_PM, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER, NIL), cons(SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE, NIL), NIL), NIL);
  }
}

void startupDateTimeParser() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupDateTimeParser1();
    }
    if (currentStartupTimePhaseP(4)) {
      helpStartupDateTimeParser2();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("HASHLIST", "(DEFUN HASHLIST ((LIST OBJECT) (TABLE OBJECT)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&hashlist)), NULL);
      defineFunctionObject("YESTERDAY", "(DEFUN YESTERDAY ((PARSED-VALUES DECODED-DATE-TIME) (DEFAULT-VALUES DECODED-DATE-TIME)))", ((cpp_function_code)(&yesterday)), NULL);
      defineFunctionObject("TODAY", "(DEFUN TODAY ((PARSED-VALUES DECODED-DATE-TIME) (DEFAULT-VALUES DECODED-DATE-TIME)))", ((cpp_function_code)(&today)), NULL);
      defineFunctionObject("TOMORROW", "(DEFUN TOMORROW ((PARSED-VALUES DECODED-DATE-TIME) (DEFAULT-VALUES DECODED-DATE-TIME)))", ((cpp_function_code)(&tomorrow)), NULL);
      defineFunctionObject("NOW", "(DEFUN NOW ((PARSED-VALUES DECODED-DATE-TIME) (DEFAULT-VALUES DECODED-DATE-TIME)))", ((cpp_function_code)(&now)), NULL);
      defineFunctionObject("AM-PM", "(DEFUN (AM-PM SYMBOL) ((STRING OBJECT)))", ((cpp_function_code)(&amPm)), NULL);
      defineFunctionObject("ERA", "(DEFUN (ERA SYMBOL) ((STRING OBJECT)))", ((cpp_function_code)(&era)), NULL);
      defineFunctionObject("NOON-MIDN", "(DEFUN (NOON-MIDN SYMBOL) ((STRING OBJECT)))", ((cpp_function_code)(&noonMidn)), NULL);
      defineFunctionObject("WEEKDAY", "(DEFUN (WEEKDAY KEYWORD) ((THING OBJECT)))", ((cpp_function_code)(&weekday)), NULL);
      defineFunctionObject("MONTH", "(DEFUN (MONTH INTEGER-WRAPPER) ((THING OBJECT)))", ((cpp_function_code)(&month)), NULL);
      defineFunctionObject("ZONE", "(DEFUN (ZONE FLOAT-WRAPPER) ((THING OBJECT)))", ((cpp_function_code)(&zone)), NULL);
      defineFunctionObject("SPECIALP", "(DEFUN (SPECIALP SYMBOL) ((STRING OBJECT)))", ((cpp_function_code)(&specialp)), NULL);
      defineFunctionObject("SECONDP", "(DEFUN (SECONDP BOOLEAN-WRAPPER) ((NUMBER OBJECT)))", ((cpp_function_code)(&secondp)), NULL);
      defineFunctionObject("MINUTE", "(DEFUN (MINUTE BOOLEAN-WRAPPER) ((NUMBER OBJECT)))", ((cpp_function_code)(&minute)), NULL);
      defineFunctionObject("ZONE-MINUTE", "(DEFUN (ZONE-MINUTE BOOLEAN-WRAPPER) ((NUMBER OBJECT)))", ((cpp_function_code)(&zoneMinute)), NULL);
      defineFunctionObject("HOUR", "(DEFUN (HOUR BOOLEAN-WRAPPER) ((NUMBER OBJECT)))", ((cpp_function_code)(&hour)), NULL);
      defineFunctionObject("DAY", "(DEFUN (DAY BOOLEAN-WRAPPER) ((NUMBER OBJECT)))", ((cpp_function_code)(&day)), NULL);
      defineFunctionObject("YEAR", "(DEFUN (YEAR BOOLEAN-WRAPPER) ((NUMBER OBJECT)))", ((cpp_function_code)(&year)), NULL);
      defineFunctionObject("TIME-DIVIDER", "(DEFUN (TIME-DIVIDER BOOLEAN-WRAPPER) ((THECHARACTER OBJECT)))", ((cpp_function_code)(&timeDivider)), NULL);
      defineFunctionObject("DATE-DIVIDER", "(DEFUN (DATE-DIVIDER BOOLEAN-WRAPPER) ((THECHARACTER OBJECT)))", ((cpp_function_code)(&dateDivider)), NULL);
      defineFunctionObject("DATE-TIME-DIVIDER", "(DEFUN (DATE-TIME-DIVIDER BOOLEAN-WRAPPER) ((THECHARACTER OBJECT)))", ((cpp_function_code)(&dateTimeDivider)), NULL);
      defineFunctionObject("MATCH-SUBSTRING", "(DEFUN (MATCH-SUBSTRING CONS) ((SUBSTRING STRING) (PARSING-TIME? BOOLEAN)))", ((cpp_function_code)(&matchSubstring)), NULL);
      defineFunctionObject("DIGIT-VALUE", "(DEFUN (DIGIT-VALUE INTEGER) ((CHAR CHARACTER)))", ((cpp_function_code)(&digitValue)), NULL);
      defineFunctionObject("DECOMPOSE-DATE-TIME-STRING", "(DEFUN (DECOMPOSE-DATE-TIME-STRING CONS) ((STRING STRING) (START INTEGER) (END INTEGER)))", ((cpp_function_code)(&decomposeDateTimeString)), NULL);
      defineFunctionObject("MATCH-PATTERN-ELEMENT", "(DEFUN (MATCH-PATTERN-ELEMENT CONS) ((PATTERN-ELEMENT SYMBOL) (DATUM-ELEMENT OBJECT)))", ((cpp_function_code)(&matchPatternElement)), NULL);
      defineFunctionObject("MATCH-PATTERN", "(DEFUN (MATCH-PATTERN CONS) ((PATTERN CONS) (DATUM CONS) (DATUM-LENGTH INTEGER)))", ((cpp_function_code)(&matchPattern)), NULL);
      defineFunctionObject("DEAL-WITH-NOON-MIDN", "(DEFUN DEAL-WITH-NOON-MIDN ((FORM-VALUE OBJECT) (PARSED-VALUES DECODED-DATE-TIME)))", ((cpp_function_code)(&dealWithNoonMidn)), NULL);
      defineFunctionObject("DEAL-WITH-AM-PM", "(DEFUN DEAL-WITH-AM-PM ((FORM-VALUE OBJECT) (PARSED-VALUES DECODED-DATE-TIME)))", ((cpp_function_code)(&dealWithAmPm)), NULL);
      defineFunctionObject("DEAL-WITH-ERA", "(DEFUN DEAL-WITH-ERA ((FORM-VALUE OBJECT) (PARSED-VALUES DECODED-DATE-TIME)))", ((cpp_function_code)(&dealWithEra)), NULL);
      defineFunctionObject("SET-TIME-VALUES", "(DEFUN SET-TIME-VALUES ((STRING-FORM (CONS OF CONS)) (PARSED-VALUES DECODED-DATE-TIME) (DEFAULT-VALUES DECODED-DATE-TIME)))", ((cpp_function_code)(&setTimeValues)), NULL);
      defineFunctionObject("MATCH-DATE-TIME-PATTERNS", "(DEFUN (MATCH-DATE-TIME-PATTERNS CONS) ((DATE-TIME-STRING STRING) (START INTEGER) (END INTEGER) (ERROR-ON-MISMATCH? BOOLEAN)))", ((cpp_function_code)(&matchDateTimePatterns)), NULL);
      defineFunctionObject("HELP-PARSE-DATE-TIME-RELATIVE-TO-BASE", "(DEFUN (HELP-PARSE-DATE-TIME-RELATIVE-TO-BASE DECODED-DATE-TIME) ((DATE-TIME-STRING STRING) (BASE-DATE-TIME DECODED-DATE-TIME) (START INTEGER) (END INTEGER) (ERROR-ON-MISMATCH? BOOLEAN) (MERGE-NULL-FIELDS? BOOLEAN)) :PUBLIC? FALSE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&helpParseDateTimeRelativeToBase)), NULL);
      defineFunctionObject("PARSE-DATE-TIME-RELATIVE-TO-BASE", "(DEFUN (PARSE-DATE-TIME-RELATIVE-TO-BASE DECODED-DATE-TIME) ((DATE-TIME-STRING STRING) (BASE-DATE-TIME DECODED-DATE-TIME) (START INTEGER) (END INTEGER) (ERROR-ON-MISMATCH? BOOLEAN) (MERGE-NULL-FIELDS? BOOLEAN)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE :DOCUMENTATION \"Tries very hard to make sense out of the argument `date-time-string' and\nreturns a time structure if successful.  If not, it returns `null'.\nIf `error-on-mismatch?' is true, parse-date-time will signal an error instead of\nreturning `null'.\nDefault values are passed in via `base-date-time'.  If the timezone field that\nis passed in is NULL, then the local time zone for the parsed date/time will\nbe used.\nIf `merge-null-fields?' is `true', then default values from `base-time-date'\nwill be merged into missing components.  If `false', then they won't be merged\nin for null components but can still be used as a basis for interpreatation of\nrelative time strings like \\\"now\\\" or \\\"yesterday\\\"\")", ((cpp_function_code)(&parseDateTimeRelativeToBase)), NULL);
      defineFunctionObject("PARSE-DATE-TIME-IN-TIME-ZONE", "(DEFUN (PARSE-DATE-TIME-IN-TIME-ZONE DECODED-DATE-TIME) ((DATE-TIME-STRING STRING) (TIME-ZONE FLOAT) (START INTEGER) (END INTEGER) (ERROR-ON-MISMATCH? BOOLEAN)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE :DOCUMENTATION \"Tries very hard to make sense out of the argument `date-time-string' and\nreturns a time structure if successful.  If not, it returns `null'.\nIf `error-on-mismatch?' is true, parse-date-time will signal an error instead of\nreturning `null'.  \nDefault values are 00:00:00 in the given timezone on the current date.  If the\ngiven `time-zone' value is `null', then the local time zone for the given date\nand time will be used as determined by the operating system.\")", ((cpp_function_code)(&parseDateTimeInTimeZone)), NULL);
      defineFunctionObject("PARSE-DATE-TIME", "(DEFUN (PARSE-DATE-TIME DECODED-DATE-TIME) ((DATE-TIME-STRING STRING) (START INTEGER) (END INTEGER) (ERROR-ON-MISMATCH? BOOLEAN)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :CONSTRUCTOR? TRUE :DOCUMENTATION \"Tries very hard to make sense out of the argument `date-time-string' and\nreturns a time structure if successful.  If not, it returns `null'.\nIf `error-on-mismatch?' is true, parse-date-time will signal an error instead of\nreturning `null'.  \nDefault values are 00:00:00 local time on the current date\" (RETURN (PARSE-DATE-TIME-IN-TIME-ZONE DATE-TIME-STRING NULL START END ERROR-ON-MISMATCH?)))", ((cpp_function_code)(&parseDateTime)), NULL);
      defineFunctionObject("STRING-TO-DECODED-DATE-TIME", "(DEFUN (STRING-TO-DECODED-DATE-TIME DECODED-DATE-TIME) ((INPUT STRING)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE :DOCUMENTATION \"Returns a decoded date-time object representing the date\nand time parsed from the `input' string.  If no valid parse is found,\n`null' is returned.\")", ((cpp_function_code)(((DecodedDateTime*  (*) (const char*))(&stringToDecodedDateTime)))), NULL);
      defineFunctionObject("STRING-TO-CALENDAR-DATE", "(DEFUN (STRING-TO-CALENDAR-DATE CALENDAR-DATE) ((INPUT STRING)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE :DOCUMENTATION \"Returns a calendar date object representing the date and time\nparsed from the `input' string.  If no valid parse is found,\n`null' is returned.\")", ((cpp_function_code)(((CalendarDate*  (*) (const char*))(&stringToCalendarDate)))), NULL);
      defineFunctionObject("STRING-TO-CALENDAR-DATE-WITH-DEFAULT", "(DEFUN (STRING-TO-CALENDAR-DATE-WITH-DEFAULT CALENDAR-DATE) ((INPUT-DATE STRING) (DEFAULT-DATE DECODED-DATE-TIME)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE :DOCUMENTATION \"Returns a calendar date object representing the date and time\nparsed from the `input-date' string.  Default values for missing fields and\nthe interpretation of relative references come from `default-date'.  If the\n`default-date' is `null', the current date will be used.  If a null set of\ndefaults is desired, use `*NULL-DECODED-DATE-TIME*'.\nIf no valid parse is found, `null' is returned.\")", ((cpp_function_code)(((CalendarDate*  (*) (const char*, DecodedDateTime*))(&stringToCalendarDateWithDefault)))), NULL);
      defineFunctionObject("STARTUP-DATE-TIME-PARSER", "(DEFUN STARTUP-DATE-TIME-PARSER () :PUBLIC? TRUE)", ((cpp_function_code)(&startupDateTimeParser)), NULL);
      { MethodSlot* function = lookupFunction(SYM_DATE_TIME_PARSER_STELLA_STARTUP_DATE_TIME_PARSER);

        setDynamicSlotValue(function->dynamicSlots, SYM_DATE_TIME_PARSER_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupDateTimeParser"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFCONSTANT WHITESPACE-CHARS CONS (BQUOTE (#\\  #\\Tab #\\Linefeed #\\Return #\\Page #\\, #\\' #\\`)))", &WHITESPACE_CHARS);
      defineGlobalVariableObject("(DEFCONSTANT TIME-DIVIDERS CONS (BQUOTE (#\\: #\\.)))", &TIME_DIVIDERS);
      defineGlobalVariableObject("(DEFCONSTANT DATE-DIVIDERS CONS (BQUOTE (#\\\\ #\\/ #\\- #\\+)))", &DATE_DIVIDERS);
      defineGlobalVariableObject("(DEFCONSTANT DATE-TIME-DIVIDERS CONS (BQUOTE (#\\T)))", &DATE_TIME_DIVIDERS);
      defineGlobalVariableObject("(DEFSPECIAL *ERROR-ON-MISMATCH* BOOLEAN FALSE :PUBLIC? TRUE :DOCUMENTATION \"If TRUE, an error will be signalled if parse-date-time is unable\n   to determine the time/date format of the string.\")", &oERROR_ON_MISMATCHo);
      defineGlobalVariableObject("(DEFSPECIAL *WEEKDAY-STRINGS* (STRING-HASH-TABLE OF STRING KEYWORD) (NEW (STRING-HASH-TABLE OF STRING KEYWORD)))", &oWEEKDAY_STRINGSo);
      defineGlobalVariableObject("(DEFSPECIAL *MONTH-STRINGS* STRING-TO-INTEGER-HASH-TABLE (NEW STRING-TO-INTEGER-HASH-TABLE))", &oMONTH_STRINGSo);
      defineGlobalVariableObject("(DEFSPECIAL *ZONE-STRINGS* (STRING-HASH-TABLE OF STRING FLOAT-WRAPPER) (NEW (STRING-HASH-TABLE OF STRING FLOAT-WRAPPER)))", &oZONE_STRINGSo);
      defineGlobalVariableObject("(DEFSPECIAL *ERA-STRINGS* (STRING-HASH-TABLE OF STRING SYMBOL) (NEW (STRING-HASH-TABLE OF STRING SYMBOL)))", &oERA_STRINGSo);
      defineGlobalVariableObject("(DEFSPECIAL *SPECIAL-STRINGS* STRING-HASH-TABLE (NEW STRING-HASH-TABLE))", &oSPECIAL_STRINGSo);
      defineGlobalVariableObject("(DEFSPECIAL *SPECIAL-SYMBOLS* (CONS OF SYMBOL) (BQUOTE (YESTERDAY TODAY TOMORROW NOW)))", &oSPECIAL_SYMBOLSo);
      defineGlobalVariableObject("(DEFSPECIAL *DATE-TIME-PATTERNS* CONS (BQUOTE ((YEAR (DATE-DIVIDER) MONTH (DATE-DIVIDER) DAY (NOON-MIDN)) ((NOON-MIDN) (WEEKDAY) MONTH (DATE-DIVIDER) DAY (DATE-DIVIDER) YEAR) ((NOON-MIDN) (WEEKDAY) DAY (DATE-DIVIDER) MONTH (DATE-DIVIDER) YEAR) ((NOON-MIDN) (WEEKDAY) MONTH (DATE-DIVIDER) DAY) ((NOON-MIDN) YEAR (DATE-DIVIDER) MONTH (DATE-DIVIDER) DAY) ((NOON-MIDN) MONTH (DATE-DIVIDER) YEAR) ((NOON-MIDN) YEAR (DATE-DIVIDER) MONTH) ((DATE-TIME-DIVIDER) HOUR (TIME-DIVIDER) (MINUTE) (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) (NOON-MIDN (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) ((DATE-TIME-DIVIDER) HOUR (NOON-MIDN)) (YEAR (DATE-DIVIDER) MONTH (DATE-DIVIDER) DAY (DATE-TIME-DIVIDER) HOUR (TIME-DIVIDER) (MINUTE) (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) (YEAR (DATE-DIVIDER) MONTH (DATE-DIVIDER) DAY NOON-MIDN (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) (YEAR (DATE-DIVIDER) MONTH (DATE-DIVIDER) DAY NOW) ((WEEKDAY) MONT" "H (DATE-DIVIDER) DAY (DATE-DIVIDER) YEAR (DATE-TIME-DIVIDER) HOUR (TIME-DIVIDER) (MINUTE) (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) ((WEEKDAY) DAY (DATE-DIVIDER) MONTH (DATE-DIVIDER) YEAR (DATE-TIME-DIVIDER) HOUR (TIME-DIVIDER) (MINUTE) (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) ((WEEKDAY) MONTH (DATE-DIVIDER) DAY (DATE-TIME-DIVIDER) HOUR (TIME-DIVIDER) (MINUTE) (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) (MONTH (DATE-DIVIDER) YEAR (DATE-TIME-DIVIDER) HOUR (TIME-DIVIDER) (MINUTE) (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) (YEAR (DATE-DIVIDER) MONTH (DATE-TIME-DIVIDER) HOUR (TIME-DIVIDER) (MINUTE) (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) ((WEEKDAY) MONTH (DATE-DIVIDER) DAY (DATE-DIVIDER) YEAR (NOON-MIDN) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) ((WEEKDAY) DAY (DATE-DIVIDER) MONTH (DATE-DIVI" "DER) YEAR (NOON-MIDN) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) ((WEEKDAY) MONTH (DATE-DIVIDER) DAY (NOON-MIDN) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) (MONTH (DATE-DIVIDER) YEAR (NOON-MIDN) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) (YEAR (DATE-DIVIDER) MONTH (NOON-MIDN) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) ((DATE-TIME-DIVIDER) HOUR (TIME-DIVIDER) (MINUTE) (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE) (WEEKDAY) MONTH (DATE-DIVIDER) DAY (DATE-DIVIDER) YEAR) ((DATE-TIME-DIVIDER) HOUR (TIME-DIVIDER) (MINUTE) (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE) (WEEKDAY) DAY (DATE-DIVIDER) MONTH (DATE-DIVIDER) YEAR) ((DATE-TIME-DIVIDER) HOUR (TIME-DIVIDER) (MINUTE) (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE) (WEEKDAY) MONTH (DATE-DIVIDER) DAY) ((DATE-TIME-DIVIDER) HOUR (TIME-DIVIDER) (MINUTE) (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDE" "R) (ZONE-MINUTE) YEAR (DATE-DIVIDER) MONTH (DATE-DIVIDER) DAY) ((DATE-TIME-DIVIDER) HOUR (TIME-DIVIDER) (MINUTE) (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE) MONTH (DATE-DIVIDER) YEAR) ((DATE-TIME-DIVIDER) HOUR (TIME-DIVIDER) (MINUTE) (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE) YEAR (DATE-DIVIDER) MONTH) (WEEKDAY MONTH DAY HOUR (TIME-DIVIDER) MINUTE (TIME-DIVIDER) SECONDP (AM-PM) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE) YEAR) ((WEEKDAY) DAY (DATE-DIVIDER) MONTH (DATE-DIVIDER) YEAR HOUR (TIME-DIVIDER) MINUTE (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) ((WEEKDAY) MONTH (DATE-DIVIDER) DAY (DATE-DIVIDER) YEAR HOUR (TIME-DIVIDER) MINUTE (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) (YEAR (DATE-DIVIDER) (MONTH)) (MONTH (DATE-DIVIDER) (YEAR)) ((WEEKDAY) MONTH DAY HOUR TIME-DIVIDER MINUTE (TIME-DIVIDER) (SECONDP) YEAR) (NOW (YESTERDAY)) ((YESTERDAY) NOW) (NOW (TODA" "Y)) ((TODAY) NOW) (NOW (TOMORROW)) ((TOMORROW) NOW) (YESTERDAY (NOON-MIDN)) ((NOON-MIDN) YESTERDAY) (TODAY (NOON-MIDN)) ((NOON-MIDN) TODAY) (TOMORROW (NOON-MIDN)) ((NOON-MIDN) TOMORROW) (YESTERDAY HOUR (TIME-DIVIDER) (MINUTE) (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) (TOMORROW HOUR (TIME-DIVIDER) (MINUTE) (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)) (TODAY HOUR (TIME-DIVIDER) (MINUTE) (TIME-DIVIDER) (SECONDP) (AM-PM) (DATE-DIVIDER) (ZONE) (TIME-DIVIDER) (ZONE-MINUTE)))))", &oDATE_TIME_PATTERNSo);
    }
  }
}

Symbol* SYM_DATE_TIME_PARSER_STELLA_FOREACH = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_ITEM = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_IN = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_CAST = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_CONS = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_OF = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_DO = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_INSERT_AT = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_FIRST = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_SECOND = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_YESTERDAY = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_TODAY = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_TOMORROW = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_NOW = NULL;

Keyword* KWD_DATE_TIME_PARSER_MONDAY = NULL;

Keyword* KWD_DATE_TIME_PARSER_TUESDAY = NULL;

Keyword* KWD_DATE_TIME_PARSER_WEDNESDAY = NULL;

Keyword* KWD_DATE_TIME_PARSER_THURSDAY = NULL;

Keyword* KWD_DATE_TIME_PARSER_FRIDAY = NULL;

Keyword* KWD_DATE_TIME_PARSER_SATURDAY = NULL;

Keyword* KWD_DATE_TIME_PARSER_SUNDAY = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_BCE = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_CE = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_YEAR = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_DATE_DIVIDER = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_MONTH = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_DAY = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_NOON_MIDN = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_WEEKDAY = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_DATE_TIME_DIVIDER = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_HOUR = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_TIME_DIVIDER = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_MINUTE = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_SECONDP = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_AM_PM = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_ZONE = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_ZONE_MINUTE = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_AM = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_PM = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_NOON = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_MIDN = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_SPECIAL = NULL;

Keyword* KWD_DATE_TIME_PARSER_LETTER = NULL;

Keyword* KWD_DATE_TIME_PARSER_DIGIT = NULL;

Surrogate* SGT_DATE_TIME_PARSER_STELLA_CONS = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_ERA = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_STARTUP_DATE_TIME_PARSER = NULL;

Symbol* SYM_DATE_TIME_PARSER_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
