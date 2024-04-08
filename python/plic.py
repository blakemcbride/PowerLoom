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

# Low-level Python C interface for PowerLoom PLI needed by pli.py v1

# OBSOLETE: this functionality has now been integrated into stellapi.py,
#           and the new ploompi.py uses that instead.

# Example usage ABI/in-line:
# - see pli.py for a more high-level, Python-ish interface
# - see also http://cffi.readthedocs.org/en/latest/overview.html
#
# % setenv LD_LIBRARY_PATH $KAGG_HOME/native/cpp/lib            # where the PowerLoom C++ libraries reside
# % setenv PYTHONPATH $HOME/Projects/powerloom/sources/logic    # where this file resides
# % python
# Python 2.7.3 (default, Apr 14 2012, 08:58:41) [GCC] on linux2
# Type "help", "copyright", "credits" or "license" for more information.
# >>> from plic import ffi, plic
# >>> 
# >>> mod = pliclib.pli_getCurrentModule(ffi.NULL)
# >>> ffi.string(pliclib.pli_objectToString(mod))
# '/STELLA'
# >>> mod = pliclib.pli_sChangeModule('PL-USER', ffi.NULL)
# >>> ffi.string(pliclib.pli_objectToString(mod))
# '/PL-KERNEL-KB/PL-USER'
# >>>

import sys
import os.path
from cffi import FFI

plic_py_directory = os.path.dirname(sys.modules['plic'].__file__)
plic_header_file = 'pli.h'
plic_header_file_path = [os.path.realpath(os.path.join(plic_py_directory, *subdir)) for subdir
                         in [[os.curdir], [os.pardir, 'native', 'cpp', 'logic'], [os.pardir, 'sources', 'logic']]]

pliclib_library_file = 'liblogic' + str((sys.platform.startswith('darwin') and '.dylib') or '.so')

ffi = FFI()

# We simply load the content of `pli.h' via ffi.cdef (which might be a bit inefficient):
for dir in plic_header_file_path:
    header = os.path.join(dir, plic_header_file)
    if os.path.exists(header):
        with open(header, 'r') as f:
            ffi.cdef(f.read())
        break
else:
    raise Exception('Cannot find PLI C-header file pli.h in any of these locations: ' + plic_header_file_path)

pliclib = ffi.dlopen(pliclib_library_file)
pliclib.pli_initialize()


#### Handling PLI exceptions raised on the C++ side

# This is somewhat tricky, because:
# (1) we can't catch them in C-code, instead we have to catch them on the PLI C++ side and unwrap to the top level there
#     returning a harmless value such as NULL and then check if an exception ocurred or not
# (2) the exception handler callback below can't create a non-local return to the Python environment that called the C function
#     so instead of raising the exception, it simply stores them on the Python side for later inspection
# (3) we have to wrap all pliclib functions that potentially throw exceptions to check right before they return whether an
#     exception was raised, and, if so, finally raise a Python exception at the right place (`defplicfunc' handles the wrapping)

class PLIException(Exception):
    # we use these static slots as global variables acccessed by get/setLastException below:
    lastException = None
    pass

def setLastException(exc):
    PLIException.lastException = exc

def clearLastException():
    PLIException.lastException = None

def getLastException():
    return PLIException.lastException

@ffi.callback("void(char*, char*)")
def exceptionCallbackHandler(msg, ctxt):
    # This only saves the information for the last exception caught on the C-side on the Python side.
    # Unfortunately, raising an exception here will simply print the stack trace and then return;
    # therefore, a special exception wrapper needs to be created that propagates the exception in Python.
    setLastException(PLIException(ffi.string(msg)))

pliclib.pli_setExceptionHandler(exceptionCallbackHandler)


### Protecting PLI objects from premature C-side garbage collection

# The basic problem is that the C++ garbage collector collects objects as soon as there are no more
# global or local variable references to them.  In C/C++, we can assign objects to variables, thus,
# protecting them from being GC-ed is easy.  In Python we don't have that option, since Python variable
# references to C++ objects are not seen by the collector, since they used a different malloc.  We
# can protect objects by wrapping them in uncollectable wrappers, the additional complication is then
# that these wrappers and their protection should be released when objects get GC-ed by Python.
#
# Our approach to address this is the following:
# - Each C-callable API function saves its result in a single value global variable buffer before returning.
#   This guarantees that the return value will stay alive at least until the next API function call is made.
#   Assignment to a global buffer variable is handled by the STELLA translator now during wrapper generation.
#   In a multi-threading environment, locking might be required to assure GC-protection.
# - we now have STELLA-level support via `stella_gcProtectObject' to protect a return value from garbage
#   collection until it is released by a call to `stella_gcReleaseObject'.  Protection is handled by creating
#   uncollectable wrappers via GC_MALLOC_UNCOLLECTABLE that point to the protected object.
# - On the Python side, we want to be able to release an object from GC protection and free its wrapper as
#   soon as the last Python reference to it is eliminated.  To do that, we use Python's weak references,
#   since those allow us to register a finalizer/destructor that is called when the weakly referenced object
#   is garbage collected.  See `gcProtectObject' below for details.
# - this is somewhat tricky and complicated and might have some peformance implications, but it is safe

ffi.cdef('void* stella_gcProtectObject(void* object);')
ffi.cdef('void* stella_gcReleaseObject(void* handle);')

gcObjectRegistry = {}

from weakref import ref

def gcProtectObject(obj):
    # create a GC-protection wrapper via STELLA's `gcProtectObject' which will
    # prevent `obj' from being C++-garbage collected until `gcReleaseObject' is called:
    wrapper = pliclib.stella_gcProtectObject(obj)
    #print 'gcProtectObject', 'wrapper=', wrapper, 'obj=', obj
    # next we create a weak reference to `obj' whose primary purpose is that it
    # allows us to register a destructor to be called when `obj' gets GC-ed by Python:
    weakRef = ref(obj, gcReleaseObject)
    # now we have to store the weak reference in a global table to prevent it from being
    # GC-ed by Python before the protected `obj' is GC-ed;  additionally, we need to store
    # the associated protective wrapper, so we can free it when the registered destructor
    # is called; we cannot attach the wrapper to the protected object in any way, since
    # that object is not available anymore when the destructor is called, thus we store it
    # with the weak reference in the global object registry; another minor wrinkle is that
    # weak refs aren't hashable, so we hash on their object ID - phew:
    gcObjectRegistry[id(weakRef)] = (weakRef, wrapper)
    return obj

def gcReleaseObject(weakRef):
    # Destructor called when the object pointed to by `weakRef' gets GC-ed by Python.
    # First we lookup and remove the object's protection wrapper from the object registry:
    (weakRef, wrapper) = gcObjectRegistry.pop(id(weakRef))
    #print 'gcReleaseObject', 'wrapper=', wrapper
    # Then we release the C++ object from C++ GC-protection:
    pliclib.stella_gcReleaseObject(wrapper)
    
cdataType   = ffi.CData
voidstarType = ffi.typeof('void *')
charstarType = ffi.typeof('char *')
pointerTypes = [voidstarType, charstarType]

def withGcProtection(obj):
    # Wrapper to add GC-protection around a PLI call (just for illustration).
    # This is not used explicitly and instead handled by `defplicfunc' below.
    if isinstance(obj, cdataType) and ffi._backend.typeof(obj) in pointerTypes:
        gcProtectObject(obj)
    return obj


### Defining/Wrapping C-level API functions

# Below we define low-level PLI functions based on the objects in pliclib.
# Instead of using pliclib objects such as `pliclib.pli_retrieve' directly, we define parallel
# intermediate functions in plic.  This allows us to wrap functions where necessary to handle
# gc and exceptions, while still giving us access to the unmodified versions if necessary.
# Should it become necessary, we can define special-purpose wrappers for added efficiency.

def defplicfunc(fun, gc=False, exceptions=False):
    # Return a function object based on `fun' that handles gc protection and/or
    # exception handling depending on whether `gc' and `exceptions' are True.
    # If no wrapping is required, simply return `fun'.
    # TO DO: consider more efficient wrapping by using argument lists that mirror
    # `fun' as opposed to using the generic *args/**kwArgs idiom.
    if gc and exceptions:
        def plicFunctionWrapper(*args, **kwArgs):
            clearLastException()
            value = fun(*args, **kwArgs)
            if (value == None or value == ffi.NULL) and getLastException() != None:
                raise getLastException()
            elif isinstance(value, cdataType) and ffi._backend.typeof(value) in pointerTypes:
                gcProtectObject(value)
            return value
        return plicFunctionWrapper
    elif gc:
        def plicFunctionWrapper(*args, **kwArgs):
            value = fun(*args, **kwArgs)
            if isinstance(value, cdataType) and ffi._backend.typeof(value) in pointerTypes:
                gcProtectObject(value)
            return value
        return plicFunctionWrapper
    elif exceptions:
        def plicFunctionWrapper(*args, **kwArgs):
            clearLastException()
            value = fun(*args, **kwArgs)
            if (value == None or value == ffi.NULL) and getLastException() != None:
                raise getLastException()
            return value
        return plicFunctionWrapper
    return fun

# instead of listing these here exhaustively, we could define programmatic support to
# define the functions and their wrappers automatically; but this will do for now
# (we might also want to do this more dynamically and on-demand instead of all-at-once):

pli_initialize = defplicfunc(pliclib.pli_initialize, exceptions=True)
pli_resetPowerloom = defplicfunc(pliclib.pli_resetPowerloom, exceptions=True)
pli_clearCaches = defplicfunc(pliclib.pli_clearCaches)
pli_plIteratorNextP = defplicfunc(pliclib.pli_plIteratorNextP)
pli_plIteratorValue = defplicfunc(pliclib.pli_plIteratorValue, gc=True)
pli_plIteratorEmptyP = defplicfunc(pliclib.pli_plIteratorEmptyP)
pli_plIteratorIsEmpty = defplicfunc(pliclib.pli_plIteratorIsEmpty)
pli_plIteratorLength = defplicfunc(pliclib.pli_plIteratorLength)
pli_consToPlIterator = defplicfunc(pliclib.pli_consToPlIterator, gc=True)
pli_listToPlIterator = defplicfunc(pliclib.pli_listToPlIterator, gc=True)
pli_iteratorToPlIterator = defplicfunc(pliclib.pli_iteratorToPlIterator, gc=True)
pli_plIteratorListify = defplicfunc(pliclib.pli_plIteratorListify, gc=True)
pli_plIteratorConsify = defplicfunc(pliclib.pli_plIteratorConsify, gc=True)
pli_createCons = defplicfunc(pliclib.pli_createCons, gc=True)
pli_createConsList = defplicfunc(pliclib.pli_createConsList, gc=True)
pli_consLength = defplicfunc(pliclib.pli_consLength)
pli_consIsEmpty = defplicfunc(pliclib.pli_consIsEmpty)
pli_consFirst = defplicfunc(pliclib.pli_consFirst, gc=True)
pli_consRest = defplicfunc(pliclib.pli_consRest, gc=True)
pli_consNth = defplicfunc(pliclib.pli_consNth, gc=True)
pli_consNthRest = defplicfunc(pliclib.pli_consNthRest, gc=True)
pli_consSetFirst = defplicfunc(pliclib.pli_consSetFirst)
pli_consSetRest = defplicfunc(pliclib.pli_consSetRest)
pli_consSetNth = defplicfunc(pliclib.pli_consSetNth)
pli_consSetNthRest = defplicfunc(pliclib.pli_consSetNthRest)
pli_listFirst = defplicfunc(pliclib.pli_listFirst, gc=True)
pli_listRest = defplicfunc(pliclib.pli_listRest, gc=True)
pli_listNth = defplicfunc(pliclib.pli_listNth, gc=True)
pli_createString = defplicfunc(pliclib.pli_createString, gc=True)
pli_createStringWrapper = defplicfunc(pliclib.pli_createStringWrapper, gc=True)
pli_createDirectStringWrapper = defplicfunc(pliclib.pli_createDirectStringWrapper, gc=True)
pli_createIntegerWrapper = defplicfunc(pliclib.pli_createIntegerWrapper, gc=True)
pli_createLongIntegerWrapper = defplicfunc(pliclib.pli_createLongIntegerWrapper, gc=True)
pli_createFloatWrapper = defplicfunc(pliclib.pli_createFloatWrapper, gc=True)
pli_createBooleanWrapper = defplicfunc(pliclib.pli_createBooleanWrapper)
pli_getKeyword = defplicfunc(pliclib.pli_getKeyword, gc=True)
pli_getSymbol = defplicfunc(pliclib.pli_getSymbol, gc=True)
pli_getOperator = defplicfunc(pliclib.pli_getOperator, gc=True, exceptions=True)
pli_getObject = defplicfunc(pliclib.pli_getObject, gc=True, exceptions=True)
pli_sGetObject = defplicfunc(pliclib.pli_sGetObject, gc=True, exceptions=True)
pli_getConcept = defplicfunc(pliclib.pli_getConcept, gc=True, exceptions=True)
pli_sGetConcept = defplicfunc(pliclib.pli_sGetConcept, gc=True, exceptions=True)
pli_getRelation = defplicfunc(pliclib.pli_getRelation, gc=True, exceptions=True)
pli_sGetRelation = defplicfunc(pliclib.pli_sGetRelation, gc=True, exceptions=True)
pli_getUndefinedRelations = defplicfunc(pliclib.pli_getUndefinedRelations, gc=True, exceptions=True)
pli_getNameInModule = defplicfunc(pliclib.pli_getNameInModule, gc=True)
pli_getName = defplicfunc(pliclib.pli_getName, gc=True)
pli_getShortName = defplicfunc(pliclib.pli_getShortName, gc=True)
pli_getSkolemName = defplicfunc(pliclib.pli_getSkolemName, gc=True)
pli_getSkolemShortName = defplicfunc(pliclib.pli_getSkolemShortName, gc=True)
pli_getVariableName = defplicfunc(pliclib.pli_getVariableName, gc=True)
pli_getVariableShortName = defplicfunc(pliclib.pli_getVariableShortName, gc=True)
pli_objectToString = defplicfunc(pliclib.pli_objectToString, gc=True)
pli_objectToInteger = defplicfunc(pliclib.pli_objectToInteger, exceptions=True)
pli_objectToFloat = defplicfunc(pliclib.pli_objectToFloat, exceptions=True)
pli_objectToParsableString = defplicfunc(pliclib.pli_objectToParsableString, gc=True)
pli_getStellaType = defplicfunc(pliclib.pli_getStellaType, gc=True)
pli_getLogicType = defplicfunc(pliclib.pli_getLogicType, gc=True)
pli_getStellaTypeName = defplicfunc(pliclib.pli_getStellaTypeName, gc=True)
pli_getStellaTypeShortName = defplicfunc(pliclib.pli_getStellaTypeShortName, gc=True)
pli_getLogicTypeName = defplicfunc(pliclib.pli_getLogicTypeName, gc=True)
pli_getLogicTypeShortName = defplicfunc(pliclib.pli_getLogicTypeShortName, gc=True)
pli_stringToObject = defplicfunc(pliclib.pli_stringToObject, gc=True, exceptions=True)
pli_stringToStellaExpression = defplicfunc(pliclib.pli_stringToStellaExpression, gc=True, exceptions=True)
pli_getProposition = defplicfunc(pliclib.pli_getProposition, gc=True, exceptions=True)
pli_sGetProposition = defplicfunc(pliclib.pli_sGetProposition, gc=True, exceptions=True)
pli_getPropositions = defplicfunc(pliclib.pli_getPropositions, gc=True, exceptions=True)
pli_sGetPropositions = defplicfunc(pliclib.pli_sGetPropositions, gc=True, exceptions=True)
pli_getInconsistentPropositions = defplicfunc(pliclib.pli_getInconsistentPropositions, gc=True, exceptions=True)
pli_getUnaryPropositions = defplicfunc(pliclib.pli_getUnaryPropositions, gc=True, exceptions=True)
pli_getBinaryProposition = defplicfunc(pliclib.pli_getBinaryProposition, gc=True, exceptions=True)
pli_getBinaryPropositions = defplicfunc(pliclib.pli_getBinaryPropositions, gc=True, exceptions=True)
pli_getInferredBinaryPropositionValues = defplicfunc(pliclib.pli_getInferredBinaryPropositionValues, gc=True, exceptions=True)
pli_sGetInferredBinaryPropositionValues = defplicfunc(pliclib.pli_sGetInferredBinaryPropositionValues, gc=True, exceptions=True)
pli_getPropositionsOf = defplicfunc(pliclib.pli_getPropositionsOf, gc=True, exceptions=True)
pli_sGetPropositionsOf = defplicfunc(pliclib.pli_sGetPropositionsOf, gc=True, exceptions=True)
pli_getPropositionsInModule = defplicfunc(pliclib.pli_getPropositionsInModule, gc=True, exceptions=True)
pli_isTrueUnaryProposition = defplicfunc(pliclib.pli_isTrueUnaryProposition, exceptions=True)
pli_isTrueBinaryProposition = defplicfunc(pliclib.pli_isTrueBinaryProposition)
pli_isTrueNaryProposition = defplicfunc(pliclib.pli_isTrueNaryProposition)
pli_sIsTrueNaryProposition = defplicfunc(pliclib.pli_sIsTrueNaryProposition)
pli_isTrueProposition = defplicfunc(pliclib.pli_isTrueProposition)
pli_isSubrelation = defplicfunc(pliclib.pli_isSubrelation)
pli_getProperSubrelations = defplicfunc(pliclib.pli_getProperSubrelations, gc=True)
pli_getDirectSubrelations = defplicfunc(pliclib.pli_getDirectSubrelations, gc=True)
pli_getProperSuperrelations = defplicfunc(pliclib.pli_getProperSuperrelations, gc=True)
pli_getDirectSuperrelations = defplicfunc(pliclib.pli_getDirectSuperrelations, gc=True)
pli_isInstance = defplicfunc(pliclib.pli_isInstance, exceptions=True)
pli_getConceptInstances = defplicfunc(pliclib.pli_getConceptInstances, gc=True, exceptions=True)
pli_sGetConceptInstances = defplicfunc(pliclib.pli_sGetConceptInstances, gc=True, exceptions=True)
pli_getDirectConceptInstances = defplicfunc(pliclib.pli_getDirectConceptInstances, gc=True, exceptions=True)
pli_sGetDirectConceptInstances = defplicfunc(pliclib.pli_sGetDirectConceptInstances, gc=True)
pli_getConceptInstancesMatchingValue = defplicfunc(pliclib.pli_getConceptInstancesMatchingValue, gc=True)
pli_getConceptInstanceMatchingValue = defplicfunc(pliclib.pli_getConceptInstanceMatchingValue, gc=True)
pli_getTypes = defplicfunc(pliclib.pli_getTypes, gc=True, exceptions=True)
pli_getDirectTypes = defplicfunc(pliclib.pli_getDirectTypes, gc=True, exceptions=True)
pli_getRelationExtension = defplicfunc(pliclib.pli_getRelationExtension, gc=True)
pli_sGetRelationExtension = defplicfunc(pliclib.pli_sGetRelationExtension, gc=True)
pli_getModule = defplicfunc(pliclib.pli_getModule, gc=True, exceptions=True)
pli_getExistingModule = defplicfunc(pliclib.pli_getExistingModule, gc=True, exceptions=True)
pli_getCurrentModule = defplicfunc(pliclib.pli_getCurrentModule, gc=True)
pli_getHomeModule = defplicfunc(pliclib.pli_getHomeModule, gc=True)
pli_getModules = defplicfunc(pliclib.pli_getModules, gc=True)
pli_createModule = defplicfunc(pliclib.pli_createModule, gc=True, exceptions=True)
pli_sCreateModule = defplicfunc(pliclib.pli_sCreateModule, gc=True, exceptions=True)
pli_changeModule = defplicfunc(pliclib.pli_changeModule, gc=True, exceptions=True)
pli_sChangeModule = defplicfunc(pliclib.pli_sChangeModule, gc=True, exceptions=True)
pli_clearModule = defplicfunc(pliclib.pli_clearModule, gc=True, exceptions=True)
pli_sClearModule = defplicfunc(pliclib.pli_sClearModule, gc=True, exceptions=True)
pli_getChildModules = defplicfunc(pliclib.pli_getChildModules, gc=True)
pli_sGetChildModules = defplicfunc(pliclib.pli_sGetChildModules, gc=True)
pli_getParentModules = defplicfunc(pliclib.pli_getParentModules, gc=True)
pli_sGetParentModules = defplicfunc(pliclib.pli_sGetParentModules, gc=True)
pli_generateUniqueName = defplicfunc(pliclib.pli_generateUniqueName, gc=True)
pli_createKeyword = defplicfunc(pliclib.pli_createKeyword, gc=True)
pli_createSymbol = defplicfunc(pliclib.pli_createSymbol, gc=True)
pli_createObject = defplicfunc(pliclib.pli_createObject, gc=True, exceptions=True)
pli_sCreateObject = defplicfunc(pliclib.pli_sCreateObject, gc=True, exceptions=True)
pli_createConcept = defplicfunc(pliclib.pli_createConcept, gc=True, exceptions=True)
pli_sCreateConcept = defplicfunc(pliclib.pli_sCreateConcept, gc=True, exceptions=True)
pli_createRelation = defplicfunc(pliclib.pli_createRelation, gc=True, exceptions=True)
pli_sCreateRelation = defplicfunc(pliclib.pli_sCreateRelation, gc=True, exceptions=True)
pli_createFunction = defplicfunc(pliclib.pli_createFunction, gc=True, exceptions=True)
pli_sCreateFunction = defplicfunc(pliclib.pli_sCreateFunction, gc=True, exceptions=True)
pli_registerSpecialistFunction = defplicfunc(pliclib.pli_registerSpecialistFunction)
pli_sRegisterSpecialistFunction = defplicfunc(pliclib.pli_sRegisterSpecialistFunction)
pli_registerComputationFunction = defplicfunc(pliclib.pli_registerComputationFunction)
pli_sRegisterComputationFunction = defplicfunc(pliclib.pli_sRegisterComputationFunction)
pli_createEnumeratedList = defplicfunc(pliclib.pli_createEnumeratedList, gc=True)
pli_createEnumeratedSet = defplicfunc(pliclib.pli_createEnumeratedSet, gc=True, exceptions=True)
pli_destroyObject = defplicfunc(pliclib.pli_destroyObject, exceptions=True)
pli_sDestroyObject = defplicfunc(pliclib.pli_sDestroyObject, exceptions=True)
pli_assertUnaryProposition = defplicfunc(pliclib.pli_assertUnaryProposition, gc=True, exceptions=True)
pli_assertBinaryProposition = defplicfunc(pliclib.pli_assertBinaryProposition, gc=True, exceptions=True)
pli_assertNaryProposition = defplicfunc(pliclib.pli_assertNaryProposition, gc=True, exceptions=True)
pli_retractUnaryProposition = defplicfunc(pliclib.pli_retractUnaryProposition, gc=True, exceptions=True)
pli_retractBinaryProposition = defplicfunc(pliclib.pli_retractBinaryProposition, gc=True, exceptions=True)
pli_retractNaryProposition = defplicfunc(pliclib.pli_retractNaryProposition, gc=True, exceptions=True)
pli_assertProposition = defplicfunc(pliclib.pli_assertProposition, gc=True, exceptions=True)
pli_sAssertProposition = defplicfunc(pliclib.pli_sAssertProposition, gc=True, exceptions=True)
pli_retractProposition = defplicfunc(pliclib.pli_retractProposition, gc=True, exceptions=True)
pli_sRetractProposition = defplicfunc(pliclib.pli_sRetractProposition, gc=True, exceptions=True)
pli_conceive = defplicfunc(pliclib.pli_conceive, gc=True, exceptions=True)
pli_sConceive = defplicfunc(pliclib.pli_sConceive, gc=True, exceptions=True)
pli_getRules = defplicfunc(pliclib.pli_getRules, gc=True, exceptions=True)
pli_sGetRules = defplicfunc(pliclib.pli_sGetRules, gc=True, exceptions=True)
pli_sPrintRules = defplicfunc(pliclib.pli_sPrintRules, exceptions=True)
pli_runForwardRules = defplicfunc(pliclib.pli_runForwardRules, exceptions=True)
pli_getArity = defplicfunc(pliclib.pli_getArity)
pli_sGetArity = defplicfunc(pliclib.pli_sGetArity)
pli_getDomain = defplicfunc(pliclib.pli_getDomain, gc=True)
pli_sGetDomain = defplicfunc(pliclib.pli_sGetDomain, gc=True)
pli_getRange = defplicfunc(pliclib.pli_getRange, gc=True)
pli_sGetRange = defplicfunc(pliclib.pli_sGetRange, gc=True)
pli_getNthDomain = defplicfunc(pliclib.pli_getNthDomain, gc=True)
pli_sGetNthDomain = defplicfunc(pliclib.pli_sGetNthDomain, gc=True)
pli_load = defplicfunc(pliclib.pli_load, exceptions=True)
pli_loadInModule = defplicfunc(pliclib.pli_loadInModule, exceptions=True)
pli_loadStream = defplicfunc(pliclib.pli_loadStream, exceptions=True)
pli_loadStreamInModule = defplicfunc(pliclib.pli_loadStreamInModule, exceptions=True)
pli_loadNativeStream = defplicfunc(pliclib.pli_loadNativeStream, exceptions=True)
pli_loadNativeStreamInModule = defplicfunc(pliclib.pli_loadNativeStreamInModule, exceptions=True)
pli_saveModule = defplicfunc(pliclib.pli_saveModule, exceptions=True)
pli_sSaveModule = defplicfunc(pliclib.pli_sSaveModule, exceptions=True)
pli_getPredicate = defplicfunc(pliclib.pli_getPredicate, gc=True)
pli_getColumnCount = defplicfunc(pliclib.pli_getColumnCount)
pli_getNthValue = defplicfunc(pliclib.pli_getNthValue, gc=True, exceptions=True)
pli_getNthString = defplicfunc(pliclib.pli_getNthString, gc=True, exceptions=True)
pli_getNthInteger = defplicfunc(pliclib.pli_getNthInteger, exceptions=True)
pli_getNthFloat = defplicfunc(pliclib.pli_getNthFloat, exceptions=True)
pli_getNthLogicObject = defplicfunc(pliclib.pli_getNthLogicObject, gc=True, exceptions=True)
pli_getEnumeratedCollectionMembers = defplicfunc(pliclib.pli_getEnumeratedCollectionMembers, gc=True)
pli_evaluate = defplicfunc(pliclib.pli_evaluate, gc=True, exceptions=True)
pli_sEvaluate = defplicfunc(pliclib.pli_sEvaluate, gc=True, exceptions=True)
pli_powerloom = defplicfunc(pliclib.pli_powerloom, exceptions=True)
pli_isLogicObject = defplicfunc(pliclib.pli_isLogicObject)
pli_isSkolem = defplicfunc(pliclib.pli_isSkolem)
pli_isVariable = defplicfunc(pliclib.pli_isVariable)
pli_isInteger = defplicfunc(pliclib.pli_isInteger)
pli_isFloat = defplicfunc(pliclib.pli_isFloat)
pli_isNumber = defplicfunc(pliclib.pli_isNumber)
pli_isString = defplicfunc(pliclib.pli_isString)
pli_isEnumeratedCollection = defplicfunc(pliclib.pli_isEnumeratedCollection)
pli_isEnumeratedSet = defplicfunc(pliclib.pli_isEnumeratedSet)
pli_isEnumeratedList = defplicfunc(pliclib.pli_isEnumeratedList)
pli_isTrue = defplicfunc(pliclib.pli_isTrue)
pli_isFalse = defplicfunc(pliclib.pli_isFalse)
pli_isUnknown = defplicfunc(pliclib.pli_isUnknown)
pli_isKnown = defplicfunc(pliclib.pli_isKnown)
pli_isInconsistent = defplicfunc(pliclib.pli_isInconsistent)
pli_isStrict = defplicfunc(pliclib.pli_isStrict)
pli_isDefault = defplicfunc(pliclib.pli_isDefault)
pli_ask = defplicfunc(pliclib.pli_ask, gc=True)
pli_sAsk = defplicfunc(pliclib.pli_sAsk, gc=True)
pli_retrieve = defplicfunc(pliclib.pli_retrieve, gc=True, exceptions=True)
pli_sRetrieve = defplicfunc(pliclib.pli_sRetrieve, gc=True, exceptions=True)
pli_getFrameProposition = defplicfunc(pliclib.pli_getFrameProposition, gc=True)
pli_getFrameArity = defplicfunc(pliclib.pli_getFrameArity)
pli_getFrameIterator = defplicfunc(pliclib.pli_getFrameIterator, gc=True)
pli_setFrameIterator = defplicfunc(pliclib.pli_setFrameIterator)
pli_getNthFrameArgument = defplicfunc(pliclib.pli_getNthFrameArgument, gc=True, exceptions=True)
pli_getNthFrameBinding = defplicfunc(pliclib.pli_getNthFrameBinding, gc=True, exceptions=True)
pli_setNthFrameBinding = defplicfunc(pliclib.pli_setNthFrameBinding, exceptions=True)
pli_isFrameBindingPattern = defplicfunc(pliclib.pli_isFrameBindingPattern, exceptions=True)
pli_getFrameBindingPattern = defplicfunc(pliclib.pli_getFrameBindingPattern, gc=True)
pli_getFrameBindingState = defplicfunc(pliclib.pli_getFrameBindingState, gc=True, exceptions=True)
pli_setFrameBindingState = defplicfunc(pliclib.pli_setFrameBindingState, exceptions=True)
pli_getPropertyObject = defplicfunc(pliclib.pli_getPropertyObject, gc=True)
pli_getPropertyString = defplicfunc(pliclib.pli_getPropertyString, gc=True)
pli_getProperty = defplicfunc(pliclib.pli_getProperty, gc=True)
pli_getPropertyInteger = defplicfunc(pliclib.pli_getPropertyInteger)
pli_getPropertyFloat = defplicfunc(pliclib.pli_getPropertyFloat)
pli_getPropertyBoolean = defplicfunc(pliclib.pli_getPropertyBoolean)
pli_setPropertyObject = defplicfunc(pliclib.pli_setPropertyObject)
pli_setPropertyString = defplicfunc(pliclib.pli_setPropertyString)
pli_setProperty = defplicfunc(pliclib.pli_setProperty)
pli_setPropertyInteger = defplicfunc(pliclib.pli_setPropertyInteger)
pli_setPropertyFloat = defplicfunc(pliclib.pli_setPropertyFloat)
pli_setPropertyBoolean = defplicfunc(pliclib.pli_setPropertyBoolean)
pli_isDefinedProperty = defplicfunc(pliclib.pli_isDefinedProperty)
pli_printProperties = defplicfunc(pliclib.pli_printProperties)
pli_getExceptionHandler = defplicfunc(pliclib.pli_getExceptionHandler)
pli_setExceptionHandler = defplicfunc(pliclib.pli_setExceptionHandler)
pli_registerObject = defplicfunc(pliclib.pli_registerObject, gc=True)
pli_unregisterObject = defplicfunc(pliclib.pli_unregisterObject)
