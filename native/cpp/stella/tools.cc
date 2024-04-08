//  -*- Mode: C++ -*-

// tools.cc

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

// String used in the PRINT-OUTLINE for each level of outline
const char* oOUTLINE_INDENT_STRINGo = "| ";

boolean outlineDepthExceededP(int currentDepth, int depthLimit) {
  // Helper function that returns `true' if `current-depth' exceeds `depth-limit'.
  // This functions uses the convention that a `null' or negative value of
  // `depth-limit' means the depth is unlimited.  In those cases it always
  // returns false.
  return ((depthLimit != NULL_INTEGER) &&
      ((depthLimit >= 0) &&
       (currentDepth >= depthLimit)));
}

void indentOutline(int currentDepth, OutputStream* stream) {
  // Helper function that indents outline printings for level
  // `current-depth' on `stream' using the value of the global
  // variable `*OUTLINE-INDENT-STRING*'
  { int i = NULL_INTEGER;
    int iter000 = 1;
    int upperBound000 = currentDepth;
    boolean unboundedP000 = upperBound000 == NULL_INTEGER;

    for  (; unboundedP000 ||
              (iter000 <= upperBound000); 
          iter000 = iter000 + 1) {
      i = iter000;
      i = i;
      *(stream->nativeStream) << oOUTLINE_INDENT_STRINGo;
    }
  }
}

void printOutline(Object* thing, OutputStream* stream, int depth, boolean namedP) {
  // Print an outline of `thing' and its subparts on `stream'.
  // If `depth' is non-negative, only `depth' levels will be printed.
  // If `named?' is `TRUE', then only named entities will be printed.
  // 
  // This function is intended to be used on things like modules, contexts,
  // concepts, etc. that have hierarchical structure.  If `thing' doesn't
  // have a hierarchical structure, it will just be printed.
  thing->helpPrintOutline(stream, 0, depth, namedP);
}

void printOutlineEvaluatorWrapper(Cons* arguments) {
  printOutline(arguments->value, ((OutputStream*)(arguments->rest->value)), ((IntegerWrapper*)(arguments->rest->rest->value))->wrapperValue, ((BooleanWrapper*)(arguments->rest->rest->rest->value))->wrapperValue);
}

void Object::helpPrintOutline(OutputStream* stream, int currentDepth, int depth, boolean namedP) {
  // Helper method for `print-outline'
  { Object* top = this;

    {
      namedP = namedP;
      currentDepth = currentDepth;
      depth = depth;
    }
    *(stream->nativeStream) << top << std::endl;
  }
}

void Context::helpPrintOutline(OutputStream* stream, int currentDepth, int depth, boolean namedP) {
  // Helper method for `print-outline'
  { Context* top = this;

    if (namedP) {
      return;
    }
    indentOutline(currentDepth, stream);
    *(stream->nativeStream) << top << std::endl;
    if (!((depth != NULL_INTEGER) &&
        ((depth >= 0) &&
         (currentDepth >= depth)))) {
      currentDepth = currentDepth + 1;
      { Context* c = NULL;
        Cons* iter000 = top->childContexts->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          c = ((Context*)(iter000->value));
          c->helpPrintOutline(stream, currentDepth, depth, namedP);
        }
      }
    }
  }
}

void Module::helpPrintOutline(OutputStream* stream, int currentDepth, int depth, boolean namedP) {
  // Helper method for `print-outline'
  { Module* top = this;

    indentOutline(currentDepth, stream);
    *(stream->nativeStream) << top->name() << std::endl;
    if (!((depth != NULL_INTEGER) &&
        ((depth >= 0) &&
         (currentDepth >= depth)))) {
      currentDepth = currentDepth + 1;
      { Context* c = NULL;
        Cons* iter000 = top->childContexts->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          c = ((Context*)(iter000->value));
          c->helpPrintOutline(stream, currentDepth, depth, namedP);
        }
      }
    }
  }
}

void Class::helpPrintOutline(OutputStream* stream, int currentDepth, int depth, boolean namedP) {
  // Helper method for `print-outline'
  { Class* top = this;

    indentOutline(currentDepth, stream);
    *(stream->nativeStream) << top->name() << std::endl;
    if (!((depth != NULL_INTEGER) &&
        ((depth >= 0) &&
         (currentDepth >= depth)))) {
      currentDepth = currentDepth + 1;
      { Surrogate* c = NULL;
        Cons* iter000 = top->classDirectSubs->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          c = ((Surrogate*)(iter000->value));
          typeToClass(c)->helpPrintOutline(stream, currentDepth, depth, namedP);
        }
      }
    }
  }
}

void Slot::helpPrintOutline(OutputStream* stream, int currentDepth, int depth, boolean namedP) {
  // Helper method for `print-outline'
  { Slot* top = this;

    indentOutline(currentDepth, stream);
    *(stream->nativeStream) << top->name() << std::endl;
    if (!((depth != NULL_INTEGER) &&
        ((depth >= 0) &&
         (currentDepth >= depth)))) {
      currentDepth = currentDepth + 1;
      { Slot* c = NULL;
        Cons* iter000 = top->slotDirectSubs_reader()->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          c = ((Slot*)(iter000->value));
          c->helpPrintOutline(stream, currentDepth, depth, namedP);
        }
      }
    }
  }
}

void startupTools() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SYM_TOOLS_STELLA_STARTUP_TOOLS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-TOOLS", NULL, 0)));
      SYM_TOOLS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("OUTLINE-DEPTH-EXCEEDED?", "(DEFUN (OUTLINE-DEPTH-EXCEEDED? BOOLEAN) ((CURRENT-DEPTH INTEGER) (DEPTH-LIMIT INTEGER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Helper function that returns `true' if `current-depth' exceeds `depth-limit'.\nThis functions uses the convention that a `null' or negative value of\n`depth-limit' means the depth is unlimited.  In those cases it always\nreturns false.\" (RETURN (AND (DEFINED? DEPTH-LIMIT) (>= DEPTH-LIMIT 0) (>= CURRENT-DEPTH DEPTH-LIMIT))))", ((cpp_function_code)(&outlineDepthExceededP)), NULL);
      defineFunctionObject("INDENT-OUTLINE", "(DEFUN INDENT-OUTLINE ((CURRENT-DEPTH INTEGER) (STREAM OUTPUT-STREAM)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Helper function that indents outline printings for level\n`current-depth' on `stream' using the value of the global\nvariable `*OUTLINE-INDENT-STRING*'\" (FOREACH I IN (INTERVAL 1 CURRENT-DEPTH) DO (IGNORE I) (PRINT-STREAM STREAM *OUTLINE-INDENT-STRING*)))", ((cpp_function_code)(&indentOutline)), NULL);
      defineFunctionObject("PRINT-OUTLINE", "(DEFUN PRINT-OUTLINE ((THING OBJECT) (STREAM OUTPUT-STREAM) (DEPTH INTEGER) (NAMED? BOOLEAN)) :PUBLIC? TRUE :COMMAND? TRUE :DOCUMENTATION \"Print an outline of `thing' and its subparts on `stream'.\nIf `depth' is non-negative, only `depth' levels will be printed.\nIf `named?' is `TRUE', then only named entities will be printed.\n\nThis function is intended to be used on things like modules, contexts,\nconcepts, etc. that have hierarchical structure.  If `thing' doesn't\nhave a hierarchical structure, it will just be printed.\")", ((cpp_function_code)(&printOutline)), ((cpp_function_code)(&printOutlineEvaluatorWrapper)));
      defineMethodObject("(DEFMETHOD HELP-PRINT-OUTLINE ((TOP OBJECT) (STREAM OUTPUT-STREAM) (CURRENT-DEPTH INTEGER) (DEPTH INTEGER) (NAMED? BOOLEAN)) :PUBLIC? TRUE :DOCUMENTATION \"Helper method for `print-outline'\")", wrapMethodCode(((cpp_method_code)(&Object::helpPrintOutline))), NULL);
      defineMethodObject("(DEFMETHOD HELP-PRINT-OUTLINE ((TOP CONTEXT) (STREAM OUTPUT-STREAM) (CURRENT-DEPTH INTEGER) (DEPTH INTEGER) (NAMED? BOOLEAN)) :PUBLIC? TRUE :DOCUMENTATION \"Helper method for `print-outline'\")", wrapMethodCode(((cpp_method_code)(&Context::helpPrintOutline))), NULL);
      defineMethodObject("(DEFMETHOD HELP-PRINT-OUTLINE ((TOP MODULE) (STREAM OUTPUT-STREAM) (CURRENT-DEPTH INTEGER) (DEPTH INTEGER) (NAMED? BOOLEAN)) :PUBLIC? TRUE :DOCUMENTATION \"Helper method for `print-outline'\")", wrapMethodCode(((cpp_method_code)(&Module::helpPrintOutline))), NULL);
      defineMethodObject("(DEFMETHOD HELP-PRINT-OUTLINE ((TOP CLASS) (STREAM OUTPUT-STREAM) (CURRENT-DEPTH INTEGER) (DEPTH INTEGER) (NAMED? BOOLEAN)) :PUBLIC? TRUE :DOCUMENTATION \"Helper method for `print-outline'\")", wrapMethodCode(((cpp_method_code)(&Class::helpPrintOutline))), NULL);
      defineMethodObject("(DEFMETHOD HELP-PRINT-OUTLINE ((TOP SLOT) (STREAM OUTPUT-STREAM) (CURRENT-DEPTH INTEGER) (DEPTH INTEGER) (NAMED? BOOLEAN)) :PUBLIC? TRUE :DOCUMENTATION \"Helper method for `print-outline'\")", wrapMethodCode(((cpp_method_code)(&Slot::helpPrintOutline))), NULL);
      defineFunctionObject("STARTUP-TOOLS", "(DEFUN STARTUP-TOOLS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupTools)), NULL);
      { MethodSlot* function = lookupFunction(SYM_TOOLS_STELLA_STARTUP_TOOLS);

        setDynamicSlotValue(function->dynamicSlots, SYM_TOOLS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupTools"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *OUTLINE-INDENT-STRING* STRING \"| \" :DOCUMENTATION \"String used in the PRINT-OUTLINE for each level of outline\")", &oOUTLINE_INDENT_STRINGo);
    }
  }
}

Symbol* SYM_TOOLS_STELLA_STARTUP_TOOLS = NULL;

Symbol* SYM_TOOLS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
