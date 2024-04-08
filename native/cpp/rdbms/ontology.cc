//  -*- Mode: C++ -*-

// ontology.cc

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

void startupOntology() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/RDBMS", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SYM_ONTOLOGY_RDBMS_DATABASE = ((Symbol*)(internRigidSymbolWrtModule("DATABASE", NULL, 0)));
      KWD_ONTOLOGY_DOCUMENTATION = ((Keyword*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 2)));
      SYM_ONTOLOGY_RDBMS_SQL_DATABASE = ((Symbol*)(internRigidSymbolWrtModule("SQL-DATABASE", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_PROTOCOL = ((Symbol*)(internRigidSymbolWrtModule("PROTOCOL", NULL, 0)));
      KWD_ONTOLOGY__g = ((Keyword*)(internRigidSymbolWrtModule("->", NULL, 2)));
      KWD_ONTOLOGY_GOES_TRUE_DEMON = ((Keyword*)(internRigidSymbolWrtModule("GOES-TRUE-DEMON", NULL, 2)));
      SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON = ((Symbol*)(internRigidSymbolWrtModule("DB-UPDATE-DEMON", NULL, 0)));
      KWD_ONTOLOGY_GOES_UNKNOWN_DEMON = ((Keyword*)(internRigidSymbolWrtModule("GOES-UNKNOWN-DEMON", NULL, 2)));
      SYM_ONTOLOGY_RDBMS_SERVER_TYPE = ((Symbol*)(internRigidSymbolWrtModule("SERVER-TYPE", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_DSN = ((Symbol*)(internRigidSymbolWrtModule("DSN", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_CONNECTION_STRING = ((Symbol*)(internRigidSymbolWrtModule("CONNECTION-STRING", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_ODBC_CONNECTION_STRING = ((Symbol*)(internRigidSymbolWrtModule("ODBC-CONNECTION-STRING", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_JDBC_CONNECTION_STRING = ((Symbol*)(internRigidSymbolWrtModule("JDBC-CONNECTION-STRING", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_HOST = ((Symbol*)(internRigidSymbolWrtModule("HOST", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_PORT = ((Symbol*)(internRigidSymbolWrtModule("PORT", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_USER = ((Symbol*)(internRigidSymbolWrtModule("USER", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_PASSWORD = ((Symbol*)(internRigidSymbolWrtModule("PASSWORD", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_DB_NAME = ((Symbol*)(internRigidSymbolWrtModule("DB-NAME", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_DB_CONNECTION = ((Symbol*)(internRigidSymbolWrtModule("DB-CONNECTION", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_pCONN = ((Symbol*)(internRigidSymbolWrtModule("?CONN", NULL, 0)));
      KWD_ONTOLOGY_AXIOMS = ((Keyword*)(internRigidSymbolWrtModule("AXIOMS", NULL, 2)));
      SYM_ONTOLOGY_RDBMS_RELATION_TABLE = ((Symbol*)(internRigidSymbolWrtModule("RELATION-TABLE", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_RELATION_DATABASE = ((Symbol*)(internRigidSymbolWrtModule("RELATION-DATABASE", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_RELATION_COLUMN_NAME = ((Symbol*)(internRigidSymbolWrtModule("RELATION-COLUMN-NAME", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_RELATION_COLUMN_MODULE_NAME = ((Symbol*)(internRigidSymbolWrtModule("RELATION-COLUMN-MODULE-NAME", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_RELATION_COLUMN_MODULE_REFERENCE = ((Symbol*)(internRigidSymbolWrtModule("RELATION-COLUMN-MODULE-REFERENCE", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_QUERY_EVALUATOR = ((Symbol*)(internRigidSymbolWrtModule("QUERY-EVALUATOR", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_SUPPORTS_DB_TYPE = ((Symbol*)(internRigidSymbolWrtModule("SUPPORTS-DB-TYPE", NULL, 0)));
      KWD_ONTOLOGY_CLOSED = ((Keyword*)(internRigidSymbolWrtModule("CLOSED", NULL, 2)));
      SYM_ONTOLOGY_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", getStellaModule("/STELLA", true), 0)));
      SYM_ONTOLOGY_RDBMS_QUERY_PATTERN = ((Symbol*)(internRigidSymbolWrtModule("QUERY-PATTERN", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_QUERY_SQL_DATABASE = ((Symbol*)(internRigidSymbolWrtModule("QUERY-SQL-DATABASE", NULL, 0)));
      KWD_ONTOLOGY_VARIABLE_ARITY = ((Keyword*)(internRigidSymbolWrtModule("VARIABLE-ARITY", NULL, 2)));
      KWD_ONTOLOGY_RELATION_SPECIALIST = ((Keyword*)(internRigidSymbolWrtModule("RELATION-SPECIALIST", NULL, 2)));
      SYM_ONTOLOGY_RDBMS_QUERY_SQL_DATABASE_SPECIALIST = ((Symbol*)(internRigidSymbolWrtModule("QUERY-SQL-DATABASE-SPECIALIST", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_QUERY_DATABASE = ((Symbol*)(internRigidSymbolWrtModule("QUERY-DATABASE", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_QUERY_DATABASE_SPECIALIST = ((Symbol*)(internRigidSymbolWrtModule("QUERY-DATABASE-SPECIALIST", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_FETCH_EDB_DATABASE = ((Symbol*)(internRigidSymbolWrtModule("FETCH-EDB-DATABASE", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_TASK_ID = ((Symbol*)(internRigidSymbolWrtModule("TASK-ID", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_SUBTASK_ID = ((Symbol*)(internRigidSymbolWrtModule("SUBTASK-ID", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_FETCH_QUERY = ((Symbol*)(internRigidSymbolWrtModule("FETCH-QUERY", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_FETCH_QUERY_TYPE_1 = ((Symbol*)(internRigidSymbolWrtModule("FETCH-QUERY-TYPE-1", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_FETCH_QUERY_TYPE_2 = ((Symbol*)(internRigidSymbolWrtModule("FETCH-QUERY-TYPE-2", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_QUERY_TABLE_NAME = ((Symbol*)(internRigidSymbolWrtModule("QUERY-TABLE-NAME", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_QUERY_PARAMETER_NAME = ((Symbol*)(internRigidSymbolWrtModule("QUERY-PARAMETER-NAME", NULL, 0)));
      SYM_ONTOLOGY_RDBMS_STARTUP_ONTOLOGY = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-ONTOLOGY", NULL, 0)));
      SYM_ONTOLOGY_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("STARTUP-ONTOLOGY", "(DEFUN STARTUP-ONTOLOGY () :PUBLIC? TRUE)", ((cpp_function_code)(&startupOntology)), NULL);
      { MethodSlot* function = lookupFunction(SYM_ONTOLOGY_RDBMS_STARTUP_ONTOLOGY);

        setDynamicSlotValue(function->dynamicSlots, SYM_ONTOLOGY_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupOntology"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("RDBMS")))));
      { 
        BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("PL-KERNEL-KB", true));
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
        defconcept(consList(3, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DATABASE))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Information defining a database.  The connection relation is transient."))))));
        defconcept(consList(4, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_SQL_DATABASE))), ((Cons*)(copyConsTree(getQuotedTree("((DATABASE) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Information defining a database that supports SQL queries via JDBC or ODBC."))))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_PROTOCOL))), ((Cons*)(copyConsTree(getQuotedTree("(((?DB DATABASE)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Cons*)(copyConsTree(getQuotedTree("((?CS STRING) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The protocol that should be used to connect to the database\nin case there are multiple options for the current implementation language.\nFor example, in Lisp and C++ we could use either \"ODBC\" or the \"MySQL\" API\n(which is not yet supported), while in Java we only support `JDBC'.")))), KWD_ONTOLOGY_GOES_TRUE_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON))), KWD_ONTOLOGY_GOES_UNKNOWN_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_SERVER_TYPE))), ((Cons*)(copyConsTree(getQuotedTree("(((?DB DATABASE)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Cons*)(copyConsTree(getQuotedTree("((?CS STRING) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The type of DBMS server used such as \"MySQL\" or \"Oracle\".\nThis information is needed if connection strings are not given directly but\nneed to be assembled from individual pieces.")))), KWD_ONTOLOGY_GOES_TRUE_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON))), KWD_ONTOLOGY_GOES_UNKNOWN_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DSN))), ((Cons*)(copyConsTree(getQuotedTree("(((?DB DATABASE)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Cons*)(copyConsTree(getQuotedTree("((?DSN STRING) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The data source name used for a connection.  Currently, data\nsources are only supported for ODBC and not (yet) JDBC.  By specifying a data\nsource, all connection information can be kept in some external file such as\n`.odbc.ini'.")))), KWD_ONTOLOGY_GOES_TRUE_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON))), KWD_ONTOLOGY_GOES_UNKNOWN_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_CONNECTION_STRING))), ((Cons*)(copyConsTree(getQuotedTree("(((?DB DATABASE)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Cons*)(copyConsTree(getQuotedTree("((?CS STRING) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The connection string used for an ODBC or JDBC connection.  Deprecated")))), KWD_ONTOLOGY_GOES_TRUE_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON))), KWD_ONTOLOGY_GOES_UNKNOWN_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_ODBC_CONNECTION_STRING))), ((Cons*)(copyConsTree(getQuotedTree("(((?DB DATABASE)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Cons*)(copyConsTree(getQuotedTree("((?CS STRING) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The connection string used for a ODBC connection.")))), KWD_ONTOLOGY_GOES_TRUE_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON))), KWD_ONTOLOGY_GOES_UNKNOWN_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_JDBC_CONNECTION_STRING))), ((Cons*)(copyConsTree(getQuotedTree("(((?DB DATABASE)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Cons*)(copyConsTree(getQuotedTree("((?CS STRING) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The connection string used for a JDBC connection.")))), KWD_ONTOLOGY_GOES_TRUE_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON))), KWD_ONTOLOGY_GOES_UNKNOWN_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_HOST))), ((Cons*)(copyConsTree(getQuotedTree("(((?DB DATABASE)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Cons*)(copyConsTree(getQuotedTree("((?HOST STRING) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The host of a database server.")))), KWD_ONTOLOGY_GOES_TRUE_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON))), KWD_ONTOLOGY_GOES_UNKNOWN_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_PORT))), ((Cons*)(copyConsTree(getQuotedTree("(((?DB DATABASE)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Cons*)(copyConsTree(getQuotedTree("((?PORT INTEGER) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The port of a database server.")))), KWD_ONTOLOGY_GOES_TRUE_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON))), KWD_ONTOLOGY_GOES_UNKNOWN_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_USER))), ((Cons*)(copyConsTree(getQuotedTree("(((?DB DATABASE)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Cons*)(copyConsTree(getQuotedTree("((?USER STRING) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The user for a database server.")))), KWD_ONTOLOGY_GOES_TRUE_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON))), KWD_ONTOLOGY_GOES_UNKNOWN_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_PASSWORD))), ((Cons*)(copyConsTree(getQuotedTree("(((?DB DATABASE)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Cons*)(copyConsTree(getQuotedTree("((?PASSWORD STRING) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The password associated with a user for a database server.")))), KWD_ONTOLOGY_GOES_TRUE_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON))), KWD_ONTOLOGY_GOES_UNKNOWN_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_NAME))), ((Cons*)(copyConsTree(getQuotedTree("(((?DB DATABASE)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Cons*)(copyConsTree(getQuotedTree("((?DBNAME STRING) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The name of a database on a database server.")))), KWD_ONTOLOGY_GOES_TRUE_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON))), KWD_ONTOLOGY_GOES_UNKNOWN_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON)))));
        deffunction(consList(8, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_CONNECTION))), ((Cons*)(copyConsTree(getQuotedTree("(((?DB DATABASE)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_pCONN))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("A connection id produced by using the rest of the information\nassociated with the database.  This relation is transient, i.e., it can be\nreset dynamically, whereas the other relations should not change.")))), KWD_ONTOLOGY_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((HIDDEN-RELATION DB-CONNECTION) \"/RDBMS\")", "/RDBMS"))))));
        defrelation(consList(4, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_RELATION_TABLE))), ((Cons*)(copyConsTree(getQuotedTree("(((?RELATION /PL-KERNEL-KB/RELATION) (?TABLE STRING)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Associates a PowerLoom ?relation with a database ?table."))))));
        defrelation(consList(4, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_RELATION_DATABASE))), ((Cons*)(copyConsTree(getQuotedTree("(((?RELATION /PL-KERNEL-KB/RELATION) (?DATABASE DATABASE)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Associates a PowerLoom ?relation with an RDBMS ?database."))))));
        deffunction(consList(6, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_RELATION_COLUMN_NAME))), ((Cons*)(copyConsTree(getQuotedTree("(((?DBRELATION /PL-KERNEL-KB/RELATION) (?COL INTEGER)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Cons*)(copyConsTree(getQuotedTree("((?COLNAME STRING) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The name of the database table column at position ?col (1-based)\nassociated with the database relation ?dbrelation."))))));
        deffunction(consList(6, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_RELATION_COLUMN_MODULE_NAME))), ((Cons*)(copyConsTree(getQuotedTree("(((?DBRELATION /PL-KERNEL-KB/RELATION) (?COL INTEGER)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Cons*)(copyConsTree(getQuotedTree("((?MODNAME STRING) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The name of the module to import the logic objects defined at table column at position ?col (1-based)\nassociated with the database relation ?dbrelation."))))));
        deffunction(consList(6, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_RELATION_COLUMN_MODULE_REFERENCE))), ((Cons*)(copyConsTree(getQuotedTree("(((?DBRELATION /PL-KERNEL-KB/RELATION) (?COL INTEGER)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Cons*)(copyConsTree(getQuotedTree("((?MODREF STRING) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The name of the column from which to get the name of the module\nto import the logic objects defined at table column at position ?col (1-based)\nassociated with the database relation ?dbrelation."))))));
        asserT(((Cons*)(copyConsTree(getQuotedTree("((COMPUTED-PROCEDURE DBTABLE-SPECIALIST) \"/RDBMS\")", "/RDBMS")))));
        defconcept(consList(4, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_QUERY_EVALUATOR))), ((Cons*)(copyConsTree(getQuotedTree("((COMPUTED-PROCEDURE) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("A specialist procedure that can evaluate generic external queries."))))));
        defrelation(consList(6, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_SUPPORTS_DB_TYPE))), ((Cons*)(copyConsTree(getQuotedTree("(((?EVALUATOR QUERY-EVALUATOR) (?DBTYPE CONCEPT)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Specifies that ?evaluator can handle external databases of\ntype ?dbType.")))), KWD_ONTOLOGY_CLOSED, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_STELLA_TRUE)))));
        defrelation(consList(6, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_QUERY_PATTERN))), ((Cons*)(copyConsTree(getQuotedTree("(((?RELATION /PL-KERNEL-KB/RELATION) (?EVALUATOR QUERY-EVALUATOR) (?DATABASE DATABASE) (?ARGUMENTS STRING)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Specifies a query evaluation pattern that can generate bindings\nfor ?relation from an external ?database.  ?evaluator is a query evaluator that\ntakes a query proposition, the ?database instance and an ?arguments specification\nand returns an iterator that generates CONS tuples whose elements will be matched\nto ?relation's arguments by position.  The format of ?arguments is specific to\neach evaluator (see for example the function `RDBMS/SQL-join').\n\nWhether a particular pattern is applicable depends on whether all the required\ninput arguments are bound and whether ?evaluator can handle the particular\n?database type.  If there are multiple applicable patterns they will be run/\nevaluated in sequence (similar to having multiple rules for ?relation).")))), KWD_ONTOLOGY_CLOSED, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_STELLA_TRUE)))));
        asserT(((Cons*)(copyConsTree(getQuotedTree("((COMPUTED-PROCEDURE SQL-QUERY) \"/RDBMS\")", "/RDBMS")))));
        asserT(((Cons*)(copyConsTree(getQuotedTree("((AND (DOCUMENTATION SQL-QUERY \"Generic query evaluator that can handle arbitrary\nSQL queries on an RDBMS/SQL-Database.\") (QUERY-EVALUATOR SQL-QUERY) (SUPPORTS-DB-TYPE SQL-QUERY SQL-DATABASE)) \"/RDBMS\")", "/RDBMS")))));
        asserT(((Cons*)(copyConsTree(getQuotedTree("((COMPUTED-PROCEDURE SQL-JOIN) \"/RDBMS\")", "/RDBMS")))));
        asserT(((Cons*)(copyConsTree(getQuotedTree("((AND (DOCUMENTATION SQL-JOIN \"Generic query evaluator that can evaluate\nsimple joins on an RDBMS/SQL-Database.\") (QUERY-EVALUATOR SQL-JOIN) (SUPPORTS-DB-TYPE SQL-JOIN SQL-DATABASE)) \"/RDBMS\")", "/RDBMS")))));
        asserT(((Cons*)(copyConsTree(getQuotedTree("((COMPUTED-PROCEDURE QUERY-SPECIALIST) \"/RDBMS\")", "/RDBMS")))));
        asserT(((Cons*)(copyConsTree(getQuotedTree("((DOCUMENTATION QUERY-SPECIALIST \"Top-level specialist that can dispatch generic query\nevaluation specialists such as RDBMS/SQL-join.\") \"/RDBMS\")", "/RDBMS")))));
        asserT(((Cons*)(copyConsTree(getQuotedTree("((COMPUTED-PROCEDURE QUERY-SQL-DATABASE-SPECIALIST) \"/RDBMS\")", "/RDBMS")))));
        defrelation(consList(8, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_QUERY_SQL_DATABASE))), ((Cons*)(copyConsTree(getQuotedTree("(((?DATABASE SQL-DATABASE) (?QUERY STRING) ?OUTPUT) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Run the SQL ?query against ?database and bind\none or more ?output arguments to the columns in the resulting tuples.\nThis can be turned into a T/F query either by binding ?output's or by\nwrapping an EXISTS around this.  Result coercion is performed based on\nthe types of the ?output variables.")))), KWD_ONTOLOGY_VARIABLE_ARITY, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_STELLA_TRUE))), KWD_ONTOLOGY_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_QUERY_SQL_DATABASE_SPECIALIST)))));
        asserT(((Cons*)(copyConsTree(getQuotedTree("((COMPUTED-PROCEDURE QUERY-DATABASE-SPECIALIST) \"/RDBMS\")", "/RDBMS")))));
        defrelation(consList(8, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_QUERY_DATABASE))), ((Cons*)(copyConsTree(getQuotedTree("(((?DATABASE DATABASE) (?QUERY STRING) ?OUTPUT) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Run the relational ?query against ?database and bind\none or more ?output arguments to the columns in the resulting tuples.\nIf there are more result columns than ?output variables, they will be\nignored.  If there are fewer, that's ok as long as the remaining ?output's\nhad initial bindings.  Initial bindings can be used to instantiate\na parametric ?query template with them (e.g., for SQL queries).  Initial\nbindings have to match result columns except for collection-valued bindings.\nThis can be turned into a T/F query either by binding ?output's or by\nwrapping an EXISTS around this.  Result coercion is performed based on\nthe types of the ?output variables.  For known database types such\nas `RDBMS/SQL-Database' this dispatches to the appropriate specialist.\nOtherwise, this relation serves as a top-level interface that can be\nlinked to other database query interfaces via appropriate rules.")))), KWD_ONTOLOGY_VARIABLE_ARITY, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_STELLA_TRUE))), KWD_ONTOLOGY_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_QUERY_DATABASE_SPECIALIST)))));
        defconcept(consList(4, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_FETCH_EDB_DATABASE))), ((Cons*)(copyConsTree(getQuotedTree("((DATABASE) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("A database that supports EELD EDB database access via Fetch HTTP wrappers."))))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_TASK_ID))), ((Cons*)(copyConsTree(getQuotedTree("(((?DB FETCH-EDB-DATABASE)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Cons*)(copyConsTree(getQuotedTree("((?ID STRING) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The task-id used for each access to ?db.")))), KWD_ONTOLOGY_GOES_TRUE_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON))), KWD_ONTOLOGY_GOES_UNKNOWN_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_SUBTASK_ID))), ((Cons*)(copyConsTree(getQuotedTree("(((?DB FETCH-EDB-DATABASE)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY__g, ((Cons*)(copyConsTree(getQuotedTree("((?ID STRING) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The subtask-id used for each access to ?db.")))), KWD_ONTOLOGY_GOES_TRUE_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON))), KWD_ONTOLOGY_GOES_UNKNOWN_DEMON, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON)))));
        asserT(((Cons*)(copyConsTree(getQuotedTree("((COMPUTED-PROCEDURE FETCH-EDB-QUERY) \"/RDBMS\")", "/RDBMS")))));
        asserT(((Cons*)(copyConsTree(getQuotedTree("((AND (DOCUMENTATION FETCH-EDB-QUERY \"Generic query evaluator that can handle EELD EDB\nqueries via the Fetch HTTP/XML interface.\") (QUERY-EVALUATOR FETCH-EDB-QUERY) (SUPPORTS-DB-TYPE FETCH-EDB-QUERY FETCH-EDB-DATABASE)) \"/RDBMS\")", "/RDBMS")))));
        defconcept(consList(4, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_FETCH_QUERY))), ((Cons*)(copyConsTree(getQuotedTree("((?C) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_CLOSED, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_STELLA_TRUE)))));
        defconcept(consList(4, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_FETCH_QUERY_TYPE_1))), ((Cons*)(copyConsTree(getQuotedTree("((?C FETCH-QUERY) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_CLOSED, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_STELLA_TRUE)))));
        defconcept(consList(4, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_FETCH_QUERY_TYPE_2))), ((Cons*)(copyConsTree(getQuotedTree("((?C FETCH-QUERY) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_CLOSED, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_STELLA_TRUE)))));
        defrelation(consList(6, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_QUERY_TABLE_NAME))), ((Cons*)(copyConsTree(getQuotedTree("(((?Q FETCH-QUERY) (?N STRING)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Database table referenced by this query.  The current set\nof queries each reference only one DB table, but this is a relation\nto allow for future expansion.")))), KWD_ONTOLOGY_CLOSED, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_STELLA_TRUE)))));
        defrelation(consList(6, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_RDBMS_QUERY_PARAMETER_NAME))), ((Cons*)(copyConsTree(getQuotedTree("(((?Q FETCH-QUERY) (?N STRING)) \"/RDBMS\")", "/RDBMS")))), KWD_ONTOLOGY_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Parameter name that needs to be set by this query.  The current set\nof queries each take only a single parameter, but this is a relation\nto allow for future expansion.  TO DO:  Figure out if this should be\na three-place relation that also has a type (concept) entry to identify\nwhat sort of value the parameter takes on.")))), KWD_ONTOLOGY_CLOSED, ((Symbol*)(copyConsTree(SYM_ONTOLOGY_STELLA_TRUE)))));
        asserT(((Cons*)(copyConsTree(getQuotedTree("((DISJOINT FETCH-QUERY-TYPE-1 FETCH-QUERY-TYPE-2) \"/RDBMS\")", "/RDBMS")))));
      }
    }
  }
}

Symbol* SYM_ONTOLOGY_RDBMS_DATABASE = NULL;

Keyword* KWD_ONTOLOGY_DOCUMENTATION = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_SQL_DATABASE = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_PROTOCOL = NULL;

Keyword* KWD_ONTOLOGY__g = NULL;

Keyword* KWD_ONTOLOGY_GOES_TRUE_DEMON = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON = NULL;

Keyword* KWD_ONTOLOGY_GOES_UNKNOWN_DEMON = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_SERVER_TYPE = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_DSN = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_CONNECTION_STRING = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_ODBC_CONNECTION_STRING = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_JDBC_CONNECTION_STRING = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_HOST = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_PORT = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_USER = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_PASSWORD = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_DB_NAME = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_DB_CONNECTION = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_pCONN = NULL;

Keyword* KWD_ONTOLOGY_AXIOMS = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_RELATION_TABLE = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_RELATION_DATABASE = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_RELATION_COLUMN_NAME = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_RELATION_COLUMN_MODULE_NAME = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_RELATION_COLUMN_MODULE_REFERENCE = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_QUERY_EVALUATOR = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_SUPPORTS_DB_TYPE = NULL;

Keyword* KWD_ONTOLOGY_CLOSED = NULL;

Symbol* SYM_ONTOLOGY_STELLA_TRUE = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_QUERY_PATTERN = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_QUERY_SQL_DATABASE = NULL;

Keyword* KWD_ONTOLOGY_VARIABLE_ARITY = NULL;

Keyword* KWD_ONTOLOGY_RELATION_SPECIALIST = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_QUERY_SQL_DATABASE_SPECIALIST = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_QUERY_DATABASE = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_QUERY_DATABASE_SPECIALIST = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_FETCH_EDB_DATABASE = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_TASK_ID = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_SUBTASK_ID = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_FETCH_QUERY = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_FETCH_QUERY_TYPE_1 = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_FETCH_QUERY_TYPE_2 = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_QUERY_TABLE_NAME = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_QUERY_PARAMETER_NAME = NULL;

Symbol* SYM_ONTOLOGY_RDBMS_STARTUP_ONTOLOGY = NULL;

Symbol* SYM_ONTOLOGY_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace rdbms
