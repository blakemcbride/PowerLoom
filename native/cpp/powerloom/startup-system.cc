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

void startupPowerloomSystem() {
  // Should be synchronized on process lock oBOOTSTRAP_LOCKo
  {
    if (currentStartupTimePhaseP(0)) {
      if (!(systemStartedUpP("logic", "/LOGIC"))) {
        startupLogicSystem();
      }
      if (!(systemStartedUpP("powerloom-extensions", "/PLX"))) {
        startupPowerloomExtensionsSystem();
      }
    }
    if (currentStartupTimePhaseP(1)) {
      defineModuleFromStringifiedSource("/POWERLOOM-CODE", "(:LISP-PACKAGE \"STELLA\" :JAVA-PACKAGE \"edu.isi.powerloom\" :JAVA-CATCHALL-CLASS \"PowerLoom\" :CLEARABLE? FALSE :CODE-ONLY? TRUE :USES (\"STELLA\" \"LOGIC\" \"PLI\" \"PLX\" \"UTILITIES\"))");
    }
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/POWERLOOM-CODE", oSTARTUP_TIME_PHASEo > 1));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      if (currentStartupTimePhaseP(2)) {
        SYM_STARTUP_SYSTEM_POWERLOOM_CODE_STARTUP_POWERLOOM_SYSTEM = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-POWERLOOM-SYSTEM", NULL, 0)));
        SYM_STARTUP_SYSTEM_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
      }
      if (currentStartupTimePhaseP(6)) {
        finalizeClasses();
      }
      if (currentStartupTimePhaseP(7)) {
        defineFunctionObject("STARTUP-POWERLOOM-SYSTEM", "(DEFUN STARTUP-POWERLOOM-SYSTEM () :PUBLIC? TRUE :C-CALLABLE? TRUE :C-NAMESPACE-PREFIX \"stella_\")", ((cpp_function_code)(&startupPowerloomSystem)), NULL);
        { MethodSlot* function = lookupFunction(SYM_STARTUP_SYSTEM_POWERLOOM_CODE_STARTUP_POWERLOOM_SYSTEM);

          setDynamicSlotValue(function->dynamicSlots, SYM_STARTUP_SYSTEM_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("StartupPowerloomSystem"), NULL_STRING_WRAPPER);
        }
      }
      if (currentStartupTimePhaseP(8)) {
        finalizeSlots();
        cleanupUnfinalizedClasses();
      }
      if (currentStartupTimePhaseP(9)) {
        inModule(((StringWrapper*)(copyConsTree(wrapString("/POWERLOOM-CODE")))));
        { int phase = NULL_INTEGER;
          int iter000 = 0;
          int upperBound001 = 9;

          for  (; iter000 <= upperBound001; 
                iter000 = iter000 + 1) {
            phase = iter000;
            oSTARTUP_TIME_PHASEo = phase;
            startupPowerloom();
          }
        }
        oSTARTUP_TIME_PHASEo = 999;
      }
    }
  }
}

extern "C" void stella_startupPowerloomSystem() {
  // C-callable wrapper for `startupPowerloomSystem'.
  startupPowerloomSystem();
}

Symbol* SYM_STARTUP_SYSTEM_POWERLOOM_CODE_STARTUP_POWERLOOM_SYSTEM = NULL;

Symbol* SYM_STARTUP_SYSTEM_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella_powerloom_code
