//  -*- Mode: Java -*-
//
// Soap.java

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

public class Soap {
  public static Symbol SYM_SOAP_STARTUP_SOAP = null;

  /** 'envelope' is a string-representation of SOAP envelope containing an
   * RPC request.  This functions writes a SOAP envelope containing a service response to <code>stream</code>.
   * @param soapstring
   * @param supressnamespacesP
   * @param stream
   */
  public static void processSoapRpcRequest(String soapstring, boolean supressnamespacesP, OutputStream stream) {
    { edu.isi.webtools.objects.xml_objects.XMLObject soapobject = edu.isi.webtools.objects.xml_objects.XmlObjects.FROM_XML_STRING(soapstring);
      Envelope resultobject = Soap.dispatchRpcCall(((Envelope)(soapobject)));

      { Object old$SupressNamespacesP$000 = edu.isi.webtools.objects.xml_objects.XmlObjects.$SUPRESS_NAMESPACESp$.get();

        try {
          Native.setBooleanSpecial(edu.isi.webtools.objects.xml_objects.XmlObjects.$SUPRESS_NAMESPACESp$, supressnamespacesP);
          OutputStream.printXmlExpression(stream, resultobject.TO_XML(Stella.NIL), 0);

        } finally {
          edu.isi.webtools.objects.xml_objects.XmlObjects.$SUPRESS_NAMESPACESp$.set(old$SupressNamespacesP$000);
        }
      }
    }
  }

  public static Symbol getRpcMethod(Envelope envelope) {
    { edu.isi.webtools.objects.xml_objects.XMLObject contents = envelope.body.contents;
      Surrogate type = contents.primaryType();

      return (Symbol.internSymbolInModule(type.symbolName, ((Module)(type.homeContext)), true));
    }
  }

  public static Cons getRpcArguments(Envelope envelope) {
    { Cons result = Stella.NIL;
      edu.isi.webtools.objects.xml_objects.XMLObject contents = envelope.body.contents;

      { Slot slot = null;
        Cons iter000 = edu.isi.webtools.objects.xml_objects.XMLObject.GET_MAPPED_SLOTS(contents).theConsList;
        Cons collect000 = null;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          slot = ((Slot)(iter000.value));
          if (edu.isi.webtools.objects.xml_objects.XmlObjects.ELEMENT_SLOTP(slot)) {
            if (collect000 == null) {
              {
                collect000 = Cons.cons(edu.isi.webtools.objects.xml_objects.XMLObject.GET_OBJECT_SLOT_VALUE(contents, ((StorageSlot)(slot))), Stella.NIL);
                if (result == Stella.NIL) {
                  result = collect000;
                }
                else {
                  Cons.addConsToEndOfConsList(result, collect000);
                }
              }
            }
            else {
              {
                collect000.rest = Cons.cons(edu.isi.webtools.objects.xml_objects.XMLObject.GET_OBJECT_SLOT_VALUE(contents, ((StorageSlot)(slot))), Stella.NIL);
                collect000 = collect000.rest;
              }
            }
          }
        }
      }
      return (result);
    }
  }

  public static Envelope dispatchRpcCall(Envelope envelope) {
    { Symbol method = Soap.getRpcMethod(envelope);
      Cons arguments = Soap.getRpcArguments(envelope);
      Envelope result = Soap.dispatchCallWithMethodAndArgs(method, arguments);

      return (result);
    }
  }

  public static Envelope dispatchCallWithMethodAndArgs(Symbol methodname, Cons arguments) {
    { java.lang.reflect.Method function = Symbol.lookupFunction(methodname).functionCode;
      Stella_Object rawresult = Stella.apply(function, arguments);
      Envelope packagedresult = Soap.createSoapEnvelope(((edu.isi.webtools.objects.xml_objects.XMLObject)(rawresult)));

      return (packagedresult);
    }
  }

  public static Envelope createSoapEnvelope(edu.isi.webtools.objects.xml_objects.XMLObject contents) {
    { Body self000 = Body.new_Body();

      self000.contents = contents;
      { Body body = self000;

        { Envelope self001 = Envelope.new_Envelope();

          self001.body = body;
          { Envelope result = self001;

            return (result);
          }
        }
      }
    }
  }

  /** Create a SOAP Fault object.  <code>fcode</code> and <code>fstring</code> are required.
   * <code>factor</code> and <code>fdetail</code> are optional fields.  Fault code should be one of
   * &quot;SOAP-ENV:VersionMismatch&quot;, &quot;SOAP-ENV:MustUnderstand&quot; &quot;SOAP-ENV:Client&quot; or
   * &quot;SOAP-ENV:Server&quot;.  These may change to keywords in the future.
   * @param fcode
   * @param fstring
   * @param factor
   * @param fdetail
   * @return Fault
   */
  public static Fault createSoapFault(String fcode, String fstring, String factor, edu.isi.webtools.objects.xml_objects.XMLObject fdetail) {
    { Fault self000 = Fault.new_Fault();

      { FaultCode self001 = FaultCode.new_FaultCode();

        self001.textContent = fcode;
        self000.faultcode = self001;
      }
      { FaultString self002 = FaultString.new_FaultString();

        self002.textContent = fstring;
        self000.faultstring = self002;
      }
      { Fault fault = self000;

        if (factor != null) {
          { FaultActor self003 = FaultActor.new_FaultActor();

            self003.textContent = factor;
            fault.faultactor = self003;
          }
        }
        if (fdetail != null) {
          { Detail self004 = Detail.new_Detail();

            self004.contents = fdetail;
            fault.detail = self004;
          }
        }
        return (fault);
      }
    }
  }

  /** Handle a request encoded by a SOAP message envelope in the body of an HTTP POST
   * command, unpack the envelope, dispatch the request, and return the result as SOAP envelope.
   * @param xchg
   */
  public static void soapRpcRequestHandler(HttpExchange xchg) {
    { OutputStream self000 = OutputStream.newOutputStream();

      self000.nativeStream = HttpExchange.getReplyStream(xchg);
      { OutputStream reply = self000;

        Soap.processSoapRpcRequest(HttpExchange.getRequestBody(xchg), true, reply);
      }
    }
  }

  /** Package <code>callobject</code> into a SOAP envelope, send it to the webservice at <code>url</code>.
   * @param callobject
   * @param url
   * @return edu.isi.webtools.objects.xml_objects.XMLObject
   */
  public static edu.isi.webtools.objects.xml_objects.XMLObject callWebservice(edu.isi.webtools.objects.xml_objects.XMLObject callobject, String url) {
    { boolean debugP = true;
      Envelope requestenvelopeobject = Soap.createSoapEnvelope(callobject);
      String requeststring = requestenvelopeobject.TO_XML_STRING();
      KeyValueList headers = Soap.makeSoapRpcRequestHeaders();
      String responseenvelopestring = Http.doHttpRequest(url, Cons.cons(Http.KWD_METHOD, Cons.cons(Http.KWD_POST, Cons.cons(Http.KWD_HEADERS, Cons.cons(headers, Cons.cons(Http.KWD_CONTENT, Cons.cons(StringWrapper.wrapString(requeststring), Stella.NIL)))))));
      edu.isi.webtools.objects.xml_objects.XMLObject responseenvelopeobject = edu.isi.webtools.objects.xml_objects.XmlObjects.FROM_XML_STRING(responseenvelopestring);
      edu.isi.webtools.objects.xml_objects.XMLObject responseobject = ((Envelope)(responseenvelopeobject)).body.contents;

      if (debugP) {
        {
          Stella.STANDARD_OUTPUT.nativeStream.println("response received: ");
          Stella.STANDARD_OUTPUT.nativeStream.println(responseenvelopestring);
        }
;
      }
      return (responseobject);
    }
  }

  public static KeyValueList makeSoapRpcRequestHeaders() {
    { KeyValueList result = KeyValueList.newKeyValueList();

      result.insertAt(StringWrapper.wrapString("content-type"), StringWrapper.wrapString("text/xml; charset=utf-8"));
      result.insertAt(StringWrapper.wrapString("SoapAction"), StringWrapper.wrapString(""));
      return (result);
    }
  }

}
