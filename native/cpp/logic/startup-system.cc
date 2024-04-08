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

#include "logic/logic-system.hh"

namespace logic {
  using namespace stella;

void startupLogicSystem() {
  // Should be synchronized on process lock oBOOTSTRAP_LOCKo
  {
    if (currentStartupTimePhaseP(0)) {
      if (!(systemStartedUpP("stella", "/STELLA"))) {
        startupStellaSystem();
      }
    }
    if (currentStartupTimePhaseP(1)) {
      defineModuleFromStringifiedSource("/LOGIC", "(:LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"logic\" :JAVA-PACKAGE \"edu.isi.powerloom.logic\" :CLEARABLE? FALSE :CODE-ONLY? TRUE)");
      defineModuleFromStringifiedSource("/PL-KERNEL-KB", "(:DOCUMENTATION \"Defines foundation classes and relations for PowerLoom.\" :CPP-PACKAGE \"pl_kernel_kb\" :JAVA-PACKAGE \"edu.isi.powerloom.pl_kernel_kb\" :USES (\"LOGIC\" \"STELLA\") :SHADOW (COLLECTION SET RELATION FUNCTION CLASS LIST VALUE ARITY INVERSE NAME QUANTITY FLOOR CEILING LOG LOG10 EXP EXPT) :NICKNAME \"PL-KERNEL\" :PROTECT-SURROGATES? TRUE)");
      defineModuleFromStringifiedSource("/PL-KERNEL-KB/PL-USER", "(:DOCUMENTATION \"The default module for PowerLoom users.  It does not\ncontain any local declarations or axioms, but it includes other modules\nneeded to call PowerLoom functions.\" :INCLUDES (\"PL-KERNEL\") :USES (\"LOGIC\" \"STELLA\"))");
      defineModuleFromStringifiedSource("/PL-ANONYMOUS", "(:DOCUMENTATION \"Holds names of system-generated anonymous objects such as prototypes.\nUsers should never allocate any names in this module.\" :CASE-SENSITIVE? TRUE :USES ())");
      defineModuleFromStringifiedSource("/PL-KERNEL-KB/LOOM-API", "(:DOCUMENTATION \"Defines a Loom API for PowerLoom.\" :LISP-PACKAGE \"LOOM-API\" :INCLUDES \"PL-KERNEL\" :USES (\"LOGIC\" \"STELLA\") :SHADOW (NAMED?) :PROTECT-SURROGATES? TRUE)");
      defineModuleFromStringifiedSource("/PL-KERNEL-KB/KIF-FRAME-ONTOLOGY", "(:DOCUMENTATION \"Defines KIF-compatible frame predicates following\nOntolingua conventions.\" :USES (\"LOGIC\" \"STELLA\"))");
      defineModuleFromStringifiedSource("/PL-KERNEL-KB/CYC-FRAME-ONTOLOGY", "(:DOCUMENTATION \"Defines Cyc-compatible frame predicates.\" :USES (\"LOGIC\" \"STELLA\"))");
      defineModuleFromStringifiedSource("/CHAMELEON", "(:DOCUMENTATION \"Namespace for Chameleon relations\" :INCLUDES () :USES () :NICKNAME \"CHAM\" :PROTECT-SURROGATES? TRUE)");
      defineModuleFromStringifiedSource("/PLI", "(:DOCUMENTATION \"Defines the PowerLoom API.\" :USES (\"LOGIC\" \"STELLA\") :SHADOW (GET-OBJECT GET-RELATION GET-MODULE CHANGE-MODULE CLEAR-MODULE LOAD LOAD-IN-MODULE LOAD-STREAM LOAD-STREAM-IN-MODULE GET-RULES PRINT-RULES RUN-FORWARD-RULES SAVE-MODULE CREATE-OBJECT DESTROY-OBJECT REGISTER-SPECIALIST-FUNCTION REGISTER-COMPUTATION-FUNCTION ASSERT RETRACT CONCEIVE EVALUATE EVALUATE-STRING IS-TRUE IS-FALSE IS-UNKNOWN ASK RETRIEVE CREATE-ENUMERATED-SET RESET-POWERLOOM CLEAR-CACHES POWERLOOM GET-PROPERTY SET-PROPERTY PRINT-PROPERTIES) :API? TRUE :LISP-PACKAGE \"PLI\" :CPP-PACKAGE \"pli\" :JAVA-PACKAGE \"edu.isi.powerloom\" :JAVA-CATCHALL-CLASS \"PLI\" :CODE-ONLY? TRUE)");
    }
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      if (currentStartupTimePhaseP(2)) {
        SYM_STARTUP_SYSTEM_LOGIC_STARTUP_LOGIC_SYSTEM = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-LOGIC-SYSTEM", NULL, 0)));
        SYM_STARTUP_SYSTEM_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
      }
      if (currentStartupTimePhaseP(6)) {
        finalizeClasses();
      }
      if (currentStartupTimePhaseP(7)) {
        defineFunctionObject("STARTUP-LOGIC-SYSTEM", "(DEFUN STARTUP-LOGIC-SYSTEM () :PUBLIC? TRUE :C-CALLABLE? TRUE :C-NAMESPACE-PREFIX \"stella_\")", ((cpp_function_code)(&startupLogicSystem)), NULL);
        { MethodSlot* function = lookupFunction(SYM_STARTUP_SYSTEM_LOGIC_STARTUP_LOGIC_SYSTEM);

          setDynamicSlotValue(function->dynamicSlots, SYM_STARTUP_SYSTEM_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("StartupLogicSystem"), NULL_STRING_WRAPPER);
        }
      }
      if (currentStartupTimePhaseP(8)) {
        finalizeSlots();
        cleanupUnfinalizedClasses();
      }
      if (currentStartupTimePhaseP(9)) {
        inModule(((StringWrapper*)(copyConsTree(wrapString("/LOGIC")))));
        { int phase = NULL_INTEGER;
          int iter067 = 0;
          int upperBound068 = 9;

          for  (; iter067 <= upperBound068; 
                iter067 = iter067 + 1) {
            phase = iter067;
            oSTARTUP_TIME_PHASEo = phase;
            startupLogicMacros();
            startupSequenceIndices();
            startupKifIn();
            startupPropositions();
            startupBacklinks();
            startupPropagate();
            startupInferenceCaches();
            startupDescriptions();
            startupNormalize();
            startupRules();
            startupQuery();
            startupJustifications();
            startupPartialMatch();
            startupMachineLearning();
            startupRuleInduction();
            startupNeuralNetwork();
            startupCaseBased();
            startupChameleon();
            startupGoalCaches();
            startupStrategies();
            startupExplanations();
            startupWhynot();
            startupKifOut();
            startupPrint();
            startupGenerate();
            startupSpecialists();
            startupSpecialize();
            startupOptimize();
            startupClassify();
            startupLogicIn();
            pl_kernel_kb::startupPlKernelKb();
            pl_kernel_kb::startupArithmetic();
            startupFrameSupport();
            pl_kernel_kb_pl_kernel_kb_loom_api::startupLoomSupport();
            startupLoomToKif();
            startupApiSupport();
            pli::startupPli();
            startupPowerloom();
            startupTools();
          }
        }
        oSTARTUP_TIME_PHASEo = 999;
      }
    }
  }
}

extern "C" void stella_startupLogicSystem() {
  // C-callable wrapper for `startupLogicSystem'.
  startupLogicSystem();
}

Symbol* SYM_STARTUP_SYSTEM_LOGIC_STARTUP_LOGIC_SYSTEM = NULL;

Symbol* SYM_STARTUP_SYSTEM_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
