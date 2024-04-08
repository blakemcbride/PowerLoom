//  -*- Mode: Java -*-
//
// _StartupHtmlUtilities.java

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

public class _StartupHtmlUtilities {
  public static void startupHtmlUtilities() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/ONTOSAURUS", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          OntosaurusUtil.SGT_LOGIC_LOGIC_OBJECT = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("LOGIC-OBJECT", Stella.getStellaModule("/LOGIC", true), 1)));
          OntosaurusUtil.SGT_STELLA_MODULE = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("MODULE", Stella.getStellaModule("/STELLA", true), 1)));
          OntosaurusUtil.SYM_ONTOSAURUS_STARTUP_HTML_UTILITIES = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-HTML-UTILITIES", null, 0)));
        }
        if (Stella.currentStartupTimePhaseP(4)) {
          OntosaurusUtil.$POWERLOOM_COPYRIGHT_TRAILER$ = Logic.$POWERLOOM_VERSION_STRING$ + "<BR>" + "Copyright 2000-" + Native.integerToString(((long)(CalendarDate.makeCurrentDateTime().getCalendarDate(Stella.getLocalTimeZone(), new Object[3])))) + " University of Southern California Information Sciences Institute";
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("MAKE-HTML-BODY-TAG", "(DEFUN (MAKE-HTML-BODY-TAG STRING) ((BACKGROUNDCOLOR STRING)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "makeHtmlBodyTag", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("HTML-LINE-BREAK", "(DEFUN HTML-LINE-BREAK ((STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlLineBreak", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("GET-HTML-OBJECT-TYPE", "(DEFUN (GET-HTML-OBJECT-TYPE STRING) ((OBJECT OBJECT)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "getHtmlObjectType", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineFunctionObject("GET-HTML-OBJECT-LOOKUP-MODULE", "(DEFUN (GET-HTML-OBJECT-LOOKUP-MODULE STRING) ((OBJECT OBJECT)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "getHtmlObjectLookupModule", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineFunctionObject("GET-HTML-OBJECT-HANDLE", "(DEFUN (GET-HTML-OBJECT-HANDLE STRING) ((OBJECT OBJECT)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "getHtmlObjectHandle", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineFunctionObject("GET-HTML-OBJECT-TITLE", "(DEFUN (GET-HTML-OBJECT-TITLE STRING) ((OBJECT OBJECT)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "getHtmlObjectTitle", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineFunctionObject("GET-HTML-OBJECT-TITLE-PREFIX", "(DEFUN (GET-HTML-OBJECT-TITLE-PREFIX STRING) ((OBJECT OBJECT)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "getHtmlObjectTitlePrefix", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineFunctionObject("HTML-WRITE-URL-IN-DETAIL", "(DEFUN HTML-WRITE-URL-IN-DETAIL ((STREAM NATIVE-OUTPUT-STREAM) (ACTION STRING) (OBJECTTYPE STRING) (CONTEXTNAME STRING) (OBJECTNAME STRING)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteUrlInDetail", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("HTML-WRITE-3PART-HREF-IN-DETAIL", "(DEFUN HTML-WRITE-3PART-HREF-IN-DETAIL ((STREAM NATIVE-OUTPUT-STREAM) (TARGET STRING) (ACTION STRING) (OBJECT-TYPE STRING) (CONTEXT-NAME STRING) (OBJECT-NAME STRING) (OBJECT-TITLE-PREFIX STRING) (OBJECT-TITLE STRING) (OBJECT-TITLE-SUFFIX STRING) (RAWTITLE? BOOLEAN)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWrite3PartHrefInDetail", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("HTML-WRITE-HREF-IN-DETAIL", "(DEFUN HTML-WRITE-HREF-IN-DETAIL ((STREAM NATIVE-OUTPUT-STREAM) (TARGET STRING) (ACTION STRING) (OBJECTTYPE STRING) (CONTEXTNAME STRING) (OBJECTNAME STRING) (OBJECTTITLE STRING) (RAWTITLE? BOOLEAN)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteHrefInDetail", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("HTML-WRITE-HREF", "(DEFUN HTML-WRITE-HREF ((STREAM NATIVE-OUTPUT-STREAM) (ACTION STRING) (OBJECTTYPE STRING) (OBJECT STANDARD-OBJECT)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteHref", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.StandardObject")}), null);
          Stella.defineFunctionObject("HTML-WRITE-URL", "(DEFUN HTML-WRITE-URL ((STREAM NATIVE-OUTPUT-STREAM) (ACTION STRING) (OBJECT STANDARD-OBJECT)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteUrl", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.StandardObject")}), null);
          Stella.defineFunctionObject("HTML-WRITE-JAVASCRIPT", "(DEFUN HTML-WRITE-JAVASCRIPT ((STREAM NATIVE-OUTPUT-STREAM) (JS STRING)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteJavascript", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("HTML-WRITE-HEADER-WITH-TABLE", "(DEFUN HTML-WRITE-HEADER-WITH-TABLE ((STREAM NATIVE-OUTPUT-STREAM) (TITLE STRING) (HEAD STRING)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteHeaderWithTable", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("WRITE-BOOKMARK-ICON", "(DEFUN WRITE-BOOKMARK-ICON ((INSTANCE LOGIC-OBJECT) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "writeBookmarkIcon", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-EMIT-IMAGE", "(DEFUN HTML-EMIT-IMAGE ((STREAM NATIVE-OUTPUT-STREAM) (IMAGEURL STRING) (ALTERNATETEXT STRING) (WIDTH INTEGER) (HEIGHT INTEGER) (ALIGNMENT STRING) (BORDER INTEGER)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlEmitImage", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), java.lang.Integer.TYPE, java.lang.Integer.TYPE, Native.find_java_class("java.lang.String"), java.lang.Integer.TYPE}), null);
          Stella.defineFunctionObject("HTML-DISPLAY-STRING-IN-PARAGRAPHS", "(DEFUN HTML-DISPLAY-STRING-IN-PARAGRAPHS ((S STRING) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDisplayStringInParagraphs", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("WRITE-POWERLOOM-TRAILER", "(DEFUN WRITE-POWERLOOM-TRAILER ((STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "writePowerloomTrailer", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("STARTUP-HTML-UTILITIES", "(DEFUN STARTUP-HTML-UTILITIES () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.ontosaurus._StartupHtmlUtilities", "startupHtmlUtilities", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(OntosaurusUtil.SYM_ONTOSAURUS_STARTUP_HTML_UTILITIES);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, OntosaurusUtil.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupHtmlUtilities"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("ONTOSAURUS")))));
          Stella.defineGlobalVariableObject("(DEFGLOBAL *ERROR-BACKGROUND-COLOR* STRING \"FF9999\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *STANDARD-BACKGROUND-COLOR* STRING \"99CCFF\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *MODULE-BACKGROUND-COLOR* STRING \"9999CC\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *CONTROL-BACKGROUND-COLOR* STRING \"6699CC\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *ANSWER-BACKGROUND-COLOR* STRING \"99FFFF\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *FORM-BACKGROUND-COLOR* STRING \"6699CC\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *HREF-PREFIX-TAG* STRING \"FONT COLOR='#666666' SIZE=-1\" :DOCUMENTATION \"Tag used for prefix part of HREF generation in\n`html-write-3part-href-in-detail'.\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *HREF-SUFFIX-TAG* STRING \"FONT COLOR='#666666' SIZE=-1\" :DOCUMENTATION \"Tag used for suffix part of HREF generation in\n`html-write-3part-href-in-detail'.\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *POWERLOOM-COPYRIGHT-TRAILER* STRING (CONCATENATE *POWERLOOM-VERSION-STRING* \"<BR>\" \"Copyright 2000-\" (INTEGER-TO-STRING (GET-CALENDAR-DATE (MAKE-CURRENT-DATE-TIME) (GET-LOCAL-TIME-ZONE))) \" University of Southern California Information Sciences Institute\"))", null);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
