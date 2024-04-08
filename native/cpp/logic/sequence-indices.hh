//  -*- Mode: C++ -*-

// sequence-indices.hh

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

// Class definitions:
class SequenceIndex : public StandardObject {
// Abstract class for managing a sequence of objects.
public:
  Cons* theSequence;
  int theSequenceLength;
public:
  virtual void printObject(std::ostream* stream);
  virtual Iterator* allocateIterator();
  virtual Cons* consify();
  virtual SequenceIndex* remove(Object* value);
  virtual SequenceIndex* removeDeletedMembers();
  virtual int estimatedLength();
  virtual boolean emptyP();
  virtual Object* first();
  virtual void push(Object* value);
  virtual void insert(Object* value);
};

class NonPagingIndex : public SequenceIndex {
// Index that manages an always-in-memory data
// strucure containing a sequence of objects.
public:
  virtual Surrogate* primaryType();
  virtual void clear();
  virtual NonPagingIndex* copy();
};

class PagingIndex : public SequenceIndex {
// Index that manages a sequence of objects retrievable from
// persistent storage.  Needs to be appropriately subclassed by actual store
// implementations and facilitated with a proper iterator class.
public:
  Cons* selectionPattern;
  ObjectStore* store;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
  virtual Iterator* allocateIterator();
  virtual SequenceIndex* remove(Object* value);
  virtual SequenceIndex* removeDeletedMembers();
  virtual int estimatedLength();
  virtual void push(Object* value);
  virtual void insert(Object* value);
};

class SequenceIndexIterator : public Iterator {
// Iterator that generates successive members of a sequence index.
public:
  Cons* listIteratorCursor;
public:
  virtual Surrogate* primaryType();
  virtual boolean emptyP();
  virtual boolean nextP();
};

class PagingIndexIterator : public SequenceIndexIterator {
// Iterator that generates successive members of a paging index.
public:
  virtual Surrogate* primaryType();
};

class ObjectStore : public StandardObject {
public:
  Module* module;
public:
  virtual void clearObjectStore();
  virtual void storeModuleTrailer(Module* module);
  virtual void storeModuleHeader(Module* module);
  virtual void storeAssertion(Proposition* proposition);
  virtual void storeRelation(NamedDescription* relation);
  virtual void storeNativeRelation(Relation* relation);
  virtual void updatePropositionInStore(Proposition* proposition, Keyword* updateMode);
  virtual Proposition* fetchDuplicateProposition(Proposition* prop);
  virtual Object* fetchInstance(Object* name);
  virtual NamedDescription* fetchRelation(Object* name);
  virtual SequenceIndex* objectStoreDcreateSequenceIndex(Cons* pattern);
};


// Global declarations:
extern NonPagingIndex* NIL_NON_PAGING_INDEX;
extern PagingIndex* NIL_PAGING_INDEX;
extern List* oALL_OBJECT_STORESo;
extern DECLARE_STELLA_SPECIAL(oLOADINGREGENERABLEOBJECTSpo, boolean );

// Function signatures:
Object* accessSequenceIndexSlotValue(SequenceIndex* self, Symbol* slotname, Object* value, boolean setvalueP);
NonPagingIndex* newNonPagingIndex();
PagingIndex* newPagingIndex();
Object* accessPagingIndexSlotValue(PagingIndex* self, Symbol* slotname, Object* value, boolean setvalueP);
int sequenceIndexDestimatedLength(SequenceIndex* self);
void printSequenceIndex(SequenceIndex* self, std::ostream* stream);
SequenceIndexIterator* newSequenceIndexIterator();
Object* accessSequenceIndexIteratorSlotValue(SequenceIndexIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
void printPagingIndex(PagingIndex* self, std::ostream* stream);
PagingIndexIterator* newPagingIndexIterator();
Object* accessObjectStoreSlotValue(ObjectStore* self, Symbol* slotname, Object* value, boolean setvalueP);
void registerObjectStore(ObjectStore* store);
void unregisterObjectStore(ObjectStore* store);
boolean haveActiveObjectStoresP();
ObjectStore* homeObjectStore(Object* self);
SequenceIndex* createSequenceIndex(Object* self, Cons* pattern);
SequenceIndex* keywordDcreateSequenceIndex(Keyword* kind, Cons* pattern);
SequenceIndex* moduleDcreateSequenceIndex(Module* module, Cons* pattern);
SequenceIndex* maybeWrapSequenceIndex(SequenceIndex* index, Cons* pattern, Keyword* kind, Object* arg1, Object* arg2);
void helpStartupSequenceIndices1();
void startupSequenceIndices();

// Auxiliary global declarations:
extern Symbol* SYM_SEQUENCE_INDICES_LOGIC_SELECTION_PATTERN;
extern Symbol* SYM_SEQUENCE_INDICES_LOGIC_THE_SEQUENCE;
extern Symbol* SYM_SEQUENCE_INDICES_LOGIC_THE_SEQUENCE_LENGTH;
extern Surrogate* SGT_SEQUENCE_INDICES_LOGIC_NON_PAGING_INDEX;
extern Surrogate* SGT_SEQUENCE_INDICES_LOGIC_PAGING_INDEX;
extern Symbol* SYM_SEQUENCE_INDICES_LOGIC_STORE;
extern Surrogate* SGT_SEQUENCE_INDICES_LOGIC_SEQUENCE_INDEX_ITERATOR;
extern Symbol* SYM_SEQUENCE_INDICES_STELLA_LIST_ITERATOR_CURSOR;
extern Surrogate* SGT_SEQUENCE_INDICES_LOGIC_PAGING_INDEX_ITERATOR;
extern Symbol* SYM_SEQUENCE_INDICES_STELLA_MODULE;
extern Symbol* SYM_SEQUENCE_INDICES_LOGIC_OBJECT_STORE;
extern Surrogate* SGT_SEQUENCE_INDICES_STELLA_MODULE;
extern Surrogate* SGT_SEQUENCE_INDICES_LOGIC_OBJECT_STORE;
extern Keyword* KWD_SEQUENCE_INDICES_PAGING;
extern Keyword* KWD_SEQUENCE_INDICES_NON_PAGING;
extern Symbol* SYM_SEQUENCE_INDICES_LOGIC_STARTUP_SEQUENCE_INDICES;
extern Symbol* SYM_SEQUENCE_INDICES_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
