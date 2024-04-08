//  -*- Mode: Java -*-
//
// HttpExchange.java

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

/** Abstract class that represents exchange objects that encapsulate all necessary
 * state needed by a http handler function to understand the request and generate the
 * appropriate response.  This is mirrored somewhat after Sun's basic HTTP server
 * implementation in com.sun.net.httpserver.
 * @author Stella Java Translator
 */
public abstract class HttpExchange extends StandardObject {
  public static void testHttpApiHandler(HttpExchange xchg) {
    Http.$TEST_HTTP_API_HANDLER_LAST_XCHG$ = xchg;
    { String uri = HttpExchange.getRequestUri(xchg);
      String path = HttpExchange.getRequestUriPath(xchg);
      String query = HttpExchange.getRequestUriQuery(xchg);
      Cons args = Http.parseAndDecodeUrlArguments(query, '+');
      Keyword method = HttpExchange.getRequestMethod(xchg);
      String localhost = HttpExchange.getRequestLocalAddress(xchg);
      String remotehost = HttpExchange.getRequestRemoteAddress(xchg);
      String body = HttpExchange.getRequestBody(xchg);
      edu.isi.stella.javalib.NativeOutputStream stream = HttpExchange.getReplyStream(xchg);

      if (method == Http.KWD_GET) {
        if (args.memberP(StringWrapper.wrapString("plain"))) {
          HttpExchange.setReplyHeaderValue(xchg, Http.KWD_CONTENT_TYPE, Http.getHttpMimeType(Http.KWD_PLAIN_TEXT, null));
        }
        stream.println("<PRE>");
        stream.println("It worked, here are some parameters: ");
        stream.println("URI=`" + uri + "'");
        stream.println("Path=`" + path + "'");
        stream.println("Query=`" + query + "'");
        stream.println("Args=`" + args + "'");
        stream.println("Method=`" + method + "'");
        stream.println("Local host=`" + localhost + "'");
        stream.println("Remote host=`" + remotehost + "'");
        stream.println("Body=`" + body + "'");
        stream.println("</PRE>");
        HttpExchange.testHttpApiHandlerServeForm(xchg);
      }
      else if (method == Http.KWD_POST) {
        { KeyValueList values = Http.parseAndDecodeFormValues(body);

          stream.println("<PRE>");
          stream.println("It worked, here are some parameters: ");
          stream.println("URI=`" + uri + "'");
          stream.println("Path=`" + path + "'");
          stream.println("Query=`" + query + "'");
          stream.println("Args=`" + args + "'");
          stream.println("Method=`" + method + "'");
          stream.println("Local host=`" + localhost + "'");
          stream.println("Remote host=`" + remotehost + "'");
          stream.println("Body=`" + body + "'");
          {
            stream.println("Values=`" + values + "'");
            stream.println();
          }
;
          stream.println("</PRE>");
        }
      }
      else {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("`" + method + "' is not a valid case option");
          throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
    }
  }

  public static void testHttpApiHandlerServeForm(HttpExchange xchg) {
    { edu.isi.stella.javalib.NativeOutputStream stream = HttpExchange.getReplyStream(xchg);

      stream.print("\n<FORM NAME=\"frank\" METHOD=\"POST\">\n<b>Execute Query</b><BR>\n<b>Theory:</b> <INPUT TYPE=\"text\" NAME=\"CONTEXT\" VALUE=\"INSPECT\" SIZE=40 ><BR>\n<b>Package:</b><INPUT TYPE=\"text\" NAME=\"PACKAGE\" VALUE=\"EXPECT\" SIZE=40 ><P>\n<b>Output Variable(s):</b><INPUT TYPE=\"text\" NAME=\"VARIABLES\" SIZE=60 ><P>\n<b>Query:</b><TEXTAREA NAME=\"QUERY\" ROWS=10 COLS=72 ></TEXTAREA><P>\n<INPUT TYPE=submit  NAME=\"submit\" VALUE=\"submit\">\n</FORM>");
    }
  }

  /** Load the STELLA system with options identified by the URL parameters.
   * @param xchg
   */
  public static void loadSystemHandler(HttpExchange xchg) {
    { Cons arguments = Http.parseAndDecodeUrlArguments(HttpExchange.getRequestUriQuery(xchg), '+');
      StringWrapper systemname = ((StringWrapper)(arguments.value));
      Cons loadcommand = Cons.list$(Cons.cons(Http.SYM_STELLA_LOAD_SYSTEM, Cons.cons(systemname, Cons.cons(Stella.NIL, Stella.NIL))));
      edu.isi.stella.javalib.NativeOutputStream stream = HttpExchange.getReplyStream(xchg);

      { StringWrapper arg = null;
        Cons iter000 = arguments.rest;
        Cons collect000 = null;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          arg = ((StringWrapper)(iter000.value));
          if (collect000 == null) {
            {
              collect000 = Cons.cons(Stella.readSExpressionFromString(arg.wrapperValue), Stella.NIL);
              if (loadcommand == Stella.NIL) {
                loadcommand = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(loadcommand, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(Stella.readSExpressionFromString(arg.wrapperValue), Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      try {
        Stella_Object.evaluate(loadcommand);
        {
          stream.print("<BODY>");
          stream.print("Successfully evaluated: " + Native.stringify(loadcommand));
          stream.println("<BR><BR>");
          stream.println("<HR SIZE=2>");
          stream.print(Http.$HTTP_SERVER_COPYRIGHT_TRAILER$);
          stream.println("</BODY>");
        }
      } catch (java.lang.Exception e) {
        HttpExchange.generateErrorResponse(xchg, Http.KWD_BAD_REQUEST, Stella.exceptionMessage(e));
      }
    }
  }

  /** Simple default handler for unknown/unhandled URLs.
   * @param xchg
   */
  public static void unknownUrlHandler(HttpExchange xchg) {
    HttpExchange.generateErrorResponse(xchg, Http.KWD_NOT_FOUND, null);
  }

  /** Serve files located anywhere in the directory specified when the associated
   * handler was published (including subdirectories).  Simple default implementation for minimal
   * servers such as the Sun JRE HttpServer.
   * @param xchg
   */
  public static void directoryHandler(HttpExchange xchg) {
    { String uripath = HttpExchange.getRequestUriPath(xchg);
      PropertyList options = HttpExchange.getHandlerOptions(xchg);
      String path = ((StringWrapper)(options.lookup(Http.KWD_PATH))).wrapperValue;
      String directory = ((StringWrapper)(options.lookup(Http.KWD_DIRECTORY))).wrapperValue;
      String resolveduri = null;
      boolean isdirectoryP = false;
      String contenttype = Http.getHttpMimeType(Http.KWD_BINARY, null);
      edu.isi.stella.javalib.NativeOutputStream stream = HttpExchange.getReplyStream(xchg);

      uripath = Stella.stringTrim(Stella.unescapeUrlString(uripath));
      isdirectoryP = Stella.endsWithP(uripath, "/", Stella.NULL_INTEGER);
      if (!(Stella.startsWithP(uripath, path, Stella.NULL_INTEGER))) {
        HttpExchange.generateErrorResponse(xchg, Http.KWD_NOT_FOUND, null);
        return;
      }
      uripath = Native.string_subsequence(uripath, path.length(), Stella.NULL_INTEGER);
      if (Stella.startsWithP(uripath, "../", Stella.NULL_INTEGER) ||
          (Stella.startsWithP(uripath, "/..", Stella.NULL_INTEGER) ||
           (Native.stringSearch(uripath, "/../", Stella.NULL_INTEGER) != Stella.NULL_INTEGER))) {
        HttpExchange.generateErrorResponse(xchg, Http.KWD_FORBIDDEN, null);
        return;
      }
      resolveduri = Native.string_substitute(uripath, Stella.directorySeparator(), '/');
      resolveduri = directory + resolveduri;
      if (isdirectoryP) {
        if (Stella.probeFileP(resolveduri + "index.html")) {
          resolveduri = resolveduri + "index.html";
        }
        else if (Stella.probeFileP(resolveduri + "index.htm")) {
          resolveduri = resolveduri + "index.htm";
        }
        else {
          HttpExchange.generateErrorResponse(xchg, Http.KWD_FORBIDDEN, null);
          return;
        }
      }
      if (!(Stella.probeFileP(resolveduri))) {
        HttpExchange.generateErrorResponse(xchg, Http.KWD_NOT_FOUND, null);
        return;
      }
      contenttype = Http.guessFileContentType(resolveduri);
      HttpExchange.setReplyHeaderValue(xchg, Http.KWD_CONTENT_TYPE, contenttype);
      { InputFileStream in = null;

        try {
          in = Stella.openInputFile(resolveduri, Stella.NIL);
          { OutputStream self000 = OutputStream.newOutputStream();

            self000.nativeStream = stream;
            InputStream.copyStreamToStream(in, self000);
          }

        } finally {
          if (in != null) {
            in.free();
          }
        }
      }
    }
  }

  /** Serve the specific file specified when the associated handler was published.
   * Simple default implementation for minimal servers such as the Sun JRE HttpServer.
   * @param xchg
   */
  public static void fileHandler(HttpExchange xchg) {
    { String uripath = HttpExchange.getRequestUriPath(xchg);
      PropertyList options = HttpExchange.getHandlerOptions(xchg);
      String path = ((StringWrapper)(options.lookup(Http.KWD_PATH))).wrapperValue;
      String file = ((StringWrapper)(options.lookup(Http.KWD_FILE))).wrapperValue;
      Stella_Object contenttype = options.lookupWithDefault(Http.KWD_CONTENT_TYPE, StringWrapper.wrapString(Http.getHttpMimeType(Http.KWD_HTML, null)));
      edu.isi.stella.javalib.NativeOutputStream stream = HttpExchange.getReplyStream(xchg);

      uripath = Stella.stringTrim(Stella.unescapeUrlString(uripath));
      if (!Stella.stringEqlP(uripath, path)) {
        HttpExchange.generateErrorResponse(xchg, Http.KWD_NOT_FOUND, null);
      }
      else {
        HttpExchange.setReplyHeaderValue(xchg, Http.KWD_CONTENT_TYPE, ((StringWrapper)(contenttype)).wrapperValue);
        { InputFileStream in = null;

          try {
            in = Stella.openInputFile(file, Stella.NIL);
            { OutputStream self000 = OutputStream.newOutputStream();

              self000.nativeStream = stream;
              InputStream.copyStreamToStream(in, self000);
            }

          } finally {
            if (in != null) {
              in.free();
            }
          }
        }
      }
    }
  }

  public static void generateErrorResponse(HttpExchange xchg, Keyword code, String message) {
    { edu.isi.stella.javalib.NativeOutputStream stream = HttpExchange.getReplyStream(xchg);

      HttpExchange.setResponseCode(xchg, code);
      HttpExchange.setReplyHeaderValue(xchg, Http.KWD_CONTENT_TYPE, Http.getHttpMimeType(Http.KWD_HTML, null));
      {
        stream.print("<BODY BGCOLOR='FF9999'>");
        stream.print("ERROR: " + Http.getHttpResponseCode(code, null) + " " + Http.getHttpResponseDesc(code, null));
        if (message != null) {
          stream.println("<BR><BR>" + message);
        }
        stream.println("</BODY>");
      }
    }
  }

  /** Return the options supplied when the handler for this exchange was published.
   * This includes required as well as optional arguments.  This will never return NULL.
   * @param xchg
   * @return PropertyList
   */
  public static PropertyList getHandlerOptions(HttpExchange xchg) {
    return (Http.$HTTP_SERVER_IMPLEMENTATION$.getHandlerOptionsImpl(xchg));
  }

  /** Set the response code of the generated reply to <code>code</code>.  By default
   * :OK (code 200) is used.
   * @param xchg
   * @param code
   */
  public static void setResponseCode(HttpExchange xchg, Keyword code) {
    Http.$HTTP_SERVER_IMPLEMENTATION$.setResponseCodeImpl(xchg, code);
  }

  /** Return the stream to which response methods have to write their output.
   * @param xchg
   * @return edu.isi.stella.javalib.NativeOutputStream
   */
  public static edu.isi.stella.javalib.NativeOutputStream getReplyStream(HttpExchange xchg) {
    return (Http.$HTTP_SERVER_IMPLEMENTATION$.getReplyStreamImpl(xchg));
  }

  /** Returns the remote-address that sent <code>xchg</code> as a string.
   * Concatenates the hostname with a port in standard : notation.  If the hostname
   * can be resolved it will be, otherwise a numeric representation will be returned.
   * Note that different implementations have slightly different behavior.
   * @param xchg
   * @return String
   */
  public static String getRequestRemoteAddress(HttpExchange xchg) {
    return (Http.$HTTP_SERVER_IMPLEMENTATION$.getRequestRemoteAddressImpl(xchg));
  }

  /** Returns the local-address that received <code>xchg</code> as a string.
   * Concatenates the hostname with a port in standard : notation.  If the hostname
   * can be resolved it will be, otherwise a numeric representation will be returned.
   * Note that different implementations have slightly different behavior.
   * @param xchg
   * @return String
   */
  public static String getRequestLocalAddress(HttpExchange xchg) {
    return (Http.$HTTP_SERVER_IMPLEMENTATION$.getRequestLocalAddressImpl(xchg));
  }

  /** Returns the body of <code>xchg</code> as a string.  If there was no body (e.g.,
   * if this was a GET), the result will be the empty string.
   * @param xchg
   * @return String
   */
  public static String getRequestBody(HttpExchange xchg) {
    return (Http.$HTTP_SERVER_IMPLEMENTATION$.getRequestBodyImpl(xchg));
  }

  /** Return the method associated with <code>xchg</code> (:get, :put or :post).
   * @param xchg
   * @return Keyword
   */
  public static Keyword getRequestMethod(HttpExchange xchg) {
    return (Http.$HTTP_SERVER_IMPLEMENTATION$.getRequestMethodImpl(xchg));
  }

  /** Return the raw path portion of the URI associated with <code>xchg</code>.  It is ensured
   * that any URI-encoded characters are not yet decoded to facilitate further parsing.  For example,
   * if the user typed http://a.b.c:42/foo/bar.html#frag?a+b+c into the client, this function will
   * return /foo/bar.html.
   * @param xchg
   * @return String
   */
  public static String getRequestUriPath(HttpExchange xchg) {
    return (Http.$HTTP_SERVER_IMPLEMENTATION$.getRequestUriPathImpl(xchg));
  }

  /** Return the raw query portion of the URI associated with <code>xchg</code>.  It is ensured
   * that any URI-encoded characters are not yet decoded to facilitate further parsing.  For example,
   * if the user typed http://a.b.c:42/foo/bar.html#frag?a+b+c into the client, this function will
   * return a+b+c .
   * @param xchg
   * @return String
   */
  public static String getRequestUriQuery(HttpExchange xchg) {
    return (Http.$HTTP_SERVER_IMPLEMENTATION$.getRequestUriQueryImpl(xchg));
  }

  /** Return the raw URI associated with <code>xchg</code> as a string.  It is ensured
   * that any URI-encoded characters are not yet decoded to facilitate further parsing.
   * This does not include any protocol/scheme and host/port information.  For example, if
   * the user typed http://a.b.c:42/foo/bar.html#frag?a+b+c into the client, this function
   * will return /foo/bar.html#frag?a+b+c .
   * @param xchg
   * @return String
   */
  public static String getRequestUri(HttpExchange xchg) {
    return (Http.$HTTP_SERVER_IMPLEMENTATION$.getRequestUriImpl(xchg));
  }

  /** Set the value associated with <code>key</code> in <code>xchg</code>s reply headers to <code>value</code>.
   * @param xchg
   * @param key
   * @param value
   */
  public static void setReplyHeaderValue(HttpExchange xchg, Keyword key, String value) {
    Http.$HTTP_SERVER_IMPLEMENTATION$.setReplyHeaderValueImpl(xchg, key, value);
  }

  /** Returns the value associated with <code>key</code> in <code>xchg</code>s request
   * headers represented as a string.  If no value is found, NULL will be returned.
   * If there are multiple values, an arbitrary one will be returned.
   * @param xchg
   * @param key
   * @return String
   */
  public static String getHeaderValue(HttpExchange xchg, Keyword key) {
    return (Http.$HTTP_SERVER_IMPLEMENTATION$.getHeaderValueImpl(xchg, key));
  }

}

