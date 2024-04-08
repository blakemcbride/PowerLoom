//  -*- Mode: C++ -*-

// startup-system.cc

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

void startupStellaSystem() {
  // Should be synchronized on process lock oBOOTSTRAP_LOCKo
  {
    if (currentStartupTimePhaseP(0)) {
      if (!(systemStartedUpP("stella", "/STELLA"))) {
        startup(false);
      }
    }
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      if (currentStartupTimePhaseP(2)) {
        SYM_STARTUP_SYSTEM_STELLA_STARTUP_STELLA_SYSTEM = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-STELLA-SYSTEM", NULL, 0)));
        SYM_STARTUP_SYSTEM_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
      }
      if (currentStartupTimePhaseP(6)) {
        finalizeClasses();
      }
      if (currentStartupTimePhaseP(7)) {
        defineFunctionObject("STARTUP-STELLA-SYSTEM", "(DEFUN STARTUP-STELLA-SYSTEM () :PUBLIC? TRUE :C-CALLABLE? TRUE :C-NAMESPACE-PREFIX \"stella_\")", ((cpp_function_code)(&startupStellaSystem)), NULL);
        { MethodSlot* function = lookupFunction(SYM_STARTUP_SYSTEM_STELLA_STARTUP_STELLA_SYSTEM);

          setDynamicSlotValue(function->dynamicSlots, SYM_STARTUP_SYSTEM_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("StartupStellaSystem"), NULL_STRING_WRAPPER);
        }
      }
      if (currentStartupTimePhaseP(8)) {
        finalizeSlots();
        cleanupUnfinalizedClasses();
      }
      if (currentStartupTimePhaseP(9)) {
        inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      }
    }
  }
}

extern "C" void stella_startupStellaSystem() {
  // C-callable wrapper for `startupStellaSystem'.
  startupStellaSystem();
}

Symbol* SYM_STARTUP_SYSTEM_STELLA_STARTUP_STELLA_SYSTEM = NULL;

Symbol* SYM_STARTUP_SYSTEM_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
