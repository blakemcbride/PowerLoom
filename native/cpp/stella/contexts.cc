//  -*- Mode: C++ -*-

// contexts.cc

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

// Eliminate pointers to discarded contexts while
// accessing a CS-VALUE context table.
boolean oUNLINK_DISCARDED_CONTEXTS_ON_READpo = true;

// Eliminate pointers to discarded contexts while
// inserting into a CS-VALUE context table.
boolean oUNLINK_DISCARDED_CONTEXTS_ON_WRITEpo = true;

// If true, indicates that contexts are being allocated
// and deallocated in depth-first fashion, and that deallocation of
// CS-VALUE entries is taken care of during context destruction.
boolean oCONTEXT_BACKTRACKING_MODEo = false;

boolean csValueP(Object* self) {
  return (((boolean)(self)) &&
      (self->primaryType() == SGT_CONTEXTS_STELLA_CS_VALUE));
}

boolean subcontextP(Context* subcontext, Context* supercontext) {
  return ((subcontext == supercontext) ||
      subcontext->allSuperContexts->membP(supercontext));
}

boolean discardedContextP(Context* context) {
  return (((context->contextNumber) % 2));
}

boolean Context::deletedP() {
  { Context* context = this;

    return (((context->contextNumber) % 2));
  }
}

Context* helpFindContextByNumber(int number, List* siblings) {
  { Context* c = NULL;
    Cons* iter000 = siblings->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      c = ((Context*)(iter000->value));
      if (c->contextNumber == number) {
        return (c);
      }
      else if (c->contextNumber < number) {
        return (helpFindContextByNumber(number, c->childContexts));
      }
      else {
        continue;
      }
    }
  }
  { OutputStringStream* stream000 = newOutputStringStream();

    *(stream000->nativeStream) << "Couldn't find context with number " << "`" << number << "'";
    throw *newNoSuchContextException(stream000->theStringReader());
  }
}

Context* findContextByNumber(int contextnumber) {
  return (helpFindContextByNumber(contextnumber, oROOT_MODULEo->childContexts));
}

Context* stringGetStellaContextSlowly(const char* self) {
  { Context* context = NULL;

    { Context* cxt = NULL;
      Cons* iter000 = oROOT_MODULEo->childContexts->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        cxt = ((Context*)(iter000->value));
        if (stringEqlP(cxt->contextName(), self)) {
          return (cxt);
        }
      }
    }
    { Context* cxt = NULL;
      Iterator* iter001 = allContexts();

      for (; iter001->nextP(); ) {
        cxt = ((Context*)(iter001->value));
        if (stringEqlP(cxt->contextName(), self) ||
            (isaP(cxt, SGT_CONTEXTS_STELLA_MODULE) &&
             (((boolean)(((Module*)(cxt))->nicknames)) &&
              ((Module*)(cxt))->nicknames->memberP(wrapString(self))))) {
          if (((boolean)(context))) {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "More than one context has the name or nickname " << "`" << self << "'" << ": " << "`" << context << "'" << " and " << "`" << cxt << "'";
              throw *newNoSuchContextException(stream000->theStringReader());
            }
          }
          context = cxt;
        }
      }
    }
    if (((boolean)(context))) {
      return (context);
    }
    else {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "No context with name or nickname " << "`" << self << "'";
        throw *newNoSuchContextException(stream001->theStringReader());
      }
    }
  }
}

Context* integerGetStellaContextSlowly(int self) {
  return (findContextByNumber(self));
}

Context* Symbol::getStellaContextSlowly() {
  { Symbol* self = this;

    return (stringGetStellaContextSlowly(self->relativeName(false)));
  }
}

Context* changeContextSlowly(Context* self) {
  if (((boolean)(self))) {
    return (self->changeContext());
  }
  else {
    return (oCONTEXTo);
  }
}

Context* cc(Cons* name) {
  // Change the current context to the one named `name'.  Return the
  // value of the new current context.  If no `name' is supplied, return
  // the pre-existing value of the current context.  `cc' is a no-op if the
  // context reference cannot be successfully evaluated.
  { Context* context = oCONTEXTo;
    Object* namespec = name->value;

    if (((boolean)(namespec))) {
      { Surrogate* testValue000 = safePrimaryType(namespec);

        if (subtypeOfIntegerP(testValue000)) {
          { Object* namespec000 = namespec;
            IntegerWrapper* namespec = ((IntegerWrapper*)(namespec000));

            context = integerGetStellaContextSlowly(((int)(namespec->wrapperValue)));
          }
        }
        else if (subtypeOfLongIntegerP(testValue000)) {
          { Object* namespec001 = namespec;
            LongIntegerWrapper* namespec = ((LongIntegerWrapper*)(namespec001));

            context = integerGetStellaContextSlowly(((int)(namespec->wrapperValue)));
          }
        }
        else {
          { const char* contextname = coerceToModuleName(namespec, true);

            if (contextname != NULL) {
              context = getStellaContext(contextname, true);
            }
          }
        }
      }
    }
    return (changeContextSlowly(context));
  }
}

Context* ccEvaluatorWrapper(Cons* arguments) {
  return (cc(arguments));
}

Context* ccc(Cons* name) {
  // Change the current context to the one named `name'.  Return the
  // value of the new current context.  If no `name' is supplied, return
  // the pre-existing value of the current context.  `cc' is a no-op if the
  // context reference cannot be successfully evaluated.
  // In CommonLisp, if the new context is case sensitive, then change
  // the readtable case to the value of CL-USER::*STELLA-CASE-SENSITIVE-READ-MODE*
  // [default = :INVERT], otherwise to :UPCASE.
  { Context* context = oCONTEXTo;
    Object* namespec = name->value;
    boolean casesensitiveP = context->baseModule->caseSensitiveP;

    if (((boolean)(namespec))) {
      { Surrogate* testValue000 = safePrimaryType(namespec);

        if (subtypeOfIntegerP(testValue000)) {
          { Object* namespec000 = namespec;
            IntegerWrapper* namespec = ((IntegerWrapper*)(namespec000));

            context = integerGetStellaContextSlowly(((int)(namespec->wrapperValue)));
          }
        }
        else if (subtypeOfLongIntegerP(testValue000)) {
          { Object* namespec001 = namespec;
            LongIntegerWrapper* namespec = ((LongIntegerWrapper*)(namespec001));

            context = integerGetStellaContextSlowly(((int)(namespec->wrapperValue)));
          }
        }
        else {
          { const char* contextname = coerceToModuleName(namespec, true);

            if (contextname != NULL) {
              context = getStellaContext(contextname, true);
              casesensitiveP = context->baseModule->caseSensitiveP;
            }
          }
        }
      }
    }
    return (changeContextSlowly(context));
  }
}

Context* cccEvaluatorWrapper(Cons* arguments) {
  return (ccc(arguments));
}

void printContext(Context* self, std::ostream* stream) {
  { const char* typestring = NULL;
    const char* name = NULL;
    int number = self->contextNumber;

    if (!oCLASS_HIERARCHY_BOOTEDpo) {
      *(stream) << "|MDL|" << ((Module*)(self))->moduleName;
      return;
    }
    { Surrogate* testValue000 = safePrimaryType(self);

      if (subtypeOfP(testValue000, SGT_CONTEXTS_STELLA_MODULE)) {
        { Context* self000 = self;
          Module* self = ((Module*)(self000));

          name = self->moduleFullName;
          if (((self->contextNumber) % 2)) {
            typestring = "|DeLeTeD MDL|";
          }
          else {
            typestring = "|MDL|";
          }
        }
      }
      else if (subtypeOfP(testValue000, SGT_CONTEXTS_STELLA_WORLD)) {
        { Context* self001 = self;
          World* self = ((World*)(self001));

          name = ((StringWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_CONTEXTS_STELLA_WORLD_NAME, NULL_STRING_WRAPPER)))->wrapperValue;
          if (((self->contextNumber) % 2)) {
            typestring = "|DeLeTeD WLD|";
          }
          else {
            typestring = "|WLD|";
          }
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    if (((self->contextNumber) % 2)) {
      number = number + 1;
    }
    if (oPRINTREADABLYpo) {
      if (name != NULL) {
        *(stream) << name;
      }
      else {
        *(stream) << "#<" << typestring << number << ">";
      }
    }
    else {
      if (name != NULL) {
        *(stream) << typestring << name;
      }
      else {
        *(stream) << typestring << number;
      }
    }
  }
}

void helpPrintContextTree(List* list, int level) {
  { Context* c = NULL;
    Cons* iter000 = list->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      c = ((Context*)(iter000->value));
      std::cout << std::endl;
      { int i = NULL_INTEGER;
        int iter001 = 1;
        int upperBound000 = level;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter001 <= upperBound000); 
              iter001 = iter001 + 1) {
          i = iter001;
          i = i;
          std::cout << "   ";
        }
      }
      std::cout << c->contextNumber;
      if (c->contextName() != NULL) {
        std::cout << "   " << c->contextName();
      }
      std::cout << std::endl;
      helpPrintContextTree(c->childContexts, level + 1);
    }
  }
}

void printContextTree(Context* root) {
  if (!((boolean)(root))) {
    root = oROOT_MODULEo;
  }
  { List* toplist = list(1, root);

    helpPrintContextTree(toplist, 0);
    toplist->free();
  }
}

Object* accessInContext(Object* value, Context* homecontext, boolean dontinheritP) {
  if ((!((boolean)(value))) ||
      (!(((boolean)(value)) &&
      (value->primaryType() == SGT_CONTEXTS_STELLA_CS_VALUE)))) {
    if (dontinheritP) {
      if (oCONTEXTo == homecontext) {
        return (value);
      }
    }
    else {
      if ((!((boolean)(homecontext))) ||
          (((oCONTEXTo == homecontext) ||
          oCONTEXTo->allSuperContexts->membP(homecontext)) ||
           (isaP(homecontext, SGT_CONTEXTS_STELLA_MODULE) &&
            visibleFromP(homecontext, oMODULEo)))) {
        return (value);
      }
    }
    return (NULL);
  }
  { KvCons* kvcons = ((CsValue*)(value))->theKvList;
    int contextnumber = NULL_INTEGER;

    { Context* target = oCONTEXTo;

      contextnumber = target->contextNumber;
      while (((boolean)(kvcons)) &&
          (contextnumber < ((Context*)(kvcons->key))->contextNumber)) {
        if (((((Context*)(kvcons->key))->contextNumber) % 2) &&
            ((!oCONTEXT_BACKTRACKING_MODEo) &&
             oUNLINK_DISCARDED_CONTEXTS_ON_READpo)) {
          if (((boolean)(kvcons->rest))) {
            { KvCons* nextkvcons = kvcons->rest;

              kvcons->key = nextkvcons->key;
              kvcons->value = nextkvcons->value;
              kvcons->rest = nextkvcons->rest;
              nextkvcons->free();
            }
          }
          else {
            {
              ((CsValue*)(value))->removeAt(((Context*)(kvcons->key)));
              return (NULL);
            }
          }
        }
        else {
          kvcons = kvcons->rest;
        }
      }
      if (!((boolean)(kvcons))) {
        return (NULL);
      }
      if (target == kvcons->key) {
        return (kvcons->value);
      }
      if (dontinheritP) {
        return (NULL);
      }
    }
    { Context* target = NULL;
      Cons* iter000 = oCONTEXTo->allSuperContexts;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        target = ((Context*)(iter000->value));
        contextnumber = target->contextNumber;
        while (((boolean)(kvcons)) &&
            (contextnumber < ((Context*)(kvcons->key))->contextNumber)) {
          if (((((Context*)(kvcons->key))->contextNumber) % 2) &&
              ((!oCONTEXT_BACKTRACKING_MODEo) &&
               oUNLINK_DISCARDED_CONTEXTS_ON_READpo)) {
            if (((boolean)(kvcons->rest))) {
              { KvCons* nextkvcons = kvcons->rest;

                kvcons->key = nextkvcons->key;
                kvcons->value = nextkvcons->value;
                kvcons->rest = nextkvcons->rest;
                nextkvcons->free();
              }
            }
            else {
              {
                ((CsValue*)(value))->removeAt(((Context*)(kvcons->key)));
                return (NULL);
              }
            }
          }
          else {
            kvcons = kvcons->rest;
          }
        }
        if (!((boolean)(kvcons))) {
          return (NULL);
        }
        if (target == kvcons->key) {
          return (kvcons->value);
        }
        if (dontinheritP) {
          return (NULL);
        }
      }
    }
    return (NULL);
  }
}

void helpInsertACsValue(KvCons* kvcons, Object* newvalue, Context* target, boolean overwriteP) {
  { int contextnumber = target->contextNumber;

    for (;;) {
      if ((!oCONTEXT_BACKTRACKING_MODEo) &&
          (oUNLINK_DISCARDED_CONTEXTS_ON_WRITEpo &&
           ((((Context*)(kvcons->key))->contextNumber) % 2))) {
        if (((boolean)(kvcons->rest))) {
          { KvCons* nextkvcons = kvcons->rest;

            kvcons->key = nextkvcons->key;
            kvcons->value = nextkvcons->value;
            kvcons->rest = nextkvcons->rest;
            nextkvcons->free();
          }
        }
        else {
          {
            kvcons->key = target;
            kvcons->value = newvalue;
            return;
          }
        }
      }
      if (kvcons->key == target) {
        if (overwriteP) {
          kvcons->value = newvalue;
        }
        return;
      }
      else if (((Context*)(kvcons->key))->contextNumber < contextnumber) {
        kvcons->rest = kvCons(kvcons->key, kvcons->value, kvcons->rest);
        kvcons->key = target;
        kvcons->value = newvalue;
        return;
      }
      else if (!((boolean)(kvcons->rest))) {
        kvcons->rest = kvCons(target, newvalue, NULL);
        return;
      }
      else {
        kvcons = kvcons->rest;
      }
    }
  }
}

void CsValue::insertAt(Context* context, Object* newvalue) {
  { CsValue* self = this;

    if (!((boolean)(self->theKvList))) {
      { KvCons* kvcons = newKvCons();

        kvcons->key = context;
        kvcons->value = newvalue;
        self->theKvList = kvcons;
        return;
      }
    }
    helpInsertACsValue(self->theKvList, newvalue, context, true);
  }
}

Object* updateInContext(Object* oldvalue, Object* newvalue, Context* homecontext, boolean copytochildrenP) {
  { CsValue* csvalue = NULL;

    if (((boolean)(oldvalue)) &&
        (oldvalue->primaryType() == SGT_CONTEXTS_STELLA_CS_VALUE)) {
      csvalue = ((CsValue*)(oldvalue));
    }
    else {
      if ((homecontext == oCONTEXTo) &&
          (oCONTEXTo->childContexts->emptyP() ||
           (!copytochildrenP))) {
        return (newvalue);
      }
      else {
        {
          csvalue = newCsValue();
          if (((boolean)(oldvalue))) {
            csvalue->insertAt(homecontext, oldvalue);
          }
        }
      }
    }
    csvalue->insertAt(oCONTEXTo, newvalue);
    if (copytochildrenP) {
      copyCurrentValueToChildren(csvalue, homecontext, newvalue);
    }
    return (csvalue);
  }
}

void copyCurrentValueToChildren(CsValue* csvalue, Context* homecontext, Object* parentvalue) {
  { Context* childcxt = NULL;
    Cons* iter000 = oCONTEXTo->childContexts->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      childcxt = ((Context*)(iter000->value));
      { 
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, childcxt);
        { Object* currentvalue = accessInContext(csvalue, homecontext, false);

          if (!eqlP(currentvalue, parentvalue)) {
            helpInsertACsValue(csvalue->theKvList, currentvalue, childcxt, false);
          }
        }
      }
    }
  }
}

void startupContexts() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SGT_CONTEXTS_STELLA_CS_VALUE = ((Surrogate*)(internRigidSymbolWrtModule("CS-VALUE", NULL, 1)));
      SGT_CONTEXTS_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", NULL, 1)));
      SGT_CONTEXTS_STELLA_WORLD = ((Surrogate*)(internRigidSymbolWrtModule("WORLD", NULL, 1)));
      SYM_CONTEXTS_STELLA_WORLD_NAME = ((Symbol*)(internRigidSymbolWrtModule("WORLD-NAME", NULL, 0)));
      SYM_CONTEXTS_STELLA_STARTUP_CONTEXTS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-CONTEXTS", NULL, 0)));
      SYM_CONTEXTS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("CS-VALUE?", "(DEFUN (CS-VALUE? BOOLEAN) ((SELF OBJECT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (AND (DEFINED? SELF) (EQL? (PRIMARY-TYPE SELF) @CS-VALUE))))", ((cpp_function_code)(&csValueP)), NULL);
      defineFunctionObject("SUBCONTEXT?", "(DEFUN (SUBCONTEXT? BOOLEAN) ((SUBCONTEXT CONTEXT) (SUPERCONTEXT CONTEXT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (OR (EQL? SUBCONTEXT SUPERCONTEXT) (MEMB? (ALL-SUPER-CONTEXTS SUBCONTEXT) SUPERCONTEXT))))", ((cpp_function_code)(&subcontextP)), NULL);
      defineFunctionObject("DISCARDED-CONTEXT?", "(DEFUN (DISCARDED-CONTEXT? BOOLEAN) ((CONTEXT CONTEXT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (ODD? (CONTEXT-NUMBER CONTEXT))))", ((cpp_function_code)(&discardedContextP)), NULL);
      defineMethodObject("(DEFMETHOD (DELETED? BOOLEAN) ((CONTEXT CONTEXT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Context::deletedP))), NULL);
      defineFunctionObject("HELP-FIND-CONTEXT-BY-NUMBER", "(DEFUN (HELP-FIND-CONTEXT-BY-NUMBER CONTEXT) ((NUMBER INTEGER) (SIBLINGS (LIST OF CONTEXT))))", ((cpp_function_code)(&helpFindContextByNumber)), NULL);
      defineFunctionObject("FIND-CONTEXT-BY-NUMBER", "(DEFUN (FIND-CONTEXT-BY-NUMBER CONTEXT) ((CONTEXTNUMBER INTEGER)))", ((cpp_function_code)(&findContextByNumber)), NULL);
      defineMethodObject("(DEFMETHOD (GET-STELLA-CONTEXT-SLOWLY CONTEXT) ((SELF STRING)))", wrapFunctionCode(((cpp_function_code)(((Context*  (*) (const char*))(&stringGetStellaContextSlowly))))), NULL);
      defineMethodObject("(DEFMETHOD (GET-STELLA-CONTEXT-SLOWLY CONTEXT) ((SELF INTEGER)))", wrapFunctionCode(((cpp_function_code)(((Context*  (*) (int))(&integerGetStellaContextSlowly))))), NULL);
      defineMethodObject("(DEFMETHOD (GET-STELLA-CONTEXT-SLOWLY CONTEXT) ((SELF SYMBOL)))", wrapMethodCode(((cpp_method_code)(&Symbol::getStellaContextSlowly))), NULL);
      defineFunctionObject("CHANGE-CONTEXT-SLOWLY", "(DEFUN (CHANGE-CONTEXT-SLOWLY CONTEXT) ((SELF CONTEXT)))", ((cpp_function_code)(&changeContextSlowly)), NULL);
      defineFunctionObject("CC", "(DEFUN (CC CONTEXT) (|&REST| (NAME NAME)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Change the current context to the one named `name'.  Return the\nvalue of the new current context.  If no `name' is supplied, return\nthe pre-existing value of the current context.  `cc' is a no-op if the\ncontext reference cannot be successfully evaluated.\")", ((cpp_function_code)(&cc)), ((cpp_function_code)(&ccEvaluatorWrapper)));
      defineFunctionObject("CCC", "(DEFUN (CCC CONTEXT) (|&REST| (NAME NAME)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Change the current context to the one named `name'.  Return the\nvalue of the new current context.  If no `name' is supplied, return\nthe pre-existing value of the current context.  `cc' is a no-op if the\ncontext reference cannot be successfully evaluated.\nIn CommonLisp, if the new context is case sensitive, then change\nthe readtable case to the value of CL-USER::*STELLA-CASE-SENSITIVE-READ-MODE*\n[default = :INVERT], otherwise to :UPCASE.\")", ((cpp_function_code)(&ccc)), ((cpp_function_code)(&cccEvaluatorWrapper)));
      defineFunctionObject("PRINT-CONTEXT", "(DEFUN PRINT-CONTEXT ((SELF CONTEXT) (STREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&printContext)), NULL);
      defineFunctionObject("HELP-PRINT-CONTEXT-TREE", "(DEFUN HELP-PRINT-CONTEXT-TREE ((LIST (LIST OF CONTEXT)) (LEVEL INTEGER)))", ((cpp_function_code)(&helpPrintContextTree)), NULL);
      defineFunctionObject("PRINT-CONTEXT-TREE", "(DEFUN PRINT-CONTEXT-TREE ((ROOT CONTEXT)))", ((cpp_function_code)(&printContextTree)), NULL);
      defineFunctionObject("ACCESS-IN-CONTEXT", "(DEFUN (ACCESS-IN-CONTEXT OBJECT) ((VALUE OBJECT) (HOMECONTEXT CONTEXT) (DONTINHERIT? BOOLEAN)) :PUBLIC? TRUE)", ((cpp_function_code)(&accessInContext)), NULL);
      defineFunctionObject("HELP-INSERT-A-CS-VALUE", "(DEFUN HELP-INSERT-A-CS-VALUE ((KVCONS KV-CONS) (NEWVALUE OBJECT) (TARGET CONTEXT) (OVERWRITE? BOOLEAN)))", ((cpp_function_code)(&helpInsertACsValue)), NULL);
      defineMethodObject("(DEFMETHOD INSERT-AT ((SELF CS-VALUE) (CONTEXT CONTEXT) (NEWVALUE OBJECT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&CsValue::insertAt))), NULL);
      defineFunctionObject("UPDATE-IN-CONTEXT", "(DEFUN (UPDATE-IN-CONTEXT OBJECT) ((OLDVALUE OBJECT) (NEWVALUE OBJECT) (HOMECONTEXT CONTEXT) (COPYTOCHILDREN? BOOLEAN)) :PUBLIC? TRUE)", ((cpp_function_code)(&updateInContext)), NULL);
      defineFunctionObject("COPY-CURRENT-VALUE-TO-CHILDREN", "(DEFUN COPY-CURRENT-VALUE-TO-CHILDREN ((CSVALUE CS-VALUE) (HOMECONTEXT CONTEXT) (PARENTVALUE OBJECT)))", ((cpp_function_code)(&copyCurrentValueToChildren)), NULL);
      defineFunctionObject("STARTUP-CONTEXTS", "(DEFUN STARTUP-CONTEXTS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupContexts)), NULL);
      { MethodSlot* function = lookupFunction(SYM_CONTEXTS_STELLA_STARTUP_CONTEXTS);

        setDynamicSlotValue(function->dynamicSlots, SYM_CONTEXTS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupContexts"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *UNLINK-DISCARDED-CONTEXTS-ON-READ?* BOOLEAN TRUE :DOCUMENTATION \"Eliminate pointers to discarded contexts while\naccessing a CS-VALUE context table.\")", &oUNLINK_DISCARDED_CONTEXTS_ON_READpo);
      defineGlobalVariableObject("(DEFGLOBAL *UNLINK-DISCARDED-CONTEXTS-ON-WRITE?* BOOLEAN TRUE :DOCUMENTATION \"Eliminate pointers to discarded contexts while\ninserting into a CS-VALUE context table.\")", &oUNLINK_DISCARDED_CONTEXTS_ON_WRITEpo);
      defineGlobalVariableObject("(DEFGLOBAL *CONTEXT-BACKTRACKING-MODE* BOOLEAN FALSE :DOCUMENTATION \"If true, indicates that contexts are being allocated\nand deallocated in depth-first fashion, and that deallocation of\nCS-VALUE entries is taken care of during context destruction.\")", &oCONTEXT_BACKTRACKING_MODEo);
    }
  }
}

Surrogate* SGT_CONTEXTS_STELLA_CS_VALUE = NULL;

Surrogate* SGT_CONTEXTS_STELLA_MODULE = NULL;

Surrogate* SGT_CONTEXTS_STELLA_WORLD = NULL;

Symbol* SYM_CONTEXTS_STELLA_WORLD_NAME = NULL;

Symbol* SYM_CONTEXTS_STELLA_STARTUP_CONTEXTS = NULL;

Symbol* SYM_CONTEXTS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
