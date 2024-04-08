// stella-system.hh

#ifndef _STELLA_STELLA_SYSTEM_HH
#define _STELLA_STELLA_SYSTEM_HH

// System-wide forward declarations:

namespace stella {

class Cons;
class BooleanWrapper;
class IntegerWrapper;
class LongIntegerWrapper;
class FloatWrapper;
class StringWrapper;
class VerbatimStringWrapper;
class CharacterWrapper;
class Wrapper;
class Surrogate;
class Symbol;
class TransientSymbol;
class Keyword;
class Class;
class StorageSlot;
class MethodSlot;
class AnchoredTypeSpecifier;
class ParametricTypeSpecifier;
class GeneralizedSymbol;
class MutableStringWrapper;
class Object;
class ReferenceCountObject;
class AbstractIterator;
class ConsIterator;
class ListIterator;
class DestructiveListIterator;
class AllPurposeIterator;
class TypesToClassesIterator;
class DictionaryIterator;
class PropertyListIterator;
class KvListIterator;
class IntegerIntervalIterator;
class ReverseIntegerIntervalIterator;
class StringIterator;
class AbstractCollection;
class Collection;
class Sequence;
class List;
class Set;
class ClassExtension;
class AbstractDictionary;
class Dictionary;
class PropertyList;
class KvCons;
class KeyValueList;
class RecycleList;
class HashTable;
class IntegerHashTable;
class FloatHashTable;
class StringHashTable;
class StringToIntegerHashTable;
class Vector;
class ExtensibleVector;
class ExtensibleSymbolArray;
class VectorSequence;
class CustomVectorSequence;
class BooleanVector;
class IntegerVector;
class ActiveList;
class ActiveSet;
class Demon;
class KeywordKeyValueList;
class Relation;
class ActiveObject;
class PolymorphicRelation;
class Slot;
class Table;
class GlobalVariable;
class QuotedExpression;
class Module;
class World;
class Context;
class CsValue;
class Interval;
class TaxonomyNode;
class TaxonomyGraph;
class Quantity;
class FunctionCodeWrapper;
class MethodCodeWrapper;
class NativeObjectPointerWrapper;
class ExceptionWrapper;
class SystemDefinition;
class OutputStream;
class InputStream;
class OutputFileStream;
class InputFileStream;
class OutputStringStream;
class InputStringStream;
class StellaHashTable;
class KeyValueMap;
class Heap;
class StellaHashTableIterator;
class HashSet;
class oneDArray;
class oneDFloatArray;
class twoDArray;
class twoDFloatArray;
class BufferedString;
class CrossProductIterator;
class StandardObject;
class SetMixin;
class DynamicSlotsMixin;
class ContextSensitiveObject;
class ContextSensitiveMixin;
class AllClassSlotsIterator;
class TransientMixin;
class SequenceMixin;
class NumberWrapper;
class TranslationUnit;
class LispCode;
class CompoundTypeSpecifier;
class CmdLineOption;
class MemoizationTable;
class MruMemoizationTable;
class MemoizableIterator;
class LiteralWrapper;
class SExpressionIterator;
class LineIterator;
class NativeLineIterator;
class CharacterIterator;
class Iterator;
class HookList;
class TokenizerTable;
class TokenizerToken;
class TokenizerStreamState;
class StreamTokenizer;
class StellaToken;
class XmlObject;
class XmlElement;
class XmlLocalAttribute;
class XmlGlobalAttribute;
class XmlProcessingInstruction;
class XmlDeclaration;
class XmlDoctypeDeclaration;
class XmlSpecial;
class XmlComment;
class XmlDoctype;
class XmlExpressionIterator;
class XmlAttribute;
class DecodedDateTime;
class DecodedTimeDuration;
class CalendarDate;
class TimeDuration;
class AbstractDictionaryIterator;
class IntervalIterator;
class AbstractHashTable;
class ActiveCollectionMixin;
class MappableObject;
class CodeWrapper;
class Thing;
class StellaException;
class InputOutputException;
class ReadException;
class EndOfFileException;
class NoSuchFileException;
class FileAlreadyExistsException;
class UnhandledException;
class EvaluationException;
class NoSuchObjectException;
class NoSuchContextException;
class UndefinedClassException;
class BadArgumentException;
class ObjectNotClassException;
class IncompatibleQuantityException;
class TimeoutException;
class Stream;
class DimensionalArrayMixin;
class twoDimensionalArrayMixin;
class AbstractDimensionalArray;
class StreamIterator;
class DateTimeObject;

} // end of namespace stella

// System components:
#include "stella/cpp-lib/cpp-primal.hh"
#include "stella/hierarchy.hh"
#include "stella/streams.hh"
#include "stella/taxonomies.hh"
#include "stella/primal.hh"
#include "stella/type-predicates.hh"
#include "stella/conses.hh"
#include "stella/lists.hh"
#include "stella/collections.hh"
#include "stella/iterators.hh"
#include "stella/symbols.hh"
#include "stella/literals.hh"
#include "stella/classes.hh"
#include "stella/methods.hh"
#include "stella/defclass.hh"
#include "stella/date-time.hh"
#include "stella/date-time-parser.hh"
#include "stella/stella-in.hh"
#include "stella/foreach.hh"
#include "stella/walk.hh"
#include "stella/cl-translate.hh"
#include "stella/cl-translate-file.hh"
#include "stella/dynamic-slots.hh"
#include "stella/dynamic-literal-slots.hh"
#include "stella/modules.hh"
#include "stella/contexts.hh"
#include "stella/read.hh"
#include "stella/xml.hh"
#include "stella/macros.hh"
#include "stella/memoize.hh"
#include "stella/demons.hh"
#include "stella/more-demons.hh"
#include "stella/name-utility.hh"
#include "stella/translate-file.hh"
#include "stella/systems.hh"
#include "stella/describe.hh"
#include "stella/cpp-translate-file.hh"
#include "stella/cpp-translate.hh"
#include "stella/cpp-class-out.hh"
#include "stella/cpp-output.hh"
#include "stella/java-translate-file.hh"
#include "stella/java-translate.hh"
#include "stella/java-class-out.hh"
#include "stella/java-output.hh"
#include "stella/idl-translate.hh"
#include "stella/idl-class-out.hh"
#include "stella/idl-translate-file.hh"
#include "stella/idl-output.hh"
#include "stella/tools.hh"
#include "stella/startup.hh"
#include "stella/startup-system.hh"

#endif
