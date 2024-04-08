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
# Portions created by the Initial Developer are Copyright (C) 1997-2022      #
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

"""
High-level Python interface v2 for PowerLoom PLI.
"""

from __future__ import print_function, division, absolute_import

import sys
PY2 = sys.version_info[0] == 2
PY3 = sys.version_info[0] >= 3
if PY3:
    basestring = str
    unicode = str
    long = int

import os
import os.path
import re

import stellapi as spi
import stellapi.stella.pdef as pstella
import stellapi.stella.cdef as cstella


# NOTES, TO DO:
# - complete test suite, at least to the point where each function is called at least once
# - support mapping other keyword arguments onto environment options (e.g., :inference-level 'assertion')
# - many of the options of PowerLoom commands can become bonafide keyword arguments to the Python function.
# + support renaming of keyword arguments such as `caseSensitiveP' to `caseSensitive' in `createModule'
# + remove with-pli-exception-handler in pli.ste (already a no-op but confusing)
# - support lower-cased module names
# - more careful use of _gc/_except/_wrapper args to improve efficiency
# - possibly support different print modes
# - we need to map back from STELLA to Python objects, e.g., for wrapped literals inside cons lists, for example,
#   returned by `list(getInferredBinaryPropositionValues('documentation', 'aggregate'))'
# - figure out what to do with QUERY-ITERATORS returned by queries inside an `evaluate'; the PLI equivalents
#   all map those onto PL-ITERATORS - maybe we just need to add another conversion function and map them
#   onto our mirror class hierarchy
# - we still need to analyze whether there are any remaining cases where a Python-allocated string could become
#   part of a PowerLoom-allocated object; this causes GC problems once the Python object gets GC-ed; we currently
#   don't use plic.pli_createString pervasively, since most of the cases are already handled by PLI, but there
#   might still be some remaining
# - see if we should define NULL float and integer values to use as the defaults of `get-property-integer', etc.
# - we should have an API version of process-definitions and decide whether we will call it automatically for
#   all/some retrieval commands or not?
# - we need better API support to find and create function terms, currently we can only find existing ones with
#   getProposition and friends
# - we should have a loadDirectory function
# - saveModule should support 'append' mode - maybe, also the command should have an outputModule option in case
#   we want to save into a different module than the one we are saving


### Startup

apiModule = sys.modules[__name__]

spi.loadSystem('powerloom')

spi.defnamespace('/LOGIC')
spi.defnamespace('/PLI')

plogic = spi.logic.pdef
ppli   = spi.pli.pdef


### Important classes

# import various classes from other modules into pli for convenience and backwards compatibility:
StellaObject = pstella.Object
Context = pstella.Context
Module = pstella.Module
Cons = pstella.Cons
List = pstella.List
StringWrapper = pstella.StringWrapper
IntegerWrapper = pstella.IntegerWrapper
FloatWrapper = pstella.FloatWrapper
LongIntegerWrapper = pstella.LongIntegerWrapper
NumberWrapper = pstella.NumberWrapper
LogicObject = spi.defclass('logic/logic-object')[0]
NamedDescription = spi.defclass('logic/named-description')[0]
Skolem = spi.defclass('logic/skolem')[0]
PatternVariable = spi.defclass('logic/pattern-variable')[0]
Proposition = spi.defclass('logic/proposition')[0]
TruthValue = spi.defclass('logic/truth-value')[0]
ControlFrame = spi.defclass('logic/control-frame')[0]
Environment = spi.defclass('pli/environment')[0]

@spi.pli.pdef
class _PlIterator(spi.ProxyClass):
    _stellaTypePath = "/PLI/@PL-ITERATOR"

    def __repr__(self):
        if self._stellaObject is not None:
            return '<proxy.' + type(self).__name__ + ' ' + str(len(self)) + ' elements>'
        else:
            return str(self)


### Type conversions

characterEncoding = 'utf8'

def dwimStringToStellaTree(string):
    """Interpret the Python `string' as a printed representation of a STELLA tree and unstringify it,
    unless the first character is a `\' in which case we generate a plain string wrapper.
    """
    if isinstance(string, unicode) and PY2:
        string = string.encode(characterEncoding)
    if len(string) > 0:
        first = string[0]
        if first == '\\':
            return pstella.wrapString(string[1:])
        elif "'`:@(#".find(first) >= 0:
            return stringToStellaExpression(string)
    return pstella.wrapString(string)

def dwimTreeToStellaTree(tree):
    """Convert the Python `tree' into an equivalent STELLA tree.  This is identical to
    `spi.pythonToStellaTree' except that strings are converted via `dwimStringToStellaTree'.
    """
    if isinstance(tree, basestring):
        return dwimStringToStellaTree(tree)
    else:
        return spi.pythonToStellaTree(tree)

def dwimStringToLogicAtom(atom, module=None):
    """Convert the Python string `atom' into an equivalent PowerLoom logic object.
    Since for string literals we don't know whether a symbol or string is meant,
    we try to lookup a logic object with that name (or upcased) first.  If it exists,
    it will be used, otherwise, the string will simply be wrapped.  If the first
    character of `atom' is a `\', we always generate a plain string wrapper.
    """
    # TO DO:
    # - figure out how to handle AND/OR/NOT/etc., since those don't have objects
    #   associated with them; we could special-case or create constants - pli.AND,...
    if isinstance(atom, unicode) and PY2:
        atom = atom.encode(characterEncoding)
    if len(atom) > 0:
        first = atom[0]
        if first == '\\':
            return pstella.wrapString(atom[1:])
        elif first == '?':
            # a variable symbol, we don't use `createSymbol' here so we get case conversion
            # if necessary; maybe we should support this in a more principled way somewhere:
            with coerceToExistingModule(module) as mod:
                return pstella.internSymbol(atom)
        elif first == ':':
            # ditto for keywords:
            with coerceToExistingModule(module) as mod:
                return pstella.internStellaName(atom)
    # if `atom' is interpretable as the name of an object, use the object, otherwise,
    # assume it's meant to be a string (this means, if we do want a string that is also the
    # name of an object, it has to passed as a wrapper object or prefixed with a backslash):
    # NOTE: our previous "solution" of looking up a symbol first fails, since there
    # the name is interpreted literally, and we do not always have an object symbol
    try:
        obj = getObject(atom, module)
        if obj != None:
            return obj
        # handle AND/OR/NOT/etc., since those don't have objects - maybe make this more efficient:
        obj = getOperator(atom)
        if obj != None:
            return obj
    except:
        pass
    return pstella.wrapString(atom)

def dwimTreeToLogicTree(tree, module=None):
    """Convert the Python `tree' into an equivalent STELLA Cons tree.
    This is identical to `spi.pythonToStellaTree' except that strings
    will be converted with `dwimStringToLogicAtom'.
    """
    if isinstance(tree, list) or isinstance(tree, tuple):
        sTree = cstella.NIL
        consfn = cstella.cons
        for elt in tree:
            elt = dwimTreeToLogicTree(elt, module)
            elt = elt is not None and elt._stellaObject or cstella.NULL
            # cons at STELLA level to avoid extraneous wrapping and checking:
            sTree = consfn(elt, sTree)
        return pstella.Cons(_stobj=sTree).reverse()
    elif isinstance(tree, StellaObject):
        return tree
    elif isinstance(tree, basestring):
        return dwimStringToLogicAtom(tree, module)
    # need to test before int, since True/False are also int's:
    elif isinstance(tree, bool):
        return pstella.wrapBoolean(tree)
    elif isinstance(tree, int):
        return pstella.wrapInteger(tree)
    elif isinstance(tree, float):
        return pstella.wrapFloat(tree)
    elif isinstance(tree, long):
        return pstella.wrapLongInteger(tree)
    elif tree == None:
        return tree
    else:
        raise spi.ApiException("Don't know how to convert " + str(tree) + " into a STELLA Cons-tree element")


### API function argument coercion:

def coerceToModule(modSpec):
    """Coerce `modSpec' to an existing module, but allow a None `modSpec' value."""
    if modSpec is None:
        return None
    elif isinstance(modSpec, pstella.Module):
        return modSpec
    else:
        return pstella.getStellaModule(str(modSpec), True)
ppli.coerceToModule = coerceToModule

def coerceToExistingModule(modSpec):
    """Coerce `modSpec' to an existing module or the current module if `modSpec' is None."""
    if modSpec is None:
        return pstella.oMODULEo
    elif isinstance(modSpec, pstella.Module):
        return modSpec
    else:
        return pstella.getStellaModule(str(modSpec), True)
ppli.coerceToExistingModule = coerceToModule

def coerceToModuleName(modNameSpec):
    """Coerce `modNameSpec' to the name of a (not necessarily existing) module, but allow a None value."""
    if modNameSpec is None:
        return None
    elif isinstance(modNameSpec, pstella.Module):
        return modNameSpec.moduleFullName
    else:
        return str(modNameSpec)
ppli.coerceToModuleName = coerceToModuleName

def coerceToExistingModuleName(modNameSpec):
    """Coerce `modNameSpec' to the name of an existing module, but allow a None value."""
    if modNameSpec is None:
        return None
    elif isinstance(modNameSpec, pstella.Module):
        return modNameSpec.moduleFullName
    else:
        module = pstella.getStellaModule(str(modNameSpec), True)
        return module.moduleFullName
ppli.coerceToExistingModuleName = coerceToExistingModuleName

def coerceToConcept(conceptSpec, module=None):
    """Try to coerce `conceptSpec' into a concept object using a combination of
    `getConcept' and `dwimTreeToLogicTree'.  If `conceptSpec' already is a named
    description simply return it without actually checking that it is of type CONCEPT.
    """
    # TO DO: need 'coerceToExistingConcept', otherwise non-existing concept can cause segfault
    if conceptSpec is None:
        return None
    elif isinstance(conceptSpec, NamedDescription):
        # NOTE: this does not check whether we actually get a CONCEPT object here:
        return conceptSpec
    elif isinstance(conceptSpec, str):
        concept = getConcept(conceptSpec, module=module)
        if concept is not None:
            return concept
    elif isinstance(conceptSpec, unicode) and PY2:
        return coerceToConcept(conceptSpec.encode(characterEncoding), module)
    else:
        # NOTE: this does not check whether we actually get a CONCEPT object here:
        return dwimTreeToLogicTree(conceptSpec, module)
ppli.coerceToConcept = coerceToConcept

def coerceToRelation(relationSpec, module=None):
    """Try to coerce `relationSpec' into a relation object using a combination of
    `getRelation' and `dwimTreeToLogicTree'.  If `relationSpec' already is a named
    description simply return it without actually checking that it is of type RELATION.
    """
    # TO DO: need 'coerceToExistingRelation', otherwise non-existing relation can cause segfault
    if relationSpec is None:
        return None
    elif isinstance(relationSpec, NamedDescription):
        # NOTE: this does not check whether we actually get a RELATION object here:
        return relationSpec
    elif isinstance(relationSpec, str):
        relation = getRelation(relationSpec, module=module)
        if relation is not None:
            return relation
    elif isinstance(relationSpec, unicode) and PY2:
        return coerceToRelation(relationSpec.encode(characterEncoding), module)
    else:
        # NOTE: this does not check whether we actually get a RELATION object here:
        return dwimTreeToLogicTree(relationSpec, module)
ppli.coerceToRelation = coerceToRelation

def coerceToLogicAtom(atomSpec, module=None):
    atom = dwimTreeToLogicTree(atomSpec, module)
    if isinstance(atom, pstella.Cons):
        raise spi.ApiException("Cannot coerce " + str(x) + " into a logic atom")
    else:
        return atom
ppli.coerceToLogicAtom = coerceToLogicAtom

def coerceToLogicTree(treeSpec, module=None):
    return dwimTreeToLogicTree(treeSpec, module)
ppli.coerceToLogicTree = coerceToLogicTree

# TO DO: complete these stubs
def coerceToInputStream(streamSpec): 
    # needs to create STELLA input streams from what's provided
    raise spi.ApiException("Not implemented")
ppli.coerceToInputStream = coerceToInputStream

def coerceToNativeInputStream(streamSpec):
    # needs to create native STELLA input streams from what's provided
    raise spi.ApiException("Not implemented")
ppli.coerceToNativeInputStream = coerceToNativeInputStream

# IMPORTANT: these need to use globally usable module qualification paths:
_coerceToModuleStmt   = 'module = stellapi.pli.pdef.coerceToModule(module)'
_coerceToRelationStmt = 'relation = stellapi.pli.pdef.coerceToRelation(relation, module)'
_coerceToConceptStmt  = 'concept = stellapi.pli.pdef.coerceToConcept(concept, module)'
_coerceToArgStmt      = 'arg = stellapi.pli.pdef.coerceToLogicAtom(arg, module)'
_coerceToArg1Stmt     = 'arg1 = stellapi.pli.pdef.coerceToLogicAtom(arg1, module)'
_coerceToArg2Stmt     = 'arg2 = stellapi.pli.pdef.coerceToLogicAtom(arg2, module)'
_coerceToValueStmt    = 'value = stellapi.pli.pdef.coerceToLogicAtom(value, module)'
_coerceToObjectStmt   = 'object = stellapi.pli.pdef.coerceToLogicAtom(object, module)'


### Utilities:

_constantsMap = {}

def defConstant(name, value):
    """Define the named constant `name' to have `value' for the benefit of `parseCommand'."""
    curval = _constantsMap.get(name)
    if curval != None and curval != value:
        raise spi.ApiException('defConstant: constant ' + name + ' already has a value, explicitly remove it first: ' + str(curval))
    else:
        _constantsMap[name] = value

def lookupConstant(name):
    """Return the value of the constant `name', or None if it is not defined."""
    return _constantsMap.get(name)

def deleteConstant(name):
    """Delete the constant `name'."""
    del _constantsMap[name]

def parseCommand(command, *args, **kwArgs):
    """Utility to define Python functions with `args' and `kwArgs' that map onto PowerLoom commands.
    Tries to map argument keywords onto STELLA keywords via `lookupConstant', and converts argument values
    via `dwimTreeToStellaTree'.  The resulting command tree can then be passed to `evaluate' for execution.
    """
    val = lookupConstant(command)
    if val == None:
        val = getSymbol(command)
        if val == None:
            val = getSymbol(command.upper())
            if val == None:
                val = stringToStellaExpression(command)
                if val == None:
                    raise spi.ApiException('parseCommand: cannot map ' + command + ' onto an existing PLI command symbol')
    parsedCommand = [val]
    for arg in args:
        parsedCommand.append(dwimTreeToStellaTree(arg))
    for key in kwArgs:
        val = lookupConstant(key)
        if val == None:
            val = getKeyword(key.upper())
        if val == None:
            raise spi.ApiException('parseCommand: cannot map ' + key + ' onto an existing PLI keyword')
        parsedCommand.append(val)
        parsedCommand.append(lookupConstant(kwArgs[key]) or dwimTreeToStellaTree(kwArgs[key]))
    return parsedCommand


### Load path

spi.defun('stella/set-load-path')
spi.defun('stella/get-load-path')
spi.defun('stella/push-load-path')
spi.defun('stella/pop-load-path')
spi.defun('stella/add-load-path')
spi.defun('stella/drop-load-path')
spi.defun('stella/find-file-in-load-path', extensions=None)

setLoadPath = pstella.setLoadPath
getLoadPath = pstella.getLoadPath
pushLoadPath = pstella.pushLoadPath
popLoadPath = pstella.popLoadPath
addLoadPath = pstella.addLoadPath
dropLoadPath = pstella.dropLoadPath
findFileInLoadPath = pstella.findFileInLoadPath


  ##
###### PLI API Functions
  ##

spi.defun('pli/initialize')
spi.defun('pli/reset-powerloom')
spi.defun('pli/clear-caches')


### PL ITERATOR:

spi.defmethod('pli/pl-iterator.next?')
def plIteratorNextP(self):
    return self.nextP()
spi.defun('pli/pl-iterator-value')
spi.defmethod('pli/pl-iterator.empty?')
def plIteratorEmptyP(self):
    return self.emptyP()
spi.defun('pli/pl-iterator-is-empty')
spi.defmethod('pli/pl-iterator.length')
def plIteratorLength(self):
    return self.length()
spi.defglobal('pli/EMPTY-PL-ITERATOR')

spi.defun('pli/cons-to-pl-iterator')
spi.defun('pli/list-to-pl-iterator')
spi.defun('pli/iterator-to-pl-iterator')
spi.defmethod('pli/pl-iterator.listify')
def plIteratorListify(self):
    return self.listify()
spi.defmethod('pli/pl-iterator.consify')
def plIteratorConsify(self):
    return self.consify()


### STELLA lists and literals:

NIL = pstella.NIL
spi.defun('pli/create-cons')
spi.defun('pli/create-cons-list')
spi.defun('pli/cons-length')
spi.defun('pli/cons-is-empty')
spi.defun('pli/cons-first')
spi.defun('pli/cons-rest')
spi.defun('pli/cons-nth')
spi.defun('pli/cons-nth-rest')
spi.defun('pli/cons-set-first')
spi.defun('pli/cons-set-rest')
spi.defun('pli/cons-set-nth')
spi.defun('pli/cons-set-nth-rest')
spi.defun('pli/list-first')
spi.defun('pli/list-rest')
spi.defun('pli/list-nth')

spi.defun('pli/create-string')
spi.defun('pli/create-string-wrapper')
spi.defun('pli/create-direct-string-wrapper')
spi.defun('pli/create-integer-wrapper')
spi.defun('pli/create-long-integer-wrapper')
spi.defun('pli/create-float-wrapper')
spi.defun('pli/create-boolean-wrapper')


### Names to instances and back:

spi.defun('pli/get-keyword')
spi.defun('pli/get-symbol', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports `module' name strings.""")
spi.defun('pli/get-operator')
spi.defun('pli/get-object', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports `module' name strings.""")
# define this as an alias - to more easily assemble trees:
gob = ppli.getObject
spi.defun('pli/s-get-object', _doc="""\nPython: obsolete, use `getObject' instead.""")
spi.defun('pli/get-concept', module=None, environment=None, _pre=_coerceToModuleStmt)
spi.defun('pli/s-get-concept', _doc="""\nPython: obsolete, use `getConcept' instead.""")
spi.defun('pli/get-relation', module=None, environment=None, _pre=_coerceToModuleStmt)
spi.defun('pli/s-get-relation', _doc="""\nPython: obsolete, use `getRelation' instead.""")

spi.defun('pli/get-undefined-relations', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports `module' name strings.""")
spi.defun('pli/get-name-in-module', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports `module' name strings.""")

spi.defun('pli/get-name')
spi.defun('pli/get-short-name')
spi.defun('pli/get-skolem-name')
spi.defun('pli/get-skolem-short-name')
spi.defun('pli/get-variable-name')
spi.defun('pli/get-variable-short-name')
spi.defun('pli/object-to-string')
spi.defun('pli/object-to-integer')
spi.defun('pli/object-to-float')
spi.defun('pli/object-to-parsable-string')
spi.defun('pli/get-stella-type')
spi.defun('pli/get-logic-type')
spi.defun('pli/get-stella-type-name')
spi.defun('pli/get-stella-type-short-name')
spi.defun('pli/get-logic-type-name')
spi.defun('pli/get-logic-type-short-name')

spi.defglobal('pli/*literal-concept*')
spi.defglobal('pli/*string-concept*')
spi.defglobal('pli/*integer-concept*')
spi.defglobal('pli/*float-concept*')

LITERAL_CONCEPT = ppli.oLITERAL_CONCEPTo
STRING_CONCEPT  = ppli.oSTRING_CONCEPTo
INTEGER_CONCEPT = ppli.oINTEGER_CONCEPTo
FLOAT_CONCEPT   = ppli.oFLOAT_CONCEPTo
CONCEPT_CONCEPT  = ppli.getObject('CONCEPT', module='PL-KERNEL')
FUNCTION_CONCEPT = ppli.getObject('FUNCTION', module='PL-KERNEL')
RELATION_CONCEPT = ppli.getObject('RELATION', module='PL-KERNEL')

spi.defun('pli/string-to-object', module=None, environment=None,
          _pre=[_coerceToModuleStmt, 'type = stellapi.pli.pdef.coerceToConcept(type, module)'],
          _doc="""\nPython: additionally supports strings for `type' and `module'.""")
spi.defun('pli/string-to-stella-expression', module=None, environment=None)


### Proposition retrieval:

spi.defun('pli/get-proposition', module=None, environment=None)
spi.defun('pli/s-get-proposition', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `getProposition' instead.""")

def getProposition(relationAndArguments, module=None, environment=None):
    """Convenience wrapper that supports objects or strings for both `relationAndArguments' and `module'.
    See also help(pli.ppli.getProposition)."""
    if isinstance(relationAndArguments, str):
        module = coerceToExistingModuleName(module)
        return ppli.sGetProposition(relationAndArguments, module, environment)
    else:
        module = coerceToModule(module)
        relationAndArguments = coerceToLogicTree(relationAndArguments, module)
        return ppli.getProposition(relationAndArguments, module, environment)

spi.defun('pli/get-propositions', module=None, environment=None)
spi.defun('pli/s-get-propositions', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `getPropositions' instead.""")

def getPropositions(relationAndArguments, module=None, environment=None):
    """Convenience wrapper that supports objects or strings for both `relationAndArguments' and `module'.
    See also help(pli.ppli.getPropositions)."""
    if isinstance(relationAndArguments, str):
        module = coerceToExistingModuleName(module)
        return ppli.sGetPropositions(relationAndArguments, module, environment)
    else:
        module = coerceToModule(module)
        relationAndArguments = coerceToLogicTree(relationAndArguments, module)
        return ppli.getPropositions(relationAndArguments, module, environment)

spi.defun('pli/get-inconsistent-propositions', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports `module' name strings.""")

spi.defun('pli/get-unary-propositions', arg=None, module=None, environment=None,
          _pre=[_coerceToModuleStmt, _coerceToRelationStmt, _coerceToArgStmt],
          _doc="""\nPython: additionally supports strings for `relation', `arg' and `module'.""")
spi.defun('pli/get-binary-proposition', arg1=None, arg2=None, module=None, environment=None,
          _pre=[_coerceToModuleStmt, _coerceToRelationStmt, _coerceToArg1Stmt, _coerceToArg2Stmt],
          _doc="""\nPython: additionally supports strings for `relation', `arg1', `arg2' and `module'.""")
spi.defun('pli/get-binary-propositions', arg1=None, arg2=None, module=None, environment=None,
          _pre=[_coerceToModuleStmt, _coerceToRelationStmt, _coerceToArg1Stmt, _coerceToArg2Stmt],
          _doc="""\nPython: additionally supports strings for `relation', `arg1', `arg2' and `module'.""")
spi.defun('pli/get-inferred-binary-proposition-values', arg=None, module=None, environment=None,
          _pre=[_coerceToModuleStmt, _coerceToRelationStmt, _coerceToArgStmt],
          _doc="""\nPython: additionally supports strings for `relation', `arg' and `module'.""")
spi.defun('pli/s-get-inferred-binary-proposition-values', argName=None, moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `getInferredBinaryPropositionValues' instead.""")
spi.defun('pli/get-propositions-of', module=None, environment=None, _pre=[_coerceToModuleStmt, _coerceToObjectStmt],
          _doc="""\nPython: additionally supports strings for `object' and `module'.""")
spi.defun('pli/s-get-propositions-of', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `getPropositionsOf' instead.""")
spi.defun('pli/get-propositions-in-module', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module' argument.""")

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


### Probes:

spi.defun('pli/is-true-unary-proposition', module=None, environment=None,
          _pre=[_coerceToModuleStmt, _coerceToRelationStmt, _coerceToArgStmt],
          _doc="""\nPython: additionally supports strings for `relation', `arg' and `module'.""")
spi.defun('pli/is-true-binary-proposition', module=None, environment=None,
          _pre=[_coerceToModuleStmt, _coerceToRelationStmt, _coerceToArgStmt, _coerceToValueStmt],
          _doc="""\nPython: additionally supports strings for `relation', `arg', `value' and `module'.""")
spi.defun('pli/is-true-nary-proposition', module=None, environment=None)
spi.defun('pli/s-is-true-nary-proposition', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `isTrueNaryProposition' instead.""")

def isTrueNaryProposition(relationAndArguments, module=None, environment=None):
    """Convenience wrapper that supports objects or strings for both `relationAndArguments' and `module'.
    See also help(pli.ppli.isTrueNaryProposition)."""
    if isinstance(relationAndArguments, str):
        module = coerceToExistingModuleName(module)
        return ppli.sIsTrueNaryProposition(relationAndArguments, module, environment)
    else:
        module = coerceToModule(module)
        relationAndArguments = coerceToLogicTree(relationAndArguments, module)
        return ppli.isTrueNaryProposition(relationAndArguments, module, environment)

spi.defun('pli/is-true-proposition', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports string arguments for `module'.""")


### Isa and Subsumption Hierarchies:

# TO DO: think about supporting conversion of kappa/setofall relation terms

spi.defun('pli/is-subrelation', module=None, environment=None,
          _pre=[_coerceToModuleStmt, 'sub = stellapi.pli.pdef.coerceToRelation(sub, module)', 'super = stellapi.pli.pdef.coerceToRelation(super, module)'],
          _doc="""\nPython: additionally supports strings for `sub', `super' and `module'.""")
spi.defun('pli/get-proper-subrelations', module=None, environment=None, _pre=[_coerceToModuleStmt, _coerceToRelationStmt],
          _doc="""\nPython: additionally supports strings for `relation' and `module'.""")
spi.defun('pli/get-direct-subrelations', module=None, environment=None, _pre=[_coerceToModuleStmt, _coerceToRelationStmt],
          _doc="""\nPython: additionally supports strings for `relation' and `module'.""")
spi.defun('pli/get-proper-superrelations', module=None, environment=None, _pre=[_coerceToModuleStmt, _coerceToRelationStmt],
          _doc="""\nPython: additionally supports strings for `relation' and `module'.""")
spi.defun('pli/get-direct-superrelations', module=None, environment=None, _pre=[_coerceToModuleStmt, _coerceToRelationStmt],
          _doc="""\nPython: additionally supports strings for `relation' and `module'.""")
spi.defun('pli/is-instance', module=None, environment=None,
          _pre=[_coerceToModuleStmt, _coerceToObjectStmt, _coerceToConceptStmt],
          _doc="""\nPython: additionally supports strings for `object', `concept' and `module'.""")
spi.defun('pli/get-concept-instances', module=None, environment=None, _pre=[_coerceToModuleStmt, _coerceToConceptStmt],
          _doc="""\nPython: additionally supports strings for `concept' and `module'.""")
spi.defun('pli/s-get-concept-instances', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `getConceptInstances' instead.""")
spi.defun('pli/get-direct-concept-instances', module=None, environment=None, _pre=[_coerceToModuleStmt, _coerceToConceptStmt],
          _doc="""\nPython: additionally supports strings for `concept' and `module'.""")
spi.defun('pli/s-get-direct-concept-instances', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `getDirectConceptInstances' instead.""")
spi.defun('pli/get-concept-instances-matching-value', module=None, environment=None,
          _pre=[_coerceToModuleStmt, _coerceToConceptStmt, _coerceToRelationStmt, _coerceToValueStmt],
          _doc="""\nPython: additionally supports strings for `concept', `relation', `value' and `module'.""")
spi.defun('pli/get-concept-instance-matching-value', module=None, environment=None,
          _pre=[_coerceToModuleStmt, _coerceToConceptStmt, _coerceToRelationStmt, _coerceToValueStmt],
          _doc="""\nPython: additionally supports strings for `concept', `relation', `value' and `module'.""")
spi.defun('pli/get-types', module=None, environment=None, _pre=[_coerceToModuleStmt, _coerceToObjectStmt],
          _doc="""\nPython: additionally supports strings for `object' and `module'.""")
spi.defun('pli/get-direct-types', module=None, environment=None, _pre=[_coerceToModuleStmt, _coerceToObjectStmt],
          _doc="""\nPython: additionally supports strings for `object' and `module'.""")
spi.defun('pli/get-relation-extension', module=None, environment=None, _pre=[_coerceToModuleStmt, _coerceToRelationStmt],
          _doc="""\nPython: additionally supports strings for `relation' and `module'.""")
spi.defun('pli/s-get-relation-extension', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `getRelationExtension' instead.""")


### Modules:

spi.defglobal('logic/*pl-kernel-module*')
oPL_KERNEL_MODULEo = spi.logic.pdef.oPL_KERNEL_MODULEo

spi.defun('pli/get-module', environment=None, _pre='name = stellapi.pli.pdef.coerceToModuleName(name)',
          _doc="""\nPython: additionally supports module objects for `name'.""")
spi.defun('pli/get-existing-module', environment=None, _pre='name = stellapi.pli.pdef.coerceToModuleName(name)',
          _doc="""\nPython: additionally supports module objects for `name'.""")
spi.defun('pli/get-current-module', environment=None)
spi.defun('pli/get-home-module')
spi.defun('pli/get-modules', kbModulesOnlyP=None, kbOnly=True, _pre='kbModulesOnlyP = kbOnly',
          _doc="""\nPython: Renamed arg to `kbOnly'.""")
spi.defun('pli/create-module', parent=None, caseSensitiveP=None, caseSensitive=False, environment=None,
          _pre=['parent = stellapi.pli.pdef.coerceToModule(parent)', 'caseSensitiveP = caseSensitive'],
          _doc="""\nPython: additionally supports strings for `parent'  Renamed arg to `caseSensitive'.""")
spi.defun('pli/s-create-module', parentName=None, caseSensitiveP=False, environment=None,
          _doc="""\nPython: obsolete, use `createModule' instead.""")
spi.defun('pli/change-module', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module'.""")
cc = ppli.changeModule
spi.defun('pli/s-change-module', environment=None,
          _doc="""\nPython: obsolete, use `changeModule' instead.""")
spi.defun('pli/clear-module', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module'.""")
spi.defun('pli/s-clear-module', name=None, environment=None,
          _doc="""\nPython: obsolete, use `clearModule' instead.""")
spi.defun('pli/get-child-modules', environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module'.""")
spi.defun('pli/s-get-child-modules', environment=None,
          _doc="""\nPython: obsolete, use `getChildModules' instead.""")
spi.defun('pli/get-parent-modules', environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module'.""")
spi.defun('pli/s-get-parent-modules', environment=None,
          _doc="""\nPython: obsolete, use `getParentModules' instead.""")
spi.defun('pli/generate-unique-name', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module'.""")


### Object creation, destruction:

spi.defun('pli/create-keyword')
spi.defun('pli/create-symbol', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module'.""")

spi.defun('pli/create-object', name=None, concept=None, module=None, environment=None,
          _pre=[_coerceToModuleStmt, _coerceToConceptStmt],
          _doc="""\nPython: additionally supports strings for `concept' and `module'.""")
spi.defun('pli/s-create-object', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `createObject' instead.""")

spi.defun('pli/create-concept', parent=None, module=None, environment=None,
          _pre=[_coerceToModuleStmt, 'parent = stellapi.pli.pdef.coerceToConcept(parent, module)'],
          _doc="""\nPython: additionally supports strings for `parent' and `module'.""")
spi.defun('pli/s-create-concept', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `createConcept' instead.""")

spi.defun('pli/create-relation', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module'.""")
spi.defun('pli/s-create-relation', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `createRelation' instead.""")

spi.defun('pli/create-function', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module'.""")
spi.defun('pli/s-create-function', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `createFunction' instead.""")

spi.defun('pli/create-enumerated-list', module=None, environment=None, 
          _pre=[_coerceToModuleStmt, 'members = stellapi.pli.pdef.coerceToLogicTree(members, module)'],
          _doc="""\nPython: additionally supports lists for `members' and strings for `module'.""")
spi.defun('pli/create-enumerated-set', module=None, environment=None,
           _pre=[_coerceToModuleStmt, 'members = stellapi.pli.pdef.coerceToLogicTree(members, module)'],
          _doc="""\nPython: additionally supports lists for `members' and strings for `module'.""")

spi.defun('pli/destroy-object')
spi.defun('pli/s-destroy-object', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `destroyObject' instead.""")

def destroyObject(obj, module=None, environment=None):
    """Convenience wrapper that supports objects or strings for both `obj' and `module'.
    See also help(pli.ppli.destroyObject)."""
    if isinstance(obj, str):
        module = coerceToExistingModuleName(module)
        ppli.sDestroyObject(obj, module, environment)
    else:
        ppli.destroyObject(obj)


### Specialists and computations:

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

spi.defun('pli/register-specialist-function', module=None, environment=None)
spi.defun('pli/s-register-specialist-function', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `registerSpecialistFunction' instead.""")

def registerSpecialistFunction(name, function, module=None, environment=None):
    """Create a C-callable specialist wrapper for the Python `function' and attach it to the STELLA
    symbol `name'.  Accepts string or object module and converts function into a C-callable if necessary.
    IMPORTANT: if a C-callable callback is passed in, make sure it is pointed to by something on the
    Python side of things to avoid it being GC-ed.
    """
    module = coerceToModule(module)
    if callable(function):
        callback = spi.FFI.callback('void*(void*, void*)', function)
        # Important: this links the callback object to the function to avoid garbage collection:
        function._pli_callback = callback
        function = callback
    elif isinstance(function, spi.FFI.CData):
        pass
    else:
        raise spi.ApiException("Cannot convert " + str(function) + " into a C-callable function reference")
    ppli.registerSpecialistFunction(name, function, module, environment)

def specialist(specfun=None, name=None, function=None, relation=None, 
               create=False, arity=None, varargs=False, 
               module='PL-USER', defer=False):
    """Decorator that handles all the callback, wrapping, unwrapping and linking magic to hook up
    a Python function as the reasoning specialist for a PowerLoom function or relation.
    STELLA-to-Python and back object conversion is handled automatically by the callback wrapper; however, the resulting
    objects are still from the Python class hierarchy and need to be converted appropriately before being used or
    passed back to STELLA (for example, a string value will need to be converted to a PLI StringWrapper).
    `specfun' is the specialist function to be decorated and will only be passed in when this is called functionally.
    `name' is the STELLA name to be used for this computation.  If unspecified, it will be based on the module-qualified
    Python name of `specfun'.  `function' or `relation' are used to specify the name of the PowerLoom relation this
    specialist computation will be linked to.  All names will be interpreted relative to `module'.  If not supplied,
    the linking of the computation name to a PowerLoom relation needs to be done manually by the user.  If `create' is True,
    the function or relation will be created by the decorator.  Depending on whether `function' or `relation' was used
    to specify the PowerLoom name, a `function' or `relation' will be created.  In this case, `arity' also has to be
    supplied, since the arity of `specfun' is unrelated to the arity of the PowerLoom relation it supports.  If `varargs'
    is True, the created relation will be marked as 'variable-arity' with `arity' being considered its minimum arity.
    All definitions and assertions will be performed in `module'.  If `defer' is True, evaluations will be deferred until
    the next call to `processDeferredCommands'.  In that case, `module' can be the name of a reference object whose home
    module will be used for the definition.
    """
    def specialist_decorator(specfun):
        # create a wrapper that converts from STELLA to PLI and back to STELLA:
        def specfun_wrapper(frame, lastMove):
            frame = spi.stellaToPythonObjectOfType(frame, ControlFrame)
            lastMove = spi.stellaToPythonObjectOfType(frame, pstella.Keyword)
            value = specfun(frame, lastMove)
            return spi.pythonToStellaObjectOfType(value, pstella.Keyword)

        # create C-callable wrapper for specfun_wrapper that can be called from PowerLoom
        # (not needed anymore, this is now handled by `registerSpecialistFunction'):
        #callback = ffi.callback('void*(void*, void*)', specfun_wrapper)

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
                raise spi.ApiException("Need arity to create PowerLoom relation for specialist: " + str(specfun))
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


spi.defun('pli/register-computation-function', module=None, environment=None)
spi.defun('pli/s-register-computation-function', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `registerComputationFunction' instead.""")

def registerComputationFunction(name, function, arity, module=None, environment=None):
    """Create a C-callable computation wrapper for the Python `function' and attach it to the STELLA
    symbol `name'.  Accepts string or object module and converts function into a C-callable if necessary.
    IMPORTANT: if a C-callable callback is passed in, make sure it is pointed to by something on the
    Python side of things to avoid it being GC-ed.  `arity' is required since it might not match the
    arity of the wrapper function being passed in.
    """
    module = coerceToModule(module)
    if callable(function):
        compfunSig = 'void*(void*' + ', void*' * (arity - 1) + ')'
        callback = spi.FFI.callback(compfunSig, function)
        # Important: this links the callback object to the function to avoid garbage collection:
        function._pli_callback = callback
        function = callback
    elif isinstance(function, spi.FFI.CData):
        pass
    else:
        raise spi.ApiException("Cannot convert " + str(function) + " into a C-callable function reference")
    ppli.registerComputationFunction(name, function, arity, module, environment)

def computation(compfun=None, name=None, function=None, relation=None, create=False, arity=None, module='PL-USER', defer=False):
    """Decorator that handles all the callback, wrapping, unwrapping and linking magic to hook up
    a Python function as the reasoning computation for a computed PowerLoom function or relation.
    STELLA-to-Python and back object conversion is handled automatically by the callback wrapper; however, the resulting
    objects are still from the PLI class hierarchy and need to be converted appropriately before being used or
    passed back to STELLA (for example, a string value will need to be converted to a PLI StringWrapper).
    `compfun' is the computation function to be decorated and will only be passed in when this is called functionally.
    `name' is the STELLA name to be used for this computation.  If unspecified, it will be based on the module-qualified
    Python name of `compfun'.  `function' or `relation' are used to specify the name of the PowerLoom relation this
    computation function will be linked to.  All names will be interpreted relative to `module'.  If not supplied,
    the linking of the computation name to a PowerLoom relation needs to be done manually by the user.  If `create' is True,
    the function or relation will be created by the decorator.  Depending on whether `function' or `relation' was used
    to specify the PowerLoom name, a `function' or `relation' will be created.  If `arity' is also supplied, it has to
    be compatible with the arity of `compfun'.  All definitions and assertions will be performed in `module'.  If `defer'
    is True, evaluations will be deferred until the next call to `processDeferredCommands'.    In that case, `module' can
    be the name of a reference object whose home module will be used for the definition.
    """
    def computation_decorator(compfun):
        # create a wrapper that converts from STELLA to PLI and back to STELLA:
        def compfun_wrapper(*args):
            return spi.pythonToStellaObject(compfun(*[spi.stellaToPythonObject(arg) for arg in args]))

        # create C-callable wrapper for compfun_wrapper that can be called from PowerLoom:
        compfunName = compfun.__name__
        compfunModule = compfun.__module__
        compfunArity = compfun.__code__.co_argcount
        # this part is now handled by registerComputationFunction:
        #compfunSig = 'void*(void*' + ', void*' * (compfunArity -1) + ')'
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
                raise spi.ApiException("Specified PowerLoom arity " + str(arity) + " does not match arity required for computation: " + str(plArity))
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


### Assert, retract:

spi.defun('pli/assert-unary-proposition', module=None, environment=None,
          _pre=[_coerceToModuleStmt, _coerceToRelationStmt, _coerceToArgStmt],
          _doc="""\nPython: additionally supports strings for `relation', `arg' and `module'.""")
spi.defun('pli/assert-binary-proposition', module=None, environment=None,
          _pre=[_coerceToModuleStmt, _coerceToRelationStmt, _coerceToArgStmt, _coerceToValueStmt],
          _doc="""\nPython: additionally supports strings for `relation', `arg', `value' and `module'.""")
spi.defun('pli/assert-nary-proposition', module=None, environment=None,
          _pre=[_coerceToModuleStmt, 'relationAndArguments = stellapi.pli.pdef.coerceToLogicTree(relationAndArguments, module)'],
          _doc="""\nPython: additionally supports trees for `relationAndArguments', and strings for `module'.""")

spi.defun('pli/assert-proposition', module=None, environment=None)
spi.defun('pli/s-assert-proposition', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `assertProposition' instead.""")

def assertProposition(proposition, module=None, environment=None):
    """Convenience wrapper that supports objects or strings for both `proposition' and `module'.
    See also help(pli.ppli.assertProposition)."""
    if isinstance(proposition, Proposition):
        module = coerceToModule(module)
        return ppli.assertProposition(proposition, module, environment)
    elif isinstance(proposition, str):
        module = coerceToExistingModuleName(module)
        # this generates an iterator which we un/listify here if possible:
        props = list(ppli.sAssertProposition(proposition, module, environment))
        return len(props) == 1 and props[0] or props
    else:
        return assertNaryProposition(proposition, module, environment)

spi.defun('pli/retract-unary-proposition', module=None, environment=None,
          _pre=[_coerceToModuleStmt, _coerceToRelationStmt, _coerceToArgStmt],
          _doc="""\nPython: additionally supports strings for `relation', `arg' and `module'.""")
spi.defun('pli/retract-binary-proposition', module=None, environment=None,
          _pre=[_coerceToModuleStmt, _coerceToRelationStmt, _coerceToArgStmt, _coerceToValueStmt],
          _doc="""\nPython: additionally supports strings for `relation', `arg', `value' and `module'.""")
spi.defun('pli/retract-nary-proposition', module=None, environment=None,
          _pre=[_coerceToModuleStmt, 'relationAndArguments = stellapi.pli.pdef.coerceToLogicTree(relationAndArguments, module)'],
          _doc="""\nPython: additionally supports trees for `relationAndArguments', and strings for `module'.""")

spi.defun('pli/retract-proposition', module=None, environment=None)
spi.defun('pli/s-retract-proposition', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `retractProposition' instead.""")

def retractProposition(proposition, module=None, environment=None):
    """Convenience wrapper that supports objects or strings for both `proposition' and `module'.
    See also help(pli.ppli.retractProposition)."""
    if isinstance(proposition, Proposition):
        module = coerceToModule(module)
        return ppli.retractProposition(proposition, module, environment)
    elif isinstance(proposition, str):
        module = coerceToExistingModuleName(module)
        # this generates an iterator which we un/listify here if possible:
        props = list(ppli.sRetractProposition(proposition, module, environment))
        return len(props) == 1 and props[0] or props
    else:
        return retractNaryProposition(proposition, module, environment)

spi.defun('pli/conceive', module=None, environment=None)
spi.defun('pli/s-conceive', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `conceive' instead.""")

def conceive(sentence, module=None, environment=None):
    """Convenience wrapper that supports objects or strings for both `sentence' and `module'.
    See also help(pli.ppli.conceive)."""
    if isinstance(sentence, str):
        module = coerceToExistingModuleName(module)
        return ppli.sConceive(sentence, module, environment)
    else:
        module = coerceToModule(module)
        sentence = coerceToLogicTree(sentence, module)
        return ppli.conceive(sentence, module, environment)


### Rules:

spi.defun('pli/get-rules', module=None, environment=None, _pre=[_coerceToModuleStmt, _coerceToRelationStmt],
          _doc="""\nPython: additionally supports strings for `relation' and `module'.""")
spi.defun('pli/s-get-rules', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `getRules' instead.""")

spi.defun('logic/process-definitions')
processDefinitions = plogic.processDefinitions

spi.defun('pli/s-print-rules', stream=None, moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `printRules' instead.""")

def printRules(obj, stream=None, module=None, environment=None):
    # Supports object and string arguments.
    processDefinitions()
    if isinstance(obj, spi.stella.pdef.Object):
        obj = objectToString(obj)
    module = coerceToExistingModuleName(module)
    ppli.sPrintRules(obj, stream, module, environment)

spi.defun('pli/run-forward-rules', module=None, localP=None, forceP=None, local=True, force=False,
          _pre=[_coerceToModuleStmt, 'localP = local', 'forceP = force'],
          _doc="""\nPython: additionally supports strings for `module'.  Renamed args to `local' and `force'.""")


### Frame queries:

spi.defun('pli/get-arity')
spi.defun('pli/s-get-arity', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `getArity' instead.""")

def getArity(relation, module=None, environment=None):
    """Convenience wrapper that supports objects or strings for both `relation' and `module'.
    See also help(pli.ppli.getArity)."""
    if isinstance(relation, str):
        module = coerceToExistingModuleName(module)
        return ppli.sGetArity(relation, module, environment)
    else:
        return ppli.getArity(relation)

spi.defun('pli/get-domain')
spi.defun('pli/s-get-domain', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `getDomain' instead.""")

def getDomain(relation, module=None, environment=None):
    """Convenience wrapper that supports objects or strings for both `relation' and `module'.
    See also help(pli.ppli.getDomain)."""
    if isinstance(relation, str):
        module = coerceToExistingModuleName(module)
        return ppli.sGetDomain(relation, module, environment)
    else:
        return ppli.getDomain(relation)

spi.defun('pli/get-range')
spi.defun('pli/s-get-range', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `getRange' instead.""")

def getRange(relation, module=None, environment=None):
    """Convenience wrapper that supports objects or strings for both `relation' and `module'.
    See also help(pli.ppli.getRange)."""
    if isinstance(relation, str):
        module = coerceToExistingModuleName(module)
        return ppli.sGetRange(relation, module, environment)
    else:
        return ppli.getRange(relation)

spi.defun('pli/get-nth-domain')
spi.defun('pli/s-get-nth-domain', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `getDomain' instead.""")

def getNthDomain(relation, n, module=None, environment=None):
    """Convenience wrapper that supports objects or strings for both `relation' and `module'.
    See also help(pli.ppli.getNthDomain)."""
    if isinstance(relation, str):
        module = coerceToExistingModuleName(module)
        return ppli.sGetNthDomain(relation, n, module, environment)
    else:
        return ppli.getNthDomain(relation, n)


### File operations:

spi.defun('pli/load', environment=None)
spi.defun('pli/load-in-module', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module'.""")
spi.defun('pli/load-stream', environment=None, _pre='stream = stellapi.pli.pdef.coerceToInputStream(stream)')
spi.defun('pli/load-stream-in-module', module=None, environment=None,
          _pre=[_coerceToModuleStmt, 'stream = stellapi.pli.pdef.coerceToInputStream(stream)'],
          _doc="""\nPython: additionally supports strings for `module'.""")
spi.defun('pli/load-native-stream', environment=None, _pre='stream = stellapi.pli.pdef.coerceToNativeInputStream(stream)')
spi.defun('pli/load-native-stream-in-module', module=None, environment=None,
          _pre=[_coerceToModuleStmt, 'stream = stellapi.pli.pdef.coerceToNativeInputStream(stream)'],
          _doc="""\nPython: additionally supports strings for `module'.""")

# the required file argument here doesn't allow us to make module optional:
spi.defun('pli/save-module', ifexists='replace', environment=None,
          _pre='module = stellapi.pli.pdef.coerceToModule(module)',
          _doc="""\nPython: additionally supports strings for `module'.""")
spi.defun('pli/s-save-module', ifexists='replace', environment=None,
          _doc="""\nPython: obsolete, use `saveModule' instead.""")


### Extracting column values from propositions and iterators:

spi.defun('pli/get-predicate')
spi.defun('pli/get-column-count')
spi.defun('pli/get-nth-value', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module'.""")
spi.defun('pli/get-nth-string', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module'.""")
spi.defun('pli/get-nth-integer', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module'.""")
spi.defun('pli/get-nth-float', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module'.""")
spi.defun('pli/get-nth-logic-object', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module'.""")

spi.defun('pli/get-enumerated-collection-members', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module'.""")


### Evaluation:

spi.defun('pli/evaluate', module=None, environment=None)
spi.defun('pli/s-evaluate', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `evaluate' instead.""")

def evaluate(command, module=None, environment=None, void=False):
    """Convenience wrapper that supports objects or strings for both `command' and `module'.
    Moreover, if `void' is True, do not return a value.  See also help(pli.ppli.evaluate).
    """
    if isinstance(command, str):
        module = coerceToExistingModuleName(module)
        value = ppli.sEvaluate(command, module, environment)
        if not void:
            return value
    else:
        module = coerceToModule(module)
        value = ppli.evaluate(command, module, environment)
        if not void:
            return value

# this shadows the Python builtin `eval', but that should be ok, since we usually reference this as `pli.eval':
eval = evaluate

def evalVoid(command, module=None, environment=None):
    """Evaluate `command' without returning its value."""
    evaluate(command, module, environment, void=True)

def execute(command, module=None, environment=None):
    """Execute one or more `command's by wrapping them with an implicit `progn'."""
    evaluate('(STELLA/PROGN ' + command + ')', module, environment, void=True)

spi.defun('pli/powerloom', module=None, environment=None, _pre=_coerceToModuleStmt,
          _doc="""\nPython: additionally supports strings for `module'.""")


### Queries and support functions

spi.defun('pli/is-logic-object')
spi.defun('pli/is-skolem')
spi.defun('pli/is-variable')
spi.defun('pli/is-integer')
spi.defun('pli/is-float')
spi.defun('pli/is-number')
spi.defun('pli/is-string')
spi.defun('pli/is-enumerated-collection')
spi.defun('pli/is-enumerated-set')
spi.defun('pli/is-enumerated-list')

spi.defun('pli/is-true')
spi.defun('pli/is-false')
spi.defun('pli/is-unknown')
spi.defun('pli/is-known')
spi.defun('pli/is-inconsistent')
spi.defun('pli/is-strict')
spi.defun('pli/is-default')


_queryOptionKeys = [
    "timeout", "TIMEOUT", "moveout", "MOVEOUT", "maximumDepth", "MAXIMUM-DEPTH", 
    "inferenceLevel", "INFERENCE-LEVEL", "threeValued", "THREE-VALUED?", "fourValued", "FOUR-VALUED?", 
    "iterativeDeepening", "ITERATIVE-DEEPENING?", "dontOptimize", "DONT-OPTIMIZE?", "allProofs", "ALL-PROOFS?",
    "howMany", "HOW-MANY", "all", "ALL", "sortBy", "SORT-BY", "score", "SCORE", "values", "VALUES", 
    "valuesDescending", "VALUES-DESCENDING", "valuesAscending", "VALUES-ASCENDING",
    "atomicSingletons", "ATOMIC-SINGLETONS?", "singletons", "SINGLETONS?"
]
for i in range(0, len(_queryOptionKeys), 2):
    defConstant(_queryOptionKeys[i], ppli.createKeyword(_queryOptionKeys[i+1]))

spi.defun('pli/ask', module=None, environment=None)
spi.defun('pli/s-ask', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `ask' instead.""")

spi.defun('pli/retrieve', module=None, environment=None)
spi.defun('pli/s-retrieve', moduleName=None, environment=None,
          _doc="""\nPython: obsolete, use `retrieve' instead.""")

# We support cached queries here and provide uniform interfaces for both regular and
# cached versions of `ask' and `retrieve'.  All that's required for caching is to
# supply an additional cache ID to store the parsed and initialized query.

spi.defun('logic/deobjectify-tree')
spi.defun('logic/parse-query-and-options')
spi.defslot('stella/property-list.the-plist')
spi.defun('logic/find-cached-query')
spi.defun('logic/make-cached-query')
spi.defun('logic/free-cached-query')
spi.defun('logic/consify-cached-query-solutions')
spi.defslot('logic/query-iterator.initial-bindings')
spi.defmethod('logic/query-iterator.consify')
spi.defmethod('logic/query-iterator.consify-current-solutions')
spi.defun('logic/call-retrieve')
spi.defun('logic/call-ask')

def makeCachedQueryId(cacheId):
    if isinstance(cacheId, pstella.Symbol):
        # already a STELLA symbol, assume it's what we want:
        return cacheId
    else:
        # add prefix to ensure that we are not getting some symbol from the current module:
        return pstella.internTransientSymbol('ploompi-cached-query-id: ' + str(cacheId))

def getCachedQuery(query=None, inVars=[], outVars=None, options=None, cacheId=None, module=None, environment=None):
    """To specify a query, we either need a `query' proposition + `outvars' and optional `options', a `cacheId'
    that points to a matching previously cached query iterator, or an already built query iterator.  If `cacheId'
    is None or does not point to a previously cached query, `query' has to be sufficient to create one.
    This does not do any query or variable normalization anymore, use the normalization functions below for that.
    """
    queryIter = None
    if isinstance(query, plogic.QueryIterator):
        queryIter = query
    elif cacheId is not None:
        cacheId = makeCachedQueryId(cacheId)
        queryIter = plogic.findCachedQuery(cacheId)
    if queryIter is not None:
        arity = queryIter.initialBindings.length()
        nUnbound = arity - len(inVars)
        bindings = createConsList(nUnbound)
        for var, value in inVars:
            bindings = createCons(value, bindings)
        queryIter = plogic.makeCachedQuery(None, queryIter, bindings, None, None)
    else:
        # remove any to-be-bound variables from `outVars':
        for var, value in inVars:
            outVars = outVars.remove(var)
        nUnbound = len(outVars)
        bindings = createConsList(nUnbound)
        ioVars = outVars
        for var, value in inVars:
            ioVars = createCons(var, ioVars)
            bindings = createCons(value, bindings)
        # keep this as narrow as possible, since the module rebinding does cost some time:
        with coerceToExistingModule(module) as mod:
            queryIter = plogic.makeCachedQuery(ioVars, query, bindings, options, cacheId)
    return queryIter

def normalizeInputVariableBindings(inVars={}, module=None):
    # ensure canonical variable sort order for prepended initial bindings:
    inVars = list(map(lambda b: (dwimTreeToLogicTree(b[0], module), dwimTreeToLogicTree(b[1], module)), inVars.items()))
    inVars.sort(key=lambda x: x[0].symbolName)
    return inVars

def isBareGoalProposition(query):
    """Try to intuit whether `query' is a bare goal proposition tree, or whether any additional
    query parameters such as number of answers, output variables or query options are provided.
    This cannot always decide for all legal syntaxes.  Therefore, if there is only a single output
    variable, make sure it is provided as a list.
    """
    if isinstance(query, pstella.Cons):
        length = len(query)
        if length > 1:
            head = query.value
            if isinstance(head, pstella.Wrapper) or isinstance(head, pstella.Cons):
                # handles (5 ...), ("all" ...) and ((?x) ...):
                return False
            if isinstance(head, pstella.Symbol) and head.symbolName.lower() == 'all':
                return False
            if isinstance(query.nth(length - 2), pstella.Keyword):
                return False
        return True
    else:
        return False

def normalizeQueryTree(query, inVars=None, outVars=None, module=None, environment=None, **options):
    """DOCUMENT ME"""
    with coerceToExistingModule(module) as mod:
        if isinstance(query, basestring):
            query = stringToStellaExpression('(' + query + ')', module=mod, environment=environment)
        else:
            # hmm, we need to deobjectify here to make `parseQueryAndOptions' work correctly:
            query = plogic.deobjectifyTree(dwimTreeToLogicTree(query, mod))
            if isBareGoalProposition(query):
                query = createCons(query, NIL)
        # FIXME: this wraps an exists around any `inVars' that aren't in `qvars':
        qvars, qbody, qoptions = plogic.parseQueryAndOptions(query)
        qvars = qvars and qvars.consify() or NIL
        qoptions = qoptions.thePlist
        # explicitly supplied outVars override anything from the query tree:
        if isinstance(outVars, basestring):
            outVars = stringToStellaExpression(outVars, module=mod, environment=environment)
        elif outVars is not None:
            outVars = dwimTreeToLogicTree(outVars, mod)
        if outVars is not None:
            outVars = outVars.consify()
            # minor complication: if we have explicitly supplied outVars, we have to make sure
            # to quantify all remaining open variables in `qvars' with an exists:
            for var in outVars:
                qvars = qvars.remove(var)
            # but do not quantify invars which need to be bound later:
            for var in inVars or []:
                qvars = qvars.remove(var[0])
            if not qvars.emptyP():
                qbody = createCons(getOperator('exists'), createCons(qvars, createCons(qbody, NIL)))
        else:
            outVars = qvars
        # explicitly supplied options override anything from the query tree:
        if len(options) > 0:
            # TO DO: maybe have a specialized `parseOptions' instead:
            options = spi.pythonToStellaTree(parseCommand('retrieve', **options)[1:])
        else:
            options = qoptions
        return qbody, outVars, options

"""
# ORIGINAL:
def ask(query, module=None, environment=None):
    if isinstance(query, str):
        module = coerceToExistingModuleName(module)
        return ppli.sAsk(query, module, environment)
    else:
        module = coerceToModule(module)
        return ppli.ask(query, module, environment)

def retrieve(query, module=None, environment=None):
    if isinstance(query, str):
        module = coerceToExistingModuleName(module)
        return ppli.sRetrieve(query, module, environment)
    else:
        module = coerceToModule(module)
        query = dwimTreeToLogicTree(query, module)
        return ppli.retrieve(query, module, environment)
"""

def ask(query=None, inVars={}, cacheId=None, module=None, environment=None, **options):
    """DOCUMENT ME"""
    queryIter = None
    inVars = normalizeInputVariableBindings(inVars=inVars, module=module)
    if cacheId is not None:
        cacheId = makeCachedQueryId(cacheId)
        queryIter = plogic.findCachedQuery(cacheId)
        if queryIter is not None:
            queryIter = getCachedQuery(queryIter, inVars=inVars, module=module, environment=environment)
    if queryIter is None:
        outVars = len(inVars) > 0 and list(map(lambda b: b[0], inVars)) or None
        qbody, outVars, options = normalizeQueryTree(query, inVars=inVars, outVars=outVars, module=module, environment=environment, **options)
        queryIter = getCachedQuery(qbody, inVars=inVars, outVars=outVars, options=options, cacheId=cacheId, module=module, environment=environment)
    # unfortunately, we need to bind the module for the benefit of `callAsk' which costs time:
    with coerceToExistingModule(module) as mod:
        truthValue = plogic.callAsk(queryIter)
    if cacheId is not None:
        plogic.freeCachedQuery(queryIter, cacheId)
    return truthValue

def retrieve(query=None, inVars={}, outVars=None, cacheId=None, module=None, environment=None, **options):
    """DOCUMENT ME"""
    queryIter = None
    inVars = normalizeInputVariableBindings(inVars=inVars, module=module)
    if cacheId is not None:
        cacheId = makeCachedQueryId(cacheId)
        queryIter = plogic.findCachedQuery(cacheId)
        if queryIter is not None:
            queryIter = getCachedQuery(queryIter, inVars=inVars, module=module, environment=environment)
    if queryIter is None:
        qbody, outVars, options = normalizeQueryTree(query, inVars=inVars, outVars=outVars, module=module, environment=environment, **options)
        queryIter = getCachedQuery(qbody, inVars=inVars, outVars=outVars, options=options, cacheId=cacheId, module=module, environment=environment)
    # unfortunately, we need to bind the module for the benefit of `callRetrieve' which costs time:
    with coerceToExistingModule(module) as mod:
        queryIter = plogic.callRetrieve(queryIter)
    solutions, tvs, justs = plogic.consifyCachedQuerySolutions(queryIter, False, False)
    plIter = consToPlIterator(solutions)
    if cacheId is not None:
        plogic.freeCachedQuery(queryIter, cacheId)
    return plIter

"""
# The bad news is that even in the most beneficial cached case, we are losing a lot of time due
# to the overhead of the Python interface.  A single call to `testRelationCached' creates about
# 30 calls to `pythonToStellaObjectOfType' (especially from functions with multiple args).  Also,
# `normalizeInputVariableBindings' and `getCachedQuery' take up about 50% of the total time.  
# Reading slot values, GC protecting and releasing all have similar times as the ask itself.  Things
# are a little bit better in PyPy where we basically just lose a factor of 2.3, but still the general
# news is that the more calls we make on the Python side, the worse off we are.  That is anything
# we can handle completely on the STELLA side is a big win.  There might be some shifts with more
# complex queries where the cost-saving from caching becomes actually more significant, but then
# the gained benefit will probably be shadowed by inference time.  Optimizing SPI further for more
# targeted type conversions, limited gc/exception handling, avoiding dotted notation, etc. will
# help but the headroom is probably fairly limited.  At least for longer running queries, the added
# inefficiency of the interface won't matter relative to query time.

def testRelation(rel):
    return pli.ppli.sAsk('(relation ' + rel + ') :inference-level :subsumption')
def testRelationCached(rel):
    return pli.ask(('relation', '?x'), inVars={'?x': rel}, cacheId='main.testRelation', inferenceLevel='subsumption')
def testRelationN(n):
    for i in range(n):
        x = testRelation(str(i))
def testRelationCachedN(n):
    for i in range(n):
        x = testRelationCached(str(i))
import cProfile
cProfile.run('testRelationCachedN(10000)', sort='cumulative')
"""


### Inference Engine API:

CONTINUING_SUCCESS = ppli.getKeyword('CONTINUING-SUCCESS')
FINAL_SUCCESS      = ppli.getKeyword('FINAL-SUCCESS')
FAILURE            = ppli.getKeyword('FAILURE')
TERMINAL_FAILURE   = ppli.getKeyword('TERMINAL-FAILURE')

spi.defun('pli/get-frame-proposition')
spi.defun('pli/get-frame-arity')
spi.defun('pli/get-frame-iterator')
spi.defun('pli/set-frame-iterator')
spi.defun('pli/get-nth-frame-argument')
spi.defun('pli/get-nth-frame-binding')
spi.defun('pli/set-nth-frame-binding')
spi.defun('pli/is-frame-binding-pattern')
spi.defun('pli/get-frame-binding-pattern')
spi.defun('pli/get-frame-binding-state')
spi.defun('pli/set-frame-binding-state')


### Properties:

spi.defun('pli/get-property-object', defaultvalue=None)
spi.defun('pli/get-property-string', defaultvalue=None)
spi.defun('pli/get-property', defaultvalue=None)
spi.defun('pli/get-property-integer', defaultvalue=0)
spi.defun('pli/get-property-float', defaultvalue=0.0)
spi.defun('pli/get-property-boolean', defaultvalue=False)
spi.defun('pli/set-property-object')
spi.defun('pli/set-property-string')
spi.defun('pli/set-property')
spi.defun('pli/set-property-integer')
spi.defun('pli/set-property-float')
spi.defun('pli/set-property-boolean')
spi.defun('pli/is-defined-property')
spi.defun('pli/print-properties')


### PLI symbol export:

# inherit functions and classes in spi.pli.pdef up to the API module, however, that
# won't work for non-constant globals which are implemented as properties...hmm:

for key, defn in ppli.__dict__.items():
    if not hasattr(apiModule, key):
        setattr(apiModule, key, defn)


### Miscellaneous

setPropertyBoolean("powerloom.confirmInteractiveExit", False)

# this will override a default value based on the root directory of ST:
pstella.defineLogicalHostProperty(
    "PL", getKeyword('ROOT-DIRECTORY'),
    createStringWrapper(os.path.realpath(os.path.join(os.path.dirname(apiModule.__file__), os.pardir))))


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
            except spi.ApiException:
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

# TO DO:
# - use new spi.pythonify and spi.stellafy when they become available
# - support varargs computation function argument similar to what we have for specialists
#   (simply add an annotation on the function that will be created) and expect a Cons
#   argument in the Python implementation
# - implement these signatures with an optional flags and module arg, where the format
#   string has to accept the number of args following it (not counting the output):
#     (python-test "-d" "opera.temporality" "timeGreaterThan(%s, %s)" ?time1 ?time2)
#     (python-eval "-d" "opera.temporality" "%s.upcase()" ?str ?upcased)
# - also confer with chameleon_pli pyEval and see if this can replace it

def _pythonEval(expression, debug=False, importMissingModules=True):
    # slightly messy since we overloaded `eval' with pli.eval:
    eval = __builtins__.get('eval')
    expression = str(expression)
    try:
        value = eval(expression, globals())
        # TO DO: add a value conversion function for this kind of wrapping,
        #        none of our currentn ones supports this case
        if isinstance(value, unicode) and PY2:
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
