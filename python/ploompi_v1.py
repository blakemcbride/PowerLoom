#!/bin/python

############################# BEGIN LICENSE BLOCK ############################
#                                                                            #
# Version: MPL 1.1/GPL 2.0/LGPL 2.1                                          #
#                                                                            #
# The contents of this file are subject to the Mozilla Public License        #
# Version 1.1 (the "License"); you may not use this file except in           #
# compliance with the License. You may obtain a copy of the License at       #
# http://www.mozilla.org/MPL/                                                #
#                                                                            #
# Software distributed under the License is distributed on an "AS IS" basis, #
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License   #
# for the specific language governing rights and limitations under the       #
# License.                                                                   #
#                                                                            #
# The Original Code is the PowerLoom KR&R System.                            #
#                                                                            #
# The Initial Developer of the Original Code is                              #
# UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          #
# 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               #
#                                                                            #
# Portions created by the Initial Developer are Copyright (C) 1997-2019      #
# the Initial Developer. All Rights Reserved.                                #
#                                                                            #
# Contributor(s):                                                            #
#                                                                            #
# Alternatively, the contents of this file may be used under the terms of    #
# either the GNU General Public License Version 2 or later (the "GPL"), or   #
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),   #
# in which case the provisions of the GPL or the LGPL are applicable instead #
# of those above. If you wish to allow use of your version of this file only #
# under the terms of either the GPL or the LGPL, and not to allow others to  #
# use your version of this file under the terms of the MPL, indicate your    #
# decision by deleting the provisions above and replace them with the notice #
# and other provisions required by the GPL or the LGPL. If you do not delete #
# the provisions above, a recipient may use your version of this file under  #
# the terms of any one of the MPL, the GPL or the LGPL.                      #
#                                                                            #
############################## END LICENSE BLOCK #############################

# High-level Python interface for PowerLoom PLI v1

# OBSOLETE: this version is now replaced by ploompi.py which is more general
#           and uses stellapi.py instead of the now obsolete plic.py.

# TO DO:
# - rename to ppli to not conflict with an existing Python package
# - rename plic to pplic for symmetry
# - eliminate use of with-pli-exception-handler in pli.ste

# This needs to handle the following:
# - definition of a Python object hierarchy that mirrors object types we can get from PLI
# - automatic argument type checking and conversion before calling C-api functions
# - automatic wrapping of result values coming back from the C-api
# - combination and automatic disambiguation of plain and string (`s-') function versions
# - optional arguments (e.g., for module and environment)
# - mapping other keyword arguments onto environment options (e.g., :inference-level 'assertion')
# - mapping of None to NULL
# - print functions that show objects the way they would show in PowerLoom
# - iterator methods for the Python equivalent of PL-Iterator
# - mapping STELLA cons/lists onto Python lists and vice versa

# Example usage:
#
# % setenv LD_LIBRARY_PATH $KAGG_HOME/native/cpp/lib            # where the PowerLoom C++ libraries reside
# % setenv PYTHONPATH $HOME/Projects/powerloom/sources/logic    # where this file resides
# % python
# Python 2.7.3 (default, Apr 14 2012, 08:58:41) [GCC] on linux2
# Type "help", "copyright", "credits" or "license" for more information.
# >>> import pli
# >>> from plic import ffi, pliclib
# >>> pli.clearCaches()
# >>> 

import plic
from plic import ffi, PLIException
import sys
import re


  ##
###### Partial mirror of STELLA / PLI class hierarchy
  ##

class StellaObject(object):
    stellaClassName = "OBJECT"
    
    def __init__(self, obj):
        self.stellaObject = obj

    def __eq__(self, other):
        return isinstance(other, StellaObject) and self.stellaObject == other.stellaObject

    def __ne__(self, other):
        return not isinstance(other, StellaObject) or (self.stellaObject != other.stellaObject)

    def __hash__(self):
        return self.stellaObject.__hash__()

    def __str__(self):
        if self.stellaObject != None:
            return ffi.string(plic.pli_objectToString(self.stellaObject))
        else:
            return '<pli.' + type(self).__name__ + ' NULL>'

    def __repr__(self):
        return '<pli.' + type(self).__name__ + ' ' + str(self) + '>'

class StellaThing(StellaObject):
    stellaClassName = "THING"
    pass

class Cons(StellaObject):
    stellaClassName = "CONS"

    # iteration support methods:
    def __len__(self):
        return consLength(self)

    def __iter__(self):
        return Cons(self.stellaObject)

    def next(self):
        if plic.pli_consIsEmpty(self.stellaObject):
            raise StopIteration()
        else:
            value = consFirst(self)
            self.stellaObject = plic.pli_consRest(self.stellaObject)
            return value

    def tree(self):
        # Convert `self' into a possibly nested Python list (or tree).
        result = list(self)
        i = 0
        for elt in result:
            if isinstance(elt, Cons):
                result[i] = elt.tree()
            i = i + 1
        return result

class List(StellaObject):
    stellaClassName = "LIST"
    pass

class Module(StellaObject):
    stellaClassName = "MODULE"

    def __enter__(self):
        # Context manager method to support `with pli.getModule(...):'
        # TO DO: this seems wrong since the stack is on the instance instead of the class (or global):
        if not hasattr(self, 'moduleStack'):
            self.moduleStack = []
        self.moduleStack.append(cc())
        changeModule(self)
        return self

    def __exit__(self, *_exc):
        # Context manager method.
        changeModule(self.moduleStack.pop())

class PropertyList(StellaObject):
    stellaClassName = "PROPERTY-LIST"
    pass

class KeyValueList(StellaObject):
    stellaClassName = "KEY-VALUE-LIST"
    pass

class GeneralizedSymbol(StellaObject):
    stellaClassName = "GENERALIZED-SYMBOL"
    pass

class Symbol(GeneralizedSymbol):
    stellaClassName = "SYMBOL"
    pass

class Surrogate(GeneralizedSymbol):
    stellaClassName = "SURROGATE"
    pass

class Keyword(GeneralizedSymbol):
    stellaClassName = "KEYWORD"
    pass

class Stream(StellaObject):
    stellaClassName = "STREAM"
    pass

class InputStream(Stream):
    stellaClassName = "INPUT-STREAM"
    pass

class OutputStream(Stream):
    stellaClassName = "OUTPUT-STREAM"
    pass

class FunctionCode(StellaObject):
    stellaClassName = "FUNCTION-CODE-WRAPPER" # think about this one
    pass

class Environment(StellaObject):
    stellaClassName = "ENVIRONMENT"
    pass

class LogicObject(StellaObject):
    stellaClassName = "LOGIC-OBJECT"
    pass

class LogicThing(StellaThing):
    stellaClassName = "LOGIC-THING"
    pass

class Skolem(LogicObject):
    stellaClassName = "SKOLEM"
    pass

class PatternVariable(Skolem):
    stellaClassName = "PATTERN-VARIABLE"
    pass

class Description(LogicObject):
    stellaClassName = "DESCRIPTION"
    pass

class NamedDescription(Description):
    stellaClassName = "NAMED-DESCRIPTION"
    pass

class TruthValue(LogicObject):
    stellaClassName = "TRUTH-VALUE"
    pass

class Proposition(StellaObject):
    stellaClassName = "PROPOSITION"
    pass

class ControlFrame(StellaObject):
    stellaClassName = "CONTROL-FRAME"
    pass

class Iterator(StellaObject):
    stellaClassName = "ITERATOR"
    pass

class PlIterator(Iterator):
    stellaClassName = "PL-ITERATOR"

    def __str__(self):
        if self.stellaObject != None:
            return '<pli.' + type(self).__name__ + '>'
        else:
            return '<pli.' + type(self).__name__ + ' NULL>'

    def __repr__(self):
        if self.stellaObject != None:
            return '<pli.' + type(self).__name__ + ' ' + str(plIteratorLength(self)) + ' elements>'
        else:
            return str(self)

    # support Python for-loop iteration over PlIterator's:
    def __len__(self):
        return plIteratorLength(self)
        
    def __iter__(self):
        return self

    def next(self):
        if plIteratorNextP(self):
            return plIteratorValue(self)
        else:
            raise StopIteration()

class Wrapper(StellaObject):
    stellaClassName = "WRAPPER"
    pass

class NumberWrapper(StellaObject):
    stellaClassName = "NUMBER-WRAPPER"
    pass

class IntegerWrapper(NumberWrapper):
    stellaClassName = "INTEGER-WRAPPER"

    def __int__(self):
        return plic.pli_objectToInteger(self.stellaObject)

    def __float__(self):
        return plic.pli_objectToFloat(self.stellaObject)

class LongIntegerWrapper(NumberWrapper):
    stellaClassName = "LONG-INTEGER-WRAPPER"
    pass

class FloatWrapper(NumberWrapper):
    stellaClassName = "FLOAT-WRAPPER"

    def __float__(self):
        return plic.pli_objectToFloat(self.stellaObject)

class StringWrapper(Wrapper):
    stellaClassName = "STRING-WRAPPER"

    def __str__(self):
        return ffi.string(plic.pli_objectToString(self.stellaObject))

class CharacterWrapper(Wrapper):
    stellaClassName = "CHARACTER-WRAPPER"
    pass

class BooleanWrapper(Wrapper):
    stellaClassName = "BOOLEAN-WRAPPER"
    pass

class IntegerLogicWrapper(IntegerWrapper):
    stellaClassName = "INTEGER-LOGIC-WRAPPER"
    pass

class FloatLogicWrapper(FloatWrapper):
    stellaClassName = "FLOAT-LOGIC-WRAPPER"
    pass

class StringLogicWrapper(StringWrapper):
    stellaClassName = "STRING-LOGIC-WRAPPER"
    pass

class QuantityLogicWrapper(LogicThing):
    stellaClassName = "QUANTITY-LOGIC-WRAPPER"
    pass

class UnmappedObject(StellaObject):
    def __init__(self, obj):
        self.stellaObject = obj
        self.stellaType = ffi.string(plic.pli_getStellaTypeShortName(obj))

    def __str__(self):
        return ffi.string(plic.pli_objectToString(self.stellaObject))

    def __repr__(self):
        return '<pli.UNMAPPED_OBJECT ' + self.stellaType + ' ' + str(self) + '>'


def all_pli_classes(root):
    # Generate all PLI classes starting from `root'
    # (using some Python nested list comprehension magic).
    return [root] + [cls for sub in root.__subclasses__()
                             for cls in all_pli_classes(sub)]

# Mapping STELLA type names to corresponding Python PLI classes:
stella_to_pli_type_map = {}

for cls in all_pli_classes(StellaObject):
    stella_to_pli_type_map[cls.stellaClassName] = cls

stella_string_type = ffi.typeof("char*")
stella_int_type = ffi.typeof("int")
stella_object_type = ffi.typeof("void*")

stella_to_pli_type_map[stella_string_type] = str
stella_to_pli_type_map[stella_int_type] = int

def stella_object_to_pli_type(obj):
    # Map a foreign STELLA object `obj' onto its corresponding Python PLI class.
    # Raise an error if no corresponding PLI class could be found.
    if isinstance(obj, ffi.CData):
        ctype = ffi.typeof(obj)
        if ctype == stella_object_type:
            stella_class_sym = plic.pli_getStellaType(obj)
            pli_class = stella_to_pli_type_map.get(stella_class_sym)
            if pli_class != None:
                return pli_class
            # find it the slower way and cache the result under the type symbol:
            stella_class_name = ffi.string(plic.pli_getStellaTypeShortName(obj))
            pli_class = stella_to_pli_type_map.get(stella_class_name)
            if pli_class != None:
                stella_to_pli_type_map[stella_class_sym] = pli_class
                return pli_class
            else:
                print("PLI Warning: Cannot map STELLA object " + str(obj) + " of type " + stella_class_name + " onto PLI type")
                return UnmappedObject
        else:
            pli_class = stella_to_pli_type_map.get(ctype)
            if pli_class != None:
                return pli_class
            else:
                raise PLIException("Cannot map STELLA object " + str(obj) + " of type " + str(ctype) + " onto PLI type")
    else:
        # we already have a Pyton object, e.g., an int:
        return type(obj)


def stella_to_pli_object(obj):
    if obj == ffi.NULL:
        return None
    else:
        cls = stella_object_to_pli_type(obj)
        if cls == str:
            return ffi.string(obj)
        elif cls == int:
            return obj
        else:
            return cls(obj)

def stella_to_pli_object_of_type(obj, cls):
    if obj == ffi.NULL:
        return None
    else:
        if cls == str:
            return ffi.string(obj)
        elif cls == int:
            return obj
        elif cls == bool:
            return not obj == 0
        else:
            return cls(obj)

def pli_to_stella_object(obj):
    if obj == None:
        return ffi.NULL
    elif isinstance(obj, str):
        # we need to allocate strings on the STELLA side to avoid premature reclamation.
        # NOTE: we do rely on gc-protect/release here in case multiple string arguments
        # need to be allocated before they are passed to a function:
        return plic.pli_createString(obj)
    elif isinstance(obj, unicode):
        obj = obj.encode('utf8')
        return plic.pli_createString(obj)
    elif isinstance(obj, list):
        obj = pli_tree_to_cons_tree(obj)
    # int/float/bool is handled automatically, no conversion needed:
    if isinstance(obj, StellaObject):
        obj = obj.stellaObject
    if obj == None:
        return ffi.NULL
    else:
        return obj

def pli_to_stella_object_of_type(obj, cls):
    if obj == None:
        return ffi.NULL
    if isinstance(obj, str):
        # need to allocate strings on STELLA side (see above):
        return plic.pli_createString(obj)
    elif isinstance(obj, unicode):
        obj = obj.encode('utf8')
        return plic.pli_createString(obj)
    if isinstance(obj, list):
        obj = pli_tree_to_cons_tree(obj)
    if isinstance(obj, cls):
        # int/float/bool is handled automatically, no conversion needed:
        if isinstance(obj, StellaObject):
            obj = obj.stellaObject
        if obj == None:
            return ffi.NULL
        else:
            return obj
    else:
        raise PLIException("Object " + str(obj) + " is not of type " + str(cls))

def dwim_pli_string_to_stella_expression(string):
    if len(string) > 0:
        first = string[0]
        if first == '\\':
            return createStringWrapper(string[1:])
        elif "'`:@(#".find(first) >= 0:
            return stringToStellaExpression(string)
    return createStringWrapper(string)

def pli_tree_to_cons_tree(tree):
    # Convert the Python `tree' into an equivalent STELLA Cons tree.
    # Literals such as numbers and strings will be automatically wrapped.
    if isinstance(tree, list) or isinstance(tree, tuple):
        sTree = createConsList(len(tree))
        # we avoid generation of new Cons-objects by using pliclib methods directly:
        cursor = sTree.stellaObject
        for elt in tree:
            plic.pli_consSetFirst(cursor, pli_to_stella_object_of_type(pli_tree_to_cons_tree(elt), StellaObject))
            cursor = plic.pli_consRest(cursor)
        return sTree
    elif isinstance(tree, StellaObject):
        return tree
    elif isinstance(tree, str):
        return dwim_pli_string_to_stella_expression(tree)
    # need to test before int, since True/False are also int's:
    elif isinstance(tree, bool):
        return createBooleanWrapper(tree)
    elif isinstance(tree, int):
        return createIntegerWrapper(tree)
    elif isinstance(tree, float):
        return createFloatWrapper(tree)
    elif tree == None:
        return tree
    else:
        raise PLIException("Don't know how to convert " + str(tree) + " into a Cons-tree element")

def dwim_pli_atom_to_logic_atom(atom, module=None, env=None):
    # Convert the Python PLI `atom' into an equivalent PowerLoom logic object.
    # Since for string literals we don't know whether a symbol or string is meant,
    # we try to lookup a logic object with that name (or upcased first.  If it exists,
    # it will be used, otherwise, the string will simply be wrapped.
    # TO DO: - figure out whether some version of that should move into PLI
    #        - figure out whether we want a variant of `pli_tree_to_cons_tree' that uses this
    #        - figure out whether this should also use `dwim_pli_string_to_stella_expression'
    #        - figure out how to handle AND/OR/NOT/etc., since those don't have objects
    #          associated with them; we could special-case or create constants - pli.AND,...
    if isinstance(atom, StellaObject):
        return atom
    elif isinstance(atom, str):
        if len(atom) > 0:
            first = atom[0]
            if first == '\\':
                return createStringWrapper(atom[1:])
            elif first == '?':
                return createSymbol(atom)
        # if `atom' is interpretable as the name of an object, use the object, otherwise,
        # assume it's meant to be a string (this means, if we do want a string that is also the
        # name of an object, it has to passed as a wrapper object or prefixed with a backslash):
        # NOTE: our previous "solution" of looking up a symbol first fails, since there
        # the name is interpreted literally, and we do not always have an object symbol
        try:
            obj = getObject(atom, module, env)
            if obj != None:
                return obj
        except:
            pass
        return createStringWrapper(atom)
    # need to test before int, since True/False are also int's:
    elif isinstance(atom, bool):
        return createBooleanWrapper(atom)
    elif isinstance(atom, int):
        return createIntegerWrapper(atom)
    elif isinstance(atom, float):
        return createFloatWrapper(atom)
    else:
        return atom

def dwim_pli_tree_to_logic_tree(tree, module=None, env=None):
    # Convert the Python `tree' into an equivalent STELLA Cons tree.
    # Atoms will be converted via `dwim_pli_atom_to_logic_atom'.
    if isinstance(tree, list):
        sTree = createConsList(len(tree))
        # we avoid generation of new Cons-objects by using pliclib methods directly:
        cursor = sTree.stellaObject
        for elt in tree:
            plic.pli_consSetFirst(cursor, pli_to_stella_object_of_type(dwim_pli_tree_to_logic_tree(elt, module, env), StellaObject))
            cursor = plic.pli_consRest(cursor)
        return sTree
    elif isinstance(tree, StellaObject):
        return tree
    elif isinstance(tree, str):
        return dwim_pli_atom_to_logic_atom(tree, module, env)
    # need to test before int, since True/False are also int's:
    elif isinstance(tree, bool):
        return createBooleanWrapper(tree)
    elif isinstance(tree, int):
        return createIntegerWrapper(tree)
    elif isinstance(tree, float):
        return createFloatWrapper(tree)
    elif tree == None:
        return tree
    else:
        raise PLIException("Don't know how to convert " + str(tree) + " into a Cons-tree element")


  ##
###### Utilities
  ##

constants_map = {}

def def_constant(name, value):
    # Define the named constant `name' to have `value'.
    curval = constants_map.get(name)
    if curval != None and curval != value:
        raise PLIException('def_constant: constant ' + name + ' already has a value, explicitly remove it first: ' + str(curval))
    else:
        constants_map[name] = value

def del_constant(name):
    # Delete the constant `name'.
    del constants_map[name]

def get_constant(name):
    # Return the value of the constant `name', raise an error if it is not defined.
    return constants_map[name]

def lookup_constant(name):
    # Return the value of the constant `name', raise an error if it is not defined.
    return constants_map.get(name)

def parse_command(command, *args, **kwArgs):
    val = lookup_constant(command)
    if val == None:
        val = getSymbol(command)
        if val == None:
            val = getSymbol(command.upper())
            if val == None:
                val = stringToStellaExpression(command)
                if val == None:
                    raise PLIException('parse_command: cannot map ' + command + ' onto an existing PLI command symbol')
    parsedCommand = [val]
    for arg in args:
        parsedCommand.append(pli_tree_to_cons_tree(arg))
    for key in kwArgs:
        val = lookup_constant(key)
        if val == None:
            val = getKeyword(key.upper())
        if val == None:
            raise PLIException('parse_command: cannot map ' + key + ' onto an existing PLI keyword')
        parsedCommand.append(val)
        parsedCommand.append(pli_tree_to_cons_tree(kwArgs[key]))
    return parsedCommand


  ##
###### API Functions
  ##

# The wrappers below were automatically generated by pli-generate.py.
# - comments starting with `###' indicate a manually post-edited function (either
#   to generalize or to fix a problem such as an optional arg at the wrong position).
# - these now still need to be tested, generalized and improved
# + return types need to be converted to a specific type where possible or necessary (e.g. booleans)
# - specifically, we'll need to map more types, e.g., to handle the binding columns returned by a query, wrappers, floats, etc.
# + we need to handle float/double types
#   - those seem to work already....
# - many of the options of PowerLoom commands can become bonafide keyword arguments to the Python function.
# + we need to implement magic iterator methods on PlIterator
# + we need to create a more abbreviated way to print PlIterator objects, right now they have the whole list
# + also, printing currently exhausts the iterator
# - we have to support different print modes
# - we need to map onto Python sequences
# - map Cons and List onto iterator protocol
# - we need to map back from STELLA to Python objects, e.g., for wrapped literals inside cons lists, for example,
#   returned by `list(getInferredBinaryPropositionValues('documentation', 'aggregate'))'
# + getObject('2.0') currently properly raises a Python exception but then segfaults, figure out why
#   - the reason was that the exception was handled at a nested level, at that point the Python callback
#     is called, but we then still execute the rest of the braking PLI function; so we need to figure out how to
#     handle that properly, it seems we always need to unwind to the top-level of the PLI function called
#   - the solution is to use :throws-exceptions? in any PLI function that might raise exceptions which makes
#     the latest version of the C-callable wrapper generation insert appropriate exception handlers in the wrapper code
#   - this means we have to fixup pli.ste in lockstep with this file to add the annotation where necessary
# + the FFI callback exception handler doesn't seem to really raise an exception, since there is still code
#   running after it, even with our new clean exception handling on the C++ side - see plic.py for an explanation
#   - the new `withExceptions' function is one way to deal with this issue correctly - see `getObject'
# - figure out what to do with QUERY-ITERATORS returned by queries inside an `evaluate'; the PLI equivalents
#   all map those onto PL-ITERATORS - maybe we just need to add another conversion function and map them
#   onto our mirror class hierarchy
# - we still need to analyze whether there are any remaining cases where a Python-allocated string could become
#   part of a PowerLoom-allocated object; this causes GC problems once the Python object gets GC-ed; we currently
#   don't use plic.pli_createString pervasively, since most of the cases are already handled by PLI, but there
#   might still some remaining
# - see if we should define NULL float and integer values to use as the defaults of `get-property-integer', etc.
# - we should have an API version of process-definitions and decide whether we will call it automatically for
#   all/some retrieval commands or not?
# - we need better API support to find and create function terms, currently we can only find existing ones with
#   getProposition and friends
# - we should have a loadDirectory function
# - saveModule should support 'append' mode - maybe, also the command should have an outputModule option in case
#   we want to save into a different module than the one we are saving
# - we need support for creation and lookup of function terms
# - dwimming and pli to constree conversion of Python tree should be officially supported, e.g., so we can create
#   lists that specialist iterators can run over.


# void pli_initialize();
def initialize():
    plic.pli_initialize()

# void pli_resetPowerloom();
def resetPowerloom():
    plic.pli_resetPowerloom()

# void pli_clearCaches();
def clearCaches():
    plic.pli_clearCaches()

### pli_boolean pli_plIteratorNextP(pli_PlIterator* self);
def plIteratorNextP(self):
    self = pli_to_stella_object_of_type(self, PlIterator)
    return stella_to_pli_object_of_type(plic.pli_plIteratorNextP(self), bool)

# pli_Object* pli_plIteratorValue(pli_PlIterator* self);
def plIteratorValue(self):
    self = pli_to_stella_object_of_type(self, PlIterator)
    return stella_to_pli_object(plic.pli_plIteratorValue(self))

### pli_boolean pli_plIteratorEmptyP(pli_PlIterator* self);
def plIteratorEmptyP(self):
    self = pli_to_stella_object_of_type(self, PlIterator)
    return stella_to_pli_object_of_type(plic.pli_plIteratorEmptyP(self), bool)

### pli_boolean pli_plIteratorIsEmpty(pli_PlIterator* self);
def plIteratorIsEmpty(self):
    self = pli_to_stella_object_of_type(self, PlIterator)
    return stella_to_pli_object_of_type(plic.pli_plIteratorIsEmpty(self), bool)

### int pli_plIteratorLength(pli_PlIterator* self);
def plIteratorLength(self):
    self = pli_to_stella_object_of_type(self, PlIterator)
    return stella_to_pli_object_of_type(plic.pli_plIteratorLength(self), int)

### pli_PlIterator* pli_consToPlIterator(pli_Cons* self);
def consToPlIterator(self):
    self = pli_to_stella_object_of_type(self, Cons)
    return stella_to_pli_object_of_type(plic.pli_consToPlIterator(self), PlIterator)

### pli_PlIterator* pli_listToPlIterator(pli_List* self);
def listToPlIterator(self):
    self = pli_to_stella_object_of_type(self, List)
    return stella_to_pli_object_of_type(plic.pli_listToPlIterator(self), PlIterator)

### pli_PlIterator* pli_iteratorToPlIterator(pli_Iterator* self);
def iteratorToPlIterator(self):
    self = pli_to_stella_object_of_type(self, Iterator)
    return stella_to_pli_object_of_type(plic.pli_iteratorToPlIterator(self), PlIterator)

### pli_List* pli_plIteratorListify(pli_PlIterator* self);
def plIteratorListify(self):
    self = pli_to_stella_object_of_type(self, PlIterator)
    return stella_to_pli_object_of_type(plic.pli_plIteratorListify(self), List)

### pli_Cons* pli_plIteratorConsify(pli_PlIterator* self);
def plIteratorConsify(self):
    self = pli_to_stella_object_of_type(self, PlIterator)
    return stella_to_pli_object_of_type(plic.pli_plIteratorConsify(self), Cons)

### pli_Cons* pli_createCons(pli_Object* first, pli_Cons* rest);
def createCons(first, rest):
    first = pli_to_stella_object_of_type(first, StellaObject)
    rest = pli_to_stella_object_of_type(rest, Cons)
    return stella_to_pli_object_of_type(plic.pli_createCons(first, rest), Cons)

### pli_Cons* pli_createConsList(int length);
def createConsList(length):
    length = pli_to_stella_object_of_type(length, int)
    return stella_to_pli_object_of_type(plic.pli_createConsList(length), Cons)

NIL = createConsList(0)

### int pli_consLength(pli_Cons* self);
def consLength(self):
    self = pli_to_stella_object_of_type(self, Cons)
    return stella_to_pli_object_of_type(plic.pli_consLength(self), int)

### pli_boolean pli_consIsEmpty(pli_Cons* self);
def consIsEmpty(self):
    self = pli_to_stella_object_of_type(self, Cons)
    return stella_to_pli_object_of_type(plic.pli_consIsEmpty(self), bool)

# pli_Object* pli_consFirst(pli_Cons* self);
def consFirst(self):
    self = pli_to_stella_object_of_type(self, Cons)
    return stella_to_pli_object(plic.pli_consFirst(self))

### pli_Cons* pli_consRest(pli_Cons* self);
def consRest(self):
    self = pli_to_stella_object_of_type(self, Cons)
    return stella_to_pli_object_of_type(plic.pli_consRest(self), Cons)

# pli_Object* pli_consNth(pli_Cons* self, int n);
def consNth(self, n):
    self = pli_to_stella_object_of_type(self, Cons)
    n = pli_to_stella_object_of_type(n, int)
    return stella_to_pli_object(plic.pli_consNth(self, n))

### pli_Cons* pli_consNthRest(pli_Cons* self, int n);
def consNthRest(self, n):
    self = pli_to_stella_object_of_type(self, Cons)
    n = pli_to_stella_object_of_type(n, int)
    return stella_to_pli_object_of_type(plic.pli_consNthRest(self, n), Cons)

# void pli_consSetFirst(pli_Cons* self, pli_Object* value);
def consSetFirst(self, value):
    self = pli_to_stella_object_of_type(self, Cons)
    value = pli_to_stella_object_of_type(value, StellaObject)
    plic.pli_consSetFirst(self, value)

# void pli_consSetRest(pli_Cons* self, pli_Cons* rest);
def consSetRest(self, rest):
    self = pli_to_stella_object_of_type(self, Cons)
    rest = pli_to_stella_object_of_type(rest, Cons)
    plic.pli_consSetRest(self, rest)

# void pli_consSetNth(pli_Cons* self, int n, pli_Object* value);
def consSetNth(self, n, value):
    self = pli_to_stella_object_of_type(self, Cons)
    n = pli_to_stella_object_of_type(n, int)
    value = pli_to_stella_object_of_type(value, StellaObject)
    plic.pli_consSetNth(self, n, value)

# void pli_consSetNthRest(pli_Cons* self, int n, pli_Cons* rest);
def consSetNthRest(self, n, rest):
    self = pli_to_stella_object_of_type(self, Cons)
    n = pli_to_stella_object_of_type(n, int)
    rest = pli_to_stella_object_of_type(rest, Cons)
    plic.pli_consSetNthRest(self, n, rest)

# pli_Object* pli_listFirst(pli_List* self);
def listFirst(self):
    self = pli_to_stella_object_of_type(self, List)
    return stella_to_pli_object(plic.pli_listFirst(self))

### pli_Cons* pli_listRest(pli_List* self);
def listRest(self):
    self = pli_to_stella_object_of_type(self, List)
    return stella_to_pli_object_of_type(plic.pli_listRest(self), Cons)

# pli_Object* pli_listNth(pli_List* self, int n);
def listNth(self, n):
    self = pli_to_stella_object_of_type(self, List)
    n = pli_to_stella_object_of_type(n, int)
    return stella_to_pli_object(plic.pli_listNth(self, n))

### char* pli_createString(char* content);
def createString(content):
    content = pli_to_stella_object_of_type(content, str)
    return stella_to_pli_object_of_type(plic.pli_createString(content), str)

### pli_StringWrapper* pli_createStringWrapper(char* self);
def createStringWrapper(self):
    self = pli_to_stella_object_of_type(self, str)
    return stella_to_pli_object_of_type(plic.pli_createStringWrapper(self), StringWrapper)

### pli_StringWrapper* pli_createDirectStringWrapper(char* self);
def createDirectStringWrapper(self):
    self = pli_to_stella_object_of_type(self, str)
    return stella_to_pli_object_of_type(plic.pli_createDirectStringWrapper(self), StringWrapper)

### pli_IntegerWrapper* pli_createIntegerWrapper(int self);
def createIntegerWrapper(self):
    self = pli_to_stella_object_of_type(self, int)
    return stella_to_pli_object_of_type(plic.pli_createIntegerWrapper(self), IntegerWrapper)

# pli_LongIntegerWrapper* pli_createLongIntegerWrapper(long long int self);
# TO DO: FIGURE OUT HOW TO DEAL WITH LONG INTEGERS
# def createLongIntegerWrapper(self):
#     self = pli_to_stella_object_of_type(self, long)
#     return stella_to_pli_object_of_type(plic.pli_createLongIntegerWrapper(self), LongIntegerWrapper)

### pli_FloatWrapper* pli_createFloatWrapper(double self);
def createFloatWrapper(self):
    self = pli_to_stella_object_of_type(self, float)
    return stella_to_pli_object_of_type(plic.pli_createFloatWrapper(self), FloatWrapper)

### pli_BooleanWrapper* pli_createBooleanWrapper(pli_boolean self);
def createBooleanWrapper(self):
    self = pli_to_stella_object_of_type(self, bool)
    return stella_to_pli_object_of_type(plic.pli_createBooleanWrapper(self), BooleanWrapper)


### pli_Keyword* pli_getKeyword(char* name);
def getKeyword(name):
    name = pli_to_stella_object_of_type(name, str)
    return stella_to_pli_object_of_type(plic.pli_getKeyword(name), Keyword)

### pli_Symbol* pli_getSymbol(char* name, pli_Module* module, pli_Environment* environment);
def getSymbol(name, module=None, environment=None):
    name = pli_to_stella_object_of_type(name, str)
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getSymbol(name, module, environment), Symbol)

### pli_Symbol* pli_getOperator(char* name);
def getOperator(name):
    name = pli_to_stella_object_of_type(name, str)
    return stella_to_pli_object_of_type(plic.pli_getOperator(name), Symbol)

### pli_Object* pli_getObject(char* name, pli_Module* module, pli_Environment* environment);
def getObject(name, module=None, env=None):
    # Combines object and string versions, uses optional arguments and automatically un/wraps args and return values.
    name = pli_to_stella_object_of_type(name, str)
    env = pli_to_stella_object_of_type(env, Environment)
    if isinstance(module, str):
        module = pli_to_stella_object_of_type(module, str) # redundant
        return stella_to_pli_object(plic.pli_sGetObject(name, module, env))
    else:
        module = pli_to_stella_object_of_type(module, Module)
        return stella_to_pli_object(plic.pli_getObject(name, module, env))

# define this as an alias - to more easily assemble trees:
gob = getObject

# Obsolete:
# pli_Object* pli_sGetObject(char* name, char* moduleName, pli_Environment* environment);
# def sGetObject(name, moduleName, environment=None):
#     name = pli_to_stella_object_of_type(name, str)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object(plic.pli_sGetObject(name, moduleName, environment))

# pli_LogicObject* pli_getConcept(char* name, pli_Module* module, pli_Environment* environment);
def getConcept(name, module=None, environment=None):
    # Combines object and string versions, uses optional arguments and automatically un/wraps args and return values.
    name = pli_to_stella_object_of_type(name, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    if isinstance(module, str):
        module = pli_to_stella_object_of_type(module, str) # redundant
        return stella_to_pli_object(plic.pli_sGetConcept(name, module, environment))
    else:
        module = pli_to_stella_object_of_type(module, Module)
        return stella_to_pli_object(plic.pli_getConcept(name, module, environment))

# Obsolete:
# pli_LogicObject* pli_sGetConcept(char* name, char* moduleName, pli_Environment* environment);
# def sGetConcept(name, moduleName, environment=None):
#     name = pli_to_stella_object_of_type(name, str)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object(plic.pli_sGetConcept(name, moduleName, environment))

# pli_LogicObject* pli_getRelation(char* name, pli_Module* module, pli_Environment* environment);
def getRelation(name, module=None, environment=None):
    # Combines object and string versions, uses optional arguments and automatically un/wraps args and return values.
    name = pli_to_stella_object_of_type(name, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    if isinstance(module, str):
        module = pli_to_stella_object_of_type(module, str) # redundant
        return stella_to_pli_object(plic.pli_sGetRelation(name, module, environment))
    else:
        module = pli_to_stella_object_of_type(module, Module)
        return stella_to_pli_object(plic.pli_getRelation(name, module, environment))

# Obsolete:
# pli_LogicObject* pli_sGetRelation(char* name, char* moduleName, pli_Environment* environment);
# def sGetRelation(name, moduleName, environment=None):
#     name = pli_to_stella_object_of_type(name, str)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object(plic.pli_sGetRelation(name, moduleName, environment))

### pli_PlIterator* pli_getUndefinedRelations(pli_Module* module, pli_Environment* environment);
def getUndefinedRelations(module=None, environment=None):
    # Additionally supports a string argument for `module', uses optional arguments and automatically un/wraps args and return values.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getUndefinedRelations(module, environment), PlIterator)

### char* pli_getNameInModule(pli_Object* obj, pli_Module* module, pli_Environment* environment);
def getNameInModule(obj, module=None, environment=None):
    # Additionally supports a string argument for `module', uses optional arguments and automatically un/wraps args and return values.
    obj = pli_to_stella_object_of_type(obj, StellaObject)
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getNameInModule(obj, module, environment), str)

### char* pli_getName(pli_Object* obj);
def getName(obj):
    obj = pli_to_stella_object_of_type(obj, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_getName(obj), str)

### char* pli_getShortName(pli_Object* obj);
def getShortName(obj):
    obj = pli_to_stella_object_of_type(obj, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_getShortName(obj), str)

### char* pli_getSkolemName(pli_Skolem* skolem);
def getSkolemName(obj):
    obj = pli_to_stella_object_of_type(obj, Skolem)
    return stella_to_pli_object_of_type(plic.pli_getSkolemName(obj), str)

### char* pli_getSkolemShortName(pli_Skolem* skolem);
def getSkolemShortName(obj):
    obj = pli_to_stella_object_of_type(obj, Skolem)
    return stella_to_pli_object_of_type(plic.pli_getSkolemShortName(obj), str)

### char* pli_getVariableName(pli_PatternVariable* variable);
def getVariableName(obj):
    obj = pli_to_stella_object_of_type(obj, PatternVariable)
    return stella_to_pli_object_of_type(plic.pli_getVariableName(obj), str)

### char* pli_getVariableShortName(pli_PatternVariable* variable);
def getVariableShortName(obj):
    obj = pli_to_stella_object_of_type(obj, PatternVariable)
    return stella_to_pli_object_of_type(plic.pli_getVariableShortName(obj), str)

### char* pli_objectToString(pli_Object* self);
def objectToString(self):
    self = pli_to_stella_object_of_type(self, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_objectToString(self), str)

### int pli_objectToInteger(pli_Object* self);
def objectToInteger(self):
    self = pli_to_stella_object_of_type(self, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_objectToInteger(self), int)

# double pli_objectToFloat(pli_Object* self);
def objectToFloat(self):
    self = pli_to_stella_object_of_type(self, StellaObject)
    return stella_to_pli_object(plic.pli_objectToFloat(self))

### char* pli_objectToParsableString(pli_Object* self);
def objectToParsableString(self):
    self = pli_to_stella_object_of_type(self, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_objectToParsableString(self), str)

### pli_Symbol* pli_getStellaType(pli_Object* self);
def getStellaType(self):
    self = pli_to_stella_object_of_type(self, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_getStellaType(self), Symbol)

### pli_Symbol* pli_getLogicType(pli_Object* self);
def getLogicType(self):
    self = pli_to_stella_object_of_type(self, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_getLogicType(self), Symbol)

### char* pli_getStellaTypeName(pli_Object* self);
def getStellaTypeName(self):
    self = pli_to_stella_object_of_type(self, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_getStellaTypeName(self), str)

### char* pli_getStellaTypeShortName(pli_Object* self);
def getStellaTypeShortName(self):
    self = pli_to_stella_object_of_type(self, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_getStellaTypeShortName(self), str)

### char* pli_getLogicTypeName(pli_Object* self);
def getLogicTypeName(self):
    self = pli_to_stella_object_of_type(self, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_getLogicTypeName(self), str)

### char* pli_getLogicTypeShortName(pli_Object* self);
def getLogicTypeShortName(self):
    self = pli_to_stella_object_of_type(self, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_getLogicTypeShortName(self), str)

LITERAL_CONCEPT = getConcept("LITERAL", "PL-USER")
STRING_CONCEPT  = getConcept("STRING", "PL-USER")
INTEGER_CONCEPT = getConcept("INTEGER", "PL-USER")
FLOAT_CONCEPT   = getConcept("FLOAT", "PL-USER")

### pli_Object* pli_stringToObject(char* string, pli_LogicObject* type, pli_Module* module, pli_Environment* environment);
def stringToObject(string, type_=None, module=None, environment=None):
    # Supports a string or proper object for `module' and `type_'.
    string = pli_to_stella_object_of_type(string, str)
    if isinstance(type_, str):
        type_ = getConcept(type_, "PL-USER")
    type_ = pli_to_stella_object_of_type(type_, LogicObject)
    if isinstance(module, str):
        module = geExistingtModule(module, environment)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object(plic.pli_stringToObject(string, type_, module, environment))

### pli_Object* pli_stringToStellaExpression(char* expression, pli_Module* module, pli_Environment* environment);
def stringToStellaExpression(expression, module=None, environment=None):
    expression = pli_to_stella_object_of_type(expression, str)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object(plic.pli_stringToStellaExpression(expression, module, environment))

### pli_Proposition* pli_getProposition(pli_Object* relationAndArguments, pli_Module* module, pli_Environment* environment);
def getProposition(relationAndArguments, module=None, environment=None):
    # Combines object and string versions, uses optional arguments and automatically un/wraps args and return values.
    # Supports a string or proper object for `module' in both object and string variants.
    if isinstance(relationAndArguments, str):
        relationAndArguments = pli_to_stella_object_of_type(relationAndArguments, str)
        if isinstance(module, Module):
            module = objectToString(module)
        # at this point, we should have a Python string:
        module = pli_to_stella_object_of_type(module, str)
        environment = pli_to_stella_object_of_type(environment, Environment)
        return stella_to_pli_object_of_type(plic.pli_sGetProposition(relationAndArguments, module, environment), Proposition)
    else:
        if isinstance(module, str):
            module = getExistingModule(module, environment)
        relationAndArguments = dwim_pli_tree_to_logic_tree(relationAndArguments, module, environment)
        relationAndArguments = pli_to_stella_object_of_type(relationAndArguments, StellaObject)
        module = pli_to_stella_object_of_type(module, Module)
        environment = pli_to_stella_object_of_type(environment, Environment)
        return stella_to_pli_object_of_type(plic.pli_getProposition(relationAndArguments, module, environment), Proposition)

# Obsolete:
### pli_Proposition* pli_sGetProposition(char* relationAndArguments, char* moduleName, pli_Environment* environment);
# def sGetProposition(relationAndArguments, moduleName, environment=None):
#     relationAndArguments = pli_to_stella_object_of_type(relationAndArguments, str)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object_of_type(plic.pli_sGetProposition(relationAndArguments, moduleName, environment), Proposition)

# this works:
# >>> prop=createConsList(2)
# >>> consSetNth(prop, 0, getObject('RELATION', 'PL-USER'))
# >>> consSetNth(prop, 1, getObject('RELATION', 'PL-USER'))
# >>> prop
# <pli.Cons (/PL-KERNEL-KB/RELATION /PL-KERNEL-KB/RELATION)>
# >>> getProposition(prop, 'PL-USER')
# <pli.Proposition (/PL-KERNEL-KB/CONCEPT /PL-KERNEL-KB/RELATION)>
# >>> getProposition(prop, getModule('PL-USER'))
# <pli.Proposition (/PL-KERNEL-KB/CONCEPT /PL-KERNEL-KB/RELATION)>
# >>> getProposition(['relation', 'relation'], 'PL-USER')
# <pli.Proposition (/PL-KERNEL-KB/CONCEPT /PL-KERNEL-KB/RELATION)>

# this now also works using Python lists/trees:
# >>> changeModule('PL-USER')
# <pli.Module /PL-KERNEL-KB/PL-USER>
# >>> getProposition([gob("RELATION"), gob("RELATION")])
# <pli.Proposition (CONCEPT RELATION)>

### pli_PlIterator* pli_getPropositions(pli_Object* relationAndArguments, pli_Module* module, pli_Environment* environment);
def getPropositions(relationAndArguments, module=None, environment=None):
    # Combines object and string versions, uses optional arguments and automatically un/wraps args and return values.
    # Supports a string or proper object for `module' in both object and string variants.
    if isinstance(relationAndArguments, str):
        relationAndArguments = pli_to_stella_object_of_type(relationAndArguments, str)
        if isinstance(module, Module):
            module = objectToString(module)
        # at this point, we should have a Python string:
        module = pli_to_stella_object_of_type(module, str)
        environment = pli_to_stella_object_of_type(environment, Environment)
        return stella_to_pli_object_of_type(plic.pli_sGetPropositions(relationAndArguments, module, environment), PlIterator)
    else:
        if isinstance(module, str):
            module = getExistingModule(module, environment)
        relationAndArguments = dwim_pli_tree_to_logic_tree(relationAndArguments, module, environment)
        relationAndArguments = pli_to_stella_object_of_type(relationAndArguments, StellaObject)
        module = pli_to_stella_object_of_type(module, Module)
        environment = pli_to_stella_object_of_type(environment, Environment)
        return stella_to_pli_object_of_type(plic.pli_getPropositions(relationAndArguments, module, environment), PlIterator)

# Obsolete:
### pli_PlIterator* pli_sGetPropositions(char* relationAndArguments, char* moduleName, pli_Environment* environment);
# def sGetPropositions(relationAndArguments, moduleName, environment=None):
#     relationAndArguments = pli_to_stella_object_of_type(relationAndArguments, str)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object_of_type(plic.pli_sGetPropositions(relationAndArguments, moduleName, environment), PlIterator)

# this works:
# >>> list(getPropositions("(concept null)", 'PL-USER'))
# [<pli.Proposition (CONCEPT CONCEPT)>, <pli.Proposition (CONCEPT RELATION)>, ...]
# >>> list(getPropositions([gob("concept"), None], 'PL-USER'))
# [<pli.Proposition (CONCEPT CONCEPT)>, <pli.Proposition (CONCEPT RELATION)>, ...]

### pli_PlIterator* pli_getInconsistentPropositions(pli_Module* module, pli_Environment* environment);
def getInconsistentPropositions(module=None, environment=None):
    # Supports a string or proper object for `module'.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getInconsistentPropositions(module, environment), PlIterator)

### pli_PlIterator* pli_getUnaryPropositions(pli_LogicObject* relation, pli_Object* arg, pli_Module* module, pli_Environment* environment);
def getUnaryPropositions(relation, arg=None, module=None, environment=None):
    # Supports object, string and other literal arguments.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    if isinstance(relation, str):
        relation = getRelation(relation, module, environment)
    arg = dwim_pli_atom_to_logic_atom(arg, module, environment)
    # PLI to STELLA conversion:
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    arg = pli_to_stella_object_of_type(arg, StellaObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getUnaryPropositions(relation, arg, module, environment), PlIterator)

# >>> cc('PL-USER')
# <pli.Module /PL-KERNEL-KB/PL-USER>
# >>> list(getUnaryPropositions('variable-arity'))
# [<pli.Proposition (VARIABLE-ARITY SKOLEM-FN)>, <pli.Proposition (VARIABLE-ARITY COLLECTIONOF)>, ...]
# >>> list(getUnaryPropositions('variable-arity', 'collectionof'))
# [<pli.Proposition (VARIABLE-ARITY COLLECTIONOF)>]

### pli_Proposition* pli_getBinaryProposition(pli_LogicObject* relation, pli_Object* arg1, pli_Object* arg2, pli_Module* module, pli_Environment* environment);
def getBinaryProposition(relation, arg1=None, arg2=None, module=None, environment=None):
    # Supports object, string and other literal arguments.
    # The rewrite pattern is a little bit different here, since we basically do the optional literal-to-object
    # conversion on the Pyhton side, and then call the core object-based method (also for this no s-method exists).
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    if isinstance(relation, str):
        relation = getRelation(relation, module, environment)
    arg1 = dwim_pli_atom_to_logic_atom(arg1, module, environment)
    arg2 = dwim_pli_atom_to_logic_atom(arg2, module, environment)
    # PLI to STELLA conversion:
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    arg1 = pli_to_stella_object_of_type(arg1, StellaObject)
    arg2 = pli_to_stella_object_of_type(arg2, StellaObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getBinaryProposition(relation, arg1, arg2, module, environment), Proposition)

# this works:
# >>> getBinaryProposition('documentation', None, None)
# <pli.Proposition (DOCUMENTATION THING "The class of all things.  `Thing' is the top-most concept
# in the concept hierarchy.")>
# >>> getBinaryProposition('documentation', 'aggregate', None)
# <pli.Proposition (DOCUMENTATION AGGREGATE "?a is an aggregate")>
# >>> getBinaryProposition('documentation', getObject('aggregate'), None)
# <pli.Proposition (DOCUMENTATION AGGREGATE "?a is an aggregate")>
# >>> getBinaryProposition('documentation', None, "?a is an aggregate")
# <pli.Proposition (DOCUMENTATION AGGREGATE "?a is an aggregate")>
# >>> getBinaryProposition('documentation', 'aggregate')
# <pli.Proposition (DOCUMENTATION AGGREGATE "?a is an aggregate")>
# >>> getBinaryProposition('documentation')
# <pli.Proposition (DOCUMENTATION THING "The class of all things.  `Thing' is the top-most concept in the concept hierarchy.")>

### pli_PlIterator* pli_getBinaryPropositions(pli_LogicObject* relation, pli_Object* arg1, pli_Object* arg2, pli_Module* module, pli_Environment* environment);
def getBinaryPropositions(relation, arg1=None, arg2=None, module=None, environment=None):
    # Supports object, string and other literal arguments.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    if isinstance(relation, str):
        relation = getRelation(relation, module, environment)
    arg1 = dwim_pli_atom_to_logic_atom(arg1, module, environment)
    arg2 = dwim_pli_atom_to_logic_atom(arg2, module, environment)
    # PLI to STELLA conversion:
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    arg1 = pli_to_stella_object_of_type(arg1, StellaObject)
    arg2 = pli_to_stella_object_of_type(arg2, StellaObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getBinaryPropositions(relation, arg1, arg2, module, environment), PlIterator)

# this works:
# >>> list(getBinaryPropositions('documentation', 'aggregate', None, 'PL-KERNEL'))
# [<pli.Proposition (DOCUMENTATION AGGREGATE "?a is an aggregate")>]
# >>> list(getBinaryPropositions('documentation', 'aggregate'))
# [<pli.Proposition (DOCUMENTATION AGGREGATE "?a is an aggregate")>]
# >>> list(getBinaryPropositions(None, 'aggregate', None, 'PL-KERNEL'))
# []
# >>> list(getBinaryPropositions('relation-specialist', None, None))[0:5]
# [<pli.Proposition (RELATION-SPECIALIST + |i|CONSTRAINT-SPECIALIST)>, <pli.Proposition (RELATION-SPECIALIST - |i|CONSTRAINT-SPECIALIST)>, <pli.Proposition (RELATION-SPECIALIST * |i|CONSTRAINT-SPECIALIST)>, <pli.Proposition (RELATION-SPECIALIST / |i|CONSTRAINT-SPECIALIST)>, <pli.Proposition (RELATION-SPECIALIST < |i|INEQUALITY-SPECIALIST)>]

### pli_PlIterator* pli_getInferredBinaryPropositionValues(pli_LogicObject* relation, pli_Object* arg, pli_Module* module, pli_Environment* environment);
def getInferredBinaryPropositionValues(relation, arg, module=None, environment=None):
    # Supports object, string and other literal arguments.
    # The rewrite pattern is a little bit different here, since we basically do the optional literal-to-object
    # conversion on the Pyhton side, and then call the core object-based method.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    if isinstance(relation, str):
        relation = getRelation(relation, module, environment)
    arg = dwim_pli_atom_to_logic_atom(arg, module, environment)
    # PLI to STELLA conversion:
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    arg = pli_to_stella_object_of_type(arg, StellaObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getInferredBinaryPropositionValues(relation, arg, module, environment), PlIterator)

# Obsolete:
### pli_PlIterator* pli_sGetInferredBinaryPropositionValues(char* relationName, char* argName, char* moduleName, pli_Environment* environment);
# def sGetInferredBinaryPropositionValues(relationName, argName, moduleName, environment=None):
#     relationName = pli_to_stella_object_of_type(relationName, str)
#     argName = pli_to_stella_object_of_type(argName, str)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object_of_type(plic.pli_sGetInferredBinaryPropositionValues(relationName, argName, moduleName, environment), PlIterator)

# >>> cc('PL-USER')
# <pli.Module /PL-KERNEL-KB/PL-USER>
# >>> list(getInferredBinaryPropositionValues('documentation', 'aggregate'))
# [2015-OCT-22 17:18:00.000 PL] Processing check-types agenda...
# [<pli.StringWrapper ?a is an aggregate>]
# >>> list(getInferredBinaryPropositionValues('documentation', None))
# []

### pli_PlIterator* pli_getPropositionsOf(pli_LogicObject* object, pli_Module* module, pli_Environment* environment);
def getPropositionsOf(object, module=None, environment=None):
    # Combines object and string versions.
    # Supports object, string and other literal arguments.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    object = dwim_pli_atom_to_logic_atom(object, module, environment)
    # PLI to STELLA conversion:
    object = pli_to_stella_object_of_type(object, LogicObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getPropositionsOf(object, module, environment), PlIterator)

def printFacts(obj, stream=None, module=None, environment=None):
    # Supports object and string arguments.
    if isinstance(obj, StellaObject):
        obj = objectToString(obj)
    if module is None:
        module = getCurrentModule(environment)
    elif not isinstance(module, Module):
        module = getModule(module, environment)
    with module as mod:
        eval('(PL-KERNEL/PROCESS-DEFINITIONS)')  # redundant for now
        eval('(PL-KERNEL/PRINT-FACTS ' + str(obj) + ')')

# Obsolete:
### pli_PlIterator* pli_sGetPropositionsOf(char* objectName, char* moduleName, pli_Environment* environment);
# def sGetPropositionsOf(objectName, moduleName, environment=None):
#     objectName = pli_to_stella_object_of_type(objectName, str)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object_of_type(plic.pli_sGetPropositionsOf(objectName, moduleName, environment), PlIterator)

# this works:
# >>> list(getPropositionsOf('aggregate'))
# [<pli.Proposition (CONCEPT AGGREGATE)>, <pli.Proposition (DOCUMENTATION AGGREGATE "?a is an aggregate")>, ...]
# >>> list(getPropositionsOf(getObject('aggregate')))
# [<pli.Proposition (CONCEPT AGGREGATE)>, <pli.Proposition (DOCUMENTATION AGGREGATE "?a is an aggregate")>, ...]
# >>> list(getPropositionsOf("?a is an aggregate"))
# Traceback (most recent call last):
#   ............
# plic.PLIException: Object ?a is an aggregate is not of type <class '__main__.LogicObject'>

### pli_PlIterator* pli_getPropositionsInModule(pli_Module* module, pli_Environment* environment);
def getPropositionsInModule(module=None, environment=None):
    # Supports object and string arguments for `module'.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getPropositionsInModule(module, environment), PlIterator)

# >>> cc('STELLA')
# <pli.Module /STELLA>
# >>> getPropositionsInModule()
# <pli.PlIterator 0 elements>
# >>> getPropositionsInModule('PL-USER')
# <pli.PlIterator 3 elements>
# >>> getPropositionsInModule('PL-KERNEL')
# <pli.PlIterator 1334 elements>
# >>> cc('PL-USER')
# <pli.Module /PL-KERNEL-KB/PL-USER>
# >>> getPropositionsInModule()
# <pli.PlIterator 3 elements>

### pli_boolean pli_isTrueUnaryProposition(pli_LogicObject* relation, pli_Object* arg, pli_Module* module, pli_Environment* environment);
def isTrueUnaryProposition(relation, arg, module=None, environment=None):
    # Supports object, string and other literal arguments.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    if isinstance(relation, str):
        relation = getRelation(relation, module, environment)
    arg = dwim_pli_atom_to_logic_atom(arg, module, environment)
    # PLI to STELLA conversion:
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    arg = pli_to_stella_object_of_type(arg, StellaObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_isTrueUnaryProposition(relation, arg, module, environment), bool)

# >>> isTrueUnaryProposition("concept", "concept")
# True
# >>> isTrueUnaryProposition("variable-arity", "holds")
# True

### pli_boolean pli_isTrueBinaryProposition(pli_LogicObject* relation, pli_Object* arg, pli_Object* value, pli_Module* module, pli_Environment* environment);
def isTrueBinaryProposition(relation, arg, value, module=None, environment=None):
    # Supports object, string and other literal arguments.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    if isinstance(relation, str):
        relation = getRelation(relation, module, environment)
    arg = dwim_pli_atom_to_logic_atom(arg, module, environment)
    value = dwim_pli_atom_to_logic_atom(value, module, environment)
    # PLI to STELLA conversion:
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    arg = pli_to_stella_object_of_type(arg, StellaObject)
    value = pli_to_stella_object_of_type(value, StellaObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_isTrueBinaryProposition(relation, arg, value, module, environment), bool)

# >>> isTrueBinaryProposition("subset-of", "NUMBER", "SCALAR")
# True
# >>> isTrueBinaryProposition("subset-of", "SCALAR", "NUMBER")
# False
# BUT - since these are not explicitly asserted:
# >>> isTrueBinaryProposition("arity", "range", 2)
# False
# >>> isTrueUnaryProposition("single-valued", "arity")
# False

### pli_boolean pli_isTrueNaryProposition(pli_Object* relationAndArguments, pli_Module* module, pli_Environment* environment);
def isTrueNaryProposition(relationAndArguments, module=None, environment=None):
    # Combines object and string versions, uses optional arguments and automatically un/wraps args and return values.
    # Supports object, string and other literal arguments.
    if isinstance(relationAndArguments, str):
        relationAndArguments = pli_to_stella_object_of_type(relationAndArguments, str)
        if isinstance(module, Module):
            module = objectToString(module)
        # at this point, we should have a Python string:
        module = pli_to_stella_object_of_type(module, str)
        environment = pli_to_stella_object_of_type(environment, Environment)
        return stella_to_pli_object_of_type(plic.pli_sIsTrueNaryProposition(relationAndArguments, module, environment), bool)
    else:
        if isinstance(module, str):
            module = getExistingModule(module, environment)
        relationAndArguments = dwim_pli_tree_to_logic_tree(relationAndArguments, module, environment)
        relationAndArguments = pli_to_stella_object_of_type(relationAndArguments, StellaObject)
        module = pli_to_stella_object_of_type(module, Module)
        environment = pli_to_stella_object_of_type(environment, Environment)
        return stella_to_pli_object_of_type(plic.pli_isTrueNaryProposition(relationAndArguments, module, environment), bool)

# >>> isTrueNaryProposition(["subset-of", "LIST", "COLLECTION"])
# True
# >>> isTrueNaryProposition(["subset-of", "COLLECTION", "LIST"])
# False
# >>> isTrueNaryProposition("(subset-of LIST COLLECTION)")
# True
# >>> isTrueNaryProposition("(subset-of COLLECTION LIST)")
# False
# >>> isTrueNaryProposition([getRelation("subset-of"), "LIST", "COLLECTION"])
# True
# >>> isTrueNaryProposition([getRelation("subset-of"), getConcept("LIST"), "COLLECTION"])
# True

# Obsolete:
# ### pli_boolean pli_sIsTrueNaryProposition(char* relationAndArguments, char* moduleName, pli_Environment* environment);
# def sIsTrueProposition(relationAndArguments, moduleName, environment=None):
#     relationAndArguments = pli_to_stella_object_of_type(relationAndArguments, str)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object_of_type(plic.pli_sIsTrueNaryProposition(relationAndArguments, moduleName, environment), bool)

### pli_boolean pli_isTrueProposition(pli_Proposition* proposition, pli_Module* module, pli_Environment* environment);
def isTrueProposition(proposition, module=None, environment=None):
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    proposition = pli_to_stella_object_of_type(proposition, Proposition)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_isTrueProposition(proposition, module, environment), bool)

# >>> getBinaryProposition("subset-of", "LIST", "COLLECTION")
# <pli.Proposition (forall (?l)
#    (<= (COLLECTION ?l)
#        (LIST ?l)))>
# >>> isTrueProposition(getBinaryProposition("subset-of", "LIST", "COLLECTION"))
# True

### pli_boolean pli_isSubrelation(pli_LogicObject* sub, pli_LogicObject* super, pli_Module* module, pli_Environment* environment);
def isSubrelation(sub, super, module=None, environment=None):
    # Supports both object and string arguments.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    # TO DO: think about supporting conversion of kappa/setofall terms:
    if isinstance(sub, str):
        sub = getRelation(sub, module, environment)
    if isinstance(super, str):
        super = getRelation(super, module, environment)
    sub = pli_to_stella_object_of_type(sub, LogicObject)
    super = pli_to_stella_object_of_type(super, LogicObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_isSubrelation(sub, super, module, environment), bool)

# >>> isSubrelation('concept', 'relation')
# True
# >>> isSubrelation('relation', 'relation')
# True
# >>> isSubrelation('relation', 'concept')
# False
# >>> cc('STELLA')
# <pli.Module /STELLA>
# >>> isSubrelation('concept', 'relation', 'PL-USER')
# True

### pli_PlIterator* pli_getProperSubrelations(pli_LogicObject* relation, pli_Module* module, pli_Environment* environment);
def getProperSubrelations(relation, module=None, environment=None):
    # Supports both object and string arguments.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    # TO DO: think about supporting conversion of kappa/setofall terms:
    if isinstance(relation, str):
        relation = getRelation(relation, module, environment)
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getProperSubrelations(relation, module, environment), PlIterator)

# >>> list(getProperSubrelations('relation'))
# [<pli.NamedDescription FUNCTION>, <pli.NamedDescription SKOLEM-FUNCTION>, <pli.NamedDescription CONCEPT>, <pli.NamedDescription FRAME-PREDICATE>, <pli.NamedDescription BINARY-RELATION>, <pli.NamedDescription ANTISYMMETRIC>, <pli.NamedDescription SYMMETRIC>, <pli.NamedDescription IRREFLEXIVE>, <pli.NamedDescription REFLEXIVE>, <pli.NamedDescription TRANSITIVE>]

### pli_PlIterator* pli_getDirectSubrelations(pli_LogicObject* relation, pli_Module* module, pli_Environment* environment);
def getDirectSubrelations(relation, module=None, environment=None):
    # Supports both object and string arguments.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    # TO DO: think about supporting conversion of kappa/setofall terms:
    if isinstance(relation, str):
        relation = getRelation(relation, module, environment)
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getDirectSubrelations(relation, module, environment), PlIterator)

# >>> list(getDirectSubrelations('relation'))
# [<pli.NamedDescription FUNCTION>, <pli.NamedDescription CONCEPT>, <pli.NamedDescription FRAME-PREDICATE>, <pli.NamedDescription BINARY-RELATION>]

### pli_PlIterator* pli_getProperSuperrelations(pli_LogicObject* relation, pli_Module* module, pli_Environment* environment);
def getProperSuperrelations(relation, module=None, environment=None):
    # Supports both object and string arguments.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    # TO DO: think about supporting conversion of kappa/setofall terms:
    if isinstance(relation, str):
        relation = getRelation(relation, module, environment)
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getProperSuperrelations(relation, module, environment), PlIterator)

# >>> list(getProperSuperrelations('concept'))
# [<pli.NamedDescription RELATION>, <pli.NamedDescription SET>, <pli.NamedDescription DUPLICATE-FREE-COLLECTION>, <pli.NamedDescription COLLECTION>, <pli.NamedDescription AGGREGATE>, <pli.NamedDescription DUPLICATE-FREE>]

### pli_PlIterator* pli_getDirectSuperrelations(pli_LogicObject* relation, pli_Module* module, pli_Environment* environment);
def getDirectSuperrelations(relation, module=None, environment=None):
    # Supports both object and string arguments.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    # TO DO: think about supporting conversion of kappa/setofall terms:
    if isinstance(relation, str):
        relation = getRelation(relation, module, environment)
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getDirectSuperrelations(relation, module, environment), PlIterator)

# >>> list(getDirectSuperrelations('concept'))
# [<pli.NamedDescription RELATION>]

### pli_boolean pli_isInstance(pli_Object* object, pli_LogicObject* concept, pli_Module* module, pli_Environment* environment);
def isInstance(object, concept, module=None, environment=None):
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    object = dwim_pli_atom_to_logic_atom(object, module, environment)
    concept = dwim_pli_atom_to_logic_atom(concept, module, environment)
    # PLI to STELLA conversion:
    object = pli_to_stella_object_of_type(object, StellaObject)
    concept = pli_to_stella_object_of_type(concept, LogicObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_isInstance(object, concept, module, environment), bool)

### pli_PlIterator* pli_getConceptInstances(pli_LogicObject* concept, pli_Module* module, pli_Environment* environment);
def getConceptInstances(concept, module=None, environment=None):
    # Combines object and string versions.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    concept = dwim_pli_atom_to_logic_atom(concept, module, environment)
    # PLI to STELLA conversion:
    concept = pli_to_stella_object_of_type(concept, LogicObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getConceptInstances(concept, module, environment), PlIterator)

# Obsolete:
### pli_PlIterator* pli_sGetConceptInstances(char* conceptName, char* moduleName, pli_Environment* environment);
# def sGetConceptInstances(conceptName, moduleName, environment=None):
#     conceptName = pli_to_stella_object_of_type(conceptName, str)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object_of_type(plic.pli_sGetConceptInstances(conceptName, moduleName, environment), PlIterator)

### pli_PlIterator* pli_getDirectConceptInstances(pli_LogicObject* concept, pli_Module* module, pli_Environment* environment);
def getDirectConceptInstances(concept, module=None, environment=None):
    # Combines object and string versions.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    concept = dwim_pli_atom_to_logic_atom(concept, module, environment)
    # PLI to STELLA conversion:
    concept = pli_to_stella_object_of_type(concept, LogicObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getDirectConceptInstances(concept, module, environment), PlIterator)

# Obsolete:
### pli_PlIterator* pli_sGetDirectConceptInstances(char* conceptName, char* moduleName, pli_Environment* environment);
# def sGetDirectConceptInstances(conceptName, moduleName=None, environment=None):
#     conceptName = pli_to_stella_object_of_type(conceptName, str)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object_of_type(plic.pli_sGetDirectConceptInstances(conceptName, moduleName, environment), PlIterator)

### pli_PlIterator* pli_getConceptInstancesMatchingValue(pli_LogicObject* concept, pli_LogicObject* relation, pli_Object* value, pli_Module* module, pli_Environment* environment);
def getConceptInstancesMatchingValue(concept, relation, value, module=None, environment=None):
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    concept = dwim_pli_atom_to_logic_atom(concept, module, environment)
    relation = dwim_pli_atom_to_logic_atom(relation, module, environment)
    value = dwim_pli_atom_to_logic_atom(value, module, environment)
    # PLI to STELLA conversion:
    concept = pli_to_stella_object_of_type(concept, LogicObject)
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    value = pli_to_stella_object_of_type(value, StellaObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getConceptInstancesMatchingValue(concept, relation, value, module, environment), PlIterator)

# pli_Object* pli_getConceptInstanceMatchingValue(pli_LogicObject* concept, pli_LogicObject* relation, pli_Object* value, pli_Module* module, pli_Environment* environment);
def getConceptInstanceMatchingValue(concept, relation, value, module=None, environment=None):
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    concept = dwim_pli_atom_to_logic_atom(concept, module, environment)
    relation = dwim_pli_atom_to_logic_atom(relation, module, environment)
    value = dwim_pli_atom_to_logic_atom(value, module, environment)
    # PLI to STELLA conversion:
    concept = pli_to_stella_object_of_type(concept, LogicObject)
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    value = pli_to_stella_object_of_type(value, StellaObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object(plic.pli_getConceptInstanceMatchingValue(concept, relation, value, module, environment))

### pli_PlIterator* pli_getTypes(pli_LogicObject* object, pli_Module* module, pli_Environment* environment);
def getTypes(object, module=None, environment=None):
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    object = dwim_pli_atom_to_logic_atom(object, module, environment)
    # PLI to STELLA conversion:
    object = pli_to_stella_object_of_type(object, LogicObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getTypes(object, module, environment), PlIterator)

### pli_PlIterator* pli_getDirectTypes(pli_LogicObject* object, pli_Module* module, pli_Environment* environment);
def getDirectTypes(object, module=None, environment=None):
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    object = dwim_pli_atom_to_logic_atom(object, module, environment)
    # PLI to STELLA conversion:
    object = pli_to_stella_object_of_type(object, LogicObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getDirectTypes(object, module, environment), PlIterator)

### pli_PlIterator* pli_getRelationExtension(pli_LogicObject* relation, pli_Module* module, pli_Environment* environment);
def getRelationExtension(relation, module=None, environment=None):
    # Combines object and string versions.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    relation = dwim_pli_atom_to_logic_atom(relation, module, environment)
    # PLI to STELLA conversion:
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getRelationExtension(relation, module, environment), PlIterator)

# Obsolete:
### pli_PlIterator* pli_sGetRelationExtension(char* relationName, pli_Module* module, pli_Environment* environment);
# def sGetRelationExtension(relationName, module=None, environment=None):
#     relationName = pli_to_stella_object_of_type(relationName, str)
#     module = pli_to_stella_object_of_type(module, Module)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object_of_type(plic.pli_sGetRelationExtension(relationName, module, environment), PlIterator)

### pli_Module* pli_getModule(char* name, pli_Environment* environment);
def getModule(name, environment=None):
    # Generalized to allow an actual module object for `name' which is useful for coercion.
    if isinstance(name, Module):
        return name
    name = pli_to_stella_object_of_type(name, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getModule(name, environment), Module)

### pli_Module* pli_getExistingModule(char* name, pli_Environment* environment);
def getExistingModule(name, environment=None):
    # Generalized to allow an actual module object for `name' which is useful for coercion.
    if isinstance(name, Module):
        return name
    if not isinstance(name, str):
        name = str(name)
    name = pli_to_stella_object_of_type(name, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getExistingModule(name, environment), Module)

### pli_Module* pli_getCurrentModule(pli_Environment* environment);
def getCurrentModule(environment=None):
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getCurrentModule(environment), Module)

### pli_Module* pli_getHomeModule(pli_LogicObject* object);
def getHomeModule(object):
    object = pli_to_stella_object_of_type(object, LogicObject)
    return stella_to_pli_object_of_type(plic.pli_getHomeModule(object), Module)

### pli_PlIterator* pli_getModules(pli_boolean kbModulesOnlyP);
def getModules(kbOnly=True):
    kbOnly = pli_to_stella_object_of_type(kbOnly, bool)
    return stella_to_pli_object_of_type(plic.pli_getModules(kbOnly), PlIterator)

### pli_Module* pli_createModule(char* name, pli_Module* parent, pli_boolean caseSensitiveP);
def createModule(name, parent=None, caseSensitive=False, environment=None):
    # Combines object and string versions.
    if isinstance(parent, str):
        parent = getExistingModule(parent, environment)
    name = pli_to_stella_object_of_type(name, str)
    parent = pli_to_stella_object_of_type(parent, Module)
    caseSensitive = pli_to_stella_object_of_type(caseSensitive, bool)
    return stella_to_pli_object_of_type(plic.pli_createModule(name, parent, caseSensitive), Module)

# Obsolete:
### pli_Module* pli_sCreateModule(char* name, char* parentName, pli_boolean caseSensitiveP, pli_Environment* environment);
# def sCreateModule(name, parentName, caseSensitiveP, environment=None):
#     name = pli_to_stella_object_of_type(name, str)
#     parentName = pli_to_stella_object_of_type(parentName, str)
#     caseSensitiveP = pli_to_stella_object_of_type(caseSensitiveP, bool)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object_of_type(plic.pli_sCreateModule(name, parentName, caseSensitiveP, environment), Module)

### pli_Module* pli_changeModule(pli_Module* module);
def changeModule(module=None, environment=None):
    # Combines object and string versions.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    module = pli_to_stella_object_of_type(module, Module)
    return stella_to_pli_object_of_type(plic.pli_changeModule(module), Module)

cc = changeModule

# Obsolete:
### pli_Module* pli_sChangeModule(char* name, pli_Environment* environment);
# def sChangeModule(name, environment=None):
#     name = pli_to_stella_object_of_type(name, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object_of_type(plic.pli_sChangeModule(name, environment), Module)

### pli_Module* pli_clearModule(pli_Module* module);
def clearModule(module=None, environment=None):
    # Combines object and string versions.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    module = pli_to_stella_object_of_type(module, Module)
    return stella_to_pli_object_of_type(plic.pli_clearModule(module), Module)

# Obsolete:
### pli_Module* pli_sClearModule(char* name, pli_Environment* environment);
# def sClearModule(name, environment=None):
#     name = pli_to_stella_object_of_type(name, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object_of_type(plic.pli_sClearModule(name, environment), Module)

### pli_PlIterator* pli_getChildModules(pli_Module* module);
def getChildModules(module=None, environment=None):
    # Combines object and string versions.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    module = pli_to_stella_object_of_type(module, Module)
    return stella_to_pli_object_of_type(plic.pli_getChildModules(module), PlIterator)

# Obsolete:
### pli_PlIterator* pli_sGetChildModules(char* name, pli_Environment* environment);
# def sGetChildModules(name, environment=None):
#     name = pli_to_stella_object_of_type(name, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object_of_type(plic.pli_sGetChildModules(name, environment), PlIterator)

### pli_PlIterator* pli_getParentModules(pli_Module* module);
def getParentModules(module=None, environment=None):
    # Combines object and string versions.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    module = pli_to_stella_object_of_type(module, Module)
    return stella_to_pli_object_of_type(plic.pli_getParentModules(module), PlIterator)

# Obsolete:
### pli_PlIterator* pli_sGetParentModules(char* name, pli_Environment* environment);
# def sGetParentModules(name, environment=None):
#     name = pli_to_stella_object_of_type(name, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object_of_type(plic.pli_sGetParentModules(name, environment), PlIterator)

### char* pli_generateUniqueName(char* prefix, pli_Module* module, pli_Environment* environment);
def generateUniqueName(prefix, module=None, environment=None):
    # Allows a string for `module'.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    prefix = pli_to_stella_object_of_type(prefix, str)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_generateUniqueName(prefix, module, environment), str)

### pli_Keyword* pli_createKeyword(char* name);
def createKeyword(name):
    name = pli_to_stella_object_of_type(name, str)
    return stella_to_pli_object_of_type(plic.pli_createKeyword(name), Keyword)

### pli_Symbol* pli_createSymbol(char* name, pli_Module* module, pli_Environment* environment);
def createSymbol(name, module=None, environment=None):
    # Allows a string for `module'.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    name = pli_to_stella_object_of_type(name, str)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_createSymbol(name, module, environment), Symbol)

# This uncovered a premature GC-bug before, where string arguments passed to plic functions
# were eventually garbage collected by Python and created memory corruption on STELLA side.
# Now we explicitly allocate STELLA strings for such arguments which solves the problem.
# >>> s = pli.createSymbol(pli.generateUniqueName('blah', 'PL-USER'))
# >>> s
# <pli.Symbol BLAH-025>
# >>> n = pli.generateUniqueName('blah', 'PL-USER')
# >>> n
# 'BLAH-026'
# >>> s2 =  pli.createSymbol(n)
# >>> s2
# <pli.Symbol BLAH-026>

### pli_LogicObject* pli_createObject(char* name, pli_LogicObject* concept, pli_Module* module, pli_Environment* environment);
def createObject(name=None, concept=None, module=None, environment=None):
    # Combines object and string versions and allows a mixture of object and string arguments.
    name = pli_to_stella_object_of_type(name, str)
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    if isinstance(concept, str):
        concept = getConcept(concept, module, environment)
    concept = pli_to_stella_object_of_type(concept, LogicObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object(plic.pli_createObject(name, concept, module, environment))

# Obsolete:
### pli_LogicObject* pli_sCreateObject(char* name, char* conceptName, char* moduleName, pli_Environment* environment);
# def sCreateObject(name, conceptName, moduleName, environment=None):
#     name = pli_to_stella_object_of_type(name, str)
#     conceptName = pli_to_stella_object_of_type(conceptName, str)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object(plic.pli_sCreateObject(name, conceptName, moduleName, environment))

### pli_LogicObject* pli_createConcept(char* name, pli_LogicObject* parent, pli_Module* module, pli_Environment* environment);
def createConcept(name, parent=None, module=None, environment=None):
    # Combines object and string versions and allows a mixture of object and string arguments.
    name = pli_to_stella_object_of_type(name, str)
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    if isinstance(parent, str):
        parent = getConcept(parent, module, environment)
    parent = pli_to_stella_object_of_type(parent, LogicObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object(plic.pli_createConcept(name, parent, module, environment))

# Obsolete:
# pli_LogicObject* pli_sCreateConcept(char* name, char* parentName, char* moduleName, pli_Environment* environment);
# def sCreateConcept(name, parentName, moduleName, environment=None):
#     name = pli_to_stella_object_of_type(name, str)
#     parentName = pli_to_stella_object_of_type(parentName, str)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object(plic.pli_sCreateConcept(name, parentName, moduleName, environment))

# pli_LogicObject* pli_createRelation(char* name, int arity, pli_Module* module, pli_Environment* environment);
def createRelation(name, arity, module=None, environment=None):
    name = pli_to_stella_object_of_type(name, str)
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    arity = pli_to_stella_object_of_type(arity, int)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object(plic.pli_createRelation(name, arity, module, environment))

# Obsolete:
# pli_LogicObject* pli_sCreateRelation(char* name, int arity, char* moduleName, pli_Environment* environment);
# def sCreateRelation(name, arity, moduleName, environment=None):
#     name = pli_to_stella_object_of_type(name, str)
#     arity = pli_to_stella_object_of_type(arity, int)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object(plic.pli_sCreateRelation(name, arity, moduleName, environment))

# pli_LogicObject* pli_createFunction(char* name, int arity, pli_Module* module, pli_Environment* environment);
def createFunction(name, arity, module=None, environment=None):
    name = pli_to_stella_object_of_type(name, str)
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    arity = pli_to_stella_object_of_type(arity, int)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object(plic.pli_createFunction(name, arity, module, environment))

# Obsolete:
# pli_LogicObject* pli_sCreateFunction(char* name, int arity, char* moduleName, pli_Environment* environment);
# def sCreateFunction(name, arity, moduleName, environment=None):
#     name = pli_to_stella_object_of_type(name, str)
#     arity = pli_to_stella_object_of_type(arity, int)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object(plic.pli_sCreateFunction(name, arity, moduleName, environment))


# Python now allows us to define PowerLoom relation computations and specialists on the fly and attach
# them to functions and relations so that these computations can be used during inference - VERY COOL.
# 
# There are various things that need to happen to make this work:
# (1) We have to define a specialist or computation function in Python that performs the computation.
# (2) We have to define a C-callable callback for it via ffi.callback so that it can be called
#     from the PowerLoom side when the inference engine tries to use it for inferencing.
# (3) The callback has to be attached to a PowerLoom name that can be linked to a function or relation.
#     Points (2) & (3) are now handled by `registerSpecialistFunction' and `registerComputationFunction'.
# (4) The callback will be called from PowerLoom with STELLA object pointers; therefore, we have to define
#     a Python wrapper, that converts the input arguments and return value from STELLA to PLI and back.
# (5) The name for the computation needs to be attached to the PowerLoom function or relation supported
#     by it, and the function or relation should be optionally defined if requested.
#     Points (4) & (5) are now handled by the @specialist and @computation decorators (see examples).
# (6) The objects reaching and leaving the Python computation now are PLI objects (similar to what the
#     API returns), which might need further conversion to and from Python, e.g., via `str' or `int'
#     and by allocating wrapper objects before returning them.
# (7) To allow the implementation of specialists, we define a limited frame API that lets us get and set
#     the current iterator, access current bindings, set current bindings, and properly unwind in case a
#     binding cannot be assigned as desired.

### void pli_registerSpecialistFunction(char* name, pli_cpp_function_code functionReference, pli_Module* module, pli_Environment* environment);
def registerSpecialistFunction(name, function, module=None, environment=None):
    # Create a C-callable specialist wrapper for the Python `function' and attach it to the STELLA symbol `name'.
    # Accepts string or object module and converts function into a C-callable if necessary.
    # IMPORTANT: if a C-callable callback is passed in, make sure it is pointed to
    # by something on the Python side of things to avoid it being GC-ed.
    name = pli_to_stella_object_of_type(name, str)
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    if callable(function):
        callback = ffi.callback('pli_Keyword*(pli_ControlFrame*, pli_Keyword*)', function)
        # Important: this links the callback object to the function to avoid garbage collection:
        function._pli_callback = callback
        function = callback
    elif isinstance(function, ffi.CData):
        pass
    else:
        raise PLIException("Cannot convert " + str(function) + " into a C-callable function reference")
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    plic.pli_registerSpecialistFunction(name, function, module, environment)

# Obsolete:
# void pli_sRegisterSpecialistFunction(char* name, char* nativeName, char* moduleName, pli_Environment* environment);
# def sRegisterSpecialistFunction(name, nativeName, moduleName=None, environment=None):
#     name = pli_to_stella_object_of_type(name, str)
#     nativeName = pli_to_stella_object_of_type(nativeName, str)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     plic.pli_sRegisterSpecialistFunction(name, nativeName, moduleName, environment)

def specialist(specfun=None, name=None, function=None, relation=None, 
               create=False, arity=None, varargs=False, 
               module='PL-USER', defer=False):
    # Decorator that handles all the callback, wrapping, unwrapping and linking magic to hook up
    # a Python function as the reasoning specialist for a PowerLoom function or relation.
    # STELLA-to-PLI and back object conversion is handled automatically by the callback wrapper; however, the resulting
    # objects are still from the PLI class hierarchy and need to be converted appropriately before being used or
    # passed back to STELLA (for example, a string value will need to be converted to a PLI StringWrapper).
    # `specfun' is the specialist function to be decorated and will only be passed in when this is called functionally.
    # `name' is the STELLA name to be used for this computation.  If unspecified, it will be based on the module-qualified
    # Python name of `specfun'.  `function' or `relation' are used to specify the name of the PowerLoom relation this
    # specialist computation will be linked to.  All names will be interpreted relative to `module'.  If not supplied,
    # the linking of the computation name to a PowerLoom relation needs to be done manually by the user.  If `create' is True,
    # the function or relation will be created by the decorator.  Depending on whether `function' or `relation' was used
    # to specify the PowerLoom name, a `function' or `relation' will be created.  In this case, `arity' also has to be
    # supplied, since the arity of `specfun' is unrelated to the arity of the PowerLoom relation it supports.  If `varargs'
    # is True, the created relation will be marked as 'variable-arity' with `arity' being considered its minimum arity.
    # All definitions and assertions will be performed in `module'.  If `defer' is True, evaluations will be deferred until
    # the next call to `processDeferredCommands'.  In that case, `module' can be the name of a reference object whose home
    # module will be used for the definition.
    def specialist_decorator(specfun):
        # create a wrapper that converts from STELLA to PLI and back to STELLA:
        def specfun_wrapper(frame, lastMove):
            frame = stella_to_pli_object_of_type(frame, ControlFrame)
            lastMove = stella_to_pli_object_of_type(frame, Keyword)
            value = specfun(frame, lastMove)
            return pli_to_stella_object_of_type(value, Keyword)

        # create C-callable wrapper for specfun_wrapper that can be called from PowerLoom
        # (not needed anymore, this is now handled by `registerSpecialistFunction'):
        #callback = ffi.callback('pli_Keyword*(pli_ControlFrame*, pli_Keyword*)', specfun_wrapper)

        # link code to specialist name that can then be linked to a PowerLoom relation: 
        specName = name      # closure vars are read-only
        if specName is None:
            # use qualified Python function name as the default PowerLoom name for the specialist:
            specName = '|' + specfun.__module__ + '.' + specfun.__name__ + '|'
        else:
            specName = str(name)
        if defer:
            evalDeferred(registerSpecialistFunction, module, specName, specfun_wrapper)
        else:
            registerSpecialistFunction(specName, specfun_wrapper, module)

        # if requested create the associated PowerLoom function/relation on the fly:
        funrel = function or relation
        if funrel is not None and create:
            if arity is None:
                raise PLIException("Need arity to create PowerLoom relation for specialist: " + str(specfun))
            creator = (function and createFunction) or createRelation
            if defer:
                evalDeferred(creator, module, funrel, arity) 
                if varargs:
                    evalDeferred(assertUnaryProposition, module, 'variable-arity', funrel)
            else:
                creator(funrel, arity, module)
                if varargs:
                    assertUnaryProposition('variable-arity', funrel, module)
                
        # associate the PowerLoom function/relation with the specialist (does not presume that it is already defined):
        if funrel is not None:
            cmd = '(ASSERT (RELATION-SPECIALIST ' + funrel + ' ' + specName + '))'
            if defer:
                evalDeferred(evalVoid, module, cmd)
            else:
                evalVoid(cmd, module)
        return specfun_wrapper

    # top-level decorator management:
    if specfun is None:
        # we are called as a decorator:
        return specialist_decorator
    else:
        # we are called directly as a function:
        return specialist_decorator(specfun)

"""
@specialist(relation='test-subconcept', module='PL-KERNEL', create=True, arity=2)
def testSubconceptSpecialist(frame, lastMove):
    # Example Python specialist implementation to test and demonstrate the API.
    iterator = getFrameIterator(frame)
    concept = getConcept('CONCEPT', 'PL-KERNEL')
    if iterator is None:
        # first time around:
        if isFrameBindingPattern(frame, 'BB'):
            sub = getNthFrameBinding(frame, 0)
            sup = getNthFrameBinding(frame, 1)
            if isInstance(sub, concept) and isInstance(sup, concept) and isSubrelation(sub, sup):
                return FINAL_SUCCESS
            else:
                return FAILURE
        elif isFrameBindingPattern(frame, '_B'):
            sup = getNthFrameBinding(frame, 1)
            if not isInstance(sup, concept):
                return FAILURE
            iterator = getProperSubrelations(sup)
            setFrameIterator(frame, iterator)
            if setNthFrameBinding(frame, 0, sup):
                # handle the reflexive case first:
                return CONTINUING_SUCCESS
        elif isFrameBindingPattern(frame, 'B_'):
            sub = getNthFrameBinding(frame, 0)
            if not isInstance(sub, concept):
                return FAILURE
            iterator = getProperSuperrelations(sub)
            setFrameIterator(frame, iterator)
            if setNthFrameBinding(frame, 1, sub):
                # handle the reflexive case first:
                return CONTINUING_SUCCESS
        elif isFrameBindingPattern(frame, '__'):
            return FAILURE
    # generate additional solutions:
    for conc in iterator:
        if isInstance(conc, concept):
            if isFrameBindingPattern(frame, '_B'):
                if setNthFrameBinding(frame, 0, conc):
                    return CONTINUING_SUCCESS
            else: # must be the other way around:
                if setNthFrameBinding(frame, 1, conc):
                    return CONTINUING_SUCCESS
    return FAILURE

# >>> list(pli.retrieve('all (test-subconcept ?x collection)'))
# [<pli.NamedDescription COLLECTION>, <pli.NamedDescription LIST>, <pli.NamedDescription NUMERIC-SET>, <pli.NamedDescription DUPLICATE-FREE-COLLECTION>, <pli.NamedDescription SET>, <pli.NamedDescription RELATION>, <pli.NamedDescription FUNCTION>, <pli.NamedDescription SKOLEM-FUNCTION>, <pli.NamedDescription CONCEPT>, <pli.NamedDescription FRAME-PREDICATE>, <pli.NamedDescription BINARY-RELATION>, <pli.NamedDescription DISPLAY-RELATION>, <pli.NamedDescription |FNRole|>, <pli.NamedDescription GROUP>]
# >>> list(pli.retrieve('all (test-subconcept collection ?y)'))
# [<pli.NamedDescription COLLECTION>, <pli.NamedDescription AGGREGATE>]

@specialist(relation='test-subconcept2', module='PL-KERNEL', create=True, arity=2)
def testSubconcept2Specialist(frame, lastMove):
    # Example Python specialist implementation to test and demonstrate the API.
    # Variant of the above that uses `getFrameBindingPattern'.
    iterator = getFrameIterator(frame)
    concept = getConcept('CONCEPT', 'PL-KERNEL')
    bindingPattern = getFrameBindingPattern(frame)
    if iterator is None:
        # first time around:
        if bindingPattern == 'BB':
            sub = getNthFrameBinding(frame, 0)
            sup = getNthFrameBinding(frame, 1)
            if isInstance(sub, concept) and isInstance(sup, concept) and isSubrelation(sub, sup):
                return FINAL_SUCCESS
            else:
                return FAILURE
        elif bindingPattern == '_B':
            sup = getNthFrameBinding(frame, 1)
            if not isInstance(sup, concept):
                return FAILURE
            iterator = getProperSubrelations(sup)
            setFrameIterator(frame, iterator)
            if setNthFrameBinding(frame, 0, sup):
                # handle the reflexive case first:
                return CONTINUING_SUCCESS
        elif bindingPattern == 'B_':
            sub = getNthFrameBinding(frame, 0)
            if not isInstance(sub, concept):
                return FAILURE
            iterator = getProperSuperrelations(sub)
            setFrameIterator(frame, iterator)
            if setNthFrameBinding(frame, 1, sub):
                # handle the reflexive case first:
                return CONTINUING_SUCCESS
        elif bindingPattern == '__':
            return FAILURE
    # generate additional solutions:
    for conc in iterator:
        if isInstance(conc, concept):
            if bindingPattern == '_B':
                if setNthFrameBinding(frame, 0, conc):
                    return CONTINUING_SUCCESS
            else: # must be the other way around:
                if setNthFrameBinding(frame, 1, conc):
                    return CONTINUING_SUCCESS
    return FAILURE
"""

### void pli_registerComputationFunction(char* name, pli_cpp_function_code functionReference, int arity, pli_Module* module, pli_Environment* environment);
def registerComputationFunction(name, function, arity, module=None, environment=None):
    # Create a C-callable computation wrapper for the Python `function' and attach it to the STELLA symbol `name'.
    # Accepts string or object module and converts function into a C-callable if necessary.
    # IMPORTANT: if a C-callable callback is passed in, make sure it is pointed to
    # by something on the Python side of things to avoid it being GC-ed.
    # `arity' is required since it might not match the arity of the wrapper function being passed in.
    name = pli_to_stella_object_of_type(name, str)
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    if callable(function):
        compfunSig = 'pli_Object*(pli_Object*' + ', pli_Object*' * (arity - 1) + ')'
        callback = ffi.callback(compfunSig, function)
        # Important: this links the callback object to the function to avoid garbage collection:
        function._pli_callback = callback
        function = callback
    elif isinstance(function, ffi.CData):
        pass
    else:
        raise PLIException("Cannot convert " + str(function) + " into a C-callable function reference")
    arity = pli_to_stella_object_of_type(arity, int)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    plic.pli_registerComputationFunction(name, function, arity, module, environment)

# Obsolete:
# void pli_sRegisterComputationFunction(char* name, char* nativeName, int arity, char* moduleName, pli_Environment* environment);
# def sRegisterComputationFunction(name, nativeName, arity, moduleName, environment=None):
#     name = pli_to_stella_object_of_type(name, str)
#     nativeName = pli_to_stella_object_of_type(nativeName, str)
#     arity = pli_to_stella_object_of_type(arity, int)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     plic.pli_sRegisterComputationFunction(name, nativeName, arity, moduleName, environment)

def computation(compfun=None, name=None, function=None, relation=None, create=False, arity=None, module='PL-USER', defer=False):
    # Decorator that handles all the callback, wrapping, unwrapping and linking magic to hook up
    # a Python function as the reasoning computation for a computed PowerLoom function or relation.
    # STELLA-to-PLI and back object conversion is handled automatically by the callback wrapper; however, the resulting
    # objects are still from the PLI class hierarchy and need to be converted appropriately before being used or
    # passed back to STELLA (for example, a string value will need to be converted to a PLI StringWrapper).
    # `compfun' is the computation function to be decorated and will only be passed in when this is called functionally.
    # `name' is the STELLA name to be used for this computation.  If unspecified, it will be based on the module-qualified
    # Python name of `compfun'.  `function' or `relation' are used to specify the name of the PowerLoom relation this
    # computation function will be linked to.  All names will be interpreted relative to `module'.  If not supplied,
    # the linking of the computation name to a PowerLoom relation needs to be done manually by the user.  If `create' is True,
    # the function or relation will be created by the decorator.  Depending on whether `function' or `relation' was used
    # to specify the PowerLoom name, a `function' or `relation' will be created.  If `arity' is also supplied, it has to
    # be compatible with the arity of `compfun'.  All definitions and assertions will be performed in `module'.  If `defer'
    # is True, evaluations will be deferred until the next call to `processDeferredCommands'.    In that case, `module' can
    # be the name of a reference object whose home module will be used for the definition.
    def computation_decorator(compfun):
        # create a wrapper that converts from STELLA to PLI and back to STELLA:
        def compfun_wrapper(*args):
            return pli_to_stella_object(compfun(*[stella_to_pli_object(arg) for arg in args]))

        # create C-callable wrapper for compfun_wrapper that can be called from PowerLoom:
        compfunName = compfun.__name__
        compfunModule = compfun.__module__
        compfunArity = compfun.__code__.co_argcount
        # this part is now handled by registerComputationFunction:
        #compfunSig = 'pli_Object*(pli_Object*' + ', pli_Object*' * (compfunArity -1) + ')'
        #callback = ffi.callback(compfunSig, compfun_wrapper)

        # link code to computation name that can then be linked to a PowerLoom relation:
        compName = name      # closure vars are read-only
        if compName is None:
            # use qualified Python function name as the default PowerLoom name for the computation:
            compName = '|' + compfunModule + '.' + compfunName + '|'
        else:
            compName = str(name)
        if defer:
            evalDeferred(registerComputationFunction, module, compName, compfun_wrapper, compfunArity)
        else:
            registerComputationFunction(compName, compfun_wrapper, compfunArity, module)

        # if requested create the associated PowerLoom function/relation on the fly:
        funrel = function or relation
        if funrel is not None and create:
            creator = (function and createFunction) or createRelation
            plArity = (function and (compfunArity + 1)) or compfunArity
            if arity is not None and arity != plArity:
                raise PLIException("Specified PowerLoom arity " + str(arity) + " does not match arity required for computation: " + str(plArity))
            if defer:
                evalDeferred(creator, module, funrel, plArity)
            else:
                creator(funrel, plArity, module)
                
        # associate the PowerLoom function/relation with the computation (does not presume that it is already defined):
        if funrel is not None:
            cmd = """(ASSERT (AND (RELATION-SPECIALIST  """ + funrel + """ COMPUTATION-SPECIALIST)
                                  (RELATION-COMPUTATION """ + funrel + ' ' + compName + """)
                                  (COMPUTED """ + funrel + """)))"""
            if defer:
                evalDeferred(evalVoid, module, cmd)
            else:
                evalVoid(cmd, module)
        return compfun_wrapper

    # top-level decorator management:
    if compfun is None:
        # we are called as a decorator:
        return computation_decorator
    else:
        # we are called directly as a function:
        return computation_decorator(compfun)

"""
@computation(function='test-plus', module='PL-KERNEL', create=True)
def testPlus(x, y):
    return createIntegerWrapper(int(x) + int(y))

# >>> list(pli.retrieve('all (test-plus 2 3 ?x)'))
# [<pli.IntegerLogicWrapper 5>]

@computation(relation='test-equal', module='PL-KERNEL', create=True)
def testEqual(x, y):
    return createBooleanWrapper(x == y)

# >>> pli.sAsk('(test-equal 1 1)')
# <pli.TruthValue TRUE>
# >>> pli.sAsk('(test-equal 1 2)')
# <pli.TruthValue FALSE>
"""

### pli_LogicObject* pli_createEnumeratedList(pli_Cons* members, pli_Module* module, pli_Environment* environment);
def createEnumeratedList(members, module=None, environment=None):
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    members = dwim_pli_tree_to_logic_tree(members, module, environment)
    members = pli_to_stella_object_of_type(members, Cons)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object(plic.pli_createEnumeratedList(members, module, environment))

### pli_LogicObject* pli_createEnumeratedSet(pli_Cons* members, pli_Module* module, pli_Environment* environment);
def createEnumeratedSet(members, module=None, environment=None):
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    members = dwim_pli_tree_to_logic_tree(members, module, environment)
    members = pli_to_stella_object_of_type(members, Cons)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object(plic.pli_createEnumeratedSet(members, module, environment))

### void pli_destroyObject(pli_Object* object);
def destroyObject(obj, module=None, environment=None):
    # Combines object and string versions.
    if isinstance(obj, str):
        if isinstance(module, Module):
            module = objectToString(module)
        obj = pli_to_stella_object_of_type(obj, str)
        module = pli_to_stella_object_of_type(module, str)
        environment = pli_to_stella_object_of_type(environment, Environment)
        plic.pli_sDestroyObject(obj, module, environment)
    else:
        obj = pli_to_stella_object_of_type(obj, StellaObject)
        plic.pli_destroyObject(obj)

# Obsolete:
# void pli_sDestroyObject(char* objectName, char* moduleName, pli_Environment* environment);
# def sDestroyObject(objectName, moduleName=None, environment=None):
#     objectName = pli_to_stella_object_of_type(objectName, str)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     plic.pli_sDestroyObject(objectName, moduleName, environment)

### pli_Proposition* pli_assertUnaryProposition(pli_LogicObject* relation, pli_Object* arg, pli_Module* module, pli_Environment* environment);
def assertUnaryProposition(relation, arg, module=None, environment=None):
    # Supports object, string and other literal arguments.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    if isinstance(relation, str):
        relation = getRelation(relation, module, environment)
    arg = dwim_pli_atom_to_logic_atom(arg, module, environment)
    # PLI to STELLA conversion:
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    arg = pli_to_stella_object_of_type(arg, StellaObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_assertUnaryProposition(relation, arg, module, environment), Proposition)

### pli_Proposition* pli_assertBinaryProposition(pli_LogicObject* relation, pli_Object* arg, pli_Object* value, pli_Module* module, pli_Environment* environment);
def assertBinaryProposition(relation, arg, value, module=None, environment=None):
    # Supports object, string and other literal arguments.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    if isinstance(relation, str):
        relation = getRelation(relation, module, environment)
    arg = dwim_pli_atom_to_logic_atom(arg, module, environment)
    value = dwim_pli_atom_to_logic_atom(value, module, environment)
    # PLI to STELLA conversion:
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    arg = pli_to_stella_object_of_type(arg, StellaObject)
    value = pli_to_stella_object_of_type(value, StellaObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_assertBinaryProposition(relation, arg, value, module, environment), Proposition)

### pli_Proposition* pli_assertNaryProposition(pli_Object* relationAndArguments, pli_Module* module, pli_Environment* environment);
def assertNaryProposition(relationAndArguments, module=None, environment=None):
    # Supports object, string and other literal arguments.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    relationAndArguments = dwim_pli_tree_to_logic_tree(relationAndArguments, module, environment)
    relationAndArguments = pli_to_stella_object_of_type(relationAndArguments, StellaObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_assertNaryProposition(relationAndArguments, module, environment), Proposition)

### pli_Proposition* pli_retractUnaryProposition(pli_LogicObject* relation, pli_Object* arg, pli_Module* module, pli_Environment* environment);
def retractUnaryProposition(relation, arg, module=None, environment=None):
    # Supports object, string and other literal arguments.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    if isinstance(relation, str):
        relation = getRelation(relation, module, environment)
    arg = dwim_pli_atom_to_logic_atom(arg, module, environment)
    # PLI to STELLA conversion:
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    arg = pli_to_stella_object_of_type(arg, StellaObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_retractUnaryProposition(relation, arg, module, environment), Proposition)

### pli_Proposition* pli_retractBinaryProposition(pli_LogicObject* relation, pli_Object* arg, pli_Object* value, pli_Module* module, pli_Environment* environment);
def retractBinaryProposition(relation, arg, value, module=None, environment=None):
    # Supports object, string and other literal arguments.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    if isinstance(relation, str):
        relation = getRelation(relation, module, environment)
    arg = dwim_pli_atom_to_logic_atom(arg, module, environment)
    value = dwim_pli_atom_to_logic_atom(value, module, environment)
    # PLI to STELLA conversion:
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    arg = pli_to_stella_object_of_type(arg, StellaObject)
    value = pli_to_stella_object_of_type(value, StellaObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_retractBinaryProposition(relation, arg, value, module, environment), Proposition)

### pli_Proposition* pli_retractNaryProposition(pli_Object* relationAndArguments, pli_Module* module, pli_Environment* environment);
def retractNaryProposition(relationAndArguments, module=None, environment=None):
    # Supports object, string and other literal arguments.
    if isinstance(module, str):
        module = getExistingModule(module, environment)
    relationAndArguments = dwim_pli_tree_to_logic_tree(relationAndArguments, module, environment)
    relationAndArguments = pli_to_stella_object_of_type(relationAndArguments, StellaObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_retractNaryProposition(relationAndArguments, module, environment), Proposition)

############################################################################################################################
###### Manually post-processed and tested up to here
###### IMPORTANT: make sure :throws-exceptions? TRUE is used in any pli function that might throw an exception
############################################################################################################################

### pli_Proposition* pli_assertProposition(pli_Proposition* proposition, pli_Module* module, pli_Environment* environment);
def assertProposition(proposition, module=None, environment=None):
    proposition = pli_to_stella_object_of_type(proposition, Proposition)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_assertProposition(proposition, module, environment), Proposition)

### pli_PlIterator* pli_sAssertProposition(char* sentence, char* moduleName, pli_Environment* environment);
def sAssertProposition(sentence, moduleName=None, environment=None):
    sentence = pli_to_stella_object_of_type(sentence, str)
    moduleName = pli_to_stella_object_of_type(moduleName, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_sAssertProposition(sentence, moduleName, environment), PlIterator)

"""
# Hmm, this version combines three API functions but returns either a proposition or an iterator (which should be converted to a list); THINK ABOUT THIS
def assertProposition(proposition, module=None, environment=None):
    if isinstance(proposition, Proposition):
        if isinstance(module, str):
            module = getExistingModule(module, environment)
        proposition = pli_to_stella_object_of_type(proposition, Proposition)
        module = pli_to_stella_object_of_type(module, Module)
        environment = pli_to_stella_object_of_type(environment, Environment)
        return stella_to_pli_object_of_type(plic.pli_assertProposition(proposition, module, environment), Proposition)
    elif isinstance(proposition, str):
        if isinstance(module, Module):
            module = objectToString(module)
        proposition = pli_to_stella_object_of_type(proposition, str)
        environment = pli_to_stella_object_of_type(environment, Environment)
        return stella_to_pli_object_of_type(plic.pli_sAssertProposition(proposition, module, environment), PlIterator)
    else:
        return assertNaryProposition(proposition, module, environment)
"""

### pli_Proposition* pli_retractProposition(pli_Proposition* proposition, pli_Module* module, pli_Environment* environment);
def retractProposition(proposition, module=None, environment=None):
    proposition = pli_to_stella_object_of_type(proposition, Proposition)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_retractProposition(proposition, module, environment), Proposition)

### pli_PlIterator* pli_sRetractProposition(char* sentence, char* moduleName, pli_Environment* environment);
def sRetractProposition(sentence, moduleName=None, environment=None):
    sentence = pli_to_stella_object_of_type(sentence, str)
    moduleName = pli_to_stella_object_of_type(moduleName, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_sRetractProposition(sentence, moduleName, environment), PlIterator)

### pli_PlIterator* pli_conceive(pli_Object* sentence, pli_Module* module, pli_Environment* environment);
def conceive(sentence, module=None, environment=None):
    sentence = pli_to_stella_object_of_type(sentence, StellaObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_conceive(sentence, module, environment), PlIterator)

### pli_PlIterator* pli_sConceive(char* sentence, char* moduleName, pli_Environment* environment);
def sConceive(sentence, moduleName=None, environment=None):
    sentence = pli_to_stella_object_of_type(sentence, str)
    moduleName = pli_to_stella_object_of_type(moduleName, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_sConceive(sentence, moduleName, environment), PlIterator)

### pli_PlIterator* pli_getRules(pli_LogicObject* relation, pli_Module* module, pli_Environment* environment);
def getRules(relation, module=None, environment=None):
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getRules(relation, module, environment), PlIterator)

### pli_PlIterator* pli_sGetRules(char* relationName, char* moduleName, pli_Environment* environment);
def sGetRules(relationName, moduleName=None, environment=None):
    relationName = pli_to_stella_object_of_type(relationName, str)
    moduleName = pli_to_stella_object_of_type(moduleName, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_sGetRules(relationName, moduleName, environment), PlIterator)

def printRules(obj, stream=None, module=None, environment=None):
    # Supports object and string arguments.
    eval('(PL-KERNEL/PROCESS-DEFINITIONS)')  # for now, improve this
    if isinstance(obj, StellaObject):
        obj = objectToString(obj)
    if isinstance(module, Module):
        module = objectToString(module)
    sPrintRules(obj, stream, module, environment)

# void pli_sPrintRules(char* name, pli_OutputStream* stream, char* moduleName, pli_Environment* environment);
def sPrintRules(name, stream=None, moduleName=None, environment=None):
    name = pli_to_stella_object_of_type(name, str)
    stream = pli_to_stella_object_of_type(stream, OutputStream)
    moduleName = pli_to_stella_object_of_type(moduleName, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    plic.pli_sPrintRules(name, stream, moduleName, environment)

### void pli_runForwardRules(pli_Object* module, pli_boolean localP, pli_boolean forceP);
def runForwardRules(module=None, local=True, force=False):
    module = pli_to_stella_object_of_type(module, StellaObject)
    local = pli_to_stella_object_of_type(local, bool)
    force = pli_to_stella_object_of_type(force, bool)
    plic.pli_runForwardRules(module, local, force)

### int pli_getArity(pli_LogicObject* relation);
def getArity(relation):
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    return stella_to_pli_object_of_type(plic.pli_getArity(relation), int)

### int pli_sGetArity(char* relationName, char* moduleName, pli_Environment* environment);
def sGetArity(relationName, moduleName=None, environment=None):
    relationName = pli_to_stella_object_of_type(relationName, str)
    moduleName = pli_to_stella_object_of_type(moduleName, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_sGetArity(relationName, moduleName, environment), int)

# pli_LogicObject* pli_getDomain(pli_LogicObject* relation);
def getDomain(relation):
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    return stella_to_pli_object(plic.pli_getDomain(relation))

# pli_LogicObject* pli_sGetDomain(char* relationName, char* moduleName, pli_Environment* environment);
def sGetDomain(relationName, moduleName=None, environment=None):
    relationName = pli_to_stella_object_of_type(relationName, str)
    moduleName = pli_to_stella_object_of_type(moduleName, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object(plic.pli_sGetDomain(relationName, moduleName, environment))

# pli_LogicObject* pli_getRange(pli_LogicObject* relation);
def getRange(relation):
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    return stella_to_pli_object(plic.pli_getRange(relation))

# pli_LogicObject* pli_sGetRange(char* relationName, char* moduleName, pli_Environment* environment);
def sGetRange(relationName, moduleName=None, environment=None):
    relationName = pli_to_stella_object_of_type(relationName, str)
    moduleName = pli_to_stella_object_of_type(moduleName, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object(plic.pli_sGetRange(relationName, moduleName, environment))

# pli_LogicObject* pli_getNthDomain(pli_LogicObject* relation, int n);
def getNthDomain(relation, n):
    relation = pli_to_stella_object_of_type(relation, LogicObject)
    n = pli_to_stella_object_of_type(n, int)
    return stella_to_pli_object(plic.pli_getNthDomain(relation, n))

# pli_LogicObject* pli_sGetNthDomain(char* relationName, int n, char* moduleName, pli_Environment* environment);
def sGetNthDomain(relationName, n, moduleName=None, environment=None):
    relationName = pli_to_stella_object_of_type(relationName, str)
    n = pli_to_stella_object_of_type(n, int)
    moduleName = pli_to_stella_object_of_type(moduleName, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object(plic.pli_sGetNthDomain(relationName, n, moduleName, environment))

# void pli_load(char* filename, pli_Environment* environment);
def load(filename, environment=None):
    filename = pli_to_stella_object_of_type(filename, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    plic.pli_load(filename, environment)

# void pli_loadInModule(char* filename, pli_Module* module, pli_Environment* environment);
def loadInModule(filename, module=None, environment=None):
    filename = pli_to_stella_object_of_type(filename, str)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    plic.pli_loadInModule(filename, module, environment)

# void pli_loadStream(pli_InputStream* stream, pli_Environment* environment);
def loadStream(stream, environment=None):
    stream = pli_to_stella_object_of_type(stream, InputStream)
    environment = pli_to_stella_object_of_type(environment, Environment)
    plic.pli_loadStream(stream, environment)

# void pli_loadStreamInModule(pli_InputStream* stream, pli_Module* module, pli_Environment* environment);
def loadStreamInModule(stream, module=None, environment=None):
    stream = pli_to_stella_object_of_type(stream, InputStream)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    plic.pli_loadStreamInModule(stream, module, environment)

# void pli_loadNativeStream(pli_istream* stream, pli_Environment* environment);
def loadNativeStream(stream, environment=None):
    stream = pli_to_stella_object_of_type(stream, istream)
    environment = pli_to_stella_object_of_type(environment, Environment)
    plic.pli_loadNativeStream(stream, environment)

# void pli_loadNativeStreamInModule(pli_istream* stream, pli_Module* module, pli_Environment* environment);
def loadNativeStreamInModule(stream, module=None, environment=None):
    stream = pli_to_stella_object_of_type(stream, istream)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    plic.pli_loadNativeStreamInModule(stream, module, environment)

### void pli_saveModule(pli_Module* module, char* filename, char* ifexists, pli_Environment* environment);
def saveModule(module, filename, ifexists='replace', environment=None):
    module = pli_to_stella_object_of_type(module, Module)
    filename = pli_to_stella_object_of_type(filename, str)
    ifexists = pli_to_stella_object_of_type(ifexists, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    plic.pli_saveModule(module, filename, ifexists, environment)

# void pli_sSaveModule(char* moduleName, char* filename, char* ifexists, pli_Environment* environment);
def sSaveModule(moduleName, filename, ifexists, environment=None):
    moduleName = pli_to_stella_object_of_type(moduleName, str)
    filename = pli_to_stella_object_of_type(filename, str)
    ifexists = pli_to_stella_object_of_type(ifexists, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    plic.pli_sSaveModule(moduleName, filename, ifexists, environment)

# pli_LogicObject* pli_getPredicate(pli_Proposition* prop);
def getPredicate(prop):
    prop = pli_to_stella_object_of_type(prop, Proposition)
    return stella_to_pli_object(plic.pli_getPredicate(prop))

### int pli_getColumnCount(pli_Object* obj);
def getColumnCount(obj):
    obj = pli_to_stella_object_of_type(obj, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_getColumnCount(obj), int)

# pli_Object* pli_getNthValue(pli_Object* sequence, int n, pli_Module* module, pli_Environment* environment);
def getNthValue(sequence, n, module=None, environment=None):
    sequence = pli_to_stella_object_of_type(sequence, StellaObject)
    n = pli_to_stella_object_of_type(n, int)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object(plic.pli_getNthValue(sequence, n, module, environment))

### char* pli_getNthString(pli_Object* sequence, int n, pli_Module* module, pli_Environment* environment);
def getNthString(sequence, n, module=None, environment=None):
    sequence = pli_to_stella_object_of_type(sequence, StellaObject)
    n = pli_to_stella_object_of_type(n, int)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getNthString(sequence, n, module, environment), str)

### int pli_getNthInteger(pli_Object* sequence, int n, pli_Module* module, pli_Environment* environment);
def getNthInteger(sequence, n, module=None, environment=None):
    sequence = pli_to_stella_object_of_type(sequence, StellaObject)
    n = pli_to_stella_object_of_type(n, int)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getNthInteger(sequence, n, module, environment), int)

# double pli_getNthFloat(pli_Object* sequence, int n, pli_Module* module, pli_Environment* environment);
def getNthFloat(sequence, n, module=None, environment=None):
    sequence = pli_to_stella_object_of_type(sequence, StellaObject)
    n = pli_to_stella_object_of_type(n, int)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object(plic.pli_getNthFloat(sequence, n, module, environment))

# pli_LogicObject* pli_getNthLogicObject(pli_Object* sequence, int n, pli_Module* module, pli_Environment* environment);
def getNthLogicObject(sequence, n, module=None, environment=None):
    sequence = pli_to_stella_object_of_type(sequence, StellaObject)
    n = pli_to_stella_object_of_type(n, int)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object(plic.pli_getNthLogicObject(sequence, n, module, environment))

### pli_Cons* pli_getEnumeratedCollectionMembers(pli_Object* collection, pli_Module* module, pli_Environment* environment);
def getEnumeratedCollectionMembers(collection, module=None, environment=None):
    collection = pli_to_stella_object_of_type(collection, StellaObject)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_getEnumeratedCollectionMembers(collection, module, environment), Cons)

### pli_Object* pli_evaluate(pli_Object* command, pli_Module* module, pli_Environment* environment);
def evaluate(command, module=None, environment=None, void=False):
    # Combines object and string versions, uses optional arguments and automatically un/wraps args and return values.
    # Supports a string or proper object for `module' in both object and string variants.
    # If `void' is True, do not return a value.
    if isinstance(command, str):
        command = pli_to_stella_object_of_type(command, str)
        if isinstance(module, Module):
            module = objectToString(module)
        # at this point, we should have a Python string:
        module = pli_to_stella_object_of_type(module, str)
        environment = pli_to_stella_object_of_type(environment, Environment)
        value = plic.pli_sEvaluate(command, module, environment)
        if not void:
            return stella_to_pli_object(value)
    else:
        command = pli_to_stella_object_of_type(command, StellaObject)
        if isinstance(module, str):
            module = getExistingModule(module, environment)
        # at this point, we should have a Python Module object:
        module = pli_to_stella_object_of_type(module, Module)
        environment = pli_to_stella_object_of_type(environment, Environment)
        value = plic.pli_evaluate(command, module, environment)
        if not void:
            return stella_to_pli_object(value)

# this shadows the Python `eval', but that should be ok, since we usually reference this as `pli.eval':
eval = evaluate

def evalVoid(command, module=None, environment=None):
    # Evaluate `command' without returning its value.
    evaluate(command, module, environment, void=True)

# Obsolete:
# pli_Object* pli_sEvaluate(char* command, char* moduleName, pli_Environment* environment);
# def sEvaluate(command, moduleName, environment=None):
#     command = pli_to_stella_object_of_type(command, str)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object(plic.pli_sEvaluate(command, moduleName, environment))

### void pli_powerloom(pli_Module* module, pli_Environment* environment);
def powerloom(module=None, environment=None):
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    plic.pli_powerloom(module, environment)

### pli_boolean pli_isLogicObject(pli_Object* obj);
def isLogicObject(obj):
    obj = pli_to_stella_object_of_type(obj, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_isLogicObject(obj), bool)

### pli_boolean pli_isSkolem(pli_Object* obj);
def isSkolem(obj):
    obj = pli_to_stella_object_of_type(obj, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_isSkolem(obj), bool)

### pli_boolean pli_isVariable(pli_Object* obj);
def isVariable(obj):
    obj = pli_to_stella_object_of_type(obj, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_isVariable(obj), bool)

### pli_boolean pli_isInteger(pli_Object* obj);
def isInteger(obj):
    obj = pli_to_stella_object_of_type(obj, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_isInteger(obj), bool)

### pli_boolean pli_isFloat(pli_Object* obj);
def isFloat(obj):
    obj = pli_to_stella_object_of_type(obj, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_isFloat(obj), bool)

### pli_boolean pli_isNumber(pli_Object* obj);
def isNumber(obj):
    obj = pli_to_stella_object_of_type(obj, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_isNumber(obj), bool)

### pli_boolean pli_isString(pli_Object* obj);
def isString(obj):
    obj = pli_to_stella_object_of_type(obj, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_isString(obj), bool)

### pli_boolean pli_isEnumeratedCollection(pli_Object* obj);
def isEnumeratedCollection(obj):
    obj = pli_to_stella_object_of_type(obj, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_isEnumeratedCollection(obj), bool)

### pli_boolean pli_isEnumeratedSet(pli_Object* obj);
def isEnumeratedSet(obj):
    obj = pli_to_stella_object_of_type(obj, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_isEnumeratedSet(obj), bool)

### pli_boolean pli_isEnumeratedList(pli_Object* obj);
def isEnumeratedList(obj):
    obj = pli_to_stella_object_of_type(obj, StellaObject)
    return stella_to_pli_object_of_type(plic.pli_isEnumeratedList(obj), bool)

### pli_boolean pli_isTrue(pli_TruthValue* tv);
def isTrue(tv):
    tv = pli_to_stella_object_of_type(tv, TruthValue)
    return stella_to_pli_object_of_type(plic.pli_isTrue(tv), bool)

### pli_boolean pli_isFalse(pli_TruthValue* tv);
def isFalse(tv):
    tv = pli_to_stella_object_of_type(tv, TruthValue)
    return stella_to_pli_object_of_type(plic.pli_isFalse(tv), bool)

### pli_boolean pli_isUnknown(pli_TruthValue* tv);
def isUnknown(tv):
    tv = pli_to_stella_object_of_type(tv, TruthValue)
    return stella_to_pli_object_of_type(plic.pli_isUnknown(tv), bool)

### pli_boolean pli_isKnown(pli_TruthValue* tv);
def isKnown(tv):
    tv = pli_to_stella_object_of_type(tv, TruthValue)
    return stella_to_pli_object_of_type(plic.pli_isKnown(tv), bool)

### pli_boolean pli_isInconsistent(pli_TruthValue* tv);
def isInconsistent(tv):
    tv = pli_to_stella_object_of_type(tv, TruthValue)
    return stella_to_pli_object_of_type(plic.pli_isInconsistent(tv), bool)

### pli_boolean pli_isStrict(pli_TruthValue* tv);
def isStrict(tv):
    tv = pli_to_stella_object_of_type(tv, TruthValue)
    return stella_to_pli_object_of_type(plic.pli_isStrict(tv), bool)

### pli_boolean pli_isDefault(pli_TruthValue* tv);
def isDefault(tv):
    tv = pli_to_stella_object_of_type(tv, TruthValue)
    return stella_to_pli_object_of_type(plic.pli_isDefault(tv), bool)

### pli_TruthValue* pli_ask(pli_Cons* query, pli_Module* module, pli_Environment* environment);
def ask(query, module=None, environment=None):
    query = pli_to_stella_object_of_type(query, Cons)
    module = pli_to_stella_object_of_type(module, Module)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_ask(query, module, environment), TruthValue)

### pli_TruthValue* pli_sAsk(char* query, char* moduleName, pli_Environment* environment);
def sAsk(query, moduleName=None, environment=None):
    query = pli_to_stella_object_of_type(query, str)
    moduleName = pli_to_stella_object_of_type(moduleName, str)
    environment = pli_to_stella_object_of_type(environment, Environment)
    return stella_to_pli_object_of_type(plic.pli_sAsk(query, moduleName, environment), TruthValue)

### pli_PlIterator* pli_retrieve(pli_Cons* query, pli_Module* module, pli_Environment* environment);
### TO DO: create a version of this that takes the query options as Python function keyword args,
###        but that will require unquoting, given that retrieve doesn't evaluate its arguments
def retrieve(query, module=None, environment=None):
    if isinstance(query, str):
        query = pli_to_stella_object_of_type(query, str)
        if isinstance(module, Module):
            module = objectToString(module)
        # at this point, we should have a Python string:
        module = pli_to_stella_object_of_type(module, str)
        environment = pli_to_stella_object_of_type(environment, Environment)
        return stella_to_pli_object_of_type(plic.pli_sRetrieve(query, module, environment), PlIterator)
    else:
        if isinstance(module, str):
            module = getExistingModule(module, environment)
        query = dwim_pli_tree_to_logic_tree(query, module, environment)
        query = pli_to_stella_object_of_type(query, Cons)
        # at this point, we should have a Python Module object:
        module = pli_to_stella_object_of_type(module, Module)
        environment = pli_to_stella_object_of_type(environment, Environment)
        return stella_to_pli_object_of_type(plic.pli_retrieve(query, module, environment), PlIterator)

# Obsolete:
### pli_PlIterator* pli_sRetrieve(char* query, char* moduleName, pli_Environment* environment);
# def sRetrieve(query, moduleName, environment=None):
#     query = pli_to_stella_object_of_type(query, str)
#     moduleName = pli_to_stella_object_of_type(moduleName, str)
#     environment = pli_to_stella_object_of_type(environment, Environment)
#     return stella_to_pli_object_of_type(plic.pli_sRetrieve(query, moduleName, environment), PlIterator)


CONTINUING_SUCCESS = getKeyword('CONTINUING-SUCCESS')
FINAL_SUCCESS      = getKeyword('FINAL-SUCCESS')
FAILURE            = getKeyword('FAILURE')
TERMINAL_FAILURE   = getKeyword('TERMINAL-FAILURE')

### pli_Proposition* pli_getFrameProposition(pli_ControlFrame* frame);
def getFrameProposition(frame):
    frame = pli_to_stella_object_of_type(frame, ControlFrame)
    return stella_to_pli_object_of_type(plic.pli_getFrameProposition(frame), Proposition)

### int pli_getFrameArity(pli_ControlFrame* frame);
def getFrameArity(frame):
    frame = pli_to_stella_object_of_type(frame, ControlFrame)
    return stella_to_pli_object_of_type(plic.pli_getFrameArity(frame), int)

# pli_PlIterator* pli_getFrameIterator(pli_ControlFrame* frame);
def getFrameIterator(frame):
    frame = pli_to_stella_object_of_type(frame, ControlFrame)
    return stella_to_pli_object_of_type(plic.pli_getFrameIterator(frame), PlIterator)

### void pli_setFrameIterator(pli_ControlFrame* frame, pli_PlIterator* iterator);
def setFrameIterator(frame, iterator):
    frame = pli_to_stella_object_of_type(frame, ControlFrame)
    iterator = pli_to_stella_object_of_type(iterator, PlIterator)
    plic.pli_setFrameIterator(frame, iterator)

### pli_Object* pli_getNthFrameArgument(pli_ControlFrame* frame, int n);
def getNthFrameArgument(frame, n):
    frame = pli_to_stella_object_of_type(frame, ControlFrame)
    n = pli_to_stella_object_of_type(n, int)
    return stella_to_pli_object(plic.pli_getNthFrameArgument(frame, n))

### pli_Object* pli_getNthFrameBinding(pli_ControlFrame* frame, int n);
def getNthFrameBinding(frame, n):
    frame = pli_to_stella_object_of_type(frame, ControlFrame)
    n = pli_to_stella_object_of_type(n, int)
    return stella_to_pli_object(plic.pli_getNthFrameBinding(frame, n))

### int pli_setNthFrameBinding(pli_ControlFrame* frame, int n, pli_Object* value);
def setNthFrameBinding(frame, n, value):
    frame = pli_to_stella_object_of_type(frame, ControlFrame)
    n = pli_to_stella_object_of_type(n, int)
    value = pli_to_stella_object_of_type(value, StellaObject)
    return stella_to_pli_object(plic.pli_setNthFrameBinding(frame, n, value))

### int pli_isFrameBindingPattern(pli_ControlFrame* frame, char* pattern);
def isFrameBindingPattern(frame, pattern):
    frame = pli_to_stella_object_of_type(frame, ControlFrame)
    pattern = pli_to_stella_object_of_type(pattern, str)
    return stella_to_pli_object(plic.pli_isFrameBindingPattern(frame, pattern))

### char* pli_getFrameBindingPattern(pli_ControlFrame* frame);
def getFrameBindingPattern(frame):
    frame = pli_to_stella_object_of_type(frame, ControlFrame)
    return stella_to_pli_object_of_type(plic.pli_getFrameBindingPattern(frame), str)

### char* pli_getFrameBindingState(pli_ControlFrame* frame);
def getFrameBindingState(frame):
    frame = pli_to_stella_object_of_type(frame, ControlFrame)
    return stella_to_pli_object_of_type(plic.pli_getFrameBindingState(frame), Cons)

### char* pli_setFrameBindingState(pli_ControlFrame* frame, pli_Cons* state);
def setFrameBindingState(frame, state):
    frame = pli_to_stella_object_of_type(frame, ControlFrame)
    state = pli_to_stella_object_of_type(state, Cons)
    plic.pli_setFrameBindingState(frame, state)

### pli_Object* pli_getPropertyObject(char* property, pli_Object* defaultvalue);
def getPropertyObject(property, default=None):
    property = pli_to_stella_object_of_type(property, str)
    default = pli_to_stella_object_of_type(default, StellaObject)
    return stella_to_pli_object(plic.pli_getPropertyObject(property, default))

### char* pli_getPropertyString(char* property, char* defaultvalue);
def getPropertyString(property, default=None):
    property = pli_to_stella_object_of_type(property, str)
    default = pli_to_stella_object_of_type(default, str)
    return stella_to_pli_object_of_type(plic.pli_getPropertyString(property, default), str)

### char* pli_getProperty(char* property, char* defaultvalue);
def getProperty(property, default=None):
    property = pli_to_stella_object_of_type(property, str)
    default = pli_to_stella_object_of_type(default, str)
    return stella_to_pli_object_of_type(plic.pli_getProperty(property, default), str)

### int pli_getPropertyInteger(char* property, int defaultvalue);
def getPropertyInteger(property, default=0):
    property = pli_to_stella_object_of_type(property, str)
    default = pli_to_stella_object_of_type(default, int)
    return stella_to_pli_object_of_type(plic.pli_getPropertyInteger(property, default), int)

### double pli_getPropertyFloat(char* property, double defaultvalue);
def getPropertyFloat(property, default=0.0):
    property = pli_to_stella_object_of_type(property, str)
    default = pli_to_stella_object_of_type(default, float)
    return stella_to_pli_object_of_type(plic.pli_getPropertyFloat(property, default), float)

### pli_boolean pli_getPropertyBoolean(char* property, pli_boolean defaultvalue);
def getPropertyBoolean(property, default=False):
    property = pli_to_stella_object_of_type(property, str)
    default = pli_to_stella_object_of_type(default, bool)
    return stella_to_pli_object_of_type(plic.pli_getPropertyBoolean(property, default), bool)

### void pli_setPropertyObject(char* property, pli_Object* value);
def setPropertyObject(property, value):
    property = pli_to_stella_object_of_type(property, str)
    value = pli_to_stella_object_of_type(value, StellaObject)
    plic.pli_setPropertyObject(property, value)

### void pli_setPropertyString(char* property, char* value);
def setPropertyString(property, value):
    property = pli_to_stella_object_of_type(property, str)
    value = pli_to_stella_object_of_type(value, str)
    # string value copying is now handled in pli.ste:
    #property = plic.pli_createString(property)
    #value = plic.pli_createString(value)
    plic.pli_setPropertyString(property, value)

### void pli_setProperty(char* property, char* value);
def setProperty(property, value):
    property = pli_to_stella_object_of_type(property, str)
    value = pli_to_stella_object_of_type(value, str)
    plic.pli_setProperty(property, value)

### void pli_setPropertyInteger(char* property, int value);
def setPropertyInteger(property, value):
    property = pli_to_stella_object_of_type(property, str)
    value = pli_to_stella_object_of_type(value, int)
    plic.pli_setPropertyInteger(property, value)

### void pli_setPropertyFloat(char* property, double value);
def setPropertyFloat(property, value):
    property = pli_to_stella_object_of_type(property, str)
    value = pli_to_stella_object_of_type(value, float)
    plic.pli_setPropertyFloat(property, value)

### void pli_setPropertyBoolean(char* property, pli_boolean value);
def setPropertyBoolean(property, value):
    property = pli_to_stella_object_of_type(property, str)
    value = pli_to_stella_object_of_type(value, bool)
    plic.pli_setPropertyBoolean(property, value)

### pli_boolean pli_isDefinedProperty(char* property);
def isDefinedProperty(property):
    property = pli_to_stella_object_of_type(property, str)
    return stella_to_pli_object_of_type(plic.pli_isDefinedProperty(property), bool)

### void pli_printProperties();
def printProperties():
    plic.pli_printProperties()

# pli_cpp_function_code pli_getExceptionHandler();
def getExceptionHandler():
    return stella_to_pli_object(plic.pli_getExceptionHandler())

# void pli_setExceptionHandler(pli_cpp_function_code handler);
def setExceptionHandler(handler):
    handler = pli_to_stella_object_of_type(handler, cpp_function_code)
    plic.pli_setExceptionHandler(handler)


  ##
###### Miscellaneous
  ##

setPropertyBoolean("powerloom.confirmInteractiveExit", False)

deferredCommands = []

def evalDeferred(_func, _refobj, *args, **kwdargs):
    # Hook to schedule the evaluation of `_func' with `args' and `kwdargs' at the next call to `executeDeferredCommands'.
    # If `_refobj' is non-None, evaluate the command only if the named PowerLoom module or object already exists.
    # If it does, evaluate the command in the named module or the home module of the named object.
    # If it does not exist, defer the evaluation until another deferred command creates it or the next call to `executeDeferredCommands'.
    # `_refobj' will be evaluated in the current module, hence, it should generally be a module-qualified name to be robust.
    global deferredCommands
    deferredCommands.append([_func, _refobj, args, kwdargs])

def processDeferredCommands():
    # Execute all currently evaluable `deferredCommands'.
    # Called `process...' in similarity to `process-definitions'.
    global deferredCommands
    while True:
        skippedCommands = []
        for command in deferredCommands:
            skippedCommands.append(command)
            refObj = command[1]
            module = None
            try:
                if refObj is not None:
                    module = getModule(refObj)
                    if module is None:
                        refObj = getObject(refObj)
                        if refObj is not None:
                            module = getHomeModule(refObj)
            except PLIException:
                pass
            if module is not None:
                with getExistingModule(module) as mod:
                    command[0](*command[2], **command[3])
                    skippedCommands.pop()
            elif command[1] is None:
                command[0](*command[2], **command[3])
                skippedCommands.pop()
        if len(deferredCommands) == len(skippedCommands):
            # nothing new could be evaluated:
            break
        else:
            deferredCommands = skippedCommands

@computation(function='python-eval', module='PL-KERNEL-KB', create=True, defer=True)
def pythonEval(expression):
    """PowerLoom computation that evaluates an arbitrary Python `expression.  Only
       succeeds if the result is back-convertible into a PowerLoom literal or object.
       The expression is evaluated relative to the `pli' module, which means functions
       not visible from `pli' need to be fully qualified with their module name which
       will then be imported dynamically into `pli'."""
    return _pythonEval(expression, debug=False)

@computation(function='python-eval-debug', module='PL-KERNEL-KB', create=True, defer=True)
def pythonEvalDebug(expression):
    "Debugging tool which prints any exception messages in case something goes wrong."
    return _pythonEval(expression, debug=True)

modulePrefixRegexp = re.compile('^[a-zA-Z][a-zA-Z0-9_.]*[.]')

def _pythonEval(expression, debug=False, importMissingModules=True):
    # slightly messy since we overloaded `eval' with pli.eval:
    eval = __builtins__.get('eval')
    expression = str(expression)
    try:
        value = eval(expression, globals())
        # TO DO: add a value conversion function for this kind of wrapping,
        #        none of our currentn ones supports this case
        if isinstance(value, unicode):
            value = value.encode('utf8')
        if isinstance(value, str):
            return createStringWrapper(value)
        elif isinstance(value, int):
            return createIntegerWrapper(value)
        elif isinstance(value, bool):
            return createBooleanWrapper(value)
        elif isinstance(value, float):
            return createFloatWrapper(value)
        elif isinstance(value, LogicObject):
            return value
        else:
            return None
    except Exception as e:
        # we failed: try to see if it is because a function module isn't visible from `pli'
        # and import it here; this requires a full module path - is there a better way?
        if importMissingModules:
            modulePrefixMatch = modulePrefixRegexp.match(expression)
            if modulePrefixMatch is not None:
                moduleName = expression[0:modulePrefixMatch.end()-1]
                if getattr(sys.modules[__name__], moduleName, None) is None:
                    try:
                        exec('import ' + moduleName, globals())
                        return _pythonEval(expression, debug=debug, importMissingModules=False)
                    except:
                        pass
        if debug:
            print('ERROR: ' + str(e))
        return None
