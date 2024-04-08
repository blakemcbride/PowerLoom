//  -*- Mode: C++ -*-

// memoize.cc

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

#include "stella/stella-system.hh"

namespace stella {

MemoizationTable* newMemoizationTable() {
  { MemoizationTable* self = NULL;

    self = new MemoizationTable();
    self->timestamps = NIL;
    self->currentTimestamp = NULL;
    self->tableName = NULL;
    self->hashTable = NULL;
    return (self);
  }
}

Surrogate* MemoizationTable::primaryType() {
  { MemoizationTable* self = this;

    return (SGT_MEMOIZE_STELLA_MEMOIZATION_TABLE);
  }
}

Object* accessMemoizationTableSlotValue(MemoizationTable* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_MEMOIZE_STELLA_HASH_TABLE) {
    if (setvalueP) {
      self->hashTable = ((IntegerHashTable*)(value));
    }
    else {
      value = self->hashTable;
    }
  }
  else if (slotname == SYM_MEMOIZE_STELLA_TABLE_NAME) {
    if (setvalueP) {
      self->tableName = ((Surrogate*)(value));
    }
    else {
      value = self->tableName;
    }
  }
  else if (slotname == SYM_MEMOIZE_STELLA_CURRENT_TIMESTAMP) {
    if (setvalueP) {
      self->currentTimestamp = ((Cons*)(value));
    }
    else {
      value = self->currentTimestamp;
    }
  }
  else if (slotname == SYM_MEMOIZE_STELLA_TIMESTAMPS) {
    if (setvalueP) {
      self->timestamps = ((Cons*)(value));
    }
    else {
      value = self->timestamps;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

// Holds all currently active memoization tables for timestamp
// maintenance and clearance purposes.
List* oALL_MEMOIZATION_TABLESo = NULL;

boolean oMEMOIZATION_ENABLEDpo = false;

void enableMemoization() {
  // Enable memoization and use of memoized expression results.
  oMEMOIZATION_ENABLEDpo = true;
}

void disableMemoization() {
  // Enable memoization and use of memoized expression results.
  oMEMOIZATION_ENABLEDpo = false;
}

// Used by memoization to indicate that a NULL value
// was cached.  Needed to distinguish between an undefined value and a
// cached NULL.
Symbol* MEMOIZED_NULL_VALUE = NULL;

int oTOTAL_MEMOIZATION_LOOKUPSo = 0;

int oFAILED_MEMOIZATION_LOOKUPSo = 0;

int hashMemoizedArguments(Object* arg1, Object* arg2, Object* arg3, Object* arg4, int eqvector) {
  { int hashcode = 0;

    if (eqvector < 0) {
      if (!((boolean)(arg1))) {
        arg1 = MEMOIZED_NULL_VALUE;
      }
      hashcode = (size_t)arg1;
      for (;;) {
        if (arg2 == MEMOIZED_NULL_VALUE) {
          break;
        }
        if (!((boolean)(arg2))) {
          arg2 = MEMOIZED_NULL_VALUE;
        }
        hashcode = (((hashcode & 1) == 0) ? ((unsigned int)hashcode >> 1) : (((hashcode >> 1)) | oINTEGER_MSB_MASKo));
        hashcode = (hashcode ^ ((size_t)arg2));
        if (arg3 == MEMOIZED_NULL_VALUE) {
          break;
        }
        if (!((boolean)(arg3))) {
          arg3 = MEMOIZED_NULL_VALUE;
        }
        hashcode = (((hashcode & 1) == 0) ? ((unsigned int)hashcode >> 1) : (((hashcode >> 1)) | oINTEGER_MSB_MASKo));
        hashcode = (hashcode ^ ((size_t)arg3));
        if (arg4 == MEMOIZED_NULL_VALUE) {
          break;
        }
        if (!((boolean)(arg4))) {
          arg4 = MEMOIZED_NULL_VALUE;
        }
        hashcode = (((hashcode & 1) == 0) ? ((unsigned int)hashcode >> 1) : (((hashcode >> 1)) | oINTEGER_MSB_MASKo));
        hashcode = (hashcode ^ ((size_t)arg4));
        break;
      }
    }
    else {
      if (!((boolean)(arg1))) {
        arg1 = MEMOIZED_NULL_VALUE;
      }
      hashcode = (((eqvector & 1) == 0) ? arg1->hashCode() : (size_t)arg1);
      for (;;) {
        if (arg2 == MEMOIZED_NULL_VALUE) {
          break;
        }
        if (!((boolean)(arg2))) {
          arg2 = MEMOIZED_NULL_VALUE;
        }
        hashcode = (((hashcode & 1) == 0) ? ((unsigned int)hashcode >> 1) : (((hashcode >> 1)) | oINTEGER_MSB_MASKo));
        hashcode = (hashcode ^ ((((eqvector & 2) == 0) ? arg2->hashCode() : (size_t)arg2)));
        if (arg3 == MEMOIZED_NULL_VALUE) {
          break;
        }
        if (!((boolean)(arg3))) {
          arg3 = MEMOIZED_NULL_VALUE;
        }
        hashcode = (((hashcode & 1) == 0) ? ((unsigned int)hashcode >> 1) : (((hashcode >> 1)) | oINTEGER_MSB_MASKo));
        hashcode = (hashcode ^ ((((eqvector & 4) == 0) ? arg3->hashCode() : (size_t)arg3)));
        if (arg4 == MEMOIZED_NULL_VALUE) {
          break;
        }
        if (!((boolean)(arg4))) {
          arg4 = MEMOIZED_NULL_VALUE;
        }
        hashcode = (((hashcode & 1) == 0) ? ((unsigned int)hashcode >> 1) : (((hashcode >> 1)) | oINTEGER_MSB_MASKo));
        hashcode = (hashcode ^ ((((eqvector & 8) == 0) ? arg4->hashCode() : (size_t)arg4)));
        break;
      }
    }
    return (hashcode);
  }
}

int hashMemoizedArgumentsn(Cons* tuple, int eqvector) {
  { int hashcode = 0;

    if (eqvector < 0) {
      { Object* arg = NULL;
        Cons* iter000 = tuple;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          arg = iter000->value;
          if (!((boolean)(arg))) {
            arg = MEMOIZED_NULL_VALUE;
          }
          hashcode = (((hashcode & 1) == 0) ? ((unsigned int)hashcode >> 1) : (((hashcode >> 1)) | oINTEGER_MSB_MASKo));
          hashcode = (hashcode ^ ((size_t)arg));
        }
      }
    }
    else {
      { Object* arg = NULL;
        Cons* iter001 = tuple;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          arg = iter001->value;
          if (!((boolean)(arg))) {
            arg = MEMOIZED_NULL_VALUE;
          }
          hashcode = (((hashcode & 1) == 0) ? ((unsigned int)hashcode >> 1) : (((hashcode >> 1)) | oINTEGER_MSB_MASKo));
          hashcode = (hashcode ^ ((((eqvector & 1) == 0) ? arg->hashCode() : (size_t)arg)));
          eqvector = (eqvector >> 1);
        }
      }
    }
    return (hashcode);
  }
}

Cons* makeMemoizedValueEntry(Object* value, Object* arg1, Object* arg2, Object* arg3, Object* arg4) {
  { Cons* entry = NIL;
    Cons* cursor = NIL;
    Cons* cell = NIL;

    entry = new Cons();
    entry->value = value;
    cell = new Cons();
    entry->rest = cell;
    cell->value = arg1;
    if (arg2 == MEMOIZED_NULL_VALUE) {
      cell->rest = NIL;
      return (entry);
    }
    cursor = cell;
    cell = new Cons();
    cursor->rest = cell;
    cell->value = arg2;
    if (arg3 == MEMOIZED_NULL_VALUE) {
      cell->rest = NIL;
      return (entry);
    }
    cursor = cell;
    cell = new Cons();
    cursor->rest = cell;
    cell->value = arg3;
    if (arg4 == MEMOIZED_NULL_VALUE) {
      cell->rest = NIL;
      return (entry);
    }
    cursor = cell;
    cell = new Cons();
    cursor->rest = cell;
    cell->value = arg4;
    cell->rest = NIL;
    return (entry);
  }
}

Cons* makeMemoizedValueEntryn(Object* value, Cons* args) {
  return (cons(value, args));
}

Cons* findMemoizedValueEntry(Cons* bucket, Object* arg1, Object* arg2, Object* arg3, Object* arg4, int eqvector, boolean deleteentryP) {
  { Cons* entries = bucket->rest;
    Cons* args = NIL;
    Cons* result = NULL;

    if (eqvector < 0) {
      while (!(entries == NIL)) {
        args = ((Cons*)(entries->value))->rest;
        if (args->value == arg1) {
          if (arg2 == MEMOIZED_NULL_VALUE) {
            result = ((Cons*)(entries->value));
            break;
          }
          args = args->rest;
          if (args->value == arg2) {
            if (arg3 == MEMOIZED_NULL_VALUE) {
              result = ((Cons*)(entries->value));
              break;
            }
            args = args->rest;
            if (args->value == arg3) {
              if (arg4 == MEMOIZED_NULL_VALUE) {
                result = ((Cons*)(entries->value));
                break;
              }
              args = args->rest;
              if (args->value == arg4) {
                result = ((Cons*)(entries->value));
                break;
              }
            }
          }
        }
        entries = entries->rest;
      }
    }
    else {
      { Object* arg = NULL;

        while (!(entries == NIL)) {
          args = ((Cons*)(entries->value))->rest;
          arg = args->value;
          if ((arg == arg1) ||
              (((eqvector & 1) == 0) &&
               (((boolean)(arg)) &&
                (((boolean)(arg1)) &&
                 arg->objectEqlP(arg1))))) {
            if (arg2 == MEMOIZED_NULL_VALUE) {
              result = ((Cons*)(entries->value));
              break;
            }
            args = args->rest;
            arg = args->value;
            if ((arg == arg2) ||
                (((eqvector & 2) == 0) &&
                 (((boolean)(arg)) &&
                  (((boolean)(arg2)) &&
                   arg->objectEqlP(arg2))))) {
              if (arg3 == MEMOIZED_NULL_VALUE) {
                result = ((Cons*)(entries->value));
                break;
              }
              args = args->rest;
              arg = args->value;
              if ((arg == arg3) ||
                  (((eqvector & 4) == 0) &&
                   (((boolean)(arg)) &&
                    (((boolean)(arg3)) &&
                     arg->objectEqlP(arg3))))) {
                if (arg4 == MEMOIZED_NULL_VALUE) {
                  result = ((Cons*)(entries->value));
                  break;
                }
                args = args->rest;
                arg = args->value;
                if ((arg == arg4) ||
                    (((eqvector & 8) == 0) &&
                     (((boolean)(arg)) &&
                      (((boolean)(arg4)) &&
                       arg->objectEqlP(arg4))))) {
                  result = ((Cons*)(entries->value));
                  break;
                }
              }
            }
          }
          entries = entries->rest;
        }
      }
    }
    if (deleteentryP &&
        ((boolean)(result))) {
      entries->value = ((Cons*)(bucket->rest->value));
      if ((bucket->rest = bucket->rest->rest) == NIL) {
        bucket->rest = NIL;
      }
    }
    return (result);
  }
}

Cons* findMemoizedValueEntryn(Cons* bucket, Cons* tuple, int eqvector, boolean deleteentryP) {
  { Cons* entries = bucket->rest;
    Cons* result = NULL;

    if (eqvector < 0) {
      while (!(entries == NIL)) {
        { boolean alwaysP000 = true;

          { Object* entryarg = NULL;
            Cons* iter000 = ((Cons*)(entries->value))->rest;
            Object* inputarg = NULL;
            Cons* iter001 = tuple;

            for  (; (!(iter000 == NIL)) &&
                      (!(iter001 == NIL)); 
                  iter000 = iter000->rest,
                  iter001 = iter001->rest) {
              entryarg = iter000->value;
              inputarg = iter001->value;
              if (!(entryarg == inputarg)) {
                alwaysP000 = false;
                break;
              }
            }
          }
          if (alwaysP000) {
            result = ((Cons*)(entries->value));
            break;
          }
        }
        entries = entries->rest;
      }
    }
    else {
      while (!(entries == NIL)) {
        result = ((Cons*)(entries->value));
        { Object* entryarg = NULL;
          Cons* iter002 = result->rest;
          Object* inputarg = NULL;
          Cons* iter003 = tuple;

          for  (; (!(iter002 == NIL)) &&
                    (!(iter003 == NIL)); 
                iter002 = iter002->rest,
                iter003 = iter003->rest) {
            entryarg = iter002->value;
            inputarg = iter003->value;
            if ((entryarg == inputarg) ||
                (((eqvector & 1) == 0) &&
                 eqlP(entryarg, inputarg))) {
              eqvector = (eqvector >> 1);
            }
            else {
              result = NULL;
              break;
            }
          }
        }
        if (((boolean)(result))) {
          break;
        }
        else {
          entries = entries->rest;
        }
      }
    }
    if (deleteentryP &&
        ((boolean)(result))) {
      entries->value = ((Cons*)(bucket->rest->value));
      if ((bucket->rest = bucket->rest->rest) == NIL) {
        bucket->rest = NIL;
      }
    }
    return (result);
  }
}

Cons* lookupMemoizedValue(MemoizationTable* memotable, Object* arg1, Object* arg2, Object* arg3, Object* arg4, int eqvector) {
  { IntegerHashTable* hashtable = memotable->hashTable;
    Cons* timestamp = NULL;
    int hashcode = 0;
    Cons* entry = NIL;
    Cons* bucket = NIL;

    if (!((boolean)(hashtable))) {
      hashtable = newIntegerHashTable();
      memotable->hashTable = hashtable;
      memotable->currentTimestamp = cons(NULL, NIL);
    }
    timestamp = memotable->currentTimestamp;
    hashcode = hashMemoizedArguments(arg1, arg2, arg3, arg4, eqvector);
    bucket = ((Cons*)(hashtable->lookup(hashcode)));
    if (((boolean)(bucket))) {
      if (((Cons*)(bucket->value)) == timestamp) {
        entry = findMemoizedValueEntry(bucket, arg1, arg2, arg3, arg4, eqvector, false);
        if (((boolean)(entry))) {
          return (entry);
        }
      }
      else {
        bucket->value = timestamp;
        bucket->rest = NIL;
      }
    }
    entry = makeMemoizedValueEntry(NULL, arg1, arg2, arg3, arg4);
    if (((boolean)(bucket))) {
      bucket->rest = cons(entry, bucket->rest);
    }
    else {
      hashtable->insertAt(hashcode, cons(timestamp, cons(entry, NIL)));
    }
    return (entry);
  }
}

Cons* lookupMemoizedValuen(MemoizationTable* memotable, Cons* args, int eqvector) {
  { IntegerHashTable* hashtable = memotable->hashTable;
    Cons* timestamp = NULL;
    int hashcode = 0;
    Cons* entry = NIL;
    Cons* bucket = NIL;

    if (!((boolean)(hashtable))) {
      hashtable = newIntegerHashTable();
      memotable->hashTable = hashtable;
      memotable->currentTimestamp = cons(NULL, NIL);
    }
    timestamp = memotable->currentTimestamp;
    hashcode = hashMemoizedArgumentsn(args, eqvector);
    bucket = ((Cons*)(hashtable->lookup(hashcode)));
    if (((boolean)(bucket))) {
      if (((Cons*)(bucket->value)) == timestamp) {
        entry = findMemoizedValueEntryn(bucket, args, eqvector, false);
        if (((boolean)(entry))) {
          return (entry);
        }
      }
      else {
        bucket->value = timestamp;
        bucket->rest = NIL;
      }
    }
    entry = cons(NULL, args);
    if (((boolean)(bucket))) {
      bucket->rest = cons(entry, bucket->rest);
    }
    else {
      hashtable->insertAt(hashcode, cons(timestamp, cons(entry, NIL)));
    }
    return (entry);
  }
}

MruMemoizationTable* newMruMemoizationTable() {
  { MruMemoizationTable* self = NULL;

    self = new MruMemoizationTable();
    self->timestamps = NIL;
    self->currentTimestamp = NULL;
    self->tableName = NULL;
    self->hashTable = NULL;
    self->maxEntries = NULL_INTEGER;
    self->freeEntries = NULL_INTEGER;
    self->nofBuckets = NULL_INTEGER;
    self->lruTimestamp = NULL;
    self->mruTimestamp = NULL;
    self->lruBuckets = NULL;
    self->mruBuckets = NULL;
    self->lruBucketsVector = NULL;
    self->mruBucketsVector = NULL;
    return (self);
  }
}

Surrogate* MruMemoizationTable::primaryType() {
  { MruMemoizationTable* self = this;

    return (SGT_MEMOIZE_STELLA_MRU_MEMOIZATION_TABLE);
  }
}

Object* accessMruMemoizationTableSlotValue(MruMemoizationTable* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_MEMOIZE_STELLA_MRU_BUCKETS_VECTOR) {
    if (setvalueP) {
      self->mruBucketsVector = ((Vector*)(value));
    }
    else {
      value = self->mruBucketsVector;
    }
  }
  else if (slotname == SYM_MEMOIZE_STELLA_LRU_BUCKETS_VECTOR) {
    if (setvalueP) {
      self->lruBucketsVector = ((Vector*)(value));
    }
    else {
      value = self->lruBucketsVector;
    }
  }
  else if (slotname == SYM_MEMOIZE_STELLA_MRU_TIMESTAMP) {
    if (setvalueP) {
      self->mruTimestamp = ((Cons*)(value));
    }
    else {
      value = self->mruTimestamp;
    }
  }
  else if (slotname == SYM_MEMOIZE_STELLA_LRU_TIMESTAMP) {
    if (setvalueP) {
      self->lruTimestamp = ((Cons*)(value));
    }
    else {
      value = self->lruTimestamp;
    }
  }
  else if (slotname == SYM_MEMOIZE_STELLA_NOF_BUCKETS) {
    if (setvalueP) {
      self->nofBuckets = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->nofBuckets);
    }
  }
  else if (slotname == SYM_MEMOIZE_STELLA_FREE_ENTRIES) {
    if (setvalueP) {
      self->freeEntries = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->freeEntries);
    }
  }
  else if (slotname == SYM_MEMOIZE_STELLA_MAX_ENTRIES) {
    if (setvalueP) {
      self->maxEntries = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->maxEntries);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

void initializeMruBucketTables(MruMemoizationTable* memotable) {
  memotable->nofBuckets = pickHashTableSizePrime(memotable->maxEntries);
  memotable->mruBucketsVector = stella::newVector(memotable->nofBuckets);
  memotable->lruBucketsVector = stella::newVector(memotable->nofBuckets);
  memotable->mruBuckets = memotable->mruBucketsVector->theArray;
  memotable->lruBuckets = memotable->lruBucketsVector->theArray;
  memotable->freeEntries = memotable->maxEntries;
  memotable->currentTimestamp = cons(NULL, NIL);
  memotable->mruTimestamp = memotable->currentTimestamp;
  memotable->lruTimestamp = memotable->currentTimestamp;
}

Cons* lookupMruMemoizedValue(MruMemoizationTable* memotable, Object* arg1, Object* arg2, Object* arg3, Object* arg4, int eqvector) {
  { Object** mrubuckets = memotable->mruBuckets;
    Object** lrubuckets = NULL;
    Cons* mrubucket = NIL;
    Cons* lrubucket = NIL;
    Cons* mrutimestamp = NULL;
    int hashcode = 0;
    int bucketindex = 0;
    Cons* entry = NULL;

    if (mrubuckets == NULL) {
      initializeMruBucketTables(memotable);
      mrubuckets = memotable->mruBuckets;
    }
    mrutimestamp = memotable->mruTimestamp;
    if (!(memotable->currentTimestamp == mrutimestamp)) {
      mrutimestamp = memotable->currentTimestamp;
      memotable->mruTimestamp = mrutimestamp;
      memotable->lruTimestamp = mrutimestamp;
      memotable->freeEntries = memotable->maxEntries;
    }
    hashcode = hashMemoizedArguments(arg1, arg2, arg3, arg4, eqvector);
    bucketindex = (((unsigned int) hashcode) % (memotable->nofBuckets));
    mrubucket = ((Cons*)(mrubuckets[bucketindex]));
    if (((boolean)(mrubucket))) {
      if (((Cons*)(mrubucket->value)) == mrutimestamp) {
        entry = findMemoizedValueEntry(mrubucket, arg1, arg2, arg3, arg4, eqvector, false);
        if (((boolean)(entry))) {
          return (entry);
        }
      }
      else {
        mrubucket->value = mrutimestamp;
        mrubucket->rest = NIL;
      }
    }
    lrubuckets = memotable->lruBuckets;
    lrubucket = ((Cons*)(lrubuckets[bucketindex]));
    if (((boolean)(lrubucket))) {
      if (((Cons*)(lrubucket->value)) == memotable->lruTimestamp) {
        entry = findMemoizedValueEntry(lrubucket, arg1, arg2, arg3, arg4, eqvector, true);
      }
      else {
        lrubucket->rest = NIL;
      }
    }
    if (!((boolean)(entry))) {
      entry = makeMemoizedValueEntry(NULL, arg1, arg2, arg3, arg4);
    }
    if (((boolean)(mrubucket))) {
      mrubucket->rest = cons(entry, mrubucket->rest);
    }
    else {
      mrubuckets[bucketindex] = (cons(mrutimestamp, cons(entry, NIL)));
    }
    if ((memotable->freeEntries = memotable->freeEntries - 1) == 0) {
      memotable->mruBuckets = lrubuckets;
      memotable->lruBuckets = mrubuckets;
      memotable->mruTimestamp = cons(NULL, NIL);
      memotable->currentTimestamp = memotable->mruTimestamp;
      memotable->lruTimestamp = mrutimestamp;
      memotable->freeEntries = memotable->maxEntries;
    }
    return (entry);
  }
}

Cons* lookupMruMemoizedValuen(MruMemoizationTable* memotable, Cons* args, int eqvector) {
  { Object** mrubuckets = memotable->mruBuckets;
    Object** lrubuckets = NULL;
    Cons* mrubucket = NIL;
    Cons* lrubucket = NIL;
    Cons* mrutimestamp = NULL;
    int hashcode = 0;
    int bucketindex = 0;
    Cons* entry = NULL;

    if (mrubuckets == NULL) {
      initializeMruBucketTables(memotable);
      mrubuckets = memotable->mruBuckets;
    }
    mrutimestamp = memotable->mruTimestamp;
    if (!(memotable->currentTimestamp == mrutimestamp)) {
      mrutimestamp = memotable->currentTimestamp;
      memotable->mruTimestamp = mrutimestamp;
      memotable->lruTimestamp = mrutimestamp;
      memotable->freeEntries = memotable->maxEntries;
    }
    hashcode = hashMemoizedArgumentsn(args, eqvector);
    bucketindex = (((unsigned int) hashcode) % (memotable->nofBuckets));
    mrubucket = ((Cons*)(mrubuckets[bucketindex]));
    if (((boolean)(mrubucket))) {
      if (((Cons*)(mrubucket->value)) == mrutimestamp) {
        entry = findMemoizedValueEntryn(mrubucket, args, eqvector, false);
        if (((boolean)(entry))) {
          return (entry);
        }
      }
      else {
        mrubucket->value = mrutimestamp;
        mrubucket->rest = NIL;
      }
    }
    lrubuckets = memotable->lruBuckets;
    lrubucket = ((Cons*)(lrubuckets[bucketindex]));
    if (((boolean)(lrubucket))) {
      if (((Cons*)(lrubucket->value)) == memotable->lruTimestamp) {
        entry = findMemoizedValueEntryn(lrubucket, args, eqvector, true);
      }
      else {
        lrubucket->rest = NIL;
      }
    }
    if (!((boolean)(entry))) {
      entry = cons(NULL, args);
    }
    if (((boolean)(mrubucket))) {
      mrubucket->rest = cons(entry, mrubucket->rest);
    }
    else {
      mrubuckets[bucketindex] = (cons(mrutimestamp, cons(entry, NIL)));
    }
    if ((memotable->freeEntries = memotable->freeEntries - 1) == 0) {
      memotable->mruBuckets = lrubuckets;
      memotable->lruBuckets = mrubuckets;
      memotable->mruTimestamp = cons(NULL, NIL);
      memotable->currentTimestamp = memotable->mruTimestamp;
      memotable->lruTimestamp = mrutimestamp;
      memotable->freeEntries = memotable->maxEntries;
    }
    return (entry);
  }
}

void initializeMemoizationTable(Surrogate* memotablesurrogate, const char* options) {
  { PropertyList* self000 = newPropertyList();

    self000->thePlist = ((Cons*)(readSExpressionFromString(options)));
    { PropertyList* theoptions = self000;
      Object* oldtable = memotablesurrogate->surrogateValue;
      IntegerWrapper* size = ((IntegerWrapper*)(theoptions->lookup(KWD_MEMOIZE_MAX_VALUES)));

      { MemoizationTable* chooseValue000 = NULL;

        if (((boolean)(size))) {
          { MruMemoizationTable* self001 = newMruMemoizationTable();

            self001->maxEntries = size->wrapperValue;
            chooseValue000 = self001;
          }
        }
        else {
          chooseValue000 = newMemoizationTable();
        }
        { MemoizationTable* table = chooseValue000;

          table->tableName = memotablesurrogate;
          if (((boolean)(theoptions->lookup(KWD_MEMOIZE_TIMESTAMPS)))) {
            table->timestamps = ((Cons*)(theoptions->lookup(KWD_MEMOIZE_TIMESTAMPS)));
          }
          oALL_MEMOIZATION_TABLESo->remove(((MemoizationTable*)(oldtable)));
          oALL_MEMOIZATION_TABLESo->insert(table);
          memotablesurrogate->surrogateValue = table;
        }
      }
    }
  }
}

void clearAllMemoizationTables() {
  { MemoizationTable* table = NULL;
    Cons* iter000 = oALL_MEMOIZATION_TABLESo->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      table = ((MemoizationTable*)(iter000->value));
      table->tableName->surrogateValue = NULL;
    }
  }
  oALL_MEMOIZATION_TABLESo->clear();
}

void clearMemoizationTables(Keyword* timestampname) {
  { MemoizationTable* table = NULL;
    Cons* iter000 = oALL_MEMOIZATION_TABLESo->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      table = ((MemoizationTable*)(iter000->value));
      { boolean foundP000 = false;

        { Keyword* ts = NULL;
          Cons* iter001 = table->timestamps;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            ts = ((Keyword*)(iter001->value));
            if (ts == timestampname) {
              foundP000 = true;
              break;
            }
          }
        }
        if (foundP000) {
          if (subtypeOfP(safePrimaryType(table), SGT_MEMOIZE_STELLA_MRU_MEMOIZATION_TABLE)) {
            { MemoizationTable* table000 = table;
              MruMemoizationTable* table = ((MruMemoizationTable*)(table000));

              if (((boolean)(table->mruBucketsVector))) {
                table->mruBucketsVector->clear();
              }
              if (((boolean)(table->lruBucketsVector))) {
                table->lruBucketsVector->clear();
              }
              table->freeEntries = table->maxEntries;
            }
          }
          else {
            table->hashTable = NULL;
          }
        }
      }
    }
  }
}

void bumpMemoizationTimestamp(Keyword* timestampname) {
  { MemoizationTable* table = NULL;
    Cons* iter000 = oALL_MEMOIZATION_TABLESo->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      table = ((MemoizationTable*)(iter000->value));
      { boolean foundP000 = false;

        { Keyword* ts = NULL;
          Cons* iter001 = table->timestamps;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            ts = ((Keyword*)(iter001->value));
            if (ts == timestampname) {
              foundP000 = true;
              break;
            }
          }
        }
        if (foundP000) {
          table->currentTimestamp = cons(NULL, NIL);
        }
      }
    }
  }
}

Surrogate* makeMemoizationTableSurrogate(Symbol* memoname) {
  if (!((boolean)(memoname))) {
    memoname = methodGensym("MEMO-TABLE");
  }
  return (memoname->surrogatify());
}

PropertyList* parseMemoizeOptions(Cons* options) {
  { PropertyList* self000 = newPropertyList();

    self000->thePlist = options;
    { PropertyList* givenoptions = self000;
      PropertyList* parsedoptions = newPropertyList();

      { Object* key = NULL;
        Object* value = NULL;
        Cons* iter000 = givenoptions->thePlist;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest->rest) {
          key = iter000->value;
          value = iter000->rest->value;
          { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(key));

            if (testValue000 == KWD_MEMOIZE_TIMESTAMPS) {
              if (!consP(value)) {
                value = cons(value, NIL);
              }
              { boolean testValue001 = false;

                { boolean alwaysP000 = true;

                  { Object* ts = NULL;
                    Cons* iter001 = ((Cons*)(value));

                    for (; !(iter001 == NIL); iter001 = iter001->rest) {
                      ts = iter001->value;
                      if (!keywordP(ts)) {
                        alwaysP000 = false;
                        break;
                      }
                    }
                  }
                  testValue001 = alwaysP000;
                }
                testValue001 = !testValue001;
                if (testValue001) {
                  { 
                    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                    signalTranslationError();
                    if (!(suppressWarningsP())) {
                      printErrorContext(">> ERROR: ", STANDARD_ERROR);
                      *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal :timestamp value in memoize: " << "`" << deUglifyParseTree(value) << "'" << "." << std::endl;
                    }
                  }
                }
                else {
                  parsedoptions->insertAt(key, value);
                }
              }
            }
            else if (testValue000 == KWD_MEMOIZE_NAME) {
              if (!isaP(value, SGT_MEMOIZE_STELLA_GENERALIZED_SYMBOL)) {
                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  signalTranslationError();
                  if (!(suppressWarningsP())) {
                    printErrorContext(">> ERROR: ", STANDARD_ERROR);
                    *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal :name value in memoize: " << "`" << deUglifyParseTree(value) << "'" << "." << std::endl;
                  }
                }
              }
              else {
                parsedoptions->insertAt(key, makeMemoizationTableSurrogate(internDerivedSymbol(((GeneralizedSymbol*)(value)), ((GeneralizedSymbol*)(value))->symbolName)));
              }
            }
            else if (testValue000 == KWD_MEMOIZE_MAX_VALUES) {
              if (!integerP(value)) {
                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  signalTranslationError();
                  if (!(suppressWarningsP())) {
                    printErrorContext(">> ERROR: ", STANDARD_ERROR);
                    *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal :max-values value in memoize: " << "`" << deUglifyParseTree(value) << "'" << "." << std::endl;
                  }
                }
              }
              else {
                parsedoptions->insertAt(key, value);
              }
            }
            else {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal memoize option: " << "`" << deUglifyParseTree(key) << "'" << "." << std::endl;
                }
              }
            }
          }
        }
      }
      return (parsedoptions);
    }
  }
}

Object* memoize(Cons* inputargs, Cons* body) {
  // Compute the value of an expression and memoize it relative to
  //    the values of `inputArgs'.
  // `inputArgs' should characterize the complete set of values upon which
  //    the computation of the result depended.
  // Calls to `memoize' should be of the form
  // 
  //       (memoize (<arg>+) {:<option> <value>}* <expression>)
  // 
  //    and have the status of an expression.
  //    The following options are supported:
  // 
  //       :timestamps   A single or list of keywords specifying the names of
  //                     timestamps which when bumped should invalidate all
  //                     entries currently memoized in this table.
  //       :name         Names the memoization table so it can be shared by other
  //                     memoization sites.  By default, a gensymed name is used.
  //                     CAUTION: IT IS ASSUMED THAT ALL ENTRIES IN A MEMOZATION
  //                     TABLE DEPEND ON THE SAME NUMBER OF ARGUMENTS!!
  //       :max-values   The maximum number of values to be memoized.  Only the
  //                     `:max-values' most recently used values will be kept
  //                     in the memoization table, older values will be discarded
  //                     and recomputed if needed.  Without a `:max-values'
  //                     specification, the memoization table will grow
  //                     indefinitely.
  // 
  // PERFORMANCE NOTES: For most efficient lookup, input arguments that vary the most
  // should be listed first.  Also, arguments of type STANDARD-OBJECT (and all its
  // subtypes) can be memoized more efficiently than arguments of type OBJECT or
  // wrapped literals (with the exception of BOOLEANs).
  { StandardObject* dummy1;
    StandardObject* dummy2;

    { Surrogate* memoname = NULL;
      Symbol* memotablevar = localGensym("MEMO-TABLE");
      Symbol* memoentryvar = localGensym("MEMOIZED-ENTRY");
      Symbol* memovaluevar = localGensym("MEMOIZED-VALUE");
      int nofinputs = inputargs->length();
      PropertyList* options = NULL;
      Object* lookupfunction = NULL;
      Cons* lookuptree = NIL;
      StandardObject* valuetypespec = NULL;
      boolean alleqP = true;
      int eqvector = 0;

      body = cons(NIL, body);
      options = parseMemoizeOptions(extractOptions(body, NULL));
      body = body->rest;
      memoname = ((Surrogate*)(options->lookup(KWD_MEMOIZE_NAME)));
      if (!((boolean)(memoname))) {
        memoname = makeMemoizationTableSurrogate(NULL);
      }
      { ConsIterator* it = inputargs->allocateIterator();
        int index = NULL_INTEGER;
        int iter000 = 0;

        for  (; it->nextP(); 
              iter000 = iter000 + 1) {
          index = iter000;
          { Object* walkedarg = NULL;
            StandardObject* type = NULL;

            walkedarg = walkATree(it->value, type);
            if (subTypeSpecOfP(type, SGT_MEMOIZE_STELLA_STANDARD_OBJECT) ||
                (subTypeSpecOfP(type, SGT_MEMOIZE_STELLA_BOOLEAN_WRAPPER) ||
                 subTypeSpecOfP(type, SGT_MEMOIZE_STELLA_BOOLEAN))) {
              if (index < 12) {
                eqvector = (eqvector | ((1 << index)));
              }
            }
            else {
              alleqP = false;
            }
            it->valueSetter(sysTree(walkedarg, type, dummy1));
          }
        }
      }
      lookupfunction = ((!((boolean)(options->lookup(KWD_MEMOIZE_MAX_VALUES)))) ? (((nofinputs <= 4) ? SYM_MEMOIZE_STELLA_LOOKUP_MEMOIZED_VALUE : SYM_MEMOIZE_STELLA_LOOKUP_MEMOIZED_VALUEN)) : (((nofinputs <= 4) ? SYM_MEMOIZE_STELLA_LOOKUP_MRU_MEMOIZED_VALUE : SYM_MEMOIZE_STELLA_LOOKUP_MRU_MEMOIZED_VALUEN)));
      switch (nofinputs) {
        case 0: 
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing memoization input argument specification" << "." << std::endl;
            }
          }
          return (walkDontCallMeTree(body, SGT_MEMOIZE_STELLA_OBJECT, dummy2));
        case 1: 
          lookuptree = cons(lookupfunction, cons(memotablevar, cons(inputargs->value, listO(5, SYM_MEMOIZE_STELLA_MEMOIZED_NULL_VALUE, SYM_MEMOIZE_STELLA_NULL, SYM_MEMOIZE_STELLA_NULL, (alleqP ? wrapInteger(-1) : wrapInteger(eqvector)), NIL))));
          break;
        case 2: 
          lookuptree = cons(lookupfunction, cons(memotablevar, cons(inputargs->value, cons(inputargs->rest->value, listO(4, SYM_MEMOIZE_STELLA_MEMOIZED_NULL_VALUE, SYM_MEMOIZE_STELLA_NULL, (alleqP ? wrapInteger(-1) : wrapInteger(eqvector)), NIL)))));
          break;
        case 3: 
          lookuptree = cons(lookupfunction, cons(memotablevar, cons(inputargs->value, cons(inputargs->rest->value, cons(inputargs->rest->rest->value, listO(3, SYM_MEMOIZE_STELLA_MEMOIZED_NULL_VALUE, (alleqP ? wrapInteger(-1) : wrapInteger(eqvector)), NIL))))));
          break;
        case 4: 
          lookuptree = cons(lookupfunction, cons(memotablevar, cons(inputargs->value, cons(inputargs->rest->value, cons(inputargs->rest->rest->value, cons(inputargs->fourth(), cons((alleqP ? wrapInteger(-1) : wrapInteger(eqvector)), NIL)))))));
          break;
        default:
          lookuptree = cons(lookupfunction, cons(memotablevar, listO(3, cons(SYM_MEMOIZE_STELLA_CONS_LIST, inputargs->concatenate(NIL, 0)), (alleqP ? wrapInteger(-1) : wrapInteger(eqvector)), NIL)));
          break;
      }
      valuetypespec = computeExpressionType(body->value, true);
      return (listO(6, SYM_MEMOIZE_STELLA_VRLET, listO(4, cons(memotablevar, listO(3, SYM_MEMOIZE_STELLA_MEMOIZATION_TABLE, SYM_MEMOIZE_STELLA_NULL, NIL)), cons(memoentryvar, listO(3, SYM_MEMOIZE_STELLA_CONS, SYM_MEMOIZE_STELLA_NULL, NIL)), cons(memovaluevar, listO(3, SYM_MEMOIZE_STELLA_OBJECT, SYM_MEMOIZE_STELLA_NULL, NIL)), NIL), listO(7, SYM_MEMOIZE_STELLA_WHEN, SYM_MEMOIZE_STELLA_oMEMOIZATION_ENABLEDpo, listO(3, SYM_MEMOIZE_STELLA_SETQ, memotablevar, cons(listO(3, SYM_MEMOIZE_STELLA_SURROGATE_VALUE, memoname, NIL), NIL)), listO(5, SYM_MEMOIZE_STELLA_WHEN, listO(3, SYM_MEMOIZE_STELLA_NULLp, memotablevar, NIL), listO(3, SYM_MEMOIZE_STELLA_INITIALIZE_MEMOIZATION_TABLE, memoname, cons(wrapString(stringify(options->thePlist)), NIL)), listO(3, SYM_MEMOIZE_STELLA_SETQ, memotablevar, cons(listO(3, SYM_MEMOIZE_STELLA_SURROGATE_VALUE, memoname, NIL), NIL)), NIL), listO(3, SYM_MEMOIZE_STELLA_SETQ, memoentryvar, cons(lookuptree, NIL)), listO(3, SYM_MEMOIZE_STELLA_SETQ, memovaluevar, cons(listO(3, SYM_MEMOIZE_STELLA_FIRST, memoentryvar, NIL), NIL)), NIL), listO(4, SYM_MEMOIZE_STELLA_COND, listO(3, listO(3, SYM_MEMOIZE_STELLA_DEFINEDp, memovaluevar, NIL), listO(4, SYM_MEMOIZE_STELLA_WHEN, listO(3, SYM_MEMOIZE_STELLA_EQLp, memovaluevar, cons(SYM_MEMOIZE_STELLA_MEMOIZED_NULL_VALUE, NIL)), listO(3, SYM_MEMOIZE_STELLA_SETQ, memovaluevar, cons(SYM_MEMOIZE_STELLA_NULL, NIL)), NIL), NIL), listO(4, SYM_MEMOIZE_STELLA_OTHERWISE, listO(3, SYM_MEMOIZE_STELLA_SETQ, memovaluevar, body->concatenate(NIL, 0)), listO(4, SYM_MEMOIZE_STELLA_WHEN, SYM_MEMOIZE_STELLA_oMEMOIZATION_ENABLEDpo, listO(4, SYM_MEMOIZE_STELLA_SETF, listO(3, SYM_MEMOIZE_STELLA_VALUE, memoentryvar, NIL), listO(5, SYM_MEMOIZE_STELLA_CHOOSE, listO(3, SYM_MEMOIZE_STELLA_NULLp, memovaluevar, NIL), SYM_MEMOIZE_STELLA_MEMOIZED_NULL_VALUE, memovaluevar, NIL), NIL), NIL), NIL), NIL), listO(3, SYM_MEMOIZE_STELLA_CAST, memovaluevar, cons(yieldTypeSpecTree(valuetypespec), NIL)), NIL));
    }
  }
}

MemoizableIterator* newMemoizableIterator(Iterator* baseIterator) {
  { MemoizableIterator* self = NULL;

    self = new MemoizableIterator();
    self->baseIterator = baseIterator;
    self->firstIterationP = true;
    self->value = NULL;
    self->cursor = NULL;
    self->iteratorAndValues = NULL;
    self->initializeMemoizableIterator();
    return (self);
  }
}

Surrogate* MemoizableIterator::primaryType() {
  { MemoizableIterator* self = this;

    return (SGT_MEMOIZE_STELLA_MEMOIZABLE_ITERATOR);
  }
}

Object* accessMemoizableIteratorSlotValue(MemoizableIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_MEMOIZE_STELLA_BASE_ITERATOR) {
    if (setvalueP) {
      self->baseIterator = ((Iterator*)(value));
    }
    else {
      value = self->baseIterator;
    }
  }
  else if (slotname == SYM_MEMOIZE_STELLA_ITERATOR_AND_VALUES) {
    if (setvalueP) {
      self->iteratorAndValues = ((Cons*)(value));
    }
    else {
      value = self->iteratorAndValues;
    }
  }
  else if (slotname == SYM_MEMOIZE_STELLA_CURSOR) {
    if (setvalueP) {
      self->cursor = ((Cons*)(value));
    }
    else {
      value = self->cursor;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

void MemoizableIterator::initializeMemoizableIterator() {
  { MemoizableIterator* self = this;

    { Cons* iterandvalues = cons(self->baseIterator, NIL);

      self->iteratorAndValues = iterandvalues;
      self->cursor = iterandvalues;
      self->baseIterator = NULL;
    }
  }
}

Iterator* cloneMemoizedIterator(MemoizableIterator* self) {
  // Clone the memoized iterator `self' so it can be used to
  // iterate over the collection represented by `self', while allowing to iterate
  // over it multiple times via multiple clones.
  { Cons* iterandvalues = self->iteratorAndValues;

    if (((boolean)(iterandvalues->value))) {
      { MemoizableIterator* child = new MemoizableIterator();

        child->firstIterationP = true;
        child->iteratorAndValues = iterandvalues;
        child->cursor = iterandvalues;
        return (child);
      }
    }
    else {
      return (iterandvalues->rest->allocateIterator());
    }
  }
}

AbstractIterator* MemoizableIterator::allocateIterator() {
  // Alias for `clone-memoized-iterator'.
  { MemoizableIterator* self = this;

    return (cloneMemoizedIterator(self));
  }
}

boolean MemoizableIterator::nextP() {
  // Generate the next value of the memoized iterator `self' (or
  // one of its clones) by either using one of the values generated so far or by
  // generating and saving the next value of the `base-iterator'.
  { MemoizableIterator* self = this;

    { Iterator* iterator = NULL;
      Cons* cursor = self->cursor;
      Cons* values = cursor->rest;

      if (!(values == NIL)) {
        self->value = values->value;
        self->cursor = values;
        return (true);
      }
      iterator = ((Iterator*)(self->iteratorAndValues->value));
      if (((boolean)(iterator))) {
        if (iterator->nextP()) {
          self->value = iterator->value;
          cursor->rest = cons(self->value, NIL);
          self->cursor = cursor->rest;
          return (true);
        }
        self->iteratorAndValues->firstSetter(NULL);
      }
      return (false);
    }
  }
}

void helpStartupMemoize1() {
  {
    SGT_MEMOIZE_STELLA_MEMOIZATION_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("MEMOIZATION-TABLE", NULL, 1)));
    SYM_MEMOIZE_STELLA_HASH_TABLE = ((Symbol*)(internRigidSymbolWrtModule("HASH-TABLE", NULL, 0)));
    SYM_MEMOIZE_STELLA_TABLE_NAME = ((Symbol*)(internRigidSymbolWrtModule("TABLE-NAME", NULL, 0)));
    SYM_MEMOIZE_STELLA_CURRENT_TIMESTAMP = ((Symbol*)(internRigidSymbolWrtModule("CURRENT-TIMESTAMP", NULL, 0)));
    SYM_MEMOIZE_STELLA_TIMESTAMPS = ((Symbol*)(internRigidSymbolWrtModule("TIMESTAMPS", NULL, 0)));
    SGT_MEMOIZE_STELLA_MRU_MEMOIZATION_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("MRU-MEMOIZATION-TABLE", NULL, 1)));
    SYM_MEMOIZE_STELLA_MRU_BUCKETS_VECTOR = ((Symbol*)(internRigidSymbolWrtModule("MRU-BUCKETS-VECTOR", NULL, 0)));
    SYM_MEMOIZE_STELLA_LRU_BUCKETS_VECTOR = ((Symbol*)(internRigidSymbolWrtModule("LRU-BUCKETS-VECTOR", NULL, 0)));
    SYM_MEMOIZE_STELLA_MRU_TIMESTAMP = ((Symbol*)(internRigidSymbolWrtModule("MRU-TIMESTAMP", NULL, 0)));
    SYM_MEMOIZE_STELLA_LRU_TIMESTAMP = ((Symbol*)(internRigidSymbolWrtModule("LRU-TIMESTAMP", NULL, 0)));
    SYM_MEMOIZE_STELLA_NOF_BUCKETS = ((Symbol*)(internRigidSymbolWrtModule("NOF-BUCKETS", NULL, 0)));
    SYM_MEMOIZE_STELLA_FREE_ENTRIES = ((Symbol*)(internRigidSymbolWrtModule("FREE-ENTRIES", NULL, 0)));
    SYM_MEMOIZE_STELLA_MAX_ENTRIES = ((Symbol*)(internRigidSymbolWrtModule("MAX-ENTRIES", NULL, 0)));
    KWD_MEMOIZE_MAX_VALUES = ((Keyword*)(internRigidSymbolWrtModule("MAX-VALUES", NULL, 2)));
    KWD_MEMOIZE_TIMESTAMPS = ((Keyword*)(internRigidSymbolWrtModule("TIMESTAMPS", NULL, 2)));
    KWD_MEMOIZE_NAME = ((Keyword*)(internRigidSymbolWrtModule("NAME", NULL, 2)));
    SGT_MEMOIZE_STELLA_GENERALIZED_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("GENERALIZED-SYMBOL", NULL, 1)));
    SGT_MEMOIZE_STELLA_STANDARD_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("STANDARD-OBJECT", NULL, 1)));
    SGT_MEMOIZE_STELLA_BOOLEAN_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN-WRAPPER", NULL, 1)));
    SGT_MEMOIZE_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 1)));
    SYM_MEMOIZE_STELLA_LOOKUP_MEMOIZED_VALUE = ((Symbol*)(internRigidSymbolWrtModule("LOOKUP-MEMOIZED-VALUE", NULL, 0)));
    SYM_MEMOIZE_STELLA_LOOKUP_MEMOIZED_VALUEN = ((Symbol*)(internRigidSymbolWrtModule("LOOKUP-MEMOIZED-VALUEN", NULL, 0)));
    SYM_MEMOIZE_STELLA_LOOKUP_MRU_MEMOIZED_VALUE = ((Symbol*)(internRigidSymbolWrtModule("LOOKUP-MRU-MEMOIZED-VALUE", NULL, 0)));
    SYM_MEMOIZE_STELLA_LOOKUP_MRU_MEMOIZED_VALUEN = ((Symbol*)(internRigidSymbolWrtModule("LOOKUP-MRU-MEMOIZED-VALUEN", NULL, 0)));
    SGT_MEMOIZE_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", NULL, 1)));
    SYM_MEMOIZE_STELLA_MEMOIZED_NULL_VALUE = ((Symbol*)(internRigidSymbolWrtModule("MEMOIZED-NULL-VALUE", NULL, 0)));
    SYM_MEMOIZE_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
    SYM_MEMOIZE_STELLA_CONS_LIST = ((Symbol*)(internRigidSymbolWrtModule("CONS-LIST", NULL, 0)));
    SYM_MEMOIZE_STELLA_VRLET = ((Symbol*)(internRigidSymbolWrtModule("VRLET", NULL, 0)));
    SYM_MEMOIZE_STELLA_MEMOIZATION_TABLE = ((Symbol*)(internRigidSymbolWrtModule("MEMOIZATION-TABLE", NULL, 0)));
    SYM_MEMOIZE_STELLA_CONS = ((Symbol*)(internRigidSymbolWrtModule("CONS", NULL, 0)));
    SYM_MEMOIZE_STELLA_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("OBJECT", NULL, 0)));
    SYM_MEMOIZE_STELLA_WHEN = ((Symbol*)(internRigidSymbolWrtModule("WHEN", NULL, 0)));
    SYM_MEMOIZE_STELLA_oMEMOIZATION_ENABLEDpo = ((Symbol*)(internRigidSymbolWrtModule("*MEMOIZATION-ENABLED?*", NULL, 0)));
    SYM_MEMOIZE_STELLA_SETQ = ((Symbol*)(internRigidSymbolWrtModule("SETQ", NULL, 0)));
    SYM_MEMOIZE_STELLA_SURROGATE_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SURROGATE-VALUE", NULL, 0)));
    SYM_MEMOIZE_STELLA_NULLp = ((Symbol*)(internRigidSymbolWrtModule("NULL?", NULL, 0)));
    SYM_MEMOIZE_STELLA_INITIALIZE_MEMOIZATION_TABLE = ((Symbol*)(internRigidSymbolWrtModule("INITIALIZE-MEMOIZATION-TABLE", NULL, 0)));
    SYM_MEMOIZE_STELLA_FIRST = ((Symbol*)(internRigidSymbolWrtModule("FIRST", NULL, 0)));
    SYM_MEMOIZE_STELLA_COND = ((Symbol*)(internRigidSymbolWrtModule("COND", NULL, 0)));
    SYM_MEMOIZE_STELLA_DEFINEDp = ((Symbol*)(internRigidSymbolWrtModule("DEFINED?", NULL, 0)));
    SYM_MEMOIZE_STELLA_EQLp = ((Symbol*)(internRigidSymbolWrtModule("EQL?", NULL, 0)));
    SYM_MEMOIZE_STELLA_OTHERWISE = ((Symbol*)(internRigidSymbolWrtModule("OTHERWISE", NULL, 0)));
    SYM_MEMOIZE_STELLA_SETF = ((Symbol*)(internRigidSymbolWrtModule("SETF", NULL, 0)));
    SYM_MEMOIZE_STELLA_VALUE = ((Symbol*)(internRigidSymbolWrtModule("VALUE", NULL, 0)));
    SYM_MEMOIZE_STELLA_CHOOSE = ((Symbol*)(internRigidSymbolWrtModule("CHOOSE", NULL, 0)));
    SYM_MEMOIZE_STELLA_CAST = ((Symbol*)(internRigidSymbolWrtModule("CAST", NULL, 0)));
    SGT_MEMOIZE_STELLA_MEMOIZABLE_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("MEMOIZABLE-ITERATOR", NULL, 1)));
    SYM_MEMOIZE_STELLA_BASE_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("BASE-ITERATOR", NULL, 0)));
    SYM_MEMOIZE_STELLA_ITERATOR_AND_VALUES = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR-AND-VALUES", NULL, 0)));
    SYM_MEMOIZE_STELLA_CURSOR = ((Symbol*)(internRigidSymbolWrtModule("CURSOR", NULL, 0)));
    SYM_MEMOIZE_STELLA_STARTUP_MEMOIZE = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-MEMOIZE", NULL, 0)));
    SYM_MEMOIZE_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void startupMemoize() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupMemoize1();
    }
    if (currentStartupTimePhaseP(4)) {
      oALL_MEMOIZATION_TABLESo = newList();
      { Symbol* self073 = newSymbol("MEMOIZED-NULL-VALUE");

        self073->homeContext = NULL;
        MEMOIZED_NULL_VALUE = self073;
      }
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("MEMOIZATION-TABLE", "(DEFCLASS MEMOIZATION-TABLE (STANDARD-OBJECT) :DOCUMENTATION \"Table that maps argument values onto computed results for\none individual memoization site.\" :SLOTS ((HASH-TABLE :TYPE (INTEGER-HASH-TABLE OF INTEGER (CONS OF CONS)) :DOCUMENTATION \"The table holding the memoized values.\nWe use an integer table, since we explicitly compute a hash code by combining\nhash codes of argument values.\") (TABLE-NAME :TYPE SURROGATE :DOCUMENTATION \"The surrogate used to point to this table.\nUsed at the memoization site for quick memo table lookup.\") (CURRENT-TIMESTAMP :TYPE CONS :DOCUMENTATION \"Marker value used to indicate valid memoized entries.\nThis marker changes everytime one of the `timestamps' gets bumped.\") (TIMESTAMPS :TYPE (CONS OF KEYWORD) :INITIALLY NIL :DOCUMENTATION \"Names of timestamps that trigger invalidation of\nmemoized entries when they get bumped.\")))");

        clasS->classConstructorCode = ((cpp_function_code)(&newMemoizationTable));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessMemoizationTableSlotValue));
      }
      oMEMOIZATION_ENABLEDpo = true;
      { Class* clasS = defineClassFromStringifiedSource("MRU-MEMOIZATION-TABLE", "(DEFCLASS MRU-MEMOIZATION-TABLE (MEMOIZATION-TABLE) :SLOTS ((MRU-BUCKETS-VECTOR :TYPE (VECTOR OF (CONS OF CONS))) (LRU-BUCKETS-VECTOR :TYPE (VECTOR OF (CONS OF CONS))) (MRU-BUCKETS :TYPE (NATIVE-VECTOR OF (CONS OF CONS))) (LRU-BUCKETS :TYPE (NATIVE-VECTOR OF (CONS OF CONS))) (MRU-TIMESTAMP :TYPE CONS) (LRU-TIMESTAMP :TYPE CONS) (NOF-BUCKETS :TYPE INTEGER) (FREE-ENTRIES :TYPE INTEGER) (MAX-ENTRIES :TYPE INTEGER)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newMruMemoizationTable));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessMruMemoizationTableSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("MEMOIZABLE-ITERATOR", "(DEFCLASS MEMOIZABLE-ITERATOR (ITERATOR) :DOCUMENTATION \"Iterator class with value buffering that can be used to memoize some\n`base-iterator' without having to generate all its values first.  The\nmemoized iterator needs to be cloned to allow multiple iterations over\nthe collection represented by the memoized iterator.  Use the following\nidiom to memoize some arbitrary iterator and return a properly cloned value:\n	 \n (clone-memoized-iterator\n   (memoize (...) <options>*\n            (new MEMOIZABLE-ITERATOR\n                 :base-iterator <base-iterator>)))\n	\nThis will ensure that <base-iterator> is exhausted exactly once even if\nthere are multiple clones for the same memoized value, and that each value\nis generated as late as absolutely possible.  THIS IS NOT YET THREAD SAFE!\" :PUBLIC? TRUE :SLOTS ((BASE-ITERATOR :TYPE ITERATOR :REQUIRED? TRUE :DOCUMENTATION \"This slot is only needed to pass the base iterator\nto the constructor.  Once `self' is initialized it will be cleared.\") (ITERATOR-AND" "-VALUES :TYPE CONS :INITIALLY NULL :DOCUMENTATION \"Holds the base iterator and the values generated\nso far.  This slot is structure shared between the memoized iterator and\nall its clones to make sure everybody sees any new values generated by\nany one of the clones, and that everybody can see when the base iterator\nis exhausted.\") (CURSOR :TYPE CONS :INITIALLY NULL :DOCUMENTATION \"Trailing cursor to the list of values generated\nso far.  Once the end of the list is reached this slot is used to add new\nvalues to the end of `iterator-and-values'.\")) :INITIALIZER INITIALIZE-MEMOIZABLE-ITERATOR)");

        clasS->classConstructorCode = ((cpp_function_code)(&newMemoizableIterator));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessMemoizableIteratorSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("ENABLE-MEMOIZATION", "(DEFUN ENABLE-MEMOIZATION () :COMMAND? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Enable memoization and use of memoized expression results.\")", ((cpp_function_code)(&enableMemoization)), NULL);
      defineFunctionObject("DISABLE-MEMOIZATION", "(DEFUN DISABLE-MEMOIZATION () :COMMAND? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Enable memoization and use of memoized expression results.\")", ((cpp_function_code)(&disableMemoization)), NULL);
      defineFunctionObject("HASH-MEMOIZED-ARGUMENTS", "(DEFUN (HASH-MEMOIZED-ARGUMENTS INTEGER) ((ARG1 OBJECT) (ARG2 OBJECT) (ARG3 OBJECT) (ARG4 OBJECT) (EQVECTOR INTEGER)))", ((cpp_function_code)(&hashMemoizedArguments)), NULL);
      defineFunctionObject("HASH-MEMOIZED-ARGUMENTSN", "(DEFUN (HASH-MEMOIZED-ARGUMENTSN INTEGER) ((TUPLE CONS) (EQVECTOR INTEGER)))", ((cpp_function_code)(&hashMemoizedArgumentsn)), NULL);
      defineFunctionObject("MAKE-MEMOIZED-VALUE-ENTRY", "(DEFUN (MAKE-MEMOIZED-VALUE-ENTRY (CONS OF CONS)) ((VALUE OBJECT) (ARG1 OBJECT) (ARG2 OBJECT) (ARG3 OBJECT) (ARG4 OBJECT)))", ((cpp_function_code)(&makeMemoizedValueEntry)), NULL);
      defineFunctionObject("MAKE-MEMOIZED-VALUE-ENTRYN", "(DEFUN (MAKE-MEMOIZED-VALUE-ENTRYN (CONS OF CONS)) ((VALUE OBJECT) (ARGS CONS)) :GLOBALLY-INLINE? TRUE (RETURN (CONS VALUE ARGS)))", ((cpp_function_code)(&makeMemoizedValueEntryn)), NULL);
      defineFunctionObject("FIND-MEMOIZED-VALUE-ENTRY", "(DEFUN (FIND-MEMOIZED-VALUE-ENTRY CONS) ((BUCKET (CONS OF CONS)) (ARG1 OBJECT) (ARG2 OBJECT) (ARG3 OBJECT) (ARG4 OBJECT) (EQVECTOR INTEGER) (DELETEENTRY? BOOLEAN)))", ((cpp_function_code)(&findMemoizedValueEntry)), NULL);
      defineFunctionObject("FIND-MEMOIZED-VALUE-ENTRYN", "(DEFUN (FIND-MEMOIZED-VALUE-ENTRYN CONS) ((BUCKET (CONS OF CONS)) (TUPLE CONS) (EQVECTOR INTEGER) (DELETEENTRY? BOOLEAN)))", ((cpp_function_code)(&findMemoizedValueEntryn)), NULL);
      defineFunctionObject("LOOKUP-MEMOIZED-VALUE", "(DEFUN (LOOKUP-MEMOIZED-VALUE CONS) ((MEMOTABLE MEMOIZATION-TABLE) (ARG1 OBJECT) (ARG2 OBJECT) (ARG3 OBJECT) (ARG4 OBJECT) (EQVECTOR INTEGER)))", ((cpp_function_code)(&lookupMemoizedValue)), NULL);
      defineFunctionObject("LOOKUP-MEMOIZED-VALUEN", "(DEFUN (LOOKUP-MEMOIZED-VALUEN CONS) ((MEMOTABLE MEMOIZATION-TABLE) (ARGS CONS) (EQVECTOR INTEGER)))", ((cpp_function_code)(&lookupMemoizedValuen)), NULL);
      defineFunctionObject("INITIALIZE-MRU-BUCKET-TABLES", "(DEFUN INITIALIZE-MRU-BUCKET-TABLES ((MEMOTABLE MRU-MEMOIZATION-TABLE)))", ((cpp_function_code)(&initializeMruBucketTables)), NULL);
      defineFunctionObject("LOOKUP-MRU-MEMOIZED-VALUE", "(DEFUN (LOOKUP-MRU-MEMOIZED-VALUE CONS) ((MEMOTABLE MRU-MEMOIZATION-TABLE) (ARG1 OBJECT) (ARG2 OBJECT) (ARG3 OBJECT) (ARG4 OBJECT) (EQVECTOR INTEGER)))", ((cpp_function_code)(&lookupMruMemoizedValue)), NULL);
      defineFunctionObject("LOOKUP-MRU-MEMOIZED-VALUEN", "(DEFUN (LOOKUP-MRU-MEMOIZED-VALUEN CONS) ((MEMOTABLE MRU-MEMOIZATION-TABLE) (ARGS CONS) (EQVECTOR INTEGER)))", ((cpp_function_code)(&lookupMruMemoizedValuen)), NULL);
      defineFunctionObject("INITIALIZE-MEMOIZATION-TABLE", "(DEFUN INITIALIZE-MEMOIZATION-TABLE ((MEMOTABLESURROGATE SURROGATE) (OPTIONS STRING)))", ((cpp_function_code)(&initializeMemoizationTable)), NULL);
      defineFunctionObject("CLEAR-ALL-MEMOIZATION-TABLES", "(DEFUN CLEAR-ALL-MEMOIZATION-TABLES ())", ((cpp_function_code)(&clearAllMemoizationTables)), NULL);
      defineFunctionObject("CLEAR-MEMOIZATION-TABLES", "(DEFUN CLEAR-MEMOIZATION-TABLES ((TIMESTAMPNAME KEYWORD)))", ((cpp_function_code)(&clearMemoizationTables)), NULL);
      defineFunctionObject("BUMP-MEMOIZATION-TIMESTAMP", "(DEFUN BUMP-MEMOIZATION-TIMESTAMP ((TIMESTAMPNAME KEYWORD)))", ((cpp_function_code)(&bumpMemoizationTimestamp)), NULL);
      defineFunctionObject("MAKE-MEMOIZATION-TABLE-SURROGATE", "(DEFUN (MAKE-MEMOIZATION-TABLE-SURROGATE SURROGATE) ((MEMONAME SYMBOL)))", ((cpp_function_code)(&makeMemoizationTableSurrogate)), NULL);
      defineFunctionObject("PARSE-MEMOIZE-OPTIONS", "(DEFUN (PARSE-MEMOIZE-OPTIONS PROPERTY-LIST) ((OPTIONS CONS)))", ((cpp_function_code)(&parseMemoizeOptions)), NULL);
      defineFunctionObject("MEMOIZE", "(DEFUN MEMOIZE ((INPUTARGS CONS) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Compute the value of an expression and memoize it relative to\n   the values of `inputArgs'.\n`inputArgs' should characterize the complete set of values upon which\n   the computation of the result depended.\nCalls to `memoize' should be of the form\n\n      (memoize (<arg>+) {:<option> <value>}* <expression>)\n\n   and have the status of an expression.\n   The following options are supported:\n\n      :timestamps   A single or list of keywords specifying the names of\n                    timestamps which when bumped should invalidate all\n                    entries currently memoized in this table.\n      :name         Names the memoization table so it can be shared by other\n                    memoization sites.  By default, a gensymed name is used.\n                    CAUTION: IT IS ASSUMED THAT ALL ENTRIES IN A MEMOZATION\n                    TABLE DEPEND ON THE SAME NUMBER OF ARGUMENTS!!\n      :max-value" "s   The maximum number of values to be memoized.  Only the\n                    `:max-values' most recently used values will be kept\n                    in the memoization table, older values will be discarded\n                    and recomputed if needed.  Without a `:max-values'\n                    specification, the memoization table will grow\n                    indefinitely.\n\nPERFORMANCE NOTES: For most efficient lookup, input arguments that vary the most\nshould be listed first.  Also, arguments of type STANDARD-OBJECT (and all its\nsubtypes) can be memoized more efficiently than arguments of type OBJECT or\nwrapped literals (with the exception of BOOLEANs).\" :PUBLIC? TRUE)", ((cpp_function_code)(&memoize)), NULL);
      defineMethodObject("(DEFMETHOD INITIALIZE-MEMOIZABLE-ITERATOR ((SELF MEMOIZABLE-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&MemoizableIterator::initializeMemoizableIterator))), NULL);
      defineFunctionObject("CLONE-MEMOIZED-ITERATOR", "(DEFUN (CLONE-MEMOIZED-ITERATOR (ITERATOR OF (LIKE (ANY-VALUE SELF)))) ((SELF MEMOIZABLE-ITERATOR)) :DOCUMENTATION \"Clone the memoized iterator `self' so it can be used to\niterate over the collection represented by `self', while allowing to iterate\nover it multiple times via multiple clones.\" :PUBLIC? TRUE)", ((cpp_function_code)(&cloneMemoizedIterator)), NULL);
      defineMethodObject("(DEFMETHOD (ALLOCATE-ITERATOR (ITERATOR OF (LIKE (ANY-VALUE SELF)))) ((SELF MEMOIZABLE-ITERATOR)) :DOCUMENTATION \"Alias for `clone-memoized-iterator'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&MemoizableIterator::allocateIterator))), NULL);
      defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF MEMOIZABLE-ITERATOR)) :DOCUMENTATION \"Generate the next value of the memoized iterator `self' (or\none of its clones) by either using one of the values generated so far or by\ngenerating and saving the next value of the `base-iterator'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&MemoizableIterator::nextP))), NULL);
      defineFunctionObject("STARTUP-MEMOIZE", "(DEFUN STARTUP-MEMOIZE () :PUBLIC? TRUE)", ((cpp_function_code)(&startupMemoize)), NULL);
      { MethodSlot* function = lookupFunction(SYM_MEMOIZE_STELLA_STARTUP_MEMOIZE);

        setDynamicSlotValue(function->dynamicSlots, SYM_MEMOIZE_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupMemoize"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *ALL-MEMOIZATION-TABLES* (LIST OF MEMOIZATION-TABLE) (NEW LIST) :DOCUMENTATION \"Holds all currently active memoization tables for timestamp\nmaintenance and clearance purposes.\")", &oALL_MEMOIZATION_TABLESo);
      defineGlobalVariableObject("(DEFGLOBAL *MEMOIZATION-ENABLED?* BOOLEAN FALSE)", &oMEMOIZATION_ENABLEDpo);
      defineGlobalVariableObject("(DEFCONSTANT MEMOIZED-NULL-VALUE SYMBOL (NEW SYMBOL :SYMBOL-NAME \"MEMOIZED-NULL-VALUE\" :HOME-CONTEXT NULL) :DOCUMENTATION \"Used by memoization to indicate that a NULL value\nwas cached.  Needed to distinguish between an undefined value and a\ncached NULL.\")", &MEMOIZED_NULL_VALUE);
      defineGlobalVariableObject("(DEFGLOBAL *TOTAL-MEMOIZATION-LOOKUPS* INTEGER 0)", &oTOTAL_MEMOIZATION_LOOKUPSo);
      defineGlobalVariableObject("(DEFGLOBAL *FAILED-MEMOIZATION-LOOKUPS* INTEGER 0)", &oFAILED_MEMOIZATION_LOOKUPSo);
    }
  }
}

Surrogate* SGT_MEMOIZE_STELLA_MEMOIZATION_TABLE = NULL;

Symbol* SYM_MEMOIZE_STELLA_HASH_TABLE = NULL;

Symbol* SYM_MEMOIZE_STELLA_TABLE_NAME = NULL;

Symbol* SYM_MEMOIZE_STELLA_CURRENT_TIMESTAMP = NULL;

Symbol* SYM_MEMOIZE_STELLA_TIMESTAMPS = NULL;

Surrogate* SGT_MEMOIZE_STELLA_MRU_MEMOIZATION_TABLE = NULL;

Symbol* SYM_MEMOIZE_STELLA_MRU_BUCKETS_VECTOR = NULL;

Symbol* SYM_MEMOIZE_STELLA_LRU_BUCKETS_VECTOR = NULL;

Symbol* SYM_MEMOIZE_STELLA_MRU_TIMESTAMP = NULL;

Symbol* SYM_MEMOIZE_STELLA_LRU_TIMESTAMP = NULL;

Symbol* SYM_MEMOIZE_STELLA_NOF_BUCKETS = NULL;

Symbol* SYM_MEMOIZE_STELLA_FREE_ENTRIES = NULL;

Symbol* SYM_MEMOIZE_STELLA_MAX_ENTRIES = NULL;

Keyword* KWD_MEMOIZE_MAX_VALUES = NULL;

Keyword* KWD_MEMOIZE_TIMESTAMPS = NULL;

Keyword* KWD_MEMOIZE_NAME = NULL;

Surrogate* SGT_MEMOIZE_STELLA_GENERALIZED_SYMBOL = NULL;

Surrogate* SGT_MEMOIZE_STELLA_STANDARD_OBJECT = NULL;

Surrogate* SGT_MEMOIZE_STELLA_BOOLEAN_WRAPPER = NULL;

Surrogate* SGT_MEMOIZE_STELLA_BOOLEAN = NULL;

Symbol* SYM_MEMOIZE_STELLA_LOOKUP_MEMOIZED_VALUE = NULL;

Symbol* SYM_MEMOIZE_STELLA_LOOKUP_MEMOIZED_VALUEN = NULL;

Symbol* SYM_MEMOIZE_STELLA_LOOKUP_MRU_MEMOIZED_VALUE = NULL;

Symbol* SYM_MEMOIZE_STELLA_LOOKUP_MRU_MEMOIZED_VALUEN = NULL;

Surrogate* SGT_MEMOIZE_STELLA_OBJECT = NULL;

Symbol* SYM_MEMOIZE_STELLA_MEMOIZED_NULL_VALUE = NULL;

Symbol* SYM_MEMOIZE_STELLA_NULL = NULL;

Symbol* SYM_MEMOIZE_STELLA_CONS_LIST = NULL;

Symbol* SYM_MEMOIZE_STELLA_VRLET = NULL;

Symbol* SYM_MEMOIZE_STELLA_MEMOIZATION_TABLE = NULL;

Symbol* SYM_MEMOIZE_STELLA_CONS = NULL;

Symbol* SYM_MEMOIZE_STELLA_OBJECT = NULL;

Symbol* SYM_MEMOIZE_STELLA_WHEN = NULL;

Symbol* SYM_MEMOIZE_STELLA_oMEMOIZATION_ENABLEDpo = NULL;

Symbol* SYM_MEMOIZE_STELLA_SETQ = NULL;

Symbol* SYM_MEMOIZE_STELLA_SURROGATE_VALUE = NULL;

Symbol* SYM_MEMOIZE_STELLA_NULLp = NULL;

Symbol* SYM_MEMOIZE_STELLA_INITIALIZE_MEMOIZATION_TABLE = NULL;

Symbol* SYM_MEMOIZE_STELLA_FIRST = NULL;

Symbol* SYM_MEMOIZE_STELLA_COND = NULL;

Symbol* SYM_MEMOIZE_STELLA_DEFINEDp = NULL;

Symbol* SYM_MEMOIZE_STELLA_EQLp = NULL;

Symbol* SYM_MEMOIZE_STELLA_OTHERWISE = NULL;

Symbol* SYM_MEMOIZE_STELLA_SETF = NULL;

Symbol* SYM_MEMOIZE_STELLA_VALUE = NULL;

Symbol* SYM_MEMOIZE_STELLA_CHOOSE = NULL;

Symbol* SYM_MEMOIZE_STELLA_CAST = NULL;

Surrogate* SGT_MEMOIZE_STELLA_MEMOIZABLE_ITERATOR = NULL;

Symbol* SYM_MEMOIZE_STELLA_BASE_ITERATOR = NULL;

Symbol* SYM_MEMOIZE_STELLA_ITERATOR_AND_VALUES = NULL;

Symbol* SYM_MEMOIZE_STELLA_CURSOR = NULL;

Symbol* SYM_MEMOIZE_STELLA_STARTUP_MEMOIZE = NULL;

Symbol* SYM_MEMOIZE_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
