;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; gui-server.lisp

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
|#

(CL:IN-PACKAGE "STELLA")

;;; Auxiliary variables:

(CL:DEFVAR KWD-GUI-SERVER-HIGH NULL)
(CL:DEFVAR KWD-GUI-SERVER-CONTENT-TYPE NULL)
(CL:DEFVAR KWD-GUI-SERVER-XML NULL)
(CL:DEFVAR KWD-GUI-SERVER-DOCUMENTATION NULL)
(CL:DEFVAR SYM-GUI-SERVER-GUI-SERVER-STARTUP-GUI-SERVER NULL)
(CL:DEFVAR SYM-GUI-SERVER-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM (CL:SPECIAL *STARTUP-TIME-PHASE* *MODULE* NIL))

;;; (DEFGLOBAL *GUI-SERVER-MODULE* ...)

(CL:DEFVAR *GUI-SERVER-MODULE* NULL)

;;; (DEFGLOBAL *SOAP-RESULT-PREFIX* ...)

(CL:DEFVAR *SOAP-RESULT-PREFIX* "<?xml version='1.0' encoding='UTF-8'?><env:Envelope xmlns:env='http://schemas.xmlsoap.org/soap/envelope/' xmlns:xsd='http://www.w3.org/2001/XMLSchema' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns:enc='http://schemas.xmlsoap.org/soap/encoding/' xmlns:ns0='http://hello.org/wsdl' env:encodingStyle='http://schemas.xmlsoap.org/soap/encoding/'><env:Body><response><result><![CDATA[")
(CL:DECLAIM (CL:TYPE CL:SIMPLE-STRING *SOAP-RESULT-PREFIX*))

;;; (DEFGLOBAL *SOAP-EXCEPTION-PREFIX* ...)

(CL:DEFVAR *SOAP-EXCEPTION-PREFIX* "<?xml version='1.0' encoding='UTF-8'?><env:Envelope xmlns:env='http://schemas.xmlsoap.org/soap/envelope/' xmlns:xsd='http://www.w3.org/2001/XMLSchema' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns:enc='http://schemas.xmlsoap.org/soap/encoding/' xmlns:ns0='http://hello.org/wsdl' env:encodingStyle='http://schemas.xmlsoap.org/soap/encoding/'><env:Body><response><exception><![CDATA[")
(CL:DECLAIM (CL:TYPE CL:SIMPLE-STRING *SOAP-EXCEPTION-PREFIX*))

;;; (DEFGLOBAL *SOAP-RESULT-SUFFIX* ...)

(CL:DEFVAR *SOAP-RESULT-SUFFIX* "]]></result></response></env:Body></env:Envelope>")
(CL:DECLAIM (CL:TYPE CL:SIMPLE-STRING *SOAP-RESULT-SUFFIX*))

;;; (DEFGLOBAL *SOAP-EXCEPTION-SUFFIX* ...)

(CL:DEFVAR *SOAP-EXCEPTION-SUFFIX* "]]></exception></response></env:Body></env:Envelope>")
(CL:DECLAIM (CL:TYPE CL:SIMPLE-STRING *SOAP-EXCEPTION-SUFFIX*))

;;; (DEFUN (SERVER-PROCESS-SOAP-REQUEST STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:SIMPLE-STRING) CL:SIMPLE-STRING)
  SERVER-PROCESS-SOAP-REQUEST))
(CL:DEFUN SERVER-PROCESS-SOAP-REQUEST (REQUESTBODY)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING REQUESTBODY))
  #+MCL
  (CL:CHECK-TYPE REQUESTBODY CL:SIMPLE-STRING)
  (CL:LET*
   ((EXCEPTION STELLA::NULL-STRING) (REALRESULT "")
    (SOAPRESULT STELLA::NULL-STRING))
   (CL:DECLARE
    (CL:TYPE CL:SIMPLE-STRING EXCEPTION REALRESULT SOAPRESULT))
   (SERVER-LOG KWD-GUI-SERVER-HIGH (WRAP-STRING "Request: ")
    (WRAP-STRING REQUESTBODY))
   (CL:HANDLER-CASE
    (CL:LET*
     ((SOAPTREE (SERVER-PARSE-XML-DOCUMENT-STRING REQUESTBODY))
      (SOAPBODYCONTENTS (SERVER-EXTRACT-SOAP-BODY-CONTENTS SOAPTREE)))
     (CL:SETQ REALRESULT
      (SERVER-INVOKE-POWERLOOM-METHOD SOAPBODYCONTENTS)))
    (LOGIC-EXCEPTION (E)
     (CL:SETQ EXCEPTION
      (SERVER-MARSHAL-EXCEPTION "PowerLoom Error" E)))
    (STELLA-EXCEPTION (E)
     (CL:SETQ EXCEPTION (SERVER-MARSHAL-EXCEPTION "STELLA Error" E)))
    (CL:CONDITION (E)
     (CL:SETQ EXCEPTION
      (SERVER-MARSHAL-EXCEPTION "Internal Error" E))))
   (CL:SETQ SOAPRESULT
    (SERVER-GENERATE-SOAP-RESPONSE REALRESULT EXCEPTION))
   (SERVER-LOG KWD-GUI-SERVER-HIGH (WRAP-STRING "Response: ")
    (WRAP-STRING SOAPRESULT))
   SOAPRESULT))

;;; (DEFUN (SERVER-MARSHAL-EXCEPTION STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:SIMPLE-STRING CL:T) CL:SIMPLE-STRING)
  SERVER-MARSHAL-EXCEPTION))
(CL:DEFUN SERVER-MARSHAL-EXCEPTION (TYPE EXCEPTION)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TYPE))
  #+MCL
  (CL:CHECK-TYPE TYPE CL:SIMPLE-STRING)
  (CL:LET*
   ((MESSAGE (EXCEPTION-MESSAGE EXCEPTION))
    (SERVEREXCEPTION (|new-ServerException|))
    (XMLSTRING STELLA::NULL-STRING))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING MESSAGE XMLSTRING))
   (CL:SETF (|%Message| SERVEREXCEPTION) MESSAGE)
   (CL:SETF (|%Type| SERVEREXCEPTION) TYPE)
   (CL:SETQ XMLSTRING (TO-XML-STRING SERVEREXCEPTION)) XMLSTRING))

;;; (DEFUN (SERVER-GENERATE-SOAP-RESPONSE STRING) ...)

(CL:DECLAIM
 (CL:FTYPE
  (CL:FUNCTION (CL:SIMPLE-STRING CL:SIMPLE-STRING) CL:SIMPLE-STRING)
  SERVER-GENERATE-SOAP-RESPONSE))
(CL:DEFUN SERVER-GENERATE-SOAP-RESPONSE (RESPONSE EXCEPTION)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING RESPONSE EXCEPTION))
  #+MCL
  (CL:CHECK-TYPE RESPONSE CL:SIMPLE-STRING)
  #+MCL
  (CL:CHECK-TYPE EXCEPTION CL:SIMPLE-STRING)
  (CL:IF (CL:NOT (CL:EQ EXCEPTION STELLA::NULL-STRING))
   (CONCATENATE *SOAP-EXCEPTION-PREFIX* EXCEPTION
    *SOAP-EXCEPTION-SUFFIX*)
   (CONCATENATE *SOAP-RESULT-PREFIX* RESPONSE *SOAP-RESULT-SUFFIX*)))

;;; (DEFUN (SERVER-PARSE-XML-DOCUMENT-STRING (CONS OF CONS)) ...)

(CL:DEFUN SERVER-PARSE-XML-DOCUMENT-STRING (REQUEST)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING REQUEST))
  #+MCL
  (CL:CHECK-TYPE REQUEST CL:SIMPLE-STRING)
  (CL:LET* ((VALUE-000 NIL))
   (CL:LET*
    ((ITEM NULL)
     (ITER-000
      (XML-EXPRESSIONS (NEW-INPUT-STRING-STREAM REQUEST) NULL))
     (COLLECT-000 NULL))
    (CL:LOOP WHILE (NEXT? ITER-000) DO (CL:SETQ ITEM (%VALUE ITER-000))
     (CL:IF (CL:EQ COLLECT-000 NULL)
      (CL:PROGN (CL:SETQ COLLECT-000 (CONS ITEM NIL))
       (CL:IF (CL:EQ VALUE-000 NIL) (CL:SETQ VALUE-000 COLLECT-000)
        (ADD-CONS-TO-END-OF-CONS-LIST VALUE-000 COLLECT-000)))
      (CL:PROGN (CL:SETF (%%REST COLLECT-000) (CONS ITEM NIL))
       (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))))
   (CL:LET* ((VALUE-001 VALUE-000)) VALUE-001)))

;;; (DEFUN (SERVER-EXTRACT-SOAP-BODY-CONTENTS OBJECT) ...)

(CL:DEFUN SERVER-EXTRACT-SOAP-BODY-CONTENTS (PARSETREE)
  (CL:LET*
   ((BODY (%%VALUE (%%REST (%%REST (%%VALUE PARSETREE)))))
    (BODYCONTENTS (%%VALUE (%%REST (%%REST BODY)))))
   BODYCONTENTS))

;;; (DEFUN (SERVER-EXTRACT-METHOD-NAME STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T) CL:SIMPLE-STRING)
  SERVER-EXTRACT-METHOD-NAME))
(CL:DEFUN SERVER-EXTRACT-METHOD-NAME (BODYCONTENTS)
  (%NAME (%%VALUE BODYCONTENTS)))

;;; (DEFUN (SERVER-EXTRACT-ARGUMENTS (CONS OF OBJECT)) ...)

(CL:DEFUN SERVER-EXTRACT-ARGUMENTS (BODYCONTENTS)
  (CL:LET* ((*DEFAULT-XML-OBJECT-MODULE* *GUI-SERVER-MODULE*))
   (CL:DECLARE (CL:SPECIAL *DEFAULT-XML-OBJECT-MODULE*))
   (CL:LET* ((RAWARGS (%%REST (%%REST BODYCONTENTS))) (RESULT NIL))
    (CL:LET* ((ARG NULL) (ITER-000 RAWARGS) (COLLECT-000 NULL))
     (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
      (CL:SETQ ARG (%%VALUE ITER-000))
      (CL:IF (CL:EQ COLLECT-000 NULL)
       (CL:PROGN
        (CL:SETQ COLLECT-000
         (CONS
          (FROM-XML-STRING
           (%WRAPPER-VALUE (%%VALUE (%%REST (%%REST ARG)))))
          NIL))
        (CL:IF (CL:EQ RESULT NIL) (CL:SETQ RESULT COLLECT-000)
         (ADD-CONS-TO-END-OF-CONS-LIST RESULT COLLECT-000)))
       (CL:PROGN
        (CL:SETF (%%REST COLLECT-000)
         (CONS
          (FROM-XML-STRING
           (%WRAPPER-VALUE (%%VALUE (%%REST (%%REST ARG)))))
          NIL))
        (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))
      (CL:SETQ ITER-000 (%%REST ITER-000))))
    RESULT)))

;;; (DEFUN (SERVER-INVOKE-POWERLOOM-METHOD STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T) CL:SIMPLE-STRING)
  SERVER-INVOKE-POWERLOOM-METHOD))
(CL:DEFUN SERVER-INVOKE-POWERLOOM-METHOD (BODYCONTENTS)
  (CL:LET*
   ((METHODNAME (SERVER-EXTRACT-METHOD-NAME BODYCONTENTS))
    (ARGUMENTS (SERVER-EXTRACT-ARGUMENTS BODYCONTENTS))
    (RESULT (DISPATCH-CALL METHODNAME ARGUMENTS))
    (MARSHALEDRESULT (TO-XML-STRING RESULT)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING METHODNAME MARSHALEDRESULT))
   MARSHALEDRESULT))

;;; (DEFUN GUI-REQUEST-HANDLER ...)

(CL:DEFUN GUI-REQUEST-HANDLER (XCHG)
  (CL:LET*
   ((REQUEST (GET-REQUEST-BODY XCHG))
    (RESPONSE (SERVER-PROCESS-SOAP-REQUEST REQUEST)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING REQUEST RESPONSE))
   (%%PRINT-STREAM (GET-REPLY-STREAM XCHG) RESPONSE)))

(CL:DEFUN STARTUP-GUI-SERVER ()
  (CL:LET*
   ((*MODULE*
     (GET-STELLA-MODULE "/POWERLOOM-SERVER/GUI-SERVER"
      (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2)
    (CL:SETQ KWD-GUI-SERVER-HIGH
     (INTERN-RIGID-SYMBOL-WRT-MODULE "HIGH" NULL 2))
    (CL:SETQ KWD-GUI-SERVER-CONTENT-TYPE
     (INTERN-RIGID-SYMBOL-WRT-MODULE "CONTENT-TYPE" NULL 2))
    (CL:SETQ KWD-GUI-SERVER-XML
     (INTERN-RIGID-SYMBOL-WRT-MODULE "XML" NULL 2))
    (CL:SETQ KWD-GUI-SERVER-DOCUMENTATION
     (INTERN-RIGID-SYMBOL-WRT-MODULE "DOCUMENTATION" NULL 2))
    (CL:SETQ SYM-GUI-SERVER-GUI-SERVER-STARTUP-GUI-SERVER
     (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-GUI-SERVER" NULL 0))
    (CL:SETQ SYM-GUI-SERVER-STELLA-METHOD-STARTUP-CLASSNAME
     (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 4)
    (CL:SETQ *GUI-SERVER-MODULE*
     (GET-STELLA-MODULE "GUI-SERVER" CL:T)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7)
    (DEFINE-FUNCTION-OBJECT "SERVER-PROCESS-SOAP-REQUEST"
     "(DEFUN (SERVER-PROCESS-SOAP-REQUEST STRING) ((REQUESTBODY STRING)))"
     (CL:FUNCTION SERVER-PROCESS-SOAP-REQUEST) NULL)
    (DEFINE-FUNCTION-OBJECT "SERVER-MARSHAL-EXCEPTION"
     "(DEFUN (SERVER-MARSHAL-EXCEPTION STRING) ((TYPE STRING) (EXCEPTION NATIVE-EXCEPTION)))"
     (CL:FUNCTION SERVER-MARSHAL-EXCEPTION) NULL)
    (DEFINE-FUNCTION-OBJECT "SERVER-GENERATE-SOAP-RESPONSE"
     "(DEFUN (SERVER-GENERATE-SOAP-RESPONSE STRING) ((RESPONSE STRING) (EXCEPTION STRING)))"
     (CL:FUNCTION SERVER-GENERATE-SOAP-RESPONSE) NULL)
    (DEFINE-FUNCTION-OBJECT "SERVER-PARSE-XML-DOCUMENT-STRING"
     "(DEFUN (SERVER-PARSE-XML-DOCUMENT-STRING (CONS OF CONS)) ((REQUEST STRING)))"
     (CL:FUNCTION SERVER-PARSE-XML-DOCUMENT-STRING) NULL)
    (DEFINE-FUNCTION-OBJECT "SERVER-EXTRACT-SOAP-BODY-CONTENTS"
     "(DEFUN (SERVER-EXTRACT-SOAP-BODY-CONTENTS OBJECT) ((PARSETREE (CONS OF CONS))))"
     (CL:FUNCTION SERVER-EXTRACT-SOAP-BODY-CONTENTS) NULL)
    (DEFINE-FUNCTION-OBJECT "SERVER-EXTRACT-METHOD-NAME"
     "(DEFUN (SERVER-EXTRACT-METHOD-NAME STRING) ((BODYCONTENTS CONS)))"
     (CL:FUNCTION SERVER-EXTRACT-METHOD-NAME) NULL)
    (DEFINE-FUNCTION-OBJECT "SERVER-EXTRACT-ARGUMENTS"
     "(DEFUN (SERVER-EXTRACT-ARGUMENTS (CONS OF OBJECT)) ((BODYCONTENTS CONS)))"
     (CL:FUNCTION SERVER-EXTRACT-ARGUMENTS) NULL)
    (DEFINE-FUNCTION-OBJECT "SERVER-INVOKE-POWERLOOM-METHOD"
     "(DEFUN (SERVER-INVOKE-POWERLOOM-METHOD STRING) ((BODYCONTENTS CONS)))"
     (CL:FUNCTION SERVER-INVOKE-POWERLOOM-METHOD) NULL)
    (DEFINE-FUNCTION-OBJECT "GUI-REQUEST-HANDLER"
     "(DEFUN GUI-REQUEST-HANDLER ((XCHG /HTTP/HTTP-EXCHANGE)))"
     (CL:FUNCTION GUI-REQUEST-HANDLER) NULL)
    (DEFINE-FUNCTION-OBJECT "STARTUP-GUI-SERVER"
     "(DEFUN STARTUP-GUI-SERVER () :PUBLIC? TRUE)"
     (CL:FUNCTION STARTUP-GUI-SERVER) NULL)
    (CL:LET*
     ((FUNCTION
       (LOOKUP-FUNCTION SYM-GUI-SERVER-GUI-SERVER-STARTUP-GUI-SERVER)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-GUI-SERVER-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupGuiServer") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "GUI-SERVER")))
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *GUI-SERVER-MODULE* MODULE (GET-STELLA-MODULE \"GUI-SERVER\" TRUE))"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *SOAP-RESULT-PREFIX* STRING \"<?xml version='1.0' encoding='UTF-8'?><env:Envelope xmlns:env='http://schemas.xmlsoap.org/soap/envelope/' xmlns:xsd='http://www.w3.org/2001/XMLSchema' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns:enc='http://schemas.xmlsoap.org/soap/encoding/' xmlns:ns0='http://hello.org/wsdl' env:encodingStyle='http://schemas.xmlsoap.org/soap/encoding/'><env:Body><response><result><![CDATA[\")"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *SOAP-EXCEPTION-PREFIX* STRING \"<?xml version='1.0' encoding='UTF-8'?><env:Envelope xmlns:env='http://schemas.xmlsoap.org/soap/envelope/' xmlns:xsd='http://www.w3.org/2001/XMLSchema' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns:enc='http://schemas.xmlsoap.org/soap/encoding/' xmlns:ns0='http://hello.org/wsdl' env:encodingStyle='http://schemas.xmlsoap.org/soap/encoding/'><env:Body><response><exception><![CDATA[\")"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *SOAP-RESULT-SUFFIX* STRING \"]]></result></response></env:Body></env:Envelope>\")"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *SOAP-EXCEPTION-SUFFIX* STRING \"]]></exception></response></env:Body></env:Envelope>\")"
     NULL)
    (PUBLISH-HANDLER "/ploom/soap-rpc/powerloom-gui-service"
     (CL:FUNCTION GUI-REQUEST-HANDLER) KWD-GUI-SERVER-CONTENT-TYPE
     (WRAP-STRING (GET-HTTP-MIME-TYPE KWD-GUI-SERVER-XML NULL))
     KWD-GUI-SERVER-DOCUMENTATION
     (WRAP-STRING "SOAP service for PowerLoom GUI.")))))
