;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; soap.lisp

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
|#

(CL:IN-PACKAGE "STELLA")

;;; Auxiliary variables:

(CL:DEFVAR KWD-SOAP-CONTENT-TYPE NULL)
(CL:DEFVAR KWD-SOAP-XML NULL)
(CL:DEFVAR KWD-SOAP-DOCUMENTATION NULL)
(CL:DEFVAR KWD-SOAP-METHOD NULL)
(CL:DEFVAR KWD-SOAP-POST NULL)
(CL:DEFVAR KWD-SOAP-HEADERS NULL)
(CL:DEFVAR KWD-SOAP-CONTENT NULL)
(CL:DEFVAR SYM-SOAP-SOAP-STARTUP-SOAP NULL)
(CL:DEFVAR SYM-SOAP-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM
 (CL:SPECIAL *STARTUP-TIME-PHASE* *MODULE* STANDARD-OUTPUT EOL NIL))

;;; (DEFCLASS SOAP-FAULT-EXCEPTION ...)

(CL:DEFINE-CONDITION SOAP-FAULT-EXCEPTION (STELLA-EXCEPTION)
  ((FAULT :ALLOCATION :INSTANCE :ACCESSOR %FAULT)))

(CL:DEFUN NEW-SOAP-FAULT-EXCEPTION (MESSAGE)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING MESSAGE))
  #+MCL
  (CL:CHECK-TYPE MESSAGE CL:SIMPLE-STRING)
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF
    (CL:MAKE-CONDITION (CL:QUOTE SOAP-FAULT-EXCEPTION)
     *CONDITION-MESSAGE-KEYWORD*
     (REPLACE-SUBSTRINGS MESSAGE "~~" "~")))
   (CL:SETF (%FAULT SELF) NULL) SELF))

;;; (DEFUN PROCESS-SOAP-RPC-REQUEST ...)

(CL:DEFUN PROCESS-SOAP-RPC-REQUEST (SOAPSTRING SUPRESSNAMESPACES? STREAM)
  "'envelope' is a string-representation of SOAP envelope containing an
RPC request.  This functions writes a SOAP envelope containing a service response to `stream'."
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SOAPSTRING))
  #+MCL
  (CL:CHECK-TYPE SOAPSTRING CL:SIMPLE-STRING)
  (CL:LET*
   ((SOAPOBJECT (FROM-XML-STRING SOAPSTRING))
    (RESULTOBJECT (DISPATCH-RPC-CALL SOAPOBJECT)))
   (CL:LET* ((*SUPRESS-NAMESPACES?* SUPRESSNAMESPACES?))
    (CL:DECLARE (CL:SPECIAL *SUPRESS-NAMESPACES?*))
    (PRINT-XML-EXPRESSION STREAM (TO-XML RESULTOBJECT NIL) 0))))

;;; (DEFUN (GET-RPC-METHOD SYMBOL) ...)

(CL:DEFUN GET-RPC-METHOD (ENVELOPE)
  (CL:LET*
   ((CONTENTS (|%contents| (|%body| ENVELOPE)))
    (TYPE (PRIMARY-TYPE CONTENTS)))
   (INTERN-SYMBOL-IN-MODULE (%SYMBOL-NAME TYPE) (%HOME-CONTEXT TYPE)
    CL:T)))

;;; (DEFUN (GET-RPC-ARGUMENTS (CONS OF |XMLObject|)) ...)

(CL:DEFUN GET-RPC-ARGUMENTS (ENVELOPE)
  (CL:LET* ((RESULT NIL) (CONTENTS (|%contents| (|%body| ENVELOPE))))
   (CL:LET*
    ((SLOT NULL)
     (ITER-000 (%THE-CONS-LIST (GET-MAPPED-SLOTS CONTENTS)))
     (COLLECT-000 NULL))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ SLOT (%%VALUE ITER-000))
     (CL:WHEN (ELEMENT-SLOT? SLOT)
      (CL:IF (CL:EQ COLLECT-000 NULL)
       (CL:PROGN
        (CL:SETQ COLLECT-000
         (CONS (GET-OBJECT-SLOT-VALUE CONTENTS SLOT) NIL))
        (CL:IF (CL:EQ RESULT NIL) (CL:SETQ RESULT COLLECT-000)
         (ADD-CONS-TO-END-OF-CONS-LIST RESULT COLLECT-000)))
       (CL:PROGN
        (CL:SETF (%%REST COLLECT-000)
         (CONS (GET-OBJECT-SLOT-VALUE CONTENTS SLOT) NIL))
        (CL:SETQ COLLECT-000 (%%REST COLLECT-000)))))
     (CL:SETQ ITER-000 (%%REST ITER-000))))
   RESULT))

;;; (DEFUN (DISPATCH-RPC-CALL |Envelope|) ...)

(CL:DEFUN DISPATCH-RPC-CALL (ENVELOPE)
  (CL:LET*
   ((METHOD (GET-RPC-METHOD ENVELOPE))
    (ARGUMENTS (GET-RPC-ARGUMENTS ENVELOPE))
    (RESULT (DISPATCH-CALL-WITH-METHOD-AND-ARGS METHOD ARGUMENTS)))
   RESULT))

;;; (DEFUN (DISPATCH-CALL-WITH-METHOD-AND-ARGS |Envelope|) ...)

(CL:DEFUN DISPATCH-CALL-WITH-METHOD-AND-ARGS (METHODNAME ARGUMENTS)
  (CL:LET*
   ((FUNCTION (%FUNCTION-CODE (LOOKUP-FUNCTION METHODNAME)))
    (RAWRESULT (APPLY FUNCTION ARGUMENTS))
    (PACKAGEDRESULT (CREATE-SOAP-ENVELOPE RAWRESULT)))
   PACKAGEDRESULT))

;;; (DEFUN (CREATE-SOAP-ENVELOPE |Envelope|) ...)

(CL:DEFUN CREATE-SOAP-ENVELOPE (CONTENTS)
  (CL:LET* ((SELF-000 (|new-Body|)))
   (CL:SETF (|%contents| SELF-000) CONTENTS)
   (CL:LET* ((BODY SELF-000))
    (CL:LET* ((SELF-001 (|new-Envelope|)))
     (CL:SETF (|%body| SELF-001) BODY)
     (CL:LET* ((RESULT SELF-001)) RESULT)))))

;;; (DEFUN (CREATE-SOAP-FAULT |Fault|) ...)

(CL:DEFUN CREATE-SOAP-FAULT (FCODE FSTRING FACTOR FDETAIL)
  "Create a SOAP Fault object.  `fcode' and `fstring' are required.
`factor' and `fdetail' are optional fields.  Fault code should be one of
\"SOAP-ENV:VersionMismatch\", \"SOAP-ENV:MustUnderstand\" \"SOAP-ENV:Client\" or
\"SOAP-ENV:Server\".  These may change to keywords in the future."
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING FCODE FSTRING FACTOR))
  #+MCL
  (CL:CHECK-TYPE FCODE CL:SIMPLE-STRING)
  #+MCL
  (CL:CHECK-TYPE FSTRING CL:SIMPLE-STRING)
  #+MCL
  (CL:CHECK-TYPE FACTOR CL:SIMPLE-STRING)
  (CL:LET* ((SELF-000 (|new-Fault|)))
   (CL:LET* ((SELF-001 (|new-FaultCode|)))
    (CL:SETF (|%textContent| SELF-001) FCODE)
    (CL:SETF (|%faultcode| SELF-000) SELF-001))
   (CL:LET* ((SELF-002 (|new-FaultString|)))
    (CL:SETF (|%textContent| SELF-002) FSTRING)
    (CL:SETF (|%faultstring| SELF-000) SELF-002))
   (CL:LET* ((FAULT SELF-000))
    (CL:WHEN (CL:NOT (CL:EQ FACTOR STELLA::NULL-STRING))
     (CL:LET* ((SELF-003 (|new-FaultActor|)))
      (CL:SETF (|%textContent| SELF-003) FACTOR)
      (CL:SETF (|%faultactor| FAULT) SELF-003)))
    (CL:WHEN (CL:NOT (CL:EQ FDETAIL NULL))
     (CL:LET* ((SELF-004 (|new-Detail|)))
      (CL:SETF (|%contents| SELF-004) FDETAIL)
      (CL:SETF (|%detail| FAULT) SELF-004)))
    FAULT)))

;;; (DEFUN SOAP-RPC-REQUEST-HANDLER ...)

(CL:DEFUN SOAP-RPC-REQUEST-HANDLER (XCHG)
  "Handle a request encoded by a SOAP message envelope in the body of an HTTP POST
command, unpack the envelope, dispatch the request, and return the result as SOAP envelope."
  (CL:LET* ((SELF-000 (NEW-OUTPUT-STREAM)))
   (CL:SETF (%NATIVE-STREAM SELF-000) (GET-REPLY-STREAM XCHG))
   (CL:LET* ((REPLY SELF-000))
    (PROCESS-SOAP-RPC-REQUEST (GET-REQUEST-BODY XCHG) CL:T REPLY))))

;;; (DEFUN (CALL-WEBSERVICE |XMLObject|) ...)

(CL:DEFUN CALL-WEBSERVICE (CALLOBJECT URL)
  "Package `callObject' into a SOAP envelope, send it to the webservice at `url'."
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING URL))
  #+MCL
  (CL:CHECK-TYPE URL CL:SIMPLE-STRING)
  (CL:LET*
   ((DEBUG? CL:T)
    (REQUESTENVELOPEOBJECT (CREATE-SOAP-ENVELOPE CALLOBJECT))
    (REQUESTSTRING (TO-XML-STRING REQUESTENVELOPEOBJECT))
    (HEADERS (MAKE-SOAP-RPC-REQUEST-HEADERS))
    (RESPONSEENVELOPESTRING
     (%DO-HTTP-REQUEST URL
      (CONS-LIST KWD-SOAP-METHOD KWD-SOAP-POST KWD-SOAP-HEADERS HEADERS
       KWD-SOAP-CONTENT (WRAP-STRING REQUESTSTRING))))
    (RESPONSEENVELOPEOBJECT (FROM-XML-STRING RESPONSEENVELOPESTRING))
    (RESPONSEOBJECT (|%contents| (|%body| RESPONSEENVELOPEOBJECT))))
   (CL:DECLARE
    (CL:TYPE CL:SIMPLE-STRING REQUESTSTRING RESPONSEENVELOPESTRING))
   (CL:WHEN DEBUG?
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     "response received: " EOL RESPONSEENVELOPESTRING EOL))
   RESPONSEOBJECT))

;;; (DEFUN (MAKE-SOAP-RPC-REQUEST-HEADERS HTTP-HEADERS) ...)

(CL:DEFUN MAKE-SOAP-RPC-REQUEST-HEADERS ()
  (CL:LET* ((RESULT (NEW-KEY-VALUE-LIST)))
   (INSERT-AT RESULT (WRAP-STRING "content-type")
    (WRAP-STRING "text/xml; charset=utf-8"))
   (INSERT-AT RESULT (WRAP-STRING "SoapAction") (WRAP-STRING ""))
   RESULT))

(CL:DEFUN STARTUP-SOAP ()
  (CL:LET*
   ((*MODULE* (GET-STELLA-MODULE "/SOAP" (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2)
    (CL:SETQ KWD-SOAP-CONTENT-TYPE
     (INTERN-RIGID-SYMBOL-WRT-MODULE "CONTENT-TYPE" NULL 2))
    (CL:SETQ KWD-SOAP-XML
     (INTERN-RIGID-SYMBOL-WRT-MODULE "XML" NULL 2))
    (CL:SETQ KWD-SOAP-DOCUMENTATION
     (INTERN-RIGID-SYMBOL-WRT-MODULE "DOCUMENTATION" NULL 2))
    (CL:SETQ KWD-SOAP-METHOD
     (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD" NULL 2))
    (CL:SETQ KWD-SOAP-POST
     (INTERN-RIGID-SYMBOL-WRT-MODULE "POST" NULL 2))
    (CL:SETQ KWD-SOAP-HEADERS
     (INTERN-RIGID-SYMBOL-WRT-MODULE "HEADERS" NULL 2))
    (CL:SETQ KWD-SOAP-CONTENT
     (INTERN-RIGID-SYMBOL-WRT-MODULE "CONTENT" NULL 2))
    (CL:SETQ SYM-SOAP-SOAP-STARTUP-SOAP
     (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-SOAP" NULL 0))
    (CL:SETQ SYM-SOAP-STELLA-METHOD-STARTUP-CLASSNAME
     (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 5)
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "SOAP-FAULT-EXCEPTION"
        "(DEFCLASS SOAP-FAULT-EXCEPTION (STELLA-EXCEPTION) :PUBLIC-SLOTS ((FAULT :TYPE |Fault|)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION NEW-SOAP-FAULT-EXCEPTION))))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7)
    (DEFINE-FUNCTION-OBJECT "PROCESS-SOAP-RPC-REQUEST"
     "(DEFUN PROCESS-SOAP-RPC-REQUEST ((SOAPSTRING STRING) (SUPRESSNAMESPACES? BOOLEAN) (STREAM OUTPUT-STREAM)) :DOCUMENTATION \"'envelope' is a string-representation of SOAP envelope containing an
RPC request.  This functions writes a SOAP envelope containing a service response to `stream'.\" :PUBLIC? TRUE)"
     (CL:FUNCTION PROCESS-SOAP-RPC-REQUEST) NULL)
    (DEFINE-FUNCTION-OBJECT "GET-RPC-METHOD"
     "(DEFUN (GET-RPC-METHOD SYMBOL) ((ENVELOPE |Envelope|)))"
     (CL:FUNCTION GET-RPC-METHOD) NULL)
    (DEFINE-FUNCTION-OBJECT "GET-RPC-ARGUMENTS"
     "(DEFUN (GET-RPC-ARGUMENTS (CONS OF |XMLObject|)) ((ENVELOPE |Envelope|)))"
     (CL:FUNCTION GET-RPC-ARGUMENTS) NULL)
    (DEFINE-FUNCTION-OBJECT "DISPATCH-RPC-CALL"
     "(DEFUN (DISPATCH-RPC-CALL |Envelope|) ((ENVELOPE |Envelope|)))"
     (CL:FUNCTION DISPATCH-RPC-CALL) NULL)
    (DEFINE-FUNCTION-OBJECT "DISPATCH-CALL-WITH-METHOD-AND-ARGS"
     "(DEFUN (DISPATCH-CALL-WITH-METHOD-AND-ARGS |Envelope|) ((METHODNAME SYMBOL) (ARGUMENTS (CONS OF |XMLObject|))))"
     (CL:FUNCTION DISPATCH-CALL-WITH-METHOD-AND-ARGS) NULL)
    (DEFINE-FUNCTION-OBJECT "CREATE-SOAP-ENVELOPE"
     "(DEFUN (CREATE-SOAP-ENVELOPE |Envelope|) ((CONTENTS |XMLObject|)))"
     (CL:FUNCTION CREATE-SOAP-ENVELOPE) NULL)
    (DEFINE-FUNCTION-OBJECT "CREATE-SOAP-FAULT"
     "(DEFUN (CREATE-SOAP-FAULT |Fault|) ((FCODE STRING) (FSTRING STRING) (FACTOR STRING) (FDETAIL |XMLObject|)) :DOCUMENTATION \"Create a SOAP Fault object.  `fcode' and `fstring' are required.
`factor' and `fdetail' are optional fields.  Fault code should be one of
\\\"SOAP-ENV:VersionMismatch\\\", \\\"SOAP-ENV:MustUnderstand\\\" \\\"SOAP-ENV:Client\\\" or
\\\"SOAP-ENV:Server\\\".  These may change to keywords in the future.\" :PUBLIC? TRUE)"
     (CL:FUNCTION CREATE-SOAP-FAULT) NULL)
    (DEFINE-FUNCTION-OBJECT "SOAP-RPC-REQUEST-HANDLER"
     "(DEFUN SOAP-RPC-REQUEST-HANDLER ((XCHG HTTP-EXCHANGE)) :DOCUMENTATION \"Handle a request encoded by a SOAP message envelope in the body of an HTTP POST
command, unpack the envelope, dispatch the request, and return the result as SOAP envelope.\" :PUBLIC? TRUE)"
     (CL:FUNCTION SOAP-RPC-REQUEST-HANDLER) NULL)
    (DEFINE-FUNCTION-OBJECT "CALL-WEBSERVICE"
     "(DEFUN (CALL-WEBSERVICE |XMLObject|) ((CALLOBJECT |XMLObject|) (URL STRING)) :DOCUMENTATION \"Package `callObject' into a SOAP envelope, send it to the webservice at `url'.\" :PUBLIC? TRUE)"
     (CL:FUNCTION CALL-WEBSERVICE) NULL)
    (DEFINE-FUNCTION-OBJECT "MAKE-SOAP-RPC-REQUEST-HEADERS"
     "(DEFUN (MAKE-SOAP-RPC-REQUEST-HEADERS HTTP-HEADERS) ())"
     (CL:FUNCTION MAKE-SOAP-RPC-REQUEST-HEADERS) NULL)
    (DEFINE-FUNCTION-OBJECT "STARTUP-SOAP"
     "(DEFUN STARTUP-SOAP () :PUBLIC? TRUE)" (CL:FUNCTION STARTUP-SOAP)
     NULL)
    (CL:LET* ((FUNCTION (LOOKUP-FUNCTION SYM-SOAP-SOAP-STARTUP-SOAP)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-SOAP-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupSoap") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "SOAP")))
    (PUBLISH-HANDLER "/ploom/soap-rpc/generic-soap-service"
     (CL:FUNCTION SOAP-RPC-REQUEST-HANDLER) KWD-SOAP-CONTENT-TYPE
     (WRAP-STRING (GET-HTTP-MIME-TYPE KWD-SOAP-XML NULL))
     KWD-SOAP-DOCUMENTATION (WRAP-STRING "Generic SOAP RPC handler.")))))
