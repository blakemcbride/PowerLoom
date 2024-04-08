//  -*- Mode: Java -*-
//
// HttpServerSun.java

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
 | Portions created by the Initial Developer are Copyright (C) 2009-2023      |
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

package edu.isi.webtools.http.sun;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.stella.*;
import edu.isi.webtools.http.*;

public class HttpServerSun extends HttpServer {
    public com.sun.net.httpserver.HttpServer currentServer;
    public int currentServerPort;

  public static HttpServerSun newHttpServerSun() {
    { HttpServerSun self = null;

      self = new HttpServerSun();
      self.currentServerPort = Stella.NULL_INTEGER;
      self.currentServer = null;
      return (self);
    }
  }

  public PropertyList getHandlerOptionsImpl(HttpExchange xchg) {
    { HttpServerSun server = this;

      { HttpExchangeSun jxchg = ((HttpExchangeSun)(xchg));

        return (jxchg.handlerOptions);
      }
    }
  }

  public void publishHandlerImpl(String path, java.lang.reflect.Method handler, PropertyList options) {
    { HttpServerSun server = this;

      { String ctype = ((StringWrapper)(options.lookupWithDefault(Sun.KWD_CONTENT_TYPE, StringWrapper.wrapString(Http.getHttpMimeType(Sun.KWD_HTML, null))))).wrapperValue;
        com.sun.net.httpserver.HttpServer curserv = server.currentServer;

        if (curserv == null) {
          throw ((StellaException)(StellaException.newStellaException("publish-handler: no server instance is running").fillInStackTrace()));
        }
              GenericResponseHandler genHandler = new GenericResponseHandler();
       genHandler.setDefaultContentType(ctype);
       genHandler.setHandlerFunction(handler);
       genHandler.setHandlerOptions(options);
       curserv.createContext(path, genHandler)
;
      }
    }
  }

  public void publishDirectoryImpl(String path, String directory, PropertyList options) {
    { HttpServerSun server = this;

      server.publishHandlerImpl(path, Native.find_java_method("edu.isi.webtools.http.HttpExchange", "directoryHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")}), options);
    }
  }

  public void publishFileImpl(String path, String file, PropertyList options) {
    { HttpServerSun server = this;

      server.publishHandlerImpl(path, Native.find_java_method("edu.isi.webtools.http.HttpExchange", "fileHandler", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")}), options);
    }
  }

  public void setResponseCodeImpl(HttpExchange xchg, Keyword code) {
    { HttpServerSun server = this;

      { HttpExchangeSun jxchg = ((HttpExchangeSun)(xchg));

        jxchg.responseCode = Http.getHttpResponseCode(code, null);
      }
    }
  }

  public edu.isi.stella.javalib.NativeOutputStream getReplyStreamImpl(HttpExchange xchg) {
    { HttpServerSun server = this;

      { HttpExchangeSun jxchg = ((HttpExchangeSun)(xchg));
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
    { HttpServerSun server = this;

      { com.sun.net.httpserver.HttpExchange jxchg = ((HttpExchangeSun)(xchg)).nativeExchange;
        String host = jxchg.getRemoteAddress().getAddress().getHostName();
        int port = jxchg.getRemoteAddress().getPort();

        return (host + ":" + Native.integerToString(((long)(port))));
      }
    }
  }

  public String getRequestLocalAddressImpl(HttpExchange xchg) {
    { HttpServerSun server = this;

      { com.sun.net.httpserver.HttpExchange jxchg = ((HttpExchangeSun)(xchg)).nativeExchange;
        String host = jxchg.getLocalAddress().getAddress().getHostName();
        int port = jxchg.getLocalAddress().getPort();

        return (host + ":" + Native.integerToString(((long)(port))));
      }
    }
  }

  public String getRequestBodyImpl(HttpExchange xchg) {
    { HttpServerSun server = this;

      { com.sun.net.httpserver.HttpExchange jxchg = ((HttpExchangeSun)(xchg)).nativeExchange;

        { InputStream self000 = InputStream.newInputStream();

          self000.nativeStream = edu.isi.stella.javalib.NativeInputStream.create(jxchg.getRequestBody());
          self000.bufferingScheme = Sun.KWD_BLOCK;
          { InputStream bodystream = self000;

            return (bodystream.streamToString());
          }
        }
      }
    }
  }

  public String getRequestProtocolImpl(HttpExchange xchg) {
    { HttpServerSun server = this;

      { com.sun.net.httpserver.HttpExchange jxchg = ((HttpExchangeSun)(xchg)).nativeExchange;

        return (jxchg.getProtocol());
      }
    }
  }

  public Keyword getRequestMethodImpl(HttpExchange xchg) {
    { HttpServerSun server = this;

      { com.sun.net.httpserver.HttpExchange jxchg = ((HttpExchangeSun)(xchg)).nativeExchange;

        return (Stella.internKeyword(jxchg.getRequestMethod()));
      }
    }
  }

  public String getRequestUriPathImpl(HttpExchange xchg) {
    { HttpServerSun server = this;

      { com.sun.net.httpserver.HttpExchange jxchg = ((HttpExchangeSun)(xchg)).nativeExchange;

        return (jxchg.getRequestURI().getRawPath());
      }
    }
  }

  public String getRequestUriQueryImpl(HttpExchange xchg) {
    { HttpServerSun server = this;

      { com.sun.net.httpserver.HttpExchange jxchg = ((HttpExchangeSun)(xchg)).nativeExchange;

        return (jxchg.getRequestURI().getRawQuery());
      }
    }
  }

  public String getRequestUriImpl(HttpExchange xchg) {
    { HttpServerSun server = this;

      { com.sun.net.httpserver.HttpExchange jxchg = ((HttpExchangeSun)(xchg)).nativeExchange;

        return (jxchg.getRequestURI().toASCIIString());
      }
    }
  }

  public void setReplyHeaderValueImpl(HttpExchange xchg, Keyword key, String value) {
    { HttpServerSun server = this;

      { com.sun.net.httpserver.HttpExchange jxchg = ((HttpExchangeSun)(xchg)).nativeExchange;
        String jkey = key.symbolName;

        jxchg.getResponseHeaders().set(jkey, value);
      }
    }
  }

  public String getReplyHeaderValueImpl(HttpExchange xchg, Keyword key) {
    { HttpServerSun server = this;

      { com.sun.net.httpserver.HttpExchange jxchg = ((HttpExchangeSun)(xchg)).nativeExchange;
        String jkey = key.symbolName;

        return (jxchg.getResponseHeaders().getFirst(jkey));
      }
    }
  }

  public String getHeaderValueImpl(HttpExchange xchg, Keyword key) {
    { HttpServerSun server = this;

      { com.sun.net.httpserver.HttpExchange jxchg = ((HttpExchangeSun)(xchg)).nativeExchange;
        String jkey = key.symbolName;

        return (jxchg.getRequestHeaders().getFirst(jkey));
      }
    }
  }

  public void stopHttpServerImpl() {
    { HttpServerSun server = this;

      { com.sun.net.httpserver.HttpServer curserv = server.currentServer;

        if (!(curserv == null)) {
          curserv.stop(0);
        }
      }
    }
  }

  public String startHttpServerImpl(int port) {
    { HttpServerSun server = this;

      { com.sun.net.httpserver.HttpServer curserv = server.currentServer;

        if (!(curserv == null)) {
          curserv.stop(0);
        }
        try {
         curserv = com.sun.net.httpserver.HttpServer.create(new java.net.InetSocketAddress(port), 0);
       } catch (java.io.IOException e) {
         //rethrowAsStellaException(e, InputOutputException.class, "start-http-server: ", true)
         throw (InputOutputException)InputOutputException.newInputOutputException("start-http-server: " + e.getMessage()).fillInStackTrace();
       }
;
        curserv.setExecutor(null); // creates a default executor
       curserv.start()
;
        server.currentServer = curserv;
        server.currentServerPort = port;
        return (null);
      }
    }
  }

  public static Stella_Object accessHttpServerSunSlotValue(HttpServerSun self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == Sun.SYM_SUN_CURRENT_SERVER_PORT) {
      if (setvalueP) {
        self.currentServerPort = ((IntegerWrapper)(value)).wrapperValue;
      }
      else {
        value = IntegerWrapper.wrapInteger(self.currentServerPort);
      }
    }
    else {
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("`" + slotname + "' is not a valid case option");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
    return (value);
  }

  public Surrogate primaryType() {
    { HttpServerSun self = this;

      return (Sun.SGT_SUN_HTTP_SERVER_SUN);
    }
  }

}

