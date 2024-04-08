//  -*- Mode: C++ -*-

// walk.cc

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

// List of available STELLA features.
List* oAVAILABLE_STELLA_FEATURESo = NULL;

// List of currently enabled STELLA features.
DEFINE_STELLA_SPECIAL(oCURRENT_STELLA_FEATURESo, List* , NULL);

// List of STELLA features enabled by default and after resetting them
// with `reset-stella-features'.
List* oDEFAULT_STELLA_FEATURESo = NULL;

void printStellaFeatures() {
  // Print the list of enabled and disabled STELLA features.
  std::cout << "Enabled STELLA features:" << std::endl;
  { Keyword* feature = NULL;
    Cons* iter000 = oCURRENT_STELLA_FEATURESo->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      feature = ((Keyword*)(iter000->value));
      std::cout << "  :" << stringDowncase(feature->symbolName) << std::endl;
    }
  }
  std::cout << std::endl << "Disabled STELLA features:" << std::endl;
  { Keyword* feature = NULL;
    Cons* iter001 = oAVAILABLE_STELLA_FEATURESo->theConsList;

    for (; !(iter001 == NIL); iter001 = iter001->rest) {
      feature = ((Keyword*)(iter001->value));
      if (!oCURRENT_STELLA_FEATURESo->memberP(feature)) {
        std::cout << "  :" << stringDowncase(feature->symbolName) << std::endl;
      }
    }
  }
}

void setStellaFeature(Cons* features) {
  // Enable all listed STELLA `features'.
  { Keyword* f = NULL;
    Cons* iter000 = features;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      f = ((Keyword*)(iter000->value));
      if (f == KWD_WALK_WARN_ABOUT_UNDEFINED_METHODS) {
      }
      else if (f == KWD_WALK_WARN_ABOUT_MISSING_METHODS) {
      }
      else if (f == KWD_WALK_SUPPRESS_WARNINGS) {
      }
      else if (f == KWD_WALK_USE_HARDCODED_SYMBOLS) {
      }
      else if (f == KWD_WALK_USE_COMMON_LISP_STRUCTS) {
        oCURRENT_STELLA_FEATURESo->remove(KWD_WALK_USE_COMMON_LISP_VECTOR_STRUCTS);
      }
      else if (f == KWD_WALK_USE_COMMON_LISP_CONSES) {
      }
      else if (f == KWD_WALK_USE_CPP_GARBAGE_COLLECTOR) {
      }
      else if (f == KWD_WALK_MINIMIZE_JAVA_PREFIXES) {
      }
      else if (f == KWD_WALK_TRANSLATE_WITH_COPYRIGHT_HEADER) {
      }
      else if (f == KWD_WALK_SUPPORT_UNEXEC) {
      }
      else {
        if (oAVAILABLE_STELLA_FEATURESo->memberP(f)) {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "STELLA feature " << "`" << f << "'" << " is valid but not yet implemented";
            throw *newStellaException(stream000->theStringReader());
          }
        }
        else {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "Invalid STELLA feature: " << "`" << f << "'" << std::endl;
        }
        continue;
      }
      oCURRENT_STELLA_FEATURESo->insertNew(f);
    }
  }
}

void setStellaFeatureEvaluatorWrapper(Cons* arguments) {
  setStellaFeature(arguments);
}

void unsetStellaFeature(Cons* features) {
  // Disable all listed STELLA `features'.
  { Keyword* f = NULL;
    Cons* iter000 = features;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      f = ((Keyword*)(iter000->value));
      if (f == KWD_WALK_WARN_ABOUT_UNDEFINED_METHODS) {
      }
      else if (f == KWD_WALK_WARN_ABOUT_MISSING_METHODS) {
      }
      else if (f == KWD_WALK_SUPPRESS_WARNINGS) {
      }
      else if (f == KWD_WALK_USE_HARDCODED_SYMBOLS) {
      }
      else if (f == KWD_WALK_USE_COMMON_LISP_STRUCTS) {
      }
      else if (f == KWD_WALK_USE_COMMON_LISP_CONSES) {
      }
      else if (f == KWD_WALK_USE_CPP_GARBAGE_COLLECTOR) {
      }
      else if (f == KWD_WALK_MINIMIZE_JAVA_PREFIXES) {
      }
      else if (f == KWD_WALK_TRANSLATE_WITH_COPYRIGHT_HEADER) {
      }
      else if (f == KWD_WALK_SUPPORT_UNEXEC) {
      }
      else {
        if (oAVAILABLE_STELLA_FEATURESo->memberP(f)) {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "STELLA feature " << "`" << f << "'" << " is valid but not yet implemented";
            throw *newStellaException(stream000->theStringReader());
          }
        }
        else {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "Invalid STELLA feature: " << "`" << f << "'" << std::endl;
        }
        continue;
      }
      oCURRENT_STELLA_FEATURESo->remove(f);
    }
  }
}

void unsetStellaFeatureEvaluatorWrapper(Cons* arguments) {
  unsetStellaFeature(arguments);
}

void resetStellaFeatures() {
  // Reset STELLA features to their default settings.
  { Keyword* f = NULL;
    Cons* iter000 = oCURRENT_STELLA_FEATURESo->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      f = ((Keyword*)(iter000->value));
      if (!oDEFAULT_STELLA_FEATURESo->memberP(f)) {
        unsetStellaFeature(consList(1, f));
      }
    }
  }
  { Keyword* f = NULL;
    Cons* iter001 = oDEFAULT_STELLA_FEATURESo->theConsList;

    for (; !(iter001 == NIL); iter001 = iter001->rest) {
      f = ((Keyword*)(iter001->value));
      if (!oCURRENT_STELLA_FEATURESo->memberP(f)) {
        setStellaFeature(consList(1, f));
      }
    }
  }
}

boolean enabledStellaFeatureP(Keyword* feature) {
  // Return true if the STELLA `feature' is currently enabled.
  return (oCURRENT_STELLA_FEATURESo->membP(feature));
}

boolean disabledStellaFeatureP(Keyword* feature) {
  // Return true if the STELLA `feature' is currently disabled.
  return (!oCURRENT_STELLA_FEATURESo->membP(feature));
}

List* oTRACED_KEYWORDSo = NULL;

Object* traceIf(Object* keyword, Cons* body) {
  // If `keyword' is a trace keyword that has been enabled with `add-trace'
  // print all the elements in `body' to standard output.  Otherwise, do nothing.
  // `keyword' can also be a list of keywords in which case printing is done if
  // one or more of them are trace enabled.
  { StandardObject* dummy1;

    { Cons* test = NIL;
      Cons* elements = copyConsList(body);

      if (safePrimaryType(keyword) == SGT_WALK_STELLA_CONS) {
        { Object* keyword000 = keyword;
          Cons* keyword = ((Cons*)(keyword000));

          { Object* kwd = NULL;
            Cons* iter000 = keyword;
            Cons* collect000 = NULL;

            for  (; !(iter000 == NIL); 
                  iter000 = iter000->rest) {
              kwd = iter000->value;
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(listO(4, SYM_WALK_STELLA_MEMBp, SYM_WALK_STELLA_oTRACED_KEYWORDSo, kwd, NIL), NIL);
                  if (test == NIL) {
                    test = collect000;
                  }
                  else {
                    addConsToEndOfConsList(test, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(listO(4, SYM_WALK_STELLA_MEMBp, SYM_WALK_STELLA_oTRACED_KEYWORDSo, kwd, NIL), NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
          switch (test->length()) {
            case 0: 
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing `trace-if' keyword" << "." << std::endl;
                }
              }
              return (walkDontCallMeTree(NIL, SGT_WALK_STELLA_VOID, dummy1));
            case 1: 
              test = ((Cons*)(test->value));
              break;
            default:
              test = cons(SYM_WALK_STELLA_OR, test);
              break;
          }
        }
      }
      else {
        test = listO(4, SYM_WALK_STELLA_MEMBp, SYM_WALK_STELLA_oTRACED_KEYWORDSo, keyword, NIL);
      }
      return (listO(4, SYM_WALK_STELLA_WHEN, listO(4, SYM_WALK_STELLA_AND, listO(3, SYM_WALK_STELLA_DEFINEDp, SYM_WALK_STELLA_oTRACED_KEYWORDSo, NIL), test, NIL), cons(SYM_WALK_STELLA_PRINT, copyConsList(elements)->concatenate(NIL, 0)), ((((elements->last() == SYM_WALK_STELLA_EOL) ||
          (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP)) ? NIL : cons(listO(3, SYM_WALK_STELLA_FLUSH_OUTPUT, SYM_WALK_STELLA_STANDARD_OUTPUT, NIL), NIL)))->concatenate(NIL, 0)));
    }
  }
}

boolean traceKeywordP(Object* keyword) {
  { boolean testValue000 = false;

    testValue000 = ((boolean)(oTRACED_KEYWORDSo));
    if (testValue000) {
      { boolean chooseValue000 = false;

        if (consP(keyword)) {
          { boolean foundP000 = false;

            { Object* kwd = NULL;
              Cons* iter000 = ((Cons*)(keyword));

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                kwd = iter000->value;
                if (oTRACED_KEYWORDSo->membP(((Keyword*)(kwd)))) {
                  foundP000 = true;
                  break;
                }
              }
            }
            chooseValue000 = foundP000;
          }
        }
        else {
          chooseValue000 = oTRACED_KEYWORDSo->membP(((Keyword*)(keyword)));
        }
        testValue000 = chooseValue000;
      }
    }
    { boolean value000 = testValue000;

      return (value000);
    }
  }
}

List* addTrace(Cons* keywords) {
  // Enable trace messages identified by any of the listed `keywords'.  After
  // calling (`add-trace' <keyword>) code guarded by (`trace-if' <keyword> ...)
  // will be executed when it is encountered.
  if (!((boolean)(oTRACED_KEYWORDSo))) {
    oTRACED_KEYWORDSo = list(0);
  }
  { GeneralizedSymbol* k = NULL;
    Cons* iter000 = keywords;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      k = ((GeneralizedSymbol*)(iter000->value));
      oTRACED_KEYWORDSo->insertNew(stringKeywordify(k->symbolName));
    }
  }
  return (oTRACED_KEYWORDSo);
}

List* addTraceEvaluatorWrapper(Cons* arguments) {
  return (addTrace(arguments));
}

List* dropTrace(Cons* keywords) {
  // Disable trace messages identified by any of the listed `keywords'.  After
  // calling (`drop-trace' <keyword>) code guarded by (`trace-if' <keyword> ...)
  // will not be executed when it is encountered.
  if (((boolean)(oTRACED_KEYWORDSo))) {
    { GeneralizedSymbol* k = NULL;
      Cons* iter000 = keywords;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        k = ((GeneralizedSymbol*)(iter000->value));
        oTRACED_KEYWORDSo->remove(stringKeywordify(k->symbolName));
      }
    }
    if (oTRACED_KEYWORDSo->emptyP()) {
      oTRACED_KEYWORDSo = NULL;
    }
  }
  return (oTRACED_KEYWORDSo);
}

List* dropTraceEvaluatorWrapper(Cons* arguments) {
  return (dropTrace(arguments));
}

void clearTrace() {
  // Disable all tracing previously enabled with `add-trace'.
  oTRACED_KEYWORDSo->clear();
}

// Integer between 0 and 3.  Higher levels call more
// safety checks.
DEFINE_STELLA_SPECIAL(oSAFETYo, int , 3);

// Integer between 0 and 3.  Higher levels generate more
// code to aid debugging.
DEFINE_STELLA_SPECIAL(oDEBUGLEVELo, int , 3);

// Integer between 0 and 3.  Higher levels optimize for
// greater execution speed.
DEFINE_STELLA_SPECIAL(oOPTIMIZESPEEDLEVELo, int , 3);

// Integer between 0 and 3.  Higher levels optimize for
// less code size and memory consumption.
DEFINE_STELLA_SPECIAL(oOPTIMIZESPACELEVELo, int , 3);

void setOptimizationLevels(int safety, int debug, int speed, int space) {
  // Set optimization levels for the qualities `safety', `debug',
  // `speed', and `space'.
  if ((safety != NULL_INTEGER) &&
      ((safety >= 0) &&
       (safety <= 3))) {
    oSAFETYo = safety;
  }
  if ((debug != NULL_INTEGER) &&
      ((debug >= 0) &&
       (debug <= 3))) {
    oDEBUGLEVELo = debug;
  }
  if ((speed != NULL_INTEGER) &&
      ((speed >= 0) &&
       (speed <= 3))) {
    oOPTIMIZESPEEDLEVELo = speed;
  }
  if ((space != NULL_INTEGER) &&
      ((space >= 0) &&
       (space <= 3))) {
    oOPTIMIZESPACELEVELo = space;
  }
}

boolean preserveTailMergeOptimizabilityP() {
  return ((oOPTIMIZESPEEDLEVELo >= 3) &&
      (oDEBUGLEVELo <= 0));
}

boolean methodCallInliningEnabledP() {
  return ((oOPTIMIZESPEEDLEVELo >= 3) &&
      (oDEBUGLEVELo <= 1));
}

boolean optimizeBooleanTestsP() {
  return ((oOPTIMIZESPEEDLEVELo >= 2) &&
      (oDEBUGLEVELo <= 2));
}

boolean checkForIllegalReturnP() {
  return ((oSAFETYo >= 3) &&
      ((!(oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA)) &&
       (!preserveTailMergeOptimizabilityP())));
}

boolean supportUnexecP() {
  return (oCURRENT_STELLA_FEATURESo->membP(KWD_WALK_SUPPORT_UNEXEC) &&
      translateToCppP());
}

const char* nameQuotedTree(Cons* tree) {
  { Cons* nametree = cons(tree, cons(wrapString(oMODULEo->moduleFullName), NIL));
    const char* name = stringify(nametree);

    return (name);
  }
}

Cons* getQuotedTree(const char* treeName, const char* modulename) {
  // Return the quoted tree with name `tree-name'.
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_WALK_STELLA_F_GET_QUOTED_TREE_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_WALK_STELLA_F_GET_QUOTED_TREE_MEMO_TABLE_000, "(:MAX-VALUES 200 :TIMESTAMPS (:MODULE-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_WALK_STELLA_F_GET_QUOTED_TREE_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), wrapString(treeName), MEMOIZED_NULL_VALUE, NULL, NULL, 0);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = permanentifyForm(((Cons*)(unstringifyInModule(treeName, getStellaModule(modulename, true))))->value);
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { Object* value000 = ((Object*)(memoizedValue000));

      return (((Cons*)(value000)));
    }
  }
}

TranslationUnit* newTranslationUnit() {
  { TranslationUnit* self = NULL;

    self = new TranslationUnit();
    self->referencedGlobals = newList();
    self->translation = NULL;
    self->codeRegister = NULL;
    self->auxiliaryP = false;
    self->annotation = NULL;
    self->category = NULL;
    self->theObject = NULL;
    self->tuHomeModule = NULL;
    return (self);
  }
}

Surrogate* TranslationUnit::primaryType() {
  { TranslationUnit* self = this;

    return (SGT_WALK_STELLA_TRANSLATION_UNIT);
  }
}

Module* TranslationUnit::homeModule() {
  { TranslationUnit* self = this;

    return (self->tuHomeModule);
  }
}

Object* accessTranslationUnitSlotValue(TranslationUnit* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_WALK_STELLA_TU_HOME_MODULE) {
    if (setvalueP) {
      self->tuHomeModule = ((Module*)(value));
    }
    else {
      value = self->tuHomeModule;
    }
  }
  else if (slotname == SYM_WALK_STELLA_THE_OBJECT) {
    if (setvalueP) {
      self->theObject = value;
    }
    else {
      value = self->theObject;
    }
  }
  else if (slotname == SYM_WALK_STELLA_CATEGORY) {
    if (setvalueP) {
      self->category = ((Symbol*)(value));
    }
    else {
      value = self->category;
    }
  }
  else if (slotname == SYM_WALK_STELLA_ANNOTATION) {
    if (setvalueP) {
      self->annotation = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->annotation);
    }
  }
  else if (slotname == SYM_WALK_STELLA_AUXILIARYp) {
    if (setvalueP) {
      self->auxiliaryP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->auxiliaryP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_WALK_STELLA_CODE_REGISTER) {
    if (setvalueP) {
      self->codeRegister = value;
    }
    else {
      value = self->codeRegister;
    }
  }
  else if (slotname == SYM_WALK_STELLA_TRANSLATION) {
    if (setvalueP) {
      self->translation = value;
    }
    else {
      value = self->translation;
    }
  }
  else if (slotname == SYM_WALK_STELLA_REFERENCED_GLOBALS) {
    if (setvalueP) {
      self->referencedGlobals = ((List*)(value));
    }
    else {
      value = self->referencedGlobals;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

void TranslationUnit::printObject(std::ostream* stream) {
  { TranslationUnit* self = this;

    printTranslationUnit(self, stream);
  }
}

void clearTranslationUnit(TranslationUnit* self) {
  self->tuHomeModule = NULL;
  self->theObject = NULL;
  self->category = NULL;
  self->codeRegister = NULL;
  self->translation = NULL;
}

void printTranslationUnit(TranslationUnit* self, std::ostream* stream) {
  *(stream) << "|TU|[" << self->category;
  { Symbol* testValue000 = self->category;

    if ((testValue000 == SYM_WALK_STELLA_CLASS) ||
        ((testValue000 == SYM_WALK_STELLA_METHOD) ||
         (testValue000 == SYM_WALK_STELLA_GLOBAL_VARIABLE))) {
      *(stream) << " " << self->theObject;
    }
    else {
    }
  }
  *(stream) << "]";
}

// List of objects representing partially walked
// top-level definitions and auxiliary code.
DEFINE_STELLA_SPECIAL(oTRANSLATIONUNITSo, List* , NULL);

// The translation unit currently operated on.
DEFINE_STELLA_SPECIAL(oCURRENTTRANSLATIONUNITo, TranslationUnit* , NULL);

// Indicates the current translation phase which is one of
// :DEFINE, :FINALIZE, :WALK, or :TRANSLATE.
DEFINE_STELLA_SPECIAL(oTRANSLATIONPHASEo, Keyword* , NULL);

// The higher the level, the more progress annotations are
// generated during the translation of Stella declarations.
DEFINE_STELLA_SPECIAL(oTRANSLATIONVERBOSITYLEVELo, int , 1);

DEFINE_STELLA_SPECIAL(oUSEHARDCODEDSYMBOLSpo, boolean , false);

boolean useHardcodedSymbolsP() {
  return (oCURRENT_STELLA_FEATURESo->memberP(KWD_WALK_USE_HARDCODED_SYMBOLS) ||
      oUSEHARDCODEDSYMBOLSpo);
}

// Specifies the current translator output language; either
// :common-lisp, :idl, :java, :cpp, or :cpp-standalone.  The initial value
// points to the native implementation language of this STELLA instance.
DEFINE_STELLA_SPECIAL(oTRANSLATOROUTPUTLANGUAGEo, Keyword* , NULL);

Keyword* translatorOutputLanguage() {
  return (oTRANSLATOROUTPUTLANGUAGEo);
}

const char* translatorOutputLanguageName() {
  if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP) {
    return ("Common Lisp");
  }
  else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP) {
    return ("C++");
  }
  else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA) {
    return ("Java");
  }
  else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP_STANDALONE) {
    return ("standalone-C++");
  }
  else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_IDL) {
    return ("IDL");
  }
  else {
    return (oTRANSLATOROUTPUTLANGUAGEo->symbolName);
  }
}

Keyword* setTranslatorOutputLanguage(Keyword* newLanguage) {
  // Set output language to `new-language'.  Return previous language.
  { Keyword* oldlanguage = oTRANSLATOROUTPUTLANGUAGEo;

    if (!(listO(6, KWD_WALK_CPP, KWD_WALK_CPP_STANDALONE, KWD_WALK_COMMON_LISP, KWD_WALK_JAVA, KWD_WALK_IDL, NIL)->memberP(newLanguage))) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "`" << newLanguage << "'" << " is not a legal translation language" << std::endl;
    }
    oTRANSLATOROUTPUTLANGUAGEo = newLanguage;
    return (oldlanguage);
  }
}

boolean translateToCommonLispP() {
  // Return `true' if current output language is Common-Lisp.
  return (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP);
}

boolean translateToCppP() {
  // Return `true' if current output language is C++
  return (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP);
}

boolean translateToJavaP() {
  // Return `true' if current output language is Java
  return (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA);
}

boolean translateToSingleInheritanceLanguageP() {
  if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP) ||
      ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP) ||
       (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA))) {
    return (true);
  }
  else {
    return (false);
  }
}

Keyword* toggleOutputLanguage() {
  // Switch between Common Lisp and C++ as output languages.
  if (translateToCommonLispP()) {
    oTRANSLATOROUTPUTLANGUAGEo = KWD_WALK_CPP;
    return (KWD_WALK_CPP);
  }
  else if (translateToCppP()) {
    oTRANSLATOROUTPUTLANGUAGEo = KWD_WALK_JAVA;
    return (KWD_WALK_JAVA);
  }
  else {
    oTRANSLATOROUTPUTLANGUAGEo = KWD_WALK_COMMON_LISP;
    return (KWD_WALK_COMMON_LISP);
  }
}

boolean useBootstrapTranslatorP() {
  return (false);
}

Keyword* toggleTranslators() {
  return (NULL);
}

boolean declarationOperatorP(Symbol* operatoR) {
  return (getQuotedTree("((DEFCLASS DEFSLOT DEFMETHOD DEFUN DEFTYPE DEFGLOBAL DEFSPECIAL DEFCONSTANT DEFMACRO DEFMODULE STARTUP-TIME-PROGN) \"/STELLA\")", "/STELLA")->memberP(operatoR));
}

boolean declarationTreeP(Cons* tree) {
  { Object* operatoR = tree->value;

    if (declarationOperatorP(((Symbol*)(operatoR)))) {
      return (true);
    }
    if (operatoR == SYM_WALK_STELLA_PROGN) {
      { boolean foundP000 = false;

        { Object* subtree = NULL;
          Cons* iter000 = tree->rest;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            subtree = iter000->value;
            if (consP(subtree) &&
                declarationTreeP(((Cons*)(subtree)))) {
              foundP000 = true;
              break;
            }
          }
        }
        { boolean value000 = foundP000;

          return (value000);
        }
      }
    }
    if (((boolean)(lookupMacro(((Symbol*)(operatoR)))))) {
      { Object* expansion = expandMacro(copyConsList(tree));

        if (((boolean)(expansion))) {
          if (safePrimaryType(expansion) == SGT_WALK_STELLA_CONS) {
            { Object* expansion000 = expansion;
              Cons* expansion = ((Cons*)(expansion000));

              tree->value = expansion->value;
              tree->rest = expansion->rest;
              return (declarationTreeP(tree));
            }
          }
          else {
            return (false);
          }
        }
        else {
          tree->value = SYM_WALK_STELLA_PROGN;
          tree->rest = NIL;
          return (false);
        }
      }
    }
    return (false);
  }
}

const char* createAnnotation(Cons* topLevelTree) {
  return (stringConcatenate("(", stringConcatenate(((Symbol*)(topLevelTree->value))->symbolName, stringConcatenate(" ", stringConcatenate(stringify(topLevelTree->rest->value), " ...)", 0), 0), 0), 0));
}

void walkTopLevelTree(Cons* tree, boolean createannotationP) {
  { 
    BIND_STELLA_SPECIAL(oCURRENTTRANSLATIONUNITo, TranslationUnit*, NULL);
    { const char* annotation = NULL;

      if (createannotationP) {
        annotation = createAnnotation(tree);
        if (oTRANSLATIONVERBOSITYLEVELo >= 2) {
          std::cout << "Defining " << "`" << annotation << "'" << std::endl;
        }
      }
      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

        if (testValue000 == SYM_WALK_STELLA_DEFCLASS) {
          walkDefclassTree(tree);
        }
        else if (testValue000 == SYM_WALK_STELLA_DEFSLOT) {
          walkDefslotTree(tree);
        }
        else if ((testValue000 == SYM_WALK_STELLA_DEFMETHOD) ||
            ((testValue000 == SYM_WALK_STELLA_DEFUN) ||
             (testValue000 == SYM_WALK_STELLA_DEFOPERATOR))) {
          if (tree->value == SYM_WALK_STELLA_DEFOPERATOR) {
            tree->firstSetter(SYM_WALK_STELLA_DEFMETHOD);
          }
          walkDefmethodTree(tree);
        }
        else if ((testValue000 == SYM_WALK_STELLA_DEFGLOBAL) ||
            ((testValue000 == SYM_WALK_STELLA_DEFSPECIAL) ||
             (testValue000 == SYM_WALK_STELLA_DEFCONSTANT))) {
          walkDefglobalTree(tree);
        }
        else if (testValue000 == SYM_WALK_STELLA_DEFTYPE) {
          walkDeftypeTree(tree);
        }
        else if (testValue000 == SYM_WALK_STELLA_DEFMODULE) {
          walkDefmoduleTree(tree);
        }
        else if (testValue000 == SYM_WALK_STELLA_DEFMACRO) {
          walkDefmacroTree(tree);
        }
        else if (testValue000 == SYM_WALK_STELLA_STARTUP_TIME_PROGN) {
          walkStartupTimePrognTree(tree);
        }
        else if (testValue000 == SYM_WALK_STELLA_VERBATIM) {
          walkVerbatimDefinitionTree(tree);
        }
        else if (testValue000 == SYM_WALK_STELLA_PROGN) {
          { Object* form = NULL;
            Cons* iter000 = tree->rest;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              form = iter000->value;
              walkTopLevelTree(((Cons*)(form)), createannotationP);
            }
          }
          return;
        }
        else {
          if (((boolean)(lookupMacro(((Symbol*)(tree->value)))))) {
            { Object* expansion = expandMacro(tree);

              if (((boolean)(expansion))) {
                walkTopLevelTree(((Cons*)(expansion)), createannotationP);
              }
            }
          }
          else {
            if (!(incrementalTranslationP() ||
                ((boolean)(lookupCommand(((Symbol*)(tree->value))))))) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationWarning();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> WARNING: ", STANDARD_WARNING);
                  *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Illegal top-level statement:" << std::endl << "   " << "`" << deUglifyParseTree(tree) << "'" << std::endl << " Wrapping it into a 'startup-time-progn'" << "." << std::endl;
                }
              }
            }
            tree = listO(3, SYM_WALK_STELLA_STARTUP_TIME_PROGN, tree, NIL);
            walkTopLevelTree(tree, false);
          }
          return;
        }
      }
      if (((boolean)(oCURRENTTRANSLATIONUNITo))) {
        oTRANSLATIONUNITSo->push(oCURRENTTRANSLATIONUNITo);
        oCURRENTTRANSLATIONUNITo->annotation = annotation;
      }
    }
  }
}

Object* walkTopLevelExpression(Object* tree) {
  { 
    BIND_STELLA_SPECIAL(oLOCALVARIABLETYPETABLEo, KeyValueList*, newKeyValueList());
    { Object* otree = walkWithoutTypeTree(tree);

      if (vrletExpressionP(otree)) {
        return (walkWithoutTypeTree(listO(3, SYM_WALK_STELLA_PROGN, otree, NIL)));
      }
      return (otree);
    }
  }
}

void walkPhaseOneUnit(TranslationUnit* unit) {
  { 
    BIND_STELLA_SPECIAL(oLOCALVARIABLETYPETABLEo, KeyValueList*, newKeyValueList());
    BIND_STELLA_SPECIAL(oCURRENTTRANSLATIONUNITo, TranslationUnit*, unit);
    { Symbol* testValue000 = unit->category;

      if (testValue000 == SYM_WALK_STELLA_GLOBAL_VARIABLE) {
        walkGlobalUnit(unit);
      }
      else if (testValue000 == SYM_WALK_STELLA_MODULE) {
        walkModuleUnit(unit);
      }
      else if (testValue000 == SYM_WALK_STELLA_TYPE) {
        walkTypeUnit(unit);
      }
      else if ((testValue000 == SYM_WALK_STELLA_METHOD) ||
          (testValue000 == SYM_WALK_STELLA_PRINT_METHOD)) {
        walkMethodUnit(unit);
      }
      else if (testValue000 == SYM_WALK_STELLA_CLASS) {
        walkClassUnit(unit);
      }
      else if (testValue000 == SYM_WALK_STELLA_SLOT) {
        walkSlotUnit(unit);
      }
      else if (testValue000 == SYM_WALK_STELLA_STARTUP_TIME_PROGN) {
        walkStartupTimePrognUnit(unit);
      }
      else if (testValue000 == SYM_WALK_STELLA_VERBATIM) {
        walkVerbatimUnit(unit);
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

void walkAuxiliaryTree(Cons* tree) {
  helpWalkAuxiliaryTree(tree, true);
}

TranslationUnit* helpWalkAuxiliaryTree(Cons* tree, boolean finalizeP) {
  if (!(getQuotedTree("((DEFCLASS DEFMETHOD DEFUN DEFMACRO DEFGLOBAL DEFSPECIAL DEFCONSTANT STARTUP-TIME-PROGN VERBATIM) \"/STELLA\")", "/STELLA")->memberP(tree->value))) {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "OOPS, illegal auxiliary statement:" << std::endl << "   " << "`" << tree << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  walkTopLevelTree(tree, false);
  if (finalizeP) {
    finalizeClassesAndSlots();
  }
  { TranslationUnit* unit = ((TranslationUnit*)(oTRANSLATIONUNITSo->pop()));

    unit->auxiliaryP = true;
    walkPhaseOneUnit(unit);
    return (unit);
  }
}

void walkAllPhaseOneUnits() {
  { List* phaseoneunits = oTRANSLATIONUNITSo;

    oTRANSLATIONUNITSo = newList();
    { TranslationUnit* unit = NULL;
      Cons* iter000 = phaseoneunits->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        unit = ((TranslationUnit*)(iter000->value));
        if ((oTRANSLATIONVERBOSITYLEVELo >= 2) &&
            (unit->annotation != NULL)) {
          std::cout << "Walking " << "`" << unit->annotation << "'" << std::endl;
        }
        walkPhaseOneUnit(unit);
      }
    }
    createFinalizationUnits();
    createStartupFunctionUnits();
    phaseoneunits->clear();
    oTRANSLATIONUNITSo->reverse();
  }
}

void translateAllUnits() {
  { TranslationUnit* unit = NULL;
    Cons* iter000 = oTRANSLATIONUNITSo->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      unit = ((TranslationUnit*)(iter000->value));
      { 
        BIND_STELLA_SPECIAL(oCURRENTTRANSLATIONUNITo, TranslationUnit*, unit);
        if ((oTRANSLATIONVERBOSITYLEVELo >= 2) &&
            (unit->annotation != NULL)) {
          std::cout << "Translating " << "`" << unit->annotation << "'" << std::endl;
        }
        if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP) {
          unit->translation = clTranslateUnit(unit);
        }
        else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_IDL) {
          unit->translation = idlTranslateUnit(unit);
        }
        else if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA) ||
            (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA_STANDALONE)) {
          if (!((boolean)(unit->translation))) {
            unit->translation = javaTranslateUnit(unit);
          }
        }
        else if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP) ||
            (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP_STANDALONE)) {
          unit->translation = cppTranslateUnit(unit);
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
  }
}

boolean unitIncludedInOtherUnitsP(TranslationUnit* unit) {
  { MethodSlot* method = NULL;

    if (!(unit->category == SYM_WALK_STELLA_METHOD)) {
      return (false);
    }
    else {
      {
        method = ((MethodSlot*)(unit->theObject));
        if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_CONSTRUCTORp, FALSE_WRAPPER)))->wrapperValue) {
          { TranslationUnit* otherUnit = NULL;
            Cons* iter000 = oTRANSLATIONUNITSo->theConsList;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              otherUnit = ((TranslationUnit*)(iter000->value));
              if ((otherUnit->category == SYM_WALK_STELLA_CLASS) &&
                  (canonicalType(method->slotBaseType) == ((Class*)(otherUnit->theObject))->classType)) {
                return (true);
              }
            }
          }
          return (false);
        }
        else {
          { TranslationUnit* otherUnit = NULL;
            Cons* iter001 = oTRANSLATIONUNITSo->theConsList;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              otherUnit = ((TranslationUnit*)(iter001->value));
              if ((otherUnit->category == SYM_WALK_STELLA_CLASS) &&
                  (canonicalType(method->slotOwner) == ((Class*)(otherUnit->theObject))->classType)) {
                return (true);
              }
            }
          }
          return (false);
        }
      }
    }
  }
}

Cons* combineTranslatedTrees() {
  { Cons* otree = NIL;

    if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP) ||
        ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP) ||
         ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP_STANDALONE) ||
          (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_IDL)))) {
      { TranslationUnit* unit = NULL;
        Cons* iter000 = oTRANSLATIONUNITSo->theConsList;
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          unit = ((TranslationUnit*)(iter000->value));
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(unit->translation, NIL);
              if (otree == NIL) {
                otree = collect000;
              }
              else {
                addConsToEndOfConsList(otree, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(unit->translation, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    else if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA) ||
        (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA_STANDALONE)) {
      { TranslationUnit* unit = NULL;
        Cons* iter001 = oTRANSLATIONUNITSo->theConsList;
        Cons* collect001 = NULL;

        for  (; !(iter001 == NIL); 
              iter001 = iter001->rest) {
          unit = ((TranslationUnit*)(iter001->value));
          if (!unitIncludedInOtherUnitsP(unit)) {
            if (!((boolean)(collect001))) {
              {
                collect001 = cons(unit->translation, NIL);
                if (otree == NIL) {
                  otree = collect001;
                }
                else {
                  addConsToEndOfConsList(otree, collect001);
                }
              }
            }
            else {
              {
                collect001->rest = cons(unit->translation, NIL);
                collect001 = collect001->rest;
              }
            }
          }
        }
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP) {
      otree = cons(internCommonLispSymbol("PROGN"), otree->concatenate(NIL, 0));
    }
    else if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP) ||
        ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP_STANDALONE) ||
         ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA) ||
          (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_IDL)))) {
    }
    else {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " is not a valid case option";
        throw *newStellaException(stream001->theStringReader());
      }
    }
    return (otree);
  }
}

Object* translateWalkedTree(Object* codetree) {
  if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP) {
    return (clTranslateATree(codetree));
  }
  else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_IDL) {
    return (idlTranslateATree(codetree));
  }
  else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA) {
    return (javaTranslateATree(codetree));
  }
  else if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP) ||
      (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP_STANDALONE)) {
    return (cppTranslateATree(codetree));
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Object* incrementallyTranslate(Object* tree) {
  // Translate a single Stella expression `tree' and return
  // the result.  For C++ and Java print the translation to standard output and
  // return NIL instead.
  { boolean toplevelinvocationP = !((boolean)(oTRANSLATIONUNITSo));
    Object* ocode = NULL;
    boolean declarationP = consP(tree) &&
        declarationTreeP(((Cons*)(tree)));

    { 
      BIND_STELLA_SPECIAL(oTRANSLATIONUNITSo, List*, newList());
      BIND_STELLA_SPECIAL(oTRANSLATIONVERBOSITYLEVELo, int, 0);
      BIND_STELLA_SPECIAL(oTRANSLATIONPHASEo, Keyword*, NULL);
      BIND_STELLA_SPECIAL(oTRANSLATIONERRORSo, int, 0);
      BIND_STELLA_SPECIAL(oTRANSLATIONWARNINGSo, int, 0);
      BIND_STELLA_SPECIAL(oTRANSLATIONNOTESo, int, 0);
      if (declarationP) {
        oTRANSLATIONPHASEo = KWD_WALK_DEFINE;
        walkTopLevelTree(((Cons*)(tree)), false);
        if (translationErrorsP()) {
          summarizeTranslationErrors();
          return (NIL);
        }
        oTRANSLATIONUNITSo->reverse();
        oTRANSLATIONPHASEo = KWD_WALK_FINALIZE;
        finalizeClassesAndSlots();
        oTRANSLATIONPHASEo = KWD_WALK_WALK;
        if (!(useHardcodedSymbolsP())) {
          clearSymbolRegistry();
        }
        walkAllPhaseOneUnits();
      }
      else {
        oTRANSLATIONPHASEo = KWD_WALK_WALK;
        { 
          BIND_STELLA_SPECIAL(oUSEHARDCODEDSYMBOLSpo, boolean, true);
          ocode = walkTopLevelExpression(tree);
        }
      }
      if (translationErrorsP()) {
        summarizeTranslationErrors();
        return (NIL);
      }
      oTRANSLATIONPHASEo = KWD_WALK_TRANSLATE;
      if (declarationP) {
        translateAllUnits();
        ocode = combineTranslatedTrees();
      }
      else {
        { 
          BIND_STELLA_SPECIAL(oUSEHARDCODEDSYMBOLSpo, boolean, true);
          ocode = translateWalkedTree(ocode);
        }
      }
      if (translationErrorsP()) {
        summarizeTranslationErrors();
        return (NIL);
      }
      if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP) {
      }
      else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_IDL) {
        idlOutputParseTree(((Cons*)(ocode)));
        ocode = NIL;
      }
      else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA) {
        javaOutputParseTree(((Cons*)(ocode)));
        ocode = NIL;
      }
      else if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP) ||
          (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP_STANDALONE)) {
        cppOutputParseTree(((Cons*)(ocode)));
        ocode = NIL;
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      { TranslationUnit* unit = NULL;
        Cons* iter000 = oTRANSLATIONUNITSo->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          unit = ((TranslationUnit*)(iter000->value));
          unit->free();
        }
      }
      oTRANSLATIONUNITSo->clear();
      if (toplevelinvocationP) {
        sweepTransients();
      }
      summarizeTranslationErrors();
      return (ocode);
    }
  }
}

// Table mapping local variable names their declared types
// (declared explicitly or implicitly).
DEFINE_STELLA_SPECIAL(oLOCALVARIABLETYPETABLEo, KeyValueList* , NULL);

// Contains the method or function being walked, or else `null'.
DEFINE_STELLA_SPECIAL(oMETHODBEINGWALKEDo, MethodSlot* , NULL);

// Indicates that one or more return statements have been found
// during the walk of the current method.
DEFINE_STELLA_SPECIAL(oFOUNDRETURNpo, boolean , false);

// Bound to the target type for an expression currently walked.
// Used instead of an extra argument to `walk-a-tree', since only a few types
// of expressions need to know about their expected type (e.g., FUNCALL).
DEFINE_STELLA_SPECIAL(oTARGETTYPEo, StandardObject* , NULL);

// Table that maps each prefix of a function-local gensym
// to its own gensym counter and/or to related gensyms.
DEFINE_STELLA_SPECIAL(oLOCALGENSYMTABLEo, KeyValueList* , NULL);

DEFINE_STELLA_SPECIAL(oTRANSLATIONERRORSo, int , 0);

DEFINE_STELLA_SPECIAL(oTRANSLATIONWARNINGSo, int , 0);

DEFINE_STELLA_SPECIAL(oTRANSLATIONNOTESo, int , 0);

void resetTranslationErrors() {
  oTRANSLATIONERRORSo = 0;
  oTRANSLATIONWARNINGSo = 0;
  oTRANSLATIONNOTESo = 0;
}

void signalTranslationError() {
  oTRANSLATIONERRORSo = oTRANSLATIONERRORSo + 1;
}

void signalTranslationWarning() {
  oTRANSLATIONWARNINGSo = oTRANSLATIONWARNINGSo + 1;
}

void signalTranslationNote() {
  oTRANSLATIONNOTESo = oTRANSLATIONNOTESo + 1;
}

boolean ignoreTranslationErrorsP() {
  return (oIGNORETRANSLATIONERRORSpo);
}

boolean translationErrorsP() {
  return ((oTRANSLATIONERRORSo > 0) &&
      (!ignoreTranslationErrorsP()));
}

void summarizeTranslationErrors() {
  if (oTRANSLATIONERRORSo > 0) {
    std::cout << oTRANSLATIONERRORSo << " error";
    if (oTRANSLATIONERRORSo > 1) {
      std::cout << "s";
    }
  }
  if (oTRANSLATIONWARNINGSo > 0) {
    if (oTRANSLATIONERRORSo > 0) {
      std::cout << ", ";
    }
    std::cout << oTRANSLATIONWARNINGSo << " warning";
    if (oTRANSLATIONWARNINGSo > 1) {
      std::cout << "s";
    }
  }
  if (oTRANSLATIONNOTESo > 0) {
    if ((oTRANSLATIONERRORSo > 0) ||
        (oTRANSLATIONWARNINGSo > 0)) {
      std::cout << ", ";
    }
    std::cout << oTRANSLATIONNOTESo << " note";
    if (oTRANSLATIONNOTESo > 1) {
      std::cout << "s";
    }
  }
  if ((oTRANSLATIONERRORSo > 0) ||
      ((oTRANSLATIONWARNINGSo > 0) ||
       (oTRANSLATIONNOTESo > 0))) {
    std::cout << "." << std::endl;
  }
}

void printErrorContext(const char* prefix, OutputStream* stream) {
  *(stream->nativeStream) << prefix << "While ";
  if (((boolean)(oTRANSLATIONPHASEo))) {
    if (oTRANSLATIONPHASEo == KWD_WALK_DEFINE) {
      *(stream->nativeStream) << "defining ";
    }
    else if (oTRANSLATIONPHASEo == KWD_WALK_FINALIZE) {
      *(stream->nativeStream) << "finalizing ";
    }
    else if (oTRANSLATIONPHASEo == KWD_WALK_WALK) {
      *(stream->nativeStream) << "walking ";
    }
    else if (oTRANSLATIONPHASEo == KWD_WALK_TRANSLATE) {
      *(stream->nativeStream) << "translating ";
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << oTRANSLATIONPHASEo << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
  else {
    *(stream->nativeStream) << "processing ";
  }
  if (((boolean)(oCURRENTTRANSLATIONUNITo))) {
    { Object* object = oCURRENTTRANSLATIONUNITo->theObject;
      Symbol* category = oCURRENTTRANSLATIONUNITo->category;

      if (category == SYM_WALK_STELLA_CLASS) {
        *(stream->nativeStream) << "class ";
        if (subtypeOfClassP(safePrimaryType(object))) {
          { Object* object000 = object;
            Class* object = ((Class*)(object000));

            *(stream->nativeStream) << object->name();
          }
        }
        else {
          *(stream->nativeStream) << object;
        }
      }
      else if (category == SYM_WALK_STELLA_SLOT) {
        *(stream->nativeStream) << "external slot ";
        { Surrogate* testValue000 = safePrimaryType(object);

          if (testValue000 == SGT_WALK_STELLA_CONS) {
            { Object* object001 = object;
              Cons* object = ((Cons*)(object001));

              *(stream->nativeStream) << object->rest->value << "." << object->rest->rest->value;
            }
          }
          else if (subtypeOfStorageSlotP(testValue000)) {
            { Object* object002 = object;
              StorageSlot* object = ((StorageSlot*)(object002));

              *(stream->nativeStream) << object->slotOwner << "." << object->slotName->symbolName;
            }
          }
          else {
            { OutputStringStream* stream001 = newOutputStringStream();

              *(stream001->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
              throw *newStellaException(stream001->theStringReader());
            }
          }
        }
      }
      else if ((category == SYM_WALK_STELLA_METHOD) ||
          (category == SYM_WALK_STELLA_PRINT_METHOD)) {
        { Surrogate* testValue001 = safePrimaryType(object);

          if (subtypeOfMethodSlotP(testValue001)) {
            { Object* object003 = object;
              MethodSlot* object = ((MethodSlot*)(object003));

              if (((BooleanWrapper*)(dynamicSlotValue(object->dynamicSlots, SYM_WALK_STELLA_METHOD_MACROp, FALSE_WRAPPER)))->wrapperValue) {
                *(stream->nativeStream) << "macro " << object->slotName;
              }
              else if (object->methodFunctionP) {
                *(stream->nativeStream) << "function " << object->slotName;
              }
              else {
                *(stream->nativeStream) << "method " << object->slotOwner << "." << object->slotName->symbolName;
              }
            }
          }
          else if (testValue001 == SGT_WALK_STELLA_CONS) {
            { Object* object004 = object;
              Cons* object = ((Cons*)(object004));

              { GeneralizedSymbol* testValue002 = ((GeneralizedSymbol*)(object->value));

                if (testValue002 == SYM_WALK_STELLA_DEFMETHOD) {
                  *(stream->nativeStream) << "method ";
                }
                else if (testValue002 == SYM_WALK_STELLA_DEFUN) {
                  *(stream->nativeStream) << "function ";
                }
                else {
                }
              }
              *(stream->nativeStream) << ((consP(object->rest->value) ? ((Cons*)(object->rest->value))->value : object->rest->value));
            }
          }
          else {
            { OutputStringStream* stream002 = newOutputStringStream();

              *(stream002->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
              throw *newStellaException(stream002->theStringReader());
            }
          }
        }
      }
      else if (category == SYM_WALK_STELLA_GLOBAL_VARIABLE) {
        { Surrogate* testValue003 = safePrimaryType(object);

          if (subtypeOfP(testValue003, SGT_WALK_STELLA_GLOBAL_VARIABLE)) {
            { Object* object005 = object;
              GlobalVariable* object = ((GlobalVariable*)(object005));

              if (object->variableConstantP) {
                *(stream->nativeStream) << "constant ";
              }
              else {
                if (object->variableSpecialP) {
                  *(stream->nativeStream) << "special variable ";
                }
                else {
                  *(stream->nativeStream) << "global variable ";
                }
              }
              *(stream->nativeStream) << object->variableName;
            }
          }
          else if (testValue003 == SGT_WALK_STELLA_CONS) {
            { Object* object006 = object;
              Cons* object = ((Cons*)(object006));

              *(stream->nativeStream) << object->value << " " << object->rest->value;
            }
          }
          else {
            { OutputStringStream* stream003 = newOutputStringStream();

              *(stream003->nativeStream) << "`" << testValue003 << "'" << " is not a valid case option";
              throw *newStellaException(stream003->theStringReader());
            }
          }
        }
      }
      else if (category == SYM_WALK_STELLA_TYPE) {
        *(stream->nativeStream) << "type ";
        { Surrogate* testValue004 = safePrimaryType(object);

          if (testValue004 == SGT_WALK_STELLA_CONS) {
            { Object* object007 = object;
              Cons* object = ((Cons*)(object007));

              *(stream->nativeStream) << object->rest->value;
            }
          }
          else if (subtypeOfP(testValue004, SGT_WALK_STELLA_TYPE_SPEC)) {
            { Object* object008 = object;
              StandardObject* object = ((StandardObject*)(object008));

              *(stream->nativeStream) << yieldTypeSpecTree(object);
            }
          }
          else {
            { OutputStringStream* stream004 = newOutputStringStream();

              *(stream004->nativeStream) << "`" << testValue004 << "'" << " is not a valid case option";
              throw *newStellaException(stream004->theStringReader());
            }
          }
        }
      }
      else if (category == SYM_WALK_STELLA_MODULE) {
        *(stream->nativeStream) << "module ";
        { Surrogate* testValue005 = safePrimaryType(object);

          if (subtypeOfP(testValue005, SGT_WALK_STELLA_MODULE)) {
            { Object* object009 = object;
              Module* object = ((Module*)(object009));

              *(stream->nativeStream) << object->moduleName;
            }
          }
          else if (testValue005 == SGT_WALK_STELLA_CONS) {
            { Object* object010 = object;
              Cons* object = ((Cons*)(object010));

              *(stream->nativeStream) << object->rest->value;
            }
          }
          else {
            { OutputStringStream* stream005 = newOutputStringStream();

              *(stream005->nativeStream) << "`" << testValue005 << "'" << " is not a valid case option";
              throw *newStellaException(stream005->theStringReader());
            }
          }
        }
      }
      else {
        *(stream->nativeStream) << category;
      }
    }
  }
  else {
    *(stream->nativeStream) << "top-level statement";
  }
  *(stream->nativeStream) << ":";
}

// The current log file to which function calls should be logged.
// A non-NULL value indicates that function call logging is enabled.
OutputStream* oFUNCTION_CALL_LOG_STREAMo = NULL;

// Translation switch which indicates that methods should
// be instrumented to log their calls to a file.
boolean oLOG_FUNCTION_CALLSpo = false;

boolean logFunctionCallP(MethodSlot* method) {
  if (oLOG_FUNCTION_CALLSpo &&
      ((!((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_SLOT_AUXILIARYp, FALSE_WRAPPER)))->wrapperValue) &&
       (!((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_GLOBALLY_INLINEp, FALSE_WRAPPER)))->wrapperValue))) {
    { Symbol* testValue000 = method->slotName;

      if ((testValue000 == SYM_WALK_STELLA_LOG_FUNCTION_CALL) ||
          ((testValue000 == SYM_WALK_STELLA_START_FUNCTION_CALL_LOGGING) ||
           ((testValue000 == SYM_WALK_STELLA_STOP_FUNCTION_CALL_LOGGING) ||
            ((testValue000 == SYM_WALK_STELLA_SET_CALL_LOG_BREAK_POINT) ||
             ((testValue000 == SYM_WALK_STELLA_BREAK_PROGRAM) ||
              ((testValue000 == SYM_WALK_STELLA_TERMINATE_PROGRAM) ||
               ((testValue000 == SYM_WALK_STELLA_PO) ||
                ((testValue000 == SYM_WALK_STELLA_DEFINEDp) ||
                 ((testValue000 == SYM_WALK_STELLA_NULLp) ||
                  ((testValue000 == SYM_WALK_STELLA_EQp) ||
                   ((testValue000 == SYM_WALK_STELLA_EQLp) ||
                    ((testValue000 == SYM_WALK_STELLA_l) ||
                     ((testValue000 == SYM_WALK_STELLA_le) ||
                      ((testValue000 == SYM_WALK_STELLA_g) ||
                       ((testValue000 == SYM_WALK_STELLA_ge) ||
                        (testValue000 == SYM_WALK_STELLA_CAST)))))))))))))))) {
        return (false);
      }
      else {
        { boolean testValue001 = false;

          if (method->methodParameterTypeSpecifiers_reader()->memberP(SGT_WALK_STELLA_UNKNOWN)) {
            testValue001 = true;
          }
          else {
            if (method->methodParameterTypeSpecifiers_reader()->memberP(SGT_WALK_STELLA_LISP_CODE)) {
              testValue001 = true;
            }
            else {
              if (method->methodReturnTypeSpecifiers_reader()->memberP(SGT_WALK_STELLA_UNKNOWN)) {
                testValue001 = true;
              }
              else {
                if (method->methodReturnTypeSpecifiers_reader()->memberP(SGT_WALK_STELLA_LISP_CODE)) {
                  testValue001 = true;
                }
                else {
                  {
                    { boolean foundP000 = false;

                      { StandardObject* tspec = NULL;
                        Cons* iter000 = method->methodParameterTypeSpecifiers_reader()->theConsList;

                        for (; !(iter000 == NIL); iter000 = iter000->rest) {
                          tspec = ((StandardObject*)(iter000->value));
                          if (subTypeSpecOfP(tspec, SGT_WALK_STELLA_OUTPUT_STREAM)) {
                            foundP000 = true;
                            break;
                          }
                        }
                      }
                      testValue001 = foundP000;
                    }
                    if (!testValue001) {
                      { boolean foundP001 = false;

                        { StandardObject* tspec = NULL;
                          Cons* iter001 = method->methodParameterTypeSpecifiers_reader()->theConsList;

                          for (; !(iter001 == NIL); iter001 = iter001->rest) {
                            tspec = ((StandardObject*)(iter001->value));
                            if (subTypeSpecOfP(tspec, SGT_WALK_STELLA_NATIVE_OUTPUT_STREAM)) {
                              foundP001 = true;
                              break;
                            }
                          }
                        }
                        testValue001 = foundP001;
                      }
                      if (!testValue001) {
                        testValue001 = (oCURRENTFILENAMEo != NULL) &&
                            ((stringSearch(oCURRENTFILENAMEo, "cl-primal", 0) != NULL_INTEGER) ||
                             (stringSearch(oCURRENTFILENAMEo, "stella-to-cl", 0) != NULL_INTEGER));
                      }
                    }
                  }
                }
              }
            }
          }
          if (testValue001) {
            return (false);
          }
        }
      }
    }
    return (true);
  }
  return (false);
}

Cons* wrapBodyWithLogFunctionCallTree(MethodSlot* method, Cons* body) {
  if (consP(body->value) &&
      (!(((Cons*)(body->value))->value == SYM_WALK_STELLA_INLINE))) {
    return (cons(listO(3, SYM_WALK_STELLA_LOG_FUNCTION_CALL, wrapString(stringify(method)), NIL), body->concatenate(NIL, 0)));
  }
  else {
    return (body);
  }
}

int oLOG_BREAK_POINT_COUNTERo = NULL_INTEGER;

void logFunctionCall(const char* name) {
  if (!(oFUNCTION_CALL_LOG_STREAMo == NULL)) {
    *(oFUNCTION_CALL_LOG_STREAMo->nativeStream) << name << std::endl;
  }
  if (oLOG_BREAK_POINT_COUNTERo != NULL_INTEGER) {
    oLOG_BREAK_POINT_COUNTERo = oLOG_BREAK_POINT_COUNTERo - 1;
    if (oLOG_BREAK_POINT_COUNTERo == 0) {
      oLOG_BREAK_POINT_COUNTERo = NULL_INTEGER;
      breakProgram("Call log break point");
    }
  }
}

void startFunctionCallLogging(const char* filename) {
  // Start function call logging to `fileName'.
  { OutputStream* currentlogstream = oFUNCTION_CALL_LOG_STREAMo;

    oFUNCTION_CALL_LOG_STREAMo = NULL;
    if (((boolean)(currentlogstream))) {
      currentlogstream->free();
    }
    oFUNCTION_CALL_LOG_STREAMo = newOutputFileStream(filename);
  }
}

void startFunctionCallLoggingEvaluatorWrapper(Cons* arguments) {
  startFunctionCallLogging(((StringWrapper*)(arguments->value))->wrapperValue);
}

void stopFunctionCallLogging() {
  // Stop function call logging and close the current log file.
  { OutputStream* currentlogstream = oFUNCTION_CALL_LOG_STREAMo;

    oFUNCTION_CALL_LOG_STREAMo = NULL;
    if (((boolean)(currentlogstream))) {
      currentlogstream->free();
    }
  }
}

void setCallLogBreakPoint(int count) {
  // Set a call log break point to `count'.  Execution will be
  // interrupted right at the entry of the `count'th logged function call.
  oLOG_BREAK_POINT_COUNTERo = count;
}

void setCallLogBreakPointEvaluatorWrapper(Cons* arguments) {
  setCallLogBreakPoint(((IntegerWrapper*)(arguments->value))->wrapperValue);
}

void breakProgram(const char* message) {
  // Interrupt the program and print `message'.  Continue after
  // confirmation with the user.
  {
    std::cout << "Program break: " << message << std::endl << std::endl;
    if (!yesOrNoP("Continue?")) {
      terminateProgram();
    }
  }
}

void breakProgramEvaluatorWrapper(Cons* arguments) {
  breakProgram(((StringWrapper*)(arguments->value))->wrapperValue);
}

void terminateProgram() {
  // Terminate and exit the program with normal exit code.
  exit(0);;
}

void po(Object* thing) {
  std::cout << thing << std::endl;
}

boolean variableEqlP(Symbol* var1, Symbol* var2) {
  return ((var1 == var2) ||
      stringEqlP(var1->symbolName, var2->symbolName));
}

Object* lookupVariableTable(KeyValueList* self, Symbol* variable) {
  { Symbol* key = NULL;
    Object* value = NULL;
    KvCons* iter000 = self->theKvList;

    for  (; ((boolean)(iter000)); 
          iter000 = iter000->rest) {
      key = ((Symbol*)(iter000->key));
      value = iter000->value;
      if (variableEqlP(key, variable)) {
        return (value);
      }
    }
  }
  return (NULL);
}

void insertAtVariableTable(KeyValueList* self, Symbol* variable, Object* value) {
  { KvCons* cursor = self->theKvList;

    while (((boolean)(cursor))) {
      if (variableEqlP(((Symbol*)(cursor->key)), variable)) {
        cursor->value = value;
        return;
      }
      cursor = cursor->rest;
    }
    self->theKvList = kvCons(variable, value, self->theKvList);
  }
}

void pushVariableBinding(Symbol* variable, StandardObject* type) {
  { Class* clasS = typeSpecToClass(type);

    if (!((boolean)(variable))) {
      return;
    }
    if ((!((boolean)(clasS))) &&
        (!(type == SGT_WALK_STELLA_UNINITIALIZED))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "No class defined for type: " << "`" << typeSpecToBaseType(type) << "'" << "." << std::endl;
        }
      }
      type = SGT_WALK_STELLA_UNKNOWN;
    }
    if ((!((!translateToSingleInheritanceLanguageP()) ||
        (!(oMIXIN_IMPLEMENTATION_STYLEo == KWD_WALK_SECOND_CLASS)))) &&
        (((boolean)(clasS)) &&
         (clasS->mixinP &&
          ((!((boolean)(oMETHODBEINGWALKEDo))) ||
           ((!mixinMethodP(oMETHODBEINGWALKEDo)) ||
            oLOCALVARIABLETYPETABLEo->nonEmptyP()))))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Variable " << "`" << deUglifyParseTree(variable) << "'" << " is typed with a mixin class which is" << std::endl << " illegal when translating to a single-inheritance language" << "." << std::endl;
        }
      }
    }
    oLOCALVARIABLETYPETABLEo->theKvList = kvCons(variable, type, oLOCALVARIABLETYPETABLEo->theKvList);
    maybeRenameLocalVariable(variable);
  }
}

void popVariableBinding() {
  { KvCons* kvlist = oLOCALVARIABLETYPETABLEo->theKvList;

    oLOCALVARIABLETYPETABLEo->theKvList = kvlist->rest;
    if (subtypeOfP(safePrimaryType(kvlist->value), SGT_WALK_STELLA_KEY_VALUE_LIST)) {
      kvlist->value->free();
    }
    else {
    }
    freeKvCons(kvlist);
  }
}

StandardObject* lookupVariableType(Symbol* variablename) {
  { StandardObject* entry = (((boolean)(oLOCALVARIABLETYPETABLEo)) ? ((StandardObject*)(lookupVariableTable(oLOCALVARIABLETYPETABLEo, variablename))) : ((StandardObject*)(NULL)));
    StandardObject* type = NULL;

    if (!((boolean)(entry))) {
      if (variablename == SYM_WALK_STELLA_NULL) {
        return (SGT_WALK_STELLA_UNKNOWN);
      }
      type = lookupGlobalVariableType(variablename);
      registerReferenceToGlobalVariable(variablename);
    }
    else {
      if (subtypeOfP(safePrimaryType(entry), SGT_WALK_STELLA_KEY_VALUE_LIST)) {
        { StandardObject* entry000 = entry;
          KeyValueList* entry = ((KeyValueList*)(entry000));

          type = ((StandardObject*)(entry->lookup(KWD_WALK_TYPE)));
        }
      }
      else {
        type = entry;
      }
    }
    if (!((boolean)(type))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Undeclared variable " << "`" << deUglifyParseTree(variablename) << "'" << "." << std::endl;
        }
      }
      return (SGT_WALK_STELLA_UNKNOWN);
    }
    if (type == SGT_WALK_STELLA_UNINITIALIZED) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Reference to defined but uninitialized variable " << "`" << deUglifyParseTree(variablename) << "'" << "." << std::endl;
        }
      }
      return (SGT_WALK_STELLA_UNKNOWN);
    }
    return (type);
  }
}

void setLocalVariableInfo(Symbol* variable, Keyword* key, Object* info) {
  { StandardObject* entry = ((StandardObject*)(lookupVariableTable(oLOCALVARIABLETYPETABLEo, variable)));

    if (((boolean)(entry))) {
      if (subtypeOfP(safePrimaryType(entry), SGT_WALK_STELLA_KEY_VALUE_LIST)) {
        { StandardObject* entry000 = entry;
          KeyValueList* entry = ((KeyValueList*)(entry000));

          entry->insertAt(key, info);
        }
      }
      else {
        { KeyValueList* variableinfo = newKeyValueList();

          variableinfo->insertAt(key, info);
          variableinfo->insertAt(KWD_WALK_TYPE, entry);
          insertAtVariableTable(oLOCALVARIABLETYPETABLEo, variable, variableinfo);
        }
      }
    }
  }
}

Object* getLocalVariableInfo(Symbol* variable, Keyword* key) {
  { StandardObject* entry = (((boolean)(oLOCALVARIABLETYPETABLEo)) ? ((StandardObject*)(lookupVariableTable(oLOCALVARIABLETYPETABLEo, variable))) : ((StandardObject*)(NULL)));

    if (((boolean)(entry))) {
      if (subtypeOfP(safePrimaryType(entry), SGT_WALK_STELLA_KEY_VALUE_LIST)) {
        { StandardObject* entry000 = entry;
          KeyValueList* entry = ((KeyValueList*)(entry000));

          return (entry->lookup(key));
        }
      }
      else {
        if (key == KWD_WALK_TYPE) {
          return (entry);
        }
      }
    }
    return (NULL);
  }
}

void registerReferenceToGlobalVariable(Symbol* variablename) {
  if (((boolean)(oCURRENTTRANSLATIONUNITo))) {
    { GlobalVariable* global = variablename->lookupGlobalVariable();
      List* referencedglobals = oCURRENTTRANSLATIONUNITo->referencedGlobals;

      if (((boolean)(global)) &&
          (!referencedglobals->memberP(global))) {
        referencedglobals->insert(global);
      }
    }
  }
}

Symbol* localGensym(const char* prefix) {
  if (!((boolean)(oLOCALGENSYMTABLEo))) {
    return (gensym(prefix));
  }
  { IntegerWrapper* prefixcounter = ((IntegerWrapper*)(oLOCALGENSYMTABLEo->lookup(wrapString(prefix))));

    if (!((boolean)(prefixcounter))) {
      prefixcounter = wrapInteger(0);
    }
    else {
      prefixcounter = wrapInteger(prefixcounter->wrapperValue + 1);
    }
    oLOCALGENSYMTABLEo->insertAt(wrapString(prefix), prefixcounter);
    return (internTransientSymbol(yieldGensymName(prefix, prefixcounter->wrapperValue)));
  }
}

Symbol* methodGensym(const char* prefix) {
  { MethodSlot* method = oMETHODBEINGWALKEDo;
    boolean localP = false;

    if (((boolean)(method))) {
      if (method->methodFunctionP) {
        prefix = stringConcatenate("F-", method->slotName->symbolName, 2, "-", prefix);
      }
      else {
        prefix = stringConcatenate("M-", method->slotOwner->symbolName, 4, ".", method->slotName->symbolName, "-", prefix);
      }
      localP = true;
    }
    if (localP) {
      return (localGensym(prefix));
    }
    else {
      return (gensym(prefix));
    }
  }
}

Symbol* yieldLocalVariableAlias(Symbol* variable, int level) {
  if (!(level >= 1)) {
    std::cerr << "Safety violation: " << "INTERNAL ERROR: Variable level must be >= 1";
  }
  if (!((boolean)(oLOCALGENSYMTABLEo))) {
    return (localGensym(variable->symbolName));
  }
  { Cons* aliases = ((Cons*)(oLOCALGENSYMTABLEo->lookup(variable)));
    Symbol* alias = NULL;

    if (!((boolean)(aliases))) {
      aliases = NIL;
    }
    if (aliases->length() < level) {
      alias = localGensym(variable->symbolName);
      oLOCALGENSYMTABLEo->insertAt(variable, aliases->concatenate(cons(alias, NIL), 0));
      return (alias);
    }
    else {
      return (((Symbol*)(aliases->nth(level - 1))));
    }
  }
}

boolean renameShadowingLocalVariablesP() {
  return (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA);
}

void maybeRenameLocalVariable(Symbol* variable) {
  if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA) {
    { KvCons* cursor = oLOCALVARIABLETYPETABLEo->theKvList;
      int level = -1;

      while (((boolean)(cursor))) {
        if (variableEqlP(((Symbol*)(cursor->key)), variable)) {
          level = level + 1;
        }
        cursor = cursor->rest;
      }
      if (level >= 1) {
        setLocalVariableInfo(variable, KWD_WALK_ALIAS, yieldLocalVariableAlias(variable, level));
      }
    }
  }
}

Symbol* trueVariableName(Symbol* variable) {
  if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA) {
    { Object* alias = getLocalVariableInfo(variable, KWD_WALK_ALIAS);

      if (((boolean)(alias))) {
        return (((Symbol*)(alias)));
      }
    }
  }
  return (variable);
}

boolean suppressWarningsP() {
  return (oCURRENT_STELLA_FEATURESo->memberP(KWD_WALK_SUPPRESS_WARNINGS));
}

boolean badArgumentRangeP(Cons* tree, int minarity, int maxarity) {
  { int argnum = tree->length() - 1;

    if (argnum < minarity) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing arguments in the expression: " << std::endl << " " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
        }
      }
      return (true);
    }
    else if ((maxarity != NULL_INTEGER) &&
        (argnum > maxarity)) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Too many arguments in the expression: " << std::endl << " " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
        }
      }
      return (true);
    }
    else {
      return (false);
    }
  }
}

boolean badArgumentCountP(Cons* tree, int arity) {
  return (badArgumentRangeP(tree, arity, arity));
}

Cons* yieldIllegalStatementTree() {
  { 
    BIND_STELLA_SPECIAL(oLOCALVARIABLETYPETABLEo, KeyValueList*, newKeyValueList());
    return (((Cons*)(walkWithoutTypeTree(listO(5, SYM_WALK_STELLA_ERROR, wrapString("Attempt to execute illegal statement flagged by the translator"), SYM_WALK_STELLA_EOL, wrapString("    but not yet fixed."), NIL)))));
  }
}

Object* yieldIllegalExpressionTree() {
  return (SYM_WALK_STELLA_ILLEGAL_EXPRESSION_FLAGGED_BY_THE_TRANSLATOR);
}

Cons* walkDontCallMeTree(Object* tree, StandardObject* returntype, StandardObject*& _Return1) {
  { Cons* _Return0 = listO(3, SYM_WALK_STELLA_BAD_SYS, tree, cons(typeSpecToBaseType(returntype), NIL));

    _Return1 = returntype;
    return (_Return0);
  }
}

boolean illegalTreeP(Object* tree) {
  return (consP(tree) &&
      (((Cons*)(tree))->value == SYM_WALK_STELLA_BAD_SYS));
}

boolean nativeClassMethodInliningP() {
  if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP) {
    return (false);
  }
  else if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA) ||
      ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP) ||
       ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP_STANDALONE) ||
        (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_IDL)))) {
    return (true);
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Object* prognify(Cons* trees) {
  switch (trees->length()) {
    case 0: 
      return (NIL);
    case 1: 
      { Object* tree = trees->value;

        trees->firstSetter(NULL);
        return (tree);
      }
      break;
    default:
      return (cons(SYM_WALK_STELLA_PROGN, trees->concatenate(NIL, 0)));
  }
}

Object* optimizeProgn(Cons* prognTree) {
  switch (prognTree->rest->length()) {
    case 0: 
      return (NIL);
    case 1: 
      { Object* tree = prognTree->rest->value;

        prognTree->secondSetter(NULL);
        return (tree);
      }
      break;
    default:
      return (prognTree);
  }
}

Cons* treeToTrees(Object* tree) {
  if (safePrimaryType(tree) == SGT_WALK_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if (tree->value == SYM_WALK_STELLA_PROGN) {
        return (tree->rest);
      }
    }
  }
  else {
  }
  return (cons(tree, NIL));
}

// Table of pairs used by `wrapper-value-type' and
// `type-to-wrapped-type'.
Cons* oWRAPPED_TYPE_TABLEo = NULL;

Surrogate* wrappedTypeToType(Surrogate* self) {
  // Return the unwrapped type for the wrapped type `self',
  // or `self' if it is not a wrapped type.
  { Cons* entry = NULL;
    Cons* iter000 = oWRAPPED_TYPE_TABLEo;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      entry = ((Cons*)(iter000->value));
      if (entry->value == self) {
        return (((Surrogate*)(entry->rest->value)));
      }
    }
  }
  return (self);
}

Surrogate* wrapperValueType(Wrapper* self) {
  // Return the type of the value stored in the wrapper `self'.
  { Surrogate* wrappertype = self->primaryType();
    Surrogate* valuetype = wrappedTypeToType(wrappertype);

    if (valuetype == wrappertype) {
      throw *newStellaException("Missing *wrapped-type-table* entry");
    }
    else {
      return (valuetype);
    }
  }
}

Surrogate* Surrogate::typeToWrappedType() {
  // Return the wrapped type for the type `self',
  // or 'self' if it is not a bare literal type.
  { Surrogate* self = this;

    if (!((boolean)(((Class*)(self->surrogateValue))))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Can't find a class named " << "`" << deUglifyParseTree(self) << "'" << "." << std::endl;
        }
      }
      return (SGT_WALK_STELLA_UNKNOWN);
    }
    if (subtypeOfP(self, SGT_WALK_STELLA_OBJECT)) {
      return (self);
    }
    { Cons* entry = NULL;
      Cons* iter000 = oWRAPPED_TYPE_TABLEo;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        entry = ((Cons*)(iter000->value));
        if (entry->rest->value == self) {
          return (((Surrogate*)(entry->value)));
        }
      }
    }
    { Surrogate* realtype = ((Class*)(self->surrogateValue))->classType;

      if (!(self == realtype)) {
        { Cons* entry = NULL;
          Cons* iter001 = oWRAPPED_TYPE_TABLEo;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            entry = ((Cons*)(iter001->value));
            if (entry->rest->value == realtype) {
              return (((Surrogate*)(entry->value)));
            }
          }
        }
      }
    }
    return (NULL);
  }
}

// Table of triples used by `lookup-coersion-method' to
// locate a coersion method.
Cons* oCOERSION_TABLEo = NULL;

Object* lookupCoersionMethod(Surrogate* sourcetype, Surrogate* targettype, Object* expression) {
  expression = expression;
  sourcetype = canonicalType(sourcetype);
  { Cons* triple = NULL;
    Cons* iter000 = oCOERSION_TABLEo;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      triple = ((Cons*)(iter000->value));
      if (subtypeOfP(sourcetype, ((Surrogate*)(triple->value))) &&
          subtypeOfP(((Surrogate*)(triple->rest->value)), targettype)) {
        return (triple->rest->rest->value);
      }
    }
  }
  return (NULL);
}

Object* applyCoercionMethod(Object* expression, Surrogate* sourcetype, Surrogate* targettype, Object* coercionmethod, StandardObject*& _Return1) {
  if (!((boolean)(coercionmethod))) {
    coercionmethod = lookupCoersionMethod(sourcetype, targettype, expression);
  }
  if (!((boolean)(coercionmethod))) {
    _Return1 = sourcetype;
    return (expression);
  }
  if (coercionmethod == SYM_WALK_STELLA_IDENTITY) {
    _Return1 = targettype;
    return (expression);
  }
  { Surrogate* testValue000 = safePrimaryType(coercionmethod);

    if (subtypeOfSymbolP(testValue000)) {
      { Object* coercionmethod000 = coercionmethod;
        Symbol* coercionmethod = ((Symbol*)(coercionmethod000));

        return (walkExpressionTree(cons(coercionmethod, cons(expression, NIL)), targettype, coercionmethod, false, _Return1));
      }
    }
    else if (testValue000 == SGT_WALK_STELLA_CONS) {
      { Object* coercionmethod001 = coercionmethod;
        Cons* coercionmethod = ((Cons*)(coercionmethod001));

        return (walkExpressionTree(copyConsTree(substituteConsTree(((Cons*)(copyConsTree(coercionmethod))), expression, SYM_WALK_STELLA_lXg)), targettype, ((Symbol*)(coercionmethod->value)), false, _Return1));
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

boolean translatingCodeP() {
  return ((oTRANSLATIONPHASEo == KWD_WALK_WALK) ||
      (oTRANSLATIONPHASEo == KWD_WALK_TRANSLATE));
}

Surrogate* verifyType(Surrogate* self) {
  if (((boolean)(self->surrogateValue)) &&
      (!stellaClassP(self->surrogateValue))) {
    *(STANDARD_WARNING->nativeStream) << "Warning: " << "Illegal object " << "`" << self->surrogateValue << "'" << " found" << std::endl << "   where STELLA class expected" << std::endl << std::endl;
    self->surrogateValue = ((Class*)(SGT_WALK_STELLA_UNKNOWN->surrogateValue));
  }
  if (translatingCodeP() &&
      ((!((boolean)(((Class*)(self->surrogateValue))))) ||
       (((Class*)(self->surrogateValue)) == ((Class*)(SGT_WALK_STELLA_UNKNOWN->surrogateValue))))) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationWarning();
      if (!(suppressWarningsP())) {
        printErrorContext(">> WARNING: ", STANDARD_WARNING);
        *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Reference to undefined class " << "`" << self->symbolName << "'" << "." << std::endl;
      }
    }
    self->surrogateValue = ((Class*)(SGT_WALK_STELLA_UNKNOWN->surrogateValue));
  }
  return (self);
}

boolean safeSubtypeOfP(Surrogate* subtype, Surrogate* supertype) {
  verifyType(subtype);
  verifyType(supertype);
  return (subtypeOfP(subtype, supertype));
}

void warnAboutUnknownSourceType(Object* tree) {
  if (warnAboutUndefinedMethodsP()) {
    { Surrogate* testValue000 = safePrimaryType(tree);

      if (subtypeOfSymbolP(testValue000)) {
        { Object* tree000 = tree;
          Symbol* tree = ((Symbol*)(tree000));

          return;
        }
      }
      else if (testValue000 == SGT_WALK_STELLA_CONS) {
        { Object* tree001 = tree;
          Cons* tree = ((Cons*)(tree001));

          { GeneralizedSymbol* testValue001 = ((GeneralizedSymbol*)(tree->value));

            if ((testValue001 == SYM_WALK_STELLA_VERBATIM) ||
                (testValue001 == SYM_WALK_STELLA_VRLET)) {
              return;
            }
            else if (testValue001 == SYM_WALK_STELLA_SYS_CALL_METHOD) {
              if (symbolCommonLispP(((Symbol*)(tree->rest->rest->value))) ||
                  (!((boolean)(lookupSlot(((Class*)(((Surrogate*)(tree->rest->value))->surrogateValue)), ((Symbol*)(tree->rest->rest->value))))))) {
                return;
              }
            }
            else if (testValue001 == SYM_WALK_STELLA_SYS_CALL_FUNCTION) {
              if (lookupFunction(((Symbol*)(tree->rest->value)))->slotBaseType == SGT_WALK_STELLA_UNKNOWN) {
                return;
              }
            }
            else if ((testValue001 == SYM_WALK_STELLA_TYPED_SYS) ||
                (testValue001 == SYM_WALK_STELLA_SYS_INLINE_CALL)) {
              warnAboutUnknownSourceType(tree->rest->value);
              return;
            }
            else {
            }
          }
        }
      }
      else {
        if (!((boolean)(tree))) {
          return;
        }
      }
    }
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "The expression" << std::endl << "   " << "`" << deUglifyParseTree(tree) << "'" << std::endl << " has UNKNOWN type" << "." << std::endl;
      }
    }
  }
}

Object* coerceATree(Object* tree, StandardObject* sourcetype, StandardObject* targettype, StandardObject*& _Return1) {
  { Object* otree = NULL;
    StandardObject* otype = NULL;
    boolean coercibleP = false;

    otree = helpCoerceATree(tree, sourcetype, targettype, false, otype, coercibleP);
    if (!(coercibleP)) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Type conflict: the expression:" << std::endl << "   " << "`" << deUglifyParseTree(tree) << "'" << std::endl << " has type " << "`" << yieldTypeSpecTree(sourcetype) << "'" << " but should have type " << "`" << yieldTypeSpecTree(targettype) << "'" << "." << std::endl;
        }
      }
    }
    _Return1 = otype;
    return (otree);
  }
}

Object* helpCoerceATree(Object* tree, StandardObject* sourcetype, StandardObject* targettype, boolean testonlyP, StandardObject*& _Return1, boolean& _Return2) {
  { StandardObject* dummy1;
    StandardObject* dummy2;

    { Object* coersionfunction = NULL;
      Surrogate* realsourcetype = targetLanguageType(tree);
      Surrogate* sourcebasetype = typeSpecToBaseType(sourcetype);
      Surrogate* targetbasetype = typeSpecToBaseType(targettype);

      if (sourcetype == SGT_WALK_STELLA_UNKNOWN) {
        warnAboutUnknownSourceType(tree);
        if ((tree == SYM_WALK_STELLA_NULL) &&
            ((boolean)(targetbasetype))) {
          { Object* _Return0 = typeToWalkedNullValueTree(targettype, targetbasetype);

            _Return1 = targettype;
            _Return2 = true;
            return (_Return0);
          }
        }
        else {
          _Return1 = targettype;
          _Return2 = true;
          return (tree);
        }
      }
      if (((boolean)(realsourcetype))) {
        setTargetLanguageType(((Cons*)(tree)), NULL, dummy1);
        tree = coerceATree(tree, realsourcetype, sourcetype, dummy2);
      }
      if (targettype == SGT_WALK_STELLA_UNKNOWN) {
        _Return1 = sourcetype;
        _Return2 = true;
        return (tree);
      }
      if (!((boolean)(((Class*)(sourcebasetype->surrogateValue))))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "No class defined for type: " << "`" << deUglifyParseTree(sourcebasetype) << "'" << "." << std::endl;
          }
        }
        _Return1 = targettype;
        _Return2 = true;
        return (tree);
      }
      if (((boolean)(targetbasetype)) &&
          (!((boolean)(((Class*)(targetbasetype->surrogateValue)))))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "No class defined for type: " << "`" << deUglifyParseTree(targetbasetype) << "'" << "." << std::endl;
          }
        }
        _Return1 = sourcetype;
        _Return2 = true;
        return (tree);
      }
      if (subTypeSpecOfP(sourcetype, targettype)) {
        _Return1 = sourcetype;
        _Return2 = true;
        return (tree);
      }
      if (((boolean)(targetbasetype)) &&
          (compatibleParameterTypesP(sourcetype, targettype) ||
           ((!arrayTypeSpecifierP(sourcetype)) &&
            (subtypeOfP(targetbasetype, sourcebasetype) &&
             compatibleParameterTypesP(targettype, sourcetype))))) {
        { boolean testValue000 = false;

          testValue000 = typeP(sourcetype);
          if (testValue000) {
            { 
              coersionfunction = lookupCoersionMethod(((Surrogate*)(sourcetype)), targetbasetype, tree);
              testValue000 = ((boolean)(coersionfunction));
            }
          }
          if (testValue000) {
            if (!(testonlyP)) {
              tree = applyCoercionMethod(tree, ((Surrogate*)(sourcetype)), targetbasetype, coersionfunction, targettype);
            }
            _Return1 = targettype;
            _Return2 = true;
            return (tree);
          }
        }
        if (subtypeOfP(targetbasetype, sourcebasetype)) {
          if (testonlyP) {
            _Return1 = targettype;
            _Return2 = true;
            return (tree);
          }
          { Object* _Return0 = walkWithoutTypeTree(cons((((boolean)(realsourcetype)) ? SYM_WALK_STELLA_SAFE_CAST : SYM_WALK_STELLA_CAST), cons(tree, cons(targettype, NIL))));

            _Return1 = targettype;
            _Return2 = true;
            return (_Return0);
          }
        }
        if (subtypeOfP(targetbasetype, SGT_WALK_STELLA_NON_OBJECT) &&
            (typeP(sourcetype) &&
             subtypeOfP(SGT_WALK_STELLA_WRAPPER, ((Surrogate*)(sourcetype))))) {
          { Surrogate* wrappertype = targetbasetype->typeToWrappedType();

            if (((boolean)(wrappertype))) {
              if (testonlyP) {
                _Return1 = targettype;
                _Return2 = true;
                return (tree);
              }
              coersionfunction = lookupCoersionMethod(wrappertype, targetbasetype, tree);
              if (((boolean)(coersionfunction))) {
                tree = applyCoercionMethod(listO(3, SYM_WALK_STELLA_CAST, tree, cons(wrappertype, NIL)), ((Surrogate*)(sourcetype)), targetbasetype, coersionfunction, targettype);
                _Return1 = targettype;
                _Return2 = true;
                return (tree);
              }
            }
          }
        }
      }
      _Return1 = sourcetype;
      _Return2 = false;
      return (tree);
    }
  }
}

boolean coercibleP(Object* tree, StandardObject* sourcetype, StandardObject* targettype) {
  { Object* otree = NULL;
    StandardObject* otype = NULL;
    boolean coercibleP = false;

    otree = helpCoerceATree(tree, sourcetype, targettype, true, otype, coercibleP);
    {
      otree = otree;
      otype = otype;
    }
    return (coercibleP);
  }
}

boolean walkingExpressionP() {
  return (!(oTARGETTYPEo == SGT_WALK_STELLA_VOID));
}

Object* walkExpressionTree(Object* exptree, StandardObject* targettype, Symbol* operatorname, boolean vrletisokP, StandardObject*& _Return1) {
  { 
    BIND_STELLA_SPECIAL(oTARGETTYPEo, StandardObject*, (((boolean)(targettype)) ? ((StandardObject*)(targettype)) : SGT_WALK_STELLA_UNKNOWN));
    { Object* oexp = NULL;
      StandardObject* sourcetype = NULL;

      oexp = walkATree(exptree, sourcetype);
      if (vrletExpressionP(oexp)) {
        if (!(vrletisokP)) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal procedural expression as argument to " << "`" << deUglifyParseTree(operatorname) << "'" << ":" << std::endl << "   " << "`" << deUglifyParseTree(exptree) << "'" << "." << std::endl;
            }
          }
        }
        _Return1 = sourcetype;
        return (oexp);
      }
      if (voidP(sourcetype) &&
          (!voidP(targettype))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal argument to " << "`" << deUglifyParseTree(operatorname) << "'" << ":" << std::endl << "   " << "`" << deUglifyParseTree(oexp) << "'" << std::endl << "The argument must be an expression, not a statement" << "." << std::endl;
          }
        }
        return (walkDontCallMeTree(oexp, sourcetype, _Return1));
      }
      if (!((boolean)(sourcetype))) {
        sourcetype = SGT_WALK_STELLA_UNKNOWN;
      }
      if (!((boolean)(targettype))) {
        targettype = sourcetype;
      }
      return (coerceATree(oexp, sourcetype, targettype, _Return1));
    }
  }
}

StandardObject* computeExpressionType(Object* expression, boolean wrapP) {
  { StandardObject* dummy1;

    { Object* walkedtree = walkATree(listO(3, SYM_WALK_STELLA_LET, cons(listO(3, SYM_WALK_STELLA_X, copyConsTree(expression), NIL), NIL), NIL), dummy1);
      Object* typespec = consTreeNth(((Cons*)(walkedtree)), 4, 1, 1, 0, 1);

      if (wrapP) {
        return ((subTypeSpecOfP(((StandardObject*)(typespec)), SGT_WALK_STELLA_LITERAL) ? typeSpecToBaseType(((StandardObject*)(typespec)))->typeToWrappedType() : ((StandardObject*)(((StandardObject*)(typespec))))));
      }
      else {
        return (((StandardObject*)(typespec)));
      }
    }
  }
}

Object* walkWithoutTypeTree(Object* tree) {
  { Object* otree = NULL;
    StandardObject* unusedtypespec = NULL;

    otree = walkATree(tree, unusedtypespec);
    unusedtypespec = unusedtypespec;
    return (otree);
  }
}

Cons* walkListOfTrees(Cons* trees) {
  { Cons* cursor = trees;

    while (!(cursor == NIL)) {
      cursor->value = walkStatement(cursor->value, false);
      cursor = cursor->rest;
    }
    return (trees);
  }
}

Cons* walkListOfStatements(Cons* trees) {
  { Cons* otrees = NIL;

    { Object* otree = NULL;
      Cons* iter000 = walkListOfTrees(trees);
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        otree = iter000->value;
        if (consP(otree)) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(otree, NIL);
              if (otrees == NIL) {
                otrees = collect000;
              }
              else {
                addConsToEndOfConsList(otrees, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(otree, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    return (otrees);
  }
}

Object* walkStatement(Object* tree, boolean warnonatomP) {
  { Object* otree = NULL;
    StandardObject* unusedtypespec = NULL;

    otree = walkATree(tree, unusedtypespec);
    unusedtypespec = unusedtypespec;
    if (safePrimaryType(otree) == SGT_WALK_STELLA_CONS) {
      { Object* otree000 = otree;
        Cons* otree = ((Cons*)(otree000));

        if (otree->value == SYM_WALK_STELLA_VRLET) {
          otree = eliminateVrletStatement(otree);
        }
      }
    }
    else {
      if (warnonatomP &&
          (((boolean)(otree)) &&
           (!(otree == SYM_WALK_STELLA_NULL)))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationWarning();
          if (!(suppressWarningsP())) {
            printErrorContext(">> WARNING: ", STANDARD_WARNING);
            *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Expression found where statement expected: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
          }
        }
      }
    }
    return (otree);
  }
}

Cons* eliminateVrletStatement(Cons* tree) {
  { StandardObject* dummy1;

    tree->firstSetter(SYM_WALK_STELLA_LET);
    return (((Cons*)(walkATree(tree, dummy1))));
  }
}

Cons* sysTree(Object* tree, StandardObject* typespec, StandardObject*& _Return1) {
  if (safePrimaryType(tree) == SGT_WALK_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

        if (testValue000 == SYM_WALK_STELLA_VOID_SYS) {
          if (voidP(typespec)) {
            _Return1 = typespec;
            return (tree);
          }
        }
        else if (testValue000 == SYM_WALK_STELLA_TYPED_SYS) {
          if (tree->rest->rest->value == typespec) {
            _Return1 = typespec;
            return (tree);
          }
        }
        else if (testValue000 == SYM_WALK_STELLA_VRLET) {
          _Return1 = typespec;
          return (tree);
        }
        else {
        }
      }
    }
  }
  else {
  }
  if (voidP(typespec)) {
    { Cons* _Return0 = listO(3, SYM_WALK_STELLA_VOID_SYS, tree, NIL);

      _Return1 = SGT_WALK_STELLA_VOID;
      return (_Return0);
    }
  }
  else {
    { Cons* _Return0 = listO(3, SYM_WALK_STELLA_TYPED_SYS, tree, cons(typespec, NIL));

      _Return1 = typespec;
      return (_Return0);
    }
  }
}

StandardObject* walkedExpressionType(Object* tree) {
  { Surrogate* testValue000 = safePrimaryType(tree);

    if (testValue000 == SGT_WALK_STELLA_CONS) {
      { Object* tree000 = tree;
        Cons* tree = ((Cons*)(tree000));

        if (tree->value == SYM_WALK_STELLA_TYPED_SYS) {
          return (((StandardObject*)(tree->rest->rest->value)));
        }
      }
    }
    else if (subtypeOfWrapperP(testValue000)) {
      { Object* tree001 = tree;
        Wrapper* tree = ((Wrapper*)(tree001));

        return (wrappedTypeToType(tree->primaryType()));
      }
    }
    else {
    }
  }
  return (SGT_WALK_STELLA_UNKNOWN);
}

Object* walkedExpressionExpression(Object* tree) {
  if (safePrimaryType(tree) == SGT_WALK_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

        if ((testValue000 == SYM_WALK_STELLA_VOID_SYS) ||
            (testValue000 == SYM_WALK_STELLA_TYPED_SYS)) {
          return (tree->rest->value);
        }
        else {
        }
      }
    }
  }
  else {
  }
  return (tree);
}

boolean needIdenticalMethodSignaturesP() {
  if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP) ||
      ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP_STANDALONE) ||
       (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA))) {
    return (true);
  }
  else {
    return (false);
  }
}

StandardObject* computeMostGeneralReturnType(MethodSlot* method, StandardObject* returntype) {
  { StandardObject* mostgeneralreturntype = returntype;
    MethodSlot* mostgeneralmethod = method;

    while (((boolean)(mostgeneralmethod->slotDirectEquivalent))) {
      mostgeneralmethod = ((MethodSlot*)(mostgeneralmethod->slotDirectEquivalent));
      if (!(mostgeneralmethod->slotBaseType == SGT_WALK_STELLA_UNKNOWN)) {
        if (arrayTypeSpecifierP(mostgeneralreturntype)) {
          mostgeneralreturntype = mostgeneralmethod->computeReturnTypeSpec(mostgeneralmethod->slotOwner);
        }
        else {
          mostgeneralreturntype = mostgeneralmethod->slotBaseType;
        }
      }
    }
    return (mostgeneralreturntype);
  }
}

StandardObject* computeRealSlotType(StorageSlot* slot, StandardObject* firstargtype, StandardObject* returntype) {
  { StandardObject* slottype = returntype;
    StorageSlot* canonicalslot = canonicalSlot(slot);
    Class* nativeslothome = NULL;

    if (nativeSlotP(canonicalslot)) {
      nativeslothome = nativeSlotHome(slot, typeSpecToClass(firstargtype));
    }
    if (((boolean)(nativeslothome))) {
      slottype = typeSpecToBaseType(lookupSlot(nativeslothome, canonicalslot->slotName)->computeReturnTypeSpec(nativeslothome->classType));
    }
    else {
      slottype = typeSpecToBaseType(slot->computeReturnTypeSpec(typeSpecToBaseType(firstargtype)));
    }
    if (slottype == typeSpecToBaseType(returntype)) {
      slottype = returntype;
    }
    return (slottype);
  }
}

Object* sysTreeIfNeeded(Slot* slot, Object* tree, StandardObject* firstargtype, StandardObject* returntype, StandardObject*& _Return1) {
  { StandardObject* dummy1;
    StandardObject* dummy2;
    StandardObject* dummy3;

    if (((boolean)(slot)) &&
        (!proceduralExpressionP(tree))) {
      { Surrogate* testValue000 = safePrimaryType(slot);

        if (subtypeOfMethodSlotP(testValue000)) {
          { Slot* slot000 = slot;
            MethodSlot* slot = ((MethodSlot*)(slot000));

            if ((!slot->methodFunctionP) &&
                needIdenticalMethodSignaturesP()) {
              { StandardObject* mostgeneralreturntype = computeMostGeneralReturnType(slot, returntype);

                if (!(returntype == mostgeneralreturntype)) {
                  return (setTargetLanguageType(sysTree(tree, returntype, dummy1), ((Surrogate*)(mostgeneralreturntype)), _Return1));
                }
              }
            }
          }
        }
        else if (subtypeOfStorageSlotP(testValue000)) {
          { Slot* slot001 = slot;
            StorageSlot* slot = ((StorageSlot*)(slot001));

            { StandardObject* realslottype = computeRealSlotType(slot, firstargtype, returntype);
              Slot* realslot = NULL;

              if (!(returntype == realslottype)) {
                if ((realslottype == SGT_WALK_STELLA_UNKNOWN) &&
                    ((!(slot == (realslot = slotFromExpressionTree(((Cons*)(tree)))))) &&
                     methodSlotP(realslot))) {
                  return (sysTreeIfNeeded(realslot, tree, firstargtype, returntype, _Return1));
                }
                return (setTargetLanguageType(sysTree(tree, returntype, dummy2), ((Surrogate*)(realslottype)), _Return1));
              }
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
      { CompoundTypeSpecifier* slottype = ((CompoundTypeSpecifier*)(dynamicSlotValue(slot->dynamicSlots, SYM_WALK_STELLA_SLOT_TYPE_SPECIFIER, NULL)));

        { boolean testValue001 = false;

          testValue001 = ((boolean)(slottype));
          if (testValue001) {
            if (anchoredTypeSpecifierP(slottype)) {
              testValue001 = true;
            }
            else {
              { boolean foundP000 = false;

                { StandardObject* ts = NULL;
                  Cons* iter000 = ((ParametricTypeSpecifier*)(slottype))->specifierParameterTypes->theConsList;

                  for (; !(iter000 == NIL); iter000 = iter000->rest) {
                    ts = ((StandardObject*)(iter000->value));
                    if (anchoredTypeSpecifierP(ts)) {
                      foundP000 = true;
                      break;
                    }
                  }
                }
                testValue001 = foundP000;
              }
            }
          }
          if (testValue001) {
            if (anchoredTypeSpecifierP(slottype) &&
                (!(oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP))) {
              return (setTargetLanguageType(sysTree(tree, returntype, dummy3), ((slot->slotBaseType == SGT_WALK_STELLA_UNKNOWN) ? typeSpecToBaseType(returntype) : slot->slotBaseType), _Return1));
            }
            else {
              return (sysTree(tree, returntype, _Return1));
            }
          }
        }
      }
    }
    _Return1 = returntype;
    return (tree);
  }
}

Surrogate* targetLanguageType(Object* tree) {
  if (safePrimaryType(tree) == SGT_WALK_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if ((tree->value == SYM_WALK_STELLA_TYPED_SYS) &&
          (tree->length() == 4)) {
        return (((Surrogate*)(tree->fourth())));
      }
    }
  }
  else {
  }
  return (NULL);
}

Cons* setTargetLanguageType(Cons* systree, Surrogate* type, StandardObject*& _Return1) {
  if (systree->length() == 4) {
    systree->fourthSetter(type);
  }
  else {
    systree->rest->rest->rest = consList(1, type);
  }
  _Return1 = ((StandardObject*)(systree->rest->rest->value));
  return (systree);
}

Object* walkATree(Object* tree, StandardObject*& _Return1) {
  return (helpWalkATree(tree, _Return1));
}

Object* helpWalkATree(Object* tree, StandardObject*& _Return1) {
  if (!((boolean)(tree))) {
    _Return1 = SGT_WALK_STELLA_UNKNOWN;
    return (NULL);
  }
  else {
    if (safePrimaryType(tree) == SGT_WALK_STELLA_CONS) {
      { Object* tree000 = tree;
        Cons* tree = ((Cons*)(tree000));

        if (tree == NIL) {
          _Return1 = SGT_WALK_STELLA_CONS;
          return (NIL);
        }
        if (consP(tree->value)) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Unimplemented or illegal parse tree: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
            }
          }
          _Return1 = SGT_WALK_STELLA_VOID;
          return (tree);
        }
        if (!(consP(tree->rest))) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal dotted pair or list*" << "." << std::endl;
            }
          }
          _Return1 = SGT_WALK_STELLA_VOID;
          return (tree);
        }
        { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

          if (testValue000 == SYM_WALK_STELLA_VOID_SYS) {
            _Return1 = SGT_WALK_STELLA_VOID;
            return (tree);
          }
          else if (testValue000 == SYM_WALK_STELLA_TYPED_SYS) {
            _Return1 = ((StandardObject*)(tree->rest->rest->value));
            return (tree);
          }
          else if (testValue000 == SYM_WALK_STELLA_SYS_FOREACH) {
            _Return1 = SGT_WALK_STELLA_VOID;
            return (tree);
          }
          else if (testValue000 == SYM_WALK_STELLA_BAD_SYS) {
            _Return1 = ((StandardObject*)(tree->rest->rest->value));
            return (tree);
          }
          else if ((testValue000 == SYM_WALK_STELLA_SETQ) ||
              (testValue000 == SYM_WALK_STELLA_SYS_SET_DEFAULT)) {
            return (walkSetqTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_SETF) {
            return (walkSetfTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_SLOT_VALUE) {
            return (walkSlotValueTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_SLOT_VALUE_SETTER) {
            return (walkSlotValueSetterTree(tree, _Return1));
          }
          else if ((testValue000 == SYM_WALK_STELLA_AREF) ||
              (testValue000 == SYM_WALK_STELLA_AREF_SETTER)) {
            return (walkArefTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_PROGN) {
            tree->rest = walkListOfStatements(tree->rest);
            return (sysTree(tree, SGT_WALK_STELLA_VOID, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_WITH_PROCESS_LOCK) {
            return (walkWithProcessLockTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_LOOP) {
            return (walkLoopTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_LET) {
            return (walkLetTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_VRLET) {
            _Return1 = SGT_WALK_STELLA_UNKNOWN;
            return (tree);
          }
          else if (testValue000 == SYM_WALK_STELLA_VALUES) {
            return (walkValuesTree(tree, _Return1));
          }
          else if ((testValue000 == SYM_WALK_STELLA_SPECIAL) ||
              (testValue000 == SYM_WALK_STELLA_SYS_SPECIAL)) {
            return (walkSpecialTree(tree, _Return1));
          }
          else if ((testValue000 == SYM_WALK_STELLA_CAST) ||
              (testValue000 == SYM_WALK_STELLA_SAFE_CAST)) {
            return (walkCastTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_RETURN) {
            return (walkReturnTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_MV_SETQ) {
            return (walkMvSetqTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_MV_BIND) {
            return (walkMvBindTree(tree, _Return1));
          }
          else if ((testValue000 == SYM_WALK_STELLA_BREAK) ||
              (testValue000 == SYM_WALK_STELLA_CONTINUE)) {
            return (walkLoopExitTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_WHILE) {
            return (walkWhileTree(tree, _Return1));
          }
          else if ((testValue000 == SYM_WALK_STELLA_FOREACH) ||
              ((testValue000 == SYM_WALK_STELLA_EXISTS) ||
               ((testValue000 == SYM_WALK_STELLA_FORALL) ||
                ((testValue000 == SYM_WALK_STELLA_SOME) ||
                 ((testValue000 == SYM_WALK_STELLA_SETOF) ||
                  ((testValue000 == SYM_WALK_STELLA_SET_OF) ||
                   (testValue000 == SYM_WALK_STELLA_SELECT))))))) {
            return (walkForeachTree(tree, _Return1));
          }
          else if ((testValue000 == SYM_WALK_STELLA_IF) ||
              ((testValue000 == SYM_WALK_STELLA_WHEN) ||
               (testValue000 == SYM_WALK_STELLA_UNLESS))) {
            return (walkConditionalTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_CHOOSE) {
            return (walkChooseTree(tree, _Return1));
          }
          else if ((testValue000 == SYM_WALK_STELLA_AND) ||
              ((testValue000 == SYM_WALK_STELLA_OR) ||
               (testValue000 == SYM_WALK_STELLA_NOT))) {
            return (walkBooleanTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_COND) {
            return (walkCondTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_CASE) {
            return (walkCaseTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_TYPECASE) {
            return (walkTypecaseTree(tree, _Return1));
          }
          else if ((testValue000 == SYM_WALK_STELLA_EQp) ||
              ((testValue000 == SYM_WALK_STELLA_EQLp) ||
               (testValue000 == SYM_WALK_STELLA_e))) {
            return (walkEqualityTree(tree, _Return1));
          }
          else if ((testValue000 == SYM_WALK_STELLA_i) ||
              ((testValue000 == SYM_WALK_STELLA__) ||
               ((testValue000 == SYM_WALK_STELLA_o) ||
                (testValue000 == SYM_WALK_STELLA_s)))) {
            { Object* value000 = NULL;
              Surrogate* value001 = NULL;

              value000 = walkArithmeticTree(tree, value001);
              _Return1 = value001;
              return (value000);
            }
          }
          else if (testValue000 == SYM_WALK_STELLA_QUOTE) {
            return (walkQuotedTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_BQUOTE) {
            return (walkBquoteTree(tree, _Return1));
          }
          else if ((testValue000 == SYM_WALK_STELLA_PRINT_STREAM) ||
              (testValue000 == SYM_WALK_STELLA_PRINT_NATIVE_STREAM)) {
            return (walkPrintStreamTree(tree, _Return1));
          }
          else if ((testValue000 == SYM_WALK_STELLA_NEW) ||
              ((testValue000 == SYM_WALK_STELLA_ALLOCATE) ||
               (testValue000 == SYM_WALK_STELLA_LOCAL_NEW))) {
            return (walkNewTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_MAKE) {
            return (walkMakeTree(tree, _Return1));
          }
          else if ((testValue000 == SYM_WALK_STELLA_FUNCALL) ||
              ((testValue000 == SYM_WALK_STELLA_SYS_CALL_FUNCTION_CODE) ||
               (testValue000 == SYM_WALK_STELLA_SYS_CALL_METHOD_CODE))) {
            return (walkFuncallTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_THE_CODE) {
            return (walkTheCodeTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_CALL_SUPER_METHOD) {
            return (walkCallSuperMethodTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_SIGNAL_EXCEPTION) {
            return (walkSignalExceptionTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_EXCEPTION_CASE) {
            return (walkExceptionCaseTree(tree, _Return1));
          }
          else if ((testValue000 == SYM_WALK_STELLA_UNWIND_PROTECT) ||
              (testValue000 == SYM_WALK_STELLA_SYS_UNWIND_PROTECT)) {
            { Cons* value002 = NULL;
              Surrogate* value003 = NULL;

              value002 = walkUnwindProtectTree(tree, value003);
              _Return1 = value003;
              return (value002);
            }
          }
          else if (testValue000 == SYM_WALK_STELLA_VERBATIM) {
            return (walkVerbatimTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_INLINE) {
            _Return1 = SGT_WALK_STELLA_VOID;
            return (tree);
          }
          else if ((testValue000 == SYM_WALK_STELLA_SYS_SLOT_VALUE) ||
              ((testValue000 == SYM_WALK_STELLA_SYS_SLOT_VALUE_SETTER) ||
               ((testValue000 == SYM_WALK_STELLA_SYS_CALL_METHOD) ||
                ((testValue000 == SYM_WALK_STELLA_SYS_CALL_SUPER_METHOD) ||
                 ((testValue000 == SYM_WALK_STELLA_SYS_CALL_METHOD_SETTER) ||
                  (testValue000 == SYM_WALK_STELLA_SYS_CALL_FUNCTION)))))) {
            return (walkSysCallTree(tree, _Return1));
          }
          else if (testValue000 == SYM_WALK_STELLA_SYS_NEW) {
            _Return1 = ((StandardObject*)(tree->rest->value));
            return (tree);
          }
          else if ((testValue000 == SYM_WALK_STELLA_DEFCLASS) ||
              ((testValue000 == SYM_WALK_STELLA_DEFMETHOD) ||
               ((testValue000 == SYM_WALK_STELLA_DEFUN) ||
                ((testValue000 == SYM_WALK_STELLA_DEFMACRO) ||
                 ((testValue000 == SYM_WALK_STELLA_STARTUP_TIME_PROGN) ||
                  ((testValue000 == SYM_WALK_STELLA_DEFGLOBAL) ||
                   ((testValue000 == SYM_WALK_STELLA_DEFSPECIAL) ||
                    (testValue000 == SYM_WALK_STELLA_DEFCONSTANT)))))))) {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal declaration -- must appear as a top-level statement;" << std::endl << "   not nested within other statements." << "." << std::endl;
              }
            }
            _Return1 = SGT_WALK_STELLA_VOID;
            return (NULL);
          }
          else {
            if (symbolP(tree->value)) {
              return (walkCallSlotTree(tree, _Return1));
            }
            else {
              {
                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  signalTranslationError();
                  if (!(suppressWarningsP())) {
                    printErrorContext(">> ERROR: ", STANDARD_ERROR);
                    *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal expression where method name expected:" << std::endl << "   " << "`" << tree->value << "'" << "." << std::endl;
                  }
                }
                return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
              }
            }
          }
        }
      }
    }
    else {
      return (tree->walkAtomicTree(_Return1));
    }
  }
}

Cons* walkAConsTree(Cons* tree, StandardObject*& _Return1) {
  { Object* otree = NULL;
    StandardObject* otype = NULL;

    otree = walkATree(tree, otype);
    _Return1 = otype;
    return (((Cons*)(otree)));
  }
}

HashTable* oSYMBOL_REGISTRYo = NULL;

List* oSYMBOL_SETo = NULL;

// Basename of file that is currently being translated.
// A NULL value indicates an incremental translation.
DEFINE_STELLA_SPECIAL(oCURRENTFILENAMEo, const char* , NULL);

boolean incrementalTranslationP() {
  return (oCURRENTFILENAMEo == NULL);
}

const char* constructSymbolConstantName(GeneralizedSymbol* symbol) {
  { const char* prefix = NULL;
    const char* environmentname = "";

    if (((boolean)(((Module*)(symbol->homeContext))))) {
      environmentname = stringConcatenate(((Module*)(symbol->homeContext))->moduleName, "-", 0);
    }
    if (!(incrementalTranslationP() ||
        (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA))) {
      environmentname = stringConcatenate(stringUpcase(oCURRENTFILENAMEo), "-", 1, environmentname);
    }
    { Surrogate* testValue000 = safePrimaryType(symbol);

      if (subtypeOfSymbolP(testValue000)) {
        { GeneralizedSymbol* symbol000 = symbol;
          Symbol* symbol = ((Symbol*)(symbol000));

          prefix = "SYM-";
        }
      }
      else if (subtypeOfSurrogateP(testValue000)) {
        { GeneralizedSymbol* symbol001 = symbol;
          Surrogate* symbol = ((Surrogate*)(symbol001));

          prefix = "SGT-";
        }
      }
      else if (subtypeOfKeywordP(testValue000)) {
        { GeneralizedSymbol* symbol002 = symbol;
          Keyword* symbol = ((Keyword*)(symbol002));

          prefix = "KWD-";
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    return (stringConcatenate(prefix, environmentname, 1, symbol->symbolName));
  }
}

Symbol* yieldSymbolConstantName(GeneralizedSymbol* symbol) {
  return (internSymbolInModule(constructSymbolConstantName(((GeneralizedSymbol*)(symbol->permanentify()))), oMODULEo, true));
}

Symbol* createStartupSymbol(GeneralizedSymbol* symbol) {
  { Module* symbolmodule = oMODULEo;
    Symbol* symbolconstant = yieldSymbolConstantName(symbol);
    const char* symbolconstantname = symbolconstant->symbolName;
    Object* symbolconstanttypetree = yieldTypeSpecTree(symbol->primaryType());
    const char* lisppackage = symbolmodule->lispPackage();
    Cons* tree = NULL;

    if (incrementalTranslationP()) {
    }
    tree = listO(3, SYM_WALK_STELLA_DEFGLOBAL, symbolconstant, cons(symbolconstanttypetree, listO(4, SYM_WALK_STELLA_NULL, KWD_WALK_PUBLICp, SYM_WALK_STELLA_TRUE, NIL)));
    walkAuxiliaryTree(tree);
    tree = listO(4, SYM_WALK_STELLA_STARTUP_TIME_PROGN, KWD_WALK_SYMBOLS, listO(3, SYM_WALK_STELLA_SETQ, symbolconstant, cons(listO(4, SYM_WALK_STELLA_SAFE_CAST, listO(3, SYM_WALK_STELLA_INTERN_RIGID_SYMBOL_WRT_MODULE, wrapString(symbol->symbolName), cons((((((Module*)(symbol->homeContext)) == oMODULEo) ||
        keywordP(symbol)) ? ((StandardObject*)(SYM_WALK_STELLA_NULL)) : ((StandardObject*)(listO(3, SYM_WALK_STELLA_GET_STELLA_MODULE, wrapString(((Module*)(symbol->homeContext))->moduleFullName), cons(SYM_WALK_STELLA_TRUE, NIL))))), cons(wrapInteger((keywordP(symbol) ? KEYWORD_SYM : ((surrogateP(symbol) ? SURROGATE_SYM : SYMBOL_SYM)))), NIL))), symbolconstanttypetree, NIL), NIL)), NIL);
    walkAuxiliaryTree(tree);
    return (symbolconstant);
  }
}

GeneralizedSymbol* registerSymbol(GeneralizedSymbol* symbol) {
  symbol = ((GeneralizedSymbol*)(symbol->permanentify()));
  { GeneralizedSymbol* registeredsymbol = ((GeneralizedSymbol*)(oSYMBOL_REGISTRYo->lookup(symbol)));

    if (!(((boolean)(registeredsymbol)))) {
      oSYMBOL_SETo->insert(symbol);
      if (useHardcodedSymbolsP()) {
        registeredsymbol = symbol;
      }
      else {
        registeredsymbol = createStartupSymbol(symbol);
      }
      oSYMBOL_REGISTRYo->insertAt(symbol, registeredsymbol);
    }
    return (registeredsymbol);
  }
}

void clearSymbolRegistry() {
  { GeneralizedSymbol* symbol = NULL;
    Cons* iter000 = oSYMBOL_SETo->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      symbol = ((GeneralizedSymbol*)(iter000->value));
      oSYMBOL_REGISTRYo->removeAt(symbol);
    }
  }
  oSYMBOL_SETo->clear();
}

Cons* yieldHardcodedInternRegisteredSymbolsTree() {
  { Cons* interntrees = listO(3, SYM_WALK_STELLA_STARTUP_TIME_PROGN, KWD_WALK_SYMBOLS, NIL);

    { GeneralizedSymbol* symbol = NULL;
      Cons* iter000 = oSYMBOL_SETo->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        symbol = ((GeneralizedSymbol*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(cons((symbolP(symbol) ? SYM_WALK_STELLA_INTERN_SYMBOL_AT : ((surrogateP(symbol) ? SYM_WALK_STELLA_INTERN_SURROGATE_AT : SYM_WALK_STELLA_INTERN_KEYWORD_AT))), cons(wrapString(symbol->symbolName), cons(wrapInteger(symbol->symbolId), NIL))), NIL);
            if (interntrees == NIL) {
              interntrees = collect000;
            }
            else {
              addConsToEndOfConsList(interntrees, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(cons((symbolP(symbol) ? SYM_WALK_STELLA_INTERN_SYMBOL_AT : ((surrogateP(symbol) ? SYM_WALK_STELLA_INTERN_SURROGATE_AT : SYM_WALK_STELLA_INTERN_KEYWORD_AT))), cons(wrapString(symbol->symbolName), cons(wrapInteger(symbol->symbolId), NIL))), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (interntrees);
  }
}

Object* Object::walkAtomicTree(StandardObject*& _Return1) {
  { Object* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "walk-atomic-tree: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Object* Wrapper::walkAtomicTree(StandardObject*& _Return1) {
  { Wrapper* self = this;

    { Object* _Return0 = self;

      _Return1 = wrapperValueType(self);
      return (_Return0);
    }
  }
}

Surrogate* lookupConstantSymbol(Symbol* self) {
  if (self == SYM_WALK_STELLA_NULL) {
    return (SGT_WALK_STELLA_UNKNOWN);
  }
  else if (self == SYM_WALK_STELLA_TRUE) {
    return (SGT_WALK_STELLA_BOOLEAN);
  }
  else if (self == SYM_WALK_STELLA_FALSE) {
    return (SGT_WALK_STELLA_BOOLEAN);
  }
  else {
    return (NULL);
  }
}

boolean constantSymbolP(Symbol* symbol) {
  return (((boolean)(lookupConstantSymbol(symbol))));
}

Symbol* walkConstantSymbol(Symbol* self, Surrogate*& _Return1) {
  { Symbol* _Return0 = self;

    _Return1 = lookupConstantSymbol(self);
    return (_Return0);
  }
}

Object* Symbol::walkAtomicTree(StandardObject*& _Return1) {
  { Symbol* self = this;
    StandardObject* dummy1;

    if (constantSymbolP(self)) {
      { Symbol* value000 = NULL;
        Surrogate* value001 = NULL;

        value000 = walkConstantSymbol(self, value001);
        _Return1 = value001;
        return (value000);
      }
    }
    if (oINLININGMETHODCALLpo &&
        ((boolean)(getLocalVariableInfo(self, KWD_WALK_INLINE_ARGUMENT)))) {
      return (walkInlineVariableReference(self, _Return1));
    }
    { Symbol* truename = trueVariableName(self);
      StandardObject* type = lookupVariableType(self);

      if (truename == self) {
        _Return1 = type;
        return (self);
      }
      else {
        { Object* _Return0 = sysTree(truename, type, dummy1);

          _Return1 = type;
          return (_Return0);
        }
      }
    }
  }
}

Object* Keyword::walkAtomicTree(StandardObject*& _Return1) {
  { Keyword* self = this;

    registerSymbol(self);
    _Return1 = SGT_WALK_STELLA_KEYWORD;
    return (self);
  }
}

Object* Surrogate::walkAtomicTree(StandardObject*& _Return1) {
  { Surrogate* self = this;

    registerSymbol(self);
    _Return1 = SGT_WALK_STELLA_SURROGATE;
    return (self);
  }
}

boolean atomicExpressionP(Object* tree) {
  if (safePrimaryType(tree) == SGT_WALK_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if (((GeneralizedSymbol*)(tree->value)) == SYM_WALK_STELLA_TYPED_SYS) {
        return (atomicExpressionP(tree->rest->value));
      }
      else {
      }
      return (false);
    }
  }
  else {
    return (true);
  }
}

boolean variableExpressionP(Object* tree) {
  { Surrogate* testValue000 = safePrimaryType(tree);

    if (testValue000 == SGT_WALK_STELLA_CONS) {
      { Object* tree000 = tree;
        Cons* tree = ((Cons*)(tree000));

        if (((GeneralizedSymbol*)(tree->value)) == SYM_WALK_STELLA_TYPED_SYS) {
          return (variableExpressionP(tree->rest->value));
        }
        else {
        }
        return (false);
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* tree001 = tree;
        Symbol* tree = ((Symbol*)(tree001));

        return (true);
      }
    }
    else {
      return (false);
    }
  }
}

boolean vrletExpressionP(Object* tree) {
  return (consP(tree) &&
      (((Cons*)(tree))->value == SYM_WALK_STELLA_VRLET));
}

boolean proceduralExpressionP(Object* tree) {
  { boolean testValue000 = false;

    testValue000 = consP(tree);
    if (testValue000) {
      if (((Cons*)(tree))->value == SYM_WALK_STELLA_VRLET) {
        testValue000 = true;
      }
      else {
        { boolean foundP000 = false;

          { Object* term = NULL;
            Cons* iter000 = ((Cons*)(tree))->rest;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              term = iter000->value;
              if (proceduralExpressionP(term)) {
                foundP000 = true;
                break;
              }
            }
          }
          testValue000 = foundP000;
        }
      }
    }
    { boolean value000 = testValue000;

      return (value000);
    }
  }
}

boolean substituteOnce(Object* expression, Object* newtree, Object* oldtree) {
  if (safePrimaryType(expression) == SGT_WALK_STELLA_CONS) {
    { Object* expression000 = expression;
      Cons* expression = ((Cons*)(expression000));

      if (!(expression == NIL)) {
        if (eqlP(expression->value, oldtree)) {
          expression->value = newtree;
          return (true);
        }
        return (substituteOnce(expression->value, newtree, oldtree) ||
            substituteOnce(expression->rest, newtree, oldtree));
      }
    }
  }
  else {
  }
  return (false);
}

Cons* transformVrletExpression(Cons* statement, Cons* vrexpression, StandardObject*& _Return1) {
  { Cons* cursor = NULL;
    Object* laststatement = NULL;

    substituteOnce(statement, KWD_WALK_PLACE_WHERE_VRLET_WAS, vrexpression);
    vrexpression->value = SYM_WALK_STELLA_LET;
    cursor = vrexpression->rest->rest;
    while (!(cursor == NIL)) {
      if (cursor->rest == NIL) {
        laststatement = cursor->value;
        cursor->value = statement;
        break;
      }
      cursor = cursor->rest;
    }
    substituteOnce(statement, laststatement, KWD_WALK_PLACE_WHERE_VRLET_WAS);
    return (walkAConsTree(vrexpression, _Return1));
  }
}

Cons* helpTransformBooleanProceduralExpression(Object* expression, Symbol* testvariable) {
  if ((!consP(expression)) ||
      (!proceduralExpressionP(expression))) {
    return (cons(listO(3, SYM_WALK_STELLA_SETQ, testvariable, cons(expression, NIL)), NIL));
  }
  { Cons* exp = ((Cons*)(expression));
    Object* operatoR = exp->value;
    Object* firstarg = exp->rest->value;
    Cons* otherargs = exp->rest->rest;

    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(operatoR));

      if (testValue000 == SYM_WALK_STELLA_AND) {
        if (otherargs == NIL) {
          return (helpTransformBooleanProceduralExpression(firstarg, testvariable));
        }
        else if (proceduralExpressionP(firstarg)) {
          return (helpTransformBooleanProceduralExpression(firstarg, testvariable)->concatenate(cons(listO(3, SYM_WALK_STELLA_WHEN, testvariable, helpTransformBooleanProceduralExpression(cons(SYM_WALK_STELLA_AND, otherargs->concatenate(NIL, 0)), testvariable)->concatenate(NIL, 0)), NIL), 0));
        }
        else {
          return (listO(3, listO(3, SYM_WALK_STELLA_SETQ, testvariable, cons(firstarg, NIL)), listO(3, SYM_WALK_STELLA_WHEN, testvariable, helpTransformBooleanProceduralExpression(cons(SYM_WALK_STELLA_AND, otherargs->concatenate(NIL, 0)), testvariable)->concatenate(NIL, 0)), NIL));
        }
      }
      else if (testValue000 == SYM_WALK_STELLA_OR) {
        if (otherargs == NIL) {
          return (helpTransformBooleanProceduralExpression(firstarg, testvariable));
        }
        else if (proceduralExpressionP(firstarg)) {
          return (helpTransformBooleanProceduralExpression(firstarg, testvariable)->concatenate(cons(listO(3, SYM_WALK_STELLA_WHEN, listO(3, SYM_WALK_STELLA_NOT, testvariable, NIL), helpTransformBooleanProceduralExpression(cons(SYM_WALK_STELLA_OR, otherargs->concatenate(NIL, 0)), testvariable)->concatenate(NIL, 0)), NIL), 0));
        }
        else {
          { Cons* otherargstest = helpTransformBooleanProceduralExpression(cons(SYM_WALK_STELLA_OR, otherargs->concatenate(NIL, 0)), testvariable);

            if (!(otherargstest->rest == NIL)) {
              otherargstest = cons(cons(SYM_WALK_STELLA_PROGN, otherargstest->concatenate(NIL, 0)), NIL);
            }
            return (cons(listO(3, SYM_WALK_STELLA_IF, firstarg, cons(listO(3, SYM_WALK_STELLA_SETQ, testvariable, cons(SYM_WALK_STELLA_TRUE, NIL)), otherargstest->concatenate(NIL, 0))), NIL));
          }
        }
      }
      else if (testValue000 == SYM_WALK_STELLA_NOT) {
        return (helpTransformBooleanProceduralExpression(firstarg, testvariable)->concatenate(cons(listO(3, SYM_WALK_STELLA_SETQ, testvariable, cons(listO(3, SYM_WALK_STELLA_NOT, testvariable, NIL), NIL)), NIL), 0));
      }
      else if (testValue000 == SYM_WALK_STELLA_VRLET) {
        { Cons* cursor = otherargs;

          while (!(cursor->rest == NIL)) {
            cursor = cursor->rest;
          }
          cursor->value = listO(3, SYM_WALK_STELLA_SETQ, testvariable, cons(cursor->value, NIL));
        }
        return (cons(listO(3, SYM_WALK_STELLA_LET, firstarg, otherargs->concatenate(NIL, 0)), NIL));
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

Cons* transformBooleanProceduralExpression(Cons* statement, Cons* vrexpression, StandardObject*& _Return1) {
  if (vrexpression->value == SYM_WALK_STELLA_VRLET) {
    return (transformVrletExpression(statement, vrexpression, _Return1));
  }
  { Symbol* testvariable = localGensym("TEST-VALUE");
    Cons* otree = NULL;

    substituteOnce(statement, testvariable, vrexpression);
    otree = ((Cons*)(walkWithoutTypeTree(listO(3, SYM_WALK_STELLA_LET, cons(cons(testvariable, cons(SYM_WALK_STELLA_FALSE, NIL)), NIL), helpTransformBooleanProceduralExpression(vrexpression, testvariable)->concatenate(cons(statement, NIL), 0)))));
    _Return1 = SGT_WALK_STELLA_BOOLEAN;
    return (otree);
  }
}

Cons* percolateOutBooleanVrletExpressions(Cons* booleanexpression) {
  { Symbol* testvariable = localGensym("TEST-VALUE");
    Cons* otree = NULL;

    otree = listO(3, SYM_WALK_STELLA_VRLET, cons(cons(testvariable, cons(SYM_WALK_STELLA_FALSE, NIL)), NIL), helpTransformBooleanProceduralExpression(booleanexpression, testvariable)->concatenate(cons(testvariable, NIL), 0));
    return (otree);
  }
}

Cons* transformProceduralExpression(Cons* statement, Cons* vrexpression, StandardObject* type, StandardObject*& _Return1) {
  if (typeSpecToBaseType(type) == SGT_WALK_STELLA_BOOLEAN) {
    return (transformBooleanProceduralExpression(statement, vrexpression, _Return1));
  }
  else {
    return (transformVrletExpression(statement, vrexpression, _Return1));
  }
}

Cons* percolateOutVrletExpression(Cons* statement, Cons* vrexpression, StandardObject* type, StandardObject*& _Return1) {
  { Object* laststatement = NULL;
    Cons* cursor = vrexpression->rest->rest;

    while (!(cursor == NIL)) {
      if (cursor->rest == NIL) {
        laststatement = cursor->value;
        cursor->value = KWD_WALK_PLACE_WHERE_LAST_EXPRESSION_WAS;
        break;
      }
      cursor = cursor->rest;
    }
    substituteOnce(statement, laststatement, vrexpression);
    substituteOnce(vrexpression, statement, KWD_WALK_PLACE_WHERE_LAST_EXPRESSION_WAS);
    _Return1 = type;
    return (vrexpression);
  }
}

Cons* walkSetqTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;

    if (badArgumentCountP(tree, 2)) {
      return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
    }
    { Object* variable = tree->rest->value;
      Object* value = tree->rest->rest->value;
      StandardObject* variabletype = NULL;
      Object* ovalue = NULL;
      StandardObject* otype = NULL;

      if (!(symbolP(variable))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal first argument to 'setq'; should be a symbol: " << "`" << deUglifyParseTree(variable) << "'" << "." << std::endl;
          }
        }
        return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
      }
      variabletype = lookupVariableType(((Symbol*)(variable)));
      ovalue = walkExpressionTree(value, variabletype, SYM_WALK_STELLA_SETQ, true, otype);
      tree->thirdSetter(ovalue);
      if (!(proceduralExpressionP(ovalue))) {
        tree->secondSetter(trueVariableName(((Symbol*)(variable))));
        if (walkingExpressionP() &&
            (!(oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP))) {
          return (setTargetLanguageType(sysTree(tree, otype, dummy1), typeSpecToBaseType(variabletype), _Return1));
        }
        if (!eqlP(variable, tree->rest->value)) {
          return (sysTree(tree, otype, _Return1));
        }
        else {
          _Return1 = otype;
          return (tree);
        }
      }
      return (transformProceduralExpression(tree, ((Cons*)(ovalue)), ((otype == SGT_WALK_STELLA_UNKNOWN) ? variabletype : otype), _Return1));
    }
  }
}

Cons* yieldFixedSlotValueSetterTree(Slot* slot, Object* objectref, Object* valuetree) {
  { StandardObject* dummy1;

    return (listO(3, SYM_WALK_STELLA_SYS_SLOT_VALUE_SETTER, slot->slotOwner, cons(slot->slotName, cons(objectref, cons(walkExpressionTree(valuetree, slot->type(), SYM_WALK_STELLA_SLOT_VALUE_SETTER, false, dummy1), NIL)))));
  }
}

Cons* walkSetfTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;
    StandardObject* dummy2;
    StandardObject* dummy3;

    { Cons* place = NULL;

      if (consP(tree->rest->value)) {
        place = ((Cons*)(tree->rest->value));
      }
      if (!(((boolean)(place)) &&
          (symbolP(place->value) &&
           (place->length() >= (((place->value == SYM_WALK_STELLA_SLOT_VALUE) ? 3 : 2)))))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal place argument in 'setf' expression: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
          }
        }
        return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
      }
      if (badArgumentCountP(tree, 2)) {
        return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
      }
      { Object* objectref = NULL;
        StandardObject* objecttype = NULL;

        objectref = walkATree(place->rest->value, objecttype);
        objectref = coerceATree(objectref, objecttype, objecttype, dummy1);
        { Class* objectclass = typeSpecToClass(objecttype);
          Object* slotname = place->value;
          Slot* slot = lookupSlot(objectclass, ((Symbol*)(slotname)));
          StandardObject* slottype = NULL;
          Cons* otherplacearguments = place->rest->rest;
          Cons* otree = NIL;

          if (((boolean)(slot))) {
            slottype = slot->computeReturnTypeSpec(objecttype);
          }
          { Object* valueref = NULL;
            StandardObject* valuetypespec = NULL;

            valueref = walkExpressionTree(tree->rest->rest->value, slottype, SYM_WALK_STELLA_SETF, true, valuetypespec);
            if (proceduralExpressionP(valueref)) {
              tree->thirdSetter(valueref);
              { Cons* ootree = NULL;
                StandardObject* otypespec = NULL;

                ootree = transformProceduralExpression(tree, ((Cons*)(valueref)), valuetypespec, otypespec);
                _Return1 = otypespec;
                return (ootree);
              }
            }
            if (slotname == SYM_WALK_STELLA_SLOT_VALUE) {
              return (walkAConsTree(listO(3, SYM_WALK_STELLA_SLOT_VALUE_SETTER, objectref, cons(valueref, otherplacearguments->concatenate(NIL, 0))), _Return1));
            }
            if (subtypeOfStorageSlotP(safePrimaryType(slot))) {
              { Slot* slot000 = slot;
                StorageSlot* slot = ((StorageSlot*)(slot000));

                if (((boolean)(slot->writer())) ||
                    ((boolean)(lookupSlot(objectclass, yieldSetterMethodName(((Symbol*)(slotname))))))) {
                  return (walkAConsTree(cons((((boolean)(slot->writer())) ? slot->writer() : yieldSetterMethodName(((Symbol*)(slotname)))), cons(objectref, cons(valueref, otherplacearguments->concatenate(NIL, 0)))), _Return1));
                }
                if (systemDefinedSlotWriterP(slot)) {
                  { Object* value000 = NULL;
                    StandardObject* value001 = NULL;

                    value000 = sysTreeIfNeeded(slot, listO(3, SYM_WALK_STELLA_SYS_CALL_METHOD, slot->slotOwner, cons(yieldSetterMethodName(((Symbol*)(slotname))), cons(objectref, cons(walkExpressionTree(valueref, slottype, SYM_WALK_STELLA_SETF, false, dummy2), NIL)))), objecttype, slottype, value001);
                    _Return1 = value001;
                    return (((Cons*)(value000)));
                  }
                }
                otree = yieldSlotValueSetterTree(slot, objectref, objecttype, valueref, slottype, NULL, dummy3);
                if (proceduralExpressionP(otree)) {
                  _Return1 = slottype;
                  return (otree);
                }
                else {
                  { Object* value002 = NULL;
                    StandardObject* value003 = NULL;

                    value002 = sysTreeIfNeeded(slot, otree, objecttype, slottype, value003);
                    _Return1 = value003;
                    return (((Cons*)(value002)));
                  }
                }
              }
            }
            else {
              return (walkAConsTree(cons(yieldSetterMethodName(((Symbol*)(slotname))), cons(objectref, cons(valueref, otherplacearguments->concatenate(NIL, 0)))), _Return1));
            }
          }
        }
      }
    }
  }
}

Cons* yieldDynamicSlotValueTree(StorageSlot* slot, Object* objectref, StandardObject* returntype) {
  if (standardDynamicSlotAccessP(slot)) {
    return (yieldStandardDynamicSlotValueTree(slot, objectref, returntype));
  }
  { Keyword* testValue000 = slot->allocation();

    if (testValue000 == KWD_WALK_DYNAMIC) {
      { Symbol* answervar = localGensym("ANSWER");

        return (listO(5, SYM_WALK_STELLA_VRLET, cons(cons(answervar, cons(returntype, cons(typeToWalkedNullValueTree(slot->typeSpecifier(), slot->type()), NIL))), NIL), listO(9, SYM_WALK_STELLA_FOREACH, SYM_WALK_STELLA_IT, SYM_WALK_STELLA_ON, listO(3, SYM_WALK_STELLA_DYNAMIC_SLOTS, objectref, NIL), SYM_WALK_STELLA_WHERE, listO(4, SYM_WALK_STELLA_EQp, listO(3, SYM_WALK_STELLA_KEY, SYM_WALK_STELLA_IT, NIL), listO(3, SYM_WALK_STELLA_BQUOTE, slot->slotName, NIL), NIL), SYM_WALK_STELLA_DO, (slotValueIsBareLiteralP(slot) ? listO(4, SYM_WALK_STELLA_LET, cons(listO(3, SYM_WALK_STELLA_WRAPPEDVALUE, slot->type()->typeToWrappedType(), cons(listO(3, SYM_WALK_STELLA_VALUE, SYM_WALK_STELLA_IT, NIL), NIL)), NIL), listO(3, SYM_WALK_STELLA_SETQ, answervar, cons(listO(3, SYM_WALK_STELLA_WRAPPER_VALUE, SYM_WALK_STELLA_WRAPPEDVALUE, NIL), NIL)), NIL) : listO(3, SYM_WALK_STELLA_SETQ, answervar, cons(listO(3, SYM_WALK_STELLA_VALUE, SYM_WALK_STELLA_IT, NIL), NIL))), cons(cons(SYM_WALK_STELLA_BREAK, NIL), NIL)), answervar, NIL));
      }
    }
    else if (testValue000 == KWD_WALK_BIT) {
      throw *newStellaException("Allocation :bit IS NOT YET IMPLEMENTED");
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Cons* yieldDynamicSlotValueSetterTree(StorageSlot* slot, Object* objectref, Object* valueref, StandardObject* returntype) {
  { Symbol* slotname = slot->slotName;

    if (standardDynamicSlotAccessP(slot)) {
      return (yieldStandardDynamicSlotValueSetterTree(slot, objectref, valueref, returntype));
    }
    { Keyword* testValue000 = slot->allocation();

      if (testValue000 == KWD_WALK_DYNAMIC) {
        return (listO(6, SYM_WALK_STELLA_VRLET, listO(4, listO(3, SYM_WALK_STELLA_DYNAMICSLOTS, listO(3, SYM_WALK_STELLA_DYNAMIC_SLOTS, objectref, NIL), NIL), listO(3, SYM_WALK_STELLA_NEWVALUE, valueref, NIL), listO(3, SYM_WALK_STELLA_FOUNDMATCHINGENTRYp, SYM_WALK_STELLA_FALSE, NIL), NIL), listO(9, SYM_WALK_STELLA_FOREACH, SYM_WALK_STELLA_IT, SYM_WALK_STELLA_ON, SYM_WALK_STELLA_DYNAMICSLOTS, SYM_WALK_STELLA_WHERE, listO(4, SYM_WALK_STELLA_EQp, listO(3, SYM_WALK_STELLA_KEY, SYM_WALK_STELLA_IT, NIL), listO(3, SYM_WALK_STELLA_BQUOTE, slotname, NIL), NIL), SYM_WALK_STELLA_DO, (slotValueIsBareLiteralP(slot) ? listO(4, SYM_WALK_STELLA_LET, cons(listO(3, SYM_WALK_STELLA_OLDVALUE, typeToSymbol(slot->type()->typeToWrappedType()), cons(listO(3, SYM_WALK_STELLA_VALUE, SYM_WALK_STELLA_IT, NIL), NIL)), NIL), listO(4, SYM_WALK_STELLA_SETF, listO(3, SYM_WALK_STELLA_WRAPPER_VALUE, SYM_WALK_STELLA_OLDVALUE, NIL), SYM_WALK_STELLA_NEWVALUE, NIL), NIL) : listO(4, SYM_WALK_STELLA_SETF, listO(3, SYM_WALK_STELLA_VALUE, SYM_WALK_STELLA_IT, NIL), SYM_WALK_STELLA_NEWVALUE, NIL)), cons(listO(4, SYM_WALK_STELLA_SETQ, SYM_WALK_STELLA_FOUNDMATCHINGENTRYp, SYM_WALK_STELLA_TRUE, NIL), NIL)), listO(4, SYM_WALK_STELLA_WHEN, listO(4, SYM_WALK_STELLA_AND, listO(3, SYM_WALK_STELLA_NOT, SYM_WALK_STELLA_FOUNDMATCHINGENTRYp, NIL), listO(3, SYM_WALK_STELLA_DEFINEDp, SYM_WALK_STELLA_NEWVALUE, NIL), NIL), listO(4, SYM_WALK_STELLA_SETF, listO(3, SYM_WALK_STELLA_THE_KV_LIST, SYM_WALK_STELLA_DYNAMICSLOTS, NIL), listO(4, SYM_WALK_STELLA_KV_CONS, listO(3, SYM_WALK_STELLA_BQUOTE, slotname, NIL), (slotValueIsBareLiteralP(slot) ? listO(3, SYM_WALK_STELLA_WRAP_LITERAL, SYM_WALK_STELLA_NEWVALUE, NIL) : ((Object*)(SYM_WALK_STELLA_NEWVALUE))), cons(listO(3, SYM_WALK_STELLA_THE_KV_LIST, SYM_WALK_STELLA_DYNAMICSLOTS, NIL), NIL)), NIL), NIL), SYM_WALK_STELLA_NEWVALUE, NIL));
      }
      else if (testValue000 == KWD_WALK_BIT) {
        throw *newStellaException("Allocation :bit IS NOT YET IMPLEMENTED");
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

Cons* yieldNativeSlotValueTree(StorageSlot* slot, Object* objectref, StandardObject* objecttype) {
  { StandardObject* dummy1;

    slot = canonicalSlot(slot);
    { boolean mixinslotP = ((Class*)(slot->slotOwner->surrogateValue))->mixinP;
      Class* objectclass = typeSpecToClass(objecttype);

      if (mixinslotP &&
          translateToSingleInheritanceLanguageP()) {
        if (objectclass->mixinP) {
          return (sysTree(listO(4, SYM_WALK_STELLA_SYS_CALL_METHOD, SGT_WALK_STELLA_OBJECT, yieldNativeSlotReaderName(slot), cons(objectref, NIL)), (((boolean)(((CompoundTypeSpecifier*)(dynamicSlotValue(slot->dynamicSlots, SYM_WALK_STELLA_SLOT_TYPE_SPECIFIER, NULL))))) ? ((StandardObject*)(((CompoundTypeSpecifier*)(dynamicSlotValue(slot->dynamicSlots, SYM_WALK_STELLA_SLOT_TYPE_SPECIFIER, NULL))))) : ((StandardObject*)(slot->slotBaseType))), dummy1));
        }
      }
      if (slot->slotHardwiredP) {
        return (listO(3, SYM_WALK_STELLA_SYS_CALL_METHOD, objectclass->classType, cons(slot->slotName, cons(objectref, NIL))));
      }
      else {
        return (listO(3, SYM_WALK_STELLA_SYS_SLOT_VALUE, objectclass->classType, cons(slot->slotName, cons(objectref, NIL))));
      }
    }
  }
}

Cons* yieldContextSensitiveSlotValueTree(StorageSlot* slot, Object* objectref, StandardObject* returntype, Cons* csoptions, StandardObject*& _Return1) {
  { StandardObject* dummy1;
    StandardObject* dummy2;

    { boolean contextsensitiveP = !(((boolean)(csoptions)) &&
          (searchPlist(csoptions, KWD_WALK_CONTEXT_SENSITIVEp) == SYM_WALK_STELLA_FALSE));
      Symbol* dontinheritP = ((((boolean)(csoptions)) &&
          (searchPlist(csoptions, KWD_WALK_DONT_INHERITp) == SYM_WALK_STELLA_TRUE)) ? SYM_WALK_STELLA_TRUE : SYM_WALK_STELLA_FALSE);
      Object* objectrefcopy = objectref;
      boolean onceonlywrapperP = contextsensitiveP &&
          (!sideEffectFreeExpressionP(objectref));
      boolean literalslotP = slotValueIsBareLiteralP(slot);
      Surrogate* realbasetype = slot->slotBaseType;
      CompoundTypeSpecifier* realtypespec = ((CompoundTypeSpecifier*)(dynamicSlotValue(slot->dynamicSlots, SYM_WALK_STELLA_SLOT_TYPE_SPECIFIER, NULL)));
      Object* oldvaluetree = NULL;
      Symbol* oldvalueref = localGensym("OLD-VALUE");
      Cons* accesstree = NULL;

      if (onceonlywrapperP) {
        objectref = localGensym("OBJECT");
        pushVariableBinding(((Symbol*)(objectref)), slot->slotOwner);
      }
      else {
        objectref = sysTree(walkWithoutTypeTree(objectref), slot->slotOwner, dummy1);
      }
      slot->slotBaseType = SGT_WALK_STELLA_OBJECT;
      if (((boolean)(realtypespec))) {
        setDynamicSlotValue(slot->dynamicSlots, SYM_WALK_STELLA_SLOT_TYPE_SPECIFIER, NULL, NULL);
      }
      slot->slotContextSensitiveP = false;
      oldvaluetree = sysTree(walkWithoutTypeTree(listO(3, SYM_WALK_STELLA_SLOT_VALUE, (contextsensitiveP ? copyConsTree(objectref) : objectref), cons(slot->slotName, NIL))), SGT_WALK_STELLA_OBJECT, dummy2);
      slot->slotBaseType = realbasetype;
      if (((boolean)(realtypespec))) {
        setDynamicSlotValue(slot->dynamicSlots, SYM_WALK_STELLA_SLOT_TYPE_SPECIFIER, realtypespec, NULL);
      }
      slot->slotContextSensitiveP = true;
      if (!contextsensitiveP) {
        _Return1 = SGT_WALK_STELLA_OBJECT;
        return (((Cons*)(oldvaluetree)));
      }
      if (onceonlywrapperP) {
        popVariableBinding();
      }
      accesstree = listO(4, SYM_WALK_STELLA_SAFE_CAST, listO(3, SYM_WALK_STELLA_ACCESS_IN_CONTEXT, (onceonlywrapperP ? oldvalueref : oldvaluetree), listO(3, listO(3, SYM_WALK_STELLA_HOME_CONTEXT, objectref, NIL), dontinheritP, NIL)), yieldTypeSpecTree((literalslotP ? slot->type()->typeToWrappedType() : ((StandardObject*)(returntype)))), NIL);
      if (literalslotP) {
        accesstree = listO(3, SYM_WALK_STELLA_WRAPPER_VALUE, accesstree, NIL);
      }
      if (onceonlywrapperP) {
        { Cons* _Return0 = listO(4, SYM_WALK_STELLA_VRLET, listO(3, cons(objectref, cons(objectrefcopy, NIL)), cons(oldvalueref, cons(oldvaluetree, NIL)), NIL), accesstree, NIL);

          _Return1 = returntype;
          return (_Return0);
        }
      }
      else {
        { Cons* _Return0 = ((Cons*)(walkWithoutTypeTree(accesstree)));

          _Return1 = returntype;
          return (_Return0);
        }
      }
    }
  }
}

Cons* yieldSlotValueTree(StorageSlot* slot, Object* objectref, StandardObject* objecttype, StandardObject* returntype, Cons* csoptions, StandardObject*& _Return1) {
  if (slot->slotContextSensitiveP) {
    return (yieldContextSensitiveSlotValueTree(slot, objectref, returntype, csoptions, _Return1));
  }
  else {
    if (slot->dynamicStorageP()) {
      { Cons* _Return0 = ((Cons*)(walkWithoutTypeTree(yieldDynamicSlotValueTree(slot, objectref, returntype))));

        _Return1 = returntype;
        return (_Return0);
      }
    }
    else {
      { Cons* _Return0 = yieldNativeSlotValueTree(slot, objectref, objecttype);

        _Return1 = returntype;
        return (_Return0);
      }
    }
  }
}

Cons* walkSlotValueTree(Cons* tree, StandardObject*& _Return1) {
  { Object* objectref = NULL;
    StandardObject* objecttype = NULL;

    objectref = walkATree(tree->rest->value, objecttype);
    { Object* slotname = tree->rest->rest->value;
      Cons* csoptions = tree->nthRest(3);
      Class* objectclass = typeSpecToClass(objecttype);
      Slot* slot = lookupSlot(objectclass, ((Symbol*)(slotname)));
      Cons* otree = NULL;
      StandardObject* otype = NULL;

      if (!((boolean)(slot))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Can't read a non-existent slot " << "`" << deUglifyParseTree(slotname) << "'" << std::endl << "   on the class " << "`" << className(objectclass) << "'" << "." << std::endl;
          }
        }
        return (walkDontCallMeTree(tree, SGT_WALK_STELLA_UNKNOWN, _Return1));
      }
      { Surrogate* testValue000 = safePrimaryType(slot);

        if (subtypeOfMethodSlotP(testValue000)) {
          { Slot* slot000 = slot;
            MethodSlot* slot = ((MethodSlot*)(slot000));

            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Can't read the method slot " << "`" << deUglifyParseTree(slot) << "'" << " by calling 'slot-value'" << "." << std::endl;
              }
            }
            _Return1 = NULL;
            return (NULL);
          }
        }
        else if (subtypeOfStorageSlotP(testValue000)) {
          { Slot* slot001 = slot;
            StorageSlot* slot = ((StorageSlot*)(slot001));

            otype = slot->computeReturnTypeSpec(objecttype);
            otree = yieldSlotValueTree(slot, objectref, objecttype, otype, csoptions, otype);
            if (proceduralExpressionP(otree)) {
              _Return1 = otype;
              return (otree);
            }
            else {
              { Object* value000 = NULL;
                StandardObject* value001 = NULL;

                value000 = sysTreeIfNeeded(slot, otree, objecttype, otype, value001);
                _Return1 = value001;
                return (((Cons*)(value000)));
              }
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
    }
  }
}

Cons* yieldNativeSlotValueSetterTree(StorageSlot* slot, Object* objectref, StandardObject* objecttype, Object* valueref) {
  { StandardObject* dummy1;
    StandardObject* dummy2;

    slot = canonicalSlot(slot);
    { boolean mixinslotP = ((Class*)(slot->slotOwner->surrogateValue))->mixinP;
      Class* objectclass = typeSpecToClass(objecttype);

      if (mixinslotP &&
          translateToSingleInheritanceLanguageP()) {
        if (objectclass->mixinP) {
          return (sysTree(listO(4, SYM_WALK_STELLA_SYS_CALL_METHOD, SGT_WALK_STELLA_OBJECT, yieldNativeSlotReaderName(slot), cons(objectref, cons(valueref, NIL))), (((boolean)(((CompoundTypeSpecifier*)(dynamicSlotValue(slot->dynamicSlots, SYM_WALK_STELLA_SLOT_TYPE_SPECIFIER, NULL))))) ? ((StandardObject*)(((CompoundTypeSpecifier*)(dynamicSlotValue(slot->dynamicSlots, SYM_WALK_STELLA_SLOT_TYPE_SPECIFIER, NULL))))) : ((StandardObject*)(slot->slotBaseType))), dummy1));
        }
      }
      if (slot->slotHardwiredP) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Can't set the value of the hardwired slot " << "`" << slot->slotOwner << "'" << "." << "`" << slot->slotName << "'" << "." << std::endl;
          }
        }
        return (walkDontCallMeTree(NULL, slot->slotBaseType, dummy2));
      }
      return (listO(3, SYM_WALK_STELLA_SYS_SLOT_VALUE_SETTER, objectclass->classType, cons(slot->slotName, cons(objectref, cons(valueref, NIL)))));
    }
  }
}

Cons* yieldContextSensitiveSlotValueSetterTree(StorageSlot* slot, Object* objectref, Object* valueref, StandardObject* returntype, Cons* csoptions, StandardObject*& _Return1) {
  { StandardObject* dummy1;
    StandardObject* dummy2;
    StandardObject* dummy3;

    { boolean contextsensitiveP = !(((boolean)(csoptions)) &&
          (searchPlist(csoptions, KWD_WALK_CONTEXT_SENSITIVEp) == SYM_WALK_STELLA_FALSE));
      Symbol* copytochildren = ((((boolean)(csoptions)) &&
          (searchPlist(csoptions, KWD_WALK_COPY_TO_CHILDRENp) == SYM_WALK_STELLA_TRUE)) ? SYM_WALK_STELLA_TRUE : SYM_WALK_STELLA_FALSE);
      Surrogate* realbasetype = slot->slotBaseType;
      CompoundTypeSpecifier* realtypespec = ((CompoundTypeSpecifier*)(dynamicSlotValue(slot->dynamicSlots, SYM_WALK_STELLA_SLOT_TYPE_SPECIFIER, NULL)));
      Symbol* objectvar = NULL;
      Symbol* valuevar = NULL;
      Symbol* oldvaluevar = NULL;
      Symbol* newvaluevar = NULL;
      Cons* oldvaluetree = NULL;
      Cons* setnewvaluetree = NULL;

      slot->slotBaseType = SGT_WALK_STELLA_OBJECT;
      if (((boolean)(realtypespec))) {
        setDynamicSlotValue(slot->dynamicSlots, SYM_WALK_STELLA_SLOT_TYPE_SPECIFIER, NULL, NULL);
      }
      slot->slotContextSensitiveP = false;
      if (contextsensitiveP) {
        objectvar = localGensym("OBJECT");
        valuevar = localGensym("VALUE");
        oldvaluevar = localGensym("OLD-VALUE");
        newvaluevar = localGensym("NEW-VALUE");
        pushVariableBinding(objectvar, slot->slotOwner);
        pushVariableBinding(newvaluevar, SGT_WALK_STELLA_OBJECT);
        oldvaluetree = sysTree(walkWithoutTypeTree(listO(3, SYM_WALK_STELLA_SLOT_VALUE, objectvar, cons(slot->slotName, NIL))), SGT_WALK_STELLA_OBJECT, dummy1);
        setnewvaluetree = sysTree(walkWithoutTypeTree(listO(4, SYM_WALK_STELLA_SETF, listO(3, SYM_WALK_STELLA_SLOT_VALUE, objectvar, cons(slot->slotName, NIL)), newvaluevar, NIL)), SGT_WALK_STELLA_OBJECT, dummy2);
      }
      else {
        setnewvaluetree = sysTree(walkWithoutTypeTree(listO(4, SYM_WALK_STELLA_SETF, listO(3, SYM_WALK_STELLA_SLOT_VALUE, objectref, cons(slot->slotName, NIL)), valueref, NIL)), SGT_WALK_STELLA_OBJECT, dummy3);
      }
      slot->slotBaseType = realbasetype;
      if (((boolean)(realtypespec))) {
        setDynamicSlotValue(slot->dynamicSlots, SYM_WALK_STELLA_SLOT_TYPE_SPECIFIER, realtypespec, NULL);
      }
      slot->slotContextSensitiveP = true;
      if (!contextsensitiveP) {
        _Return1 = SGT_WALK_STELLA_OBJECT;
        return (setnewvaluetree);
      }
      popVariableBinding();
      popVariableBinding();
      { Cons* _Return0 = listO(5, SYM_WALK_STELLA_VRLET, listO(5, cons(objectvar, cons(objectref, NIL)), cons(valuevar, cons(realbasetype, cons(valueref, NIL))), cons(oldvaluevar, cons(oldvaluetree, NIL)), cons(newvaluevar, cons(listO(3, SYM_WALK_STELLA_UPDATE_IN_CONTEXT, oldvaluevar, cons(valuevar, listO(3, listO(3, SYM_WALK_STELLA_HOME_CONTEXT, objectvar, NIL), copytochildren, NIL))), NIL)), NIL), listO(4, SYM_WALK_STELLA_WHEN, listO(3, SYM_WALK_STELLA_NOT, listO(3, SYM_WALK_STELLA_CS_VALUEp, oldvaluevar, NIL), NIL), setnewvaluetree, NIL), valuevar, NIL);

        _Return1 = returntype;
        return (_Return0);
      }
    }
  }
}

Cons* yieldSlotValueSetterTree(StorageSlot* slot, Object* objectref, StandardObject* objecttype, Object* valueref, StandardObject* returntype, Cons* csoptions, StandardObject*& _Return1) {
  if (slot->slotContextSensitiveP) {
    return (yieldContextSensitiveSlotValueSetterTree(slot, objectref, valueref, returntype, csoptions, _Return1));
  }
  else {
    if (slot->dynamicStorageP()) {
      { Cons* _Return0 = ((Cons*)(walkWithoutTypeTree(yieldDynamicSlotValueSetterTree(slot, objectref, valueref, returntype))));

        _Return1 = returntype;
        return (_Return0);
      }
    }
    else {
      { Cons* _Return0 = yieldNativeSlotValueSetterTree(slot, objectref, objecttype, valueref);

        _Return1 = returntype;
        return (_Return0);
      }
    }
  }
}

Cons* walkSlotValueSetterTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;

    { Object* objectref = NULL;
      StandardObject* objecttype = NULL;

      objectref = walkATree(tree->rest->value, objecttype);
      { Object* slotname = tree->fourth();
        Cons* csoptions = tree->nthRest(4);
        Class* objectclass = typeSpecToClass(objecttype);
        Slot* slot = lookupSlot(objectclass, ((Symbol*)(slotname)));
        Object* valueref = NULL;
        Cons* otree = NULL;
        StandardObject* otype = NULL;

        if (!((boolean)(slot))) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Can't set a non-existent slot " << "`" << deUglifyParseTree(slotname) << "'" << std::endl << "   on the class " << "`" << className(objectclass) << "'" << "." << std::endl;
            }
          }
          return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
        }
        { Surrogate* testValue000 = safePrimaryType(slot);

          if (subtypeOfMethodSlotP(testValue000)) {
            { Slot* slot000 = slot;
              MethodSlot* slot = ((MethodSlot*)(slot000));

              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Can't set the method slot " << "`" << deUglifyParseTree(slot) << "'" << " by calling 'slot-value-setter'" << "." << std::endl;
                }
              }
              return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
            }
          }
          else if (subtypeOfStorageSlotP(testValue000)) {
            { Slot* slot001 = slot;
              StorageSlot* slot = ((StorageSlot*)(slot001));

              otype = slot->computeReturnTypeSpec(objecttype);
              valueref = walkExpressionTree(tree->rest->rest->value, otype, SYM_WALK_STELLA_SLOT_VALUE_SETTER, false, dummy1);
              otree = yieldSlotValueSetterTree(slot, objectref, objecttype, valueref, otype, csoptions, otype);
              if (proceduralExpressionP(otree)) {
                _Return1 = otype;
                return (otree);
              }
              else {
                { Object* value000 = NULL;
                  StandardObject* value001 = NULL;

                  value000 = sysTreeIfNeeded(slot, otree, objecttype, otype, value001);
                  _Return1 = value001;
                  return (((Cons*)(value000)));
                }
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
      }
    }
  }
}

Cons* walkArefTree(Cons* tree, StandardObject*& _Return1) {
  { boolean dummy1;
    StandardObject* dummy2;

    { Object* operatoR = tree->value;
      Object* otree = NULL;
      StandardObject* otype = NULL;
      ParametricTypeSpecifier* arraytype = NULL;
      StandardObject* elementtype = NULL;
      Cons* arguments = tree->rest;

      otree = walkExpressionTree(arguments->value, SGT_WALK_STELLA_ARRAY, ((Symbol*)(operatoR)), true, otype);
      if (vrletExpressionP(otree)) {
        arguments->firstSetter(otree);
        return (percolateOutVrletExpression(tree, ((Cons*)(otree)), SGT_WALK_STELLA_UNKNOWN, _Return1));
      }
      if (!(arrayTypeSpecifierP(otype))) {
        return (walkDontCallMeTree(tree, SGT_WALK_STELLA_UNKNOWN, _Return1));
      }
      arraytype = ((ParametricTypeSpecifier*)(otype));
      elementtype = extractParameterType(arraytype, SYM_WALK_STELLA_ANY_VALUE, dummy1);
      { boolean testValue000 = false;

        testValue000 = indefiniteArrayTypeP(arraytype);
        if (testValue000) {
          { boolean alwaysP000 = true;

            { IntegerWrapper* dim = NULL;
              Cons* iter000 = arrayTypeDimensions(arraytype)->rest();

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                dim = ((IntegerWrapper*)(iter000->value));
                if (!((boolean)(dim))) {
                  alwaysP000 = false;
                  break;
                }
              }
            }
            testValue000 = alwaysP000;
          }
          testValue000 = !testValue000;
        }
        if (testValue000) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Can't AREF underspecified array type" << std::endl << "   " << "`" << deUglifyParseTree(arraytype) << "'" << " in" << std::endl << "   " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
            }
          }
          return (walkDontCallMeTree(tree, SGT_WALK_STELLA_UNKNOWN, _Return1));
        }
      }
      arguments->firstSetter(otree);
      arguments = arguments->rest;
      if (operatoR == SYM_WALK_STELLA_AREF_SETTER) {
        otree = walkExpressionTree(arguments->value, elementtype, ((Symbol*)(operatoR)), true, otype);
        arguments->firstSetter(otree);
        if (vrletExpressionP(otree)) {
          return (percolateOutVrletExpression(tree, ((Cons*)(otree)), SGT_WALK_STELLA_UNKNOWN, _Return1));
        }
        arguments = arguments->rest;
      }
      if (!(arguments->length() == arrayTypeRank(arraytype))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "AREF indices don't match the rank of the array in" << std::endl << "   " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
          }
        }
      }
      while (!(arguments == NIL)) {
        otree = walkExpressionTree(arguments->value, SGT_WALK_STELLA_INTEGER, ((Symbol*)(operatoR)), true, otype);
        arguments->firstSetter(otree);
        if (vrletExpressionP(otree)) {
          return (percolateOutVrletExpression(tree, ((Cons*)(otree)), SGT_WALK_STELLA_UNKNOWN, _Return1));
        }
        arguments = arguments->rest;
      }
      return (sysTree(listO(3, SYM_WALK_STELLA_SYS_CALL_METHOD, arraytype->specifierBaseType, cons(operatoR, cons(sysTree(tree->rest->value, arraytype, dummy2), tree->rest->rest->concatenate(NIL, 0)))), elementtype, _Return1));
    }
  }
}

StandardObject* safeYieldTypeSpecifier(Object* typetree) {
  if (((boolean)(typetree))) {
    { StandardObject* typespec = typetree->yieldTypeSpecifier();

      validateTypeSpecifier(typespec, NULL, true);
      return (typespec);
    }
  }
  else {
    return (NULL);
  }
}

Cons* walkADeclaration(Symbol* variable, Object* typetree, Object* value, boolean inputparameterP) {
  { StandardObject* sourcetype = NULL;
    StandardObject* targettype = safeYieldTypeSpecifier(typetree);
    Surrogate* methodownertype = (((boolean)(oMETHODBEINGWALKEDo)) ? oMETHODBEINGWALKEDo->slotOwner : ((Surrogate*)(NULL)));
    Object* ovalue = NULL;

    if (((boolean)(targettype)) &&
        (((boolean)(methodownertype)) &&
         (!voidP(methodownertype)))) {
      targettype = computeRelativeTypeSpec(targettype, methodownertype);
    }
    if (!(inputparameterP)) {
      pushVariableBinding(variable, SGT_WALK_STELLA_UNINITIALIZED);
      ovalue = walkExpressionTree(value, targettype, SYM_WALK_STELLA_VARIABLE_DECLARATION, true, sourcetype);
      if (!((boolean)(targettype))) {
        targettype = sourcetype;
      }
      popVariableBinding();
    }
    pushVariableBinding(variable, targettype);
    if (inputparameterP) {
      return (cons(variable, cons(targettype, NIL)));
    }
    else {
      return (cons(trueVariableName(variable), cons(targettype, cons(ovalue, NIL))));
    }
  }
}

Cons* walkVariableDeclarations(Cons* declarations) {
  { Cons* odeclarations = NIL;
    Symbol* variable = NULL;
    boolean vrletencounteredP = false;

    { Object* decl = NULL;
      Cons* iter000 = declarations;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        decl = iter000->value;
        if (safePrimaryType(decl) == SGT_WALK_STELLA_CONS) {
          { Object* decl000 = decl;
            Cons* decl = ((Cons*)(decl000));

            if (vrletencounteredP) {
              odeclarations = cons(decl, odeclarations);
              continue;
            }
            else if (!symbolP(decl->value)) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal variable in `let' declaration: " << "`" << deUglifyParseTree(decl) << "'" << "." << std::endl;
                }
              }
              variable = SYM_WALK_STELLA_ILLEGAL_VARIABLE;
            }
            else {
              variable = ((Symbol*)(decl->value));
              if (((boolean)(variable->lookupGlobalVariable())) ||
                  constantSymbolP(variable)) {
                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  signalTranslationError();
                  if (!(suppressWarningsP())) {
                    printErrorContext(">> ERROR: ", STANDARD_ERROR);
                    *(STANDARD_ERROR->nativeStream) << std::endl << " " << "`" << ((constantSymbolP(variable) ? "Illegal binding of constant value " : "Illegal binding of global or special variable ")) << "'" << "in `let' declaration:" << std::endl << "    " << "`" << deUglifyParseTree(decl) << "'" << "." << std::endl;
                  }
                }
                variable = SYM_WALK_STELLA_ILLEGAL_VARIABLE;
              }
            }
            switch (decl->length()) {
              case 1: 
                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  signalTranslationError();
                  if (!(suppressWarningsP())) {
                    printErrorContext(">> ERROR: ", STANDARD_ERROR);
                    *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing argument(s) in `let' declaration: " << "`" << deUglifyParseTree(decl) << "'" << "." << std::endl;
                  }
                }
                break;
              case 2: 
                if (decl->rest->value == SYM_WALK_STELLA_NULL) {
                  { 
                    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                    signalTranslationError();
                    if (!(suppressWarningsP())) {
                      printErrorContext(">> ERROR: ", STANDARD_ERROR);
                      *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing type specifier in `let' declaration: " << "`" << deUglifyParseTree(decl) << "'" << "." << std::endl;
                    }
                  }
                }
                odeclarations = cons(walkADeclaration(variable, NULL, decl->rest->value, false), odeclarations);
                break;
              case 3: 
                odeclarations = cons(walkADeclaration(variable, decl->rest->value, decl->rest->rest->value, false), odeclarations);
                break;
              default:
                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  signalTranslationError();
                  if (!(suppressWarningsP())) {
                    printErrorContext(">> ERROR: ", STANDARD_ERROR);
                    *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Too many terms in `let' declaration:" << "`" << deUglifyParseTree(decl) << "'" << "." << std::endl;
                  }
                }
                break;
            }
            if (proceduralExpressionP(((Cons*)(odeclarations->value))->rest->rest->value)) {
              vrletencounteredP = true;
              popVariableBinding();
            }
          }
        }
        else {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal `let' declaration: " << "`" << deUglifyParseTree(decl) << "'" << "." << std::endl;
            }
          }
        }
      }
    }
    return (odeclarations->reverse());
  }
}

Cons* transformLetWithProceduralExpression(Cons* tree) {
  { Cons* firstdeclaration = ((Cons*)(((Cons*)(tree->rest->value))->value));
    Object* typetree = firstdeclaration->rest->value;
    Object* vrlettree = walkWithoutTypeTree(firstdeclaration->rest->rest->value);

    if (typetree == SGT_WALK_STELLA_UNKNOWN) {
      firstdeclaration->rest = firstdeclaration->rest->rest;
    }
    { Cons* otree = NULL;
      StandardObject* unusedtypespec = NULL;

      otree = transformProceduralExpression(tree, ((Cons*)(vrlettree)), ((StandardObject*)(typetree)), unusedtypespec);
      unusedtypespec = unusedtypespec;
      return (otree);
    }
  }
}

void popLocalVariableBindings(Cons* declarations) {
  { Object* d = NULL;
    Cons* iter000 = declarations;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      d = iter000->value;
      d = d;
      popVariableBinding();
    }
  }
}

Cons* walkLetTree(Cons* tree, StandardObject*& _Return1) {
  tree->secondSetter(walkVariableDeclarations(((Cons*)(tree->rest->value))));
  { boolean testValue000 = false;

    { boolean foundP000 = false;

      { Cons* d = NULL;
        Cons* iter000 = ((Cons*)(tree->rest->value));

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          d = ((Cons*)(iter000->value));
          if (proceduralExpressionP(d->rest->rest->value)) {
            foundP000 = true;
            break;
          }
        }
      }
      testValue000 = foundP000;
    }
    testValue000 = !testValue000;
    if (testValue000) {
      tree->rest->rest = walkListOfStatements(tree->rest->rest);
      popLocalVariableBindings(((Cons*)(tree->rest->value)));
      return (sysTree(tree, SGT_WALK_STELLA_VOID, _Return1));
    }
  }
  { Cons* originaldeclarations = ((Cons*)(tree->rest->value));
    Cons* leadingdeclarations = NIL;
    Cons* trailingdeclarations = NIL;
    boolean leadingP = true;

    { Cons* d = NULL;
      Cons* iter001 = ((Cons*)(originaldeclarations));

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        d = ((Cons*)(iter001->value));
        if (proceduralExpressionP(d->rest->rest->value)) {
          leadingP = false;
        }
        if (leadingP) {
          leadingdeclarations = cons(d, leadingdeclarations);
        }
        else {
          trailingdeclarations = cons(d, trailingdeclarations);
        }
      }
    }
    leadingdeclarations = leadingdeclarations->reverse();
    trailingdeclarations = trailingdeclarations->reverse();
    tree->secondSetter(trailingdeclarations);
    tree = transformLetWithProceduralExpression(tree);
    if (!(leadingdeclarations == NIL)) {
      popLocalVariableBindings(leadingdeclarations);
      tree = listO(3, SYM_WALK_STELLA_LET, leadingdeclarations, cons(tree, NIL));
    }
    return (walkAConsTree(tree, _Return1));
  }
}

// Stack mirroring the current state of bound specials
// with their associated old-value variables.
DEFINE_STELLA_SPECIAL(oSPECIALVARIABLESTACKo, KeyValueList* , NULL);

// `true' if using specials is enabled and legal.
DEFINE_STELLA_SPECIAL(oSPECIALSENABLEDpo, boolean , true);

// Number of specials bound at the most recent entry
// to a LOOP/WHILE/FOREACH construct.
DEFINE_STELLA_SPECIAL(oNOFSPECIALSATLOOPENTRYo, int , 0);

Keyword* specialImplementationStyle() {
  if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP) {
    return (KWD_WALK_COMMON_LISP);
  }
  else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP) {
    return (KWD_WALK_UNBIND_WITH_DESTRUCTORS);
  }
  else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA) {
    return (KWD_WALK_COMMON_LISP);
  }
  else {
    return (KWD_WALK_UNWIND_PROTECT);
  }
}

void pushSpecial(Symbol* variable, Symbol* oldvaluevariable) {
  oSPECIALVARIABLESTACKo->theKvList = kvCons(variable, oldvaluevariable, oSPECIALVARIABLESTACKo->theKvList);
}

void popSpecial() {
  { KvCons* kvlist = oSPECIALVARIABLESTACKo->theKvList;

    oSPECIALVARIABLESTACKo->theKvList = kvlist->rest;
    freeKvCons(kvlist);
  }
}

Symbol* lookupOldValueVariable(Symbol* variable) {
  return (((Symbol*)(lookupVariableTable(oSPECIALVARIABLESTACKo, variable))));
}

boolean needToUnbindSpecialsP() {
  return (oSPECIALSENABLEDpo &&
      ((oSPECIALVARIABLESTACKo->length() > 0) &&
       (!getQuotedTree("((:COMMON-LISP :UNBIND-WITH-DESTRUCTORS) \"/STELLA\")", "/STELLA")->memberP(specialImplementationStyle()))));
}

Cons* yieldSpecialUnbindTree(int nofbindings) {
  { Cons* otree = NIL;

    if (specialImplementationStyle() == KWD_WALK_UNWIND_PROTECT) {
      { Symbol* variable = NULL;
        Symbol* oldvaluevariable = NULL;
        KvCons* iter000 = oSPECIALVARIABLESTACKo->theKvList;

        for  (; ((boolean)(iter000)); 
              iter000 = iter000->rest) {
          variable = ((Symbol*)(iter000->key));
          oldvaluevariable = ((Symbol*)(iter000->value));
          if ((nofbindings = nofbindings - 1) >= 0) {
            { Cons* value000 = NULL;

              { Cons* tree = NULL;
                Cons* iter001 = otree;

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  tree = ((Cons*)(iter001->value));
                  if (tree->rest->value == variable) {
                    value000 = tree;
                    break;
                  }
                }
              }
              otree = otree->remove(value000);
            }
            otree = cons(listO(3, SYM_WALK_STELLA_SETQ, variable, cons(oldvaluevariable, NIL)), otree);
          }
        }
      }
      return (((Cons*)(prognify(otree->reverse()))));
    }
    else {
      return (NULL);
    }
  }
}

Cons* yieldReturnSpecialUnbindTree() {
  return (yieldSpecialUnbindTree(oSPECIALVARIABLESTACKo->length()));
}

Cons* yieldLoopExitSpecialUnbindTree() {
  return (yieldSpecialUnbindTree(oSPECIALVARIABLESTACKo->length() - oNOFSPECIALSATLOOPENTRYo));
}

Cons* walkSpecialTree(Cons* tree, StandardObject*& _Return1) {
  if (!(oSPECIALSENABLEDpo)) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "'special' statement not legal in the current context: " << std::endl << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
      }
    }
    return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
  }
  { boolean testValue000 = false;

    if (tree->length() < 2) {
      testValue000 = true;
    }
    else {
      if (!consP(tree->rest->value)) {
        testValue000 = true;
      }
      else {
        {
          { boolean alwaysP000 = true;

            { Cons* binding = NULL;
              Cons* iter000 = ((Cons*)(tree->rest->value));

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                binding = ((Cons*)(iter000->value));
                if (!(consP(binding) &&
                    (symbolP(binding->value) &&
                     (binding->length() == 2)))) {
                  alwaysP000 = false;
                  break;
                }
              }
            }
            testValue000 = alwaysP000;
          }
          testValue000 = !testValue000;
        }
      }
    }
    if (testValue000) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal 'special' statement: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
        }
      }
      return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
    }
  }
  if (((Cons*)(tree->rest->value))->length() == 0) {
    tree->firstSetter(SYM_WALK_STELLA_LET);
    return (walkLetTree(tree, _Return1));
  }
  { GlobalVariable* variable = NULL;

    { Cons* binding = NULL;
      Cons* iter001 = ((Cons*)(tree->rest->value));

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        binding = ((Cons*)(iter001->value));
        variable = ((Symbol*)(binding->value))->lookupGlobalVariable();
        if ((!((boolean)(variable))) ||
            (!variable->variableSpecialP)) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Trying to bind non-special variable " << "`" << binding->value << "'" << std::endl << " in 'special' statement" << "." << std::endl;
            }
          }
        }
      }
    }
  }
  { Keyword* testValue001 = specialImplementationStyle();

    if (testValue001 == KWD_WALK_COMMON_LISP) {
      return (walkClSpecialTree(tree, _Return1));
    }
    else if (testValue001 == KWD_WALK_UNBIND_WITH_DESTRUCTORS) {
      return (walkClSpecialTree(tree, _Return1));
    }
    else if (testValue001 == KWD_WALK_UNWIND_PROTECT) {
      return (walkUnwindProtectSpecialTree(tree, _Return1));
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Cons* walkClSpecialTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;
    StandardObject* dummy2;
    StandardObject* dummy3;

    { Cons* bindings = ((Cons*)(tree->rest->value));
      Cons* body = tree->rest->rest;
      Symbol* variablename = NULL;
      StandardObject* variabletype = NULL;
      boolean bindviasetqP = false;
      Cons* bindviasetqtrees = NIL;
      Object* otree = NULL;

      { Cons* binding = NULL;
        Cons* iter000 = bindings;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          binding = ((Cons*)(iter000->value));
          variablename = ((Symbol*)(binding->value));
          variabletype = lookupGlobalVariableType(variablename);
          if (bindviasetqP) {
            bindviasetqtrees = cons(walkATree(listO(3, SYM_WALK_STELLA_SETQ, variablename, cons(binding->rest->value, NIL)), dummy1), bindviasetqtrees);
            binding->secondSetter(variabletype);
            binding->rest->rest = cons(SYM_WALK_STELLA_NULL, NIL);
          }
          else {
            otree = walkExpressionTree(binding->rest->value, variabletype, SYM_WALK_STELLA_SPECIAL, true, dummy2);
            if (proceduralExpressionP(otree)) {
              bindviasetqP = true;
              bindviasetqtrees = cons(walkATree(listO(3, SYM_WALK_STELLA_SETQ, variablename, cons(otree, NIL)), dummy3), bindviasetqtrees);
              otree = SYM_WALK_STELLA_NULL;
            }
            binding->secondSetter(variabletype);
            binding->rest->rest = cons(otree, NIL);
          }
        }
      }
      tree->firstSetter(SYM_WALK_STELLA_SPECIAL);
      tree->rest->rest = bindviasetqtrees->reverse()->concatenate(walkListOfStatements(body), 0);
      return (sysTree(tree, SGT_WALK_STELLA_VOID, _Return1));
    }
  }
}

Cons* walkUnwindProtectSpecialTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;

    { Cons* bindings = ((Cons*)(tree->rest->value));
      Cons* body = tree->rest->rest;
      Symbol* variable = NULL;
      Symbol* oldvaluevariable = NULL;
      Cons* oldvaluebindings = NIL;
      Cons* bindtrees = NIL;
      Cons* unbindtrees = NIL;

      { Cons* binding = NULL;
        Cons* iter000 = bindings;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          binding = ((Cons*)(iter000->value));
          variable = ((Symbol*)(binding->value));
          bindtrees = cons(listO(3, SYM_WALK_STELLA_SETQ, variable, cons(binding->rest->value, NIL)), bindtrees);
          oldvaluevariable = localGensym(stringConcatenate("OLD-", variable->symbolName, 0));
          pushSpecial(variable, oldvaluevariable);
          oldvaluebindings = cons(cons(oldvaluevariable, cons(variable, NIL)), oldvaluebindings);
          unbindtrees = cons(listO(3, SYM_WALK_STELLA_SETQ, variable, cons(oldvaluevariable, NIL)), unbindtrees);
        }
      }
      tree = ((Cons*)(walkATree(listO(3, SYM_WALK_STELLA_LET, oldvaluebindings->reverse(), bindtrees->reverse()->concatenate(cons(listO(3, SYM_WALK_STELLA_UNWIND_PROTECT, prognify(body), unbindtrees->concatenate(NIL, 0)), NIL), 0)), dummy1)));
      { Cons* binding = NULL;
        Cons* iter001 = bindings;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          binding = ((Cons*)(iter001->value));
          binding = binding;
          popSpecial();
        }
      }
      _Return1 = SGT_WALK_STELLA_VOID;
      return (tree);
    }
  }
}

Cons* walkCastTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;

    if (badArgumentCountP(tree, 2)) {
      return (walkDontCallMeTree(tree, SGT_WALK_STELLA_UNKNOWN, _Return1));
    }
    { StandardObject* typespec = tree->rest->rest->value->yieldTypeSpecifier();

      tree->secondSetter(walkExpressionTree(tree->rest->value, SGT_WALK_STELLA_UNKNOWN, SYM_WALK_STELLA_CAST, true, dummy1));
      if (vrletExpressionP(tree->rest->value)) {
        return (percolateOutVrletExpression(tree, ((Cons*)(tree->rest->value)), typespec, _Return1));
      }
      tree->thirdSetter(typespec);
      if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP) &&
          ((tree->value == SYM_WALK_STELLA_CAST) &&
           (oSAFETYo >= 2))) {
        registerSymbol(typeSpecToBaseType(typespec));
      }
      _Return1 = typespec;
      return (tree);
    }
  }
}

boolean valuesTreeP(Object* tree) {
  return (consP(tree) &&
      (SYM_WALK_STELLA_VALUES == ((Cons*)(tree))->value));
}

Cons* walkValuesTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;

    { Object* otree = NULL;
      StandardObject* otype = NULL;
      Cons* bindtree = NIL;
      Symbol* valuevar = NULL;
      boolean hasproceduralvalueP = false;

      { ConsIterator* it = tree->rest->allocateIterator();

        for (; it->nextP(); ) {
          otree = walkATree(it->value, otype);
          if (vrletExpressionP(otree)) {
            it->valueSetter(otree);
            hasproceduralvalueP = true;
            break;
          }
          otree = sysTree(otree, otype, dummy1);
          if (voidP(otype)) {
            otree = ((Cons*)(otree))->concatenate(cons(SGT_WALK_STELLA_VOID, NIL), 0);
          }
          it->valueSetter(otree);
        }
      }
      if (!hasproceduralvalueP) {
        tree->firstSetter(SYM_WALK_STELLA_PROGN);
        _Return1 = SGT_WALK_STELLA_VOID;
        return (tree);
      }
      { ConsIterator* it = tree->rest->allocateIterator();

        for (; it->nextP(); ) {
          { Cons* value = ((Cons*)(it->value));

            if (proceduralExpressionP(value) ||
                (!atomicExpressionP(value->rest->value))) {
              valuevar = localGensym("VALUE");
              bindtree = cons(cons(valuevar, cons((proceduralExpressionP(value) ? value : value->rest->value), NIL)), bindtree);
              if (proceduralExpressionP(value)) {
                it->valueSetter(valuevar);
                break;
              }
              else {
                value->secondSetter(valuevar);
              }
            }
          }
        }
      }
      return (walkAConsTree(listO(3, SYM_WALK_STELLA_LET, bindtree->reverse(), cons(tree, NIL)), _Return1));
    }
  }
}

Object* walkMvExpressionTree(Object* tree, List* targettypes, Symbol* operatoR, Cons*& _Return1, List*& _Return2) {
  { 
    BIND_STELLA_SPECIAL(oTARGETTYPEo, StandardObject*, ((targettypes->length() == 1) ? ((StandardObject*)(((StandardObject*)(targettypes->first())))) : SGT_WALK_STELLA_UNKNOWN));
    { Object* otree = NULL;
      Cons* valuestree = NULL;
      List* sourcetypes = NULL;

      otree = walkMvTree(tree, valuestree, sourcetypes);
      if (!(sourcetypes->length() == targettypes->length())) {
        if ((sourcetypes->length() == 1) &&
            (SGT_WALK_STELLA_UNKNOWN == ((StandardObject*)(sourcetypes->first())))) {
          warnAboutUnknownSourceType(otree);
        }
        else {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "`" << deUglifyParseTree(operatoR) << "'" << " operator expected " << "`" << targettypes->length() << "'" << " value(s) from " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
            }
          }
        }
        { Object* _Return0 = otree;

          _Return1 = valuestree;
          _Return2 = targettypes->copy();
          return (_Return0);
        }
      }
      if (sourcetypes->emptyP()) {
        _Return1 = valuestree;
        _Return2 = sourcetypes;
        return (otree);
      }
      if (((boolean)(valuestree))) {
        tree = coerceMvTree(valuestree, operatoR, sourcetypes, targettypes, valuestree, targettypes);
      }
      else {
        otree = coerceMvTree(otree, operatoR, sourcetypes, targettypes, valuestree, targettypes);
      }
      sourcetypes->free();
      _Return1 = valuestree;
      _Return2 = targettypes;
      return (otree);
    }
  }
}

List* listifyTypeSpec(StandardObject* typespec) {
  if (voidP(typespec)) {
    return (list(0));
  }
  else {
    return (list(1, typespec));
  }
}

Slot* slotFromExpressionTree(Cons* tree) {
  if (SYM_WALK_STELLA_TYPED_SYS == tree->value) {
    tree = ((Cons*)(tree->rest->value));
  }
  { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

    if ((testValue000 == SYM_WALK_STELLA_SYS_SLOT_VALUE) ||
        ((testValue000 == SYM_WALK_STELLA_SYS_CALL_METHOD) ||
         ((testValue000 == SYM_WALK_STELLA_SYS_CALL_SUPER_METHOD) ||
          ((testValue000 == SYM_WALK_STELLA_SYS_SLOT_VALUE_SETTER) ||
           (testValue000 == SYM_WALK_STELLA_SYS_CALL_METHOD_SETTER))))) {
      return (lookupSlot(((Class*)(((Surrogate*)(tree->rest->value))->surrogateValue)), ((Symbol*)(tree->rest->rest->value))));
    }
    else if (testValue000 == SYM_WALK_STELLA_SYS_CALL_FUNCTION) {
      { MethodSlot* function = lookupFunction(((Symbol*)(tree->rest->value)));

        if (((boolean)(function)) &&
            isaP(function, SGT_WALK_STELLA_METHOD_SLOT)) {
          return (function);
        }
      }
    }
    else {
      return (NULL);
    }
  }
  return (NULL);
}

Object* walkMvTree(Object* tree, Cons*& _Return1, List*& _Return2) {
  { Object* otree = NULL;
    StandardObject* otype = NULL;
    Slot* slot = NULL;

    if (valuesTreeP(tree)) {
      return (walkMvValuesTree(((Cons*)(tree)), _Return1, _Return2));
    }
    otree = walkATree(tree, otype);
    if (consP(otree)) {
      slot = slotFromExpressionTree(((Cons*)(otree)));
    }
    if (((boolean)(slot))) {
      if (subtypeOfMethodSlotP(safePrimaryType(slot))) {
        { Slot* slot000 = slot;
          MethodSlot* slot = ((MethodSlot*)(slot000));

          { Object* _Return0 = otree;

            _Return1 = NULL;
            _Return2 = slot->methodReturnTypeSpecifiers_reader()->copy();
            return (_Return0);
          }
        }
      }
      else {
      }
    }
    { Object* _Return0 = otree;

      _Return1 = NULL;
      _Return2 = listifyTypeSpec(otype);
      return (_Return0);
    }
  }
}

Cons* walkMvValuesTree(Cons* tree, Cons*& _Return1, List*& _Return2) {
  if (tree->length() == 1) {
    { Cons* _Return0 = tree;

      _Return1 = tree;
      _Return2 = listifyTypeSpec(SGT_WALK_STELLA_VOID);
      return (_Return0);
    }
  }
  { Object* otree = NULL;
    StandardObject* otype = NULL;
    List* returntypes = newList();
    Cons* typedsystree = NULL;

    otype = otype;
    otree = walkValuesTree(tree, otype);
    tree->firstSetter(SYM_WALK_STELLA_VALUES);
    { ConsIterator* it = tree->rest->allocateIterator();

      for (; it->nextP(); ) {
        typedsystree = ((Cons*)(it->value));
        returntypes->push(((StandardObject*)(typedsystree->rest->rest->value)));
        if (SGT_WALK_STELLA_UNKNOWN == typedsystree->rest->rest->value) {
          it->valueSetter(typedsystree->rest->value);
        }
      }
    }
    { Cons* _Return0 = ((Cons*)(otree));

      _Return1 = tree;
      _Return2 = returntypes->reverse();
      return (_Return0);
    }
  }
}

Object* coerceMvTree(Object* tree, Symbol* operatoR, List* sourcetypes, List* targettypes, Cons*& _Return1, List*& _Return2) {
  { StandardObject* dummy1;
    StandardObject* dummy2;
    StandardObject* dummy3;

    { boolean valuestreeP = valuesTreeP(tree);
      Cons* valuestree = NIL;
      boolean needtemporariesP = false;
      boolean successP = false;
      Object* otree = NULL;
      StandardObject* otype = NULL;
      List* returntypes = newList();

      if (valuestreeP) {
        valuestree = ((Cons*)(tree));
      }
      else {
        valuestree = cons(SYM_WALK_STELLA_VALUES, NIL);
        { StandardObject* type = NULL;
          Cons* iter000 = sourcetypes->theConsList;
          Cons* collect000 = NULL;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest) {
            type = ((StandardObject*)(iter000->value));
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(sysTree(NULL, type, dummy1), NIL);
                if (valuestree == NIL) {
                  valuestree = collect000;
                }
                else {
                  addConsToEndOfConsList(valuestree, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(sysTree(NULL, type, dummy2), NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
      }
      { StandardObject* tgtts = NULL;
        Cons* iter001 = targettypes->theConsList;
        StandardObject* srcts = NULL;
        Cons* iter002 = sourcetypes->theConsList;
        int i = NULL_INTEGER;
        int iter003 = 1;
        ConsIterator* it = valuestree->rest->allocateIterator();
        Cons* collect001 = NULL;

        for  (; (!(iter001 == NIL)) &&
                  ((!(iter002 == NIL)) &&
                   it->nextP()); 
              iter001 = iter001->rest,
              iter002 = iter002->rest,
              iter003 = iter003 + 1) {
          tgtts = ((StandardObject*)(iter001->value));
          srcts = ((StandardObject*)(iter002->value));
          i = iter003;
          otree = helpCoerceATree(it->value, srcts, tgtts, false, otype, successP);
          if (!(successP)) {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Type clash on argument " << "`" << deUglifyParseTree(wrapInteger(i)) << "'" << " of " << "`" << deUglifyParseTree(operatoR) << "'" << " operator." << std::endl << " " << "`" << deUglifyParseTree(srcts) << "'" << " found where " << "`" << deUglifyParseTree(tgtts) << "'" << " expected" << "." << std::endl;
              }
            }
            { Object* _Return0 = tree;

              _Return1 = ((Cons*)((valuestreeP ? tree : ((Object*)(NULL)))));
              _Return2 = targettypes->copy();
              return (_Return0);
            }
          }
          if ((!eqlP(otree, it->value)) ||
              ((i > 1) &&
               ((!valuestreeP) &&
                ((!(oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP)) &&
                 ((!(typeSpecToBaseType(tgtts) == SGT_WALK_STELLA_UNKNOWN)) &&
                  (!(typeSpecToBaseType(srcts) == typeSpecToBaseType(tgtts)))))))) {
            needtemporariesP = true;
          }
          it->valueSetter(otree);
          if (!((boolean)(collect001))) {
            {
              collect001 = cons(otype, NIL);
              if (returntypes->theConsList == NIL) {
                returntypes->theConsList = collect001;
              }
              else {
                addConsToEndOfConsList(returntypes->theConsList, collect001);
              }
            }
          }
          else {
            {
              collect001->rest = cons(otype, NIL);
              collect001 = collect001->rest;
            }
          }
        }
      }
      if (valuestreeP) {
        _Return1 = ((Cons*)(tree));
        _Return2 = returntypes;
        return (tree);
      }
      if (!needtemporariesP) {
        _Return1 = NULL;
        _Return2 = returntypes;
        return (tree);
      }
      valuestree = cons(SYM_WALK_STELLA_VALUES, NIL);
      { int i = NULL_INTEGER;
        int iter004 = 1;
        int upperBound000 = targettypes->length();
        Cons* collect002 = NULL;

        for  (; iter004 <= upperBound000; 
              iter004 = iter004 + 1) {
          i = iter004;
          i = i;
          if (!((boolean)(collect002))) {
            {
              collect002 = cons(localGensym("VALUE"), NIL);
              if (valuestree == NIL) {
                valuestree = collect002;
              }
              else {
                addConsToEndOfConsList(valuestree, collect002);
              }
            }
          }
          else {
            {
              collect002->rest = cons(localGensym("VALUE"), NIL);
              collect002 = collect002->rest;
            }
          }
        }
      }
      otree = walkWithoutTypeTree(listO(3, SYM_WALK_STELLA_MV_BIND, copyConsList(valuestree->rest), cons(tree, cons(valuestree, NIL))));
      valuestree->firstSetter(getQuotedTree("((VALUES) \"/STELLA\")", "/STELLA"));
      { ConsIterator* it = valuestree->rest->allocateIterator();
        StandardObject* srcts = NULL;
        Cons* iter005 = sourcetypes->theConsList;
        StandardObject* tgtts = NULL;
        Cons* iter006 = targettypes->theConsList;

        for  (; it->nextP() &&
                  ((!(iter005 == NIL)) &&
                   (!(iter006 == NIL))); 
              iter005 = iter005->rest,
              iter006 = iter006->rest) {
          srcts = ((StandardObject*)(iter005->value));
          tgtts = ((StandardObject*)(iter006->value));
          it->valueSetter(coerceATree(it->value, srcts, tgtts, dummy3));
        }
      }
      _Return1 = valuestree;
      _Return2 = returntypes;
      return (otree);
    }
  }
}

Cons* walkReturnAndUnbindSpecials(Cons* tree, StandardObject*& _Return1) {
  { Cons* unbindtree = yieldReturnSpecialUnbindTree();
    Cons* valuetrees = tree->rest;
    Cons* valuevariables = NIL;
    Cons* valuebindings = NIL;

    { 
      BIND_STELLA_SPECIAL(oSPECIALSENABLEDpo, boolean, false);
      if (valuetrees->length() == 0) {
        return (walkAConsTree(listO(3, SYM_WALK_STELLA_PROGN, unbindtree, cons(tree, NIL)), _Return1));
      }
      if ((valuetrees->length() == 1) &&
          (!(oMETHODBEINGWALKEDo->methodReturnTypeSpecifiers_reader()->rest() == NIL))) {
        { int i = NULL_INTEGER;
          int iter000 = 0;
          int upperBound000 = oMETHODBEINGWALKEDo->methodReturnTypeSpecifiers_reader()->length() - 1;
          Cons* collect000 = NULL;

          for  (; iter000 <= upperBound000; 
                iter000 = iter000 + 1) {
            i = iter000;
            i = i;
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(localGensym("RETURN-VALUE"), NIL);
                if (valuevariables == NIL) {
                  valuevariables = collect000;
                }
                else {
                  addConsToEndOfConsList(valuevariables, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(localGensym("RETURN-VALUE"), NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        tree->rest = valuevariables;
        return (walkAConsTree(listO(3, SYM_WALK_STELLA_MV_BIND, copyConsList(valuevariables), cons(valuetrees->value, treeToTrees(unbindtree)->concatenate(cons(tree, NIL), 0))), _Return1));
      }
      { ConsIterator* it = valuetrees->allocateIterator();

        for (; it->nextP(); ) {
          if (consP(it->value) ||
              (symbolP(it->value) &&
               ((boolean)(lookupOldValueVariable(((Symbol*)(it->value))))))) {
            valuebindings = cons(cons(localGensym("RETURN-VALUE"), cons(it->value, NIL)), valuebindings);
            it->valueSetter(((Cons*)(valuebindings->value))->value);
          }
        }
      }
      return (walkAConsTree(listO(3, SYM_WALK_STELLA_LET, valuebindings->reverse(), treeToTrees(unbindtree)->concatenate(cons(tree, NIL), 0)), _Return1));
    }
  }
}

Cons* walkReturnTree(Cons* tree, StandardObject*& _Return1) {
  if (!((boolean)(oMETHODBEINGWALKEDo))) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Return statement encountered outside of method or function definition" << "." << std::endl;
      }
    }
    return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
  }
  oFOUNDRETURNpo = true;
  if (needToUnbindSpecialsP()) {
    return (walkReturnAndUnbindSpecials(tree, _Return1));
  }
  { MethodSlot* method = oMETHODBEINGWALKEDo;
    List* targettypes = newList();

    { StandardObject* rtype = NULL;
      Cons* iter000 = method->methodReturnTypeSpecifiers_reader()->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        rtype = ((StandardObject*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(computeRelativeTypeSpec(rtype, method->slotOwner), NIL);
            if (targettypes->theConsList == NIL) {
              targettypes->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(targettypes->theConsList, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(computeRelativeTypeSpec(rtype, method->slotOwner), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    { Object* otree = NULL;
      Cons* valuestree = NULL;
      List* valuetypes = NULL;

      otree = walkMvExpressionTree((((tree->rest->length() == 1) &&
          (!(targettypes->rest() == NIL))) ? tree->rest->value : cons(SYM_WALK_STELLA_VALUES, tree->rest->concatenate(NIL, 0))), targettypes, SYM_WALK_STELLA_RETURN, valuestree, valuetypes);
      targettypes->free();
      valuetypes->free();
      if (!((boolean)(valuestree))) {
        if (!(tree->rest == NIL)) {
          tree->secondSetter(otree);
        }
        _Return1 = SGT_WALK_STELLA_VOID;
        return (tree);
      }
      valuestree->firstSetter(SYM_WALK_STELLA_RETURN);
      _Return1 = SGT_WALK_STELLA_VOID;
      return (((Cons*)(otree)));
    }
  }
}

Cons* walkMvSetqTree(Cons* tree, StandardObject*& _Return1) {
  { boolean testValue000 = false;

    if (badArgumentCountP(tree, 2)) {
      testValue000 = true;
    }
    else {
      if (!consP(tree->rest->value)) {
        testValue000 = true;
      }
      else {
        {
          { boolean alwaysP000 = true;

            { Object* v = NULL;
              Cons* iter000 = ((Cons*)(tree->rest->value));

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                v = iter000->value;
                if (!symbolP(v)) {
                  alwaysP000 = false;
                  break;
                }
              }
            }
            testValue000 = alwaysP000;
          }
          testValue000 = !testValue000;
        }
      }
    }
    if (testValue000) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal 'mv-setq' expression: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
        }
      }
      return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
    }
  }
  { Cons* variables = ((Cons*)(tree->rest->value));
    List* targettypes = newList();

    { ConsIterator* it = variables->allocateIterator();
      Cons* collect000 = NULL;

      for (; it->nextP(); ) {
        it->valueSetter(trueVariableName(((Symbol*)(it->value))));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(lookupVariableType(((Symbol*)(it->value))), NIL);
            if (targettypes->theConsList == NIL) {
              targettypes->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(targettypes->theConsList, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(lookupVariableType(((Symbol*)(it->value))), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    { Object* otree = NULL;
      Cons* valuestree = NULL;
      List* valuetypes = NULL;

      otree = walkMvExpressionTree(tree->rest->rest->value, targettypes, SYM_WALK_STELLA_MV_SETQ, valuestree, valuetypes);
      valuetypes->free();
      targettypes->free();
      if (((boolean)(valuestree))) {
        valuestree->firstSetter(SYM_WALK_STELLA_PROGN);
        { ConsIterator* it = valuestree->rest->allocateIterator();
          Object* var = NULL;
          Cons* iter001 = variables;

          for  (; it->nextP() &&
                    (!(iter001 == NIL)); 
                iter001 = iter001->rest) {
            var = iter001->value;
            it->valueSetter(listO(3, SYM_WALK_STELLA_SETQ, var, cons(it->value, NIL)));
          }
        }
        tree->rest->rest = NIL;
        return (sysTree(otree, SGT_WALK_STELLA_VOID, _Return1));
      }
      tree->thirdSetter(otree);
      return (sysTree(tree, SGT_WALK_STELLA_VOID, _Return1));
    }
  }
}

Cons* walkMvBindTree(Cons* tree, StandardObject*& _Return1) {
  if ((tree->length() < 3) ||
      (!consP(tree->rest->value))) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal 'mv-bind' expression: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
      }
    }
    return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
  }
  { Cons* declarations = ((Cons*)(tree->rest->value));
    Object* mvtree = tree->rest->rest->value;
    Cons* body = tree->rest->rest->rest;
    Cons* variables = NIL;
    Object* decl = NULL;
    List* targettypes = newList();

    { ConsIterator* it = declarations->allocateIterator();

      for (; it->nextP(); ) {
        decl = it->value;
        { Surrogate* testValue000 = safePrimaryType(decl);

          if (testValue000 == SGT_WALK_STELLA_CONS) {
            { Object* decl000 = decl;
              Cons* decl = ((Cons*)(decl000));

              if (!(symbolP(decl->value) &&
                  (decl->length() == 2))) {
                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  signalTranslationError();
                  if (!(suppressWarningsP())) {
                    printErrorContext(">> ERROR: ", STANDARD_ERROR);
                    *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal variable declaration " << "`" << deUglifyParseTree(decl) << "'" << " in 'mv-bind' expression: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
                  }
                }
                return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
              }
              targettypes->push(decl->rest->value->yieldTypeSpecifier());
              decl->rest->rest = cons(SYM_WALK_STELLA_NULL, NIL);
              variables = cons(decl->value, variables);
            }
          }
          else if (subtypeOfSymbolP(testValue000)) {
            { Object* decl001 = decl;
              Symbol* decl = ((Symbol*)(decl001));

              targettypes->push(SGT_WALK_STELLA_UNKNOWN);
              it->valueSetter(cons(decl, listO(3, SGT_WALK_STELLA_UNKNOWN, SYM_WALK_STELLA_NULL, NIL)));
              variables = cons(decl, variables);
            }
          }
          else {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal variable " << "`" << deUglifyParseTree(decl) << "'" << " in 'mv-bind' expression: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
              }
            }
            return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
          }
        }
      }
    }
    variables = variables->reverse();
    { Object* variable = NULL;
      Cons* iter000 = variables;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        variable = iter000->value;
        pushVariableBinding(((Symbol*)(variable)), SGT_WALK_STELLA_UNINITIALIZED);
      }
    }
    { Object* omvtree = NULL;
      Cons* valuestree = NULL;
      List* variabletypes = NULL;

      omvtree = walkMvExpressionTree(mvtree, targettypes->reverse(), SYM_WALK_STELLA_MV_BIND, valuestree, variabletypes);
      { Object* variable = NULL;
        Cons* iter001 = variables;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          variable = iter001->value;
          variable = variable;
          popVariableBinding();
        }
      }
      targettypes->free();
      tree->rest->rest->rest = NIL;
      { Cons* decl = NULL;
        Cons* iter002 = ((Cons*)(declarations));
        StandardObject* type = NULL;
        Cons* iter003 = variabletypes->theConsList;

        for  (; (!(iter002 == NIL)) &&
                  (!(iter003 == NIL)); 
              iter002 = iter002->rest,
              iter003 = iter003->rest) {
          decl = ((Cons*)(iter002->value));
          type = ((StandardObject*)(iter003->value));
          if (SGT_WALK_STELLA_UNKNOWN == decl->rest->value) {
            decl->secondSetter(type);
          }
        }
      }
      variabletypes->free();
      if (((boolean)(valuestree))) {
        valuestree->firstSetter(SYM_WALK_STELLA_PROGN);
        { ConsIterator* it = valuestree->rest->allocateIterator();
          Object* var = NULL;
          Cons* iter004 = variables;

          for  (; it->nextP() &&
                    (!(iter004 == NIL)); 
                iter004 = iter004->rest) {
            var = iter004->value;
            it->valueSetter(listO(3, SYM_WALK_STELLA_SETQ, var, cons(it->value, NIL)));
          }
        }
        valuestree = ((Cons*)(omvtree));
      }
      else {
        valuestree = listO(3, SYM_WALK_STELLA_MV_SETQ, variables, cons(omvtree, NIL));
      }
      return (walkAConsTree(listO(3, SYM_WALK_STELLA_LET, declarations, cons(valuestree, body->concatenate(NIL, 0))), _Return1));
    }
  }
}

Cons* walkLoopTree(Cons* tree, StandardObject*& _Return1) {
  { 
    BIND_STELLA_SPECIAL(oNOFSPECIALSATLOOPENTRYo, int, oSPECIALVARIABLESTACKo->length());
    tree->rest = walkListOfStatements(tree->rest);
    return (sysTree(tree, SGT_WALK_STELLA_VOID, _Return1));
  }
}

Cons* walkLoopExitTree(Cons* tree, StandardObject*& _Return1) {
  badArgumentCountP(tree, 0);
  if (needToUnbindSpecialsP()) {
    { Cons* unbindtree = yieldLoopExitSpecialUnbindTree();

      { 
        BIND_STELLA_SPECIAL(oSPECIALSENABLEDpo, boolean, false);
        return (walkAConsTree(listO(3, SYM_WALK_STELLA_PROGN, unbindtree, cons(tree, NIL)), _Return1));
      }
    }
  }
  else {
    _Return1 = SGT_WALK_STELLA_VOID;
    return (tree);
  }
}

Cons* walkWhileTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;

    { 
      BIND_STELLA_SPECIAL(oNOFSPECIALSATLOOPENTRYo, int, oSPECIALVARIABLESTACKo->length());
      { Object* test = walkExpressionTree(tree->rest->value, SGT_WALK_STELLA_BOOLEAN, SYM_WALK_STELLA_WHILE, true, dummy1);
        Cons* body = tree->rest->rest;

        tree->secondSetter(test);
        if (proceduralExpressionP(test)) {
          tree->rest->rest = NIL;
          return (walkAConsTree(listO(3, SYM_WALK_STELLA_LOOP, listO(3, SYM_WALK_STELLA_UNLESS, test, cons(cons(SYM_WALK_STELLA_BREAK, NIL), NIL)), body->concatenate(NIL, 0)), _Return1));
        }
        tree->rest->rest = walkListOfStatements(tree->rest->rest);
        _Return1 = SGT_WALK_STELLA_VOID;
        return (tree);
      }
    }
  }
}

Cons* walkConditionalTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;
    StandardObject* dummy2;

    { Object* operatoR = tree->value;
      Object* test = walkExpressionTree(tree->rest->value, SGT_WALK_STELLA_BOOLEAN, ((Symbol*)(operatoR)), true, dummy1);

      tree->secondSetter(test);
      if (proceduralExpressionP(test)) {
        { Cons* _Return0 = transformBooleanProceduralExpression(tree, ((Cons*)(test)), dummy2);

          _Return1 = SGT_WALK_STELLA_VOID;
          return (_Return0);
        }
      }
      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(operatoR));

        if (testValue000 == SYM_WALK_STELLA_IF) {
          if (badArgumentCountP(tree, 3)) {
            return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
          }
          tree->thirdSetter(walkStatement(tree->rest->rest->value, true));
          tree->fourthSetter(walkStatement(tree->fourth(), true));
        }
        else if ((testValue000 == SYM_WALK_STELLA_WHEN) ||
            (testValue000 == SYM_WALK_STELLA_UNLESS)) {
          tree->rest->rest = walkListOfStatements(tree->rest->rest);
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      _Return1 = SGT_WALK_STELLA_VOID;
      return (tree);
    }
  }
}

Cons* walkChooseTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;
    StandardObject* dummy2;
    StandardObject* dummy3;

    { Object* operatoR = tree->value;
      Object* test = walkExpressionTree(tree->rest->value, SGT_WALK_STELLA_BOOLEAN, ((Symbol*)(operatoR)), true, dummy1);
      Object* temp = NULL;
      StandardObject* type1 = NULL;
      StandardObject* type2 = NULL;
      StandardObject* type = NULL;

      tree->secondSetter(test);
      if (vrletExpressionP(test)) {
        return (percolateOutVrletExpression(tree, ((Cons*)(test)), SGT_WALK_STELLA_BOOLEAN, _Return1));
      }
      if (badArgumentCountP(tree, 3)) {
        return (walkDontCallMeTree(tree, SGT_WALK_STELLA_UNKNOWN, _Return1));
      }
      temp = walkExpressionTree(tree->rest->rest->value, oTARGETTYPEo, SYM_WALK_STELLA_CHOOSE, true, type1);
      tree->thirdSetter(temp);
      temp = walkExpressionTree(tree->fourth(), oTARGETTYPEo, SYM_WALK_STELLA_CHOOSE, true, type2);
      tree->fourthSetter(temp);
      if (type1 == SGT_WALK_STELLA_UNKNOWN) {
        type = type2;
        tree->thirdSetter(coerceATree(tree->rest->rest->value, type1, type, dummy2));
      }
      else if (type2 == SGT_WALK_STELLA_UNKNOWN) {
        type = type1;
        tree->fourthSetter(coerceATree(tree->fourth(), type2, type, dummy3));
      }
      else {
        type = twoArgumentLeastCommonSupertype(type1, type2);
      }
      if ((type == SGT_WALK_STELLA_VOID) ||
          ((!subTypeSpecOfP(type, SGT_WALK_STELLA_OBJECT)) &&
           typeSpecToClass(type)->abstractP)) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Incompatible subexpression types " << "`" << deUglifyParseTree(type1) << "'" << " and " << "`" << deUglifyParseTree(type2) << "'" << std::endl << " in 'choose' expression." << "." << std::endl;
          }
        }
      }
      if (vrletExpressionP(tree->rest->rest->value) ||
          vrletExpressionP(tree->fourth())) {
        { Symbol* resultvariable = localGensym("CHOOSE-VALUE");

          { Object* value000 = NULL;
            StandardObject* value001 = NULL;

            value000 = walkATree(listO(5, SYM_WALK_STELLA_VRLET, cons(cons(resultvariable, cons(type, cons(SYM_WALK_STELLA_NULL, NIL))), NIL), listO(3, SYM_WALK_STELLA_IF, tree->rest->value, listO(3, listO(3, SYM_WALK_STELLA_SETQ, resultvariable, cons(tree->rest->rest->value, NIL)), listO(3, SYM_WALK_STELLA_SETQ, resultvariable, cons(tree->fourth(), NIL)), NIL)), resultvariable, NIL), value001);
            _Return1 = value001;
            return (((Cons*)(value000)));
          }
        }
      }
      if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP) {
      }
      else {
        if ((!(type1 == type)) &&
            (!subTypeSpecOfP(type1, type2))) {
          tree->thirdSetter(listO(3, SYM_WALK_STELLA_CAST, tree->rest->rest->value, cons(type, NIL)));
        }
        if ((!(type2 == type)) &&
            (!subTypeSpecOfP(type2, type1))) {
          tree->fourthSetter(listO(3, SYM_WALK_STELLA_CAST, tree->fourth(), cons(type, NIL)));
        }
      }
      _Return1 = type;
      return (tree);
    }
  }
}

Object* walkBooleanTree(Cons* tree, StandardObject*& _Return1) {
  { Object* otree = helpWalkBooleanTree(tree);

    if (proceduralExpressionP(otree)) {
      otree = percolateOutBooleanVrletExpressions(((Cons*)(otree)));
    }
    _Return1 = SGT_WALK_STELLA_BOOLEAN;
    return (otree);
  }
}

boolean andOrNotTreeP(Object* tree) {
  if (consP(tree)) {
    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(((Cons*)(tree))->value));

      if ((testValue000 == SYM_WALK_STELLA_AND) ||
          ((testValue000 == SYM_WALK_STELLA_OR) ||
           (testValue000 == SYM_WALK_STELLA_NOT))) {
        return (true);
      }
      else {
        return (false);
      }
    }
  }
  else {
    return (false);
  }
}

Object* helpWalkBooleanTree(Cons* tree) {
  { StandardObject* dummy1;
    StandardObject* dummy2;

    { Cons* cursor = tree->rest;
      Object* temp = NULL;

      while (!(cursor == NIL)) {
        cursor->value = (andOrNotTreeP(cursor->value) ? helpWalkBooleanTree(((Cons*)(cursor->value))) : walkExpressionTree(cursor->value, SGT_WALK_STELLA_BOOLEAN, ((Symbol*)(tree->value)), true, dummy1));
        cursor = cursor->rest;
      }
      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

        if (testValue000 == SYM_WALK_STELLA_AND) {
          if (tree->rest == NIL) {
            return (TRUE_WRAPPER);
          }
          if (tree->rest->rest == NIL) {
            temp = tree->rest->value;
            return (temp);
          }
        }
        else if (testValue000 == SYM_WALK_STELLA_OR) {
          if (tree->rest == NIL) {
            return (FALSE_WRAPPER);
          }
          if (tree->rest->rest == NIL) {
            temp = tree->rest->value;
            return (temp);
          }
        }
        else if (testValue000 == SYM_WALK_STELLA_NOT) {
          if (badArgumentCountP(tree, 1)) {
            return (walkDontCallMeTree(tree, SGT_WALK_STELLA_BOOLEAN, dummy2));
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      return (tree);
    }
  }
}

Cons* walkCondTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;

    { Object* condition = NULL;
      Cons* iter000 = tree->rest;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        condition = iter000->value;
        if (safePrimaryType(condition) == SGT_WALK_STELLA_CONS) {
          { Object* condition000 = condition;
            Cons* condition = ((Cons*)(condition000));

            if (!(condition->value == SYM_WALK_STELLA_OTHERWISE)) {
              condition->value = walkExpressionTree(condition->value, SGT_WALK_STELLA_BOOLEAN, SYM_WALK_STELLA_COND, true, dummy1);
              if (proceduralExpressionP(condition->value)) {
                return (walkAConsTree(condTreeToIfTree(tree), _Return1));
              }
            }
            condition->rest = walkListOfStatements(condition->rest);
          }
        }
        else {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal condition in COND statement: " << "`" << deUglifyParseTree(condition) << "'" << "." << std::endl;
            }
          }
          return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
        }
      }
    }
    _Return1 = SGT_WALK_STELLA_VOID;
    return (tree);
  }
}

Cons* condTreeToIfTree(Cons* tree) {
  { StandardObject* dummy1;

    { Object* firstcondition = tree->rest->value;
      Cons* otherconditions = tree->rest->rest;
      Object* firsttest = NULL;

      if (safePrimaryType(firstcondition) == SGT_WALK_STELLA_CONS) {
        { Object* firstcondition000 = firstcondition;
          Cons* firstcondition = ((Cons*)(firstcondition000));

          firsttest = firstcondition->value;
          if (firsttest == SYM_WALK_STELLA_OTHERWISE) {
            if (otherconditions == NIL) {
              tree->firstSetter(SYM_WALK_STELLA_PROGN);
              tree->rest = firstcondition->rest;
              return (tree);
            }
            else {
              firstcondition->value = SYM_WALK_STELLA_TRUE;
              return (condTreeToIfTree(tree));
            }
          }
          else if (otherconditions == NIL) {
            tree->firstSetter(SYM_WALK_STELLA_WHEN);
            tree->rest = firstcondition;
            return (tree);
          }
          else {
            firstcondition->value = SYM_WALK_STELLA_PROGN;
            tree->secondSetter(SYM_WALK_STELLA_COND);
            return (listO(3, SYM_WALK_STELLA_IF, firsttest, cons(firstcondition, cons(condTreeToIfTree(tree->rest), NIL))));
          }
        }
      }
      else {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal condition in COND statement: " << "`" << deUglifyParseTree(firstcondition) << "'" << "." << std::endl;
          }
        }
        return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, dummy1));
      }
    }
  }
}

Object* yieldHardcodedCaseSymbolIdOrIds(Object* casetest) {
  if (casetest == SYM_WALK_STELLA_OTHERWISE) {
    return (casetest);
  }
  { Symbol* symbol = NULL;

    { Surrogate* testValue000 = safePrimaryType(casetest);

      if (testValue000 == SGT_WALK_STELLA_CONS) {
        { Object* casetest000 = casetest;
          Cons* casetest = ((Cons*)(casetest000));

          { ConsIterator* it = casetest->allocateIterator();

            for (; it->nextP(); ) {
              symbol = ((Symbol*)(it->value));
              if (!(symbol->symbolId != NULL_INTEGER)) {
                symbol = internPermanentSymbol(symbol->symbolName);
              }
              it->valueSetter(wrapInteger(symbol->symbolId));
              registerSymbol(symbol);
            }
          }
          return (casetest);
        }
      }
      else if (subtypeOfSymbolP(testValue000)) {
        { Object* casetest001 = casetest;
          Symbol* casetest = ((Symbol*)(casetest001));

          symbol = casetest;
          if (!(symbol->symbolId != NULL_INTEGER)) {
            symbol = internPermanentSymbol(symbol->symbolName);
          }
          registerSymbol(casetest);
          return (wrapInteger(symbol->symbolId));
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
}

Cons* walkHardcodedSymbolCaseTree(Cons* tree, StandardObject*& _Return1) {
  tree->secondSetter(listO(3, SYM_WALK_STELLA_SYMBOL_ID, listO(3, SYM_WALK_STELLA_CAST, tree->rest->value, cons(SYM_WALK_STELLA_GENERALIZED_SYMBOL, NIL)), NIL));
  { Cons* cond = NULL;
    Cons* iter000 = ((Cons*)(tree->rest->rest));

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      cond = ((Cons*)(iter000->value));
      cond->firstSetter(yieldHardcodedCaseSymbolIdOrIds(cond->value));
    }
  }
  return (walkCaseTree(tree, _Return1));
}

// Table of specialized type predicates for various types.
// These predicates have to be used instead of `isa?', since they also work
// during bootstrap when only some class objects are defined.
Cons* oTYPE_PREDICATE_TABLEo = NULL;

Cons* yieldIsaPCaseTest(Surrogate* casekey, Object* testexpression) {
  { Cons* entry = NULL;
    Cons* iter000 = oTYPE_PREDICATE_TABLEo;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      entry = ((Cons*)(iter000->value));
      if (entry->value == casekey) {
        return (cons(entry->rest->value, cons(copyConsTree(testexpression), NIL)));
      }
    }
  }
  return (listO(3, SYM_WALK_STELLA_ISAp, copyConsTree(testexpression), cons(casekey, NIL)));
}

Cons* yieldSubtypeOfPCaseTest(Surrogate* casekey, Object* testexpression) {
  { Cons* entry = NULL;
    Cons* iter000 = oTYPE_PREDICATE_TABLEo;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      entry = ((Cons*)(iter000->value));
      if (entry->value == casekey) {
        return (cons(entry->rest->rest->value, cons(copyConsTree(testexpression), NIL)));
      }
    }
  }
  return (listO(3, SYM_WALK_STELLA_SUBTYPE_OFp, copyConsTree(testexpression), cons(casekey, NIL)));
}

Cons* yieldCondTest(Object* casetest, Object* testvariable, Symbol* equalitytest) {
  if (symbolP(casetest) &&
      (!useHardcodedSymbolsP())) {
    casetest = listO(3, SYM_WALK_STELLA_TYPED_SYS, registerSymbol(((GeneralizedSymbol*)(casetest))), cons(SGT_WALK_STELLA_SYMBOL, NIL));
  }
  if (equalitytest == SYM_WALK_STELLA_ISAp) {
    return (yieldIsaPCaseTest(typify(casetest), testvariable));
  }
  else if (equalitytest == SYM_WALK_STELLA_SUBTYPE_OFp) {
    return (yieldSubtypeOfPCaseTest(typify(casetest), testvariable));
  }
  else {
    return (cons(equalitytest, cons(copyConsTree(testvariable), cons(casetest, NIL))));
  }
}

Object* yieldCondTestOrTests(Object* casetest, Object* testvariable, Symbol* equalitytest) {
  if (safePrimaryType(casetest) == SGT_WALK_STELLA_CONS) {
    { Object* casetest000 = casetest;
      Cons* casetest = ((Cons*)(casetest000));

      { ConsIterator* it = casetest->allocateIterator();

        for (; it->nextP(); ) {
          it->valueSetter(yieldCondTest(it->value, testvariable, equalitytest));
        }
      }
      casetest = cons(SYM_WALK_STELLA_OR, casetest);
      return (casetest);
    }
  }
  else {
    if (casetest == SYM_WALK_STELLA_OTHERWISE) {
      return (casetest);
    }
    else {
      return (yieldCondTest(casetest, testvariable, equalitytest));
    }
  }
}

int countCaseTestClauses(Cons* tree, boolean& _Return1) {
  { Cons* clauses = ((Cons*)(tree->rest->rest));
    int nofclauses = 0;
    boolean otherwiseP = false;

    { Cons* clause = NULL;
      Cons* iter000 = clauses;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        clause = ((Cons*)(iter000->value));
        if (safePrimaryType(clause->value) == SGT_WALK_STELLA_CONS) {
          nofclauses = nofclauses + ((Cons*)(clause->value))->length();
        }
        else {
          if (clause->value == SYM_WALK_STELLA_OTHERWISE) {
            otherwiseP = true;
          }
          else {
            nofclauses = nofclauses + 1;
          }
        }
      }
    }
    _Return1 = otherwiseP;
    return (nofclauses);
  }
}

Cons* attachUnhandledCaseErrorClause(Cons* casetree, Object* testtree) {
  { Object* lastclause = casetree->last();

    if (consP(lastclause) &&
        (!(((Cons*)(lastclause))->value == SYM_WALK_STELLA_OTHERWISE))) {
      return (casetree->concatenate(cons(listO(3, SYM_WALK_STELLA_OTHERWISE, listO(3, SYM_WALK_STELLA_ERROR, copyConsTree(testtree), cons(wrapString(" is not a valid case option"), NIL)), NIL), NIL), 0));
    }
    else {
      return (casetree);
    }
  }
}

Cons* walkNonBuiltInCaseTree(Cons* tree, Symbol* equalitytest, StandardObject*& _Return1) {
  { boolean dummy1;

    { Object* testexpression = tree->rest->value;
      Object* testvariable = ((atomicExpressionP(testexpression) ||
          (countCaseTestClauses(tree, dummy1) <= 1)) ? tree->rest->value : localGensym("TEST-VALUE"));
      Cons* conditions = tree->rest->rest;

      { Cons* cond = NULL;
        Cons* iter000 = ((Cons*)(conditions));

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          cond = ((Cons*)(iter000->value));
          cond->firstSetter(yieldCondTestOrTests(cond->value, testvariable, equalitytest));
        }
      }
      conditions = attachUnhandledCaseErrorClause(conditions, testvariable);
      return (walkAConsTree((eqlP(testexpression, testvariable) ? cons(SYM_WALK_STELLA_COND, conditions->concatenate(NIL, 0)) : listO(4, SYM_WALK_STELLA_LET, cons(cons(testvariable, cons(testexpression, NIL)), NIL), cons(SYM_WALK_STELLA_COND, conditions->concatenate(NIL, 0)), NIL)), _Return1));
    }
  }
}

Cons* walkCaseTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;
    StandardObject* dummy2;

    { boolean testValue000 = false;

      testValue000 = tree->length() >= 3;
      if (testValue000) {
        { boolean alwaysP000 = true;

          { Object* clause = NULL;
            Cons* iter000 = tree->rest->rest;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              clause = iter000->value;
              if (!consP(clause)) {
                alwaysP000 = false;
                break;
              }
            }
          }
          testValue000 = alwaysP000;
        }
      }
      testValue000 = !testValue000;
      if (testValue000) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal `case' statement: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
          }
        }
        return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
      }
    }
    { Cons* clauses = ((Cons*)(tree->rest->rest));
      Object* firsttesttree = (consP(((Cons*)(clauses->value))->value) ? ((Cons*)(((Cons*)(clauses->value))->value))->value : ((Cons*)(clauses->value))->value);
      Surrogate* caseconstanttype = SGT_WALK_STELLA_UNKNOWN;

      { Surrogate* testValue001 = safePrimaryType(firsttesttree);

        if (subtypeOfSymbolP(testValue001)) {
          { Object* firsttesttree000 = firsttesttree;
            Symbol* firsttesttree = ((Symbol*)(firsttesttree000));

            caseconstanttype = SGT_WALK_STELLA_GENERALIZED_SYMBOL;
          }
        }
        else if (subtypeOfSurrogateP(testValue001)) {
          { Object* firsttesttree001 = firsttesttree;
            Surrogate* firsttesttree = ((Surrogate*)(firsttesttree001));

            caseconstanttype = SGT_WALK_STELLA_GENERALIZED_SYMBOL;
          }
        }
        else if (subtypeOfKeywordP(testValue001)) {
          { Object* firsttesttree002 = firsttesttree;
            Keyword* firsttesttree = ((Keyword*)(firsttesttree002));

            caseconstanttype = SGT_WALK_STELLA_GENERALIZED_SYMBOL;
          }
        }
        else if (subtypeOfStringP(testValue001)) {
          { Object* firsttesttree003 = firsttesttree;
            StringWrapper* firsttesttree = ((StringWrapper*)(firsttesttree003));

            caseconstanttype = SGT_WALK_STELLA_STRING;
          }
        }
        else if (subtypeOfCharacterP(testValue001)) {
          { Object* firsttesttree004 = firsttesttree;
            CharacterWrapper* firsttesttree = ((CharacterWrapper*)(firsttesttree004));

            caseconstanttype = SGT_WALK_STELLA_CHARACTER;
          }
        }
        else if (subtypeOfIntegerP(testValue001)) {
          { Object* firsttesttree005 = firsttesttree;
            IntegerWrapper* firsttesttree = ((IntegerWrapper*)(firsttesttree005));

            caseconstanttype = SGT_WALK_STELLA_INTEGER;
          }
        }
        else if (subtypeOfLongIntegerP(testValue001)) {
          { Object* firsttesttree006 = firsttesttree;
            LongIntegerWrapper* firsttesttree = ((LongIntegerWrapper*)(firsttesttree006));

            caseconstanttype = SGT_WALK_STELLA_LONG_INTEGER;
          }
        }
        else if (subtypeOfFloatP(testValue001)) {
          { Object* firsttesttree007 = firsttesttree;
            FloatWrapper* firsttesttree = ((FloatWrapper*)(firsttesttree007));

            caseconstanttype = SGT_WALK_STELLA_FLOAT;
          }
        }
        else {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "`case' statement contains illegal constant of type " << "`" << firsttesttree->primaryType() << "'" << std::endl << "    " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
            }
          }
          return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
        }
      }
      tree->secondSetter(walkExpressionTree(tree->rest->value, caseconstanttype, SYM_WALK_STELLA_CASE, true, dummy1));
      if (vrletExpressionP(tree->rest->value)) {
        return (percolateOutVrletExpression(tree, ((Cons*)(tree->rest->value)), caseconstanttype, _Return1));
      }
      if ((caseconstanttype == SGT_WALK_STELLA_GENERALIZED_SYMBOL) &&
          useHardcodedSymbolsP()) {
        return (walkHardcodedSymbolCaseTree(tree, _Return1));
      }
      if (!((caseconstanttype == SGT_WALK_STELLA_INTEGER) ||
          ((caseconstanttype == SGT_WALK_STELLA_LONG_INTEGER) ||
           (caseconstanttype == SGT_WALK_STELLA_CHARACTER)))) {
        return (walkNonBuiltInCaseTree(tree, ((caseconstanttype == SGT_WALK_STELLA_STRING) ? SYM_WALK_STELLA_STRING_EQLp : SYM_WALK_STELLA_EQLp), _Return1));
      }
      if (!(oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP)) {
        tree = attachUnhandledCaseErrorClause(tree, tree->rest->value);
      }
      { Cons* cursor = tree->rest->rest;
        Cons* conditiontree = NULL;

        while (!(cursor == NIL)) {
          conditiontree = ((Cons*)(cursor->value));
          if (!(conditiontree->value == SYM_WALK_STELLA_OTHERWISE)) {
            conditiontree->firstSetter((consP(conditiontree->value) ? walkListOfTrees(((Cons*)(conditiontree->value))) : walkATree(conditiontree->value, dummy2)));
          }
          conditiontree->rest = walkListOfStatements(conditiontree->rest);
          cursor = cursor->rest;
        }
        _Return1 = SGT_WALK_STELLA_VOID;
        return (tree);
      }
    }
  }
}

Cons* walkTypecaseTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;

    { Object* testtree = tree->rest->value;
      StandardObject* testexpressiontype = NULL;
      Symbol* testvariable = NULL;
      Cons* expandedcases = NIL;
      boolean needcastP = symbolP(testtree) &&
          (!((boolean)(((Symbol*)(testtree))->lookupGlobalVariable())));
      List* precedingclausetypes = newList();

      if (needcastP) {
        testvariable = ((Symbol*)(testtree));
      }
      testtree = walkATree(testtree, testexpressiontype);
      tree->secondSetter(testtree);
      testexpressiontype = typeSpecToBaseType(testexpressiontype);
      if (unknownTypeP(((Surrogate*)(testexpressiontype)))) {
        testexpressiontype = SGT_WALK_STELLA_UNKNOWN;
      }
      tree->secondSetter(sysTree(testtree, testexpressiontype, dummy1));
      if (needcastP) {
        { Object* casetree = NULL;
          Cons* iter000 = tree->rest->rest;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            casetree = iter000->value;
            if (safePrimaryType(casetree) == SGT_WALK_STELLA_CONS) {
              { Object* casetree000 = casetree;
                Cons* casetree = ((Cons*)(casetree000));

                { Object* typetree = casetree->value;

                  if (safePrimaryType(typetree) == SGT_WALK_STELLA_CONS) {
                    { Object* typetree000 = typetree;
                      Cons* typetree = ((Cons*)(typetree000));

                      casetree->firstSetter(typetree->value);
                      expandedcases = cons(casetree, expandedcases);
                      { Object* type = NULL;
                        Cons* iter001 = typetree->rest;

                        for (; !(iter001 == NIL); iter001 = iter001->rest) {
                          type = iter001->value;
                          expandedcases = cons(cons(type, ((Cons*)(((Cons*)(copyConsTree(casetree->rest)))))->concatenate(NIL, 0)), expandedcases);
                        }
                      }
                    }
                  }
                  else {
                    expandedcases = cons(casetree, expandedcases);
                  }
                }
              }
            }
            else {
              expandedcases = cons(casetree, expandedcases);
            }
          }
        }
        tree->rest->rest = expandedcases->reverse();
      }
      { Object* casetree = NULL;
        Cons* iter002 = tree->rest->rest;

        for (; !(iter002 == NIL); iter002 = iter002->rest) {
          casetree = iter002->value;
          if (safePrimaryType(casetree) == SGT_WALK_STELLA_CONS) {
            { Object* casetree001 = casetree;
              Cons* casetree = ((Cons*)(casetree001));

              { Object* typetree = casetree->value;

                { Surrogate* testValue000 = safePrimaryType(typetree);

                  if (subtypeOfSymbolP(testValue000)) {
                    { Object* typetree001 = typetree;
                      Symbol* typetree = ((Symbol*)(typetree001));

                      if (!(stringEqlP(typetree->symbolName, "OTHERWISE"))) {
                        { Surrogate* type = typeSpecToBaseType(typetree->yieldTypeSpecifier());

                          verifyTypecaseClauseType(((Surrogate*)(testexpressiontype)), type, precedingclausetypes, casetree);
                          casetree->firstSetter(type);
                          type = type->typeToWrappedType();
                          if (needcastP &&
                              (!(casetree->rest == NIL))) {
                            casetree->rest = yieldCastedTypecaseClauseTrees(testvariable, type, casetree->rest);
                          }
                        }
                      }
                    }
                  }
                  else if (subtypeOfSurrogateP(testValue000)) {
                    { Object* typetree002 = typetree;
                      Surrogate* typetree = ((Surrogate*)(typetree002));

                      if (!(stringEqlP(typetree->symbolName, "OTHERWISE"))) {
                        { Surrogate* type = typeSpecToBaseType(typetree->yieldTypeSpecifier());

                          verifyTypecaseClauseType(((Surrogate*)(testexpressiontype)), type, precedingclausetypes, casetree);
                          casetree->firstSetter(type);
                          type = type->typeToWrappedType();
                          if (needcastP &&
                              (!(casetree->rest == NIL))) {
                            casetree->rest = yieldCastedTypecaseClauseTrees(testvariable, type, casetree->rest);
                          }
                        }
                      }
                    }
                  }
                  else if (testValue000 == SGT_WALK_STELLA_CONS) {
                    { Object* typetree003 = typetree;
                      Cons* typetree = ((Cons*)(typetree003));

                      { ConsIterator* it = typetree->allocateIterator();

                        for (; it->nextP(); ) {
                          if (consP(it->value)) {
                            { 
                              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                              signalTranslationError();
                              if (!(suppressWarningsP())) {
                                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal type expression in 'typecase': " << "`" << deUglifyParseTree(typetree) << "'" << "." << std::endl;
                              }
                            }
                            return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
                          }
                          it->valueSetter(typeSpecToBaseType(it->value->yieldTypeSpecifier()));
                          verifyTypecaseClauseType(((Surrogate*)(testexpressiontype)), ((Surrogate*)(it->value)), precedingclausetypes, casetree);
                        }
                      }
                    }
                  }
                  else {
                    { 
                      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                      signalTranslationError();
                      if (!(suppressWarningsP())) {
                        printErrorContext(">> ERROR: ", STANDARD_ERROR);
                        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal type expression in 'typecase': " << "`" << deUglifyParseTree(typetree) << "'" << "." << std::endl;
                      }
                    }
                    return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
                  }
                }
              }
            }
          }
          else {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal case expression in 'typecase': " << "`" << deUglifyParseTree(casetree) << "'" << "." << std::endl;
              }
            }
            return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
          }
        }
      }
      return (walkNonBuiltInCaseTree(listO(3, SYM_WALK_STELLA_CASE, listO(3, SYM_WALK_STELLA_SAFE_PRIMARY_TYPE, tree->rest->value, NIL), tree->rest->rest->concatenate(NIL, 0)), SYM_WALK_STELLA_SUBTYPE_OFp, _Return1));
    }
  }
}

Cons* yieldCastedTypecaseClauseTrees(Symbol* testvariable, StandardObject* clausetype, Cons* clausetrees) {
  { StandardObject* dummy1;

    { StandardObject* testvariabletype = lookupVariableType(testvariable);
      boolean needrealcastP = !(oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP);
      Symbol* auxvariable = (((!(oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA)) &&
          needrealcastP) ? localGensym(testvariable->symbolName) : ((Symbol*)(NULL)));
      Cons* castedclausetrees = NULL;

      if (!needrealcastP) {
        pushVariableBinding(testvariable, clausetype);
        castedclausetrees = cons(listO(3, SYM_WALK_STELLA_VOID_SYS, cons(SYM_WALK_STELLA_PROGN, walkListOfStatements(clausetrees)->concatenate(NIL, 0)), NIL), NIL);
        popVariableBinding();
      }
      else {
        if (((boolean)(auxvariable))) {
          pushVariableBinding(auxvariable, testvariabletype);
        }
        castedclausetrees = cons(listO(3, SYM_WALK_STELLA_LET, (((boolean)(auxvariable)) ? listO(3, cons(auxvariable, cons(testvariable, NIL)), cons(testvariable, cons(clausetype, cons(auxvariable, NIL))), NIL) : cons(cons(testvariable, cons(listO(3, SYM_WALK_STELLA_SAFE_CAST, sysTree(walkWithoutTypeTree(testvariable), clausetype, dummy1), cons(clausetype, NIL)), NIL)), NIL)), clausetrees->concatenate(NIL, 0)), NIL);
        if (((boolean)(auxvariable))) {
          popVariableBinding();
        }
      }
      return (castedclausetrees);
    }
  }
}

void verifyTypecaseClauseType(Surrogate* testtype, Surrogate* clausetype, List* precedingclausetypes, Cons* clause) {
  { Surrogate* shadowingtype = NULL;
    Surrogate* wrappedclausetype = clausetype->typeToWrappedType();

    if (((boolean)(wrappedclausetype))) {
      clausetype = wrappedclausetype;
    }
    if (unknownTypeP(clausetype)) {
      {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Reference to undefined or unwrappable non-object type in `typecase': " << "`" << deUglifyParseTree(clausetype) << "'" << "." << std::endl;
          }
        }
      }
    }
    else {
      if ((!(testtype == SGT_WALK_STELLA_UNKNOWN)) &&
          (!subTypeSpecOfP(clausetype, testtype))) {
        {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationWarning();
            if (!(suppressWarningsP())) {
              printErrorContext(">> WARNING: ", STANDARD_WARNING);
              *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Type " << "`" << deUglifyParseTree(clausetype) << "'" << " of `typecase' clause " << std::endl << "    " << "`" << deUglifyParseTree(clause) << "'" << std::endl << " is not a subtype of the test expression type " << "`" << deUglifyParseTree(testtype) << "'" << "." << std::endl;
            }
          }
        }
      }
      else {
        { 
          { Surrogate* value000 = NULL;

            { Surrogate* type = NULL;
              Cons* iter000 = precedingclausetypes->theConsList;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                type = ((Surrogate*)(iter000->value));
                if (subtypeOfP(clausetype, type)) {
                  value000 = type;
                  break;
                }
              }
            }
            shadowingtype = value000;
          }
          if (((boolean)(shadowingtype))) {
            {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationWarning();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> WARNING: ", STANDARD_WARNING);
                  *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Type " << "`" << deUglifyParseTree(clausetype) << "'" << " of `typecase' clause " << std::endl << "    " << "`" << deUglifyParseTree(clause) << "'" << std::endl << " is shadowed by type " << "`" << deUglifyParseTree(shadowingtype) << "'" << "." << std::endl;
                }
              }
            }
          }
          else {
            {
              precedingclausetypes->push(clausetype);
            }
          }
        }
      }
    }
  }
}

Cons* walkWithProcessLockTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;

    tree->secondSetter(walkExpressionTree(tree->rest->value, SGT_WALK_STELLA_PROCESS_LOCK_OBJECT, ((Symbol*)(tree->value)), true, dummy1));
    tree->rest->rest = walkListOfStatements(tree->rest->rest);
    return (sysTree(tree, SGT_WALK_STELLA_VOID, _Return1));
  }
}

Cons* finishWalkingEqlTree(Cons* tree, Surrogate* type1, Surrogate* type2, StandardObject*& _Return1) {
  { StandardObject* dummy1;
    StandardObject* dummy2;

    if (subtypeOfP(type1, SGT_WALK_STELLA_STANDARD_OBJECT) ||
        (subtypeOfP(type2, SGT_WALK_STELLA_STANDARD_OBJECT) ||
         (((type1 == SGT_WALK_STELLA_BOOLEAN_WRAPPER) &&
        (type2 == SGT_WALK_STELLA_BOOLEAN_WRAPPER)) ||
          (((!subtypeOfP(type1, SGT_WALK_STELLA_OBJECT)) &&
        (!subtypeOfP(type1, SGT_WALK_STELLA_LITERAL))) ||
           ((!subtypeOfP(type2, SGT_WALK_STELLA_OBJECT)) &&
            (!subtypeOfP(type2, SGT_WALK_STELLA_LITERAL))))))) {
      tree->firstSetter(SYM_WALK_STELLA_EQp);
      tree->secondSetter(sysTree(tree->rest->value, type1, dummy1));
      tree->thirdSetter(sysTree(tree->rest->rest->value, type2, dummy2));
      _Return1 = SGT_WALK_STELLA_BOOLEAN;
      return (tree);
    }
    if (subtypeOfP(type1, SGT_WALK_STELLA_LITERAL) &&
        subtypeOfP(type2, SGT_WALK_STELLA_LITERAL)) {
      if (type1 == SGT_WALK_STELLA_STRING) {
        tree->firstSetter(SYM_WALK_STELLA_STRING_EQLp);
      }
      else {
        tree->firstSetter(SYM_WALK_STELLA_EQp);
      }
      return (walkAConsTree(tree, _Return1));
    }
    if ((!subtypeOfP(type1, SGT_WALK_STELLA_LITERAL)) &&
        (!subtypeOfP(type2, SGT_WALK_STELLA_LITERAL))) {
      { Object* otree = NULL;
        StandardObject* otype = NULL;

        otree = walkCallSlotTree(tree, otype);
        _Return1 = otype;
        return (((Cons*)(otree)));
      }
    }
    if (!subtypeOfP(type2, SGT_WALK_STELLA_LITERAL)) {
      { Object* temparg = tree->rest->rest->value;
        Surrogate* temptype = type2;

        tree->thirdSetter(tree->rest->value);
        tree->secondSetter(temparg);
        type2 = type1;
        type1 = temptype;
      }
    }
    if (type2 == SGT_WALK_STELLA_BOOLEAN) {
      tree->firstSetter(SYM_WALK_STELLA_EQL_TO_BOOLEANp);
    }
    else if (type2 == SGT_WALK_STELLA_INTEGER) {
      tree->firstSetter(SYM_WALK_STELLA_EQL_TO_INTEGERp);
    }
    else if (type2 == SGT_WALK_STELLA_LONG_INTEGER) {
      tree->firstSetter(SYM_WALK_STELLA_EQL_TO_LONG_INTEGERp);
    }
    else if (type2 == SGT_WALK_STELLA_FLOAT) {
      tree->firstSetter(SYM_WALK_STELLA_EQL_TO_FLOATp);
    }
    else if (type2 == SGT_WALK_STELLA_STRING) {
      tree->firstSetter(SYM_WALK_STELLA_EQL_TO_STRINGp);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << type2 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    { Cons* _Return0 = ((Cons*)(walkWithoutTypeTree(tree)));

      _Return1 = SGT_WALK_STELLA_BOOLEAN;
      return (_Return0);
    }
  }
}

Cons* finishWalkingEqualTree(Cons* tree, Surrogate* type1, Surrogate* type2, StandardObject*& _Return1) {
  {
    tree = tree;
    type1 = type1;
    type2 = type2;
  }
  { 
    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
    signalTranslationError();
    if (!(suppressWarningsP())) {
      printErrorContext(">> ERROR: ", STANDARD_ERROR);
      *(STANDARD_ERROR->nativeStream) << std::endl << " " << "finish-walking-equal-tree: NOT YET IMPLEMENTED." << "." << std::endl;
    }
  }
  _Return1 = SGT_WALK_STELLA_BOOLEAN;
  return (NULL);
}

Object* walkEqualityTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;
    StandardObject* dummy2;
    StandardObject* dummy3;
    StandardObject* dummy4;

    { Object* arg1 = NULL;
      Object* arg2 = NULL;
      StandardObject* type1 = NULL;
      StandardObject* type2 = NULL;

      arg1 = walkExpressionTree(tree->rest->value, SGT_WALK_STELLA_UNKNOWN, ((Symbol*)(tree->value)), true, type1);
      arg2 = walkExpressionTree(tree->rest->rest->value, SGT_WALK_STELLA_UNKNOWN, ((Symbol*)(tree->value)), true, type2);
      tree->secondSetter(arg1);
      tree->thirdSetter(arg2);
      if (vrletExpressionP(arg1)) {
        return (walkATree(percolateOutVrletExpression(tree, ((Cons*)(arg1)), SGT_WALK_STELLA_BOOLEAN, dummy1), _Return1));
      }
      if (vrletExpressionP(arg2)) {
        return (walkATree(percolateOutVrletExpression(tree, ((Cons*)(arg2)), SGT_WALK_STELLA_BOOLEAN, dummy2), _Return1));
      }
      type1 = canonicalType(typeSpecToBaseType(type1));
      type2 = canonicalType(typeSpecToBaseType(type2));
      if (!((type1 == SGT_WALK_STELLA_UNKNOWN) ||
          ((type2 == SGT_WALK_STELLA_UNKNOWN) ||
           (subtypeOfP(((Surrogate*)(type1)), ((Surrogate*)(type2))) ||
            (subtypeOfP(((Surrogate*)(type2)), ((Surrogate*)(type1))) ||
             ((subtypeOfP(((Surrogate*)(type1)), SGT_WALK_STELLA_NUMBER) &&
          subtypeOfP(((Surrogate*)(type2)), SGT_WALK_STELLA_NUMBER)) ||
              (subtypeOfP(((Surrogate*)(type1))->typeToWrappedType(), ((Surrogate*)(type2))) ||
               subtypeOfP(((Surrogate*)(type2))->typeToWrappedType(), ((Surrogate*)(type1)))))))))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationWarning();
          if (!(suppressWarningsP())) {
            printErrorContext(">> WARNING: ", STANDARD_WARNING);
            *(STANDARD_WARNING->nativeStream) << std::endl << " " << "This equality test will always fail due to disjoint " << "argument types:" << std::endl << "    " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
          }
        }
      }
      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

        if ((testValue000 == SYM_WALK_STELLA_EQp) ||
            (testValue000 == SYM_WALK_STELLA_e)) {
          tree->firstSetter(SYM_WALK_STELLA_EQp);
          tree->secondSetter(sysTree(tree->rest->value, type1, dummy3));
          tree->thirdSetter(sysTree(tree->rest->rest->value, type2, dummy4));
          _Return1 = SGT_WALK_STELLA_BOOLEAN;
          return (tree);
        }
        else if (testValue000 == SYM_WALK_STELLA_EQLp) {
          return (finishWalkingEqlTree(tree, ((Surrogate*)(type1)), ((Surrogate*)(type2)), _Return1));
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
  }
}

List* oNUMERIC_TYPE_HIERARCHYo = NULL;

Surrogate* moreGeneralNumericType(Surrogate* type1, Surrogate* type2) {
  { int position1 = oNUMERIC_TYPE_HIERARCHYo->position(type1, 0);
    int position2 = oNUMERIC_TYPE_HIERARCHYo->position(type2, 0);

    if ((position1 == NULL_INTEGER) ||
        (position2 == NULL_INTEGER)) {
      return (SGT_WALK_STELLA_NUMBER);
    }
    if (position1 > position2) {
      return (type1);
    }
    else {
      return (type2);
    }
  }
}

Cons* yieldArithmeticOperatorCallTree(Symbol* operatoR, Cons* operands) {
  return (listO(4, SYM_WALK_STELLA_SYS_CALL_METHOD, SGT_WALK_STELLA_NUMBER, operatoR, operands->concatenate(NIL, 0)));
}

Cons* yieldNestedArithmeticOperatorCallTree(Symbol* operatoR, Cons* operands) {
  { int nofoperands = operands->length();
    Cons* parenthesizedtree = yieldArithmeticOperatorCallTree(operatoR, consList(2, operands->value, operands->rest->value));

    { int i = NULL_INTEGER;
      int iter000 = 2;
      int upperBound000 = nofoperands - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        parenthesizedtree = yieldArithmeticOperatorCallTree(operatoR, consList(2, parenthesizedtree, operands->nth(i)));
      }
    }
    return (parenthesizedtree);
  }
}

Object* walkArithmeticTree(Cons* tree, Surrogate*& _Return1) {
  { Object* operatoR = tree->value;
    Cons* operands = tree->rest;
    int nofoperands = operands->length();
    Object* operand = NULL;
    StandardObject* operandtype = NULL;
    Surrogate* returntype = SGT_WALK_STELLA_INTEGER;

    switch (nofoperands) {
      case 0: 
        { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(operatoR));

          if (testValue000 == SYM_WALK_STELLA_i) {
            { Object* _Return0 = wrapInteger(0);

              _Return1 = SGT_WALK_STELLA_INTEGER;
              return (_Return0);
            }
          }
          else if (testValue000 == SYM_WALK_STELLA_o) {
            { Object* _Return0 = wrapInteger(1);

              _Return1 = SGT_WALK_STELLA_INTEGER;
              return (_Return0);
            }
          }
          else {
            badArgumentCountP(tree, 1);
            { Cons* value000 = NULL;
              StandardObject* value001 = NULL;

              value000 = walkDontCallMeTree(tree, SGT_WALK_STELLA_NUMBER, value001);
              _Return1 = ((Surrogate*)(value001));
              return (value000);
            }
          }
        }
        break;
      case 1: 
        { GeneralizedSymbol* testValue001 = ((GeneralizedSymbol*)(operatoR));

          if ((testValue001 == SYM_WALK_STELLA_i) ||
              (testValue001 == SYM_WALK_STELLA_o)) {
            { Object* value002 = NULL;
              StandardObject* value003 = NULL;

              value002 = walkExpressionTree(operands->value, SGT_WALK_STELLA_NUMBER, ((Symbol*)(operatoR)), false, value003);
              _Return1 = ((Surrogate*)(value003));
              return (value002);
            }
          }
          else if ((testValue001 == SYM_WALK_STELLA__) ||
              (testValue001 == SYM_WALK_STELLA_s)) {
            operands->rest = cons(operands->value, NIL);
            operands->firstSetter(((operatoR == SYM_WALK_STELLA__) ? wrapInteger(0) : wrapInteger(1)));
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
        break;
      default:
        break;
    }
    { ConsIterator* it = operands->allocateIterator();

      for (; it->nextP(); ) {
        operand = walkExpressionTree(it->value, SGT_WALK_STELLA_NUMBER, ((Symbol*)(operatoR)), false, operandtype);
        returntype = moreGeneralNumericType(returntype, typeSpecToBaseType(operandtype));
        it->valueSetter(operand);
      }
    }
    if ((operatoR == SYM_WALK_STELLA_s) &&
        ((returntype == SGT_WALK_STELLA_INTEGER) ||
         (returntype == SGT_WALK_STELLA_LONG_INTEGER))) {
      if (wrapperP(operands->value)) {
        operands->firstSetter(wrapFloat(coerceToFloat(operands->value)));
      }
      else if (wrapperP(operands->rest->value)) {
        operands->secondSetter(wrapFloat(coerceToFloat(operands->rest->value)));
      }
      else {
        operands = cons(listO(3, SYM_WALK_STELLA_CAST, operands->value, cons(SGT_WALK_STELLA_FLOAT, NIL)), operands->rest->concatenate(NIL, 0));
        nofoperands = nofoperands + 1;
      }
      returntype = SGT_WALK_STELLA_FLOAT;
    }
    if ((nofoperands > 2) &&
        (!(oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP))) {
      { Cons* value004 = NULL;
        StandardObject* value005 = NULL;

        value004 = sysTree(yieldNestedArithmeticOperatorCallTree(((Symbol*)(operatoR)), operands), returntype, value005);
        _Return1 = ((Surrogate*)(value005));
        return (value004);
      }
    }
    else {
      { Cons* value006 = NULL;
        StandardObject* value007 = NULL;

        value006 = sysTree(yieldArithmeticOperatorCallTree(((Symbol*)(operatoR)), operands), returntype, value007);
        _Return1 = ((Surrogate*)(value007));
        return (value006);
      }
    }
  }
}

Object* walkQuotedTree(Cons* tree, StandardObject*& _Return1) {
  if (badArgumentCountP(tree, 1)) {
    return (walkDontCallMeTree(tree, SGT_WALK_STELLA_UNKNOWN, _Return1));
  }
  { Object* argument = tree->rest->value;
    boolean quotedliteralP = (!consP(argument)) ||
        (argument == NIL);
    const char* objectname = NULL;

    if (quotedliteralP) {
      { Object* otree = NULL;
        StandardObject* otype = NULL;

        otree = walkATree(bquotify(argument), otype);
        _Return1 = otype;
        return (otree);
      }
    }
    objectname = nameQuotedTree(((Cons*)(argument)));
    return (walkATree(listO(3, SYM_WALK_STELLA_GET_QUOTED_TREE, wrapString(objectname), cons(wrapString(oMODULEo->moduleFullName), NIL)), _Return1));
  }
}

Object* walkBquoteTree(Cons* tree, StandardObject*& _Return1) {
  if (badArgumentCountP(tree, 1)) {
    return (walkDontCallMeTree(tree, SGT_WALK_STELLA_UNKNOWN, _Return1));
  }
  { Object* otree = NULL;
    StandardObject* otype = NULL;

    otree = walkATree(simplifyBquoteTree(expandBquoteTree(tree->rest->value)), otype);
    _Return1 = otype;
    return (otree);
  }
}

Object* expandMacro(Cons* tree) {
  { StandardObject* dummy1;
    StandardObject* dummy2;

    { Symbol* macroname = ((Symbol*)(tree->value));
      MethodSlot* expanderobject = lookupMacro(macroname);
      cpp_function_code expandercode = expanderobject->functionCode;
      Cons* args = tree->rest;
      Object* expansion = NULL;

      if (expandercode == NULL) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Macro expander code for " << "`" << deUglifyParseTree(macroname) << "'" << " is not available" << "." << std::endl;
          }
        }
        return (walkDontCallMeTree(tree, SGT_WALK_STELLA_UNKNOWN, dummy1));
      }
      if (((BooleanWrapper*)(dynamicSlotValue(expanderobject->dynamicSlots, SYM_WALK_STELLA_METHOD_BODY_ARGUMENTp, FALSE_WRAPPER)))->wrapperValue) {
        switch (expanderobject->methodArgumentCount()) {
          case 1: 
            expansion = ((Object*  (*) (Cons*))expandercode)(args);
            tree->rest = NIL;
            break;
          case 2: 
            expansion = ((Object*  (*) (Object*, Cons*))expandercode)(args->value, args->rest);
            args->rest = NIL;
            break;
          case 3: 
            expansion = ((Object*  (*) (Object*, Object*, Cons*))expandercode)(args->value, args->rest->value, args->rest->rest);
            args->rest->rest = NIL;
            break;
          case 4: 
            expansion = ((Object*  (*) (Object*, Object*, Object*, Cons*))expandercode)(args->value, args->rest->value, args->rest->rest->value, args->nthRest(3));
            args->nthRestSetter(NIL, 3);
            break;
          case 5: 
            expansion = ((Object*  (*) (Object*, Object*, Object*, Object*, Cons*))expandercode)(args->value, args->rest->value, args->rest->rest->value, args->fourth(), args->nthRest(4));
            args->nthRestSetter(NIL, 4);
            break;
          default:
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Too many arguments in definition of macro " << "`" << deUglifyParseTree(macroname) << "'" << "." << std::endl;
              }
            }
            return (walkDontCallMeTree(tree, SGT_WALK_STELLA_UNKNOWN, dummy2));
        }
      }
      else {
        expansion = apply(expandercode, tree->rest);
      }
      return (expansion);
    }
  }
}

Object* walkMacroTree(Cons* tree, StandardObject*& _Return1) {
  return (walkATree(expandMacro(tree), _Return1));
}

Cons* walkPrintStreamTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;

    if (tree->length() <= 2) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing arguments in print statement: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
        }
      }
      return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
    }
    { Object* operatoR = tree->value;
      Object* streamtree = tree->rest->value;
      Object* otree = NULL;
      StandardObject* otype = NULL;

      if (keywordP(streamtree)) {
        if (!((streamtree == KWD_WALK_WARN) ||
            ((streamtree == KWD_WALK_ERROR) ||
             (streamtree == KWD_WALK_CONTINUABLE_ERROR)))) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal stream argument in print statement: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
            }
          }
          return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
        }
      }
      else {
        otree = walkExpressionTree(streamtree, SGT_WALK_STELLA_NATIVE_OUTPUT_STREAM, ((Symbol*)(tree->value)), false, otype);
        tree->firstSetter(SYM_WALK_STELLA_PRINT_NATIVE_STREAM);
        tree->secondSetter(otree);
      }
      { ConsIterator* it = tree->rest->rest->allocateIterator();

        for (; it->nextP(); ) {
          otree = walkExpressionTree(it->value, SGT_WALK_STELLA_UNKNOWN, ((Symbol*)(operatoR)), false, otype);
          it->valueSetter(otree);
          if (!(otree == SYM_WALK_STELLA_EOL)) {
            { Surrogate* testValue000 = safePrimaryType(otree);

              if (subtypeOfStringP(testValue000)) {
                { Object* otree000 = otree;
                  StringWrapper* otree = ((StringWrapper*)(otree000));

                }
              }
              else if (subtypeOfIntegerP(testValue000)) {
                { Object* otree001 = otree;
                  IntegerWrapper* otree = ((IntegerWrapper*)(otree001));

                  it->valueSetter(wrapString(stringify(otree)));
                }
              }
              else if (subtypeOfLongIntegerP(testValue000)) {
                { Object* otree002 = otree;
                  LongIntegerWrapper* otree = ((LongIntegerWrapper*)(otree002));

                  it->valueSetter(wrapString(stringify(otree)));
                }
              }
              else if (subtypeOfFloatP(testValue000)) {
                { Object* otree003 = otree;
                  FloatWrapper* otree = ((FloatWrapper*)(otree003));

                  it->valueSetter(wrapString(stringify(otree)));
                }
              }
              else if (subtypeOfCharacterP(testValue000)) {
                { Object* otree004 = otree;
                  CharacterWrapper* otree = ((CharacterWrapper*)(otree004));

                  it->valueSetter(wrapString(makeString(1, otree->wrapperValue)));
                }
              }
              else {
                it->valueSetter(sysTree(otree, otype, dummy1));
              }
            }
          }
        }
      }
      _Return1 = SGT_WALK_STELLA_VOID;
      return (tree);
    }
  }
}

boolean warnAboutUndefinedMethodsP() {
  return (oCURRENT_STELLA_FEATURESo->memberP(KWD_WALK_WARN_ABOUT_UNDEFINED_METHODS));
}

boolean warnAboutMissingMethodsP() {
  return ((!(oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP)) ||
      oCURRENT_STELLA_FEATURESo->memberP(KWD_WALK_WARN_ABOUT_MISSING_METHODS));
}

boolean walkTypeSpecIsNativeTypeP(StandardObject* thetype) {
  if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP) {
    return (((StringWrapper*)(dynamicSlotValue(typeSpecToClass(thetype)->dynamicSlots, SYM_WALK_STELLA_CLASS_CL_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue != NULL);
  }
  else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP) {
    return (((StringWrapper*)(dynamicSlotValue(typeSpecToClass(thetype)->dynamicSlots, SYM_WALK_STELLA_CLASS_CPP_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue != NULL);
  }
  else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA) {
    return (((StringWrapper*)(dynamicSlotValue(typeSpecToClass(thetype)->dynamicSlots, SYM_WALK_STELLA_CLASS_JAVA_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue != NULL);
  }
  else {
    return (false);
  }
}

Cons* walkUndefinedSlotTree(Cons* tree, StandardObject* firstargtype, boolean warnP, Surrogate*& _Return1) {
  { StandardObject* dummy1;

    { Cons* cursor = tree->rest->rest;
      Surrogate* type = typeSpecToBaseType(firstargtype);
      Symbol* operatorname = ((Symbol*)(tree->value));

      while (!(cursor == NIL)) {
        cursor->value = walkExpressionTree(cursor->value, NULL, operatorname, true, dummy1);
        cursor = cursor->rest;
      }
      if (warnP &&
          (!symbolCommonLispP(operatorname))) {
        if ((operatorname == SYM_WALK_STELLA_NULLp) ||
            (operatorname == SYM_WALK_STELLA_DEFINEDp)) {
          if (!(walkTypeSpecIsNativeTypeP(type))) {
            std::cout << "Using default native test for " << "`" << operatorname << "'" << " in the expression:" << std::endl << "  " << "`" << tree << "'" << std::endl;
          }
        }
        else {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Reference to undefined method or function named " << "`" << deUglifyParseTree(operatorname) << "'" << std::endl << "   in the expression:" << std::endl << "   " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
            }
          }
        }
      }
      { Cons* _Return0 = listO(3, SYM_WALK_STELLA_SYS_CALL_METHOD, type, tree->concatenate(NIL, 0));

        _Return1 = SGT_WALK_STELLA_UNKNOWN;
        return (_Return0);
      }
    }
  }
}

Cons* walkSlotOnAbstractTypeTree(Cons* tree, Surrogate* abstracttype, StandardObject*& _Return1) {
  { StandardObject* dummy1;

    { Object* methodname = tree->value;
      MethodSlot* prototypemethod = findPrototypeMethod(((Symbol*)(methodname)), abstracttype);
      boolean undefinedmethodP = true;
      Object* otree = NULL;
      StandardObject* otype = NULL;

      if (((boolean)(prototypemethod))) {
        undefinedmethodP = false;
        if (warnAboutMissingMethodsP()) {
          { int nofsubs = NULL_INTEGER;
            int nofmethods = NULL_INTEGER;
            boolean compatibleP = false;

            nofsubs = compatibleRealMethods(prototypemethod, abstracttype, nofmethods, compatibleP);
            if ((nofsubs == nofmethods) &&
                compatibleP) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationNote();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> NOTE: ", STANDARD_OUTPUT);
                  std::cout << std::endl << " " << "Inferred the method " << "`" << deUglifyParseTree(methodname) << "'" << " on the abstract" << std::endl << "   type " << "`" << deUglifyParseTree(abstracttype) << "'" << ", since " << "`" << deUglifyParseTree(methodname) << "'" << " is implemented" << std::endl << "   on all non-abstract subtypes of " << "`" << deUglifyParseTree(abstracttype) << "'" << "." << std::endl;
                }
              }
              tree->secondSetter(sysTree(tree->rest->value, prototypemethod->slotOwner, dummy1));
              otree = walkCallSlotTree(tree, otype);
            }
            else if (nofsubs == nofmethods) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationWarning();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> WARNING: ", STANDARD_WARNING);
                  *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Could not infer " << "`" << deUglifyParseTree(methodname) << "'" << " on abstract type " << "`" << deUglifyParseTree(abstracttype) << "'" << "," << std::endl << "   since the implementations of " << "`" << deUglifyParseTree(methodname) << "'" << " on the non-abstract" << std::endl << "   subtypes of " << "`" << deUglifyParseTree(abstracttype) << "'" << " are not all compatible" << "." << std::endl;
                }
              }
            }
            else {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationWarning();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> WARNING: ", STANDARD_WARNING);
                  *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Could not infer " << "`" << deUglifyParseTree(methodname) << "'" << " on abstract type " << "`" << deUglifyParseTree(abstracttype) << "'" << "," << std::endl << "   since " << "`" << deUglifyParseTree(methodname) << "'" << " is only implemented on " << "`" << deUglifyParseTree(wrapInteger(nofmethods)) << "'" << " of the " << "`" << deUglifyParseTree(wrapInteger(nofsubs)) << "'" << std::endl << "   non-abstract subtypes of " << "`" << deUglifyParseTree(abstracttype) << "'" << "." << std::endl;
                }
              }
              if (!(compatibleP)) {
                std::cout << " Additionally, the method signatures are " << "not compatible." << std::endl;
              }
            }
          }
        }
      }
      if (undefinedmethodP) {
        { Cons* value000 = NULL;
          Surrogate* value001 = NULL;

          value000 = walkUndefinedSlotTree(tree, abstracttype, warnAboutUndefinedMethodsP(), value001);
          {
            otree = value000;
            otype = value001;
          }
        }
      }
      else {
        { Cons* value002 = NULL;
          Surrogate* value003 = NULL;

          value002 = walkUndefinedSlotTree(tree, abstracttype, false, value003);
          {
            otree = value002;
            otype = value003;
          }
        }
      }
      _Return1 = otype;
      return (((Cons*)(otree)));
    }
  }
}

MethodSlot* findPrototypeMethod(Symbol* methodname, Surrogate* abstracttype) {
  { Slot* method = NULL;

    { Surrogate* sub = NULL;
      Cons* iter000 = ((Class*)(abstracttype->surrogateValue))->classDirectSubs->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        sub = ((Surrogate*)(iter000->value));
        if (((boolean)(((Class*)(sub->surrogateValue))))) {
          if (((Class*)(sub->surrogateValue))->abstractP) {
            method = findPrototypeMethod(methodname, sub);
          }
          else {
            method = lookupSlot(((Class*)(sub->surrogateValue)), methodname);
          }
          if (((boolean)(method)) &&
              (!storageSlotP(method))) {
            return (((MethodSlot*)(method)));
          }
        }
      }
    }
    return (NULL);
  }
}

int compatibleRealMethods(MethodSlot* prototypemethod, Surrogate* abstracttype, int& _Return1, boolean& _Return2) {
  { Symbol* methodname = prototypemethod->slotName;
    int nofrealsubtypes = 0;
    int nofrealmethods = 0;
    boolean compatiblesignaturesP = true;

    { Surrogate* sub = NULL;
      Cons* iter000 = ((Class*)(abstracttype->surrogateValue))->classDirectSubs->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        sub = ((Surrogate*)(iter000->value));
        if (((Class*)(sub->surrogateValue))->abstractP) {
          { int nofsubs = NULL_INTEGER;
            int nofmethods = NULL_INTEGER;
            boolean compatibleP = false;

            nofsubs = compatibleRealMethods(prototypemethod, sub, nofmethods, compatibleP);
            nofrealsubtypes = nofrealsubtypes + nofsubs;
            nofrealmethods = nofrealmethods + nofmethods;
            if (!(compatibleP)) {
              compatiblesignaturesP = false;
            }
          }
        }
        else {
          { Slot* thismethod = NULL;

            nofrealsubtypes = nofrealsubtypes + 1;
            thismethod = lookupSlot(((Class*)(sub->surrogateValue)), methodname);
            if (((boolean)(thismethod)) &&
                (!storageSlotP(thismethod))) {
              nofrealmethods = nofrealmethods + 1;
              if (!(identicalSignaturesP(prototypemethod, ((MethodSlot*)(thismethod))))) {
                compatiblesignaturesP = false;
              }
            }
          }
        }
      }
    }
    _Return1 = nofrealmethods;
    _Return2 = compatiblesignaturesP;
    return (nofrealsubtypes);
  }
}

Object* Slot::finishWalkingCallSlotTree(Cons* tree, StandardObject* firstargtype, StandardObject*& _Return1) {
  { Slot* self = this;

    {
      tree = tree;
      firstargtype = firstargtype;
    }
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "finish-walking-call-slot-tree: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Object* StorageSlot::finishWalkingCallSlotTree(Cons* tree, StandardObject* firstargtype, StandardObject*& _Return1) {
  { StorageSlot* self = this;
    StandardObject* dummy1;

    { Object* objectref = tree->rest->value;
      StandardObject* otype = self->computeReturnTypeSpec(firstargtype);

      if (((boolean)(self->reader()))) {
        tree->firstSetter(self->reader());
        return (walkAConsTree(tree, _Return1));
      }
      if (systemDefinedSlotReaderP(self)) {
        { Object* _Return0 = listO(3, SYM_WALK_STELLA_SYS_CALL_METHOD, self->slotOwner, cons(self->slotName, cons(objectref, NIL)));

          _Return1 = otype;
          return (_Return0);
        }
      }
      else {
        { Object* _Return0 = yieldSlotValueTree(self, objectref, firstargtype, otype, NULL, dummy1);

          _Return1 = otype;
          return (_Return0);
        }
      }
    }
  }
}

boolean stringConcatenateMethodP(MethodSlot* method) {
  return ((method->slotName == SYM_WALK_STELLA_CONCATENATE) &&
      (method->slotOwner == SGT_WALK_STELLA_STRING));
}

boolean passVariableArgumentsAsListP(MethodSlot* method) {
  return (methodMustBeEvaluableP(method) ||
      ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA) &&
       ((oMETHODBEINGWALKEDo == method) ||
        (!stringConcatenateMethodP(method)))));
}

StandardObject* variableArgumentsType(MethodSlot* method) {
  { boolean dummy1;

    return (extractParameterType(((StandardObject*)(method->methodParameterTypeSpecifiers_reader()->last())), SYM_WALK_STELLA_ANY_VALUE, dummy1));
  }
}

Symbol* variableArgumentsName(MethodSlot* method) {
  return (((Symbol*)(method->methodParameterNames_reader()->last())));
}

StandardObject* yieldListifiedVariableArgumentsType(MethodSlot* method) {
  { Surrogate* listbasetype = SGT_WALK_STELLA_CONS;
    StandardObject* elementtype = variableArgumentsType(method);

    if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA) &&
        (!methodMustBeEvaluableP(method))) {
    }
    if (typeP(elementtype)) {
      elementtype = ((Surrogate*)(elementtype))->typeToWrappedType();
    }
    { ParametricTypeSpecifier* self000 = newParametricTypeSpecifier();

      self000->specifierBaseType = listbasetype;
      self000->specifierParameterTypes = list(1, elementtype);
      { ParametricTypeSpecifier* value000 = self000;

        return (value000);
      }
    }
  }
}

Cons* yieldListifiedVariableArguments(Cons* walkedargs, StandardObject* targettype, boolean wrapargsP) {
  { StandardObject* dummy1;

    if (!(walkedargs == NIL)) {
      { Object* listifiedargs = SYM_WALK_STELLA_NIL;

        { ConsIterator* it = walkedargs->allocateIterator();

          for (; it->nextP(); ) {
            { Object* arg = it->value;

              arg = sysTree(arg, targettype, dummy1);
              if (wrapargsP) {
                arg = cons(((targettype == SGT_WALK_STELLA_BOOLEAN) ? SYM_WALK_STELLA_WRAP_BOOLEAN : SYM_WALK_STELLA_WRAP_LITERAL), cons(arg, NIL));
              }
              it->valueSetter(arg);
            }
          }
        }
        if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA) {
          { Object* arg = NULL;
            Cons* iter000 = walkedargs->reverse();

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              arg = iter000->value;
              listifiedargs = listO(3, SYM_WALK_STELLA_CONS, arg, cons(listifiedargs, NIL));
            }
          }
        }
        else {
          listifiedargs = listO(3, SYM_WALK_STELLA_CONS_LIST, walkedargs->value, walkedargs->rest->concatenate(NIL, 0));
        }
        return (((Cons*)(walkWithoutTypeTree(listifiedargs))));
      }
    }
    else {
      return (cons(SYM_WALK_STELLA_NIL, NIL));
    }
  }
}

Object* finishWalkingArgumentListTree(Slot* self, Cons* tree, StandardObject* firstargtype, StandardObject*& _Return1) {
  if (self->slotName == SYM_WALK_STELLA_ALLOCATE_ITERATOR) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Cannot invoke " << "`" << deUglifyParseTree(self) << "'" << " directly, use `foreach' instead" << "." << std::endl;
      }
    }
    return (walkDontCallMeTree(tree, SGT_WALK_STELLA_ARGUMENT_LIST_ITERATOR, _Return1));
  }
  if (self->slotOwner == SGT_WALK_STELLA_CONS) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationNote();
      if (!(suppressWarningsP())) {
        printErrorContext(">> NOTE: ", STANDARD_OUTPUT);
        std::cout << std::endl << " " << "Applying CONS-methods to &rest-arguments is deprecated." << std::endl << "   " << "`" << deUglifyParseTree(tree) << "'" << std::endl << " Use `foreach' or explicitly coerce with `coerce-&rest-to-cons'" << "." << std::endl;
      }
    }
    firstargtype = yieldListifiedVariableArgumentsType(oMETHODBEINGWALKEDo);
  }
  if (passVariableArgumentsAsListP(oMETHODBEINGWALKEDo)) {
    if (self->slotName == SYM_WALK_STELLA_LENGTH) {
      return (sysTree(listO(3, SYM_WALK_STELLA_SYS_CALL_METHOD, typeSpecToBaseType(yieldListifiedVariableArgumentsType(oMETHODBEINGWALKEDo)), tree->concatenate(NIL, 0)), SGT_WALK_STELLA_INTEGER, _Return1));
    }
    else {
      return (self->finishWalkingCallSlotTree(tree, firstargtype, _Return1));
    }
  }
  else {
    return (self->finishWalkingCallSlotTree(tree, firstargtype, _Return1));
  }
}

Cons* walkVariableArguments(Cons* arguments, MethodSlot* method, StandardObject* firstargtype) {
  { StandardObject* dummy1;

    { StandardObject* targettype = variableArgumentsType(method);
      boolean listifyargsP = passVariableArgumentsAsListP(method);
      boolean wrapargsP = false;
      Cons* cursor = arguments;

      if ((!typeP(targettype)) &&
          ((boolean)(firstargtype))) {
        targettype = computeRelativeTypeSpec(targettype, firstargtype);
      }
      wrapargsP = listifyargsP &&
          subTypeSpecOfP(targettype, SGT_WALK_STELLA_LITERAL);
      while (!(cursor == NIL)) {
        cursor->value = walkExpressionTree(cursor->value, targettype, method->slotName, false, dummy1);
        cursor = cursor->rest;
      }
      if (listifyargsP) {
        { Cons* listifiedargs = yieldListifiedVariableArguments(arguments, targettype, wrapargsP);

          if (arguments == NIL) {
            return (listifiedargs);
          }
          arguments->value = listifiedargs;
          arguments->rest = NIL;
        }
      }
      return (arguments);
    }
  }
}

Object* MethodSlot::finishWalkingCallSlotTree(Cons* tree, StandardObject* firstargtype, StandardObject*& _Return1) {
  { MethodSlot* self = this;
    StandardObject* dummy1;

    { Symbol* methodname = self->slotName;
      StandardObject* otypespec = self->computeReturnTypeSpec(firstargtype);
      Object* otree = NULL;

      { List* ptypespecs = self->methodParameterTypeSpecifiers_reader();
        int nofparameters = ptypespecs->length();
        Cons* cursor = tree->rest->rest;

        { StandardObject* targetts = NULL;
          Cons* iter000 = ptypespecs->rest();
          int pindex = NULL_INTEGER;
          int iter001 = 2;
          int upperBound000 = nofparameters;
          boolean unboundedP000 = upperBound000 == NULL_INTEGER;

          for  (; (!(iter000 == NIL)) &&
                    (unboundedP000 ||
                     (iter001 <= upperBound000)); 
                iter000 = iter000->rest,
                iter001 = iter001 + 1) {
            targetts = ((StandardObject*)(iter000->value));
            pindex = iter001;
            targetts = computeRelativeTypeSpec(targetts, firstargtype);
            if ((pindex == nofparameters) &&
                ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_WALK_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue) {
              tree->nthRestSetter(walkVariableArguments(cursor, self, firstargtype), pindex);
              break;
            }
            cursor->value = walkExpressionTree(cursor->value, targetts, methodname, true, dummy1);
            cursor = cursor->rest;
          }
        }
      }
      { Object* arg = NULL;
        Cons* iter002 = tree->rest;

        for (; !(iter002 == NIL); iter002 = iter002->rest) {
          arg = iter002->value;
          if (vrletExpressionP(arg)) {
            return (percolateOutVrletExpression(tree, ((Cons*)(arg)), otypespec, _Return1));
          }
        }
      }
      if (inlineMethodCallP(self)) {
        otree = walkInlineMethodCall(self, tree->rest, firstargtype);
        if (((boolean)(otree))) {
          return (sysTree(otree, otypespec, _Return1));
        }
      }
      if (self->methodFunctionP) {
        otree = cons(SYM_WALK_STELLA_SYS_CALL_FUNCTION, tree->concatenate(NIL, 0));
      }
      else {
        otree = listO(3, SYM_WALK_STELLA_SYS_CALL_METHOD, self->slotOwner, tree->concatenate(NIL, 0));
      }
      _Return1 = otypespec;
      return (otree);
    }
  }
}

Cons* quoteArguments(MethodSlot* method, Cons* arguments) {
  { List* ptypespecs = method->methodParameterTypeSpecifiers_reader();
    int lastparameterindex = ptypespecs->length() - 1;
    StandardObject* varargstype = (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue ? variableArgumentsType(method) : ((StandardObject*)(NULL)));
    StandardObject* ptype = NULL;

    { ConsIterator* it = arguments->allocateIterator();
      int argindex = NULL_INTEGER;
      int iter000 = 0;

      for  (; it->nextP(); 
            iter000 = iter000 + 1) {
        argindex = iter000;
        if (!(surrogateP(it->value) ||
            keywordP(it->value))) {
          if ((argindex >= lastparameterindex) &&
              ((boolean)(varargstype))) {
            ptype = varargstype;
          }
          else {
            ptype = ((StandardObject*)(ptypespecs->nth(argindex)));
          }
          if ((it->value == SYM_WALK_STELLA_NULL) ||
              (((ptype == SGT_WALK_STELLA_BOOLEAN) &&
              ((it->value == SYM_WALK_STELLA_TRUE) ||
               (it->value == SYM_WALK_STELLA_FALSE))) ||
               (wrapperP(it->value) &&
                (((boolean)(ptype)) &&
                 subTypeSpecOfP(ptype, SGT_WALK_STELLA_LITERAL))))) {
            continue;
          }
          it->valueSetter(listO(3, SYM_WALK_STELLA_COPY_CONS_TREE, listO(3, SYM_WALK_STELLA_QUOTE, it->value, NIL), NIL));
        }
      }
    }
    return (arguments);
  }
}

StandardObject* walkFirstArgumentToFunction(MethodSlot* fnslot, Cons* tree) {
  { List* ptypespecs = fnslot->methodParameterTypeSpecifiers_reader();
    StandardObject* targetts = ((StandardObject*)(ptypespecs->first()));

    if (!fnslot->methodEvaluateArgumentsP_reader()) {
      tree->rest = quoteArguments(fnslot, tree->rest);
    }
    if (((BooleanWrapper*)(dynamicSlotValue(fnslot->dynamicSlots, SYM_WALK_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue &&
        (ptypespecs->length() == 1)) {
      tree->rest = walkVariableArguments(tree->rest, fnslot, NULL);
      return (SGT_WALK_STELLA_UNKNOWN);
    }
    if ((tree->rest == NIL) ||
        fnslot->methodParameterTypeSpecifiers_reader()->emptyP()) {
      return (SGT_WALK_STELLA_UNKNOWN);
    }
    { Object* otree = NULL;
      StandardObject* otype = NULL;

      otree = walkExpressionTree(tree->rest->value, targetts, fnslot->slotName, true, otype);
      tree->secondSetter(otree);
      if (subtypeOfIntegerP(safePrimaryType(otree))) {
        { Object* otree000 = otree;
          IntegerWrapper* otree = ((IntegerWrapper*)(otree000));

          { Symbol* testValue000 = fnslot->slotName;

            if (testValue000 == SYM_WALK_STELLA_GET_SYM) {
              registerSymbol(getSymFromOffset(otree->wrapperValue));
            }
            else if (testValue000 == SYM_WALK_STELLA_GET_SGT) {
              registerSymbol(getSgtFromOffset(otree->wrapperValue));
            }
            else if (testValue000 == SYM_WALK_STELLA_GET_KWD) {
              registerSymbol(getKwdFromOffset(otree->wrapperValue));
            }
            else {
            }
          }
        }
      }
      else {
      }
      return (otype);
    }
  }
}

Object* walkCallSlotTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;

    { Object* slotname = tree->value;
      Object* walkedfirstarg = NULL;
      StandardObject* firstargtype = SGT_WALK_STELLA_VOID;
      Class* firstargclass = NULL;
      boolean illegalfirstargP = false;
      int previouserrors = oTRANSLATIONERRORSo;
      Slot* slot = NULL;

      if (slotname == SYM_WALK_STELLA_ERROR) {
        oFOUNDRETURNpo = true;
      }
      slot = lookupFunction(((Symbol*)(slotname)));
      if (((boolean)(slot))) {
        if (((BooleanWrapper*)(dynamicSlotValue(((MethodSlot*)(slot))->dynamicSlots, SYM_WALK_STELLA_METHOD_MACROp, FALSE_WRAPPER)))->wrapperValue) {
          return (walkMacroTree(tree, _Return1));
        }
        else {
          firstargtype = walkFirstArgumentToFunction(((MethodSlot*)(slot)), tree);
        }
      }
      else {
        if (!(tree->rest == NIL)) {
          walkedfirstarg = walkExpressionTree(tree->rest->value, SGT_WALK_STELLA_UNKNOWN, ((Symbol*)(slotname)), true, firstargtype);
          tree->secondSetter(coerceATree(walkedfirstarg, firstargtype, firstargtype, dummy1));
          if (voidP(firstargtype)) {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "First argument in call to " << "`" << deUglifyParseTree(slotname) << "'" << " returns @VOID" << "." << std::endl;
              }
            }
            return (walkDontCallMeTree(tree, SGT_WALK_STELLA_UNKNOWN, _Return1));
          }
          firstargclass = typeSpecToClass(firstargtype);
          slot = lookupSlot(firstargclass, ((Symbol*)(slotname)));
        }
      }
      illegalfirstargP = oTRANSLATIONERRORSo > previouserrors;
      if (vrletExpressionP(tree->rest->value)) {
        return (percolateOutVrletExpression(tree, ((Cons*)(tree->rest->value)), SGT_WALK_STELLA_UNKNOWN, _Return1));
      }
      if ((!((boolean)(slot))) &&
          subTypeSpecOfP(firstargtype, SGT_WALK_STELLA_ARGUMENT_LIST)) {
        slot = lookupSlot(((Class*)(SGT_WALK_STELLA_CONS->surrogateValue)), ((Symbol*)(slotname)));
      }
      if (!((boolean)(slot))) {
        if (warnAboutUndefinedMethodsP() &&
            ((!(firstargtype == SGT_WALK_STELLA_UNKNOWN)) &&
             (((boolean)(firstargclass)) &&
              firstargclass->abstractP))) {
          return (walkSlotOnAbstractTypeTree(tree, typeSpecToBaseType(firstargtype), _Return1));
        }
        else {
          { Cons* value000 = NULL;
            Surrogate* value001 = NULL;

            value000 = walkUndefinedSlotTree(tree, (voidP(firstargtype) ? SGT_WALK_STELLA_UNKNOWN : ((StandardObject*)(firstargtype))), (!illegalfirstargP) &&
                warnAboutUndefinedMethodsP(), value001);
            _Return1 = value001;
            return (value000);
          }
        }
      }
      { int minargs = slot->methodArgumentCount();
        int maxargs = minargs;

        if (subtypeOfMethodSlotP(safePrimaryType(slot))) {
          { Slot* slot000 = slot;
            MethodSlot* slot = ((MethodSlot*)(slot000));

            if (((BooleanWrapper*)(dynamicSlotValue(slot->dynamicSlots, SYM_WALK_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue ||
                ((BooleanWrapper*)(dynamicSlotValue(slot->dynamicSlots, SYM_WALK_STELLA_METHOD_BODY_ARGUMENTp, FALSE_WRAPPER)))->wrapperValue) {
              minargs = minargs - 1;
              maxargs = NULL_INTEGER;
            }
          }
        }
        else {
        }
        if (badArgumentRangeP(tree, minargs, maxargs)) {
          return (walkDontCallMeTree(tree, SGT_WALK_STELLA_UNKNOWN, _Return1));
        }
      }
      { Object* otree = NULL;
        StandardObject* otype = NULL;

        if (subTypeSpecOfP(firstargtype, SGT_WALK_STELLA_ARGUMENT_LIST)) {
          otree = finishWalkingArgumentListTree(slot, tree, firstargtype, otype);
        }
        else {
          otree = slot->finishWalkingCallSlotTree(tree, firstargtype, otype);
        }
        return (sysTreeIfNeeded(slot, otree, firstargtype, otype, _Return1));
      }
    }
  }
}

boolean inlineMethodCallP(MethodSlot* method) {
  return (methodCallInliningEnabledP() &&
      ((((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_GLOBALLY_INLINEp, FALSE_WRAPPER)))->wrapperValue ||
      (((boolean)(oMETHODBEINGWALKEDo)) &&
       oMETHODBEINGWALKEDo->methodInlinedFunctions_reader()->memberP(method->slotName))) &&
       methodInlinableP(method)));
}

boolean methodInlinableP(MethodSlot* method) {
  if (voidP(method->type()) ||
      ((method->methodReturnTypeSpecifiers_reader()->length() > 1) ||
       ((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue)) {
    return (false);
  }
  if (method->methodFunctionP ||
      mostSpecificMethodP(method)) {
    return (((boolean)(inlinableMethodBody(method))));
  }
  else {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationNote();
      if (!(suppressWarningsP())) {
        printErrorContext(">> NOTE: ", STANDARD_OUTPUT);
        std::cout << std::endl << " " << "Cannot inline method " << "`" << deUglifyParseTree(method) << "'" << ", since there are" << std::endl << " one or more methods that specialize it" << "." << std::endl;
      }
    }
    return (false);
  }
}

boolean mostSpecificMethodP(MethodSlot* method) {
  { boolean alwaysP000 = true;

    { Surrogate* sub = NULL;
      Cons* iter000 = ((Class*)(method->slotOwner->surrogateValue))->classDirectSubs->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        sub = ((Surrogate*)(iter000->value));
        if (!helpMostSpecificMethodP(((Class*)(sub->surrogateValue)), method)) {
          alwaysP000 = false;
          break;
        }
      }
    }
    { boolean value000 = alwaysP000;

      return (value000);
    }
  }
}

boolean helpMostSpecificMethodP(Class* clasS, MethodSlot* method) {
  if (!((boolean)(clasS))) {
    return (true);
  }
  { boolean testValue000 = false;

    { boolean foundP000 = false;

      { Slot* slot = NULL;
        Cons* iter000 = clasS->classLocalSlots->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          slot = ((Slot*)(iter000->value));
          if (slot->slotDirectEquivalent == method) {
            foundP000 = true;
            break;
          }
        }
      }
      testValue000 = foundP000;
    }
    testValue000 = !testValue000;
    if (testValue000) {
      { boolean alwaysP000 = true;

        { Surrogate* sub = NULL;
          Cons* iter001 = clasS->classDirectSubs->theConsList;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            sub = ((Surrogate*)(iter001->value));
            if (!helpMostSpecificMethodP(((Class*)(sub->surrogateValue)), method)) {
              alwaysP000 = false;
              break;
            }
          }
        }
        testValue000 = alwaysP000;
      }
    }
    { boolean value000 = testValue000;

      return (value000);
    }
  }
}

Object* inlinableMethodBody(MethodSlot* method) {
  { Cons* definition = NULL;
    Object* body = dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_CACHED_INLINABLE_METHOD_BODY, NULL);

    if (body == method) {
      return (NULL);
    }
    if (((boolean)(body))) {
      return (body);
    }
    definition = ((Cons*)(unstringifyStellaSource(method->methodStringifiedSource, method->homeModule())));
    extractOptions(definition, NULL);
    setDynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_CACHED_INLINABLE_METHOD_BODY, method, NULL);
    if (definition->length() == 4) {
      body = definition->last();
      if (safePrimaryType(body) == SGT_WALK_STELLA_CONS) {
        { Object* body000 = body;
          Cons* body = ((Cons*)(body000));

          if ((body->value == SYM_WALK_STELLA_RETURN) &&
              (verbatimTreeP(body->rest->value) ||
               (!searchConsTreeP(body, SYM_WALK_STELLA_VERBATIM)))) {
            return (setDynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_CACHED_INLINABLE_METHOD_BODY, permanentifyForm(body->rest->value), NULL));
          }
        }
      }
      else {
      }
    }
    return (NULL);
  }
}

DEFINE_STELLA_SPECIAL(oINLININGMETHODCALLpo, boolean , false);

Object* walkInlineMethodCall(MethodSlot* method, Cons* walkedargs, StandardObject* firstargtype) {
  { StandardObject* dummy1;

    { Object* body = inlinableMethodBody(method);
      int nofreferences = NULL_INTEGER;
      Object* inlinearg = NULL;
      boolean successP = true;

      if (verbatimTreeP(body) &&
          ((boolean)(lookupVerbatimTree(((Cons*)(body)), NULL)))) {
        return (yieldVerbatimInlineCallTree(method, walkedargs));
      }
      body = copyConsTree(body);
      { 
        BIND_STELLA_SPECIAL(oINLININGMETHODCALLpo, boolean, true);
        BIND_STELLA_SPECIAL(oMETHODBEINGWALKEDo, MethodSlot*, method);
        { Symbol* var = NULL;
          Cons* iter000 = method->methodParameterNames_reader()->theConsList;
          StandardObject* tspec = NULL;
          Cons* iter001 = method->methodParameterTypeSpecifiers_reader()->theConsList;
          Object* arg = NULL;
          Cons* iter002 = walkedargs;
          int i = NULL_INTEGER;
          int iter003 = 0;

          for  (; (!(iter000 == NIL)) &&
                    ((!(iter001 == NIL)) &&
                     (!(iter002 == NIL))); 
                iter000 = iter000->rest,
                iter001 = iter001->rest,
                iter002 = iter002->rest,
                iter003 = iter003 + 1) {
            var = ((Symbol*)(iter000->value));
            tspec = ((StandardObject*)(iter001->value));
            arg = iter002->value;
            i = iter003;
            if ((i == 0) &&
                (mixinMethodP(method) &&
                 translateToSingleInheritanceLanguageP())) {
              tspec = firstargtype;
            }
            else {
              tspec = computeRelativeTypeSpec(tspec, firstargtype);
            }
            walkADeclaration(var, tspec, NULL, true);
            setLocalVariableInfo(var, KWD_WALK_INLINE_ARGUMENT, arg);
            setLocalVariableInfo(var, KWD_WALK_INLINE_REFERENCES, wrapInteger(0));
          }
        }
        body = walkExpressionTree(body, method->type(), SYM_WALK_STELLA_INLINE_CALL, true, dummy1);
      }
      if (proceduralExpressionP(body)) {
        successP = false;
      }
      if (successP) {
        { Symbol* var = NULL;
          Cons* iter004 = method->methodParameterNames_reader()->theConsList;

          for (; !(iter004 == NIL); iter004 = iter004->rest) {
            var = ((Symbol*)(iter004->value));
            inlinearg = getLocalVariableInfo(var, KWD_WALK_INLINE_ARGUMENT);
            nofreferences = ((IntegerWrapper*)(getLocalVariableInfo(var, KWD_WALK_INLINE_REFERENCES)))->wrapperValue;
            switch (nofreferences) {
              case 0: 
                if (!sideEffectFreeExpressionP(inlinearg)) {
                  successP = false;
                  goto loopExit092;
                }
                break;
              case 1: 
                break;
              default:
                if (!(sideEffectFreeExpressionP(inlinearg) &&
                    ((estimatedEvaluationCost(inlinearg) * nofreferences) <= 2))) {
                  successP = false;
                  goto loopExit092;
                }
                break;
            }
          }
        }
        loopExit092:;
      }
      { Symbol* var = NULL;
        Cons* iter005 = method->methodParameterNames_reader()->theConsList;

        for (; !(iter005 == NIL); iter005 = iter005->rest) {
          var = ((Symbol*)(iter005->value));
          var = var;
          popVariableBinding();
        }
      }
      return ((successP ? body : NULL));
    }
  }
}

Cons* yieldVerbatimInlineCallTree(MethodSlot* method, Cons* walkedargs) {
  return (listO(3, SYM_WALK_STELLA_SYS_INLINE_CALL, cons((method->methodFunctionP ? SYM_WALK_STELLA_SYS_CALL_FUNCTION : SYM_WALK_STELLA_SYS_CALL_METHOD), ((method->methodFunctionP ? NIL : cons(method->slotOwner, NIL)))->concatenate(cons(method->slotName, walkedargs->concatenate(NIL, 0)), 0)), NIL));
}

boolean inlineVariableReferenceP(Symbol* self) {
  return (oINLININGMETHODCALLpo &&
      ((boolean)(getLocalVariableInfo(self, KWD_WALK_INLINE_ARGUMENT))));
}

Cons* walkInlineVariableReference(Symbol* self, StandardObject*& _Return1) {
  setLocalVariableInfo(self, KWD_WALK_INLINE_REFERENCES, wrapInteger(((IntegerWrapper*)(getLocalVariableInfo(self, KWD_WALK_INLINE_REFERENCES)))->wrapperValue + 1));
  return (sysTree(copyConsTree(getLocalVariableInfo(self, KWD_WALK_INLINE_ARGUMENT)), lookupVariableType(self), _Return1));
}

boolean sideEffectFreeExpressionP(Object* tree) {
  if (safePrimaryType(tree) == SGT_WALK_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

        if ((testValue000 == SYM_WALK_STELLA_TYPED_SYS) ||
            ((testValue000 == SYM_WALK_STELLA_CAST) ||
             (testValue000 == SYM_WALK_STELLA_SAFE_CAST))) {
          return (sideEffectFreeExpressionP(tree->rest->value));
        }
        else if ((testValue000 == SYM_WALK_STELLA_AND) ||
            ((testValue000 == SYM_WALK_STELLA_OR) ||
             ((testValue000 == SYM_WALK_STELLA_NOT) ||
              ((testValue000 == SYM_WALK_STELLA_EQp) ||
               ((testValue000 == SYM_WALK_STELLA_EQLp) ||
                ((testValue000 == SYM_WALK_STELLA_e) ||
                 ((testValue000 == SYM_WALK_STELLA_i) ||
                  ((testValue000 == SYM_WALK_STELLA__) ||
                   ((testValue000 == SYM_WALK_STELLA_o) ||
                    ((testValue000 == SYM_WALK_STELLA_s) ||
                     ((testValue000 == SYM_WALK_STELLA_g) ||
                      ((testValue000 == SYM_WALK_STELLA_ge) ||
                       ((testValue000 == SYM_WALK_STELLA_l) ||
                        ((testValue000 == SYM_WALK_STELLA_le) ||
                         ((testValue000 == SYM_WALK_STELLA_THE_CODE) ||
                          ((testValue000 == SYM_WALK_STELLA_SYS_SLOT_VALUE) ||
                           (testValue000 == SYM_WALK_STELLA_SYS_SLOT_VALUE_SETTER))))))))))))))))) {
          { boolean alwaysP000 = true;

            { Object* arg = NULL;
              Cons* iter000 = tree->rest;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                arg = iter000->value;
                if (!sideEffectFreeExpressionP(arg)) {
                  alwaysP000 = false;
                  break;
                }
              }
            }
            { boolean value000 = alwaysP000;

              return (value000);
            }
          }
        }
        else {
        }
      }
    }
  }
  else {
    return (true);
  }
  return (false);
}

int estimatedEvaluationCost(Object* tree) {
  { int cost = 0;

    if (safePrimaryType(tree) == SGT_WALK_STELLA_CONS) {
      { Object* tree000 = tree;
        Cons* tree = ((Cons*)(tree000));

        { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

          if ((testValue000 == SYM_WALK_STELLA_TYPED_SYS) ||
              ((testValue000 == SYM_WALK_STELLA_CAST) ||
               (testValue000 == SYM_WALK_STELLA_SAFE_CAST))) {
            return (estimatedEvaluationCost(tree->rest->value));
          }
          else if ((testValue000 == SYM_WALK_STELLA_AND) ||
              ((testValue000 == SYM_WALK_STELLA_OR) ||
               ((testValue000 == SYM_WALK_STELLA_NOT) ||
                ((testValue000 == SYM_WALK_STELLA_EQp) ||
                 ((testValue000 == SYM_WALK_STELLA_EQLp) ||
                  ((testValue000 == SYM_WALK_STELLA_e) ||
                   ((testValue000 == SYM_WALK_STELLA_i) ||
                    ((testValue000 == SYM_WALK_STELLA__) ||
                     ((testValue000 == SYM_WALK_STELLA_o) ||
                      ((testValue000 == SYM_WALK_STELLA_s) ||
                       ((testValue000 == SYM_WALK_STELLA_g) ||
                        ((testValue000 == SYM_WALK_STELLA_ge) ||
                         ((testValue000 == SYM_WALK_STELLA_l) ||
                          ((testValue000 == SYM_WALK_STELLA_le) ||
                           ((testValue000 == SYM_WALK_STELLA_THE_CODE) ||
                            ((testValue000 == SYM_WALK_STELLA_SYS_SLOT_VALUE) ||
                             (testValue000 == SYM_WALK_STELLA_SYS_SLOT_VALUE_SETTER))))))))))))))))) {
            cost = cost + 1;
            { Object* arg = NULL;
              Cons* iter000 = tree->rest;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                arg = iter000->value;
                cost = cost + estimatedEvaluationCost(arg);
              }
            }
          }
          else {
          }
        }
      }
    }
    else {
    }
    return (cost);
  }
}

Cons* yieldSynthesizedMethodBody(TranslationUnit* unit) {
  { MethodSlot* method = ((MethodSlot*)(unit->theObject));
    Cons* body = ((Cons*)(unit->codeRegister));

    if (!((boolean)(method->methodParameterNames_reader()))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing parameters for :inherits-through method" << "." << std::endl;
        }
      }
    }
    if (!(body == NIL)) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Over-specified definition of :inherits-through method" << "." << std::endl;
        }
      }
      return (body);
    }
    else {
      return (synthesizeMethodBody(method));
    }
  }
}

Cons* walkMethodObject(TranslationUnit* unit) {
  { MethodSlot* method = ((MethodSlot*)(unit->theObject));
    Cons* body = ((Cons*)(unit->codeRegister));

    { 
      BIND_STELLA_SPECIAL(oLOCALVARIABLETYPETABLEo, KeyValueList*, newKeyValueList());
      BIND_STELLA_SPECIAL(oLOCALGENSYMTABLEo, KeyValueList*, newKeyValueList());
      BIND_STELLA_SPECIAL(oSPECIALVARIABLESTACKo, KeyValueList*, newKeyValueList());
      BIND_STELLA_SPECIAL(oMETHODBEINGWALKEDo, MethodSlot*, method);
      BIND_STELLA_SPECIAL(oFOUNDRETURNpo, boolean, false);
      if (((boolean)(((Symbol*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_INHERITS_THROUGH, NULL)))))) {
        body = yieldSynthesizedMethodBody(unit);
      }
      { Symbol* name = NULL;
        Cons* iter000 = method->methodParameterNames_reader()->theConsList;
        StandardObject* typespec = NULL;
        Cons* iter001 = method->methodParameterTypeSpecifiers_reader()->theConsList;

        for  (; (!(iter000 == NIL)) &&
                  (!(iter001 == NIL)); 
              iter000 = iter000->rest,
              iter001 = iter001->rest) {
          name = ((Symbol*)(iter000->value));
          typespec = ((StandardObject*)(iter001->value));
          walkADeclaration(name, typespec, NULL, true);
        }
      }
      if (!(body == NIL)) {
        { boolean testValue000 = false;

          testValue000 = checkForIllegalReturnP();
          if (testValue000) {
            testValue000 = !voidP(method->type());
            if (testValue000) {
              testValue000 = !unit->auxiliaryP;
              if (testValue000) {
                testValue000 = !((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_SLOT_AUXILIARYp, FALSE_WRAPPER)))->wrapperValue;
                if (testValue000) {
                  { boolean foundP000 = false;

                    { Object* form = NULL;
                      Cons* iter002 = body;

                      for (; !(iter002 == NIL); iter002 = iter002->rest) {
                        form = iter002->value;
                        if (consP(form) &&
                            (((Cons*)(form))->value == SYM_WALK_STELLA_RETURN)) {
                          foundP000 = true;
                          break;
                        }
                      }
                    }
                    testValue000 = foundP000;
                  }
                  testValue000 = !testValue000;
                }
              }
            }
          }
          if (testValue000) {
            body = body->concatenate(cons(listO(4, SYM_WALK_STELLA_ERROR, wrapString("Returned from `"), wrapString(stringify(method)), cons(wrapString("' without a `return'."), NIL)), NIL), 0);
          }
        }
        if (logFunctionCallP(method) &&
            (!unit->auxiliaryP)) {
          body = wrapBodyWithLogFunctionCallTree(method, body);
        }
        body = walkListOfStatements(body);
        if ((!voidP(method->type())) &&
            ((!method->abstractP) &&
             (!oFOUNDRETURNpo))) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing return statement" << "." << std::endl;
            }
          }
        }
      }
      oLOCALVARIABLETYPETABLEo->free();
      oLOCALGENSYMTABLEo->free();
      oSPECIALVARIABLESTACKo->free();
      unit->codeRegister = body;
      return (body);
    }
  }
}

void walkDefmethodTree(Cons* tree) {
  { MethodSlot* method = NULL;

    { TranslationUnit* self000 = newTranslationUnit();

      self000->category = SYM_WALK_STELLA_METHOD;
      self000->theObject = tree;
      self000->tuHomeModule = oMODULEo;
      oCURRENTTRANSLATIONUNITo = self000;
    }
    method = defineMethodFromParseTree(tree);
    if ((!method->methodFunctionP) &&
        ((!((boolean)(method->slotOwner))) ||
         (!((boolean)(((Class*)(method->slotOwner->surrogateValue))))))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Can't define method " << "`" << method->slotName << "'" << " on the non-existent class " << "`" << method->slotOwner << "'" << "." << std::endl;
        }
      }
      method->free();
      clearTranslationUnit(oCURRENTTRANSLATIONUNITo);
      oCURRENTTRANSLATIONUNITo = NULL;
    }
    else {
      oCURRENTTRANSLATIONUNITo->theObject = method;
      oCURRENTTRANSLATIONUNITo->codeRegister = tree->nthRest(3);
      if (methodNeedsLispMacroP(method)) {
        registerNativeName(method->slotName, KWD_WALK_COMMON_LISP, KWD_WALK_FUNCTION);
      }
    }
  }
}

boolean methodStoresNativeCodePointerP(MethodSlot* method) {
  { Symbol* name = method->slotName;
    Surrogate* owner = method->slotOwner;

    if (method->abstractP) {
      return (false);
    }
    else if (name == SYM_WALK_STELLA_MAIN) {
      return (false);
    }
    else if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_NATIVEp, FALSE_WRAPPER)))->wrapperValue) {
      if (getQuotedTree("((NULL? DEFINED?) \"/STELLA\")", "/STELLA")->memberP(name)) {
        return (false);
      }
      if (((boolean)(oCPP_OPERATOR_TABLEo->lookup(name)))) {
        return (false);
      }
      { StandardObject* type = NULL;
        Cons* iter000 = method->methodParameterTypeSpecifiers_reader()->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          type = ((StandardObject*)(iter000->value));
          type = typeSpecToBaseType(computeRelativeTypeSpec(type, owner));
          if (subtypeOfP(((Surrogate*)(type)), SGT_WALK_STELLA_LITERAL) &&
              typeToClass(((Surrogate*)(type)))->abstractP) {
            return (false);
          }
        }
      }
    }
    return (true);
  }
}

void walkMethodUnit(TranslationUnit* unit) {
  { 
    BIND_STELLA_SPECIAL(oCURRENTTRANSLATIONUNITo, TranslationUnit*, unit);
    { MethodSlot* method = ((MethodSlot*)(unit->theObject));
      Symbol* name = method->slotName;
      Cons* body = ((Cons*)(unit->codeRegister));
      boolean createmethodobjectP = true;
      boolean storecodepointerP = true;
      MethodSlot* evaluatorwrappermethod = NULL;

      if (mixinMethodP(method) &&
          translateToSingleInheritanceLanguageP()) {
        clearTranslationUnit(unit);
        walkAuxiliaryTree(listO(4, SYM_WALK_STELLA_STARTUP_TIME_PROGN, KWD_WALK_METHODS, yieldDefineStellaMethodObject(method, NULL, NULL), NIL));
        return;
      }
      if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_FORWARD_DECLARATIONp, FALSE_WRAPPER)))->wrapperValue) {
        setDynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_FORWARD_DECLARATIONp, FALSE_WRAPPER, FALSE_WRAPPER);
      }
      if ((!method->methodFunctionP) &&
          ((!((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_NATIVEp, FALSE_WRAPPER)))->wrapperValue) &&
           (!(method->homeModule() == ((Class*)(method->owner()->surrogateValue))->homeModule())))) {
        if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationWarning();
            if (!(suppressWarningsP())) {
              printErrorContext(">> WARNING: ", STANDARD_WARNING);
              *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Defining method " << "`" << deUglifyParseTree(method) << "'" << " outside the home module of" << std::endl << "   its owner class will be illegal in C++ and Java" << "." << std::endl;
            }
          }
        }
        else {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Defining method " << "`" << deUglifyParseTree(method) << "'" << " outside the home module of" << std::endl << "   its owner class is illegal in " << "`" << translatorOutputLanguageName() << "'" << "." << std::endl;
            }
          }
          clearTranslationUnit(unit);
          return;
        }
      }
      if ((body == NIL) &&
          (!((boolean)(((Symbol*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_INHERITS_THROUGH, NULL))))))) {
        walkMethodObject(unit);
        if (!(((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_NATIVEp, FALSE_WRAPPER)))->wrapperValue ||
            method->abstractP)) {
          createmethodobjectP = false;
          setDynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_FORWARD_DECLARATIONp, TRUE_WRAPPER, FALSE_WRAPPER);
          if (oTRANSLATIONVERBOSITYLEVELo >= 3) {
            std::cout << "Forward declaration of " << "`" << method << "'" << std::endl;
          }
        }
        clearTranslationUnit(unit);
      }
      else if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_SLOT_AUXILIARYp, FALSE_WRAPPER)))->wrapperValue ||
          (unit->auxiliaryP &&
           (!inlineMethodP(method)))) {
        createmethodobjectP = false;
        oTRANSLATIONUNITSo->push(unit);
        walkMethodObject(unit);
      }
      else {
        oTRANSLATIONUNITSo->push(unit);
        walkMethodObject(unit);
      }
      if (createmethodobjectP) {
        if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_COMMANDp, FALSE_WRAPPER)))->wrapperValue &&
            (!commandP(method))) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationWarning();
            if (!(suppressWarningsP())) {
              printErrorContext(">> WARNING: ", STANDARD_WARNING);
              *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Ignored :command? declaration.  " << "Currently, only functions can be commands." << "." << std::endl;
            }
          }
        }
        if (methodNeedsEvaluatorWrapperP(method)) {
          evaluatorwrappermethod = createEvaluatorWrapperUnit(method);
        }
        if (methodNeedsLispMacroP(method)) {
          createLispMacroUnits(name, method);
        }
        if (methodNeedsCCallableWrapperP(method)) {
          createCCallableWrapperUnit(method);
        }
        storecodepointerP = methodStoresNativeCodePointerP(method);
        walkAuxiliaryTree(listO(4, SYM_WALK_STELLA_STARTUP_TIME_PROGN, KWD_WALK_METHODS, yieldDefineStellaMethodObject(method, (storecodepointerP ? method : NULL), (storecodepointerP ? evaluatorwrappermethod : NULL)), NIL));
        if (methodNeedsCCallableWrapperP(method) &&
            method->methodFunctionP) {
          walkAuxiliaryTree(listO(3, SYM_WALK_STELLA_STARTUP_TIME_PROGN, listO(4, SYM_WALK_STELLA_SETF, listO(3, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, listO(3, SYM_WALK_STELLA_LOOKUP_FUNCTION_BY_NAME, wrapString(name->symbolName), NIL), NIL), listO(4, SYM_WALK_STELLA_THE_CODE, KWD_WALK_FUNCTION, yieldCCallableWrapperName(method), NIL), NIL), NIL));
        }
      }
    }
  }
}

void printUndefinedMethods(Module* module, boolean localP) {
  // Print all declared but not yet defined functions and methods
  // in `module'.  If `local?' is true, do not consider any parent modules of
  // `module'.  If `module' is NULL, look at all modules in the system.  This
  // is handy to pinpoint forward declarations that haven't been followed up
  // by actual definitions.
  { Cons* undefinedmethods = NIL;

    { MethodSlot* method = NULL;
      Iterator* iter000 = allMethods(module, localP);
      Cons* collect000 = NULL;

      for  (; iter000->nextP(); ) {
        method = ((MethodSlot*)(iter000->value));
        if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_FORWARD_DECLARATIONp, FALSE_WRAPPER)))->wrapperValue &&
            ((!method->abstractP) &&
             (!methodContainsUnknownTypeP(method)))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(method, NIL);
              if (undefinedmethods == NIL) {
                undefinedmethods = collect000;
              }
              else {
                addConsToEndOfConsList(undefinedmethods, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(method, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    { MethodSlot* function = NULL;
      Iterator* iter001 = allFunctions(module, localP);
      Cons* collect001 = NULL;

      for  (; iter001->nextP(); ) {
        function = ((MethodSlot*)(iter001->value));
        if (((BooleanWrapper*)(dynamicSlotValue(function->dynamicSlots, SYM_WALK_STELLA_FORWARD_DECLARATIONp, FALSE_WRAPPER)))->wrapperValue) {
          if (!((boolean)(collect001))) {
            {
              collect001 = cons(function, NIL);
              if (undefinedmethods == NIL) {
                undefinedmethods = collect001;
              }
              else {
                addConsToEndOfConsList(undefinedmethods, collect001);
              }
            }
          }
          else {
            {
              collect001->rest = cons(function, NIL);
              collect001 = collect001->rest;
            }
          }
        }
      }
    }
    if (!(undefinedmethods == NIL)) {
      std::cout << "The following functions and methods are declared " << "but not yet defined:" << std::endl;
      { Object* method = NULL;
        Cons* iter002 = undefinedmethods;

        for (; !(iter002 == NIL); iter002 = iter002->rest) {
          method = iter002->value;
          std::cout << "    " << method << std::endl;
        }
      }
    }
  }
}

Cons* walkSysCallTree(Cons* tree, StandardObject*& _Return1) {
  { Slot* slot = slotFromExpressionTree(tree);
    StandardObject* slottype = SGT_WALK_STELLA_UNKNOWN;

    if (((boolean)(slot))) {
      slottype = ((CompoundTypeSpecifier*)(dynamicSlotValue(slot->dynamicSlots, SYM_WALK_STELLA_SLOT_TYPE_SPECIFIER, NULL)));
      { boolean testValue000 = false;

        testValue000 = ((boolean)(slottype));
        if (testValue000) {
          if (anchoredTypeSpecifierP(slottype)) {
            testValue000 = true;
          }
          else {
            { boolean foundP000 = false;

              { StandardObject* ts = NULL;
                Cons* iter000 = ((ParametricTypeSpecifier*)(slottype))->specifierParameterTypes->theConsList;

                for (; !(iter000 == NIL); iter000 = iter000->rest) {
                  ts = ((StandardObject*)(iter000->value));
                  if (anchoredTypeSpecifierP(ts)) {
                    foundP000 = true;
                    break;
                  }
                }
              }
              testValue000 = foundP000;
            }
          }
        }
        if (testValue000) {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "walk-sys-call-tree: OOPS, can't handle anchored slot types: " << "`" << tree << "'";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      if (!(((boolean)(slottype)))) {
        slottype = slot->type();
      }
    }
    _Return1 = slottype;
    return (tree);
  }
}

void walkDefclassTree(Cons* tree) {
  { TranslationUnit* self000 = newTranslationUnit();

    self000->category = SYM_WALK_STELLA_CLASS;
    self000->theObject = tree->rest->value;
    self000->tuHomeModule = oMODULEo;
    oCURRENTTRANSLATIONUNITo = self000;
  }
  oCURRENTTRANSLATIONUNITo->theObject = defineClassFromParseTree(tree);
  if (!((boolean)(oCURRENTTRANSLATIONUNITo->theObject))) {
    clearTranslationUnit(oCURRENTTRANSLATIONUNITo);
    oCURRENTTRANSLATIONUNITo = NULL;
  }
}

Cons* yieldInitializeHardwiredSlots(Class* clasS) {
  { Cons* hardwiredslotinitializers = NIL;

    if (createNativeClassP(clasS)) {
      { Slot* slot = NULL;
        Iterator* iter000 = clasS->classSlots();

        for (; iter000->nextP(); ) {
          slot = ((Slot*)(iter000->value));
          if (subtypeOfStorageSlotP(safePrimaryType(slot))) {
            { Slot* slot000 = slot;
              StorageSlot* slot = ((StorageSlot*)(slot000));

              if (slot->slotHardwiredP &&
                  ((boolean)(slot->initialValue()))) {
                hardwiredslotinitializers = cons(listO(3, SYM_WALK_STELLA_SETQ, yieldHardwiredSlotVariable(slot), cons(slot->initialValue(), NIL)), hardwiredslotinitializers);
              }
            }
          }
          else {
          }
        }
      }
    }
    return (hardwiredslotinitializers);
  }
}

Object* yieldInitialValueExpression(StorageSlot* slot) {
  if (slot->abstractP ||
      (slot->dynamicStorageP() ||
       (slot->slotHardwiredP ||
        (slot->allocation() == KWD_WALK_CLASS)))) {
    return (NULL);
  }
  { Object* initialvalueexpression = slot->initially();

    if (((boolean)(initialvalueexpression))) {
      return (copyConsTree(initialvalueexpression));
    }
    if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP) {
      if (slot->allocation() == KWD_WALK_EMBEDDED) {
        return (listO(3, SYM_WALK_STELLA_ALLOCATE, typeToSymbol(slot->type()), NIL));
      }
    }
    else if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA) ||
        ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP) ||
         ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP_STANDALONE) ||
          (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_IDL)))) {
      if (slot->allocation() == KWD_WALK_EMBEDDED) {
        return (listO(3, SYM_WALK_STELLA_ALLOCATE, typeToSymbol(slot->type()), NIL));
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    return (typeToWalkedNullValueTree(slot->typeSpecifier(), slot->type()));
  }
}

Cons* yieldConstructorAttachment(Class* clasS, Symbol* classref) {
  if ((!clasS->abstractP) &&
      createNativeClassP(clasS)) {
    { Cons* constructorfncode = listO(4, SYM_WALK_STELLA_THE_CODE, KWD_WALK_FUNCTION, yieldConstructorName(clasS), NIL);

      return (cons(listO(4, SYM_WALK_STELLA_SETF, listO(3, SYM_WALK_STELLA_CLASS_CONSTRUCTOR_CODE, classref, NIL), constructorfncode, NIL), NIL));
    }
  }
  else {
    return (NIL);
  }
}

List* Class::classAuxiliaryMethods_reader() {
  { Class* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_WALK_STELLA_CLASS_AUXILIARY_METHODS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

void cleanupAuxiliaryMethods(Class* clasS) {
  { List* auxiliarymethods = clasS->classAuxiliaryMethods_reader();
    Slot* reason = NULL;

    { MethodSlot* method = NULL;
      Cons* iter000 = auxiliarymethods->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        method = ((MethodSlot*)(iter000->value));
        if (!method->deletedP()) {
          if (coerceWrappedBooleanToBoolean(method->badP_reader())) {
            method->deletedPSetter(true);
          }
          else {
            reason = ((Slot*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_AUXILIARY_METHOD_REASON, NULL)));
            if ((!((boolean)(reason))) ||
                (reason->deletedP() ||
                 (coerceWrappedBooleanToBoolean(reason->badP_reader()) ||
                  ((!((boolean)(reason->slotOwner))) ||
                   ((reason->slotOwner->symbolId == -1) ||
                    ((!((boolean)(((Class*)(reason->slotOwner->surrogateValue))))) ||
                     (((Class*)(reason->slotOwner->surrogateValue))->deletedP() ||
                      (coerceWrappedBooleanToBoolean(((Class*)(reason->slotOwner->surrogateValue))->badP_reader()) ||
                       (!(lookupSlot(((Class*)(reason->slotOwner->surrogateValue)), reason->slotName) == reason)))))))))) {
              setDynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_AUXILIARY_METHOD_REASON, NULL, NULL);
              method->deletedPSetter(true);
            }
          }
        }
      }
    }
    auxiliarymethods->removeDeletedMembers();
  }
}

void registerAuxiliaryMethod(MethodSlot* method, Slot* reason) {
  if (((boolean)(method))) {
    { Class* clasS = ((Class*)(method->slotOwner->surrogateValue));
      List* auxiliarymethods = NULL;

      if (((boolean)(clasS))) {
        auxiliarymethods = clasS->classAuxiliaryMethods_reader();
        if (nullListP(auxiliarymethods)) {
          auxiliarymethods = ((List*)(setDynamicSlotValue(clasS->dynamicSlots, SYM_WALK_STELLA_CLASS_AUXILIARY_METHODS, newList(), NULL)));
        }
        finalizeAuxiliaryMethod(method);
        { MethodSlot* value000 = NULL;

          { MethodSlot* aux = NULL;
            Cons* iter000 = auxiliarymethods->theConsList;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              aux = ((MethodSlot*)(iter000->value));
              if ((method->slotName == aux->slotName) &&
                  (method->slotOwner == aux->slotOwner)) {
                value000 = aux;
                break;
              }
            }
          }
          auxiliarymethods->remove(value000);
        }
        auxiliarymethods->insert(method);
        setDynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_AUXILIARY_METHOD_REASON, reason, NULL);
      }
    }
  }
}

// A keyword describing how mixin classes are handled in
// single-inheritance target languages.  The legal values are
// :FIRST-CLASS-WITH-METHOD, which means that variables of a mixin type
// are legal and that slot access on a mixin type is facilitated by
// inherited-down accessor methods and a catch-all method on OBJECT,
// :FIRST-CLASS-WITH-TYPECASE which is similar but replaces the catch-all
// method with a function using a TYPECASE, and :SECOND-CLASS, which
// means that variables of a mixin type are illegal and no additional
// accessors and catch-all methods are needed.
Keyword* oMIXIN_IMPLEMENTATION_STYLEo = NULL;

boolean mixinTypeVariablesAllowedP() {
  return ((!translateToSingleInheritanceLanguageP()) ||
      (!(oMIXIN_IMPLEMENTATION_STYLEo == KWD_WALK_SECOND_CLASS)));
}

boolean createNativeMixinSlotAccessorsP() {
  return (translateToSingleInheritanceLanguageP() &&
      ((!translateToSingleInheritanceLanguageP()) ||
       (!(oMIXIN_IMPLEMENTATION_STYLEo == KWD_WALK_SECOND_CLASS))));
}

void createAccessorUnitsForSlot(StorageSlot* slot, Class* clasS, boolean mixinaccessorsP, boolean signaturesonlyP) {
  { Cons* methodtree = NULL;
    MethodSlot* method = NULL;

    if (systemDefinedSlotReaderP(slot)) {
      methodtree = yieldSlotReaderTree(slot, clasS);
      if (signaturesonlyP) {
        { 
          BIND_STELLA_SPECIAL(oMODULEo, Module*, slot->homeModule());
          BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
          method = defineMethodFromParseTree(methodtree);
        }
      }
      else {
        method = ((MethodSlot*)(helpWalkAuxiliaryTree(methodtree, true)->theObject));
      }
      registerAuxiliaryMethod(method, slot);
    }
    if (systemDefinedSlotWriterP(slot)) {
      methodtree = yieldSlotWriterTree(slot, clasS);
      if (signaturesonlyP) {
        { 
          BIND_STELLA_SPECIAL(oMODULEo, Module*, slot->homeModule());
          BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
          method = defineMethodFromParseTree(methodtree);
        }
      }
      else {
        method = ((MethodSlot*)(helpWalkAuxiliaryTree(methodtree, true)->theObject));
      }
      registerAuxiliaryMethod(method, slot);
    }
    if (mixinaccessorsP &&
        (!slot->abstractP)) {
      methodtree = yieldNativeSlotReaderTree(slot, clasS);
      if (signaturesonlyP) {
        { 
          BIND_STELLA_SPECIAL(oMODULEo, Module*, slot->homeModule());
          BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
          method = defineMethodFromParseTree(methodtree);
        }
      }
      else {
        method = ((MethodSlot*)(helpWalkAuxiliaryTree(methodtree, true)->theObject));
      }
      registerAuxiliaryMethod(method, slot);
      if (!(slot->slotHardwiredP)) {
        methodtree = yieldNativeSlotWriterTree(slot, clasS);
        if (signaturesonlyP) {
          { 
            BIND_STELLA_SPECIAL(oMODULEo, Module*, slot->homeModule());
            BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
            method = defineMethodFromParseTree(methodtree);
          }
        }
        else {
          method = ((MethodSlot*)(helpWalkAuxiliaryTree(methodtree, true)->theObject));
        }
        registerAuxiliaryMethod(method, slot);
      }
    }
  }
}

void createAccessorUnitsForMixinSlot(StorageSlot* slot, Class* clasS) {
  if (nativeSlotP(slot) &&
      (nativeSlotHome(slot, clasS) == clasS)) {
    if (oMIXIN_IMPLEMENTATION_STYLEo == KWD_WALK_FIRST_CLASS_WITH_TYPECASE) {
      walkAuxiliaryTree(yieldMixinSlotReaderTree(slot));
      walkAuxiliaryTree(yieldMixinSlotWriterTree(slot));
    }
    else {
      createAccessorUnitsForSlot(slot, ((Class*)(SGT_WALK_STELLA_OBJECT->surrogateValue)), true, false);
    }
  }
  if (slot->slotHardwiredP) {
    { Cons* readcode = NULL;
      Cons* auxiliarycode = NULL;

      readcode = yieldHardwiredSlotReaderBody(slot, auxiliarycode);
      readcode = readcode;
      walkAuxiliaryTree(auxiliarycode);
    }
    createAccessorUnitsForSlot(slot, ((Class*)(SGT_WALK_STELLA_OBJECT->surrogateValue)), false, false);
  }
}

void createSlotAccessorUnits(Class* clasS) {
  { Slot* slot = NULL;
    Cons* iter000 = clasS->localSlots()->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      slot = ((Slot*)(iter000->value));
      if (subtypeOfStorageSlotP(safePrimaryType(slot))) {
        { Slot* slot000 = slot;
          StorageSlot* slot = ((StorageSlot*)(slot000));

          if ((translateToSingleInheritanceLanguageP() &&
              ((!translateToSingleInheritanceLanguageP()) ||
               (!(oMIXIN_IMPLEMENTATION_STYLEo == KWD_WALK_SECOND_CLASS)))) &&
              clasS->mixinP) {
            createAccessorUnitsForMixinSlot(slot, clasS);
          }
          else {
            createAccessorUnitsForSlot(slot, clasS, false, slot->slotExternalP);
          }
        }
      }
      else {
      }
    }
  }
  { boolean testValue000 = false;

    testValue000 = translateToSingleInheritanceLanguageP();
    if (testValue000) {
      { boolean foundP000 = false;

        { Surrogate* super = NULL;
          Cons* iter001 = clasS->classDirectSupers->theConsList;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            super = ((Surrogate*)(iter001->value));
            if (((Class*)(super->surrogateValue))->mixinP) {
              foundP000 = true;
              break;
            }
          }
        }
        testValue000 = foundP000;
      }
    }
    if (testValue000) {
      { Slot* slot = NULL;
        Iterator* iter002 = clasS->classSlots();

        for (; iter002->nextP(); ) {
          slot = ((Slot*)(iter002->value));
          if (mixinSlotP(slot) &&
              (nativeSlotHome(slot, clasS) == clasS)) {
            createAccessorUnitsForSlot(((StorageSlot*)(slot)), clasS, translateToSingleInheritanceLanguageP() &&
                ((!translateToSingleInheritanceLanguageP()) ||
                 (!(oMIXIN_IMPLEMENTATION_STYLEo == KWD_WALK_SECOND_CLASS))), slot->slotExternalP);
          }
        }
      }
    }
  }
  createGenericSlotAccessorUnit(clasS);
}

void createInlineMethodUnits(Class* clasS) {
  { Slot* slot = NULL;
    Cons* iter000 = clasS->localSlots()->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      slot = ((Slot*)(iter000->value));
      if (inlineMethodP(slot)) {
        { Object* name = NULL;
          Cons* parameters = NULL;
          Cons* body = NULL;

          name = destructureDefmethodTree(((Cons*)(unstringifyStellaSource(((MethodSlot*)(slot))->methodStringifiedSource, slot->homeModule()))), NULL, parameters, body);
          {
            name = name;
            parameters = parameters;
          }
          { TranslationUnit* self000 = newTranslationUnit();

            self000->theObject = slot;
            self000->category = SYM_WALK_STELLA_METHOD;
            self000->codeRegister = body;
            self000->auxiliaryP = true;
            self000->tuHomeModule = oMODULEo;
            walkMethodUnit(self000);
          }
        }
      }
    }
  }
}

Cons* yieldMixinMethodTree(MethodSlot* method, Class* clasS) {
  { Cons* tree = ((Cons*)(unstringifyStellaSource(method->methodStringifiedSource, method->homeModule())));
    Cons* parameters = ((Cons*)(tree->rest->rest->value));
    Cons* selftree = ((Cons*)(parameters->value));
    Object* selftypetree = yieldTypeSpecTree(((StandardObject*)(method->methodParameterTypeSpecifiers_reader()->first())));
    Cons* body = tree->nthRest(3);

    if (safePrimaryType(selftypetree) == SGT_WALK_STELLA_CONS) {
      { Object* selftypetree000 = selftypetree;
        Cons* selftypetree = ((Cons*)(selftypetree000));

        selftypetree->firstSetter(yieldTypeSpecTree(clasS->classType));
      }
    }
    else {
      selftypetree = yieldTypeSpecTree(clasS->classType);
    }
    lastCons(selftree)->firstSetter(selftypetree);
    if (clasS == ((Class*)(SGT_WALK_STELLA_OBJECT->surrogateValue))) {
      body = extractOptions(tree, NULL)->concatenate(cons(SYM_WALK_STELLA_NULL, NIL), 0);
    }
    return (listO(3, SYM_WALK_STELLA_DEFMETHOD, tree->rest->value, cons(parameters, listO(5, KWD_WALK_AUXILIARYp, SYM_WALK_STELLA_TRUE, KWD_WALK_PUBLICp, (method->slotPublicP ? SYM_WALK_STELLA_TRUE : SYM_WALK_STELLA_FALSE), body->concatenate(NIL, 0)))));
  }
}

void createMixinMethodUnits(Class* clasS) {
  if (clasS->mixinP &&
      ((!translateToSingleInheritanceLanguageP()) ||
       (!(oMIXIN_IMPLEMENTATION_STYLEo == KWD_WALK_SECOND_CLASS)))) {
    { Slot* slot = NULL;
      Cons* iter000 = clasS->classLocalSlots->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        slot = ((Slot*)(iter000->value));
        if (methodSlotP(slot)) {
          registerAuxiliaryMethod(((MethodSlot*)(helpWalkAuxiliaryTree(yieldMixinMethodTree(((MethodSlot*)(slot)), ((Class*)(SGT_WALK_STELLA_OBJECT->surrogateValue))), true)->theObject)), slot);
        }
      }
    }
  }
  else {
    { List* mixinmethods = newList();
      List* supermethods = newList();

      { Surrogate* super = NULL;
        Cons* iter001 = clasS->classDirectSupers->theConsList;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          super = ((Surrogate*)(iter001->value));
          if (((Class*)(super->surrogateValue))->mixinP) {
            { Slot* slot = NULL;
              Iterator* iter002 = ((Class*)(super->surrogateValue))->classSlots();

              for (; iter002->nextP(); ) {
                slot = ((Slot*)(iter002->value));
                if (methodSlotP(slot) &&
                    (nativeSlotHome(slot, clasS) == clasS)) {
                  if (((boolean)(slot->slotDirectEquivalent))) {
                    supermethods->insertNew(((MethodSlot*)(slot->slotDirectEquivalent)));
                  }
                  if (!(supermethods->memberP(slot))) {
                    mixinmethods->insertNew(((MethodSlot*)(slot)));
                  }
                }
              }
            }
          }
        }
      }
      { MethodSlot* method = NULL;
        Cons* iter003 = mixinmethods->reverse()->theConsList;

        for (; !(iter003 == NIL); iter003 = iter003->rest) {
          method = ((MethodSlot*)(iter003->value));
          registerAuxiliaryMethod(((MethodSlot*)(helpWalkAuxiliaryTree(yieldMixinMethodTree(method, clasS), true)->theObject)), method);
        }
      }
    }
  }
}

void createDefprintUnit(Class* clasS) {
  { StandardObject* dummy1;
    StandardObject* dummy2;

    if (!(!((boolean)(dynamicSlotValue(clasS->dynamicSlots, SYM_WALK_STELLA_PRINT_FORM, NULL))))) {
      walkAuxiliaryTree(listO(7, SYM_WALK_STELLA_DEFMETHOD, SYM_WALK_STELLA_PRINT_OBJECT, listO(3, listO(3, SYM_WALK_STELLA_SELF, clasS->classType, NIL), listO(3, SYM_WALK_STELLA_STREAM, SYM_WALK_STELLA_NATIVE_OUTPUT_STREAM, NIL), NIL), KWD_WALK_PUBLICp, SYM_WALK_STELLA_TRUE, copyConsTree(dynamicSlotValue(clasS->dynamicSlots, SYM_WALK_STELLA_PRINT_FORM, NULL)), NIL));
      { boolean testValue000 = false;

        testValue000 = oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP;
        if (testValue000) {
          { boolean foundP000 = false;

            { Class* super = NULL;
              Cons* iter000 = clasS->classAllSuperClasses;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                super = ((Class*)(iter000->value));
                if (((boolean)(dynamicSlotValue(super->dynamicSlots, SYM_WALK_STELLA_PRINT_FORM, NULL)))) {
                  foundP000 = true;
                  break;
                }
              }
            }
            testValue000 = foundP000;
          }
          testValue000 = !testValue000;
        }
        if (testValue000) {
          pushVariableBinding(SYM_WALK_STELLA_SELF, clasS->classType);
          pushVariableBinding(SYM_WALK_STELLA_STREAM, SGT_WALK_STELLA_NATIVE_OUTPUT_STREAM);
          { TranslationUnit* self000 = newTranslationUnit();

            self000->theObject = clasS;
            self000->category = SYM_WALK_STELLA_PRINT_METHOD;
            self000->tuHomeModule = oMODULEo;
            self000->codeRegister = walkATree(listO(5, SYM_WALK_STELLA_IF, listO(3, SYM_WALK_STELLA_NULLp, SYM_WALK_STELLA_SELF, NIL), listO(4, SYM_WALK_STELLA_PRINT_NATIVE_STREAM, SYM_WALK_STELLA_STREAM, wrapString("!NULL!"), NIL), listO(4, SYM_WALK_STELLA_PRINT_OBJECT, SYM_WALK_STELLA_SELF, SYM_WALK_STELLA_STREAM, NIL), NIL), dummy1);
            self000->auxiliaryP = true;
            oTRANSLATIONUNITSo->push(self000);
          }
          popVariableBinding();
          popVariableBinding();
        }
      }
      { boolean testValue001 = false;

        testValue001 = oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA;
        if (testValue001) {
          { boolean foundP001 = false;

            { Class* super = NULL;
              Cons* iter001 = clasS->classAllSuperClasses;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                super = ((Class*)(iter001->value));
                if (((boolean)(dynamicSlotValue(super->dynamicSlots, SYM_WALK_STELLA_PRINT_FORM, NULL)))) {
                  foundP001 = true;
                  break;
                }
              }
            }
            testValue001 = foundP001;
          }
          testValue001 = !testValue001;
        }
        if (testValue001) {
          { 
            BIND_STELLA_SPECIAL(oMETHODBEINGWALKEDo, MethodSlot*, newMethodSlot());
            oMETHODBEINGWALKEDo->methodReturnTypeSpecifiers = list(1, SGT_WALK_STELLA_STRING);
            pushVariableBinding(SYM_WALK_STELLA_SELF, clasS->classType);
            { TranslationUnit* self002 = newTranslationUnit();

              self002->theObject = clasS;
              self002->category = SYM_WALK_STELLA_PRINT_METHOD;
              self002->tuHomeModule = oMODULEo;
              self002->codeRegister = walkATree(listO(5, SYM_WALK_STELLA_IF, listO(3, SYM_WALK_STELLA_NULLp, SYM_WALK_STELLA_SELF, NIL), listO(3, SYM_WALK_STELLA_RETURN, wrapString("!NULL!"), NIL), listO(3, SYM_WALK_STELLA_RETURN, listO(4, SYM_WALK_STELLA_VERBATIM, KWD_WALK_JAVA, wrapString("#$(STELLAROOT).javalib.Native.stringify_via_print(self)"), NIL), NIL), NIL), dummy2);
              self002->auxiliaryP = true;
              oTRANSLATIONUNITSo->push(self002);
            }
            popVariableBinding();
          }
        }
      }
    }
  }
}

void walkClassUnit(TranslationUnit* unit) {
  { Class* clasS = ((Class*)(unit->theObject));
    Cons* startuptimecode = NULL;

    if (!clasS->classFinalizedP) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Cannot translate class " << "`" << classSymbol(clasS) << "'" << ", since it could not be finalized" << "." << std::endl;
        }
      }
      clearTranslationUnit(unit);
      return;
    }
    if (createNativeClassP(clasS)) {
      warnAboutMultipleParents(clasS);
      warnAboutNonDirectSupers(clasS);
      cleanupAuxiliaryMethods(clasS);
      if (!(clasS->mixinP &&
          translateToSingleInheritanceLanguageP())) {
        oTRANSLATIONUNITSo->push(unit);
        createConstructorAndDestructorUnits(clasS);
        createInlineMethodUnits(clasS);
      }
      createSlotAccessorUnits(clasS);
      if (translateToSingleInheritanceLanguageP()) {
        createMixinMethodUnits(clasS);
      }
      { Slot* slot = NULL;
        Cons* iter000 = clasS->classLocalSlots->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          slot = ((Slot*)(iter000->value));
          if (storageSlotP(slot) &&
              (nativeSlotP(((StorageSlot*)(slot))) &&
               ((nativeSlotHome(slot, clasS) == clasS) &&
                ((!(clasS->homeModule() == slot->homeModule())) &&
                 slotNameConflictP(slot, clasS))))) {
            if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_COMMON_LISP) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationWarning();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> WARNING: ", STANDARD_WARNING);
                  *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Defining slot " << "`" << deUglifyParseTree(slot) << "'" << " outside the home module of" << std::endl << "   its owner class will be illegal in C++ and Java" << "." << std::endl;
                }
              }
            }
            else {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Slot " << "`" << deUglifyParseTree(slot) << "'" << " is defined outside the home module of " << std::endl << "   its owner class " << "`" << deUglifyParseTree(clasS) << "'" << ", and the name of" << std::endl << "   the slot conflicts with another slot." << "." << std::endl;
                }
              }
              while (!(((TranslationUnit*)(oTRANSLATIONUNITSo->pop())) == unit)) {
              }
              clearTranslationUnit(unit);
              return;
            }
          }
        }
      }
    }
    createDefprintUnit(clasS);
    startuptimecode = yieldInitializeHardwiredSlots(clasS)->concatenate(yieldConstructorAttachment(clasS, SYM_WALK_STELLA_CLASS)->concatenate(yieldGenericSlotAccessorAttachment(clasS, SYM_WALK_STELLA_CLASS)->concatenate(NIL, 0), 0), 0);
    walkAuxiliaryTree(((startuptimecode == NIL) ? listO(4, SYM_WALK_STELLA_STARTUP_TIME_PROGN, KWD_WALK_CLASSES, yieldDefineStellaClass(clasS), NIL) : listO(4, SYM_WALK_STELLA_STARTUP_TIME_PROGN, KWD_WALK_CLASSES, listO(3, SYM_WALK_STELLA_LET, cons(listO(3, SYM_WALK_STELLA_CLASS, yieldDefineStellaClass(clasS), NIL), NIL), startuptimecode->concatenate(NIL, 0)), NIL)));
    { Surrogate* synonym = NULL;
      Cons* iter001 = clasS->classSynonyms_reader()->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        synonym = ((Surrogate*)(iter001->value));
        registerSymbol(internSymbolInModule(synonym->symbolName, ((Module*)(synonym->homeContext)), true));
      }
    }
  }
}

void createFinalizationUnits() {
  walkAuxiliaryTree(listO(4, SYM_WALK_STELLA_STARTUP_TIME_PROGN, KWD_WALK_FINALIZE_CLASSES, cons(SYM_WALK_STELLA_FINALIZE_CLASSES, NIL), NIL));
  walkAuxiliaryTree(listO(5, SYM_WALK_STELLA_STARTUP_TIME_PROGN, KWD_WALK_FINALIZE_METHODS, cons(SYM_WALK_STELLA_FINALIZE_SLOTS, NIL), cons(SYM_WALK_STELLA_CLEANUP_UNFINALIZED_CLASSES, NIL), NIL));
}

void walkDefslotTree(Cons* tree) {
  { TranslationUnit* self000 = newTranslationUnit();

    self000->category = SYM_WALK_STELLA_SLOT;
    self000->theObject = tree;
    self000->tuHomeModule = oMODULEo;
    oCURRENTTRANSLATIONUNITo = self000;
  }
  { StorageSlot* slot = NULL;

    slot = defineExternalSlotFromParseTree(tree);
    if (!((boolean)(slot))) {
      clearTranslationUnit(oCURRENTTRANSLATIONUNITo);
      oCURRENTTRANSLATIONUNITo = NULL;
      return;
    }
    oCURRENTTRANSLATIONUNITo->theObject = slot;
    oCURRENTTRANSLATIONUNITo->codeRegister = tree;
  }
}

void walkSlotUnit(TranslationUnit* unit) {
  { StorageSlot* slot = ((StorageSlot*)(unit->theObject));
    Class* ownerclass = ((Class*)(slot->slotOwner->surrogateValue));
    const char* stringifieddefinition = stringify(unit->codeRegister);

    createAccessorUnitsForSlot(slot, ownerclass, false, false);
    clearTranslationUnit(unit);
    walkAuxiliaryTree(listO(4, SYM_WALK_STELLA_STARTUP_TIME_PROGN, KWD_WALK_METHODS, listO(3, SYM_WALK_STELLA_DEFINE_EXTERNAL_SLOT_FROM_STRINGIFIED_SOURCE, wrapString(stringifieddefinition), NIL), NIL));
  }
}

MethodSlot* lookupMacro(Symbol* name) {
  // If `name' has a macro definition, return the method object
  // holding its expander function.
  { MethodSlot* function = lookupFunction(name);

    if (((boolean)(function)) &&
        ((BooleanWrapper*)(dynamicSlotValue(function->dynamicSlots, SYM_WALK_STELLA_METHOD_MACROp, FALSE_WRAPPER)))->wrapperValue) {
      return (function);
    }
    return (NULL);
  }
}

void walkDefmacroTree(Cons* tree) {
  { Object* name = tree->rest->value;

    { PropertyList* self000 = newPropertyList();

      self000->thePlist = extractOptions(tree, NULL);
      { PropertyList* options = self000;
        MethodSlot* method = NULL;

        if (consP(name)) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Macro " << "`" << ((Cons*)(name))->value << "'" << " contains return type specification" << "." << std::endl;
            }
          }
          return;
        }
        if (!(symbolP(name))) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal macro name: " << "`" << deUglifyParseTree(name) << "'" << "." << std::endl;
            }
          }
          return;
        }
        tree->firstSetter(SYM_WALK_STELLA_DEFUN);
        options->insertAt(KWD_WALK_MACROp, SYM_WALK_STELLA_TRUE);
        options->insertAt(KWD_WALK_TYPE, SYM_WALK_STELLA_OBJECT);
        tree->rest->rest->rest = options->thePlist->concatenate(tree->rest->rest->rest, 0);
        walkDefmethodTree(tree);
        if (((boolean)(oCURRENTTRANSLATIONUNITo))) {
          method = ((MethodSlot*)(oCURRENTTRANSLATIONUNITo->theObject));
          if (method->methodArgumentCount() > 5) {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Too many arguments in macro definition, maximum is 5" << "." << std::endl;
              }
            }
            oCURRENTTRANSLATIONUNITo = NULL;
          }
        }
      }
    }
  }
}

void walkDefglobalTree(Cons* tree) {
  { TranslationUnit* self000 = newTranslationUnit();

    self000->category = SYM_WALK_STELLA_GLOBAL_VARIABLE;
    self000->theObject = tree;
    self000->tuHomeModule = oMODULEo;
    oCURRENTTRANSLATIONUNITo = self000;
  }
  if (tree->length() < 3) {
    badArgumentCountP(tree, 3);
    clearTranslationUnit(oCURRENTTRANSLATIONUNITo);
    oCURRENTTRANSLATIONUNITo = NULL;
    return;
  }
  { GlobalVariable* global = NULL;
    Object* initialvaluetree = NULL;

    global = defineStellaGlobalVariableFromParseTree(tree, stringify(tree), initialvaluetree);
    oCURRENTTRANSLATIONUNITo->theObject = global;
    oCURRENTTRANSLATIONUNITo->codeRegister = initialvaluetree;
    oCURRENTTRANSLATIONUNITo->auxiliaryP = global->variableAuxiliaryP;
  }
}

void walkGlobalUnit(TranslationUnit* unit) {
  { StandardObject* dummy1;

    { GlobalVariable* global = ((GlobalVariable*)(unit->theObject));
      Object* initialvaluetree = unit->codeRegister;
      const char* stringifiedsource = global->variableStringifiedSource;

      oTRANSLATIONUNITSo->push(unit);
      if (!(initialvaluetree == KWD_WALK_UNBOUND_SPECIAL_VARIABLE)) {
        if (global->variableSpecialP &&
            (translateToJavaP() ||
             supportUnexecP())) {
          global->variableConstantP = false;
          walkAuxiliaryTree(listO(4, SYM_WALK_STELLA_STARTUP_TIME_PROGN, KWD_WALK_GLOBALS, listO(3, SYM_WALK_STELLA_SYS_SET_DEFAULT, global->variableName, cons(initialvaluetree, NIL)), NIL));
          initialvaluetree = KWD_WALK_UNBOUND_SPECIAL_VARIABLE;
        }
        else if (wrapperP(initialvaluetree) ||
            ((symbolP(initialvaluetree) &&
            (constantSymbolP(((Symbol*)(initialvaluetree))) &&
             ((!(initialvaluetree == SYM_WALK_STELLA_NULL)) ||
              (typeToNullValueTree(global->variableType) == SYM_WALK_STELLA_NULL)))) ||
             (consP(initialvaluetree) &&
              (((Cons*)(initialvaluetree))->value == SYM_WALK_STELLA_VERBATIM)))) {
          initialvaluetree = walkExpressionTree(initialvaluetree, globalVariableTypeSpec(global), global->variableName, true, dummy1);
        }
        else {
          global->variableConstantP = false;
          walkAuxiliaryTree(listO(4, SYM_WALK_STELLA_STARTUP_TIME_PROGN, KWD_WALK_GLOBALS, listO(3, SYM_WALK_STELLA_SETQ, global->variableName, cons(initialvaluetree, NIL)), NIL));
          if (supportUnexecP()) {
            initialvaluetree = KWD_WALK_UNBOUND_SPECIAL_VARIABLE;
          }
          else {
            initialvaluetree = typeToWalkedNullValueTree(globalVariableTypeSpec(global), typeSpecToBaseType(global->variableType));
          }
        }
      }
      unit->codeRegister = initialvaluetree;
      if (!(unit->auxiliaryP)) {
        walkAuxiliaryTree(listO(3, SYM_WALK_STELLA_STARTUP_TIME_PROGN, listO(3, SYM_WALK_STELLA_DEFINE_GLOBAL_VARIABLE_OBJECT, wrapString(stringifiedsource), cons(((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP) ? ((StandardObject*)(listO(4, SYM_WALK_STELLA_VERBATIM, KWD_WALK_CPP, cppTranslateGlobalVariableAddress(global), NIL))) : ((StandardObject*)(SYM_WALK_STELLA_NULL))), NIL)), NIL));
      }
    }
  }
}

void walkDeftypeTree(Cons* tree) {
  { TranslationUnit* self000 = newTranslationUnit();

    self000->category = SYM_WALK_STELLA_TYPE;
    self000->theObject = tree;
    self000->tuHomeModule = oMODULEo;
    oCURRENTTRANSLATIONUNITo = self000;
  }
  if (tree->length() < 3) {
    badArgumentCountP(tree, 3);
    clearTranslationUnit(oCURRENTTRANSLATIONUNITo);
    oCURRENTTRANSLATIONUNITo = NULL;
    return;
  }
  { Surrogate* type = NULL;

    type = defineStellaTypeFromParseTree(tree);
    oCURRENTTRANSLATIONUNITo->theObject = type;
    oCURRENTTRANSLATIONUNITo->codeRegister = tree;
  }
}

void walkTypeUnit(TranslationUnit* unit) {
  { const char* stringifieddefinition = stringify(unit->codeRegister);

    oTRANSLATIONUNITSo->push(unit);
    walkAuxiliaryTree(listO(4, SYM_WALK_STELLA_STARTUP_TIME_PROGN, KWD_WALK_CLASSES, listO(3, SYM_WALK_STELLA_DEFINE_STELLA_TYPE_FROM_STRINGIFIED_SOURCE, wrapString(stringifieddefinition), NIL), NIL));
    registerSymbol(internSymbolInModule(((Surrogate*)(unit->theObject))->symbolName, ((Module*)(((Surrogate*)(unit->theObject))->homeContext)), true));
  }
}

void walkStartupTimePrognTree(Cons* tree) {
  { TranslationUnit* self000 = newTranslationUnit();

    self000->category = SYM_WALK_STELLA_STARTUP_TIME_PROGN;
    self000->tuHomeModule = oMODULEo;
    self000->codeRegister = tree;
    oCURRENTTRANSLATIONUNITo = self000;
  }
}

Keyword* extractStartupTimePhase(Cons* tree) {
  { Keyword* startuptimephase = KWD_WALK_FINAL;
    Cons* startuptimephasetree = NULL;

    if ((tree->length() >= 2) &&
        (keywordP(tree->rest->value) &&
         oSTARTUP_TIME_PHASESo->memberP(tree->rest->value))) {
      startuptimephase = ((Keyword*)(tree->rest->value));
      startuptimephasetree = tree->rest;
      tree->rest = tree->rest->rest;
      startuptimephasetree->rest = NIL;
    }
    return (startuptimephase);
  }
}

void walkStartupTimePrognUnit(TranslationUnit* unit) {
  { Cons* tree = ((Cons*)(unit->codeRegister));
    Keyword* phase = extractStartupTimePhase(tree);

    oTRANSLATIONUNITSo->push(unit);
    unit->theObject = walkListOfStatements(tree->rest);
    unit->codeRegister = phase;
  }
}

// The maximum number of startup units that can be combined
// into a single startup function (this avoids the construction of huge startup
// functions that would cause too much stress for some wimpy compilers).
int oMAX_NUMBER_OF_STARTUP_UNITSo = 60;

boolean earlierStartupUnitP(TranslationUnit* unit1, TranslationUnit* unit2) {
  return (encodeStartupTimePhase(((Keyword*)(unit1->codeRegister))) < encodeStartupTimePhase(((Keyword*)(unit2->codeRegister))));
}

Cons* combineStartupFunctionUnits(Symbol* startupfnname) {
  { Cons* earlystartuptrees = NIL;
    Cons* startuptrees = NIL;
    Cons* startupphasetrees = NIL;
    List* startupunits = newList();

    { ListIterator* it = ((ListIterator*)(oTRANSLATIONUNITSo->allocateIterator()));

      for (; it->nextP(); ) {
        if (((TranslationUnit*)(it->value))->category == SYM_WALK_STELLA_STARTUP_TIME_PROGN) {
          startupunits->push(((TranslationUnit*)(it->value)));
          it->valueSetter(NULL);
        }
      }
    }
    oTRANSLATIONUNITSo->remove(NULL);
    startupunits->sort(((cpp_function_code)(&earlierStartupUnitP)));
    if (((boolean)(startupfnname)) &&
        (startupunits->length() > oMAX_NUMBER_OF_STARTUP_UNITSo)) {
      extractStartupFunctionUnits(startupunits, startupfnname);
    }
    { Keyword* phase = NULL;
      Cons* iter000 = oSTARTUP_TIME_PHASESo->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        phase = ((Keyword*)(iter000->value));
        while (startupunits->nonEmptyP() &&
            (((TranslationUnit*)(startupunits->first()))->codeRegister == phase)) {
          startupphasetrees = startupphasetrees->concatenate(((Cons*)(((TranslationUnit*)(startupunits->first()))->theObject)), 0);
          clearTranslationUnit(((TranslationUnit*)(startupunits->pop())));
        }
        if (!(startupphasetrees == NIL)) {
          startupphasetrees = listO(3, SYM_WALK_STELLA_VOID_SYS, listO(3, SYM_WALK_STELLA_WHEN, listO(4, SYM_WALK_STELLA_SYS_CALL_FUNCTION, SYM_WALK_STELLA_CURRENT_STARTUP_TIME_PHASEp, wrapInteger(encodeStartupTimePhase(phase)), NIL), startupphasetrees->concatenate(NIL, 0)), NIL);
          if (encodeStartupTimePhase(phase) <= encodeStartupTimePhase(KWD_WALK_MODULES)) {
            earlystartuptrees = cons(startupphasetrees, earlystartuptrees);
          }
          else {
            startuptrees = cons(startupphasetrees, startuptrees);
          }
          startupphasetrees = NIL;
        }
      }
    }
    if (!(startuptrees == NIL)) {
      startuptrees = cons(listO(3, SYM_WALK_STELLA_WITHIN_MODULE, ((oMODULEo == oSTELLA_MODULEo) ? ((StandardObject*)(SYM_WALK_STELLA_oSTELLA_MODULEo)) : ((StandardObject*)(listO(3, SYM_WALK_STELLA_GET_STELLA_MODULE, wrapString(oMODULEo->moduleFullName), cons(listO(4, SYM_WALK_STELLA_g, SYM_WALK_STELLA_oSTARTUP_TIME_PHASEo, wrapInteger(encodeStartupTimePhase(KWD_WALK_MODULES)), NIL), NIL))))), startuptrees->reverse()->concatenate(NIL, 0)), NIL);
    }
    if ((!(earlystartuptrees == NIL)) ||
        (!(startuptrees == NIL))) {
      startuptrees = earlystartuptrees->reverse()->concatenate(startuptrees, 0);
    }
    return (startuptrees);
  }
}

boolean MethodSlot::methodStartupFunctionP() {
  { MethodSlot* method = this;

    return (((StringWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_STARTUP_CLASSNAME, NULL_STRING_WRAPPER)))->wrapperValue != NULL);
  }
}

void extractStartupFunctionUnits(List* startupunits, Symbol* startupfnname) {
  { int remainingunits = startupunits->length();
    int minunitsperfunction = stella::floor((((double)(oMAX_NUMBER_OF_STARTUP_UNITSo)) / oSTARTUP_TIME_PHASESo->length()) + 1);
    Cons* cursor = startupunits->theConsList;
    Cons* phasestart = cursor;
    int phaseunits = 0;
    Keyword* phase = ((Keyword*)(((TranslationUnit*)(cursor->value))->codeRegister));
    Keyword* unitphase = phase;
    int helpfncounter = 0;

    while (!(cursor == NIL)) {
      unitphase = ((Keyword*)(((TranslationUnit*)(cursor->value))->codeRegister));
      if (unitphase == phase) {
        phaseunits = phaseunits + 1;
        if (phaseunits < oMAX_NUMBER_OF_STARTUP_UNITSo) {
          cursor = cursor->rest;
          continue;
        }
      }
      if (phaseunits < minunitsperfunction) {
        phasestart = cursor;
        phaseunits = 0;
        phase = unitphase;
        continue;
      }
      { Symbol* functionname = internDerivedSymbol(startupfnname, stringConcatenate("HELP-", stringConcatenate(startupfnname->symbolName, integerToString(((long long int)(helpfncounter = helpfncounter + 1))), 0), 0));
        Cons* helpfntree = ((Cons*)(((TranslationUnit*)(phasestart->value))->theObject));

        ((TranslationUnit*)(phasestart->value))->theObject = cons(listO(3, SYM_WALK_STELLA_SYS_CALL_FUNCTION, functionname, NIL), NIL);
        phasestart = phasestart->rest;
        { ConsIterator* it = phasestart->allocateIterator();
          int i = NULL_INTEGER;
          int iter000 = 2;
          int upperBound000 = phaseunits;
          boolean unboundedP000 = upperBound000 == NULL_INTEGER;

          for  (; it->nextP() &&
                    (unboundedP000 ||
                     (iter000 <= upperBound000)); 
                iter000 = iter000 + 1) {
            i = iter000;
            i = i;
            helpfntree = helpfntree->concatenate(((Cons*)(((TranslationUnit*)(it->value))->theObject)), 0);
            clearTranslationUnit(((TranslationUnit*)(it->value)));
            it->valueSetter(NULL);
          }
        }
        helpfntree = listO(3, SYM_WALK_STELLA_DEFUN, functionname, listO(5, NIL, KWD_WALK_PUBLICp, SYM_WALK_STELLA_FALSE, listO(3, SYM_WALK_STELLA_VOID_SYS, cons(SYM_WALK_STELLA_PROGN, helpfntree->concatenate(NIL, 0)), NIL), NIL));
        setDynamicSlotValue(((MethodSlot*)(helpWalkAuxiliaryTree(helpfntree, true)->theObject))->dynamicSlots, SYM_WALK_STELLA_METHOD_STARTUP_CLASSNAME, wrapString(yieldStartupFunctionClassname(startupfnname)), NULL_STRING_WRAPPER);
        remainingunits = remainingunits - (phaseunits - 1);
        if (remainingunits <= oMAX_NUMBER_OF_STARTUP_UNITSo) {
          break;
        }
        if (unitphase == phase) {
          cursor = cursor->rest;
        }
        phasestart = cursor;
        phaseunits = 0;
        phase = ((Keyword*)(((TranslationUnit*)(cursor->value))->codeRegister));
      }
    }
    startupunits->remove(NULL);
  }
}

Symbol* yieldStartupFunctionName(const char* file) {
  file = ((file == NULL) ? oCURRENTFILENAMEo : file);
  if (systemStartupFileP(file)) {
    return (systemStartupFunctionSymbol(oCURRENTSYSTEMDEFINITIONo));
  }
  else {
    return (internSymbolInModule(stringConcatenate("STARTUP-", stringUpcase(fileBaseName(file)), 0), oMODULEo, true));
  }
}

const char* yieldStartupFunctionClassname(Symbol* functionName) {
  { StringWrapper* baseName = javaTranslateClassNamestring(wrapString(functionName->symbolName));

    if (systemStartupFileP(oCURRENTFILENAMEo)) {
      return (baseName->wrapperValue);
    }
    else {
      return (stringConcatenate("_", baseName->wrapperValue, 0));
    }
  }
}

void createStartupFunctionUnits() {
  { Symbol* startupfnname = (incrementalTranslationP() ? ((Symbol*)(NULL)) : yieldStartupFunctionName(oCURRENTFILENAMEo));
    boolean systemstartupP = systemStartupFileP(oCURRENTFILENAMEo);
    Cons* options = (systemstartupP ? listO(7, KWD_WALK_PUBLICp, SYM_WALK_STELLA_TRUE, KWD_WALK_C_CALLABLEp, SYM_WALK_STELLA_TRUE, KWD_WALK_C_NAMESPACE_PREFIX, wrapString("stella_"), NIL) : listO(3, KWD_WALK_PUBLICp, SYM_WALK_STELLA_TRUE, NIL));
    Cons* tree = NULL;
    MethodSlot* method = NULL;

    if (dontGenerateStartupCodeP()) {
      removeAllStartupTimePrognUnits();
    }
    else if (((boolean)(startupfnname))) {
      tree = listO(3, SYM_WALK_STELLA_DEFUN, startupfnname, cons(NIL, options->concatenate(cons(SYM_WALK_STELLA_NULL, NIL), 0)));
      method = defineMethodFromParseTree(tree);
      setDynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_FORWARD_DECLARATIONp, FALSE_WRAPPER, FALSE_WRAPPER);
      setDynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_STARTUP_CLASSNAME, wrapString(yieldStartupFunctionClassname(startupfnname)), NULL_STRING_WRAPPER);
      tree = listO(4, SYM_WALK_STELLA_STARTUP_TIME_PROGN, KWD_WALK_METHODS, yieldDefineStellaMethodObject(method, method, NULL), cons(listO(4, SYM_WALK_STELLA_LET, cons(listO(3, SYM_WALK_STELLA_FUNCTION, listO(3, SYM_WALK_STELLA_LOOKUP_FUNCTION, listO(3, SYM_WALK_STELLA_QUOTE, startupfnname, NIL), NIL), NIL), NIL), listO(4, SYM_WALK_STELLA_SETF, listO(3, SYM_WALK_STELLA_METHOD_STARTUP_CLASSNAME, SYM_WALK_STELLA_FUNCTION, NIL), wrapString(((StringWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_STARTUP_CLASSNAME, NULL_STRING_WRAPPER)))->wrapperValue), NIL), NIL), NIL));
      walkAuxiliaryTree(tree);
      if (systemstartupP) {
        tree = listO(3, SYM_WALK_STELLA_DEFUN, startupfnname, listO(7, NIL, KWD_WALK_PUBLICp, SYM_WALK_STELLA_TRUE, KWD_WALK_AUXILIARYp, SYM_WALK_STELLA_TRUE, listO(3, SYM_WALK_STELLA_WITH_PROCESS_LOCK, SYM_WALK_STELLA_oBOOTSTRAP_LOCKo, combineStartupFunctionUnits(startupfnname)->concatenate(NIL, 0)), NIL));
      }
      else {
        tree = listO(3, SYM_WALK_STELLA_DEFUN, startupfnname, listO(6, NIL, KWD_WALK_PUBLICp, SYM_WALK_STELLA_TRUE, KWD_WALK_AUXILIARYp, SYM_WALK_STELLA_TRUE, combineStartupFunctionUnits(startupfnname)->concatenate(NIL, 0)));
      }
      setDynamicSlotValue(((MethodSlot*)(helpWalkAuxiliaryTree(tree, true)->theObject))->dynamicSlots, SYM_WALK_STELLA_METHOD_STARTUP_CLASSNAME, wrapString(yieldStartupFunctionClassname(startupfnname)), NULL_STRING_WRAPPER);
      if (methodNeedsCCallableWrapperP(method)) {
        createCCallableWrapperUnit(method);
      }
    }
    else {
      tree = cons(SYM_WALK_STELLA_STARTUP_TIME_PROGN, combineStartupFunctionUnits(startupfnname)->concatenate(NIL, 0));
      walkAuxiliaryTree(tree);
      tree = cons(SYM_WALK_STELLA_PROGN, ((Cons*)(((TranslationUnit*)(oTRANSLATIONUNITSo->first()))->theObject)));
      ((TranslationUnit*)(oTRANSLATIONUNITSo->first()))->theObject = tree;
    }
  }
}

boolean dontGenerateStartupCodeP() {
  return (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP_STANDALONE);
}

void removeAllStartupTimePrognUnits() {
  { TranslationUnit* placeholderunit = NULL;

    { ListIterator* it = ((ListIterator*)(oTRANSLATIONUNITSo->allocateIterator()));

      for (; it->nextP(); ) {
        if (((TranslationUnit*)(it->value))->category == SYM_WALK_STELLA_STARTUP_TIME_PROGN) {
          { TranslationUnit* unit = ((TranslationUnit*)(it->value));

            if (!((boolean)(placeholderunit))) {
              placeholderunit = unit;
            }
            else {
              clearTranslationUnit(unit);
            }
            it->valueSetter(placeholderunit);
          }
        }
      }
    }
    oTRANSLATIONUNITSo->remove(placeholderunit);
    clearTranslationUnit(placeholderunit);
  }
}

Cons* walkSignalExceptionTree(Cons* tree, StandardObject*& _Return1) {
  oFOUNDRETURNpo = true;
  { Object* expression = NULL;
    StandardObject* itsType = NULL;

    expression = walkExpressionTree(tree->rest->value, SGT_WALK_STELLA_STELLA_ROOT_EXCEPTION, SYM_WALK_STELLA_SIGNAL_EXCEPTION, false, itsType);
    { Cons* _Return0 = listO(3, SYM_WALK_STELLA_SYS_SIGNAL, expression, cons(itsType, NIL));

      _Return1 = SGT_WALK_STELLA_VOID;
      return (_Return0);
    }
  }
}

Cons* walkExceptionCaseTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;
    StandardObject* dummy2;

    if (tree->length() <= 2) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing handler(s) in 'exception-case': " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
        }
      }
      return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
    }
    { Object* protectedtree = walkATree(tree->rest->value, dummy1);
      Cons* handlertrees = walkExceptionHandlerTrees(tree->rest->rest);

      if ((!((boolean)(protectedtree))) ||
          (!((boolean)(handlertrees)))) {
        return (walkDontCallMeTree(tree, SGT_WALK_STELLA_VOID, _Return1));
      }
      { Cons* _Return0 = listO(3, SYM_WALK_STELLA_SYS_HANDLER_CASE, walkATree(protectedtree, dummy2), handlertrees->concatenate(NIL, 0));

        _Return1 = SGT_WALK_STELLA_VOID;
        return (_Return0);
      }
    }
  }
}

Cons* walkExceptionHandlerTrees(Cons* tree) {
  { Cons* clauses = NIL;
    Object* exceptiontype = NULL;
    Object* exceptionvariablespec = NULL;
    Symbol* exceptionvariable = NULL;

    { Object* clause = NULL;
      Cons* iter000 = tree;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        clause = iter000->value;
        if (safePrimaryType(clause) == SGT_WALK_STELLA_CONS) {
          { Object* clause000 = clause;
            Cons* clause = ((Cons*)(clause000));

            if (clause->length() < 2) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal exception handler clause: " << "`" << deUglifyParseTree(clause) << "'" << "." << std::endl;
                }
              }
              return (NULL);
            }
            exceptiontype = clause->value;
            if (!symbolP(exceptiontype)) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal exception type: " << "`" << deUglifyParseTree(exceptiontype) << "'" << "." << std::endl;
                }
              }
              return (NULL);
            }
            exceptiontype = typify(exceptiontype);
            if (!((boolean)(typeToClass(((Surrogate*)(exceptiontype)))))) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Undefined exception type: " << "`" << deUglifyParseTree(exceptiontype) << "'" << "." << std::endl;
                }
              }
              return (NULL);
            }
            if (!subtypeOfP(((Surrogate*)(exceptiontype)), SGT_WALK_STELLA_NATIVE_EXCEPTION)) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Exception type " << "`" << deUglifyParseTree(exceptiontype) << "'" << " is not a subtype of NATIVE-EXCEPTION" << "." << std::endl;
                }
              }
              return (NULL);
            }
            exceptionvariablespec = clause->rest->value;
            if ((!consP(exceptionvariablespec)) ||
                ((((Cons*)(exceptionvariablespec))->length() > 1) ||
                 ((((Cons*)(exceptionvariablespec))->length() == 1) &&
                  (!symbolP(((Cons*)(exceptionvariablespec))->value))))) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal exception variable specification: " << "`" << deUglifyParseTree(clause) << "'" << "." << std::endl;
                }
              }
              return (NULL);
            }
            exceptionvariable = ((Symbol*)(((Cons*)(exceptionvariablespec))->value));
            if (translateToJavaP() &&
                (!((boolean)(exceptionvariable)))) {
              exceptionvariable = localGensym("E");
            }
            exceptionvariablespec = walkADeclaration(exceptionvariable, exceptiontype, NULL, true);
            clause = listO(3, SYM_WALK_STELLA_SYS_HANDLE_EXCEPTION, exceptionvariablespec, walkListOfTrees(clause->rest->rest)->concatenate(NIL, 0));
            if (((boolean)(exceptionvariable))) {
              popVariableBinding();
            }
            clauses = cons(clause, clauses);
          }
        }
        else {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal exception handler clause: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
            }
          }
          return (NULL);
        }
      }
    }
    return (clauses->reverse());
  }
}

Cons* walkUnwindProtectTree(Cons* tree, Surrogate*& _Return1) {
  if (tree->value == SYM_WALK_STELLA_SYS_UNWIND_PROTECT) {
    _Return1 = SGT_WALK_STELLA_VOID;
    return (tree);
  }
  { Cons* _Return0 = cons(SYM_WALK_STELLA_SYS_UNWIND_PROTECT, walkListOfStatements(tree->rest)->concatenate(NIL, 0));

    _Return1 = SGT_WALK_STELLA_VOID;
    return (_Return0);
  }
}

void walkVerbatimDefinitionTree(Cons* tree) {
  { TranslationUnit* self000 = newTranslationUnit();

    self000->category = SYM_WALK_STELLA_VERBATIM;
    self000->codeRegister = tree;
    oCURRENTTRANSLATIONUNITo = self000;
  }
}

void walkVerbatimUnit(TranslationUnit* unit) {
  { StandardObject* dummy1;

    unit->theObject = walkATree(unit->codeRegister, dummy1);
    if (((boolean)(unit->theObject))) {
      oTRANSLATIONUNITSo->push(unit);
      unit->codeRegister = NULL;
    }
    else {
      unit->codeRegister = NULL;
      clearTranslationUnit(unit);
    }
  }
}

Object* walkVerbatimTree(Cons* tree, StandardObject*& _Return1) {
  { PropertyList* self000 = newPropertyList();

    self000->thePlist = tree->rest;
    { PropertyList* options = self000;
      Object* verbatimtree = options->lookup(oTRANSLATOROUTPUTLANGUAGEo);

      if (!((boolean)(verbatimtree))) {
        verbatimtree = options->lookup(KWD_WALK_OTHERWISE);
        if (!((boolean)(verbatimtree))) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Verbatim statement has no " << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " option." << "." << std::endl;
            }
          }
          _Return1 = SGT_WALK_STELLA_UNKNOWN;
          return (NULL);
        }
        if (!(verbatimtree == SYM_WALK_STELLA_NULL)) {
          return (walkATree(verbatimtree, _Return1));
        }
      }
      if (verbatimtree == SYM_WALK_STELLA_NULL) {
        _Return1 = SGT_WALK_STELLA_UNKNOWN;
        return (NULL);
      }
      if (subtypeOfStringP(safePrimaryType(verbatimtree))) {
        { Object* verbatimtree000 = verbatimtree;
          StringWrapper* verbatimtree = ((StringWrapper*)(verbatimtree000));

          options->insertAt(oTRANSLATOROUTPUTLANGUAGEo, newVerbatimStringWrapper(verbatimtree->wrapperValue));
        }
      }
      else {
      }
      _Return1 = SGT_WALK_STELLA_UNKNOWN;
      return (tree);
    }
  }
}

Object* lookupVerbatimTree(Cons* tree, Keyword* language) {
  if (!((boolean)(language))) {
    language = oTRANSLATOROUTPUTLANGUAGEo;
  }
  return (searchPlist(tree->rest, language));
}

boolean verbatimTreeP(Object* tree) {
  return (consP(tree) &&
      (((Cons*)(tree))->value == SYM_WALK_STELLA_VERBATIM));
}

void walkDefmoduleTree(Cons* tree) {
  { TranslationUnit* self000 = newTranslationUnit();

    self000->category = SYM_WALK_STELLA_MODULE;
    self000->theObject = tree;
    oCURRENTTRANSLATIONUNITo = self000;
  }
  { Module* module = NULL;
    const char* modulename = coerceToModuleName(tree->rest->value, false);

    if (modulename == NULL) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal module name: " << "`" << tree->rest->value << "'" << "." << std::endl;
        }
      }
      clearTranslationUnit(oCURRENTTRANSLATIONUNITo);
      oCURRENTTRANSLATIONUNITo = NULL;
      return;
    }
    module = defineModule(modulename, tree->rest->rest);
    oCURRENTTRANSLATIONUNITo->theObject = module;
  }
}

void walkModuleUnit(TranslationUnit* unit) {
  { Module* module = ((Module*)(unit->theObject));

    walkAuxiliaryTree(listO(4, SYM_WALK_STELLA_STARTUP_TIME_PROGN, KWD_WALK_MODULES, yieldDefineModule(module), NIL));
  }
}

Cons* extractRequiredArgumentValues(StandardObject* classtype, PropertyList* slotsandvalues) {
  { StandardObject* dummy1;

    { boolean arraytypeP = arrayTypeSpecifierP(classtype);
      List* requiredvalues = newList();
      boolean foundP = false;

      if (arraytypeP) {
        preprocessArrayArguments(((ParametricTypeSpecifier*)(classtype)), slotsandvalues);
      }
      { Symbol* requiredslotname = NULL;
        Cons* iter000 = typeSpecToClass(classtype)->classRequiredSlotNames_reader()->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          requiredslotname = ((Symbol*)(iter000->value));
          foundP = false;
          { Slot* slot = NULL;
            Object* valueref = NULL;
            Cons* iter001 = slotsandvalues->thePlist;

            for  (; !(iter001 == NIL); 
                  iter001 = iter001->rest->rest) {
              slot = ((Slot*)(iter001->value));
              valueref = iter001->rest->value;
              if (slot->slotName == requiredslotname) {
                foundP = true;
                if (arraytypeP) {
                  evaluateArrayArgumentValue(((ParametricTypeSpecifier*)(classtype)), requiredvalues, slot, valueref);
                }
                else {
                  requiredvalues->insertLast(walkExpressionTree(valueref, slot->computeReturnTypeSpec(classtype), SYM_WALK_STELLA_NEW, false, dummy1));
                }
                slotsandvalues->removeAt(slot);
                break;
              }
            }
          }
          if (!(foundP)) {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing required NEW argument: " << "`" << deUglifyParseTree(requiredslotname) << "'" << "." << std::endl;
              }
            }
          }
        }
      }
      return (requiredvalues->theConsList);
    }
  }
}

void preprocessArrayArguments(ParametricTypeSpecifier* arraytype, PropertyList* slotsandvalues) {
  { Class* arrayclass = ((Class*)(arraytype->specifierBaseType->surrogateValue));
    List* arraydimensions = arrayTypeDimensions(arraytype);
    int arrayrank = arraydimensions->length();
    Slot* initialelementslot = lookupSlot(arrayclass, SYM_WALK_STELLA_INITIAL_ELEMENT);
    Object* initialelementref = slotsandvalues->lookup(initialelementslot);
    Slot* arraysizeslot = lookupSlot(arrayclass, SYM_WALK_STELLA_SIZE);
    Object* sizeref = slotsandvalues->lookup(arraysizeslot);
    boolean nonlistsizeP = false;

    if (!((boolean)(sizeref))) {
      if (!indefiniteArrayTypeP(arraytype)) {
        sizeref = arrayTypeDimensions(arraytype)->theConsList;
      }
    }
    if (!((boolean)(sizeref))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing array :size argument in NEW expression" << "." << std::endl;
        }
      }
    }
    else {
      if (safePrimaryType(sizeref) == SGT_WALK_STELLA_CONS) {
        { Object* sizeref000 = sizeref;
          Cons* sizeref = ((Cons*)(sizeref000));

          if ((arrayrank == 1) &&
              ((!(sizeref->length() == 1)) ||
               (symbolP(sizeref->value) &&
                (((boolean)(lookupFunction(((Symbol*)(sizeref->value))))) ||
                 ((boolean)(lookupMacro(((Symbol*)(sizeref->value))))))))) {
            nonlistsizeP = true;
          }
        }
      }
      else {
        nonlistsizeP = true;
      }
      if (nonlistsizeP) {
        sizeref = cons(sizeref, NIL);
      }
      if (!(((Cons*)(sizeref))->length() == arrayrank)) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Array :size initializer " << "`" << deUglifyParseTree(sizeref) << "'" << std::endl << "   doesn't match the rank of" << std::endl << "   " << "`" << deUglifyParseTree(arraytype) << "'" << "." << std::endl;
          }
        }
        sizeref = NULL;
      }
      else {
        { ConsIterator* sizeit = ((Cons*)(sizeref))->allocateIterator();
          ListIterator* dimit = ((ListIterator*)(arraydimensions->allocateIterator()));
          int dim = NULL_INTEGER;
          int iter000 = 0;

          for  (; sizeit->nextP() &&
                    dimit->nextP(); 
                iter000 = iter000 + 1) {
            dim = iter000;
            if (!((boolean)(((IntegerWrapper*)(dimit->value))))) {
              if (integerP(sizeit->value)) {
                dimit->valueSetter(((IntegerWrapper*)(sizeit->value)));
              }
            }
            else if (!eqlP(((IntegerWrapper*)(dimit->value)), sizeit->value)) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Array :size initializer " << "`" << sizeit->value << "'" << " doesn't match array dimension " << "`" << deUglifyParseTree(wrapInteger(dim)) << "'" << " of" << std::endl << "   " << "`" << deUglifyParseTree(arraytype) << "'" << "." << std::endl;
                }
              }
              sizeit->valueSetter(((IntegerWrapper*)(dimit->value)));
            }
          }
        }
      }
    }
    slotsandvalues->insertAt(initialelementslot, initialelementref);
    if (((boolean)(sizeref))) {
      slotsandvalues->insertAt(arraysizeslot, sizeref);
    }
    else {
      slotsandvalues->removeAt(arraysizeslot);
    }
  }
}

void evaluateArrayArgumentValue(ParametricTypeSpecifier* arraytype, List* requiredvalues, Slot* slot, Object* valueref) {
  { StandardObject* dummy1;
    StandardObject* dummy2;
    StandardObject* dummy3;

    if (slot->slotName == SYM_WALK_STELLA_SIZE) {
      { Object* dim = NULL;
        Cons* iter000 = ((Cons*)(valueref));
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          dim = iter000->value;
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(walkExpressionTree(dim, SGT_WALK_STELLA_INTEGER, SYM_WALK_STELLA_NEW, false, dummy1), NIL);
              if (requiredvalues->theConsList == NIL) {
                requiredvalues->theConsList = collect000;
              }
              else {
                addConsToEndOfConsList(requiredvalues->theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(walkExpressionTree(dim, SGT_WALK_STELLA_INTEGER, SYM_WALK_STELLA_NEW, false, dummy2), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    else {
      requiredvalues->insertLast(walkExpressionTree(valueref, slot->computeReturnTypeSpec(arraytype), SYM_WALK_STELLA_NEW, false, dummy3));
    }
  }
}

Cons* yieldNewArgumentsTree(Cons* keywordsandvalues, StandardObject* classtype, Symbol* selfvariable, Cons*& _Return1) {
  if (((keywordsandvalues->length()) % 2)) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Odd number of arguments in 'new' expression: " << "`" << deUglifyParseTree(keywordsandvalues) << "'" << "." << std::endl;
      }
    }
    _Return1 = NIL;
    return (NIL);
  }
  { Class* clasS = typeSpecToClass(classtype);

    { PropertyList* self000 = newPropertyList();

      self000->thePlist = keywordsandvalues;
      { PropertyList* plist = self000;
        Cons* otherassignments = NIL;
        Cons* requiredvalues = NULL;
        Symbol* slotname = NULL;
        Slot* slot = NULL;

        { PropertyListIterator* it = ((PropertyListIterator*)(plist->allocateIterator()));

          for (; it->nextP(); ) {
            { Surrogate* testValue000 = safePrimaryType(it->key);

              if (subtypeOfKeywordP(testValue000)) {
                slotname = internSymbolInModule(((Keyword*)(it->key))->symbolName, clasS->homeModule(), false);
              }
              else if (subtypeOfSymbolP(testValue000)) {
                slotname = ((Symbol*)(it->key));
              }
              else {
                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  signalTranslationError();
                  if (!(suppressWarningsP())) {
                    printErrorContext(">> ERROR: ", STANDARD_ERROR);
                    *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal slot keyword " << "`" << it->key << "'" << " in NEW expression" << "." << std::endl;
                  }
                }
                _Return1 = NIL;
                return (NIL);
              }
            }
            slot = lookupSlot(clasS, slotname);
            if (!((boolean)(slot))) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "No such slot " << "`" << deUglifyParseTree(slotname) << "'" << " on the class " << "`" << className(clasS) << "'" << "." << std::endl;
                }
              }
              _Return1 = NIL;
              return (NIL);
            }
            it->keySetter(slot);
          }
        }
        requiredvalues = extractRequiredArgumentValues(classtype, plist);
        { Slot* slot = NULL;
          Object* valueref = NULL;
          Cons* iter000 = ((PropertyList*)(plist))->thePlist;
          Cons* collect000 = NULL;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest->rest) {
            slot = ((Slot*)(iter000->value));
            valueref = iter000->rest->value;
            if (!storageSlotP(slot)) {
              { MethodSlot* method = ((MethodSlot*)(slot));

                if (((boolean)(((Symbol*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_STORAGE_SLOT, NULL)))))) {
                  slot = lookupSlot(clasS, ((Symbol*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_STORAGE_SLOT, NULL))));
                }
              }
            }
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(listO(4, SYM_WALK_STELLA_SETF, cons(slot->slotName, cons(selfvariable, NIL)), valueref, NIL), NIL);
                if (otherassignments == NIL) {
                  otherassignments = collect000;
                }
                else {
                  addConsToEndOfConsList(otherassignments, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(listO(4, SYM_WALK_STELLA_SETF, cons(slot->slotName, cons(selfvariable, NIL)), valueref, NIL), NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        _Return1 = otherassignments;
        return (requiredvalues);
      }
    }
  }
}

Surrogate* getCurrentSelfType() {
  { MethodSlot* method = oMETHODBEINGWALKEDo;
    Surrogate* owner = SGT_WALK_STELLA_UNKNOWN;

    if (((boolean)(method))) {
      owner = method->owner();
      if (!((boolean)(owner))) {
        if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_CONSTRUCTORp, FALSE_WRAPPER)))->wrapperValue) {
          owner = method->slotBaseType;
        }
        else {
          owner = SGT_WALK_STELLA_UNKNOWN;
        }
      }
    }
    return (owner);
  }
}

Cons* walkNewTree(Cons* tree, StandardObject*& _Return1) {
  { Object* operatoR = tree->value;
    Object* classtree = tree->rest->value;
    Object* baseclassname = (consP(classtree) ? ((Cons*)(classtree))->value : classtree);
    Cons* keywordarguments = tree->rest->rest;
    Symbol* selfvariable = localGensym("SELF");
    StandardObject* classtype = NULL;
    Cons* newtree = NULL;

    if ((!symbolP(baseclassname)) &&
        (!keywordP(baseclassname))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal argument to " << "`" << deUglifyParseTree(operatoR) << "'" << " where symbol expected:  " << "`" << deUglifyParseTree(baseclassname) << "'" << "." << std::endl;
        }
      }
      return (walkDontCallMeTree(tree, SGT_WALK_STELLA_UNKNOWN, _Return1));
    }
    classtype = safeYieldTypeSpecifier(classtree);
    if (!((boolean)(typeSpecToClass(classtype)))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Undefined class supplied to " << "`" << deUglifyParseTree(operatoR) << "'" << " operator: " << "`" << deUglifyParseTree(baseclassname) << "'" << "." << std::endl;
        }
      }
      return (walkDontCallMeTree(tree, SGT_WALK_STELLA_UNKNOWN, _Return1));
    }
    if (!(typeP(classtype))) {
      classtype = computeRelativeTypeSpec(classtype, getCurrentSelfType());
    }
    if (typeSpecToClass(classtype)->abstractP) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Trying to create an instance of the ABSTRACT class " << "`" << deUglifyParseTree(baseclassname) << "'" << "." << std::endl;
        }
      }
      return (walkDontCallMeTree(tree, SGT_WALK_STELLA_UNKNOWN, _Return1));
    }
    { Cons* requiredargs = NULL;
      Cons* otherassignments = NULL;

      requiredargs = yieldNewArgumentsTree(keywordarguments, classtype, selfvariable, otherassignments);
      newtree = listO(3, SYM_WALK_STELLA_SYS_NEW, classtype, requiredargs->concatenate(NIL, 0));
      if (otherassignments == NIL) {
        _Return1 = classtype;
        return (newtree);
      }
      else {
        { Cons* _Return0 = listO(3, SYM_WALK_STELLA_VRLET, cons(cons(selfvariable, cons(newtree, NIL)), NIL), otherassignments->concatenate(cons(selfvariable, NIL), 0));

          _Return1 = classtype;
          return (_Return0);
        }
      }
    }
  }
}

Cons* walkMakeTree(Cons* tree, StandardObject*& _Return1) {
  { Object* classname = tree->rest->value;
    Cons* arguments = tree->rest->rest;
    Surrogate* type = NULL;
    Class* clasS = NULL;

    if (symbolP(classname)) {
    }
    else if (typeP(classname)) {
      tree->secondSetter(internSymbolInModule(((Surrogate*)(classname))->symbolName, ((Module*)(((Surrogate*)(classname))->homeContext)), true));
    }
    else {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Bad argument to 'make':" << std::endl << "   " << "`" << deUglifyParseTree(classname) << "'" << " found where symbol expected" << "." << std::endl;
        }
      }
      return (walkDontCallMeTree(tree, SGT_WALK_STELLA_UNKNOWN, _Return1));
    }
    type = typify(classname);
    clasS = ((Class*)(type->surrogateValue));
    if (!((boolean)(clasS))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Reference to undefined class " << "`" << deUglifyParseTree(classname) << "'" << "." << std::endl;
        }
      }
      return (walkDontCallMeTree(tree, SGT_WALK_STELLA_UNKNOWN, _Return1));
    }
    if ((!(arguments == NIL)) &&
        (!exceptionClassP(clasS))) {
      if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP) {
        if (!(((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_WALK_STELLA_CLASS_CPP_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue != NULL)) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "MAKE arguments not supported for non-native class " << "`" << deUglifyParseTree(classname) << "'" << "." << std::endl;
            }
          }
          return (walkDontCallMeTree(tree, type, _Return1));
        }
      }
      else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_JAVA) {
        if (!(((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_WALK_STELLA_CLASS_JAVA_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue != NULL)) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "MAKE arguments not supported for non-native class " << "`" << deUglifyParseTree(classname) << "'" << "." << std::endl;
            }
          }
          return (walkDontCallMeTree(tree, type, _Return1));
        }
      }
      else {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationWarning();
          if (!(suppressWarningsP())) {
            printErrorContext(">> WARNING: ", STANDARD_WARNING);
            *(STANDARD_WARNING->nativeStream) << std::endl << " " << "MAKE arguments not supported for " << "`" << translatorOutputLanguageName() << "'" << "; skipping them" << "." << std::endl;
          }
        }
        arguments = NIL;
      }
    }
    tree->rest->rest = walkListOfTrees(arguments);
    _Return1 = type;
    return (tree);
  }
}

Cons* walkFuncallTree(Cons* tree, StandardObject*& _Return1) {
  if ((tree->value == SYM_WALK_STELLA_SYS_CALL_FUNCTION_CODE) ||
      (tree->value == SYM_WALK_STELLA_SYS_CALL_METHOD_CODE)) {
    _Return1 = ((StandardObject*)(((Cons*)(((Cons*)(tree->rest->value))->value))->value));
    return (tree);
  }
  { StandardObject* returntype = ((oTARGETTYPEo == SGT_WALK_STELLA_UNKNOWN) ? SGT_WALK_STELLA_VOID : ((StandardObject*)(oTARGETTYPEo)));
    Cons* signature = cons(cons(returntype, NIL), NIL);

    { Object* otree = NULL;
      StandardObject* otype = NULL;

      otree = walkExpressionTree(tree->rest->value, SGT_WALK_STELLA_CODE, SYM_WALK_STELLA_FUNCALL, true, otype);
      tree->firstSetter(((otype == SGT_WALK_STELLA_METHOD_CODE) ? SYM_WALK_STELLA_SYS_CALL_METHOD_CODE : SYM_WALK_STELLA_SYS_CALL_FUNCTION_CODE));
      tree->secondSetter(otree);
    }
    { ConsIterator* it = tree->rest->rest->allocateIterator();

      for (; it->nextP(); ) {
        { Object* argtree = NULL;
          StandardObject* argtype = NULL;

          argtree = walkATree(it->value, argtype);
          it->valueSetter(argtree);
          signature = cons(argtype, signature);
        }
      }
    }
    tree->rest = cons(signature->reverse(), tree->rest);
    _Return1 = returntype;
    return (tree);
  }
}

Cons* walkTheCodeTree(Cons* tree, StandardObject*& _Return1) {
  { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->rest->value));

    if (testValue000 == KWD_WALK_FUNCTION) {
      if (badArgumentRangeP(tree, 2, 3)) {
        return (walkDontCallMeTree(tree, SGT_WALK_STELLA_FUNCTION_CODE, _Return1));
      }
      if (!(symbolP(tree->rest->rest->value))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal function name: " << "`" << tree->rest->rest->value << "'" << "." << std::endl;
          }
        }
        return (walkDontCallMeTree(tree, SGT_WALK_STELLA_FUNCTION_CODE, _Return1));
      }
      if (tree->rest->rest->value == SYM_WALK_STELLA_MAIN) {
        if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP) ||
            (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP_STANDALONE)) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Cannot generate a function pointer to `main' in C++" << "." << std::endl;
            }
          }
          return (walkDontCallMeTree(tree, SGT_WALK_STELLA_FUNCTION_CODE, _Return1));
        }
        else {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationWarning();
            if (!(suppressWarningsP())) {
              printErrorContext(">> WARNING: ", STANDARD_WARNING);
              *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Won't be able to generate a function pointer to `main' in C++" << "." << std::endl;
            }
          }
        }
      }
      _Return1 = SGT_WALK_STELLA_FUNCTION_CODE;
      return (tree);
    }
    else if (testValue000 == KWD_WALK_METHOD) {
      if (badArgumentCountP(tree, 3)) {
        return (walkDontCallMeTree(tree, SGT_WALK_STELLA_METHOD_CODE, _Return1));
      }
      if (!(isaP(tree->rest->rest->value, SGT_WALK_STELLA_GENERALIZED_SYMBOL))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal method class: " << "`" << tree->rest->rest->value << "'" << "." << std::endl;
          }
        }
        return (walkDontCallMeTree(tree, SGT_WALK_STELLA_METHOD_CODE, _Return1));
      }
      if (!(symbolP(tree->fourth()))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal method name: " << "`" << tree->fourth() << "'" << "." << std::endl;
          }
        }
        return (walkDontCallMeTree(tree, SGT_WALK_STELLA_METHOD_CODE, _Return1));
      }
      { Surrogate* type = typify(tree->rest->rest->value);

        tree->thirdSetter(type);
        if (!((boolean)(((Class*)(type->surrogateValue))))) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "No class defined for the type: " << "`" << deUglifyParseTree(type) << "'" << "." << std::endl;
            }
          }
        }
        else {
          if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP) ||
              (oTRANSLATOROUTPUTLANGUAGEo == KWD_WALK_CPP_STANDALONE)) {
            { Slot* method = lookupSlot(((Class*)(type->surrogateValue)), ((Symbol*)(tree->fourth())));

              if (((boolean)(method)) &&
                  cppMethodObjectIsOverloadedFunctionP(((MethodSlot*)(method)))) {
                return (sysTree(listO(4, SYM_WALK_STELLA_THE_CODE, KWD_WALK_FUNCTION, method, NIL), SGT_WALK_STELLA_FUNCTION_CODE, _Return1));
              }
            }
            if (!subtypeOfP(type, SGT_WALK_STELLA_OBJECT)) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationNote();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> NOTE: ", STANDARD_OUTPUT);
                  std::cout << std::endl << " " << "Cannot store a method-code pointer for " << std::endl << " " << "`" << tree->rest->rest->value << "'" << "." << "`" << tree->fourth() << "'" << std::endl << " since it is not defined on a subtype of @OBJECT" << "." << std::endl;
                }
              }
              { Object* value000 = NULL;
                StandardObject* value001 = NULL;

                value000 = walkATree(listO(4, SYM_WALK_STELLA_CAST, SYM_WALK_STELLA_NULL, SYM_WALK_STELLA_METHOD_CODE, NIL), value001);
                _Return1 = value001;
                return (((Cons*)(value000)));
              }
            }
          }
          else {
          }
        }
        _Return1 = SGT_WALK_STELLA_METHOD_CODE;
        return (tree);
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

Cons* walkCallSuperMethodTree(Cons* tree, StandardObject*& _Return1) {
  { MethodSlot* enclosingmethod = oMETHODBEINGWALKEDo;
    Cons* calltree = NULL;
    StandardObject* calltype = NULL;
    Cons* baretree = NULL;

    if ((!((boolean)(enclosingmethod))) ||
        enclosingmethod->methodFunctionP) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "call-super-method not called within a method: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
        }
      }
    }
    else if (!(((Symbol*)(enclosingmethod->methodParameterNames_reader()->first())) == tree->rest->value)) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "call-super-method needs to be called with enclosing method's self arg: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
        }
      }
    }
    else if (!((boolean)(enclosingmethod->slotDirectEquivalent))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "call-super-method: no super method available for: " << "`" << deUglifyParseTree(oMETHODBEINGWALKEDo) << "'" << "." << std::endl;
        }
      }
    }
    else {
      tree->firstSetter(enclosingmethod->slotName);
      { Object* value000 = NULL;
        StandardObject* value001 = NULL;

        value000 = walkCallSlotTree(tree, value001);
        {
          calltree = ((Cons*)(value000));
          calltype = value001;
        }
      }
      baretree = ((Cons*)(walkedExpressionExpression(calltree)));
      if (baretree->value == SYM_WALK_STELLA_SYS_CALL_METHOD) {
        baretree->firstSetter(SYM_WALK_STELLA_SYS_CALL_SUPER_METHOD);
        return (sysTree(calltree, calltype, _Return1));
      }
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal call-super-method call or context: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
        }
      }
    }
    return (walkDontCallMeTree(tree, oTARGETTYPEo, _Return1));
  }
}

Cons* deUglifyArguments(Cons* uglyarguments) {
  { Cons* prettyarguments = NIL;

    { Object* arg = NULL;
      Cons* iter000 = uglyarguments;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        arg = iter000->value;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(deUglifyParseTree(arg), NIL);
            if (prettyarguments == NIL) {
              prettyarguments = collect000;
            }
            else {
              addConsToEndOfConsList(prettyarguments, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(deUglifyParseTree(arg), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (prettyarguments);
  }
}

Object* deUglifyParseTree(Object* tree) {
  if (!((boolean)(tree))) {
    return (NULL);
  }
  { Surrogate* testValue000 = safePrimaryType(tree);

    if (testValue000 == SGT_WALK_STELLA_CONS) {
      { Object* tree000 = tree;
        Cons* tree = ((Cons*)(tree000));

        { Object* operatoR = tree->value;

          if (!symbolP(operatoR)) {
            return (deUglifyArguments(tree));
          }
          { GeneralizedSymbol* testValue001 = ((GeneralizedSymbol*)(operatoR));

            if ((testValue001 == SYM_WALK_STELLA_SYS_SLOT_VALUE) ||
                ((testValue001 == SYM_WALK_STELLA_SYS_SLOT_VALUE_SETTER) ||
                 (testValue001 == SYM_WALK_STELLA_SYS_CALL_METHOD))) {
              return (deUglifyParseTree(tree->rest->rest));
            }
            else if (testValue001 == SYM_WALK_STELLA_SYS_CALL_FUNCTION) {
              return (deUglifyParseTree(tree->rest));
            }
            else if ((testValue001 == SYM_WALK_STELLA_TYPED_SYS) ||
                ((testValue001 == SYM_WALK_STELLA_VOID_SYS) ||
                 (testValue001 == SYM_WALK_STELLA_BAD_SYS))) {
              return (deUglifyParseTree(tree->rest->value));
            }
            else if (testValue001 == SYM_WALK_STELLA_GET_SYM) {
              return (getSymFromOffset(((IntegerWrapper*)(tree->rest->value))->wrapperValue));
            }
            else {
              { Cons* prettyarguments = NIL;

                { Object* arg = NULL;
                  Cons* iter000 = tree->rest;
                  Cons* collect000 = NULL;

                  for  (; !(iter000 == NIL); 
                        iter000 = iter000->rest) {
                    arg = iter000->value;
                    if (!((boolean)(collect000))) {
                      {
                        collect000 = cons(deUglifyParseTree(arg), NIL);
                        if (prettyarguments == NIL) {
                          prettyarguments = collect000;
                        }
                        else {
                          addConsToEndOfConsList(prettyarguments, collect000);
                        }
                      }
                    }
                    else {
                      {
                        collect000->rest = cons(deUglifyParseTree(arg), NIL);
                        collect000 = collect000->rest;
                      }
                    }
                  }
                }
                return (cons(operatoR, prettyarguments->concatenate(NIL, 0)));
              }
            }
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_WALK_STELLA_COMPOUND_TYPE_SPECIFIER)) {
      { Object* tree001 = tree;
        CompoundTypeSpecifier* tree = ((CompoundTypeSpecifier*)(tree001));

        return (yieldTypeSpecTree(tree));
      }
    }
    else {
      return (tree);
    }
  }
}

HashTable* oNATIVE_NAME_TABLEo = NULL;

void registerNativeName(Symbol* name, Keyword* language, Keyword* category) {
  { KeyValueList* tableentry = ((KeyValueList*)(oNATIVE_NAME_TABLEo->lookup(name)));
    List* categories = NULL;

    if (!((boolean)(tableentry))) {
      tableentry = newKeyValueList();
    }
    categories = ((List*)(tableentry->lookup(language)));
    if (!((boolean)(categories))) {
      categories = newList();
    }
    categories->insertNew(category);
    tableentry->insertAt(language, categories);
    oNATIVE_NAME_TABLEo->insertAt(name, tableentry);
  }
}

boolean nativeNameP(Symbol* name, Keyword* language, Keyword* category) {
  { KeyValueList* tableentry = ((KeyValueList*)(oNATIVE_NAME_TABLEo->lookup(name)));
    List* categories = NULL;

    if (!((boolean)(tableentry))) {
      return (false);
    }
    categories = ((List*)(tableentry->lookup(language)));
    if (!((boolean)(categories))) {
      return (false);
    }
    else {
      return ((!((boolean)(category))) ||
          categories->memberP(category));
    }
  }
}

Symbol* yieldRenamedNameIfNative(Symbol* name, Keyword* language, Keyword* category) {
  if (nativeNameP(name, language, category)) {
    { Symbol* newname = NULL;

      if (language == KWD_WALK_COMMON_LISP) {
        newname = internDerivedSymbol(name, stringConcatenate("%", name->symbolName, 0));
      }
      else if (language == KWD_WALK_CPP) {
        return (name);
      }
      else {
        newname = internDerivedSymbol(name, stringConcatenate(name->symbolName, "_", 0));
      }
      return (yieldRenamedNameIfNative(newname, language, category));
    }
  }
  else {
    return (name);
  }
}

boolean methodNeedsLispMacroP(MethodSlot* method) {
  if (translateToCommonLispP() &&
      method->methodParameterNames_reader()->nonEmptyP()) {
    { BooleanWrapper* lispmacroP = ((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_LISP_MACROp, NULL)));

      return ((((boolean)(lispmacroP)) &&
          coerceWrappedBooleanToBoolean(lispmacroP)) ||
          (commandP(method) &&
           ((!((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_NATIVEp, FALSE_WRAPPER)))->wrapperValue) &&
            ((!((boolean)(lispmacroP))) ||
             coerceWrappedBooleanToBoolean(lispmacroP)))));
    }
  }
  else {
    return (false);
  }
}

Cons* yieldLispMacroTrees(Symbol* name, MethodSlot* method, Cons*& _Return1) {
  { Module* module = (((boolean)(((Module*)(name->homeContext)))) ? ((Module*)(name->homeContext)) : oMODULEo);
    Object* translatedname = yieldGlobalLispSymbol(module, name->symbolName);
    Object* translatedfullname = yieldGlobalLispSymbol(module, computeFullName(name->symbolName, module));
    const char* documentation = ((StringWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue;

    { Cons* _Return0 = listO(6, SYM_WALK_STELLA_VERBATIM, KWD_WALK_COMMON_LISP, listO(3, internCommonLispSymbol("DEFMACRO"), translatedname, cons(listO(5, internCommonLispSymbol("&WHOLE"), SYM_WALK_STELLA_EXPRESSION, internCommonLispSymbol("&REST"), SYM_WALK_STELLA_IGNORE, NIL), (((documentation != NULL) ? cons(wrapString(documentation), NIL) : NIL))->concatenate(listO(3, listO(3, internCommonLispSymbol("DECLARE"), listO(3, internCommonLispSymbol("IGNORE"), SYM_WALK_STELLA_IGNORE, NIL), NIL), listO(4, internCommonLispSymbol("LET"), cons(cons(clTranslateGlobalSymbol(SYM_WALK_STELLA_oIGNORETRANSLATIONERRORSpo), cons((commandP(method) ? clTranslateGlobalSymbol(SYM_WALK_STELLA_FALSE) : clTranslateGlobalSymbol(SYM_WALK_STELLA_TRUE)), NIL)), NIL), cons(clTranslateGlobalSymbol(SYM_WALK_STELLA_CL_INCREMENTALLY_TRANSLATE), cons(SYM_WALK_STELLA_EXPRESSION, NIL)), NIL), NIL), 0))), KWD_WALK_OTHERWISE, SYM_WALK_STELLA_NULL, NIL);

      _Return1 = listO(6, SYM_WALK_STELLA_VERBATIM, KWD_WALK_COMMON_LISP, listO(4, internCommonLispSymbol("SETF"), listO(3, internCommonLispSymbol("MACRO-FUNCTION"), listO(3, internCommonLispSymbol("QUOTE"), translatedfullname, NIL), NIL), listO(3, internCommonLispSymbol("MACRO-FUNCTION"), listO(3, internCommonLispSymbol("QUOTE"), translatedname, NIL), NIL), NIL), KWD_WALK_OTHERWISE, SYM_WALK_STELLA_NULL, NIL);
      return (_Return0);
    }
  }
}

void createLispMacroUnits(Symbol* name, MethodSlot* method) {
  if (name == method->slotName) {
    registerNativeName(name, KWD_WALK_COMMON_LISP, KWD_WALK_FUNCTION);
  }
  { Cons* macrotree = NULL;
    Cons* aliasdefinitiontree = NULL;

    macrotree = yieldLispMacroTrees(name, method, aliasdefinitiontree);
    walkAuxiliaryTree(macrotree);
    walkAuxiliaryTree(aliasdefinitiontree);
  }
  if (name == method->slotName) {
    walkAuxiliaryTree(listO(3, SYM_WALK_STELLA_STARTUP_TIME_PROGN, listO(5, SYM_WALK_STELLA_REGISTER_NATIVE_NAME, listO(3, SYM_WALK_STELLA_QUOTE, name, NIL), KWD_WALK_COMMON_LISP, KWD_WALK_FUNCTION, NIL), NIL));
  }
}

boolean methodNeedsCCallableWrapperP(MethodSlot* method) {
  if (translateToCppP() &&
      (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_C_CALLABLEp, FALSE_WRAPPER)))->wrapperValue &&
       (!((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_SLOT_AUXILIARYp, FALSE_WRAPPER)))->wrapperValue))) {
    if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationWarning();
        if (!(suppressWarningsP())) {
          printErrorContext(">> WARNING: ", STANDARD_WARNING);
          *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Cannot create a C-callable wrapper for a variable arguments function: " << "`" << deUglifyParseTree(method) << "'" << "." << std::endl;
        }
      }
      return (false);
    }
    else if (method->methodReturnTypeSpecifiers_reader()->length() > 1) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationWarning();
        if (!(suppressWarningsP())) {
          printErrorContext(">> WARNING: ", STANDARD_WARNING);
          *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Cannot create a C-callable wrapper for a multi-valued function: " << "`" << deUglifyParseTree(method) << "'" << "." << std::endl;
        }
      }
      return (false);
    }
    else {
      return (true);
    }
  }
  else {
    return (false);
  }
}

Symbol* yieldCCallableWrapperName(MethodSlot* method) {
  { Symbol* methodname = method->slotName;
    const char* basename = methodname->symbolName;
    const char* prefix = ((StringWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_C_NAMESPACE_PREFIX, NULL_STRING_WRAPPER)))->wrapperValue;

    if (!(method->methodFunctionP)) {
      basename = stringConcatenate(method->slotOwner->symbolName, "-", 1, basename);
    }
    if (prefix == NULL) {
      prefix = stringConcatenate(cppYieldNamespacePrefixFromModule(method->homeModule()), "_", 0);
    }
    if (allUpperCaseStringP(basename)) {
      prefix = stringUpcase(prefix);
    }
    return (internDerivedSymbol(methodname, stringConcatenate(prefix, basename, 0)));
  }
}

Cons* yieldCCallableWrapperTree(MethodSlot* method) {
  { Cons* definition = ((Cons*)(unstringifyStellaSource(method->methodStringifiedSource, NULL)));
    Symbol* wrappername = yieldCCallableWrapperName(method);
    Object* nametree = definition->rest->value;
    Cons* calltree = cons(method->slotName, NIL);
    Surrogate* returntype = method->type();
    boolean returnsvaluesP = !(returntype == SGT_WALK_STELLA_VOID);

    { Symbol* name = NULL;
      Cons* iter000 = method->methodParameterNames_reader()->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        name = ((Symbol*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(name, NIL);
            if (calltree == NIL) {
              calltree = collect000;
            }
            else {
              addConsToEndOfConsList(calltree, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(name, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    if (returnsvaluesP) {
      if (subtypeOfP(returntype, SGT_WALK_STELLA_STRING) ||
          (subtypeOfP(returntype, SGT_WALK_STELLA_MUTABLE_STRING) ||
           (!subtypeOfP(returntype, SGT_WALK_STELLA_LITERAL)))) {
        calltree = listO(4, SYM_WALK_STELLA_PROGN, listO(4, SYM_WALK_STELLA_SETQ, SYM_WALK_STELLA_oC_API_RESULT_BUFFERo, listO(3, SYM_WALK_STELLA_CAST, calltree, cons(SYM_WALK_STELLA_NATIVE_OBJECT_POINTER, NIL)), NIL), listO(3, SYM_WALK_STELLA_RETURN, listO(4, SYM_WALK_STELLA_CAST, SYM_WALK_STELLA_oC_API_RESULT_BUFFERo, returntype, NIL), NIL), NIL);
      }
      else {
        calltree = listO(3, SYM_WALK_STELLA_RETURN, calltree, NIL);
      }
    }
    if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_THROWS_EXCEPTIONSp, FALSE_WRAPPER)))->wrapperValue) {
      { Cons* returntree = NIL;

        if (returnsvaluesP) {
          { StandardObject* type = NULL;
            Cons* iter001 = method->methodReturnTypeSpecifiers_reader()->theConsList;
            Cons* collect001 = NULL;

            for  (; !(iter001 == NIL); 
                  iter001 = iter001->rest) {
              type = ((StandardObject*)(iter001->value));
              type = type;
              if (!((boolean)(collect001))) {
                {
                  collect001 = cons(SYM_WALK_STELLA_NULL, NIL);
                  if (returntree == NIL) {
                    returntree = collect001;
                  }
                  else {
                    addConsToEndOfConsList(returntree, collect001);
                  }
                }
              }
              else {
                {
                  collect001->rest = cons(SYM_WALK_STELLA_NULL, NIL);
                  collect001 = collect001->rest;
                }
              }
            }
          }
          returntree = cons(cons(SYM_WALK_STELLA_RETURN, returntree->concatenate(NIL, 0)), NIL);
        }
        calltree = listO(3, SYM_WALK_STELLA_EXCEPTION_CASE, calltree, cons(listO(4, SYM_WALK_STELLA_NATIVE_EXCEPTION, cons(SYM_WALK_STELLA_E, NIL), listO(3, SYM_WALK_STELLA_CALL_GLOBAL_EXCEPTION_HANDLER, SYM_WALK_STELLA_E, NIL), returntree->concatenate(NIL, 0)), NIL));
      }
    }
    if (consP(nametree)) {
      ((Cons*)(nametree))->firstSetter(wrappername);
    }
    else {
      nametree = wrappername;
    }
    return (listO(3, SYM_WALK_STELLA_DEFUN, nametree, cons(definition->rest->rest->value, listO(3, KWD_WALK_DOCUMENTATION, wrapString(stringConcatenate("C-callable wrapper for `", cppTranslateMethodName(method, true)->wrapperValue, 1, "'.")), listO(8, KWD_WALK_PUBLICp, SYM_WALK_STELLA_TRUE, KWD_WALK_AUXILIARYp, SYM_WALK_STELLA_TRUE, KWD_WALK_C_CALLABLEp, SYM_WALK_STELLA_TRUE, calltree, NIL)))));
  }
}

MethodSlot* createCCallableWrapperUnit(MethodSlot* method) {
  { Cons* wrappertree = yieldCCallableWrapperTree(method);
    MethodSlot* wrappermethod = NULL;

    wrappermethod = ((MethodSlot*)(helpWalkAuxiliaryTree(wrappertree, true)->theObject));
    return (wrappermethod);
  }
}

boolean cCallableWrapperMethodP(MethodSlot* method) {
  return (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_SLOT_AUXILIARYp, FALSE_WRAPPER)))->wrapperValue &&
      ((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_C_CALLABLEp, FALSE_WRAPPER)))->wrapperValue);
}

Cons* yieldFunctionCppSignature(MethodSlot* function, StandardObject* firstargtype, boolean qualifyP) {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (qualifyP ? oROOT_MODULEo : function->homeModule()));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (!((boolean)(firstargtype))) {
      firstargtype = function->slotOwner;
    }
    { StandardObject* returntype = computeMostGeneralReturnType(function, function->computeReturnTypeSpec(firstargtype));
      Cons* cppsig = cons(cons(cppTranslateMethodName(function, true), cons((voidP(returntype) ? wrapString("void") : cppTranslateAndPointerizeTypeSpec(returntype)), cons(wrapString(stringify(typeSpecToBaseType(returntype))), NIL))), NIL);
      List* returntypes = function->methodReturnTypeSpecifiers_reader();
      List* parametertypes = function->methodParameterTypeSpecifiers_reader();
      int retidx = 0;

      { Cons* param = NULL;
        Cons* iter000 = ((Cons*)(cppTranslateFunctionParameters(function)));
        int i = NULL_INTEGER;
        int iter001 = 0;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest,
              iter001 = iter001 + 1) {
          param = ((Cons*)(iter000->value));
          i = iter001;
          { Object* type = param->value;
            Object* name = param->rest->value;
            StandardObject* stellatype = NULL;

            if (type == SYM_WALK_STELLA_CPP_VAR_ARGS) {
              cppsig = cons(consList(3, name, wrapString("int"), wrapString(stringify(SGT_WALK_STELLA_INTEGER))), cppsig);
              name = wrapString("...");
              stellatype = variableArgumentsType(function);
              type = cppTranslateAndPointerizeTypeSpec(stellatype);
            }
            else if (startsWithP(((StringWrapper*)(name))->wrapperValue, "_Return", 0)) {
              retidx = retidx + 1;
              stellatype = ((StandardObject*)(returntypes->nth(retidx)));
            }
            else {
              stellatype = ((StandardObject*)(parametertypes->nth(i)));
            }
            stellatype = computeRelativeTypeSpec(stellatype, firstargtype);
            cppsig = cons(consList(3, name, type, wrapString(stringify(typeSpecToBaseType(stellatype)))), cppsig);
          }
        }
      }
      return (cppsig->reverse());
    }
  }
}

const char* cppTypeToCType(const char* type) {
  { boolean returnparameterP = endsWithP(type, "&", NULL_INTEGER);

    if (returnparameterP) {
      type = stringSubsequence(type, 0, strlen(type) - 1);
    }
    if (stringEqlP(type, "boolean")) {
      type = "int";
    }
    else if (stringEqlP(type, "char*")) {
    }
    else if (stringEqlP(type, "const char*")) {
    }
    else if (stringEqlP(type, "cpp_function_code")) {
      type = "void*";
    }
    else if (stringEqlP(type, "cpp_method_code")) {
      type = "void*";
    }
    else {
      { int starpos = stringPosition(type, '*', 0);

        if (starpos != NULL_INTEGER) {
          type = stringConcatenate("void*", stringSubsequence(type, starpos + 1, NULL_INTEGER), 0);
        }
      }
    }
    if (returnparameterP) {
      type = stringConcatenate(type, "&", 0);
    }
    return (type);
  }
}

Cons* yieldFunctionCSignature(MethodSlot* function, StandardObject* firstargtype) {
  { Cons* cppsignature = yieldFunctionCppSignature(function, firstargtype, true);
    Cons* csignature = NIL;
    const char* name = NULL;
    const char* type = NULL;
    const char* stellatype = NULL;

    ((Cons*)(cppsignature->value))->firstSetter(cppTranslateName(yieldCCallableWrapperName(function)));
    { Cons* tuple = NULL;
      Cons* iter000 = cppsignature;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        tuple = ((Cons*)(iter000->value));
        name = ((StringWrapper*)(tuple->value))->wrapperValue;
        type = ((StringWrapper*)(tuple->rest->value))->wrapperValue;
        stellatype = ((StringWrapper*)(tuple->rest->rest->value))->wrapperValue;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(consList(3, wrapString(name), wrapString(cppTypeToCType(type)), wrapString(stellatype)), NIL);
            if (csignature == NIL) {
              csignature = collect000;
            }
            else {
              addConsToEndOfConsList(csignature, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(consList(3, wrapString(name), wrapString(cppTypeToCType(type)), wrapString(stellatype)), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (csignature);
  }
}

Cons* yieldMethodCppSignature(MethodSlot* method, StandardObject* firstargtype, boolean qualifyP) {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (qualifyP ? oROOT_MODULEo : method->homeModule()));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    { Cons* sig = NULL;
      const char* transname = NULL;

      try {
        method->methodFunctionP = true;
        sig = yieldFunctionCppSignature(method, firstargtype, qualifyP);
      }
catch (...) {
        method->methodFunctionP = false;
        throw;
      }
      method->methodFunctionP = false;
      transname = cppTranslateMethodName(method, qualifyP)->wrapperValue;
      ((Cons*)(sig->value))->firstSetter(wrapString(transname));
      return (sig);
    }
  }
}

Cons* yieldMethodCSignature(MethodSlot* method, StandardObject* firstargtype) {
  { StringWrapper* cppname = ((StringWrapper*)(((Cons*)(yieldMethodCppSignature(method, firstargtype, true)->value))->value));
    Cons* sig = NULL;

    try {
      method->methodFunctionP = true;
      sig = yieldFunctionCSignature(method, firstargtype);
    }
catch (...) {
      method->methodFunctionP = false;
      throw;
    }
    method->methodFunctionP = false;
    ((Cons*)(sig->value))->firstSetter(wrapString(replaceSubstrings(cppname->wrapperValue, "_", "::")));
    return (sig);
  }
}

Cons* yieldStorageSlotCppSignature(StorageSlot* slot, StandardObject* firstargtype, boolean qualifyP) {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (qualifyP ? oROOT_MODULEo : slot->homeModule()));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (!((boolean)(firstargtype))) {
      firstargtype = slot->slotOwner;
    }
    { Symbol* slotname = trueSlotName(slot->slotName, slot->slotOwner);
      StandardObject* slottype = slot->computeReturnTypeSpec(firstargtype);
      Cons* cppsig = cons(cons(cppTranslateName(slotname), cons(cppTranslateAndPointerizeTypeSpec(slottype), cons(wrapString(stringify(typeSpecToBaseType(slottype))), NIL))), NIL);

      return (cppsig);
    }
  }
}

Cons* yieldStorageSlotCSignature(StorageSlot* slot, StandardObject* firstargtype) {
  { Cons* sig = yieldStorageSlotCppSignature(slot, firstargtype, true);
    StringWrapper* cppname = ((StringWrapper*)(((Cons*)(sig->value))->value));
    StringWrapper* cpptype = ((StringWrapper*)(((Cons*)(sig->value))->rest->value));

    ((Cons*)(sig->value))->firstSetter(wrapString(replaceSubstrings(cppname->wrapperValue, "_", "::")));
    ((Cons*)(sig->value))->secondSetter(wrapString(cppTypeToCType(cpptype->wrapperValue)));
    return (sig);
  }
}

Cons* yieldGlobalVariableCppSignature(GlobalVariable* global, boolean qualifyP) {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (qualifyP ? oROOT_MODULEo : global->homeModule()));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    { Cons* cppsig = cons(cons(cppTranslateGlobalVariableName(global), cons(cppTranslateAndPointerizeTypeSpec(globalVariableTypeSpec(global)), cons(wrapString(stringify(typeSpecToBaseType(globalVariableTypeSpec(global)))), NIL))), NIL);

      return (cppsig);
    }
  }
}

Cons* yieldGlobalVariableCSignature(GlobalVariable* global) {
  { Cons* sig = yieldGlobalVariableCppSignature(global, true);
    StringWrapper* cppname = ((StringWrapper*)(((Cons*)(sig->value))->value));
    StringWrapper* cpptype = ((StringWrapper*)(((Cons*)(sig->value))->rest->value));

    ((Cons*)(sig->value))->firstSetter(wrapString(replaceSubstrings(cppname->wrapperValue, "_", "::")));
    ((Cons*)(sig->value))->secondSetter(wrapString(cppTypeToCType(cpptype->wrapperValue)));
    return (sig);
  }
}

const char* listSignatureToString(Cons* signature) {
  { char sep = '\t';
    OutputStringStream* ssig = newOutputStringStream();

    { Cons* tuple = NULL;
      Cons* iter000 = signature;
      int i = NULL_INTEGER;
      int iter001 = 0;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        tuple = ((Cons*)(iter000->value));
        i = iter001;
        if (i > 0) {
          *(ssig->nativeStream) << sep;
        }
        *(ssig->nativeStream) << unwrapString(((StringWrapper*)(tuple->value))) << sep << unwrapString(((StringWrapper*)(tuple->rest->value))) << sep << unwrapString(((StringWrapper*)(tuple->rest->rest->value)));
      }
    }
    return (ssig->theStringReader());
  }
}

cpp_function_code lookupFunctionCodeByName(const char* qualifiedname) {
  { MethodSlot* function = lookupFunctionByQualifiedName(qualifiedname);

    if (((boolean)(function))) {
      return (function->functionCode);
    }
    else {
      return (NULL);
    }
  }
}

extern "C" cpp_function_code stella_lookupFunctionCodeByName(const char* qualifiedname) {
  // C-callable wrapper for `lookupFunctionCodeByName'.
  try {
    return (lookupFunctionCodeByName(qualifiedname));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

cpp_function_code lookupCCallableWrapperCodeByName(const char* qualifiedname) {
  { MethodSlot* function = lookupFunctionByQualifiedName(qualifiedname);

    if (((boolean)(function))) {
      return (((FunctionCodeWrapper*)(dynamicSlotValue(function->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, NULL_FUNCTION_CODE_WRAPPER)))->wrapperValue);
    }
    else {
      return (NULL);
    }
  }
}

extern "C" cpp_function_code stella_lookupCCallableWrapperCodeByName(const char* qualifiedname) {
  // C-callable wrapper for `lookupCCallableWrapperCodeByName'.
  try {
    return (lookupCCallableWrapperCodeByName(qualifiedname));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

const char* lookupFunctionCppSignatureByName(const char* qualifiedname) {
  { MethodSlot* function = lookupFunctionByQualifiedName(qualifiedname);

    if (((boolean)(function))) {
      return (listSignatureToString(yieldFunctionCppSignature(function, NULL, true)));
    }
    else {
      return (NULL);
    }
  }
}

extern "C" const char* stella_lookupFunctionCppSignatureByName(const char* qualifiedname) {
  // C-callable wrapper for `lookupFunctionCppSignatureByName'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(lookupFunctionCppSignatureByName(qualifiedname)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

const char* lookupFunctionCSignatureByName(const char* qualifiedname) {
  { MethodSlot* function = lookupFunctionByQualifiedName(qualifiedname);

    if (((boolean)(function))) {
      return (listSignatureToString(yieldFunctionCSignature(function, NULL)));
    }
    else {
      return (NULL);
    }
  }
}

extern "C" const char* stella_lookupFunctionCSignatureByName(const char* qualifiedname) {
  // C-callable wrapper for `lookupFunctionCSignatureByName'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(lookupFunctionCSignatureByName(qualifiedname)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

CodeWrapper* lookupMethodCodeByName(const char* qualifiedname) {
  { Slot* slot = lookupSlotByQualifiedName(qualifiedname);

    if (methodSlotP(slot)) {
      return (((MethodSlot*)(slot))->methodCode);
    }
    else {
      return (NULL);
    }
  }
}

extern "C" CodeWrapper* stella_lookupMethodCodeByName(const char* qualifiedname) {
  // C-callable wrapper for `lookupMethodCodeByName'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(lookupMethodCodeByName(qualifiedname)));
    return (((CodeWrapper*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

const char* lookupMethodCppSignatureByName(const char* qualifiedname) {
  { Slot* slot = NULL;
    Class* clasS = NULL;

    slot = lookupSlotAndClassByQualifiedName(qualifiedname, clasS);
    if (methodSlotP(slot)) {
      return (listSignatureToString(yieldMethodCppSignature(((MethodSlot*)(slot)), clasS->classType, true)));
    }
    else {
      return (NULL);
    }
  }
}

extern "C" const char* stella_lookupMethodCppSignatureByName(const char* qualifiedname) {
  // C-callable wrapper for `lookupMethodCppSignatureByName'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(lookupMethodCppSignatureByName(qualifiedname)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

const char* lookupMethodCSignatureByName(const char* qualifiedname) {
  { Slot* slot = NULL;
    Class* clasS = NULL;

    slot = lookupSlotAndClassByQualifiedName(qualifiedname, clasS);
    if (methodSlotP(slot)) {
      return (listSignatureToString(yieldMethodCSignature(((MethodSlot*)(slot)), clasS->classType)));
    }
    else {
      return (NULL);
    }
  }
}

extern "C" const char* stella_lookupMethodCSignatureByName(const char* qualifiedname) {
  // C-callable wrapper for `lookupMethodCSignatureByName'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(lookupMethodCSignatureByName(qualifiedname)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

const char* lookupStorageSlotCppSignatureByName(const char* qualifiedname) {
  { Slot* slot = NULL;
    Class* clasS = NULL;

    slot = lookupSlotAndClassByQualifiedName(qualifiedname, clasS);
    if (storageSlotP(slot)) {
      return (listSignatureToString(yieldStorageSlotCppSignature(((StorageSlot*)(slot)), clasS->classType, true)));
    }
    else {
      return (NULL);
    }
  }
}

extern "C" const char* stella_lookupStorageSlotCppSignatureByName(const char* qualifiedname) {
  // C-callable wrapper for `lookupStorageSlotCppSignatureByName'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(lookupStorageSlotCppSignatureByName(qualifiedname)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

const char* lookupStorageSlotCSignatureByName(const char* qualifiedname) {
  { Slot* slot = NULL;
    Class* clasS = NULL;

    slot = lookupSlotAndClassByQualifiedName(qualifiedname, clasS);
    if (storageSlotP(slot)) {
      return (listSignatureToString(yieldStorageSlotCSignature(((StorageSlot*)(slot)), clasS->classType)));
    }
    else {
      return (NULL);
    }
  }
}

extern "C" const char* stella_lookupStorageSlotCSignatureByName(const char* qualifiedname) {
  // C-callable wrapper for `lookupStorageSlotCSignatureByName'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(lookupStorageSlotCSignatureByName(qualifiedname)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

const char* lookupClassCppTypeByName(const char* qualifiedname) {
  // Return a namespace-qualified C++ translation of the class type
  // named by `qualifiedName' or NULL if no such STELLA class exists.
  { Class* clasS = lookupClassByQualifiedName(qualifiedname);

    if (((boolean)(clasS))) {
      { 
        BIND_STELLA_SPECIAL(oMODULEo, Module*, oROOT_MODULEo);
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
        return (cppTranslateAndPointerizeTypeSpec(clasS->classType)->wrapperValue);
      }
    }
    else {
      return (NULL);
    }
  }
}

extern "C" const char* stella_lookupClassCppTypeByName(const char* qualifiedname) {
  // C-callable wrapper for `lookupClassCppTypeByName'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(lookupClassCppTypeByName(qualifiedname)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

const char* lookupGlobalVariableCppSignatureByName(const char* qualifiedname) {
  { GlobalVariable* global = lookupGlobalVariableByQualifiedName(qualifiedname);

    if (((boolean)(global))) {
      return (listSignatureToString(yieldGlobalVariableCppSignature(global, true)));
    }
    else {
      return (NULL);
    }
  }
}

extern "C" const char* stella_lookupGlobalVariableCppSignatureByName(const char* qualifiedname) {
  // C-callable wrapper for `lookupGlobalVariableCppSignatureByName'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(lookupGlobalVariableCppSignatureByName(qualifiedname)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

const char* lookupGlobalVariableCSignatureByName(const char* qualifiedname) {
  { GlobalVariable* global = lookupGlobalVariableByQualifiedName(qualifiedname);

    if (((boolean)(global))) {
      return (listSignatureToString(yieldGlobalVariableCSignature(global)));
    }
    else {
      return (NULL);
    }
  }
}

extern "C" const char* stella_lookupGlobalVariableCSignatureByName(const char* qualifiedname) {
  // C-callable wrapper for `lookupGlobalVariableCSignatureByName'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(lookupGlobalVariableCSignatureByName(qualifiedname)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

// Handler to handle exceptions caught within a c-callable function that throws exceptions.
// If non-NULL the handler will be called with two string arguments: message and context.
// This is intended primarily for language environments that can't directly catch native
// exceptions (e.g., if we are in C or Python).
cpp_function_code oGLOBAL_EXCEPTION_HANDLERo = NULL;

cpp_function_code getGlobalExceptionHandler() {
  return (oGLOBAL_EXCEPTION_HANDLERo);
}

extern "C" cpp_function_code stella_getGlobalExceptionHandler() {
  // C-callable wrapper for `getGlobalExceptionHandler'.
  return (getGlobalExceptionHandler());
}

void setGlobalExceptionHandler(cpp_function_code handler) {
  oGLOBAL_EXCEPTION_HANDLERo = handler;
}

extern "C" void stella_setGlobalExceptionHandler(cpp_function_code handler) {
  // C-callable wrapper for `setGlobalExceptionHandler'.
  setGlobalExceptionHandler(handler);
}

void callGlobalExceptionHandler(std::exception* e) {
  { cpp_function_code handler = getGlobalExceptionHandler();

    if (handler != NULL) {
      ((void  (*) (const char*, const char*))handler)(exceptionMessage(e), exceptionContext(e));
    }
    else {
      throw *((std::runtime_error*)(e));
    }
  }
}

// Result buffer used to support temporary protection of garbage-collectable
// objects when a C API function is called from a non-C environment (such as Python).
void* oC_API_RESULT_BUFFERo = NULL;

void* gcProtectObject(void* object) {
  // Protect `object' from garbage collection.  Returns a handle that can later
  // be passed to `gc-release-object' to release `object' from garbage collection protection.
  
    void** handle = (void**)GC_MALLOC_UNCOLLECTABLE(sizeof(void*));
    *handle = object;
    return handle;
  return (object);
}

extern "C" void* stella_gcProtectObject(void* object) {
  // C-callable wrapper for `gcProtectObject'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(gcProtectObject(object)));
    return (((void*)(oC_API_RESULT_BUFFERo)));
  }
}

void* gcReleaseObject(void* handle) {
  // Release the object pointed to by `handle' from garbage collection protection
  // and return the protected object.  This frees `handle' but does not necessarily mean that the
  // object will be garbage collected, it just can be again, once all references to it disappear.
  
    void* object = *((void**)handle);
    *((void**)handle) = NULL;
    GC_FREE(handle);
    return object;
  return (handle);
}

extern "C" void* stella_gcReleaseObject(void* handle) {
  // C-callable wrapper for `gcReleaseObject'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(gcReleaseObject(handle)));
    return (((void*)(oC_API_RESULT_BUFFERo)));
  }
}

boolean commandP(MethodSlot* method) {
  // Return `true' if `method' is an evaluable command.
  return (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_COMMANDp, FALSE_WRAPPER)))->wrapperValue &&
      method->methodFunctionP);
}

MethodSlot* lookupCommand(Symbol* name) {
  // If `name' names an evaluable command return its associated
  // command object;  otherwise, return `null'.  Currently, commands are not
  // polymorphic, i.e., they can only be implemented by functions.
  { MethodSlot* function = lookupFunction(name);

    if (((boolean)(function)) &&
        commandP(function)) {
      return (function);
    }
    else {
      return (NULL);
    }
  }
}

MethodSlot* lookupCommandLikeFunction(Symbol* name) {
  // Look up a function with `name' that can be evaluated via `apply'
  // just like a command, regardless of whether it was marked as such.
  { MethodSlot* function = lookupFunction(name);

    if (((boolean)(function)) &&
        methodCallableViaApplyP(function)) {
      return (function);
    }
    else {
      return (NULL);
    }
  }
}

boolean methodMustBeEvaluableP(MethodSlot* method) {
  return (commandP(method) &&
      (!((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_NATIVEp, FALSE_WRAPPER)))->wrapperValue));
}

boolean methodCallableViaApplyP(MethodSlot* method) {
  { boolean testValue000 = false;

    if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue) {
      testValue000 = true;
    }
    else {
      if (method->methodParameterNames_reader()->length() > 10) {
        testValue000 = true;
      }
      else {
        if (method->methodReturnTypeSpecifiers_reader()->length() > 1) {
          testValue000 = true;
        }
        else {
          if (subtypeOfP(method->type(), SGT_WALK_STELLA_LITERAL)) {
            testValue000 = true;
          }
          else {
            { boolean foundP000 = false;

              { StandardObject* tspec = NULL;
                Cons* iter000 = method->methodParameterTypeSpecifiers_reader()->theConsList;

                for (; !(iter000 == NIL); iter000 = iter000->rest) {
                  tspec = ((StandardObject*)(iter000->value));
                  if (subtypeOfP(typeSpecToBaseType(tspec), SGT_WALK_STELLA_LITERAL)) {
                    foundP000 = true;
                    break;
                  }
                }
              }
              testValue000 = foundP000;
            }
          }
        }
      }
    }
    testValue000 = !testValue000;
    { boolean value000 = testValue000;

      return (value000);
    }
  }
}

boolean methodNeedsEvaluatorWrapperP(MethodSlot* method) {
  return (methodMustBeEvaluableP(method) &&
      (!methodCallableViaApplyP(method)));
}

Symbol* yieldEvaluatorWrapperName(Symbol* methodname) {
  { const char* baseName = methodname->symbolName;
    const char* suffix = (allUpperCaseStringP(baseName) ? "-EVALUATOR-WRAPPER" : "-Evaluator-Wrapper");

    return (internDerivedSymbol(methodname, stringConcatenate(baseName, suffix, 0)));
  }
}

Object* yieldArgumentAccessTree(Symbol* argumentsvariable, int index, boolean restargumentP) {
  { int limit = 5;
    Object* accesstree = argumentsvariable;

    if (index <= limit) {
      { int i = NULL_INTEGER;
        int iter000 = 2;
        int upperBound000 = index;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter000 <= upperBound000); 
              iter000 = iter000 + 1) {
          i = iter000;
          i = i;
          accesstree = listO(3, SYM_WALK_STELLA_REST, accesstree, NIL);
        }
      }
    }
    else {
      accesstree = listO(3, SYM_WALK_STELLA_NTH_REST, accesstree, cons(wrapInteger(index - 1), NIL));
    }
    if (!restargumentP) {
      if (index <= limit) {
        accesstree = listO(3, SYM_WALK_STELLA_VALUE, accesstree, NIL);
      }
      else {
        ((Cons*)(accesstree))->value = SYM_WALK_STELLA_NTH;
      }
    }
    return (accesstree);
  }
}

Cons* yieldEvaluatorWrapperTree(MethodSlot* method) {
  { StandardObject* dummy1;

    { Object* nametree = yieldEvaluatorWrapperName(method->slotName);
      Cons* calltree = cons(method->slotName, NIL);
      List* parametertypespecs = method->methodParameterTypeSpecifiers_reader();
      Surrogate* resulttype = method->type();
      int nofparameters = parametertypespecs->length();
      boolean variableargumentsP = ((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue;

      { int index = NULL_INTEGER;
        int iter000 = 1;
        int upperBound000 = nofparameters;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;
        Cons* collect000 = NULL;

        for  (; unboundedP000 ||
                  (iter000 <= upperBound000); 
              iter000 = iter000 + 1) {
          index = iter000;
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(yieldArgumentAccessTree(SYM_WALK_STELLA_ARGUMENTS, index, (index == nofparameters) &&
                  variableargumentsP), NIL);
              if (calltree == NIL) {
                calltree = collect000;
              }
              else {
                addConsToEndOfConsList(calltree, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(yieldArgumentAccessTree(SYM_WALK_STELLA_ARGUMENTS, index, (index == nofparameters) &&
                  variableargumentsP), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      { StandardObject* ptype = NULL;
        Cons* iter001 = parametertypespecs->theConsList;
        ConsIterator* it = calltree->rest->allocateIterator();

        for  (; (!(iter001 == NIL)) &&
                  it->nextP(); 
              iter001 = iter001->rest) {
          ptype = ((StandardObject*)(iter001->value));
          if (subTypeSpecOfP(ptype, SGT_WALK_STELLA_LITERAL)) {
            it->valueSetter(listO(3, SYM_WALK_STELLA_WRAPPER_VALUE, listO(3, SYM_WALK_STELLA_SAFE_CAST, it->value, cons(typeSpecToBaseType(ptype)->typeToWrappedType(), NIL)), NIL));
          }
          else if (subTypeSpecOfP(ptype, SGT_WALK_STELLA_ARGUMENT_LIST)) {
            pushVariableBinding(SYM_WALK_STELLA_ARGUMENTS, yieldListifiedVariableArgumentsType(method));
            it->valueSetter(sysTree(walkWithoutTypeTree(it->value), ptype, dummy1));
            popVariableBinding();
          }
          else if (!(ptype == SGT_WALK_STELLA_OBJECT)) {
            it->valueSetter(listO(3, SYM_WALK_STELLA_SAFE_CAST, it->value, cons(yieldTypeSpecTree(ptype), NIL)));
          }
        }
      }
      if (voidP(resulttype)) {
      }
      else if (subtypeOfP(resulttype, SGT_WALK_STELLA_LITERAL)) {
        nametree = cons(nametree, cons(resulttype->typeToWrappedType(), NIL));
        if (method->type() == SGT_WALK_STELLA_BOOLEAN) {
          calltree = listO(3, SYM_WALK_STELLA_RETURN, listO(3, SYM_WALK_STELLA_WRAP_BOOLEAN, calltree, NIL), NIL);
        }
        else {
          calltree = listO(4, SYM_WALK_STELLA_LET, cons(listO(3, SYM_WALK_STELLA_RESULT, calltree, NIL), NIL), listO(5, SYM_WALK_STELLA_IF, listO(3, SYM_WALK_STELLA_DEFINEDp, SYM_WALK_STELLA_RESULT, NIL), listO(3, SYM_WALK_STELLA_RETURN, listO(3, SYM_WALK_STELLA_WRAP_LITERAL, SYM_WALK_STELLA_RESULT, NIL), NIL), listO(3, SYM_WALK_STELLA_RETURN, SYM_WALK_STELLA_NULL, NIL), NIL), NIL);
        }
      }
      else {
        nametree = cons(nametree, cons(resulttype, NIL));
        calltree = listO(3, SYM_WALK_STELLA_RETURN, calltree, NIL);
      }
      return (listO(3, SYM_WALK_STELLA_DEFUN, nametree, listO(4, cons(listO(3, SYM_WALK_STELLA_ARGUMENTS, SYM_WALK_STELLA_CONS, NIL), NIL), KWD_WALK_AUXILIARYp, SYM_WALK_STELLA_TRUE, (((nofparameters == 0) ? cons(listO(3, SYM_WALK_STELLA_IGNORE, SYM_WALK_STELLA_ARGUMENTS, NIL), NIL) : NIL))->concatenate(cons(calltree, NIL), 0))));
    }
  }
}

MethodSlot* createEvaluatorWrapperUnit(MethodSlot* method) {
  { boolean variableargumentsP = ((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue;
    boolean evaluateargumentsP = method->methodEvaluateArgumentsP_reader();
    Cons* wrappertree = yieldEvaluatorWrapperTree(method);
    MethodSlot* wrappermethod = NULL;

    if (method->methodReturnTypeSpecifiers_reader()->length() > 1) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationWarning();
        if (!(suppressWarningsP())) {
          printErrorContext(">> WARNING: ", STANDARD_WARNING);
          *(STANDARD_WARNING->nativeStream) << std::endl << " " << "During interpreted command evaluation only the" << std::endl << " first return value will be usable" << "." << std::endl;
        }
      }
    }
    if (!evaluateargumentsP) {
      setDynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_EVALUATE_ARGUMENTSp, TRUE_WRAPPER, FALSE_WRAPPER);
    }
    if (variableargumentsP) {
      setDynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER, FALSE_WRAPPER);
    }
    wrappermethod = ((MethodSlot*)(helpWalkAuxiliaryTree(wrappertree, true)->theObject));
    if (!evaluateargumentsP) {
      setDynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_EVALUATE_ARGUMENTSp, FALSE_WRAPPER, FALSE_WRAPPER);
    }
    if (variableargumentsP) {
      setDynamicSlotValue(method->dynamicSlots, SYM_WALK_STELLA_METHOD_VARIABLE_ARGUMENTSp, TRUE_WRAPPER, FALSE_WRAPPER);
    }
    return (wrappermethod);
  }
}

DEFINE_STELLA_SPECIAL(oEVALUATIONTREEo, Object* , NULL);

DEFINE_STELLA_SPECIAL(oEVALUATIONPARENTTREEo, Object* , NULL);

Object* evaluate(Object* expression) {
  // Evaluate the expression `expression' and return the result.
  // Currently, only the evaluation of (possibly nested) commands and global
  // variables is supported.  The second return value indicates the actual type 
  // of the result (which might have been wrapped), and the third return value
  // indicates whether an error occurred during the evaluation.  Expressions
  // are simple to program in Common Lisp, since they are built into the language,
  // and relatively awkward in Java and C++.  Users of either of those 
  // languages are more likely to want to call `evaluate-string'.
  { StandardObject* dummy1;
    StandardObject* dummy2;

    { Object* otree = NULL;

      if (((boolean)(expression))) {
        if (safePrimaryType(expression) == SGT_WALK_STELLA_CONS) {
          { Object* expression000 = expression;
            Cons* expression = ((Cons*)(expression000));

            otree = evaluateConsTree(expression, dummy1);
          }
        }
        else {
          otree = evaluateAtomicTree(expression, dummy2);
        }
      }
      return (otree);
    }
  }
}

Object* evaluateString(const char* expression) {
  // Evaluate the expression represented by `expression' and return the result.
  // This is equivalent to '(evaluate (unstringify expression))'.
  return (evaluate(readSExpressionFromString(expression)));
}

Object* tryToEvaluate(Object* tree) {
  // Variant of `evaluate' that only evaluates `tree' if it
  // represents an evaluable expression.  If it does not, `tree' is returned
  // unmodified.  This can be used to implement commands with mixed argument
  // evaluation strategies.
  { StandardObject* dummy1;

    { Object* otree = tree;

      if (((boolean)(tree))) {
        if (safePrimaryType(tree) == SGT_WALK_STELLA_CONS) {
          { Object* tree000 = tree;
            Cons* tree = ((Cons*)(tree000));

            if (symbolP(tree->value) &&
                ((boolean)(lookupCommand(((Symbol*)(tree->value)))))) {
              try {
                otree = evaluateConsTree(tree, dummy1);
              }
              catch (StellaException& _e) {
                StellaException* e = &_e;

                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  signalTranslationError();
                  if (!(suppressWarningsP())) {
                    printErrorContext(">> ERROR: ", STANDARD_ERROR);
                    *(STANDARD_ERROR->nativeStream) << std::endl << " " << "`" << exceptionMessage(e) << "'" << "." << std::endl;
                  }
                }
              }
            }
          }
        }
        else {
        }
      }
      return (otree);
    }
  }
}

Object* evaluateConsTree(Cons* tree, StandardObject*& _Return1) {
  { StandardObject* dummy1;
    StandardObject* dummy2;
    StandardObject* dummy3;
    StandardObject* dummy4;

    { 
      BIND_STELLA_SPECIAL(oEVALUATIONPARENTTREEo, Object*, oEVALUATIONTREEo);
      BIND_STELLA_SPECIAL(oEVALUATIONTREEo, Object*, tree);
      { Object* operatorname = tree->value;
        Cons* arguments = tree->rest;
        MethodSlot* operatoR = NULL;

        if (subtypeOfSymbolP(safePrimaryType(operatorname))) {
          { Object* operatorname000 = operatorname;
            Symbol* operatorname = ((Symbol*)(operatorname000));

            if (operatorname == SYM_WALK_STELLA_QUOTE) {
              if (arguments->length() == 1) {
                { Object* _Return0 = arguments->value;

                  _Return1 = arguments->value->primaryType();
                  return (_Return0);
                }
              }
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "While evaluating '" << oEVALUATIONTREEo;
                if (((boolean)(oEVALUATIONPARENTTREEo))) {
                  *(stream000->nativeStream) << std::endl << "' inside '" << oEVALUATIONPARENTTREEo;
                }
                *(stream000->nativeStream) << "':" << std::endl;
                *(stream000->nativeStream) << "Illegal QUOTE expression";
                throw *newEvaluationException(stream000->theStringReader());
              }
            }
            else if (operatorname == SYM_WALK_STELLA_BQUOTE) {
              return (evaluateBquoteTree(tree, _Return1));
            }
            else if (operatorname == SYM_WALK_STELLA_CONS) {
              { Object* arg1 = evaluateArgumentTree(arguments->value, true, dummy1);
                Object* arg2 = evaluateArgumentTree(arguments->rest->value, true, dummy2);

                if (consP(arg2) &&
                    (arguments->rest->rest == NIL)) {
                  { Object* _Return0 = cons(arg1, ((Cons*)(arg2)));

                    _Return1 = SGT_WALK_STELLA_CONS;
                    return (_Return0);
                  }
                }
                { OutputStringStream* stream001 = newOutputStringStream();

                  *(stream001->nativeStream) << "While evaluating '" << oEVALUATIONTREEo;
                  if (((boolean)(oEVALUATIONPARENTTREEo))) {
                    *(stream001->nativeStream) << std::endl << "' inside '" << oEVALUATIONPARENTTREEo;
                  }
                  *(stream001->nativeStream) << "':" << std::endl;
                  *(stream001->nativeStream) << "Illegal CONS expression";
                  throw *newEvaluationException(stream001->theStringReader());
                }
              }
            }
            else if (operatorname == SYM_WALK_STELLA_APPEND) {
              { Object* arg1 = evaluateArgumentTree(arguments->value, true, dummy3);
                Object* arg2 = evaluateArgumentTree(arguments->rest->value, true, dummy4);

                if (consP(arg1) &&
                    (consP(arg2) &&
                     (arguments->rest->rest == NIL))) {
                  { Object* _Return0 = append(((Cons*)(arg1)), ((Cons*)(arg2)));

                    _Return1 = SGT_WALK_STELLA_CONS;
                    return (_Return0);
                  }
                }
                { OutputStringStream* stream002 = newOutputStringStream();

                  *(stream002->nativeStream) << "While evaluating '" << oEVALUATIONTREEo;
                  if (((boolean)(oEVALUATIONPARENTTREEo))) {
                    *(stream002->nativeStream) << std::endl << "' inside '" << oEVALUATIONPARENTTREEo;
                  }
                  *(stream002->nativeStream) << "':" << std::endl;
                  *(stream002->nativeStream) << "Illegal APPEND expression";
                  throw *newEvaluationException(stream002->theStringReader());
                }
              }
            }
            else if (operatorname == SYM_WALK_STELLA_SETQ) {
              if (arguments->length() == 2) {
                { Object* varname = arguments->value;
                  Object* value = arguments->rest->value;
                  StandardObject* valuetype = NULL;
                  GlobalVariable* global = NULL;

                  if (symbolP(varname)) {
                    global = ((Symbol*)(varname))->lookupGlobalVariable();
                    if (!((boolean)(global))) {
                      { OutputStringStream* stream003 = newOutputStringStream();

                        *(stream003->nativeStream) << "While evaluating '" << oEVALUATIONTREEo;
                        if (((boolean)(oEVALUATIONPARENTTREEo))) {
                          *(stream003->nativeStream) << std::endl << "' inside '" << oEVALUATIONPARENTTREEo;
                        }
                        *(stream003->nativeStream) << "':" << std::endl;
                        *(stream003->nativeStream) << "Undefined global variable: " << "`" << varname << "'";
                        throw *newEvaluationException(stream003->theStringReader());
                      }
                    }
                    value = evaluateArgumentTree(value, true, valuetype);
                    writeGlobalVariableValue(global, value);
                    _Return1 = valuetype;
                    return (value);
                  }
                }
              }
              { OutputStringStream* stream004 = newOutputStringStream();

                *(stream004->nativeStream) << "While evaluating '" << oEVALUATIONTREEo;
                if (((boolean)(oEVALUATIONPARENTTREEo))) {
                  *(stream004->nativeStream) << std::endl << "' inside '" << oEVALUATIONPARENTTREEo;
                }
                *(stream004->nativeStream) << "':" << std::endl;
                *(stream004->nativeStream) << "Illegal SETQ expression";
                throw *newEvaluationException(stream004->theStringReader());
              }
            }
            else if (operatorname == SYM_WALK_STELLA_PROGN) {
              { Object* arg = NULL;
                Cons* iter000 = arguments;

                for (; !(iter000 == NIL); iter000 = iter000->rest) {
                  arg = iter000->value;
                  evaluate(arg);
                }
              }
              _Return1 = SGT_WALK_STELLA_VOID;
              return (NULL);
            }
            else {
              operatoR = lookupCommand(operatorname);
              if (!((boolean)(operatoR))) {
                operatoR = lookupCommandLikeFunction(operatorname);
              }
              if (!((boolean)(operatoR))) {
                { OutputStringStream* stream005 = newOutputStringStream();

                  *(stream005->nativeStream) << "While evaluating '" << oEVALUATIONTREEo;
                  if (((boolean)(oEVALUATIONPARENTTREEo))) {
                    *(stream005->nativeStream) << std::endl << "' inside '" << oEVALUATIONPARENTTREEo;
                  }
                  *(stream005->nativeStream) << "':" << std::endl;
                  *(stream005->nativeStream) << "Undefined operator: " << "`" << operatorname << "'";
                  throw *newEvaluationException(stream005->theStringReader());
                }
              }
            }
          }
        }
        else {
          { OutputStringStream* stream006 = newOutputStringStream();

            *(stream006->nativeStream) << "While evaluating '" << oEVALUATIONTREEo;
            if (((boolean)(oEVALUATIONPARENTTREEo))) {
              *(stream006->nativeStream) << std::endl << "' inside '" << oEVALUATIONPARENTTREEo;
            }
            *(stream006->nativeStream) << "':" << std::endl;
            *(stream006->nativeStream) << "Illegal operator: " << "`" << operatorname << "'";
            throw *newEvaluationException(stream006->theStringReader());
          }
        }
        { cpp_function_code evaluatorwrappercode = ((FunctionCodeWrapper*)(dynamicSlotValue(operatoR->dynamicSlots, SYM_WALK_STELLA_EVALUATOR_WRAPPER_CODE, NULL_FUNCTION_CODE_WRAPPER)))->wrapperValue;
          boolean evaluateargsP = operatoR->methodEvaluateArgumentsP_reader();
          boolean variableargsP = ((BooleanWrapper*)(dynamicSlotValue(operatoR->dynamicSlots, SYM_WALK_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue;
          List* parametertypes = operatoR->methodParameterTypeSpecifiers_reader();
          int nofparameters = parametertypes->length();
          int nofargs = arguments->length();
          int minargs = (variableargsP ? (nofparameters - 1) : nofparameters);
          int maxargs = (variableargsP ? ((int)(NULL_INTEGER)) : nofparameters);
          Cons* unevaluatedargs = arguments;
          Object* evaluatedarg = NULL;
          StandardObject* evaluatedargtype = NULL;
          int argindex = 0;
          Surrogate* returntype = operatoR->type();
          Object* result = NULL;

          if ((nofargs < minargs) ||
              ((maxargs != NULL_INTEGER) &&
               (nofargs > maxargs))) {
            { const char* minstring = integerToString(((long long int)(minargs)));
              const char* maxstring = "";

              if (maxargs == NULL_INTEGER) {
                maxstring = "+";
              }
              else if (maxargs > minargs) {
                maxstring = stringConcatenate("-", integerToString(((long long int)(maxargs))));
              }
              { OutputStringStream* stream007 = newOutputStringStream();

                *(stream007->nativeStream) << "While evaluating '" << oEVALUATIONTREEo;
                if (((boolean)(oEVALUATIONPARENTTREEo))) {
                  *(stream007->nativeStream) << std::endl << "' inside '" << oEVALUATIONPARENTTREEo;
                }
                *(stream007->nativeStream) << "':" << std::endl;
                *(stream007->nativeStream) << "Wrong number of arguments.  Expected " << "`" << minstring << "'" << "`" << maxstring << "'" << " but got " << "`" << nofargs << "'";
                throw *newEvaluationException(stream007->theStringReader());
              }
            }
          }
          while (!(unevaluatedargs == NIL)) {
            evaluatedarg = evaluateArgumentTree(unevaluatedargs->value, evaluateargsP, evaluatedargtype);
            evaluatedarg = coerceEvaluatedTree(evaluatedarg, unevaluatedargs->value, evaluatedargtype, ((argindex >= minargs) ? variableArgumentsType(operatoR) : ((StandardObject*)(parametertypes->nth(argindex)))), evaluateargsP, evaluatedargtype);
            unevaluatedargs->value = evaluatedarg;
            unevaluatedargs = unevaluatedargs->rest;
            argindex = argindex + 1;
          }
          if (evaluatorwrappercode != NULL) {
            if (voidP(returntype)) {
              ((void  (*) (Cons*))evaluatorwrappercode)(arguments);
            }
            else {
              result = ((Object*  (*) (Cons*))evaluatorwrappercode)(arguments);
            }
          }
          else {
            if (voidP(returntype)) {
              apply(operatoR->functionCode, arguments);
            }
            else {
              result = apply(operatoR->functionCode, arguments);
            }
          }
          if (((boolean)(result))) {
            returntype = result->primaryType();
          }
          _Return1 = returntype;
          return (result);
        }
      }
    }
  }
}

Object* evaluateArgumentTree(Object* tree, boolean evaluateP, StandardObject*& _Return1) {
  { Surrogate* testValue000 = safePrimaryType(tree);

    if (testValue000 == SGT_WALK_STELLA_CONS) {
      { Object* tree000 = tree;
        Cons* tree = ((Cons*)(tree000));

        if (evaluateP) {
          return (evaluateConsTree(tree, _Return1));
        }
        else {
          _Return1 = SGT_WALK_STELLA_CONS;
          return (tree);
        }
      }
    }
    else if (subtypeOfWrapperP(testValue000)) {
      { Object* tree001 = tree;
        Wrapper* tree = ((Wrapper*)(tree001));

        { Object* _Return0 = tree;

          _Return1 = wrappedTypeToType(tree->primaryType());
          return (_Return0);
        }
      }
    }
    else {
      if (evaluateP) {
        return (evaluateAtomicTree(tree, _Return1));
      }
      else {
        { Object* _Return0 = tree;

          _Return1 = tree->primaryType();
          return (_Return0);
        }
      }
    }
  }
}

Object* evaluateAtomicTree(Object* tree, StandardObject*& _Return1) {
  { 
    BIND_STELLA_SPECIAL(oEVALUATIONPARENTTREEo, Object*, oEVALUATIONTREEo);
    BIND_STELLA_SPECIAL(oEVALUATIONTREEo, Object*, tree);
    { Surrogate* testValue000 = safePrimaryType(tree);

      if (subtypeOfSymbolP(testValue000)) {
        { Object* tree000 = tree;
          Symbol* tree = ((Symbol*)(tree000));

          if (tree == SYM_WALK_STELLA_NULL) {
            _Return1 = SGT_WALK_STELLA_UNKNOWN;
            return (tree);
          }
          else if (tree == SYM_WALK_STELLA_NIL) {
            _Return1 = SGT_WALK_STELLA_CONS;
            return (NIL);
          }
          else if (tree == SYM_WALK_STELLA_TRUE) {
            _Return1 = SGT_WALK_STELLA_BOOLEAN;
            return (TRUE_WRAPPER);
          }
          else if (tree == SYM_WALK_STELLA_FALSE) {
            _Return1 = SGT_WALK_STELLA_BOOLEAN;
            return (FALSE_WRAPPER);
          }
          else {
            { GlobalVariable* global = tree->lookupGlobalVariable();

              if (((boolean)(global))) {
                { Object* _Return0 = readGlobalVariableValue(global);

                  _Return1 = ((StandardObject*)(dynamicSlotValue(global->dynamicSlots, SYM_WALK_STELLA_VARIABLE_TYPE_SPECIFIER, NULL)));
                  return (_Return0);
                }
              }
              else {
                { OutputStringStream* stream000 = newOutputStringStream();

                  *(stream000->nativeStream) << "While evaluating '" << oEVALUATIONTREEo;
                  if (((boolean)(oEVALUATIONPARENTTREEo))) {
                    *(stream000->nativeStream) << std::endl << "' inside '" << oEVALUATIONPARENTTREEo;
                  }
                  *(stream000->nativeStream) << "':" << std::endl;
                  *(stream000->nativeStream) << "Undefined variable: " << "`" << tree << "'";
                  throw *newEvaluationException(stream000->theStringReader());
                }
              }
            }
          }
        }
      }
      else if (subtypeOfSurrogateP(testValue000)) {
        { Object* tree001 = tree;
          Surrogate* tree = ((Surrogate*)(tree001));

          _Return1 = SGT_WALK_STELLA_SURROGATE;
          return (tree);
        }
      }
      else if (subtypeOfKeywordP(testValue000)) {
        { Object* tree002 = tree;
          Keyword* tree = ((Keyword*)(tree002));

          _Return1 = SGT_WALK_STELLA_KEYWORD;
          return (tree);
        }
      }
      else if (subtypeOfWrapperP(testValue000)) {
        { Object* tree003 = tree;
          Wrapper* tree = ((Wrapper*)(tree003));

          { Object* _Return0 = tree;

            _Return1 = wrappedTypeToType(tree->primaryType());
            return (_Return0);
          }
        }
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "While evaluating '" << oEVALUATIONTREEo;
          if (((boolean)(oEVALUATIONPARENTTREEo))) {
            *(stream001->nativeStream) << std::endl << "' inside '" << oEVALUATIONPARENTTREEo;
          }
          *(stream001->nativeStream) << "':" << std::endl;
          *(stream001->nativeStream) << "Unknown atomic expression type: " << "`" << tree << "'";
          throw *newEvaluationException(stream001->theStringReader());
        }
      }
    }
  }
}

Object* makeEvaluatableBquoteTree(Object* tree) {
  if (safePrimaryType(tree) == SGT_WALK_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

        if (testValue000 == SYM_WALK_STELLA_GET_SYM) {
          return (listO(3, SYM_WALK_STELLA_QUOTE, getSym(((IntegerWrapper*)(tree->rest->value))->wrapperValue), NIL));
        }
        else if (testValue000 == SYM_WALK_STELLA_GET_SGT) {
          return (getSgt(((IntegerWrapper*)(tree->rest->value))->wrapperValue));
        }
        else if (testValue000 == SYM_WALK_STELLA_GET_KWD) {
          return (getKwd(((IntegerWrapper*)(tree->rest->value))->wrapperValue));
        }
        else {
          { Cons* args = NIL;

            { Object* arg = NULL;
              Cons* iter000 = tree->rest;
              Cons* collect000 = NULL;

              for  (; !(iter000 == NIL); 
                    iter000 = iter000->rest) {
                arg = iter000->value;
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(makeEvaluatableBquoteTree(arg), NIL);
                    if (args == NIL) {
                      args = collect000;
                    }
                    else {
                      addConsToEndOfConsList(args, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000->rest = cons(makeEvaluatableBquoteTree(arg), NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
            { GeneralizedSymbol* testValue001 = ((GeneralizedSymbol*)(tree->value));

              if (testValue001 == SYM_WALK_STELLA_LISTo) {
                if (args->rest == NIL) {
                  return (args->value);
                }
                args = args->reverse();
                { Cons* constree = listO(3, SYM_WALK_STELLA_CONS, args->rest->value, cons(args->value, NIL));

                  { Object* arg = NULL;
                    Cons* iter001 = args->rest->rest;

                    for (; !(iter001 == NIL); iter001 = iter001->rest) {
                      arg = iter001->value;
                      constree = listO(3, SYM_WALK_STELLA_CONS, arg, cons(constree, NIL));
                    }
                  }
                  return (constree);
                }
              }
              else if (testValue001 == SYM_WALK_STELLA_CONCATENATE) {
                return (listO(3, SYM_WALK_STELLA_APPEND, args->value, cons(args->rest->value, NIL)));
              }
              else if (testValue001 == SYM_WALK_STELLA_WRAP_LITERAL) {
                return (args->value);
              }
              else {
                return (cons(tree->value, args));
              }
            }
          }
        }
      }
    }
  }
  else {
    return (tree);
  }
}

Object* evaluateBquoteTree(Cons* tree, StandardObject*& _Return1) {
  { Object* argtree = NULL;

    { 
      BIND_STELLA_SPECIAL(oUSEHARDCODEDSYMBOLSpo, boolean, true);
      argtree = makeEvaluatableBquoteTree(expandBquoteTree(tree->rest->value));
    }
    return (evaluateArgumentTree(argtree, true, _Return1));
  }
}

Object* coerceEvaluatedTree(Object* tree, Object* sourcetree, StandardObject* sourcetype, StandardObject* targettype, boolean evaluateP, StandardObject*& _Return1) {
  { 
    BIND_STELLA_SPECIAL(oEVALUATIONPARENTTREEo, Object*, oEVALUATIONTREEo);
    BIND_STELLA_SPECIAL(oEVALUATIONTREEo, Object*, sourcetree);
    { Surrogate* sourcebasetype = typeSpecToBaseType(sourcetype);
      Surrogate* targetbasetype = typeSpecToBaseType(targettype);

      if ((!((boolean)(tree))) ||
          (tree == SYM_WALK_STELLA_NULL)) {
        { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(targettype));

          if (testValue000 == SGT_WALK_STELLA_INTEGER) {
            _Return1 = targettype;
            return (NULL_INTEGER_WRAPPER);
          }
          else if (testValue000 == SGT_WALK_STELLA_LONG_INTEGER) {
            _Return1 = targettype;
            return (NULL_LONG_INTEGER_WRAPPER);
          }
          else if (testValue000 == SGT_WALK_STELLA_FLOAT) {
            _Return1 = targettype;
            return (NULL_FLOAT_WRAPPER);
          }
          else if (testValue000 == SGT_WALK_STELLA_STRING) {
            _Return1 = targettype;
            return (NULL_STRING_WRAPPER);
          }
          else if (testValue000 == SGT_WALK_STELLA_BOOLEAN) {
            _Return1 = targettype;
            return (FALSE_WRAPPER);
          }
          else {
            _Return1 = targettype;
            return (NULL);
          }
        }
      }
      if ((targettype == SGT_WALK_STELLA_BOOLEAN) &&
          (!evaluateP)) {
        if (tree == SYM_WALK_STELLA_TRUE) {
          _Return1 = targettype;
          return (TRUE_WRAPPER);
        }
        if (tree == SYM_WALK_STELLA_FALSE) {
          _Return1 = targettype;
          return (FALSE_WRAPPER);
        }
      }
      if (subtypeOfP(sourcebasetype, targetbasetype)) {
        _Return1 = sourcetype;
        return (tree);
      }
      if (((!evaluateP) ||
          isaP(tree, SGT_WALK_STELLA_WRAPPER)) &&
          (subtypeOfP(sourcebasetype, SGT_WALK_STELLA_LITERAL) &&
           subtypeOfP(sourcebasetype->typeToWrappedType(), targetbasetype))) {
        { Object* _Return0 = tree;

          _Return1 = sourcebasetype->typeToWrappedType();
          return (_Return0);
        }
      }
      if (subtypeOfP(targetbasetype, SGT_WALK_STELLA_LITERAL) &&
          subtypeOfP(sourcebasetype, targetbasetype->typeToWrappedType())) {
        _Return1 = targettype;
        return (tree);
      }
      if (voidP(sourcetype)) {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "While evaluating '" << oEVALUATIONTREEo;
          if (((boolean)(oEVALUATIONPARENTTREEo))) {
            *(stream000->nativeStream) << std::endl << "' inside '" << oEVALUATIONPARENTTREEo;
          }
          *(stream000->nativeStream) << "':" << std::endl;
          *(stream000->nativeStream) << "`" << sourcetree << "'" << " does not return a value";
          throw *newEvaluationException(stream000->theStringReader());
        }
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "While evaluating '" << oEVALUATIONTREEo;
          if (((boolean)(oEVALUATIONPARENTTREEo))) {
            *(stream001->nativeStream) << std::endl << "' inside '" << oEVALUATIONPARENTTREEo;
          }
          *(stream001->nativeStream) << "':" << std::endl;
          *(stream001->nativeStream) << "Type conflict: " << "`" << yieldTypeSpecTree(sourcetype) << "'" << " found where " << "`" << yieldTypeSpecTree(targettype) << "'" << " expected";
          throw *newEvaluationException(stream001->theStringReader());
        }
      }
    }
  }
}

void helpStartupWalk1() {
  {
    KWD_WALK_WARN_ABOUT_UNDEFINED_METHODS = ((Keyword*)(internRigidSymbolWrtModule("WARN-ABOUT-UNDEFINED-METHODS", NULL, 2)));
    KWD_WALK_WARN_ABOUT_MISSING_METHODS = ((Keyword*)(internRigidSymbolWrtModule("WARN-ABOUT-MISSING-METHODS", NULL, 2)));
    KWD_WALK_SUPPRESS_WARNINGS = ((Keyword*)(internRigidSymbolWrtModule("SUPPRESS-WARNINGS", NULL, 2)));
    KWD_WALK_USE_HARDCODED_SYMBOLS = ((Keyword*)(internRigidSymbolWrtModule("USE-HARDCODED-SYMBOLS", NULL, 2)));
    KWD_WALK_USE_COMMON_LISP_STRUCTS = ((Keyword*)(internRigidSymbolWrtModule("USE-COMMON-LISP-STRUCTS", NULL, 2)));
    KWD_WALK_USE_COMMON_LISP_CONSES = ((Keyword*)(internRigidSymbolWrtModule("USE-COMMON-LISP-CONSES", NULL, 2)));
    KWD_WALK_USE_CPP_GARBAGE_COLLECTOR = ((Keyword*)(internRigidSymbolWrtModule("USE-CPP-GARBAGE-COLLECTOR", NULL, 2)));
    KWD_WALK_MINIMIZE_JAVA_PREFIXES = ((Keyword*)(internRigidSymbolWrtModule("MINIMIZE-JAVA-PREFIXES", NULL, 2)));
    KWD_WALK_TRANSLATE_WITH_COPYRIGHT_HEADER = ((Keyword*)(internRigidSymbolWrtModule("TRANSLATE-WITH-COPYRIGHT-HEADER", NULL, 2)));
    KWD_WALK_SUPPORT_UNEXEC = ((Keyword*)(internRigidSymbolWrtModule("SUPPORT-UNEXEC", NULL, 2)));
    KWD_WALK_USE_COMMON_LISP_VECTOR_STRUCTS = ((Keyword*)(internRigidSymbolWrtModule("USE-COMMON-LISP-VECTOR-STRUCTS", NULL, 2)));
    SGT_WALK_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SYM_WALK_STELLA_MEMBp = ((Symbol*)(internRigidSymbolWrtModule("MEMB?", NULL, 0)));
    SYM_WALK_STELLA_oTRACED_KEYWORDSo = ((Symbol*)(internRigidSymbolWrtModule("*TRACED-KEYWORDS*", NULL, 0)));
    SGT_WALK_STELLA_VOID = ((Surrogate*)(internRigidSymbolWrtModule("VOID", NULL, 1)));
    SYM_WALK_STELLA_OR = ((Symbol*)(internRigidSymbolWrtModule("OR", NULL, 0)));
    SYM_WALK_STELLA_WHEN = ((Symbol*)(internRigidSymbolWrtModule("WHEN", NULL, 0)));
    SYM_WALK_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", NULL, 0)));
    SYM_WALK_STELLA_DEFINEDp = ((Symbol*)(internRigidSymbolWrtModule("DEFINED?", NULL, 0)));
    SYM_WALK_STELLA_PRINT = ((Symbol*)(internRigidSymbolWrtModule("PRINT", NULL, 0)));
    SYM_WALK_STELLA_EOL = ((Symbol*)(internRigidSymbolWrtModule("EOL", NULL, 0)));
    KWD_WALK_COMMON_LISP = ((Keyword*)(internRigidSymbolWrtModule("COMMON-LISP", NULL, 2)));
    SYM_WALK_STELLA_FLUSH_OUTPUT = ((Symbol*)(internRigidSymbolWrtModule("FLUSH-OUTPUT", NULL, 0)));
    SYM_WALK_STELLA_STANDARD_OUTPUT = ((Symbol*)(internRigidSymbolWrtModule("STANDARD-OUTPUT", NULL, 0)));
    KWD_WALK_JAVA = ((Keyword*)(internRigidSymbolWrtModule("JAVA", NULL, 2)));
    SGT_WALK_STELLA_F_GET_QUOTED_TREE_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-GET-QUOTED-TREE-MEMO-TABLE-000", NULL, 1)));
    SGT_WALK_STELLA_TRANSLATION_UNIT = ((Surrogate*)(internRigidSymbolWrtModule("TRANSLATION-UNIT", NULL, 1)));
    SYM_WALK_STELLA_HOME_MODULE = ((Symbol*)(internRigidSymbolWrtModule("HOME-MODULE", NULL, 0)));
    SYM_WALK_STELLA_TU_HOME_MODULE = ((Symbol*)(internRigidSymbolWrtModule("TU-HOME-MODULE", NULL, 0)));
    SYM_WALK_STELLA_THE_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("THE-OBJECT", NULL, 0)));
    SYM_WALK_STELLA_CATEGORY = ((Symbol*)(internRigidSymbolWrtModule("CATEGORY", NULL, 0)));
    SYM_WALK_STELLA_ANNOTATION = ((Symbol*)(internRigidSymbolWrtModule("ANNOTATION", NULL, 0)));
    SYM_WALK_STELLA_AUXILIARYp = ((Symbol*)(internRigidSymbolWrtModule("AUXILIARY?", NULL, 0)));
    SYM_WALK_STELLA_CODE_REGISTER = ((Symbol*)(internRigidSymbolWrtModule("CODE-REGISTER", NULL, 0)));
    SYM_WALK_STELLA_TRANSLATION = ((Symbol*)(internRigidSymbolWrtModule("TRANSLATION", NULL, 0)));
    SYM_WALK_STELLA_REFERENCED_GLOBALS = ((Symbol*)(internRigidSymbolWrtModule("REFERENCED-GLOBALS", NULL, 0)));
    SYM_WALK_STELLA_CLASS = ((Symbol*)(internRigidSymbolWrtModule("CLASS", NULL, 0)));
    SYM_WALK_STELLA_METHOD = ((Symbol*)(internRigidSymbolWrtModule("METHOD", NULL, 0)));
    SYM_WALK_STELLA_GLOBAL_VARIABLE = ((Symbol*)(internRigidSymbolWrtModule("GLOBAL-VARIABLE", NULL, 0)));
    KWD_WALK_CPP = ((Keyword*)(internRigidSymbolWrtModule("CPP", NULL, 2)));
    KWD_WALK_CPP_STANDALONE = ((Keyword*)(internRigidSymbolWrtModule("CPP-STANDALONE", NULL, 2)));
    KWD_WALK_IDL = ((Keyword*)(internRigidSymbolWrtModule("IDL", NULL, 2)));
    SYM_WALK_STELLA_PROGN = ((Symbol*)(internRigidSymbolWrtModule("PROGN", NULL, 0)));
    SYM_WALK_STELLA_DEFCLASS = ((Symbol*)(internRigidSymbolWrtModule("DEFCLASS", NULL, 0)));
    SYM_WALK_STELLA_DEFSLOT = ((Symbol*)(internRigidSymbolWrtModule("DEFSLOT", NULL, 0)));
    SYM_WALK_STELLA_DEFMETHOD = ((Symbol*)(internRigidSymbolWrtModule("DEFMETHOD", NULL, 0)));
    SYM_WALK_STELLA_DEFUN = ((Symbol*)(internRigidSymbolWrtModule("DEFUN", NULL, 0)));
    SYM_WALK_STELLA_DEFOPERATOR = ((Symbol*)(internRigidSymbolWrtModule("DEFOPERATOR", NULL, 0)));
    SYM_WALK_STELLA_DEFGLOBAL = ((Symbol*)(internRigidSymbolWrtModule("DEFGLOBAL", NULL, 0)));
    SYM_WALK_STELLA_DEFSPECIAL = ((Symbol*)(internRigidSymbolWrtModule("DEFSPECIAL", NULL, 0)));
    SYM_WALK_STELLA_DEFCONSTANT = ((Symbol*)(internRigidSymbolWrtModule("DEFCONSTANT", NULL, 0)));
    SYM_WALK_STELLA_DEFTYPE = ((Symbol*)(internRigidSymbolWrtModule("DEFTYPE", NULL, 0)));
    SYM_WALK_STELLA_DEFMODULE = ((Symbol*)(internRigidSymbolWrtModule("DEFMODULE", NULL, 0)));
    SYM_WALK_STELLA_DEFMACRO = ((Symbol*)(internRigidSymbolWrtModule("DEFMACRO", NULL, 0)));
    SYM_WALK_STELLA_STARTUP_TIME_PROGN = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-TIME-PROGN", NULL, 0)));
    SYM_WALK_STELLA_VERBATIM = ((Symbol*)(internRigidSymbolWrtModule("VERBATIM", NULL, 0)));
    SYM_WALK_STELLA_MODULE = ((Symbol*)(internRigidSymbolWrtModule("MODULE", NULL, 0)));
    SYM_WALK_STELLA_TYPE = ((Symbol*)(internRigidSymbolWrtModule("TYPE", NULL, 0)));
    SYM_WALK_STELLA_PRINT_METHOD = ((Symbol*)(internRigidSymbolWrtModule("PRINT-METHOD", NULL, 0)));
    SYM_WALK_STELLA_SLOT = ((Symbol*)(internRigidSymbolWrtModule("SLOT", NULL, 0)));
  }
}

void helpStartupWalk2() {
  {
    KWD_WALK_JAVA_STANDALONE = ((Keyword*)(internRigidSymbolWrtModule("JAVA-STANDALONE", NULL, 2)));
    SYM_WALK_STELLA_METHOD_CONSTRUCTORp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-CONSTRUCTOR?", NULL, 0)));
    KWD_WALK_DEFINE = ((Keyword*)(internRigidSymbolWrtModule("DEFINE", NULL, 2)));
    KWD_WALK_FINALIZE = ((Keyword*)(internRigidSymbolWrtModule("FINALIZE", NULL, 2)));
    KWD_WALK_WALK = ((Keyword*)(internRigidSymbolWrtModule("WALK", NULL, 2)));
    KWD_WALK_TRANSLATE = ((Keyword*)(internRigidSymbolWrtModule("TRANSLATE", NULL, 2)));
    SYM_WALK_STELLA_METHOD_MACROp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-MACRO?", NULL, 0)));
    SGT_WALK_STELLA_GLOBAL_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("GLOBAL-VARIABLE", NULL, 1)));
    SGT_WALK_STELLA_TYPE_SPEC = ((Surrogate*)(internRigidSymbolWrtModule("TYPE-SPEC", NULL, 1)));
    SGT_WALK_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", NULL, 1)));
    SYM_WALK_STELLA_SLOT_AUXILIARYp = ((Symbol*)(internRigidSymbolWrtModule("SLOT-AUXILIARY?", NULL, 0)));
    SYM_WALK_STELLA_METHOD_GLOBALLY_INLINEp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-GLOBALLY-INLINE?", NULL, 0)));
    SYM_WALK_STELLA_LOG_FUNCTION_CALL = ((Symbol*)(internRigidSymbolWrtModule("LOG-FUNCTION-CALL", NULL, 0)));
    SYM_WALK_STELLA_START_FUNCTION_CALL_LOGGING = ((Symbol*)(internRigidSymbolWrtModule("START-FUNCTION-CALL-LOGGING", NULL, 0)));
    SYM_WALK_STELLA_STOP_FUNCTION_CALL_LOGGING = ((Symbol*)(internRigidSymbolWrtModule("STOP-FUNCTION-CALL-LOGGING", NULL, 0)));
    SYM_WALK_STELLA_SET_CALL_LOG_BREAK_POINT = ((Symbol*)(internRigidSymbolWrtModule("SET-CALL-LOG-BREAK-POINT", NULL, 0)));
    SYM_WALK_STELLA_BREAK_PROGRAM = ((Symbol*)(internRigidSymbolWrtModule("BREAK-PROGRAM", NULL, 0)));
    SYM_WALK_STELLA_TERMINATE_PROGRAM = ((Symbol*)(internRigidSymbolWrtModule("TERMINATE-PROGRAM", NULL, 0)));
    SYM_WALK_STELLA_PO = ((Symbol*)(internRigidSymbolWrtModule("PO", NULL, 0)));
    SYM_WALK_STELLA_NULLp = ((Symbol*)(internRigidSymbolWrtModule("NULL?", NULL, 0)));
    SYM_WALK_STELLA_EQp = ((Symbol*)(internRigidSymbolWrtModule("EQ?", NULL, 0)));
    SYM_WALK_STELLA_EQLp = ((Symbol*)(internRigidSymbolWrtModule("EQL?", NULL, 0)));
    SYM_WALK_STELLA_l = ((Symbol*)(internRigidSymbolWrtModule("<", NULL, 0)));
    SYM_WALK_STELLA_le = ((Symbol*)(internRigidSymbolWrtModule("<=", NULL, 0)));
    SYM_WALK_STELLA_g = ((Symbol*)(internRigidSymbolWrtModule(">", NULL, 0)));
    SYM_WALK_STELLA_ge = ((Symbol*)(internRigidSymbolWrtModule(">=", NULL, 0)));
    SYM_WALK_STELLA_CAST = ((Symbol*)(internRigidSymbolWrtModule("CAST", NULL, 0)));
    SGT_WALK_STELLA_UNKNOWN = ((Surrogate*)(internRigidSymbolWrtModule("UNKNOWN", NULL, 1)));
    SGT_WALK_STELLA_LISP_CODE = ((Surrogate*)(internRigidSymbolWrtModule("LISP-CODE", NULL, 1)));
    SGT_WALK_STELLA_OUTPUT_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("OUTPUT-STREAM", NULL, 1)));
    SGT_WALK_STELLA_NATIVE_OUTPUT_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("NATIVE-OUTPUT-STREAM", NULL, 1)));
    SYM_WALK_STELLA_INLINE = ((Symbol*)(internRigidSymbolWrtModule("INLINE", NULL, 0)));
    SGT_WALK_STELLA_UNINITIALIZED = ((Surrogate*)(internRigidSymbolWrtModule("UNINITIALIZED", NULL, 1)));
    KWD_WALK_SECOND_CLASS = ((Keyword*)(internRigidSymbolWrtModule("SECOND-CLASS", NULL, 2)));
    SGT_WALK_STELLA_KEY_VALUE_LIST = ((Surrogate*)(internRigidSymbolWrtModule("KEY-VALUE-LIST", NULL, 1)));
    SYM_WALK_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
    KWD_WALK_TYPE = ((Keyword*)(internRigidSymbolWrtModule("TYPE", NULL, 2)));
    KWD_WALK_ALIAS = ((Keyword*)(internRigidSymbolWrtModule("ALIAS", NULL, 2)));
    SYM_WALK_STELLA_ERROR = ((Symbol*)(internRigidSymbolWrtModule("ERROR", NULL, 0)));
    SYM_WALK_STELLA_ILLEGAL_EXPRESSION_FLAGGED_BY_THE_TRANSLATOR = ((Symbol*)(internRigidSymbolWrtModule("ILLEGAL-EXPRESSION-FLAGGED-BY-THE-TRANSLATOR", NULL, 0)));
    SYM_WALK_STELLA_BAD_SYS = ((Symbol*)(internRigidSymbolWrtModule("BAD-SYS", NULL, 0)));
    SGT_WALK_STELLA_INTEGER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER-WRAPPER", NULL, 1)));
    SGT_WALK_STELLA_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER", NULL, 1)));
    SGT_WALK_STELLA_LONG_INTEGER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("LONG-INTEGER-WRAPPER", NULL, 1)));
    SGT_WALK_STELLA_LONG_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("LONG-INTEGER", NULL, 1)));
    SGT_WALK_STELLA_FLOAT_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT-WRAPPER", NULL, 1)));
    SGT_WALK_STELLA_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT", NULL, 1)));
    SGT_WALK_STELLA_NUMBER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER-WRAPPER", NULL, 1)));
    SGT_WALK_STELLA_NUMBER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER", NULL, 1)));
    SGT_WALK_STELLA_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("STRING-WRAPPER", NULL, 1)));
    SGT_WALK_STELLA_STRING = ((Surrogate*)(internRigidSymbolWrtModule("STRING", NULL, 1)));
    SGT_WALK_STELLA_MUTABLE_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("MUTABLE-STRING-WRAPPER", NULL, 1)));
    SGT_WALK_STELLA_MUTABLE_STRING = ((Surrogate*)(internRigidSymbolWrtModule("MUTABLE-STRING", NULL, 1)));
    SGT_WALK_STELLA_CHARACTER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("CHARACTER-WRAPPER", NULL, 1)));
    SGT_WALK_STELLA_CHARACTER = ((Surrogate*)(internRigidSymbolWrtModule("CHARACTER", NULL, 1)));
    SGT_WALK_STELLA_BOOLEAN_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN-WRAPPER", NULL, 1)));
    SGT_WALK_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 1)));
    SGT_WALK_STELLA_FUNCTION_CODE_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("FUNCTION-CODE-WRAPPER", NULL, 1)));
    SGT_WALK_STELLA_FUNCTION_CODE = ((Surrogate*)(internRigidSymbolWrtModule("FUNCTION-CODE", NULL, 1)));
    SGT_WALK_STELLA_METHOD_CODE_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-CODE-WRAPPER", NULL, 1)));
  }
}

void helpStartupWalk3() {
  {
    SGT_WALK_STELLA_METHOD_CODE = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-CODE", NULL, 1)));
    SGT_WALK_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", NULL, 1)));
    SYM_WALK_STELLA_INLINE_WRAP_BOOLEAN = ((Symbol*)(internRigidSymbolWrtModule("INLINE-WRAP-BOOLEAN", NULL, 0)));
    SYM_WALK_STELLA_WRAP_LITERAL = ((Symbol*)(internRigidSymbolWrtModule("WRAP-LITERAL", NULL, 0)));
    SYM_WALK_STELLA_INTEGER_TO_BOOLEAN_WRAPPER = ((Symbol*)(internRigidSymbolWrtModule("INTEGER-TO-BOOLEAN-WRAPPER", NULL, 0)));
    SYM_WALK_STELLA_INTEGER_TO_BOOLEAN = ((Symbol*)(internRigidSymbolWrtModule("INTEGER-TO-BOOLEAN", NULL, 0)));
    SYM_WALK_STELLA_MUTABLE_STRING_TO_STRING = ((Symbol*)(internRigidSymbolWrtModule("MUTABLE-STRING-TO-STRING", NULL, 0)));
    SYM_WALK_STELLA_STRING_TO_MUTABLE_STRING = ((Symbol*)(internRigidSymbolWrtModule("STRING-TO-MUTABLE-STRING", NULL, 0)));
    SGT_WALK_STELLA_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("SYMBOL", NULL, 1)));
    SYM_WALK_STELLA_INTERN_SYMBOL = ((Symbol*)(internRigidSymbolWrtModule("INTERN-SYMBOL", NULL, 0)));
    SYM_WALK_STELLA_CHARACTER_TO_STRING = ((Symbol*)(internRigidSymbolWrtModule("CHARACTER-TO-STRING", NULL, 0)));
    SYM_WALK_STELLA_SYMBOL_NAME = ((Symbol*)(internRigidSymbolWrtModule("SYMBOL-NAME", NULL, 0)));
    SYM_WALK_STELLA_INLINE_UNWRAP_BOOLEAN = ((Symbol*)(internRigidSymbolWrtModule("INLINE-UNWRAP-BOOLEAN", NULL, 0)));
    SYM_WALK_STELLA_WRAPPER_VALUE = ((Symbol*)(internRigidSymbolWrtModule("WRAPPER-VALUE", NULL, 0)));
    SYM_WALK_STELLA_NUMBER_WRAPPER_TO_FLOAT = ((Symbol*)(internRigidSymbolWrtModule("NUMBER-WRAPPER-TO-FLOAT", NULL, 0)));
    SGT_WALK_STELLA_SURROGATE = ((Surrogate*)(internRigidSymbolWrtModule("SURROGATE", NULL, 1)));
    SGT_WALK_STELLA_CLASS = ((Surrogate*)(internRigidSymbolWrtModule("CLASS", NULL, 1)));
    SYM_WALK_STELLA_SURROGATE_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SURROGATE-VALUE", NULL, 0)));
    SGT_WALK_STELLA_INPUT_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("INPUT-STREAM", NULL, 1)));
    SGT_WALK_STELLA_NATIVE_INPUT_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("NATIVE-INPUT-STREAM", NULL, 1)));
    SYM_WALK_STELLA_NATIVE_STREAM = ((Symbol*)(internRigidSymbolWrtModule("NATIVE-STREAM", NULL, 0)));
    SYM_WALK_STELLA_lXg = ((Symbol*)(internRigidSymbolWrtModule("<X>", NULL, 0)));
    SGT_WALK_STELLA_SINGLE_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("SINGLE-FLOAT", NULL, 1)));
    SYM_WALK_STELLA_IDENTITY = ((Symbol*)(internRigidSymbolWrtModule("IDENTITY", NULL, 0)));
    SGT_WALK_STELLA_DOUBLE_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("DOUBLE-FLOAT", NULL, 1)));
    SGT_WALK_STELLA_SHORT_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("SHORT-INTEGER", NULL, 1)));
    SGT_WALK_STELLA_UNSIGNED_SHORT_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("UNSIGNED-SHORT-INTEGER", NULL, 1)));
    SGT_WALK_STELLA_UNSIGNED_LONG_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("UNSIGNED-LONG-INTEGER", NULL, 1)));
    SYM_WALK_STELLA_VRLET = ((Symbol*)(internRigidSymbolWrtModule("VRLET", NULL, 0)));
    SYM_WALK_STELLA_SYS_CALL_METHOD = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-METHOD", NULL, 0)));
    SYM_WALK_STELLA_SYS_CALL_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-FUNCTION", NULL, 0)));
    SYM_WALK_STELLA_TYPED_SYS = ((Symbol*)(internRigidSymbolWrtModule("TYPED-SYS", NULL, 0)));
    SYM_WALK_STELLA_SYS_INLINE_CALL = ((Symbol*)(internRigidSymbolWrtModule("SYS-INLINE-CALL", NULL, 0)));
    SYM_WALK_STELLA_SAFE_CAST = ((Symbol*)(internRigidSymbolWrtModule("SAFE-CAST", NULL, 0)));
    SGT_WALK_STELLA_NON_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("NON-OBJECT", NULL, 1)));
    SGT_WALK_STELLA_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("WRAPPER", NULL, 1)));
    SYM_WALK_STELLA_LET = ((Symbol*)(internRigidSymbolWrtModule("LET", NULL, 0)));
    SYM_WALK_STELLA_X = ((Symbol*)(internRigidSymbolWrtModule("X", NULL, 0)));
    SGT_WALK_STELLA_LITERAL = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL", NULL, 1)));
    SYM_WALK_STELLA_VOID_SYS = ((Symbol*)(internRigidSymbolWrtModule("VOID-SYS", NULL, 0)));
    SYM_WALK_STELLA_SLOT_TYPE_SPECIFIER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-TYPE-SPECIFIER", NULL, 0)));
    SYM_WALK_STELLA_SYS_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("SYS-FOREACH", NULL, 0)));
    SYM_WALK_STELLA_SETQ = ((Symbol*)(internRigidSymbolWrtModule("SETQ", NULL, 0)));
    SYM_WALK_STELLA_SYS_SET_DEFAULT = ((Symbol*)(internRigidSymbolWrtModule("SYS-SET-DEFAULT", NULL, 0)));
    SYM_WALK_STELLA_SETF = ((Symbol*)(internRigidSymbolWrtModule("SETF", NULL, 0)));
    SYM_WALK_STELLA_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SLOT-VALUE", NULL, 0)));
    SYM_WALK_STELLA_SLOT_VALUE_SETTER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-VALUE-SETTER", NULL, 0)));
    SYM_WALK_STELLA_AREF = ((Symbol*)(internRigidSymbolWrtModule("AREF", NULL, 0)));
    SYM_WALK_STELLA_AREF_SETTER = ((Symbol*)(internRigidSymbolWrtModule("AREF-SETTER", NULL, 0)));
    SYM_WALK_STELLA_WITH_PROCESS_LOCK = ((Symbol*)(internRigidSymbolWrtModule("WITH-PROCESS-LOCK", NULL, 0)));
    SYM_WALK_STELLA_LOOP = ((Symbol*)(internRigidSymbolWrtModule("LOOP", NULL, 0)));
    SYM_WALK_STELLA_VALUES = ((Symbol*)(internRigidSymbolWrtModule("VALUES", NULL, 0)));
    SYM_WALK_STELLA_SPECIAL = ((Symbol*)(internRigidSymbolWrtModule("SPECIAL", NULL, 0)));
    SYM_WALK_STELLA_SYS_SPECIAL = ((Symbol*)(internRigidSymbolWrtModule("SYS-SPECIAL", NULL, 0)));
    SYM_WALK_STELLA_RETURN = ((Symbol*)(internRigidSymbolWrtModule("RETURN", NULL, 0)));
    SYM_WALK_STELLA_MV_SETQ = ((Symbol*)(internRigidSymbolWrtModule("MV-SETQ", NULL, 0)));
    SYM_WALK_STELLA_MV_BIND = ((Symbol*)(internRigidSymbolWrtModule("MV-BIND", NULL, 0)));
    SYM_WALK_STELLA_BREAK = ((Symbol*)(internRigidSymbolWrtModule("BREAK", NULL, 0)));
    SYM_WALK_STELLA_CONTINUE = ((Symbol*)(internRigidSymbolWrtModule("CONTINUE", NULL, 0)));
    SYM_WALK_STELLA_WHILE = ((Symbol*)(internRigidSymbolWrtModule("WHILE", NULL, 0)));
  }
}

void helpStartupWalk4() {
  {
    SYM_WALK_STELLA_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("FOREACH", NULL, 0)));
    SYM_WALK_STELLA_EXISTS = ((Symbol*)(internRigidSymbolWrtModule("EXISTS", NULL, 0)));
    SYM_WALK_STELLA_FORALL = ((Symbol*)(internRigidSymbolWrtModule("FORALL", NULL, 0)));
    SYM_WALK_STELLA_SOME = ((Symbol*)(internRigidSymbolWrtModule("SOME", NULL, 0)));
    SYM_WALK_STELLA_SETOF = ((Symbol*)(internRigidSymbolWrtModule("SETOF", NULL, 0)));
    SYM_WALK_STELLA_SET_OF = ((Symbol*)(internRigidSymbolWrtModule("SET-OF", NULL, 0)));
    SYM_WALK_STELLA_SELECT = ((Symbol*)(internRigidSymbolWrtModule("SELECT", NULL, 0)));
    SYM_WALK_STELLA_IF = ((Symbol*)(internRigidSymbolWrtModule("IF", NULL, 0)));
    SYM_WALK_STELLA_UNLESS = ((Symbol*)(internRigidSymbolWrtModule("UNLESS", NULL, 0)));
    SYM_WALK_STELLA_CHOOSE = ((Symbol*)(internRigidSymbolWrtModule("CHOOSE", NULL, 0)));
    SYM_WALK_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", NULL, 0)));
    SYM_WALK_STELLA_COND = ((Symbol*)(internRigidSymbolWrtModule("COND", NULL, 0)));
    SYM_WALK_STELLA_CASE = ((Symbol*)(internRigidSymbolWrtModule("CASE", NULL, 0)));
    SYM_WALK_STELLA_TYPECASE = ((Symbol*)(internRigidSymbolWrtModule("TYPECASE", NULL, 0)));
    SYM_WALK_STELLA_e = ((Symbol*)(internRigidSymbolWrtModule("=", NULL, 0)));
    SYM_WALK_STELLA_i = ((Symbol*)(internRigidSymbolWrtModule("+", NULL, 0)));
    SYM_WALK_STELLA__ = ((Symbol*)(internRigidSymbolWrtModule("-", NULL, 0)));
    SYM_WALK_STELLA_o = ((Symbol*)(internRigidSymbolWrtModule("*", NULL, 0)));
    SYM_WALK_STELLA_s = ((Symbol*)(internRigidSymbolWrtModule("/", NULL, 0)));
    SYM_WALK_STELLA_QUOTE = ((Symbol*)(internRigidSymbolWrtModule("QUOTE", NULL, 0)));
    SYM_WALK_STELLA_BQUOTE = ((Symbol*)(internRigidSymbolWrtModule("BQUOTE", NULL, 0)));
    SYM_WALK_STELLA_PRINT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("PRINT-STREAM", NULL, 0)));
    SYM_WALK_STELLA_PRINT_NATIVE_STREAM = ((Symbol*)(internRigidSymbolWrtModule("PRINT-NATIVE-STREAM", NULL, 0)));
    SYM_WALK_STELLA_NEW = ((Symbol*)(internRigidSymbolWrtModule("NEW", NULL, 0)));
    SYM_WALK_STELLA_ALLOCATE = ((Symbol*)(internRigidSymbolWrtModule("ALLOCATE", NULL, 0)));
    SYM_WALK_STELLA_LOCAL_NEW = ((Symbol*)(internRigidSymbolWrtModule("LOCAL-NEW", NULL, 0)));
    SYM_WALK_STELLA_MAKE = ((Symbol*)(internRigidSymbolWrtModule("MAKE", NULL, 0)));
    SYM_WALK_STELLA_FUNCALL = ((Symbol*)(internRigidSymbolWrtModule("FUNCALL", NULL, 0)));
    SYM_WALK_STELLA_SYS_CALL_FUNCTION_CODE = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-FUNCTION-CODE", NULL, 0)));
    SYM_WALK_STELLA_SYS_CALL_METHOD_CODE = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-METHOD-CODE", NULL, 0)));
    SYM_WALK_STELLA_THE_CODE = ((Symbol*)(internRigidSymbolWrtModule("THE-CODE", NULL, 0)));
    SYM_WALK_STELLA_CALL_SUPER_METHOD = ((Symbol*)(internRigidSymbolWrtModule("CALL-SUPER-METHOD", NULL, 0)));
    SYM_WALK_STELLA_SIGNAL_EXCEPTION = ((Symbol*)(internRigidSymbolWrtModule("SIGNAL-EXCEPTION", NULL, 0)));
    SYM_WALK_STELLA_EXCEPTION_CASE = ((Symbol*)(internRigidSymbolWrtModule("EXCEPTION-CASE", NULL, 0)));
    SYM_WALK_STELLA_UNWIND_PROTECT = ((Symbol*)(internRigidSymbolWrtModule("UNWIND-PROTECT", NULL, 0)));
    SYM_WALK_STELLA_SYS_UNWIND_PROTECT = ((Symbol*)(internRigidSymbolWrtModule("SYS-UNWIND-PROTECT", NULL, 0)));
    SYM_WALK_STELLA_SYS_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SYS-SLOT-VALUE", NULL, 0)));
    SYM_WALK_STELLA_SYS_SLOT_VALUE_SETTER = ((Symbol*)(internRigidSymbolWrtModule("SYS-SLOT-VALUE-SETTER", NULL, 0)));
    SYM_WALK_STELLA_SYS_CALL_SUPER_METHOD = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-SUPER-METHOD", NULL, 0)));
    SYM_WALK_STELLA_SYS_CALL_METHOD_SETTER = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-METHOD-SETTER", NULL, 0)));
    SYM_WALK_STELLA_SYS_NEW = ((Symbol*)(internRigidSymbolWrtModule("SYS-NEW", NULL, 0)));
    KWD_WALK_PUBLICp = ((Keyword*)(internRigidSymbolWrtModule("PUBLIC?", NULL, 2)));
    SYM_WALK_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    KWD_WALK_SYMBOLS = ((Keyword*)(internRigidSymbolWrtModule("SYMBOLS", NULL, 2)));
    SYM_WALK_STELLA_INTERN_RIGID_SYMBOL_WRT_MODULE = ((Symbol*)(internRigidSymbolWrtModule("INTERN-RIGID-SYMBOL-WRT-MODULE", NULL, 0)));
    SYM_WALK_STELLA_GET_STELLA_MODULE = ((Symbol*)(internRigidSymbolWrtModule("GET-STELLA-MODULE", NULL, 0)));
    SYM_WALK_STELLA_INTERN_SYMBOL_AT = ((Symbol*)(internRigidSymbolWrtModule("INTERN-SYMBOL-AT", NULL, 0)));
    SYM_WALK_STELLA_INTERN_SURROGATE_AT = ((Symbol*)(internRigidSymbolWrtModule("INTERN-SURROGATE-AT", NULL, 0)));
    SYM_WALK_STELLA_INTERN_KEYWORD_AT = ((Symbol*)(internRigidSymbolWrtModule("INTERN-KEYWORD-AT", NULL, 0)));
    SYM_WALK_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", NULL, 0)));
    KWD_WALK_INLINE_ARGUMENT = ((Keyword*)(internRigidSymbolWrtModule("INLINE-ARGUMENT", NULL, 2)));
    SGT_WALK_STELLA_KEYWORD = ((Surrogate*)(internRigidSymbolWrtModule("KEYWORD", NULL, 1)));
    KWD_WALK_PLACE_WHERE_VRLET_WAS = ((Keyword*)(internRigidSymbolWrtModule("PLACE-WHERE-VRLET-WAS", NULL, 2)));
    KWD_WALK_PLACE_WHERE_LAST_EXPRESSION_WAS = ((Keyword*)(internRigidSymbolWrtModule("PLACE-WHERE-LAST-EXPRESSION-WAS", NULL, 2)));
    KWD_WALK_DYNAMIC = ((Keyword*)(internRigidSymbolWrtModule("DYNAMIC", NULL, 2)));
    SYM_WALK_STELLA_IT = ((Symbol*)(internRigidSymbolWrtModule("IT", NULL, 0)));
    SYM_WALK_STELLA_ON = ((Symbol*)(internRigidSymbolWrtModule("ON", NULL, 0)));
    SYM_WALK_STELLA_DYNAMIC_SLOTS = ((Symbol*)(internRigidSymbolWrtModule("DYNAMIC-SLOTS", NULL, 0)));
    SYM_WALK_STELLA_WHERE = ((Symbol*)(internRigidSymbolWrtModule("WHERE", NULL, 0)));
    SYM_WALK_STELLA_KEY = ((Symbol*)(internRigidSymbolWrtModule("KEY", NULL, 0)));
  }
}

void helpStartupWalk5() {
  {
    SYM_WALK_STELLA_DO = ((Symbol*)(internRigidSymbolWrtModule("DO", NULL, 0)));
    SYM_WALK_STELLA_WRAPPEDVALUE = ((Symbol*)(internRigidSymbolWrtModule("WRAPPEDVALUE", NULL, 0)));
    SYM_WALK_STELLA_VALUE = ((Symbol*)(internRigidSymbolWrtModule("VALUE", NULL, 0)));
    KWD_WALK_BIT = ((Keyword*)(internRigidSymbolWrtModule("BIT", NULL, 2)));
    SYM_WALK_STELLA_DYNAMICSLOTS = ((Symbol*)(internRigidSymbolWrtModule("DYNAMICSLOTS", NULL, 0)));
    SYM_WALK_STELLA_NEWVALUE = ((Symbol*)(internRigidSymbolWrtModule("NEWVALUE", NULL, 0)));
    SYM_WALK_STELLA_FOUNDMATCHINGENTRYp = ((Symbol*)(internRigidSymbolWrtModule("FOUNDMATCHINGENTRY?", NULL, 0)));
    SYM_WALK_STELLA_THE_KV_LIST = ((Symbol*)(internRigidSymbolWrtModule("THE-KV-LIST", NULL, 0)));
    SYM_WALK_STELLA_KV_CONS = ((Symbol*)(internRigidSymbolWrtModule("KV-CONS", NULL, 0)));
    SYM_WALK_STELLA_OLDVALUE = ((Symbol*)(internRigidSymbolWrtModule("OLDVALUE", NULL, 0)));
    KWD_WALK_CONTEXT_SENSITIVEp = ((Keyword*)(internRigidSymbolWrtModule("CONTEXT-SENSITIVE?", NULL, 2)));
    KWD_WALK_DONT_INHERITp = ((Keyword*)(internRigidSymbolWrtModule("DONT-INHERIT?", NULL, 2)));
    SYM_WALK_STELLA_ACCESS_IN_CONTEXT = ((Symbol*)(internRigidSymbolWrtModule("ACCESS-IN-CONTEXT", NULL, 0)));
    SYM_WALK_STELLA_HOME_CONTEXT = ((Symbol*)(internRigidSymbolWrtModule("HOME-CONTEXT", NULL, 0)));
    KWD_WALK_COPY_TO_CHILDRENp = ((Keyword*)(internRigidSymbolWrtModule("COPY-TO-CHILDREN?", NULL, 2)));
    SYM_WALK_STELLA_UPDATE_IN_CONTEXT = ((Symbol*)(internRigidSymbolWrtModule("UPDATE-IN-CONTEXT", NULL, 0)));
    SYM_WALK_STELLA_CS_VALUEp = ((Symbol*)(internRigidSymbolWrtModule("CS-VALUE?", NULL, 0)));
    SGT_WALK_STELLA_ARRAY = ((Surrogate*)(internRigidSymbolWrtModule("ARRAY", NULL, 1)));
    SYM_WALK_STELLA_ANY_VALUE = ((Symbol*)(internRigidSymbolWrtModule("ANY-VALUE", NULL, 0)));
    SYM_WALK_STELLA_VARIABLE_DECLARATION = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-DECLARATION", NULL, 0)));
    SYM_WALK_STELLA_ILLEGAL_VARIABLE = ((Symbol*)(internRigidSymbolWrtModule("ILLEGAL-VARIABLE", NULL, 0)));
    KWD_WALK_UNBIND_WITH_DESTRUCTORS = ((Keyword*)(internRigidSymbolWrtModule("UNBIND-WITH-DESTRUCTORS", NULL, 2)));
    KWD_WALK_UNWIND_PROTECT = ((Keyword*)(internRigidSymbolWrtModule("UNWIND-PROTECT", NULL, 2)));
    SGT_WALK_STELLA_METHOD_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-SLOT", NULL, 1)));
    SYM_WALK_STELLA_OTHERWISE = ((Symbol*)(internRigidSymbolWrtModule("OTHERWISE", NULL, 0)));
    SYM_WALK_STELLA_SYMBOL_ID = ((Symbol*)(internRigidSymbolWrtModule("SYMBOL-ID", NULL, 0)));
    SYM_WALK_STELLA_GENERALIZED_SYMBOL = ((Symbol*)(internRigidSymbolWrtModule("GENERALIZED-SYMBOL", NULL, 0)));
    SYM_WALK_STELLA_BOOLEANp = ((Symbol*)(internRigidSymbolWrtModule("BOOLEAN?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_BOOLEANp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-BOOLEAN?", NULL, 0)));
    SYM_WALK_STELLA_INTEGERp = ((Symbol*)(internRigidSymbolWrtModule("INTEGER?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_INTEGERp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-INTEGER?", NULL, 0)));
    SYM_WALK_STELLA_LONG_INTEGERp = ((Symbol*)(internRigidSymbolWrtModule("LONG-INTEGER?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_LONG_INTEGERp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-LONG-INTEGER?", NULL, 0)));
    SYM_WALK_STELLA_FLOATp = ((Symbol*)(internRigidSymbolWrtModule("FLOAT?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_FLOATp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-FLOAT?", NULL, 0)));
    SYM_WALK_STELLA_STRINGp = ((Symbol*)(internRigidSymbolWrtModule("STRING?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_STRINGp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-STRING?", NULL, 0)));
    SYM_WALK_STELLA_CHARACTERp = ((Symbol*)(internRigidSymbolWrtModule("CHARACTER?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_CHARACTERp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-CHARACTER?", NULL, 0)));
    SYM_WALK_STELLA_WRAPPERp = ((Symbol*)(internRigidSymbolWrtModule("WRAPPER?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_WRAPPERp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-WRAPPER?", NULL, 0)));
    SGT_WALK_STELLA_VERBATIM_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("VERBATIM-STRING-WRAPPER", NULL, 1)));
    SYM_WALK_STELLA_VERBATIM_STRINGp = ((Symbol*)(internRigidSymbolWrtModule("VERBATIM-STRING?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_VERBATIM_STRINGp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-VERBATIM-STRING?", NULL, 0)));
    SYM_WALK_STELLA_SURROGATEp = ((Symbol*)(internRigidSymbolWrtModule("SURROGATE?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_SURROGATEp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-SURROGATE?", NULL, 0)));
    SGT_WALK_STELLA_TYPE = ((Surrogate*)(internRigidSymbolWrtModule("TYPE", NULL, 1)));
    SYM_WALK_STELLA_TYPEp = ((Symbol*)(internRigidSymbolWrtModule("TYPE?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_TYPEp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-TYPE?", NULL, 0)));
    SYM_WALK_STELLA_SYMBOLp = ((Symbol*)(internRigidSymbolWrtModule("SYMBOL?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_SYMBOLp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-SYMBOL?", NULL, 0)));
    SGT_WALK_STELLA_TRANSIENT_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("TRANSIENT-SYMBOL", NULL, 1)));
    SYM_WALK_STELLA_TRANSIENT_SYMBOLp = ((Symbol*)(internRigidSymbolWrtModule("TRANSIENT-SYMBOL?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_TRANSIENT_SYMBOLp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-TRANSIENT-SYMBOL?", NULL, 0)));
    SYM_WALK_STELLA_KEYWORDp = ((Symbol*)(internRigidSymbolWrtModule("KEYWORD?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_KEYWORDp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-KEYWORD?", NULL, 0)));
    SYM_WALK_STELLA_CONSp = ((Symbol*)(internRigidSymbolWrtModule("CONS?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_CONSp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-CONS?", NULL, 0)));
    SYM_WALK_STELLA_STELLA_CLASSp = ((Symbol*)(internRigidSymbolWrtModule("STELLA-CLASS?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_CLASSp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-CLASS?", NULL, 0)));
  }
}

void helpStartupWalk6() {
  {
    SGT_WALK_STELLA_STORAGE_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("STORAGE-SLOT", NULL, 1)));
    SYM_WALK_STELLA_STORAGE_SLOTp = ((Symbol*)(internRigidSymbolWrtModule("STORAGE-SLOT?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_STORAGE_SLOTp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-STORAGE-SLOT?", NULL, 0)));
    SYM_WALK_STELLA_METHOD_SLOTp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-SLOT?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_METHOD_SLOTp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-METHOD-SLOT?", NULL, 0)));
    SGT_WALK_STELLA_ANCHORED_TYPE_SPECIFIER = ((Surrogate*)(internRigidSymbolWrtModule("ANCHORED-TYPE-SPECIFIER", NULL, 1)));
    SYM_WALK_STELLA_ANCHORED_TYPE_SPECIFIERp = ((Symbol*)(internRigidSymbolWrtModule("ANCHORED-TYPE-SPECIFIER?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_ANCHORED_TYPE_SPECIFIERp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-ANCHORED-TYPE-SPECIFIER?", NULL, 0)));
    SGT_WALK_STELLA_PARAMETRIC_TYPE_SPECIFIER = ((Surrogate*)(internRigidSymbolWrtModule("PARAMETRIC-TYPE-SPECIFIER", NULL, 1)));
    SYM_WALK_STELLA_PARAMETRIC_TYPE_SPECIFIERp = ((Symbol*)(internRigidSymbolWrtModule("PARAMETRIC-TYPE-SPECIFIER?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OF_PARAMETRIC_TYPE_SPECIFIERp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF-PARAMETRIC-TYPE-SPECIFIER?", NULL, 0)));
    SYM_WALK_STELLA_ISAp = ((Symbol*)(internRigidSymbolWrtModule("ISA?", NULL, 0)));
    SYM_WALK_STELLA_SUBTYPE_OFp = ((Symbol*)(internRigidSymbolWrtModule("SUBTYPE-OF?", NULL, 0)));
    SGT_WALK_STELLA_GENERALIZED_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("GENERALIZED-SYMBOL", NULL, 1)));
    SYM_WALK_STELLA_STRING_EQLp = ((Symbol*)(internRigidSymbolWrtModule("STRING-EQL?", NULL, 0)));
    SYM_WALK_STELLA_SAFE_PRIMARY_TYPE = ((Symbol*)(internRigidSymbolWrtModule("SAFE-PRIMARY-TYPE", NULL, 0)));
    SGT_WALK_STELLA_PROCESS_LOCK_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("PROCESS-LOCK-OBJECT", NULL, 1)));
    SGT_WALK_STELLA_STANDARD_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("STANDARD-OBJECT", NULL, 1)));
    SYM_WALK_STELLA_EQL_TO_BOOLEANp = ((Symbol*)(internRigidSymbolWrtModule("EQL-TO-BOOLEAN?", NULL, 0)));
    SYM_WALK_STELLA_EQL_TO_INTEGERp = ((Symbol*)(internRigidSymbolWrtModule("EQL-TO-INTEGER?", NULL, 0)));
    SYM_WALK_STELLA_EQL_TO_LONG_INTEGERp = ((Symbol*)(internRigidSymbolWrtModule("EQL-TO-LONG-INTEGER?", NULL, 0)));
    SYM_WALK_STELLA_EQL_TO_FLOATp = ((Symbol*)(internRigidSymbolWrtModule("EQL-TO-FLOAT?", NULL, 0)));
    SYM_WALK_STELLA_EQL_TO_STRINGp = ((Symbol*)(internRigidSymbolWrtModule("EQL-TO-STRING?", NULL, 0)));
    SYM_WALK_STELLA_GET_QUOTED_TREE = ((Symbol*)(internRigidSymbolWrtModule("GET-QUOTED-TREE", NULL, 0)));
    SYM_WALK_STELLA_METHOD_BODY_ARGUMENTp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-BODY-ARGUMENT?", NULL, 0)));
    KWD_WALK_WARN = ((Keyword*)(internRigidSymbolWrtModule("WARN", NULL, 2)));
    KWD_WALK_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    KWD_WALK_CONTINUABLE_ERROR = ((Keyword*)(internRigidSymbolWrtModule("CONTINUABLE-ERROR", NULL, 2)));
    SYM_WALK_STELLA_CLASS_CL_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CL-NATIVE-TYPE", NULL, 0)));
    SYM_WALK_STELLA_CLASS_CPP_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CPP-NATIVE-TYPE", NULL, 0)));
    SYM_WALK_STELLA_CLASS_JAVA_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-JAVA-NATIVE-TYPE", NULL, 0)));
    SYM_WALK_STELLA_CONCATENATE = ((Symbol*)(internRigidSymbolWrtModule("CONCATENATE", NULL, 0)));
    SYM_WALK_STELLA_NIL = ((Symbol*)(internRigidSymbolWrtModule("NIL", NULL, 0)));
    SYM_WALK_STELLA_WRAP_BOOLEAN = ((Symbol*)(internRigidSymbolWrtModule("WRAP-BOOLEAN", NULL, 0)));
    SYM_WALK_STELLA_CONS = ((Symbol*)(internRigidSymbolWrtModule("CONS", NULL, 0)));
    SYM_WALK_STELLA_CONS_LIST = ((Symbol*)(internRigidSymbolWrtModule("CONS-LIST", NULL, 0)));
    SYM_WALK_STELLA_ALLOCATE_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("ALLOCATE-ITERATOR", NULL, 0)));
    SGT_WALK_STELLA_ARGUMENT_LIST_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("ARGUMENT-LIST-ITERATOR", NULL, 1)));
    SYM_WALK_STELLA_LENGTH = ((Symbol*)(internRigidSymbolWrtModule("LENGTH", NULL, 0)));
    SYM_WALK_STELLA_METHOD_VARIABLE_ARGUMENTSp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-VARIABLE-ARGUMENTS?", NULL, 0)));
    SYM_WALK_STELLA_COPY_CONS_TREE = ((Symbol*)(internRigidSymbolWrtModule("COPY-CONS-TREE", NULL, 0)));
    SYM_WALK_STELLA_GET_SYM = ((Symbol*)(internRigidSymbolWrtModule("GET-SYM", NULL, 0)));
    SYM_WALK_STELLA_GET_SGT = ((Symbol*)(internRigidSymbolWrtModule("GET-SGT", NULL, 0)));
    SYM_WALK_STELLA_GET_KWD = ((Symbol*)(internRigidSymbolWrtModule("GET-KWD", NULL, 0)));
    SGT_WALK_STELLA_ARGUMENT_LIST = ((Surrogate*)(internRigidSymbolWrtModule("ARGUMENT-LIST", NULL, 1)));
    SYM_WALK_STELLA_CACHED_INLINABLE_METHOD_BODY = ((Symbol*)(internRigidSymbolWrtModule("CACHED-INLINABLE-METHOD-BODY", NULL, 0)));
    KWD_WALK_INLINE_REFERENCES = ((Keyword*)(internRigidSymbolWrtModule("INLINE-REFERENCES", NULL, 2)));
    SYM_WALK_STELLA_INLINE_CALL = ((Symbol*)(internRigidSymbolWrtModule("INLINE-CALL", NULL, 0)));
    SYM_WALK_STELLA_METHOD_INHERITS_THROUGH = ((Symbol*)(internRigidSymbolWrtModule("METHOD-INHERITS-THROUGH", NULL, 0)));
    KWD_WALK_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SYM_WALK_STELLA_MAIN = ((Symbol*)(internRigidSymbolWrtModule("MAIN", NULL, 0)));
    SYM_WALK_STELLA_METHOD_NATIVEp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-NATIVE?", NULL, 0)));
    KWD_WALK_METHODS = ((Keyword*)(internRigidSymbolWrtModule("METHODS", NULL, 2)));
    SYM_WALK_STELLA_FORWARD_DECLARATIONp = ((Symbol*)(internRigidSymbolWrtModule("FORWARD-DECLARATION?", NULL, 0)));
    SYM_WALK_STELLA_METHOD_COMMANDp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-COMMAND?", NULL, 0)));
    SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE = ((Symbol*)(internRigidSymbolWrtModule("C-CALLABLE-WRAPPER-CODE", NULL, 0)));
    SYM_WALK_STELLA_LOOKUP_FUNCTION_BY_NAME = ((Symbol*)(internRigidSymbolWrtModule("LOOKUP-FUNCTION-BY-NAME", NULL, 0)));
    KWD_WALK_CLASS = ((Keyword*)(internRigidSymbolWrtModule("CLASS", NULL, 2)));
    KWD_WALK_EMBEDDED = ((Keyword*)(internRigidSymbolWrtModule("EMBEDDED", NULL, 2)));
    SYM_WALK_STELLA_CLASS_CONSTRUCTOR_CODE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CONSTRUCTOR-CODE", NULL, 0)));
  }
}

void helpStartupWalk7() {
  {
    SYM_WALK_STELLA_CLASS_AUXILIARY_METHODS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-AUXILIARY-METHODS", NULL, 0)));
    SYM_WALK_STELLA_AUXILIARY_METHOD_REASON = ((Symbol*)(internRigidSymbolWrtModule("AUXILIARY-METHOD-REASON", NULL, 0)));
    KWD_WALK_FIRST_CLASS_WITH_TYPECASE = ((Keyword*)(internRigidSymbolWrtModule("FIRST-CLASS-WITH-TYPECASE", NULL, 2)));
    KWD_WALK_AUXILIARYp = ((Keyword*)(internRigidSymbolWrtModule("AUXILIARY?", NULL, 2)));
    SYM_WALK_STELLA_PRINT_FORM = ((Symbol*)(internRigidSymbolWrtModule("PRINT-FORM", NULL, 0)));
    SYM_WALK_STELLA_PRINT_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("PRINT-OBJECT", NULL, 0)));
    SYM_WALK_STELLA_SELF = ((Symbol*)(internRigidSymbolWrtModule("SELF", NULL, 0)));
    SYM_WALK_STELLA_STREAM = ((Symbol*)(internRigidSymbolWrtModule("STREAM", NULL, 0)));
    SYM_WALK_STELLA_NATIVE_OUTPUT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("NATIVE-OUTPUT-STREAM", NULL, 0)));
    KWD_WALK_CLASSES = ((Keyword*)(internRigidSymbolWrtModule("CLASSES", NULL, 2)));
    KWD_WALK_FINALIZE_CLASSES = ((Keyword*)(internRigidSymbolWrtModule("FINALIZE-CLASSES", NULL, 2)));
    SYM_WALK_STELLA_FINALIZE_CLASSES = ((Symbol*)(internRigidSymbolWrtModule("FINALIZE-CLASSES", NULL, 0)));
    KWD_WALK_FINALIZE_METHODS = ((Keyword*)(internRigidSymbolWrtModule("FINALIZE-METHODS", NULL, 2)));
    SYM_WALK_STELLA_FINALIZE_SLOTS = ((Symbol*)(internRigidSymbolWrtModule("FINALIZE-SLOTS", NULL, 0)));
    SYM_WALK_STELLA_CLEANUP_UNFINALIZED_CLASSES = ((Symbol*)(internRigidSymbolWrtModule("CLEANUP-UNFINALIZED-CLASSES", NULL, 0)));
    SYM_WALK_STELLA_DEFINE_EXTERNAL_SLOT_FROM_STRINGIFIED_SOURCE = ((Symbol*)(internRigidSymbolWrtModule("DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE", NULL, 0)));
    KWD_WALK_MACROp = ((Keyword*)(internRigidSymbolWrtModule("MACRO?", NULL, 2)));
    SYM_WALK_STELLA_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("OBJECT", NULL, 0)));
    KWD_WALK_UNBOUND_SPECIAL_VARIABLE = ((Keyword*)(internRigidSymbolWrtModule("UNBOUND-SPECIAL-VARIABLE", NULL, 2)));
    KWD_WALK_GLOBALS = ((Keyword*)(internRigidSymbolWrtModule("GLOBALS", NULL, 2)));
    SYM_WALK_STELLA_DEFINE_GLOBAL_VARIABLE_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("DEFINE-GLOBAL-VARIABLE-OBJECT", NULL, 0)));
    SYM_WALK_STELLA_DEFINE_STELLA_TYPE_FROM_STRINGIFIED_SOURCE = ((Symbol*)(internRigidSymbolWrtModule("DEFINE-STELLA-TYPE-FROM-STRINGIFIED-SOURCE", NULL, 0)));
    KWD_WALK_FINAL = ((Keyword*)(internRigidSymbolWrtModule("FINAL", NULL, 2)));
    SYM_WALK_STELLA_CURRENT_STARTUP_TIME_PHASEp = ((Symbol*)(internRigidSymbolWrtModule("CURRENT-STARTUP-TIME-PHASE?", NULL, 0)));
    KWD_WALK_MODULES = ((Keyword*)(internRigidSymbolWrtModule("MODULES", NULL, 2)));
    SYM_WALK_STELLA_WITHIN_MODULE = ((Symbol*)(internRigidSymbolWrtModule("WITHIN-MODULE", NULL, 0)));
    SYM_WALK_STELLA_oSTELLA_MODULEo = ((Symbol*)(internRigidSymbolWrtModule("*STELLA-MODULE*", NULL, 0)));
    SYM_WALK_STELLA_oSTARTUP_TIME_PHASEo = ((Symbol*)(internRigidSymbolWrtModule("*STARTUP-TIME-PHASE*", NULL, 0)));
    SYM_WALK_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    KWD_WALK_C_CALLABLEp = ((Keyword*)(internRigidSymbolWrtModule("C-CALLABLE?", NULL, 2)));
    KWD_WALK_C_NAMESPACE_PREFIX = ((Keyword*)(internRigidSymbolWrtModule("C-NAMESPACE-PREFIX", NULL, 2)));
    SYM_WALK_STELLA_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("FUNCTION", NULL, 0)));
    SYM_WALK_STELLA_LOOKUP_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("LOOKUP-FUNCTION", NULL, 0)));
    SYM_WALK_STELLA_oBOOTSTRAP_LOCKo = ((Symbol*)(internRigidSymbolWrtModule("*BOOTSTRAP-LOCK*", NULL, 0)));
    SGT_WALK_STELLA_STELLA_ROOT_EXCEPTION = ((Surrogate*)(internRigidSymbolWrtModule("STELLA-ROOT-EXCEPTION", NULL, 1)));
    SYM_WALK_STELLA_SYS_SIGNAL = ((Symbol*)(internRigidSymbolWrtModule("SYS-SIGNAL", NULL, 0)));
    SYM_WALK_STELLA_SYS_HANDLER_CASE = ((Symbol*)(internRigidSymbolWrtModule("SYS-HANDLER-CASE", NULL, 0)));
    SGT_WALK_STELLA_NATIVE_EXCEPTION = ((Surrogate*)(internRigidSymbolWrtModule("NATIVE-EXCEPTION", NULL, 1)));
    SYM_WALK_STELLA_SYS_HANDLE_EXCEPTION = ((Symbol*)(internRigidSymbolWrtModule("SYS-HANDLE-EXCEPTION", NULL, 0)));
    KWD_WALK_OTHERWISE = ((Keyword*)(internRigidSymbolWrtModule("OTHERWISE", NULL, 2)));
    SYM_WALK_STELLA_INITIAL_ELEMENT = ((Symbol*)(internRigidSymbolWrtModule("INITIAL-ELEMENT", NULL, 0)));
    SYM_WALK_STELLA_SIZE = ((Symbol*)(internRigidSymbolWrtModule("SIZE", NULL, 0)));
    SYM_WALK_STELLA_STORAGE_SLOT = ((Symbol*)(internRigidSymbolWrtModule("STORAGE-SLOT", NULL, 0)));
    SGT_WALK_STELLA_CODE = ((Surrogate*)(internRigidSymbolWrtModule("CODE", NULL, 1)));
    KWD_WALK_METHOD = ((Keyword*)(internRigidSymbolWrtModule("METHOD", NULL, 2)));
    SYM_WALK_STELLA_METHOD_CODE = ((Symbol*)(internRigidSymbolWrtModule("METHOD-CODE", NULL, 0)));
    SGT_WALK_STELLA_COMPOUND_TYPE_SPECIFIER = ((Surrogate*)(internRigidSymbolWrtModule("COMPOUND-TYPE-SPECIFIER", NULL, 1)));
    SYM_WALK_STELLA_METHOD_LISP_MACROp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-LISP-MACRO?", NULL, 0)));
    SYM_WALK_STELLA_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 0)));
    SYM_WALK_STELLA_EXPRESSION = ((Symbol*)(internRigidSymbolWrtModule("EXPRESSION", NULL, 0)));
    SYM_WALK_STELLA_IGNORE = ((Symbol*)(internRigidSymbolWrtModule("IGNORE", NULL, 0)));
    SYM_WALK_STELLA_oIGNORETRANSLATIONERRORSpo = ((Symbol*)(internRigidSymbolWrtModule("*IGNORETRANSLATIONERRORS?*", NULL, 0)));
    SYM_WALK_STELLA_CL_INCREMENTALLY_TRANSLATE = ((Symbol*)(internRigidSymbolWrtModule("CL-INCREMENTALLY-TRANSLATE", NULL, 0)));
    SYM_WALK_STELLA_REGISTER_NATIVE_NAME = ((Symbol*)(internRigidSymbolWrtModule("REGISTER-NATIVE-NAME", NULL, 0)));
    SYM_WALK_STELLA_METHOD_C_CALLABLEp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-C-CALLABLE?", NULL, 0)));
    SYM_WALK_STELLA_METHOD_C_NAMESPACE_PREFIX = ((Symbol*)(internRigidSymbolWrtModule("METHOD-C-NAMESPACE-PREFIX", NULL, 0)));
    SYM_WALK_STELLA_oC_API_RESULT_BUFFERo = ((Symbol*)(internRigidSymbolWrtModule("*C-API-RESULT-BUFFER*", NULL, 0)));
    SYM_WALK_STELLA_NATIVE_OBJECT_POINTER = ((Symbol*)(internRigidSymbolWrtModule("NATIVE-OBJECT-POINTER", NULL, 0)));
    SYM_WALK_STELLA_METHOD_THROWS_EXCEPTIONSp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-THROWS-EXCEPTIONS?", NULL, 0)));
    SYM_WALK_STELLA_NATIVE_EXCEPTION = ((Symbol*)(internRigidSymbolWrtModule("NATIVE-EXCEPTION", NULL, 0)));
  }
}

void helpStartupWalk8() {
  {
    SYM_WALK_STELLA_E = ((Symbol*)(internRigidSymbolWrtModule("E", NULL, 0)));
    SYM_WALK_STELLA_CALL_GLOBAL_EXCEPTION_HANDLER = ((Symbol*)(internRigidSymbolWrtModule("CALL-GLOBAL-EXCEPTION-HANDLER", NULL, 0)));
    KWD_WALK_DOCUMENTATION = ((Keyword*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 2)));
    SYM_WALK_STELLA_CPP_VAR_ARGS = ((Symbol*)(internRigidSymbolWrtModule("CPP_VAR_ARGS", NULL, 0)));
    SYM_WALK_STELLA_REST = ((Symbol*)(internRigidSymbolWrtModule("REST", NULL, 0)));
    SYM_WALK_STELLA_NTH_REST = ((Symbol*)(internRigidSymbolWrtModule("NTH-REST", NULL, 0)));
    SYM_WALK_STELLA_NTH = ((Symbol*)(internRigidSymbolWrtModule("NTH", NULL, 0)));
    SYM_WALK_STELLA_ARGUMENTS = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENTS", NULL, 0)));
    SYM_WALK_STELLA_RESULT = ((Symbol*)(internRigidSymbolWrtModule("RESULT", NULL, 0)));
    SYM_WALK_STELLA_METHOD_EVALUATE_ARGUMENTSp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-EVALUATE-ARGUMENTS?", NULL, 0)));
    SYM_WALK_STELLA_APPEND = ((Symbol*)(internRigidSymbolWrtModule("APPEND", NULL, 0)));
    SYM_WALK_STELLA_EVALUATOR_WRAPPER_CODE = ((Symbol*)(internRigidSymbolWrtModule("EVALUATOR-WRAPPER-CODE", NULL, 0)));
    SYM_WALK_STELLA_VARIABLE_TYPE_SPECIFIER = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-TYPE-SPECIFIER", NULL, 0)));
    SYM_WALK_STELLA_LISTo = ((Symbol*)(internRigidSymbolWrtModule("LIST*", NULL, 0)));
    SYM_WALK_STELLA_STARTUP_WALK = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-WALK", NULL, 0)));
  }
}

void helpStartupWalk9() {
  {
    oAVAILABLE_STELLA_FEATURESo = list(10, KWD_WALK_WARN_ABOUT_UNDEFINED_METHODS, KWD_WALK_WARN_ABOUT_MISSING_METHODS, KWD_WALK_SUPPRESS_WARNINGS, KWD_WALK_USE_HARDCODED_SYMBOLS, KWD_WALK_USE_COMMON_LISP_STRUCTS, KWD_WALK_USE_COMMON_LISP_CONSES, KWD_WALK_USE_CPP_GARBAGE_COLLECTOR, KWD_WALK_MINIMIZE_JAVA_PREFIXES, KWD_WALK_TRANSLATE_WITH_COPYRIGHT_HEADER, KWD_WALK_SUPPORT_UNEXEC);
    oCURRENT_STELLA_FEATURESo = list(0);
    oDEFAULT_STELLA_FEATURESo = list(5, KWD_WALK_WARN_ABOUT_UNDEFINED_METHODS, KWD_WALK_WARN_ABOUT_MISSING_METHODS, KWD_WALK_USE_CPP_GARBAGE_COLLECTOR, KWD_WALK_USE_COMMON_LISP_CONSES, KWD_WALK_MINIMIZE_JAVA_PREFIXES);
    resetStellaFeatures();
    oTRANSLATOROUTPUTLANGUAGEo = runningInLanguage();
    oTARGETTYPEo = SGT_WALK_STELLA_VOID;
    oLOG_BREAK_POINT_COUNTERo = NULL_INTEGER;
    oWRAPPED_TYPE_TABLEo = listO(11, listO(3, SGT_WALK_STELLA_INTEGER_WRAPPER, SGT_WALK_STELLA_INTEGER, NIL), listO(3, SGT_WALK_STELLA_LONG_INTEGER_WRAPPER, SGT_WALK_STELLA_LONG_INTEGER, NIL), listO(3, SGT_WALK_STELLA_FLOAT_WRAPPER, SGT_WALK_STELLA_FLOAT, NIL), listO(3, SGT_WALK_STELLA_NUMBER_WRAPPER, SGT_WALK_STELLA_NUMBER, NIL), listO(3, SGT_WALK_STELLA_STRING_WRAPPER, SGT_WALK_STELLA_STRING, NIL), listO(3, SGT_WALK_STELLA_MUTABLE_STRING_WRAPPER, SGT_WALK_STELLA_MUTABLE_STRING, NIL), listO(3, SGT_WALK_STELLA_CHARACTER_WRAPPER, SGT_WALK_STELLA_CHARACTER, NIL), listO(3, SGT_WALK_STELLA_BOOLEAN_WRAPPER, SGT_WALK_STELLA_BOOLEAN, NIL), listO(3, SGT_WALK_STELLA_FUNCTION_CODE_WRAPPER, SGT_WALK_STELLA_FUNCTION_CODE, NIL), listO(3, SGT_WALK_STELLA_METHOD_CODE_WRAPPER, SGT_WALK_STELLA_METHOD_CODE, NIL), NIL);
    oCOERSION_TABLEo = listO(45, listO(4, SGT_WALK_STELLA_BOOLEAN, SGT_WALK_STELLA_BOOLEAN_WRAPPER, SYM_WALK_STELLA_INLINE_WRAP_BOOLEAN, NIL), listO(4, SGT_WALK_STELLA_INTEGER, SGT_WALK_STELLA_INTEGER_WRAPPER, SYM_WALK_STELLA_WRAP_LITERAL, NIL), listO(4, SGT_WALK_STELLA_LONG_INTEGER, SGT_WALK_STELLA_LONG_INTEGER_WRAPPER, SYM_WALK_STELLA_WRAP_LITERAL, NIL), listO(4, SGT_WALK_STELLA_INTEGER, SGT_WALK_STELLA_BOOLEAN_WRAPPER, SYM_WALK_STELLA_INTEGER_TO_BOOLEAN_WRAPPER, NIL), listO(4, SGT_WALK_STELLA_INTEGER, SGT_WALK_STELLA_BOOLEAN, SYM_WALK_STELLA_INTEGER_TO_BOOLEAN, NIL), listO(4, SGT_WALK_STELLA_FLOAT, SGT_WALK_STELLA_FLOAT_WRAPPER, SYM_WALK_STELLA_WRAP_LITERAL, NIL), listO(4, SGT_WALK_STELLA_MUTABLE_STRING, SGT_WALK_STELLA_STRING, SYM_WALK_STELLA_MUTABLE_STRING_TO_STRING, NIL), listO(4, SGT_WALK_STELLA_MUTABLE_STRING, SGT_WALK_STELLA_MUTABLE_STRING_WRAPPER, SYM_WALK_STELLA_WRAP_LITERAL, NIL), listO(4, SGT_WALK_STELLA_STRING, SGT_WALK_STELLA_STRING_WRAPPER, SYM_WALK_STELLA_WRAP_LITERAL, NIL), listO(4, SGT_WALK_STELLA_STRING, SGT_WALK_STELLA_MUTABLE_STRING, SYM_WALK_STELLA_STRING_TO_MUTABLE_STRING, NIL), listO(4, SGT_WALK_STELLA_STRING, SGT_WALK_STELLA_SYMBOL, SYM_WALK_STELLA_INTERN_SYMBOL, NIL), listO(4, SGT_WALK_STELLA_CHARACTER, SGT_WALK_STELLA_CHARACTER_WRAPPER, SYM_WALK_STELLA_WRAP_LITERAL, NIL), listO(4, SGT_WALK_STELLA_CHARACTER, SGT_WALK_STELLA_STRING, SYM_WALK_STELLA_CHARACTER_TO_STRING, NIL), listO(4, SGT_WALK_STELLA_FUNCTION_CODE, SGT_WALK_STELLA_FUNCTION_CODE_WRAPPER, SYM_WALK_STELLA_WRAP_LITERAL, NIL), listO(4, SGT_WALK_STELLA_METHOD_CODE, SGT_WALK_STELLA_METHOD_CODE_WRAPPER, SYM_WALK_STELLA_WRAP_LITERAL, NIL), listO(4, SGT_WALK_STELLA_SYMBOL, SGT_WALK_STELLA_STRING, SYM_WALK_STELLA_SYMBOL_NAME, NIL), listO(4, SGT_WALK_STELLA_BOOLEAN_WRAPPER, SGT_WALK_STELLA_BOOLEAN, SYM_WALK_STELLA_INLINE_UNWRAP_BOOLEAN, NIL), listO(4, SGT_WALK_STELLA_INTEGER_WRAPPER, SGT_WALK_STELLA_INTEGER, SYM_WALK_STELLA_WRAPPER_VALUE, NIL), listO(4, SGT_WALK_STELLA_INTEGER_WRAPPER, SGT_WALK_STELLA_LONG_INTEGER, SYM_WALK_STELLA_WRAPPER_VALUE, NIL), listO(4, SGT_WALK_STELLA_LONG_INTEGER_WRAPPER, SGT_WALK_STELLA_LONG_INTEGER, SYM_WALK_STELLA_WRAPPER_VALUE, NIL), listO(4, SGT_WALK_STELLA_FLOAT_WRAPPER, SGT_WALK_STELLA_FLOAT, SYM_WALK_STELLA_WRAPPER_VALUE, NIL), listO(4, SGT_WALK_STELLA_NUMBER_WRAPPER, SGT_WALK_STELLA_FLOAT, SYM_WALK_STELLA_NUMBER_WRAPPER_TO_FLOAT, NIL), listO(4, SGT_WALK_STELLA_STRING_WRAPPER, SGT_WALK_STELLA_STRING, SYM_WALK_STELLA_WRAPPER_VALUE, NIL), listO(4, SGT_WALK_STELLA_MUTABLE_STRING_WRAPPER, SGT_WALK_STELLA_MUTABLE_STRING, SYM_WALK_STELLA_WRAPPER_VALUE, NIL), listO(4, SGT_WALK_STELLA_CHARACTER_WRAPPER, SGT_WALK_STELLA_CHARACTER, SYM_WALK_STELLA_WRAPPER_VALUE, NIL), listO(4, SGT_WALK_STELLA_FUNCTION_CODE_WRAPPER, SGT_WALK_STELLA_FUNCTION_CODE, SYM_WALK_STELLA_WRAPPER_VALUE, NIL), listO(4, SGT_WALK_STELLA_METHOD_CODE_WRAPPER, SGT_WALK_STELLA_METHOD_CODE, SYM_WALK_STELLA_WRAPPER_VALUE, NIL), listO(4, SGT_WALK_STELLA_SURROGATE, SGT_WALK_STELLA_CLASS, SYM_WALK_STELLA_SURROGATE_VALUE, NIL), listO(4, SGT_WALK_STELLA_SURROGATE, SGT_WALK_STELLA_MODULE, SYM_WALK_STELLA_SURROGATE_VALUE, NIL), listO(4, SGT_WALK_STELLA_INPUT_STREAM, SGT_WALK_STELLA_NATIVE_INPUT_STREAM, SYM_WALK_STELLA_NATIVE_STREAM, NIL), listO(4, SGT_WALK_STELLA_OUTPUT_STREAM, SGT_WALK_STELLA_NATIVE_OUTPUT_STREAM, SYM_WALK_STELLA_NATIVE_STREAM, NIL), listO(4, SGT_WALK_STELLA_NUMBER, SGT_WALK_STELLA_INTEGER, listO(4, SYM_WALK_STELLA_CAST, SYM_WALK_STELLA_lXg, SGT_WALK_STELLA_INTEGER, NIL), NIL), listO(4, SGT_WALK_STELLA_NUMBER, SGT_WALK_STELLA_LONG_INTEGER, listO(4, SYM_WALK_STELLA_CAST, SYM_WALK_STELLA_lXg, SGT_WALK_STELLA_LONG_INTEGER, NIL), NIL), listO(4, SGT_WALK_STELLA_NUMBER, SGT_WALK_STELLA_FLOAT, listO(4, SYM_WALK_STELLA_CAST, SYM_WALK_STELLA_lXg, SGT_WALK_STELLA_FLOAT, NIL), NIL), listO(4, SGT_WALK_STELLA_INTEGER, SGT_WALK_STELLA_FLOAT, listO(4, SYM_WALK_STELLA_CAST, SYM_WALK_STELLA_lXg, SGT_WALK_STELLA_FLOAT, NIL), NIL), listO(4, SGT_WALK_STELLA_INTEGER, SGT_WALK_STELLA_SINGLE_FLOAT, listO(4, SYM_WALK_STELLA_CAST, SYM_WALK_STELLA_lXg, SGT_WALK_STELLA_SINGLE_FLOAT, NIL), NIL), listO(4, SGT_WALK_STELLA_LONG_INTEGER, SGT_WALK_STELLA_FLOAT, listO(4, SYM_WALK_STELLA_CAST, SYM_WALK_STELLA_lXg, SGT_WALK_STELLA_FLOAT, NIL), NIL), listO(4, SGT_WALK_STELLA_LONG_INTEGER, SGT_WALK_STELLA_SINGLE_FLOAT, listO(4, SYM_WALK_STELLA_CAST, SYM_WALK_STELLA_lXg, SGT_WALK_STELLA_SINGLE_FLOAT, NIL), NIL), listO(4, SGT_WALK_STELLA_FLOAT, SGT_WALK_STELLA_SINGLE_FLOAT, SYM_WALK_STELLA_IDENTITY, NIL), listO(4, SGT_WALK_STELLA_FLOAT, SGT_WALK_STELLA_DOUBLE_FLOAT, SYM_WALK_STELLA_IDENTITY, NIL), listO(4, SGT_WALK_STELLA_INTEGER, SGT_WALK_STELLA_SHORT_INTEGER, SYM_WALK_STELLA_IDENTITY, NIL), listO(4, SGT_WALK_STELLA_INTEGER, SGT_WALK_STELLA_LONG_INTEGER, SYM_WALK_STELLA_IDENTITY, NIL), listO(4, SGT_WALK_STELLA_INTEGER, SGT_WALK_STELLA_UNSIGNED_SHORT_INTEGER, SYM_WALK_STELLA_IDENTITY, NIL), listO(4, SGT_WALK_STELLA_INTEGER, SGT_WALK_STELLA_UNSIGNED_LONG_INTEGER, SYM_WALK_STELLA_IDENTITY, NIL), NIL);
    oSYMBOL_REGISTRYo = newHashTable();
    oSYMBOL_SETo = newList();
    oCURRENTFILENAMEo = NULL;
    oSPECIALVARIABLESTACKo = newKeyValueList();
    oTYPE_PREDICATE_TABLEo = listO(26, listO(4, SGT_WALK_STELLA_BOOLEAN, SYM_WALK_STELLA_BOOLEANp, SYM_WALK_STELLA_SUBTYPE_OF_BOOLEANp, NIL), listO(4, SGT_WALK_STELLA_INTEGER, SYM_WALK_STELLA_INTEGERp, SYM_WALK_STELLA_SUBTYPE_OF_INTEGERp, NIL), listO(4, SGT_WALK_STELLA_LONG_INTEGER, SYM_WALK_STELLA_LONG_INTEGERp, SYM_WALK_STELLA_SUBTYPE_OF_LONG_INTEGERp, NIL), listO(4, SGT_WALK_STELLA_FLOAT, SYM_WALK_STELLA_FLOATp, SYM_WALK_STELLA_SUBTYPE_OF_FLOATp, NIL), listO(4, SGT_WALK_STELLA_STRING, SYM_WALK_STELLA_STRINGp, SYM_WALK_STELLA_SUBTYPE_OF_STRINGp, NIL), listO(4, SGT_WALK_STELLA_CHARACTER, SYM_WALK_STELLA_CHARACTERp, SYM_WALK_STELLA_SUBTYPE_OF_CHARACTERp, NIL), listO(4, SGT_WALK_STELLA_WRAPPER, SYM_WALK_STELLA_WRAPPERp, SYM_WALK_STELLA_SUBTYPE_OF_WRAPPERp, NIL), listO(4, SGT_WALK_STELLA_BOOLEAN_WRAPPER, SYM_WALK_STELLA_BOOLEANp, SYM_WALK_STELLA_SUBTYPE_OF_BOOLEANp, NIL), listO(4, SGT_WALK_STELLA_INTEGER_WRAPPER, SYM_WALK_STELLA_INTEGERp, SYM_WALK_STELLA_SUBTYPE_OF_INTEGERp, NIL), listO(4, SGT_WALK_STELLA_LONG_INTEGER_WRAPPER, SYM_WALK_STELLA_LONG_INTEGERp, SYM_WALK_STELLA_SUBTYPE_OF_LONG_INTEGERp, NIL), listO(4, SGT_WALK_STELLA_FLOAT_WRAPPER, SYM_WALK_STELLA_FLOATp, SYM_WALK_STELLA_SUBTYPE_OF_FLOATp, NIL), listO(4, SGT_WALK_STELLA_STRING_WRAPPER, SYM_WALK_STELLA_STRINGp, SYM_WALK_STELLA_SUBTYPE_OF_STRINGp, NIL), listO(4, SGT_WALK_STELLA_CHARACTER_WRAPPER, SYM_WALK_STELLA_CHARACTERp, SYM_WALK_STELLA_SUBTYPE_OF_CHARACTERp, NIL), listO(4, SGT_WALK_STELLA_VERBATIM_STRING_WRAPPER, SYM_WALK_STELLA_VERBATIM_STRINGp, SYM_WALK_STELLA_SUBTYPE_OF_VERBATIM_STRINGp, NIL), listO(4, SGT_WALK_STELLA_SURROGATE, SYM_WALK_STELLA_SURROGATEp, SYM_WALK_STELLA_SUBTYPE_OF_SURROGATEp, NIL), listO(4, SGT_WALK_STELLA_TYPE, SYM_WALK_STELLA_TYPEp, SYM_WALK_STELLA_SUBTYPE_OF_TYPEp, NIL), listO(4, SGT_WALK_STELLA_SYMBOL, SYM_WALK_STELLA_SYMBOLp, SYM_WALK_STELLA_SUBTYPE_OF_SYMBOLp, NIL), listO(4, SGT_WALK_STELLA_TRANSIENT_SYMBOL, SYM_WALK_STELLA_TRANSIENT_SYMBOLp, SYM_WALK_STELLA_SUBTYPE_OF_TRANSIENT_SYMBOLp, NIL), listO(4, SGT_WALK_STELLA_KEYWORD, SYM_WALK_STELLA_KEYWORDp, SYM_WALK_STELLA_SUBTYPE_OF_KEYWORDp, NIL), listO(4, SGT_WALK_STELLA_CONS, SYM_WALK_STELLA_CONSp, SYM_WALK_STELLA_SUBTYPE_OF_CONSp, NIL), listO(4, SGT_WALK_STELLA_CLASS, SYM_WALK_STELLA_STELLA_CLASSp, SYM_WALK_STELLA_SUBTYPE_OF_CLASSp, NIL), listO(4, SGT_WALK_STELLA_STORAGE_SLOT, SYM_WALK_STELLA_STORAGE_SLOTp, SYM_WALK_STELLA_SUBTYPE_OF_STORAGE_SLOTp, NIL), listO(4, SGT_WALK_STELLA_METHOD_SLOT, SYM_WALK_STELLA_METHOD_SLOTp, SYM_WALK_STELLA_SUBTYPE_OF_METHOD_SLOTp, NIL), listO(4, SGT_WALK_STELLA_ANCHORED_TYPE_SPECIFIER, SYM_WALK_STELLA_ANCHORED_TYPE_SPECIFIERp, SYM_WALK_STELLA_SUBTYPE_OF_ANCHORED_TYPE_SPECIFIERp, NIL), listO(4, SGT_WALK_STELLA_PARAMETRIC_TYPE_SPECIFIER, SYM_WALK_STELLA_PARAMETRIC_TYPE_SPECIFIERp, SYM_WALK_STELLA_SUBTYPE_OF_PARAMETRIC_TYPE_SPECIFIERp, NIL), NIL);
    oNUMERIC_TYPE_HIERARCHYo = list(4, SGT_WALK_STELLA_INTEGER, SGT_WALK_STELLA_LONG_INTEGER, SGT_WALK_STELLA_FLOAT, SGT_WALK_STELLA_NUMBER);
    oMIXIN_IMPLEMENTATION_STYLEo = KWD_WALK_SECOND_CLASS;
    oNATIVE_NAME_TABLEo = newHashTable();
  }
}

void helpStartupWalk10() {
  {
    defineFunctionObject("PRINT-STELLA-FEATURES", "(DEFUN PRINT-STELLA-FEATURES () :DOCUMENTATION \"Print the list of enabled and disabled STELLA features.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&printStellaFeatures)), NULL);
    defineFunctionObject("SET-STELLA-FEATURE", "(DEFUN SET-STELLA-FEATURE (|&REST| (FEATURES KEYWORD)) :DOCUMENTATION \"Enable all listed STELLA `features'.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&setStellaFeature)), ((cpp_function_code)(&setStellaFeatureEvaluatorWrapper)));
    defineFunctionObject("UNSET-STELLA-FEATURE", "(DEFUN UNSET-STELLA-FEATURE (|&REST| (FEATURES KEYWORD)) :DOCUMENTATION \"Disable all listed STELLA `features'.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&unsetStellaFeature)), ((cpp_function_code)(&unsetStellaFeatureEvaluatorWrapper)));
    defineFunctionObject("RESET-STELLA-FEATURES", "(DEFUN RESET-STELLA-FEATURES () :DOCUMENTATION \"Reset STELLA features to their default settings.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&resetStellaFeatures)), NULL);
    defineFunctionObject("ENABLED-STELLA-FEATURE?", "(DEFUN (ENABLED-STELLA-FEATURE? BOOLEAN) ((FEATURE KEYWORD)) :DOCUMENTATION \"Return true if the STELLA `feature' is currently enabled.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (MEMB? *CURRENT-STELLA-FEATURES* FEATURE)))", ((cpp_function_code)(&enabledStellaFeatureP)), NULL);
    defineFunctionObject("DISABLED-STELLA-FEATURE?", "(DEFUN (DISABLED-STELLA-FEATURE? BOOLEAN) ((FEATURE KEYWORD)) :DOCUMENTATION \"Return true if the STELLA `feature' is currently disabled.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (NOT (MEMB? *CURRENT-STELLA-FEATURES* FEATURE))))", ((cpp_function_code)(&disabledStellaFeatureP)), NULL);
    defineFunctionObject("TRACE-IF", "(DEFUN TRACE-IF ((KEYWORD OBJECT) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"If `keyword' is a trace keyword that has been enabled with `add-trace'\nprint all the elements in `body' to standard output.  Otherwise, do nothing.\n`keyword' can also be a list of keywords in which case printing is done if\none or more of them are trace enabled.\" :PUBLIC? TRUE)", ((cpp_function_code)(&traceIf)), NULL);
    defineFunctionObject("TRACE-KEYWORD?", "(DEFUN (TRACE-KEYWORD? BOOLEAN) ((KEYWORD OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&traceKeywordP)), NULL);
    defineFunctionObject("ADD-TRACE", "(DEFUN (ADD-TRACE LIST) (|&REST| (KEYWORDS GENERALIZED-SYMBOL)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Enable trace messages identified by any of the listed `keywords'.  After\ncalling (`add-trace' <keyword>) code guarded by (`trace-if' <keyword> ...)\nwill be executed when it is encountered.\")", ((cpp_function_code)(&addTrace)), ((cpp_function_code)(&addTraceEvaluatorWrapper)));
    defineFunctionObject("DROP-TRACE", "(DEFUN (DROP-TRACE LIST) (|&REST| (KEYWORDS GENERALIZED-SYMBOL)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Disable trace messages identified by any of the listed `keywords'.  After\ncalling (`drop-trace' <keyword>) code guarded by (`trace-if' <keyword> ...)\nwill not be executed when it is encountered.\")", ((cpp_function_code)(&dropTrace)), ((cpp_function_code)(&dropTraceEvaluatorWrapper)));
    defineFunctionObject("CLEAR-TRACE", "(DEFUN CLEAR-TRACE () :COMMAND? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Disable all tracing previously enabled with `add-trace'.\")", ((cpp_function_code)(&clearTrace)), NULL);
    defineFunctionObject("SET-OPTIMIZATION-LEVELS", "(DEFUN SET-OPTIMIZATION-LEVELS ((SAFETY INTEGER) (DEBUG INTEGER) (SPEED INTEGER) (SPACE INTEGER)) :DOCUMENTATION \"Set optimization levels for the qualities `safety', `debug',\n`speed', and `space'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&setOptimizationLevels)), NULL);
    defineFunctionObject("PRESERVE-TAIL-MERGE-OPTIMIZABILITY?", "(DEFUN (PRESERVE-TAIL-MERGE-OPTIMIZABILITY? BOOLEAN) ())", ((cpp_function_code)(&preserveTailMergeOptimizabilityP)), NULL);
    defineFunctionObject("METHOD-CALL-INLINING-ENABLED?", "(DEFUN (METHOD-CALL-INLINING-ENABLED? BOOLEAN) ())", ((cpp_function_code)(&methodCallInliningEnabledP)), NULL);
    defineFunctionObject("OPTIMIZE-BOOLEAN-TESTS?", "(DEFUN (OPTIMIZE-BOOLEAN-TESTS? BOOLEAN) ())", ((cpp_function_code)(&optimizeBooleanTestsP)), NULL);
    defineFunctionObject("CHECK-FOR-ILLEGAL-RETURN?", "(DEFUN (CHECK-FOR-ILLEGAL-RETURN? BOOLEAN) ())", ((cpp_function_code)(&checkForIllegalReturnP)), NULL);
    defineFunctionObject("SUPPORT-UNEXEC?", "(DEFUN (SUPPORT-UNEXEC? BOOLEAN) ())", ((cpp_function_code)(&supportUnexecP)), NULL);
    defineFunctionObject("NAME-QUOTED-TREE", "(DEFUN (NAME-QUOTED-TREE STRING) ((TREE CONS)))", ((cpp_function_code)(&nameQuotedTree)), NULL);
    defineFunctionObject("GET-QUOTED-TREE", "(DEFUN (GET-QUOTED-TREE CONS) ((TREE-NAME STRING) (MODULENAME STRING)) :DOCUMENTATION \"Return the quoted tree with name `tree-name'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getQuotedTree)), NULL);
    defineInlineMethodCode(SGT_WALK_STELLA_TRANSLATION_UNIT, SYM_WALK_STELLA_HOME_MODULE, wrapMethodCode(((cpp_method_code)(&TranslationUnit::homeModule))), NULL);
    defineFunctionObject("CLEAR-TRANSLATION-UNIT", "(DEFUN CLEAR-TRANSLATION-UNIT ((SELF TRANSLATION-UNIT)))", ((cpp_function_code)(&clearTranslationUnit)), NULL);
    defineFunctionObject("PRINT-TRANSLATION-UNIT", "(DEFUN PRINT-TRANSLATION-UNIT ((SELF TRANSLATION-UNIT) (STREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&printTranslationUnit)), NULL);
    defineFunctionObject("USE-HARDCODED-SYMBOLS?", "(DEFUN (USE-HARDCODED-SYMBOLS? BOOLEAN) ())", ((cpp_function_code)(&useHardcodedSymbolsP)), NULL);
    defineFunctionObject("TRANSLATOR-OUTPUT-LANGUAGE", "(DEFUN (TRANSLATOR-OUTPUT-LANGUAGE KEYWORD) () :GLOBALLY-INLINE? TRUE (RETURN *TRANSLATOROUTPUTLANGUAGE*))", ((cpp_function_code)(&translatorOutputLanguage)), NULL);
    defineFunctionObject("TRANSLATOR-OUTPUT-LANGUAGE-NAME", "(DEFUN (TRANSLATOR-OUTPUT-LANGUAGE-NAME STRING) ())", ((cpp_function_code)(&translatorOutputLanguageName)), NULL);
    defineFunctionObject("SET-TRANSLATOR-OUTPUT-LANGUAGE", "(DEFUN (SET-TRANSLATOR-OUTPUT-LANGUAGE KEYWORD) ((NEW-LANGUAGE KEYWORD)) :DOCUMENTATION \"Set output language to `new-language'.  Return previous language.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&setTranslatorOutputLanguage)), NULL);
    defineFunctionObject("TRANSLATE-TO-COMMON-LISP?", "(DEFUN (TRANSLATE-TO-COMMON-LISP? BOOLEAN) () :DOCUMENTATION \"Return `true' if current output language is Common-Lisp.\")", ((cpp_function_code)(&translateToCommonLispP)), NULL);
    defineFunctionObject("TRANSLATE-TO-CPP?", "(DEFUN (TRANSLATE-TO-CPP? BOOLEAN) () :DOCUMENTATION \"Return `true' if current output language is C++\")", ((cpp_function_code)(&translateToCppP)), NULL);
    defineFunctionObject("TRANSLATE-TO-JAVA?", "(DEFUN (TRANSLATE-TO-JAVA? BOOLEAN) () :DOCUMENTATION \"Return `true' if current output language is Java\")", ((cpp_function_code)(&translateToJavaP)), NULL);
    defineFunctionObject("TRANSLATE-TO-SINGLE-INHERITANCE-LANGUAGE?", "(DEFUN (TRANSLATE-TO-SINGLE-INHERITANCE-LANGUAGE? BOOLEAN) ())", ((cpp_function_code)(&translateToSingleInheritanceLanguageP)), NULL);
    defineFunctionObject("TOGGLE-OUTPUT-LANGUAGE", "(DEFUN (TOGGLE-OUTPUT-LANGUAGE KEYWORD) () :DOCUMENTATION \"Switch between Common Lisp and C++ as output languages.\")", ((cpp_function_code)(&toggleOutputLanguage)), NULL);
    defineFunctionObject("USE-BOOTSTRAP-TRANSLATOR?", "(DEFUN (USE-BOOTSTRAP-TRANSLATOR? BOOLEAN) ())", ((cpp_function_code)(&useBootstrapTranslatorP)), NULL);
    defineFunctionObject("TOGGLE-TRANSLATORS", "(DEFUN (TOGGLE-TRANSLATORS KEYWORD) ())", ((cpp_function_code)(&toggleTranslators)), NULL);
    defineFunctionObject("DECLARATION-OPERATOR?", "(DEFUN (DECLARATION-OPERATOR? BOOLEAN) ((OPERATOR SYMBOL)))", ((cpp_function_code)(&declarationOperatorP)), NULL);
    defineFunctionObject("DECLARATION-TREE?", "(DEFUN (DECLARATION-TREE? BOOLEAN) ((TREE CONS)) :PUBLIC? TRUE)", ((cpp_function_code)(&declarationTreeP)), NULL);
    defineFunctionObject("CREATE-ANNOTATION", "(DEFUN (CREATE-ANNOTATION STRING) ((TOP-LEVEL-TREE CONS)))", ((cpp_function_code)(&createAnnotation)), NULL);
    defineFunctionObject("WALK-TOP-LEVEL-TREE", "(DEFUN WALK-TOP-LEVEL-TREE ((TREE CONS) (CREATEANNOTATION? BOOLEAN)) :PUBLIC? TRUE)", ((cpp_function_code)(&walkTopLevelTree)), NULL);
    defineFunctionObject("WALK-TOP-LEVEL-EXPRESSION", "(DEFUN (WALK-TOP-LEVEL-EXPRESSION OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&walkTopLevelExpression)), NULL);
    defineFunctionObject("WALK-PHASE-ONE-UNIT", "(DEFUN WALK-PHASE-ONE-UNIT ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&walkPhaseOneUnit)), NULL);
    defineFunctionObject("WALK-AUXILIARY-TREE", "(DEFUN WALK-AUXILIARY-TREE ((TREE CONS)))", ((cpp_function_code)(&walkAuxiliaryTree)), NULL);
    defineFunctionObject("HELP-WALK-AUXILIARY-TREE", "(DEFUN (HELP-WALK-AUXILIARY-TREE TRANSLATION-UNIT) ((TREE CONS) (FINALIZE? BOOLEAN)))", ((cpp_function_code)(&helpWalkAuxiliaryTree)), NULL);
    defineFunctionObject("WALK-ALL-PHASE-ONE-UNITS", "(DEFUN WALK-ALL-PHASE-ONE-UNITS ())", ((cpp_function_code)(&walkAllPhaseOneUnits)), NULL);
    defineFunctionObject("TRANSLATE-ALL-UNITS", "(DEFUN TRANSLATE-ALL-UNITS ())", ((cpp_function_code)(&translateAllUnits)), NULL);
    defineFunctionObject("UNIT-INCLUDED-IN-OTHER-UNITS?", "(DEFUN (UNIT-INCLUDED-IN-OTHER-UNITS? BOOLEAN) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&unitIncludedInOtherUnitsP)), NULL);
    defineFunctionObject("COMBINE-TRANSLATED-TREES", "(DEFUN (COMBINE-TRANSLATED-TREES CONS) ())", ((cpp_function_code)(&combineTranslatedTrees)), NULL);
    defineFunctionObject("TRANSLATE-WALKED-TREE", "(DEFUN (TRANSLATE-WALKED-TREE OBJECT) ((CODETREE OBJECT)))", ((cpp_function_code)(&translateWalkedTree)), NULL);
    defineFunctionObject("INCREMENTALLY-TRANSLATE", "(DEFUN (INCREMENTALLY-TRANSLATE OBJECT) ((TREE OBJECT)) :DOCUMENTATION \"Translate a single Stella expression `tree' and return\nthe result.  For C++ and Java print the translation to standard output and\nreturn NIL instead.\" :PUBLIC? TRUE)", ((cpp_function_code)(&incrementallyTranslate)), NULL);
    defineFunctionObject("RESET-TRANSLATION-ERRORS", "(DEFUN RESET-TRANSLATION-ERRORS ())", ((cpp_function_code)(&resetTranslationErrors)), NULL);
    defineFunctionObject("SIGNAL-TRANSLATION-ERROR", "(DEFUN SIGNAL-TRANSLATION-ERROR () :PUBLIC? TRUE)", ((cpp_function_code)(&signalTranslationError)), NULL);
    defineFunctionObject("SIGNAL-TRANSLATION-WARNING", "(DEFUN SIGNAL-TRANSLATION-WARNING () :PUBLIC? TRUE)", ((cpp_function_code)(&signalTranslationWarning)), NULL);
    defineFunctionObject("SIGNAL-TRANSLATION-NOTE", "(DEFUN SIGNAL-TRANSLATION-NOTE () :PUBLIC? TRUE)", ((cpp_function_code)(&signalTranslationNote)), NULL);
    defineFunctionObject("IGNORE-TRANSLATION-ERRORS?", "(DEFUN (IGNORE-TRANSLATION-ERRORS? BOOLEAN) ())", ((cpp_function_code)(&ignoreTranslationErrorsP)), NULL);
    defineFunctionObject("TRANSLATION-ERRORS?", "(DEFUN (TRANSLATION-ERRORS? BOOLEAN) () :PUBLIC? TRUE)", ((cpp_function_code)(&translationErrorsP)), NULL);
    defineFunctionObject("SUMMARIZE-TRANSLATION-ERRORS", "(DEFUN SUMMARIZE-TRANSLATION-ERRORS ())", ((cpp_function_code)(&summarizeTranslationErrors)), NULL);
    defineFunctionObject("PRINT-ERROR-CONTEXT", "(DEFUN PRINT-ERROR-CONTEXT ((PREFIX STRING) (STREAM OUTPUT-STREAM)) :PUBLIC? TRUE)", ((cpp_function_code)(&printErrorContext)), NULL);
    defineFunctionObject("LOG-FUNCTION-CALL?", "(DEFUN (LOG-FUNCTION-CALL? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&logFunctionCallP)), NULL);
    defineFunctionObject("WRAP-BODY-WITH-LOG-FUNCTION-CALL-TREE", "(DEFUN (WRAP-BODY-WITH-LOG-FUNCTION-CALL-TREE CONS) ((METHOD METHOD-SLOT) (BODY CONS)))", ((cpp_function_code)(&wrapBodyWithLogFunctionCallTree)), NULL);
    defineFunctionObject("LOG-FUNCTION-CALL", "(DEFUN LOG-FUNCTION-CALL ((NAME STRING)))", ((cpp_function_code)(&logFunctionCall)), NULL);
    defineFunctionObject("START-FUNCTION-CALL-LOGGING", "(DEFUN START-FUNCTION-CALL-LOGGING ((FILENAME STRING)) :DOCUMENTATION \"Start function call logging to `fileName'.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&startFunctionCallLogging)), ((cpp_function_code)(&startFunctionCallLoggingEvaluatorWrapper)));
    defineFunctionObject("STOP-FUNCTION-CALL-LOGGING", "(DEFUN STOP-FUNCTION-CALL-LOGGING () :DOCUMENTATION \"Stop function call logging and close the current log file.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&stopFunctionCallLogging)), NULL);
  }
}

void helpStartupWalk11() {
  {
    defineFunctionObject("SET-CALL-LOG-BREAK-POINT", "(DEFUN SET-CALL-LOG-BREAK-POINT ((COUNT INTEGER)) :DOCUMENTATION \"Set a call log break point to `count'.  Execution will be\ninterrupted right at the entry of the `count'th logged function call.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&setCallLogBreakPoint)), ((cpp_function_code)(&setCallLogBreakPointEvaluatorWrapper)));
    defineFunctionObject("BREAK-PROGRAM", "(DEFUN BREAK-PROGRAM ((MESSAGE STRING)) :DOCUMENTATION \"Interrupt the program and print `message'.  Continue after\nconfirmation with the user.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&breakProgram)), ((cpp_function_code)(&breakProgramEvaluatorWrapper)));
    defineFunctionObject("TERMINATE-PROGRAM", "(DEFUN TERMINATE-PROGRAM () :DOCUMENTATION \"Terminate and exit the program with normal exit code.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&terminateProgram)), NULL);
    defineFunctionObject("PO", "(DEFUN PO ((THING OBJECT)))", ((cpp_function_code)(&po)), NULL);
    defineFunctionObject("VARIABLE-EQL?", "(DEFUN (VARIABLE-EQL? BOOLEAN) ((VAR1 SYMBOL) (VAR2 SYMBOL)))", ((cpp_function_code)(&variableEqlP)), NULL);
    defineFunctionObject("LOOKUP-VARIABLE-TABLE", "(DEFUN (LOOKUP-VARIABLE-TABLE (LIKE (ANY-VALUE SELF))) ((SELF (KEY-VALUE-LIST OF SYMBOL OBJECT)) (VARIABLE SYMBOL)))", ((cpp_function_code)(&lookupVariableTable)), NULL);
    defineFunctionObject("INSERT-AT-VARIABLE-TABLE", "(DEFUN INSERT-AT-VARIABLE-TABLE ((SELF (KEY-VALUE-LIST OF SYMBOL OBJECT)) (VARIABLE SYMBOL) (VALUE OBJECT)))", ((cpp_function_code)(&insertAtVariableTable)), NULL);
    defineFunctionObject("PUSH-VARIABLE-BINDING", "(DEFUN PUSH-VARIABLE-BINDING ((VARIABLE SYMBOL) (TYPE TYPE-SPEC)))", ((cpp_function_code)(&pushVariableBinding)), NULL);
    defineFunctionObject("POP-VARIABLE-BINDING", "(DEFUN POP-VARIABLE-BINDING ())", ((cpp_function_code)(&popVariableBinding)), NULL);
    defineFunctionObject("LOOKUP-VARIABLE-TYPE", "(DEFUN (LOOKUP-VARIABLE-TYPE TYPE-SPEC) ((VARIABLENAME SYMBOL)))", ((cpp_function_code)(&lookupVariableType)), NULL);
    defineFunctionObject("SET-LOCAL-VARIABLE-INFO", "(DEFUN SET-LOCAL-VARIABLE-INFO ((VARIABLE SYMBOL) (KEY KEYWORD) (INFO OBJECT)))", ((cpp_function_code)(&setLocalVariableInfo)), NULL);
    defineFunctionObject("GET-LOCAL-VARIABLE-INFO", "(DEFUN (GET-LOCAL-VARIABLE-INFO OBJECT) ((VARIABLE SYMBOL) (KEY KEYWORD)))", ((cpp_function_code)(&getLocalVariableInfo)), NULL);
    defineFunctionObject("REGISTER-REFERENCE-TO-GLOBAL-VARIABLE", "(DEFUN REGISTER-REFERENCE-TO-GLOBAL-VARIABLE ((VARIABLENAME SYMBOL)))", ((cpp_function_code)(&registerReferenceToGlobalVariable)), NULL);
    defineFunctionObject("LOCAL-GENSYM", "(DEFUN (LOCAL-GENSYM SYMBOL) ((PREFIX STRING)))", ((cpp_function_code)(&localGensym)), NULL);
    defineFunctionObject("METHOD-GENSYM", "(DEFUN (METHOD-GENSYM SYMBOL) ((PREFIX STRING)))", ((cpp_function_code)(&methodGensym)), NULL);
    defineFunctionObject("YIELD-LOCAL-VARIABLE-ALIAS", "(DEFUN (YIELD-LOCAL-VARIABLE-ALIAS SYMBOL) ((VARIABLE SYMBOL) (LEVEL INTEGER)))", ((cpp_function_code)(&yieldLocalVariableAlias)), NULL);
    defineFunctionObject("RENAME-SHADOWING-LOCAL-VARIABLES?", "(DEFUN (RENAME-SHADOWING-LOCAL-VARIABLES? BOOLEAN) () :GLOBALLY-INLINE? TRUE (RETURN (EQL? (TRANSLATOR-OUTPUT-LANGUAGE) :JAVA)))", ((cpp_function_code)(&renameShadowingLocalVariablesP)), NULL);
    defineFunctionObject("MAYBE-RENAME-LOCAL-VARIABLE", "(DEFUN MAYBE-RENAME-LOCAL-VARIABLE ((VARIABLE SYMBOL)))", ((cpp_function_code)(&maybeRenameLocalVariable)), NULL);
    defineFunctionObject("TRUE-VARIABLE-NAME", "(DEFUN (TRUE-VARIABLE-NAME SYMBOL) ((VARIABLE SYMBOL)))", ((cpp_function_code)(&trueVariableName)), NULL);
    defineFunctionObject("SUPPRESS-WARNINGS?", "(DEFUN (SUPPRESS-WARNINGS? BOOLEAN) () :PUBLIC? TRUE)", ((cpp_function_code)(&suppressWarningsP)), NULL);
    defineFunctionObject("BAD-ARGUMENT-RANGE?", "(DEFUN (BAD-ARGUMENT-RANGE? BOOLEAN) ((TREE CONS) (MINARITY INTEGER) (MAXARITY INTEGER)))", ((cpp_function_code)(&badArgumentRangeP)), NULL);
    defineFunctionObject("BAD-ARGUMENT-COUNT?", "(DEFUN (BAD-ARGUMENT-COUNT? BOOLEAN) ((TREE CONS) (ARITY INTEGER)))", ((cpp_function_code)(&badArgumentCountP)), NULL);
    defineFunctionObject("YIELD-ILLEGAL-STATEMENT-TREE", "(DEFUN (YIELD-ILLEGAL-STATEMENT-TREE CONS) ())", ((cpp_function_code)(&yieldIllegalStatementTree)), NULL);
    defineFunctionObject("YIELD-ILLEGAL-EXPRESSION-TREE", "(DEFUN (YIELD-ILLEGAL-EXPRESSION-TREE OBJECT) ())", ((cpp_function_code)(&yieldIllegalExpressionTree)), NULL);
    defineFunctionObject("WALK-DONT-CALL-ME-TREE", "(DEFUN (WALK-DONT-CALL-ME-TREE CONS TYPE-SPEC) ((TREE OBJECT) (RETURNTYPE TYPE-SPEC)))", ((cpp_function_code)(&walkDontCallMeTree)), NULL);
    defineFunctionObject("ILLEGAL-TREE?", "(DEFUN (ILLEGAL-TREE? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&illegalTreeP)), NULL);
    defineFunctionObject("NATIVE-CLASS-METHOD-INLINING?", "(DEFUN (NATIVE-CLASS-METHOD-INLINING? BOOLEAN) ())", ((cpp_function_code)(&nativeClassMethodInliningP)), NULL);
    defineFunctionObject("PROGNIFY", "(DEFUN (PROGNIFY OBJECT) ((TREES CONS)))", ((cpp_function_code)(&prognify)), NULL);
    defineFunctionObject("OPTIMIZE-PROGN", "(DEFUN (OPTIMIZE-PROGN OBJECT) ((PROGN-TREE CONS)))", ((cpp_function_code)(&optimizeProgn)), NULL);
    defineFunctionObject("TREE-TO-TREES", "(DEFUN (TREE-TO-TREES CONS) ((TREE OBJECT)))", ((cpp_function_code)(&treeToTrees)), NULL);
    defineFunctionObject("WRAPPED-TYPE-TO-TYPE", "(DEFUN (WRAPPED-TYPE-TO-TYPE TYPE) ((SELF TYPE)) :DOCUMENTATION \"Return the unwrapped type for the wrapped type `self',\nor `self' if it is not a wrapped type.\" :PUBLIC? TRUE)", ((cpp_function_code)(&wrappedTypeToType)), NULL);
    defineFunctionObject("WRAPPER-VALUE-TYPE", "(DEFUN (WRAPPER-VALUE-TYPE TYPE) ((SELF WRAPPER)) :DOCUMENTATION \"Return the type of the value stored in the wrapper `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&wrapperValueType)), NULL);
    defineMethodObject("(DEFMETHOD (TYPE-TO-WRAPPED-TYPE TYPE) ((SELF TYPE)) :DOCUMENTATION \"Return the wrapped type for the type `self',\nor 'self' if it is not a bare literal type.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Surrogate::typeToWrappedType))), NULL);
    defineFunctionObject("LOOKUP-COERSION-METHOD", "(DEFUN (LOOKUP-COERSION-METHOD OBJECT) ((SOURCETYPE TYPE) (TARGETTYPE TYPE) (EXPRESSION OBJECT)))", ((cpp_function_code)(&lookupCoersionMethod)), NULL);
    defineFunctionObject("APPLY-COERCION-METHOD", "(DEFUN (APPLY-COERCION-METHOD OBJECT TYPE-SPEC) ((EXPRESSION OBJECT) (SOURCETYPE TYPE) (TARGETTYPE TYPE) (COERCIONMETHOD OBJECT)))", ((cpp_function_code)(&applyCoercionMethod)), NULL);
    defineFunctionObject("TRANSLATING-CODE?", "(DEFUN (TRANSLATING-CODE? BOOLEAN) ())", ((cpp_function_code)(&translatingCodeP)), NULL);
    defineFunctionObject("VERIFY-TYPE", "(DEFUN (VERIFY-TYPE TYPE) ((SELF TYPE)))", ((cpp_function_code)(&verifyType)), NULL);
    defineFunctionObject("SAFE-SUBTYPE-OF?", "(DEFUN (SAFE-SUBTYPE-OF? BOOLEAN) ((SUBTYPE TYPE) (SUPERTYPE TYPE)))", ((cpp_function_code)(&safeSubtypeOfP)), NULL);
    defineFunctionObject("WARN-ABOUT-UNKNOWN-SOURCE-TYPE", "(DEFUN WARN-ABOUT-UNKNOWN-SOURCE-TYPE ((TREE OBJECT)))", ((cpp_function_code)(&warnAboutUnknownSourceType)), NULL);
    defineFunctionObject("COERCE-A-TREE", "(DEFUN (COERCE-A-TREE OBJECT TYPE-SPEC) ((TREE OBJECT) (SOURCETYPE TYPE-SPEC) (TARGETTYPE TYPE-SPEC)))", ((cpp_function_code)(&coerceATree)), NULL);
    defineFunctionObject("HELP-COERCE-A-TREE", "(DEFUN (HELP-COERCE-A-TREE OBJECT TYPE-SPEC BOOLEAN) ((TREE OBJECT) (SOURCETYPE TYPE-SPEC) (TARGETTYPE TYPE-SPEC) (TESTONLY? BOOLEAN)))", ((cpp_function_code)(&helpCoerceATree)), NULL);
    defineFunctionObject("COERCIBLE?", "(DEFUN (COERCIBLE? BOOLEAN) ((TREE OBJECT) (SOURCETYPE TYPE-SPEC) (TARGETTYPE TYPE-SPEC)))", ((cpp_function_code)(&coercibleP)), NULL);
    defineFunctionObject("WALKING-EXPRESSION?", "(DEFUN (WALKING-EXPRESSION? BOOLEAN) ())", ((cpp_function_code)(&walkingExpressionP)), NULL);
    defineFunctionObject("WALK-EXPRESSION-TREE", "(DEFUN (WALK-EXPRESSION-TREE OBJECT TYPE-SPEC) ((EXPTREE OBJECT) (TARGETTYPE TYPE-SPEC) (OPERATORNAME SYMBOL) (VRLETISOK? BOOLEAN)))", ((cpp_function_code)(&walkExpressionTree)), NULL);
    defineFunctionObject("COMPUTE-EXPRESSION-TYPE", "(DEFUN (COMPUTE-EXPRESSION-TYPE TYPE-SPEC) ((EXPRESSION OBJECT) (WRAP? BOOLEAN)))", ((cpp_function_code)(&computeExpressionType)), NULL);
    defineFunctionObject("WALK-WITHOUT-TYPE-TREE", "(DEFUN (WALK-WITHOUT-TYPE-TREE OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&walkWithoutTypeTree)), NULL);
    defineFunctionObject("WALK-LIST-OF-TREES", "(DEFUN (WALK-LIST-OF-TREES CONS) ((TREES CONS)))", ((cpp_function_code)(&walkListOfTrees)), NULL);
    defineFunctionObject("WALK-LIST-OF-STATEMENTS", "(DEFUN (WALK-LIST-OF-STATEMENTS CONS) ((TREES CONS)))", ((cpp_function_code)(&walkListOfStatements)), NULL);
    defineFunctionObject("WALK-STATEMENT", "(DEFUN (WALK-STATEMENT OBJECT) ((TREE OBJECT) (WARNONATOM? BOOLEAN)))", ((cpp_function_code)(&walkStatement)), NULL);
    defineFunctionObject("ELIMINATE-VRLET-STATEMENT", "(DEFUN (ELIMINATE-VRLET-STATEMENT CONS) ((TREE CONS)))", ((cpp_function_code)(&eliminateVrletStatement)), NULL);
    defineFunctionObject("SYS-TREE", "(DEFUN (SYS-TREE CONS TYPE-SPEC) ((TREE OBJECT) (TYPESPEC TYPE-SPEC)))", ((cpp_function_code)(&sysTree)), NULL);
    defineFunctionObject("WALKED-EXPRESSION-TYPE", "(DEFUN (WALKED-EXPRESSION-TYPE TYPE-SPEC) ((TREE OBJECT)))", ((cpp_function_code)(&walkedExpressionType)), NULL);
    defineFunctionObject("WALKED-EXPRESSION-EXPRESSION", "(DEFUN (WALKED-EXPRESSION-EXPRESSION OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&walkedExpressionExpression)), NULL);
    defineFunctionObject("NEED-IDENTICAL-METHOD-SIGNATURES?", "(DEFUN (NEED-IDENTICAL-METHOD-SIGNATURES? BOOLEAN) ())", ((cpp_function_code)(&needIdenticalMethodSignaturesP)), NULL);
    defineFunctionObject("COMPUTE-MOST-GENERAL-RETURN-TYPE", "(DEFUN (COMPUTE-MOST-GENERAL-RETURN-TYPE TYPE-SPEC) ((METHOD METHOD-SLOT) (RETURNTYPE TYPE-SPEC)))", ((cpp_function_code)(&computeMostGeneralReturnType)), NULL);
    defineFunctionObject("COMPUTE-REAL-SLOT-TYPE", "(DEFUN (COMPUTE-REAL-SLOT-TYPE TYPE-SPEC) ((SLOT STORAGE-SLOT) (FIRSTARGTYPE TYPE-SPEC) (RETURNTYPE TYPE-SPEC)))", ((cpp_function_code)(&computeRealSlotType)), NULL);
    defineFunctionObject("SYS-TREE-IF-NEEDED", "(DEFUN (SYS-TREE-IF-NEEDED OBJECT TYPE-SPEC) ((SLOT SLOT) (TREE OBJECT) (FIRSTARGTYPE TYPE-SPEC) (RETURNTYPE TYPE-SPEC)))", ((cpp_function_code)(&sysTreeIfNeeded)), NULL);
    defineFunctionObject("TARGET-LANGUAGE-TYPE", "(DEFUN (TARGET-LANGUAGE-TYPE TYPE) ((TREE OBJECT)))", ((cpp_function_code)(&targetLanguageType)), NULL);
    defineFunctionObject("SET-TARGET-LANGUAGE-TYPE", "(DEFUN (SET-TARGET-LANGUAGE-TYPE CONS TYPE-SPEC) ((SYSTREE CONS) (TYPE TYPE)))", ((cpp_function_code)(&setTargetLanguageType)), NULL);
    defineFunctionObject("WALK-A-TREE", "(DEFUN (WALK-A-TREE OBJECT TYPE-SPEC) ((TREE OBJECT)))", ((cpp_function_code)(&walkATree)), NULL);
  }
}

void helpStartupWalk12() {
  {
    defineFunctionObject("HELP-WALK-A-TREE", "(DEFUN (HELP-WALK-A-TREE OBJECT TYPE-SPEC) ((TREE OBJECT)))", ((cpp_function_code)(&helpWalkATree)), NULL);
    defineFunctionObject("WALK-A-CONS-TREE", "(DEFUN (WALK-A-CONS-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkAConsTree)), NULL);
    defineFunctionObject("INCREMENTAL-TRANSLATION?", "(DEFUN (INCREMENTAL-TRANSLATION? BOOLEAN) ())", ((cpp_function_code)(&incrementalTranslationP)), NULL);
    defineFunctionObject("CONSTRUCT-SYMBOL-CONSTANT-NAME", "(DEFUN (CONSTRUCT-SYMBOL-CONSTANT-NAME STRING) ((SYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&constructSymbolConstantName)), NULL);
    defineFunctionObject("YIELD-SYMBOL-CONSTANT-NAME", "(DEFUN (YIELD-SYMBOL-CONSTANT-NAME SYMBOL) ((SYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&yieldSymbolConstantName)), NULL);
    defineFunctionObject("CREATE-STARTUP-SYMBOL", "(DEFUN (CREATE-STARTUP-SYMBOL SYMBOL) ((SYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&createStartupSymbol)), NULL);
    defineFunctionObject("REGISTER-SYMBOL", "(DEFUN (REGISTER-SYMBOL GENERALIZED-SYMBOL) ((SYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&registerSymbol)), NULL);
    defineFunctionObject("CLEAR-SYMBOL-REGISTRY", "(DEFUN CLEAR-SYMBOL-REGISTRY ())", ((cpp_function_code)(&clearSymbolRegistry)), NULL);
    defineFunctionObject("YIELD-HARDCODED-INTERN-REGISTERED-SYMBOLS-TREE", "(DEFUN (YIELD-HARDCODED-INTERN-REGISTERED-SYMBOLS-TREE CONS) ())", ((cpp_function_code)(&yieldHardcodedInternRegisteredSymbolsTree)), NULL);
    defineMethodObject("(DEFMETHOD (WALK-ATOMIC-TREE OBJECT TYPE-SPEC) ((SELF OBJECT)))", wrapMethodCode(((cpp_method_code)(&Object::walkAtomicTree))), NULL);
    defineMethodObject("(DEFMETHOD (WALK-ATOMIC-TREE OBJECT TYPE-SPEC) ((SELF WRAPPER)))", wrapMethodCode(((cpp_method_code)(&Wrapper::walkAtomicTree))), NULL);
    defineFunctionObject("LOOKUP-CONSTANT-SYMBOL", "(DEFUN (LOOKUP-CONSTANT-SYMBOL TYPE) ((SELF SYMBOL)))", ((cpp_function_code)(&lookupConstantSymbol)), NULL);
    defineFunctionObject("CONSTANT-SYMBOL?", "(DEFUN (CONSTANT-SYMBOL? BOOLEAN) ((SYMBOL SYMBOL)))", ((cpp_function_code)(&constantSymbolP)), NULL);
    defineFunctionObject("WALK-CONSTANT-SYMBOL", "(DEFUN (WALK-CONSTANT-SYMBOL SYMBOL TYPE) ((SELF SYMBOL)))", ((cpp_function_code)(&walkConstantSymbol)), NULL);
    defineMethodObject("(DEFMETHOD (WALK-ATOMIC-TREE OBJECT TYPE-SPEC) ((SELF SYMBOL)))", wrapMethodCode(((cpp_method_code)(&Symbol::walkAtomicTree))), NULL);
    defineMethodObject("(DEFMETHOD (WALK-ATOMIC-TREE OBJECT TYPE-SPEC) ((SELF KEYWORD)))", wrapMethodCode(((cpp_method_code)(&Keyword::walkAtomicTree))), NULL);
    defineMethodObject("(DEFMETHOD (WALK-ATOMIC-TREE OBJECT TYPE-SPEC) ((SELF SURROGATE)))", wrapMethodCode(((cpp_method_code)(&Surrogate::walkAtomicTree))), NULL);
    defineFunctionObject("ATOMIC-EXPRESSION?", "(DEFUN (ATOMIC-EXPRESSION? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&atomicExpressionP)), NULL);
    defineFunctionObject("VARIABLE-EXPRESSION?", "(DEFUN (VARIABLE-EXPRESSION? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&variableExpressionP)), NULL);
    defineFunctionObject("VRLET-EXPRESSION?", "(DEFUN (VRLET-EXPRESSION? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&vrletExpressionP)), NULL);
    defineFunctionObject("PROCEDURAL-EXPRESSION?", "(DEFUN (PROCEDURAL-EXPRESSION? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&proceduralExpressionP)), NULL);
    defineFunctionObject("SUBSTITUTE-ONCE", "(DEFUN (SUBSTITUTE-ONCE BOOLEAN) ((EXPRESSION OBJECT) (NEWTREE OBJECT) (OLDTREE OBJECT)))", ((cpp_function_code)(&substituteOnce)), NULL);
    defineFunctionObject("TRANSFORM-VRLET-EXPRESSION", "(DEFUN (TRANSFORM-VRLET-EXPRESSION CONS TYPE-SPEC) ((STATEMENT CONS) (VREXPRESSION CONS)))", ((cpp_function_code)(&transformVrletExpression)), NULL);
    defineFunctionObject("HELP-TRANSFORM-BOOLEAN-PROCEDURAL-EXPRESSION", "(DEFUN (HELP-TRANSFORM-BOOLEAN-PROCEDURAL-EXPRESSION CONS) ((EXPRESSION OBJECT) (TESTVARIABLE SYMBOL)))", ((cpp_function_code)(&helpTransformBooleanProceduralExpression)), NULL);
    defineFunctionObject("TRANSFORM-BOOLEAN-PROCEDURAL-EXPRESSION", "(DEFUN (TRANSFORM-BOOLEAN-PROCEDURAL-EXPRESSION CONS TYPE-SPEC) ((STATEMENT CONS) (VREXPRESSION CONS)))", ((cpp_function_code)(&transformBooleanProceduralExpression)), NULL);
    defineFunctionObject("PERCOLATE-OUT-BOOLEAN-VRLET-EXPRESSIONS", "(DEFUN (PERCOLATE-OUT-BOOLEAN-VRLET-EXPRESSIONS CONS) ((BOOLEANEXPRESSION CONS)))", ((cpp_function_code)(&percolateOutBooleanVrletExpressions)), NULL);
    defineFunctionObject("TRANSFORM-PROCEDURAL-EXPRESSION", "(DEFUN (TRANSFORM-PROCEDURAL-EXPRESSION CONS TYPE-SPEC) ((STATEMENT CONS) (VREXPRESSION CONS) (TYPE TYPE-SPEC)))", ((cpp_function_code)(&transformProceduralExpression)), NULL);
    defineFunctionObject("PERCOLATE-OUT-VRLET-EXPRESSION", "(DEFUN (PERCOLATE-OUT-VRLET-EXPRESSION CONS TYPE-SPEC) ((STATEMENT CONS) (VREXPRESSION CONS) (TYPE TYPE-SPEC)))", ((cpp_function_code)(&percolateOutVrletExpression)), NULL);
    defineFunctionObject("WALK-SETQ-TREE", "(DEFUN (WALK-SETQ-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkSetqTree)), NULL);
    defineFunctionObject("YIELD-FIXED-SLOT-VALUE-SETTER-TREE", "(DEFUN (YIELD-FIXED-SLOT-VALUE-SETTER-TREE CONS) ((SLOT SLOT) (OBJECTREF OBJECT) (VALUETREE OBJECT)))", ((cpp_function_code)(&yieldFixedSlotValueSetterTree)), NULL);
    defineFunctionObject("WALK-SETF-TREE", "(DEFUN (WALK-SETF-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkSetfTree)), NULL);
    defineFunctionObject("YIELD-DYNAMIC-SLOT-VALUE-TREE", "(DEFUN (YIELD-DYNAMIC-SLOT-VALUE-TREE CONS) ((SLOT STORAGE-SLOT) (OBJECTREF OBJECT) (RETURNTYPE TYPE-SPEC)))", ((cpp_function_code)(&yieldDynamicSlotValueTree)), NULL);
    defineFunctionObject("YIELD-DYNAMIC-SLOT-VALUE-SETTER-TREE", "(DEFUN (YIELD-DYNAMIC-SLOT-VALUE-SETTER-TREE CONS) ((SLOT STORAGE-SLOT) (OBJECTREF OBJECT) (VALUEREF OBJECT) (RETURNTYPE TYPE-SPEC)))", ((cpp_function_code)(&yieldDynamicSlotValueSetterTree)), NULL);
    defineFunctionObject("YIELD-NATIVE-SLOT-VALUE-TREE", "(DEFUN (YIELD-NATIVE-SLOT-VALUE-TREE CONS) ((SLOT STORAGE-SLOT) (OBJECTREF OBJECT) (OBJECTTYPE TYPE-SPEC)))", ((cpp_function_code)(&yieldNativeSlotValueTree)), NULL);
    defineFunctionObject("YIELD-CONTEXT-SENSITIVE-SLOT-VALUE-TREE", "(DEFUN (YIELD-CONTEXT-SENSITIVE-SLOT-VALUE-TREE CONS TYPE-SPEC) ((SLOT STORAGE-SLOT) (OBJECTREF OBJECT) (RETURNTYPE TYPE-SPEC) (CSOPTIONS CONS)))", ((cpp_function_code)(&yieldContextSensitiveSlotValueTree)), NULL);
    defineFunctionObject("YIELD-SLOT-VALUE-TREE", "(DEFUN (YIELD-SLOT-VALUE-TREE CONS TYPE-SPEC) ((SLOT STORAGE-SLOT) (OBJECTREF OBJECT) (OBJECTTYPE TYPE-SPEC) (RETURNTYPE TYPE-SPEC) (CSOPTIONS CONS)))", ((cpp_function_code)(&yieldSlotValueTree)), NULL);
    defineFunctionObject("WALK-SLOT-VALUE-TREE", "(DEFUN (WALK-SLOT-VALUE-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkSlotValueTree)), NULL);
    defineFunctionObject("YIELD-NATIVE-SLOT-VALUE-SETTER-TREE", "(DEFUN (YIELD-NATIVE-SLOT-VALUE-SETTER-TREE CONS) ((SLOT STORAGE-SLOT) (OBJECTREF OBJECT) (OBJECTTYPE TYPE-SPEC) (VALUEREF OBJECT)))", ((cpp_function_code)(&yieldNativeSlotValueSetterTree)), NULL);
    defineFunctionObject("YIELD-CONTEXT-SENSITIVE-SLOT-VALUE-SETTER-TREE", "(DEFUN (YIELD-CONTEXT-SENSITIVE-SLOT-VALUE-SETTER-TREE CONS TYPE-SPEC) ((SLOT STORAGE-SLOT) (OBJECTREF OBJECT) (VALUEREF OBJECT) (RETURNTYPE TYPE-SPEC) (CSOPTIONS CONS)))", ((cpp_function_code)(&yieldContextSensitiveSlotValueSetterTree)), NULL);
    defineFunctionObject("YIELD-SLOT-VALUE-SETTER-TREE", "(DEFUN (YIELD-SLOT-VALUE-SETTER-TREE CONS TYPE-SPEC) ((SLOT STORAGE-SLOT) (OBJECTREF OBJECT) (OBJECTTYPE TYPE-SPEC) (VALUEREF OBJECT) (RETURNTYPE TYPE-SPEC) (CSOPTIONS CONS)))", ((cpp_function_code)(&yieldSlotValueSetterTree)), NULL);
    defineFunctionObject("WALK-SLOT-VALUE-SETTER-TREE", "(DEFUN (WALK-SLOT-VALUE-SETTER-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkSlotValueSetterTree)), NULL);
    defineFunctionObject("WALK-AREF-TREE", "(DEFUN (WALK-AREF-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkArefTree)), NULL);
    defineFunctionObject("SAFE-YIELD-TYPE-SPECIFIER", "(DEFUN (SAFE-YIELD-TYPE-SPECIFIER TYPE-SPEC) ((TYPETREE OBJECT)))", ((cpp_function_code)(&safeYieldTypeSpecifier)), NULL);
    defineFunctionObject("WALK-A-DECLARATION", "(DEFUN (WALK-A-DECLARATION CONS) ((VARIABLE SYMBOL) (TYPETREE OBJECT) (VALUE OBJECT) (INPUTPARAMETER? BOOLEAN)))", ((cpp_function_code)(&walkADeclaration)), NULL);
    defineFunctionObject("WALK-VARIABLE-DECLARATIONS", "(DEFUN (WALK-VARIABLE-DECLARATIONS CONS) ((DECLARATIONS CONS)))", ((cpp_function_code)(&walkVariableDeclarations)), NULL);
    defineFunctionObject("TRANSFORM-LET-WITH-PROCEDURAL-EXPRESSION", "(DEFUN (TRANSFORM-LET-WITH-PROCEDURAL-EXPRESSION CONS) ((TREE CONS)))", ((cpp_function_code)(&transformLetWithProceduralExpression)), NULL);
    defineFunctionObject("POP-LOCAL-VARIABLE-BINDINGS", "(DEFUN POP-LOCAL-VARIABLE-BINDINGS ((DECLARATIONS CONS)))", ((cpp_function_code)(&popLocalVariableBindings)), NULL);
    defineFunctionObject("WALK-LET-TREE", "(DEFUN (WALK-LET-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkLetTree)), NULL);
    defineFunctionObject("SPECIAL-IMPLEMENTATION-STYLE", "(DEFUN (SPECIAL-IMPLEMENTATION-STYLE KEYWORD) ())", ((cpp_function_code)(&specialImplementationStyle)), NULL);
    defineFunctionObject("PUSH-SPECIAL", "(DEFUN PUSH-SPECIAL ((VARIABLE SYMBOL) (OLDVALUEVARIABLE SYMBOL)))", ((cpp_function_code)(&pushSpecial)), NULL);
    defineFunctionObject("POP-SPECIAL", "(DEFUN POP-SPECIAL ())", ((cpp_function_code)(&popSpecial)), NULL);
    defineFunctionObject("LOOKUP-OLD-VALUE-VARIABLE", "(DEFUN (LOOKUP-OLD-VALUE-VARIABLE SYMBOL) ((VARIABLE SYMBOL)))", ((cpp_function_code)(&lookupOldValueVariable)), NULL);
    defineFunctionObject("NEED-TO-UNBIND-SPECIALS?", "(DEFUN (NEED-TO-UNBIND-SPECIALS? BOOLEAN) ())", ((cpp_function_code)(&needToUnbindSpecialsP)), NULL);
    defineFunctionObject("YIELD-SPECIAL-UNBIND-TREE", "(DEFUN (YIELD-SPECIAL-UNBIND-TREE CONS) ((NOFBINDINGS INTEGER)))", ((cpp_function_code)(&yieldSpecialUnbindTree)), NULL);
    defineFunctionObject("YIELD-RETURN-SPECIAL-UNBIND-TREE", "(DEFUN (YIELD-RETURN-SPECIAL-UNBIND-TREE CONS) ())", ((cpp_function_code)(&yieldReturnSpecialUnbindTree)), NULL);
    defineFunctionObject("YIELD-LOOP-EXIT-SPECIAL-UNBIND-TREE", "(DEFUN (YIELD-LOOP-EXIT-SPECIAL-UNBIND-TREE CONS) ())", ((cpp_function_code)(&yieldLoopExitSpecialUnbindTree)), NULL);
    defineFunctionObject("WALK-SPECIAL-TREE", "(DEFUN (WALK-SPECIAL-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkSpecialTree)), NULL);
    defineFunctionObject("WALK-CL-SPECIAL-TREE", "(DEFUN (WALK-CL-SPECIAL-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkClSpecialTree)), NULL);
    defineFunctionObject("WALK-UNWIND-PROTECT-SPECIAL-TREE", "(DEFUN (WALK-UNWIND-PROTECT-SPECIAL-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkUnwindProtectSpecialTree)), NULL);
    defineFunctionObject("WALK-CAST-TREE", "(DEFUN (WALK-CAST-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkCastTree)), NULL);
  }
}

void helpStartupWalk13() {
  {
    defineFunctionObject("VALUES-TREE?", "(DEFUN (VALUES-TREE? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&valuesTreeP)), NULL);
    defineFunctionObject("WALK-VALUES-TREE", "(DEFUN (WALK-VALUES-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkValuesTree)), NULL);
    defineFunctionObject("WALK-MV-EXPRESSION-TREE", "(DEFUN (WALK-MV-EXPRESSION-TREE OBJECT CONS (LIST OF TYPE-SPEC)) ((TREE OBJECT) (TARGETTYPES (LIST OF TYPE-SPEC)) (OPERATOR SYMBOL)))", ((cpp_function_code)(&walkMvExpressionTree)), NULL);
    defineFunctionObject("LISTIFY-TYPE-SPEC", "(DEFUN (LISTIFY-TYPE-SPEC (LIST OF TYPE-SPEC)) ((TYPESPEC TYPE-SPEC)))", ((cpp_function_code)(&listifyTypeSpec)), NULL);
    defineFunctionObject("SLOT-FROM-EXPRESSION-TREE", "(DEFUN (SLOT-FROM-EXPRESSION-TREE SLOT) ((TREE CONS)))", ((cpp_function_code)(&slotFromExpressionTree)), NULL);
    defineFunctionObject("WALK-MV-TREE", "(DEFUN (WALK-MV-TREE OBJECT CONS (LIST OF TYPE-SPEC)) ((TREE OBJECT)))", ((cpp_function_code)(&walkMvTree)), NULL);
    defineFunctionObject("WALK-MV-VALUES-TREE", "(DEFUN (WALK-MV-VALUES-TREE CONS CONS (LIST OF TYPE-SPEC)) ((TREE CONS)))", ((cpp_function_code)(&walkMvValuesTree)), NULL);
    defineFunctionObject("COERCE-MV-TREE", "(DEFUN (COERCE-MV-TREE OBJECT CONS (LIST OF TYPE-SPEC)) ((TREE OBJECT) (OPERATOR SYMBOL) (SOURCETYPES (LIST OF TYPE-SPEC)) (TARGETTYPES (LIST OF TYPE-SPEC))))", ((cpp_function_code)(&coerceMvTree)), NULL);
    defineFunctionObject("WALK-RETURN-AND-UNBIND-SPECIALS", "(DEFUN (WALK-RETURN-AND-UNBIND-SPECIALS CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkReturnAndUnbindSpecials)), NULL);
    defineFunctionObject("WALK-RETURN-TREE", "(DEFUN (WALK-RETURN-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkReturnTree)), NULL);
    defineFunctionObject("WALK-MV-SETQ-TREE", "(DEFUN (WALK-MV-SETQ-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkMvSetqTree)), NULL);
    defineFunctionObject("WALK-MV-BIND-TREE", "(DEFUN (WALK-MV-BIND-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkMvBindTree)), NULL);
    defineFunctionObject("WALK-LOOP-TREE", "(DEFUN (WALK-LOOP-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkLoopTree)), NULL);
    defineFunctionObject("WALK-LOOP-EXIT-TREE", "(DEFUN (WALK-LOOP-EXIT-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkLoopExitTree)), NULL);
    defineFunctionObject("WALK-WHILE-TREE", "(DEFUN (WALK-WHILE-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkWhileTree)), NULL);
    defineFunctionObject("WALK-CONDITIONAL-TREE", "(DEFUN (WALK-CONDITIONAL-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkConditionalTree)), NULL);
    defineFunctionObject("WALK-CHOOSE-TREE", "(DEFUN (WALK-CHOOSE-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkChooseTree)), NULL);
    defineFunctionObject("WALK-BOOLEAN-TREE", "(DEFUN (WALK-BOOLEAN-TREE OBJECT TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkBooleanTree)), NULL);
    defineFunctionObject("AND-OR-NOT-TREE?", "(DEFUN (AND-OR-NOT-TREE? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&andOrNotTreeP)), NULL);
    defineFunctionObject("HELP-WALK-BOOLEAN-TREE", "(DEFUN (HELP-WALK-BOOLEAN-TREE OBJECT) ((TREE CONS)))", ((cpp_function_code)(&helpWalkBooleanTree)), NULL);
    defineFunctionObject("WALK-COND-TREE", "(DEFUN (WALK-COND-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkCondTree)), NULL);
    defineFunctionObject("COND-TREE-TO-IF-TREE", "(DEFUN (COND-TREE-TO-IF-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&condTreeToIfTree)), NULL);
    defineFunctionObject("YIELD-HARDCODED-CASE-SYMBOL-ID-OR-IDS", "(DEFUN (YIELD-HARDCODED-CASE-SYMBOL-ID-OR-IDS OBJECT) ((CASETEST OBJECT)))", ((cpp_function_code)(&yieldHardcodedCaseSymbolIdOrIds)), NULL);
    defineFunctionObject("WALK-HARDCODED-SYMBOL-CASE-TREE", "(DEFUN (WALK-HARDCODED-SYMBOL-CASE-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkHardcodedSymbolCaseTree)), NULL);
    defineFunctionObject("YIELD-ISA?-CASE-TEST", "(DEFUN (YIELD-ISA?-CASE-TEST CONS) ((CASEKEY TYPE) (TESTEXPRESSION OBJECT)))", ((cpp_function_code)(&yieldIsaPCaseTest)), NULL);
    defineFunctionObject("YIELD-SUBTYPE-OF?-CASE-TEST", "(DEFUN (YIELD-SUBTYPE-OF?-CASE-TEST CONS) ((CASEKEY TYPE) (TESTEXPRESSION OBJECT)))", ((cpp_function_code)(&yieldSubtypeOfPCaseTest)), NULL);
    defineFunctionObject("YIELD-COND-TEST", "(DEFUN (YIELD-COND-TEST CONS) ((CASETEST OBJECT) (TESTVARIABLE OBJECT) (EQUALITYTEST SYMBOL)))", ((cpp_function_code)(&yieldCondTest)), NULL);
    defineFunctionObject("YIELD-COND-TEST-OR-TESTS", "(DEFUN (YIELD-COND-TEST-OR-TESTS OBJECT) ((CASETEST OBJECT) (TESTVARIABLE OBJECT) (EQUALITYTEST SYMBOL)))", ((cpp_function_code)(&yieldCondTestOrTests)), NULL);
    defineFunctionObject("COUNT-CASE-TEST-CLAUSES", "(DEFUN (COUNT-CASE-TEST-CLAUSES INTEGER BOOLEAN) ((TREE CONS)))", ((cpp_function_code)(&countCaseTestClauses)), NULL);
    defineFunctionObject("ATTACH-UNHANDLED-CASE-ERROR-CLAUSE", "(DEFUN (ATTACH-UNHANDLED-CASE-ERROR-CLAUSE CONS) ((CASETREE CONS) (TESTTREE OBJECT)))", ((cpp_function_code)(&attachUnhandledCaseErrorClause)), NULL);
    defineFunctionObject("WALK-NON-BUILT-IN-CASE-TREE", "(DEFUN (WALK-NON-BUILT-IN-CASE-TREE CONS TYPE-SPEC) ((TREE CONS) (EQUALITYTEST SYMBOL)))", ((cpp_function_code)(&walkNonBuiltInCaseTree)), NULL);
    defineFunctionObject("WALK-CASE-TREE", "(DEFUN (WALK-CASE-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkCaseTree)), NULL);
    defineFunctionObject("WALK-TYPECASE-TREE", "(DEFUN (WALK-TYPECASE-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkTypecaseTree)), NULL);
    defineFunctionObject("YIELD-CASTED-TYPECASE-CLAUSE-TREES", "(DEFUN (YIELD-CASTED-TYPECASE-CLAUSE-TREES CONS) ((TESTVARIABLE SYMBOL) (CLAUSETYPE TYPE-SPEC) (CLAUSETREES CONS)))", ((cpp_function_code)(&yieldCastedTypecaseClauseTrees)), NULL);
    defineFunctionObject("VERIFY-TYPECASE-CLAUSE-TYPE", "(DEFUN VERIFY-TYPECASE-CLAUSE-TYPE ((TESTTYPE TYPE) (CLAUSETYPE TYPE) (PRECEDINGCLAUSETYPES (LIST OF TYPE)) (CLAUSE CONS)))", ((cpp_function_code)(&verifyTypecaseClauseType)), NULL);
    defineFunctionObject("WALK-WITH-PROCESS-LOCK-TREE", "(DEFUN (WALK-WITH-PROCESS-LOCK-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkWithProcessLockTree)), NULL);
    defineFunctionObject("FINISH-WALKING-EQL-TREE", "(DEFUN (FINISH-WALKING-EQL-TREE CONS TYPE-SPEC) ((TREE CONS) (TYPE1 TYPE) (TYPE2 TYPE)))", ((cpp_function_code)(&finishWalkingEqlTree)), NULL);
    defineFunctionObject("FINISH-WALKING-EQUAL-TREE", "(DEFUN (FINISH-WALKING-EQUAL-TREE CONS TYPE-SPEC) ((TREE CONS) (TYPE1 TYPE) (TYPE2 TYPE)))", ((cpp_function_code)(&finishWalkingEqualTree)), NULL);
    defineFunctionObject("WALK-EQUALITY-TREE", "(DEFUN (WALK-EQUALITY-TREE OBJECT TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkEqualityTree)), NULL);
    defineFunctionObject("MORE-GENERAL-NUMERIC-TYPE", "(DEFUN (MORE-GENERAL-NUMERIC-TYPE TYPE) ((TYPE1 TYPE) (TYPE2 TYPE)))", ((cpp_function_code)(&moreGeneralNumericType)), NULL);
    defineFunctionObject("YIELD-ARITHMETIC-OPERATOR-CALL-TREE", "(DEFUN (YIELD-ARITHMETIC-OPERATOR-CALL-TREE CONS) ((OPERATOR SYMBOL) (OPERANDS CONS)))", ((cpp_function_code)(&yieldArithmeticOperatorCallTree)), NULL);
    defineFunctionObject("YIELD-NESTED-ARITHMETIC-OPERATOR-CALL-TREE", "(DEFUN (YIELD-NESTED-ARITHMETIC-OPERATOR-CALL-TREE CONS) ((OPERATOR SYMBOL) (OPERANDS CONS)))", ((cpp_function_code)(&yieldNestedArithmeticOperatorCallTree)), NULL);
    defineFunctionObject("WALK-ARITHMETIC-TREE", "(DEFUN (WALK-ARITHMETIC-TREE OBJECT TYPE) ((TREE CONS)))", ((cpp_function_code)(&walkArithmeticTree)), NULL);
    defineFunctionObject("WALK-QUOTED-TREE", "(DEFUN (WALK-QUOTED-TREE OBJECT TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkQuotedTree)), NULL);
    defineFunctionObject("WALK-BQUOTE-TREE", "(DEFUN (WALK-BQUOTE-TREE OBJECT TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkBquoteTree)), NULL);
    defineFunctionObject("EXPAND-MACRO", "(DEFUN (EXPAND-MACRO OBJECT) ((TREE CONS)))", ((cpp_function_code)(&expandMacro)), NULL);
    defineFunctionObject("WALK-MACRO-TREE", "(DEFUN (WALK-MACRO-TREE OBJECT TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkMacroTree)), NULL);
    defineFunctionObject("WALK-PRINT-STREAM-TREE", "(DEFUN (WALK-PRINT-STREAM-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkPrintStreamTree)), NULL);
    defineFunctionObject("WARN-ABOUT-UNDEFINED-METHODS?", "(DEFUN (WARN-ABOUT-UNDEFINED-METHODS? BOOLEAN) ())", ((cpp_function_code)(&warnAboutUndefinedMethodsP)), NULL);
    defineFunctionObject("WARN-ABOUT-MISSING-METHODS?", "(DEFUN (WARN-ABOUT-MISSING-METHODS? BOOLEAN) ())", ((cpp_function_code)(&warnAboutMissingMethodsP)), NULL);
    defineFunctionObject("WALK-TYPE-SPEC-IS-NATIVE-TYPE?", "(DEFUN (WALK-TYPE-SPEC-IS-NATIVE-TYPE? BOOLEAN) ((THETYPE TYPE-SPEC)))", ((cpp_function_code)(&walkTypeSpecIsNativeTypeP)), NULL);
    defineFunctionObject("WALK-UNDEFINED-SLOT-TREE", "(DEFUN (WALK-UNDEFINED-SLOT-TREE CONS TYPE) ((TREE CONS) (FIRSTARGTYPE TYPE-SPEC) (WARN? BOOLEAN)))", ((cpp_function_code)(&walkUndefinedSlotTree)), NULL);
    defineFunctionObject("WALK-SLOT-ON-ABSTRACT-TYPE-TREE", "(DEFUN (WALK-SLOT-ON-ABSTRACT-TYPE-TREE CONS TYPE-SPEC) ((TREE CONS) (ABSTRACTTYPE TYPE)))", ((cpp_function_code)(&walkSlotOnAbstractTypeTree)), NULL);
    defineFunctionObject("FIND-PROTOTYPE-METHOD", "(DEFUN (FIND-PROTOTYPE-METHOD METHOD-SLOT) ((METHODNAME SYMBOL) (ABSTRACTTYPE TYPE)))", ((cpp_function_code)(&findPrototypeMethod)), NULL);
    defineFunctionObject("COMPATIBLE-REAL-METHODS", "(DEFUN (COMPATIBLE-REAL-METHODS INTEGER INTEGER BOOLEAN) ((PROTOTYPEMETHOD METHOD-SLOT) (ABSTRACTTYPE TYPE)))", ((cpp_function_code)(&compatibleRealMethods)), NULL);
    defineMethodObject("(DEFMETHOD (FINISH-WALKING-CALL-SLOT-TREE OBJECT TYPE-SPEC) ((SELF SLOT) (TREE CONS) (FIRSTARGTYPE TYPE-SPEC)))", wrapMethodCode(((cpp_method_code)(&Slot::finishWalkingCallSlotTree))), NULL);
    defineMethodObject("(DEFMETHOD (FINISH-WALKING-CALL-SLOT-TREE OBJECT TYPE-SPEC) ((SELF STORAGE-SLOT) (TREE CONS) (FIRSTARGTYPE TYPE-SPEC)))", wrapMethodCode(((cpp_method_code)(&StorageSlot::finishWalkingCallSlotTree))), NULL);
    defineFunctionObject("STRING-CONCATENATE-METHOD?", "(DEFUN (STRING-CONCATENATE-METHOD? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(((boolean  (*) (MethodSlot*))(&stringConcatenateMethodP)))), NULL);
    defineFunctionObject("PASS-VARIABLE-ARGUMENTS-AS-LIST?", "(DEFUN (PASS-VARIABLE-ARGUMENTS-AS-LIST? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&passVariableArgumentsAsListP)), NULL);
    defineFunctionObject("VARIABLE-ARGUMENTS-TYPE", "(DEFUN (VARIABLE-ARGUMENTS-TYPE TYPE-SPEC) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&variableArgumentsType)), NULL);
  }
}

void helpStartupWalk14() {
  {
    defineFunctionObject("VARIABLE-ARGUMENTS-NAME", "(DEFUN (VARIABLE-ARGUMENTS-NAME SYMBOL) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&variableArgumentsName)), NULL);
    defineFunctionObject("YIELD-LISTIFIED-VARIABLE-ARGUMENTS-TYPE", "(DEFUN (YIELD-LISTIFIED-VARIABLE-ARGUMENTS-TYPE TYPE-SPEC) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&yieldListifiedVariableArgumentsType)), NULL);
    defineFunctionObject("YIELD-LISTIFIED-VARIABLE-ARGUMENTS", "(DEFUN (YIELD-LISTIFIED-VARIABLE-ARGUMENTS CONS) ((WALKEDARGS CONS) (TARGETTYPE TYPE-SPEC) (WRAPARGS? BOOLEAN)))", ((cpp_function_code)(&yieldListifiedVariableArguments)), NULL);
    defineFunctionObject("FINISH-WALKING-ARGUMENT-LIST-TREE", "(DEFUN (FINISH-WALKING-ARGUMENT-LIST-TREE OBJECT TYPE-SPEC) ((SELF SLOT) (TREE CONS) (FIRSTARGTYPE TYPE-SPEC)))", ((cpp_function_code)(&finishWalkingArgumentListTree)), NULL);
    defineFunctionObject("WALK-VARIABLE-ARGUMENTS", "(DEFUN (WALK-VARIABLE-ARGUMENTS CONS) ((ARGUMENTS CONS) (METHOD METHOD-SLOT) (FIRSTARGTYPE TYPE-SPEC)))", ((cpp_function_code)(&walkVariableArguments)), NULL);
    defineMethodObject("(DEFMETHOD (FINISH-WALKING-CALL-SLOT-TREE OBJECT TYPE-SPEC) ((SELF METHOD-SLOT) (TREE CONS) (FIRSTARGTYPE TYPE-SPEC)))", wrapMethodCode(((cpp_method_code)(&MethodSlot::finishWalkingCallSlotTree))), NULL);
    defineFunctionObject("QUOTE-ARGUMENTS", "(DEFUN (QUOTE-ARGUMENTS CONS) ((METHOD METHOD-SLOT) (ARGUMENTS CONS)))", ((cpp_function_code)(&quoteArguments)), NULL);
    defineFunctionObject("WALK-FIRST-ARGUMENT-TO-FUNCTION", "(DEFUN (WALK-FIRST-ARGUMENT-TO-FUNCTION TYPE-SPEC) ((FNSLOT METHOD-SLOT) (TREE CONS)))", ((cpp_function_code)(&walkFirstArgumentToFunction)), NULL);
    defineFunctionObject("WALK-CALL-SLOT-TREE", "(DEFUN (WALK-CALL-SLOT-TREE OBJECT TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkCallSlotTree)), NULL);
    defineFunctionObject("INLINE-METHOD-CALL?", "(DEFUN (INLINE-METHOD-CALL? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&inlineMethodCallP)), NULL);
    defineFunctionObject("METHOD-INLINABLE?", "(DEFUN (METHOD-INLINABLE? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&methodInlinableP)), NULL);
    defineFunctionObject("MOST-SPECIFIC-METHOD?", "(DEFUN (MOST-SPECIFIC-METHOD? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&mostSpecificMethodP)), NULL);
    defineFunctionObject("HELP-MOST-SPECIFIC-METHOD?", "(DEFUN (HELP-MOST-SPECIFIC-METHOD? BOOLEAN) ((CLASS CLASS) (METHOD METHOD-SLOT)))", ((cpp_function_code)(&helpMostSpecificMethodP)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT METHOD-SLOT CACHED-INLINABLE-METHOD-BODY :TYPE OBJECT :ALLOCATION :DYNAMIC)");
    defineFunctionObject("INLINABLE-METHOD-BODY", "(DEFUN (INLINABLE-METHOD-BODY OBJECT) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&inlinableMethodBody)), NULL);
    defineFunctionObject("WALK-INLINE-METHOD-CALL", "(DEFUN (WALK-INLINE-METHOD-CALL OBJECT) ((METHOD METHOD-SLOT) (WALKEDARGS CONS) (FIRSTARGTYPE TYPE-SPEC)))", ((cpp_function_code)(&walkInlineMethodCall)), NULL);
    defineFunctionObject("YIELD-VERBATIM-INLINE-CALL-TREE", "(DEFUN (YIELD-VERBATIM-INLINE-CALL-TREE CONS) ((METHOD METHOD-SLOT) (WALKEDARGS CONS)))", ((cpp_function_code)(&yieldVerbatimInlineCallTree)), NULL);
    defineFunctionObject("INLINE-VARIABLE-REFERENCE?", "(DEFUN (INLINE-VARIABLE-REFERENCE? BOOLEAN) ((SELF SYMBOL)) :GLOBALLY-INLINE? TRUE (RETURN (AND *INLININGMETHODCALL?* (DEFINED? (GET-LOCAL-VARIABLE-INFO SELF :INLINE-ARGUMENT)))))", ((cpp_function_code)(&inlineVariableReferenceP)), NULL);
    defineFunctionObject("WALK-INLINE-VARIABLE-REFERENCE", "(DEFUN (WALK-INLINE-VARIABLE-REFERENCE CONS TYPE-SPEC) ((SELF SYMBOL)))", ((cpp_function_code)(&walkInlineVariableReference)), NULL);
    defineFunctionObject("SIDE-EFFECT-FREE-EXPRESSION?", "(DEFUN (SIDE-EFFECT-FREE-EXPRESSION? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&sideEffectFreeExpressionP)), NULL);
    defineFunctionObject("ESTIMATED-EVALUATION-COST", "(DEFUN (ESTIMATED-EVALUATION-COST INTEGER) ((TREE OBJECT)))", ((cpp_function_code)(&estimatedEvaluationCost)), NULL);
    defineFunctionObject("YIELD-SYNTHESIZED-METHOD-BODY", "(DEFUN (YIELD-SYNTHESIZED-METHOD-BODY CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&yieldSynthesizedMethodBody)), NULL);
    defineFunctionObject("WALK-METHOD-OBJECT", "(DEFUN (WALK-METHOD-OBJECT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&walkMethodObject)), NULL);
    defineFunctionObject("WALK-DEFMETHOD-TREE", "(DEFUN WALK-DEFMETHOD-TREE ((TREE CONS)))", ((cpp_function_code)(&walkDefmethodTree)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT METHOD-SLOT FORWARD-DECLARATION? :TYPE BOOLEAN :DEFAULT FALSE :DOCUMENTATION \"Set to `true' for walked methods without a body.\nUsed to flag functions and methods that were declared but not defined.\" :ALLOCATION :DYNAMIC)");
    defineFunctionObject("METHOD-STORES-NATIVE-CODE-POINTER?", "(DEFUN (METHOD-STORES-NATIVE-CODE-POINTER? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&methodStoresNativeCodePointerP)), NULL);
    defineFunctionObject("WALK-METHOD-UNIT", "(DEFUN WALK-METHOD-UNIT ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&walkMethodUnit)), NULL);
    defineFunctionObject("PRINT-UNDEFINED-METHODS", "(DEFUN PRINT-UNDEFINED-METHODS ((MODULE MODULE) (LOCAL? BOOLEAN)) :PUBLIC? TRUE :DOCUMENTATION \"Print all declared but not yet defined functions and methods\nin `module'.  If `local?' is true, do not consider any parent modules of\n`module'.  If `module' is NULL, look at all modules in the system.  This\nis handy to pinpoint forward declarations that haven't been followed up\nby actual definitions.\")", ((cpp_function_code)(&printUndefinedMethods)), NULL);
    defineFunctionObject("WALK-SYS-CALL-TREE", "(DEFUN (WALK-SYS-CALL-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkSysCallTree)), NULL);
    defineFunctionObject("WALK-DEFCLASS-TREE", "(DEFUN WALK-DEFCLASS-TREE ((TREE CONS)))", ((cpp_function_code)(&walkDefclassTree)), NULL);
    defineFunctionObject("YIELD-INITIALIZE-HARDWIRED-SLOTS", "(DEFUN (YIELD-INITIALIZE-HARDWIRED-SLOTS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldInitializeHardwiredSlots)), NULL);
    defineFunctionObject("YIELD-INITIAL-VALUE-EXPRESSION", "(DEFUN (YIELD-INITIAL-VALUE-EXPRESSION OBJECT) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&yieldInitialValueExpression)), NULL);
    defineFunctionObject("YIELD-CONSTRUCTOR-ATTACHMENT", "(DEFUN (YIELD-CONSTRUCTOR-ATTACHMENT CONS) ((CLASS CLASS) (CLASSREF SYMBOL)))", ((cpp_function_code)(&yieldConstructorAttachment)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT CLASS CLASS-AUXILIARY-METHODS :TYPE (LIST OF METHOD-SLOT) :DEFAULT NIL-LIST :DOCUMENTATION \"Stores auxiliary method objects such as slot accessors and\ninherited mixin methods that are not attached to the class as regular methods\nbut need to be accessible by the C++ translator in order to generate the\nnecessary signatures.\" :ALLOCATION :DYNAMIC)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT METHOD-SLOT AUXILIARY-METHOD-REASON :TYPE SLOT :ALLOCATION :DYNAMIC)");
    defineFunctionObject("CLEANUP-AUXILIARY-METHODS", "(DEFUN CLEANUP-AUXILIARY-METHODS ((CLASS CLASS)))", ((cpp_function_code)(&cleanupAuxiliaryMethods)), NULL);
    defineFunctionObject("REGISTER-AUXILIARY-METHOD", "(DEFUN REGISTER-AUXILIARY-METHOD ((METHOD METHOD-SLOT) (REASON SLOT)))", ((cpp_function_code)(&registerAuxiliaryMethod)), NULL);
    defineFunctionObject("MIXIN-TYPE-VARIABLES-ALLOWED?", "(DEFUN (MIXIN-TYPE-VARIABLES-ALLOWED? BOOLEAN) () :GLOBALLY-INLINE? TRUE (RETURN (OR (NOT (TRANSLATE-TO-SINGLE-INHERITANCE-LANGUAGE?)) (NOT (EQL? *MIXIN-IMPLEMENTATION-STYLE* :SECOND-CLASS)))))", ((cpp_function_code)(&mixinTypeVariablesAllowedP)), NULL);
    defineFunctionObject("CREATE-NATIVE-MIXIN-SLOT-ACCESSORS?", "(DEFUN (CREATE-NATIVE-MIXIN-SLOT-ACCESSORS? BOOLEAN) () :GLOBALLY-INLINE? TRUE (RETURN (AND (TRANSLATE-TO-SINGLE-INHERITANCE-LANGUAGE?) (MIXIN-TYPE-VARIABLES-ALLOWED?))))", ((cpp_function_code)(&createNativeMixinSlotAccessorsP)), NULL);
    defineFunctionObject("CREATE-ACCESSOR-UNITS-FOR-SLOT", "(DEFUN CREATE-ACCESSOR-UNITS-FOR-SLOT ((SLOT STORAGE-SLOT) (CLASS CLASS) (MIXINACCESSORS? BOOLEAN) (SIGNATURESONLY? BOOLEAN)))", ((cpp_function_code)(&createAccessorUnitsForSlot)), NULL);
    defineFunctionObject("CREATE-ACCESSOR-UNITS-FOR-MIXIN-SLOT", "(DEFUN CREATE-ACCESSOR-UNITS-FOR-MIXIN-SLOT ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&createAccessorUnitsForMixinSlot)), NULL);
    defineFunctionObject("CREATE-SLOT-ACCESSOR-UNITS", "(DEFUN CREATE-SLOT-ACCESSOR-UNITS ((CLASS CLASS)))", ((cpp_function_code)(&createSlotAccessorUnits)), NULL);
    defineFunctionObject("CREATE-INLINE-METHOD-UNITS", "(DEFUN CREATE-INLINE-METHOD-UNITS ((CLASS CLASS)))", ((cpp_function_code)(&createInlineMethodUnits)), NULL);
    defineFunctionObject("YIELD-MIXIN-METHOD-TREE", "(DEFUN (YIELD-MIXIN-METHOD-TREE CONS) ((METHOD METHOD-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&yieldMixinMethodTree)), NULL);
    defineFunctionObject("CREATE-MIXIN-METHOD-UNITS", "(DEFUN CREATE-MIXIN-METHOD-UNITS ((CLASS CLASS)))", ((cpp_function_code)(&createMixinMethodUnits)), NULL);
    defineFunctionObject("CREATE-DEFPRINT-UNIT", "(DEFUN CREATE-DEFPRINT-UNIT ((CLASS CLASS)))", ((cpp_function_code)(&createDefprintUnit)), NULL);
    defineFunctionObject("WALK-CLASS-UNIT", "(DEFUN WALK-CLASS-UNIT ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&walkClassUnit)), NULL);
    defineFunctionObject("CREATE-FINALIZATION-UNITS", "(DEFUN CREATE-FINALIZATION-UNITS ())", ((cpp_function_code)(&createFinalizationUnits)), NULL);
    defineFunctionObject("WALK-DEFSLOT-TREE", "(DEFUN WALK-DEFSLOT-TREE ((TREE CONS)))", ((cpp_function_code)(&walkDefslotTree)), NULL);
    defineFunctionObject("WALK-SLOT-UNIT", "(DEFUN WALK-SLOT-UNIT ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&walkSlotUnit)), NULL);
    defineFunctionObject("LOOKUP-MACRO", "(DEFUN (LOOKUP-MACRO METHOD-SLOT) ((NAME SYMBOL)) :DOCUMENTATION \"If `name' has a macro definition, return the method object\nholding its expander function.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupMacro)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT METHOD-SLOT METHOD-MACRO? :TYPE BOOLEAN :OPTION-KEYWORD :MACRO? :DOCUMENTATION \"If true, the object is a macro expander function.\" :ALLOCATION :DYNAMIC)");
    defineFunctionObject("WALK-DEFMACRO-TREE", "(DEFUN WALK-DEFMACRO-TREE ((TREE CONS)))", ((cpp_function_code)(&walkDefmacroTree)), NULL);
    defineFunctionObject("WALK-DEFGLOBAL-TREE", "(DEFUN WALK-DEFGLOBAL-TREE ((TREE CONS)))", ((cpp_function_code)(&walkDefglobalTree)), NULL);
    defineFunctionObject("WALK-GLOBAL-UNIT", "(DEFUN WALK-GLOBAL-UNIT ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&walkGlobalUnit)), NULL);
    defineFunctionObject("WALK-DEFTYPE-TREE", "(DEFUN WALK-DEFTYPE-TREE ((TREE CONS)))", ((cpp_function_code)(&walkDeftypeTree)), NULL);
    defineFunctionObject("WALK-TYPE-UNIT", "(DEFUN WALK-TYPE-UNIT ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&walkTypeUnit)), NULL);
    defineFunctionObject("WALK-STARTUP-TIME-PROGN-TREE", "(DEFUN WALK-STARTUP-TIME-PROGN-TREE ((TREE CONS)))", ((cpp_function_code)(&walkStartupTimePrognTree)), NULL);
    defineFunctionObject("EXTRACT-STARTUP-TIME-PHASE", "(DEFUN (EXTRACT-STARTUP-TIME-PHASE KEYWORD) ((TREE CONS)))", ((cpp_function_code)(&extractStartupTimePhase)), NULL);
    defineFunctionObject("WALK-STARTUP-TIME-PROGN-UNIT", "(DEFUN WALK-STARTUP-TIME-PROGN-UNIT ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&walkStartupTimePrognUnit)), NULL);
  }
}

void helpStartupWalk15() {
  {
    defineFunctionObject("EARLIER-STARTUP-UNIT?", "(DEFUN (EARLIER-STARTUP-UNIT? BOOLEAN) ((UNIT1 TRANSLATION-UNIT) (UNIT2 TRANSLATION-UNIT)))", ((cpp_function_code)(&earlierStartupUnitP)), NULL);
    defineFunctionObject("COMBINE-STARTUP-FUNCTION-UNITS", "(DEFUN (COMBINE-STARTUP-FUNCTION-UNITS CONS) ((STARTUPFNNAME SYMBOL)))", ((cpp_function_code)(&combineStartupFunctionUnits)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT METHOD-SLOT METHOD-STARTUP-CLASSNAME :TYPE STRING :ALLOCATION :DYNAMIC)");
    defineMethodObject("(DEFMETHOD (METHOD-STARTUP-FUNCTION? BOOLEAN) ((METHOD METHOD-SLOT)))", wrapMethodCode(((cpp_method_code)(&MethodSlot::methodStartupFunctionP))), NULL);
    defineFunctionObject("EXTRACT-STARTUP-FUNCTION-UNITS", "(DEFUN EXTRACT-STARTUP-FUNCTION-UNITS ((STARTUPUNITS (LIST OF TRANSLATION-UNIT)) (STARTUPFNNAME SYMBOL)))", ((cpp_function_code)(&extractStartupFunctionUnits)), NULL);
    defineFunctionObject("YIELD-STARTUP-FUNCTION-NAME", "(DEFUN (YIELD-STARTUP-FUNCTION-NAME SYMBOL) ((FILE STRING)))", ((cpp_function_code)(&yieldStartupFunctionName)), NULL);
    defineFunctionObject("YIELD-STARTUP-FUNCTION-CLASSNAME", "(DEFUN (YIELD-STARTUP-FUNCTION-CLASSNAME STRING) ((FUNCTION-NAME SYMBOL)))", ((cpp_function_code)(&yieldStartupFunctionClassname)), NULL);
    defineFunctionObject("CREATE-STARTUP-FUNCTION-UNITS", "(DEFUN CREATE-STARTUP-FUNCTION-UNITS ())", ((cpp_function_code)(&createStartupFunctionUnits)), NULL);
    defineFunctionObject("DONT-GENERATE-STARTUP-CODE?", "(DEFUN (DONT-GENERATE-STARTUP-CODE? BOOLEAN) ())", ((cpp_function_code)(&dontGenerateStartupCodeP)), NULL);
    defineFunctionObject("REMOVE-ALL-STARTUP-TIME-PROGN-UNITS", "(DEFUN REMOVE-ALL-STARTUP-TIME-PROGN-UNITS ())", ((cpp_function_code)(&removeAllStartupTimePrognUnits)), NULL);
    defineFunctionObject("WALK-SIGNAL-EXCEPTION-TREE", "(DEFUN (WALK-SIGNAL-EXCEPTION-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkSignalExceptionTree)), NULL);
    defineFunctionObject("WALK-EXCEPTION-CASE-TREE", "(DEFUN (WALK-EXCEPTION-CASE-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkExceptionCaseTree)), NULL);
    defineFunctionObject("WALK-EXCEPTION-HANDLER-TREES", "(DEFUN (WALK-EXCEPTION-HANDLER-TREES CONS) ((TREE CONS)))", ((cpp_function_code)(&walkExceptionHandlerTrees)), NULL);
    defineFunctionObject("WALK-UNWIND-PROTECT-TREE", "(DEFUN (WALK-UNWIND-PROTECT-TREE CONS TYPE) ((TREE CONS)))", ((cpp_function_code)(&walkUnwindProtectTree)), NULL);
    defineFunctionObject("WALK-VERBATIM-DEFINITION-TREE", "(DEFUN WALK-VERBATIM-DEFINITION-TREE ((TREE CONS)))", ((cpp_function_code)(&walkVerbatimDefinitionTree)), NULL);
    defineFunctionObject("WALK-VERBATIM-UNIT", "(DEFUN WALK-VERBATIM-UNIT ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&walkVerbatimUnit)), NULL);
    defineFunctionObject("WALK-VERBATIM-TREE", "(DEFUN (WALK-VERBATIM-TREE OBJECT TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkVerbatimTree)), NULL);
    defineFunctionObject("LOOKUP-VERBATIM-TREE", "(DEFUN (LOOKUP-VERBATIM-TREE OBJECT) ((TREE CONS) (LANGUAGE KEYWORD)))", ((cpp_function_code)(&lookupVerbatimTree)), NULL);
    defineFunctionObject("VERBATIM-TREE?", "(DEFUN (VERBATIM-TREE? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&verbatimTreeP)), NULL);
    defineFunctionObject("WALK-DEFMODULE-TREE", "(DEFUN WALK-DEFMODULE-TREE ((TREE CONS)))", ((cpp_function_code)(&walkDefmoduleTree)), NULL);
    defineFunctionObject("WALK-MODULE-UNIT", "(DEFUN WALK-MODULE-UNIT ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&walkModuleUnit)), NULL);
    defineFunctionObject("EXTRACT-REQUIRED-ARGUMENT-VALUES", "(DEFUN (EXTRACT-REQUIRED-ARGUMENT-VALUES CONS) ((CLASSTYPE TYPE-SPEC) (SLOTSANDVALUES (PROPERTY-LIST OF SLOT OBJECT))))", ((cpp_function_code)(&extractRequiredArgumentValues)), NULL);
    defineFunctionObject("PREPROCESS-ARRAY-ARGUMENTS", "(DEFUN PREPROCESS-ARRAY-ARGUMENTS ((ARRAYTYPE PARAMETRIC-TYPE-SPECIFIER) (SLOTSANDVALUES (PROPERTY-LIST OF SLOT OBJECT))))", ((cpp_function_code)(&preprocessArrayArguments)), NULL);
    defineFunctionObject("EVALUATE-ARRAY-ARGUMENT-VALUE", "(DEFUN EVALUATE-ARRAY-ARGUMENT-VALUE ((ARRAYTYPE PARAMETRIC-TYPE-SPECIFIER) (REQUIREDVALUES LIST) (SLOT SLOT) (VALUEREF OBJECT)))", ((cpp_function_code)(&evaluateArrayArgumentValue)), NULL);
    defineFunctionObject("YIELD-NEW-ARGUMENTS-TREE", "(DEFUN (YIELD-NEW-ARGUMENTS-TREE CONS CONS) ((KEYWORDSANDVALUES CONS) (CLASSTYPE TYPE-SPEC) (SELFVARIABLE SYMBOL)))", ((cpp_function_code)(&yieldNewArgumentsTree)), NULL);
    defineFunctionObject("GET-CURRENT-SELF-TYPE", "(DEFUN (GET-CURRENT-SELF-TYPE TYPE) ())", ((cpp_function_code)(&getCurrentSelfType)), NULL);
    defineFunctionObject("WALK-NEW-TREE", "(DEFUN (WALK-NEW-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkNewTree)), NULL);
    defineFunctionObject("WALK-MAKE-TREE", "(DEFUN (WALK-MAKE-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkMakeTree)), NULL);
    defineFunctionObject("WALK-FUNCALL-TREE", "(DEFUN (WALK-FUNCALL-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkFuncallTree)), NULL);
    defineFunctionObject("WALK-THE-CODE-TREE", "(DEFUN (WALK-THE-CODE-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkTheCodeTree)), NULL);
    defineFunctionObject("WALK-CALL-SUPER-METHOD-TREE", "(DEFUN (WALK-CALL-SUPER-METHOD-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkCallSuperMethodTree)), NULL);
    defineFunctionObject("DE-UGLIFY-ARGUMENTS", "(DEFUN (DE-UGLIFY-ARGUMENTS CONS) ((UGLYARGUMENTS CONS)))", ((cpp_function_code)(&deUglifyArguments)), NULL);
    defineFunctionObject("DE-UGLIFY-PARSE-TREE", "(DEFUN (DE-UGLIFY-PARSE-TREE OBJECT) ((TREE OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&deUglifyParseTree)), NULL);
    defineFunctionObject("REGISTER-NATIVE-NAME", "(DEFUN REGISTER-NATIVE-NAME ((NAME SYMBOL) (LANGUAGE KEYWORD) (CATEGORY KEYWORD)))", ((cpp_function_code)(&registerNativeName)), NULL);
    defineFunctionObject("NATIVE-NAME?", "(DEFUN (NATIVE-NAME? BOOLEAN) ((NAME SYMBOL) (LANGUAGE KEYWORD) (CATEGORY KEYWORD)))", ((cpp_function_code)(&nativeNameP)), NULL);
    defineFunctionObject("YIELD-RENAMED-NAME-IF-NATIVE", "(DEFUN (YIELD-RENAMED-NAME-IF-NATIVE SYMBOL) ((NAME SYMBOL) (LANGUAGE KEYWORD) (CATEGORY KEYWORD)))", ((cpp_function_code)(&yieldRenamedNameIfNative)), NULL);
    defineFunctionObject("METHOD-NEEDS-LISP-MACRO?", "(DEFUN (METHOD-NEEDS-LISP-MACRO? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&methodNeedsLispMacroP)), NULL);
    defineFunctionObject("YIELD-LISP-MACRO-TREES", "(DEFUN (YIELD-LISP-MACRO-TREES CONS CONS) ((NAME SYMBOL) (METHOD METHOD-SLOT)))", ((cpp_function_code)(&yieldLispMacroTrees)), NULL);
    defineFunctionObject("CREATE-LISP-MACRO-UNITS", "(DEFUN CREATE-LISP-MACRO-UNITS ((NAME SYMBOL) (METHOD METHOD-SLOT)))", ((cpp_function_code)(&createLispMacroUnits)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT METHOD-SLOT METHOD-C-NAMESPACE-PREFIX :TYPE STRING :OPTION-KEYWORD :C-NAMESPACE-PREFIX :DOCUMENTATION \"The package prefix to use for the C-callable function (defaults to C++ namespace).\" :ALLOCATION :DYNAMIC)");
    defineFunctionObject("METHOD-NEEDS-C-CALLABLE-WRAPPER?", "(DEFUN (METHOD-NEEDS-C-CALLABLE-WRAPPER? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&methodNeedsCCallableWrapperP)), NULL);
    defineFunctionObject("YIELD-C-CALLABLE-WRAPPER-NAME", "(DEFUN (YIELD-C-CALLABLE-WRAPPER-NAME SYMBOL) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&yieldCCallableWrapperName)), NULL);
    defineFunctionObject("YIELD-C-CALLABLE-WRAPPER-TREE", "(DEFUN (YIELD-C-CALLABLE-WRAPPER-TREE CONS) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&yieldCCallableWrapperTree)), NULL);
    defineFunctionObject("CREATE-C-CALLABLE-WRAPPER-UNIT", "(DEFUN (CREATE-C-CALLABLE-WRAPPER-UNIT METHOD-SLOT) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&createCCallableWrapperUnit)), NULL);
    defineFunctionObject("C-CALLABLE-WRAPPER-METHOD?", "(DEFUN (C-CALLABLE-WRAPPER-METHOD? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&cCallableWrapperMethodP)), NULL);
    defineFunctionObject("YIELD-FUNCTION-CPP-SIGNATURE", "(DEFUN (YIELD-FUNCTION-CPP-SIGNATURE (CONS OF (CONS OF STRING-WRAPPER))) ((FUNCTION METHOD-SLOT) (FIRSTARGTYPE TYPE-SPEC) (QUALIFY? BOOLEAN)))", ((cpp_function_code)(&yieldFunctionCppSignature)), NULL);
    defineFunctionObject("CPP-TYPE-TO-C-TYPE", "(DEFUN (CPP-TYPE-TO-C-TYPE STRING) ((TYPE STRING)))", ((cpp_function_code)(&cppTypeToCType)), NULL);
    defineFunctionObject("YIELD-FUNCTION-C-SIGNATURE", "(DEFUN (YIELD-FUNCTION-C-SIGNATURE (CONS OF (CONS OF STRING-WRAPPER))) ((FUNCTION METHOD-SLOT) (FIRSTARGTYPE TYPE-SPEC)))", ((cpp_function_code)(&yieldFunctionCSignature)), NULL);
    defineFunctionObject("YIELD-METHOD-CPP-SIGNATURE", "(DEFUN (YIELD-METHOD-CPP-SIGNATURE (CONS OF (CONS OF STRING-WRAPPER))) ((METHOD METHOD-SLOT) (FIRSTARGTYPE TYPE-SPEC) (QUALIFY? BOOLEAN)))", ((cpp_function_code)(&yieldMethodCppSignature)), NULL);
    defineFunctionObject("YIELD-METHOD-C-SIGNATURE", "(DEFUN (YIELD-METHOD-C-SIGNATURE (CONS OF (CONS OF STRING-WRAPPER))) ((METHOD METHOD-SLOT) (FIRSTARGTYPE TYPE-SPEC)))", ((cpp_function_code)(&yieldMethodCSignature)), NULL);
    defineFunctionObject("YIELD-STORAGE-SLOT-CPP-SIGNATURE", "(DEFUN (YIELD-STORAGE-SLOT-CPP-SIGNATURE (CONS OF (CONS OF STRING-WRAPPER))) ((SLOT STORAGE-SLOT) (FIRSTARGTYPE TYPE-SPEC) (QUALIFY? BOOLEAN)))", ((cpp_function_code)(&yieldStorageSlotCppSignature)), NULL);
    defineFunctionObject("YIELD-STORAGE-SLOT-C-SIGNATURE", "(DEFUN (YIELD-STORAGE-SLOT-C-SIGNATURE (CONS OF (CONS OF STRING-WRAPPER))) ((SLOT STORAGE-SLOT) (FIRSTARGTYPE TYPE-SPEC)))", ((cpp_function_code)(&yieldStorageSlotCSignature)), NULL);
    defineFunctionObject("YIELD-GLOBAL-VARIABLE-CPP-SIGNATURE", "(DEFUN (YIELD-GLOBAL-VARIABLE-CPP-SIGNATURE (CONS OF (CONS OF STRING-WRAPPER))) ((GLOBAL GLOBAL-VARIABLE) (QUALIFY? BOOLEAN)))", ((cpp_function_code)(&yieldGlobalVariableCppSignature)), NULL);
    defineFunctionObject("YIELD-GLOBAL-VARIABLE-C-SIGNATURE", "(DEFUN (YIELD-GLOBAL-VARIABLE-C-SIGNATURE (CONS OF (CONS OF STRING-WRAPPER))) ((GLOBAL GLOBAL-VARIABLE)))", ((cpp_function_code)(&yieldGlobalVariableCSignature)), NULL);
    defineFunctionObject("LIST-SIGNATURE-TO-STRING", "(DEFUN (LIST-SIGNATURE-TO-STRING STRING) ((SIGNATURE (CONS OF (CONS OF STRING-WRAPPER)))))", ((cpp_function_code)(&listSignatureToString)), NULL);
    defineFunctionObject("LOOKUP-FUNCTION-CODE-BY-NAME", "(DEFUN (LOOKUP-FUNCTION-CODE-BY-NAME FUNCTION-CODE) ((QUALIFIEDNAME STRING)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&lookupFunctionCodeByName)), NULL);
    defineFunctionObject("LOOKUP-C-CALLABLE-WRAPPER-CODE-BY-NAME", "(DEFUN (LOOKUP-C-CALLABLE-WRAPPER-CODE-BY-NAME FUNCTION-CODE) ((QUALIFIEDNAME STRING)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&lookupCCallableWrapperCodeByName)), NULL);
    defineFunctionObject("LOOKUP-FUNCTION-CPP-SIGNATURE-BY-NAME", "(DEFUN (LOOKUP-FUNCTION-CPP-SIGNATURE-BY-NAME STRING) ((QUALIFIEDNAME STRING)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&lookupFunctionCppSignatureByName)), NULL);
    defineFunctionObject("LOOKUP-FUNCTION-C-SIGNATURE-BY-NAME", "(DEFUN (LOOKUP-FUNCTION-C-SIGNATURE-BY-NAME STRING) ((QUALIFIEDNAME STRING)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&lookupFunctionCSignatureByName)), NULL);
    defineFunctionObject("LOOKUP-METHOD-CODE-BY-NAME", "(DEFUN (LOOKUP-METHOD-CODE-BY-NAME CODE-WRAPPER) ((QUALIFIEDNAME STRING)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&lookupMethodCodeByName)), NULL);
  }
}

void helpStartupWalk16() {
  {
    defineFunctionObject("LOOKUP-METHOD-CPP-SIGNATURE-BY-NAME", "(DEFUN (LOOKUP-METHOD-CPP-SIGNATURE-BY-NAME STRING) ((QUALIFIEDNAME STRING)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&lookupMethodCppSignatureByName)), NULL);
    defineFunctionObject("LOOKUP-METHOD-C-SIGNATURE-BY-NAME", "(DEFUN (LOOKUP-METHOD-C-SIGNATURE-BY-NAME STRING) ((QUALIFIEDNAME STRING)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&lookupMethodCSignatureByName)), NULL);
    defineFunctionObject("LOOKUP-STORAGE-SLOT-CPP-SIGNATURE-BY-NAME", "(DEFUN (LOOKUP-STORAGE-SLOT-CPP-SIGNATURE-BY-NAME STRING) ((QUALIFIEDNAME STRING)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&lookupStorageSlotCppSignatureByName)), NULL);
    defineFunctionObject("LOOKUP-STORAGE-SLOT-C-SIGNATURE-BY-NAME", "(DEFUN (LOOKUP-STORAGE-SLOT-C-SIGNATURE-BY-NAME STRING) ((QUALIFIEDNAME STRING)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&lookupStorageSlotCSignatureByName)), NULL);
    defineFunctionObject("LOOKUP-CLASS-CPP-TYPE-BY-NAME", "(DEFUN (LOOKUP-CLASS-CPP-TYPE-BY-NAME STRING) ((QUALIFIEDNAME STRING)) :DOCUMENTATION \"Return a namespace-qualified C++ translation of the class type\nnamed by `qualifiedName' or NULL if no such STELLA class exists.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&lookupClassCppTypeByName)), NULL);
    defineFunctionObject("LOOKUP-GLOBAL-VARIABLE-CPP-SIGNATURE-BY-NAME", "(DEFUN (LOOKUP-GLOBAL-VARIABLE-CPP-SIGNATURE-BY-NAME STRING) ((QUALIFIEDNAME STRING)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&lookupGlobalVariableCppSignatureByName)), NULL);
    defineFunctionObject("LOOKUP-GLOBAL-VARIABLE-C-SIGNATURE-BY-NAME", "(DEFUN (LOOKUP-GLOBAL-VARIABLE-C-SIGNATURE-BY-NAME STRING) ((QUALIFIEDNAME STRING)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&lookupGlobalVariableCSignatureByName)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT METHOD-SLOT METHOD-THROWS-EXCEPTIONS? :TYPE BOOLEAN :OPTION-KEYWORD :THROWS-EXCEPTIONS? :DOCUMENTATION \"If TRUE, this function might throw exceptions which means we need to explicitly catch and handle them in C.\" :ALLOCATION :DYNAMIC)");
    defineFunctionObject("GET-GLOBAL-EXCEPTION-HANDLER", "(DEFUN (GET-GLOBAL-EXCEPTION-HANDLER FUNCTION-CODE) () :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getGlobalExceptionHandler)), NULL);
    defineFunctionObject("SET-GLOBAL-EXCEPTION-HANDLER", "(DEFUN SET-GLOBAL-EXCEPTION-HANDLER ((HANDLER FUNCTION-CODE)) :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&setGlobalExceptionHandler)), NULL);
    defineFunctionObject("CALL-GLOBAL-EXCEPTION-HANDLER", "(DEFUN CALL-GLOBAL-EXCEPTION-HANDLER ((E NATIVE-EXCEPTION)))", ((cpp_function_code)(&callGlobalExceptionHandler)), NULL);
    defineFunctionObject("GC-PROTECT-OBJECT", "(DEFUN (GC-PROTECT-OBJECT NATIVE-OBJECT-POINTER) ((OBJECT NATIVE-OBJECT-POINTER)) :DOCUMENTATION \"Protect `object' from garbage collection.  Returns a handle that can later\nbe passed to `gc-release-object' to release `object' from garbage collection protection.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&gcProtectObject)), NULL);
    defineFunctionObject("GC-RELEASE-OBJECT", "(DEFUN (GC-RELEASE-OBJECT NATIVE-OBJECT-POINTER) ((HANDLE NATIVE-OBJECT-POINTER)) :DOCUMENTATION \"Release the object pointed to by `handle' from garbage collection protection\nand return the protected object.  This frees `handle' but does not necessarily mean that the\nobject will be garbage collected, it just can be again, once all references to it disappear.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&gcReleaseObject)), NULL);
    defineFunctionObject("COMMAND?", "(DEFUN (COMMAND? BOOLEAN) ((METHOD METHOD-SLOT)) :DOCUMENTATION \"Return `true' if `method' is an evaluable command.\" :PUBLIC? TRUE)", ((cpp_function_code)(&commandP)), NULL);
    defineFunctionObject("LOOKUP-COMMAND", "(DEFUN (LOOKUP-COMMAND METHOD-SLOT) ((NAME SYMBOL)) :DOCUMENTATION \"If `name' names an evaluable command return its associated\ncommand object;  otherwise, return `null'.  Currently, commands are not\npolymorphic, i.e., they can only be implemented by functions.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupCommand)), NULL);
    defineFunctionObject("LOOKUP-COMMAND-LIKE-FUNCTION", "(DEFUN (LOOKUP-COMMAND-LIKE-FUNCTION METHOD-SLOT) ((NAME SYMBOL)) :DOCUMENTATION \"Look up a function with `name' that can be evaluated via `apply'\njust like a command, regardless of whether it was marked as such.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupCommandLikeFunction)), NULL);
    defineFunctionObject("METHOD-MUST-BE-EVALUABLE?", "(DEFUN (METHOD-MUST-BE-EVALUABLE? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&methodMustBeEvaluableP)), NULL);
    defineFunctionObject("METHOD-CALLABLE-VIA-APPLY?", "(DEFUN (METHOD-CALLABLE-VIA-APPLY? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&methodCallableViaApplyP)), NULL);
    defineFunctionObject("METHOD-NEEDS-EVALUATOR-WRAPPER?", "(DEFUN (METHOD-NEEDS-EVALUATOR-WRAPPER? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&methodNeedsEvaluatorWrapperP)), NULL);
    defineFunctionObject("YIELD-EVALUATOR-WRAPPER-NAME", "(DEFUN (YIELD-EVALUATOR-WRAPPER-NAME SYMBOL) ((METHODNAME SYMBOL)))", ((cpp_function_code)(&yieldEvaluatorWrapperName)), NULL);
    defineFunctionObject("YIELD-ARGUMENT-ACCESS-TREE", "(DEFUN (YIELD-ARGUMENT-ACCESS-TREE OBJECT) ((ARGUMENTSVARIABLE SYMBOL) (INDEX INTEGER) (RESTARGUMENT? BOOLEAN)))", ((cpp_function_code)(&yieldArgumentAccessTree)), NULL);
    defineFunctionObject("YIELD-EVALUATOR-WRAPPER-TREE", "(DEFUN (YIELD-EVALUATOR-WRAPPER-TREE CONS) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&yieldEvaluatorWrapperTree)), NULL);
    defineFunctionObject("CREATE-EVALUATOR-WRAPPER-UNIT", "(DEFUN (CREATE-EVALUATOR-WRAPPER-UNIT METHOD-SLOT) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&createEvaluatorWrapperUnit)), NULL);
    defineFunctionObject("EVALUATE", "(DEFUN (EVALUATE OBJECT) ((EXPRESSION OBJECT)) :DOCUMENTATION \"Evaluate the expression `expression' and return the result.\nCurrently, only the evaluation of (possibly nested) commands and global\nvariables is supported.  The second return value indicates the actual type \nof the result (which might have been wrapped), and the third return value\nindicates whether an error occurred during the evaluation.  Expressions\nare simple to program in Common Lisp, since they are built into the language,\nand relatively awkward in Java and C++.  Users of either of those \nlanguages are more likely to want to call `evaluate-string'.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&evaluate)), NULL);
    defineFunctionObject("EVALUATE-STRING", "(DEFUN (EVALUATE-STRING OBJECT) ((EXPRESSION STRING)) :DOCUMENTATION \"Evaluate the expression represented by `expression' and return the result.\nThis is equivalent to '(evaluate (unstringify expression))'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&evaluateString)), NULL);
    defineFunctionObject("TRY-TO-EVALUATE", "(DEFUN (TRY-TO-EVALUATE OBJECT) ((TREE OBJECT)) :DOCUMENTATION \"Variant of `evaluate' that only evaluates `tree' if it\nrepresents an evaluable expression.  If it does not, `tree' is returned\nunmodified.  This can be used to implement commands with mixed argument\nevaluation strategies.\" :PUBLIC? TRUE)", ((cpp_function_code)(&tryToEvaluate)), NULL);
    defineFunctionObject("EVALUATE-CONS-TREE", "(DEFUN (EVALUATE-CONS-TREE OBJECT TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&evaluateConsTree)), NULL);
    defineFunctionObject("EVALUATE-ARGUMENT-TREE", "(DEFUN (EVALUATE-ARGUMENT-TREE OBJECT TYPE-SPEC) ((TREE OBJECT) (EVALUATE? BOOLEAN)))", ((cpp_function_code)(&evaluateArgumentTree)), NULL);
    defineFunctionObject("EVALUATE-ATOMIC-TREE", "(DEFUN (EVALUATE-ATOMIC-TREE OBJECT TYPE-SPEC) ((TREE OBJECT)))", ((cpp_function_code)(&evaluateAtomicTree)), NULL);
    defineFunctionObject("MAKE-EVALUATABLE-BQUOTE-TREE", "(DEFUN (MAKE-EVALUATABLE-BQUOTE-TREE OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&makeEvaluatableBquoteTree)), NULL);
    defineFunctionObject("EVALUATE-BQUOTE-TREE", "(DEFUN (EVALUATE-BQUOTE-TREE OBJECT TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&evaluateBquoteTree)), NULL);
    defineFunctionObject("COERCE-EVALUATED-TREE", "(DEFUN (COERCE-EVALUATED-TREE OBJECT TYPE-SPEC) ((TREE OBJECT) (SOURCETREE OBJECT) (SOURCETYPE TYPE-SPEC) (TARGETTYPE TYPE-SPEC) (EVALUATE? BOOLEAN)))", ((cpp_function_code)(&coerceEvaluatedTree)), NULL);
    defineFunctionObject("STARTUP-WALK", "(DEFUN STARTUP-WALK () :PUBLIC? TRUE)", ((cpp_function_code)(&startupWalk)), NULL);
    { MethodSlot* function = lookupFunction(SYM_WALK_STELLA_STARTUP_WALK);

      setDynamicSlotValue(function->dynamicSlots, SYM_WALK_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupWalk"), NULL_STRING_WRAPPER);
    }
  }
}

void helpStartupWalk17() {
  {
    inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
    defineGlobalVariableObject("(DEFGLOBAL *AVAILABLE-STELLA-FEATURES* (LIST OF KEYWORD) (LIST :WARN-ABOUT-UNDEFINED-METHODS :WARN-ABOUT-MISSING-METHODS :SUPPRESS-WARNINGS :USE-HARDCODED-SYMBOLS :USE-COMMON-LISP-STRUCTS :USE-COMMON-LISP-CONSES :USE-CPP-GARBAGE-COLLECTOR :MINIMIZE-JAVA-PREFIXES :TRANSLATE-WITH-COPYRIGHT-HEADER :SUPPORT-UNEXEC) :DOCUMENTATION \"List of available STELLA features.\" :PUBLIC? TRUE)", &oAVAILABLE_STELLA_FEATURESo);
    defineGlobalVariableObject("(DEFSPECIAL *CURRENT-STELLA-FEATURES* (LIST OF KEYWORD) (LIST) :DOCUMENTATION \"List of currently enabled STELLA features.\" :PUBLIC? TRUE)", &oCURRENT_STELLA_FEATURESo);
    defineGlobalVariableObject("(DEFGLOBAL *DEFAULT-STELLA-FEATURES* (LIST OF KEYWORD) (LIST :WARN-ABOUT-UNDEFINED-METHODS :WARN-ABOUT-MISSING-METHODS :USE-CPP-GARBAGE-COLLECTOR :USE-COMMON-LISP-CONSES :MINIMIZE-JAVA-PREFIXES) :DOCUMENTATION \"List of STELLA features enabled by default and after resetting them\nwith `reset-stella-features'.\" :PUBLIC? TRUE)", &oDEFAULT_STELLA_FEATURESo);
    defineGlobalVariableObject("(DEFGLOBAL *TRACED-KEYWORDS* (LIST OF KEYWORD) NULL :PUBLIC? TRUE)", &oTRACED_KEYWORDSo);
    defineGlobalVariableObject("(DEFSPECIAL *SAFETY* INTEGER 3 :DOCUMENTATION \"Integer between 0 and 3.  Higher levels call more\nsafety checks.\")", &oSAFETYo);
    defineGlobalVariableObject("(DEFSPECIAL *DEBUGLEVEL* INTEGER 3 :DOCUMENTATION \"Integer between 0 and 3.  Higher levels generate more\ncode to aid debugging.\")", &oDEBUGLEVELo);
    defineGlobalVariableObject("(DEFSPECIAL *OPTIMIZESPEEDLEVEL* INTEGER 3 :DOCUMENTATION \"Integer between 0 and 3.  Higher levels optimize for\ngreater execution speed.\")", &oOPTIMIZESPEEDLEVELo);
    defineGlobalVariableObject("(DEFSPECIAL *OPTIMIZESPACELEVEL* INTEGER 3 :DOCUMENTATION \"Integer between 0 and 3.  Higher levels optimize for\nless code size and memory consumption.\")", &oOPTIMIZESPACELEVELo);
    defineGlobalVariableObject("(DEFSPECIAL *TRANSLATIONUNITS* (LIST OF TRANSLATION-UNIT) NULL :PUBLIC? TRUE :DOCUMENTATION \"List of objects representing partially walked\ntop-level definitions and auxiliary code.\")", &oTRANSLATIONUNITSo);
    defineGlobalVariableObject("(DEFSPECIAL *CURRENTTRANSLATIONUNIT* TRANSLATION-UNIT NULL :PUBLIC? TRUE :DOCUMENTATION \"The translation unit currently operated on.\")", &oCURRENTTRANSLATIONUNITo);
    defineGlobalVariableObject("(DEFSPECIAL *TRANSLATIONPHASE* KEYWORD NULL :PUBLIC? TRUE :DOCUMENTATION \"Indicates the current translation phase which is one of\n:DEFINE, :FINALIZE, :WALK, or :TRANSLATE.\")", &oTRANSLATIONPHASEo);
    defineGlobalVariableObject("(DEFSPECIAL *TRANSLATIONVERBOSITYLEVEL* INTEGER 1 :PUBLIC? TRUE :DOCUMENTATION \"The higher the level, the more progress annotations are\ngenerated during the translation of Stella declarations.\")", &oTRANSLATIONVERBOSITYLEVELo);
    defineGlobalVariableObject("(DEFSPECIAL *USEHARDCODEDSYMBOLS?* BOOLEAN FALSE)", &oUSEHARDCODEDSYMBOLSpo);
    defineGlobalVariableObject("(DEFSPECIAL *TRANSLATOROUTPUTLANGUAGE* KEYWORD (RUNNING-IN-LANGUAGE) :DOCUMENTATION \"Specifies the current translator output language; either\n:common-lisp, :idl, :java, :cpp, or :cpp-standalone.  The initial value\npoints to the native implementation language of this STELLA instance.\")", &oTRANSLATOROUTPUTLANGUAGEo);
    defineGlobalVariableObject("(DEFSPECIAL *LOCALVARIABLETYPETABLE* (KEY-VALUE-LIST OF SYMBOL STANDARD-OBJECT) NULL :DOCUMENTATION \"Table mapping local variable names their declared types\n(declared explicitly or implicitly).\")", &oLOCALVARIABLETYPETABLEo);
    defineGlobalVariableObject("(DEFSPECIAL *METHODBEINGWALKED* METHOD-SLOT NULL :DOCUMENTATION \"Contains the method or function being walked, or else `null'.\")", &oMETHODBEINGWALKEDo);
    defineGlobalVariableObject("(DEFSPECIAL *FOUNDRETURN?* BOOLEAN FALSE :DOCUMENTATION \"Indicates that one or more return statements have been found\nduring the walk of the current method.\")", &oFOUNDRETURNpo);
    defineGlobalVariableObject("(DEFSPECIAL *TARGETTYPE* TYPE-SPEC @VOID :DOCUMENTATION \"Bound to the target type for an expression currently walked.\nUsed instead of an extra argument to `walk-a-tree', since only a few types\nof expressions need to know about their expected type (e.g., FUNCALL).\")", &oTARGETTYPEo);
    defineGlobalVariableObject("(DEFSPECIAL *LOCALGENSYMTABLE* KEY-VALUE-LIST NULL :DOCUMENTATION \"Table that maps each prefix of a function-local gensym\nto its own gensym counter and/or to related gensyms.\")", &oLOCALGENSYMTABLEo);
    defineGlobalVariableObject("(DEFSPECIAL *TRANSLATIONERRORS* INTEGER 0 :PUBLIC? TRUE)", &oTRANSLATIONERRORSo);
    defineGlobalVariableObject("(DEFSPECIAL *TRANSLATIONWARNINGS* INTEGER 0 :PUBLIC? TRUE)", &oTRANSLATIONWARNINGSo);
    defineGlobalVariableObject("(DEFSPECIAL *TRANSLATIONNOTES* INTEGER 0 :PUBLIC? TRUE)", &oTRANSLATIONNOTESo);
    defineGlobalVariableObject("(DEFGLOBAL *FUNCTION-CALL-LOG-STREAM* OUTPUT-STREAM NULL :DOCUMENTATION \"The current log file to which function calls should be logged.\nA non-NULL value indicates that function call logging is enabled.\")", &oFUNCTION_CALL_LOG_STREAMo);
    defineGlobalVariableObject("(DEFGLOBAL *LOG-FUNCTION-CALLS?* BOOLEAN FALSE :DOCUMENTATION \"Translation switch which indicates that methods should\nbe instrumented to log their calls to a file.\")", &oLOG_FUNCTION_CALLSpo);
    defineGlobalVariableObject("(DEFGLOBAL *LOG-BREAK-POINT-COUNTER* INTEGER NULL)", &oLOG_BREAK_POINT_COUNTERo);
    defineGlobalVariableObject("(DEFGLOBAL *WRAPPED-TYPE-TABLE* (CONS OF CONS) (BQUOTE ((@INTEGER-WRAPPER @INTEGER) (@LONG-INTEGER-WRAPPER @LONG-INTEGER) (@FLOAT-WRAPPER @FLOAT) (@NUMBER-WRAPPER @NUMBER) (@STRING-WRAPPER @STRING) (@MUTABLE-STRING-WRAPPER @MUTABLE-STRING) (@CHARACTER-WRAPPER @CHARACTER) (@BOOLEAN-WRAPPER @BOOLEAN) (@FUNCTION-CODE-WRAPPER @FUNCTION-CODE) (@METHOD-CODE-WRAPPER @METHOD-CODE))) :DOCUMENTATION \"Table of pairs used by `wrapper-value-type' and\n`type-to-wrapped-type'.\")", &oWRAPPED_TYPE_TABLEo);
    defineGlobalVariableObject("(DEFGLOBAL *COERSION-TABLE* (CONS OF CONS) (BQUOTE ((@BOOLEAN @BOOLEAN-WRAPPER INLINE-WRAP-BOOLEAN) (@INTEGER @INTEGER-WRAPPER WRAP-LITERAL) (@LONG-INTEGER @LONG-INTEGER-WRAPPER WRAP-LITERAL) (@INTEGER @BOOLEAN-WRAPPER INTEGER-TO-BOOLEAN-WRAPPER) (@INTEGER @BOOLEAN INTEGER-TO-BOOLEAN) (@FLOAT @FLOAT-WRAPPER WRAP-LITERAL) (@MUTABLE-STRING @STRING MUTABLE-STRING-TO-STRING) (@MUTABLE-STRING @MUTABLE-STRING-WRAPPER WRAP-LITERAL) (@STRING @STRING-WRAPPER WRAP-LITERAL) (@STRING @MUTABLE-STRING STRING-TO-MUTABLE-STRING) (@STRING @SYMBOL INTERN-SYMBOL) (@CHARACTER @CHARACTER-WRAPPER WRAP-LITERAL) (@CHARACTER @STRING CHARACTER-TO-STRING) (@FUNCTION-CODE @FUNCTION-CODE-WRAPPER WRAP-LITERAL) (@METHOD-CODE @METHOD-CODE-WRAPPER WRAP-LITERAL) (@SYMBOL @STRING SYMBOL-NAME) (@BOOLEAN-WRAPPER @BOOLEAN INLINE-UNWRAP-BOOLEAN) (@INTEGER-WRAPPER @INTEGER WRAPPER-VALUE) (@INTEGER-WRAPPER @LONG-INTEGER WRAPPER-VALUE) (@LONG-INTEGER-WRAPPER @LONG-INTEGER WRAPPER-VALUE) (@FLOAT-WRAPPER @FLOAT WRAPPER-VALUE) (@NUMBER-WRAPPER @FLOAT N" "UMBER-WRAPPER-TO-FLOAT) (@STRING-WRAPPER @STRING WRAPPER-VALUE) (@MUTABLE-STRING-WRAPPER @MUTABLE-STRING WRAPPER-VALUE) (@CHARACTER-WRAPPER @CHARACTER WRAPPER-VALUE) (@FUNCTION-CODE-WRAPPER @FUNCTION-CODE WRAPPER-VALUE) (@METHOD-CODE-WRAPPER @METHOD-CODE WRAPPER-VALUE) (@SURROGATE @CLASS SURROGATE-VALUE) (@SURROGATE @MODULE SURROGATE-VALUE) (@INPUT-STREAM @NATIVE-INPUT-STREAM NATIVE-STREAM) (@OUTPUT-STREAM @NATIVE-OUTPUT-STREAM NATIVE-STREAM) (@NUMBER @INTEGER (CAST <X> @INTEGER)) (@NUMBER @LONG-INTEGER (CAST <X> @LONG-INTEGER)) (@NUMBER @FLOAT (CAST <X> @FLOAT)) (@INTEGER @FLOAT (CAST <X> @FLOAT)) (@INTEGER @SINGLE-FLOAT (CAST <X> @SINGLE-FLOAT)) (@LONG-INTEGER @FLOAT (CAST <X> @FLOAT)) (@LONG-INTEGER @SINGLE-FLOAT (CAST <X> @SINGLE-FLOAT)) (@FLOAT @SINGLE-FLOAT IDENTITY) (@FLOAT @DOUBLE-FLOAT IDENTITY) (@INTEGER @SHORT-INTEGER IDENTITY) (@INTEGER @LONG-INTEGER IDENTITY) (@INTEGER @UNSIGNED-SHORT-INTEGER IDENTITY) (@INTEGER @UNSIGNED-LONG-INTEGER IDENTITY))) :DOCUMENTATION \"Table of triples used by `lookup" "-coersion-method' to\nlocate a coersion method.\")", &oCOERSION_TABLEo);
    defineGlobalVariableObject("(DEFGLOBAL *SYMBOL-REGISTRY* (HASH-TABLE OF GENERALIZED-SYMBOL GENERALIZED-SYMBOL) (NEW (HASH-TABLE OF GENERALIZED-SYMBOL GENERALIZED-SYMBOL)) :PUBLIC? TRUE)", &oSYMBOL_REGISTRYo);
    defineGlobalVariableObject("(DEFGLOBAL *SYMBOL-SET* (LIST OF GENERALIZED-SYMBOL) (NEW (LIST OF GENERALIZED-SYMBOL)))", &oSYMBOL_SETo);
    defineGlobalVariableObject("(DEFSPECIAL *CURRENTFILENAME* STRING NULL :PUBLIC? TRUE :DOCUMENTATION \"Basename of file that is currently being translated.\nA NULL value indicates an incremental translation.\")", &oCURRENTFILENAMEo);
    defineGlobalVariableObject("(DEFSPECIAL *SPECIALVARIABLESTACK* (KEY-VALUE-LIST OF SYMBOL SYMBOL) (NEW (KEY-VALUE-LIST OF SYMBOL SYMBOL)) :DOCUMENTATION \"Stack mirroring the current state of bound specials\nwith their associated old-value variables.\")", &oSPECIALVARIABLESTACKo);
    defineGlobalVariableObject("(DEFSPECIAL *SPECIALSENABLED?* BOOLEAN TRUE :DOCUMENTATION \"`true' if using specials is enabled and legal.\")", &oSPECIALSENABLEDpo);
    defineGlobalVariableObject("(DEFSPECIAL *NOFSPECIALSATLOOPENTRY* INTEGER 0 :DOCUMENTATION \"Number of specials bound at the most recent entry\nto a LOOP/WHILE/FOREACH construct.\")", &oNOFSPECIALSATLOOPENTRYo);
    defineGlobalVariableObject("(DEFGLOBAL *TYPE-PREDICATE-TABLE* (CONS OF CONS) (BQUOTE ((@BOOLEAN BOOLEAN? SUBTYPE-OF-BOOLEAN?) (@INTEGER INTEGER? SUBTYPE-OF-INTEGER?) (@LONG-INTEGER LONG-INTEGER? SUBTYPE-OF-LONG-INTEGER?) (@FLOAT FLOAT? SUBTYPE-OF-FLOAT?) (@STRING STRING? SUBTYPE-OF-STRING?) (@CHARACTER CHARACTER? SUBTYPE-OF-CHARACTER?) (@WRAPPER WRAPPER? SUBTYPE-OF-WRAPPER?) (@BOOLEAN-WRAPPER BOOLEAN? SUBTYPE-OF-BOOLEAN?) (@INTEGER-WRAPPER INTEGER? SUBTYPE-OF-INTEGER?) (@LONG-INTEGER-WRAPPER LONG-INTEGER? SUBTYPE-OF-LONG-INTEGER?) (@FLOAT-WRAPPER FLOAT? SUBTYPE-OF-FLOAT?) (@STRING-WRAPPER STRING? SUBTYPE-OF-STRING?) (@CHARACTER-WRAPPER CHARACTER? SUBTYPE-OF-CHARACTER?) (@VERBATIM-STRING-WRAPPER VERBATIM-STRING? SUBTYPE-OF-VERBATIM-STRING?) (@SURROGATE SURROGATE? SUBTYPE-OF-SURROGATE?) (@TYPE TYPE? SUBTYPE-OF-TYPE?) (@SYMBOL SYMBOL? SUBTYPE-OF-SYMBOL?) (@TRANSIENT-SYMBOL TRANSIENT-SYMBOL? SUBTYPE-OF-TRANSIENT-SYMBOL?) (@KEYWORD KEYWORD? SUBTYPE-OF-KEYWORD?) (@CONS CONS? SUBTYPE-OF-CONS?) (@CLASS STELLA-CLASS? SUBTYPE-OF-CLASS?) (@STORAG" "E-SLOT STORAGE-SLOT? SUBTYPE-OF-STORAGE-SLOT?) (@METHOD-SLOT METHOD-SLOT? SUBTYPE-OF-METHOD-SLOT?) (@ANCHORED-TYPE-SPECIFIER ANCHORED-TYPE-SPECIFIER? SUBTYPE-OF-ANCHORED-TYPE-SPECIFIER?) (@PARAMETRIC-TYPE-SPECIFIER PARAMETRIC-TYPE-SPECIFIER? SUBTYPE-OF-PARAMETRIC-TYPE-SPECIFIER?))) :DOCUMENTATION \"Table of specialized type predicates for various types.\nThese predicates have to be used instead of `isa?', since they also work\nduring bootstrap when only some class objects are defined.\")", &oTYPE_PREDICATE_TABLEo);
    defineGlobalVariableObject("(DEFGLOBAL *NUMERIC-TYPE-HIERARCHY* (LIST OF TYPE) (LIST @INTEGER @LONG-INTEGER @FLOAT @NUMBER))", &oNUMERIC_TYPE_HIERARCHYo);
    defineGlobalVariableObject("(DEFSPECIAL *INLININGMETHODCALL?* BOOLEAN FALSE)", &oINLININGMETHODCALLpo);
    defineGlobalVariableObject("(DEFGLOBAL *MIXIN-IMPLEMENTATION-STYLE* KEYWORD :SECOND-CLASS :DOCUMENTATION \"A keyword describing how mixin classes are handled in\nsingle-inheritance target languages.  The legal values are\n:FIRST-CLASS-WITH-METHOD, which means that variables of a mixin type\nare legal and that slot access on a mixin type is facilitated by\ninherited-down accessor methods and a catch-all method on OBJECT,\n:FIRST-CLASS-WITH-TYPECASE which is similar but replaces the catch-all\nmethod with a function using a TYPECASE, and :SECOND-CLASS, which\nmeans that variables of a mixin type are illegal and no additional\naccessors and catch-all methods are needed.\")", &oMIXIN_IMPLEMENTATION_STYLEo);
    defineGlobalVariableObject("(DEFGLOBAL *MAX-NUMBER-OF-STARTUP-UNITS* INTEGER 60 :DOCUMENTATION \"The maximum number of startup units that can be combined\ninto a single startup function (this avoids the construction of huge startup\nfunctions that would cause too much stress for some wimpy compilers).\")", &oMAX_NUMBER_OF_STARTUP_UNITSo);
    defineGlobalVariableObject("(DEFGLOBAL *NATIVE-NAME-TABLE* (HASH-TABLE OF SYMBOL (KEY-VALUE-LIST OF KEYWORD LIST)) (NEW HASH-TABLE))", &oNATIVE_NAME_TABLEo);
    setDynamicSlotValue(lookupFunctionByName("LOOKUP-FUNCTION-CODE-BY-NAME")->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&stella_lookupFunctionCodeByName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOOKUP-C-CALLABLE-WRAPPER-CODE-BY-NAME")->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&stella_lookupCCallableWrapperCodeByName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOOKUP-FUNCTION-CPP-SIGNATURE-BY-NAME")->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&stella_lookupFunctionCppSignatureByName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOOKUP-FUNCTION-C-SIGNATURE-BY-NAME")->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&stella_lookupFunctionCSignatureByName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOOKUP-METHOD-CODE-BY-NAME")->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&stella_lookupMethodCodeByName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOOKUP-METHOD-CPP-SIGNATURE-BY-NAME")->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&stella_lookupMethodCppSignatureByName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOOKUP-METHOD-C-SIGNATURE-BY-NAME")->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&stella_lookupMethodCSignatureByName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOOKUP-STORAGE-SLOT-CPP-SIGNATURE-BY-NAME")->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&stella_lookupStorageSlotCppSignatureByName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOOKUP-STORAGE-SLOT-C-SIGNATURE-BY-NAME")->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&stella_lookupStorageSlotCSignatureByName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOOKUP-CLASS-CPP-TYPE-BY-NAME")->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&stella_lookupClassCppTypeByName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOOKUP-GLOBAL-VARIABLE-CPP-SIGNATURE-BY-NAME")->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&stella_lookupGlobalVariableCppSignatureByName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOOKUP-GLOBAL-VARIABLE-C-SIGNATURE-BY-NAME")->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&stella_lookupGlobalVariableCSignatureByName))), NULL_FUNCTION_CODE_WRAPPER);
    defineGlobalVariableObject("(DEFGLOBAL *GLOBAL-EXCEPTION-HANDLER* FUNCTION-CODE NULL :DOCUMENTATION \"Handler to handle exceptions caught within a c-callable function that throws exceptions.\nIf non-NULL the handler will be called with two string arguments: message and context.\nThis is intended primarily for language environments that can't directly catch native\nexceptions (e.g., if we are in C or Python).\" :PUBLIC? TRUE)", &oGLOBAL_EXCEPTION_HANDLERo);
    setDynamicSlotValue(lookupFunctionByName("GET-GLOBAL-EXCEPTION-HANDLER")->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&stella_getGlobalExceptionHandler))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("SET-GLOBAL-EXCEPTION-HANDLER")->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&stella_setGlobalExceptionHandler))), NULL_FUNCTION_CODE_WRAPPER);
    defineGlobalVariableObject("(DEFGLOBAL *C-API-RESULT-BUFFER* NATIVE-OBJECT-POINTER NULL :DOCUMENTATION \"Result buffer used to support temporary protection of garbage-collectable\nobjects when a C API function is called from a non-C environment (such as Python).\" :PUBLIC? FALSE)", &oC_API_RESULT_BUFFERo);
    setDynamicSlotValue(lookupFunctionByName("GC-PROTECT-OBJECT")->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&stella_gcProtectObject))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GC-RELEASE-OBJECT")->dynamicSlots, SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&stella_gcReleaseObject))), NULL_FUNCTION_CODE_WRAPPER);
    defineGlobalVariableObject("(DEFSPECIAL *EVALUATIONTREE* OBJECT NULL :PUBLIC? TRUE)", &oEVALUATIONTREEo);
    defineGlobalVariableObject("(DEFSPECIAL *EVALUATIONPARENTTREE* OBJECT NULL :PUBLIC? TRUE)", &oEVALUATIONPARENTTREEo);
  }
}

void startupWalk() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupWalk1();
      helpStartupWalk2();
      helpStartupWalk3();
      helpStartupWalk4();
      helpStartupWalk5();
      helpStartupWalk6();
      helpStartupWalk7();
      helpStartupWalk8();
    }
    if (currentStartupTimePhaseP(4)) {
      helpStartupWalk9();
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("TRANSLATION-UNIT", "(DEFCLASS TRANSLATION-UNIT (STANDARD-OBJECT) :PUBLIC? TRUE :PUBLIC-SLOTS ((TU-HOME-MODULE :TYPE MODULE :OPTION-KEYWORD :TU-HOME-MODULE) (THE-OBJECT :TYPE OBJECT) (CATEGORY :TYPE SYMBOL) (ANNOTATION :TYPE STRING) (AUXILIARY? :TYPE BOOLEAN) (CODE-REGISTER :TYPE OBJECT) (TRANSLATION :TYPE OBJECT) (REFERENCED-GLOBALS :TYPE (LIST OF GLOBAL-VARIABLE) :ALLOCATION :EMBEDDED :COMPONENT? TRUE)) :PUBLIC-METHODS ((HOME-MODULE ((SELF TRANSLATION-UNIT)) :TYPE MODULE (RETURN (TU-HOME-MODULE SELF)))) :PRINT-FORM (PRINT-TRANSLATION-UNIT SELF STREAM))");

        clasS->classConstructorCode = ((cpp_function_code)(&newTranslationUnit));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessTranslationUnitSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupWalk10();
      helpStartupWalk11();
      helpStartupWalk12();
      helpStartupWalk13();
      helpStartupWalk14();
      helpStartupWalk15();
      helpStartupWalk16();
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      helpStartupWalk17();
    }
  }
}

Keyword* KWD_WALK_WARN_ABOUT_UNDEFINED_METHODS = NULL;

Keyword* KWD_WALK_WARN_ABOUT_MISSING_METHODS = NULL;

Keyword* KWD_WALK_SUPPRESS_WARNINGS = NULL;

Keyword* KWD_WALK_USE_HARDCODED_SYMBOLS = NULL;

Keyword* KWD_WALK_USE_COMMON_LISP_STRUCTS = NULL;

Keyword* KWD_WALK_USE_COMMON_LISP_CONSES = NULL;

Keyword* KWD_WALK_USE_CPP_GARBAGE_COLLECTOR = NULL;

Keyword* KWD_WALK_MINIMIZE_JAVA_PREFIXES = NULL;

Keyword* KWD_WALK_TRANSLATE_WITH_COPYRIGHT_HEADER = NULL;

Keyword* KWD_WALK_SUPPORT_UNEXEC = NULL;

Keyword* KWD_WALK_USE_COMMON_LISP_VECTOR_STRUCTS = NULL;

Surrogate* SGT_WALK_STELLA_CONS = NULL;

Symbol* SYM_WALK_STELLA_MEMBp = NULL;

Symbol* SYM_WALK_STELLA_oTRACED_KEYWORDSo = NULL;

Surrogate* SGT_WALK_STELLA_VOID = NULL;

Symbol* SYM_WALK_STELLA_OR = NULL;

Symbol* SYM_WALK_STELLA_WHEN = NULL;

Symbol* SYM_WALK_STELLA_AND = NULL;

Symbol* SYM_WALK_STELLA_DEFINEDp = NULL;

Symbol* SYM_WALK_STELLA_PRINT = NULL;

Symbol* SYM_WALK_STELLA_EOL = NULL;

Keyword* KWD_WALK_COMMON_LISP = NULL;

Symbol* SYM_WALK_STELLA_FLUSH_OUTPUT = NULL;

Symbol* SYM_WALK_STELLA_STANDARD_OUTPUT = NULL;

Keyword* KWD_WALK_JAVA = NULL;

Surrogate* SGT_WALK_STELLA_F_GET_QUOTED_TREE_MEMO_TABLE_000 = NULL;

Surrogate* SGT_WALK_STELLA_TRANSLATION_UNIT = NULL;

Symbol* SYM_WALK_STELLA_HOME_MODULE = NULL;

Symbol* SYM_WALK_STELLA_TU_HOME_MODULE = NULL;

Symbol* SYM_WALK_STELLA_THE_OBJECT = NULL;

Symbol* SYM_WALK_STELLA_CATEGORY = NULL;

Symbol* SYM_WALK_STELLA_ANNOTATION = NULL;

Symbol* SYM_WALK_STELLA_AUXILIARYp = NULL;

Symbol* SYM_WALK_STELLA_CODE_REGISTER = NULL;

Symbol* SYM_WALK_STELLA_TRANSLATION = NULL;

Symbol* SYM_WALK_STELLA_REFERENCED_GLOBALS = NULL;

Symbol* SYM_WALK_STELLA_CLASS = NULL;

Symbol* SYM_WALK_STELLA_METHOD = NULL;

Symbol* SYM_WALK_STELLA_GLOBAL_VARIABLE = NULL;

Keyword* KWD_WALK_CPP = NULL;

Keyword* KWD_WALK_CPP_STANDALONE = NULL;

Keyword* KWD_WALK_IDL = NULL;

Symbol* SYM_WALK_STELLA_PROGN = NULL;

Symbol* SYM_WALK_STELLA_DEFCLASS = NULL;

Symbol* SYM_WALK_STELLA_DEFSLOT = NULL;

Symbol* SYM_WALK_STELLA_DEFMETHOD = NULL;

Symbol* SYM_WALK_STELLA_DEFUN = NULL;

Symbol* SYM_WALK_STELLA_DEFOPERATOR = NULL;

Symbol* SYM_WALK_STELLA_DEFGLOBAL = NULL;

Symbol* SYM_WALK_STELLA_DEFSPECIAL = NULL;

Symbol* SYM_WALK_STELLA_DEFCONSTANT = NULL;

Symbol* SYM_WALK_STELLA_DEFTYPE = NULL;

Symbol* SYM_WALK_STELLA_DEFMODULE = NULL;

Symbol* SYM_WALK_STELLA_DEFMACRO = NULL;

Symbol* SYM_WALK_STELLA_STARTUP_TIME_PROGN = NULL;

Symbol* SYM_WALK_STELLA_VERBATIM = NULL;

Symbol* SYM_WALK_STELLA_MODULE = NULL;

Symbol* SYM_WALK_STELLA_TYPE = NULL;

Symbol* SYM_WALK_STELLA_PRINT_METHOD = NULL;

Symbol* SYM_WALK_STELLA_SLOT = NULL;

Keyword* KWD_WALK_JAVA_STANDALONE = NULL;

Symbol* SYM_WALK_STELLA_METHOD_CONSTRUCTORp = NULL;

Keyword* KWD_WALK_DEFINE = NULL;

Keyword* KWD_WALK_FINALIZE = NULL;

Keyword* KWD_WALK_WALK = NULL;

Keyword* KWD_WALK_TRANSLATE = NULL;

Symbol* SYM_WALK_STELLA_METHOD_MACROp = NULL;

Surrogate* SGT_WALK_STELLA_GLOBAL_VARIABLE = NULL;

Surrogate* SGT_WALK_STELLA_TYPE_SPEC = NULL;

Surrogate* SGT_WALK_STELLA_MODULE = NULL;

Symbol* SYM_WALK_STELLA_SLOT_AUXILIARYp = NULL;

Symbol* SYM_WALK_STELLA_METHOD_GLOBALLY_INLINEp = NULL;

Symbol* SYM_WALK_STELLA_LOG_FUNCTION_CALL = NULL;

Symbol* SYM_WALK_STELLA_START_FUNCTION_CALL_LOGGING = NULL;

Symbol* SYM_WALK_STELLA_STOP_FUNCTION_CALL_LOGGING = NULL;

Symbol* SYM_WALK_STELLA_SET_CALL_LOG_BREAK_POINT = NULL;

Symbol* SYM_WALK_STELLA_BREAK_PROGRAM = NULL;

Symbol* SYM_WALK_STELLA_TERMINATE_PROGRAM = NULL;

Symbol* SYM_WALK_STELLA_PO = NULL;

Symbol* SYM_WALK_STELLA_NULLp = NULL;

Symbol* SYM_WALK_STELLA_EQp = NULL;

Symbol* SYM_WALK_STELLA_EQLp = NULL;

Symbol* SYM_WALK_STELLA_l = NULL;

Symbol* SYM_WALK_STELLA_le = NULL;

Symbol* SYM_WALK_STELLA_g = NULL;

Symbol* SYM_WALK_STELLA_ge = NULL;

Symbol* SYM_WALK_STELLA_CAST = NULL;

Surrogate* SGT_WALK_STELLA_UNKNOWN = NULL;

Surrogate* SGT_WALK_STELLA_LISP_CODE = NULL;

Surrogate* SGT_WALK_STELLA_OUTPUT_STREAM = NULL;

Surrogate* SGT_WALK_STELLA_NATIVE_OUTPUT_STREAM = NULL;

Symbol* SYM_WALK_STELLA_INLINE = NULL;

Surrogate* SGT_WALK_STELLA_UNINITIALIZED = NULL;

Keyword* KWD_WALK_SECOND_CLASS = NULL;

Surrogate* SGT_WALK_STELLA_KEY_VALUE_LIST = NULL;

Symbol* SYM_WALK_STELLA_NULL = NULL;

Keyword* KWD_WALK_TYPE = NULL;

Keyword* KWD_WALK_ALIAS = NULL;

Symbol* SYM_WALK_STELLA_ERROR = NULL;

Symbol* SYM_WALK_STELLA_ILLEGAL_EXPRESSION_FLAGGED_BY_THE_TRANSLATOR = NULL;

Symbol* SYM_WALK_STELLA_BAD_SYS = NULL;

Surrogate* SGT_WALK_STELLA_INTEGER_WRAPPER = NULL;

Surrogate* SGT_WALK_STELLA_INTEGER = NULL;

Surrogate* SGT_WALK_STELLA_LONG_INTEGER_WRAPPER = NULL;

Surrogate* SGT_WALK_STELLA_LONG_INTEGER = NULL;

Surrogate* SGT_WALK_STELLA_FLOAT_WRAPPER = NULL;

Surrogate* SGT_WALK_STELLA_FLOAT = NULL;

Surrogate* SGT_WALK_STELLA_NUMBER_WRAPPER = NULL;

Surrogate* SGT_WALK_STELLA_NUMBER = NULL;

Surrogate* SGT_WALK_STELLA_STRING_WRAPPER = NULL;

Surrogate* SGT_WALK_STELLA_STRING = NULL;

Surrogate* SGT_WALK_STELLA_MUTABLE_STRING_WRAPPER = NULL;

Surrogate* SGT_WALK_STELLA_MUTABLE_STRING = NULL;

Surrogate* SGT_WALK_STELLA_CHARACTER_WRAPPER = NULL;

Surrogate* SGT_WALK_STELLA_CHARACTER = NULL;

Surrogate* SGT_WALK_STELLA_BOOLEAN_WRAPPER = NULL;

Surrogate* SGT_WALK_STELLA_BOOLEAN = NULL;

Surrogate* SGT_WALK_STELLA_FUNCTION_CODE_WRAPPER = NULL;

Surrogate* SGT_WALK_STELLA_FUNCTION_CODE = NULL;

Surrogate* SGT_WALK_STELLA_METHOD_CODE_WRAPPER = NULL;

Surrogate* SGT_WALK_STELLA_METHOD_CODE = NULL;

Surrogate* SGT_WALK_STELLA_OBJECT = NULL;

Symbol* SYM_WALK_STELLA_INLINE_WRAP_BOOLEAN = NULL;

Symbol* SYM_WALK_STELLA_WRAP_LITERAL = NULL;

Symbol* SYM_WALK_STELLA_INTEGER_TO_BOOLEAN_WRAPPER = NULL;

Symbol* SYM_WALK_STELLA_INTEGER_TO_BOOLEAN = NULL;

Symbol* SYM_WALK_STELLA_MUTABLE_STRING_TO_STRING = NULL;

Symbol* SYM_WALK_STELLA_STRING_TO_MUTABLE_STRING = NULL;

Surrogate* SGT_WALK_STELLA_SYMBOL = NULL;

Symbol* SYM_WALK_STELLA_INTERN_SYMBOL = NULL;

Symbol* SYM_WALK_STELLA_CHARACTER_TO_STRING = NULL;

Symbol* SYM_WALK_STELLA_SYMBOL_NAME = NULL;

Symbol* SYM_WALK_STELLA_INLINE_UNWRAP_BOOLEAN = NULL;

Symbol* SYM_WALK_STELLA_WRAPPER_VALUE = NULL;

Symbol* SYM_WALK_STELLA_NUMBER_WRAPPER_TO_FLOAT = NULL;

Surrogate* SGT_WALK_STELLA_SURROGATE = NULL;

Surrogate* SGT_WALK_STELLA_CLASS = NULL;

Symbol* SYM_WALK_STELLA_SURROGATE_VALUE = NULL;

Surrogate* SGT_WALK_STELLA_INPUT_STREAM = NULL;

Surrogate* SGT_WALK_STELLA_NATIVE_INPUT_STREAM = NULL;

Symbol* SYM_WALK_STELLA_NATIVE_STREAM = NULL;

Symbol* SYM_WALK_STELLA_lXg = NULL;

Surrogate* SGT_WALK_STELLA_SINGLE_FLOAT = NULL;

Symbol* SYM_WALK_STELLA_IDENTITY = NULL;

Surrogate* SGT_WALK_STELLA_DOUBLE_FLOAT = NULL;

Surrogate* SGT_WALK_STELLA_SHORT_INTEGER = NULL;

Surrogate* SGT_WALK_STELLA_UNSIGNED_SHORT_INTEGER = NULL;

Surrogate* SGT_WALK_STELLA_UNSIGNED_LONG_INTEGER = NULL;

Symbol* SYM_WALK_STELLA_VRLET = NULL;

Symbol* SYM_WALK_STELLA_SYS_CALL_METHOD = NULL;

Symbol* SYM_WALK_STELLA_SYS_CALL_FUNCTION = NULL;

Symbol* SYM_WALK_STELLA_TYPED_SYS = NULL;

Symbol* SYM_WALK_STELLA_SYS_INLINE_CALL = NULL;

Symbol* SYM_WALK_STELLA_SAFE_CAST = NULL;

Surrogate* SGT_WALK_STELLA_NON_OBJECT = NULL;

Surrogate* SGT_WALK_STELLA_WRAPPER = NULL;

Symbol* SYM_WALK_STELLA_LET = NULL;

Symbol* SYM_WALK_STELLA_X = NULL;

Surrogate* SGT_WALK_STELLA_LITERAL = NULL;

Symbol* SYM_WALK_STELLA_VOID_SYS = NULL;

Symbol* SYM_WALK_STELLA_SLOT_TYPE_SPECIFIER = NULL;

Symbol* SYM_WALK_STELLA_SYS_FOREACH = NULL;

Symbol* SYM_WALK_STELLA_SETQ = NULL;

Symbol* SYM_WALK_STELLA_SYS_SET_DEFAULT = NULL;

Symbol* SYM_WALK_STELLA_SETF = NULL;

Symbol* SYM_WALK_STELLA_SLOT_VALUE = NULL;

Symbol* SYM_WALK_STELLA_SLOT_VALUE_SETTER = NULL;

Symbol* SYM_WALK_STELLA_AREF = NULL;

Symbol* SYM_WALK_STELLA_AREF_SETTER = NULL;

Symbol* SYM_WALK_STELLA_WITH_PROCESS_LOCK = NULL;

Symbol* SYM_WALK_STELLA_LOOP = NULL;

Symbol* SYM_WALK_STELLA_VALUES = NULL;

Symbol* SYM_WALK_STELLA_SPECIAL = NULL;

Symbol* SYM_WALK_STELLA_SYS_SPECIAL = NULL;

Symbol* SYM_WALK_STELLA_RETURN = NULL;

Symbol* SYM_WALK_STELLA_MV_SETQ = NULL;

Symbol* SYM_WALK_STELLA_MV_BIND = NULL;

Symbol* SYM_WALK_STELLA_BREAK = NULL;

Symbol* SYM_WALK_STELLA_CONTINUE = NULL;

Symbol* SYM_WALK_STELLA_WHILE = NULL;

Symbol* SYM_WALK_STELLA_FOREACH = NULL;

Symbol* SYM_WALK_STELLA_EXISTS = NULL;

Symbol* SYM_WALK_STELLA_FORALL = NULL;

Symbol* SYM_WALK_STELLA_SOME = NULL;

Symbol* SYM_WALK_STELLA_SETOF = NULL;

Symbol* SYM_WALK_STELLA_SET_OF = NULL;

Symbol* SYM_WALK_STELLA_SELECT = NULL;

Symbol* SYM_WALK_STELLA_IF = NULL;

Symbol* SYM_WALK_STELLA_UNLESS = NULL;

Symbol* SYM_WALK_STELLA_CHOOSE = NULL;

Symbol* SYM_WALK_STELLA_NOT = NULL;

Symbol* SYM_WALK_STELLA_COND = NULL;

Symbol* SYM_WALK_STELLA_CASE = NULL;

Symbol* SYM_WALK_STELLA_TYPECASE = NULL;

Symbol* SYM_WALK_STELLA_e = NULL;

Symbol* SYM_WALK_STELLA_i = NULL;

Symbol* SYM_WALK_STELLA__ = NULL;

Symbol* SYM_WALK_STELLA_o = NULL;

Symbol* SYM_WALK_STELLA_s = NULL;

Symbol* SYM_WALK_STELLA_QUOTE = NULL;

Symbol* SYM_WALK_STELLA_BQUOTE = NULL;

Symbol* SYM_WALK_STELLA_PRINT_STREAM = NULL;

Symbol* SYM_WALK_STELLA_PRINT_NATIVE_STREAM = NULL;

Symbol* SYM_WALK_STELLA_NEW = NULL;

Symbol* SYM_WALK_STELLA_ALLOCATE = NULL;

Symbol* SYM_WALK_STELLA_LOCAL_NEW = NULL;

Symbol* SYM_WALK_STELLA_MAKE = NULL;

Symbol* SYM_WALK_STELLA_FUNCALL = NULL;

Symbol* SYM_WALK_STELLA_SYS_CALL_FUNCTION_CODE = NULL;

Symbol* SYM_WALK_STELLA_SYS_CALL_METHOD_CODE = NULL;

Symbol* SYM_WALK_STELLA_THE_CODE = NULL;

Symbol* SYM_WALK_STELLA_CALL_SUPER_METHOD = NULL;

Symbol* SYM_WALK_STELLA_SIGNAL_EXCEPTION = NULL;

Symbol* SYM_WALK_STELLA_EXCEPTION_CASE = NULL;

Symbol* SYM_WALK_STELLA_UNWIND_PROTECT = NULL;

Symbol* SYM_WALK_STELLA_SYS_UNWIND_PROTECT = NULL;

Symbol* SYM_WALK_STELLA_SYS_SLOT_VALUE = NULL;

Symbol* SYM_WALK_STELLA_SYS_SLOT_VALUE_SETTER = NULL;

Symbol* SYM_WALK_STELLA_SYS_CALL_SUPER_METHOD = NULL;

Symbol* SYM_WALK_STELLA_SYS_CALL_METHOD_SETTER = NULL;

Symbol* SYM_WALK_STELLA_SYS_NEW = NULL;

Keyword* KWD_WALK_PUBLICp = NULL;

Symbol* SYM_WALK_STELLA_TRUE = NULL;

Keyword* KWD_WALK_SYMBOLS = NULL;

Symbol* SYM_WALK_STELLA_INTERN_RIGID_SYMBOL_WRT_MODULE = NULL;

Symbol* SYM_WALK_STELLA_GET_STELLA_MODULE = NULL;

Symbol* SYM_WALK_STELLA_INTERN_SYMBOL_AT = NULL;

Symbol* SYM_WALK_STELLA_INTERN_SURROGATE_AT = NULL;

Symbol* SYM_WALK_STELLA_INTERN_KEYWORD_AT = NULL;

Symbol* SYM_WALK_STELLA_FALSE = NULL;

Keyword* KWD_WALK_INLINE_ARGUMENT = NULL;

Surrogate* SGT_WALK_STELLA_KEYWORD = NULL;

Keyword* KWD_WALK_PLACE_WHERE_VRLET_WAS = NULL;

Keyword* KWD_WALK_PLACE_WHERE_LAST_EXPRESSION_WAS = NULL;

Keyword* KWD_WALK_DYNAMIC = NULL;

Symbol* SYM_WALK_STELLA_IT = NULL;

Symbol* SYM_WALK_STELLA_ON = NULL;

Symbol* SYM_WALK_STELLA_DYNAMIC_SLOTS = NULL;

Symbol* SYM_WALK_STELLA_WHERE = NULL;

Symbol* SYM_WALK_STELLA_KEY = NULL;

Symbol* SYM_WALK_STELLA_DO = NULL;

Symbol* SYM_WALK_STELLA_WRAPPEDVALUE = NULL;

Symbol* SYM_WALK_STELLA_VALUE = NULL;

Keyword* KWD_WALK_BIT = NULL;

Symbol* SYM_WALK_STELLA_DYNAMICSLOTS = NULL;

Symbol* SYM_WALK_STELLA_NEWVALUE = NULL;

Symbol* SYM_WALK_STELLA_FOUNDMATCHINGENTRYp = NULL;

Symbol* SYM_WALK_STELLA_THE_KV_LIST = NULL;

Symbol* SYM_WALK_STELLA_KV_CONS = NULL;

Symbol* SYM_WALK_STELLA_OLDVALUE = NULL;

Keyword* KWD_WALK_CONTEXT_SENSITIVEp = NULL;

Keyword* KWD_WALK_DONT_INHERITp = NULL;

Symbol* SYM_WALK_STELLA_ACCESS_IN_CONTEXT = NULL;

Symbol* SYM_WALK_STELLA_HOME_CONTEXT = NULL;

Keyword* KWD_WALK_COPY_TO_CHILDRENp = NULL;

Symbol* SYM_WALK_STELLA_UPDATE_IN_CONTEXT = NULL;

Symbol* SYM_WALK_STELLA_CS_VALUEp = NULL;

Surrogate* SGT_WALK_STELLA_ARRAY = NULL;

Symbol* SYM_WALK_STELLA_ANY_VALUE = NULL;

Symbol* SYM_WALK_STELLA_VARIABLE_DECLARATION = NULL;

Symbol* SYM_WALK_STELLA_ILLEGAL_VARIABLE = NULL;

Keyword* KWD_WALK_UNBIND_WITH_DESTRUCTORS = NULL;

Keyword* KWD_WALK_UNWIND_PROTECT = NULL;

Surrogate* SGT_WALK_STELLA_METHOD_SLOT = NULL;

Symbol* SYM_WALK_STELLA_OTHERWISE = NULL;

Symbol* SYM_WALK_STELLA_SYMBOL_ID = NULL;

Symbol* SYM_WALK_STELLA_GENERALIZED_SYMBOL = NULL;

Symbol* SYM_WALK_STELLA_BOOLEANp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_BOOLEANp = NULL;

Symbol* SYM_WALK_STELLA_INTEGERp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_INTEGERp = NULL;

Symbol* SYM_WALK_STELLA_LONG_INTEGERp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_LONG_INTEGERp = NULL;

Symbol* SYM_WALK_STELLA_FLOATp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_FLOATp = NULL;

Symbol* SYM_WALK_STELLA_STRINGp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_STRINGp = NULL;

Symbol* SYM_WALK_STELLA_CHARACTERp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_CHARACTERp = NULL;

Symbol* SYM_WALK_STELLA_WRAPPERp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_WRAPPERp = NULL;

Surrogate* SGT_WALK_STELLA_VERBATIM_STRING_WRAPPER = NULL;

Symbol* SYM_WALK_STELLA_VERBATIM_STRINGp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_VERBATIM_STRINGp = NULL;

Symbol* SYM_WALK_STELLA_SURROGATEp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_SURROGATEp = NULL;

Surrogate* SGT_WALK_STELLA_TYPE = NULL;

Symbol* SYM_WALK_STELLA_TYPEp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_TYPEp = NULL;

Symbol* SYM_WALK_STELLA_SYMBOLp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_SYMBOLp = NULL;

Surrogate* SGT_WALK_STELLA_TRANSIENT_SYMBOL = NULL;

Symbol* SYM_WALK_STELLA_TRANSIENT_SYMBOLp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_TRANSIENT_SYMBOLp = NULL;

Symbol* SYM_WALK_STELLA_KEYWORDp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_KEYWORDp = NULL;

Symbol* SYM_WALK_STELLA_CONSp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_CONSp = NULL;

Symbol* SYM_WALK_STELLA_STELLA_CLASSp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_CLASSp = NULL;

Surrogate* SGT_WALK_STELLA_STORAGE_SLOT = NULL;

Symbol* SYM_WALK_STELLA_STORAGE_SLOTp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_STORAGE_SLOTp = NULL;

Symbol* SYM_WALK_STELLA_METHOD_SLOTp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_METHOD_SLOTp = NULL;

Surrogate* SGT_WALK_STELLA_ANCHORED_TYPE_SPECIFIER = NULL;

Symbol* SYM_WALK_STELLA_ANCHORED_TYPE_SPECIFIERp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_ANCHORED_TYPE_SPECIFIERp = NULL;

Surrogate* SGT_WALK_STELLA_PARAMETRIC_TYPE_SPECIFIER = NULL;

Symbol* SYM_WALK_STELLA_PARAMETRIC_TYPE_SPECIFIERp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OF_PARAMETRIC_TYPE_SPECIFIERp = NULL;

Symbol* SYM_WALK_STELLA_ISAp = NULL;

Symbol* SYM_WALK_STELLA_SUBTYPE_OFp = NULL;

Surrogate* SGT_WALK_STELLA_GENERALIZED_SYMBOL = NULL;

Symbol* SYM_WALK_STELLA_STRING_EQLp = NULL;

Symbol* SYM_WALK_STELLA_SAFE_PRIMARY_TYPE = NULL;

Surrogate* SGT_WALK_STELLA_PROCESS_LOCK_OBJECT = NULL;

Surrogate* SGT_WALK_STELLA_STANDARD_OBJECT = NULL;

Symbol* SYM_WALK_STELLA_EQL_TO_BOOLEANp = NULL;

Symbol* SYM_WALK_STELLA_EQL_TO_INTEGERp = NULL;

Symbol* SYM_WALK_STELLA_EQL_TO_LONG_INTEGERp = NULL;

Symbol* SYM_WALK_STELLA_EQL_TO_FLOATp = NULL;

Symbol* SYM_WALK_STELLA_EQL_TO_STRINGp = NULL;

Symbol* SYM_WALK_STELLA_GET_QUOTED_TREE = NULL;

Symbol* SYM_WALK_STELLA_METHOD_BODY_ARGUMENTp = NULL;

Keyword* KWD_WALK_WARN = NULL;

Keyword* KWD_WALK_ERROR = NULL;

Keyword* KWD_WALK_CONTINUABLE_ERROR = NULL;

Symbol* SYM_WALK_STELLA_CLASS_CL_NATIVE_TYPE = NULL;

Symbol* SYM_WALK_STELLA_CLASS_CPP_NATIVE_TYPE = NULL;

Symbol* SYM_WALK_STELLA_CLASS_JAVA_NATIVE_TYPE = NULL;

Symbol* SYM_WALK_STELLA_CONCATENATE = NULL;

Symbol* SYM_WALK_STELLA_NIL = NULL;

Symbol* SYM_WALK_STELLA_WRAP_BOOLEAN = NULL;

Symbol* SYM_WALK_STELLA_CONS = NULL;

Symbol* SYM_WALK_STELLA_CONS_LIST = NULL;

Symbol* SYM_WALK_STELLA_ALLOCATE_ITERATOR = NULL;

Surrogate* SGT_WALK_STELLA_ARGUMENT_LIST_ITERATOR = NULL;

Symbol* SYM_WALK_STELLA_LENGTH = NULL;

Symbol* SYM_WALK_STELLA_METHOD_VARIABLE_ARGUMENTSp = NULL;

Symbol* SYM_WALK_STELLA_COPY_CONS_TREE = NULL;

Symbol* SYM_WALK_STELLA_GET_SYM = NULL;

Symbol* SYM_WALK_STELLA_GET_SGT = NULL;

Symbol* SYM_WALK_STELLA_GET_KWD = NULL;

Surrogate* SGT_WALK_STELLA_ARGUMENT_LIST = NULL;

Symbol* SYM_WALK_STELLA_CACHED_INLINABLE_METHOD_BODY = NULL;

Keyword* KWD_WALK_INLINE_REFERENCES = NULL;

Symbol* SYM_WALK_STELLA_INLINE_CALL = NULL;

Symbol* SYM_WALK_STELLA_METHOD_INHERITS_THROUGH = NULL;

Keyword* KWD_WALK_FUNCTION = NULL;

Symbol* SYM_WALK_STELLA_MAIN = NULL;

Symbol* SYM_WALK_STELLA_METHOD_NATIVEp = NULL;

Keyword* KWD_WALK_METHODS = NULL;

Symbol* SYM_WALK_STELLA_FORWARD_DECLARATIONp = NULL;

Symbol* SYM_WALK_STELLA_METHOD_COMMANDp = NULL;

Symbol* SYM_WALK_STELLA_C_CALLABLE_WRAPPER_CODE = NULL;

Symbol* SYM_WALK_STELLA_LOOKUP_FUNCTION_BY_NAME = NULL;

Keyword* KWD_WALK_CLASS = NULL;

Keyword* KWD_WALK_EMBEDDED = NULL;

Symbol* SYM_WALK_STELLA_CLASS_CONSTRUCTOR_CODE = NULL;

Symbol* SYM_WALK_STELLA_CLASS_AUXILIARY_METHODS = NULL;

Symbol* SYM_WALK_STELLA_AUXILIARY_METHOD_REASON = NULL;

Keyword* KWD_WALK_FIRST_CLASS_WITH_TYPECASE = NULL;

Keyword* KWD_WALK_AUXILIARYp = NULL;

Symbol* SYM_WALK_STELLA_PRINT_FORM = NULL;

Symbol* SYM_WALK_STELLA_PRINT_OBJECT = NULL;

Symbol* SYM_WALK_STELLA_SELF = NULL;

Symbol* SYM_WALK_STELLA_STREAM = NULL;

Symbol* SYM_WALK_STELLA_NATIVE_OUTPUT_STREAM = NULL;

Keyword* KWD_WALK_CLASSES = NULL;

Keyword* KWD_WALK_FINALIZE_CLASSES = NULL;

Symbol* SYM_WALK_STELLA_FINALIZE_CLASSES = NULL;

Keyword* KWD_WALK_FINALIZE_METHODS = NULL;

Symbol* SYM_WALK_STELLA_FINALIZE_SLOTS = NULL;

Symbol* SYM_WALK_STELLA_CLEANUP_UNFINALIZED_CLASSES = NULL;

Symbol* SYM_WALK_STELLA_DEFINE_EXTERNAL_SLOT_FROM_STRINGIFIED_SOURCE = NULL;

Keyword* KWD_WALK_MACROp = NULL;

Symbol* SYM_WALK_STELLA_OBJECT = NULL;

Keyword* KWD_WALK_UNBOUND_SPECIAL_VARIABLE = NULL;

Keyword* KWD_WALK_GLOBALS = NULL;

Symbol* SYM_WALK_STELLA_DEFINE_GLOBAL_VARIABLE_OBJECT = NULL;

Symbol* SYM_WALK_STELLA_DEFINE_STELLA_TYPE_FROM_STRINGIFIED_SOURCE = NULL;

Keyword* KWD_WALK_FINAL = NULL;

Symbol* SYM_WALK_STELLA_CURRENT_STARTUP_TIME_PHASEp = NULL;

Keyword* KWD_WALK_MODULES = NULL;

Symbol* SYM_WALK_STELLA_WITHIN_MODULE = NULL;

Symbol* SYM_WALK_STELLA_oSTELLA_MODULEo = NULL;

Symbol* SYM_WALK_STELLA_oSTARTUP_TIME_PHASEo = NULL;

Symbol* SYM_WALK_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

Keyword* KWD_WALK_C_CALLABLEp = NULL;

Keyword* KWD_WALK_C_NAMESPACE_PREFIX = NULL;

Symbol* SYM_WALK_STELLA_FUNCTION = NULL;

Symbol* SYM_WALK_STELLA_LOOKUP_FUNCTION = NULL;

Symbol* SYM_WALK_STELLA_oBOOTSTRAP_LOCKo = NULL;

Surrogate* SGT_WALK_STELLA_STELLA_ROOT_EXCEPTION = NULL;

Symbol* SYM_WALK_STELLA_SYS_SIGNAL = NULL;

Symbol* SYM_WALK_STELLA_SYS_HANDLER_CASE = NULL;

Surrogate* SGT_WALK_STELLA_NATIVE_EXCEPTION = NULL;

Symbol* SYM_WALK_STELLA_SYS_HANDLE_EXCEPTION = NULL;

Keyword* KWD_WALK_OTHERWISE = NULL;

Symbol* SYM_WALK_STELLA_INITIAL_ELEMENT = NULL;

Symbol* SYM_WALK_STELLA_SIZE = NULL;

Symbol* SYM_WALK_STELLA_STORAGE_SLOT = NULL;

Surrogate* SGT_WALK_STELLA_CODE = NULL;

Keyword* KWD_WALK_METHOD = NULL;

Symbol* SYM_WALK_STELLA_METHOD_CODE = NULL;

Surrogate* SGT_WALK_STELLA_COMPOUND_TYPE_SPECIFIER = NULL;

Symbol* SYM_WALK_STELLA_METHOD_LISP_MACROp = NULL;

Symbol* SYM_WALK_STELLA_DOCUMENTATION = NULL;

Symbol* SYM_WALK_STELLA_EXPRESSION = NULL;

Symbol* SYM_WALK_STELLA_IGNORE = NULL;

Symbol* SYM_WALK_STELLA_oIGNORETRANSLATIONERRORSpo = NULL;

Symbol* SYM_WALK_STELLA_CL_INCREMENTALLY_TRANSLATE = NULL;

Symbol* SYM_WALK_STELLA_REGISTER_NATIVE_NAME = NULL;

Symbol* SYM_WALK_STELLA_METHOD_C_CALLABLEp = NULL;

Symbol* SYM_WALK_STELLA_METHOD_C_NAMESPACE_PREFIX = NULL;

Symbol* SYM_WALK_STELLA_oC_API_RESULT_BUFFERo = NULL;

Symbol* SYM_WALK_STELLA_NATIVE_OBJECT_POINTER = NULL;

Symbol* SYM_WALK_STELLA_METHOD_THROWS_EXCEPTIONSp = NULL;

Symbol* SYM_WALK_STELLA_NATIVE_EXCEPTION = NULL;

Symbol* SYM_WALK_STELLA_E = NULL;

Symbol* SYM_WALK_STELLA_CALL_GLOBAL_EXCEPTION_HANDLER = NULL;

Keyword* KWD_WALK_DOCUMENTATION = NULL;

Symbol* SYM_WALK_STELLA_CPP_VAR_ARGS = NULL;

Symbol* SYM_WALK_STELLA_REST = NULL;

Symbol* SYM_WALK_STELLA_NTH_REST = NULL;

Symbol* SYM_WALK_STELLA_NTH = NULL;

Symbol* SYM_WALK_STELLA_ARGUMENTS = NULL;

Symbol* SYM_WALK_STELLA_RESULT = NULL;

Symbol* SYM_WALK_STELLA_METHOD_EVALUATE_ARGUMENTSp = NULL;

Symbol* SYM_WALK_STELLA_APPEND = NULL;

Symbol* SYM_WALK_STELLA_EVALUATOR_WRAPPER_CODE = NULL;

Symbol* SYM_WALK_STELLA_VARIABLE_TYPE_SPECIFIER = NULL;

Symbol* SYM_WALK_STELLA_LISTo = NULL;

Symbol* SYM_WALK_STELLA_STARTUP_WALK = NULL;

} // end of namespace stella
