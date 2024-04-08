//  -*- Mode: Java -*-
//
// _StartupFetchDemo.java

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

package edu.isi.webtools.examples.fetch;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.webtools.objects.xml_objects.*;
import edu.isi.stella.*;

public class _StartupFetchDemo {
  public static void STARTUP_FETCH_DEMO() {
    { Object OLD_$MODULE$_000 = Stella.$MODULE$.get();
      Object OLD_$CONTEXT$_000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/STELLA/XML-OBJECTS/FETCH", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          Fetch.SGT_FETCH_runAgentAndWaitForResponse = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("runAgentAndWaitForResponse", null, 1)));
          Fetch.SYM_FETCH_arg0 = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("arg0", null, 0)));
          Fetch.SYM_FETCH_arg1 = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("arg1", null, 0)));
          Fetch.SYM_FETCH_arg2 = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("arg2", null, 0)));
          Fetch.SGT_FETCH_runAgentAndWaitForResponseResponse = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("runAgentAndWaitForResponseResponse", null, 1)));
          Fetch.SYM_FETCH_return = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("return", null, 0)));
          Fetch.SGT_FETCH_runAgentAndWaitForResponseReturn = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("runAgentAndWaitForResponseReturn", null, 1)));
          Fetch.SYM_FETCH_STARTUP_FETCH_DEMO = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-FETCH-DEMO", null, 0)));
        }
        if (Stella.currentStartupTimePhaseP(5)) {
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("runAgentAndWaitForResponse", "(DEFCLASS runAgentAndWaitForResponse (XMLObject) :PUBLIC-SLOTS ((arg0 :TYPE /STELLA/XML-OBJECTS/FETCH-CONTENT/arg0) (arg1 :TYPE /STELLA/XML-OBJECTS/FETCH-CONTENT/arg1) (arg2 :TYPE /STELLA/XML-OBJECTS/FETCH-CONTENT/arg2)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.fetch.runAgentAndWaitForResponse", "new_runAgentAndWaitForResponse", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.fetch.runAgentAndWaitForResponse", "access_runAgentAndWaitForResponse_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.fetch.runAgentAndWaitForResponse"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("runAgentAndWaitForResponseResponse", "(DEFCLASS runAgentAndWaitForResponseResponse (XMLObject) :PUBLIC-SLOTS ((return :TYPE runAgentAndWaitForResponseReturn)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.fetch.runAgentAndWaitForResponseResponse", "new_runAgentAndWaitForResponseResponse", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.fetch.runAgentAndWaitForResponseResponse", "access_runAgentAndWaitForResponseResponse_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.fetch.runAgentAndWaitForResponseResponse"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("runAgentAndWaitForResponseReturn", "(DEFCLASS runAgentAndWaitForResponseReturn (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.fetch.runAgentAndWaitForResponseReturn", "new_runAgentAndWaitForResponseReturn", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.fetch.runAgentAndWaitForResponseReturn", "access_runAgentAndWaitForResponseReturn_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.fetch.runAgentAndWaitForResponseReturn"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("GET-FETCH-RESPONSE1", "(DEFUN GET-FETCH-RESPONSE1 ())", Native.find_java_method("edu.isi.webtools.examples.fetch.Fetch", "GET_FETCH_RESPONSE1", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("GET-FETCH-RESPONSE2", "(DEFUN GET-FETCH-RESPONSE2 ())", Native.find_java_method("edu.isi.webtools.examples.fetch.Fetch", "GET_FETCH_RESPONSE2", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("GET-FETCH-RESPONSE3", "(DEFUN GET-FETCH-RESPONSE3 ())", Native.find_java_method("edu.isi.webtools.examples.fetch.Fetch", "GET_FETCH_RESPONSE3", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("MAKE-FETCH-REQUEST1", "(DEFUN (MAKE-FETCH-REQUEST1 STRING) ())", Native.find_java_method("edu.isi.webtools.examples.fetch.Fetch", "MAKE_FETCH_REQUEST1", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("MAKE-FETCH-REQUEST-OBJECT1", "(DEFUN (MAKE-FETCH-REQUEST-OBJECT1 XMLObject) ())", Native.find_java_method("edu.isi.webtools.examples.fetch.Fetch", "MAKE_FETCH_REQUEST_OBJECT1", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("STARTUP-FETCH-DEMO", "(DEFUN STARTUP-FETCH-DEMO () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.examples.fetch._StartupFetchDemo", "STARTUP_FETCH_DEMO", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(Fetch.SYM_FETCH_STARTUP_FETCH_DEMO);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, edu.isi.webtools.examples.sample.Sample.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupFetchDemo"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("FETCH")))));
          XmlObjects.$NAMESPACE_PREFIX_URI_TABLE$.insertAt(StringWrapper.wrapString("FETCH"), StringWrapper.wrapString("http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService/"));
          XmlObjects.$NAMESPACE_URI_PREFIX_TABLE$.insertAt(StringWrapper.wrapString("http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService/"), StringWrapper.wrapString("FETCH"));
          Stella.defineGlobalVariableObject("(DEFGLOBAL *FETCH-REQUEST1* STRING \"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?>\n<soapenv:Envelope xmlns:soapenv=\\\"http://schemas.xmlsoap.org/soap/envelope/\\\" xmlns:xsd=\\\"http://www.w3.org/2001/XMLSchema\\\" xmlns:xsi=\\\"http://www.w3.org/2001/XMLSchema-instance\\\">\n <soapenv:Body>\n  <ns1:runAgentAndWaitForResponse soapenv:encodingStyle=\\\"http://schemas.xmlsoap.org/soap/encoding/\\\" xmlns:ns1=\\\"http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService/\\\">\n   <arg0 xsi:type=\\\"xsd:string\\\">eeld/gettygeonames/plans/production</arg0>     \n   <arg1 href=\\\"#id0\\\"/>\n   <arg2 href=\\\"#id1\\\"/>\n  </ns1:runAgentAndWaitForResponse>\n  <multiRef id=\\\"id0\\\" soapenc:root=\\\"0\\\" soapenv:encodingStyle=\\\"http://schemas.xmlsoap.org/soap/encoding/\\\" xsi:type=\\\"ns2:Map\\\" xmlns:soapenc=\\\"http://schemas.xmlsoap.org/soap/encoding/\\\" xmlns:ns2=\\\"http://xml.apache.org/xml-soap\\\">\n   <item>\n    <key xsi:type=\\\"xsd:string\\\">keywords</key>		\n    <value xsi:type=\\\"xsd:string\\\">Marina Del Rey</value>\n   </item>\n  </multiRef>\n  <multiRef id=\\\"id1\\\" soapenc:root=\\\"0\\\" soapenv:encodingStyle=\\\"http://schemas.xmlsoap.org/soap/encoding/\\\" xsi:type=\\\"ns3:Map\\\" xmlns:ns3=\\\"http://xml.apache.org/xml-soap\\\" xmlns:soapenc=\\\"http://schemas.xmlsoap.org/soap/encoding/\\\"/>\n </soapenv:Body>\n</soapenv:Envelope>\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *FETCH-REQUEST2* STRING \"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?>\n<soapenv:Envelope xmlns:soapenv=\\\"http://schemas.xmlsoap.org/soap/envelope/\\\" xmlns:xsd=\\\"http://www.w3.org/2001/XMLSchema\\\" xmlns:xsi=\\\"http://www.w3.org/2001/XMLSchema-instance\\\">\n <soapenv:Body>\n  <ns1:runAgentAndWaitForResponse soapenv:encodingStyle=\\\"http://schemas.xmlsoap.org/soap/encoding/\\\" xmlns:ns1=\\\"http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService/\\\">\n   <arg0 xsi:type=\\\"xsd:string\\\">eeld/gettygeonames/plans/production</arg0>     \n   <arg1>\n     <item>\n       <key xsi:type=\\\"xsd:string\\\">keywords</key>		\n       <value xsi:type=\\\"xsd:string\\\">Marina Del Rey</value>\n     </item>\n   </arg1>\n   <arg2/>\n  </ns1:runAgentAndWaitForResponse>\n </soapenv:Body>\n</soapenv:Envelope>\")", null);
        }

      } finally {
        Stella.$CONTEXT$.set(OLD_$CONTEXT$_000);
        Stella.$MODULE$.set(OLD_$MODULE$_000);
      }
    }
  }

}
