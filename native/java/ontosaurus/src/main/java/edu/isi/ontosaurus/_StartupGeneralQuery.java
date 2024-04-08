//  -*- Mode: Java -*-
//
// _StartupGeneralQuery.java

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

public class _StartupGeneralQuery {
  public static void startupGeneralQuery() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/ONTOSAURUS", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          OntosaurusUtil.KWD_SORT_BY = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("SORT-BY", null, 2)));
          OntosaurusUtil.KWD_VALUES = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("VALUES", null, 2)));
          OntosaurusUtil.KWD_TIMEOUT = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("TIMEOUT", null, 2)));
          OntosaurusUtil.SYM_LOGIC_ALL = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("ALL", Stella.getStellaModule("/LOGIC", true), 0)));
          OntosaurusUtil.SYM_STELLA_EXISTS = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("EXISTS", Stella.getStellaModule("/STELLA", true), 0)));
          OntosaurusUtil.SYM_LOGIC_JUSTIFICATION = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("JUSTIFICATION", Stella.getStellaModule("/LOGIC", true), 0)));
          OntosaurusUtil.KWD_LAY = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("LAY", null, 2)));
          OntosaurusUtil.KWD_POST = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("POST", null, 2)));
          OntosaurusUtil.KWD_INTERNAL_ERROR = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("INTERNAL-ERROR", null, 2)));
          OntosaurusUtil.SYM_ONTOSAURUS_STARTUP_GENERAL_QUERY = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-GENERAL-QUERY", null, 0)));
        }
        if (Stella.currentStartupTimePhaseP(4)) {
          OntosaurusUtil.$PRESET_QUERIES$.setDefaultValue(Stella.NIL);
          OntosaurusUtil.$GENERAL_QUERY_FORM_TEMPLATE$ = "<HTML>\n<HEAD>\n<BASE TARGET='answer'>\n<TITLE>Query Form</TITLE>\n</HEAD>\n<" + OntosaurusUtil.makeHtmlBodyTag(OntosaurusUtil.$STANDARD_BACKGROUND_COLOR$) + ">\n\n#$(FORM-HEADER)\n\n<H1>Query Form</H1>\n\nModule:&nbsp;#$(MODULE-MENU)\n<BR>\n\nQueries:&nbsp;#$(QUERY-MENU)\n<BR>\nNumber of answers:&nbsp;#$(NOF-ANSWERS-MENU)\n<BR>\n#$(QUERY-INPUT-AREA)\n<BR>\n#$(SUBMIT-BUTTON)\n#$(RESET-BUTTON)\n\n#$(FORM-TRAILER)\n\n<BR>\n<HR SIZE=2>\n" + OntosaurusUtil.$POWERLOOM_COPYRIGHT_TRAILER$ + "</BODY>\n</HTML>\n";
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("HTML-WRITE-QUERY-FORM-PAGE", "(DEFUN HTML-WRITE-QUERY-FORM-PAGE ((STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteQueryFormPage", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("YIELD-PRESET-QUERIES-SCRIPT", "(DEFUN (YIELD-PRESET-QUERIES-SCRIPT STRING) ((QUERIES (CONS OF (CONS OF STRING-WRAPPER)))))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "yieldPresetQueriesScript", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
          Stella.defineFunctionObject("YIELD-CHOICE-MENU-STRING", "(DEFUN (YIELD-CHOICE-MENU-STRING STRING) ((ITEMS CONS) (SELECTOPTIONS STRING)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "yieldChoiceMenuString", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons"), Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("YIELD-MODULE-MENU-STRING", "(DEFUN (YIELD-MODULE-MENU-STRING STRING) ((MODULES (CONS OF STRING-WRAPPER))))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "yieldModuleMenuString", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
          Stella.defineFunctionObject("YIELD-QUERY-MENU-STRING", "(DEFUN (YIELD-QUERY-MENU-STRING STRING) ((QUERIES (CONS OF (CONS OF STRING-WRAPPER)))))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "yieldQueryMenuString", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
          Stella.defineFunctionObject("YIELD-NOF-ANSWERS-MENU-STRING", "(DEFUN (YIELD-NOF-ANSWERS-MENU-STRING STRING) ((NOFANSWERS (CONS OF STRING-WRAPPER))))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "yieldNofAnswersMenuString", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
          Stella.defineFunctionObject("YIELD-TIMEOUTS-MENU-STRING", "(DEFUN (YIELD-TIMEOUTS-MENU-STRING STRING) ((TIMEOUTS (CONS OF STRING-WRAPPER))))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "yieldTimeoutsMenuString", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
          Stella.defineFunctionObject("HTML-WRITE-QUERY-FORM-PAGE-FROM-TEMPLATE", "(DEFUN HTML-WRITE-QUERY-FORM-PAGE-FROM-TEMPLATE ((STREAM OUTPUT-STREAM) (TEMPLATESTREAM INPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteQueryFormPageFromTemplate", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.OutputStream"), Native.find_java_class("edu.isi.stella.InputStream")}), null);
          Stella.defineFunctionObject("HTML-EXECUTE-QUERY", "(DEFUN HTML-EXECUTE-QUERY ((QUERYDATA KEY-VALUE-LIST) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlExecuteQuery", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.KeyValueList"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-EXECUTE-ASK-QUERY", "(DEFUN HTML-EXECUTE-ASK-QUERY ((QUERY CONS) (OPTIONS CONS) (MOD MODULE) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlExecuteAskQuery", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons"), Native.find_java_class("edu.isi.stella.Cons"), Native.find_java_class("edu.isi.stella.Module"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-EXECUTE-RETRIEVE-QUERY", "(DEFUN HTML-EXECUTE-RETRIEVE-QUERY ((NVALUES INTEGER) (VARIABLES CONS) (QUERY CONS) (OPTIONS CONS) (MOD MODULE) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlExecuteRetrieveQuery", new java.lang.Class [] {java.lang.Integer.TYPE, Native.find_java_class("edu.isi.stella.Cons"), Native.find_java_class("edu.isi.stella.Cons"), Native.find_java_class("edu.isi.stella.Cons"), Native.find_java_class("edu.isi.stella.Module"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("WRITE-EXPLANATION-ICON", "(DEFUN WRITE-EXPLANATION-ICON ((QUERY QUERY-ITERATOR) (BINDINGS CONS) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "writeExplanationIcon", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.QueryIterator"), Native.find_java_class("edu.isi.stella.Cons"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-WRITE-EXPLANATION-RESPONSE-PAGE", "(DEFUN HTML-WRITE-EXPLANATION-RESPONSE-PAGE ((MODULENAME STRING) (QUERY STRING) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteExplanationResponsePage", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PLOOM-QUERY-HANDLER", "(DEFUN PLOOM-QUERY-HANDLER ((XCHG /HTTP/HTTP-EXCHANGE)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "ploomQueryHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")}), null);
          Stella.defineFunctionObject("STARTUP-GENERAL-QUERY", "(DEFUN STARTUP-GENERAL-QUERY () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.ontosaurus._StartupGeneralQuery", "startupGeneralQuery", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(OntosaurusUtil.SYM_ONTOSAURUS_STARTUP_GENERAL_QUERY);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, OntosaurusUtil.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupGeneralQuery"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("ONTOSAURUS")))));
          Stella.defineGlobalVariableObject("(DEFSPECIAL *PRESET-QUERIES* (CONS OF (CONS OF STRING-WRAPPER)) NIL :DOCUMENTATION \"A list of preset queries to make entry easier.  Format is\n(\\\"Title\\\" \\\"ModuleName\\\" \\\"QueryBody\\\") \")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *GENERAL-QUERY-FORM-TEMPLATE* STRING (CONCATENATE \"<HTML>\n<HEAD>\n<BASE TARGET='answer'>\n<TITLE>Query Form</TITLE>\n</HEAD>\n<\" (MAKE-HTML-BODY-TAG *STANDARD-BACKGROUND-COLOR*) \">\n\n#$(FORM-HEADER)\n\n<H1>Query Form</H1>\n\nModule:&nbsp;#$(MODULE-MENU)\n<BR>\n\nQueries:&nbsp;#$(QUERY-MENU)\n<BR>\nNumber of answers:&nbsp;#$(NOF-ANSWERS-MENU)\n<BR>\n#$(QUERY-INPUT-AREA)\n<BR>\n#$(SUBMIT-BUTTON)\n#$(RESET-BUTTON)\n\n#$(FORM-TRAILER)\n\n<BR>\n<HR SIZE=2>\n\" *POWERLOOM-COPYRIGHT-TRAILER* \"</BODY>\n</HTML>\n\"))", null);
          edu.isi.webtools.http.Http.publishHandler("/ploom/ontosaurus/do-query", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "ploomQueryHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")}), Cons.cons(OntosaurusUtil.KWD_CONTENT_TYPE, Cons.cons(StringWrapper.wrapString(edu.isi.webtools.http.Http.getHttpMimeType(OntosaurusUtil.KWD_HTML, null)), Cons.cons(OntosaurusUtil.KWD_DOCUMENTATION, Cons.cons(StringWrapper.wrapString("Ontosaurus form to send PowerLoom queries."), Stella.NIL)))));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
