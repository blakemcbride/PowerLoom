//  -*- Mode: C++ -*-

// memoize.hh

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
class MemoizationTable : public StandardObject {
// Table that maps argument values onto computed results for
// one individual memoization site.
public:
  // The table holding the memoized values.
  // We use an integer table, since we explicitly compute a hash code by combining
  // hash codes of argument values.
  IntegerHashTable* hashTable;
  // The surrogate used to point to this table.
  // Used at the memoization site for quick memo table lookup.
  Surrogate* tableName;
  // Marker value used to indicate valid memoized entries.
  // This marker changes everytime one of the `timestamps' gets bumped.
  Cons* currentTimestamp;
  // Names of timestamps that trigger invalidation of
  // memoized entries when they get bumped.
  Cons* timestamps;
public:
  virtual Surrogate* primaryType();
};

class MruMemoizationTable : public MemoizationTable {
public:
  Vector* mruBucketsVector;
  Vector* lruBucketsVector;
  Object** mruBuckets;
  Object** lruBuckets;
  Cons* mruTimestamp;
  Cons* lruTimestamp;
  int nofBuckets;
  int freeEntries;
  int maxEntries;
public:
  virtual Surrogate* primaryType();
};

class MemoizableIterator : public Iterator {
// Iterator class with value buffering that can be used to memoize some
// `base-iterator' without having to generate all its values first.  The
// memoized iterator needs to be cloned to allow multiple iterations over
// the collection represented by the memoized iterator.  Use the following
// idiom to memoize some arbitrary iterator and return a properly cloned value:
// 	 
//  (clone-memoized-iterator
//    (memoize (...) <options>*
//             (new MEMOIZABLE-ITERATOR
//                  :base-iterator <base-iterator>)))
// 	
// This will ensure that <base-iterator> is exhausted exactly once even if
// there are multiple clones for the same memoized value, and that each value
// is generated as late as absolutely possible.  THIS IS NOT YET THREAD SAFE!
public:
  // This slot is only needed to pass the base iterator
  // to the constructor.  Once `self' is initialized it will be cleared.
  Iterator* baseIterator;
  // Holds the base iterator and the values generated
  // so far.  This slot is structure shared between the memoized iterator and
  // all its clones to make sure everybody sees any new values generated by
  // any one of the clones, and that everybody can see when the base iterator
  // is exhausted.
  Cons* iteratorAndValues;
  // Trailing cursor to the list of values generated
  // so far.  Once the end of the list is reached this slot is used to add new
  // values to the end of `iterator-and-values'.
  Cons* cursor;
public:
  virtual boolean nextP();
  virtual AbstractIterator* allocateIterator();
  virtual void initializeMemoizableIterator();
  virtual Surrogate* primaryType();
};


// Global declarations:
extern List* oALL_MEMOIZATION_TABLESo;
extern boolean oMEMOIZATION_ENABLEDpo;
extern Symbol* MEMOIZED_NULL_VALUE;
extern int oTOTAL_MEMOIZATION_LOOKUPSo;
extern int oFAILED_MEMOIZATION_LOOKUPSo;

// Function signatures:
MemoizationTable* newMemoizationTable();
Object* accessMemoizationTableSlotValue(MemoizationTable* self, Symbol* slotname, Object* value, boolean setvalueP);
void enableMemoization();
void disableMemoization();
int hashMemoizedArguments(Object* arg1, Object* arg2, Object* arg3, Object* arg4, int eqvector);
int hashMemoizedArgumentsn(Cons* tuple, int eqvector);
Cons* makeMemoizedValueEntry(Object* value, Object* arg1, Object* arg2, Object* arg3, Object* arg4);
Cons* makeMemoizedValueEntryn(Object* value, Cons* args);
Cons* findMemoizedValueEntry(Cons* bucket, Object* arg1, Object* arg2, Object* arg3, Object* arg4, int eqvector, boolean deleteentryP);
Cons* findMemoizedValueEntryn(Cons* bucket, Cons* tuple, int eqvector, boolean deleteentryP);
Cons* lookupMemoizedValue(MemoizationTable* memotable, Object* arg1, Object* arg2, Object* arg3, Object* arg4, int eqvector);
Cons* lookupMemoizedValuen(MemoizationTable* memotable, Cons* args, int eqvector);
MruMemoizationTable* newMruMemoizationTable();
Object* accessMruMemoizationTableSlotValue(MruMemoizationTable* self, Symbol* slotname, Object* value, boolean setvalueP);
void initializeMruBucketTables(MruMemoizationTable* memotable);
Cons* lookupMruMemoizedValue(MruMemoizationTable* memotable, Object* arg1, Object* arg2, Object* arg3, Object* arg4, int eqvector);
Cons* lookupMruMemoizedValuen(MruMemoizationTable* memotable, Cons* args, int eqvector);
void initializeMemoizationTable(Surrogate* memotablesurrogate, const char* options);
void clearAllMemoizationTables();
void clearMemoizationTables(Keyword* timestampname);
void bumpMemoizationTimestamp(Keyword* timestampname);
Surrogate* makeMemoizationTableSurrogate(Symbol* memoname);
PropertyList* parseMemoizeOptions(Cons* options);
Object* memoize(Cons* inputargs, Cons* body);
MemoizableIterator* newMemoizableIterator(Iterator* baseIterator);
Object* accessMemoizableIteratorSlotValue(MemoizableIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
Iterator* cloneMemoizedIterator(MemoizableIterator* self);
void helpStartupMemoize1();
void startupMemoize();

// Auxiliary global declarations:
extern Surrogate* SGT_MEMOIZE_STELLA_MEMOIZATION_TABLE;
extern Symbol* SYM_MEMOIZE_STELLA_HASH_TABLE;
extern Symbol* SYM_MEMOIZE_STELLA_TABLE_NAME;
extern Symbol* SYM_MEMOIZE_STELLA_CURRENT_TIMESTAMP;
extern Symbol* SYM_MEMOIZE_STELLA_TIMESTAMPS;
extern Surrogate* SGT_MEMOIZE_STELLA_MRU_MEMOIZATION_TABLE;
extern Symbol* SYM_MEMOIZE_STELLA_MRU_BUCKETS_VECTOR;
extern Symbol* SYM_MEMOIZE_STELLA_LRU_BUCKETS_VECTOR;
extern Symbol* SYM_MEMOIZE_STELLA_MRU_TIMESTAMP;
extern Symbol* SYM_MEMOIZE_STELLA_LRU_TIMESTAMP;
extern Symbol* SYM_MEMOIZE_STELLA_NOF_BUCKETS;
extern Symbol* SYM_MEMOIZE_STELLA_FREE_ENTRIES;
extern Symbol* SYM_MEMOIZE_STELLA_MAX_ENTRIES;
extern Keyword* KWD_MEMOIZE_MAX_VALUES;
extern Keyword* KWD_MEMOIZE_TIMESTAMPS;
extern Keyword* KWD_MEMOIZE_NAME;
extern Surrogate* SGT_MEMOIZE_STELLA_GENERALIZED_SYMBOL;
extern Surrogate* SGT_MEMOIZE_STELLA_STANDARD_OBJECT;
extern Surrogate* SGT_MEMOIZE_STELLA_BOOLEAN_WRAPPER;
extern Surrogate* SGT_MEMOIZE_STELLA_BOOLEAN;
extern Symbol* SYM_MEMOIZE_STELLA_LOOKUP_MEMOIZED_VALUE;
extern Symbol* SYM_MEMOIZE_STELLA_LOOKUP_MEMOIZED_VALUEN;
extern Symbol* SYM_MEMOIZE_STELLA_LOOKUP_MRU_MEMOIZED_VALUE;
extern Symbol* SYM_MEMOIZE_STELLA_LOOKUP_MRU_MEMOIZED_VALUEN;
extern Surrogate* SGT_MEMOIZE_STELLA_OBJECT;
extern Symbol* SYM_MEMOIZE_STELLA_MEMOIZED_NULL_VALUE;
extern Symbol* SYM_MEMOIZE_STELLA_NULL;
extern Symbol* SYM_MEMOIZE_STELLA_CONS_LIST;
extern Symbol* SYM_MEMOIZE_STELLA_VRLET;
extern Symbol* SYM_MEMOIZE_STELLA_MEMOIZATION_TABLE;
extern Symbol* SYM_MEMOIZE_STELLA_CONS;
extern Symbol* SYM_MEMOIZE_STELLA_OBJECT;
extern Symbol* SYM_MEMOIZE_STELLA_WHEN;
extern Symbol* SYM_MEMOIZE_STELLA_oMEMOIZATION_ENABLEDpo;
extern Symbol* SYM_MEMOIZE_STELLA_SETQ;
extern Symbol* SYM_MEMOIZE_STELLA_SURROGATE_VALUE;
extern Symbol* SYM_MEMOIZE_STELLA_NULLp;
extern Symbol* SYM_MEMOIZE_STELLA_INITIALIZE_MEMOIZATION_TABLE;
extern Symbol* SYM_MEMOIZE_STELLA_FIRST;
extern Symbol* SYM_MEMOIZE_STELLA_COND;
extern Symbol* SYM_MEMOIZE_STELLA_DEFINEDp;
extern Symbol* SYM_MEMOIZE_STELLA_EQLp;
extern Symbol* SYM_MEMOIZE_STELLA_OTHERWISE;
extern Symbol* SYM_MEMOIZE_STELLA_SETF;
extern Symbol* SYM_MEMOIZE_STELLA_VALUE;
extern Symbol* SYM_MEMOIZE_STELLA_CHOOSE;
extern Symbol* SYM_MEMOIZE_STELLA_CAST;
extern Surrogate* SGT_MEMOIZE_STELLA_MEMOIZABLE_ITERATOR;
extern Symbol* SYM_MEMOIZE_STELLA_BASE_ITERATOR;
extern Symbol* SYM_MEMOIZE_STELLA_ITERATOR_AND_VALUES;
extern Symbol* SYM_MEMOIZE_STELLA_CURSOR;
extern Symbol* SYM_MEMOIZE_STELLA_STARTUP_MEMOIZE;
extern Symbol* SYM_MEMOIZE_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
