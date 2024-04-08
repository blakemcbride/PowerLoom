//  -*- Mode: Java -*-
//
// _StartupTopWindow.java

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
 | Portions created by the Initial Developer are Copyright (C) 2000-2023      |
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

package edu.isi.ontosaurus;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.powerloom.logic.*;
import edu.isi.stella.*;

public class _StartupTopWindow {
  public static void startupTopWindow() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/ONTOSAURUS", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          OntosaurusUtil.KWD_GET = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("GET", null, 2)));
          OntosaurusUtil.SYM_ONTOSAURUS_STARTUP_TOP_WINDOW = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-TOP-WINDOW", null, 0)));
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("SAVING-ALLOWED?", "(DEFUN (SAVING-ALLOWED? BOOLEAN) ())", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "savingAllowedP", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("LOADING-ALLOWED?", "(DEFUN (LOADING-ALLOWED? BOOLEAN) ())", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "loadingAllowedP", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("EDITTING-ALLOWED?", "(DEFUN (EDITTING-ALLOWED? BOOLEAN) ())", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "edittingAllowedP", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("EDITTING-POSSIBLE?", "(DEFUN (EDITTING-POSSIBLE? BOOLEAN) ())", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "edittingPossibleP", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("CURRENT-EDIT-LOCK?", "(DEFUN (CURRENT-EDIT-LOCK? BOOLEAN) ())", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "currentEditLockP", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("SORTED-CONTEXTS", "(DEFUN (SORTED-CONTEXTS (CONS OF STRING-WRAPPER)) ())", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "sortedContexts", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("SERVE-CONTROL-PANEL-INTERNAL", "(DEFUN SERVE-CONTROL-PANEL-INTERNAL ((STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "serveControlPanelInternal", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("WRITE-THEORY-SECTION", "(DEFUN WRITE-THEORY-SECTION ((STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "writeTheorySection", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("WRITE-TOP-SECTION", "(DEFUN WRITE-TOP-SECTION ((STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "writeTopSection", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("WRITE-BOTTOM-SECTION", "(DEFUN WRITE-BOTTOM-SECTION ((STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "writeBottomSection", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("SERVE-CONTROL-PANEL-NEEDS-JAVASCRIPT", "(DEFUN SERVE-CONTROL-PANEL-NEEDS-JAVASCRIPT ((STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "serveControlPanelNeedsJavascript", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("CONTROL-PANEL-HANDLER", "(DEFUN CONTROL-PANEL-HANDLER ((XCHG /HTTP/HTTP-EXCHANGE)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "controlPanelHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")}), null);
          Stella.defineFunctionObject("STARTUP-TOP-WINDOW", "(DEFUN STARTUP-TOP-WINDOW () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.ontosaurus._StartupTopWindow", "startupTopWindow", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(OntosaurusUtil.SYM_ONTOSAURUS_STARTUP_TOP_WINDOW);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, OntosaurusUtil.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupTopWindow"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("ONTOSAURUS")))));
          Stella.defineGlobalVariableObject("(DEFGLOBAL *POWERLOOM-REFERENCE-MANUAL-URL* STRING \"http://www.isi.edu/isd/LOOM/PowerLoom/documentation/manual/manual_frame.html\")", null);
          edu.isi.webtools.http.Http.publishHandler("/ploom/ontosaurus/top-window.html", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "controlPanelHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")}), Cons.cons(OntosaurusUtil.KWD_CONTENT_TYPE, Cons.cons(StringWrapper.wrapString(edu.isi.webtools.http.Http.getHttpMimeType(OntosaurusUtil.KWD_HTML, null)), Cons.cons(OntosaurusUtil.KWD_DOCUMENTATION, Cons.cons(StringWrapper.wrapString("Ontosaurus control-panel handler."), Stella.NIL)))));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
