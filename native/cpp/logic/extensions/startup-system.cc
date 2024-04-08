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

#include "logic/extensions/powerloom-extensions-system.hh"

namespace stella_plx {
  using namespace stella_utilities;
  using namespace pli;
  using namespace logic;
  using namespace stella;

void startupPowerloomExtensionsSystem() {
  // Should be synchronized on process lock oBOOTSTRAP_LOCKo
  {
    if (currentStartupTimePhaseP(0)) {
      if (!(systemStartedUpP("stella", "/STELLA"))) {
        startupStellaSystem();
      }
      if (!(systemStartedUpP("logic", "/LOGIC"))) {
        startupLogicSystem();
      }
      if (!(systemStartedUpP("utilities", "/UTILITIES"))) {
        startupUtilitiesSystem();
      }
    }
    if (currentStartupTimePhaseP(1)) {
      defineModuleFromStringifiedSource("/PLX", "(:LISP-PACKAGE \"STELLA\" :JAVA-PACKAGE \"edu.isi.powerloom.extensions\" :JAVA-CATCHALL-CLASS \"Extensions\" :CLEARABLE? FALSE :CODE-ONLY? TRUE :USES (\"STELLA\" \"LOGIC\" \"PLI\" \"UTILITIES\"))");
      defineModuleFromStringifiedSource("/UNIT-SUPPORT", "(:USES (\"LOGIC\" \"STELLA\" \"UTILITIES\") :JAVA-PACKAGE \"edu.isi.powerloom.extensions.units\" :CPP-PACKAGE \"units\" :LISP-PACKAGE \"STELLA\" :JAVA-CATCHALL-CLASS \"Units\" :CASE-SENSITIVE? FALSE :CLEARABLE? FALSE :CODE-ONLY? TRUE)");
      defineModuleFromStringifiedSource("/UNIT-KB", "(:INCLUDES () :JAVA-PACKAGE \"edu.isi.powerloom.extensions.units\" :CPP-PACKAGE \"units\" :LISP-PACKAGE \"STELLA\" :JAVA-CATCHALL-CLASS \"Units\" :CASE-SENSITIVE? FALSE :CLEARABLE? TRUE)");
      defineModuleFromStringifiedSource("/TIMEPOINT-SUPPORT", "(:USES (\"LOGIC\" \"STELLA\" \"UTILITIES\") :CPP-PACKAGE \"timepoint\" :JAVA-PACKAGE \"edu.isi.powerloom.extensions.timepoint\" :LISP-PACKAGE \"STELLA\" :JAVA-CATCHALL-CLASS \"Timepoint\" :CASE-SENSITIVE? FALSE :CODE-ONLY? TRUE :CLEARABLE? FALSE)");
      defineModuleFromStringifiedSource("/TIMEPOINT-KB", "(:INCLUDES () :CPP-PACKAGE \"timepoint\" :JAVA-PACKAGE \"edu.isi.powerloom.extensions.timepoint\" :LISP-PACKAGE \"STELLA\" :JAVA-CATCHALL-CLASS \"Timepoint\" :CASE-SENSITIVE? FALSE :CLEARABLE? TRUE)");
    }
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/PLX", oSTARTUP_TIME_PHASEo > 1));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      if (currentStartupTimePhaseP(2)) {
        SYM_STARTUP_SYSTEM_PLX_STARTUP_POWERLOOM_EXTENSIONS_SYSTEM = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-POWERLOOM-EXTENSIONS-SYSTEM", NULL, 0)));
        SYM_STARTUP_SYSTEM_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
      }
      if (currentStartupTimePhaseP(6)) {
        finalizeClasses();
      }
      if (currentStartupTimePhaseP(7)) {
        defineFunctionObject("STARTUP-POWERLOOM-EXTENSIONS-SYSTEM", "(DEFUN STARTUP-POWERLOOM-EXTENSIONS-SYSTEM () :PUBLIC? TRUE :C-CALLABLE? TRUE :C-NAMESPACE-PREFIX \"stella_\")", ((cpp_function_code)(&startupPowerloomExtensionsSystem)), NULL);
        { MethodSlot* function = lookupFunction(SYM_STARTUP_SYSTEM_PLX_STARTUP_POWERLOOM_EXTENSIONS_SYSTEM);

          setDynamicSlotValue(function->dynamicSlots, SYM_STARTUP_SYSTEM_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("StartupPowerloomExtensionsSystem"), NULL_STRING_WRAPPER);
        }
      }
      if (currentStartupTimePhaseP(8)) {
        finalizeSlots();
        cleanupUnfinalizedClasses();
      }
      if (currentStartupTimePhaseP(9)) {
        inModule(((StringWrapper*)(copyConsTree(wrapString("/PLX")))));
        { int phase = NULL_INTEGER;
          int iter004 = 0;
          int upperBound005 = 9;

          for  (; iter004 <= upperBound005; 
                iter004 = iter004 + 1) {
            phase = iter004;
            oSTARTUP_TIME_PHASEo = phase;
            startupExtensions();
            units::startupUnitSupport();
            units::startupUnitKb();
            timepoint::startupTimepointSupport();
            timepoint::startupTimepointKb();
          }
        }
        oSTARTUP_TIME_PHASEo = 999;
      }
    }
  }
}

extern "C" void stella_startupPowerloomExtensionsSystem() {
  // C-callable wrapper for `startupPowerloomExtensionsSystem'.
  startupPowerloomExtensionsSystem();
}

Symbol* SYM_STARTUP_SYSTEM_PLX_STARTUP_POWERLOOM_EXTENSIONS_SYSTEM = NULL;

Symbol* SYM_STARTUP_SYSTEM_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella_plx
