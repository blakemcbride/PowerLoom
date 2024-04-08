//  -*- Mode: Java -*-
//
// _StartupHttpClient.java

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

package edu.isi.webtools.http;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.stella.*;

public class _StartupHttpClient {
  public static void startupHttpClient() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/HTTP", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          Http.KWD_MAC = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("MAC", null, 2)));
          Http.SYM_HTTP_HTTP_HEADERS = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("HTTP-HEADERS", null, 0)));
          Http.SGT_STELLA_FILE_INPUT_STREAM = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("FILE-INPUT-STREAM", Stella.getStellaModule("/STELLA", true), 1)));
          Http.SGT_STELLA_INPUT_STREAM = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("INPUT-STREAM", Stella.getStellaModule("/STELLA", true), 1)));
          Http.KWD_POST = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("POST", null, 2)));
          Http.KWD_GET = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("GET", null, 2)));
          Http.SYM_STELLA_LET = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("LET", Stella.getStellaModule("/STELLA", true), 0)));
          Http.SYM_STELLA_INPUT_STREAM = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("INPUT-STREAM", Stella.getStellaModule("/STELLA", true), 0)));
          Http.SYM_STELLA_NULL = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("NULL", Stella.getStellaModule("/STELLA", true), 0)));
          Http.SYM_STELLA_UNWIND_PROTECT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("UNWIND-PROTECT", Stella.getStellaModule("/STELLA", true), 0)));
          Http.SYM_STELLA_PROGN = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PROGN", Stella.getStellaModule("/STELLA", true), 0)));
          Http.SYM_STELLA_SETQ = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("SETQ", Stella.getStellaModule("/STELLA", true), 0)));
          Http.SYM_HTTP_OPEN_URL_STREAM = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("OPEN-URL-STREAM", null, 0)));
          Http.SYM_STELLA_WHEN = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("WHEN", Stella.getStellaModule("/STELLA", true), 0)));
          Http.SYM_STELLA_DEFINEDp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("DEFINED?", Stella.getStellaModule("/STELLA", true), 0)));
          Http.SYM_STELLA_CLOSE_STREAM = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("CLOSE-STREAM", Stella.getStellaModule("/STELLA", true), 0)));
          Http.KWD_METHOD = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD", null, 2)));
          Http.KWD_HEADERS = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("HEADERS", null, 2)));
          Http.KWD_CONTENT = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("CONTENT", null, 2)));
          Http.SGT_HTTP_HTTP_HEADERS = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("HTTP-HEADERS", null, 1)));
          Http.SYM_HTTP_STARTUP_HTTP_CLIENT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-HTTP-CLIENT", null, 0)));
          Http.SYM_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", Stella.getStellaModule("/STELLA", true), 0)));
        }
        if (Stella.currentStartupTimePhaseP(5)) {
          Stella.defineStellaTypeFromStringifiedSource("(DEFTYPE HTTP-HEADERS (KEY-VALUE-LIST OF STRING-WRAPPER STRING-WRAPPER))");
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("HTTP-EXCEPTION", "(DEFCLASS HTTP-EXCEPTION (READ-EXCEPTION) :PUBLIC-SLOTS ((ERROR-CODE :TYPE INTEGER)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.http.HttpException", "newHttpException", new java.lang.Class [] {Native.find_java_class("java.lang.String")});
          }
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("DECOMPOSE-INTERNET-URL", "(DEFUN (DECOMPOSE-INTERNET-URL STRING STRING STRING STRING STRING STRING STRING) ((URL STRING)) :DOCUMENTATION \"Takes an internet style URL and returns the components of\nthat URL as specified below.  Missing elements return the empty string \\\"\\\".\n  PROTOCOL USERNAME:PASSWORD DOMAIN PORT PATH QUERY FRAGMENT\n\n  o Protocol.  The access protocol.\n\n       Those schemes which refer to internet protocols mostly have a\n       common syntax for the rest of the object name. This starts with a\n       double slash '//' to indicate its presence, and continues until\n       the following slash '/':\n\n  o An optional user name, if required (as it is with a few FTP servers).\n    The password, if present, follows the user name, separated from it by a colon;\n    the user name and optional password are followed by a commercial at sign '@'. \n  o The internet domain name of the host\n  o The port number, if it is not the default number for the protocol,\n    is given in decimal notation after a colon.\n  o Path The path is a hierarchical representation of a particular path. It may \n    define details of how the client should communicate with the server, including\n    information to be passed transparently to the server without any processing by\n    the client.\n    The path is interpreted in a manner dependent on the scheme being used.\n    Generally, the reserved slash '/' character (ASCII 2F hex) denotes a level in a\n    hierarchical structure, the higher level part to the left of the slash.\n  o Query is the part of the hierarchical information following a '?' character.\n  o Fragment is the part of the hierarchical information following a '#' character.\n\nReferences:  http://www.gbiv.com/protocols/uri/rfc/rfc3986.html\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "decomposeInternetUrl", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("[Ljava.lang.Object;")}), null);
          Stella.defineFunctionObject("COMPOSE-INTERNET-URL", "(DEFUN (COMPOSE-INTERNET-URL STRING) ((PROTOCOL STRING) (USERINFO STRING) (HOST STRING) (PORT INTEGER) (PATH STRING) (QUERY STRING) (FRAGMENT STRING)) :DOCUMENTATION \"The inverse to `decompose-internet-url'.  Builds a URL string from the supplied\ncomponents.  Undefined portions can be supplied as NULL or the empty string.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "composeInternetUrl", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), java.lang.Integer.TYPE, Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("URL-PATH-TO-FILENAME", "(DEFUN (URL-PATH-TO-FILENAME STRING) ((PATH STRING)) :DOCUMENTATION \"Transform a URL `path' into a valid native filename for the local OS.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "urlPathToFilename", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("HANDLE-HTTP-HEADER-FIRST-LINE", "(DEFUN (HANDLE-HTTP-HEADER-FIRST-LINE STRING INTEGER STRING) ((LINE STRING) (FIELDS HTTP-HEADERS)) :DOCUMENTATION \"Handles the first line of an http header.  \nReturns version, response code, response message.  The first\nline is inserted into `fields' fields with the empty string key \\\"\\\"\nThis is a low-level utility routine that can be used to build custom\nmessage parsing code.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "handleHttpHeaderFirstLine", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.KeyValueList"), Native.find_java_class("[Ljava.lang.Object;")}), null);
          Stella.defineFunctionObject("HANDLE-HTTP-HEADER-OTHER-LINE", "(DEFUN HANDLE-HTTP-HEADER-OTHER-LINE ((LINE STRING) (FIELDS HTTP-HEADERS)) :DOCUMENTATION \"Handles header lines other than the first one.\nEach such line is inserted into `fields' as keyword value pairs.\nThis is a low-level utility routine that can be used to build custom\nmessage parsing code.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "handleHttpHeaderOtherLine", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.KeyValueList")}), null);
          Stella.defineFunctionObject("READ-HTTP-HEADER-LINE", "(DEFUN (READ-HTTP-HEADER-LINE STRING) ((STREAM INPUT-STREAM)))", Native.find_java_method("edu.isi.webtools.http.Http", "readHttpHeaderLine", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.InputStream")}), null);
          Stella.defineFunctionObject("READ-HTTP-HEADER", "(DEFUN (READ-HTTP-HEADER INTEGER STRING STRING) ((STREAM INPUT-STREAM) (FIELDS HTTP-HEADERS)) :DOCUMENTATION \"Reads the HTTP header from `stream', parses the header fields\nand stores the results in `fields'.  The first line of the response will be\nstored in `fields' with the empty string \\\"\\\" as the key.  Other values will\nhave the header name as the key.  The first return value is the response code\nof the HTTP request.  A response of 200 indicates success.  Other common\nresponses are 404 (page not found).  The second return value is the message\nassociated with the code.  The third return value is the version information.\nIf the stream ends before a valid header is read, then `null' is returned for\nall values.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "readHttpHeader", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.InputStream"), Native.find_java_class("edu.isi.stella.KeyValueList"), Native.find_java_class("[Ljava.lang.Object;")}), null);
          Stella.defineFunctionObject("GET-CONTENT-AND-LENGTH", "(DEFUN (GET-CONTENT-AND-LENGTH OBJECT LONG-INTEGER) ((CONTENT OBJECT)))", Native.find_java_method("edu.isi.webtools.http.Http", "getContentAndLength", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("[Ljava.lang.Object;")}), null);
          Stella.defineFunctionObject("WRITE-HTTP-REQUEST", "(DEFUN WRITE-HTTP-REQUEST ((STREAM OUTPUT-STREAM) (METHOD KEYWORD) (HOST STRING) (URL-PATH STRING) (HEADERS HTTP-HEADERS) (CONTENT OBJECT)) :DOCUMENTATION \"Send `content' as an HTTP 1.0 request on `stream' using `method'.\nThe request is sent to `url-path' at `host'.  The `stream' must be a TCP-stream\nthat is connected to `host' at the appropriate port.  `content' can be a string or\nan input stream to read from.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "writeHttpRequest", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.OutputStream"), Native.find_java_class("edu.isi.stella.Keyword"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.KeyValueList"), Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineFunctionObject("HTTP-POST-DATA", "(DEFUN (HTTP-POST-DATA INPUT-STREAM) ((HOST STRING) (PORT INTEGER) (URL-PATH STRING) (HEADERS HTTP-HEADERS) (CONTENT OBJECT)) :DOCUMENTATION \"Posts `content' as data to `url-path' on `host' and `port'.\n`content' can be a string or an input stream to read from.  The port value for\nstandard http servers is 80.  Returns the body of the reply message as a stream,\nif successful.  Otherwise an HTTP-EXCEPTION is signaled.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "httpPostData", new java.lang.Class [] {Native.find_java_class("java.lang.String"), java.lang.Integer.TYPE, Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.KeyValueList"), Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineFunctionObject("HTTP-POST-DATA-TO-STRING", "(DEFUN (HTTP-POST-DATA-TO-STRING STRING) ((HOST STRING) (PORT INTEGER) (URL-PATH STRING) (HEADERS HTTP-HEADERS) (CONTENT OBJECT)) :DOCUMENTATION \"Just like `http-post-data' (which see) but returns the reply as a string.\nCAUTION: String conversion will not do the right thing for binary data in Java.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "httpPostDataToString", new java.lang.Class [] {Native.find_java_class("java.lang.String"), java.lang.Integer.TYPE, Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.KeyValueList"), Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineFunctionObject("HTTP-GET-DATA", "(DEFUN (HTTP-GET-DATA INPUT-STREAM) ((HOST STRING) (PORT INTEGER) (URL-PATH STRING) (RETURN-HEADERS HTTP-HEADERS)) :DOCUMENTATION \"Accesses the data described by `url-path' on `host' and `port'.\nThe port value for standard http servers is 80.  If successful, returns the body\nof the web message as a stream.  The headers from the reply message will be set\nin `return-headers' if not null'.  If an error occurs an HTTP-EXCEPTION is signaled.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "httpGetData", new java.lang.Class [] {Native.find_java_class("java.lang.String"), java.lang.Integer.TYPE, Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.KeyValueList")}), null);
          Stella.defineFunctionObject("HTTP-GET-DATA-TO-STRING", "(DEFUN (HTTP-GET-DATA-TO-STRING STRING) ((HOST STRING) (PORT INTEGER) (URL-PATH STRING) (RETURN-HEADERS HTTP-HEADERS)) :DOCUMENTATION \"Just like `http-get-data' (which see) but returns the result as a string.\nCAUTION: String conversion will not do the right thing for binary data in Java.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "httpGetDataToString", new java.lang.Class [] {Native.find_java_class("java.lang.String"), java.lang.Integer.TYPE, Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.KeyValueList")}), null);
          Stella.defineFunctionObject("OPEN-URL-STREAM", "(DEFUN (OPEN-URL-STREAM INPUT-STREAM) ((URL STRING)) :DOCUMENTATION \"Opens an input stream to `url'.\nCurrently only http: with no user name or password and file: urls on the local\nhost with absolute pathnames are supported.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "openUrlStream", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("WITH-INPUT-URL", "(DEFUN WITH-INPUT-URL ((BINDING CONS) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Sets up an unwind-protected form which opens a URL for\ninput and closes it afterwards.  The stream for reading is bound to the\nvariable provided in the macro form.\nSyntax is `(WITH-INPUT-URL (var url) body+)'.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "withInputUrl", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons"), Native.find_java_class("edu.isi.stella.Cons")}), null);
          Stella.defineFunctionObject("DOWNLOAD-URL", "(DEFUN DOWNLOAD-URL ((URL STRING) (FILE STRING)) :DOCUMENTATION \"Download the data at `url' and save it to `file'.\" :PUBLIC? TRUE :COMMAND? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "downloadUrl", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String")}), Native.find_java_method("edu.isi.webtools.http.Http", "downloadUrlEvaluatorWrapper", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}));
          Stella.defineFunctionObject("DOWNLOAD-URL-TO-STRING", "(DEFUN (DOWNLOAD-URL-TO-STRING STRING) ((URL STRING)) :DOCUMENTATION \"Download the data at `url' and return it as a string.\nCAUTION: String conversion will not do the right thing for binary data in Java.\" :PUBLIC? TRUE :COMMAND? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "downloadUrlToString", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), Native.find_java_method("edu.isi.webtools.http.Http", "downloadUrlToStringEvaluatorWrapper", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}));
          Stella.defineFunctionObject("DO-HTTP-REQUEST", "(DEFUN (DO-HTTP-REQUEST STRING) ((URI STRING) |&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Send an http request to `uri' and return a string representing the result.\" :PUBLIC? TRUE :COMMAND? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "doHttpRequest", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.Cons")}), Native.find_java_method("edu.isi.webtools.http.Http", "doHttpRequestEvaluatorWrapper", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}));
          Stella.defineFunctionObject("STARTUP-HTTP-CLIENT", "(DEFUN STARTUP-HTTP-CLIENT () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http._StartupHttpClient", "startupHttpClient", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(Http.SYM_HTTP_STARTUP_HTTP_CLIENT);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, Http.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupHttpClient"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("HTTP")))));
          Stella.defineGlobalVariableObject("(DEFCONSTANT HTTP-DEFAULT-PORT INTEGER 80)", null);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
