//  -*- Mode: C++ -*-

// foreach.hh

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
| Portions created by the Initial Developer are Copyright (C) 1996-2023      |
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



namespace stella {

// Global declarations:
extern boolean oAGGRESSIVELY_OPTIMIZE_INTERVAL_FOREACHpo;

// Function signatures:
Cons* extractOneInClause(Cons* tail, Cons*& _Return1);
Cons* extractOneGeneratorTerm(Cons* tail, Cons*& _Return1);
Cons* extractGeneratorsClause(Cons* tail, Cons*& _Return1);
Object* extractOptionAndResidue(Symbol* option, Cons* tail, Cons*& _Return1);
Cons* extractDoClause(Cons* tail, Cons*& _Return1);
Cons* foreachToPrefixForeachTree(Cons* foreachtree);
Cons* walkForeachTree(Cons* tree, StandardObject*& _Return1);
Object* walkCollectionTree(Object* tree, boolean dontoptimizeP, StandardObject*& _Return1);
Cons* yieldInCursorClauses(Cons* intree, boolean dontoptimizeP, Cons*& _Return1, Cons*& _Return2, Object*& _Return3);
boolean useVectorStyleIterationP(Surrogate* collectiontype);
Cons* yieldInCursorClausesForGeneralCollection(Object* collectiontree, StandardObject* collectiontype, Symbol* keyvar, Symbol* valuevar, Cons*& _Return1, Cons*& _Return2, Object*& _Return3);
Cons* yieldInCursorClausesForIntegerInterval(Cons* collectiontree, StandardObject* collectiontype, Symbol* keyvar, Symbol* valuevar, Cons*& _Return1, Cons*& _Return2, Object*& _Return3);
Cons* yieldOptimizedInCursorClausesForIntegerInterval(Cons* collectiontree, StandardObject* collectiontype, Symbol* keyvar, Symbol* valuevar, Cons*& _Return1, Cons*& _Return2, Object*& _Return3);
Cons* yieldInCursorClausesForVector(Object* collectiontree, StandardObject* collectiontype, Symbol* keyvar, Symbol* valuevar, Cons*& _Return1, Cons*& _Return2, Object*& _Return3);
Cons* yieldInCursorClausesForArgumentList(Object* collectiontree, StandardObject* collectiontype, Symbol* keyvar, Symbol* valuevar, Cons*& _Return1, Cons*& _Return2, Object*& _Return3);
Cons* yieldOnCursorClauses(Cons* ontree, Cons*& _Return1, Cons*& _Return2, Object*& _Return3);
Cons* collectCursorClauses(Cons* cursorstree, boolean dontoptimizeP, Cons*& _Return1, Cons*& _Return2, Object*& _Return3);
Cons* walkCursorsTree(Cons* cursorstree, boolean dontoptimizeP, Cons*& _Return1, Cons*& _Return2, Object*& _Return3);
Cons* yieldCollectIntoListCode(Symbol* collectvariable, Object* intovariable, Object* collecttree);
Cons* yieldCollectIntoConsCode(Symbol* collectvariable, Object* intovariable, Object* collecttree);
Cons* yieldCollectCode(Symbol* collectvariable, Object* intovariable, Object* collecttree);
Cons* walkPrefixCollectIntoTree(Cons* collectintotree, Cons* iterators, Cons* docode, Cons*& _Return1);
Cons* wrapWhereTest(Object* wheretest, Cons* actions);
Cons* walkPrefixForeachBody(Cons* iteratorclauses, Object* wheretest, Cons* doactions);
Cons* walkPrefixForeachTree(Cons* tree, StandardObject*& _Return1);
Cons* walkExistsTree(Cons* tree, StandardObject*& _Return1);
Cons* walkForallTree(Cons* tree, StandardObject*& _Return1);
Cons* walkSomeTree(Cons* tree, StandardObject*& _Return1);
void helpStartupForeach1();
void startupForeach();

// Auxiliary global declarations:
extern Symbol* SYM_FOREACH_STELLA_AS;
extern Symbol* SYM_FOREACH_STELLA_COMMA;
extern Symbol* SYM_FOREACH_STELLA_DO;
extern Symbol* SYM_FOREACH_STELLA_COLLECT;
extern Surrogate* SGT_FOREACH_STELLA_VOID;
extern Symbol* SYM_FOREACH_STELLA_PREFIX_FOREACH;
extern Symbol* SYM_FOREACH_STELLA_IN;
extern Symbol* SYM_FOREACH_STELLA_X;
extern Symbol* SYM_FOREACH_STELLA_NIL;
extern Symbol* SYM_FOREACH_STELLA_WHERE;
extern Symbol* SYM_FOREACH_STELLA_INTO;
extern Symbol* SYM_FOREACH_STELLA_COLLECT_INTO;
extern Symbol* SYM_FOREACH_STELLA_FOREACH;
extern Symbol* SYM_FOREACH_STELLA_EXISTS;
extern Symbol* SYM_FOREACH_STELLA_FORALL;
extern Symbol* SYM_FOREACH_STELLA_SOME;
extern Surrogate* SGT_FOREACH_STELLA_CONS;
extern Symbol* SYM_FOREACH_STELLA_INTERVAL;
extern Surrogate* SGT_FOREACH_STELLA_INTEGER_INTERVAL;
extern Surrogate* SGT_FOREACH_STELLA_UNKNOWN;
extern Surrogate* SGT_FOREACH_STELLA_ABSTRACT_ITERATOR;
extern Symbol* SYM_FOREACH_STELLA_ALLOCATE_ITERATOR;
extern Symbol* SYM_FOREACH_STELLA_FALSE;
extern Surrogate* SGT_FOREACH_STELLA_ARGUMENT_LIST;
extern Surrogate* SGT_FOREACH_STELLA_STRING;
extern Surrogate* SGT_FOREACH_STELLA_MUTABLE_STRING;
extern Surrogate* SGT_FOREACH_STELLA_VECTOR;
extern Surrogate* SGT_FOREACH_STELLA_SEQUENCE_MIXIN;
extern Symbol* SYM_FOREACH_STELLA_THE_ARRAY;
extern Surrogate* SGT_FOREACH_STELLA_LIST;
extern Symbol* SYM_FOREACH_STELLA_THE_CONS_LIST;
extern Surrogate* SGT_FOREACH_STELLA_KEY_VALUE_LIST;
extern Surrogate* SGT_FOREACH_STELLA_KV_CONS;
extern Symbol* SYM_FOREACH_STELLA_THE_KV_LIST;
extern Surrogate* SGT_FOREACH_STELLA_PROPERTY_LIST;
extern Symbol* SYM_FOREACH_STELLA_THE_PLIST;
extern Symbol* SYM_FOREACH_STELLA_KEY;
extern Symbol* SYM_FOREACH_STELLA_VALUE;
extern Symbol* SYM_FOREACH_STELLA_SETQ;
extern Symbol* SYM_FOREACH_STELLA_REST;
extern Symbol* SYM_FOREACH_STELLA_NOT;
extern Symbol* SYM_FOREACH_STELLA_NILp;
extern Symbol* SYM_FOREACH_STELLA_DEFINEDp;
extern Symbol* SYM_FOREACH_STELLA_NEXTp;
extern Symbol* SYM_FOREACH_STELLA_NULL;
extern Symbol* SYM_FOREACH_STELLA_ANY_VALUE;
extern Symbol* SYM_FOREACH_STELLA_ANY_KEY;
extern Symbol* SYM_FOREACH_STELLA_NULL_INTEGER;
extern Surrogate* SGT_FOREACH_STELLA_INTEGER;
extern Surrogate* SGT_FOREACH_STELLA_NUMBER_WRAPPER;
extern Surrogate* SGT_FOREACH_STELLA_BOOLEAN;
extern Symbol* SYM_FOREACH_STELLA_NULLp;
extern Symbol* SYM_FOREACH_STELLA_ii;
extern Symbol* SYM_FOREACH_STELLA_TRUE;
extern Symbol* SYM_FOREACH_STELLA_le;
extern Symbol* SYM_FOREACH_STELLA_OR;
extern Symbol* SYM_FOREACH_STELLA_1_;
extern Symbol* SYM_FOREACH_STELLA__;
extern Symbol* SYM_FOREACH_STELLA_l;
extern Symbol* SYM_FOREACH_STELLA_LENGTH;
extern Surrogate* SGT_FOREACH_STELLA_CHARACTER;
extern Symbol* SYM_FOREACH_STELLA_NTH;
extern Surrogate* SGT_FOREACH_STELLA_ARGUMENT_LIST_ITERATOR;
extern Symbol* SYM_FOREACH_STELLA_SYS_CALL_METHOD;
extern Surrogate* SGT_FOREACH_STELLA_LITERAL;
extern Symbol* SYM_FOREACH_STELLA_ON;
extern Symbol* SYM_FOREACH_STELLA_AND;
extern Symbol* SYM_FOREACH_STELLA_IF;
extern Symbol* SYM_FOREACH_STELLA_PROGN;
extern Symbol* SYM_FOREACH_STELLA_CONS;
extern Symbol* SYM_FOREACH_STELLA_EMPTYp;
extern Symbol* SYM_FOREACH_STELLA_SETF;
extern Symbol* SYM_FOREACH_STELLA_ADD_CONS_TO_END_OF_CONS_LIST;
extern Symbol* SYM_FOREACH_STELLA_COND;
extern Symbol* SYM_FOREACH_STELLA_CONSp;
extern Symbol* SYM_FOREACH_STELLA_OTHERWISE;
extern Symbol* SYM_FOREACH_STELLA_WHEN;
extern Symbol* SYM_FOREACH_STELLA_SYS_FOREACH;
extern Symbol* SYM_FOREACH_STELLA_VRLET;
extern Symbol* SYM_FOREACH_STELLA_BREAK;
extern Symbol* SYM_FOREACH_STELLA_ALWAYS;
extern Symbol* SYM_FOREACH_STELLA_STARTUP_FOREACH;
extern Symbol* SYM_FOREACH_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
