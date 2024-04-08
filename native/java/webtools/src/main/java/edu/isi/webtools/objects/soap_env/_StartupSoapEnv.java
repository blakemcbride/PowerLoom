//  -*- Mode: Java -*-
//
// _StartupSoapEnv.java

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

package edu.isi.webtools.objects.soap_env;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.webtools.objects.xml_objects.*;
import edu.isi.stella.*;

public class _StartupSoapEnv {
  public static void STARTUP_SOAP_ENV() {
    { Object OLD_$MODULE$_000 = Stella.$MODULE$.get();
      Object OLD_$CONTEXT$_000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/STELLA/XML-OBJECTS/SOAP-ENV", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          SoapEnv.SGT_SOAP_ENV_Envelope = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("Envelope", null, 1)));
          SoapEnv.SYM_SOAP_ENV_encodingStyle = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("encodingStyle", null, 0)));
          SoapEnv.SYM_XML_OBJECTS_body = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("body", Stella.getStellaModule("/STELLA/XML-OBJECTS", true), 0)));
          SoapEnv.SGT_SOAP_ENV_Body = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("Body", null, 1)));
          SoapEnv.SYM_SOAP_ENV_contents = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("contents", null, 0)));
          SoapEnv.SGT_SOAP_ENV_Fault = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("Fault", null, 1)));
          SoapEnv.SYM_SOAP_ENV_faultcode = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("faultcode", null, 0)));
          SoapEnv.SYM_SOAP_ENV_faultstring = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("faultstring", null, 0)));
          SoapEnv.SYM_SOAP_ENV_faultactor = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("faultactor", null, 0)));
          SoapEnv.SYM_SOAP_ENV_detail = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("detail", null, 0)));
          SoapEnv.SGT_SOAP_ENV_FaultCode = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("FaultCode", null, 1)));
          SoapEnv.SGT_SOAP_ENV_FaultString = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("FaultString", null, 1)));
          SoapEnv.SGT_SOAP_ENV_FaultActor = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("FaultActor", null, 1)));
          SoapEnv.SGT_SOAP_ENV_Detail = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("Detail", null, 1)));
          SoapEnv.SYM_SOAP_ENV_STARTUP_SOAP_ENV = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-SOAP-ENV", null, 0)));
        }
        if (Stella.currentStartupTimePhaseP(5)) {
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("Envelope", "(DEFCLASS Envelope (XMLObject) :PUBLIC-SLOTS ((encodingStyle :TYPE STRING :INITIALLY \"http://schemas.xmlsoap.org/soap/encoding/\") (body :TYPE Body)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.objects.soap_env.Envelope", "new_Envelope", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.objects.soap_env.Envelope", "access_Envelope_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.soap_env.Envelope"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("Body", "(DEFCLASS Body (XMLObject) :PUBLIC-SLOTS ((contents :TYPE XMLObject)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.objects.soap_env.Body", "new_Body", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.objects.soap_env.Body", "access_Body_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.soap_env.Body"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("Fault", "(DEFCLASS Fault (XMLObject) :PUBLIC-SLOTS ((faultcode :TYPE FaultCode) (faultstring :TYPE FaultString) (faultactor :TYPE FaultActor) (detail :TYPE Detail)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.objects.soap_env.Fault", "new_Fault", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.objects.soap_env.Fault", "access_Fault_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.soap_env.Fault"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("FaultCode", "(DEFCLASS FaultCode (XMLObject))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.objects.soap_env.FaultCode", "new_FaultCode", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("FaultString", "(DEFCLASS FaultString (XMLObject))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.objects.soap_env.FaultString", "new_FaultString", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("FaultActor", "(DEFCLASS FaultActor (XMLObject))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.objects.soap_env.FaultActor", "new_FaultActor", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("Detail", "(DEFCLASS Detail (XMLObject) :PUBLIC-SLOTS ((contents :TYPE XMLObject)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.objects.soap_env.Detail", "new_Detail", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.objects.soap_env.Detail", "access_Detail_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.soap_env.Detail"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("GET-BODY", "(DEFUN (GET-BODY Body) ((envelope Envelope)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (body envelope)))", Native.find_java_method("edu.isi.webtools.objects.soap_env.Envelope", "GET_BODY", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.soap_env.Envelope")}), null);
          Stella.defineFunctionObject("GET-BODY-CONTENTS", "(DEFUN (GET-BODY-CONTENTS XMLObject) ((envelope Envelope)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (contents (GET-BODY envelope))))", Native.find_java_method("edu.isi.webtools.objects.soap_env.Envelope", "GET_BODY_CONTENTS", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.soap_env.Envelope")}), null);
          Stella.defineFunctionObject("FAULT-MESSAGE?", "(DEFUN (FAULT-MESSAGE? BOOLEAN) ((envelope Envelope)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (ISA? (GET-BODY-CONTENTS envelope) @Fault)))", Native.find_java_method("edu.isi.webtools.objects.soap_env.Envelope", "FAULT_MESSAGEP", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.soap_env.Envelope")}), null);
          Stella.defineFunctionObject("GET-FAULT", "(DEFUN (GET-FAULT Fault) ((envelope Envelope)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (SAFETY 2 (FAULT-MESSAGE? envelope) \"Envelope doesn't contain a Fault message\") (RETURN (GET-BODY-CONTENTS envelope)))", Native.find_java_method("edu.isi.webtools.objects.soap_env.Envelope", "GET_FAULT", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.soap_env.Envelope")}), null);
          Stella.defineFunctionObject("STARTUP-SOAP-ENV", "(DEFUN STARTUP-SOAP-ENV () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.objects.soap_env._StartupSoapEnv", "STARTUP_SOAP_ENV", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(SoapEnv.SYM_SOAP_ENV_STARTUP_SOAP_ENV);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, edu.isi.webtools.http.Http.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupSoapEnv"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("SOAP-ENV")))));
          XmlObjects.$NAMESPACE_PREFIX_URI_TABLE$.insertAt(StringWrapper.wrapString("SOAP-ENV"), StringWrapper.wrapString("http://schemas.xmlsoap.org/soap/envelope/"));
          XmlObjects.$NAMESPACE_URI_PREFIX_TABLE$.insertAt(StringWrapper.wrapString("http://schemas.xmlsoap.org/soap/envelope/"), StringWrapper.wrapString("SOAP-ENV"));
        }

      } finally {
        Stella.$CONTEXT$.set(OLD_$CONTEXT$_000);
        Stella.$MODULE$.set(OLD_$MODULE$_000);
      }
    }
  }

}
