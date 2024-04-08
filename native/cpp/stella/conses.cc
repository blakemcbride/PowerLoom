//  -*- Mode: C++ -*-

// conses.cc

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

Cons* NIL = NULL;

boolean Cons::emptyP() {
  // Return `true' iff `self' equals `nil'.
  { Cons* self = this;

    return (self == NIL);
  }
}

boolean Cons::nonEmptyP() {
  // Return `true' iff `self' is not equal to `nil'.
  { Cons* self = this;

    return (!(self == NIL));
  }
}

boolean nilP(Object* x) {
  // Return `true' iff `x' equals `nil'.
  return (x == NIL);
}

int Cons::length() {
  // Return the length of the CONS list `self'.
  { Cons* self = this;

    { Cons* cons = self;
      int i = 0;

      while (!(cons == NIL)) {
        i = i + 1;
        cons = cons->rest;
      }
      return (i);
    }
  }
}

int Cons::position(Object* object, int start) {
  // Return the position of `object' within the cons-list
  // `self' (counting from zero); or return `null' if `object' does not occur within 
  // `self' (uses an `eql?' test).  If `start' was supplied as non-`null', only 
  // consider the sublist starting at `start', however, the returned position 
  // will always be relative to the entire list.
  { Cons* self = this;

    if (start == NULL_INTEGER) {
      start = 0;
    }
    { Object* element = NULL;
      Cons* iter000 = self->nthRest(start);
      int position = NULL_INTEGER;
      int iter001 = start;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        element = iter000->value;
        position = iter001;
        if (eqlP(element, object)) {
          return (position);
        }
      }
    }
    return (NULL_INTEGER);
  }
}

int Cons::lastPosition(Object* object, int end) {
  // Return the position of `object' within the cons-list
  // `self' (counting from zero); or return `null' if `object' does not occur within 
  // `self' (uses an `eql?' test).  If `start' was supplied as non-`null', only 
  // consider the sublist ending at `end', however, the returned position 
  // will always be relative to the entire list.
  { Cons* self = this;

    { int lastPos = NULL_INTEGER;

      if (end == NULL_INTEGER) {
        end = self->length() - 1;
      }
      { Object* element = NULL;
        Cons* iter000 = self;
        int position = NULL_INTEGER;
        int iter001 = 0;
        int upperBound000 = end;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; (!(iter000 == NIL)) &&
                  (unboundedP000 ||
                   (iter001 <= upperBound000)); 
              iter000 = iter000->rest,
              iter001 = iter001 + 1) {
          element = iter000->value;
          position = iter001;
          if (eqlP(element, object)) {
            lastPos = position;
          }
        }
      }
      return (lastPos);
    }
  }
}

boolean Cons::memberP(Object* object) {
  // Return `true' iff `object' is a member of the cons list
  // `self' (uses an `eql?' test).
  { Cons* self = this;

    if ((!((boolean)(object))) ||
        object->standardObjectP()) {
      { Object* i = NULL;
        Cons* iter000 = self;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          i = iter000->value;
          if (i == object) {
            return (true);
          }
        }
      }
    }
    else {
      { Object* i = NULL;
        Cons* iter001 = self;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          i = iter001->value;
          if (eqlP(i, object)) {
            return (true);
          }
        }
      }
    }
    return (false);
  }
}

boolean Cons::membP(Object* object) {
  // Return `true' iff `object' is a member of the cons list
  // `self' (uses an `eq?' test).
  { Cons* self = this;

    { Object* i = NULL;
      Cons* iter000 = self;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        i = iter000->value;
        if (i == object) {
          return (true);
        }
      }
    }
    return (false);
  }
}

Cons* cons(Object* value, Cons* rest) {
  // Return a cons record that points to `value' and `rest'.
  { Cons* cons = new Cons();

    cons->value = value;
    cons->rest = rest;
    return (cons);
  }
}

Cons* Cons::remove(Object* value) {
  // Destructively remove all entries in the cons list `self' that
  // match `value'.  Unless the remaining list is `nil', insure that the cons that
  // heads the list is unchanged.
  { Cons* self = this;

    { Cons* cons = self;
      Cons* previouscons = NULL;

      if (!(cons == NIL)) {
        if (!(cons->rest == NIL)) {
          previouscons = cons;
          cons = cons->rest;
          while (!(cons == NIL)) {
            if (eqlP(cons->value, value)) {
              {
                previouscons->rest = cons->rest;
                cons = cons->rest;
              }
            }
            else {
              {
                previouscons = cons;
                cons = cons->rest;
              }
            }
          }
        }
        if (eqlP(self->value, value)) {
          if (self->rest == NIL) {
            return (NIL);
          }
          cons = self->rest;
          self->value = cons->value;
          self->rest = cons->rest;
        }
      }
      return (self);
    }
  }
}

Cons* Cons::removeIf(cpp_function_code testP) {
  // Destructively removes all members of the cons list
  // `self' for which `test?' evaluates to `true'.  `test' takes a single 
  // argument of type OBJECT and returns `true' or `false'.  Returns a cons list.
  // In case the first element is removed, the return result should be
  // assigned to a variable.
  { Cons* self = this;

    { Cons* cursor = self;
      Cons* trailer = NULL;

      while (!(cursor == NIL)) {
        if (((boolean  (*) (Object*))testP)(cursor->value) &&
            ((boolean)(trailer))) {
          {
            trailer->rest = cursor->rest;
            cursor = trailer->rest;
          }
        }
        else {
          {
            trailer = cursor;
            cursor = cursor->rest;
          }
        }
      }
      cursor = self;
      if ((!(cursor == NIL)) &&
          ((boolean  (*) (Object*))testP)(cursor->value)) {
        trailer = cursor->rest;
        return (trailer);
      }
      return (self);
    }
  }
}

// Point where we switch from using a quadratic remove
// duplicates algorithm to a linear one using a hash table.  For
// an unoptimized Common Lisp, 20 is a good crossover point.
int oREMOVE_DUPLICATES_CROSSOVER_POINTo = 20;

Cons* Cons::removeDuplicates() {
  // Destructively remove duplicates from `self' and return the
  // result.  Removes all but the first occurrence of items in the list.
  // Preserves the original order of the remaining members.  Runs in linear time.
  { Cons* self = this;

    if (self->length() > oREMOVE_DUPLICATES_CROSSOVER_POINTo) {
      return (removeDuplicatesFromLongList(self, false));
    }
    else {
      { Cons* cursor = self;
        Cons* rest = NULL;

        while (!(cursor == NIL)) {
          rest = cursor->rest;
          if (rest->memberP(cursor->value)) {
            rest = rest->remove(cursor->value);
            cursor->rest = rest;
          }
          cursor = rest;
        }
        return (self);
      }
    }
  }
}

Cons* Cons::removeDuplicatesEqual() {
  // `remove-duplicates' (which see) using an `equal?' test.
  // IMPORTANT: since this uses hashing to speed things up, an `equal-hash-code'
  // method needs to be defined for this to work.
  { Cons* self = this;

    return (removeDuplicatesFromLongList(self, true));
  }
}

Cons* removeDuplicatesFromLongList(Cons* self, boolean equaltestP) {
  { int tablesize = ceiling(self->length() * 0.3);
    Cons** table = new (GC)Cons*[tablesize];
    Cons* cursor = self;
    Object* item = NULL;
    Cons* bucket = NULL;
    int bucketindex = 0;

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = tablesize - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        table[i] = NIL;
      }
    }
    while (!(cursor == NIL)) {
      item = cursor->value;
      if (equaltestP) {
        bucketindex = item->equalHashCode();
      }
      else {
        bucketindex = item->hashCode();
      }
      bucketindex = (((unsigned int) bucketindex) % tablesize);
      bucket = table[bucketindex];
      { boolean foundP000 = false;

        { Object* it = NULL;
          Cons* iter001 = bucket;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            it = iter001->value;
            if ((equaltestP ? equalP(it, item) : eqlP(it, item))) {
              foundP000 = true;
              break;
            }
          }
        }
        if (foundP000) {
          cursor->value = NULL;
        }
        else {
          table[bucketindex] = cons(item, bucket);
        }
      }
      cursor = cursor->rest;
    }
    return (self->remove(NULL));
  }
}

Cons* Cons::concatenate(Cons* list2, int otherlists, ...) {
  // Return a cons list consisting of the concatenation of 
  // `list1', `list2', and `otherLists'.  The operation is destructive wrt all
  // but the last list argument which is left intact.  The two mandatory
  // parameters allow us to optimize the common binary case by not relying on
  // the somewhat less efficient variable arguments mechanism.
  { Cons* list1 = this;

    if (list1 == NIL) {
      list1 = list2;
    }
    else {
      if (list2 == NIL) {
        list2 = list1;
      }
      else {
        lastCons(list1)->rest = list2;
      }
    }
    if (otherlists > 0) {
      { va_list iter000;
        int iter000Count = otherlists;
        Cons* list = NULL;

        va_start(iter000, otherlists);
                for  (; (iter000Count--) > 0; ) {
          list = va_arg(iter000, Cons*);
          if (!(list == NIL)) {
            if (!(list2 == NIL)) {
              lastCons(list2)->rest = list;
            }
            else {
              list1 = list;
            }
            list2 = list;
          }
        }
        va_end(iter000);
      }
    }
    return (list1);
  }
}

Cons* Cons::prepend(Cons* list1) {
  // Return a cons list consisting of the concatenation of
  // `list1' and `self'.  A copy of `list1' is prepended to `self'.  This
  // operation results in structure sharing of `self'; to avoid this, `self'
  // should not be pointed to by anything other than the tail of the prepended
  // copy.
  { Cons* self = this;

    if (list1 == NIL) {
      return (self);
    }
    { Cons* copy1 = copyConsList(list1);

      copy1->concatenate(self, 0);
      return (copy1);
    }
  }
}

Cons* Cons::reverse() {
  // Destructively reverse the members of the cons list `self'.
  { Cons* self = this;

    if (self == NIL) {
      return (self);
    }
    { Cons* reversedconslist = self;
      Cons* remainingconslist = reversedconslist->rest;
      Cons* detachedcons = NULL;

      if (remainingconslist == NIL) {
        return (reversedconslist);
      }
      reversedconslist->rest = NIL;
      while (!(remainingconslist == NIL)) {
        detachedcons = remainingconslist;
        remainingconslist = remainingconslist->rest;
        detachedcons->rest = reversedconslist;
        reversedconslist = detachedcons;
      }
      return (reversedconslist);
    }
  }
}

Cons* Cons::substitute(Object* invalue, Object* outvalue) {
  // Destructively replace each appearance of `outValue' by
  // `inValue' in the cons list `self'.
  { Cons* self = this;

    { Cons* cursor = self;

      while (!(cursor == NIL)) {
        if (eqlP(cursor->value, outvalue)) {
          cursor->value = invalue;
        }
        cursor = cursor->rest;
      }
      return (self);
    }
  }
}

Cons* mapNullToNil(Cons* self) {
  // Return `nil' iff `self' is `null' or `self' otherwise.
  return (((!((boolean)(self))) ? NIL : self));
}

Object* Cons::first() {
  // Return the first element of `self'.  The first element
  // of `self' can be set with `setf'.  Note that '(first NIL)' = `null'.
  { Cons* self = this;

    return (self->value);
  }
}

Object* Cons::second() {
  // Return the second element of `self'.  The second element
  // of `self' can be set with `setf'.  Note that '(second NIL)' = `null'.
  { Cons* self = this;

    return (self->rest->value);
  }
}

Object* Cons::third() {
  // Return the third element of `self'.  The third element
  // of `self' can be set with `setf'.  Note that '(third NIL)' = `null'.
  { Cons* self = this;

    return (self->rest->rest->value);
  }
}

Object* Cons::fourth() {
  // Return the fourth element of `self'.  The fourth element
  // of `self' can be set with `setf'.  Note that '(fourth NIL)' = `null'.
  { Cons* self = this;

    return (self->rest->rest->rest->value);
  }
}

Object* Cons::fifth() {
  // Return the fifth element of `self'.  The fifth element
  // of `self' can be set with `setf'.  Note, that '(fifth NIL)' = `null'.
  { Cons* self = this;

    return (self->rest->rest->rest->rest->value);
  }
}

Object* Cons::nth(int position) {
  // Return the element of `self' at `position'.  The nth element
  // of `self' can be set with `setf'.  Note, that '(nth NIL <pos>)' = `null'.
  { Cons* self = this;

    { int i = -1;

      { Object* value = NULL;
        Cons* iter000 = self;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          value = iter000->value;
          if ((i = i + 1) == position) {
            return (value);
          }
        }
      }
      return (NULL);
    }
  }
}

Cons* Cons::nthRest(int position) {
  // Apply `rest' `position' times to `self'.
  { Cons* self = this;

    if (position < 0) {
      return (NULL);
    }
    { Cons* cursor = self;

      { int i = NULL_INTEGER;
        int iter000 = 1;
        int upperBound000 = position;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter000 <= upperBound000); 
              iter000 = iter000 + 1) {
          i = iter000;
          i = i;
          cursor = cursor->rest;
          if (cursor == NIL) {
            return (NIL);
          }
        }
      }
      return (cursor);
    }
  }
}

Cons* lastCons(Cons* self) {
  // Return the last cons of `self'.
  while (!(self->rest == NIL)) {
    self = self->rest;
  }
  return (self);
}

Object* Cons::last() {
  // Return the last element of `self'.
  { Cons* self = this;

    return (lastCons(self)->value);
  }
}

Object* Cons::firstSetter(Object* value) {
  { Cons* self = this;

    if (self == NIL) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't apply first setter to empty list." << std::endl;
      return (NULL);
    }
    return (self->value = value);
  }
}

Object* Cons::secondSetter(Object* value) {
  { Cons* self = this;

    if (self->rest == NIL) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "'second setter' applied to too short cons list." << std::endl;
      return (NULL);
    }
    return (self->rest->value = value);
  }
}

Object* Cons::thirdSetter(Object* value) {
  { Cons* self = this;

    { Cons* thirdcons = self->rest->rest;

      if (!(thirdcons == NIL)) {
        return (thirdcons->value = value);
      }
      else {
        {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "'third setter' applied to too short cons list." << std::endl;
          return (NULL);
        }
      }
    }
  }
}

Object* Cons::nthSetter(Object* value, int position) {
  { Cons* self = this;

    if (position < 0) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't apply nth setter to negative position " << "`" << position << "'" << "." << std::endl;
      return (NULL);
    }
    { Cons* cursor = self;

      { int i = NULL_INTEGER;
        int iter000 = 1;
        int upperBound000 = position;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter000 <= upperBound000); 
              iter000 = iter000 + 1) {
          i = iter000;
          i = i;
          cursor = cursor->rest;
          if (cursor == NIL) {
            *(STANDARD_WARNING->nativeStream) << "Warning: " << "'nth setter' ran off end of cons list." << std::endl;
            return (NULL);
          }
        }
      }
      cursor->value = value;
      return (value);
    }
  }
}

Object* Cons::fourthSetter(Object* value) {
  { Cons* self = this;

    return (self->nthSetter(value, 3));
  }
}

Object* Cons::fifthSetter(Object* value) {
  { Cons* self = this;

    return (self->nthSetter(value, 4));
  }
}

Object* Cons::nthRestSetter(Object* value, int position) {
  { Cons* self = this;

    if (position <= 0) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't apply nth-rest setter to negative position " << "`" << position << "'" << "." << std::endl;
    }
    { Cons* cursor = self;

      { int i = NULL_INTEGER;
        int iter000 = 2;
        int upperBound000 = position;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter000 <= upperBound000); 
              iter000 = iter000 + 1) {
          i = iter000;
          i = i;
          cursor = cursor->rest;
          if (cursor == NIL) {
            *(STANDARD_WARNING->nativeStream) << "Warning: " << "'nth-rest setter' ran off end of cons list." << std::endl;
            return (NULL);
          }
        }
      }
      cursor->rest = ((Cons*)(value));
      return (value);
    }
  }
}

ConsIterator* Cons::allocateIterator() {
  { Cons* self = this;

    { ConsIterator* iterator = newConsIterator();

      iterator->consIteratorCursor = self;
      iterator->firstIterationP = true;
      return (iterator);
    }
  }
}

boolean terminateConsIteratorP(ConsIterator* self) {
  self->consIteratorCursor = NULL;
  return (true);
}

boolean ConsIterator::nextP() {
  { ConsIterator* self = this;

    if (self->firstIterationP) {
      self->firstIterationP = false;
    }
    else {
      self->consIteratorCursor = self->consIteratorCursor->rest;
    }
    self->value = self->consIteratorCursor->value;
    return (!(self->consIteratorCursor == NIL));
  }
}

boolean ConsIterator::emptyP() {
  { ConsIterator* self = this;

    return ((self->firstIterationP ? (self->consIteratorCursor == NIL) : (self->consIteratorCursor->rest == NIL)));
  }
}

int ConsIterator::length() {
  // Iterate over 'self', and count how many items there are.
  { ConsIterator* self = this;

    { int count = (self->firstIterationP ? self->consIteratorCursor->length() : self->consIteratorCursor->rest->length());

      self->consIteratorCursor = NIL;
      return (count);
    }
  }
}

boolean ConsIterator::memberP(Object* value) {
  // Iterate over values of `self' and return TRUE
  // if one of them is `eql?' to 'value.
  { ConsIterator* self = this;

    { boolean result = (self->firstIterationP ? self->consIteratorCursor->memberP(value) : self->consIteratorCursor->rest->memberP(value));

      self->consIteratorCursor = NIL;
      return (result);
    }
  }
}

Object* ConsIterator::valueSetter(Object* value) {
  { ConsIterator* self = this;

    self->consIteratorCursor->value = value;
    self->value = value;
    return (value);
  }
}

void addConsToEndOfConsList(Cons* self, Cons* lastcons) {
  while (!(self->rest == NIL)) {
    self = self->rest;
  }
  self->rest = lastcons;
}

boolean butLastNextP(AllPurposeIterator* self) {
  if (self->firstIterationP) {
    self->firstIterationP = false;
  }
  else {
    self->iteratorConsList = self->iteratorConsList->rest;
  }
  if (self->iteratorConsList->rest == NIL) {
    return (false);
  }
  self->value = self->iteratorConsList->value;
  return (true);
}

Iterator* Cons::butLast() {
  // Generate all but the last element of the cons list `self'.
  { Cons* self = this;

    { AllPurposeIterator* iterator = newAllPurposeIterator();

      iterator->iteratorConsList = self;
      iterator->firstIterationP = true;
      iterator->iteratorNextCode = ((cpp_function_code)(&butLastNextP));
      return (iterator);
    }
  }
}

Cons* Cons::consify() {
  // Return `self'.
  { Cons* self = this;

    return (self);
  }
}

Cons* List::consify() {
  // Return a list of elements in `self'.
  { List* self = this;

    return (self->theConsList);
  }
}

Cons* KeyValueList::consify() {
  // Return a list of key-value pairs in `self'.
  { KeyValueList* self = this;

    { Cons* result = NIL;

      { Object* k = NULL;
        Object* v = NULL;
        KvCons* iter000 = self->theKvList;
        Cons* collect000 = NULL;

        for  (; ((boolean)(iter000)); 
              iter000 = iter000->rest) {
          k = iter000->key;
          v = iter000->value;
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(cons(k, cons(v, NIL)), NIL);
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
              collect000->rest = cons(cons(k, cons(v, NIL)), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      return (result);
    }
  }
}

Cons* Vector::consify() {
  // Return a list of elements in `self'.
  { Vector* self = this;

    { Cons* result = NIL;

      { Object* v = NULL;
        Vector* vector000 = self;
        int index000 = 0;
        int length000 = vector000->length();
        Cons* collect000 = NULL;

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          v = (vector000->theArray)[index000];
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(v, NIL);
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
              collect000->rest = cons(v, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      return (result);
    }
  }
}

Cons* Iterator::consify() {
  // Return a list of elements generated by `self'.
  { Iterator* self = this;

    { Cons* list = NIL;

      { Object* value = NULL;
        Iterator* iter000 = self;

        for (; iter000->nextP(); ) {
          value = iter000->value;
          list = cons(value, list);
        }
      }
      return (list->reverse());
    }
  }
}

Cons* Object::consify() {
  // If `object' is a CONS, return it.  Otherwise, return
  // a singleton cons list containing it.
  { Object* self = this;

    return ((consP(self) ? ((Cons*)(self)) : cons(self, NIL)));
  }
}

Cons* Cons::removeDeletedMembers() {
  { Cons* self = this;

    { Cons* cursor = self;
      Cons* trailer = NULL;

      while (!(cursor == NIL)) {
        if (cursor->value->deletedP() &&
            ((boolean)(trailer))) {
          {
            trailer->rest = cursor->rest;
            cursor = trailer->rest;
          }
        }
        else {
          {
            trailer = cursor;
            cursor = cursor->rest;
          }
        }
      }
      if ((!(self == NIL)) &&
          self->value->deletedP()) {
        return (self->rest);
      }
      return (self);
    }
  }
}

Cons* copyConsList(Cons* self) {
  // Return a copy of the cons list `self'.
  if (self == NIL) {
    return (NIL);
  }
  { Cons* newconslist = cons(self->value, NIL);
    Cons* nextcons = newconslist;
    Cons* copyfromcons = NULL;
    Cons* previouscons = NULL;

    copyfromcons = self->rest;
    while (!(copyfromcons == NIL)) {
      previouscons = nextcons;
      nextcons = cons(copyfromcons->value, NIL);
      previouscons->rest = nextcons;
      copyfromcons = copyfromcons->rest;
    }
    return (newconslist);
  }
}

Cons* consList(int values, ...) {
  // Return a cons list containing `values', in order.
  { Cons* list = NIL;

    { va_list iter000;
      int iter000Count = values;
      Object* v = NULL;
      Cons* collect000 = NULL;

      va_start(iter000, values);
            for  (; (iter000Count--) > 0; ) {
        v = va_arg(iter000, Object*);
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(v, NIL);
            if (list == NIL) {
              list = collect000;
            }
            else {
              addConsToEndOfConsList(list, collect000);
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
      va_end(iter000);
    }
    return (list);
  }
}

Cons* makeConsList(int size) {
  // Return a cons list of length 'size' initialized with NULL values.
  { Cons* cell = NULL;
    Cons* list = NIL;

    while (size > 0) {
      cell = new Cons();
      cell->value = NULL;
      cell->rest = list;
      list = cell;
      size = size - 1;
    }
    return (list);
  }
}

Cons* consSetFirstGetNext(Cons* list, Object* value) {
  // Set the first element of 'list' to value and return the rest of 'list'.
  // This is primarily a utility for the Python API to construct CONS-lists.
  if (!(list == NIL)) {
    list->value = value;
  }
  return (list->rest);
}

Cons* listO(int values, ...) {
  // Return a list of conses that make up the list `values',
  // terminated by the last value rather than by `nil'.  Assumes that
  // at least one value is passed in.
  { Cons* headcons = NIL;
    Object* answer = NULL;
    Cons* lastcons = NULL;

    { va_list iter000;
      int iter000Count = values;
      Object* v = NULL;

      va_start(iter000, values);
            for  (; (iter000Count--) > 0; ) {
        v = va_arg(iter000, Object*);
        headcons = cons(v, headcons);
      }
      va_end(iter000);
    }
    answer = headcons->rest->reverse();
    if (answer == NIL) {
      answer = headcons->value;
      return (((Cons*)(answer)));
    }
    lastcons = ((Cons*)(answer));
    while (!(lastcons->rest == NIL)) {
      lastcons = lastcons->rest;
    }
    lastcons->rest = ((Cons*)(headcons->value));
    return (((Cons*)(answer)));
  }
}

Cons* append(Cons* conslist1, Cons* conslist2) {
  // Return a cons list representing the concatenation
  // of `consList1' and `consList2'.  The concatenation is NOT destructive.
  if (conslist1 == NIL) {
    return (conslist2);
  }
  else if (conslist2 == NIL) {
    return (conslist1);
  }
  else {
    return (copyConsList(conslist1)->concatenate(conslist2, 0));
  }
}

boolean Cons::subsetP(Cons* otherlist) {
  // Return true if every element of `self' also occurs in `otherList'.
  // Uses an `eql?' test and a simple quadratic-time algorithm.  Note that
  // this does not check whether `self' and `otherList' actually are sets.
  { Cons* self = this;

    { boolean alwaysP000 = true;

      { Object* item = NULL;
        Cons* iter000 = self;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          item = iter000->value;
          if (!otherlist->memberP(item)) {
            alwaysP000 = false;
            break;
          }
        }
      }
      { boolean value000 = alwaysP000;

        return (value000);
      }
    }
  }
}

boolean Cons::equivalentSetsP(Cons* otherlist) {
  // Return true if every element of `self' occurs in `otherList' and vice versa.
  // Uses an `eql?' test and a simple quadratic-time algorithm.  Note that
  // this does not check whether `self' and `otherList' actually are sets.
  { Cons* self = this;

    { boolean testValue000 = false;

      testValue000 = self->length() == otherlist->length();
      if (testValue000) {
        { boolean alwaysP000 = true;

          { Object* item = NULL;
            Cons* iter000 = self;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              item = iter000->value;
              if (!otherlist->memberP(item)) {
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

boolean Cons::disjointSetsP(Cons* otherlist) {
  // Return true if the intersection of `self' and `otherList' is empty.
  // This is always true if at least one of the two sets is the empty set.
  // Uses an `eql?' test and a simple quadratic-time algorithm.  Note that
  // this does not check whether `self' and `otherList' actually are sets.
  { Cons* self = this;

    { boolean alwaysP000 = true;

      { Object* item = NULL;
        Cons* iter000 = self;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          item = iter000->value;
          if (!(!otherlist->memberP(item))) {
            alwaysP000 = false;
            break;
          }
        }
      }
      { boolean value000 = alwaysP000;

        return (value000);
      }
    }
  }
}

Cons* Cons::intersection(Cons* otherlist) {
  // Return the set intersection of `self' and `otherList'.  Uses an `eql?'
  // test and a simple quadratic-time algorithm.  Note that the result is only
  // guaranteed to be a set if both `self' and `otherList' are sets.
  { Cons* self = this;

    { Cons* list = NIL;

      if (!((boolean)(otherlist))) {
        return (list);
      }
      { Object* i = NULL;
        Cons* iter000 = self;
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          i = iter000->value;
          if (otherlist->memberP(i)) {
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(i, NIL);
                if (list == NIL) {
                  list = collect000;
                }
                else {
                  addConsToEndOfConsList(list, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(i, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
      }
      return (list);
    }
  }
}

Cons* Cons::unioN(Cons* otherlist) {
  // Return the set union of `self' and `otherList'.  Uses an `eql?' test
  // and a simple quadratic-time algorithm.  Note that the result is only
  // guaranteed to be a set if both `self' and `otherList' are sets.
  { Cons* self = this;

    { Cons* list = copyConsList(self);
      Cons* othersurvivors = NIL;

      if (!((boolean)(otherlist))) {
        return (list);
      }
      { Object* i = NULL;
        Cons* iter000 = otherlist;
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          i = iter000->value;
          if (!list->memberP(i)) {
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(i, NIL);
                if (othersurvivors == NIL) {
                  othersurvivors = collect000;
                }
                else {
                  addConsToEndOfConsList(othersurvivors, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(i, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
      }
      return (list->concatenate(othersurvivors, 0));
    }
  }
}

Cons* Cons::difference(Cons* otherlist) {
  // Return the set difference of `self' and `otherList' (i.e., all elements
  // that are in `self' but not in `otherSet').  Uses an `eql?' test and a simple
  // quadratic-time algorithm.  Note that the result is only guaranteed to be a
  // set if both `self' and `otherList' are sets.
  { Cons* self = this;

    if ((!((boolean)(otherlist))) ||
        (otherlist == NIL)) {
      return (copyConsList(self));
    }
    { Cons* diff = NIL;

      { Object* i = NULL;
        Cons* iter000 = self;
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          i = iter000->value;
          if (!otherlist->memberP(i)) {
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(i, NIL);
                if (diff == NIL) {
                  diff = collect000;
                }
                else {
                  addConsToEndOfConsList(diff, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(i, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
      }
      return (diff);
    }
  }
}

Cons* Cons::subtract(Cons* otherlist) {
  // Return the set difference of `self' and `otherList' by destructively
  // removing elements from `self' that also occur in `otherList'.  Uses an `eql?'
  // test and a simple quadratic-time algorithm.  Note that the result is only
  // guaranteed to be a set if `self' is a set.
  { Cons* self = this;

    if (!((boolean)(otherlist))) {
      return (self);
    }
    { Object* i = NULL;
      Cons* iter000 = otherlist;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        i = iter000->value;
        if (self->memberP(i)) {
          self = self->remove(i);
        }
      }
    }
    return (self);
  }
}

Cons* Cons::sort(cpp_function_code predicate) {
  // Perform a stable, destructive sort of `self' according to
  // `predicate', and return the result.  If `predicate' has a '<' semantics, the
  // result will be in ascending order.  It is not guaranteed that `self' will
  // point to the beginning of the sorted result.  If `predicate' is `null', a
  // suitable '<' predicate is chosen depending on the first element of `self',
  // and it is assumed that all elements of `self' have the same type (supported
  // element types are GENERALIZED-SYMBOL, STRING, INTEGER, and FLOAT).
  { Cons* self = this;

    if (predicate == NULL) {
      predicate = chooseSortPredicate(self->value);
    }
    return (helpSortConsList(self, self->length(), predicate));
  }
}

Cons* helpSortConsList(Cons* list, int length, cpp_function_code predicate) {
  if (length < 2) {
    return (list);
  }
  { int frontlength = stella::floor(length / 2.0);
    Cons* temp = list;
    Cons* back = NIL;

    { int i = NULL_INTEGER;
      int iter000 = 2;
      int upperBound000 = frontlength;
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;

      for  (; unboundedP000 ||
                (iter000 <= upperBound000); 
            iter000 = iter000 + 1) {
        i = iter000;
        i = i;
        temp = temp->rest;
      }
    }
    back = temp->rest;
    temp->rest = NIL;
    return (mergeConsLists(helpSortConsList(list, frontlength, predicate), helpSortConsList(back, length - frontlength, predicate), predicate));
  }
}

Cons* mergeConsLists(Cons* list1, Cons* list2, cpp_function_code predicate) {
  { Cons* cursor1 = list1;
    Cons* cursor2 = list2;
    Cons* result = NIL;
    Cons* tail = NIL;
    Cons* temp = NIL;

    for (;;) {
      if (cursor1 == NIL) {
        if (tail == NIL) {
          return (cursor2);
        }
        tail->rest = cursor2;
        return (result);
      }
      if (cursor2 == NIL) {
        if (tail == NIL) {
          return (cursor1);
        }
        tail->rest = cursor1;
        return (result);
      }
      if (((boolean  (*) (Object*, Object*))predicate)(cursor2->value, cursor1->value)) {
        temp = cursor2;
        cursor2 = cursor2->rest;
        list2 = cursor2;
      }
      else {
        temp = cursor1;
        cursor1 = cursor1->rest;
        list1 = cursor1;
      }
      if (tail == NIL) {
        result = temp;
      }
      else {
        tail->rest = temp;
      }
      tail = temp;
    }
  }
}

boolean generalizedSymbolLessThanP(GeneralizedSymbol* x, GeneralizedSymbol* y) {
  return (stringL(x->symbolName, y->symbolName));
}

boolean wrappedIntegerLessThanP(IntegerWrapper* x, IntegerWrapper* y) {
  return (x->wrapperValue < y->wrapperValue);
}

boolean wrappedLongIntegerLessThanP(LongIntegerWrapper* x, LongIntegerWrapper* y) {
  return (x->wrapperValue < y->wrapperValue);
}

boolean wrappedFloatLessThanP(FloatWrapper* x, FloatWrapper* y) {
  return (x->wrapperValue < y->wrapperValue);
}

boolean wrappedStringLessThanP(StringWrapper* x, StringWrapper* y) {
  return (stringL(x->wrapperValue, y->wrapperValue));
}

boolean wrappedMutableStringLessThanP(MutableStringWrapper* x, MutableStringWrapper* y) {
  return (stringL((x->wrapperValue), (y->wrapperValue)));
}

boolean numberLessThanP(NumberWrapper* x, NumberWrapper* y) {
  // Generic number comparison that works with integers, longs and floats.
  { Surrogate* testValue000 = safePrimaryType(x);

    if (subtypeOfIntegerP(testValue000)) {
      { NumberWrapper* x000 = x;
        IntegerWrapper* x = ((IntegerWrapper*)(x000));

        { Surrogate* testValue001 = safePrimaryType(y);

          if (subtypeOfFloatP(testValue001)) {
            { NumberWrapper* y000 = y;
              FloatWrapper* y = ((FloatWrapper*)(y000));

              return (x->wrapperValue < y->wrapperValue);
            }
          }
          else if (subtypeOfLongIntegerP(testValue001)) {
            { NumberWrapper* y001 = y;
              LongIntegerWrapper* y = ((LongIntegerWrapper*)(y001));

              return (x->wrapperValue < y->wrapperValue);
            }
          }
          else if (subtypeOfIntegerP(testValue001)) {
            { NumberWrapper* y002 = y;
              IntegerWrapper* y = ((IntegerWrapper*)(y002));

              return (x->wrapperValue < y->wrapperValue);
            }
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
      }
    }
    else if (subtypeOfLongIntegerP(testValue000)) {
      { NumberWrapper* x001 = x;
        LongIntegerWrapper* x = ((LongIntegerWrapper*)(x001));

        { Surrogate* testValue002 = safePrimaryType(y);

          if (subtypeOfFloatP(testValue002)) {
            { NumberWrapper* y003 = y;
              FloatWrapper* y = ((FloatWrapper*)(y003));

              return (x->wrapperValue < y->wrapperValue);
            }
          }
          else if (subtypeOfLongIntegerP(testValue002)) {
            { NumberWrapper* y004 = y;
              LongIntegerWrapper* y = ((LongIntegerWrapper*)(y004));

              return (x->wrapperValue < y->wrapperValue);
            }
          }
          else if (subtypeOfIntegerP(testValue002)) {
            { NumberWrapper* y005 = y;
              IntegerWrapper* y = ((IntegerWrapper*)(y005));

              return (x->wrapperValue < y->wrapperValue);
            }
          }
          else {
            { OutputStringStream* stream001 = newOutputStringStream();

              *(stream001->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
              throw *newStellaException(stream001->theStringReader());
            }
          }
        }
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { NumberWrapper* x002 = x;
        FloatWrapper* x = ((FloatWrapper*)(x002));

        { Surrogate* testValue003 = safePrimaryType(y);

          if (subtypeOfFloatP(testValue003)) {
            { NumberWrapper* y006 = y;
              FloatWrapper* y = ((FloatWrapper*)(y006));

              return (x->wrapperValue < y->wrapperValue);
            }
          }
          else if (subtypeOfLongIntegerP(testValue003)) {
            { NumberWrapper* y007 = y;
              LongIntegerWrapper* y = ((LongIntegerWrapper*)(y007));

              return (x->wrapperValue < y->wrapperValue);
            }
          }
          else if (subtypeOfIntegerP(testValue003)) {
            { NumberWrapper* y008 = y;
              IntegerWrapper* y = ((IntegerWrapper*)(y008));

              return (x->wrapperValue < y->wrapperValue);
            }
          }
          else {
            { OutputStringStream* stream002 = newOutputStringStream();

              *(stream002->nativeStream) << "`" << testValue003 << "'" << " is not a valid case option";
              throw *newStellaException(stream002->theStringReader());
            }
          }
        }
      }
    }
    else {
      { OutputStringStream* stream003 = newOutputStringStream();

        *(stream003->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream003->theStringReader());
      }
    }
  }
}

cpp_function_code chooseSortPredicate(Object* firstelement) {
  if (!((boolean)(firstelement))) {
    return (NULL);
  }
  { Surrogate* testValue000 = safePrimaryType(firstelement);

    if (subtypeOfP(testValue000, SGT_CONSES_STELLA_GENERALIZED_SYMBOL)) {
      { Object* firstelement000 = firstelement;
        GeneralizedSymbol* firstelement = ((GeneralizedSymbol*)(firstelement000));

        return (((cpp_function_code)(&generalizedSymbolLessThanP)));
      }
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { Object* firstelement001 = firstelement;
        IntegerWrapper* firstelement = ((IntegerWrapper*)(firstelement001));

        return (((cpp_function_code)(&wrappedIntegerLessThanP)));
      }
    }
    else if (subtypeOfLongIntegerP(testValue000)) {
      { Object* firstelement002 = firstelement;
        LongIntegerWrapper* firstelement = ((LongIntegerWrapper*)(firstelement002));

        return (((cpp_function_code)(&wrappedLongIntegerLessThanP)));
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { Object* firstelement003 = firstelement;
        FloatWrapper* firstelement = ((FloatWrapper*)(firstelement003));

        return (((cpp_function_code)(&wrappedFloatLessThanP)));
      }
    }
    else if (subtypeOfStringP(testValue000)) {
      { Object* firstelement004 = firstelement;
        StringWrapper* firstelement = ((StringWrapper*)(firstelement004));

        return (((cpp_function_code)(&wrappedStringLessThanP)));
      }
    }
    else if (subtypeOfP(testValue000, SGT_CONSES_STELLA_MUTABLE_STRING_WRAPPER)) {
      { Object* firstelement005 = firstelement;
        MutableStringWrapper* firstelement = ((MutableStringWrapper*)(firstelement005));

        return (((cpp_function_code)(&wrappedMutableStringLessThanP)));
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "choose-sort-predicate: Don't know how to sort " << "`" << firstelement->primaryType() << "'" << "s";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

DEFINE_STELLA_SPECIAL(oSORT_TUPLE_COMPARE_PREDICATEo, cpp_function_code , NULL);

DEFINE_STELLA_SPECIAL(oSORT_TUPLE_COMPARE_INDEXo, int , 0);

boolean sortTupleCompareP(Cons* x, Cons* y) {
  { int n = oSORT_TUPLE_COMPARE_INDEXo;
    cpp_function_code pred = oSORT_TUPLE_COMPARE_PREDICATEo;

    return (((boolean  (*) (Object*, Object*))pred)(x->nth(n), y->nth(n)));
  }
}

Cons* Cons::sortTuples(int n, cpp_function_code predicate) {
  // Just like `sort' but assumes each element of `self' is a tuple (a cons)
  // whose `n'-th element (0-based) will be used for comparison.
  { Cons* self = this;

    if ((predicate == NULL) &&
        (!(self == NIL))) {
      predicate = chooseSortPredicate(((Cons*)(self->value))->nth(n));
    }
    { 
      BIND_STELLA_SPECIAL(oSORT_TUPLE_COMPARE_PREDICATEo, cpp_function_code, predicate);
      BIND_STELLA_SPECIAL(oSORT_TUPLE_COMPARE_INDEXo, int, n);
      return (helpSortConsList(self, self->length(), ((cpp_function_code)(&sortTupleCompareP))));
    }
  }
}

DEFINE_STELLA_SPECIAL(oSORT_OBJECTS_COMPARE_SLOTo, StorageSlot* , NULL);

boolean sortObjectsCompareP(Object* x, Object* y) {
  { StorageSlot* slot = oSORT_OBJECTS_COMPARE_SLOTo;
    cpp_function_code pred = oSORT_TUPLE_COMPARE_PREDICATEo;

    return (((boolean  (*) (Object*, Object*))pred)(readSlotValue(((StandardObject*)(x)), slot), readSlotValue(((StandardObject*)(y)), slot)));
  }
}

Cons* Cons::sortObjects(StorageSlot* slot, cpp_function_code predicate) {
  // Just like `sort' but assumes each element of `self' has a `slot'
  // whose value will be used for comparison.  Elements must be descendants of
  // STANDARD OBJECT.  Note that while this will work with literal-valued slots,
  // it will cause value wrapping everytime `slot' is read.
  { Cons* self = this;

    if ((predicate == NULL) &&
        (!(self == NIL))) {
      predicate = chooseSortPredicate(readSlotValue(((StandardObject*)(self->value)), slot));
    }
    { 
      BIND_STELLA_SPECIAL(oSORT_TUPLE_COMPARE_PREDICATEo, cpp_function_code, predicate);
      BIND_STELLA_SPECIAL(oSORT_OBJECTS_COMPARE_SLOTo, StorageSlot*, slot);
      return (helpSortConsList(self, self->length(), ((cpp_function_code)(&sortObjectsCompareP))));
    }
  }
}

boolean searchConsTreeP(Object* tree, Object* value) {
  // Return `true' iff the value `value' is embedded within
  // the cons tree `tree'.  Uses an `eql?' test.
  if (safePrimaryType(tree) == SGT_CONSES_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if (tree == NIL) {
        return (value == NIL);
      }
      else {
        return (searchConsTreeP(tree->value, value) ||
            searchConsTreeP(tree->rest, value));
      }
    }
  }
  else {
    return (eqlP(tree, value));
  }
}

boolean searchConsTreeWithFilterP(Object* tree, Object* value, Cons* filter) {
  // Return `true' iff the value `value' is embedded within
  // the cons tree `tree'.  Uses an `eql?' test.  Does not descend into any
  // cons whose first element matches an element of `filter'.
  if (safePrimaryType(tree) == SGT_CONSES_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if (tree == NIL) {
        return (value == NIL);
      }
      else if (filter->memberP(tree->value)) {
        return (false);
      }
      else {
        { boolean foundP000 = false;

          { Object* item = NULL;
            Cons* iter000 = tree;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              item = iter000->value;
              if (searchConsTreeWithFilterP(item, value, filter)) {
                foundP000 = true;
                break;
              }
            }
          }
          { boolean value000 = foundP000;

            return (value000);
          }
        }
      }
    }
  }
  else {
    return (eqlP(tree, value));
  }
}

Object* copyConsTree(Object* self) {
  // Return a copy of the cons tree `self'.
  if (safePrimaryType(self) == SGT_CONSES_STELLA_CONS) {
    { Object* self000 = self;
      Cons* self = ((Cons*)(self000));

      if (self == NIL) {
        return (NIL);
      }
      else {
        return (cons(copyConsTree(self->value), ((Cons*)(copyConsTree(self->rest)))));
      }
    }
  }
  else {
    return (self);
  }
}

boolean equalConsTreesP(Object* tree1, Object* tree2) {
  // Return `true' iff the cons trees `tree1' and `tree2' are
  // structurally equivalent.  Uses an `eql?' test.
  if (eqlP(tree1, tree2)) {
    return (true);
  }
  else {
    if (safePrimaryType(tree1) == SGT_CONSES_STELLA_CONS) {
      { Object* tree1000 = tree1;
        Cons* tree1 = ((Cons*)(tree1000));

        if (safePrimaryType(tree2) == SGT_CONSES_STELLA_CONS) {
          { Object* tree2000 = tree2;
            Cons* tree2 = ((Cons*)(tree2000));

            return (equalConsTreesP(tree1->value, tree2->value) &&
                equalConsTreesP(tree1->rest, tree2->rest));
          }
        }
        else {
          return (false);
        }
      }
    }
    else {
      return (false);
    }
  }
}

boolean Cons::objectEqualP(Object* tree2) {
  // Return `true' iff the cons trees `tree1' and `tree2' are
  // structurally equivalent.  Uses `equal?' to test equality of subtrees.
  { Cons* tree1 = this;

    if (safePrimaryType(tree2) == SGT_CONSES_STELLA_CONS) {
      { Object* tree2000 = tree2;
        Cons* tree2 = ((Cons*)(tree2000));

        while (!(tree1 == NIL)) {
          if (!equalP(tree1->value, tree2->value)) {
            return (false);
          }
          tree1 = tree1->rest;
          tree2 = tree2->rest;
        }
        return (tree2 == NIL);
      }
    }
    else {
      return (false);
    }
  }
}

int Cons::equalHashCode() {
  // Return an `equal?' hash code for `self'.  Note that this
  // is O(N) in the number of elements of `self'.
  { Cons* self = this;

    { int code = 18589447;

      for (;;) {
        if (self == NIL) {
          break;
        }
        code = (code ^ (safeEqualHashCode(self->value)));
        self = self->rest;
        code = (((code & 1) == 0) ? ((unsigned int)code >> 1) : (((code >> 1)) | oINTEGER_MSB_MASKo));
      }
      return (code);
    }
  }
}

Object* substituteConsTree(Object* tree, Object* newvalue, Object* oldvalue) {
  // Destructively replace each appearance of `oldValue' by
  // `newValue' in the cons tree `tree'.  Return the tree.  Uses an `eql?' test.
  if (safePrimaryType(tree) == SGT_CONSES_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if (!(tree == NIL)) {
        if (eqlP(tree->value, oldvalue)) {
          tree->value = newvalue;
        }
        else {
          substituteConsTree(tree->value, newvalue, oldvalue);
        }
        substituteConsTree(tree->rest, newvalue, oldvalue);
      }
    }
  }
  else {
  }
  return (tree);
}

Object* consTreeNth(Cons* tree, int index, ...) {
  // Access an arbitrary element of `tree' identified by a path
  // specified as a list of `index' values.  The first `index' specifies the
  // `index'-th element of `tree', the second `index' the `index'-th subelement
  // of that element, etc.  Example:
  // 	 
  //   (cons-tree-nth (quote (a (b (c d e) f) g)) 1 1 2) => e
  // 	
  // 
  { Object* result = tree;

    { va_list iter000;
      int iter000Count = index;
      int i = NULL_INTEGER;

      va_start(iter000, index);
            for  (; (iter000Count--) > 0; ) {
        i = va_arg(iter000, int);
        if (safePrimaryType(result) == SGT_CONSES_STELLA_CONS) {
          { Object* result000 = result;
            Cons* result = ((Cons*)(result000));

            tree = result;
          }
        }
        else {
          return (NULL);
        }
        result = tree->nth(i);
      }
      va_end(iter000);
    }
    return (result);
  }
}

Cons* consTreeNthRest(Cons* tree, int index, ...) {
  // Access an arbitrary sublist of `tree' identified by a path
  // specified as a list of `index' values.  The first `index' specifies the
  // `index'-th element of `tree', the second `index' the `index'-th subelement
  // of that element, ..., the last index specifies the `nth-rest' of the previous
  // element (different from `cons-tree-nth').  Example:
  // 	 
  //   (cons-tree-nth-rest (quote (a (b (c d e) f) g)) 1 1 1) => (d e)
  // 	
  // 
  { Object* result = tree;
    int nofindices = index;

    { va_list iter000;
      int iter000Count = index;
      int i = NULL_INTEGER;
      int j = NULL_INTEGER;
      int iter001 = 1;

      va_start(iter000, index);
            for  (; (iter000Count--) > 0; 
            iter001 = iter001 + 1) {
        i = va_arg(iter000, int);
        j = iter001;
        if (safePrimaryType(result) == SGT_CONSES_STELLA_CONS) {
          { Object* result000 = result;
            Cons* result = ((Cons*)(result000));

            tree = result;
          }
        }
        else {
          return (NULL);
        }
        if (j == nofindices) {
          result = tree->nthRest(i);
        }
        else {
          result = tree->nth(i);
        }
      }
      va_end(iter000);
    }
    return (((Cons*)(result)));
  }
}

KeyValueList* matchConsTree(Object* tree, Object* pattern, KeyValueList* bindings) {
  // Match `pattern' against `tree' and return a list of
  // variable bindings if they match, or NULL otherwise.  `bindings' can
  // be NULL or an initial list of bindings to consider.  Pattern variables
  // use KIF syntax, i.e., they need to start with a `?' character.  A
  // single question mark is interpreted as the anonymous variable. Example:
  // 	 
  //   (match-cons-tree (quote (a (b (a d) e) (a d) f g))
  //                    (quote (a (?x ?y ?) ?y ? g))
  //                    NULL)
  //   => |kv|(<?Y,(A D)> <?X,B>)
  // 	
  // Variables can't be quoted but quoting can effectively be achieved by
  // inserting to-be-quoted variables bound to themselves into `bindings'.
  if (!((boolean)(bindings))) {
    bindings = newKeyValueList();
  }
  if (pattern == SYM_CONSES_STELLA_p) {
    return (bindings);
  }
  { Surrogate* testValue000 = safePrimaryType(pattern);

    if (subtypeOfSymbolP(testValue000)) {
      { Object* pattern000 = pattern;
        Symbol* pattern = ((Symbol*)(pattern000));

        if ((pattern->symbolName)[0] == '?') {
          { Object* value = bindings->lookup(pattern);

            if (!((boolean)(value))) {
              bindings->insertAt(pattern, tree);
              return (bindings);
            }
            else if (equalP(value, tree)) {
              return (bindings);
            }
          }
        }
        else {
          if (tree == pattern) {
            return (bindings);
          }
        }
      }
    }
    else if (testValue000 == SGT_CONSES_STELLA_CONS) {
      { Object* pattern001 = pattern;
        Cons* pattern = ((Cons*)(pattern001));

        if (safePrimaryType(tree) == SGT_CONSES_STELLA_CONS) {
          { Object* tree000 = tree;
            Cons* tree = ((Cons*)(tree000));

            { boolean testValue001 = false;

              testValue001 = tree->length() == pattern->length();
              if (testValue001) {
                { boolean alwaysP000 = true;

                  { Object* elt = NULL;
                    Cons* iter000 = tree;
                    Object* pat = NULL;
                    Cons* iter001 = pattern;

                    for  (; (!(iter000 == NIL)) &&
                              (!(iter001 == NIL)); 
                          iter000 = iter000->rest,
                          iter001 = iter001->rest) {
                      elt = iter000->value;
                      pat = iter001->value;
                      if (!((boolean)(matchConsTree(elt, pat, bindings)))) {
                        alwaysP000 = false;
                        break;
                      }
                    }
                  }
                  testValue001 = alwaysP000;
                }
              }
              if (testValue001) {
                return (bindings);
              }
            }
          }
        }
        else {
        }
      }
    }
    else {
      if (eqlP(tree, pattern)) {
        return (bindings);
      }
    }
  }
  return (NULL);
}

boolean consTreeMatchP(Object* tree, Object* pattern) {
  // Predicate version of `match-cons-tree' (which see).
  return (((boolean)(matchConsTree(tree, pattern, NULL))));
}

// If `true' conses will be pretty printed.
DEFINE_STELLA_SPECIAL(oPRINTPRETTYpo, boolean , true);

// If `true' conses will be printed as readable Stella code.
DEFINE_STELLA_SPECIAL(oPRINTREADABLYpo, boolean , false);

// If non-NULL list-like data structures will print at most
// that many elements.
DEFINE_STELLA_SPECIAL(oPRINTLENGTHo, int , NULL_INTEGER);

// Generates an ellipsis '...' when found in a
// pretty-printed parse tree.
Symbol* ELLIPSIS = NULL;

void printCons(Cons* tree, std::ostream* stream, const char* lparen, const char* rparen) {
  if (oPRINTREADABLYpo) {
    lparen = "(";
    rparen = ")";
  }
  if (oPRINTPRETTYpo) {
    pprintCons(tree, stream, lparen, rparen);
    return;
  }
  *(stream) << lparen;
  if (!(tree == NIL)) {
    *(stream) << tree->value;
    tree = tree->rest;
    if (oPRINTLENGTHo != NULL_INTEGER) {
      { int i = 1;

        { Object* element = NULL;
          Cons* iter000 = tree;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            element = iter000->value;
            *(stream) << " " << element;
            tree = tree->rest;
            i = i + 1;
            if (i >= oPRINTLENGTHo) {
              break;
            }
          }
        }
        if (!(tree == NIL)) {
          *(stream) << " ...";
        }
      }
    }
    else {
      { Object* element = NULL;
        Cons* iter001 = tree;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          element = iter001->value;
          *(stream) << " " << element;
        }
      }
    }
  }
  *(stream) << rparen;
}

void pprintCons(Cons* tree, std::ostream* stream, const char* lparen, const char* rparen) {
  { 
    BIND_STELLA_SPECIAL(oPRINTPRETTYpo, boolean, false);
    printCons(tree, stream, lparen, rparen);
  }
}

// When `true' pretty-print Stella and translated code.
// Since (Lisp) pretty-printing is somewhat slow, turning this off speeds up
// file translation, but it also makes translated output very unreadable.
DEFINE_STELLA_SPECIAL(oPRINTPRETTYCODEpo, boolean , true);

void printStellaCode(Object* tree, std::ostream* stream) {
  { 
    BIND_STELLA_SPECIAL(oPRINTPRETTYpo, boolean, oPRINTPRETTYCODEpo);
    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
    *(stream) << tree << std::endl;
  }
}

void printStellaDefinition(Object* tree, std::ostream* stream) {
  { 
    BIND_STELLA_SPECIAL(oPRINTPRETTYpo, boolean, oPRINTPRETTYCODEpo);
    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
    if (safePrimaryType(tree) == SGT_CONSES_STELLA_CONS) {
      { Object* tree000 = tree;
        Cons* tree = ((Cons*)(tree000));

        if (tree->length() >= 3) {
          oPRINTPRETTYpo = false;
          *(stream) << "(" << tree->value << " " << tree->rest->value << " " << tree->rest->rest->value;
          oPRINTPRETTYpo = oPRINTPRETTYCODEpo;
          { Object* form = NULL;
            Cons* iter000 = tree->nthRest(3);

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              form = iter000->value;
              *(stream) << std::endl << "  " << form;
            }
          }
          *(stream) << ")";
        }
        else {
          *(stream) << tree;
        }
      }
    }
    else {
      *(stream) << tree;
    }
    *(stream) << std::endl;
  }
}

int treeSize(Object* self) {
  if (safePrimaryType(self) == SGT_CONSES_STELLA_CONS) {
    { Object* self000 = self;
      Cons* self = ((Cons*)(self000));

      if (self == NIL) {
        return (0);
      }
      else {
        return (1 + treeSize(self->value) + treeSize(self->rest));
      }
    }
  }
  else {
    return (0);
  }
}

DEFINE_STELLA_SPECIAL(oDEPTHEXCEEDEDpo, boolean , false);

int oDEPTHCUTOFFo = 33;

int safelyComputeTreeSize(Cons* tree, int depthcount, int cutoff) {
  { int count = 1;
    Object* value = NULL;

    if (depthcount > oDEPTHCUTOFFo) {
      oDEPTHEXCEEDEDpo = true;
      return (1);
    }
    for (;;) {
      value = tree->value;
      if (consP(value)) {
        count = count + safelyComputeTreeSize(((Cons*)(tree->value)), depthcount + 1, cutoff);
      }
      if ((!((boolean)(tree->rest))) ||
          ((tree->rest == NIL) ||
           (count > cutoff))) {
        return (count);
      }
      tree = tree->rest;
    }
  }
}

int safeTreeSize(Cons* tree, const char*& _Return1) {
  { 
    BIND_STELLA_SPECIAL(oDEPTHEXCEEDEDpo, boolean, false);
    { int cutoff = 99;
      int size = safelyComputeTreeSize(tree, 0, cutoff);

      { int _Return0 = size;

        _Return1 = ((oDEPTHEXCEEDEDpo ||
            (size >= cutoff)) ? "CIRCULAR" : "OK");
        return (_Return0);
      }
    }
  }
}

void helpStartupConses1() {
  {
    SGT_CONSES_STELLA_GENERALIZED_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("GENERALIZED-SYMBOL", NULL, 1)));
    SGT_CONSES_STELLA_MUTABLE_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("MUTABLE-STRING-WRAPPER", NULL, 1)));
    SGT_CONSES_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SYM_CONSES_STELLA_p = ((Symbol*)(internRigidSymbolWrtModule("?", NULL, 0)));
    SYM_CONSES_STELLA_ddd = ((Symbol*)(internRigidSymbolWrtModule("...", NULL, 0)));
    SYM_CONSES_STELLA_STARTUP_CONSES = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-CONSES", NULL, 0)));
    SYM_CONSES_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupConses2() {
  {
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF CONS)) :DOCUMENTATION \"Return `true' iff `self' equals `nil'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (EQ? SELF NIL)))", wrapMethodCode(((cpp_method_code)(&Cons::emptyP))), NULL);
    defineMethodObject("(DEFMETHOD (NON-EMPTY? BOOLEAN) ((SELF CONS)) :DOCUMENTATION \"Return `true' iff `self' is not equal to `nil'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (NOT (EQ? SELF NIL))))", wrapMethodCode(((cpp_method_code)(&Cons::nonEmptyP))), NULL);
    defineFunctionObject("NIL?", "(DEFUN (NIL? BOOLEAN) ((X OBJECT)) :DOCUMENTATION \"Return `true' iff `x' equals `nil'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (EQ? X NIL)))", ((cpp_function_code)(&nilP)), NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF CONS)) :DOCUMENTATION \"Return the length of the CONS list `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::length))), NULL);
    defineMethodObject("(DEFMETHOD (POSITION INTEGER) ((SELF CONS) (OBJECT OBJECT) (START INTEGER)) :DOCUMENTATION \"Return the position of `object' within the cons-list\n`self' (counting from zero); or return `null' if `object' does not occur within \n`self' (uses an `eql?' test).  If `start' was supplied as non-`null', only \nconsider the sublist starting at `start', however, the returned position \nwill always be relative to the entire list.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::position))), NULL);
    defineMethodObject("(DEFMETHOD (LAST-POSITION INTEGER) ((SELF CONS) (OBJECT OBJECT) (END INTEGER)) :DOCUMENTATION \"Return the position of `object' within the cons-list\n`self' (counting from zero); or return `null' if `object' does not occur within \n`self' (uses an `eql?' test).  If `start' was supplied as non-`null', only \nconsider the sublist ending at `end', however, the returned position \nwill always be relative to the entire list.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::lastPosition))), NULL);
    defineMethodObject("(DEFMETHOD (MEMBER? BOOLEAN) ((SELF CONS) (OBJECT OBJECT)) :DOCUMENTATION \"Return `true' iff `object' is a member of the cons list\n`self' (uses an `eql?' test).\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::memberP))), NULL);
    defineMethodObject("(DEFMETHOD (MEMB? BOOLEAN) ((SELF CONS) (OBJECT OBJECT)) :DOCUMENTATION \"Return `true' iff `object' is a member of the cons list\n`self' (uses an `eq?' test).\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::membP))), NULL);
    defineFunctionObject("CONS", "(DEFUN (CONS CONS) ((VALUE OBJECT) (REST CONS)) :DOCUMENTATION \"Return a cons record that points to `value' and `rest'.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&cons)), NULL);
    defineMethodObject("(DEFMETHOD (REMOVE (LIKE SELF)) ((SELF CONS) (VALUE OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Destructively remove all entries in the cons list `self' that\nmatch `value'.  Unless the remaining list is `nil', insure that the cons that\nheads the list is unchanged.\")", wrapMethodCode(((cpp_method_code)(&Cons::remove))), NULL);
    defineMethodObject("(DEFMETHOD (REMOVE-IF (LIKE SELF)) ((SELF CONS) (TEST? FUNCTION-CODE)) :PUBLIC? TRUE :DOCUMENTATION \"Destructively removes all members of the cons list\n`self' for which `test?' evaluates to `true'.  `test' takes a single \nargument of type OBJECT and returns `true' or `false'.  Returns a cons list.\nIn case the first element is removed, the return result should be\nassigned to a variable.\")", wrapMethodCode(((cpp_method_code)(&Cons::removeIf))), NULL);
    defineMethodObject("(DEFMETHOD (REMOVE-DUPLICATES (LIKE SELF)) ((SELF CONS)) :PUBLIC? TRUE :DOCUMENTATION \"Destructively remove duplicates from `self' and return the\nresult.  Removes all but the first occurrence of items in the list.\nPreserves the original order of the remaining members.  Runs in linear time.\")", wrapMethodCode(((cpp_method_code)(&Cons::removeDuplicates))), NULL);
    defineMethodObject("(DEFMETHOD (REMOVE-DUPLICATES-EQUAL (LIKE SELF)) ((SELF CONS)) :DOCUMENTATION \"`remove-duplicates' (which see) using an `equal?' test.\nIMPORTANT: since this uses hashing to speed things up, an `equal-hash-code'\nmethod needs to be defined for this to work.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::removeDuplicatesEqual))), NULL);
    defineFunctionObject("REMOVE-DUPLICATES-FROM-LONG-LIST", "(DEFUN (REMOVE-DUPLICATES-FROM-LONG-LIST (LIKE SELF)) ((SELF CONS) (EQUALTEST? BOOLEAN)))", ((cpp_function_code)(&removeDuplicatesFromLongList)), NULL);
    defineMethodObject("(DEFMETHOD (CONCATENATE CONS) ((LIST1 CONS) (LIST2 CONS) |&REST| (OTHERLISTS CONS)) :PUBLIC? TRUE :DOCUMENTATION \"Return a cons list consisting of the concatenation of \n`list1', `list2', and `otherLists'.  The operation is destructive wrt all\nbut the last list argument which is left intact.  The two mandatory\nparameters allow us to optimize the common binary case by not relying on\nthe somewhat less efficient variable arguments mechanism.\")", wrapMethodCode(((cpp_method_code)(&Cons::concatenate))), NULL);
    defineMethodObject("(DEFMETHOD (PREPEND CONS) ((SELF CONS) (LIST1 CONS)) :DOCUMENTATION \"Return a cons list consisting of the concatenation of\n`list1' and `self'.  A copy of `list1' is prepended to `self'.  This\noperation results in structure sharing of `self'; to avoid this, `self'\nshould not be pointed to by anything other than the tail of the prepended\ncopy.\")", wrapMethodCode(((cpp_method_code)(&Cons::prepend))), NULL);
    defineMethodObject("(DEFMETHOD (REVERSE (LIKE SELF)) ((SELF CONS)) :DOCUMENTATION \"Destructively reverse the members of the cons list `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::reverse))), NULL);
    defineMethodObject("(DEFMETHOD (SUBSTITUTE CONS) ((SELF CONS) (INVALUE OBJECT) (OUTVALUE OBJECT)) :DOCUMENTATION \"Destructively replace each appearance of `outValue' by\n`inValue' in the cons list `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::substitute))), NULL);
    defineFunctionObject("MAP-NULL-TO-NIL", "(DEFUN (MAP-NULL-TO-NIL (LIKE SELF)) ((SELF CONS)) :DOCUMENTATION \"Return `nil' iff `self' is `null' or `self' otherwise.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (CHOOSE (NULL? SELF) NIL SELF)))", ((cpp_function_code)(&mapNullToNil)), NULL);
    defineMethodObject("(DEFMETHOD (FIRST (LIKE (ANY-VALUE SELF))) ((SELF CONS)) :DOCUMENTATION \"Return the first element of `self'.  The first element\nof `self' can be set with `setf'.  Note that '(first NIL)' = `null'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VALUE SELF)))", wrapMethodCode(((cpp_method_code)(&Cons::first))), NULL);
    defineMethodObject("(DEFMETHOD (SECOND (LIKE (ANY-VALUE SELF))) ((SELF CONS)) :DOCUMENTATION \"Return the second element of `self'.  The second element\nof `self' can be set with `setf'.  Note that '(second NIL)' = `null'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VALUE (REST SELF))))", wrapMethodCode(((cpp_method_code)(&Cons::second))), NULL);
    defineMethodObject("(DEFMETHOD (THIRD (LIKE (ANY-VALUE SELF))) ((SELF CONS)) :DOCUMENTATION \"Return the third element of `self'.  The third element\nof `self' can be set with `setf'.  Note that '(third NIL)' = `null'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VALUE (REST (REST SELF)))))", wrapMethodCode(((cpp_method_code)(&Cons::third))), NULL);
    defineMethodObject("(DEFMETHOD (FOURTH (LIKE (ANY-VALUE SELF))) ((SELF CONS)) :DOCUMENTATION \"Return the fourth element of `self'.  The fourth element\nof `self' can be set with `setf'.  Note that '(fourth NIL)' = `null'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::fourth))), NULL);
    defineMethodObject("(DEFMETHOD (FIFTH (LIKE (ANY-VALUE SELF))) ((SELF CONS)) :DOCUMENTATION \"Return the fifth element of `self'.  The fifth element\nof `self' can be set with `setf'.  Note, that '(fifth NIL)' = `null'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::fifth))), NULL);
    defineMethodObject("(DEFMETHOD (NTH (LIKE (ANY-VALUE SELF))) ((SELF CONS) (POSITION INTEGER)) :DOCUMENTATION \"Return the element of `self' at `position'.  The nth element\nof `self' can be set with `setf'.  Note, that '(nth NIL <pos>)' = `null'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::nth))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-REST (LIKE SELF)) ((SELF CONS) (POSITION INTEGER)) :DOCUMENTATION \"Apply `rest' `position' times to `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::nthRest))), NULL);
    defineFunctionObject("LAST-CONS", "(DEFUN (LAST-CONS (CONS OF (LIKE (ANY-VALUE SELF)))) ((SELF CONS)) :DOCUMENTATION \"Return the last cons of `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lastCons)), NULL);
    defineMethodObject("(DEFMETHOD (LAST (LIKE (ANY-VALUE SELF))) ((SELF CONS)) :DOCUMENTATION \"Return the last element of `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::last))), NULL);
    defineMethodObject("(DEFMETHOD (FIRST-SETTER (LIKE (ANY-VALUE SELF))) ((SELF CONS) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::firstSetter))), NULL);
    defineMethodObject("(DEFMETHOD (SECOND-SETTER (LIKE (ANY-VALUE SELF))) ((SELF CONS) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::secondSetter))), NULL);
    defineMethodObject("(DEFMETHOD (THIRD-SETTER (LIKE (ANY-VALUE SELF))) ((SELF CONS) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::thirdSetter))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-SETTER (LIKE (ANY-VALUE SELF))) ((SELF CONS) (VALUE (LIKE (ANY-VALUE SELF))) (POSITION INTEGER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::nthSetter))), NULL);
    defineMethodObject("(DEFMETHOD (FOURTH-SETTER (LIKE (ANY-VALUE SELF))) ((SELF CONS) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::fourthSetter))), NULL);
    defineMethodObject("(DEFMETHOD (FIFTH-SETTER (LIKE (ANY-VALUE SELF))) ((SELF CONS) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::fifthSetter))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-REST-SETTER OBJECT) ((SELF CONS) (VALUE OBJECT) (POSITION INTEGER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::nthRestSetter))), NULL);
    defineMethodObject("(DEFMETHOD (ALLOCATE-ITERATOR (CONS-ITERATOR OF (LIKE (ANY-VALUE SELF)))) ((SELF CONS)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::allocateIterator))), NULL);
    defineFunctionObject("TERMINATE-CONS-ITERATOR?", "(DEFUN (TERMINATE-CONS-ITERATOR? BOOLEAN) ((SELF CONS-ITERATOR)) :PUBLIC? TRUE)", ((cpp_function_code)(&terminateConsIteratorP)), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF CONS-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ConsIterator::nextP))), NULL);
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF CONS-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ConsIterator::emptyP))), NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF CONS-ITERATOR)) :DOCUMENTATION \"Iterate over 'self', and count how many items there are.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ConsIterator::length))), NULL);
    defineMethodObject("(DEFMETHOD (MEMBER? BOOLEAN) ((SELF CONS-ITERATOR) (VALUE OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Iterate over values of `self' and return TRUE\nif one of them is `eql?' to 'value.\")", wrapMethodCode(((cpp_method_code)(&ConsIterator::memberP))), NULL);
    defineMethodObject("(DEFMETHOD (VALUE-SETTER OBJECT) ((SELF CONS-ITERATOR) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ConsIterator::valueSetter))), NULL);
    defineFunctionObject("ADD-CONS-TO-END-OF-CONS-LIST", "(DEFUN ADD-CONS-TO-END-OF-CONS-LIST ((SELF CONS) (LASTCONS CONS)) :PUBLIC? TRUE)", ((cpp_function_code)(&addConsToEndOfConsList)), NULL);
    defineFunctionObject("BUT-LAST-NEXT?", "(DEFUN (BUT-LAST-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)) :PUBLIC? TRUE)", ((cpp_function_code)(&butLastNextP)), NULL);
    defineMethodObject("(DEFMETHOD (BUT-LAST (ITERATOR OF (LIKE (ANY-VALUE SELF)))) ((SELF CONS)) :DOCUMENTATION \"Generate all but the last element of the cons list `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::butLast))), NULL);
    defineMethodObject("(DEFMETHOD (CONSIFY (CONS OF (LIKE (ANY-VALUE SELF)))) ((SELF CONS)) :DOCUMENTATION \"Return `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::consify))), NULL);
    defineMethodObject("(DEFMETHOD (CONSIFY (CONS OF (LIKE (ANY-VALUE SELF)))) ((SELF LIST)) :DOCUMENTATION \"Return a list of elements in `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::consify))), NULL);
    defineMethodObject("(DEFMETHOD (CONSIFY (CONS OF (LIKE (ANY-VALUE SELF)))) ((SELF KEY-VALUE-LIST)) :DOCUMENTATION \"Return a list of key-value pairs in `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueList::consify))), NULL);
    defineMethodObject("(DEFMETHOD (CONSIFY (CONS OF (LIKE (ANY-VALUE SELF)))) ((SELF VECTOR)) :DOCUMENTATION \"Return a list of elements in `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Vector::consify))), NULL);
    defineMethodObject("(DEFMETHOD (CONSIFY (CONS OF (LIKE (ANY-VALUE SELF)))) ((SELF ITERATOR)) :DOCUMENTATION \"Return a list of elements generated by `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Iterator::consify))), NULL);
    defineMethodObject("(DEFMETHOD (CONSIFY CONS) ((SELF OBJECT)) :DOCUMENTATION \"If `object' is a CONS, return it.  Otherwise, return\na singleton cons list containing it.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Object::consify))), NULL);
    defineMethodObject("(DEFMETHOD (REMOVE-DELETED-MEMBERS (LIKE SELF)) ((SELF CONS)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::removeDeletedMembers))), NULL);
    defineFunctionObject("COPY-CONS-LIST", "(DEFUN (COPY-CONS-LIST (LIKE SELF)) ((SELF CONS)) :DOCUMENTATION \"Return a copy of the cons list `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&copyConsList)), NULL);
    defineFunctionObject("CONS-LIST", "(DEFUN (CONS-LIST CONS) (|&REST| (VALUES OBJECT)) :DOCUMENTATION \"Return a cons list containing `values', in order.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&consList)), NULL);
    defineFunctionObject("MAKE-CONS-LIST", "(DEFUN (MAKE-CONS-LIST CONS) ((SIZE INTEGER)) :DOCUMENTATION \"Return a cons list of length 'size' initialized with NULL values.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&makeConsList)), NULL);
    defineFunctionObject("CONS-SET-FIRST-GET-NEXT", "(DEFUN (CONS-SET-FIRST-GET-NEXT CONS) ((LIST CONS) (VALUE OBJECT)) :DOCUMENTATION \"Set the first element of 'list' to value and return the rest of 'list'.\nThis is primarily a utility for the Python API to construct CONS-lists.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&consSetFirstGetNext)), NULL);
    defineFunctionObject("LIST*", "(DEFUN (LIST* CONS) (|&REST| (VALUES OBJECT)) :DOCUMENTATION \"Return a list of conses that make up the list `values',\nterminated by the last value rather than by `nil'.  Assumes that\nat least one value is passed in.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&listO)), NULL);
    defineFunctionObject("APPEND", "(DEFUN (APPEND CONS) ((CONSLIST1 CONS) (CONSLIST2 CONS)) :DOCUMENTATION \"Return a cons list representing the concatenation\nof `consList1' and `consList2'.  The concatenation is NOT destructive.\" :PUBLIC? TRUE)", ((cpp_function_code)(&append)), NULL);
    defineMethodObject("(DEFMETHOD (SUBSET? BOOLEAN) ((SELF CONS) (OTHERLIST CONS)) :DOCUMENTATION \"Return true if every element of `self' also occurs in `otherList'.\nUses an `eql?' test and a simple quadratic-time algorithm.  Note that\nthis does not check whether `self' and `otherList' actually are sets.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::subsetP))), NULL);
    defineMethodObject("(DEFMETHOD (EQUIVALENT-SETS? BOOLEAN) ((SELF CONS) (OTHERLIST CONS)) :DOCUMENTATION \"Return true if every element of `self' occurs in `otherList' and vice versa.\nUses an `eql?' test and a simple quadratic-time algorithm.  Note that\nthis does not check whether `self' and `otherList' actually are sets.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::equivalentSetsP))), NULL);
  }
}

void startupConses() {
  if (currentStartupTimePhaseP(0)) {
    if (!(((boolean)(NIL)))) {
      NIL = new Cons();
      NIL->value = NULL;
      NIL->rest = NIL;
    }
  }
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupConses1();
    }
    if (currentStartupTimePhaseP(4)) {
      oPRINTLENGTHo = NULL_INTEGER;
      ELLIPSIS = SYM_CONSES_STELLA_ddd;
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupConses2();
      defineMethodObject("(DEFMETHOD (DISJOINT-SETS? BOOLEAN) ((SELF CONS) (OTHERLIST CONS)) :DOCUMENTATION \"Return true if the intersection of `self' and `otherList' is empty.\nThis is always true if at least one of the two sets is the empty set.\nUses an `eql?' test and a simple quadratic-time algorithm.  Note that\nthis does not check whether `self' and `otherList' actually are sets.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::disjointSetsP))), NULL);
      defineMethodObject("(DEFMETHOD (INTERSECTION CONS) ((SELF CONS) (OTHERLIST CONS)) :DOCUMENTATION \"Return the set intersection of `self' and `otherList'.  Uses an `eql?'\ntest and a simple quadratic-time algorithm.  Note that the result is only\nguaranteed to be a set if both `self' and `otherList' are sets.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::intersection))), NULL);
      defineMethodObject("(DEFMETHOD (UNION CONS) ((SELF CONS) (OTHERLIST CONS)) :DOCUMENTATION \"Return the set union of `self' and `otherList'.  Uses an `eql?' test\nand a simple quadratic-time algorithm.  Note that the result is only\nguaranteed to be a set if both `self' and `otherList' are sets.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::unioN))), NULL);
      defineMethodObject("(DEFMETHOD (DIFFERENCE CONS) ((SELF CONS) (OTHERLIST CONS)) :DOCUMENTATION \"Return the set difference of `self' and `otherList' (i.e., all elements\nthat are in `self' but not in `otherSet').  Uses an `eql?' test and a simple\nquadratic-time algorithm.  Note that the result is only guaranteed to be a\nset if both `self' and `otherList' are sets.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::difference))), NULL);
      defineMethodObject("(DEFMETHOD (SUBTRACT CONS) ((SELF CONS) (OTHERLIST CONS)) :DOCUMENTATION \"Return the set difference of `self' and `otherList' by destructively\nremoving elements from `self' that also occur in `otherList'.  Uses an `eql?'\ntest and a simple quadratic-time algorithm.  Note that the result is only\nguaranteed to be a set if `self' is a set.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::subtract))), NULL);
      defineMethodObject("(DEFMETHOD (SORT (CONS OF (LIKE (ANY-VALUE SELF)))) ((SELF CONS) (PREDICATE FUNCTION-CODE)) :PUBLIC? TRUE :DOCUMENTATION \"Perform a stable, destructive sort of `self' according to\n`predicate', and return the result.  If `predicate' has a '<' semantics, the\nresult will be in ascending order.  It is not guaranteed that `self' will\npoint to the beginning of the sorted result.  If `predicate' is `null', a\nsuitable '<' predicate is chosen depending on the first element of `self',\nand it is assumed that all elements of `self' have the same type (supported\nelement types are GENERALIZED-SYMBOL, STRING, INTEGER, and FLOAT).\")", wrapMethodCode(((cpp_method_code)(&Cons::sort))), NULL);
      defineFunctionObject("HELP-SORT-CONS-LIST", "(DEFUN (HELP-SORT-CONS-LIST CONS) ((LIST CONS) (LENGTH INTEGER) (PREDICATE FUNCTION-CODE)))", ((cpp_function_code)(&helpSortConsList)), NULL);
      defineFunctionObject("MERGE-CONS-LISTS", "(DEFUN (MERGE-CONS-LISTS CONS) ((LIST1 CONS) (LIST2 CONS) (PREDICATE FUNCTION-CODE)))", ((cpp_function_code)(&mergeConsLists)), NULL);
      defineFunctionObject("GENERALIZED-SYMBOL-LESS-THAN?", "(DEFUN (GENERALIZED-SYMBOL-LESS-THAN? BOOLEAN) ((X GENERALIZED-SYMBOL) (Y GENERALIZED-SYMBOL)) :PUBLIC? TRUE)", ((cpp_function_code)(&generalizedSymbolLessThanP)), NULL);
      defineFunctionObject("WRAPPED-INTEGER-LESS-THAN?", "(DEFUN (WRAPPED-INTEGER-LESS-THAN? BOOLEAN) ((X INTEGER-WRAPPER) (Y INTEGER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&wrappedIntegerLessThanP)), NULL);
      defineFunctionObject("WRAPPED-LONG-INTEGER-LESS-THAN?", "(DEFUN (WRAPPED-LONG-INTEGER-LESS-THAN? BOOLEAN) ((X LONG-INTEGER-WRAPPER) (Y LONG-INTEGER-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&wrappedLongIntegerLessThanP)), NULL);
      defineFunctionObject("WRAPPED-FLOAT-LESS-THAN?", "(DEFUN (WRAPPED-FLOAT-LESS-THAN? BOOLEAN) ((X FLOAT-WRAPPER) (Y FLOAT-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&wrappedFloatLessThanP)), NULL);
      defineFunctionObject("WRAPPED-STRING-LESS-THAN?", "(DEFUN (WRAPPED-STRING-LESS-THAN? BOOLEAN) ((X STRING-WRAPPER) (Y STRING-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&wrappedStringLessThanP)), NULL);
      defineFunctionObject("WRAPPED-MUTABLE-STRING-LESS-THAN?", "(DEFUN (WRAPPED-MUTABLE-STRING-LESS-THAN? BOOLEAN) ((X MUTABLE-STRING-WRAPPER) (Y MUTABLE-STRING-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&wrappedMutableStringLessThanP)), NULL);
      defineFunctionObject("NUMBER-LESS-THAN?", "(DEFUN (NUMBER-LESS-THAN? BOOLEAN) ((X NUMBER-WRAPPER) (Y NUMBER-WRAPPER)) :DOCUMENTATION \"Generic number comparison that works with integers, longs and floats.\" :PUBLIC? TRUE)", ((cpp_function_code)(((boolean  (*) (NumberWrapper*, NumberWrapper*))(&numberLessThanP)))), NULL);
      defineFunctionObject("CHOOSE-SORT-PREDICATE", "(DEFUN (CHOOSE-SORT-PREDICATE FUNCTION-CODE) ((FIRSTELEMENT OBJECT)))", ((cpp_function_code)(&chooseSortPredicate)), NULL);
      defineFunctionObject("SORT-TUPLE-COMPARE?", "(DEFUN (SORT-TUPLE-COMPARE? BOOLEAN) ((X CONS) (Y CONS)))", ((cpp_function_code)(&sortTupleCompareP)), NULL);
      defineMethodObject("(DEFMETHOD (SORT-TUPLES (CONS OF (LIKE (ANY-VALUE SELF)))) ((SELF CONS) (N INTEGER) (PREDICATE FUNCTION-CODE)) :PUBLIC? TRUE :DOCUMENTATION \"Just like `sort' but assumes each element of `self' is a tuple (a cons)\nwhose `n'-th element (0-based) will be used for comparison.\")", wrapMethodCode(((cpp_method_code)(&Cons::sortTuples))), NULL);
      defineFunctionObject("SORT-OBJECTS-COMPARE?", "(DEFUN (SORT-OBJECTS-COMPARE? BOOLEAN) ((X OBJECT) (Y OBJECT)))", ((cpp_function_code)(&sortObjectsCompareP)), NULL);
      defineMethodObject("(DEFMETHOD (SORT-OBJECTS (CONS OF (LIKE (ANY-VALUE SELF)))) ((SELF CONS) (SLOT STORAGE-SLOT) (PREDICATE FUNCTION-CODE)) :DOCUMENTATION \"Just like `sort' but assumes each element of `self' has a `slot'\nwhose value will be used for comparison.  Elements must be descendants of\nSTANDARD OBJECT.  Note that while this will work with literal-valued slots,\nit will cause value wrapping everytime `slot' is read.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::sortObjects))), NULL);
      defineFunctionObject("SEARCH-CONS-TREE?", "(DEFUN (SEARCH-CONS-TREE? BOOLEAN) ((TREE OBJECT) (VALUE OBJECT)) :DOCUMENTATION \"Return `true' iff the value `value' is embedded within\nthe cons tree `tree'.  Uses an `eql?' test.\" :PUBLIC? TRUE)", ((cpp_function_code)(&searchConsTreeP)), NULL);
      defineFunctionObject("SEARCH-CONS-TREE-WITH-FILTER?", "(DEFUN (SEARCH-CONS-TREE-WITH-FILTER? BOOLEAN) ((TREE OBJECT) (VALUE OBJECT) (FILTER CONS)) :DOCUMENTATION \"Return `true' iff the value `value' is embedded within\nthe cons tree `tree'.  Uses an `eql?' test.  Does not descend into any\ncons whose first element matches an element of `filter'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&searchConsTreeWithFilterP)), NULL);
      defineFunctionObject("COPY-CONS-TREE", "(DEFUN (COPY-CONS-TREE (LIKE SELF)) ((SELF OBJECT)) :DOCUMENTATION \"Return a copy of the cons tree `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&copyConsTree)), NULL);
      defineFunctionObject("EQUAL-CONS-TREES?", "(DEFUN (EQUAL-CONS-TREES? BOOLEAN) ((TREE1 OBJECT) (TREE2 OBJECT)) :DOCUMENTATION \"Return `true' iff the cons trees `tree1' and `tree2' are\nstructurally equivalent.  Uses an `eql?' test.\" :PUBLIC? TRUE)", ((cpp_function_code)(&equalConsTreesP)), NULL);
      defineMethodObject("(DEFMETHOD (OBJECT-EQUAL? BOOLEAN) ((TREE1 CONS) (TREE2 OBJECT)) :DOCUMENTATION \"Return `true' iff the cons trees `tree1' and `tree2' are\nstructurally equivalent.  Uses `equal?' to test equality of subtrees.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::objectEqualP))), NULL);
      defineMethodObject("(DEFMETHOD (EQUAL-HASH-CODE INTEGER) ((SELF CONS)) :DOCUMENTATION \"Return an `equal?' hash code for `self'.  Note that this\nis O(N) in the number of elements of `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::equalHashCode))), NULL);
      defineFunctionObject("SUBSTITUTE-CONS-TREE", "(DEFUN (SUBSTITUTE-CONS-TREE OBJECT) ((TREE OBJECT) (NEWVALUE OBJECT) (OLDVALUE OBJECT)) :DOCUMENTATION \"Destructively replace each appearance of `oldValue' by\n`newValue' in the cons tree `tree'.  Return the tree.  Uses an `eql?' test.\" :PUBLIC? TRUE)", ((cpp_function_code)(&substituteConsTree)), NULL);
      defineFunctionObject("CONS-TREE-NTH", "(DEFUN (CONS-TREE-NTH OBJECT) ((TREE CONS) |&REST| (INDEX INTEGER)) :DOCUMENTATION \"Access an arbitrary element of `tree' identified by a path\nspecified as a list of `index' values.  The first `index' specifies the\n`index'-th element of `tree', the second `index' the `index'-th subelement\nof that element, etc.  Example:\n	 \n  (cons-tree-nth (quote (a (b (c d e) f) g)) 1 1 2) => e\n	\n\" :PUBLIC? TRUE)", ((cpp_function_code)(&consTreeNth)), NULL);
      defineFunctionObject("CONS-TREE-NTH-REST", "(DEFUN (CONS-TREE-NTH-REST CONS) ((TREE CONS) |&REST| (INDEX INTEGER)) :DOCUMENTATION \"Access an arbitrary sublist of `tree' identified by a path\nspecified as a list of `index' values.  The first `index' specifies the\n`index'-th element of `tree', the second `index' the `index'-th subelement\nof that element, ..., the last index specifies the `nth-rest' of the previous\nelement (different from `cons-tree-nth').  Example:\n	 \n  (cons-tree-nth-rest (quote (a (b (c d e) f) g)) 1 1 1) => (d e)\n	\n\" :PUBLIC? TRUE)", ((cpp_function_code)(&consTreeNthRest)), NULL);
      defineFunctionObject("MATCH-CONS-TREE", "(DEFUN (MATCH-CONS-TREE KEY-VALUE-LIST) ((TREE OBJECT) (PATTERN OBJECT) (BINDINGS KEY-VALUE-LIST)) :DOCUMENTATION \"Match `pattern' against `tree' and return a list of\nvariable bindings if they match, or NULL otherwise.  `bindings' can\nbe NULL or an initial list of bindings to consider.  Pattern variables\nuse KIF syntax, i.e., they need to start with a `?' character.  A\nsingle question mark is interpreted as the anonymous variable. Example:\n	 \n  (match-cons-tree (quote (a (b (a d) e) (a d) f g))\n                   (quote (a (?x ?y ?) ?y ? g))\n                   NULL)\n  => |kv|(<?Y,(A D)> <?X,B>)\n	\nVariables can't be quoted but quoting can effectively be achieved by\ninserting to-be-quoted variables bound to themselves into `bindings'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&matchConsTree)), NULL);
      defineFunctionObject("CONS-TREE-MATCH?", "(DEFUN (CONS-TREE-MATCH? BOOLEAN) ((TREE OBJECT) (PATTERN OBJECT)) :DOCUMENTATION \"Predicate version of `match-cons-tree' (which see).\" :PUBLIC? TRUE)", ((cpp_function_code)(&consTreeMatchP)), NULL);
      defineFunctionObject("PRINT-CONS", "(DEFUN PRINT-CONS ((TREE CONS) (STREAM NATIVE-OUTPUT-STREAM) (LPAREN STRING) (RPAREN STRING)))", ((cpp_function_code)(&printCons)), NULL);
      defineFunctionObject("PPRINT-CONS", "(DEFUN PPRINT-CONS ((TREE CONS) (STREAM NATIVE-OUTPUT-STREAM) (LPAREN STRING) (RPAREN STRING)))", ((cpp_function_code)(&pprintCons)), NULL);
      defineFunctionObject("PRINT-STELLA-CODE", "(DEFUN PRINT-STELLA-CODE ((TREE OBJECT) (STREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&printStellaCode)), NULL);
      defineFunctionObject("PRINT-STELLA-DEFINITION", "(DEFUN PRINT-STELLA-DEFINITION ((TREE OBJECT) (STREAM NATIVE-OUTPUT-STREAM)) :PUBLIC? TRUE)", ((cpp_function_code)(&printStellaDefinition)), NULL);
      defineFunctionObject("TREE-SIZE", "(DEFUN (TREE-SIZE INTEGER) ((SELF OBJECT)))", ((cpp_function_code)(&treeSize)), NULL);
      defineFunctionObject("SAFELY-COMPUTE-TREE-SIZE", "(DEFUN (SAFELY-COMPUTE-TREE-SIZE INTEGER) ((TREE CONS) (DEPTHCOUNT INTEGER) (CUTOFF INTEGER)))", ((cpp_function_code)(&safelyComputeTreeSize)), NULL);
      defineFunctionObject("SAFE-TREE-SIZE", "(DEFUN (SAFE-TREE-SIZE INTEGER STRING) ((TREE CONS)))", ((cpp_function_code)(&safeTreeSize)), NULL);
      defineFunctionObject("STARTUP-CONSES", "(DEFUN STARTUP-CONSES () :PUBLIC? TRUE)", ((cpp_function_code)(&startupConses)), NULL);
      { MethodSlot* function = lookupFunction(SYM_CONSES_STELLA_STARTUP_CONSES);

        setDynamicSlotValue(function->dynamicSlots, SYM_CONSES_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupConses"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL NIL CONS NULL :PUBLIC? TRUE)", &NIL);
      defineGlobalVariableObject("(DEFGLOBAL *REMOVE-DUPLICATES-CROSSOVER-POINT* INTEGER 20 :DOCUMENTATION \"Point where we switch from using a quadratic remove\nduplicates algorithm to a linear one using a hash table.  For\nan unoptimized Common Lisp, 20 is a good crossover point.\")", &oREMOVE_DUPLICATES_CROSSOVER_POINTo);
      defineGlobalVariableObject("(DEFSPECIAL *SORT-TUPLE-COMPARE-PREDICATE* FUNCTION-CODE NULL)", &oSORT_TUPLE_COMPARE_PREDICATEo);
      defineGlobalVariableObject("(DEFSPECIAL *SORT-TUPLE-COMPARE-INDEX* INTEGER 0)", &oSORT_TUPLE_COMPARE_INDEXo);
      defineGlobalVariableObject("(DEFSPECIAL *SORT-OBJECTS-COMPARE-SLOT* STORAGE-SLOT NULL)", &oSORT_OBJECTS_COMPARE_SLOTo);
      defineGlobalVariableObject("(DEFSPECIAL *PRINTPRETTY?* BOOLEAN TRUE :DOCUMENTATION \"If `true' conses will be pretty printed.\" :PUBLIC? TRUE)", &oPRINTPRETTYpo);
      defineGlobalVariableObject("(DEFSPECIAL *PRINTREADABLY?* BOOLEAN FALSE :DOCUMENTATION \"If `true' conses will be printed as readable Stella code.\" :PUBLIC? TRUE)", &oPRINTREADABLYpo);
      defineGlobalVariableObject("(DEFSPECIAL *PRINTLENGTH* INTEGER NULL :DOCUMENTATION \"If non-NULL list-like data structures will print at most\nthat many elements.\" :PUBLIC? TRUE)", &oPRINTLENGTHo);
      defineGlobalVariableObject("(DEFGLOBAL ELLIPSIS SYMBOL (QUOTE ...) :DOCUMENTATION \"Generates an ellipsis '...' when found in a\npretty-printed parse tree.\" :PUBLIC? TRUE)", &ELLIPSIS);
      defineGlobalVariableObject("(DEFSPECIAL *PRINTPRETTYCODE?* BOOLEAN TRUE :DOCUMENTATION \"When `true' pretty-print Stella and translated code.\nSince (Lisp) pretty-printing is somewhat slow, turning this off speeds up\nfile translation, but it also makes translated output very unreadable.\" :PUBLIC? TRUE)", &oPRINTPRETTYCODEpo);
      defineGlobalVariableObject("(DEFSPECIAL *DEPTHEXCEEDED?* BOOLEAN FALSE)", &oDEPTHEXCEEDEDpo);
      defineGlobalVariableObject("(DEFGLOBAL *DEPTHCUTOFF* INTEGER 33)", &oDEPTHCUTOFFo);
    }
  }
}

Surrogate* SGT_CONSES_STELLA_GENERALIZED_SYMBOL = NULL;

Surrogate* SGT_CONSES_STELLA_MUTABLE_STRING_WRAPPER = NULL;

Surrogate* SGT_CONSES_STELLA_CONS = NULL;

Symbol* SYM_CONSES_STELLA_p = NULL;

Symbol* SYM_CONSES_STELLA_ddd = NULL;

Symbol* SYM_CONSES_STELLA_STARTUP_CONSES = NULL;

Symbol* SYM_CONSES_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
