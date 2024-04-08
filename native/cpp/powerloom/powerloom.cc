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

#include "powerloom/powerloom-system.hh"

namespace stella_powerloom_code {
  using namespace stella_utilities;
  using namespace stella_plx;
  using namespace pli;
  using namespace logic;
  using namespace stella;

// List of extension systems that can be loaded
// dynamically (not yet in C++).
Cons* oPOWERLOOM_EXTENSION_SYSTEMSo = NULL;

void loadAllExtensionSystems() {
  // Load and initialize all installed extension systems.
  { StringWrapper* system = NULL;
    Cons* iter000 = oPOWERLOOM_EXTENSION_SYSTEMSo;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      system = ((StringWrapper*)(iter000->value));
      if (!systemLoadedOrStartedUpP(stringDowncase(system->wrapperValue))) {
        std::cout << "Initializing " << unwrapString(system) << "...";
        try {
          loadSystem(stringDowncase(system->wrapperValue), NIL);
        }
        catch (std::exception ) {
          std::cout << "FAILED";
        }
        std::cout << std::endl;
      }
    }
  }
}

void loadAllExtensionsOptionHandler(CmdLineOption* option, Object* value) {
  // Load and initialize all installed extension systems.
  {
    option = option;
    value = value;
  }
  loadAllExtensionSystems();
}

void startPowerloomGuiOptionHandler(CmdLineOption* option, Object* value) {
  // Start the PowerLoom GUI.
  {
    option = option;
    value = value;
  }
  setConfigurationProperty("powerloom.runInteractively", TRUE_WRAPPER, NULL);
  startPowerloomGui(NIL);
}

int main(int count, const char** arguments) {
  std::cout << "Initializing STELLA..." << std::endl;
  startupStellaSystem();
  std::cout << "Initializing PowerLoom..." << std::endl;
  startupLogicSystem();
  startupPowerloomExtensionsSystem();
  startupPowerloomSystem();
  stella::stringChangeModule("PL-USER");
  processCommandLineArguments(count, arguments, KWD_POWERLOOM_WARN);
  if ((!eqlP(stella::getProperty(wrapString("powerloom.runInteractively"), NIL), FALSE_WRAPPER)) &&
      (!eqlP(stella::getProperty(wrapString("stella.showInfoOnly"), NIL), TRUE_WRAPPER))) {
    logic::powerloom();
  }
  runHooks(oSTELLA_EXIT_HOOKSo, NULL);
  return (1);
}

void startupPowerloom() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/POWERLOOM-CODE", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      KWD_POWERLOOM_KEY = ((Keyword*)(internRigidSymbolWrtModule("KEY", NULL, 2)));
      KWD_POWERLOOM_DOCUMENTATION = ((Keyword*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 2)));
      KWD_POWERLOOM_N_ARGUMENTS = ((Keyword*)(internRigidSymbolWrtModule("N-ARGUMENTS", NULL, 2)));
      KWD_POWERLOOM_HANDLER = ((Keyword*)(internRigidSymbolWrtModule("HANDLER", NULL, 2)));
      SYM_POWERLOOM_POWERLOOM_CODE_LOAD_ALL_EXTENSIONS_OPTION_HANDLER = ((Symbol*)(internRigidSymbolWrtModule("LOAD-ALL-EXTENSIONS-OPTION-HANDLER", NULL, 0)));
      KWD_POWERLOOM_ERROR_ACTION = ((Keyword*)(internRigidSymbolWrtModule("ERROR-ACTION", NULL, 2)));
      KWD_POWERLOOM_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
      SYM_POWERLOOM_POWERLOOM_CODE_START_POWERLOOM_GUI_OPTION_HANDLER = ((Symbol*)(internRigidSymbolWrtModule("START-POWERLOOM-GUI-OPTION-HANDLER", NULL, 0)));
      KWD_POWERLOOM_WARN = ((Keyword*)(internRigidSymbolWrtModule("WARN", NULL, 2)));
      KWD_POWERLOOM_KEY2 = ((Keyword*)(internRigidSymbolWrtModule("KEY2", NULL, 2)));
      KWD_POWERLOOM_PROPERTY = ((Keyword*)(internRigidSymbolWrtModule("PROPERTY", NULL, 2)));
      KWD_POWERLOOM_VALUE_TYPE = ((Keyword*)(internRigidSymbolWrtModule("VALUE-TYPE", NULL, 2)));
      SGT_POWERLOOM_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", getStellaModule("/STELLA", true), 1)));
      KWD_POWERLOOM_DEFAULT_VALUE = ((Keyword*)(internRigidSymbolWrtModule("DEFAULT-VALUE", NULL, 2)));
      KWD_POWERLOOM_KEY3 = ((Keyword*)(internRigidSymbolWrtModule("KEY3", NULL, 2)));
      SYM_POWERLOOM_STELLA_EVAL_OPTION_HANDLER = ((Symbol*)(internRigidSymbolWrtModule("EVAL-OPTION-HANDLER", getStellaModule("/STELLA", true), 0)));
      KWD_POWERLOOM_ROOT_DIRECTORY = ((Keyword*)(internRigidSymbolWrtModule("ROOT-DIRECTORY", NULL, 2)));
      SYM_POWERLOOM_POWERLOOM_CODE_STARTUP_POWERLOOM = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-POWERLOOM", NULL, 0)));
      SYM_POWERLOOM_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
    }
    if (currentStartupTimePhaseP(4)) {
      oPOWERLOOM_EXTENSION_SYSTEMSo = consList(2, wrapString("SDBC"), wrapString("RDBMS"));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("LOAD-ALL-EXTENSION-SYSTEMS", "(DEFUN LOAD-ALL-EXTENSION-SYSTEMS () :DOCUMENTATION \"Load and initialize all installed extension systems.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&loadAllExtensionSystems)), NULL);
      defineFunctionObject("LOAD-ALL-EXTENSIONS-OPTION-HANDLER", "(DEFUN LOAD-ALL-EXTENSIONS-OPTION-HANDLER ((OPTION CMD-LINE-OPTION) (VALUE OBJECT)) :DOCUMENTATION \"Load and initialize all installed extension systems.\" :PUBLIC? TRUE)", ((cpp_function_code)(&loadAllExtensionsOptionHandler)), NULL);
      defineFunctionObject("START-POWERLOOM-GUI-OPTION-HANDLER", "(DEFUN START-POWERLOOM-GUI-OPTION-HANDLER ((OPTION CMD-LINE-OPTION) (VALUE OBJECT)) :DOCUMENTATION \"Start the PowerLoom GUI.\" :PUBLIC? TRUE)", ((cpp_function_code)(&startPowerloomGuiOptionHandler)), NULL);
      defineFunctionObject("MAIN", "(DEFUN (MAIN INTEGER) ((COUNT INTEGER) (ARGUMENTS (ARRAY () OF STRING))) :PUBLIC? TRUE)", ((cpp_function_code)(&main)), NULL);
      defineFunctionObject("STARTUP-POWERLOOM", "(DEFUN STARTUP-POWERLOOM () :PUBLIC? TRUE)", ((cpp_function_code)(&startupPowerloom)), NULL);
      { MethodSlot* function = lookupFunction(SYM_POWERLOOM_POWERLOOM_CODE_STARTUP_POWERLOOM);

        setDynamicSlotValue(function->dynamicSlots, SYM_POWERLOOM_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupPowerloom"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("POWERLOOM-CODE")))));
      defineGlobalVariableObject("(DEFGLOBAL *POWERLOOM-EXTENSION-SYSTEMS* (CONS OF STRING-WRAPPER) (CONS-LIST \"SDBC\" \"RDBMS\") :DOCUMENTATION \"List of extension systems that can be loaded\ndynamically (not yet in C++).\" :PUBLIC? TRUE)", &oPOWERLOOM_EXTENSION_SYSTEMSo);
      registerCmdLineOption(10, KWD_POWERLOOM_KEY, wrapString("--load-all-extensions"), KWD_POWERLOOM_DOCUMENTATION, wrapString("\n  Load all available PowerLoom extension systems."), KWD_POWERLOOM_N_ARGUMENTS, wrapInteger(0), KWD_POWERLOOM_HANDLER, SYM_POWERLOOM_POWERLOOM_CODE_LOAD_ALL_EXTENSIONS_OPTION_HANDLER, KWD_POWERLOOM_ERROR_ACTION, KWD_POWERLOOM_ERROR);
      registerCmdLineOption(10, KWD_POWERLOOM_KEY, wrapString("--gui"), KWD_POWERLOOM_DOCUMENTATION, wrapString("\n  Launch the PowerLoom GUI in addition to the read/eval/print loop."), KWD_POWERLOOM_N_ARGUMENTS, wrapInteger(0), KWD_POWERLOOM_HANDLER, SYM_POWERLOOM_POWERLOOM_CODE_START_POWERLOOM_GUI_OPTION_HANDLER, KWD_POWERLOOM_ERROR_ACTION, KWD_POWERLOOM_WARN);
      registerCmdLineOption(14, KWD_POWERLOOM_KEY, wrapString("-i"), KWD_POWERLOOM_KEY2, wrapString("--interactive"), KWD_POWERLOOM_DOCUMENTATION, wrapString("\n  Launch an interactive read/eval/print loop after all startup code and\n  command line arguments have been processed."), KWD_POWERLOOM_N_ARGUMENTS, wrapInteger(0), KWD_POWERLOOM_PROPERTY, wrapString("powerloom.runInteractively"), KWD_POWERLOOM_VALUE_TYPE, SGT_POWERLOOM_STELLA_BOOLEAN, KWD_POWERLOOM_DEFAULT_VALUE, TRUE_WRAPPER);
      registerCmdLineOption(12, KWD_POWERLOOM_KEY, wrapString("--batch"), KWD_POWERLOOM_DOCUMENTATION, wrapString("\n  Do not start an interactive read/eval/print loop.  Just evaluate all\n  command line arguments and main function code and then exit."), KWD_POWERLOOM_N_ARGUMENTS, wrapInteger(0), KWD_POWERLOOM_PROPERTY, wrapString("powerloom.runInteractively"), KWD_POWERLOOM_VALUE_TYPE, SGT_POWERLOOM_STELLA_BOOLEAN, KWD_POWERLOOM_DEFAULT_VALUE, FALSE_WRAPPER);
      registerCmdLineOption(14, KWD_POWERLOOM_KEY, wrapString("-e"), KWD_POWERLOOM_KEY2, wrapString("--eval"), KWD_POWERLOOM_KEY3, wrapString("-eval"), KWD_POWERLOOM_DOCUMENTATION, wrapString("<s-expression>\n  Evaluate the STELLA <s-expression> in the PL-USER module."), KWD_POWERLOOM_N_ARGUMENTS, wrapInteger(1), KWD_POWERLOOM_HANDLER, SYM_POWERLOOM_STELLA_EVAL_OPTION_HANDLER, KWD_POWERLOOM_ERROR_ACTION, KWD_POWERLOOM_WARN);
      if (((boolean)(getSystemDefinition("powerloom", false)))) {
        defineLogicalHostProperty("PL", KWD_POWERLOOM_ROOT_DIRECTORY, wrapString(findSystemRootDirectory(getSystemDefinition("powerloom", true))));
      }
    }
  }
}

Keyword* KWD_POWERLOOM_KEY = NULL;

Keyword* KWD_POWERLOOM_DOCUMENTATION = NULL;

Keyword* KWD_POWERLOOM_N_ARGUMENTS = NULL;

Keyword* KWD_POWERLOOM_HANDLER = NULL;

Symbol* SYM_POWERLOOM_POWERLOOM_CODE_LOAD_ALL_EXTENSIONS_OPTION_HANDLER = NULL;

Keyword* KWD_POWERLOOM_ERROR_ACTION = NULL;

Keyword* KWD_POWERLOOM_ERROR = NULL;

Symbol* SYM_POWERLOOM_POWERLOOM_CODE_START_POWERLOOM_GUI_OPTION_HANDLER = NULL;

Keyword* KWD_POWERLOOM_WARN = NULL;

Keyword* KWD_POWERLOOM_KEY2 = NULL;

Keyword* KWD_POWERLOOM_PROPERTY = NULL;

Keyword* KWD_POWERLOOM_VALUE_TYPE = NULL;

Surrogate* SGT_POWERLOOM_STELLA_BOOLEAN = NULL;

Keyword* KWD_POWERLOOM_DEFAULT_VALUE = NULL;

Keyword* KWD_POWERLOOM_KEY3 = NULL;

Symbol* SYM_POWERLOOM_STELLA_EVAL_OPTION_HANDLER = NULL;

Keyword* KWD_POWERLOOM_ROOT_DIRECTORY = NULL;

Symbol* SYM_POWERLOOM_POWERLOOM_CODE_STARTUP_POWERLOOM = NULL;

Symbol* SYM_POWERLOOM_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella_powerloom_code


