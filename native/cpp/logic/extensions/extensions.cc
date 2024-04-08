//  -*- Mode: C++ -*-

// extensions.cc

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

#include "logic/extensions/powerloom-extensions-system.hh"

namespace stella_plx {
  using namespace stella_utilities;
  using namespace pli;
  using namespace logic;
  using namespace stella;

int main() {
  std::cout << "Initializing STELLA..." << std::endl;
  startupStellaSystem();
  std::cout << "Initializing PowerLoom..." << std::endl;
  startupLogicSystem();
  std::cout << "Initializing PowerLoom extensions..." << std::endl;
  startupPowerloomExtensionsSystem();
  stella::stringChangeModule("PL-USER");
  logic::powerloom();
  return (1);
}

void startupExtensions() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/PLX", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      KWD_EXTENSIONS_DOCUMENTATION = ((Keyword*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 2)));
      SYM_EXTENSIONS_PLX_STARTUP_EXTENSIONS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-EXTENSIONS", NULL, 0)));
      SYM_EXTENSIONS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("MAIN", "(DEFUN (MAIN INTEGER) () :PUBLIC? TRUE)", ((cpp_function_code)(&main)), NULL);
      defineFunctionObject("STARTUP-EXTENSIONS", "(DEFUN STARTUP-EXTENSIONS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupExtensions)), NULL);
      { MethodSlot* function = lookupFunction(SYM_EXTENSIONS_PLX_STARTUP_EXTENSIONS);

        setDynamicSlotValue(function->dynamicSlots, SYM_EXTENSIONS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupExtensions"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("PLX")))));
    }
  }
}

Keyword* KWD_EXTENSIONS_DOCUMENTATION = NULL;

Symbol* SYM_EXTENSIONS_PLX_STARTUP_EXTENSIONS = NULL;

Symbol* SYM_EXTENSIONS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella_plx


