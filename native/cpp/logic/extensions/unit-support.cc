//  -*- Mode: C++ -*-

// unit-support.cc

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

namespace units {
  using namespace stella_utilities;
  using namespace stella;
  using namespace logic;

// Table for interning dim number logic wrappers
StellaHashTable* oDIM_NUMBER_HASH_TABLEo = NULL;

DimNumberLogicWrapper* newDimNumberLogicWrapper(DimNumber* wrapperValue) {
  { DimNumberLogicWrapper* self = NULL;

    self = new DimNumberLogicWrapper();
    self->wrapperValue = wrapperValue;
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    self->functionTerm = NULL;
    return (self);
  }
}

Surrogate* DimNumberLogicWrapper::primaryType() {
  { DimNumberLogicWrapper* self = this;

    return (SGT_UNIT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER);
  }
}

Object* accessDimNumberLogicWrapperSlotValue(DimNumberLogicWrapper* self, Symbol* slotname, Object* value, boolean setvalueP) {
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

void DimNumberLogicWrapper::printObject(std::ostream* stream) {
  { DimNumberLogicWrapper* self = this;

    if (oPRINTREADABLYpo) {
      *(stream) << ((DimNumber*)(self->wrapperValue));
    }
    else {
      *(stream) << "|uw|" << ((DimNumber*)(self->wrapperValue));
    }
  }
}

Object* DimNumberLogicWrapper::generateSpecializedTerm() {
  { DimNumberLogicWrapper* self = this;

    { Cons* term = self->functionTerm;
      DimNumber* dim = ((DimNumber*)(self->wrapperValue));

      if (((boolean)(term))) {
        return (term);
      }
      else if (((boolean)(dim))) {
        term = cons(generateTerm(SGT_UNIT_SUPPORT_UNIT_KB_UNITS), cons(wrapFloat(dim->getMagnitude(dim->getUnit())), cons(wrapString(dim->getUnit()), NIL)));
        self->functionTerm = term;
        return (term);
      }
      else {
        throw *newTermGenerationException(self, "Dim Number Wrapper doesn't have a value.");
      }
    }
  }
}

int DimNumberLogicWrapper::hashCode() {
  { DimNumberLogicWrapper* self = this;

    if (((boolean)(((DimNumber*)(self->wrapperValue))))) {
      return (((DimNumber*)(self->wrapperValue))->hashCode());
    }
    else {
      return (0);
    }
  }
}

boolean DimNumberLogicWrapper::objectEqlP(Object* x) {
  { DimNumberLogicWrapper* self = this;

    return (((boolean)(x)) &&
        (isaP(x, SGT_UNIT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER) &&
         eqlP(((DimNumber*)(self->wrapperValue)), ((DimNumber*)(((DimNumberLogicWrapper*)(x))->wrapperValue)))));
  }
}

DimNumberLogicWrapper* wrapDimNumber(DimNumber* value) {
  // Return an interned LOGIC-WRAPPER for `value'.  This assures us
  // that all logic-wrapped DIM-NUMBERs are the same object.
  { DimNumberLogicWrapper* wrapper = ((DimNumberLogicWrapper*)(oDIM_NUMBER_HASH_TABLEo->lookup(value)));

    if (!((boolean)(wrapper))) {
      value->preferredUnits = NULL;
      wrapper = newDimNumberLogicWrapper(value);
      oDIM_NUMBER_HASH_TABLEo->insertAt(value, wrapper);
    }
    return (wrapper);
  }
}

const char* DimNumberLogicWrapper::getUnit() {
  { DimNumberLogicWrapper* self = this;

    return (((DimNumber*)(self->wrapperValue))->getUnit());
  }
}

const char* DimNumberLogicWrapper::getBaseUnit() {
  { DimNumberLogicWrapper* self = this;

    return (((DimNumber*)(self->wrapperValue))->getBaseUnit());
  }
}

double DimNumberLogicWrapper::getMagnitude(const char* units) {
  { DimNumberLogicWrapper* self = this;

    return (((DimNumber*)(self->wrapperValue))->getMagnitude(units));
  }
}

DimNumberLogicWrapper* helpGetDimNumber(Object* item) {
  { Surrogate* testValue000 = safePrimaryType(item);

    if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER)) {
      { Object* item000 = item;
        DimNumberLogicWrapper* item = ((DimNumberLogicWrapper*)(item000));

        return (item);
      }
    }
    else if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_TIMEPOINT_SUPPORT_DATE_TIME_LOGIC_WRAPPER)) {
      { Object* item001 = item;
        timepoint::DateTimeLogicWrapper* item = ((timepoint::DateTimeLogicWrapper*)(item001));

        { DateTimeObject* value = ((DateTimeObject*)(item->wrapperValue));

          { Surrogate* testValue001 = safePrimaryType(value);

            if (subtypeOfP(testValue001, SGT_UNIT_SUPPORT_STELLA_CALENDAR_DATE)) {
              { DateTimeObject* value000 = value;
                CalendarDate* value = ((CalendarDate*)(value000));

                return (NULL);
              }
            }
            else if (subtypeOfP(testValue001, SGT_UNIT_SUPPORT_STELLA_TIME_DURATION)) {
              { DateTimeObject* value001 = value;
                TimeDuration* value = ((TimeDuration*)(value001));

                return (newDimNumberLogicWrapper(timeDurationToDim(value)));
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
    }
    else if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
      { Object* item002 = item;
        PatternVariable* item = ((PatternVariable*)(item002));

        { Object* value = safeBoundTo(item);

          if (((boolean)(value))) {
            return (helpGetDimNumber(value));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
      { Object* item003 = item;
        Skolem* item = ((Skolem*)(item003));

        { Object* value = ((Object*)(accessInContext(item->variableValue, item->homeContext, false)));

          if (!((boolean)(value))) {
            return (NULL);
          }
          { Surrogate* testValue002 = safePrimaryType(value);

            if (subtypeOfP(testValue002, SGT_UNIT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER)) {
              { Object* value002 = value;
                DimNumberLogicWrapper* value = ((DimNumberLogicWrapper*)(value002));

                return (value);
              }
            }
            else if (subtypeOfP(testValue002, SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
              { Object* value003 = value;
                Skolem* value = ((Skolem*)(value003));

                if (!((boolean)(((Object*)(accessInContext(value->variableValue, value->homeContext, false)))))) {
                  return (NULL);
                }
                if (isaP(((Object*)(accessInContext(value->variableValue, value->homeContext, false))), SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
                  return (NULL);
                }
                else {
                  return (helpGetDimNumber(((Object*)(accessInContext(value->variableValue, value->homeContext, false)))));
                }
              }
            }
            else {
              if (isaP(((Object*)(accessInContext(item->variableValue, item->homeContext, false))), SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
                return (NULL);
              }
              else {
                return (helpGetDimNumber(((Object*)(accessInContext(item->variableValue, item->homeContext, false)))));
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

DimNumberLogicWrapper* helpGetUnitValue(Object* magnitude, Object* units) {
  { Surrogate* testValue000 = safePrimaryType(magnitude);

    if (subtypeOfFloatP(testValue000)) {
      { Object* magnitude000 = magnitude;
        FloatWrapper* magnitude = ((FloatWrapper*)(magnitude000));

        { Surrogate* testValue001 = safePrimaryType(units);

          if (subtypeOfStringP(testValue001)) {
            { Object* units000 = units;
              StringWrapper* units = ((StringWrapper*)(units000));

              { double value = magnitude->wrapperValue;
                DimNumberLogicWrapper* returnValue = NULL;

                try {
                  if (value != NULL_FLOAT) {
                    returnValue = wrapDimNumber(makeDimNumber(value, units->wrapperValue));
                  }
                }
                catch (StellaException ) {
                }
                return (returnValue);
              }
            }
          }
          else if (subtypeOfP(testValue001, SGT_UNIT_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
            { Object* units001 = units;
              PatternVariable* units = ((PatternVariable*)(units001));

              { Object* unitValue = safeBoundTo(units);

                if (((boolean)(unitValue))) {
                  return (helpGetUnitValue(magnitude, unitValue));
                }
                else {
                  return (NULL);
                }
              }
            }
          }
          else if (subtypeOfP(testValue001, SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
            { Object* units002 = units;
              Skolem* units = ((Skolem*)(units002));

              { Object* unitValue = ((Object*)(accessInContext(units->variableValue, units->homeContext, false)));

                { Surrogate* testValue002 = safePrimaryType(unitValue);

                  if (subtypeOfStringP(testValue002)) {
                    { Object* unitValue000 = unitValue;
                      StringWrapper* unitValue = ((StringWrapper*)(unitValue000));

                      return (helpGetUnitValue(magnitude, unitValue));
                    }
                  }
                  else if (subtypeOfP(testValue002, SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
                    { Object* unitValue001 = unitValue;
                      Skolem* unitValue = ((Skolem*)(unitValue001));

                      if (isaP(((Object*)(accessInContext(unitValue->variableValue, unitValue->homeContext, false))), SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
                        return (NULL);
                      }
                      else {
                        return (helpGetUnitValue(magnitude, ((Object*)(accessInContext(unitValue->variableValue, unitValue->homeContext, false)))));
                      }
                    }
                  }
                  else {
                    if (isaP(((Object*)(accessInContext(units->variableValue, units->homeContext, false))), SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
                      return (NULL);
                    }
                    else {
                      return (helpGetUnitValue(magnitude, ((Object*)(accessInContext(units->variableValue, units->homeContext, false)))));
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
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { Object* magnitude001 = magnitude;
        IntegerWrapper* magnitude = ((IntegerWrapper*)(magnitude001));

        { Surrogate* testValue003 = safePrimaryType(units);

          if (subtypeOfStringP(testValue003)) {
            { Object* units003 = units;
              StringWrapper* units = ((StringWrapper*)(units003));

              { int value = magnitude->wrapperValue;
                DimNumberLogicWrapper* returnValue = NULL;

                try {
                  if (value != NULL_INTEGER) {
                    returnValue = wrapDimNumber(makeDimNumber(((double)(value)), units->wrapperValue));
                  }
                }
                catch (StellaException ) {
                }
                return (returnValue);
              }
            }
          }
          else if (subtypeOfP(testValue003, SGT_UNIT_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
            { Object* units004 = units;
              PatternVariable* units = ((PatternVariable*)(units004));

              { Object* unitValue = safeBoundTo(units);

                if (((boolean)(unitValue))) {
                  return (helpGetUnitValue(magnitude, unitValue));
                }
                else {
                  return (NULL);
                }
              }
            }
          }
          else if (subtypeOfP(testValue003, SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
            { Object* units005 = units;
              Skolem* units = ((Skolem*)(units005));

              { Object* unitValue = ((Object*)(accessInContext(units->variableValue, units->homeContext, false)));

                { Surrogate* testValue004 = safePrimaryType(unitValue);

                  if (subtypeOfStringP(testValue004)) {
                    { Object* unitValue002 = unitValue;
                      StringWrapper* unitValue = ((StringWrapper*)(unitValue002));

                      return (helpGetUnitValue(magnitude, unitValue));
                    }
                  }
                  else if (subtypeOfP(testValue004, SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
                    { Object* unitValue003 = unitValue;
                      Skolem* unitValue = ((Skolem*)(unitValue003));

                      if (isaP(((Object*)(accessInContext(unitValue->variableValue, unitValue->homeContext, false))), SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
                        return (NULL);
                      }
                      else {
                        return (helpGetUnitValue(magnitude, ((Object*)(accessInContext(unitValue->variableValue, unitValue->homeContext, false)))));
                      }
                    }
                  }
                  else {
                    if (isaP(((Object*)(accessInContext(units->variableValue, units->homeContext, false))), SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
                      return (NULL);
                    }
                    else {
                      return (helpGetUnitValue(magnitude, ((Object*)(accessInContext(units->variableValue, units->homeContext, false)))));
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
    }
    else if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
      { Object* magnitude002 = magnitude;
        PatternVariable* magnitude = ((PatternVariable*)(magnitude002));

        { Object* value = safeBoundTo(magnitude);

          if (((boolean)(value))) {
            return (helpGetUnitValue(value, units));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
      { Object* magnitude003 = magnitude;
        Skolem* magnitude = ((Skolem*)(magnitude003));

        { Object* value = ((Object*)(accessInContext(magnitude->variableValue, magnitude->homeContext, false)));

          if (subtypeOfP(safePrimaryType(value), SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
            { Object* value000 = value;
              Skolem* value = ((Skolem*)(value000));

              if (isaP(((Object*)(accessInContext(value->variableValue, value->homeContext, false))), SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
                return (NULL);
              }
              else {
                return (helpGetUnitValue(((Object*)(accessInContext(value->variableValue, value->homeContext, false))), units));
              }
            }
          }
          else {
            if (isaP(((Object*)(accessInContext(magnitude->variableValue, magnitude->homeContext, false))), SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
              return (NULL);
            }
            else {
              return (helpGetUnitValue(((Object*)(accessInContext(magnitude->variableValue, magnitude->homeContext, false))), units));
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

void unitsEvaluator(Proposition* self) {
  { Object* magnitude = valueOf((self->arguments->theArray)[0]);
    Object* units = valueOf((self->arguments->theArray)[1]);
    Object* dimNumber = valueOf((self->arguments->theArray)[2]);
    DimNumberLogicWrapper* value1 = helpGetUnitValue(magnitude, units);

    if (((boolean)(value1))) {
      { Surrogate* testValue000 = safePrimaryType(dimNumber);

        if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
          { Object* dimNumber000 = dimNumber;
            Skolem* dimNumber = ((Skolem*)(dimNumber000));

            bindSkolemToValue(dimNumber, value1, false);
          }
        }
        else if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER)) {
          { Object* dimNumber001 = dimNumber;
            DimNumberLogicWrapper* dimNumber = ((DimNumberLogicWrapper*)(dimNumber001));

            if (!(eqlP(((DimNumber*)(value1->wrapperValue)), ((DimNumber*)(dimNumber->wrapperValue))))) {
              signalUnificationClash(self, value1, dimNumber);
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_TIMEPOINT_SUPPORT_DATE_TIME_LOGIC_WRAPPER)) {
          { Object* dimNumber002 = dimNumber;
            timepoint::DateTimeLogicWrapper* dimNumber = ((timepoint::DateTimeLogicWrapper*)(dimNumber002));

            { DimNumberLogicWrapper* theDim = helpGetDimNumber(dimNumber);

              if (!(((boolean)(theDim)) &&
                  eqlP(((DimNumber*)(value1->wrapperValue)), ((DimNumber*)(theDim->wrapperValue))))) {
                signalUnificationClash(self, value1, dimNumber);
              }
            }
          }
        }
        else {
          signalUnificationClash(self, value1, dimNumber);
        }
      }
    }
  }
}

Keyword* unitsSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* magnitude = valueOf((proposition->arguments->theArray)[0]);
    Object* units = valueOf((proposition->arguments->theArray)[1]);
    Object* dim = valueOf((proposition->arguments->theArray)[2]);
    DimNumberLogicWrapper* theValue = helpGetUnitValue(magnitude, units);
    const char* unitString = NULL;

    lastmove = lastmove;
    if (((boolean)(theValue))) {
      { Surrogate* testValue000 = safePrimaryType(dim);

        if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
          { Object* dim000 = dim;
            PatternVariable* dim = ((PatternVariable*)(dim000));

            return (selectProofResult(bindVariableToValueP(dim, theValue, true), false, true));
          }
        }
        else if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
          { Object* dim001 = dim;
            Skolem* dim = ((Skolem*)(dim001));

            { Skolem* object000 = dim;
              Object* value000 = theValue;
              Object* oldValue000 = object000->variableValue;
              Object* newValue000 = updateInContext(oldValue000, value000, object000->homeContext, false);

              if (!(((boolean)(oldValue000)) &&
                  (oldValue000->primaryType() == SGT_UNIT_SUPPORT_STELLA_CS_VALUE))) {
                object000->variableValue = newValue000;
              }
            }
            return (KWD_UNIT_SUPPORT_FINAL_SUCCESS);
          }
        }
        else if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER)) {
          { Object* dim002 = dim;
            DimNumberLogicWrapper* dim = ((DimNumberLogicWrapper*)(dim002));

            return (selectProofResult(((DimNumber*)(theValue->wrapperValue))->objectEqlP(((DimNumber*)(dim->wrapperValue))), false, true));
          }
        }
        else if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_TIMEPOINT_SUPPORT_DATE_TIME_LOGIC_WRAPPER)) {
          { Object* dim003 = dim;
            timepoint::DateTimeLogicWrapper* dim = ((timepoint::DateTimeLogicWrapper*)(dim003));

            { DimNumberLogicWrapper* theDim = helpGetDimNumber(dim);

              if (!((boolean)(theDim))) {
                return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
              }
              else {
                return (selectProofResult(((DimNumber*)(theValue->wrapperValue))->objectEqlP(((DimNumber*)(theDim->wrapperValue))), false, true));
              }
            }
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
    else if (((boolean)(dim))) {
      theValue = helpGetDimNumber(dim);
      if (!(((boolean)(theValue)))) {
        return (KWD_UNIT_SUPPORT_FAILURE);
      }
      unitString = ((DimNumber*)(theValue->wrapperValue))->getUnit();
      { Surrogate* testValue001 = safePrimaryType(magnitude);

        if (subtypeOfP(testValue001, SGT_UNIT_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
          { Object* magnitude000 = magnitude;
            PatternVariable* magnitude = ((PatternVariable*)(magnitude000));

            { Surrogate* testValue002 = safePrimaryType(units);

              if (subtypeOfP(testValue002, SGT_UNIT_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
                { Object* units000 = units;
                  PatternVariable* units = ((PatternVariable*)(units000));

                  return (selectProofResult(bindVariableToValueP(units, wrapString(unitString), true) &&
                      bindVariableToValueP(magnitude, wrapFloat(((DimNumber*)(theValue->wrapperValue))->getMagnitude(unitString)), true), false, true));
                }
              }
              else if (subtypeOfStringP(testValue002)) {
                { Object* units001 = units;
                  StringWrapper* units = ((StringWrapper*)(units001));

                  { Keyword* returnValue = KWD_UNIT_SUPPORT_FAILURE;

                    try {
                      returnValue = selectProofResult(bindVariableToValueP(magnitude, wrapFloat(((DimNumber*)(theValue->wrapperValue))->getMagnitude(units->wrapperValue)), true), false, true);
                    }
                    catch (IncompatibleUnitsException ) {
                      returnValue = KWD_UNIT_SUPPORT_TERMINAL_FAILURE;
                    }
                    catch (StellaException ) {
                    }
                    return (returnValue);
                  }
                }
              }
              else if (subtypeOfP(testValue002, SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
                { Object* units002 = units;
                  Skolem* units = ((Skolem*)(units002));

                  { Skolem* object001 = units;
                    Object* value001 = wrapString(unitString);
                    Object* oldValue001 = object001->variableValue;
                    Object* newValue001 = updateInContext(oldValue001, value001, object001->homeContext, false);

                    if (!(((boolean)(oldValue001)) &&
                        (oldValue001->primaryType() == SGT_UNIT_SUPPORT_STELLA_CS_VALUE))) {
                      object001->variableValue = newValue001;
                    }
                  }
                  return (selectProofResult(bindVariableToValueP(magnitude, wrapFloat(((DimNumber*)(theValue->wrapperValue))->getMagnitude(unitString)), true), false, true));
                }
              }
              else {
                return (KWD_UNIT_SUPPORT_FAILURE);
              }
            }
          }
        }
        else if (subtypeOfP(testValue001, SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
          { Object* magnitude001 = magnitude;
            Skolem* magnitude = ((Skolem*)(magnitude001));

            { Surrogate* testValue003 = safePrimaryType(units);

              if (subtypeOfP(testValue003, SGT_UNIT_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
                { Object* units003 = units;
                  PatternVariable* units = ((PatternVariable*)(units003));

                  { Skolem* object002 = magnitude;
                    Object* value002 = wrapFloat(((DimNumber*)(theValue->wrapperValue))->getMagnitude(unitString));
                    Object* oldValue002 = object002->variableValue;
                    Object* newValue002 = updateInContext(oldValue002, value002, object002->homeContext, false);

                    if (!(((boolean)(oldValue002)) &&
                        (oldValue002->primaryType() == SGT_UNIT_SUPPORT_STELLA_CS_VALUE))) {
                      object002->variableValue = newValue002;
                    }
                  }
                  return (selectProofResult(bindVariableToValueP(units, wrapString(unitString), true), false, true));
                }
              }
              else if (subtypeOfStringP(testValue003)) {
                { Object* units004 = units;
                  StringWrapper* units = ((StringWrapper*)(units004));

                  { Keyword* returnValue = KWD_UNIT_SUPPORT_FINAL_SUCCESS;

                    try {
                      { Skolem* object003 = magnitude;
                        Object* value003 = wrapFloat(((DimNumber*)(theValue->wrapperValue))->getMagnitude(units->wrapperValue));
                        Object* oldValue003 = object003->variableValue;
                        Object* newValue003 = updateInContext(oldValue003, value003, object003->homeContext, false);

                        if (!(((boolean)(oldValue003)) &&
                            (oldValue003->primaryType() == SGT_UNIT_SUPPORT_STELLA_CS_VALUE))) {
                          object003->variableValue = newValue003;
                        }
                      }
                    }
                    catch (IncompatibleUnitsException ) {
                      returnValue = KWD_UNIT_SUPPORT_TERMINAL_FAILURE;
                    }
                    catch (StellaException ) {
                      returnValue = KWD_UNIT_SUPPORT_FAILURE;
                    }
                    return (returnValue);
                  }
                }
              }
              else if (subtypeOfP(testValue003, SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
                { Object* units005 = units;
                  Skolem* units = ((Skolem*)(units005));

                  { Skolem* object004 = units;
                    Object* value004 = wrapString(unitString);
                    Object* oldValue004 = object004->variableValue;
                    Object* newValue004 = updateInContext(oldValue004, value004, object004->homeContext, false);

                    if (!(((boolean)(oldValue004)) &&
                        (oldValue004->primaryType() == SGT_UNIT_SUPPORT_STELLA_CS_VALUE))) {
                      object004->variableValue = newValue004;
                    }
                  }
                  { Skolem* object005 = magnitude;
                    Object* value005 = wrapFloat(((DimNumber*)(theValue->wrapperValue))->getMagnitude(unitString));
                    Object* oldValue005 = object005->variableValue;
                    Object* newValue005 = updateInContext(oldValue005, value005, object005->homeContext, false);

                    if (!(((boolean)(oldValue005)) &&
                        (oldValue005->primaryType() == SGT_UNIT_SUPPORT_STELLA_CS_VALUE))) {
                      object005->variableValue = newValue005;
                    }
                  }
                  return (KWD_UNIT_SUPPORT_FINAL_SUCCESS);
                }
              }
              else {
                return (KWD_UNIT_SUPPORT_FAILURE);
              }
            }
          }
        }
        else if (subtypeOfFloatP(testValue001)) {
          { Object* magnitude002 = magnitude;
            FloatWrapper* magnitude = ((FloatWrapper*)(magnitude002));

            if ((magnitude->wrapperValue != NULL_FLOAT) &&
                (magnitude->wrapperValue == ((DimNumber*)(theValue->wrapperValue))->getMagnitude(unitString))) {
              { Surrogate* testValue004 = safePrimaryType(units);

                if (subtypeOfP(testValue004, SGT_UNIT_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
                  { Object* units006 = units;
                    PatternVariable* units = ((PatternVariable*)(units006));

                    return (selectProofResult(bindVariableToValueP(units, wrapString(unitString), true), false, true));
                  }
                }
                else if (subtypeOfP(testValue004, SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
                  { Object* units007 = units;
                    Skolem* units = ((Skolem*)(units007));

                    { Skolem* object006 = units;
                      Object* value006 = wrapString(unitString);
                      Object* oldValue006 = object006->variableValue;
                      Object* newValue006 = updateInContext(oldValue006, value006, object006->homeContext, false);

                      if (!(((boolean)(oldValue006)) &&
                          (oldValue006->primaryType() == SGT_UNIT_SUPPORT_STELLA_CS_VALUE))) {
                        object006->variableValue = newValue006;
                      }
                    }
                    return (KWD_UNIT_SUPPORT_FINAL_SUCCESS);
                  }
                }
                else {
                  return (KWD_UNIT_SUPPORT_FAILURE);
                }
              }
            }
            else {
              return (KWD_UNIT_SUPPORT_FAILURE);
            }
          }
        }
        else if (subtypeOfIntegerP(testValue001)) {
          { Object* magnitude003 = magnitude;
            IntegerWrapper* magnitude = ((IntegerWrapper*)(magnitude003));

            if ((magnitude->wrapperValue != NULL_INTEGER) &&
                (((double)(magnitude->wrapperValue)) == ((DimNumber*)(theValue->wrapperValue))->getMagnitude(unitString))) {
              { Surrogate* testValue005 = safePrimaryType(units);

                if (subtypeOfP(testValue005, SGT_UNIT_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
                  { Object* units008 = units;
                    PatternVariable* units = ((PatternVariable*)(units008));

                    return (selectProofResult(bindVariableToValueP(units, wrapString(unitString), true), false, true));
                  }
                }
                else if (subtypeOfP(testValue005, SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
                  { Object* units009 = units;
                    Skolem* units = ((Skolem*)(units009));

                    { Skolem* object007 = units;
                      Object* value007 = wrapString(unitString);
                      Object* oldValue007 = object007->variableValue;
                      Object* newValue007 = updateInContext(oldValue007, value007, object007->homeContext, false);

                      if (!(((boolean)(oldValue007)) &&
                          (oldValue007->primaryType() == SGT_UNIT_SUPPORT_STELLA_CS_VALUE))) {
                        object007->variableValue = newValue007;
                      }
                    }
                    return (KWD_UNIT_SUPPORT_FINAL_SUCCESS);
                  }
                }
                else {
                  return (KWD_UNIT_SUPPORT_FAILURE);
                }
              }
            }
            else {
              return (KWD_UNIT_SUPPORT_FAILURE);
            }
          }
        }
        else {
          return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
        }
      }
    }
    else {
      return (KWD_UNIT_SUPPORT_FAILURE);
    }
  }
}

Object* uPlusConstraint(IntegerWrapper* missingArgument, DimNumberLogicWrapper* x1, DimNumberLogicWrapper* x2, DimNumberLogicWrapper* x3) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        value = (eqlP(((DimNumber*)(x1->wrapperValue))->add(((DimNumber*)(x2->wrapperValue))), ((DimNumber*)(x3->wrapperValue))) ? TRUE_WRAPPER : FALSE_WRAPPER);
        break;
      case 0: 
        value = (((DimNumber*)(x3->wrapperValue))->pid->objectEqlP(((DimNumber*)(x2->wrapperValue))->pid) ? wrapDimNumber(((DimNumber*)(x3->wrapperValue))->subtract(((DimNumber*)(x2->wrapperValue)))) : NULL);
        break;
      case 1: 
        value = (((DimNumber*)(x3->wrapperValue))->pid->objectEqlP(((DimNumber*)(x1->wrapperValue))->pid) ? wrapDimNumber(((DimNumber*)(x3->wrapperValue))->subtract(((DimNumber*)(x1->wrapperValue)))) : NULL);
        break;
      case 2: 
        value = (((DimNumber*)(x1->wrapperValue))->pid->objectEqlP(((DimNumber*)(x2->wrapperValue))->pid) ? wrapDimNumber(((DimNumber*)(x1->wrapperValue))->add(((DimNumber*)(x2->wrapperValue)))) : NULL);
        break;
      default:
        break;
    }
    return (value);
  }
}

Object* uMinusConstraint(IntegerWrapper* missingArgument, DimNumberLogicWrapper* x1, DimNumberLogicWrapper* x2, DimNumberLogicWrapper* x3) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        value = (eqlP(((DimNumber*)(x1->wrapperValue))->subtract(((DimNumber*)(x2->wrapperValue))), ((DimNumber*)(x3->wrapperValue))) ? TRUE_WRAPPER : FALSE_WRAPPER);
        break;
      case 0: 
        value = (((DimNumber*)(x3->wrapperValue))->pid->objectEqlP(((DimNumber*)(x2->wrapperValue))->pid) ? wrapDimNumber(((DimNumber*)(x3->wrapperValue))->add(((DimNumber*)(x2->wrapperValue)))) : NULL);
        break;
      case 1: 
        value = (((DimNumber*)(x3->wrapperValue))->pid->objectEqlP(((DimNumber*)(x1->wrapperValue))->pid) ? wrapDimNumber(((DimNumber*)(x1->wrapperValue))->subtract(((DimNumber*)(x3->wrapperValue)))) : NULL);
        break;
      case 2: 
        value = (((DimNumber*)(x1->wrapperValue))->pid->objectEqlP(((DimNumber*)(x2->wrapperValue))->pid) ? wrapDimNumber(((DimNumber*)(x1->wrapperValue))->subtract(((DimNumber*)(x2->wrapperValue)))) : NULL);
        break;
      default:
        break;
    }
    return (value);
  }
}

Object* uTimesConstraint(IntegerWrapper* missingArgument, DimNumberLogicWrapper* x1, DimNumberLogicWrapper* x2, DimNumberLogicWrapper* x3) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        value = (eqlP(((DimNumber*)(x1->wrapperValue))->multiply(((DimNumber*)(x2->wrapperValue))), ((DimNumber*)(x3->wrapperValue))) ? TRUE_WRAPPER : FALSE_WRAPPER);
        break;
      case 0: 
        value = ((((DimNumber*)(x2->wrapperValue))->magnitude == 0.0) ? NULL : wrapDimNumber(((DimNumber*)(x3->wrapperValue))->divide(((DimNumber*)(x2->wrapperValue)))));
        break;
      case 1: 
        value = ((((DimNumber*)(x1->wrapperValue))->magnitude == 0.0) ? NULL : wrapDimNumber(((DimNumber*)(x3->wrapperValue))->divide(((DimNumber*)(x1->wrapperValue)))));
        break;
      case 2: 
        value = wrapDimNumber(((DimNumber*)(x1->wrapperValue))->multiply(((DimNumber*)(x2->wrapperValue))));
        break;
      default:
        break;
    }
    return (value);
  }
}

Object* uDivideConstraint(IntegerWrapper* missingArgument, DimNumberLogicWrapper* x1, DimNumberLogicWrapper* x2, DimNumberLogicWrapper* x3) {
  { Object* value = NULL;

    switch (missingArgument->wrapperValue) {
      case -1: 
        value = ((((DimNumber*)(x2->wrapperValue))->magnitude == 0.0) ? ((eqlP(((DimNumber*)(x1->wrapperValue)), ((DimNumber*)(x2->wrapperValue))->multiply(((DimNumber*)(x3->wrapperValue)))) ? TRUE_WRAPPER : FALSE_WRAPPER)) : ((eqlP(((DimNumber*)(x3->wrapperValue)), ((DimNumber*)(x1->wrapperValue))->divide(((DimNumber*)(x2->wrapperValue)))) ? TRUE_WRAPPER : FALSE_WRAPPER)));
        break;
      case 0: 
        value = wrapDimNumber(((DimNumber*)(x2->wrapperValue))->multiply(((DimNumber*)(x3->wrapperValue))));
        break;
      case 1: 
        value = ((((DimNumber*)(x3->wrapperValue))->magnitude == 0.0) ? NULL : wrapDimNumber(((DimNumber*)(x1->wrapperValue))->divide(((DimNumber*)(x3->wrapperValue)))));
        break;
      case 2: 
        value = ((((DimNumber*)(x2->wrapperValue))->magnitude == 0.0) ? NULL : wrapDimNumber(((DimNumber*)(x1->wrapperValue))->divide(((DimNumber*)(x2->wrapperValue)))));
        break;
      default:
        break;
    }
    return (value);
  }
}

Keyword* uAbsSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* mainarg = (proposition->arguments->theArray)[0];
    Object* mainargvalue = argumentBoundTo(mainarg);
    DimNumberLogicWrapper* mainargdim = ((!((boolean)(mainargvalue))) ? ((DimNumberLogicWrapper*)(NULL)) : helpGetDimNumber(mainargvalue));
    Object* absarg = (proposition->arguments->theArray)[1];
    Object* absargvalue = argumentBoundTo(absarg);
    DimNumberLogicWrapper* absargdim = ((!((boolean)(absargvalue))) ? ((DimNumberLogicWrapper*)(NULL)) : helpGetDimNumber(absargvalue));
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_UNIT_SUPPORT_STELLA_ITERATOR, NULL)));
    Cons* collection = NIL;

    lastmove = lastmove;
    if (!((boolean)(iterator))) {
      if (!((boolean)(absargvalue))) {
        if (!((boolean)(mainargvalue))) {
          return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
        }
        else {
          if (((boolean)(mainargdim))) {
            return (selectProofResult(bindArgumentToValueP(absarg, wrapDimNumber(((DimNumber*)(mainargdim->wrapperValue))->absoluteValue()), true), false, true));
          }
          else {
            return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
          }
        }
      }
      else {
        if (((boolean)(absargdim))) {
          if (((DimNumber*)(absargdim->wrapperValue))->magnitude < 0.0) {
            return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
          }
          else {
            collection = consList(2, absargdim, wrapDimNumber(((DimNumber*)(absargdim->wrapperValue))->negate()));
          }
        }
        else {
          return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
        }
      }
    }
    if (((boolean)(mainargdim))) {
      if (collection->memberP(mainargdim)) {
        {
          setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
          return (KWD_UNIT_SUPPORT_FINAL_SUCCESS);
        }
      }
      else {
        {
          setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
          return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
        }
      }
    }
    if (!((boolean)(iterator))) {
      iterator = collection->allocateIterator();
      setDynamicSlotValue(frame->dynamicSlots, SYM_UNIT_SUPPORT_STELLA_ITERATOR, iterator, NULL);
    }
    if (iterator->nextP() &&
        bindArgumentToValueP(mainarg, iterator->value, true)) {
      return (KWD_UNIT_SUPPORT_CONTINUING_SUCCESS);
    }
    else {
      return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
    }
  }
}

Keyword* uSignumSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* mainarg = (proposition->arguments->theArray)[0];
    Object* mainargvalue = argumentBoundTo(mainarg);
    DimNumberLogicWrapper* mainargdim = ((!((boolean)(mainargvalue))) ? ((DimNumberLogicWrapper*)(NULL)) : helpGetDimNumber(mainargvalue));
    Object* signumarg = (proposition->arguments->theArray)[1];
    Object* signumargvalue = argumentBoundTo(signumarg);

    lastmove = lastmove;
    if (!((boolean)(mainargvalue))) {
      return (KWD_UNIT_SUPPORT_FAILURE);
    }
    else {
      if (!((boolean)(signumargvalue))) {
        if (((boolean)(mainargdim))) {
          return (selectProofResult(bindArgumentToValueP(signumarg, wrapInteger(((DimNumber*)(mainargdim->wrapperValue))->signum()), true), false, true));
        }
        else {
          return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
        }
      }
      else {
        if (isaP(signumargvalue, SGT_UNIT_SUPPORT_STELLA_INTEGER_WRAPPER) &&
            ((boolean)(mainargdim))) {
          if (((DimNumber*)(mainargdim->wrapperValue))->signum() == ((IntegerWrapper*)(signumargvalue))->wrapperValue) {
            {
              setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
              return (KWD_UNIT_SUPPORT_FINAL_SUCCESS);
            }
          }
          else {
            {
              setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
              return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
            }
          }
        }
        else {
          return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
        }
      }
    }
  }
}

Keyword* minimumOfUnitsSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* listarg = (proposition->arguments->theArray)[0];
    Object* listskolem = argumentBoundTo(listarg);
    Object* minarg = (proposition->arguments->theArray)[1];
    Object* minvalue = argumentBoundTo(minarg);
    DimNumber* minimum = NULL;
    boolean missingunitsP = false;

    lastmove = lastmove;
    if (((boolean)(listskolem)) &&
        (!logicalCollectionP(listskolem))) {
      std::cout << std::endl << "Non list appears in second argument to 'MINIMUM-OF-UNITS'" << std::endl << std::endl;
      return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
    }
    { List* listvalue = assertedCollectionMembers(listskolem, true);
      DimNumberLogicWrapper* dimvalue = NULL;

      if (listvalue->emptyP()) {
        return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
      }
      { Object* v = NULL;
        Cons* iter000 = listvalue->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          v = iter000->value;
          dimvalue = helpGetDimNumber(v);
          if (((boolean)(dimvalue))) {
            if ((!((boolean)(minimum))) ||
                ((DimNumber*)(dimvalue->wrapperValue))->lessP(minimum)) {
              minimum = ((DimNumber*)(dimvalue->wrapperValue));
            }
          }
          else {
            missingunitsP = true;
          }
        }
      }
      if (!((boolean)(minimum))) {
        return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
      }
      if (missingunitsP) {
        if (((boolean)(minvalue)) &&
            (((boolean)(helpGetDimNumber(minvalue))) &&
             ((DimNumber*)(helpGetDimNumber(minvalue)->wrapperValue))->greaterP(minimum))) {
          {
            setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
            return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
          }
        }
        else {
          {
            setFrameTruthValue(frame, UNKNOWN_TRUTH_VALUE);
            return (KWD_UNIT_SUPPORT_FAILURE);
          }
        }
      }
      if (bindArgumentToValueP(minarg, wrapDimNumber(minimum), true)) {
        {
          setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
          return (KWD_UNIT_SUPPORT_FINAL_SUCCESS);
        }
      }
      else {
        {
          setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
          return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
        }
      }
    }
  }
}

Keyword* maximumOfUnitsSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* listarg = (proposition->arguments->theArray)[0];
    Object* listskolem = argumentBoundTo(listarg);
    Object* maxarg = (proposition->arguments->theArray)[1];
    Object* maxvalue = argumentBoundTo(maxarg);
    DimNumber* maximum = NULL;
    boolean missingunitsP = false;

    lastmove = lastmove;
    if (((boolean)(listskolem)) &&
        (!logicalCollectionP(listskolem))) {
      std::cout << std::endl << "Non list appears in second argument to 'MAXIMUM-OF-UNITS'" << std::endl << std::endl;
      return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
    }
    { List* listvalue = assertedCollectionMembers(listskolem, true);
      DimNumberLogicWrapper* dimvalue = NULL;

      if (listvalue->emptyP()) {
        return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
      }
      { Object* v = NULL;
        Cons* iter000 = listvalue->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          v = iter000->value;
          dimvalue = helpGetDimNumber(v);
          if (isaP(v, SGT_UNIT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER)) {
            if ((!((boolean)(maximum))) ||
                ((DimNumber*)(dimvalue->wrapperValue))->greaterP(maximum)) {
              maximum = ((DimNumber*)(dimvalue->wrapperValue));
            }
          }
          else {
            missingunitsP = true;
          }
        }
      }
      if (!((boolean)(maximum))) {
        return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
      }
      if (missingunitsP) {
        if (((boolean)(maxvalue)) &&
            (((boolean)(helpGetDimNumber(maxvalue))) &&
             ((DimNumber*)(helpGetDimNumber(maxvalue)->wrapperValue))->lessP(maximum))) {
          {
            setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
            return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
          }
        }
        else {
          {
            setFrameTruthValue(frame, UNKNOWN_TRUTH_VALUE);
            return (KWD_UNIT_SUPPORT_FAILURE);
          }
        }
      }
      if (bindArgumentToValueP(maxarg, wrapDimNumber(maximum), true)) {
        {
          setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
          return (KWD_UNIT_SUPPORT_FINAL_SUCCESS);
        }
      }
      else {
        {
          setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
          return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
        }
      }
    }
  }
}

Keyword* sumOfUnitsSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* listarg = (proposition->arguments->theArray)[0];
    Object* listskolem = argumentBoundTo(listarg);
    Object* sumarg = (proposition->arguments->theArray)[1];
    DimNumber* sum = NULL;

    lastmove = lastmove;
    if (((boolean)(listskolem)) &&
        (!logicalCollectionP(listskolem))) {
      std::cout << std::endl << "Non list appears in second argument to 'SUM-OF-NUMBERS'" << std::endl << std::endl;
      return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
    }
    { List* listvalue = assertedCollectionMembers(listskolem, true);
      DimNumberLogicWrapper* dimvalue = NULL;

      if (listvalue->emptyP()) {
        return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
      }
      try {
        { Object* v = NULL;
          Cons* iter000 = listvalue->theConsList;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            v = iter000->value;
            dimvalue = helpGetDimNumber(v);
            if (((boolean)(dimvalue))) {
              if (!((boolean)(sum))) {
                sum = ((DimNumber*)(dimvalue->wrapperValue));
              }
              else {
                sum = sum->add(((DimNumber*)(dimvalue->wrapperValue)));
              }
            }
            else {
              return (KWD_UNIT_SUPPORT_FAILURE);
            }
          }
        }
      }
      catch (IncompatibleUnitsException ) {
        return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
      }
      if (!((boolean)(sum))) {
        return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
      }
      if (bindArgumentToValueP(sumarg, wrapDimNumber(sum), true)) {
        {
          setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
          return (KWD_UNIT_SUPPORT_FINAL_SUCCESS);
        }
      }
      else {
        {
          setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
          return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
        }
      }
    }
  }
}

Keyword* uValueMeasureSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* mainarg = (proposition->arguments->theArray)[0];
    Object* mainargvalue = argumentBoundTo(mainarg);
    Object* measurearg = (proposition->arguments->theArray)[1];
    Object* measureargvalue = argumentBoundTo(measurearg);

    lastmove = lastmove;
    if (!((boolean)(mainargvalue))) {
      return (KWD_UNIT_SUPPORT_FAILURE);
    }
    else {
      if (!((boolean)(measureargvalue))) {
        if (isaP(mainargvalue, SGT_UNIT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER)) {
          { Measure* measure = ((DimNumber*)(((DimNumberLogicWrapper*)(mainargvalue))->wrapperValue))->getMeasure();
            LogicObject* measureInstance = (((boolean)(measure)) ? ((LogicObject*)(oMEASURE_INSTANCE_TABLEo->lookup(measure))) : ((LogicObject*)(NULL)));

            if (((boolean)(measureInstance))) {
              return (selectProofResult(bindArgumentToValueP(measurearg, measureInstance, true), false, true));
            }
            else {
              return (KWD_UNIT_SUPPORT_FAILURE);
            }
          }
        }
        else {
          return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
        }
      }
      else {
        if (isaP(mainargvalue, SGT_UNIT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER)) {
          { Measure* measure = ((DimNumber*)(((DimNumberLogicWrapper*)(mainargvalue))->wrapperValue))->getMeasure();
            LogicObject* measureInstance = (((boolean)(measure)) ? ((LogicObject*)(oMEASURE_INSTANCE_TABLEo->lookup(measure))) : ((LogicObject*)(NULL)));

            if (((boolean)(measureInstance))) {
              if (measureargvalue == measureInstance) {
                {
                  setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
                  return (KWD_UNIT_SUPPORT_FINAL_SUCCESS);
                }
              }
              else {
                {
                  setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
                  return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
                }
              }
            }
            else {
              return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
            }
          }
        }
        else {
          return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
        }
      }
    }
  }
}

boolean argumentMatchesListHelperP(Object* argument, List* theList) {
  { Surrogate* testValue000 = safePrimaryType(argument);

    if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
      { Object* argument000 = argument;
        PatternVariable* argument = ((PatternVariable*)(argument000));

        { Object* value = (oQUERYITERATORo->currentPatternRecord->variableBindings->theArray)[(argument->boundToOffset)];

          if (((boolean)(value))) {
            return (argumentMatchesListHelperP(value, theList));
          }
          else {
            return (true);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_LOGIC_SKOLEM)) {
      { Object* argument001 = argument;
        Skolem* argument = ((Skolem*)(argument001));

        { Proposition* prop = argument->definingProposition;
          Vector* args = (((boolean)(prop)) ? prop->arguments : ((Vector*)(NULL)));
          int listLength = theList->length();

          if (!((boolean)(args))) {
            return (false);
          }
          else if (args->length() == (listLength + 1)) {
            { Object* item = NULL;
              Cons* iter000 = theList->theConsList;
              int i = NULL_INTEGER;
              int iter001 = 0;

              for  (; !(iter000 == NIL); 
                    iter000 = iter000->rest,
                    iter001 = iter001 + 1) {
                item = iter000->value;
                i = iter001;
                if (!(eqlP(item, (args->theArray)[i]))) {
                  return (false);
                }
              }
            }
            return (true);
          }
          else {
            return (false);
          }
        }
      }
    }
    else {
      return (false);
    }
  }
}

Keyword* integerToMeasuresHelper(ControlFrame* frame, Keyword* lastmove, int code) {
  lastmove = lastmove;
  { Proposition* proposition = frame->proposition;
    Object* listarg = (proposition->arguments->theArray)[1];
    Object* listargvalue = argumentBoundTo(listarg);
    List* measureslist = newList();

    { Measure* m = NULL;
      Cons* iter000 = computeMeasuresForInteger(code);
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        m = ((Measure*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(((LogicObject*)(oMEASURE_INSTANCE_TABLEo->lookup(m))), NIL);
            if (measureslist->theConsList == NIL) {
              measureslist->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(measureslist->theConsList, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(((LogicObject*)(oMEASURE_INSTANCE_TABLEo->lookup(m))), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    if (!((boolean)(listargvalue))) {
      return (selectProofResult(bindArgumentToValueP(listarg, createLogicalList(measureslist), true), false, true));
    }
    else if (argumentMatchesListHelperP(listarg, measureslist)) {
      setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
      return (KWD_UNIT_SUPPORT_FINAL_SUCCESS);
    }
    else {
      setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
      return (KWD_UNIT_SUPPORT_TERMINAL_FAILURE);
    }
  }
}

Keyword* uBaseMeasuresSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* mainarg = (proposition->arguments->theArray)[0];
    Object* mainargvalue = argumentBoundTo(mainarg);
    int value = NULL_INTEGER;

    if (!((boolean)(mainargvalue))) {
      return (KWD_UNIT_SUPPORT_FAILURE);
    }
    else {
      { Surrogate* testValue000 = safePrimaryType(mainargvalue);

        if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER)) {
          { Object* mainargvalue000 = mainargvalue;
            DimNumberLogicWrapper* mainargvalue = ((DimNumberLogicWrapper*)(mainargvalue000));

            { GeneralizedSymbol* testValue001 = proposition->operatoR;

              if (testValue001 == SGT_UNIT_SUPPORT_UNIT_KB_NUMERATOR_MEASURES) {
                value = ((DimNumber*)(mainargvalue->wrapperValue))->pid->numerator;
              }
              else if (testValue001 == SGT_UNIT_SUPPORT_UNIT_KB_DENOMINATOR_MEASURES) {
                value = ((DimNumber*)(mainargvalue->wrapperValue))->pid->denominator;
              }
              else {
                { OutputStringStream* stream000 = newOutputStringStream();

                  *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
                  throw *newStellaException(stream000->theStringReader());
                }
              }
            }
            return (integerToMeasuresHelper(frame, lastmove, value));
          }
        }
        else if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_LOGIC_LOGIC_OBJECT)) {
          { Object* mainargvalue001 = mainargvalue;
            LogicObject* mainargvalue = ((LogicObject*)(mainargvalue001));

            { Measure* measure = ((Measure*)(oINSTANCE_MEASURE_TABLEo->lookup(mainargvalue)));

              if (((boolean)(measure))) {
                { GeneralizedSymbol* testValue002 = proposition->operatoR;

                  if (testValue002 == SGT_UNIT_SUPPORT_UNIT_KB_NUMERATOR_MEASURES) {
                    value = measure->primeId->numerator;
                  }
                  else if (testValue002 == SGT_UNIT_SUPPORT_UNIT_KB_DENOMINATOR_MEASURES) {
                    value = measure->primeId->denominator;
                  }
                  else {
                    { OutputStringStream* stream001 = newOutputStringStream();

                      *(stream001->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
                      throw *newStellaException(stream001->theStringReader());
                    }
                  }
                }
                return (integerToMeasuresHelper(frame, lastmove, value));
              }
            }
            return (KWD_UNIT_SUPPORT_FAILURE);
          }
        }
        else {
          return (KWD_UNIT_SUPPORT_FAILURE);
        }
      }
    }
  }
}

Ratio* getObjectPid(Object* obj) {
  { Surrogate* testValue000 = safePrimaryType(obj);

    if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER)) {
      { Object* obj000 = obj;
        DimNumberLogicWrapper* obj = ((DimNumberLogicWrapper*)(obj000));

        return (((DimNumber*)(obj->wrapperValue))->pid);
      }
    }
    else if (subtypeOfStringP(testValue000)) {
      { Object* obj001 = obj;
        StringWrapper* obj = ((StringWrapper*)(obj001));

        { const char* stringValue = obj->wrapperValue;

          if (stringValue == NULL) {
            return (NULL);
          }
          else {
            { double dummy = NULL_FLOAT;
              Ratio* pid = NULL;

              dummy = unitToScaleFactorAndId(stringValue, pid);
              dummy = dummy;
              return (pid);
            }
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_UNIT_SUPPORT_STELLA_NUMBER_WRAPPER)) {
      { Object* obj002 = obj;
        NumberWrapper* obj = ((NumberWrapper*)(obj002));

        return (oRATIO_ONEo);
      }
    }
    else {
      return (NULL);
    }
  }
}

Keyword* comensurateUnitsSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* arg1 = (proposition->arguments->theArray)[0];
    Object* arg1Value = argumentBoundTo(arg1);
    Object* arg2 = (proposition->arguments->theArray)[1];
    Object* arg2Value = argumentBoundTo(arg2);

    lastmove = lastmove;
    if ((!((boolean)(arg1Value))) ||
        (!((boolean)(arg2Value)))) {
      return (KWD_UNIT_SUPPORT_FAILURE);
    }
    else {
      try {
        { Ratio* arg1Pid = getObjectPid(arg1Value);
          Ratio* arg2Pid = getObjectPid(arg2Value);

          if (((boolean)(arg1Pid)) &&
              ((boolean)(arg2Pid))) {
            return (selectTestResult(arg1Pid->objectEqlP(arg2Pid), true, frame));
          }
          else {
            return (KWD_UNIT_SUPPORT_FAILURE);
          }
        }
      }
      catch (BadArgumentException ) {
        return (selectTestResult(false, true, frame));
      }
    }
  }
}

// Mapping table from measure objects to their PowerLoom representation.
HashTable* oMEASURE_INSTANCE_TABLEo = NULL;

// Mapping table from PowerLoom representations of measures to measure objects
HashTable* oINSTANCE_MEASURE_TABLEo = NULL;

void initializeMeasureConcepts() {
  { 
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getStellaContext("PL-KERNEL-KB", true));
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
    { LogicObject* i = NULL;
      LogicObject* measure = pli::getConcept("/UNIT-KB/MEASURE", NULL, NULL);
      LogicObject* baseMeasure = pli::getConcept("/UNIT-KB/BASE-MEASURE", NULL, NULL);
      LogicObject* unitRelation = pli::getRelation("/UNIT-KB/MEASURE-UNIT", NULL, NULL);
      const char* measureName = NULL;

      { Measure* m = NULL;
        Cons* iter000 = oALL_MEASURESo;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          m = ((Measure*)(iter000->value));
          measureName = stringConcatenate("/UNIT-KB/", stringUpcase(m->name), 1, "-MEASURE");
          i = pli::getConcept(measureName, NULL, NULL);
          if (!(((boolean)(i)))) {
            i = pli::createConcept(measureName, measure, NULL, NULL);
          }
          pli::assertUnaryProposition(measure, i, NULL, NULL);
          if (oBASE_MEASURESo->memberP(m)) {
            pli::assertUnaryProposition(baseMeasure, i, NULL, NULL);
          }
          oMEASURE_INSTANCE_TABLEo->insertAt(m, i);
          oINSTANCE_MEASURE_TABLEo->insertAt(i, m);
          { StringWrapper* u = NULL;
            Cons* iter001 = m->getUnits()->theConsList;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              u = ((StringWrapper*)(iter001->value));
              pli::assertBinaryProposition(unitRelation, i, u, NULL, NULL);
            }
          }
        }
      }
    }
  }
}

void startupUnitSupport() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/UNIT-SUPPORT", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SGT_UNIT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("DIM-NUMBER-LOGIC-WRAPPER", NULL, 1)));
      SGT_UNIT_SUPPORT_UNIT_KB_UNITS = ((Surrogate*)(internRigidSymbolWrtModule("UNITS", getStellaModule("/UNIT-KB", true), 1)));
      SGT_UNIT_SUPPORT_TIMEPOINT_SUPPORT_DATE_TIME_LOGIC_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("DATE-TIME-LOGIC-WRAPPER", getStellaModule("/TIMEPOINT-SUPPORT", true), 1)));
      SGT_UNIT_SUPPORT_STELLA_CALENDAR_DATE = ((Surrogate*)(internRigidSymbolWrtModule("CALENDAR-DATE", getStellaModule("/STELLA", true), 1)));
      SGT_UNIT_SUPPORT_STELLA_TIME_DURATION = ((Surrogate*)(internRigidSymbolWrtModule("TIME-DURATION", getStellaModule("/STELLA", true), 1)));
      SGT_UNIT_SUPPORT_LOGIC_PATTERN_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("PATTERN-VARIABLE", getStellaModule("/LOGIC", true), 1)));
      SGT_UNIT_SUPPORT_LOGIC_SKOLEM = ((Surrogate*)(internRigidSymbolWrtModule("SKOLEM", getStellaModule("/LOGIC", true), 1)));
      SGT_UNIT_SUPPORT_STELLA_CS_VALUE = ((Surrogate*)(internRigidSymbolWrtModule("CS-VALUE", getStellaModule("/STELLA", true), 1)));
      KWD_UNIT_SUPPORT_FINAL_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("FINAL-SUCCESS", NULL, 2)));
      KWD_UNIT_SUPPORT_TERMINAL_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("TERMINAL-FAILURE", NULL, 2)));
      KWD_UNIT_SUPPORT_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("FAILURE", NULL, 2)));
      SYM_UNIT_SUPPORT_STELLA_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR", getStellaModule("/STELLA", true), 0)));
      KWD_UNIT_SUPPORT_CONTINUING_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("CONTINUING-SUCCESS", NULL, 2)));
      SGT_UNIT_SUPPORT_STELLA_INTEGER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER-WRAPPER", getStellaModule("/STELLA", true), 1)));
      SGT_UNIT_SUPPORT_UNIT_KB_NUMERATOR_MEASURES = ((Surrogate*)(internRigidSymbolWrtModule("NUMERATOR-MEASURES", getStellaModule("/UNIT-KB", true), 1)));
      SGT_UNIT_SUPPORT_UNIT_KB_DENOMINATOR_MEASURES = ((Surrogate*)(internRigidSymbolWrtModule("DENOMINATOR-MEASURES", getStellaModule("/UNIT-KB", true), 1)));
      SGT_UNIT_SUPPORT_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", getStellaModule("/LOGIC", true), 1)));
      SGT_UNIT_SUPPORT_STELLA_NUMBER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER-WRAPPER", getStellaModule("/STELLA", true), 1)));
      SYM_UNIT_SUPPORT_UNIT_SUPPORT_STARTUP_UNIT_SUPPORT = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-UNIT-SUPPORT", NULL, 0)));
      SYM_UNIT_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
    }
    if (currentStartupTimePhaseP(4)) {
      oDIM_NUMBER_HASH_TABLEo = newStellaHashTable();
      oMEASURE_INSTANCE_TABLEo = newHashTable();
      oINSTANCE_MEASURE_TABLEo = newHashTable();
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("DIM-NUMBER-LOGIC-WRAPPER", "(DEFCLASS DIM-NUMBER-LOGIC-WRAPPER (QUANTITY-LOGIC-WRAPPER) :PUBLIC-SLOTS ((WRAPPER-VALUE :TYPE DIM-NUMBER :REQUIRED? TRUE)) :PRINT-FORM (IF *PRINTREADABLY?* (PRINT-NATIVE-STREAM STREAM (WRAPPER-VALUE SELF)) (PRINT-NATIVE-STREAM STREAM \"|uw|\" (WRAPPER-VALUE SELF))))");

        clasS->classConstructorCode = ((cpp_function_code)(&newDimNumberLogicWrapper));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineMethodObject("(DEFMETHOD (GENERATE-SPECIALIZED-TERM OBJECT) ((SELF DIM-NUMBER-LOGIC-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&DimNumberLogicWrapper::generateSpecializedTerm))), NULL);
      defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF DIM-NUMBER-LOGIC-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&DimNumberLogicWrapper::hashCode))), NULL);
      defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((SELF DIM-NUMBER-LOGIC-WRAPPER) (X OBJECT)))", wrapMethodCode(((cpp_method_code)(&DimNumberLogicWrapper::objectEqlP))), NULL);
      defineFunctionObject("WRAP-DIM-NUMBER", "(DEFUN (WRAP-DIM-NUMBER DIM-NUMBER-LOGIC-WRAPPER) ((VALUE DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Return an interned LOGIC-WRAPPER for `value'.  This assures us\nthat all logic-wrapped DIM-NUMBERs are the same object.\")", ((cpp_function_code)(&wrapDimNumber)), NULL);
      defineMethodObject("(DEFMETHOD (GET-UNIT STRING) ((SELF DIM-NUMBER-LOGIC-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&DimNumberLogicWrapper::getUnit))), NULL);
      defineMethodObject("(DEFMETHOD (GET-BASE-UNIT STRING) ((SELF DIM-NUMBER-LOGIC-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&DimNumberLogicWrapper::getBaseUnit))), NULL);
      defineMethodObject("(DEFMETHOD (GET-MAGNITUDE FLOAT) ((SELF DIM-NUMBER-LOGIC-WRAPPER) (UNITS STRING)))", wrapMethodCode(((cpp_method_code)(&DimNumberLogicWrapper::getMagnitude))), NULL);
      defineFunctionObject("HELP-GET-DIM-NUMBER", "(DEFUN (HELP-GET-DIM-NUMBER DIM-NUMBER-LOGIC-WRAPPER) ((ITEM OBJECT)))", ((cpp_function_code)(&helpGetDimNumber)), NULL);
      defineFunctionObject("HELP-GET-UNIT-VALUE", "(DEFUN (HELP-GET-UNIT-VALUE DIM-NUMBER-LOGIC-WRAPPER) ((MAGNITUDE OBJECT) (UNITS OBJECT)))", ((cpp_function_code)(&helpGetUnitValue)), NULL);
      defineFunctionObject("UNITS-EVALUATOR", "(DEFUN UNITS-EVALUATOR ((SELF PROPOSITION)))", ((cpp_function_code)(&unitsEvaluator)), NULL);
      defineFunctionObject("UNITS-SPECIALIST", "(DEFUN (UNITS-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&unitsSpecialist)), NULL);
      defineFunctionObject("U-PLUS-CONSTRAINT", "(DEFUN (U-PLUS-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X1 DIM-NUMBER-LOGIC-WRAPPER) (X2 DIM-NUMBER-LOGIC-WRAPPER) (X3 DIM-NUMBER-LOGIC-WRAPPER)))", ((cpp_function_code)(&uPlusConstraint)), NULL);
      defineFunctionObject("U-MINUS-CONSTRAINT", "(DEFUN (U-MINUS-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X1 DIM-NUMBER-LOGIC-WRAPPER) (X2 DIM-NUMBER-LOGIC-WRAPPER) (X3 DIM-NUMBER-LOGIC-WRAPPER)))", ((cpp_function_code)(&uMinusConstraint)), NULL);
      defineFunctionObject("U-TIMES-CONSTRAINT", "(DEFUN (U-TIMES-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X1 DIM-NUMBER-LOGIC-WRAPPER) (X2 DIM-NUMBER-LOGIC-WRAPPER) (X3 DIM-NUMBER-LOGIC-WRAPPER)))", ((cpp_function_code)(&uTimesConstraint)), NULL);
      defineFunctionObject("U-DIVIDE-CONSTRAINT", "(DEFUN (U-DIVIDE-CONSTRAINT OBJECT) ((MISSING-ARGUMENT INTEGER-WRAPPER) (X1 DIM-NUMBER-LOGIC-WRAPPER) (X2 DIM-NUMBER-LOGIC-WRAPPER) (X3 DIM-NUMBER-LOGIC-WRAPPER)))", ((cpp_function_code)(&uDivideConstraint)), NULL);
      defineFunctionObject("U-ABS-SPECIALIST", "(DEFUN (U-ABS-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&uAbsSpecialist)), NULL);
      defineFunctionObject("U-SIGNUM-SPECIALIST", "(DEFUN (U-SIGNUM-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&uSignumSpecialist)), NULL);
      defineFunctionObject("MINIMUM-OF-UNITS-SPECIALIST", "(DEFUN (MINIMUM-OF-UNITS-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&minimumOfUnitsSpecialist)), NULL);
      defineFunctionObject("MAXIMUM-OF-UNITS-SPECIALIST", "(DEFUN (MAXIMUM-OF-UNITS-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&maximumOfUnitsSpecialist)), NULL);
      defineFunctionObject("SUM-OF-UNITS-SPECIALIST", "(DEFUN (SUM-OF-UNITS-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&sumOfUnitsSpecialist)), NULL);
      defineFunctionObject("U-VALUE-MEASURE-SPECIALIST", "(DEFUN (U-VALUE-MEASURE-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&uValueMeasureSpecialist)), NULL);
      defineFunctionObject("ARGUMENT-MATCHES-LIST-HELPER?", "(DEFUN (ARGUMENT-MATCHES-LIST-HELPER? BOOLEAN) ((ARGUMENT OBJECT) (THE-LIST LIST)))", ((cpp_function_code)(&argumentMatchesListHelperP)), NULL);
      defineFunctionObject("INTEGER-TO-MEASURES-HELPER", "(DEFUN (INTEGER-TO-MEASURES-HELPER KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD) (CODE INTEGER)))", ((cpp_function_code)(((Keyword*  (*) (ControlFrame*, Keyword*, int))(&integerToMeasuresHelper)))), NULL);
      defineFunctionObject("U-BASE-MEASURES-SPECIALIST", "(DEFUN (U-BASE-MEASURES-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&uBaseMeasuresSpecialist)), NULL);
      defineFunctionObject("GET-OBJECT-PID", "(DEFUN (GET-OBJECT-PID RATIO) ((OBJ OBJECT)))", ((cpp_function_code)(&getObjectPid)), NULL);
      defineFunctionObject("COMENSURATE-UNITS-SPECIALIST", "(DEFUN (COMENSURATE-UNITS-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&comensurateUnitsSpecialist)), NULL);
      defineFunctionObject("INITIALIZE-MEASURE-CONCEPTS", "(DEFUN INITIALIZE-MEASURE-CONCEPTS ())", ((cpp_function_code)(&initializeMeasureConcepts)), NULL);
      defineFunctionObject("STARTUP-UNIT-SUPPORT", "(DEFUN STARTUP-UNIT-SUPPORT () :PUBLIC? TRUE)", ((cpp_function_code)(&startupUnitSupport)), NULL);
      { MethodSlot* function = lookupFunction(SYM_UNIT_SUPPORT_UNIT_SUPPORT_STARTUP_UNIT_SUPPORT);

        setDynamicSlotValue(function->dynamicSlots, SYM_UNIT_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupUnitSupport"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("UNIT-SUPPORT")))));
      defineGlobalVariableObject("(DEFGLOBAL *DIM-NUMBER-HASH-TABLE* (STELLA-HASH-TABLE OF DIM-NUMBER DIM-NUMBER-LOGIC-WRAPPER) (NEW STELLA-HASH-TABLE) :DOCUMENTATION \"Table for interning dim number logic wrappers\")", &oDIM_NUMBER_HASH_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *MEASURE-INSTANCE-TABLE* (HASH-TABLE OF MEASURE LOGIC-OBJECT) (NEW HASH-TABLE) :DOCUMENTATION \"Mapping table from measure objects to their PowerLoom representation.\")", &oMEASURE_INSTANCE_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *INSTANCE-MEASURE-TABLE* (HASH-TABLE OF LOGIC-OBJECT MEASURE) (NEW HASH-TABLE) :DOCUMENTATION \"Mapping table from PowerLoom representations of measures to measure objects\")", &oINSTANCE_MEASURE_TABLEo);
    }
  }
}

Surrogate* SGT_UNIT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER = NULL;

Surrogate* SGT_UNIT_SUPPORT_UNIT_KB_UNITS = NULL;

Surrogate* SGT_UNIT_SUPPORT_TIMEPOINT_SUPPORT_DATE_TIME_LOGIC_WRAPPER = NULL;

Surrogate* SGT_UNIT_SUPPORT_STELLA_CALENDAR_DATE = NULL;

Surrogate* SGT_UNIT_SUPPORT_STELLA_TIME_DURATION = NULL;

Surrogate* SGT_UNIT_SUPPORT_LOGIC_PATTERN_VARIABLE = NULL;

Surrogate* SGT_UNIT_SUPPORT_LOGIC_SKOLEM = NULL;

Surrogate* SGT_UNIT_SUPPORT_STELLA_CS_VALUE = NULL;

Keyword* KWD_UNIT_SUPPORT_FINAL_SUCCESS = NULL;

Keyword* KWD_UNIT_SUPPORT_TERMINAL_FAILURE = NULL;

Keyword* KWD_UNIT_SUPPORT_FAILURE = NULL;

Symbol* SYM_UNIT_SUPPORT_STELLA_ITERATOR = NULL;

Keyword* KWD_UNIT_SUPPORT_CONTINUING_SUCCESS = NULL;

Surrogate* SGT_UNIT_SUPPORT_STELLA_INTEGER_WRAPPER = NULL;

Surrogate* SGT_UNIT_SUPPORT_UNIT_KB_NUMERATOR_MEASURES = NULL;

Surrogate* SGT_UNIT_SUPPORT_UNIT_KB_DENOMINATOR_MEASURES = NULL;

Surrogate* SGT_UNIT_SUPPORT_LOGIC_LOGIC_OBJECT = NULL;

Surrogate* SGT_UNIT_SUPPORT_STELLA_NUMBER_WRAPPER = NULL;

Symbol* SYM_UNIT_SUPPORT_UNIT_SUPPORT_STARTUP_UNIT_SUPPORT = NULL;

Symbol* SYM_UNIT_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace units
