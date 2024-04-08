//  -*- Mode: Java -*-
//
// Plsoap.java

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
 | Portions created by the Initial Developer are Copyright (C) 2002-2023      |
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

package edu.isi.powerloom.server.plsoap;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.stella.*;
import edu.isi.powerloom.logic.*;
import edu.isi.webtools.objects.xml_objects.*;
import edu.isi.webtools.soap.*;
import edu.isi.powerloom.server.*;

public class Plsoap {
  public static boolean $SOAP_READ_ONLYp$ = false;

  public static Surrogate SGT_PLSOAP_module = null;

  public static Surrogate SGT_PLSOAP_nresults = null;

  public static Symbol SYM_XSI_type = null;

  public static Surrogate SGT_PLSOAP_pattern = null;

  public static Surrogate SGT_PLSOAP_options = null;

  public static Surrogate SGT_PLSOAP_SOAP_COMMAND = null;

  public static Symbol SYM_PLSOAP_TARGET_MODULE = null;

  public static Surrogate SGT_PLSOAP_command = null;

  public static Surrogate SGT_PLSOAP_assertion = null;

  public static Surrogate SGT_PLSOAP_retraction = null;

  public static Surrogate SGT_PLSOAP_ask = null;

  public static Symbol SYM_STELLA_OPTIONS = null;

  public static Surrogate SGT_PLSOAP_retrieval = null;

  public static Symbol SYM_PLSOAP_NRESULTS = null;

  public static Symbol SYM_PLSOAP_QUERY_PATTERN = null;

  public static Surrogate SGT_PLSOAP_query = null;

  public static Surrogate SGT_PLSOAP_result = null;

  public static Surrogate SGT_PLSOAP_answer = null;

  public static Symbol SYM_LOGIC_QUERY = null;

  public static Symbol SYM_STELLA_RESULT = null;

  public static Surrogate SGT_PLSOAP_item = null;

  public static Surrogate SGT_PLSOAP_proposition = null;

  public static Surrogate SGT_PLSOAP_tuple = null;

  public static Symbol SYM_STELLA_ITEM = null;

  public static Surrogate SGT_PLSOAP_tuples = null;

  public static Symbol SYM_PLSOAP_TUPLE = null;

  public static Surrogate SGT_PLSOAP_propositions = null;

  public static Symbol SYM_LOGIC_PROPOSITION = null;

  public static Surrogate SGT_PLSOAP_powerloomerror = null;

  public static Surrogate SGT_PLSOAP_stellaerror = null;

  public static Surrogate SGT_PLSOAP_nativeerror = null;

  public static Module $POWERLOOM_SOAP_MODULE$ = null;

  public static Keyword KWD_IGNORE_TYPE_VIOLATIONS = null;

  public static Keyword KWD_REALISTIC = null;

  public static Keyword KWD_METHOD = null;

  public static Keyword KWD_POST = null;

  public static Keyword KWD_HEADERS = null;

  public static Keyword KWD_CONTENT = null;

  public static Symbol SYM_PLSOAP_STARTUP_SOAP_SERVER = null;

  public static String powerloomProcessSoapRequest(String requestBody) {
    { XMLObject answer = null;
      XMLObject request = null;

      { Object old$DefaultXmlObjectModule$000 = XmlObjects.$DEFAULT_XML_OBJECT_MODULE$.get();

        try {
          Native.setSpecial(XmlObjects.$DEFAULT_XML_OBJECT_MODULE$, Plsoap.$POWERLOOM_SOAP_MODULE$);
          try {
            request = XmlObjects.FROM_XML_STRING(requestBody);
            answer = SoapCommand.processSoapEncodedCommand(((SoapCommand)(((edu.isi.webtools.objects.soap_env.Envelope)(request)).body.contents)));
          } catch (LogicException e) {
            answer = powerloomerror.new_powerloomerror();
            answer.SET_CONTENT(Stella.exceptionMessage(e));
            answer = Soap.createSoapFault("SOAP-ENV:Server", "PowerLoom error", null, answer);
          } catch (StellaException e) {
            answer = stellaerror.new_stellaerror();
            answer.SET_CONTENT(Stella.exceptionMessage(e));
            answer = Soap.createSoapFault("SOAP-ENV:Server", "PowerLoom error", null, answer);
          } catch (java.lang.Exception e) {
            answer = nativeerror.new_nativeerror();
            answer.SET_CONTENT(Stella.exceptionMessage(e));
            answer = Soap.createSoapFault("SOAP-ENV:Server", "PowerLoom error", null, answer);
          }
          return (Soap.createSoapEnvelope(answer).TO_XML_STRING());

        } finally {
          XmlObjects.$DEFAULT_XML_OBJECT_MODULE$.set(old$DefaultXmlObjectModule$000);
        }
      }
    }
  }

  /** WRITE ME
   * @param xchg
   */
  public static void powerloomSoapRequestHandler(edu.isi.webtools.http.HttpExchange xchg) {
    { String request = edu.isi.webtools.http.HttpExchange.getRequestBody(xchg);
      edu.isi.stella.javalib.NativeOutputStream reply = edu.isi.webtools.http.HttpExchange.getReplyStream(xchg);

      reply.print(Plsoap.powerloomProcessSoapRequest(request));
    }
  }

  public static String safeGetContent(XMLObject obj) {
    if (obj != null) {
      return (obj.GET_CONTENT());
    }
    else {
      return (null);
    }
  }

  public static XMLObject soapEncodeCommandResponse(Stella_Object obj) {
    { Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();
      Object old$Printmode$000 = Logic.$PRINTMODE$.get();

      try {
        Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, true);
        Native.setSpecial(Logic.$PRINTMODE$, Plsoap.KWD_REALISTIC);
        { result answer = result.new_result();

          answer.SET_CONTENT(Native.stringify(obj));
          return (answer);
        }

      } finally {
        Logic.$PRINTMODE$.set(old$Printmode$000);
        Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
      }
    }
  }

  public static XMLObject soapEncodeAssertResponse(edu.isi.powerloom.PlIterator iter) {
    { Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();
      Object old$Printmode$000 = Logic.$PRINTMODE$.get();

      try {
        Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, true);
        Native.setSpecial(Logic.$PRINTMODE$, Plsoap.KWD_REALISTIC);
        { propositions answer = propositions.new_propositions();
          List props = List.newList();
          proposition propForm = null;
          nresults count = nresults.new_nresults();
          int n = 0;

          { Proposition prop = null;
            edu.isi.powerloom.PlIterator iter000 = iter;

            while (iter000.nextP()) {
              prop = ((Proposition)(iter000.value));
              n = n + 1;
              propForm = proposition.new_proposition();
              propForm.SET_CONTENT(Native.stringify(prop));
              props.push(propForm);
            }
          }
          count.textContent = Native.integerToString(((long)(n)));
          count.type = "XSD:int";
          answer.nresults = count;
          answer.proposition = props.reverse();
          return (answer);
        }

      } finally {
        Logic.$PRINTMODE$.set(old$Printmode$000);
        Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
      }
    }
  }

  public static XMLObject soapEncodeSimpleAnswer(String queryString, TruthValue tv) {
    { Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();
      Object old$Printmode$000 = Logic.$PRINTMODE$.get();

      try {
        Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, true);
        Native.setSpecial(Logic.$PRINTMODE$, Plsoap.KWD_REALISTIC);
        { result self000 = result.new_result();

          self000.textContent = Native.stringify(tv);
          { result truthValue = self000;
            answer ans = answer.new_answer();

            { query self002 = query.new_query();

              self002.textContent = queryString;
              ans.query = self002;
            }
            ans.result = truthValue;
            return (ans);
          }
        }

      } finally {
        Logic.$PRINTMODE$.set(old$Printmode$000);
        Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
      }
    }
  }

  public static item soapEncodeItem(Stella_Object obj) {
    { item encodedItem = item.new_item();

      { Surrogate testValue000 = Stella_Object.safePrimaryType(obj);

        if (Surrogate.subtypeOfFloatP(testValue000)) {
          { FloatWrapper obj000 = ((FloatWrapper)(obj));

            encodedItem.textContent = Native.floatToString(FloatWrapper.unwrapFloat(obj000));
            encodedItem.type = "XSD:double";
          }
        }
        else if (Surrogate.subtypeOfIntegerP(testValue000)) {
          { IntegerWrapper obj000 = ((IntegerWrapper)(obj));

            encodedItem.textContent = Native.integerToString(((long)(IntegerWrapper.unwrapInteger(obj000))));
            encodedItem.type = "XSD:int";
          }
        }
        else if (Surrogate.subtypeOfStringP(testValue000)) {
          { StringWrapper obj000 = ((StringWrapper)(obj));

            encodedItem.cdataContent = StringWrapper.unwrapString(obj000);
            encodedItem.type = "XSD:string";
          }
        }
        else {
          encodedItem.SET_CONTENT(Native.stringify(obj));
        }
      }
      return (encodedItem);
    }
  }

  public static tuple soapEncodeTuple(Stella_Object obj) {
    { tuple result = tuple.new_tuple();
      List items = List.newList();
      nresults count = nresults.new_nresults();
      int n = 0;

      if (Stella_Object.safePrimaryType(obj) == edu.isi.powerloom.server.gui.GuiServer.SGT_STELLA_CONS) {
        { Cons obj000 = ((Cons)(obj));

          { Stella_Object i = null;
            Cons iter000 = obj000;

            for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
              i = iter000.value;
              n = n + 1;
              items.push(Plsoap.soapEncodeItem(i));
            }
          }
        }
      }
      else {
        n = 1;
        items.push(Plsoap.soapEncodeItem(obj));
      }
      count.textContent = Native.integerToString(((long)(n)));
      count.type = "XSD:int";
      result.nresults = count;
      result.item = items.reverse();
      return (result);
    }
  }

  public static XMLObject soapEncodeRetrievalAnswer(String queryString, QueryIterator iter) {
    { Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();
      Object old$Printmode$000 = Logic.$PRINTMODE$.get();

      try {
        Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, true);
        Native.setSpecial(Logic.$PRINTMODE$, Plsoap.KWD_REALISTIC);
        { tuples result = tuples.new_tuples();
          List tuples = List.newList();
          nresults count = nresults.new_nresults();
          query theQuery = query.new_query();
          pattern queryPattern = pattern.new_pattern();
          OutputStringStream ss = OutputStringStream.newOutputStringStream();
          boolean firstP = true;
          int n = 0;

          { PatternVariable var = null;
            Vector vector000 = iter.externalVariables;
            int index000 = 0;
            int length000 = vector000.length();

            for (;index000 < length000; index000 = index000 + 1) {
              var = ((PatternVariable)((vector000.theArray)[index000]));
              if (firstP) {
                {
                  ss.nativeStream.print("(" + var.skolemName);
                  firstP = false;
                }
              }
              else {
                ss.nativeStream.print(" " + var.skolemName);
              }
            }
          }
          ss.nativeStream.print(")");
          { Stella_Object answer = null;
            Cons iter000 = iter.consifyCurrentSolutions();

            for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
              answer = iter000.value;
              n = n + 1;
              tuples.push(Plsoap.soapEncodeTuple(answer));
            }
          }
          count.textContent = Native.integerToString(((long)(n)));
          count.type = "XSD:int";
          theQuery.textContent = queryString;
          queryPattern.textContent = ss.theStringReader();
          result.nresults = count;
          result.query = theQuery;
          result.queryPattern = queryPattern;
          result.tuple = tuples.reverse();
          return (result);
        }

      } finally {
        Logic.$PRINTMODE$.set(old$Printmode$000);
        Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
      }
    }
  }

  public static void buildAndSendRequest(String target, String type, String content) {
    { String req = Plsoap.createTestString(type, content);
      String res = edu.isi.webtools.http.Http.doHttpRequest("http://" + target + "/ploom/soap-rpc/powerloom-soap-service", Cons.cons(Plsoap.KWD_METHOD, Cons.cons(Plsoap.KWD_POST, Cons.cons(Plsoap.KWD_HEADERS, Cons.cons(Soap.makeSoapRpcRequestHeaders(), Cons.cons(Plsoap.KWD_CONTENT, Cons.cons(StringWrapper.wrapString(req), Stella.NIL)))))));
      InputStringStream rStream = InputStringStream.newInputStringStream(res);

      {
        Stella.STANDARD_OUTPUT.nativeStream.println("Sent");
        Stella.STANDARD_OUTPUT.nativeStream.println(req);
      }
;
      {
        Stella.STANDARD_OUTPUT.nativeStream.println("");
        Stella.STANDARD_OUTPUT.nativeStream.println();
        Stella.STANDARD_OUTPUT.nativeStream.println("Received");
      }
;
      { String line = null;
        LineIterator iter000 = InputStream.lines(rStream);

        while (iter000.nextP()) {
          line = iter000.value;
          Stella.STANDARD_OUTPUT.nativeStream.println(line);
        }
      }
      {
        Stella.STANDARD_OUTPUT.nativeStream.println("");
        Stella.STANDARD_OUTPUT.nativeStream.println();
      }
;
    }
  }

  public static String createTestString(String bodyTagName, String content) {
    return ("<?xml version='1.0' encoding='UTF-8'?>\n  <SOAP-ENV:Envelope xmlns:SOAP-ENV='http://schemas.xmlsoap.org/soap/envelope/' xmlns:xsd='http://www.w3.org/2001/XMLSchema' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns:enc='http://schemas.xmlsoap.org/soap/encoding/' xmlns:ns0='http://hello.org/wsdl' SOAP-ENV:encodingStyle='http://schemas.xmlsoap.org/soap/encoding/'>\n <SOAP-ENV:Body>\n <" + bodyTagName + " xmlns='http://www.isi.edu/powerloom/'" + ">" + content + "</" + bodyTagName + ">\n</SOAP-ENV:Body></SOAP-ENV:Envelope>");
  }

}
