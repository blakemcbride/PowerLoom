//  -*- Mode: Java -*-
//
// Http.java

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

public class Http {
  public static Keyword KWD_MAC = null;

  public static Symbol SYM_HTTP_HTTP_HEADERS = null;

  public final static int HTTP_DEFAULT_PORT = 80;

  public static Surrogate SGT_STELLA_FILE_INPUT_STREAM = null;

  public static Surrogate SGT_STELLA_INPUT_STREAM = null;

  public static Keyword KWD_POST = null;

  public static Keyword KWD_GET = null;

  public static Symbol SYM_STELLA_LET = null;

  public static Symbol SYM_STELLA_INPUT_STREAM = null;

  public static Symbol SYM_STELLA_NULL = null;

  public static Symbol SYM_STELLA_UNWIND_PROTECT = null;

  public static Symbol SYM_STELLA_PROGN = null;

  public static Symbol SYM_STELLA_SETQ = null;

  public static Symbol SYM_HTTP_OPEN_URL_STREAM = null;

  public static Symbol SYM_STELLA_WHEN = null;

  public static Symbol SYM_STELLA_DEFINEDp = null;

  public static Symbol SYM_STELLA_CLOSE_STREAM = null;

  public static Keyword KWD_METHOD = null;

  public static Keyword KWD_HEADERS = null;

  public static Keyword KWD_CONTENT = null;

  public static Surrogate SGT_HTTP_HTTP_HEADERS = null;

  public static Symbol SYM_HTTP_STARTUP_HTTP_CLIENT = null;

  public static Symbol SYM_STELLA_METHOD_STARTUP_CLASSNAME = null;

  /** Server instance used for method dispatch - not to be confused
   * with an actual native server object.
   */
  public static HttpServer $HTTP_SERVER_IMPLEMENTATION$ = null;

  public static int $DEFAULT_HTTP_SERVER_PORT$ = 9090;

  public static Symbol SYM_HTTP_HTTP_SERVER_EXIT_HOOK = null;

  public static Cons $HTTP_RESPONSE_CODES$ = null;

  public static Keyword KWD_OK = null;

  public static Keyword KWD_REDIRECT = null;

  public static Keyword KWD_FORBIDDEN = null;

  public static Keyword KWD_NOT_FOUND = null;

  public static Keyword KWD_BAD_REQUEST = null;

  public static Keyword KWD_INTERNAL_ERROR = null;

  public static Keyword KWD_NOT_IMPLEMENTED = null;

  public static Cons $HTTP_MIME_TYPES$ = null;

  public static Keyword KWD_PLAIN_TEXT = null;

  public static Keyword KWD_HTML = null;

  public static Keyword KWD_XML = null;

  public static Keyword KWD_BINARY = null;

  public static Keyword KWD_IMAGE_GIF = null;

  public static Keyword KWD_IMAGE_JPG = null;

  public static Keyword KWD_IMAGE_PNG = null;

  public static Keyword KWD_AUDIO_MPEG = null;

  public static Keyword KWD_PDF = null;

  public static Keyword KWD_MSWORD = null;

  public static String $HTTP_DOCUMENT_ROOT$ = null;

  public static KeyValueMap $HTTP_HANDLER_REGISTRY$ = null;

  public static Keyword KWD_HANDLER_TYPE = null;

  public static Keyword KWD_FILE = null;

  public static Keyword KWD_DIRECTORY = null;

  public static Keyword KWD_HANDLER = null;

  public static Keyword KWD_CONTENT_TYPE = null;

  public static Keyword KWD_PATH = null;

  public static String $HTTP_SERVER_COPYRIGHT_TRAILER$ = null;

  public static Keyword KWD_DOCUMENTATION = null;

  public static Symbol SYM_STELLA_LOAD_SYSTEM = null;

  public static HttpExchange $TEST_HTTP_API_HANDLER_LAST_XCHG$ = null;

  public static Symbol SYM_HTTP_STARTUP_HTTP_SERVER = null;

  /** System-wide session table; each session is indexed on a
   * globally unique session name.
   */
  public static KeyValueMap $SESSION_TABLE$ = null;

  public static Object $SESSIONS_LOCK$ = null;

  public static Surrogate SGT_HTTP_SESSION = null;

  public static Symbol SYM_STELLA_NAME = null;

  public static Symbol SYM_HTTP_TIMEOUT = null;

  public static Symbol SYM_HTTP_TIMESTAMP = null;

  public static Symbol SYM_HTTP_OBJECTS = null;

  public static int $SESSION_TABLE_CLEANUP_COUNTER$ = 0;

  public static Symbol SYM_HTTP_STARTUP_SESSIONS = null;

  /** Takes an internet style URL and returns the components of
   * that URL as specified below.  Missing elements return the empty string &quot;&quot;.
   *   PROTOCOL USERNAME:PASSWORD DOMAIN PORT PATH QUERY FRAGMENT
   * <p>
   *   o Protocol.  The access protocol.
   * <p>
   *        Those schemes which refer to internet protocols mostly have a
   *        common syntax for the rest of the object name. This starts with a
   *        double slash '//' to indicate its presence, and continues until
   *        the following slash '/':
   * <p>
   *   o An optional user name, if required (as it is with a few FTP servers).
   *     The password, if present, follows the user name, separated from it by a colon;
   *     the user name and optional password are followed by a commercial at sign '@'. 
   *   o The internet domain name of the host
   *   o The port number, if it is not the default number for the protocol,
   *     is given in decimal notation after a colon.
   *   o Path The path is a hierarchical representation of a particular path. It may 
   *     define details of how the client should communicate with the server, including
   *     information to be passed transparently to the server without any processing by
   *     the client.
   *     The path is interpreted in a manner dependent on the scheme being used.
   *     Generally, the reserved slash '/' character (ASCII 2F hex) denotes a level in a
   *     hierarchical structure, the higher level part to the left of the slash.
   *   o Query is the part of the hierarchical information following a '?' character.
   *   o Fragment is the part of the hierarchical information following a '#' character.
   * <p>
   * References:  http://www.gbiv.com/protocols/uri/rfc/rfc3986.html
   * @param url
   * @param MV_returnarray
   * @return String
   */
  public static String decomposeInternetUrl(String url, Object [] MV_returnarray) {
    { int fieldStart = 0;
      int fieldEnd = Native.stringSearch(url, Native.makeString(1, ':'), 0);
      String protocol = "";
      String userInformation = "";
      String domainName = "";
      String portNumber = "";
      String path = "";
      String query = "";
      String fragment = "";

      if (fieldEnd != Stella.NULL_INTEGER) {
        protocol = Native.string_subsequence(url, 0, fieldEnd);
        if (fieldEnd == Native.stringSearch(url, "://", fieldEnd)) {
          fieldEnd = fieldEnd + 3;
        }
        else {
          fieldEnd = fieldEnd + 1;
        }
        fieldStart = fieldEnd;
        fieldEnd = Native.string_position(url, '/', fieldStart);
        domainName = Native.string_subsequence(url, fieldStart, fieldEnd);
        fieldStart = fieldEnd;
      }
      fieldEnd = Native.string_position(url, '?', fieldStart);
      if (fieldEnd != Stella.NULL_INTEGER) {
        {
          path = Native.string_subsequence(url, fieldStart, fieldEnd);
          fieldStart = fieldEnd + 1;
          fieldEnd = Native.string_position(url, '#', fieldStart);
          if (fieldEnd != Stella.NULL_INTEGER) {
            {
              query = Native.string_subsequence(url, fieldStart, fieldEnd);
              fieldStart = fieldEnd + 1;
              fragment = Native.string_subsequence(url, fieldStart, Stella.NULL_INTEGER);
            }
          }
          else {
            query = Native.string_subsequence(url, fieldStart, Stella.NULL_INTEGER);
          }
        }
      }
      else {
        {
          fieldEnd = Native.string_position(url, '#', fieldStart);
          if (fieldEnd != Stella.NULL_INTEGER) {
            {
              path = Native.string_subsequence(url, fieldStart, fieldEnd);
              fieldStart = fieldEnd + 1;
              fragment = Native.string_subsequence(url, fieldStart, Stella.NULL_INTEGER);
            }
          }
          else {
            path = Native.string_subsequence(url, fieldStart, Stella.NULL_INTEGER);
          }
        }
      }
      fieldEnd = Native.string_position(domainName, '@', 0);
      if (fieldEnd != Stella.NULL_INTEGER) {
        userInformation = Native.string_subsequence(domainName, 0, fieldEnd);
        domainName = Native.string_subsequence(domainName, fieldEnd + 1, Stella.NULL_INTEGER);
      }
      fieldStart = Native.string_position(domainName, ':', 0);
      if (fieldStart != Stella.NULL_INTEGER) {
        portNumber = Native.string_subsequence(domainName, fieldStart + 1, Stella.NULL_INTEGER);
        domainName = Native.string_subsequence(domainName, 0, fieldStart);
      }
      { String _return_temp = protocol;

        MV_returnarray[0] = StringWrapper.wrapString(userInformation);
        MV_returnarray[1] = StringWrapper.wrapString(domainName);
        MV_returnarray[2] = StringWrapper.wrapString(portNumber);
        MV_returnarray[3] = StringWrapper.wrapString(path);
        MV_returnarray[4] = StringWrapper.wrapString(query);
        MV_returnarray[5] = StringWrapper.wrapString(fragment);
        return (_return_temp);
      }
    }
  }

  /** The inverse to <code>decomposeInternetUrl</code>.  Builds a URL string from the supplied
   * components.  Undefined portions can be supplied as NULL or the empty string.
   * @param protocol
   * @param userinfo
   * @param host
   * @param port
   * @param path
   * @param query
   * @param fragment
   * @return String
   */
  public static String composeInternetUrl(String protocol, String userinfo, String host, int port, String path, String query, String fragment) {
    { OutputStringStream url = OutputStringStream.newOutputStringStream();

      if (!(Stella.blankStringP(protocol))) {
        url.nativeStream.print(protocol + "://");
      }
      if (!(Stella.blankStringP(userinfo))) {
        url.nativeStream.print(userinfo + "@");
      }
      if (!(Stella.blankStringP(host))) {
        url.nativeStream.print(host);
      }
      if (port != Stella.NULL_INTEGER) {
        url.nativeStream.print(":" + port);
      }
      if (!(Stella.blankStringP(path))) {
        if (Stella.startsWithP(path, "/", 0)) {
          url.nativeStream.print(path);
        }
        else {
          url.nativeStream.print("/" + path);
        }
      }
      if (!(Stella.blankStringP(query))) {
        url.nativeStream.print("?" + query);
      }
      if (!(Stella.blankStringP(fragment))) {
        url.nativeStream.print("#" + fragment);
      }
      return (url.theStringReader());
    }
  }

  /** Transform a URL <code>path</code> into a valid native filename for the local OS.
   * @param path
   * @return String
   */
  public static String urlPathToFilename(String path) {
    { char separator = Stella.directorySeparator();

      if (separator == '/') {
        return (Stella.unescapeUrlString(path));
      }
      else {
        {
          path = Stella.unescapeUrlString(Native.string_substitute(path, separator, '/'));
          if ((Stella.operatingSystem() == Http.KWD_MAC) &&
              (path.charAt(0) == separator)) {
            path = Native.string_subsequence(path, 1, Stella.NULL_INTEGER);
          }
          return (path);
        }
      }
    }
  }

  /** Handles the first line of an http header.  
   * Returns version, response code, response message.  The first
   * line is inserted into <code>fields</code> fields with the empty string key &quot;&quot;
   * This is a low-level utility routine that can be used to build custom
   * message parsing code.
   * @param line
   * @param fields
   * @param MV_returnarray
   * @return String
   */
  public static String handleHttpHeaderFirstLine(String line, KeyValueList fields, Object [] MV_returnarray) {
    { int space1 = Native.string_position(line, ' ', 0);
      int space2 = ((space1 == Stella.NULL_INTEGER) ? Stella.NULL_INTEGER : Native.string_position(line, ' ', space1 + 1));

      if (space2 == Stella.NULL_INTEGER) {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("Malformed header line: `" + line + "'");
          throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
      fields.insertAt(StringWrapper.wrapString(""), StringWrapper.wrapString(line));
      { String _return_temp = Native.string_subsequence(line, 0, space1);

        MV_returnarray[0] = IntegerWrapper.wrapInteger(((int)(Native.stringToInteger(Native.string_subsequence(line, space1 + 1, space2)))));
        MV_returnarray[1] = StringWrapper.wrapString(Native.string_subsequence(line, space2 + 1, Stella.NULL_INTEGER));
        return (_return_temp);
      }
    }
  }

  /** Handles header lines other than the first one.
   * Each such line is inserted into <code>fields</code> as keyword value pairs.
   * This is a low-level utility routine that can be used to build custom
   * message parsing code.
   * @param line
   * @param fields
   */
  public static void handleHttpHeaderOtherLine(String line, KeyValueList fields) {
    { int colonPosition = Native.string_position(line, ':', 0);

      if (colonPosition == Stella.NULL_INTEGER) {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("Bad header seen: `" + line + "'");
          throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
      else {
        fields.insertAt(StringWrapper.wrapString(Native.string_subsequence(line, 0, colonPosition)), StringWrapper.wrapString(Native.string_subsequence(line, colonPosition + 2, Stella.NULL_INTEGER)));
      }
    }
  }

  public static String readHttpHeaderLine(InputStream stream) {
    { String line = InputStream.nativeReadLine(stream);
      int length = line.length();
      char nextchar = Stella.NULL_CHARACTER;

      if (line == null) {
        return (null);
      }
      if ((length > 0) &&
          (line.charAt((length - 1)) == '\r')) {
        return (Native.string_subsequence(line, 0, length - 1));
      }
      nextchar = InputStream.readCharacter(stream, new Object[1]);
      if (nextchar == '\n') {
      }
      else {
        Stella.unreadCharacter(nextchar, stream);
      }
      return (line);
    }
  }

  /** Reads the HTTP header from <code>stream</code>, parses the header fields
   * and stores the results in <code>fields</code>.  The first line of the response will be
   * stored in <code>fields</code> with the empty string &quot;&quot; as the key.  Other values will
   * have the header name as the key.  The first return value is the response code
   * of the HTTP request.  A response of 200 indicates success.  Other common
   * responses are 404 (page not found).  The second return value is the message
   * associated with the code.  The third return value is the version information.
   * If the stream ends before a valid header is read, then <code>null</code> is returned for
   * all values.
   * @param stream
   * @param fields
   * @param MV_returnarray
   * @return int
   */
  public static int readHttpHeader(InputStream stream, KeyValueList fields, Object [] MV_returnarray) {
    { String versionString = null;
      int responseCode = Stella.NULL_INTEGER;
      String responseMessage = null;

      { Object [] caller_MV_returnarray = new Object[2];

        versionString = Http.handleHttpHeaderFirstLine(Http.readHttpHeaderLine(stream), fields, caller_MV_returnarray);
        responseCode = ((int)(((IntegerWrapper)(caller_MV_returnarray[0])).wrapperValue));
        responseMessage = ((String)(((StringWrapper)(caller_MV_returnarray[1])).wrapperValue));
      }
      { String line = null;

        loop000 : for (;;) {
          line = Http.readHttpHeaderLine(stream);
          if (Stella.stringEqlP(line, "")) {
            break loop000;
          }
          else if (line == null) {
            break loop000;
          }
          else {
            Http.handleHttpHeaderOtherLine(line, fields);
          }
        }
        { int _return_temp = responseCode;

          MV_returnarray[0] = StringWrapper.wrapString(responseMessage);
          MV_returnarray[1] = StringWrapper.wrapString(versionString);
          return (_return_temp);
        }
      }
    }
  }

  public static Stella_Object getContentAndLength(Stella_Object content, Object [] MV_returnarray) {
    { Surrogate testValue000 = Stella_Object.safePrimaryType(content);

      if (Surrogate.subtypeOfStringP(testValue000)) {
        { StringWrapper content000 = ((StringWrapper)(content));

          { Stella_Object _return_temp = content000;

            MV_returnarray[0] = Stella.wrapLongInteger(((long)((StringWrapper.unwrapString(content000)).length())));
            return (_return_temp);
          }
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, Http.SGT_STELLA_FILE_INPUT_STREAM)) {
        { InputFileStream content000 = ((InputFileStream)(content));

          { Stella_Object _return_temp = content000;

            MV_returnarray[0] = Stella.wrapLongInteger(Stella.fileLength(content000.filename));
            return (_return_temp);
          }
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, Http.SGT_STELLA_INPUT_STREAM)) {
        { InputStream content000 = ((InputStream)(content));

          { String contentstring = content000.streamToString();

            { Stella_Object _return_temp = StringWrapper.wrapString(contentstring);

              MV_returnarray[0] = Stella.wrapLongInteger(((long)(contentstring.length())));
              return (_return_temp);
            }
          }
        }
      }
      else {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("`" + testValue000 + "' is not a valid case option");
          throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
    }
  }

  /** Send <code>content</code> as an HTTP 1.0 request on <code>stream</code> using <code>method</code>.
   * The request is sent to <code>urlPath</code> at <code>host</code>.  The <code>stream</code> must be a TCP-stream
   * that is connected to <code>host</code> at the appropriate port.  <code>content</code> can be a string or
   * an input stream to read from.
   * @param stream
   * @param method
   * @param host
   * @param urlPath
   * @param headers
   * @param content
   */
  public static void writeHttpRequest(OutputStream stream, Keyword method, String host, String urlPath, KeyValueList headers, Stella_Object content) {
    { long contentlength = 0l;

      stream.nativeStream.print(method.symbolName + " " + urlPath + " HTTP/1.0\r\n");
      if (host != null) {
        if (headers == null) {
          headers = KeyValueList.newKeyValueList();
        }
        headers.insertAt(StringWrapper.wrapString("Host"), StringWrapper.wrapString(host));
      }
      if (content != null) {
        { Object [] caller_MV_returnarray = new Object[1];

          content = Http.getContentAndLength(content, caller_MV_returnarray);
          contentlength = ((long)(((LongIntegerWrapper)(caller_MV_returnarray[0])).wrapperValue));
        }
        if (headers == null) {
          headers = KeyValueList.newKeyValueList();
        }
        headers.insertAt(StringWrapper.wrapString("Content-Length"), StringWrapper.wrapString(Native.integerToString(contentlength)));
      }
      if (headers != null) {
        { StringWrapper key = null;
          StringWrapper value = null;
          KvCons iter000 = headers.theKvList;

          for (;iter000 != null; iter000 = iter000.rest) {
            key = ((StringWrapper)(iter000.key));
            value = ((StringWrapper)(iter000.value));
            stream.nativeStream.print(StringWrapper.unwrapString(key) + ": " + StringWrapper.unwrapString(value) + "\r\n");
          }
        }
      }
      stream.nativeStream.print("Connection: close\r\n");
      stream.nativeStream.print("\r\n");
      if (content != null) {
        { Surrogate testValue000 = Stella_Object.safePrimaryType(content);

          if (Surrogate.subtypeOfStringP(testValue000)) {
            { StringWrapper content000 = ((StringWrapper)(content));

              stream.nativeStream.print(StringWrapper.unwrapString(content000));
            }
          }
          else if (Surrogate.subtypeOfP(testValue000, Http.SGT_STELLA_INPUT_STREAM)) {
            { InputStream content000 = ((InputStream)(content));

              InputStream.copyStreamToStream(content000, stream);
            }
          }
          else {
            { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

              stream000.nativeStream.print("`" + testValue000 + "' is not a valid case option");
              throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
            }
          }
        }
      }
      OutputStream.flushOutput(stream);
    }
  }

  /** Posts <code>content</code> as data to <code>urlPath</code> on <code>host</code> and <code>port</code>.
   * <code>content</code> can be a string or an input stream to read from.  The port value for
   * standard http servers is 80.  Returns the body of the reply message as a stream,
   * if successful.  Otherwise an HTTP-EXCEPTION is signaled.
   * @param host
   * @param port
   * @param urlPath
   * @param headers
   * @param content
   * @return InputStream
   */
  public static InputStream httpPostData(String host, int port, String urlPath, KeyValueList headers, Stella_Object content) {
    { KeyValueList returnHeaders = KeyValueList.newKeyValueList();

      { Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();

        try {
          Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, false);
          { InputStream in = null;
            OutputStream out = null;

            { Object [] caller_MV_returnarray = new Object[1];

              in = Stella.openNetworkStream(host, port, caller_MV_returnarray);
              out = ((OutputStream)(caller_MV_returnarray[0]));
            }
            Http.writeHttpRequest(out, Http.KWD_POST, host, urlPath, headers, content);
            { int returnCode = Stella.NULL_INTEGER;
              String returnMessage = null;
              String version = null;

              { Object [] caller_MV_returnarray = new Object[2];

                returnCode = Http.readHttpHeader(in, returnHeaders, caller_MV_returnarray);
                returnMessage = ((String)(((StringWrapper)(caller_MV_returnarray[0])).wrapperValue));
                version = ((String)(((StringWrapper)(caller_MV_returnarray[1])).wrapperValue));
              }
              version = version;
              if (Http.httpSuccessResponseCodeP(returnCode)) {
                return (in);
              }
              else {
                { HttpException self001 = HttpException.newHttpException(returnMessage);

                  self001.errorCode = returnCode;
                  { HttpException ex = self001;

                    Stella.STANDARD_OUTPUT.nativeStream.print("http-post-data: code=" + returnCode + ", message=" + returnMessage + ", version=" + version);
                    Stream.closeStream(in);
                    Stream.closeStream(out);
                    throw ((HttpException)(ex.fillInStackTrace()));
                  }
                }
              }
            }
          }

        } finally {
          Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
        }
      }
    }
  }

  /** Just like <code>httpPostData</code> (which see) but returns the reply as a string.
   * CAUTION: String conversion will not do the right thing for binary data in Java.
   * @param host
   * @param port
   * @param urlPath
   * @param headers
   * @param content
   * @return String
   */
  public static String httpPostDataToString(String host, int port, String urlPath, KeyValueList headers, Stella_Object content) {
    { InputStream stream = Http.httpPostData(host, port, urlPath, headers, content);
      String data = stream.streamToString();

      Stream.closeStream(stream);
      return (data);
    }
  }

  /** Accesses the data described by <code>urlPath</code> on <code>host</code> and <code>port</code>.
   * The port value for standard http servers is 80.  If successful, returns the body
   * of the web message as a stream.  The headers from the reply message will be set
   * in <code>returnHeaders</code> if not null'.  If an error occurs an HTTP-EXCEPTION is signaled.
   * @param host
   * @param port
   * @param urlPath
   * @param returnHeaders
   * @return InputStream
   */
  public static InputStream httpGetData(String host, int port, String urlPath, KeyValueList returnHeaders) {
    if (returnHeaders == null) {
      returnHeaders = KeyValueList.newKeyValueList();
    }
    { Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();

      try {
        Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, false);
        { InputStream in = null;
          OutputStream out = null;

          { Object [] caller_MV_returnarray = new Object[1];

            in = Stella.openNetworkStream(host, port, caller_MV_returnarray);
            out = ((OutputStream)(caller_MV_returnarray[0]));
          }
          Http.writeHttpRequest(out, Http.KWD_GET, host, urlPath, null, null);
          { int returnCode = Stella.NULL_INTEGER;
            String returnMessage = null;
            String version = null;

            { Object [] caller_MV_returnarray = new Object[2];

              returnCode = Http.readHttpHeader(in, returnHeaders, caller_MV_returnarray);
              returnMessage = ((String)(((StringWrapper)(caller_MV_returnarray[0])).wrapperValue));
              version = ((String)(((StringWrapper)(caller_MV_returnarray[1])).wrapperValue));
            }
            version = version;
            if (Http.httpSuccessResponseCodeP(returnCode)) {
              return (in);
            }
            else {
              { HttpException self001 = HttpException.newHttpException(returnMessage);

                self001.errorCode = returnCode;
                { HttpException ex = self001;

                  Stella.STANDARD_OUTPUT.nativeStream.print("http-get-data: code=" + returnCode + ", message=" + returnMessage + ", version=" + version);
                  Stream.closeStream(in);
                  Stream.closeStream(out);
                  throw ((HttpException)(ex.fillInStackTrace()));
                }
              }
            }
          }
        }

      } finally {
        Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
      }
    }
  }

  /** Just like <code>httpGetData</code> (which see) but returns the result as a string.
   * CAUTION: String conversion will not do the right thing for binary data in Java.
   * @param host
   * @param port
   * @param urlPath
   * @param returnHeaders
   * @return String
   */
  public static String httpGetDataToString(String host, int port, String urlPath, KeyValueList returnHeaders) {
    { InputStream stream = Http.httpGetData(host, port, urlPath, returnHeaders);
      String data = stream.streamToString();

      Stream.closeStream(stream);
      return (data);
    }
  }

  /** Opens an input stream to <code>url</code>.
   * Currently only http: with no user name or password and file: urls on the local
   * host with absolute pathnames are supported.
   * @param url
   * @return InputStream
   */
  public static InputStream openUrlStream(String url) {
    { String protocol = null;
      String userInfo = null;
      String host = null;
      String port = null;
      String path = null;
      String query = null;
      String fragment = null;

      { Object [] caller_MV_returnarray = new Object[6];

        protocol = Http.decomposeInternetUrl(url, caller_MV_returnarray);
        userInfo = ((String)(((StringWrapper)(caller_MV_returnarray[0])).wrapperValue));
        host = ((String)(((StringWrapper)(caller_MV_returnarray[1])).wrapperValue));
        port = ((String)(((StringWrapper)(caller_MV_returnarray[2])).wrapperValue));
        path = ((String)(((StringWrapper)(caller_MV_returnarray[3])).wrapperValue));
        query = ((String)(((StringWrapper)(caller_MV_returnarray[4])).wrapperValue));
        fragment = ((String)(((StringWrapper)(caller_MV_returnarray[5])).wrapperValue));
      }
      { String testValue000 = Native.stringDowncase(protocol);

        if (Stella.stringEqlP(testValue000, "http")) {
          if (!Stella.stringEqlP(userInfo, "")) {
            { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

              stream000.nativeStream.print("open-url-stream: only URLs without user information are supported: `" + url + "'");
              throw ((BadArgumentException)(BadArgumentException.newBadArgumentException(stream000.theStringReader()).fillInStackTrace()));
            }
          }
          else {
            { int theport = Http.HTTP_DEFAULT_PORT;
              String thepath = Http.composeInternetUrl("", "", "", Stella.NULL_INTEGER, path, query, fragment);

              if (!(Stella.blankStringP(port))) {
                theport = ((int)(Native.stringToInteger(port)));
              }
              return (Http.httpGetData(host, theport, thepath, null));
            }
          }
        }
        else if (Stella.stringEqlP(testValue000, "file")) {
          if (!Stella.stringEqlP(userInfo, "")) {
            { OutputStringStream stream001 = OutputStringStream.newOutputStringStream();

              stream001.nativeStream.print("open-url-stream: only URLs without user information are supported: `" + url + "'");
              throw ((BadArgumentException)(BadArgumentException.newBadArgumentException(stream001.theStringReader()).fillInStackTrace()));
            }
          }
          else if (Stella.blankStringP(host) ||
              Stella.stringEqlP(host, "localhost")) {
            return (InputFileStream.newInputFileStream(Http.urlPathToFilename(path)));
          }
          else {
            { OutputStringStream stream002 = OutputStringStream.newOutputStringStream();

              stream002.nativeStream.print("open-url-stream: only absolute file URLs on the local host are supported: `" + url + "'");
              throw ((BadArgumentException)(BadArgumentException.newBadArgumentException(stream002.theStringReader()).fillInStackTrace()));
            }
          }
        }
        else {
          { OutputStringStream stream003 = OutputStringStream.newOutputStringStream();

            stream003.nativeStream.print("open-url-stream: only http and file URLs are supported: `" + url + "'");
            throw ((BadArgumentException)(BadArgumentException.newBadArgumentException(stream003.theStringReader()).fillInStackTrace()));
          }
        }
      }
    }
  }

  /** Sets up an unwind-protected form which opens a URL for
   * input and closes it afterwards.  The stream for reading is bound to the
   * variable provided in the macro form.
   * Syntax is <code>_WITH_INPUT_URL__var_url__bodyI_</code>.
   * @param binding
   * @param body
   * @return Stella_Object
   */
  public static Stella_Object withInputUrl(Cons binding, Cons body) {
    { Symbol var = ((Symbol)(binding.value));

      return (Cons.list$(Cons.cons(Http.SYM_STELLA_LET, Cons.cons(Cons.cons(Cons.cons(var, Cons.list$(Cons.cons(Http.SYM_STELLA_INPUT_STREAM, Cons.cons(Http.SYM_STELLA_NULL, Cons.cons(Stella.NIL, Stella.NIL))))), Stella.NIL), Cons.cons(Cons.list$(Cons.cons(Http.SYM_STELLA_UNWIND_PROTECT, Cons.cons(Cons.list$(Cons.cons(Http.SYM_STELLA_PROGN, Cons.cons(Cons.list$(Cons.cons(Http.SYM_STELLA_SETQ, Cons.cons(var, Cons.cons(Cons.cons(Cons.list$(Cons.cons(Http.SYM_HTTP_OPEN_URL_STREAM, Cons.cons(binding.rest.value, Cons.cons(Stella.NIL, Stella.NIL)))), Stella.NIL), Stella.NIL)))), Cons.cons(body.concatenate(Stella.NIL, Stella.NIL), Stella.NIL)))), Cons.cons(Cons.list$(Cons.cons(Http.SYM_STELLA_WHEN, Cons.cons(Cons.list$(Cons.cons(Http.SYM_STELLA_DEFINEDp, Cons.cons(var, Cons.cons(Stella.NIL, Stella.NIL)))), Cons.cons(Cons.list$(Cons.cons(Http.SYM_STELLA_CLOSE_STREAM, Cons.cons(var, Cons.cons(Stella.NIL, Stella.NIL)))), Cons.cons(Stella.NIL, Stella.NIL))))), Cons.cons(Stella.NIL, Stella.NIL))))), Cons.cons(Stella.NIL, Stella.NIL))))));
    }
  }

  /** Download the data at <code>url</code> and save it to <code>file</code>.
   * @param url
   * @param file
   */
  public static void downloadUrl(String url, String file) {
    { OutputFileStream out = null;

      try {
        out = Stella.openOutputFile(file, Stella.NIL);
        { InputStream in = null;

          try {
            in = Http.openUrlStream(url);
            InputStream.copyStreamToStream(in, out);

          } finally {
            if (in != null) {
              Stream.closeStream(in);
            }
          }
        }

      } finally {
        if (out != null) {
          out.free();
        }
      }
    }
  }

  public static void downloadUrlEvaluatorWrapper(Cons arguments) {
    Http.downloadUrl(((StringWrapper)(arguments.value)).wrapperValue, ((StringWrapper)(arguments.rest.value)).wrapperValue);
  }

  /** Download the data at <code>url</code> and return it as a string.
   * CAUTION: String conversion will not do the right thing for binary data in Java.
   * @param url
   * @return String
   */
  public static String downloadUrlToString(String url) {
    { String result = null;

      { InputStream in = null;

        try {
          in = Http.openUrlStream(url);
          result = in.streamToString();

        } finally {
          if (in != null) {
            Stream.closeStream(in);
          }
        }
      }
      return (result);
    }
  }

  public static StringWrapper downloadUrlToStringEvaluatorWrapper(Cons arguments) {
    { String result = Http.downloadUrlToString(((StringWrapper)(arguments.value)).wrapperValue);

      if (result != null) {
        return (StringWrapper.wrapString(result));
      }
      else {
        return (null);
      }
    }
  }

  /** Send an http request to <code>uri</code> and return a string representing the result.
   * @param uri
   * @param options
   * @return String
   */
  public static String doHttpRequest(String uri, Cons options) {
    { PropertyList proplist = Stella_Object.vetOptions(options, Stella.getQuotedTree("((:METHOD :HEADERS :CONTENT) \"/HTTP\")", "/HTTP"));
      Keyword method = ((Keyword)(proplist.lookupWithDefault(Http.KWD_METHOD, Http.KWD_GET)));
      Dictionary headers = ((Dictionary)(proplist.lookup(Http.KWD_HEADERS)));
      StringWrapper content = ((StringWrapper)(proplist.lookup(Http.KWD_CONTENT)));

      if (headers != null) {
        if (!(Stella_Object.isaP(headers, StandardObject.typeSpecToBaseType(Surrogate.realTypeSpecifier(Http.SGT_HTTP_HTTP_HEADERS))))) {
          { KeyValueList httpheaders = KeyValueList.newKeyValueList();

            { Stella_Object key = null;
              Stella_Object value = null;
              DictionaryIterator iter000 = ((DictionaryIterator)(headers.allocateIterator()));

              while (iter000.nextP()) {
                key = iter000.key;
                value = iter000.value;
                httpheaders.insertAt(((StringWrapper)(key)), ((StringWrapper)(value)));
              }
            }
            headers = httpheaders;
          }
        }
      }
      { String protocol = null;
        String userInfo = null;
        String host = null;
        String port = null;
        String path = null;
        String query = null;
        String fragment = null;

        { Object [] caller_MV_returnarray = new Object[6];

          protocol = Http.decomposeInternetUrl(uri, caller_MV_returnarray);
          userInfo = ((String)(((StringWrapper)(caller_MV_returnarray[0])).wrapperValue));
          host = ((String)(((StringWrapper)(caller_MV_returnarray[1])).wrapperValue));
          port = ((String)(((StringWrapper)(caller_MV_returnarray[2])).wrapperValue));
          path = ((String)(((StringWrapper)(caller_MV_returnarray[3])).wrapperValue));
          query = ((String)(((StringWrapper)(caller_MV_returnarray[4])).wrapperValue));
          fragment = ((String)(((StringWrapper)(caller_MV_returnarray[5])).wrapperValue));
        }
        userInfo = userInfo;
        if (!(Stella.stringEqualP(protocol, "http"))) {
          { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

            stream000.nativeStream.print("do-http-request: unsupported protocol: `" + protocol + "'");
            throw ((BadArgumentException)(BadArgumentException.newBadArgumentException(stream000.theStringReader()).fillInStackTrace()));
          }
        }
        { int theport = Http.HTTP_DEFAULT_PORT;
          String thepath = Http.composeInternetUrl("", "", "", Stella.NULL_INTEGER, path, query, fragment);

          if (!(Stella.blankStringP(port))) {
            theport = ((int)(Native.stringToInteger(port)));
          }
          if (method == Http.KWD_GET) {
            return (Http.httpGetDataToString(host, theport, thepath, ((KeyValueList)(headers))));
          }
          else if (method == Http.KWD_POST) {
            return (Http.httpPostDataToString(host, theport, thepath, ((KeyValueList)(headers)), content));
          }
          else {
            { OutputStringStream stream001 = OutputStringStream.newOutputStringStream();

              stream001.nativeStream.print("do-http-request: unsupported method: `" + method + "'");
              throw ((BadArgumentException)(BadArgumentException.newBadArgumentException(stream001.theStringReader()).fillInStackTrace()));
            }
          }
        }
      }
    }
  }

  public static StringWrapper doHttpRequestEvaluatorWrapper(Cons arguments) {
    { String result = Http.doHttpRequest(((StringWrapper)(arguments.value)).wrapperValue, arguments.rest);

      if (result != null) {
        return (StringWrapper.wrapString(result));
      }
      else {
        return (null);
      }
    }
  }

  /** Return a default HTTP server implementation system for the case
   * where none has been loaded yet.  If <code>errorP</code> is TRUE, raise an error if none
   * is defined for the current native language environment.
   * @param errorP
   * @return String
   */
  public static String getDefaultHttpServerImpl(boolean errorP) {
    return ("webtools-sun");
  }

  /** Start an HTTP server running at <code>port</code>.  If there is already
   * a server instance running, it will be stopped first.  If <code>port</code> is &lt;= 0 or
   * NULL, use the value of <code>$DEFAULT_HTTP_SERVER_PORT$</code>.  Returns the listening
   * address of the started server instance.
   * @param port
   * @return String
   */
  public static String startHttpServer(int port) {
    if (Http.$HTTP_SERVER_IMPLEMENTATION$ == null) {
      Stella.autoload("HTTP-SERVER-IMPL-SYSTEM", Http.getDefaultHttpServerImpl(true), null, false);
      if (Http.$HTTP_SERVER_IMPLEMENTATION$ == null) {
        throw ((StellaException)(StellaException.newStellaException("start-http-server: no HTTP server implementation loaded").fillInStackTrace()));
      }
    }
    if (port <= 0) {
      port = Http.$DEFAULT_HTTP_SERVER_PORT$;
    }
    { String temp000 = Http.$HTTP_SERVER_IMPLEMENTATION$.startHttpServerImpl(port);

      { String address = ((temp000 != null) ? temp000 : ("http://localhost:" + Native.integerToString(((long)(port))) + "/"));

        HookList.addHook(Stella.$STELLA_EXIT_HOOKS$, Http.SYM_HTTP_HTTP_SERVER_EXIT_HOOK);
        Http.publishRegisteredHttpHandlers();
        return (address);
      }
    }
  }

  public static StringWrapper startHttpServerEvaluatorWrapper(Cons arguments) {
    { String result = Http.startHttpServer(((IntegerWrapper)(arguments.value)).wrapperValue);

      if (result != null) {
        return (StringWrapper.wrapString(result));
      }
      else {
        return (null);
      }
    }
  }

  /** Stop any currently running HTTP server.  If there is no
   * server instance running, this is a no-op.
   */
  public static void stopHttpServer() {
    if (Http.$HTTP_SERVER_IMPLEMENTATION$ == null) {
      Stella.autoload("HTTP-SERVER-IMPL-SYSTEM", Http.getDefaultHttpServerImpl(true), null, false);
      if (Http.$HTTP_SERVER_IMPLEMENTATION$ == null) {
        throw ((StellaException)(StellaException.newStellaException("stop-http-server: no HTTP server implementation loaded").fillInStackTrace()));
      }
    }
    Http.$HTTP_SERVER_IMPLEMENTATION$.stopHttpServerImpl();
  }

  /** Hook function that will be called upon PowerLoom exit.
   * This is a no-op if no server is running or if the server is not supported.
   * @param argument
   */
  public static void httpServerExitHook(Stella_Object argument) {
    argument = argument;
    if (Http.$HTTP_SERVER_IMPLEMENTATION$ != null) {
      try {
        Http.stopHttpServer();
      } catch (java.lang.Exception e) {
        Stella.STANDARD_OUTPUT.nativeStream.print("ERROR: http-server-exit-hook: " + Stella.exceptionMessage(e));
      }
    }
  }

  public static int getHttpResponseCode(Keyword codename, Keyword renamed_Default) {
    { Cons entry = null;
      Cons iter000 = Http.$HTTP_RESPONSE_CODES$;

      for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
        entry = ((Cons)(iter000.value));
        if (entry.value == codename) {
          return (((IntegerWrapper)(entry.rest.value)).wrapperValue);
        }
      }
    }
    if (renamed_Default == null) {
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("get-http-response-code: undefined response code: `" + codename + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
    else {
      return (Http.getHttpResponseCode(renamed_Default, null));
    }
  }

  public static String getHttpResponseDesc(Keyword codename, Keyword renamed_Default) {
    { Cons entry = null;
      Cons iter000 = Http.$HTTP_RESPONSE_CODES$;

      for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
        entry = ((Cons)(iter000.value));
        if (entry.value == codename) {
          return (((StringWrapper)(entry.rest.rest.value)).wrapperValue);
        }
      }
    }
    if (renamed_Default == null) {
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("get-http-response-desc: undefined response code: `" + codename + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
    else {
      return (Http.getHttpResponseDesc(renamed_Default, null));
    }
  }

  public static boolean httpSuccessResponseCodeP(int code) {
    return ((code >= 200) &&
        (code <= 205));
  }

  public static String getHttpMimeType(Keyword typename, Keyword renamed_Default) {
    { Cons entry = null;
      Cons iter000 = Http.$HTTP_MIME_TYPES$;

      for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
        entry = ((Cons)(iter000.value));
        if (entry.value == typename) {
          return (((StringWrapper)(entry.rest.value)).wrapperValue);
        }
      }
    }
    if (renamed_Default == null) {
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("get-http-mime-type: undefined mime type: `" + typename + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
    else {
      return (Http.getHttpMimeType(renamed_Default, null));
    }
  }

  public static String getHttpMimeTypeFromExtension(String extension) {
    { Cons entry = null;
      Cons iter000 = Http.$HTTP_MIME_TYPES$;

      for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
        entry = ((Cons)(iter000.value));
        { boolean foundP000 = false;

          { Stella_Object ext = null;
            Cons iter001 = entry.rest.rest;

            loop001 : for (;!(iter001 == Stella.NIL); iter001 = iter001.rest) {
              ext = iter001.value;
              if (Stella_Object.eqlToStringP(ext, extension)) {
                foundP000 = true;
                break loop001;
              }
            }
          }
          if (foundP000) {
            return (((StringWrapper)(entry.rest.value)).wrapperValue);
          }
        }
      }
    }
    return ("application/octet-stream");
  }

  public static String guessFileContentType(String file) {
    return (Http.getHttpMimeTypeFromExtension(Native.string_subsequence(Native.stringDowncase(Stella.fileExtension(file)), 1, Stella.NULL_INTEGER)));
  }

  /** Given the <code>arguments</code> following the <code>P</code> character in a URL, split them at
   * <code>separator</code> and return them as a list of properly decoded strings.
   * @param arguments
   * @param separator
   * @return Cons
   */
  public static Cons parseAndDecodeUrlArguments(String arguments, char separator) {
    if (Stella.blankStringP(arguments)) {
      return (Stella.NIL);
    }
    { Cons result = Stella.splitString(arguments, separator);
      Cons cursor = result;

      while (!(cursor == Stella.NIL)) {
        cursor.firstSetter(StringWrapper.wrapString(Stella.unescapeUrlString(((StringWrapper)(cursor.value)).wrapperValue)));
        cursor = cursor.rest;
      }
      return (result);
    }
  }

  /** Given the <code>values</code> returned by a form, parse and decode them and return them as
   * a key-value-list.  NOTE: values will not be trimmed and empty values will be represented by the empty
   * string rather than NULL.  Also, if the same input name occurs more than once, only the value of the
   * last input will be recorded in the resulting key-value-list.
   * @param values
   * @return KeyValueList
   */
  public static KeyValueList parseAndDecodeFormValues(String values) {
    { KeyValueList result = KeyValueList.newKeyValueList();
      String bareentry = null;
      int split = 0;

      values = Native.string_substitute(values, ' ', '+');
      { StringWrapper entry = null;
        Cons iter000 = Stella.splitString(values, '&');

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          entry = ((StringWrapper)(iter000.value));
          bareentry = StringWrapper.unwrapString(entry);
          split = Native.string_position(bareentry, '=', 0);
          if (split != Stella.NULL_INTEGER) {
            result.insertAt(StringWrapper.wrapString(Stella.unescapeUrlString(Native.string_subsequence(bareentry, 0, split))), StringWrapper.wrapString(Stella.unescapeUrlString(Native.string_subsequence(bareentry, split + 1, Stella.NULL_INTEGER))));
          }
        }
      }
      return (result);
    }
  }

  /** Given the <code>values</code> returned by a form, parse and decode them and return them as
   * a property-list.  NOTE: values will not be trimmed and empty values will be represented by the empty
   * string rather than NULL.  Keys will be inserted into the result in the order they appear in the form.
   * If they are non-unique, multiple entries per key will result which can be iterated over, however,
   * standard <code>lookup</code> calls will return the value of the first key only.
   * @param values
   * @return PropertyList
   */
  public static PropertyList parseAndDecodeNonUniqueFormValues(String values) {
    { Cons result = Stella.NIL;
      String bareentry = null;
      int split = 0;

      values = Native.string_substitute(values, ' ', '+');
      { StringWrapper entry = null;
        Cons iter000 = Stella.splitString(values, '&');

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          entry = ((StringWrapper)(iter000.value));
          bareentry = StringWrapper.unwrapString(entry);
          split = Native.string_position(bareentry, '=', 0);
          if (split != Stella.NULL_INTEGER) {
            result = Cons.cons(StringWrapper.wrapString(Stella.unescapeUrlString(Native.string_subsequence(bareentry, 0, split))), result);
            result = Cons.cons(StringWrapper.wrapString(Stella.unescapeUrlString(Native.string_subsequence(bareentry, split + 1, Stella.NULL_INTEGER))), result);
          }
        }
      }
      { PropertyList self000 = PropertyList.newPropertyList();

        self000.thePlist = result.reverse();
        { PropertyList value000 = self000;

          return (value000);
        }
      }
    }
  }

  public static String getHttpDocumentRoot() {
    return (Http.$HTTP_DOCUMENT_ROOT$);
  }

  public static StringWrapper getHttpDocumentRootEvaluatorWrapper(Cons arguments) {
    arguments = arguments;
    { String result = Http.getHttpDocumentRoot();

      if (result != null) {
        return (StringWrapper.wrapString(result));
      }
      else {
        return (null);
      }
    }
  }

  /** Set the document root to <code>root</code>.  Important: this needs to be
   * called before any handlers are published, otherwise it won't be effective.
   * @param root
   */
  public static void setHttpDocumentRoot(String root) {
    Http.$HTTP_DOCUMENT_ROOT$ = root;
  }

  public static void setHttpDocumentRootEvaluatorWrapper(Cons arguments) {
    Http.setHttpDocumentRoot(((StringWrapper)(arguments.value)).wrapperValue);
  }

  /** Publish all currently registered HTTP handler with the current HTTP server.
   * This is run every time a server is started with <code>startHttpServer</code>.
   */
  public static void publishRegisteredHttpHandlers() {
    if (Http.$HTTP_SERVER_IMPLEMENTATION$ == null) {
      throw ((StellaException)(StellaException.newStellaException("publish-registered-http-handlers: no HTTP server implementation loaded").fillInStackTrace()));
    }
    { StringWrapper path = null;
      PropertyList options = null;
      DictionaryIterator iter000 = ((DictionaryIterator)(Http.$HTTP_HANDLER_REGISTRY$.allocateIterator()));

      while (iter000.nextP()) {
        path = ((StringWrapper)(iter000.key));
        options = ((PropertyList)(iter000.value));
        { GeneralizedSymbol testValue000 = ((GeneralizedSymbol)(options.lookup(Http.KWD_HANDLER_TYPE)));

          if (testValue000 == Http.KWD_FILE) {
            Http.$HTTP_SERVER_IMPLEMENTATION$.publishFileImpl(path.wrapperValue, ((StringWrapper)(options.lookup(Http.KWD_FILE))).wrapperValue, options);
          }
          else if (testValue000 == Http.KWD_DIRECTORY) {
            Http.$HTTP_SERVER_IMPLEMENTATION$.publishDirectoryImpl(path.wrapperValue, ((StringWrapper)(options.lookup(Http.KWD_DIRECTORY))).wrapperValue, options);
          }
          else if (testValue000 == Http.KWD_HANDLER) {
            Http.$HTTP_SERVER_IMPLEMENTATION$.publishHandlerImpl(path.wrapperValue, ((FunctionCodeWrapper)(options.lookup(Http.KWD_HANDLER))).wrapperValue, options);
          }
          else {
            { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

              stream000.nativeStream.print("`" + testValue000 + "' is not a valid case option");
              throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
            }
          }
        }
      }
    }
  }

  public static void printRegisteredHttpHandlers() {
    {
      Stella.STANDARD_OUTPUT.nativeStream.println("Document root: " + Http.getHttpDocumentRoot());
      Stella.STANDARD_OUTPUT.nativeStream.println();
    }
;
    { Cons paths = Stella.NIL;

      { StringWrapper path = null;
        PropertyList options = null;
        DictionaryIterator iter000 = ((DictionaryIterator)(Http.$HTTP_HANDLER_REGISTRY$.allocateIterator()));

        while (iter000.nextP()) {
          path = ((StringWrapper)(iter000.key));
          options = ((PropertyList)(iter000.value));
          options = options;
          paths = Cons.cons(path, paths);
        }
      }
      paths = paths.sort(null);
      { Object old$PrintprettyP$000 = Stella.$PRINTPRETTYp$.get();
        Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();

        try {
          Native.setBooleanSpecial(Stella.$PRINTPRETTYp$, false);
          Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, true);
          { Stella_Object path = null;
            Cons iter001 = paths;

            for (;!(iter001 == Stella.NIL); iter001 = iter001.rest) {
              path = iter001.value;
              Stella.STANDARD_OUTPUT.nativeStream.println(StringWrapper.unwrapString(((StringWrapper)(path))) + " ->");
              { Stella_Object key = null;
                Stella_Object value = null;
                Cons iter002 = Http.$HTTP_SERVER_IMPLEMENTATION$.lookupHandler(((StringWrapper)(path)).wrapperValue).thePlist;

                for (;!(iter002 == Stella.NIL); iter002 = iter002.rest.rest) {
                  key = iter002.value;
                  value = iter002.rest.value;
                  Stella.STANDARD_OUTPUT.nativeStream.println("      " + key + " " + value);
                }
              }
            }
          }

        } finally {
          Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
          Stella.$PRINTPRETTYp$.set(old$PrintprettyP$000);
        }
      }
    }
  }

  /** Publish <code>path</code> to be served with <code>file</code> which must exist and be readable.
   * If :content-type is supplied, it will be used when serving <code>file</code>, otherwise, a content
   * type is guessed from <code>file</code>s extension.
   * @param path
   * @param file
   * @param options
   */
  public static void publishFile(String path, String file, Cons options) {
    file = Stella.translateLogicalPathname(file);
    Stella.ensureFileExists(file, "publish-file");
    { PropertyList theoptions = Stella_Object.vetOptions(options, Stella.getQuotedTree("((:CONTENT-TYPE :DOCUMENTATION) \"/HTTP\")", "/HTTP"));

      if (theoptions.lookup(Http.KWD_CONTENT_TYPE) == null) {
        theoptions.insertAt(Http.KWD_CONTENT_TYPE, StringWrapper.wrapString(Http.guessFileContentType(file)));
      }
      theoptions.insertAt(Http.KWD_HANDLER_TYPE, Http.KWD_FILE);
      theoptions.insertAt(Http.KWD_PATH, StringWrapper.wrapString(path));
      theoptions.insertAt(Http.KWD_FILE, StringWrapper.wrapString(file));
      Http.$HTTP_HANDLER_REGISTRY$.insertAt(StringWrapper.wrapString(path), theoptions);
    }
  }

  public static void publishFileEvaluatorWrapper(Cons arguments) {
    Http.publishFile(((StringWrapper)(arguments.value)).wrapperValue, ((StringWrapper)(arguments.rest.value)).wrapperValue, arguments.rest.rest);
  }

  /** Make all files descending from <code>directory</code> available on the server.
   * <code>path</code> will be coerced to end in a delimiter and <code>directory</code> must exist.
   * This is very rudimentary right now and does not provide any sophisticated access
   * control.  It recurses into subdirectories of <code>directory</code>, prevents escape via <code>DD</code>
   * and does not (yet) support directory listings.
   * @param path
   * @param directory
   * @param options
   */
  public static void publishDirectory(String path, String directory, Cons options) {
    directory = Stella.translateLogicalPathname(directory);
    directory = Stella.fileNameAsDirectory(directory);
    if (!(Stella.probeFileP(directory))) {
      Stella.STANDARD_WARNING.nativeStream.println("Warning: HTTP/publish-directory: `" + directory + "' does not exist");
    }
    if (!(Stella.endsWithP(path, "/", Stella.NULL_INTEGER))) {
      path = path + "/";
    }
    { PropertyList theoptions = Stella_Object.vetOptions(options, Stella.getQuotedTree("((:DOCUMENTATION) \"/HTTP\")", "/HTTP"));

      theoptions.insertAt(Http.KWD_HANDLER_TYPE, Http.KWD_DIRECTORY);
      theoptions.insertAt(Http.KWD_PATH, StringWrapper.wrapString(path));
      theoptions.insertAt(Http.KWD_DIRECTORY, StringWrapper.wrapString(directory));
      Http.$HTTP_HANDLER_REGISTRY$.insertAt(StringWrapper.wrapString(path), theoptions);
    }
  }

  public static void publishDirectoryEvaluatorWrapper(Cons arguments) {
    Http.publishDirectory(((StringWrapper)(arguments.value)).wrapperValue, ((StringWrapper)(arguments.rest.value)).wrapperValue, arguments.rest.rest);
  }

  /** Publish <code>path</code> to be handled by the handler function <code>handler</code> which must
   * take a single argument of type HTTP-EXCHANGE and use the API functions to read request
   * information and generate a result page.  If :content-type is supplied, it will be used as
   * the content type of the resulting page, otherwise, text/html will be used by default.
   * @param path
   * @param handler
   * @param options
   */
  public static void publishHandler(String path, java.lang.reflect.Method handler, Cons options) {
    { PropertyList theoptions = Stella_Object.vetOptions(options, Stella.getQuotedTree("((:CONTENT-TYPE :DOCUMENTATION) \"/HTTP\")", "/HTTP"));

      if (theoptions.lookup(Http.KWD_CONTENT_TYPE) == null) {
        theoptions.insertAt(Http.KWD_CONTENT_TYPE, StringWrapper.wrapString(Http.getHttpMimeType(Http.KWD_HTML, null)));
      }
      theoptions.insertAt(Http.KWD_HANDLER_TYPE, Http.KWD_HANDLER);
      theoptions.insertAt(Http.KWD_PATH, StringWrapper.wrapString(path));
      theoptions.insertAt(Http.KWD_HANDLER, FunctionCodeWrapper.wrapFunctionCode(handler));
      Http.$HTTP_HANDLER_REGISTRY$.insertAt(StringWrapper.wrapString(path), theoptions);
    }
  }

  public static void cleanupSessionTable() {
    Http.$SESSION_TABLE_CLEANUP_COUNTER$ = Http.$SESSION_TABLE_CLEANUP_COUNTER$ + 1;
    if (Stella.integer_mod(Http.$SESSION_TABLE_CLEANUP_COUNTER$, 100) == 0) {
      synchronized (Http.$SESSIONS_LOCK$) {
        { StringWrapper name = null;
          Session session = null;
          DictionaryIterator iter000 = ((DictionaryIterator)(Http.$SESSION_TABLE$.allocateIterator()));

          while (iter000.nextP()) {
            name = ((StringWrapper)(iter000.key));
            session = ((Session)(iter000.value));
            if (session.timedOutP()) {
              Http.$SESSION_TABLE$.removeAt(name);
            }
          }
        }
      }
    }
  }

  /** Retrieve an existing session object with <code>name</code> if it exists, NULL otherwise.
   * If a session was found but has timed out, raise an error if <code>errorIfTimeoutP</code> is true,
   * otherwise, return the timed-out session.  Bumps the timestamp on existing sessions that
   * haven't yet timed out.
   * @param name
   * @param erroriftimeoutP
   * @return Session
   */
  public static Session lookupSession(String name, boolean erroriftimeoutP) {
    { Session session = ((Session)(Http.$SESSION_TABLE$.lookup(StringWrapper.wrapString(name))));

      if (session != null) {
        if (session.timedOutP()) {
          if (erroriftimeoutP) {
            throw ((TimeoutException)(TimeoutException.newTimeoutException("lookup-session: session timed out: " + name).fillInStackTrace()));
          }
        }
        else {
          session.refresh();
        }
      }
      return (session);
    }
  }

  /** Create a new session object with <code>name</code> (replacing any existing
   * sessions with the same name).  If <code>name</code> is NULL, generate a random UUID for it.
   * Timeout after <code>timeout</code> seconds or never in case the value is &lt;= 0 or undefined.
   * @param name
   * @param timeout
   * @return Session
   */
  public static Session createSession(String name, int timeout) {
    { Session session = Session.newSession();

      if (name == null) {
        name = Stella.generateRandomUuid();
      }
      session.name = name;
      if (timeout > 0) {
        session.timeout = TimeDuration.makeTimeDuration(0, timeout * 1000);
      }
      synchronized (Http.$SESSIONS_LOCK$) {
        Http.$SESSION_TABLE$.insertAt(StringWrapper.wrapString(name), session);
      }
      Http.cleanupSessionTable();
      return (session);
    }
  }

  /** Retrieve an existing session object with <code>name</code> if it exists or create a new one.
   * If <code>name</code> is NULL, generate a random UUID for it.  If an existing object was found but has timed
   * out, raise an error if <code>errorIfTimeoutP</code> is true.  If a new object is created, initialize its
   * timeout field with <code>timeout</code> seconds (0 or undefined means no timeout).
   * @param name
   * @param erroriftimeoutP
   * @param timeout
   * @return Session
   */
  public static Session getSession(String name, boolean erroriftimeoutP, int timeout) {
    if (name == null) {
      return (Http.createSession(null, timeout));
    }
    else {
      { Session session = Http.lookupSession(name, erroriftimeoutP);

        if (session == null) {
          session = Http.createSession(name, timeout);
        }
        return (session);
      }
    }
  }

}
