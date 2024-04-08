//  -*- Mode: Java -*-
//
// _StartupExplanations.java

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
 | Portions created by the Initial Developer are Copyright (C) 2002-2023      |
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

package edu.isi.powerloom.server.gui;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.stella.*;
import edu.isi.powerloom.logic.*;
import edu.isi.webtools.objects.xml_objects.*;
import edu.isi.webtools.soap.*;
import edu.isi.powerloom.server.*;

public class _StartupExplanations {
  public static void startupExplanations() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/POWERLOOM-SERVER/GUI-SERVER", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          GuiServer.KWD_KIF = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("KIF", null, 2)));
          GuiServer.SGT_LOGIC_PROPOSITION = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PROPOSITION", Stella.getStellaModule("/LOGIC", true), 1)));
          GuiServer.KWD_ISA = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("ISA", null, 2)));
          GuiServer.KWD_FUNCTION = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("FUNCTION", null, 2)));
          GuiServer.KWD_PREDICATE = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("PREDICATE", null, 2)));
          GuiServer.KWD_NOT = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("NOT", null, 2)));
          GuiServer.KWD_EQUIVALENT = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("EQUIVALENT", null, 2)));
          GuiServer.SGT_STELLA_LITERAL_WRAPPER = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("LITERAL-WRAPPER", Stella.getStellaModule("/STELLA", true), 1)));
          GuiServer.SGT_LOGIC_PATTERN_VARIABLE = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PATTERN-VARIABLE", Stella.getStellaModule("/LOGIC", true), 1)));
          GuiServer.SGT_STELLA_GENERALIZED_SYMBOL = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("GENERALIZED-SYMBOL", Stella.getStellaModule("/STELLA", true), 1)));
          GuiServer.SGT_STELLA_MODULE = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("MODULE", Stella.getStellaModule("/STELLA", true), 1)));
          GuiServer.SGT_STELLA_THING = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("THING", Stella.getStellaModule("/STELLA", true), 1)));
          GuiServer.KWD_JAVA_GUI_HTML = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("JAVA-GUI-HTML", null, 2)));
          GuiServer.KWD_HTML = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("HTML", null, 2)));
          GuiServer.KWD_LAY = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("LAY", null, 2)));
          GuiServer.KWD_KIF_ONTOSAURUS = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("KIF-ONTOSAURUS", null, 2)));
          GuiServer.KWD_BRIEF = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("BRIEF", null, 2)));
          GuiServer.SYM_GUI_SERVER_STARTUP_EXPLANATIONS = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-EXPLANATIONS", null, 0)));
        }
        if (Stella.currentStartupTimePhaseP(4)) {
          GuiServer.$PLGUI_URL_ACTION$.setDefaultValue("show");
          GuiServer.$PLGUI_EXPLANATION_TRACE_FILE$ = null;
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("PLGUI-HTML-PPRINT-OBJECT", "(DEFUN PLGUI-HTML-PPRINT-OBJECT ((SELF OBJECT) (STREAM OUTPUT-STREAM)))", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "plguiHtmlPprintObject", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.OutputStream")}), null);
          Stella.defineFunctionObject("PLGUI-HTML-PPRINT-ATOMIC-OBJECT", "(DEFUN PLGUI-HTML-PPRINT-ATOMIC-OBJECT ((SELF OBJECT) (STREAM NATIVE-OUTPUT-STREAM)) :PUBLIC? TRUE)", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "plguiHtmlPprintAtomicObject", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PRINT-PLGUI-URL", "(DEFUN PRINT-PLGUI-URL ((THE-OBJECT LOGIC-OBJECT) (NATIVESTREAM NATIVE-OUTPUT-STREAM)) :PUBLIC? TRUE :DOCUMENTATION \"Prints a URL following PowerLoom Plgui conventions.\")", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "printPlguiUrl", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PLGUI-WRITE-URL-IN-DETAIL", "(DEFUN PLGUI-WRITE-URL-IN-DETAIL ((STREAM NATIVE-OUTPUT-STREAM) (TARGET STRING) (ACTION STRING) (OBJECTTYPE STRING) (CONTEXTNAME STRING) (OBJECTNAME STRING) (OBJECTTITLE STRING) (RAWTITLE? BOOLEAN)))", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "plguiWriteUrlInDetail", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("PLGUI-WRITE-URL", "(DEFUN PLGUI-WRITE-URL ((STREAM NATIVE-OUTPUT-STREAM) (ACTION STRING) (OBJECTTYPE STRING) (OBJECT STANDARD-OBJECT)))", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "plguiWriteUrl", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.StandardObject")}), null);
          Stella.defineFunctionObject("PRINT-JUSTIFICATION-TO-HTML-FILE", "(DEFUN PRINT-JUSTIFICATION-TO-HTML-FILE ((JUSTIFICATION JUSTIFICATION) (FILE STRING)))", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "printJustificationToHtmlFile", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Justification"), Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("GET-JUSTIFICATION-STRING", "(DEFUN (GET-JUSTIFICATION-STRING STRING) ((JUSTIFICATION JUSTIFICATION)))", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "getJustificationString", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Justification")}), null);
          Stella.defineFunctionObject("STARTUP-EXPLANATIONS", "(DEFUN STARTUP-EXPLANATIONS () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.powerloom.server.gui._StartupExplanations", "startupExplanations", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(GuiServer.SYM_GUI_SERVER_STARTUP_EXPLANATIONS);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, GuiServer.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupExplanations"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("GUI-SERVER")))));
          Stella.defineGlobalVariableObject("(DEFSPECIAL *PLGUI-URL-ACTION* STRING \"show\" :DOCUMENTATION \"The action parameter for URL printing\" :PUBLIC? TRUE)", null);
          Logic.registerLogicDialectPrintFunction(GuiServer.KWD_JAVA_GUI_HTML, FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "plguiHtmlPprintObject", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.OutputStream")})));
          Stella.defineGlobalVariableObject("(DEFGLOBAL *PLGUI-EXPLANATION-TRACE-FILE* STRING NULL)", null);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
