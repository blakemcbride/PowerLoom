//  -*- Mode: C++ -*-

// timepoint-support.cc

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
 | The Original Code is the PowerLoom KR&R System.                            |
 |                                                                            |
 | The Initial Developer of the Original Code is                              |
 | UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |
 | 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |
 |                                                                            |
 | Portions created by the Initial Developer are Copyright (C) 1997-2023      |
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
 +----------------------------- END LICENSE BLOCK ----------------------------+
*/

#include "logic/extensions/powerloom-extensions-system.hh"

namespace timepoint {
  using namespace stella_utilities;
  using namespace stella;
  using namespace logic;

// Table for interning date-time logic wrappers
StellaHashTable* oDATE_TIME_HASH_TABLEo = NULL;

DateTimeLogicWrapper* newDateTimeLogicWrapper(DateTimeObject* wrapperValue) {
  { DateTimeLogicWrapper* self = NULL;

    self = new DateTimeLogicWrapper();
    self->wrapperValue = wrapperValue;
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    self->functionTerm = NULL;
    return (self);
  }
}

Surrogate* DateTimeLogicWrapper::primaryType() {
  { DateTimeLogicWrapper* self = this;

    return (SGT_TIMEPOINT_SUPPORT_TIMEPOINT_SUPPORT_DATE_TIME_LOGIC_WRAPPER);
  }
}

Object* accessDateTimeLogicWrapperSlotValue(DateTimeLogicWrapper* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (TRUE) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

void DateTimeLogicWrapper::printObject(std::ostream* stream) {
  { DateTimeLogicWrapper* self = this;

    if (oPRINTREADABLYpo) {
      *(stream) << ((DateTimeObject*)(self->wrapperValue));
    }
    else {
      *(stream) << "|tw|" << ((DateTimeObject*)(self->wrapperValue));
    }
  }
}

Object* DateTimeLogicWrapper::generateSpecializedTerm() {
  { DateTimeLogicWrapper* self = this;

    { Cons* term = self->functionTerm;
      DateTimeObject* datetime = ((DateTimeObject*)(self->wrapperValue));

      if (((boolean)(term))) {
        return (term);
      }
      else if (((boolean)(datetime))) {
        { Surrogate* testValue000 = safePrimaryType(datetime);

          if (subtypeOfP(testValue000, SGT_TIMEPOINT_SUPPORT_STELLA_CALENDAR_DATE)) {
            { DateTimeObject* datetime000 = datetime;
              CalendarDate* datetime = ((CalendarDate*)(datetime000));

              term = cons(generateTerm(SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_TIMEPOINT_OF), cons(wrapString(datetime->calendarDateToString(0.0, false, true)), NIL));
            }
          }
          else if (subtypeOfP(testValue000, SGT_TIMEPOINT_SUPPORT_STELLA_TIME_DURATION)) {
            { DateTimeObject* datetime001 = datetime;
              TimeDuration* datetime = ((TimeDuration*)(datetime001));

              term = cons(generateTerm(SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_DURATION_OF), cons(wrapString(datetime->timeDurationToString()), NIL));
            }
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
        self->functionTerm = term;
        return (term);
      }
      else {
        throw *newTermGenerationException(self, "Date Time Number Wrapper doesn't have a value.");
      }
    }
  }
}

int DateTimeLogicWrapper::hashCode() {
  { DateTimeLogicWrapper* self = this;

    if (((boolean)(((DateTimeObject*)(self->wrapperValue))))) {
      return (((DateTimeObject*)(self->wrapperValue))->hashCode());
    }
    else {
      return (0);
    }
  }
}

boolean DateTimeLogicWrapper::objectEqlP(Object* x) {
  { DateTimeLogicWrapper* self = this;

    if (subtypeOfP(safePrimaryType(x), SGT_TIMEPOINT_SUPPORT_TIMEPOINT_SUPPORT_DATE_TIME_LOGIC_WRAPPER)) {
      { Object* x000 = x;
        DateTimeLogicWrapper* x = ((DateTimeLogicWrapper*)(x000));

        return (((DateTimeObject*)(self->wrapperValue))->objectEqlP(((DateTimeObject*)(x->wrapperValue))));
      }
    }
    else {
      return (false);
    }
  }
}

DateTimeLogicWrapper* wrapDateTime(DateTimeObject* value) {
  // Return an interned LOGIC-WRAPPER for `value'.  This assures us
  // that all logic-wrapped DATE-TIME-OBJECTs are the same object.
  { DateTimeLogicWrapper* wrapper = ((DateTimeLogicWrapper*)(oDATE_TIME_HASH_TABLEo->lookup(value)));

    if (!((boolean)(wrapper))) {
      wrapper = newDateTimeLogicWrapper(value);
      oDATE_TIME_HASH_TABLEo->insertAt(value, wrapper);
    }
    return (wrapper);
  }
}

DateTimeLogicWrapper* helpGetCalendarTime(Object* item) {
  { Surrogate* testValue000 = safePrimaryType(item);

    if (subtypeOfStringP(testValue000)) {
      { Object* item000 = item;
        StringWrapper* item = ((StringWrapper*)(item000));

        { CalendarDate* value = stringToCalendarDate(item->wrapperValue);

          if (((boolean)(value))) {
            return (wrapDateTime(value));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_TIMEPOINT_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
      { Object* item001 = item;
        PatternVariable* item = ((PatternVariable*)(item001));

        { Object* value = safeBoundTo(item);

          if (((boolean)(value))) {
            return (helpGetCalendarTime(value));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_TIMEPOINT_SUPPORT_TIMEPOINT_SUPPORT_DATE_TIME_LOGIC_WRAPPER)) {
      { Object* item002 = item;
        DateTimeLogicWrapper* item = ((DateTimeLogicWrapper*)(item002));

        return (item);
      }
    }
    else if (subtypeOfP(testValue000, SGT_TIMEPOINT_SUPPORT_LOGIC_SKOLEM)) {
      { Object* item003 = item;
        Skolem* item = ((Skolem*)(item003));

        { Object* value = ((Object*)(accessInContext(item->variableValue, item->homeContext, false)));

          if (!((boolean)(value))) {
            return (NULL);
          }
          { Surrogate* testValue001 = safePrimaryType(value);

            if (subtypeOfP(testValue001, SGT_TIMEPOINT_SUPPORT_TIMEPOINT_SUPPORT_DATE_TIME_LOGIC_WRAPPER)) {
              { Object* value000 = value;
                DateTimeLogicWrapper* value = ((DateTimeLogicWrapper*)(value000));

                return (value);
              }
            }
            else if (subtypeOfP(testValue001, SGT_TIMEPOINT_SUPPORT_LOGIC_SKOLEM)) {
              { Object* value001 = value;
                Skolem* value = ((Skolem*)(value001));

                if (isaP(((Object*)(accessInContext(value->variableValue, value->homeContext, false))), SGT_TIMEPOINT_SUPPORT_LOGIC_SKOLEM)) {
                  return (NULL);
                }
                else {
                  return (helpGetCalendarTime(((Object*)(accessInContext(value->variableValue, value->homeContext, false)))));
                }
              }
            }
            else {
              if (isaP(((Object*)(accessInContext(item->variableValue, item->homeContext, false))), SGT_TIMEPOINT_SUPPORT_LOGIC_SKOLEM)) {
                return (NULL);
              }
              else {
                return (helpGetCalendarTime(((Object*)(accessInContext(item->variableValue, item->homeContext, false)))));
              }
            }
          }
        }
      }
    }
    else {
      return (NULL);
    }
  }
}

DateTimeLogicWrapper* helpGetTimeDuration(Object* item) {
  { Surrogate* testValue000 = safePrimaryType(item);

    if (subtypeOfStringP(testValue000)) {
      { Object* item000 = item;
        StringWrapper* item = ((StringWrapper*)(item000));

        { TimeDuration* value = stringToTimeDuration(item->wrapperValue);

          if (((boolean)(value))) {
            return (wrapDateTime(value));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_TIMEPOINT_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
      { Object* item001 = item;
        PatternVariable* item = ((PatternVariable*)(item001));

        { Object* value = safeBoundTo(item);

          if (((boolean)(value))) {
            return (helpGetTimeDuration(value));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_TIMEPOINT_SUPPORT_TIMEPOINT_SUPPORT_DATE_TIME_LOGIC_WRAPPER)) {
      { Object* item002 = item;
        DateTimeLogicWrapper* item = ((DateTimeLogicWrapper*)(item002));

        return (item);
      }
    }
    else if (subtypeOfP(testValue000, SGT_TIMEPOINT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER)) {
      { Object* item003 = item;
        units::DimNumberLogicWrapper* item = ((units::DimNumberLogicWrapper*)(item003));

        try {
          return (wrapDateTime(dimToTimeDuration(((DimNumber*)(item->wrapperValue)))));
        }
        catch (IncompatibleUnitsException ) {
          return (NULL);
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_TIMEPOINT_SUPPORT_LOGIC_SKOLEM)) {
      { Object* item004 = item;
        Skolem* item = ((Skolem*)(item004));

        { Object* value = ((Object*)(accessInContext(item->variableValue, item->homeContext, false)));

          if (!((boolean)(value))) {
            return (NULL);
          }
          { Surrogate* testValue001 = safePrimaryType(value);

            if (subtypeOfP(testValue001, SGT_TIMEPOINT_SUPPORT_TIMEPOINT_SUPPORT_DATE_TIME_LOGIC_WRAPPER)) {
              { Object* value000 = value;
                DateTimeLogicWrapper* value = ((DateTimeLogicWrapper*)(value000));

                return (value);
              }
            }
            else if (subtypeOfP(testValue001, SGT_TIMEPOINT_SUPPORT_LOGIC_SKOLEM)) {
              { Object* value001 = value;
                Skolem* value = ((Skolem*)(value001));

                if (isaP(((Object*)(accessInContext(value->variableValue, value->homeContext, false))), SGT_TIMEPOINT_SUPPORT_LOGIC_SKOLEM)) {
                  return (NULL);
                }
                else {
                  return (helpGetTimeDuration(((Object*)(accessInContext(value->variableValue, value->homeContext, false)))));
                }
              }
            }
            else {
              if (isaP(((Object*)(accessInContext(item->variableValue, item->homeContext, false))), SGT_TIMEPOINT_SUPPORT_LOGIC_SKOLEM)) {
                return (NULL);
              }
              else {
                return (helpGetTimeDuration(((Object*)(accessInContext(item->variableValue, item->homeContext, false)))));
              }
            }
          }
        }
      }
    }
    else {
      return (NULL);
    }
  }
}

DateTimeLogicWrapper* helpGetTimeObject(Object* item) {
  { Surrogate* testValue000 = safePrimaryType(item);

    if (subtypeOfStringP(testValue000)) {
      { Object* item000 = item;
        StringWrapper* item = ((StringWrapper*)(item000));

        { DateTimeObject* value = stringToCalendarDate(item->wrapperValue);

          if (!((boolean)(value))) {
            value = stringToTimeDuration(item->wrapperValue);
          }
          if (((boolean)(value))) {
            return (wrapDateTime(value));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_TIMEPOINT_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
      { Object* item001 = item;
        PatternVariable* item = ((PatternVariable*)(item001));

        { Object* value = safeBoundTo(item);

          if (((boolean)(value))) {
            return (helpGetTimeObject(value));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_TIMEPOINT_SUPPORT_TIMEPOINT_SUPPORT_DATE_TIME_LOGIC_WRAPPER)) {
      { Object* item002 = item;
        DateTimeLogicWrapper* item = ((DateTimeLogicWrapper*)(item002));

        return (item);
      }
    }
    else if (subtypeOfP(testValue000, SGT_TIMEPOINT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER)) {
      { Object* item003 = item;
        units::DimNumberLogicWrapper* item = ((units::DimNumberLogicWrapper*)(item003));

        try {
          return (wrapDateTime(dimToTimeDuration(((DimNumber*)(item->wrapperValue)))));
        }
        catch (IncompatibleUnitsException ) {
          return (NULL);
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_TIMEPOINT_SUPPORT_LOGIC_SKOLEM)) {
      { Object* item004 = item;
        Skolem* item = ((Skolem*)(item004));

        { Object* value = ((Object*)(accessInContext(item->variableValue, item->homeContext, false)));

          { Surrogate* testValue001 = safePrimaryType(value);

            if (subtypeOfP(testValue001, SGT_TIMEPOINT_SUPPORT_TIMEPOINT_SUPPORT_DATE_TIME_LOGIC_WRAPPER)) {
              { Object* value000 = value;
                DateTimeLogicWrapper* value = ((DateTimeLogicWrapper*)(value000));

                return (value);
              }
            }
            else if (subtypeOfP(testValue001, SGT_TIMEPOINT_SUPPORT_LOGIC_SKOLEM)) {
              { Object* value001 = value;
                Skolem* value = ((Skolem*)(value001));

                if (isaP(((Object*)(accessInContext(value->variableValue, value->homeContext, false))), SGT_TIMEPOINT_SUPPORT_LOGIC_SKOLEM)) {
                  return (NULL);
                }
                else {
                  return (helpGetTimeObject(((Object*)(accessInContext(value->variableValue, value->homeContext, false)))));
                }
              }
            }
            else {
              if (isaP(((Object*)(accessInContext(item->variableValue, item->homeContext, false))), SGT_TIMEPOINT_SUPPORT_LOGIC_SKOLEM)) {
                return (NULL);
              }
              else {
                return (helpGetTimeObject(((Object*)(accessInContext(item->variableValue, item->homeContext, false)))));
              }
            }
          }
        }
      }
    }
    else {
      return (NULL);
    }
  }
}

int helpGetInteger(Object* obj) {
  if (!((boolean)(obj))) {
    return (NULL_INTEGER);
  }
  else {
    { Surrogate* testValue000 = safePrimaryType(obj);

      if (subtypeOfFloatP(testValue000)) {
        { Object* obj000 = obj;
          FloatWrapper* obj = ((FloatWrapper*)(obj000));

          if (integerValuedP(obj->wrapperValue)) {
            return (stella::floor(obj->wrapperValue));
          }
          else {
            return (NULL_INTEGER);
          }
        }
      }
      else if (subtypeOfIntegerP(testValue000)) {
        { Object* obj001 = obj;
          IntegerWrapper* obj = ((IntegerWrapper*)(obj001));

          return (obj->wrapperValue);
        }
      }
      else {
        return (NULL_INTEGER);
      }
    }
  }
}

double helpGetFloat(Object* obj) {
  if (!((boolean)(obj))) {
    return (NULL_FLOAT);
  }
  else {
    { Surrogate* testValue000 = safePrimaryType(obj);

      if (subtypeOfFloatP(testValue000)) {
        { Object* obj000 = obj;
          FloatWrapper* obj = ((FloatWrapper*)(obj000));

          return (obj->wrapperValue);
        }
      }
      else if (subtypeOfIntegerP(testValue000)) {
        { Object* obj001 = obj;
          IntegerWrapper* obj = ((IntegerWrapper*)(obj001));

          return (((double)(obj->wrapperValue)));
        }
      }
      else {
        return (NULL_FLOAT);
      }
    }
  }
}

double helpGetTimezone(Object* obj) {
  if (!((boolean)(obj))) {
    return (NULL_FLOAT);
  }
  else {
    { Surrogate* testValue000 = safePrimaryType(obj);

      if (subtypeOfFloatP(testValue000)) {
        { Object* obj000 = obj;
          FloatWrapper* obj = ((FloatWrapper*)(obj000));

          return (obj->wrapperValue);
        }
      }
      else if (subtypeOfIntegerP(testValue000)) {
        { Object* obj001 = obj;
          IntegerWrapper* obj = ((IntegerWrapper*)(obj001));

          return (((double)(obj->wrapperValue)));
        }
      }
      else if (subtypeOfStringP(testValue000)) {
        { Object* obj002 = obj;
          StringWrapper* obj = ((StringWrapper*)(obj002));

          { FloatWrapper* decodedZone = zone(wrapString(stringDowncase(obj->wrapperValue)));

            if (((boolean)(decodedZone)) &&
                (!nullWrapperP(decodedZone))) {
              return (decodedZone->wrapperValue);
            }
            else if (((boolean)(decodedZone))) {
              return (getLocalTimeZone());
            }
            else {
              return (NULL_FLOAT);
            }
          }
        }
      }
      else {
        return (NULL_FLOAT);
      }
    }
  }
}

boolean isCurrentTimeSpecP(Object* spec) {
  if (subtypeOfStringP(safePrimaryType(spec))) {
    { Object* spec000 = spec;
      StringWrapper* spec = ((StringWrapper*)(spec000));

      return (stringEqualP(spec->wrapperValue, "now"));
    }
  }
  else {
    return (false);
  }
}

boolean canBindAllP(Cons* plObjects, Cons* values) {
  { Object* obj = NULL;
    Cons* iter000 = plObjects;
    Object* value = NULL;
    Cons* iter001 = values;

    for  (; (!(iter000 == NIL)) &&
              (!(iter001 == NIL)); 
          iter000 = iter000->rest,
          iter001 = iter001->rest) {
      obj = iter000->value;
      value = iter001->value;
      { Surrogate* testValue000 = safePrimaryType(obj);

        if (subtypeOfP(testValue000, SGT_TIMEPOINT_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
          { Object* obj000 = obj;
            PatternVariable* obj = ((PatternVariable*)(obj000));

            if (!(bindVariableToValueP(obj, value, true))) {
              return (false);
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_TIMEPOINT_SUPPORT_LOGIC_SKOLEM)) {
          { Object* obj001 = obj;
            Skolem* obj = ((Skolem*)(obj001));

            { Skolem* object000 = obj;
              Object* value000 = value;
              Object* oldValue000 = object000->variableValue;
              Object* newValue000 = updateInContext(oldValue000, value000, object000->homeContext, false);

              if (!(((boolean)(oldValue000)) &&
                  (oldValue000->primaryType() == SGT_TIMEPOINT_SUPPORT_STELLA_CS_VALUE))) {
                object000->variableValue = newValue000;
              }
            }
          }
        }
        else {
          if (!(obj->objectEqlP(value))) {
            return (false);
          }
        }
      }
    }
  }
  return (true);
}

Object* timepointOfConstraint(IntegerWrapper* missingArgument, StringWrapper* x1, DateTimeLogicWrapper* x2) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        value = ((((DateTimeObject*)(helpGetCalendarTime(x1)->wrapperValue))->objectEqlP(((DateTimeObject*)(x2->wrapperValue))) ||
            isCurrentTimeSpecP(x1)) ? TRUE_WRAPPER : FALSE_WRAPPER);
        break;
      case 0: 
        { DateTimeLogicWrapper* timepointwrapper = helpGetCalendarTime(x2);

          value = wrapString(((CalendarDate*)(((DateTimeObject*)(timepointwrapper->wrapperValue))))->calendarDateToString(0.0, false, true));
        }
        break;
      case 1: 
        { Object* timepointspecvalue = valueOf(x1);

          if (!((boolean)(timepointspecvalue))) {
            value = NULL;
          }
          else {
            value = helpGetCalendarTime(timepointspecvalue);
          }
        }
        break;
      default:
        break;
    }
    return (value);
  }
}

DateTimeLogicWrapper* timepointOfOComputation(IntegerWrapper* yy, IntegerWrapper* mm, IntegerWrapper* dd, IntegerWrapper* hr, IntegerWrapper* min, NumberWrapper* sec, Object* tz) {
  { Object* yyValue = valueOf(yy);
    Object* mmValue = valueOf(mm);
    Object* ddValue = valueOf(dd);
    Object* hrValue = valueOf(hr);
    Object* minValue = valueOf(min);
    Object* secValue = valueOf(sec);
    Object* tzValue = valueOf(tz);
    int year = helpGetInteger(yyValue);
    int month = helpGetInteger(mmValue);
    int day = helpGetInteger(ddValue);
    int hour = helpGetInteger(hrValue);
    int minute = helpGetInteger(minValue);
    double secondFloat = helpGetFloat(secValue);
    double zone = helpGetTimezone(tzValue);
    int second = 0;
    DateTimeLogicWrapper* tp = NULL;

    if ((year != NULL_INTEGER) &&
        ((month != NULL_INTEGER) &&
         ((day != NULL_INTEGER) &&
          ((hour != NULL_INTEGER) &&
           ((minute != NULL_INTEGER) &&
            ((secondFloat != NULL_FLOAT) &&
             (zone != NULL_FLOAT))))))) {
      second = stella::floor(secondFloat);
      tp = wrapDateTime(makeDateTime(year, month, day, hour, minute, second, stella::floor(1000 * (secondFloat - second)), zone));
    }
    return (tp);
  }
}

void timepointOfOEvaluator(Proposition* self) {
  equateEquivalentFunctionPropositions(self);
  { Object* storedvalue = valueOf((self->arguments->theArray)[7]);
    MethodSlot* computation = lookupFunction(SYM_TIMEPOINT_SUPPORT_TIMEPOINT_SUPPORT_TIMEPOINT_OFo_COMPUTATION);
    Object* computedvalue = computeRelationValue(self, computation, false);

    if (((boolean)(computedvalue)) &&
        (!eqlP(computedvalue, storedvalue))) {
      equateValues(self, computedvalue, storedvalue);
    }
  }
}

Keyword* timepointOfOSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Vector* args = proposition->arguments;
    int year = helpGetInteger(argumentBoundTo((args->theArray)[0]));
    int month = helpGetInteger(argumentBoundTo((args->theArray)[1]));
    int day = helpGetInteger(argumentBoundTo((args->theArray)[2]));
    int hour = helpGetInteger(argumentBoundTo((args->theArray)[3]));
    int minute = helpGetInteger(argumentBoundTo((args->theArray)[4]));
    double secondFloat = helpGetFloat(argumentBoundTo((args->theArray)[5]));
    int second = 0;
    double zone = helpGetTimezone(argumentBoundTo((args->theArray)[6]));
    Object* tp = argumentBoundTo((args->theArray)[7]);
    DateTimeLogicWrapper* theTime = NULL;
    CalendarDate* calendarDate = NULL;

    lastmove = lastmove;
    if ((year != NULL_INTEGER) &&
        ((month != NULL_INTEGER) &&
         ((day != NULL_INTEGER) &&
          ((hour != NULL_INTEGER) &&
           ((minute != NULL_INTEGER) &&
            ((secondFloat != NULL_FLOAT) &&
             (zone != NULL_FLOAT))))))) {
      second = stella::floor(secondFloat);
      theTime = wrapDateTime(makeDateTime(year, month, day, hour, minute, second, stella::floor(1000 * (secondFloat - second)), zone));
      return (selectProofResult(bindArgumentToValueP((args->theArray)[7], theTime, true), false, true));
    }
    else if (((boolean)(tp))) {
      theTime = helpGetCalendarTime(tp);
      calendarDate = ((CalendarDate*)(((DateTimeObject*)(theTime->wrapperValue))));
      if (zone == NULL_FLOAT) {
        zone = 0.0;
        if (!(bindArgumentToValueP((args->theArray)[6], wrapFloat(zone), true))) {
          return (KWD_TIMEPOINT_SUPPORT_FAILURE);
        }
      }
      if (((boolean)(theTime))) {
        { int yy = NULL_INTEGER;
          int mm = NULL_INTEGER;
          int dd = NULL_INTEGER;
          Keyword* dow = NULL;

          yy = calendarDate->getCalendarDate(zone, mm, dd, dow);
          dow = dow;
          { int h = NULL_INTEGER;
            int m = NULL_INTEGER;
            int s = NULL_INTEGER;
            int milli = NULL_INTEGER;

            h = calendarDate->getTime(zone, m, s, milli);
            return (selectProofResult(canBindAllP(consList(6, (args->theArray)[0], (args->theArray)[1], (args->theArray)[2], (args->theArray)[3], (args->theArray)[4], (args->theArray)[5]), consList(6, wrapInteger(yy), wrapInteger(mm), wrapInteger(dd), wrapInteger(h), wrapInteger(m), wrapFloat(((double)(s + (milli * 0.001)))))), false, true));
          }
        }
      }
      else {
        return (KWD_TIMEPOINT_SUPPORT_TERMINAL_FAILURE);
      }
    }
    else {
      return (KWD_TIMEPOINT_SUPPORT_FAILURE);
    }
  }
}

Object* durationOfConstraint(IntegerWrapper* missingArgument, StringWrapper* x1, DateTimeLogicWrapper* x2) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        value = (((DateTimeObject*)(helpGetTimeDuration(x1)->wrapperValue))->objectEqlP(((DateTimeObject*)(x2->wrapperValue))) ? TRUE_WRAPPER : FALSE_WRAPPER);
        break;
      case 0: 
        { DateTimeLogicWrapper* durationwrapper = helpGetTimeDuration(x2);

          value = wrapString(((TimeDuration*)(((DateTimeObject*)(durationwrapper->wrapperValue))))->timeDurationToString());
        }
        break;
      case 1: 
        { Object* durationspecvalue = valueOf(x1);

          if (!((boolean)(durationspecvalue))) {
            value = NULL;
          }
          else {
            value = helpGetTimeDuration(durationspecvalue);
          }
        }
        break;
      default:
        break;
    }
    return (value);
  }
}

Object* timeMinusConstraint(IntegerWrapper* missingArgument, DateTimeLogicWrapper* x1, DateTimeLogicWrapper* x2, DateTimeLogicWrapper* x3) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        value = (timeSubtract(((DateTimeObject*)(x1->wrapperValue)), ((DateTimeObject*)(x2->wrapperValue)))->objectEqlP(((DateTimeObject*)(x3->wrapperValue))) ? TRUE_WRAPPER : FALSE_WRAPPER);
        break;
      case 0: 
        value = wrapDateTime(timeAdd(((DateTimeObject*)(x2->wrapperValue)), ((DateTimeObject*)(x3->wrapperValue))));
        break;
      case 1: 
        value = wrapDateTime(timeSubtract(((DateTimeObject*)(x1->wrapperValue)), ((DateTimeObject*)(x3->wrapperValue))));
        break;
      case 2: 
        value = wrapDateTime(timeSubtract(((DateTimeObject*)(x1->wrapperValue)), ((DateTimeObject*)(x2->wrapperValue))));
        break;
      default:
        break;
    }
    return (value);
  }
}

Object* timePlusConstraint(IntegerWrapper* missingArgument, DateTimeLogicWrapper* x1, DateTimeLogicWrapper* x2, DateTimeLogicWrapper* x3) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        value = (timeAdd(((DateTimeObject*)(x1->wrapperValue)), ((DateTimeObject*)(x2->wrapperValue)))->objectEqlP(((DateTimeObject*)(x3->wrapperValue))) ? TRUE_WRAPPER : FALSE_WRAPPER);
        break;
      case 0: 
        value = wrapDateTime(timeSubtract(((DateTimeObject*)(x3->wrapperValue)), ((DateTimeObject*)(x2->wrapperValue))));
        break;
      case 1: 
        value = wrapDateTime(timeSubtract(((DateTimeObject*)(x3->wrapperValue)), ((DateTimeObject*)(x1->wrapperValue))));
        break;
      case 2: 
        value = wrapDateTime(timeAdd(((DateTimeObject*)(x1->wrapperValue)), ((DateTimeObject*)(x2->wrapperValue))));
        break;
      default:
        break;
    }
    return (value);
  }
}

LogicObject* dowKeywordToInstance(Keyword* dow) {
  if (dow == KWD_TIMEPOINT_SUPPORT_MONDAY) {
    return (((LogicObject*)(SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_MONDAY->surrogateValue)));
  }
  else if (dow == KWD_TIMEPOINT_SUPPORT_TUESDAY) {
    return (((LogicObject*)(SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_TUESDAY->surrogateValue)));
  }
  else if (dow == KWD_TIMEPOINT_SUPPORT_WEDNESDAY) {
    return (((LogicObject*)(SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_WEDNESDAY->surrogateValue)));
  }
  else if (dow == KWD_TIMEPOINT_SUPPORT_THURSDAY) {
    return (((LogicObject*)(SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_THURSDAY->surrogateValue)));
  }
  else if (dow == KWD_TIMEPOINT_SUPPORT_FRIDAY) {
    return (((LogicObject*)(SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_FRIDAY->surrogateValue)));
  }
  else if (dow == KWD_TIMEPOINT_SUPPORT_SATURDAY) {
    return (((LogicObject*)(SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_SATURDAY->surrogateValue)));
  }
  else if (dow == KWD_TIMEPOINT_SUPPORT_SUNDAY) {
    return (((LogicObject*)(SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_SUNDAY->surrogateValue)));
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << dow << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

IntegerWrapper* timepointYearComputation(DateTimeLogicWrapper* timepoint, Object* timezone) {
  timezone = wrapFloat(helpGetTimezone(timezone));
  if (!nullWrapperP(timezone)) {
    { int year = NULL_INTEGER;
      int month = NULL_INTEGER;
      int day = NULL_INTEGER;
      Keyword* dow = NULL;

      year = ((CalendarDate*)(((DateTimeObject*)(timepoint->wrapperValue))))->getCalendarDate(((FloatWrapper*)(timezone))->wrapperValue, month, day, dow);
      {
        month = month;
        day = day;
        dow = dow;
      }
      return (wrapInteger(year));
    }
  }
  else {
    return (NULL);
  }
}

IntegerWrapper* timepointMonthComputation(DateTimeLogicWrapper* timepoint, Object* timezone) {
  timezone = wrapFloat(helpGetTimezone(timezone));
  if (!nullWrapperP(timezone)) {
    { int year = NULL_INTEGER;
      int month = NULL_INTEGER;
      int day = NULL_INTEGER;
      Keyword* dow = NULL;

      year = ((CalendarDate*)(((DateTimeObject*)(timepoint->wrapperValue))))->getCalendarDate(((FloatWrapper*)(timezone))->wrapperValue, month, day, dow);
      {
        year = year;
        day = day;
        dow = dow;
      }
      return (wrapInteger(month));
    }
  }
  else {
    return (NULL);
  }
}

IntegerWrapper* timepointDayComputation(DateTimeLogicWrapper* timepoint, Object* timezone) {
  timezone = wrapFloat(helpGetTimezone(timezone));
  if (!nullWrapperP(timezone)) {
    { int year = NULL_INTEGER;
      int month = NULL_INTEGER;
      int day = NULL_INTEGER;
      Keyword* dow = NULL;

      year = ((CalendarDate*)(((DateTimeObject*)(timepoint->wrapperValue))))->getCalendarDate(((FloatWrapper*)(timezone))->wrapperValue, month, day, dow);
      {
        year = year;
        month = month;
        dow = dow;
      }
      return (wrapInteger(day));
    }
  }
  else {
    return (NULL);
  }
}

LogicObject* timepointDayOfWeekComputation(DateTimeLogicWrapper* timepoint, Object* timezone) {
  timezone = wrapFloat(helpGetTimezone(timezone));
  if (!nullWrapperP(timezone)) {
    { int year = NULL_INTEGER;
      int month = NULL_INTEGER;
      int day = NULL_INTEGER;
      Keyword* dow = NULL;

      year = ((CalendarDate*)(((DateTimeObject*)(timepoint->wrapperValue))))->getCalendarDate(((FloatWrapper*)(timezone))->wrapperValue, month, day, dow);
      {
        year = year;
        month = month;
        day = day;
      }
      return (dowKeywordToInstance(dow));
    }
  }
  else {
    return (NULL);
  }
}

IntegerWrapper* timepointHourComputation(DateTimeLogicWrapper* timepoint, Object* timezone) {
  timezone = wrapFloat(helpGetTimezone(timezone));
  if (!nullWrapperP(timezone)) {
    { int hour = NULL_INTEGER;
      int minute = NULL_INTEGER;
      int second = NULL_INTEGER;
      int millisecond = NULL_INTEGER;

      hour = ((CalendarDate*)(((DateTimeObject*)(timepoint->wrapperValue))))->getTime(((FloatWrapper*)(timezone))->wrapperValue, minute, second, millisecond);
      {
        minute = minute;
        second = second;
        millisecond = millisecond;
      }
      return (wrapInteger(hour));
    }
  }
  else {
    return (NULL);
  }
}

IntegerWrapper* timepointMinuteComputation(DateTimeLogicWrapper* timepoint, Object* timezone) {
  timezone = wrapFloat(helpGetTimezone(timezone));
  if (!nullWrapperP(timezone)) {
    { int hour = NULL_INTEGER;
      int minute = NULL_INTEGER;
      int second = NULL_INTEGER;
      int millisecond = NULL_INTEGER;

      hour = ((CalendarDate*)(((DateTimeObject*)(timepoint->wrapperValue))))->getTime(((FloatWrapper*)(timezone))->wrapperValue, minute, second, millisecond);
      {
        hour = hour;
        second = second;
        millisecond = millisecond;
      }
      return (wrapInteger(minute));
    }
  }
  else {
    return (NULL);
  }
}

NumberWrapper* timepointSecondComputation(DateTimeLogicWrapper* timepoint, Object* timezone) {
  timezone = wrapFloat(helpGetTimezone(timezone));
  if (!nullWrapperP(timezone)) {
    { int hour = NULL_INTEGER;
      int minute = NULL_INTEGER;
      int second = NULL_INTEGER;
      int millisecond = NULL_INTEGER;

      hour = ((CalendarDate*)(((DateTimeObject*)(timepoint->wrapperValue))))->getTime(((FloatWrapper*)(timezone))->wrapperValue, minute, second, millisecond);
      {
        hour = hour;
        minute = minute;
      }
      if (millisecond == 0) {
        return (wrapInteger(second));
      }
      else {
        return (wrapFloat(second + (millisecond * 0.001)));
      }
    }
  }
  else {
    return (NULL);
  }
}

StringWrapper* timepointDateComputation(DateTimeLogicWrapper* timepoint, Object* timezone) {
  timezone = wrapFloat(helpGetTimezone(timezone));
  if (!nullWrapperP(timezone)) {
    return (wrapString(((CalendarDate*)(((DateTimeObject*)(timepoint->wrapperValue))))->calendarDateToDateString(((FloatWrapper*)(timezone))->wrapperValue, false)));
  }
  else {
    return (NULL);
  }
}

StringWrapper* timepointTimeComputation(DateTimeLogicWrapper* timepoint, Object* timezone) {
  timezone = wrapFloat(helpGetTimezone(timezone));
  if (!nullWrapperP(timezone)) {
    return (wrapString(((CalendarDate*)(((DateTimeObject*)(timepoint->wrapperValue))))->calendarDateToTimeString(((FloatWrapper*)(timezone))->wrapperValue, true, true, true)));
  }
  else {
    return (NULL);
  }
}

StringWrapper* formatTimepointComputation(DateTimeLogicWrapper* timepoint, Object* timezone, StringWrapper* control) {
  timezone = wrapFloat(helpGetTimezone(timezone));
  if (!nullWrapperP(timezone)) {
    try {
      return (wrapString(formatDate(((DateTimeObject*)(timepoint->wrapperValue)), timezone, control->wrapperValue)));
    }
    catch (std::exception ) {
    }
  }
  return (NULL);
}

void helpStartupTimepointSupport1() {
  {
    SGT_TIMEPOINT_SUPPORT_TIMEPOINT_SUPPORT_DATE_TIME_LOGIC_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("DATE-TIME-LOGIC-WRAPPER", NULL, 1)));
    SGT_TIMEPOINT_SUPPORT_STELLA_CALENDAR_DATE = ((Surrogate*)(internRigidSymbolWrtModule("CALENDAR-DATE", getStellaModule("/STELLA", true), 1)));
    SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_TIMEPOINT_OF = ((Surrogate*)(internRigidSymbolWrtModule("TIMEPOINT-OF", getStellaModule("/TIMEPOINT-KB", true), 1)));
    SGT_TIMEPOINT_SUPPORT_STELLA_TIME_DURATION = ((Surrogate*)(internRigidSymbolWrtModule("TIME-DURATION", getStellaModule("/STELLA", true), 1)));
    SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_DURATION_OF = ((Surrogate*)(internRigidSymbolWrtModule("DURATION-OF", getStellaModule("/TIMEPOINT-KB", true), 1)));
    SGT_TIMEPOINT_SUPPORT_LOGIC_PATTERN_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("PATTERN-VARIABLE", getStellaModule("/LOGIC", true), 1)));
    SGT_TIMEPOINT_SUPPORT_LOGIC_SKOLEM = ((Surrogate*)(internRigidSymbolWrtModule("SKOLEM", getStellaModule("/LOGIC", true), 1)));
    SGT_TIMEPOINT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("DIM-NUMBER-LOGIC-WRAPPER", getStellaModule("/UNIT-SUPPORT", true), 1)));
    SGT_TIMEPOINT_SUPPORT_STELLA_CS_VALUE = ((Surrogate*)(internRigidSymbolWrtModule("CS-VALUE", getStellaModule("/STELLA", true), 1)));
    SYM_TIMEPOINT_SUPPORT_TIMEPOINT_SUPPORT_TIMEPOINT_OFo_COMPUTATION = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-OF*-COMPUTATION", NULL, 0)));
    KWD_TIMEPOINT_SUPPORT_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("FAILURE", NULL, 2)));
    KWD_TIMEPOINT_SUPPORT_TERMINAL_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("TERMINAL-FAILURE", NULL, 2)));
    KWD_TIMEPOINT_SUPPORT_MONDAY = ((Keyword*)(internRigidSymbolWrtModule("MONDAY", NULL, 2)));
    SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_MONDAY = ((Surrogate*)(internRigidSymbolWrtModule("MONDAY", getStellaModule("/TIMEPOINT-KB", true), 1)));
    KWD_TIMEPOINT_SUPPORT_TUESDAY = ((Keyword*)(internRigidSymbolWrtModule("TUESDAY", NULL, 2)));
    SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_TUESDAY = ((Surrogate*)(internRigidSymbolWrtModule("TUESDAY", getStellaModule("/TIMEPOINT-KB", true), 1)));
    KWD_TIMEPOINT_SUPPORT_WEDNESDAY = ((Keyword*)(internRigidSymbolWrtModule("WEDNESDAY", NULL, 2)));
    SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_WEDNESDAY = ((Surrogate*)(internRigidSymbolWrtModule("WEDNESDAY", getStellaModule("/TIMEPOINT-KB", true), 1)));
    KWD_TIMEPOINT_SUPPORT_THURSDAY = ((Keyword*)(internRigidSymbolWrtModule("THURSDAY", NULL, 2)));
    SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_THURSDAY = ((Surrogate*)(internRigidSymbolWrtModule("THURSDAY", getStellaModule("/TIMEPOINT-KB", true), 1)));
    KWD_TIMEPOINT_SUPPORT_FRIDAY = ((Keyword*)(internRigidSymbolWrtModule("FRIDAY", NULL, 2)));
    SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_FRIDAY = ((Surrogate*)(internRigidSymbolWrtModule("FRIDAY", getStellaModule("/TIMEPOINT-KB", true), 1)));
    KWD_TIMEPOINT_SUPPORT_SATURDAY = ((Keyword*)(internRigidSymbolWrtModule("SATURDAY", NULL, 2)));
    SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_SATURDAY = ((Surrogate*)(internRigidSymbolWrtModule("SATURDAY", getStellaModule("/TIMEPOINT-KB", true), 1)));
    KWD_TIMEPOINT_SUPPORT_SUNDAY = ((Keyword*)(internRigidSymbolWrtModule("SUNDAY", NULL, 2)));
    SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_SUNDAY = ((Surrogate*)(internRigidSymbolWrtModule("SUNDAY", getStellaModule("/TIMEPOINT-KB", true), 1)));
    SYM_TIMEPOINT_SUPPORT_TIMEPOINT_SUPPORT_STARTUP_TIMEPOINT_SUPPORT = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-TIMEPOINT-SUPPORT", NULL, 0)));
    SYM_TIMEPOINT_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void startupTimepointSupport() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/TIMEPOINT-SUPPORT", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupTimepointSupport1();
    }
    if (currentStartupTimePhaseP(4)) {
      oDATE_TIME_HASH_TABLEo = newStellaHashTable();
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("DATE-TIME-LOGIC-WRAPPER", "(DEFCLASS DATE-TIME-LOGIC-WRAPPER (QUANTITY-LOGIC-WRAPPER) :PUBLIC-SLOTS ((WRAPPER-VALUE :TYPE DATE-TIME-OBJECT :REQUIRED? TRUE)) :PRINT-FORM (IF *PRINTREADABLY?* (PRINT-NATIVE-STREAM STREAM (WRAPPER-VALUE SELF)) (PRINT-NATIVE-STREAM STREAM \"|tw|\" (WRAPPER-VALUE SELF))))");

        clasS->classConstructorCode = ((cpp_function_code)(&newDateTimeLogicWrapper));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineMethodObject("(DEFMETHOD (GENERATE-SPECIALIZED-TERM OBJECT) ((SELF DATE-TIME-LOGIC-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&DateTimeLogicWrapper::generateSpecializedTerm))), NULL);
      defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF DATE-TIME-LOGIC-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&DateTimeLogicWrapper::hashCode))), NULL);
      defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((SELF DATE-TIME-LOGIC-WRAPPER) (X OBJECT)))", wrapMethodCode(((cpp_method_code)(&DateTimeLogicWrapper::objectEqlP))), NULL);
      defineFunctionObject("WRAP-DATE-TIME", "(DEFUN (WRAP-DATE-TIME DATE-TIME-LOGIC-WRAPPER) ((VALUE DATE-TIME-OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Return an interned LOGIC-WRAPPER for `value'.  This assures us\nthat all logic-wrapped DATE-TIME-OBJECTs are the same object.\")", ((cpp_function_code)(&wrapDateTime)), NULL);
      defineFunctionObject("HELP-GET-CALENDAR-TIME", "(DEFUN (HELP-GET-CALENDAR-TIME DATE-TIME-LOGIC-WRAPPER) ((ITEM OBJECT)))", ((cpp_function_code)(&helpGetCalendarTime)), NULL);
      defineFunctionObject("HELP-GET-TIME-DURATION", "(DEFUN (HELP-GET-TIME-DURATION DATE-TIME-LOGIC-WRAPPER) ((ITEM OBJECT)))", ((cpp_function_code)(&helpGetTimeDuration)), NULL);
      defineFunctionObject("HELP-GET-TIME-OBJECT", "(DEFUN (HELP-GET-TIME-OBJECT DATE-TIME-LOGIC-WRAPPER) ((ITEM OBJECT)))", ((cpp_function_code)(&helpGetTimeObject)), NULL);
      defineFunctionObject("HELP-GET-INTEGER", "(DEFUN (HELP-GET-INTEGER INTEGER) ((OBJ OBJECT)))", ((cpp_function_code)(&helpGetInteger)), NULL);
      defineFunctionObject("HELP-GET-FLOAT", "(DEFUN (HELP-GET-FLOAT FLOAT) ((OBJ OBJECT)))", ((cpp_function_code)(&helpGetFloat)), NULL);
      defineFunctionObject("HELP-GET-TIMEZONE", "(DEFUN (HELP-GET-TIMEZONE FLOAT) ((OBJ OBJECT)))", ((cpp_function_code)(&helpGetTimezone)), NULL);
      defineFunctionObject("IS-CURRENT-TIME-SPEC?", "(DEFUN (IS-CURRENT-TIME-SPEC? BOOLEAN) ((SPEC OBJECT)))", ((cpp_function_code)(&isCurrentTimeSpecP)), NULL);
      defineFunctionObject("CAN-BIND-ALL?", "(DEFUN (CAN-BIND-ALL? BOOLEAN) ((PL-OBJECTS CONS) (VALUES CONS)))", ((cpp_function_code)(&canBindAllP)), NULL);
      defineFunctionObject("TIMEPOINT-OF-CONSTRAINT", "(DEFUN (TIMEPOINT-OF-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X1 STRING-WRAPPER) (X2 DATE-TIME-LOGIC-WRAPPER)))", ((cpp_function_code)(&timepointOfConstraint)), NULL);
      defineFunctionObject("TIMEPOINT-OF*-COMPUTATION", "(DEFUN (TIMEPOINT-OF*-COMPUTATION DATE-TIME-LOGIC-WRAPPER) ((YY INTEGER-WRAPPER) (MM INTEGER-WRAPPER) (DD INTEGER-WRAPPER) (HR INTEGER-WRAPPER) (MIN INTEGER-WRAPPER) (SEC NUMBER-WRAPPER) (TZ OBJECT)))", ((cpp_function_code)(&timepointOfOComputation)), NULL);
      defineFunctionObject("TIMEPOINT-OF*-EVALUATOR", "(DEFUN TIMEPOINT-OF*-EVALUATOR ((SELF PROPOSITION)))", ((cpp_function_code)(&timepointOfOEvaluator)), NULL);
      defineFunctionObject("TIMEPOINT-OF*-SPECIALIST", "(DEFUN (TIMEPOINT-OF*-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&timepointOfOSpecialist)), NULL);
      defineFunctionObject("DURATION-OF-CONSTRAINT", "(DEFUN (DURATION-OF-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X1 STRING-WRAPPER) (X2 DATE-TIME-LOGIC-WRAPPER)))", ((cpp_function_code)(&durationOfConstraint)), NULL);
      defineFunctionObject("TIME-MINUS-CONSTRAINT", "(DEFUN (TIME-MINUS-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X1 DATE-TIME-LOGIC-WRAPPER) (X2 DATE-TIME-LOGIC-WRAPPER) (X3 DATE-TIME-LOGIC-WRAPPER)))", ((cpp_function_code)(&timeMinusConstraint)), NULL);
      defineFunctionObject("TIME-PLUS-CONSTRAINT", "(DEFUN (TIME-PLUS-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X1 DATE-TIME-LOGIC-WRAPPER) (X2 DATE-TIME-LOGIC-WRAPPER) (X3 DATE-TIME-LOGIC-WRAPPER)))", ((cpp_function_code)(&timePlusConstraint)), NULL);
      defineFunctionObject("DOW-KEYWORD-TO-INSTANCE", "(DEFUN (DOW-KEYWORD-TO-INSTANCE LOGIC-OBJECT) ((DOW KEYWORD)))", ((cpp_function_code)(&dowKeywordToInstance)), NULL);
      defineFunctionObject("TIMEPOINT-YEAR-COMPUTATION", "(DEFUN (TIMEPOINT-YEAR-COMPUTATION INTEGER-WRAPPER) ((TIMEPOINT DATE-TIME-LOGIC-WRAPPER) (TIMEZONE OBJECT)))", ((cpp_function_code)(&timepointYearComputation)), NULL);
      defineFunctionObject("TIMEPOINT-MONTH-COMPUTATION", "(DEFUN (TIMEPOINT-MONTH-COMPUTATION INTEGER-WRAPPER) ((TIMEPOINT DATE-TIME-LOGIC-WRAPPER) (TIMEZONE OBJECT)))", ((cpp_function_code)(&timepointMonthComputation)), NULL);
      defineFunctionObject("TIMEPOINT-DAY-COMPUTATION", "(DEFUN (TIMEPOINT-DAY-COMPUTATION INTEGER-WRAPPER) ((TIMEPOINT DATE-TIME-LOGIC-WRAPPER) (TIMEZONE OBJECT)))", ((cpp_function_code)(&timepointDayComputation)), NULL);
      defineFunctionObject("TIMEPOINT-DAY-OF-WEEK-COMPUTATION", "(DEFUN (TIMEPOINT-DAY-OF-WEEK-COMPUTATION LOGIC-OBJECT) ((TIMEPOINT DATE-TIME-LOGIC-WRAPPER) (TIMEZONE OBJECT)))", ((cpp_function_code)(&timepointDayOfWeekComputation)), NULL);
      defineFunctionObject("TIMEPOINT-HOUR-COMPUTATION", "(DEFUN (TIMEPOINT-HOUR-COMPUTATION INTEGER-WRAPPER) ((TIMEPOINT DATE-TIME-LOGIC-WRAPPER) (TIMEZONE OBJECT)))", ((cpp_function_code)(&timepointHourComputation)), NULL);
      defineFunctionObject("TIMEPOINT-MINUTE-COMPUTATION", "(DEFUN (TIMEPOINT-MINUTE-COMPUTATION INTEGER-WRAPPER) ((TIMEPOINT DATE-TIME-LOGIC-WRAPPER) (TIMEZONE OBJECT)))", ((cpp_function_code)(&timepointMinuteComputation)), NULL);
      defineFunctionObject("TIMEPOINT-SECOND-COMPUTATION", "(DEFUN (TIMEPOINT-SECOND-COMPUTATION NUMBER-WRAPPER) ((TIMEPOINT DATE-TIME-LOGIC-WRAPPER) (TIMEZONE OBJECT)))", ((cpp_function_code)(&timepointSecondComputation)), NULL);
      defineFunctionObject("TIMEPOINT-DATE-COMPUTATION", "(DEFUN (TIMEPOINT-DATE-COMPUTATION STRING-WRAPPER) ((TIMEPOINT DATE-TIME-LOGIC-WRAPPER) (TIMEZONE OBJECT)))", ((cpp_function_code)(&timepointDateComputation)), NULL);
      defineFunctionObject("TIMEPOINT-TIME-COMPUTATION", "(DEFUN (TIMEPOINT-TIME-COMPUTATION STRING-WRAPPER) ((TIMEPOINT DATE-TIME-LOGIC-WRAPPER) (TIMEZONE OBJECT)))", ((cpp_function_code)(&timepointTimeComputation)), NULL);
      defineFunctionObject("FORMAT-TIMEPOINT-COMPUTATION", "(DEFUN (FORMAT-TIMEPOINT-COMPUTATION STRING-WRAPPER) ((TIMEPOINT DATE-TIME-LOGIC-WRAPPER) (TIMEZONE OBJECT) (CONTROL STRING-WRAPPER)))", ((cpp_function_code)(&formatTimepointComputation)), NULL);
      defineFunctionObject("STARTUP-TIMEPOINT-SUPPORT", "(DEFUN STARTUP-TIMEPOINT-SUPPORT () :PUBLIC? TRUE)", ((cpp_function_code)(&startupTimepointSupport)), NULL);
      { MethodSlot* function = lookupFunction(SYM_TIMEPOINT_SUPPORT_TIMEPOINT_SUPPORT_STARTUP_TIMEPOINT_SUPPORT);

        setDynamicSlotValue(function->dynamicSlots, SYM_TIMEPOINT_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupTimepointSupport"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("TIMEPOINT-SUPPORT")))));
      defineGlobalVariableObject("(DEFGLOBAL *DATE-TIME-HASH-TABLE* (STELLA-HASH-TABLE OF DATE-TIME-OBJECT DATE-TIME-LOGIC-WRAPPER) (NEW STELLA-HASH-TABLE) :DOCUMENTATION \"Table for interning date-time logic wrappers\")", &oDATE_TIME_HASH_TABLEo);
    }
  }
}

Surrogate* SGT_TIMEPOINT_SUPPORT_TIMEPOINT_SUPPORT_DATE_TIME_LOGIC_WRAPPER = NULL;

Surrogate* SGT_TIMEPOINT_SUPPORT_STELLA_CALENDAR_DATE = NULL;

Surrogate* SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_TIMEPOINT_OF = NULL;

Surrogate* SGT_TIMEPOINT_SUPPORT_STELLA_TIME_DURATION = NULL;

Surrogate* SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_DURATION_OF = NULL;

Surrogate* SGT_TIMEPOINT_SUPPORT_LOGIC_PATTERN_VARIABLE = NULL;

Surrogate* SGT_TIMEPOINT_SUPPORT_LOGIC_SKOLEM = NULL;

Surrogate* SGT_TIMEPOINT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER = NULL;

Surrogate* SGT_TIMEPOINT_SUPPORT_STELLA_CS_VALUE = NULL;

Symbol* SYM_TIMEPOINT_SUPPORT_TIMEPOINT_SUPPORT_TIMEPOINT_OFo_COMPUTATION = NULL;

Keyword* KWD_TIMEPOINT_SUPPORT_FAILURE = NULL;

Keyword* KWD_TIMEPOINT_SUPPORT_TERMINAL_FAILURE = NULL;

Keyword* KWD_TIMEPOINT_SUPPORT_MONDAY = NULL;

Surrogate* SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_MONDAY = NULL;

Keyword* KWD_TIMEPOINT_SUPPORT_TUESDAY = NULL;

Surrogate* SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_TUESDAY = NULL;

Keyword* KWD_TIMEPOINT_SUPPORT_WEDNESDAY = NULL;

Surrogate* SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_WEDNESDAY = NULL;

Keyword* KWD_TIMEPOINT_SUPPORT_THURSDAY = NULL;

Surrogate* SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_THURSDAY = NULL;

Keyword* KWD_TIMEPOINT_SUPPORT_FRIDAY = NULL;

Surrogate* SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_FRIDAY = NULL;

Keyword* KWD_TIMEPOINT_SUPPORT_SATURDAY = NULL;

Surrogate* SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_SATURDAY = NULL;

Keyword* KWD_TIMEPOINT_SUPPORT_SUNDAY = NULL;

Surrogate* SGT_TIMEPOINT_SUPPORT_TIMEPOINT_KB_SUNDAY = NULL;

Symbol* SYM_TIMEPOINT_SUPPORT_TIMEPOINT_SUPPORT_STARTUP_TIMEPOINT_SUPPORT = NULL;

Symbol* SYM_TIMEPOINT_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace timepoint
