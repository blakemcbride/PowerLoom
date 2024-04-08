//  -*- Mode: C++ -*-

// cl-translate-file.cc

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

void lptrans(Object* statement) {
  // Translate `statement' to Common-Lisp and print the result.
  helpLptrans(statement);
}

void ptrans(Object* statement) {
  // Translate `statement' to Common-Lisp and print the result.
  helpLptrans(statement);
}

void helpLptrans(Object* statement) {
  { 
    BIND_STELLA_SPECIAL(oTRANSLATOROUTPUTLANGUAGEo, Keyword*, oTRANSLATOROUTPUTLANGUAGEo);
    BIND_STELLA_SPECIAL(oPRINTPRETTYCODEpo, boolean, true);
    setTranslatorOutputLanguage(KWD_CL_TRANSLATE_FILE_COMMON_LISP);
    { boolean declarationP = declarationTreeP(((Cons*)(statement)));
      Object* translation = incrementallyTranslate(statement);

      if (declarationP &&
          (consP(translation) &&
           (((Cons*)(translation))->value == internCommonLispSymbol("PROGN")))) {
        { Object* elt = NULL;
          Cons* iter000 = ((Cons*)(translation))->rest;
          int i = NULL_INTEGER;
          int iter001 = 1;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest,
                iter001 = iter001 + 1) {
            elt = iter000->value;
            i = iter001;
            if (i == 1) {
              printStellaDefinition(elt, STANDARD_OUTPUT->nativeStream);
            }
            else {
              printStellaCode(elt, STANDARD_OUTPUT->nativeStream);
            }
          }
        }
      }
      else {
        printStellaCode(translation, STANDARD_OUTPUT->nativeStream);
      }
    }
  }
}

boolean auxiliaryVariableUnitP(TranslationUnit* unit) {
  return (unit->auxiliaryP &&
      (unit->category == SYM_CL_TRANSLATE_FILE_STELLA_GLOBAL_VARIABLE));
}

void clOutputOneUnit(TranslationUnit* unit, std::ostream* stream) {
  { Object* translation = unit->translation;

    if (!((boolean)(translation))) {
      std::cout << "`" << unit << "'" << " has a NULL translation." << std::endl;
      return;
    }
    if (((boolean)(unit->category))) {
      if (!(auxiliaryVariableUnitP(unit))) {
        *(stream) << std::endl;
      }
      if (unit->annotation != NULL) {
        *(stream) << ";;; " << unit->annotation << std::endl << std::endl;
      }
      if (isaP(translation, SGT_CL_TRANSLATE_FILE_STELLA_CONS) &&
          (((Cons*)(translation))->value == internCommonLispSymbol("PROGN"))) {
        { Object* form = NULL;
          Cons* iter000 = ((Cons*)(translation))->rest;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            form = iter000->value;
            printStellaDefinition(form, stream);
          }
        }
      }
      else {
        printStellaDefinition(translation, stream);
      }
      unit->category = NULL;
    }
  }
}

void clOutputAllUnitsToFile(const char* sourcefile) {
  { const char* outputfile = makeFileName(sourcefile, KWD_CL_TRANSLATE_FILE_LISP, false);
    OutputFileStream* outputstream = openOutputFile(outputfile, 2, KWD_CL_TRANSLATE_FILE_IF_NOT_EXISTS, KWD_CL_TRANSLATE_FILE_CREATE_PATH);
    std::ostream* nativeoutputstream = outputstream->nativeStream;

    if (oTRANSLATIONVERBOSITYLEVELo >= 1) {
      std::cout << "Writing " << "`" << outputfile << "'" << "..." << std::endl;
    }
    outputFileHeader(outputstream, outputfile);
    *(nativeoutputstream) << ";;; Auxiliary variables:" << std::endl << std::endl;
    { TranslationUnit* unit = NULL;
      Cons* iter000 = oTRANSLATIONUNITSo->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        unit = ((TranslationUnit*)(iter000->value));
        if (auxiliaryVariableUnitP(unit)) {
          clOutputOneUnit(unit, nativeoutputstream);
        }
      }
    }
    clOutputForwardDeclarations(nativeoutputstream);
    if (oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_FILE_USE_COMMON_LISP_STRUCTS) &&
        (!oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_FILE_USE_COMMON_LISP_VECTOR_STRUCTS))) {
      { TranslationUnit* unit = NULL;
        Cons* iter001 = oTRANSLATIONUNITSo->theConsList;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          unit = ((TranslationUnit*)(iter001->value));
          if (unit->category == SYM_CL_TRANSLATE_FILE_STELLA_CLASS) {
            clOutputOneUnit(unit, nativeoutputstream);
          }
        }
      }
    }
    { TranslationUnit* unit = NULL;
      Cons* iter002 = oTRANSLATIONUNITSo->theConsList;

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        unit = ((TranslationUnit*)(iter002->value));
        if (!auxiliaryVariableUnitP(unit)) {
          clOutputOneUnit(unit, nativeoutputstream);
        }
      }
    }
    outputstream->free();
  }
}

void clOutputFileHeader(OutputStream* stream, const char* file, boolean ensurepackageP) {
  { const char* package = oMODULEo->lispPackage();

    *(stream->nativeStream) << ";;; -*- Mode: Lisp; Package: " << package << "; Syntax: COMMON-LISP; Base: 10 -*-" << std::endl << std::endl;
    if (file != NULL) {
      *(stream->nativeStream) << ";;; " << fileNameWithoutDirectory(file) << std::endl << std::endl;
    }
    { 
      BIND_STELLA_SPECIAL(oTRANSLATOROUTPUTLANGUAGEo, Keyword*, KWD_CL_TRANSLATE_FILE_COMMON_LISP);
      outputCopyrightHeader(stream);
    }
    if (!(stringEqlP(package, "STELLA") ||
        (!ensurepackageP))) {
      clOutputEnsurePackageDefinition(stream, package);
      *(stream->nativeStream) << std::endl;
    }
    clOutputInPackageDeclaration(stream, package);
    *(stream->nativeStream) << std::endl;
  }
}

void clOutputEnsurePackageDefinition(OutputStream* stream, const char* package) {
  *(stream->nativeStream) << "(CL:EVAL-WHEN (:COMPILE-TOPLEVEL :LOAD-TOPLEVEL :EXECUTE)" << std::endl << "  (CL:UNLESS (CL:FIND-PACKAGE \"" << package << "\")" << std::endl << "     (CL:DEFPACKAGE \"" << package << "\" (:USE))))" << std::endl;
}

void clOutputInPackageDeclaration(OutputStream* stream, const char* package) {
  *(stream->nativeStream) << "(CL:IN-PACKAGE \"" << package << "\")" << std::endl;
}

void clOutputForwardDeclarations(std::ostream* stream) {
  { List* definedvariables = newList();
    List* forwardreferencedvariables = newList();

    { TranslationUnit* unit = NULL;
      Cons* iter000 = oTRANSLATIONUNITSo->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        unit = ((TranslationUnit*)(iter000->value));
        if (auxiliaryVariableUnitP(unit)) {
          definedvariables->push(unit->theObject);
        }
      }
    }
    { TranslationUnit* unit = NULL;
      Cons* iter001 = oTRANSLATIONUNITSo->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        unit = ((TranslationUnit*)(iter001->value));
        if (!auxiliaryVariableUnitP(unit)) {
          if (unit->category == SYM_CL_TRANSLATE_FILE_STELLA_GLOBAL_VARIABLE) {
            definedvariables->push(unit->theObject);
          }
          { GlobalVariable* variable = NULL;
            Cons* iter002 = unit->referencedGlobals->theConsList;

            for (; !(iter002 == NIL); iter002 = iter002->rest) {
              variable = ((GlobalVariable*)(iter002->value));
              if ((!definedvariables->memberP(variable)) &&
                  (!forwardreferencedvariables->memberP(variable))) {
                forwardreferencedvariables->push(variable);
              }
            }
          }
        }
      }
    }
    { ListIterator* it = ((ListIterator*)(forwardreferencedvariables->allocateIterator()));

      for (; it->nextP(); ) {
        it->valueSetter(((GlobalVariable*)(it->value))->variableName);
      }
    }
    if (forwardreferencedvariables->nonEmptyP()) {
      *(stream) << std::endl << ";;; Forward declarations:" << std::endl << std::endl;
      printStellaDefinition(listO(3, internCommonLispSymbol("DECLAIM"), cons(internCommonLispSymbol("SPECIAL"), clTranslateListOfTrees(forwardreferencedvariables->theConsList)->concatenate(NIL, 0)), NIL), stream);
    }
    definedvariables->free();
    forwardreferencedvariables->free();
  }
}

void clTranslateFile(const char* file, boolean relativeP) {
  // Translate a Stella `file' to Common-Lisp.  If
  // `relative?', concatenate root directory to `file'.
  if (relativeP) {
    file = makeFileName(file, KWD_CL_TRANSLATE_FILE_STELLA, true);
  }
  translateFile(file, KWD_CL_TRANSLATE_FILE_COMMON_LISP, false);
}

void clTranslateWalkedSystemUnits(KeyValueList* systemunits) {
  { 
    BIND_STELLA_SPECIAL(oCURRENTFILENAMEo, const char*, NULL);
    BIND_STELLA_SPECIAL(oTRANSLATIONUNITSo, List*, NULL);
    { List* classunits = newList();
      boolean useclstructsP = oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_FILE_USE_COMMON_LISP_STRUCTS);
      const char* filename = NULL;

      { StringWrapper* file = NULL;
        List* units = NULL;
        KvCons* iter000 = systemunits->theKvList;

        for  (; ((boolean)(iter000)); 
              iter000 = iter000->rest) {
          file = ((StringWrapper*)(iter000->key));
          units = ((List*)(iter000->value));
          oCURRENTFILENAMEo = fileBaseName(file->wrapperValue);
          if (useclstructsP) {
            oTRANSLATIONUNITSo = newList();
            { TranslationUnit* unit = NULL;
              Cons* iter001 = units->theConsList;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                unit = ((TranslationUnit*)(iter001->value));
                if (unit->category == SYM_CL_TRANSLATE_FILE_STELLA_CLASS) {
                  classunits->push(unit);
                }
                else {
                  oTRANSLATIONUNITSo->push(unit);
                }
              }
            }
            oTRANSLATIONUNITSo->reverse();
          }
          else {
            oTRANSLATIONUNITSo = units;
          }
          { 
            BIND_STELLA_SPECIAL(oMODULEo, Module*, computeFileUnitsModule(units));
            BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
            translateAndOutputUnitsToFile(file->wrapperValue, "Common Lisp");
          }
          cleanUpTranslationUnitsSpecial();
        }
      }
      if (useclstructsP) {
        if (oTRANSLATIONVERBOSITYLEVELo >= 1) {
          std::cout << "Collecting CL structure class definitions..." << std::endl;
        }
        { StringWrapper* file = NULL;
          Cons* iter002 = filesPlusSystemStartup(systemDefinitionSourceFiles(oCURRENTSYSTEMDEFINITIONo));

          for (; !(iter002 == NIL); iter002 = iter002->rest) {
            file = ((StringWrapper*)(iter002->value));
            if (!((boolean)(((List*)(systemunits->lookup(wrapString(filename = makeFileName(file->wrapperValue, KWD_CL_TRANSLATE_FILE_STELLA, true)))))))) {
              oTRANSLATIONUNITSo = newList();
              oCURRENTFILENAMEo = fileBaseName(filename);
              oTRANSLATIONUNITSo = newList();
              operateOnFile(filename, KWD_CL_TRANSLATE_FILE_FINALIZE);
              { TranslationUnit* unit = NULL;
                Cons* iter003 = oTRANSLATIONUNITSo->theConsList;
                Cons* collect000 = NULL;

                for  (; !(iter003 == NIL); 
                      iter003 = iter003->rest) {
                  unit = ((TranslationUnit*)(iter003->value));
                  if ((unit->category == SYM_CL_TRANSLATE_FILE_STELLA_CLASS) &&
                      (createNativeClassP(((Class*)(unit->theObject))) &&
                       (!((Class*)(unit->theObject))->mixinP))) {
                    if (!((boolean)(collect000))) {
                      {
                        collect000 = cons(unit, NIL);
                        if (classunits->theConsList == NIL) {
                          classunits->theConsList = collect000;
                        }
                        else {
                          addConsToEndOfConsList(classunits->theConsList, collect000);
                        }
                      }
                    }
                    else {
                      {
                        collect000->rest = cons(unit, NIL);
                        collect000 = collect000->rest;
                      }
                    }
                  }
                }
              }
              cleanUpTranslationUnitsSpecial();
            }
          }
        }
        clOutputSystemClStructsFile(classunits);
      }
    }
  }
}

List* sortClStructClasses(List* unsortedclasses) {
  { HashTable* classtable = newHashTable();
    List* roots = list(0);
    List* sortedclasses = list(0);

    { Class* clasS = NULL;
      Cons* iter000 = unsortedclasses->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        clasS = ((Class*)(iter000->value));
        classtable->insertAt(clasS->classType, TRUE_WRAPPER);
      }
    }
    { Class* clasS = NULL;
      Cons* iter001 = unsortedclasses->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest) {
        clasS = ((Class*)(iter001->value));
        { boolean testValue000 = false;

          { boolean foundP000 = false;

            { Surrogate* super = NULL;
              Cons* iter002 = clasS->classDirectSupers->theConsList;

              for (; !(iter002 == NIL); iter002 = iter002->rest) {
                super = ((Surrogate*)(iter002->value));
                if (((boolean)(((BooleanWrapper*)(classtable->lookup(super)))))) {
                  foundP000 = true;
                  break;
                }
              }
            }
            testValue000 = foundP000;
          }
          testValue000 = !testValue000;
          if (testValue000) {
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(clasS, NIL);
                if (roots->theConsList == NIL) {
                  roots->theConsList = collect000;
                }
                else {
                  addConsToEndOfConsList(roots->theConsList, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(clasS, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
      }
    }
    while (roots->nonEmptyP()) {
      sortedclasses->push(((Class*)(roots->first())));
      { Surrogate* sub = NULL;
        Cons* iter003 = ((Class*)(roots->pop()))->classDirectSubs->theConsList;

        for (; !(iter003 == NIL); iter003 = iter003->rest) {
          sub = ((Surrogate*)(iter003->value));
          if (((boolean)(((BooleanWrapper*)(classtable->lookup(sub)))))) {
            roots->push(((Class*)(sub->surrogateValue)));
          }
        }
      }
    }
    return (sortedclasses->reverse());
  }
}

const char* clYieldStructClassFileName(const char* systemname) {
  return (stringConcatenate(stringDowncase(systemname), "-system-structs", 0));
}

void clOutputSystemClStructsFile(List* classunits) {
  { const char* outputfile = makeFileName(clYieldStructClassFileName(oCURRENTSYSTEMDEFINITIONo->name), KWD_CL_TRANSLATE_FILE_LISP, true);
    OutputFileStream* outputstream = openOutputFile(outputfile, 2, KWD_CL_TRANSLATE_FILE_IF_NOT_EXISTS, KWD_CL_TRANSLATE_FILE_CREATE_PATH);
    List* classes = newList();
    Module* currentmodule = oMODULEo;
    const char* package = NULL;
    List* ensuredpackages = list(0);

    { TranslationUnit* unit = NULL;
      Cons* iter000 = classunits->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        unit = ((TranslationUnit*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(unit->theObject, NIL);
            if (classes->theConsList == NIL) {
              classes->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(classes->theConsList, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(unit->theObject, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    classes = sortClStructClasses(classes);
    if (oTRANSLATIONVERBOSITYLEVELo >= 1) {
      std::cout << "Writing " << "`" << outputfile << "'" << "..." << std::endl;
    }
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oMODULEo);
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      if (classes->nonEmptyP()) {
        oMODULEo = ((Class*)(classes->first()))->homeModule();
      }
      else {
        oMODULEo = getStellaModule(oCURRENTSYSTEMDEFINITIONo->cardinalModule, true);
      }
      currentmodule = oMODULEo;
      clOutputFileHeader(outputstream, outputfile, true);
      { TranslationUnit* unit = NULL;
        Cons* iter001 = classunits->theConsList;
        Class* clasS = NULL;
        Cons* iter002 = classes->theConsList;

        for  (; (!(iter001 == NIL)) &&
                  (!(iter002 == NIL)); 
              iter001 = iter001->rest,
              iter002 = iter002->rest) {
          unit = ((TranslationUnit*)(iter001->value));
          clasS = ((Class*)(iter002->value));
          unit->theObject = clasS;
          unit->annotation = NULL;
          oMODULEo = clasS->homeModule();
          if (!(oMODULEo == currentmodule)) {
            currentmodule = oMODULEo;
            package = oMODULEo->lispPackage();
            if (!(ensuredpackages->memberP(wrapString(package)))) {
              ensuredpackages->push(wrapString(package));
              *(outputstream->nativeStream) << std::endl;
              clOutputEnsurePackageDefinition(outputstream, package);
            }
            *(outputstream->nativeStream) << std::endl;
            clOutputInPackageDeclaration(outputstream, package);
          }
          unit->translation = clTranslateDefineNativeClassUnit(unit);
          clOutputOneUnit(unit, outputstream->nativeStream);
        }
      }
    }
    outputstream->free();
  }
}

void clTranslateSystem(const char* systemName) {
  // Translate a Stella system named `system-name' to Common Lisp.
  translateSystem(systemName, consList(7, KWD_CL_TRANSLATE_FILE_COMMON_LISP, KWD_CL_TRANSLATE_FILE_TWO_PASSp, TRUE_WRAPPER, KWD_CL_TRANSLATE_FILE_FORCE_TRANSLATIONp, TRUE_WRAPPER, KWD_CL_TRANSLATE_FILE_PRODUCTION_SETTINGSp, TRUE_WRAPPER));
}

boolean clCompileAndLoadFiles(Cons* files, boolean relativeP, boolean forcerecompilationP) {
  { Keyword* lispkey = KWD_CL_TRANSLATE_FILE_LISP;
    Keyword* binarykey = KWD_CL_TRANSLATE_FILE_LISP_BINARY;
    boolean translatedfileP = false;

    return (translatedfileP);
  }
}

void clTranslateStella(boolean productionsettingsP) {
  translateSystem("stella", consList(5, KWD_CL_TRANSLATE_FILE_COMMON_LISP, KWD_CL_TRANSLATE_FILE_FORCE_TRANSLATIONp, TRUE_WRAPPER, KWD_CL_TRANSLATE_FILE_PRODUCTION_SETTINGSp, (productionsettingsP ? TRUE_WRAPPER : FALSE_WRAPPER)));
}

void clRetranslateStella(boolean productionsettingsP) {
  translateSystem("stella", consList(7, KWD_CL_TRANSLATE_FILE_COMMON_LISP, KWD_CL_TRANSLATE_FILE_TWO_PASSp, TRUE_WRAPPER, KWD_CL_TRANSLATE_FILE_FORCE_TRANSLATIONp, TRUE_WRAPPER, KWD_CL_TRANSLATE_FILE_PRODUCTION_SETTINGSp, (productionsettingsP ? TRUE_WRAPPER : FALSE_WRAPPER)));
}

void startupClTranslateFile() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      KWD_CL_TRANSLATE_FILE_COMMON_LISP = ((Keyword*)(internRigidSymbolWrtModule("COMMON-LISP", NULL, 2)));
      SYM_CL_TRANSLATE_FILE_STELLA_GLOBAL_VARIABLE = ((Symbol*)(internRigidSymbolWrtModule("GLOBAL-VARIABLE", NULL, 0)));
      SGT_CL_TRANSLATE_FILE_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
      KWD_CL_TRANSLATE_FILE_LISP = ((Keyword*)(internRigidSymbolWrtModule("LISP", NULL, 2)));
      KWD_CL_TRANSLATE_FILE_IF_NOT_EXISTS = ((Keyword*)(internRigidSymbolWrtModule("IF-NOT-EXISTS", NULL, 2)));
      KWD_CL_TRANSLATE_FILE_CREATE_PATH = ((Keyword*)(internRigidSymbolWrtModule("CREATE-PATH", NULL, 2)));
      KWD_CL_TRANSLATE_FILE_USE_COMMON_LISP_STRUCTS = ((Keyword*)(internRigidSymbolWrtModule("USE-COMMON-LISP-STRUCTS", NULL, 2)));
      KWD_CL_TRANSLATE_FILE_USE_COMMON_LISP_VECTOR_STRUCTS = ((Keyword*)(internRigidSymbolWrtModule("USE-COMMON-LISP-VECTOR-STRUCTS", NULL, 2)));
      SYM_CL_TRANSLATE_FILE_STELLA_CLASS = ((Symbol*)(internRigidSymbolWrtModule("CLASS", NULL, 0)));
      KWD_CL_TRANSLATE_FILE_STELLA = ((Keyword*)(internRigidSymbolWrtModule("STELLA", NULL, 2)));
      KWD_CL_TRANSLATE_FILE_FINALIZE = ((Keyword*)(internRigidSymbolWrtModule("FINALIZE", NULL, 2)));
      KWD_CL_TRANSLATE_FILE_TWO_PASSp = ((Keyword*)(internRigidSymbolWrtModule("TWO-PASS?", NULL, 2)));
      KWD_CL_TRANSLATE_FILE_FORCE_TRANSLATIONp = ((Keyword*)(internRigidSymbolWrtModule("FORCE-TRANSLATION?", NULL, 2)));
      KWD_CL_TRANSLATE_FILE_PRODUCTION_SETTINGSp = ((Keyword*)(internRigidSymbolWrtModule("PRODUCTION-SETTINGS?", NULL, 2)));
      KWD_CL_TRANSLATE_FILE_LISP_BINARY = ((Keyword*)(internRigidSymbolWrtModule("LISP-BINARY", NULL, 2)));
      SYM_CL_TRANSLATE_FILE_STELLA_STARTUP_CL_TRANSLATE_FILE = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-CL-TRANSLATE-FILE", NULL, 0)));
      SYM_CL_TRANSLATE_FILE_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("LPTRANS", "(DEFUN LPTRANS ((STATEMENT OBJECT)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Translate `statement' to Common-Lisp and print the result.\")", ((cpp_function_code)(&lptrans)), NULL);
      defineFunctionObject("PTRANS", "(DEFUN PTRANS ((STATEMENT OBJECT)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Translate `statement' to Common-Lisp and print the result.\")", ((cpp_function_code)(&ptrans)), NULL);
      defineFunctionObject("HELP-LPTRANS", "(DEFUN HELP-LPTRANS ((STATEMENT OBJECT)))", ((cpp_function_code)(&helpLptrans)), NULL);
      defineFunctionObject("AUXILIARY-VARIABLE-UNIT?", "(DEFUN (AUXILIARY-VARIABLE-UNIT? BOOLEAN) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&auxiliaryVariableUnitP)), NULL);
      defineFunctionObject("CL-OUTPUT-ONE-UNIT", "(DEFUN CL-OUTPUT-ONE-UNIT ((UNIT TRANSLATION-UNIT) (STREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&clOutputOneUnit)), NULL);
      defineFunctionObject("CL-OUTPUT-ALL-UNITS-TO-FILE", "(DEFUN CL-OUTPUT-ALL-UNITS-TO-FILE ((SOURCEFILE FILE-NAME)))", ((cpp_function_code)(&clOutputAllUnitsToFile)), NULL);
      defineFunctionObject("CL-OUTPUT-FILE-HEADER", "(DEFUN CL-OUTPUT-FILE-HEADER ((STREAM OUTPUT-STREAM) (FILE FILE-NAME) (ENSUREPACKAGE? BOOLEAN)))", ((cpp_function_code)(&clOutputFileHeader)), NULL);
      defineFunctionObject("CL-OUTPUT-ENSURE-PACKAGE-DEFINITION", "(DEFUN CL-OUTPUT-ENSURE-PACKAGE-DEFINITION ((STREAM OUTPUT-STREAM) (PACKAGE STRING)))", ((cpp_function_code)(&clOutputEnsurePackageDefinition)), NULL);
      defineFunctionObject("CL-OUTPUT-IN-PACKAGE-DECLARATION", "(DEFUN CL-OUTPUT-IN-PACKAGE-DECLARATION ((STREAM OUTPUT-STREAM) (PACKAGE STRING)))", ((cpp_function_code)(&clOutputInPackageDeclaration)), NULL);
      defineFunctionObject("CL-OUTPUT-FORWARD-DECLARATIONS", "(DEFUN CL-OUTPUT-FORWARD-DECLARATIONS ((STREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&clOutputForwardDeclarations)), NULL);
      defineFunctionObject("CL-TRANSLATE-FILE", "(DEFUN CL-TRANSLATE-FILE ((FILE FILE-NAME) (RELATIVE? BOOLEAN)) :DOCUMENTATION \"Translate a Stella `file' to Common-Lisp.  If\n`relative?', concatenate root directory to `file'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&clTranslateFile)), NULL);
      defineFunctionObject("CL-TRANSLATE-WALKED-SYSTEM-UNITS", "(DEFUN CL-TRANSLATE-WALKED-SYSTEM-UNITS ((SYSTEMUNITS SYSTEM-UNITS-ALIST)))", ((cpp_function_code)(&clTranslateWalkedSystemUnits)), NULL);
      defineFunctionObject("SORT-CL-STRUCT-CLASSES", "(DEFUN (SORT-CL-STRUCT-CLASSES (LIST OF CLASS)) ((UNSORTEDCLASSES (LIST OF CLASS))))", ((cpp_function_code)(&sortClStructClasses)), NULL);
      defineFunctionObject("CL-YIELD-STRUCT-CLASS-FILE-NAME", "(DEFUN (CL-YIELD-STRUCT-CLASS-FILE-NAME FILE-NAME) ((SYSTEMNAME STRING)))", ((cpp_function_code)(&clYieldStructClassFileName)), NULL);
      defineFunctionObject("CL-OUTPUT-SYSTEM-CL-STRUCTS-FILE", "(DEFUN CL-OUTPUT-SYSTEM-CL-STRUCTS-FILE ((CLASSUNITS (LIST OF TRANSLATION-UNIT))))", ((cpp_function_code)(&clOutputSystemClStructsFile)), NULL);
      defineFunctionObject("CL-TRANSLATE-SYSTEM", "(DEFUN CL-TRANSLATE-SYSTEM ((SYSTEM-NAME STRING)) :DOCUMENTATION \"Translate a Stella system named `system-name' to Common Lisp.\" :PUBLIC? TRUE)", ((cpp_function_code)(&clTranslateSystem)), NULL);
      defineFunctionObject("CL-COMPILE-AND-LOAD-FILES", "(DEFUN (CL-COMPILE-AND-LOAD-FILES BOOLEAN) ((FILES (CONS OF STRING-WRAPPER)) (RELATIVE? BOOLEAN) (FORCERECOMPILATION? BOOLEAN)))", ((cpp_function_code)(&clCompileAndLoadFiles)), NULL);
      defineFunctionObject("CL-TRANSLATE-STELLA", "(DEFUN CL-TRANSLATE-STELLA ((PRODUCTIONSETTINGS? BOOLEAN)))", ((cpp_function_code)(&clTranslateStella)), NULL);
      defineFunctionObject("CL-RETRANSLATE-STELLA", "(DEFUN CL-RETRANSLATE-STELLA ((PRODUCTIONSETTINGS? BOOLEAN)))", ((cpp_function_code)(&clRetranslateStella)), NULL);
      defineFunctionObject("STARTUP-CL-TRANSLATE-FILE", "(DEFUN STARTUP-CL-TRANSLATE-FILE () :PUBLIC? TRUE)", ((cpp_function_code)(&startupClTranslateFile)), NULL);
      { MethodSlot* function = lookupFunction(SYM_CL_TRANSLATE_FILE_STELLA_STARTUP_CL_TRANSLATE_FILE);

        setDynamicSlotValue(function->dynamicSlots, SYM_CL_TRANSLATE_FILE_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupClTranslateFile"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("STELLA")))));
    }
  }
}

Keyword* KWD_CL_TRANSLATE_FILE_COMMON_LISP = NULL;

Symbol* SYM_CL_TRANSLATE_FILE_STELLA_GLOBAL_VARIABLE = NULL;

Surrogate* SGT_CL_TRANSLATE_FILE_STELLA_CONS = NULL;

Keyword* KWD_CL_TRANSLATE_FILE_LISP = NULL;

Keyword* KWD_CL_TRANSLATE_FILE_IF_NOT_EXISTS = NULL;

Keyword* KWD_CL_TRANSLATE_FILE_CREATE_PATH = NULL;

Keyword* KWD_CL_TRANSLATE_FILE_USE_COMMON_LISP_STRUCTS = NULL;

Keyword* KWD_CL_TRANSLATE_FILE_USE_COMMON_LISP_VECTOR_STRUCTS = NULL;

Symbol* SYM_CL_TRANSLATE_FILE_STELLA_CLASS = NULL;

Keyword* KWD_CL_TRANSLATE_FILE_STELLA = NULL;

Keyword* KWD_CL_TRANSLATE_FILE_FINALIZE = NULL;

Keyword* KWD_CL_TRANSLATE_FILE_TWO_PASSp = NULL;

Keyword* KWD_CL_TRANSLATE_FILE_FORCE_TRANSLATIONp = NULL;

Keyword* KWD_CL_TRANSLATE_FILE_PRODUCTION_SETTINGSp = NULL;

Keyword* KWD_CL_TRANSLATE_FILE_LISP_BINARY = NULL;

Symbol* SYM_CL_TRANSLATE_FILE_STELLA_STARTUP_CL_TRANSLATE_FILE = NULL;

Symbol* SYM_CL_TRANSLATE_FILE_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
