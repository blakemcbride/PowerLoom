//  -*- Mode: Java -*-
//
// HttpServerTomcat.java

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

public class HttpServerTomcat extends HttpServer {
  public static HttpServerTomcat newHttpServerTomcat() {
    { HttpServerTomcat self = null;

      self = new HttpServerTomcat();
      return (self);
    }
  }

  public HttpExchangeTomcat servletHandleRequest(javax.servlet.http.HttpServletRequest request, javax.servlet.http.HttpServletResponse response) {
    { HttpServerTomcat server = this;

      { HttpExchangeTomcat self000 = HttpExchangeTomcat.newHttpExchangeTomcat();

        self000.nativeRequest = request;
        self000.nativeResponse = response;
        { HttpExchangeTomcat xchg = self000;
          String path = Stella.stringTrim(Stella.unescapeUrlString(server.getRequestUriPathImpl(xchg)));
          PropertyList handler = server.lookupHandler(path);
          int code = xchg.responseCode;

          if (handler == null) {
            handler = ((PropertyList)(AbstractDictionary.dictionary(Tomcat.SGT_STELLA_PROPERTY_LIST, Cons.cons(Tomcat.KWD_PATH, Cons.cons(StringWrapper.wrapString(path), Cons.cons(Tomcat.KWD_HANDLER_TYPE, Cons.cons(Tomcat.KWD_ERROR, Stella.NIL)))))));
          }
          xchg.handlerOptions = handler;
          { java.lang.reflect.Method function = FunctionCodeWrapper.unwrapFunctionCode(((FunctionCodeWrapper)(handler.lookup(Tomcat.KWD_HANDLER))));

            if (function == null) {
              { GeneralizedSymbol testValue000 = ((GeneralizedSymbol)(handler.lookup(Tomcat.KWD_HANDLER_TYPE)));

                if (testValue000 == Tomcat.KWD_FILE) {
                  function = Native.find_java_method("edu.isi.webtools.http.HttpExchange", "fileHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")});
                }
                else if (testValue000 == Tomcat.KWD_DIRECTORY) {
                  function = Native.find_java_method("edu.isi.webtools.http.HttpExchange", "directoryHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")});
                }
                else {
                  function = Native.find_java_method("edu.isi.webtools.http.HttpExchange", "unknownUrlHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")});
                }
              }
            }
            HttpExchange.setReplyHeaderValue(xchg, Tomcat.KWD_CONTENT_TYPE, ((StringWrapper)(handler.lookupWithDefault(Tomcat.KWD_CONTENT_TYPE, StringWrapper.wrapString(Http.getHttpMimeType(Tomcat.KWD_HTML, null))))).wrapperValue);
            edu.isi.stella.javalib.Native.funcall(function, null, new java.lang.Object [] {xchg});
            return (xchg);
          }
        }
      }
    }
  }

  public PropertyList getHandlerOptionsImpl(HttpExchange xchg) {
    { HttpServerTomcat server = this;

      { HttpExchangeTomcat jxchg = ((HttpExchangeTomcat)(xchg));

        return (jxchg.handlerOptions);
      }
    }
  }

  public void publishHandlerImpl(String path, java.lang.reflect.Method handler, PropertyList options) {
    { HttpServerTomcat server = this;

    }
  }

  public void publishDirectoryImpl(String path, String directory, PropertyList options) {
    { HttpServerTomcat server = this;

    }
  }

  public void publishFileImpl(String path, String file, PropertyList options) {
    { HttpServerTomcat server = this;

    }
  }

  public void setResponseCodeImpl(HttpExchange xchg, Keyword code) {
    { HttpServerTomcat server = this;

      { HttpExchangeTomcat jxchg = ((HttpExchangeTomcat)(xchg));

        jxchg.responseCode = Http.getHttpResponseCode(code, null);
      }
    }
  }

  public edu.isi.stella.javalib.NativeOutputStream getReplyStreamImpl(HttpExchange xchg) {
    { HttpServerTomcat server = this;

      { HttpExchangeTomcat jxchg = ((HttpExchangeTomcat)(xchg));
        edu.isi.stella.javalib.NativeOutputStream jstream = jxchg.replyStream;

        if (jstream == null) {
          jstream = edu.isi.stella.javalib.NativeStringOutputStream.create();
          jxchg.replyStream = jstream;
        }
        return (jstream);
      }
    }
  }

  public String getRequestRemoteAddressImpl(HttpExchange xchg) {
    { HttpServerTomcat server = this;

      { javax.servlet.http.HttpServletRequest jreq = ((HttpExchangeTomcat)(xchg)).nativeRequest;
        String host = jreq.getRemoteHost();
        int port = jreq.getRemotePort();

        return (host + ":" + Native.integerToString(((long)(port))));
      }
    }
  }

  public String getRequestLocalAddressImpl(HttpExchange xchg) {
    { HttpServerTomcat server = this;

      { javax.servlet.http.HttpServletRequest jreq = ((HttpExchangeTomcat)(xchg)).nativeRequest;
        String host = jreq.getLocalName();
        int port = jreq.getLocalPort();

        return (host + ":" + Native.integerToString(((long)(port))));
      }
    }
  }

  public String getRequestBodyImpl(HttpExchange xchg) {
    { HttpServerTomcat server = this;

      { javax.servlet.http.HttpServletRequest jreq = ((HttpExchangeTomcat)(xchg)).nativeRequest;

        { InputStream self000 = InputStream.newInputStream();

          self000.bufferingScheme = Tomcat.KWD_BLOCK;
          { InputStream bodystream = self000;
            edu.isi.stella.javalib.NativeInputStream body = null;

            try {
         body = new edu.isi.stella.javalib.NativeInputStream(jreq.getInputStream());
       }
       catch (java.io.IOException e) {
         Native.rethrowAsStellaException(e, InputOutputException.class, "getRequestBodyImpl: ", true);
       }
;
            bodystream.nativeStream = body;
            return (bodystream.streamToString());
          }
        }
      }
    }
  }

  public String getRequestProtocolImpl(HttpExchange xchg) {
    { HttpServerTomcat server = this;

      throw ((StellaException)(StellaException.newStellaException("get-request-protocol: not available for a Tomcat server").fillInStackTrace()));
    }
  }

  public Keyword getRequestMethodImpl(HttpExchange xchg) {
    { HttpServerTomcat server = this;

      { javax.servlet.http.HttpServletRequest jreq = ((HttpExchangeTomcat)(xchg)).nativeRequest;

        return (Stella.internKeyword(jreq.getMethod()));
      }
    }
  }

  public String getRequestUriPathImpl(HttpExchange xchg) {
    { HttpServerTomcat server = this;

      { javax.servlet.http.HttpServletRequest jreq = ((HttpExchangeTomcat)(xchg)).nativeRequest;

        return (jreq.getRequestURI());
      }
    }
  }

  public String getRequestUriQueryImpl(HttpExchange xchg) {
    { HttpServerTomcat server = this;

      { javax.servlet.http.HttpServletRequest jreq = ((HttpExchangeTomcat)(xchg)).nativeRequest;

        return (jreq.getQueryString());
      }
    }
  }

  public String getRequestUriImpl(HttpExchange xchg) {
    { HttpServerTomcat server = this;

      { javax.servlet.http.HttpServletRequest jreq = ((HttpExchangeTomcat)(xchg)).nativeRequest;
        String uri = jreq.getRequestURI();
        String query = jreq.getQueryString();

        return (((query != null) ? (uri + "?" + query) : uri));
      }
    }
  }

  public void setReplyHeaderValueImpl(HttpExchange xchg, Keyword key, String value) {
    { HttpServerTomcat server = this;

      { javax.servlet.http.HttpServletResponse jresp = ((HttpExchangeTomcat)(xchg)).nativeResponse;
        String jkey = key.symbolName;

        jresp.setHeader(jkey, value);
      }
    }
  }

  public String getReplyHeaderValueImpl(HttpExchange xchg, Keyword key) {
    { HttpServerTomcat server = this;

      throw ((StellaException)(StellaException.newStellaException("get-reply-header-value: not available for a Tomcat server").fillInStackTrace()));
    }
  }

  public String getHeaderValueImpl(HttpExchange xchg, Keyword key) {
    { HttpServerTomcat server = this;

      { javax.servlet.http.HttpServletRequest jreq = ((HttpExchangeTomcat)(xchg)).nativeRequest;
        String jkey = key.symbolName;

        return (jreq.getHeader(jkey));
      }
    }
  }

  public void stopHttpServerImpl() {
    { HttpServerTomcat server = this;

    }
  }

  public String startHttpServerImpl(int port) {
    { HttpServerTomcat server = this;

      Stella.STANDARD_OUTPUT.nativeStream.print("start-http-server: you cannot start/stop or change the port on which Tomcat listens");
      return ("http://localhost:8080/");
    }
  }

  public Surrogate primaryType() {
    { HttpServerTomcat self = this;

      return (Tomcat.SGT_TOMCAT_HTTP_SERVER_TOMCAT);
    }
  }

}

