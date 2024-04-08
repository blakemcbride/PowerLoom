//  -*- Mode: C++ -*-

// idl-translate-file.cc

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

void idlTranslateClassToStream(Class* clasS, std::ostream* nativeStream) {
  { TranslationUnit* self000 = newTranslationUnit();

    self000->theObject = clasS;
    { TranslationUnit* tempunit = self000;

      { 
        BIND_STELLA_SPECIAL(oCURRENT_STREAMo, OutputStream*, NULL);
        { OutputStream* self001 = newOutputStream();

          self001->nativeStream = nativeStream;
          oCURRENT_STREAMo = self001;
        }
        idlOutputStatement(idlTranslateDefineNativeClassUnit(tempunit));
      }
    }
  }
}

const char* oIDL_TRANSLATED_FILE_SUFFIXo = "";

const char* idlMakeCodeOutputFileName(const char* sourcefile) {
  return (stringConcatenate(fileNameWithoutExtension(sourcefile), stringConcatenate(oIDL_TRANSLATED_FILE_SUFFIXo, ".sidl", 0), 0));
}

void idlOutputAllUnitsToFile(const char* sourcefile) {
  { const char* codeoutputfile = idlMakeCodeOutputFileName(sourcefile);
    OutputFileStream* codeoutputstream = newOutputFileStream(codeoutputfile);
    Cons* globals = NIL;
    Cons* methods = NIL;
    Cons* verbatimstatements = NIL;
    Cons* forms = NIL;

    { 
      BIND_STELLA_SPECIAL(oCURRENT_STREAMo, OutputStream*, codeoutputstream);
      oTRANSLATIONUNITSo = oTRANSLATIONUNITSo->reverse();
      { TranslationUnit* unit = NULL;
        Cons* iter000 = oTRANSLATIONUNITSo->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          unit = ((TranslationUnit*)(iter000->value));
          { Symbol* testValue000 = unit->category;

            if ((testValue000 == SYM_IDL_TRANSLATE_FILE_STELLA_METHOD) ||
                ((testValue000 == SYM_IDL_TRANSLATE_FILE_STELLA_PRINT_METHOD) ||
                 (testValue000 == SYM_IDL_TRANSLATE_FILE_STELLA_MACRO))) {
              methods = cons(unit->translation, methods);
            }
            else if (testValue000 == SYM_IDL_TRANSLATE_FILE_STELLA_VERBATIM) {
              verbatimstatements = cons(unit->translation, verbatimstatements);
            }
            else if (testValue000 == SYM_IDL_TRANSLATE_FILE_STELLA_GLOBAL_VARIABLE) {
              globals = cons(unit->translation, globals);
            }
            else {
              forms = cons(unit->translation, forms);
            }
          }
        }
      }
      std::cout << "Writing " << "`" << codeoutputfile << "'" << "..." << std::endl;
      *(oCURRENT_STREAMo->nativeStream) << "// " << codeoutputfile << std::endl << std::endl;
      if (translateWithCopyrightHeaderP()) {
        outputCopyrightHeader(oCURRENT_STREAMo);
      }
      { Object* form = NULL;
        Cons* iter001 = forms;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          form = iter001->value;
          idlOutputStatement(((Cons*)(form)));
        }
      }
      codeoutputstream->free();
    }
  }
}

void idlTranslateFile(const char* filename) {
  translateFile(filename, KWD_IDL_TRANSLATE_FILE_IDL, false);
}

void startupIdlTranslateFile() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SYM_IDL_TRANSLATE_FILE_STELLA_METHOD = ((Symbol*)(internRigidSymbolWrtModule("METHOD", NULL, 0)));
      SYM_IDL_TRANSLATE_FILE_STELLA_PRINT_METHOD = ((Symbol*)(internRigidSymbolWrtModule("PRINT-METHOD", NULL, 0)));
      SYM_IDL_TRANSLATE_FILE_STELLA_MACRO = ((Symbol*)(internRigidSymbolWrtModule("MACRO", NULL, 0)));
      SYM_IDL_TRANSLATE_FILE_STELLA_VERBATIM = ((Symbol*)(internRigidSymbolWrtModule("VERBATIM", NULL, 0)));
      SYM_IDL_TRANSLATE_FILE_STELLA_GLOBAL_VARIABLE = ((Symbol*)(internRigidSymbolWrtModule("GLOBAL-VARIABLE", NULL, 0)));
      KWD_IDL_TRANSLATE_FILE_IDL = ((Keyword*)(internRigidSymbolWrtModule("IDL", NULL, 2)));
      SYM_IDL_TRANSLATE_FILE_STELLA_STARTUP_IDL_TRANSLATE_FILE = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-IDL-TRANSLATE-FILE", NULL, 0)));
      SYM_IDL_TRANSLATE_FILE_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("IDL-TRANSLATE-CLASS-TO-STREAM", "(DEFUN IDL-TRANSLATE-CLASS-TO-STREAM ((CLASS CLASS) (NATIVE-STREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&idlTranslateClassToStream)), NULL);
      defineFunctionObject("IDL-MAKE-CODE-OUTPUT-FILE-NAME", "(DEFUN (IDL-MAKE-CODE-OUTPUT-FILE-NAME FILE-NAME) ((SOURCEFILE FILE-NAME)))", ((cpp_function_code)(&idlMakeCodeOutputFileName)), NULL);
      defineFunctionObject("IDL-OUTPUT-ALL-UNITS-TO-FILE", "(DEFUN IDL-OUTPUT-ALL-UNITS-TO-FILE ((SOURCEFILE FILE-NAME)))", ((cpp_function_code)(&idlOutputAllUnitsToFile)), NULL);
      defineFunctionObject("IDL-TRANSLATE-FILE", "(DEFUN IDL-TRANSLATE-FILE ((FILENAME FILE-NAME)))", ((cpp_function_code)(&idlTranslateFile)), NULL);
      defineFunctionObject("STARTUP-IDL-TRANSLATE-FILE", "(DEFUN STARTUP-IDL-TRANSLATE-FILE () :PUBLIC? TRUE)", ((cpp_function_code)(&startupIdlTranslateFile)), NULL);
      { MethodSlot* function = lookupFunction(SYM_IDL_TRANSLATE_FILE_STELLA_STARTUP_IDL_TRANSLATE_FILE);

        setDynamicSlotValue(function->dynamicSlots, SYM_IDL_TRANSLATE_FILE_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupIdlTranslateFile"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *IDL-TRANSLATED-FILE-SUFFIX* STRING \"\")", &oIDL_TRANSLATED_FILE_SUFFIXo);
    }
  }
}

Symbol* SYM_IDL_TRANSLATE_FILE_STELLA_METHOD = NULL;

Symbol* SYM_IDL_TRANSLATE_FILE_STELLA_PRINT_METHOD = NULL;

Symbol* SYM_IDL_TRANSLATE_FILE_STELLA_MACRO = NULL;

Symbol* SYM_IDL_TRANSLATE_FILE_STELLA_VERBATIM = NULL;

Symbol* SYM_IDL_TRANSLATE_FILE_STELLA_GLOBAL_VARIABLE = NULL;

Keyword* KWD_IDL_TRANSLATE_FILE_IDL = NULL;

Symbol* SYM_IDL_TRANSLATE_FILE_STELLA_STARTUP_IDL_TRANSLATE_FILE = NULL;

Symbol* SYM_IDL_TRANSLATE_FILE_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
