;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; fetch-demo.lisp

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

(CL:DEFVAR |SGT-FETCH-DEMO-FETCH-runAgentAndWaitForResponse| NULL)
(CL:DEFVAR |SYM-FETCH-DEMO-FETCH-arg0| NULL)
(CL:DEFVAR |SYM-FETCH-DEMO-FETCH-arg1| NULL)
(CL:DEFVAR |SYM-FETCH-DEMO-FETCH-arg2| NULL)
(CL:DEFVAR |SGT-FETCH-DEMO-FETCH-runAgentAndWaitForResponseResponse| NULL)
(CL:DEFVAR |SYM-FETCH-DEMO-FETCH-return| NULL)
(CL:DEFVAR |SGT-FETCH-DEMO-FETCH-runAgentAndWaitForResponseReturn| NULL)
(CL:DEFVAR |SYM-FETCH-DEMO-XSI-type| NULL)
(CL:DEFVAR KWD-FETCH-DEMO-METHOD NULL)
(CL:DEFVAR KWD-FETCH-DEMO-POST NULL)
(CL:DEFVAR KWD-FETCH-DEMO-HEADERS NULL)
(CL:DEFVAR KWD-FETCH-DEMO-CONTENT NULL)
(CL:DEFVAR SYM-FETCH-DEMO-FETCH-STARTUP-FETCH-DEMO NULL)
(CL:DEFVAR SYM-FETCH-DEMO-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM
 (CL:SPECIAL *STARTUP-TIME-PHASE* *MODULE* STANDARD-OUTPUT EOL))

;;; (DEFCLASS runAgentAndWaitForResponse ...)

(CL:DEFCLASS |runAgentAndWaitForResponse| (|XMLObject|)
  ((|arg0| :ALLOCATION :INSTANCE :ACCESSOR |%arg0|)
   (|arg1| :ALLOCATION :INSTANCE :ACCESSOR |%arg1|)
   (|arg2| :ALLOCATION :INSTANCE :ACCESSOR |%arg2|)))

(CL:DEFUN |new-runAgentAndWaitForResponse| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF
    (CL:MAKE-INSTANCE (CL:QUOTE |runAgentAndWaitForResponse|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%arg2| SELF) NULL) (CL:SETF (|%arg1| SELF) NULL)
   (CL:SETF (|%arg0| SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |runAgentAndWaitForResponse|))
  |SGT-FETCH-DEMO-FETCH-runAgentAndWaitForResponse|)

(CL:DEFUN |access-runAgentAndWaitForResponse-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-FETCH-DEMO-FETCH-arg0|)
    (CL:IF SETVALUE? (CL:SETF (|%arg0| SELF) VALUE)
     (CL:SETQ VALUE (|%arg0| SELF))))
   ((CL:EQ SLOTNAME |SYM-FETCH-DEMO-FETCH-arg1|)
    (CL:IF SETVALUE? (CL:SETF (|%arg1| SELF) VALUE)
     (CL:SETQ VALUE (|%arg1| SELF))))
   ((CL:EQ SLOTNAME |SYM-FETCH-DEMO-FETCH-arg2|)
    (CL:IF SETVALUE? (CL:SETF (|%arg2| SELF) VALUE)
     (CL:SETQ VALUE (|%arg2| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS runAgentAndWaitForResponseResponse ...)

(CL:DEFCLASS |runAgentAndWaitForResponseResponse| (|XMLObject|)
  ((|return| :ALLOCATION :INSTANCE :ACCESSOR |%return|)))

(CL:DEFUN |new-runAgentAndWaitForResponseResponse| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF
    (CL:MAKE-INSTANCE (CL:QUOTE |runAgentAndWaitForResponseResponse|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%return| SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |runAgentAndWaitForResponseResponse|))
  |SGT-FETCH-DEMO-FETCH-runAgentAndWaitForResponseResponse|)

(CL:DEFUN |access-runAgentAndWaitForResponseResponse-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-FETCH-DEMO-FETCH-return|)
    (CL:IF SETVALUE? (CL:SETF (|%return| SELF) VALUE)
     (CL:SETQ VALUE (|%return| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS runAgentAndWaitForResponseReturn ...)

(CL:DEFCLASS |runAgentAndWaitForResponseReturn| (|XMLObject|)
  ((|type| :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR |%type|)))

(CL:DEFUN |new-runAgentAndWaitForResponseReturn| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF
    (CL:MAKE-INSTANCE (CL:QUOTE |runAgentAndWaitForResponseReturn|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%type| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |runAgentAndWaitForResponseReturn|))
  |SGT-FETCH-DEMO-FETCH-runAgentAndWaitForResponseReturn|)

(CL:DEFUN |access-runAgentAndWaitForResponseReturn-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-FETCH-DEMO-XSI-type|)
    (CL:IF SETVALUE? (CL:SETF (|%type| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (|%type| SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFGLOBAL *FETCH-REQUEST1* ...)

(CL:DEFVAR *FETCH-REQUEST1* "<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">
 <soapenv:Body>
  <ns1:runAgentAndWaitForResponse soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:ns1=\"http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService/\">
   <arg0 xsi:type=\"xsd:string\">eeld/gettygeonames/plans/production</arg0>     
   <arg1 href=\"#id0\"/>
   <arg2 href=\"#id1\"/>
  </ns1:runAgentAndWaitForResponse>
  <multiRef id=\"id0\" soapenc:root=\"0\" soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xsi:type=\"ns2:Map\" xmlns:soapenc=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:ns2=\"http://xml.apache.org/xml-soap\">
   <item>
    <key xsi:type=\"xsd:string\">keywords</key>		
    <value xsi:type=\"xsd:string\">Marina Del Rey</value>
   </item>
  </multiRef>
  <multiRef id=\"id1\" soapenc:root=\"0\" soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xsi:type=\"ns3:Map\" xmlns:ns3=\"http://xml.apache.org/xml-soap\" xmlns:soapenc=\"http://schemas.xmlsoap.org/soap/encoding/\"/>
 </soapenv:Body>
</soapenv:Envelope>")
(CL:DECLAIM (CL:TYPE CL:SIMPLE-STRING *FETCH-REQUEST1*))

;;; (DEFGLOBAL *FETCH-REQUEST2* ...)

(CL:DEFVAR *FETCH-REQUEST2* "<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">
 <soapenv:Body>
  <ns1:runAgentAndWaitForResponse soapenv:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\" xmlns:ns1=\"http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService/\">
   <arg0 xsi:type=\"xsd:string\">eeld/gettygeonames/plans/production</arg0>     
   <arg1>
     <item>
       <key xsi:type=\"xsd:string\">keywords</key>		
       <value xsi:type=\"xsd:string\">Marina Del Rey</value>
     </item>
   </arg1>
   <arg2/>
  </ns1:runAgentAndWaitForResponse>
 </soapenv:Body>
</soapenv:Envelope>")
(CL:DECLAIM (CL:TYPE CL:SIMPLE-STRING *FETCH-REQUEST2*))

;;; (DEFUN GET-FETCH-RESPONSE1 ...)

(CL:DEFUN GET-FETCH-RESPONSE1 ()
  (CL:LET*
   ((|url|
     "http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService")
    (|headers| (NEW-PROPERTY-LIST)) (|response| STELLA::NULL-STRING))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |url| |response|))
   (INSERT-AT |headers| (WRAP-STRING "content-type")
    (WRAP-STRING "text/xml; charset=utf-8"))
   (INSERT-AT |headers| (WRAP-STRING "SoapAction") (WRAP-STRING ""))
   (CL:SETQ |response|
    (%DO-HTTP-REQUEST |url|
     (CONS-LIST KWD-FETCH-DEMO-METHOD KWD-FETCH-DEMO-POST
      KWD-FETCH-DEMO-HEADERS |headers| KWD-FETCH-DEMO-CONTENT
      (WRAP-STRING *FETCH-REQUEST2*))))
   (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "Response: " EOL
    |response| EOL)))

;;; (DEFUN GET-FETCH-RESPONSE2 ...)

(CL:DEFUN GET-FETCH-RESPONSE2 ()
  (CL:LET*
   ((|url|
     "http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService")
    (|headers| (NEW-PROPERTY-LIST)) (|response| STELLA::NULL-STRING)
    (|request| (MAKE-FETCH-REQUEST1)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |url| |response| |request|))
   (INSERT-AT |headers| (WRAP-STRING "content-type")
    (WRAP-STRING "text/xml; charset=utf-8"))
   (INSERT-AT |headers| (WRAP-STRING "SoapAction") (WRAP-STRING ""))
   (CL:SETQ |response|
    (%DO-HTTP-REQUEST |url|
     (CONS-LIST KWD-FETCH-DEMO-METHOD KWD-FETCH-DEMO-POST
      KWD-FETCH-DEMO-HEADERS |headers| KWD-FETCH-DEMO-CONTENT
      (WRAP-STRING |request|))))
   (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "Response: " EOL
    |response| EOL)))

;;; (DEFUN GET-FETCH-RESPONSE3 ...)

(CL:DEFUN GET-FETCH-RESPONSE3 ()
  (CL:LET*
   ((|url|
     "http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService")
    (|requestObject| (MAKE-FETCH-REQUEST-OBJECT1))
    (|responseObject| (CALL-WEBSERVICE |requestObject| |url|)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |url|))
   (CL:LET* ((*SUPRESS-NAMESPACES?* CL:T))
    (CL:DECLARE (CL:SPECIAL *SUPRESS-NAMESPACES?*))
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     "Retrieved Result is: " EOL (TO-XML-STRING |responseObject|) EOL))))

;;; (DEFUN (MAKE-FETCH-REQUEST1 STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION () CL:SIMPLE-STRING) MAKE-FETCH-REQUEST1))
(CL:DEFUN MAKE-FETCH-REQUEST1 ()
  (CL:LET* ((*SUPRESS-NAMESPACES?* CL:T))
   (CL:DECLARE (CL:SPECIAL *SUPRESS-NAMESPACES?*))
   (TO-XML-STRING (MAKE-FETCH-REQUEST-OBJECT1))))

;;; (DEFUN (MAKE-FETCH-REQUEST-OBJECT1 XMLObject) ...)

(CL:DEFUN MAKE-FETCH-REQUEST-OBJECT1 ()
  (CL:LET* ((SELF-000 (|new-key|)))
   (CL:SETF (|%textContent| SELF-000) "keywords")
   (CL:LET* ((|key| SELF-000))
    (CL:LET* ((SELF-001 (|new-value|)))
     (CL:SETF (|%textContent| SELF-001) "Marina Del Rey")
     (CL:LET* ((|value| SELF-001))
      (CL:LET* ((SELF-002 (|new-item|)))
       (CL:SETF (|%key| SELF-002) |key|)
       (CL:SETF (|%val| SELF-002) |value|)
       (CL:LET* ((|item| SELF-002))
        (CL:LET* ((SELF-003 (|new-arg0|)))
         (CL:SETF (|%textContent| SELF-003)
          "eeld/gettygeonames/plans/production")
         (CL:LET* ((|arg0| SELF-003))
          (CL:LET* ((SELF-004 (|new-arg1|)))
           (CL:SETF (|%item| SELF-004) |item|)
           (CL:LET* ((|arg1| SELF-004) (|arg2| (|new-arg2|)))
            (CL:LET* ((SELF-006 (|new-runAgentAndWaitForResponse|)))
             (CL:SETF (|%arg0| SELF-006) |arg0|)
             (CL:SETF (|%arg1| SELF-006) |arg1|)
             (CL:SETF (|%arg2| SELF-006) |arg2|)
             (CL:LET* ((|runAgentAndWaitForResponse| SELF-006))
              |runAgentAndWaitForResponse|)))))))))))))

(CL:DEFUN STARTUP-FETCH-DEMO ()
  (CL:LET*
   ((*MODULE*
     (GET-STELLA-MODULE "/STELLA/XML-OBJECTS/FETCH"
      (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2)
    (CL:SETQ |SGT-FETCH-DEMO-FETCH-runAgentAndWaitForResponse|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "runAgentAndWaitForResponse" NULL
      1))
    (CL:SETQ |SYM-FETCH-DEMO-FETCH-arg0|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "arg0" NULL 0))
    (CL:SETQ |SYM-FETCH-DEMO-FETCH-arg1|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "arg1" NULL 0))
    (CL:SETQ |SYM-FETCH-DEMO-FETCH-arg2|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "arg2" NULL 0))
    (CL:SETQ |SGT-FETCH-DEMO-FETCH-runAgentAndWaitForResponseResponse|
     (INTERN-RIGID-SYMBOL-WRT-MODULE
      "runAgentAndWaitForResponseResponse" NULL 1))
    (CL:SETQ |SYM-FETCH-DEMO-FETCH-return|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "return" NULL 0))
    (CL:SETQ |SGT-FETCH-DEMO-FETCH-runAgentAndWaitForResponseReturn|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "runAgentAndWaitForResponseReturn"
      NULL 1))
    (CL:SETQ |SYM-FETCH-DEMO-XSI-type|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "type"
      (GET-STELLA-MODULE "/STELLA/XML-OBJECTS/XSI" CL:T) 0))
    (CL:SETQ KWD-FETCH-DEMO-METHOD
     (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD" NULL 2))
    (CL:SETQ KWD-FETCH-DEMO-POST
     (INTERN-RIGID-SYMBOL-WRT-MODULE "POST" NULL 2))
    (CL:SETQ KWD-FETCH-DEMO-HEADERS
     (INTERN-RIGID-SYMBOL-WRT-MODULE "HEADERS" NULL 2))
    (CL:SETQ KWD-FETCH-DEMO-CONTENT
     (INTERN-RIGID-SYMBOL-WRT-MODULE "CONTENT" NULL 2))
    (CL:SETQ SYM-FETCH-DEMO-FETCH-STARTUP-FETCH-DEMO
     (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-FETCH-DEMO" NULL 0))
    (CL:SETQ SYM-FETCH-DEMO-STELLA-METHOD-STARTUP-CLASSNAME
     (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 5)
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE
        "runAgentAndWaitForResponse"
        "(DEFCLASS runAgentAndWaitForResponse (XMLObject) :PUBLIC-SLOTS ((arg0 :TYPE /STELLA/XML-OBJECTS/FETCH-CONTENT/arg0) (arg1 :TYPE /STELLA/XML-OBJECTS/FETCH-CONTENT/arg1) (arg2 :TYPE /STELLA/XML-OBJECTS/FETCH-CONTENT/arg2)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-runAgentAndWaitForResponse|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-runAgentAndWaitForResponse-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE
        "runAgentAndWaitForResponseResponse"
        "(DEFCLASS runAgentAndWaitForResponseResponse (XMLObject) :PUBLIC-SLOTS ((return :TYPE runAgentAndWaitForResponseReturn)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-runAgentAndWaitForResponseResponse|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION
       |access-runAgentAndWaitForResponseResponse-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE
        "runAgentAndWaitForResponseReturn"
        "(DEFCLASS runAgentAndWaitForResponseReturn (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-runAgentAndWaitForResponseReturn|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION
       |access-runAgentAndWaitForResponseReturn-Slot-Value|))))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7)
    (DEFINE-FUNCTION-OBJECT "GET-FETCH-RESPONSE1"
     "(DEFUN GET-FETCH-RESPONSE1 ())" (CL:FUNCTION GET-FETCH-RESPONSE1)
     NULL)
    (DEFINE-FUNCTION-OBJECT "GET-FETCH-RESPONSE2"
     "(DEFUN GET-FETCH-RESPONSE2 ())" (CL:FUNCTION GET-FETCH-RESPONSE2)
     NULL)
    (DEFINE-FUNCTION-OBJECT "GET-FETCH-RESPONSE3"
     "(DEFUN GET-FETCH-RESPONSE3 ())" (CL:FUNCTION GET-FETCH-RESPONSE3)
     NULL)
    (DEFINE-FUNCTION-OBJECT "MAKE-FETCH-REQUEST1"
     "(DEFUN (MAKE-FETCH-REQUEST1 STRING) ())"
     (CL:FUNCTION MAKE-FETCH-REQUEST1) NULL)
    (DEFINE-FUNCTION-OBJECT "MAKE-FETCH-REQUEST-OBJECT1"
     "(DEFUN (MAKE-FETCH-REQUEST-OBJECT1 XMLObject) ())"
     (CL:FUNCTION MAKE-FETCH-REQUEST-OBJECT1) NULL)
    (DEFINE-FUNCTION-OBJECT "STARTUP-FETCH-DEMO"
     "(DEFUN STARTUP-FETCH-DEMO () :PUBLIC? TRUE)"
     (CL:FUNCTION STARTUP-FETCH-DEMO) NULL)
    (CL:LET*
     ((FUNCTION
       (LOOKUP-FUNCTION SYM-FETCH-DEMO-FETCH-STARTUP-FETCH-DEMO)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-FETCH-DEMO-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupFetchDemo") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "FETCH")))
    (INSERT-AT *NAMESPACE-PREFIX-URI-TABLE* (WRAP-STRING "FETCH")
     (WRAP-STRING
      "http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService/"))
    (INSERT-AT *NAMESPACE-URI-PREFIX-TABLE*
     (WRAP-STRING
      "http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService/")
     (WRAP-STRING "FETCH"))
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *FETCH-REQUEST1* STRING \"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?>
<soapenv:Envelope xmlns:soapenv=\\\"http://schemas.xmlsoap.org/soap/envelope/\\\" xmlns:xsd=\\\"http://www.w3.org/2001/XMLSchema\\\" xmlns:xsi=\\\"http://www.w3.org/2001/XMLSchema-instance\\\">
 <soapenv:Body>
  <ns1:runAgentAndWaitForResponse soapenv:encodingStyle=\\\"http://schemas.xmlsoap.org/soap/encoding/\\\" xmlns:ns1=\\\"http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService/\\\">
   <arg0 xsi:type=\\\"xsd:string\\\">eeld/gettygeonames/plans/production</arg0>     
   <arg1 href=\\\"#id0\\\"/>
   <arg2 href=\\\"#id1\\\"/>
  </ns1:runAgentAndWaitForResponse>
  <multiRef id=\\\"id0\\\" soapenc:root=\\\"0\\\" soapenv:encodingStyle=\\\"http://schemas.xmlsoap.org/soap/encoding/\\\" xsi:type=\\\"ns2:Map\\\" xmlns:soapenc=\\\"http://schemas.xmlsoap.org/soap/encoding/\\\" xmlns:ns2=\\\"http://xml.apache.org/xml-soap\\\">
   <item>
    <key xsi:type=\\\"xsd:string\\\">keywords</key>		
    <value xsi:type=\\\"xsd:string\\\">Marina Del Rey</value>
   </item>
  </multiRef>
  <multiRef id=\\\"id1\\\" soapenc:root=\\\"0\\\" soapenv:encodingStyle=\\\"http://schemas.xmlsoap.org/soap/encoding/\\\" xsi:type=\\\"ns3:Map\\\" xmlns:ns3=\\\"http://xml.apache.org/xml-soap\\\" xmlns:soapenc=\\\"http://schemas.xmlsoap.org/soap/encoding/\\\"/>
 </soapenv:Body>
</soapenv:Envelope>\")" NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *FETCH-REQUEST2* STRING \"<?xml version=\\\"1.0\\\" encoding=\\\"UTF-8\\\"?>
<soapenv:Envelope xmlns:soapenv=\\\"http://schemas.xmlsoap.org/soap/envelope/\\\" xmlns:xsd=\\\"http://www.w3.org/2001/XMLSchema\\\" xmlns:xsi=\\\"http://www.w3.org/2001/XMLSchema-instance\\\">
 <soapenv:Body>
  <ns1:runAgentAndWaitForResponse soapenv:encodingStyle=\\\"http://schemas.xmlsoap.org/soap/encoding/\\\" xmlns:ns1=\\\"http://pegasus2.isi.edu:8080/axis/services/AgentRunnerService/\\\">
   <arg0 xsi:type=\\\"xsd:string\\\">eeld/gettygeonames/plans/production</arg0>     
   <arg1>
     <item>
       <key xsi:type=\\\"xsd:string\\\">keywords</key>		
       <value xsi:type=\\\"xsd:string\\\">Marina Del Rey</value>
     </item>
   </arg1>
   <arg2/>
  </ns1:runAgentAndWaitForResponse>
 </soapenv:Body>
</soapenv:Envelope>\")" NULL))))
