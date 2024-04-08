//  -*- Mode: C++ -*-

// symbols.cc

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

int nextFreeOffset(ExtensibleSymbolArray* self) {
  { int topoffset = self->topSymbolOffset;
    int freeoffset = topoffset + 1;

    { int i = NULL_INTEGER;
      int iter000 = self->potentialFreeSymbolOffset;
      int upperBound000 = topoffset;
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;

      for  (; unboundedP000 ||
                (iter000 <= upperBound000); 
            iter000 = iter000 + 1) {
        i = iter000;
        if (!((boolean)((self->theArray)[i]))) {
          freeoffset = i;
          break;
        }
      }
    }
    self->potentialFreeSymbolOffset = freeoffset + 1;
    return (freeoffset);
  }
}

void freeSymbolOffset(ExtensibleSymbolArray* self, int offset) {
  (self->theArray)[offset] = NULL;
  if (offset < self->potentialFreeSymbolOffset) {
    self->potentialFreeSymbolOffset = offset;
  }
}

void addToSymbolArrayAt(ExtensibleSymbolArray* array, int offset, GeneralizedSymbol* symbol) {
  array->insertAt(offset, symbol);
  symbol->symbolId = offset;
}

int addToSymbolArray(ExtensibleSymbolArray* array, GeneralizedSymbol* symbol) {
  { int offset = nextFreeOffset(array);

    addToSymbolArrayAt(array, offset, symbol);
    return (offset);
  }
}

boolean legalSymbolArrayOffsetP(ExtensibleSymbolArray* array, int offset) {
  return (offset <= array->topSymbolOffset);
}

ExtensibleSymbolArray* oSYMBOL_ARRAYo = NULL;

ExtensibleSymbolArray* oSURROGATE_ARRAYo = NULL;

ExtensibleSymbolArray* oKEYWORD_ARRAYo = NULL;

StringToIntegerHashTable* oKEYWORD_OFFSET_TABLEo = NULL;

ExtensibleSymbolArray* oFIXED_SYMBOL_ARRAYo = NULL;

ExtensibleSymbolArray* oFIXED_SURROGATE_ARRAYo = NULL;

ExtensibleSymbolArray* oFIXED_KEYWORD_ARRAYo = NULL;

StringHashTable* oTRANSIENT_SYMBOL_LOOKUP_TABLEo = NULL;

StringHashTable* oCOMMON_LISP_SYMBOL_LOOKUP_TABLEo = NULL;

int SYMBOL_SYM = 0;

int SURROGATE_SYM = 1;

int KEYWORD_SYM = 2;

// Pointer to the top-most module ROOT-MODULE.
Module* oROOT_MODULEo = NULL;

// Pointer to the module STELLA containing definitions of 
// STELLA classes and methods.
Module* oSTELLA_MODULEo = NULL;

// Pointer to the module COMMON-LISP containing Common
// Lisp symbols (and maybe other things).
Module* oCOMMON_LISP_MODULEo = NULL;

// Pointer to the module ALTERNATE-STELLA containing
// definitions of STELLA classes and methods generated during the
// translation of STELLA files.
Module* oALTERNATE_STELLA_MODULEo = NULL;

// Points to the current context (either a module or a
// world).  Set by calls to `change-world' and `change-module'.
DEFINE_STELLA_SPECIAL(oCONTEXTo, Context* , NULL);

// Points to the current module.  Set by calls to
// `change-context' and `change-module'.
DEFINE_STELLA_SPECIAL(oMODULEo, Module* , NULL);

// Character used to prefix the name of a surrogate.
char SURROGATE_PREFIX_CHARACTER = '@';

// Character used to concatenate a module name
// to a symbol or surrogate name to form a qualified name.
char MODULE_SEPARATOR_CHARACTER = '/';

// String containing character used to concatenate a module name
// to a symbol or surrogate name to form a qualified name.
const char* MODULE_SEPARATOR_STRING = "/";

Symbol* getSym(int offset) {
  return (((Symbol*)((oFIXED_SYMBOL_ARRAYo->theArray)[offset])));
}

Surrogate* getSgt(int offset) {
  return (((Surrogate*)((oFIXED_SURROGATE_ARRAYo->theArray)[offset])));
}

Keyword* getKwd(int offset) {
  return (((Keyword*)((oFIXED_KEYWORD_ARRAYo->theArray)[offset])));
}

GeneralizedSymbol* getGeneralizedSymbolFromOffset(ExtensibleSymbolArray* symbolarray, int offset) {
  return (((GeneralizedSymbol*)((symbolarray->theArray)[offset])));
}

Symbol* getSymFromOffset(int offset) {
  return (((Symbol*)(getGeneralizedSymbolFromOffset(oSYMBOL_ARRAYo, offset))));
}

Surrogate* getSgtFromOffset(int offset) {
  return (((Surrogate*)(getGeneralizedSymbolFromOffset(oSURROGATE_ARRAYo, offset))));
}

Keyword* getKwdFromOffset(int offset) {
  return (((Keyword*)(getGeneralizedSymbolFromOffset(oKEYWORD_ARRAYo, offset))));
}

StringToIntegerHashTable* selectSymbolOffsetTable(Module* module, int kindofsym) {
  switch (kindofsym) {
    case 0: 
      return (module->symbolOffsetTable);
    case 1: 
      return (module->surrogateOffsetTable);
    case 2: 
      return (oKEYWORD_OFFSET_TABLEo);
    default:
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << kindofsym << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
      break;
  }
}

ExtensibleSymbolArray* selectSymbolArray(int kindofsym) {
  switch (kindofsym) {
    case 0: 
      return (oSYMBOL_ARRAYo);
    case 1: 
      return (oSURROGATE_ARRAYo);
    case 2: 
      return (oKEYWORD_ARRAYo);
    default:
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << kindofsym << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
      break;
  }
}

GeneralizedSymbol* lookupRigidSymbolLocally(const char* name, Module* module, int kindofsym) {
  { StringToIntegerHashTable* offsettable = selectSymbolOffsetTable(module, kindofsym);
    int offset = offsettable->lookup(name);

    if (offset != NULL_INTEGER) {
      switch (kindofsym) {
        case 0: 
          return (getSymFromOffset(offset));
        case 1: 
          return (getSgtFromOffset(offset));
        case 2: 
          return (getKwdFromOffset(offset));
        default:
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << kindofsym << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
          break;
      }
    }
    return (NULL);
  }
}

Cons* yieldVisibleRigidSymbolsWrtModule(const char* name, Module* module, int kindofsym) {
  { Cons* listofsymbols = NIL;
    GeneralizedSymbol* symbol = NULL;

    { Module* visiblemodule = NULL;
      Cons* iter000 = visibleModules(module);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        visiblemodule = ((Module*)(iter000->value));
        { 
          symbol = lookupRigidSymbolLocally(name, visiblemodule, kindofsym);
          if (((boolean)(symbol))) {
            listofsymbols = cons(symbol, listofsymbols);
          }
        }
      }
    }
    return (listofsymbols->reverse());
  }
}

Iterator* visibleRigidSymbolsWrtModule(const char* name, Module* module, int kindofsym) {
  return (yieldVisibleRigidSymbolsWrtModule(name, module, kindofsym)->allocateDestructiveListIterator());
}

Cons* removeShadowedSymbols(Cons* visiblesymbols) {
  if (visiblesymbols->rest == NIL) {
    return (visiblesymbols);
  }
  { Cons* shadowingmodules = NIL;

    { GeneralizedSymbol* symbol = NULL;
      Cons* iter000 = visiblesymbols;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        symbol = ((GeneralizedSymbol*)(iter000->value));
        if (shadowedSymbolP(symbol)) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(((Module*)(symbol->homeContext)), NIL);
              if (shadowingmodules == NIL) {
                shadowingmodules = collect000;
              }
              else {
                addConsToEndOfConsList(shadowingmodules, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(((Module*)(symbol->homeContext)), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    if (!(shadowingmodules == NIL)) {
      { Cons* unshadowedsymbols = NIL;

        { GeneralizedSymbol* symbol = NULL;
          Cons* iter001 = visiblesymbols;
          Cons* collect001 = NULL;

          for  (; !(iter001 == NIL); 
                iter001 = iter001->rest) {
            symbol = ((GeneralizedSymbol*)(iter001->value));
            { boolean testValue000 = false;

              { boolean foundP000 = false;

                { Module* module = NULL;
                  Cons* iter002 = shadowingmodules;

                  for (; !(iter002 == NIL); iter002 = iter002->rest) {
                    module = ((Module*)(iter002->value));
                    if ((!(module == ((Module*)(symbol->homeContext)))) &&
                        visibleFromP(((Module*)(symbol->homeContext)), module)) {
                      foundP000 = true;
                      break;
                    }
                  }
                }
                testValue000 = foundP000;
              }
              testValue000 = !testValue000;
              if (testValue000) {
                if (!((boolean)(collect001))) {
                  {
                    collect001 = cons(symbol, NIL);
                    if (unshadowedsymbols == NIL) {
                      unshadowedsymbols = collect001;
                    }
                    else {
                      addConsToEndOfConsList(unshadowedsymbols, collect001);
                    }
                  }
                }
                else {
                  {
                    collect001->rest = cons(symbol, NIL);
                    collect001 = collect001->rest;
                  }
                }
              }
            }
          }
        }
        visiblesymbols = unshadowedsymbols;
      }
    }
    return (visiblesymbols);
  }
}

int lookupRigidSymbolOffsetWrtModule(const char* name, Module* module, int kindofsym) {
  { StringToIntegerHashTable* offsettable = selectSymbolOffsetTable(module, kindofsym);
    int offset = offsettable->lookup(name);

    if (offset != NULL_INTEGER) {
      return (offset);
    }
    { Module* super = NULL;
      Cons* iter000 = visibleModules(module)->rest;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        super = ((Module*)(iter000->value));
        offset = selectSymbolOffsetTable(super, kindofsym)->lookup(name);
        if (offset != NULL_INTEGER) {
          return (offset);
        }
      }
    }
    return (NULL_INTEGER);
  }
}

GeneralizedSymbol* lookupRigidSymbolWrtModule(const char* name, Module* module, int kindofsym) {
  { int offset = lookupRigidSymbolOffsetWrtModule(name, module, kindofsym);

    if (offset != NULL_INTEGER) {
      switch (kindofsym) {
        case 0: 
          return (getSymFromOffset(offset));
        case 1: 
          return (getSgtFromOffset(offset));
        case 2: 
          return (getKwdFromOffset(offset));
        default:
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << kindofsym << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
          break;
      }
    }
    else {
      return (NULL);
    }
  }
}

GeneralizedSymbol* lookupRigidSymbol(const char* name, int kindofsym) {
  // Return the permanent symbol with name 'name' and type
  // `kindOfSym' visible from the current module (case-sensitive).
  return (lookupRigidSymbolWrtModule(name, oMODULEo, kindofsym));
}

Symbol* lookupSymbol(const char* name) {
  // Return the first symbol with `name' visible from the current module.
  return (((Symbol*)(lookupRigidSymbolWrtModule(name, oMODULEo, SYMBOL_SYM))));
}

Symbol* lookupSymbolInModule(const char* name, Module* module, boolean localP) {
  // Return the first symbol with `name' visible from `module'.
  // If `local?' only consider symbols directly interned in `module'.
  // If `module' is `null', use `*MODULE*' instead.
  if (!((boolean)(module))) {
    module = oMODULEo;
  }
  if (localP) {
    return (((Symbol*)(lookupRigidSymbolLocally(name, module, SYMBOL_SYM))));
  }
  else {
    return (((Symbol*)(lookupRigidSymbolWrtModule(name, module, SYMBOL_SYM))));
  }
}

Cons* lookupVisibleSymbolsInModule(const char* name, Module* module, boolean enforceshadowingP) {
  // Return the list of symbols with `name' visible from `module'.
  // More specific symbols (relative to the module precedence order defined by
  // `visible-modules') come earlier in the list.  If `module' is `null', start
  // from `*MODULE*' instead.  If `enforceShadowing?' is true, do not return any
  // symbols that are shadowed due to some :SHADOW declaration.
  { Cons* visiblesymbols = yieldVisibleRigidSymbolsWrtModule(name, module, SYMBOL_SYM);

    if (enforceshadowingP &&
        (!(visiblesymbols->rest == NIL))) {
      return (((Cons*)(removeShadowedSymbols(visiblesymbols))));
    }
    else {
      return (((Cons*)(visiblesymbols)));
    }
  }
}

Surrogate* lookupSurrogate(const char* name) {
  // Return the first surrogate with `name' visible from the current module.
  return (((Surrogate*)(lookupRigidSymbolWrtModule(name, oMODULEo, SURROGATE_SYM))));
}

Surrogate* lookupSurrogateInModule(const char* name, Module* module, boolean localP) {
  // Return the first surrogate with `name' visible from `module'.
  // If `local?' only consider surrogates directly interned in `module'.
  // If `module' is `null', use `*MODULE*' instead.
  if (!((boolean)(module))) {
    module = oMODULEo;
  }
  if (localP) {
    return (((Surrogate*)(lookupRigidSymbolLocally(name, module, SURROGATE_SYM))));
  }
  else {
    return (((Surrogate*)(lookupRigidSymbolWrtModule(name, module, SURROGATE_SYM))));
  }
}

Cons* lookupVisibleSurrogatesInModule(const char* name, Module* module, boolean enforceshadowingP) {
  // Return the list of surrogates with `name' visible from `module'.
  // More specific surrogates (relative to the module precedence order defined by
  // `visible-modules') come earlier in the list.  If `module' is `null', start
  // from `*MODULE*' instead.  If `enforceShadowing?' is true, do not return any
  // surrogates that are shadowed due to some :SHADOW declaration.
  { Cons* visiblesurrogates = yieldVisibleRigidSymbolsWrtModule(name, module, SURROGATE_SYM);

    if (enforceshadowingP &&
        (!(visiblesurrogates->rest == NIL))) {
      return (((Cons*)(removeShadowedSymbols(visiblesurrogates))));
    }
    else {
      return (((Cons*)(visiblesurrogates)));
    }
  }
}

Keyword* lookupKeyword(const char* name) {
  // Return the keyword with `name' if it exists.
  return (((Keyword*)(lookupRigidSymbol(name, KEYWORD_SYM))));
}

GeneralizedSymbol* helpInternGeneralizedSymbol(const char* name, int kindofsym, ExtensibleSymbolArray* array, int offset, Module* module) {
  { GeneralizedSymbol* symbol = NULL;
    StringToIntegerHashTable* table = selectSymbolOffsetTable(module, kindofsym);

    switch (kindofsym) {
      case 0: 
        symbol = newSymbol(name);
        table->insertAt(name, offset);
        symbol->homeContext = module;
        break;
      case 1: 
        symbol = newSurrogate(name);
        table->insertAt(name, offset);
        symbol->homeContext = module;
        break;
      case 2: 
        symbol = newKeyword(name);
        table->insertAt(name, offset);
        symbol->homeContext = NULL;
        break;
      default:
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << kindofsym << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
        break;
    }
    addToSymbolArrayAt(array, offset, symbol);
    return (symbol);
  }
}

GeneralizedSymbol* internRigidSymbolWrtModule(const char* name, Module* module, int kindofsym) {
  // Return a newly-created or existing rigid symbol with
  // name `name'.
  if (!((boolean)(module))) {
    module = oMODULEo;
  }
  { int offset = lookupRigidSymbolOffsetWrtModule(name, module, kindofsym);

    if (offset != NULL_INTEGER) {
      switch (kindofsym) {
        case 0: 
          return (getSymFromOffset(offset));
        case 1: 
          return (getSgtFromOffset(offset));
        case 2: 
          return (getKwdFromOffset(offset));
        default:
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << kindofsym << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
          break;
      }
    }
    { ExtensibleSymbolArray* array = selectSymbolArray(kindofsym);

      offset = nextFreeOffset(array);
      return (helpInternGeneralizedSymbol(name, kindofsym, array, offset, module));
    }
  }
}

GeneralizedSymbol* internRigidSymbolLocally(const char* name, Module* module, int kindofsym) {
  // Return a newly-created or existing rigid symbol
  // interned into the module `module' with name `name'.
  if (!((boolean)(module))) {
    module = oMODULEo;
  }
  { GeneralizedSymbol* symbol = lookupRigidSymbolLocally(name, module, kindofsym);

    if (((boolean)(symbol))) {
      return (symbol);
    }
    { ExtensibleSymbolArray* array = selectSymbolArray(kindofsym);

      return (helpInternGeneralizedSymbol(name, kindofsym, array, nextFreeOffset(array), module));
    }
  }
}

GeneralizedSymbol* internRigidSymbolCaseSensitively(const char* name, int kindofsym, boolean tryupcasingP) {
  { GeneralizedSymbol* symbol = NULL;

    symbol = lookupRigidSymbol(name, kindofsym);
    if (((boolean)(symbol))) {
      return (symbol);
    }
    if (oTRANSIENTOBJECTSpo &&
        (kindofsym == SYMBOL_SYM)) {
      symbol = lookupTransientSymbol(name);
      if (((boolean)(symbol))) {
        return (symbol);
      }
    }
    if (tryupcasingP) {
      symbol = lookupRigidSymbol(stringUpcase(name), kindofsym);
      if (((boolean)(symbol))) {
        return (symbol);
      }
    }
    switch (kindofsym) {
      case 0: 
        if (oTRANSIENTOBJECTSpo) {
          return (internTransientSymbol(name));
        }
        else {
          return (internPermanentSymbol(name));
        }
        break;
      case 1: 
        return (internRigidSymbolWrtModule(name, oMODULEo, SURROGATE_SYM));
      default:
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << kindofsym << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
        break;
    }
  }
}

Symbol* internPermanentSymbol(const char* name) {
  // Return a newly-created or existing permanent symbol with
  // name `name'.
  return (((Symbol*)(internRigidSymbolWrtModule(name, oMODULEo, SYMBOL_SYM))));
}

Symbol* internSymbol(const char* name) {
  // Return a newly-created or existing symbol with name `name'.
  if (oMODULEo->caseSensitiveP) {
    return (((Symbol*)(internRigidSymbolCaseSensitively(name, SYMBOL_SYM, false))));
  }
  else {
    if (oTRANSIENTOBJECTSpo) {
      return (internTransientSymbol(stringUpcase(name)));
    }
    else {
      return (internPermanentSymbol(stringUpcase(name)));
    }
  }
}

Symbol* internSymbolInModule(const char* name, Module* module, boolean localP) {
  // Look for a symbol named `name' in `module' (if `local?' do
  // not consider inherited modules).  If none exists, intern it locally in
  // `module'.  Return the existing or newly-created symbol.
  if (!((boolean)(module))) {
    module = oMODULEo;
  }
  if (localP) {
    return (((Symbol*)(internRigidSymbolLocally(name, module, SYMBOL_SYM))));
  }
  else {
    return (((Symbol*)(internRigidSymbolWrtModule(name, module, SYMBOL_SYM))));
  }
}

Symbol* internDerivedSymbol(GeneralizedSymbol* basesymbol, const char* newname) {
  // Return a newly-created or existing symbol with name
  // `newName' which is interned in the same module as `baseSymbol'.
  { Module* currentmodule = oMODULEo;

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, ((Module*)(basesymbol->homeContext)));
      if (((boolean)(oMODULEo))) {
        return (((Symbol*)(internRigidSymbolLocally(newname, oMODULEo, SYMBOL_SYM))));
      }
      oMODULEo = currentmodule;
      return (((Symbol*)(internRigidSymbolCaseSensitively(newname, SYMBOL_SYM, false))));
    }
  }
}

Surrogate* internSurrogate(const char* name) {
  // Return a newly-created or existing surrogate with name `name'.
  if (oMODULEo->caseSensitiveP) {
    return (((Surrogate*)(internRigidSymbolCaseSensitively(name, SURROGATE_SYM, false))));
  }
  else {
    return (((Surrogate*)(internRigidSymbolWrtModule(stringUpcase(name), oMODULEo, SURROGATE_SYM))));
  }
}

Surrogate* internSurrogateInModule(const char* name, Module* module, boolean localP) {
  // Look for a symbol named `name' in `module' (if `local?' do
  // not consider inherited modules).  If none exists, intern it locally in
  // `module'.  Return the existing or newly-created symbol.
  if (!((boolean)(module))) {
    module = oMODULEo;
  }
  if (localP) {
    return (((Surrogate*)(internRigidSymbolLocally(name, module, SURROGATE_SYM))));
  }
  else {
    return (((Surrogate*)(internRigidSymbolWrtModule(name, module, SURROGATE_SYM))));
  }
}

Surrogate* internDerivedSurrogate(GeneralizedSymbol* basesymbol, const char* newname) {
  // Return a newly-created or existing surrogate with name
  // `newName' which is interned in the same module as `baseSymbol'.
  { Module* currentmodule = oMODULEo;

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, ((Module*)(basesymbol->homeContext)));
      if (((boolean)(oMODULEo))) {
        return (((Surrogate*)(internRigidSymbolLocally((oMODULEo->caseSensitiveP ? newname : stringUpcase(newname)), oMODULEo, SURROGATE_SYM))));
      }
      oMODULEo = currentmodule;
      return (internSurrogate(newname));
    }
  }
}

Keyword* internKeyword(const char* name) {
  // Return a newly-created or existing keyword with name
  // `name'.  Storage note: a COPY of `name' is stored in the keyword
  return (((Keyword*)(internRigidSymbolWrtModule(stringUpcase(name), oMODULEo, KEYWORD_SYM))));
}

Symbol* importSymbol(Symbol* symbol, Module* module) {
  // Import `symbol' into `module' and return the imported `symbol'.
  // Signal an error if a different symbol with the same name already exists
  // locally in `module'.  Any symbol with the same name visible in `module' by
  // inheritance will be shadowed by the newly imported `symbol'.
  { const char* name = symbol->symbolName;
    Symbol* modulesymbol = lookupSymbolInModule(name, module, true);

    if (!((boolean)(((Module*)(symbol->homeContext))))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't import the TRANSIENT symbol " << "`" << name << "'" << " into " << "`" << module << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    if (!(modulesymbol == symbol)) {
      if (((boolean)(modulesymbol))) {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "Can't import, a symbol with name " << "`" << name << "'" << " already exists in " << "`" << module << "'";
          throw *newStellaException(stream001->theStringReader());
        }
      }
      if (((boolean)(symbol))) {
        selectSymbolOffsetTable(module, SYMBOL_SYM)->insertAt(name, symbol->symbolId);
      }
    }
    return (symbol);
  }
}

Surrogate* importSurrogate(Surrogate* surrogate, Module* module) {
  // Import `surrogate' into `module' and return the imported `surrogate'.
  // Signal an error if a different surrogate with the same name already exists
  // locally in `module'.  Any surrogate with the same name visible in `module' by
  // inheritance will be shadowed by the newly imported `surrogate'.
  { const char* name = surrogate->symbolName;
    Surrogate* modulesurrogate = lookupSurrogateInModule(name, module, true);

    if (!(modulesurrogate == surrogate)) {
      if (((boolean)(modulesurrogate))) {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Can't import, a surrogate with name " << "`" << name << "'" << " already exists in " << "`" << module << "'";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      if (((boolean)(surrogate))) {
        selectSymbolOffsetTable(module, SURROGATE_SYM)->insertAt(name, surrogate->symbolId);
      }
    }
    return (surrogate);
  }
}

Symbol* safeImportSymbol(Symbol* symbol, Module* module) {
  // Safe version of `import-symbol' (which see).  Only imports `symbol' if
  // no symbol with that name is currently interned or visible in `module'.
  // Returns `symbol' if it was imported or the conflicting symbol in `module'
  // otherwise.
  { const char* name = symbol->symbolName;
    Symbol* modulesymbol = lookupSymbolInModule(name, module, false);

    if (((boolean)(modulesymbol)) ||
        (!((boolean)(((Module*)(symbol->homeContext)))))) {
      return (modulesymbol);
    }
    else {
      return (importSymbol(symbol, module));
    }
  }
}

Surrogate* safeImportSurrogate(Surrogate* surrogate, Module* module) {
  // Safe version of `import-surrogate' (which see).  Only imports `surrogate' if
  // no surrogate with that name is currently interned or visible in `module'.
  // Returns `surrogate' if it was imported or the conflicting surrogate in `module'
  // otherwise.
  { const char* name = surrogate->symbolName;
    Surrogate* modulesurrogate = lookupSurrogateInModule(name, module, false);

    if (((boolean)(modulesurrogate))) {
      return (modulesurrogate);
    }
    else {
      return (importSurrogate(surrogate, module));
    }
  }
}

void uninternSymbol(Symbol* self) {
  // Remove `self' from its home module and the symbol table.
  { ExtensibleSymbolArray* symbolarray = selectSymbolArray(SYMBOL_SYM);
    StringToIntegerHashTable* offsettable = (((boolean)(((Module*)(self->homeContext)))) ? selectSymbolOffsetTable(((Module*)(self->homeContext)), SYMBOL_SYM) : ((StringToIntegerHashTable*)(NULL)));
    int symbolid = self->symbolId;
    Symbol* realsymbol = getSymFromOffset(symbolid);

    if (self == realsymbol) {
      freeSymbolOffset(symbolarray, symbolid);
    }
    if (((boolean)(offsettable)) &&
        (symbolid == offsettable->lookup(self->symbolName))) {
      offsettable->removeAt(self->symbolName);
    }
    self->symbolId = -1;
    self->symbolValueAndPlist = NULL;
  }
}

void uninternSurrogate(Surrogate* self) {
  // Remove `self' from its home module and the surrogate table.
  { ExtensibleSymbolArray* surrogatearray = selectSymbolArray(SURROGATE_SYM);
    StringToIntegerHashTable* offsettable = (((boolean)(((Module*)(self->homeContext)))) ? selectSymbolOffsetTable(((Module*)(self->homeContext)), SURROGATE_SYM) : ((StringToIntegerHashTable*)(NULL)));
    int surrogateid = self->symbolId;
    Surrogate* realsurrogate = getSgtFromOffset(surrogateid);

    if (self == realsurrogate) {
      freeSymbolOffset(surrogatearray, surrogateid);
    }
    if (((boolean)(offsettable)) &&
        (surrogateid == offsettable->lookup(self->symbolName))) {
      offsettable->removeAt(self->symbolName);
    }
    self->symbolId = -1;
    self->surrogateValue = NULL;
  }
}

boolean GeneralizedSymbol::deletedP() {
  { GeneralizedSymbol* self = this;

    return (self->symbolId == -1);
  }
}

GeneralizedSymbol* internBootstrapSymbolAt(const char* name, int offset, int kindofsym) {
  // Interns a symbol, or keyword with
  // `name' and symbol-id `offset'.
  // If a symbol with that ID already existed, an error is signaled.  This
  // function is used to recreate the symbol table in a way where symbol IDs
  // which got hardwired into translated code will refer to the correct objects.
  { ExtensibleSymbolArray* symbolarray = NULL;
    GeneralizedSymbol* symbol = NULL;

    switch (kindofsym) {
      case 0: 
        symbol = lookupSymbol(name);
        break;
      case 1: 
        symbol = lookupSurrogate(name);
        break;
      case 2: 
        symbol = lookupKeyword(name);
        break;
      default:
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << kindofsym << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
        break;
    }
    if (((boolean)(symbol))) {
      if (!(symbol->symbolId == offset)) {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "intern-bootstrap-symbol-at: " << "`" << symbol << "'" << " is already interned at offset " << "`" << symbol->symbolId << "'" << std::endl;
      }
      return (symbol);
    }
    symbolarray = selectSymbolArray(kindofsym);
    if (legalSymbolArrayOffsetP(symbolarray, offset) &&
        ((boolean)(getGeneralizedSymbolFromOffset(symbolarray, offset)))) {
      symbol = getGeneralizedSymbolFromOffset(symbolarray, offset);
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "intern-bootstrap-symbol-at: " << "`" << symbol << "'" << " is already interned at offset " << "`" << offset << "'" << std::endl;
      return (symbol);
    }
    { ExtensibleSymbolArray* array = selectSymbolArray(kindofsym);

      return (helpInternGeneralizedSymbol(name, kindofsym, array, offset, oMODULEo));
    }
  }
}

Symbol* internSymbolAt(const char* name, int offset) {
  return (((Symbol*)(internBootstrapSymbolAt(name, offset, SYMBOL_SYM))));
}

Surrogate* internSurrogateAt(const char* name, int offset) {
  return (((Surrogate*)(internBootstrapSymbolAt(name, offset, SURROGATE_SYM))));
}

Keyword* internKeywordAt(const char* name, int offset) {
  return (((Keyword*)(internBootstrapSymbolAt(name, offset, KEYWORD_SYM))));
}

// Contains the number of the last-created
// context (all 'live' contexts are even-numbered).
int oCONTEXT_NUMBER_COUNTERo = -2;

void initializeKernelModule(Module* module, const char* name, const char* fullname, Module* parent) {
  module->moduleName = name;
  module->moduleFullName = fullname;
  if (((boolean)(parent))) {
    parent->childContexts->insert(module);
    module->cardinalModule = module;
  }
  module->symbolOffsetTable = newStringToIntegerHashTable();
  module->surrogateOffsetTable = newStringToIntegerHashTable();
  module->allSuperContexts = NIL;
  module->baseModule = module;
  oCONTEXT_NUMBER_COUNTERo = oCONTEXT_NUMBER_COUNTERo + 2;
  module->contextNumber = oCONTEXT_NUMBER_COUNTERo;
  module->stringifiedOptions = "";
}

void initializeKernelModules() {
  oROOT_MODULEo = newModule();
  initializeKernelModule(oROOT_MODULEo, "ROOT-MODULE", "/", NULL);
  oSTELLA_MODULEo = newModule();
  initializeKernelModule(oSTELLA_MODULEo, "STELLA", "/STELLA", oROOT_MODULEo);
  oCOMMON_LISP_MODULEo = newModule();
  initializeKernelModule(oCOMMON_LISP_MODULEo, "COMMON-LISP", "/COMMON-LISP", oROOT_MODULEo);
  setDynamicSlotValue(oCOMMON_LISP_MODULEo->dynamicSlots, SYM_SYMBOLS_STELLA_MODULE_LISP_PACKAGE, wrapString("CL"), NULL_STRING_WRAPPER);
  oROOT_MODULEo->cardinalModule = oSTELLA_MODULEo;
  oMODULEo = oSTELLA_MODULEo;
  oCONTEXTo = oMODULEo;
}

void initializeSymbolsAndKernelModules() {
  oFIXED_SYMBOL_ARRAYo = newExtensibleSymbolArray(100);
  oFIXED_SURROGATE_ARRAYo = newExtensibleSymbolArray(100);
  oFIXED_KEYWORD_ARRAYo = newExtensibleSymbolArray(100);
  oKEYWORD_OFFSET_TABLEo = newStringToIntegerHashTable();
  oSYMBOL_ARRAYo = oFIXED_SYMBOL_ARRAYo;
  oSURROGATE_ARRAYo = oFIXED_SURROGATE_ARRAYo;
  oKEYWORD_ARRAYo = oFIXED_KEYWORD_ARRAYo;
  initializeKernelModules();
}

Symbol* lookupTransientSymbol(const char* name) {
  if (((boolean)(oTRANSIENT_SYMBOL_LOOKUP_TABLEo))) {
    return (((Symbol*)(oTRANSIENT_SYMBOL_LOOKUP_TABLEo->lookup(name))));
  }
  else {
    {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Looking for a transient symbol when the parsing tables have\nnot been initialized." << std::endl;
      return (NULL);
    }
  }
}

Symbol* internTransientSymbol(const char* name) {
  { Symbol* symbol = lookupSymbolInModule(name, oMODULEo, false);

    if (((boolean)(symbol))) {
      return (symbol);
    }
    symbol = lookupTransientSymbol(name);
    if (((boolean)(symbol))) {
      return (symbol);
    }
    symbol = newTransientSymbol(name);
    symbol->homeContext = NULL;
    oTRANSIENT_SYMBOL_LOOKUP_TABLEo->insertAt(name, symbol);
    return (symbol);
  }
}

void freeTransientSymbols() {
  oTRANSIENT_SYMBOL_LOOKUP_TABLEo->initializeHashTable();
}

Symbol* internCommonLispSymbol(const char* name) {
  { Symbol* symbol = ((Symbol*)(lookupRigidSymbolWrtModule(name, oCOMMON_LISP_MODULEo, SYMBOL_SYM)));

    if (((boolean)(symbol))) {
      return (symbol);
    }
    name = stringUpcase(name);
    symbol = ((Symbol*)(lookupRigidSymbolWrtModule(name, oCOMMON_LISP_MODULEo, SYMBOL_SYM)));
    if (((boolean)(symbol))) {
      return (symbol);
    }
    symbol = ((Symbol*)(internRigidSymbolWrtModule(name, oCOMMON_LISP_MODULEo, SYMBOL_SYM)));
    return (symbol);
  }
}

boolean symbolCommonLispP(Symbol* self) {
  return (((Module*)(self->homeContext)) == oCOMMON_LISP_MODULEo);
}

boolean commonLispSymbolP(Object* self) {
  return (symbolP(self) &&
      symbolCommonLispP(((Symbol*)(self))));
}

void initializeParsingTables() {
  // Create indices for recording transient symbols and
  // Common Lisp symbols while parsing.
  oTRANSIENT_SYMBOL_LOOKUP_TABLEo = newStringHashTable();
  oCOMMON_LISP_SYMBOL_LOOKUP_TABLEo = newStringHashTable();
}

// Incremented once for each gensym call.
int oGENSYM_COUNTERo = 0;

// Defines the separator character for gensyms,
// and the fill digits.
const char* oGENSYM_MASKo = "-000";

const char* yieldGensymName(const char* prefix, int counter) {
  { const char* suffix = integerToString(((long long int)(counter)));
    int maskend = 4 - strlen(suffix);

    if (maskend < 1) {
      maskend = 1;
    }
    return (stringConcatenate(prefix, stringSubsequence(oGENSYM_MASKo, 0, maskend), 1, suffix));
  }
}

const char* yieldUniqueGensymName(const char* prefix, Module* module) {
  { const char* gensymName = yieldGensymName(prefix, oGENSYM_COUNTERo = oGENSYM_COUNTERo + 1);

    while (((boolean)(lookupSymbolInModule(gensymName, module, false)))) {
      gensymName = yieldGensymName(prefix, oGENSYM_COUNTERo = oGENSYM_COUNTERo + 1);
    }
    return (gensymName);
  }
}

Symbol* gensym(const char* prefix) {
  // Return a transient symbol with a name beginning with
  // `prefix' and ending with a globally gensym'd integer.
  return (internTransientSymbol(yieldUniqueGensymName(prefix, oMODULEo)));
}

Symbol* surrogateToSymbol(Surrogate* self) {
  return (internSymbolInModule(self->symbolName, oMODULEo, false));
}

Symbol* typeToSymbol(Surrogate* type) {
  // Convert `type' into a symbol with the same name and module.
  return (internSymbolInModule(type->symbolName, ((Module*)(type->homeContext)), true));
}

Symbol* symbolize(Surrogate* surrogate) {
  // Convert `surrogate' into a symbol with the same name and module.
  return (internSymbolInModule(surrogate->symbolName, ((Module*)(surrogate->homeContext)), false));
}

Surrogate* symbolToType(Symbol* self) {
  // Convert `self' into a surrogate with the same name and module.
  return (internSurrogateInModule(self->symbolName, ((Module*)(self->homeContext)), true));
}

Surrogate* stringToSurrogate(const char* self) {
  // Return a surrogate with the name 'self' visible
  // in the current module.  Very tricky: The logic is designed to avoid
  // returning an inherited surrogate that has no value.  In that case,
  // a new local surrogate is created that shadows the inherited surrogate.
  { Surrogate* surrogate = internSurrogateInModule(self, oMODULEo, false);

    if ((surrogate->homeContext == oMODULEo) ||
        ((boolean)(surrogate->surrogateValue))) {
      return (surrogate);
    }
    return (internSurrogateInModule(self, oMODULEo, true));
  }
}

Surrogate* symbolToSurrogate(Symbol* self) {
  // Return a surrogate with the same name as 'self'.
  // Very tricky: The logic is designed to avoid returning an inherited surrogate
  // that has no value.  In that case, a new local surrogate is created that shadows
  // the inherited surrogate.  Unlike 'string-to-surrogate', the search starts first
  // from the home context of 'self', and if that fails, then it restarts in
  // *module*.
  { Surrogate* surrogate = lookupSurrogateInModule(self->symbolName, ((Module*)(self->homeContext)), false);

    if (((boolean)(surrogate)) &&
        ((boolean)(surrogate->surrogateValue))) {
      return (surrogate);
    }
    return (stringToSurrogate(self->symbolName));
  }
}

Surrogate* Surrogate::surrogatify() {
  // Converts 'self' into a surrogate.
  { Surrogate* self = this;

    return (self);
  }
}

Surrogate* Symbol::surrogatify() {
  // Converts 'self' into a surrogate (same semantics
  // as `symbol-to-surrogate' which see).
  { Symbol* self = this;

    return (symbolToSurrogate(self));
  }
}

Surrogate* stringSurrogatify(const char* self) {
  // Converts 'self' into a surrogate.
  return (internSurrogate(self));
}

Surrogate* Object::surrogatify() {
  { Object* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "Don't know how to 'surrogatify' " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Surrogate* typify(Object* self) {
  return (self->surrogatify());
}

Keyword* Keyword::keywordify() {
  { Keyword* self = this;

    return (self);
  }
}

Keyword* GeneralizedSymbol::keywordify() {
  { GeneralizedSymbol* self = this;

    return (internKeyword(self->symbolName));
  }
}

Keyword* StringWrapper::keywordify() {
  { StringWrapper* self = this;

    return (internKeyword(self->wrapperValue));
  }
}

Keyword* stringKeywordify(const char* self) {
  return (internKeyword(self));
}

void inPlaceObjectsToSymbols(Cons* conslist) {
  { Cons* cursor = conslist;

    while (!(cursor == NIL)) {
      cursor->value = cursor->value->permanentify();
      cursor = cursor->rest;
    }
  }
}

void inPlaceObjectsToTypes(Cons* conslist) {
  { Cons* cursor = conslist;

    while (!(cursor == NIL)) {
      cursor->value = typify(cursor->value);
      cursor = cursor->rest;
    }
  }
}

boolean surrogateNameP(const char* name) {
  // Return TRUE if name is prefixed by 'SURROGATE-PREFIX-CHARACTER'.
  return ((strlen(name) > 0) &&
      (name[0] == SURROGATE_PREFIX_CHARACTER));
}

boolean keywordNameP(const char* name) {
  // Return TRUE if name is prefixed by ':'.
  return ((strlen(name) > 0) &&
      (name[0] == ':'));
}

GeneralizedSymbol* internStellaName(const char* name) {
  // Parse `name' which is assumed to be the printed
  // representation of a STELLA symbol, surrogate or keyword, intern
  // it into the current or specified module and return the result.
  // This is identical to calling `unstringify' on `name' but 10-15
  // times faster.
  { Module* module = oMODULEo;

    { const char* barename = NULL;
      const char* modulename = NULL;
      Keyword* kind = NULL;

      barename = parseStellaName(name, true, modulename, kind);
      if (modulename != NULL) {
        module = getStellaModule(modulename, true);
      }
      if (kind == KWD_SYMBOLS_SYMBOL) {
        if (oTRANSIENTOBJECTSpo &&
            (modulename == NULL)) {
          return (internTransientSymbol(barename));
        }
        else {
          return (internSymbolInModule(barename, module, false));
        }
      }
      else if (kind == KWD_SYMBOLS_SURROGATE) {
        return (internSurrogateInModule(barename, module, false));
      }
      else if (kind == KWD_SYMBOLS_KEYWORD) {
        return (internRigidSymbolWrtModule(barename, NULL, KEYWORD_SYM));
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << kind << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

GeneralizedSymbol* lookupStellaName(const char* name) {
  // Parse `name' which is assumed to be the printed
  // representation of a STELLA symbol, surrogate or keyword, and try
  // to look it up according to its type.  This is a lookup version of
  // `intern-stella-name' (which see) for cases where we don't necessarily
  // want to create a symbol in case it doesn't exist already.
  { Module* module = oMODULEo;

    { const char* barename = NULL;
      const char* modulename = NULL;
      Keyword* kind = NULL;

      barename = parseStellaName(name, true, modulename, kind);
      if (modulename != NULL) {
        module = getStellaModule(modulename, true);
      }
      if (kind == KWD_SYMBOLS_SYMBOL) {
        return (lookupSymbolInModule(barename, module, false));
      }
      else if (kind == KWD_SYMBOLS_SURROGATE) {
        return (lookupSurrogateInModule(barename, module, false));
      }
      else if (kind == KWD_SYMBOLS_KEYWORD) {
        return (lookupRigidSymbolWrtModule(barename, NULL, KEYWORD_SYM));
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << kind << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

const char* computeFullName(const char* name, Module* module) {
  if (!((boolean)(module))) {
    return (name);
  }
  else if (stringEqlP(name, "")) {
    { const char* pathname = "";

      while (((boolean)(module))) {
        pathname = stringConcatenate(MODULE_SEPARATOR_STRING, module->moduleName, 1, pathname);
        module = ((Module*)(module->parentModules->first()));
      }
      return (pathname);
    }
  }
  else {
    { const char* modulefullname = module->moduleFullName;

      if (modulefullname == NULL) {
        modulefullname = computeFullName("", module);
      }
      return (stringConcatenate(modulefullname, MODULE_SEPARATOR_STRING, 1, name));
    }
  }
}

const char* GeneralizedSymbol::localPrintName(boolean readableP) {
  { GeneralizedSymbol* self = this;

    if (readableP) {
      return (readableSymbolName(self->symbolName, oMODULEo->caseSensitiveP));
    }
    else {
      return (self->symbolName);
    }
  }
}

const char* Surrogate::localPrintName(boolean readableP) {
  { Surrogate* self = this;

    { const char* localName = (readableP ? readableSymbolName(self->symbolName, oMODULEo->caseSensitiveP) : self->symbolName);

      return (stringConcatenate("@", localName, 0));
    }
  }
}

const char* GeneralizedSymbol::relativeName(boolean readableP) {
  { GeneralizedSymbol* self = this;

    { const char* string = NULL;

      if (((Module*)(self->homeContext)) == oMODULEo) {
        string = self->localPrintName(readableP);
      }
      else {
        string = computeFullName(self->localPrintName(readableP), ((Module*)(self->homeContext)));
      }
      if (self->symbolId == -1) {
        string = stringConcatenate("<<UNINTERNED>>/", string, 0);
      }
      return (string);
    }
  }
}

const char* GeneralizedSymbol::absoluteName(boolean readableP) {
  { GeneralizedSymbol* self = this;

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oROOT_MODULEo);
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      return (self->relativeName(readableP));
    }
  }
}

extern "C" const char* stella_generalizedSymbolAbsoluteName(GeneralizedSymbol* self, int readableP) {
  // C-callable wrapper for `GeneralizedSymbol::absoluteName'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(self->absoluteName(readableP)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

boolean visibleSymbolP(Symbol* self) {
  // Return `true' if `self' is visible from the current module.
  return (self == lookupSymbolInModule(self->symbolName, oMODULEo, false));
}

boolean visibleSurrogateP(Surrogate* self) {
  // Return `true' if `self' is visible from the current module.
  return (self == lookupSurrogateInModule(self->symbolName, oMODULEo, false));
}

const char* GeneralizedSymbol::visibleName(boolean readableP) {
  { GeneralizedSymbol* self = this;

    { boolean visibleP = false;

      { Surrogate* testValue000 = safePrimaryType(self);

        if (subtypeOfSymbolP(testValue000)) {
          { GeneralizedSymbol* self000 = self;
            Symbol* self = ((Symbol*)(self000));

            visibleP = self == lookupSymbolInModule(self->symbolName, oMODULEo, false);
          }
        }
        else if (subtypeOfSurrogateP(testValue000)) {
          { GeneralizedSymbol* self001 = self;
            Surrogate* self = ((Surrogate*)(self001));

            visibleP = self == lookupSurrogateInModule(self->symbolName, oMODULEo, false);
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      if (visibleP) {
        return (self->localPrintName(readableP));
      }
      else {
        return (computeFullName(self->localPrintName(readableP), ((Module*)(self->homeContext))));
      }
    }
  }
}

Object* symbolValue(Symbol* symbol) {
  // Return the value of `symbol'.  Note, that this value is not
  // visible to code that references a variable with the same name as `symbol'.
  // The `symbol-value' is simply a special property that can always be accessed
  // in constant time.  The `symbol-value' of a symbol can be changed with `setf'.
  return (symbol->symbolValueAndPlist->value);
}

Object* symbolValueSetter(Symbol* symbol, Object* value) {
  { Cons* vplist = symbol->symbolValueAndPlist;

    if (vplist == NIL) {
      vplist = cons(NULL, NIL);
      symbol->symbolValueAndPlist = vplist;
    }
    return (vplist->value = value);
  }
}

Cons* symbolPlist(Symbol* symbol) {
  // Return the property list of `symbol'.  The `symbol-plist'
  // of a symbol can be set with `setf'.  IMPORTANT: Property list are modified 
  // destructively, hence, if you supply it as a whole make sure to always supply
  // a modfiable copy, e.g., by using `bquote'.
  return (symbol->symbolValueAndPlist->rest);
}

Cons* symbolPlistSetter(Symbol* symbol, Cons* plist) {
  { Cons* vplist = symbol->symbolValueAndPlist;

    if (vplist == NIL) {
      vplist = cons(NULL, NIL);
      symbol->symbolValueAndPlist = vplist;
    }
    return (vplist->rest = plist);
  }
}

Object* symbolProperty(Symbol* symbol, StandardObject* key) {
  // Return the property of `symbol' whose key is `eq?' to `key'.
  // Symbol properties can be set with `setf'.
  { Cons* plist = symbol->symbolValueAndPlist->rest;

    while (!(plist == NIL)) {
      if (plist->value == key) {
        return (plist->rest->value);
      }
      plist = plist->rest->rest;
    }
    return (NULL);
  }
}

Object* symbolPropertySetter(Symbol* symbol, Object* value, StandardObject* key) {
  { Cons* vplist = symbol->symbolValueAndPlist;
    Cons* plist = vplist->rest;

    while (!(plist == NIL)) {
      if (plist->value == key) {
        if (((boolean)(value))) {
          plist->rest->value = value;
        }
        else if (!(plist->rest->rest == NIL)) {
          { Cons* restplist = plist->rest;

            plist->value = restplist->rest->value;
            plist->rest = restplist->rest->rest;
          }
        }
        else if (plist == vplist->rest) {
          vplist->rest = NIL;
        }
        else {
          plist->rest->value = value;
        }
        return (value);
      }
      plist = plist->rest->rest;
    }
    if (((boolean)(value))) {
      if (vplist == NIL) {
        vplist = cons(NULL, NIL);
        symbol->symbolValueAndPlist = vplist;
      }
      vplist->rest = cons(key, cons(value, vplist->rest));
    }
    return (value);
  }
}

boolean symbolConstituentCharacterP(char character) {
  { Keyword* testValue000 = oCHARACTER_TYPE_TABLEo[(int)(unsigned char) character];

    if ((testValue000 == KWD_SYMBOLS_LETTER) ||
        ((testValue000 == KWD_SYMBOLS_DIGIT) ||
         (testValue000 == KWD_SYMBOLS_SYMBOL_CONSTITUENT))) {
      return (true);
    }
    else {
      return (false);
    }
  }
}

const char* oSYMBOL_ESCAPE_CODE_TABLEo = NULL;

const char* oCASE_SENSITIVE_SYMBOL_ESCAPE_CODE_TABLEo = NULL;

const char* initializeSymbolEscapeCodeTable(boolean casesensitiveP) {
  { char* buffer = native_make_mutable_string(256, NULL_CHARACTER);

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = 255;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        { Keyword* testValue000 = oCHARACTER_TYPE_TABLEo[i];

          if (testValue000 == KWD_SYMBOLS_DIGIT) {
            buffer[i] = ((char) 1);
          }
          else if ((testValue000 == KWD_SYMBOLS_LETTER) ||
              (testValue000 == KWD_SYMBOLS_SYMBOL_CONSTITUENT)) {
            if ((!casesensitiveP) &&
                lowerCaseCharacterP((char) i)) {
              buffer[i] = ((char) 2);
            }
            else {
              buffer[i] = ((char) 0);
            }
          }
          else {
            buffer[i] = ((char) 2);
          }
        }
      }
    }
    { char ch = NULL_CHARACTER;
      const char* vector000 = ".+-";
      int index000 = 0;
      int length000 = strlen(vector000);

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        ch = vector000[index000];
        buffer[((int)(unsigned char) ch)] = ((char) 1);
      }
    }
    buffer[((int)(unsigned char) '\\')] = ((char) 3);
    buffer[((int)(unsigned char) '|')] = ((char) 3);
    return (buffer);
  }
}

Keyword* computeSymbolEscapeCode(const char* name, boolean casesensitiveP) {
  { const char* table = (casesensitiveP ? oCASE_SENSITIVE_SYMBOL_ESCAPE_CODE_TABLEo : oSYMBOL_ESCAPE_CODE_TABLEo);
    int escapecode = 0;
    int maxescapecode = 0;
    boolean firstcharP = true;
    boolean couldbenumberP = true;

    { char ch = NULL_CHARACTER;
      const char* vector000 = name;
      int index000 = 0;
      int length000 = strlen(vector000);

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        ch = vector000[index000];
        escapecode = (int)(unsigned char) (table[((int)(unsigned char) ch)]);
        if (escapecode == 0) {
          if (couldbenumberP &&
              ((!(ch == 'E')) &&
               (!(ch == 'e')))) {
            couldbenumberP = false;
          }
        }
        else if (firstcharP) {
          maxescapecode = escapecode;
          couldbenumberP = escapecode == 1;
        }
        else {
          if ((escapecode > 1) &&
              (escapecode > maxescapecode)) {
            maxescapecode = escapecode;
          }
        }
        firstcharP = false;
      }
    }
    if (firstcharP) {
      return (KWD_SYMBOLS_ESCAPED);
    }
    else {
      switch (maxescapecode) {
        case 0: 
          return (KWD_SYMBOLS_UNESCAPED);
        case 1: 
          if (couldbenumberP) {
            { TokenizerTable* tok_table_ = oSTELLA_TOKENIZER_TABLEo;
              const char* tok_transitions_ = tok_table_->transitions;
              Object** tok_statenames_ = tok_table_->stateNames->theArray;
              int tok_tokenstart_ = -1;
              boolean tok_endoftokensP_ = false;
              TokenizerStreamState* tok_streamstate_ = NULL;
              char* tok_buffer_ = mutableStringCopy(name);
              int tok_state_ = 1;
              int tok_nextstate_ = tok_state_;
              int tok_cursor_ = 0;
              int tok_size_ = strlen(name);
              int tok_end_ = tok_size_;

              {
                tok_statenames_ = tok_statenames_;
                tok_endoftokensP_ = tok_endoftokensP_;
              }
              tok_streamstate_ = tok_streamstate_;
              { Object** tok_stellalogicalstatenames_ = oSTELLA_LOGICAL_STATE_NAMESo->theArray;
                Keyword* tok_stellalogicalstatename_ = NULL;

                {
                  {
                    tok_tokenstart_ = -1;
                    for (;;) {
                      if (tok_cursor_ == tok_end_) {
                        if (tok_nextstate_ == -1) {
                          tok_endoftokensP_ = true;
                        }
                        else if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)((tok_table_->legalEofStates->theArray)[tok_state_])))) {
                          tok_nextstate_ = -1;
                          if (tok_tokenstart_ == -1) {
                            tok_endoftokensP_ = true;
                          }
                        }
                        else {
                          tok_state_ = 0;
                          tok_nextstate_ = -1;
                        }
                        goto loopExit090;
                      }
                      tok_nextstate_ = (int)(unsigned char) (tok_buffer_[tok_cursor_]);
                      tok_nextstate_ = (int)(unsigned char) (tok_transitions_[((((tok_state_ << 8)) | tok_nextstate_))]);
                      if ((tok_nextstate_ & 128) == 0) {
                        tok_state_ = tok_nextstate_;
                        tok_cursor_ = tok_cursor_ + 1;
                      }
                      else if (tok_tokenstart_ == -1) {
                        if ((tok_nextstate_ & 64) == 0) {
                          tok_tokenstart_ = tok_cursor_;
                        }
                        tok_state_ = (tok_nextstate_ & 63);
                        tok_cursor_ = tok_cursor_ + 1;
                      }
                      else {
                        goto loopExit090;
                      }
                    }
                    loopExit090:;
                    if (((boolean)(tok_streamstate_))) {
                      tok_streamstate_->cursor = tok_cursor_;
                      tok_streamstate_->table = tok_table_;
                      tok_streamstate_->state = tok_state_;
                    }
                  }
                  tok_stellalogicalstatename_ = ((Keyword*)(tok_stellalogicalstatenames_[tok_state_]));
                }
                if (tok_stellalogicalstatename_ == KWD_SYMBOLS_SYMBOL) {
                  couldbenumberP = false;
                }
              }
            }
          }
          if (couldbenumberP) {
            return (KWD_SYMBOLS_ESCAPED);
          }
          else {
            return (KWD_SYMBOLS_UNESCAPED);
          }
          break;
        case 2: 
          if ((name[0] == '/') &&
              stringEqlP(name, "/")) {
            return (KWD_SYMBOLS_UNESCAPED);
          }
          else {
            return (KWD_SYMBOLS_ESCAPED);
          }
          break;
        case 3: 
          return (KWD_SYMBOLS_COMPLEX_ESCAPED);
        default:
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << maxescapecode << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
          break;
      }
    }
  }
}

void printSymbolNameReadably(const char* name, std::ostream* stream, boolean casesensitiveP) {
  { Keyword* testValue000 = computeSymbolEscapeCode(name, casesensitiveP);

    if (testValue000 == KWD_SYMBOLS_UNESCAPED) {
      *(stream) << name;
    }
    else if (testValue000 == KWD_SYMBOLS_ESCAPED) {
      *(stream) << "|" << name << "|";
    }
    else if (testValue000 == KWD_SYMBOLS_COMPLEX_ESCAPED) {
      *(stream) << "|";
      { char ch = NULL_CHARACTER;
        const char* vector000 = name;
        int index000 = 0;
        int length000 = strlen(vector000);

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          ch = vector000[index000];
          if ((ch == '\\') ||
              (ch == '|')) {
            *(stream) << "\\";
          }
          *(stream) << ch;
        }
      }
      *(stream) << "|";
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

const char* readableSymbolName(const char* name, boolean casesensitiveP) {
  { Keyword* testValue000 = computeSymbolEscapeCode(name, casesensitiveP);

    if (testValue000 == KWD_SYMBOLS_UNESCAPED) {
      return (name);
    }
    else if (testValue000 == KWD_SYMBOLS_ESCAPED) {
      return (stringConcatenate("|", name, 1, "|"));
    }
    else if (testValue000 == KWD_SYMBOLS_COMPLEX_ESCAPED) {
      { OutputStringStream* s = newOutputStringStream();

        printSymbolNameReadably(name, s->nativeStream, casesensitiveP);
        return (s->theStringReader());
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

void printSymbol(Symbol* self, std::ostream* stream) {
  { boolean visibleP = self == lookupSymbolInModule(self->symbolName, oMODULEo, false);
    Module* module = ((Module*)(self->homeContext));

    if (!visibleP) {
      if (self->symbolId == -1) {
        *(stream) << "<<UNINTERNED>>/";
      }
      else {
        if (((boolean)(module))) {
          if (oPRINTREADABLYpo &&
              (module == oCOMMON_LISP_MODULEo)) {
            {
              *(stream) << "CL:" << self->symbolName;
              return;
            }
          }
          else {
            *(stream) << module->moduleFullName << "/";
          }
        }
      }
    }
    if (oPRINTREADABLYpo) {
      printSymbolNameReadably(self->symbolName, stream, oMODULEo->caseSensitiveP);
    }
    else {
      *(stream) << self->symbolName;
    }
  }
}

void printSurrogate(Surrogate* self, std::ostream* stream) {
  { boolean visibleP = self == lookupSurrogateInModule(self->symbolName, oMODULEo, false);
    Module* module = ((Module*)(self->homeContext));

    if (!visibleP) {
      if ((self->symbolId == -1) ||
          (!((boolean)(module)))) {
        *(stream) << "<<UNINTERNED>>/";
      }
      else {
        *(stream) << module->moduleFullName << "/";
      }
    }
    *(stream) << "@";
    if (oPRINTREADABLYpo) {
      printSymbolNameReadably(self->symbolName, stream, oMODULEo->caseSensitiveP);
    }
    else {
      *(stream) << self->symbolName;
    }
  }
}

void printKeyword(Keyword* self, std::ostream* stream) {
  *(stream) << ":";
  if (oPRINTREADABLYpo) {
    printSymbolNameReadably(self->symbolName, stream, false);
  }
  else {
    *(stream) << self->symbolName;
  }
}

void helpStartupSymbols1() {
  {
    SYM_SYMBOLS_STELLA_MODULE_LISP_PACKAGE = ((Symbol*)(internRigidSymbolWrtModule("MODULE-LISP-PACKAGE", NULL, 0)));
    SYM_SYMBOLS_STELLA_JAVA_PACKAGE = ((Symbol*)(internRigidSymbolWrtModule("JAVA-PACKAGE", NULL, 0)));
    SYM_SYMBOLS_STELLA_MODULE_CPP_PACKAGE = ((Symbol*)(internRigidSymbolWrtModule("MODULE-CPP-PACKAGE", NULL, 0)));
    SYM_SYMBOLS_STELLA_CODE_ONLYp = ((Symbol*)(internRigidSymbolWrtModule("CODE-ONLY?", NULL, 0)));
    KWD_SYMBOLS_SYMBOL = ((Keyword*)(internRigidSymbolWrtModule("SYMBOL", NULL, 2)));
    KWD_SYMBOLS_SURROGATE = ((Keyword*)(internRigidSymbolWrtModule("SURROGATE", NULL, 2)));
    KWD_SYMBOLS_KEYWORD = ((Keyword*)(internRigidSymbolWrtModule("KEYWORD", NULL, 2)));
    KWD_SYMBOLS_LETTER = ((Keyword*)(internRigidSymbolWrtModule("LETTER", NULL, 2)));
    KWD_SYMBOLS_DIGIT = ((Keyword*)(internRigidSymbolWrtModule("DIGIT", NULL, 2)));
    KWD_SYMBOLS_SYMBOL_CONSTITUENT = ((Keyword*)(internRigidSymbolWrtModule("SYMBOL-CONSTITUENT", NULL, 2)));
    KWD_SYMBOLS_ESCAPED = ((Keyword*)(internRigidSymbolWrtModule("ESCAPED", NULL, 2)));
    KWD_SYMBOLS_UNESCAPED = ((Keyword*)(internRigidSymbolWrtModule("UNESCAPED", NULL, 2)));
    KWD_SYMBOLS_COMPLEX_ESCAPED = ((Keyword*)(internRigidSymbolWrtModule("COMPLEX-ESCAPED", NULL, 2)));
    SYM_SYMBOLS_STELLA_STARTUP_SYMBOLS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-SYMBOLS", NULL, 0)));
    SYM_SYMBOLS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupSymbols2() {
  {
    defineFunctionObject("NEXT-FREE-OFFSET", "(DEFUN (NEXT-FREE-OFFSET INTEGER) ((SELF EXTENSIBLE-SYMBOL-ARRAY)))", ((cpp_function_code)(&nextFreeOffset)), NULL);
    defineFunctionObject("FREE-SYMBOL-OFFSET", "(DEFUN FREE-SYMBOL-OFFSET ((SELF EXTENSIBLE-SYMBOL-ARRAY) (OFFSET INTEGER)))", ((cpp_function_code)(&freeSymbolOffset)), NULL);
    defineFunctionObject("ADD-TO-SYMBOL-ARRAY-AT", "(DEFUN ADD-TO-SYMBOL-ARRAY-AT ((ARRAY EXTENSIBLE-SYMBOL-ARRAY) (OFFSET INTEGER) (SYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&addToSymbolArrayAt)), NULL);
    defineFunctionObject("ADD-TO-SYMBOL-ARRAY", "(DEFUN (ADD-TO-SYMBOL-ARRAY INTEGER) ((ARRAY EXTENSIBLE-SYMBOL-ARRAY) (SYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&addToSymbolArray)), NULL);
    defineFunctionObject("LEGAL-SYMBOL-ARRAY-OFFSET?", "(DEFUN (LEGAL-SYMBOL-ARRAY-OFFSET? BOOLEAN) ((ARRAY EXTENSIBLE-SYMBOL-ARRAY) (OFFSET INTEGER)))", ((cpp_function_code)(&legalSymbolArrayOffsetP)), NULL);
    defineFunctionObject("GET-SYM", "(DEFUN (GET-SYM SYMBOL) ((OFFSET INTEGER)) :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&getSym)), NULL);
    defineFunctionObject("GET-SGT", "(DEFUN (GET-SGT SURROGATE) ((OFFSET INTEGER)) :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&getSgt)), NULL);
    defineFunctionObject("GET-KWD", "(DEFUN (GET-KWD KEYWORD) ((OFFSET INTEGER)) :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&getKwd)), NULL);
    defineFunctionObject("GET-GENERALIZED-SYMBOL-FROM-OFFSET", "(DEFUN (GET-GENERALIZED-SYMBOL-FROM-OFFSET GENERALIZED-SYMBOL) ((SYMBOLARRAY EXTENSIBLE-SYMBOL-ARRAY) (OFFSET INTEGER)) :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&getGeneralizedSymbolFromOffset)), NULL);
    defineFunctionObject("GET-SYM-FROM-OFFSET", "(DEFUN (GET-SYM-FROM-OFFSET SYMBOL) ((OFFSET INTEGER)) :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&getSymFromOffset)), NULL);
    defineFunctionObject("GET-SGT-FROM-OFFSET", "(DEFUN (GET-SGT-FROM-OFFSET SURROGATE) ((OFFSET INTEGER)) :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&getSgtFromOffset)), NULL);
    defineFunctionObject("GET-KWD-FROM-OFFSET", "(DEFUN (GET-KWD-FROM-OFFSET KEYWORD) ((OFFSET INTEGER)) :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&getKwdFromOffset)), NULL);
    defineFunctionObject("SELECT-SYMBOL-OFFSET-TABLE", "(DEFUN (SELECT-SYMBOL-OFFSET-TABLE STRING-TO-INTEGER-HASH-TABLE) ((MODULE MODULE) (KINDOFSYM INTEGER)))", ((cpp_function_code)(&selectSymbolOffsetTable)), NULL);
    defineFunctionObject("SELECT-SYMBOL-ARRAY", "(DEFUN (SELECT-SYMBOL-ARRAY EXTENSIBLE-SYMBOL-ARRAY) ((KINDOFSYM INTEGER)))", ((cpp_function_code)(&selectSymbolArray)), NULL);
    defineFunctionObject("LOOKUP-RIGID-SYMBOL-LOCALLY", "(DEFUN (LOOKUP-RIGID-SYMBOL-LOCALLY GENERALIZED-SYMBOL) ((NAME STRING) (MODULE MODULE) (KINDOFSYM INTEGER)) :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&lookupRigidSymbolLocally)), NULL);
    defineFunctionObject("YIELD-VISIBLE-RIGID-SYMBOLS-WRT-MODULE", "(DEFUN (YIELD-VISIBLE-RIGID-SYMBOLS-WRT-MODULE (CONS OF GENERALIZED-SYMBOL)) ((NAME STRING) (MODULE MODULE) (KINDOFSYM INTEGER)))", ((cpp_function_code)(&yieldVisibleRigidSymbolsWrtModule)), NULL);
    defineFunctionObject("VISIBLE-RIGID-SYMBOLS-WRT-MODULE", "(DEFUN (VISIBLE-RIGID-SYMBOLS-WRT-MODULE (ITERATOR OF GENERALIZED-SYMBOL)) ((NAME STRING) (MODULE MODULE) (KINDOFSYM INTEGER)))", ((cpp_function_code)(&visibleRigidSymbolsWrtModule)), NULL);
    defineFunctionObject("REMOVE-SHADOWED-SYMBOLS", "(DEFUN (REMOVE-SHADOWED-SYMBOLS (CONS OF GENERALIZED-SYMBOL)) ((VISIBLESYMBOLS (CONS OF GENERALIZED-SYMBOL))))", ((cpp_function_code)(&removeShadowedSymbols)), NULL);
    defineFunctionObject("LOOKUP-RIGID-SYMBOL-OFFSET-WRT-MODULE", "(DEFUN (LOOKUP-RIGID-SYMBOL-OFFSET-WRT-MODULE INTEGER) ((NAME STRING) (MODULE MODULE) (KINDOFSYM INTEGER)))", ((cpp_function_code)(&lookupRigidSymbolOffsetWrtModule)), NULL);
    defineFunctionObject("LOOKUP-RIGID-SYMBOL-WRT-MODULE", "(DEFUN (LOOKUP-RIGID-SYMBOL-WRT-MODULE GENERALIZED-SYMBOL) ((NAME STRING) (MODULE MODULE) (KINDOFSYM INTEGER)))", ((cpp_function_code)(&lookupRigidSymbolWrtModule)), NULL);
    defineFunctionObject("LOOKUP-RIGID-SYMBOL", "(DEFUN (LOOKUP-RIGID-SYMBOL GENERALIZED-SYMBOL) ((NAME STRING) (KINDOFSYM INTEGER)) :DOCUMENTATION \"Return the permanent symbol with name 'name' and type\n`kindOfSym' visible from the current module (case-sensitive).\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&lookupRigidSymbol)), NULL);
    defineFunctionObject("LOOKUP-SYMBOL", "(DEFUN (LOOKUP-SYMBOL SYMBOL) ((NAME STRING)) :DOCUMENTATION \"Return the first symbol with `name' visible from the current module.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&lookupSymbol)), NULL);
    defineFunctionObject("LOOKUP-SYMBOL-IN-MODULE", "(DEFUN (LOOKUP-SYMBOL-IN-MODULE SYMBOL) ((NAME STRING) (MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Return the first symbol with `name' visible from `module'.\nIf `local?' only consider symbols directly interned in `module'.\nIf `module' is `null', use `*MODULE*' instead.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&lookupSymbolInModule)), NULL);
    defineFunctionObject("LOOKUP-VISIBLE-SYMBOLS-IN-MODULE", "(DEFUN (LOOKUP-VISIBLE-SYMBOLS-IN-MODULE (CONS OF SYMBOL)) ((NAME STRING) (MODULE MODULE) (ENFORCESHADOWING? BOOLEAN)) :DOCUMENTATION \"Return the list of symbols with `name' visible from `module'.\nMore specific symbols (relative to the module precedence order defined by\n`visible-modules') come earlier in the list.  If `module' is `null', start\nfrom `*MODULE*' instead.  If `enforceShadowing?' is true, do not return any\nsymbols that are shadowed due to some :SHADOW declaration.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupVisibleSymbolsInModule)), NULL);
    defineFunctionObject("LOOKUP-SURROGATE", "(DEFUN (LOOKUP-SURROGATE SURROGATE) ((NAME STRING)) :DOCUMENTATION \"Return the first surrogate with `name' visible from the current module.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&lookupSurrogate)), NULL);
    defineFunctionObject("LOOKUP-SURROGATE-IN-MODULE", "(DEFUN (LOOKUP-SURROGATE-IN-MODULE SURROGATE) ((NAME STRING) (MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Return the first surrogate with `name' visible from `module'.\nIf `local?' only consider surrogates directly interned in `module'.\nIf `module' is `null', use `*MODULE*' instead.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&lookupSurrogateInModule)), NULL);
    defineFunctionObject("LOOKUP-VISIBLE-SURROGATES-IN-MODULE", "(DEFUN (LOOKUP-VISIBLE-SURROGATES-IN-MODULE (CONS OF SURROGATE)) ((NAME STRING) (MODULE MODULE) (ENFORCESHADOWING? BOOLEAN)) :DOCUMENTATION \"Return the list of surrogates with `name' visible from `module'.\nMore specific surrogates (relative to the module precedence order defined by\n`visible-modules') come earlier in the list.  If `module' is `null', start\nfrom `*MODULE*' instead.  If `enforceShadowing?' is true, do not return any\nsurrogates that are shadowed due to some :SHADOW declaration.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupVisibleSurrogatesInModule)), NULL);
    defineFunctionObject("LOOKUP-KEYWORD", "(DEFUN (LOOKUP-KEYWORD KEYWORD) ((NAME STRING)) :DOCUMENTATION \"Return the keyword with `name' if it exists.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&lookupKeyword)), NULL);
    defineFunctionObject("HELP-INTERN-GENERALIZED-SYMBOL", "(DEFUN (HELP-INTERN-GENERALIZED-SYMBOL GENERALIZED-SYMBOL) ((NAME STRING) (KINDOFSYM INTEGER) (ARRAY EXTENSIBLE-SYMBOL-ARRAY) (OFFSET INTEGER) (MODULE MODULE)) :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&helpInternGeneralizedSymbol)), NULL);
    defineFunctionObject("INTERN-RIGID-SYMBOL-WRT-MODULE", "(DEFUN (INTERN-RIGID-SYMBOL-WRT-MODULE GENERALIZED-SYMBOL) ((NAME STRING) (MODULE MODULE) (KINDOFSYM INTEGER)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE :DOCUMENTATION \"Return a newly-created or existing rigid symbol with\nname `name'.\")", ((cpp_function_code)(&internRigidSymbolWrtModule)), NULL);
    defineFunctionObject("INTERN-RIGID-SYMBOL-LOCALLY", "(DEFUN (INTERN-RIGID-SYMBOL-LOCALLY GENERALIZED-SYMBOL) ((NAME STRING) (MODULE MODULE) (KINDOFSYM INTEGER)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE :DOCUMENTATION \"Return a newly-created or existing rigid symbol\ninterned into the module `module' with name `name'.\")", ((cpp_function_code)(&internRigidSymbolLocally)), NULL);
    defineFunctionObject("INTERN-RIGID-SYMBOL-CASE-SENSITIVELY", "(DEFUN (INTERN-RIGID-SYMBOL-CASE-SENSITIVELY GENERALIZED-SYMBOL) ((NAME STRING) (KINDOFSYM INTEGER) (TRYUPCASING? BOOLEAN)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&internRigidSymbolCaseSensitively)), NULL);
    defineFunctionObject("INTERN-PERMANENT-SYMBOL", "(DEFUN (INTERN-PERMANENT-SYMBOL SYMBOL) ((NAME STRING)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE :DOCUMENTATION \"Return a newly-created or existing permanent symbol with\nname `name'.\")", ((cpp_function_code)(&internPermanentSymbol)), NULL);
    defineFunctionObject("INTERN-SYMBOL", "(DEFUN (INTERN-SYMBOL SYMBOL) ((NAME STRING)) :DOCUMENTATION \"Return a newly-created or existing symbol with name `name'.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&internSymbol)), NULL);
    defineFunctionObject("INTERN-SYMBOL-IN-MODULE", "(DEFUN (INTERN-SYMBOL-IN-MODULE SYMBOL) ((NAME STRING) (MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Look for a symbol named `name' in `module' (if `local?' do\nnot consider inherited modules).  If none exists, intern it locally in\n`module'.  Return the existing or newly-created symbol.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&internSymbolInModule)), NULL);
    defineFunctionObject("INTERN-DERIVED-SYMBOL", "(DEFUN (INTERN-DERIVED-SYMBOL SYMBOL) ((BASESYMBOL GENERALIZED-SYMBOL) (NEWNAME STRING)) :PUBLIC? TRUE :CONSTRUCTOR? TRUE :DOCUMENTATION \"Return a newly-created or existing symbol with name\n`newName' which is interned in the same module as `baseSymbol'.\")", ((cpp_function_code)(&internDerivedSymbol)), NULL);
    defineFunctionObject("INTERN-SURROGATE", "(DEFUN (INTERN-SURROGATE SURROGATE) ((NAME STRING)) :DOCUMENTATION \"Return a newly-created or existing surrogate with name `name'.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&internSurrogate)), NULL);
    defineFunctionObject("INTERN-SURROGATE-IN-MODULE", "(DEFUN (INTERN-SURROGATE-IN-MODULE SURROGATE) ((NAME STRING) (MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Look for a symbol named `name' in `module' (if `local?' do\nnot consider inherited modules).  If none exists, intern it locally in\n`module'.  Return the existing or newly-created symbol.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&internSurrogateInModule)), NULL);
    defineFunctionObject("INTERN-DERIVED-SURROGATE", "(DEFUN (INTERN-DERIVED-SURROGATE SURROGATE) ((BASESYMBOL GENERALIZED-SYMBOL) (NEWNAME STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Return a newly-created or existing surrogate with name\n`newName' which is interned in the same module as `baseSymbol'.\")", ((cpp_function_code)(&internDerivedSurrogate)), NULL);
    defineFunctionObject("INTERN-KEYWORD", "(DEFUN (INTERN-KEYWORD KEYWORD) ((NAME STRING)) :DOCUMENTATION \"Return a newly-created or existing keyword with name\n`name'.  Storage note: a COPY of `name' is stored in the keyword\" :PUBLIC? TRUE)", ((cpp_function_code)(&internKeyword)), NULL);
    defineFunctionObject("IMPORT-SYMBOL", "(DEFUN (IMPORT-SYMBOL SYMBOL) ((SYMBOL SYMBOL) (MODULE MODULE)) :DOCUMENTATION \"Import `symbol' into `module' and return the imported `symbol'.\nSignal an error if a different symbol with the same name already exists\nlocally in `module'.  Any symbol with the same name visible in `module' by\ninheritance will be shadowed by the newly imported `symbol'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&importSymbol)), NULL);
    defineFunctionObject("IMPORT-SURROGATE", "(DEFUN (IMPORT-SURROGATE SURROGATE) ((SURROGATE SURROGATE) (MODULE MODULE)) :DOCUMENTATION \"Import `surrogate' into `module' and return the imported `surrogate'.\nSignal an error if a different surrogate with the same name already exists\nlocally in `module'.  Any surrogate with the same name visible in `module' by\ninheritance will be shadowed by the newly imported `surrogate'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&importSurrogate)), NULL);
    defineFunctionObject("SAFE-IMPORT-SYMBOL", "(DEFUN (SAFE-IMPORT-SYMBOL SYMBOL) ((SYMBOL SYMBOL) (MODULE MODULE)) :DOCUMENTATION \"Safe version of `import-symbol' (which see).  Only imports `symbol' if\nno symbol with that name is currently interned or visible in `module'.\nReturns `symbol' if it was imported or the conflicting symbol in `module'\notherwise.\" :PUBLIC? TRUE)", ((cpp_function_code)(&safeImportSymbol)), NULL);
    defineFunctionObject("SAFE-IMPORT-SURROGATE", "(DEFUN (SAFE-IMPORT-SURROGATE SURROGATE) ((SURROGATE SURROGATE) (MODULE MODULE)) :DOCUMENTATION \"Safe version of `import-surrogate' (which see).  Only imports `surrogate' if\nno surrogate with that name is currently interned or visible in `module'.\nReturns `surrogate' if it was imported or the conflicting surrogate in `module'\notherwise.\" :PUBLIC? TRUE)", ((cpp_function_code)(&safeImportSurrogate)), NULL);
    defineFunctionObject("UNINTERN-SYMBOL", "(DEFUN UNINTERN-SYMBOL ((SELF SYMBOL)) :DOCUMENTATION \"Remove `self' from its home module and the symbol table.\" :PUBLIC? TRUE)", ((cpp_function_code)(&uninternSymbol)), NULL);
    defineFunctionObject("UNINTERN-SURROGATE", "(DEFUN UNINTERN-SURROGATE ((SELF SURROGATE)) :DOCUMENTATION \"Remove `self' from its home module and the surrogate table.\")", ((cpp_function_code)(&uninternSurrogate)), NULL);
    defineMethodObject("(DEFMETHOD (DELETED? BOOLEAN) ((SELF GENERALIZED-SYMBOL)) :GLOBALLY-INLINE? TRUE (RETURN (EQL? (SYMBOL-ID SELF) -1)))", wrapMethodCode(((cpp_method_code)(&GeneralizedSymbol::deletedP))), NULL);
    defineFunctionObject("INTERN-BOOTSTRAP-SYMBOL-AT", "(DEFUN (INTERN-BOOTSTRAP-SYMBOL-AT GENERALIZED-SYMBOL) ((NAME STRING) (OFFSET INTEGER) (KINDOFSYM INTEGER)) :DOCUMENTATION \"Interns a symbol, or keyword with\n`name' and symbol-id `offset'.\nIf a symbol with that ID already existed, an error is signaled.  This\nfunction is used to recreate the symbol table in a way where symbol IDs\nwhich got hardwired into translated code will refer to the correct objects.\")", ((cpp_function_code)(&internBootstrapSymbolAt)), NULL);
    defineFunctionObject("INTERN-SYMBOL-AT", "(DEFUN (INTERN-SYMBOL-AT SYMBOL) ((NAME STRING) (OFFSET INTEGER)))", ((cpp_function_code)(&internSymbolAt)), NULL);
    defineFunctionObject("INTERN-SURROGATE-AT", "(DEFUN (INTERN-SURROGATE-AT SURROGATE) ((NAME STRING) (OFFSET INTEGER)))", ((cpp_function_code)(&internSurrogateAt)), NULL);
    defineFunctionObject("INTERN-KEYWORD-AT", "(DEFUN (INTERN-KEYWORD-AT KEYWORD) ((NAME STRING) (OFFSET INTEGER)))", ((cpp_function_code)(&internKeywordAt)), NULL);
    defineFunctionObject("INITIALIZE-KERNEL-MODULE", "(DEFUN INITIALIZE-KERNEL-MODULE ((MODULE MODULE) (NAME STRING) (FULLNAME STRING) (PARENT MODULE)))", ((cpp_function_code)(&initializeKernelModule)), NULL);
    defineFunctionObject("INITIALIZE-KERNEL-MODULES", "(DEFUN INITIALIZE-KERNEL-MODULES ())", ((cpp_function_code)(&initializeKernelModules)), NULL);
    defineFunctionObject("INITIALIZE-SYMBOLS-AND-KERNEL-MODULES", "(DEFUN INITIALIZE-SYMBOLS-AND-KERNEL-MODULES ())", ((cpp_function_code)(&initializeSymbolsAndKernelModules)), NULL);
    defineFunctionObject("LOOKUP-TRANSIENT-SYMBOL", "(DEFUN (LOOKUP-TRANSIENT-SYMBOL SYMBOL) ((NAME STRING)))", ((cpp_function_code)(&lookupTransientSymbol)), NULL);
    defineFunctionObject("INTERN-TRANSIENT-SYMBOL", "(DEFUN (INTERN-TRANSIENT-SYMBOL SYMBOL) ((NAME STRING)))", ((cpp_function_code)(&internTransientSymbol)), NULL);
    defineFunctionObject("FREE-TRANSIENT-SYMBOLS", "(DEFUN FREE-TRANSIENT-SYMBOLS ())", ((cpp_function_code)(&freeTransientSymbols)), NULL);
    defineFunctionObject("INTERN-COMMON-LISP-SYMBOL", "(DEFUN (INTERN-COMMON-LISP-SYMBOL SYMBOL) ((NAME STRING)))", ((cpp_function_code)(&internCommonLispSymbol)), NULL);
    defineFunctionObject("SYMBOL-COMMON-LISP?", "(DEFUN (SYMBOL-COMMON-LISP? BOOLEAN) ((SELF SYMBOL)))", ((cpp_function_code)(&symbolCommonLispP)), NULL);
    defineFunctionObject("COMMON-LISP-SYMBOL?", "(DEFUN (COMMON-LISP-SYMBOL? BOOLEAN) ((SELF OBJECT)))", ((cpp_function_code)(&commonLispSymbolP)), NULL);
  }
}

void helpStartupSymbols3() {
  {
    defineFunctionObject("INITIALIZE-PARSING-TABLES", "(DEFUN INITIALIZE-PARSING-TABLES () :DOCUMENTATION \"Create indices for recording transient symbols and\nCommon Lisp symbols while parsing.\")", ((cpp_function_code)(&initializeParsingTables)), NULL);
    defineFunctionObject("YIELD-GENSYM-NAME", "(DEFUN (YIELD-GENSYM-NAME STRING) ((PREFIX STRING) (COUNTER INTEGER)))", ((cpp_function_code)(&yieldGensymName)), NULL);
    defineFunctionObject("YIELD-UNIQUE-GENSYM-NAME", "(DEFUN (YIELD-UNIQUE-GENSYM-NAME STRING) ((PREFIX STRING) (MODULE MODULE)))", ((cpp_function_code)(&yieldUniqueGensymName)), NULL);
    defineFunctionObject("GENSYM", "(DEFUN (GENSYM SYMBOL) ((PREFIX STRING)) :DOCUMENTATION \"Return a transient symbol with a name beginning with\n`prefix' and ending with a globally gensym'd integer.\" :PUBLIC? TRUE)", ((cpp_function_code)(&gensym)), NULL);
    defineFunctionObject("SURROGATE-TO-SYMBOL", "(DEFUN (SURROGATE-TO-SYMBOL SYMBOL) ((SELF SURROGATE)) :PUBLIC? TRUE)", ((cpp_function_code)(&surrogateToSymbol)), NULL);
    defineFunctionObject("TYPE-TO-SYMBOL", "(DEFUN (TYPE-TO-SYMBOL SYMBOL) ((TYPE TYPE)) :DOCUMENTATION \"Convert `type' into a symbol with the same name and module.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (INTERN-SYMBOL-IN-MODULE (SYMBOL-NAME TYPE) (INTERNED-IN TYPE) TRUE)))", ((cpp_function_code)(&typeToSymbol)), NULL);
    defineFunctionObject("SYMBOLIZE", "(DEFUN (SYMBOLIZE SYMBOL) ((SURROGATE SURROGATE)) :DOCUMENTATION \"Convert `surrogate' into a symbol with the same name and module.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (INTERN-SYMBOL-IN-MODULE (SYMBOL-NAME SURROGATE) (INTERNED-IN SURROGATE) FALSE)))", ((cpp_function_code)(&symbolize)), NULL);
    defineFunctionObject("SYMBOL-TO-TYPE", "(DEFUN (SYMBOL-TO-TYPE SURROGATE) ((SELF SYMBOL)) :DOCUMENTATION \"Convert `self' into a surrogate with the same name and module.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (INTERN-SURROGATE-IN-MODULE (SYMBOL-NAME SELF) (INTERNED-IN SELF) TRUE)))", ((cpp_function_code)(&symbolToType)), NULL);
    defineFunctionObject("STRING-TO-SURROGATE", "(DEFUN (STRING-TO-SURROGATE SURROGATE) ((SELF STRING)) :DOCUMENTATION \"Return a surrogate with the name 'self' visible\nin the current module.  Very tricky: The logic is designed to avoid\nreturning an inherited surrogate that has no value.  In that case,\na new local surrogate is created that shadows the inherited surrogate.\" :PUBLIC? TRUE)", ((cpp_function_code)(((Surrogate*  (*) (const char*))(&stringToSurrogate)))), NULL);
    defineFunctionObject("SYMBOL-TO-SURROGATE", "(DEFUN (SYMBOL-TO-SURROGATE SURROGATE) ((SELF SYMBOL)) :DOCUMENTATION \"Return a surrogate with the same name as 'self'.\nVery tricky: The logic is designed to avoid returning an inherited surrogate\nthat has no value.  In that case, a new local surrogate is created that shadows\nthe inherited surrogate.  Unlike 'string-to-surrogate', the search starts first\nfrom the home context of 'self', and if that fails, then it restarts in\n*module*.\" :PUBLIC? TRUE)", ((cpp_function_code)(&symbolToSurrogate)), NULL);
    defineMethodObject("(DEFMETHOD (SURROGATIFY SURROGATE) ((SELF SURROGATE)) :DOCUMENTATION \"Converts 'self' into a surrogate.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Surrogate::surrogatify))), NULL);
    defineMethodObject("(DEFMETHOD (SURROGATIFY SURROGATE) ((SELF SYMBOL)) :PUBLIC? TRUE :DOCUMENTATION \"Converts 'self' into a surrogate (same semantics\nas `symbol-to-surrogate' which see).\")", wrapMethodCode(((cpp_method_code)(&Symbol::surrogatify))), NULL);
    defineMethodObject("(DEFMETHOD (SURROGATIFY SURROGATE) ((SELF STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Converts 'self' into a surrogate.\")", wrapFunctionCode(((cpp_function_code)(((Surrogate*  (*) (const char*))(&stringSurrogatify))))), NULL);
    defineMethodObject("(DEFMETHOD (SURROGATIFY SURROGATE) ((SELF OBJECT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Object::surrogatify))), NULL);
    defineFunctionObject("TYPIFY", "(DEFUN (TYPIFY TYPE) ((SELF OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&typify)), NULL);
    defineMethodObject("(DEFMETHOD (KEYWORDIFY KEYWORD) ((SELF KEYWORD)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Keyword::keywordify))), NULL);
    defineMethodObject("(DEFMETHOD (KEYWORDIFY KEYWORD) ((SELF GENERALIZED-SYMBOL)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&GeneralizedSymbol::keywordify))), NULL);
    defineMethodObject("(DEFMETHOD (KEYWORDIFY KEYWORD) ((SELF STRING-WRAPPER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StringWrapper::keywordify))), NULL);
    defineMethodObject("(DEFMETHOD (KEYWORDIFY KEYWORD) ((SELF STRING)) :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((Keyword*  (*) (const char*))(&stringKeywordify))))), NULL);
    defineFunctionObject("IN-PLACE-OBJECTS-TO-SYMBOLS", "(DEFUN IN-PLACE-OBJECTS-TO-SYMBOLS ((CONSLIST CONS)))", ((cpp_function_code)(&inPlaceObjectsToSymbols)), NULL);
    defineFunctionObject("IN-PLACE-OBJECTS-TO-TYPES", "(DEFUN IN-PLACE-OBJECTS-TO-TYPES ((CONSLIST CONS)))", ((cpp_function_code)(&inPlaceObjectsToTypes)), NULL);
    defineFunctionObject("SURROGATE-NAME?", "(DEFUN (SURROGATE-NAME? BOOLEAN) ((NAME STRING)) :DOCUMENTATION \"Return TRUE if name is prefixed by 'SURROGATE-PREFIX-CHARACTER'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&surrogateNameP)), NULL);
    defineFunctionObject("KEYWORD-NAME?", "(DEFUN (KEYWORD-NAME? BOOLEAN) ((NAME STRING)) :DOCUMENTATION \"Return TRUE if name is prefixed by ':'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&keywordNameP)), NULL);
    defineFunctionObject("INTERN-STELLA-NAME", "(DEFUN (INTERN-STELLA-NAME GENERALIZED-SYMBOL) ((NAME STRING)) :DOCUMENTATION \"Parse `name' which is assumed to be the printed\nrepresentation of a STELLA symbol, surrogate or keyword, intern\nit into the current or specified module and return the result.\nThis is identical to calling `unstringify' on `name' but 10-15\ntimes faster.\" :PUBLIC? TRUE)", ((cpp_function_code)(&internStellaName)), NULL);
    defineFunctionObject("LOOKUP-STELLA-NAME", "(DEFUN (LOOKUP-STELLA-NAME GENERALIZED-SYMBOL) ((NAME STRING)) :DOCUMENTATION \"Parse `name' which is assumed to be the printed\nrepresentation of a STELLA symbol, surrogate or keyword, and try\nto look it up according to its type.  This is a lookup version of\n`intern-stella-name' (which see) for cases where we don't necessarily\nwant to create a symbol in case it doesn't exist already.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupStellaName)), NULL);
    defineFunctionObject("COMPUTE-FULL-NAME", "(DEFUN (COMPUTE-FULL-NAME STRING) ((NAME STRING) (MODULE MODULE)) :PUBLIC? TRUE)", ((cpp_function_code)(&computeFullName)), NULL);
    defineMethodObject("(DEFMETHOD (LOCAL-PRINT-NAME STRING) ((SELF GENERALIZED-SYMBOL) (READABLE? BOOLEAN)))", wrapMethodCode(((cpp_method_code)(&GeneralizedSymbol::localPrintName))), NULL);
    defineMethodObject("(DEFMETHOD (LOCAL-PRINT-NAME STRING) ((SELF SURROGATE) (READABLE? BOOLEAN)))", wrapMethodCode(((cpp_method_code)(&Surrogate::localPrintName))), NULL);
    defineMethodObject("(DEFMETHOD (RELATIVE-NAME STRING) ((SELF GENERALIZED-SYMBOL) (READABLE? BOOLEAN)))", wrapMethodCode(((cpp_method_code)(&GeneralizedSymbol::relativeName))), NULL);
    defineMethodObject("(DEFMETHOD (ABSOLUTE-NAME STRING) ((SELF GENERALIZED-SYMBOL) (READABLE? BOOLEAN)) :PUBLIC? TRUE :C-CALLABLE? TRUE)", wrapMethodCode(((cpp_method_code)(&GeneralizedSymbol::absoluteName))), NULL);
    defineFunctionObject("VISIBLE-SYMBOL?", "(DEFUN (VISIBLE-SYMBOL? BOOLEAN) ((SELF SYMBOL)) :DOCUMENTATION \"Return `true' if `self' is visible from the current module.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (EQL? SELF (LOOKUP-SYMBOL-IN-MODULE (SYMBOL-NAME SELF) *MODULE* FALSE))))", ((cpp_function_code)(&visibleSymbolP)), NULL);
    defineFunctionObject("VISIBLE-SURROGATE?", "(DEFUN (VISIBLE-SURROGATE? BOOLEAN) ((SELF SURROGATE)) :DOCUMENTATION \"Return `true' if `self' is visible from the current module.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (EQL? SELF (LOOKUP-SURROGATE-IN-MODULE (SYMBOL-NAME SELF) *MODULE* FALSE))))", ((cpp_function_code)(&visibleSurrogateP)), NULL);
    defineMethodObject("(DEFMETHOD (VISIBLE-NAME STRING) ((SELF GENERALIZED-SYMBOL) (READABLE? BOOLEAN)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&GeneralizedSymbol::visibleName))), NULL);
    defineFunctionObject("SYMBOL-VALUE", "(DEFUN (SYMBOL-VALUE OBJECT) ((SYMBOL SYMBOL)) :DOCUMENTATION \"Return the value of `symbol'.  Note, that this value is not\nvisible to code that references a variable with the same name as `symbol'.\nThe `symbol-value' is simply a special property that can always be accessed\nin constant time.  The `symbol-value' of a symbol can be changed with `setf'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VALUE (SYMBOL-VALUE-AND-PLIST SYMBOL))))", ((cpp_function_code)(&symbolValue)), NULL);
    defineFunctionObject("SYMBOL-VALUE-SETTER", "(DEFUN (SYMBOL-VALUE-SETTER OBJECT) ((SYMBOL SYMBOL) (VALUE OBJECT)))", ((cpp_function_code)(&symbolValueSetter)), NULL);
    defineFunctionObject("SYMBOL-PLIST", "(DEFUN (SYMBOL-PLIST CONS) ((SYMBOL SYMBOL)) :DOCUMENTATION \"Return the property list of `symbol'.  The `symbol-plist'\nof a symbol can be set with `setf'.  IMPORTANT: Property list are modified \ndestructively, hence, if you supply it as a whole make sure to always supply\na modfiable copy, e.g., by using `bquote'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (REST (SYMBOL-VALUE-AND-PLIST SYMBOL))))", ((cpp_function_code)(&symbolPlist)), NULL);
    defineFunctionObject("SYMBOL-PLIST-SETTER", "(DEFUN (SYMBOL-PLIST-SETTER CONS) ((SYMBOL SYMBOL) (PLIST CONS)))", ((cpp_function_code)(&symbolPlistSetter)), NULL);
    defineFunctionObject("SYMBOL-PROPERTY", "(DEFUN (SYMBOL-PROPERTY OBJECT) ((SYMBOL SYMBOL) (KEY STANDARD-OBJECT)) :DOCUMENTATION \"Return the property of `symbol' whose key is `eq?' to `key'.\nSymbol properties can be set with `setf'.\")", ((cpp_function_code)(&symbolProperty)), NULL);
    defineFunctionObject("SYMBOL-PROPERTY-SETTER", "(DEFUN (SYMBOL-PROPERTY-SETTER OBJECT) ((SYMBOL SYMBOL) (VALUE OBJECT) (KEY STANDARD-OBJECT)))", ((cpp_function_code)(&symbolPropertySetter)), NULL);
    defineFunctionObject("SYMBOL-CONSTITUENT-CHARACTER?", "(DEFUN (SYMBOL-CONSTITUENT-CHARACTER? BOOLEAN) ((CHARACTER CHARACTER)))", ((cpp_function_code)(&symbolConstituentCharacterP)), NULL);
    defineFunctionObject("INITIALIZE-SYMBOL-ESCAPE-CODE-TABLE", "(DEFUN (INITIALIZE-SYMBOL-ESCAPE-CODE-TABLE STRING) ((CASESENSITIVE? BOOLEAN)))", ((cpp_function_code)(&initializeSymbolEscapeCodeTable)), NULL);
    defineFunctionObject("COMPUTE-SYMBOL-ESCAPE-CODE", "(DEFUN (COMPUTE-SYMBOL-ESCAPE-CODE KEYWORD) ((NAME STRING) (CASESENSITIVE? BOOLEAN)))", ((cpp_function_code)(&computeSymbolEscapeCode)), NULL);
    defineFunctionObject("PRINT-SYMBOL-NAME-READABLY", "(DEFUN PRINT-SYMBOL-NAME-READABLY ((NAME STRING) (STREAM NATIVE-OUTPUT-STREAM) (CASESENSITIVE? BOOLEAN)))", ((cpp_function_code)(&printSymbolNameReadably)), NULL);
    defineFunctionObject("READABLE-SYMBOL-NAME", "(DEFUN (READABLE-SYMBOL-NAME STRING) ((NAME STRING) (CASESENSITIVE? BOOLEAN)) :PUBLIC? TRUE)", ((cpp_function_code)(&readableSymbolName)), NULL);
    defineFunctionObject("PRINT-SYMBOL", "(DEFUN PRINT-SYMBOL ((SELF SYMBOL) (STREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&printSymbol)), NULL);
    defineFunctionObject("PRINT-SURROGATE", "(DEFUN PRINT-SURROGATE ((SELF SURROGATE) (STREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&printSurrogate)), NULL);
    defineFunctionObject("PRINT-KEYWORD", "(DEFUN PRINT-KEYWORD ((SELF KEYWORD) (STREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&printKeyword)), NULL);
    defineFunctionObject("STARTUP-SYMBOLS", "(DEFUN STARTUP-SYMBOLS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupSymbols)), NULL);
    { MethodSlot* function = lookupFunction(SYM_SYMBOLS_STELLA_STARTUP_SYMBOLS);

      setDynamicSlotValue(function->dynamicSlots, SYM_SYMBOLS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupSymbols"), NULL_STRING_WRAPPER);
    }
  }
}

void startupSymbols() {
  if (currentStartupTimePhaseP(0)) {
    if (!((boolean)(oFIXED_SYMBOL_ARRAYo))) {
      initializeSymbolsAndKernelModules();
    }
    initializeParsingTables();
  }
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupSymbols1();
    }
    if (currentStartupTimePhaseP(4)) {
      setDynamicSlotValue(oSTELLA_MODULEo->dynamicSlots, SYM_SYMBOLS_STELLA_JAVA_PACKAGE, wrapString("edu.isi.stella"), NULL_STRING_WRAPPER);
      setDynamicSlotValue(oSTELLA_MODULEo->dynamicSlots, SYM_SYMBOLS_STELLA_MODULE_LISP_PACKAGE, wrapString("STELLA"), NULL_STRING_WRAPPER);
      setDynamicSlotValue(oSTELLA_MODULEo->dynamicSlots, SYM_SYMBOLS_STELLA_MODULE_CPP_PACKAGE, wrapString("stella"), NULL_STRING_WRAPPER);
      setDynamicSlotValue(oROOT_MODULEo->dynamicSlots, SYM_SYMBOLS_STELLA_CODE_ONLYp, TRUE_WRAPPER, FALSE_WRAPPER);
      setDynamicSlotValue(oSTELLA_MODULEo->dynamicSlots, SYM_SYMBOLS_STELLA_CODE_ONLYp, TRUE_WRAPPER, FALSE_WRAPPER);
      setDynamicSlotValue(oCOMMON_LISP_MODULEo->dynamicSlots, SYM_SYMBOLS_STELLA_CODE_ONLYp, TRUE_WRAPPER, FALSE_WRAPPER);
      oSYMBOL_ESCAPE_CODE_TABLEo = initializeSymbolEscapeCodeTable(false);
      oCASE_SENSITIVE_SYMBOL_ESCAPE_CODE_TABLEo = initializeSymbolEscapeCodeTable(true);
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupSymbols2();
      helpStartupSymbols3();
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *SYMBOL-ARRAY* (EXTENSIBLE-SYMBOL-ARRAY OF SYMBOL) NULL :PUBLIC? TRUE)", &oSYMBOL_ARRAYo);
      defineGlobalVariableObject("(DEFGLOBAL *SURROGATE-ARRAY* (EXTENSIBLE-SYMBOL-ARRAY OF SURROGATE) NULL :PUBLIC? TRUE)", &oSURROGATE_ARRAYo);
      defineGlobalVariableObject("(DEFGLOBAL *KEYWORD-ARRAY* (EXTENSIBLE-SYMBOL-ARRAY OF KEYWORD) NULL :PUBLIC? TRUE)", &oKEYWORD_ARRAYo);
      defineGlobalVariableObject("(DEFGLOBAL *KEYWORD-OFFSET-TABLE* STRING-TO-INTEGER-HASH-TABLE NULL)", &oKEYWORD_OFFSET_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *FIXED-SYMBOL-ARRAY* (EXTENSIBLE-SYMBOL-ARRAY OF SYMBOL) NULL)", &oFIXED_SYMBOL_ARRAYo);
      defineGlobalVariableObject("(DEFGLOBAL *FIXED-SURROGATE-ARRAY* (EXTENSIBLE-SYMBOL-ARRAY OF SURROGATE) NULL)", &oFIXED_SURROGATE_ARRAYo);
      defineGlobalVariableObject("(DEFGLOBAL *FIXED-KEYWORD-ARRAY* (EXTENSIBLE-SYMBOL-ARRAY OF KEYWORD) NULL)", &oFIXED_KEYWORD_ARRAYo);
      defineGlobalVariableObject("(DEFGLOBAL *TRANSIENT-SYMBOL-LOOKUP-TABLE* STRING-HASH-TABLE NULL)", &oTRANSIENT_SYMBOL_LOOKUP_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *COMMON-LISP-SYMBOL-LOOKUP-TABLE* STRING-HASH-TABLE NULL)", &oCOMMON_LISP_SYMBOL_LOOKUP_TABLEo);
      defineGlobalVariableObject("(DEFCONSTANT SYMBOL-SYM INTEGER 0)", &SYMBOL_SYM);
      defineGlobalVariableObject("(DEFCONSTANT SURROGATE-SYM INTEGER 1)", &SURROGATE_SYM);
      defineGlobalVariableObject("(DEFCONSTANT KEYWORD-SYM INTEGER 2)", &KEYWORD_SYM);
      defineGlobalVariableObject("(DEFGLOBAL *ROOT-MODULE* MODULE NULL :PUBLIC? TRUE :DOCUMENTATION \"Pointer to the top-most module ROOT-MODULE.\")", &oROOT_MODULEo);
      defineGlobalVariableObject("(DEFGLOBAL *STELLA-MODULE* MODULE NULL :PUBLIC? TRUE :DOCUMENTATION \"Pointer to the module STELLA containing definitions of \nSTELLA classes and methods.\")", &oSTELLA_MODULEo);
      defineGlobalVariableObject("(DEFGLOBAL *COMMON-LISP-MODULE* MODULE NULL :PUBLIC? TRUE :DOCUMENTATION \"Pointer to the module COMMON-LISP containing Common\nLisp symbols (and maybe other things).\")", &oCOMMON_LISP_MODULEo);
      defineGlobalVariableObject("(DEFGLOBAL *ALTERNATE-STELLA-MODULE* MODULE NULL :DOCUMENTATION \"Pointer to the module ALTERNATE-STELLA containing\ndefinitions of STELLA classes and methods generated during the\ntranslation of STELLA files.\")", &oALTERNATE_STELLA_MODULEo);
      defineGlobalVariableObject("(DEFSPECIAL *CONTEXT* CONTEXT :UNBOUND-SPECIAL-VARIABLE :DOCUMENTATION \"Points to the current context (either a module or a\nworld).  Set by calls to `change-world' and `change-module'.\" :PUBLIC? TRUE)", &oCONTEXTo);
      defineGlobalVariableObject("(DEFSPECIAL *MODULE* MODULE :UNBOUND-SPECIAL-VARIABLE :DOCUMENTATION \"Points to the current module.  Set by calls to\n`change-context' and `change-module'.\" :PUBLIC? TRUE)", &oMODULEo);
      defineGlobalVariableObject("(DEFCONSTANT SURROGATE-PREFIX-CHARACTER CHARACTER #\\@ :DOCUMENTATION \"Character used to prefix the name of a surrogate.\")", &SURROGATE_PREFIX_CHARACTER);
      defineGlobalVariableObject("(DEFCONSTANT MODULE-SEPARATOR-CHARACTER CHARACTER #\\/ :DOCUMENTATION \"Character used to concatenate a module name\nto a symbol or surrogate name to form a qualified name.\")", &MODULE_SEPARATOR_CHARACTER);
      defineGlobalVariableObject("(DEFCONSTANT MODULE-SEPARATOR-STRING STRING \"/\" :DOCUMENTATION \"String containing character used to concatenate a module name\nto a symbol or surrogate name to form a qualified name.\")", &MODULE_SEPARATOR_STRING);
      defineGlobalVariableObject("(DEFGLOBAL *CONTEXT-NUMBER-COUNTER* INTEGER -2 :DOCUMENTATION \"Contains the number of the last-created\ncontext (all 'live' contexts are even-numbered).\")", &oCONTEXT_NUMBER_COUNTERo);
      defineGlobalVariableObject("(DEFGLOBAL *GENSYM-COUNTER* INTEGER 0 :DOCUMENTATION \"Incremented once for each gensym call.\")", &oGENSYM_COUNTERo);
      defineGlobalVariableObject("(DEFGLOBAL *GENSYM-MASK* STRING \"-000\" :DOCUMENTATION \"Defines the separator character for gensyms,\nand the fill digits.\")", &oGENSYM_MASKo);
      defineGlobalVariableObject("(DEFGLOBAL *SYMBOL-ESCAPE-CODE-TABLE* STRING (INITIALIZE-SYMBOL-ESCAPE-CODE-TABLE FALSE))", &oSYMBOL_ESCAPE_CODE_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *CASE-SENSITIVE-SYMBOL-ESCAPE-CODE-TABLE* STRING (INITIALIZE-SYMBOL-ESCAPE-CODE-TABLE TRUE))", &oCASE_SENSITIVE_SYMBOL_ESCAPE_CODE_TABLEo);
    }
  }
}

Symbol* SYM_SYMBOLS_STELLA_MODULE_LISP_PACKAGE = NULL;

Symbol* SYM_SYMBOLS_STELLA_JAVA_PACKAGE = NULL;

Symbol* SYM_SYMBOLS_STELLA_MODULE_CPP_PACKAGE = NULL;

Symbol* SYM_SYMBOLS_STELLA_CODE_ONLYp = NULL;

Keyword* KWD_SYMBOLS_SYMBOL = NULL;

Keyword* KWD_SYMBOLS_SURROGATE = NULL;

Keyword* KWD_SYMBOLS_KEYWORD = NULL;

Keyword* KWD_SYMBOLS_LETTER = NULL;

Keyword* KWD_SYMBOLS_DIGIT = NULL;

Keyword* KWD_SYMBOLS_SYMBOL_CONSTITUENT = NULL;

Keyword* KWD_SYMBOLS_ESCAPED = NULL;

Keyword* KWD_SYMBOLS_UNESCAPED = NULL;

Keyword* KWD_SYMBOLS_COMPLEX_ESCAPED = NULL;

Symbol* SYM_SYMBOLS_STELLA_STARTUP_SYMBOLS = NULL;

Symbol* SYM_SYMBOLS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
