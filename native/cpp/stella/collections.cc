//  -*- Mode: C++ -*-

// collections.cc

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

boolean Collection::memberP(Object* object) {
  // Return true iff `object' is a member of the collection `self'.
  { Collection* self = this;

    { Object* i = NULL;
      Iterator* iter000 = ((Iterator*)(self->allocateIterator()));

      for (; iter000->nextP(); ) {
        i = iter000->value;
        if (eqlP(i, object)) {
          return (true);
        }
      }
    }
    return (false);
  }
}

boolean stellaCollectionP(Object* self) {
  // Return `true' if `self' is a native collection.
  return (isaP(self, SGT_COLLECTIONS_STELLA_COLLECTION));
}

boolean Collection::noDuplicatesP() {
  // Return `true' if the collection `self' forbids duplicate values.
  { Collection* self = this;

    return (false);
  }
}

boolean Set::noDuplicatesP() {
  { Set* self = this;

    return (true);
  }
}

boolean Collection::orderedP() {
  // Return `true' if the collection `self' is ordered.
  { Collection* self = this;

    return (false);
  }
}

boolean Sequence::orderedP() {
  { Sequence* self = this;

    return (true);
  }
}

boolean Set::orderedP() {
  { Set* self = this;

    return (false);
  }
}

void Set::insert(Object* value) {
  // Add `value' to the set `self' unless it is already a member.
  { Set* self = this;

    if (!self->memberP(value)) {
      self->theConsList = cons(value, self->theConsList);
    }
  }
}

void Set::push(Object* value) {
  // Add `value' to the front of set `self' unless it is already a member.
  { Set* self = this;

    if (!self->memberP(value)) {
      self->theConsList = cons(value, self->theConsList);
    }
  }
}

void Set::insertLast(Object* value) {
  // Add `value' to the end of set `self' unless it is already a member.
  { Set* self = this;

    if (!self->memberP(value)) {
      { Cons* cursor = self->theConsList;
        Cons* lastcons = cons(value, NIL);

        if (cursor == NIL) {
          self->theConsList = lastcons;
        }
        else {
          addConsToEndOfConsList(cursor, lastcons);
        }
      }
    }
  }
}

Collection* Set::removeDuplicates() {
  { Set* self = this;

    return (self);
  }
}

List* Set::substitute(Object* neW, Object* old) {
  // Destructively replace `old' with `new' in the set `self'
  // unless `new' is already a member.
  { Set* self = this;

    if (!self->memberP(neW)) {
      self->theConsList = self->theConsList->substitute(neW, old);
    }
    return (self);
  }
}

List* Set::concatenate(List* set2, int othersets, ...) {
  // Union `set2' and all `otherSets' onto the end of `set1'.
  // The operation is destructive wrt `set1', but leaves all other sets intact.
  // The two mandatory parameters allow us to optimize the common binary case by
  // not relying on the somewhat less efficient variable arguments mechanism.
  { Set* set1 = this;

    { Cons* resultset = set1->theConsList;

      { Object* elt = NULL;
        Cons* iter000 = set2->theConsList;
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          elt = iter000->value;
          if (!resultset->memberP(elt)) {
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(elt, NIL);
                if (resultset == NIL) {
                  resultset = collect000;
                }
                else {
                  addConsToEndOfConsList(resultset, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(elt, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
      }
      if (othersets > 0) {
        { va_list iter001;
          int iter001Count = othersets;
          List* oset = NULL;

          va_start(iter001, othersets);
                    for  (; (iter001Count--) > 0; ) {
            oset = va_arg(iter001, List*);
            { Object* elt = NULL;
              Cons* iter002 = oset->theConsList;
              Cons* collect001 = NULL;

              for  (; !(iter002 == NIL); 
                    iter002 = iter002->rest) {
                elt = iter002->value;
                if (!resultset->memberP(elt)) {
                  if (!((boolean)(collect001))) {
                    {
                      collect001 = cons(elt, NIL);
                      if (resultset == NIL) {
                        resultset = collect001;
                      }
                      else {
                        addConsToEndOfConsList(resultset, collect001);
                      }
                    }
                  }
                  else {
                    {
                      collect001->rest = cons(elt, NIL);
                      collect001 = collect001->rest;
                    }
                  }
                }
              }
            }
          }
          va_end(iter001);
        }
      }
      set1->theConsList = resultset;
      return (set1);
    }
  }
}

boolean Set::objectEqualP(Object* y) {
  // Return TRUE iff `x' and `y' are SET's with equivalent members.
  // Uses `equal?' to test equality of elements.  This is more general than
  // `equivalent-sets?', since that only uses an `eql?' test.
  { Set* x = this;

    if (subtypeOfP(safePrimaryType(y), SGT_COLLECTIONS_STELLA_SET)) {
      { Object* y000 = y;
        Set* y = ((Set*)(y000));

        { boolean testValue000 = false;

          testValue000 = x->length() == y->length();
          if (testValue000) {
            { boolean alwaysP000 = true;

              { Object* eltx = NULL;
                ListIterator* iter000 = ((ListIterator*)(x->allocateIterator()));

                for (; iter000->nextP(); ) {
                  eltx = iter000->value;
                  { boolean testValue001 = false;

                    { boolean foundP000 = false;

                      { Object* elty = NULL;
                        ListIterator* iter001 = ((ListIterator*)(y->allocateIterator()));

                        for (; iter001->nextP(); ) {
                          elty = iter001->value;
                          if (equalP(eltx, elty)) {
                            foundP000 = true;
                            break;
                          }
                        }
                      }
                      testValue001 = foundP000;
                    }
                    testValue001 = !testValue001;
                    if (testValue001) {
                      alwaysP000 = false;
                      break;
                    }
                  }
                }
              }
              testValue000 = alwaysP000;
            }
          }
          { boolean value000 = testValue000;

            return (value000);
          }
        }
      }
    }
    else {
    }
    return (false);
  }
}

int Set::equalHashCode() {
  // Return an `equal?' hash code for `self'.  Note that this
  // is O(N) in the number of elements of `self'.
  { Set* self = this;

    { Cons* cursor = self->theConsList;
      int code = 95880665;

      for (;;) {
        if (cursor == NIL) {
          break;
        }
        code = (code ^ (safeEqualHashCode(cursor->value)));
        cursor = cursor->rest;
      }
      return (code);
    }
  }
}

Set* set(int values, ...) {
  // Return a set containing `values', in order.
  { Set* set = newSet();

    { va_list iter000;
      int iter000Count = values;
      Object* v = NULL;
      Cons* collect000 = NULL;

      va_start(iter000, values);
            for  (; (iter000Count--) > 0; ) {
        v = va_arg(iter000, Object*);
        if (!set->memberP(v)) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(v, NIL);
              if (set->theConsList == NIL) {
                set->theConsList = collect000;
              }
              else {
                addConsToEndOfConsList(set->theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(v, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      va_end(iter000);
    }
    return (set);
  }
}

void Vector::printVector(std::ostream* stream) {
  { Vector* self = this;

    if (self->length() == 0) {
      *(stream) << "|i|[]";
    }
    else {
      { int i = 0;
        int limit = 9;

        *(stream) << "|i|[";
        { Object* element = NULL;
          Vector* vector000 = self;
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            element = (vector000->theArray)[index000];
            *(stream) << element;
            i = i + 1;
            if (i > limit) {
              break;
            }
            if (i < self->length()) {
              *(stream) << " ";
            }
          }
        }
        if ((i <= limit) ||
            (i == self->length())) {
          *(stream) << "]";
        }
        else {
          *(stream) << " ...]";
        }
      }
    }
  }
}

boolean Vector::emptyP() {
  // Return `true' if `self' has length 0.
  { Vector* self = this;

    return (self->arraySize == 0);
  }
}

boolean Vector::nonEmptyP() {
  // Return `true' if `self' has length > 0.
  { Vector* self = this;

    return (self->arraySize > 0);
  }
}

Object* Vector::first() {
  { Vector* self = this;

    return ((self->theArray)[0]);
  }
}

Object* Vector::second() {
  { Vector* self = this;

    return ((self->theArray)[1]);
  }
}

Object* Vector::third() {
  { Vector* self = this;

    return ((self->theArray)[2]);
  }
}

Object* Vector::fourth() {
  { Vector* self = this;

    return ((self->theArray)[3]);
  }
}

Object* Vector::fifth() {
  { Vector* self = this;

    return ((self->theArray)[4]);
  }
}

Object* Vector::nth(int position) {
  { Vector* self = this;

    return ((self->theArray)[position]);
  }
}

Object* Vector::last() {
  // Return the last item in the vector `self'.
  { Vector* self = this;

    return ((self->theArray)[(self->arraySize - 1)]);
  }
}

Object* Vector::firstSetter(Object* value) {
  { Vector* self = this;

    return ((self->theArray)[0] = value);
  }
}

Object* Vector::secondSetter(Object* value) {
  { Vector* self = this;

    return ((self->theArray)[1] = value);
  }
}

Object* Vector::thirdSetter(Object* value) {
  { Vector* self = this;

    return ((self->theArray)[2] = value);
  }
}

Object* Vector::fourthSetter(Object* value) {
  { Vector* self = this;

    return ((self->theArray)[3] = value);
  }
}

Object* Vector::fifthSetter(Object* value) {
  { Vector* self = this;

    return ((self->theArray)[4] = value);
  }
}

Object* Vector::nthSetter(Object* value, int position) {
  { Vector* self = this;

    return ((self->theArray)[position] = value);
  }
}

Object* Vector::lastSetter(Object* value) {
  { Vector* self = this;

    return ((self->theArray)[(self->arraySize - 1)] = value);
  }
}

int Vector::length() {
  { Vector* self = this;

    return (self->arraySize);
  }
}

boolean Vector::memberP(Object* object) {
  { Vector* self = this;

    { Object** array = self->theArray;

      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = self->length() - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          if (eqlP(array[i], object)) {
            return (true);
          }
        }
      }
      return (false);
    }
  }
}

int Vector::position(Object* object, int start) {
  // Return the position of `object' within the vector
  // `self' (counting from zero); or return `null' if `object' does not occur within 
  // `self' (uses an `eql?' test).  If `start' was supplied as non-`null', only 
  // consider the portion starting at `start', however, the returned position 
  // will always be relative to the entire vector.
  { Vector* self = this;

    if (start == NULL_INTEGER) {
      start = 0;
    }
    { int i = NULL_INTEGER;
      int iter000 = start;
      int upperBound000 = self->length() - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        if (eqlP((self->theArray)[i], object)) {
          return (i);
        }
      }
    }
    return (NULL_INTEGER);
  }
}

int Vector::lastPosition(Object* object, int end) {
  // Return the position of `object' within the vector
  // `self' (counting from zero); or return `null' if `object' does not occur within 
  // `self' (uses an `eql?' test).  If `end' was supplied as non-`null', only 
  // consider the portion ending at index `end', however, the returned position 
  // will always be relative to the entire vector.
  { Vector* self = this;

    if (end == NULL_INTEGER) {
      end = self->length() - 1;
    }
    { int i = NULL_INTEGER;
      ReverseIntegerIntervalIterator* iter000 = interval(0, end)->reverse();

      for (; iter000->nextP(); ) {
        i = iter000->value;
        if (eqlP((self->theArray)[i], object)) {
          return (i);
        }
      }
    }
    return (NULL_INTEGER);
  }
}

void Vector::insertAt(int offset, Object* value) {
  { Vector* self = this;

    if (offset >= self->arraySize) {
      throw *newStellaException("Out-of-bounds array access");
    }
    (self->theArray)[offset] = value;
  }
}

Vector* Vector::copy() {
  // Return a copy of the vector `self'.
  { Vector* self = this;

    { int size = self->arraySize;
      Object** sourcearray = self->theArray;
      Vector* copy = stella::newVector(size);
      Object** copyarray = copy->theArray;

      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = size - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          copyarray[i] = (sourcearray[i]);
        }
      }
      return (copy);
    }
  }
}

void Vector::clear() {
  { Vector* self = this;

    { int size = self->arraySize;
      Object** array = self->theArray;

      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = size - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          array[i] = NULL;
        }
      }
    }
  }
}

Vector* vector(int values, ...) {
  // Return a vector containing `values', in order.
  { Vector* vector = stella::newVector(values);

    { va_list iter000;
      int iter000Count = values;
      Object* v = NULL;
      int i = NULL_INTEGER;
      int iter001 = 0;

      va_start(iter000, values);
            for  (; (iter000Count--) > 0; 
            iter001 = iter001 + 1) {
        v = va_arg(iter000, Object*);
        i = iter001;
        (vector->theArray)[i] = v;
      }
      va_end(iter000);
    }
    return (vector);
  }
}

boolean Vector::objectEqualP(Object* y) {
  // Return TRUE iff the vectors `x' and `y' are structurally
  // equivalent.  Uses `equal?' to test equality of elements.
  { Vector* x = this;

    if (subtypeOfP(safePrimaryType(y), SGT_COLLECTIONS_STELLA_VECTOR)) {
      { Object* y000 = y;
        Vector* y = ((Vector*)(y000));

        if (x->arraySize == y->arraySize) {
          { Object* eltx = NULL;
            Vector* vector000 = x;
            int index000 = 0;
            int length000 = vector000->length();
            Object* elty = NULL;
            Vector* vector001 = y;
            int index001 = 0;
            int length001 = vector001->length();

            for  (; (index000 < length000) &&
                      (index001 < length001); 
                  index000 = index000 + 1,
                  index001 = index001 + 1) {
              eltx = (vector000->theArray)[index000];
              elty = (vector001->theArray)[index001];
              if (!equalP(eltx, elty)) {
                return (false);
              }
            }
          }
          return (true);
        }
      }
    }
    else {
    }
    return (false);
  }
}

int Vector::equalHashCode() {
  // Return an `equal?' hash code for `self'.
  { Vector* self = this;

    { int cursor = self->length();
      int code = 66435053;

      for (;;) {
        if (cursor == 0) {
          break;
        }
        else {
          cursor = cursor - 1;
        }
        code = (code ^ (safeEqualHashCode((self->theArray)[cursor])));
        code = (((code & 1) == 0) ? ((unsigned int)code >> 1) : (((code >> 1)) | oINTEGER_MSB_MASKo));
      }
      return (code);
    }
  }
}

void ExtensibleVector::insertAt(int offset, Object* value) {
  { ExtensibleVector* self = this;

    if (offset >= self->arraySize) {
      { int size = self->arraySize;

        while (offset >= size) {
          size = 2 * size;
        }
        resizeVector(self, size);
      }
    }
    (self->theArray)[offset] = value;
  }
}

void ExtensibleSymbolArray::insertAt(int offset, Object* value) {
  { ExtensibleSymbolArray* self = this;

    if (offset >= self->arraySize) {
      { int size = self->arraySize;

        while (offset >= size) {
          size = 2 * size;
        }
        resizeVector(self, size);
      }
    }
    (self->theArray)[offset] = value;
    if (offset > self->topSymbolOffset) {
      self->topSymbolOffset = offset;
    }
  }
}

boolean VectorSequence::emptyP() {
  // Return `true' if `self' has length 0.
  { VectorSequence* self = this;

    return (self->sequenceLength == 0);
  }
}

boolean VectorSequence::nonEmptyP() {
  // Return `true' if `self' has length > 0.
  { VectorSequence* self = this;

    return (self->sequenceLength > 0);
  }
}

int VectorSequence::length() {
  { VectorSequence* self = this;

    return (self->sequenceLength);
  }
}

Object* VectorSequence::last() {
  // Return the last item in the vector `self'.
  { VectorSequence* self = this;

    return ((self->theArray)[(self->sequenceLength - 1)]);
  }
}

Object* VectorSequence::lastSetter(Object* value) {
  { VectorSequence* self = this;

    return ((self->theArray)[(self->sequenceLength - 1)] = value);
  }
}

void VectorSequence::insert(Object* value) {
  // Append `value' to the END of the sequence `self'.  
  // Resize the array if necessary.
  { VectorSequence* self = this;

    { int oldlength = self->sequenceLength;

      if (oldlength == self->arraySize) {
        resizeVector(self, self->arraySize * 2);
      }
      (self->theArray)[oldlength] = value;
      self->sequenceLength = oldlength + 1;
    }
  }
}

void CustomVectorSequence::insert(Object* value) {
  // Append `value' to the END of the sequence `self'.  
  // Resize the array if necessary.
  { CustomVectorSequence* self = this;

    { int oldlength = self->sequenceLength;

      if (oldlength == self->arraySize) {
        if (!(self->resizeFactor > 1.0)) {
          std::cerr << "Safety violation: " << "CUSTOM-VECTOR-SEQUENCE.insert: resize factor needs to be > 1";
        }
        resizeVector(self, ((int)(self->arraySize * self->resizeFactor)));
      }
      (self->theArray)[oldlength] = value;
      self->sequenceLength = oldlength + 1;
    }
  }
}

AbstractCollection* VectorSequence::remove(Object* value) {
  // Remove `value' from the sequence `self', and left shift
  // the values after it to close the gap.
  { VectorSequence* self = this;

    { Object** array = self->theArray;
      int length = self->sequenceLength;
      int nhits = 0;

      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = length - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          if (eqlP(array[i], value)) {
            nhits = nhits + 1;
          }
          else if (nhits > 0) {
            array[(i - nhits)] = (array[i]);
          }
        }
      }
      self->sequenceLength = length - nhits;
      { int i = NULL_INTEGER;
        int iter001 = self->sequenceLength;
        int upperBound001 = length - 1;

        for  (; iter001 <= upperBound001; 
              iter001 = iter001 + 1) {
          i = iter001;
          array[i] = NULL;
        }
      }
      return (self);
    }
  }
}

VectorSequence* VectorSequence::reverse() {
  // Reverse the order of elements in the active portion of `self'.
  { VectorSequence* self = this;

    { Object** array = self->theArray;
      int bottom = 0;
      int top = self->sequenceLength - 1;
      Object* elt = NULL;

      while (bottom < top) {
        elt = array[bottom];
        array[bottom] = (array[top]);
        array[top] = elt;
        bottom = bottom + 1;
        top = top - 1;
      }
      return (self);
    }
  }
}

void copyVectorSequence(VectorSequence* source, VectorSequence* copy) {
  { Object** sourcearray = source->theArray;
    Object** copyarray = copy->theArray;
    int length = source->sequenceLength;

    copy->sequenceLength = length;
    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = length - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        copyarray[i] = (sourcearray[i]);
      }
    }
  }
}

Vector* VectorSequence::copy() {
  // Return a copy of the vector sequence `self'.
  { VectorSequence* self = this;

    { VectorSequence* copy = newVectorSequence(self->arraySize);

      copyVectorSequence(self, copy);
      return (copy);
    }
  }
}

Vector* CustomVectorSequence::copy() {
  // Return a copy of the vector sequence `self'.
  { CustomVectorSequence* self = this;

    { CustomVectorSequence* copy = newCustomVectorSequence(self->arraySize);

      copy->resizeFactor = self->resizeFactor;
      copyVectorSequence(self, copy);
      return (copy);
    }
  }
}

void VectorSequence::clear() {
  // Clear `self' by setting its active length to zero.
  { VectorSequence* self = this;

    self->sequenceLength = 0;
  }
}

boolean VectorSequence::objectEqualP(Object* y) {
  // Return TRUE iff the sequences `x' and `y' are structurally
  // equivalent.  Uses `equal?' to test equality of elements.
  { VectorSequence* x = this;

    if (subtypeOfP(safePrimaryType(y), SGT_COLLECTIONS_STELLA_VECTOR_SEQUENCE)) {
      { Object* y000 = y;
        VectorSequence* y = ((VectorSequence*)(y000));

        if (x->sequenceLength == y->sequenceLength) {
          { Object* eltx = NULL;
            VectorSequence* vector000 = x;
            int index000 = 0;
            int length000 = vector000->sequenceLength;
            Object* elty = NULL;
            VectorSequence* vector001 = y;
            int index001 = 0;
            int length001 = vector001->sequenceLength;

            for  (; (index000 < length000) &&
                      (index001 < length001); 
                  index000 = index000 + 1,
                  index001 = index001 + 1) {
              eltx = (vector000->theArray)[index000];
              elty = (vector001->theArray)[index001];
              if (!equalP(eltx, elty)) {
                return (false);
              }
            }
          }
          return (true);
        }
      }
    }
    else {
    }
    return (false);
  }
}

AbstractIterator* Vector::allocateIterator() {
  { Vector* self = this;

    { AllPurposeIterator* iterator = newAllPurposeIterator();

      iterator->iteratorObject = self;
      iterator->iteratorInteger = 0;
      iterator->iteratorSecondInteger = self->length();
      iterator->iteratorNextCode = ((cpp_function_code)(&vectorNextP));
      return (iterator);
    }
  }
}

boolean vectorNextP(AllPurposeIterator* self) {
  { int cursor = self->iteratorInteger;

    if (cursor < self->iteratorSecondInteger) {
      self->value = (((Vector*)(self->iteratorObject))->theArray)[cursor];
      self->iteratorInteger = cursor + 1;
      return (true);
    }
    return (false);
  }
}

Iterator* Vector::butLast() {
  // Generate all but the last element of the vector `self'.
  { Vector* self = this;

    { AllPurposeIterator* iterator = newAllPurposeIterator();

      iterator->iteratorObject = self;
      iterator->iteratorInteger = 0;
      iterator->iteratorSecondInteger = self->arraySize - 1;
      iterator->iteratorNextCode = ((cpp_function_code)(&vectorNextP));
      return (iterator);
    }
  }
}

Vector* Vector::sort(cpp_function_code predicate) {
  // Perform a destructive sort of `self' according to
  // `predicate', and return the result.  If `predicate' has a '<' semantics, the
  // result will be in ascending order.  If `predicate' is `null', a
  // suitable '<' predicate is chosen depending on the first element of `self',
  // and it is assumed that all elements of `self' have the same type (supported
  // element types are GENERALIZED-SYMBOL, STRING, INTEGER, and FLOAT).
  { Vector* self = this;

    { int length = self->length();

      if (length == 0) {
        return (self);
      }
      else if (predicate == NULL) {
        predicate = chooseSortPredicate((self->theArray)[0]);
      }
      heapSortNativeVector(self->theArray, self->length(), predicate);
      return (self);
    }
  }
}

Vector* Vector::sortTuples(int n, cpp_function_code predicate) {
  // Just like `sort' but assumes each element of `self' is a tuple (a cons)
  // whose `n'-th element (0-based) will be used for comparison.
  { Vector* self = this;

    { int length = self->length();

      if (length == 0) {
        return (self);
      }
      else if (predicate == NULL) {
        predicate = chooseSortPredicate(((Cons*)((self->theArray)[0]))->nth(n));
      }
      { 
        BIND_STELLA_SPECIAL(oSORT_TUPLE_COMPARE_PREDICATEo, cpp_function_code, predicate);
        BIND_STELLA_SPECIAL(oSORT_TUPLE_COMPARE_INDEXo, int, n);
        heapSortNativeVector(self->theArray, self->length(), ((cpp_function_code)(&sortTupleCompareP)));
        return (self);
      }
    }
  }
}

Vector* Vector::sortObjects(StorageSlot* slot, cpp_function_code predicate) {
  // Just like `sort' but assumes each element of `self' has a `slot'
  // whose value will be used for comparison.  Elements must be descendants of
  // STANDARD OBJECT.  Note that while this will work with literal-valued slots,
  // it will cause value wrapping everytime `slot' is read.
  { Vector* self = this;

    { int length = self->length();

      if (length == 0) {
        return (self);
      }
      else if (predicate == NULL) {
        predicate = chooseSortPredicate(readSlotValue(((StandardObject*)((self->theArray)[0])), slot));
      }
      { 
        BIND_STELLA_SPECIAL(oSORT_TUPLE_COMPARE_PREDICATEo, cpp_function_code, predicate);
        BIND_STELLA_SPECIAL(oSORT_OBJECTS_COMPARE_SLOTo, StorageSlot*, slot);
        heapSortNativeVector(self->theArray, self->length(), ((cpp_function_code)(&sortObjectsCompareP)));
        return (self);
      }
    }
  }
}

void heapSortNativeVector(Object** vector, int size, cpp_function_code predicate) {
  heapSortHeapify(vector, size, predicate);
  { int end = size - 1;
    Object* aux = NULL;

    while (end > 0) {
      aux = vector[0];
      vector[0] = (vector[end]);
      vector[end] = aux;
      end = end - 1;
      heapSortSiftDown(vector, 0, end, predicate);
    }
  }
}

void heapSortHeapify(Object** vector, int size, cpp_function_code predicate) {
  { int start = (size >> 1) - 1;

    while (start >= 0) {
      heapSortSiftDown(vector, start, size - 1, predicate);
      start = start - 1;
    }
  }
}

void heapSortSiftDown(Object** vector, int start, int end, cpp_function_code predicate) {
  { int root = start;
    int child = 0;
    Object* aux = NULL;

    for (;;) {
      child = (root << 1) + 1;
      if (child > end) {
        break;
      }
      if ((child < end) &&
          ((boolean  (*) (Object*, Object*))predicate)(vector[child], vector[(child + 1)])) {
        child = child + 1;
      }
      if (((boolean  (*) (Object*, Object*))predicate)(vector[root], vector[child])) {
        aux = vector[root];
        vector[root] = (vector[child]);
        vector[child] = aux;
        root = child;
      }
      else {
        return;
      }
    }
  }
}

Object* quickSortPickSplitElement(Object** vector, int start, int end, cpp_function_code predicate) {
  { Object* splitelement = vector[start];
    int middle = ((start + end) >> 1);

    end = end - 1;
    if (((boolean  (*) (Object*, Object*))predicate)(splitelement, vector[middle])) {
      if (((boolean  (*) (Object*, Object*))predicate)(vector[middle], vector[end])) {
        splitelement = vector[middle];
        vector[middle] = (vector[start]);
      }
      else if (((boolean  (*) (Object*, Object*))predicate)(splitelement, vector[end])) {
        splitelement = vector[end];
        vector[end] = (vector[start]);
      }
      else {
      }
    }
    else {
      if (((boolean  (*) (Object*, Object*))predicate)(splitelement, vector[end])) {
      }
      else if (((boolean  (*) (Object*, Object*))predicate)(vector[middle], vector[end])) {
        splitelement = vector[end];
        vector[end] = (vector[start]);
      }
      else {
        splitelement = vector[middle];
        vector[middle] = (vector[start]);
      }
    }
    return (splitelement);
  }
}

void quickSortNativeVector(Object** vector, int start, int end, cpp_function_code predicate) {
  for (;;) {
    { int length = end - start;
      Object* splitelement = NULL;
      Object* element = NULL;
      int lowcursor = start;
      int highcursor = end;

      if (length <= 1) {
        return;
      }
      else if (length >= 10) {
        splitelement = quickSortPickSplitElement(vector, start, end, predicate);
      }
      else {
        splitelement = vector[start];
      }
      while (lowcursor < highcursor) {
        while (lowcursor < highcursor) {
          highcursor = highcursor - 1;
          element = vector[highcursor];
          if (((boolean  (*) (Object*, Object*))predicate)(element, splitelement)) {
            vector[lowcursor] = element;
            break;
          }
        }
        while (lowcursor < highcursor) {
          lowcursor = lowcursor + 1;
          element = vector[lowcursor];
          if (((boolean  (*) (Object*, Object*))predicate)(splitelement, element)) {
            vector[highcursor] = element;
            break;
          }
        }
      }
      vector[highcursor] = splitelement;
      if (((start + end) >> 1) < highcursor) {
        quickSortNativeVector(vector, highcursor + 1, end, predicate);
        end = highcursor;
      }
      else {
        quickSortNativeVector(vector, start, highcursor, predicate);
        start = highcursor + 1;
      }
    }
  }
}

Heap* newHeap(cpp_function_code predicate, int arraySize) {
  { Heap* self = NULL;

    self = new Heap();
    self->predicate = predicate;
    self->arraySize = arraySize;
    self->theArray = NULL;
    self->fillPointer = 0;
    self->initializeVector();
    self->initializeHeap();
    return (self);
  }
}

Surrogate* Heap::primaryType() {
  { Heap* self = this;

    return (SGT_COLLECTIONS_STELLA_HEAP);
  }
}

Object* accessHeapSlotValue(Heap* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_COLLECTIONS_STELLA_PREDICATE) {
    if (setvalueP) {
      self->predicate = ((FunctionCodeWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFunctionCode(self->predicate);
    }
  }
  else if (slotname == SYM_COLLECTIONS_STELLA_FILL_POINTER) {
    if (setvalueP) {
      self->fillPointer = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->fillPointer);
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

void Heap::initializeHeap() {
  { Heap* self = this;

    { int size = self->arraySize;

      if (!(size > 0)) {
        std::cerr << "Safety violation: " << "Trying to create an empty heap";
      }
    }
  }
}

Vector* Heap::copy() {
  // Return a copy of the heap `self'.
  { Heap* self = this;

    { int length = self->fillPointer;

      { Heap* self000 = newHeap(self->predicate, self->arraySize);

        self000->fillPointer = length;
        { Heap* copy = self000;
          Object** sourcearray = self->theArray;
          Object** copyarray = copy->theArray;

          { int i = NULL_INTEGER;
            int iter000 = 0;
            int upperBound000 = length - 1;

            for  (; iter000 <= upperBound000; 
                  iter000 = iter000 + 1) {
              i = iter000;
              copyarray[i] = (sourcearray[i]);
            }
          }
          return (copy);
        }
      }
    }
  }
}

void Heap::clear() {
  // Clear `self' by setting its active length to zero.
  { Heap* self = this;

    self->fillPointer = 0;
  }
}

int Heap::length() {
  // Return the length of the currently filled portion of `self'.
  { Heap* self = this;

    return (self->fillPointer);
  }
}

boolean Heap::emptyP() {
  // Return TRUE if `self' is empty.
  { Heap* self = this;

    return (self->fillPointer == 0);
  }
}

Object* Heap::last() {
  // Return the last item in the heap `self' which will be the
  // largest or best item if `self' is a sorted min-heap with a '<' predicate.
  { Heap* self = this;

    return ((self->theArray)[(self->length() - 1)]);
  }
}

Object* Heap::heapRoot() {
  // Return the root of `self' (NULL if `self' is empty).
  // The root contains the minimum element of a min-heap with '<' predicate.
  { Heap* self = this;

    return ((self->emptyP() ? NULL : (self->theArray)[0]));
  }
}

Object* Heap::fastHeapRoot() {
  // Return the root of `self' which is assumed to be non-empty.
  { Heap* self = this;

    return ((self->theArray)[0]);
  }
}

void heapSiftUp(Object** heap, int start, int end, Object* value, cpp_function_code predicate) {
  { int parent = NULL_INTEGER;
    int child = end;

    heap[end] = value;
    while (child > start) {
      if ((child & 1) == 0) {
        parent = ((child - 2) >> 1);
      }
      else {
        parent = ((child - 1) >> 1);
      }
      if (((boolean  (*) (Object*, Object*))predicate)(value, heap[parent])) {
        heap[child] = (heap[parent]);
        heap[parent] = value;
        child = parent;
      }
      else {
        break;
      }
    }
  }
}

void heapSiftDown(Object** heap, int start, int end, Object* value, cpp_function_code predicate) {
  { int parent = start;
    int child = NULL_INTEGER;
    Object* leftchild = NULL;
    Object* rightchild = NULL;

    heap[start] = value;
    end = end - 1;
    for (;;) {
      child = (parent << 1) + 1;
      if (child > end) {
        break;
      }
      else if (child == end) {
        if (!(((boolean  (*) (Object*, Object*))predicate)(heap[child], value))) {
          break;
        }
      }
      else {
        leftchild = heap[child];
        rightchild = heap[(child + 1)];
        if (((boolean  (*) (Object*, Object*))predicate)(leftchild, value)) {
          if (((boolean  (*) (Object*, Object*))predicate)(rightchild, value) &&
              ((boolean  (*) (Object*, Object*))predicate)(rightchild, leftchild)) {
            child = child + 1;
          }
        }
        else if (((boolean  (*) (Object*, Object*))predicate)(rightchild, value)) {
          child = child + 1;
        }
        else {
          break;
        }
      }
      heap[parent] = (heap[child]);
      heap[child] = value;
      parent = child;
    }
  }
}

void Heap::insert(Object* value) {
  // Insert `value' into `self' and restore the heap property.
  // Signal an error if there is no more room in `self'.  Maintains `self' as
  // a Min-heap if `self's `predicate' has `<' semantics; otherwise as a Max-heap.
  { Heap* self = this;

    { Object** values = self->theArray;
      int fillpointer = self->fillPointer;
      cpp_function_code predicate = self->predicate;

      if (fillpointer < self->arraySize) {
        heapSiftUp(values, 0, fillpointer, value, predicate);
        self->fillPointer = fillpointer + 1;
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "HEAP.insert: heap overflow, can't insert new value: " << "`" << value << "'";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

void Heap::replaceHeapRoot(Object* value) {
  // Replace the current root of `self' with `value' and restore
  // the heap property.  Signal an error if `self' is empty.  Maintains `self' as
  // a Min-heap if `self's `predicate' has `<' semantics; otherwise as a Max-heap.
  { Heap* self = this;

    { Object** values = self->theArray;
      int fillpointer = self->fillPointer;
      cpp_function_code predicate = self->predicate;

      if (fillpointer == 0) {
        throw *newStellaException("HEAP.replace-heap-root: can't replace root of an empty heap");
      }
      else {
        heapSiftDown(values, 0, fillpointer, value, predicate);
      }
    }
  }
}

void Heap::insertIfBetter(Object* value) {
  // Insert `value' into `self' and restore the heap property.
  // If `self' has available room, simply insert `value'.  If the heap is full, only
  // insert `value' if it is better than the current root (i.e., if `value' is
  // greater than the minimum of `self' for the case of a min-heap where `self's
  // `predicate' has `<' semantics).  In that case, replace the root of `self'
  // and restore the heap property.  This is useful to build and maintain a
  // heap with some top-N elements (relative to `predicate') where the root (or
  // minimum) of `self' is the currently weakest element at the end of the list.
  { Heap* self = this;

    { Object** values = self->theArray;
      int fillpointer = self->fillPointer;
      cpp_function_code predicate = self->predicate;

      if (fillpointer == self->arraySize) {
        if (((boolean  (*) (Object*, Object*))predicate)((self->theArray)[0], value)) {
          heapSiftDown(values, 0, fillpointer, value, predicate);
        }
      }
      else {
        heapSiftUp(values, 0, fillpointer, value, predicate);
        self->fillPointer = fillpointer + 1;
      }
    }
  }
}

void Heap::heapify() {
  // Restore the heap property of `self' according to its
  // `predicate'.  Normally, this is not needed, since insert operations
  // preserve the heap property.  However, this can be useful after bulk
  // insertion of values or if `predicate' has been changed.
  { Heap* self = this;

    { Object** values = self->theArray;
      int fillpointer = self->fillPointer;
      cpp_function_code predicate = self->predicate;

      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = fillpointer - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          heapSiftUp(values, 0, i, values[i], predicate);
        }
      }
    }
  }
}

Vector* Heap::sort(cpp_function_code predicate) {
  // Sort the heap `self' according to `predicate' (in
  // ascending order if `predicate' has `<' semantics).  If `predicate'
  // is NULL simply use `self's internal predicate (the normal case).
  // If it is different from `self's internal predicate, heapify `self' first
  // according to the new predicate, store the new predicate in `self' and
  // then sort the heap.  Note that a sorted array automatically satisfies
  // the heap property.  This is slightly different than a regular heap
  // sort due to the way HEAP's are maintained; however, the complexity is
  // the same.
  { Heap* self = this;

    { Object** values = self->theArray;
      int cursor = self->fillPointer;
      Object* value = NULL;

      if (predicate == NULL) {
        predicate = self->predicate;
      }
      else if (!(predicate == self->predicate)) {
        self->predicate = predicate;
        self->heapify();
      }
      while (cursor > 0) {
        cursor = cursor - 1;
        value = values[cursor];
        values[cursor] = (values[0]);
        heapSiftDown(values, 0, cursor, value, predicate);
      }
      cursor = self->fillPointer;
      { int i = NULL_INTEGER;
        int iter000 = 0;

        for (; true; iter000 = iter000 + 1) {
          i = iter000;
          cursor = cursor - 1;
          if (i >= cursor) {
            break;
          }
          value = values[i];
          values[i] = (values[cursor]);
          values[cursor] = value;
        }
      }
      return (self);
    }
  }
}

boolean oUSE_STELLA_HASH_TABLESpo = 
#ifndef HAVE_SGI_HASH_MAPS
  TRUE
#else
  FALSE
#endif
;

StellaHashTable* newStellaHashTable() {
  { StellaHashTable* self = NULL;

    self = new StellaHashTable();
    self->theStellaHashTable = NULL;
    self->theHashTable = NULL;
    self->equalTestP = false;
    self->freeElements = NULL_INTEGER;
    self->initialSize = 50;
    self->size = NULL_INTEGER;
    self->theTable = NULL;
    self->initializeHashTable();
    return (self);
  }
}

Surrogate* StellaHashTable::primaryType() {
  { StellaHashTable* self = this;

    return (SGT_COLLECTIONS_STELLA_STELLA_HASH_TABLE);
  }
}

Object* accessStellaHashTableSlotValue(StellaHashTable* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_COLLECTIONS_STELLA_SIZE) {
    if (setvalueP) {
      self->size = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->size);
    }
  }
  else if (slotname == SYM_COLLECTIONS_STELLA_INITIAL_SIZE) {
    if (setvalueP) {
      self->initialSize = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->initialSize);
    }
  }
  else if (slotname == SYM_COLLECTIONS_STELLA_FREE_ELEMENTS) {
    if (setvalueP) {
      self->freeElements = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->freeElements);
    }
  }
  else if (slotname == SYM_COLLECTIONS_STELLA_EQUAL_TESTp) {
    if (setvalueP) {
      self->equalTestP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->equalTestP ? TRUE_WRAPPER : FALSE_WRAPPER);
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

double oSTELLA_HASH_TABLE_AVG_BUCKET_LENGTHo = 1.0;

void initializeStellaHashTable(StellaHashTable* self) {
  { int size = pickHashTableSizePrime(stella::floor(self->initialSize / oSTELLA_HASH_TABLE_AVG_BUCKET_LENGTHo));
    KvCons** table = new (GC)KvCons*[size];

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = size - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        table[i] = NULL;
      }
    }
    self->theTable = table;
    self->size = size;
    self->freeElements = stella::floor(size * oSTELLA_HASH_TABLE_AVG_BUCKET_LENGTHo);
  }
}

void StellaHashTable::initializeHashTable() {
  // Initialize the STELLA hash table `self'.  This is a
  // no-op and primarily exists to shadow the standard initializer inherited
  // from ABSTRACT-HASH-TABLE.  STELLA hash tables are initialized at the
  // first insertion operation.
  { StellaHashTable* self = this;

  }
}

void rehashStellaHashTable(StellaHashTable* self, int newsize) {
  if (self->theTable == NULL) {
    initializeStellaHashTable(self);
    return;
  }
  { int size = self->size;
    KvCons** table = self->theTable;
    KvCons** newtable = new (GC)KvCons*[newsize];
    int newbucketindex = 0;
    KvCons* newbucket = NULL;
    KvCons* cursor = NULL;
    KvCons* current = NULL;
    boolean equaltestP = self->equalTestP;

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = newsize - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        newtable[i] = NULL;
      }
    }
    { int i = NULL_INTEGER;
      int iter001 = 0;
      int upperBound001 = size - 1;

      for  (; iter001 <= upperBound001; 
            iter001 = iter001 + 1) {
        i = iter001;
        cursor = table[i];
        while (((boolean)(cursor))) {
          if (equaltestP) {
            newbucketindex = (((unsigned int) (cursor->key->equalHashCode())) % newsize);
          }
          else {
            newbucketindex = (((unsigned int) (cursor->key->hashCode())) % newsize);
          }
          newbucket = newtable[newbucketindex];
          current = cursor;
          cursor = cursor->rest;
          if (((boolean)(newbucket))) {
            current->rest = newbucket->rest;
            newbucket->rest = current;
          }
          else {
            newtable[newbucketindex] = current;
            current->rest = NULL;
          }
        }
      }
    }
    self->theTable = newtable;
    self->size = newsize;
    self->freeElements = stella::integerMax(self->freeElements + stella::floor((newsize - size) * oSTELLA_HASH_TABLE_AVG_BUCKET_LENGTHo), 0);
  }
}

void stellaHashTableInsertAt(StellaHashTable* self, Object* key, Object* value) {
  { KvCons** table = self->theTable;
    int free = self->freeElements;
    int bucketindex = 0;
    KvCons* bucket = NULL;
    boolean equaltestP = self->equalTestP;

    if (table == NULL) {
      initializeStellaHashTable(self);
      table = self->theTable;
      free = self->freeElements;
    }
    if (free == 0) {
      rehashStellaHashTable(self, pickHashTableSizePrime(self->size + 1));
      table = self->theTable;
      free = self->freeElements;
    }
    if (equaltestP) {
      bucketindex = (((unsigned int) (key->equalHashCode())) % (self->size));
    }
    else {
      bucketindex = (((unsigned int) (key->hashCode())) % (self->size));
    }
    bucket = table[bucketindex];
    if (!((boolean)(bucket))) {
      { KvCons* self000 = newKvCons();

        self000->key = key;
        self000->value = value;
        table[bucketindex] = self000;
      }
      self->freeElements = free - 1;
    }
    else {
      { KvCons* cursor = bucket;

        if (equaltestP) {
          while (((boolean)(cursor)) &&
              (!equalP(cursor->key, key))) {
            cursor = cursor->rest;
          }
        }
        else {
          while (((boolean)(cursor)) &&
              (!eqlP(cursor->key, key))) {
            cursor = cursor->rest;
          }
        }
        if (((boolean)(cursor))) {
          cursor->value = value;
        }
        else {
          { KvCons* self001 = newKvCons();

            self001->key = key;
            self001->value = value;
            self001->rest = bucket->rest;
            bucket->rest = self001;
          }
          self->freeElements = free - 1;
        }
      }
    }
  }
}

void stellaHashTableRemoveAt(StellaHashTable* self, Object* key) {
  { KvCons** table = self->theTable;
    int bucketindex = 0;
    KvCons* bucket = NULL;
    boolean equaltestP = self->equalTestP;

    if (table == NULL) {
      return;
    }
    if (equaltestP) {
      bucketindex = (((unsigned int) (key->equalHashCode())) % (self->size));
    }
    else {
      bucketindex = (((unsigned int) (key->hashCode())) % (self->size));
    }
    bucket = table[bucketindex];
    if (!((boolean)(bucket))) {
      return;
    }
    else if ((!equaltestP) &&
        eqlP(bucket->key, key)) {
      table[bucketindex] = bucket->rest;
      self->freeElements = self->freeElements + 1;
      return;
    }
    else if (equaltestP &&
        equalP(bucket->key, key)) {
      table[bucketindex] = bucket->rest;
      self->freeElements = self->freeElements + 1;
      return;
    }
    else {
      { KvCons* trailer = bucket;

        bucket = bucket->rest;
        while (((boolean)(bucket))) {
          if ((!equaltestP) &&
              eqlP(bucket->key, key)) {
            trailer->rest = bucket->rest;
            self->freeElements = self->freeElements + 1;
            return;
          }
          else if (equaltestP &&
              equalP(bucket->key, key)) {
            trailer->rest = bucket->rest;
            self->freeElements = self->freeElements + 1;
            return;
          }
          else {
            trailer = bucket;
            bucket = bucket->rest;
          }
        }
      }
    }
  }
}

Object* stellaHashTableLookup(StellaHashTable* self, Object* key) {
  { KvCons** table = self->theTable;
    KvCons* bucket = NULL;

    if (table == NULL) {
      return (NULL);
    }
    if (self->equalTestP) {
      bucket = table[(((unsigned int) (key->equalHashCode())) % (self->size))];
      while (((boolean)(bucket))) {
        if (equalP(bucket->key, key)) {
          return (bucket->value);
        }
        else {
          bucket = bucket->rest;
        }
      }
    }
    else {
      bucket = table[(((unsigned int) (key->hashCode())) % (self->size))];
      while (((boolean)(bucket))) {
        if (eqlP(bucket->key, key)) {
          return (bucket->value);
        }
        else {
          bucket = bucket->rest;
        }
      }
    }
    return (NULL);
  }
}

Object* stellaStringHashTableLookup(StellaHashTable* self, const char* key) {
  { KvCons** table = self->theTable;
    KvCons* bucket = NULL;

    if (table == NULL) {
      return (NULL);
    }
    bucket = table[(((unsigned int) (native_hash_string(key))) % (self->size))];
    while (((boolean)(bucket))) {
      if (stringEqlP(((StringWrapper*)(bucket->key))->wrapperValue, key)) {
        return (bucket->value);
      }
      else {
        bucket = bucket->rest;
      }
    }
    return (NULL);
  }
}

Object* StellaHashTable::lookup(Object* key) {
  // Lookup the entry identified by `key' in `self' and
  // return its value, or NULL if no such entry exists.    Uses an `eql?'
  // test by default or `equal?' if `equal-test?' of `self' is TRUE.
  { StellaHashTable* self = this;

    return (stellaHashTableLookup(self, key));
  }
}

void StellaHashTable::insertAt(Object* key, Object* value) {
  // Set the value of the entry identified by `key' in `self'
  // to `value' or add a new entry if no entry with `key' exists yet.  Uses an
  // `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.
  { StellaHashTable* self = this;

    stellaHashTableInsertAt(self, key, value);
    return;
  }
}

void StellaHashTable::removeAt(Object* key) {
  // Remove the entry identified by `key' from `self'.  Uses an
  // `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.
  { StellaHashTable* self = this;

    stellaHashTableRemoveAt(self, key);
    return;
  }
}

int StellaHashTable::length() {
  // Return the number of entries in `self'.
  { StellaHashTable* self = this;

    if (self->theTable == NULL) {
      return (0);
    }
    else {
      return (self->size - self->freeElements);
    }
  }
}

boolean StellaHashTable::emptyP() {
  // Return TRUE if `self' has zero entries.
  { StellaHashTable* self = this;

    return (self->length() == 0);
  }
}

boolean StellaHashTable::nonEmptyP() {
  // Return TRUE if `self' has at least 1 entry.
  { StellaHashTable* self = this;

    return (self->length() > 0);
  }
}

StellaHashTable* StellaHashTable::copy() {
  // Return a copy of the hash table `self'.  The bucket table
  // and buckets are freshly allocated, however, the keys and values of entries
  // are not copied themselves (similar to what we do for lists, etc.).
  { StellaHashTable* self = this;

    { int size = self->size;

      { StellaHashTable* self000 = newStellaHashTable();

        self000->size = size;
        self000->initialSize = self->initialSize;
        self000->freeElements = self->freeElements;
        self000->equalTestP = self->equalTestP;
        { StellaHashTable* copy = self000;
          KvCons** table = self->theTable;
          KvCons** tablecopy = table;
          KvCons* bucket = NULL;

          if (table != NULL) {
            tablecopy = new (GC)KvCons*[size];
            copy->theTable = tablecopy;
            { int i = NULL_INTEGER;
              int iter000 = 0;
              int upperBound000 = size - 1;

              for  (; iter000 <= upperBound000; 
                    iter000 = iter000 + 1) {
                i = iter000;
                bucket = table[i];
                if (((boolean)(bucket))) {
                  tablecopy[i] = copyKvConsList(bucket);
                }
                else {
                  tablecopy[i] = NULL;
                }
              }
            }
          }
          return (copy);
        }
      }
    }
  }
}

void StellaHashTable::clear() {
  // Remove all entries from `self'.  This will result in a
  // re-initialization of the table upon the first insertion into `self'.
  { StellaHashTable* self = this;

    self->theTable = NULL;
    self->size = NULL_INTEGER;
    self->freeElements = NULL_INTEGER;
  }
}

Cons* StellaHashTable::consify() {
  // Collect all entries of `self' into a cons list of
  // `(<key> <value>)' pairs and return the result.
  { StellaHashTable* self = this;

    { Cons* result = NIL;

      { Object* key = NULL;
        Object* value = NULL;
        StellaHashTableIterator* iter000 = ((StellaHashTableIterator*)(self->allocateIterator()));
        Cons* collect000 = NULL;

        for  (; iter000->nextP(); ) {
          key = iter000->key;
          value = iter000->value;
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(cons(key, cons(value, NIL)), NIL);
              if (result == NIL) {
                result = collect000;
              }
              else {
                addConsToEndOfConsList(result, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(cons(key, cons(value, NIL)), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      return (result);
    }
  }
}

boolean StellaHashTable::objectEqualP(Object* y) {
  // Return TRUE if `x' and `y' represent the same set of key/value pairs.
  { StellaHashTable* x = this;

    if (subtypeOfP(safePrimaryType(y), SGT_COLLECTIONS_STELLA_STELLA_HASH_TABLE)) {
      { Object* y000 = y;
        StellaHashTable* y = ((StellaHashTable*)(y000));

        if (x->length() == y->length()) {
          { Object* key = NULL;
            Object* value = NULL;
            StellaHashTableIterator* iter000 = ((StellaHashTableIterator*)(x->allocateIterator()));

            for  (; iter000->nextP(); ) {
              key = iter000->key;
              value = iter000->value;
              if (!equalP(value, y->lookup(key))) {
                return (false);
              }
            }
          }
          return (true);
        }
      }
    }
    else {
    }
    return (false);
  }
}

int StellaHashTable::equalHashCode() {
  // Return an `equal?' hash code for `self'.  Note that this
  // is O(N) in the number of entries of `self'.
  { StellaHashTable* self = this;

    { int code = 36273463;

      { Object* key = NULL;
        Object* value = NULL;
        StellaHashTableIterator* iter000 = ((StellaHashTableIterator*)(self->allocateIterator()));

        for  (; iter000->nextP(); ) {
          key = iter000->key;
          value = iter000->value;
          code = (code ^ (key->equalHashCode()));
          code = (code ^ (value->equalHashCode()));
        }
      }
      return (code);
    }
  }
}

StellaHashTableIterator* newStellaHashTableIterator() {
  { StellaHashTableIterator* self = NULL;

    self = new StellaHashTableIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->key = NULL;
    self->bucketCursor = NULL;
    self->bucketIndex = 0;
    self->bucketTable = NULL;
    self->size = NULL_INTEGER;
    return (self);
  }
}

Surrogate* StellaHashTableIterator::primaryType() {
  { StellaHashTableIterator* self = this;

    return (SGT_COLLECTIONS_STELLA_STELLA_HASH_TABLE_ITERATOR);
  }
}

Object* accessStellaHashTableIteratorSlotValue(StellaHashTableIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_COLLECTIONS_STELLA_SIZE) {
    if (setvalueP) {
      self->size = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->size);
    }
  }
  else if (slotname == SYM_COLLECTIONS_STELLA_BUCKET_INDEX) {
    if (setvalueP) {
      self->bucketIndex = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->bucketIndex);
    }
  }
  else if (slotname == SYM_COLLECTIONS_STELLA_BUCKET_CURSOR) {
    if (setvalueP) {
      self->bucketCursor = ((KvCons*)(value));
    }
    else {
      value = self->bucketCursor;
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

AbstractIterator* StellaHashTable::allocateIterator() {
  // Allocate an iterator for `self'.
  { StellaHashTable* self = this;

    { StellaHashTableIterator* self000 = newStellaHashTableIterator();

      self000->size = self->size;
      self000->bucketTable = self->theTable;
      self000->bucketIndex = 0;
      self000->bucketCursor = NULL;
      { StellaHashTableIterator* value000 = self000;

        return (value000);
      }
    }
  }
}

boolean StellaHashTableIterator::nextP() {
  { StellaHashTableIterator* self = this;

    { KvCons* cursor = self->bucketCursor;

      if (self->firstIterationP) {
        self->firstIterationP = false;
      }
      else if (((boolean)(cursor))) {
        cursor = cursor->rest;
      }
      if (!((boolean)(cursor))) {
        { KvCons** table = self->bucketTable;
          int index = self->bucketIndex;
          int size = self->size;

          if (table == NULL) {
            return (false);
          }
          while ((!((boolean)(cursor))) &&
              (index < size)) {
            cursor = table[index];
            index = index + 1;
          }
          self->bucketIndex = index;
          self->bucketCursor = cursor;
        }
      }
      if (((boolean)(cursor))) {
        self->key = cursor->key;
        self->value = cursor->value;
        self->bucketCursor = cursor;
        return (true);
      }
      else {
        return (false);
      }
    }
  }
}

Object* StellaHashTableIterator::valueSetter(Object* value) {
  { StellaHashTableIterator* self = this;

    { KvCons* cursor = self->bucketCursor;

      if (((boolean)(cursor))) {
        cursor->value = value;
      }
      self->value = value;
      return (value);
    }
  }
}

Object* StellaHashTableIterator::keySetter(Object* key) {
  { StellaHashTableIterator* self = this;

    throw *newStellaException("Cannot change the key of a STELLA-HASH-TABLE item");
  }
}

// Point where we switch from using a KV-CONS table
// representation to a STELLA hash table to preserve O(1) access.
int oKEY_VALUE_MAP_CROSSOVER_POINTo = NULL_INTEGER;

KeyValueMap* newKeyValueMap() {
  { KeyValueMap* self = NULL;

    self = new KeyValueMap();
    self->crossoverPoint = oKEY_VALUE_MAP_CROSSOVER_POINTo;
    self->initialSize = oKEY_VALUE_MAP_CROSSOVER_POINTo;
    self->equalTestP = false;
    self->theMap = NULL;
    return (self);
  }
}

Surrogate* KeyValueMap::primaryType() {
  { KeyValueMap* self = this;

    return (SGT_COLLECTIONS_STELLA_KEY_VALUE_MAP);
  }
}

Object* accessKeyValueMapSlotValue(KeyValueMap* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_COLLECTIONS_STELLA_THE_MAP) {
    if (setvalueP) {
      self->theMap = value;
    }
    else {
      value = self->theMap;
    }
  }
  else if (slotname == SYM_COLLECTIONS_STELLA_EQUAL_TESTp) {
    if (setvalueP) {
      self->equalTestP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->equalTestP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_COLLECTIONS_STELLA_INITIAL_SIZE) {
    if (setvalueP) {
      self->initialSize = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->initialSize);
    }
  }
  else if (slotname == SYM_COLLECTIONS_STELLA_CROSSOVER_POINT) {
    if (setvalueP) {
      self->crossoverPoint = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->crossoverPoint);
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

Object* KeyValueMap::lookup(Object* key) {
  // Lookup the entry identified by `key' in `self' and
  // return its value, or NULL if no such entry exists.    Uses an `eql?'
  // test by default or `equal?' if `equal-test?' of `self' is TRUE.
  { KeyValueMap* self = this;

    { Object* map = self->theMap;
      int crossover = self->crossoverPoint;

      if (crossover == 0) {
        return (stellaHashTableLookup(((StellaHashTable*)(map)), key));
      }
      else {
        { KvCons* cursor = ((KvCons*)(map));

          if (self->equalTestP) {
            while (((boolean)(cursor))) {
              if (equalP(cursor->key, key)) {
                return (cursor->value);
              }
              cursor = cursor->rest;
            }
          }
          else {
            while (((boolean)(cursor))) {
              if (eqlP(cursor->key, key)) {
                return (cursor->value);
              }
              cursor = cursor->rest;
            }
          }
          return (NULL);
        }
      }
    }
  }
}

void KeyValueMap::insertAt(Object* key, Object* value) {
  // Set the value of the entry identified by `key' in `self'
  // to `value' or add a new entry if no entry with `key' exists yet.  Uses an
  // `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.
  { KeyValueMap* self = this;

    { Object* map = self->theMap;
      int crossover = self->crossoverPoint;

      if (!((boolean)(map))) {
        if (self->initialSize > oKEY_VALUE_MAP_CROSSOVER_POINTo) {
          { StellaHashTable* self000 = newStellaHashTable();

            self000->initialSize = self->initialSize;
            self000->equalTestP = self->equalTestP;
            map = self000;
          }
          self->theMap = map;
          crossover = 0;
        }
        else {
          crossover = oKEY_VALUE_MAP_CROSSOVER_POINTo;
        }
        self->crossoverPoint = crossover;
      }
      if (crossover == 0) {
        stellaHashTableInsertAt(((StellaHashTable*)(map)), key, value);
      }
      else {
        { KvCons* cursor = ((KvCons*)(map));

          if (self->equalTestP) {
            while (((boolean)(cursor))) {
              if (equalP(cursor->key, key)) {
                cursor->value = value;
                return;
              }
              cursor = cursor->rest;
            }
          }
          else {
            while (((boolean)(cursor))) {
              if (eqlP(cursor->key, key)) {
                cursor->value = value;
                return;
              }
              cursor = cursor->rest;
            }
          }
          cursor = kvCons(key, value, ((KvCons*)(map)));
          self->theMap = cursor;
          crossover = crossover - 1;
          self->crossoverPoint = crossover;
          if (crossover == 0) {
            { StellaHashTable* self001 = newStellaHashTable();

              self001->equalTestP = self->equalTestP;
              map = self001;
            }
            self->theMap = map;
            { Object* key = NULL;
              Object* value = NULL;
              KvCons* iter000 = cursor;

              for  (; ((boolean)(iter000)); 
                    iter000 = iter000->rest) {
                key = iter000->key;
                value = iter000->value;
                stellaHashTableInsertAt(((StellaHashTable*)(map)), key, value);
              }
            }
          }
        }
      }
    }
  }
}

void KeyValueMap::removeAt(Object* key) {
  // Remove the entry identified by `key' from `self'.  Uses an
  // `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.
  { KeyValueMap* self = this;

    { Object* map = self->theMap;
      int crossover = self->crossoverPoint;

      if (crossover == 0) {
        stellaHashTableRemoveAt(((StellaHashTable*)(map)), key);
      }
      else {
        { KvCons* cursor = ((KvCons*)(map));
          KvCons* trailer = ((KvCons*)(map));

          if (self->equalTestP) {
            while (((boolean)(cursor))) {
              if (equalP(cursor->key, key)) {
                break;
              }
              trailer = cursor;
              cursor = cursor->rest;
            }
          }
          else {
            while (((boolean)(cursor))) {
              if (eqlP(cursor->key, key)) {
                break;
              }
              trailer = cursor;
              cursor = cursor->rest;
            }
          }
          if (!((boolean)(cursor))) {
            return;
          }
          else if (cursor == trailer) {
            self->theMap = cursor->rest;
          }
          else {
            trailer->rest = cursor->rest;
          }
          self->crossoverPoint = crossover + 1;
        }
      }
    }
  }
}

int KeyValueMap::length() {
  // Return the number of entries in `self'.
  { KeyValueMap* self = this;

    { Object* map = self->theMap;

      if (!((boolean)(map))) {
        return (0);
      }
      else if (self->crossoverPoint == 0) {
        return (((StellaHashTable*)(map))->length());
      }
      else {
        return (((KvCons*)(map))->length());
      }
    }
  }
}

boolean KeyValueMap::emptyP() {
  // Return TRUE if `self' has zero entries.
  { KeyValueMap* self = this;

    { Object* map = self->theMap;

      if (!((boolean)(map))) {
        return (true);
      }
      else if (self->crossoverPoint == 0) {
        return (((StellaHashTable*)(map))->length() == 0);
      }
      else {
        return (false);
      }
    }
  }
}

boolean KeyValueMap::nonEmptyP() {
  // Return TRUE if `self' has at least 1 entry.
  { KeyValueMap* self = this;

    { Object* map = self->theMap;

      if (!((boolean)(map))) {
        return (false);
      }
      else if (self->crossoverPoint == 0) {
        return (((StellaHashTable*)(map))->length() > 0);
      }
      else {
        return (true);
      }
    }
  }
}

KeyValueMap* KeyValueMap::copy() {
  // Return a copy of the map `self'.  All entries are freshly
  // allocated, however, the keys and values of entries are not copied themselves
  //  (similar to what we do for lists, etc.).
  { KeyValueMap* self = this;

    { KeyValueMap* self000 = newKeyValueMap();

      self000->equalTestP = self->equalTestP;
      self000->initialSize = self->initialSize;
      self000->crossoverPoint = self->crossoverPoint;
      { KeyValueMap* copy = self000;
        Object* map = self->theMap;

        if (self->crossoverPoint == 0) {
          copy->theMap = ((StellaHashTable*)(map))->copy();
        }
        else {
          copy->theMap = copyKvConsList(((KvCons*)(map)));
        }
        return (copy);
      }
    }
  }
}

void KeyValueMap::clear() {
  // Reset `self' to have zero entries.
  { KeyValueMap* self = this;

    self->theMap = NULL;
    self->crossoverPoint = oKEY_VALUE_MAP_CROSSOVER_POINTo;
  }
}

AbstractIterator* KeyValueMap::allocateIterator() {
  // Allocate an iterator for `self'.  The only modifying
  // operations allowed during iteration are removal of the current element or
  // changing its value.  All other removal or insertion operations might lead
  // to corruption or undefined results.
  { KeyValueMap* self = this;

    { Object* map = self->theMap;

      if (self->crossoverPoint == 0) {
        return (((StellaHashTableIterator*)(((StellaHashTable*)(map))->allocateIterator())));
      }
      else {
        { KeyValueList* self000 = newKeyValueList();

          self000->theKvList = ((KvCons*)(map));
          { KvListIterator* value000 = ((KvListIterator*)(self000->allocateIterator()));

            return (value000);
          }
        }
      }
    }
  }
}

Cons* KeyValueMap::consify() {
  // Collect all entries of `self' into a cons list of
  // `(<key> <value>)' pairs and return the result.
  { KeyValueMap* self = this;

    { Cons* result = NIL;

      { Object* key = NULL;
        Object* value = NULL;
        DictionaryIterator* iter000 = ((DictionaryIterator*)(self->allocateIterator()));
        Cons* collect000 = NULL;

        for  (; iter000->nextP(); ) {
          key = iter000->key;
          value = iter000->value;
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(cons(key, cons(value, NIL)), NIL);
              if (result == NIL) {
                result = collect000;
              }
              else {
                addConsToEndOfConsList(result, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(cons(key, cons(value, NIL)), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      return (result);
    }
  }
}

boolean KeyValueMap::objectEqualP(Object* y) {
  // Return TRUE if `x' and `y' represent the same set of key/value pairs.
  { KeyValueMap* x = this;

    if (subtypeOfP(safePrimaryType(y), SGT_COLLECTIONS_STELLA_KEY_VALUE_MAP)) {
      { Object* y000 = y;
        KeyValueMap* y = ((KeyValueMap*)(y000));

        if (x->length() == y->length()) {
          { Object* key = NULL;
            Object* value = NULL;
            DictionaryIterator* iter000 = ((DictionaryIterator*)(x->allocateIterator()));

            for  (; iter000->nextP(); ) {
              key = iter000->key;
              value = iter000->value;
              if (!equalP(value, y->lookup(key))) {
                return (false);
              }
            }
          }
          return (true);
        }
      }
    }
    else {
    }
    return (false);
  }
}

int KeyValueMap::equalHashCode() {
  // Return an `equal?' hash code for `self'.  Note that this
  // is O(N) in the number of entries of `self'.
  { KeyValueMap* self = this;

    { int code = 2137005;

      { Object* key = NULL;
        Object* value = NULL;
        DictionaryIterator* iter000 = ((DictionaryIterator*)(self->allocateIterator()));

        for  (; iter000->nextP(); ) {
          key = iter000->key;
          value = iter000->value;
          code = (code ^ (key->equalHashCode()));
          code = (code ^ (value->equalHashCode()));
        }
      }
      return (code);
    }
  }
}

HashSet* newHashSet() {
  { HashSet* self = NULL;

    self = new HashSet();
    self->crossoverPoint = oKEY_VALUE_MAP_CROSSOVER_POINTo;
    self->initialSize = oKEY_VALUE_MAP_CROSSOVER_POINTo;
    self->equalTestP = false;
    self->theMap = NULL;
    return (self);
  }
}

Surrogate* HashSet::primaryType() {
  { HashSet* self = this;

    return (SGT_COLLECTIONS_STELLA_HASH_SET);
  }
}

HashSet* hashSet(int values, ...) {
  // Return an `eql?' HASH-SET containing `values'.
  { HashSet* set = newHashSet();

    { va_list iter000;
      int iter000Count = values;
      Object* v = NULL;

      va_start(iter000, values);
            for  (; (iter000Count--) > 0; ) {
        v = va_arg(iter000, Object*);
        set->insertAt(v, v);
      }
      va_end(iter000);
    }
    return (set);
  }
}

HashSet* coerceToHashSet(Object* self, boolean equaltestP) {
  // Coerce the collection `self' into a HASH-SET.  Use an
  // equal test if `equalTest?' is TRUE (`equalTest?' will be ignored if `self'
  // already is a HASH-SET).
  { HashSet* chooseValue000 = NULL;

    if (isaP(self, SGT_COLLECTIONS_STELLA_HASH_SET)) {
      chooseValue000 = ((HashSet*)(self));
    }
    else {
      { HashSet* self000 = newHashSet();

        self000->equalTestP = equaltestP;
        chooseValue000 = self000;
      }
    }
    { HashSet* theset = chooseValue000;

      { Surrogate* testValue000 = safePrimaryType(self);

        if (subtypeOfP(testValue000, SGT_COLLECTIONS_STELLA_HASH_SET)) {
          { Object* self001 = self;
            HashSet* self = ((HashSet*)(self001));

          }
        }
        else if (testValue000 == SGT_COLLECTIONS_STELLA_CONS) {
          { Object* self002 = self;
            Cons* self = ((Cons*)(self002));

            { Object* elt = NULL;
              Cons* iter000 = self;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                elt = iter000->value;
                theset->insertAt(elt, elt);
              }
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_COLLECTIONS_STELLA_LIST)) {
          { Object* self003 = self;
            List* self = ((List*)(self003));

            { Object* elt = NULL;
              Cons* iter001 = self->theConsList;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                elt = iter001->value;
                theset->insertAt(elt, elt);
              }
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_COLLECTIONS_STELLA_VECTOR)) {
          { Object* self004 = self;
            Vector* self = ((Vector*)(self004));

            { Object* elt = NULL;
              Vector* vector000 = self;
              int index000 = 0;
              int length000 = vector000->length();

              for  (; index000 < length000; 
                    index000 = index000 + 1) {
                elt = (vector000->theArray)[index000];
                theset->insertAt(elt, elt);
              }
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_COLLECTIONS_STELLA_COLLECTION)) {
          { Object* self005 = self;
            Collection* self = ((Collection*)(self005));

            { Object* elt = NULL;
              Iterator* iter002 = ((Iterator*)(self->allocateIterator()));

              for (; iter002->nextP(); ) {
                elt = iter002->value;
                theset->insertAt(elt, elt);
              }
            }
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "coerce-to-hash-set: don't know how to coerce a " << "`" << self->primaryType() << "'" << " into a hash-set";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      return (theset);
    }
  }
}

boolean HashSet::memberP(Object* object) {
  // Return TRUE iff `object' is a member of the set `self'.
  // Uses an `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.
  { HashSet* self = this;

    return (((boolean)(self->lookup(object))));
  }
}

void HashSet::insert(Object* value) {
  // Add `value' to the set `self' unless it is already a member.
  // Uses an `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.
  { HashSet* self = this;

    self->insertAt(value, value);
  }
}

AbstractCollection* HashSet::remove(Object* value) {
  // Destructively remove `value' from the set `self' if it is a member and
  // return `self'.  Uses an `eql?' test by default or `equal?' if `equal-test?' of
  // `self' is TRUE.
  { HashSet* self = this;

    self->removeAt(value);
    return (self);
  }
}

HashSet* HashSet::removeIf(cpp_function_code testP) {
  // Destructively remove all elements of the set `self' for which
  // 'test?' evaluates to TRUE.  `test?' takes a single argument of type OBJECT and
  // returns TRUE or FALSE.  Returns `self'.
  { HashSet* self = this;

    { Object* element = NULL;
      DictionaryIterator* iter000 = ((DictionaryIterator*)(self->allocateIterator()));

      for (; iter000->nextP(); ) {
        element = iter000->value;
        if (((boolean  (*) (Object*))testP)(element)) {
          self->removeAt(element);
        }
      }
    }
    return (self);
  }
}

Object* HashSet::pop() {
  // Remove and return an arbitrary element of the set `self'.
  // Return NULL if the set is empty.  Performance note: for large sets implemented
  // via hash tables it takes O(N) to empty out the set with repeated calls to `pop',
  // since the emptier the table gets, the longer it takes to find an element.
  // Therefore, it is usually better to use iteration with embedded removals for
  // such cases.
  { HashSet* self = this;

    { Object* element = NULL;
      Object* setmap = self->theMap;

      if (((boolean)(setmap))) {
        if (self->crossoverPoint == 0) {
          { StellaHashTable* map = ((StellaHashTable*)(setmap));
            KvCons** table = map->theTable;
            KvCons* bucket = NULL;

            if (table != NULL) {
              { int i = NULL_INTEGER;
                int iter000 = 0;
                int upperBound000 = map->size - 1;

                for  (; iter000 <= upperBound000; 
                      iter000 = iter000 + 1) {
                  i = iter000;
                  bucket = table[i];
                  if (((boolean)(bucket))) {
                    element = bucket->key;
                    break;
                  }
                }
              }
            }
          }
        }
        else {
          { KvCons* map = ((KvCons*)(self->theMap));

            if (((boolean)(map))) {
              element = map->key;
            }
          }
        }
      }
      if (((boolean)(element))) {
        self->removeAt(element);
      }
      return (element);
    }
  }
}

HashSet* HashSet::substitute(Object* neW, Object* old) {
  // Destructively replace `old' with `new' in the set `self'
  // unless `new' is already a member.  Uses an `eql?' test by default or `equal?'
  // if `equal-test?' of `self' is TRUE.
  { HashSet* self = this;

    if (!self->memberP(neW)) {
      self->removeAt(old);
      self->insertAt(neW, neW);
    }
    return (self);
  }
}

KeyValueMap* HashSet::copy() {
  // Return a copy of the set `self'.  All entries are freshly
  // allocated, however, the values are not copied themselves (similar to what we
  // do for lists, etc.).
  { HashSet* self = this;

    { HashSet* self000 = newHashSet();

      self000->equalTestP = self->equalTestP;
      self000->initialSize = self->initialSize;
      self000->crossoverPoint = self->crossoverPoint;
      { HashSet* copy = self000;
        Object* map = self->theMap;

        if (self->crossoverPoint == 0) {
          copy->theMap = ((StellaHashTable*)(map))->copy();
        }
        else {
          copy->theMap = copyKvConsList(((KvCons*)(map)));
        }
        return (copy);
      }
    }
  }
}

Cons* HashSet::consify() {
  // Collect all entries of `self' into a cons list and return the result.
  { HashSet* self = this;

    { Cons* result = NIL;

      { Object* value = NULL;
        DictionaryIterator* iter000 = ((DictionaryIterator*)(self->allocateIterator()));
        Cons* collect000 = NULL;

        for  (; iter000->nextP(); ) {
          value = iter000->value;
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(value, NIL);
              if (result == NIL) {
                result = collect000;
              }
              else {
                addConsToEndOfConsList(result, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(value, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      return (result);
    }
  }
}

boolean HashSet::subsetP(HashSet* otherset) {
  // Return true if every element of `self' also occurs in `otherSet'.
  // Uses an `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.
  { HashSet* self = this;

    { boolean testValue000 = false;

      testValue000 = self->length() <= otherset->length();
      if (testValue000) {
        { boolean alwaysP000 = true;

          { Object* elt = NULL;
            DictionaryIterator* iter000 = ((DictionaryIterator*)(self->allocateIterator()));

            for (; iter000->nextP(); ) {
              elt = iter000->value;
              if (!((boolean)(otherset->lookup(elt)))) {
                alwaysP000 = false;
                break;
              }
            }
          }
          testValue000 = alwaysP000;
        }
      }
      { boolean value000 = testValue000;

        return (value000);
      }
    }
  }
}

boolean HashSet::equivalentSetsP(HashSet* otherset) {
  // Return true if every element of `self' occurs in `otherSet' and vice versa.
  // Uses an `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.
  { HashSet* self = this;

    { boolean testValue000 = false;

      testValue000 = self->length() == otherset->length();
      if (testValue000) {
        { boolean alwaysP000 = true;

          { Object* elt = NULL;
            DictionaryIterator* iter000 = ((DictionaryIterator*)(self->allocateIterator()));

            for (; iter000->nextP(); ) {
              elt = iter000->value;
              if (!((boolean)(otherset->lookup(elt)))) {
                alwaysP000 = false;
                break;
              }
            }
          }
          testValue000 = alwaysP000;
        }
      }
      { boolean value000 = testValue000;

        return (value000);
      }
    }
  }
}

HashSet* HashSet::intersection(HashSet* otherset) {
  // Return the set intersection of `self' and `otherSet' as a new set.
  // Uses an `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.
  { HashSet* self = this;

    { HashSet* self000 = newHashSet();

      self000->equalTestP = self->equalTestP;
      { HashSet* result = self000;
        HashSet* aux = self;

        if (self->length() > otherset->length()) {
          self = otherset;
          otherset = aux;
        }
        { Object* elt = NULL;
          DictionaryIterator* iter000 = ((DictionaryIterator*)(self->allocateIterator()));

          for (; iter000->nextP(); ) {
            elt = iter000->value;
            if (((boolean)(otherset->lookup(elt)))) {
              result->insertAt(elt, elt);
            }
          }
        }
        return (result);
      }
    }
  }
}

HashSet* HashSet::unioN(HashSet* otherset) {
  // Return the set union of `self' and `otherSet' as a new set.
  // Uses an `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.
  { HashSet* self = this;

    { HashSet* result = NULL;
      HashSet* aux = self;

      if (self->length() < otherset->length()) {
        self = otherset;
        otherset = aux;
      }
      result = ((HashSet*)(self->copy()));
      { Object* elt = NULL;
        DictionaryIterator* iter000 = ((DictionaryIterator*)(otherset->allocateIterator()));

        for (; iter000->nextP(); ) {
          elt = iter000->value;
          result->insertAt(elt, elt);
        }
      }
      return (result);
    }
  }
}

HashSet* HashSet::difference(HashSet* otherset) {
  // Return the set difference of `self' and `otherSet' as a new set (i.e.,
  // all elements that are in `self' but not in `otherSet').  Uses an `eql?' test
  // by default or `equal?' if `equal-test?' of `self' is TRUE.
  { HashSet* self = this;

    { HashSet* result = NULL;

      if (self->length() > (otherset->length() * 2)) {
        result = ((HashSet*)(self->copy()));
        { Object* elt = NULL;
          DictionaryIterator* iter000 = ((DictionaryIterator*)(otherset->allocateIterator()));

          for (; iter000->nextP(); ) {
            elt = iter000->value;
            if (((boolean)(result->lookup(elt)))) {
              result->removeAt(elt);
            }
          }
        }
      }
      else {
        { HashSet* self000 = newHashSet();

          self000->equalTestP = self->equalTestP;
          result = self000;
        }
        { Object* elt = NULL;
          DictionaryIterator* iter001 = ((DictionaryIterator*)(self->allocateIterator()));

          for (; iter001->nextP(); ) {
            elt = iter001->value;
            if (!((boolean)(otherset->lookup(elt)))) {
              result->insertAt(elt, elt);
            }
          }
        }
      }
      return (result);
    }
  }
}

HashSet* HashSet::subtract(HashSet* otherset) {
  // Return the set difference of `self' and `otherSet' by destructively
  // removing elements from `self' that also occur in `otherSet'.  Uses an `eql?'
  // test by default or `equal?' if `equal-test?' of `self' is TRUE.
  { HashSet* self = this;

    { Object* elt = NULL;
      DictionaryIterator* iter000 = ((DictionaryIterator*)(self->allocateIterator()));

      for (; iter000->nextP(); ) {
        elt = iter000->value;
        if (((boolean)(otherset->lookup(elt)))) {
          self->removeAt(elt);
        }
      }
    }
    return (self);
  }
}

boolean HashSet::objectEqualP(Object* y) {
  // Return TRUE iff sets `x' and `y' are HASH-SET's with equivalent members.
  // Uses an `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.
  // This is equivalent to calling `equivalent-sets?'.
  { HashSet* x = this;

    if (subtypeOfP(safePrimaryType(y), SGT_COLLECTIONS_STELLA_HASH_SET)) {
      { Object* y000 = y;
        HashSet* y = ((HashSet*)(y000));

        return (x->equivalentSetsP(y));
      }
    }
    else {
    }
    return (false);
  }
}

int HashSet::equalHashCode() {
  // Return an `equal?' hash code for `self'.  Note that this
  // is O(N) in the number of elements of `self'.
  { HashSet* self = this;

    { int code = 7971569;

      { Object* elt = NULL;
        DictionaryIterator* iter000 = ((DictionaryIterator*)(self->allocateIterator()));

        for (; iter000->nextP(); ) {
          elt = iter000->value;
          code = (code ^ (elt->equalHashCode()));
        }
      }
      return (code);
    }
  }
}

oneDArray* new1DArray(int dim1) {
  { oneDArray* self = NULL;

    self = new oneDArray();
    self->dim1 = dim1;
    self->theArray = NULL;
    self->initializeDimensionalArray();
    return (self);
  }
}

Surrogate* oneDArray::primaryType() {
  { oneDArray* self = this;

    return (SGT_COLLECTIONS_STELLA_1D_ARRAY);
  }
}

int oneDArray::oneDArefAddress(int i) {
  // Return the 1D address of the element at position `[i]'.
  // This is useful for fast element-wise iteration that doesn't need arithmetic.
  { oneDArray* self = this;

    return (i);
  }
}

Object* oneDArray::oneDArefSetter(Object* value, int i) {
  // Set the element of `self' at position `[i]' to `value'
  // and return the result.
  { oneDArray* self = this;

    return (self->theArray[i] = value);
  }
}

Object* oneDArray::oneDAref(int i) {
  // Return the element of `self' at position `[i]'.
  { oneDArray* self = this;

    return (self->theArray[i]);
  }
}

void oneDArray::initializeArray(Object* initialvalue) {
  // Initialize the elements of `self' with `initialValue'.
  { oneDArray* self = this;

    { Object** array = self->theArray;

      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = self->length() - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          array[i] = initialvalue;
        }
      }
    }
  }
}

int oneDArray::length() {
  // Return the total number of elements in `self'.
  { oneDArray* self = this;

    return (self->dim1);
  }
}

void oneDArray::initializeDimensionalArray() {
  { oneDArray* self = this;

    self->theArray = new (GC)Object*[self->length()];
  }
}

oneDFloatArray* new1DFloatArray(int dim1) {
  { oneDFloatArray* self = NULL;

    self = new oneDFloatArray();
    self->dim1 = dim1;
    self->theArray = NULL;
    self->initializeDimensionalArray();
    return (self);
  }
}

Surrogate* oneDFloatArray::primaryType() {
  { oneDFloatArray* self = this;

    return (SGT_COLLECTIONS_STELLA_1D_FLOAT_ARRAY);
  }
}

int oneDFloatArray::oneDArefAddress(int i) {
  // Return the 1D address of the element at position `[i]'.
  // This is useful for fast element-wise iteration that doesn't need arithmetic.
  { oneDFloatArray* self = this;

    return (i);
  }
}

double oneDFloatArray::oneDArefSetter(double value, int i) {
  // Set the element of `self' at position `[i]' to `value'
  // and return the result.
  { oneDFloatArray* self = this;

    return (self->theArray[i] = value);
  }
}

double oneDFloatArray::oneDAref(int i) {
  // Return the element of `self' at position `[i]'.
  { oneDFloatArray* self = this;

    return (self->theArray[i]);
  }
}

void oneDFloatArray::initializeArray(double initialvalue) {
  // Initialize the elements of `self' with `initialValue'.
  { oneDFloatArray* self = this;

    { double* array = self->theArray;

      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = self->length() - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          array[i] = initialvalue;
        }
      }
    }
  }
}

int oneDFloatArray::length() {
  // Return the total number of elements in `self'.
  { oneDFloatArray* self = this;

    return (self->dim1);
  }
}

void oneDFloatArray::initializeDimensionalArray() {
  { oneDFloatArray* self = this;

    self->theArray = new (PointerFreeGC)double[self->length()];
  }
}

twoDArray* new2DArray(int dim2, int dim1) {
  { twoDArray* self = NULL;

    self = new twoDArray();
    self->dim2 = dim2;
    self->dim1 = dim1;
    self->theArray = NULL;
    self->initializeDimensionalArray();
    return (self);
  }
}

Surrogate* twoDArray::primaryType() {
  { twoDArray* self = this;

    return (SGT_COLLECTIONS_STELLA_2D_ARRAY);
  }
}

int twoDArray::twoDArefAddress(int i, int j) {
  // Return the 1D address of the element at position `[i, j]'.
  // This is useful for fast element-wise iteration that doesn't need arithmetic.
  { twoDArray* self = this;

    return ((i * self->dim2) + j);
  }
}

Object* twoDArray::twoDArefSetter(Object* value, int i, int j) {
  // Set the element of `self' at position `[i, j]' to `value'
  // and return the result.
  { twoDArray* self = this;

    return (self->theArray[(i * self->dim2) + j] = value);
  }
}

Object* twoDArray::twoDAref(int i, int j) {
  // Return the element of `self' at position `[i, j]'.
  { twoDArray* self = this;

    return (self->theArray[(i * self->dim2) + j]);
  }
}

int twoDArray::length() {
  // Return the total number of elements in `self'.
  { twoDArray* self = this;

    return (self->dim1 * self->dim2);
  }
}

int twoDArray::oneDArefAddress(int i) {
  // Return the 1D address of the element at position `[i]'.
  // This is useful for fast element-wise iteration that doesn't need arithmetic.
  { twoDArray* self = this;

    return (i);
  }
}

Object* twoDArray::oneDArefSetter(Object* value, int i) {
  // Set the element of `self' at position `[i]' to `value'
  // and return the result.
  { twoDArray* self = this;

    return (self->theArray[i] = value);
  }
}

Object* twoDArray::oneDAref(int i) {
  // Return the element of `self' at position `[i]'.
  { twoDArray* self = this;

    return (self->theArray[i]);
  }
}

void twoDArray::initializeArray(Object* initialvalue) {
  // Initialize the elements of `self' with `initialValue'.
  { twoDArray* self = this;

    { Object** array = self->theArray;

      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = self->length() - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          array[i] = initialvalue;
        }
      }
    }
  }
}

void twoDArray::initializeDimensionalArray() {
  { twoDArray* self = this;

    self->theArray = new (GC)Object*[self->length()];
  }
}

twoDFloatArray* new2DFloatArray(int dim2, int dim1) {
  { twoDFloatArray* self = NULL;

    self = new twoDFloatArray();
    self->dim2 = dim2;
    self->dim1 = dim1;
    self->theArray = NULL;
    self->initializeDimensionalArray();
    return (self);
  }
}

Surrogate* twoDFloatArray::primaryType() {
  { twoDFloatArray* self = this;

    return (SGT_COLLECTIONS_STELLA_2D_FLOAT_ARRAY);
  }
}

int twoDFloatArray::twoDArefAddress(int i, int j) {
  // Return the 1D address of the element at position `[i, j]'.
  // This is useful for fast element-wise iteration that doesn't need arithmetic.
  { twoDFloatArray* self = this;

    return ((i * self->dim2) + j);
  }
}

double twoDFloatArray::twoDArefSetter(double value, int i, int j) {
  // Set the element of `self' at position `[i, j]' to `value'
  // and return the result.
  { twoDFloatArray* self = this;

    return (self->theArray[(i * self->dim2) + j] = value);
  }
}

double twoDFloatArray::twoDAref(int i, int j) {
  // Return the element of `self' at position `[i, j]'.
  { twoDFloatArray* self = this;

    return (self->theArray[(i * self->dim2) + j]);
  }
}

int twoDFloatArray::length() {
  // Return the total number of elements in `self'.
  { twoDFloatArray* self = this;

    return (self->dim1 * self->dim2);
  }
}

int twoDFloatArray::oneDArefAddress(int i) {
  // Return the 1D address of the element at position `[i]'.
  // This is useful for fast element-wise iteration that doesn't need arithmetic.
  { twoDFloatArray* self = this;

    return (i);
  }
}

double twoDFloatArray::oneDArefSetter(double value, int i) {
  // Set the element of `self' at position `[i]' to `value'
  // and return the result.
  { twoDFloatArray* self = this;

    return (self->theArray[i] = value);
  }
}

double twoDFloatArray::oneDAref(int i) {
  // Return the element of `self' at position `[i]'.
  { twoDFloatArray* self = this;

    return (self->theArray[i]);
  }
}

void twoDFloatArray::initializeArray(double initialvalue) {
  // Initialize the elements of `self' with `initialValue'.
  { twoDFloatArray* self = this;

    { double* array = self->theArray;

      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = self->length() - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          array[i] = initialvalue;
        }
      }
    }
  }
}

void twoDFloatArray::initializeDimensionalArray() {
  { twoDFloatArray* self = this;

    self->theArray = new (PointerFreeGC)double[self->length()];
  }
}

Object** oneDArray::theArrayReader() {
  { oneDArray* self = this;

    return (self->theArray);
  }
}

double* oneDFloatArray::theArrayReader() {
  { oneDFloatArray* self = this;

    return (self->theArray);
  }
}

Object** twoDArray::theArrayReader() {
  { twoDArray* self = this;

    return (self->theArray);
  }
}

double* twoDFloatArray::theArrayReader() {
  { twoDFloatArray* self = this;

    return (self->theArray);
  }
}

BufferedString* newBufferedString() {
  { BufferedString* self = NULL;

    self = new BufferedString();
    self->fillPointer = 0;
    self->bufferSize = 16;
    self->buffer = makeRawMutableString(16);
    return (self);
  }
}

Surrogate* BufferedString::primaryType() {
  { BufferedString* self = this;

    return (SGT_COLLECTIONS_STELLA_BUFFERED_STRING);
  }
}

Object* accessBufferedStringSlotValue(BufferedString* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_COLLECTIONS_STELLA_BUFFER) {
    if (setvalueP) {
      self->buffer = ((MutableStringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapMutableString(self->buffer);
    }
  }
  else if (slotname == SYM_COLLECTIONS_STELLA_BUFFER_SIZE) {
    if (setvalueP) {
      self->bufferSize = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->bufferSize);
    }
  }
  else if (slotname == SYM_COLLECTIONS_STELLA_FILL_POINTER) {
    if (setvalueP) {
      self->fillPointer = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->fillPointer);
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

char* BufferedString::resizeBuffer(int size) {
  // Change the size of `self' to `size'.  If `size' is smaller
  // than the current size of `self', it's buffer will be truncated.
  { BufferedString* self = this;

    { int oldsize = self->bufferSize;
      char* oldbuffer = self->buffer;
      char* newbuffer = oldbuffer;

      if (oldsize == 0) {
        newbuffer = makeRawMutableString(size);
        self->buffer = newbuffer;
        self->bufferSize = size;
      }
      else if (size == oldsize) {
      }
      else {
        { int l = self->fillPointer;

          newbuffer = makeRawMutableString(size);
          self->buffer = newbuffer;
          self->bufferSize = size;
          if (size < l) {
            l = size;
            self->fillPointer = l;
          }
          while (l > 0) {
            l = l - 1;
            newbuffer[l] = (oldbuffer[l]);
          }
        }
      }
      return (newbuffer);
    }
  }
}

char* BufferedString::ensureFreeSpace(int size) {
  // Ensure `self' is big enough to accommodate an additional item of `size'.
  { BufferedString* self = this;

    if ((self->fillPointer + size) > self->bufferSize) {
      return (self->resizeBuffer(stella::integerMax(self->bufferSize * 2, self->fillPointer + size)));
    }
    else {
      return (self->buffer);
    }
  }
}

int BufferedString::freeSpace() {
  // Return the amount of free space in `self'.
  { BufferedString* self = this;

    return (self->bufferSize - self->fillPointer);
  }
}

int BufferedString::length() {
  { BufferedString* self = this;

    return (self->fillPointer);
  }
}

int BufferedString::lengthSetter(int newlength) {
  // Reset the length of `self' to `newLength'.  Fill in NULL characters if `newLength' 
  // is greater than the current length.  This is the safe way to reset the fill pointer.
  { BufferedString* self = this;

    { int fp = self->fillPointer;

      if (newlength < 0) {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Out-of-bounds: cannot set string buffer to negative length: " << "`" << newlength << "'";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      else if (newlength < fp) {
        self->fillPointer = newlength;
      }
      else if (newlength > fp) {
        self->ensureFreeSpace(newlength - fp);
        { char* buf = self->buffer;

          while (fp < newlength) {
            buf[fp] = NULL_CHARACTER;
            fp = fp + 1;
          }
          self->fillPointer = newlength;
        }
      }
      return (newlength);
    }
  }
}

boolean BufferedString::emptyP() {
  // Return `true' if `self' has length 0.
  { BufferedString* self = this;

    return (self->fillPointer == 0);
  }
}

boolean BufferedString::nonEmptyP() {
  // Return `true' if `self' has length > 0.
  { BufferedString* self = this;

    return (self->fillPointer > 0);
  }
}

char BufferedString::nth(int position) {
  // Return the character in `self' at `position'.
  { BufferedString* self = this;

    return ((self->buffer)[position]);
  }
}

char BufferedString::nthSetter(char ch, int position) {
  // Set the character in `self' at `position' to `ch'.
  { BufferedString* self = this;

    return ((self->buffer)[position] = ch);
  }
}

char BufferedString::last() {
  // Return the last character in `self'.
  { BufferedString* self = this;

    return ((self->buffer)[(self->fillPointer - 1)]);
  }
}

char BufferedString::lastSetter(char value) {
  { BufferedString* self = this;

    return ((self->buffer)[(self->fillPointer - 1)] = value);
  }
}

void BufferedString::appendString(const char* value) {
  // Append `value' to the END of the string `self'.  
  // Resize the buffer if necessary.
  { BufferedString* self = this;

    { int vallength = strlen(value);
      int valcursor = 0;
      int bufsize = self->bufferSize;
      int bufcursor = self->fillPointer;
      char* buffer = self->buffer;

      if ((bufcursor + vallength) > bufsize) {
        buffer = self->resizeBuffer(stella::integerMax(bufsize * 2, bufcursor + vallength));
      }
      while (valcursor < vallength) {
        buffer[bufcursor] = (value[valcursor]);
        valcursor = valcursor + 1;
        bufcursor = bufcursor + 1;
      }
      self->fillPointer = bufcursor;
    }
  }
}

void BufferedString::appendCharacter(char chaR) {
  // Append `char' to the END of the string `self'.  
  // Resize the buffer if necessary.
  { BufferedString* self = this;

    { int bufsize = self->bufferSize;
      int bufcursor = self->fillPointer;
      char* buffer = self->buffer;

      if (bufcursor >= bufsize) {
        buffer = self->resizeBuffer(stella::integerMax(bufsize, 1) * 2);
      }
      buffer[bufcursor] = chaR;
      self->fillPointer = bufcursor + 1;
    }
  }
}

char BufferedString::pop() {
  { BufferedString* self = this;

    { int bufcursor = self->fillPointer;

      if (bufcursor > 0) {
        bufcursor = bufcursor - 1;
        self->fillPointer = bufcursor;
        return ((self->buffer)[bufcursor]);
      }
      else {
        return (NULL_CHARACTER);
      }
    }
  }
}

BufferedString* BufferedString::copy() {
  { BufferedString* self = this;

    { BufferedString* self000 = newBufferedString();

      self000->bufferSize = self->bufferSize;
      self000->fillPointer = self->fillPointer;
      { BufferedString* copy = self000;

        copy->buffer = stringToMutableString(mutableStringSubsequence(self->buffer, 0, NULL_INTEGER));
        return (copy);
      }
    }
  }
}

void BufferedString::clear() {
  // Clear `self' by setting its active length to zero.
  { BufferedString* self = this;

    self->fillPointer = 0;
  }
}

const char* BufferedString::theString() {
  // Return a substring of `string' beginning at position `start'
  // and ending up to but not including position `end', counting from zero.  An
  // `end' value of NULL stands for the rest of the string.
  { BufferedString* self = this;

    return (mutableStringSubsequence(self->buffer, 0, self->fillPointer));
  }
}

const char* BufferedString::subsequence(int start, int end) {
  // Return a substring of `string' beginning at position `start'
  // and ending up to but not including position `end', counting from zero.  An
  // `end' value of NULL stands for the rest of the string.
  { BufferedString* self = this;

    if (end == NULL_INTEGER) {
      end = self->fillPointer;
    }
    return (mutableStringSubsequence(self->buffer, start, end));
  }
}

void helpStartupCollections1() {
  {
    SGT_COLLECTIONS_STELLA_COLLECTION = ((Surrogate*)(internRigidSymbolWrtModule("COLLECTION", NULL, 1)));
    SGT_COLLECTIONS_STELLA_SET = ((Surrogate*)(internRigidSymbolWrtModule("SET", NULL, 1)));
    SYM_COLLECTIONS_STELLA_VECTOR = ((Symbol*)(internRigidSymbolWrtModule("VECTOR", NULL, 0)));
    KWD_COLLECTIONS_CPP = ((Keyword*)(internRigidSymbolWrtModule("CPP", NULL, 2)));
    KWD_COLLECTIONS_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SGT_COLLECTIONS_STELLA_VECTOR = ((Surrogate*)(internRigidSymbolWrtModule("VECTOR", NULL, 1)));
    SGT_COLLECTIONS_STELLA_VECTOR_SEQUENCE = ((Surrogate*)(internRigidSymbolWrtModule("VECTOR-SEQUENCE", NULL, 1)));
    SGT_COLLECTIONS_STELLA_HEAP = ((Surrogate*)(internRigidSymbolWrtModule("HEAP", NULL, 1)));
    SYM_COLLECTIONS_STELLA_PREDICATE = ((Symbol*)(internRigidSymbolWrtModule("PREDICATE", NULL, 0)));
    SYM_COLLECTIONS_STELLA_FILL_POINTER = ((Symbol*)(internRigidSymbolWrtModule("FILL-POINTER", NULL, 0)));
    SGT_COLLECTIONS_STELLA_STELLA_HASH_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("STELLA-HASH-TABLE", NULL, 1)));
    SYM_COLLECTIONS_STELLA_SIZE = ((Symbol*)(internRigidSymbolWrtModule("SIZE", NULL, 0)));
    SYM_COLLECTIONS_STELLA_INITIAL_SIZE = ((Symbol*)(internRigidSymbolWrtModule("INITIAL-SIZE", NULL, 0)));
    SYM_COLLECTIONS_STELLA_FREE_ELEMENTS = ((Symbol*)(internRigidSymbolWrtModule("FREE-ELEMENTS", NULL, 0)));
    SYM_COLLECTIONS_STELLA_EQUAL_TESTp = ((Symbol*)(internRigidSymbolWrtModule("EQUAL-TEST?", NULL, 0)));
    SGT_COLLECTIONS_STELLA_STELLA_HASH_TABLE_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("STELLA-HASH-TABLE-ITERATOR", NULL, 1)));
    SYM_COLLECTIONS_STELLA_BUCKET_INDEX = ((Symbol*)(internRigidSymbolWrtModule("BUCKET-INDEX", NULL, 0)));
    SYM_COLLECTIONS_STELLA_BUCKET_CURSOR = ((Symbol*)(internRigidSymbolWrtModule("BUCKET-CURSOR", NULL, 0)));
    SGT_COLLECTIONS_STELLA_KEY_VALUE_MAP = ((Surrogate*)(internRigidSymbolWrtModule("KEY-VALUE-MAP", NULL, 1)));
    SYM_COLLECTIONS_STELLA_THE_MAP = ((Symbol*)(internRigidSymbolWrtModule("THE-MAP", NULL, 0)));
    SYM_COLLECTIONS_STELLA_CROSSOVER_POINT = ((Symbol*)(internRigidSymbolWrtModule("CROSSOVER-POINT", NULL, 0)));
    SGT_COLLECTIONS_STELLA_HASH_SET = ((Surrogate*)(internRigidSymbolWrtModule("HASH-SET", NULL, 1)));
    SGT_COLLECTIONS_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SGT_COLLECTIONS_STELLA_LIST = ((Surrogate*)(internRigidSymbolWrtModule("LIST", NULL, 1)));
    SGT_COLLECTIONS_STELLA_1D_ARRAY = ((Surrogate*)(internRigidSymbolWrtModule("1D-ARRAY", NULL, 1)));
    SYM_COLLECTIONS_STELLA_OBJECT_ARRAY = ((Symbol*)(internRigidSymbolWrtModule("OBJECT-ARRAY", NULL, 0)));
    SGT_COLLECTIONS_STELLA_1D_FLOAT_ARRAY = ((Surrogate*)(internRigidSymbolWrtModule("1D-FLOAT-ARRAY", NULL, 1)));
    SYM_COLLECTIONS_STELLA_FLOAT_ARRAY = ((Symbol*)(internRigidSymbolWrtModule("FLOAT-ARRAY", NULL, 0)));
    SGT_COLLECTIONS_STELLA_2D_ARRAY = ((Surrogate*)(internRigidSymbolWrtModule("2D-ARRAY", NULL, 1)));
    SGT_COLLECTIONS_STELLA_2D_FLOAT_ARRAY = ((Surrogate*)(internRigidSymbolWrtModule("2D-FLOAT-ARRAY", NULL, 1)));
    SGT_COLLECTIONS_STELLA_BUFFERED_STRING = ((Surrogate*)(internRigidSymbolWrtModule("BUFFERED-STRING", NULL, 1)));
    SYM_COLLECTIONS_STELLA_BUFFER = ((Symbol*)(internRigidSymbolWrtModule("BUFFER", NULL, 0)));
    SYM_COLLECTIONS_STELLA_BUFFER_SIZE = ((Symbol*)(internRigidSymbolWrtModule("BUFFER-SIZE", NULL, 0)));
    SYM_COLLECTIONS_STELLA_STRING_BUFFER = ((Symbol*)(internRigidSymbolWrtModule("STRING-BUFFER", NULL, 0)));
    SYM_COLLECTIONS_STELLA_STARTUP_COLLECTIONS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-COLLECTIONS", NULL, 0)));
    SYM_COLLECTIONS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupCollections2() {
  {
    { Class* clasS = defineClassFromStringifiedSource("HEAP", "(DEFCLASS HEAP (VECTOR) :DOCUMENTATION \"Implements a Min or Max heap depending on the semantics\nof `predicate' (Min if `predicate' has a `<' semantics).  This is useful\nfor in-place sorting (even though we have specialzed sort routines for that)\nor to maintain top-N lists with log(N) insertion time.  We place this under\nVECTOR instead of VECTOR-SEQUENCE for now, since sequential order isn't\nreally maintained or accessible until we sort the heap.\" :PUBLIC? TRUE :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :SLOTS ((PREDICATE :TYPE FUNCTION-CODE :REQUIRED? TRUE) (FILL-POINTER :TYPE INTEGER :INITIALLY 0)) :INITIALIZER INITIALIZE-HEAP)");

      clasS->classConstructorCode = ((cpp_function_code)(&newHeap));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessHeapSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("STELLA-HASH-TABLE", "(DEFCLASS STELLA-HASH-TABLE (ABSTRACT-HASH-TABLE) :PARAMETERS ((ANY-KEY :TYPE OBJECT) (ANY-VALUE :TYPE OBJECT)) :SLOTS ((THE-TABLE :TYPE (ARRAY () OF KV-CONS)) (SIZE :TYPE INTEGER) (INITIAL-SIZE :TYPE INTEGER :INITIALLY 50 :PUBLIC? TRUE :DOCUMENTATION \"If supplied, the initial hash table\nwill be sized to hold at least that many elements.\") (FREE-ELEMENTS :TYPE INTEGER) (EQUAL-TEST? :TYPE BOOLEAN :INITIALLY FALSE :PUBLIC? TRUE :DOCUMENTATION \"If true use `equal?' as the\nequality test and `equal-hash-code' as the hash function, otherwise,\nuse `eql?' and `hash-code' (the default).\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newStellaHashTable));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessStellaHashTableSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("STELLA-HASH-TABLE-ITERATOR", "(DEFCLASS STELLA-HASH-TABLE-ITERATOR (DICTIONARY-ITERATOR) :DOCUMENTATION \"Iterator class for STELLA-HASH-TABLE's.  The only modifying\noperations allowed during iteration are removal of the current element or\nchanging its value.  All other removal or insertion operations might lead\nto corruption or undefined results.\" :SLOTS ((SIZE :TYPE INTEGER) (BUCKET-TABLE :TYPE (ARRAY () OF KV-CONS)) (BUCKET-INDEX :TYPE INTEGER :INITIALLY 0) (BUCKET-CURSOR :TYPE KV-CONS)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newStellaHashTableIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessStellaHashTableIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("KEY-VALUE-MAP", "(DEFCLASS KEY-VALUE-MAP (DICTIONARY) :DOCUMENTATION \"Full-featured dictionary class that supports `eql?' or\n`equal?' equality tests, O(1) access operations even for large numbers\nof entries by using a hash table, light-weight KV-CONS representation for\nsmall tables and iteration even if the dictionary is represented by a\nhash table.\" :PUBLIC? TRUE :SLOTS ((THE-MAP :TYPE OBJECT) (EQUAL-TEST? :TYPE BOOLEAN :INITIALLY FALSE :PUBLIC? TRUE :DOCUMENTATION \"If true use `equal?' as the\nequality test (and `equal-hash-code' as the hash function), otherwise,\nuse `eql?' (and `hash-code') (the default).\") (INITIAL-SIZE :TYPE INTEGER :INITIALLY *KEY-VALUE-MAP-CROSSOVER-POINT* :PUBLIC? TRUE :DOCUMENTATION \"If supplied, the initial table\nwill be sized to hold at least that many elements.\") (CROSSOVER-POINT :TYPE INTEGER :INITIALLY *KEY-VALUE-MAP-CROSSOVER-POINT*)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newKeyValueMap));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessKeyValueMapSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("HASH-SET", "(DEFCLASS HASH-SET (KEY-VALUE-MAP SET-MIXIN) :DOCUMENTATION \"Full-featured set class that supports `eql?' or `equal?'\nequality tests, O(1) insert and `member?' operations & O(N) `intersection'\netc. operations even for large numbers of entries by using a hash table,\nlight-weight KV-CONS representation for small sets and iteration even if the\nset is represented by a hash table.  The only minor drawback right now is that\nthis wastes a value slot per entry, since we piggy-back off KEY-VALUE-MAP's,\nhowever, that wastes at most 25% space.\" :PUBLIC? TRUE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newHashSet));
    }
    defineClassFromStringifiedSource("DIMENSIONAL-ARRAY-MIXIN", "(DEFCLASS DIMENSIONAL-ARRAY-MIXIN () :MIXIN? TRUE :PARAMETERS ((ANY-VALUE :TYPE UNKNOWN)) :SLOTS ((DIM1 :TYPE INTEGER :REQUIRED? TRUE) (THE-ARRAY :TYPE (ARRAY () OF (LIKE (ANY-VALUE SELF))))) :INITIALIZER INITIALIZE-DIMENSIONAL-ARRAY)");
    defineClassFromStringifiedSource("2-DIMENSIONAL-ARRAY-MIXIN", "(DEFCLASS 2-DIMENSIONAL-ARRAY-MIXIN (DIMENSIONAL-ARRAY-MIXIN) :MIXIN? TRUE :PUBLIC? TRUE :SLOTS ((DIM2 :TYPE INTEGER :REQUIRED? TRUE)))");
    defineClassFromStringifiedSource("ABSTRACT-DIMENSIONAL-ARRAY", "(DEFCLASS ABSTRACT-DIMENSIONAL-ARRAY (ABSTRACT-COLLECTION) :DOCUMENTATION \"Array objects that are aware of their dimensions.\" :PUBLIC? TRUE :ABSTRACT? TRUE :PARAMETERS ((ANY-VALUE :TYPE UNKNOWN)))");
    { Class* clasS = defineClassFromStringifiedSource("1D-ARRAY", "(DEFCLASS 1D-ARRAY (ABSTRACT-DIMENSIONAL-ARRAY DIMENSIONAL-ARRAY-MIXIN) :DOCUMENTATION \"1-dimensional array with OBJECT values.  This is more or\nless equivalent to VECTOR (fewer methods) but kept here for symmetry.\" :PUBLIC? TRUE :SYNONYMS (OBJECT-ARRAY) :PARAMETERS ((ANY-VALUE :TYPE OBJECT)))");

      clasS->classConstructorCode = ((cpp_function_code)(&new1DArray));
    }
    { Class* clasS = defineClassFromStringifiedSource("1D-FLOAT-ARRAY", "(DEFCLASS 1D-FLOAT-ARRAY (ABSTRACT-DIMENSIONAL-ARRAY DIMENSIONAL-ARRAY-MIXIN) :DOCUMENTATION \"1-dimensional array with float values.\" :PUBLIC? TRUE :SYNONYMS (FLOAT-ARRAY) :PARAMETERS ((ANY-VALUE :TYPE FLOAT)))");

      clasS->classConstructorCode = ((cpp_function_code)(&new1DFloatArray));
    }
    { Class* clasS = defineClassFromStringifiedSource("2D-ARRAY", "(DEFCLASS 2D-ARRAY (ABSTRACT-DIMENSIONAL-ARRAY 2-DIMENSIONAL-ARRAY-MIXIN) :DOCUMENTATION \"2-dimensional array with object values.\" :PUBLIC? TRUE :PARAMETERS ((ANY-VALUE :TYPE OBJECT)))");

      clasS->classConstructorCode = ((cpp_function_code)(&new2DArray));
    }
    { Class* clasS = defineClassFromStringifiedSource("2D-FLOAT-ARRAY", "(DEFCLASS 2D-FLOAT-ARRAY (ABSTRACT-DIMENSIONAL-ARRAY 2-DIMENSIONAL-ARRAY-MIXIN) :DOCUMENTATION \"2-dimensional array with float values.\" :PUBLIC? TRUE :PARAMETERS ((ANY-VALUE :TYPE FLOAT)))");

      clasS->classConstructorCode = ((cpp_function_code)(&new2DFloatArray));
    }
    { Class* clasS = defineClassFromStringifiedSource("BUFFERED-STRING", "(DEFCLASS BUFFERED-STRING (STANDARD-OBJECT) :SYNONYMS (STRING-BUFFER) :SLOTS ((BUFFER :TYPE MUTABLE-STRING :INITIALLY (MAKE-RAW-MUTABLE-STRING 16)) (BUFFER-SIZE :TYPE INTEGER :INITIALLY 16) (FILL-POINTER :TYPE INTEGER :INITIALLY 0)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newBufferedString));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessBufferedStringSlotValue));
    }
  }
}

void helpStartupCollections3() {
  {
    defineMethodObject("(DEFMETHOD (MEMBER? BOOLEAN) ((SELF COLLECTION) (OBJECT OBJECT)) :DOCUMENTATION \"Return true iff `object' is a member of the collection `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Collection::memberP))), NULL);
    defineMethodObject("(DEFMETHOD (REMOVE-DUPLICATES (LIKE SELF)) ((SELF COLLECTION)) :DOCUMENTATION \"Return `self' with duplicates removed.  Preserves the\noriginal order of the remaining members.\" :PUBLIC? TRUE :ABSTRACT? TRUE)", NULL, NULL);
    defineFunctionObject("STELLA-COLLECTION?", "(DEFUN (STELLA-COLLECTION? BOOLEAN) ((SELF OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Return `true' if `self' is a native collection.\")", ((cpp_function_code)(&stellaCollectionP)), NULL);
    defineMethodObject("(DEFMETHOD (NO-DUPLICATES? BOOLEAN) ((SELF COLLECTION)) :PUBLIC? TRUE :DOCUMENTATION \"Return `true' if the collection `self' forbids duplicate values.\")", wrapMethodCode(((cpp_method_code)(&Collection::noDuplicatesP))), NULL);
    defineMethodObject("(DEFMETHOD (NO-DUPLICATES? BOOLEAN) ((SELF SET)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Set::noDuplicatesP))), NULL);
    defineMethodObject("(DEFMETHOD (ORDERED? BOOLEAN) ((SELF COLLECTION)) :PUBLIC? TRUE :DOCUMENTATION \"Return `true' if the collection `self' is ordered.\")", wrapMethodCode(((cpp_method_code)(&Collection::orderedP))), NULL);
    defineMethodObject("(DEFMETHOD (ORDERED? BOOLEAN) ((SELF SEQUENCE)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Sequence::orderedP))), NULL);
    defineMethodObject("(DEFMETHOD (ORDERED? BOOLEAN) ((SELF SET)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Set::orderedP))), NULL);
    defineMethodObject("(DEFMETHOD INSERT ((SELF SET) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE :DOCUMENTATION \"Add `value' to the set `self' unless it is already a member.\")", wrapMethodCode(((cpp_method_code)(&Set::insert))), NULL);
    defineMethodObject("(DEFMETHOD PUSH ((SELF SET) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE :DOCUMENTATION \"Add `value' to the front of set `self' unless it is already a member.\")", wrapMethodCode(((cpp_method_code)(&Set::push))), NULL);
    defineMethodObject("(DEFMETHOD INSERT-LAST ((SELF SET) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Add `value' to the end of set `self' unless it is already a member.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Set::insertLast))), NULL);
    defineMethodObject("(DEFMETHOD (REMOVE-DUPLICATES (LIKE SELF)) ((SELF SET)))", wrapMethodCode(((cpp_method_code)(&Set::removeDuplicates))), NULL);
    defineMethodObject("(DEFMETHOD (SUBSTITUTE (LIKE SELF)) ((SELF SET) (NEW OBJECT) (OLD OBJECT)) :DOCUMENTATION \"Destructively replace `old' with `new' in the set `self'\nunless `new' is already a member.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Set::substitute))), NULL);
    defineMethodObject("(DEFMETHOD (CONCATENATE SET) ((SET1 SET) (SET2 LIST) |&REST| (OTHERSETS LIST)) :DOCUMENTATION \"Union `set2' and all `otherSets' onto the end of `set1'.\nThe operation is destructive wrt `set1', but leaves all other sets intact.\nThe two mandatory parameters allow us to optimize the common binary case by\nnot relying on the somewhat less efficient variable arguments mechanism.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Set::concatenate))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQUAL? BOOLEAN) ((X SET) (Y OBJECT)) :DOCUMENTATION \"Return TRUE iff `x' and `y' are SET's with equivalent members.\nUses `equal?' to test equality of elements.  This is more general than\n`equivalent-sets?', since that only uses an `eql?' test.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Set::objectEqualP))), NULL);
    defineMethodObject("(DEFMETHOD (EQUAL-HASH-CODE INTEGER) ((SELF SET)) :DOCUMENTATION \"Return an `equal?' hash code for `self'.  Note that this\nis O(N) in the number of elements of `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Set::equalHashCode))), NULL);
    defineFunctionObject("SET", "(DEFUN (SET SET) (|&REST| (VALUES OBJECT)) :DOCUMENTATION \"Return a set containing `values', in order.\" :PUBLIC? TRUE)", ((cpp_function_code)(&set)), NULL);
    defineMethodObject("(DEFMETHOD PRINT-VECTOR ((SELF VECTOR) (STREAM NATIVE-OUTPUT-STREAM)))", wrapMethodCode(((cpp_method_code)(&Vector::printVector))), NULL);
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF VECTOR)) :DOCUMENTATION \"Return `true' if `self' has length 0.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Vector::emptyP))), NULL);
    defineMethodObject("(DEFMETHOD (NON-EMPTY? BOOLEAN) ((SELF VECTOR)) :DOCUMENTATION \"Return `true' if `self' has length > 0.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Vector::nonEmptyP))), NULL);
    defineMethodObject("(DEFMETHOD (FIRST (LIKE (ANY-VALUE SELF))) ((SELF VECTOR)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (NTH SELF 0)))", wrapMethodCode(((cpp_method_code)(&Vector::first))), NULL);
    defineMethodObject("(DEFMETHOD (SECOND (LIKE (ANY-VALUE SELF))) ((SELF VECTOR)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (NTH SELF 1)))", wrapMethodCode(((cpp_method_code)(&Vector::second))), NULL);
    defineMethodObject("(DEFMETHOD (THIRD (LIKE (ANY-VALUE SELF))) ((SELF VECTOR)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (NTH SELF 2)))", wrapMethodCode(((cpp_method_code)(&Vector::third))), NULL);
    defineMethodObject("(DEFMETHOD (FOURTH (LIKE (ANY-VALUE SELF))) ((SELF VECTOR)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (NTH SELF 3)))", wrapMethodCode(((cpp_method_code)(&Vector::fourth))), NULL);
    defineMethodObject("(DEFMETHOD (FIFTH (LIKE (ANY-VALUE SELF))) ((SELF VECTOR)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (NTH SELF 4)))", wrapMethodCode(((cpp_method_code)(&Vector::fifth))), NULL);
    defineMethodObject("(DEFMETHOD (NTH (LIKE (ANY-VALUE SELF))) ((SELF VECTOR) (POSITION INTEGER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (NTH (THE-ARRAY SELF) POSITION)))", wrapMethodCode(((cpp_method_code)(&Vector::nth))), NULL);
    defineMethodObject("(DEFMETHOD (LAST (LIKE (ANY-VALUE SELF))) ((SELF VECTOR)) :PUBLIC? TRUE :DOCUMENTATION \"Return the last item in the vector `self'.\")", wrapMethodCode(((cpp_method_code)(&Vector::last))), NULL);
    defineMethodObject("(DEFMETHOD (FIRST-SETTER (LIKE (ANY-VALUE SELF))) ((SELF VECTOR) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (SETF (NTH SELF 0) VALUE)))", wrapMethodCode(((cpp_method_code)(&Vector::firstSetter))), NULL);
    defineMethodObject("(DEFMETHOD (SECOND-SETTER (LIKE (ANY-VALUE SELF))) ((SELF VECTOR) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (SETF (NTH SELF 1) VALUE)))", wrapMethodCode(((cpp_method_code)(&Vector::secondSetter))), NULL);
    defineMethodObject("(DEFMETHOD (THIRD-SETTER (LIKE (ANY-VALUE SELF))) ((SELF VECTOR) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (SETF (NTH SELF 2) VALUE)))", wrapMethodCode(((cpp_method_code)(&Vector::thirdSetter))), NULL);
    defineMethodObject("(DEFMETHOD (FOURTH-SETTER (LIKE (ANY-VALUE SELF))) ((SELF VECTOR) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (SETF (NTH SELF 3) VALUE)))", wrapMethodCode(((cpp_method_code)(&Vector::fourthSetter))), NULL);
    defineMethodObject("(DEFMETHOD (FIFTH-SETTER (LIKE (ANY-VALUE SELF))) ((SELF VECTOR) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (SETF (NTH SELF 4) VALUE)))", wrapMethodCode(((cpp_method_code)(&Vector::fifthSetter))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-SETTER (LIKE (ANY-VALUE SELF))) ((SELF VECTOR) (VALUE (LIKE (ANY-VALUE SELF))) (POSITION INTEGER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (SETF (NTH (THE-ARRAY SELF) POSITION) VALUE)))", wrapMethodCode(((cpp_method_code)(&Vector::nthSetter))), NULL);
    defineMethodObject("(DEFMETHOD (LAST-SETTER (LIKE (ANY-VALUE SELF))) ((SELF VECTOR) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Vector::lastSetter))), NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF VECTOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Vector::length))), NULL);
    defineMethodObject("(DEFMETHOD (MEMBER? BOOLEAN) ((SELF VECTOR) (OBJECT OBJECT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Vector::memberP))), NULL);
    defineMethodObject("(DEFMETHOD (POSITION INTEGER) ((SELF VECTOR) (OBJECT OBJECT) (START INTEGER)) :DOCUMENTATION \"Return the position of `object' within the vector\n`self' (counting from zero); or return `null' if `object' does not occur within \n`self' (uses an `eql?' test).  If `start' was supplied as non-`null', only \nconsider the portion starting at `start', however, the returned position \nwill always be relative to the entire vector.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Vector::position))), NULL);
    defineMethodObject("(DEFMETHOD (LAST-POSITION INTEGER) ((SELF VECTOR) (OBJECT OBJECT) (END INTEGER)) :DOCUMENTATION \"Return the position of `object' within the vector\n`self' (counting from zero); or return `null' if `object' does not occur within \n`self' (uses an `eql?' test).  If `end' was supplied as non-`null', only \nconsider the portion ending at index `end', however, the returned position \nwill always be relative to the entire vector.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Vector::lastPosition))), NULL);
    defineMethodObject("(DEFMETHOD INSERT-AT ((SELF VECTOR) (OFFSET INTEGER) (VALUE (LIKE (ANY-VALUE SELF)))))", wrapMethodCode(((cpp_method_code)(&Vector::insertAt))), NULL);
    defineMethodObject("(DEFMETHOD (COPY (VECTOR OF (LIKE (ANY-VALUE SELF)))) ((SELF VECTOR)) :DOCUMENTATION \"Return a copy of the vector `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Vector::copy))), NULL);
    defineMethodObject("(DEFMETHOD CLEAR ((SELF VECTOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Vector::clear))), NULL);
    defineFunctionObject("VECTOR", "(DEFUN (VECTOR VECTOR) (|&REST| (VALUES OBJECT)) :DOCUMENTATION \"Return a vector containing `values', in order.\" :PUBLIC? TRUE)", ((cpp_function_code)(&stella::vector)), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQUAL? BOOLEAN) ((X VECTOR) (Y OBJECT)) :DOCUMENTATION \"Return TRUE iff the vectors `x' and `y' are structurally\nequivalent.  Uses `equal?' to test equality of elements.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Vector::objectEqualP))), NULL);
    defineMethodObject("(DEFMETHOD (EQUAL-HASH-CODE INTEGER) ((SELF VECTOR)) :DOCUMENTATION \"Return an `equal?' hash code for `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Vector::equalHashCode))), NULL);
    defineMethodObject("(DEFMETHOD INSERT-AT ((SELF EXTENSIBLE-VECTOR) (OFFSET INTEGER) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ExtensibleVector::insertAt))), NULL);
    defineMethodObject("(DEFMETHOD INSERT-AT ((SELF EXTENSIBLE-SYMBOL-ARRAY) (OFFSET INTEGER) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ExtensibleSymbolArray::insertAt))), NULL);
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF VECTOR-SEQUENCE)) :DOCUMENTATION \"Return `true' if `self' has length 0.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (EQL? (LENGTH SELF) 0)))", wrapMethodCode(((cpp_method_code)(&VectorSequence::emptyP))), NULL);
    defineMethodObject("(DEFMETHOD (NON-EMPTY? BOOLEAN) ((SELF VECTOR-SEQUENCE)) :DOCUMENTATION \"Return `true' if `self' has length > 0.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (> (LENGTH SELF) 0)))", wrapMethodCode(((cpp_method_code)(&VectorSequence::nonEmptyP))), NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF VECTOR-SEQUENCE)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (SEQUENCE-LENGTH SELF)))", wrapMethodCode(((cpp_method_code)(&VectorSequence::length))), NULL);
    defineMethodObject("(DEFMETHOD (LAST (LIKE (ANY-VALUE SELF))) ((SELF VECTOR-SEQUENCE)) :PUBLIC? TRUE :DOCUMENTATION \"Return the last item in the vector `self'.\")", wrapMethodCode(((cpp_method_code)(&VectorSequence::last))), NULL);
    defineMethodObject("(DEFMETHOD (LAST-SETTER (LIKE (ANY-VALUE SELF))) ((SELF VECTOR-SEQUENCE) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&VectorSequence::lastSetter))), NULL);
    defineMethodObject("(DEFMETHOD INSERT ((SELF VECTOR-SEQUENCE) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Append `value' to the END of the sequence `self'.  \nResize the array if necessary.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&VectorSequence::insert))), NULL);
    defineMethodObject("(DEFMETHOD INSERT ((SELF CUSTOM-VECTOR-SEQUENCE) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Append `value' to the END of the sequence `self'.  \nResize the array if necessary.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&CustomVectorSequence::insert))), NULL);
    defineMethodObject("(DEFMETHOD (REMOVE VECTOR-SEQUENCE) ((SELF VECTOR-SEQUENCE) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Remove `value' from the sequence `self', and left shift\nthe values after it to close the gap.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&VectorSequence::remove))), NULL);
    defineMethodObject("(DEFMETHOD (REVERSE (LIKE SELF)) ((SELF VECTOR-SEQUENCE)) :DOCUMENTATION \"Reverse the order of elements in the active portion of `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&VectorSequence::reverse))), NULL);
    defineFunctionObject("COPY-VECTOR-SEQUENCE", "(DEFUN COPY-VECTOR-SEQUENCE ((SOURCE VECTOR-SEQUENCE) (COPY VECTOR-SEQUENCE)))", ((cpp_function_code)(&copyVectorSequence)), NULL);
    defineMethodObject("(DEFMETHOD (COPY (VECTOR-SEQUENCE OF (LIKE (ANY-VALUE SELF)))) ((SELF VECTOR-SEQUENCE)) :DOCUMENTATION \"Return a copy of the vector sequence `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&VectorSequence::copy))), NULL);
    defineMethodObject("(DEFMETHOD (COPY (CUSTOM-VECTOR-SEQUENCE OF (LIKE (ANY-VALUE SELF)))) ((SELF CUSTOM-VECTOR-SEQUENCE)) :DOCUMENTATION \"Return a copy of the vector sequence `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&CustomVectorSequence::copy))), NULL);
    defineMethodObject("(DEFMETHOD CLEAR ((SELF VECTOR-SEQUENCE)) :DOCUMENTATION \"Clear `self' by setting its active length to zero.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&VectorSequence::clear))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQUAL? BOOLEAN) ((X VECTOR-SEQUENCE) (Y OBJECT)) :DOCUMENTATION \"Return TRUE iff the sequences `x' and `y' are structurally\nequivalent.  Uses `equal?' to test equality of elements.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&VectorSequence::objectEqualP))), NULL);
  }
}

void helpStartupCollections4() {
  {
    defineMethodObject("(DEFMETHOD (ALLOCATE-ITERATOR (ITERATOR OF (LIKE (ANY-VALUE SELF)))) ((SELF VECTOR)))", wrapMethodCode(((cpp_method_code)(&Vector::allocateIterator))), NULL);
    defineFunctionObject("VECTOR-NEXT?", "(DEFUN (VECTOR-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&vectorNextP)), NULL);
    defineMethodObject("(DEFMETHOD (BUT-LAST (ITERATOR OF (LIKE (ANY-VALUE SELF)))) ((SELF VECTOR)) :DOCUMENTATION \"Generate all but the last element of the vector `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Vector::butLast))), NULL);
    defineMethodObject("(DEFMETHOD (SORT (VECTOR OF (LIKE (ANY-VALUE SELF)))) ((SELF VECTOR) (PREDICATE FUNCTION-CODE)) :PUBLIC? TRUE :DOCUMENTATION \"Perform a destructive sort of `self' according to\n`predicate', and return the result.  If `predicate' has a '<' semantics, the\nresult will be in ascending order.  If `predicate' is `null', a\nsuitable '<' predicate is chosen depending on the first element of `self',\nand it is assumed that all elements of `self' have the same type (supported\nelement types are GENERALIZED-SYMBOL, STRING, INTEGER, and FLOAT).\")", wrapMethodCode(((cpp_method_code)(&Vector::sort))), NULL);
    defineMethodObject("(DEFMETHOD (SORT-TUPLES (VECTOR OF (LIKE (ANY-VALUE SELF)))) ((SELF VECTOR) (N INTEGER) (PREDICATE FUNCTION-CODE)) :PUBLIC? TRUE :DOCUMENTATION \"Just like `sort' but assumes each element of `self' is a tuple (a cons)\nwhose `n'-th element (0-based) will be used for comparison.\")", wrapMethodCode(((cpp_method_code)(&Vector::sortTuples))), NULL);
    defineMethodObject("(DEFMETHOD (SORT-OBJECTS (VECTOR OF (LIKE (ANY-VALUE SELF)))) ((SELF VECTOR) (SLOT STORAGE-SLOT) (PREDICATE FUNCTION-CODE)) :DOCUMENTATION \"Just like `sort' but assumes each element of `self' has a `slot'\nwhose value will be used for comparison.  Elements must be descendants of\nSTANDARD OBJECT.  Note that while this will work with literal-valued slots,\nit will cause value wrapping everytime `slot' is read.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Vector::sortObjects))), NULL);
    defineFunctionObject("HEAP-SORT-NATIVE-VECTOR", "(DEFUN HEAP-SORT-NATIVE-VECTOR ((VECTOR NATIVE-VECTOR) (SIZE INTEGER) (PREDICATE FUNCTION-CODE)))", ((cpp_function_code)(&heapSortNativeVector)), NULL);
    defineFunctionObject("HEAP-SORT-HEAPIFY", "(DEFUN HEAP-SORT-HEAPIFY ((VECTOR NATIVE-VECTOR) (SIZE INTEGER) (PREDICATE FUNCTION-CODE)))", ((cpp_function_code)(&heapSortHeapify)), NULL);
    defineFunctionObject("HEAP-SORT-SIFT-DOWN", "(DEFUN HEAP-SORT-SIFT-DOWN ((VECTOR NATIVE-VECTOR) (START INTEGER) (END INTEGER) (PREDICATE FUNCTION-CODE)))", ((cpp_function_code)(&heapSortSiftDown)), NULL);
    defineFunctionObject("QUICK-SORT-PICK-SPLIT-ELEMENT", "(DEFUN (QUICK-SORT-PICK-SPLIT-ELEMENT OBJECT) ((VECTOR NATIVE-VECTOR) (START INTEGER) (END INTEGER) (PREDICATE FUNCTION-CODE)))", ((cpp_function_code)(&quickSortPickSplitElement)), NULL);
    defineFunctionObject("QUICK-SORT-NATIVE-VECTOR", "(DEFUN QUICK-SORT-NATIVE-VECTOR ((VECTOR NATIVE-VECTOR) (START INTEGER) (END INTEGER) (PREDICATE FUNCTION-CODE)))", ((cpp_function_code)(&quickSortNativeVector)), NULL);
    defineMethodObject("(DEFMETHOD INITIALIZE-HEAP ((SELF HEAP)))", wrapMethodCode(((cpp_method_code)(&Heap::initializeHeap))), NULL);
    defineMethodObject("(DEFMETHOD (COPY (HEAP OF (LIKE (ANY-VALUE SELF)))) ((SELF HEAP)) :DOCUMENTATION \"Return a copy of the heap `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Heap::copy))), NULL);
    defineMethodObject("(DEFMETHOD CLEAR ((SELF HEAP)) :DOCUMENTATION \"Clear `self' by setting its active length to zero.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Heap::clear))), NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF HEAP)) :DOCUMENTATION \"Return the length of the currently filled portion of `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Heap::length))), NULL);
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF HEAP)) :DOCUMENTATION \"Return TRUE if `self' is empty.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Heap::emptyP))), NULL);
    defineMethodObject("(DEFMETHOD (LAST (LIKE (ANY-VALUE SELF))) ((SELF HEAP)) :DOCUMENTATION \"Return the last item in the heap `self' which will be the\nlargest or best item if `self' is a sorted min-heap with a '<' predicate.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Heap::last))), NULL);
    defineMethodObject("(DEFMETHOD (HEAP-ROOT (LIKE (ANY-VALUE SELF))) ((SELF HEAP)) :DOCUMENTATION \"Return the root of `self' (NULL if `self' is empty).\nThe root contains the minimum element of a min-heap with '<' predicate.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Heap::heapRoot))), NULL);
    defineMethodObject("(DEFMETHOD (FAST-HEAP-ROOT (LIKE (ANY-VALUE SELF))) ((SELF HEAP)) :DOCUMENTATION \"Return the root of `self' which is assumed to be non-empty.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (NTH SELF 0)))", wrapMethodCode(((cpp_method_code)(&Heap::fastHeapRoot))), NULL);
    defineFunctionObject("HEAP-SIFT-UP", "(DEFUN HEAP-SIFT-UP ((HEAP NATIVE-VECTOR) (START INTEGER) (END INTEGER) (VALUE (LIKE (ANY-VALUE SELF))) (PREDICATE FUNCTION-CODE)))", ((cpp_function_code)(&heapSiftUp)), NULL);
    defineFunctionObject("HEAP-SIFT-DOWN", "(DEFUN HEAP-SIFT-DOWN ((HEAP NATIVE-VECTOR) (START INTEGER) (END INTEGER) (VALUE (LIKE (ANY-VALUE SELF))) (PREDICATE FUNCTION-CODE)))", ((cpp_function_code)(&heapSiftDown)), NULL);
    defineMethodObject("(DEFMETHOD INSERT ((SELF HEAP) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Insert `value' into `self' and restore the heap property.\nSignal an error if there is no more room in `self'.  Maintains `self' as\na Min-heap if `self's `predicate' has `<' semantics; otherwise as a Max-heap.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Heap::insert))), NULL);
    defineMethodObject("(DEFMETHOD REPLACE-HEAP-ROOT ((SELF HEAP) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Replace the current root of `self' with `value' and restore\nthe heap property.  Signal an error if `self' is empty.  Maintains `self' as\na Min-heap if `self's `predicate' has `<' semantics; otherwise as a Max-heap.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Heap::replaceHeapRoot))), NULL);
    defineMethodObject("(DEFMETHOD INSERT-IF-BETTER ((SELF HEAP) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Insert `value' into `self' and restore the heap property.\nIf `self' has available room, simply insert `value'.  If the heap is full, only\ninsert `value' if it is better than the current root (i.e., if `value' is\ngreater than the minimum of `self' for the case of a min-heap where `self's\n`predicate' has `<' semantics).  In that case, replace the root of `self'\nand restore the heap property.  This is useful to build and maintain a\nheap with some top-N elements (relative to `predicate') where the root (or\nminimum) of `self' is the currently weakest element at the end of the list.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Heap::insertIfBetter))), NULL);
    defineMethodObject("(DEFMETHOD HEAPIFY ((SELF HEAP)) :DOCUMENTATION \"Restore the heap property of `self' according to its\n`predicate'.  Normally, this is not needed, since insert operations\npreserve the heap property.  However, this can be useful after bulk\ninsertion of values or if `predicate' has been changed.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Heap::heapify))), NULL);
    defineMethodObject("(DEFMETHOD (SORT (HEAP OF (LIKE (ANY-VALUE SELF)))) ((SELF HEAP) (PREDICATE FUNCTION-CODE)) :DOCUMENTATION \"Sort the heap `self' according to `predicate' (in\nascending order if `predicate' has `<' semantics).  If `predicate'\nis NULL simply use `self's internal predicate (the normal case).\nIf it is different from `self's internal predicate, heapify `self' first\naccording to the new predicate, store the new predicate in `self' and\nthen sort the heap.  Note that a sorted array automatically satisfies\nthe heap property.  This is slightly different than a regular heap\nsort due to the way HEAP's are maintained; however, the complexity is\nthe same.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Heap::sort))), NULL);
    defineFunctionObject("INITIALIZE-STELLA-HASH-TABLE", "(DEFUN INITIALIZE-STELLA-HASH-TABLE ((SELF STELLA-HASH-TABLE)))", ((cpp_function_code)(&initializeStellaHashTable)), NULL);
    defineMethodObject("(DEFMETHOD INITIALIZE-HASH-TABLE ((SELF STELLA-HASH-TABLE)) :DOCUMENTATION \"Initialize the STELLA hash table `self'.  This is a\nno-op and primarily exists to shadow the standard initializer inherited\nfrom ABSTRACT-HASH-TABLE.  STELLA hash tables are initialized at the\nfirst insertion operation.\")", wrapMethodCode(((cpp_method_code)(&StellaHashTable::initializeHashTable))), NULL);
    defineFunctionObject("REHASH-STELLA-HASH-TABLE", "(DEFUN REHASH-STELLA-HASH-TABLE ((SELF STELLA-HASH-TABLE) (NEWSIZE INTEGER)))", ((cpp_function_code)(&rehashStellaHashTable)), NULL);
    defineFunctionObject("STELLA-HASH-TABLE-INSERT-AT", "(DEFUN STELLA-HASH-TABLE-INSERT-AT ((SELF STELLA-HASH-TABLE) (KEY OBJECT) (VALUE OBJECT)))", ((cpp_function_code)(&stellaHashTableInsertAt)), NULL);
    defineFunctionObject("STELLA-HASH-TABLE-REMOVE-AT", "(DEFUN STELLA-HASH-TABLE-REMOVE-AT ((SELF STELLA-HASH-TABLE) (KEY OBJECT)))", ((cpp_function_code)(&stellaHashTableRemoveAt)), NULL);
    defineFunctionObject("STELLA-HASH-TABLE-LOOKUP", "(DEFUN (STELLA-HASH-TABLE-LOOKUP (LIKE (ANY-VALUE SELF))) ((SELF STELLA-HASH-TABLE) (KEY OBJECT)))", ((cpp_function_code)(&stellaHashTableLookup)), NULL);
    defineFunctionObject("STELLA-STRING-HASH-TABLE-LOOKUP", "(DEFUN (STELLA-STRING-HASH-TABLE-LOOKUP (LIKE (ANY-VALUE SELF))) ((SELF STELLA-HASH-TABLE) (KEY STRING)))", ((cpp_function_code)(&stellaStringHashTableLookup)), NULL);
    defineMethodObject("(DEFMETHOD (LOOKUP (LIKE (ANY-VALUE SELF))) ((SELF STELLA-HASH-TABLE) (KEY (LIKE (ANY-KEY SELF)))) :DOCUMENTATION \"Lookup the entry identified by `key' in `self' and\nreturn its value, or NULL if no such entry exists.    Uses an `eql?'\ntest by default or `equal?' if `equal-test?' of `self' is TRUE.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StellaHashTable::lookup))), NULL);
    defineMethodObject("(DEFMETHOD INSERT-AT ((SELF STELLA-HASH-TABLE) (KEY (LIKE (ANY-KEY SELF))) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Set the value of the entry identified by `key' in `self'\nto `value' or add a new entry if no entry with `key' exists yet.  Uses an\n`eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StellaHashTable::insertAt))), NULL);
    defineMethodObject("(DEFMETHOD REMOVE-AT ((SELF STELLA-HASH-TABLE) (KEY (LIKE (ANY-KEY SELF)))) :DOCUMENTATION \"Remove the entry identified by `key' from `self'.  Uses an\n`eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StellaHashTable::removeAt))), NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF STELLA-HASH-TABLE)) :DOCUMENTATION \"Return the number of entries in `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StellaHashTable::length))), NULL);
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF STELLA-HASH-TABLE)) :DOCUMENTATION \"Return TRUE if `self' has zero entries.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StellaHashTable::emptyP))), NULL);
    defineMethodObject("(DEFMETHOD (NON-EMPTY? BOOLEAN) ((SELF STELLA-HASH-TABLE)) :DOCUMENTATION \"Return TRUE if `self' has at least 1 entry.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StellaHashTable::nonEmptyP))), NULL);
    defineMethodObject("(DEFMETHOD (COPY (LIKE SELF)) ((SELF STELLA-HASH-TABLE)) :DOCUMENTATION \"Return a copy of the hash table `self'.  The bucket table\nand buckets are freshly allocated, however, the keys and values of entries\nare not copied themselves (similar to what we do for lists, etc.).\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StellaHashTable::copy))), NULL);
    defineMethodObject("(DEFMETHOD CLEAR ((SELF STELLA-HASH-TABLE)) :DOCUMENTATION \"Remove all entries from `self'.  This will result in a\nre-initialization of the table upon the first insertion into `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StellaHashTable::clear))), NULL);
    defineMethodObject("(DEFMETHOD (CONSIFY (CONS OF CONS)) ((SELF STELLA-HASH-TABLE)) :DOCUMENTATION \"Collect all entries of `self' into a cons list of\n`(<key> <value>)' pairs and return the result.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StellaHashTable::consify))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQUAL? BOOLEAN) ((X STELLA-HASH-TABLE) (Y OBJECT)) :DOCUMENTATION \"Return TRUE if `x' and `y' represent the same set of key/value pairs.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StellaHashTable::objectEqualP))), NULL);
    defineMethodObject("(DEFMETHOD (EQUAL-HASH-CODE INTEGER) ((SELF STELLA-HASH-TABLE)) :DOCUMENTATION \"Return an `equal?' hash code for `self'.  Note that this\nis O(N) in the number of entries of `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StellaHashTable::equalHashCode))), NULL);
    defineMethodObject("(DEFMETHOD (ALLOCATE-ITERATOR (STELLA-HASH-TABLE-ITERATOR OF (LIKE (ANY-KEY SELF)) (LIKE (ANY-VALUE SELF)))) ((SELF STELLA-HASH-TABLE)) :DOCUMENTATION \"Allocate an iterator for `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StellaHashTable::allocateIterator))), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF STELLA-HASH-TABLE-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&StellaHashTableIterator::nextP))), NULL);
    defineMethodObject("(DEFMETHOD (VALUE-SETTER (LIKE (ANY-VALUE SELF))) ((SELF STELLA-HASH-TABLE-ITERATOR) (VALUE (LIKE (ANY-VALUE SELF)))))", wrapMethodCode(((cpp_method_code)(&StellaHashTableIterator::valueSetter))), NULL);
    defineMethodObject("(DEFMETHOD (KEY-SETTER (LIKE (ANY-KEY SELF))) ((SELF STELLA-HASH-TABLE-ITERATOR) (KEY (LIKE (ANY-KEY SELF)))))", wrapMethodCode(((cpp_method_code)(&StellaHashTableIterator::keySetter))), NULL);
    defineMethodObject("(DEFMETHOD (LOOKUP (LIKE (ANY-VALUE SELF))) ((SELF KEY-VALUE-MAP) (KEY (LIKE (ANY-KEY SELF)))) :DOCUMENTATION \"Lookup the entry identified by `key' in `self' and\nreturn its value, or NULL if no such entry exists.    Uses an `eql?'\ntest by default or `equal?' if `equal-test?' of `self' is TRUE.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueMap::lookup))), NULL);
    defineMethodObject("(DEFMETHOD INSERT-AT ((SELF KEY-VALUE-MAP) (KEY (LIKE (ANY-KEY SELF))) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Set the value of the entry identified by `key' in `self'\nto `value' or add a new entry if no entry with `key' exists yet.  Uses an\n`eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueMap::insertAt))), NULL);
    defineMethodObject("(DEFMETHOD REMOVE-AT ((SELF KEY-VALUE-MAP) (KEY (LIKE (ANY-KEY SELF)))) :DOCUMENTATION \"Remove the entry identified by `key' from `self'.  Uses an\n`eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueMap::removeAt))), NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF KEY-VALUE-MAP)) :DOCUMENTATION \"Return the number of entries in `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueMap::length))), NULL);
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF KEY-VALUE-MAP)) :DOCUMENTATION \"Return TRUE if `self' has zero entries.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueMap::emptyP))), NULL);
    defineMethodObject("(DEFMETHOD (NON-EMPTY? BOOLEAN) ((SELF KEY-VALUE-MAP)) :DOCUMENTATION \"Return TRUE if `self' has at least 1 entry.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueMap::nonEmptyP))), NULL);
    defineMethodObject("(DEFMETHOD (COPY (LIKE SELF)) ((SELF KEY-VALUE-MAP)) :DOCUMENTATION \"Return a copy of the map `self'.  All entries are freshly\nallocated, however, the keys and values of entries are not copied themselves\n (similar to what we do for lists, etc.).\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueMap::copy))), NULL);
    defineMethodObject("(DEFMETHOD CLEAR ((SELF KEY-VALUE-MAP)) :DOCUMENTATION \"Reset `self' to have zero entries.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueMap::clear))), NULL);
    defineMethodObject("(DEFMETHOD (ALLOCATE-ITERATOR (DICTIONARY-ITERATOR OF (LIKE (ANY-KEY SELF)) (LIKE (ANY-VALUE SELF)))) ((SELF KEY-VALUE-MAP)) :DOCUMENTATION \"Allocate an iterator for `self'.  The only modifying\noperations allowed during iteration are removal of the current element or\nchanging its value.  All other removal or insertion operations might lead\nto corruption or undefined results.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueMap::allocateIterator))), NULL);
    defineMethodObject("(DEFMETHOD (CONSIFY CONS) ((SELF KEY-VALUE-MAP)) :DOCUMENTATION \"Collect all entries of `self' into a cons list of\n`(<key> <value>)' pairs and return the result.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueMap::consify))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQUAL? BOOLEAN) ((X KEY-VALUE-MAP) (Y OBJECT)) :DOCUMENTATION \"Return TRUE if `x' and `y' represent the same set of key/value pairs.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueMap::objectEqualP))), NULL);
    defineMethodObject("(DEFMETHOD (EQUAL-HASH-CODE INTEGER) ((SELF KEY-VALUE-MAP)) :DOCUMENTATION \"Return an `equal?' hash code for `self'.  Note that this\nis O(N) in the number of entries of `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueMap::equalHashCode))), NULL);
  }
}

void helpStartupCollections5() {
  {
    defineFunctionObject("HASH-SET", "(DEFUN (HASH-SET HASH-SET) (|&REST| (VALUES OBJECT)) :DOCUMENTATION \"Return an `eql?' HASH-SET containing `values'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&hashSet)), NULL);
    defineFunctionObject("COERCE-TO-HASH-SET", "(DEFUN (COERCE-TO-HASH-SET HASH-SET) ((SELF OBJECT) (EQUALTEST? BOOLEAN)) :DOCUMENTATION \"Coerce the collection `self' into a HASH-SET.  Use an\nequal test if `equalTest?' is TRUE (`equalTest?' will be ignored if `self'\nalready is a HASH-SET).\" :PUBLIC? TRUE)", ((cpp_function_code)(&coerceToHashSet)), NULL);
    defineMethodObject("(DEFMETHOD (MEMBER? BOOLEAN) ((SELF HASH-SET) (OBJECT OBJECT)) :DOCUMENTATION \"Return TRUE iff `object' is a member of the set `self'.\nUses an `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashSet::memberP))), NULL);
    defineMethodObject("(DEFMETHOD INSERT ((SELF HASH-SET) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Add `value' to the set `self' unless it is already a member.\nUses an `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashSet::insert))), NULL);
    defineMethodObject("(DEFMETHOD (REMOVE (LIKE SELF)) ((SELF HASH-SET) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Destructively remove `value' from the set `self' if it is a member and\nreturn `self'.  Uses an `eql?' test by default or `equal?' if `equal-test?' of\n`self' is TRUE.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashSet::remove))), NULL);
    defineMethodObject("(DEFMETHOD (REMOVE-IF (LIKE SELF)) ((SELF HASH-SET) (TEST? FUNCTION-CODE)) :DOCUMENTATION \"Destructively remove all elements of the set `self' for which\n'test?' evaluates to TRUE.  `test?' takes a single argument of type OBJECT and\nreturns TRUE or FALSE.  Returns `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashSet::removeIf))), NULL);
    defineMethodObject("(DEFMETHOD (POP (LIKE (ANY-VALUE SELF))) ((SELF HASH-SET)) :DOCUMENTATION \"Remove and return an arbitrary element of the set `self'.\nReturn NULL if the set is empty.  Performance note: for large sets implemented\nvia hash tables it takes O(N) to empty out the set with repeated calls to `pop',\nsince the emptier the table gets, the longer it takes to find an element.\nTherefore, it is usually better to use iteration with embedded removals for\nsuch cases.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashSet::pop))), NULL);
    defineMethodObject("(DEFMETHOD (SUBSTITUTE (LIKE SELF)) ((SELF HASH-SET) (NEW OBJECT) (OLD OBJECT)) :DOCUMENTATION \"Destructively replace `old' with `new' in the set `self'\nunless `new' is already a member.  Uses an `eql?' test by default or `equal?'\nif `equal-test?' of `self' is TRUE.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashSet::substitute))), NULL);
    defineMethodObject("(DEFMETHOD (COPY (LIKE SELF)) ((SELF HASH-SET)) :DOCUMENTATION \"Return a copy of the set `self'.  All entries are freshly\nallocated, however, the values are not copied themselves (similar to what we\ndo for lists, etc.).\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashSet::copy))), NULL);
    defineMethodObject("(DEFMETHOD (CONSIFY (CONS OF (LIKE (ANY-VALUE SELF)))) ((SELF HASH-SET)) :DOCUMENTATION \"Collect all entries of `self' into a cons list and return the result.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashSet::consify))), NULL);
    defineMethodObject("(DEFMETHOD (SUBSET? BOOLEAN) ((SELF HASH-SET) (OTHERSET HASH-SET)) :DOCUMENTATION \"Return true if every element of `self' also occurs in `otherSet'.\nUses an `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashSet::subsetP))), NULL);
    defineMethodObject("(DEFMETHOD (EQUIVALENT-SETS? BOOLEAN) ((SELF HASH-SET) (OTHERSET HASH-SET)) :DOCUMENTATION \"Return true if every element of `self' occurs in `otherSet' and vice versa.\nUses an `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashSet::equivalentSetsP))), NULL);
    defineMethodObject("(DEFMETHOD (INTERSECTION HASH-SET) ((SELF HASH-SET) (OTHERSET HASH-SET)) :DOCUMENTATION \"Return the set intersection of `self' and `otherSet' as a new set.\nUses an `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashSet::intersection))), NULL);
    defineMethodObject("(DEFMETHOD (UNION HASH-SET) ((SELF HASH-SET) (OTHERSET HASH-SET)) :DOCUMENTATION \"Return the set union of `self' and `otherSet' as a new set.\nUses an `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashSet::unioN))), NULL);
    defineMethodObject("(DEFMETHOD (DIFFERENCE HASH-SET) ((SELF HASH-SET) (OTHERSET HASH-SET)) :DOCUMENTATION \"Return the set difference of `self' and `otherSet' as a new set (i.e.,\nall elements that are in `self' but not in `otherSet').  Uses an `eql?' test\nby default or `equal?' if `equal-test?' of `self' is TRUE.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashSet::difference))), NULL);
    defineMethodObject("(DEFMETHOD (SUBTRACT HASH-SET) ((SELF HASH-SET) (OTHERSET HASH-SET)) :DOCUMENTATION \"Return the set difference of `self' and `otherSet' by destructively\nremoving elements from `self' that also occur in `otherSet'.  Uses an `eql?'\ntest by default or `equal?' if `equal-test?' of `self' is TRUE.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashSet::subtract))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQUAL? BOOLEAN) ((X HASH-SET) (Y OBJECT)) :DOCUMENTATION \"Return TRUE iff sets `x' and `y' are HASH-SET's with equivalent members.\nUses an `eql?' test by default or `equal?' if `equal-test?' of `self' is TRUE.\nThis is equivalent to calling `equivalent-sets?'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashSet::objectEqualP))), NULL);
    defineMethodObject("(DEFMETHOD (EQUAL-HASH-CODE INTEGER) ((SELF HASH-SET)) :DOCUMENTATION \"Return an `equal?' hash code for `self'.  Note that this\nis O(N) in the number of elements of `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&HashSet::equalHashCode))), NULL);
    defineMethodObject("(DEFMETHOD INITIALIZE-DIMENSIONAL-ARRAY ((SELF DIMENSIONAL-ARRAY-MIXIN)) (SETF (THE-ARRAY SELF) (NEW (ARRAY () OF (LIKE (ANY-VALUE SELF))) :SIZE (LENGTH SELF))))", NULL, NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF DIMENSIONAL-ARRAY-MIXIN)) :DOCUMENTATION \"Return the total number of elements in `self'.\" :PUBLIC? TRUE (RETURN (DIM1 SELF)))", NULL, NULL);
    defineMethodObject("(DEFMETHOD INITIALIZE-ARRAY ((SELF DIMENSIONAL-ARRAY-MIXIN) (INITIALVALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Initialize the elements of `self' with `initialValue'.\" :PUBLIC? TRUE (LET ((ARRAY (THE-ARRAY SELF))) (FOREACH I IN (INTERVAL 0 (1- (LENGTH SELF))) DO (SETF (AREF ARRAY I) INITIALVALUE))))", NULL, NULL);
    defineMethodObject("(DEFMETHOD (1D-AREF (LIKE (ANY-VALUE SELF))) ((SELF DIMENSIONAL-ARRAY-MIXIN) (I INTEGER)) :DOCUMENTATION \"Return the element of `self' at position `[i]'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (AREF (THE-ARRAY SELF) I)))", NULL, NULL);
    defineMethodObject("(DEFMETHOD (1D-AREF-SETTER (LIKE (ANY-VALUE SELF))) ((SELF DIMENSIONAL-ARRAY-MIXIN) (VALUE (LIKE (ANY-VALUE SELF))) (I INTEGER)) :DOCUMENTATION \"Set the element of `self' at position `[i]' to `value'\nand return the result.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (SETF (AREF (THE-ARRAY SELF) I) VALUE)))", NULL, NULL);
    defineMethodObject("(DEFMETHOD (1D-AREF-ADDRESS INTEGER) ((SELF DIMENSIONAL-ARRAY-MIXIN) (I INTEGER)) :DOCUMENTATION \"Return the 1D address of the element at position `[i]'.\nThis is useful for fast element-wise iteration that doesn't need arithmetic.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN I))", NULL, NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF 2-DIMENSIONAL-ARRAY-MIXIN)) :DOCUMENTATION \"Return the total number of elements in `self'.\" :PUBLIC? TRUE (RETURN (* (DIM1 SELF) (DIM2 SELF))))", NULL, NULL);
    defineMethodObject("(DEFMETHOD (2D-AREF (LIKE (ANY-VALUE SELF))) ((SELF 2-DIMENSIONAL-ARRAY-MIXIN) (I INTEGER) (J INTEGER)) :DOCUMENTATION \"Return the element of `self' at position `[i, j]'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (AREF (THE-ARRAY SELF) (+ (* I (DIM2 SELF)) J))))", NULL, NULL);
    defineMethodObject("(DEFMETHOD (2D-AREF-SETTER (LIKE (ANY-VALUE SELF))) ((SELF 2-DIMENSIONAL-ARRAY-MIXIN) (VALUE (LIKE (ANY-VALUE SELF))) (I INTEGER) (J INTEGER)) :DOCUMENTATION \"Set the element of `self' at position `[i, j]' to `value'\nand return the result.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (SETF (AREF (THE-ARRAY SELF) (+ (* I (DIM2 SELF)) J)) VALUE)))", NULL, NULL);
    defineMethodObject("(DEFMETHOD (2D-AREF-ADDRESS INTEGER) ((SELF 2-DIMENSIONAL-ARRAY-MIXIN) (I INTEGER) (J INTEGER)) :DOCUMENTATION \"Return the 1D address of the element at position `[i, j]'.\nThis is useful for fast element-wise iteration that doesn't need arithmetic.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (+ (* I (DIM2 SELF)) J)))", NULL, NULL);
    defineMethodObject("(DEFMETHOD (THE-ARRAY-READER (ARRAY () OF (LIKE (ANY-VALUE SELF)))) ((SELF 1D-ARRAY)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&oneDArray::theArrayReader))), NULL);
    defineMethodObject("(DEFMETHOD (THE-ARRAY-READER (ARRAY () OF (LIKE (ANY-VALUE SELF)))) ((SELF 1D-FLOAT-ARRAY)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&oneDFloatArray::theArrayReader))), NULL);
    defineMethodObject("(DEFMETHOD (THE-ARRAY-READER (ARRAY () OF (LIKE (ANY-VALUE SELF)))) ((SELF 2D-ARRAY)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&twoDArray::theArrayReader))), NULL);
    defineMethodObject("(DEFMETHOD (THE-ARRAY-READER (ARRAY () OF (LIKE (ANY-VALUE SELF)))) ((SELF 2D-FLOAT-ARRAY)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&twoDFloatArray::theArrayReader))), NULL);
    defineMethodObject("(DEFMETHOD (RESIZE-BUFFER MUTABLE-STRING) ((SELF STRING-BUFFER) (SIZE INTEGER)) :DOCUMENTATION \"Change the size of `self' to `size'.  If `size' is smaller\nthan the current size of `self', it's buffer will be truncated.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&BufferedString::resizeBuffer))), NULL);
    defineMethodObject("(DEFMETHOD (ENSURE-FREE-SPACE MUTABLE-STRING) ((SELF STRING-BUFFER) (SIZE INTEGER)) :DOCUMENTATION \"Ensure `self' is big enough to accommodate an additional item of `size'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&BufferedString::ensureFreeSpace))), NULL);
    defineMethodObject("(DEFMETHOD (FREE-SPACE INTEGER) ((SELF STRING-BUFFER)) :DOCUMENTATION \"Return the amount of free space in `self'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (- (BUFFER-SIZE SELF) (FILL-POINTER SELF))))", wrapMethodCode(((cpp_method_code)(&BufferedString::freeSpace))), NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF STRING-BUFFER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (FILL-POINTER SELF)))", wrapMethodCode(((cpp_method_code)(&BufferedString::length))), NULL);
    defineMethodObject("(DEFMETHOD (LENGTH-SETTER INTEGER) ((SELF STRING-BUFFER) (NEWLENGTH INTEGER)) :DOCUMENTATION \"Reset the length of `self' to `newLength'.  Fill in NULL characters if `newLength' \nis greater than the current length.  This is the safe way to reset the fill pointer.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&BufferedString::lengthSetter))), NULL);
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF STRING-BUFFER)) :DOCUMENTATION \"Return `true' if `self' has length 0.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (EQL? (LENGTH SELF) 0)))", wrapMethodCode(((cpp_method_code)(&BufferedString::emptyP))), NULL);
    defineMethodObject("(DEFMETHOD (NON-EMPTY? BOOLEAN) ((SELF STRING-BUFFER)) :DOCUMENTATION \"Return `true' if `self' has length > 0.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (> (LENGTH SELF) 0)))", wrapMethodCode(((cpp_method_code)(&BufferedString::nonEmptyP))), NULL);
    defineMethodObject("(DEFMETHOD (NTH CHARACTER) ((SELF STRING-BUFFER) (POSITION INTEGER)) :DOCUMENTATION \"Return the character in `self' at `position'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (NTH (BUFFER SELF) POSITION)))", wrapMethodCode(((cpp_method_code)(&BufferedString::nth))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-SETTER CHARACTER) ((SELF STRING-BUFFER) (CH CHARACTER) (POSITION INTEGER)) :DOCUMENTATION \"Set the character in `self' at `position' to `ch'.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (SETF (NTH (BUFFER SELF) POSITION) CH)))", wrapMethodCode(((cpp_method_code)(&BufferedString::nthSetter))), NULL);
    defineMethodObject("(DEFMETHOD (LAST CHARACTER) ((SELF STRING-BUFFER)) :DOCUMENTATION \"Return the last character in `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&BufferedString::last))), NULL);
    defineMethodObject("(DEFMETHOD (LAST-SETTER CHARACTER) ((SELF STRING-BUFFER) (VALUE CHARACTER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&BufferedString::lastSetter))), NULL);
    defineMethodObject("(DEFMETHOD APPEND-STRING ((SELF STRING-BUFFER) (VALUE STRING)) :DOCUMENTATION \"Append `value' to the END of the string `self'.  \nResize the buffer if necessary.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&BufferedString::appendString))), NULL);
    defineMethodObject("(DEFMETHOD APPEND-CHARACTER ((SELF STRING-BUFFER) (CHAR CHARACTER)) :DOCUMENTATION \"Append `char' to the END of the string `self'.  \nResize the buffer if necessary.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&BufferedString::appendCharacter))), NULL);
    defineMethodObject("(DEFMETHOD (POP CHARACTER) ((SELF STRING-BUFFER)))", wrapMethodCode(((cpp_method_code)(&BufferedString::pop))), NULL);
    defineMethodObject("(DEFMETHOD (COPY STRING-BUFFER) ((SELF STRING-BUFFER)))", wrapMethodCode(((cpp_method_code)(&BufferedString::copy))), NULL);
    defineMethodObject("(DEFMETHOD CLEAR ((SELF STRING-BUFFER)) :DOCUMENTATION \"Clear `self' by setting its active length to zero.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&BufferedString::clear))), NULL);
    defineMethodObject("(DEFMETHOD (THE-STRING STRING) ((SELF STRING-BUFFER)) :DOCUMENTATION \"Return a substring of `string' beginning at position `start'\nand ending up to but not including position `end', counting from zero.  An\n`end' value of NULL stands for the rest of the string.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (SUBSEQUENCE (BUFFER SELF) 0 (FILL-POINTER SELF))))", wrapMethodCode(((cpp_method_code)(&BufferedString::theString))), NULL);
    defineMethodObject("(DEFMETHOD (SUBSEQUENCE STRING) ((SELF STRING-BUFFER) (START INTEGER) (END INTEGER)) :DOCUMENTATION \"Return a substring of `string' beginning at position `start'\nand ending up to but not including position `end', counting from zero.  An\n`end' value of NULL stands for the rest of the string.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (WHEN (NULL? END) (SETQ END (LENGTH SELF))) (RETURN (SUBSEQUENCE (BUFFER SELF) START END)))", wrapMethodCode(((cpp_method_code)(&BufferedString::subsequence))), NULL);
    defineFunctionObject("STARTUP-COLLECTIONS", "(DEFUN STARTUP-COLLECTIONS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupCollections)), NULL);
    { MethodSlot* function = lookupFunction(SYM_COLLECTIONS_STELLA_STARTUP_COLLECTIONS);

      setDynamicSlotValue(function->dynamicSlots, SYM_COLLECTIONS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupCollections"), NULL_STRING_WRAPPER);
    }
  }
}

void startupCollections() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupCollections1();
    }
    if (currentStartupTimePhaseP(4)) {
      oKEY_VALUE_MAP_CROSSOVER_POINTo = oREMOVE_DUPLICATES_CROSSOVER_POINTo;
    }
    if (currentStartupTimePhaseP(5)) {
      helpStartupCollections2();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupCollections3();
      helpStartupCollections4();
      helpStartupCollections5();
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      registerNativeName(SYM_COLLECTIONS_STELLA_VECTOR, KWD_COLLECTIONS_CPP, KWD_COLLECTIONS_FUNCTION);
      defineGlobalVariableObject("(DEFGLOBAL *USE-STELLA-HASH-TABLES?* BOOLEAN (VERBATIM :COMMON-LISP \"CL-USER::*use-stella-hash-tables?*\" :CPP \"\n#ifndef HAVE_SGI_HASH_MAPS\n  TRUE\n#else\n  FALSE\n#endif\n\" :OTHERWISE FALSE))", &oUSE_STELLA_HASH_TABLESpo);
      defineGlobalVariableObject("(DEFGLOBAL *STELLA-HASH-TABLE-AVG-BUCKET-LENGTH* FLOAT 1.0)", &oSTELLA_HASH_TABLE_AVG_BUCKET_LENGTHo);
      defineGlobalVariableObject("(DEFGLOBAL *KEY-VALUE-MAP-CROSSOVER-POINT* INTEGER *REMOVE-DUPLICATES-CROSSOVER-POINT* :DOCUMENTATION \"Point where we switch from using a KV-CONS table\nrepresentation to a STELLA hash table to preserve O(1) access.\")", &oKEY_VALUE_MAP_CROSSOVER_POINTo);
    }
  }
}

Surrogate* SGT_COLLECTIONS_STELLA_COLLECTION = NULL;

Surrogate* SGT_COLLECTIONS_STELLA_SET = NULL;

Symbol* SYM_COLLECTIONS_STELLA_VECTOR = NULL;

Keyword* KWD_COLLECTIONS_CPP = NULL;

Keyword* KWD_COLLECTIONS_FUNCTION = NULL;

Surrogate* SGT_COLLECTIONS_STELLA_VECTOR = NULL;

Surrogate* SGT_COLLECTIONS_STELLA_VECTOR_SEQUENCE = NULL;

Surrogate* SGT_COLLECTIONS_STELLA_HEAP = NULL;

Symbol* SYM_COLLECTIONS_STELLA_PREDICATE = NULL;

Symbol* SYM_COLLECTIONS_STELLA_FILL_POINTER = NULL;

Surrogate* SGT_COLLECTIONS_STELLA_STELLA_HASH_TABLE = NULL;

Symbol* SYM_COLLECTIONS_STELLA_SIZE = NULL;

Symbol* SYM_COLLECTIONS_STELLA_INITIAL_SIZE = NULL;

Symbol* SYM_COLLECTIONS_STELLA_FREE_ELEMENTS = NULL;

Symbol* SYM_COLLECTIONS_STELLA_EQUAL_TESTp = NULL;

Surrogate* SGT_COLLECTIONS_STELLA_STELLA_HASH_TABLE_ITERATOR = NULL;

Symbol* SYM_COLLECTIONS_STELLA_BUCKET_INDEX = NULL;

Symbol* SYM_COLLECTIONS_STELLA_BUCKET_CURSOR = NULL;

Surrogate* SGT_COLLECTIONS_STELLA_KEY_VALUE_MAP = NULL;

Symbol* SYM_COLLECTIONS_STELLA_THE_MAP = NULL;

Symbol* SYM_COLLECTIONS_STELLA_CROSSOVER_POINT = NULL;

Surrogate* SGT_COLLECTIONS_STELLA_HASH_SET = NULL;

Surrogate* SGT_COLLECTIONS_STELLA_CONS = NULL;

Surrogate* SGT_COLLECTIONS_STELLA_LIST = NULL;

Surrogate* SGT_COLLECTIONS_STELLA_1D_ARRAY = NULL;

Symbol* SYM_COLLECTIONS_STELLA_OBJECT_ARRAY = NULL;

Surrogate* SGT_COLLECTIONS_STELLA_1D_FLOAT_ARRAY = NULL;

Symbol* SYM_COLLECTIONS_STELLA_FLOAT_ARRAY = NULL;

Surrogate* SGT_COLLECTIONS_STELLA_2D_ARRAY = NULL;

Surrogate* SGT_COLLECTIONS_STELLA_2D_FLOAT_ARRAY = NULL;

Surrogate* SGT_COLLECTIONS_STELLA_BUFFERED_STRING = NULL;

Symbol* SYM_COLLECTIONS_STELLA_BUFFER = NULL;

Symbol* SYM_COLLECTIONS_STELLA_BUFFER_SIZE = NULL;

Symbol* SYM_COLLECTIONS_STELLA_STRING_BUFFER = NULL;

Symbol* SYM_COLLECTIONS_STELLA_STARTUP_COLLECTIONS = NULL;

Symbol* SYM_COLLECTIONS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
