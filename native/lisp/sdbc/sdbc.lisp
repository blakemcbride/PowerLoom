;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; sdbc.lisp

#|
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
|#

(CL:IN-PACKAGE "STELLA")

;;; Auxiliary variables:

(CL:DEFVAR KWD-SDBC-LOG-LEVELS NULL)
(CL:DEFVAR KWD-SDBC-LEVEL NULL)
(CL:DEFVAR KWD-SDBC-NONE NULL)
(CL:DEFVAR KWD-SDBC-MAX-WIDTH NULL)
(CL:DEFVAR SGT-SDBC-SDBC-CONNECTION NULL)
(CL:DEFVAR SYM-SDBC-SDBC-CONNECTION-STRING NULL)
(CL:DEFVAR SYM-SDBC-SDBC-PROTOCOL NULL)
(CL:DEFVAR SYM-SDBC-SDBC-DBMS-NAME NULL)
(CL:DEFVAR SYM-SDBC-SDBC-STATEMENT NULL)
(CL:DEFVAR SYM-SDBC-SDBC-AUTO-COMMIT? NULL)
(CL:DEFVAR SYM-SDBC-SDBC-CREATION-TIME NULL)
(CL:DEFVAR SYM-SDBC-SDBC-LAST-ACCESS-TIME NULL)
(CL:DEFVAR SYM-SDBC-SDBC-RENEWAL-TIME NULL)
(CL:DEFVAR SGT-SDBC-SDBC-PREPARED-STATEMENT NULL)
(CL:DEFVAR SYM-SDBC-SDBC-CONNECTION NULL)
(CL:DEFVAR SYM-SDBC-SDBC-SQL NULL)
(CL:DEFVAR SYM-SDBC-STELLA-PARAMETERS NULL)
(CL:DEFVAR SYM-SDBC-SDBC-RDBMS-ROW NULL)
(CL:DEFVAR SGT-SDBC-SDBC-RESULT-SET-ITERATOR NULL)
(CL:DEFVAR SYM-SDBC-SDBC-TYPES NULL)
(CL:DEFVAR SYM-SDBC-SDBC-CONNECT NULL)
(CL:DEFVAR KWD-SDBC-COMMON-LISP NULL)
(CL:DEFVAR KWD-SDBC-FUNCTION NULL)
(CL:DEFVAR KWD-SDBC-PROTOCOL NULL)
(CL:DEFVAR KWD-SDBC-SERVER-TYPE NULL)
(CL:DEFVAR KWD-SDBC-LOW NULL)
(CL:DEFVAR KWD-SDBC-CONNECTION-STRING NULL)
(CL:DEFVAR KWD-SDBC-HOST NULL)
(CL:DEFVAR KWD-SDBC-PORT NULL)
(CL:DEFVAR KWD-SDBC-DB-NAME NULL)
(CL:DEFVAR KWD-SDBC-DSN NULL)
(CL:DEFVAR KWD-SDBC-USER NULL)
(CL:DEFVAR KWD-SDBC-PASSWORD NULL)
(CL:DEFVAR SYM-SDBC-SDBC-DISCONNECT NULL)
(CL:DEFVAR KWD-SDBC-WHITE-SPACE NULL)
(CL:DEFVAR KWD-SDBC-LETTER NULL)
(CL:DEFVAR SYM-SDBC-STELLA-NULL NULL)
(CL:DEFVAR SGT-SDBC-STELLA-CALENDAR-DATE NULL)
(CL:DEFVAR SGT-SDBC-STELLA-STRING NULL)
(CL:DEFVAR SGT-SDBC-STELLA-INTEGER NULL)
(CL:DEFVAR SGT-SDBC-STELLA-LONG-INTEGER NULL)
(CL:DEFVAR SGT-SDBC-STELLA-DOUBLE-FLOAT NULL)
(CL:DEFVAR KWD-SDBC-TYPES NULL)
(CL:DEFVAR KWD-SDBC-HIGH NULL)
(CL:DEFVAR SYM-SDBC-SDBC-EXECUTE-SQL NULL)
(CL:DEFVAR KWD-SDBC-STRING-CONSTANT NULL)
(CL:DEFVAR KWD-SDBC-IDENTIFIER NULL)
(CL:DEFVAR KWD-SDBC-MYSQL NULL)
(CL:DEFVAR KWD-SDBC-NULL NULL)
(CL:DEFVAR SYM-SDBC-STELLA-DEFAULT NULL)
(CL:DEFVAR KWD-SDBC-DEFAULT NULL)
(CL:DEFVAR SYM-SDBC-SDBC-INSERT-ROW NULL)
(CL:DEFVAR KWD-SDBC-ORACLE NULL)
(CL:DEFVAR SYM-SDBC-SDBC-INSERT-ROWS NULL)
(CL:DEFVAR SYM-SDBC-SDBC-PREPARE-STATEMENT NULL)
(CL:DEFVAR SYM-SDBC-SDBC-BIND-PARAMETER NULL)
(CL:DEFVAR SGT-SDBC-STELLA-WRAPPER NULL)
(CL:DEFVAR SYM-SDBC-SDBC-SET-AUTO-COMMIT NULL)
(CL:DEFVAR SYM-SDBC-SDBC-COMMIT NULL)
(CL:DEFVAR SYM-SDBC-SDBC-ROLLBACK NULL)
(CL:DEFVAR SGT-SDBC-SDBC-TABLE-INFO NULL)
(CL:DEFVAR SYM-SDBC-SDBC-DATABASE NULL)
(CL:DEFVAR SYM-SDBC-SDBC-CATALOG NULL)
(CL:DEFVAR SYM-SDBC-SDBC-SCHEMA NULL)
(CL:DEFVAR SYM-SDBC-STELLA-NAME NULL)
(CL:DEFVAR SYM-SDBC-STELLA-TYPE NULL)
(CL:DEFVAR SYM-SDBC-SDBC-REMARKS NULL)
(CL:DEFVAR SYM-SDBC-SDBC-COLUMNS NULL)
(CL:DEFVAR SGT-SDBC-SDBC-COLUMN-INFO NULL)
(CL:DEFVAR SYM-SDBC-STELLA-TABLE-NAME NULL)
(CL:DEFVAR SYM-SDBC-SDBC-DATA-TYPE NULL)
(CL:DEFVAR SYM-SDBC-SDBC-DATA-TYPE-NAME NULL)
(CL:DEFVAR SYM-SDBC-SDBC-COLUMN-SIZE NULL)
(CL:DEFVAR SYM-SDBC-SDBC-BUFFER-LENGTH NULL)
(CL:DEFVAR SYM-SDBC-SDBC-DECIMAL-DIGITS NULL)
(CL:DEFVAR SYM-SDBC-SDBC-RADIX NULL)
(CL:DEFVAR SYM-SDBC-SDBC-NULLABLE? NULL)
(CL:DEFVAR SYM-SDBC-SDBC-IS-NULLABLE? NULL)
(CL:DEFVAR SYM-SDBC-STELLA-DOCUMENTATION NULL)
(CL:DEFVAR SYM-SDBC-STELLA-DEFAULT-VALUE NULL)
(CL:DEFVAR SYM-SDBC-SDBC-SQL-DATA-TYPE NULL)
(CL:DEFVAR SYM-SDBC-SDBC-SQL-DATETIME-SUB NULL)
(CL:DEFVAR SYM-SDBC-SDBC-CHAR-OCTET-LENGTH NULL)
(CL:DEFVAR SYM-SDBC-SDBC-ORDINAL-POSITION NULL)
(CL:DEFVAR SYM-SDBC-SDBC-GET-TABLES NULL)
(CL:DEFVAR SYM-SDBC-SDBC-GET-COLUMNS NULL)
(CL:DEFVAR SYM-SDBC-SDBC-GET-SERVER-INFO NULL)
(CL:DEFVAR KWD-SDBC-COMMAND NULL)
(CL:DEFVAR KWD-SDBC-DATA-SOURCE NULL)
(CL:DEFVAR KWD-SDBC-SQL NULL)
(CL:DEFVAR KWD-SDBC-OTHERWISE NULL)
(CL:DEFVAR SGT-SDBC-STELLA-CONS NULL)
(CL:DEFVAR KWD-SDBC-DIGIT NULL)
(CL:DEFVAR KWD-SDBC-CONNECTIONSTRING NULL)
(CL:DEFVAR SYM-SDBC-SDBC-STARTUP-SDBC NULL)
(CL:DEFVAR SYM-SDBC-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM
 (CL:SPECIAL *STARTUP-TIME-PHASE* *MODULE* NULL-CHARACTER EOL
  STANDARD-OUTPUT *CHARACTER-TYPE-TABLE* NULL-INTEGER NIL TRUE-WRAPPER
  FALSE-WRAPPER))

;;; (VERBATIM :CPP ...)

#+:EXCL (cl:require :aodbc-v2)
#+(or :openmcl :sbcl) (cl:eval-when (:compile-toplevel :load-toplevel :execute)
   (cl-user::load-clsql)
   (cl:pushnew :CLSQL CL:*FEATURES*))

;;; (DEFCLASS CONNECTION ...)

(CL:DEFCLASS CONNECTION (STANDARD-OBJECT)
  ((NATIVE-CONNECTION :ALLOCATION :INSTANCE :ACCESSOR
    %NATIVE-CONNECTION)
   (CONNECTION-STRING :TYPE CL:SIMPLE-STRING :INITFORM
    STELLA::NULL-STRING :ALLOCATION :INSTANCE :ACCESSOR
    %CONNECTION-STRING)
   (PROTOCOL :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %PROTOCOL)
   (DBMS-NAME :DOCUMENTATION
    "Indicates to what kind of DBMS we are connected." :ALLOCATION
    :INSTANCE :ACCESSOR %DBMS-NAME)
   (STATEMENT :DOCUMENTATION
    "Prepared statement associated with this connection." :ALLOCATION
    :INSTANCE :ACCESSOR %STATEMENT)
   (AUTO-COMMIT? :DOCUMENTATION
    "State of connection's auto-commit feature." :ALLOCATION :INSTANCE
    :ACCESSOR %AUTO-COMMIT?)
   (CREATION-TIME :DOCUMENTATION
    "Time at which connection was created." :ALLOCATION :INSTANCE
    :ACCESSOR %CREATION-TIME)
   (LAST-ACCESS-TIME :DOCUMENTATION
    "Time at which connection was last accessed." :ALLOCATION :INSTANCE
    :ACCESSOR %LAST-ACCESS-TIME)
   (RENEWAL-TIME :DOCUMENTATION
    "Time at or after which connection should be renewed." :ALLOCATION
    :INSTANCE :ACCESSOR %RENEWAL-TIME)))

(CL:DEFUN NEW-CONNECTION ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE CONNECTION)))
   (CL:SETF (%RENEWAL-TIME SELF) NULL)
   (CL:SETF (%LAST-ACCESS-TIME SELF) NULL)
   (CL:SETF (%CREATION-TIME SELF) NULL)
   (CL:SETF (%AUTO-COMMIT? SELF) CL:T) (CL:SETF (%STATEMENT SELF) NULL)
   (CL:SETF (%DBMS-NAME SELF) NULL)
   (CL:SETF (%PROTOCOL SELF) STELLA::NULL-STRING)
   (CL:SETF (%CONNECTION-STRING SELF) STELLA::NULL-STRING)
   (CL:SETF (%NATIVE-CONNECTION SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF CONNECTION))
  SGT-SDBC-SDBC-CONNECTION)

(CL:DEFUN ACCESS-CONNECTION-SLOT-VALUE (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-CONNECTION-STRING)
    (CL:IF SETVALUE?
     (CL:SETF (%CONNECTION-STRING SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%CONNECTION-STRING SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-PROTOCOL)
    (CL:IF SETVALUE? (CL:SETF (%PROTOCOL SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%PROTOCOL SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-DBMS-NAME)
    (CL:IF SETVALUE? (CL:SETF (%DBMS-NAME SELF) VALUE)
     (CL:SETQ VALUE (%DBMS-NAME SELF))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-STATEMENT)
    (CL:IF SETVALUE? (CL:SETF (%STATEMENT SELF) VALUE)
     (CL:SETQ VALUE (%STATEMENT SELF))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-AUTO-COMMIT?)
    (CL:IF SETVALUE?
     (CL:SETF (%AUTO-COMMIT? SELF)
      (COERCE-WRAPPED-BOOLEAN-TO-BOOLEAN VALUE))
     (CL:SETQ VALUE
      (CL:IF (%AUTO-COMMIT? SELF) TRUE-WRAPPER FALSE-WRAPPER))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-CREATION-TIME)
    (CL:IF SETVALUE? (CL:SETF (%CREATION-TIME SELF) VALUE)
     (CL:SETQ VALUE (%CREATION-TIME SELF))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-LAST-ACCESS-TIME)
    (CL:IF SETVALUE? (CL:SETF (%LAST-ACCESS-TIME SELF) VALUE)
     (CL:SETQ VALUE (%LAST-ACCESS-TIME SELF))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-RENEWAL-TIME)
    (CL:IF SETVALUE? (CL:SETF (%RENEWAL-TIME SELF) VALUE)
     (CL:SETQ VALUE (%RENEWAL-TIME SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

(CL:DEFMETHOD PRINT-OBJECT ((SELF CONNECTION) STREAM)
  (%%PRINT-STREAM STREAM "|CON|\"" (%CONNECTION-STRING SELF) "\""))

;;; (DEFCLASS PREPARED-STATEMENT ...)

(CL:DEFCLASS PREPARED-STATEMENT (STANDARD-OBJECT)
  ((CONNECTION :ALLOCATION :INSTANCE :ACCESSOR %CONNECTION)
   (STATEMENT :ALLOCATION :INSTANCE :ACCESSOR %STATEMENT)
   (SQL :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %SQL)
   (PARAMETERS :DOCUMENTATION
    "Stores parameters bound so far to support connection renewal."
    :ALLOCATION :INSTANCE :ACCESSOR %PARAMETERS)))

(CL:DEFUN NEW-PREPARED-STATEMENT ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE PREPARED-STATEMENT)))
   (CL:SETF (%PARAMETERS SELF) (NEW-KEY-VALUE-LIST))
   (CL:SETF (%SQL SELF) STELLA::NULL-STRING)
   (CL:SETF (%STATEMENT SELF) NULL) (CL:SETF (%CONNECTION SELF) NULL)
   SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF PREPARED-STATEMENT))
  SGT-SDBC-SDBC-PREPARED-STATEMENT)

(CL:DEFUN ACCESS-PREPARED-STATEMENT-SLOT-VALUE (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-CONNECTION)
    (CL:IF SETVALUE? (CL:SETF (%CONNECTION SELF) VALUE)
     (CL:SETQ VALUE (%CONNECTION SELF))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-SQL)
    (CL:IF SETVALUE? (CL:SETF (%SQL SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%SQL SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-STELLA-PARAMETERS)
    (CL:IF SETVALUE? (CL:SETF (%PARAMETERS SELF) VALUE)
     (CL:SETQ VALUE (%PARAMETERS SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS NATIVE-PREPARED-STATEMENT ...)

(CL:DEFCLASS NATIVE-PREPARED-STATEMENT (CLSYS-ROOT-OBJECT)
  ())

;;; (DEFCLASS DATABASE-EXCEPTION ...)

(CL:DEFINE-CONDITION DATABASE-EXCEPTION (STELLA-EXCEPTION)
  ())

(CL:DEFUN NEW-DATABASE-EXCEPTION (MESSAGE)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING MESSAGE))
  #+MCL
  (CL:CHECK-TYPE MESSAGE CL:SIMPLE-STRING)
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF
    (CL:MAKE-CONDITION (CL:QUOTE DATABASE-EXCEPTION)
     *CONDITION-MESSAGE-KEYWORD*
     (REPLACE-SUBSTRINGS MESSAGE "~~" "~")))
   SELF))

;;; (DEFCLASS RESULT-SET-ITERATOR ...)

(CL:DEFCLASS RESULT-SET-ITERATOR (ITERATOR)
  ((RESULT-SET :ALLOCATION :INSTANCE :ACCESSOR %RESULT-SET)
   (TYPES :ALLOCATION :INSTANCE :ACCESSOR %TYPES))
  (:DOCUMENTATION "Iterator class for a table returned by a SQL query."))

(CL:DEFUN NEW-RESULT-SET-ITERATOR ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE RESULT-SET-ITERATOR)))
   (CL:SETF (%FIRST-ITERATION? SELF) CL:T) (CL:SETF (%VALUE SELF) NULL)
   (CL:SETF (%TYPES SELF) NULL) (CL:SETF (%RESULT-SET SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF RESULT-SET-ITERATOR))
  SGT-SDBC-SDBC-RESULT-SET-ITERATOR)

(CL:DEFUN ACCESS-RESULT-SET-ITERATOR-SLOT-VALUE (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-TYPES)
    (CL:IF SETVALUE? (CL:SETF (%TYPES SELF) VALUE)
     (CL:SETQ VALUE (%TYPES SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFUN (CONNECT CONNECTION) ...)

(CL:DEFUN %CONNECT (KEYS-AND-VALUES)
  "Create a connection to a database.  Currently-supported parameters
are (values need to be strings):
  :PROTOCOL          - \"ODBC\", \"JDBC\", \"CLSQL\" or \"MYSQL\" (defaults to \"ODBC\")
  :SERVER-TYPE       - Type of database server (for JDBC strings)
  :DSN               - Name of ODBC Datasource
  :DB-NAME           - Name of physical database
  :USER              - Database user id.
  :PASSWORD          - Database password
  :HOST              - Host database server runs on
  :PORT              - Port to use to connect to the server
  :CONNECTION-STRING - Connection string to be used by ODBC or JDBC drivers
                       instead of DSN, USER, PASSWORD, etc.
A DATABASE-EXCEPTION is thrown if the connection is unsuccessful."
  (CALL-CONNECT KEYS-AND-VALUES))

(CL:DEFUN CONNECT-EVALUATOR-WRAPPER (ARGUMENTS)
  (%CONNECT ARGUMENTS))

(CL:DEFMACRO CONNECT (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Create a connection to a database.  Currently-supported parameters
are (values need to be strings):
  :PROTOCOL          - \"ODBC\", \"JDBC\", \"CLSQL\" or \"MYSQL\" (defaults to \"ODBC\")
  :SERVER-TYPE       - Type of database server (for JDBC strings)
  :DSN               - Name of ODBC Datasource
  :DB-NAME           - Name of physical database
  :USER              - Database user id.
  :PASSWORD          - Database password
  :HOST              - Host database server runs on
  :PORT              - Port to use to connect to the server
  :CONNECTION-STRING - Connection string to be used by ODBC or JDBC drivers
                       instead of DSN, USER, PASSWORD, etc.
A DATABASE-EXCEPTION is thrown if the connection is unsuccessful."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/SDBC/CONNECT|)) (CL:MACRO-FUNCTION (CL:QUOTE CONNECT)))

;;; (DEFUN (CALL-CONNECT CONNECTION) ...)

(CL:DEFUN CALL-CONNECT (KEYS-AND-VALUES)
  "Functional interface to `connect'.  See its documentation"
  (CL:LET*
   ((RESULT (NEW-CONNECTION)) (NATIVECONNECTION NULL)
    (OPTIONS
     (VET-OPTIONS KEYS-AND-VALUES
      (GET-QUOTED-TREE
       "((:PROTOCOL :SERVER-TYPE :DSN :DB-NAME :USER :PASSWORD :HOST :PORT :CONNECTION-STRING) \"/SDBC\")"
       "/SDBC"))))
   (CL:LET* ((TEMP-000 (LOOKUP OPTIONS KWD-SDBC-PROTOCOL)))
    (CL:LET*
     ((PROTOCOL
       (STRING-UPCASE
        (CL:IF (CL:NOT (CL:EQ TEMP-000 NULL)) (%WRAPPER-VALUE TEMP-000)
         #+:CLSQL "CLSQL" #-:CLSQL "ODBC")))
      (SERVER-TYPE
       (UNWRAP-STRING (LOOKUP OPTIONS KWD-SDBC-SERVER-TYPE)))
      (CONNECTIONSTRING STELLA::NULL-STRING))
     (CL:DECLARE
      (CL:TYPE CL:SIMPLE-STRING PROTOCOL SERVER-TYPE CONNECTIONSTRING))
     (CL:COND
      ((STRING-EQL? PROTOCOL "CLSQL")
       (CL:SETQ NATIVECONNECTION
        (cl:multiple-value-setq (nativeConnection connectionString)
                    (cl-native-clsql-connect options server-type))))
      ((STRING-EQL? PROTOCOL "ODBC")
       (CL:SETQ CONNECTIONSTRING (MAKE-ODBC-CONNECTION-STRING OPTIONS))
       (CL:SETQ NATIVECONNECTION
        (cl:multiple-value-setq (nativeConnection connectionString)
               (cl-native-odbc-connect connectionString))))
      ((STRING-EQL? PROTOCOL "JDBC")
       (CL:SETQ CONNECTIONSTRING (MAKE-JDBC-CONNECTION-STRING OPTIONS))
       (CL:SETQ NATIVECONNECTION NULL))
      (CL:T
       (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
        (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
         "Database Error: unsupported protocol `" PROTOCOL "'")
        (CL:ERROR
         (NEW-DATABASE-EXCEPTION (THE-STRING-READER STREAM-000))))))
     (CL:WHEN (CL:EQ NATIVECONNECTION NULL)
      (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
       (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001) "Database Error: `"
        PROTOCOL "' not supported in `" "Lisp" "'")
       (CL:ERROR
        (NEW-DATABASE-EXCEPTION (THE-STRING-READER STREAM-001)))))
     (CL:SETF (%NATIVE-CONNECTION RESULT) NATIVECONNECTION)
     (CL:SETF (%CONNECTION-STRING RESULT) CONNECTIONSTRING)
     (CL:SETF (%PROTOCOL RESULT) PROTOCOL)
     (CL:SETF (%CREATION-TIME RESULT) (MAKE-CURRENT-DATE-TIME))
     (CL:SETF (%LAST-ACCESS-TIME RESULT) (%CREATION-TIME RESULT))
     (CL:SETF (%RENEWAL-TIME RESULT)
      (TIME-ADD (%CREATION-TIME RESULT)
       (MAKE-TIME-DURATION 0
        (CL:* (GET-MAX-CONNECTION-LIFETIME RESULT) 1000))))
     (LOGMSG "SDBC" KWD-SDBC-LOW (WRAP-STRING "Connect via ")
      (WRAP-STRING PROTOCOL) (WRAP-STRING ": ")
      (WRAP-STRING CONNECTIONSTRING))
     RESULT))))

;;; (DEFGLOBAL *DB-CONNECTION-RENEWAL-INTERVAL* ...)

(CL:DEFVAR *DB-CONNECTION-RENEWAL-INTERVAL* 60
  "The maximum lifetime of a database connection (in seconds) after which
it gets automatically renewed.  Auto-renewals avoid connection timeout errors which are
otherwise tricky to catch, e.g., we might just see a `bad handle passed' error.")
(CL:DECLAIM (CL:TYPE CL:FIXNUM *DB-CONNECTION-RENEWAL-INTERVAL*))

;;; (DEFUN (*DB-CONNECTION-RENEWAL-INTERVAL*-SETTER INTEGER) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:FIXNUM) CL:FIXNUM)
  *DB-CONNECTION-RENEWAL-INTERVAL*-SETTER))
(CL:DEFUN *DB-CONNECTION-RENEWAL-INTERVAL*-SETTER (VALUE)
  (CL:DECLARE (CL:TYPE CL:FIXNUM VALUE))
  #+MCL
  (CL:CHECK-TYPE VALUE CL:FIXNUM)
  (CL:SETQ *DB-CONNECTION-RENEWAL-INTERVAL* VALUE))

;;; (DEFUN (GET-MAX-CONNECTION-LIFETIME INTEGER) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T) CL:FIXNUM) GET-MAX-CONNECTION-LIFETIME))
(CL:DEFUN GET-MAX-CONNECTION-LIFETIME (CON)
  (CL:SETQ CON CON)
  *DB-CONNECTION-RENEWAL-INTERVAL*)

;;; (DEFUN MAYBE-RENEW-CONNECTION ...)

(CL:DEFUN MAYBE-RENEW-CONNECTION (CON)
  (CL:WHEN (CL:NOT (%AUTO-COMMIT? CON))
   (CL:RETURN-FROM MAYBE-RENEW-CONNECTION))
  (CL:LET*
   ((CURRENTTIME (MAKE-CURRENT-DATE-TIME)) (STATEMENT (%STATEMENT CON))
    (NEWCON NULL))
   (CL:SETF (%LAST-ACCESS-TIME CON) CURRENTTIME)
   (CL:WHEN (GREATER-EQUAL? CURRENTTIME (%RENEWAL-TIME CON))
    (LOGMSG "SDBC" KWD-SDBC-LOW (WRAP-STRING "Renewing ")
     (WRAP-STRING (%PROTOCOL CON)) (WRAP-STRING " connection: ")
     (WRAP-STRING (%CONNECTION-STRING CON)))
    (CL:SETQ NEWCON
     (%CONNECT
      (CONS-LIST KWD-SDBC-PROTOCOL (WRAP-STRING (%PROTOCOL CON))
       KWD-SDBC-CONNECTION-STRING
       (WRAP-STRING (%CONNECTION-STRING CON)))))
    (%DISCONNECT CON)
    (CL:SETF (%NATIVE-CONNECTION CON) (%NATIVE-CONNECTION NEWCON))
    (CL:SETF (%CONNECTION-STRING CON) (%CONNECTION-STRING NEWCON))
    (CL:SETF (%PROTOCOL CON) (%PROTOCOL NEWCON))
    (CL:SETF (%CREATION-TIME CON) (%CREATION-TIME NEWCON))
    (CL:SETF (%LAST-ACCESS-TIME CON) (%LAST-ACCESS-TIME NEWCON))
    (CL:SETF (%RENEWAL-TIME CON) (%RENEWAL-TIME NEWCON))
    (CL:WHEN (CL:NOT (CL:EQ STATEMENT NULL))
     (%PREPARE-STATEMENT CON (%SQL STATEMENT))
     (CL:SETF (%STATEMENT STATEMENT) (%STATEMENT (%STATEMENT CON)))
     (CL:SETF (%STATEMENT CON) STATEMENT)
     (CL:LET*
      ((POS NULL) (ENTRY NULL)
       (ITER-000 (%THE-KV-LIST (%PARAMETERS STATEMENT))))
      (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NULL)) DO
       (CL:SETQ POS (%KEY ITER-000)) (CL:SETQ ENTRY (%VALUE ITER-000))
       (%BIND-PARAMETER STATEMENT (%WRAPPER-VALUE POS) (%%VALUE ENTRY)
        (%%VALUE (%%REST ENTRY)))
       (CL:SETQ ITER-000 (%REST ITER-000))))))))

;;; (DEFUN (JDBC-CONNECTION-STRING? BOOLEAN) ...)

(CL:DEFUN JDBC-CONNECTION-STRING? (STRING)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING STRING))
  #+MCL
  (CL:CHECK-TYPE STRING CL:SIMPLE-STRING)
  (CL:= (STRING-SEARCH STRING "jdbc:" 0) 0))

;;; (DEFUN (MAKE-JDBC-CONNECTION-STRING STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T) CL:SIMPLE-STRING)
  MAKE-JDBC-CONNECTION-STRING))
(CL:DEFUN MAKE-JDBC-CONNECTION-STRING (OPTIONS)
  (CL:WHEN
   (CL:NOT (CL:EQ (LOOKUP OPTIONS KWD-SDBC-CONNECTION-STRING) NULL))
   (CL:RETURN-FROM MAKE-JDBC-CONNECTION-STRING
    (%WRAPPER-VALUE (LOOKUP OPTIONS KWD-SDBC-CONNECTION-STRING))))
  (CL:LET*
   ((CON (NEW-OUTPUT-STRING-STREAM)) (VALUE STELLA::NULL-STRING))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING VALUE))
   (%%PRINT-STREAM (%NATIVE-STREAM CON) "jdbc:")
   (CL:LET*
    ((TEMP-000 (UNWRAP-STRING (LOOKUP OPTIONS KWD-SDBC-SERVER-TYPE))))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TEMP-000))
    (CL:SETQ VALUE
     (STRING-DOWNCASE
      (CL:IF (CL:NOT (CL:EQ TEMP-000 STELLA::NULL-STRING)) TEMP-000
       "mysql"))))
   (%%PRINT-STREAM (%NATIVE-STREAM CON) VALUE ":")
   (CL:COND
    ((STRING-EQL? VALUE "mysql")
     (%%PRINT-STREAM (%NATIVE-STREAM CON) "//")
     (CL:SETQ VALUE (UNWRAP-STRING (LOOKUP OPTIONS KWD-SDBC-HOST)))
     (CL:WHEN (CL:NOT (CL:EQ VALUE STELLA::NULL-STRING))
      (%%PRINT-STREAM (%NATIVE-STREAM CON) VALUE))
     (CL:LET* ((PORT (LOOKUP OPTIONS KWD-SDBC-PORT)))
      (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE PORT)))
       (CL:COND
        ((SUBTYPE-OF-STRING? TEST-VALUE-000)
         (CL:PROGN
          (%%PRINT-STREAM (%NATIVE-STREAM CON) ":"
           (UNWRAP-STRING PORT))))
        ((SUBTYPE-OF-INTEGER? TEST-VALUE-000)
         (CL:PROGN
          (%%PRINT-STREAM (%NATIVE-STREAM CON) ":"
           (UNWRAP-INTEGER PORT))))
        (CL:T))))
     (%%PRINT-STREAM (%NATIVE-STREAM CON) "/")
     (CL:SETQ VALUE (UNWRAP-STRING (LOOKUP OPTIONS KWD-SDBC-DB-NAME)))
     (CL:WHEN (CL:NOT (CL:EQ VALUE STELLA::NULL-STRING))
      (%%PRINT-STREAM (%NATIVE-STREAM CON) VALUE))
     (CL:LET* ((SEPARATOR #\?))
      (CL:LET*
       ((OPTION NULL) (VAL NULL) (ITER-000 (%THE-PLIST OPTIONS)))
       (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
        (CL:SETQ OPTION (%%VALUE ITER-000))
        (CL:SETQ VAL (%%VALUE (%%REST ITER-000)))
        (CL:TAGBODY
         (CL:WHEN (CL:NOT (CL:EQ VAL NULL))
          (CL:COND
           ((CL:OR (CL:EQ OPTION KWD-SDBC-SERVER-TYPE)
             (CL:EQ OPTION KWD-SDBC-DSN) (CL:EQ OPTION KWD-SDBC-HOST)
             (CL:EQ OPTION KWD-SDBC-PORT)
             (CL:EQ OPTION KWD-SDBC-DB-NAME)
             (CL:EQ OPTION KWD-SDBC-PROTOCOL))
            (CL:GO :CONTINUE))
           ((CL:OR (CL:EQ OPTION KWD-SDBC-USER)
             (CL:EQ OPTION KWD-SDBC-PASSWORD))
            (%%PRINT-STREAM (%NATIVE-STREAM CON) SEPARATOR
             (STRING-DOWNCASE (%SYMBOL-NAME OPTION))))
           (CL:T
            (%%PRINT-STREAM (%NATIVE-STREAM CON) SEPARATOR
             (%SYMBOL-NAME OPTION) "=" (UNWRAP-STRING VAL))))
          (%%PRINT-STREAM (%NATIVE-STREAM CON) "=" (UNWRAP-STRING VAL))
          (CL:SETQ SEPARATOR #\&))
         :CONTINUE)
        (CL:SETQ ITER-000 (%%REST (%%REST ITER-000)))))))
    ((STRING-EQL? VALUE "oracle")
     (%%PRINT-STREAM (%NATIVE-STREAM CON) "thin:")
     (CL:SETQ VALUE (UNWRAP-STRING (LOOKUP OPTIONS KWD-SDBC-USER)))
     (CL:WHEN (CL:NOT (CL:EQ VALUE STELLA::NULL-STRING))
      (%%PRINT-STREAM (%NATIVE-STREAM CON) VALUE))
     (CL:LET*
      ((TEMP-001 (UNWRAP-STRING (LOOKUP OPTIONS KWD-SDBC-PASSWORD))))
      (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TEMP-001))
      (CL:SETQ VALUE
       (CL:IF (CL:NOT (CL:EQ TEMP-001 STELLA::NULL-STRING)) TEMP-001
        "")))
     (%%PRINT-STREAM (%NATIVE-STREAM CON) "/" VALUE)
     (CL:LET*
      ((TEMP-002 (UNWRAP-STRING (LOOKUP OPTIONS KWD-SDBC-HOST))))
      (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TEMP-002))
      (CL:SETQ VALUE
       (CL:IF (CL:NOT (CL:EQ TEMP-002 STELLA::NULL-STRING)) TEMP-002
        "localhost")))
     (%%PRINT-STREAM (%NATIVE-STREAM CON) "@//" VALUE)
     (CL:LET* ((TEMP-003 (LOOKUP OPTIONS KWD-SDBC-PORT)))
      (CL:LET*
       ((PORT
         (CL:IF (CL:NOT (CL:EQ TEMP-003 NULL)) TEMP-003
          (WRAP-STRING "1521"))))
       (CL:LET* ((TEST-VALUE-001 (SAFE-PRIMARY-TYPE PORT)))
        (CL:COND
         ((SUBTYPE-OF-STRING? TEST-VALUE-001)
          (CL:PROGN
           (%%PRINT-STREAM (%NATIVE-STREAM CON) ":"
            (UNWRAP-STRING PORT))))
         ((SUBTYPE-OF-INTEGER? TEST-VALUE-001)
          (CL:PROGN
           (%%PRINT-STREAM (%NATIVE-STREAM CON) ":"
            (UNWRAP-INTEGER PORT))))
         (CL:T
          (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
           (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`"
            TEST-VALUE-001 "' is not a valid case option")
           (CL:ERROR
            (NEW-STELLA-EXCEPTION
             (THE-STRING-READER STREAM-000)))))))))
     (CL:SETQ VALUE (UNWRAP-STRING (LOOKUP OPTIONS KWD-SDBC-DB-NAME)))
     (CL:WHEN (CL:NOT (CL:EQ VALUE STELLA::NULL-STRING))
      (%%PRINT-STREAM (%NATIVE-STREAM CON) "/" VALUE)))
    (CL:T
     (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001)
       "Don't know how to generate JDBC connection string for servers of :SERVER-TYPE `"
       (LOOKUP OPTIONS KWD-SDBC-SERVER-TYPE) "'")
      (CL:ERROR
       (NEW-DATABASE-EXCEPTION (THE-STRING-READER STREAM-001))))))
   (THE-STRING-READER CON)))

;;; (DEFUN (ODBC-CONNECTION-STRING? BOOLEAN) ...)

(CL:DEFUN ODBC-CONNECTION-STRING? (STRING)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING STRING))
  #+MCL
  (CL:CHECK-TYPE STRING CL:SIMPLE-STRING)
  (CL:AND (CL:> (CL:THE CL:FIXNUM (CL:LENGTH STRING)) 0)
   (CL:NOT (JDBC-CONNECTION-STRING? STRING))
   (CL:NOT (CL:= (POSITION STRING #\= 1) NULL-INTEGER))))

;;; (DEFUN (MAKE-ODBC-CONNECTION-STRING STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T) CL:SIMPLE-STRING)
  MAKE-ODBC-CONNECTION-STRING))
(CL:DEFUN MAKE-ODBC-CONNECTION-STRING (OPTIONS)
  (CL:WHEN
   (CL:NOT (CL:EQ (LOOKUP OPTIONS KWD-SDBC-CONNECTION-STRING) NULL))
   (CL:RETURN-FROM MAKE-ODBC-CONNECTION-STRING
    (%WRAPPER-VALUE (LOOKUP OPTIONS KWD-SDBC-CONNECTION-STRING))))
  (CL:LET* ((CON (NEW-OUTPUT-STRING-STREAM)))
   (CL:LET*
    ((OPTION NULL) (VALUE NULL) (ITER-000 (%THE-PLIST OPTIONS)))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ OPTION (%%VALUE ITER-000))
     (CL:SETQ VALUE (%%VALUE (%%REST ITER-000)))
     (CL:TAGBODY
      (CL:WHEN (CL:NOT (CL:EQ VALUE NULL))
       (CL:COND
        ((CL:EQ OPTION KWD-SDBC-USER)
         (%%PRINT-STREAM (%NATIVE-STREAM CON) "UID"))
        ((CL:EQ OPTION KWD-SDBC-PASSWORD)
         (%%PRINT-STREAM (%NATIVE-STREAM CON) "PWD"))
        ((CL:EQ OPTION KWD-SDBC-DB-NAME)
         (%%PRINT-STREAM (%NATIVE-STREAM CON) "DATABASE"))
        ((CL:EQ OPTION KWD-SDBC-HOST)
         (%%PRINT-STREAM (%NATIVE-STREAM CON) "SERVER"))
        ((CL:OR (CL:EQ OPTION KWD-SDBC-PROTOCOL)
          (CL:EQ OPTION KWD-SDBC-SERVER-TYPE))
         (CL:GO :CONTINUE))
        (CL:T
         (%%PRINT-STREAM (%NATIVE-STREAM CON) (%SYMBOL-NAME OPTION))))
       (%%PRINT-STREAM (%NATIVE-STREAM CON) "=" (UNWRAP-STRING VALUE)
        ";"))
      :CONTINUE)
     (CL:SETQ ITER-000 (%%REST (%%REST ITER-000)))))
   (THE-STRING-READER CON)))

;;; (DEFUN (CL-NATIVE-ODBC-CONNECT NATIVE-CONNECTION STRING) ...)

(CL:DEFUN CL-NATIVE-ODBC-CONNECT (CONNECTIONSTRING)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING CONNECTIONSTRING))
  #+MCL
  (CL:CHECK-TYPE CONNECTIONSTRING CL:SIMPLE-STRING)
  (CL:LET* ((ERRORMSG STELLA::NULL-STRING) (NATIVECONNECTION NULL))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING ERRORMSG)) #+:allegro
       (cl:handler-case
          (cl:progn
            (cl:require :aodbc-v2)
            (cl:setq nativeConnection
               (dbi:CONNECT :connect-string (lispify connectionString))))
        (dbi:ODBC-ERROR (c)
          (cl:setq errorMsg (cl:format cl:nil "Database Error: ~A" c)))
        (cl:ERROR (c)
          (cl:setq errorMsg (cl:format cl:nil "Unhandled DB connect error: ~A" c))))
       #-:allegro
       (cl:setq errorMsg
          (cl:format cl:nil "ODBC not available in ~A." (cl:lisp-implementation-type)))
   (CL:WHEN (CL:NOT (CL:EQ ERRORMSG STELLA::NULL-STRING))
    (CL:ERROR (NEW-DATABASE-EXCEPTION ERRORMSG)))
   (CL:VALUES NATIVECONNECTION CONNECTIONSTRING)))

;;; (DEFUN (CL-NATIVE-CLSQL-CONNECT NATIVE-CONNECTION STRING) ...)

(CL:DEFUN CL-NATIVE-CLSQL-CONNECT (OPTIONS SERVER-TYPE)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SERVER-TYPE))
  #+MCL
  (CL:CHECK-TYPE SERVER-TYPE CL:SIMPLE-STRING)
  (CL:LET*
   ((CONNECTION-STRING
     (UNWRAP-STRING (LOOKUP OPTIONS KWD-SDBC-CONNECTION-STRING)))
    (USER (UNWRAP-STRING (LOOKUP OPTIONS KWD-SDBC-USER)))
    (PASSWORD (UNWRAP-STRING (LOOKUP OPTIONS KWD-SDBC-PASSWORD)))
    (DB-NAME (UNWRAP-STRING (LOOKUP OPTIONS KWD-SDBC-DB-NAME)))
    (HOST (UNWRAP-STRING (LOOKUP OPTIONS KWD-SDBC-HOST)))
    (ERROR-MESSAGE STELLA::NULL-STRING) (NATIVE-CONNECTION NULL))
   (CL:DECLARE
    (CL:TYPE CL:SIMPLE-STRING CONNECTION-STRING USER PASSWORD DB-NAME
     HOST ERROR-MESSAGE))
   #+:CLSQL
       (cl:handler-case
	  (cl:let ((database-type (cl:intern (cl:string-upcase server-type) :KEYWORD))
		   (connection-list cl:nil)
                   (db (cl:and (defined? connection-string) 
                               (clsql:find-database connection-string :errorp cl:nil)))
		   ;; Hack, because calling CLSQL:CONNECT can trigger loading and compilation
		   ;; of files that rely on CL symbols being visible so that DEFPACKAGE
		   ;; and IN-PACKAGE at the top of the files are properly interpreted.
		   (cl:*package* (cl:find-package "COMMON-LISP")))
            (cl:if db			; Assume a reconnect.
                (cl:setq native-connection (clsql:reconnect :database db :error cl:nil))
                (cl:progn
		  (cl:case database-type
		    ((:MYSQL :POSTGRESQL :POSTGRESQL-SOCKET)
		       (cl:setq connection-list (CL:LIST host db-name user password)))
		    ((:ODBC :AODBC :ORACLE)
		       (cl:setq connection-list (CL:LIST db-name user password)))
		    ((:SQLITE)
		       (cl:setq connection-list (CL:LIST db-name)))
		    (otherwise
		       (cl:setq error-message
				(concatenate "Unrecognized server-type `" server-type "'"))))
		  (cl:when connection-list
		     (cl:setq native-connection (clsql:connect connection-list 
							    :database-type database-type
							    :if-exists :new))
		     (cl:setq connection-string (clsql:database-name native-connection))))))
	  (clsql:SQL-CONNECTION-ERROR (c)
	     (cl:setq error-message (cl:format cl:nil "Database Connection Spec Error: ~A" c)))
	  (clsql:SQL-ERROR (c)
	     (cl:setq error-message (cl:format cl:nil "Database Error: ~A" c)))
	  (cl:ERROR (c)
	     (cl:setq error-message (cl:format cl:nil "Unhandled DB connect error: ~A" c))))
       #-:CLSQL
       (cl:setq error-message
          (cl:format cl:nil "CLSQL not available in ~A." (cl:lisp-implementation-type)))
   (CL:WHEN (CL:NOT (CL:EQ ERROR-MESSAGE STELLA::NULL-STRING))
    (CL:ERROR (NEW-DATABASE-EXCEPTION ERROR-MESSAGE)))
   (CL:VALUES NATIVE-CONNECTION CONNECTION-STRING)))

;;; (DEFUN DISCONNECT ...)

(CL:DEFUN %DISCONNECT (CONNECTION)
  "Disconnect `connection' from a database.  A DATABASE-EXCEPTION is thrown if
the disconnect is unsuccessful."
  (CL:LET* ((NATIVECONNECTION (%NATIVE-CONNECTION CONNECTION)))
   (CL:WHEN (CL:NOT (CL:EQ NATIVECONNECTION NULL))
    (cl-native-disconnect nativeConnection)
    (LOGMSG "SDBC" KWD-SDBC-LOW (WRAP-STRING "Disconnecting ")
     (WRAP-STRING (%PROTOCOL CONNECTION)) (WRAP-STRING " connection: ")
     (WRAP-STRING (%CONNECTION-STRING CONNECTION)))
    (CL:SETF (%NATIVE-CONNECTION CONNECTION) NULL))))

(CL:DEFMACRO DISCONNECT (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Disconnect `connection' from a database.  A DATABASE-EXCEPTION is thrown if
the disconnect is unsuccessful."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/SDBC/DISCONNECT|)) (CL:MACRO-FUNCTION (CL:QUOTE DISCONNECT)))

;;; (DEFUN CL-NATIVE-DISCONNECT ...)

(CL:DEFUN CL-NATIVE-DISCONNECT (NATIVE-CONNECTION)
  #+:EXCL (cl-native-odbc-disconnect native-connection)
    #+:CLSQL (cl-native-clsql-disconnect native-connection))

;;; (DEFUN CL-NATIVE-ODBC-DISCONNECT ...)

(CL:DEFUN CL-NATIVE-ODBC-DISCONNECT (NATIVECONNECTION)
  (CL:LET* ((ERRORMSG STELLA::NULL-STRING))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING ERRORMSG)) #+:allegro
       (cl:handler-case
          (cl:progn
            (cl:require :aodbc-v2)
            (dbi:disconnect nativeConnection))
        (dbi:ODBC-ERROR (c)
          (cl:setq errorMsg
             (cl:format cl:nil "Database Error: ~A" c)))
        ;; NOTE: An ODBC error isn't thrown if we try to disconnect twice:
        (cl:SIMPLE-ERROR (c)
          (cl:setq errorMsg (cl:format cl:nil "Database Error: ~A" c)))
        (cl:ERROR (c)
          (cl:setq errorMsg (cl:format cl:nil "Unhandled DB disconnect error: ~A" c))))
       #-:allegro
       (cl:setq errorMsg
          (cl:format cl:nil "ODBC not available in ~A." (cl:lisp-implementation-type)))
   (CL:WHEN (CL:NOT (CL:EQ ERRORMSG STELLA::NULL-STRING))
    (CL:ERROR (NEW-DATABASE-EXCEPTION ERRORMSG)))))

;;; (DEFUN CL-NATIVE-CLSQL-DISCONNECT ...)

(CL:DEFUN CL-NATIVE-CLSQL-DISCONNECT (NATIVE-CONNECTION)
  (CL:LET* ((ERROR-MSG STELLA::NULL-STRING))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING ERROR-MSG)) #+:CLSQL
       (cl:handler-case
            (cl:when (cl:member native-connection (clsql:connected-databases))
               (clsql:disconnect :database native-connection :error cl:nil))
        (clsql:SQL-ERROR (c)
          (cl:setq error-msg (cl:format cl:nil "Database Error: ~A" c)))
        (cl:ERROR (c)
          (cl:setq error-msg (cl:format cl:nil "Unhandled DB disconnect error: ~A" c))))
       #-:CLSQL
       (cl:setq error-msg
          (cl:format cl:nil "CLSQL not available in ~A." (cl:lisp-implementation-type)))
   (CL:WHEN (CL:NOT (CL:EQ ERROR-MSG STELLA::NULL-STRING))
    (CL:ERROR (NEW-DATABASE-EXCEPTION ERROR-MSG)))))

;;; (DEFUN (SQL-QUERY? BOOLEAN) ...)

(CL:DEFUN SQL-QUERY? (SQL-EXPRESSION)
  "Return `true' if `sql-expression' is a SQL command string which returns
values."
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SQL-EXPRESSION))
  #+MCL
  (CL:CHECK-TYPE SQL-EXPRESSION CL:SIMPLE-STRING)
  (CL:LET* ((START 0) (END 0) (OPERATOR ""))
   (CL:DECLARE (CL:TYPE CL:FIXNUM START END)
    (CL:TYPE CL:SIMPLE-STRING OPERATOR))
   (CL:LOOP WHILE
    (CL:EQ
     (CL:AREF *CHARACTER-TYPE-TABLE*
      (CL:THE CL:FIXNUM
       (CL:CHAR-CODE
        (CL:LET ((SELF SQL-EXPRESSION) (POSITION START))
         (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
          (CL:TYPE CL:FIXNUM POSITION))
         (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
          (CL:THE CL:FIXNUM POSITION))))))
     KWD-SDBC-WHITE-SPACE)
    DO (CL:SETQ START (CL:1+ START)))
   (CL:SETQ END START)
   (CL:LOOP WHILE
    (CL:EQ
     (CL:AREF *CHARACTER-TYPE-TABLE*
      (CL:THE CL:FIXNUM
       (CL:CHAR-CODE
        (CL:LET ((SELF SQL-EXPRESSION) (POSITION END))
         (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
          (CL:TYPE CL:FIXNUM POSITION))
         (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
          (CL:THE CL:FIXNUM POSITION))))))
     KWD-SDBC-LETTER)
    DO (CL:SETQ END (CL:1+ END)))
   (CL:SETQ OPERATOR (SUBSEQUENCE SQL-EXPRESSION START END))
   (CL:OR (STRING-EQUAL? OPERATOR "SELECT")
    (STRING-EQUAL? OPERATOR "SHOW") (STRING-EQUAL? OPERATOR "DESCRIBE")
    (STRING-EQUAL? OPERATOR "EXPLAIN")
    (STRING-EQUAL? OPERATOR "ANALYZE"))))

;;; (DEFUN (STELLIFY-WITH-NIL-TO-NULL OBJECT) ...)

(CL:DEFUN STELLIFY-WITH-NIL-TO-NULL (SELF)
  "Convert a Lisp object into a STELLA object."
  (CL:LET* ((RESULT SELF)) (CL:typecase self
        (CL:NULL (cl:setq result STELLA::NIL))
        (CL:CONS (cl:setq result 
                     (stella::cons 
                        (cl:if (CL:NULL (CL:car self))
                            NULL
                            (stellify-with-nil-to-null (CL:car self)))
                        (stellify-with-nil-to-null (CL:cdr self)))))
        (CL:KEYWORD (cl:setq result (intern-keyword (CL:symbol-name self))))
        (CL:SYMBOL
         (CL:if (cl:eq self CL:t)
           (cl:setq result TRUE-WRAPPER)
           (cl:setq result (intern-symbol (CL:symbol-name self)))))
        ((CL:or CL:NUMBER CL:STRING) (cl:setq result (wrap-literal self)))
        (STELLA::OBJECT (cl:setq result self))
        (CL:t (CL:error "Can't stellify: ~S" self))) RESULT))

;;; (DEFUN (CL-TRANSLATE-SQL-PARAMETER-TYPE-SPECIFIER OBJECT) ...)

(CL:DEFUN CL-TRANSLATE-SQL-PARAMETER-TYPE-SPECIFIER (STELLATYPE)
  (CL:LET* ((RESULT NULL))
   (CL:COND
    ((CL:OR (CL:EQ STELLATYPE NULL)
      (CL:EQ STELLATYPE SYM-SDBC-STELLA-NULL))
     (cl:setq result :varchar))
    (CL:T
     (CL:LET* ((TEST-VALUE-000 STELLATYPE))
      (CL:COND
       ((CL:EQ TEST-VALUE-000 SGT-SDBC-STELLA-CALENDAR-DATE)
        (cl:setq result :varchar))
       ((CL:EQ TEST-VALUE-000 SGT-SDBC-STELLA-STRING)
        (cl:setq result :varchar))
       ((CL:EQ TEST-VALUE-000 SGT-SDBC-STELLA-INTEGER)
        (cl:setq result :int))
       ((CL:EQ TEST-VALUE-000 SGT-SDBC-STELLA-LONG-INTEGER)
        (cl:setq result :long))
       ((CL:EQ TEST-VALUE-000 SGT-SDBC-STELLA-DOUBLE-FLOAT)
        (cl:setq result :double))
       (CL:T (cl:setq result :unknown))))))
   RESULT))

;;; (DEFUN (CL-TRANSLATE-SQL-TYPE-SPECIFIER OBJECT) ...)

(CL:DEFUN CL-TRANSLATE-SQL-TYPE-SPECIFIER (STELLATYPE)
  (CL:LET* ((RESULT NULL))
   (CL:COND
    ((CL:OR (CL:EQ STELLATYPE NULL)
      (CL:EQ STELLATYPE SYM-SDBC-STELLA-NULL))
     (cl:setq result cl:t))
    (CL:T
     (CL:LET* ((TEST-VALUE-000 STELLATYPE))
      (CL:COND
       ((CL:EQ TEST-VALUE-000 SGT-SDBC-STELLA-CALENDAR-DATE)
        (cl:setq result cl:t))
       ((CL:EQ TEST-VALUE-000 SGT-SDBC-STELLA-STRING)
        (cl:setq result cl:t))
       ((CL:EQ TEST-VALUE-000 SGT-SDBC-STELLA-INTEGER)
        (cl:setq result :int))
       ((CL:EQ TEST-VALUE-000 SGT-SDBC-STELLA-LONG-INTEGER)
        (cl:setq result :long))
       ((CL:EQ TEST-VALUE-000 SGT-SDBC-STELLA-DOUBLE-FLOAT)
        (cl:setq result :double))
       (CL:T (cl:setq result :unknown))))))
   RESULT))

;;; (DEFUN (CL-TRANSLATE-SQL-TYPE-SPECIFIERS CONS) ...)

(CL:DEFUN CL-TRANSLATE-SQL-TYPE-SPECIFIERS (STELLATYPES)
  (CL:LET* ((VALUE-000 NIL))
   (CL:LET* ((TYPE NULL) (ITER-000 STELLATYPES) (COLLECT-000 NULL))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ TYPE (%%VALUE ITER-000))
     (CL:IF (CL:EQ COLLECT-000 NULL)
      (CL:PROGN
       (CL:SETQ COLLECT-000
        (CONS (CL-TRANSLATE-SQL-TYPE-SPECIFIER TYPE) NIL))
       (CL:IF (CL:EQ VALUE-000 NIL) (CL:SETQ VALUE-000 COLLECT-000)
        (ADD-CONS-TO-END-OF-CONS-LIST VALUE-000 COLLECT-000)))
      (CL:PROGN
       (CL:SETF (%%REST COLLECT-000)
        (CONS (CL-TRANSLATE-SQL-TYPE-SPECIFIER TYPE) NIL))
       (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))
     (CL:SETQ ITER-000 (%%REST ITER-000))))
   (CL:LET* ((VALUE-001 VALUE-000)) VALUE-001)))

;;; (DEFUN (EXECUTE-SQL OBJECT) ...)

(CL:DEFUN %EXECUTE-SQL (CONNECTION SQL OPTIONS)
  "Execute a SQL statement, and return a table as the reuslt
                  of a SQL query (represented as a (CONS OF (CONS OF OBJECT))),
                  or NULL as the result of a successfull SQL insert, update,
                  delete or other command.
                  `sql' can either be a string representing a SQL command or
                  a PREPARED-STATEMENT.
                  Options include: 
                     :types <typelist>, where <typelist> is a cons list of surrogates
                  specifying the expected Stella types.  Legal surrogate values are
                  @INTEGER, @LONG-INTEGER, @DOUBLE-FLOAT, @CALENDAR-DATE, @STRING, and
                  NULL.  If NULL is specified, values are returned as strings.
                  A DATABASE-EXCEPTION is thrown if execution is unsuccessful."
  (MAYBE-RENEW-CONNECTION CONNECTION)
  (CL:LET*
   ((RESULT NULL) (NCON (%NATIVE-CONNECTION CONNECTION))
    (PROPLIST
     (VET-OPTIONS OPTIONS
      (GET-QUOTED-TREE "((:TYPES) \"/SDBC\")" "/SDBC")))
    (TYPES (LOOKUP PROPLIST KWD-SDBC-TYPES)))
   (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE SQL)))
    (CL:COND
     ((SUBTYPE-OF-STRING? TEST-VALUE-000)
      (CL:PROGN
       (LOGMSG "SDBC" KWD-SDBC-HIGH (WRAP-STRING "execute-sql: sql=")
        SQL)
       (CL:SETQ RESULT
        (cl-execute-sql ncon (unwrap-string sql) types))))
     ((SUBTYPE-OF? TEST-VALUE-000 SGT-SDBC-SDBC-PREPARED-STATEMENT)
      (CL:PROGN
       (LOGMSG "SDBC" KWD-SDBC-HIGH
        (WRAP-STRING "execute-sql: prepared sql=")
        (WRAP-STRING (%SQL SQL)) (WRAP-STRING ", parameters=")
        (%PARAMETERS SQL))
       (CL:SETQ RESULT (cl-do-execute-prepared-statement ncon sql))))
     (CL:T
      (CL:ERROR
       (NEW-STELLA-EXCEPTION
        "`sql' argument must be of type STRING-WRAPPER or PREPARED-STATEMENT")))))
   (COERCE-UNCOERCED-VALUES-IN-TABLE RESULT TYPES)))

(CL:DEFUN EXECUTE-SQL-EVALUATOR-WRAPPER (ARGUMENTS)
  (%EXECUTE-SQL (%%VALUE ARGUMENTS) (%%VALUE (%%REST ARGUMENTS))
   (%%REST (%%REST ARGUMENTS))))

(CL:DEFMACRO EXECUTE-SQL (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Execute a SQL statement, and return a table as the reuslt
                  of a SQL query (represented as a (CONS OF (CONS OF OBJECT))),
                  or NULL as the result of a successfull SQL insert, update,
                  delete or other command.
                  `sql' can either be a string representing a SQL command or
                  a PREPARED-STATEMENT.
                  Options include: 
                     :types <typelist>, where <typelist> is a cons list of surrogates
                  specifying the expected Stella types.  Legal surrogate values are
                  @INTEGER, @LONG-INTEGER, @DOUBLE-FLOAT, @CALENDAR-DATE, @STRING, and
                  NULL.  If NULL is specified, values are returned as strings.
                  A DATABASE-EXCEPTION is thrown if execution is unsuccessful."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/SDBC/EXECUTE-SQL|)) (CL:MACRO-FUNCTION (CL:QUOTE EXECUTE-SQL)))

;;; (DEFUN (CL-EXECUTE-SQL OBJECT) ...)

(CL:DEFUN CL-EXECUTE-SQL (CONNECTION SQL TYPES)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SQL))
  #+MCL
  (CL:CHECK-TYPE SQL CL:SIMPLE-STRING)
  #+:EXCL
         (cl:progn 
          (cl:require :aodbc-v2)
          (cl:handler-case
              (cl:or
               (stellify-with-nil-to-null
                (cl:if (null? types) 
                    (dbi:sql sql :db connection)
                    (dbi:sql sql :db connection 
                             :types (cl-translate-sql-type-specifiers types))))
               NULL)
            (dbi:ODBC-ERROR (c)
              (cl:error
               (NEW-DATABASE-EXCEPTION (cl:format cl:nil "Database Error: ~A~%" c))))
            (cl:ERROR (c)
              (cl:error
               (NEW-UNHANDLED-EXCEPTION
                (cl:format cl:nil "execute-sql: Caught unhandled exception ~A.~%" c))))))
         #+:CLSQL
         (cl:handler-case
            (cl:or
               (stellify-with-nil-to-null
                (cl:cond ((cl:not (sql-query? sql))
                          (clsql:execute-command sql :database connection)
                          NULL)
                         ((null? types) 
                          (clsql:query sql :database connection :result-types cl:nil))
                         (cl:t
                           (clsql:query sql :database connection 
                                        :result-types (cl-translate-sql-type-specifiers types)))))
               NULL)
            (clsql:SQL-ERROR (c)
              (cl:error
               (NEW-DATABASE-EXCEPTION (cl:format cl:nil "Database Error: ~A~%" c))))
            (cl:ERROR (c)
              (cl:error
               (NEW-UNHANDLED-EXCEPTION
                (cl:format cl:nil "execute-sql: Caught unhandled exception ~A.~%" c)))))
         #-(OR :EXCL :CLSQL) NULL)

;;; (DEFUN (CL-DO-EXECUTE-PREPARED-STATEMENT OBJECT) ...)

(CL:DEFUN CL-DO-EXECUTE-PREPARED-STATEMENT (CONNECTION SQL)
  (CL:SETQ SQL SQL)
  #+:EXCL
         (cl:progn
           (cl:require :aodbc-v2)
           (cl:handler-case
               (cl:or
                (stellify-with-nil-to-null
                 (dbi:run-prepared-sql :db connection))
                NULL)
             (dbi:ODBC-ERROR (c)
               (cl:error
                (NEW-DATABASE-EXCEPTION (cl:format cl:nil "Database Error: ~A~%" c))))
             (cl:ERROR (c)
               (cl:error
                (NEW-UNHANDLED-EXCEPTION
                 (cl:format cl:nil "execute-sql: Caught unhandled exception ~A.~%" c))))))
         #+:CLSQL
         (CL:error (NEW-BAD-ARGUMENT-EXCEPTION "CLSQL does not support prepared statements."))
         #-(OR :EXCL :CLSQL) NULL)

;;; (DEFUN (GET-RESULT-SET RESULT-SET-ITERATOR) ...)

(CL:DEFUN GET-RESULT-SET (CONNECTION SQL CL:&REST OPTIONS)
  "Execute a SQL query, and return a ResultSet object.
                  Options include: 
                     :types <typelist>, where <typelist> is a cons list of surrogates
                  specifying the expected Stella types.  Legal surrogate values are
                  @INTEGER, @LONG-INTEGER, @DOUBLE-FLOAT, @CALENDAR-DATE, @STRING, and
                  NULL.  If NULL is specified, values are returned as strings.
                  A DATABASE-EXCEPTION is thrown if execution is unsuccessful."
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SQL))
  #+MCL
  (CL:CHECK-TYPE SQL CL:SIMPLE-STRING)
  (MAYBE-RENEW-CONNECTION CONNECTION)
  (CL:LET*
   ((NATIVERESULTSET NULL)
    (NATIVECONNECTION (%NATIVE-CONNECTION CONNECTION))
    (RESULTSETITERATOR (NEW-RESULT-SET-ITERATOR)))
   (CL:LET* ((ARGLIST-000 NIL))
    (CL:LET* ((ARG-000 NULL) (ITER-000 OPTIONS) (COLLECT-000 NULL))
     (CL:LOOP WHILE ITER-000 DO (CL:SETQ ARG-000 (CL:POP ITER-000))
      (CL:IF (CL:EQ COLLECT-000 NULL)
       (CL:PROGN (CL:SETQ COLLECT-000 (CONS ARG-000 NIL))
        (CL:IF (CL:EQ ARGLIST-000 NIL)
         (CL:SETQ ARGLIST-000 COLLECT-000)
         (ADD-CONS-TO-END-OF-CONS-LIST ARGLIST-000 COLLECT-000)))
       (CL:PROGN (CL:SETF (%%REST COLLECT-000) (CONS ARG-000 NIL))
        (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))))
    (CL:LET*
     ((PROPLIST
       (VET-OPTIONS ARGLIST-000
        (GET-QUOTED-TREE "((:TYPES) \"/SDBC\")" "/SDBC")))
      (TYPES (LOOKUP PROPLIST KWD-SDBC-TYPES)))
     (CL:SETF (%TYPES RESULTSETITERATOR) TYPES)
     (LOGMSG "SDBC" KWD-SDBC-HIGH (WRAP-STRING "get-result-set: sql=")
      (WRAP-STRING SQL))
     (CL:SETQ NATIVERESULTSET
      (cl-get-native-result-set nativeConnection sql types))
     (CL:SETF (%RESULT-SET RESULTSETITERATOR) NATIVERESULTSET)
     RESULTSETITERATOR))))

;;; (DEFUN (CL-GET-NATIVE-RESULT-SET NATIVE-RESULT-SET) ...)

(CL:DEFUN CL-GET-NATIVE-RESULT-SET (CONNECTION SQL TYPES)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SQL))
  #+MCL
  (CL:CHECK-TYPE SQL CL:SIMPLE-STRING)
  #+:EXCL
       (cl:progn 
         (cl:require :aodbc-v2)
         (cl:handler-case
             (cl:if (null? types) 
                 (dbi:sql sql :db connection :query cl:t)
                 (dbi:sql sql :db connection :query cl:t
                              :types (cl-translate-sql-type-specifiers types)))
           (dbi:ODBC-ERROR (c)
             (cl:error
              (NEW-DATABASE-EXCEPTION (cl:format cl:nil "Database Error: ~A~%" c))))
           (cl:ERROR (c)
             (cl:error
              (NEW-UNHANDLED-EXCEPTION
               (cl:format cl:nil "get-result-set: Caught unhandled exception ~A.~%" c))))))
       #+:CLSQL
       (cl:handler-case
          (cl:if (null? types) 
                 (clsql:query sql :database connection :result-types cl:nil)
                 (clsql:query sql :database connection
                            :result-types (cl-translate-sql-type-specifiers types)))
           (clsql:SQL-ERROR (c)
             (cl:error
              (NEW-DATABASE-EXCEPTION (cl:format cl:nil "Database Error: ~A~%" c))))
           (cl:ERROR (c)
             (cl:error
              (NEW-UNHANDLED-EXCEPTION
               (cl:format cl:nil "get-result-set: Caught unhandled exception ~A.~%" c)))))
         #-(OR :EXCL :CLSQL) NULL)

;;; (DEFMETHOD (NEXT? BOOLEAN) ...)

(CL:DEFMETHOD NEXT? ((SELF RESULT-SET-ITERATOR))
  (CL:LET* ((NATIVE-RESULT-SET (%RESULT-SET SELF)) (RESULT NULL))
   (CL:WHEN (NULL? NATIVE-RESULT-SET) (CL:RETURN-FROM NEXT? CL:NIL))
   (CL:PROGN
    (CL:SETQ RESULT
     #+:EXCL (dbi:fetch-row native-result-set cl:nil NULL)
            #+:CLSQL (cl:if native-result-set
                         (cl:pop native-result-set)
                         NULL)
            #-(OR :EXCL CLSQL) NULL)
    (CL:SETF (%RESULT-SET SELF) NATIVE-RESULT-SET)
    (CL:WHEN (CL:NOT (CL:EQ RESULT NULL))
     (CL:SETQ RESULT (STELLIFY-WITH-NIL-TO-NULL RESULT))))
   (CL:SETF (%VALUE SELF)
    (CL:IF (CL:NOT (CL:EQ RESULT NULL))
     (COERCE-UNCOERCED-COLUMN-VALUES RESULT (%TYPES SELF)) NULL))
   (CL:COND ((CL:NOT (CL:EQ RESULT NULL)) CL:T)
    (CL:T #+:EXCL (dbi:close-query native-result-set)
     (CL:SETF (%RESULT-SET SELF) NULL) CL:NIL))))

;;; (DEFUN (SQL-ESCAPE-STRING STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:SIMPLE-STRING CL:T) CL:SIMPLE-STRING)
  SQL-ESCAPE-STRING))
(CL:DEFUN SQL-ESCAPE-STRING (VALUE QUOTECHAR)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING VALUE))
  #+MCL
  (CL:CHECK-TYPE VALUE CL:SIMPLE-STRING)
  (CL:LET* ((CURSOR (CL:1- (CL:THE CL:FIXNUM (CL:LENGTH VALUE)))))
   (CL:DECLARE (CL:TYPE CL:FIXNUM CURSOR))
   (CL:LOOP WHILE (CL:>= CURSOR 0) DO
    (CL:WHEN
     (CL:EQL
      (CL:LET ((SELF VALUE) (POSITION CURSOR))
       (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
        (CL:TYPE CL:FIXNUM POSITION))
       (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
        (CL:THE CL:FIXNUM POSITION)))
      QUOTECHAR)
     (CL:RETURN-FROM SQL-ESCAPE-STRING
      (REPLACE-SUBSTRINGS VALUE (MAKE-STRING 2 QUOTECHAR)
       (MAKE-STRING 1 QUOTECHAR))))
    (CL:SETQ CURSOR (CL:1- CURSOR)))
   VALUE))

;;; (DEFUN (SQL-QUOTE-CHARACTER CHARACTER) ...)

(CL:DEFUN SQL-QUOTE-CHARACTER (DBMS-NAME LEXICALTYPE)
  (CL:COND ((CL:EQ LEXICALTYPE KWD-SDBC-STRING-CONSTANT) #\')
   ((CL:EQ LEXICALTYPE KWD-SDBC-IDENTIFIER)
    (CL:COND ((CL:EQ DBMS-NAME KWD-SDBC-MYSQL) #\`) (CL:T #\")))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" LEXICALTYPE
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000)))))))

;;; (DEFUN PRINT-VALUE-LIST ...)

(CL:DEFUN PRINT-VALUE-LIST (STREAM VALUES QUOTECHAR)
  (CL:LET*
   ((VALUE NULL) (ITER-000 VALUES) (I NULL-INTEGER) (ITER-001 1))
   (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-001))
   (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
    (CL:SETQ VALUE (%%VALUE ITER-000)) (CL:SETQ I ITER-001)
    (CL:WHEN (CL:> I 1) (%%PRINT-STREAM (%NATIVE-STREAM STREAM) ","))
    (CL:COND
     ((CL:OR (CL:EQ VALUE NULL) (CL:EQ VALUE SYM-SDBC-STELLA-NULL)
       (CL:EQ VALUE KWD-SDBC-NULL))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM) "NULL"))
     ((CL:OR (CL:EQ VALUE SYM-SDBC-STELLA-DEFAULT)
       (CL:EQ VALUE KWD-SDBC-DEFAULT))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM) "DEFAULT"))
     (CL:T
      (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE VALUE)))
       (CL:COND
        ((SUBTYPE-OF-INTEGER? TEST-VALUE-000)
         (CL:PROGN
          (%%PRINT-STREAM (%NATIVE-STREAM STREAM)
           (%WRAPPER-VALUE VALUE))))
        ((SUBTYPE-OF-FLOAT? TEST-VALUE-000)
         (CL:PROGN
          (%%PRINT-STREAM (%NATIVE-STREAM STREAM)
           (%WRAPPER-VALUE VALUE))))
        ((SUBTYPE-OF-VERBATIM-STRING? TEST-VALUE-000)
         (CL:PROGN
          (%%PRINT-STREAM (%NATIVE-STREAM STREAM)
           (%WRAPPER-VALUE VALUE))))
        ((SUBTYPE-OF-STRING? TEST-VALUE-000)
         (CL:PROGN
          (%%PRINT-STREAM (%NATIVE-STREAM STREAM) QUOTECHAR
           (SQL-ESCAPE-STRING (%WRAPPER-VALUE VALUE) QUOTECHAR)
           QUOTECHAR)))
        (CL:T
         (%%PRINT-STREAM (%NATIVE-STREAM STREAM) QUOTECHAR
          (SQL-ESCAPE-STRING (STRINGIFY VALUE) QUOTECHAR)
          QUOTECHAR))))))
    (CL:SETQ ITER-000 (%%REST ITER-000))
    (CL:SETQ ITER-001 (CL:1+ ITER-001)))))

;;; (DEFUN INSERT-ROW ...)

(CL:DEFUN %INSERT-ROW (CONNECTION TABLE COLUMNS VALUES)
  "Insert a row of `values' into `table'.  `columns'
can be NULL or NIL in which case `values' must be suppied for all
columns.  If `columns' are given `values' will be only inserted in
the specified columns.  Table and column names will be quoted which
means their casing must match exactly their definition (no case
conversion will be performed).  Supplied `values' can be strings,
integers or floats.  Strings will be quoted and escaped appropriately.
The values NULL, :NULL or (quote NULL) translate into NULL.  The
values :DEFAULT or (quote DEFAULT) translate into DEFAULT.  Arbitrary
unquoted strings can be generated via VERBATIM-STRING-WRAPPERs as
values (e.g., for something like `seq.nextval' in Oracle)."
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TABLE))
  #+MCL
  (CL:CHECK-TYPE TABLE CL:SIMPLE-STRING)
  (CL:WHEN (CL:OR (CL:EQ VALUES NULL) (CL:EQ VALUES NIL))
   (CL:RETURN-FROM %INSERT-ROW))
  (%INSERT-ROWS CONNECTION TABLE COLUMNS (CONS VALUES NIL)))

(CL:DEFUN INSERT-ROW-EVALUATOR-WRAPPER (ARGUMENTS)
  (%INSERT-ROW (%%VALUE ARGUMENTS)
   (%WRAPPER-VALUE (%%VALUE (%%REST ARGUMENTS)))
   (%%VALUE (%%REST (%%REST ARGUMENTS)))
   (%%VALUE (%%REST (%%REST (%%REST ARGUMENTS))))))

(CL:DEFMACRO INSERT-ROW (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Insert a row of `values' into `table'.  `columns'
can be NULL or NIL in which case `values' must be suppied for all
columns.  If `columns' are given `values' will be only inserted in
the specified columns.  Table and column names will be quoted which
means their casing must match exactly their definition (no case
conversion will be performed).  Supplied `values' can be strings,
integers or floats.  Strings will be quoted and escaped appropriately.
The values NULL, :NULL or (quote NULL) translate into NULL.  The
values :DEFAULT or (quote DEFAULT) translate into DEFAULT.  Arbitrary
unquoted strings can be generated via VERBATIM-STRING-WRAPPERs as
values (e.g., for something like `seq.nextval' in Oracle)."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/SDBC/INSERT-ROW|)) (CL:MACRO-FUNCTION (CL:QUOTE INSERT-ROW)))

;;; (DEFUN INSERT-ROWS ...)

(CL:DEFUN %INSERT-ROWS (CONNECTION TABLE COLUMNS ROWS)
  "Insert a set of `rows' into `table'.  `columns'
can be NULL or NIL in which case values must be suppied for all
columns.  If `columns' are given `values' will be only inserted in
the specified columns.  Table and column names will be quoted which
means their casing must match exactly their definition (no case
conversion will be performed).  See `insert-row' for a description
of supported value formats.  DEFAULT values are currently not supported
for Oracle!  This function performs a fairly efficient multi-row
insert which is significantly faster than inserting rows one by one."
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TABLE))
  #+MCL
  (CL:CHECK-TYPE TABLE CL:SIMPLE-STRING)
  (CL:WHEN (CL:OR (CL:EQ ROWS NULL) (CL:EQ ROWS NIL))
   (CL:RETURN-FROM %INSERT-ROWS))
  (CL:LET*
   ((SQL NULL)
    (IDQUOTE
     (SQL-QUOTE-CHARACTER (GET-DBMS-NAME CONNECTION)
      KWD-SDBC-IDENTIFIER))
    (VALUEQUOTE
     (SQL-QUOTE-CHARACTER (GET-DBMS-NAME CONNECTION)
      KWD-SDBC-STRING-CONSTANT))
    (BLOCKLENGTH 1000) (ORACLEBLOCKLENGTH 100))
   (CL:DECLARE (CL:TYPE CL:FIXNUM BLOCKLENGTH ORACLEBLOCKLENGTH))
   (CL:LOOP (CL:SETQ SQL (NEW-OUTPUT-STRING-STREAM))
    (%%PRINT-STREAM (%NATIVE-STREAM SQL) "INSERT INTO " IDQUOTE
     (SQL-ESCAPE-STRING TABLE IDQUOTE) IDQUOTE)
    (CL:WHEN
     (CL:AND (CL:NOT (CL:EQ COLUMNS NULL))
      (CL:NOT (CL:EQ COLUMNS NIL)))
     (%%PRINT-STREAM (%NATIVE-STREAM SQL) "(")
     (PRINT-VALUE-LIST SQL COLUMNS IDQUOTE)
     (%%PRINT-STREAM (%NATIVE-STREAM SQL) ")"))
    (CL:COND
     ((CL:AND (CL:EQ (GET-DBMS-NAME CONNECTION) KWD-SDBC-ORACLE)
       (CL:NOT (CL:EQ (%%REST ROWS) NIL)))
      (CL:LET*
       ((VALUES NULL) (ITER-000 ROWS) (I NULL-INTEGER) (ITER-001 1)
        (UPPER-BOUND-000 ORACLEBLOCKLENGTH)
        (UNBOUNDED?-000 (CL:= UPPER-BOUND-000 NULL-INTEGER)))
       (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-001 UPPER-BOUND-000))
       (CL:LOOP WHILE
        (CL:AND (CL:NOT (CL:EQ ITER-000 NIL))
         (CL:OR UNBOUNDED?-000 (CL:<= ITER-001 UPPER-BOUND-000)))
        DO (CL:SETQ VALUES (%%VALUE ITER-000)) (CL:SETQ I ITER-001)
        (CL:WHEN (CL:> I 1)
         (%%PRINT-STREAM (%NATIVE-STREAM SQL) " UNION"))
        (%%PRINT-STREAM (%NATIVE-STREAM SQL) " SELECT ")
        (PRINT-VALUE-LIST SQL VALUES VALUEQUOTE)
        (%%PRINT-STREAM (%NATIVE-STREAM SQL) " FROM DUAL")
        (CL:SETQ ROWS (%%REST ROWS))
        (CL:SETQ ITER-000 (%%REST ITER-000))
        (CL:SETQ ITER-001 (CL:1+ ITER-001)))))
     (CL:T (%%PRINT-STREAM (%NATIVE-STREAM SQL) " VALUES")
      (CL:LET*
       ((VALUES NULL) (ITER-002 ROWS) (I NULL-INTEGER) (ITER-003 1)
        (UPPER-BOUND-001 BLOCKLENGTH)
        (UNBOUNDED?-001 (CL:= UPPER-BOUND-001 NULL-INTEGER)))
       (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-003 UPPER-BOUND-001))
       (CL:LOOP WHILE
        (CL:AND (CL:NOT (CL:EQ ITER-002 NIL))
         (CL:OR UNBOUNDED?-001 (CL:<= ITER-003 UPPER-BOUND-001)))
        DO (CL:SETQ VALUES (%%VALUE ITER-002)) (CL:SETQ I ITER-003)
        (CL:WHEN (CL:> I 1) (%%PRINT-STREAM (%NATIVE-STREAM SQL) ","))
        (%%PRINT-STREAM (%NATIVE-STREAM SQL) "(")
        (PRINT-VALUE-LIST SQL VALUES VALUEQUOTE)
        (%%PRINT-STREAM (%NATIVE-STREAM SQL) ")")
        (CL:SETQ ROWS (%%REST ROWS))
        (CL:SETQ ITER-002 (%%REST ITER-002))
        (CL:SETQ ITER-003 (CL:1+ ITER-003))))))
    (%EXECUTE-SQL CONNECTION (WRAP-STRING (THE-STRING-READER SQL)) NIL)
    (CL:WHEN (CL:EQ ROWS NIL) (CL:RETURN)))))

(CL:DEFUN INSERT-ROWS-EVALUATOR-WRAPPER (ARGUMENTS)
  (%INSERT-ROWS (%%VALUE ARGUMENTS)
   (%WRAPPER-VALUE (%%VALUE (%%REST ARGUMENTS)))
   (%%VALUE (%%REST (%%REST ARGUMENTS)))
   (%%VALUE (%%REST (%%REST (%%REST ARGUMENTS))))))

(CL:DEFMACRO INSERT-ROWS (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Insert a set of `rows' into `table'.  `columns'
can be NULL or NIL in which case values must be suppied for all
columns.  If `columns' are given `values' will be only inserted in
the specified columns.  Table and column names will be quoted which
means their casing must match exactly their definition (no case
conversion will be performed).  See `insert-row' for a description
of supported value formats.  DEFAULT values are currently not supported
for Oracle!  This function performs a fairly efficient multi-row
insert which is significantly faster than inserting rows one by one."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/SDBC/INSERT-ROWS|)) (CL:MACRO-FUNCTION (CL:QUOTE INSERT-ROWS)))

;;; (DEFUN (COERCE-UNCOERCED-VALUES-IN-TABLE CONS) ...)

(CL:DEFUN COERCE-UNCOERCED-VALUES-IN-TABLE (TABLE TYPES)
  (CL:WHEN (CL:EQ TYPES NULL)
   (CL:RETURN-FROM COERCE-UNCOERCED-VALUES-IN-TABLE TABLE))
  (CL:LET* ((RESULT NIL))
   (CL:LET* ((ROW NULL) (ITER-000 TABLE) (COLLECT-000 NULL))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ ROW (%%VALUE ITER-000))
     (CL:IF (CL:EQ COLLECT-000 NULL)
      (CL:PROGN
       (CL:SETQ COLLECT-000
        (CONS (COERCE-UNCOERCED-COLUMN-VALUES ROW TYPES) NIL))
       (CL:IF (CL:EQ RESULT NIL) (CL:SETQ RESULT COLLECT-000)
        (ADD-CONS-TO-END-OF-CONS-LIST RESULT COLLECT-000)))
      (CL:PROGN
       (CL:SETF (%%REST COLLECT-000)
        (CONS (COERCE-UNCOERCED-COLUMN-VALUES ROW TYPES) NIL))
       (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))
     (CL:SETQ ITER-000 (%%REST ITER-000))))
   RESULT))

;;; (DEFUN (COERCE-UNCOERCED-COLUMN-VALUES CONS) ...)

(CL:DEFUN COERCE-UNCOERCED-COLUMN-VALUES (ROW TYPES)
  (CL:WHEN (CL:EQ TYPES NULL)
   (CL:RETURN-FROM COERCE-UNCOERCED-COLUMN-VALUES ROW))
  (CL:LET* ((RESULT NIL))
   (CL:LET*
    ((VALUE NULL) (ITER-000 ROW) (TYPE NULL) (ITER-001 TYPES)
     (COLLECT-000 NULL))
    (CL:LOOP WHILE
     (CL:AND (CL:NOT (CL:EQ ITER-000 NIL))
      (CL:NOT (CL:EQ ITER-001 NIL)))
     DO (CL:SETQ VALUE (%%VALUE ITER-000))
     (CL:SETQ TYPE (%%VALUE ITER-001))
     (CL:IF (CL:EQ COLLECT-000 NULL)
      (CL:PROGN
       (CL:SETQ COLLECT-000
        (CONS
         (CL:IF (STRING? VALUE)
          (CONVERT-STRING-TO-TYPED-OBJECT (%WRAPPER-VALUE VALUE) TYPE)
          VALUE)
         NIL))
       (CL:IF (CL:EQ RESULT NIL) (CL:SETQ RESULT COLLECT-000)
        (ADD-CONS-TO-END-OF-CONS-LIST RESULT COLLECT-000)))
      (CL:PROGN
       (CL:SETF (%%REST COLLECT-000)
        (CONS
         (CL:IF (STRING? VALUE)
          (CONVERT-STRING-TO-TYPED-OBJECT (%WRAPPER-VALUE VALUE) TYPE)
          VALUE)
         NIL))
       (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))
     (CL:SETQ ITER-000 (%%REST ITER-000))
     (CL:SETQ ITER-001 (%%REST ITER-001))))
   RESULT))

;;; (DEFUN (CONVERT-STRING-TO-TYPED-OBJECT OBJECT) ...)

(CL:DEFUN CONVERT-STRING-TO-TYPED-OBJECT (VALUESTRING TYPESPEC)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING VALUESTRING))
  #+MCL
  (CL:CHECK-TYPE VALUESTRING CL:SIMPLE-STRING)
  (CL:COND
   ((CL:EQ TYPESPEC SGT-SDBC-STELLA-CALENDAR-DATE)
    (STRING-TO-CALENDAR-DATE VALUESTRING))
   (CL:T (WRAP-STRING VALUESTRING))))

;;; (DEFUN (PREPARE-STATEMENT PREPARED-STATEMENT) ...)

(CL:DEFUN %PREPARE-STATEMENT (CONNECTION SQL)
  "Prepare the `sql' statement for execution at the server and return
a prepared statement object.  After binding all its paramters via `bind-parameter'
the statement can be executed via `execute-sql'.
IMPORTANT: Only one prepared statement can be associated with a connection at a time."
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SQL))
  #+MCL
  (CL:CHECK-TYPE SQL CL:SIMPLE-STRING)
  (MAYBE-RENEW-CONNECTION CONNECTION)
  (CL:LET*
   ((RESULT (NEW-PREPARED-STATEMENT))
    (NATIVECONNECTION (%NATIVE-CONNECTION CONNECTION)))
   (CL:SETF (%CONNECTION RESULT) CONNECTION)
   (CL:SETF (%STATEMENT CONNECTION) RESULT) (CL:SETF (%SQL RESULT) SQL)
   #+:EXCL (dbi:prepare-sql sql :db nativeConnection) RESULT))

(CL:DEFUN PREPARE-STATEMENT-EVALUATOR-WRAPPER (ARGUMENTS)
  (%PREPARE-STATEMENT (%%VALUE ARGUMENTS)
   (%WRAPPER-VALUE (%%VALUE (%%REST ARGUMENTS)))))

(CL:DEFMACRO PREPARE-STATEMENT (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Prepare the `sql' statement for execution at the server and return
a prepared statement object.  After binding all its paramters via `bind-parameter'
the statement can be executed via `execute-sql'.
IMPORTANT: Only one prepared statement can be associated with a connection at a time."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/SDBC/PREPARE-STATEMENT|)) (CL:MACRO-FUNCTION (CL:QUOTE PREPARE-STATEMENT)))

;;; (DEFUN BIND-PARAMETER ...)

(CL:DEFUN %BIND-PARAMETER (STATEMENT POSITION TYPESPEC VALUE)
  "Bind the parameter at `position' (1-based) in the prepared
statement `statement' to `value'.  `typeSpec' characterizes the type of
`value' for proper translation and coercion."
  (CL:DECLARE (CL:TYPE CL:FIXNUM POSITION))
  #+MCL
  (CL:CHECK-TYPE POSITION CL:FIXNUM)
  (CL:LET* ((CONNECTION (%CONNECTION STATEMENT)) (NCON NULL))
   (MAYBE-RENEW-CONNECTION CONNECTION)
   (CL:SETQ NCON (%NATIVE-CONNECTION CONNECTION))
   (INSERT-AT (%PARAMETERS STATEMENT) (WRAP-INTEGER POSITION)
    (CONS-LIST TYPESPEC VALUE))
   (CL:WHEN (CL:EQ TYPESPEC SGT-SDBC-STELLA-CALENDAR-DATE)
    (CL:SETQ TYPESPEC SGT-SDBC-STELLA-STRING)
    (CL:WHEN (CL:NOT (CL:EQ VALUE NULL))
     (CL:SETQ VALUE
      (WRAP-STRING (CALENDAR-DATE-TO-SQL-STRING VALUE)))))
   (cl-do-bind-parameter statement position typeSpec value)))

(CL:DEFUN BIND-PARAMETER-EVALUATOR-WRAPPER (ARGUMENTS)
  (%BIND-PARAMETER (%%VALUE ARGUMENTS)
   (%WRAPPER-VALUE (%%VALUE (%%REST ARGUMENTS)))
   (%%VALUE (%%REST (%%REST ARGUMENTS)))
   (%%VALUE (%%REST (%%REST (%%REST ARGUMENTS))))))

(CL:DEFMACRO BIND-PARAMETER (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Bind the parameter at `position' (1-based) in the prepared
statement `statement' to `value'.  `typeSpec' characterizes the type of
`value' for proper translation and coercion."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/SDBC/BIND-PARAMETER|)) (CL:MACRO-FUNCTION (CL:QUOTE BIND-PARAMETER)))

;;; (DEFUN CL-DO-BIND-PARAMETER ...)

(CL:DEFUN CL-DO-BIND-PARAMETER (STATEMENT POSITION TYPESPEC VALUE)
  (CL:DECLARE (CL:TYPE CL:FIXNUM POSITION))
  #+MCL
  (CL:CHECK-TYPE POSITION CL:FIXNUM)
  (CL:LET*
   ((NATIVECONNECTION (%NATIVE-CONNECTION (%CONNECTION STATEMENT)))
    (NULL? (CL:EQ VALUE NULL))
    (WRAPPER? (ISA? VALUE SGT-SDBC-STELLA-WRAPPER)))
   #+EXCL
       (cl:let* ((transTypeSpec (cl-translate-sql-parameter-type-specifier typeSpec))
                 (par (dbi:bind-parameter position cl:nil
                                          (cl:if null? :null transTypeSpec)
                                          (cl:cond (null? 0)
                                                   ((cl:eq transTypeSpec :varchar) 255)
                                                   (cl:t cl:nil))
                                          :db nativeConnection)))
         (cl:cond (null? (cl:setq value cl:nil))
                  (wrapper? (cl:setq value (lispify value))))
         (cl:unless null?
           (cl:setf (ff:fslot-value par :data) value))
         par)))

;;; (DEFUN SET-AUTO-COMMIT ...)

(CL:DEFUN %SET-AUTO-COMMIT (CONNECTION FLAG)
  "Set the auto-commit feature of `connection' to TRUE or FALSE.
If a connection is in auto-commit mode, then all its SQL statements will be executed
and committed as individual transactions.  Otherwise, its SQL statements are grouped
into transactions that are terminated by a call to either `commit' or `rollback'.
By default, new connections are in auto-commit mode."
  (MAYBE-RENEW-CONNECTION CONNECTION)
  (CL:LET* ((NATIVE-CONNECTION (%NATIVE-CONNECTION CONNECTION)))
   #+:EXCL (dbi:set-autocommit flag :db native-connection)
     #+:CLSQL (clsql:set-autocommit flag :database native-connection)
   (CL:SETF (%AUTO-COMMIT? CONNECTION) FLAG)))

(CL:DEFUN SET-AUTO-COMMIT-EVALUATOR-WRAPPER (ARGUMENTS)
  (%SET-AUTO-COMMIT (%%VALUE ARGUMENTS)
   (%WRAPPER-VALUE (%%VALUE (%%REST ARGUMENTS)))))

(CL:DEFMACRO SET-AUTO-COMMIT (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Set the auto-commit feature of `connection' to TRUE or FALSE.
If a connection is in auto-commit mode, then all its SQL statements will be executed
and committed as individual transactions.  Otherwise, its SQL statements are grouped
into transactions that are terminated by a call to either `commit' or `rollback'.
By default, new connections are in auto-commit mode."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/SDBC/SET-AUTO-COMMIT|)) (CL:MACRO-FUNCTION (CL:QUOTE SET-AUTO-COMMIT)))

;;; (DEFUN COMMIT ...)

(CL:DEFUN %COMMIT (CONNECTION)
  "Commit the current transaction.  Makes all changes made since the
previous commit/rollback permanent and releases any database locks currently held
by this `connection' object.  This function is a no-op if auto-commit mode is
enabled (see `set-auto-commit')."
  (CL:WHEN (CL:NOT (%AUTO-COMMIT? CONNECTION))
   (CL:LET* ((NATIVE-CONNECTION (%NATIVE-CONNECTION CONNECTION)))
    #+:EXCL (dbi:end-transaction :commit :db native-connection)
    #+:CLSQL (clsql:commit :database native-connection))))

(CL:DEFMACRO COMMIT (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Commit the current transaction.  Makes all changes made since the
previous commit/rollback permanent and releases any database locks currently held
by this `connection' object.  This function is a no-op if auto-commit mode is
enabled (see `set-auto-commit')."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/SDBC/COMMIT|)) (CL:MACRO-FUNCTION (CL:QUOTE COMMIT)))

;;; (DEFUN ROLLBACK ...)

(CL:DEFUN %ROLLBACK (CONNECTION)
  "Rollback the current transaction.  Undoes all changes made in
the current transaction and releases any database locks currently held by this
`connection' object.  This function is a no-op if auto-commit mode is enabled
 (see `set-auto-commit')."
  (CL:WHEN (CL:NOT (%AUTO-COMMIT? CONNECTION))
   (CL:LET* ((NATIVE-CONNECTION (%NATIVE-CONNECTION CONNECTION)))
    #+:EXCL (dbi:end-transaction :rollback :db native-connection)
      #+:CLSQL (clsql:rollback :database native-connection))))

(CL:DEFMACRO ROLLBACK (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Rollback the current transaction.  Undoes all changes made in
the current transaction and releases any database locks currently held by this
`connection' object.  This function is a no-op if auto-commit mode is enabled
 (see `set-auto-commit')."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/SDBC/ROLLBACK|)) (CL:MACRO-FUNCTION (CL:QUOTE ROLLBACK)))

;;; (DEFCLASS TABLE-INFO ...)

(CL:DEFCLASS TABLE-INFO (STANDARD-OBJECT)
  ((DATABASE :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %DATABASE)
   (SCHEMA :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %SCHEMA)
   (NAME :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %NAME)
   (TYPE :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %TYPE)
   (REMARKS :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %REMARKS)
   (COLUMNS :ALLOCATION :INSTANCE :ACCESSOR %COLUMNS)))

(CL:DEFUN NEW-TABLE-INFO ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE TABLE-INFO)))
   (CL:SETF (%COLUMNS SELF) NULL)
   (CL:SETF (%REMARKS SELF) STELLA::NULL-STRING)
   (CL:SETF (%TYPE SELF) STELLA::NULL-STRING)
   (CL:SETF (%NAME SELF) STELLA::NULL-STRING)
   (CL:SETF (%SCHEMA SELF) STELLA::NULL-STRING)
   (CL:SETF (%DATABASE SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF TABLE-INFO))
  SGT-SDBC-SDBC-TABLE-INFO)

(CL:DEFUN ACCESS-TABLE-INFO-SLOT-VALUE (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-DATABASE)
    (CL:IF SETVALUE? (CL:SETF (%DATABASE SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%DATABASE SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-CATALOG)
    (CL:IF SETVALUE? (CL:SETF (%DATABASE SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%DATABASE SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-SCHEMA)
    (CL:IF SETVALUE? (CL:SETF (%SCHEMA SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%SCHEMA SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-STELLA-NAME)
    (CL:IF SETVALUE? (CL:SETF (%NAME SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%NAME SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-STELLA-TYPE)
    (CL:IF SETVALUE? (CL:SETF (%TYPE SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%TYPE SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-REMARKS)
    (CL:IF SETVALUE? (CL:SETF (%REMARKS SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%REMARKS SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-COLUMNS)
    (CL:IF SETVALUE? (CL:SETF (%COLUMNS SELF) VALUE)
     (CL:SETQ VALUE (%COLUMNS SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS COLUMN-INFO ...)

(CL:DEFCLASS COLUMN-INFO (STANDARD-OBJECT)
  ((DATABASE :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %DATABASE)
   (SCHEMA :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %SCHEMA)
   (TABLE-NAME :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %TABLE-NAME)
   (NAME :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %NAME)
   (DATA-TYPE :TYPE CL:FIXNUM :INITFORM NULL-INTEGER :DOCUMENTATION
    "SQL type from java.sql.Types." :ALLOCATION :INSTANCE :ACCESSOR
    %DATA-TYPE)
   (DATA-TYPE-NAME :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :DOCUMENTATION
    "Data source dependent type name, for a UDT the type name is fully qualified."
    :ALLOCATION :INSTANCE :ACCESSOR %DATA-TYPE-NAME)
   (COLUMN-SIZE :TYPE CL:FIXNUM :INITFORM NULL-INTEGER :DOCUMENTATION
    "Column size. For char or date types this is the maximum number of characters,
for numeric or decimal types this is precision." :ALLOCATION :INSTANCE
    :ACCESSOR %COLUMN-SIZE)
   (BUFFER-LENGTH :TYPE CL:FIXNUM :INITFORM NULL-INTEGER :DOCUMENTATION
    "Not used." :ALLOCATION :INSTANCE :ACCESSOR %BUFFER-LENGTH)
   (DECIMAL-DIGITS :TYPE CL:FIXNUM :INITFORM NULL-INTEGER
    :DOCUMENTATION "The number of fractional digits." :ALLOCATION
    :INSTANCE :ACCESSOR %DECIMAL-DIGITS)
   (RADIX :TYPE CL:FIXNUM :INITFORM NULL-INTEGER :DOCUMENTATION
    "Radix (typically either 10 or 2)." :ALLOCATION :INSTANCE :ACCESSOR
    %RADIX)
   (NULLABLE? :DOCUMENTATION
    "TRUE means definitely allows NULL values, FALSE means might not allow
NULL values, NULL means nullability unknown." :ALLOCATION :INSTANCE
    :ACCESSOR %NULLABLE?)
   (IS-NULLABLE? :DOCUMENTATION
    "TRUE means might allow NULL values, FALSE means definitely does not
allow NULL values, NULL means nullability unknown." :ALLOCATION
    :INSTANCE :ACCESSOR %IS-NULLABLE?)
   (DOCUMENTATION :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :DOCUMENTATION "Comment describing column (may be null)."
    :ALLOCATION :INSTANCE :ACCESSOR %DOCUMENTATION)
   (DEFAULT-VALUE :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %DEFAULT-VALUE)
   (SQL-DATA-TYPE :TYPE CL:FIXNUM :INITFORM NULL-INTEGER :DOCUMENTATION
    "Not used." :ALLOCATION :INSTANCE :ACCESSOR %SQL-DATA-TYPE)
   (SQL-DATETIME-SUB :TYPE CL:FIXNUM :INITFORM NULL-INTEGER
    :DOCUMENTATION "Not used." :ALLOCATION :INSTANCE :ACCESSOR
    %SQL-DATETIME-SUB)
   (CHAR-OCTET-LENGTH :TYPE CL:FIXNUM :INITFORM NULL-INTEGER
    :DOCUMENTATION
    "For char types the maximum number of bytes in the column."
    :ALLOCATION :INSTANCE :ACCESSOR %CHAR-OCTET-LENGTH)
   (ORDINAL-POSITION :TYPE CL:FIXNUM :INITFORM NULL-INTEGER
    :DOCUMENTATION "Index of column in table (starting at 1)."
    :ALLOCATION :INSTANCE :ACCESSOR %ORDINAL-POSITION)))

(CL:DEFUN NEW-COLUMN-INFO ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE COLUMN-INFO)))
   (CL:SETF (%ORDINAL-POSITION SELF) NULL-INTEGER)
   (CL:SETF (%CHAR-OCTET-LENGTH SELF) NULL-INTEGER)
   (CL:SETF (%SQL-DATETIME-SUB SELF) NULL-INTEGER)
   (CL:SETF (%SQL-DATA-TYPE SELF) NULL-INTEGER)
   (CL:SETF (%DEFAULT-VALUE SELF) STELLA::NULL-STRING)
   (CL:SETF (%DOCUMENTATION SELF) STELLA::NULL-STRING)
   (CL:SETF (%IS-NULLABLE? SELF) NULL) (CL:SETF (%NULLABLE? SELF) NULL)
   (CL:SETF (%RADIX SELF) NULL-INTEGER)
   (CL:SETF (%DECIMAL-DIGITS SELF) NULL-INTEGER)
   (CL:SETF (%BUFFER-LENGTH SELF) NULL-INTEGER)
   (CL:SETF (%COLUMN-SIZE SELF) NULL-INTEGER)
   (CL:SETF (%DATA-TYPE-NAME SELF) STELLA::NULL-STRING)
   (CL:SETF (%DATA-TYPE SELF) NULL-INTEGER)
   (CL:SETF (%NAME SELF) STELLA::NULL-STRING)
   (CL:SETF (%TABLE-NAME SELF) STELLA::NULL-STRING)
   (CL:SETF (%SCHEMA SELF) STELLA::NULL-STRING)
   (CL:SETF (%DATABASE SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF COLUMN-INFO))
  SGT-SDBC-SDBC-COLUMN-INFO)

(CL:DEFUN ACCESS-COLUMN-INFO-SLOT-VALUE (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-DATABASE)
    (CL:IF SETVALUE? (CL:SETF (%DATABASE SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%DATABASE SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-CATALOG)
    (CL:IF SETVALUE? (CL:SETF (%DATABASE SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%DATABASE SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-SCHEMA)
    (CL:IF SETVALUE? (CL:SETF (%SCHEMA SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%SCHEMA SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-STELLA-TABLE-NAME)
    (CL:IF SETVALUE?
     (CL:SETF (%TABLE-NAME SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%TABLE-NAME SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-STELLA-NAME)
    (CL:IF SETVALUE? (CL:SETF (%NAME SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%NAME SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-DATA-TYPE)
    (CL:IF SETVALUE? (CL:SETF (%DATA-TYPE SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-INTEGER (%DATA-TYPE SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-DATA-TYPE-NAME)
    (CL:IF SETVALUE?
     (CL:SETF (%DATA-TYPE-NAME SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%DATA-TYPE-NAME SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-COLUMN-SIZE)
    (CL:IF SETVALUE?
     (CL:SETF (%COLUMN-SIZE SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-INTEGER (%COLUMN-SIZE SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-BUFFER-LENGTH)
    (CL:IF SETVALUE?
     (CL:SETF (%BUFFER-LENGTH SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-INTEGER (%BUFFER-LENGTH SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-DECIMAL-DIGITS)
    (CL:IF SETVALUE?
     (CL:SETF (%DECIMAL-DIGITS SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-INTEGER (%DECIMAL-DIGITS SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-RADIX)
    (CL:IF SETVALUE? (CL:SETF (%RADIX SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-INTEGER (%RADIX SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-NULLABLE?)
    (CL:IF SETVALUE? (CL:SETF (%NULLABLE? SELF) VALUE)
     (CL:SETQ VALUE (%NULLABLE? SELF))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-IS-NULLABLE?)
    (CL:IF SETVALUE? (CL:SETF (%IS-NULLABLE? SELF) VALUE)
     (CL:SETQ VALUE (%IS-NULLABLE? SELF))))
   ((CL:EQ SLOTNAME SYM-SDBC-STELLA-DOCUMENTATION)
    (CL:IF SETVALUE?
     (CL:SETF (%DOCUMENTATION SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%DOCUMENTATION SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-REMARKS)
    (CL:IF SETVALUE?
     (CL:SETF (%DOCUMENTATION SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%DOCUMENTATION SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-STELLA-DEFAULT-VALUE)
    (CL:IF SETVALUE?
     (CL:SETF (%DEFAULT-VALUE SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%DEFAULT-VALUE SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-SQL-DATA-TYPE)
    (CL:IF SETVALUE?
     (CL:SETF (%SQL-DATA-TYPE SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-INTEGER (%SQL-DATA-TYPE SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-SQL-DATETIME-SUB)
    (CL:IF SETVALUE?
     (CL:SETF (%SQL-DATETIME-SUB SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-INTEGER (%SQL-DATETIME-SUB SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-CHAR-OCTET-LENGTH)
    (CL:IF SETVALUE?
     (CL:SETF (%CHAR-OCTET-LENGTH SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-INTEGER (%CHAR-OCTET-LENGTH SELF)))))
   ((CL:EQ SLOTNAME SYM-SDBC-SDBC-ORDINAL-POSITION)
    (CL:IF SETVALUE?
     (CL:SETF (%ORDINAL-POSITION SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-INTEGER (%ORDINAL-POSITION SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFUN (GET-TABLES (CONS OF TABLE-INFO)) ...)

(CL:DEFUN %GET-TABLES (CONNECTION CATALOG-NAME SCHEMA-NAME TABLE-NAME TABLE-TYPE)
  "Get the tables of the database identified by `connection'
and return the result as a list of objects containing all the relevant
meta information.  If any of the remaining arguments is supplied as
non-NULL, only tables whose corresponding field matches will be returned.
This is less general than what is supported by JDBC and ODBC, but Allegro
ODBC does not support filtering based on patterns, so we only do simple
manual filtering here."
  (CL:DECLARE
   (CL:TYPE CL:SIMPLE-STRING CATALOG-NAME SCHEMA-NAME TABLE-NAME
    TABLE-TYPE))
  #+MCL
  (CL:CHECK-TYPE CATALOG-NAME CL:SIMPLE-STRING)
  #+MCL
  (CL:CHECK-TYPE SCHEMA-NAME CL:SIMPLE-STRING)
  #+MCL
  (CL:CHECK-TYPE TABLE-NAME CL:SIMPLE-STRING)
  #+MCL
  (CL:CHECK-TYPE TABLE-TYPE CL:SIMPLE-STRING)
  (MAYBE-RENEW-CONNECTION CONNECTION)
  (CL:LET*
   ((NCON (%NATIVE-CONNECTION CONNECTION)) (RESULT-SET NULL)
    (RESULT-ITERATOR NULL)
    (FILTERTABLES?
     (CL:AND TRUE
      (CL:OR (CL:NOT (CL:EQ CATALOG-NAME STELLA::NULL-STRING))
       (CL:NOT (CL:EQ SCHEMA-NAME STELLA::NULL-STRING))
       (CL:NOT (CL:EQ TABLE-NAME STELLA::NULL-STRING))
       (CL:NOT (CL:EQ TABLE-TYPE STELLA::NULL-STRING)))))
    (TABLE-INFO NULL) (TABLES NIL))
   (CL:setq result-iterator
                      (allocate-iterator
                        (stellify-with-nil-to-null 
                          #+:EXCL (dbi:list-all-database-tables :db ncon)
                          #+:CLSQL (cl:append
                                    (cl:mapcar #'(cl:lambda (name) (cl:list nil nil name "TABLE"))
                                       (clsql:list-tables :database ncon :owner cl:nil))
                                    (cl:mapcar #'(cl:lambda (name) (cl:list nil nil name "VIEW"))
                                       (clsql:list-views :database ncon :owner cl:nil)))
                          #-(OR :EXCL :CLSQL) cl:nil)))
   (CL:WHEN (CL:EQ RESULT-ITERATOR NULL)
    (CL:LET* ((SELF-000 (NEW-RESULT-SET-ITERATOR)))
     (CL:SETF (%RESULT-SET SELF-000) RESULT-SET)
     (CL:SETQ RESULT-ITERATOR SELF-000)))
   (CL:LET* ((TABLE-ROW NULL) (ITER-000 RESULT-ITERATOR))
    (CL:LOOP WHILE (NEXT? ITER-000) DO
     (CL:SETQ TABLE-ROW (%VALUE ITER-000))
     (CL:TAGBODY
      (CL:WHEN
       (CL:AND FILTERTABLES?
        (CL:OR
         (CL:AND (CL:NOT (CL:EQ CATALOG-NAME STELLA::NULL-STRING))
          (CL:NOT (EQL-TO-STRING? (%%VALUE TABLE-ROW) CATALOG-NAME)))
         (CL:AND (CL:NOT (CL:EQ SCHEMA-NAME STELLA::NULL-STRING))
          (CL:NOT
           (EQL-TO-STRING? (%%VALUE (%%REST TABLE-ROW)) SCHEMA-NAME)))
         (CL:AND (CL:NOT (CL:EQ TABLE-NAME STELLA::NULL-STRING))
          (CL:NOT
           (EQL-TO-STRING? (%%VALUE (%%REST (%%REST TABLE-ROW)))
            TABLE-NAME)))
         (CL:AND (CL:NOT (CL:EQ TABLE-TYPE STELLA::NULL-STRING))
          (CL:NOT (EQL-TO-STRING? (FOURTH TABLE-ROW) TABLE-TYPE)))))
       (CL:GO :CONTINUE))
      (CL:LET* ((SELF-001 (NEW-TABLE-INFO)))
       (CL:SETF (%DATABASE SELF-001)
        (%WRAPPER-VALUE (%%VALUE TABLE-ROW)))
       (CL:SETF (%SCHEMA SELF-001)
        (%WRAPPER-VALUE (%%VALUE (%%REST TABLE-ROW))))
       (CL:SETF (%NAME SELF-001)
        (%WRAPPER-VALUE (%%VALUE (%%REST (%%REST TABLE-ROW)))))
       (CL:SETF (%TYPE SELF-001) (%WRAPPER-VALUE (FOURTH TABLE-ROW)))
       (CL:SETF (%REMARKS SELF-001) (%WRAPPER-VALUE (FIFTH TABLE-ROW)))
       (CL:SETQ TABLE-INFO SELF-001))
      (CL:WHEN (STRING-EQL? (%DATABASE TABLE-INFO) "")
       (CL:SETF (%DATABASE TABLE-INFO) STELLA::NULL-STRING))
      (CL:WHEN (STRING-EQL? (%SCHEMA TABLE-INFO) "")
       (CL:SETF (%SCHEMA TABLE-INFO) STELLA::NULL-STRING))
      (CL:SETQ TABLES (CONS TABLE-INFO TABLES)) :CONTINUE)))
   (REVERSE TABLES)))

(CL:DEFUN GET-TABLES-EVALUATOR-WRAPPER (ARGUMENTS)
  (%GET-TABLES (%%VALUE ARGUMENTS)
   (%WRAPPER-VALUE (%%VALUE (%%REST ARGUMENTS)))
   (%WRAPPER-VALUE (%%VALUE (%%REST (%%REST ARGUMENTS))))
   (%WRAPPER-VALUE (%%VALUE (%%REST (%%REST (%%REST ARGUMENTS)))))
   (%WRAPPER-VALUE
    (%%VALUE (%%REST (%%REST (%%REST (%%REST ARGUMENTS))))))))

(CL:DEFMACRO GET-TABLES (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Get the tables of the database identified by `connection'
and return the result as a list of objects containing all the relevant
meta information.  If any of the remaining arguments is supplied as
non-NULL, only tables whose corresponding field matches will be returned.
This is less general than what is supported by JDBC and ODBC, but Allegro
ODBC does not support filtering based on patterns, so we only do simple
manual filtering here."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/SDBC/GET-TABLES|)) (CL:MACRO-FUNCTION (CL:QUOTE GET-TABLES)))

;;; (DEFUN (GET-COLUMNS (CONS OF COLUMN-INFO)) ...)

(CL:DEFUN %GET-COLUMNS (CONNECTION CATALOGNAME SCHEMANAME TABLENAME COLUMNNAME)
  (CL:DECLARE
   (CL:TYPE CL:SIMPLE-STRING CATALOGNAME SCHEMANAME TABLENAME
    COLUMNNAME))
  #+MCL
  (CL:CHECK-TYPE CATALOGNAME CL:SIMPLE-STRING)
  #+MCL
  (CL:CHECK-TYPE SCHEMANAME CL:SIMPLE-STRING)
  #+MCL
  (CL:CHECK-TYPE TABLENAME CL:SIMPLE-STRING)
  #+MCL
  (CL:CHECK-TYPE COLUMNNAME CL:SIMPLE-STRING)
  (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "FINISH ME")
  NULL)

(CL:DEFUN GET-COLUMNS-EVALUATOR-WRAPPER (ARGUMENTS)
  (%GET-COLUMNS (%%VALUE ARGUMENTS)
   (%WRAPPER-VALUE (%%VALUE (%%REST ARGUMENTS)))
   (%WRAPPER-VALUE (%%VALUE (%%REST (%%REST ARGUMENTS))))
   (%WRAPPER-VALUE (%%VALUE (%%REST (%%REST (%%REST ARGUMENTS)))))
   (%WRAPPER-VALUE
    (%%VALUE (%%REST (%%REST (%%REST (%%REST ARGUMENTS))))))))

(CL:DEFMACRO GET-COLUMNS (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/SDBC/GET-COLUMNS|)) (CL:MACRO-FUNCTION (CL:QUOTE GET-COLUMNS)))

;;; (DEFUN (GET-SERVER-INFO WRAPPER) ...)

(CL:DEFUN %GET-SERVER-INFO (CONNECTION PROPERTY)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING PROPERTY))
  #+MCL
  (CL:CHECK-TYPE PROPERTY CL:SIMPLE-STRING)
  (CL:LET* ((NCON (%NATIVE-CONNECTION CONNECTION)))
   (CL:LET* ((TEST-VALUE-000 (%PROTOCOL CONNECTION)))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TEST-VALUE-000))
    (CL:COND ((STRING-EQL? TEST-VALUE-000 "ODBC"))
     ((STRING-EQL? TEST-VALUE-000 "JDBC")) (CL:T)))
   (CL:LET* ((TEST-VALUE-001 (STRING-UPCASE PROPERTY)))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TEST-VALUE-001))
    (CL:COND
     ((STRING-EQL? TEST-VALUE-001 "DBMS-NAME")
      (CL:RETURN-FROM %GET-SERVER-INFO
       (WRAP-STRING (GUESS-DBMS-NAME CONNECTION))))
     ((STRING-EQL? TEST-VALUE-001 "DBMS-VERSION")
      (CL:LET* ((TEST-VALUE-002 (GET-DBMS-NAME CONNECTION)))
       (CL:COND
        ((CL:EQ TEST-VALUE-002 KWD-SDBC-MYSQL)
         (CL:RETURN-FROM %GET-SERVER-INFO
          (CONS-TREE-NTH
           (%EXECUTE-SQL CONNECTION (WRAP-STRING "select version()")
            NIL)
           0 0)))
        ((CL:EQ TEST-VALUE-002 KWD-SDBC-ORACLE)
         (CL:RETURN-FROM %GET-SERVER-INFO
          (CONS-TREE-NTH
           (%EXECUTE-SQL CONNECTION
            (WRAP-STRING
             "select * from v$version where banner like 'Oracle%'")
            NIL)
           0 0)))
        (CL:T))))
     (CL:T)))
   NULL))

(CL:DEFUN GET-SERVER-INFO-EVALUATOR-WRAPPER (ARGUMENTS)
  (%GET-SERVER-INFO (%%VALUE ARGUMENTS)
   (%WRAPPER-VALUE (%%VALUE (%%REST ARGUMENTS)))))

(CL:DEFMACRO GET-SERVER-INFO (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/SDBC/GET-SERVER-INFO|)) (CL:MACRO-FUNCTION (CL:QUOTE GET-SERVER-INFO)))

;;; (DEFUN (GUESS-DBMS-NAME STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T) CL:SIMPLE-STRING) GUESS-DBMS-NAME))
(CL:DEFUN GUESS-DBMS-NAME (CONNECTION)
  (CL:LET*
   ((DBMSNAME STELLA::NULL-STRING)
    (NCON (%NATIVE-CONNECTION CONNECTION)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING DBMSNAME))
   #+:CLSQL (cl:return-from guess-dbms-name (cl:symbol-name (clsql:database-type ncon)))
   (CL:HANDLER-CASE
    (CL:PROGN
     (%EXECUTE-SQL CONNECTION
      (WRAP-STRING "select @@myisam_max_sort_file_size") NIL)
     (CL:SETQ DBMSNAME "MySQL"))
    (DATABASE-EXCEPTION ()))
   (CL:WHEN (CL:EQ DBMSNAME STELLA::NULL-STRING)
    (CL:HANDLER-CASE
     (CL:PROGN
      (%EXECUTE-SQL CONNECTION (WRAP-STRING "select 1 from dual") NIL)
      (CL:SETQ DBMSNAME "Oracle"))
     (DATABASE-EXCEPTION ())))
   DBMSNAME))

;;; (DEFUN (GET-DBMS-NAME KEYWORD) ...)

(CL:DEFUN GET-DBMS-NAME (CONNECTION)
  (CL:LET* ((CACHEDDBMSNAME (%DBMS-NAME CONNECTION)) (DBMSNAME NULL))
   (CL:WHEN (CL:NOT (CL:EQ CACHEDDBMSNAME NULL))
    (CL:RETURN-FROM GET-DBMS-NAME CACHEDDBMSNAME))
   (CL:HANDLER-CASE
    (CL:SETQ DBMSNAME (%GET-SERVER-INFO CONNECTION "DBMS-NAME"))
    (STELLA-EXCEPTION ()))
   (CL:IF (CL:NOT (CL:EQ DBMSNAME NULL))
    (CL:SETQ CACHEDDBMSNAME
     (INTERN-KEYWORD (STRING-UPCASE (%WRAPPER-VALUE DBMSNAME))))
    (CL:SETQ CACHEDDBMSNAME (INTERN-KEYWORD "UNKNOWN")))
   (CL:SETF (%DBMS-NAME CONNECTION) CACHEDDBMSNAME) CACHEDDBMSNAME))

;;; (DEFUN PRINT-TABLE ...)

(CL:DEFUN PRINT-TABLE (TABLE)
  (CL:WHEN (CL:EQ TABLE NULL) (CL:RETURN-FROM PRINT-TABLE))
  (CL:LET* ((CONSTABLE TABLE))
   (CL:LET* ((ROW NULL) (ITER-000 CONSTABLE))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ ROW (%%VALUE ITER-000))
     (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "row = " ROW EOL)
     (CL:SETQ ITER-000 (%%REST ITER-000))))))

;;; (DEFUN (CALENDAR-DATE-TO-SQL-STRING STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T) CL:SIMPLE-STRING)
  CALENDAR-DATE-TO-SQL-STRING))
(CL:DEFUN CALENDAR-DATE-TO-SQL-STRING (DATE)
  (CALENDAR-DATE-TO-STRING DATE 0.0d0 CL:T CL:NIL))

;;; (DEFSPECIAL *SQL-COMMAND-TEMPLATES* ...)

(CL:DEFVAR *SQL-COMMAND-TEMPLATES* NULL)

;;; (DEFUN LOAD-SQL-CMD-TEMPLATES ...)

(CL:DEFUN LOAD-SQL-CMD-TEMPLATES (FILE)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING FILE))
  #+MCL
  (CL:CHECK-TYPE FILE CL:SIMPLE-STRING)
  (CL:LET* ((IN NULL))
   (CL:UNWIND-PROTECT
    (CL:PROGN (CL:SETQ IN (OPEN-INPUT-FILE FILE))
     (CL:LET* ((COMMAND NULL) (ITER-000 (S-EXPRESSIONS IN)))
      (CL:LOOP WHILE (NEXT? ITER-000) DO
       (CL:SETQ COMMAND (%VALUE ITER-000))
       (CL:LET* ((SELF-000 (NEW-PROPERTY-LIST)))
        (CL:SETF (%THE-PLIST SELF-000) COMMAND)
        (INSERT-SQL-COMMAND-TEMPLATE SELF-000)))))
    (CL:WHEN (CL:NOT (CL:EQ IN NULL)) (FREE IN)))))

;;; (DEFUN INSERT-SQL-COMMAND-TEMPLATE ...)

(CL:DEFUN INSERT-SQL-COMMAND-TEMPLATE (TEMPLATE)
  (CL:LET* ((COMMANDNAME (LOOKUP TEMPLATE KWD-SDBC-COMMAND)))
   (CL:LET* ((TEMP-000 (LOOKUP TEMPLATE KWD-SDBC-DATA-SOURCE)))
    (CL:LET*
     ((DATASOURCES
       (CONSIFY
        (CL:IF (CL:NOT (CL:EQ TEMP-000 NULL)) TEMP-000
         KWD-SDBC-DEFAULT)))
      (SQL (LOOKUP TEMPLATE KWD-SDBC-SQL))
      (TEMPLATES (LOOKUP *SQL-COMMAND-TEMPLATES* COMMANDNAME)))
     (CL:WHEN (CL:EQ COMMANDNAME NULL)
      (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
       (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
        "Missing :command name in SQL template: `" TEMPLATE "'")
       (CL:ERROR
        (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000)))))
     (CL:WHEN (CL:NOT (STRING? SQL))
      (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
       (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001)
        "Illegal or missing :sql specification in SQL template: `" SQL
        "'" EOL "   String expected.")
       (CL:ERROR
        (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-001)))))
     (CL:WHEN (CL:EQ TEMPLATES NULL)
      (CL:SETQ TEMPLATES (NEW-KEY-VALUE-LIST))
      (INSERT-AT *SQL-COMMAND-TEMPLATES* COMMANDNAME TEMPLATES))
     (CL:LET* ((DATASOURCE NULL) (ITER-000 DATASOURCES))
      (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
       (CL:SETQ DATASOURCE (%%VALUE ITER-000))
       (CL:WHEN (CL:EQ DATASOURCE KWD-SDBC-OTHERWISE)
        (CL:SETQ DATASOURCE KWD-SDBC-DEFAULT))
       (INSERT-AT TEMPLATES DATASOURCE TEMPLATE)
       (CL:SETQ ITER-000 (%%REST ITER-000))))))))

;;; (DEFUN (LOOKUP-SQL-CMD-TEMPLATE PROPERTY-LIST) ...)

(CL:DEFUN LOOKUP-SQL-CMD-TEMPLATE (COMMANDNAME DATASOURCE)
  (CL:LET*
   ((TEMPLATES (LOOKUP *SQL-COMMAND-TEMPLATES* COMMANDNAME))
    (TEMPLATE NULL))
   (CL:WHEN (CL:EQ TEMPLATES NULL)
    (CL:RETURN-FROM LOOKUP-SQL-CMD-TEMPLATE NULL))
   (CL:SETQ TEMPLATE
    (LOOKUP TEMPLATES
     (CL:IF (CL:NOT (CL:EQ DATASOURCE NULL)) DATASOURCE
      KWD-SDBC-DEFAULT)))
   (CL:IF (CL:EQ TEMPLATE NULL) (LOOKUP TEMPLATES KWD-SDBC-DEFAULT)
    TEMPLATE)))

;;; (DEFUN (INSTANTIATE-SQL-CMD STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T CL:T CL:&REST CL:T) CL:SIMPLE-STRING)
  INSTANTIATE-SQL-CMD))
(CL:DEFUN INSTANTIATE-SQL-CMD (CMDNAME DATASOURCE CL:&REST |VARS&VALUES|)
  (CL:LET*
   ((TEMPLATE (LOOKUP-SQL-CMD-TEMPLATE CMDNAME DATASOURCE))
    (VARIABLES (NEW-KEY-VALUE-LIST)) (KEY NULL))
   (CL:WHEN (CL:EQ TEMPLATE NULL)
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
      "Undefined SQL command template: `" CMDNAME "'")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000)))))
   (CL:LET* ((ITEM STELLA::NULL-STRING) (ITER-000 |VARS&VALUES|))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING ITEM))
    (CL:LOOP WHILE ITER-000 DO (CL:SETQ ITEM (CL:POP ITER-000))
     (CL:COND
      ((CL:NOT (CL:EQ KEY NULL))
       (INSERT-AT VARIABLES KEY
        (CL:IF (CL:EQ ITEM STELLA::NULL-STRING) NULL
         (WRAP-STRING ITEM)))
       (CL:SETQ KEY NULL))
      (CL:T (CL:SETQ KEY (WRAP-STRING ITEM))))))
   (INSTANTIATE-SQL-CMD-TEMPLATE
    (%WRAPPER-VALUE (LOOKUP TEMPLATE KWD-SDBC-SQL)) VARIABLES)))

;;; (DEFGLOBAL *SQL-CMD-TEMPLATE-VARIABLE-PREFIX* ...)

(CL:DEFVAR *SQL-CMD-TEMPLATE-VARIABLE-PREFIX* "#$")
(CL:DECLAIM
 (CL:TYPE CL:SIMPLE-STRING *SQL-CMD-TEMPLATE-VARIABLE-PREFIX*))

;;; (DEFUN (INSTANTIATE-SQL-CMD-TEMPLATE STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:SIMPLE-STRING CL:T) CL:SIMPLE-STRING)
  INSTANTIATE-SQL-CMD-TEMPLATE))
(CL:DEFUN INSTANTIATE-SQL-CMD-TEMPLATE (TEMPLATE VARIABLES)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TEMPLATE))
  #+MCL
  (CL:CHECK-TYPE TEMPLATE CL:SIMPLE-STRING)
  (CL:LET*
   ((PREFIX *SQL-CMD-TEMPLATE-VARIABLE-PREFIX*)
    (PREFIXLENGTH (CL:THE CL:FIXNUM (CL:LENGTH PREFIX))) (CURSOR 0)
    (VARIABLESTART 0) (LENGTH (CL:THE CL:FIXNUM (CL:LENGTH TEMPLATE)))
    (RESULT NULL) (VARIABLE STELLA::NULL-STRING))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING PREFIX VARIABLE)
    (CL:TYPE CL:FIXNUM PREFIXLENGTH CURSOR VARIABLESTART LENGTH))
   (CL:WHEN
    (CL:= (STRING-SEARCH TEMPLATE PREFIX NULL-INTEGER) NULL-INTEGER)
    (CL:RETURN-FROM INSTANTIATE-SQL-CMD-TEMPLATE TEMPLATE))
   (CL:SETQ RESULT (NEW-OUTPUT-STRING-STREAM))
   (CL:LOOP
    (CL:SETQ VARIABLESTART (STRING-SEARCH TEMPLATE PREFIX CURSOR))
    (%%PRINT-STREAM (%NATIVE-STREAM RESULT)
     (SUBSEQUENCE TEMPLATE CURSOR VARIABLESTART))
    (CL:WHEN (CL:= VARIABLESTART NULL-INTEGER) (CL:RETURN))
    (CL:MULTIPLE-VALUE-SETQ (VARIABLE CURSOR)
     (READ-SQL-CMD-TEMPLATE-VARIABLE TEMPLATE
      (CL:+ VARIABLESTART PREFIXLENGTH) LENGTH))
    (%%PRINT-STREAM (%NATIVE-STREAM RESULT)
     (INSTANTIATE-SQL-CMD-TEMPLATE-VARIABLE VARIABLE VARIABLES)))
   (THE-STRING-READER RESULT)))

;;; (DEFUN (READ-SQL-CMD-TEMPLATE-VARIABLE STRING INTEGER) ...)

(CL:DECLAIM
 (CL:FTYPE
  (CL:FUNCTION (CL:SIMPLE-STRING CL:FIXNUM CL:FIXNUM)
   (CL:VALUES CL:SIMPLE-STRING CL:FIXNUM))
  READ-SQL-CMD-TEMPLATE-VARIABLE))
(CL:DEFUN READ-SQL-CMD-TEMPLATE-VARIABLE (TEMPLATE START END)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TEMPLATE)
   (CL:TYPE CL:FIXNUM START END))
  #+MCL
  (CL:CHECK-TYPE TEMPLATE CL:SIMPLE-STRING)
  #+MCL
  (CL:CHECK-TYPE START CL:FIXNUM)
  #+MCL
  (CL:CHECK-TYPE END CL:FIXNUM)
  (CL:LET* ((CURSOR START) (ESCAPED? CL:NIL))
   (CL:DECLARE (CL:TYPE CL:FIXNUM CURSOR))
   (CL:COND
    ((CL:OR (CL:>= CURSOR END)
      (CL:NOT
       (CL:EQL
        (CL:LET ((SELF TEMPLATE) (POSITION CURSOR))
         (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
          (CL:TYPE CL:FIXNUM POSITION))
         (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
          (CL:THE CL:FIXNUM POSITION)))
        #\{))))
    (CL:T
     (CL:LOOP WHILE (CL:< CURSOR END) DO
      (CL:LET*
       ((C
         (CL:LET ((SELF TEMPLATE) (POSITION CURSOR))
          (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
           (CL:TYPE CL:FIXNUM POSITION))
          (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
           (CL:THE CL:FIXNUM POSITION)))))
       (CL:COND
        ((CL:EQL C #\\) (CL:SETQ ESCAPED? CL:T)
         (CL:SETQ CURSOR (CL:1+ CURSOR)))
        ((CL:EQL C #\}) (CL:RETURN)) (CL:T))
       (CL:SETQ CURSOR (CL:1+ CURSOR))))
     (CL:WHEN (CL:< CURSOR END)
      (CL:IF ESCAPED?
       (CL:RETURN-FROM READ-SQL-CMD-TEMPLATE-VARIABLE
        (CL:VALUES
         (UNESCAPE-TOKEN-STRING
          (SUBSEQUENCE TEMPLATE (CL:1+ START) CURSOR) #\\ CL:NIL)
         (CL:1+ CURSOR)))
       (CL:RETURN-FROM READ-SQL-CMD-TEMPLATE-VARIABLE
        (CL:VALUES (SUBSEQUENCE TEMPLATE (CL:1+ START) CURSOR)
         (CL:1+ CURSOR)))))))
   (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
    (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
     "Illegal template variable syntax at position `" CURSOR "' in" EOL
     EOL "    `" TEMPLATE "'")
    (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))

;;; (DEFUN (INSTANTIATE-SQL-CMD-TEMPLATE-VARIABLE STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:SIMPLE-STRING CL:T) CL:SIMPLE-STRING)
  INSTANTIATE-SQL-CMD-TEMPLATE-VARIABLE))
(CL:DEFUN INSTANTIATE-SQL-CMD-TEMPLATE-VARIABLE (TEMPLATEVARIABLE VARIABLES)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TEMPLATEVARIABLE))
  #+MCL
  (CL:CHECK-TYPE TEMPLATEVARIABLE CL:SIMPLE-STRING)
  (CL:LET* ((START 0) (QUOTES "'`\"") (QUOTE NULL-CHARACTER))
   (CL:DECLARE (CL:TYPE CL:FIXNUM START)
    (CL:TYPE CL:SIMPLE-STRING QUOTES))
   (CL:LET*
    ((VAR NULL) (VALUE NULL) (ITER-000 (%THE-KV-LIST VARIABLES)))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NULL)) DO
     (CL:SETQ VAR (%KEY ITER-000)) (CL:SETQ VALUE (%VALUE ITER-000))
     (CL:SETQ START
      (STRING-SEARCH TEMPLATEVARIABLE (%WRAPPER-VALUE VAR) 0))
     (CL:WHEN (CL:NOT (CL:= START NULL-INTEGER))
      (CL:LET*
       ((VARSPEC STELLA::NULL-STRING) (FROM NULL-INTEGER)
        (TO NULL-INTEGER) (DEFAULT STELLA::NULL-STRING))
       (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING VARSPEC DEFAULT)
        (CL:TYPE CL:FIXNUM FROM TO))
       (CL:MULTIPLE-VALUE-SETQ (VARSPEC FROM TO DEFAULT)
        (PARSE-SQL-CMD-TEMPLATE-VARIABLE-RANGE-AND-DEFAULT
         TEMPLATEVARIABLE (%WRAPPER-VALUE VAR) START))
       (CL:WHEN
        (CL:AND (CL:> START 0)
         (MEMBER? QUOTES
          (CL:LET ((SELF TEMPLATEVARIABLE) (POSITION (CL:1- START)))
           (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
            (CL:TYPE CL:FIXNUM POSITION))
           (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
            (CL:THE CL:FIXNUM POSITION)))))
        (CL:SETQ QUOTE
         (CL:LET ((SELF TEMPLATEVARIABLE) (POSITION (CL:1- START)))
          (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
           (CL:TYPE CL:FIXNUM POSITION))
          (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
           (CL:THE CL:FIXNUM POSITION)))))
       (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE VALUE)))
        (CL:COND
         ((SUBTYPE-OF-STRING? TEST-VALUE-000)
          (CL:PROGN
           (CL:WHEN
            (CL:OR (CL:EQ (UNWRAP-STRING VALUE) STELLA::NULL-STRING)
             (CL:> FROM 0))
            (CL:RETURN-FROM INSTANTIATE-SQL-CMD-TEMPLATE-VARIABLE
             DEFAULT))
           (CL:WHEN (DEFINED? QUOTE)
            (CL:SETQ VALUE
             (WRAP-STRING
              (SQL-ESCAPE-STRING (%WRAPPER-VALUE VALUE) QUOTE))))
           (CL:RETURN-FROM INSTANTIATE-SQL-CMD-TEMPLATE-VARIABLE
            (REPLACE-SUBSTRINGS TEMPLATEVARIABLE (%WRAPPER-VALUE VALUE)
             VARSPEC))))
         ((CL:EQ TEST-VALUE-000 SGT-SDBC-STELLA-CONS)
          (CL:PROGN
           (CL:IF (CL:OR (CL:EQ VALUE NIL) (CL:>= FROM (LENGTH VALUE)))
            (CL:RETURN-FROM INSTANTIATE-SQL-CMD-TEMPLATE-VARIABLE
             DEFAULT)
            (CL:LET* ((RESULT (NEW-OUTPUT-STRING-STREAM)))
             (CL:LET*
              ((ELT NULL) (ITER-001 VALUE) (I NULL-INTEGER)
               (ITER-002 0))
              (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-002))
              (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
               (CL:SETQ ELT (%%VALUE ITER-001)) (CL:SETQ I ITER-002)
               (CL:WHEN
                (CL:AND (CL:>= I FROM)
                 (CL:OR (CL:= TO NULL-INTEGER) (CL:<= I TO)))
                (CL:WHEN (DEFINED? QUOTE)
                 (CL:SETQ ELT
                  (WRAP-STRING
                   (SQL-ESCAPE-STRING (%WRAPPER-VALUE ELT) QUOTE))))
                (%%PRINT-STREAM (%NATIVE-STREAM RESULT)
                 (REPLACE-SUBSTRINGS TEMPLATEVARIABLE
                  (%WRAPPER-VALUE ELT) VARSPEC)))
               (CL:SETQ ITER-001 (%%REST ITER-001))
               (CL:SETQ ITER-002 (CL:1+ ITER-002))))
             (CL:RETURN-FROM INSTANTIATE-SQL-CMD-TEMPLATE-VARIABLE
              (THE-STRING-READER RESULT))))))
         (CL:T
          (CL:RETURN-FROM INSTANTIATE-SQL-CMD-TEMPLATE-VARIABLE
           DEFAULT))))))
     (CL:SETQ ITER-000 (%REST ITER-000))))
   (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
    (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
     "Undefined template variable: `" TEMPLATEVARIABLE "'")
    (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))

;;; (DEFUN (PARSE-SQL-CMD-TEMPLATE-VARIABLE-RANGE-AND-DEFAULT STRING INTEGER INTEGER STRING) ...)

(CL:DECLAIM
 (CL:FTYPE
  (CL:FUNCTION (CL:SIMPLE-STRING CL:SIMPLE-STRING CL:FIXNUM)
   (CL:VALUES CL:SIMPLE-STRING CL:FIXNUM CL:FIXNUM CL:SIMPLE-STRING))
  PARSE-SQL-CMD-TEMPLATE-VARIABLE-RANGE-AND-DEFAULT))
(CL:DEFUN PARSE-SQL-CMD-TEMPLATE-VARIABLE-RANGE-AND-DEFAULT (TEMPLATEVARIABLE VARIABLENAME START)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TEMPLATEVARIABLE VARIABLENAME)
   (CL:TYPE CL:FIXNUM START))
  #+MCL
  (CL:CHECK-TYPE TEMPLATEVARIABLE CL:SIMPLE-STRING)
  #+MCL
  (CL:CHECK-TYPE VARIABLENAME CL:SIMPLE-STRING)
  #+MCL
  (CL:CHECK-TYPE START CL:FIXNUM)
  (CL:LET*
   ((VARIABLESTART START)
    (END (CL:THE CL:FIXNUM (CL:LENGTH TEMPLATEVARIABLE))) (STARTIDX 0)
    (ENDIDX 0) (DEFAULT "1=1") (CURSOR 0) (RANGE NIL)
    (ELEMENT STELLA::NULL-STRING) (NOFELEMENTS 0))
   (CL:DECLARE
    (CL:TYPE CL:FIXNUM VARIABLESTART END STARTIDX ENDIDX CURSOR
     NOFELEMENTS)
    (CL:TYPE CL:SIMPLE-STRING DEFAULT ELEMENT))
   (CL:SETQ START
    (CL:+ START (CL:THE CL:FIXNUM (CL:LENGTH VARIABLENAME))))
   (CL:WHEN
    (CL:OR (CL:>= START END)
     (CL:NOT
      (CL:EQL
       (CL:LET ((SELF TEMPLATEVARIABLE) (POSITION START))
        (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
         (CL:TYPE CL:FIXNUM POSITION))
        (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
         (CL:THE CL:FIXNUM POSITION)))
       #\[)))
    (CL:RETURN-FROM PARSE-SQL-CMD-TEMPLATE-VARIABLE-RANGE-AND-DEFAULT
     (CL:VALUES VARIABLENAME STARTIDX ENDIDX DEFAULT)))
   (CL:SETQ START (CL:1+ START))
   (CL:SETQ END (POSITION TEMPLATEVARIABLE #\] START))
   (CL:WHEN (CL:= END NULL-INTEGER)
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
      "Missing right parenthesis in template variable range: `"
      TEMPLATEVARIABLE "'")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000)))))
   (CL:SETQ CURSOR START)
   (CL:LOOP WHILE (CL:< CURSOR END) DO
    (CL:COND
     ((CL:AND
       (CL:EQL
        (CL:LET ((SELF TEMPLATEVARIABLE) (POSITION CURSOR))
         (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
          (CL:TYPE CL:FIXNUM POSITION))
         (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
          (CL:THE CL:FIXNUM POSITION)))
        #\,)
       (CL:< NOFELEMENTS 2))
      (CL:SETQ RANGE
       (CONS (WRAP-STRING (SUBSEQUENCE TEMPLATEVARIABLE START CURSOR))
        RANGE))
      (CL:SETQ NOFELEMENTS (CL:1+ NOFELEMENTS))
      (CL:SETQ CURSOR (CL:1+ CURSOR)) (CL:SETQ START CURSOR))
     (CL:T (CL:SETQ CURSOR (CL:1+ CURSOR)))))
   (CL:SETQ NOFELEMENTS (CL:1+ NOFELEMENTS))
   (CL:SETQ RANGE
    (CONS (WRAP-STRING (SUBSEQUENCE TEMPLATEVARIABLE START CURSOR))
     RANGE))
   (CL:LET*
    ((ELT NULL) (ITER-000 (REVERSE RANGE)) (I NULL-INTEGER)
     (ITER-001 1))
    (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-001))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ ELT (%%VALUE ITER-000)) (CL:SETQ I ITER-001)
     (CL:SETQ ELEMENT (%WRAPPER-VALUE ELT))
     (CL:ECASE I
      (1
       (CL:IF (CL:= I NOFELEMENTS)
        (CL:PROGN
         (CL:IF (STRING-EQL? ELEMENT "")
          (CL:PROGN (CL:SETQ DEFAULT ELEMENT))
          (CL:LET* ((ALWAYS?-000 CL:T))
           (CL:LET*
            ((CHAR NULL-CHARACTER) (VECTOR-000 ELEMENT) (INDEX-000 0)
             (LENGTH-000 (CL:THE CL:FIXNUM (CL:LENGTH VECTOR-000))))
            (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING VECTOR-000)
             (CL:TYPE CL:FIXNUM INDEX-000 LENGTH-000))
            (CL:LOOP WHILE (CL:< INDEX-000 LENGTH-000) DO
             (CL:SETQ CHAR
              (CL:LET ((SELF VECTOR-000) (POSITION INDEX-000))
               (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
                (CL:TYPE CL:FIXNUM POSITION))
               (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
                (CL:THE CL:FIXNUM POSITION))))
             (CL:WHEN
              (CL:NOT
               (CL:EQ
                (CL:AREF *CHARACTER-TYPE-TABLE*
                 (CL:THE CL:FIXNUM (CL:CHAR-CODE CHAR)))
                KWD-SDBC-DIGIT))
              (CL:SETQ ALWAYS?-000 CL:NIL) (CL:RETURN))
             (CL:SETQ INDEX-000 (CL:1+ INDEX-000))))
           (CL:IF ALWAYS?-000
            (CL:PROGN
             (CL:SETQ STARTIDX
              (CL:TRUNCATE (STRING-TO-INTEGER ELEMENT)))
             (CL:SETQ ENDIDX STARTIDX))
            (CL:PROGN (CL:SETQ DEFAULT ELEMENT))))))
        (CL:LET* ((ALWAYS?-001 CL:T))
         (CL:LET*
          ((CHAR NULL-CHARACTER) (VECTOR-001 ELEMENT) (INDEX-001 0)
           (LENGTH-001 (CL:THE CL:FIXNUM (CL:LENGTH VECTOR-001))))
          (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING VECTOR-001)
           (CL:TYPE CL:FIXNUM INDEX-001 LENGTH-001))
          (CL:LOOP WHILE (CL:< INDEX-001 LENGTH-001) DO
           (CL:SETQ CHAR
            (CL:LET ((SELF VECTOR-001) (POSITION INDEX-001))
             (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
              (CL:TYPE CL:FIXNUM POSITION))
             (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
              (CL:THE CL:FIXNUM POSITION))))
           (CL:WHEN
            (CL:NOT
             (CL:EQ
              (CL:AREF *CHARACTER-TYPE-TABLE*
               (CL:THE CL:FIXNUM (CL:CHAR-CODE CHAR)))
              KWD-SDBC-DIGIT))
            (CL:SETQ ALWAYS?-001 CL:NIL) (CL:RETURN))
           (CL:SETQ INDEX-001 (CL:1+ INDEX-001))))
         (CL:IF ALWAYS?-001
          (CL:PROGN
           (CL:SETQ STARTIDX (CL:TRUNCATE (STRING-TO-INTEGER ELEMENT)))
           (CL:SETQ ENDIDX STARTIDX))
          (CL:PROGN
           (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
            (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001)
             "Illegal template variable range: `" TEMPLATEVARIABLE "'")
            (CL:ERROR
             (NEW-STELLA-EXCEPTION
              (THE-STRING-READER STREAM-001)))))))))
      (2
       (CL:IF (CL:= I NOFELEMENTS)
        (CL:PROGN
         (CL:IF (STRING-EQL? ELEMENT "")
          (CL:PROGN (CL:SETQ DEFAULT ELEMENT))
          (CL:IF (STRING-EQL? ELEMENT ":")
           (CL:PROGN (CL:SETQ ENDIDX NULL-INTEGER))
           (CL:LET* ((ALWAYS?-002 CL:T))
            (CL:LET*
             ((CHAR NULL-CHARACTER) (VECTOR-002 ELEMENT) (INDEX-002 0)
              (LENGTH-002 (CL:THE CL:FIXNUM (CL:LENGTH VECTOR-002))))
             (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING VECTOR-002)
              (CL:TYPE CL:FIXNUM INDEX-002 LENGTH-002))
             (CL:LOOP WHILE (CL:< INDEX-002 LENGTH-002) DO
              (CL:SETQ CHAR
               (CL:LET ((SELF VECTOR-002) (POSITION INDEX-002))
                (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
                 (CL:TYPE CL:FIXNUM POSITION))
                (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
                 (CL:THE CL:FIXNUM POSITION))))
              (CL:WHEN
               (CL:NOT
                (CL:EQ
                 (CL:AREF *CHARACTER-TYPE-TABLE*
                  (CL:THE CL:FIXNUM (CL:CHAR-CODE CHAR)))
                 KWD-SDBC-DIGIT))
               (CL:SETQ ALWAYS?-002 CL:NIL) (CL:RETURN))
              (CL:SETQ INDEX-002 (CL:1+ INDEX-002))))
            (CL:IF ALWAYS?-002
             (CL:PROGN
              (CL:SETQ ENDIDX
               (CL:TRUNCATE (STRING-TO-INTEGER ELEMENT))))
             (CL:PROGN (CL:SETQ DEFAULT ELEMENT)))))))
        (CL:IF (STRING-EQL? ELEMENT "")
         (CL:PROGN (CL:SETQ ENDIDX STARTIDX))
         (CL:IF (STRING-EQL? ELEMENT ":")
          (CL:PROGN (CL:SETQ ENDIDX NULL-INTEGER))
          (CL:LET* ((ALWAYS?-003 CL:T))
           (CL:LET*
            ((CHAR NULL-CHARACTER) (VECTOR-003 ELEMENT) (INDEX-003 0)
             (LENGTH-003 (CL:THE CL:FIXNUM (CL:LENGTH VECTOR-003))))
            (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING VECTOR-003)
             (CL:TYPE CL:FIXNUM INDEX-003 LENGTH-003))
            (CL:LOOP WHILE (CL:< INDEX-003 LENGTH-003) DO
             (CL:SETQ CHAR
              (CL:LET ((SELF VECTOR-003) (POSITION INDEX-003))
               (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
                (CL:TYPE CL:FIXNUM POSITION))
               (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
                (CL:THE CL:FIXNUM POSITION))))
             (CL:WHEN
              (CL:NOT
               (CL:EQ
                (CL:AREF *CHARACTER-TYPE-TABLE*
                 (CL:THE CL:FIXNUM (CL:CHAR-CODE CHAR)))
                KWD-SDBC-DIGIT))
              (CL:SETQ ALWAYS?-003 CL:NIL) (CL:RETURN))
             (CL:SETQ INDEX-003 (CL:1+ INDEX-003))))
           (CL:IF ALWAYS?-003
            (CL:PROGN
             (CL:SETQ ENDIDX
              (CL:TRUNCATE (STRING-TO-INTEGER ELEMENT))))
            (CL:PROGN
             (CL:LET* ((STREAM-002 (NEW-OUTPUT-STRING-STREAM)))
              (%%PRINT-STREAM (%NATIVE-STREAM STREAM-002)
               "Illegal template variable range: `" TEMPLATEVARIABLE
               "'")
              (CL:ERROR
               (NEW-STELLA-EXCEPTION
                (THE-STRING-READER STREAM-002)))))))))))
      (3 (CL:SETQ DEFAULT ELEMENT)))
     (CL:SETQ ITER-000 (%%REST ITER-000))
     (CL:SETQ ITER-001 (CL:1+ ITER-001))))
   (CL:VALUES (SUBSEQUENCE TEMPLATEVARIABLE VARIABLESTART (CL:1+ END))
    STARTIDX ENDIDX DEFAULT)))

;;; (DEFUN TEST-PREPARED-STATEMENT ...)

(CL:DEFUN TEST-PREPARED-STATEMENT ()
  (CL:HANDLER-CASE
   (CL:LET*
    ((CON
      (%CONNECT
       (CONS-LIST KWD-SDBC-DSN (WRAP-STRING "myodbc3") KWD-SDBC-USER
        (WRAP-STRING "scott") KWD-SDBC-PASSWORD (WRAP-STRING "tiger")
        KWD-SDBC-CONNECTIONSTRING
        (WRAP-STRING
         "jdbc:mysql://localhost:3306/menagerie?user=scott&password=tiger"))))
     (PREPAREDSQL "insert into customer4 values (?, ?, ?, ?)")
     (SELECTSQL "select * from customer4") (PREPAREDSTATEMENT NULL)
     (RESULT NULL))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING PREPAREDSQL SELECTSQL))
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     "Table before executing prepared statement:" EOL)
    (PRINT-TABLE (%EXECUTE-SQL CON (WRAP-STRING SELECTSQL) NIL))
    (CL:SETQ PREPAREDSTATEMENT (%PREPARE-STATEMENT CON PREPAREDSQL))
    (%BIND-PARAMETER PREPAREDSTATEMENT 1 SGT-SDBC-STELLA-INTEGER
     (WRAP-INTEGER 23))
    (%BIND-PARAMETER PREPAREDSTATEMENT 2 SGT-SDBC-STELLA-STRING
     (WRAP-STRING "k"))
    (%BIND-PARAMETER PREPAREDSTATEMENT 3 SGT-SDBC-STELLA-DOUBLE-FLOAT
     (WRAP-FLOAT 5.3d0))
    (%BIND-PARAMETER PREPAREDSTATEMENT 4 SGT-SDBC-STELLA-CALENDAR-DATE
     (STRING-TO-CALENDAR-DATE "1997-02-14"))
    (CL:SETQ RESULT (%EXECUTE-SQL CON PREPAREDSTATEMENT NIL))
    (%BIND-PARAMETER PREPAREDSTATEMENT 1 SGT-SDBC-STELLA-INTEGER
     (WRAP-INTEGER 24))
    (%BIND-PARAMETER PREPAREDSTATEMENT 2 SGT-SDBC-STELLA-STRING NULL)
    (%BIND-PARAMETER PREPAREDSTATEMENT 3 SGT-SDBC-STELLA-DOUBLE-FLOAT
     NULL)
    (%BIND-PARAMETER PREPAREDSTATEMENT 4 SGT-SDBC-STELLA-CALENDAR-DATE
     NULL)
    (CL:SETQ RESULT (%EXECUTE-SQL CON PREPAREDSTATEMENT NIL))
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     "Table after executing prepared statements:" EOL)
    (PRINT-TABLE (%EXECUTE-SQL CON (WRAP-STRING SELECTSQL) NIL)))
   (DATABASE-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     "Caught Database Exception: " (EXCEPTION-MESSAGE E) EOL))))

;;; (DEFUN TEST-TRANSACTIONS ...)

(CL:DEFUN TEST-TRANSACTIONS ()
  (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
   "testing transactions..." EOL)
  (CL:HANDLER-CASE
   (CL:LET*
    ((CON
      (%CONNECT
       (CONS-LIST KWD-SDBC-DSN (WRAP-STRING "myodbc3") KWD-SDBC-USER
        (WRAP-STRING "scott") KWD-SDBC-PASSWORD (WRAP-STRING "tiger")
        KWD-SDBC-CONNECTIONSTRING
        (WRAP-STRING
         "jdbc:mysql://localhost:3306/menagerie?user=scott&password=tiger"))))
     (SELECTSQL "select * from customer2")
     (INSERTSQL1 "insert into customer2 values (28, 'aa')")
     (INSERTSQL2 "insert into customer2 values (29, 'z')"))
    (CL:DECLARE
     (CL:TYPE CL:SIMPLE-STRING SELECTSQL INSERTSQL1 INSERTSQL2))
    (%SET-AUTO-COMMIT CON CL:NIL)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     "Table before insert:" EOL)
    (PRINT-TABLE (%EXECUTE-SQL CON (WRAP-STRING SELECTSQL) NIL))
    (%EXECUTE-SQL CON (WRAP-STRING INSERTSQL1) NIL)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     "Table after insert1:" EOL)
    (PRINT-TABLE (%EXECUTE-SQL CON (WRAP-STRING SELECTSQL) NIL))
    (%COMMIT CON)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     "Table after commit:" EOL)
    (PRINT-TABLE (%EXECUTE-SQL CON (WRAP-STRING SELECTSQL) NIL))
    (%EXECUTE-SQL CON (WRAP-STRING INSERTSQL2) NIL)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     "Table after insert2:" EOL)
    (PRINT-TABLE (%EXECUTE-SQL CON (WRAP-STRING SELECTSQL) NIL))
    (%ROLLBACK CON)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     "Table after rollback:" EOL)
    (PRINT-TABLE (%EXECUTE-SQL CON (WRAP-STRING SELECTSQL) NIL))
    (%DISCONNECT CON))
   (DATABASE-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     "Caught Database Exception: " (EXCEPTION-MESSAGE E) EOL))))

;;; (DEFUN TEST-RESULT-SET ...)

(CL:DEFUN TEST-RESULT-SET ()
  (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
   "Testing result set..." EOL)
  (CL:HANDLER-CASE
   (CL:LET*
    ((CON
      (%CONNECT
       (CONS-LIST KWD-SDBC-DSN (WRAP-STRING "myodbc3") KWD-SDBC-USER
        (WRAP-STRING "scott") KWD-SDBC-PASSWORD (WRAP-STRING "tiger")
        KWD-SDBC-CONNECTIONSTRING
        (WRAP-STRING
         "jdbc:mysql://localhost:3306/menagerie?user=scott&password=tiger"))))
     (TYPES
      (LIST* SGT-SDBC-STELLA-INTEGER SGT-SDBC-STELLA-DOUBLE-FLOAT
       SGT-SDBC-STELLA-LONG-INTEGER SYM-SDBC-STELLA-NULL
       SGT-SDBC-STELLA-STRING SGT-SDBC-STELLA-CALENDAR-DATE NIL))
     (SQL
      "select intcol, floatcol, bigintcol, blobcol, varcharcol, datecol from typetest")
     (RESULT (GET-RESULT-SET CON SQL KWD-SDBC-TYPES TYPES)))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SQL))
    (CL:LET* ((ROW NULL) (ITER-000 RESULT))
     (CL:LOOP WHILE (NEXT? ITER-000) DO (CL:SETQ ROW (%VALUE ITER-000))
      (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
       "Retrieved row : " (%VALUE RESULT) EOL)))
    (%DISCONNECT CON))
   (DATABASE-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     "Caught Database Exception: " (EXCEPTION-MESSAGE E) EOL))))

;;; (DEFUN TEST-RETRIEVE-ALL ...)

(CL:DEFUN TEST-RETRIEVE-ALL ()
  (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
   "Testing retrieve all..." EOL)
  (CL:HANDLER-CASE
   (CL:LET*
    ((CON
      (%CONNECT
       (CONS-LIST KWD-SDBC-DSN (WRAP-STRING "myodbc3") KWD-SDBC-USER
        (WRAP-STRING "scott") KWD-SDBC-PASSWORD (WRAP-STRING "tiger")
        KWD-SDBC-CONNECTIONSTRING
        (WRAP-STRING
         "jdbc:mysql://localhost:3306/menagerie?user=scott&password=tiger"))))
     (SQL
      "select intcol, floatcol, bigintcol, blobcol, varcharcol, datecol from typetest")
     (TYPES
      (LIST* SGT-SDBC-STELLA-INTEGER SGT-SDBC-STELLA-DOUBLE-FLOAT
       SGT-SDBC-STELLA-LONG-INTEGER SYM-SDBC-STELLA-NULL
       SGT-SDBC-STELLA-STRING SGT-SDBC-STELLA-CALENDAR-DATE NIL))
     (RESULT
      (%EXECUTE-SQL CON (WRAP-STRING SQL)
       (CONS-LIST KWD-SDBC-TYPES TYPES))))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SQL))
    (CL:WHEN (CL:NOT (CL:EQ RESULT NULL)) (PRINT-TABLE RESULT))
    (%DISCONNECT CON)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     "connection string: " CON EOL))
   (DATABASE-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     "Caught Database Exception: " (EXCEPTION-MESSAGE E) EOL))))

;;; (DEFUN MAIN ...)

(CL:DEFUN MAIN ()
  (STARTUP-SDBC-SYSTEM)
  (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "Start..." EOL)
  (TEST-RETRIEVE-ALL)
  (TEST-RESULT-SET)
  (TEST-TRANSACTIONS)
  (TEST-PREPARED-STATEMENT)
  (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "done!" EOL))

(CL:DEFUN HELP-STARTUP-SDBC1 ()
  (CL:PROGN
   (CL:SETQ KWD-SDBC-LOG-LEVELS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "LOG-LEVELS" NULL 2))
   (CL:SETQ KWD-SDBC-LEVEL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "LEVEL" NULL 2))
   (CL:SETQ KWD-SDBC-NONE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "NONE" NULL 2))
   (CL:SETQ KWD-SDBC-MAX-WIDTH
    (INTERN-RIGID-SYMBOL-WRT-MODULE "MAX-WIDTH" NULL 2))
   (CL:SETQ SGT-SDBC-SDBC-CONNECTION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONNECTION" NULL 1))
   (CL:SETQ SYM-SDBC-SDBC-CONNECTION-STRING
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONNECTION-STRING" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-PROTOCOL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PROTOCOL" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-DBMS-NAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DBMS-NAME" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-STATEMENT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "STATEMENT" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-AUTO-COMMIT?
    (INTERN-RIGID-SYMBOL-WRT-MODULE "AUTO-COMMIT?" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-CREATION-TIME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CREATION-TIME" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-LAST-ACCESS-TIME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "LAST-ACCESS-TIME" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-RENEWAL-TIME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RENEWAL-TIME" NULL 0))
   (CL:SETQ SGT-SDBC-SDBC-PREPARED-STATEMENT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PREPARED-STATEMENT" NULL 1))
   (CL:SETQ SYM-SDBC-SDBC-CONNECTION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONNECTION" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-SQL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "SQL" NULL 0))
   (CL:SETQ SYM-SDBC-STELLA-PARAMETERS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PARAMETERS"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-SDBC-SDBC-RDBMS-ROW
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RDBMS-ROW" NULL 0))
   (CL:SETQ SGT-SDBC-SDBC-RESULT-SET-ITERATOR
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RESULT-SET-ITERATOR" NULL 1))
   (CL:SETQ SYM-SDBC-SDBC-TYPES
    (INTERN-RIGID-SYMBOL-WRT-MODULE "TYPES" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-CONNECT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONNECT" NULL 0))
   (CL:SETQ KWD-SDBC-COMMON-LISP
    (INTERN-RIGID-SYMBOL-WRT-MODULE "COMMON-LISP" NULL 2))
   (CL:SETQ KWD-SDBC-FUNCTION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "FUNCTION" NULL 2))
   (CL:SETQ KWD-SDBC-PROTOCOL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PROTOCOL" NULL 2))
   (CL:SETQ KWD-SDBC-SERVER-TYPE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "SERVER-TYPE" NULL 2))
   (CL:SETQ KWD-SDBC-LOW (INTERN-RIGID-SYMBOL-WRT-MODULE "LOW" NULL 2))
   (CL:SETQ KWD-SDBC-CONNECTION-STRING
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONNECTION-STRING" NULL 2))
   (CL:SETQ KWD-SDBC-HOST
    (INTERN-RIGID-SYMBOL-WRT-MODULE "HOST" NULL 2))
   (CL:SETQ KWD-SDBC-PORT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PORT" NULL 2))
   (CL:SETQ KWD-SDBC-DB-NAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DB-NAME" NULL 2))
   (CL:SETQ KWD-SDBC-DSN (INTERN-RIGID-SYMBOL-WRT-MODULE "DSN" NULL 2))
   (CL:SETQ KWD-SDBC-USER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "USER" NULL 2))
   (CL:SETQ KWD-SDBC-PASSWORD
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PASSWORD" NULL 2))
   (CL:SETQ SYM-SDBC-SDBC-DISCONNECT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DISCONNECT" NULL 0))
   (CL:SETQ KWD-SDBC-WHITE-SPACE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "WHITE-SPACE" NULL 2))
   (CL:SETQ KWD-SDBC-LETTER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "LETTER" NULL 2))
   (CL:SETQ SYM-SDBC-STELLA-NULL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "NULL"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SGT-SDBC-STELLA-CALENDAR-DATE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CALENDAR-DATE"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ SGT-SDBC-STELLA-STRING
    (INTERN-RIGID-SYMBOL-WRT-MODULE "STRING"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ SGT-SDBC-STELLA-INTEGER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "INTEGER"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ SGT-SDBC-STELLA-LONG-INTEGER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "LONG-INTEGER"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ SGT-SDBC-STELLA-DOUBLE-FLOAT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DOUBLE-FLOAT"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ KWD-SDBC-TYPES
    (INTERN-RIGID-SYMBOL-WRT-MODULE "TYPES" NULL 2))
   (CL:SETQ KWD-SDBC-HIGH
    (INTERN-RIGID-SYMBOL-WRT-MODULE "HIGH" NULL 2))
   (CL:SETQ SYM-SDBC-SDBC-EXECUTE-SQL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "EXECUTE-SQL" NULL 0))
   (CL:SETQ KWD-SDBC-STRING-CONSTANT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "STRING-CONSTANT" NULL 2))
   (CL:SETQ KWD-SDBC-IDENTIFIER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "IDENTIFIER" NULL 2))
   (CL:SETQ KWD-SDBC-MYSQL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "MYSQL" NULL 2))
   (CL:SETQ KWD-SDBC-NULL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "NULL" NULL 2))
   (CL:SETQ SYM-SDBC-STELLA-DEFAULT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFAULT"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ KWD-SDBC-DEFAULT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFAULT" NULL 2))
   (CL:SETQ SYM-SDBC-SDBC-INSERT-ROW
    (INTERN-RIGID-SYMBOL-WRT-MODULE "INSERT-ROW" NULL 0))
   (CL:SETQ KWD-SDBC-ORACLE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ORACLE" NULL 2))
   (CL:SETQ SYM-SDBC-SDBC-INSERT-ROWS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "INSERT-ROWS" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-PREPARE-STATEMENT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PREPARE-STATEMENT" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-BIND-PARAMETER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "BIND-PARAMETER" NULL 0))
   (CL:SETQ SGT-SDBC-STELLA-WRAPPER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "WRAPPER"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ SYM-SDBC-SDBC-SET-AUTO-COMMIT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "SET-AUTO-COMMIT" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-COMMIT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "COMMIT" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-ROLLBACK
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ROLLBACK" NULL 0))))

(CL:DEFUN HELP-STARTUP-SDBC2 ()
  (CL:PROGN
   (CL:SETQ SGT-SDBC-SDBC-TABLE-INFO
    (INTERN-RIGID-SYMBOL-WRT-MODULE "TABLE-INFO" NULL 1))
   (CL:SETQ SYM-SDBC-SDBC-DATABASE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DATABASE" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-CATALOG
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CATALOG" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-SCHEMA
    (INTERN-RIGID-SYMBOL-WRT-MODULE "SCHEMA" NULL 0))
   (CL:SETQ SYM-SDBC-STELLA-NAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "NAME"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-SDBC-STELLA-TYPE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "TYPE"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-SDBC-SDBC-REMARKS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "REMARKS" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-COLUMNS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "COLUMNS" NULL 0))
   (CL:SETQ SGT-SDBC-SDBC-COLUMN-INFO
    (INTERN-RIGID-SYMBOL-WRT-MODULE "COLUMN-INFO" NULL 1))
   (CL:SETQ SYM-SDBC-STELLA-TABLE-NAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "TABLE-NAME"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-SDBC-SDBC-DATA-TYPE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DATA-TYPE" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-DATA-TYPE-NAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DATA-TYPE-NAME" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-COLUMN-SIZE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "COLUMN-SIZE" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-BUFFER-LENGTH
    (INTERN-RIGID-SYMBOL-WRT-MODULE "BUFFER-LENGTH" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-DECIMAL-DIGITS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DECIMAL-DIGITS" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-RADIX
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RADIX" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-NULLABLE?
    (INTERN-RIGID-SYMBOL-WRT-MODULE "NULLABLE?" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-IS-NULLABLE?
    (INTERN-RIGID-SYMBOL-WRT-MODULE "IS-NULLABLE?" NULL 0))
   (CL:SETQ SYM-SDBC-STELLA-DOCUMENTATION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DOCUMENTATION"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-SDBC-STELLA-DEFAULT-VALUE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFAULT-VALUE"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-SDBC-SDBC-SQL-DATA-TYPE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "SQL-DATA-TYPE" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-SQL-DATETIME-SUB
    (INTERN-RIGID-SYMBOL-WRT-MODULE "SQL-DATETIME-SUB" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-CHAR-OCTET-LENGTH
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CHAR-OCTET-LENGTH" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-ORDINAL-POSITION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ORDINAL-POSITION" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-GET-TABLES
    (INTERN-RIGID-SYMBOL-WRT-MODULE "GET-TABLES" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-GET-COLUMNS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "GET-COLUMNS" NULL 0))
   (CL:SETQ SYM-SDBC-SDBC-GET-SERVER-INFO
    (INTERN-RIGID-SYMBOL-WRT-MODULE "GET-SERVER-INFO" NULL 0))
   (CL:SETQ KWD-SDBC-COMMAND
    (INTERN-RIGID-SYMBOL-WRT-MODULE "COMMAND" NULL 2))
   (CL:SETQ KWD-SDBC-DATA-SOURCE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DATA-SOURCE" NULL 2))
   (CL:SETQ KWD-SDBC-SQL (INTERN-RIGID-SYMBOL-WRT-MODULE "SQL" NULL 2))
   (CL:SETQ KWD-SDBC-OTHERWISE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "OTHERWISE" NULL 2))
   (CL:SETQ SGT-SDBC-STELLA-CONS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONS"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ KWD-SDBC-DIGIT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DIGIT" NULL 2))
   (CL:SETQ KWD-SDBC-CONNECTIONSTRING
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONNECTIONSTRING" NULL 2))
   (CL:SETQ SYM-SDBC-SDBC-STARTUP-SDBC
    (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-SDBC" NULL 0))
   (CL:SETQ SYM-SDBC-STELLA-METHOD-STARTUP-CLASSNAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))))

(CL:DEFUN HELP-STARTUP-SDBC3 ()
  (CL:PROGN
   (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "NATIVE-CONNECTION"
    "(DEFCLASS NATIVE-CONNECTION () :ABSTRACT? TRUE :CPP-NATIVE-TYPE \"sdbc::NativeConnection*\" :JAVA-NATIVE-TYPE \"edu.isi.sdbc.NativeConnection\" :CL-NATIVE-TYPE \"#+:EXCL DB-INTERFACE::ODBC-DB #+:CLSQL CLSQL:DATABASE  #-(OR :EXCL :CLSQL) CL:STANDARD-OBJECT\")")
   (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "NATIVE-RESULT-SET"
    "(DEFCLASS NATIVE-RESULT-SET () :ABSTRACT? TRUE :CPP-NATIVE-TYPE \"NativeResultSet*\" :JAVA-NATIVE-TYPE \"edu.isi.sdbc.ResultSet\" :CL-NATIVE-TYPE \"#+:EXCL DB-INTERFACE::QUERY #+:CLSQL CL:LIST  #-(OR :EXCL :CLSQL) CL:STANDARD-OBJECT\")")
   (CL:LET*
    ((CLASS
      (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "CONNECTION"
       "(DEFCLASS CONNECTION (STANDARD-OBJECT) :PUBLIC-SLOTS ((NATIVE-CONNECTION :TYPE NATIVE-CONNECTION :PUBLIC? TRUE) (CONNECTION-STRING :TYPE STRING) (PROTOCOL :TYPE STRING) (DBMS-NAME :TYPE KEYWORD :DOCUMENTATION \"Indicates to what kind of DBMS we are connected.\") (STATEMENT :TYPE PREPARED-STATEMENT :DOCUMENTATION \"Prepared statement associated with this connection.\") (AUTO-COMMIT? :TYPE BOOLEAN :INITIALLY TRUE :DOCUMENTATION \"State of connection's auto-commit feature.\") (CREATION-TIME :TYPE CALENDAR-DATE :DOCUMENTATION \"Time at which connection was created.\") (LAST-ACCESS-TIME :TYPE CALENDAR-DATE :DOCUMENTATION \"Time at which connection was last accessed.\") (RENEWAL-TIME :TYPE CALENDAR-DATE :DOCUMENTATION \"Time at or after which connection should be renewed.\")) :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"|CON|\\\"\" (CONNECTION-STRING SELF) \"\\\"\"))")))
    (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
     (CL:FUNCTION NEW-CONNECTION))
    (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
     (CL:FUNCTION ACCESS-CONNECTION-SLOT-VALUE)))
   (CL:LET*
    ((CLASS
      (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "PREPARED-STATEMENT"
       "(DEFCLASS PREPARED-STATEMENT (STANDARD-OBJECT) :SLOTS ((CONNECTION :TYPE CONNECTION) (STATEMENT :TYPE NATIVE-PREPARED-STATEMENT) (SQL :TYPE STRING) (PARAMETERS :TYPE (KEY-VALUE-LIST OF INTEGER-WRAPPER CONS) :INITIALLY (NEW KEY-VALUE-LIST) :DOCUMENTATION \"Stores parameters bound so far to support connection renewal.\")))")))
    (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
     (CL:FUNCTION NEW-PREPARED-STATEMENT))
    (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
     (CL:FUNCTION ACCESS-PREPARED-STATEMENT-SLOT-VALUE)))
   (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "NATIVE-PREPARED-STATEMENT"
    "(DEFCLASS NATIVE-PREPARED-STATEMENT () :ABSTRACT? TRUE :JAVA-NATIVE-TYPE \"java.sql.PreparedStatement\")")
   (CL:LET*
    ((CLASS
      (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "DATABASE-EXCEPTION"
       "(DEFCLASS DATABASE-EXCEPTION (STELLA-EXCEPTION))")))
    (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
     (CL:FUNCTION NEW-DATABASE-EXCEPTION)))
   (DEFINE-STELLA-TYPE-FROM-STRINGIFIED-SOURCE
    "(DEFTYPE RDBMS-ROW (CONS OF STRING-WRAPPER))")
   (CL:LET*
    ((CLASS
      (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "RESULT-SET-ITERATOR"
       "(DEFCLASS RESULT-SET-ITERATOR (ITERATOR) :DOCUMENTATION \"Iterator class for a table returned by a SQL query.\" :PARAMETERS ((ANY-VALUE :TYPE RDBMS-ROW)) :PUBLIC-SLOTS ((RESULT-SET :TYPE NATIVE-RESULT-SET) (TYPES :TYPE CONS)))")))
    (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
     (CL:FUNCTION NEW-RESULT-SET-ITERATOR))
    (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
     (CL:FUNCTION ACCESS-RESULT-SET-ITERATOR-SLOT-VALUE)))
   (CL:LET*
    ((CLASS
      (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "TABLE-INFO"
       "(DEFCLASS TABLE-INFO (STANDARD-OBJECT) :PUBLIC-SLOTS ((DATABASE :TYPE STRING) (CATALOG :RENAMES DATABASE) (SCHEMA :TYPE STRING) (NAME :TYPE STRING) (TYPE :TYPE STRING) (REMARKS :TYPE STRING) (COLUMNS :TYPE (LIST OF COLUMN-INFO))))")))
    (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
     (CL:FUNCTION NEW-TABLE-INFO))
    (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
     (CL:FUNCTION ACCESS-TABLE-INFO-SLOT-VALUE)))
   (CL:LET*
    ((CLASS
      (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "COLUMN-INFO"
       "(DEFCLASS COLUMN-INFO (STANDARD-OBJECT) :PUBLIC-SLOTS ((DATABASE :TYPE STRING) (CATALOG :RENAMES DATABASE) (SCHEMA :TYPE STRING) (TABLE-NAME :TYPE STRING) (NAME :TYPE STRING) (DATA-TYPE :TYPE INTEGER :DOCUMENTATION \"SQL type from java.sql.Types.\") (DATA-TYPE-NAME :TYPE STRING :DOCUMENTATION \"Data source dependent type name, for a UDT the type name is fully qualified.\") (COLUMN-SIZE :TYPE INTEGER :DOCUMENTATION \"Column size. For char or date types this is the maximum number of characters,
for numeric or decimal types this is precision.\") (BUFFER-LENGTH :TYPE INTEGER :DOCUMENTATION \"Not used.\") (DECIMAL-DIGITS :TYPE INTEGER :DOCUMENTATION \"The number of fractional digits.\") (RADIX :TYPE INTEGER :DOCUMENTATION \"Radix (typically either 10 or 2).\") (NULLABLE? :TYPE THREE-VALUED-BOOLEAN :DOCUMENTATION \"TRUE means definitely allows NULL values, FALSE means might not allow
NULL values, NULL means nullability unknown.\") (IS-NULLABLE? :TYPE THREE-VALUED-BOOLEAN :DOCUMENTATION \"TRUE means might allow NULL values, FALSE means definitely does not
allow NULL values, NULL means nullability unknown.\") (DOCUMENTATION :TYPE STRING :DOCUMENTATION \"Comment describing column (may be null).\") (REMARKS :RENAMES DOCUMENTATION) (DEFAULT-VALUE :TYPE STRING) (SQL-DATA-TYPE :TYPE INTEGER :DOCUMENTATION \"Not used.\") (SQL-DATETIME-SUB :TYPE INTEGER :DOCUMENTATION \"Not used.\") (CHAR-OCTET-LENGTH :TYPE INTEGER :DOCUMENTATION \"For char types the maximum number of bytes in the column.\") (ORDINAL-POSITION :TYPE INTEGER :DOCUMENTATION \"Index of column in table (starting at 1).\")))")))
    (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
     (CL:FUNCTION NEW-COLUMN-INFO))
    (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
     (CL:FUNCTION ACCESS-COLUMN-INFO-SLOT-VALUE)))))

(CL:DEFUN HELP-STARTUP-SDBC4 ()
  (CL:PROGN
   (DEFINE-FUNCTION-OBJECT "CONNECT"
    "(DEFUN (CONNECT CONNECTION) (|&REST| (KEYS-AND-VALUES OBJECT)) :DOCUMENTATION \"Create a connection to a database.  Currently-supported parameters
are (values need to be strings):
  :PROTOCOL          - \\\"ODBC\\\", \\\"JDBC\\\", \\\"CLSQL\\\" or \\\"MYSQL\\\" (defaults to \\\"ODBC\\\")
  :SERVER-TYPE       - Type of database server (for JDBC strings)
  :DSN               - Name of ODBC Datasource
  :DB-NAME           - Name of physical database
  :USER              - Database user id.
  :PASSWORD          - Database password
  :HOST              - Host database server runs on
  :PORT              - Port to use to connect to the server
  :CONNECTION-STRING - Connection string to be used by ODBC or JDBC drivers
                       instead of DSN, USER, PASSWORD, etc.
A DATABASE-EXCEPTION is thrown if the connection is unsuccessful.\" :PUBLIC? TRUE :COMMAND? TRUE)"
    (CL:FUNCTION %CONNECT) (CL:FUNCTION CONNECT-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "CALL-CONNECT"
    "(DEFUN (CALL-CONNECT CONNECTION) ((KEYS-AND-VALUES CONS)) :PUBLIC? TRUE :DOCUMENTATION \"Functional interface to `connect'.  See its documentation\")"
    (CL:FUNCTION CALL-CONNECT) NULL)
   (DEFINE-FUNCTION-OBJECT "*DB-CONNECTION-RENEWAL-INTERVAL*-SETTER"
    "(DEFUN (*DB-CONNECTION-RENEWAL-INTERVAL*-SETTER INTEGER) ((VALUE INTEGER)))"
    (CL:FUNCTION *DB-CONNECTION-RENEWAL-INTERVAL*-SETTER) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-MAX-CONNECTION-LIFETIME"
    "(DEFUN (GET-MAX-CONNECTION-LIFETIME INTEGER) ((CON CONNECTION)))"
    (CL:FUNCTION GET-MAX-CONNECTION-LIFETIME) NULL)
   (DEFINE-FUNCTION-OBJECT "MAYBE-RENEW-CONNECTION"
    "(DEFUN MAYBE-RENEW-CONNECTION ((CON CONNECTION)))"
    (CL:FUNCTION MAYBE-RENEW-CONNECTION) NULL)
   (DEFINE-FUNCTION-OBJECT "JDBC-CONNECTION-STRING?"
    "(DEFUN (JDBC-CONNECTION-STRING? BOOLEAN) ((STRING STRING)))"
    (CL:FUNCTION JDBC-CONNECTION-STRING?) NULL)
   (DEFINE-FUNCTION-OBJECT "MAKE-JDBC-CONNECTION-STRING"
    "(DEFUN (MAKE-JDBC-CONNECTION-STRING STRING) ((OPTIONS (PROPERTY-LIST OF KEYWORD OBJECT))))"
    (CL:FUNCTION MAKE-JDBC-CONNECTION-STRING) NULL)
   (DEFINE-FUNCTION-OBJECT "ODBC-CONNECTION-STRING?"
    "(DEFUN (ODBC-CONNECTION-STRING? BOOLEAN) ((STRING STRING)))"
    (CL:FUNCTION ODBC-CONNECTION-STRING?) NULL)
   (DEFINE-FUNCTION-OBJECT "MAKE-ODBC-CONNECTION-STRING"
    "(DEFUN (MAKE-ODBC-CONNECTION-STRING STRING) ((OPTIONS (PROPERTY-LIST OF KEYWORD STRING-WRAPPER))))"
    (CL:FUNCTION MAKE-ODBC-CONNECTION-STRING) NULL)
   (DEFINE-FUNCTION-OBJECT "CL-NATIVE-ODBC-CONNECT"
    "(DEFUN (CL-NATIVE-ODBC-CONNECT NATIVE-CONNECTION STRING) ((CONNECTIONSTRING STRING)))"
    (CL:FUNCTION CL-NATIVE-ODBC-CONNECT) NULL)
   (DEFINE-FUNCTION-OBJECT "CL-NATIVE-CLSQL-CONNECT"
    "(DEFUN (CL-NATIVE-CLSQL-CONNECT NATIVE-CONNECTION STRING) ((OPTIONS (PROPERTY-LIST OF KEYWORD STRING-WRAPPER)) (SERVER-TYPE STRING)))"
    (CL:FUNCTION CL-NATIVE-CLSQL-CONNECT) NULL)
   (DEFINE-FUNCTION-OBJECT "DISCONNECT"
    "(DEFUN DISCONNECT ((CONNECTION CONNECTION)) :DOCUMENTATION \"Disconnect `connection' from a database.  A DATABASE-EXCEPTION is thrown if
the disconnect is unsuccessful.\" :PUBLIC? TRUE :COMMAND? TRUE)"
    (CL:FUNCTION %DISCONNECT) NULL)
   (DEFINE-FUNCTION-OBJECT "CL-NATIVE-DISCONNECT"
    "(DEFUN CL-NATIVE-DISCONNECT ((NATIVE-CONNECTION NATIVE-CONNECTION)))"
    (CL:FUNCTION CL-NATIVE-DISCONNECT) NULL)
   (DEFINE-FUNCTION-OBJECT "CL-NATIVE-ODBC-DISCONNECT"
    "(DEFUN CL-NATIVE-ODBC-DISCONNECT ((NATIVECONNECTION NATIVE-CONNECTION)))"
    (CL:FUNCTION CL-NATIVE-ODBC-DISCONNECT) NULL)
   (DEFINE-FUNCTION-OBJECT "CL-NATIVE-CLSQL-DISCONNECT"
    "(DEFUN CL-NATIVE-CLSQL-DISCONNECT ((NATIVE-CONNECTION NATIVE-CONNECTION)))"
    (CL:FUNCTION CL-NATIVE-CLSQL-DISCONNECT) NULL)
   (DEFINE-FUNCTION-OBJECT "SQL-QUERY?"
    "(DEFUN (SQL-QUERY? BOOLEAN) ((SQL-EXPRESSION STRING)) :DOCUMENTATION \"Return `true' if `sql-expression' is a SQL command string which returns
values.\" :PUBLIC? FALSE)" (CL:FUNCTION SQL-QUERY?) NULL)
   (DEFINE-FUNCTION-OBJECT "STELLIFY-WITH-NIL-TO-NULL"
    "(DEFUN (STELLIFY-WITH-NIL-TO-NULL OBJECT) ((SELF OBJECT)) :DOCUMENTATION \"Convert a Lisp object into a STELLA object.\" :PUBLIC? TRUE)"
    (CL:FUNCTION STELLIFY-WITH-NIL-TO-NULL) NULL)
   (DEFINE-FUNCTION-OBJECT "CL-TRANSLATE-SQL-PARAMETER-TYPE-SPECIFIER"
    "(DEFUN (CL-TRANSLATE-SQL-PARAMETER-TYPE-SPECIFIER OBJECT) ((STELLATYPE OBJECT)))"
    (CL:FUNCTION CL-TRANSLATE-SQL-PARAMETER-TYPE-SPECIFIER) NULL)
   (DEFINE-FUNCTION-OBJECT "CL-TRANSLATE-SQL-TYPE-SPECIFIER"
    "(DEFUN (CL-TRANSLATE-SQL-TYPE-SPECIFIER OBJECT) ((STELLATYPE OBJECT)))"
    (CL:FUNCTION CL-TRANSLATE-SQL-TYPE-SPECIFIER) NULL)
   (DEFINE-FUNCTION-OBJECT "CL-TRANSLATE-SQL-TYPE-SPECIFIERS"
    "(DEFUN (CL-TRANSLATE-SQL-TYPE-SPECIFIERS CONS) ((STELLATYPES CONS)))"
    (CL:FUNCTION CL-TRANSLATE-SQL-TYPE-SPECIFIERS) NULL)
   (DEFINE-FUNCTION-OBJECT "EXECUTE-SQL"
    "(DEFUN (EXECUTE-SQL OBJECT) ((CONNECTION CONNECTION) (SQL OBJECT) |&REST| (OPTIONS OBJECT)) :PUBLIC? TRUE :COMMAND? TRUE :DOCUMENTATION \"Execute a SQL statement, and return a table as the reuslt
                  of a SQL query (represented as a (CONS OF (CONS OF OBJECT))),
                  or NULL as the result of a successfull SQL insert, update,
                  delete or other command.
                  `sql' can either be a string representing a SQL command or
                  a PREPARED-STATEMENT.
                  Options include: 
                     :types <typelist>, where <typelist> is a cons list of surrogates
                  specifying the expected Stella types.  Legal surrogate values are
                  @INTEGER, @LONG-INTEGER, @DOUBLE-FLOAT, @CALENDAR-DATE, @STRING, and
                  NULL.  If NULL is specified, values are returned as strings.
                  A DATABASE-EXCEPTION is thrown if execution is unsuccessful.\")"
    (CL:FUNCTION %EXECUTE-SQL)
    (CL:FUNCTION EXECUTE-SQL-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "CL-EXECUTE-SQL"
    "(DEFUN (CL-EXECUTE-SQL OBJECT) ((CONNECTION NATIVE-CONNECTION) (SQL STRING) (TYPES CONS)))"
    (CL:FUNCTION CL-EXECUTE-SQL) NULL)
   (DEFINE-FUNCTION-OBJECT "CL-DO-EXECUTE-PREPARED-STATEMENT"
    "(DEFUN (CL-DO-EXECUTE-PREPARED-STATEMENT OBJECT) ((CONNECTION NATIVE-CONNECTION) (SQL PREPARED-STATEMENT)))"
    (CL:FUNCTION CL-DO-EXECUTE-PREPARED-STATEMENT) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-RESULT-SET"
    "(DEFUN (GET-RESULT-SET RESULT-SET-ITERATOR) ((CONNECTION CONNECTION) (SQL STRING) |&REST| (OPTIONS OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Execute a SQL query, and return a ResultSet object.
                  Options include: 
                     :types <typelist>, where <typelist> is a cons list of surrogates
                  specifying the expected Stella types.  Legal surrogate values are
                  @INTEGER, @LONG-INTEGER, @DOUBLE-FLOAT, @CALENDAR-DATE, @STRING, and
                  NULL.  If NULL is specified, values are returned as strings.
                  A DATABASE-EXCEPTION is thrown if execution is unsuccessful.\")"
    (CL:FUNCTION GET-RESULT-SET) NULL)
   (DEFINE-FUNCTION-OBJECT "CL-GET-NATIVE-RESULT-SET"
    "(DEFUN (CL-GET-NATIVE-RESULT-SET NATIVE-RESULT-SET) ((CONNECTION NATIVE-CONNECTION) (SQL STRING) (TYPES CONS)))"
    (CL:FUNCTION CL-GET-NATIVE-RESULT-SET) NULL)
   (DEFINE-METHOD-OBJECT
    "(DEFMETHOD (NEXT? BOOLEAN) ((SELF RESULT-SET-ITERATOR)))"
    (WRAP-METHOD-CODE (CL:FUNCTION NEXT?)) NULL)
   (DEFINE-FUNCTION-OBJECT "SQL-ESCAPE-STRING"
    "(DEFUN (SQL-ESCAPE-STRING STRING) ((VALUE STRING) (QUOTECHAR CHARACTER)))"
    (CL:FUNCTION SQL-ESCAPE-STRING) NULL)
   (DEFINE-FUNCTION-OBJECT "SQL-QUOTE-CHARACTER"
    "(DEFUN (SQL-QUOTE-CHARACTER CHARACTER) ((DBMS-NAME KEYWORD) (LEXICALTYPE KEYWORD)))"
    (CL:FUNCTION SQL-QUOTE-CHARACTER) NULL)
   (DEFINE-FUNCTION-OBJECT "PRINT-VALUE-LIST"
    "(DEFUN PRINT-VALUE-LIST ((STREAM OUTPUT-STREAM) (VALUES CONS) (QUOTECHAR CHARACTER)))"
    (CL:FUNCTION PRINT-VALUE-LIST) NULL)
   (DEFINE-FUNCTION-OBJECT "INSERT-ROW"
    "(DEFUN INSERT-ROW ((CONNECTION CONNECTION) (TABLE STRING) (COLUMNS (CONS OF STRING-WRAPPER)) (VALUES CONS)) :DOCUMENTATION \"Insert a row of `values' into `table'.  `columns'
can be NULL or NIL in which case `values' must be suppied for all
columns.  If `columns' are given `values' will be only inserted in
the specified columns.  Table and column names will be quoted which
means their casing must match exactly their definition (no case
conversion will be performed).  Supplied `values' can be strings,
integers or floats.  Strings will be quoted and escaped appropriately.
The values NULL, :NULL or (quote NULL) translate into NULL.  The
values :DEFAULT or (quote DEFAULT) translate into DEFAULT.  Arbitrary
unquoted strings can be generated via VERBATIM-STRING-WRAPPERs as
values (e.g., for something like `seq.nextval' in Oracle).\" :PUBLIC? TRUE :COMMAND? TRUE)"
    (CL:FUNCTION %INSERT-ROW)
    (CL:FUNCTION INSERT-ROW-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "INSERT-ROWS"
    "(DEFUN INSERT-ROWS ((CONNECTION CONNECTION) (TABLE STRING) (COLUMNS (CONS OF STRING-WRAPPER)) (ROWS (CONS OF RDBMS-ROW))) :DOCUMENTATION \"Insert a set of `rows' into `table'.  `columns'
can be NULL or NIL in which case values must be suppied for all
columns.  If `columns' are given `values' will be only inserted in
the specified columns.  Table and column names will be quoted which
means their casing must match exactly their definition (no case
conversion will be performed).  See `insert-row' for a description
of supported value formats.  DEFAULT values are currently not supported
for Oracle!  This function performs a fairly efficient multi-row
insert which is significantly faster than inserting rows one by one.\" :PUBLIC? TRUE :COMMAND? TRUE)"
    (CL:FUNCTION %INSERT-ROWS)
    (CL:FUNCTION INSERT-ROWS-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "COERCE-UNCOERCED-VALUES-IN-TABLE"
    "(DEFUN (COERCE-UNCOERCED-VALUES-IN-TABLE CONS) ((TABLE CONS) (TYPES CONS)))"
    (CL:FUNCTION COERCE-UNCOERCED-VALUES-IN-TABLE) NULL)
   (DEFINE-FUNCTION-OBJECT "COERCE-UNCOERCED-COLUMN-VALUES"
    "(DEFUN (COERCE-UNCOERCED-COLUMN-VALUES CONS) ((ROW CONS) (TYPES CONS)))"
    (CL:FUNCTION COERCE-UNCOERCED-COLUMN-VALUES) NULL)
   (DEFINE-FUNCTION-OBJECT "CONVERT-STRING-TO-TYPED-OBJECT"
    "(DEFUN (CONVERT-STRING-TO-TYPED-OBJECT OBJECT) ((VALUESTRING STRING) (TYPESPEC GENERALIZED-SYMBOL)))"
    (CL:FUNCTION CONVERT-STRING-TO-TYPED-OBJECT) NULL)
   (DEFINE-FUNCTION-OBJECT "PREPARE-STATEMENT"
    "(DEFUN (PREPARE-STATEMENT PREPARED-STATEMENT) ((CONNECTION CONNECTION) (SQL STRING)) :DOCUMENTATION \"Prepare the `sql' statement for execution at the server and return
a prepared statement object.  After binding all its paramters via `bind-parameter'
the statement can be executed via `execute-sql'.
IMPORTANT: Only one prepared statement can be associated with a connection at a time.\" :PUBLIC? TRUE :COMMAND? TRUE)"
    (CL:FUNCTION %PREPARE-STATEMENT)
    (CL:FUNCTION PREPARE-STATEMENT-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "BIND-PARAMETER"
    "(DEFUN BIND-PARAMETER ((STATEMENT PREPARED-STATEMENT) (POSITION INTEGER) (TYPESPEC SURROGATE) (VALUE OBJECT)) :DOCUMENTATION \"Bind the parameter at `position' (1-based) in the prepared
statement `statement' to `value'.  `typeSpec' characterizes the type of
`value' for proper translation and coercion.\" :PUBLIC? TRUE :COMMAND? TRUE)"
    (CL:FUNCTION %BIND-PARAMETER)
    (CL:FUNCTION BIND-PARAMETER-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "CL-DO-BIND-PARAMETER"
    "(DEFUN CL-DO-BIND-PARAMETER ((STATEMENT PREPARED-STATEMENT) (POSITION INTEGER) (TYPESPEC SURROGATE) (VALUE OBJECT)))"
    (CL:FUNCTION CL-DO-BIND-PARAMETER) NULL)
   (DEFINE-FUNCTION-OBJECT "SET-AUTO-COMMIT"
    "(DEFUN SET-AUTO-COMMIT ((CONNECTION CONNECTION) (FLAG BOOLEAN)) :DOCUMENTATION \"Set the auto-commit feature of `connection' to TRUE or FALSE.
If a connection is in auto-commit mode, then all its SQL statements will be executed
and committed as individual transactions.  Otherwise, its SQL statements are grouped
into transactions that are terminated by a call to either `commit' or `rollback'.
By default, new connections are in auto-commit mode.\" :PUBLIC? TRUE :COMMAND? TRUE)"
    (CL:FUNCTION %SET-AUTO-COMMIT)
    (CL:FUNCTION SET-AUTO-COMMIT-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "COMMIT"
    "(DEFUN COMMIT ((CONNECTION CONNECTION)) :DOCUMENTATION \"Commit the current transaction.  Makes all changes made since the
previous commit/rollback permanent and releases any database locks currently held
by this `connection' object.  This function is a no-op if auto-commit mode is
enabled (see `set-auto-commit').\" :PUBLIC? TRUE :COMMAND? TRUE)"
    (CL:FUNCTION %COMMIT) NULL)
   (DEFINE-FUNCTION-OBJECT "ROLLBACK"
    "(DEFUN ROLLBACK ((CONNECTION CONNECTION)) :DOCUMENTATION \"Rollback the current transaction.  Undoes all changes made in
the current transaction and releases any database locks currently held by this
`connection' object.  This function is a no-op if auto-commit mode is enabled
 (see `set-auto-commit').\" :PUBLIC? TRUE :COMMAND? TRUE)"
    (CL:FUNCTION %ROLLBACK) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-TABLES"
    "(DEFUN (GET-TABLES (CONS OF TABLE-INFO)) ((CONNECTION CONNECTION) (CATALOG-NAME STRING) (SCHEMA-NAME STRING) (TABLE-NAME STRING) (TABLE-TYPE STRING)) :DOCUMENTATION \"Get the tables of the database identified by `connection'
and return the result as a list of objects containing all the relevant
meta information.  If any of the remaining arguments is supplied as
non-NULL, only tables whose corresponding field matches will be returned.
This is less general than what is supported by JDBC and ODBC, but Allegro
ODBC does not support filtering based on patterns, so we only do simple
manual filtering here.\" :PUBLIC? TRUE :COMMAND? TRUE)"
    (CL:FUNCTION %GET-TABLES)
    (CL:FUNCTION GET-TABLES-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "GET-COLUMNS"
    "(DEFUN (GET-COLUMNS (CONS OF COLUMN-INFO)) ((CONNECTION CONNECTION) (CATALOGNAME STRING) (SCHEMANAME STRING) (TABLENAME STRING) (COLUMNNAME STRING)) :PUBLIC? TRUE :COMMAND? TRUE)"
    (CL:FUNCTION %GET-COLUMNS)
    (CL:FUNCTION GET-COLUMNS-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "GET-SERVER-INFO"
    "(DEFUN (GET-SERVER-INFO WRAPPER) ((CONNECTION CONNECTION) (PROPERTY STRING)) :PUBLIC? TRUE :COMMAND? TRUE)"
    (CL:FUNCTION %GET-SERVER-INFO)
    (CL:FUNCTION GET-SERVER-INFO-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "GUESS-DBMS-NAME"
    "(DEFUN (GUESS-DBMS-NAME STRING) ((CONNECTION CONNECTION)))"
    (CL:FUNCTION GUESS-DBMS-NAME) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-DBMS-NAME"
    "(DEFUN (GET-DBMS-NAME KEYWORD) ((CONNECTION CONNECTION)))"
    (CL:FUNCTION GET-DBMS-NAME) NULL)
   (DEFINE-FUNCTION-OBJECT "PRINT-TABLE"
    "(DEFUN PRINT-TABLE ((TABLE OBJECT)))" (CL:FUNCTION PRINT-TABLE)
    NULL)
   (DEFINE-FUNCTION-OBJECT "CALENDAR-DATE-TO-SQL-STRING"
    "(DEFUN (CALENDAR-DATE-TO-SQL-STRING STRING) ((DATE CALENDAR-DATE)))"
    (CL:FUNCTION CALENDAR-DATE-TO-SQL-STRING) NULL)
   (DEFINE-FUNCTION-OBJECT "LOAD-SQL-CMD-TEMPLATES"
    "(DEFUN LOAD-SQL-CMD-TEMPLATES ((FILE STRING)))"
    (CL:FUNCTION LOAD-SQL-CMD-TEMPLATES) NULL)
   (DEFINE-FUNCTION-OBJECT "INSERT-SQL-COMMAND-TEMPLATE"
    "(DEFUN INSERT-SQL-COMMAND-TEMPLATE ((TEMPLATE PROPERTY-LIST)))"
    (CL:FUNCTION INSERT-SQL-COMMAND-TEMPLATE) NULL)
   (DEFINE-FUNCTION-OBJECT "LOOKUP-SQL-CMD-TEMPLATE"
    "(DEFUN (LOOKUP-SQL-CMD-TEMPLATE PROPERTY-LIST) ((COMMANDNAME OBJECT) (DATASOURCE OBJECT)))"
    (CL:FUNCTION LOOKUP-SQL-CMD-TEMPLATE) NULL)
   (DEFINE-FUNCTION-OBJECT "INSTANTIATE-SQL-CMD"
    "(DEFUN (INSTANTIATE-SQL-CMD STRING) ((CMDNAME OBJECT) (DATASOURCE OBJECT) |&REST| (|VARS&VALUES| STRING)))"
    (CL:FUNCTION INSTANTIATE-SQL-CMD) NULL)
   (DEFINE-FUNCTION-OBJECT "INSTANTIATE-SQL-CMD-TEMPLATE"
    "(DEFUN (INSTANTIATE-SQL-CMD-TEMPLATE STRING) ((TEMPLATE STRING) (VARIABLES (KEY-VALUE-LIST OF STRING-WRAPPER OBJECT))))"
    (CL:FUNCTION INSTANTIATE-SQL-CMD-TEMPLATE) NULL)
   (DEFINE-FUNCTION-OBJECT "READ-SQL-CMD-TEMPLATE-VARIABLE"
    "(DEFUN (READ-SQL-CMD-TEMPLATE-VARIABLE STRING INTEGER) ((TEMPLATE STRING) (START INTEGER) (END INTEGER)))"
    (CL:FUNCTION READ-SQL-CMD-TEMPLATE-VARIABLE) NULL)
   (DEFINE-FUNCTION-OBJECT "INSTANTIATE-SQL-CMD-TEMPLATE-VARIABLE"
    "(DEFUN (INSTANTIATE-SQL-CMD-TEMPLATE-VARIABLE STRING) ((TEMPLATEVARIABLE STRING) (VARIABLES (KEY-VALUE-LIST OF STRING-WRAPPER OBJECT))))"
    (CL:FUNCTION INSTANTIATE-SQL-CMD-TEMPLATE-VARIABLE) NULL)
   (DEFINE-FUNCTION-OBJECT
    "PARSE-SQL-CMD-TEMPLATE-VARIABLE-RANGE-AND-DEFAULT"
    "(DEFUN (PARSE-SQL-CMD-TEMPLATE-VARIABLE-RANGE-AND-DEFAULT STRING INTEGER INTEGER STRING) ((TEMPLATEVARIABLE STRING) (VARIABLENAME STRING) (START INTEGER)))"
    (CL:FUNCTION PARSE-SQL-CMD-TEMPLATE-VARIABLE-RANGE-AND-DEFAULT)
    NULL)
   (DEFINE-FUNCTION-OBJECT "TEST-PREPARED-STATEMENT"
    "(DEFUN TEST-PREPARED-STATEMENT ())"
    (CL:FUNCTION TEST-PREPARED-STATEMENT) NULL)
   (DEFINE-FUNCTION-OBJECT "TEST-TRANSACTIONS"
    "(DEFUN TEST-TRANSACTIONS ())" (CL:FUNCTION TEST-TRANSACTIONS)
    NULL)
   (DEFINE-FUNCTION-OBJECT "TEST-RESULT-SET"
    "(DEFUN TEST-RESULT-SET ())" (CL:FUNCTION TEST-RESULT-SET) NULL)
   (DEFINE-FUNCTION-OBJECT "TEST-RETRIEVE-ALL"
    "(DEFUN TEST-RETRIEVE-ALL ())" (CL:FUNCTION TEST-RETRIEVE-ALL)
    NULL)
   (DEFINE-FUNCTION-OBJECT "MAIN" "(DEFUN MAIN () :PUBLIC? TRUE)"
    (CL:FUNCTION MAIN) NULL)))

(CL:DEFUN STARTUP-SDBC ()
  (CL:LET*
   ((*MODULE* (GET-STELLA-MODULE "/SDBC" (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2) (HELP-STARTUP-SDBC1)
    (HELP-STARTUP-SDBC2))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 4)
    (CL:SETQ *SQL-COMMAND-TEMPLATES* (NEW-KEY-VALUE-MAP)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 5) (HELP-STARTUP-SDBC3))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7) (HELP-STARTUP-SDBC4)
    (DEFINE-FUNCTION-OBJECT "STARTUP-SDBC"
     "(DEFUN STARTUP-SDBC () :PUBLIC? TRUE)" (CL:FUNCTION STARTUP-SDBC)
     NULL)
    (CL:LET* ((FUNCTION (LOOKUP-FUNCTION SYM-SDBC-SDBC-STARTUP-SDBC)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-SDBC-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupSdbc") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "/SDBC")))
    (%SET-LOGGING-PARAMETERS "SDBC"
     (CONS-LIST KWD-SDBC-LOG-LEVELS
      (GET-QUOTED-TREE "((:NONE :LOW :MEDIUM :HIGH) \"/SDBC\")"
       "/SDBC")
      KWD-SDBC-LEVEL KWD-SDBC-NONE KWD-SDBC-MAX-WIDTH
      (WRAP-INTEGER 250)))
    (REGISTER-NATIVE-NAME SYM-SDBC-SDBC-CONNECT KWD-SDBC-COMMON-LISP
     KWD-SDBC-FUNCTION)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *DB-CONNECTION-RENEWAL-INTERVAL* INTEGER 60 :DOCUMENTATION \"The maximum lifetime of a database connection (in seconds) after which
it gets automatically renewed.  Auto-renewals avoid connection timeout errors which are
otherwise tricky to catch, e.g., we might just see a `bad handle passed' error.\" :DEMON-PROPERTY \"sdbc.dbConnectionRenewalInterval\" :PUBLIC? TRUE)"
     NULL)
    (REGISTER-NATIVE-NAME SYM-SDBC-SDBC-DISCONNECT KWD-SDBC-COMMON-LISP
     KWD-SDBC-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-SDBC-SDBC-EXECUTE-SQL
     KWD-SDBC-COMMON-LISP KWD-SDBC-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-SDBC-SDBC-INSERT-ROW KWD-SDBC-COMMON-LISP
     KWD-SDBC-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-SDBC-SDBC-INSERT-ROWS
     KWD-SDBC-COMMON-LISP KWD-SDBC-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-SDBC-SDBC-PREPARE-STATEMENT
     KWD-SDBC-COMMON-LISP KWD-SDBC-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-SDBC-SDBC-BIND-PARAMETER
     KWD-SDBC-COMMON-LISP KWD-SDBC-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-SDBC-SDBC-SET-AUTO-COMMIT
     KWD-SDBC-COMMON-LISP KWD-SDBC-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-SDBC-SDBC-COMMIT KWD-SDBC-COMMON-LISP
     KWD-SDBC-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-SDBC-SDBC-ROLLBACK KWD-SDBC-COMMON-LISP
     KWD-SDBC-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-SDBC-SDBC-GET-TABLES KWD-SDBC-COMMON-LISP
     KWD-SDBC-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-SDBC-SDBC-GET-COLUMNS
     KWD-SDBC-COMMON-LISP KWD-SDBC-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-SDBC-SDBC-GET-SERVER-INFO
     KWD-SDBC-COMMON-LISP KWD-SDBC-FUNCTION)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFSPECIAL *SQL-COMMAND-TEMPLATES* (KEY-VALUE-MAP OF OBJECT (KEY-VALUE-LIST OF OBJECT PROPERTY-LIST)) (NEW KEY-VALUE-MAP))"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *SQL-CMD-TEMPLATE-VARIABLE-PREFIX* STRING \"#$\")"
     NULL))))
