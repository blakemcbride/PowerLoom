//  -*- Mode: Java -*-
//
// _StartupGuiServer.java

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

public class _StartupGuiServer {
  public static void startupGuiServer() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/POWERLOOM-SERVER/GUI-SERVER", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          GuiServer.KWD_CONTENT_TYPE = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("CONTENT-TYPE", null, 2)));
          GuiServer.KWD_XML = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("XML", null, 2)));
          GuiServer.KWD_DOCUMENTATION = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("DOCUMENTATION", null, 2)));
          GuiServer.SYM_GUI_SERVER_STARTUP_GUI_SERVER = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-GUI-SERVER", null, 0)));
        }
        if (Stella.currentStartupTimePhaseP(4)) {
          GuiServer.$GUI_SERVER_MODULE$ = Stella.getStellaModule("GUI-SERVER", true);
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("SERVER-PROCESS-SOAP-REQUEST", "(DEFUN (SERVER-PROCESS-SOAP-REQUEST STRING) ((REQUESTBODY STRING)))", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "serverProcessSoapRequest", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("SERVER-MARSHAL-EXCEPTION", "(DEFUN (SERVER-MARSHAL-EXCEPTION STRING) ((TYPE STRING) (EXCEPTION NATIVE-EXCEPTION)))", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "serverMarshalException", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.Exception")}), null);
          Stella.defineFunctionObject("SERVER-GENERATE-SOAP-RESPONSE", "(DEFUN (SERVER-GENERATE-SOAP-RESPONSE STRING) ((RESPONSE STRING) (EXCEPTION STRING)))", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "serverGenerateSoapResponse", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("SERVER-PARSE-XML-DOCUMENT-STRING", "(DEFUN (SERVER-PARSE-XML-DOCUMENT-STRING (CONS OF CONS)) ((REQUEST STRING)))", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "serverParseXmlDocumentString", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("SERVER-EXTRACT-SOAP-BODY-CONTENTS", "(DEFUN (SERVER-EXTRACT-SOAP-BODY-CONTENTS OBJECT) ((PARSETREE (CONS OF CONS))))", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "serverExtractSoapBodyContents", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
          Stella.defineFunctionObject("SERVER-EXTRACT-METHOD-NAME", "(DEFUN (SERVER-EXTRACT-METHOD-NAME STRING) ((BODYCONTENTS CONS)))", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "serverExtractMethodName", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
          Stella.defineFunctionObject("SERVER-EXTRACT-ARGUMENTS", "(DEFUN (SERVER-EXTRACT-ARGUMENTS (CONS OF OBJECT)) ((BODYCONTENTS CONS)))", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "serverExtractArguments", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
          Stella.defineFunctionObject("SERVER-INVOKE-POWERLOOM-METHOD", "(DEFUN (SERVER-INVOKE-POWERLOOM-METHOD STRING) ((BODYCONTENTS CONS)))", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "serverInvokePowerloomMethod", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
          Stella.defineFunctionObject("GUI-REQUEST-HANDLER", "(DEFUN GUI-REQUEST-HANDLER ((XCHG /HTTP/HTTP-EXCHANGE)))", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "guiRequestHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")}), null);
          Stella.defineFunctionObject("STARTUP-GUI-SERVER", "(DEFUN STARTUP-GUI-SERVER () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.powerloom.server.gui._StartupGuiServer", "startupGuiServer", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(GuiServer.SYM_GUI_SERVER_STARTUP_GUI_SERVER);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, GuiServer.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupGuiServer"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("GUI-SERVER")))));
          Stella.defineGlobalVariableObject("(DEFGLOBAL *GUI-SERVER-MODULE* MODULE (GET-STELLA-MODULE \"GUI-SERVER\" TRUE))", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *SOAP-RESULT-PREFIX* STRING \"<?xml version='1.0' encoding='UTF-8'?><env:Envelope xmlns:env='http://schemas.xmlsoap.org/soap/envelope/' xmlns:xsd='http://www.w3.org/2001/XMLSchema' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns:enc='http://schemas.xmlsoap.org/soap/encoding/' xmlns:ns0='http://hello.org/wsdl' env:encodingStyle='http://schemas.xmlsoap.org/soap/encoding/'><env:Body><response><result><![CDATA[\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *SOAP-EXCEPTION-PREFIX* STRING \"<?xml version='1.0' encoding='UTF-8'?><env:Envelope xmlns:env='http://schemas.xmlsoap.org/soap/envelope/' xmlns:xsd='http://www.w3.org/2001/XMLSchema' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns:enc='http://schemas.xmlsoap.org/soap/encoding/' xmlns:ns0='http://hello.org/wsdl' env:encodingStyle='http://schemas.xmlsoap.org/soap/encoding/'><env:Body><response><exception><![CDATA[\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *SOAP-RESULT-SUFFIX* STRING \"]]></result></response></env:Body></env:Envelope>\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *SOAP-EXCEPTION-SUFFIX* STRING \"]]></exception></response></env:Body></env:Envelope>\")", null);
          edu.isi.webtools.http.Http.publishHandler("/ploom/soap-rpc/powerloom-gui-service", Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "guiRequestHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")}), Cons.cons(GuiServer.KWD_CONTENT_TYPE, Cons.cons(StringWrapper.wrapString(edu.isi.webtools.http.Http.getHttpMimeType(GuiServer.KWD_XML, null)), Cons.cons(GuiServer.KWD_DOCUMENTATION, Cons.cons(StringWrapper.wrapString("SOAP service for PowerLoom GUI."), Stella.NIL)))));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
