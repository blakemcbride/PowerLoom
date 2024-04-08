//  -*- Mode: C++ -*-

// units.hh

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


namespace stella_utilities {
  using namespace stella;

// Class definitions:
class IncompatibleUnitsException : public IncompatibleQuantityException {
public:
  IncompatibleUnitsException(const std::string& msg) : IncompatibleQuantityException(msg) {
}

};

class Ratio : public Quantity {
public:
  int numerator;
  int denominator;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
  virtual Ratio* exponentiate(int y);
  virtual Ratio* invert();
  virtual Ratio* negate();
  virtual Ratio* divide(Ratio* y);
  virtual Ratio* multiply(Ratio* y);
  virtual Ratio* subtract(Ratio* y);
  virtual Ratio* add(Ratio* y);
  virtual boolean greaterP(Object* y);
  virtual boolean greaterEqualP(Object* y);
  virtual boolean lessEqualP(Object* y);
  virtual boolean lessP(Object* y);
  virtual boolean objectEqlP(Object* y);
  virtual Quantity* coerceTo(Object* y);
  virtual int hashCode();
};

class Measure : public StandardObject {
public:
  const char* baseUnit;
  KeyValueList* scale;
  Ratio* primeId;
  const char* name;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
  virtual List* getUnits();
  virtual void addUnit(const char* unitName, double scaleFactor, const char* definition);
  virtual boolean baseMeasureP();
  virtual void setupIndices();
};

class DimNumber : public Quantity {
public:
  Ratio* pid;
  double magnitude;
  const char* preferredUnits;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
  virtual boolean greaterP(Object* y);
  virtual boolean greaterEqualP(Object* y);
  virtual boolean lessEqualP(Object* y);
  virtual boolean lessP(Object* y);
  virtual DimNumber* exponentiate(int y);
  virtual DimNumber* squareRoot();
  virtual DimNumber* absoluteValue();
  virtual DimNumber* invert();
  virtual DimNumber* negate();
  virtual DimNumber* modulus(DimNumber* y);
  virtual DimNumber* divide(DimNumber* y);
  virtual DimNumber* multiply(DimNumber* y);
  virtual DimNumber* subtract(DimNumber* y);
  virtual DimNumber* add(DimNumber* y);
  virtual int signum();
  virtual int hashCode();
  virtual boolean objectEqlP(Object* y);
  virtual const char* formatDimNumber(const char* units, int decimals);
  virtual Cons* getBaseMeasures(Cons*& _Return1);
  virtual Measure* getMeasure();
  virtual const char* getBaseUnit();
  virtual const char* getUnit();
  virtual double getMagnitude(const char* units);
  virtual Quantity* coerceTo(Object* y);
};


// Global declarations:
extern Cons* oPRIME_NUMBERSo;
extern int oCURRENT_PRIME_INDEXo;
extern StellaHashTable* oPRIME_TO_MEASURE_TABLEo;
extern IntegerHashTable* oPRIME_TO_BASE_MEASURE_TABLEo;
extern StringHashTable* oNAME_TO_MEASURE_TABLEo;
extern StringHashTable* oUNIT_TO_MEASURE_TABLEo;
extern Cons* oALL_MEASURESo;
extern Cons* oBASE_MEASURESo;
extern Ratio* oRATIO_ONEo;
extern Cons* oUNIT_TOKENIZER_TABLE_DEFINITIONo;
extern TokenizerTable* oUNIT_TOKENIZER_TABLEo;

// Function signatures:
int nextPrimeId();
IncompatibleUnitsException* newIncompatibleUnitsException(const char* message);
Ratio* newRatio(int numerator, int denominator);
Object* accessRatioSlotValue(Ratio* self, Symbol* slotname, Object* value, boolean setvalueP);
Ratio* makeRatio(int num, int denom);
int ipower(int x, int exp);
Measure* newMeasure();
Object* accessMeasureSlotValue(Measure* self, Symbol* slotname, Object* value, boolean setvalueP);
void resetMeasures();
Measure* defineBaseMeasure(const char* measureName, const char* measureBaseUnit);
Measure* defineDerivedMeasure(const char* measureName, const char* measureBaseUnit, const char* definition);
Measure* defineDimensionlessMeasure();
Measure* lookupMeasure(const char* name);
Measure* lookupMeasureForUnit(const char* unit);
double unitToScaleFactorAndId(const char* definition, Ratio*& _Return1);
Cons* computeMeasuresForInteger(int value);
Cons* computeMeasuresForPrimeId(Ratio* pid, Cons*& _Return1);
const char* computeUnitsForInteger(int value, boolean negateExponentP);
const char* computeUnitsForPrimeId(Ratio* pid);
DimNumber* newDimNumber(Ratio* pid, double magnitude);
Object* accessDimNumberSlotValue(DimNumber* self, Symbol* slotname, Object* value, boolean setvalueP);
DimNumber* makeDimNumber(double magnitude, const char* units);
DimNumber* parseDimNumber(const char* input);
boolean compatibleUnitsP(DimNumber* x, DimNumber* y);
TimeDuration* dimToTimeDuration(DimNumber* timeValue);
DimNumber* timeDurationToDim(TimeDuration* duration);
DimNumber* dmsToDegrees(Cons* l);
Cons* degreesToDms(DimNumber* d);
DimNumber* hmsToHours(Cons* l);
Cons* hoursToHms(DimNumber* d);
void showMeasures();
void showMeasure(const char* measureName);
void showMeasureEvaluatorWrapper(Cons* arguments);
void helpStartupUnits1();
void helpStartupUnits2();
void helpStartupUnits3();
void startupUnits();

// Auxiliary global declarations:
extern Surrogate* SGT_UNITS_UTILITIES_RATIO;
extern Symbol* SYM_UNITS_UTILITIES_NUMERATOR;
extern Symbol* SYM_UNITS_UTILITIES_DENOMINATOR;
extern Keyword* KWD_UNITS_START;
extern Symbol* SYM_UNITS_STELLA_o;
extern Keyword* KWD_UNITS_INTEGER;
extern Keyword* KWD_UNITS_DELIMITER;
extern Keyword* KWD_UNITS_FRACTION;
extern Keyword* KWD_UNITS_UNIT;
extern Keyword* KWD_UNITS_EOF;
extern Keyword* KWD_UNITS_OTHERWISE;
extern Keyword* KWD_UNITS_ERROR;
extern Keyword* KWD_UNITS_INCLUDE;
extern Surrogate* SGT_UNITS_UTILITIES_MEASURE;
extern Symbol* SYM_UNITS_UTILITIES_BASE_UNIT;
extern Symbol* SYM_UNITS_UTILITIES_SCALE;
extern Symbol* SYM_UNITS_UTILITIES_PRIME_ID;
extern Symbol* SYM_UNITS_STELLA_NAME;
extern Keyword* KWD_UNITS_PRESERVE;
extern Surrogate* SGT_UNITS_UTILITIES_DIM_NUMBER;
extern Symbol* SYM_UNITS_UTILITIES_PID;
extern Symbol* SYM_UNITS_UTILITIES_MAGNITUDE;
extern Symbol* SYM_UNITS_UTILITIES_PREFERRED_UNITS;
extern Keyword* KWD_UNITS_DIGIT;
extern Surrogate* SGT_UNITS_STELLA_TIME_DURATION;
extern Symbol* SYM_UNITS_UTILITIES_STARTUP_UNITS;
extern Symbol* SYM_UNITS_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella_utilities
