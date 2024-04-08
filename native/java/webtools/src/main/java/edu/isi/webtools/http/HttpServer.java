//  -*- Mode: Java -*-
//
// HttpServer.java

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

/** Abstract class that will be implemented by specific server implementations
 * and instantiated with a single instance used to dispatch all API methods.
 * @author Stella Java Translator
 */
public abstract class HttpServer extends StandardObject {
  public PropertyList getHandlerOptionsImpl(HttpExchange xchg) {
    { HttpServer server = this;

      xchg = xchg;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("get-handler-options-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public void publishHandlerImpl(String path, java.lang.reflect.Method handler, PropertyList options) {
    { HttpServer server = this;

      {
        path = path;
        handler = handler;
        options = options;
      }
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("publish-handler-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public void publishDirectoryImpl(String path, String directory, PropertyList options) {
    { HttpServer server = this;

      {
        path = path;
        directory = directory;
        options = options;
      }
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("publish-directory-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public void publishFileImpl(String path, String file, PropertyList options) {
    { HttpServer server = this;

      {
        path = path;
        file = file;
        options = options;
      }
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("publish-file-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Simple default handler lookup implementation.  Return the registered
   * handler whose path is identical to <code>path</code> or is the longest prefix of <code>path</code>.
   * @param path
   * @return PropertyList
   */
  public PropertyList lookupHandler(String path) {
    { HttpServer server = this;

      if (Http.$HTTP_SERVER_IMPLEMENTATION$ == null) {
        throw ((StellaException)(StellaException.newStellaException("lookup-handler: no HTTP server implementation loaded").fillInStackTrace()));
      }
      { PropertyList handler = ((PropertyList)(Http.$HTTP_HANDLER_REGISTRY$.lookup(StringWrapper.wrapString(path))));
        String handlerpath = null;
        int handlerpathlength = 0;

        if (handler != null) {
          return (handler);
        }
        { StringWrapper p = null;
          PropertyList h = null;
          DictionaryIterator iter000 = ((DictionaryIterator)(Http.$HTTP_HANDLER_REGISTRY$.allocateIterator()));

          while (iter000.nextP()) {
            p = ((StringWrapper)(iter000.key));
            h = ((PropertyList)(iter000.value));
            if (Stella.startsWithP(path, p.wrapperValue, 0)) {
              if ((handler == null) ||
                  ((StringWrapper.unwrapString(p)).length() > handlerpathlength)) {
                handler = h;
                handlerpath = p.wrapperValue;
                handlerpathlength = handlerpath.length();
              }
            }
          }
        }
        return (handler);
      }
    }
  }

  public void setResponseCodeImpl(HttpExchange xchg, Keyword code) {
    { HttpServer server = this;

      {
        xchg = xchg;
        code = code;
      }
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("set-response-code-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public edu.isi.stella.javalib.NativeOutputStream getReplyStreamImpl(HttpExchange xchg) {
    { HttpServer server = this;

      xchg = xchg;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("get-reply-stream-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public String getRequestRemoteAddressImpl(HttpExchange xchg) {
    { HttpServer server = this;

      xchg = xchg;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("get-request-remote-address-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public String getRequestLocalAddressImpl(HttpExchange xchg) {
    { HttpServer server = this;

      xchg = xchg;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("get-request-local-address-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public String getRequestBodyImpl(HttpExchange xchg) {
    { HttpServer server = this;

      xchg = xchg;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("get-request-body-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public Keyword getRequestMethodImpl(HttpExchange xchg) {
    { HttpServer server = this;

      xchg = xchg;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("get-request-method-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public String getRequestUriPathImpl(HttpExchange xchg) {
    { HttpServer server = this;

      xchg = xchg;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("get-request-uri-path-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public String getRequestUriQueryImpl(HttpExchange xchg) {
    { HttpServer server = this;

      xchg = xchg;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("get-request-uri-query-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public String getRequestUriImpl(HttpExchange xchg) {
    { HttpServer server = this;

      xchg = xchg;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("get-request-uri-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public void setReplyHeaderValueImpl(HttpExchange xchg, Keyword key, String value) {
    { HttpServer server = this;

      {
        xchg = xchg;
        key = key;
        value = value;
      }
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("set-reply-header-value-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public String getHeaderValueImpl(HttpExchange xchg, Keyword key) {
    { HttpServer server = this;

      {
        xchg = xchg;
        key = key;
      }
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("get-header-value-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public void stopHttpServerImpl() {
    { HttpServer server = this;

      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("stop-http-server-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public String startHttpServerImpl(int port) {
    { HttpServer server = this;

      port = port;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("start-http-server-impl: not implemented on `" + server + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

}

