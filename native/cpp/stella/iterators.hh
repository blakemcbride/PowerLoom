//  -*- Mode: C++ -*-

// iterators.hh

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

// Class definitions:
class CrossProductIterator : public Iterator {
// Iterator class that generates the cross product of a list of domains.
// Each value tuple is represented as a CONS.  CAUTION: the value tuple will be modified
// destructively, hence, it needs to be copied in case it needs to persist beyond a single
// iteration.
public:
  Cons* domains;
  Cons* cursors;
public:
  virtual boolean nextP();
  virtual void reset();
  virtual Surrogate* primaryType();
};



// Function signatures:
boolean terminateDestructiveListIteratorP(DestructiveListIterator* self);
boolean filteredNestedIteratorNextP(AllPurposeIterator* self);
boolean iteratorConsListNextP(AllPurposeIterator* self);
boolean iteratorConsListEmptyP(AllPurposeIterator* self);
boolean filteredConcatenatedIteratorNextP(AllPurposeIterator* self);
IntegerIntervalIterator* interval(int lowerbound, int upperbound);
void initializeReverseIntegerIntervalIterator(ReverseIntegerIntervalIterator* self);
ReverseIntegerIntervalIterator* reverseInterval(int lowerbound, int upperbound);
StringIterator* stringAllocateIterator(const char* self);
Iterator* allocateAllMetaObjectsIterator(int arraysize, cpp_function_code nextcode, Module* module, boolean localP);
boolean selectedMetaObjectP(AllPurposeIterator* self, Module* objectmodule);
boolean allSymbolsNextP(AllPurposeIterator* self);
Iterator* allSymbols(Module* module, boolean localP);
boolean filterPublicSlotP(Slot* self, AllPurposeIterator* iterator);
boolean filterPrivateSlotP(Slot* self, AllPurposeIterator* iterator);
boolean filterMethodSlotP(Slot* self, AllPurposeIterator* iterator);
boolean filterPublicMethodSlotP(Slot* self, AllPurposeIterator* iterator);
boolean filterNonExternalSlotP(Slot* self, AllPurposeIterator* iterator);
boolean filterNonParameterSlotP(Slot* self, AllPurposeIterator* iterator);
boolean filterNonAuxiliarySlotP(Slot* self, AllPurposeIterator* iterator);
boolean filterSlotP(Slot* self, AllPurposeIterator* iterator);
boolean allFunctionsNextP(AllPurposeIterator* self);
Iterator* allFunctions(Module* module, boolean localP);
Iterator* allPublicFunctions(Module* module, boolean localP);
boolean allVariablesNextP(AllPurposeIterator* self);
Iterator* allVariables(Module* module, boolean localP);
boolean allSurrogatesNextP(AllPurposeIterator* self);
Iterator* allSurrogates(Module* module, boolean localP);
boolean allClassesNextP(AllPurposeIterator* self);
Iterator* allClasses(Module* module, boolean localP);
boolean slotsNextP(AllPurposeIterator* self);
Iterator* allSlots(Module* module, boolean localP);
Iterator* allMethods(Module* module, boolean localP);
Iterator* allPublicMethods(Module* module, boolean localP);
boolean classMethodsNextP(AllPurposeIterator* self);
Iterator* classMethods(Class* clasS, Cons* filters);
Iterator* publicClassMethods(Class* clasS);
Iterator* privateClassMethods(Class* clasS);
boolean classStorageSlotsNextP(AllPurposeIterator* self);
Iterator* classStorageSlots(Class* clasS, Cons* filters);
boolean classTablesNextP(AllPurposeIterator* self);
Iterator* classTables(Class* clasS, Cons* filters);
Iterator* publicClassStorageSlots(Class* clasS);
Iterator* privateClassStorageSlots(Class* clasS);
CrossProductIterator* newCrossProductIterator();
Object* accessCrossProductIteratorSlotValue(CrossProductIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
CrossProductIterator* allocateCrossProductIterator(Cons* domains);
void helpStartupIterators1();
void helpStartupIterators2();
void startupIterators();

// Auxiliary global declarations:
extern Symbol* SYM_ITERATORS_STELLA_SLOT_AUXILIARYp;
extern Surrogate* SGT_ITERATORS_STELLA_TABLE;
extern Surrogate* SGT_ITERATORS_STELLA_CROSS_PRODUCT_ITERATOR;
extern Symbol* SYM_ITERATORS_STELLA_DOMAINS;
extern Symbol* SYM_ITERATORS_STELLA_CURSORS;
extern Symbol* SYM_ITERATORS_STELLA_STARTUP_ITERATORS;
extern Symbol* SYM_ITERATORS_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
