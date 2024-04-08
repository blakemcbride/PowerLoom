//  -*- Mode: Java -*-
//
// _StartupVisualize.java

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

public class _StartupVisualize {
  static void helpStartupVisualize1() {
    {
      OntosaurusUtil.SGT_ONTOSAURUS_VIZ_INFO = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("VIZ-INFO", null, 1)));
      OntosaurusUtil.SYM_STELLA_STREAM = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STREAM", Stella.getStellaModule("/STELLA", true), 0)));
      OntosaurusUtil.SYM_ONTOSAURUS_ALLOWED_OBJECTS = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("ALLOWED-OBJECTS", null, 0)));
      OntosaurusUtil.SYM_ONTOSAURUS_SHOW_RELATIONSp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("SHOW-RELATIONS?", null, 0)));
      OntosaurusUtil.SYM_ONTOSAURUS_SHOW_ATTRIBUTESp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("SHOW-ATTRIBUTES?", null, 0)));
      OntosaurusUtil.SYM_ONTOSAURUS_SHOW_RULESp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("SHOW-RULES?", null, 0)));
      OntosaurusUtil.SYM_ONTOSAURUS_ADD_TOPp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("ADD-TOP?", null, 0)));
      OntosaurusUtil.SYM_ONTOSAURUS_NODE_COLOR = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("NODE-COLOR", null, 0)));
      OntosaurusUtil.SYM_ONTOSAURUS_RELATION_COLOR = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("RELATION-COLOR", null, 0)));
      OntosaurusUtil.SYM_ONTOSAURUS_RELATION_STYLE = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("RELATION-STYLE", null, 0)));
      OntosaurusUtil.SYM_ONTOSAURUS_FONT_SIZE = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("FONT-SIZE", null, 0)));
      OntosaurusUtil.SYM_LOGIC_pRELATION = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("?RELATION", Stella.getStellaModule("/LOGIC", true), 0)));
      OntosaurusUtil.SYM_ONTOSAURUS_pDOMAIN = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("?DOMAIN", null, 0)));
      OntosaurusUtil.SYM_STELLA_AND = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("AND", Stella.getStellaModule("/STELLA", true), 0)));
      OntosaurusUtil.SYM_PL_KERNEL_KB_NTH_DOMAIN = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("NTH-DOMAIN", Stella.getStellaModule("/PL-KERNEL-KB", true), 0)));
      OntosaurusUtil.SYM_ONTOSAURUS_BINARY_RELATION = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("BINARY-RELATION", null, 0)));
      OntosaurusUtil.KWD_SINGLETONSp = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("SINGLETONS?", null, 2)));
      OntosaurusUtil.KWD_INFERENCE_LEVEL = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("INFERENCE-LEVEL", null, 2)));
      OntosaurusUtil.KWD_SHALLOW = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("SHALLOW", null, 2)));
      OntosaurusUtil.SYM_ONTOSAURUS_M_VIZ_INFOdVIZ_GET_BINARY_RELATIONS_OF_QUERY_000 = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("M-VIZ-INFO.VIZ-GET-BINARY-RELATIONS-OF-QUERY-000", null, 0)));
      OntosaurusUtil.SGT_ONTOSAURUS_M_VIZ_INFOdVIZ_GET_BINARY_RELATIONS_OF_MEMO_TABLE_000 = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("M-VIZ-INFO.VIZ-GET-BINARY-RELATIONS-OF-MEMO-TABLE-000", null, 1)));
      OntosaurusUtil.SYM_ONTOSAURUS_M_VIZ_INFOdVIZ_GET_BINARY_RELATIONS_OF_QUERY_001 = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("M-VIZ-INFO.VIZ-GET-BINARY-RELATIONS-OF-QUERY-001", null, 0)));
      OntosaurusUtil.SGT_PL_KERNEL_KB_CONCEPT = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("CONCEPT", Stella.getStellaModule("/PL-KERNEL-KB", true), 1)));
      OntosaurusUtil.KWD_MEDIUM = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("MEDIUM", null, 2)));
      OntosaurusUtil.SGT_ONTOSAURUS_F_VIZ_SERVER_EXPORT_OBJECT_MEMO_TABLE_000 = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("F-VIZ-SERVER-EXPORT-OBJECT-MEMO-TABLE-000", null, 1)));
      OntosaurusUtil.KWD_NOT_IMPLEMENTED = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("NOT-IMPLEMENTED", null, 2)));
      OntosaurusUtil.KWD_IMAGE_GIF = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("IMAGE-GIF", null, 2)));
      OntosaurusUtil.KWD_INPUT = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("INPUT", null, 2)));
      OntosaurusUtil.SYM_ONTOSAURUS_STARTUP_VISUALIZE = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-VISUALIZE", null, 0)));
    }
  }

  public static void startupVisualize() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/ONTOSAURUS", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          _StartupVisualize.helpStartupVisualize1();
        }
        if (Stella.currentStartupTimePhaseP(4)) {
          OntosaurusUtil.$VIZ_EXCLUDED_MODULES$ = List.list(Stella.NIL);
        }
        if (Stella.currentStartupTimePhaseP(5)) {
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("VIZ-INFO", "(DEFCLASS VIZ-INFO (STANDARD-OBJECT) :DOCUMENTATION \"Encapsulates all the options and local state information needed to\nvisualize a set of concepts as a graph.\" :SLOTS ((STREAM :TYPE OUTPUT-STREAM) (ALLOWED-OBJECTS :TYPE HASH-SET) (SHOW-RELATIONS? :TYPE BOOLEAN :INITIALLY *VIZ-SHOW-RELATIONS?*) (SHOW-ATTRIBUTES? :TYPE BOOLEAN :INITIALLY *VIZ-SHOW-ATTRIBUTES?*) (SHOW-RULES? :TYPE BOOLEAN :INITIALLY *VIZ-SHOW-RULES?*) (ADD-TOP? :TYPE BOOLEAN :INITIALLY *VIZ-ADD-TOP?*) (NODE-COLOR :TYPE STRING :INITIALLY *VIZ-NODE-COLOR*) (RELATION-COLOR :TYPE STRING :INITIALLY *VIZ-RELATION-COLOR*) (RELATION-STYLE :TYPE STRING :INITIALLY *VIZ-RELATION-STYLE*) (FONT-SIZE :TYPE INTEGER :INITIALLY *VIZ-FONT-SIZE*)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.ontosaurus.VizInfo", "newVizInfo", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.ontosaurus.VizInfo", "accessVizInfoSlotValue", new java.lang.Class [] {Native.find_java_class("edu.isi.ontosaurus.VizInfo"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("VIZ-GET-OBJECT-NAME", "(DEFUN (VIZ-GET-OBJECT-NAME STRING) ((OBJECT OBJECT)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "vizGetObjectName", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineMethodObject("(DEFMETHOD (VIZ-GENERATE-ONTOSAURUS-HANDLE STRING) ((SELF VIZ-INFO) (OBJECT STANDARD-OBJECT)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizGenerateOntosaurusHandle", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject")})), null);
          Stella.defineMethodObject("(DEFMETHOD (VIZ-GET-BINARY-RELATIONS-OF (CONS OF LOGIC-OBJECT)) ((SELF VIZ-INFO) (CONCEPT LOGIC-OBJECT)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizGetBinaryRelationsOf", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject")})), null);
          Stella.defineFunctionObject("VIZ-DOT-STRING", "(DEFUN (VIZ-DOT-STRING STRING) ((NAME STRING)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "vizDotString", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("VIZ-DOT-OBJECT-NAME", "(DEFUN (VIZ-DOT-OBJECT-NAME STRING) ((OBJECT OBJECT)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "vizDotObjectName", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineMethodObject("(DEFMETHOD (VIZ-EXCLUDED-MODULE? BOOLEAN) ((SELF VIZ-INFO) (MODULE MODULE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizExcludedModuleP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Module")})), null);
          Stella.defineMethodObject("(DEFMETHOD (VIZ-ALLOWED-OBJECT? BOOLEAN) ((SELF VIZ-INFO) (OBJECT OBJECT)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizAllowedObjectP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")})), null);
          Stella.defineMethodObject("(DEFMETHOD VIZ-ALLOW-OBJECT ((SELF VIZ-INFO) (OBJECT OBJECT)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizAllowObject", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")})), null);
          Stella.defineMethodObject("(DEFMETHOD VIZ-EXCLUDE-OBJECT ((SELF VIZ-INFO) (OBJECT OBJECT)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizExcludeObject", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")})), null);
          Stella.defineMethodObject("(DEFMETHOD VIZ-CONCEPT-TO-DOT-NODE ((SELF VIZ-INFO) (CONCEPT LOGIC-OBJECT) (MODULE MODULE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizConceptToDotNode", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.Module")})), null);
          Stella.defineMethodObject("(DEFMETHOD VIZ-ADD-CONCEPT-ATTRIBUTES-TO-DOT-NODE ((SELF VIZ-INFO) (CONCEPT LOGIC-OBJECT) (MODULE MODULE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizAddConceptAttributesToDotNode", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.Module")})), null);
          Stella.defineMethodObject("(DEFMETHOD VIZ-ADD-CONCEPT-RULES-TO-DOT-NODE ((SELF VIZ-INFO) (CONCEPT LOGIC-OBJECT) (MODULE MODULE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizAddConceptRulesToDotNode", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.Module")})), null);
          Stella.defineMethodObject("(DEFMETHOD VIZ-CONCEPT-LINKS-TO-DOT-EDGES ((SELF VIZ-INFO) (CONCEPT LOGIC-OBJECT) (MODULE MODULE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizConceptLinksToDotEdges", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.Module")})), null);
          Stella.defineMethodObject("(DEFMETHOD VIZ-EXPORT-CONCEPT-TO-DOT ((SELF VIZ-INFO) (CONCEPT LOGIC-OBJECT) (MODULE MODULE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizExportConceptToDot", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.Module")})), null);
          Stella.defineMethodObject("(DEFMETHOD VIZ-EXPORT-DOT-HEADER ((SELF VIZ-INFO)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizExportDotHeader", new java.lang.Class [] {})), null);
          Stella.defineMethodObject("(DEFMETHOD VIZ-EXPORT-DOT-TRAILER ((SELF VIZ-INFO)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizExportDotTrailer", new java.lang.Class [] {})), null);
          Stella.defineMethodObject("(DEFMETHOD VIZ-EXPORT-CONCEPT ((SELF VIZ-INFO) (CONCEPT LOGIC-OBJECT) (MODULE MODULE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizExportConcept", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.Module")})), null);
          Stella.defineMethodObject("(DEFMETHOD VIZ-EXPORT-CONCEPT-TREE ((SELF VIZ-INFO) (CONCEPT LOGIC-OBJECT) (MODULE MODULE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizExportConceptTree", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.Module")})), null);
          Stella.defineMethodObject("(DEFMETHOD VIZ-EXPORT-CONCEPTS ((SELF VIZ-INFO) (MODULE MODULE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizExportConcepts", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Module")})), null);
          Stella.defineMethodObject("(DEFMETHOD VIZ-EXPORT-MODULE ((SELF VIZ-INFO) (MODULE MODULE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizExportModule", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Module")})), null);
          Stella.defineMethodObject("(DEFMETHOD VIZ-EXPORT-HEADER ((SELF VIZ-INFO)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizExportHeader", new java.lang.Class [] {})), null);
          Stella.defineMethodObject("(DEFMETHOD VIZ-EXPORT-TRAILER ((SELF VIZ-INFO)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.VizInfo", "vizExportTrailer", new java.lang.Class [] {})), null);
          Stella.defineFunctionObject("VIZ-EXPORT-MODULE-TO-FILE", "(DEFUN VIZ-EXPORT-MODULE-TO-FILE ((MODULE MODULE) (FILE STRING)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "vizExportModuleToFile", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Module"), Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("VIZ-EXPORT-CONCEPT-TO-FILE", "(DEFUN VIZ-EXPORT-CONCEPT-TO-FILE ((CONCEPT LOGIC-OBJECT) (MODULE MODULE) (FILE STRING)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "vizExportConceptToFile", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.Module"), Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("VIZ-SERVER-AVAILABLE?", "(DEFUN (VIZ-SERVER-AVAILABLE? BOOLEAN) ())", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "vizServerAvailableP", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("VIZ-SERVER-EXPORT-MODULE", "(DEFUN VIZ-SERVER-EXPORT-MODULE ((MODULE MODULE) (OUT OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "vizServerExportModule", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Module"), Native.find_java_class("edu.isi.stella.OutputStream")}), null);
          Stella.defineFunctionObject("VIZ-SERVER-EXPORT-CONCEPT", "(DEFUN VIZ-SERVER-EXPORT-CONCEPT ((CONCEPT LOGIC-OBJECT) (MODULE MODULE) (OUT OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "vizServerExportConcept", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.stella.Module"), Native.find_java_class("edu.isi.stella.OutputStream")}), null);
          Stella.defineFunctionObject("VIZ-SERVER-EXPORT-OBJECT", "(DEFUN (VIZ-SERVER-EXPORT-OBJECT STRING) ((OBJECT OBJECT) (MODULE MODULE)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "vizServerExportObject", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.Module")}), null);
          Stella.defineFunctionObject("HELP-VIZ-SERVER-EXPORT-OBJECT", "(DEFUN (HELP-VIZ-SERVER-EXPORT-OBJECT STRING) ((OBJECT OBJECT) (MODULE MODULE)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "helpVizServerExportObject", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.Module")}), null);
          Stella.defineFunctionObject("VIZ-SERVER-HANDLER", "(DEFUN VIZ-SERVER-HANDLER ((XCHG /HTTP/HTTP-EXCHANGE)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "vizServerHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")}), null);
          Stella.defineFunctionObject("VIZ-SERVER-SERVE-IMAGE", "(DEFUN VIZ-SERVER-SERVE-IMAGE ((XCHG /HTTP/HTTP-EXCHANGE) (OBJECT OBJECT) (MODULE MODULE)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "vizServerServeImage", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange"), Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.Module")}), null);
          Stella.defineFunctionObject("VIZ-SERVER-SERVE-IMAGE-PLUS-MAP", "(DEFUN VIZ-SERVER-SERVE-IMAGE-PLUS-MAP ((XCHG /HTTP/HTTP-EXCHANGE) (OBJECT OBJECT) (MODULE MODULE)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "vizServerServeImagePlusMap", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange"), Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.Module")}), null);
          Stella.defineFunctionObject("STARTUP-VISUALIZE", "(DEFUN STARTUP-VISUALIZE () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.ontosaurus._StartupVisualize", "startupVisualize", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(OntosaurusUtil.SYM_ONTOSAURUS_STARTUP_VISUALIZE);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, OntosaurusUtil.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupVisualize"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("ONTOSAURUS")))));
          Stella.defineGlobalVariableObject("(DEFGLOBAL *VIZ-SHOW-RELATIONS?* BOOLEAN FALSE :DOCUMENTATION \"If true, show binary relations between domain and range concepts as edges.\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *VIZ-SHOW-ATTRIBUTES?* BOOLEAN FALSE :DOCUMENTATION \"If true, show binary relations as attributes (2nd box in a concept label).\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *VIZ-SHOW-RULES?* BOOLEAN FALSE :DOCUMENTATION \"If true, show defining rules (3rd box in a concept label).\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *VIZ-ADD-TOP?* BOOLEAN FALSE :DOCUMENTATION \"If true, put everything under artificial TOP node.\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *VIZ-NODE-COLOR* STRING \"yellow\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *VIZ-RELATION-COLOR* STRING \"blue\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *VIZ-RELATION-STYLE* STRING \"dashed\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *VIZ-FONT-SIZE* INTEGER 7)", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL VIZ-TOP STRING \"top\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL VIZ-UNKNOWN STRING \"unknown\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *VIZ-EXCLUDED-MODULES* (LIST OF MODULE) (LIST) :DOCUMENTATION \"Set of PowerLoom logic modules that shouldn't be visualized.\nBy default this is empty but it could be used to customize the visualizer.\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *VIZ-DOT-PROGRAM* STRING \"dot\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *VIZ-SERVER-ENABLED?* BOOLEAN TRUE :DOCUMENTATION \"If true, visualization requests are enabled.\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *VIZ-SERVER-IMAGE-MAPS-ENABLED?* BOOLEAN TRUE :DOCUMENTATION \"If true, visualization images will be linked with a\nclickable image map.\" :PUBLIC? TRUE)", null);
          try {
            OntosaurusUtil.shellCommand(Cons.cons(StringWrapper.wrapString(OntosaurusUtil.$VIZ_DOT_PROGRAM$), Cons.cons(StringWrapper.wrapString("-V"), Stella.NIL)), Stella.NIL);
          } catch (StellaException e) {
            if (!(Native.stringSearch(Native.stringDowncase(Stella.exceptionMessage(e)), "graphviz", Stella.NULL_INTEGER) != Stella.NULL_INTEGER)) {
              OntosaurusUtil.$VIZ_SERVER_ENABLEDp$ = false;
            }
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
