//  -*- Mode: C++ -*-

// arithmetic.hh

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


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

// Class definitions:
class IntegerInterval : public Thing {
// An interval of integers
public:
  int intervalLowerBound;
  int intervalUpperBound;
public:
  virtual Surrogate* primaryType();
};

class IntervalCache : public Thing {
public:
  Context* homeContext;
  LogicObject* intervalMember;
  Object* lowerBound;
  Object* upperBound;
  boolean strictLowerBoundP;
  boolean strictUpperBoundP;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
  virtual void propagateInequalityToIntervalCache(Object* value, Surrogate* operatoR);
  virtual void evaluateTighterInterval();
  virtual void evaluateTighterIntegerInterval();
  virtual IntegerWrapper* integerUpperBound();
  virtual IntegerWrapper* integerLowerBound();
  virtual boolean integerValuedMemberP();
};



// Function signatures:
boolean arithmeticEqualTest(NumberWrapper* x, NumberWrapper* y);
boolean arithmeticLessTest(NumberWrapper* x, NumberWrapper* y);
boolean arithmeticGreaterTest(NumberWrapper* x, NumberWrapper* y);
NumberWrapper* plusComputation(NumberWrapper* x, NumberWrapper* y);
NumberWrapper* minusComputation(NumberWrapper* x, NumberWrapper* y);
NumberWrapper* timesComputation(NumberWrapper* x, NumberWrapper* y);
NumberWrapper* divideComputation(NumberWrapper* x, NumberWrapper* y);
NumberWrapper* sqrtComputation(NumberWrapper* x);
NumberWrapper* negateComputation(NumberWrapper* x);
NumberWrapper* absComputation(NumberWrapper* x);
IntegerWrapper* floorComputation(NumberWrapper* x);
IntegerWrapper* ceilingComputation(NumberWrapper* x);
Object* plusConstraint(IntegerWrapper* missingArgument, NumberWrapper* x1, NumberWrapper* x2, NumberWrapper* x3);
Object* minusConstraint(IntegerWrapper* missingArgument, NumberWrapper* x1, NumberWrapper* x2, NumberWrapper* x3);
Object* timesConstraint(IntegerWrapper* missingArgument, NumberWrapper* x1, NumberWrapper* x2, NumberWrapper* x3);
Object* divideConstraint(IntegerWrapper* missingArgument, NumberWrapper* x1, NumberWrapper* x2, NumberWrapper* x3);
Object* negateConstraint(IntegerWrapper* missingArgument, NumberWrapper* x1, NumberWrapper* x2);
Object* sqrtConstraint(IntegerWrapper* missingArgument, NumberWrapper* x1, NumberWrapper* x2);
FloatWrapper* logComputation(NumberWrapper* x);
FloatWrapper* log10Computation(NumberWrapper* x);
FloatWrapper* expComputation(NumberWrapper* x);
FloatWrapper* exptComputation(NumberWrapper* x, NumberWrapper* n);
Object* logConstraint(IntegerWrapper* missingArgument, NumberWrapper* x, NumberWrapper* log);
Object* log10Constraint(IntegerWrapper* missingArgument, NumberWrapper* x, NumberWrapper* log);
Object* expConstraint(IntegerWrapper* missingArgument, NumberWrapper* x, NumberWrapper* y);
IntegerInterval* newIntegerInterval();
Object* accessIntegerIntervalSlotValue(IntegerInterval* self, Symbol* slotname, Object* value, boolean setvalueP);
IntervalCache* newIntervalCache();
Object* accessIntervalCacheSlotValue(IntervalCache* self, Symbol* slotname, Object* value, boolean setvalueP);
void printInterval(std::ostream* stream, Object* lower, boolean strictLowerP, Object* upper, boolean strictUpperP);
IntervalCache* createIntervalCache(LogicObject* intervalmember);
IntervalCache* getIntervalCache(LogicObject* self);
void signalIntervalClash(IntervalCache* interval);
void evaluateAdjacentInequalities(LogicObject* self);
Surrogate* inverseInequalityOperator(Surrogate* operatoR);
void unifyIntervalCaches(IntervalCache* cache1, IntervalCache* cache2, Surrogate* operatoR);
Object* accessIntervalBounds(Object* x, Keyword* lowerorupper, boolean& _Return1);
Object* accessIntervalCacheBounds(IntervalCache* intervalcache, Keyword* lowerorupper, boolean& _Return1);
boolean compareIntervalBoundsP(Surrogate* relation, Object* x, Object* y);
boolean nullNumberP(NumberWrapper* self);
boolean nullLiteralWrapperP(Object* self);
boolean satisfiesIntervalBoundsP(Object* object, Object* value);
Keyword* lessSpecialistHelper(ControlFrame* frame, Surrogate* relation, Object* xarg, Object* yarg);
Keyword* inequalitySpecialist(ControlFrame* frame, Keyword* lastmove);
void inequalityEvaluator(Proposition* self);
StringWrapper* stringConcatenateComputation(Object* x, Cons* yargs);
Keyword* subsequenceSpecialist(ControlFrame* frame, Keyword* lastmove);
const char* normalizeStringComputationArgs(Object* x, Object* start, Object* end, boolean coerceP, int& _Return1, int& _Return2);
IntegerWrapper* stringMatchComputationHelper(Object* pattern, Object* x, Object* start, Object* end, boolean ignoreCaseP);
IntegerWrapper* stringMatchComputation(Object* pattern, Object* x, Object* start, Object* end);
IntegerWrapper* stringMatchIgnoreCaseComputation(Object* pattern, Object* x, Object* start, Object* end);
StringWrapper* stringUpcaseComputation(Object* x, Object* start, Object* end);
StringWrapper* stringDowncaseComputation(Object* x, Object* start, Object* end);
StringWrapper* stringCapitalizeComputation(Object* x, Object* start, Object* end);
StringWrapper* stringReplaceComputation(Object* x, Object* from, Object* to, Object* start, Object* end);
IntegerWrapper* stringCompareComputationHelper(Object* o1, Object* o2, Object* start1, Object* end1, Object* start2, Object* end2, boolean ignorecaseP);
IntegerWrapper* stringCompareComputation(Object* o1, Object* o2, Object* start1, Object* end1, Object* start2, Object* end2);
IntegerWrapper* stringCompareIgnoreCaseComputation(Object* o1, Object* o2, Object* start1, Object* end1, Object* start2, Object* end2);
NumberWrapper* stringToNumberComputation(Object* x, Object* start, Object* end);
IntegerWrapper* lengthComputation(Object* x);
void helpStartupArithmetic1();
void helpStartupArithmetic2();
void startupArithmetic();

// Auxiliary global declarations:
extern Surrogate* SGT_ARITHMETIC_PL_KERNEL_KB_INTEGER_INTERVAL;
extern Symbol* SYM_ARITHMETIC_PL_KERNEL_KB_INTERVAL_LOWER_BOUND;
extern Symbol* SYM_ARITHMETIC_PL_KERNEL_KB_INTERVAL_UPPER_BOUND;
extern Surrogate* SGT_ARITHMETIC_PL_KERNEL_KB_INTERVAL_CACHE;
extern Symbol* SYM_ARITHMETIC_STELLA_HOME_CONTEXT;
extern Symbol* SYM_ARITHMETIC_LOGIC_INTERVAL_MEMBER;
extern Symbol* SYM_ARITHMETIC_STELLA_LOWER_BOUND;
extern Symbol* SYM_ARITHMETIC_STELLA_UPPER_BOUND;
extern Symbol* SYM_ARITHMETIC_LOGIC_STRICT_LOWER_BOUNDp;
extern Symbol* SYM_ARITHMETIC_LOGIC_STRICT_UPPER_BOUNDp;
extern Surrogate* SGT_ARITHMETIC_PL_KERNEL_KB_INTERVAL_CACHE_OF;
extern Surrogate* SGT_ARITHMETIC_PL_KERNEL_KB_INEQUALITY;
extern Surrogate* SGT_ARITHMETIC_LOGIC_LOGIC_OBJECT;
extern Surrogate* SGT_ARITHMETIC_LOGIC_SKOLEM;
extern Surrogate* SGT_ARITHMETIC_STELLA_INTEGER;
extern Surrogate* SGT_ARITHMETIC_PL_KERNEL_KB_g;
extern Surrogate* SGT_ARITHMETIC_STELLA_NUMBER_WRAPPER;
extern Surrogate* SGT_ARITHMETIC_LOGIC_QUANTITY_LOGIC_WRAPPER;
extern Surrogate* SGT_ARITHMETIC_PL_KERNEL_KB_ge;
extern Surrogate* SGT_ARITHMETIC_PL_KERNEL_KB_l;
extern Surrogate* SGT_ARITHMETIC_PL_KERNEL_KB_el;
extern Keyword* KWD_ARITHMETIC_LOWER_BOUND;
extern Keyword* KWD_ARITHMETIC_UPPER_BOUND;
extern Surrogate* SGT_ARITHMETIC_STELLA_e;
extern Keyword* KWD_ARITHMETIC_TERMINAL_FAILURE;
extern Surrogate* SGT_ARITHMETIC_STELLA_INTEGER_WRAPPER;
extern Keyword* KWD_ARITHMETIC_FINAL_SUCCESS;
extern Keyword* KWD_ARITHMETIC_FAILURE;
extern Keyword* KWD_ARITHMETIC_ORIGINAL;
extern Symbol* SYM_ARITHMETIC_STELLA_ITERATOR;
extern Keyword* KWD_ARITHMETIC_CONTINUING_SUCCESS;
extern Symbol* SYM_ARITHMETIC_PL_KERNEL_KB_STARTUP_ARITHMETIC;
extern Symbol* SYM_ARITHMETIC_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace pl_kernel_kb
