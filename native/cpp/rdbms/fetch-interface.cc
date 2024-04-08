//  -*- Mode: C++ -*-

// fetch-interface.cc

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
 | Portions created by the Initial Developer are Copyright (C) 1997-2023      |
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

#include "rdbms/rdbms-system.hh"

namespace rdbms {
  using namespace stella;
  using namespace logic;

Object* runFetchQuery(const char* host, int port, const char* queryId, const char* taskId, const char* subtaskId, const char* database, const char* parameters) {
  // Runs a Fetch query specifying the parameters given.
  // Returns an object representing the returned XML-encoded answer from
  // the server.
  { 
    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, false);
    { OutputStringStream* url = newOutputStringStream();
      InputStream* reply = NULL;

      *(url->nativeStream) << "/agent/runner?plan=";
      writeHtmlEscapingUrlSpecialCharacters(url->nativeStream, queryId);
      *(url->nativeStream) << "&TaskID=";
      writeHtmlEscapingUrlSpecialCharacters(url->nativeStream, taskId);
      *(url->nativeStream) << "-";
      writeHtmlEscapingUrlSpecialCharacters(url->nativeStream, subtaskId);
      *(url->nativeStream) << "&Database=";
      writeHtmlEscapingUrlSpecialCharacters(url->nativeStream, database);
      *(url->nativeStream) << "&";
      *(url->nativeStream) << parameters;
      reply = ((InputStream*  (*) (const char*, int, const char*, Object*))autoload("HTTP/HTTP-GET-DATA", "webtools", SGT_FETCH_INTERFACE_RDBMS_RUN_FETCH_QUERY, true))(host, port, url->theStringReader(), ((Object*)(NULL)));
      { Object* exp = NULL;
        XmlExpressionIterator* iter000 = xmlExpressions(reply, NULL);

        for (; iter000->nextP(); ) {
          exp = iter000->value;
          if (isaP(exp, SGT_FETCH_INTERFACE_STELLA_CONS) &&
              isaP(((Cons*)(exp))->value, SGT_FETCH_INTERFACE_STELLA_XML_ELEMENT)) {
            { XmlElement* item000 = ((XmlElement*)(((Cons*)(exp))->value));

              if (stringEqlP(item000->name, "PlanExecution") &&
                  stringEqlP(item000->namespaceUri, NULL)) {
                return (exp);
              }
              else if (stringEqlP(item000->name, "Error") &&
                  stringEqlP(item000->namespaceUri, NULL)) {
                { OutputStringStream* stream000 = newOutputStringStream();

                  *(stream000->nativeStream) << "`" << ((StringWrapper*)(((Cons*)(exp))->rest->rest->value))->wrapperValue << "'";
                  throw *newStellaException(stream000->theStringReader());
                }
              }
              else {
              }
            }
          }
        }
      }
      throw *newStellaException("Fetch Query Error: No answer element found.");
    }
  }
}

const char* normalizeFetchQueryArguments(Proposition* proposition, Object* arguments, Cons*& _Return1, PropertyList*& _Return2) {
  if (!(stringP(arguments))) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "PARSING ERROR: " << "Fetch-EDB-query: illegal pattern arguments: " << "`" << arguments << "'" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_FETCH_INTERFACE_ERROR);
      }
      throw *newParsingError(stream000->theStringReader());
    }
  }
  { Object* args = readSExpressionFromString(((StringWrapper*)(arguments))->wrapperValue);
    Cons* cursor = NULL;
    const char* queryid = NULL;
    Cons* outputargs = NIL;
    Cons* parameters = NIL;
    Object* parametervalue = NULL;

    if (safePrimaryType(args) == SGT_FETCH_INTERFACE_STELLA_CONS) {
      { Object* args000 = args;
        Cons* args = ((Cons*)(args000));

        { boolean testValue000 = false;

          testValue000 = (consP(args->value) &&
              !((args->length()) % 2)) ||
              ((!consP(args->value)) &&
               ((args->length()) % 2));
          if (testValue000) {
            { boolean alwaysP000 = true;

              { Object* arg = NULL;
                Cons* iter000 = args->rest;

                for (; !(iter000 == NIL); iter000 = iter000->rest) {
                  arg = iter000->value;
                  if (!(!consP(arg))) {
                    alwaysP000 = false;
                    break;
                  }
                }
              }
              testValue000 = alwaysP000;
            }
          }
          if (!(testValue000)) {
            { OutputStringStream* stream001 = newOutputStringStream();

              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                *(stream001->nativeStream) << "PARSING ERROR: " << "Fetch-EDB-query: illegal pattern arguments: " << "`" << arguments << "'" << "." << std::endl;
                helpSignalPropositionError(stream001, KWD_FETCH_INTERFACE_ERROR);
              }
              throw *newParsingError(stream001->theStringReader());
            }
          }
        }
        cursor = args;
        if (consP(cursor->value)) {
          { Object* outarg = NULL;
            Cons* iter001 = ((Cons*)(cursor->value));
            Cons* collect000 = NULL;

            for  (; !(iter001 == NIL); 
                  iter001 = iter001->rest) {
              outarg = iter001->value;
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(wrapString(coerceToString(outarg)), NIL);
                  if (outputargs == NIL) {
                    outputargs = collect000;
                  }
                  else {
                    addConsToEndOfConsList(outputargs, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(wrapString(coerceToString(outarg)), NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
          cursor = cursor->rest;
        }
        else {
          outputargs = getTableColumnNames(getDescription(((Surrogate*)(proposition->operatoR))));
          if (!((boolean)(outputargs))) {
            { OutputStringStream* stream002 = newOutputStringStream();

              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                *(stream002->nativeStream) << "PARSING ERROR: " << "Fetch-EDB-query: missing output arg/column specifications for: " << "`" << getDescription(((Surrogate*)(proposition->operatoR))) << "'" << "." << std::endl;
                helpSignalPropositionError(stream002, KWD_FETCH_INTERFACE_ERROR);
              }
              throw *newParsingError(stream002->theStringReader());
            }
          }
        }
        queryid = coerceToString(cursor->value);
        cursor = cursor->rest;
        parameters = cursor;
        while (!(cursor == NIL)) {
          cursor->firstSetter(wrapString(coerceToString(cursor->value)));
          parametervalue = cursor->rest->value;
          if (questionMarkSymbolP(parametervalue)) {
            { Object* value000 = NULL;

              { Object* arg = NULL;
                Vector* vector000 = proposition->arguments;
                int index000 = 0;
                int length000 = vector000->length();
                Symbol* var = NULL;
                Cons* iter002 = getDescription(((Surrogate*)(proposition->operatoR)))->ioVariableNames->theConsList;

                for  (; (index000 < length000) &&
                          (!(iter002 == NIL)); 
                      index000 = index000 + 1,
                      iter002 = iter002->rest) {
                  arg = (vector000->theArray)[index000];
                  var = ((Symbol*)(iter002->value));
                  if (var == parametervalue) {
                    value000 = arg;
                    break;
                  }
                }
              }
              parametervalue = value000;
            }
            if (!((boolean)(parametervalue))) {
              { OutputStringStream* stream003 = newOutputStringStream();

                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  *(stream003->nativeStream) << "PARSING ERROR: " << "Fetch-EDB-query: non-existent input variable: " << "`" << cursor->rest->value << "'" << "." << std::endl;
                  helpSignalPropositionError(stream003, KWD_FETCH_INTERFACE_ERROR);
                }
                throw *newParsingError(stream003->theStringReader());
              }
            }
            cursor->rest->firstSetter(parametervalue);
          }
          else {
            cursor->rest->firstSetter(wrapString(coerceToString(parametervalue)));
          }
          cursor = cursor->rest->rest;
        }
      }
    }
    else {
      { OutputStringStream* stream004 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream004->nativeStream) << "PARSING ERROR: " << "Fetch-EDB-query: illegal pattern arguments: " << "`" << arguments << "'" << "." << std::endl;
          helpSignalPropositionError(stream004, KWD_FETCH_INTERFACE_ERROR);
        }
        throw *newParsingError(stream004->theStringReader());
      }
    }
    { PropertyList* self010 = newPropertyList();

      self010->thePlist = parameters;
      { PropertyList* value001 = self010;

        _Return1 = outputargs;
        _Return2 = value001;
        return (queryid);
      }
    }
  }
}

Iterator* helpMemoizeFetchEdbQuery(Proposition* proposition, LogicObject* database, Object* arguments) {
  { const char* queryid = NULL;
    Cons* outputargs = NIL;
    PropertyList* parameters = NULL;
    NamedDescription* relation = getDescription(((Surrogate*)(proposition->operatoR)));
    OutputStringStream* params = newOutputStringStream();

    queryid = normalizeFetchQueryArguments(proposition, arguments, outputargs, parameters);
    { Object* key = NULL;
      Object* value = NULL;
      Cons* iter000 = parameters->thePlist;
      int i = NULL_INTEGER;
      int iter001 = 1;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest->rest,
            iter001 = iter001 + 1) {
        key = iter000->value;
        value = iter000->rest->value;
        i = iter001;
        if ((!((boolean)(key))) ||
            (!((boolean)(value)))) {
          return (NULL);
        }
        if (i > 1) {
          *(params->nativeStream) << "&";
        }
        *(params->nativeStream) << unwrapString(((StringWrapper*)(key)));
        value = argumentBoundTo(value);
        if (!((boolean)(value))) {
          return (NULL);
        }
        *(params->nativeStream) << "=" << coercePowerloomObjectToString(value, NULL);
      }
    }
    { const char* temp000 = unwrapString(((StringWrapper*)(accessBinaryValue(database, SGT_FETCH_INTERFACE_RDBMS_HOST))));

      { int temp001 = unwrapInteger(((IntegerWrapper*)(accessBinaryValue(database, SGT_FETCH_INTERFACE_RDBMS_PORT))));

        { const char* temp002 = unwrapString(((StringWrapper*)(accessBinaryValue(database, SGT_FETCH_INTERFACE_RDBMS_TASK_ID))));

          { const char* temp003 = unwrapString(((StringWrapper*)(accessBinaryValue(database, SGT_FETCH_INTERFACE_RDBMS_SUBTASK_ID))));

            { const char* temp004 = unwrapString(((StringWrapper*)(accessBinaryValue(database, SGT_FETCH_INTERFACE_RDBMS_DB_NAME))));

              { ConsIterator* value000 = parseFetchXmlAnswer(((Cons*)(runFetchQuery(((temp000 != NULL) ? temp000 : "pegasus2.isi.edu"), ((temp001 != NULL_INTEGER) ? temp001 : 8080), queryid, ((temp002 != NULL) ? temp002 : "TASK"), ((temp003 != NULL) ? temp003 : "SUBTASK"), ((temp004 != NULL) ? temp004 : "EELD-DATABASE"), params->theStringReader()))), relation, outputargs)->allocateIterator();

                return (value000);
              }
            }
          }
        }
      }
    }
  }
}

Iterator* fetchEdbQuery(Proposition* proposition, LogicObject* database, Object* arguments) {
  checkForExternalDbUpdates(proposition, database);
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_FETCH_INTERFACE_RDBMS_F_FETCH_EDB_QUERY_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_FETCH_INTERFACE_RDBMS_F_FETCH_EDB_QUERY_MEMO_TABLE_000, "(:MAX-VALUES 10000 :TIMESTAMPS (:META-KB-UPDATE :EXTERNAL-DB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_FETCH_INTERFACE_RDBMS_F_FETCH_EDB_QUERY_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), getQueryPatternMemoizationKey(proposition), oCONTEXTo, (oREVERSEPOLARITYpo ? TRUE_WRAPPER : FALSE_WRAPPER), MEMOIZED_NULL_VALUE, 6);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = newMemoizableIterator(helpMemoizeFetchEdbQuery(proposition, database, arguments));
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { Iterator* value000 = cloneMemoizedIterator(((MemoizableIterator*)(memoizedValue000)));

      return (((Iterator*)(value000)));
    }
  }
}

Cons* parseFetchXmlAnswer(Cons* xmlanswer, NamedDescription* relation, Cons* outputcolumns) {
  { Cons* tuples = NIL;

    if (!(isaP(xmlanswer->value, SGT_FETCH_INTERFACE_STELLA_XML_ELEMENT) &&
        (stringEqlP(((XmlElement*)(xmlanswer->value))->name, "PlanExecution") &&
         stringEqlP(((XmlElement*)(xmlanswer->value))->namespaceUri, NULL)))) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Fetch-EDB-query Error: Didn't find a Fetch Answer in " << "`" << xmlanswer << "'" << std::endl;
      return (NIL);
    }
    { Object* answer = NULL;
      Cons* iter000 = xmlanswer->rest->rest;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        answer = iter000->value;
        if (isaP(answer, SGT_FETCH_INTERFACE_STELLA_CONS) &&
            isaP(((Cons*)(answer))->value, SGT_FETCH_INTERFACE_STELLA_XML_ELEMENT)) {
          { XmlElement* item000 = ((XmlElement*)(((Cons*)(answer))->value));

            if (stringEqlP(item000->name, "OBJECT") &&
                stringEqlP(item000->namespaceUri, NULL)) {
              tuples = cons(parseOneFetchXmlObject(((Cons*)(answer))->rest->rest, relation, outputcolumns), tuples);
            }
            else if (stringEqlP(item000->name, "Error") &&
                stringEqlP(item000->namespaceUri, NULL)) {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "`" << unwrapString(((StringWrapper*)(((Cons*)(answer))->rest->rest->value))) << "'";
                throw *newStellaException(stream000->theStringReader());
              }
            }
            else if (stringEqlP(item000->name, "ERROR") &&
                stringEqlP(item000->namespaceUri, NULL)) {
              { OutputStringStream* stream001 = newOutputStringStream();

                *(stream001->nativeStream) << "`" << unwrapString(((StringWrapper*)(((Cons*)(answer))->rest->rest->value))) << "'";
                throw *newStellaException(stream001->theStringReader());
              }
            }
          }
        }
      }
    }
    return (tuples->reverse());
  }
}

Cons* parseOneFetchXmlObject(Cons* object, NamedDescription* relation, Cons* outputcolumns) {
  { Cons* tuple = NIL;

    { StringWrapper* column = NULL;
      Cons* iter000 = outputcolumns;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        column = ((StringWrapper*)(iter000->value));
        { Object* item = NULL;
          Cons* iter001 = object;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            item = iter001->value;
            if (eqlToStringP(column, ((XmlElement*)(((Cons*)(item))->value))->name)) {
              tuple = cons(((Cons*)(item))->rest->rest->value, tuple);
              if (!(((Cons*)(item))->rest->rest->rest == NIL)) {
                *(STANDARD_WARNING->nativeStream) << "Warning: " << "Extra elements found in " << "`" << item << "'" << std::endl;
              }
            }
          }
        }
      }
    }
    tuple = tuple->reverse();
    return (coerceValues(tuple, getRelationTableInfo(relation)));
  }
}

void startFetchEdbGateway(int port) {
  { const char* lispforms = "#+:aserve\n    (CL:progn\n      (CL:defun handle-fetch-query (request entity)\n        (net.aserve:with-http-response (request entity)\n          (net.aserve:with-http-body (request entity)\n            (CL:case (net.aserve:request-method request)\n              (:get\n               (CL:let ((query (net.aserve:request-query request\n                                                         :uri CL:t\n                                                         :post CL:nil))\n                        (keys (stella::new-key-value-list)))\n                 (CL:loop for (key . value) in query\n                     do (stella::insert-at\n                         keys\n                         (stella::wrap-string (CL:string key))\n                         (stella::wrap-string value)))\n                 (evaluate-fetch-query\n                  keys (net.aserve:request-reply-stream request))))\n              (CL:t\n               (CL:format (net.aserve:request-reply-stream request) \n                          \"Error o" "ccurred:<BR>~%Unhandled request method ~S\"\n                          (net.aserve:request-method request)))))))\n      (CL:defun start-fetch-EDB-servlet (port)\n        (CL:compile 'handle-fetch-query)\n        (net.aserve:publish :path \"/ploom/fetch-EDB-query\"\n                            :content-type \"text/html\"\n                            :function 'handle-fetch-query)\n        (net.aserve:start :port port)))\n    #-:aserve ()";

  }
}

void evaluateFetchQuery(KeyValueList* keys, std::ostream* out) {
  try {
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, NULL);
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, NULL);
      { Module* temp001 = getStellaModule("EELD-EDB", false);

        { Module* temp000 = (((boolean)(temp001)) ? temp001 : oMODULEo);

          oMODULEo = (((boolean)(temp000)) ? temp000 : oMODULEo);
        }
      }
      oCONTEXTo = oMODULEo;
      // Should be synchronized on process lock oPOWERLOOM_LOCKo
      {
        { Object* secondarydbname = keys->lookup(wrapString("sdatabase"));
          Object* fetchdb = get(((StringWrapper*)(copyConsTree(wrapString("fetch-edb")))), NIL);
          Object* taskid = keys->lookup(wrapString("task"));
          Object* subtaskid = keys->lookup(wrapString("subtask"));
          Object* command = keys->lookup(wrapString("command"));
          Object* result = NULL;

          { OutputStream* self000 = newOutputStream();

            self000->nativeStream = out;
            { OutputStream* wrappedout = self000;

              if (((boolean)(fetchdb))) {
                if (((boolean)(secondarydbname))) {
                  pli::assertNaryProposition(cons(getRelation(SGT_FETCH_INTERFACE_RDBMS_DB_NAME), cons(fetchdb, cons(secondarydbname, NIL))), NULL, NULL);
                }
                if (((boolean)(taskid))) {
                  pli::assertNaryProposition(cons(getRelation(SGT_FETCH_INTERFACE_RDBMS_TASK_ID), cons(fetchdb, cons(taskid, NIL))), NULL, NULL);
                }
                if (((boolean)(subtaskid))) {
                  pli::assertNaryProposition(cons(getRelation(SGT_FETCH_INTERFACE_RDBMS_SUBTASK_ID), cons(fetchdb, cons(subtaskid, NIL))), NULL, NULL);
                }
              }
              result = evaluateLogicCommand(readSExpressionFromString(((StringWrapper*)(command))->wrapperValue), true);
              if (subtypeOfP(safePrimaryType(result), SGT_FETCH_INTERFACE_LOGIC_QUERY_ITERATOR)) {
                { Object* result000 = result;
                  QueryIterator* result = ((QueryIterator*)(result000));

                  { QuerySolution* solution = NULL;
                    DictionaryIterator* iter000 = ((DictionaryIterator*)(result->solutions->allocateIterator()));

                    for (; iter000->nextP(); ) {
                      solution = ((QuerySolution*)(iter000->value));
                      { Object* elt = NULL;
                        Vector* vector000 = solution->bindings;
                        int index000 = 0;
                        int length000 = vector000->length();
                        int i = NULL_INTEGER;
                        int iter001 = 0;

                        for  (; index000 < length000; 
                              index000 = index000 + 1,
                              iter001 = iter001 + 1) {
                          elt = (vector000->theArray)[index000];
                          i = iter001;
                          if (i > 0) {
                            *(out) << " ";
                          }
                          printLogicalForm(elt, wrappedout);
                        }
                      }
                      *(out) << "<br>";
                    }
                  }
                }
              }
              else {
                writeHtmlQuotingSpecialCharacters(out, stringify(result));
              }
            }
          }
        }
      }
    }
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    *(out) << "ERROR: " << exceptionMessage(e);
  }
}

Cons* buildOneTableAssertion(NamedDescription* tableRelation, Cons* tuple, Module* dbModule) {
  { Cons* assertion = NIL;
    int colno = -1;

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = tableRelation->arity();
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;
      Cons* collect000 = NULL;

      for  (; unboundedP000 ||
                (iter000 <= upperBound000); 
            iter000 = iter000 + 1) {
        i = iter000;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(NULL_STRING_WRAPPER, NIL);
            if (assertion == NIL) {
              assertion = collect000;
            }
            else {
              addConsToEndOfConsList(assertion, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(NULL_STRING_WRAPPER, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    { Object* item = NULL;
      Cons* iter001 = tuple;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        item = iter001->value;
        colno = getTableColumnIndex(tableRelation, ((XmlElement*)(((Cons*)(item))->value))->name, dbModule);
        if (colno < 0) {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "Couldn't find column number for " << "`" << item << "'" << " on relation " << "`" << tableRelation << "'" << std::endl;
        }
        else {
          assertion->nthSetter(((Cons*)(item))->rest->rest->value, colno);
        }
        if (!(((Cons*)(item))->rest->rest->rest == NIL)) {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "Extra elements found in " << "`" << item << "'" << std::endl;
        }
      }
    }
    { Object* item = NULL;
      Cons* iter002 = assertion->rest;

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        item = iter002->value;
        if (unwrapString(((StringWrapper*)(item))) == NULL) {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "Some table relation values not set: " << "`" << assertion << "'" << std::endl;
          break;
        }
      }
    }
    assertion->rest = coerceValues(((Cons*)(assertion->rest)), getRelationTableInfo(tableRelation));
    assertion->nthSetter(tableRelation, 0);
    return (assertion);
  }
}

Cons* generateTableAssertions(const char* tableName, Cons* xmlAnswer, Module* module, Module* dbModule) {
  // Takes a Stella-parsed, XML-encoded `xml-answer' from Fetch based on
  // the database table `table-name' and uses it to generate an assertion
  // for an appropriate relation for inclusion in `module'.  The database
  // meta information is found in `db-module'.
  { NamedDescription* tableRelation = getTableRelation(tableName, dbModule);
    Cons* assertions = NIL;

    if (!(isaP(xmlAnswer->value, SGT_FETCH_INTERFACE_STELLA_XML_ELEMENT) &&
        (stringEqlP(((XmlElement*)(xmlAnswer->value))->name, "PlanExecution") &&
         stringEqlP(((XmlElement*)(xmlAnswer->value))->namespaceUri, NULL)))) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Didn't find a Fetch Answer in " << "`" << xmlAnswer << "'" << std::endl;
      return (NIL);
    }
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, module);
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      { Object* answer = NULL;
        Cons* iter000 = xmlAnswer->rest->rest;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          answer = iter000->value;
          if (isaP(answer, SGT_FETCH_INTERFACE_STELLA_CONS) &&
              isaP(((Cons*)(answer))->value, SGT_FETCH_INTERFACE_STELLA_XML_ELEMENT)) {
            { XmlElement* item000 = ((XmlElement*)(((Cons*)(answer))->value));

              if (stringEqlP(item000->name, "OBJECT") &&
                  stringEqlP(item000->namespaceUri, NULL)) {
                assertions = cons(buildOneTableAssertion(tableRelation, ((Cons*)(answer))->rest->rest, dbModule), assertions);
              }
              else if (stringEqlP(item000->name, "Error") &&
                  stringEqlP(item000->namespaceUri, NULL)) {
                { OutputStringStream* stream000 = newOutputStringStream();

                  *(stream000->nativeStream) << "`" << ((StringWrapper*)(((Cons*)(answer))->rest->rest->value))->wrapperValue << "'";
                  throw *newStellaException(stream000->theStringReader());
                }
              }
              else if (stringEqlP(item000->name, "ERROR") &&
                  stringEqlP(item000->namespaceUri, NULL)) {
                { OutputStringStream* stream001 = newOutputStringStream();

                  *(stream001->nativeStream) << "`" << ((StringWrapper*)(((Cons*)(answer))->rest->rest->value))->wrapperValue << "'";
                  throw *newStellaException(stream001->theStringReader());
                }
              }
            }
          }
        }
      }
    }
    return (assertions);
  }
}

const char* lookupStringValue(NamedDescription* relation, LogicObject* instance, Module* mod) {
  { pli::PlIterator* iter = pli::retrieve(listO(3, wrapInteger(1), cons(objectName(relation), cons(instance, cons(SYM_FETCH_INTERFACE_LOGIC_pX, NIL))), NIL), mod, NULL);

    if (iter->nextP()) {
      return (((StringWrapper*)(iter->value))->wrapperValue);
    }
    else {
      return (NULL);
    }
  }
}

Cons* fetchQueryAssertions(const char* host, int port, LogicObject* fetchQuery, const char* taskId, const char* subtaskId, const char* database, const char* parameterValue, Module* targetModule, Module* dbModule) {
  // Runs a `fetch-query' using `task-id'; `subtask-id',`database'
  // and specifying a single additional `parameter-value'.  The connection
  // is made to a remote http query server running on `host' port number `port'.
  // Returns a set of assertions for `target-module' using the information in `db-module'
  // to find the appropriate relations.
  { const char* dbTable = lookupStringValue(((NamedDescription*)(pli::getRelation("QUERY-TABLE-NAME", dbModule, NULL))), fetchQuery, dbModule);
    const char* parameterName = lookupStringValue(((NamedDescription*)(pli::getRelation("QUERY-PARAMETER-NAME", dbModule, NULL))), fetchQuery, dbModule);
    Object* fetchAnswer = runFetchQuery(host, port, objectName(fetchQuery)->symbolName, taskId, subtaskId, database, stringConcatenate(parameterName, "=", 1, parameterValue));

    return (generateTableAssertions(dbTable, ((Cons*)(fetchAnswer)), targetModule, dbModule));
  }
}

void startupFetchInterface() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/RDBMS", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SGT_FETCH_INTERFACE_RDBMS_RUN_FETCH_QUERY = ((Surrogate*)(internRigidSymbolWrtModule("RUN-FETCH-QUERY", NULL, 1)));
      SGT_FETCH_INTERFACE_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
      SGT_FETCH_INTERFACE_STELLA_XML_ELEMENT = ((Surrogate*)(internRigidSymbolWrtModule("XML-ELEMENT", getStellaModule("/STELLA", true), 1)));
      KWD_FETCH_INTERFACE_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
      SGT_FETCH_INTERFACE_RDBMS_HOST = ((Surrogate*)(internRigidSymbolWrtModule("HOST", NULL, 1)));
      SGT_FETCH_INTERFACE_RDBMS_PORT = ((Surrogate*)(internRigidSymbolWrtModule("PORT", NULL, 1)));
      SGT_FETCH_INTERFACE_RDBMS_TASK_ID = ((Surrogate*)(internRigidSymbolWrtModule("TASK-ID", NULL, 1)));
      SGT_FETCH_INTERFACE_RDBMS_SUBTASK_ID = ((Surrogate*)(internRigidSymbolWrtModule("SUBTASK-ID", NULL, 1)));
      SGT_FETCH_INTERFACE_RDBMS_DB_NAME = ((Surrogate*)(internRigidSymbolWrtModule("DB-NAME", NULL, 1)));
      SGT_FETCH_INTERFACE_RDBMS_F_FETCH_EDB_QUERY_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-FETCH-EDB-QUERY-MEMO-TABLE-000", NULL, 1)));
      SGT_FETCH_INTERFACE_LOGIC_QUERY_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("QUERY-ITERATOR", getStellaModule("/LOGIC", true), 1)));
      SYM_FETCH_INTERFACE_LOGIC_pX = ((Symbol*)(internRigidSymbolWrtModule("?X", getStellaModule("/LOGIC", true), 0)));
      SYM_FETCH_INTERFACE_RDBMS_STARTUP_FETCH_INTERFACE = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-FETCH-INTERFACE", NULL, 0)));
      SYM_FETCH_INTERFACE_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("RUN-FETCH-QUERY", "(DEFUN (RUN-FETCH-QUERY OBJECT) ((HOST STRING) (PORT INTEGER) (QUERY-ID STRING) (TASK-ID STRING) (SUBTASK-ID STRING) (DATABASE STRING) (PARAMETERS STRING)) :DOCUMENTATION \"Runs a Fetch query specifying the parameters given.\nReturns an object representing the returned XML-encoded answer from\nthe server.\" :PUBLIC? TRUE)", ((cpp_function_code)(&runFetchQuery)), NULL);
      defineFunctionObject("NORMALIZE-FETCH-QUERY-ARGUMENTS", "(DEFUN (NORMALIZE-FETCH-QUERY-ARGUMENTS STRING (CONS OF STRING-WRAPPER) PROPERTY-LIST) ((PROPOSITION PROPOSITION) (ARGUMENTS OBJECT)))", ((cpp_function_code)(&normalizeFetchQueryArguments)), NULL);
      defineFunctionObject("HELP-MEMOIZE-FETCH-EDB-QUERY", "(DEFUN (HELP-MEMOIZE-FETCH-EDB-QUERY (ITERATOR OF CONS)) ((PROPOSITION PROPOSITION) (DATABASE LOGIC-OBJECT) (ARGUMENTS OBJECT)))", ((cpp_function_code)(&helpMemoizeFetchEdbQuery)), NULL);
      defineFunctionObject("FETCH-EDB-QUERY", "(DEFUN (FETCH-EDB-QUERY (ITERATOR OF CONS)) ((PROPOSITION PROPOSITION) (DATABASE LOGIC-OBJECT) (ARGUMENTS OBJECT)))", ((cpp_function_code)(&fetchEdbQuery)), NULL);
      defineFunctionObject("PARSE-FETCH-XML-ANSWER", "(DEFUN (PARSE-FETCH-XML-ANSWER (CONS OF CONS)) ((XMLANSWER CONS) (RELATION NAMED-DESCRIPTION) (OUTPUTCOLUMNS (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&parseFetchXmlAnswer)), NULL);
      defineFunctionObject("PARSE-ONE-FETCH-XML-OBJECT", "(DEFUN (PARSE-ONE-FETCH-XML-OBJECT CONS) ((OBJECT CONS) (RELATION NAMED-DESCRIPTION) (OUTPUTCOLUMNS (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&parseOneFetchXmlObject)), NULL);
      defineFunctionObject("START-FETCH-EDB-GATEWAY", "(DEFUN START-FETCH-EDB-GATEWAY ((PORT INTEGER)))", ((cpp_function_code)(&startFetchEdbGateway)), NULL);
      defineFunctionObject("EVALUATE-FETCH-QUERY", "(DEFUN EVALUATE-FETCH-QUERY ((KEYS KEY-VALUE-LIST) (OUT NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&evaluateFetchQuery)), NULL);
      defineFunctionObject("BUILD-ONE-TABLE-ASSERTION", "(DEFUN (BUILD-ONE-TABLE-ASSERTION CONS) ((TABLE-RELATION NAMED-DESCRIPTION) (TUPLE CONS) (DB-MODULE MODULE)))", ((cpp_function_code)(&buildOneTableAssertion)), NULL);
      defineFunctionObject("GENERATE-TABLE-ASSERTIONS", "(DEFUN (GENERATE-TABLE-ASSERTIONS (CONS OF CONS)) ((TABLE-NAME STRING) (XML-ANSWER CONS) (MODULE MODULE) (DB-MODULE MODULE)) :DOCUMENTATION \"Takes a Stella-parsed, XML-encoded `xml-answer' from Fetch based on\nthe database table `table-name' and uses it to generate an assertion\nfor an appropriate relation for inclusion in `module'.  The database\nmeta information is found in `db-module'.\")", ((cpp_function_code)(&generateTableAssertions)), NULL);
      defineFunctionObject("LOOKUP-STRING-VALUE", "(DEFUN (LOOKUP-STRING-VALUE STRING) ((RELATION NAMED-DESCRIPTION) (INSTANCE LOGIC-OBJECT) (MOD MODULE)))", ((cpp_function_code)(&lookupStringValue)), NULL);
      defineFunctionObject("FETCH-QUERY-ASSERTIONS", "(DEFUN (FETCH-QUERY-ASSERTIONS (CONS OF CONS)) ((HOST STRING) (PORT INTEGER) (FETCH-QUERY LOGIC-OBJECT) (TASK-ID STRING) (SUBTASK-ID STRING) (DATABASE STRING) (PARAMETER-VALUE STRING) (TARGET-MODULE MODULE) (DB-MODULE MODULE)) :PUBLIC? TRUE :DOCUMENTATION \"Runs a `fetch-query' using `task-id'; `subtask-id',`database'\nand specifying a single additional `parameter-value'.  The connection\nis made to a remote http query server running on `host' port number `port'.\nReturns a set of assertions for `target-module' using the information in `db-module'\nto find the appropriate relations.\")", ((cpp_function_code)(&fetchQueryAssertions)), NULL);
      defineFunctionObject("STARTUP-FETCH-INTERFACE", "(DEFUN STARTUP-FETCH-INTERFACE () :PUBLIC? TRUE)", ((cpp_function_code)(&startupFetchInterface)), NULL);
      { MethodSlot* function = lookupFunction(SYM_FETCH_INTERFACE_RDBMS_STARTUP_FETCH_INTERFACE);

        setDynamicSlotValue(function->dynamicSlots, SYM_FETCH_INTERFACE_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupFetchInterface"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("RDBMS")))));
    }
  }
}

Surrogate* SGT_FETCH_INTERFACE_RDBMS_RUN_FETCH_QUERY = NULL;

Surrogate* SGT_FETCH_INTERFACE_STELLA_CONS = NULL;

Surrogate* SGT_FETCH_INTERFACE_STELLA_XML_ELEMENT = NULL;

Keyword* KWD_FETCH_INTERFACE_ERROR = NULL;

Surrogate* SGT_FETCH_INTERFACE_RDBMS_HOST = NULL;

Surrogate* SGT_FETCH_INTERFACE_RDBMS_PORT = NULL;

Surrogate* SGT_FETCH_INTERFACE_RDBMS_TASK_ID = NULL;

Surrogate* SGT_FETCH_INTERFACE_RDBMS_SUBTASK_ID = NULL;

Surrogate* SGT_FETCH_INTERFACE_RDBMS_DB_NAME = NULL;

Surrogate* SGT_FETCH_INTERFACE_RDBMS_F_FETCH_EDB_QUERY_MEMO_TABLE_000 = NULL;

Surrogate* SGT_FETCH_INTERFACE_LOGIC_QUERY_ITERATOR = NULL;

Symbol* SYM_FETCH_INTERFACE_LOGIC_pX = NULL;

Symbol* SYM_FETCH_INTERFACE_RDBMS_STARTUP_FETCH_INTERFACE = NULL;

Symbol* SYM_FETCH_INTERFACE_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace rdbms
