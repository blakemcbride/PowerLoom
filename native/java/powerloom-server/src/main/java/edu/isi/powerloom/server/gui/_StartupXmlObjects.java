//  -*- Mode: Java -*-
//
// _StartupXmlObjects.java

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

public class _StartupXmlObjects {
  static void helpStartupXmlObjects1() {
    {
      GuiServer.SGT_GUI_SERVER_PLString = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLString", null, 1)));
      GuiServer.SYM_GUI_SERVER_Value = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("Value", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLSurrogate = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLSurrogate", null, 1)));
      GuiServer.SYM_LOGIC_ID = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("ID", Stella.getStellaModule("/LOGIC", true), 0)));
      GuiServer.SGT_GUI_SERVER_ServerException = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("ServerException", null, 1)));
      GuiServer.SYM_GUI_SERVER_Type = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("Type", null, 0)));
      GuiServer.SYM_GUI_SERVER_Message = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("Message", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLModuleContainer = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLModuleContainer", null, 1)));
      GuiServer.SYM_GUI_SERVER_PLModule = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PLModule", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLModule = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLModule", null, 1)));
      GuiServer.SYM_GUI_SERVER_ModuleName = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("ModuleName", null, 0)));
      GuiServer.SYM_GUI_SERVER_SourceString = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("SourceString", null, 0)));
      GuiServer.SYM_GUI_SERVER_CppPackage = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("CppPackage", null, 0)));
      GuiServer.SYM_GUI_SERVER_LispPackage = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("LispPackage", null, 0)));
      GuiServer.SYM_GUI_SERVER_JavaPackage = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("JavaPackage", null, 0)));
      GuiServer.SYM_GUI_SERVER_JavaCatchallClass = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("JavaCatchallClass", null, 0)));
      GuiServer.SYM_GUI_SERVER_Documentation = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("Documentation", null, 0)));
      GuiServer.SYM_GUI_SERVER_API = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("API", null, 0)));
      GuiServer.SYM_GUI_SERVER_CaseSensitive = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("CaseSensitive", null, 0)));
      GuiServer.SYM_GUI_SERVER_PLSurrogate = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PLSurrogate", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLConcept = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLConcept", null, 1)));
      GuiServer.SYM_GUI_SERVER_ConceptName = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("ConceptName", null, 0)));
      GuiServer.SYM_GUI_SERVER_Module = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("Module", null, 0)));
      GuiServer.SYM_GUI_SERVER_PLConcept = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PLConcept", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLConceptContainer = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLConceptContainer", null, 1)));
      GuiServer.SGT_GUI_SERVER_PLRelation = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLRelation", null, 1)));
      GuiServer.SYM_GUI_SERVER_RelationName = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("RelationName", null, 0)));
      GuiServer.SYM_GUI_SERVER_IsFunction = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("IsFunction", null, 0)));
      GuiServer.SYM_GUI_SERVER_IsClosed = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("IsClosed", null, 0)));
      GuiServer.SYM_GUI_SERVER_PLRelation = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PLRelation", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLRelationContainer = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLRelationContainer", null, 1)));
      GuiServer.SGT_GUI_SERVER_PLInstance = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLInstance", null, 1)));
      GuiServer.SYM_GUI_SERVER_InstanceName = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("InstanceName", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLInstanceContainer = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLInstanceContainer", null, 1)));
      GuiServer.SYM_GUI_SERVER_PLInstance = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PLInstance", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLProposition = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLProposition", null, 1)));
      GuiServer.SYM_GUI_SERVER_PropositionName = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PropositionName", null, 0)));
      GuiServer.SYM_GUI_SERVER_IsStrict = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("IsStrict", null, 0)));
      GuiServer.SYM_GUI_SERVER_IsAsserted = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("IsAsserted", null, 0)));
      GuiServer.SYM_GUI_SERVER_IsRule = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("IsRule", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLPropositionContainer = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLPropositionContainer", null, 1)));
      GuiServer.SYM_GUI_SERVER_PLProposition = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PLProposition", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLRule = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLRule", null, 1)));
      GuiServer.SYM_GUI_SERVER_RuleName = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("RuleName", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLVariable = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLVariable", null, 1)));
      GuiServer.SYM_GUI_SERVER_VariableName = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("VariableName", null, 0)));
      GuiServer.SYM_GUI_SERVER_VariableType = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("VariableType", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLVariableList = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLVariableList", null, 1)));
      GuiServer.SYM_GUI_SERVER_PLVariable = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PLVariable", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLModuleFileList = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLModuleFileList", null, 1)));
      GuiServer.SYM_GUI_SERVER_PLModuleFile = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PLModuleFile", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLModuleFile = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLModuleFile", null, 1)));
      GuiServer.SYM_GUI_SERVER_KBName = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("KBName", null, 0)));
      GuiServer.SYM_GUI_SERVER_KBDescription = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("KBDescription", null, 0)));
      GuiServer.SYM_GUI_SERVER_FileName = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("FileName", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLFile = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLFile", null, 1)));
      GuiServer.SYM_GUI_SERVER_PLFileContent = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PLFileContent", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLFileContent = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLFileContent", null, 1)));
      GuiServer.SGT_GUI_SERVER_PLDirectory = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLDirectory", null, 1)));
      GuiServer.SYM_GUI_SERVER_DirectoryName = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("DirectoryName", null, 0)));
    }
  }

  static void helpStartupXmlObjects2() {
    {
      GuiServer.SGT_GUI_SERVER_PLDirectoryContents = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLDirectoryContents", null, 1)));
      GuiServer.SYM_GUI_SERVER_PLDirectory = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PLDirectory", null, 0)));
      GuiServer.SYM_GUI_SERVER_PLFile = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PLFile", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLSurrogateCollection = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLSurrogateCollection", null, 1)));
      GuiServer.SGT_GUI_SERVER_PLObjectUnion = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLObjectUnion", null, 1)));
      GuiServer.SYM_GUI_SERVER_LiteralValue = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("LiteralValue", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLTuple = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLTuple", null, 1)));
      GuiServer.SYM_GUI_SERVER_PLObjectUnion = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PLObjectUnion", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLQuery = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLQuery", null, 1)));
      GuiServer.SYM_GUI_SERVER_IsAsk = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("IsAsk", null, 0)));
      GuiServer.SYM_GUI_SERVER_QueryName = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("QueryName", null, 0)));
      GuiServer.SYM_GUI_SERVER_Query = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("Query", null, 0)));
      GuiServer.SYM_GUI_SERVER_InferenceLevel = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("InferenceLevel", null, 0)));
      GuiServer.SYM_GUI_SERVER_Timeout = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("Timeout", null, 0)));
      GuiServer.SYM_GUI_SERVER_Moveout = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("Moveout", null, 0)));
      GuiServer.SYM_GUI_SERVER_MatchMode = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("MatchMode", null, 0)));
      GuiServer.SYM_GUI_SERVER_NumResults = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("NumResults", null, 0)));
      GuiServer.SYM_GUI_SERVER_MinScore = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("MinScore", null, 0)));
      GuiServer.SYM_GUI_SERVER_MaxUnknowns = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("MaxUnknowns", null, 0)));
      GuiServer.SYM_GUI_SERVER_MaximizeScore = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("MaximizeScore", null, 0)));
      GuiServer.SYM_GUI_SERVER_DontOptimize = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("DontOptimize", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLQueryResult = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLQueryResult", null, 1)));
      GuiServer.SYM_GUI_SERVER_PLTuple = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PLTuple", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLSearchParameter = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLSearchParameter", null, 1)));
      GuiServer.SYM_GUI_SERVER_SearchString = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("SearchString", null, 0)));
      GuiServer.SYM_GUI_SERVER_SearchConcept = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("SearchConcept", null, 0)));
      GuiServer.SYM_GUI_SERVER_SearchRelation = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("SearchRelation", null, 0)));
      GuiServer.SYM_GUI_SERVER_SearchInstance = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("SearchInstance", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLSearchResult = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLSearchResult", null, 1)));
      GuiServer.SYM_GUI_SERVER_PLSearchResultItem = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PLSearchResultItem", null, 0)));
      GuiServer.SGT_GUI_SERVER_PLSearchResultItem = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLSearchResultItem", null, 1)));
      GuiServer.SGT_GUI_SERVER_PLServerInfo = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PLServerInfo", null, 1)));
      GuiServer.SYM_GUI_SERVER_AllowRemoteFileBrowsing = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("AllowRemoteFileBrowsing", null, 0)));
      GuiServer.SYM_GUI_SERVER_STARTUP_XML_OBJECTS = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-XML-OBJECTS", null, 0)));
      GuiServer.SYM_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", Stella.getStellaModule("/STELLA", true), 0)));
    }
  }

  public static void startupXmlObjects() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/POWERLOOM-SERVER/GUI-SERVER", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          _StartupXmlObjects.helpStartupXmlObjects1();
          _StartupXmlObjects.helpStartupXmlObjects2();
        }
        if (Stella.currentStartupTimePhaseP(5)) {
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLString", "(DEFCLASS |PLString| (|XMLObject|) :PUBLIC-SLOTS ((|Value| :TYPE STRING)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "new_PLString", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "access_PLString_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLSurrogate", "(DEFCLASS |PLSurrogate| (|XMLObject|) :PUBLIC-SLOTS ((ID :TYPE STRING)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLSurrogate", "new_PLSurrogate", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLSurrogate", "access_PLSurrogate_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLSurrogate"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("ServerException", "(DEFCLASS |ServerException| (|XMLObject|) :PUBLIC-SLOTS ((|Type| :TYPE STRING) (|Message| :TYPE STRING)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.ServerException", "new_ServerException", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.ServerException", "access_ServerException_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.ServerException"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLModuleContainer", "(DEFCLASS |PLModuleContainer| (|XMLObject|) :PUBLIC-SLOTS ((|PLModule| :TYPE (LIST OF |PLModule|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLModuleContainer", "new_PLModuleContainer", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLModuleContainer", "access_PLModuleContainer_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLModuleContainer"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLModule", "(DEFCLASS |PLModule| (|XMLObject|) :PUBLIC-SLOTS ((|ModuleName| :TYPE STRING) (|SourceString| :TYPE STRING) (|CppPackage| :TYPE STRING) (|LispPackage| :TYPE STRING) (|JavaPackage| :TYPE STRING) (|JavaCatchallClass| :TYPE STRING) (|Documentation| :TYPE STRING) (API :TYPE STRING) (|CaseSensitive| :TYPE STRING) (|PLModule| :TYPE (LIST OF |PLModule|)) (|PLSurrogate| :TYPE (LIST OF |PLSurrogate|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLModule", "new_PLModule", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLModule", "access_PLModule_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLModule"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLConcept", "(DEFCLASS |PLConcept| (|XMLObject|) :PUBLIC-SLOTS ((|ConceptName| :TYPE STRING) (|Module| :TYPE STRING) (|SourceString| :TYPE STRING) (|PLConcept| :TYPE (LIST OF |PLConcept|)) (|PLSurrogate| :TYPE (LIST OF |PLSurrogate|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLConcept", "new_PLConcept", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLConcept", "access_PLConcept_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLConcept"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLConceptContainer", "(DEFCLASS |PLConceptContainer| (|XMLObject|) :PUBLIC-SLOTS ((|PLConcept| :TYPE (LIST OF |PLConcept|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLConceptContainer", "new_PLConceptContainer", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLConceptContainer", "access_PLConceptContainer_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLConceptContainer"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLRelation", "(DEFCLASS |PLRelation| (|XMLObject|) :PUBLIC-SLOTS ((|RelationName| :TYPE STRING) (|SourceString| :TYPE STRING) (|Module| :TYPE STRING) (|IsFunction| :TYPE STRING) (|IsClosed| :TYPE STRING) (|PLRelation| :TYPE (LIST OF |PLRelation|)) (|PLSurrogate| :TYPE (LIST OF |PLSurrogate|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLRelation", "new_PLRelation", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLRelation", "access_PLRelation_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLRelation"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLRelationContainer", "(DEFCLASS |PLRelationContainer| (|XMLObject|) :PUBLIC-SLOTS ((|PLRelation| :TYPE (LIST OF |PLRelation|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLRelationContainer", "new_PLRelationContainer", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLRelationContainer", "access_PLRelationContainer_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLRelationContainer"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLInstance", "(DEFCLASS |PLInstance| (|XMLObject|) :PUBLIC-SLOTS ((|InstanceName| :TYPE STRING) (|Module| :TYPE STRING) (|SourceString| :TYPE STRING)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLInstance", "new_PLInstance", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLInstance", "access_PLInstance_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLInstance"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLInstanceContainer", "(DEFCLASS |PLInstanceContainer| (|XMLObject|) :PUBLIC-SLOTS ((|PLInstance| :TYPE (LIST OF |PLInstance|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLInstanceContainer", "new_PLInstanceContainer", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLInstanceContainer", "access_PLInstanceContainer_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLInstanceContainer"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLProposition", "(DEFCLASS |PLProposition| (|XMLObject|) :PUBLIC-SLOTS ((|PropositionName| :TYPE STRING) (|IsStrict| :TYPE STRING) (|IsAsserted| :TYPE STRING) (|IsRule| :TYPE STRING)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLProposition", "new_PLProposition", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLProposition", "access_PLProposition_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLProposition"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLPropositionContainer", "(DEFCLASS |PLPropositionContainer| (|XMLObject|) :PUBLIC-SLOTS ((|PLProposition| :TYPE (LIST OF |PLProposition|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLPropositionContainer", "new_PLPropositionContainer", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLPropositionContainer", "access_PLPropositionContainer_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLPropositionContainer"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLRule", "(DEFCLASS |PLRule| (|XMLObject|) :PUBLIC-SLOTS ((|RuleName| :TYPE STRING)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLRule", "new_PLRule", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLRule", "access_PLRule_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLRule"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLVariable", "(DEFCLASS |PLVariable| (|XMLObject|) :PUBLIC-SLOTS ((|VariableName| :TYPE |PLString|) (|VariableType| :TYPE |PLSurrogate|)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLVariable", "new_PLVariable", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLVariable", "access_PLVariable_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLVariable"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLVariableList", "(DEFCLASS |PLVariableList| (|XMLObject|) :PUBLIC-SLOTS ((|PLVariable| :TYPE (LIST OF |PLVariable|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLVariableList", "new_PLVariableList", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLVariableList", "access_PLVariableList_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLVariableList"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLModuleFileList", "(DEFCLASS |PLModuleFileList| (|XMLObject|) :PUBLIC-SLOTS ((|PLModuleFile| :TYPE (LIST OF |PLModuleFile|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLModuleFileList", "new_PLModuleFileList", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLModuleFileList", "access_PLModuleFileList_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLModuleFileList"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLModuleFile", "(DEFCLASS |PLModuleFile| (|XMLObject|) :PUBLIC-SLOTS ((|KBName| :TYPE STRING) (|ModuleName| :TYPE STRING) (|KBDescription| :TYPE STRING) (|FileName| :TYPE STRING)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLModuleFile", "new_PLModuleFile", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLModuleFile", "access_PLModuleFile_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLModuleFile"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLFile", "(DEFCLASS |PLFile| (|XMLObject|) :PUBLIC-SLOTS ((|FileName| :TYPE STRING) (|PLFileContent| :TYPE |PLFileContent|)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLFile", "new_PLFile", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLFile", "access_PLFile_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLFile"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLFileContent", "(DEFCLASS |PLFileContent| (|XMLObject|) :PUBLIC-SLOTS ((|textContent| :ENCODING-SCHEME :BASE64)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLFileContent", "new_PLFileContent", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLDirectory", "(DEFCLASS |PLDirectory| (|XMLObject|) :PUBLIC-SLOTS ((|DirectoryName| :TYPE STRING)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLDirectory", "new_PLDirectory", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLDirectory", "access_PLDirectory_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLDirectory"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLDirectoryContents", "(DEFCLASS |PLDirectoryContents| (|XMLObject|) :PUBLIC-SLOTS ((|DirectoryName| :TYPE STRING) (|PLDirectory| :TYPE (LIST OF |PLDirectory|)) (|PLFile| :TYPE (LIST OF |PLFile|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLDirectoryContents", "new_PLDirectoryContents", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLDirectoryContents", "access_PLDirectoryContents_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLDirectoryContents"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLSurrogateCollection", "(DEFCLASS |PLSurrogateCollection| (|XMLObject|) :PUBLIC-SLOTS ((|PLSurrogate| :TYPE (LIST OF |PLSurrogate|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLSurrogateCollection", "new_PLSurrogateCollection", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLSurrogateCollection", "access_PLSurrogateCollection_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLSurrogateCollection"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLObjectUnion", "(DEFCLASS |PLObjectUnion| (|XMLObject|) :PUBLIC-SLOTS ((|Type| :TYPE STRING) (|PLSurrogate| :TYPE |PLSurrogate|) (|LiteralValue| :TYPE STRING)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLObjectUnion", "new_PLObjectUnion", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLObjectUnion", "access_PLObjectUnion_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLObjectUnion"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLTuple", "(DEFCLASS |PLTuple| (|XMLObject|) :PUBLIC-SLOTS ((|PLObjectUnion| :TYPE (LIST OF |PLObjectUnion|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLTuple", "new_PLTuple", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLTuple", "access_PLTuple_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLTuple"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLQuery", "(DEFCLASS |PLQuery| (|XMLObject|) :PUBLIC-SLOTS ((|IsAsk| :TYPE STRING) (|QueryName| :TYPE STRING) (|Query| :TYPE STRING) (|Module| :TYPE STRING) (|InferenceLevel| :TYPE STRING) (|Timeout| :TYPE STRING) (|Moveout| :TYPE STRING) (|MatchMode| :TYPE STRING) (|NumResults| :TYPE STRING) (|MinScore| :TYPE STRING) (|MaxUnknowns| :TYPE STRING) (|MaximizeScore| :TYPE STRING) (|DontOptimize| :TYPE STRING)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLQuery", "new_PLQuery", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLQuery", "access_PLQuery_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLQuery"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLQueryResult", "(DEFCLASS |PLQueryResult| (|XMLObject|) :PUBLIC-SLOTS ((|PLTuple| :TYPE (LIST OF |PLTuple|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLQueryResult", "new_PLQueryResult", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLQueryResult", "access_PLQueryResult_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLQueryResult"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLSearchParameter", "(DEFCLASS |PLSearchParameter| (|XMLObject|) :PUBLIC-SLOTS ((|ModuleName| :TYPE STRING) (|SearchString| :TYPE STRING) (|SearchConcept| :TYPE STRING) (|SearchRelation| :TYPE STRING) (|SearchInstance| :TYPE STRING) (|CaseSensitive| :TYPE STRING)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLSearchParameter", "new_PLSearchParameter", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLSearchParameter", "access_PLSearchParameter_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLSearchParameter"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLSearchResult", "(DEFCLASS |PLSearchResult| (|XMLObject|) :PUBLIC-SLOTS ((|PLSearchResultItem| :TYPE (LIST OF |PLSearchResultItem|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLSearchResult", "new_PLSearchResult", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLSearchResult", "access_PLSearchResult_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLSearchResult"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLSearchResultItem", "(DEFCLASS |PLSearchResultItem| (|XMLObject|) :PUBLIC-SLOTS ((|ModuleName| :TYPE STRING) (|PLObjectUnion| :TYPE |PLObjectUnion|)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLSearchResultItem", "new_PLSearchResultItem", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLSearchResultItem", "access_PLSearchResultItem_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLSearchResultItem"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PLServerInfo", "(DEFCLASS |PLServerInfo| (|XMLObject|) :PUBLIC-SLOTS ((|AllowRemoteFileBrowsing| :TYPE STRING)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLServerInfo", "new_PLServerInfo", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.gui.PLServerInfo", "access_PLServerInfo_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLServerInfo"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((X |PLConcept|) (Y OBJECT)) :DOCUMENTATION \"Return TRUE if `x' and `y' represent the same Concept\" :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLConcept", "objectEqlP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")})), null);
          Stella.defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((X |PLRelation|) (Y OBJECT)) :DOCUMENTATION \"Return TRUE if `x' and `y' represent the same Relation\" :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLRelation", "objectEqlP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")})), null);
          Stella.defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((X |PLInstance|) (Y OBJECT)) :DOCUMENTATION \"Return TRUE if `x' and `y' represent the same Instance\" :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLInstance", "objectEqlP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")})), null);
          Stella.defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((X |PLProposition|) (Y OBJECT)) :DOCUMENTATION \"Return TRUE if `x' and `y' represent the same Propositions\" :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLProposition", "objectEqlP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")})), null);
          Stella.defineFunctionObject(" |PLSurrogate<|", "(DEFUN (|PLSurrogate<| BOOLEAN) ((INST1 |PLSurrogate|) (INST2 |PLSurrogate|)))", Native.find_java_method("edu.isi.powerloom.server.gui.PLSurrogate", "PLSurrogateL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLSurrogate"), Native.find_java_class("edu.isi.powerloom.server.gui.PLSurrogate")}), null);
          Stella.defineFunctionObject(" |PLModule<|", "(DEFUN (|PLModule<| BOOLEAN) ((INST1 |PLModule|) (INST2 |PLModule|)))", Native.find_java_method("edu.isi.powerloom.server.gui.PLModule", "PLModuleL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLModule"), Native.find_java_class("edu.isi.powerloom.server.gui.PLModule")}), null);
          Stella.defineFunctionObject(" |PLInstance<|", "(DEFUN (|PLInstance<| BOOLEAN) ((INST1 |PLInstance|) (INST2 |PLInstance|)))", Native.find_java_method("edu.isi.powerloom.server.gui.PLInstance", "PLInstanceL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLInstance"), Native.find_java_class("edu.isi.powerloom.server.gui.PLInstance")}), null);
          Stella.defineFunctionObject(" |PLConcept<|", "(DEFUN (|PLConcept<| BOOLEAN) ((INST1 |PLConcept|) (INST2 |PLConcept|)))", Native.find_java_method("edu.isi.powerloom.server.gui.PLConcept", "PLConceptL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLConcept"), Native.find_java_class("edu.isi.powerloom.server.gui.PLConcept")}), null);
          Stella.defineFunctionObject(" |PLRelation<|", "(DEFUN (|PLRelation<| BOOLEAN) ((INST1 |PLRelation|) (INST2 |PLRelation|)))", Native.find_java_method("edu.isi.powerloom.server.gui.PLRelation", "PLRelationL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLRelation"), Native.find_java_class("edu.isi.powerloom.server.gui.PLRelation")}), null);
          Stella.defineFunctionObject("STARTUP-XML-OBJECTS", "(DEFUN STARTUP-XML-OBJECTS () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.powerloom.server.gui._StartupXmlObjects", "startupXmlObjects", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(GuiServer.SYM_GUI_SERVER_STARTUP_XML_OBJECTS);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, GuiServer.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupXmlObjects"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("GUI-SERVER")))));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
