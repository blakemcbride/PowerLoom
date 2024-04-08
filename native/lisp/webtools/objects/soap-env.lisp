;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; soap-env.lisp

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

(CL:DEFVAR |SGT-SOAP-ENV-SOAP-ENV-Envelope| NULL)
(CL:DEFVAR |SYM-SOAP-ENV-SOAP-ENV-encodingStyle| NULL)
(CL:DEFVAR |SYM-SOAP-ENV-XML-OBJECTS-body| NULL)
(CL:DEFVAR |SGT-SOAP-ENV-SOAP-ENV-Body| NULL)
(CL:DEFVAR |SYM-SOAP-ENV-SOAP-ENV-contents| NULL)
(CL:DEFVAR |SGT-SOAP-ENV-SOAP-ENV-Fault| NULL)
(CL:DEFVAR |SYM-SOAP-ENV-SOAP-ENV-faultcode| NULL)
(CL:DEFVAR |SYM-SOAP-ENV-SOAP-ENV-faultstring| NULL)
(CL:DEFVAR |SYM-SOAP-ENV-SOAP-ENV-faultactor| NULL)
(CL:DEFVAR |SYM-SOAP-ENV-SOAP-ENV-detail| NULL)
(CL:DEFVAR |SGT-SOAP-ENV-SOAP-ENV-FaultCode| NULL)
(CL:DEFVAR |SGT-SOAP-ENV-SOAP-ENV-FaultString| NULL)
(CL:DEFVAR |SGT-SOAP-ENV-SOAP-ENV-FaultActor| NULL)
(CL:DEFVAR |SGT-SOAP-ENV-SOAP-ENV-Detail| NULL)
(CL:DEFVAR SYM-SOAP-ENV-SOAP-ENV-STARTUP-SOAP-ENV NULL)
(CL:DEFVAR SYM-SOAP-ENV-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM (CL:SPECIAL *STARTUP-TIME-PHASE* *MODULE*))

;;; (DEFCLASS Envelope ...)

(CL:DEFCLASS |Envelope| (|XMLObject|)
  ((|encodingStyle| :TYPE CL:SIMPLE-STRING :INITFORM
    STELLA::NULL-STRING :ALLOCATION :INSTANCE :ACCESSOR
    |%encodingStyle|)
   (|body| :ALLOCATION :INSTANCE :ACCESSOR |%body|)))

(CL:DEFUN |new-Envelope| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |Envelope|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%body| SELF) NULL)
   (CL:SETF (|%encodingStyle| SELF)
    "http://schemas.xmlsoap.org/soap/encoding/")
   SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |Envelope|))
  |SGT-SOAP-ENV-SOAP-ENV-Envelope|)

(CL:DEFUN |access-Envelope-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-SOAP-ENV-SOAP-ENV-encodingStyle|)
    (CL:IF SETVALUE?
     (CL:SETF (|%encodingStyle| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (|%encodingStyle| SELF)))))
   ((CL:EQ SLOTNAME |SYM-SOAP-ENV-XML-OBJECTS-body|)
    (CL:IF SETVALUE? (CL:SETF (|%body| SELF) VALUE)
     (CL:SETQ VALUE (|%body| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS Body ...)

(CL:DEFCLASS |Body| (|XMLObject|)
  ((|contents| :ALLOCATION :INSTANCE :ACCESSOR |%contents|)))

(CL:DEFUN |new-Body| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |Body|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%contents| SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |Body|))
  |SGT-SOAP-ENV-SOAP-ENV-Body|)

(CL:DEFUN |access-Body-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-SOAP-ENV-SOAP-ENV-contents|)
    (CL:IF SETVALUE? (CL:SETF (|%contents| SELF) VALUE)
     (CL:SETQ VALUE (|%contents| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS Fault ...)

(CL:DEFCLASS |Fault| (|XMLObject|)
  ((|faultcode| :ALLOCATION :INSTANCE :ACCESSOR |%faultcode|)
   (|faultstring| :ALLOCATION :INSTANCE :ACCESSOR |%faultstring|)
   (|faultactor| :ALLOCATION :INSTANCE :ACCESSOR |%faultactor|)
   (|detail| :ALLOCATION :INSTANCE :ACCESSOR |%detail|)))

(CL:DEFUN |new-Fault| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |Fault|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%detail| SELF) NULL) (CL:SETF (|%faultactor| SELF) NULL)
   (CL:SETF (|%faultstring| SELF) NULL)
   (CL:SETF (|%faultcode| SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |Fault|))
  |SGT-SOAP-ENV-SOAP-ENV-Fault|)

(CL:DEFUN |access-Fault-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-SOAP-ENV-SOAP-ENV-faultcode|)
    (CL:IF SETVALUE? (CL:SETF (|%faultcode| SELF) VALUE)
     (CL:SETQ VALUE (|%faultcode| SELF))))
   ((CL:EQ SLOTNAME |SYM-SOAP-ENV-SOAP-ENV-faultstring|)
    (CL:IF SETVALUE? (CL:SETF (|%faultstring| SELF) VALUE)
     (CL:SETQ VALUE (|%faultstring| SELF))))
   ((CL:EQ SLOTNAME |SYM-SOAP-ENV-SOAP-ENV-faultactor|)
    (CL:IF SETVALUE? (CL:SETF (|%faultactor| SELF) VALUE)
     (CL:SETQ VALUE (|%faultactor| SELF))))
   ((CL:EQ SLOTNAME |SYM-SOAP-ENV-SOAP-ENV-detail|)
    (CL:IF SETVALUE? (CL:SETF (|%detail| SELF) VALUE)
     (CL:SETQ VALUE (|%detail| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS FaultCode ...)

(CL:DEFCLASS |FaultCode| (|XMLObject|)
  ())

(CL:DEFUN |new-FaultCode| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |FaultCode|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |FaultCode|))
  |SGT-SOAP-ENV-SOAP-ENV-FaultCode|)

;;; (DEFCLASS FaultString ...)

(CL:DEFCLASS |FaultString| (|XMLObject|)
  ())

(CL:DEFUN |new-FaultString| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |FaultString|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |FaultString|))
  |SGT-SOAP-ENV-SOAP-ENV-FaultString|)

;;; (DEFCLASS FaultActor ...)

(CL:DEFCLASS |FaultActor| (|XMLObject|)
  ())

(CL:DEFUN |new-FaultActor| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |FaultActor|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |FaultActor|))
  |SGT-SOAP-ENV-SOAP-ENV-FaultActor|)

;;; (DEFCLASS Detail ...)

(CL:DEFCLASS |Detail| (|XMLObject|)
  ((|contents| :ALLOCATION :INSTANCE :ACCESSOR |%contents|)))

(CL:DEFUN |new-Detail| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |Detail|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%contents| SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |Detail|))
  |SGT-SOAP-ENV-SOAP-ENV-Detail|)

(CL:DEFUN |access-Detail-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-SOAP-ENV-SOAP-ENV-contents|)
    (CL:IF SETVALUE? (CL:SETF (|%contents| SELF) VALUE)
     (CL:SETQ VALUE (|%contents| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFUN (GET-BODY Body) ...)

(CL:DEFUN GET-BODY (|envelope|)
  (|%body| |envelope|))

;;; (DEFUN (GET-BODY-CONTENTS XMLObject) ...)

(CL:DEFUN GET-BODY-CONTENTS (|envelope|)
  (|%contents| (|%body| |envelope|)))

;;; (DEFUN (FAULT-MESSAGE? BOOLEAN) ...)

(CL:DEFUN FAULT-MESSAGE? (|envelope|)
  (ISA? (|%contents| (|%body| |envelope|))
   |SGT-SOAP-ENV-SOAP-ENV-Fault|))

;;; (DEFUN (GET-FAULT Fault) ...)

(CL:DEFUN GET-FAULT (|envelope|)
  (|%contents| (|%body| |envelope|)))

(CL:DEFUN STARTUP-SOAP-ENV ()
  (CL:LET*
   ((*MODULE*
     (GET-STELLA-MODULE "/STELLA/XML-OBJECTS/SOAP-ENV"
      (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2)
    (CL:SETQ |SGT-SOAP-ENV-SOAP-ENV-Envelope|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "Envelope" NULL 1))
    (CL:SETQ |SYM-SOAP-ENV-SOAP-ENV-encodingStyle|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "encodingStyle" NULL 0))
    (CL:SETQ |SYM-SOAP-ENV-XML-OBJECTS-body|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "body"
      (GET-STELLA-MODULE "/STELLA/XML-OBJECTS" CL:T) 0))
    (CL:SETQ |SGT-SOAP-ENV-SOAP-ENV-Body|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "Body" NULL 1))
    (CL:SETQ |SYM-SOAP-ENV-SOAP-ENV-contents|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "contents" NULL 0))
    (CL:SETQ |SGT-SOAP-ENV-SOAP-ENV-Fault|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "Fault" NULL 1))
    (CL:SETQ |SYM-SOAP-ENV-SOAP-ENV-faultcode|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "faultcode" NULL 0))
    (CL:SETQ |SYM-SOAP-ENV-SOAP-ENV-faultstring|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "faultstring" NULL 0))
    (CL:SETQ |SYM-SOAP-ENV-SOAP-ENV-faultactor|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "faultactor" NULL 0))
    (CL:SETQ |SYM-SOAP-ENV-SOAP-ENV-detail|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "detail" NULL 0))
    (CL:SETQ |SGT-SOAP-ENV-SOAP-ENV-FaultCode|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "FaultCode" NULL 1))
    (CL:SETQ |SGT-SOAP-ENV-SOAP-ENV-FaultString|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "FaultString" NULL 1))
    (CL:SETQ |SGT-SOAP-ENV-SOAP-ENV-FaultActor|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "FaultActor" NULL 1))
    (CL:SETQ |SGT-SOAP-ENV-SOAP-ENV-Detail|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "Detail" NULL 1))
    (CL:SETQ SYM-SOAP-ENV-SOAP-ENV-STARTUP-SOAP-ENV
     (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-SOAP-ENV" NULL 0))
    (CL:SETQ SYM-SOAP-ENV-STELLA-METHOD-STARTUP-CLASSNAME
     (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 5)
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "Envelope"
        "(DEFCLASS Envelope (XMLObject) :PUBLIC-SLOTS ((encodingStyle :TYPE STRING :INITIALLY \"http://schemas.xmlsoap.org/soap/encoding/\") (body :TYPE Body)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-Envelope|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-Envelope-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "Body"
        "(DEFCLASS Body (XMLObject) :PUBLIC-SLOTS ((contents :TYPE XMLObject)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS) (CL:FUNCTION |new-Body|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-Body-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "Fault"
        "(DEFCLASS Fault (XMLObject) :PUBLIC-SLOTS ((faultcode :TYPE FaultCode) (faultstring :TYPE FaultString) (faultactor :TYPE FaultActor) (detail :TYPE Detail)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-Fault|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-Fault-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "FaultCode"
        "(DEFCLASS FaultCode (XMLObject))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-FaultCode|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "FaultString"
        "(DEFCLASS FaultString (XMLObject))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-FaultString|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "FaultActor"
        "(DEFCLASS FaultActor (XMLObject))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-FaultActor|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "Detail"
        "(DEFCLASS Detail (XMLObject) :PUBLIC-SLOTS ((contents :TYPE XMLObject)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-Detail|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-Detail-Slot-Value|))))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7)
    (DEFINE-FUNCTION-OBJECT "GET-BODY"
     "(DEFUN (GET-BODY Body) ((envelope Envelope)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (body envelope)))"
     (CL:FUNCTION GET-BODY) NULL)
    (DEFINE-FUNCTION-OBJECT "GET-BODY-CONTENTS"
     "(DEFUN (GET-BODY-CONTENTS XMLObject) ((envelope Envelope)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (contents (GET-BODY envelope))))"
     (CL:FUNCTION GET-BODY-CONTENTS) NULL)
    (DEFINE-FUNCTION-OBJECT "FAULT-MESSAGE?"
     "(DEFUN (FAULT-MESSAGE? BOOLEAN) ((envelope Envelope)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (ISA? (GET-BODY-CONTENTS envelope) @Fault)))"
     (CL:FUNCTION FAULT-MESSAGE?) NULL)
    (DEFINE-FUNCTION-OBJECT "GET-FAULT"
     "(DEFUN (GET-FAULT Fault) ((envelope Envelope)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (SAFETY 2 (FAULT-MESSAGE? envelope) \"Envelope doesn't contain a Fault message\") (RETURN (GET-BODY-CONTENTS envelope)))"
     (CL:FUNCTION GET-FAULT) NULL)
    (DEFINE-FUNCTION-OBJECT "STARTUP-SOAP-ENV"
     "(DEFUN STARTUP-SOAP-ENV () :PUBLIC? TRUE)"
     (CL:FUNCTION STARTUP-SOAP-ENV) NULL)
    (CL:LET*
     ((FUNCTION
       (LOOKUP-FUNCTION SYM-SOAP-ENV-SOAP-ENV-STARTUP-SOAP-ENV)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-SOAP-ENV-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupSoapEnv") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "SOAP-ENV")))
    (INSERT-AT *NAMESPACE-PREFIX-URI-TABLE* (WRAP-STRING "SOAP-ENV")
     (WRAP-STRING "http://schemas.xmlsoap.org/soap/envelope/"))
    (INSERT-AT *NAMESPACE-URI-PREFIX-TABLE*
     (WRAP-STRING "http://schemas.xmlsoap.org/soap/envelope/")
     (WRAP-STRING "SOAP-ENV")))))
