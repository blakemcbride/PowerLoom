//  -*- Mode: C++ -*-

// conses.hh

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
extern Cons* NIL;
extern int oREMOVE_DUPLICATES_CROSSOVER_POINTo;
extern DECLARE_STELLA_SPECIAL(oSORT_TUPLE_COMPARE_PREDICATEo, cpp_function_code );
extern DECLARE_STELLA_SPECIAL(oSORT_TUPLE_COMPARE_INDEXo, int );
extern DECLARE_STELLA_SPECIAL(oSORT_OBJECTS_COMPARE_SLOTo, StorageSlot* );
extern DECLARE_STELLA_SPECIAL(oPRINTPRETTYpo, boolean );
extern DECLARE_STELLA_SPECIAL(oPRINTREADABLYpo, boolean );
extern DECLARE_STELLA_SPECIAL(oPRINTLENGTHo, int );
extern Symbol* ELLIPSIS;
extern DECLARE_STELLA_SPECIAL(oPRINTPRETTYCODEpo, boolean );
extern DECLARE_STELLA_SPECIAL(oDEPTHEXCEEDEDpo, boolean );
extern int oDEPTHCUTOFFo;

// Function signatures:
boolean nilP(Object* x);
Cons* cons(Object* value, Cons* rest);
Cons* removeDuplicatesFromLongList(Cons* self, boolean equaltestP);
Cons* mapNullToNil(Cons* self);
Cons* lastCons(Cons* self);
boolean terminateConsIteratorP(ConsIterator* self);
void addConsToEndOfConsList(Cons* self, Cons* lastcons);
boolean butLastNextP(AllPurposeIterator* self);
Cons* copyConsList(Cons* self);
Cons* consList(int values, ...);
Cons* makeConsList(int size);
Cons* consSetFirstGetNext(Cons* list, Object* value);
Cons* listO(int values, ...);
Cons* append(Cons* conslist1, Cons* conslist2);
Cons* helpSortConsList(Cons* list, int length, cpp_function_code predicate);
Cons* mergeConsLists(Cons* list1, Cons* list2, cpp_function_code predicate);
boolean generalizedSymbolLessThanP(GeneralizedSymbol* x, GeneralizedSymbol* y);
boolean wrappedIntegerLessThanP(IntegerWrapper* x, IntegerWrapper* y);
boolean wrappedLongIntegerLessThanP(LongIntegerWrapper* x, LongIntegerWrapper* y);
boolean wrappedFloatLessThanP(FloatWrapper* x, FloatWrapper* y);
boolean wrappedStringLessThanP(StringWrapper* x, StringWrapper* y);
boolean wrappedMutableStringLessThanP(MutableStringWrapper* x, MutableStringWrapper* y);
boolean numberLessThanP(NumberWrapper* x, NumberWrapper* y);
cpp_function_code chooseSortPredicate(Object* firstelement);
boolean sortTupleCompareP(Cons* x, Cons* y);
boolean sortObjectsCompareP(Object* x, Object* y);
boolean searchConsTreeP(Object* tree, Object* value);
boolean searchConsTreeWithFilterP(Object* tree, Object* value, Cons* filter);
Object* copyConsTree(Object* self);
boolean equalConsTreesP(Object* tree1, Object* tree2);
Object* substituteConsTree(Object* tree, Object* newvalue, Object* oldvalue);
Object* consTreeNth(Cons* tree, int index, ...);
Cons* consTreeNthRest(Cons* tree, int index, ...);
KeyValueList* matchConsTree(Object* tree, Object* pattern, KeyValueList* bindings);
boolean consTreeMatchP(Object* tree, Object* pattern);
void printCons(Cons* tree, std::ostream* stream, const char* lparen, const char* rparen);
void pprintCons(Cons* tree, std::ostream* stream, const char* lparen, const char* rparen);
void printStellaCode(Object* tree, std::ostream* stream);
void printStellaDefinition(Object* tree, std::ostream* stream);
int treeSize(Object* self);
int safelyComputeTreeSize(Cons* tree, int depthcount, int cutoff);
int safeTreeSize(Cons* tree, const char*& _Return1);
void helpStartupConses1();
void helpStartupConses2();
void startupConses();

// Auxiliary global declarations:
extern Surrogate* SGT_CONSES_STELLA_GENERALIZED_SYMBOL;
extern Surrogate* SGT_CONSES_STELLA_MUTABLE_STRING_WRAPPER;
extern Surrogate* SGT_CONSES_STELLA_CONS;
extern Symbol* SYM_CONSES_STELLA_p;
extern Symbol* SYM_CONSES_STELLA_ddd;
extern Symbol* SYM_CONSES_STELLA_STARTUP_CONSES;
extern Symbol* SYM_CONSES_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
