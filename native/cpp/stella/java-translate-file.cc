//  -*- Mode: C++ -*-

// java-translate-file.cc

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

// Holds the current Stella class being output in Java
DEFINE_STELLA_SPECIAL(oCURRENT_JAVA_OUTPUT_CLASSo, Class* , NULL);

void clt() {
  stringChangeModule("STELLA");
  setTranslatorOutputLanguage(KWD_JAVA_TRANSLATE_FILE_COMMON_LISP);
}

void jt() {
  stringChangeModule("STELLA");
  setTranslatorOutputLanguage(KWD_JAVA_TRANSLATE_FILE_JAVA);
}

void jptrans(Object* statement) {
  // Translate `statement' to C++ and print the result.
  { 
    BIND_STELLA_SPECIAL(oTRANSLATOROUTPUTLANGUAGEo, Keyword*, oTRANSLATOROUTPUTLANGUAGEo);
    BIND_STELLA_SPECIAL(oCURRENT_STREAMo, OutputStream*, STANDARD_OUTPUT);
    setTranslatorOutputLanguage(KWD_JAVA_TRANSLATE_FILE_JAVA);
    incrementallyTranslate(statement);
  }
}

const char* stringJavaMakeCodeOutputFileName(const char* barefile, boolean donttruncateP) {
  if (donttruncateP) {
    { 
      BIND_STELLA_SPECIAL(oDONTTRUNCATEFILENAMESpo, boolean, true);
      return (makeFileNameFromRelativePath(wrapString(barefile), KWD_JAVA_TRANSLATE_FILE_JAVA));
    }
  }
  else {
    return (makeFileNameFromRelativePath(wrapString(barefile), KWD_JAVA_TRANSLATE_FILE_JAVA));
  }
}

const char* Class::javaMakeCodeOutputFileName(boolean donttruncateP) {
  { Class* source = this;

    { StringWrapper* barefile = javaTranslateClassNamestring(wrapString(className(source)));

      return (stringJavaMakeCodeOutputFileName(barefile->wrapperValue, donttruncateP));
    }
  }
}

const char* javaMakeGlobalOutputFileName(Module* module, boolean donttruncateP) {
  return (stringJavaMakeCodeOutputFileName(javaYieldFlotsamClassName(module), donttruncateP));
}

void javaOutputFlotsamUnitsToFile(HashTable* globalsht, HashTable* functionht, Cons* codemodulelist) {
  { Cons* functions = NIL;
    Cons* globals = NIL;
    const char* filename = NULL;
    Cons* flotsamFiles = NIL;

    { Module* module = NULL;
      Cons* iter000 = codemodulelist;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        module = ((Module*)(iter000->value));
        { 
          BIND_STELLA_SPECIAL(oMODULEo, Module*, module);
          BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
          filename = javaMakeGlobalOutputFileName(module, false);
          if (flotsamFiles->memberP(wrapString(filename))) {
            *(STANDARD_WARNING->nativeStream) << "Warning: " << "Overwriting Flotsam file " << "`" << filename << "'" << ".  This is surely bad." << std::endl;
          }
          flotsamFiles = cons(wrapString(filename), flotsamFiles);
          globals = ((Cons*)(globalsht->lookup(module)));
          if (!(((boolean)(globals)))) {
            globals = NIL;
          }
          functions = ((Cons*)(functionht->lookup(module)));
          if (!(((boolean)(functions)))) {
            functions = NIL;
          }
          javaOutputFlotsamUnitsToFileForModule(filename, module, NULL, globals, functions);
        }
      }
    }
  }
}

void javaOutputFlotsamUnitsToFileForModule(const char* classoutputfile, Module* module, TranslationUnit* classunit, Cons* globals, Cons* functions) {
  { 
    BIND_STELLA_SPECIAL(oCURRENT_JAVA_OUTPUT_CLASSo, Class*, NULL);
    { Cons* translation = NIL;
      Class* clasS = NULL;
      Cons* classtranslation = NIL;

      { 
        BIND_STELLA_SPECIAL(oMODULEo, Module*, module);
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
        { OutputFileStream* classoutputstream = NULL;

          try {
            classoutputstream = openOutputFile(classoutputfile, 2, KWD_JAVA_TRANSLATE_FILE_IF_NOT_EXISTS, KWD_JAVA_TRANSLATE_FILE_CREATE_PATH);
            if (((boolean)(classunit))) {
              oCURRENT_JAVA_OUTPUT_CLASSo = ((Class*)(classunit->theObject));
              std::cout << "Translating " << "`" << clasS << "'" << "..." << std::endl;
              classtranslation = javaTranslateDefineNativeClass(oCURRENT_JAVA_OUTPUT_CLASSo)->rest;
            }
            { 
              BIND_STELLA_SPECIAL(oCURRENT_STREAMo, OutputStream*, classoutputstream);
              if (oTRANSLATIONVERBOSITYLEVELo >= 1) {
                if (((boolean)(classunit))) {
                  std::cout << "    Writing " << "`" << classoutputfile << "'" << " ..." << std::endl;
                }
                else {
                  std::cout << "Writing " << "`" << classoutputfile << "'" << "..." << std::endl;
                }
              }
              javaOutputFileHeader(classoutputstream, javaMakeGlobalOutputFileName(module, true));
              if (((boolean)(classunit))) {
                javaOutputClassDeclaration(classtranslation);
              }
              else {
                *(oCURRENT_STREAMo->nativeStream) << "public class " << javaYieldFlotsamClassName(module) << " ";
              }
              *(oCURRENT_STREAMo->nativeStream) << "{" << std::endl;
              javaBumpIndent();
              if (((boolean)(classunit))) {
                javaOutputClassVariableDefinitions(((Cons*)(classtranslation->nth(6))));
              }
              { TranslationUnit* global = NULL;
                Cons* iter000 = globals;

                for (; !(iter000 == NIL); iter000 = iter000->rest) {
                  global = ((TranslationUnit*)(iter000->value));
                  translation = javaTranslateUnit(global);
                  javaOutputGlobalDefinition(translation->rest);
                  global->translation = NULL;
                  global->codeRegister = NULL;
                }
              }
              if (((boolean)(classunit))) {
                javaOutputClassConstructors(((Cons*)(classtranslation->nth(7))), javaYieldFlotsamClassName(module), ((boolean)(oCURRENT_JAVA_OUTPUT_CLASSo)) &&
                    exceptionClassP(oCURRENT_JAVA_OUTPUT_CLASSo));
                { TranslationUnit* statement = NULL;
                  Cons* iter001 = ((Cons*)(classtranslation->nth(8)));

                  for (; !(iter001 == NIL); iter001 = iter001->rest) {
                    statement = ((TranslationUnit*)(iter001->value));
                    javaOutputStatement(javaTranslateUnit(statement));
                    statement->translation = NULL;
                    statement->codeRegister = NULL;
                  }
                }
              }
              { TranslationUnit* function = NULL;
                Cons* iter002 = functions;

                for (; !(iter002 == NIL); iter002 = iter002->rest) {
                  function = ((TranslationUnit*)(iter002->value));
                  javaOutputMethod(javaTranslateUnit(function)->rest);
                  function->translation = NULL;
                  function->codeRegister = NULL;
                }
              }
              javaUnbumpIndent();
              *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
            }
          }
catch (...) {
            if (((boolean)(classoutputstream))) {
              classoutputstream->free();
            }
            throw;
          }
          if (((boolean)(classoutputstream))) {
            classoutputstream->free();
          }
        }
      }
    }
  }
}

void javaOutputFileHeader(OutputStream* stream, const char* filename) {
  *(stream->nativeStream) << "//  -*- Mode: Java -*-" << std::endl << "//" << std::endl;
  if (filename != NULL) {
    *(stream->nativeStream) << "// " << fileNameWithoutDirectory(filename) << std::endl << std::endl;
  }
  { const char* packageName = javaPackagePrefix(oMODULEo, ".");
    Cons* importedPackages = NIL;
    const char* name = NULL;

    outputCopyrightHeader(stream);
    if (!((packageName == NULL) ||
        stringEqlP(packageName, ""))) {
      packageName = stringSubsequence(packageName, 0, strlen(packageName) - 1);
      *(stream->nativeStream) << "package " << packageName << ";" << std::endl << std::endl;
    }
    if (oMODULEo == oSTELLA_MODULEo) {
      *(stream->nativeStream) << "import " << javaStellaPackage() << ".javalib.*;" << std::endl;
    }
    else {
      {
        if ((!((boolean)(stringGetStellaClass("NATIVE", false)))) &&
            (!inheritedClassNameConflictsP("NATIVE"))) {
          *(stream->nativeStream) << "import " << javaStellaPackage() << ".javalib.Native;" << std::endl;
        }
        if ((!((boolean)(stringGetStellaClass("STELLA-SPECIAL-VARIABLE", false)))) &&
            (!inheritedClassNameConflictsP("STELLA-SPECIAL-VARIABLE"))) {
          *(stream->nativeStream) << "import " << javaStellaPackage() << ".javalib.StellaSpecialVariable;" << std::endl;
        }
      }
    }
    if (oCURRENT_STELLA_FEATURESo->membP(KWD_JAVA_TRANSLATE_FILE_MINIMIZE_JAVA_PREFIXES)) {
      { Module* module = NULL;
        Cons* iter000 = oMODULEo->uses->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          module = ((Module*)(iter000->value));
          name = javaPackagePrefix(module, ".");
          if (!(stringEqlP(name, packageName) ||
              importedPackages->memberP(wrapString(name)))) {
            *(stream->nativeStream) << "import " << name << "*;" << std::endl;
            importedPackages = cons(wrapString(name), importedPackages);
          }
        }
      }
      { Context* module = NULL;
        Cons* iter001 = oMODULEo->allSuperContexts;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          module = ((Context*)(iter001->value));
          name = javaPackagePrefix(((Module*)(module)), ".");
          if (!(stringEqlP(name, packageName) ||
              importedPackages->memberP(wrapString(name)))) {
            *(stream->nativeStream) << "import " << name << "*;" << std::endl;
            importedPackages = cons(wrapString(name), importedPackages);
          }
        }
      }
    }
    *(stream->nativeStream) << std::endl;
  }
}

void javaOutputClassToFile(Class* clasS) {
  { 
    BIND_STELLA_SPECIAL(oCURRENT_JAVA_OUTPUT_CLASSo, Class*, clasS);
    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, clasS->homeModule());
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
      { const char* classoutputfile = clasS->javaMakeCodeOutputFileName(false);
        Cons* translation = NIL;

        { OutputFileStream* classoutputstream = NULL;

          try {
            classoutputstream = openOutputFile(classoutputfile, 2, KWD_JAVA_TRANSLATE_FILE_IF_NOT_EXISTS, KWD_JAVA_TRANSLATE_FILE_CREATE_PATH);
            { 
              BIND_STELLA_SPECIAL(oCURRENT_STREAMo, OutputStream*, classoutputstream);
              std::cout << "Translating " << "`" << clasS << "'" << "..." << std::endl;
              translation = javaTranslateDefineNativeClass(clasS);
              if (oTRANSLATIONVERBOSITYLEVELo >= 1) {
                std::cout << "    Writing " << "`" << classoutputfile << "'" << "..." << std::endl;
              }
              javaOutputFileHeader(classoutputstream, clasS->javaMakeCodeOutputFileName(true));
              javaOutputClass(translation->rest, exceptionClassP(clasS));
            }
          }
catch (...) {
            if (((boolean)(classoutputstream))) {
              classoutputstream->free();
            }
            throw;
          }
          if (((boolean)(classoutputstream))) {
            classoutputstream->free();
          }
        }
      }
    }
  }
}

void javaOutputClassUnitToFile(TranslationUnit* classunit) {
  javaOutputClassToFile(((Class*)(classunit->theObject)));
}

boolean javaFlotsamFunctionP(MethodSlot* method) {
  return ((!((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD_CONSTRUCTORp, FALSE_WRAPPER)))->wrapperValue) &&
      ((!((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD_NATIVEp, FALSE_WRAPPER)))->wrapperValue) &&
       ((!method->methodStartupFunctionP()) &&
        (zeroArgumentFunctionP(method) ||
         (javaMethodObjectDefinedOnNativeTypeP(method) ||
          javaFunctionInDifferentModuleP(method))))));
}

void javaOutputStartupUnitsToFile(StringHashTable* startupht, Cons* keylist) {
  { const char* classoutputfile = NULL;
    Cons* startupfunctions = NULL;

    { 
      BIND_STELLA_SPECIAL(oCURRENT_STREAMo, OutputStream*, NULL);
      { StringWrapper* classname = NULL;
        Cons* iter000 = keylist;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          classname = ((StringWrapper*)(iter000->value));
          startupfunctions = ((Cons*)(startupht->lookup(classname->wrapperValue)));
          if (((boolean)(startupfunctions)) &&
              (!(!((boolean)(startupfunctions))))) {
            { 
              BIND_STELLA_SPECIAL(oMODULEo, Module*, ((TranslationUnit*)(startupfunctions->value))->homeModule());
              BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
              classoutputfile = stringJavaMakeCodeOutputFileName(classname->wrapperValue, false);
              { OutputFileStream* classoutputstream = NULL;

                try {
                  classoutputstream = openOutputFile(classoutputfile, 2, KWD_JAVA_TRANSLATE_FILE_IF_NOT_EXISTS, KWD_JAVA_TRANSLATE_FILE_CREATE_PATH);
                  oCURRENT_STREAMo = classoutputstream;
                  if (oTRANSLATIONVERBOSITYLEVELo >= 1) {
                    std::cout << "Writing " << "`" << classoutputfile << "'" << "..." << std::endl;
                  }
                  javaOutputFileHeader(classoutputstream, stringJavaMakeCodeOutputFileName(classname->wrapperValue, true));
                  *(oCURRENT_STREAMo->nativeStream) << "public class " << classname->wrapperValue << " {" << std::endl;
                  javaBumpIndent();
                  { TranslationUnit* function = NULL;
                    Cons* iter001 = startupfunctions;

                    for (; !(iter001 == NIL); iter001 = iter001->rest) {
                      function = ((TranslationUnit*)(iter001->value));
                      javaOutputMethod(javaTranslateUnit(function)->rest);
                      function->translation = NULL;
                      function->codeRegister = NULL;
                    }
                  }
                  javaUnbumpIndent();
                  *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
                }
catch (...) {
                  if (((boolean)(classoutputstream))) {
                    classoutputstream->free();
                  }
                  throw;
                }
                if (((boolean)(classoutputstream))) {
                  classoutputstream->free();
                }
              }
            }
          }
        }
      }
    }
  }
}

void javaPushIntoHashTable(HashTable* ht, Object* key, Object* object) {
  { Cons* value = ((Cons*)(ht->lookup(key)));

    if (((boolean)(value))) {
      ht->insertAt(key, cons(object, value));
    }
    else {
      ht->insertAt(key, cons(object, NIL));
    }
  }
}

void javaPushIntoStringHashTable(StringHashTable* ht, const char* key, Object* object) {
  { Cons* value = ((Cons*)(ht->lookup(key)));

    if (((boolean)(value))) {
      ht->insertAt(key, cons(object, value));
    }
    else {
      ht->insertAt(key, cons(object, NIL));
    }
  }
}

boolean javaClassUnitDefinesFlotsamClassP(TranslationUnit* classunit) {
  { Class* clasS = ((Class*)(classunit->theObject));
    Module* module = classunit->homeModule();

    return (stringEqlP(javaTranslateClassNamestring(wrapString(internSymbolInModule(clasS->classType->symbolName, ((Module*)(clasS->classType->homeContext)), false)->symbolName))->wrapperValue, javaYieldFlotsamClassName(module)));
  }
}

void javaOutputAllUnitsToFile() {
  { StringWrapper* startupclassname = NULL;
    StringHashTable* startupht = newStringHashTable();
    Cons* startupclasslist = NIL;
    Cons* methods = NIL;
    HashTable* flotsamfunctionht = newHashTable();
    HashTable* globalsht = newHashTable();
    List* codemoduleslist = list(0);
    Cons* verbatimstatements = NIL;
    Cons* classes = NIL;
    Module* codeoutputmodule = NULL;

    oJAVA_STELLA_PACKAGE_MAPPINGo->insertAt(wrapString("STELLAROOT"), wrapString(javaStellaPackage()));
    oTRANSLATIONUNITSo = oTRANSLATIONUNITSo->reverse();
    { TranslationUnit* unit = NULL;
      Cons* iter000 = oTRANSLATIONUNITSo->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        unit = ((TranslationUnit*)(iter000->value));
        { Symbol* testValue000 = unit->category;

          if ((testValue000 == SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD) ||
              (testValue000 == SYM_JAVA_TRANSLATE_FILE_STELLA_MACRO)) {
            if (javaFlotsamFunctionP(((MethodSlot*)(unit->theObject)))) {
              codeoutputmodule = unit->theObject->homeModule();
              javaPushIntoHashTable(flotsamfunctionht, codeoutputmodule, unit);
              codemoduleslist->insertNew(codeoutputmodule);
            }
            else if (((MethodSlot*)(unit->theObject))->methodStartupFunctionP()) {
              startupclassname = javaTranslateClassNamestring(wrapString(((StringWrapper*)(dynamicSlotValue(((MethodSlot*)(unit->theObject))->dynamicSlots, SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD_STARTUP_CLASSNAME, NULL_STRING_WRAPPER)))->wrapperValue));
              javaPushIntoStringHashTable(startupht, startupclassname->wrapperValue, unit);
              if (!(startupclasslist->memberP(startupclassname))) {
                startupclasslist = cons(startupclassname, startupclasslist);
              }
            }
            else {
              methods = cons(unit, methods);
            }
          }
          else if (testValue000 == SYM_JAVA_TRANSLATE_FILE_STELLA_PRINT_METHOD) {
            methods = cons(unit, methods);
          }
          else if (testValue000 == SYM_JAVA_TRANSLATE_FILE_STELLA_TYPE) {
          }
          else if (testValue000 == SYM_JAVA_TRANSLATE_FILE_STELLA_VERBATIM) {
            verbatimstatements = cons(unit, verbatimstatements);
          }
          else if (testValue000 == SYM_JAVA_TRANSLATE_FILE_STELLA_CLASS) {
            classes = cons(unit, classes);
          }
          else if (testValue000 == SYM_JAVA_TRANSLATE_FILE_STELLA_GLOBAL_VARIABLE) {
            codeoutputmodule = unit->theObject->homeModule();
            javaPushIntoHashTable(globalsht, codeoutputmodule, unit);
            codemoduleslist->insertNew(codeoutputmodule);
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
    { TranslationUnit* classunit = NULL;
      Cons* iter001 = classes;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        classunit = ((TranslationUnit*)(iter001->value));
        if (javaClassUnitDefinesFlotsamClassP(classunit)) {
          { Module* module = classunit->theObject->homeModule();
            Cons* globals = NIL;
            Cons* functions = NIL;

            { 
              BIND_STELLA_SPECIAL(oMODULEo, Module*, module);
              BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
              globals = ((Cons*)(globalsht->lookup(module)));
              if (!(((boolean)(globals)))) {
                globals = NIL;
              }
              functions = ((Cons*)(flotsamfunctionht->lookup(module)));
              if (!(((boolean)(functions)))) {
                functions = NIL;
              }
              javaOutputFlotsamUnitsToFileForModule(javaMakeGlobalOutputFileName(module, false), module, classunit, globals, functions);
              codemoduleslist->remove(module);
            }
          }
        }
        else {
          javaOutputClassUnitToFile(classunit);
        }
      }
    }
    javaOutputFlotsamUnitsToFile(globalsht, flotsamfunctionht, codemoduleslist->theConsList);
    javaOutputStartupUnitsToFile(startupht, startupclasslist);
  }
}

void javaInitializeFileTranslation() {
  oJAVA_INDENT_CHARSo = 0;
}

void javaTranslateFile(const char* filename) {
  translateFile(filename, KWD_JAVA_TRANSLATE_FILE_JAVA, false);
}

void javaTranslateFileAsPartOfSystem(const char* filename) {
  translateFile(filename, KWD_JAVA_TRANSLATE_FILE_JAVA, true);
}

void javaTranslateWalkedSystemUnits(KeyValueList* systemunits) {
  { 
    BIND_STELLA_SPECIAL(oTRANSLATIONUNITSo, List*, concatenateSystemUnits(systemunits));
    if (oTRANSLATIONVERBOSITYLEVELo >= 1) {
      std::cout << "Generating Java translations..." << std::endl;
    }
    javaOutputAllUnitsToFile();
    cleanUpTranslationUnitsSpecial();
    javaOutputSystemSpecificFiles();
  }
}

void javaOutputSystemSpecificFiles() {
  if (oJAVA_BUILD_METHODo == KWD_JAVA_TRANSLATE_FILE_MAVEN) {
    javaOutputSystemMavenFiles();
  }
  else {
  }
}

void javaTranslateSystem(const char* systemname) {
  // Translate the system `systemName' to Java.
  translateSystem(systemname, consList(7, KWD_JAVA_TRANSLATE_FILE_JAVA, KWD_JAVA_TRANSLATE_FILE_TWO_PASSp, TRUE_WRAPPER, KWD_JAVA_TRANSLATE_FILE_FORCE_TRANSLATIONp, TRUE_WRAPPER, KWD_JAVA_TRANSLATE_FILE_PRODUCTION_SETTINGSp, TRUE_WRAPPER));
}

// Indicates how JAVA translations of STELLA systems will be compiled and built.
// Controls the native java directory structure as well as generation of build files such as pom.xml.
// Currently supported methods are :JAVAC (the original) and :MAVEN.
Keyword* oJAVA_BUILD_METHODo = NULL;

const char* javaGetSystemMavenTemplateFile() {
  { const char* pomfile = makeFileName("pom", KWD_JAVA_TRANSLATE_FILE_STELLA, true);
    const char* templatefile = stringConcatenate(fileNameWithoutExtension(pomfile), ".xml.in", 0);

    if (!(probeFileP(templatefile))) {
      { 
        BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONo, SystemDefinition*, getSystemDefinition("STELLA", true));
        BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo, const char*, oCURRENTSYSTEMDEFINITIONo->directory);
        {
          pomfile = makeFileName("pom", KWD_JAVA_TRANSLATE_FILE_STELLA, true);
          templatefile = stringConcatenate(fileNameWithoutExtension(pomfile), ".xml-default.in", 0);
        }
      }
    }
    return (templatefile);
  }
}

const char* javaGetSystemParentMavenTemplateFile() {
  { const char* pomfile = makeFileName("pom", KWD_JAVA_TRANSLATE_FILE_STELLA, true);
    const char* templatefile = stringConcatenate(fileNameWithoutExtension(pomfile), ".xml.parent.in", 0);

    if (!(probeFileP(templatefile))) {
      { 
        BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONo, SystemDefinition*, getSystemDefinition("STELLA", true));
        BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo, const char*, oCURRENTSYSTEMDEFINITIONo->directory);
        {
          pomfile = makeFileName("pom", KWD_JAVA_TRANSLATE_FILE_STELLA, true);
          templatefile = stringConcatenate(fileNameWithoutExtension(pomfile), ".xml.parent-default.in", 0);
        }
      }
    }
    return (templatefile);
  }
}

const char* SystemDefinition::systemGroupName_reader() {
  { SystemDefinition* self = this;

    { const char* answer = ((StringWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_JAVA_TRANSLATE_FILE_STELLA_SYSTEM_GROUP_NAME, NULL_STRING_WRAPPER)))->wrapperValue;

      if (answer == NULL) {
        return ("edu.isi.loom.stella");
      }
      else {
        return (answer);
      }
    }
  }
}

const char* javaYieldSystemGroupName(SystemDefinition* system) {
  if (system->systemGroupName_reader() != NULL) {
    return (system->systemGroupName_reader());
  }
  else {
    { const char* defaultgroupname = javaPackagePrefix(getStellaModule(system->cardinalModule, true), ".");
      int pos = 0;

      defaultgroupname = stringSubsequence(defaultgroupname, 0, strlen(defaultgroupname) - 1);
      pos = stringLastPosition(defaultgroupname, '.', NULL_INTEGER);
      if (pos != NULL_INTEGER) {
        defaultgroupname = stringSubsequence(defaultgroupname, 0, pos);
      }
      return (defaultgroupname);
    }
  }
}

const char* javaYieldSystemVersion(SystemDefinition* system) {
  return (getSystemVersionString(system));
}

const char* javaYieldSystemParentName(SystemDefinition* system) {
  system = system;
  { const char* parentname = fileNameWithoutDirectory(directoryFileName(directoryParentDirectory(rootNativeDirectory(), 1)));

    if (blankStringP(parentname)) {
      parentname = "stella";
    }
    return (stringConcatenate(parentname, "-parent-system", 0));
  }
}

void substituteTemplateVariablesToMavenFile(const char* templatefile, const char* outputfile, KeyValueList* variables) {
  { InputFileStream* in = NULL;

    try {
      in = openInputFile(templatefile, 0);
      { OutputFileStream* out = NULL;

        try {
          out = openOutputFile(outputfile, 2, KWD_JAVA_TRANSLATE_FILE_IF_NOT_EXISTS, KWD_JAVA_TRANSLATE_FILE_CREATE_PATH);
          substituteTemplateVariablesToStream(in, out, variables);
        }
catch (...) {
          if (((boolean)(out))) {
            out->free();
          }
          throw;
        }
        if (((boolean)(out))) {
          out->free();
        }
      }
    }
catch (...) {
      if (((boolean)(in))) {
        in->free();
      }
      throw;
    }
    if (((boolean)(in))) {
      in->free();
    }
  }
}

void javaOutputSystemMavenFiles() {
  { SystemDefinition* system = oCURRENTSYSTEMDEFINITIONo;
    const char* templatefile = javaGetSystemMavenTemplateFile();
    const char* parenttemplatefile = javaGetSystemParentMavenTemplateFile();
    KeyValueList* variables = newKeyValueList();
    OutputStringStream* requiredsystems = newOutputStringStream();
    OutputStringStream* childsystems = newOutputStringStream();
    const char* nativeroot = rootNativeDirectory();
    const char* languagesubdir = getLanguageSubdirectoryFromFileType(KWD_JAVA_TRANSLATE_FILE_JAVA);
    const char* languagedirectory = concatenateFileNames(nativeroot, 1, languagesubdir);
    const char* systemsubdir = getSystemSubdirectoryFromFileType(KWD_JAVA_TRANSLATE_FILE_JAVA);
    const char* pomfile = concatenateFileNames(languagedirectory, 2, systemsubdir, "pom.xml");
    const char* parentpomfile = concatenateFileNames(languagedirectory, 1, "pom.xml");
    boolean firstlineP = true;

    variables->insertAt(wrapString("SYSTEM-NAME"), wrapString(system->name));
    variables->insertAt(wrapString("SYSTEM-GROUP-NAME"), wrapString(javaYieldSystemGroupName(system)));
    variables->insertAt(wrapString("SYSTEM-VERSION"), wrapString(javaYieldSystemVersion(system)));
    variables->insertAt(wrapString("SYSTEM-PARENT-NAME"), wrapString(javaYieldSystemParentName(system)));
    variables->insertAt(wrapString("SYSTEM-PARENT-GROUP-NAME"), wrapString("stella-parent-systems"));
    variables->insertAt(wrapString("SYSTEM-PARENT-VERSION"), wrapString(dateToVersionString(makeCurrentDateTime(), KWD_JAVA_TRANSLATE_FILE_MINUTES)));
    if (((boolean)(system->requiredSystems))) {
      firstlineP = true;
      { StringWrapper* reqsys = NULL;
        Cons* iter000 = system->requiredSystems;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          reqsys = ((StringWrapper*)(iter000->value));
          system = getSystemDefinition(reqsys->wrapperValue, true);
          if (!(firstlineP)) {
            *(requiredsystems->nativeStream) << std::endl << "    ";
          }
          *(requiredsystems->nativeStream) << "<dependency>" << std::endl;
          *(requiredsystems->nativeStream) << "      <groupId>" << javaYieldSystemGroupName(system) << "</groupId>" << std::endl;
          *(requiredsystems->nativeStream) << "      <artifactId>" << system->name << "</artifactId>" << std::endl;
          *(requiredsystems->nativeStream) << "      <version>" << "[0,10000]" << "</version>" << std::endl;
          *(requiredsystems->nativeStream) << "    </dependency>";
          firstlineP = false;
        }
      }
    }
    variables->insertAt(wrapString("REQUIRED-SYSTEMS"), wrapString(requiredsystems->theStringReader()));
    substituteTemplateVariablesToMavenFile(templatefile, pomfile, variables);
    firstlineP = true;
    { StringWrapper* dir = NULL;
      Cons* iter001 = listDirectoryFiles(languagedirectory);

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        dir = ((StringWrapper*)(iter001->value));
        if (probeFileP(concatenateFileNames(languagedirectory, 2, dir->wrapperValue, "pom.xml"))) {
          if (!(firstlineP)) {
            *(childsystems->nativeStream) << std::endl << "    ";
          }
          *(childsystems->nativeStream) << "<module>" << unwrapString(dir) << "</module>";
          firstlineP = false;
        }
      }
    }
    variables->insertAt(wrapString("CHILD-SYSTEMS"), wrapString(childsystems->theStringReader()));
    substituteTemplateVariablesToMavenFile(parenttemplatefile, parentpomfile, variables);
  }
}

void helpStartupJavaTranslateFile1() {
  {
    KWD_JAVA_TRANSLATE_FILE_COMMON_LISP = ((Keyword*)(internRigidSymbolWrtModule("COMMON-LISP", NULL, 2)));
    KWD_JAVA_TRANSLATE_FILE_JAVA = ((Keyword*)(internRigidSymbolWrtModule("JAVA", NULL, 2)));
    KWD_JAVA_TRANSLATE_FILE_IF_NOT_EXISTS = ((Keyword*)(internRigidSymbolWrtModule("IF-NOT-EXISTS", NULL, 2)));
    KWD_JAVA_TRANSLATE_FILE_CREATE_PATH = ((Keyword*)(internRigidSymbolWrtModule("CREATE-PATH", NULL, 2)));
    KWD_JAVA_TRANSLATE_FILE_MINIMIZE_JAVA_PREFIXES = ((Keyword*)(internRigidSymbolWrtModule("MINIMIZE-JAVA-PREFIXES", NULL, 2)));
    SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD_CONSTRUCTORp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-CONSTRUCTOR?", NULL, 0)));
    SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD_NATIVEp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-NATIVE?", NULL, 0)));
    SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD = ((Symbol*)(internRigidSymbolWrtModule("METHOD", NULL, 0)));
    SYM_JAVA_TRANSLATE_FILE_STELLA_MACRO = ((Symbol*)(internRigidSymbolWrtModule("MACRO", NULL, 0)));
    SYM_JAVA_TRANSLATE_FILE_STELLA_PRINT_METHOD = ((Symbol*)(internRigidSymbolWrtModule("PRINT-METHOD", NULL, 0)));
    SYM_JAVA_TRANSLATE_FILE_STELLA_TYPE = ((Symbol*)(internRigidSymbolWrtModule("TYPE", NULL, 0)));
    SYM_JAVA_TRANSLATE_FILE_STELLA_VERBATIM = ((Symbol*)(internRigidSymbolWrtModule("VERBATIM", NULL, 0)));
    SYM_JAVA_TRANSLATE_FILE_STELLA_CLASS = ((Symbol*)(internRigidSymbolWrtModule("CLASS", NULL, 0)));
    SYM_JAVA_TRANSLATE_FILE_STELLA_GLOBAL_VARIABLE = ((Symbol*)(internRigidSymbolWrtModule("GLOBAL-VARIABLE", NULL, 0)));
    SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    KWD_JAVA_TRANSLATE_FILE_MAVEN = ((Keyword*)(internRigidSymbolWrtModule("MAVEN", NULL, 2)));
    KWD_JAVA_TRANSLATE_FILE_TWO_PASSp = ((Keyword*)(internRigidSymbolWrtModule("TWO-PASS?", NULL, 2)));
    KWD_JAVA_TRANSLATE_FILE_FORCE_TRANSLATIONp = ((Keyword*)(internRigidSymbolWrtModule("FORCE-TRANSLATION?", NULL, 2)));
    KWD_JAVA_TRANSLATE_FILE_PRODUCTION_SETTINGSp = ((Keyword*)(internRigidSymbolWrtModule("PRODUCTION-SETTINGS?", NULL, 2)));
    KWD_JAVA_TRANSLATE_FILE_STELLA = ((Keyword*)(internRigidSymbolWrtModule("STELLA", NULL, 2)));
    SYM_JAVA_TRANSLATE_FILE_STELLA_SYSTEM_GROUP_NAME = ((Symbol*)(internRigidSymbolWrtModule("SYSTEM-GROUP-NAME", NULL, 0)));
    KWD_JAVA_TRANSLATE_FILE_MINUTES = ((Keyword*)(internRigidSymbolWrtModule("MINUTES", NULL, 2)));
    SYM_JAVA_TRANSLATE_FILE_STELLA_STARTUP_JAVA_TRANSLATE_FILE = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-JAVA-TRANSLATE-FILE", NULL, 0)));
  }
}

void startupJavaTranslateFile() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupJavaTranslateFile1();
    }
    if (currentStartupTimePhaseP(4)) {
      oJAVA_BUILD_METHODo = KWD_JAVA_TRANSLATE_FILE_MAVEN;
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("CLT", "(DEFUN CLT ())", ((cpp_function_code)(&clt)), NULL);
      defineFunctionObject("JT", "(DEFUN JT ())", ((cpp_function_code)(&jt)), NULL);
      defineFunctionObject("JPTRANS", "(DEFUN JPTRANS ((STATEMENT OBJECT)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Translate `statement' to C++ and print the result.\")", ((cpp_function_code)(&jptrans)), NULL);
      defineMethodObject("(DEFMETHOD (JAVA-MAKE-CODE-OUTPUT-FILE-NAME FILE-NAME) ((BAREFILE FILE-NAME) (DONTTRUNCATE? BOOLEAN)))", wrapFunctionCode(((cpp_function_code)(((const char*  (*) (const char*, boolean))(&stringJavaMakeCodeOutputFileName))))), NULL);
      defineMethodObject("(DEFMETHOD (JAVA-MAKE-CODE-OUTPUT-FILE-NAME FILE-NAME) ((SOURCE CLASS) (DONTTRUNCATE? BOOLEAN)))", wrapMethodCode(((cpp_method_code)(&Class::javaMakeCodeOutputFileName))), NULL);
      defineFunctionObject("JAVA-MAKE-GLOBAL-OUTPUT-FILE-NAME", "(DEFUN (JAVA-MAKE-GLOBAL-OUTPUT-FILE-NAME FILE-NAME) ((MODULE MODULE) (DONTTRUNCATE? BOOLEAN)))", ((cpp_function_code)(&javaMakeGlobalOutputFileName)), NULL);
      defineFunctionObject("JAVA-OUTPUT-FLOTSAM-UNITS-TO-FILE", "(DEFUN JAVA-OUTPUT-FLOTSAM-UNITS-TO-FILE ((GLOBALSHT HASH-TABLE) (FUNCTIONHT HASH-TABLE) (CODEMODULELIST (CONS OF MODULE))))", ((cpp_function_code)(&javaOutputFlotsamUnitsToFile)), NULL);
      defineFunctionObject("JAVA-OUTPUT-FLOTSAM-UNITS-TO-FILE-FOR-MODULE", "(DEFUN JAVA-OUTPUT-FLOTSAM-UNITS-TO-FILE-FOR-MODULE ((CLASSOUTPUTFILE FILE-NAME) (MODULE MODULE) (CLASSUNIT TRANSLATION-UNIT) (GLOBALS (CONS OF TRANSLATION-UNIT)) (FUNCTIONS (CONS OF TRANSLATION-UNIT))))", ((cpp_function_code)(&javaOutputFlotsamUnitsToFileForModule)), NULL);
      defineFunctionObject("JAVA-OUTPUT-FILE-HEADER", "(DEFUN JAVA-OUTPUT-FILE-HEADER ((STREAM OUTPUT-STREAM) (FILENAME FILE-NAME)))", ((cpp_function_code)(&javaOutputFileHeader)), NULL);
      defineFunctionObject("JAVA-OUTPUT-CLASS-TO-FILE", "(DEFUN JAVA-OUTPUT-CLASS-TO-FILE ((CLASS CLASS)))", ((cpp_function_code)(&javaOutputClassToFile)), NULL);
      defineFunctionObject("JAVA-OUTPUT-CLASS-UNIT-TO-FILE", "(DEFUN JAVA-OUTPUT-CLASS-UNIT-TO-FILE ((CLASSUNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&javaOutputClassUnitToFile)), NULL);
      defineFunctionObject("JAVA-FLOTSAM-FUNCTION?", "(DEFUN (JAVA-FLOTSAM-FUNCTION? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&javaFlotsamFunctionP)), NULL);
      defineFunctionObject("JAVA-OUTPUT-STARTUP-UNITS-TO-FILE", "(DEFUN JAVA-OUTPUT-STARTUP-UNITS-TO-FILE ((STARTUPHT STRING-HASH-TABLE) (KEYLIST (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&javaOutputStartupUnitsToFile)), NULL);
      defineFunctionObject("JAVA-PUSH-INTO-HASH-TABLE", "(DEFUN JAVA-PUSH-INTO-HASH-TABLE ((HT HASH-TABLE) (KEY OBJECT) (OBJECT OBJECT)))", ((cpp_function_code)(&javaPushIntoHashTable)), NULL);
      defineFunctionObject("JAVA-PUSH-INTO-STRING-HASH-TABLE", "(DEFUN JAVA-PUSH-INTO-STRING-HASH-TABLE ((HT STRING-HASH-TABLE) (KEY STRING) (OBJECT OBJECT)))", ((cpp_function_code)(&javaPushIntoStringHashTable)), NULL);
      defineFunctionObject("JAVA-CLASS-UNIT-DEFINES-FLOTSAM-CLASS?", "(DEFUN (JAVA-CLASS-UNIT-DEFINES-FLOTSAM-CLASS? BOOLEAN) ((CLASSUNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&javaClassUnitDefinesFlotsamClassP)), NULL);
      defineFunctionObject("JAVA-OUTPUT-ALL-UNITS-TO-FILE", "(DEFUN JAVA-OUTPUT-ALL-UNITS-TO-FILE ())", ((cpp_function_code)(&javaOutputAllUnitsToFile)), NULL);
      defineFunctionObject("JAVA-INITIALIZE-FILE-TRANSLATION", "(DEFUN JAVA-INITIALIZE-FILE-TRANSLATION ())", ((cpp_function_code)(&javaInitializeFileTranslation)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-FILE", "(DEFUN JAVA-TRANSLATE-FILE ((FILENAME FILE-NAME)) :PUBLIC? TRUE)", ((cpp_function_code)(&javaTranslateFile)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-FILE-AS-PART-OF-SYSTEM", "(DEFUN JAVA-TRANSLATE-FILE-AS-PART-OF-SYSTEM ((FILENAME FILE-NAME)))", ((cpp_function_code)(&javaTranslateFileAsPartOfSystem)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-WALKED-SYSTEM-UNITS", "(DEFUN JAVA-TRANSLATE-WALKED-SYSTEM-UNITS ((SYSTEMUNITS SYSTEM-UNITS-ALIST)))", ((cpp_function_code)(&javaTranslateWalkedSystemUnits)), NULL);
      defineFunctionObject("JAVA-OUTPUT-SYSTEM-SPECIFIC-FILES", "(DEFUN JAVA-OUTPUT-SYSTEM-SPECIFIC-FILES ())", ((cpp_function_code)(&javaOutputSystemSpecificFiles)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-SYSTEM", "(DEFUN JAVA-TRANSLATE-SYSTEM ((SYSTEMNAME STRING)) :DOCUMENTATION \"Translate the system `systemName' to Java.\" :PUBLIC? TRUE)", ((cpp_function_code)(&javaTranslateSystem)), NULL);
      defineFunctionObject("JAVA-GET-SYSTEM-MAVEN-TEMPLATE-FILE", "(DEFUN (JAVA-GET-SYSTEM-MAVEN-TEMPLATE-FILE FILE-NAME) ())", ((cpp_function_code)(&javaGetSystemMavenTemplateFile)), NULL);
      defineFunctionObject("JAVA-GET-SYSTEM-PARENT-MAVEN-TEMPLATE-FILE", "(DEFUN (JAVA-GET-SYSTEM-PARENT-MAVEN-TEMPLATE-FILE FILE-NAME) ())", ((cpp_function_code)(&javaGetSystemParentMavenTemplateFile)), NULL);
      defineExternalSlotFromStringifiedSource("(DEFSLOT SYSTEM-DEFINITION SYSTEM-GROUP-NAME :TYPE STRING :DEFAULT \"edu.isi.loom.stella\" :OPTION-KEYWORD :GROUP-NAME :DOCUMENTATION \"Used as the Maven groupId for this system.\" :ALLOCATION :DYNAMIC)");
      defineFunctionObject("JAVA-YIELD-SYSTEM-GROUP-NAME", "(DEFUN (JAVA-YIELD-SYSTEM-GROUP-NAME STRING) ((SYSTEM SYSTEM-DEFINITION)))", ((cpp_function_code)(&javaYieldSystemGroupName)), NULL);
      defineFunctionObject("JAVA-YIELD-SYSTEM-VERSION", "(DEFUN (JAVA-YIELD-SYSTEM-VERSION STRING) ((SYSTEM SYSTEM-DEFINITION)))", ((cpp_function_code)(&javaYieldSystemVersion)), NULL);
      defineFunctionObject("JAVA-YIELD-SYSTEM-PARENT-NAME", "(DEFUN (JAVA-YIELD-SYSTEM-PARENT-NAME STRING) ((SYSTEM SYSTEM-DEFINITION)))", ((cpp_function_code)(&javaYieldSystemParentName)), NULL);
      defineFunctionObject("SUBSTITUTE-TEMPLATE-VARIABLES-TO-MAVEN-FILE", "(DEFUN SUBSTITUTE-TEMPLATE-VARIABLES-TO-MAVEN-FILE ((TEMPLATEFILE STRING) (OUTPUTFILE STRING) (VARIABLES (KEY-VALUE-LIST OF STRING-WRAPPER STRING-WRAPPER))))", ((cpp_function_code)(&substituteTemplateVariablesToMavenFile)), NULL);
      defineFunctionObject("JAVA-OUTPUT-SYSTEM-MAVEN-FILES", "(DEFUN JAVA-OUTPUT-SYSTEM-MAVEN-FILES ())", ((cpp_function_code)(&javaOutputSystemMavenFiles)), NULL);
      defineFunctionObject("STARTUP-JAVA-TRANSLATE-FILE", "(DEFUN STARTUP-JAVA-TRANSLATE-FILE () :PUBLIC? TRUE)", ((cpp_function_code)(&startupJavaTranslateFile)), NULL);
      { MethodSlot* function = lookupFunction(SYM_JAVA_TRANSLATE_FILE_STELLA_STARTUP_JAVA_TRANSLATE_FILE);

        setDynamicSlotValue(function->dynamicSlots, SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupJavaTranslateFile"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("STELLA")))));
      defineGlobalVariableObject("(DEFSPECIAL *CURRENT-JAVA-OUTPUT-CLASS* CLASS NULL :PUBLIC? FALSE :DOCUMENTATION \"Holds the current Stella class being output in Java\")", &oCURRENT_JAVA_OUTPUT_CLASSo);
      defineGlobalVariableObject("(DEFGLOBAL *JAVA-BUILD-METHOD* KEYWORD :MAVEN :DOCUMENTATION \"Indicates how JAVA translations of STELLA systems will be compiled and built.\nControls the native java directory structure as well as generation of build files such as pom.xml.\nCurrently supported methods are :JAVAC (the original) and :MAVEN.\" :DEMON-PROPERTY \"stella.javaBuildMethod\" :PUBLIC? TRUE)", &oJAVA_BUILD_METHODo);
    }
  }
}

Keyword* KWD_JAVA_TRANSLATE_FILE_COMMON_LISP = NULL;

Keyword* KWD_JAVA_TRANSLATE_FILE_JAVA = NULL;

Keyword* KWD_JAVA_TRANSLATE_FILE_IF_NOT_EXISTS = NULL;

Keyword* KWD_JAVA_TRANSLATE_FILE_CREATE_PATH = NULL;

Keyword* KWD_JAVA_TRANSLATE_FILE_MINIMIZE_JAVA_PREFIXES = NULL;

Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD_CONSTRUCTORp = NULL;

Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD_NATIVEp = NULL;

Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD = NULL;

Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_MACRO = NULL;

Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_PRINT_METHOD = NULL;

Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_TYPE = NULL;

Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_VERBATIM = NULL;

Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_CLASS = NULL;

Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_GLOBAL_VARIABLE = NULL;

Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

Keyword* KWD_JAVA_TRANSLATE_FILE_MAVEN = NULL;

Keyword* KWD_JAVA_TRANSLATE_FILE_TWO_PASSp = NULL;

Keyword* KWD_JAVA_TRANSLATE_FILE_FORCE_TRANSLATIONp = NULL;

Keyword* KWD_JAVA_TRANSLATE_FILE_PRODUCTION_SETTINGSp = NULL;

Keyword* KWD_JAVA_TRANSLATE_FILE_STELLA = NULL;

Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_SYSTEM_GROUP_NAME = NULL;

Keyword* KWD_JAVA_TRANSLATE_FILE_MINUTES = NULL;

Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_STARTUP_JAVA_TRANSLATE_FILE = NULL;

} // end of namespace stella
