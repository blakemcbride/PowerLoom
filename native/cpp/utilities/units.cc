//  -*- Mode: C++ -*-

// units.cc

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
| Portions created by the Initial Developer are Copyright (C) 2001-2023      |
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

#include "utilities/utilities-system.hh"

namespace stella_utilities {
  using namespace stella;

Cons* oPRIME_NUMBERSo = NULL;

int oCURRENT_PRIME_INDEXo = -1;

StellaHashTable* oPRIME_TO_MEASURE_TABLEo = NULL;

IntegerHashTable* oPRIME_TO_BASE_MEASURE_TABLEo = NULL;

StringHashTable* oNAME_TO_MEASURE_TABLEo = NULL;

StringHashTable* oUNIT_TO_MEASURE_TABLEo = NULL;

Cons* oALL_MEASURESo = NULL;

Cons* oBASE_MEASURESo = NULL;

int nextPrimeId() {
  oCURRENT_PRIME_INDEXo = oCURRENT_PRIME_INDEXo + 1;
  return (((IntegerWrapper*)(oPRIME_NUMBERSo->nth(oCURRENT_PRIME_INDEXo)))->wrapperValue);
}

IncompatibleUnitsException* newIncompatibleUnitsException(const char* message) {
  { IncompatibleUnitsException* self = NULL;

    self = new IncompatibleUnitsException(message);
    return (self);
  }
}

Ratio* oRATIO_ONEo = NULL;

Ratio* newRatio(int numerator, int denominator) {
  { Ratio* self = NULL;

    self = new (PointerFreeGC)Ratio;
    self->numerator = numerator;
    self->denominator = denominator;
    return (self);
  }
}

Surrogate* Ratio::primaryType() {
  { Ratio* self = this;

    return (SGT_UNITS_UTILITIES_RATIO);
  }
}

Object* accessRatioSlotValue(Ratio* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_UNITS_UTILITIES_NUMERATOR) {
    if (setvalueP) {
      self->numerator = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->numerator);
    }
  }
  else if (slotname == SYM_UNITS_UTILITIES_DENOMINATOR) {
    if (setvalueP) {
      self->denominator = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->denominator);
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

void Ratio::printObject(std::ostream* stream) {
  { Ratio* self = this;

    *(stream) << self->numerator << "/" << self->denominator;
  }
}

Ratio* makeRatio(int num, int denom) {
  { long long int thegcd = gcd(((long long int)(num)), ((long long int)(denom)));
    int n = 0;
    int d = 0;
    boolean negativeP = false;

    if (num < 0) {
      {
        n = ((int)(((double)(0 - num)) / thegcd));
        negativeP = true;
      }
    }
    else {
      n = ((int)(((double)(num)) / thegcd));
    }
    if (denom < 0) {
      {
        d = ((int)(((double)(0 - denom)) / thegcd));
        negativeP = !negativeP;
      }
    }
    else {
      d = ((int)(((double)(denom)) / thegcd));
    }
    if (negativeP) {
      n = 0 - n;
    }
    return (newRatio(n, d));
  }
}

int Ratio::hashCode() {
  { Ratio* self = this;

    return (((self->numerator) | (((self->denominator) << 10))));
  }
}

Quantity* Ratio::coerceTo(Object* y) {
  // Coerces `y' to be a compatible type with `x'.
  // If this isn't possible, an exception is thrown.  The exception
  // will be either INCOMPATIBLE-QUANTITY-EXCEPTION or 
  // INCOMPATIBLE-UNITS-EXCEPTION.
  { Ratio* x = this;

    { Surrogate* testValue000 = safePrimaryType(y);

      if (subtypeOfP(testValue000, SGT_UNITS_UTILITIES_RATIO)) {
        { Object* y000 = y;
          Ratio* y = ((Ratio*)(y000));

          return (y);
        }
      }
      else if (subtypeOfIntegerP(testValue000)) {
        { Object* y001 = y;
          IntegerWrapper* y = ((IntegerWrapper*)(y001));

          return (makeRatio(y->wrapperValue, 1));
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Can't convert " << "`" << y << "'" << " to a RATIO";
          throw *newIncompatibleQuantityException(stream000->theStringReader());
        }
      }
    }
  }
}

boolean Ratio::objectEqlP(Object* y) {
  { Ratio* x = this;

    return (((boolean)(y)) &&
        ((y->primaryType() == SGT_UNITS_UTILITIES_RATIO) &&
         ((x->numerator == ((Ratio*)(y))->numerator) &&
          (x->denominator == ((Ratio*)(y))->denominator))));
  }
}

boolean Ratio::lessP(Object* y) {
  // Computes `x' < `y'
  { Ratio* x = this;

    { Ratio* yRatio = ((Ratio*)(x->coerceTo(y)));

      return ((x->numerator * yRatio->denominator) < (yRatio->numerator * x->denominator));
    }
  }
}

boolean Ratio::lessEqualP(Object* y) {
  // Computes `x' <= `y'
  { Ratio* x = this;

    { Ratio* yRatio = ((Ratio*)(x->coerceTo(y)));

      return ((x->numerator * yRatio->denominator) <= (yRatio->numerator * x->denominator));
    }
  }
}

boolean Ratio::greaterEqualP(Object* y) {
  // Computes `x' >= `y'
  { Ratio* x = this;

    { Ratio* yRatio = ((Ratio*)(x->coerceTo(y)));

      return ((x->numerator * yRatio->denominator) >= (yRatio->numerator * x->denominator));
    }
  }
}

boolean Ratio::greaterP(Object* y) {
  // Computes `x' > `y'
  { Ratio* x = this;

    { Ratio* yRatio = ((Ratio*)(x->coerceTo(y)));

      return ((x->numerator * yRatio->denominator) > (yRatio->numerator * x->denominator));
    }
  }
}

Ratio* Ratio::add(Ratio* y) {
  { Ratio* x = this;

    return (makeRatio((x->numerator * y->denominator) + (y->numerator * x->denominator), x->denominator * y->denominator));
  }
}

Ratio* Ratio::subtract(Ratio* y) {
  { Ratio* x = this;

    return (makeRatio((x->numerator * y->denominator) - (y->numerator * x->denominator), x->denominator * y->denominator));
  }
}

Ratio* Ratio::multiply(Ratio* y) {
  { Ratio* x = this;

    return (makeRatio(x->numerator * y->numerator, x->denominator * y->denominator));
  }
}

Ratio* Ratio::divide(Ratio* y) {
  { Ratio* x = this;

    return (makeRatio(x->numerator * y->denominator, x->denominator * y->numerator));
  }
}

Ratio* Ratio::negate() {
  { Ratio* x = this;

    return (newRatio(0 - x->numerator, x->denominator));
  }
}

Ratio* Ratio::invert() {
  { Ratio* x = this;

    return (newRatio(x->denominator, x->numerator));
  }
}

int ipower(int x, int exp) {
  if (exp < 0) {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "Illegal negative exponent: " << "`" << exp << "'";
      throw *newBadArgumentException(stream000->theStringReader());
    }
  }
  else {
    { int result = 1;

      while ((exp = exp - 1) >= 0) {
        result = result * x;
      }
      return (result);
    }
  }
}

Ratio* Ratio::exponentiate(int y) {
  { Ratio* x = this;

    if (y < 0) {
      return (newRatio(ipower(x->denominator, 0 - y), ipower(x->numerator, 0 - y)));
    }
    else {
      return (newRatio(ipower(x->numerator, y), ipower(x->denominator, y)));
    }
  }
}

Cons* oUNIT_TOKENIZER_TABLE_DEFINITIONo = NULL;

TokenizerTable* oUNIT_TOKENIZER_TABLEo = NULL;

Measure* newMeasure() {
  { Measure* self = NULL;

    self = new Measure();
    self->name = NULL;
    self->primeId = NULL;
    self->scale = newKeyValueList();
    self->baseUnit = NULL;
    return (self);
  }
}

Surrogate* Measure::primaryType() {
  { Measure* self = this;

    return (SGT_UNITS_UTILITIES_MEASURE);
  }
}

Object* accessMeasureSlotValue(Measure* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_UNITS_UTILITIES_BASE_UNIT) {
    if (setvalueP) {
      self->baseUnit = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->baseUnit);
    }
  }
  else if (slotname == SYM_UNITS_UTILITIES_SCALE) {
    if (setvalueP) {
      self->scale = ((KeyValueList*)(value));
    }
    else {
      value = self->scale;
    }
  }
  else if (slotname == SYM_UNITS_UTILITIES_PRIME_ID) {
    if (setvalueP) {
      self->primeId = ((Ratio*)(value));
    }
    else {
      value = self->primeId;
    }
  }
  else if (slotname == SYM_UNITS_STELLA_NAME) {
    if (setvalueP) {
      self->name = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->name);
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

void Measure::printObject(std::ostream* stream) {
  { Measure* self = this;

    *(stream) << "<Measure " << self->name << "(" << self->baseUnit << ")>";
  }
}

void resetMeasures() {
  oCURRENT_PRIME_INDEXo = -1;
  oPRIME_TO_MEASURE_TABLEo = newStellaHashTable();
  oPRIME_TO_BASE_MEASURE_TABLEo = newIntegerHashTable();
  oNAME_TO_MEASURE_TABLEo = newStringHashTable();
  oUNIT_TO_MEASURE_TABLEo = newStringHashTable();
  oALL_MEASURESo = NIL;
  oBASE_MEASURESo = NIL;
}

void Measure::setupIndices() {
  { Measure* m = this;

    oALL_MEASURESo = ((Cons*)((oALL_MEASURESo->memberP(m) ? oALL_MEASURESo : cons(m, oALL_MEASURESo))));
    oPRIME_TO_MEASURE_TABLEo->insertAt(m->primeId, m);
    oNAME_TO_MEASURE_TABLEo->insertAt(m->name, m);
    oUNIT_TO_MEASURE_TABLEo->insertAt(m->baseUnit, m);
  }
}

boolean Measure::baseMeasureP() {
  // Returns `true' if `m' is a base measure.
  { Measure* m = this;

    return (oBASE_MEASURESo->memberP(m));
  }
}

Measure* defineBaseMeasure(const char* measureName, const char* measureBaseUnit) {
  { int prime = nextPrimeId();

    { Measure* self000 = newMeasure();

      self000->name = measureName;
      self000->baseUnit = measureBaseUnit;
      self000->primeId = makeRatio(prime, 1);
      { Measure* m = self000;

        m->scale->insertAt(wrapString(measureBaseUnit), wrapFloat(1.0));
        oPRIME_TO_BASE_MEASURE_TABLEo->insertAt(prime, m);
        oBASE_MEASURESo = ((Cons*)((oBASE_MEASURESo->memberP(m) ? oBASE_MEASURESo : cons(m, oBASE_MEASURESo))));
        m->setupIndices();
        return (m);
      }
    }
  }
}

Measure* defineDerivedMeasure(const char* measureName, const char* measureBaseUnit, const char* definition) {
  { double scaleFactor = NULL_FLOAT;
    Ratio* id = NULL;

    scaleFactor = unitToScaleFactorAndId(definition, id);
    { Measure* self000 = newMeasure();

      self000->name = measureName;
      self000->baseUnit = measureBaseUnit;
      self000->primeId = id;
      { Measure* m = self000;

        m->scale->insertAt(wrapString(measureBaseUnit), wrapFloat(scaleFactor));
        m->setupIndices();
        return (m);
      }
    }
  }
}

Measure* defineDimensionlessMeasure() {
  { Measure* self000 = newMeasure();

    self000->name = "Dimensionless";
    self000->baseUnit = "";
    self000->primeId = oRATIO_ONEo;
    { Measure* m = self000;

      m->scale->insertAt(wrapString(""), wrapFloat(1.0));
      oBASE_MEASURESo = ((Cons*)((oBASE_MEASURESo->memberP(m) ? oBASE_MEASURESo : cons(m, oBASE_MEASURESo))));
      m->setupIndices();
      return (m);
    }
  }
}

void Measure::addUnit(const char* unitName, double scaleFactor, const char* definition) {
  { Measure* self = this;

    { double definitionFactor = NULL_FLOAT;
      Ratio* id = NULL;

      definitionFactor = unitToScaleFactorAndId(definition, id);
      if (eqlP(id, self->primeId)) {
        {
          self->scale->insertAt(wrapString(unitName), wrapFloat(scaleFactor * definitionFactor));
          oUNIT_TO_MEASURE_TABLEo->insertAt(unitName, self);
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Unit " << "`" << unitName << "'" << " has a definition " << "`" << definition << "'" << " that is not compatible with Measure " << "`" << self->name << "'";
          throw *newIncompatibleUnitsException(stream000->theStringReader());
        }
      }
    }
  }
}

Measure* lookupMeasure(const char* name) {
  return (((Measure*)(oNAME_TO_MEASURE_TABLEo->lookup(name))));
}

Measure* lookupMeasureForUnit(const char* unit) {
  return (((Measure*)(oUNIT_TO_MEASURE_TABLEo->lookup(unit))));
}

List* Measure::getUnits() {
  { Measure* self = this;

    { List* result = newList();

      { StringWrapper* key = NULL;
        FloatWrapper* unused = NULL;
        KvListIterator* iter000 = ((KvListIterator*)(self->scale->allocateIterator()));
        Cons* collect000 = NULL;

        for  (; iter000->nextP(); ) {
          key = ((StringWrapper*)(iter000->key));
          unused = ((FloatWrapper*)(iter000->value));
          unused = unused;
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(key, NIL);
              if (result->theConsList == NIL) {
                result->theConsList = collect000;
              }
              else {
                addConsToEndOfConsList(result->theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(key, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      return (result);
    }
  }
}

double unitToScaleFactorAndId(const char* definition, Ratio*& _Return1) {
  { double scaleFactor = 1.0;
    Ratio* id = oRATIO_ONEo;
    double factor = NULL_FLOAT;
    Ratio* pid = NULL;
    boolean invertP = false;
    const char* oneUnit = NULL;
    int exponentValue = NULL_INTEGER;
    Measure* m = NULL;
    boolean scaledP = true;

    { TokenizerTable* tok_table_ = oUNIT_TOKENIZER_TABLEo;
      const char* tok_transitions_ = tok_table_->transitions;
      Object** tok_statenames_ = tok_table_->stateNames->theArray;
      int tok_tokenstart_ = -1;
      boolean tok_endoftokensP_ = false;
      TokenizerStreamState* tok_streamstate_ = NULL;
      char* tok_buffer_ = mutableStringCopy(definition);
      int tok_state_ = 1;
      int tok_nextstate_ = tok_state_;
      int tok_cursor_ = 0;
      int tok_size_ = strlen(definition);
      int tok_end_ = tok_size_;

      {
        tok_statenames_ = tok_statenames_;
        tok_endoftokensP_ = tok_endoftokensP_;
      }
      tok_streamstate_ = tok_streamstate_;
      for (;;) {
        {
          tok_tokenstart_ = -1;
          for (;;) {
            if (tok_cursor_ == tok_end_) {
              if (tok_nextstate_ == -1) {
                tok_endoftokensP_ = true;
              }
              else if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)((tok_table_->legalEofStates->theArray)[tok_state_])))) {
                tok_nextstate_ = -1;
                if (tok_tokenstart_ == -1) {
                  tok_endoftokensP_ = true;
                }
              }
              else {
                tok_state_ = 0;
                tok_nextstate_ = -1;
              }
              break;
            }
            tok_nextstate_ = (int)(unsigned char) (tok_buffer_[tok_cursor_]);
            tok_nextstate_ = (int)(unsigned char) (tok_transitions_[((((tok_state_ << 8)) | tok_nextstate_))]);
            if ((tok_nextstate_ & 128) == 0) {
              tok_state_ = tok_nextstate_;
              tok_cursor_ = tok_cursor_ + 1;
            }
            else if (tok_tokenstart_ == -1) {
              if ((tok_nextstate_ & 64) == 0) {
                tok_tokenstart_ = tok_cursor_;
              }
              tok_state_ = (tok_nextstate_ & 63);
              tok_cursor_ = tok_cursor_ + 1;
            }
            else {
              break;
            }
          }
        }
        if (tok_endoftokensP_) {
          break;
        }
        { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tok_statenames_[tok_state_]));

          if (testValue000 == KWD_UNITS_UNIT) {
            oneUnit = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false);
            m = ((Measure*)(oUNIT_TO_MEASURE_TABLEo->lookup(oneUnit)));
            if (!((boolean)(m))) {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "Unrecognized unit: " << "`" << definition << "'";
                throw *newBadArgumentException(stream000->theStringReader());
              }
            }
            factor = ((FloatWrapper*)(m->scale->lookup(wrapString(oneUnit))))->wrapperValue;
            pid = m->primeId;
            scaledP = false;
          }
          else if (testValue000 == KWD_UNITS_INTEGER) {
            exponentValue = ((int)(stringToInteger(getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false))));
            if (invertP) {
              exponentValue = 0 - exponentValue;
            }
            factor = ::pow(factor,(((double)(exponentValue))));
            pid = pid->exponentiate(exponentValue);
            scaleFactor = scaleFactor * factor;
            id = id->multiply(pid);
            scaledP = true;
          }
          else if (testValue000 == KWD_UNITS_FRACTION) {
            if (!(scaledP)) {
              scaleFactor = scaleFactor * factor;
              id = id->multiply(pid);
              scaledP = true;
            }
            if (invertP) {
              { OutputStringStream* stream001 = newOutputStringStream();

                *(stream001->nativeStream) << "Multiple / signs in units expression is not allowed: " << "`" << definition << "'";
                throw *newBadArgumentException(stream001->theStringReader());
              }
            }
            else {
              invertP = true;
            }
          }
          else if (testValue000 == KWD_UNITS_ERROR) {
            { OutputStringStream* stream002 = newOutputStringStream();

              *(stream002->nativeStream) << "Error in units expression:  Not legal syntax: " << "`" << definition << "'";
              throw *newBadArgumentException(stream002->theStringReader());
            }
          }
          else if (testValue000 == KWD_UNITS_DELIMITER) {
            if (invertP) {
              {
                scaleFactor = scaleFactor / factor;
                id = id->divide(pid);
              }
            }
            else {
              {
                scaleFactor = scaleFactor * factor;
                id = id->multiply(pid);
              }
            }
            scaledP = true;
          }
          else {
            { OutputStringStream* stream003 = newOutputStringStream();

              *(stream003->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
              throw *newStellaException(stream003->theStringReader());
            }
          }
        }
      }
    }
    if (!(scaledP)) {
      if (invertP) {
        {
          scaleFactor = scaleFactor / factor;
          id = id->divide(pid);
        }
      }
      else {
        {
          scaleFactor = scaleFactor * factor;
          id = id->multiply(pid);
        }
      }
    }
    _Return1 = id;
    return (scaleFactor);
  }
}

Cons* computeMeasuresForInteger(int value) {
  { Cons* measures = NIL;
    int p = 1;

    { IntegerWrapper* prime = NULL;
      Cons* iter000 = oPRIME_NUMBERSo;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        prime = ((IntegerWrapper*)(iter000->value));
        p = prime->wrapperValue;
        while ((value % p) == 0) {
          value = ((int)(((double)(value)) / p));
          measures = cons(((Measure*)(oPRIME_TO_BASE_MEASURE_TABLEo->lookup(p))), measures);
        }
        if (value < p) {
          break;
        }
      }
    }
    return (measures->reverse());
  }
}

Cons* computeMeasuresForPrimeId(Ratio* pid, Cons*& _Return1) {
  // Returns two CONSes of Measure objects for the prime ID `pid'
  { Cons* _Return0 = computeMeasuresForInteger(pid->numerator);

    _Return1 = computeMeasuresForInteger(pid->denominator);
    return (_Return0);
  }
}

const char* computeUnitsForInteger(int value, boolean negateExponentP) {
  { char* buffer = makeRawMutableString(128);
    int i = 0;
    int p = 1;
    int e = 0;
    boolean previousNoExponentP = false;

    { IntegerWrapper* prime = NULL;
      Cons* iter000 = oPRIME_NUMBERSo;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        prime = ((IntegerWrapper*)(iter000->value));
        e = 0;
        p = prime->wrapperValue;
        while ((value % p) == 0) {
          value = ((int)(((double)(value)) / p));
          e = e + 1;
        }
        if (e > 0) {
          if (previousNoExponentP) {
            buffer[i] = '.';
            i = i + 1;
          }
          i = insertString(((Measure*)(oPRIME_TO_BASE_MEASURE_TABLEo->lookup(p)))->baseUnit, 0, NULL_INTEGER, buffer, i, KWD_UNITS_PRESERVE);
          if (negateExponentP) {
            i = insertString(integerToString(((long long int)(0 - e))), 0, NULL_INTEGER, buffer, i, KWD_UNITS_PRESERVE);
            previousNoExponentP = false;
          }
          else if (e > 1) {
            i = insertString(integerToString(((long long int)(e))), 0, NULL_INTEGER, buffer, i, KWD_UNITS_PRESERVE);
            previousNoExponentP = false;
          }
          else {
            previousNoExponentP = true;
          }
        }
        if (value < p) {
          break;
        }
      }
    }
    return (mutableStringSubsequence(buffer, 0, i));
  }
}

const char* computeUnitsForPrimeId(Ratio* pid) {
  { const char* numeratorString = computeUnitsForInteger(pid->numerator, false);
    const char* denominatorString = computeUnitsForInteger(pid->denominator, false);

    if (stringEqlP(denominatorString, "")) {
      return (numeratorString);
    }
    else {
      return (stringConcatenate(numeratorString, "/", 1, denominatorString));
    }
  }
}

DimNumber* newDimNumber(Ratio* pid, double magnitude) {
  { DimNumber* self = NULL;

    self = new DimNumber();
    self->pid = pid;
    self->magnitude = magnitude;
    self->preferredUnits = NULL;
    return (self);
  }
}

Surrogate* DimNumber::primaryType() {
  { DimNumber* self = this;

    return (SGT_UNITS_UTILITIES_DIM_NUMBER);
  }
}

Object* accessDimNumberSlotValue(DimNumber* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_UNITS_UTILITIES_PID) {
    if (setvalueP) {
      self->pid = ((Ratio*)(value));
    }
    else {
      value = self->pid;
    }
  }
  else if (slotname == SYM_UNITS_UTILITIES_MAGNITUDE) {
    if (setvalueP) {
      self->magnitude = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->magnitude);
    }
  }
  else if (slotname == SYM_UNITS_UTILITIES_PREFERRED_UNITS) {
    if (setvalueP) {
      self->preferredUnits = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->preferredUnits);
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

void DimNumber::printObject(std::ostream* stream) {
  { DimNumber* self = this;

    *(stream) << "<" << self->getMagnitude(self->getUnit()) << self->getUnit() << ">";
  }
}

DimNumber* makeDimNumber(double magnitude, const char* units) {
  { double scaleFactor = NULL_FLOAT;
    Ratio* id = NULL;

    scaleFactor = unitToScaleFactorAndId(units, id);
    { DimNumber* self000 = newDimNumber(id, magnitude * scaleFactor);

      self000->preferredUnits = units;
      { DimNumber* value000 = self000;

        return (value000);
      }
    }
  }
}

DimNumber* parseDimNumber(const char* input) {
  { char currentCharacter = NULL_CHARACTER;
    char lastCharacter = ' ';
    boolean signAllowedP = true;
    boolean decimalSeenP = false;
    int len = strlen(input);
    int index = 0;
    double magnitude = NULL_FLOAT;

    while (index < len) {
      currentCharacter = input[index];
      if ((currentCharacter == '+') ||
          (currentCharacter == '-')) {
        if (!signAllowedP) {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "Bad number format (sign in bad place): " << "`" << input << "'";
            throw *newBadArgumentException(stream000->theStringReader());
          }
        }
        signAllowedP = false;
      }
      else if (currentCharacter == '.') {
        if (decimalSeenP) {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "Bad number format (too many decimals): " << "`" << input << "'";
            throw *newBadArgumentException(stream001->theStringReader());
          }
        }
        decimalSeenP = true;
        signAllowedP = false;
      }
      else if (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) currentCharacter] == KWD_UNITS_DIGIT) {
        signAllowedP = false;
      }
      else if ((currentCharacter == 'e') ||
          (currentCharacter == 'E')) {
        if (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) lastCharacter] == KWD_UNITS_DIGIT) {
          signAllowedP = true;
        }
        else {
          break;
        }
      }
      else {
        if ((lastCharacter == 'e') ||
            (lastCharacter == 'E')) {
          index = index - 1;
        }
        break;
      }
      lastCharacter = currentCharacter;
      index = index + 1;
    }
    try {
      magnitude = stringToFloat(stringSubsequence(input, 0, index));
    }
    catch (std::exception ) {
      try {
        magnitude = ((double)(stringToInteger(stringSubsequence(input, 0, index))));
      }
      catch (std::exception ) {
        { OutputStringStream* stream002 = newOutputStringStream();

          *(stream002->nativeStream) << "Bad number format: " << "`" << input << "'";
          throw *newBadArgumentException(stream002->theStringReader());
        }
      }
    }
    return (makeDimNumber(magnitude, stringSubsequence(input, index, len)));
  }
}

Quantity* DimNumber::coerceTo(Object* y) {
  // Coerces `y' to be a compatible type with `x'.
  // If this isn't possible, an exception is thrown.  The exception
  // will be either INCOMPATIBLE-QUANTITY-EXCEPTION or 
  // INCOMPATIBLE-UNITS-EXCEPTION.
  { DimNumber* x = this;

    { Surrogate* testValue000 = safePrimaryType(y);

      if (subtypeOfP(testValue000, SGT_UNITS_UTILITIES_DIM_NUMBER)) {
        { Object* y000 = y;
          DimNumber* y = ((DimNumber*)(y000));

          return (y);
        }
      }
      else if (subtypeOfP(testValue000, SGT_UNITS_STELLA_TIME_DURATION)) {
        { Object* y001 = y;
          TimeDuration* y = ((TimeDuration*)(y001));

          return (timeDurationToDim(y));
        }
      }
      else if (subtypeOfIntegerP(testValue000)) {
        { Object* y002 = y;
          IntegerWrapper* y = ((IntegerWrapper*)(y002));

          return (makeDimNumber(((double)(y->wrapperValue)), ""));
        }
      }
      else if (subtypeOfFloatP(testValue000)) {
        { Object* y003 = y;
          FloatWrapper* y = ((FloatWrapper*)(y003));

          return (makeDimNumber(y->wrapperValue, ""));
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Can't convert " << "`" << y << "'" << " to a DIM-NUMBER";
          throw *newIncompatibleQuantityException(stream000->theStringReader());
        }
      }
    }
  }
}

double DimNumber::getMagnitude(const char* units) {
  // Returns the magnitude of the dim number in the given units.
  { DimNumber* self = this;

    { double scaleFactor = NULL_FLOAT;
      Ratio* id = NULL;

      scaleFactor = unitToScaleFactorAndId(units, id);
      if (eqlP(id, self->pid)) {
        return (self->magnitude / scaleFactor);
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Unit " << "`" << units << "'" << " is not compatible with " << "`" << self->getUnit() << "'";
          throw *newIncompatibleUnitsException(stream000->theStringReader());
        }
      }
    }
  }
}

const char* DimNumber::getUnit() {
  // Returns the units for the dim number.  This will return the
  // preferred output units if they exist, otherwise the base units. (see `get-base-unit')
  { DimNumber* self = this;

    { const char* units = self->preferredUnits;

      if (units != NULL) {
        return (units);
      }
      else {
        return (self->getBaseUnit());
      }
    }
  }
}

const char* DimNumber::getBaseUnit() {
  // Returns the base units for the dim number.
  { DimNumber* self = this;

    { Measure* measure = ((Measure*)(oPRIME_TO_MEASURE_TABLEo->lookup(self->pid)));

      if (((boolean)(measure))) {
        return (measure->baseUnit);
      }
      else {
        return (computeUnitsForPrimeId(self->pid));
      }
    }
  }
}

Measure* DimNumber::getMeasure() {
  // Returns the measure for the dim number, if one is defined.
  { DimNumber* self = this;

    return (((Measure*)(oPRIME_TO_MEASURE_TABLEo->lookup(self->pid))));
  }
}

Cons* DimNumber::getBaseMeasures(Cons*& _Return1) {
  // Returns cons of the base measures for the numerator and denominator
  // of `self'.
  { DimNumber* self = this;

    return (computeMeasuresForPrimeId(self->pid, _Return1));
  }
}

const char* DimNumber::formatDimNumber(const char* units, int decimals) {
  // Returns a string representation of `x' in `units' with `decimals' digits.
  { DimNumber* x = this;

    if (units == NULL) {
      units = x->getUnit();
    }
    if (decimals != NULL_INTEGER) {
      return (stringConcatenate(formatFloat(x->getMagnitude(units), decimals), units, 0));
    }
    else {
      return (stringConcatenate(floatToString(x->getMagnitude(units)), units, 0));
    }
  }
}

boolean compatibleUnitsP(DimNumber* x, DimNumber* y) {
  // Returns TRUE if the units of `x' and `y' are compatible.
  return (x->pid->objectEqlP(y->pid));
}

boolean DimNumber::objectEqlP(Object* y) {
  { DimNumber* x = this;

    return (((boolean)(y)) &&
        ((y->primaryType() == SGT_UNITS_UTILITIES_DIM_NUMBER) &&
         (x->pid->objectEqlP(((DimNumber*)(y))->pid) &&
          (x->magnitude == ((DimNumber*)(y))->magnitude))));
  }
}

int DimNumber::hashCode() {
  { DimNumber* self = this;

    return ((((size_t)(self->magnitude)) ^ (self->pid->hashCode())));
  }
}

int DimNumber::signum() {
  // Computes the signum of `x':  -1 if negative, 0 if zero, 1 if positive
  { DimNumber* x = this;

    if (x->magnitude > 0.0) {
      return (1);
    }
    else if (x->magnitude == 0.0) {
      return (0);
    }
    else {
      return (-1);
    }
  }
}

DimNumber* DimNumber::add(DimNumber* y) {
  // Computes `x' + `y'
  { DimNumber* x = this;

    if (x->pid->objectEqlP(y->pid)) {
      return (newDimNumber(x->pid, x->magnitude + y->magnitude));
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't add " << "`" << x << "'" << " and " << "`" << y << "'" << " because of incompatible units";
        throw *newIncompatibleUnitsException(stream000->theStringReader());
      }
    }
  }
}

DimNumber* DimNumber::subtract(DimNumber* y) {
  // Computes `x' - `y'
  { DimNumber* x = this;

    if (x->pid->objectEqlP(y->pid)) {
      return (newDimNumber(x->pid, x->magnitude - y->magnitude));
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't subtract " << "`" << y << "'" << " from " << "`" << x << "'" << " because of incompatible units";
        throw *newIncompatibleUnitsException(stream000->theStringReader());
      }
    }
  }
}

DimNumber* DimNumber::multiply(DimNumber* y) {
  // Computes `x' * `y'
  { DimNumber* x = this;

    return (newDimNumber(x->pid->multiply(y->pid), x->magnitude * y->magnitude));
  }
}

DimNumber* DimNumber::divide(DimNumber* y) {
  // Computes `x' / `y'
  { DimNumber* x = this;

    return (newDimNumber(x->pid->divide(y->pid), x->magnitude / y->magnitude));
  }
}

DimNumber* DimNumber::modulus(DimNumber* y) {
  // Computes the modulus of `x' and `y'.  `x' and `y' must be compatible
  // units, and the result has the preferred units of `x'.
  { DimNumber* x = this;

    if (x->pid->objectEqlP(y->pid)) {
      { double quotient = x->magnitude / y->magnitude;

        { DimNumber* self000 = newDimNumber(x->pid, (quotient - stella::floor(quotient)) * y->magnitude);

          self000->preferredUnits = x->preferredUnits;
          { DimNumber* value000 = self000;

            return (value000);
          }
        }
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't perform modulus on " << "`" << x << "'" << " and " << "`" << y << "'" << " because of incompatible units";
        throw *newIncompatibleUnitsException(stream000->theStringReader());
      }
    }
  }
}

DimNumber* DimNumber::negate() {
  // Computes - `x'
  { DimNumber* x = this;

    { DimNumber* self000 = newDimNumber(x->pid, 0 - x->magnitude);

      self000->preferredUnits = x->preferredUnits;
      { DimNumber* value000 = self000;

        return (value000);
      }
    }
  }
}

DimNumber* DimNumber::invert() {
  // Computes  1 / `x'
  { DimNumber* x = this;

    return (newDimNumber(x->pid->invert(), 1 / x->magnitude));
  }
}

DimNumber* DimNumber::absoluteValue() {
  // Computes  abs(`x')
  { DimNumber* x = this;

    if (x->magnitude < 0.0) {
      return (x->negate());
    }
    else {
      return (x);
    }
  }
}

DimNumber* DimNumber::squareRoot() {
  // Computes the positive square root of x, assuming the units are perfect squares
  { DimNumber* x = this;

    { double numeratorRoot = ::sqrt((((double)(x->pid->numerator))));
      int integerNumeratorRoot = stella::floor(numeratorRoot);
      double denominatorRoot = ::sqrt((((double)(x->pid->denominator))));
      int integerDenominatorRoot = stella::floor(denominatorRoot);

      if ((numeratorRoot == ((double)(integerNumeratorRoot))) &&
          (denominatorRoot == ((double)(integerDenominatorRoot)))) {
        return (newDimNumber(makeRatio(integerNumeratorRoot, integerDenominatorRoot), ::sqrt((x->magnitude))));
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Attempt to take square root of " << "`" << x << "'" << "  when the units are not a perfect square";
          throw *newBadArgumentException(stream000->theStringReader());
        }
      }
    }
  }
}

DimNumber* DimNumber::exponentiate(int y) {
  // Computes `x' ^ `y'
  { DimNumber* x = this;

    return (newDimNumber(x->pid->exponentiate(y), ::pow((x->magnitude),(((double)(y))))));
  }
}

boolean DimNumber::lessP(Object* y) {
  // Computes `x' < `y'
  { DimNumber* x = this;

    { DimNumber* yDim = ((DimNumber*)(x->coerceTo(y)));

      if (x->pid->objectEqlP(yDim->pid)) {
        return (x->magnitude < yDim->magnitude);
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Can't compare " << "`" << x << "'" << " and " << "`" << yDim << "'" << " because of incompatible units";
          throw *newIncompatibleUnitsException(stream000->theStringReader());
        }
      }
    }
  }
}

boolean DimNumber::lessEqualP(Object* y) {
  // Computes `x' <= `y'
  { DimNumber* x = this;

    { DimNumber* yDim = ((DimNumber*)(x->coerceTo(y)));

      if (x->pid->objectEqlP(yDim->pid)) {
        return (x->magnitude <= yDim->magnitude);
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Can't compare " << "`" << x << "'" << " and " << "`" << yDim << "'" << " because of incompatible units";
          throw *newIncompatibleUnitsException(stream000->theStringReader());
        }
      }
    }
  }
}

boolean DimNumber::greaterEqualP(Object* y) {
  // Computes `x' >= `y'
  { DimNumber* x = this;

    { DimNumber* yDim = ((DimNumber*)(x->coerceTo(y)));

      if (x->pid->objectEqlP(yDim->pid)) {
        return (x->magnitude >= yDim->magnitude);
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Can't compare " << "`" << x << "'" << " and " << "`" << yDim << "'" << " because of incompatible units";
          throw *newIncompatibleUnitsException(stream000->theStringReader());
        }
      }
    }
  }
}

boolean DimNumber::greaterP(Object* y) {
  // Computes `x' > `y'
  { DimNumber* x = this;

    { DimNumber* yDim = ((DimNumber*)(x->coerceTo(y)));

      if (x->pid->objectEqlP(yDim->pid)) {
        return (x->magnitude > yDim->magnitude);
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Can't compare " << "`" << x << "'" << " and " << "`" << yDim << "'" << " because of incompatible units";
          throw *newIncompatibleUnitsException(stream000->theStringReader());
        }
      }
    }
  }
}

TimeDuration* dimToTimeDuration(DimNumber* timeValue) {
  // Converts the dimensioned number `time-value' to its
  // equivalent value as a `time-duration' object.  If `time-value' is not
  // of the appropriate units, an `incompatible-units-exception' is thrown.
  if (timeValue->signum() == -1) {
    {
      timeValue = timeValue->negate();
      { int days = stella::floor(timeValue->getMagnitude("days"));

        return (makeTimeDuration(0 - days, 0 - stella::floor(timeValue->subtract(makeDimNumber(((double)(days)), "days"))->getMagnitude("ms"))));
      }
    }
  }
  else {
    { int days = stella::floor(timeValue->getMagnitude("days"));

      return (makeTimeDuration(days, stella::floor(timeValue->subtract(makeDimNumber(((double)(days)), "days"))->getMagnitude("ms"))));
    }
  }
}

DimNumber* timeDurationToDim(TimeDuration* duration) {
  // Converts the time duration `duration' to its
  // equivalent value as dimensioned number.  The default time unit
  // will be used.
  return (makeDimNumber(((double)(duration->days)), "days")->add(makeDimNumber(((double)(duration->millis)), "ms")));
}

DimNumber* dmsToDegrees(Cons* l) {
  // Converts a (Degree Minute Second) to decimal degrees.
  { DimNumber* degrees = ((DimNumber*)(l->value));

    { DimNumber* value = NULL;
      Cons* iter000 = l->rest;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        value = ((DimNumber*)(iter000->value));
        degrees = degrees->add(value);
      }
    }
    return (degrees);
  }
}

Cons* degreesToDms(DimNumber* d) {
  // Convert decimal degrees to a list of (Degree Minute Second)
  // where Degree and Minute are integer-valued.
  { int degreeMagnitude = truncate(d->getMagnitude("deg"));
    DimNumber* degreeValue = makeDimNumber(((double)(degreeMagnitude)), "deg");
    int minuteMagnitude = truncate(d->subtract(degreeValue)->getMagnitude("arcmin"));
    DimNumber* minuteValue = makeDimNumber(((double)(minuteMagnitude)), "arcmin");
    int secondMagnitude = truncate(d->subtract(degreeValue)->subtract(minuteValue)->getMagnitude("arcsec"));

    return (consList(3, degreeValue, minuteValue, makeDimNumber(((double)(secondMagnitude)), "arcsec")));
  }
}

DimNumber* hmsToHours(Cons* l) {
  // Converts a (Hour Minute Second) to decimal hours
  { DimNumber* hours = ((DimNumber*)(l->value));

    { DimNumber* value = NULL;
      Cons* iter000 = l->rest;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        value = ((DimNumber*)(iter000->value));
        hours = hours->add(value);
      }
    }
    return (hours);
  }
}

Cons* hoursToHms(DimNumber* d) {
  // Convert decimal hours to a list of (Hour Minute Second)
  // where Hour and Minute are integer-valued.
  { int hourMagnitude = truncate(d->getMagnitude("hr"));
    DimNumber* hourValue = makeDimNumber(((double)(hourMagnitude)), "hr");
    int minuteMagnitude = truncate(d->subtract(hourValue)->getMagnitude("min"));
    DimNumber* minuteValue = makeDimNumber(((double)(minuteMagnitude)), "min");
    int secondMagnitude = truncate(d->subtract(hourValue)->subtract(minuteValue)->getMagnitude("s"));

    return (consList(3, hourValue, minuteValue, makeDimNumber(((double)(secondMagnitude)), "s")));
  }
}

void showMeasures() {
  // Print all defined measures.
  { Measure* m = NULL;
    Cons* iter000 = oALL_MEASURESo;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      m = ((Measure*)(iter000->value));
      std::cout << m->name << "   base-unit=" << m->baseUnit << "   prime-id=" << m->primeId << ((m->baseMeasureP() ? "   BASE" : "   DERIVED")) << std::endl;
    }
  }
}

void showMeasure(const char* measureName) {
  // Print all units and scale factors for measure `measure-name'.
  { Measure* m = lookupMeasure(measureName);

    if (((boolean)(m))) {
      { KeyValueList* theScale = m->scale;

        std::cout << measureName << "   base-unit=" << m->baseUnit << "   prime-id=" << m->primeId << ((m->baseMeasureP() ? "   BASE" : "   DERIVED")) << std::endl;
        { StringWrapper* u = NULL;
          Cons* iter000 = m->getUnits()->theConsList;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            u = ((StringWrapper*)(iter000->value));
            std::cout << "  " << unwrapString(u) << "   factor=" << unwrapFloat(((FloatWrapper*)(theScale->lookup(u)))) << std::endl;
          }
        }
      }
    }
    else {
      std::cout << "No measure with name `" << measureName << "' found." << std::endl;
    }
  }
}

void showMeasureEvaluatorWrapper(Cons* arguments) {
  showMeasure(((StringWrapper*)(arguments->value))->wrapperValue);
}

void helpStartupUnits1() {
  {
    SGT_UNITS_UTILITIES_RATIO = ((Surrogate*)(internRigidSymbolWrtModule("RATIO", NULL, 1)));
    SYM_UNITS_UTILITIES_NUMERATOR = ((Symbol*)(internRigidSymbolWrtModule("NUMERATOR", NULL, 0)));
    SYM_UNITS_UTILITIES_DENOMINATOR = ((Symbol*)(internRigidSymbolWrtModule("DENOMINATOR", NULL, 0)));
    KWD_UNITS_START = ((Keyword*)(internRigidSymbolWrtModule("START", NULL, 2)));
    SYM_UNITS_STELLA_o = ((Symbol*)(internRigidSymbolWrtModule("*", getStellaModule("/STELLA", true), 0)));
    KWD_UNITS_INTEGER = ((Keyword*)(internRigidSymbolWrtModule("INTEGER", NULL, 2)));
    KWD_UNITS_DELIMITER = ((Keyword*)(internRigidSymbolWrtModule("DELIMITER", NULL, 2)));
    KWD_UNITS_FRACTION = ((Keyword*)(internRigidSymbolWrtModule("FRACTION", NULL, 2)));
    KWD_UNITS_UNIT = ((Keyword*)(internRigidSymbolWrtModule("UNIT", NULL, 2)));
    KWD_UNITS_EOF = ((Keyword*)(internRigidSymbolWrtModule("EOF", NULL, 2)));
    KWD_UNITS_OTHERWISE = ((Keyword*)(internRigidSymbolWrtModule("OTHERWISE", NULL, 2)));
    KWD_UNITS_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    KWD_UNITS_INCLUDE = ((Keyword*)(internRigidSymbolWrtModule("INCLUDE", NULL, 2)));
    SGT_UNITS_UTILITIES_MEASURE = ((Surrogate*)(internRigidSymbolWrtModule("MEASURE", NULL, 1)));
    SYM_UNITS_UTILITIES_BASE_UNIT = ((Symbol*)(internRigidSymbolWrtModule("BASE-UNIT", NULL, 0)));
    SYM_UNITS_UTILITIES_SCALE = ((Symbol*)(internRigidSymbolWrtModule("SCALE", NULL, 0)));
    SYM_UNITS_UTILITIES_PRIME_ID = ((Symbol*)(internRigidSymbolWrtModule("PRIME-ID", NULL, 0)));
    SYM_UNITS_STELLA_NAME = ((Symbol*)(internRigidSymbolWrtModule("NAME", getStellaModule("/STELLA", true), 0)));
    KWD_UNITS_PRESERVE = ((Keyword*)(internRigidSymbolWrtModule("PRESERVE", NULL, 2)));
    SGT_UNITS_UTILITIES_DIM_NUMBER = ((Surrogate*)(internRigidSymbolWrtModule("DIM-NUMBER", NULL, 1)));
    SYM_UNITS_UTILITIES_PID = ((Symbol*)(internRigidSymbolWrtModule("PID", NULL, 0)));
    SYM_UNITS_UTILITIES_MAGNITUDE = ((Symbol*)(internRigidSymbolWrtModule("MAGNITUDE", NULL, 0)));
    SYM_UNITS_UTILITIES_PREFERRED_UNITS = ((Symbol*)(internRigidSymbolWrtModule("PREFERRED-UNITS", NULL, 0)));
    KWD_UNITS_DIGIT = ((Keyword*)(internRigidSymbolWrtModule("DIGIT", NULL, 2)));
    SGT_UNITS_STELLA_TIME_DURATION = ((Surrogate*)(internRigidSymbolWrtModule("TIME-DURATION", getStellaModule("/STELLA", true), 1)));
    SYM_UNITS_UTILITIES_STARTUP_UNITS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-UNITS", NULL, 0)));
    SYM_UNITS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupUnits2() {
  {
    oPRIME_NUMBERSo = getQuotedTree("((2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97) \"/UTILITIES\")", "/UTILITIES");
    oPRIME_TO_MEASURE_TABLEo = newStellaHashTable();
    oPRIME_TO_BASE_MEASURE_TABLEo = newIntegerHashTable();
    oNAME_TO_MEASURE_TABLEo = newStringHashTable();
    oUNIT_TO_MEASURE_TABLEo = newStringHashTable();
    oALL_MEASURESo = NIL;
    oBASE_MEASURESo = NIL;
    oRATIO_ONEo = newRatio(1, 1);
    oUNIT_TOKENIZER_TABLE_DEFINITIONo = listO(7, listO(18, KWD_UNITS_START, SYM_UNITS_STELLA_o, wrapString("-+0123456789"), KWD_UNITS_INTEGER, SYM_UNITS_STELLA_o, wrapString("."), KWD_UNITS_DELIMITER, SYM_UNITS_STELLA_o, wrapString("/"), KWD_UNITS_FRACTION, SYM_UNITS_STELLA_o, wrapString("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ%"), KWD_UNITS_UNIT, KWD_UNITS_EOF, KWD_UNITS_EOF, KWD_UNITS_OTHERWISE, KWD_UNITS_ERROR, NIL), listO(17, KWD_UNITS_UNIT, SYM_UNITS_STELLA_o, wrapString("-+0123456789"), KWD_UNITS_INTEGER, SYM_UNITS_STELLA_o, wrapString("."), KWD_UNITS_DELIMITER, SYM_UNITS_STELLA_o, wrapString("/"), KWD_UNITS_FRACTION, wrapString("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ%"), KWD_UNITS_UNIT, KWD_UNITS_EOF, KWD_UNITS_EOF, KWD_UNITS_OTHERWISE, KWD_UNITS_ERROR, NIL), listO(17, KWD_UNITS_INTEGER, wrapString("-+0123456789"), KWD_UNITS_INTEGER, SYM_UNITS_STELLA_o, wrapString("."), KWD_UNITS_DELIMITER, SYM_UNITS_STELLA_o, wrapString("/"), KWD_UNITS_FRACTION, SYM_UNITS_STELLA_o, wrapString("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ%"), KWD_UNITS_UNIT, KWD_UNITS_EOF, KWD_UNITS_EOF, KWD_UNITS_OTHERWISE, KWD_UNITS_ERROR, NIL), listO(4, KWD_UNITS_FRACTION, KWD_UNITS_INCLUDE, KWD_UNITS_START, NIL), listO(4, KWD_UNITS_DELIMITER, KWD_UNITS_INCLUDE, KWD_UNITS_START, NIL), listO(4, KWD_UNITS_ERROR, KWD_UNITS_INCLUDE, KWD_UNITS_START, NIL), NIL);
  }
}

void helpStartupUnits3() {
  {
    defineFunctionObject("NEXT-PRIME-ID", "(DEFUN (NEXT-PRIME-ID INTEGER) () :PUBLIC? FALSE)", ((cpp_function_code)(&nextPrimeId)), NULL);
    defineFunctionObject("MAKE-RATIO", "(DEFUN (MAKE-RATIO RATIO) ((NUM INTEGER) (DENOM INTEGER)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&makeRatio)), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF RATIO)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Ratio::hashCode))), NULL);
    defineMethodObject("(DEFMETHOD (COERCE-TO RATIO) ((X RATIO) (Y OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Coerces `y' to be a compatible type with `x'.\nIf this isn't possible, an exception is thrown.  The exception\nwill be either INCOMPATIBLE-QUANTITY-EXCEPTION or \nINCOMPATIBLE-UNITS-EXCEPTION.\")", wrapMethodCode(((cpp_method_code)(&Ratio::coerceTo))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((X RATIO) (Y OBJECT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Ratio::objectEqlP))), NULL);
    defineMethodObject("(DEFMETHOD (LESS? BOOLEAN) ((X RATIO) (Y OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Computes `x' < `y'\")", wrapMethodCode(((cpp_method_code)(&Ratio::lessP))), NULL);
    defineMethodObject("(DEFMETHOD (LESS-EQUAL? BOOLEAN) ((X RATIO) (Y OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Computes `x' <= `y'\")", wrapMethodCode(((cpp_method_code)(&Ratio::lessEqualP))), NULL);
    defineMethodObject("(DEFMETHOD (GREATER-EQUAL? BOOLEAN) ((X RATIO) (Y OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Computes `x' >= `y'\")", wrapMethodCode(((cpp_method_code)(&Ratio::greaterEqualP))), NULL);
    defineMethodObject("(DEFMETHOD (GREATER? BOOLEAN) ((X RATIO) (Y OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Computes `x' > `y'\")", wrapMethodCode(((cpp_method_code)(&Ratio::greaterP))), NULL);
    defineMethodObject("(DEFMETHOD (ADD RATIO) ((X RATIO) (Y RATIO)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Ratio::add))), NULL);
    defineMethodObject("(DEFMETHOD (SUBTRACT RATIO) ((X RATIO) (Y RATIO)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Ratio::subtract))), NULL);
    defineMethodObject("(DEFMETHOD (MULTIPLY RATIO) ((X RATIO) (Y RATIO)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Ratio::multiply))), NULL);
    defineMethodObject("(DEFMETHOD (DIVIDE RATIO) ((X RATIO) (Y RATIO)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Ratio::divide))), NULL);
    defineMethodObject("(DEFMETHOD (NEGATE RATIO) ((X RATIO)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Ratio::negate))), NULL);
    defineMethodObject("(DEFMETHOD (INVERT RATIO) ((X RATIO)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Ratio::invert))), NULL);
    defineFunctionObject("IPOWER", "(DEFUN (IPOWER INTEGER) ((X INTEGER) (EXP INTEGER)))", ((cpp_function_code)(&ipower)), NULL);
    defineMethodObject("(DEFMETHOD (EXPONENTIATE RATIO) ((X RATIO) (Y INTEGER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Ratio::exponentiate))), NULL);
    defineFunctionObject("RESET-MEASURES", "(DEFUN RESET-MEASURES () :PUBLIC? TRUE)", ((cpp_function_code)(&resetMeasures)), NULL);
    defineMethodObject("(DEFMETHOD SETUP-INDICES ((M MEASURE)))", wrapMethodCode(((cpp_method_code)(&Measure::setupIndices))), NULL);
    defineMethodObject("(DEFMETHOD (BASE-MEASURE? BOOLEAN) ((M MEASURE)) :PUBLIC? TRUE :DOCUMENTATION \"Returns `true' if `m' is a base measure.\")", wrapMethodCode(((cpp_method_code)(&Measure::baseMeasureP))), NULL);
    defineFunctionObject("DEFINE-BASE-MEASURE", "(DEFUN (DEFINE-BASE-MEASURE MEASURE) ((MEASURE-NAME STRING) (MEASURE-BASE-UNIT STRING)) :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&defineBaseMeasure)), NULL);
    defineFunctionObject("DEFINE-DERIVED-MEASURE", "(DEFUN (DEFINE-DERIVED-MEASURE MEASURE) ((MEASURE-NAME STRING) (MEASURE-BASE-UNIT STRING) (DEFINITION STRING)) :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&defineDerivedMeasure)), NULL);
    defineFunctionObject("DEFINE-DIMENSIONLESS-MEASURE", "(DEFUN (DEFINE-DIMENSIONLESS-MEASURE MEASURE) () :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&defineDimensionlessMeasure)), NULL);
    defineMethodObject("(DEFMETHOD ADD-UNIT ((SELF MEASURE) (UNIT-NAME STRING) (SCALE-FACTOR FLOAT) (DEFINITION STRING)))", wrapMethodCode(((cpp_method_code)(&Measure::addUnit))), NULL);
    defineFunctionObject("LOOKUP-MEASURE", "(DEFUN (LOOKUP-MEASURE MEASURE) ((NAME STRING)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&lookupMeasure)), NULL);
    defineFunctionObject("LOOKUP-MEASURE-FOR-UNIT", "(DEFUN (LOOKUP-MEASURE-FOR-UNIT MEASURE) ((UNIT STRING)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&lookupMeasureForUnit)), NULL);
    defineMethodObject("(DEFMETHOD (GET-UNITS (LIST OF STRING-WRAPPER)) ((SELF MEASURE)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Measure::getUnits))), NULL);
    defineFunctionObject("UNIT-TO-SCALE-FACTOR-AND-ID", "(DEFUN (UNIT-TO-SCALE-FACTOR-AND-ID FLOAT RATIO) ((DEFINITION STRING)))", ((cpp_function_code)(&unitToScaleFactorAndId)), NULL);
    defineFunctionObject("COMPUTE-MEASURES-FOR-INTEGER", "(DEFUN (COMPUTE-MEASURES-FOR-INTEGER (CONS OF MEASURE)) ((VALUE INTEGER)))", ((cpp_function_code)(&computeMeasuresForInteger)), NULL);
    defineFunctionObject("COMPUTE-MEASURES-FOR-PRIME-ID", "(DEFUN (COMPUTE-MEASURES-FOR-PRIME-ID (CONS OF MEASURE) (CONS OF MEASURE)) ((PID RATIO)) :PUBLIC? TRUE :DOCUMENTATION \"Returns two CONSes of Measure objects for the prime ID `pid'\")", ((cpp_function_code)(&computeMeasuresForPrimeId)), NULL);
    defineFunctionObject("COMPUTE-UNITS-FOR-INTEGER", "(DEFUN (COMPUTE-UNITS-FOR-INTEGER STRING) ((VALUE INTEGER) (NEGATE-EXPONENT? BOOLEAN)))", ((cpp_function_code)(&computeUnitsForInteger)), NULL);
    defineFunctionObject("COMPUTE-UNITS-FOR-PRIME-ID", "(DEFUN (COMPUTE-UNITS-FOR-PRIME-ID STRING) ((PID RATIO)))", ((cpp_function_code)(&computeUnitsForPrimeId)), NULL);
    defineFunctionObject("MAKE-DIM-NUMBER", "(DEFUN (MAKE-DIM-NUMBER DIM-NUMBER) ((MAGNITUDE FLOAT) (UNITS STRING)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&makeDimNumber)), NULL);
    defineFunctionObject("PARSE-DIM-NUMBER", "(DEFUN (PARSE-DIM-NUMBER DIM-NUMBER) ((INPUT STRING)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&parseDimNumber)), NULL);
    defineMethodObject("(DEFMETHOD (COERCE-TO DIM-NUMBER) ((X DIM-NUMBER) (Y OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Coerces `y' to be a compatible type with `x'.\nIf this isn't possible, an exception is thrown.  The exception\nwill be either INCOMPATIBLE-QUANTITY-EXCEPTION or \nINCOMPATIBLE-UNITS-EXCEPTION.\")", wrapMethodCode(((cpp_method_code)(&DimNumber::coerceTo))), NULL);
    defineMethodObject("(DEFMETHOD (GET-MAGNITUDE FLOAT) ((SELF DIM-NUMBER) (UNITS STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the magnitude of the dim number in the given units.\")", wrapMethodCode(((cpp_method_code)(&DimNumber::getMagnitude))), NULL);
    defineMethodObject("(DEFMETHOD (GET-UNIT STRING) ((SELF DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the units for the dim number.  This will return the\npreferred output units if they exist, otherwise the base units. (see `get-base-unit')\")", wrapMethodCode(((cpp_method_code)(&DimNumber::getUnit))), NULL);
    defineMethodObject("(DEFMETHOD (GET-BASE-UNIT STRING) ((SELF DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the base units for the dim number.\")", wrapMethodCode(((cpp_method_code)(&DimNumber::getBaseUnit))), NULL);
    defineMethodObject("(DEFMETHOD (GET-MEASURE MEASURE) ((SELF DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the measure for the dim number, if one is defined.\")", wrapMethodCode(((cpp_method_code)(&DimNumber::getMeasure))), NULL);
    defineMethodObject("(DEFMETHOD (GET-BASE-MEASURES (CONS OF MEASURE) (CONS OF MEASURE)) ((SELF DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Returns cons of the base measures for the numerator and denominator\nof `self'.\")", wrapMethodCode(((cpp_method_code)(&DimNumber::getBaseMeasures))), NULL);
    defineMethodObject("(DEFMETHOD (FORMAT-DIM-NUMBER STRING) ((X DIM-NUMBER) (UNITS STRING) (DECIMALS INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Returns a string representation of `x' in `units' with `decimals' digits.\")", wrapMethodCode(((cpp_method_code)(&DimNumber::formatDimNumber))), NULL);
    defineFunctionObject("COMPATIBLE-UNITS?", "(DEFUN (COMPATIBLE-UNITS? BOOLEAN) ((X DIM-NUMBER) (Y DIM-NUMBER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Returns TRUE if the units of `x' and `y' are compatible.\" (RETURN (OBJECT-EQL? (PID X) (PID Y))))", ((cpp_function_code)(&compatibleUnitsP)), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((X DIM-NUMBER) (Y OBJECT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&DimNumber::objectEqlP))), NULL);
    defineMethodObject("(DEFMETHOD (HASH-CODE INTEGER) ((SELF DIM-NUMBER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&DimNumber::hashCode))), NULL);
    defineMethodObject("(DEFMETHOD (SIGNUM INTEGER) ((X DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Computes the signum of `x':  -1 if negative, 0 if zero, 1 if positive\")", wrapMethodCode(((cpp_method_code)(&DimNumber::signum))), NULL);
    defineMethodObject("(DEFMETHOD (ADD DIM-NUMBER) ((X DIM-NUMBER) (Y DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Computes `x' + `y'\")", wrapMethodCode(((cpp_method_code)(&DimNumber::add))), NULL);
    defineMethodObject("(DEFMETHOD (SUBTRACT DIM-NUMBER) ((X DIM-NUMBER) (Y DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Computes `x' - `y'\")", wrapMethodCode(((cpp_method_code)(&DimNumber::subtract))), NULL);
    defineMethodObject("(DEFMETHOD (MULTIPLY DIM-NUMBER) ((X DIM-NUMBER) (Y DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Computes `x' * `y'\")", wrapMethodCode(((cpp_method_code)(&DimNumber::multiply))), NULL);
    defineMethodObject("(DEFMETHOD (DIVIDE DIM-NUMBER) ((X DIM-NUMBER) (Y DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Computes `x' / `y'\")", wrapMethodCode(((cpp_method_code)(&DimNumber::divide))), NULL);
    defineMethodObject("(DEFMETHOD (MODULUS DIM-NUMBER) ((X DIM-NUMBER) (Y DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Computes the modulus of `x' and `y'.  `x' and `y' must be compatible\nunits, and the result has the preferred units of `x'.\")", wrapMethodCode(((cpp_method_code)(&DimNumber::modulus))), NULL);
    defineMethodObject("(DEFMETHOD (NEGATE DIM-NUMBER) ((X DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Computes - `x'\")", wrapMethodCode(((cpp_method_code)(&DimNumber::negate))), NULL);
    defineMethodObject("(DEFMETHOD (INVERT DIM-NUMBER) ((X DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Computes  1 / `x'\")", wrapMethodCode(((cpp_method_code)(&DimNumber::invert))), NULL);
    defineMethodObject("(DEFMETHOD (ABSOLUTE-VALUE DIM-NUMBER) ((X DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Computes  abs(`x')\")", wrapMethodCode(((cpp_method_code)(&DimNumber::absoluteValue))), NULL);
    defineMethodObject("(DEFMETHOD (SQUARE-ROOT DIM-NUMBER) ((X DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Computes the positive square root of x, assuming the units are perfect squares\")", wrapMethodCode(((cpp_method_code)(&DimNumber::squareRoot))), NULL);
    defineMethodObject("(DEFMETHOD (EXPONENTIATE DIM-NUMBER) ((X DIM-NUMBER) (Y INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Computes `x' ^ `y'\")", wrapMethodCode(((cpp_method_code)(&DimNumber::exponentiate))), NULL);
    defineMethodObject("(DEFMETHOD (LESS? BOOLEAN) ((X DIM-NUMBER) (Y OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Computes `x' < `y'\")", wrapMethodCode(((cpp_method_code)(&DimNumber::lessP))), NULL);
    defineMethodObject("(DEFMETHOD (LESS-EQUAL? BOOLEAN) ((X DIM-NUMBER) (Y OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Computes `x' <= `y'\")", wrapMethodCode(((cpp_method_code)(&DimNumber::lessEqualP))), NULL);
    defineMethodObject("(DEFMETHOD (GREATER-EQUAL? BOOLEAN) ((X DIM-NUMBER) (Y OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Computes `x' >= `y'\")", wrapMethodCode(((cpp_method_code)(&DimNumber::greaterEqualP))), NULL);
    defineMethodObject("(DEFMETHOD (GREATER? BOOLEAN) ((X DIM-NUMBER) (Y OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Computes `x' > `y'\")", wrapMethodCode(((cpp_method_code)(&DimNumber::greaterP))), NULL);
    defineFunctionObject("DIM-TO-TIME-DURATION", "(DEFUN (DIM-TO-TIME-DURATION TIME-DURATION) ((TIME-VALUE DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Converts the dimensioned number `time-value' to its\nequivalent value as a `time-duration' object.  If `time-value' is not\nof the appropriate units, an `incompatible-units-exception' is thrown.\")", ((cpp_function_code)(&dimToTimeDuration)), NULL);
  }
}

void startupUnits() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/UTILITIES", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupUnits1();
    }
    if (currentStartupTimePhaseP(4)) {
      helpStartupUnits2();
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("INCOMPATIBLE-UNITS-EXCEPTION", "(DEFCLASS INCOMPATIBLE-UNITS-EXCEPTION (INCOMPATIBLE-QUANTITY-EXCEPTION) :PUBLIC? TRUE)");

        clasS->classConstructorCode = ((cpp_function_code)(&newIncompatibleUnitsException));
      }
      { Class* clasS = defineClassFromStringifiedSource("RATIO", "(DEFCLASS RATIO (QUANTITY) :PUBLIC? TRUE :PUBLIC-SLOTS ((NUMERATOR :TYPE INTEGER :REQUIRED? TRUE) (DENOMINATOR :TYPE INTEGER :REQUIRED? TRUE)) :PRINT-FORM (PRINT-STREAM STREAM (NUMERATOR SELF) \"/\" (DENOMINATOR SELF)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newRatio));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessRatioSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("MEASURE", "(DEFCLASS MEASURE (STANDARD-OBJECT) :PUBLIC? TRUE :PUBLIC-SLOTS ((BASE-UNIT :TYPE STRING) (SCALE :TYPE (KEY-VALUE-LIST OF STRING-WRAPPER FLOAT-WRAPPER) :INITIALLY (NEW KEY-VALUE-LIST)) (PRIME-ID :TYPE RATIO) (NAME :TYPE STRING)) :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"<Measure \" (NAME SELF) \"(\" (BASE-UNIT SELF) \")>\"))");

        clasS->classConstructorCode = ((cpp_function_code)(&newMeasure));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessMeasureSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("DIM-NUMBER", "(DEFCLASS DIM-NUMBER (QUANTITY) :PUBLIC? TRUE :PUBLIC-SLOTS ((PID :TYPE RATIO :REQUIRED? TRUE) (MAGNITUDE :TYPE FLOAT :REQUIRED? TRUE) (PREFERRED-UNITS :TYPE STRING :INITIALLY NULL)) :PRINT-FORM (PRINT-STREAM STREAM \"<\" (GET-MAGNITUDE SELF (GET-UNIT SELF)) (GET-UNIT SELF) \">\"))");

        clasS->classConstructorCode = ((cpp_function_code)(&newDimNumber));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessDimNumberSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupUnits3();
      defineFunctionObject("TIME-DURATION-TO-DIM", "(DEFUN (TIME-DURATION-TO-DIM DIM-NUMBER) ((DURATION TIME-DURATION)) :PUBLIC? TRUE :DOCUMENTATION \"Converts the time duration `duration' to its\nequivalent value as dimensioned number.  The default time unit\nwill be used.\")", ((cpp_function_code)(&timeDurationToDim)), NULL);
      defineFunctionObject("DMS-TO-DEGREES", "(DEFUN (DMS-TO-DEGREES DIM-NUMBER) ((L (CONS OF DIM-NUMBER))) :PUBLIC? TRUE :DOCUMENTATION \"Converts a (Degree Minute Second) to decimal degrees.\")", ((cpp_function_code)(&dmsToDegrees)), NULL);
      defineFunctionObject("DEGREES-TO-DMS", "(DEFUN (DEGREES-TO-DMS (CONS OF DIM-NUMBER)) ((D DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Convert decimal degrees to a list of (Degree Minute Second)\nwhere Degree and Minute are integer-valued.\")", ((cpp_function_code)(&degreesToDms)), NULL);
      defineFunctionObject("HMS-TO-HOURS", "(DEFUN (HMS-TO-HOURS DIM-NUMBER) ((L (CONS OF DIM-NUMBER))) :PUBLIC? TRUE :DOCUMENTATION \"Converts a (Hour Minute Second) to decimal hours\")", ((cpp_function_code)(&hmsToHours)), NULL);
      defineFunctionObject("HOURS-TO-HMS", "(DEFUN (HOURS-TO-HMS (CONS OF DIM-NUMBER)) ((D DIM-NUMBER)) :PUBLIC? TRUE :DOCUMENTATION \"Convert decimal hours to a list of (Hour Minute Second)\nwhere Hour and Minute are integer-valued.\")", ((cpp_function_code)(&hoursToHms)), NULL);
      defineFunctionObject("SHOW-MEASURES", "(DEFUN SHOW-MEASURES () :PUBLIC? TRUE :COMMAND? TRUE :DOCUMENTATION \"Print all defined measures.\")", ((cpp_function_code)(&showMeasures)), NULL);
      defineFunctionObject("SHOW-MEASURE", "(DEFUN SHOW-MEASURE ((MEASURE-NAME STRING)) :PUBLIC? TRUE :COMMAND? TRUE :DOCUMENTATION \"Print all units and scale factors for measure `measure-name'.\")", ((cpp_function_code)(&showMeasure)), ((cpp_function_code)(&showMeasureEvaluatorWrapper)));
      defineFunctionObject("STARTUP-UNITS", "(DEFUN STARTUP-UNITS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupUnits)), NULL);
      { MethodSlot* function = lookupFunction(SYM_UNITS_UTILITIES_STARTUP_UNITS);

        setDynamicSlotValue(function->dynamicSlots, SYM_UNITS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupUnits"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("UTILITIES")))));
      defineGlobalVariableObject("(DEFGLOBAL *PRIME-NUMBERS* (CONS OF INTEGER-WRAPPER) (QUOTE (2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97)) :PUBLIC? FALSE)", &oPRIME_NUMBERSo);
      defineGlobalVariableObject("(DEFGLOBAL *CURRENT-PRIME-INDEX* INTEGER -1 :PUBLIC? FALSE)", &oCURRENT_PRIME_INDEXo);
      defineGlobalVariableObject("(DEFGLOBAL *PRIME-TO-MEASURE-TABLE* (STELLA-HASH-TABLE OF RATIO MEASURE) (NEW STELLA-HASH-TABLE) :PUBLIC? FALSE)", &oPRIME_TO_MEASURE_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *PRIME-TO-BASE-MEASURE-TABLE* (INTEGER-HASH-TABLE OF INTEGER MEASURE) (NEW INTEGER-HASH-TABLE) :PUBLIC? FALSE)", &oPRIME_TO_BASE_MEASURE_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *NAME-TO-MEASURE-TABLE* (STRING-HASH-TABLE OF STRING MEASURE) (NEW STRING-HASH-TABLE) :PUBLIC? FALSE)", &oNAME_TO_MEASURE_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *UNIT-TO-MEASURE-TABLE* (STRING-HASH-TABLE OF STRING MEASURE) (NEW STRING-HASH-TABLE) :PUBLIC? FALSE)", &oUNIT_TO_MEASURE_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *ALL-MEASURES* (CONS OF MEASURE) NIL :PUBLIC? TRUE)", &oALL_MEASURESo);
      defineGlobalVariableObject("(DEFGLOBAL *BASE-MEASURES* (CONS OF MEASURE) NIL :PUBLIC? TRUE)", &oBASE_MEASURESo);
      defineGlobalVariableObject("(DEFGLOBAL *RATIO-ONE* RATIO (NEW RATIO :NUMERATOR 1 :DENOMINATOR 1) :PUBLIC? TRUE)", &oRATIO_ONEo);
      defineGlobalVariableObject("(DEFGLOBAL *UNIT-TOKENIZER-TABLE-DEFINITION* CONS (BQUOTE ((:START * \"-+0123456789\" :INTEGER * \".\" :DELIMITER * \"/\" :FRACTION * \"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ%\" :UNIT :EOF :EOF :OTHERWISE :ERROR) (:UNIT * \"-+0123456789\" :INTEGER * \".\" :DELIMITER * \"/\" :FRACTION \"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ%\" :UNIT :EOF :EOF :OTHERWISE :ERROR) (:INTEGER \"-+0123456789\" :INTEGER * \".\" :DELIMITER * \"/\" :FRACTION * \"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ%\" :UNIT :EOF :EOF :OTHERWISE :ERROR) (:FRACTION :INCLUDE :START) (:DELIMITER :INCLUDE :START) (:ERROR :INCLUDE :START))))", &oUNIT_TOKENIZER_TABLE_DEFINITIONo);
      defineGlobalVariableObject("(DEFGLOBAL *UNIT-TOKENIZER-TABLE* TOKENIZER-TABLE NULL)", &oUNIT_TOKENIZER_TABLEo);
      oUNIT_TOKENIZER_TABLEo = parseTokenizerDefinition(oUNIT_TOKENIZER_TABLE_DEFINITIONo);
      resetMeasures();
      initializeUnitDefinitions();
    }
  }
}

Surrogate* SGT_UNITS_UTILITIES_RATIO = NULL;

Symbol* SYM_UNITS_UTILITIES_NUMERATOR = NULL;

Symbol* SYM_UNITS_UTILITIES_DENOMINATOR = NULL;

Keyword* KWD_UNITS_START = NULL;

Symbol* SYM_UNITS_STELLA_o = NULL;

Keyword* KWD_UNITS_INTEGER = NULL;

Keyword* KWD_UNITS_DELIMITER = NULL;

Keyword* KWD_UNITS_FRACTION = NULL;

Keyword* KWD_UNITS_UNIT = NULL;

Keyword* KWD_UNITS_EOF = NULL;

Keyword* KWD_UNITS_OTHERWISE = NULL;

Keyword* KWD_UNITS_ERROR = NULL;

Keyword* KWD_UNITS_INCLUDE = NULL;

Surrogate* SGT_UNITS_UTILITIES_MEASURE = NULL;

Symbol* SYM_UNITS_UTILITIES_BASE_UNIT = NULL;

Symbol* SYM_UNITS_UTILITIES_SCALE = NULL;

Symbol* SYM_UNITS_UTILITIES_PRIME_ID = NULL;

Symbol* SYM_UNITS_STELLA_NAME = NULL;

Keyword* KWD_UNITS_PRESERVE = NULL;

Surrogate* SGT_UNITS_UTILITIES_DIM_NUMBER = NULL;

Symbol* SYM_UNITS_UTILITIES_PID = NULL;

Symbol* SYM_UNITS_UTILITIES_MAGNITUDE = NULL;

Symbol* SYM_UNITS_UTILITIES_PREFERRED_UNITS = NULL;

Keyword* KWD_UNITS_DIGIT = NULL;

Surrogate* SGT_UNITS_STELLA_TIME_DURATION = NULL;

Symbol* SYM_UNITS_UTILITIES_STARTUP_UNITS = NULL;

Symbol* SYM_UNITS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella_utilities
