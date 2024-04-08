//  -*- Mode: C++ -*-

// sdbc.cc

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
| Portions created by the Initial Developer are Copyright (C) 1996-2023      |
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

#include "sdbc/sdbc-system.hh"

namespace sdbc {
  using namespace stella;

Connection* newConnection() {
  { Connection* self = NULL;

    self = new Connection();
    self->renewalTime = NULL;
    self->lastAccessTime = NULL;
    self->creationTime = NULL;
    self->autoCommitP = true;
    self->statement = NULL;
    self->dbmsName = NULL;
    self->protocol = NULL;
    self->connectionString = NULL;
    self->nativeConnection = NULL;
    return (self);
  }
}

Surrogate* Connection::primaryType() {
  { Connection* self = this;

    return (SGT_SDBC_SDBC_CONNECTION);
  }
}

Object* accessConnectionSlotValue(Connection* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SDBC_SDBC_CONNECTION_STRING) {
    if (setvalueP) {
      self->connectionString = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->connectionString);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_PROTOCOL) {
    if (setvalueP) {
      self->protocol = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->protocol);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_DBMS_NAME) {
    if (setvalueP) {
      self->dbmsName = ((Keyword*)(value));
    }
    else {
      value = self->dbmsName;
    }
  }
  else if (slotname == SYM_SDBC_SDBC_STATEMENT) {
    if (setvalueP) {
      self->statement = ((PreparedStatement*)(value));
    }
    else {
      value = self->statement;
    }
  }
  else if (slotname == SYM_SDBC_SDBC_AUTO_COMMITp) {
    if (setvalueP) {
      self->autoCommitP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->autoCommitP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_CREATION_TIME) {
    if (setvalueP) {
      self->creationTime = ((CalendarDate*)(value));
    }
    else {
      value = self->creationTime;
    }
  }
  else if (slotname == SYM_SDBC_SDBC_LAST_ACCESS_TIME) {
    if (setvalueP) {
      self->lastAccessTime = ((CalendarDate*)(value));
    }
    else {
      value = self->lastAccessTime;
    }
  }
  else if (slotname == SYM_SDBC_SDBC_RENEWAL_TIME) {
    if (setvalueP) {
      self->renewalTime = ((CalendarDate*)(value));
    }
    else {
      value = self->renewalTime;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

void Connection::printObject(std::ostream* stream) {
  { Connection* self = this;

    *(stream) << "|CON|\"" << self->connectionString << "\"";
  }
}

PreparedStatement* newPreparedStatement() {
  { PreparedStatement* self = NULL;

    self = new PreparedStatement();
    self->parameters = newKeyValueList();
    self->sql = NULL;
    self->statement = NULL;
    self->connection = NULL;
    return (self);
  }
}

Surrogate* PreparedStatement::primaryType() {
  { PreparedStatement* self = this;

    return (SGT_SDBC_SDBC_PREPARED_STATEMENT);
  }
}

Object* accessPreparedStatementSlotValue(PreparedStatement* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SDBC_SDBC_CONNECTION) {
    if (setvalueP) {
      self->connection = ((Connection*)(value));
    }
    else {
      value = self->connection;
    }
  }
  else if (slotname == SYM_SDBC_SDBC_SQL) {
    if (setvalueP) {
      self->sql = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->sql);
    }
  }
  else if (slotname == SYM_SDBC_STELLA_PARAMETERS) {
    if (setvalueP) {
      self->parameters = ((KeyValueList*)(value));
    }
    else {
      value = self->parameters;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

DatabaseException* newDatabaseException(const char* message) {
  { DatabaseException* self = NULL;

    self = new DatabaseException(message);
    return (self);
  }
}

ResultSetIterator* newResultSetIterator() {
  { ResultSetIterator* self = NULL;

    self = new ResultSetIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->types = NULL;
    self->resultSet = NULL;
    return (self);
  }
}

Surrogate* ResultSetIterator::primaryType() {
  { ResultSetIterator* self = this;

    return (SGT_SDBC_SDBC_RESULT_SET_ITERATOR);
  }
}

Object* accessResultSetIteratorSlotValue(ResultSetIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SDBC_SDBC_TYPES) {
    if (setvalueP) {
      self->types = ((Cons*)(value));
    }
    else {
      value = self->types;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

Connection* connect(Cons* keysAndValues) {
  // Create a connection to a database.  Currently-supported parameters
  // are (values need to be strings):
  //   :PROTOCOL          - "ODBC", "JDBC", "CLSQL" or "MYSQL" (defaults to "ODBC")
  //   :SERVER-TYPE       - Type of database server (for JDBC strings)
  //   :DSN               - Name of ODBC Datasource
  //   :DB-NAME           - Name of physical database
  //   :USER              - Database user id.
  //   :PASSWORD          - Database password
  //   :HOST              - Host database server runs on
  //   :PORT              - Port to use to connect to the server
  //   :CONNECTION-STRING - Connection string to be used by ODBC or JDBC drivers
  //                        instead of DSN, USER, PASSWORD, etc.
  // A DATABASE-EXCEPTION is thrown if the connection is unsuccessful.
  return (callConnect(keysAndValues));
}

Connection* connectEvaluatorWrapper(Cons* arguments) {
  return (connect(arguments));
}

Connection* callConnect(Cons* keysAndValues) {
  // Functional interface to `connect'.  See its documentation
  { Connection* result = newConnection();
    sdbc::NativeConnection* nativeconnection = NULL;
    PropertyList* options = vetOptions(keysAndValues, getQuotedTree("((:PROTOCOL :SERVER-TYPE :DSN :DB-NAME :USER :PASSWORD :HOST :PORT :CONNECTION-STRING) \"/SDBC\")", "/SDBC"));

    { Object* temp000 = options->lookup(KWD_SDBC_PROTOCOL);

      { const char* protocol = stringUpcase((((boolean)(temp000)) ? ((StringWrapper*)(temp000))->wrapperValue : "ODBC"));
        const char* serverType = unwrapString(((StringWrapper*)(options->lookup(KWD_SDBC_SERVER_TYPE))));
        const char* connectionstring = NULL;

        if (stringEqlP(protocol, "CLSQL")) {
          nativeconnection = NULL;
        }
        else if (stringEqlP(protocol, "ODBC")) {
          connectionstring = makeOdbcConnectionString(options);
          nativeconnection = sdbc::getConnection((char*)connectionstring);
        }
        else if (stringEqlP(protocol, "JDBC")) {
          connectionstring = makeJdbcConnectionString(options);
          nativeconnection = NULL;
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "Database Error: unsupported protocol " << "`" << protocol << "'";
            throw *newDatabaseException(stream000->theStringReader());
          }
        }
        if (nativeconnection == NULL) {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "Database Error: " << "`" << protocol << "'" << " not supported in " << "`" << "C++" << "'";
            throw *newDatabaseException(stream001->theStringReader());
          }
        }
        result->nativeConnection = nativeconnection;
        result->connectionString = connectionstring;
        result->protocol = protocol;
        result->creationTime = makeCurrentDateTime();
        result->lastAccessTime = result->creationTime;
        result->renewalTime = ((CalendarDate*)(timeAdd(result->creationTime, makeTimeDuration(0, getMaxConnectionLifetime(result) * 1000))));
        logmsg("SDBC", KWD_SDBC_LOW, 4, wrapString("Connect via "), wrapString(protocol), wrapString(": "), wrapString(connectionstring));
        return (result);
      }
    }
  }
}

// The maximum lifetime of a database connection (in seconds) after which
// it gets automatically renewed.  Auto-renewals avoid connection timeout errors which are
// otherwise tricky to catch, e.g., we might just see a `bad handle passed' error.
int oDB_CONNECTION_RENEWAL_INTERVALo = 60;

int ODbConnectionRenewalIntervalOSetter(int value) {
  return (oDB_CONNECTION_RENEWAL_INTERVALo = value);
}

int getMaxConnectionLifetime(Connection* con) {
  con = con;
  return (oDB_CONNECTION_RENEWAL_INTERVALo);
}

void maybeRenewConnection(Connection* con) {
  if (!(con->autoCommitP)) {
    return;
  }
  { CalendarDate* currenttime = makeCurrentDateTime();
    PreparedStatement* statement = con->statement;
    Connection* newcon = NULL;

    con->lastAccessTime = currenttime;
    if (currenttime->greaterEqualP(con->renewalTime)) {
      logmsg("SDBC", KWD_SDBC_LOW, 4, wrapString("Renewing "), wrapString(con->protocol), wrapString(" connection: "), wrapString(con->connectionString));
      newcon = connect(consList(4, KWD_SDBC_PROTOCOL, wrapString(con->protocol), KWD_SDBC_CONNECTION_STRING, wrapString(con->connectionString)));
      disconnect(con);
      con->nativeConnection = newcon->nativeConnection;
      con->connectionString = newcon->connectionString;
      con->protocol = newcon->protocol;
      con->creationTime = newcon->creationTime;
      con->lastAccessTime = newcon->lastAccessTime;
      con->renewalTime = newcon->renewalTime;
      if (((boolean)(statement))) {
        prepareStatement(con, statement->sql);
        statement->statement = con->statement->statement;
        con->statement = statement;
        { IntegerWrapper* pos = NULL;
          Cons* entry = NULL;
          KvCons* iter000 = statement->parameters->theKvList;

          for  (; ((boolean)(iter000)); 
                iter000 = iter000->rest) {
            pos = ((IntegerWrapper*)(iter000->key));
            entry = ((Cons*)(iter000->value));
            bindParameter(statement, pos->wrapperValue, ((Surrogate*)(entry->value)), entry->rest->value);
          }
        }
      }
    }
  }
}

boolean jdbcConnectionStringP(const char* string) {
  return (stringSearch(string, "jdbc:", 0) == 0);
}

const char* makeJdbcConnectionString(PropertyList* options) {
  if (((boolean)(options->lookup(KWD_SDBC_CONNECTION_STRING)))) {
    return (((StringWrapper*)(options->lookup(KWD_SDBC_CONNECTION_STRING)))->wrapperValue);
  }
  { OutputStringStream* con = newOutputStringStream();
    const char* value = NULL;

    *(con->nativeStream) << "jdbc:";
    { const char* temp000 = unwrapString(((StringWrapper*)(options->lookup(KWD_SDBC_SERVER_TYPE))));

      value = stringDowncase(((temp000 != NULL) ? temp000 : "mysql"));
    }
    *(con->nativeStream) << value << ":";
    if (stringEqlP(value, "mysql")) {
      *(con->nativeStream) << "//";
      value = unwrapString(((StringWrapper*)(options->lookup(KWD_SDBC_HOST))));
      if (value != NULL) {
        *(con->nativeStream) << value;
      }
      { Object* port = options->lookup(KWD_SDBC_PORT);

        { Surrogate* testValue000 = safePrimaryType(port);

          if (subtypeOfStringP(testValue000)) {
            { Object* port000 = port;
              StringWrapper* port = ((StringWrapper*)(port000));

              *(con->nativeStream) << ":" << unwrapString(port);
            }
          }
          else if (subtypeOfIntegerP(testValue000)) {
            { Object* port001 = port;
              IntegerWrapper* port = ((IntegerWrapper*)(port001));

              *(con->nativeStream) << ":" << unwrapInteger(port);
            }
          }
          else {
          }
        }
      }
      *(con->nativeStream) << "/";
      value = unwrapString(((StringWrapper*)(options->lookup(KWD_SDBC_DB_NAME))));
      if (value != NULL) {
        *(con->nativeStream) << value;
      }
      { char separator = '?';

        { Keyword* option = NULL;
          Object* val = NULL;
          Cons* iter000 = options->thePlist;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest->rest) {
            option = ((Keyword*)(iter000->value));
            val = iter000->rest->value;
            if (((boolean)(val))) {
              if ((option == KWD_SDBC_SERVER_TYPE) ||
                  ((option == KWD_SDBC_DSN) ||
                   ((option == KWD_SDBC_HOST) ||
                    ((option == KWD_SDBC_PORT) ||
                     ((option == KWD_SDBC_DB_NAME) ||
                      (option == KWD_SDBC_PROTOCOL)))))) {
                continue;
              }
              else if ((option == KWD_SDBC_USER) ||
                  (option == KWD_SDBC_PASSWORD)) {
                *(con->nativeStream) << separator << stringDowncase(option->symbolName);
              }
              else {
                *(con->nativeStream) << separator << option->symbolName << "=" << unwrapString(((StringWrapper*)(val)));
              }
              *(con->nativeStream) << "=" << unwrapString(((StringWrapper*)(val)));
              separator = '&';
            }
          }
        }
      }
    }
    else if (stringEqlP(value, "oracle")) {
      *(con->nativeStream) << "thin:";
      value = unwrapString(((StringWrapper*)(options->lookup(KWD_SDBC_USER))));
      if (value != NULL) {
        *(con->nativeStream) << value;
      }
      { const char* temp001 = unwrapString(((StringWrapper*)(options->lookup(KWD_SDBC_PASSWORD))));

        value = ((temp001 != NULL) ? temp001 : "");
      }
      *(con->nativeStream) << "/" << value;
      { const char* temp002 = unwrapString(((StringWrapper*)(options->lookup(KWD_SDBC_HOST))));

        value = ((temp002 != NULL) ? temp002 : "localhost");
      }
      *(con->nativeStream) << "@//" << value;
      { Object* temp003 = options->lookup(KWD_SDBC_PORT);

        { Object* port = (((boolean)(temp003)) ? temp003 : wrapString("1521"));

          { Surrogate* testValue001 = safePrimaryType(port);

            if (subtypeOfStringP(testValue001)) {
              { Object* port002 = port;
                StringWrapper* port = ((StringWrapper*)(port002));

                *(con->nativeStream) << ":" << unwrapString(port);
              }
            }
            else if (subtypeOfIntegerP(testValue001)) {
              { Object* port003 = port;
                IntegerWrapper* port = ((IntegerWrapper*)(port003));

                *(con->nativeStream) << ":" << unwrapInteger(port);
              }
            }
            else {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
                throw *newStellaException(stream000->theStringReader());
              }
            }
          }
        }
      }
      value = unwrapString(((StringWrapper*)(options->lookup(KWD_SDBC_DB_NAME))));
      if (value != NULL) {
        *(con->nativeStream) << "/" << value;
      }
    }
    else {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "Don't know how to generate JDBC connection string" << " for servers of :SERVER-TYPE " << "`" << options->lookup(KWD_SDBC_SERVER_TYPE) << "'";
        throw *newDatabaseException(stream001->theStringReader());
      }
    }
    return (con->theStringReader());
  }
}

boolean odbcConnectionStringP(const char* string) {
  return ((strlen(string) > 0) &&
      ((!jdbcConnectionStringP(string)) &&
       (stringPosition(string, '=', 1) != NULL_INTEGER)));
}

const char* makeOdbcConnectionString(PropertyList* options) {
  if (((boolean)(((StringWrapper*)(options->lookup(KWD_SDBC_CONNECTION_STRING)))))) {
    return (((StringWrapper*)(options->lookup(KWD_SDBC_CONNECTION_STRING)))->wrapperValue);
  }
  { OutputStringStream* con = newOutputStringStream();

    { Keyword* option = NULL;
      StringWrapper* value = NULL;
      Cons* iter000 = options->thePlist;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest->rest) {
        option = ((Keyword*)(iter000->value));
        value = ((StringWrapper*)(iter000->rest->value));
        if (((boolean)(value))) {
          if (option == KWD_SDBC_USER) {
            *(con->nativeStream) << "UID";
          }
          else if (option == KWD_SDBC_PASSWORD) {
            *(con->nativeStream) << "PWD";
          }
          else if (option == KWD_SDBC_DB_NAME) {
            *(con->nativeStream) << "DATABASE";
          }
          else if (option == KWD_SDBC_HOST) {
            *(con->nativeStream) << "SERVER";
          }
          else if ((option == KWD_SDBC_PROTOCOL) ||
              (option == KWD_SDBC_SERVER_TYPE)) {
            continue;
          }
          else {
            *(con->nativeStream) << option->symbolName;
          }
          *(con->nativeStream) << "=" << unwrapString(value) << ";";
        }
      }
    }
    return (con->theStringReader());
  }
}

sdbc::NativeConnection* clNativeOdbcConnect(const char* connectionstring, const char*& _Return1) {
  { const char* errormsg = NULL;
    sdbc::NativeConnection* nativeconnection = NULL;

    nativeconnection = nativeconnection;
    if (errormsg != NULL) {
      throw *newDatabaseException(errormsg);
    }
    _Return1 = connectionstring;
    return (nativeconnection);
  }
}

sdbc::NativeConnection* clNativeClsqlConnect(PropertyList* options, const char* serverType, const char*& _Return1) {
  { const char* connectionString = unwrapString(((StringWrapper*)(options->lookup(KWD_SDBC_CONNECTION_STRING))));
    const char* user = unwrapString(((StringWrapper*)(options->lookup(KWD_SDBC_USER))));
    const char* password = unwrapString(((StringWrapper*)(options->lookup(KWD_SDBC_PASSWORD))));
    const char* dbName = unwrapString(((StringWrapper*)(options->lookup(KWD_SDBC_DB_NAME))));
    const char* host = unwrapString(((StringWrapper*)(options->lookup(KWD_SDBC_HOST))));
    const char* errorMessage = NULL;
    sdbc::NativeConnection* nativeConnection = NULL;

    nativeConnection = nativeConnection;
    if (errorMessage != NULL) {
      throw *newDatabaseException(errorMessage);
    }
    _Return1 = connectionString;
    return (nativeConnection);
  }
}

void disconnect(Connection* connection) {
  // Disconnect `connection' from a database.  A DATABASE-EXCEPTION is thrown if
  // the disconnect is unsuccessful.
  { sdbc::NativeConnection* nativeconnection = connection->nativeConnection;

    if (!(nativeconnection == NULL)) {
      sdbc::nativeDisconnect(nativeconnection);
      logmsg("SDBC", KWD_SDBC_LOW, 4, wrapString("Disconnecting "), wrapString(connection->protocol), wrapString(" connection: "), wrapString(connection->connectionString));
      connection->nativeConnection = NULL;
    }
  }
}

void clNativeDisconnect(sdbc::NativeConnection* nativeConnection) {
}

void clNativeOdbcDisconnect(sdbc::NativeConnection* nativeconnection) {
  { const char* errormsg = NULL;

    nativeconnection = nativeconnection;
    if (errormsg != NULL) {
      throw *newDatabaseException(errormsg);
    }
  }
}

void clNativeClsqlDisconnect(sdbc::NativeConnection* nativeConnection) {
  { const char* errorMsg = NULL;

    nativeConnection = nativeConnection;
    if (errorMsg != NULL) {
      throw *newDatabaseException(errorMsg);
    }
  }
}

boolean sqlQueryP(const char* sqlExpression) {
  // Return `true' if `sql-expression' is a SQL command string which returns
  // values.
  { int start = 0;
    int end = 0;
    const char* operatoR = "";

    while (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (sqlExpression[start])] == KWD_SDBC_WHITE_SPACE) {
      start = start + 1;
    }
    end = start;
    while (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (sqlExpression[end])] == KWD_SDBC_LETTER) {
      end = end + 1;
    }
    operatoR = stringSubsequence(sqlExpression, start, end);
    return (stringEqualP(operatoR, "SELECT") ||
        (stringEqualP(operatoR, "SHOW") ||
         (stringEqualP(operatoR, "DESCRIBE") ||
          (stringEqualP(operatoR, "EXPLAIN") ||
           stringEqualP(operatoR, "ANALYZE")))));
  }
}

Object* stellifyWithNilToNull(Object* self) {
  // Convert a Lisp object into a STELLA object.
  { Object* result = self;

    return (result);
  }
}

Object* clTranslateSqlParameterTypeSpecifier(Object* stellatype) {
  { Object* result = NULL;

    if ((!((boolean)(stellatype))) ||
        (stellatype == SYM_SDBC_STELLA_NULL)) {
    }
    else {
      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(stellatype));

        if (testValue000 == SGT_SDBC_STELLA_CALENDAR_DATE) {
        }
        else if (testValue000 == SGT_SDBC_STELLA_STRING) {
        }
        else if (testValue000 == SGT_SDBC_STELLA_INTEGER) {
        }
        else if (testValue000 == SGT_SDBC_STELLA_LONG_INTEGER) {
        }
        else if (testValue000 == SGT_SDBC_STELLA_DOUBLE_FLOAT) {
        }
        else {
        }
      }
    }
    return (result);
  }
}

Object* clTranslateSqlTypeSpecifier(Object* stellatype) {
  { Object* result = NULL;

    if ((!((boolean)(stellatype))) ||
        (stellatype == SYM_SDBC_STELLA_NULL)) {
    }
    else {
      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(stellatype));

        if (testValue000 == SGT_SDBC_STELLA_CALENDAR_DATE) {
        }
        else if (testValue000 == SGT_SDBC_STELLA_STRING) {
        }
        else if (testValue000 == SGT_SDBC_STELLA_INTEGER) {
        }
        else if (testValue000 == SGT_SDBC_STELLA_LONG_INTEGER) {
        }
        else if (testValue000 == SGT_SDBC_STELLA_DOUBLE_FLOAT) {
        }
        else {
        }
      }
    }
    return (result);
  }
}

Cons* clTranslateSqlTypeSpecifiers(Cons* stellatypes) {
  { Cons* value000 = NIL;

    { Object* type = NULL;
      Cons* iter000 = stellatypes;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        type = iter000->value;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(clTranslateSqlTypeSpecifier(type), NIL);
            if (value000 == NIL) {
              value000 = collect000;
            }
            else {
              addConsToEndOfConsList(value000, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(clTranslateSqlTypeSpecifier(type), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    { Cons* value001 = value000;

      return (value001);
    }
  }
}

Object* executeSql(Connection* connection, Object* sql, Cons* options) {
  // Execute a SQL statement, and return a table as the reuslt
  //                   of a SQL query (represented as a (CONS OF (CONS OF OBJECT))),
  //                   or NULL as the result of a successfull SQL insert, update,
  //                   delete or other command.
  //                   `sql' can either be a string representing a SQL command or
  //                   a PREPARED-STATEMENT.
  //                   Options include: 
  //                      :types <typelist>, where <typelist> is a cons list of surrogates
  //                   specifying the expected Stella types.  Legal surrogate values are
  //                   @INTEGER, @LONG-INTEGER, @DOUBLE-FLOAT, @CALENDAR-DATE, @STRING, and
  //                   NULL.  If NULL is specified, values are returned as strings.
  //                   A DATABASE-EXCEPTION is thrown if execution is unsuccessful.
  maybeRenewConnection(connection);
  { Object* result = NULL;
    sdbc::NativeConnection* ncon = connection->nativeConnection;
    PropertyList* proplist = vetOptions(options, getQuotedTree("((:TYPES) \"/SDBC\")", "/SDBC"));
    Cons* types = ((Cons*)(proplist->lookup(KWD_SDBC_TYPES)));

    { Surrogate* testValue000 = safePrimaryType(sql);

      if (subtypeOfStringP(testValue000)) {
        { Object* sql000 = sql;
          StringWrapper* sql = ((StringWrapper*)(sql000));

          logmsg("SDBC", KWD_SDBC_HIGH, 2, wrapString("execute-sql: sql="), sql);
          result = sdbc::executeSQL(ncon, (char*)stella::unwrapString((StringWrapper*)sql), types);
        }
      }
      else if (subtypeOfP(testValue000, SGT_SDBC_SDBC_PREPARED_STATEMENT)) {
        { Object* sql001 = sql;
          PreparedStatement* sql = ((PreparedStatement*)(sql001));

          logmsg("SDBC", KWD_SDBC_HIGH, 4, wrapString("execute-sql: prepared sql="), wrapString(sql->sql), wrapString(", parameters="), sql->parameters);
          result = sdbc::doExecutePreparedStatement(ncon);
        }
      }
      else {
        throw *newStellaException("`sql' argument must be of type STRING-WRAPPER or PREPARED-STATEMENT");
      }
    }
    return (coerceUncoercedValuesInTable(((Cons*)(result)), types));
  }
}

Object* executeSqlEvaluatorWrapper(Cons* arguments) {
  return (executeSql(((Connection*)(arguments->value)), arguments->rest->value, arguments->rest->rest));
}

Object* clExecuteSql(sdbc::NativeConnection* connection, const char* sql, Cons* types) {
  return (NULL);
}

Object* clDoExecutePreparedStatement(sdbc::NativeConnection* connection, PreparedStatement* sql) {
  sql = sql;
  return (NULL);
}

ResultSetIterator* getResultSet(Connection* connection, const char* sql, int options, ...) {
  // Execute a SQL query, and return a ResultSet object.
  //                   Options include: 
  //                      :types <typelist>, where <typelist> is a cons list of surrogates
  //                   specifying the expected Stella types.  Legal surrogate values are
  //                   @INTEGER, @LONG-INTEGER, @DOUBLE-FLOAT, @CALENDAR-DATE, @STRING, and
  //                   NULL.  If NULL is specified, values are returned as strings.
  //                   A DATABASE-EXCEPTION is thrown if execution is unsuccessful.
  maybeRenewConnection(connection);
  { NativeResultSet* nativeresultset = NULL;
    sdbc::NativeConnection* nativeconnection = connection->nativeConnection;
    ResultSetIterator* resultsetiterator = newResultSetIterator();

    { Cons* arglist000 = NIL;

      { va_list iter000;
        int iter000Count = options;
        Object* arg000 = NULL;
        Cons* collect000 = NULL;

        va_start(iter000, options);
                for  (; (iter000Count--) > 0; ) {
          arg000 = va_arg(iter000, Object*);
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(arg000, NIL);
              if (arglist000 == NIL) {
                arglist000 = collect000;
              }
              else {
                addConsToEndOfConsList(arglist000, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(arg000, NIL);
              collect000 = collect000->rest;
            }
          }
        }
        va_end(iter000);
      }
      { PropertyList* proplist = vetOptions(arglist000, getQuotedTree("((:TYPES) \"/SDBC\")", "/SDBC"));
        Cons* types = ((Cons*)(proplist->lookup(KWD_SDBC_TYPES)));

        resultsetiterator->types = types;
        logmsg("SDBC", KWD_SDBC_HIGH, 2, wrapString("get-result-set: sql="), wrapString(sql));
        nativeresultset = sdbc::getNativeResultSet(nativeconnection, (char*)sql, types);
        resultsetiterator->resultSet = nativeresultset;
        return (resultsetiterator);
      }
    }
  }
}

NativeResultSet* clGetNativeResultSet(sdbc::NativeConnection* connection, const char* sql, Cons* types) {
  return (NULL);
}

boolean ResultSetIterator::nextP() {
  { ResultSetIterator* self = this;

    { NativeResultSet* nativeResultSet = self->resultSet;
      Cons* result = NULL;

      if (nativeResultSet == NULL) {
        return (false);
      }
      result = sdbc::fetchRow(nativeResultSet);
      self->value = (((boolean)(result)) ? coerceUncoercedColumnValues(result, self->types) : ((Cons*)(NULL)));
      if (((boolean)(result))) {
        return (true);
      }
      else {
        self->resultSet = NULL;
        return (false);
      }
    }
  }
}

const char* sqlEscapeString(const char* value, char quotechar) {
  { int cursor = strlen(value) - 1;

    while (cursor >= 0) {
      if (value[cursor] == quotechar) {
        return (replaceSubstrings(value, makeString(2, quotechar), makeString(1, quotechar)));
      }
      cursor = cursor - 1;
    }
    return (value);
  }
}

char sqlQuoteCharacter(Keyword* dbmsName, Keyword* lexicaltype) {
  if (lexicaltype == KWD_SDBC_STRING_CONSTANT) {
    return ('\'');
  }
  else if (lexicaltype == KWD_SDBC_IDENTIFIER) {
    if (dbmsName == KWD_SDBC_MYSQL) {
      return ('`');
    }
    else {
      return ('"');
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << lexicaltype << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void printValueList(OutputStream* stream, Cons* values, char quotechar) {
  { Object* value = NULL;
    Cons* iter000 = values;
    int i = NULL_INTEGER;
    int iter001 = 1;

    for  (; !(iter000 == NIL); 
          iter000 = iter000->rest,
          iter001 = iter001 + 1) {
      value = iter000->value;
      i = iter001;
      if (i > 1) {
        *(stream->nativeStream) << ",";
      }
      if ((!((boolean)(value))) ||
          ((value == SYM_SDBC_STELLA_NULL) ||
           (value == KWD_SDBC_NULL))) {
        *(stream->nativeStream) << "NULL";
      }
      else if ((value == SYM_SDBC_STELLA_DEFAULT) ||
          (value == KWD_SDBC_DEFAULT)) {
        *(stream->nativeStream) << "DEFAULT";
      }
      else {
        { Surrogate* testValue000 = safePrimaryType(value);

          if (subtypeOfIntegerP(testValue000)) {
            { Object* value000 = value;
              IntegerWrapper* value = ((IntegerWrapper*)(value000));

              *(stream->nativeStream) << value->wrapperValue;
            }
          }
          else if (subtypeOfFloatP(testValue000)) {
            { Object* value001 = value;
              FloatWrapper* value = ((FloatWrapper*)(value001));

              *(stream->nativeStream) << value->wrapperValue;
            }
          }
          else if (subtypeOfVerbatimStringP(testValue000)) {
            { Object* value002 = value;
              VerbatimStringWrapper* value = ((VerbatimStringWrapper*)(value002));

              *(stream->nativeStream) << value->wrapperValue;
            }
          }
          else if (subtypeOfStringP(testValue000)) {
            { Object* value003 = value;
              StringWrapper* value = ((StringWrapper*)(value003));

              *(stream->nativeStream) << quotechar << sqlEscapeString(value->wrapperValue, quotechar) << quotechar;
            }
          }
          else {
            *(stream->nativeStream) << quotechar << sqlEscapeString(stringify(value), quotechar) << quotechar;
          }
        }
      }
    }
  }
}

void insertRow(Connection* connection, const char* table, Cons* columns, Cons* values) {
  // Insert a row of `values' into `table'.  `columns'
  // can be NULL or NIL in which case `values' must be suppied for all
  // columns.  If `columns' are given `values' will be only inserted in
  // the specified columns.  Table and column names will be quoted which
  // means their casing must match exactly their definition (no case
  // conversion will be performed).  Supplied `values' can be strings,
  // integers or floats.  Strings will be quoted and escaped appropriately.
  // The values NULL, :NULL or (quote NULL) translate into NULL.  The
  // values :DEFAULT or (quote DEFAULT) translate into DEFAULT.  Arbitrary
  // unquoted strings can be generated via VERBATIM-STRING-WRAPPERs as
  // values (e.g., for something like `seq.nextval' in Oracle).
  if ((!((boolean)(values))) ||
      (values == NIL)) {
    return;
  }
  insertRows(connection, table, columns, cons(values, NIL));
}

void insertRowEvaluatorWrapper(Cons* arguments) {
  insertRow(((Connection*)(arguments->value)), ((StringWrapper*)(arguments->rest->value))->wrapperValue, ((Cons*)(arguments->rest->rest->value)), ((Cons*)(arguments->rest->rest->rest->value)));
}

void insertRows(Connection* connection, const char* table, Cons* columns, Cons* rows) {
  // Insert a set of `rows' into `table'.  `columns'
  // can be NULL or NIL in which case values must be suppied for all
  // columns.  If `columns' are given `values' will be only inserted in
  // the specified columns.  Table and column names will be quoted which
  // means their casing must match exactly their definition (no case
  // conversion will be performed).  See `insert-row' for a description
  // of supported value formats.  DEFAULT values are currently not supported
  // for Oracle!  This function performs a fairly efficient multi-row
  // insert which is significantly faster than inserting rows one by one.
  if ((!((boolean)(rows))) ||
      (rows == NIL)) {
    return;
  }
  { OutputStringStream* sql = NULL;
    char idquote = sqlQuoteCharacter(getDbmsName(connection), KWD_SDBC_IDENTIFIER);
    char valuequote = sqlQuoteCharacter(getDbmsName(connection), KWD_SDBC_STRING_CONSTANT);
    int blocklength = 1000;
    int oracleblocklength = 100;

    for (;;) {
      sql = newOutputStringStream();
      *(sql->nativeStream) << "INSERT INTO " << idquote << sqlEscapeString(table, idquote) << idquote;
      if (((boolean)(columns)) &&
          (!(columns == NIL))) {
        *(sql->nativeStream) << "(";
        printValueList(sql, columns, idquote);
        *(sql->nativeStream) << ")";
      }
      if ((getDbmsName(connection) == KWD_SDBC_ORACLE) &&
          (!(rows->rest == NIL))) {
        { Cons* values = NULL;
          Cons* iter000 = rows;
          int i = NULL_INTEGER;
          int iter001 = 1;
          int upperBound000 = oracleblocklength;
          boolean unboundedP000 = upperBound000 == NULL_INTEGER;

          for  (; (!(iter000 == NIL)) &&
                    (unboundedP000 ||
                     (iter001 <= upperBound000)); 
                iter000 = iter000->rest,
                iter001 = iter001 + 1) {
            values = ((Cons*)(iter000->value));
            i = iter001;
            if (i > 1) {
              *(sql->nativeStream) << " UNION";
            }
            *(sql->nativeStream) << " SELECT ";
            printValueList(sql, values, valuequote);
            *(sql->nativeStream) << " FROM DUAL";
            rows = rows->rest;
          }
        }
      }
      else {
        *(sql->nativeStream) << " VALUES";
        { Cons* values = NULL;
          Cons* iter002 = rows;
          int i = NULL_INTEGER;
          int iter003 = 1;
          int upperBound001 = blocklength;
          boolean unboundedP001 = upperBound001 == NULL_INTEGER;

          for  (; (!(iter002 == NIL)) &&
                    (unboundedP001 ||
                     (iter003 <= upperBound001)); 
                iter002 = iter002->rest,
                iter003 = iter003 + 1) {
            values = ((Cons*)(iter002->value));
            i = iter003;
            if (i > 1) {
              *(sql->nativeStream) << ",";
            }
            *(sql->nativeStream) << "(";
            printValueList(sql, values, valuequote);
            *(sql->nativeStream) << ")";
            rows = rows->rest;
          }
        }
      }
      executeSql(connection, wrapString(sql->theStringReader()), NIL);
      if (rows == NIL) {
        break;
      }
    }
  }
}

void insertRowsEvaluatorWrapper(Cons* arguments) {
  insertRows(((Connection*)(arguments->value)), ((StringWrapper*)(arguments->rest->value))->wrapperValue, ((Cons*)(arguments->rest->rest->value)), ((Cons*)(arguments->rest->rest->rest->value)));
}

Cons* coerceUncoercedValuesInTable(Cons* table, Cons* types) {
  if (!((boolean)(types))) {
    return (table);
  }
  { Cons* result = NIL;

    { Object* row = NULL;
      Cons* iter000 = table;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        row = iter000->value;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(coerceUncoercedColumnValues(((Cons*)(row)), types), NIL);
            if (result == NIL) {
              result = collect000;
            }
            else {
              addConsToEndOfConsList(result, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(coerceUncoercedColumnValues(((Cons*)(row)), types), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (result);
  }
}

Cons* coerceUncoercedColumnValues(Cons* row, Cons* types) {
  if (!((boolean)(types))) {
    return (row);
  }
  { Cons* result = NIL;

    { Object* value = NULL;
      Cons* iter000 = row;
      Object* type = NULL;
      Cons* iter001 = types;
      Cons* collect000 = NULL;

      for  (; (!(iter000 == NIL)) &&
                (!(iter001 == NIL)); 
            iter000 = iter000->rest,
            iter001 = iter001->rest) {
        value = iter000->value;
        type = iter001->value;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons((stringP(value) ? convertStringToTypedObject(((StringWrapper*)(value))->wrapperValue, ((GeneralizedSymbol*)(type))) : value), NIL);
            if (result == NIL) {
              result = collect000;
            }
            else {
              addConsToEndOfConsList(result, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons((stringP(value) ? convertStringToTypedObject(((StringWrapper*)(value))->wrapperValue, ((GeneralizedSymbol*)(type))) : value), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (result);
  }
}

Object* convertStringToTypedObject(const char* valuestring, GeneralizedSymbol* typespec) {
  if (typespec == SGT_SDBC_STELLA_CALENDAR_DATE) {
    return (stringToCalendarDate(valuestring));
  }
  else {
    return (wrapString(valuestring));
  }
}

PreparedStatement* prepareStatement(Connection* connection, const char* sql) {
  // Prepare the `sql' statement for execution at the server and return
  // a prepared statement object.  After binding all its paramters via `bind-parameter'
  // the statement can be executed via `execute-sql'.
  // IMPORTANT: Only one prepared statement can be associated with a connection at a time.
  maybeRenewConnection(connection);
  { PreparedStatement* result = newPreparedStatement();
    sdbc::NativeConnection* nativeconnection = connection->nativeConnection;

    result->connection = connection;
    connection->statement = result;
    result->sql = sql;
    sdbc::doPrepareStatement(nativeconnection, (char*)sql);
    return (result);
  }
}

PreparedStatement* prepareStatementEvaluatorWrapper(Cons* arguments) {
  return (prepareStatement(((Connection*)(arguments->value)), ((StringWrapper*)(arguments->rest->value))->wrapperValue));
}

void bindParameter(PreparedStatement* statement, int position, Surrogate* typespec, Object* value) {
  // Bind the parameter at `position' (1-based) in the prepared
  // statement `statement' to `value'.  `typeSpec' characterizes the type of
  // `value' for proper translation and coercion.
  { Connection* connection = statement->connection;
    sdbc::NativeConnection* ncon = NULL;

    maybeRenewConnection(connection);
    ncon = connection->nativeConnection;
    statement->parameters->insertAt(wrapInteger(position), consList(2, typespec, value));
    if (typespec == SGT_SDBC_STELLA_CALENDAR_DATE) {
      typespec = SGT_SDBC_STELLA_STRING;
      if (((boolean)(value))) {
        value = wrapString(calendarDateToSqlString(((CalendarDate*)(value))));
      }
    }
    sdbc::doBindParameter(ncon, position, typespec, value);
  }
}

void bindParameterEvaluatorWrapper(Cons* arguments) {
  bindParameter(((PreparedStatement*)(arguments->value)), ((IntegerWrapper*)(arguments->rest->value))->wrapperValue, ((Surrogate*)(arguments->rest->rest->value)), arguments->rest->rest->rest->value);
}

void clDoBindParameter(PreparedStatement* statement, int position, Surrogate* typespec, Object* value) {
  { sdbc::NativeConnection* nativeconnection = statement->connection->nativeConnection;
    boolean nullP = !((boolean)(value));
    boolean wrapperP = isaP(value, SGT_SDBC_STELLA_WRAPPER);

  }
}

void setAutoCommit(Connection* connection, boolean flag) {
  // Set the auto-commit feature of `connection' to TRUE or FALSE.
  // If a connection is in auto-commit mode, then all its SQL statements will be executed
  // and committed as individual transactions.  Otherwise, its SQL statements are grouped
  // into transactions that are terminated by a call to either `commit' or `rollback'.
  // By default, new connections are in auto-commit mode.
  maybeRenewConnection(connection);
  { sdbc::NativeConnection* nativeConnection = connection->nativeConnection;

    sdbc::setAutocommitFlag(nativeConnection, flag);
    connection->autoCommitP = flag;
  }
}

void setAutoCommitEvaluatorWrapper(Cons* arguments) {
  setAutoCommit(((Connection*)(arguments->value)), ((BooleanWrapper*)(arguments->rest->value))->wrapperValue);
}

void commit(Connection* connection) {
  // Commit the current transaction.  Makes all changes made since the
  // previous commit/rollback permanent and releases any database locks currently held
  // by this `connection' object.  This function is a no-op if auto-commit mode is
  // enabled (see `set-auto-commit').
  if (!(connection->autoCommitP)) {
    { sdbc::NativeConnection* nativeConnection = connection->nativeConnection;

      sdbc::doCommit(nativeConnection);
    }
  }
}

void rollback(Connection* connection) {
  // Rollback the current transaction.  Undoes all changes made in
  // the current transaction and releases any database locks currently held by this
  // `connection' object.  This function is a no-op if auto-commit mode is enabled
  //  (see `set-auto-commit').
  if (!(connection->autoCommitP)) {
    { sdbc::NativeConnection* nativeConnection = connection->nativeConnection;

      sdbc::doRollback(nativeConnection);
    }
  }
}

TableInfo* newTableInfo() {
  { TableInfo* self = NULL;

    self = new TableInfo();
    self->columns = NULL;
    self->remarks = NULL;
    self->type = NULL;
    self->name = NULL;
    self->schema = NULL;
    self->database = NULL;
    return (self);
  }
}

Surrogate* TableInfo::primaryType() {
  { TableInfo* self = this;

    return (SGT_SDBC_SDBC_TABLE_INFO);
  }
}

Object* accessTableInfoSlotValue(TableInfo* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SDBC_SDBC_DATABASE) {
    if (setvalueP) {
      self->database = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->database);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_CATALOG) {
    if (setvalueP) {
      self->database = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->database);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_SCHEMA) {
    if (setvalueP) {
      self->schema = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->schema);
    }
  }
  else if (slotname == SYM_SDBC_STELLA_NAME) {
    if (setvalueP) {
      self->name = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->name);
    }
  }
  else if (slotname == SYM_SDBC_STELLA_TYPE) {
    if (setvalueP) {
      self->type = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->type);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_REMARKS) {
    if (setvalueP) {
      self->remarks = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->remarks);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_COLUMNS) {
    if (setvalueP) {
      self->columns = ((List*)(value));
    }
    else {
      value = self->columns;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

ColumnInfo* newColumnInfo() {
  { ColumnInfo* self = NULL;

    self = new ColumnInfo();
    self->ordinalPosition = NULL_INTEGER;
    self->charOctetLength = NULL_INTEGER;
    self->sqlDatetimeSub = NULL_INTEGER;
    self->sqlDataType = NULL_INTEGER;
    self->defaultValue = NULL;
    self->documentation = NULL;
    self->isNullableP = NULL;
    self->nullableP = NULL;
    self->radix = NULL_INTEGER;
    self->decimalDigits = NULL_INTEGER;
    self->bufferLength = NULL_INTEGER;
    self->columnSize = NULL_INTEGER;
    self->dataTypeName = NULL;
    self->dataType = NULL_INTEGER;
    self->name = NULL;
    self->tableName = NULL;
    self->schema = NULL;
    self->database = NULL;
    return (self);
  }
}

Surrogate* ColumnInfo::primaryType() {
  { ColumnInfo* self = this;

    return (SGT_SDBC_SDBC_COLUMN_INFO);
  }
}

Object* accessColumnInfoSlotValue(ColumnInfo* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SDBC_SDBC_DATABASE) {
    if (setvalueP) {
      self->database = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->database);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_CATALOG) {
    if (setvalueP) {
      self->database = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->database);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_SCHEMA) {
    if (setvalueP) {
      self->schema = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->schema);
    }
  }
  else if (slotname == SYM_SDBC_STELLA_TABLE_NAME) {
    if (setvalueP) {
      self->tableName = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->tableName);
    }
  }
  else if (slotname == SYM_SDBC_STELLA_NAME) {
    if (setvalueP) {
      self->name = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->name);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_DATA_TYPE) {
    if (setvalueP) {
      self->dataType = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->dataType);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_DATA_TYPE_NAME) {
    if (setvalueP) {
      self->dataTypeName = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->dataTypeName);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_COLUMN_SIZE) {
    if (setvalueP) {
      self->columnSize = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->columnSize);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_BUFFER_LENGTH) {
    if (setvalueP) {
      self->bufferLength = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->bufferLength);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_DECIMAL_DIGITS) {
    if (setvalueP) {
      self->decimalDigits = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->decimalDigits);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_RADIX) {
    if (setvalueP) {
      self->radix = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->radix);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_NULLABLEp) {
    if (setvalueP) {
      self->nullableP = ((BooleanWrapper*)(value));
    }
    else {
      value = self->nullableP;
    }
  }
  else if (slotname == SYM_SDBC_SDBC_IS_NULLABLEp) {
    if (setvalueP) {
      self->isNullableP = ((BooleanWrapper*)(value));
    }
    else {
      value = self->isNullableP;
    }
  }
  else if (slotname == SYM_SDBC_STELLA_DOCUMENTATION) {
    if (setvalueP) {
      self->documentation = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->documentation);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_REMARKS) {
    if (setvalueP) {
      self->documentation = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->documentation);
    }
  }
  else if (slotname == SYM_SDBC_STELLA_DEFAULT_VALUE) {
    if (setvalueP) {
      self->defaultValue = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->defaultValue);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_SQL_DATA_TYPE) {
    if (setvalueP) {
      self->sqlDataType = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->sqlDataType);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_SQL_DATETIME_SUB) {
    if (setvalueP) {
      self->sqlDatetimeSub = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->sqlDatetimeSub);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_CHAR_OCTET_LENGTH) {
    if (setvalueP) {
      self->charOctetLength = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->charOctetLength);
    }
  }
  else if (slotname == SYM_SDBC_SDBC_ORDINAL_POSITION) {
    if (setvalueP) {
      self->ordinalPosition = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->ordinalPosition);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

Cons* getTables(Connection* connection, const char* catalogName, const char* schemaName, const char* tableName, const char* tableType) {
  // Get the tables of the database identified by `connection'
  // and return the result as a list of objects containing all the relevant
  // meta information.  If any of the remaining arguments is supplied as
  // non-NULL, only tables whose corresponding field matches will be returned.
  // This is less general than what is supported by JDBC and ODBC, but Allegro
  // ODBC does not support filtering based on patterns, so we only do simple
  // manual filtering here.
  maybeRenewConnection(connection);
  { sdbc::NativeConnection* ncon = connection->nativeConnection;
    NativeResultSet* resultSet = NULL;
    Iterator* resultIterator = NULL;
    boolean filtertablesP = false &&
        ((catalogName != NULL) ||
         ((schemaName != NULL) ||
          ((tableName != NULL) ||
           (tableType != NULL))));
    TableInfo* tableInfo = NULL;
    Cons* tables = NIL;

    throw *newStellaException("get-tables not yet implemented");
    if (!((boolean)(resultIterator))) {
      { ResultSetIterator* self001 = newResultSetIterator();

        self001->resultSet = resultSet;
        resultIterator = self001;
      }
    }
    { Cons* tableRow = NULL;
      Iterator* iter000 = resultIterator;

      for (; iter000->nextP(); ) {
        tableRow = ((Cons*)(iter000->value));
        if (filtertablesP &&
            (((catalogName != NULL) &&
            (!eqlToStringP(tableRow->value, catalogName))) ||
             (((schemaName != NULL) &&
            (!eqlToStringP(tableRow->rest->value, schemaName))) ||
              (((tableName != NULL) &&
            (!eqlToStringP(tableRow->rest->rest->value, tableName))) ||
               ((tableType != NULL) &&
                (!eqlToStringP(tableRow->fourth(), tableType))))))) {
          continue;
        }
        { TableInfo* self002 = newTableInfo();

          self002->database = ((StringWrapper*)(tableRow->value))->wrapperValue;
          self002->schema = ((StringWrapper*)(tableRow->rest->value))->wrapperValue;
          self002->name = ((StringWrapper*)(tableRow->rest->rest->value))->wrapperValue;
          self002->type = ((StringWrapper*)(tableRow->fourth()))->wrapperValue;
          self002->remarks = ((StringWrapper*)(tableRow->fifth()))->wrapperValue;
          tableInfo = self002;
        }
        if (stringEqlP(tableInfo->database, "")) {
          tableInfo->database = NULL;
        }
        if (stringEqlP(tableInfo->schema, "")) {
          tableInfo->schema = NULL;
        }
        tables = cons(tableInfo, tables);
      }
    }
    return (tables->reverse());
  }
}

Cons* getTablesEvaluatorWrapper(Cons* arguments) {
  return (getTables(((Connection*)(arguments->value)), ((StringWrapper*)(arguments->rest->value))->wrapperValue, ((StringWrapper*)(arguments->rest->rest->value))->wrapperValue, ((StringWrapper*)(arguments->rest->rest->rest->value))->wrapperValue, ((StringWrapper*)(arguments->rest->rest->rest->rest->value))->wrapperValue));
}

Cons* getColumns(Connection* connection, const char* catalogname, const char* schemaname, const char* tablename, const char* columnname) {
  std::cout << "FINISH ME";
  return (NULL);
}

Cons* getColumnsEvaluatorWrapper(Cons* arguments) {
  return (getColumns(((Connection*)(arguments->value)), ((StringWrapper*)(arguments->rest->value))->wrapperValue, ((StringWrapper*)(arguments->rest->rest->value))->wrapperValue, ((StringWrapper*)(arguments->rest->rest->rest->value))->wrapperValue, ((StringWrapper*)(arguments->rest->rest->rest->rest->value))->wrapperValue));
}

Wrapper* getServerInfo(Connection* connection, const char* property) {
  { sdbc::NativeConnection* ncon = connection->nativeConnection;

    { const char* testValue000 = connection->protocol;

      if (stringEqlP(testValue000, "ODBC")) {
        return(sdbc::doGetServerInfo(ncon, (char*)property));
      }
      else if (stringEqlP(testValue000, "JDBC")) {
      }
      else {
      }
    }
    { const char* testValue001 = stringUpcase(property);

      if (stringEqlP(testValue001, "DBMS-NAME")) {
        return (wrapString(guessDbmsName(connection)));
      }
      else if (stringEqlP(testValue001, "DBMS-VERSION")) {
        { Keyword* testValue002 = getDbmsName(connection);

          if (testValue002 == KWD_SDBC_MYSQL) {
            return (((Wrapper*)(consTreeNth(((Cons*)(executeSql(connection, wrapString("select version()"), NIL))), 2, 0, 0))));
          }
          else if (testValue002 == KWD_SDBC_ORACLE) {
            return (((Wrapper*)(consTreeNth(((Cons*)(executeSql(connection, wrapString("select * from v$version where banner like 'Oracle%'"), NIL))), 2, 0, 0))));
          }
          else {
          }
        }
      }
      else {
      }
    }
    return (NULL);
  }
}

Wrapper* getServerInfoEvaluatorWrapper(Cons* arguments) {
  return (getServerInfo(((Connection*)(arguments->value)), ((StringWrapper*)(arguments->rest->value))->wrapperValue));
}

const char* guessDbmsName(Connection* connection) {
  { const char* dbmsname = NULL;
    sdbc::NativeConnection* ncon = connection->nativeConnection;

    try {
      executeSql(connection, wrapString("select @@myisam_max_sort_file_size"), NIL);
      dbmsname = "MySQL";
    }
    catch (DatabaseException ) {
    }
    if (dbmsname == NULL) {
      try {
        executeSql(connection, wrapString("select 1 from dual"), NIL);
        dbmsname = "Oracle";
      }
      catch (DatabaseException ) {
      }
    }
    return (dbmsname);
  }
}

Keyword* getDbmsName(Connection* connection) {
  { Keyword* cacheddbmsname = connection->dbmsName;
    StringWrapper* dbmsname = NULL;

    if (((boolean)(cacheddbmsname))) {
      return (cacheddbmsname);
    }
    try {
      dbmsname = ((StringWrapper*)(getServerInfo(connection, "DBMS-NAME")));
    }
    catch (StellaException ) {
    }
    if (((boolean)(dbmsname))) {
      cacheddbmsname = internKeyword(stringUpcase(dbmsname->wrapperValue));
    }
    else {
      cacheddbmsname = internKeyword("UNKNOWN");
    }
    connection->dbmsName = cacheddbmsname;
    return (cacheddbmsname);
  }
}

void printTable(Object* table) {
  if (!((boolean)(table))) {
    return;
  }
  { Cons* constable = ((Cons*)(table));

    { Cons* row = NULL;
      Cons* iter000 = constable;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        row = ((Cons*)(iter000->value));
        std::cout << "row = " << row << std::endl;
      }
    }
  }
}

const char* calendarDateToSqlString(CalendarDate* date) {
  return (date->calendarDateToString(0.0, true, false));
}

DEFINE_STELLA_SPECIAL(oSQL_COMMAND_TEMPLATESo, KeyValueMap* , NULL);

void loadSqlCmdTemplates(const char* file) {
  { InputFileStream* in = NULL;

    try {
      in = openInputFile(file, 0);
      { Object* command = NULL;
        SExpressionIterator* iter000 = sExpressions(in);

        for (; iter000->nextP(); ) {
          command = iter000->value;
          { PropertyList* self000 = newPropertyList();

            self000->thePlist = ((Cons*)(command));
            insertSqlCommandTemplate(self000);
          }
        }
      }
    }
catch (...) {
      if (((boolean)(in))) {
        in->free();
      }
      throw;
    }
    if (((boolean)(in))) {
      in->free();
    }
  }
}

void insertSqlCommandTemplate(PropertyList* templatE) {
  { Object* commandname = templatE->lookup(KWD_SDBC_COMMAND);

    { Object* temp000 = templatE->lookup(KWD_SDBC_DATA_SOURCE);

      { Cons* datasources = ((((boolean)(temp000)) ? temp000 : KWD_SDBC_DEFAULT))->consify();
        Object* sql = templatE->lookup(KWD_SDBC_SQL);
        KeyValueList* templates = ((KeyValueList*)(oSQL_COMMAND_TEMPLATESo->lookup(commandname)));

        if (!((boolean)(commandname))) {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "Missing :command name in SQL template: " << "`" << templatE << "'";
            throw *newStellaException(stream000->theStringReader());
          }
        }
        if (!(stringP(sql))) {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "Illegal or missing :sql specification in SQL template: " << "`" << sql << "'" << std::endl << "   String expected.";
            throw *newStellaException(stream001->theStringReader());
          }
        }
        if (!((boolean)(templates))) {
          templates = newKeyValueList();
          oSQL_COMMAND_TEMPLATESo->insertAt(commandname, templates);
        }
        { Object* datasource = NULL;
          Cons* iter000 = datasources;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            datasource = iter000->value;
            if (datasource == KWD_SDBC_OTHERWISE) {
              datasource = KWD_SDBC_DEFAULT;
            }
            templates->insertAt(datasource, templatE);
          }
        }
      }
    }
  }
}

PropertyList* lookupSqlCmdTemplate(Object* commandname, Object* datasource) {
  { KeyValueList* templates = ((KeyValueList*)(oSQL_COMMAND_TEMPLATESo->lookup(commandname)));
    PropertyList* templatE = NULL;

    if (!((boolean)(templates))) {
      return (NULL);
    }
    templatE = ((PropertyList*)(templates->lookup((((boolean)(datasource)) ? datasource : KWD_SDBC_DEFAULT))));
    if (!((boolean)(templatE))) {
      return (((PropertyList*)(templates->lookup(KWD_SDBC_DEFAULT))));
    }
    else {
      return (templatE);
    }
  }
}

const char* instantiateSqlCmd(Object* cmdname, Object* datasource, int varsAvalues, ...) {
  { PropertyList* templatE = lookupSqlCmdTemplate(cmdname, datasource);
    KeyValueList* variables = newKeyValueList();
    StringWrapper* key = NULL;

    if (!((boolean)(templatE))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Undefined SQL command template: " << "`" << cmdname << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    { va_list iter000;
      int iter000Count = varsAvalues;
      const char* item = NULL;

      va_start(iter000, varsAvalues);
            for  (; (iter000Count--) > 0; ) {
        item = va_arg(iter000, const char*);
        if (((boolean)(key))) {
          variables->insertAt(key, ((item == NULL) ? NULL : wrapString(item)));
          key = NULL;
        }
        else {
          key = wrapString(item);
        }
      }
      va_end(iter000);
    }
    return (instantiateSqlCmdTemplate(((StringWrapper*)(templatE->lookup(KWD_SDBC_SQL)))->wrapperValue, variables));
  }
}

const char* oSQL_CMD_TEMPLATE_VARIABLE_PREFIXo = "#$";

const char* instantiateSqlCmdTemplate(const char* templatE, KeyValueList* variables) {
  { const char* prefix = oSQL_CMD_TEMPLATE_VARIABLE_PREFIXo;
    int prefixlength = strlen(prefix);
    int cursor = 0;
    int variablestart = 0;
    int length = strlen(templatE);
    OutputStringStream* result = NULL;
    const char* variable = NULL;

    if (stringSearch(templatE, prefix, NULL_INTEGER) == NULL_INTEGER) {
      return (templatE);
    }
    result = newOutputStringStream();
    for (;;) {
      variablestart = stringSearch(templatE, prefix, cursor);
      *(result->nativeStream) << stringSubsequence(templatE, cursor, variablestart);
      if (variablestart == NULL_INTEGER) {
        break;
      }
      variable = readSqlCmdTemplateVariable(templatE, variablestart + prefixlength, length, cursor);
      *(result->nativeStream) << instantiateSqlCmdTemplateVariable(variable, variables);
    }
    return (result->theStringReader());
  }
}

const char* readSqlCmdTemplateVariable(const char* templatE, int start, int end, int& _Return1) {
  { int cursor = start;
    boolean escapedP = false;

    if ((cursor >= end) ||
        (!(templatE[cursor] == '{'))) {
    }
    else {
      while (cursor < end) {
        { char c = templatE[cursor];

          if (c == '\\') {
            escapedP = true;
            cursor = cursor + 1;
          }
          else if (c == '}') {
            break;
          }
          else {
          }
          cursor = cursor + 1;
        }
      }
      if (cursor < end) {
        if (escapedP) {
          { const char* _Return0 = unescapeTokenString(stringSubsequence(templatE, start + 1, cursor), '\\', false);

            _Return1 = cursor + 1;
            return (_Return0);
          }
        }
        else {
          { const char* _Return0 = stringSubsequence(templatE, start + 1, cursor);

            _Return1 = cursor + 1;
            return (_Return0);
          }
        }
      }
    }
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "Illegal template variable syntax at position " << "`" << cursor << "'" << " in" << std::endl << std::endl << "    " << "`" << templatE << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

const char* instantiateSqlCmdTemplateVariable(const char* templatevariable, KeyValueList* variables) {
  { int start = 0;
    const char* quotes = "'`\"";
    char quote = NULL_CHARACTER;

    { StringWrapper* var = NULL;
      Object* value = NULL;
      KvCons* iter000 = variables->theKvList;

      for  (; ((boolean)(iter000)); 
            iter000 = iter000->rest) {
        var = ((StringWrapper*)(iter000->key));
        value = iter000->value;
        start = stringSearch(templatevariable, var->wrapperValue, 0);
        if (start != NULL_INTEGER) {
          { const char* varspec = NULL;
            int from = NULL_INTEGER;
            int to = NULL_INTEGER;
            const char* defaulT = NULL;

            varspec = parseSqlCmdTemplateVariableRangeAndDefault(templatevariable, var->wrapperValue, start, from, to, defaulT);
            if ((start > 0) &&
                stringMemberP(quotes, templatevariable[(start - 1)])) {
              quote = templatevariable[(start - 1)];
            }
            { Surrogate* testValue000 = safePrimaryType(value);

              if (subtypeOfStringP(testValue000)) {
                { Object* value000 = value;
                  StringWrapper* value = ((StringWrapper*)(value000));

                  if ((unwrapString(value) == NULL) ||
                      (from > 0)) {
                    return (defaulT);
                  }
                  if (quote != NULL_CHARACTER) {
                    value = wrapString(sqlEscapeString(value->wrapperValue, quote));
                  }
                  return (replaceSubstrings(templatevariable, value->wrapperValue, varspec));
                }
              }
              else if (testValue000 == SGT_SDBC_STELLA_CONS) {
                { Object* value001 = value;
                  Cons* value = ((Cons*)(value001));

                  if ((value == NIL) ||
                      (from >= value->length())) {
                    return (defaulT);
                  }
                  else {
                    { OutputStringStream* result = newOutputStringStream();

                      { StringWrapper* elt = NULL;
                        Cons* iter001 = ((Cons*)(value));
                        int i = NULL_INTEGER;
                        int iter002 = 0;

                        for  (; !(iter001 == NIL); 
                              iter001 = iter001->rest,
                              iter002 = iter002 + 1) {
                          elt = ((StringWrapper*)(iter001->value));
                          i = iter002;
                          if ((i >= from) &&
                              ((to == NULL_INTEGER) ||
                               (i <= to))) {
                            if (quote != NULL_CHARACTER) {
                              elt = wrapString(sqlEscapeString(elt->wrapperValue, quote));
                            }
                            *(result->nativeStream) << replaceSubstrings(templatevariable, elt->wrapperValue, varspec);
                          }
                        }
                      }
                      return (result->theStringReader());
                    }
                  }
                }
              }
              else {
                return (defaulT);
              }
            }
          }
        }
      }
    }
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "Undefined template variable: " << "`" << templatevariable << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

const char* parseSqlCmdTemplateVariableRangeAndDefault(const char* templatevariable, const char* variablename, int start, int& _Return1, int& _Return2, const char*& _Return3) {
  { int variablestart = start;
    int end = strlen(templatevariable);
    int startidx = 0;
    int endidx = 0;
    const char* defaulT = "1=1";
    int cursor = 0;
    Cons* range = NIL;
    const char* element = NULL;
    int nofelements = 0;

    start = start + strlen(variablename);
    if ((start >= end) ||
        (!(templatevariable[start] == '['))) {
      _Return1 = startidx;
      _Return2 = endidx;
      _Return3 = defaulT;
      return (variablename);
    }
    start = start + 1;
    end = stringPosition(templatevariable, ']', start);
    if (end == NULL_INTEGER) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Missing right parenthesis in template variable range: " << "`" << templatevariable << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    cursor = start;
    while (cursor < end) {
      if ((templatevariable[cursor] == ',') &&
          (nofelements < 2)) {
        range = cons(wrapString(stringSubsequence(templatevariable, start, cursor)), range);
        nofelements = nofelements + 1;
        cursor = cursor + 1;
        start = cursor;
      }
      else {
        cursor = cursor + 1;
      }
    }
    nofelements = nofelements + 1;
    range = cons(wrapString(stringSubsequence(templatevariable, start, cursor)), range);
    { StringWrapper* elt = NULL;
      Cons* iter000 = range->reverse();
      int i = NULL_INTEGER;
      int iter001 = 1;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        elt = ((StringWrapper*)(iter000->value));
        i = iter001;
        element = elt->wrapperValue;
        switch (i) {
          case 1: 
            if (i == nofelements) {
              {
                if (stringEqlP(element, "")) {
                  {
                    defaulT = element;
                  }
                }
                else {
                  { boolean alwaysP000 = true;

                    { char chaR = NULL_CHARACTER;
                      const char* vector000 = element;
                      int index000 = 0;
                      int length000 = strlen(vector000);

                      for  (; index000 < length000; 
                            index000 = index000 + 1) {
                        chaR = vector000[index000];
                        if (!(oCHARACTER_TYPE_TABLEo[(int)(unsigned char) chaR] == KWD_SDBC_DIGIT)) {
                          alwaysP000 = false;
                          goto loopExit003;
                        }
                      }
                    }
                    loopExit003:;
                    if (alwaysP000) {
                      {
                        startidx = ((int)(stringToInteger(element)));
                        endidx = startidx;
                      }
                    }
                    else {
                      {
                        defaulT = element;
                      }
                    }
                  }
                }
              }
            }
            else {
              { boolean alwaysP001 = true;

                { char chaR = NULL_CHARACTER;
                  const char* vector001 = element;
                  int index001 = 0;
                  int length001 = strlen(vector001);

                  for  (; index001 < length001; 
                        index001 = index001 + 1) {
                    chaR = vector001[index001];
                    if (!(oCHARACTER_TYPE_TABLEo[(int)(unsigned char) chaR] == KWD_SDBC_DIGIT)) {
                      alwaysP001 = false;
                      goto loopExit004;
                    }
                  }
                }
                loopExit004:;
                if (alwaysP001) {
                  {
                    startidx = ((int)(stringToInteger(element)));
                    endidx = startidx;
                  }
                }
                else {
                  {
                    { OutputStringStream* stream001 = newOutputStringStream();

                      *(stream001->nativeStream) << "Illegal template variable range: " << "`" << templatevariable << "'";
                      throw *newStellaException(stream001->theStringReader());
                    }
                  }
                }
              }
            }
            break;
          case 2: 
            if (i == nofelements) {
              {
                if (stringEqlP(element, "")) {
                  {
                    defaulT = element;
                  }
                }
                else {
                  if (stringEqlP(element, ":")) {
                    {
                      endidx = NULL_INTEGER;
                    }
                  }
                  else {
                    { boolean alwaysP002 = true;

                      { char chaR = NULL_CHARACTER;
                        const char* vector002 = element;
                        int index002 = 0;
                        int length002 = strlen(vector002);

                        for  (; index002 < length002; 
                              index002 = index002 + 1) {
                          chaR = vector002[index002];
                          if (!(oCHARACTER_TYPE_TABLEo[(int)(unsigned char) chaR] == KWD_SDBC_DIGIT)) {
                            alwaysP002 = false;
                            goto loopExit005;
                          }
                        }
                      }
                      loopExit005:;
                      if (alwaysP002) {
                        {
                          endidx = ((int)(stringToInteger(element)));
                        }
                      }
                      else {
                        {
                          defaulT = element;
                        }
                      }
                    }
                  }
                }
              }
            }
            else {
              if (stringEqlP(element, "")) {
                {
                  endidx = startidx;
                }
              }
              else {
                if (stringEqlP(element, ":")) {
                  {
                    endidx = NULL_INTEGER;
                  }
                }
                else {
                  { boolean alwaysP003 = true;

                    { char chaR = NULL_CHARACTER;
                      const char* vector003 = element;
                      int index003 = 0;
                      int length003 = strlen(vector003);

                      for  (; index003 < length003; 
                            index003 = index003 + 1) {
                        chaR = vector003[index003];
                        if (!(oCHARACTER_TYPE_TABLEo[(int)(unsigned char) chaR] == KWD_SDBC_DIGIT)) {
                          alwaysP003 = false;
                          goto loopExit006;
                        }
                      }
                    }
                    loopExit006:;
                    if (alwaysP003) {
                      {
                        endidx = ((int)(stringToInteger(element)));
                      }
                    }
                    else {
                      {
                        { OutputStringStream* stream002 = newOutputStringStream();

                          *(stream002->nativeStream) << "Illegal template variable range: " << "`" << templatevariable << "'";
                          throw *newStellaException(stream002->theStringReader());
                        }
                      }
                    }
                  }
                }
              }
            }
            break;
          case 3: 
            defaulT = element;
            break;
          default:
            { OutputStringStream* stream003 = newOutputStringStream();

              *(stream003->nativeStream) << "`" << i << "'" << " is not a valid case option";
              throw *newStellaException(stream003->theStringReader());
            }
            break;
        }
      }
    }
    { const char* _Return0 = stringSubsequence(templatevariable, variablestart, end + 1);

      _Return1 = startidx;
      _Return2 = endidx;
      _Return3 = defaulT;
      return (_Return0);
    }
  }
}

void testPreparedStatement() {
  try {
    { Connection* con = connect(consList(8, KWD_SDBC_DSN, wrapString("myodbc3"), KWD_SDBC_USER, wrapString("scott"), KWD_SDBC_PASSWORD, wrapString("tiger"), KWD_SDBC_CONNECTIONSTRING, wrapString("jdbc:mysql://localhost:3306/menagerie?user=scott&password=tiger")));
      const char* preparedsql = "insert into customer4 values (?, ?, ?, ?)";
      const char* selectsql = "select * from customer4";
      PreparedStatement* preparedstatement = NULL;
      Cons* result = NULL;

      std::cout << "Table before executing prepared statement:" << std::endl;
      printTable(executeSql(con, wrapString(selectsql), NIL));
      preparedstatement = prepareStatement(con, preparedsql);
      bindParameter(preparedstatement, 1, SGT_SDBC_STELLA_INTEGER, wrapInteger(23));
      bindParameter(preparedstatement, 2, SGT_SDBC_STELLA_STRING, wrapString("k"));
      bindParameter(preparedstatement, 3, SGT_SDBC_STELLA_DOUBLE_FLOAT, wrapFloat(5.3));
      bindParameter(preparedstatement, 4, SGT_SDBC_STELLA_CALENDAR_DATE, stringToCalendarDate("1997-02-14"));
      result = ((Cons*)(executeSql(con, preparedstatement, NIL)));
      bindParameter(preparedstatement, 1, SGT_SDBC_STELLA_INTEGER, wrapInteger(24));
      bindParameter(preparedstatement, 2, SGT_SDBC_STELLA_STRING, NULL);
      bindParameter(preparedstatement, 3, SGT_SDBC_STELLA_DOUBLE_FLOAT, NULL);
      bindParameter(preparedstatement, 4, SGT_SDBC_STELLA_CALENDAR_DATE, NULL);
      result = ((Cons*)(executeSql(con, preparedstatement, NIL)));
      std::cout << "Table after executing prepared statements:" << std::endl;
      printTable(executeSql(con, wrapString(selectsql), NIL));
    }
  }
  catch (DatabaseException& _e) {
    DatabaseException* e = &_e;

    std::cout << "Caught Database Exception: " << exceptionMessage(e) << std::endl;
  }
}

void testTransactions() {
  std::cout << "testing transactions..." << std::endl;
  try {
    { Connection* con = connect(consList(8, KWD_SDBC_DSN, wrapString("myodbc3"), KWD_SDBC_USER, wrapString("scott"), KWD_SDBC_PASSWORD, wrapString("tiger"), KWD_SDBC_CONNECTIONSTRING, wrapString("jdbc:mysql://localhost:3306/menagerie?user=scott&password=tiger")));
      const char* selectsql = "select * from customer2";
      const char* insertsql1 = "insert into customer2 values (28, 'aa')";
      const char* insertsql2 = "insert into customer2 values (29, 'z')";

      setAutoCommit(con, false);
      std::cout << "Table before insert:" << std::endl;
      printTable(executeSql(con, wrapString(selectsql), NIL));
      executeSql(con, wrapString(insertsql1), NIL);
      std::cout << "Table after insert1:" << std::endl;
      printTable(executeSql(con, wrapString(selectsql), NIL));
      commit(con);
      std::cout << "Table after commit:" << std::endl;
      printTable(executeSql(con, wrapString(selectsql), NIL));
      executeSql(con, wrapString(insertsql2), NIL);
      std::cout << "Table after insert2:" << std::endl;
      printTable(executeSql(con, wrapString(selectsql), NIL));
      rollback(con);
      std::cout << "Table after rollback:" << std::endl;
      printTable(executeSql(con, wrapString(selectsql), NIL));
      disconnect(con);
    }
  }
  catch (DatabaseException& _e) {
    DatabaseException* e = &_e;

    std::cout << "Caught Database Exception: " << exceptionMessage(e) << std::endl;
  }
}

void testResultSet() {
  std::cout << "Testing result set..." << std::endl;
  try {
    { Connection* con = connect(consList(8, KWD_SDBC_DSN, wrapString("myodbc3"), KWD_SDBC_USER, wrapString("scott"), KWD_SDBC_PASSWORD, wrapString("tiger"), KWD_SDBC_CONNECTIONSTRING, wrapString("jdbc:mysql://localhost:3306/menagerie?user=scott&password=tiger")));
      Cons* types = listO(7, SGT_SDBC_STELLA_INTEGER, SGT_SDBC_STELLA_DOUBLE_FLOAT, SGT_SDBC_STELLA_LONG_INTEGER, SYM_SDBC_STELLA_NULL, SGT_SDBC_STELLA_STRING, SGT_SDBC_STELLA_CALENDAR_DATE, NIL);
      const char* sql = "select intcol, floatcol, bigintcol, blobcol, varcharcol, datecol from typetest";
      ResultSetIterator* result = getResultSet(con, sql, 2, KWD_SDBC_TYPES, types);

      { Cons* row = NULL;
        ResultSetIterator* iter000 = result;

        for (; iter000->nextP(); ) {
          row = ((Cons*)(iter000->value));
          std::cout << "Retrieved row : " << ((Cons*)(result->value)) << std::endl;
        }
      }
      disconnect(con);
    }
  }
  catch (DatabaseException& _e) {
    DatabaseException* e = &_e;

    std::cout << "Caught Database Exception: " << exceptionMessage(e) << std::endl;
  }
}

void testRetrieveAll() {
  std::cout << "Testing retrieve all..." << std::endl;
  try {
    { Connection* con = connect(consList(8, KWD_SDBC_DSN, wrapString("myodbc3"), KWD_SDBC_USER, wrapString("scott"), KWD_SDBC_PASSWORD, wrapString("tiger"), KWD_SDBC_CONNECTIONSTRING, wrapString("jdbc:mysql://localhost:3306/menagerie?user=scott&password=tiger")));
      const char* sql = "select intcol, floatcol, bigintcol, blobcol, varcharcol, datecol from typetest";
      Cons* types = listO(7, SGT_SDBC_STELLA_INTEGER, SGT_SDBC_STELLA_DOUBLE_FLOAT, SGT_SDBC_STELLA_LONG_INTEGER, SYM_SDBC_STELLA_NULL, SGT_SDBC_STELLA_STRING, SGT_SDBC_STELLA_CALENDAR_DATE, NIL);
      Object* result = executeSql(con, wrapString(sql), consList(2, KWD_SDBC_TYPES, types));

      if (((boolean)(result))) {
        printTable(result);
      }
      disconnect(con);
      std::cout << "connection string: " << con << std::endl;
    }
  }
  catch (DatabaseException& _e) {
    DatabaseException* e = &_e;

    std::cout << "Caught Database Exception: " << exceptionMessage(e) << std::endl;
  }
}

int main() {
  startupSdbcSystem();
  std::cout << "Start..." << std::endl;
  testRetrieveAll();
  testResultSet();
  testTransactions();
  testPreparedStatement();
  std::cout << "done!" << std::endl;
  return (1);
}

void helpStartupSdbc1() {
  {
    KWD_SDBC_LOG_LEVELS = ((Keyword*)(internRigidSymbolWrtModule("LOG-LEVELS", NULL, 2)));
    KWD_SDBC_LEVEL = ((Keyword*)(internRigidSymbolWrtModule("LEVEL", NULL, 2)));
    KWD_SDBC_NONE = ((Keyword*)(internRigidSymbolWrtModule("NONE", NULL, 2)));
    KWD_SDBC_MAX_WIDTH = ((Keyword*)(internRigidSymbolWrtModule("MAX-WIDTH", NULL, 2)));
    SGT_SDBC_SDBC_CONNECTION = ((Surrogate*)(internRigidSymbolWrtModule("CONNECTION", NULL, 1)));
    SYM_SDBC_SDBC_CONNECTION_STRING = ((Symbol*)(internRigidSymbolWrtModule("CONNECTION-STRING", NULL, 0)));
    SYM_SDBC_SDBC_PROTOCOL = ((Symbol*)(internRigidSymbolWrtModule("PROTOCOL", NULL, 0)));
    SYM_SDBC_SDBC_DBMS_NAME = ((Symbol*)(internRigidSymbolWrtModule("DBMS-NAME", NULL, 0)));
    SYM_SDBC_SDBC_STATEMENT = ((Symbol*)(internRigidSymbolWrtModule("STATEMENT", NULL, 0)));
    SYM_SDBC_SDBC_AUTO_COMMITp = ((Symbol*)(internRigidSymbolWrtModule("AUTO-COMMIT?", NULL, 0)));
    SYM_SDBC_SDBC_CREATION_TIME = ((Symbol*)(internRigidSymbolWrtModule("CREATION-TIME", NULL, 0)));
    SYM_SDBC_SDBC_LAST_ACCESS_TIME = ((Symbol*)(internRigidSymbolWrtModule("LAST-ACCESS-TIME", NULL, 0)));
    SYM_SDBC_SDBC_RENEWAL_TIME = ((Symbol*)(internRigidSymbolWrtModule("RENEWAL-TIME", NULL, 0)));
    SGT_SDBC_SDBC_PREPARED_STATEMENT = ((Surrogate*)(internRigidSymbolWrtModule("PREPARED-STATEMENT", NULL, 1)));
    SYM_SDBC_SDBC_CONNECTION = ((Symbol*)(internRigidSymbolWrtModule("CONNECTION", NULL, 0)));
    SYM_SDBC_SDBC_SQL = ((Symbol*)(internRigidSymbolWrtModule("SQL", NULL, 0)));
    SYM_SDBC_STELLA_PARAMETERS = ((Symbol*)(internRigidSymbolWrtModule("PARAMETERS", getStellaModule("/STELLA", true), 0)));
    SYM_SDBC_SDBC_RDBMS_ROW = ((Symbol*)(internRigidSymbolWrtModule("RDBMS-ROW", NULL, 0)));
    SGT_SDBC_SDBC_RESULT_SET_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("RESULT-SET-ITERATOR", NULL, 1)));
    SYM_SDBC_SDBC_TYPES = ((Symbol*)(internRigidSymbolWrtModule("TYPES", NULL, 0)));
    KWD_SDBC_PROTOCOL = ((Keyword*)(internRigidSymbolWrtModule("PROTOCOL", NULL, 2)));
    KWD_SDBC_SERVER_TYPE = ((Keyword*)(internRigidSymbolWrtModule("SERVER-TYPE", NULL, 2)));
    KWD_SDBC_LOW = ((Keyword*)(internRigidSymbolWrtModule("LOW", NULL, 2)));
    KWD_SDBC_CONNECTION_STRING = ((Keyword*)(internRigidSymbolWrtModule("CONNECTION-STRING", NULL, 2)));
    KWD_SDBC_HOST = ((Keyword*)(internRigidSymbolWrtModule("HOST", NULL, 2)));
    KWD_SDBC_PORT = ((Keyword*)(internRigidSymbolWrtModule("PORT", NULL, 2)));
    KWD_SDBC_DB_NAME = ((Keyword*)(internRigidSymbolWrtModule("DB-NAME", NULL, 2)));
    KWD_SDBC_DSN = ((Keyword*)(internRigidSymbolWrtModule("DSN", NULL, 2)));
    KWD_SDBC_USER = ((Keyword*)(internRigidSymbolWrtModule("USER", NULL, 2)));
    KWD_SDBC_PASSWORD = ((Keyword*)(internRigidSymbolWrtModule("PASSWORD", NULL, 2)));
    KWD_SDBC_WHITE_SPACE = ((Keyword*)(internRigidSymbolWrtModule("WHITE-SPACE", NULL, 2)));
    KWD_SDBC_LETTER = ((Keyword*)(internRigidSymbolWrtModule("LETTER", NULL, 2)));
    SYM_SDBC_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", getStellaModule("/STELLA", true), 0)));
    SGT_SDBC_STELLA_CALENDAR_DATE = ((Surrogate*)(internRigidSymbolWrtModule("CALENDAR-DATE", getStellaModule("/STELLA", true), 1)));
    SGT_SDBC_STELLA_STRING = ((Surrogate*)(internRigidSymbolWrtModule("STRING", getStellaModule("/STELLA", true), 1)));
    SGT_SDBC_STELLA_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER", getStellaModule("/STELLA", true), 1)));
    SGT_SDBC_STELLA_LONG_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("LONG-INTEGER", getStellaModule("/STELLA", true), 1)));
    SGT_SDBC_STELLA_DOUBLE_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("DOUBLE-FLOAT", getStellaModule("/STELLA", true), 1)));
    KWD_SDBC_TYPES = ((Keyword*)(internRigidSymbolWrtModule("TYPES", NULL, 2)));
    KWD_SDBC_HIGH = ((Keyword*)(internRigidSymbolWrtModule("HIGH", NULL, 2)));
    KWD_SDBC_STRING_CONSTANT = ((Keyword*)(internRigidSymbolWrtModule("STRING-CONSTANT", NULL, 2)));
    KWD_SDBC_IDENTIFIER = ((Keyword*)(internRigidSymbolWrtModule("IDENTIFIER", NULL, 2)));
    KWD_SDBC_MYSQL = ((Keyword*)(internRigidSymbolWrtModule("MYSQL", NULL, 2)));
    KWD_SDBC_NULL = ((Keyword*)(internRigidSymbolWrtModule("NULL", NULL, 2)));
    SYM_SDBC_STELLA_DEFAULT = ((Symbol*)(internRigidSymbolWrtModule("DEFAULT", getStellaModule("/STELLA", true), 0)));
    KWD_SDBC_DEFAULT = ((Keyword*)(internRigidSymbolWrtModule("DEFAULT", NULL, 2)));
    KWD_SDBC_ORACLE = ((Keyword*)(internRigidSymbolWrtModule("ORACLE", NULL, 2)));
    SGT_SDBC_STELLA_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_SDBC_SDBC_TABLE_INFO = ((Surrogate*)(internRigidSymbolWrtModule("TABLE-INFO", NULL, 1)));
    SYM_SDBC_SDBC_DATABASE = ((Symbol*)(internRigidSymbolWrtModule("DATABASE", NULL, 0)));
    SYM_SDBC_SDBC_CATALOG = ((Symbol*)(internRigidSymbolWrtModule("CATALOG", NULL, 0)));
    SYM_SDBC_SDBC_SCHEMA = ((Symbol*)(internRigidSymbolWrtModule("SCHEMA", NULL, 0)));
    SYM_SDBC_STELLA_NAME = ((Symbol*)(internRigidSymbolWrtModule("NAME", getStellaModule("/STELLA", true), 0)));
    SYM_SDBC_STELLA_TYPE = ((Symbol*)(internRigidSymbolWrtModule("TYPE", getStellaModule("/STELLA", true), 0)));
    SYM_SDBC_SDBC_REMARKS = ((Symbol*)(internRigidSymbolWrtModule("REMARKS", NULL, 0)));
    SYM_SDBC_SDBC_COLUMNS = ((Symbol*)(internRigidSymbolWrtModule("COLUMNS", NULL, 0)));
    SGT_SDBC_SDBC_COLUMN_INFO = ((Surrogate*)(internRigidSymbolWrtModule("COLUMN-INFO", NULL, 1)));
    SYM_SDBC_STELLA_TABLE_NAME = ((Symbol*)(internRigidSymbolWrtModule("TABLE-NAME", getStellaModule("/STELLA", true), 0)));
    SYM_SDBC_SDBC_DATA_TYPE = ((Symbol*)(internRigidSymbolWrtModule("DATA-TYPE", NULL, 0)));
    SYM_SDBC_SDBC_DATA_TYPE_NAME = ((Symbol*)(internRigidSymbolWrtModule("DATA-TYPE-NAME", NULL, 0)));
  }
}

void helpStartupSdbc2() {
  {
    SYM_SDBC_SDBC_COLUMN_SIZE = ((Symbol*)(internRigidSymbolWrtModule("COLUMN-SIZE", NULL, 0)));
    SYM_SDBC_SDBC_BUFFER_LENGTH = ((Symbol*)(internRigidSymbolWrtModule("BUFFER-LENGTH", NULL, 0)));
    SYM_SDBC_SDBC_DECIMAL_DIGITS = ((Symbol*)(internRigidSymbolWrtModule("DECIMAL-DIGITS", NULL, 0)));
    SYM_SDBC_SDBC_RADIX = ((Symbol*)(internRigidSymbolWrtModule("RADIX", NULL, 0)));
    SYM_SDBC_SDBC_NULLABLEp = ((Symbol*)(internRigidSymbolWrtModule("NULLABLE?", NULL, 0)));
    SYM_SDBC_SDBC_IS_NULLABLEp = ((Symbol*)(internRigidSymbolWrtModule("IS-NULLABLE?", NULL, 0)));
    SYM_SDBC_STELLA_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("DOCUMENTATION", getStellaModule("/STELLA", true), 0)));
    SYM_SDBC_STELLA_DEFAULT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("DEFAULT-VALUE", getStellaModule("/STELLA", true), 0)));
    SYM_SDBC_SDBC_SQL_DATA_TYPE = ((Symbol*)(internRigidSymbolWrtModule("SQL-DATA-TYPE", NULL, 0)));
    SYM_SDBC_SDBC_SQL_DATETIME_SUB = ((Symbol*)(internRigidSymbolWrtModule("SQL-DATETIME-SUB", NULL, 0)));
    SYM_SDBC_SDBC_CHAR_OCTET_LENGTH = ((Symbol*)(internRigidSymbolWrtModule("CHAR-OCTET-LENGTH", NULL, 0)));
    SYM_SDBC_SDBC_ORDINAL_POSITION = ((Symbol*)(internRigidSymbolWrtModule("ORDINAL-POSITION", NULL, 0)));
    KWD_SDBC_COMMAND = ((Keyword*)(internRigidSymbolWrtModule("COMMAND", NULL, 2)));
    KWD_SDBC_DATA_SOURCE = ((Keyword*)(internRigidSymbolWrtModule("DATA-SOURCE", NULL, 2)));
    KWD_SDBC_SQL = ((Keyword*)(internRigidSymbolWrtModule("SQL", NULL, 2)));
    KWD_SDBC_OTHERWISE = ((Keyword*)(internRigidSymbolWrtModule("OTHERWISE", NULL, 2)));
    SGT_SDBC_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
    KWD_SDBC_DIGIT = ((Keyword*)(internRigidSymbolWrtModule("DIGIT", NULL, 2)));
    KWD_SDBC_CONNECTIONSTRING = ((Keyword*)(internRigidSymbolWrtModule("CONNECTIONSTRING", NULL, 2)));
    SYM_SDBC_SDBC_STARTUP_SDBC = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-SDBC", NULL, 0)));
    SYM_SDBC_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupSdbc3() {
  {
    defineClassFromStringifiedSource("NATIVE-CONNECTION", "(DEFCLASS NATIVE-CONNECTION () :ABSTRACT? TRUE :CPP-NATIVE-TYPE \"sdbc::NativeConnection*\" :JAVA-NATIVE-TYPE \"edu.isi.sdbc.NativeConnection\" :CL-NATIVE-TYPE \"#+:EXCL DB-INTERFACE::ODBC-DB #+:CLSQL CLSQL:DATABASE  #-(OR :EXCL :CLSQL) CL:STANDARD-OBJECT\")");
    defineClassFromStringifiedSource("NATIVE-RESULT-SET", "(DEFCLASS NATIVE-RESULT-SET () :ABSTRACT? TRUE :CPP-NATIVE-TYPE \"NativeResultSet*\" :JAVA-NATIVE-TYPE \"edu.isi.sdbc.ResultSet\" :CL-NATIVE-TYPE \"#+:EXCL DB-INTERFACE::QUERY #+:CLSQL CL:LIST  #-(OR :EXCL :CLSQL) CL:STANDARD-OBJECT\")");
    { Class* clasS = defineClassFromStringifiedSource("CONNECTION", "(DEFCLASS CONNECTION (STANDARD-OBJECT) :PUBLIC-SLOTS ((NATIVE-CONNECTION :TYPE NATIVE-CONNECTION :PUBLIC? TRUE) (CONNECTION-STRING :TYPE STRING) (PROTOCOL :TYPE STRING) (DBMS-NAME :TYPE KEYWORD :DOCUMENTATION \"Indicates to what kind of DBMS we are connected.\") (STATEMENT :TYPE PREPARED-STATEMENT :DOCUMENTATION \"Prepared statement associated with this connection.\") (AUTO-COMMIT? :TYPE BOOLEAN :INITIALLY TRUE :DOCUMENTATION \"State of connection's auto-commit feature.\") (CREATION-TIME :TYPE CALENDAR-DATE :DOCUMENTATION \"Time at which connection was created.\") (LAST-ACCESS-TIME :TYPE CALENDAR-DATE :DOCUMENTATION \"Time at which connection was last accessed.\") (RENEWAL-TIME :TYPE CALENDAR-DATE :DOCUMENTATION \"Time at or after which connection should be renewed.\")) :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"|CON|\\\"\" (CONNECTION-STRING SELF) \"\\\"\"))");

      clasS->classConstructorCode = ((cpp_function_code)(&newConnection));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessConnectionSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("PREPARED-STATEMENT", "(DEFCLASS PREPARED-STATEMENT (STANDARD-OBJECT) :SLOTS ((CONNECTION :TYPE CONNECTION) (STATEMENT :TYPE NATIVE-PREPARED-STATEMENT) (SQL :TYPE STRING) (PARAMETERS :TYPE (KEY-VALUE-LIST OF INTEGER-WRAPPER CONS) :INITIALLY (NEW KEY-VALUE-LIST) :DOCUMENTATION \"Stores parameters bound so far to support connection renewal.\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newPreparedStatement));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessPreparedStatementSlotValue));
    }
    defineClassFromStringifiedSource("NATIVE-PREPARED-STATEMENT", "(DEFCLASS NATIVE-PREPARED-STATEMENT () :ABSTRACT? TRUE :JAVA-NATIVE-TYPE \"java.sql.PreparedStatement\")");
    { Class* clasS = defineClassFromStringifiedSource("DATABASE-EXCEPTION", "(DEFCLASS DATABASE-EXCEPTION (STELLA-EXCEPTION))");

      clasS->classConstructorCode = ((cpp_function_code)(&newDatabaseException));
    }
    defineStellaTypeFromStringifiedSource("(DEFTYPE RDBMS-ROW (CONS OF STRING-WRAPPER))");
    { Class* clasS = defineClassFromStringifiedSource("RESULT-SET-ITERATOR", "(DEFCLASS RESULT-SET-ITERATOR (ITERATOR) :DOCUMENTATION \"Iterator class for a table returned by a SQL query.\" :PARAMETERS ((ANY-VALUE :TYPE RDBMS-ROW)) :PUBLIC-SLOTS ((RESULT-SET :TYPE NATIVE-RESULT-SET) (TYPES :TYPE CONS)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newResultSetIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessResultSetIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("TABLE-INFO", "(DEFCLASS TABLE-INFO (STANDARD-OBJECT) :PUBLIC-SLOTS ((DATABASE :TYPE STRING) (CATALOG :RENAMES DATABASE) (SCHEMA :TYPE STRING) (NAME :TYPE STRING) (TYPE :TYPE STRING) (REMARKS :TYPE STRING) (COLUMNS :TYPE (LIST OF COLUMN-INFO))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newTableInfo));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessTableInfoSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("COLUMN-INFO", "(DEFCLASS COLUMN-INFO (STANDARD-OBJECT) :PUBLIC-SLOTS ((DATABASE :TYPE STRING) (CATALOG :RENAMES DATABASE) (SCHEMA :TYPE STRING) (TABLE-NAME :TYPE STRING) (NAME :TYPE STRING) (DATA-TYPE :TYPE INTEGER :DOCUMENTATION \"SQL type from java.sql.Types.\") (DATA-TYPE-NAME :TYPE STRING :DOCUMENTATION \"Data source dependent type name, for a UDT the type name is fully qualified.\") (COLUMN-SIZE :TYPE INTEGER :DOCUMENTATION \"Column size. For char or date types this is the maximum number of characters,\nfor numeric or decimal types this is precision.\") (BUFFER-LENGTH :TYPE INTEGER :DOCUMENTATION \"Not used.\") (DECIMAL-DIGITS :TYPE INTEGER :DOCUMENTATION \"The number of fractional digits.\") (RADIX :TYPE INTEGER :DOCUMENTATION \"Radix (typically either 10 or 2).\") (NULLABLE? :TYPE THREE-VALUED-BOOLEAN :DOCUMENTATION \"TRUE means definitely allows NULL values, FALSE means might not allow\nNULL values, NULL means nullability unknown.\") (IS-NULLABLE? :TYPE THREE-VALUED-BOOLEAN :DOCUMENTATION \"TRUE means might allow N" "ULL values, FALSE means definitely does not\nallow NULL values, NULL means nullability unknown.\") (DOCUMENTATION :TYPE STRING :DOCUMENTATION \"Comment describing column (may be null).\") (REMARKS :RENAMES DOCUMENTATION) (DEFAULT-VALUE :TYPE STRING) (SQL-DATA-TYPE :TYPE INTEGER :DOCUMENTATION \"Not used.\") (SQL-DATETIME-SUB :TYPE INTEGER :DOCUMENTATION \"Not used.\") (CHAR-OCTET-LENGTH :TYPE INTEGER :DOCUMENTATION \"For char types the maximum number of bytes in the column.\") (ORDINAL-POSITION :TYPE INTEGER :DOCUMENTATION \"Index of column in table (starting at 1).\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newColumnInfo));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessColumnInfoSlotValue));
    }
  }
}

void helpStartupSdbc4() {
  {
    defineFunctionObject("CONNECT", "(DEFUN (CONNECT CONNECTION) (|&REST| (KEYS-AND-VALUES OBJECT)) :DOCUMENTATION \"Create a connection to a database.  Currently-supported parameters\nare (values need to be strings):\n  :PROTOCOL          - \\\"ODBC\\\", \\\"JDBC\\\", \\\"CLSQL\\\" or \\\"MYSQL\\\" (defaults to \\\"ODBC\\\")\n  :SERVER-TYPE       - Type of database server (for JDBC strings)\n  :DSN               - Name of ODBC Datasource\n  :DB-NAME           - Name of physical database\n  :USER              - Database user id.\n  :PASSWORD          - Database password\n  :HOST              - Host database server runs on\n  :PORT              - Port to use to connect to the server\n  :CONNECTION-STRING - Connection string to be used by ODBC or JDBC drivers\n                       instead of DSN, USER, PASSWORD, etc.\nA DATABASE-EXCEPTION is thrown if the connection is unsuccessful.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&connect)), ((cpp_function_code)(&connectEvaluatorWrapper)));
    defineFunctionObject("CALL-CONNECT", "(DEFUN (CALL-CONNECT CONNECTION) ((KEYS-AND-VALUES CONS)) :PUBLIC? TRUE :DOCUMENTATION \"Functional interface to `connect'.  See its documentation\")", ((cpp_function_code)(&callConnect)), NULL);
    defineFunctionObject("*DB-CONNECTION-RENEWAL-INTERVAL*-SETTER", "(DEFUN (*DB-CONNECTION-RENEWAL-INTERVAL*-SETTER INTEGER) ((VALUE INTEGER)))", ((cpp_function_code)(&ODbConnectionRenewalIntervalOSetter)), NULL);
    defineFunctionObject("GET-MAX-CONNECTION-LIFETIME", "(DEFUN (GET-MAX-CONNECTION-LIFETIME INTEGER) ((CON CONNECTION)))", ((cpp_function_code)(&getMaxConnectionLifetime)), NULL);
    defineFunctionObject("MAYBE-RENEW-CONNECTION", "(DEFUN MAYBE-RENEW-CONNECTION ((CON CONNECTION)))", ((cpp_function_code)(&maybeRenewConnection)), NULL);
    defineFunctionObject("JDBC-CONNECTION-STRING?", "(DEFUN (JDBC-CONNECTION-STRING? BOOLEAN) ((STRING STRING)))", ((cpp_function_code)(&jdbcConnectionStringP)), NULL);
    defineFunctionObject("MAKE-JDBC-CONNECTION-STRING", "(DEFUN (MAKE-JDBC-CONNECTION-STRING STRING) ((OPTIONS (PROPERTY-LIST OF KEYWORD OBJECT))))", ((cpp_function_code)(&makeJdbcConnectionString)), NULL);
    defineFunctionObject("ODBC-CONNECTION-STRING?", "(DEFUN (ODBC-CONNECTION-STRING? BOOLEAN) ((STRING STRING)))", ((cpp_function_code)(&odbcConnectionStringP)), NULL);
    defineFunctionObject("MAKE-ODBC-CONNECTION-STRING", "(DEFUN (MAKE-ODBC-CONNECTION-STRING STRING) ((OPTIONS (PROPERTY-LIST OF KEYWORD STRING-WRAPPER))))", ((cpp_function_code)(&makeOdbcConnectionString)), NULL);
    defineFunctionObject("CL-NATIVE-ODBC-CONNECT", "(DEFUN (CL-NATIVE-ODBC-CONNECT NATIVE-CONNECTION STRING) ((CONNECTIONSTRING STRING)))", ((cpp_function_code)(&clNativeOdbcConnect)), NULL);
    defineFunctionObject("CL-NATIVE-CLSQL-CONNECT", "(DEFUN (CL-NATIVE-CLSQL-CONNECT NATIVE-CONNECTION STRING) ((OPTIONS (PROPERTY-LIST OF KEYWORD STRING-WRAPPER)) (SERVER-TYPE STRING)))", ((cpp_function_code)(&clNativeClsqlConnect)), NULL);
    defineFunctionObject("DISCONNECT", "(DEFUN DISCONNECT ((CONNECTION CONNECTION)) :DOCUMENTATION \"Disconnect `connection' from a database.  A DATABASE-EXCEPTION is thrown if\nthe disconnect is unsuccessful.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&disconnect)), NULL);
    defineFunctionObject("CL-NATIVE-DISCONNECT", "(DEFUN CL-NATIVE-DISCONNECT ((NATIVE-CONNECTION NATIVE-CONNECTION)))", ((cpp_function_code)(&clNativeDisconnect)), NULL);
    defineFunctionObject("CL-NATIVE-ODBC-DISCONNECT", "(DEFUN CL-NATIVE-ODBC-DISCONNECT ((NATIVECONNECTION NATIVE-CONNECTION)))", ((cpp_function_code)(&clNativeOdbcDisconnect)), NULL);
    defineFunctionObject("CL-NATIVE-CLSQL-DISCONNECT", "(DEFUN CL-NATIVE-CLSQL-DISCONNECT ((NATIVE-CONNECTION NATIVE-CONNECTION)))", ((cpp_function_code)(&clNativeClsqlDisconnect)), NULL);
    defineFunctionObject("SQL-QUERY?", "(DEFUN (SQL-QUERY? BOOLEAN) ((SQL-EXPRESSION STRING)) :DOCUMENTATION \"Return `true' if `sql-expression' is a SQL command string which returns\nvalues.\" :PUBLIC? FALSE)", ((cpp_function_code)(&sqlQueryP)), NULL);
    defineFunctionObject("STELLIFY-WITH-NIL-TO-NULL", "(DEFUN (STELLIFY-WITH-NIL-TO-NULL OBJECT) ((SELF OBJECT)) :DOCUMENTATION \"Convert a Lisp object into a STELLA object.\" :PUBLIC? TRUE)", ((cpp_function_code)(&stellifyWithNilToNull)), NULL);
    defineFunctionObject("CL-TRANSLATE-SQL-PARAMETER-TYPE-SPECIFIER", "(DEFUN (CL-TRANSLATE-SQL-PARAMETER-TYPE-SPECIFIER OBJECT) ((STELLATYPE OBJECT)))", ((cpp_function_code)(&clTranslateSqlParameterTypeSpecifier)), NULL);
    defineFunctionObject("CL-TRANSLATE-SQL-TYPE-SPECIFIER", "(DEFUN (CL-TRANSLATE-SQL-TYPE-SPECIFIER OBJECT) ((STELLATYPE OBJECT)))", ((cpp_function_code)(&clTranslateSqlTypeSpecifier)), NULL);
    defineFunctionObject("CL-TRANSLATE-SQL-TYPE-SPECIFIERS", "(DEFUN (CL-TRANSLATE-SQL-TYPE-SPECIFIERS CONS) ((STELLATYPES CONS)))", ((cpp_function_code)(&clTranslateSqlTypeSpecifiers)), NULL);
    defineFunctionObject("EXECUTE-SQL", "(DEFUN (EXECUTE-SQL OBJECT) ((CONNECTION CONNECTION) (SQL OBJECT) |&REST| (OPTIONS OBJECT)) :PUBLIC? TRUE :COMMAND? TRUE :DOCUMENTATION \"Execute a SQL statement, and return a table as the reuslt\n                  of a SQL query (represented as a (CONS OF (CONS OF OBJECT))),\n                  or NULL as the result of a successfull SQL insert, update,\n                  delete or other command.\n                  `sql' can either be a string representing a SQL command or\n                  a PREPARED-STATEMENT.\n                  Options include: \n                     :types <typelist>, where <typelist> is a cons list of surrogates\n                  specifying the expected Stella types.  Legal surrogate values are\n                  @INTEGER, @LONG-INTEGER, @DOUBLE-FLOAT, @CALENDAR-DATE, @STRING, and\n                  NULL.  If NULL is specified, values are returned as strings.\n                  A DATABASE-EXCEPTION is thrown if execution is unsuccessful.\")", ((cpp_function_code)(&executeSql)), ((cpp_function_code)(&executeSqlEvaluatorWrapper)));
    defineFunctionObject("CL-EXECUTE-SQL", "(DEFUN (CL-EXECUTE-SQL OBJECT) ((CONNECTION NATIVE-CONNECTION) (SQL STRING) (TYPES CONS)))", ((cpp_function_code)(&clExecuteSql)), NULL);
    defineFunctionObject("CL-DO-EXECUTE-PREPARED-STATEMENT", "(DEFUN (CL-DO-EXECUTE-PREPARED-STATEMENT OBJECT) ((CONNECTION NATIVE-CONNECTION) (SQL PREPARED-STATEMENT)))", ((cpp_function_code)(&clDoExecutePreparedStatement)), NULL);
    defineFunctionObject("GET-RESULT-SET", "(DEFUN (GET-RESULT-SET RESULT-SET-ITERATOR) ((CONNECTION CONNECTION) (SQL STRING) |&REST| (OPTIONS OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Execute a SQL query, and return a ResultSet object.\n                  Options include: \n                     :types <typelist>, where <typelist> is a cons list of surrogates\n                  specifying the expected Stella types.  Legal surrogate values are\n                  @INTEGER, @LONG-INTEGER, @DOUBLE-FLOAT, @CALENDAR-DATE, @STRING, and\n                  NULL.  If NULL is specified, values are returned as strings.\n                  A DATABASE-EXCEPTION is thrown if execution is unsuccessful.\")", ((cpp_function_code)(&getResultSet)), NULL);
    defineFunctionObject("CL-GET-NATIVE-RESULT-SET", "(DEFUN (CL-GET-NATIVE-RESULT-SET NATIVE-RESULT-SET) ((CONNECTION NATIVE-CONNECTION) (SQL STRING) (TYPES CONS)))", ((cpp_function_code)(&clGetNativeResultSet)), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF RESULT-SET-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&ResultSetIterator::nextP))), NULL);
    defineFunctionObject("SQL-ESCAPE-STRING", "(DEFUN (SQL-ESCAPE-STRING STRING) ((VALUE STRING) (QUOTECHAR CHARACTER)))", ((cpp_function_code)(&sqlEscapeString)), NULL);
    defineFunctionObject("SQL-QUOTE-CHARACTER", "(DEFUN (SQL-QUOTE-CHARACTER CHARACTER) ((DBMS-NAME KEYWORD) (LEXICALTYPE KEYWORD)))", ((cpp_function_code)(&sqlQuoteCharacter)), NULL);
    defineFunctionObject("PRINT-VALUE-LIST", "(DEFUN PRINT-VALUE-LIST ((STREAM OUTPUT-STREAM) (VALUES CONS) (QUOTECHAR CHARACTER)))", ((cpp_function_code)(&printValueList)), NULL);
    defineFunctionObject("INSERT-ROW", "(DEFUN INSERT-ROW ((CONNECTION CONNECTION) (TABLE STRING) (COLUMNS (CONS OF STRING-WRAPPER)) (VALUES CONS)) :DOCUMENTATION \"Insert a row of `values' into `table'.  `columns'\ncan be NULL or NIL in which case `values' must be suppied for all\ncolumns.  If `columns' are given `values' will be only inserted in\nthe specified columns.  Table and column names will be quoted which\nmeans their casing must match exactly their definition (no case\nconversion will be performed).  Supplied `values' can be strings,\nintegers or floats.  Strings will be quoted and escaped appropriately.\nThe values NULL, :NULL or (quote NULL) translate into NULL.  The\nvalues :DEFAULT or (quote DEFAULT) translate into DEFAULT.  Arbitrary\nunquoted strings can be generated via VERBATIM-STRING-WRAPPERs as\nvalues (e.g., for something like `seq.nextval' in Oracle).\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&insertRow)), ((cpp_function_code)(&insertRowEvaluatorWrapper)));
    defineFunctionObject("INSERT-ROWS", "(DEFUN INSERT-ROWS ((CONNECTION CONNECTION) (TABLE STRING) (COLUMNS (CONS OF STRING-WRAPPER)) (ROWS (CONS OF RDBMS-ROW))) :DOCUMENTATION \"Insert a set of `rows' into `table'.  `columns'\ncan be NULL or NIL in which case values must be suppied for all\ncolumns.  If `columns' are given `values' will be only inserted in\nthe specified columns.  Table and column names will be quoted which\nmeans their casing must match exactly their definition (no case\nconversion will be performed).  See `insert-row' for a description\nof supported value formats.  DEFAULT values are currently not supported\nfor Oracle!  This function performs a fairly efficient multi-row\ninsert which is significantly faster than inserting rows one by one.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&insertRows)), ((cpp_function_code)(&insertRowsEvaluatorWrapper)));
    defineFunctionObject("COERCE-UNCOERCED-VALUES-IN-TABLE", "(DEFUN (COERCE-UNCOERCED-VALUES-IN-TABLE CONS) ((TABLE CONS) (TYPES CONS)))", ((cpp_function_code)(&coerceUncoercedValuesInTable)), NULL);
    defineFunctionObject("COERCE-UNCOERCED-COLUMN-VALUES", "(DEFUN (COERCE-UNCOERCED-COLUMN-VALUES CONS) ((ROW CONS) (TYPES CONS)))", ((cpp_function_code)(&coerceUncoercedColumnValues)), NULL);
    defineFunctionObject("CONVERT-STRING-TO-TYPED-OBJECT", "(DEFUN (CONVERT-STRING-TO-TYPED-OBJECT OBJECT) ((VALUESTRING STRING) (TYPESPEC GENERALIZED-SYMBOL)))", ((cpp_function_code)(&convertStringToTypedObject)), NULL);
    defineFunctionObject("PREPARE-STATEMENT", "(DEFUN (PREPARE-STATEMENT PREPARED-STATEMENT) ((CONNECTION CONNECTION) (SQL STRING)) :DOCUMENTATION \"Prepare the `sql' statement for execution at the server and return\na prepared statement object.  After binding all its paramters via `bind-parameter'\nthe statement can be executed via `execute-sql'.\nIMPORTANT: Only one prepared statement can be associated with a connection at a time.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&prepareStatement)), ((cpp_function_code)(&prepareStatementEvaluatorWrapper)));
    defineFunctionObject("BIND-PARAMETER", "(DEFUN BIND-PARAMETER ((STATEMENT PREPARED-STATEMENT) (POSITION INTEGER) (TYPESPEC SURROGATE) (VALUE OBJECT)) :DOCUMENTATION \"Bind the parameter at `position' (1-based) in the prepared\nstatement `statement' to `value'.  `typeSpec' characterizes the type of\n`value' for proper translation and coercion.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&bindParameter)), ((cpp_function_code)(&bindParameterEvaluatorWrapper)));
    defineFunctionObject("CL-DO-BIND-PARAMETER", "(DEFUN CL-DO-BIND-PARAMETER ((STATEMENT PREPARED-STATEMENT) (POSITION INTEGER) (TYPESPEC SURROGATE) (VALUE OBJECT)))", ((cpp_function_code)(&clDoBindParameter)), NULL);
    defineFunctionObject("SET-AUTO-COMMIT", "(DEFUN SET-AUTO-COMMIT ((CONNECTION CONNECTION) (FLAG BOOLEAN)) :DOCUMENTATION \"Set the auto-commit feature of `connection' to TRUE or FALSE.\nIf a connection is in auto-commit mode, then all its SQL statements will be executed\nand committed as individual transactions.  Otherwise, its SQL statements are grouped\ninto transactions that are terminated by a call to either `commit' or `rollback'.\nBy default, new connections are in auto-commit mode.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&setAutoCommit)), ((cpp_function_code)(&setAutoCommitEvaluatorWrapper)));
    defineFunctionObject("COMMIT", "(DEFUN COMMIT ((CONNECTION CONNECTION)) :DOCUMENTATION \"Commit the current transaction.  Makes all changes made since the\nprevious commit/rollback permanent and releases any database locks currently held\nby this `connection' object.  This function is a no-op if auto-commit mode is\nenabled (see `set-auto-commit').\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&commit)), NULL);
    defineFunctionObject("ROLLBACK", "(DEFUN ROLLBACK ((CONNECTION CONNECTION)) :DOCUMENTATION \"Rollback the current transaction.  Undoes all changes made in\nthe current transaction and releases any database locks currently held by this\n`connection' object.  This function is a no-op if auto-commit mode is enabled\n (see `set-auto-commit').\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&rollback)), NULL);
    defineFunctionObject("GET-TABLES", "(DEFUN (GET-TABLES (CONS OF TABLE-INFO)) ((CONNECTION CONNECTION) (CATALOG-NAME STRING) (SCHEMA-NAME STRING) (TABLE-NAME STRING) (TABLE-TYPE STRING)) :DOCUMENTATION \"Get the tables of the database identified by `connection'\nand return the result as a list of objects containing all the relevant\nmeta information.  If any of the remaining arguments is supplied as\nnon-NULL, only tables whose corresponding field matches will be returned.\nThis is less general than what is supported by JDBC and ODBC, but Allegro\nODBC does not support filtering based on patterns, so we only do simple\nmanual filtering here.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&getTables)), ((cpp_function_code)(&getTablesEvaluatorWrapper)));
    defineFunctionObject("GET-COLUMNS", "(DEFUN (GET-COLUMNS (CONS OF COLUMN-INFO)) ((CONNECTION CONNECTION) (CATALOGNAME STRING) (SCHEMANAME STRING) (TABLENAME STRING) (COLUMNNAME STRING)) :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&getColumns)), ((cpp_function_code)(&getColumnsEvaluatorWrapper)));
    defineFunctionObject("GET-SERVER-INFO", "(DEFUN (GET-SERVER-INFO WRAPPER) ((CONNECTION CONNECTION) (PROPERTY STRING)) :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&getServerInfo)), ((cpp_function_code)(&getServerInfoEvaluatorWrapper)));
    defineFunctionObject("GUESS-DBMS-NAME", "(DEFUN (GUESS-DBMS-NAME STRING) ((CONNECTION CONNECTION)))", ((cpp_function_code)(&guessDbmsName)), NULL);
    defineFunctionObject("GET-DBMS-NAME", "(DEFUN (GET-DBMS-NAME KEYWORD) ((CONNECTION CONNECTION)))", ((cpp_function_code)(&getDbmsName)), NULL);
    defineFunctionObject("PRINT-TABLE", "(DEFUN PRINT-TABLE ((TABLE OBJECT)))", ((cpp_function_code)(&printTable)), NULL);
    defineFunctionObject("CALENDAR-DATE-TO-SQL-STRING", "(DEFUN (CALENDAR-DATE-TO-SQL-STRING STRING) ((DATE CALENDAR-DATE)))", ((cpp_function_code)(&calendarDateToSqlString)), NULL);
    defineFunctionObject("LOAD-SQL-CMD-TEMPLATES", "(DEFUN LOAD-SQL-CMD-TEMPLATES ((FILE STRING)))", ((cpp_function_code)(&loadSqlCmdTemplates)), NULL);
    defineFunctionObject("INSERT-SQL-COMMAND-TEMPLATE", "(DEFUN INSERT-SQL-COMMAND-TEMPLATE ((TEMPLATE PROPERTY-LIST)))", ((cpp_function_code)(&insertSqlCommandTemplate)), NULL);
    defineFunctionObject("LOOKUP-SQL-CMD-TEMPLATE", "(DEFUN (LOOKUP-SQL-CMD-TEMPLATE PROPERTY-LIST) ((COMMANDNAME OBJECT) (DATASOURCE OBJECT)))", ((cpp_function_code)(&lookupSqlCmdTemplate)), NULL);
    defineFunctionObject("INSTANTIATE-SQL-CMD", "(DEFUN (INSTANTIATE-SQL-CMD STRING) ((CMDNAME OBJECT) (DATASOURCE OBJECT) |&REST| (|VARS&VALUES| STRING)))", ((cpp_function_code)(&instantiateSqlCmd)), NULL);
    defineFunctionObject("INSTANTIATE-SQL-CMD-TEMPLATE", "(DEFUN (INSTANTIATE-SQL-CMD-TEMPLATE STRING) ((TEMPLATE STRING) (VARIABLES (KEY-VALUE-LIST OF STRING-WRAPPER OBJECT))))", ((cpp_function_code)(&instantiateSqlCmdTemplate)), NULL);
    defineFunctionObject("READ-SQL-CMD-TEMPLATE-VARIABLE", "(DEFUN (READ-SQL-CMD-TEMPLATE-VARIABLE STRING INTEGER) ((TEMPLATE STRING) (START INTEGER) (END INTEGER)))", ((cpp_function_code)(&readSqlCmdTemplateVariable)), NULL);
    defineFunctionObject("INSTANTIATE-SQL-CMD-TEMPLATE-VARIABLE", "(DEFUN (INSTANTIATE-SQL-CMD-TEMPLATE-VARIABLE STRING) ((TEMPLATEVARIABLE STRING) (VARIABLES (KEY-VALUE-LIST OF STRING-WRAPPER OBJECT))))", ((cpp_function_code)(&instantiateSqlCmdTemplateVariable)), NULL);
    defineFunctionObject("PARSE-SQL-CMD-TEMPLATE-VARIABLE-RANGE-AND-DEFAULT", "(DEFUN (PARSE-SQL-CMD-TEMPLATE-VARIABLE-RANGE-AND-DEFAULT STRING INTEGER INTEGER STRING) ((TEMPLATEVARIABLE STRING) (VARIABLENAME STRING) (START INTEGER)))", ((cpp_function_code)(&parseSqlCmdTemplateVariableRangeAndDefault)), NULL);
    defineFunctionObject("TEST-PREPARED-STATEMENT", "(DEFUN TEST-PREPARED-STATEMENT ())", ((cpp_function_code)(&testPreparedStatement)), NULL);
    defineFunctionObject("TEST-TRANSACTIONS", "(DEFUN TEST-TRANSACTIONS ())", ((cpp_function_code)(&testTransactions)), NULL);
    defineFunctionObject("TEST-RESULT-SET", "(DEFUN TEST-RESULT-SET ())", ((cpp_function_code)(&testResultSet)), NULL);
    defineFunctionObject("TEST-RETRIEVE-ALL", "(DEFUN TEST-RETRIEVE-ALL ())", ((cpp_function_code)(&testRetrieveAll)), NULL);
    defineFunctionObject("MAIN", "(DEFUN (MAIN INTEGER) () :PUBLIC? TRUE)", ((cpp_function_code)(&main)), NULL);
  }
}

void startupSdbc() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/SDBC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupSdbc1();
      helpStartupSdbc2();
    }
    if (currentStartupTimePhaseP(4)) {
      oSQL_COMMAND_TEMPLATESo = newKeyValueMap();
    }
    if (currentStartupTimePhaseP(5)) {
      helpStartupSdbc3();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupSdbc4();
      defineFunctionObject("STARTUP-SDBC", "(DEFUN STARTUP-SDBC () :PUBLIC? TRUE)", ((cpp_function_code)(&startupSdbc)), NULL);
      { MethodSlot* function = lookupFunction(SYM_SDBC_SDBC_STARTUP_SDBC);

        setDynamicSlotValue(function->dynamicSlots, SYM_SDBC_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupSdbc"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/SDBC")))));
      setLoggingParameters("SDBC", consList(6, KWD_SDBC_LOG_LEVELS, getQuotedTree("((:NONE :LOW :MEDIUM :HIGH) \"/SDBC\")", "/SDBC"), KWD_SDBC_LEVEL, KWD_SDBC_NONE, KWD_SDBC_MAX_WIDTH, wrapInteger(250)));
      defineGlobalVariableObject("(DEFGLOBAL *DB-CONNECTION-RENEWAL-INTERVAL* INTEGER 60 :DOCUMENTATION \"The maximum lifetime of a database connection (in seconds) after which\nit gets automatically renewed.  Auto-renewals avoid connection timeout errors which are\notherwise tricky to catch, e.g., we might just see a `bad handle passed' error.\" :DEMON-PROPERTY \"sdbc.dbConnectionRenewalInterval\" :PUBLIC? TRUE)", &oDB_CONNECTION_RENEWAL_INTERVALo);
      defineGlobalVariableObject("(DEFSPECIAL *SQL-COMMAND-TEMPLATES* (KEY-VALUE-MAP OF OBJECT (KEY-VALUE-LIST OF OBJECT PROPERTY-LIST)) (NEW KEY-VALUE-MAP))", &oSQL_COMMAND_TEMPLATESo);
      defineGlobalVariableObject("(DEFGLOBAL *SQL-CMD-TEMPLATE-VARIABLE-PREFIX* STRING \"#$\")", &oSQL_CMD_TEMPLATE_VARIABLE_PREFIXo);
      sdbc::initializeSymbols();
    }
  }
}

Keyword* KWD_SDBC_LOG_LEVELS = NULL;

Keyword* KWD_SDBC_LEVEL = NULL;

Keyword* KWD_SDBC_NONE = NULL;

Keyword* KWD_SDBC_MAX_WIDTH = NULL;

Surrogate* SGT_SDBC_SDBC_CONNECTION = NULL;

Symbol* SYM_SDBC_SDBC_CONNECTION_STRING = NULL;

Symbol* SYM_SDBC_SDBC_PROTOCOL = NULL;

Symbol* SYM_SDBC_SDBC_DBMS_NAME = NULL;

Symbol* SYM_SDBC_SDBC_STATEMENT = NULL;

Symbol* SYM_SDBC_SDBC_AUTO_COMMITp = NULL;

Symbol* SYM_SDBC_SDBC_CREATION_TIME = NULL;

Symbol* SYM_SDBC_SDBC_LAST_ACCESS_TIME = NULL;

Symbol* SYM_SDBC_SDBC_RENEWAL_TIME = NULL;

Surrogate* SGT_SDBC_SDBC_PREPARED_STATEMENT = NULL;

Symbol* SYM_SDBC_SDBC_CONNECTION = NULL;

Symbol* SYM_SDBC_SDBC_SQL = NULL;

Symbol* SYM_SDBC_STELLA_PARAMETERS = NULL;

Symbol* SYM_SDBC_SDBC_RDBMS_ROW = NULL;

Surrogate* SGT_SDBC_SDBC_RESULT_SET_ITERATOR = NULL;

Symbol* SYM_SDBC_SDBC_TYPES = NULL;

Keyword* KWD_SDBC_PROTOCOL = NULL;

Keyword* KWD_SDBC_SERVER_TYPE = NULL;

Keyword* KWD_SDBC_LOW = NULL;

Keyword* KWD_SDBC_CONNECTION_STRING = NULL;

Keyword* KWD_SDBC_HOST = NULL;

Keyword* KWD_SDBC_PORT = NULL;

Keyword* KWD_SDBC_DB_NAME = NULL;

Keyword* KWD_SDBC_DSN = NULL;

Keyword* KWD_SDBC_USER = NULL;

Keyword* KWD_SDBC_PASSWORD = NULL;

Keyword* KWD_SDBC_WHITE_SPACE = NULL;

Keyword* KWD_SDBC_LETTER = NULL;

Symbol* SYM_SDBC_STELLA_NULL = NULL;

Surrogate* SGT_SDBC_STELLA_CALENDAR_DATE = NULL;

Surrogate* SGT_SDBC_STELLA_STRING = NULL;

Surrogate* SGT_SDBC_STELLA_INTEGER = NULL;

Surrogate* SGT_SDBC_STELLA_LONG_INTEGER = NULL;

Surrogate* SGT_SDBC_STELLA_DOUBLE_FLOAT = NULL;

Keyword* KWD_SDBC_TYPES = NULL;

Keyword* KWD_SDBC_HIGH = NULL;

Keyword* KWD_SDBC_STRING_CONSTANT = NULL;

Keyword* KWD_SDBC_IDENTIFIER = NULL;

Keyword* KWD_SDBC_MYSQL = NULL;

Keyword* KWD_SDBC_NULL = NULL;

Symbol* SYM_SDBC_STELLA_DEFAULT = NULL;

Keyword* KWD_SDBC_DEFAULT = NULL;

Keyword* KWD_SDBC_ORACLE = NULL;

Surrogate* SGT_SDBC_STELLA_WRAPPER = NULL;

Surrogate* SGT_SDBC_SDBC_TABLE_INFO = NULL;

Symbol* SYM_SDBC_SDBC_DATABASE = NULL;

Symbol* SYM_SDBC_SDBC_CATALOG = NULL;

Symbol* SYM_SDBC_SDBC_SCHEMA = NULL;

Symbol* SYM_SDBC_STELLA_NAME = NULL;

Symbol* SYM_SDBC_STELLA_TYPE = NULL;

Symbol* SYM_SDBC_SDBC_REMARKS = NULL;

Symbol* SYM_SDBC_SDBC_COLUMNS = NULL;

Surrogate* SGT_SDBC_SDBC_COLUMN_INFO = NULL;

Symbol* SYM_SDBC_STELLA_TABLE_NAME = NULL;

Symbol* SYM_SDBC_SDBC_DATA_TYPE = NULL;

Symbol* SYM_SDBC_SDBC_DATA_TYPE_NAME = NULL;

Symbol* SYM_SDBC_SDBC_COLUMN_SIZE = NULL;

Symbol* SYM_SDBC_SDBC_BUFFER_LENGTH = NULL;

Symbol* SYM_SDBC_SDBC_DECIMAL_DIGITS = NULL;

Symbol* SYM_SDBC_SDBC_RADIX = NULL;

Symbol* SYM_SDBC_SDBC_NULLABLEp = NULL;

Symbol* SYM_SDBC_SDBC_IS_NULLABLEp = NULL;

Symbol* SYM_SDBC_STELLA_DOCUMENTATION = NULL;

Symbol* SYM_SDBC_STELLA_DEFAULT_VALUE = NULL;

Symbol* SYM_SDBC_SDBC_SQL_DATA_TYPE = NULL;

Symbol* SYM_SDBC_SDBC_SQL_DATETIME_SUB = NULL;

Symbol* SYM_SDBC_SDBC_CHAR_OCTET_LENGTH = NULL;

Symbol* SYM_SDBC_SDBC_ORDINAL_POSITION = NULL;

Keyword* KWD_SDBC_COMMAND = NULL;

Keyword* KWD_SDBC_DATA_SOURCE = NULL;

Keyword* KWD_SDBC_SQL = NULL;

Keyword* KWD_SDBC_OTHERWISE = NULL;

Surrogate* SGT_SDBC_STELLA_CONS = NULL;

Keyword* KWD_SDBC_DIGIT = NULL;

Keyword* KWD_SDBC_CONNECTIONSTRING = NULL;

Symbol* SYM_SDBC_SDBC_STARTUP_SDBC = NULL;

Symbol* SYM_SDBC_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace sdbc


