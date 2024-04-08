//  -*- Mode: C++ -*-

// rdbms.cc

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

LogicObject* defuntable(Cons* args) {
  // Define (or redefine) a database table and map it to a function
  // The accepted syntax is:
  // 	 
  //  (defuntable <relconst> <dbconst> <tablename> (<columndecl>+)
  //     [<keyword-option>*]).
  // 
  // <columndecl>'s specify the names (and optionally types) of the columns
  // of the database table.  They have the same form as a PowerLoom <vardecl>, but
  // column names can be specified with or without question marks.  If there
  // is a question mark it will be stripped to determine the column name, otherwise
  // a question mark will be added to generate the relation variable.  The optional
  // type specifies the domain of that argument and controls any necessary coercion.
  // The name of each column HAS TO MATCH one of the columns of <tablename>, however,
  // the order is irrelevant and arbitrary projections can be defined by only
  // specifying some subset of <tablename>'s columns.
  // 
  // See `deffunction' for legal keyword options.
  // 
  try {
    return (callDefuntable(args));
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
    return (NULL);
  }
}

LogicObject* defuntableEvaluatorWrapper(Cons* arguments) {
  return (defuntable(arguments));
}

NamedDescription* callDefuntable(Cons* arguments) {
  // Callable version of the `deftable' command (which see).
  // Expects the same arguments as `deftable' but supplied as a list.
  { Object* relconst = arguments->value;
    Object* dbconst = arguments->rest->value;
    Object* tablename = arguments->rest->rest->value;
    Object* columnspecs = arguments->fourth();
    Cons* dbaxioms = listO(4, listO(3, SYM_RDBMS_RDBMS_RELATION_TABLE, relconst, cons(tablename, NIL)), listO(3, SYM_RDBMS_RDBMS_RELATION_DATABASE, relconst, cons(dbconst, NIL)), listO(3, SYM_RDBMS_PL_KERNEL_KB_RELATION_SPECIALIST, relconst, cons(SYM_RDBMS_RDBMS_DBTABLE_SPECIALIST, NIL)), NIL);

    { Cons* relationargs = NULL;
      Cons* columnaxioms = NULL;

      relationargs = parseColumnSpecs(relconst, columnspecs, columnaxioms);
      arguments->fourthSetter(relationargs);
      dbaxioms->concatenate(columnaxioms, 0);
    }
    return (callDeffunction(cons(relconst, arguments->rest->rest->rest->concatenate(listO(3, KWD_RDBMS_AXIOMS, dbaxioms, NIL), 0))));
  }
}

LogicObject* deftable(Cons* args) {
  // Define (or redefine) a database table and map it to a relation.
  // The accepted syntax is:
  // 	 
  //  (deftable <relconst> <dbconst> <tablename> (<columndecl>+)
  //     [<keyword-option>*]).
  // 	
  // <columndecl>'s specify the names (and optionally types) of the columns
  // of the database table.  They have the same form as a PowerLoom <vardecl>, but
  // column names can be specified with or without question marks.  If there
  // is a question mark it will be stripped to determine the column name, otherwise
  // a question mark will be added to generate the relation variable.  The optional
  // type specifies the domain of that argument and controls any necessary coercion.
  // The name of each column HAS TO MATCH one of the columns of <tablename>, however,
  // the order is irrelevant and arbitrary projections can be defined by only
  // specifying some subset of <tablename>'s columns.
  // 
  // See `defrelation' for legal keyword options.
  // 
  try {
    return (callDeftable(args));
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
    return (NULL);
  }
}

LogicObject* deftableEvaluatorWrapper(Cons* arguments) {
  return (deftable(arguments));
}

NamedDescription* callDeftable(Cons* arguments) {
  // Callable version of the `deftable' command (which see).
  // Expects the same arguments as `deftable' but supplied as a list.
  { Object* relconst = arguments->value;
    Object* dbconst = arguments->rest->value;
    Object* tablename = arguments->rest->rest->value;
    Object* columnspecs = arguments->fourth();
    Cons* dbaxioms = listO(4, listO(3, SYM_RDBMS_RDBMS_RELATION_TABLE, relconst, cons(tablename, NIL)), listO(3, SYM_RDBMS_RDBMS_RELATION_DATABASE, relconst, cons(dbconst, NIL)), listO(3, SYM_RDBMS_PL_KERNEL_KB_RELATION_SPECIALIST, relconst, cons(SYM_RDBMS_RDBMS_DBTABLE_SPECIALIST, NIL)), NIL);

    { Cons* relationargs = NULL;
      Cons* columnaxioms = NULL;

      relationargs = parseColumnSpecs(relconst, columnspecs, columnaxioms);
      arguments->fourthSetter(relationargs);
      dbaxioms->concatenate(columnaxioms, 0);
    }
    return (callDefrelation(cons(relconst, arguments->rest->rest->rest->concatenate(listO(3, KWD_RDBMS_AXIOMS, dbaxioms, NIL), 0))));
  }
}

PropertyList* parseOneColumnSpec(Object* columnspec) {
  { PropertyList* parsedcolumn = newPropertyList();
    Symbol* var = NULL;
    Object* name = NULL;
    Cons* options = NIL;
    PropertyList* optionsplist = NULL;
    Object* type = NULL;

    { Surrogate* testValue000 = safePrimaryType(columnspec);

      if (testValue000 == SGT_RDBMS_STELLA_CONS) {
        { Object* columnspec000 = columnspec;
          Cons* columnspec = ((Cons*)(columnspec000));

          name = columnspec->value;
          if (((boolean)(columnspec->rest->value)) &&
              (!keywordP(columnspec->rest->value))) {
            {
              type = columnspec->rest->value;
              options = columnspec->rest->rest;
            }
          }
          else {
            options = columnspec->rest;
          }
        }
      }
      else if (subtypeOfSymbolP(testValue000)) {
        { Object* columnspec001 = columnspec;
          Symbol* columnspec = ((Symbol*)(columnspec001));

          name = columnspec;
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream000->nativeStream) << "PARSING ERROR: " << "Illegal table column specification: " << "`" << columnspec << "'" << "." << std::endl;
            helpSignalPropositionError(stream000, KWD_RDBMS_ERROR);
          }
          throw *newParsingError(stream000->theStringReader());
        }
      }
    }
    if (!(((boolean)(name)) &&
        symbolP(name))) {
      { OutputStringStream* stream001 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream001->nativeStream) << "PARSING ERROR: " << "Illegal table column name: " << "`" << name << "'" << "." << std::endl;
          helpSignalPropositionError(stream001, KWD_RDBMS_ERROR);
        }
        throw *newParsingError(stream001->theStringReader());
      }
    }
    if (!((!((boolean)(type))) ||
        symbolP(type))) {
      { OutputStringStream* stream002 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream002->nativeStream) << "PARSING ERROR: " << "Illegal table column type: " << "`" << type << "'" << "." << std::endl;
          helpSignalPropositionError(stream002, KWD_RDBMS_ERROR);
        }
        throw *newParsingError(stream002->theStringReader());
      }
    }
    { Cons* arglist000 = NIL;

      { Object* arg000 = NULL;
        Cons* iter000 = options;
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          arg000 = iter000->value;
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
      }
      optionsplist = vetOptions(arglist000, getQuotedTree("((:MODULE-NAME :MODULE-REFERENCE) \"/RDBMS\")", "/RDBMS"));
    }
    var = ((Symbol*)(name));
    if (questionMarkSymbolP(name)) {
      name = wrapString(stringSubsequence(var->symbolName, 1, NULL_INTEGER));
    }
    else {
      name = wrapString(var->symbolName);
      var = internDerivedSymbol(var, stringConcatenate("?", ((StringWrapper*)(name))->wrapperValue, 0));
    }
    parsedcolumn->insertAt(KWD_RDBMS_NAME, name);
    parsedcolumn->insertAt(KWD_RDBMS_VARIABLE, var);
    if (((boolean)(type))) {
      parsedcolumn->insertAt(KWD_RDBMS_TYPE, type);
    }
    { Object* key = NULL;
      Object* val = NULL;
      Cons* iter001 = optionsplist->thePlist;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest->rest) {
        key = iter001->value;
        val = iter001->rest->value;
        parsedcolumn->insertAt(key, val);
      }
    }
    return (parsedcolumn);
  }
}

Cons* parseColumnSpecs(Object* relconst, Object* columnspecs, Cons*& _Return1) {
  if (!(consP(columnspecs))) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "PARSING ERROR: " << "Illegal variable/column specifications: " << "`" << columnspecs << "'" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_RDBMS_ERROR);
      }
      throw *newParsingError(stream000->theStringReader());
    }
  }
  { Cons* relationargs = NIL;
    Cons* axioms = NIL;

    { Object* columnspec = NULL;
      Cons* iter000 = ((Cons*)(columnspecs));
      int i = NULL_INTEGER;
      int iter001 = 1;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        columnspec = iter000->value;
        i = iter001;
        { PropertyList* columninfo = parseOneColumnSpec(columnspec);
          Object* type = columninfo->lookup(KWD_RDBMS_TYPE);
          Object* name = columninfo->lookup(KWD_RDBMS_NAME);
          Object* var = columninfo->lookup(KWD_RDBMS_VARIABLE);
          Object* modulename = columninfo->lookup(KWD_RDBMS_MODULE_NAME);
          Object* modulereference = columninfo->lookup(KWD_RDBMS_MODULE_REFERENCE);

          if (((boolean)(type))) {
            relationargs = cons(consList(2, var, type), relationargs);
          }
          else {
            relationargs = cons(var, relationargs);
          }
          if (((boolean)(name))) {
            axioms = cons(listO(3, SYM_RDBMS_RDBMS_RELATION_COLUMN_NAME, relconst, cons(wrapInteger(i), cons(name, NIL))), axioms);
          }
          if (((boolean)(modulename))) {
            axioms = cons(listO(3, SYM_RDBMS_RDBMS_RELATION_COLUMN_MODULE_NAME, relconst, cons(wrapInteger(i), cons(modulename, NIL))), axioms);
          }
          if (((boolean)(modulereference))) {
            axioms = cons(listO(3, SYM_RDBMS_RDBMS_RELATION_COLUMN_MODULE_REFERENCE, relconst, cons(wrapInteger(i), cons(modulereference, NIL))), axioms);
          }
        }
      }
    }
    { Cons* _Return0 = relationargs->reverse();

      _Return1 = axioms->reverse();
      return (_Return0);
    }
  }
}

LogicObject* defdb(Cons* args) {
  // Define (or redefine) a database instance.  The accepted syntax is:
  // 	 
  //  (defdb <dbconst>
  //     [:protocol <protocol string>]
  //     [:server-type <server type string>]
  //     [:dsn <ODBC data-source name string>]
  //     [:odbc-connection-string <ODBC connection string>]
  //     [:jdbc-connection-string <JDBC connection string>]
  //     [:connection-string <connection string>] ;; deprecated
  //     [:host <server host string>]
  //     [:port <server host port>]
  //     [:user <user name string>]
  //     [:password <password string>]
  //     [:db-name <database name string>]
  //     [<keyword-option>*])
  // 	
  // Connection information can be asserted explicitly later or be done
  // programmatically, as long as it is done before the first time a
  // connection attempt is made (e.g., during a query).  This information
  // is passed to `SDBC/connect' (which see for more documentation on
  // ways to specify a connection).  For example, for ODBC a :DSN, an
  // :ODBC-CONNECTION-STRING or an appropriate combination of :HOST,
  // :PORT, :USER, :PASSWORD AND :DB-NAME can be used.  For JDBC a
  // :JDBC-CONNECTION-STRING or combination of :HOST, :PORT, etc. can
  // be used.  See `defobject' for additional legal keyword options.
  // 
  try {
    return (callDefdb(args));
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
    return (NULL);
  }
}

LogicObject* defdbEvaluatorWrapper(Cons* arguments) {
  return (defdb(arguments));
}

LogicObject* callDefdb(Cons* arguments) {
  // Callable version of of the `defdb' command (which see).
  // Expects the same arguments as `defdb' but supplied as a list.
  { Cons* definition = cons(SYM_RDBMS_RDBMS_DEFDB, arguments->concatenate(NIL, 0));
    Symbol* dbname = NULL;
    Cons* dbaxioms = NIL;
    Cons* relationoptions = NIL;

    { 
      BIND_STELLA_SPECIAL(oTERMSOURCEBEINGPARSEDo, const char*, stringify(definition));
      arguments = normalizeDefobjectArguments(arguments);
      dbname = ((Symbol*)(arguments->value));
      dbaxioms = extractRdbmsOptions(dbname, arguments->rest, relationoptions);
      dbaxioms = cons(listO(3, SYM_RDBMS_RDBMS_DATABASE, dbname, NIL), dbaxioms);
      arguments->rest = relationoptions->concatenate(listO(3, KWD_RDBMS_AXIOMS, dbaxioms, NIL), 0);
      return (callDefobject(arguments));
    }
  }
}

Cons* extractRdbmsOptions(Symbol* selfname, Cons* options, Cons*& _Return1) {
  { PropertyList* self000 = newPropertyList();

    self000->thePlist = options;
    { PropertyList* sourceoptions = self000;
      Module* rdbmsmodule = getStellaModule("RDBMS", true);
      Surrogate* relationref = NULL;
      NamedDescription* relation = NULL;
      Cons* axioms = NIL;
      Cons* otheroptions = NIL;

      { Object* key = NULL;
        Object* value = NULL;
        Cons* iter000 = sourceoptions->thePlist;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest->rest) {
          key = iter000->value;
          value = iter000->rest->value;
          if (keywordP(key)) {
            relationref = lookupSurrogateInModule(((Keyword*)(key))->symbolName, rdbmsmodule, true);
            if (((boolean)(relationref))) {
              relation = getDescription(relationref);
              if (((boolean)(relation))) {
                if (consP(value)) {
                  axioms = cons(cons(relation->descriptionName(), cons(selfname, ((Cons*)(value)))), axioms);
                }
                else {
                  { 
                    BIND_STELLA_SPECIAL(oMODULEo, Module*, rdbmsmodule);
                    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
                    axioms = cons(helpDefineKeywordAxioms(selfname, ((Keyword*)(key)), value), axioms);
                  }
                }
                continue;
              }
            }
          }
          otheroptions = cons(key, otheroptions);
          otheroptions = cons(value, otheroptions);
        }
      }
      { Cons* _Return0 = axioms->reverse();

        _Return1 = otheroptions->reverse();
        return (_Return0);
      }
    }
  }
}

void assertRdbmsConnectionInfo(const char* dbInstanceName, Cons* options) {
  // Assert DB connectivity information about the DB instance `db-instance-name' (for
  // example, "edb") according to `options'.  Looks up `db-instance-name' in the module
  // specified by the :module option (defaults to current module) and retracts any
  // preexisting connection information.  New assertions are also made in that module.
  // Default values are taken from the configuration table specified by :configuration.
  // 
  // Understands the following options, with default values specified by the configuration
  // key in parentheses:
  //    :connection-string ("DBConnection"),
  //    :jdbc-connection-string ("JDBCString"),
  //    :odbc-connection-string ("ODBCString"),
  //    :dsn ("DSN"),
  //    :db ("DBName"),
  //    :host ("DBHost"),
  //    :port ("DBPort"),
  //    :user ("DBUser"),
  //    :password ("DBPassword"),
  //    :module,
  //    :configuration.
  { PropertyList* theoptions = parseLogicCommandOptions(options, listO(23, KWD_RDBMS_CONNECTION_STRING, SGT_RDBMS_STELLA_STRING, KWD_RDBMS_JDBC_CONNECTION_STRING, SGT_RDBMS_STELLA_STRING, KWD_RDBMS_ODBC_CONNECTION_STRING, SGT_RDBMS_STELLA_STRING, KWD_RDBMS_DSN, SGT_RDBMS_STELLA_STRING, KWD_RDBMS_DB, SGT_RDBMS_STELLA_STRING, KWD_RDBMS_HOST, SGT_RDBMS_STELLA_STRING, KWD_RDBMS_PORT, SGT_RDBMS_STELLA_INTEGER, KWD_RDBMS_USER, SGT_RDBMS_STELLA_STRING, KWD_RDBMS_PASSWORD, SGT_RDBMS_STELLA_STRING, KWD_RDBMS_MODULE, SGT_RDBMS_STELLA_MODULE, KWD_RDBMS_CONFIGURATION, SGT_RDBMS_STELLA_CONFIGURATION_TABLE, NIL), true, false);
    Object* config = theoptions->lookup(KWD_RDBMS_CONFIGURATION);
    StringWrapper* conString = ((StringWrapper*)(theoptions->lookupWithDefault(KWD_RDBMS_CONNECTION_STRING, lookupConfigurationProperty("DBConnection", NULL, ((KeyValueList*)(config))))));
    StringWrapper* jdbcConString = ((StringWrapper*)(theoptions->lookupWithDefault(KWD_RDBMS_CONNECTION_STRING, lookupConfigurationProperty("JDBCString", NULL, ((KeyValueList*)(config))))));
    StringWrapper* odbcConString = ((StringWrapper*)(theoptions->lookupWithDefault(KWD_RDBMS_CONNECTION_STRING, lookupConfigurationProperty("ODBCString", NULL, ((KeyValueList*)(config))))));
    StringWrapper* dsn = ((StringWrapper*)(theoptions->lookupWithDefault(KWD_RDBMS_DSN, lookupConfigurationProperty("DSN", NULL, ((KeyValueList*)(config))))));
    StringWrapper* dbName = ((StringWrapper*)(theoptions->lookupWithDefault(KWD_RDBMS_DB_NAME, lookupConfigurationProperty("DBName", NULL, ((KeyValueList*)(config))))));
    StringWrapper* host = ((StringWrapper*)(theoptions->lookupWithDefault(KWD_RDBMS_HOST, lookupConfigurationProperty("DBHost", NULL, ((KeyValueList*)(config))))));
    IntegerWrapper* port = ((IntegerWrapper*)(theoptions->lookupWithDefault(KWD_RDBMS_PORT, lookupConfigurationProperty("DBPort", NULL, ((KeyValueList*)(config))))));
    StringWrapper* user = ((StringWrapper*)(theoptions->lookupWithDefault(KWD_RDBMS_USER, lookupConfigurationProperty("DBUser", NULL, ((KeyValueList*)(config))))));
    StringWrapper* password = ((StringWrapper*)(theoptions->lookupWithDefault(KWD_RDBMS_PASSWORD, lookupConfigurationProperty("DBPassword", NULL, ((KeyValueList*)(config))))));
    Module* module = ((Module*)(theoptions->lookupWithDefault(KWD_RDBMS_MODULE, oMODULEo)));
    const char* moduleName = module->moduleFullName;
    Object* dbObject = pli::sGetObject(dbInstanceName, moduleName, NULL);
    const char* assertionTemplate = instantiateStringTemplate(stringConcatenate("(AND", ((((boolean)(jdbcConString)) &&
        (!stringEqlP(jdbcConString->wrapperValue, ""))) ? "(RDBMS/JDBC-CONNECTION-STRING #$DB \"#$JDBCCON\")" : ""), 8, ((((boolean)(odbcConString)) &&
        (!stringEqlP(odbcConString->wrapperValue, ""))) ? "(RDBMS/ODBC-CONNECTION-STRING #$DB \"#$ODBCCON\")" : ""), ((((boolean)(dsn)) &&
        (!stringEqlP(dsn->wrapperValue, ""))) ? "(RDBMS/DSN #$DB \"#$DSN\")" : ""), ((((boolean)(dbName)) &&
        (!stringEqlP(dbName->wrapperValue, ""))) ? "(RDBMS/DB-NAME #$DB \"#$NAME\")" : ""), ((((boolean)(host)) &&
        (!stringEqlP(host->wrapperValue, ""))) ? "(RDBMS/HOST #$DB \"#$HOST\")" : ""), (((boolean)(port)) ? "(RDBMS/PORT #$DB #$PORT)" : ""), ((((boolean)(user)) &&
        (!stringEqlP(user->wrapperValue, ""))) ? "(RDBMS/USER #$DB \"#$USER\")" : ""), ((((boolean)(password)) &&
        (!stringEqlP(password->wrapperValue, ""))) ? "(RDBMS/PASSWORD #$DB \"#$PWD\")" : ""), ")"), 18, "#$DB", dbInstanceName, "#$DSN", dsn->wrapperValue, "#$NAME", (((boolean)(dbName)) ? dbName->wrapperValue : ""), "#$HOST", (((boolean)(host)) ? host->wrapperValue : ""), "#$PORT", (((boolean)(port)) ? integerToString(((long long int)(port->wrapperValue))) : ""), "#$USER", (((boolean)(user)) ? user->wrapperValue : ""), "#$PWD", (((boolean)(password)) ? password->wrapperValue : ""), "#$JDBCCON", (((boolean)(jdbcConString)) ? jdbcConString->wrapperValue : ""), "#$ODBCCON", (((boolean)(odbcConString)) ? odbcConString->wrapperValue : ""));

    if (((boolean)(dbObject))) {
      pli::sEvaluate(instantiateStringTemplate("(PROGN (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/DSN #$DB ?dsn)))\n                  (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/DB-NAME #$DB ?db)))\n                  (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/HOST #$DB ?host)))\n                  (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/PORT #$DB ?port)))\n                  (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/USER #$DB ?user)))\n                  (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/PASSWORD #$DB ?pwd)))\n                  (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/CONNECTION-STRING #$DB ?con)))\n                  (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/ODBC-CONNECTION-STRING #$DB ?con)))\n                  (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/JDBC-CONNECTION-STRING #$DB ?con))))", 2, "#$DB", dbInstanceName), moduleName, NULL);
    }
    if (((boolean)(conString))) {
      pli::sAssertProposition(instantiateStringTemplate("(RDBMS/#$PROTOCOL-CONNECTION-STRING #$DB \"#$CON\")", 6, "#$PROTOCOL", (sdbc::odbcConnectionStringP(conString->wrapperValue) ? "ODBC" : "JDBC"), "#$DB", dbInstanceName, "#$CON", conString->wrapperValue), moduleName, NULL);
    }
    if (!(stringEqlP(assertionTemplate, "(AND)"))) {
      pli::sAssertProposition(assertionTemplate, moduleName, NULL);
    }
  }
}

void assertRdbmsConnectionInfoEvaluatorWrapper(Cons* arguments) {
  assertRdbmsConnectionInfo(((StringWrapper*)(arguments->value))->wrapperValue, arguments->rest);
}

LogicObject* defquery(Cons* args) {
  // Define (or redefine) an (external) query and map it to a relation.
  // The accepted syntax is:
  // 	 
  //  (defquery <relconst> (<vardecl>+)
  //     {:query-pattern (<query-evaluator> <dbconst> <arguments-string>)}*
  //     [<keyword-option>*]).
  // 	
  // <query-evaluator> has to be a `Computed-Procedure' that takes the following
  // three arguments: the <relconst> query proposition, the database object <dbconst>
  // and the arguments string.  It needs to return an iterator that generates CONS
  // tuples whose elements will be bound in sequence to <relconst>'s arguments.
  // 
  // See `defrelation' for other legal keyword options.
  // 
  try {
    return (callDefquery(args));
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
    return (NULL);
  }
}

LogicObject* defqueryEvaluatorWrapper(Cons* arguments) {
  return (defquery(arguments));
}

NamedDescription* callDefquery(Cons* arguments) {
  // Callable version of the `defquery' command (which see).
  // Expects the same arguments as `deftable' but supplied as a list.
  { Cons* definition = cons(SYM_RDBMS_RDBMS_DEFQUERY, arguments->concatenate(NIL, 0));
    Symbol* relationname = NULL;
    Cons* queryaxioms = NIL;
    Cons* relationoptions = NIL;

    { 
      BIND_STELLA_SPECIAL(oTERMSOURCEBEINGPARSEDo, const char*, stringify(definition));
      arguments = normalizeDefrelationArguments(arguments);
      relationname = ((Symbol*)(arguments->value));
      queryaxioms = extractRdbmsOptions(relationname, arguments->rest->rest, relationoptions);
      queryaxioms = cons(listO(3, SYM_RDBMS_PL_KERNEL_KB_RELATION_SPECIALIST, relationname, cons(SYM_RDBMS_RDBMS_QUERY_SPECIALIST, NIL)), queryaxioms);
      { Cons* relationargs = NULL;
        Cons* columnaxioms = NULL;

        relationargs = parseColumnSpecs(relationname, arguments->rest->value, columnaxioms);
        arguments->secondSetter(relationargs);
        queryaxioms->concatenate(columnaxioms, 0);
      }
      arguments->rest->rest = relationoptions->concatenate(listO(3, KWD_RDBMS_AXIOMS, queryaxioms, NIL), 0);
      return (callDefrelation(arguments));
    }
  }
}

ConnectionWrapper* newConnectionWrapper() {
  { ConnectionWrapper* self = NULL;

    self = new ConnectionWrapper();
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    self->wrapperValue = NULL;
    return (self);
  }
}

Surrogate* ConnectionWrapper::primaryType() {
  { ConnectionWrapper* self = this;

    return (SGT_RDBMS_RDBMS_CONNECTION_WRAPPER);
  }
}

Object* accessConnectionWrapperSlotValue(ConnectionWrapper* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_RDBMS_STELLA_WRAPPER_VALUE) {
    if (setvalueP) {
      self->wrapperValue = ((sdbc::Connection*)(value));
    }
    else {
      value = self->wrapperValue;
    }
  }
  else {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

StringWrapper* normalizeConnectionArgument(Object* arg) {
  { Surrogate* testValue000 = safePrimaryType(arg);

    if (subtypeOfStringP(testValue000)) {
      { Object* arg000 = arg;
        StringWrapper* arg = ((StringWrapper*)(arg000));

        if (nullWrapperP(arg)) {
          return (NULL);
        }
        else {
          return (arg);
        }
      }
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { Object* arg001 = arg;
        IntegerWrapper* arg = ((IntegerWrapper*)(arg001));

        if (nullWrapperP(arg)) {
          return (NULL);
        }
        else {
          return (wrapString(integerToString(((long long int)(arg->wrapperValue)))));
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_RDBMS_LOGIC_LOGIC_OBJECT)) {
      { Object* arg002 = arg;
        LogicObject* arg = ((LogicObject*)(arg002));

        return (wrapString(pli::getName(arg)));
      }
    }
    else {
      return (NULL);
    }
  }
}

sdbc::Connection* connectToDatabase(LogicObject* database) {
  { Object* protocol = accessBinaryValue(database, SGT_RDBMS_RDBMS_PROTOCOL);
    Object* servertype = accessBinaryValue(database, SGT_RDBMS_RDBMS_SERVER_TYPE);
    Object* host = accessBinaryValue(database, SGT_RDBMS_RDBMS_HOST);
    Object* port = accessBinaryValue(database, SGT_RDBMS_RDBMS_PORT);
    Object* user = accessBinaryValue(database, SGT_RDBMS_RDBMS_USER);
    Object* password = accessBinaryValue(database, SGT_RDBMS_RDBMS_PASSWORD);
    Object* dbname = accessBinaryValue(database, SGT_RDBMS_RDBMS_DB_NAME);

    { Object* temp000 = accessBinaryValue(database, SGT_RDBMS_RDBMS_ODBC_CONNECTION_STRING);

      { Object* connectionstring = (((boolean)(temp000)) ? temp000 : accessBinaryValue(database, SGT_RDBMS_RDBMS_CONNECTION_STRING));
        Object* dsn = accessBinaryValue(database, SGT_RDBMS_RDBMS_DSN);
        sdbc::Connection* connection = NULL;
        ConnectionWrapper* connectionwrapper = newConnectionWrapper();

        connection = sdbc::connect(consList(18, KWD_RDBMS_PROTOCOL, normalizeConnectionArgument(protocol), KWD_RDBMS_SERVER_TYPE, normalizeConnectionArgument(servertype), KWD_RDBMS_DSN, normalizeConnectionArgument(dsn), KWD_RDBMS_DB_NAME, normalizeConnectionArgument(dbname), KWD_RDBMS_USER, normalizeConnectionArgument(user), KWD_RDBMS_PASSWORD, normalizeConnectionArgument(password), KWD_RDBMS_HOST, normalizeConnectionArgument(host), KWD_RDBMS_PORT, normalizeConnectionArgument(port), KWD_RDBMS_CONNECTION_STRING, normalizeConnectionArgument(connectionstring)));
        connectionwrapper->wrapperValue = connection;
        { 
          BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
          BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
          { 
            BIND_STELLA_SPECIAL(oINVISIBLEASSERTIONpo, boolean, true);
            BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_RDBMS_EXTENSIONAL_ASSERTION);
            pli::assertNaryProposition(cons(getRelation(SGT_RDBMS_RDBMS_DB_CONNECTION), cons(database, cons(connectionwrapper, NIL))), NULL, NULL);
          }
        }
        return (connection);
      }
    }
  }
}

void disconnectFromDatabase(LogicObject* database) {
  { Object* connection = accessBinaryValue(database, SGT_RDBMS_RDBMS_DB_CONNECTION);

    if (subtypeOfP(safePrimaryType(connection), SGT_RDBMS_RDBMS_CONNECTION_WRAPPER)) {
      { Object* connection000 = connection;
        ConnectionWrapper* connection = ((ConnectionWrapper*)(connection000));

        if (((boolean)(connection->wrapperValue))) {
          sdbc::disconnect(connection->wrapperValue);
        }
        { 
          BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
          BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
          pli::retractNaryProposition(cons(getRelation(SGT_RDBMS_RDBMS_DB_CONNECTION), cons(database, cons(connection, NIL))), NULL, NULL);
        }
      }
    }
    else {
    }
  }
}

sdbc::Connection* getConnectionFromDatabase(LogicObject* database) {
  { Object* connection = accessBinaryValue(database, SGT_RDBMS_RDBMS_DB_CONNECTION);

    if (subtypeOfP(safePrimaryType(connection), SGT_RDBMS_RDBMS_CONNECTION_WRAPPER)) {
      { Object* connection000 = connection;
        ConnectionWrapper* connection = ((ConnectionWrapper*)(connection000));

        return (connection->wrapperValue);
      }
    }
    else {
      return (connectToDatabase(database));
    }
  }
}

sdbc::Connection* getConnectionFromPredicate(Surrogate* relationref) {
  { Object* database = accessBinaryValue(getDescription(relationref), SGT_RDBMS_RDBMS_RELATION_DATABASE);
    sdbc::Connection* connection = getConnectionFromDatabase(((LogicObject*)(database)));

    return (connection);
  }
}

Iterator* allocateResultSetIterator(sdbc::Connection* connection, LogicObject* relation, const char* sqlstatement) {
  { AllPurposeIterator* self000 = newAllPurposeIterator();

    self000->iteratorNestedIterator = sdbc::getResultSet(connection, sqlstatement, 0);
    self000->iteratorObject = relation;
    self000->iteratorSecondObject = getRelationTableInfo(((NamedDescription*)(relation)));
    self000->iteratorNextCode = ((cpp_function_code)(&resultSetIteratorNextP));
    { AllPurposeIterator* value000 = self000;

      return (value000);
    }
  }
}

boolean resultSetIteratorNextP(AllPurposeIterator* self) {
  { Iterator* resultset = self->iteratorNestedIterator;
    Object* tableinfo = self->iteratorSecondObject;

    if (resultset->nextP()) {
      self->value = coerceValues(((Cons*)(resultset->value)), ((RelationTableInfo*)(tableinfo)));
      return (true);
    }
    else {
      return (false);
    }
  }
}

NamedDescription* getTableRelation(const char* tableName, Module* module) {
  { pli::PlIterator* iter = pli::retrieve(listO(3, wrapInteger(1), listO(4, SYM_RDBMS_RDBMS_RELATION_TABLE, SYM_RDBMS_LOGIC_pX, wrapString(tableName), NIL), NIL), module, NULL);

    if (iter->nextP()) {
      return (((NamedDescription*)(iter->value)));
    }
    else {
      return (NULL);
    }
  }
}

int getTableColumnIndex(NamedDescription* tableRelation, const char* columnName, Module* module) {
  { pli::PlIterator* iter = pli::retrieve(listO(3, wrapInteger(1), listO(3, SYM_RDBMS_RDBMS_RELATION_COLUMN_NAME, tableRelation, listO(3, SYM_RDBMS_LOGIC_pX, wrapString(columnName), NIL)), NIL), module, NULL);

    if (iter->nextP()) {
      return (((IntegerWrapper*)(iter->value))->wrapperValue);
    }
    else {
      return (-1);
    }
  }
}

StringWrapper* getTableColumnModuleName(NamedDescription* tablerelation, int columnindex) {
  return (((StringWrapper*)(pli::retrieve(listO(3, wrapInteger(1), listO(3, SYM_RDBMS_RDBMS_RELATION_COLUMN_MODULE_NAME, tablerelation, cons(wrapInteger(columnindex), cons(SYM_RDBMS_LOGIC_pX, NIL))), NIL), NULL, NULL)->pop())));
}

StringWrapper* getTableColumnModuleReference(NamedDescription* tablerelation, int columnindex) {
  return (((StringWrapper*)(pli::retrieve(listO(3, wrapInteger(1), listO(3, SYM_RDBMS_RDBMS_RELATION_COLUMN_MODULE_REFERENCE, tablerelation, cons(wrapInteger(columnindex), cons(SYM_RDBMS_LOGIC_pX, NIL))), NIL), NULL, NULL)->pop())));
}

StringWrapper* getTableColumnName(NamedDescription* tablerelation, int columnindex) {
  return (((StringWrapper*)(pli::retrieve(listO(3, wrapInteger(1), listO(3, SYM_RDBMS_RDBMS_RELATION_COLUMN_NAME, tablerelation, cons(wrapInteger(columnindex), cons(SYM_RDBMS_LOGIC_pX, NIL))), NIL), NULL, NULL)->pop())));
}

Cons* getTableColumnNames(NamedDescription* tablerelation) {
  { Cons* value000 = NIL;

    { RelationColumnInfo* column = NULL;
      Cons* iter000 = getRelationTableInfo(tablerelation)->columnList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        column = ((RelationColumnInfo*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(wrapString(column->columnName), NIL);
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
            collect000->rest = cons(wrapString(column->columnName), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    { Cons* names = value000;

      if (names->memberP(NULL)) {
        return (NULL);
      }
      else {
        return (names);
      }
    }
  }
}

RelationTableInfo* newRelationTableInfo() {
  { RelationTableInfo* self = NULL;

    self = new RelationTableInfo();
    self->adjunct = NULL;
    self->columnIndex = NULL;
    self->columnVector = NULL;
    self->columnList = NULL;
    self->tableAlias = "_T";
    self->tableName = NULL;
    self->dbmsName = NULL;
    self->database = NULL;
    self->relation = NULL;
    return (self);
  }
}

Surrogate* RelationTableInfo::primaryType() {
  { RelationTableInfo* self = this;

    return (SGT_RDBMS_RDBMS_RELATION_TABLE_INFO);
  }
}

Object* accessRelationTableInfoSlotValue(RelationTableInfo* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_RDBMS_STELLA_RELATION) {
    if (setvalueP) {
      self->relation = ((NamedDescription*)(value));
    }
    else {
      value = self->relation;
    }
  }
  else if (slotname == SYM_RDBMS_RDBMS_DATABASE) {
    if (setvalueP) {
      self->database = value;
    }
    else {
      value = self->database;
    }
  }
  else if (slotname == SYM_RDBMS_RDBMS_DBMS_NAME) {
    if (setvalueP) {
      self->dbmsName = ((Keyword*)(value));
    }
    else {
      value = self->dbmsName;
    }
  }
  else if (slotname == SYM_RDBMS_STELLA_TABLE_NAME) {
    if (setvalueP) {
      self->tableName = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->tableName);
    }
  }
  else if (slotname == SYM_RDBMS_RDBMS_TABLE_ALIAS) {
    if (setvalueP) {
      self->tableAlias = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->tableAlias);
    }
  }
  else if (slotname == SYM_RDBMS_RDBMS_COLUMN_LIST) {
    if (setvalueP) {
      self->columnList = ((Cons*)(value));
    }
    else {
      value = self->columnList;
    }
  }
  else if (slotname == SYM_RDBMS_RDBMS_COLUMN_VECTOR) {
    if (setvalueP) {
      self->columnVector = ((Vector*)(value));
    }
    else {
      value = self->columnVector;
    }
  }
  else if (slotname == SYM_RDBMS_RDBMS_COLUMN_INDEX) {
    if (setvalueP) {
      self->columnIndex = ((KeyValueMap*)(value));
    }
    else {
      value = self->columnIndex;
    }
  }
  else if (slotname == SYM_RDBMS_RDBMS_ADJUNCT) {
    if (setvalueP) {
      self->adjunct = value;
    }
    else {
      value = self->adjunct;
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

RelationColumnInfo* newRelationColumnInfo() {
  { RelationColumnInfo* self = NULL;

    self = new RelationColumnInfo();
    self->coercionFunction = NULL;
    self->moduleReferenceColumn = NULL;
    self->moduleLocalP = false;
    self->module = NULL;
    self->moduleReference = NULL;
    self->moduleName = NULL;
    self->columnDbType = NULL;
    self->columnType = NULL;
    self->columnIndex = NULL_INTEGER;
    self->columnVariable = NULL;
    self->columnName = NULL;
    self->tableInfo = NULL;
    return (self);
  }
}

Surrogate* RelationColumnInfo::primaryType() {
  { RelationColumnInfo* self = this;

    return (SGT_RDBMS_RDBMS_RELATION_COLUMN_INFO);
  }
}

Object* accessRelationColumnInfoSlotValue(RelationColumnInfo* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_RDBMS_RDBMS_TABLE_INFO) {
    if (setvalueP) {
      self->tableInfo = ((RelationTableInfo*)(value));
    }
    else {
      value = self->tableInfo;
    }
  }
  else if (slotname == SYM_RDBMS_RDBMS_COLUMN_NAME) {
    if (setvalueP) {
      self->columnName = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->columnName);
    }
  }
  else if (slotname == SYM_RDBMS_RDBMS_COLUMN_VARIABLE) {
    if (setvalueP) {
      self->columnVariable = ((Symbol*)(value));
    }
    else {
      value = self->columnVariable;
    }
  }
  else if (slotname == SYM_RDBMS_RDBMS_COLUMN_INDEX) {
    if (setvalueP) {
      self->columnIndex = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->columnIndex);
    }
  }
  else if (slotname == SYM_RDBMS_RDBMS_COLUMN_TYPE) {
    if (setvalueP) {
      self->columnType = ((NamedDescription*)(value));
    }
    else {
      value = self->columnType;
    }
  }
  else if (slotname == SYM_RDBMS_RDBMS_COLUMN_DB_TYPE) {
    if (setvalueP) {
      self->columnDbType = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->columnDbType);
    }
  }
  else if (slotname == SYM_RDBMS_STELLA_MODULE_NAME) {
    if (setvalueP) {
      self->moduleName = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->moduleName);
    }
  }
  else if (slotname == SYM_RDBMS_RDBMS_MODULE_REFERENCE) {
    if (setvalueP) {
      self->moduleReference = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->moduleReference);
    }
  }
  else if (slotname == SYM_RDBMS_STELLA_MODULE) {
    if (setvalueP) {
      self->module = ((Module*)(value));
    }
    else {
      value = self->module;
    }
  }
  else if (slotname == SYM_RDBMS_RDBMS_MODULE_LOCALp) {
    if (setvalueP) {
      self->moduleLocalP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->moduleLocalP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_RDBMS_RDBMS_MODULE_REFERENCE_COLUMN) {
    if (setvalueP) {
      self->moduleReferenceColumn = ((RelationColumnInfo*)(value));
    }
    else {
      value = self->moduleReferenceColumn;
    }
  }
  else if (slotname == SYM_RDBMS_RDBMS_COERCION_FUNCTION) {
    if (setvalueP) {
      self->coercionFunction = ((FunctionCodeWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFunctionCode(self->coercionFunction);
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

RelationTableInfo* createRelationTableInfo(NamedDescription* relation) {
  { RelationTableInfo* self000 = newRelationTableInfo();

    self000->relation = relation;
    { RelationTableInfo* tableinfo = self000;
      RelationColumnInfo* columninfo = NULL;
      int arity = relation->ioVariables->length();
      Cons* columns = NIL;
      Module* defaultmodule = oCONTEXTo->baseModule;

      tableinfo->database = accessBinaryValue(relation, SGT_RDBMS_RDBMS_RELATION_DATABASE);
      tableinfo->dbmsName = (((boolean)(tableinfo->database)) ? sdbc::getDbmsName(getConnectionFromDatabase(((LogicObject*)(tableinfo->database)))) : KWD_RDBMS_UNKNOWN);
      tableinfo->tableName = unwrapString(((StringWrapper*)(accessBinaryValue(relation, SGT_RDBMS_RDBMS_RELATION_TABLE))));
      tableinfo->columnIndex = newKeyValueMap();
      { int i = NULL_INTEGER;
        int iter000 = 1;
        int upperBound000 = arity;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;
        Symbol* var = NULL;
        Cons* iter001 = relation->ioVariableNames->theConsList;
        Cons* collect000 = NULL;

        for  (; (unboundedP000 ||
                  (iter000 <= upperBound000)) &&
                  (!(iter001 == NIL)); 
              iter000 = iter000 + 1,
              iter001 = iter001->rest) {
          i = iter000;
          var = ((Symbol*)(iter001->value));
          { RelationColumnInfo* self002 = newRelationColumnInfo();

            self002->tableInfo = tableinfo;
            columninfo = self002;
          }
          columninfo->columnName = unwrapString(getTableColumnName(relation, i));
          columninfo->columnVariable = var;
          columninfo->columnIndex = i - 1;
          columninfo->columnType = ((NamedDescription*)(pli::getNthDomain(relation, i - 1)));
          columninfo->moduleName = unwrapString(getTableColumnModuleName(relation, i));
          columninfo->moduleReference = unwrapString(getTableColumnModuleReference(relation, i));
          tableinfo->columnIndex->insertAt(wrapString(columninfo->columnName), columninfo);
          tableinfo->columnIndex->insertAt(var, columninfo);
          tableinfo->columnIndex->insertAt(wrapString(var->symbolName), columninfo);
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(columninfo, NIL);
              if (columns == NIL) {
                columns = collect000;
              }
              else {
                addConsToEndOfConsList(columns, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(columninfo, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      tableinfo->columnList = columns;
      tableinfo->columnVector = consToVector(columns);
      { RelationColumnInfo* column = NULL;
        Cons* iter002 = tableinfo->columnList;

        for (; !(iter002 == NIL); iter002 = iter002->rest) {
          column = ((RelationColumnInfo*)(iter002->value));
          if (column->moduleName != NULL) {
            column->moduleLocalP = true;
            column->module = getStellaModule(column->moduleName, false);
            if (!((boolean)(column->module))) {
              *(STANDARD_WARNING->nativeStream) << "Warning: " << "RDBMS: Column module " << "`" << column->moduleName << "'" << " for column " << "`" << column->columnName << "'" << " on relation " << "`" << relation << "'" << " is not defined; ignoring it..." << std::endl;
              column->module = defaultmodule;
            }
          }
          else if (column->moduleReference != NULL) {
            column->moduleLocalP = true;
            column->moduleReferenceColumn = ((RelationColumnInfo*)(tableinfo->columnIndex->lookup(wrapString(column->moduleReference))));
          }
          else {
            column->module = defaultmodule;
          }
        }
      }
      return (tableinfo);
    }
  }
}

Module* getModuleUsingReference(RelationColumnInfo* column, Cons* values) {
  { int refcolumindex = column->moduleReferenceColumn->columnIndex;
    Object* modulename = values->nth(refcolumindex);
    Module* module = (((boolean)(modulename)) ? getStellaModule(((StringWrapper*)(modulename))->wrapperValue, false) : ((Module*)(NULL)));

    if (!(((boolean)(module)))) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "RDBMS: Column module " << "`" << modulename << "'" << " defined by reference for column " << "`" << column->columnName << "'" << " on relation " << "`" << column->tableInfo->relation << "'" << " is not defined; ignoring it..." << std::endl;
      module = oCONTEXTo->baseModule;
    }
    return (module);
  }
}

RelationTableInfo* getRelationTableInfo(NamedDescription* tablerelation) {
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_RDBMS_RDBMS_F_GET_RELATION_TABLE_INFO_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_RDBMS_RDBMS_F_GET_RELATION_TABLE_INFO_MEMO_TABLE_000, "(:MAX-VALUES 100 :TIMESTAMPS (:META-KB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_RDBMS_RDBMS_F_GET_RELATION_TABLE_INFO_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), tablerelation, oCONTEXTo, MEMOIZED_NULL_VALUE, NULL, -1);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = createRelationTableInfo(tablerelation);
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { RelationTableInfo* value000 = ((RelationTableInfo*)(memoizedValue000));

      return (value000);
    }
  }
}

boolean collectionValuedConstraintP(Object* argument) {
  return (((boolean)(argument)) &&
      (enumeratedListP(argument) ||
       enumeratedSetP(argument)));
}

Cons* collectionValuedConstraintElements(Object* argument) {
  return (assertedCollectionMembers(argument, true)->consify());
}

void printSqlValue(OutputStream* stream, Object* value, RelationColumnInfo* column) {
  { NamedDescription* targetType = column->columnType;
    const char* baseString = coercePowerloomObjectToString(value, targetType);
    char quoteChar = sdbc::sqlQuoteCharacter(column->tableInfo->dbmsName, KWD_RDBMS_STRING_CONSTANT);

    if (targetType == getDescription(SGT_RDBMS_STELLA_STRING)) {
      *(stream->nativeStream) << quoteChar << sdbc::sqlEscapeString(baseString, quoteChar) << quoteChar;
    }
    else if (subrelationOfP(targetType, getDescription(SGT_RDBMS_STELLA_NUMBER)) ||
        subrelationOfP(targetType, getDescription(SGT_RDBMS_STELLA_BOOLEAN))) {
      *(stream->nativeStream) << baseString;
    }
    else {
      *(stream->nativeStream) << quoteChar << sdbc::sqlEscapeString(baseString, quoteChar) << quoteChar;
    }
  }
}

void printColumnConstraint(OutputStream* sql, RelationColumnInfo* column, const char* value, boolean casesensitiveP) {
  { RelationTableInfo* tableinfo = column->tableInfo;
    const char* tablealias = tableinfo->tableAlias;
    const char* columnname = column->columnName;

    if (tablealias != NULL) {
      columnname = stringConcatenate(tablealias, ".", 1, columnname);
    }
    *(sql->nativeStream) << columnname << "=";
    printSqlValue(sql, wrapString(value), column);
    if (casesensitiveP) {
      if (tableinfo->dbmsName == KWD_RDBMS_MYSQL) {
        *(sql->nativeStream) << " AND " << columnname << " LIKE BINARY ";
        printSqlValue(sql, wrapString(value), column);
      }
      else {
      }
    }
  }
}

void printArgumentConstraint(OutputStream* sql, Object* argument, RelationColumnInfo* column) {
  { NamedDescription* columntype = column->columnType;
    Surrogate* argname = objectSurrogate(argument);
    Module* argmodule = (((boolean)(argname)) ? ((Module*)(argname->homeContext)) : ((Module*)(NULL)));
    RelationColumnInfo* modulerefcolumn = column->moduleReferenceColumn;
    boolean casesensitiveP = (((boolean)(argmodule)) &&
        argmodule->caseSensitiveP) ||
        isaP(argument, SGT_RDBMS_STELLA_STRING_WRAPPER);

    if (collectionValuedConstraintP(argument)) {
      *(sql->nativeStream) << "(";
      { Object* subarg = NULL;
        Cons* iter000 = collectionValuedConstraintElements(argument);
        int si = NULL_INTEGER;
        int iter001 = 1;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest,
              iter001 = iter001 + 1) {
          subarg = iter000->value;
          si = iter001;
          if (si > 1) {
            *(sql->nativeStream) << " OR ";
          }
          printColumnConstraint(sql, column, coercePowerloomObjectToString(subarg, columntype), casesensitiveP);
        }
      }
      *(sql->nativeStream) << ")";
    }
    else {
      printColumnConstraint(sql, column, coercePowerloomObjectToString(argument, columntype), casesensitiveP);
    }
    if (((boolean)(modulerefcolumn)) &&
        ((boolean)(argmodule))) {
      *(sql->nativeStream) << " AND ";
      printColumnConstraint(sql, modulerefcolumn, argmodule->moduleName, false);
    }
  }
}

void printSqlColumnList(OutputStream* stream, RelationTableInfo* tableInfo) {
  { boolean firstP = true;
    const char* alias = tableInfo->tableAlias;

    { RelationColumnInfo* column = NULL;
      Cons* iter000 = tableInfo->columnList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        column = ((RelationColumnInfo*)(iter000->value));
        if (firstP) {
          firstP = false;
        }
        else {
          *(stream->nativeStream) << ", ";
        }
        if (alias != NULL) {
          *(stream->nativeStream) << alias << "." << column->columnName;
        }
        else {
          *(stream->nativeStream) << column->columnName;
        }
      }
    }
  }
}

void printSqlConstraintList(OutputStream* stream, RelationTableInfo* tableInfo, Vector* arguments) {
  { boolean firstP = true;

    { RelationColumnInfo* column = NULL;
      Cons* iter000 = tableInfo->columnList;
      Object* arg = NULL;
      Vector* vector000 = arguments;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; (!(iter000 == NIL)) &&
                (index000 < length000); 
            iter000 = iter000->rest,
            index000 = index000 + 1) {
        column = ((RelationColumnInfo*)(iter000->value));
        arg = (vector000->theArray)[index000];
        arg = safeArgumentBoundTo(arg);
        if (((boolean)(arg)) &&
            (!skolemP(arg))) {
          if (firstP) {
            {
              firstP = false;
              *(stream->nativeStream) << " WHERE ";
            }
          }
          else {
            *(stream->nativeStream) << " AND ";
          }
          printArgumentConstraint(stream, arg, column);
        }
      }
    }
  }
}

const char* createSqlFromProposition(Proposition* proposition) {
  { NamedDescription* relation = getDescription(((Surrogate*)(proposition->operatoR)));
    RelationTableInfo* tableinfo = getRelationTableInfo(relation);
    const char* tablealias = tableinfo->tableAlias;
    Vector* arguments = proposition->arguments;
    OutputStringStream* sql = newOutputStringStream();

    *(sql->nativeStream) << "SELECT DISTINCT ";
    printSqlColumnList(sql, tableinfo);
    *(sql->nativeStream) << " FROM " << tableinfo->tableName;
    if (tablealias != NULL) {
      *(sql->nativeStream) << " " << tablealias;
    }
    printSqlConstraintList(sql, tableinfo, arguments);
    return (sql->theStringReader());
  }
}

Iterator* allocateDbtableSpecialistIterator(ControlFrame* frame) {
  if (!((boolean)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_RDBMS_STELLA_ITERATOR, NULL)))))) {
    { Proposition* proposition = frame->proposition;
      Surrogate* relationref = ((Surrogate*)(proposition->operatoR));
      NamedDescription* relation = getDescription(relationref);

      checkForExternalDbUpdates(proposition, ((LogicObject*)(accessBinaryValue(relation, SGT_RDBMS_RDBMS_DATABASE))));
      { MemoizationTable* memoTable000 = NULL;
        Cons* memoizedEntry000 = NULL;
        Object* memoizedValue000 = NULL;

        if (oMEMOIZATION_ENABLEDpo) {
          memoTable000 = ((MemoizationTable*)(SGT_RDBMS_RDBMS_F_ALLOCATE_DBTABLE_SPECIALIST_ITERATOR_MEMO_TABLE_000->surrogateValue));
          if (!((boolean)(memoTable000))) {
            initializeMemoizationTable(SGT_RDBMS_RDBMS_F_ALLOCATE_DBTABLE_SPECIALIST_ITERATOR_MEMO_TABLE_000, "(:MAX-VALUES 1000 :TIMESTAMPS (:META-KB-UPDATE :EXTERNAL-DB-UPDATE))");
            memoTable000 = ((MemoizationTable*)(SGT_RDBMS_RDBMS_F_ALLOCATE_DBTABLE_SPECIALIST_ITERATOR_MEMO_TABLE_000->surrogateValue));
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
          memoizedValue000 = newMemoizableIterator(allocateResultSetIterator(getConnectionFromPredicate(relationref), relation, createSqlFromProposition(proposition)));
          if (oMEMOIZATION_ENABLEDpo) {
            memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
          }
        }
        setDynamicSlotValue(frame->dynamicSlots, SYM_RDBMS_STELLA_ITERATOR, cloneMemoizedIterator(((MemoizableIterator*)(memoizedValue000))), NULL);
      }
    }
  }
  return (((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_RDBMS_STELLA_ITERATOR, NULL))));
}

Keyword* retrieveNextDbQuerySolution(ControlFrame* frame, Keyword* lastmove) {
  { Vector* arguments = frame->proposition->arguments;
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_RDBMS_STELLA_ITERATOR, NULL)));

    lastmove = lastmove;
    if (!(((boolean)(iterator)))) {
      return (KWD_RDBMS_FAILURE);
    }
    if (iterator->firstIterationP) {
      if (!(iterator->nextP())) {
        return (KWD_RDBMS_FAILURE);
      }
      iterator->firstIterationP = false;
    }
    for (;;) {
      { boolean nonullsP = true;
        Cons* result = NIL;
        Object* binding = NULL;

        { Object* col = NULL;
          Cons* iter000 = ((Cons*)(iterator->value));
          Object* arg = NULL;
          Vector* vector000 = arguments;
          int index000 = 0;
          int length000 = vector000->length();
          Cons* collect000 = NULL;

          for  (; (!(iter000 == NIL)) &&
                    (index000 < length000); 
                iter000 = iter000->rest,
                index000 = index000 + 1) {
            col = iter000->value;
            arg = (vector000->theArray)[index000];
            binding = argumentBoundTo(arg);
            if (!((boolean)(col))) {
              nonullsP = false;
            }
            else if (((boolean)(binding)) &&
                (!skolemP(binding))) {
              col = binding;
            }
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(col, NIL);
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
                collect000->rest = cons(col, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        if ((((boolean)(oQUERYITERATORo)) &&
            ((boolean)(oQUERYITERATORo->partialMatchStrategy))) ||
            nonullsP) {
          if (bindVectorOfArgumentsToValuesP(arguments, result)) {
            break;
          }
        }
        if (!(iterator->nextP())) {
          return (KWD_RDBMS_FAILURE);
        }
      }
    }
    if (oRECORD_JUSTIFICATIONSpo) {
      { PrimitiveStrategy* self000 = newPrimitiveStrategy();

        self000->strategy = KWD_RDBMS_DB_LOOKUP;
        self000->antecedents = NIL;
        recordGoalJustification(frame, self000);
      }
    }
    if (iterator->nextP()) {
      return (KWD_RDBMS_CONTINUING_SUCCESS);
    }
    else {
      {
        setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
        return (KWD_RDBMS_FINAL_SUCCESS);
      }
    }
  }
}

Keyword* dbtableSpecialist(ControlFrame* frame, Keyword* lastmove) {
  if (!((boolean)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_RDBMS_STELLA_ITERATOR, NULL)))))) {
    setDynamicSlotValue(frame->dynamicSlots, SYM_RDBMS_STELLA_ITERATOR, allocateDbtableSpecialistIterator(frame), NULL);
  }
  return (retrieveNextDbQuerySolution(frame, lastmove));
}

Cons* getQueryPatternEvaluators(Surrogate* relationref) {
  { Cons* dummy1;
    Cons* dummy2;

    { Cons* evaluatorforms = NIL;

      { MemoizationTable* memoTable000 = NULL;
        Cons* memoizedEntry000 = NULL;
        Object* memoizedValue000 = NULL;

        if (oMEMOIZATION_ENABLEDpo) {
          memoTable000 = ((MemoizationTable*)(SGT_RDBMS_RDBMS_F_GET_QUERY_PATTERN_EVALUATORS_MEMO_TABLE_000->surrogateValue));
          if (!((boolean)(memoTable000))) {
            initializeMemoizationTable(SGT_RDBMS_RDBMS_F_GET_QUERY_PATTERN_EVALUATORS_MEMO_TABLE_000, "(:MAX-VALUES 100 :TIMESTAMPS (:META-KB-UPDATE))");
            memoTable000 = ((MemoizationTable*)(SGT_RDBMS_RDBMS_F_GET_QUERY_PATTERN_EVALUATORS_MEMO_TABLE_000->surrogateValue));
          }
          memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), relationref, oCONTEXTo, MEMOIZED_NULL_VALUE, NULL, -1);
          memoizedValue000 = memoizedEntry000->value;
        }
        if (((boolean)(memoizedValue000))) {
          if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
            memoizedValue000 = NULL;
          }
        }
        else {
          memoizedValue000 = applyCachedRetrieve(listO(5, SYM_RDBMS_RDBMS_pREL, SYM_RDBMS_RDBMS_pEV, SYM_RDBMS_RDBMS_pDB, SYM_RDBMS_RDBMS_pARGS, NIL), listO(4, SYM_RDBMS_STELLA_AND, listO(6, SYM_RDBMS_RDBMS_QUERY_PATTERN, SYM_RDBMS_RDBMS_pREL, SYM_RDBMS_RDBMS_pEV, SYM_RDBMS_RDBMS_pDB, SYM_RDBMS_RDBMS_pARGS, NIL), listO(5, SYM_RDBMS_STELLA_EXISTS, cons(SYM_RDBMS_RDBMS_pDB_TYPE, NIL), listO(4, SYM_RDBMS_RDBMS_SUPPORTS_DB_TYPE, SYM_RDBMS_RDBMS_pEV, SYM_RDBMS_RDBMS_pDB_TYPE, NIL), listO(4, SYM_RDBMS_RDBMS_INSTANCE_OF, SYM_RDBMS_RDBMS_pDB, SYM_RDBMS_RDBMS_pDB_TYPE, NIL), NIL), NIL), consList(4, relationref, NULL, NULL, NULL), consList(6, KWD_RDBMS_DONT_OPTIMIZEp, TRUE_WRAPPER, KWD_RDBMS_HOW_MANY, KWD_RDBMS_ALL, KWD_RDBMS_INFERENCE_LEVEL, KWD_RDBMS_ASSERTION), SYM_RDBMS_RDBMS_F_GET_QUERY_PATTERN_EVALUATORS_QUERY_001, dummy1, dummy2);
          if (oMEMOIZATION_ENABLEDpo) {
            memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
          }
        }
        { Cons* patterns = ((Cons*)(memoizedValue000));

          { Cons* triple = NULL;
            Cons* iter000 = patterns;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              triple = ((Cons*)(iter000->value));
              { cpp_function_code code = functionCodeFromProcedure(((ComputedProcedure*)(triple->value)));

                if (code != NULL) {
                  evaluatorforms = cons(consList(3, wrapFunctionCode(code), triple->rest->value, triple->rest->rest->value), evaluatorforms);
                }
              }
            }
          }
          return (evaluatorforms->reverse());
        }
      }
    }
  }
}

Cons* normalizeSqlJoinArguments(RelationTableInfo* tableinfo, Object* arguments, Cons*& _Return1) {
  if (((boolean)(tableinfo->adjunct))) {
    _Return1 = ((Cons*)(((Cons*)(tableinfo->adjunct))->rest->value));
    return (((Cons*)(((Cons*)(tableinfo->adjunct))->value)));
  }
  if (!(stringP(arguments))) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "PARSING ERROR: " << "SQL-join: illegal pattern arguments: " << "`" << arguments << "'" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_RDBMS_ERROR);
      }
      throw *newParsingError(stream000->theStringReader());
    }
  }
  { Object* args = readSExpressionFromString(((StringWrapper*)(arguments))->wrapperValue);
    Cons* tables = NIL;
    Cons* joinargs = NIL;

    if (safePrimaryType(args) == SGT_RDBMS_STELLA_CONS) {
      { Object* args000 = args;
        Cons* args = ((Cons*)(args000));

        { boolean testValue000 = false;

          testValue000 = args->length() >= 2;
          if (testValue000) {
            testValue000 = args->length() <= 3;
            if (testValue000) {
              { boolean alwaysP000 = true;

                { Object* arg = NULL;
                  Cons* iter000 = args;

                  for (; !(iter000 == NIL); iter000 = iter000->rest) {
                    arg = iter000->value;
                    if (!consP(arg)) {
                      alwaysP000 = false;
                      break;
                    }
                  }
                }
                testValue000 = alwaysP000;
              }
            }
          }
          if (!(testValue000)) {
            { OutputStringStream* stream001 = newOutputStringStream();

              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                *(stream001->nativeStream) << "PARSING ERROR: " << "SQL-join: illegal pattern arguments: " << "`" << arguments << "'" << "." << std::endl;
                helpSignalPropositionError(stream001, KWD_RDBMS_ERROR);
              }
              throw *newParsingError(stream001->theStringReader());
            }
          }
        }
        if (args->length() == 3) {
          { Object* outarg = NULL;
            Cons* iter001 = ((Cons*)(args->value));
            RelationColumnInfo* column = NULL;
            Cons* iter002 = tableinfo->columnList;

            for  (; (!(iter001 == NIL)) &&
                      (!(iter002 == NIL)); 
                  iter001 = iter001->rest,
                  iter002 = iter002->rest) {
              outarg = iter001->value;
              column = ((RelationColumnInfo*)(iter002->value));
              column->columnName = coerceToString(outarg);
              tableinfo->columnIndex->insertAt(wrapString(column->columnName), column);
            }
          }
          args = args->rest;
        }
        else {
          { RelationColumnInfo* column = NULL;
            Cons* iter003 = tableinfo->columnList;

            for (; !(iter003 == NIL); iter003 = iter003->rest) {
              column = ((RelationColumnInfo*)(iter003->value));
              if (column->columnName == NULL) {
                { OutputStringStream* stream002 = newOutputStringStream();

                  { 
                    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                    *(stream002->nativeStream) << "PARSING ERROR: " << "SQL-join: missing output argument/column specifications for: " << "`" << column->tableInfo->relation << "'" << "." << std::endl;
                    helpSignalPropositionError(stream002, KWD_RDBMS_ERROR);
                  }
                  throw *newParsingError(stream002->theStringReader());
                }
              }
            }
          }
        }
        { Object* table = NULL;
          Cons* iter004 = ((Cons*)(args->value));
          Cons* collect000 = NULL;

          for  (; !(iter004 == NIL); 
                iter004 = iter004->rest) {
            table = iter004->value;
            if (!((boolean)(collect000))) {
              {
                collect000 = cons((consP(table) ? ((Object*)(cons(wrapString(coerceToString(((Cons*)(table))->value)), cons(wrapString(coerceToString(((Cons*)(table))->rest->value)), NIL)))) : ((Object*)(wrapString(coerceToString(table))))), NIL);
                if (tables == NIL) {
                  tables = collect000;
                }
                else {
                  addConsToEndOfConsList(tables, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons((consP(table) ? ((Object*)(cons(wrapString(coerceToString(((Cons*)(table))->value)), cons(wrapString(coerceToString(((Cons*)(table))->rest->value)), NIL)))) : ((Object*)(wrapString(coerceToString(table))))), NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        { Object* pair = NULL;
          Cons* iter005 = ((Cons*)(args->rest->value));
          Cons* collect001 = NULL;

          for  (; !(iter005 == NIL); 
                iter005 = iter005->rest) {
            pair = iter005->value;
            if (!(consP(pair))) {
              { OutputStringStream* stream003 = newOutputStringStream();

                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  *(stream003->nativeStream) << "PARSING ERROR: " << "SQL-join: illegal pattern arguments: " << "`" << arguments << "'" << "." << std::endl;
                  helpSignalPropositionError(stream003, KWD_RDBMS_ERROR);
                }
                throw *newParsingError(stream003->theStringReader());
              }
            }
            pair = consList(2, wrapString(coerceToString(((Cons*)(pair))->value)), wrapString(coerceToString(((Cons*)(pair))->rest->value)));
            if (!((boolean)(collect001))) {
              {
                collect001 = cons(pair, NIL);
                if (joinargs == NIL) {
                  joinargs = collect001;
                }
                else {
                  addConsToEndOfConsList(joinargs, collect001);
                }
              }
            }
            else {
              {
                collect001->rest = cons(pair, NIL);
                collect001 = collect001->rest;
              }
            }
          }
        }
      }
    }
    else {
      { OutputStringStream* stream004 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream004->nativeStream) << "PARSING ERROR: " << "SQL-join: illegal pattern arguments: " << "`" << arguments << "'" << "." << std::endl;
          helpSignalPropositionError(stream004, KWD_RDBMS_ERROR);
        }
        throw *newParsingError(stream004->theStringReader());
      }
    }
    tableinfo->adjunct = consList(2, tables, joinargs);
    _Return1 = joinargs;
    return (tables);
  }
}

Iterator* helpMemoizeSqlJoin(Proposition* proposition, LogicObject* database, Object* arguments) {
  { NamedDescription* relation = getDescription(((Surrogate*)(proposition->operatoR)));
    RelationTableInfo* tableinfo = getRelationTableInfo(relation);
    Cons* tables = NIL;
    Cons* joinargs = NIL;
    OutputStringStream* sql = newOutputStringStream();

    tables = normalizeSqlJoinArguments(tableinfo, arguments, joinargs);
    *(sql->nativeStream) << "SELECT DISTINCT ";
    { RelationColumnInfo* column = NULL;
      Cons* iter000 = tableinfo->columnList;
      int i = NULL_INTEGER;
      int iter001 = 1;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        column = ((RelationColumnInfo*)(iter000->value));
        i = iter001;
        if (i > 1) {
          *(sql->nativeStream) << ", ";
        }
        *(sql->nativeStream) << column->columnName;
      }
    }
    *(sql->nativeStream) << " FROM ";
    { Object* table = NULL;
      Cons* iter002 = tables;
      int i = NULL_INTEGER;
      int iter003 = 1;

      for  (; !(iter002 == NIL); 
            iter002 = iter002->rest,
            iter003 = iter003 + 1) {
        table = iter002->value;
        i = iter003;
        if (i > 1) {
          *(sql->nativeStream) << ", ";
        }
        if (consP(table)) {
          *(sql->nativeStream) << unwrapString(((StringWrapper*)(((Cons*)(table))->value))) << " " << unwrapString(((StringWrapper*)(((Cons*)(table))->rest->value)));
        }
        else {
          *(sql->nativeStream) << unwrapString(((StringWrapper*)(table)));
        }
      }
    }
    *(sql->nativeStream) << " WHERE ";
    { Cons* pair = NULL;
      Cons* iter004 = joinargs;
      int i = NULL_INTEGER;
      int iter005 = 1;

      for  (; !(iter004 == NIL); 
            iter004 = iter004->rest,
            iter005 = iter005 + 1) {
        pair = ((Cons*)(iter004->value));
        i = iter005;
        if (i > 1) {
          *(sql->nativeStream) << " AND ";
        }
        *(sql->nativeStream) << unwrapString(((StringWrapper*)(pair->value))) << "=" << unwrapString(((StringWrapper*)(pair->rest->value)));
      }
    }
    { Object* arg = NULL;
      Vector* vector000 = proposition->arguments;
      int index000 = 0;
      int length000 = vector000->length();
      RelationColumnInfo* column = NULL;
      Cons* iter006 = tableinfo->columnList;

      for  (; (index000 < length000) &&
                (!(iter006 == NIL)); 
            index000 = index000 + 1,
            iter006 = iter006->rest) {
        arg = (vector000->theArray)[index000];
        column = ((RelationColumnInfo*)(iter006->value));
        arg = safeArgumentBoundTo(arg);
        if (((boolean)(arg))) {
          *(sql->nativeStream) << " AND ";
          printArgumentConstraint(sql, arg, column);
        }
      }
    }
    return (allocateResultSetIterator(getConnectionFromDatabase(database), relation, sql->theStringReader()));
  }
}

Iterator* sqlJoin(Proposition* proposition, LogicObject* database, Object* arguments) {
  checkForExternalDbUpdates(proposition, database);
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_RDBMS_RDBMS_F_SQL_JOIN_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_RDBMS_RDBMS_F_SQL_JOIN_MEMO_TABLE_000, "(:MAX-VALUES 100 :TIMESTAMPS (:META-KB-UPDATE :EXTERNAL-DB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_RDBMS_RDBMS_F_SQL_JOIN_MEMO_TABLE_000->surrogateValue));
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
      memoizedValue000 = newMemoizableIterator(helpMemoizeSqlJoin(proposition, database, arguments));
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { Iterator* value000 = cloneMemoizedIterator(((MemoizableIterator*)(memoizedValue000)));

      return (((Iterator*)(value000)));
    }
  }
}

void collectVariableBinding(const char* name, Object* type, Object* binding, KeyValueList* bindings) {
  if (((boolean)(binding))) {
    if (((boolean)(type))) {
      type = getDescription(type);
    }
    if (collectionValuedConstraintP(binding)) {
      { Cons* args = NIL;

        { Object* elt = NULL;
          Cons* iter000 = collectionValuedConstraintElements(binding);
          Cons* collect000 = NULL;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest) {
            elt = iter000->value;
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(wrapString(coercePowerloomObjectToString(elt, ((NamedDescription*)(type)))), NIL);
                if (args == NIL) {
                  args = collect000;
                }
                else {
                  addConsToEndOfConsList(args, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(wrapString(coercePowerloomObjectToString(elt, ((NamedDescription*)(type)))), NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        binding = args;
      }
    }
    else {
      binding = wrapString(coercePowerloomObjectToString(binding, ((NamedDescription*)(type))));
    }
  }
  bindings->insertAt(wrapString(name), binding);
}

const char* createSqlQueryFromProposition(Proposition* proposition, LogicObject* database, Object* arguments) {
  database = database;
  { NamedDescription* relation = getDescription(((Surrogate*)(proposition->operatoR)));
    const char* templatE = ((StringWrapper*)(arguments))->wrapperValue;
    KeyValueList* bindings = newKeyValueList();
    const char* sql = NULL;

    { Symbol* var = NULL;
      Cons* iter000 = relation->ioVariableNames->theConsList;
      Object* arg = NULL;
      Vector* vector000 = proposition->arguments;
      int index000 = 0;
      int length000 = vector000->length();
      int i = NULL_INTEGER;
      int iter001 = 1;

      for  (; (!(iter000 == NIL)) &&
                (index000 < length000); 
            iter000 = iter000->rest,
            index000 = index000 + 1,
            iter001 = iter001 + 1) {
        var = ((Symbol*)(iter000->value));
        arg = (vector000->theArray)[index000];
        i = iter001;
        collectVariableBinding(var->symbolName, pli::getNthDomain(relation, i), safeArgumentBoundTo(arg), bindings);
      }
    }
    sql = sdbc::instantiateSqlCmdTemplate(templatE, bindings);
    sql = sqlQueryInstantiateConstraints(sql, bindings);
    return (sql);
  }
}

Iterator* helpMemoizeSqlQuery(Proposition* proposition, LogicObject* database, Object* arguments) {
  return (allocateResultSetIterator(getConnectionFromDatabase(database), getDescription(((Surrogate*)(proposition->operatoR))), createSqlQueryFromProposition(proposition, database, arguments)));
}

const char* sqlQueryInstantiateConstraints(const char* sql, KeyValueList* bindings) {
  { int start = 0;
    int end = strlen(sql);
    const char* variable = NULL;
    Object* value = NULL;
    int varstart = 0;
    int varend = 0;
    int colstart = 0;
    Keyword* constraint = KWD_RDBMS_VALUE;
    const char* quotes = "'`\"";
    char quote = NULL_CHARACTER;
    Cons* result = NIL;
    const char* truecondition = "1=1";
    const char* falsecondition = "0=1";

    for (;;) {
      varstart = stringPosition(sql, '?', varend);
      if (varstart == NULL_INTEGER) {
        if (result == NIL) {
          return (sql);
        }
        else {
          result = cons(wrapString(stringSubsequence(sql, start, NULL_INTEGER)), result);
          break;
        }
      }
      variable = NULL;
      { StringWrapper* var = NULL;
        Object* val = NULL;
        KvCons* iter000 = bindings->theKvList;

        for  (; ((boolean)(iter000)); 
              iter000 = iter000->rest) {
          var = ((StringWrapper*)(iter000->key));
          val = iter000->value;
          if (startsWithP(sql, var->wrapperValue, varstart)) {
            variable = var->wrapperValue;
            value = val;
            varend = varstart + strlen(variable);
            if ((varend == end) ||
                ((oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (sql[varend])] == KWD_RDBMS_WHITE_SPACE) ||
                 stringMemberP(quotes, sql[varend]))) {
              break;
            }
          }
        }
      }
      if (variable == NULL) {
        varend = varstart + 1;
        continue;
      }
      quote = NULL_CHARACTER;
      if (sql[(stella::integerMax(varstart - 1, 0))] == '=') {
        colstart = varstart - 2;
        constraint = KWD_RDBMS_VALUE;
      }
      else if ((sql[(stella::integerMax(varstart - 2, 0))] == '=') &&
          stringMemberP(quotes, sql[(varstart - 1)])) {
        colstart = varstart - 3;
        constraint = KWD_RDBMS_VALUE;
        quote = sql[(varstart - 1)];
      }
      else if (startsWithP(sql, " IN ", stella::integerMax(varstart - 4, 0)) ||
          startsWithP(sql, " in ", stella::integerMax(varstart - 4, 0))) {
        colstart = varstart - 5;
        constraint = KWD_RDBMS_SET;
      }
      else if ((startsWithP(sql, " IN ", stella::integerMax(varstart - 5, 0)) ||
          startsWithP(sql, " in ", stella::integerMax(varstart - 5, 0))) &&
          stringMemberP(quotes, sql[(varstart - 1)])) {
        colstart = varstart - 6;
        constraint = KWD_RDBMS_SET;
        quote = sql[(varstart - 1)];
      }
      else {
        constraint = KWD_RDBMS_NONE;
        continue;
      }
      if ((constraint == KWD_RDBMS_VALUE) &&
          (consP(value) &&
           (!(value == NIL)))) {
        constraint = KWD_RDBMS_SET;
        result = cons(wrapString(stringSubsequence(sql, start, colstart + 1)), result);
        result = cons(wrapString(" IN "), result);
        start = ((quote != NULL_CHARACTER) ? (varstart - 1) : varstart);
      }
      if ((!((boolean)(value))) ||
          (value == NIL)) {
        for (;;) {
          if (colstart <= 0) {
            colstart = 0;
            break;
          }
          else if (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (sql[colstart])] == KWD_RDBMS_WHITE_SPACE) {
            colstart = colstart + 1;
            break;
          }
          else {
            colstart = colstart - 1;
          }
        }
        if (quote != NULL_CHARACTER) {
          varend = varend + 1;
        }
        result = cons(wrapString(stringSubsequence(sql, start, colstart)), result);
        result = cons(((value == NIL) ? wrapString(falsecondition) : wrapString(truecondition)), result);
      }
      else if (constraint == KWD_RDBMS_SET) {
        if (quote != NULL_CHARACTER) {
          varstart = varstart - 1;
          varend = varend + 1;
        }
        { OutputStringStream* set = newOutputStringStream();

          *(set->nativeStream) << "(";
          { Object* elt = NULL;
            Cons* iter001 = value->consify();
            int i = NULL_INTEGER;
            int iter002 = 1;

            for  (; !(iter001 == NIL); 
                  iter001 = iter001->rest,
                  iter002 = iter002 + 1) {
              elt = iter001->value;
              i = iter002;
              *(set->nativeStream) << (((i > 1) ? "," : ""));
              if (quote != NULL_CHARACTER) {
                *(set->nativeStream) << quote << sdbc::sqlEscapeString(((StringWrapper*)(elt))->wrapperValue, quote) << quote;
              }
              else {
                *(set->nativeStream) << unwrapString(((StringWrapper*)(elt)));
              }
            }
          }
          *(set->nativeStream) << ")";
          result = cons(wrapString(stringSubsequence(sql, start, varstart)), result);
          result = cons(wrapString(set->theStringReader()), result);
        }
      }
      else {
        result = cons(wrapString(stringSubsequence(sql, start, varstart)), result);
        result = cons(((quote != NULL_CHARACTER) ? wrapString(sdbc::sqlEscapeString(((StringWrapper*)(value))->wrapperValue, quote)) : value), result);
      }
      start = varend;
    }
    { OutputStringStream* res = newOutputStringStream();

      { StringWrapper* piece = NULL;
        Cons* iter003 = result->reverse();

        for (; !(iter003 == NIL); iter003 = iter003->rest) {
          piece = ((StringWrapper*)(iter003->value));
          *(res->nativeStream) << unwrapString(piece);
        }
      }
      return (res->theStringReader());
    }
  }
}

Iterator* sqlQuery(Proposition* proposition, LogicObject* database, Object* arguments) {
  checkForExternalDbUpdates(proposition, database);
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_RDBMS_RDBMS_F_SQL_QUERY_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_RDBMS_RDBMS_F_SQL_QUERY_MEMO_TABLE_000, "(:MAX-VALUES 100 :TIMESTAMPS (:META-KB-UPDATE :EXTERNAL-DB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_RDBMS_RDBMS_F_SQL_QUERY_MEMO_TABLE_000->surrogateValue));
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
      memoizedValue000 = newMemoizableIterator(helpMemoizeSqlQuery(proposition, database, arguments));
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { Iterator* value000 = cloneMemoizedIterator(((MemoizableIterator*)(memoizedValue000)));

      return (((Iterator*)(value000)));
    }
  }
}

Iterator* allocateQuerySpecialistIterator(ControlFrame* frame) {
  if (!((boolean)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_RDBMS_STELLA_ITERATOR, NULL)))))) {
    { Iterator* iterator = NULL;
      Iterator* iterator2 = NULL;
      Proposition* proposition = frame->proposition;
      Surrogate* relationref = ((Surrogate*)(proposition->operatoR));

      { Cons* triple = NULL;
        Cons* iter000 = getQueryPatternEvaluators(relationref);

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          triple = ((Cons*)(iter000->value));
          if (!((boolean)(iterator))) {
            iterator = ((Iterator*  (*) (Proposition*, Object*, Object*))((FunctionCodeWrapper*)(triple->value))->wrapperValue)(proposition, triple->rest->value, triple->rest->rest->value);
          }
          else {
            iterator2 = ((Iterator*  (*) (Proposition*, Object*, Object*))((FunctionCodeWrapper*)(triple->value))->wrapperValue)(proposition, triple->rest->value, triple->rest->rest->value);
            if (((boolean)(iterator2))) {
              iterator = iterator->concatenate(iterator2, 0);
            }
          }
        }
      }
      setDynamicSlotValue(frame->dynamicSlots, SYM_RDBMS_STELLA_ITERATOR, iterator, NULL);
    }
  }
  return (((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_RDBMS_STELLA_ITERATOR, NULL))));
}

Keyword* querySpecialist(ControlFrame* frame, Keyword* lastmove) {
  if (!((boolean)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_RDBMS_STELLA_ITERATOR, NULL)))))) {
    setDynamicSlotValue(frame->dynamicSlots, SYM_RDBMS_STELLA_ITERATOR, allocateQuerySpecialistIterator(frame), NULL);
  }
  return (retrieveNextDbQuerySolution(frame, lastmove));
}

KeyValueList* collectQueryDatabaseSpecialistBindings(ControlFrame* frame, int firstargindex) {
  { Vector* arguments = frame->proposition->arguments;
    KeyValueList* bindings = newKeyValueList();

    { Object* arg = NULL;
      Vector* vector000 = arguments;
      int index000 = 0;
      int length000 = vector000->length();
      int i = NULL_INTEGER;
      int iter000 = 0;

      for  (; index000 < length000; 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        arg = (vector000->theArray)[index000];
        i = iter000;
        if ((i >= firstargindex) &&
            variableP(arg)) {
          collectVariableBinding(((PatternVariable*)(arg))->skolemName->symbolName, logicalType(arg), argumentBoundTo(arg), bindings);
        }
      }
    }
    return (bindings);
  }
}

Keyword* bindNextDatabaseTupleToArguments(ControlFrame* frame, int firstargindex) {
  { Vector* arguments = frame->proposition->arguments;
    int nofoutputs = arguments->length() - firstargindex;
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_RDBMS_STELLA_ITERATOR, NULL)));
    PatternRecord* patternrecord = oQUERYITERATORo->currentPatternRecord;
    int ubstackoffset = patternrecord->topUnbindingStackOffset;
    boolean checkedunboundoutputsP = false;

    while (iterator->nextP()) {
      { boolean alwaysP000 = true;

        { StringWrapper* output = NULL;
          Cons* iter000 = ((Cons*)(iterator->value));
          int i = NULL_INTEGER;
          int iter001 = firstargindex;
          int upperBound000 = arguments->length() - 1;

          for  (; (!(iter000 == NIL)) &&
                    (iter001 <= upperBound000); 
                iter000 = iter000->rest,
                iter001 = iter001 + 1) {
            output = ((StringWrapper*)(iter000->value));
            i = iter001;
            if (!collectionValuedConstraintP(argumentBoundTo((arguments->theArray)[i]))) {
              if (!bindArgumentToValueP((arguments->theArray)[i], coerceStringToPowerloomObject(unwrapString(output), getDescription(logicalType((arguments->theArray)[i])), oMODULEo, false), true)) {
                alwaysP000 = false;
                break;
              }
            }
          }
        }
        if (alwaysP000) {
          if ((!checkedunboundoutputsP) &&
              (((Cons*)(iterator->value))->length() < nofoutputs)) {
            { int i = NULL_INTEGER;
              int iter002 = ((Cons*)(iterator->value))->length() + firstargindex;
              int upperBound001 = arguments->length() - 1;

              for  (; iter002 <= upperBound001; 
                    iter002 = iter002 + 1) {
                i = iter002;
                if (!((boolean)(argumentBoundTo((arguments->theArray)[i])))) {
                  return (KWD_RDBMS_TERMINAL_FAILURE);
                }
              }
            }
          }
          checkedunboundoutputsP = true;
          return (KWD_RDBMS_CONTINUING_SUCCESS);
        }
      }
      unbindVariablesBeginningAt(patternrecord, ubstackoffset + 1);
    }
    return (KWD_RDBMS_TERMINAL_FAILURE);
  }
}

Keyword* querySqlDatabaseSpecialist(ControlFrame* frame, Keyword* lastmove) {
  lastmove = lastmove;
  { Vector* arguments = frame->proposition->arguments;
    Object* database = argumentBoundTo((arguments->theArray)[0]);
    Object* query = argumentBoundTo((arguments->theArray)[1]);

    if ((!((boolean)(database))) ||
        ((!stringP(query)) ||
         (!testIsaP(database, SGT_RDBMS_RDBMS_SQL_DATABASE)))) {
      return (KWD_RDBMS_TERMINAL_FAILURE);
    }
    if (!((boolean)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_RDBMS_STELLA_ITERATOR, NULL)))))) {
      { KeyValueList* bindings = collectQueryDatabaseSpecialistBindings(frame, 2);

        query = wrapString(sdbc::instantiateSqlCmdTemplate(((StringWrapper*)(query))->wrapperValue, bindings));
        query = wrapString(sqlQueryInstantiateConstraints(((StringWrapper*)(query))->wrapperValue, bindings));
        setDynamicSlotValue(frame->dynamicSlots, SYM_RDBMS_STELLA_ITERATOR, sdbc::getResultSet(getConnectionFromDatabase(((LogicObject*)(database))), ((StringWrapper*)(query))->wrapperValue, 0), NULL);
      }
    }
    return (bindNextDatabaseTupleToArguments(frame, 2));
  }
}

Keyword* queryDatabaseSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Vector* arguments = proposition->arguments;
    Object* database = argumentBoundTo((arguments->theArray)[0]);
    Object* query = argumentBoundTo((arguments->theArray)[1]);

    if ((!((boolean)(database))) ||
        (!stringP(query))) {
      return (KWD_RDBMS_TERMINAL_FAILURE);
    }
    if (testIsaP(database, SGT_RDBMS_RDBMS_SQL_DATABASE)) {
      return (querySqlDatabaseSpecialist(frame, lastmove));
    }
    else {
      return (KWD_RDBMS_FAILURE);
    }
  }
}

void dbUpdateDemon(Proposition* dbproposition) {
  { Object* db = (dbproposition->arguments->theArray)[0];

    disconnectFromDatabase(((LogicObject*)(db)));
    bumpMemoizationTimestamp(KWD_RDBMS_EXTERNAL_DB_UPDATE);
  }
}

void checkForExternalDbUpdates(Proposition* proposition, LogicObject* database) {
  {
    proposition = proposition;
    database = database;
  }
}

Object* getQueryPatternMemoizationKey(Proposition* proposition) {
  { Surrogate* relationref = ((Surrogate*)(proposition->operatoR));
    Vector* iovars = getDescription(relationref)->ioVariables;
    List* unboundvars = list(0);
    OutputStringStream* key = newOutputStringStream();

    printLogicalForm(relationref, key);
    { Object* arg = NULL;
      Vector* vector000 = proposition->arguments;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = (vector000->theArray)[index000];
        *(key->nativeStream) << " ";
        if (variableP(arg) &&
            (!((boolean)(safeArgumentBoundTo(arg))))) {
          if (!(unboundvars->memberP(arg))) {
            unboundvars->insertLast(arg);
          }
          printLogicalForm(((PatternVariable*)((iovars->theArray)[(unboundvars->position(arg, 0))])), key);
        }
        else {
          printLogicalForm(safeArgumentBoundTo(arg), key);
        }
      }
    }
    return (wrapString(key->theStringReader()));
  }
}

Cons* coerceValues(Cons* values, RelationTableInfo* table) {
  { Cons* result = NIL;
    Module* module = NULL;
    boolean localP = false;

    { StringWrapper* value = NULL;
      Cons* iter000 = values;
      RelationColumnInfo* column = NULL;
      Cons* iter001 = table->columnList;
      Cons* collect000 = NULL;

      for  (; (!(iter000 == NIL)) &&
                (!(iter001 == NIL)); 
            iter000 = iter000->rest,
            iter001 = iter001->rest) {
        value = ((StringWrapper*)(iter000->value));
        column = ((RelationColumnInfo*)(iter001->value));
        module = column->module;
        localP = column->moduleLocalP;
        if (!((boolean)(module))) {
          module = getModuleUsingReference(column, values);
        }
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(coerceStringToPowerloomObject(unwrapString(value), column->columnType, module, localP), NIL);
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
            collect000->rest = cons(coerceStringToPowerloomObject(unwrapString(value), column->columnType, module, localP), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (result);
  }
}

Object* coerceStringToPowerloomObject(const char* value, NamedDescription* type, Module* module, boolean localP) {
  if (value == NULL) {
    return (NULL);
  }
  { Surrogate* typesurrogate = objectSurrogate(type);
    const char* typenamE = typesurrogate->symbolName;
    Object* result = NULL;

    if (typesurrogate == SGT_RDBMS_STELLA_STRING) {
      result = wrapString(value);
    }
    else if (stringEqlP(typenamE, "KEYWORD")) {
      result = internKeyword(value);
    }
    else if (stringEqlP(typenamE, "SEXP")) {
      result = readSExpressionFromString(value);
    }
    else if (isaP(typesurrogate->surrogateValue, SGT_RDBMS_LOGIC_NAMED_DESCRIPTION)) {
      result = findOrCreateInstance(value, type, module, localP);
      { 
        BIND_STELLA_SPECIAL(oMODULEo, Module*, module);
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
        assertIsaProposition(result, typesurrogate);
      }
    }
    else if (subtypeOfP(typesurrogate, SGT_RDBMS_STELLA_BOOLEAN)) {
      result = (stringEqlP(value, "1") ? SGT_RDBMS_STELLA_TRUE->surrogateValue : SGT_RDBMS_STELLA_FALSE->surrogateValue);
    }
    else if (subtypeOfP(typesurrogate, SGT_RDBMS_STELLA_INTEGER)) {
      result = wrapInteger(numberStringToInteger(value));
    }
    else if (subtypeOfP(typesurrogate, SGT_RDBMS_STELLA_NUMBER)) {
      result = wrapFloat(stringToFloat(value));
    }
    else if (subtypeOfP(typesurrogate, SGT_RDBMS_STELLA_THING)) {
      result = findOrCreateInstance(value, type, module, localP);
    }
    else {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "RDBMS: Don't yet know how to coerce string \"" << "`" << value << "'" << "\" to type " << "`" << typenamE << "'" << std::endl;
    }
    return (result);
  }
}

int numberStringToInteger(const char* x) {
  try {
    return (((int)(stringToInteger(x))));
  }
  catch (std::exception ) {
    return (((int)(stringToFloat(x))));
  }
}

const char* coercePowerloomObjectToString(Object* object, NamedDescription* type) {
  type = type;
  { 
    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
    { Surrogate* testValue000 = safePrimaryType(object);

      if (subtypeOfStringP(testValue000)) {
        { Object* object000 = object;
          StringWrapper* object = ((StringWrapper*)(object000));

          return (object->wrapperValue);
        }
      }
      else if (subtypeOfP(testValue000, SGT_RDBMS_LOGIC_LOGIC_OBJECT)) {
        { Object* object001 = object;
          LogicObject* object = ((LogicObject*)(object001));

          return (object->surrogateValueInverse->symbolName);
        }
      }
      else {
        return (stringify(object));
      }
    }
  }
}

Object* findOrCreateInstance(const char* name, NamedDescription* type, Module* module, boolean localP) {
  // Find an existing instance with `name' in `module' or create one with `type'
  // if it does not yet exist.  If `local?' do not look into any inherited modules.
  { Surrogate* instanceref = lookupSurrogateInModule(name, module, localP);
    Object* value = (((boolean)(instanceref)) ? instanceref->surrogateValue : ((Object*)(NULL)));
    Surrogate* typeref = NULL;

    if (((boolean)(value))) {
      if (stellaClassP(value)) {
        return (classDgetDescription(((Class*)(value))));
      }
      else {
        return (value);
      }
    }
    else if (!((boolean)(instanceref))) {
      if (!(name[0] == '(')) {
        instanceref = internSurrogateInModule(name, module, localP);
      }
    }
    typeref = objectSurrogate(type);
    if (typeref == SGT_RDBMS_STELLA_THING) {
      typeref = NULL;
    }
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, module);
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      if (((boolean)(instanceref))) {
        return (createLogicInstance(instanceref, typeref));
      }
      else {
        { Object* skolem = evaluateTerm(readSExpressionFromString(name));

          assertIsaProposition(skolem, typeref);
          return (skolem);
        }
      }
    }
  }
}

const char* createSqlAssertionFromProposition(Proposition* proposition, Keyword* mode) {
  { Surrogate* relationRef = getPropositionBaseOperator(proposition);
    NamedDescription* relation = getDescription(relationRef);
    boolean isfunctionP = logic::functionP(relationRef);
    RelationTableInfo* tableInfo = getRelationTableInfo(relation);
    const char* tableAlias = tableInfo->tableAlias;
    Skolem* skolemTerm = NULL;
    Object* functionValue = NULL;
    Vector* arguments = NULL;
    OutputStringStream* sql = newOutputStringStream();
    boolean firstP = true;

    tableInfo->tableAlias = NULL;
    if (isfunctionP) {
      {
        skolemTerm = getSkolemAndValueTerms(proposition, functionValue);
        { Vector* args = skolemTerm->definingProposition->arguments;
          int argsLength = args->length();

          arguments = stella::newVector(((mode == KWD_RDBMS_CLIP) ? (argsLength - 1) : argsLength));
          { int i = NULL_INTEGER;
            int iter000 = 0;
            int upperBound000 = argsLength - 2;

            for  (; iter000 <= upperBound000; 
                  iter000 = iter000 + 1) {
              i = iter000;
              (arguments->theArray)[i] = ((args->theArray)[i]);
            }
          }
          if (!(mode == KWD_RDBMS_CLIP)) {
            (arguments->theArray)[(argsLength - 1)] = functionValue;
          }
        }
      }
    }
    else {
      arguments = proposition->arguments;
    }
    if (mode == KWD_RDBMS_ASSERT) {
      *(sql->nativeStream) << "INSERT INTO " << tableInfo->tableName;
      *(sql->nativeStream) << " (";
      printSqlColumnList(sql, tableInfo);
      *(sql->nativeStream) << ") VALUES (";
      { RelationColumnInfo* column = NULL;
        Cons* iter001 = tableInfo->columnList;
        Object* arg = NULL;
        Vector* vector000 = arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; (!(iter001 == NIL)) &&
                  (index000 < length000); 
              iter001 = iter001->rest,
              index000 = index000 + 1) {
          column = ((RelationColumnInfo*)(iter001->value));
          arg = (vector000->theArray)[index000];
          if ((!((boolean)(arg))) ||
              skolemP(arg)) {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "Can't assert non-ground items to table from " << "`" << proposition << "'";
              throw *newStellaException(stream000->theStringReader());
            }
          }
          else if (firstP) {
            firstP = false;
          }
          else {
            *(sql->nativeStream) << ", ";
          }
          printSqlValue(sql, arg, column);
        }
      }
      *(sql->nativeStream) << ")";
    }
    else if ((mode == KWD_RDBMS_RETRACT) ||
        (mode == KWD_RDBMS_CLIP)) {
      *(sql->nativeStream) << "DELETE FROM " << tableInfo->tableName << " ";
      printSqlConstraintList(sql, tableInfo, arguments);
    }
    else {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "`" << mode << "'" << " is not a valid case option";
        throw *newStellaException(stream001->theStringReader());
      }
    }
    tableInfo->tableAlias = tableAlias;
    bumpMemoizationTimestamp(KWD_RDBMS_EXTERNAL_DB_UPDATE);
    return (sql->theStringReader());
  }
}

void dbRelationGoesTrue(Proposition* proposition) {
  { Surrogate* baseRelation = getPropositionBaseOperator(proposition);
    sdbc::Connection* connection = getConnectionFromPredicate(baseRelation);

    if (oCLIPPINGENABLEDpo &&
        logic::functionP(getDescription(baseRelation))) {
      sdbc::executeSql(connection, wrapString(createSqlAssertionFromProposition(proposition, KWD_RDBMS_CLIP)), NIL);
    }
    else {
      sdbc::executeSql(connection, wrapString(createSqlAssertionFromProposition(proposition, KWD_RDBMS_RETRACT)), NIL);
    }
    sdbc::executeSql(connection, wrapString(createSqlAssertionFromProposition(proposition, KWD_RDBMS_ASSERT)), NIL);
  }
}

void dbRelationGoesUnknown(Proposition* proposition) {
  { sdbc::Connection* connection = getConnectionFromPredicate(getPropositionBaseOperator(proposition));

    sdbc::executeSql(connection, wrapString(createSqlAssertionFromProposition(proposition, KWD_RDBMS_RETRACT)), NIL);
  }
}

void dbRelationGoesFalse(Proposition* proposition) {
  *(STANDARD_WARNING->nativeStream) << "Warning: " << "RDBMS: DB relations can't be made false.  Making " << "`" << proposition << "'" << " unknown instead." << std::endl;
  dbRelationGoesUnknown(proposition);
}

void dbRelationUpdateDemon(Proposition* proposition, Keyword* updateMode) {
  if ((updateMode == KWD_RDBMS_ASSERT_TRUE) ||
      (updateMode == KWD_RDBMS_PRESUME_TRUE)) {
    dbRelationGoesTrue(proposition);
    destroyRedundantProposition(proposition);
  }
  else if (updateMode == KWD_RDBMS_RETRACT_TRUE) {
    dbRelationGoesUnknown(proposition);
    destroyRedundantProposition(proposition);
  }
  else if (updateMode == KWD_RDBMS_RETRACT_FALSE) {
    *(STANDARD_WARNING->nativeStream) << "Warning: " << "RDBMS: DB relations can't be false." << std::endl;
    dbRelationGoesUnknown(proposition);
    destroyRedundantProposition(proposition);
  }
  else if ((updateMode == KWD_RDBMS_ASSERT_FALSE) ||
      (updateMode == KWD_RDBMS_PRESUME_FALSE)) {
    dbRelationGoesFalse(proposition);
    destroyRedundantProposition(proposition);
  }
  else if (updateMode == KWD_RDBMS_CONCEIVE) {
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << updateMode << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void helpStartupRdbms1() {
  {
    SYM_RDBMS_RDBMS_DEFUNTABLE = ((Symbol*)(internRigidSymbolWrtModule("DEFUNTABLE", NULL, 0)));
    SYM_RDBMS_RDBMS_RELATION_TABLE = ((Symbol*)(internRigidSymbolWrtModule("RELATION-TABLE", NULL, 0)));
    SYM_RDBMS_RDBMS_RELATION_DATABASE = ((Symbol*)(internRigidSymbolWrtModule("RELATION-DATABASE", NULL, 0)));
    SYM_RDBMS_PL_KERNEL_KB_RELATION_SPECIALIST = ((Symbol*)(internRigidSymbolWrtModule("RELATION-SPECIALIST", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_RDBMS_RDBMS_DBTABLE_SPECIALIST = ((Symbol*)(internRigidSymbolWrtModule("DBTABLE-SPECIALIST", NULL, 0)));
    KWD_RDBMS_AXIOMS = ((Keyword*)(internRigidSymbolWrtModule("AXIOMS", NULL, 2)));
    SYM_RDBMS_RDBMS_DEFTABLE = ((Symbol*)(internRigidSymbolWrtModule("DEFTABLE", NULL, 0)));
    SGT_RDBMS_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
    KWD_RDBMS_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    KWD_RDBMS_NAME = ((Keyword*)(internRigidSymbolWrtModule("NAME", NULL, 2)));
    KWD_RDBMS_VARIABLE = ((Keyword*)(internRigidSymbolWrtModule("VARIABLE", NULL, 2)));
    KWD_RDBMS_TYPE = ((Keyword*)(internRigidSymbolWrtModule("TYPE", NULL, 2)));
    KWD_RDBMS_MODULE_NAME = ((Keyword*)(internRigidSymbolWrtModule("MODULE-NAME", NULL, 2)));
    KWD_RDBMS_MODULE_REFERENCE = ((Keyword*)(internRigidSymbolWrtModule("MODULE-REFERENCE", NULL, 2)));
    SYM_RDBMS_RDBMS_RELATION_COLUMN_NAME = ((Symbol*)(internRigidSymbolWrtModule("RELATION-COLUMN-NAME", NULL, 0)));
    SYM_RDBMS_RDBMS_RELATION_COLUMN_MODULE_NAME = ((Symbol*)(internRigidSymbolWrtModule("RELATION-COLUMN-MODULE-NAME", NULL, 0)));
    SYM_RDBMS_RDBMS_RELATION_COLUMN_MODULE_REFERENCE = ((Symbol*)(internRigidSymbolWrtModule("RELATION-COLUMN-MODULE-REFERENCE", NULL, 0)));
    SYM_RDBMS_RDBMS_DEFDB = ((Symbol*)(internRigidSymbolWrtModule("DEFDB", NULL, 0)));
    SYM_RDBMS_RDBMS_DATABASE = ((Symbol*)(internRigidSymbolWrtModule("DATABASE", NULL, 0)));
    KWD_RDBMS_CONNECTION_STRING = ((Keyword*)(internRigidSymbolWrtModule("CONNECTION-STRING", NULL, 2)));
    SGT_RDBMS_STELLA_STRING = ((Surrogate*)(internRigidSymbolWrtModule("STRING", getStellaModule("/STELLA", true), 1)));
    KWD_RDBMS_JDBC_CONNECTION_STRING = ((Keyword*)(internRigidSymbolWrtModule("JDBC-CONNECTION-STRING", NULL, 2)));
    KWD_RDBMS_ODBC_CONNECTION_STRING = ((Keyword*)(internRigidSymbolWrtModule("ODBC-CONNECTION-STRING", NULL, 2)));
    KWD_RDBMS_DSN = ((Keyword*)(internRigidSymbolWrtModule("DSN", NULL, 2)));
    KWD_RDBMS_DB = ((Keyword*)(internRigidSymbolWrtModule("DB", NULL, 2)));
    KWD_RDBMS_HOST = ((Keyword*)(internRigidSymbolWrtModule("HOST", NULL, 2)));
    KWD_RDBMS_PORT = ((Keyword*)(internRigidSymbolWrtModule("PORT", NULL, 2)));
    SGT_RDBMS_STELLA_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER", getStellaModule("/STELLA", true), 1)));
    KWD_RDBMS_USER = ((Keyword*)(internRigidSymbolWrtModule("USER", NULL, 2)));
    KWD_RDBMS_PASSWORD = ((Keyword*)(internRigidSymbolWrtModule("PASSWORD", NULL, 2)));
    KWD_RDBMS_MODULE = ((Keyword*)(internRigidSymbolWrtModule("MODULE", NULL, 2)));
    SGT_RDBMS_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", getStellaModule("/STELLA", true), 1)));
    KWD_RDBMS_CONFIGURATION = ((Keyword*)(internRigidSymbolWrtModule("CONFIGURATION", NULL, 2)));
    SGT_RDBMS_STELLA_CONFIGURATION_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("CONFIGURATION-TABLE", getStellaModule("/STELLA", true), 1)));
    KWD_RDBMS_DB_NAME = ((Keyword*)(internRigidSymbolWrtModule("DB-NAME", NULL, 2)));
    SYM_RDBMS_RDBMS_DEFQUERY = ((Symbol*)(internRigidSymbolWrtModule("DEFQUERY", NULL, 0)));
    SYM_RDBMS_RDBMS_QUERY_SPECIALIST = ((Symbol*)(internRigidSymbolWrtModule("QUERY-SPECIALIST", NULL, 0)));
    SGT_RDBMS_RDBMS_CONNECTION_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("CONNECTION-WRAPPER", NULL, 1)));
    SYM_RDBMS_STELLA_WRAPPER_VALUE = ((Symbol*)(internRigidSymbolWrtModule("WRAPPER-VALUE", getStellaModule("/STELLA", true), 0)));
    SGT_RDBMS_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", getStellaModule("/LOGIC", true), 1)));
    SGT_RDBMS_RDBMS_PROTOCOL = ((Surrogate*)(internRigidSymbolWrtModule("PROTOCOL", NULL, 1)));
    SGT_RDBMS_RDBMS_SERVER_TYPE = ((Surrogate*)(internRigidSymbolWrtModule("SERVER-TYPE", NULL, 1)));
    SGT_RDBMS_RDBMS_HOST = ((Surrogate*)(internRigidSymbolWrtModule("HOST", NULL, 1)));
    SGT_RDBMS_RDBMS_PORT = ((Surrogate*)(internRigidSymbolWrtModule("PORT", NULL, 1)));
    SGT_RDBMS_RDBMS_USER = ((Surrogate*)(internRigidSymbolWrtModule("USER", NULL, 1)));
    SGT_RDBMS_RDBMS_PASSWORD = ((Surrogate*)(internRigidSymbolWrtModule("PASSWORD", NULL, 1)));
    SGT_RDBMS_RDBMS_DB_NAME = ((Surrogate*)(internRigidSymbolWrtModule("DB-NAME", NULL, 1)));
    SGT_RDBMS_RDBMS_ODBC_CONNECTION_STRING = ((Surrogate*)(internRigidSymbolWrtModule("ODBC-CONNECTION-STRING", NULL, 1)));
    SGT_RDBMS_RDBMS_CONNECTION_STRING = ((Surrogate*)(internRigidSymbolWrtModule("CONNECTION-STRING", NULL, 1)));
    SGT_RDBMS_RDBMS_DSN = ((Surrogate*)(internRigidSymbolWrtModule("DSN", NULL, 1)));
    KWD_RDBMS_PROTOCOL = ((Keyword*)(internRigidSymbolWrtModule("PROTOCOL", NULL, 2)));
    KWD_RDBMS_SERVER_TYPE = ((Keyword*)(internRigidSymbolWrtModule("SERVER-TYPE", NULL, 2)));
    KWD_RDBMS_EXTENSIONAL_ASSERTION = ((Keyword*)(internRigidSymbolWrtModule("EXTENSIONAL-ASSERTION", NULL, 2)));
    SGT_RDBMS_RDBMS_DB_CONNECTION = ((Surrogate*)(internRigidSymbolWrtModule("DB-CONNECTION", NULL, 1)));
    SGT_RDBMS_RDBMS_RELATION_DATABASE = ((Surrogate*)(internRigidSymbolWrtModule("RELATION-DATABASE", NULL, 1)));
    SYM_RDBMS_LOGIC_pX = ((Symbol*)(internRigidSymbolWrtModule("?X", getStellaModule("/LOGIC", true), 0)));
    SGT_RDBMS_RDBMS_RELATION_TABLE_INFO = ((Surrogate*)(internRigidSymbolWrtModule("RELATION-TABLE-INFO", NULL, 1)));
    SYM_RDBMS_STELLA_RELATION = ((Symbol*)(internRigidSymbolWrtModule("RELATION", getStellaModule("/STELLA", true), 0)));
    SYM_RDBMS_RDBMS_DBMS_NAME = ((Symbol*)(internRigidSymbolWrtModule("DBMS-NAME", NULL, 0)));
    SYM_RDBMS_STELLA_TABLE_NAME = ((Symbol*)(internRigidSymbolWrtModule("TABLE-NAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupRdbms2() {
  {
    SYM_RDBMS_RDBMS_TABLE_ALIAS = ((Symbol*)(internRigidSymbolWrtModule("TABLE-ALIAS", NULL, 0)));
    SYM_RDBMS_RDBMS_COLUMN_LIST = ((Symbol*)(internRigidSymbolWrtModule("COLUMN-LIST", NULL, 0)));
    SYM_RDBMS_RDBMS_COLUMN_VECTOR = ((Symbol*)(internRigidSymbolWrtModule("COLUMN-VECTOR", NULL, 0)));
    SYM_RDBMS_RDBMS_COLUMN_INDEX = ((Symbol*)(internRigidSymbolWrtModule("COLUMN-INDEX", NULL, 0)));
    SYM_RDBMS_RDBMS_ADJUNCT = ((Symbol*)(internRigidSymbolWrtModule("ADJUNCT", NULL, 0)));
    SGT_RDBMS_RDBMS_RELATION_COLUMN_INFO = ((Surrogate*)(internRigidSymbolWrtModule("RELATION-COLUMN-INFO", NULL, 1)));
    SYM_RDBMS_RDBMS_TABLE_INFO = ((Symbol*)(internRigidSymbolWrtModule("TABLE-INFO", NULL, 0)));
    SYM_RDBMS_RDBMS_COLUMN_NAME = ((Symbol*)(internRigidSymbolWrtModule("COLUMN-NAME", NULL, 0)));
    SYM_RDBMS_RDBMS_COLUMN_VARIABLE = ((Symbol*)(internRigidSymbolWrtModule("COLUMN-VARIABLE", NULL, 0)));
    SYM_RDBMS_RDBMS_COLUMN_TYPE = ((Symbol*)(internRigidSymbolWrtModule("COLUMN-TYPE", NULL, 0)));
    SYM_RDBMS_RDBMS_COLUMN_DB_TYPE = ((Symbol*)(internRigidSymbolWrtModule("COLUMN-DB-TYPE", NULL, 0)));
    SYM_RDBMS_STELLA_MODULE_NAME = ((Symbol*)(internRigidSymbolWrtModule("MODULE-NAME", getStellaModule("/STELLA", true), 0)));
    SYM_RDBMS_RDBMS_MODULE_REFERENCE = ((Symbol*)(internRigidSymbolWrtModule("MODULE-REFERENCE", NULL, 0)));
    SYM_RDBMS_STELLA_MODULE = ((Symbol*)(internRigidSymbolWrtModule("MODULE", getStellaModule("/STELLA", true), 0)));
    SYM_RDBMS_RDBMS_MODULE_LOCALp = ((Symbol*)(internRigidSymbolWrtModule("MODULE-LOCAL?", NULL, 0)));
    SYM_RDBMS_RDBMS_MODULE_REFERENCE_COLUMN = ((Symbol*)(internRigidSymbolWrtModule("MODULE-REFERENCE-COLUMN", NULL, 0)));
    SYM_RDBMS_RDBMS_COERCION_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("COERCION-FUNCTION", NULL, 0)));
    KWD_RDBMS_UNKNOWN = ((Keyword*)(internRigidSymbolWrtModule("UNKNOWN", NULL, 2)));
    SGT_RDBMS_RDBMS_RELATION_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("RELATION-TABLE", NULL, 1)));
    SGT_RDBMS_RDBMS_F_GET_RELATION_TABLE_INFO_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-GET-RELATION-TABLE-INFO-MEMO-TABLE-000", NULL, 1)));
    KWD_RDBMS_STRING_CONSTANT = ((Keyword*)(internRigidSymbolWrtModule("STRING-CONSTANT", NULL, 2)));
    SGT_RDBMS_STELLA_NUMBER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER", getStellaModule("/STELLA", true), 1)));
    SGT_RDBMS_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", getStellaModule("/STELLA", true), 1)));
    KWD_RDBMS_MYSQL = ((Keyword*)(internRigidSymbolWrtModule("MYSQL", NULL, 2)));
    SGT_RDBMS_STELLA_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("STRING-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SYM_RDBMS_STELLA_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR", getStellaModule("/STELLA", true), 0)));
    SGT_RDBMS_RDBMS_DATABASE = ((Surrogate*)(internRigidSymbolWrtModule("DATABASE", NULL, 1)));
    SGT_RDBMS_RDBMS_F_ALLOCATE_DBTABLE_SPECIALIST_ITERATOR_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-ALLOCATE-DBTABLE-SPECIALIST-ITERATOR-MEMO-TABLE-000", NULL, 1)));
    KWD_RDBMS_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("FAILURE", NULL, 2)));
    KWD_RDBMS_DB_LOOKUP = ((Keyword*)(internRigidSymbolWrtModule("DB-LOOKUP", NULL, 2)));
    KWD_RDBMS_CONTINUING_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("CONTINUING-SUCCESS", NULL, 2)));
    KWD_RDBMS_FINAL_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("FINAL-SUCCESS", NULL, 2)));
    KWD_RDBMS_TECHNICAL = ((Keyword*)(internRigidSymbolWrtModule("TECHNICAL", NULL, 2)));
    KWD_RDBMS_LAY = ((Keyword*)(internRigidSymbolWrtModule("LAY", NULL, 2)));
    SYM_RDBMS_RDBMS_pREL = ((Symbol*)(internRigidSymbolWrtModule("?REL", NULL, 0)));
    SYM_RDBMS_RDBMS_pEV = ((Symbol*)(internRigidSymbolWrtModule("?EV", NULL, 0)));
    SYM_RDBMS_RDBMS_pDB = ((Symbol*)(internRigidSymbolWrtModule("?DB", NULL, 0)));
    SYM_RDBMS_RDBMS_pARGS = ((Symbol*)(internRigidSymbolWrtModule("?ARGS", NULL, 0)));
    SYM_RDBMS_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", getStellaModule("/STELLA", true), 0)));
    SYM_RDBMS_RDBMS_QUERY_PATTERN = ((Symbol*)(internRigidSymbolWrtModule("QUERY-PATTERN", NULL, 0)));
    SYM_RDBMS_STELLA_EXISTS = ((Symbol*)(internRigidSymbolWrtModule("EXISTS", getStellaModule("/STELLA", true), 0)));
    SYM_RDBMS_RDBMS_pDB_TYPE = ((Symbol*)(internRigidSymbolWrtModule("?DB-TYPE", NULL, 0)));
    SYM_RDBMS_RDBMS_SUPPORTS_DB_TYPE = ((Symbol*)(internRigidSymbolWrtModule("SUPPORTS-DB-TYPE", NULL, 0)));
    SYM_RDBMS_RDBMS_INSTANCE_OF = ((Symbol*)(internRigidSymbolWrtModule("INSTANCE-OF", NULL, 0)));
    KWD_RDBMS_DONT_OPTIMIZEp = ((Keyword*)(internRigidSymbolWrtModule("DONT-OPTIMIZE?", NULL, 2)));
    KWD_RDBMS_HOW_MANY = ((Keyword*)(internRigidSymbolWrtModule("HOW-MANY", NULL, 2)));
    KWD_RDBMS_ALL = ((Keyword*)(internRigidSymbolWrtModule("ALL", NULL, 2)));
    KWD_RDBMS_INFERENCE_LEVEL = ((Keyword*)(internRigidSymbolWrtModule("INFERENCE-LEVEL", NULL, 2)));
    KWD_RDBMS_ASSERTION = ((Keyword*)(internRigidSymbolWrtModule("ASSERTION", NULL, 2)));
    SYM_RDBMS_RDBMS_F_GET_QUERY_PATTERN_EVALUATORS_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("F-GET-QUERY-PATTERN-EVALUATORS-QUERY-000", NULL, 0)));
    SGT_RDBMS_RDBMS_F_GET_QUERY_PATTERN_EVALUATORS_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-GET-QUERY-PATTERN-EVALUATORS-MEMO-TABLE-000", NULL, 1)));
    SYM_RDBMS_RDBMS_F_GET_QUERY_PATTERN_EVALUATORS_QUERY_001 = ((Symbol*)(internRigidSymbolWrtModule("F-GET-QUERY-PATTERN-EVALUATORS-QUERY-001", NULL, 0)));
    SGT_RDBMS_RDBMS_F_SQL_JOIN_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-SQL-JOIN-MEMO-TABLE-000", NULL, 1)));
    KWD_RDBMS_VALUE = ((Keyword*)(internRigidSymbolWrtModule("VALUE", NULL, 2)));
    KWD_RDBMS_WHITE_SPACE = ((Keyword*)(internRigidSymbolWrtModule("WHITE-SPACE", NULL, 2)));
    KWD_RDBMS_SET = ((Keyword*)(internRigidSymbolWrtModule("SET", NULL, 2)));
    KWD_RDBMS_NONE = ((Keyword*)(internRigidSymbolWrtModule("NONE", NULL, 2)));
    SGT_RDBMS_RDBMS_F_SQL_QUERY_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-SQL-QUERY-MEMO-TABLE-000", NULL, 1)));
    KWD_RDBMS_TERMINAL_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("TERMINAL-FAILURE", NULL, 2)));
    SGT_RDBMS_RDBMS_SQL_DATABASE = ((Surrogate*)(internRigidSymbolWrtModule("SQL-DATABASE", NULL, 1)));
  }
}

void helpStartupRdbms3() {
  {
    KWD_RDBMS_EXTERNAL_DB_UPDATE = ((Keyword*)(internRigidSymbolWrtModule("EXTERNAL-DB-UPDATE", NULL, 2)));
    SGT_RDBMS_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", getStellaModule("/LOGIC", true), 1)));
    SGT_RDBMS_STELLA_TRUE = ((Surrogate*)(internRigidSymbolWrtModule("TRUE", getStellaModule("/STELLA", true), 1)));
    SGT_RDBMS_STELLA_FALSE = ((Surrogate*)(internRigidSymbolWrtModule("FALSE", getStellaModule("/STELLA", true), 1)));
    SGT_RDBMS_STELLA_THING = ((Surrogate*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 1)));
    KWD_RDBMS_CLIP = ((Keyword*)(internRigidSymbolWrtModule("CLIP", NULL, 2)));
    KWD_RDBMS_ASSERT = ((Keyword*)(internRigidSymbolWrtModule("ASSERT", NULL, 2)));
    KWD_RDBMS_RETRACT = ((Keyword*)(internRigidSymbolWrtModule("RETRACT", NULL, 2)));
    KWD_RDBMS_ASSERT_TRUE = ((Keyword*)(internRigidSymbolWrtModule("ASSERT-TRUE", NULL, 2)));
    KWD_RDBMS_PRESUME_TRUE = ((Keyword*)(internRigidSymbolWrtModule("PRESUME-TRUE", NULL, 2)));
    KWD_RDBMS_RETRACT_TRUE = ((Keyword*)(internRigidSymbolWrtModule("RETRACT-TRUE", NULL, 2)));
    KWD_RDBMS_RETRACT_FALSE = ((Keyword*)(internRigidSymbolWrtModule("RETRACT-FALSE", NULL, 2)));
    KWD_RDBMS_ASSERT_FALSE = ((Keyword*)(internRigidSymbolWrtModule("ASSERT-FALSE", NULL, 2)));
    KWD_RDBMS_PRESUME_FALSE = ((Keyword*)(internRigidSymbolWrtModule("PRESUME-FALSE", NULL, 2)));
    KWD_RDBMS_CONCEIVE = ((Keyword*)(internRigidSymbolWrtModule("CONCEIVE", NULL, 2)));
    SYM_RDBMS_RDBMS_STARTUP_RDBMS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-RDBMS", NULL, 0)));
    SYM_RDBMS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupRdbms4() {
  {
    defineFunctionObject("DEFUNTABLE", "(DEFUN (DEFUNTABLE LOGIC-OBJECT) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a database table and map it to a function\nThe accepted syntax is:\n	 \n (defuntable <relconst> <dbconst> <tablename> (<columndecl>+)\n    [<keyword-option>*]).\n\n<columndecl>'s specify the names (and optionally types) of the columns\nof the database table.  They have the same form as a PowerLoom <vardecl>, but\ncolumn names can be specified with or without question marks.  If there\nis a question mark it will be stripped to determine the column name, otherwise\na question mark will be added to generate the relation variable.  The optional\ntype specifies the domain of that argument and controls any necessary coercion.\nThe name of each column HAS TO MATCH one of the columns of <tablename>, however,\nthe order is irrelevant and arbitrary projections can be defined by only\nspecifying some subset of <tablename>'s columns.\n\nSee `deffunction' for legal key" "word options.\n\")", ((cpp_function_code)(&defuntable)), ((cpp_function_code)(&defuntableEvaluatorWrapper)));
    defineFunctionObject("CALL-DEFUNTABLE", "(DEFUN (CALL-DEFUNTABLE NAMED-DESCRIPTION) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of the `deftable' command (which see).\nExpects the same arguments as `deftable' but supplied as a list.\" :PUBLIC? TRUE)", ((cpp_function_code)(&callDefuntable)), NULL);
    defineFunctionObject("DEFTABLE", "(DEFUN (DEFTABLE LOGIC-OBJECT) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a database table and map it to a relation.\nThe accepted syntax is:\n	 \n (deftable <relconst> <dbconst> <tablename> (<columndecl>+)\n    [<keyword-option>*]).\n	\n<columndecl>'s specify the names (and optionally types) of the columns\nof the database table.  They have the same form as a PowerLoom <vardecl>, but\ncolumn names can be specified with or without question marks.  If there\nis a question mark it will be stripped to determine the column name, otherwise\na question mark will be added to generate the relation variable.  The optional\ntype specifies the domain of that argument and controls any necessary coercion.\nThe name of each column HAS TO MATCH one of the columns of <tablename>, however,\nthe order is irrelevant and arbitrary projections can be defined by only\nspecifying some subset of <tablename>'s columns.\n\nSee `defrelation' for legal keywo" "rd options.\n\")", ((cpp_function_code)(&deftable)), ((cpp_function_code)(&deftableEvaluatorWrapper)));
    defineFunctionObject("CALL-DEFTABLE", "(DEFUN (CALL-DEFTABLE NAMED-DESCRIPTION) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of the `deftable' command (which see).\nExpects the same arguments as `deftable' but supplied as a list.\" :PUBLIC? TRUE)", ((cpp_function_code)(&callDeftable)), NULL);
    defineFunctionObject("PARSE-ONE-COLUMN-SPEC", "(DEFUN (PARSE-ONE-COLUMN-SPEC PROPERTY-LIST) ((COLUMNSPEC OBJECT)))", ((cpp_function_code)(&parseOneColumnSpec)), NULL);
    defineFunctionObject("PARSE-COLUMN-SPECS", "(DEFUN (PARSE-COLUMN-SPECS CONS CONS) ((RELCONST OBJECT) (COLUMNSPECS OBJECT)))", ((cpp_function_code)(&parseColumnSpecs)), NULL);
    defineFunctionObject("DEFDB", "(DEFUN (DEFDB LOGIC-OBJECT) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a database instance.  The accepted syntax is:\n	 \n (defdb <dbconst>\n    [:protocol <protocol string>]\n    [:server-type <server type string>]\n    [:dsn <ODBC data-source name string>]\n    [:odbc-connection-string <ODBC connection string>]\n    [:jdbc-connection-string <JDBC connection string>]\n    [:connection-string <connection string>] ;; deprecated\n    [:host <server host string>]\n    [:port <server host port>]\n    [:user <user name string>]\n    [:password <password string>]\n    [:db-name <database name string>]\n    [<keyword-option>*])\n	\nConnection information can be asserted explicitly later or be done\nprogrammatically, as long as it is done before the first time a\nconnection attempt is made (e.g., during a query).  This information\nis passed to `SDBC/connect' (which see for more documentation on\nways to specify a connection).  For exampl" "e, for ODBC a :DSN, an\n:ODBC-CONNECTION-STRING or an appropriate combination of :HOST,\n:PORT, :USER, :PASSWORD AND :DB-NAME can be used.  For JDBC a\n:JDBC-CONNECTION-STRING or combination of :HOST, :PORT, etc. can\nbe used.  See `defobject' for additional legal keyword options.\n\")", ((cpp_function_code)(&defdb)), ((cpp_function_code)(&defdbEvaluatorWrapper)));
    defineFunctionObject("CALL-DEFDB", "(DEFUN (CALL-DEFDB LOGIC-OBJECT) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of of the `defdb' command (which see).\nExpects the same arguments as `defdb' but supplied as a list.\" :PUBLIC? TRUE)", ((cpp_function_code)(&callDefdb)), NULL);
    defineFunctionObject("EXTRACT-RDBMS-OPTIONS", "(DEFUN (EXTRACT-RDBMS-OPTIONS CONS CONS) ((SELFNAME SYMBOL) (OPTIONS CONS)))", ((cpp_function_code)(&extractRdbmsOptions)), NULL);
    defineFunctionObject("ASSERT-RDBMS-CONNECTION-INFO", "(DEFUN ASSERT-RDBMS-CONNECTION-INFO ((DB-INSTANCE-NAME STRING) |&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Assert DB connectivity information about the DB instance `db-instance-name' (for\nexample, \\\"edb\\\") according to `options'.  Looks up `db-instance-name' in the module\nspecified by the :module option (defaults to current module) and retracts any\npreexisting connection information.  New assertions are also made in that module.\nDefault values are taken from the configuration table specified by :configuration.\n\nUnderstands the following options, with default values specified by the configuration\nkey in parentheses:\n   :connection-string (\\\"DBConnection\\\"),\n   :jdbc-connection-string (\\\"JDBCString\\\"),\n   :odbc-connection-string (\\\"ODBCString\\\"),\n   :dsn (\\\"DSN\\\"),\n   :db (\\\"DBName\\\"),\n   :host (\\\"DBHost\\\"),\n   :port (\\\"DBPort\\\"),\n   :user (\\\"DBUser\\\"),\n   :password (\\\"DBPassword\\\"),\n   :module,\n   :configuration.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&assertRdbmsConnectionInfo)), ((cpp_function_code)(&assertRdbmsConnectionInfoEvaluatorWrapper)));
    defineFunctionObject("DEFQUERY", "(DEFUN (DEFQUERY LOGIC-OBJECT) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) an (external) query and map it to a relation.\nThe accepted syntax is:\n	 \n (defquery <relconst> (<vardecl>+)\n    {:query-pattern (<query-evaluator> <dbconst> <arguments-string>)}*\n    [<keyword-option>*]).\n	\n<query-evaluator> has to be a `Computed-Procedure' that takes the following\nthree arguments: the <relconst> query proposition, the database object <dbconst>\nand the arguments string.  It needs to return an iterator that generates CONS\ntuples whose elements will be bound in sequence to <relconst>'s arguments.\n\nSee `defrelation' for other legal keyword options.\n\")", ((cpp_function_code)(&defquery)), ((cpp_function_code)(&defqueryEvaluatorWrapper)));
    defineFunctionObject("CALL-DEFQUERY", "(DEFUN (CALL-DEFQUERY NAMED-DESCRIPTION) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of the `defquery' command (which see).\nExpects the same arguments as `deftable' but supplied as a list.\" :PUBLIC? TRUE)", ((cpp_function_code)(&callDefquery)), NULL);
    defineFunctionObject("NORMALIZE-CONNECTION-ARGUMENT", "(DEFUN (NORMALIZE-CONNECTION-ARGUMENT STRING-WRAPPER) ((ARG OBJECT)))", ((cpp_function_code)(&normalizeConnectionArgument)), NULL);
    defineFunctionObject("CONNECT-TO-DATABASE", "(DEFUN (CONNECT-TO-DATABASE /SDBC/CONNECTION) ((DATABASE LOGIC-OBJECT)))", ((cpp_function_code)(&connectToDatabase)), NULL);
    defineFunctionObject("DISCONNECT-FROM-DATABASE", "(DEFUN DISCONNECT-FROM-DATABASE ((DATABASE LOGIC-OBJECT)))", ((cpp_function_code)(&disconnectFromDatabase)), NULL);
    defineFunctionObject("GET-CONNECTION-FROM-DATABASE", "(DEFUN (GET-CONNECTION-FROM-DATABASE /SDBC/CONNECTION) ((DATABASE LOGIC-OBJECT)))", ((cpp_function_code)(&getConnectionFromDatabase)), NULL);
    defineFunctionObject("GET-CONNECTION-FROM-PREDICATE", "(DEFUN (GET-CONNECTION-FROM-PREDICATE /SDBC/CONNECTION) ((RELATIONREF SURROGATE)))", ((cpp_function_code)(&getConnectionFromPredicate)), NULL);
    defineFunctionObject("ALLOCATE-RESULT-SET-ITERATOR", "(DEFUN (ALLOCATE-RESULT-SET-ITERATOR (ITERATOR OF CONS)) ((CONNECTION /SDBC/CONNECTION) (RELATION LOGIC-OBJECT) (SQLSTATEMENT STRING)))", ((cpp_function_code)(&allocateResultSetIterator)), NULL);
    defineFunctionObject("RESULT-SET-ITERATOR-NEXT?", "(DEFUN (RESULT-SET-ITERATOR-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&resultSetIteratorNextP)), NULL);
    defineFunctionObject("GET-TABLE-RELATION", "(DEFUN (GET-TABLE-RELATION NAMED-DESCRIPTION) ((TABLE-NAME STRING) (MODULE MODULE)))", ((cpp_function_code)(&getTableRelation)), NULL);
    defineFunctionObject("GET-TABLE-COLUMN-INDEX", "(DEFUN (GET-TABLE-COLUMN-INDEX INTEGER) ((TABLE-RELATION NAMED-DESCRIPTION) (COLUMN-NAME STRING) (MODULE MODULE)))", ((cpp_function_code)(&getTableColumnIndex)), NULL);
    defineFunctionObject("GET-TABLE-COLUMN-MODULE-NAME", "(DEFUN (GET-TABLE-COLUMN-MODULE-NAME STRING-WRAPPER) ((TABLERELATION NAMED-DESCRIPTION) (COLUMNINDEX INTEGER)))", ((cpp_function_code)(&getTableColumnModuleName)), NULL);
    defineFunctionObject("GET-TABLE-COLUMN-MODULE-REFERENCE", "(DEFUN (GET-TABLE-COLUMN-MODULE-REFERENCE STRING-WRAPPER) ((TABLERELATION NAMED-DESCRIPTION) (COLUMNINDEX INTEGER)))", ((cpp_function_code)(&getTableColumnModuleReference)), NULL);
    defineFunctionObject("GET-TABLE-COLUMN-NAME", "(DEFUN (GET-TABLE-COLUMN-NAME STRING-WRAPPER) ((TABLERELATION NAMED-DESCRIPTION) (COLUMNINDEX INTEGER)))", ((cpp_function_code)(&getTableColumnName)), NULL);
    defineFunctionObject("GET-TABLE-COLUMN-NAMES", "(DEFUN (GET-TABLE-COLUMN-NAMES (CONS OF STRING-WRAPPER)) ((TABLERELATION NAMED-DESCRIPTION)))", ((cpp_function_code)(&getTableColumnNames)), NULL);
    defineFunctionObject("CREATE-RELATION-TABLE-INFO", "(DEFUN (CREATE-RELATION-TABLE-INFO RELATION-TABLE-INFO) ((RELATION NAMED-DESCRIPTION)))", ((cpp_function_code)(&createRelationTableInfo)), NULL);
    defineFunctionObject("GET-MODULE-USING-REFERENCE", "(DEFUN (GET-MODULE-USING-REFERENCE MODULE) ((COLUMN RELATION-COLUMN-INFO) (VALUES CONS)))", ((cpp_function_code)(&getModuleUsingReference)), NULL);
    defineFunctionObject("GET-RELATION-TABLE-INFO", "(DEFUN (GET-RELATION-TABLE-INFO RELATION-TABLE-INFO) ((TABLERELATION NAMED-DESCRIPTION)))", ((cpp_function_code)(&getRelationTableInfo)), NULL);
    defineFunctionObject("COLLECTION-VALUED-CONSTRAINT?", "(DEFUN (COLLECTION-VALUED-CONSTRAINT? BOOLEAN) ((ARGUMENT OBJECT)))", ((cpp_function_code)(&collectionValuedConstraintP)), NULL);
    defineFunctionObject("COLLECTION-VALUED-CONSTRAINT-ELEMENTS", "(DEFUN (COLLECTION-VALUED-CONSTRAINT-ELEMENTS CONS) ((ARGUMENT OBJECT)))", ((cpp_function_code)(&collectionValuedConstraintElements)), NULL);
    defineFunctionObject("PRINT-SQL-VALUE", "(DEFUN PRINT-SQL-VALUE ((STREAM OUTPUT-STREAM) (VALUE OBJECT) (COLUMN RELATION-COLUMN-INFO)))", ((cpp_function_code)(&printSqlValue)), NULL);
    defineFunctionObject("PRINT-COLUMN-CONSTRAINT", "(DEFUN PRINT-COLUMN-CONSTRAINT ((SQL OUTPUT-STREAM) (COLUMN RELATION-COLUMN-INFO) (VALUE STRING) (CASESENSITIVE? BOOLEAN)))", ((cpp_function_code)(&printColumnConstraint)), NULL);
    defineFunctionObject("PRINT-ARGUMENT-CONSTRAINT", "(DEFUN PRINT-ARGUMENT-CONSTRAINT ((SQL OUTPUT-STREAM) (ARGUMENT OBJECT) (COLUMN RELATION-COLUMN-INFO)))", ((cpp_function_code)(&printArgumentConstraint)), NULL);
    defineFunctionObject("PRINT-SQL-COLUMN-LIST", "(DEFUN PRINT-SQL-COLUMN-LIST ((STREAM OUTPUT-STREAM) (TABLE-INFO RELATION-TABLE-INFO)))", ((cpp_function_code)(&printSqlColumnList)), NULL);
    defineFunctionObject("PRINT-SQL-CONSTRAINT-LIST", "(DEFUN PRINT-SQL-CONSTRAINT-LIST ((STREAM OUTPUT-STREAM) (TABLE-INFO RELATION-TABLE-INFO) (ARGUMENTS VECTOR)))", ((cpp_function_code)(&printSqlConstraintList)), NULL);
    defineFunctionObject("CREATE-SQL-FROM-PROPOSITION", "(DEFUN (CREATE-SQL-FROM-PROPOSITION STRING) ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&createSqlFromProposition)), NULL);
    defineFunctionObject("ALLOCATE-DBTABLE-SPECIALIST-ITERATOR", "(DEFUN (ALLOCATE-DBTABLE-SPECIALIST-ITERATOR (ITERATOR OF CONS)) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&allocateDbtableSpecialistIterator)), NULL);
    defineFunctionObject("RETRIEVE-NEXT-DB-QUERY-SOLUTION", "(DEFUN (RETRIEVE-NEXT-DB-QUERY-SOLUTION KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&retrieveNextDbQuerySolution)), NULL);
    defineFunctionObject("DBTABLE-SPECIALIST", "(DEFUN (DBTABLE-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&dbtableSpecialist)), NULL);
    defineFunctionObject("GET-QUERY-PATTERN-EVALUATORS", "(DEFUN (GET-QUERY-PATTERN-EVALUATORS (CONS OF CONS)) ((RELATIONREF SURROGATE)))", ((cpp_function_code)(&getQueryPatternEvaluators)), NULL);
    defineFunctionObject("NORMALIZE-SQL-JOIN-ARGUMENTS", "(DEFUN (NORMALIZE-SQL-JOIN-ARGUMENTS CONS CONS) ((TABLEINFO RELATION-TABLE-INFO) (ARGUMENTS OBJECT)))", ((cpp_function_code)(&normalizeSqlJoinArguments)), NULL);
    defineFunctionObject("HELP-MEMOIZE-SQL-JOIN", "(DEFUN (HELP-MEMOIZE-SQL-JOIN (ITERATOR OF CONS)) ((PROPOSITION PROPOSITION) (DATABASE LOGIC-OBJECT) (ARGUMENTS OBJECT)))", ((cpp_function_code)(&helpMemoizeSqlJoin)), NULL);
    defineFunctionObject("SQL-JOIN", "(DEFUN (SQL-JOIN (ITERATOR OF CONS)) ((PROPOSITION PROPOSITION) (DATABASE LOGIC-OBJECT) (ARGUMENTS OBJECT)))", ((cpp_function_code)(&sqlJoin)), NULL);
    defineFunctionObject("COLLECT-VARIABLE-BINDING", "(DEFUN COLLECT-VARIABLE-BINDING ((NAME STRING) (TYPE OBJECT) (BINDING OBJECT) (BINDINGS (KEY-VALUE-LIST OF STRING-WRAPPER OBJECT))))", ((cpp_function_code)(&collectVariableBinding)), NULL);
    defineFunctionObject("CREATE-SQL-QUERY-FROM-PROPOSITION", "(DEFUN (CREATE-SQL-QUERY-FROM-PROPOSITION STRING) ((PROPOSITION PROPOSITION) (DATABASE LOGIC-OBJECT) (ARGUMENTS OBJECT)))", ((cpp_function_code)(&createSqlQueryFromProposition)), NULL);
    defineFunctionObject("HELP-MEMOIZE-SQL-QUERY", "(DEFUN (HELP-MEMOIZE-SQL-QUERY (ITERATOR OF CONS)) ((PROPOSITION PROPOSITION) (DATABASE LOGIC-OBJECT) (ARGUMENTS OBJECT)))", ((cpp_function_code)(&helpMemoizeSqlQuery)), NULL);
    defineFunctionObject("SQL-QUERY-INSTANTIATE-CONSTRAINTS", "(DEFUN (SQL-QUERY-INSTANTIATE-CONSTRAINTS STRING) ((SQL STRING) (BINDINGS (KEY-VALUE-LIST OF STRING-WRAPPER OBJECT))))", ((cpp_function_code)(&sqlQueryInstantiateConstraints)), NULL);
    defineFunctionObject("SQL-QUERY", "(DEFUN (SQL-QUERY (ITERATOR OF CONS)) ((PROPOSITION PROPOSITION) (DATABASE LOGIC-OBJECT) (ARGUMENTS OBJECT)))", ((cpp_function_code)(&sqlQuery)), NULL);
    defineFunctionObject("ALLOCATE-QUERY-SPECIALIST-ITERATOR", "(DEFUN (ALLOCATE-QUERY-SPECIALIST-ITERATOR (ITERATOR OF CONS)) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&allocateQuerySpecialistIterator)), NULL);
    defineFunctionObject("QUERY-SPECIALIST", "(DEFUN (QUERY-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&querySpecialist)), NULL);
    defineFunctionObject("COLLECT-QUERY-DATABASE-SPECIALIST-BINDINGS", "(DEFUN (COLLECT-QUERY-DATABASE-SPECIALIST-BINDINGS (KEY-VALUE-LIST OF STRING-WRAPPER OBJECT)) ((FRAME CONTROL-FRAME) (FIRSTARGINDEX INTEGER)))", ((cpp_function_code)(&collectQueryDatabaseSpecialistBindings)), NULL);
    defineFunctionObject("BIND-NEXT-DATABASE-TUPLE-TO-ARGUMENTS", "(DEFUN (BIND-NEXT-DATABASE-TUPLE-TO-ARGUMENTS KEYWORD) ((FRAME CONTROL-FRAME) (FIRSTARGINDEX INTEGER)))", ((cpp_function_code)(&bindNextDatabaseTupleToArguments)), NULL);
    defineFunctionObject("QUERY-SQL-DATABASE-SPECIALIST", "(DEFUN (QUERY-SQL-DATABASE-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&querySqlDatabaseSpecialist)), NULL);
    defineFunctionObject("QUERY-DATABASE-SPECIALIST", "(DEFUN (QUERY-DATABASE-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&queryDatabaseSpecialist)), NULL);
    defineFunctionObject("DB-UPDATE-DEMON", "(DEFUN DB-UPDATE-DEMON ((DBPROPOSITION PROPOSITION)))", ((cpp_function_code)(&dbUpdateDemon)), NULL);
    defineFunctionObject("CHECK-FOR-EXTERNAL-DB-UPDATES", "(DEFUN CHECK-FOR-EXTERNAL-DB-UPDATES ((PROPOSITION PROPOSITION) (DATABASE LOGIC-OBJECT)))", ((cpp_function_code)(&checkForExternalDbUpdates)), NULL);
    defineFunctionObject("GET-QUERY-PATTERN-MEMOIZATION-KEY", "(DEFUN (GET-QUERY-PATTERN-MEMOIZATION-KEY OBJECT) ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&getQueryPatternMemoizationKey)), NULL);
    defineFunctionObject("COERCE-VALUES", "(DEFUN (COERCE-VALUES (CONS OF OBJECT)) ((VALUES (CONS OF STRING-WRAPPER)) (TABLE RELATION-TABLE-INFO)))", ((cpp_function_code)(&coerceValues)), NULL);
    defineFunctionObject("COERCE-STRING-TO-POWERLOOM-OBJECT", "(DEFUN (COERCE-STRING-TO-POWERLOOM-OBJECT OBJECT) ((VALUE STRING) (TYPE NAMED-DESCRIPTION) (MODULE MODULE) (LOCAL? BOOLEAN)))", ((cpp_function_code)(&coerceStringToPowerloomObject)), NULL);
    defineFunctionObject("NUMBER-STRING-TO-INTEGER", "(DEFUN (NUMBER-STRING-TO-INTEGER INTEGER) ((X STRING)))", ((cpp_function_code)(((int  (*) (const char*))(&numberStringToInteger)))), NULL);
  }
}

void startupRdbms() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/RDBMS", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupRdbms1();
      helpStartupRdbms2();
      helpStartupRdbms3();
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("CONNECTION-WRAPPER", "(DEFCLASS CONNECTION-WRAPPER (LOGIC-THING) :PUBLIC-SLOTS ((WRAPPER-VALUE :TYPE /SDBC/CONNECTION)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newConnectionWrapper));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessConnectionWrapperSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("RELATION-TABLE-INFO", "(DEFCLASS RELATION-TABLE-INFO (STANDARD-OBJECT) :DOCUMENTATION \"Data structure that associates a PowerLoom relation representing\na database table or query with various information about its columns, value coercion, etc.\" :PUBLIC-SLOTS ((RELATION :TYPE NAMED-DESCRIPTION) (DATABASE :TYPE OBJECT) (DBMS-NAME :TYPE KEYWORD) (TABLE-NAME :TYPE STRING) (TABLE-ALIAS :TYPE STRING :INITIALLY \"_T\") (COLUMN-LIST :TYPE (CONS OF RELATION-COLUMN-INFO)) (COLUMN-VECTOR :TYPE (VECTOR OF RELATION-COLUMN-INFO)) (COLUMN-INDEX :TYPE (KEY-VALUE-MAP OF OBJECT RELATION-COLUMN-INFO)) (ADJUNCT :TYPE OBJECT)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newRelationTableInfo));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessRelationTableInfoSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("RELATION-COLUMN-INFO", "(DEFCLASS RELATION-COLUMN-INFO (STANDARD-OBJECT) :PUBLIC-SLOTS ((TABLE-INFO :TYPE RELATION-TABLE-INFO) (COLUMN-NAME :TYPE STRING) (COLUMN-VARIABLE :TYPE SYMBOL) (COLUMN-INDEX :TYPE INTEGER) (COLUMN-TYPE :TYPE NAMED-DESCRIPTION) (COLUMN-DB-TYPE :TYPE STRING) (MODULE-NAME :TYPE STRING) (MODULE-REFERENCE :TYPE STRING) (MODULE :TYPE MODULE) (MODULE-LOCAL? :TYPE BOOLEAN) (MODULE-REFERENCE-COLUMN :TYPE RELATION-COLUMN-INFO) (COERCION-FUNCTION :TYPE FUNCTION-CODE)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newRelationColumnInfo));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessRelationColumnInfoSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupRdbms4();
      defineFunctionObject("COERCE-POWERLOOM-OBJECT-TO-STRING", "(DEFUN (COERCE-POWERLOOM-OBJECT-TO-STRING STRING) ((OBJECT OBJECT) (TYPE NAMED-DESCRIPTION)))", ((cpp_function_code)(&coercePowerloomObjectToString)), NULL);
      defineFunctionObject("FIND-OR-CREATE-INSTANCE", "(DEFUN (FIND-OR-CREATE-INSTANCE OBJECT) ((NAME STRING) (TYPE NAMED-DESCRIPTION) (MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Find an existing instance with `name' in `module' or create one with `type'\nif it does not yet exist.  If `local?' do not look into any inherited modules.\" :PUBLIC? TRUE)", ((cpp_function_code)(&findOrCreateInstance)), NULL);
      defineFunctionObject("CREATE-SQL-ASSERTION-FROM-PROPOSITION", "(DEFUN (CREATE-SQL-ASSERTION-FROM-PROPOSITION STRING) ((PROPOSITION PROPOSITION) (MODE KEYWORD)))", ((cpp_function_code)(&createSqlAssertionFromProposition)), NULL);
      defineFunctionObject("DB-RELATION-GOES-TRUE", "(DEFUN DB-RELATION-GOES-TRUE ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&dbRelationGoesTrue)), NULL);
      defineFunctionObject("DB-RELATION-GOES-UNKNOWN", "(DEFUN DB-RELATION-GOES-UNKNOWN ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&dbRelationGoesUnknown)), NULL);
      defineFunctionObject("DB-RELATION-GOES-FALSE", "(DEFUN DB-RELATION-GOES-FALSE ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&dbRelationGoesFalse)), NULL);
      defineFunctionObject("DB-RELATION-UPDATE-DEMON", "(DEFUN DB-RELATION-UPDATE-DEMON ((PROPOSITION PROPOSITION) (UPDATE-MODE KEYWORD)))", ((cpp_function_code)(&dbRelationUpdateDemon)), NULL);
      defineFunctionObject("STARTUP-RDBMS", "(DEFUN STARTUP-RDBMS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupRdbms)), NULL);
      { MethodSlot* function = lookupFunction(SYM_RDBMS_RDBMS_STARTUP_RDBMS);

        setDynamicSlotValue(function->dynamicSlots, SYM_RDBMS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupRdbms"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("RDBMS")))));
      safeImportSymbol(SYM_RDBMS_RDBMS_DEFUNTABLE, getStellaModule("PL-KERNEL", true));
      safeImportSymbol(SYM_RDBMS_RDBMS_DEFTABLE, getStellaModule("PL-KERNEL", true));
      safeImportSymbol(SYM_RDBMS_RDBMS_DEFDB, getStellaModule("PL-KERNEL", true));
      safeImportSymbol(SYM_RDBMS_RDBMS_DEFQUERY, getStellaModule("PL-KERNEL", true));
      defineExplanationPhrase(KWD_RDBMS_DB_LOOKUP, KWD_RDBMS_TECHNICAL, "by database lookup", 0);
      defineExplanationPhrase(KWD_RDBMS_DB_LOOKUP, KWD_RDBMS_LAY, "because it is stored in database", 0);
    }
  }
}

Symbol* SYM_RDBMS_RDBMS_DEFUNTABLE = NULL;

Symbol* SYM_RDBMS_RDBMS_RELATION_TABLE = NULL;

Symbol* SYM_RDBMS_RDBMS_RELATION_DATABASE = NULL;

Symbol* SYM_RDBMS_PL_KERNEL_KB_RELATION_SPECIALIST = NULL;

Symbol* SYM_RDBMS_RDBMS_DBTABLE_SPECIALIST = NULL;

Keyword* KWD_RDBMS_AXIOMS = NULL;

Symbol* SYM_RDBMS_RDBMS_DEFTABLE = NULL;

Surrogate* SGT_RDBMS_STELLA_CONS = NULL;

Keyword* KWD_RDBMS_ERROR = NULL;

Keyword* KWD_RDBMS_NAME = NULL;

Keyword* KWD_RDBMS_VARIABLE = NULL;

Keyword* KWD_RDBMS_TYPE = NULL;

Keyword* KWD_RDBMS_MODULE_NAME = NULL;

Keyword* KWD_RDBMS_MODULE_REFERENCE = NULL;

Symbol* SYM_RDBMS_RDBMS_RELATION_COLUMN_NAME = NULL;

Symbol* SYM_RDBMS_RDBMS_RELATION_COLUMN_MODULE_NAME = NULL;

Symbol* SYM_RDBMS_RDBMS_RELATION_COLUMN_MODULE_REFERENCE = NULL;

Symbol* SYM_RDBMS_RDBMS_DEFDB = NULL;

Symbol* SYM_RDBMS_RDBMS_DATABASE = NULL;

Keyword* KWD_RDBMS_CONNECTION_STRING = NULL;

Surrogate* SGT_RDBMS_STELLA_STRING = NULL;

Keyword* KWD_RDBMS_JDBC_CONNECTION_STRING = NULL;

Keyword* KWD_RDBMS_ODBC_CONNECTION_STRING = NULL;

Keyword* KWD_RDBMS_DSN = NULL;

Keyword* KWD_RDBMS_DB = NULL;

Keyword* KWD_RDBMS_HOST = NULL;

Keyword* KWD_RDBMS_PORT = NULL;

Surrogate* SGT_RDBMS_STELLA_INTEGER = NULL;

Keyword* KWD_RDBMS_USER = NULL;

Keyword* KWD_RDBMS_PASSWORD = NULL;

Keyword* KWD_RDBMS_MODULE = NULL;

Surrogate* SGT_RDBMS_STELLA_MODULE = NULL;

Keyword* KWD_RDBMS_CONFIGURATION = NULL;

Surrogate* SGT_RDBMS_STELLA_CONFIGURATION_TABLE = NULL;

Keyword* KWD_RDBMS_DB_NAME = NULL;

Symbol* SYM_RDBMS_RDBMS_DEFQUERY = NULL;

Symbol* SYM_RDBMS_RDBMS_QUERY_SPECIALIST = NULL;

Surrogate* SGT_RDBMS_RDBMS_CONNECTION_WRAPPER = NULL;

Symbol* SYM_RDBMS_STELLA_WRAPPER_VALUE = NULL;

Surrogate* SGT_RDBMS_LOGIC_LOGIC_OBJECT = NULL;

Surrogate* SGT_RDBMS_RDBMS_PROTOCOL = NULL;

Surrogate* SGT_RDBMS_RDBMS_SERVER_TYPE = NULL;

Surrogate* SGT_RDBMS_RDBMS_HOST = NULL;

Surrogate* SGT_RDBMS_RDBMS_PORT = NULL;

Surrogate* SGT_RDBMS_RDBMS_USER = NULL;

Surrogate* SGT_RDBMS_RDBMS_PASSWORD = NULL;

Surrogate* SGT_RDBMS_RDBMS_DB_NAME = NULL;

Surrogate* SGT_RDBMS_RDBMS_ODBC_CONNECTION_STRING = NULL;

Surrogate* SGT_RDBMS_RDBMS_CONNECTION_STRING = NULL;

Surrogate* SGT_RDBMS_RDBMS_DSN = NULL;

Keyword* KWD_RDBMS_PROTOCOL = NULL;

Keyword* KWD_RDBMS_SERVER_TYPE = NULL;

Keyword* KWD_RDBMS_EXTENSIONAL_ASSERTION = NULL;

Surrogate* SGT_RDBMS_RDBMS_DB_CONNECTION = NULL;

Surrogate* SGT_RDBMS_RDBMS_RELATION_DATABASE = NULL;

Symbol* SYM_RDBMS_LOGIC_pX = NULL;

Surrogate* SGT_RDBMS_RDBMS_RELATION_TABLE_INFO = NULL;

Symbol* SYM_RDBMS_STELLA_RELATION = NULL;

Symbol* SYM_RDBMS_RDBMS_DBMS_NAME = NULL;

Symbol* SYM_RDBMS_STELLA_TABLE_NAME = NULL;

Symbol* SYM_RDBMS_RDBMS_TABLE_ALIAS = NULL;

Symbol* SYM_RDBMS_RDBMS_COLUMN_LIST = NULL;

Symbol* SYM_RDBMS_RDBMS_COLUMN_VECTOR = NULL;

Symbol* SYM_RDBMS_RDBMS_COLUMN_INDEX = NULL;

Symbol* SYM_RDBMS_RDBMS_ADJUNCT = NULL;

Surrogate* SGT_RDBMS_RDBMS_RELATION_COLUMN_INFO = NULL;

Symbol* SYM_RDBMS_RDBMS_TABLE_INFO = NULL;

Symbol* SYM_RDBMS_RDBMS_COLUMN_NAME = NULL;

Symbol* SYM_RDBMS_RDBMS_COLUMN_VARIABLE = NULL;

Symbol* SYM_RDBMS_RDBMS_COLUMN_TYPE = NULL;

Symbol* SYM_RDBMS_RDBMS_COLUMN_DB_TYPE = NULL;

Symbol* SYM_RDBMS_STELLA_MODULE_NAME = NULL;

Symbol* SYM_RDBMS_RDBMS_MODULE_REFERENCE = NULL;

Symbol* SYM_RDBMS_STELLA_MODULE = NULL;

Symbol* SYM_RDBMS_RDBMS_MODULE_LOCALp = NULL;

Symbol* SYM_RDBMS_RDBMS_MODULE_REFERENCE_COLUMN = NULL;

Symbol* SYM_RDBMS_RDBMS_COERCION_FUNCTION = NULL;

Keyword* KWD_RDBMS_UNKNOWN = NULL;

Surrogate* SGT_RDBMS_RDBMS_RELATION_TABLE = NULL;

Surrogate* SGT_RDBMS_RDBMS_F_GET_RELATION_TABLE_INFO_MEMO_TABLE_000 = NULL;

Keyword* KWD_RDBMS_STRING_CONSTANT = NULL;

Surrogate* SGT_RDBMS_STELLA_NUMBER = NULL;

Surrogate* SGT_RDBMS_STELLA_BOOLEAN = NULL;

Keyword* KWD_RDBMS_MYSQL = NULL;

Surrogate* SGT_RDBMS_STELLA_STRING_WRAPPER = NULL;

Symbol* SYM_RDBMS_STELLA_ITERATOR = NULL;

Surrogate* SGT_RDBMS_RDBMS_DATABASE = NULL;

Surrogate* SGT_RDBMS_RDBMS_F_ALLOCATE_DBTABLE_SPECIALIST_ITERATOR_MEMO_TABLE_000 = NULL;

Keyword* KWD_RDBMS_FAILURE = NULL;

Keyword* KWD_RDBMS_DB_LOOKUP = NULL;

Keyword* KWD_RDBMS_CONTINUING_SUCCESS = NULL;

Keyword* KWD_RDBMS_FINAL_SUCCESS = NULL;

Keyword* KWD_RDBMS_TECHNICAL = NULL;

Keyword* KWD_RDBMS_LAY = NULL;

Symbol* SYM_RDBMS_RDBMS_pREL = NULL;

Symbol* SYM_RDBMS_RDBMS_pEV = NULL;

Symbol* SYM_RDBMS_RDBMS_pDB = NULL;

Symbol* SYM_RDBMS_RDBMS_pARGS = NULL;

Symbol* SYM_RDBMS_STELLA_AND = NULL;

Symbol* SYM_RDBMS_RDBMS_QUERY_PATTERN = NULL;

Symbol* SYM_RDBMS_STELLA_EXISTS = NULL;

Symbol* SYM_RDBMS_RDBMS_pDB_TYPE = NULL;

Symbol* SYM_RDBMS_RDBMS_SUPPORTS_DB_TYPE = NULL;

Symbol* SYM_RDBMS_RDBMS_INSTANCE_OF = NULL;

Keyword* KWD_RDBMS_DONT_OPTIMIZEp = NULL;

Keyword* KWD_RDBMS_HOW_MANY = NULL;

Keyword* KWD_RDBMS_ALL = NULL;

Keyword* KWD_RDBMS_INFERENCE_LEVEL = NULL;

Keyword* KWD_RDBMS_ASSERTION = NULL;

Symbol* SYM_RDBMS_RDBMS_F_GET_QUERY_PATTERN_EVALUATORS_QUERY_000 = NULL;

Surrogate* SGT_RDBMS_RDBMS_F_GET_QUERY_PATTERN_EVALUATORS_MEMO_TABLE_000 = NULL;

Symbol* SYM_RDBMS_RDBMS_F_GET_QUERY_PATTERN_EVALUATORS_QUERY_001 = NULL;

Surrogate* SGT_RDBMS_RDBMS_F_SQL_JOIN_MEMO_TABLE_000 = NULL;

Keyword* KWD_RDBMS_VALUE = NULL;

Keyword* KWD_RDBMS_WHITE_SPACE = NULL;

Keyword* KWD_RDBMS_SET = NULL;

Keyword* KWD_RDBMS_NONE = NULL;

Surrogate* SGT_RDBMS_RDBMS_F_SQL_QUERY_MEMO_TABLE_000 = NULL;

Keyword* KWD_RDBMS_TERMINAL_FAILURE = NULL;

Surrogate* SGT_RDBMS_RDBMS_SQL_DATABASE = NULL;

Keyword* KWD_RDBMS_EXTERNAL_DB_UPDATE = NULL;

Surrogate* SGT_RDBMS_LOGIC_NAMED_DESCRIPTION = NULL;

Surrogate* SGT_RDBMS_STELLA_TRUE = NULL;

Surrogate* SGT_RDBMS_STELLA_FALSE = NULL;

Surrogate* SGT_RDBMS_STELLA_THING = NULL;

Keyword* KWD_RDBMS_CLIP = NULL;

Keyword* KWD_RDBMS_ASSERT = NULL;

Keyword* KWD_RDBMS_RETRACT = NULL;

Keyword* KWD_RDBMS_ASSERT_TRUE = NULL;

Keyword* KWD_RDBMS_PRESUME_TRUE = NULL;

Keyword* KWD_RDBMS_RETRACT_TRUE = NULL;

Keyword* KWD_RDBMS_RETRACT_FALSE = NULL;

Keyword* KWD_RDBMS_ASSERT_FALSE = NULL;

Keyword* KWD_RDBMS_PRESUME_FALSE = NULL;

Keyword* KWD_RDBMS_CONCEIVE = NULL;

Symbol* SYM_RDBMS_RDBMS_STARTUP_RDBMS = NULL;

Symbol* SYM_RDBMS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace rdbms
