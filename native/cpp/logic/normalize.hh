//  -*- Mode: C++ -*-

// normalize.hh

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




namespace logic {
  using namespace stella;

// Function signatures:
boolean searchControlPropositionP(Proposition* self);
boolean duplicateAndOrArgumentsP(Proposition* prop1, Proposition* prop2);
void collectFlatConjuncts(Proposition* self, List* flatconjuncts);
void overlayWithConstantProposition(Proposition* self, Proposition* constantproposition);
Proposition* conjoinPropositions(Cons* conjuncts);
Proposition* conjoinTwoPropositions(Proposition* prop1, Proposition* prop2);
void collectFlatDisjuncts(Proposition* self, List* flatdisjuncts);
Proposition* disjoinPropositions(Cons* disjuncts);
PatternVariable* renameLogicVariableApart(PatternVariable* variable, boolean destructiveP);
void overlayProposition(Proposition* self, Proposition* overlayingprop);
void normalizeExistsProposition(Proposition* self);
boolean migrateConsequentGoalsToAntecedentP(Proposition* self);
void flattenNestedForallProposition(Proposition* self);
void normalizeForallProposition(Proposition* self);
void normalizeNotProposition(Proposition* self);
void normalizeAndProposition(Proposition* self);
void normalizeOrProposition(Proposition* self);
void helpNormalizePredicateProposition(Proposition* self, Surrogate* relationref, Vector* predicatearguments);
void normalizeHoldsProposition(Proposition* self);
void normalizePredicateProposition(Proposition* self);
void normalizeFunctionProposition(Proposition* self);
Surrogate* computeRelationTermSurrogate(Skolem* skolem, Proposition* proposition);
Surrogate* evaluateRelationTerm(Object* relationterm, Proposition* proposition);
Proposition* normalizeValueFunction(Proposition* self);
void normalizeEquivalentProposition(Proposition* self);
Proposition* shallowCopyProposition(Proposition* self);
void normalizeProposition(Proposition* self);
void normalizeTopLevelProposition(Proposition* self);
void normalizeDescriptiveProposition(Proposition* self, Vector* iovariables, Keyword* kind);
void invertAtomicProposition(Proposition* self);
void invertExistsProposition(Proposition* self);
void invertForallProposition(Proposition* self);
Proposition* extractProposition(Description* self, KeyValueMap* mapping);
void invertImpliesProposition(Proposition* self);
Proposition* invertProposition(Proposition* self);
Proposition* safelyInvertProposition(Proposition* self);
void helpStartupNormalize1();
void startupNormalize();

// Auxiliary global declarations:
extern Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_CUT;
extern Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_BOUND_VARIABLES;
extern Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_FORK;
extern Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_QUERY;
extern Keyword* KWD_NORMALIZE_AND;
extern Keyword* KWD_NORMALIZE_CONSTANT;
extern Surrogate* SGT_NORMALIZE_STELLA_TRUE;
extern Symbol* SYM_NORMALIZE_LOGIC_CONSTANT;
extern Surrogate* SGT_NORMALIZE_STELLA_CS_VALUE;
extern Symbol* SYM_NORMALIZE_STELLA_AND;
extern Symbol* SYM_NORMALIZE_LOGIC_DESCRIPTIVEp;
extern Keyword* KWD_NORMALIZE_OR;
extern Symbol* SYM_NORMALIZE_STELLA_OR;
extern Symbol* SYM_NORMALIZE_LOGIC_WEIGHT;
extern Symbol* SYM_NORMALIZE_LOGIC_NEURAL_NET;
extern Symbol* SYM_NORMALIZE_LOGIC_IO_VARIABLES;
extern Symbol* SYM_NORMALIZE_LOGIC_VARIABLE_TYPEp;
extern Keyword* KWD_NORMALIZE_DESCRIPTION;
extern Keyword* KWD_NORMALIZE_EXISTS;
extern Keyword* KWD_NORMALIZE_NOT;
extern Keyword* KWD_NORMALIZE_ERROR;
extern Surrogate* SGT_NORMALIZE_STELLA_FALSE;
extern Keyword* KWD_NORMALIZE_FORALL;
extern Keyword* KWD_NORMALIZE_EQUIVALENT;
extern Keyword* KWD_NORMALIZE_ISA;
extern Keyword* KWD_NORMALIZE_PREDICATE;
extern Keyword* KWD_NORMALIZE_FUNCTION;
extern Symbol* SYM_NORMALIZE_STELLA_EXISTS;
extern Surrogate* SGT_NORMALIZE_LOGIC_DESCRIPTION;
extern Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_HOLDS;
extern Surrogate* SGT_NORMALIZE_STELLA_THING;
extern Surrogate* SGT_NORMALIZE_LOGIC_PROPOSITION;
extern Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_VARIABLE_ARITY;
extern Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_ARITY;
extern Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_CLASS;
extern Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_FUNCTION;
extern Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_VALUE;
extern Surrogate* SGT_NORMALIZE_LOGIC_PATTERN_VARIABLE;
extern Surrogate* SGT_NORMALIZE_LOGIC_SKOLEM;
extern Surrogate* SGT_NORMALIZE_LOGIC_NAMED_DESCRIPTION;
extern Symbol* SYM_NORMALIZE_STELLA_FUNCTION;
extern Symbol* SYM_NORMALIZE_LOGIC_DONT_OPTIMIZEp;
extern Keyword* KWD_NORMALIZE_IMPLIES;
extern Keyword* KWD_NORMALIZE_FAIL;
extern Keyword* KWD_NORMALIZE_COLLECT_INTO;
extern Keyword* KWD_NORMALIZE_TAIL;
extern Keyword* KWD_NORMALIZE_HEAD;
extern Symbol* SYM_NORMALIZE_STELLA_NOT;
extern Surrogate* SGT_NORMALIZE_LOGIC_NOT;
extern Surrogate* SGT_NORMALIZE_LOGIC_FORALL;
extern Surrogate* SGT_NORMALIZE_LOGIC_EXISTS;
extern Surrogate* SGT_NORMALIZE_LOGIC_OR;
extern Surrogate* SGT_NORMALIZE_LOGIC_AND;
extern Symbol* SYM_NORMALIZE_LOGIC_STARTUP_NORMALIZE;
extern Symbol* SYM_NORMALIZE_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
