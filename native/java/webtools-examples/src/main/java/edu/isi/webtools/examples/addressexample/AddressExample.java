//  -*- Mode: Java -*-
//
// AddressExample.java

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

package edu.isi.webtools.examples.addressexample;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.webtools.objects.xml_objects.*;
import edu.isi.stella.*;

public class AddressExample {
  public static Surrogate SGT_ADDRESS_EXAMPLE_getAddressFromName = null;

  public static Symbol SYM_ADDRESS_EXAMPLE_nameElement = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_return = null;

  public static Symbol SYM_ADDRESS_EXAMPLE_streetNum = null;

  public static Symbol SYM_ADDRESS_EXAMPLE_streetName = null;

  public static Symbol SYM_ADDRESS_EXAMPLE_city = null;

  public static Symbol SYM_ADDRESS_EXAMPLE_state = null;

  public static Symbol SYM_ADDRESS_EXAMPLE_zip = null;

  public static Symbol SYM_ADDRESS_EXAMPLE_phone = null;

  public static Symbol SYM_XSI_type = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_getAddressFromNameResponse = null;

  public static Symbol SYM_ADDRESS_EXAMPLE_return = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_nameToLookup = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_Address = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_StreetNum = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_StreetName = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_City = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_State = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_Zip = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_PhoneNumber = null;

  public static Symbol SYM_ADDRESS_EXAMPLE_areaCode = null;

  public static Symbol SYM_ADDRESS_EXAMPLE_exchange = null;

  public static Symbol SYM_ADDRESS_EXAMPLE_number = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_AreaCode = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_Exchange = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_Number = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_streetNum = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_streetName = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_city = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_state = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_zip = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_phoneNumber = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_areaCode = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_exchange = null;

  public static Surrogate SGT_ADDRESS_EXAMPLE_number = null;

  public static Keyword KWD_METHOD = null;

  public static Keyword KWD_POST = null;

  public static Keyword KWD_CONTENT = null;

  public static Keyword KWD_HEADERS = null;

  public static Surrogate SGT_SOAP_ENV_Fault = null;

  public static String $ADDRESS_REQUEST$ = "<?xml version='1.0' encoding='UTF-8'?>\n<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">\n<SOAP-ENV:Body>\n<ns1:getAddressFromName xmlns:ns1=\"urn:AddressFetcher\" SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">\n<ns1:nameToLookup xsi:type=\"xsd:string\">John B. Good</ns1:nameToLookup>\n</ns1:getAddressFromName>\n</SOAP-ENV:Body>\n</SOAP-ENV:Envelope>\n";

  public static Symbol SYM_ADDRESS_EXAMPLE_STARTUP_ADDRESS_EXAMPLE = null;

  public static getAddressFromName MAKE_REQUEST_OBJECT1() {
    { nameToLookup SELF_000 = nameToLookup.new_nameToLookup();

      SELF_000.textContent = "John B. Good";
      { nameToLookup nameToLookup = SELF_000;

        { getAddressFromName SELF_001 = getAddressFromName.new_getAddressFromName();

          SELF_001.nameElement = nameToLookup;
          { getAddressFromName requestObject = SELF_001;

            nameToLookup.type = "XSD:string";
            return (requestObject);
          }
        }
      }
    }
  }

  public static void ADDRESS_TEST1() {
    { OutputStringStream result = OutputStringStream.newOutputStringStream();

      edu.isi.webtools.soap.Soap.processSoapRpcRequest(AddressExample.$ADDRESS_REQUEST$, false, result);
      {
        Stella.STANDARD_OUTPUT.nativeStream.println("Retrieved envelope is: ");
        Stella.STANDARD_OUTPUT.nativeStream.print(XmlObjects.FROM_XML_STRING(result.theStringReader()).TO_XML_STRING());
      }
;
    }
  }

  public static void ADDRESS_TEST2() {
    { String resultString = edu.isi.webtools.http.Http.doHttpRequest("http://localhost:8012/ploom/soap-rpc", Cons.cons(AddressExample.KWD_METHOD, Cons.cons(AddressExample.KWD_POST, Cons.cons(AddressExample.KWD_CONTENT, Cons.cons(StringWrapper.wrapString(AddressExample.$ADDRESS_REQUEST$), Stella.NIL)))));

      {
        Stella.STANDARD_OUTPUT.nativeStream.println("Retrieved envelope is: ");
        Stella.STANDARD_OUTPUT.nativeStream.print(resultString);
      }
;
    }
  }

  public static void GET_APACHE_RESPONSE1() {
    { String url = "http://localhost:8080/soap/servlet/rpcrouter";
      PropertyList headers = PropertyList.newPropertyList();
      String response = null;
      edu.isi.webtools.objects.soap_env.Envelope responseEnvelope = null;
      Address address = null;
      String addressString = null;

      headers.insertAt(StringWrapper.wrapString("content-type"), StringWrapper.wrapString("text/xml; charset=utf-8"));
      response = edu.isi.webtools.http.Http.doHttpRequest(url, Cons.cons(AddressExample.KWD_METHOD, Cons.cons(AddressExample.KWD_POST, Cons.cons(AddressExample.KWD_HEADERS, Cons.cons(headers, Cons.cons(AddressExample.KWD_CONTENT, Cons.cons(StringWrapper.wrapString(AddressExample.$ADDRESS_REQUEST$), Stella.NIL)))))));
      {
        Stella.STANDARD_OUTPUT.nativeStream.println("Response: ");
        Stella.STANDARD_OUTPUT.nativeStream.println(response);
      }
;
      responseEnvelope = ((edu.isi.webtools.objects.soap_env.Envelope)(XmlObjects.FROM_XML_STRING(response)));
      address = ((Address)(responseEnvelope.body.contents));
      { Object OLD_$SUPRESS_NAMESPACESP$_000 = XmlObjects.$SUPRESS_NAMESPACESp$.get();

        try {
          Native.setBooleanSpecial(XmlObjects.$SUPRESS_NAMESPACESp$, true);
          addressString = address.TO_XML_STRING();
          {
            Stella.STANDARD_OUTPUT.nativeStream.println("Retrieved Address is: ");
            Stella.STANDARD_OUTPUT.nativeStream.print(addressString);
          }
;

        } finally {
          XmlObjects.$SUPRESS_NAMESPACESp$.set(OLD_$SUPRESS_NAMESPACESP$_000);
        }
      }
    }
  }

  public static void GET_APACHE_RESPONSE2() {
    { String url = "http://tubular.isi.edu:8080/soap/servlet/rpcrouter";
      getAddressFromName requestObject = AddressExample.MAKE_REQUEST_OBJECT1();
      XMLObject responseObject = edu.isi.webtools.soap.Soap.callWebservice(requestObject, url);

      { Object OLD_$SUPRESS_NAMESPACESP$_000 = XmlObjects.$SUPRESS_NAMESPACESp$.get();

        try {
          Native.setBooleanSpecial(XmlObjects.$SUPRESS_NAMESPACESp$, true);
          {
            Stella.STANDARD_OUTPUT.nativeStream.println("Retrieved Response object is: ");
            Stella.STANDARD_OUTPUT.nativeStream.println(responseObject.TO_XML_STRING());
            Stella.STANDARD_OUTPUT.nativeStream.println();
          }
;
          { Surrogate TEST_VALUE_000 = Stella_Object.safePrimaryType(responseObject);

            if (Surrogate.subtypeOfP(TEST_VALUE_000, AddressExample.SGT_ADDRESS_EXAMPLE_getAddressFromNameResponse)) {
              { getAddressFromNameResponse responseObject_000 = ((getAddressFromNameResponse)(responseObject));

                { String streetName = responseObject_000.renamed_Return.streetName.textContent;

                  Stella.STANDARD_OUTPUT.nativeStream.println("Retrieved Street Name is: " + streetName);
                }
              }
            }
            else if (Surrogate.subtypeOfP(TEST_VALUE_000, AddressExample.SGT_SOAP_ENV_Fault)) {
              { edu.isi.webtools.objects.soap_env.Fault responseObject_000 = ((edu.isi.webtools.objects.soap_env.Fault)(responseObject));

                { String code = responseObject_000.faultcode.textContent;
                  String string = responseObject_000.faultstring.textContent;
                  String actor = responseObject_000.faultactor.textContent;

                  Stella.STANDARD_OUTPUT.nativeStream.println("Received SOAP Fault:");
                  Stella.STANDARD_OUTPUT.nativeStream.println(" CODE   : " + code);
                  Stella.STANDARD_OUTPUT.nativeStream.println(" STRING : " + string);
                  Stella.STANDARD_OUTPUT.nativeStream.println(" ACTOR  : " + actor);
                }
              }
            }
            else {
              { OutputStringStream STREAM_000 = OutputStringStream.newOutputStringStream();

                STREAM_000.nativeStream.print("`" + TEST_VALUE_000 + "' is not a valid case option");
                throw ((StellaException)(StellaException.newStellaException(STREAM_000.theStringReader()).fillInStackTrace()));
              }
            }
          }

        } finally {
          XmlObjects.$SUPRESS_NAMESPACESp$.set(OLD_$SUPRESS_NAMESPACESP$_000);
        }
      }
    }
  }

}
