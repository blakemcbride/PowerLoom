//  -*- Mode: Java -*-
//
// _StartupHtmlDescribeObject.java

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

public class _StartupHtmlDescribeObject {
  static void helpStartupHtmlDescribeObject1() {
    {
      OntosaurusUtil.KWD_CONCEPT = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("CONCEPT", null, 2)));
      OntosaurusUtil.KWD_RELATION = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("RELATION", null, 2)));
      OntosaurusUtil.KWD_CONTEXT = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("CONTEXT", null, 2)));
      OntosaurusUtil.KWD_INSTANCE = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("INSTANCE", null, 2)));
      OntosaurusUtil.KWD_QUERY = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("QUERY", null, 2)));
      OntosaurusUtil.KWD_OBJECT = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("OBJECT", null, 2)));
      OntosaurusUtil.KWD_PREORDER = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("PREORDER", null, 2)));
      OntosaurusUtil.SYM_STELLA_CODE_ONLYp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("CODE-ONLY?", Stella.getStellaModule("/STELLA", true), 0)));
      OntosaurusUtil.SYM_STELLA_NAMESPACEp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("NAMESPACE?", Stella.getStellaModule("/STELLA", true), 0)));
      OntosaurusUtil.KWD_MODULE = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("MODULE", null, 2)));
      OntosaurusUtil.KWD_EXACT = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("EXACT", null, 2)));
      OntosaurusUtil.KWD_CASE_INSENSITIVE = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("CASE-INSENSITIVE", null, 2)));
      OntosaurusUtil.KWD_SUBSTRING = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("SUBSTRING", null, 2)));
      OntosaurusUtil.KWD_WILDCARD = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("WILDCARD", null, 2)));
      OntosaurusUtil.KWD_REGEX = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("REGEX", null, 2)));
      OntosaurusUtil.SYM_ONTOSAURUS_PPRINT_ATOMIC_OBJECT_FOR_HTML = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PPRINT-ATOMIC-OBJECT-FOR-HTML", null, 0)));
      OntosaurusUtil.KWD_BAD_REQUEST = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("BAD-REQUEST", null, 2)));
      OntosaurusUtil.KWD_CONTENT_TYPE = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("CONTENT-TYPE", null, 2)));
      OntosaurusUtil.KWD_HTML = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("HTML", null, 2)));
      OntosaurusUtil.KWD_DOCUMENTATION = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("DOCUMENTATION", null, 2)));
      OntosaurusUtil.SYM_ONTOSAURUS_STARTUP_HTML_DESCRIBE_OBJECT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-HTML-DESCRIBE-OBJECT", null, 0)));
    }
  }

  public static void startupHtmlDescribeObject() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/ONTOSAURUS", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          _StartupHtmlDescribeObject.helpStartupHtmlDescribeObject1();
        }
        if (Stella.currentStartupTimePhaseP(4)) {
          OntosaurusUtil.$IMAGE_URL_RELATION$ = edu.isi.powerloom.PLI.sGetRelation("IMAGE-URL", "PL-USER", null);
          OntosaurusUtil.$DOCUMENTATION_RELATION$ = edu.isi.powerloom.PLI.sGetRelation("DOCUMENTATION", "PL-USER", null);
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("LOOKUP-TERM", "(DEFUN (LOOKUP-TERM STRING) ((TERM KEYWORD) (CAPITALIZED? BOOLEAN) (PLURAL? BOOLEAN)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "lookupTerm", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Keyword"), java.lang.Boolean.TYPE, java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("SAFE-OBJECT-NAME-STRING", "(DEFUN (SAFE-OBJECT-NAME-STRING STRING) ((INSTANCE LOGIC-OBJECT)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "safeObjectNameString", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject")}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-LOCATION", "(DEFUN HTML-DESCRIBE-LOCATION ((SELF LOGIC-OBJECT) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeLocation", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-WRITE-CONTEXT-VIEW-OPTION", "(DEFUN HTML-WRITE-CONTEXT-VIEW-OPTION ((STREAM NATIVE-OUTPUT-STREAM) (OBJECTNAME STRING) (CTX MODULE)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteContextViewOption", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.Module")}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-CONTEXT-VIEW", "(DEFUN HTML-DESCRIBE-CONTEXT-VIEW ((SELF LOGIC-OBJECT) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeContextView", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-DISPLAY-IMAGES", "(DEFUN HTML-DISPLAY-IMAGES ((SELF STANDARD-OBJECT) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDisplayImages", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-DISPLAY-DOCUMENTATION", "(DEFUN HTML-DISPLAY-DOCUMENTATION ((SELF STANDARD-OBJECT) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDisplayDocumentation", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-DISPLAY-SYNONYMS", "(DEFUN HTML-DISPLAY-SYNONYMS ((SELF OBJECT) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDisplaySynonyms", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-EQUIVALENTS", "(DEFUN HTML-DESCRIBE-EQUIVALENTS ((TITLE STRING) (HEAD STRING) (RELATION NAMED-DESCRIPTION) (STREAM NATIVE-OUTPUT-STREAM) (RULE? BOOLEAN)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeEquivalents", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.powerloom.logic.NamedDescription"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-ONE-SUB-LEVEL", "(DEFUN HTML-DESCRIBE-ONE-SUB-LEVEL ((OBJECT NAMED-DESCRIPTION) (DEPTH INTEGER) (CUTOFF INTEGER) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeOneSubLevel", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.NamedDescription"), java.lang.Integer.TYPE, java.lang.Integer.TYPE, Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-SUBS", "(DEFUN HTML-DESCRIBE-SUBS ((TITLE STRING) (HEAD STRING) (RELATION NAMED-DESCRIPTION) (STREAM NATIVE-OUTPUT-STREAM) (RULE? BOOLEAN)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeSubs", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.powerloom.logic.NamedDescription"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-ONE-SUPER-LEVEL", "(DEFUN HTML-DESCRIBE-ONE-SUPER-LEVEL ((DIRECTSUPERS (CONS OF NAMED-DESCRIPTION)) (ALREADYOUTPUT HASH-TABLE) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeOneSuperLevel", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons"), Native.find_java_class("edu.isi.stella.HashTable"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-SUPERS", "(DEFUN HTML-DESCRIBE-SUPERS ((TITLE STRING) (HEAD STRING) (RELATION NAMED-DESCRIPTION) (STREAM NATIVE-OUTPUT-STREAM) (RULE? BOOLEAN)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeSupers", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.powerloom.logic.NamedDescription"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-TYPES", "(DEFUN HTML-DESCRIBE-TYPES ((TITLE STRING) (HEAD STRING) (RELATION LOGIC-OBJECT) (STREAM NATIVE-OUTPUT-STREAM) (RULE? BOOLEAN)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeTypes", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-ONE-PARENT-WITH-SIBLINGS", "(DEFUN HTML-DESCRIBE-ONE-PARENT-WITH-SIBLINGS ((PARENT NAMED-DESCRIPTION) (CHILD NAMED-DESCRIPTION) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeOneParentWithSiblings", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.NamedDescription"), Native.find_java_class("edu.isi.powerloom.logic.NamedDescription"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HAS-CHILD-OTHER-THAN?", "(DEFUN (HAS-CHILD-OTHER-THAN? BOOLEAN) ((PARENT NAMED-DESCRIPTION) (CHILD NAMED-DESCRIPTION)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "hasChildOtherThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.NamedDescription"), Native.find_java_class("edu.isi.powerloom.logic.NamedDescription")}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-SIBLINGS", "(DEFUN HTML-DESCRIBE-SIBLINGS ((TITLE STRING) (HEAD STRING) (RELATION NAMED-DESCRIPTION) (STREAM NATIVE-OUTPUT-STREAM) (RULE? BOOLEAN)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeSiblings", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.powerloom.logic.NamedDescription"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-RULES", "(DEFUN HTML-DESCRIBE-RULES ((TITLE STRING) (HEAD STRING) (RELATION LOGIC-OBJECT) (STREAM NATIVE-OUTPUT-STREAM) (RULE? BOOLEAN)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeRules", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-FACTS", "(DEFUN HTML-DESCRIBE-FACTS ((TITLE STRING) (HEAD STRING) (RELATION LOGIC-OBJECT) (STREAM NATIVE-OUTPUT-STREAM) (FILTER-RULES? BOOLEAN) (RULE? BOOLEAN)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeFacts", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), java.lang.Boolean.TYPE, java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-INSTANCES", "(DEFUN HTML-DESCRIBE-INSTANCES ((TITLE STRING) (HEAD STRING) (RELATION NAMED-DESCRIPTION) (STREAM NATIVE-OUTPUT-STREAM) (RULE? BOOLEAN)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeInstances", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.powerloom.logic.NamedDescription"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-TUPLES", "(DEFUN HTML-DESCRIBE-TUPLES ((TITLE STRING) (HEAD STRING) (RELATION NAMED-DESCRIPTION) (STREAM NATIVE-OUTPUT-STREAM) (RULE? BOOLEAN)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeTuples", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.powerloom.logic.NamedDescription"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-NAMED-DESCRIPTION", "(DEFUN HTML-DESCRIBE-NAMED-DESCRIPTION ((CONCEPT NAMED-DESCRIPTION) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeNamedDescription", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.NamedDescription"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-INSTANCE", "(DEFUN HTML-DESCRIBE-INSTANCE ((INSTANCE LOGIC-OBJECT) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeInstance", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("CHILD-MODULES", "(DEFUN (CHILD-MODULES (CONS OF MODULE)) ((MODULE MODULE)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "childModules", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Module")}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-ONE-MODULE-SUB-LEVEL", "(DEFUN HTML-DESCRIBE-ONE-MODULE-SUB-LEVEL ((MODULE MODULE) (DEPTH INTEGER) (CUTOFF INTEGER) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeOneModuleSubLevel", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Module"), java.lang.Integer.TYPE, java.lang.Integer.TYPE, Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-MODULE-SUBS", "(DEFUN HTML-DESCRIBE-MODULE-SUBS ((TITLE STRING) (HEAD STRING) (MODULE MODULE) (STREAM NATIVE-OUTPUT-STREAM) (RULE? BOOLEAN)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeModuleSubs", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.Module"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-ONE-MODULE-SUPER-LEVEL", "(DEFUN HTML-DESCRIBE-ONE-MODULE-SUPER-LEVEL ((MODULE MODULE) (ALREADYOUTPUT HASH-TABLE) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeOneModuleSuperLevel", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Module"), Native.find_java_class("edu.isi.stella.HashTable"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-MODULE-SUPERS", "(DEFUN HTML-DESCRIBE-MODULE-SUPERS ((TITLE STRING) (HEAD STRING) (MODULE MODULE) (STREAM NATIVE-OUTPUT-STREAM) (RULE? BOOLEAN)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeModuleSupers", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.Module"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("HTML-DISPLAY-MODULE-STATS", "(DEFUN HTML-DISPLAY-MODULE-STATS ((TITLE STRING) (HEAD STRING) (MODULE MODULE) (STREAM NATIVE-OUTPUT-STREAM) (RULE? BOOLEAN)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDisplayModuleStats", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.Module"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream"), java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("HTML-DESCRIBE-MODULE", "(DEFUN HTML-DESCRIBE-MODULE ((MODULE MODULE) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlDescribeModule", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Module"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-UNKNOWN-MODULE-RESPONSE", "(DEFUN HTML-UNKNOWN-MODULE-RESPONSE ((ITEMTYPE KEYWORD) (ITEMNAME STRING) (MODULENAME STRING) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlUnknownModuleResponse", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Keyword"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-UNKNOWN-OBJECT-RESPONSE", "(DEFUN HTML-UNKNOWN-OBJECT-RESPONSE ((ITEMTYPE KEYWORD) (ITEMNAME STRING) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlUnknownObjectResponse", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Keyword"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-WRITE-RELATION-RESPONSE-PAGE", "(DEFUN HTML-WRITE-RELATION-RESPONSE-PAGE ((RELATION NAMED-DESCRIPTION) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteRelationResponsePage", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.NamedDescription"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-WRITE-INSTANCE-RESPONSE-PAGE", "(DEFUN HTML-WRITE-INSTANCE-RESPONSE-PAGE ((INSTANCE LOGIC-OBJECT) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteInstanceResponsePage", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-WRITE-OBJECT-RESPONSE-PAGE-INTERNAL", "(DEFUN HTML-WRITE-OBJECT-RESPONSE-PAGE-INTERNAL ((OBJECT OBJECT) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteObjectResponsePageInternal", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-WRITE-MODULE-RESPONSE-PAGE-INTERNAL", "(DEFUN HTML-WRITE-MODULE-RESPONSE-PAGE-INTERNAL ((MODULE MODULE) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteModuleResponsePageInternal", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Module"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-WRITE-MODULE-RESPONSE-PAGE", "(DEFUN HTML-WRITE-MODULE-RESPONSE-PAGE ((MODULENAME STRING) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteModuleResponsePage", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-WRITE-OBJECT-RESPONSE-PAGE", "(DEFUN HTML-WRITE-OBJECT-RESPONSE-PAGE ((MODULENAME STRING) (OBJECTNAME STRING) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteObjectResponsePage", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("FIND-CANDIDATE-OBJECTS", "(DEFUN (FIND-CANDIDATE-OBJECTS (LIST OF LOGIC-OBJECT)) ((OBJECTNAME STRING) (OBJECTTYPE STRING) (MATCHTYPE KEYWORD)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "findCandidateObjects", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.Keyword")}), null);
          Stella.defineFunctionObject("RESOLVE-SYNONYMS", "(DEFUN (RESOLVE-SYNONYMS LOGIC-OBJECT) ((OBJ LOGIC-OBJECT)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "resolveSynonyms", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject")}), null);
          Stella.defineFunctionObject("HTML-WRITE-FIND-OBJECT-RESPONSE-PAGE", "(DEFUN HTML-WRITE-FIND-OBJECT-RESPONSE-PAGE ((MODULENAME STRING) (OBJECTNAME STRING) (OBJECTTYPE STRING) (MATCHTYPE KEYWORD) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteFindObjectResponsePage", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.Keyword"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-WRITE-MULTIPLE-CHOICE-PAGE", "(DEFUN HTML-WRITE-MULTIPLE-CHOICE-PAGE ((SEARCHSTRING STRING) (CANDIDATEOBJECTS (LIST OF LOGIC-OBJECT)) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlWriteMultipleChoicePage", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.List"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HTML-POWERLOOM-RESPONSE", "(DEFUN HTML-POWERLOOM-RESPONSE ((ACTION STRING) (OBJECTTYPE STRING) (MODULENAME STRING) (OBJECTNAME STRING) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "htmlPowerloomResponse", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("DO-ACTION-HANDLER", "(DEFUN DO-ACTION-HANDLER ((XCHG /HTTP/HTTP-EXCHANGE)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "doActionHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")}), null);
          Stella.defineFunctionObject("STARTUP-HTML-DESCRIBE-OBJECT", "(DEFUN STARTUP-HTML-DESCRIBE-OBJECT () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.ontosaurus._StartupHtmlDescribeObject", "startupHtmlDescribeObject", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(OntosaurusUtil.SYM_ONTOSAURUS_STARTUP_HTML_DESCRIBE_OBJECT);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, OntosaurusUtil.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupHtmlDescribeObject"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("ONTOSAURUS")))));
          Stella.defineGlobalVariableObject("(DEFGLOBAL *IMAGE-URL-RELATION* LOGIC-OBJECT (/PLI/S-GET-RELATION \"IMAGE-URL\" \"PL-USER\" NULL))", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *DOCUMENTATION-RELATION* LOGIC-OBJECT (/PLI/S-GET-RELATION \"DOCUMENTATION\" \"PL-USER\" NULL))", null);
          edu.isi.webtools.http.Http.publishHandler("/ploom/ontosaurus/do-action", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "doActionHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")}), Cons.cons(OntosaurusUtil.KWD_CONTENT_TYPE, Cons.cons(StringWrapper.wrapString(edu.isi.webtools.http.Http.getHttpMimeType(OntosaurusUtil.KWD_HTML, null)), Cons.cons(OntosaurusUtil.KWD_DOCUMENTATION, Cons.cons(StringWrapper.wrapString("Various parameterized Ontosaurus actions to describe objects."), Stella.NIL)))));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
