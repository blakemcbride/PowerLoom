//  -*- Mode: C++ -*-

// translate-file.cc

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

// If `true', record object signatures into a persistent table.
boolean oRECORD_SIGNATURESpo = false;

// If `true', the walker will try to find previously recorded
// signatures for referenced but undefined functions, methods, etc.
boolean oWALK_WITH_RECORDED_SIGNATURESpo = false;

// If `true', `safe-lookup-slot' and `lookup-function' will
// try to retrieve a previously recorded signature if normal lookup fails.
DEFINE_STELLA_SPECIAL(oUSERECORDEDSIGNATURESpo, boolean , false);

DEFINE_STELLA_SPECIAL(oDEFAULTROOTSOURCEDIRECTORYo, const char* , "ST:sources;");

DEFINE_STELLA_SPECIAL(oDEFAULTROOTNATIVEDIRECTORYo, const char* , "ST:native;");

DEFINE_STELLA_SPECIAL(oDEFAULTROOTBINARYDIRECTORYo, const char* , "ST:bin;");

// Points to a list of directories containing system definition files.
DEFINE_STELLA_SPECIAL(oDEFAULTSYSTEMDEFINITIONDIRECTORIESo, Cons* , NULL);

const char* rootSourceDirectory() {
  // Accessor to determine the currently active sources directory root.
  // If it is defined as an option in the currently active system action, use that.
  // If we have an active system, use its value, otherwise use the STELLA default value.
  if (((boolean)(oCURRENT_SYSTEM_ACTIONo)) &&
      ((boolean)(oCURRENT_SYSTEM_ACTIONo->lookup(KWD_TRANSLATE_FILE_ROOT_SOURCE_DIRECTORY)))) {
    return (translateLogicalPathname(((StringWrapper*)(oCURRENT_SYSTEM_ACTIONo->lookup(KWD_TRANSLATE_FILE_ROOT_SOURCE_DIRECTORY)))->wrapperValue));
  }
  else if (((boolean)(oCURRENTSYSTEMDEFINITIONo)) &&
      (oCURRENTSYSTEMDEFINITIONo->sourceRootDirectory != NULL)) {
    return (translateLogicalPathname(oCURRENTSYSTEMDEFINITIONo->sourceRootDirectory));
  }
  else {
    return (translateLogicalPathname(oDEFAULTROOTSOURCEDIRECTORYo));
  }
}

const char* rootNativeDirectory() {
  // Accessor to determine the currently active native directory root.
  // If it is defined as an option in the currently active system action, use that.
  // If we have an active system, use its value, otherwise use the STELLA default value.
  if (((boolean)(oCURRENT_SYSTEM_ACTIONo)) &&
      ((boolean)(oCURRENT_SYSTEM_ACTIONo->lookup(KWD_TRANSLATE_FILE_ROOT_NATIVE_DIRECTORY)))) {
    return (translateLogicalPathname(((StringWrapper*)(oCURRENT_SYSTEM_ACTIONo->lookup(KWD_TRANSLATE_FILE_ROOT_NATIVE_DIRECTORY)))->wrapperValue));
  }
  else if (((boolean)(oCURRENTSYSTEMDEFINITIONo)) &&
      (oCURRENTSYSTEMDEFINITIONo->nativeRootDirectory != NULL)) {
    return (translateLogicalPathname(oCURRENTSYSTEMDEFINITIONo->nativeRootDirectory));
  }
  else {
    return (translateLogicalPathname(oDEFAULTROOTNATIVEDIRECTORYo));
  }
}

const char* rootBinaryDirectory() {
  // Accessor to determine the currently active binary directory root.
  // If it is defined as an option in the currently active system action, use that.
  // If we have an active system, use its value, otherwise use the STELLA default value.
  if (((boolean)(oCURRENT_SYSTEM_ACTIONo)) &&
      ((boolean)(oCURRENT_SYSTEM_ACTIONo->lookup(KWD_TRANSLATE_FILE_ROOT_BINARY_DIRECTORY)))) {
    return (translateLogicalPathname(((StringWrapper*)(oCURRENT_SYSTEM_ACTIONo->lookup(KWD_TRANSLATE_FILE_ROOT_BINARY_DIRECTORY)))->wrapperValue));
  }
  else if (((boolean)(oCURRENTSYSTEMDEFINITIONo)) &&
      (oCURRENTSYSTEMDEFINITIONo->binaryRootDirectory != NULL)) {
    return (translateLogicalPathname(oCURRENTSYSTEMDEFINITIONo->binaryRootDirectory));
  }
  else {
    return (translateLogicalPathname(oDEFAULTROOTBINARYDIRECTORYo));
  }
}

Cons* systemDefinitionDirectories() {
  { Cons* value000 = NIL;

    { StringWrapper* dir = NULL;
      Cons* iter000 = oDEFAULTSYSTEMDEFINITIONDIRECTORIESo;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        dir = ((StringWrapper*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(wrapString(translateLogicalPathname(dir->wrapperValue)), NIL);
            if (value000 == NIL) {
              value000 = collect000;
            }
            else {
              addConsToEndOfConsList(value000, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(wrapString(translateLogicalPathname(dir->wrapperValue)), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    { Cons* value001 = value000;

      return (value001);
    }
  }
}

// Points to the current system.
DEFINE_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONo, SystemDefinition* , NULL);

// Points to a path from the root directory down
// to a local directory containing sources, natives, or binaries.
DEFINE_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo, const char* , "");

boolean topLevelStellaSystemDirectoryP(const char* directory) {
  // Return TRUE if `directory' is a top-level STELLA installation directory
  // containing one or more STELLA systems.  We currently determine this solely by looking
  // for the existence of at least one relevant top-level native directory.  This is needed
  // to find system root directories and other relevant STELLA installation directories.
  { const char* nativename = relativeUnlogicalizePathname(oDEFAULTROOTNATIVEDIRECTORYo);
    const char* sourcename = relativeUnlogicalizePathname(oDEFAULTROOTSOURCEDIRECTORYo);

    return (probeFileP(concatenateFileNames(directory, 2, nativename, "cpp")) ||
        (probeFileP(concatenateFileNames(directory, 2, nativename, "java")) ||
         (probeFileP(concatenateFileNames(directory, 2, nativename, "lisp")) ||
          probeFileP(concatenateFileNames(directory, 2, sourcename, "systems")))));
  }
}

boolean handleInModuleTree(Cons* tree, boolean seeninmoduleP, boolean erroroninmoduleP, boolean& _Return1) {
  { Object* operatoR = tree->value;
    Object* firstarg = NULL;

    if (subtypeOfSymbolP(safePrimaryType(operatoR))) {
      { Object* operator000 = operatoR;
        Symbol* operatoR = ((Symbol*)(operator000));

        { const char* testValue000 = (oMODULEo->caseSensitiveP ? stringUpcase(operatoR->symbolName) : operatoR->symbolName);

          if (stringEqlP(testValue000, "IN-PACKAGE")) {
            _Return1 = seeninmoduleP;
            return (true);
          }
          else if (stringEqlP(testValue000, "IN-MODULE")) {
            if (seeninmoduleP &&
                erroroninmoduleP) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Additional IN-MODULE declaration: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
                }
              }
              _Return1 = seeninmoduleP;
              return (false);
            }
            firstarg = tree->rest->value;
            if (subtypeOfStringP(safePrimaryType(firstarg))) {
              { Object* firstarg000 = firstarg;
                StringWrapper* firstarg = ((StringWrapper*)(firstarg000));

                stringChangeModule(firstarg->wrapperValue);
                seeninmoduleP = true;
              }
            }
            else {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationWarning();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> WARNING: ", STANDARD_WARNING);
                  *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Ignoring illegal IN-MODULE declaration: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
                }
              }
            }
            _Return1 = seeninmoduleP;
            return (false);
          }
          else if (stringEqlP(testValue000, "DEFMODULE") ||
              stringEqlP(testValue000, "VERBATIM")) {
          }
          else {
            if (!(seeninmoduleP)) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationWarning();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> WARNING: ", STANDARD_WARNING);
                  *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Missing IN-MODULE declaration, translating " << "into module STELLA" << "." << std::endl;
                }
              }
              stringChangeModule("STELLA");
              seeninmoduleP = true;
            }
          }
        }
      }
    }
    else {
    }
    _Return1 = seeninmoduleP;
    return (false);
  }
}

void translateAndOutputUnitsToFile(const char* file, const char* targetlanguage) {
  oTRANSLATIONPHASEo = KWD_TRANSLATE_FILE_TRANSLATE;
  if (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_JAVA) {
  }
  else {
    if (oTRANSLATIONVERBOSITYLEVELo >= 1) {
      std::cout << "Translating " << "`" << file << "'" << " to " << "`" << targetlanguage << "'" << "..." << std::endl;
    }
    translateAllUnits();
  }
  outputAllUnitsToFile(file);
}

void operateOnFile(const char* file, Keyword* operation) {
  { const char* targetlanguage = oTRANSLATOROUTPUTLANGUAGEo->symbolName;
    Module* currentmodule = oMODULEo;
    Context* currentcontext = oCONTEXTo;
    boolean seeninmoduleP = false;
    boolean skipP = false;

    file = translateLogicalPathname(file);
    if (!((boolean)(operation))) {
      operation = KWD_TRANSLATE_FILE_TRANSLATE;
    }
    { 
      BIND_STELLA_SPECIAL(oTRANSLATIONPHASEo, Keyword*, NULL);
      BIND_STELLA_SPECIAL(oTRANSLATIONERRORSo, int, 0);
      BIND_STELLA_SPECIAL(oTRANSLATIONWARNINGSo, int, 0);
      BIND_STELLA_SPECIAL(oTRANSLATIONNOTESo, int, 0);
      BIND_STELLA_SPECIAL(oCURRENTFILENAMEo, const char*, fileBaseName(file));
      BIND_STELLA_SPECIAL(oMODULEo, Module*, currentmodule);
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, currentcontext);
      if (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_COMMON_LISP) {
        targetlanguage = "Common Lisp";
      }
      else if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_CPP) ||
          (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_CPP_STANDALONE)) {
        targetlanguage = "C++";
      }
      else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_IDL) {
        targetlanguage = "IDL";
      }
      else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_JAVA) {
        targetlanguage = "Java";
      }
      else {
      }
      if (oTRANSLATIONVERBOSITYLEVELo >= 1) {
        std::cout << "Processing " << "`" << file << "'" << ":" << std::endl;
        std::cout << "*** Pass 1, generating objects..." << std::endl;
      }
      { 
        BIND_STELLA_SPECIAL(oTRANSIENTOBJECTSpo, boolean, true);
        { Object* tree = NULL;
          SExpressionIterator* iter000 = sExpressions(newInputFileStream(file));

          for (; iter000->nextP(); ) {
            tree = iter000->value;
            { 
              BIND_STELLA_SPECIAL(oTRANSIENTOBJECTSpo, boolean, false);
              if (safePrimaryType(tree) == SGT_TRANSLATE_FILE_STELLA_CONS) {
                { Object* tree000 = tree;
                  Cons* tree = ((Cons*)(tree000));

                  skipP = handleInModuleTree(tree, seeninmoduleP, true, seeninmoduleP);
                  if (!(skipP)) {
                    { 
                      BIND_STELLA_SPECIAL(oTRANSLATIONPHASEo, Keyword*, KWD_TRANSLATE_FILE_DEFINE);
                      walkTopLevelTree(tree, true);
                    }
                  }
                }
              }
              else {
              }
            }
          }
        }
      }
      oTRANSLATIONUNITSo->reverse();
      if (!(operation == KWD_TRANSLATE_FILE_DEFINE)) {
        if (oTRANSLATIONVERBOSITYLEVELo >= 1) {
          std::cout << "*** Pass 2, finalizing objects..." << std::endl;
        }
        oTRANSLATIONPHASEo = KWD_TRANSLATE_FILE_FINALIZE;
        finalizeClassesAndSlots();
        if (!(operation == KWD_TRANSLATE_FILE_FINALIZE)) {
          if (oTRANSLATIONVERBOSITYLEVELo >= 1) {
            std::cout << "*** Pass 3, walking objects..." << std::endl;
          }
          oTRANSLATIONPHASEo = KWD_TRANSLATE_FILE_WALK;
          if (!(useHardcodedSymbolsP() ||
              (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_JAVA))) {
            clearSymbolRegistry();
          }
          { 
            BIND_STELLA_SPECIAL(oUSERECORDEDSIGNATURESpo, boolean, oWALK_WITH_RECORDED_SIGNATURESpo);
            walkAllPhaseOneUnits();
          }
          if (!(operation == KWD_TRANSLATE_FILE_WALK)) {
            translateAndOutputUnitsToFile(file, targetlanguage);
          }
          if (oRECORD_SIGNATURESpo) {
            std::cout << "Recording object signatures..." << std::endl;
            recordSignaturesOfAllUnits(file);
          }
        }
      }
      summarizeTranslationErrors();
    }
  }
}

void cleanUpTranslationUnitsSpecial() {
  { TranslationUnit* unit = NULL;
    Cons* iter000 = oTRANSLATIONUNITSo->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      unit = ((TranslationUnit*)(iter000->value));
      unit->free();
    }
  }
  oTRANSLATIONUNITSo->clear();
  sweepTransients();
}

void translateFile(const char* file, Keyword* outputlanguage, boolean aspartofsystemP) {
  { Keyword* mode = KWD_TRANSLATE_FILE_TRANSLATE;

    { 
      BIND_STELLA_SPECIAL(oJAVA_INDENT_CHARSo, int, 0);
      BIND_STELLA_SPECIAL(oIDL_INDENT_CHARSo, int, 0);
      BIND_STELLA_SPECIAL(oCPP_INDENT_CHARSo, int, 0);
      if (outputlanguage == KWD_TRANSLATE_FILE_JAVA) {
        if (aspartofsystemP) {
          mode = KWD_TRANSLATE_FILE_WALK;
        }
      }
      else {
      }
      if (aspartofsystemP) {
        operateOnFile(file, mode);
      }
      else {
        { 
          BIND_STELLA_SPECIAL(oTRANSLATOROUTPUTLANGUAGEo, Keyword*, oTRANSLATOROUTPUTLANGUAGEo);
          BIND_STELLA_SPECIAL(oTRANSLATIONUNITSo, List*, newList());
          setTranslatorOutputLanguage(outputlanguage);
          operateOnFile(file, mode);
          if (outputlanguage == KWD_TRANSLATE_FILE_CPP_STANDALONE) {
          }
          else {
            cleanUpTranslationUnitsSpecial();
          }
        }
      }
    }
  }
}

void outputAllUnitsToFile(const char* sourcefile) {
  if (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_COMMON_LISP) {
    clOutputAllUnitsToFile(sourcefile);
  }
  else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_JAVA) {
    { 
      BIND_STELLA_SPECIAL(oJAVA_INDENT_CHARSo, int, 0);
      javaOutputAllUnitsToFile();
    }
  }
  else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_IDL) {
    { 
      BIND_STELLA_SPECIAL(oIDL_INDENT_CHARSo, int, 0);
      idlOutputAllUnitsToFile(sourcefile);
    }
  }
  else if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_CPP) ||
      (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_CPP_STANDALONE)) {
    { 
      BIND_STELLA_SPECIAL(oCPP_INDENT_CHARSo, int, 0);
      cppOutputAllUnitsToFile(sourcefile);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void recordSignaturesOfAllUnits(const char* sourcefile) {
  sourcefile = sourcefile;
}

boolean translateWithCopyrightHeaderP() {
  return (oCURRENT_STELLA_FEATURESo->membP(KWD_TRANSLATE_FILE_TRANSLATE_WITH_COPYRIGHT_HEADER));
}

void outputCopyrightHeader(OutputStream* stream) {
  if ((!translateWithCopyrightHeaderP()) ||
      ((!((boolean)(oCURRENTSYSTEMDEFINITIONo))) ||
       (oCURRENTSYSTEMDEFINITIONo->banner == NULL))) {
    return;
  }
  if (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_COMMON_LISP) {
    *(stream->nativeStream) << "#|" << std::endl;
  }
  else if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_JAVA) ||
      ((oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_CPP) ||
       (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_CPP_STANDALONE))) {
    *(stream->nativeStream) << "/*" << std::endl;
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  { KeyValueList* substitutionList = newKeyValueList();
    InputStringStream* bstream = makeTokenizerStringStream(oCURRENTSYSTEMDEFINITIONo->banner);

    fillInDateSubstitution(substitutionList);
    substituteTemplateVariablesToStream(bstream, stream, substitutionList);
  }
  if (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_COMMON_LISP) {
    *(stream->nativeStream) << "|#";
  }
  else if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_JAVA) ||
      ((oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_CPP) ||
       (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_CPP_STANDALONE))) {
    *(stream->nativeStream) << "*/";
  }
  else {
    { OutputStringStream* stream001 = newOutputStringStream();

      *(stream001->nativeStream) << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " is not a valid case option";
      throw *newStellaException(stream001->theStringReader());
    }
  }
  *(stream->nativeStream) << std::endl << std::endl;
}

void outputFileHeader(OutputStream* stream, const char* file) {
  if (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_COMMON_LISP) {
    clOutputFileHeader(stream, file, true);
  }
  else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_JAVA) {
    javaOutputFileHeader(stream, file);
  }
  else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_CPP) {
    cppOutputFileHeader(stream, file);
  }
  else {
    clOutputFileHeader(stream, file, false);
  }
}

// The operating system we are running on.  Currently,
// either :UNIX, :WINDOWS, or :MAC.  Note that on the Mac OS X, the
// OS can be either :UNIX or :MAC, depending on which file naming 
// conventions are being observed by the software.
Keyword* oOSo = NULL;

Keyword* operatingSystem() {
  if (probeFileP("C:\\AUTOEXEC.BAT") ||
      (probeFileP("C:\\IO.SYS") ||
       (probeFileP("C:\\BOOT.INI") ||
        startsWithP("", "win", 0)))) {
    return (KWD_TRANSLATE_FILE_WINDOWS);
  }
  else if (probeFileP("/usr") ||
      probeFileP("/etc")) {
    return (KWD_TRANSLATE_FILE_UNIX);
  }
  else {
    return (KWD_TRANSLATE_FILE_MAC);
  }
}

char directorySeparator() {
  { char separator = '?';

    if (((boolean)(oOSo))) {
      if (oOSo == KWD_TRANSLATE_FILE_UNIX) {
        separator = '/';
      }
      else if (oOSo == KWD_TRANSLATE_FILE_MAC) {
        separator = ':';
      }
      else if (oOSo == KWD_TRANSLATE_FILE_WINDOWS) {
        separator = '\\';
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << oOSo << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    return (separator);
  }
}

const char* directorySeparatorString() {
  return (makeString(1, directorySeparator()));
}

char directorySeparatorForFile(const char* file) {
  if (logicalPathnameP(file)) {
    return (LOGICAL_DIRECTORY_SEPARATOR);
  }
  else {
    return (directorySeparator());
  }
}

char TYPE_SEPARATOR = '.';

const char* fileNameDirectory(const char* file) {
  // Return the directory component of `file' including the final
  // directory separator or the empty string if `file' does not include a directory.
  // Note that for purposes of this function, a logical host is considered part of
  // the directory portion of `file'
  { int start = 0;
    int length = strlen(file);
    char separator = directorySeparatorForFile(file);

    if (logicalPathnameP(file)) {
      start = stringPosition(file, LOGICAL_HOST_SEPARATOR, 0) + 1;
    }
    while ((start < length) &&
        (stringPosition(file, separator, start) != NULL_INTEGER)) {
      start = stringPosition(file, separator, start) + 1;
    }
    return (stringSubsequence(file, 0, start));
  }
}

const char* directoryFileName(const char* directory) {
  // Return `directory' as a file name, i.e., without a terminating
  // directory separator.
  { char separator = directorySeparatorForFile(directory);
    int last = strlen(directory) - 1;

    if ((last >= 0) &&
        (directory[last] == separator)) {
      return (stringSubsequence(directory, 0, last));
    }
    else {
      return (directory);
    }
  }
}

const char* fileNameAsDirectory(const char* file) {
  // Return `file' interpreted as a directory, i.e., with a
  // terminating directory separator.  If `file' is the empty string simply
  // return the empty string, i.e., interpret it as the current directory instead
  // of the root directory.
  { char separator = directorySeparatorForFile(file);
    int last = strlen(file) - 1;

    if ((last < 0) ||
        (file[last] == separator)) {
      return (file);
    }
    else {
      return (stringConcatenate(file, makeString(1, separator), 0));
    }
  }
}

const char* directoryParentDirectory(const char* directory, int level) {
  // Return the `level'-th parent directory component of `directory'
  // including the final directory separator, or the empty string if `directory' does
  // not have that many parents.
  { int i = NULL_INTEGER;
    int iter000 = 1;
    int upperBound000 = level;
    boolean unboundedP000 = upperBound000 == NULL_INTEGER;

    for  (; unboundedP000 ||
              (iter000 <= upperBound000); 
          iter000 = iter000 + 1) {
      i = iter000;
      i = i;
      directory = fileNameDirectory(directoryFileName(directory));
    }
  }
  return (directory);
}

const char* fileNameWithoutDevice(const char* file) {
  // Return the file name portion of `file' by removing any
  // physical device components.  This is just like `logical-pathname-without-host'
  // but only looks for one-character device strings as used in Windows.
  { char separator = ':';

    if ((strlen(file) >= 2) &&
        ((file[1] == separator) &&
         (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (file[0])] == KWD_TRANSLATE_FILE_LETTER))) {
      return (stringSubsequence(file, 2, NULL_INTEGER));
    }
    else {
      return (file);
    }
  }
}

const char* fileNameWithoutDirectory(const char* file) {
  // Return the file name portion of `file' by removing any
  // directory and logical host components.
  { int start = 0;
    char separator = directorySeparatorForFile(file);

    if (separator == LOGICAL_HOST_SEPARATOR) {
      file = logicalPathnameWithoutHost(file);
    }
    else {
      file = fileNameWithoutDevice(file);
    }
    while (stringPosition(file, separator, start) != NULL_INTEGER) {
      start = stringPosition(file, separator, start) + 1;
    }
    return (stringSubsequence(file, start, NULL_INTEGER));
  }
}

const char* fileNameWithoutExtension(const char* file) {
  // Remove `file's extension (or type) if there is any and
  // return the result.
  { int start = 0;
    int end = NULL_INTEGER;

    while (stringPosition(file, TYPE_SEPARATOR, start) != NULL_INTEGER) {
      end = stringPosition(file, TYPE_SEPARATOR, start);
      start = end + 1;
    }
    return (stringSubsequence(file, 0, end));
  }
}

const char* fileExtension(const char* file) {
  // Return `file's extension (or type) if it has any including
  // the separator character.
  { int start = 0;
    int end = NULL_INTEGER;

    while (stringPosition(file, TYPE_SEPARATOR, start) != NULL_INTEGER) {
      end = stringPosition(file, TYPE_SEPARATOR, start);
      start = end + 1;
    }
    if (end == NULL_INTEGER) {
      return (NULL);
    }
    else if (stringPosition(file, directorySeparatorForFile(file), end) != NULL_INTEGER) {
      return (NULL);
    }
    else {
      return (stringSubsequence(file, end, NULL_INTEGER));
    }
  }
}

const char* fileBaseName(const char* file) {
  // Remove `file's directory (including logical host) and
  // extension components and return the result.
  return (fileNameWithoutExtension(fileNameWithoutDirectory(file)));
}

char LOGICAL_DIRECTORY_SEPARATOR = ';';

char LOGICAL_HOST_SEPARATOR = ':';

StringHashTable* oLOGICAL_HOST_TABLEo = NULL;

void defineLogicalHostProperty(const char* host, Keyword* property, Object* value) {
  // Define `property' with `value' for the logical host `host'.
  // As a side-effect, this also defines `host' as a logical host (both
  // `property' and `value' can be supplied as NULL).  If :ROOT-DIRECTORY
  // is specified, all pathnames with `host' are assumed to be relative to
  // that directory (even if they are absolute) and will be rerooted upon
  // translation.  :ROOT-DIRECTORY can be a logical or physical pathname.
  // If :LISP-TRANSLATIONS is specified, those will be used verbatimely as
  // the value of `(CL:logical-pathname-translations host)' if we are
  // running in Lisp, which allows us to depend on the native
  // `CL:translate-logical-pathname' for more complex translation operations.
  host = stringUpcase(host);
  { KeyValueList* properties = ((KeyValueList*)(oLOGICAL_HOST_TABLEo->lookup(host)));

    if (!((boolean)(properties))) {
      properties = newKeyValueList();
      oLOGICAL_HOST_TABLEo->insertAt(host, properties);
    }
    if (((boolean)(property))) {
      if (property == KWD_TRANSLATE_FILE_ROOT_DIRECTORY) {
        properties->insertAt(property, NULL);
        if (((boolean)(value))) {
          properties->insertAt(property, wrapString(translateLogicalPathname(fileNameAsDirectory(((StringWrapper*)(value))->wrapperValue))));
        }
      }
      else if (property == KWD_TRANSLATE_FILE_LISP_TRANSLATIONS) {
        properties->insertAt(property, value);
      }
      else {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "Illegal host property: " << "`" << property << "'" << std::endl;
      }
    }
  }
}

void defineLogicalHostPropertyEvaluatorWrapper(Cons* arguments) {
  defineLogicalHostProperty(((StringWrapper*)(arguments->value))->wrapperValue, ((Keyword*)(arguments->rest->value)), arguments->rest->rest->value);
}

Object* lookupLogicalHostProperty(const char* host, Keyword* property) {
  host = stringUpcase(host);
  { KeyValueList* properties = ((KeyValueList*)(oLOGICAL_HOST_TABLEo->lookup(host)));

    if (!((boolean)(properties))) {
      return (NULL);
    }
    else {
      return (properties->lookup(property));
    }
  }
}

Object* getLogicalHostProperty(Object* host, Object* property) {
  // Lookup the value of `property' for the logical host `host'.
  return (lookupLogicalHostProperty(coerceValueToString(host, true), ((Keyword*)(coerceValueToType(property, SGT_TRANSLATE_FILE_STELLA_KEYWORD, true)))));
}

boolean logicalHostP(const char* host) {
  return (((boolean)(((KeyValueList*)(oLOGICAL_HOST_TABLEo->lookup(stringUpcase(host)))))));
}

boolean logicalPathnameP(const char* pathname) {
  { const char* host = getLogicalHostName(pathname);

    return ((host != NULL) &&
        logicalHostP(host));
  }
}

boolean absolutePathnameP(const char* pathname) {
  { char separator = directorySeparator();

    if (logicalPathnameP(pathname)) {
      separator = LOGICAL_DIRECTORY_SEPARATOR;
      pathname = logicalPathnameWithoutHost(pathname);
    }
    else {
      pathname = fileNameWithoutDevice(pathname);
    }
    return ((strlen(pathname) > 0) &&
        (pathname[0] == separator));
  }
}

const char* getLogicalHostName(const char* pathname) {
  { int separatorpos = stringPosition(pathname, LOGICAL_HOST_SEPARATOR, 0);

    if ((separatorpos != NULL_INTEGER) &&
        (separatorpos >= 1)) {
      return (stringSubsequence(pathname, 0, separatorpos));
    }
    else {
      return (NULL);
    }
  }
}

const char* logicalPathnameWithoutHost(const char* pathname) {
  { const char* hostname = getLogicalHostName(pathname);

    if (hostname == NULL) {
      return (pathname);
    }
    else {
      return (stringSubsequence(pathname, strlen(hostname) + 1, NULL_INTEGER));
    }
  }
}

const char* translateLogicalPathname(const char* pathname) {
  if (!(logicalPathnameP(pathname))) {
    return (pathname);
  }
  { const char* host = getLogicalHostName(pathname);
    const char* translatedpathname = pathname;

    translatedpathname = stringSubstitute(logicalPathnameWithoutHost(pathname), directorySeparator(), LOGICAL_DIRECTORY_SEPARATOR);
    { StringWrapper* rootdirectory = ((StringWrapper*)(lookupLogicalHostProperty(host, KWD_TRANSLATE_FILE_ROOT_DIRECTORY)));

      if (((boolean)(rootdirectory))) {
        if (absolutePathnameP(translatedpathname)) {
          translatedpathname = stringSubsequence(translatedpathname, 1, NULL_INTEGER);
        }
        translatedpathname = stringConcatenate(rootdirectory->wrapperValue, translatedpathname, 0);
      }
    }
    return (translatedpathname);
  }
}

const char* unlogicalizePathname(const char* pathname) {
  return (translateLogicalPathname(pathname));
}

const char* relativeUnlogicalizePathname(const char* pathname) {
  // If `pathName' is a logical pathname translate it, however, remove the
  // :root-directory prefix of the logical host.  Otherwise, return `pathName' as is.
  if (!(logicalPathnameP(pathname))) {
    return (pathname);
  }
  { const char* host = getLogicalHostName(pathname);
    const char* rootprefix = translateLogicalPathname(stringConcatenate(host, ":", 0));

    return (stringSubsequence(translateLogicalPathname(pathname), strlen(rootprefix), NULL_INTEGER));
  }
}

const char* mergeFileNames(const char* basefile, const char* defaults) {
  // Parse `baseFile', supply any missing components from
  // `defaults' if supplied and return the result.
  { char baseseparator = directorySeparatorForFile(basefile);
    const char* basehost = getLogicalHostName(basefile);
    const char* basedirectory = logicalPathnameWithoutHost(fileNameDirectory(basefile));
    const char* basename = fileBaseName(basefile);
    const char* baseextension = fileExtension(basefile);
    char defaultsseparator = directorySeparatorForFile(defaults);
    boolean mergedP = false;
    OutputStringStream* result = NULL;

    if ((!(baseseparator == defaultsseparator)) &&
        (stringMemberP(basefile, baseseparator) &&
         stringMemberP(defaults, defaultsseparator))) {
      throw *newStellaException("merge-file-names: base file and defaults use different syntax");
    }
    if (basehost == NULL) {
      basehost = getLogicalHostName(defaults);
      mergedP = mergedP ||
          (basehost != NULL);
    }
    if (stringEqlP(basedirectory, "")) {
      basedirectory = logicalPathnameWithoutHost(fileNameDirectory(defaults));
      mergedP = mergedP ||
          (!stringEqlP(basedirectory, ""));
    }
    if (basename == NULL) {
      basename = fileBaseName(defaults);
      mergedP = mergedP ||
          (basename != NULL);
    }
    if (baseextension == NULL) {
      baseextension = fileExtension(defaults);
      mergedP = mergedP ||
          (baseextension != NULL);
    }
    if (!mergedP) {
      return (basefile);
    }
    result = newOutputStringStream();
    if (basehost != NULL) {
      *(result->nativeStream) << basehost << LOGICAL_HOST_SEPARATOR;
    }
    *(result->nativeStream) << basedirectory;
    if (basename != NULL) {
      *(result->nativeStream) << basename;
    }
    if (baseextension != NULL) {
      *(result->nativeStream) << baseextension;
    }
    return (result->theStringReader());
  }
}

const char* concatenateFileNames(const char* file, int otherfiles, ...) {
  // Intelligently join `file' and `otherFiles' into a concatenated path where each
  // component is separated by a single separator (similar to Python's os.path.join).  Keeps the result
  // a logical pathname as long as possible, but converts to physical as soon as any of `otherFiles'
  // contain a physical directory separator.
  { char separator = directorySeparator();

    { va_list iter000;
      int iter000Count = otherfiles;
      const char* otherfile = NULL;

      va_start(iter000, otherfiles);
            for  (; (iter000Count--) > 0; ) {
        otherfile = va_arg(iter000, const char*);
        if (absolutePathnameP(otherfile)) {
          file = otherfile;
        }
        else {
          if ((separator != NULL_CHARACTER) &&
              stringMemberP(otherfile, separator)) {
            file = translateLogicalPathname(file);
            separator = NULL_CHARACTER;
          }
          file = stringConcatenate(fileNameAsDirectory(file), otherfile, 0);
        }
      }
      va_end(iter000);
    }
    return (file);
  }
}

// Used by `select-file-extension'.
Cons* oTYPE_TO_FILE_EXTENSION_TABLEo = NULL;

const char* computeCommonLispFileExtension(Keyword* type) {
  if (!(runningAsLispP())) {
    throw *newStellaException("Shouldn't call COMPUTE-COMMON-LISP-FILE-EXTENSION unless running in Lisp");
  }
  { const char* suffix = NULL;

    if (type == KWD_TRANSLATE_FILE_LISP_BINARY) {
      suffix = NULL;
      if (oCURRENT_STELLA_FEATURESo->membP(KWD_TRANSLATE_FILE_USE_COMMON_LISP_STRUCTS)) {
        suffix = stringConcatenate("s", suffix, 0);
      }
      else if (oCURRENT_STELLA_FEATURESo->membP(KWD_TRANSLATE_FILE_USE_COMMON_LISP_VECTOR_STRUCTS)) {
        suffix = stringConcatenate("vs", suffix, 0);
      }
      else {
      }
    }
    else if (type == KWD_TRANSLATE_FILE_LISP) {
      if (oCURRENT_STELLA_FEATURESo->membP(KWD_TRANSLATE_FILE_USE_COMMON_LISP_STRUCTS)) {
        suffix = ".slisp";
      }
      else if (oCURRENT_STELLA_FEATURESo->membP(KWD_TRANSLATE_FILE_USE_COMMON_LISP_VECTOR_STRUCTS)) {
        suffix = ".vslisp";
      }
      else {
        suffix = ".lisp";
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << type << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    return (stringConcatenate(".", suffix, 0));
  }
}

const char* defaultCommonLispFileExtension(Keyword* type) {
  if (type == KWD_TRANSLATE_FILE_LISP) {
    if (oOSo == KWD_TRANSLATE_FILE_WINDOWS) {
      return (".lsp");
    }
    else {
      return (".lisp");
    }
  }
  else if (type == KWD_TRANSLATE_FILE_LISP_BINARY) {
    if (oOSo == KWD_TRANSLATE_FILE_MAC) {
      return (".cfsl");
    }
    else if (oOSo == KWD_TRANSLATE_FILE_WINDOWS) {
      return (".fas");
    }
    else {
      return (".fasl");
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << type << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

const char* selectFileExtension(Keyword* type) {
  { const char* extension = NULL;

    { Cons* entry = NULL;
      Cons* iter000 = oTYPE_TO_FILE_EXTENSION_TABLEo;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        entry = ((Cons*)(iter000->value));
        if (entry->value == type) {
          extension = ((StringWrapper*)(entry->rest->value))->wrapperValue;
        }
      }
    }
    if (type == KWD_TRANSLATE_FILE_DIRECTORY) {
      return (directorySeparatorString());
    }
    else if ((type == KWD_TRANSLATE_FILE_LISP) ||
        (type == KWD_TRANSLATE_FILE_LISP_BINARY)) {
      if (runningAsLispP()) {
        return (computeCommonLispFileExtension(type));
      }
      else {
        return (defaultCommonLispFileExtension(type));
      }
    }
    else {
    }
    return (extension);
  }
}

Keyword* classifyFileExtension(const char* file) {
  { const char* extension = fileExtension(file);

    if (extension == NULL) {
      return (KWD_TRANSLATE_FILE_NONE);
    }
    { Cons* entry = NULL;
      Cons* iter000 = oTYPE_TO_FILE_EXTENSION_TABLEo;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        entry = ((Cons*)(iter000->value));
        if (eqlToStringP(entry->rest->value, extension)) {
          return (((Keyword*)(entry->value)));
        }
      }
    }
    if (runningAsLispP()) {
      if (stringEqlP(computeCommonLispFileExtension(KWD_TRANSLATE_FILE_LISP), extension)) {
        return (KWD_TRANSLATE_FILE_LISP);
      }
      if (stringEqlP(computeCommonLispFileExtension(KWD_TRANSLATE_FILE_LISP_BINARY), extension)) {
        return (KWD_TRANSLATE_FILE_LISP_BINARY);
      }
    }
    if (stringEqlP(defaultCommonLispFileExtension(KWD_TRANSLATE_FILE_LISP), extension)) {
      return (KWD_TRANSLATE_FILE_LISP);
    }
    if (stringEqlP(defaultCommonLispFileExtension(KWD_TRANSLATE_FILE_LISP_BINARY), extension)) {
      return (KWD_TRANSLATE_FILE_LISP_BINARY);
    }
    return (KWD_TRANSLATE_FILE_OTHER);
  }
}

const char* getRootDirectoryFromFileType(Keyword* type) {
  // Given a normalized file `type', determine which STELLA installation
  // root directory tree it naturally belongs to (i.e., source, native or binary).
  { const char* root = NULL;

    if ((type == KWD_TRANSLATE_FILE_STELLA) ||
        (type == KWD_TRANSLATE_FILE_KB)) {
      root = rootSourceDirectory();
    }
    else if ((type == KWD_TRANSLATE_FILE_LISP_BINARY) ||
        (type == KWD_TRANSLATE_FILE_DIRECTORY)) {
      root = rootBinaryDirectory();
    }
    else {
      root = rootNativeDirectory();
    }
    return (root);
  }
}

const char* getRootDirectoryFromFileExtension(const char* file) {
  // Given a `file', determine which STELLA installation root directory
  // tree it naturally belongs to based on its extension (i.e., source, native or binary).
  return (getRootDirectoryFromFileType(classifyFileExtension(file)));
}

const char* oLISP_SPLITTER_PATHo = "lisp";

const char* oJAVA_SPLITTER_PATHo = "java";

const char* oCPP_SPLITTER_PATHo = "cpp";

const char* getLanguageSubdirectoryFromFileType(Keyword* type) {
  // Compute a language-specific native subdirectory that should
  // be used for files of `type'.  If `type' does not naturally suggest which native
  // language it is associated with, key in on the current translation output language.
  // Returns the empty string for unhandled types.
  { const char* splitterpath = "";

    if ((type == KWD_TRANSLATE_FILE_LISP) ||
        (type == KWD_TRANSLATE_FILE_COMMON_LISP)) {
      splitterpath = oLISP_SPLITTER_PATHo;
    }
    else if (type == KWD_TRANSLATE_FILE_JAVA) {
      splitterpath = oJAVA_SPLITTER_PATHo;
    }
    else if ((type == KWD_TRANSLATE_FILE_CPP) ||
        ((type == KWD_TRANSLATE_FILE_CPP_HEADER) ||
         ((type == KWD_TRANSLATE_FILE_CPP_CODE) ||
          ((type == KWD_TRANSLATE_FILE_C_HEADER) ||
           (type == KWD_TRANSLATE_FILE_C_CODE))))) {
      splitterpath = oCPP_SPLITTER_PATHo;
    }
    else if ((type == KWD_TRANSLATE_FILE_NONE) ||
        (type == KWD_TRANSLATE_FILE_OTHER)) {
      return (getLanguageSubdirectoryFromFileType(oTRANSLATOROUTPUTLANGUAGEo));
    }
    else {
    }
    return (splitterpath);
  }
}

const char* getSystemSubdirectoryFromFileType(Keyword* type) {
  // Compute a native system subdirectory that should be used
  // for files of `type'.  If `type' does not naturally suggest which native language
  // it is associated with, key in on the current translation output language.
  // Returns the empty string for unhandled types.
  { const char* systemdirectory = "";
    boolean javaP = (type == KWD_TRANSLATE_FILE_JAVA) ||
        (((type == KWD_TRANSLATE_FILE_OTHER) ||
        (type == KWD_TRANSLATE_FILE_NONE)) &&
         (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_JAVA));

    if (javaP) {
      if (oJAVA_BUILD_METHODo == KWD_TRANSLATE_FILE_JAVAC) {
        return ("");
      }
      else if (oJAVA_BUILD_METHODo == KWD_TRANSLATE_FILE_MAVEN) {
        if (((boolean)(oCURRENTSYSTEMDEFINITIONo))) {
          return (oCURRENTSYSTEMDEFINITIONo->name);
        }
      }
      else {
      }
    }
    if (!(blankStringP(oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo))) {
      systemdirectory = oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo;
    }
    if (blankStringP(systemdirectory) &&
        ((boolean)(oCURRENTSYSTEMDEFINITIONo))) {
      systemdirectory = oCURRENTSYSTEMDEFINITIONo->name;
    }
    return (systemdirectory);
  }
}

const char* getNativeSourceSubdirectoryFromFileType(Keyword* type) {
  // Compute a native source subdirectory that should be used
  // for files of `type'.  If `type' does not naturally suggest which native language
  // it is associated with, key in on the current translation output language.
  // Returns the empty string for unhandled types.
  { const char* directory = "";
    boolean javaP = (type == KWD_TRANSLATE_FILE_JAVA) ||
        (((type == KWD_TRANSLATE_FILE_OTHER) ||
        (type == KWD_TRANSLATE_FILE_NONE)) &&
         (oTRANSLATOROUTPUTLANGUAGEo == KWD_TRANSLATE_FILE_JAVA));

    if (javaP) {
      if (oJAVA_BUILD_METHODo == KWD_TRANSLATE_FILE_MAVEN) {
        directory = concatenateFileNames("src", 2, "main", "java");
      }
      else {
      }
      directory = concatenateFileNames(directory, 1, javaPackagePrefix(oMODULEo, directorySeparatorString()));
    }
    return (directory);
  }
}

const char* makeFileNameFromRelativePath(Object* filepath, Keyword* type) {
  return (makeFileName(implodePathname(filepath), type, true));
}

const char* makeFileName(const char* filepath, Keyword* type, boolean relativeP) {
  // Make an absolute file-name string from 'filePath' with directory location
  // and file extension determined by 'type' and 'relative?'.  `type' is the main determiner
  // for whether we are creating a source, native or binary pathname in the respective root
  // directories, and it also controls the new extension of the resulting pathname replacing any
  // one on `filePath'.  If 'relative?' is TRUE, then the respective root directory prefix is appended,
  // plus any additional relevant language, system and source subdirectories.  If 'relative?' is
  // FALSE, then the current directory prefix of `filePath' as indicated by its extension is switched
  // to the new root directory indicated by `type'.  In this case, only the root and language directories
  // are inserted, but all the remaining source directory components are left the same (thus, this will
  // generally not do the right thing for Java file names).  This function takes the dynamic state of
  // currently active systems and modules into account.
  { const char* extension = selectFileExtension(type);
    const char* rootpath = "";
    const char* languagedir = "";
    const char* systemdir = "";
    const char* sourcedir = "";

    if (relativeP) {
      rootpath = getRootDirectoryFromFileType(type);
      languagedir = getLanguageSubdirectoryFromFileType(type);
      systemdir = getSystemSubdirectoryFromFileType(type);
      sourcedir = getNativeSourceSubdirectoryFromFileType(type);
      if (!(type == KWD_TRANSLATE_FILE_OTHER)) {
        filepath = fileNameWithoutExtension(filepath);
      }
    }
    else {
      { const char* rootprefix = fileNameAsDirectory(getRootDirectoryFromFileExtension(filepath));

        if (!(type == KWD_TRANSLATE_FILE_OTHER)) {
          filepath = fileNameWithoutExtension(filepath);
        }
        if (!getQuotedTree("((:STELLA :KB) \"/STELLA\")", "/STELLA")->memberP(type)) {
          { const char* relativepath = relativizeFileName(filepath, rootprefix);

            if (!stringEqlP(filepath, relativepath)) {
              rootpath = getRootDirectoryFromFileType(type);
              languagedir = getLanguageSubdirectoryFromFileType(type);
              filepath = relativepath;
            }
          }
        }
      }
    }
    return (concatenateFileNames(rootpath, 4, languagedir, systemdir, sourcedir, stringConcatenate(filepath, extension, 0)));
  }
}

const char* relativizeFileName(const char* file, const char* rootpath) {
  { boolean absoluteP = stringSearch(file, rootpath, 0) == 0;

    if (absoluteP) {
      return (stringSubsequence(file, strlen(rootpath), NULL_INTEGER));
    }
    else {
      return (file);
    }
  }
}

const char* helpImplodePathname(const char* filename) {
  { const char* extension = fileExtension(filename);

    if (extension == NULL) {
      return (maybeTruncateFilename(filename));
    }
    else {
      return (stringConcatenate(maybeTruncateFilename(fileBaseName(filename)), extension, 0));
    }
  }
}

const char* implodePathname(Object* filepath) {
  { const char* file = NULL;

    if (safePrimaryType(filepath) == SGT_TRANSLATE_FILE_STELLA_CONS) {
      { Object* filepath000 = filepath;
        Cons* filepath = ((Cons*)(filepath000));

        { int pathLength = filepath->length();

          file = "";
          { StringWrapper* name = NULL;
            Cons* iter000 = ((Cons*)(filepath));
            int n = NULL_INTEGER;
            int iter001 = 1;
            int upperBound000 = pathLength;
            boolean unboundedP000 = upperBound000 == NULL_INTEGER;

            for  (; (!(iter000 == NIL)) &&
                      (unboundedP000 ||
                       (iter001 <= upperBound000)); 
                  iter000 = iter000->rest,
                  iter001 = iter001 + 1) {
              name = ((StringWrapper*)(iter000->value));
              n = iter001;
              if (n == pathLength) {
                file = stringConcatenate(file, helpImplodePathname(name->wrapperValue), 0);
              }
              else {
                file = stringConcatenate(file, name->wrapperValue, 1, directorySeparatorString());
              }
            }
          }
        }
      }
    }
    else {
      file = helpImplodePathname(((StringWrapper*)(filepath))->wrapperValue);
    }
    return (file);
  }
}

// When TRUE, overrides normal truncation of file names.
DEFINE_STELLA_SPECIAL(oDONTTRUNCATEFILENAMESpo, boolean , false);

const char* maybeTruncateFilename(const char* barefilename) {
  if (oDONTTRUNCATEFILENAMESpo) {
    return (barefilename);
  }
  { int maximumlength = 999;

    if (oOSo == KWD_TRANSLATE_FILE_MAC) {
      maximumlength = 31 - 5;
    }
    else {
    }
    if (strlen(barefilename) > maximumlength) {
      { const char* originalfilename = barefilename;

        barefilename = stringSubsequence(barefilename, 0, maximumlength - 1);
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "Truncating name of file." << std::endl << "   Original: " << "`" << originalfilename << "'" << "    Truncated: " << "`" << barefilename << "'" << std::endl << std::endl;
      }
    }
    return (barefilename);
  }
}

const char* findSourceFromNativeFileName(const char* nativefilename) {
  // Try to find a STELLA source file based on the name and system components of `nativeFileName'.
  // This will generally search the current STELLA systems path, since the tree where a native file resides is not
  // necessarily the one where the corresponding source file is also.  This will only work for Lisp and C++ files
  // where the basename of translated files corresponds to the source file from which they were derived.  The main
  // purpose for this is to support the Emacs Lisp/STELLA interface to find function definitions.
  { const char* nativedir = fileNameDirectory(nativefilename);
    const char* nativename = fileNameWithoutExtension(fileBaseName(nativefilename));
    const char* nativesystemdir = NULL;
    const char* sourcefilename = NULL;
    const char* sourcesdir = relativeUnlogicalizePathname(oDEFAULTROOTSOURCEDIRECTORYo);
    Cons* stelladirectories = buildStellaSystemsPath();

    { int level = NULL_INTEGER;
      int iter000 = 1;

      for (; true; iter000 = iter000 + 1) {
        level = iter000;
        nativesystemdir = directoryParentDirectory(nativedir, level);
        if (blankStringP(nativesystemdir)) {
          break;
        }
        nativesystemdir = stringSubsequence(nativedir, strlen(nativesystemdir), NULL_INTEGER);
        sourcefilename = concatenateFileNames(nativesystemdir, 1, stringConcatenate(nativename, ".ste", 0));
        { StringWrapper* dir = NULL;
          Cons* iter001 = stelladirectories;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            dir = ((StringWrapper*)(iter001->value));
            if (probeFileP(concatenateFileNames(dir->wrapperValue, 2, sourcesdir, sourcefilename))) {
              return (concatenateFileNames(dir->wrapperValue, 2, sourcesdir, sourcefilename));
            }
          }
        }
      }
    }
    return (NULL);
  }
}

Keyword* languageToFileType(Keyword* language) {
  if (language == KWD_TRANSLATE_FILE_COMMON_LISP) {
    return (KWD_TRANSLATE_FILE_LISP);
  }
  else if (language == KWD_TRANSLATE_FILE_CPP) {
    return (KWD_TRANSLATE_FILE_CPP_CODE);
  }
  else {
    return (language);
  }
}

const char* rerootFileName(const char* file, const char* fromroot, const char* toroot) {
  { boolean absoluteP = stringSearch(file, fromroot, 0) == 0;

    if (absoluteP) {
      if (stringEqlP(fromroot, toroot)) {
        return (file);
      }
      else {
        return (stringConcatenate(toroot, stringSubsequence(file, strlen(fromroot), NULL_INTEGER), 0));
      }
    }
    else {
      return (stringConcatenate(toroot, file, 0));
    }
  }
}

BooleanWrapper* fileYoungerThanP(const char* file1, const char* file2) {
  if ((!probeFileP(file1)) ||
      (!probeFileP(file2))) {
    return (NULL);
  }
  else {
    { CalendarDate* file1Date = fileWriteDate(file1);
      CalendarDate* file2Date = fileWriteDate(file2);

      if ((!((boolean)(file1Date))) ||
          (!((boolean)(file2Date)))) {
        return (NULL);
      }
      else {
        return ((file1Date->greaterEqualP(file2Date) ? TRUE_WRAPPER : FALSE_WRAPPER));
      }
    }
  }
}

boolean stellaNeedToTranslateP(Object* file, Keyword* language) {
  if (language == KWD_TRANSLATE_FILE_JAVA) {
    return (true);
  }
  { const char* sourcefile = makeFileName(((StringWrapper*)(file))->wrapperValue, KWD_TRANSLATE_FILE_STELLA, true);
    const char* translatedfile = makeFileName(((StringWrapper*)(file))->wrapperValue, languageToFileType(language), true);

    return (probeFileP(sourcefile) &&
        (!(fileYoungerThanP(translatedfile, sourcefile) == TRUE_WRAPPER)));
  }
}

boolean stellaNeedToCompileP(Object* file) {
  { const char* sourcefile = makeFileName(((StringWrapper*)(file))->wrapperValue, KWD_TRANSLATE_FILE_LISP, true);
    const char* compiledfile = makeFileName(((StringWrapper*)(file))->wrapperValue, KWD_TRANSLATE_FILE_LISP_BINARY, true);

    return (!(fileYoungerThanP(compiledfile, sourcefile) == TRUE_WRAPPER));
  }
}

boolean systemNeedsTranslationP(const char* systemname, Keyword* language) {
  { 
    BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONo, SystemDefinition*, getSystemDefinition(systemname, true));
    BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo, const char*, oCURRENTSYSTEMDEFINITIONo->directory);
    {
      { boolean foundP000 = false;

        { StringWrapper* file = NULL;
          Cons* iter000 = systemDefinitionSourceFiles(oCURRENTSYSTEMDEFINITIONo);

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            file = ((StringWrapper*)(iter000->value));
            if (stellaNeedToTranslateP(file, language)) {
              foundP000 = true;
              break;
            }
          }
        }
        if (foundP000) {
          return (true);
        }
      }
      { const char* startupFile = systemStartupFileName(NULL);

        if (!(probeFileP(makeFileName(startupFile, KWD_TRANSLATE_FILE_STELLA, true)))) {
          return (true);
        }
        return (stellaNeedToTranslateP(wrapString(startupFile), language));
      }
    }
  }
}

Module* computeFileUnitsModule(List* fileunits) {
  { TranslationUnit* unit = NULL;
    Cons* iter000 = fileunits->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      unit = ((TranslationUnit*)(iter000->value));
      if (((boolean)(unit->tuHomeModule))) {
        return (unit->tuHomeModule);
      }
    }
  }
  return (oMODULEo);
}

List* concatenateSystemUnits(KeyValueList* systemunits) {
  { Cons* head = cons(NULL, NIL);
    Cons* cursor = head;

    { StringWrapper* file = NULL;
      List* units = NULL;
      KvCons* iter000 = systemunits->theKvList;

      for  (; ((boolean)(iter000)); 
            iter000 = iter000->rest) {
        file = ((StringWrapper*)(iter000->key));
        units = ((List*)(iter000->value));
        file = file;
        if (units->nonEmptyP()) {
          cursor->concatenate(units->theConsList, 0);
          cursor = units->theConsList;
        }
      }
    }
    { List* self000 = newList();

      self000->theConsList = head->rest;
      { List* value000 = self000;

        return (value000);
      }
    }
  }
}

boolean translateSystem(const char* systemname, Cons* languageAoptions) {
  // Translate all of the STELLA source files in system `systemName' into
  // `language' (the optional first argument).  The following keyword/value
  // `options' are recognized:
  // 
  // `:language': can be used as an alternative to the optional language argument.
  // If not specified, the language of the running implementation is assumed.
  // 
  // `:two-pass?' (default false): if true, all files will be scanned twice, once
  // to load the signatures of objects defined in them, and once to actually
  // translate the definitions.
  // 
  // `:force-translation?' (default false): if true, files will be translated
  // whether or not their translations are up-to-date.
  // 
  // `:development-settings?' (default false): if true translation will favor
  // safe, readable and debuggable code over efficiency (according to the value
  // of `:development-settings' on the system definition).  If false, efficiency
  // will be favored instead (according to the value of `:production-settings'
  // on the system definition).
  // 
  // `:production-settings?' (default true): inverse to `:development-settings?'.
  // 
  // `:recursive?' (default false): if true, perform `translate-system' with the provided
  // options on `systemName' as well as all its required systems and so on.  Required
  // systems will be processed first.  Note that even without this option, any required
  // systems that have not yet been loaded or started up will also be processed, since
  // that is assumed when loading `systemName' and supporting modules from a definition file.
  // 
  // `:root-source-directory', `:root-native-directory', `:root-binary-directory': if
  // specified these directories will be used to override the respective paths provided
  // in system definitions or computed as defaults from a system's home location.
  { Cons* options = languageAoptions;

    if (!(getQuotedTree("((:COMMON-LISP :CPP :JAVA) \"/STELLA\")", "/STELLA")->memberP(options->value))) {
      options = cons(runningInLanguage(), options);
    }
    { PropertyList* theoptions = parseOptions(options->rest, listO(23, KWD_TRANSLATE_FILE_TWO_PASSp, SGT_TRANSLATE_FILE_STELLA_BOOLEAN, KWD_TRANSLATE_FILE_DEVELOPMENT_SETTINGSp, SGT_TRANSLATE_FILE_STELLA_BOOLEAN, KWD_TRANSLATE_FILE_PRODUCTION_SETTINGSp, SGT_TRANSLATE_FILE_STELLA_BOOLEAN, KWD_TRANSLATE_FILE_FORCE_TRANSLATIONp, SGT_TRANSLATE_FILE_STELLA_BOOLEAN, KWD_TRANSLATE_FILE_RECURSIVEp, SGT_TRANSLATE_FILE_STELLA_BOOLEAN, KWD_TRANSLATE_FILE_LANGUAGE, SGT_TRANSLATE_FILE_STELLA_KEYWORD, KWD_TRANSLATE_FILE_ACTION, SGT_TRANSLATE_FILE_STELLA_KEYWORD, KWD_TRANSLATE_FILE_ROOT_SOURCE_DIRECTORY, SGT_TRANSLATE_FILE_STELLA_FILE_NAME, KWD_TRANSLATE_FILE_ROOT_NATIVE_DIRECTORY, SGT_TRANSLATE_FILE_STELLA_FILE_NAME, KWD_TRANSLATE_FILE_ROOT_BINARY_DIRECTORY, SGT_TRANSLATE_FILE_STELLA_FILE_NAME, KWD_TRANSLATE_FILE_PROCESSED, SGT_TRANSLATE_FILE_STELLA_LIST, NIL), true, false);
      Keyword* language = ((Keyword*)(theoptions->lookupWithDefault(KWD_TRANSLATE_FILE_LANGUAGE, options->value)));
      boolean twopassP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_TRANSLATE_FILE_TWO_PASSp, ((!systemLoadedOrStartedUpP(systemname)) ? TRUE_WRAPPER : FALSE_WRAPPER)))));
      boolean productionmodeP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_TRANSLATE_FILE_PRODUCTION_SETTINGSp, TRUE_WRAPPER)))) ||
          (!coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_TRANSLATE_FILE_DEVELOPMENT_SETTINGSp, FALSE_WRAPPER)))));
      boolean forcetranslationP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_TRANSLATE_FILE_FORCE_TRANSLATIONp, FALSE_WRAPPER))));
      boolean recursiveP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_TRANSLATE_FILE_RECURSIVEp, FALSE_WRAPPER))));
      List* processed = ((List*)(theoptions->lookupWithDefault(KWD_TRANSLATE_FILE_PROCESSED, list(0))));
      Object* action = theoptions->lookupWithDefault(KWD_TRANSLATE_FILE_ACTION, KWD_TRANSLATE_FILE_TRANSLATE_SYSTEM);
      boolean translatedsomethingP = false;
      int oldgensymcounter = oGENSYM_COUNTERo;

      theoptions->insertAt(KWD_TRANSLATE_FILE_LANGUAGE, language);
      theoptions->insertAt(KWD_TRANSLATE_FILE_ACTION, action);
      theoptions->insertAt(KWD_TRANSLATE_FILE_PROCESSED, processed);
      try {
        { 
          BIND_STELLA_SPECIAL(oTRANSLATOROUTPUTLANGUAGEo, Keyword*, oTRANSLATOROUTPUTLANGUAGEo);
          BIND_STELLA_SPECIAL(oTRANSLATIONPHASEo, Keyword*, NULL);
          BIND_STELLA_SPECIAL(oSAFETYo, int, oSAFETYo);
          BIND_STELLA_SPECIAL(oRECYCLING_ENABLEDpo, boolean, !(language == KWD_TRANSLATE_FILE_JAVA));
          BIND_STELLA_SPECIAL(oCURRENT_STELLA_FEATURESo, List*, oCURRENT_STELLA_FEATURESo->copy());
          BIND_STELLA_SPECIAL(oCURRENT_SYSTEM_ACTIONo, PropertyList*, theoptions);
          { 
            BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONo, SystemDefinition*, getSystemDefinition(systemname, true));
            BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo, const char*, oCURRENTSYSTEMDEFINITIONo->directory);
            {
              processed->insertNew(wrapString(systemname));
              if (recursiveP &&
                  ((boolean)(oCURRENTSYSTEMDEFINITIONo->requiredSystems))) {
                { StringWrapper* reqsys = NULL;
                  Cons* iter000 = oCURRENTSYSTEMDEFINITIONo->requiredSystems;

                  for (; !(iter000 == NIL); iter000 = iter000->rest) {
                    reqsys = ((StringWrapper*)(iter000->value));
                    if (!processed->memberP(reqsys)) {
                      std::cout << "Translating required system " << "`" << unwrapString(reqsys) << "'" << std::endl;
                      translateSystem(reqsys->wrapperValue, consList(2, KWD_TRANSLATE_FILE_OPTIONS, theoptions));
                    }
                  }
                }
              }
              oGENSYM_COUNTERo = -1;
              setStellaFeature(consList(3, KWD_TRANSLATE_FILE_TRANSLATE_WITH_COPYRIGHT_HEADER, KWD_TRANSLATE_FILE_WARN_ABOUT_MISSING_METHODS, KWD_TRANSLATE_FILE_WARN_ABOUT_UNDEFINED_METHODS));
              unsetStellaFeature(consList(1, KWD_TRANSLATE_FILE_USE_HARDCODED_SYMBOLS));
              setTranslatorOutputLanguage(language);
              computeOptimizationLevels(oCURRENTSYSTEMDEFINITIONo, productionmodeP);
              if (forcetranslationP ||
                  systemNeedsTranslationP(systemname, language)) {
                createSystemStartupFile(oCURRENTSYSTEMDEFINITIONo);
                translatedsomethingP = helpTranslateSystem(filesPlusSystemStartup(systemDefinitionSourceFiles(oCURRENTSYSTEMDEFINITIONo)), twopassP, forcetranslationP);
              }
              transferNativeSystemFiles(language);
              transferDataFiles(language);
            }
          }
        }
      }
catch (...) {
        oGENSYM_COUNTERo = oldgensymcounter;
        throw;
      }
      oGENSYM_COUNTERo = oldgensymcounter;
      return (translatedsomethingP);
    }
  }
}

BooleanWrapper* translateSystemEvaluatorWrapper(Cons* arguments) {
  return ((translateSystem(((StringWrapper*)(arguments->value))->wrapperValue, arguments->rest) ? TRUE_WRAPPER : FALSE_WRAPPER));
}

boolean helpTranslateSystem(Cons* files, boolean twopassP, boolean forcetranslationP) {
  { 
    BIND_STELLA_SPECIAL(oTRANSLATIONUNITSo, List*, newList());
    { Keyword* outputlanguage = oTRANSLATOROUTPUTLANGUAGEo;
      const char* filename = NULL;
      boolean translatedfileP = false;
      KeyValueList* walkedunits = newKeyValueList();

      clearSymbolRegistry();
      if (twopassP) {
        { StringWrapper* file = NULL;
          Cons* iter000 = files;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            file = ((StringWrapper*)(iter000->value));
            if (forcetranslationP ||
                (stellaNeedToTranslateP(file, outputlanguage) ||
                 (!oCURRENTSYSTEMDEFINITIONo->loadedP))) {
              filename = makeFileName(file->wrapperValue, KWD_TRANSLATE_FILE_STELLA, true);
              if (!(probeFileP(filename))) {
                std::cout << "Warning: File " << "`" << filename << "'" << " does not exist." << std::endl;
                continue;
              }
              operateOnFile(filename, KWD_TRANSLATE_FILE_DEFINE);
              cleanUpTranslationUnitsSpecial();
              translatedfileP = true;
            }
          }
        }
        if (translatedfileP) {
          if (oTRANSLATIONVERBOSITYLEVELo >= 1) {
            std::cout << "*** Pass 2, finalizing objects..." << std::endl;
          }
          finalizeClassesAndSlots();
        }
      }
      { StringWrapper* file = NULL;
        Cons* iter001 = files;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          file = ((StringWrapper*)(iter001->value));
          if (forcetranslationP ||
              stellaNeedToTranslateP(file, outputlanguage)) {
            filename = makeFileName(file->wrapperValue, KWD_TRANSLATE_FILE_STELLA, true);
            if (!(probeFileP(filename))) {
              std::cout << "Warning: File " << "`" << filename << "'" << " does not exist." << std::endl;
              continue;
            }
            operateOnFile(filename, KWD_TRANSLATE_FILE_WALK);
            walkedunits->insertAt(wrapString(filename), oTRANSLATIONUNITSo);
            oTRANSLATIONUNITSo = newList();
          }
        }
      }
      walkedunits->reverse();
      if (oTRANSLATIONVERBOSITYLEVELo >= 1) {
        std::cout << "    ==============================" << std::endl;
      }
      if (outputlanguage == KWD_TRANSLATE_FILE_COMMON_LISP) {
        clTranslateWalkedSystemUnits(walkedunits);
      }
      else if (outputlanguage == KWD_TRANSLATE_FILE_CPP) {
        cppTranslateWalkedSystemUnits(walkedunits);
      }
      else if (outputlanguage == KWD_TRANSLATE_FILE_JAVA) {
        javaTranslateWalkedSystemUnits(walkedunits);
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << outputlanguage << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      clearSymbolRegistry();
      return (translatedfileP);
    }
  }
}

void transferNativeSystemFiles(Keyword* outputLanguage) {
  { Cons* nativeFiles = NULL;

    if (outputLanguage == KWD_TRANSLATE_FILE_COMMON_LISP) {
      nativeFiles = oCURRENTSYSTEMDEFINITIONo->lispOnlyFiles;
    }
    else if (outputLanguage == KWD_TRANSLATE_FILE_JAVA) {
      nativeFiles = oCURRENTSYSTEMDEFINITIONo->javaOnlyFiles;
    }
    else if (outputLanguage == KWD_TRANSLATE_FILE_CPP) {
      nativeFiles = oCURRENTSYSTEMDEFINITIONo->cppOnlyFiles;
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << outputLanguage << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    if (((boolean)(nativeFiles))) {
      nativeFiles = nativeFiles->difference(systemDefinitionSourceFiles(oCURRENTSYSTEMDEFINITIONo));
      transferFiles(nativeFiles, outputLanguage);
    }
  }
}

void transferDataFiles(Keyword* outputLanguage) {
  { Cons* dataFiles = oCURRENTSYSTEMDEFINITIONo->dataFiles;

    if (((boolean)(dataFiles))) {
      transferFiles(dataFiles, outputLanguage);
    }
  }
}

void transferFiles(Cons* files, Keyword* outputLanguage) {
  if (stringEqlP(rootSourceDirectory(), rootNativeDirectory())) {
    return;
  }
  { const char* flotsamfilename = "";
    const char* systemSubDirectory = (stringEqlP(oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo, "") ? "" : fileNameAsDirectory(oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo));

    if (outputLanguage == KWD_TRANSLATE_FILE_JAVA) {
      flotsamfilename = javaYieldFlotsamClassName(getCardinalModule(oCURRENTSYSTEMDEFINITIONo));
    }
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, getCardinalModule(oCURRENTSYSTEMDEFINITIONo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      { StringWrapper* f = NULL;
        Cons* iter000 = files;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          f = ((StringWrapper*)(iter000->value));
          { const char* filename = f->wrapperValue;
            Keyword* type = classifyFileExtension(filename);
            const char* relativefilename = relativizeFileName(filename, rootSourceDirectory());
            const char* fromfilename = NULL;
            const char* tofilename = NULL;

            if (type == KWD_TRANSLATE_FILE_JAVA) {
              if (stringEqlP(fileBaseName(filename), flotsamfilename)) {
                *(STANDARD_WARNING->nativeStream) << "Warning: " << "Native Java filename " << "`" << flotsamfilename << "'" << std::endl << " conflicts with the Java catchall class' filename" << std::endl;
              }
            }
            else {
            }
            fromfilename = concatenateFileNames(rootSourceDirectory(), 2, systemSubDirectory, filename);
            tofilename = makeFileName(relativefilename, type, true);
            if (!(fileYoungerThanP(tofilename, fromfilename) == TRUE_WRAPPER)) {
              if (oTRANSLATIONVERBOSITYLEVELo >= 1) {
                std::cout << "Copying " << "`" << fromfilename << "'" << std::endl << " to " << "`" << tofilename << "'" << " ..." << std::endl;
              }
              ensureDirectoriesExist(tofilename);
              copyFile(fromfilename, tofilename);
            }
          }
        }
      }
    }
  }
}

void helpStartupTranslateFile1() {
  {
    KWD_TRANSLATE_FILE_ROOT_SOURCE_DIRECTORY = ((Keyword*)(internRigidSymbolWrtModule("ROOT-SOURCE-DIRECTORY", NULL, 2)));
    KWD_TRANSLATE_FILE_ROOT_NATIVE_DIRECTORY = ((Keyword*)(internRigidSymbolWrtModule("ROOT-NATIVE-DIRECTORY", NULL, 2)));
    KWD_TRANSLATE_FILE_ROOT_BINARY_DIRECTORY = ((Keyword*)(internRigidSymbolWrtModule("ROOT-BINARY-DIRECTORY", NULL, 2)));
    KWD_TRANSLATE_FILE_TRANSLATE = ((Keyword*)(internRigidSymbolWrtModule("TRANSLATE", NULL, 2)));
    KWD_TRANSLATE_FILE_JAVA = ((Keyword*)(internRigidSymbolWrtModule("JAVA", NULL, 2)));
    KWD_TRANSLATE_FILE_COMMON_LISP = ((Keyword*)(internRigidSymbolWrtModule("COMMON-LISP", NULL, 2)));
    KWD_TRANSLATE_FILE_CPP = ((Keyword*)(internRigidSymbolWrtModule("CPP", NULL, 2)));
    KWD_TRANSLATE_FILE_CPP_STANDALONE = ((Keyword*)(internRigidSymbolWrtModule("CPP-STANDALONE", NULL, 2)));
    KWD_TRANSLATE_FILE_IDL = ((Keyword*)(internRigidSymbolWrtModule("IDL", NULL, 2)));
    SGT_TRANSLATE_FILE_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    KWD_TRANSLATE_FILE_DEFINE = ((Keyword*)(internRigidSymbolWrtModule("DEFINE", NULL, 2)));
    KWD_TRANSLATE_FILE_FINALIZE = ((Keyword*)(internRigidSymbolWrtModule("FINALIZE", NULL, 2)));
    KWD_TRANSLATE_FILE_WALK = ((Keyword*)(internRigidSymbolWrtModule("WALK", NULL, 2)));
    KWD_TRANSLATE_FILE_TRANSLATE_WITH_COPYRIGHT_HEADER = ((Keyword*)(internRigidSymbolWrtModule("TRANSLATE-WITH-COPYRIGHT-HEADER", NULL, 2)));
    KWD_TRANSLATE_FILE_WINDOWS = ((Keyword*)(internRigidSymbolWrtModule("WINDOWS", NULL, 2)));
    KWD_TRANSLATE_FILE_UNIX = ((Keyword*)(internRigidSymbolWrtModule("UNIX", NULL, 2)));
    KWD_TRANSLATE_FILE_MAC = ((Keyword*)(internRigidSymbolWrtModule("MAC", NULL, 2)));
    KWD_TRANSLATE_FILE_LETTER = ((Keyword*)(internRigidSymbolWrtModule("LETTER", NULL, 2)));
    KWD_TRANSLATE_FILE_ROOT_DIRECTORY = ((Keyword*)(internRigidSymbolWrtModule("ROOT-DIRECTORY", NULL, 2)));
    KWD_TRANSLATE_FILE_LISP_TRANSLATIONS = ((Keyword*)(internRigidSymbolWrtModule("LISP-TRANSLATIONS", NULL, 2)));
    SGT_TRANSLATE_FILE_STELLA_KEYWORD = ((Surrogate*)(internRigidSymbolWrtModule("KEYWORD", NULL, 1)));
    KWD_TRANSLATE_FILE_STELLA = ((Keyword*)(internRigidSymbolWrtModule("STELLA", NULL, 2)));
    KWD_TRANSLATE_FILE_KB = ((Keyword*)(internRigidSymbolWrtModule("KB", NULL, 2)));
    KWD_TRANSLATE_FILE_CPP_CODE = ((Keyword*)(internRigidSymbolWrtModule("CPP-CODE", NULL, 2)));
    KWD_TRANSLATE_FILE_CPP_HEADER = ((Keyword*)(internRigidSymbolWrtModule("CPP-HEADER", NULL, 2)));
    KWD_TRANSLATE_FILE_C_CODE = ((Keyword*)(internRigidSymbolWrtModule("C-CODE", NULL, 2)));
    KWD_TRANSLATE_FILE_C_HEADER = ((Keyword*)(internRigidSymbolWrtModule("C-HEADER", NULL, 2)));
    KWD_TRANSLATE_FILE_OTHER = ((Keyword*)(internRigidSymbolWrtModule("OTHER", NULL, 2)));
    KWD_TRANSLATE_FILE_NONE = ((Keyword*)(internRigidSymbolWrtModule("NONE", NULL, 2)));
    KWD_TRANSLATE_FILE_LISP_BINARY = ((Keyword*)(internRigidSymbolWrtModule("LISP-BINARY", NULL, 2)));
    KWD_TRANSLATE_FILE_USE_COMMON_LISP_STRUCTS = ((Keyword*)(internRigidSymbolWrtModule("USE-COMMON-LISP-STRUCTS", NULL, 2)));
    KWD_TRANSLATE_FILE_USE_COMMON_LISP_VECTOR_STRUCTS = ((Keyword*)(internRigidSymbolWrtModule("USE-COMMON-LISP-VECTOR-STRUCTS", NULL, 2)));
    KWD_TRANSLATE_FILE_LISP = ((Keyword*)(internRigidSymbolWrtModule("LISP", NULL, 2)));
    KWD_TRANSLATE_FILE_DIRECTORY = ((Keyword*)(internRigidSymbolWrtModule("DIRECTORY", NULL, 2)));
    KWD_TRANSLATE_FILE_JAVAC = ((Keyword*)(internRigidSymbolWrtModule("JAVAC", NULL, 2)));
    KWD_TRANSLATE_FILE_MAVEN = ((Keyword*)(internRigidSymbolWrtModule("MAVEN", NULL, 2)));
    SYM_TRANSLATE_FILE_STELLA_SYSTEM_UNITS_ALIST = ((Symbol*)(internRigidSymbolWrtModule("SYSTEM-UNITS-ALIST", NULL, 0)));
    KWD_TRANSLATE_FILE_TWO_PASSp = ((Keyword*)(internRigidSymbolWrtModule("TWO-PASS?", NULL, 2)));
    SGT_TRANSLATE_FILE_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 1)));
    KWD_TRANSLATE_FILE_DEVELOPMENT_SETTINGSp = ((Keyword*)(internRigidSymbolWrtModule("DEVELOPMENT-SETTINGS?", NULL, 2)));
    KWD_TRANSLATE_FILE_PRODUCTION_SETTINGSp = ((Keyword*)(internRigidSymbolWrtModule("PRODUCTION-SETTINGS?", NULL, 2)));
    KWD_TRANSLATE_FILE_FORCE_TRANSLATIONp = ((Keyword*)(internRigidSymbolWrtModule("FORCE-TRANSLATION?", NULL, 2)));
    KWD_TRANSLATE_FILE_RECURSIVEp = ((Keyword*)(internRigidSymbolWrtModule("RECURSIVE?", NULL, 2)));
    KWD_TRANSLATE_FILE_LANGUAGE = ((Keyword*)(internRigidSymbolWrtModule("LANGUAGE", NULL, 2)));
    KWD_TRANSLATE_FILE_ACTION = ((Keyword*)(internRigidSymbolWrtModule("ACTION", NULL, 2)));
    SGT_TRANSLATE_FILE_STELLA_FILE_NAME = ((Surrogate*)(internRigidSymbolWrtModule("FILE-NAME", NULL, 1)));
    KWD_TRANSLATE_FILE_PROCESSED = ((Keyword*)(internRigidSymbolWrtModule("PROCESSED", NULL, 2)));
    SGT_TRANSLATE_FILE_STELLA_LIST = ((Surrogate*)(internRigidSymbolWrtModule("LIST", NULL, 1)));
    KWD_TRANSLATE_FILE_TRANSLATE_SYSTEM = ((Keyword*)(internRigidSymbolWrtModule("TRANSLATE-SYSTEM", NULL, 2)));
    KWD_TRANSLATE_FILE_OPTIONS = ((Keyword*)(internRigidSymbolWrtModule("OPTIONS", NULL, 2)));
    KWD_TRANSLATE_FILE_WARN_ABOUT_MISSING_METHODS = ((Keyword*)(internRigidSymbolWrtModule("WARN-ABOUT-MISSING-METHODS", NULL, 2)));
    KWD_TRANSLATE_FILE_WARN_ABOUT_UNDEFINED_METHODS = ((Keyword*)(internRigidSymbolWrtModule("WARN-ABOUT-UNDEFINED-METHODS", NULL, 2)));
    KWD_TRANSLATE_FILE_USE_HARDCODED_SYMBOLS = ((Keyword*)(internRigidSymbolWrtModule("USE-HARDCODED-SYMBOLS", NULL, 2)));
    SYM_TRANSLATE_FILE_STELLA_STARTUP_TRANSLATE_FILE = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-TRANSLATE-FILE", NULL, 0)));
    SYM_TRANSLATE_FILE_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupTranslateFile2() {
  {
    defineFunctionObject("ROOT-SOURCE-DIRECTORY", "(DEFUN (ROOT-SOURCE-DIRECTORY FILE-NAME) () :DOCUMENTATION \"Accessor to determine the currently active sources directory root.\nIf it is defined as an option in the currently active system action, use that.\nIf we have an active system, use its value, otherwise use the STELLA default value.\" :PUBLIC? TRUE)", ((cpp_function_code)(&rootSourceDirectory)), NULL);
    defineFunctionObject("ROOT-NATIVE-DIRECTORY", "(DEFUN (ROOT-NATIVE-DIRECTORY FILE-NAME) () :DOCUMENTATION \"Accessor to determine the currently active native directory root.\nIf it is defined as an option in the currently active system action, use that.\nIf we have an active system, use its value, otherwise use the STELLA default value.\" :PUBLIC? TRUE)", ((cpp_function_code)(&rootNativeDirectory)), NULL);
    defineFunctionObject("ROOT-BINARY-DIRECTORY", "(DEFUN (ROOT-BINARY-DIRECTORY FILE-NAME) () :DOCUMENTATION \"Accessor to determine the currently active binary directory root.\nIf it is defined as an option in the currently active system action, use that.\nIf we have an active system, use its value, otherwise use the STELLA default value.\" :PUBLIC? TRUE)", ((cpp_function_code)(&rootBinaryDirectory)), NULL);
    defineFunctionObject("SYSTEM-DEFINITION-DIRECTORIES", "(DEFUN (SYSTEM-DEFINITION-DIRECTORIES (CONS OF STRING-WRAPPER)) ())", ((cpp_function_code)(&systemDefinitionDirectories)), NULL);
    defineFunctionObject("TOP-LEVEL-STELLA-SYSTEM-DIRECTORY?", "(DEFUN (TOP-LEVEL-STELLA-SYSTEM-DIRECTORY? BOOLEAN) ((DIRECTORY FILE-NAME)) :DOCUMENTATION \"Return TRUE if `directory' is a top-level STELLA installation directory\ncontaining one or more STELLA systems.  We currently determine this solely by looking\nfor the existence of at least one relevant top-level native directory.  This is needed\nto find system root directories and other relevant STELLA installation directories.\" :PUBLIC? TRUE)", ((cpp_function_code)(&topLevelStellaSystemDirectoryP)), NULL);
    defineFunctionObject("HANDLE-IN-MODULE-TREE", "(DEFUN (HANDLE-IN-MODULE-TREE BOOLEAN BOOLEAN) ((TREE CONS) (SEENINMODULE? BOOLEAN) (ERRORONINMODULE? BOOLEAN)) :PUBLIC? TRUE)", ((cpp_function_code)(&handleInModuleTree)), NULL);
    defineFunctionObject("TRANSLATE-AND-OUTPUT-UNITS-TO-FILE", "(DEFUN TRANSLATE-AND-OUTPUT-UNITS-TO-FILE ((FILE FILE-NAME) (TARGETLANGUAGE STRING)))", ((cpp_function_code)(&translateAndOutputUnitsToFile)), NULL);
    defineFunctionObject("OPERATE-ON-FILE", "(DEFUN OPERATE-ON-FILE ((FILE FILE-NAME) (OPERATION KEYWORD)))", ((cpp_function_code)(&operateOnFile)), NULL);
    defineFunctionObject("CLEAN-UP-TRANSLATION-UNITS-SPECIAL", "(DEFUN CLEAN-UP-TRANSLATION-UNITS-SPECIAL ())", ((cpp_function_code)(&cleanUpTranslationUnitsSpecial)), NULL);
    defineFunctionObject("TRANSLATE-FILE", "(DEFUN TRANSLATE-FILE ((FILE FILE-NAME) (OUTPUTLANGUAGE KEYWORD) (ASPARTOFSYSTEM? BOOLEAN)))", ((cpp_function_code)(&translateFile)), NULL);
    defineFunctionObject("OUTPUT-ALL-UNITS-TO-FILE", "(DEFUN OUTPUT-ALL-UNITS-TO-FILE ((SOURCEFILE FILE-NAME)))", ((cpp_function_code)(&outputAllUnitsToFile)), NULL);
    defineFunctionObject("RECORD-SIGNATURES-OF-ALL-UNITS", "(DEFUN RECORD-SIGNATURES-OF-ALL-UNITS ((SOURCEFILE FILE-NAME)))", ((cpp_function_code)(&recordSignaturesOfAllUnits)), NULL);
    defineFunctionObject("TRANSLATE-WITH-COPYRIGHT-HEADER?", "(DEFUN (TRANSLATE-WITH-COPYRIGHT-HEADER? BOOLEAN) ())", ((cpp_function_code)(&translateWithCopyrightHeaderP)), NULL);
    defineFunctionObject("OUTPUT-COPYRIGHT-HEADER", "(DEFUN OUTPUT-COPYRIGHT-HEADER ((STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&outputCopyrightHeader)), NULL);
    defineFunctionObject("OUTPUT-FILE-HEADER", "(DEFUN OUTPUT-FILE-HEADER ((STREAM OUTPUT-STREAM) (FILE FILE-NAME)))", ((cpp_function_code)(&outputFileHeader)), NULL);
    defineFunctionObject("OPERATING-SYSTEM", "(DEFUN (OPERATING-SYSTEM KEYWORD) ())", ((cpp_function_code)(&operatingSystem)), NULL);
    defineFunctionObject("DIRECTORY-SEPARATOR", "(DEFUN (DIRECTORY-SEPARATOR CHARACTER) ())", ((cpp_function_code)(&directorySeparator)), NULL);
    defineFunctionObject("DIRECTORY-SEPARATOR-STRING", "(DEFUN (DIRECTORY-SEPARATOR-STRING STRING) ())", ((cpp_function_code)(&directorySeparatorString)), NULL);
    defineFunctionObject("DIRECTORY-SEPARATOR-FOR-FILE", "(DEFUN (DIRECTORY-SEPARATOR-FOR-FILE CHARACTER) ((FILE FILE-NAME)))", ((cpp_function_code)(&directorySeparatorForFile)), NULL);
    defineFunctionObject("FILE-NAME-DIRECTORY", "(DEFUN (FILE-NAME-DIRECTORY FILE-NAME) ((FILE FILE-NAME)) :DOCUMENTATION \"Return the directory component of `file' including the final\ndirectory separator or the empty string if `file' does not include a directory.\nNote that for purposes of this function, a logical host is considered part of\nthe directory portion of `file'\" :PUBLIC? TRUE)", ((cpp_function_code)(((const char*  (*) (const char*))(&fileNameDirectory)))), NULL);
    defineFunctionObject("DIRECTORY-FILE-NAME", "(DEFUN (DIRECTORY-FILE-NAME FILE-NAME) ((DIRECTORY FILE-NAME)) :DOCUMENTATION \"Return `directory' as a file name, i.e., without a terminating\ndirectory separator.\" :PUBLIC? TRUE)", ((cpp_function_code)(&directoryFileName)), NULL);
    defineFunctionObject("FILE-NAME-AS-DIRECTORY", "(DEFUN (FILE-NAME-AS-DIRECTORY FILE-NAME) ((FILE FILE-NAME)) :DOCUMENTATION \"Return `file' interpreted as a directory, i.e., with a\nterminating directory separator.  If `file' is the empty string simply\nreturn the empty string, i.e., interpret it as the current directory instead\nof the root directory.\" :PUBLIC? TRUE)", ((cpp_function_code)(((const char*  (*) (const char*))(&fileNameAsDirectory)))), NULL);
    defineFunctionObject("DIRECTORY-PARENT-DIRECTORY", "(DEFUN (DIRECTORY-PARENT-DIRECTORY FILE-NAME) ((DIRECTORY FILE-NAME) (LEVEL INTEGER)) :DOCUMENTATION \"Return the `level'-th parent directory component of `directory'\nincluding the final directory separator, or the empty string if `directory' does\nnot have that many parents.\" :PUBLIC? TRUE)", ((cpp_function_code)(&directoryParentDirectory)), NULL);
    defineFunctionObject("FILE-NAME-WITHOUT-DEVICE", "(DEFUN (FILE-NAME-WITHOUT-DEVICE FILE-NAME) ((FILE FILE-NAME)) :DOCUMENTATION \"Return the file name portion of `file' by removing any\nphysical device components.  This is just like `logical-pathname-without-host'\nbut only looks for one-character device strings as used in Windows.\" :PUBLIC? TRUE)", ((cpp_function_code)(((const char*  (*) (const char*))(&fileNameWithoutDevice)))), NULL);
    defineFunctionObject("FILE-NAME-WITHOUT-DIRECTORY", "(DEFUN (FILE-NAME-WITHOUT-DIRECTORY FILE-NAME) ((FILE FILE-NAME)) :DOCUMENTATION \"Return the file name portion of `file' by removing any\ndirectory and logical host components.\" :PUBLIC? TRUE)", ((cpp_function_code)(((const char*  (*) (const char*))(&fileNameWithoutDirectory)))), NULL);
    defineFunctionObject("FILE-NAME-WITHOUT-EXTENSION", "(DEFUN (FILE-NAME-WITHOUT-EXTENSION FILE-NAME) ((FILE FILE-NAME)) :DOCUMENTATION \"Remove `file's extension (or type) if there is any and\nreturn the result.\" :PUBLIC? TRUE)", ((cpp_function_code)(((const char*  (*) (const char*))(&fileNameWithoutExtension)))), NULL);
    defineFunctionObject("FILE-EXTENSION", "(DEFUN (FILE-EXTENSION STRING) ((FILE FILE-NAME)) :DOCUMENTATION \"Return `file's extension (or type) if it has any including\nthe separator character.\" :PUBLIC? TRUE)", ((cpp_function_code)(&fileExtension)), NULL);
    defineFunctionObject("FILE-BASE-NAME", "(DEFUN (FILE-BASE-NAME FILE-NAME) ((FILE FILE-NAME)) :DOCUMENTATION \"Remove `file's directory (including logical host) and\nextension components and return the result.\" :PUBLIC? TRUE)", ((cpp_function_code)(&fileBaseName)), NULL);
    defineFunctionObject("DEFINE-LOGICAL-HOST-PROPERTY", "(DEFUN DEFINE-LOGICAL-HOST-PROPERTY ((HOST STRING) (PROPERTY KEYWORD) (VALUE OBJECT)) :DOCUMENTATION \"Define `property' with `value' for the logical host `host'.\nAs a side-effect, this also defines `host' as a logical host (both\n`property' and `value' can be supplied as NULL).  If :ROOT-DIRECTORY\nis specified, all pathnames with `host' are assumed to be relative to\nthat directory (even if they are absolute) and will be rerooted upon\ntranslation.  :ROOT-DIRECTORY can be a logical or physical pathname.\nIf :LISP-TRANSLATIONS is specified, those will be used verbatimely as\nthe value of `(CL:logical-pathname-translations host)' if we are\nrunning in Lisp, which allows us to depend on the native\n`CL:translate-logical-pathname' for more complex translation operations.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&defineLogicalHostProperty)), ((cpp_function_code)(&defineLogicalHostPropertyEvaluatorWrapper)));
    defineFunctionObject("LOOKUP-LOGICAL-HOST-PROPERTY", "(DEFUN (LOOKUP-LOGICAL-HOST-PROPERTY OBJECT) ((HOST STRING) (PROPERTY KEYWORD)))", ((cpp_function_code)(&lookupLogicalHostProperty)), NULL);
    defineFunctionObject("GET-LOGICAL-HOST-PROPERTY", "(DEFUN (GET-LOGICAL-HOST-PROPERTY OBJECT) ((HOST OBJECT) (PROPERTY OBJECT)) :DOCUMENTATION \"Lookup the value of `property' for the logical host `host'.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&getLogicalHostProperty)), NULL);
    defineFunctionObject("LOGICAL-HOST?", "(DEFUN (LOGICAL-HOST? BOOLEAN) ((HOST STRING)))", ((cpp_function_code)(&logicalHostP)), NULL);
    defineFunctionObject("LOGICAL-PATHNAME?", "(DEFUN (LOGICAL-PATHNAME? BOOLEAN) ((PATHNAME STRING)))", ((cpp_function_code)(&logicalPathnameP)), NULL);
    defineFunctionObject("ABSOLUTE-PATHNAME?", "(DEFUN (ABSOLUTE-PATHNAME? BOOLEAN) ((PATHNAME STRING)))", ((cpp_function_code)(&absolutePathnameP)), NULL);
    defineFunctionObject("GET-LOGICAL-HOST-NAME", "(DEFUN (GET-LOGICAL-HOST-NAME STRING) ((PATHNAME STRING)))", ((cpp_function_code)(&getLogicalHostName)), NULL);
    defineFunctionObject("LOGICAL-PATHNAME-WITHOUT-HOST", "(DEFUN (LOGICAL-PATHNAME-WITHOUT-HOST STRING) ((PATHNAME STRING)))", ((cpp_function_code)(&logicalPathnameWithoutHost)), NULL);
    defineFunctionObject("TRANSLATE-LOGICAL-PATHNAME", "(DEFUN (TRANSLATE-LOGICAL-PATHNAME STRING) ((PATHNAME STRING)))", ((cpp_function_code)(&translateLogicalPathname)), NULL);
    defineFunctionObject("UNLOGICALIZE-PATHNAME", "(DEFUN (UNLOGICALIZE-PATHNAME STRING) ((PATHNAME STRING)) :GLOBALLY-INLINE? TRUE (RETURN (TRANSLATE-LOGICAL-PATHNAME PATHNAME)))", ((cpp_function_code)(&unlogicalizePathname)), NULL);
    defineFunctionObject("RELATIVE-UNLOGICALIZE-PATHNAME", "(DEFUN (RELATIVE-UNLOGICALIZE-PATHNAME STRING) ((PATHNAME STRING)) :DOCUMENTATION \"If `pathName' is a logical pathname translate it, however, remove the\n:root-directory prefix of the logical host.  Otherwise, return `pathName' as is.\" :PUBLIC? TRUE)", ((cpp_function_code)(&relativeUnlogicalizePathname)), NULL);
    defineFunctionObject("MERGE-FILE-NAMES", "(DEFUN (MERGE-FILE-NAMES FILE-NAME) ((BASEFILE FILE-NAME) (DEFAULTS FILE-NAME)) :DOCUMENTATION \"Parse `baseFile', supply any missing components from\n`defaults' if supplied and return the result.\" :PUBLIC? TRUE)", ((cpp_function_code)(&mergeFileNames)), NULL);
    defineFunctionObject("CONCATENATE-FILE-NAMES", "(DEFUN (CONCATENATE-FILE-NAMES FILE-NAME) ((FILE FILE-NAME) |&REST| (OTHERFILES FILE-NAME)) :DOCUMENTATION \"Intelligently join `file' and `otherFiles' into a concatenated path where each\ncomponent is separated by a single separator (similar to Python's os.path.join).  Keeps the result\na logical pathname as long as possible, but converts to physical as soon as any of `otherFiles'\ncontain a physical directory separator.\" :PUBLIC? TRUE)", ((cpp_function_code)(&concatenateFileNames)), NULL);
    defineFunctionObject("COMPUTE-COMMON-LISP-FILE-EXTENSION", "(DEFUN (COMPUTE-COMMON-LISP-FILE-EXTENSION STRING) ((TYPE KEYWORD)))", ((cpp_function_code)(&computeCommonLispFileExtension)), NULL);
    defineFunctionObject("DEFAULT-COMMON-LISP-FILE-EXTENSION", "(DEFUN (DEFAULT-COMMON-LISP-FILE-EXTENSION STRING) ((TYPE KEYWORD)))", ((cpp_function_code)(&defaultCommonLispFileExtension)), NULL);
    defineFunctionObject("SELECT-FILE-EXTENSION", "(DEFUN (SELECT-FILE-EXTENSION STRING) ((TYPE KEYWORD)))", ((cpp_function_code)(&selectFileExtension)), NULL);
    defineFunctionObject("CLASSIFY-FILE-EXTENSION", "(DEFUN (CLASSIFY-FILE-EXTENSION KEYWORD) ((FILE FILE-NAME)))", ((cpp_function_code)(&classifyFileExtension)), NULL);
    defineFunctionObject("GET-ROOT-DIRECTORY-FROM-FILE-TYPE", "(DEFUN (GET-ROOT-DIRECTORY-FROM-FILE-TYPE STRING) ((TYPE KEYWORD)) :DOCUMENTATION \"Given a normalized file `type', determine which STELLA installation\nroot directory tree it naturally belongs to (i.e., source, native or binary).\" :PUBLIC? TRUE)", ((cpp_function_code)(&getRootDirectoryFromFileType)), NULL);
    defineFunctionObject("GET-ROOT-DIRECTORY-FROM-FILE-EXTENSION", "(DEFUN (GET-ROOT-DIRECTORY-FROM-FILE-EXTENSION FILE-NAME) ((FILE FILE-NAME)) :DOCUMENTATION \"Given a `file', determine which STELLA installation root directory\ntree it naturally belongs to based on its extension (i.e., source, native or binary).\" :PUBLIC? TRUE)", ((cpp_function_code)(&getRootDirectoryFromFileExtension)), NULL);
    defineFunctionObject("GET-LANGUAGE-SUBDIRECTORY-FROM-FILE-TYPE", "(DEFUN (GET-LANGUAGE-SUBDIRECTORY-FROM-FILE-TYPE STRING) ((TYPE KEYWORD)) :DOCUMENTATION \"Compute a language-specific native subdirectory that should\nbe used for files of `type'.  If `type' does not naturally suggest which native\nlanguage it is associated with, key in on the current translation output language.\nReturns the empty string for unhandled types.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getLanguageSubdirectoryFromFileType)), NULL);
    defineFunctionObject("GET-SYSTEM-SUBDIRECTORY-FROM-FILE-TYPE", "(DEFUN (GET-SYSTEM-SUBDIRECTORY-FROM-FILE-TYPE STRING) ((TYPE KEYWORD)) :DOCUMENTATION \"Compute a native system subdirectory that should be used\nfor files of `type'.  If `type' does not naturally suggest which native language\nit is associated with, key in on the current translation output language.\nReturns the empty string for unhandled types.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getSystemSubdirectoryFromFileType)), NULL);
    defineFunctionObject("GET-NATIVE-SOURCE-SUBDIRECTORY-FROM-FILE-TYPE", "(DEFUN (GET-NATIVE-SOURCE-SUBDIRECTORY-FROM-FILE-TYPE STRING) ((TYPE KEYWORD)) :DOCUMENTATION \"Compute a native source subdirectory that should be used\nfor files of `type'.  If `type' does not naturally suggest which native language\nit is associated with, key in on the current translation output language.\nReturns the empty string for unhandled types.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getNativeSourceSubdirectoryFromFileType)), NULL);
    defineFunctionObject("MAKE-FILE-NAME-FROM-RELATIVE-PATH", "(DEFUN (MAKE-FILE-NAME-FROM-RELATIVE-PATH FILE-NAME) ((FILEPATH OBJECT) (TYPE KEYWORD)))", ((cpp_function_code)(&makeFileNameFromRelativePath)), NULL);
    defineFunctionObject("MAKE-FILE-NAME", "(DEFUN (MAKE-FILE-NAME FILE-NAME) ((FILEPATH STRING) (TYPE KEYWORD) (RELATIVE? BOOLEAN)) :DOCUMENTATION \"Make an absolute file-name string from 'filePath' with directory location\nand file extension determined by 'type' and 'relative?'.  `type' is the main determiner\nfor whether we are creating a source, native or binary pathname in the respective root\ndirectories, and it also controls the new extension of the resulting pathname replacing any\none on `filePath'.  If 'relative?' is TRUE, then the respective root directory prefix is appended,\nplus any additional relevant language, system and source subdirectories.  If 'relative?' is\nFALSE, then the current directory prefix of `filePath' as indicated by its extension is switched\nto the new root directory indicated by `type'.  In this case, only the root and language directories\nare inserted, but all the remaining source directory components are left the same (thus, this will\ngenerally not do the right thing for Java file names).  This function takes the" " dynamic state of\ncurrently active systems and modules into account.\" :PUBLIC? TRUE)", ((cpp_function_code)(&makeFileName)), NULL);
    defineFunctionObject("RELATIVIZE-FILE-NAME", "(DEFUN (RELATIVIZE-FILE-NAME FILE-NAME) ((FILE FILE-NAME) (ROOTPATH FILE-NAME)))", ((cpp_function_code)(&relativizeFileName)), NULL);
    defineFunctionObject("HELP-IMPLODE-PATHNAME", "(DEFUN (HELP-IMPLODE-PATHNAME FILE-NAME) ((FILENAME FILE-NAME)))", ((cpp_function_code)(&helpImplodePathname)), NULL);
    defineFunctionObject("IMPLODE-PATHNAME", "(DEFUN (IMPLODE-PATHNAME FILE-NAME) ((FILEPATH OBJECT)))", ((cpp_function_code)(&implodePathname)), NULL);
    defineFunctionObject("MAYBE-TRUNCATE-FILENAME", "(DEFUN (MAYBE-TRUNCATE-FILENAME FILE-NAME) ((BAREFILENAME FILE-NAME)))", ((cpp_function_code)(&maybeTruncateFilename)), NULL);
    defineFunctionObject("FIND-SOURCE-FROM-NATIVE-FILE-NAME", "(DEFUN (FIND-SOURCE-FROM-NATIVE-FILE-NAME STRING) ((NATIVEFILENAME STRING)) :DOCUMENTATION \"Try to find a STELLA source file based on the name and system components of `nativeFileName'.\nThis will generally search the current STELLA systems path, since the tree where a native file resides is not\nnecessarily the one where the corresponding source file is also.  This will only work for Lisp and C++ files\nwhere the basename of translated files corresponds to the source file from which they were derived.  The main\npurpose for this is to support the Emacs Lisp/STELLA interface to find function definitions.\" :PUBLIC? TRUE)", ((cpp_function_code)(&findSourceFromNativeFileName)), NULL);
    defineFunctionObject("LANGUAGE-TO-FILE-TYPE", "(DEFUN (LANGUAGE-TO-FILE-TYPE KEYWORD) ((LANGUAGE KEYWORD)))", ((cpp_function_code)(&languageToFileType)), NULL);
    defineFunctionObject("REROOT-FILE-NAME", "(DEFUN (REROOT-FILE-NAME FILE-NAME) ((FILE FILE-NAME) (FROMROOT FILE-NAME) (TOROOT FILE-NAME)))", ((cpp_function_code)(&rerootFileName)), NULL);
    defineFunctionObject("FILE-YOUNGER-THAN?", "(DEFUN (FILE-YOUNGER-THAN? THREE-VALUED-BOOLEAN) ((FILE1 STRING) (FILE2 STRING)))", ((cpp_function_code)(&fileYoungerThanP)), NULL);
  }
}

void startupTranslateFile() {
  if (currentStartupTimePhaseP(0)) {
    oLOGICAL_HOST_TABLEo = newStringHashTable();
    defineLogicalHostProperty("ST", NULL, NULL);
    defineLogicalHostProperty("PL", NULL, NULL);
  }
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupTranslateFile1();
    }
    if (currentStartupTimePhaseP(4)) {
      oDEFAULTSYSTEMDEFINITIONDIRECTORIESo = consList(2, wrapString(concatenateFileNames(oDEFAULTROOTSOURCEDIRECTORYo, 1, "systems;")), wrapString("ST:systems;"));
      oOSo = operatingSystem();
      oTYPE_TO_FILE_EXTENSION_TABLEo = listO(12, listO(3, KWD_TRANSLATE_FILE_STELLA, wrapString(".ste"), NIL), listO(3, KWD_TRANSLATE_FILE_KB, wrapString(".kb"), NIL), listO(3, KWD_TRANSLATE_FILE_CPP, wrapString(".cc"), NIL), listO(3, KWD_TRANSLATE_FILE_CPP_CODE, wrapString(".cc"), NIL), listO(3, KWD_TRANSLATE_FILE_CPP_HEADER, wrapString(".hh"), NIL), listO(3, KWD_TRANSLATE_FILE_C_CODE, wrapString(".c"), NIL), listO(3, KWD_TRANSLATE_FILE_C_HEADER, wrapString(".h"), NIL), listO(3, KWD_TRANSLATE_FILE_JAVA, wrapString(".java"), NIL), listO(3, KWD_TRANSLATE_FILE_IDL, wrapString(".idl"), NIL), listO(3, KWD_TRANSLATE_FILE_OTHER, wrapString(""), NIL), listO(3, KWD_TRANSLATE_FILE_NONE, wrapString(""), NIL), NIL);
    }
    if (currentStartupTimePhaseP(5)) {
      defineStellaTypeFromStringifiedSource("(DEFTYPE SYSTEM-UNITS-ALIST (KEY-VALUE-LIST OF STRING-WRAPPER (LIST OF TRANSLATION-UNIT)))");
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupTranslateFile2();
      defineFunctionObject("STELLA-NEED-TO-TRANSLATE?", "(DEFUN (STELLA-NEED-TO-TRANSLATE? BOOLEAN) ((FILE OBJECT) (LANGUAGE KEYWORD)))", ((cpp_function_code)(&stellaNeedToTranslateP)), NULL);
      defineFunctionObject("STELLA-NEED-TO-COMPILE?", "(DEFUN (STELLA-NEED-TO-COMPILE? BOOLEAN) ((FILE OBJECT)))", ((cpp_function_code)(&stellaNeedToCompileP)), NULL);
      defineFunctionObject("SYSTEM-NEEDS-TRANSLATION?", "(DEFUN (SYSTEM-NEEDS-TRANSLATION? BOOLEAN) ((SYSTEMNAME STRING) (LANGUAGE KEYWORD)))", ((cpp_function_code)(&systemNeedsTranslationP)), NULL);
      defineFunctionObject("COMPUTE-FILE-UNITS-MODULE", "(DEFUN (COMPUTE-FILE-UNITS-MODULE MODULE) ((FILEUNITS (LIST OF TRANSLATION-UNIT))))", ((cpp_function_code)(&computeFileUnitsModule)), NULL);
      defineFunctionObject("CONCATENATE-SYSTEM-UNITS", "(DEFUN (CONCATENATE-SYSTEM-UNITS (LIST OF TRANSLATION-UNIT)) ((SYSTEMUNITS SYSTEM-UNITS-ALIST)))", ((cpp_function_code)(&concatenateSystemUnits)), NULL);
      defineFunctionObject("TRANSLATE-SYSTEM", "(DEFUN (TRANSLATE-SYSTEM BOOLEAN) ((SYSTEMNAME STRING) |&REST| (|LANGUAGE&OPTIONS| OBJECT)) :DOCUMENTATION \"Translate all of the STELLA source files in system `systemName' into\n`language' (the optional first argument).  The following keyword/value\n`options' are recognized:\n\n`:language': can be used as an alternative to the optional language argument.\nIf not specified, the language of the running implementation is assumed.\n\n`:two-pass?' (default false): if true, all files will be scanned twice, once\nto load the signatures of objects defined in them, and once to actually\ntranslate the definitions.\n\n`:force-translation?' (default false): if true, files will be translated\nwhether or not their translations are up-to-date.\n\n`:development-settings?' (default false): if true translation will favor\nsafe, readable and debuggable code over efficiency (according to the value\nof `:development-settings' on the system definition).  If false, efficiency\nwill be favored instead (according to the value of `:" "production-settings'\non the system definition).\n\n`:production-settings?' (default true): inverse to `:development-settings?'.\n\n`:recursive?' (default false): if true, perform `translate-system' with the provided\noptions on `systemName' as well as all its required systems and so on.  Required\nsystems will be processed first.  Note that even without this option, any required\nsystems that have not yet been loaded or started up will also be processed, since\nthat is assumed when loading `systemName' and supporting modules from a definition file.\n\n`:root-source-directory', `:root-native-directory', `:root-binary-directory': if\nspecified these directories will be used to override the respective paths provided\nin system definitions or computed as defaults from a system's home location.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&translateSystem)), ((cpp_function_code)(&translateSystemEvaluatorWrapper)));
      defineFunctionObject("HELP-TRANSLATE-SYSTEM", "(DEFUN (HELP-TRANSLATE-SYSTEM BOOLEAN) ((FILES (CONS OF STRING-WRAPPER)) (TWOPASS? BOOLEAN) (FORCETRANSLATION? BOOLEAN)))", ((cpp_function_code)(&helpTranslateSystem)), NULL);
      defineFunctionObject("TRANSFER-NATIVE-SYSTEM-FILES", "(DEFUN TRANSFER-NATIVE-SYSTEM-FILES ((OUTPUT-LANGUAGE KEYWORD)))", ((cpp_function_code)(&transferNativeSystemFiles)), NULL);
      defineFunctionObject("TRANSFER-DATA-FILES", "(DEFUN TRANSFER-DATA-FILES ((OUTPUT-LANGUAGE KEYWORD)))", ((cpp_function_code)(&transferDataFiles)), NULL);
      defineFunctionObject("TRANSFER-FILES", "(DEFUN TRANSFER-FILES ((FILES (CONS OF STRING-WRAPPER)) (OUTPUT-LANGUAGE KEYWORD)))", ((cpp_function_code)(&transferFiles)), NULL);
      defineFunctionObject("STARTUP-TRANSLATE-FILE", "(DEFUN STARTUP-TRANSLATE-FILE () :PUBLIC? TRUE)", ((cpp_function_code)(&startupTranslateFile)), NULL);
      { MethodSlot* function = lookupFunction(SYM_TRANSLATE_FILE_STELLA_STARTUP_TRANSLATE_FILE);

        setDynamicSlotValue(function->dynamicSlots, SYM_TRANSLATE_FILE_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupTranslateFile"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *RECORD-SIGNATURES?* BOOLEAN FALSE :DOCUMENTATION \"If `true', record object signatures into a persistent table.\")", &oRECORD_SIGNATURESpo);
      defineGlobalVariableObject("(DEFGLOBAL *WALK-WITH-RECORDED-SIGNATURES?* BOOLEAN FALSE :DOCUMENTATION \"If `true', the walker will try to find previously recorded\nsignatures for referenced but undefined functions, methods, etc.\")", &oWALK_WITH_RECORDED_SIGNATURESpo);
      defineGlobalVariableObject("(DEFSPECIAL *USERECORDEDSIGNATURES?* BOOLEAN FALSE :DOCUMENTATION \"If `true', `safe-lookup-slot' and `lookup-function' will\ntry to retrieve a previously recorded signature if normal lookup fails.\")", &oUSERECORDEDSIGNATURESpo);
      defineGlobalVariableObject("(DEFSPECIAL *DEFAULTROOTSOURCEDIRECTORY* STRING \"ST:sources;\")", &oDEFAULTROOTSOURCEDIRECTORYo);
      defineGlobalVariableObject("(DEFSPECIAL *DEFAULTROOTNATIVEDIRECTORY* STRING \"ST:native;\")", &oDEFAULTROOTNATIVEDIRECTORYo);
      defineGlobalVariableObject("(DEFSPECIAL *DEFAULTROOTBINARYDIRECTORY* STRING \"ST:bin;\")", &oDEFAULTROOTBINARYDIRECTORYo);
      defineGlobalVariableObject("(DEFSPECIAL *DEFAULTSYSTEMDEFINITIONDIRECTORIES* (CONS OF STRING-WRAPPER) (CONS-LIST (CONCATENATE-FILE-NAMES *DEFAULTROOTSOURCEDIRECTORY* \"systems;\") \"ST:systems;\") :DOCUMENTATION \"Points to a list of directories containing system definition files.\")", &oDEFAULTSYSTEMDEFINITIONDIRECTORIESo);
      defineGlobalVariableObject("(DEFSPECIAL *CURRENTSYSTEMDEFINITION* SYSTEM-DEFINITION NULL :DOCUMENTATION \"Points to the current system.\")", &oCURRENTSYSTEMDEFINITIONo);
      defineGlobalVariableObject("(DEFSPECIAL *CURRENTSYSTEMDEFINITIONSUBDIRECTORY* STRING \"\" :DOCUMENTATION \"Points to a path from the root directory down\nto a local directory containing sources, natives, or binaries.\")", &oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo);
      defineGlobalVariableObject("(DEFGLOBAL *OS* KEYWORD (OPERATING-SYSTEM) :DOCUMENTATION \"The operating system we are running on.  Currently,\neither :UNIX, :WINDOWS, or :MAC.  Note that on the Mac OS X, the\nOS can be either :UNIX or :MAC, depending on which file naming \nconventions are being observed by the software.\")", &oOSo);
      defineGlobalVariableObject("(DEFCONSTANT TYPE-SEPARATOR CHARACTER #\\.)", &TYPE_SEPARATOR);
      defineGlobalVariableObject("(DEFCONSTANT LOGICAL-DIRECTORY-SEPARATOR CHARACTER #\\;)", &LOGICAL_DIRECTORY_SEPARATOR);
      defineGlobalVariableObject("(DEFCONSTANT LOGICAL-HOST-SEPARATOR CHARACTER #\\:)", &LOGICAL_HOST_SEPARATOR);
      defineGlobalVariableObject("(DEFGLOBAL *LOGICAL-HOST-TABLE* (STRING-HASH-TABLE OF STRING KEY-VALUE-LIST) NULL)", &oLOGICAL_HOST_TABLEo);
      { SystemDefinition* system = getSystemDefinition("stella", false);
        const char* rootdir = (((boolean)(system)) ? findSystemRootDirectory(system) : ((const char*)(NULL)));

        if (!(blankStringP(rootdir))) {
          defineLogicalHostProperty("ST", KWD_TRANSLATE_FILE_ROOT_DIRECTORY, wrapString(rootdir));
        }
      }
      defineGlobalVariableObject("(DEFGLOBAL *TYPE-TO-FILE-EXTENSION-TABLE* (CONS OF CONS) (BQUOTE ((:STELLA \".ste\") (:KB \".kb\") (:CPP \".cc\") (:CPP-CODE \".cc\") (:CPP-HEADER \".hh\") (:C-CODE \".c\") (:C-HEADER \".h\") (:JAVA \".java\") (:IDL \".idl\") (:OTHER \"\") (:NONE \"\"))) :DOCUMENTATION \"Used by `select-file-extension'.\")", &oTYPE_TO_FILE_EXTENSION_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *LISP-SPLITTER-PATH* STRING \"lisp\")", &oLISP_SPLITTER_PATHo);
      defineGlobalVariableObject("(DEFGLOBAL *JAVA-SPLITTER-PATH* STRING \"java\")", &oJAVA_SPLITTER_PATHo);
      defineGlobalVariableObject("(DEFGLOBAL *CPP-SPLITTER-PATH* STRING \"cpp\")", &oCPP_SPLITTER_PATHo);
      defineGlobalVariableObject("(DEFSPECIAL *DONTTRUNCATEFILENAMES?* BOOLEAN FALSE :DOCUMENTATION \"When TRUE, overrides normal truncation of file names.\")", &oDONTTRUNCATEFILENAMESpo);
    }
  }
}

Keyword* KWD_TRANSLATE_FILE_ROOT_SOURCE_DIRECTORY = NULL;

Keyword* KWD_TRANSLATE_FILE_ROOT_NATIVE_DIRECTORY = NULL;

Keyword* KWD_TRANSLATE_FILE_ROOT_BINARY_DIRECTORY = NULL;

Keyword* KWD_TRANSLATE_FILE_TRANSLATE = NULL;

Keyword* KWD_TRANSLATE_FILE_JAVA = NULL;

Keyword* KWD_TRANSLATE_FILE_COMMON_LISP = NULL;

Keyword* KWD_TRANSLATE_FILE_CPP = NULL;

Keyword* KWD_TRANSLATE_FILE_CPP_STANDALONE = NULL;

Keyword* KWD_TRANSLATE_FILE_IDL = NULL;

Surrogate* SGT_TRANSLATE_FILE_STELLA_CONS = NULL;

Keyword* KWD_TRANSLATE_FILE_DEFINE = NULL;

Keyword* KWD_TRANSLATE_FILE_FINALIZE = NULL;

Keyword* KWD_TRANSLATE_FILE_WALK = NULL;

Keyword* KWD_TRANSLATE_FILE_TRANSLATE_WITH_COPYRIGHT_HEADER = NULL;

Keyword* KWD_TRANSLATE_FILE_WINDOWS = NULL;

Keyword* KWD_TRANSLATE_FILE_UNIX = NULL;

Keyword* KWD_TRANSLATE_FILE_MAC = NULL;

Keyword* KWD_TRANSLATE_FILE_LETTER = NULL;

Keyword* KWD_TRANSLATE_FILE_ROOT_DIRECTORY = NULL;

Keyword* KWD_TRANSLATE_FILE_LISP_TRANSLATIONS = NULL;

Surrogate* SGT_TRANSLATE_FILE_STELLA_KEYWORD = NULL;

Keyword* KWD_TRANSLATE_FILE_STELLA = NULL;

Keyword* KWD_TRANSLATE_FILE_KB = NULL;

Keyword* KWD_TRANSLATE_FILE_CPP_CODE = NULL;

Keyword* KWD_TRANSLATE_FILE_CPP_HEADER = NULL;

Keyword* KWD_TRANSLATE_FILE_C_CODE = NULL;

Keyword* KWD_TRANSLATE_FILE_C_HEADER = NULL;

Keyword* KWD_TRANSLATE_FILE_OTHER = NULL;

Keyword* KWD_TRANSLATE_FILE_NONE = NULL;

Keyword* KWD_TRANSLATE_FILE_LISP_BINARY = NULL;

Keyword* KWD_TRANSLATE_FILE_USE_COMMON_LISP_STRUCTS = NULL;

Keyword* KWD_TRANSLATE_FILE_USE_COMMON_LISP_VECTOR_STRUCTS = NULL;

Keyword* KWD_TRANSLATE_FILE_LISP = NULL;

Keyword* KWD_TRANSLATE_FILE_DIRECTORY = NULL;

Keyword* KWD_TRANSLATE_FILE_JAVAC = NULL;

Keyword* KWD_TRANSLATE_FILE_MAVEN = NULL;

Symbol* SYM_TRANSLATE_FILE_STELLA_SYSTEM_UNITS_ALIST = NULL;

Keyword* KWD_TRANSLATE_FILE_TWO_PASSp = NULL;

Surrogate* SGT_TRANSLATE_FILE_STELLA_BOOLEAN = NULL;

Keyword* KWD_TRANSLATE_FILE_DEVELOPMENT_SETTINGSp = NULL;

Keyword* KWD_TRANSLATE_FILE_PRODUCTION_SETTINGSp = NULL;

Keyword* KWD_TRANSLATE_FILE_FORCE_TRANSLATIONp = NULL;

Keyword* KWD_TRANSLATE_FILE_RECURSIVEp = NULL;

Keyword* KWD_TRANSLATE_FILE_LANGUAGE = NULL;

Keyword* KWD_TRANSLATE_FILE_ACTION = NULL;

Surrogate* SGT_TRANSLATE_FILE_STELLA_FILE_NAME = NULL;

Keyword* KWD_TRANSLATE_FILE_PROCESSED = NULL;

Surrogate* SGT_TRANSLATE_FILE_STELLA_LIST = NULL;

Keyword* KWD_TRANSLATE_FILE_TRANSLATE_SYSTEM = NULL;

Keyword* KWD_TRANSLATE_FILE_OPTIONS = NULL;

Keyword* KWD_TRANSLATE_FILE_WARN_ABOUT_MISSING_METHODS = NULL;

Keyword* KWD_TRANSLATE_FILE_WARN_ABOUT_UNDEFINED_METHODS = NULL;

Keyword* KWD_TRANSLATE_FILE_USE_HARDCODED_SYMBOLS = NULL;

Symbol* SYM_TRANSLATE_FILE_STELLA_STARTUP_TRANSLATE_FILE = NULL;

Symbol* SYM_TRANSLATE_FILE_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
