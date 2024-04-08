//  -*- Mode: Java -*-
//
// Fetch.java

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

package edu.isi.webtools.examples.fetch;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.webtools.objects.xml_objects.*;
import edu.isi.stella.*;

public class Fetch {
  public static Surrogate SGT_FETCH_runAgentAndWaitForResponse = null;

  public static Symbol SYM_FETCH_arg0 = null;

  public static Symbol SYM_FETCH_arg1 = null;

  public static Symbol SYM_FETCH_arg2 = null;

  public static Surrogate SGT_FETCH_runAgentAndWaitForResponseResponse = null;

  public static Symbol SYM_FETCH_return = null;

  public static Surrogate SGT_FETCH_runAgentAndWaitForResponseReturn = null;

  public static String $FETCH_REQUEST1$ = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n <soapenv:Body>\n  <ns1:runAgentAndWaitForResponse soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:ns1=\"http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService/\">\n   <arg0 xsi:type=\"xsd:string\">eeld/gettygeonames/plans/production</arg0>     \n   <arg1 href=\"#id0\"/>\n   <arg2 href=\"#id1\"/>\n  </ns1:runAgentAndWaitForResponse>\n  <multiRef id=\"id0\" soapenc:root=\"0\" soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xsi:type=\"ns2:Map\" xmlns:soapenc=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:ns2=\"http://xml.apache.org/xml-soap\">\n   <item>\n    <key xsi:type=\"xsd:string\">keywords</key>		\n    <value xsi:type=\"xsd:string\">Marina Del Rey</value>\n   </item>\n  </multiRef>\n  <multiRef id=\"id1\" soapenc:root=\"0\" soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xsi:type=\"ns3:Map\" xmlns:ns3=\"http://xml.apache.org/xml-soap\" xmlns:soapenc=\"http://schemas.xmlsoap.org/soap/encoding/\"/>\n </soapenv:Body>\n</soapenv:Envelope>";

  public static String $FETCH_REQUEST2$ = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n <soapenv:Body>\n  <ns1:runAgentAndWaitForResponse soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:ns1=\"http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService/\">\n   <arg0 xsi:type=\"xsd:string\">eeld/gettygeonames/plans/production</arg0>     \n   <arg1>\n     <item>\n       <key xsi:type=\"xsd:string\">keywords</key>		\n       <value xsi:type=\"xsd:string\">Marina Del Rey</value>\n     </item>\n   </arg1>\n   <arg2/>\n  </ns1:runAgentAndWaitForResponse>\n </soapenv:Body>\n</soapenv:Envelope>";

  public static Symbol SYM_FETCH_STARTUP_FETCH_DEMO = null;

  public static void GET_FETCH_RESPONSE1() {
    { String url = "http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService";
      PropertyList headers = PropertyList.newPropertyList();
      String response = null;

      headers.insertAt(StringWrapper.wrapString("content-type"), StringWrapper.wrapString("text/xml; charset=utf-8"));
      headers.insertAt(StringWrapper.wrapString("SoapAction"), StringWrapper.wrapString(""));
      response = edu.isi.webtools.http.Http.doHttpRequest(url, Cons.cons(edu.isi.webtools.examples.addressexample.AddressExample.KWD_METHOD, Cons.cons(edu.isi.webtools.examples.addressexample.AddressExample.KWD_POST, Cons.cons(edu.isi.webtools.examples.addressexample.AddressExample.KWD_HEADERS, Cons.cons(headers, Cons.cons(edu.isi.webtools.examples.addressexample.AddressExample.KWD_CONTENT, Cons.cons(StringWrapper.wrapString(Fetch.$FETCH_REQUEST2$), Stella.NIL)))))));
      {
        Stella.STANDARD_OUTPUT.nativeStream.println("Response: ");
        Stella.STANDARD_OUTPUT.nativeStream.println(response);
      }
;
    }
  }

  public static void GET_FETCH_RESPONSE2() {
    { String url = "http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService";
      PropertyList headers = PropertyList.newPropertyList();
      String response = null;
      String request = Fetch.MAKE_FETCH_REQUEST1();

      headers.insertAt(StringWrapper.wrapString("content-type"), StringWrapper.wrapString("text/xml; charset=utf-8"));
      headers.insertAt(StringWrapper.wrapString("SoapAction"), StringWrapper.wrapString(""));
      response = edu.isi.webtools.http.Http.doHttpRequest(url, Cons.cons(edu.isi.webtools.examples.addressexample.AddressExample.KWD_METHOD, Cons.cons(edu.isi.webtools.examples.addressexample.AddressExample.KWD_POST, Cons.cons(edu.isi.webtools.examples.addressexample.AddressExample.KWD_HEADERS, Cons.cons(headers, Cons.cons(edu.isi.webtools.examples.addressexample.AddressExample.KWD_CONTENT, Cons.cons(StringWrapper.wrapString(request), Stella.NIL)))))));
      {
        Stella.STANDARD_OUTPUT.nativeStream.println("Response: ");
        Stella.STANDARD_OUTPUT.nativeStream.println(response);
      }
;
    }
  }

  public static void GET_FETCH_RESPONSE3() {
    { String url = "http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService";
      XMLObject requestObject = Fetch.MAKE_FETCH_REQUEST_OBJECT1();
      XMLObject responseObject = edu.isi.webtools.soap.Soap.callWebservice(requestObject, url);

      { Object OLD_$SUPRESS_NAMESPACESP$_000 = XmlObjects.$SUPRESS_NAMESPACESp$.get();

        try {
          Native.setBooleanSpecial(XmlObjects.$SUPRESS_NAMESPACESp$, true);
          {
            Stella.STANDARD_OUTPUT.nativeStream.println("Retrieved Result is: ");
            Stella.STANDARD_OUTPUT.nativeStream.println(responseObject.TO_XML_STRING());
          }
;

        } finally {
          XmlObjects.$SUPRESS_NAMESPACESp$.set(OLD_$SUPRESS_NAMESPACESP$_000);
        }
      }
    }
  }

  public static String MAKE_FETCH_REQUEST1() {
    { Object OLD_$SUPRESS_NAMESPACESP$_000 = XmlObjects.$SUPRESS_NAMESPACESp$.get();

      try {
        Native.setBooleanSpecial(XmlObjects.$SUPRESS_NAMESPACESp$, true);
        return (Fetch.MAKE_FETCH_REQUEST_OBJECT1().TO_XML_STRING());

      } finally {
        XmlObjects.$SUPRESS_NAMESPACESp$.set(OLD_$SUPRESS_NAMESPACESP$_000);
      }
    }
  }

  public static XMLObject MAKE_FETCH_REQUEST_OBJECT1() {
    { edu.isi.webtools.examples.fetchcontent.key SELF_000 = edu.isi.webtools.examples.fetchcontent.key.new_key();

      SELF_000.textContent = "keywords";
      { edu.isi.webtools.examples.fetchcontent.key key = SELF_000;

        { edu.isi.webtools.examples.fetchcontent.value SELF_001 = edu.isi.webtools.examples.fetchcontent.value.new_value();

          SELF_001.textContent = "Marina Del Rey";
          { edu.isi.webtools.examples.fetchcontent.value value = SELF_001;

            { edu.isi.webtools.examples.fetchcontent.item SELF_002 = edu.isi.webtools.examples.fetchcontent.item.new_item();

              SELF_002.key = key;
              SELF_002.val = value;
              { edu.isi.webtools.examples.fetchcontent.item item = SELF_002;

                { edu.isi.webtools.examples.fetchcontent.arg0 SELF_003 = edu.isi.webtools.examples.fetchcontent.arg0.new_arg0();

                  SELF_003.textContent = "eeld/gettygeonames/plans/production";
                  { edu.isi.webtools.examples.fetchcontent.arg0 arg0 = SELF_003;

                    { edu.isi.webtools.examples.fetchcontent.arg1 SELF_004 = edu.isi.webtools.examples.fetchcontent.arg1.new_arg1();

                      SELF_004.item = item;
                      { edu.isi.webtools.examples.fetchcontent.arg1 arg1 = SELF_004;
                        edu.isi.webtools.examples.fetchcontent.arg2 arg2 = edu.isi.webtools.examples.fetchcontent.arg2.new_arg2();

                        { runAgentAndWaitForResponse SELF_006 = runAgentAndWaitForResponse.new_runAgentAndWaitForResponse();

                          SELF_006.arg0 = arg0;
                          SELF_006.arg1 = arg1;
                          SELF_006.arg2 = arg2;
                          { runAgentAndWaitForResponse runAgentAndWaitForResponse = SELF_006;

                            return (runAgentAndWaitForResponse);
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

}
