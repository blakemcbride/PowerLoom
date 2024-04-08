//  -*- Mode: Java -*-
//
// _StartupSoapServer.java

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

package edu.isi.powerloom.server.plsoap;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.stella.*;
import edu.isi.powerloom.logic.*;
import edu.isi.webtools.objects.xml_objects.*;
import edu.isi.webtools.soap.*;
import edu.isi.powerloom.server.*;

public class _StartupSoapServer {
  static void helpStartupSoapServer1() {
    {
      Plsoap.SGT_PLSOAP_module = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("module", null, 1)));
      Plsoap.SGT_PLSOAP_nresults = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("nresults", null, 1)));
      Plsoap.SYM_XSI_type = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("type", Stella.getStellaModule("/STELLA/XML-OBJECTS/XSI", true), 0)));
      Plsoap.SGT_PLSOAP_pattern = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("pattern", null, 1)));
      Plsoap.SGT_PLSOAP_options = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("options", null, 1)));
      Plsoap.SGT_PLSOAP_SOAP_COMMAND = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("SOAP-COMMAND", null, 1)));
      Plsoap.SYM_PLSOAP_TARGET_MODULE = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("TARGET-MODULE", null, 0)));
      Plsoap.SGT_PLSOAP_command = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("command", null, 1)));
      Plsoap.SGT_PLSOAP_assertion = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("assertion", null, 1)));
      Plsoap.SGT_PLSOAP_retraction = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("retraction", null, 1)));
      Plsoap.SGT_PLSOAP_ask = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("ask", null, 1)));
      Plsoap.SYM_STELLA_OPTIONS = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("OPTIONS", Stella.getStellaModule("/STELLA", true), 0)));
      Plsoap.SGT_PLSOAP_retrieval = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("retrieval", null, 1)));
      Plsoap.SYM_PLSOAP_NRESULTS = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("NRESULTS", null, 0)));
      Plsoap.SYM_PLSOAP_QUERY_PATTERN = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("QUERY-PATTERN", null, 0)));
      Plsoap.SGT_PLSOAP_query = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("query", null, 1)));
      Plsoap.SGT_PLSOAP_result = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("result", null, 1)));
      Plsoap.SGT_PLSOAP_answer = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("answer", null, 1)));
      Plsoap.SYM_LOGIC_QUERY = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("QUERY", Stella.getStellaModule("/LOGIC", true), 0)));
      Plsoap.SYM_STELLA_RESULT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("RESULT", Stella.getStellaModule("/STELLA", true), 0)));
      Plsoap.SGT_PLSOAP_item = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("item", null, 1)));
      Plsoap.SGT_PLSOAP_proposition = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("proposition", null, 1)));
      Plsoap.SGT_PLSOAP_tuple = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("tuple", null, 1)));
      Plsoap.SYM_STELLA_ITEM = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("ITEM", Stella.getStellaModule("/STELLA", true), 0)));
      Plsoap.SGT_PLSOAP_tuples = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("tuples", null, 1)));
      Plsoap.SYM_PLSOAP_TUPLE = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("TUPLE", null, 0)));
      Plsoap.SGT_PLSOAP_propositions = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("propositions", null, 1)));
      Plsoap.SYM_LOGIC_PROPOSITION = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PROPOSITION", Stella.getStellaModule("/LOGIC", true), 0)));
      Plsoap.SGT_PLSOAP_powerloomerror = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("powerloomerror", null, 1)));
      Plsoap.SGT_PLSOAP_stellaerror = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("stellaerror", null, 1)));
      Plsoap.SGT_PLSOAP_nativeerror = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("nativeerror", null, 1)));
      Plsoap.KWD_IGNORE_TYPE_VIOLATIONS = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("IGNORE-TYPE-VIOLATIONS", null, 2)));
      Plsoap.KWD_REALISTIC = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("REALISTIC", null, 2)));
      Plsoap.KWD_METHOD = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD", null, 2)));
      Plsoap.KWD_POST = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("POST", null, 2)));
      Plsoap.KWD_HEADERS = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("HEADERS", null, 2)));
      Plsoap.KWD_CONTENT = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("CONTENT", null, 2)));
      Plsoap.SYM_PLSOAP_STARTUP_SOAP_SERVER = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-SOAP-SERVER", null, 0)));
    }
  }

  public static void startupSoapServer() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/POWERLOOM-SERVER/PLSOAP", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          _StartupSoapServer.helpStartupSoapServer1();
        }
        if (Stella.currentStartupTimePhaseP(4)) {
          Plsoap.$POWERLOOM_SOAP_MODULE$ = Stella.getStellaModule("PLSOAP", true);
        }
        if (Stella.currentStartupTimePhaseP(5)) {
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("module", "(DEFCLASS |module| (|XMLObject|))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.module", "new_module", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("nresults", "(DEFCLASS |nresults| (|XMLObject|) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/|type| :TYPE STRING)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.nresults", "new_nresults", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.nresults", "access_nresults_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.plsoap.nresults"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("pattern", "(DEFCLASS |pattern| (|XMLObject|))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.pattern", "new_pattern", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("options", "(DEFCLASS |options| (|XMLObject|))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.options", "new_options", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("SOAP-COMMAND", "(DEFCLASS SOAP-COMMAND (|XMLObject|) :DOCUMENTATION \"Common parent in type hierarchy.  This will\nnot actually be realized in surface syntax.\" :PUBLIC-SLOTS ((TARGET-MODULE :TYPE |module|)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.SoapCommand", "newSoapCommand", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.SoapCommand", "accessSoapCommandSlotValue", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.plsoap.SoapCommand"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("command", "(DEFCLASS |command| (SOAP-COMMAND) :PUBLIC-SLOTS ((TARGET-MODULE :TYPE |module|)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.command", "new_command", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("assertion", "(DEFCLASS |assertion| (SOAP-COMMAND) :PUBLIC-SLOTS ((TARGET-MODULE :TYPE |module|)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.assertion", "new_assertion", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("retraction", "(DEFCLASS |retraction| (SOAP-COMMAND) :PUBLIC-SLOTS ((TARGET-MODULE :TYPE |module|)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.retraction", "new_retraction", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("ask", "(DEFCLASS |ask| (SOAP-COMMAND) :PUBLIC-SLOTS ((TARGET-MODULE :TYPE |module|) (OPTIONS :TYPE |options|)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.ask", "new_ask", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.ask", "access_ask_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.plsoap.ask"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("retrieval", "(DEFCLASS |retrieval| (SOAP-COMMAND) :PUBLIC-SLOTS ((TARGET-MODULE :TYPE |module|) (NRESULTS :TYPE |nresults|) (QUERY-PATTERN :TYPE |pattern|) (OPTIONS :TYPE |options|)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.retrieval", "new_retrieval", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.retrieval", "access_retrieval_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.plsoap.retrieval"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("query", "(DEFCLASS |query| (|XMLObject|))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.query", "new_query", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("result", "(DEFCLASS |result| (|XMLObject|))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.result", "new_result", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("answer", "(DEFCLASS |answer| (|XMLObject|) :PUBLIC-SLOTS ((QUERY :TYPE |query|) (RESULT :TYPE |result|)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.answer", "new_answer", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.answer", "access_answer_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.plsoap.answer"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("item", "(DEFCLASS |item| (|XMLObject|) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/|type| :TYPE STRING)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.item", "new_item", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.item", "access_item_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.plsoap.item"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("proposition", "(DEFCLASS |proposition| (|XMLObject|))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.proposition", "new_proposition", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("tuple", "(DEFCLASS |tuple| (|XMLObject|) :PUBLIC-SLOTS ((NRESULTS :TYPE |nresults|) (ITEM :TYPE (LIST OF |item|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.tuple", "new_tuple", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.tuple", "access_tuple_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.plsoap.tuple"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("tuples", "(DEFCLASS |tuples| (|XMLObject|) :PUBLIC-SLOTS ((NRESULTS :TYPE |nresults|) (QUERY :TYPE |query|) (QUERY-PATTERN :TYPE |pattern|) (TUPLE :TYPE (LIST OF |tuple|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.tuples", "new_tuples", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.tuples", "access_tuples_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.plsoap.tuples"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("propositions", "(DEFCLASS |propositions| (|XMLObject|) :PUBLIC-SLOTS ((NRESULTS :TYPE |nresults|) (PROPOSITION :TYPE (LIST OF |proposition|))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.propositions", "new_propositions", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.propositions", "access_propositions_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.plsoap.propositions"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("powerloomerror", "(DEFCLASS |powerloomerror| (|XMLObject|))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.powerloomerror", "new_powerloomerror", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("stellaerror", "(DEFCLASS |stellaerror| (|XMLObject|))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.stellaerror", "new_stellaerror", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("nativeerror", "(DEFCLASS |nativeerror| (|XMLObject|))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.powerloom.server.plsoap.nativeerror", "new_nativeerror", new java.lang.Class [] {});
          }
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("POWERLOOM-PROCESS-SOAP-REQUEST", "(DEFUN (POWERLOOM-PROCESS-SOAP-REQUEST STRING) ((REQUEST-BODY STRING)))", Native.find_java_method("edu.isi.powerloom.server.plsoap.Plsoap", "powerloomProcessSoapRequest", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("POWERLOOM-SOAP-REQUEST-HANDLER", "(DEFUN POWERLOOM-SOAP-REQUEST-HANDLER ((XCHG /HTTP/HTTP-EXCHANGE)) :DOCUMENTATION \"WRITE ME\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.powerloom.server.plsoap.Plsoap", "powerloomSoapRequestHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")}), null);
          Stella.defineFunctionObject("SAFE-GET-CONTENT", "(DEFUN (SAFE-GET-CONTENT STRING) ((OBJ |XMLObject|)))", Native.find_java_method("edu.isi.powerloom.server.plsoap.Plsoap", "safeGetContent", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
          Stella.defineFunctionObject("CHECK-READ-ONLY", "(DEFUN CHECK-READ-ONLY ((COMMAND-FORM SOAP-COMMAND)))", Native.find_java_method("edu.isi.powerloom.server.plsoap.SoapCommand", "checkReadOnly", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.plsoap.SoapCommand")}), null);
          Stella.defineFunctionObject("PROCESS-SOAP-ENCODED-COMMAND", "(DEFUN (PROCESS-SOAP-ENCODED-COMMAND |XMLObject|) ((COMMAND-FORM SOAP-COMMAND)))", Native.find_java_method("edu.isi.powerloom.server.plsoap.SoapCommand", "processSoapEncodedCommand", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.plsoap.SoapCommand")}), null);
          Stella.defineFunctionObject("SOAP-ENCODE-COMMAND-RESPONSE", "(DEFUN (SOAP-ENCODE-COMMAND-RESPONSE |XMLObject|) ((OBJ OBJECT)))", Native.find_java_method("edu.isi.powerloom.server.plsoap.Plsoap", "soapEncodeCommandResponse", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineFunctionObject("SOAP-ENCODE-ASSERT-RESPONSE", "(DEFUN (SOAP-ENCODE-ASSERT-RESPONSE |XMLObject|) ((ITER (/PLI/PL-ITERATOR OF PROPOSITION))))", Native.find_java_method("edu.isi.powerloom.server.plsoap.Plsoap", "soapEncodeAssertResponse", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.PlIterator")}), null);
          Stella.defineFunctionObject("SOAP-ENCODE-SIMPLE-ANSWER", "(DEFUN (SOAP-ENCODE-SIMPLE-ANSWER |XMLObject|) ((QUERY-STRING STRING) (TV TRUTH-VALUE)))", Native.find_java_method("edu.isi.powerloom.server.plsoap.Plsoap", "soapEncodeSimpleAnswer", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.powerloom.logic.TruthValue")}), null);
          Stella.defineFunctionObject("SOAP-ENCODE-ITEM", "(DEFUN (SOAP-ENCODE-ITEM |item|) ((OBJ OBJECT)))", Native.find_java_method("edu.isi.powerloom.server.plsoap.Plsoap", "soapEncodeItem", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineFunctionObject("SOAP-ENCODE-TUPLE", "(DEFUN (SOAP-ENCODE-TUPLE |tuple|) ((OBJ OBJECT)))", Native.find_java_method("edu.isi.powerloom.server.plsoap.Plsoap", "soapEncodeTuple", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineFunctionObject("SOAP-ENCODE-RETRIEVAL-ANSWER", "(DEFUN (SOAP-ENCODE-RETRIEVAL-ANSWER |XMLObject|) ((QUERY-STRING STRING) (ITER QUERY-ITERATOR)))", Native.find_java_method("edu.isi.powerloom.server.plsoap.Plsoap", "soapEncodeRetrievalAnswer", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.powerloom.logic.QueryIterator")}), null);
          Stella.defineFunctionObject("BUILD-AND-SEND-REQUEST", "(DEFUN BUILD-AND-SEND-REQUEST ((TARGET STRING) (TYPE STRING) (CONTENT STRING)))", Native.find_java_method("edu.isi.powerloom.server.plsoap.Plsoap", "buildAndSendRequest", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("CREATE-TEST-STRING", "(DEFUN (CREATE-TEST-STRING STRING) ((BODY-TAG-NAME STRING) (CONTENT STRING)))", Native.find_java_method("edu.isi.powerloom.server.plsoap.Plsoap", "createTestString", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("STARTUP-SOAP-SERVER", "(DEFUN STARTUP-SOAP-SERVER () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.powerloom.server.plsoap._StartupSoapServer", "startupSoapServer", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(Plsoap.SYM_PLSOAP_STARTUP_SOAP_SERVER);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, edu.isi.powerloom.server.gui.GuiServer.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupSoapServer"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("PLSOAP")))));
          Stella.defineGlobalVariableObject("(DEFGLOBAL *SOAP-READ-ONLY?* BOOLEAN FALSE)", null);
          XmlObjects.$NAMESPACE_PREFIX_URI_TABLE$.insertAt(StringWrapper.wrapString("PLSOAP"), StringWrapper.wrapString("http://www.isi.edu/powerloom/"));
          XmlObjects.$NAMESPACE_URI_PREFIX_TABLE$.insertAt(StringWrapper.wrapString("http://www.isi.edu/powerloom/"), StringWrapper.wrapString("PLSOAP"));
          Stella.defineGlobalVariableObject("(DEFGLOBAL *POWERLOOM-SOAP-MODULE* MODULE (GET-STELLA-MODULE \"PLSOAP\" TRUE))", null);
          edu.isi.webtools.http.Http.publishHandler("/ploom/soap-rpc/powerloom-soap-service", Native.find_java_method("edu.isi.powerloom.server.plsoap.Plsoap", "powerloomSoapRequestHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")}), Cons.cons(edu.isi.powerloom.server.gui.GuiServer.KWD_CONTENT_TYPE, Cons.cons(StringWrapper.wrapString(edu.isi.webtools.http.Http.getHttpMimeType(edu.isi.powerloom.server.gui.GuiServer.KWD_XML, null)), Cons.cons(edu.isi.powerloom.server.gui.GuiServer.KWD_DOCUMENTATION, Cons.cons(StringWrapper.wrapString("Service for PowerLoom SOAP server."), Stella.NIL)))));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
