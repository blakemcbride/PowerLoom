//  -*- Mode: Java -*-
//
// _StartupHtmlPprint.java

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

public class _StartupHtmlPprint {
  public static void startupHtmlPprint() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/ONTOSAURUS", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          OntosaurusUtil.SGT_STELLA_GENERALIZED_SYMBOL = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("GENERALIZED-SYMBOL", Stella.getStellaModule("/STELLA", true), 1)));
          OntosaurusUtil.SYM_ONTOSAURUS_STARTUP_HTML_PPRINT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-HTML-PPRINT", null, 0)));
        }
        if (Stella.currentStartupTimePhaseP(4)) {
          OntosaurusUtil.$ONTOSAURUS_URL_ACTION$.setDefaultValue("show");
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("PPRINT-ATOMIC-OBJECT-FOR-HTML-DEFINITION", "(DEFUN PPRINT-ATOMIC-OBJECT-FOR-HTML-DEFINITION ((SELF OBJECT) (STREAM NATIVE-OUTPUT-STREAM)) :PUBLIC? TRUE)", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintAtomicObjectForHtmlDefinition", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-ATOMIC-OBJECT-FOR-HTML", "(DEFUN PPRINT-ATOMIC-OBJECT-FOR-HTML ((SELF OBJECT) (STREAM NATIVE-OUTPUT-STREAM)) :PUBLIC? TRUE)", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintAtomicObjectForHtml", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-LITERAL-WRAPPER-FOR-HTML", "(DEFUN PPRINT-LITERAL-WRAPPER-FOR-HTML ((SELF LITERAL-WRAPPER) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintLiteralWrapperForHtml", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.LiteralWrapper"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("LOGIC-OBJECT-DISPLAY-TYPE", "(DEFUN (LOGIC-OBJECT-DISPLAY-TYPE STRING) ((OBJ LOGIC-OBJECT)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "logicObjectDisplayType", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject")}), null);
          Stella.defineFunctionObject("PRINT-ONTOSAURUS-URL", "(DEFUN PRINT-ONTOSAURUS-URL ((THE-OBJECT LOGIC-OBJECT) (NATIVESTREAM NATIVE-OUTPUT-STREAM)) :PUBLIC? TRUE :DOCUMENTATION \"Prints a URL following PowerLoom Ontosaurus conventions.\")", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "printOntosaurusUrl", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("STARTUP-HTML-PPRINT", "(DEFUN STARTUP-HTML-PPRINT () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.ontosaurus._StartupHtmlPprint", "startupHtmlPprint", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(OntosaurusUtil.SYM_ONTOSAURUS_STARTUP_HTML_PPRINT);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, OntosaurusUtil.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupHtmlPprint"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("ONTOSAURUS")))));
          Stella.defineGlobalVariableObject("(DEFSPECIAL *ONTOSAURUS-URL-ACTION* STRING \"show\" :DOCUMENTATION \"The action parameter for URL printing\" :PUBLIC? TRUE)", null);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
