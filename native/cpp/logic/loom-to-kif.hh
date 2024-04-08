//  -*- Mode: C++ -*-

// loom-to-kif.hh

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
Object* loomArgumentDescriptionToKif(Object* tree, Keyword* arity);
Cons* loomRestrictionToKif(Cons* tree, Symbol* implicitvariable);
Cons* loomRelatesToKif(Cons* tree, Cons* implicitvariables);
void substituteVariablesInTree(Cons* tree, Cons* substitution);
Cons* loomThroughToKif(Cons* tree, Cons* implicitvariables);
Cons* loomSatisfiesToKif(Cons* tree, Cons* implicitvariables);
Cons* loomDescriptionToKif(Object* tree, Cons* implicitvariables);
boolean loomDescriptionOperatorP(Object* self);
Object* loomSentenceToKif(Object* tree);
int computeLoomDescriptionArity(Object* tree);
Object* eliminateLoomKeywords(Object* tree);
Cons* yieldImplicitVariables(int arity);
Cons* helpTranslateLoomDescriptionToKif(Object* tree, Cons* implicitvariables);
Cons* translateLoomDescriptionToKif(Object* tree);
Object* translateLoomSentenceToKif(Object* tree);
Cons* translateLoomAssertions(Cons* tree, boolean retractP);
Cons* translateLoomAsk(Cons* tree);
Cons* translateLoomRetrieve(Cons* tree);
Cons* translateOneLoomForm(Object* tree);
Object* safeGetNextSExpression(SExpressionIterator* iter);
void destructivelyUnquoteTopLevel(Cons* tree);
void translateLoomFile(const char* input, const char* output);
void translateLoomFileEvaluatorWrapper(Cons* arguments);
Cons* translateLoomStatement(Cons* tree);
Cons* translateLoomCreateClause(Cons* tree);
int guessLoomDefinitionArity(int arity, Object* definition, Cons* constraints);
Object* conjoinSentences(Cons* sentences);
Cons* translateLoomPartitions(Object* partitions, boolean exhaustiveP, Symbol* parentconcept);
Cons* translateLoomCharacteristics(Object* characteristics, Symbol* name);
Cons* translateLoomAnnotations(Object* annotations, Symbol* name);
Cons* translateLoomDefaults(Object* defaultTree, Cons* variables);
Keyword* simplifyTopLevelLoomKeywords(Keyword* keyword);
Cons* translateLoomDefinition(Cons* tree);
Cons* translateLoomContextChange(Cons* tree, boolean needsquoteP);
void helpStartupLoomToKif1();
void helpStartupLoomToKif2();
void startupLoomToKif();

// Auxiliary global declarations:
extern Surrogate* SGT_LOOM_TO_KIF_STELLA_CONS;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_INVERSE;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_INVERSE;
extern Keyword* KWD_LOOM_TO_KIF_BINARY;
extern Keyword* KWD_LOOM_TO_KIF_UNARY;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_KAPPA;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_AT_LEAST;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_AT_MOST;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_EXACTLY;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_ALL;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_SOME;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_THE;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_FILLED_BY;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_FILLERS;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_NOT_FILLED_BY;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_QUALIFIED_RANGE_CARDINALITY_LOWER_BOUND;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_QUALIFIED_RANGE_CARDINALITY_UPPER_BOUND;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_QUALIFIED_RANGE_CARDINALITY;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_RANGE_CARDINALITY_LOWER_BOUND;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_RANGE_CARDINALITY_UPPER_BOUND;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_RANGE_CARDINALITY;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_EXISTS;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_eg;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_AND;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_RANGE_TYPE;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_NOT;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_RELATES;
extern Surrogate* SGT_LOOM_TO_KIF_STELLA_NUMBER_WRAPPER;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_FOR_SOME;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_FORALL;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_THROUGH;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_INTERVALii;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_INTERVALi_;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_INTERVAL_i;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_INTERVAL__;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_el;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_l;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_ge;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_g;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_OR;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_SAME_AS;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_le;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_lg;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_e;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_ONE_OF;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_THE_ORDERED_SET;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_SATISFIES;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_DOMAIN;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_DOMAINS;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_RANGE;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_COMPOSE;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_MEMBER_OF;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_SETOF;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_LISTOF;
extern Keyword* KWD_LOOM_TO_KIF_ERROR;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_ABOUT;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_CREATE;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_SUPERRELATIONS;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_SUPERCONCEPTS;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_SUBSET_OF;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_QUOTE;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_RETRACT;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_ASSERT;
extern Keyword* KWD_LOOM_TO_KIF_3_VALUED_P;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_ASK;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_NULL;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_CONSIFY;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_RETRIEVE;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_PROGN;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_EVAL_WHEN;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_TELL;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_FORGET;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_TELLM;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_FORGETM;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_CREATEM;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_DEFCONCEPT;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_DEFSET;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_DEFRELATION;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_DEFPROPERTY;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_DEFCONTEXT;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_ADD_VALUE;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_SET_VALUE;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_FADD_VALUE;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_CHANGE_CONTEXT;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_IN_CONTEXT;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_IN_KB;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_CC;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_NIL;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_IN_DIALECT;
extern Keyword* KWD_LOOM_TO_KIF_KIF;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_IN_MODULE;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_THING;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_MUTUALLY_DISJOINT_COLLECTION;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_COVERING;
extern Keyword* KWD_LOOM_TO_KIF_SINGLE_VALUED;
extern Keyword* KWD_LOOM_TO_KIF_CLOSED_WORLD;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_CLOSED;
extern Keyword* KWD_LOOM_TO_KIF_COMMUTATIVE;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_COMMUTATIVE;
extern Keyword* KWD_LOOM_TO_KIF_SYMMETRIC;
extern Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_SYMMETRIC;
extern Keyword* KWD_LOOM_TO_KIF_CLOS_CLASS;
extern Keyword* KWD_LOOM_TO_KIF_MULTIPLE_VALUED;
extern Keyword* KWD_LOOM_TO_KIF_HASH_ON_DOMAINS;
extern Keyword* KWD_LOOM_TO_KIF_NON_EXPORTED;
extern Keyword* KWD_LOOM_TO_KIF_PERFECT;
extern Keyword* KWD_LOOM_TO_KIF_CLOSED_ON_CONSTANTS;
extern Keyword* KWD_LOOM_TO_KIF_BACKWARD_CHAINING;
extern Keyword* KWD_LOOM_TO_KIF_MONOTONIC;
extern Keyword* KWD_LOOM_TO_KIF_TEMPORAL;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_tg;
extern Keyword* KWD_LOOM_TO_KIF_ATTRIBUTES;
extern Keyword* KWD_LOOM_TO_KIF_CHARACTERISTICS;
extern Keyword* KWD_LOOM_TO_KIF_PARTITION;
extern Keyword* KWD_LOOM_TO_KIF_PARTITIONS;
extern Keyword* KWD_LOOM_TO_KIF_IMPLIES;
extern Keyword* KWD_LOOM_TO_KIF_CONSTRAINTS;
extern Keyword* KWD_LOOM_TO_KIF_EXHAUSTIVE_PARTITION;
extern Keyword* KWD_LOOM_TO_KIF_EXHAUSTIVE_PARTITIONS;
extern Surrogate* SGT_LOOM_TO_KIF_STELLA_STRING_WRAPPER;
extern Keyword* KWD_LOOM_TO_KIF_IS_PRIMITIVE;
extern Keyword* KWD_LOOM_TO_KIF_IS;
extern Keyword* KWD_LOOM_TO_KIF_DEFAULTS;
extern Keyword* KWD_LOOM_TO_KIF_DOMAIN;
extern Keyword* KWD_LOOM_TO_KIF_DOMAINS;
extern Keyword* KWD_LOOM_TO_KIF_RANGE;
extern Keyword* KWD_LOOM_TO_KIF_ARITY;
extern Keyword* KWD_LOOM_TO_KIF_IN_PARTITION;
extern Keyword* KWD_LOOM_TO_KIF_ANNOTATIONS;
extern Keyword* KWD_LOOM_TO_KIF_ROLES;
extern Keyword* KWD_LOOM_TO_KIF_NAME;
extern Keyword* KWD_LOOM_TO_KIF_IDENTIFIER;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_DEFFUNCTION;
extern Keyword* KWD_LOOM_TO_KIF__g;
extern Keyword* KWD_LOOM_TO_KIF_DOCUMENTATION;
extern Keyword* KWD_LOOM_TO_KIF_llegg;
extern Keyword* KWD_LOOM_TO_KIF_egg;
extern Keyword* KWD_LOOM_TO_KIF_AXIOMS;
extern Symbol* SYM_LOOM_TO_KIF_LOGIC_STARTUP_LOOM_TO_KIF;
extern Symbol* SYM_LOOM_TO_KIF_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
