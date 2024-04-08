//  -*- Mode: C++ -*-

// unit-support.hh

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


namespace units {
  using namespace stella_utilities;
  using namespace stella;
  using namespace logic;

// Class definitions:
class DimNumberLogicWrapper : public QuantityLogicWrapper {
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
  virtual double getMagnitude(const char* units);
  virtual const char* getBaseUnit();
  virtual const char* getUnit();
  virtual boolean objectEqlP(Object* x);
  virtual int hashCode();
  virtual Object* generateSpecializedTerm();
};


// Global declarations:
extern StellaHashTable* oDIM_NUMBER_HASH_TABLEo;
extern HashTable* oMEASURE_INSTANCE_TABLEo;
extern HashTable* oINSTANCE_MEASURE_TABLEo;

// Function signatures:
DimNumberLogicWrapper* newDimNumberLogicWrapper(DimNumber* wrapperValue);
Object* accessDimNumberLogicWrapperSlotValue(DimNumberLogicWrapper* self, Symbol* slotname, Object* value, boolean setvalueP);
DimNumberLogicWrapper* wrapDimNumber(DimNumber* value);
DimNumberLogicWrapper* helpGetDimNumber(Object* item);
DimNumberLogicWrapper* helpGetUnitValue(Object* magnitude, Object* units);
void unitsEvaluator(Proposition* self);
Keyword* unitsSpecialist(ControlFrame* frame, Keyword* lastmove);
Object* uPlusConstraint(IntegerWrapper* missingArgument, DimNumberLogicWrapper* x1, DimNumberLogicWrapper* x2, DimNumberLogicWrapper* x3);
Object* uMinusConstraint(IntegerWrapper* missingArgument, DimNumberLogicWrapper* x1, DimNumberLogicWrapper* x2, DimNumberLogicWrapper* x3);
Object* uTimesConstraint(IntegerWrapper* missingArgument, DimNumberLogicWrapper* x1, DimNumberLogicWrapper* x2, DimNumberLogicWrapper* x3);
Object* uDivideConstraint(IntegerWrapper* missingArgument, DimNumberLogicWrapper* x1, DimNumberLogicWrapper* x2, DimNumberLogicWrapper* x3);
Keyword* uAbsSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* uSignumSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* minimumOfUnitsSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* maximumOfUnitsSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* sumOfUnitsSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* uValueMeasureSpecialist(ControlFrame* frame, Keyword* lastmove);
boolean argumentMatchesListHelperP(Object* argument, List* theList);
Keyword* integerToMeasuresHelper(ControlFrame* frame, Keyword* lastmove, int code);
Keyword* uBaseMeasuresSpecialist(ControlFrame* frame, Keyword* lastmove);
Ratio* getObjectPid(Object* obj);
Keyword* comensurateUnitsSpecialist(ControlFrame* frame, Keyword* lastmove);
void initializeMeasureConcepts();
void startupUnitSupport();

// Auxiliary global declarations:
extern Surrogate* SGT_UNIT_SUPPORT_UNIT_SUPPORT_DIM_NUMBER_LOGIC_WRAPPER;
extern Surrogate* SGT_UNIT_SUPPORT_UNIT_KB_UNITS;
extern Surrogate* SGT_UNIT_SUPPORT_TIMEPOINT_SUPPORT_DATE_TIME_LOGIC_WRAPPER;
extern Surrogate* SGT_UNIT_SUPPORT_STELLA_CALENDAR_DATE;
extern Surrogate* SGT_UNIT_SUPPORT_STELLA_TIME_DURATION;
extern Surrogate* SGT_UNIT_SUPPORT_LOGIC_PATTERN_VARIABLE;
extern Surrogate* SGT_UNIT_SUPPORT_LOGIC_SKOLEM;
extern Surrogate* SGT_UNIT_SUPPORT_STELLA_CS_VALUE;
extern Keyword* KWD_UNIT_SUPPORT_FINAL_SUCCESS;
extern Keyword* KWD_UNIT_SUPPORT_TERMINAL_FAILURE;
extern Keyword* KWD_UNIT_SUPPORT_FAILURE;
extern Symbol* SYM_UNIT_SUPPORT_STELLA_ITERATOR;
extern Keyword* KWD_UNIT_SUPPORT_CONTINUING_SUCCESS;
extern Surrogate* SGT_UNIT_SUPPORT_STELLA_INTEGER_WRAPPER;
extern Surrogate* SGT_UNIT_SUPPORT_UNIT_KB_NUMERATOR_MEASURES;
extern Surrogate* SGT_UNIT_SUPPORT_UNIT_KB_DENOMINATOR_MEASURES;
extern Surrogate* SGT_UNIT_SUPPORT_LOGIC_LOGIC_OBJECT;
extern Surrogate* SGT_UNIT_SUPPORT_STELLA_NUMBER_WRAPPER;
extern Symbol* SYM_UNIT_SUPPORT_UNIT_SUPPORT_STARTUP_UNIT_SUPPORT;
extern Symbol* SYM_UNIT_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace units
