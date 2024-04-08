//  -*- Mode: C++ -*-

// hierarchy.hh

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
class Object : public gc {
// A reflective object that can participate in dynamically-typed
// contexts.  Either a STANDARD-OBJECT or a WRAPPER or a GENERIC-OBJECT.
// Also, either an OBJECT-WITH-INHERITED-TYPE or an OBJECT-WITH-OWN-TYPE.
public:
  virtual void printObject(std::ostream* stream);
  virtual void helpPrintOutline(OutputStream* stream, int currentDepth, int depth, boolean namedP);
  virtual void idlOutputLiteral();
  virtual Cons* idlTranslateAtomicTree();
  virtual void javaOutputLiteral();
  virtual Cons* javaTranslateAtomicTree();
  virtual void cppOutputLiteral();
  virtual Cons* cppTranslateAtomicTree();
  virtual void describeObject(OutputStream* stream, Keyword* mode);
  virtual Object* getObject(Object* type);
  virtual Object* clTranslateAtomicTree();
  virtual Object* walkAtomicTree(StandardObject*& _Return1);
  virtual void sweep();
  virtual StandardObject* yieldTypeSpecifier();
  virtual Iterator* publicSlots();
  virtual void free();
  virtual Class* primaryClass();
  virtual Surrogate* surrogatify();
  virtual double numberWrapperToFloat();
  virtual Object* permanentify();
  virtual boolean objectEqlP(Object* y);
  virtual Cons* consify();
  virtual boolean standardObjectP();
  virtual int equalHashCode();
  virtual int hashCode();
  virtual boolean objectEqualP(Object* y);
  virtual Surrogate* primaryType();
  virtual Module* homeModule();
  virtual boolean deletedP();
  virtual void incrementReferenceCount();
  virtual void decrementReferenceCount();
};

class StandardObject : public Object {
// Object that used to find its type stored in a :class slot.
// By reimplementing `primary-type' as a method, the justification for this
// class went away, but we'll keep it for now to keep things working.
public:
  virtual boolean objectEqlP(Object* y);
  virtual Object* copyWrappedLiteral();
  virtual boolean standardObjectP();
  virtual int hashCode();
};

class ReferenceCountObject : public Object {
// A reference count objects contains a slot `reference-count' 
// that is incremented whenever the object is assigned to a slot, and decremented
// whenever it is deassigned from a slot.
public:
  int referenceCount;
public:
  virtual void incrementReferenceCount();
  virtual void decrementReferenceCount();
};

class ContextSensitiveObject : public StandardObject {
// Context sensitive objects inherit a slot `home-context'
// that enables context-dependent access machinery to determine the
// visibility of objects from modules.
public:
  Context* homeContext;
public:
  virtual Module* homeModule();
};

class ActiveObject : public ContextSensitiveObject {
// Active objects call class and slot triggers in response
// to instance creation/destruction and slot updates.  They include internal
// storage slots needed for class extensions, dynamic storage, and home context.
public:
  KeyValueList* dynamicSlots;
public:
  virtual void free();
  virtual boolean deletedPSetter(boolean value);
  virtual boolean deletedP();
  virtual BooleanWrapper* badP_reader();
};

class AbstractIterator : public StandardObject {
// Instances of ABSTRACT-ITERATOR support iteration over collections.
public:
  boolean firstIterationP;
public:
  virtual AbstractIterator* allocateIterator();
  virtual boolean nextP();
  virtual int length();
};

class Iterator : public AbstractIterator {
// Instances of ITERATOR support iteration over 
// collections of OBJECTs.
public:
  // The current value of this iterator
  Object* value;
public:
  virtual AllPurposeIterator* concatenate(Iterator* iterator2, int otheriterators, ...);
  virtual boolean memberP(Object* value);
  virtual boolean emptyP();
  virtual Iterator* advance(int n);
  virtual Object* pop();
  virtual List* listify();
  virtual Cons* consify();
};

class ConsIterator : public Iterator {
// Iterator class for the class CONS.
public:
  Cons* consIteratorCursor;
public:
  virtual void free();
  virtual Object* valueSetter(Object* value);
  virtual boolean memberP(Object* value);
  virtual int length();
  virtual boolean emptyP();
  virtual boolean nextP();
  virtual Surrogate* primaryType();
};

class ListIterator : public Iterator {
// Iterator class for the collection LIST.
public:
  Cons* listIteratorCursor;
  List* listIteratorCollection;
public:
  virtual void free();
  virtual Object* valueSetter(Object* value);
  virtual boolean emptyP();
  virtual boolean nextP();
  virtual Surrogate* primaryType();
};

class DestructiveListIterator : public Iterator {
// An iterator that contains a cons list.  Iterates over
// the stored list, and destroys it when the iterator is free'd.
public:
  Cons* theConsList;
  Cons* listIteratorCursor;
public:
  virtual void free();
  virtual void insert(Object* value);
  virtual boolean emptyP();
  virtual boolean nextP();
  virtual Surrogate* primaryType();
};

class AllPurposeIterator : public Iterator {
// The all-purpose iterator works by storing a `next?'
// function within itself during iterator allocation.  The method
// `ALL-PURPOSE-ITERAOR.next?' funcalls the stored `next?' function.
// An assortment of storage slots are provided for constructing different
// kinds of iterators.
public:
  Object* key;
  cpp_function_code iteratorNextCode;
  cpp_function_code iteratorFilterCode;
  cpp_function_code iteratorEmptyCode;
  Iterator* iteratorNestedIterator;
  Cons* iteratorConsList;
  Object* iteratorObject;
  Object* iteratorSecondObject;
  int iteratorInteger;
  int iteratorSecondInteger;
public:
  virtual void free();
  virtual boolean terminateAllPurposeIteratorP();
  virtual boolean emptyP();
  virtual boolean nextP();
  virtual Surrogate* primaryType();
};

class TypesToClassesIterator : public Iterator {
// Iterator that returns a class for each type
// in a cons list of types.
public:
  Cons* iteratorCursor;
public:
  virtual Surrogate* primaryType();
  virtual boolean nextP();
};

class AbstractDictionaryIterator : public AbstractIterator {
// Instances of ABSTRACT-DICTIONARY-ITERATOR support iteration
// over dictionaries.
};

class DictionaryIterator : public AbstractDictionaryIterator {
// Instances of DICTIONARY-ITERATOR support iteration
// over dictionaries with keys and values of type OBJECT.
public:
  Object* key;
  // The current value of this iterator
  Object* value;
public:
  virtual Object* valueSetter(Object* value);
  virtual Object* keySetter(Object* key);
};

class PropertyListIterator : public DictionaryIterator {
// Iterator class for the collection PROPERTY-LIST.
public:
  Cons* plistIteratorCursor;
  PropertyList* plistIteratorCollection;
public:
  virtual Object* keySetter(Object* key);
  virtual Object* valueSetter(Object* value);
  virtual boolean nextP();
  virtual Surrogate* primaryType();
};

class KvListIterator : public DictionaryIterator {
public:
  KeyValueList* theKvList;
  KvCons* kvListIteratorCursor;
public:
  virtual Object* keySetter(Object* key);
  virtual Object* valueSetter(Object* value);
  virtual boolean nextP();
  virtual Surrogate* primaryType();
};

class IntervalIterator : public AbstractIterator {
// An iterator that specifies a (possibly infinite) range of
// values.  Supports `member?' test as well as iteration methods.
};

class IntegerIntervalIterator : public IntervalIterator {
public:
  int intervalCursor;
  int lowerBound;
  int upperBound;
  // The current value of this iterator
  int value;
public:
  virtual ReverseIntegerIntervalIterator* reverse();
  virtual boolean nextP();
  virtual void initializeIntegerIntervalIterator();
  virtual Surrogate* primaryType();
};

class ReverseIntegerIntervalIterator : public IntervalIterator {
public:
  int intervalCursor;
  int lowerBound;
  int upperBound;
  // The current value of this iterator
  int value;
public:
  virtual boolean nextP();
  virtual Surrogate* primaryType();
};

class StringIterator : public AbstractIterator {
// Iterator that yields characters from a string.
public:
  const char* theString;
  int cursor;
  int end;
  // The current value of this iterator
  char value;
public:
  virtual boolean nextP();
  virtual Surrogate* primaryType();
};

class AbstractCollection : public StandardObject {
public:
  virtual AbstractIterator* allocateIterator();
  virtual int length();
};

class Collection : public AbstractCollection {
public:
  virtual boolean orderedP();
  virtual boolean noDuplicatesP();
  virtual boolean memberP(Object* object);
  virtual AbstractIterator* allocateIterator();
  virtual int length();
  virtual void insert(Object* value);
  virtual AbstractCollection* remove(Object* value);
};

class Sequence : public Collection {
public:
  virtual boolean orderedP();
  virtual boolean memberP(Object* value);
  virtual AbstractIterator* allocateIterator();
  virtual int length();
};

class List : public Sequence {
public:
  Cons* theConsList;
public:
  virtual void printObject(std::ostream* stream);
  virtual Iterator* allocateDestructiveListIterator();
  virtual List* listify();
  virtual List* subtract(List* otherlist);
  virtual List* difference(List* otherlist);
  virtual List* unioN(List* otherlist);
  virtual List* intersection(List* otherlist);
  virtual boolean equivalentSetsP(List* otherlist);
  virtual boolean subsetP(List* otherlist);
  virtual List* removeDeletedMembers();
  virtual Iterator* butLast();
  virtual AbstractIterator* allocateIterator();
  virtual int equalHashCode();
  virtual boolean objectEqualP(Object* y);
  virtual List* sort(cpp_function_code predicate);
  virtual void clear();
  virtual List* copy();
  virtual List* prepend(List* list2);
  virtual List* concatenate(List* list2, int otherlists, ...);
  virtual List* substitute(Object* invalue, Object* outvalue);
  virtual List* reverse();
  virtual Object* pop();
  virtual List* removeDuplicatesEqual();
  virtual Collection* removeDuplicates();
  virtual List* removeIf(cpp_function_code testP);
  virtual AbstractCollection* remove(Object* value);
  virtual void insertLast(Object* value);
  virtual void insertNew(Object* value);
  virtual void push(Object* value);
  virtual void insert(Object* value);
  virtual int lastPosition(Object* object, int end);
  virtual int position(Object* object, int start);
  virtual int length();
  virtual Object* nthSetter(Object* value, int position);
  virtual Object* fifthSetter(Object* value);
  virtual Object* fourthSetter(Object* value);
  virtual Object* thirdSetter(Object* value);
  virtual Object* secondSetter(Object* value);
  virtual Object* firstSetter(Object* value);
  virtual Cons* rest();
  virtual Object* last();
  virtual Object* nth(int position);
  virtual Object* fifth();
  virtual Object* fourth();
  virtual Object* third();
  virtual Object* second();
  virtual Object* first();
  virtual boolean membP(Object* object);
  virtual boolean memberP(Object* object);
  virtual boolean nonEmptyP();
  virtual boolean emptyP();
  virtual Cons* consify();
  virtual Surrogate* primaryType();
};

class Set : public List {
public:
  virtual void printObject(std::ostream* stream);
  virtual int equalHashCode();
  virtual boolean objectEqualP(Object* y);
  virtual List* concatenate(List* set2, int othersets, ...);
  virtual List* substitute(Object* neW, Object* old);
  virtual Collection* removeDuplicates();
  virtual void insertLast(Object* value);
  virtual void push(Object* value);
  virtual void insert(Object* value);
  virtual boolean orderedP();
  virtual boolean noDuplicatesP();
  virtual Surrogate* primaryType();
};

class ClassExtension : public List {
public:
  virtual Surrogate* primaryType();
};

class Cons : public StandardObject {
public:
  Object* value;
  Cons* rest;
public:
  virtual void printObject(std::ostream* stream);
  virtual void javaOutputLiteral();
  virtual void cppOutputLiteral();
  virtual StandardObject* yieldTypeSpecifier();
  virtual Iterator* allocateDestructiveListIterator();
  virtual List* listify();
  virtual int equalHashCode();
  virtual boolean objectEqualP(Object* tree2);
  virtual Cons* sortObjects(StorageSlot* slot, cpp_function_code predicate);
  virtual Cons* sortTuples(int n, cpp_function_code predicate);
  virtual Cons* sort(cpp_function_code predicate);
  virtual Cons* subtract(Cons* otherlist);
  virtual Cons* difference(Cons* otherlist);
  virtual Cons* unioN(Cons* otherlist);
  virtual Cons* intersection(Cons* otherlist);
  virtual boolean disjointSetsP(Cons* otherlist);
  virtual boolean equivalentSetsP(Cons* otherlist);
  virtual boolean subsetP(Cons* otherlist);
  virtual Cons* removeDeletedMembers();
  virtual Cons* consify();
  virtual Iterator* butLast();
  virtual Object* nthRestSetter(Object* value, int position);
  virtual Object* fifthSetter(Object* value);
  virtual Object* fourthSetter(Object* value);
  virtual Object* nthSetter(Object* value, int position);
  virtual Object* thirdSetter(Object* value);
  virtual Object* secondSetter(Object* value);
  virtual Object* firstSetter(Object* value);
  virtual Object* last();
  virtual Cons* nthRest(int position);
  virtual Object* nth(int position);
  virtual Object* fifth();
  virtual Object* fourth();
  virtual Object* third();
  virtual Object* second();
  virtual Object* first();
  virtual Cons* substitute(Object* invalue, Object* outvalue);
  virtual Cons* reverse();
  virtual Cons* prepend(Cons* list1);
  virtual Cons* concatenate(Cons* list2, int otherlists, ...);
  virtual Cons* removeDuplicatesEqual();
  virtual Cons* removeDuplicates();
  virtual Cons* removeIf(cpp_function_code testP);
  virtual Cons* remove(Object* value);
  virtual boolean membP(Object* object);
  virtual boolean memberP(Object* object);
  virtual int lastPosition(Object* object, int end);
  virtual int position(Object* object, int start);
  virtual int length();
  virtual boolean nonEmptyP();
  virtual boolean emptyP();
  virtual Surrogate* primaryType();
  virtual ConsIterator* allocateIterator();
};

class AbstractDictionary : public AbstractCollection {
public:
  virtual AbstractIterator* allocateIterator();
};

class Dictionary : public AbstractDictionary {
public:
  virtual AbstractIterator* allocateIterator();
  virtual Object* lookup(Object* key);
  virtual void insertAt(Object* key, Object* value);
};

class PropertyList : public Dictionary {
public:
  Cons* thePlist;
public:
  virtual void printObject(std::ostream* stream);
  virtual AbstractIterator* allocateIterator();
  virtual int equalHashCode();
  virtual boolean objectEqualP(Object* y);
  virtual void clear();
  virtual PropertyList* copy();
  virtual boolean nonEmptyP();
  virtual boolean emptyP();
  virtual Object* removeAt(Object* key);
  virtual void insertAt(Object* key, Object* value);
  virtual int length();
  virtual Object* lookupWithDefault(Object* key, Object* defaulT);
  virtual Object* lookup(Object* key);
  virtual void initializeObject();
  virtual Surrogate* primaryType();
};

class KvCons : public StandardObject {
public:
  Object* key;
  Object* value;
  KvCons* rest;
public:
  virtual void printObject(std::ostream* stream);
  virtual int length();
  virtual Object* lookup(Object* key);
  virtual Surrogate* primaryType();
};

class KeyValueList : public Dictionary {
public:
  KvCons* theKvList;
public:
  virtual void printObject(std::ostream* stream);
  virtual List* listify();
  virtual AbstractIterator* allocateIterator();
  virtual int equalHashCode();
  virtual boolean objectEqualP(Object* y);
  virtual void clear();
  virtual KeyValueList* copy();
  virtual boolean nonEmptyP();
  virtual boolean emptyP();
  virtual KeyValueList* reverse();
  virtual Object* pop();
  virtual void kvPush(Object* key, Object* value);
  virtual void push(KvCons* value);
  virtual void removeEntry(Object* key, Object* value);
  virtual void insertEntry(Object* key, Object* value);
  virtual Object* removeAt(Object* key);
  virtual void insertAt(Object* key, Object* value);
  virtual int length();
  virtual Object* lookupWithDefault(Object* key, Object* defaulT);
  virtual Object* lookup(Object* key);
  virtual Cons* consify();
  virtual Surrogate* primaryType();
};

class RecycleList : public Sequence {
public:
  Surrogate* recycleListOf;
  Object* recycledItems;
  List* listOfRecycledItems;
  Object* allItems;
  Object* unusedItems;
  int currentLength;
  int itemSize;
public:
  virtual void printObject(std::ostream* stream);
  virtual boolean deletedPSetter(boolean value);
  virtual boolean deletedP();
  virtual Surrogate* primaryType();
};

class AbstractHashTable : public AbstractDictionary {
public:
  cpp_hash_table* theHashTable;
  StellaHashTable* theStellaHashTable;
public:
  virtual void initializeHashTable();
  virtual void freeHashTableValues();
};

class HashTable : public AbstractHashTable {
public:
  virtual void removeAt(Object* key);
  virtual void insertAt(Object* key, Object* value);
  virtual Object* lookup(Object* key);
  virtual Surrogate* primaryType();
};

class IntegerHashTable : public AbstractHashTable {
public:
  virtual void removeAt(int key);
  virtual void insertAt(int key, Object* value);
  virtual Object* lookup(int key);
  virtual void initializeHashTable();
  virtual Surrogate* primaryType();
};

class FloatHashTable : public AbstractHashTable {
public:
  virtual void removeAt(double key);
  virtual void insertAt(double key, Object* value);
  virtual Object* lookup(double key);
  virtual void initializeHashTable();
  virtual Surrogate* primaryType();
};

class StringHashTable : public AbstractHashTable {
public:
  virtual void removeAt(const char* key);
  virtual void insertAt(const char* key, Object* value);
  virtual Object* lookup(const char* key);
  virtual void initializeHashTable();
  virtual Surrogate* primaryType();
};

class StringToIntegerHashTable : public AbstractHashTable {
public:
  virtual void removeAt(const char* key);
  virtual void insertAt(const char* key, int value);
  virtual int lookup(const char* key);
  virtual void initializeHashTable();
  virtual Surrogate* primaryType();
};

class Vector : public Sequence {
public:
  int arraySize;
  Object** theArray;
public:
  virtual void printObject(std::ostream* stream);
  virtual Vector* sortObjects(StorageSlot* slot, cpp_function_code predicate);
  virtual Vector* sortTuples(int n, cpp_function_code predicate);
  virtual Vector* sort(cpp_function_code predicate);
  virtual Iterator* butLast();
  virtual AbstractIterator* allocateIterator();
  virtual int equalHashCode();
  virtual boolean objectEqualP(Object* y);
  virtual void clear();
  virtual Vector* copy();
  virtual void insertAt(int offset, Object* value);
  virtual int lastPosition(Object* object, int end);
  virtual int position(Object* object, int start);
  virtual boolean memberP(Object* object);
  virtual int length();
  virtual Object* lastSetter(Object* value);
  virtual Object* nthSetter(Object* value, int position);
  virtual Object* fifthSetter(Object* value);
  virtual Object* fourthSetter(Object* value);
  virtual Object* thirdSetter(Object* value);
  virtual Object* secondSetter(Object* value);
  virtual Object* firstSetter(Object* value);
  virtual Object* last();
  virtual Object* nth(int position);
  virtual Object* fifth();
  virtual Object* fourth();
  virtual Object* third();
  virtual Object* second();
  virtual Object* first();
  virtual boolean nonEmptyP();
  virtual boolean emptyP();
  virtual void printVector(std::ostream* stream);
  virtual List* listify();
  virtual Cons* consify();
  virtual void initializeVector();
  virtual Surrogate* primaryType();
};

class ExtensibleVector : public Vector {
public:
  virtual void insertAt(int offset, Object* value);
  virtual Surrogate* primaryType();
};

class ExtensibleSymbolArray : public ExtensibleVector {
// Self-extending array with methods for storing and
// accessing symbols within it.
public:
  int topSymbolOffset;
  int potentialFreeSymbolOffset;
public:
  virtual void insertAt(int offset, Object* value);
  virtual Surrogate* primaryType();
};

class VectorSequence : public Vector {
// Extensible sequence implemented by a vector.  Whenever we run
// out of room, we grow the sequence by a factor of two.  Note that this keeps the
// average insertion cost per element constant.  This is generally preferable over
// linked lists unless we need within-list insertions or removals, since it uses
// less space and has better cache locality.
public:
  int sequenceLength;
public:
  virtual boolean objectEqualP(Object* y);
  virtual void clear();
  virtual Vector* copy();
  virtual VectorSequence* reverse();
  virtual AbstractCollection* remove(Object* value);
  virtual void insert(Object* value);
  virtual Object* lastSetter(Object* value);
  virtual Object* last();
  virtual int length();
  virtual boolean nonEmptyP();
  virtual boolean emptyP();
  virtual Surrogate* primaryType();
};

class CustomVectorSequence : public VectorSequence {
// VECTOR-SEQUENCE (which see) with a customizable resize factor.
// The resize factor needs to be > 1.
public:
  double resizeFactor;
public:
  virtual Vector* copy();
  virtual void insert(Object* value);
  virtual Surrogate* primaryType();
};

class BooleanVector : public Vector {
public:
  virtual Surrogate* primaryType();
};

class IntegerVector : public Vector {
public:
  virtual Surrogate* primaryType();
};

class ActiveList : public List {
public:
  StorageSlot* activeSlot;
  StandardObject* ownerInstance;
public:
  virtual AbstractCollection* remove(Object* value);
  virtual void insert(Object* value);
  virtual Surrogate* primaryType();
};

class ActiveSet : public List {
public:
  StorageSlot* activeSlot;
  StandardObject* ownerInstance;
public:
  virtual AbstractCollection* remove(Object* value);
  virtual void insert(Object* value);
  virtual Surrogate* primaryType();
};

class Demon : public StandardObject {
public:
  const char* demonName;
  Keyword* demonAction;
  List* demonClassRefs;
  List* demonSlotRefs;
  cpp_function_code demonCode;
  MethodSlot* demonMethod;
  const char* demonDocumentation;
  boolean demonGuardP;
  boolean demonAllP;
  boolean demonInheritP;
public:
  virtual Surrogate* primaryType();
};

class KeywordKeyValueList : public KeyValueList {
public:
  virtual Surrogate* primaryType();
};

class GeneralizedSymbol : public ContextSensitiveObject {
public:
  const char* symbolName;
  int symbolId;
public:
  virtual GlobalVariable* lookupGlobalVariable();
  virtual const char* visibleName(boolean readableP);
  virtual const char* absoluteName(boolean readableP);
  virtual const char* relativeName(boolean readableP);
  virtual const char* localPrintName(boolean readableP);
  virtual Keyword* keywordify();
  virtual boolean deletedP();
};

class Symbol : public GeneralizedSymbol {
public:
  int symbolSlotOffset;
  Cons* symbolValueAndPlist;
public:
  virtual void printObject(std::ostream* stream);
  virtual void idlOutputLiteral();
  virtual Cons* idlTranslateAtomicTree();
  virtual void javaOutputLiteral();
  virtual Cons* javaTranslateAtomicTree();
  virtual void cppOutputLiteral();
  virtual Cons* cppTranslateAtomicTree();
  virtual Context* getStellaContextSlowly();
  virtual Object* clTranslateAtomicTree();
  virtual Object* walkAtomicTree(StandardObject*& _Return1);
  virtual StandardObject* yieldTypeSpecifier();
  virtual Class* getStellaClass(boolean errorP);
  virtual Class* lookupClass();
  virtual Surrogate* surrogatify();
  virtual Symbol* softPermanentify();
  virtual Object* permanentify();
  virtual Surrogate* primaryType();
};

class Surrogate : public GeneralizedSymbol {
// Rigid surrogate.
public:
  Object* surrogateValue;
public:
  virtual void printObject(std::ostream* stream);
  virtual void idlOutputLiteral();
  virtual void javaOutputLiteral();
  virtual void cppOutputLiteral();
  virtual Cons* cppTranslateAtomicTree();
  virtual Object* clTranslateAtomicTree();
  virtual Object* walkAtomicTree(StandardObject*& _Return1);
  virtual Surrogate* typeToWrappedType();
  virtual GlobalVariable* lookupGlobalVariable();
  virtual StandardObject* yieldTypeSpecifier();
  virtual void destroyClass();
  virtual Class* getStellaClass(boolean errorP);
  virtual const char* localPrintName(boolean readableP);
  virtual Surrogate* surrogatify();
  virtual Surrogate* primaryType();
};

class Keyword : public GeneralizedSymbol {
public:
  virtual void printObject(std::ostream* stream);
  virtual void idlOutputLiteral();
  virtual void javaOutputLiteral();
  virtual void cppOutputLiteral();
  virtual Cons* cppTranslateAtomicTree();
  virtual Object* clTranslateAtomicTree();
  virtual Object* walkAtomicTree(StandardObject*& _Return1);
  virtual Keyword* keywordify();
  virtual Surrogate* primaryType();
};

class TransientSymbol : public Symbol {
public:
  virtual Symbol* softPermanentify();
  virtual Object* permanentify();
  virtual Surrogate* primaryType();
  virtual boolean transientP_reader();
};

class MappableObject : public StandardObject {
// The class MAPPABLE-OBJECT enables the definition of projections
// from a Stella class, slot, global variable, etc. onto a corresponding native
// entity.
public:
  KeyValueList* dynamicSlots;
public:
  virtual boolean deletedPSetter(boolean value);
  virtual boolean deletedP();
  virtual BooleanWrapper* badP_reader();
  virtual List* projectedFrom_reader();
  virtual List* projectsOnto_reader();
};

class Relation : public MappableObject {
public:
  boolean abstractP;
public:
  virtual boolean privateP();
  virtual boolean primitiveP();
  virtual const char* name();
  virtual Module* homeModule();
  virtual int arity();
  virtual boolean publicP();
  virtual List* directSupers();
  virtual List* allSupers();
  virtual Iterator* slots();
  virtual List* properties_reader();
};

class Class : public Relation {
public:
  boolean clStructP;
  boolean mixinP;
  Surrogate* classType;
  List* classDirectSupers;
  List* classDirectSubs;
  Cons* classAllSuperClasses;
  Cons* classAllSlots;
  List* classLocalSlots;
  Vector* classSlotAndMethodCache;
  boolean classCollectionP;
  boolean classPublicP;
  boolean classFinalizedP;
  boolean classSlotsFinalizedP;
  const char* classStringifiedSource;
  cpp_function_code classConstructorCode;
  cpp_function_code classSlotAccessorCode;
  boolean classMarkedP;
  TaxonomyNode* classTaxonomyNode;
public:
  virtual void printObject(std::ostream* stream);
  virtual void helpPrintOutline(OutputStream* stream, int currentDepth, int depth, boolean namedP);
  virtual const char* javaMakeCodeOutputFileName(boolean donttruncateP);
  virtual void describeObject(OutputStream* stream, Keyword* mode);
  virtual void prettyPrintObject(OutputStream* stream);
  virtual Iterator* superClasses();
  virtual Iterator* directSuperClasses();
  virtual List* localSlots();
  virtual Iterator* classSlots();
  virtual Iterator* allClassSlots();
  virtual Iterator* publicSlots();
  virtual boolean multipleParentsP();
  virtual void destroyClass();
  virtual void unbindFromSurrogate();
  virtual Surrogate* primaryType();
  virtual const char* name();
  virtual Module* homeModule();
  virtual int arity();
  virtual boolean publicP();
  virtual boolean activeP();
  virtual Symbol* creator();
  virtual Symbol* initializer();
  virtual Symbol* terminator();
  virtual Symbol* destructor();
  virtual List* requiredSlots();
  virtual List* parameters();
  virtual Object* initialValue();
  virtual ClassExtension* extension();
  virtual const char* clNativeType();
  virtual const char* cppNativeType();
  virtual const char* idlNativeType();
  virtual const char* javaNativeType();
  virtual List* classAuxiliaryMethods_reader();
  virtual List* classSynonyms_reader();
  virtual List* classKey_reader();
  virtual List* classDestructorDemons_reader();
  virtual List* classGuardDestructorDemons_reader();
  virtual List* classConstructorDemons_reader();
  virtual List* classGuardConstructorDemons_reader();
  virtual List* classRequiredSlotNames_reader();
  virtual List* classParameters_reader();
  virtual Keyword* classRecycleMethod_reader();
  virtual List* classClStructSlots_reader();
  virtual int classArity_reader();
};

class PolymorphicRelation : public Relation {
public:
  Slot* slotDirectEquivalent;
public:
  virtual Surrogate* owner();
  virtual Symbol* renames();
  virtual boolean activeP();
};

class Slot : public PolymorphicRelation {
public:
  Symbol* slotName;
  Surrogate* slotOwner;
  Surrogate* slotBaseType;
  Surrogate* slotSlotref;
  boolean slotPublicP;
  boolean slotRenamedP;
  boolean slotExternalP;
  boolean slotMarkedP;
public:
  virtual void printObject(std::ostream* stream);
  virtual void helpPrintOutline(OutputStream* stream, int currentDepth, int depth, boolean namedP);
  virtual void prettyPrintObject(OutputStream* stream);
  virtual Object* finishWalkingCallSlotTree(Cons* tree, StandardObject* firstargtype, StandardObject*& _Return1);
  virtual StandardObject* computeReturnTypeSpec(StandardObject* firstargtype);
  virtual int methodArgumentCount();
  virtual Object* systemDefaultValue();
  virtual boolean activeP();
  virtual boolean publicP();
  virtual boolean conformingSignaturesP(Slot* superslot);
  virtual void unfinalizeLocalSlot();
  virtual void helpFinalizeLocalSlot();
  virtual void finalizeSlotTypeComputations();
  virtual const char* name();
  virtual Surrogate* type();
  virtual StandardObject* typeSpecifier();
  virtual Surrogate* owner();
  virtual Module* homeModule();
  virtual Symbol* renames();
  virtual boolean collectionValuedP();
  virtual Keyword* closureAssumption();
  virtual List* slotDirectSubs_reader();
  virtual List* slotDirectSupers_reader();
};

class StorageSlot : public Slot {
public:
  boolean slotRequiredP;
  boolean slotComponentP;
  boolean slotReadOnlyP;
  boolean slotHardwiredP;
  boolean slotContextSensitiveP;
public:
  virtual void describeObject(OutputStream* stream, Keyword* mode);
  virtual void prettyPrintObject(OutputStream* stream);
  virtual Object* finishWalkingCallSlotTree(Cons* tree, StandardObject* firstargtype, StandardObject*& _Return1);
  virtual StandardObject* computeReturnTypeSpec(StandardObject* firstargtype);
  virtual int arity();
  virtual boolean methodBodyArgumentP();
  virtual boolean methodVariableArgumentsP();
  virtual int methodArgumentCount();
  virtual Object* systemDefaultValue();
  virtual Object* initialValue();
  virtual boolean dynamicStorageP();
  virtual boolean conformingSignaturesP(Slot* superslot);
  virtual void unfinalizeLocalSlot();
  virtual void helpFinalizeLocalSlot();
  virtual void finalizeSlotTypeComputations();
  virtual Surrogate* primaryType();
  virtual Object* initially();
  virtual Keyword* allocation();
  virtual Object* defaultForm();
  virtual boolean requiredP();
  virtual boolean componentP();
  virtual Symbol* reader();
  virtual Symbol* writer();
  virtual List* slotDemons_reader();
  virtual List* slotGuardDemons_reader();
  virtual Keyword* slotAllocation_reader();
};

class MethodSlot : public Slot {
public:
  boolean methodSetterP;
  List* methodParameterNames;
  List* methodParameterTypeSpecifiers;
  List* methodReturnTypeSpecifiers;
  const char* methodStringifiedSource;
  CodeWrapper* methodCode;
  cpp_function_code functionCode;
  boolean methodFunctionP;
public:
  virtual void printObject(std::ostream* stream);
  virtual StringWrapper* javaTranslateMethodName();
  virtual void printDocumentation(OutputStream* stream, boolean shortP);
  virtual void prettyPrintObject(OutputStream* stream);
  virtual boolean methodStartupFunctionP();
  virtual Object* finishWalkingCallSlotTree(Cons* tree, StandardObject* firstargtype, StandardObject*& _Return1);
  virtual StandardObject* computeReturnTypeSpec(StandardObject* firstargtype);
  virtual int arity();
  virtual int methodArgumentCount();
  virtual void unfinalizeLocalSlot();
  virtual void helpFinalizeLocalSlot();
  virtual void finalizeSlotTypeComputations();
  virtual boolean conformingSignaturesP(Slot* superslot);
  virtual Surrogate* primaryType();
  virtual boolean setterP();
  virtual boolean methodEvaluateArgumentsP_reader();
  virtual List* methodInlinedFunctions_reader();
  virtual List* methodReturnTypeSpecifiers_reader();
  virtual List* methodParameterDirections_reader();
  virtual List* methodParameterTypeSpecifiers_reader();
  virtual List* methodParameterNames_reader();
};

class CompoundTypeSpecifier : public StandardObject {
public:
  virtual void printObject(std::ostream* stream);
};

class ParametricTypeSpecifier : public CompoundTypeSpecifier {
public:
  Surrogate* specifierBaseType;
  List* specifierParameterTypes;
  List* specifierDimensions;
public:
  virtual StandardObject* yieldTypeSpecifier();
  virtual Surrogate* primaryType();
};

class AnchoredTypeSpecifier : public CompoundTypeSpecifier {
public:
  Symbol* specifierParameterName;
public:
  virtual StandardObject* yieldTypeSpecifier();
  virtual Surrogate* primaryType();
};

class Table : public Slot {
public:
  List* tupleDomains;
public:
  virtual void printObject(std::ostream* stream);
  virtual int arity();
  virtual int methodArgumentCount();
  virtual boolean conformingSignaturesP(Slot* superslot);
  virtual Surrogate* primaryType();
};

class GlobalVariable : public MappableObject {
public:
  const char* documentation;
  Symbol* variableName;
  Surrogate* variableType;
  boolean variableSpecialP;
  boolean variableConstantP;
  boolean variablePublicP;
  boolean variableAuxiliaryP;
  // Points to a handle that can be used to access the native value.
  void* variableNativeObject;
  const char* variableStringifiedSource;
public:
  virtual Surrogate* primaryType();
  virtual const char* name();
  virtual Surrogate* type();
  virtual Module* homeModule();
};

class QuotedExpression : public StandardObject {
public:
  int quotationTableOffset;
public:
  virtual void idlOutputLiteral();
  virtual void javaOutputLiteral();
  virtual void cppOutputLiteral();
  virtual Cons* cppTranslateAtomicTree();
  virtual Surrogate* primaryType();
};

class Thing : public StandardObject {
// Defines a class that must be inherited by any
// class that participates in the PowerLoom side of things.
public:
  Surrogate* surrogateValueInverse;
  KeyValueList* dynamicSlots;
public:
  virtual void printObject(std::ostream* stream);
  virtual boolean deletedPSetter(boolean value);
  virtual boolean deletedP();
  virtual BooleanWrapper* badP_reader();
};

class Context : public Thing {
public:
  List* childContexts;
  Module* baseModule;
  Cons* allSuperContexts;
  int contextNumber;
public:
  virtual void printObject(std::ostream* stream);
  virtual void helpPrintOutline(OutputStream* stream, int currentDepth, int depth, boolean namedP);
  virtual boolean deletedP();
  virtual void destroyContext();
  virtual void uninheritSupercontexts();
  virtual void inheritSupercontexts();
  virtual boolean multipleParentsP();
  virtual Context* changeContext();
  virtual const char* contextName();
  virtual Iterator* parentContexts();
  virtual Module* homeModule();
};

class Module : public Context {
public:
  List* parentModules;
  const char* documentation;
  List* nicknames;
  List* uses;
  List* usedBy;
  List* requires;
  boolean caseSensitiveP;
  const char* moduleFullName;
  const char* moduleName;
  const char* moduleStringifiedSource;
  const char* stringifiedOptions;
  Module* cardinalModule;
  StringToIntegerHashTable* symbolOffsetTable;
  StringToIntegerHashTable* surrogateOffsetTable;
  World* strictInferenceCache;
  World* defaultInferenceCache;
  World* prototypeInferenceCache;
public:
  virtual void helpPrintOutline(OutputStream* stream, int currentDepth, int depth, boolean namedP);
  virtual void destroyContext();
  virtual void unfinalizeModule();
  virtual void inheritSupercontexts();
  virtual boolean multipleParentsP();
  virtual Module* changeModule();
  virtual Iterator* parentContexts();
  virtual void describeObject(OutputStream* stream, Keyword* mode);
  virtual void printDefinition(OutputStream* stream);
  virtual Surrogate* primaryType();
  virtual const char* name();
  virtual Module* parentModule();
  virtual const char* lispPackage();
  virtual const char* cppPackage();
  virtual boolean protectSurrogatesP_reader();
  virtual boolean clearableP_reader();
  virtual const char* javaPackage_reader();
  virtual const char* moduleCppPackage_reader();
  virtual const char* moduleLispPackage_reader();
  virtual List* shadowedSurrogates_reader();
};

class World : public Context {
public:
  Context* parentContext;
public:
  virtual boolean multipleParentsP();
  virtual void destroyContext();
  virtual void unfinalizeWorld();
  virtual void inheritSupercontexts();
  virtual Iterator* parentContexts();
  virtual Surrogate* primaryType();
};

class CsValue : public KeyValueList {
// Contextualized value.  Contains a sorted kv-cons list indexed
// by context. The kv-cons list is never null.  Newer (higher numbered) contexts
// appear first.
public:
  virtual void insertAt(Context* context, Object* newvalue);
  virtual Surrogate* primaryType();
};

class Interval : public StandardObject {
public:
  int lowerBound;
  int upperBound;
public:
  virtual void printObject(std::ostream* stream);
  virtual boolean memberP(int n);
  virtual Surrogate* primaryType();
};

class TaxonomyNode : public StandardObject {
public:
  Object* nativeObject;
  int label;
  Cons* intervals;
  Interval* initialInterval;
  int firstIntervalLowerBound;
  int firstIntervalUpperBound;
  Cons* parents;
  Cons* children;
  int totalAncestors;
  Cons* treeChildren;
  Object* marker;
public:
  virtual void printObject(std::ostream* stream);
  virtual boolean deletedPSetter(boolean value);
  virtual boolean deletedP();
  virtual Surrogate* primaryType();
};

class TaxonomyGraph : public StandardObject {
public:
  // If TRUE, relabel the entire graph when a new interval
  // for an incrementally inserted node can't be allocated due to lack of
  // splittable interval space.  Otherwise, create a `foreign' interval and
  // propagate it.
  boolean renumberIfOutOfNumbersP;
  // Whenever the ratio between foreign intervals and
  // non-foreign intervals becomes greater than `renumber-ratio', relabel
  // the whole graph non-incrementally.
  double renumberRatio;
  boolean incrementalModeP;
  int largestPostorderNumber;
  int numberOfNodes;
  int numberOfForeignIntervalNodes;
  List* roots;
  List* brokenLinks;
  List* addedLinks;
  List* removedLinks;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
};

class StellaException : public gc, public std::runtime_error {
public:
  StellaException(const std::string& msg) : std::runtime_error(msg) {
}

};

class InputOutputException : public StellaException {
public:
  InputOutputException(const std::string& msg) : StellaException(msg) {
}

};

class ReadException : public InputOutputException {
public:
  ReadException(const std::string& msg) : InputOutputException(msg) {
}

};

class EndOfFileException : public InputOutputException {
public:
  EndOfFileException(const std::string& msg) : InputOutputException(msg) {
}

};

class NoSuchFileException : public InputOutputException {
public:
  const char* filename;
public:
  NoSuchFileException(const std::string& msg) : InputOutputException(msg) {
}

};

class FileAlreadyExistsException : public InputOutputException {
public:
  const char* filename;
public:
  FileAlreadyExistsException(const std::string& msg) : InputOutputException(msg) {
}

};

class UnhandledException : public StellaException {
public:
  UnhandledException(const std::string& msg) : StellaException(msg) {
}

};

class EvaluationException : public StellaException {
public:
  EvaluationException(const std::string& msg) : StellaException(msg) {
}

};

class NoSuchObjectException : public StellaException {
public:
  NoSuchObjectException(const std::string& msg) : StellaException(msg) {
}

};

class NoSuchContextException : public NoSuchObjectException {
public:
  NoSuchContextException(const std::string& msg) : NoSuchObjectException(msg) {
}

};

class UndefinedClassException : public NoSuchObjectException {
public:
  UndefinedClassException(const std::string& msg) : NoSuchObjectException(msg) {
}

};

class BadArgumentException : public StellaException {
public:
  BadArgumentException(const std::string& msg) : StellaException(msg) {
}

};

class ObjectNotClassException : public BadArgumentException {
public:
  ObjectNotClassException(const std::string& msg) : BadArgumentException(msg) {
}

};

class IncompatibleQuantityException : public StellaException {
// Exception thrown when an operation is attempted on quantities
// that are not compatible with the requested operation.  For example,
// comparing dates and time durations.
public:
  IncompatibleQuantityException(const std::string& msg) : StellaException(msg) {
}

};

class TimeoutException : public StellaException {
public:
  TimeoutException(const std::string& msg) : StellaException(msg) {
}

};

class Quantity : public Object {
// General superclass for extensible quantity objects
public:
  virtual Quantity* coerceTo(Object* other);
  virtual boolean lessP(Object* other);
  virtual boolean lessEqualP(Object* other);
  virtual boolean greaterEqualP(Object* other);
  virtual boolean greaterP(Object* other);
};

class Wrapper : public Object {
public:
  virtual Object* walkAtomicTree(StandardObject*& _Return1);
  virtual boolean terminateWrapperP();
  virtual int hashCode();
  virtual boolean objectEqualP(Object* y);
};

class LiteralWrapper : public Wrapper {
public:
  virtual Object* permanentify();
  virtual Object* copyWrappedLiteral();
};

class NumberWrapper : public LiteralWrapper {
public:
  virtual NumberWrapper* max(NumberWrapper* y);
  virtual NumberWrapper* min(NumberWrapper* y);
};

class IntegerWrapper : public NumberWrapper {
public:
  int wrapperValue;
public:
  virtual void printObject(std::ostream* stream);
  virtual void javaOutputLiteral();
  virtual void cppOutputLiteral();
  virtual double numberWrapperToFloat();
  virtual boolean objectEqlP(Object* y);
  virtual Object* copyWrappedLiteral();
  virtual boolean terminateWrapperP();
  virtual int hashCode();
  virtual Surrogate* primaryType();
};

class LongIntegerWrapper : public NumberWrapper {
public:
  long long int wrapperValue;
public:
  virtual void printObject(std::ostream* stream);
  virtual void javaOutputLiteral();
  virtual void cppOutputLiteral();
  virtual double numberWrapperToFloat();
  virtual boolean objectEqlP(Object* y);
  virtual Object* copyWrappedLiteral();
  virtual int hashCode();
  virtual Surrogate* primaryType();
};

class FloatWrapper : public NumberWrapper {
public:
  double wrapperValue;
public:
  virtual void printObject(std::ostream* stream);
  virtual void javaOutputLiteral();
  virtual void cppOutputLiteral();
  virtual Object* clTranslateAtomicTree();
  virtual double numberWrapperToFloat();
  virtual boolean objectEqlP(Object* y);
  virtual Object* copyWrappedLiteral();
  virtual int hashCode();
  virtual Surrogate* primaryType();
};

class StringWrapper : public LiteralWrapper {
public:
  const char* wrapperValue;
public:
  virtual void printObject(std::ostream* stream);
  virtual void idlOutputLiteral();
  virtual void javaOutputLiteral();
  virtual void cppOutputLiteral();
  virtual Keyword* keywordify();
  virtual boolean objectEqlP(Object* y);
  virtual Object* copyWrappedLiteral();
  virtual int hashCode();
  virtual boolean nonEmptyP();
  virtual boolean emptyP();
  virtual Surrogate* primaryType();
};

class MutableStringWrapper : public LiteralWrapper {
public:
  char* wrapperValue;
public:
  virtual void printObject(std::ostream* stream);
  virtual void idlOutputLiteral();
  virtual void javaOutputLiteral();
  virtual void cppOutputLiteral();
  virtual boolean objectEqlP(Object* y);
  virtual Object* copyWrappedLiteral();
  virtual Surrogate* primaryType();
};

class CharacterWrapper : public LiteralWrapper {
public:
  char wrapperValue;
public:
  virtual void printObject(std::ostream* stream);
  virtual void javaOutputLiteral();
  virtual void cppOutputLiteral();
  virtual boolean objectEqlP(Object* y);
  virtual Object* copyWrappedLiteral();
  virtual int hashCode();
  virtual Surrogate* primaryType();
};

class BooleanWrapper : public LiteralWrapper {
// Objectified version of the BOOLEAN data type.  The NULL
// value can be used for a 3-valued semantics (see THREE-VALUED-BOOLEAN).
public:
  boolean wrapperValue;
public:
  virtual void printObject(std::ostream* stream);
  virtual void javaOutputLiteral();
  virtual void cppOutputLiteral();
  virtual boolean objectEqlP(Object* y);
  virtual int hashCode();
  virtual Surrogate* primaryType();
};

class CodeWrapper : public Wrapper {
public:
  // Redundant slot that supports a fast type test.
  boolean methodCodeP;
};

class FunctionCodeWrapper : public CodeWrapper {
public:
  cpp_function_code wrapperValue;
public:
  virtual Object* copyWrappedLiteral();
  virtual Surrogate* primaryType();
};

class MethodCodeWrapper : public CodeWrapper {
public:
  cpp_method_code wrapperValue;
public:
  virtual Object* copyWrappedLiteral();
  virtual Surrogate* primaryType();
};

class VerbatimStringWrapper : public StringWrapper {
// Wrapper class used to hold verbatim native code strings.
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
};

class NativeObjectPointerWrapper : public Wrapper {
// Wrapper class for native object pointers so that they can be
// stored in standard collection classes as well as in dynamic slots.
public:
  void* wrapperValue;
public:
  virtual Surrogate* primaryType();
};

class ExceptionWrapper : public Wrapper {
// Wrapper class for exceptions so they can be stored in standard
// collection classes as well as in dynamic slots.  NOTE: in order to determine the
// exact type of the wrapped native exception, it has to be signaled and caught in
// an `exception-case' statement, a normal `type-case' will not work here.
public:
  std::exception* wrapperValue;
public:
  virtual Surrogate* primaryType();
};

class LispCode : public gc {
// Used to indicate variables that input or output Common Lisp~
//       structures.
};

class SystemDefinition : public StandardObject {
// The System-Definition class is used to define systems of files
// that constitute STELLA applications.
public:
  const char* name;
  const char* definitionFile;
  const char* directory;
  Cons* files;
  Cons* lispOnlyFiles;
  Cons* cppOnlyFiles;
  Cons* javaOnlyFiles;
  Cons* dataFiles;
  Cons* preprocessedFiles;
  Cons* requiredSystems;
  boolean loadedP;
  boolean upToDateP;
  const char* cardinalModule;
  const char* sourceRootDirectory;
  const char* nativeRootDirectory;
  const char* binaryRootDirectory;
  const char* banner;
  Cons* productionSettings;
  Cons* developmentSettings;
  Symbol* finalizationFunction;
  KeyValueList* dynamicSlots;
public:
  virtual void printObject(std::ostream* stream);
  virtual const char* systemStartupFunctionName();
  virtual Surrogate* primaryType();
  virtual const char* systemGroupName_reader();
  virtual boolean deletedPSetter(boolean value);
  virtual boolean deletedP();
  virtual BooleanWrapper* badP_reader();
};

class Stream : public StandardObject {
public:
  Keyword* state;
};

class OutputStream : public Stream {
public:
  std::ostream* nativeStream;
public:
  virtual void free();
  virtual Surrogate* primaryType();
};

class InputStream : public Stream {
public:
  std::istream* nativeStream;
  OutputStream* echoStream;
  TokenizerStreamState* tokenizerState;
  // One of :CHARACTER, :LINE or :BLOCK indicating what kind of
  // input buffer we are reading from.  This determines what read function to use
  // for tokenization.
  Keyword* bufferingScheme;
public:
  virtual void free();
  virtual const char* streamToString();
  virtual Surrogate* primaryType();
};

class OutputFileStream : public OutputStream {
public:
  const char* filename;
  Keyword* ifExistsAction;
  Keyword* ifNotExistsAction;
public:
  virtual void printObject(std::ostream* stream);
  virtual void free();
  virtual long long int streamPositionSetter(long long int newpos);
  virtual long long int streamPosition();
  virtual Surrogate* primaryType();
};

class InputFileStream : public InputStream {
public:
  const char* filename;
  Keyword* ifNotExistsAction;
public:
  virtual void printObject(std::ostream* stream);
  virtual void free();
  virtual long long int streamPositionSetter(long long int newpos);
  virtual long long int streamPosition();
  virtual Surrogate* primaryType();
};

class OutputStringStream : public OutputStream {
public:
  const char* theString;
public:
  virtual void free();
  virtual const char* theStringReader();
  virtual Surrogate* primaryType();
};

class InputStringStream : public InputStream {
public:
  const char* theString;
public:
  virtual void free();
  virtual Surrogate* primaryType();
};



// Function signatures:
std::ostream& operator << (std::ostream& stream, Object* self);
Object* accessReferenceCountObjectSlotValue(ReferenceCountObject* self, Symbol* slotname, Object* value, boolean setvalueP);
Object* accessActiveObjectSlotValue(ActiveObject* self, Symbol* slotname, Object* value, boolean setvalueP);
Object* accessAbstractIteratorSlotValue(AbstractIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
Object* accessIteratorSlotValue(Iterator* self, Symbol* slotname, Object* value, boolean setvalueP);
ConsIterator* newConsIterator();
Object* accessConsIteratorSlotValue(ConsIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
ListIterator* newListIterator();
Object* accessListIteratorSlotValue(ListIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
DestructiveListIterator* newDestructiveListIterator();
Object* accessDestructiveListIteratorSlotValue(DestructiveListIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
AllPurposeIterator* newAllPurposeIterator();
Object* accessAllPurposeIteratorSlotValue(AllPurposeIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
TypesToClassesIterator* newTypesToClassesIterator(Cons* iteratorCursor);
Object* accessTypesToClassesIteratorSlotValue(TypesToClassesIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
Object* accessDictionaryIteratorSlotValue(DictionaryIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
PropertyListIterator* newPropertyListIterator();
Object* accessPropertyListIteratorSlotValue(PropertyListIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
KvListIterator* newKvListIterator();
Object* accessKvListIteratorSlotValue(KvListIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
IntegerIntervalIterator* newIntegerIntervalIterator(int lowerBound, int upperBound);
Object* accessIntegerIntervalIteratorSlotValue(IntegerIntervalIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
ReverseIntegerIntervalIterator* newReverseIntegerIntervalIterator(int lowerBound, int upperBound);
Object* accessReverseIntegerIntervalIteratorSlotValue(ReverseIntegerIntervalIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
StringIterator* newStringIterator();
Object* accessStringIteratorSlotValue(StringIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
List* newList();
Object* accessListSlotValue(List* self, Symbol* slotname, Object* value, boolean setvalueP);
Set* newSet();
ClassExtension* newClassExtension();
Cons* newCons();
Object* accessConsSlotValue(Cons* self, Symbol* slotname, Object* value, boolean setvalueP);
PropertyList* newPropertyList();
Object* accessPropertyListSlotValue(PropertyList* self, Symbol* slotname, Object* value, boolean setvalueP);
KvCons* newKvCons();
Object* accessKvConsSlotValue(KvCons* self, Symbol* slotname, Object* value, boolean setvalueP);
KeyValueList* newKeyValueList();
Object* accessKeyValueListSlotValue(KeyValueList* self, Symbol* slotname, Object* value, boolean setvalueP);
RecycleList* newRecycleList();
Object* accessRecycleListSlotValue(RecycleList* self, Symbol* slotname, Object* value, boolean setvalueP);
Object* accessAbstractHashTableSlotValue(AbstractHashTable* self, Symbol* slotname, Object* value, boolean setvalueP);
HashTable* newHashTable();
IntegerHashTable* newIntegerHashTable();
FloatHashTable* newFloatHashTable();
StringHashTable* newStringHashTable();
StringToIntegerHashTable* newStringToIntegerHashTable();
Vector* newVector(int arraySize);
Object* accessVectorSlotValue(Vector* self, Symbol* slotname, Object* value, boolean setvalueP);
ExtensibleVector* newExtensibleVector(int arraySize);
ExtensibleSymbolArray* newExtensibleSymbolArray(int arraySize);
Object* accessExtensibleSymbolArraySlotValue(ExtensibleSymbolArray* self, Symbol* slotname, Object* value, boolean setvalueP);
VectorSequence* newVectorSequence(int arraySize);
Object* accessVectorSequenceSlotValue(VectorSequence* self, Symbol* slotname, Object* value, boolean setvalueP);
CustomVectorSequence* newCustomVectorSequence(int arraySize);
Object* accessCustomVectorSequenceSlotValue(CustomVectorSequence* self, Symbol* slotname, Object* value, boolean setvalueP);
BooleanVector* newBooleanVector(int arraySize);
IntegerVector* newIntegerVector(int arraySize);
ActiveList* newActiveList();
ActiveSet* newActiveSet();
Demon* newDemon();
Object* accessDemonSlotValue(Demon* self, Symbol* slotname, Object* value, boolean setvalueP);
KeywordKeyValueList* newKeywordKeyValueList();
Object* accessGeneralizedSymbolSlotValue(GeneralizedSymbol* self, Symbol* slotname, Object* value, boolean setvalueP);
Symbol* newSymbol(const char* symbolName);
Object* accessSymbolSlotValue(Symbol* self, Symbol* slotname, Object* value, boolean setvalueP);
Surrogate* newSurrogate(const char* symbolName);
Object* accessSurrogateSlotValue(Surrogate* self, Symbol* slotname, Object* value, boolean setvalueP);
Keyword* newKeyword(const char* symbolName);
TransientSymbol* newTransientSymbol(const char* symbolName);
Object* accessMappableObjectSlotValue(MappableObject* self, Symbol* slotname, Object* value, boolean setvalueP);
Object* accessRelationSlotValue(Relation* self, Symbol* slotname, Object* value, boolean setvalueP);
Class* newClass();
Object* accessClassSlotValue(Class* self, Symbol* slotname, Object* value, boolean setvalueP);
Object* accessPolymorphicRelationSlotValue(PolymorphicRelation* self, Symbol* slotname, Object* value, boolean setvalueP);
Object* accessSlotSlotValue(Slot* self, Symbol* slotname, Object* value, boolean setvalueP);
StorageSlot* newStorageSlot();
Object* accessStorageSlotSlotValue(StorageSlot* self, Symbol* slotname, Object* value, boolean setvalueP);
MethodSlot* newMethodSlot();
Object* accessMethodSlotSlotValue(MethodSlot* self, Symbol* slotname, Object* value, boolean setvalueP);
ParametricTypeSpecifier* newParametricTypeSpecifier();
Object* accessParametricTypeSpecifierSlotValue(ParametricTypeSpecifier* self, Symbol* slotname, Object* value, boolean setvalueP);
AnchoredTypeSpecifier* newAnchoredTypeSpecifier();
Object* accessAnchoredTypeSpecifierSlotValue(AnchoredTypeSpecifier* self, Symbol* slotname, Object* value, boolean setvalueP);
Table* newTable();
Object* accessTableSlotValue(Table* self, Symbol* slotname, Object* value, boolean setvalueP);
GlobalVariable* newGlobalVariable();
Object* accessGlobalVariableSlotValue(GlobalVariable* self, Symbol* slotname, Object* value, boolean setvalueP);
QuotedExpression* newQuotedExpression();
Object* accessQuotedExpressionSlotValue(QuotedExpression* self, Symbol* slotname, Object* value, boolean setvalueP);
Object* accessThingSlotValue(Thing* self, Symbol* slotname, Object* value, boolean setvalueP);
Object* accessContextSlotValue(Context* self, Symbol* slotname, Object* value, boolean setvalueP);
Module* newModule();
Object* accessModuleSlotValue(Module* self, Symbol* slotname, Object* value, boolean setvalueP);
World* newWorld();
Object* accessWorldSlotValue(World* self, Symbol* slotname, Object* value, boolean setvalueP);
CsValue* newCsValue();
Interval* newInterval();
Object* accessIntervalSlotValue(Interval* self, Symbol* slotname, Object* value, boolean setvalueP);
TaxonomyNode* newTaxonomyNode();
Object* accessTaxonomyNodeSlotValue(TaxonomyNode* self, Symbol* slotname, Object* value, boolean setvalueP);
TaxonomyGraph* newTaxonomyGraph();
Object* accessTaxonomyGraphSlotValue(TaxonomyGraph* self, Symbol* slotname, Object* value, boolean setvalueP);
StellaException* newStellaException(const char* message);
InputOutputException* newInputOutputException(const char* message);
ReadException* newReadException(const char* message);
EndOfFileException* newEndOfFileException(const char* message);
NoSuchFileException* newNoSuchFileException(const char* message);
FileAlreadyExistsException* newFileAlreadyExistsException(const char* message);
UnhandledException* newUnhandledException(const char* message);
EvaluationException* newEvaluationException(const char* message);
NoSuchObjectException* newNoSuchObjectException(const char* message);
NoSuchContextException* newNoSuchContextException(const char* message);
UndefinedClassException* newUndefinedClassException(const char* message);
BadArgumentException* newBadArgumentException(const char* message);
ObjectNotClassException* newObjectNotClassException(const char* message);
IncompatibleQuantityException* newIncompatibleQuantityException(const char* message);
TimeoutException* newTimeoutException(const char* message);
IntegerWrapper* newIntegerWrapper(int wrapperValue);
Object* accessIntegerWrapperSlotValue(IntegerWrapper* self, Symbol* slotname, Object* value, boolean setvalueP);
LongIntegerWrapper* newLongIntegerWrapper(long long int wrapperValue);
Object* accessLongIntegerWrapperSlotValue(LongIntegerWrapper* self, Symbol* slotname, Object* value, boolean setvalueP);
FloatWrapper* newFloatWrapper(double wrapperValue);
Object* accessFloatWrapperSlotValue(FloatWrapper* self, Symbol* slotname, Object* value, boolean setvalueP);
StringWrapper* newStringWrapper(const char* wrapperValue);
Object* accessStringWrapperSlotValue(StringWrapper* self, Symbol* slotname, Object* value, boolean setvalueP);
MutableStringWrapper* newMutableStringWrapper(char* wrapperValue);
Object* accessMutableStringWrapperSlotValue(MutableStringWrapper* self, Symbol* slotname, Object* value, boolean setvalueP);
CharacterWrapper* newCharacterWrapper(char wrapperValue);
Object* accessCharacterWrapperSlotValue(CharacterWrapper* self, Symbol* slotname, Object* value, boolean setvalueP);
BooleanWrapper* newBooleanWrapper(boolean wrapperValue);
Object* accessBooleanWrapperSlotValue(BooleanWrapper* self, Symbol* slotname, Object* value, boolean setvalueP);
Object* accessCodeWrapperSlotValue(CodeWrapper* self, Symbol* slotname, Object* value, boolean setvalueP);
FunctionCodeWrapper* newFunctionCodeWrapper(cpp_function_code wrapperValue);
Object* accessFunctionCodeWrapperSlotValue(FunctionCodeWrapper* self, Symbol* slotname, Object* value, boolean setvalueP);
MethodCodeWrapper* newMethodCodeWrapper(cpp_method_code wrapperValue);
Object* accessMethodCodeWrapperSlotValue(MethodCodeWrapper* self, Symbol* slotname, Object* value, boolean setvalueP);
VerbatimStringWrapper* newVerbatimStringWrapper(const char* wrapperValue);
NativeObjectPointerWrapper* newNativeObjectPointerWrapper(void* wrapperValue);
ExceptionWrapper* newExceptionWrapper(std::exception* wrapperValue);
SystemDefinition* newSystemDefinition();
Object* accessSystemDefinitionSlotValue(SystemDefinition* self, Symbol* slotname, Object* value, boolean setvalueP);
Object* accessStreamSlotValue(Stream* self, Symbol* slotname, Object* value, boolean setvalueP);
OutputStream* newOutputStream();
InputStream* newInputStream();
Object* accessInputStreamSlotValue(InputStream* self, Symbol* slotname, Object* value, boolean setvalueP);
OutputFileStream* newOutputFileStream(const char* filename);
Object* accessOutputFileStreamSlotValue(OutputFileStream* self, Symbol* slotname, Object* value, boolean setvalueP);
InputFileStream* newInputFileStream(const char* filename);
Object* accessInputFileStreamSlotValue(InputFileStream* self, Symbol* slotname, Object* value, boolean setvalueP);
OutputStringStream* newOutputStringStream();
Object* accessOutputStringStreamSlotValue(OutputStringStream* self, Symbol* slotname, Object* value, boolean setvalueP);
InputStringStream* newInputStringStream(const char* theString);
Object* accessInputStringStreamSlotValue(InputStringStream* self, Symbol* slotname, Object* value, boolean setvalueP);
void helpStartupHierarchy1();
void helpStartupHierarchy2();
void helpStartupHierarchy3();
void helpStartupHierarchy4();
void helpStartupHierarchy5();
void helpStartupHierarchy6();
void helpStartupHierarchy7();
void helpStartupHierarchy8();
void helpStartupHierarchy9();
void helpStartupHierarchy10();
void helpStartupHierarchy11();
void startupHierarchy();

// Auxiliary global declarations:
extern Surrogate* SGT_HIERARCHY_STELLA_OBJECT;
extern Symbol* SYM_HIERARCHY_STELLA_PRIMARY_TYPE;
extern Symbol* SYM_HIERARCHY_STELLA_HOME_MODULE;
extern Symbol* SYM_HIERARCHY_STELLA_DELETEDp;
extern Symbol* SYM_HIERARCHY_STELLA_INCREMENT_REFERENCE_COUNT;
extern Symbol* SYM_HIERARCHY_STELLA_DECREMENT_REFERENCE_COUNT;
extern Symbol* SYM_HIERARCHY_STELLA_TYPE_SPEC;
extern boolean oHARDWIRED_TRANSIENTp_ON_TRANSIENT_MIXINo;
extern Surrogate* SGT_HIERARCHY_STELLA_REFERENCE_COUNT_OBJECT;
extern Symbol* SYM_HIERARCHY_STELLA_REFERENCE_COUNT;
extern Symbol* SYM_HIERARCHY_STELLA_BADp;
extern Symbol* SYM_HIERARCHY_STELLA_DELETED_OBJECTp;
extern Surrogate* SGT_HIERARCHY_STELLA_ABSTRACT_ITERATOR;
extern Symbol* SYM_HIERARCHY_STELLA_NEXTp;
extern Symbol* SYM_HIERARCHY_STELLA_FIRST_ITERATIONp;
extern Symbol* SYM_HIERARCHY_STELLA_VALUE;
extern Symbol* SYM_HIERARCHY_STELLA_OBJECT_ITERATOR;
extern Surrogate* SGT_HIERARCHY_STELLA_CONS_ITERATOR;
extern Symbol* SYM_HIERARCHY_STELLA_CONS_ITERATOR_CURSOR;
extern Surrogate* SGT_HIERARCHY_STELLA_LIST_ITERATOR;
extern Symbol* SYM_HIERARCHY_STELLA_LIST_ITERATOR_CURSOR;
extern Symbol* SYM_HIERARCHY_STELLA_LIST_ITERATOR_COLLECTION;
extern Surrogate* SGT_HIERARCHY_STELLA_DESTRUCTIVE_LIST_ITERATOR;
extern Symbol* SYM_HIERARCHY_STELLA_THE_CONS_LIST;
extern Surrogate* SGT_HIERARCHY_STELLA_ALL_PURPOSE_ITERATOR;
extern Symbol* SYM_HIERARCHY_STELLA_KEY;
extern Symbol* SYM_HIERARCHY_STELLA_ITERATOR_NEXT_CODE;
extern Symbol* SYM_HIERARCHY_STELLA_ITERATOR_FILTER_CODE;
extern Symbol* SYM_HIERARCHY_STELLA_ITERATOR_EMPTY_CODE;
extern Symbol* SYM_HIERARCHY_STELLA_ITERATOR_NESTED_ITERATOR;
extern Symbol* SYM_HIERARCHY_STELLA_ITERATOR_CONS_LIST;
extern Symbol* SYM_HIERARCHY_STELLA_ITERATOR_OBJECT;
extern Symbol* SYM_HIERARCHY_STELLA_ITERATOR_SECOND_OBJECT;
extern Symbol* SYM_HIERARCHY_STELLA_ITERATOR_INTEGER;
extern Symbol* SYM_HIERARCHY_STELLA_ITERATOR_SECOND_INTEGER;
extern Surrogate* SGT_HIERARCHY_STELLA_TYPES_TO_CLASSES_ITERATOR;
extern Symbol* SYM_HIERARCHY_STELLA_ITERATOR_CURSOR;
extern Surrogate* SGT_HIERARCHY_STELLA_DICTIONARY_ITERATOR;
extern Symbol* SYM_HIERARCHY_STELLA_VALUE_SETTER;
extern Symbol* SYM_HIERARCHY_STELLA_KEY_SETTER;
extern Symbol* SYM_HIERARCHY_STELLA_OBJECT_DICTIONARY_ITERATOR;
extern Surrogate* SGT_HIERARCHY_STELLA_PROPERTY_LIST_ITERATOR;
extern Symbol* SYM_HIERARCHY_STELLA_PLIST_ITERATOR_CURSOR;
extern Symbol* SYM_HIERARCHY_STELLA_PLIST_ITERATOR_COLLECTION;
extern Surrogate* SGT_HIERARCHY_STELLA_KV_LIST_ITERATOR;
extern Symbol* SYM_HIERARCHY_STELLA_THE_KV_LIST;
extern Symbol* SYM_HIERARCHY_STELLA_KV_LIST_ITERATOR_CURSOR;
extern Surrogate* SGT_HIERARCHY_STELLA_INTEGER_INTERVAL_ITERATOR;
extern Symbol* SYM_HIERARCHY_STELLA_INTERVAL_CURSOR;
extern Symbol* SYM_HIERARCHY_STELLA_LOWER_BOUND;
extern Symbol* SYM_HIERARCHY_STELLA_UPPER_BOUND;
extern Surrogate* SGT_HIERARCHY_STELLA_REVERSE_INTEGER_INTERVAL_ITERATOR;
extern Surrogate* SGT_HIERARCHY_STELLA_STRING_ITERATOR;
extern Symbol* SYM_HIERARCHY_STELLA_THE_STRING;
extern Symbol* SYM_HIERARCHY_STELLA_CURSOR;
extern Symbol* SYM_HIERARCHY_STELLA_END;
extern Surrogate* SGT_HIERARCHY_STELLA_ABSTRACT_COLLECTION;
extern Symbol* SYM_HIERARCHY_STELLA_ALLOCATE_ITERATOR;
extern Symbol* SYM_HIERARCHY_STELLA_LENGTH;
extern Surrogate* SGT_HIERARCHY_STELLA_COLLECTION;
extern Symbol* SYM_HIERARCHY_STELLA_INSERT;
extern Symbol* SYM_HIERARCHY_STELLA_REMOVE;
extern Symbol* SYM_HIERARCHY_STELLA_OBJECT_COLLECTION;
extern Surrogate* SGT_HIERARCHY_STELLA_SEQUENCE;
extern Symbol* SYM_HIERARCHY_STELLA_OBJECT_SEQUENCE;
extern Surrogate* SGT_HIERARCHY_STELLA_LIST;
extern Surrogate* SGT_HIERARCHY_STELLA_SET;
extern Surrogate* SGT_HIERARCHY_STELLA_CLASS_EXTENSION;
extern Surrogate* SGT_HIERARCHY_STELLA_CONS;
extern Symbol* SYM_HIERARCHY_STELLA_REST;
extern Surrogate* SGT_HIERARCHY_STELLA_ABSTRACT_DICTIONARY;
extern Surrogate* SGT_HIERARCHY_STELLA_DICTIONARY;
extern Symbol* SYM_HIERARCHY_STELLA_LOOKUP;
extern Symbol* SYM_HIERARCHY_STELLA_INSERT_AT;
extern Symbol* SYM_HIERARCHY_STELLA_OBJECT_TO_OBJECT_DICTIONARY;
extern Surrogate* SGT_HIERARCHY_STELLA_PROPERTY_LIST;
extern Symbol* SYM_HIERARCHY_STELLA_THE_PLIST;
extern Surrogate* SGT_HIERARCHY_STELLA_KV_CONS;
extern Surrogate* SGT_HIERARCHY_STELLA_KEY_VALUE_LIST;
extern Surrogate* SGT_HIERARCHY_STELLA_RECYCLE_LIST;
extern Symbol* SYM_HIERARCHY_STELLA_RECYCLE_LIST_OF;
extern Symbol* SYM_HIERARCHY_STELLA_RECYCLED_ITEMS;
extern Symbol* SYM_HIERARCHY_STELLA_LIST_OF_RECYCLED_ITEMS;
extern Symbol* SYM_HIERARCHY_STELLA_ALL_ITEMS;
extern Symbol* SYM_HIERARCHY_STELLA_UNUSED_ITEMS;
extern Symbol* SYM_HIERARCHY_STELLA_CURRENT_LENGTH;
extern Symbol* SYM_HIERARCHY_STELLA_ITEM_SIZE;
extern Symbol* SYM_HIERARCHY_STELLA_THE_STELLA_HASH_TABLE;
extern Surrogate* SGT_HIERARCHY_STELLA_HASH_TABLE;
extern Symbol* SYM_HIERARCHY_STELLA_OBJECT_TO_OBJECT_HASH_TABLE;
extern Surrogate* SGT_HIERARCHY_STELLA_INTEGER_HASH_TABLE;
extern Surrogate* SGT_HIERARCHY_STELLA_FLOAT_HASH_TABLE;
extern Surrogate* SGT_HIERARCHY_STELLA_STRING_HASH_TABLE;
extern Surrogate* SGT_HIERARCHY_STELLA_STRING_TO_INTEGER_HASH_TABLE;
extern Surrogate* SGT_HIERARCHY_STELLA_VECTOR;
extern Symbol* SYM_HIERARCHY_STELLA_ARRAY_SIZE;
extern Surrogate* SGT_HIERARCHY_STELLA_EXTENSIBLE_VECTOR;
extern Surrogate* SGT_HIERARCHY_STELLA_EXTENSIBLE_SYMBOL_ARRAY;
extern Symbol* SYM_HIERARCHY_STELLA_TOP_SYMBOL_OFFSET;
extern Symbol* SYM_HIERARCHY_STELLA_POTENTIAL_FREE_SYMBOL_OFFSET;
extern Surrogate* SGT_HIERARCHY_STELLA_VECTOR_SEQUENCE;
extern Symbol* SYM_HIERARCHY_STELLA_SEQUENCE_LENGTH;
extern Surrogate* SGT_HIERARCHY_STELLA_CUSTOM_VECTOR_SEQUENCE;
extern Symbol* SYM_HIERARCHY_STELLA_RESIZE_FACTOR;
extern Surrogate* SGT_HIERARCHY_STELLA_BOOLEAN_VECTOR;
extern Surrogate* SGT_HIERARCHY_STELLA_INTEGER_VECTOR;
extern Surrogate* SGT_HIERARCHY_STELLA_ACTIVE_LIST;
extern Surrogate* SGT_HIERARCHY_STELLA_ACTIVE_SET;
extern Surrogate* SGT_HIERARCHY_STELLA_DEMON;
extern Symbol* SYM_HIERARCHY_STELLA_DEMON_NAME;
extern Symbol* SYM_HIERARCHY_STELLA_DEMON_ACTION;
extern Symbol* SYM_HIERARCHY_STELLA_DEMON_CLASS_REFS;
extern Symbol* SYM_HIERARCHY_STELLA_DEMON_SLOT_REFS;
extern Symbol* SYM_HIERARCHY_STELLA_DEMON_CODE;
extern Symbol* SYM_HIERARCHY_STELLA_DEMON_METHOD;
extern Symbol* SYM_HIERARCHY_STELLA_DEMON_DOCUMENTATION;
extern Symbol* SYM_HIERARCHY_STELLA_DEMON_GUARDp;
extern Symbol* SYM_HIERARCHY_STELLA_DEMON_ALLp;
extern Symbol* SYM_HIERARCHY_STELLA_DEMON_INHERITp;
extern Surrogate* SGT_HIERARCHY_STELLA_KEYWORD_KEY_VALUE_LIST;
extern Symbol* SYM_HIERARCHY_STELLA_SYMBOL_NAME;
extern Symbol* SYM_HIERARCHY_STELLA_SYMBOL_ID;
extern Surrogate* SGT_HIERARCHY_STELLA_SYMBOL;
extern Symbol* SYM_HIERARCHY_STELLA_SYMBOL_SLOT_OFFSET;
extern Symbol* SYM_HIERARCHY_STELLA_SYMBOL_VALUE_AND_PLIST;
extern Surrogate* SGT_HIERARCHY_STELLA_SURROGATE;
extern Symbol* SYM_HIERARCHY_STELLA_SURROGATE_VALUE;
extern Symbol* SYM_HIERARCHY_STELLA_TYPE_CLASS;
extern Symbol* SYM_HIERARCHY_STELLA_SLOTREF_SLOT;
extern Symbol* SYM_HIERARCHY_STELLA_TYPE;
extern Symbol* SYM_HIERARCHY_STELLA_SLOTREF;
extern Surrogate* SGT_HIERARCHY_STELLA_KEYWORD;
extern Surrogate* SGT_HIERARCHY_STELLA_TRANSIENT_SYMBOL;
extern Symbol* SYM_HIERARCHY_STELLA_PROJECTS_ONTO;
extern Symbol* SYM_HIERARCHY_STELLA_PROJECTED_FROM;
extern Surrogate* SGT_HIERARCHY_STELLA_RELATION;
extern Symbol* SYM_HIERARCHY_STELLA_NAME;
extern Symbol* SYM_HIERARCHY_STELLA_ARITY;
extern Symbol* SYM_HIERARCHY_STELLA_PUBLICp;
extern Symbol* SYM_HIERARCHY_STELLA_DIRECT_SUPERS;
extern Symbol* SYM_HIERARCHY_STELLA_ALL_SUPERS;
extern Symbol* SYM_HIERARCHY_STELLA_SLOTS;
extern Symbol* SYM_HIERARCHY_STELLA_PROPERTIES;
extern Symbol* SYM_HIERARCHY_STELLA_ABSTRACTp;
extern Surrogate* SGT_HIERARCHY_STELLA_CLASS;
extern Symbol* SYM_HIERARCHY_STELLA_STORED_ACTIVEp;
extern Surrogate* SGT_HIERARCHY_STELLA_ACTIVE_OBJECT;
extern Symbol* SYM_HIERARCHY_STELLA_ACTIVEp;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_CREATOR;
extern Symbol* SYM_HIERARCHY_STELLA_CREATOR;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_INITIALIZER;
extern Symbol* SYM_HIERARCHY_STELLA_INITIALIZER;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_TERMINATOR;
extern Symbol* SYM_HIERARCHY_STELLA_TERMINATOR;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_DESTRUCTOR;
extern Symbol* SYM_HIERARCHY_STELLA_DESTRUCTOR;
extern Symbol* SYM_HIERARCHY_STELLA_REQUIRED_SLOTS;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_PARAMETERS;
extern Symbol* SYM_HIERARCHY_STELLA_PARAMETERS;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_INITIAL_VALUE;
extern Symbol* SYM_HIERARCHY_STELLA_INITIAL_VALUE;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_EXTENSION;
extern Symbol* SYM_HIERARCHY_STELLA_EXTENSION;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_CL_NATIVE_TYPE;
extern Symbol* SYM_HIERARCHY_STELLA_CL_NATIVE_TYPE;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_CPP_NATIVE_TYPE;
extern Symbol* SYM_HIERARCHY_STELLA_CPP_NATIVE_TYPE;
extern Symbol* SYM_HIERARCHY_STELLA_IDL_NATIVE_TYPE;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_JAVA_NATIVE_TYPE;
extern Symbol* SYM_HIERARCHY_STELLA_JAVA_NATIVE_TYPE;
extern int oHARDWIRED_CLASS_ARITY_ON_CLASSo;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_CL_STRUCT_SLOTS;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_RECYCLE_METHOD;
extern Keyword* KWD_HIERARCHY_NONE;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_REQUIRED_SLOT_NAMES;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_GUARD_CONSTRUCTOR_DEMONS;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_CONSTRUCTOR_DEMONS;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_GUARD_DESTRUCTOR_DEMONS;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_DESTRUCTOR_DEMONS;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_KEY;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_SYNONYMS;
extern Symbol* SYM_HIERARCHY_STELLA_CL_STRUCTp;
extern Symbol* SYM_HIERARCHY_STELLA_MIXINp;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_TYPE;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_ARITY;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_DIRECT_SUPERS;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_DIRECT_SUBS;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_ALL_SUPER_CLASSES;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_ALL_SLOTS;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_LOCAL_SLOTS;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_SLOT_AND_METHOD_CACHE;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_MIXINp;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_COLLECTIONp;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_CL_STRUCTp;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_PUBLICp;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_FINALIZEDp;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_SLOTS_FINALIZEDp;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_STRINGIFIED_SOURCE;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_CONSTRUCTOR_CODE;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_SLOT_ACCESSOR_CODE;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_MARKEDp;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_TAXONOMY_NODE;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_DOCUMENTATION;
extern Symbol* SYM_HIERARCHY_STELLA_CLASS_PRINT_FORM;
extern Symbol* SYM_HIERARCHY_STELLA_DOCUMENTATION;
extern Symbol* SYM_HIERARCHY_STELLA_PRINT_FORM;
extern Surrogate* SGT_HIERARCHY_STELLA_POLYMORPHIC_RELATION;
extern Symbol* SYM_HIERARCHY_STELLA_OWNER;
extern Symbol* SYM_HIERARCHY_STELLA_RENAMES;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_DIRECT_EQUIVALENT;
extern Surrogate* SGT_HIERARCHY_STELLA_SLOT;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_TYPE_SPECIFIER;
extern Symbol* SYM_HIERARCHY_STELLA_TYPE_SPECIFIER;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_HOME_MODULE;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_RENAMES;
extern Symbol* SYM_HIERARCHY_STELLA_COLLECTION_VALUEDp;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_CLOSURE_ASSUMPTION;
extern Symbol* SYM_HIERARCHY_STELLA_CLOSURE_ASSUMPTION;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_DIRECT_SUPERS;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_DIRECT_SUBS;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_NAME;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_OWNER;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_BASE_TYPE;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_SLOTREF;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_PUBLICp;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_RENAMEDp;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_EXTERNALp;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_MARKEDp;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_DOCUMENTATION;
extern Surrogate* SGT_HIERARCHY_STELLA_STORAGE_SLOT;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_ALLOCATION;
extern Keyword* KWD_HIERARCHY_INSTANCE;
extern Symbol* SYM_HIERARCHY_STELLA_ALLOCATION;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_DEFAULT_EXPRESSION;
extern Symbol* SYM_HIERARCHY_STELLA_DEFAULT_FORM;
extern Symbol* SYM_HIERARCHY_STELLA_REQUIREDp;
extern Symbol* SYM_HIERARCHY_STELLA_COMPONENTp;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_READER;
extern Symbol* SYM_HIERARCHY_STELLA_READER;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_WRITER;
extern Symbol* SYM_HIERARCHY_STELLA_WRITER;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_GUARD_DEMONS;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_DEMONS;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_REQUIREDp;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_COMPONENTp;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_READ_ONLYp;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_HARDWIREDp;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_CONTEXT_SENSITIVEp;
extern Surrogate* SGT_HIERARCHY_STELLA_METHOD_SLOT;
extern Symbol* SYM_HIERARCHY_STELLA_SETTERp;
extern Symbol* SYM_HIERARCHY_STELLA_METHOD_PARAMETER_DIRECTIONS;
extern Symbol* SYM_HIERARCHY_STELLA_METHOD_INLINED_FUNCTIONS;
extern Symbol* SYM_HIERARCHY_STELLA_METHOD_EVALUATE_ARGUMENTSp;
extern Symbol* SYM_HIERARCHY_STELLA_METHOD_SETTERp;
extern Symbol* SYM_HIERARCHY_STELLA_METHOD_PARAMETER_NAMES;
extern Symbol* SYM_HIERARCHY_STELLA_METHOD_PARAMETER_TYPE_SPECIFIERS;
extern Symbol* SYM_HIERARCHY_STELLA_METHOD_RETURN_TYPE_SPECIFIERS;
extern Symbol* SYM_HIERARCHY_STELLA_METHOD_STRINGIFIED_SOURCE;
extern Symbol* SYM_HIERARCHY_STELLA_METHOD_CODE;
extern Symbol* SYM_HIERARCHY_STELLA_FUNCTION_CODE;
extern Symbol* SYM_HIERARCHY_STELLA_METHOD_FUNCTIONp;
extern Symbol* SYM_HIERARCHY_STELLA_METHOD_DOCUMENTATION;
extern Symbol* SYM_HIERARCHY_STELLA_METHOD_AUXILIARYp;
extern Symbol* SYM_HIERARCHY_STELLA_METHOD_STORAGE_SLOT;
extern Symbol* SYM_HIERARCHY_STELLA_SLOT_AUXILIARYp;
extern Symbol* SYM_HIERARCHY_STELLA_STORAGE_SLOT;
extern Symbol* SYM_HIERARCHY_STELLA_FUNCTION;
extern Surrogate* SGT_HIERARCHY_STELLA_PARAMETRIC_TYPE_SPECIFIER;
extern Symbol* SYM_HIERARCHY_STELLA_SPECIFIER_BASE_TYPE;
extern Symbol* SYM_HIERARCHY_STELLA_SPECIFIER_PARAMETER_TYPES;
extern Symbol* SYM_HIERARCHY_STELLA_SPECIFIER_DIMENSIONS;
extern Surrogate* SGT_HIERARCHY_STELLA_ANCHORED_TYPE_SPECIFIER;
extern Symbol* SYM_HIERARCHY_STELLA_SPECIFIER_PARAMETER_NAME;
extern Surrogate* SGT_HIERARCHY_STELLA_TABLE;
extern Symbol* SYM_HIERARCHY_STELLA_TUPLE_DOMAINS;
extern Surrogate* SGT_HIERARCHY_STELLA_GLOBAL_VARIABLE;
extern Symbol* SYM_HIERARCHY_STELLA_VARIABLE_HOME_MODULE;
extern Symbol* SYM_HIERARCHY_STELLA_VARIABLE_NAME;
extern Symbol* SYM_HIERARCHY_STELLA_VARIABLE_TYPE;
extern Symbol* SYM_HIERARCHY_STELLA_VARIABLE_SPECIALp;
extern Symbol* SYM_HIERARCHY_STELLA_VARIABLE_CONSTANTp;
extern Symbol* SYM_HIERARCHY_STELLA_VARIABLE_PUBLICp;
extern Symbol* SYM_HIERARCHY_STELLA_VARIABLE_AUXILIARYp;
extern Symbol* SYM_HIERARCHY_STELLA_VARIABLE_DOCUMENTATION;
extern Symbol* SYM_HIERARCHY_STELLA_VARIABLE_STRINGIFIED_SOURCE;
extern Surrogate* SGT_HIERARCHY_STELLA_QUOTED_EXPRESSION;
extern Symbol* SYM_HIERARCHY_STELLA_QUOTATION_TABLE_OFFSET;
extern Symbol* SYM_HIERARCHY_STELLA_SURROGATE_VALUE_INVERSE;
extern Surrogate* SGT_HIERARCHY_STELLA_MODULE;
extern Surrogate* SGT_HIERARCHY_STELLA_WORLD;
extern Symbol* SYM_HIERARCHY_STELLA_WORLD_NAME;
extern Surrogate* SGT_HIERARCHY_STELLA_CONTEXT;
extern Symbol* SYM_HIERARCHY_STELLA_CONTEXT_NAME;
extern Symbol* SYM_HIERARCHY_STELLA_CHILD_CONTEXTS;
extern Symbol* SYM_HIERARCHY_STELLA_BASE_MODULE;
extern Symbol* SYM_HIERARCHY_STELLA_ALL_SUPER_CONTEXTS;
extern Symbol* SYM_HIERARCHY_STELLA_CONTEXT_NUMBER;
extern Symbol* SYM_HIERARCHY_STELLA_PARENT_MODULE;
extern Symbol* SYM_HIERARCHY_STELLA_MODULE_LISP_PACKAGE;
extern Symbol* SYM_HIERARCHY_STELLA_LISP_PACKAGE;
extern Symbol* SYM_HIERARCHY_STELLA_MODULE_CPP_PACKAGE;
extern Symbol* SYM_HIERARCHY_STELLA_CPP_PACKAGE;
extern Symbol* SYM_HIERARCHY_STELLA_SHADOWED_SURROGATES;
extern Symbol* SYM_HIERARCHY_STELLA_JAVA_PACKAGE;
extern Symbol* SYM_HIERARCHY_STELLA_CLEARABLEp;
extern Symbol* SYM_HIERARCHY_STELLA_PROTECT_SURROGATESp;
extern Symbol* SYM_HIERARCHY_STELLA_PARENT_MODULES;
extern Symbol* SYM_HIERARCHY_STELLA_NICKNAMES;
extern Symbol* SYM_HIERARCHY_STELLA_USES;
extern Symbol* SYM_HIERARCHY_STELLA_USED_BY;
extern Symbol* SYM_HIERARCHY_STELLA_REQUIRES;
extern Symbol* SYM_HIERARCHY_STELLA_CASE_SENSITIVEp;
extern Symbol* SYM_HIERARCHY_STELLA_MODULE_FULL_NAME;
extern Symbol* SYM_HIERARCHY_STELLA_MODULE_NAME;
extern Symbol* SYM_HIERARCHY_STELLA_MODULE_STRINGIFIED_SOURCE;
extern Symbol* SYM_HIERARCHY_STELLA_STRINGIFIED_OPTIONS;
extern Symbol* SYM_HIERARCHY_STELLA_CARDINAL_MODULE;
extern Symbol* SYM_HIERARCHY_STELLA_SYMBOL_OFFSET_TABLE;
extern Symbol* SYM_HIERARCHY_STELLA_SURROGATE_OFFSET_TABLE;
extern Symbol* SYM_HIERARCHY_STELLA_STRICT_INFERENCE_CACHE;
extern Symbol* SYM_HIERARCHY_STELLA_DEFAULT_INFERENCE_CACHE;
extern Symbol* SYM_HIERARCHY_STELLA_PROTOTYPE_INFERENCE_CACHE;
extern Symbol* SYM_HIERARCHY_STELLA_PARENT_CONTEXT;
extern Surrogate* SGT_HIERARCHY_STELLA_CS_VALUE;
extern Surrogate* SGT_HIERARCHY_STELLA_INTERVAL;
extern Surrogate* SGT_HIERARCHY_STELLA_TAXONOMY_NODE;
extern Symbol* SYM_HIERARCHY_STELLA_NATIVE_OBJECT;
extern Symbol* SYM_HIERARCHY_STELLA_LABEL;
extern Symbol* SYM_HIERARCHY_STELLA_INTERVALS;
extern Symbol* SYM_HIERARCHY_STELLA_INITIAL_INTERVAL;
extern Symbol* SYM_HIERARCHY_STELLA_FIRST_INTERVAL_LOWER_BOUND;
extern Symbol* SYM_HIERARCHY_STELLA_FIRST_INTERVAL_UPPER_BOUND;
extern Symbol* SYM_HIERARCHY_STELLA_PARENTS;
extern Symbol* SYM_HIERARCHY_STELLA_CHILDREN;
extern Symbol* SYM_HIERARCHY_STELLA_TOTAL_ANCESTORS;
extern Symbol* SYM_HIERARCHY_STELLA_TREE_CHILDREN;
extern Symbol* SYM_HIERARCHY_STELLA_MARKER;
extern Surrogate* SGT_HIERARCHY_STELLA_TAXONOMY_GRAPH;
extern Symbol* SYM_HIERARCHY_STELLA_RENUMBER_IF_OUT_OF_NUMBERSp;
extern Symbol* SYM_HIERARCHY_STELLA_RENUMBER_RATIO;
extern Symbol* SYM_HIERARCHY_STELLA_INCREMENTAL_MODEp;
extern Symbol* SYM_HIERARCHY_STELLA_LARGEST_POSTORDER_NUMBER;
extern Symbol* SYM_HIERARCHY_STELLA_NUMBER_OF_NODES;
extern Symbol* SYM_HIERARCHY_STELLA_NUMBER_OF_FOREIGN_INTERVAL_NODES;
extern Symbol* SYM_HIERARCHY_STELLA_ROOTS;
extern Symbol* SYM_HIERARCHY_STELLA_BROKEN_LINKS;
extern Symbol* SYM_HIERARCHY_STELLA_ADDED_LINKS;
extern Symbol* SYM_HIERARCHY_STELLA_REMOVED_LINKS;
extern Surrogate* SGT_HIERARCHY_STELLA_QUANTITY;
extern Symbol* SYM_HIERARCHY_STELLA_COERCE_TO;
extern Symbol* SYM_HIERARCHY_STELLA_LESSp;
extern Symbol* SYM_HIERARCHY_STELLA_LESS_EQUALp;
extern Symbol* SYM_HIERARCHY_STELLA_GREATER_EQUALp;
extern Symbol* SYM_HIERARCHY_STELLA_GREATERp;
extern Symbol* SYM_HIERARCHY_STELLA_FILE_NAME;
extern Surrogate* SGT_HIERARCHY_STELLA_INTEGER_WRAPPER;
extern Symbol* SYM_HIERARCHY_STELLA_WRAPPER_VALUE;
extern Symbol* SYM_HIERARCHY_STELLA_NULL_INTEGER;
extern Surrogate* SGT_HIERARCHY_STELLA_LONG_INTEGER_WRAPPER;
extern Symbol* SYM_HIERARCHY_STELLA_NULL_LONG_INTEGER;
extern Surrogate* SGT_HIERARCHY_STELLA_FLOAT_WRAPPER;
extern Symbol* SYM_HIERARCHY_STELLA_NULL_FLOAT;
extern Surrogate* SGT_HIERARCHY_STELLA_STRING_WRAPPER;
extern Symbol* SYM_HIERARCHY_STELLA_NULL_STRING;
extern Surrogate* SGT_HIERARCHY_STELLA_MUTABLE_STRING_WRAPPER;
extern Symbol* SYM_HIERARCHY_STELLA_NULL_MUTABLE_STRING;
extern Surrogate* SGT_HIERARCHY_STELLA_CHARACTER_WRAPPER;
extern Symbol* SYM_HIERARCHY_STELLA_NULL_CHARACTER;
extern Surrogate* SGT_HIERARCHY_STELLA_BOOLEAN_WRAPPER;
extern Symbol* SYM_HIERARCHY_STELLA_TRUE;
extern Symbol* SYM_HIERARCHY_STELLA_FALSE;
extern Symbol* SYM_HIERARCHY_STELLA_METHOD_CODEp;
extern Surrogate* SGT_HIERARCHY_STELLA_FUNCTION_CODE_WRAPPER;
extern Surrogate* SGT_HIERARCHY_STELLA_METHOD_CODE_WRAPPER;
extern Surrogate* SGT_HIERARCHY_STELLA_VERBATIM_STRING_WRAPPER;
extern Surrogate* SGT_HIERARCHY_STELLA_NATIVE_OBJECT_POINTER_WRAPPER;
extern Surrogate* SGT_HIERARCHY_STELLA_EXCEPTION_WRAPPER;
extern Symbol* SYM_HIERARCHY_STELLA_THREE_VALUED_BOOLEAN;
extern Symbol* SYM_HIERARCHY_STELLA_PYTHON_OBJECT_POINTER;
extern Surrogate* SGT_HIERARCHY_STELLA_SYSTEM_DEFINITION;
extern Symbol* SYM_HIERARCHY_STELLA_DEFINITION_FILE;
extern Symbol* SYM_HIERARCHY_STELLA_DIRECTORY;
extern Symbol* SYM_HIERARCHY_STELLA_FILES;
extern Symbol* SYM_HIERARCHY_STELLA_LISP_ONLY_FILES;
extern Symbol* SYM_HIERARCHY_STELLA_CPP_ONLY_FILES;
extern Symbol* SYM_HIERARCHY_STELLA_JAVA_ONLY_FILES;
extern Symbol* SYM_HIERARCHY_STELLA_DATA_FILES;
extern Symbol* SYM_HIERARCHY_STELLA_PREPROCESSED_FILES;
extern Symbol* SYM_HIERARCHY_STELLA_REQUIRED_SYSTEMS;
extern Symbol* SYM_HIERARCHY_STELLA_LOADEDp;
extern Symbol* SYM_HIERARCHY_STELLA_UP_TO_DATEp;
extern Symbol* SYM_HIERARCHY_STELLA_SOURCE_ROOT_DIRECTORY;
extern Symbol* SYM_HIERARCHY_STELLA_NATIVE_ROOT_DIRECTORY;
extern Symbol* SYM_HIERARCHY_STELLA_BINARY_ROOT_DIRECTORY;
extern Symbol* SYM_HIERARCHY_STELLA_BANNER;
extern Symbol* SYM_HIERARCHY_STELLA_COPYRIGHT_HEADER;
extern Symbol* SYM_HIERARCHY_STELLA_PRODUCTION_SETTINGS;
extern Symbol* SYM_HIERARCHY_STELLA_DEVELOPMENT_SETTINGS;
extern Symbol* SYM_HIERARCHY_STELLA_FINALIZATION_FUNCTION;
extern Symbol* SYM_HIERARCHY_STELLA_STATE;
extern Surrogate* SGT_HIERARCHY_STELLA_OUTPUT_STREAM;
extern Keyword* KWD_HIERARCHY_LINE;
extern Surrogate* SGT_HIERARCHY_STELLA_INPUT_STREAM;
extern Symbol* SYM_HIERARCHY_STELLA_ECHO_STREAM;
extern Symbol* SYM_HIERARCHY_STELLA_TOKENIZER_STATE;
extern Symbol* SYM_HIERARCHY_STELLA_BUFFERING_SCHEME;
extern Keyword* KWD_HIERARCHY_CREATE;
extern Keyword* KWD_HIERARCHY_SUPERSEDE;
extern Surrogate* SGT_HIERARCHY_STELLA_OUTPUT_FILE_STREAM;
extern Symbol* SYM_HIERARCHY_STELLA_FILENAME;
extern Symbol* SYM_HIERARCHY_STELLA_IF_EXISTS_ACTION;
extern Symbol* SYM_HIERARCHY_STELLA_IF_NOT_EXISTS_ACTION;
extern Symbol* SYM_HIERARCHY_STELLA_FILE_OUTPUT_STREAM;
extern Keyword* KWD_HIERARCHY_BLOCK;
extern Keyword* KWD_HIERARCHY_ERROR;
extern Surrogate* SGT_HIERARCHY_STELLA_INPUT_FILE_STREAM;
extern Symbol* SYM_HIERARCHY_STELLA_FILE_INPUT_STREAM;
extern Surrogate* SGT_HIERARCHY_STELLA_OUTPUT_STRING_STREAM;
extern Symbol* SYM_HIERARCHY_STELLA_STRING_OUTPUT_STREAM;
extern Surrogate* SGT_HIERARCHY_STELLA_INPUT_STRING_STREAM;
extern Symbol* SYM_HIERARCHY_STELLA_STRING_INPUT_STREAM;
extern Symbol* SYM_HIERARCHY_STELLA_STARTUP_HIERARCHY;
extern Symbol* SYM_HIERARCHY_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
