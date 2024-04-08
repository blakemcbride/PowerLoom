//  -*- Mode: Java -*-
//
// StartupWebtoolsExamplesSystem.java

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
| Portions created by the Initial Developer are Copyright (C) 2003-2023      |
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

package edu.isi.webtools.examples.sample;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.webtools.objects.xml_objects.*;
import edu.isi.stella.*;

public class StartupWebtoolsExamplesSystem {
  public static void STARTUP_WEBTOOLS_EXAMPLES_SYSTEM() {
    synchronized (Stella.$BOOTSTRAP_LOCK$) {
      if (Stella.currentStartupTimePhaseP(0)) {
        if (!(Stella.systemStartedUpP("webtools", "/HTTP/WEBTOOLS"))) {
          edu.isi.webtools.StartupWebtoolsSystem.startupWebtoolsSystem();
        }
      }
      { Object OLD_$MODULE$_000 = Stella.$MODULE$.get();
        Object OLD_$CONTEXT$_000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/STELLA/XML-OBJECTS/SAMPLE", Stella.$STARTUP_TIME_PHASE$ > 1));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          if (Stella.currentStartupTimePhaseP(2)) {
            Sample.SYM_SAMPLE_STARTUP_WEBTOOLS_EXAMPLES_SYSTEM = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-WEBTOOLS-EXAMPLES-SYSTEM", null, 0)));
          }
          if (Stella.currentStartupTimePhaseP(6)) {
            Stella.finalizeClasses();
          }
          if (Stella.currentStartupTimePhaseP(7)) {
            Stella.defineFunctionObject("STARTUP-WEBTOOLS-EXAMPLES-SYSTEM", "(DEFUN STARTUP-WEBTOOLS-EXAMPLES-SYSTEM () :PUBLIC? TRUE :C-CALLABLE? TRUE :C-NAMESPACE-PREFIX \"stella_\")", Native.find_java_method("edu.isi.webtools.examples.sample.StartupWebtoolsExamplesSystem", "STARTUP_WEBTOOLS_EXAMPLES_SYSTEM", new java.lang.Class [] {}), null);
            { MethodSlot function = Symbol.lookupFunction(Sample.SYM_SAMPLE_STARTUP_WEBTOOLS_EXAMPLES_SYSTEM);

              KeyValueList.setDynamicSlotValue(function.dynamicSlots, Sample.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("StartupWebtoolsExamplesSystem"), Stella.NULL_STRING_WRAPPER);
            }
          }
          if (Stella.currentStartupTimePhaseP(8)) {
            Stella.finalizeSlots();
            Stella.cleanupUnfinalizedClasses();
          }
          if (Stella.currentStartupTimePhaseP(9)) {
            Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("/STELLA/XML-OBJECTS/SAMPLE")))));
            { int phase = Stella.NULL_INTEGER;
              int ITER_000 = 0;
              int UPPER_BOUND_001 = 9;

              for (;ITER_000 <= UPPER_BOUND_001; ITER_000 = ITER_000 + 1) {
                phase = ITER_000;
                Stella.$STARTUP_TIME_PHASE$ = phase;
                _StartupSampleContents.STARTUP_SAMPLE_CONTENTS();
                edu.isi.webtools.examples.addressexample._StartupAddressExample.STARTUP_ADDRESS_EXAMPLE();
                edu.isi.webtools.examples.addressdemo._StartupAddressDemo.STARTUP_ADDRESS_DEMO();
                edu.isi.webtools.examples.fetchcontent._StartupFetchDemoContent.STARTUP_FETCH_DEMO_CONTENT();
                edu.isi.webtools.examples.fetch._StartupFetchDemo.STARTUP_FETCH_DEMO();
              }
            }
            Stella.$STARTUP_TIME_PHASE$ = 999;
          }

        } finally {
          Stella.$CONTEXT$.set(OLD_$CONTEXT$_000);
          Stella.$MODULE$.set(OLD_$MODULE$_000);
        }
      }
    }
  }

}
