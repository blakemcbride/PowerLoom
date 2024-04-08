//  -*- Mode: Java -*-
//
// _StartupSoap.java

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

package edu.isi.webtools.soap;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.stella.*;
import edu.isi.webtools.objects.soap_env.*;
import edu.isi.webtools.http.*;

public class _StartupSoap {
  public static void startupSoap() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/SOAP", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          Soap.SYM_SOAP_STARTUP_SOAP = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-SOAP", null, 0)));
        }
        if (Stella.currentStartupTimePhaseP(5)) {
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("SOAP-FAULT-EXCEPTION", "(DEFCLASS SOAP-FAULT-EXCEPTION (STELLA-EXCEPTION) :PUBLIC-SLOTS ((FAULT :TYPE |Fault|)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.soap.SoapFaultException", "newSoapFaultException", new java.lang.Class [] {Native.find_java_class("java.lang.String")});
          }
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("PROCESS-SOAP-RPC-REQUEST", "(DEFUN PROCESS-SOAP-RPC-REQUEST ((SOAPSTRING STRING) (SUPRESSNAMESPACES? BOOLEAN) (STREAM OUTPUT-STREAM)) :DOCUMENTATION \"'envelope' is a string-representation of SOAP envelope containing an\nRPC request.  This functions writes a SOAP envelope containing a service response to `stream'.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.soap.Soap", "processSoapRpcRequest", new java.lang.Class [] {Native.find_java_class("java.lang.String"), java.lang.Boolean.TYPE, Native.find_java_class("edu.isi.stella.OutputStream")}), null);
          Stella.defineFunctionObject("GET-RPC-METHOD", "(DEFUN (GET-RPC-METHOD SYMBOL) ((ENVELOPE |Envelope|)))", Native.find_java_method("edu.isi.webtools.soap.Soap", "getRpcMethod", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.soap_env.Envelope")}), null);
          Stella.defineFunctionObject("GET-RPC-ARGUMENTS", "(DEFUN (GET-RPC-ARGUMENTS (CONS OF |XMLObject|)) ((ENVELOPE |Envelope|)))", Native.find_java_method("edu.isi.webtools.soap.Soap", "getRpcArguments", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.soap_env.Envelope")}), null);
          Stella.defineFunctionObject("DISPATCH-RPC-CALL", "(DEFUN (DISPATCH-RPC-CALL |Envelope|) ((ENVELOPE |Envelope|)))", Native.find_java_method("edu.isi.webtools.soap.Soap", "dispatchRpcCall", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.soap_env.Envelope")}), null);
          Stella.defineFunctionObject("DISPATCH-CALL-WITH-METHOD-AND-ARGS", "(DEFUN (DISPATCH-CALL-WITH-METHOD-AND-ARGS |Envelope|) ((METHODNAME SYMBOL) (ARGUMENTS (CONS OF |XMLObject|))))", Native.find_java_method("edu.isi.webtools.soap.Soap", "dispatchCallWithMethodAndArgs", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Cons")}), null);
          Stella.defineFunctionObject("CREATE-SOAP-ENVELOPE", "(DEFUN (CREATE-SOAP-ENVELOPE |Envelope|) ((CONTENTS |XMLObject|)))", Native.find_java_method("edu.isi.webtools.soap.Soap", "createSoapEnvelope", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
          Stella.defineFunctionObject("CREATE-SOAP-FAULT", "(DEFUN (CREATE-SOAP-FAULT |Fault|) ((FCODE STRING) (FSTRING STRING) (FACTOR STRING) (FDETAIL |XMLObject|)) :DOCUMENTATION \"Create a SOAP Fault object.  `fcode' and `fstring' are required.\n`factor' and `fdetail' are optional fields.  Fault code should be one of\n\\\"SOAP-ENV:VersionMismatch\\\", \\\"SOAP-ENV:MustUnderstand\\\" \\\"SOAP-ENV:Client\\\" or\n\\\"SOAP-ENV:Server\\\".  These may change to keywords in the future.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.soap.Soap", "createSoapFault", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
          Stella.defineFunctionObject("SOAP-RPC-REQUEST-HANDLER", "(DEFUN SOAP-RPC-REQUEST-HANDLER ((XCHG HTTP-EXCHANGE)) :DOCUMENTATION \"Handle a request encoded by a SOAP message envelope in the body of an HTTP POST\ncommand, unpack the envelope, dispatch the request, and return the result as SOAP envelope.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.soap.Soap", "soapRpcRequestHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")}), null);
          Stella.defineFunctionObject("CALL-WEBSERVICE", "(DEFUN (CALL-WEBSERVICE |XMLObject|) ((CALLOBJECT |XMLObject|) (URL STRING)) :DOCUMENTATION \"Package `callObject' into a SOAP envelope, send it to the webservice at `url'.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.soap.Soap", "callWebservice", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("MAKE-SOAP-RPC-REQUEST-HEADERS", "(DEFUN (MAKE-SOAP-RPC-REQUEST-HEADERS HTTP-HEADERS) ())", Native.find_java_method("edu.isi.webtools.soap.Soap", "makeSoapRpcRequestHeaders", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("STARTUP-SOAP", "(DEFUN STARTUP-SOAP () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.soap._StartupSoap", "startupSoap", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(Soap.SYM_SOAP_STARTUP_SOAP);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, Http.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupSoap"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("SOAP")))));
          Http.publishHandler("/ploom/soap-rpc/generic-soap-service", Native.find_java_method("edu.isi.webtools.soap.Soap", "soapRpcRequestHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")}), Cons.cons(Http.KWD_CONTENT_TYPE, Cons.cons(StringWrapper.wrapString(Http.getHttpMimeType(Http.KWD_XML, null)), Cons.cons(Http.KWD_DOCUMENTATION, Cons.cons(StringWrapper.wrapString("Generic SOAP RPC handler."), Stella.NIL)))));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
