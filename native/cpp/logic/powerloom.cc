//  -*- Mode: C++ -*-

// powerloom.cc

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
 | The Original Code is the PowerLoom KR&R System.                            |
 |                                                                            |
 | The Initial Developer of the Original Code is                              |
 | UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |
 | 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |
 |                                                                            |
 | Portions created by the Initial Developer are Copyright (C) 1997-2023      |
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
 +----------------------------- END LICENSE BLOCK ----------------------------+
*/

#include "logic/logic-system.hh"

namespace logic {
  using namespace stella;

int oPOWERLOOM_MAJOR_VERSION_NUMBERo = 5;

int oPOWERLOOM_MINOR_VERSION_NUMBERo = 0;

const char* oPOWERLOOM_RELEASE_STATEo = "";

int oPOWERLOOM_PATCH_LEVELo = 0;

const char* oPOWERLOOM_VERSION_STRINGo = NULL;

// Either :development, :debugging or :release (so far) which controls
// whether certain internal error and warning messages are surfaced to the user.
Keyword* oPOWERLOOM_EXECUTION_MODEo = NULL;

void plLog(Keyword* loglevel, int message, ...) {
  { Cons* arglist000 = NIL;

    { va_list iter000;
      int iter000Count = message;
      Object* arg000 = NULL;
      Cons* collect000 = NULL;

      va_start(iter000, message);
            for  (; (iter000Count--) > 0; ) {
        arg000 = va_arg(iter000, Object*);
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(arg000, NIL);
            if (arglist000 == NIL) {
              arglist000 = collect000;
            }
            else {
              addConsToEndOfConsList(arglist000, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(arg000, NIL);
            collect000 = collect000->rest;
          }
        }
      }
      va_end(iter000);
    }
    logMessage("PowerLoom", loglevel, arglist000);
  }
}

const char* powerloomInformation() {
  // Returns information about the current PowerLoom implementation.
  // Useful when reporting problems.
  { OutputStringStream* ss = newOutputStringStream();

    *(ss->nativeStream) << oPOWERLOOM_VERSION_STRINGo << std::endl << stellaInformation();
    return (ss->theStringReader());
  }
}

StringWrapper* powerloomInformationEvaluatorWrapper(Cons* arguments) {
  arguments = arguments;
  { const char* result = powerloomInformation();

    if (result != NULL) {
      return (wrapString(result));
    }
    else {
      return (NULL);
    }
  }
}

const char* powerloomCopyrightHeader() {
  { SystemDefinition* logicsystem = getSystemDefinition("logic", false);
    KeyValueList* substitutionList = newKeyValueList();

    fillInDateSubstitution(substitutionList);
    if (((boolean)(logicsystem))) {
      return (substituteTemplateVariablesInString(logicsystem->banner, substitutionList));
    }
    else {
      return ("---------------------------- BEGIN LICENSE BLOCK ---------------------------+\n |                                                                            |\n | Version: MPL 1.1/GPL 2.0/LGPL 2.1                                          |\n |                                                                            |\n | The contents of this file are subject to the Mozilla Public License        |\n | Version 1.1 (the \"License\"); you may not use this file except in           |\n | compliance with the License. You may obtain a copy of the License at       |\n | http://www.mozilla.org/MPL/                                                |\n |                                                                            |\n | Software distributed under the License is distributed on an \"AS IS\" basis, |\n | WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License   |\n | for the specific language governing rights and limitations under the       |\n | License.                                      " "                             |\n |                                                                            |\n | The Original Code is the PowerLoom KR&R System.                            |\n |                                                                            |\n | The Initial Developer of the Original Code is                              |\n | UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |\n | 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |\n |                                                                            |\n | Portions created by the Initial Developer are Copyright (C) 1997-2010      |\n | the Initial Developer. All Rights Reserved.                                |\n |                                                                            |\n | Contributor(s):                                                            |\n |                                                                            |\n | Alternatively, t" "he contents of this file may be used under the terms of    |\n | either the GNU General Public License Version 2 or later (the \"GPL\"), or   |\n | the GNU Lesser General Public License Version 2.1 or later (the \"LGPL\"),   |\n | in which case the provisions of the GPL or the LGPL are applicable instead |\n | of those above. If you wish to allow use of your version of this file only |\n | under the terms of either the GPL or the LGPL, and not to allow others to  |\n | use your version of this file under the terms of the MPL, indicate your    |\n | decision by deleting the provisions above and replace them with the notice |\n | and other provisions required by the GPL or the LGPL. If you do not delete |\n | the provisions above, a recipient may use your version of this file under  |\n | the terms of any one of the MPL, the GPL or the LGPL.                      |\n |                                                                            |\n +----------------------------- END LICENSE BLOCK ----------------" "------------");
    }
  }
}

void copyright() {
  // Print detailed PowerLoom copyright information.
  std::cout << " +" << powerloomCopyrightHeader() << "+" << std::endl;
}

const char* copyrightYears() {
  { const char* copyright = powerloomCopyrightHeader();
    int start = stringSearch(copyright, "1997", 0);
    int end = stringSearch(copyright, "  ", start);

    return (stringSubsequence(copyright, start, end));
  }
}

// Lock object for synchronizing safe multi-process access to PowerLoom
void* oPOWERLOOM_LOCKo = NULL;

void powerloom() {
  // Run the PowerLoom listener.  Read logic commands from the
  // standard input, evaluate them, and print their results.  Exit if the user
  // entered `bye', `exit', `halt', `quit', or `stop'.
  std::cout << std::endl << "    Welcome to " << oPOWERLOOM_VERSION_STRINGo << std::endl << std::endl << "Copyright (C) USC Information Sciences Institute, " << copyrightYears() << "." << std::endl << "PowerLoom is a trademark of the University of Southern California." << std::endl << "PowerLoom comes with ABSOLUTELY NO WARRANTY!" << std::endl << "Type `(copyright)' for detailed copyright information." << std::endl << "Type `(help)' for a list of available commands." << std::endl << "Type `(demo)' for a list of example applications." << std::endl << "Type `bye', `exit', `halt', `quit', or `stop', to exit." << std::endl << std::endl;
  try {
    logicCommandLoop(NULL);
    std::cout << "Bye." << std::endl << std::endl;
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    *(STANDARD_ERROR->nativeStream) << "Caught native non-STELLA exception " << e << " at top level." << std::endl;
    printExceptionContext(e, STANDARD_ERROR);
    *(STANDARD_ERROR->nativeStream) << "Exiting PowerLoom." << std::endl << std::endl;
  }
}

void startupPowerloom() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      KWD_POWERLOOM_RELEASE = ((Keyword*)(internRigidSymbolWrtModule("RELEASE", NULL, 2)));
      KWD_POWERLOOM_LOG_LEVELS = ((Keyword*)(internRigidSymbolWrtModule("LOG-LEVELS", NULL, 2)));
      KWD_POWERLOOM_LEVEL = ((Keyword*)(internRigidSymbolWrtModule("LEVEL", NULL, 2)));
      KWD_POWERLOOM_DEVELOPMENT = ((Keyword*)(internRigidSymbolWrtModule("DEVELOPMENT", NULL, 2)));
      KWD_POWERLOOM_MEDIUM = ((Keyword*)(internRigidSymbolWrtModule("MEDIUM", NULL, 2)));
      KWD_POWERLOOM_LOW = ((Keyword*)(internRigidSymbolWrtModule("LOW", NULL, 2)));
      KWD_POWERLOOM_PREFIX = ((Keyword*)(internRigidSymbolWrtModule("PREFIX", NULL, 2)));
      KWD_POWERLOOM_MAX_WIDTH = ((Keyword*)(internRigidSymbolWrtModule("MAX-WIDTH", NULL, 2)));
      SYM_POWERLOOM_LOGIC_STARTUP_POWERLOOM = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-POWERLOOM", NULL, 0)));
      SYM_POWERLOOM_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
    }
    if (currentStartupTimePhaseP(4)) {
      oPOWERLOOM_VERSION_STRINGo = stringConcatenate("PowerLoom ", integerToString(((long long int)(oPOWERLOOM_MAJOR_VERSION_NUMBERo))), 5, ".", integerToString(((long long int)(oPOWERLOOM_MINOR_VERSION_NUMBERo))), ".", integerToString(((long long int)(oPOWERLOOM_PATCH_LEVELo))), oPOWERLOOM_RELEASE_STATEo);
      oPOWERLOOM_EXECUTION_MODEo = KWD_POWERLOOM_RELEASE;
      oPOWERLOOM_LOCKo = makeProcessLock();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("PL-LOG", "(DEFUN PL-LOG ((LOGLEVEL KEYWORD) |&REST| (MESSAGE OBJECT)))", ((cpp_function_code)(&plLog)), NULL);
      defineFunctionObject("POWERLOOM-INFORMATION", "(DEFUN (POWERLOOM-INFORMATION STRING) () :DOCUMENTATION \"Returns information about the current PowerLoom implementation.\nUseful when reporting problems.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&powerloomInformation)), ((cpp_function_code)(&powerloomInformationEvaluatorWrapper)));
      defineFunctionObject("POWERLOOM-COPYRIGHT-HEADER", "(DEFUN (POWERLOOM-COPYRIGHT-HEADER STRING) ())", ((cpp_function_code)(&powerloomCopyrightHeader)), NULL);
      defineFunctionObject("COPYRIGHT", "(DEFUN COPYRIGHT () :COMMAND? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Print detailed PowerLoom copyright information.\")", ((cpp_function_code)(&copyright)), NULL);
      defineFunctionObject("COPYRIGHT-YEARS", "(DEFUN (COPYRIGHT-YEARS STRING) ())", ((cpp_function_code)(&copyrightYears)), NULL);
      defineFunctionObject("POWERLOOM", "(DEFUN POWERLOOM () :DOCUMENTATION \"Run the PowerLoom listener.  Read logic commands from the\nstandard input, evaluate them, and print their results.  Exit if the user\nentered `bye', `exit', `halt', `quit', or `stop'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&powerloom)), NULL);
      defineFunctionObject("STARTUP-POWERLOOM", "(DEFUN STARTUP-POWERLOOM () :PUBLIC? TRUE)", ((cpp_function_code)(&startupPowerloom)), NULL);
      { MethodSlot* function = lookupFunction(SYM_POWERLOOM_LOGIC_STARTUP_POWERLOOM);

        setDynamicSlotValue(function->dynamicSlots, SYM_POWERLOOM_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupPowerloom"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFGLOBAL *POWERLOOM-MAJOR-VERSION-NUMBER* INTEGER 5)", &oPOWERLOOM_MAJOR_VERSION_NUMBERo);
      defineGlobalVariableObject("(DEFGLOBAL *POWERLOOM-MINOR-VERSION-NUMBER* INTEGER 0)", &oPOWERLOOM_MINOR_VERSION_NUMBERo);
      defineGlobalVariableObject("(DEFGLOBAL *POWERLOOM-RELEASE-STATE* STRING \"\")", &oPOWERLOOM_RELEASE_STATEo);
      defineGlobalVariableObject("(DEFGLOBAL *POWERLOOM-PATCH-LEVEL* INTEGER 0)", &oPOWERLOOM_PATCH_LEVELo);
      defineGlobalVariableObject("(DEFGLOBAL *POWERLOOM-VERSION-STRING* STRING (CONCATENATE \"PowerLoom \" (INTEGER-TO-STRING *POWERLOOM-MAJOR-VERSION-NUMBER*) \".\" (INTEGER-TO-STRING *POWERLOOM-MINOR-VERSION-NUMBER*) \".\" (INTEGER-TO-STRING *POWERLOOM-PATCH-LEVEL*) *POWERLOOM-RELEASE-STATE*))", &oPOWERLOOM_VERSION_STRINGo);
      defineGlobalVariableObject("(DEFGLOBAL *POWERLOOM-EXECUTION-MODE* KEYWORD :RELEASE :DOCUMENTATION \"Either :development, :debugging or :release (so far) which controls\nwhether certain internal error and warning messages are surfaced to the user.\" :DEMON-PROPERTY \"powerloom.executionMode\")", &oPOWERLOOM_EXECUTION_MODEo);
      setLoggingParameters("PowerLoom", consList(8, KWD_POWERLOOM_LOG_LEVELS, getQuotedTree("((:NONE :LOW :MEDIUM :HIGH) \"/LOGIC\")", "/LOGIC"), KWD_POWERLOOM_LEVEL, ((oPOWERLOOM_EXECUTION_MODEo == KWD_POWERLOOM_DEVELOPMENT) ? KWD_POWERLOOM_MEDIUM : KWD_POWERLOOM_LOW), KWD_POWERLOOM_PREFIX, wrapString("PL"), KWD_POWERLOOM_MAX_WIDTH, wrapInteger(250)));
      defineGlobalVariableObject("(DEFGLOBAL *POWERLOOM-LOCK* PROCESS-LOCK-OBJECT (MAKE-PROCESS-LOCK) :PUBLIC? TRUE :DOCUMENTATION \"Lock object for synchronizing safe multi-process access to PowerLoom\")", &oPOWERLOOM_LOCKo);
    }
  }
}

Keyword* KWD_POWERLOOM_RELEASE = NULL;

Keyword* KWD_POWERLOOM_LOG_LEVELS = NULL;

Keyword* KWD_POWERLOOM_LEVEL = NULL;

Keyword* KWD_POWERLOOM_DEVELOPMENT = NULL;

Keyword* KWD_POWERLOOM_MEDIUM = NULL;

Keyword* KWD_POWERLOOM_LOW = NULL;

Keyword* KWD_POWERLOOM_PREFIX = NULL;

Keyword* KWD_POWERLOOM_MAX_WIDTH = NULL;

Symbol* SYM_POWERLOOM_LOGIC_STARTUP_POWERLOOM = NULL;

Symbol* SYM_POWERLOOM_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
