//  -*- Mode: C++ -*-

// lists.cc

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

List* NIL_LIST = NULL;

boolean definedListP(List* self) {
  // Return TRUE unless `self' is NULL or the `NIL-LIST'.
  return ((!(self == NIL_LIST)) &&
      ((boolean)(self)));
}

boolean nullListP(List* self) {
  // Return TRUE iff `self' is NULL or the `NIL-LIST'.
  return ((self == NIL_LIST) ||
      (!((boolean)(self))));
}

boolean List::emptyP() {
  // Return TRUE if the list `self' has no members.
  { List* self = this;

    return (self->theConsList == NIL);
  }
}

boolean List::nonEmptyP() {
  // Return TRUE if the list `self' has at least one member.
  { List* self = this;

    return (!(self->theConsList == NIL));
  }
}

boolean terminateListP(List* self) {
  if (self == NIL_LIST) {
    if (!(!(self == NIL_LIST))) {
      std::cerr << "Safety violation: " << "Attempt to free NIL-LIST.";
    }
    return (false);
  }
  { Cons* cons = self->theConsList;
    Cons* rest = NULL;

    while (!(cons == NIL)) {
      rest = cons->rest;
      cons->free();
      cons = rest;
    }
    self->theConsList = NIL;
    return (true);
  }
}

boolean List::memberP(Object* object) {
  // Return TRUE iff `object' is a member of the list
  // `self' (uses an `eql?' test).
  { List* self = this;

    { Object* i = NULL;
      Cons* iter000 = self->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        i = iter000->value;
        if (eqlP(i, object)) {
          return (true);
        }
      }
    }
    return (false);
  }
}

boolean List::membP(Object* object) {
  // Return TRUE iff `object' is a member of the cons list
  // `self' (uses an 'eq?' test).
  { List* self = this;

    { Object* i = NULL;
      Cons* iter000 = self->theConsList;

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

Object* List::first() {
  // Return the first item in the list `self', or NULL if empty.
  { List* self = this;

    { Cons* cons = self->theConsList;

      return (((!(cons == NIL)) ? cons->value : NULL));
    }
  }
}

Object* List::second() {
  // Return the second item in the list `self', or NULL if empty.
  { List* self = this;

    return (self->theConsList->rest->value);
  }
}

Object* List::third() {
  // Return the third item in the list `self', or NULL if empty.
  { List* self = this;

    return (self->theConsList->rest->rest->value);
  }
}

Object* List::fourth() {
  // Return the fourth item in the list `self', or NULL if empty.
  { List* self = this;

    return (self->theConsList->fourth());
  }
}

Object* List::fifth() {
  // Return the fifth item in the list `self', or NULL if empty.
  { List* self = this;

    return (self->theConsList->fifth());
  }
}

Object* List::nth(int position) {
  // Return the nth item in the list `self', or NULL if empty.
  { List* self = this;

    return (self->theConsList->nth(position));
  }
}

Object* List::last() {
  // Return the last element of `self'.
  { List* self = this;

    return (self->theConsList->last());
  }
}

Cons* List::rest() {
  // Return a cons list of all but the first item in the list `self'.
  { List* self = this;

    return (self->theConsList->rest);
  }
}

Object* List::firstSetter(Object* value) {
  { List* self = this;

    return (self->theConsList->firstSetter(value));
  }
}

Object* List::secondSetter(Object* value) {
  { List* self = this;

    return (self->theConsList->secondSetter(value));
  }
}

Object* List::thirdSetter(Object* value) {
  { List* self = this;

    return (self->theConsList->thirdSetter(value));
  }
}

Object* List::fourthSetter(Object* value) {
  { List* self = this;

    return (self->theConsList->fourthSetter(value));
  }
}

Object* List::fifthSetter(Object* value) {
  { List* self = this;

    return (self->theConsList->fifthSetter(value));
  }
}

Object* List::nthSetter(Object* value, int position) {
  { List* self = this;

    return (self->theConsList->nthSetter(value, position));
  }
}

int List::length() {
  { List* self = this;

    // inline method
    return (self->theConsList->length());
  }
}

int List::position(Object* object, int start) {
  // Return the position of `object' within the list
  // `self' (counting from zero); or return NULL if `object' does not occur within 
  // `self' (uses an `eql?' test).  If `start' was supplied as non-NULL, only 
  // consider the sublist starting at `start', however, the returned position 
  // will always be relative to the entire list.
  { List* self = this;

    return (self->theConsList->position(object, start));
  }
}

int List::lastPosition(Object* object, int end) {
  // Return the position of `object' within the list
  // `self' (counting from zero); or return NULL if `object' does not occur within 
  // `self' (uses an `eql?' test).  If `end' was supplied as non-NULL, only 
  // consider the sublist ending at `end', however, the returned position 
  // will always be relative to the entire list.
  { List* self = this;

    return (self->theConsList->lastPosition(object, end));
  }
}

void List::insert(Object* value) {
  // Add `value' to the front of the list `self'.
  { List* self = this;

    if (!(!(self == NIL_LIST))) {
      std::cerr << "Safety violation: " << "Attempt to insert into NIL-LIST.";
    }
    self->theConsList = cons(value, self->theConsList);
  }
}

void List::push(Object* value) {
  // Add `value' to the front of the list `self'.
  { List* self = this;

    if (!(!(self == NIL_LIST))) {
      std::cerr << "Safety violation: " << "Attempt to insert into NIL-LIST.";
    }
    self->theConsList = cons(value, self->theConsList);
  }
}

void List::insertNew(Object* value) {
  // Add `value' to the front of the list `self' unless its 
  // already a member.
  { List* self = this;

    if (!(!(self == NIL_LIST))) {
      std::cerr << "Safety violation: " << "Attempt to insert into NIL-LIST.";
    }
    if (!self->theConsList->memberP(value)) {
      self->theConsList = cons(value, self->theConsList);
    }
  }
}

void List::insertLast(Object* value) {
  // Insert `value' as the last entry in the list `self'.
  { List* self = this;

    if (!(!(self == NIL_LIST))) {
      std::cerr << "Safety violation: " << "Attempt to insert into NIL-LIST.";
    }
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

AbstractCollection* List::remove(Object* value) {
  // Destructively remove all entries in `self' that match `value'.
  { List* self = this;

    self->theConsList = self->theConsList->remove(value);
    return (self);
  }
}

List* List::removeIf(cpp_function_code testP) {
  // Destructively remove all members of the list `self' for which
  // 'test?' evaluates to TRUE.  `test' takes a single argument of type OBJECT and
  // returns TRUE or FALSE.  Returns `self'.
  { List* self = this;

    self->theConsList = self->theConsList->removeIf(testP);
    return (self);
  }
}

Collection* List::removeDuplicates() {
  // Destructively remove duplicates from `self' and return the result.
  // Preserves the original order of the remaining members.
  { List* self = this;

    if (!(self->theConsList == NIL)) {
      self->theConsList = self->theConsList->removeDuplicates();
    }
    return (self);
  }
}

List* List::removeDuplicatesEqual() {
  // `remove-duplicates' (which see) using an `equal?' test.
  { List* self = this;

    if (!(self->theConsList == NIL)) {
      self->theConsList = self->theConsList->removeDuplicatesEqual();
    }
    return (self);
  }
}

Object* List::pop() {
  // Remove and return the first element in the list `self'.
  // Return NULL if the list is empty.
  { List* self = this;

    { Cons* cons = self->theConsList;
      Object* value = NULL;

      if (cons == NIL) {
        return (NULL);
      }
      value = cons->value;
      self->theConsList = cons->rest;
      return (value);
    }
  }
}

List* List::reverse() {
  // Reverse the members of `self' (in place).
  { List* self = this;

    self->theConsList = self->theConsList->reverse();
    return (self);
  }
}

List* List::substitute(Object* invalue, Object* outvalue) {
  // Destructively replace each appearance of `outValue' by
  // `inValue' in the list `self'.
  { List* self = this;

    self->theConsList = self->theConsList->substitute(invalue, outvalue);
    return (self);
  }
}

List* List::concatenate(List* list2, int otherlists, ...) {
  // Copy `list2' and all `otherLists' onto the end of `list1'.
  // The operation is destructive wrt `list1', but leaves all other lists intact.
  // The two mandatory parameters allow us to optimize the common binary case by
  // not relying on the somewhat less efficient variable arguments mechanism.
  { List* list1 = this;

    { Cons* firstlist = list1->theConsList;
      Cons* lastlist = list2->theConsList;
      Cons* copy = NIL;

      if (firstlist == NIL) {
        firstlist = copyConsList(lastlist);
        lastlist = firstlist;
      }
      else if (lastlist == NIL) {
        lastlist = firstlist;
      }
      else {
        lastlist = copyConsList(lastlist);
        lastCons(firstlist)->rest = lastlist;
      }
      if (otherlists > 0) {
        { va_list iter000;
          int iter000Count = otherlists;
          List* list = NULL;

          va_start(iter000, otherlists);
                    for  (; (iter000Count--) > 0; ) {
            list = va_arg(iter000, List*);
            if (list->nonEmptyP()) {
              copy = copyConsList(list->theConsList);
              if (!(lastlist == NIL)) {
                lastCons(lastlist)->rest = copy;
              }
              else {
                firstlist = copy;
              }
              lastlist = copy;
            }
          }
          va_end(iter000);
        }
      }
      list1->theConsList = firstlist;
      return (list1);
    }
  }
}

List* List::prepend(List* list2) {
  // Copy `list2' onto the front of the list `self'.
  // The operation is destructive wrt `self', but leaves `list2' intact.
  { List* self = this;

    if (list2->emptyP()) {
      return (self);
    }
    self->theConsList = copyConsList(list2->theConsList)->concatenate(self->theConsList, 0);
    return (self);
  }
}

List* createDerivedList(List* self) {
  // Create a new list object with the same type as `self'.
  { Surrogate* listtype = self->primaryType();

    if (listtype == SGT_LISTS_STELLA_LIST) {
      return (newList());
    }
    else if (listtype == SGT_LISTS_STELLA_SET) {
      return (newSet());
    }
    else {
      return (((List*)(createObject(listtype, 0))));
    }
  }
}

List* List::copy() {
  // Return a copy of the list `self'.  The conses in the copy are
  // freshly allocated.
  { List* self = this;

    { List* copy = createDerivedList(self);

      copy->theConsList = copyConsList(self->theConsList);
      return (copy);
    }
  }
}

void List::clear() {
  // Make `self' an empty list.
  { List* self = this;

    self->theConsList = NIL;
  }
}

List* List::sort(cpp_function_code predicate) {
  // Perform a stable, destructive sort of `self' according to
  // `predicate', and return the result.  If `predicate' has a '<' semantics, the
  // result will be in ascending order.  If `predicate' is NULL, a suitable
  // '<' predicate is chosen depending on the first element of `self', and it 
  // is assumed that all elements of `self' have the same type (supported
  // element types are GENERALIZED-SYMBOL, STRING, INTEGER, and FLOAT).
  { List* self = this;

    self->theConsList = self->theConsList->sort(predicate);
    return (self);
  }
}

List* mapNullToNilList(List* self) {
  // Return NIL-LIST iff `self' is NULL or `self' otherwise.
  return (((!((boolean)(self))) ? NIL_LIST : self));
}

boolean List::objectEqualP(Object* y) {
  // Return TRUE iff the lists `x' and `y' are structurally
  // equivalent.  Uses `equal?' to test equality of elements.
  { List* x = this;

    if (subtypeOfP(safePrimaryType(y), SGT_LISTS_STELLA_LIST)) {
      { Object* y000 = y;
        List* y = ((List*)(y000));

        return (equalP(x->theConsList, y->theConsList));
      }
    }
    else {
    }
    return (false);
  }
}

int List::equalHashCode() {
  // Return an `equal?' hash code for `self'.  Note that this
  // is O(N) in the number of elements of `self'.
  { List* self = this;

    { int code = 5619580;

      return ((code ^ (self->theConsList->equalHashCode())));
    }
  }
}

AbstractIterator* List::allocateIterator() {
  { List* self = this;

    { ListIterator* iterator = newListIterator();

      iterator->listIteratorCursor = self->theConsList;
      iterator->listIteratorCollection = self;
      iterator->firstIterationP = true;
      return (iterator);
    }
  }
}

boolean terminateListIteratorP(ListIterator* self) {
  self->listIteratorCursor = NIL;
  self->listIteratorCollection = NULL;
  return (true);
}

boolean ListIterator::nextP() {
  { ListIterator* self = this;

    if (self->firstIterationP) {
      {
        self->firstIterationP = false;
        self->listIteratorCursor = self->listIteratorCollection->theConsList;
      }
    }
    else {
      self->listIteratorCursor = self->listIteratorCursor->rest;
    }
    self->value = self->listIteratorCursor->value;
    return (!(self->listIteratorCursor == NIL));
  }
}

boolean ListIterator::emptyP() {
  { ListIterator* self = this;

    return ((self->firstIterationP ? (self->listIteratorCollection->theConsList == NIL) : (self->listIteratorCursor->rest == NIL)));
  }
}

Object* ListIterator::valueSetter(Object* value) {
  { ListIterator* self = this;

    self->listIteratorCursor->value = value;
    self->value = value;
    return (value);
  }
}

Iterator* List::butLast() {
  // Generate all but the last element of the list `self'.
  { List* self = this;

    return (self->theConsList->butLast());
  }
}

List* List::removeDeletedMembers() {
  { List* self = this;

    self->theConsList = self->theConsList->removeDeletedMembers();
    return (self);
  }
}

void PropertyList::initializeObject() {
  { PropertyList* self = this;

    self->thePlist = NIL;
  }
}

Object* searchPlist(Cons* plist, Object* key) {
  while (!(plist == NIL)) {
    if (eqlP(plist->value, key)) {
      return (plist->rest->value);
    }
    plist = plist->rest->rest;
  }
  return (NULL);
}

Object* PropertyList::lookup(Object* key) {
  { PropertyList* self = this;

    // inline method
    return (searchPlist(self->thePlist, key));
  }
}

Object* PropertyList::lookupWithDefault(Object* key, Object* defaulT) {
  // Lookup `key' in `self' and return the result.
  // Return `default' if no value was found.
  { PropertyList* self = this;

    { Object* value = searchPlist(self->thePlist, key);

      if (!((boolean)(value))) {
        return (defaulT);
      }
      else {
        return (value);
      }
    }
  }
}

int PropertyList::length() {
  { PropertyList* self = this;

    { Cons* cursor = self->thePlist;
      int length = 0;

      while (!(cursor == NIL)) {
        length = length + 1;
        cursor = cursor->rest->rest;
      }
      return (length);
    }
  }
}

void PropertyList::insertAt(Object* key, Object* value) {
  // Insert the entry <`key', `value'> into the property list `self'.
  // If a previous entry existed with key `key', that entry is replaced.
  { PropertyList* self = this;

    { Cons* cursor = self->thePlist;

      while (!(cursor == NIL)) {
        if (eqlP(cursor->value, key)) {
          cursor = cursor->rest;
          cursor->value = value;
          return;
        }
        cursor = cursor->rest->rest;
      }
      self->thePlist = cons(key, cons(value, self->thePlist));
    }
  }
}

Object* PropertyList::removeAt(Object* key) {
  // Remove the entry that matches the key `key'.  Return the
  // value of the matching entry, or NULL if there is no matching entry.  Assumes that at
  // most one entry matches `key'.
  { PropertyList* self = this;

    { Cons* cursor = self->thePlist;
      Cons* previouscons = NULL;
      Object* value = NULL;

      if (!(cursor == NIL)) {
        if (eqlP(cursor->value, key)) {
          self->thePlist = cursor->rest->rest;
          value = cursor->rest->value;
          return (value);
        }
        previouscons = cursor->rest;
        cursor = previouscons->rest;
        while (!(cursor == NIL)) {
          if (eqlP(cursor->value, key)) {
            previouscons->rest = cursor->rest->rest;
            value = cursor->rest->value;
            return (value);
          }
          previouscons = cursor->rest;
          cursor = previouscons->rest;
        }
      }
      return (NULL);
    }
  }
}

boolean PropertyList::emptyP() {
  { PropertyList* self = this;

    return (self->thePlist == NIL);
  }
}

boolean PropertyList::nonEmptyP() {
  { PropertyList* self = this;

    return (!(self->thePlist == NIL));
  }
}

PropertyList* PropertyList::copy() {
  // Return a copy of the list `self'.  The conses in the copy are
  // freshly allocated.
  { PropertyList* self = this;

    { PropertyList* copy = ((PropertyList*)(createObject(self->primaryType(), 0)));

      copy->thePlist = copyConsList(self->thePlist);
      return (copy);
    }
  }
}

void PropertyList::clear() {
  // Make `self' an empty property list.
  { PropertyList* self = this;

    self->thePlist = NIL;
  }
}

boolean PropertyList::objectEqualP(Object* y) {
  // Return TRUE if `x' and `y' represent the same set of key/value pairs..
  { PropertyList* x = this;

    if (subtypeOfP(safePrimaryType(y), SGT_LISTS_STELLA_PROPERTY_LIST)) {
      { Object* y000 = y;
        PropertyList* y = ((PropertyList*)(y000));

        if (x->length() == y->length()) {
          { Object* key = NULL;
            Object* value = NULL;
            Cons* iter000 = x->thePlist;

            for  (; !(iter000 == NIL); 
                  iter000 = iter000->rest->rest) {
              key = iter000->value;
              value = iter000->rest->value;
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

int PropertyList::equalHashCode() {
  // Return an `equal?' hash code for `self'.  Note that this
  // is O(N) in the number of entries of `self'.
  { PropertyList* self = this;

    { int code = 108398967;

      { Object* key = NULL;
        Object* value = NULL;
        Cons* iter000 = self->thePlist;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest->rest) {
          key = iter000->value;
          value = iter000->rest->value;
          code = (code ^ (safeEqualHashCode(key)));
          code = (code ^ (safeEqualHashCode(value)));
        }
      }
      return (code);
    }
  }
}

boolean List::subsetP(List* otherlist) {
  // Return true if every element of `self' also occurs in `otherList'.
  // Uses an `eql?' test and a simple quadratic-time algorithm.  Note that
  // this does not check whether `self' and `otherList' actually are sets.
  { List* self = this;

    return (self->theConsList->subsetP(otherlist->theConsList));
  }
}

boolean List::equivalentSetsP(List* otherlist) {
  // Return true if every element of `self' occurs in `otherList' and vice versa.
  // Uses an `eql?' test and a simple quadratic-time algorithm.  Note that
  // this does not check whether `self' and `otherList' actually are sets.
  { List* self = this;

    return (self->theConsList->equivalentSetsP(otherlist->theConsList));
  }
}

List* List::intersection(List* otherlist) {
  // Return the set intersection of `self' and `otherList'.  Uses an `eql?'
  // test and a simple quadratic-time algorithm.  Note that the result is only
  // guaranteed to be a set if both `self' and `otherList' are sets.
  { List* self = this;

    { List* result = createDerivedList(self);

      result->theConsList = self->theConsList->intersection(otherlist->theConsList);
      return (result);
    }
  }
}

List* List::unioN(List* otherlist) {
  // Return the set union of `self' and `otherList'.  Uses an `eql?' test
  // and a simple quadratic-time algorithm.  Note that the result is only
  // guaranteed to be a set if both `self' and `otherList' are sets.
  { List* self = this;

    { List* result = createDerivedList(self);

      result->theConsList = self->theConsList->unioN(otherlist->theConsList);
      return (result);
    }
  }
}

List* List::difference(List* otherlist) {
  // Return the set difference of `self' and `otherList' (i.e., all elements
  // that are in `self' but not in `otherSet').  Uses an `eql?' test and a simple
  // quadratic-time algorithm.  Note that the result is only guaranteed to be a
  // set if both `self' and `otherList' are sets.
  { List* self = this;

    { List* result = createDerivedList(self);

      result->theConsList = self->theConsList->difference(otherlist->theConsList);
      return (result);
    }
  }
}

List* List::subtract(List* otherlist) {
  // Return the set difference of `self' and `otherList' by destructively
  // removing elements from `self' that also occur in `otherList'.  Uses an `eql?'
  // test and a simple quadratic-time algorithm.  Note that the result is only
  // guaranteed to be a set if `self' is a set.
  { List* self = this;

    self->theConsList = self->theConsList->subtract(otherlist->theConsList);
    return (self);
  }
}

AbstractIterator* PropertyList::allocateIterator() {
  { PropertyList* self = this;

    { PropertyListIterator* iterator = newPropertyListIterator();

      iterator->plistIteratorCursor = self->thePlist;
      iterator->plistIteratorCollection = self;
      iterator->firstIterationP = true;
      return (iterator);
    }
  }
}

boolean PropertyListIterator::nextP() {
  { PropertyListIterator* self = this;

    if (self->firstIterationP) {
      self->firstIterationP = false;
    }
    else {
      self->plistIteratorCursor = self->plistIteratorCursor->rest->rest;
    }
    { Cons* remainingplist = self->plistIteratorCursor;

      if (!(remainingplist == NIL)) {
        self->key = remainingplist->value;
        self->value = remainingplist->rest->value;
        return (true);
      }
      return (false);
    }
  }
}

Object* PropertyListIterator::valueSetter(Object* value) {
  { PropertyListIterator* self = this;

    self->plistIteratorCursor->rest->value = value;
    self->value = value;
    return (value);
  }
}

Object* PropertyListIterator::keySetter(Object* key) {
  { PropertyListIterator* self = this;

    self->plistIteratorCursor->value = key;
    self->key = key;
    return (key);
  }
}

KvCons* kvCons(Object* key, Object* value, KvCons* rest) {
  // Create, fill-in, and return a new KV-CONS.
  { KvCons* newkvc = newKvCons();

    newkvc->key = key;
    newkvc->value = value;
    newkvc->rest = rest;
    return (newkvc);
  }
}

Object* KvCons::lookup(Object* key) {
  { KvCons* self = this;

    { KvCons* cursor = self;

      while (((boolean)(cursor))) {
        if (eqlP(cursor->key, key)) {
          return (cursor->value);
        }
        cursor = cursor->rest;
      }
      return (NULL);
    }
  }
}

int KvCons::length() {
  { KvCons* self = this;

    { KvCons* cursor = self;
      int length = 0;

      while (((boolean)(cursor))) {
        length = length + 1;
        cursor = cursor->rest;
      }
      return (length);
    }
  }
}

void freeKvCons(KvCons* kvcons) {
  kvcons->free();
}

Object* KeyValueList::lookup(Object* key) {
  { KeyValueList* self = this;

    { KvCons* cursor = self->theKvList;

      while (((boolean)(cursor))) {
        if (eqlP(cursor->key, key)) {
          return (cursor->value);
        }
        cursor = cursor->rest;
      }
      return (NULL);
    }
  }
}

Object* KeyValueList::lookupWithDefault(Object* key, Object* defaulT) {
  // Lookup `key' in `self' and return the result.
  // Return `default' if no value was found.
  { KeyValueList* self = this;

    { KvCons* cursor = self->theKvList;

      while (((boolean)(cursor))) {
        if (eqlP(cursor->key, key)) {
          return (cursor->value);
        }
        cursor = cursor->rest;
      }
      return (defaulT);
    }
  }
}

int KeyValueList::length() {
  { KeyValueList* self = this;

    { int length = 0;
      KvCons* cursor = self->theKvList;

      while (((boolean)(cursor))) {
        length = length + 1;
        cursor = cursor->rest;
      }
      return (length);
    }
  }
}

void KeyValueList::insertAt(Object* key, Object* value) {
  // Insert the entry <`key', `value'> into the association
  // `self'. If a previous entry existed with key `key', that entry is replaced.
  { KeyValueList* self = this;

    { KvCons* cursor = self->theKvList;

      while (((boolean)(cursor))) {
        if (eqlP(cursor->key, key)) {
          cursor->value = value;
          return;
        }
        cursor = cursor->rest;
      }
      self->theKvList = kvCons(key, value, self->theKvList);
    }
  }
}

Object* KeyValueList::removeAt(Object* key) {
  // Remove the entry that matches the key `key'.
  // Return the value of the matching entry, or NULL if there is no matching entry.
  // Assumes that at most one entry matches `key'.
  { KeyValueList* self = this;

    { KvCons* cursor = self->theKvList;
      KvCons* previouscursor = NULL;
      Object* value = NULL;

      if (((boolean)(cursor))) {
        if (eqlP(cursor->key, key)) {
          self->theKvList = cursor->rest;
          value = cursor->value;
          freeKvCons(cursor);
          return (value);
        }
        while (((boolean)(cursor->rest))) {
          previouscursor = cursor;
          cursor = cursor->rest;
          if (eqlP(cursor->key, key)) {
            previouscursor->rest = cursor->rest;
            value = cursor->value;
            freeKvCons(cursor);
            return (value);
          }
        }
      }
      return (NULL);
    }
  }
}

void KeyValueList::insertEntry(Object* key, Object* value) {
  // Insert an entry <`key',`value'> to `self' unless an identical
  // entry already exists.  This can generate duplicate entries for `key'.
  { KeyValueList* self = this;

    { boolean foundP000 = false;

      { Object* k = NULL;
        Object* v = NULL;
        KvCons* iter000 = self->theKvList;

        for  (; ((boolean)(iter000)); 
              iter000 = iter000->rest) {
          k = iter000->key;
          v = iter000->value;
          if ((k == key) &&
              (v == value)) {
            foundP000 = true;
            break;
          }
        }
      }
      if (!(foundP000)) {
        self->theKvList = kvCons(key, value, self->theKvList);
      }
    }
  }
}

void KeyValueList::removeEntry(Object* key, Object* value) {
  // Remove the entry that matches <`key',`value'>.
  // Assumes that more than one entry can match `key'.
  { KeyValueList* self = this;

    { KvCons* cursor = self->theKvList;
      KvCons* previouscursor = NULL;

      if (((boolean)(cursor))) {
        if (eqlP(cursor->key, key) &&
            eqlP(cursor->value, value)) {
          self->theKvList = cursor->rest;
          freeKvCons(cursor);
          return;
        }
        while (((boolean)(cursor->rest))) {
          previouscursor = cursor;
          cursor = cursor->rest;
          if (eqlP(cursor->key, key) &&
              eqlP(cursor->value, value)) {
            previouscursor->rest = cursor->rest;
            freeKvCons(cursor);
            return;
          }
        }
      }
    }
  }
}

void KeyValueList::push(KvCons* value) {
  // Make `value' be the new first element of `self'.  Note that
  // the `rest' slot of `value' should be `null', since it will be overwritten.
  // This might duplicate an existing entry. If a previous entry existed with the
  // same key as `value', that entry is retained, but shadowed by this new entry.
  { KeyValueList* self = this;

    if (!(!((boolean)(value->rest)))) {
      std::cerr << "Safety violation: " << "Push only supports single entry KV-CONSes";
    }
    value->rest = self->theKvList;
    self->theKvList = value;
  }
}

void KeyValueList::kvPush(Object* key, Object* value) {
  // Add a new entry <`key', `value'> to the front of the association
  // `self'. This might duplicate an existing entry. If a previous entry existed with key
  // `key', that entry is retained, but shadowed by this new entry.
  { KeyValueList* self = this;

    self->theKvList = kvCons(key, value, self->theKvList);
  }
}

Object* KeyValueList::pop() {
  // Remove and return the value of the first element of the
  // kv-list `self'.  It does NOT return the KV-CONS object.  Return `null' if
  // the list is empty.
  { KeyValueList* self = this;

    if (self->emptyP()) {
      return (NULL);
    }
    { KvCons* cons = self->theKvList;
      Object* value = NULL;

      value = cons->value;
      self->theKvList = cons->rest;
      freeKvCons(cons);
      return (value);
    }
  }
}

KeyValueList* KeyValueList::reverse() {
  // Destructively reverse the members of the list `self'.
  { KeyValueList* self = this;

    { KvCons* reversedlist = self->theKvList;
      KvCons* remaininglist = NULL;
      KvCons* temp = NULL;

      if (!((boolean)(reversedlist))) {
        return (self);
      }
      remaininglist = reversedlist->rest;
      if (!((boolean)(remaininglist))) {
        return (self);
      }
      reversedlist->rest = NULL;
      while (((boolean)(remaininglist))) {
        temp = remaininglist;
        remaininglist = remaininglist->rest;
        temp->rest = reversedlist;
        reversedlist = temp;
      }
      self->theKvList = reversedlist;
      return (self);
    }
  }
}

boolean KeyValueList::emptyP() {
  { KeyValueList* self = this;

    return (!((boolean)(self->theKvList)));
  }
}

boolean KeyValueList::nonEmptyP() {
  { KeyValueList* self = this;

    return (((boolean)(self->theKvList)));
  }
}

KvCons* copyKvConsList(KvCons* kvconslist) {
  // Return a copy of the cons list `consList'.
  if (!((boolean)(kvconslist))) {
    return (NULL);
  }
  { KvCons* newkvconslist = newKvCons();
    KvCons* nextkvcons = newkvconslist;
    KvCons* copyfromkvcons = NULL;
    KvCons* previouskvcons = NULL;

    nextkvcons->key = kvconslist->key;
    nextkvcons->value = kvconslist->value;
    copyfromkvcons = kvconslist->rest;
    while (((boolean)(copyfromkvcons))) {
      previouskvcons = nextkvcons;
      nextkvcons = newKvCons();
      previouskvcons->rest = nextkvcons;
      nextkvcons->key = copyfromkvcons->key;
      nextkvcons->value = copyfromkvcons->value;
      copyfromkvcons = copyfromkvcons->rest;
    }
    nextkvcons->rest = NULL;
    return (newkvconslist);
  }
}

KeyValueList* KeyValueList::copy() {
  // Return a copy of the kv-list `self'.  The kv-conses in
  // the copy are freshly allocated.
  { KeyValueList* self = this;

    { KeyValueList* copy = newKeyValueList();

      copy->theKvList = copyKvConsList(self->theKvList);
      return (copy);
    }
  }
}

void KeyValueList::clear() {
  // Make `self' an empty dictionary.
  { KeyValueList* self = this;

    { KvCons* next = self->theKvList;
      KvCons* current = NULL;

      while (((boolean)(next))) {
        current = next;
        next = next->rest;
        freeKvCons(current);
      }
      self->theKvList = NULL;
    }
  }
}

boolean KeyValueList::objectEqualP(Object* y) {
  // Return TRUE if `x' and `y' represent the same set of key/value pairs.
  { KeyValueList* x = this;

    if (subtypeOfP(safePrimaryType(y), SGT_LISTS_STELLA_KEY_VALUE_LIST)) {
      { Object* y000 = y;
        KeyValueList* y = ((KeyValueList*)(y000));

        if (x->length() == y->length()) {
          { Object* key = NULL;
            Object* value = NULL;
            KvCons* iter000 = x->theKvList;

            for  (; ((boolean)(iter000)); 
                  iter000 = iter000->rest) {
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

int KeyValueList::equalHashCode() {
  // Return an `equal?' hash code for `self'.  Note that this
  // is O(N) in the number of entries of `self'.
  { KeyValueList* self = this;

    { int code = 94797224;

      { Object* key = NULL;
        Object* value = NULL;
        KvCons* iter000 = self->theKvList;

        for  (; ((boolean)(iter000)); 
              iter000 = iter000->rest) {
          key = iter000->key;
          value = iter000->value;
          code = (code ^ (safeEqualHashCode(key)));
          code = (code ^ (safeEqualHashCode(value)));
        }
      }
      return (code);
    }
  }
}

AbstractIterator* KeyValueList::allocateIterator() {
  { KeyValueList* self = this;

    { KvListIterator* iterator = newKvListIterator();

      iterator->theKvList = self;
      iterator->kvListIteratorCursor = self->theKvList;
      iterator->firstIterationP = true;
      return (iterator);
    }
  }
}

boolean KvListIterator::nextP() {
  { KvListIterator* self = this;

    if (self->firstIterationP) {
      self->firstIterationP = false;
    }
    else {
      self->kvListIteratorCursor = self->kvListIteratorCursor->rest;
    }
    if (!((boolean)(self->kvListIteratorCursor))) {
      return (false);
    }
    self->key = self->kvListIteratorCursor->key;
    self->value = self->kvListIteratorCursor->value;
    return (true);
  }
}

Object* KvListIterator::valueSetter(Object* value) {
  { KvListIterator* self = this;

    self->kvListIteratorCursor->value = value;
    self->value = value;
    return (value);
  }
}

Object* KvListIterator::keySetter(Object* key) {
  { KvListIterator* self = this;

    self->kvListIteratorCursor->key = key;
    self->key = key;
    return (key);
  }
}

PropertyList* kvlistToPlist(KeyValueList* self) {
  // Convert `self' into a property list with identical and identically
  // ordered keys and values.
  { Cons* plist = NIL;

    { Object* key = NULL;
      Object* value = NULL;
      KvCons* iter000 = self->theKvList;

      for  (; ((boolean)(iter000)); 
            iter000 = iter000->rest) {
        key = iter000->key;
        value = iter000->value;
        plist = cons(value, cons(key, plist));
      }
    }
    { PropertyList* self000 = newPropertyList();

      self000->thePlist = plist->reverse();
      { PropertyList* value000 = self000;

        return (value000);
      }
    }
  }
}

KeyValueList* plistToKvlist(PropertyList* self) {
  // Convert `self' into a key-value list with identical and identically
  // ordered keys and values.
  { KeyValueList* kvlist = newKeyValueList();
    KvCons* kvcons = NULL;

    { Object* key = NULL;
      Object* value = NULL;
      Cons* iter000 = self->thePlist;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest->rest) {
        key = iter000->value;
        value = iter000->rest->value;
        if (!((boolean)(kvcons))) {
          kvcons = newKvCons();
          kvlist->theKvList = kvcons;
        }
        else {
          kvcons->rest = newKvCons();
          kvcons = kvcons->rest;
        }
        kvcons->key = key;
        kvcons->value = value;
      }
    }
    return (kvlist);
  }
}

boolean Sequence::memberP(Object* value) {
  // Return TRUE if `value' is a member of the sequence `self'.
  { Sequence* self = this;

    { Object* m = NULL;
      Iterator* iter000 = ((Iterator*)(self->allocateIterator()));

      for (; iter000->nextP(); ) {
        m = iter000->value;
        if (eqlP(m, value)) {
          return (true);
        }
      }
    }
    return (false);
  }
}

List* list(int values, ...) {
  // Return a list containing `values', in order.
  { List* list = newList();

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
            if (list->theConsList == NIL) {
              list->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(list->theConsList, collect000);
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

Sequence* sequence(Surrogate* collectiontype, int values, ...) {
  // Return a sequence containing `values', in order.
  { Sequence* sequence = ((Sequence*)(createObject(collectiontype, 0)));

    { va_list iter000;
      int iter000Count = values;
      Object* i = NULL;

      va_start(iter000, values);
            for  (; (iter000Count--) > 0; ) {
        i = va_arg(iter000, Object*);
        if (subtypeOfP(safePrimaryType(sequence), SGT_LISTS_STELLA_LIST)) {
          { Sequence* sequence000 = sequence;
            List* sequence = ((List*)(sequence000));

            sequence->insertLast(i);
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "sequence: Don't know how to `insert-last' into a " << "`" << collectiontype << "'";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      va_end(iter000);
    }
    return (sequence);
  }
}

AbstractDictionary* dictionary(Surrogate* collectiontype, int alternatingkeysandvalues, ...) {
  // Return a dictionary of `collectionType' containing `values', in order.
  // Currently supported `collectionType's are @HASH-TABLE, @STELLA-HASH-TABLE,
  // @KEY-VALUE-LIST, @KEY-VALUE-MAP and @PROPERTY-LIST.
  { AbstractDictionary* dictionary = ((AbstractDictionary*)(createObject(collectiontype, 0)));
    Object* key = NULL;
    Object* value = NULL;
    Cons* copy = NIL;
    Cons* cursor = NULL;

    { va_list iter000;
      int iter000Count = alternatingkeysandvalues;
      Object* item = NULL;
      Cons* collect000 = NULL;

      va_start(iter000, alternatingkeysandvalues);
            for  (; (iter000Count--) > 0; ) {
        item = va_arg(iter000, Object*);
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(item, NIL);
            if (copy == NIL) {
              copy = collect000;
            }
            else {
              addConsToEndOfConsList(copy, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(item, NIL);
            collect000 = collect000->rest;
          }
        }
      }
      va_end(iter000);
    }
    cursor = copy;
    while (!(cursor == NIL)) {
      key = cursor->value;
      value = cursor->rest->value;
      { Surrogate* testValue000 = safePrimaryType(dictionary);

        if (subtypeOfP(testValue000, SGT_LISTS_STELLA_HASH_TABLE)) {
          { AbstractDictionary* dictionary000 = dictionary;
            HashTable* dictionary = ((HashTable*)(dictionary000));

            dictionary->insertAt(key, value);
          }
        }
        else if (subtypeOfP(testValue000, SGT_LISTS_STELLA_STELLA_HASH_TABLE)) {
          { AbstractDictionary* dictionary001 = dictionary;
            StellaHashTable* dictionary = ((StellaHashTable*)(dictionary001));

            dictionary->insertAt(key, value);
          }
        }
        else if (subtypeOfP(testValue000, SGT_LISTS_STELLA_KEY_VALUE_LIST)) {
          { AbstractDictionary* dictionary002 = dictionary;
            KeyValueList* dictionary = ((KeyValueList*)(dictionary002));

            dictionary->insertAt(key, value);
          }
        }
        else if (subtypeOfP(testValue000, SGT_LISTS_STELLA_KEY_VALUE_MAP)) {
          { AbstractDictionary* dictionary003 = dictionary;
            KeyValueMap* dictionary = ((KeyValueMap*)(dictionary003));

            dictionary->insertAt(key, value);
          }
        }
        else if (subtypeOfP(testValue000, SGT_LISTS_STELLA_PROPERTY_LIST)) {
          { AbstractDictionary* dictionary004 = dictionary;
            PropertyList* dictionary = ((PropertyList*)(dictionary004));

            dictionary->insertAt(key, value);
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "dictionary: Can't create dictionaries of type " << "`" << collectiontype << "'";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      cursor = cursor->rest->rest;
    }
    return (dictionary);
  }
}

List* List::listify() {
  // Return `self'.
  { List* self = this;

    return (self);
  }
}

List* Cons::listify() {
  // Return a list of elements in `self'.
  { Cons* self = this;

    { List* self000 = newList();

      self000->theConsList = self;
      { List* value000 = self000;

        return (value000);
      }
    }
  }
}

List* KeyValueList::listify() {
  // Return a list of key-value pairs in `self'.
  { KeyValueList* self = this;

    { List* result = newList();

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
              if (result->theConsList == NIL) {
                result->theConsList = collect000;
              }
              else {
                addConsToEndOfConsList(result->theConsList, collect000);
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

List* Vector::listify() {
  // Return a list of elements in `self'.
  { Vector* self = this;

    { List* result = newList();

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
              if (result->theConsList == NIL) {
                result->theConsList = collect000;
              }
              else {
                addConsToEndOfConsList(result->theConsList, collect000);
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

List* Iterator::listify() {
  // Return a list of elements generated by `self'.
  { Iterator* self = this;

    { List* list = newList();

      { Object* value = NULL;
        Iterator* iter000 = self;

        for (; iter000->nextP(); ) {
          value = iter000->value;
          list->push(value);
        }
      }
      return (list->reverse());
    }
  }
}

void printKeyValueList(KeyValueList* self, std::ostream* stream) {
  *(stream) << "|kv|(";
  { KvCons* cursor = self->theKvList;
    int position = 1;

    while (((boolean)(cursor))) {
      if ((oPRINTLENGTHo != NULL_INTEGER) &&
          (position > oPRINTLENGTHo)) {
        *(stream) << " ...";
        break;
      }
      if (!(position == 1)) {
        *(stream) << " ";
      }
      *(stream) << cursor;
      cursor = cursor->rest;
      position = position + 1;
    }
    *(stream) << ")";
  }
}

void helpStartupLists1() {
  {
    SGT_LISTS_STELLA_LIST = ((Surrogate*)(internRigidSymbolWrtModule("LIST", NULL, 1)));
    SGT_LISTS_STELLA_SET = ((Surrogate*)(internRigidSymbolWrtModule("SET", NULL, 1)));
    SGT_LISTS_STELLA_PROPERTY_LIST = ((Surrogate*)(internRigidSymbolWrtModule("PROPERTY-LIST", NULL, 1)));
    SGT_LISTS_STELLA_KEY_VALUE_LIST = ((Surrogate*)(internRigidSymbolWrtModule("KEY-VALUE-LIST", NULL, 1)));
    SGT_LISTS_STELLA_HASH_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("HASH-TABLE", NULL, 1)));
    SGT_LISTS_STELLA_STELLA_HASH_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("STELLA-HASH-TABLE", NULL, 1)));
    SGT_LISTS_STELLA_KEY_VALUE_MAP = ((Surrogate*)(internRigidSymbolWrtModule("KEY-VALUE-MAP", NULL, 1)));
    SYM_LISTS_STELLA_STARTUP_LISTS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-LISTS", NULL, 0)));
    SYM_LISTS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupLists2() {
  {
    defineFunctionObject("DEFINED-LIST?", "(DEFUN (DEFINED-LIST? BOOLEAN) ((SELF LIST)) :PUBLIC? TRUE :DOCUMENTATION \"Return TRUE unless `self' is NULL or the `NIL-LIST'.\")", ((cpp_function_code)(&definedListP)), NULL);
    defineFunctionObject("NULL-LIST?", "(DEFUN (NULL-LIST? BOOLEAN) ((SELF LIST)) :PUBLIC? TRUE :DOCUMENTATION \"Return TRUE iff `self' is NULL or the `NIL-LIST'.\")", ((cpp_function_code)(&nullListP)), NULL);
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF LIST)) :PUBLIC? TRUE :DOCUMENTATION \"Return TRUE if the list `self' has no members.\")", wrapMethodCode(((cpp_method_code)(&List::emptyP))), NULL);
    defineMethodObject("(DEFMETHOD (NON-EMPTY? BOOLEAN) ((SELF LIST)) :PUBLIC? TRUE :DOCUMENTATION \"Return TRUE if the list `self' has at least one member.\")", wrapMethodCode(((cpp_method_code)(&List::nonEmptyP))), NULL);
    defineFunctionObject("TERMINATE-LIST?", "(DEFUN (TERMINATE-LIST? BOOLEAN) ((SELF LIST)))", ((cpp_function_code)(&terminateListP)), NULL);
    defineMethodObject("(DEFMETHOD (MEMBER? BOOLEAN) ((SELF LIST) (OBJECT OBJECT)) :DOCUMENTATION \"Return TRUE iff `object' is a member of the list\n`self' (uses an `eql?' test).\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::memberP))), NULL);
    defineMethodObject("(DEFMETHOD (MEMB? BOOLEAN) ((SELF LIST) (OBJECT (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Return TRUE iff `object' is a member of the cons list\n`self' (uses an 'eq?' test).\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::membP))), NULL);
    defineMethodObject("(DEFMETHOD (FIRST (LIKE (ANY-VALUE SELF))) ((SELF LIST)) :DOCUMENTATION \"Return the first item in the list `self', or NULL if empty.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::first))), NULL);
    defineMethodObject("(DEFMETHOD (SECOND (LIKE (ANY-VALUE SELF))) ((SELF LIST)) :DOCUMENTATION \"Return the second item in the list `self', or NULL if empty.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::second))), NULL);
    defineMethodObject("(DEFMETHOD (THIRD (LIKE (ANY-VALUE SELF))) ((SELF LIST)) :DOCUMENTATION \"Return the third item in the list `self', or NULL if empty.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::third))), NULL);
    defineMethodObject("(DEFMETHOD (FOURTH (LIKE (ANY-VALUE SELF))) ((SELF LIST)) :DOCUMENTATION \"Return the fourth item in the list `self', or NULL if empty.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::fourth))), NULL);
    defineMethodObject("(DEFMETHOD (FIFTH (LIKE (ANY-VALUE SELF))) ((SELF LIST)) :DOCUMENTATION \"Return the fifth item in the list `self', or NULL if empty.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::fifth))), NULL);
    defineMethodObject("(DEFMETHOD (NTH (LIKE (ANY-VALUE SELF))) ((SELF LIST) (POSITION INTEGER)) :DOCUMENTATION \"Return the nth item in the list `self', or NULL if empty.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::nth))), NULL);
    defineMethodObject("(DEFMETHOD (LAST (LIKE (ANY-VALUE SELF))) ((SELF LIST)) :DOCUMENTATION \"Return the last element of `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::last))), NULL);
    defineMethodObject("(DEFMETHOD (REST (CONS OF (LIKE (ANY-VALUE SELF)))) ((SELF LIST)) :DOCUMENTATION \"Return a cons list of all but the first item in the list `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::rest))), NULL);
    defineMethodObject("(DEFMETHOD (FIRST-SETTER (LIKE (ANY-VALUE SELF))) ((SELF LIST) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::firstSetter))), NULL);
    defineMethodObject("(DEFMETHOD (SECOND-SETTER (LIKE (ANY-VALUE SELF))) ((SELF LIST) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::secondSetter))), NULL);
    defineMethodObject("(DEFMETHOD (THIRD-SETTER (LIKE (ANY-VALUE SELF))) ((SELF LIST) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::thirdSetter))), NULL);
    defineMethodObject("(DEFMETHOD (FOURTH-SETTER (LIKE (ANY-VALUE SELF))) ((SELF LIST) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::fourthSetter))), NULL);
    defineMethodObject("(DEFMETHOD (FIFTH-SETTER (LIKE (ANY-VALUE SELF))) ((SELF LIST) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::fifthSetter))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-SETTER (LIKE (ANY-VALUE SELF))) ((SELF LIST) (VALUE (LIKE (ANY-VALUE SELF))) (POSITION INTEGER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::nthSetter))), NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF LIST)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::length))), NULL);
    defineMethodObject("(DEFMETHOD (POSITION INTEGER) ((SELF LIST) (OBJECT OBJECT) (START INTEGER)) :DOCUMENTATION \"Return the position of `object' within the list\n`self' (counting from zero); or return NULL if `object' does not occur within \n`self' (uses an `eql?' test).  If `start' was supplied as non-NULL, only \nconsider the sublist starting at `start', however, the returned position \nwill always be relative to the entire list.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::position))), NULL);
    defineMethodObject("(DEFMETHOD (LAST-POSITION INTEGER) ((SELF LIST) (OBJECT OBJECT) (END INTEGER)) :DOCUMENTATION \"Return the position of `object' within the list\n`self' (counting from zero); or return NULL if `object' does not occur within \n`self' (uses an `eql?' test).  If `end' was supplied as non-NULL, only \nconsider the sublist ending at `end', however, the returned position \nwill always be relative to the entire list.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::lastPosition))), NULL);
    defineMethodObject("(DEFMETHOD INSERT ((SELF LIST) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Add `value' to the front of the list `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::insert))), NULL);
    defineMethodObject("(DEFMETHOD PUSH ((SELF LIST) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Add `value' to the front of the list `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::push))), NULL);
    defineMethodObject("(DEFMETHOD INSERT-NEW ((SELF LIST) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Add `value' to the front of the list `self' unless its \nalready a member.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::insertNew))), NULL);
    defineMethodObject("(DEFMETHOD INSERT-LAST ((SELF LIST) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Insert `value' as the last entry in the list `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::insertLast))), NULL);
    defineMethodObject("(DEFMETHOD (REMOVE (LIKE SELF)) ((SELF LIST) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Destructively remove all entries in `self' that match `value'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::remove))), NULL);
    defineMethodObject("(DEFMETHOD (REMOVE-IF (LIKE SELF)) ((SELF LIST) (TEST? FUNCTION-CODE)) :DOCUMENTATION \"Destructively remove all members of the list `self' for which\n'test?' evaluates to TRUE.  `test' takes a single argument of type OBJECT and\nreturns TRUE or FALSE.  Returns `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::removeIf))), NULL);
    defineMethodObject("(DEFMETHOD (REMOVE-DUPLICATES (LIKE SELF)) ((SELF LIST)) :DOCUMENTATION \"Destructively remove duplicates from `self' and return the result.\nPreserves the original order of the remaining members.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::removeDuplicates))), NULL);
    defineMethodObject("(DEFMETHOD (REMOVE-DUPLICATES-EQUAL (LIKE SELF)) ((SELF LIST)) :DOCUMENTATION \"`remove-duplicates' (which see) using an `equal?' test.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::removeDuplicatesEqual))), NULL);
    defineMethodObject("(DEFMETHOD (POP (LIKE (ANY-VALUE SELF))) ((SELF LIST)) :DOCUMENTATION \"Remove and return the first element in the list `self'.\nReturn NULL if the list is empty.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::pop))), NULL);
    defineMethodObject("(DEFMETHOD (REVERSE (LIKE SELF)) ((SELF LIST)) :DOCUMENTATION \"Reverse the members of `self' (in place).\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::reverse))), NULL);
    defineMethodObject("(DEFMETHOD (SUBSTITUTE (LIKE SELF)) ((SELF LIST) (INVALUE OBJECT) (OUTVALUE OBJECT)) :DOCUMENTATION \"Destructively replace each appearance of `outValue' by\n`inValue' in the list `self'.\")", wrapMethodCode(((cpp_method_code)(&List::substitute))), NULL);
    defineMethodObject("(DEFMETHOD (CONCATENATE LIST) ((LIST1 LIST) (LIST2 LIST) |&REST| (OTHERLISTS LIST)) :DOCUMENTATION \"Copy `list2' and all `otherLists' onto the end of `list1'.\nThe operation is destructive wrt `list1', but leaves all other lists intact.\nThe two mandatory parameters allow us to optimize the common binary case by\nnot relying on the somewhat less efficient variable arguments mechanism.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::concatenate))), NULL);
    defineMethodObject("(DEFMETHOD (PREPEND (LIKE SELF)) ((SELF LIST) (LIST2 LIST)) :DOCUMENTATION \"Copy `list2' onto the front of the list `self'.\nThe operation is destructive wrt `self', but leaves `list2' intact.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::prepend))), NULL);
    defineFunctionObject("CREATE-DERIVED-LIST", "(DEFUN (CREATE-DERIVED-LIST LIST) ((SELF LIST)) :DOCUMENTATION \"Create a new list object with the same type as `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&createDerivedList)), NULL);
    defineMethodObject("(DEFMETHOD (COPY (LIST OF (LIKE (ANY-VALUE SELF)))) ((SELF LIST)) :DOCUMENTATION \"Return a copy of the list `self'.  The conses in the copy are\nfreshly allocated.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::copy))), NULL);
    defineMethodObject("(DEFMETHOD CLEAR ((SELF LIST)) :DOCUMENTATION \"Make `self' an empty list.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::clear))), NULL);
    defineMethodObject("(DEFMETHOD (SORT (LIST OF (LIKE (ANY-VALUE SELF)))) ((SELF LIST) (PREDICATE FUNCTION-CODE)) :PUBLIC? TRUE :DOCUMENTATION \"Perform a stable, destructive sort of `self' according to\n`predicate', and return the result.  If `predicate' has a '<' semantics, the\nresult will be in ascending order.  If `predicate' is NULL, a suitable\n'<' predicate is chosen depending on the first element of `self', and it \nis assumed that all elements of `self' have the same type (supported\nelement types are GENERALIZED-SYMBOL, STRING, INTEGER, and FLOAT).\")", wrapMethodCode(((cpp_method_code)(&List::sort))), NULL);
    defineFunctionObject("MAP-NULL-TO-NIL-LIST", "(DEFUN (MAP-NULL-TO-NIL-LIST LIST) ((SELF LIST)) :DOCUMENTATION \"Return NIL-LIST iff `self' is NULL or `self' otherwise.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (CHOOSE (NULL? SELF) NIL-LIST SELF)))", ((cpp_function_code)(&mapNullToNilList)), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQUAL? BOOLEAN) ((X LIST) (Y OBJECT)) :DOCUMENTATION \"Return TRUE iff the lists `x' and `y' are structurally\nequivalent.  Uses `equal?' to test equality of elements.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::objectEqualP))), NULL);
    defineMethodObject("(DEFMETHOD (EQUAL-HASH-CODE INTEGER) ((SELF LIST)) :DOCUMENTATION \"Return an `equal?' hash code for `self'.  Note that this\nis O(N) in the number of elements of `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::equalHashCode))), NULL);
    defineMethodObject("(DEFMETHOD (ALLOCATE-ITERATOR (LIST-ITERATOR OF (LIKE (ANY-VALUE SELF)))) ((SELF LIST)))", wrapMethodCode(((cpp_method_code)(&List::allocateIterator))), NULL);
    defineFunctionObject("TERMINATE-LIST-ITERATOR?", "(DEFUN (TERMINATE-LIST-ITERATOR? BOOLEAN) ((SELF LIST-ITERATOR)))", ((cpp_function_code)(&terminateListIteratorP)), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF LIST-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ListIterator::nextP))), NULL);
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF LIST-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ListIterator::emptyP))), NULL);
    defineMethodObject("(DEFMETHOD (VALUE-SETTER OBJECT) ((SELF LIST-ITERATOR) (VALUE (LIKE (ANY-VALUE SELF)))))", wrapMethodCode(((cpp_method_code)(&ListIterator::valueSetter))), NULL);
    defineMethodObject("(DEFMETHOD (BUT-LAST (ITERATOR OF (LIKE (ANY-VALUE SELF)))) ((SELF LIST)) :DOCUMENTATION \"Generate all but the last element of the list `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::butLast))), NULL);
    defineMethodObject("(DEFMETHOD (REMOVE-DELETED-MEMBERS (LIKE SELF)) ((SELF LIST)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::removeDeletedMembers))), NULL);
    defineMethodObject("(DEFMETHOD INITIALIZE-OBJECT ((SELF PROPERTY-LIST)))", wrapMethodCode(((cpp_method_code)(&PropertyList::initializeObject))), NULL);
    defineFunctionObject("SEARCH-PLIST", "(DEFUN (SEARCH-PLIST OBJECT) ((PLIST CONS) (KEY OBJECT)))", ((cpp_function_code)(&searchPlist)), NULL);
    defineMethodObject("(DEFMETHOD (LOOKUP (LIKE (ANY-VALUE SELF))) ((SELF PROPERTY-LIST) (KEY (LIKE (ANY-KEY SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropertyList::lookup))), NULL);
    defineMethodObject("(DEFMETHOD (LOOKUP-WITH-DEFAULT (LIKE (ANY-VALUE SELF))) ((SELF PROPERTY-LIST) (KEY (LIKE (ANY-KEY SELF))) (DEFAULT (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Lookup `key' in `self' and return the result.\nReturn `default' if no value was found.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropertyList::lookupWithDefault))), NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF PROPERTY-LIST)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropertyList::length))), NULL);
    defineMethodObject("(DEFMETHOD INSERT-AT ((SELF PROPERTY-LIST) (KEY (LIKE (ANY-KEY SELF))) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Insert the entry <`key', `value'> into the property list `self'.\nIf a previous entry existed with key `key', that entry is replaced.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropertyList::insertAt))), NULL);
    defineMethodObject("(DEFMETHOD (REMOVE-AT OBJECT) ((SELF PROPERTY-LIST) (KEY (LIKE (ANY-KEY SELF)))) :DOCUMENTATION \"Remove the entry that matches the key `key'.  Return the\nvalue of the matching entry, or NULL if there is no matching entry.  Assumes that at\nmost one entry matches `key'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropertyList::removeAt))), NULL);
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF PROPERTY-LIST)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropertyList::emptyP))), NULL);
    defineMethodObject("(DEFMETHOD (NON-EMPTY? BOOLEAN) ((SELF PROPERTY-LIST)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropertyList::nonEmptyP))), NULL);
  }
}

void startupLists() {
  if (currentStartupTimePhaseP(0)) {
    if (!(((boolean)(NIL_LIST)))) {
      NIL_LIST = new List();
    }
    NIL_LIST->theConsList = NIL;
  }
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupLists1();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupLists2();
      defineMethodObject("(DEFMETHOD (COPY (LIKE SELF)) ((SELF PROPERTY-LIST)) :DOCUMENTATION \"Return a copy of the list `self'.  The conses in the copy are\nfreshly allocated.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropertyList::copy))), NULL);
      defineMethodObject("(DEFMETHOD CLEAR ((SELF PROPERTY-LIST)) :DOCUMENTATION \"Make `self' an empty property list.\")", wrapMethodCode(((cpp_method_code)(&PropertyList::clear))), NULL);
      defineMethodObject("(DEFMETHOD (OBJECT-EQUAL? BOOLEAN) ((X PROPERTY-LIST) (Y OBJECT)) :DOCUMENTATION \"Return TRUE if `x' and `y' represent the same set of key/value pairs..\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropertyList::objectEqualP))), NULL);
      defineMethodObject("(DEFMETHOD (EQUAL-HASH-CODE INTEGER) ((SELF PROPERTY-LIST)) :DOCUMENTATION \"Return an `equal?' hash code for `self'.  Note that this\nis O(N) in the number of entries of `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropertyList::equalHashCode))), NULL);
      defineMethodObject("(DEFMETHOD (SUBSET? BOOLEAN) ((SELF LIST) (OTHERLIST LIST)) :DOCUMENTATION \"Return true if every element of `self' also occurs in `otherList'.\nUses an `eql?' test and a simple quadratic-time algorithm.  Note that\nthis does not check whether `self' and `otherList' actually are sets.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::subsetP))), NULL);
      defineMethodObject("(DEFMETHOD (EQUIVALENT-SETS? BOOLEAN) ((SELF LIST) (OTHERLIST LIST)) :DOCUMENTATION \"Return true if every element of `self' occurs in `otherList' and vice versa.\nUses an `eql?' test and a simple quadratic-time algorithm.  Note that\nthis does not check whether `self' and `otherList' actually are sets.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::equivalentSetsP))), NULL);
      defineMethodObject("(DEFMETHOD (INTERSECTION LIST) ((SELF LIST) (OTHERLIST LIST)) :DOCUMENTATION \"Return the set intersection of `self' and `otherList'.  Uses an `eql?'\ntest and a simple quadratic-time algorithm.  Note that the result is only\nguaranteed to be a set if both `self' and `otherList' are sets.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::intersection))), NULL);
      defineMethodObject("(DEFMETHOD (UNION LIST) ((SELF LIST) (OTHERLIST LIST)) :DOCUMENTATION \"Return the set union of `self' and `otherList'.  Uses an `eql?' test\nand a simple quadratic-time algorithm.  Note that the result is only\nguaranteed to be a set if both `self' and `otherList' are sets.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::unioN))), NULL);
      defineMethodObject("(DEFMETHOD (DIFFERENCE LIST) ((SELF LIST) (OTHERLIST LIST)) :DOCUMENTATION \"Return the set difference of `self' and `otherList' (i.e., all elements\nthat are in `self' but not in `otherSet').  Uses an `eql?' test and a simple\nquadratic-time algorithm.  Note that the result is only guaranteed to be a\nset if both `self' and `otherList' are sets.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::difference))), NULL);
      defineMethodObject("(DEFMETHOD (SUBTRACT LIST) ((SELF LIST) (OTHERLIST LIST)) :DOCUMENTATION \"Return the set difference of `self' and `otherList' by destructively\nremoving elements from `self' that also occur in `otherList'.  Uses an `eql?'\ntest and a simple quadratic-time algorithm.  Note that the result is only\nguaranteed to be a set if `self' is a set.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::subtract))), NULL);
      defineMethodObject("(DEFMETHOD (ALLOCATE-ITERATOR (PROPERTY-LIST-ITERATOR OF (LIKE (ANY-KEY SELF)) (LIKE (ANY-VALUE SELF)))) ((SELF PROPERTY-LIST)))", wrapMethodCode(((cpp_method_code)(&PropertyList::allocateIterator))), NULL);
      defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF PROPERTY-LIST-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropertyListIterator::nextP))), NULL);
      defineMethodObject("(DEFMETHOD (VALUE-SETTER (LIKE (ANY-VALUE SELF))) ((SELF PROPERTY-LIST-ITERATOR) (VALUE (LIKE (ANY-VALUE SELF)))))", wrapMethodCode(((cpp_method_code)(&PropertyListIterator::valueSetter))), NULL);
      defineMethodObject("(DEFMETHOD (KEY-SETTER (LIKE (ANY-KEY SELF))) ((SELF PROPERTY-LIST-ITERATOR) (KEY (LIKE (ANY-KEY SELF)))))", wrapMethodCode(((cpp_method_code)(&PropertyListIterator::keySetter))), NULL);
      defineFunctionObject("KV-CONS", "(DEFUN (KV-CONS KV-CONS) ((KEY OBJECT) (VALUE OBJECT) (REST KV-CONS)) :DOCUMENTATION \"Create, fill-in, and return a new KV-CONS.\" :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&kvCons)), NULL);
      defineMethodObject("(DEFMETHOD (LOOKUP (LIKE (ANY-VALUE SELF))) ((SELF KV-CONS) (KEY (LIKE (ANY-KEY SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KvCons::lookup))), NULL);
      defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF KV-CONS)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KvCons::length))), NULL);
      defineFunctionObject("FREE-KV-CONS", "(DEFUN FREE-KV-CONS ((KVCONS KV-CONS)))", ((cpp_function_code)(&freeKvCons)), NULL);
      defineMethodObject("(DEFMETHOD (LOOKUP (LIKE (ANY-VALUE SELF))) ((SELF KEY-VALUE-LIST) (KEY (LIKE (ANY-KEY SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueList::lookup))), NULL);
      defineMethodObject("(DEFMETHOD (LOOKUP-WITH-DEFAULT (LIKE (ANY-VALUE SELF))) ((SELF KEY-VALUE-LIST) (KEY (LIKE (ANY-KEY SELF))) (DEFAULT (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Lookup `key' in `self' and return the result.\nReturn `default' if no value was found.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueList::lookupWithDefault))), NULL);
      defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF KEY-VALUE-LIST)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueList::length))), NULL);
      defineMethodObject("(DEFMETHOD INSERT-AT ((SELF KEY-VALUE-LIST) (KEY (LIKE (ANY-KEY SELF))) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE :DOCUMENTATION \"Insert the entry <`key', `value'> into the association\n`self'. If a previous entry existed with key `key', that entry is replaced.\")", wrapMethodCode(((cpp_method_code)(&KeyValueList::insertAt))), NULL);
      defineMethodObject("(DEFMETHOD (REMOVE-AT OBJECT) ((SELF KEY-VALUE-LIST) (KEY (LIKE (ANY-KEY SELF)))) :PUBLIC? TRUE :DOCUMENTATION \"Remove the entry that matches the key `key'.\nReturn the value of the matching entry, or NULL if there is no matching entry.\nAssumes that at most one entry matches `key'.\")", wrapMethodCode(((cpp_method_code)(&KeyValueList::removeAt))), NULL);
      defineMethodObject("(DEFMETHOD INSERT-ENTRY ((SELF KEY-VALUE-LIST) (KEY (LIKE (ANY-KEY SELF))) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE :DOCUMENTATION \"Insert an entry <`key',`value'> to `self' unless an identical\nentry already exists.  This can generate duplicate entries for `key'.\")", wrapMethodCode(((cpp_method_code)(&KeyValueList::insertEntry))), NULL);
      defineMethodObject("(DEFMETHOD REMOVE-ENTRY ((SELF KEY-VALUE-LIST) (KEY (LIKE (ANY-KEY SELF))) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE :DOCUMENTATION \"Remove the entry that matches <`key',`value'>.\nAssumes that more than one entry can match `key'.\")", wrapMethodCode(((cpp_method_code)(&KeyValueList::removeEntry))), NULL);
      defineMethodObject("(DEFMETHOD PUSH ((SELF KEY-VALUE-LIST) (VALUE KV-CONS)) :DOCUMENTATION \"Make `value' be the new first element of `self'.  Note that\nthe `rest' slot of `value' should be `null', since it will be overwritten.\nThis might duplicate an existing entry. If a previous entry existed with the\nsame key as `value', that entry is retained, but shadowed by this new entry.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueList::push))), NULL);
      defineMethodObject("(DEFMETHOD KV-PUSH ((SELF KEY-VALUE-LIST) (KEY (LIKE (ANY-KEY SELF))) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Add a new entry <`key', `value'> to the front of the association\n`self'. This might duplicate an existing entry. If a previous entry existed with key\n`key', that entry is retained, but shadowed by this new entry.\")", wrapMethodCode(((cpp_method_code)(&KeyValueList::kvPush))), NULL);
      defineMethodObject("(DEFMETHOD (POP (LIKE (ANY-VALUE SELF))) ((SELF KEY-VALUE-LIST)) :DOCUMENTATION \"Remove and return the value of the first element of the\nkv-list `self'.  It does NOT return the KV-CONS object.  Return `null' if\nthe list is empty.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueList::pop))), NULL);
      defineMethodObject("(DEFMETHOD (REVERSE (LIKE SELF)) ((SELF KEY-VALUE-LIST)) :DOCUMENTATION \"Destructively reverse the members of the list `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueList::reverse))), NULL);
      defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF KEY-VALUE-LIST)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueList::emptyP))), NULL);
      defineMethodObject("(DEFMETHOD (NON-EMPTY? BOOLEAN) ((SELF KEY-VALUE-LIST)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueList::nonEmptyP))), NULL);
      defineFunctionObject("COPY-KV-CONS-LIST", "(DEFUN (COPY-KV-CONS-LIST KV-CONS) ((KVCONSLIST KV-CONS)) :DOCUMENTATION \"Return a copy of the cons list `consList'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&copyKvConsList)), NULL);
      defineMethodObject("(DEFMETHOD (COPY (LIKE SELF)) ((SELF KEY-VALUE-LIST)) :DOCUMENTATION \"Return a copy of the kv-list `self'.  The kv-conses in\nthe copy are freshly allocated.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueList::copy))), NULL);
      defineMethodObject("(DEFMETHOD CLEAR ((SELF KEY-VALUE-LIST)) :DOCUMENTATION \"Make `self' an empty dictionary.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueList::clear))), NULL);
      defineMethodObject("(DEFMETHOD (OBJECT-EQUAL? BOOLEAN) ((X KEY-VALUE-LIST) (Y OBJECT)) :DOCUMENTATION \"Return TRUE if `x' and `y' represent the same set of key/value pairs.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueList::objectEqualP))), NULL);
      defineMethodObject("(DEFMETHOD (EQUAL-HASH-CODE INTEGER) ((SELF KEY-VALUE-LIST)) :DOCUMENTATION \"Return an `equal?' hash code for `self'.  Note that this\nis O(N) in the number of entries of `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueList::equalHashCode))), NULL);
      defineMethodObject("(DEFMETHOD (ALLOCATE-ITERATOR (KV-LIST-ITERATOR OF (LIKE (ANY-KEY SELF)) (LIKE (ANY-VALUE SELF)))) ((SELF KEY-VALUE-LIST)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueList::allocateIterator))), NULL);
      defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF KV-LIST-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KvListIterator::nextP))), NULL);
      defineMethodObject("(DEFMETHOD (VALUE-SETTER (LIKE (ANY-VALUE SELF))) ((SELF KV-LIST-ITERATOR) (VALUE (LIKE (ANY-VALUE SELF)))) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KvListIterator::valueSetter))), NULL);
      defineMethodObject("(DEFMETHOD (KEY-SETTER OBJECT) ((SELF KV-LIST-ITERATOR) (KEY OBJECT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KvListIterator::keySetter))), NULL);
      defineFunctionObject("KVLIST-TO-PLIST", "(DEFUN (KVLIST-TO-PLIST (PROPERTY-LIST OF (LIKE (ANY-KEY SELF)) (LIKE (ANY-VALUE SELF)))) ((SELF KEY-VALUE-LIST)) :DOCUMENTATION \"Convert `self' into a property list with identical and identically\nordered keys and values.\" :PUBLIC? TRUE)", ((cpp_function_code)(&kvlistToPlist)), NULL);
      defineFunctionObject("PLIST-TO-KVLIST", "(DEFUN (PLIST-TO-KVLIST (KEY-VALUE-LIST OF (LIKE (ANY-KEY SELF)) (LIKE (ANY-VALUE SELF)))) ((SELF PROPERTY-LIST)) :DOCUMENTATION \"Convert `self' into a key-value list with identical and identically\nordered keys and values.\" :PUBLIC? TRUE)", ((cpp_function_code)(&plistToKvlist)), NULL);
      defineMethodObject("(DEFMETHOD (MEMBER? BOOLEAN) ((SELF SEQUENCE) (VALUE OBJECT)) :DOCUMENTATION \"Return TRUE if `value' is a member of the sequence `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Sequence::memberP))), NULL);
      defineFunctionObject("LIST", "(DEFUN (LIST LIST) (|&REST| (VALUES OBJECT)) :DOCUMENTATION \"Return a list containing `values', in order.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&list)), NULL);
      defineFunctionObject("SEQUENCE", "(DEFUN (SEQUENCE (SEQUENCE OF OBJECT)) ((COLLECTIONTYPE TYPE) |&REST| (VALUES OBJECT)) :DOCUMENTATION \"Return a sequence containing `values', in order.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&sequence)), NULL);
      defineFunctionObject("DICTIONARY", "(DEFUN (DICTIONARY (ABSTRACT-DICTIONARY OF OBJECT OBJECT)) ((COLLECTIONTYPE TYPE) |&REST| (ALTERNATINGKEYSANDVALUES OBJECT)) :DOCUMENTATION \"Return a dictionary of `collectionType' containing `values', in order.\nCurrently supported `collectionType's are @HASH-TABLE, @STELLA-HASH-TABLE,\n@KEY-VALUE-LIST, @KEY-VALUE-MAP and @PROPERTY-LIST.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&dictionary)), NULL);
      defineMethodObject("(DEFMETHOD (LISTIFY (LIST OF (LIKE (ANY-VALUE SELF)))) ((SELF LIST)) :DOCUMENTATION \"Return `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::listify))), NULL);
      defineMethodObject("(DEFMETHOD (LISTIFY (LIST OF (LIKE (ANY-VALUE SELF)))) ((SELF CONS)) :DOCUMENTATION \"Return a list of elements in `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::listify))), NULL);
      defineMethodObject("(DEFMETHOD (LISTIFY (LIST OF (LIKE (ANY-VALUE SELF)))) ((SELF KEY-VALUE-LIST)) :DOCUMENTATION \"Return a list of key-value pairs in `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&KeyValueList::listify))), NULL);
      defineMethodObject("(DEFMETHOD (LISTIFY (LIST OF (LIKE (ANY-VALUE SELF)))) ((SELF VECTOR)) :DOCUMENTATION \"Return a list of elements in `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Vector::listify))), NULL);
      defineMethodObject("(DEFMETHOD (LISTIFY (LIST OF (LIKE (ANY-VALUE SELF)))) ((SELF ITERATOR)) :DOCUMENTATION \"Return a list of elements generated by `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Iterator::listify))), NULL);
      defineFunctionObject("PRINT-KEY-VALUE-LIST", "(DEFUN PRINT-KEY-VALUE-LIST ((SELF KEY-VALUE-LIST) (STREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&printKeyValueList)), NULL);
      defineFunctionObject("STARTUP-LISTS", "(DEFUN STARTUP-LISTS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupLists)), NULL);
      { MethodSlot* function = lookupFunction(SYM_LISTS_STELLA_STARTUP_LISTS);

        setDynamicSlotValue(function->dynamicSlots, SYM_LISTS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupLists"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL NIL-LIST LIST NULL :PUBLIC? TRUE)", &NIL_LIST);
    }
  }
}

Surrogate* SGT_LISTS_STELLA_LIST = NULL;

Surrogate* SGT_LISTS_STELLA_SET = NULL;

Surrogate* SGT_LISTS_STELLA_PROPERTY_LIST = NULL;

Surrogate* SGT_LISTS_STELLA_KEY_VALUE_LIST = NULL;

Surrogate* SGT_LISTS_STELLA_HASH_TABLE = NULL;

Surrogate* SGT_LISTS_STELLA_STELLA_HASH_TABLE = NULL;

Surrogate* SGT_LISTS_STELLA_KEY_VALUE_MAP = NULL;

Symbol* SYM_LISTS_STELLA_STARTUP_LISTS = NULL;

Symbol* SYM_LISTS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
