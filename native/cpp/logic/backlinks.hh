//  -*- Mode: C++ -*-

// backlinks.hh

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
extern int oSPECIALIZED_BACKLINKS_CROSSOVER_POINTo;
extern IntegerHashTable* oINTEGER_LOGIC_WRAPPER_TABLEo;
extern FloatHashTable* oFLOAT_LOGIC_WRAPPER_TABLEo;
extern StringHashTable* oSTRING_LOGIC_WRAPPER_TABLEo;
extern boolean oBACKLINK_ALL_PROPOSITION_ARGUMENTSpo;
extern DECLARE_STELLA_SPECIAL(oSUPPRESSINSERTIONINTOCLASSEXTENSIONpo, boolean );

// Function signatures:
boolean typeHasBacklinksP(Surrogate* type);
BacklinksIndex* createBacklinksIndex(Object* self);
BacklinksIndex* getBacklinksIndex(Object* self);
void addDependentPropositionToSpecializedIndex(BacklinksIndex* index, Proposition* proposition, Object* argument);
void helpAddDependentProposition(BacklinksIndex* index, Proposition* proposition, Object* argument);
void addDependentPropositionLink(Object* self, Proposition* proposition);
void removeDependentPropositionLink(Object* self, Proposition* proposition);
void helpRemoveDependentProposition(BacklinksIndex* index, Proposition* proposition);
void removeAllDependentPropositionLinks(LogicObject* self);
Object* rewrapArgument(Object* argument);
boolean indexIthDomainP(NamedDescription* description, int i);
boolean rewrapIthArgumentP(Object* argument, Proposition* proposition, int i);
void rewrapPropositionArguments(Proposition* self);
SequenceIndex* helpUnfilteredDependentPropositions(Object* self, Surrogate* relation);
SequenceIndex* unfilteredDependentPropositions(Object* self, Surrogate* relation);
boolean allSpecializingDependentPropositionsNextP(AllPurposeIterator* self);
Iterator* allSpecializingDependentPropositions(Object* self, Surrogate* relationref);
SequenceIndex* unfilteredDependentIsaPropositions(Object* self);
SequenceIndex* unfilteredDependentImpliesPropositions(Object* self);
boolean inheritsTruthFromMasterP(Proposition* self);
Cons* applicableRulesOfDescription(LogicObject* self, Keyword* direction, boolean truerulesonlyP);
Cons* makeSelectionPattern(Keyword* kind, Cons* options, Cons* arguments);
Keyword* patternKind(Cons* pattern);
Cons* patternOptions(Cons* pattern);
Cons* patternArguments(Cons* pattern);
Cons* makeDependentPropositionsPattern(Object* argument);
Cons* makeIsaPattern(Object* argument);
Cons* makeRelationExtensionPattern(Surrogate* relation);
Cons* makeRelationPattern(Surrogate* relation, Object* argument);
Cons* makeRelationPattern1(Surrogate* relation, Object* argument);
Cons* makeRelationPattern2(Surrogate* relation, Object* argument1, Object* argument2);
Cons* makeRelationPattern3(Surrogate* relation, Object* argument1, Object* argument2, Object* argument3);
Cons* makeRelationPattern4(Surrogate* relation, Object* argument1, Object* argument2, Object* argument3, Object* argument4);
Cons* makeRelationPatternN(Surrogate* relation, int arguments, ...);
Cons* makeRulesPattern(Object* posrelation, Object* negrelation);
Object* findSelectionKeyWithEquivalents(Cons* pattern);
SequenceIndex* selectPropositions(Cons* pattern);
SequenceIndex* selectIsaPropositions(Cons* pattern);
SequenceIndex* helpSelectRelationPropositions(Cons* pattern);
SequenceIndex* selectRelationPropositions(Cons* pattern);
SequenceIndex* selectRulePropositions(Cons* pattern);
TruthValue* evaluateSelectionPattern(Cons* pattern);
boolean evaluationSelectionPatternP(Cons* pattern);
boolean argumentDiscouragesBacklinksP(Object* self);
void surrogatifyDiscouragedArguments(Proposition* self);
int countBacklinksOnRelation(Object* self, Keyword* kind, Surrogate* relation);
Object* selectArgumentWithBacklinks(Proposition* proposition, boolean& _Return1);
boolean instanceHasBacklinksP(Object* self);
Object* selectInstanceWithBacklinks(Cons* instances, Surrogate* relation);
SequenceIndex* findSimilarPropositions(Proposition* self);
Proposition* findMatchingConceivedProposition(Proposition* goal);
void transferPropositionsAndBacklinks(Object* from, Object* to);
void transferPropositionsExceptFor(Object* from, Object* to, List* exceptpropositions);
void transferDescriptionExtension(NamedDescription* from, NamedDescription* to);
SequenceIndex* getDescriptionExtension(NamedDescription* description, boolean updateP);
void cleanupDescriptionExtension(NamedDescription* description);
void cleanupAllDescriptionExtensions();
void updateDescriptionExtension(Proposition* self);
Iterator* allExtensionMembers(NamedDescription* description);
boolean collectionImpliesCollectionP(LogicObject* subcollection, LogicObject* supercollection);
boolean relationImpliesRelationP(NamedDescription* subrel, NamedDescription* superrel);
boolean descriptionImpliesDescriptionP(Description* subdesc, Description* superdesc);
boolean relationrefSpecializesRelationrefP(Surrogate* relationref1, Surrogate* relationref2);
void helpStartupBacklinks1();
void helpStartupBacklinks2();
void startupBacklinks();

// Auxiliary global declarations:
extern Surrogate* SGT_BACKLINKS_LOGIC_PATTERN_VARIABLE;
extern Keyword* KWD_BACKLINKS_NON_PAGING;
extern Keyword* KWD_BACKLINKS_DEPENDENTS;
extern Surrogate* SGT_BACKLINKS_LOGIC_LOGIC_OBJECT;
extern Surrogate* SGT_BACKLINKS_STELLA_THING;
extern Symbol* SYM_BACKLINKS_LOGIC_DEPENDENT_PROPOSITIONS_INDEX;
extern Surrogate* SGT_BACKLINKS_LOGIC_PROPOSITION;
extern Symbol* SYM_BACKLINKS_LOGIC_DESCRIPTIVEp;
extern Surrogate* SGT_BACKLINKS_LOGIC_INTEGER_LOGIC_WRAPPER;
extern Surrogate* SGT_BACKLINKS_LOGIC_FLOAT_LOGIC_WRAPPER;
extern Surrogate* SGT_BACKLINKS_LOGIC_STRING_LOGIC_WRAPPER;
extern Keyword* KWD_BACKLINKS_ISA;
extern Keyword* KWD_BACKLINKS_RELATION;
extern Surrogate* SGT_BACKLINKS_PL_KERNEL_KB_EQUIVALENT;
extern Keyword* KWD_BACKLINKS_CONSTANT;
extern Surrogate* SGT_BACKLINKS_LOGIC_SKOLEM;
extern Surrogate* SGT_BACKLINKS_LOGIC_DESCRIPTION;
extern Keyword* KWD_BACKLINKS_DEBUGGING;
extern Symbol* SYM_BACKLINKS_LOGIC_HYPOTHESIZED_INSTANCEp;
extern Keyword* KWD_BACKLINKS_WARNING;
extern Surrogate* SGT_BACKLINKS_STELLA_INTEGER;
extern Surrogate* SGT_BACKLINKS_STELLA_FLOAT;
extern Surrogate* SGT_BACKLINKS_STELLA_STRING;
extern Surrogate* SGT_BACKLINKS_STELLA_LITERAL_WRAPPER;
extern Surrogate* SGT_BACKLINKS_LOGIC_BACKLINKS_MIXIN;
extern Surrogate* SGT_BACKLINKS_LOGIC_PAGING_INDEX;
extern Surrogate* SGT_BACKLINKS_PL_KERNEL_KB_SUBSET_OF;
extern Symbol* SYM_BACKLINKS_LOGIC_MASTER_PROPOSITION;
extern Keyword* KWD_BACKLINKS_FORWARD;
extern Symbol* SYM_BACKLINKS_LOGIC_SUBSUMPTION_LINKp;
extern Keyword* KWD_BACKLINKS_RULES;
extern Keyword* KWD_BACKLINKS_CONTEXT_PROPOSITIONS;
extern Keyword* KWD_BACKLINKS_CONTEXT_INSTANCES;
extern Keyword* KWD_BACKLINKS_EQUIVALENT;
extern Surrogate* SGT_BACKLINKS_LOGIC_F_SELECT_RELATION_PROPOSITIONS_MEMO_TABLE_000;
extern Surrogate* SGT_BACKLINKS_LOGIC_F_SELECT_RELATION_PROPOSITIONS_MEMO_TABLE_001;
extern Surrogate* SGT_BACKLINKS_LOGIC_F_SELECT_RELATION_PROPOSITIONS_MEMO_TABLE_002;
extern Surrogate* SGT_BACKLINKS_LOGIC_F_SELECT_RELATION_PROPOSITIONS_MEMO_TABLE_003;
extern Surrogate* SGT_BACKLINKS_LOGIC_F_SELECT_RELATION_PROPOSITIONS_MEMO_TABLE_004;
extern Keyword* KWD_BACKLINKS_EVALUATEp;
extern Symbol* SYM_BACKLINKS_STELLA_TRUE;
extern Keyword* KWD_BACKLINKS_FUNCTION;
extern Keyword* KWD_BACKLINKS_PREDICATE;
extern Keyword* KWD_BACKLINKS_EXTENSIONAL_ASSERTION;
extern Keyword* KWD_BACKLINKS_DESCRIPTION;
extern Keyword* KWD_BACKLINKS_PAGING;
extern Symbol* SYM_BACKLINKS_LOGIC_STARTUP_BACKLINKS;
extern Symbol* SYM_BACKLINKS_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
