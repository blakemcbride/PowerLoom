//  -*- Mode: Java -*-
//
// SoapCommand.java

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

/** Common parent in type hierarchy.  This will
 * not actually be realized in surface syntax.
 * @author Stella Java Translator
 */
public class SoapCommand extends XMLObject {
    public module targetModule;

  public static SoapCommand newSoapCommand() {
    { SoapCommand self = null;

      self = new SoapCommand();
      self.cdataContent = null;
      self.textContent = null;
      self.targetModule = null;
      return (self);
    }
  }

  public static XMLObject processSoapEncodedCommand(SoapCommand commandForm) {
    { String moduleName = Plsoap.safeGetContent(commandForm.targetModule);
      Module module = null;

      SoapCommand.checkReadOnly(commandForm);
      if (moduleName == null) {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("No module specified. `" + commandForm + "'");
          throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
      module = edu.isi.powerloom.PLI.getModule(moduleName, null);
      if (module == null) {
        { OutputStringStream stream001 = OutputStringStream.newOutputStringStream();

          stream001.nativeStream.print("No module named '`" + moduleName + "''.  `" + commandForm + "'");
          throw ((StellaException)(StellaException.newStellaException(stream001.theStringReader()).fillInStackTrace()));
        }
      }
      { Object old$Typecheckmode$000 = Logic.$TYPECHECKMODE$.get();

        try {
          Native.setSpecial(Logic.$TYPECHECKMODE$, Plsoap.KWD_IGNORE_TYPE_VIOLATIONS);
          { Object old$Module$000 = Stella.$MODULE$.get();
            Object old$Context$000 = Stella.$CONTEXT$.get();

            try {
              Native.setSpecial(Stella.$MODULE$, edu.isi.powerloom.PLI.getModule(moduleName, null));
              Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
              { Surrogate testValue000 = Stella_Object.safePrimaryType(commandForm);

                if (Surrogate.subtypeOfP(testValue000, Plsoap.SGT_PLSOAP_command)) {
                  { command commandForm000 = ((command)(commandForm));

                    { String commandString = Plsoap.safeGetContent(commandForm000);

                      if ((commandString == null) ||
                          Stella.stringEqlP(commandString, "")) {
                        { OutputStringStream stream002 = OutputStringStream.newOutputStringStream();

                          stream002.nativeStream.print("Command was empty.`" + commandForm000 + "'");
                          throw ((StellaException)(StellaException.newStellaException(stream002.theStringReader()).fillInStackTrace()));
                        }
                      }
                      return (Plsoap.soapEncodeCommandResponse(edu.isi.powerloom.PLI.sEvaluate(commandString, moduleName, null)));
                    }
                  }
                }
                else if (Surrogate.subtypeOfP(testValue000, Plsoap.SGT_PLSOAP_assertion)) {
                  { assertion commandForm000 = ((assertion)(commandForm));

                    { String commandString = Plsoap.safeGetContent(commandForm000);

                      if ((commandString == null) ||
                          Stella.stringEqlP(commandString, "")) {
                        { OutputStringStream stream003 = OutputStringStream.newOutputStringStream();

                          stream003.nativeStream.print("Command was empty.`" + commandForm000 + "'");
                          throw ((StellaException)(StellaException.newStellaException(stream003.theStringReader()).fillInStackTrace()));
                        }
                      }
                      return (Plsoap.soapEncodeAssertResponse(edu.isi.powerloom.PLI.sAssertProposition(commandString, moduleName, null)));
                    }
                  }
                }
                else if (Surrogate.subtypeOfP(testValue000, Plsoap.SGT_PLSOAP_retraction)) {
                  { retraction commandForm000 = ((retraction)(commandForm));

                    { String commandString = Plsoap.safeGetContent(commandForm000);

                      if ((commandString == null) ||
                          Stella.stringEqlP(commandString, "")) {
                        { OutputStringStream stream004 = OutputStringStream.newOutputStringStream();

                          stream004.nativeStream.print("Command was empty.`" + commandForm000 + "'");
                          throw ((StellaException)(StellaException.newStellaException(stream004.theStringReader()).fillInStackTrace()));
                        }
                      }
                      return (Plsoap.soapEncodeAssertResponse(edu.isi.powerloom.PLI.sRetractProposition(commandString, moduleName, null)));
                    }
                  }
                }
                else if (Surrogate.subtypeOfP(testValue000, Plsoap.SGT_PLSOAP_ask)) {
                  { ask commandForm000 = ((ask)(commandForm));

                    { String baseQueryString = Plsoap.safeGetContent(commandForm000);
                      String queryString = baseQueryString;
                      String queryOptions = Plsoap.safeGetContent(commandForm000.options);

                      if ((queryString == null) ||
                          Stella.stringEqlP(queryString, "")) {
                        { OutputStringStream stream005 = OutputStringStream.newOutputStringStream();

                          stream005.nativeStream.print("Query was empty.`" + commandForm000 + "'");
                          throw ((StellaException)(StellaException.newStellaException(stream005.theStringReader()).fillInStackTrace()));
                        }
                      }
                      if (!((queryOptions == null) ||
                          Stella.stringEqlP(queryOptions, ""))) {
                        queryString = queryString + " " + queryOptions;
                      }
                      return (Plsoap.soapEncodeSimpleAnswer(queryString, edu.isi.powerloom.PLI.sAsk(baseQueryString, moduleName, null)));
                    }
                  }
                }
                else if (Surrogate.subtypeOfP(testValue000, Plsoap.SGT_PLSOAP_retrieval)) {
                  { retrieval commandForm000 = ((retrieval)(commandForm));

                    { String nResults = Plsoap.safeGetContent(commandForm000.nresults);
                      String queryPattern = Plsoap.safeGetContent(commandForm000.queryPattern);
                      String queryOptions = Plsoap.safeGetContent(commandForm000.options);
                      String baseQueryString = Plsoap.safeGetContent(commandForm000);
                      String queryString = baseQueryString;
                      Cons queryForm = Stella.NIL;

                      if ((queryString == null) ||
                          Stella.stringEqlP(queryString, "")) {
                        { OutputStringStream stream006 = OutputStringStream.newOutputStringStream();

                          stream006.nativeStream.print("Query was empty.`" + commandForm000 + "'");
                          throw ((StellaException)(StellaException.newStellaException(stream006.theStringReader()).fillInStackTrace()));
                        }
                      }
                      if (!((queryPattern == null) ||
                          Stella.stringEqlP(queryPattern, ""))) {
                        if (Native.string_position(queryPattern, '(', 0) != Stella.NULL_INTEGER) {
                          queryString = queryPattern + " " + queryString;
                        }
                        else {
                          queryString = "(" + queryPattern + ") " + queryString;
                        }
                      }
                      if ((nResults == null) ||
                          Stella.stringEqlP(nResults, "")) {
                        queryString = "/STELLA/ALL " + queryString;
                      }
                      else {
                        queryString = nResults + " " + queryString;
                      }
                      if (!((queryOptions == null) ||
                          Stella.stringEqlP(queryOptions, ""))) {
                        queryString = queryString + " " + queryOptions;
                      }
                      { Object old$Module$001 = Stella.$MODULE$.get();
                        Object old$Context$001 = Stella.$CONTEXT$.get();

                        try {
                          Native.setSpecial(Stella.$MODULE$, null);
                          Native.setSpecial(Stella.$CONTEXT$, null);
                          { Module temp000 = edu.isi.powerloom.PLI.getModule(moduleName, null);

                            Native.setSpecial(Stella.$MODULE$, ((temp000 != null) ? temp000 : ((Module)(Stella.$MODULE$.get()))));
                          }
                          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
                          synchronized (Logic.$POWERLOOM_LOCK$) {
                            { Stella_Object sexp = null;
                              SExpressionIterator iter000 = InputStream.sExpressions(InputStringStream.newInputStringStream(queryString));
                              Cons collect000 = null;

                              while (iter000.nextP()) {
                                sexp = iter000.value;
                                if (collect000 == null) {
                                  {
                                    collect000 = Cons.cons(sexp, Stella.NIL);
                                    if (queryForm == Stella.NIL) {
                                      queryForm = collect000;
                                    }
                                    else {
                                      Cons.addConsToEndOfConsList(queryForm, collect000);
                                    }
                                  }
                                }
                                else {
                                  {
                                    collect000.rest = Cons.cons(sexp, Stella.NIL);
                                    collect000 = collect000.rest;
                                  }
                                }
                              }
                            }
                            return (Plsoap.soapEncodeRetrievalAnswer(baseQueryString, Logic.callRetrieve(queryForm)));
                          }

                        } finally {
                          Stella.$CONTEXT$.set(old$Context$001);
                          Stella.$MODULE$.set(old$Module$001);
                        }
                      }
                    }
                  }
                }
                else {
                  { OutputStringStream stream007 = OutputStringStream.newOutputStringStream();

                    stream007.nativeStream.print("XML is not a recognized command: `" + commandForm + "'");
                    throw ((StellaException)(StellaException.newStellaException(stream007.theStringReader()).fillInStackTrace()));
                  }
                }
              }

            } finally {
              Stella.$CONTEXT$.set(old$Context$000);
              Stella.$MODULE$.set(old$Module$000);
            }
          }

        } finally {
          Logic.$TYPECHECKMODE$.set(old$Typecheckmode$000);
        }
      }
    }
  }

  public static void checkReadOnly(SoapCommand commandForm) {
    if (Plsoap.$SOAP_READ_ONLYp$) {
      { Surrogate testValue000 = Stella_Object.safePrimaryType(commandForm);

        if (Surrogate.subtypeOfP(testValue000, Plsoap.SGT_PLSOAP_ask)) {
          { ask commandForm000 = ((ask)(commandForm));

          }
        }
        else if (Surrogate.subtypeOfP(testValue000, Plsoap.SGT_PLSOAP_retrieval)) {
          { retrieval commandForm000 = ((retrieval)(commandForm));

          }
        }
        else {
          { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

            stream000.nativeStream.print("Command not supported in read-only mode.`" + commandForm + "'");
            throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
          }
        }
      }
    }
  }

  public static Stella_Object accessSoapCommandSlotValue(SoapCommand self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == Plsoap.SYM_PLSOAP_TARGET_MODULE) {
      if (setvalueP) {
        self.targetModule = ((module)(value));
      }
      else {
        value = self.targetModule;
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
    { SoapCommand self = this;

      return (Plsoap.SGT_PLSOAP_SOAP_COMMAND);
    }
  }

}

