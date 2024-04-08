//  -*- Mode: Java -*-
//
// _StartupHttpServerImpl.java

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
 +----------------------------- END LICENSE BLOCK ----------------------------+
*/

package edu.isi.webtools.http.tomcat;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.stella.*;
import edu.isi.webtools.http.*;

public class _StartupHttpServerImpl {
  public static void startupHttpServerImpl() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/HTTP/TOMCAT", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          Tomcat.SGT_TOMCAT_HTTP_SERVER_TOMCAT = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("HTTP-SERVER-TOMCAT", null, 1)));
          Tomcat.KWD_OK = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("OK", null, 2)));
          Tomcat.SGT_TOMCAT_HTTP_EXCHANGE_TOMCAT = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("HTTP-EXCHANGE-TOMCAT", null, 1)));
          Tomcat.SYM_TOMCAT_RESPONSE_CODE = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("RESPONSE-CODE", null, 0)));
          Tomcat.SYM_TOMCAT_HANDLER_OPTIONS = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("HANDLER-OPTIONS", null, 0)));
          Tomcat.KWD_BLOCK = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("BLOCK", null, 2)));
          Tomcat.SGT_STELLA_PROPERTY_LIST = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PROPERTY-LIST", Stella.getStellaModule("/STELLA", true), 1)));
          Tomcat.KWD_PATH = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("PATH", null, 2)));
          Tomcat.KWD_HANDLER_TYPE = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("HANDLER-TYPE", null, 2)));
          Tomcat.KWD_ERROR = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("ERROR", null, 2)));
          Tomcat.KWD_HANDLER = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("HANDLER", null, 2)));
          Tomcat.KWD_FILE = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("FILE", null, 2)));
          Tomcat.KWD_DIRECTORY = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("DIRECTORY", null, 2)));
          Tomcat.KWD_CONTENT_TYPE = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("CONTENT-TYPE", null, 2)));
          Tomcat.KWD_HTML = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("HTML", null, 2)));
          Tomcat.SYM_TOMCAT_STARTUP_HTTP_SERVER_IMPL = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-HTTP-SERVER-IMPL", null, 0)));
          Tomcat.SYM_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", Stella.getStellaModule("/STELLA", true), 0)));
        }
        if (Stella.currentStartupTimePhaseP(5)) {
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("HTTP-SERVER-TOMCAT", "(DEFCLASS HTTP-SERVER-TOMCAT (HTTP-SERVER) :PUBLIC? TRUE)");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "newHttpServerTomcat", new java.lang.Class [] {});
          }
          Stella.defineClassFromStringifiedSource("NATIVE-HTTP-SERVLET-REQUEST", "(DEFCLASS NATIVE-HTTP-SERVLET-REQUEST () :JAVA-NATIVE-TYPE \"javax.servlet.http.HttpServletRequest\")");
          Stella.defineClassFromStringifiedSource("NATIVE-HTTP-SERVLET-RESPONSE", "(DEFCLASS NATIVE-HTTP-SERVLET-RESPONSE () :JAVA-NATIVE-TYPE \"javax.servlet.http.HttpServletResponse\")");
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("HTTP-EXCHANGE-TOMCAT", "(DEFCLASS HTTP-EXCHANGE-TOMCAT (HTTP-EXCHANGE) :SLOTS ((NATIVE-REQUEST :TYPE NATIVE-HTTP-SERVLET-REQUEST) (NATIVE-RESPONSE :TYPE NATIVE-HTTP-SERVLET-RESPONSE) (RESPONSE-CODE :TYPE INTEGER :INITIALLY (GET-HTTP-RESPONSE-CODE :OK NULL)) (REPLY-STREAM :TYPE NATIVE-OUTPUT-STREAM) (HANDLER-OPTIONS :TYPE PROPERTY-LIST)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.http.tomcat.HttpExchangeTomcat", "newHttpExchangeTomcat", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.http.tomcat.HttpExchangeTomcat", "accessHttpExchangeTomcatSlotValue", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.tomcat.HttpExchangeTomcat"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineMethodObject("(DEFMETHOD (START-HTTP-SERVER-IMPL STRING) ((SERVER HTTP-SERVER-TOMCAT) (PORT INTEGER)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "startHttpServerImpl", new java.lang.Class [] {java.lang.Integer.TYPE})), null);
          Stella.defineMethodObject("(DEFMETHOD STOP-HTTP-SERVER-IMPL ((SERVER HTTP-SERVER-TOMCAT)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "stopHttpServerImpl", new java.lang.Class [] {})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-HEADER-VALUE-IMPL STRING) ((SERVER HTTP-SERVER-TOMCAT) (XCHG HTTP-EXCHANGE) (KEY KEYWORD)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "getHeaderValueImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange"), Native.find_java_class("edu.isi.stella.Keyword")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REPLY-HEADER-VALUE-IMPL STRING) ((SERVER HTTP-SERVER-TOMCAT) (XCHG HTTP-EXCHANGE) (KEY KEYWORD)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "getReplyHeaderValueImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange"), Native.find_java_class("edu.isi.stella.Keyword")})), null);
          Stella.defineMethodObject("(DEFMETHOD SET-REPLY-HEADER-VALUE-IMPL ((SERVER HTTP-SERVER-TOMCAT) (XCHG HTTP-EXCHANGE) (KEY KEYWORD) (VALUE STRING)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "setReplyHeaderValueImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange"), Native.find_java_class("edu.isi.stella.Keyword"), Native.find_java_class("java.lang.String")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REQUEST-URI-IMPL STRING) ((SERVER HTTP-SERVER-TOMCAT) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "getRequestUriImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REQUEST-URI-QUERY-IMPL STRING) ((SERVER HTTP-SERVER-TOMCAT) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "getRequestUriQueryImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REQUEST-URI-PATH-IMPL STRING) ((SERVER HTTP-SERVER-TOMCAT) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "getRequestUriPathImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REQUEST-METHOD-IMPL KEYWORD) ((SERVER HTTP-SERVER-TOMCAT) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "getRequestMethodImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REQUEST-PROTOCOL-IMPL STRING) ((SERVER HTTP-SERVER-TOMCAT) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "getRequestProtocolImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REQUEST-BODY-IMPL STRING) ((SERVER HTTP-SERVER-TOMCAT) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "getRequestBodyImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REQUEST-LOCAL-ADDRESS-IMPL STRING) ((SERVER HTTP-SERVER-TOMCAT) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "getRequestLocalAddressImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REQUEST-REMOTE-ADDRESS-IMPL STRING) ((SERVER HTTP-SERVER-TOMCAT) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "getRequestRemoteAddressImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REPLY-STREAM-IMPL NATIVE-OUTPUT-STREAM) ((SERVER HTTP-SERVER-TOMCAT) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "getReplyStreamImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD SET-RESPONSE-CODE-IMPL ((SERVER HTTP-SERVER-TOMCAT) (XCHG HTTP-EXCHANGE) (CODE KEYWORD)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "setResponseCodeImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange"), Native.find_java_class("edu.isi.stella.Keyword")})), null);
          Stella.defineMethodObject("(DEFMETHOD PUBLISH-FILE-IMPL ((SERVER HTTP-SERVER-TOMCAT) (PATH STRING) (FILE STRING) (OPTIONS PROPERTY-LIST)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "publishFileImpl", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.PropertyList")})), null);
          Stella.defineMethodObject("(DEFMETHOD PUBLISH-DIRECTORY-IMPL ((SERVER HTTP-SERVER-TOMCAT) (PATH STRING) (DIRECTORY STRING) (OPTIONS PROPERTY-LIST)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "publishDirectoryImpl", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.PropertyList")})), null);
          Stella.defineMethodObject("(DEFMETHOD PUBLISH-HANDLER-IMPL ((SERVER HTTP-SERVER-TOMCAT) (PATH STRING) (HANDLER FUNCTION-CODE) (OPTIONS PROPERTY-LIST)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "publishHandlerImpl", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.reflect.Method"), Native.find_java_class("edu.isi.stella.PropertyList")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-HANDLER-OPTIONS-IMPL PROPERTY-LIST) ((SERVER HTTP-SERVER-TOMCAT) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "getHandlerOptionsImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (SERVLET-HANDLE-REQUEST HTTP-EXCHANGE-TOMCAT) ((SERVER HTTP-SERVER-TOMCAT) (REQUEST NATIVE-HTTP-SERVLET-REQUEST) (RESPONSE NATIVE-HTTP-SERVLET-RESPONSE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.tomcat.HttpServerTomcat", "servletHandleRequest", new java.lang.Class [] {Native.find_java_class("javax.servlet.http.HttpServletRequest"), Native.find_java_class("javax.servlet.http.HttpServletResponse")})), null);
          Stella.defineFunctionObject("STARTUP-HTTP-SERVER-IMPL", "(DEFUN STARTUP-HTTP-SERVER-IMPL () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.tomcat._StartupHttpServerImpl", "startupHttpServerImpl", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(Tomcat.SYM_TOMCAT_STARTUP_HTTP_SERVER_IMPL);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, Tomcat.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupHttpServerImpl"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("HTTP/TOMCAT")))));
          if ((Http.$HTTP_SERVER_IMPLEMENTATION$ != null) &&
              (!Stella_Object.isaP(Http.$HTTP_SERVER_IMPLEMENTATION$, Tomcat.SGT_TOMCAT_HTTP_SERVER_TOMCAT))) {
            throw ((StellaException)(StellaException.newStellaException("Conflicting HTTP server implementation already loaded").fillInStackTrace()));
          }
          else {
            Http.$HTTP_SERVER_IMPLEMENTATION$ = HttpServerTomcat.newHttpServerTomcat();
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
