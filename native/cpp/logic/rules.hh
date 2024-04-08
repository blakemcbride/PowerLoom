//  -*- Mode: C++ -*-

// rules.hh

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

// Global declarations:
extern boolean oLAZY_SATELLITE_RULESpo;
extern DECLARE_STELLA_SPECIAL(oDERIVE_DEFERRED_SATELLITE_RULES_INVOCATIONSo, List* );

// Function signatures:
List* findMatchableGoals(Proposition* forallprop, Keyword* headortail);
void collectMatchingRuleGoals(Proposition* proposition, Cons* toplevelvars, Keyword* headortail, List* collection);
boolean atomicForallArgumentP(Proposition* forallprop, Keyword* headortail);
boolean atomicGoalPropositionP(Proposition* proposition);
boolean atomicGoalDescriptionP(Description* description);
boolean variableArityGoalPropositionP(Proposition* proposition);
boolean chainableRelationP(NamedDescription* description, Keyword* headortail);
Description* extractGoalDescription(Proposition* goal, Keyword* headortail);
Cons* extractGoalArguments(Proposition* goal);
Proposition* substituteProposition(Proposition* proposition, Proposition* outprop, Proposition* inprop);
Proposition* extractInvertedGoal(Proposition* proposition, Proposition* goal);
Proposition* invertForallAroundGoal(Proposition* forallprop, Proposition* goal, Keyword* headortail, boolean contrapositiveP);
Description* constructDescriptionFromForallProposition(Proposition* forallprop, Keyword* headortail);
void markAsForwardRule(Proposition* impliesprop);
void deriveOneSatelliteRule(Proposition* masterforall, Proposition* goal, Keyword* headortail, boolean contrapositiveP);
boolean deriveSatelliteRulesForGoalP(Proposition* forallprop, Description* goaldescription, Keyword* direction, boolean lazysatellitesP);
void deriveSatelliteRules(Proposition* forallprop);
void deriveDeferredSatelliteRules(Description* self);
void deriveDeferredContrapositiveSatelliteRules(Description* self);
Description* getInferableComplementDescription(Description* self);
Proposition* deriveImpliesFromForall(Proposition* forallprop);
Cons* deconstructForallTree(Cons* foralltree, Object*& _Return1, Cons*& _Return2);
ForwardChainingIndex* createForwardChainingIndex(Proposition* goal, Proposition* masterforall);
void deriveComplexForwardRule(Proposition* goal, Proposition* masterforall);
void skolemizeRule(Proposition* rule);
Cons* skolemizeRuleForGoal(Cons* goal, Cons* antecedent, Cons* forallvars, Cons* existsvars, Symbol* skolemfnid);
Cons* helpGetForwardChainingRules(Description* description);
Cons* callGetRules(Object* relationref);
Cons* getRules(Object* relation);
void deleteRules(Object* relation);
void printRules(Object* relation);
void printSatellites(Proposition* forallprop);
boolean propositionHasStrengthP(Proposition* self, TruthValue* minimalstrength);
Proposition* getRule(Object* rulename);
Proposition* findRule(Object* rulename);
Proposition* assertRule(Object* rulename);
Proposition* retractRule(Object* rulename);
void deleteRuleCachesOnRelation(Relation* relation);
void resetQueryCaches();
void helpStartupRules1();
void startupRules();

// Auxiliary global declarations:
extern Keyword* KWD_RULES_HEAD;
extern Symbol* SYM_RULES_LOGIC_IO_VARIABLES;
extern Keyword* KWD_RULES_TAIL;
extern Keyword* KWD_RULES_AND;
extern Keyword* KWD_RULES_EXISTS;
extern Keyword* KWD_RULES_OR;
extern Keyword* KWD_RULES_FORALL;
extern Keyword* KWD_RULES_ISA;
extern Keyword* KWD_RULES_PREDICATE;
extern Keyword* KWD_RULES_FUNCTION;
extern Keyword* KWD_RULES_NOT;
extern Keyword* KWD_RULES_IMPLIES;
extern Surrogate* SGT_RULES_PL_KERNEL_KB_HOLDS;
extern Surrogate* SGT_RULES_LOGIC_PATTERN_VARIABLE;
extern Symbol* SYM_RULES_LOGIC_COMPLEMENT_DESCRIPTION;
extern Surrogate* SGT_RULES_STELLA_SURROGATE;
extern Keyword* KWD_RULES_ERROR;
extern Surrogate* SGT_RULES_LOGIC_PROPOSITION;
extern Surrogate* SGT_RULES_STELLA_FALSE;
extern Surrogate* SGT_RULES_STELLA_TRUE;
extern Symbol* SYM_RULES_STELLA_FORALL;
extern Keyword* KWD_RULES_DESCRIPTION;
extern Symbol* SYM_RULES_LOGIC_FORWARD_ONLYp;
extern Keyword* KWD_RULES_EXTENSIONAL_ASSERTION;
extern Symbol* SYM_RULES_LOGIC_SATELLITE_PROPOSITIONS;
extern Symbol* SYM_RULES_LOGIC_MASTER_PROPOSITION;
extern Symbol* SYM_RULES_LOGIC_BACKWARD_ONLYp;
extern Symbol* SYM_RULES_LOGIC_DONT_OPTIMIZEp;
extern Keyword* KWD_RULES_POSITIVE;
extern Keyword* KWD_RULES_CONTRAPOSITIVE;
extern Symbol* SYM_RULES_LOGIC_RULES_WITH_DEFERRED_SATELLITES;
extern Keyword* KWD_RULES_NON_PAGING;
extern Symbol* SYM_RULES_LOGIC_DEFERRED_CONTRAPOSITIVESp;
extern Keyword* KWD_RULES_POSITIVE_AND_CONTRAPOSITIVE;
extern Symbol* SYM_RULES_STELLA_TRUE;
extern Symbol* SYM_RULES_STELLA_EXISTS;
extern Symbol* SYM_RULES_LOGIC_FORWARD_CHAINING_INDICES;
extern Symbol* SYM_RULES_STELLA_AND;
extern Keyword* KWD_RULES_CONCEIVE;
extern Symbol* SYM_RULES_PL_KERNEL_KB_SKOLEM_FN;
extern Symbol* SYM_RULES_LOGIC_lle;
extern Surrogate* SGT_RULES_LOGIC_NAMED_DESCRIPTION;
extern Keyword* KWD_RULES_FORWARD;
extern Keyword* KWD_RULES_BACKWARD;
extern Keyword* KWD_RULES_ASSERT_TRUE;
extern Keyword* KWD_RULES_RETRACT_TRUE;
extern Symbol* SYM_RULES_LOGIC_DESCRIPTION;
extern Symbol* SYM_RULES_LOGIC_STARTUP_RULES;
extern Symbol* SYM_RULES_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
