;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; address-example.lisp

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

(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-getAddressFromName| NULL)
(CL:DEFVAR |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-nameElement| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-return| NULL)
(CL:DEFVAR |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-streetNum| NULL)
(CL:DEFVAR |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-streetName| NULL)
(CL:DEFVAR |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-city| NULL)
(CL:DEFVAR |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-state| NULL)
(CL:DEFVAR |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-zip| NULL)
(CL:DEFVAR |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-phone| NULL)
(CL:DEFVAR |SYM-ADDRESS-EXAMPLE-XSI-type| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-getAddressFromNameResponse| NULL)
(CL:DEFVAR |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-return| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-nameToLookup| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-Address| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-StreetNum| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-StreetName| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-City| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-State| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-Zip| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-PhoneNumber| NULL)
(CL:DEFVAR |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-areaCode| NULL)
(CL:DEFVAR |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-exchange| NULL)
(CL:DEFVAR |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-number| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-AreaCode| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-Exchange| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-Number| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-streetNum| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-streetName| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-city| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-state| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-zip| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-phoneNumber| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-areaCode| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-exchange| NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-number| NULL)
(CL:DEFVAR KWD-ADDRESS-EXAMPLE-METHOD NULL)
(CL:DEFVAR KWD-ADDRESS-EXAMPLE-POST NULL)
(CL:DEFVAR KWD-ADDRESS-EXAMPLE-CONTENT NULL)
(CL:DEFVAR KWD-ADDRESS-EXAMPLE-HEADERS NULL)
(CL:DEFVAR |SGT-ADDRESS-EXAMPLE-SOAP-ENV-Fault| NULL)
(CL:DEFVAR SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-STARTUP-ADDRESS-EXAMPLE NULL)
(CL:DEFVAR SYM-ADDRESS-EXAMPLE-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM
 (CL:SPECIAL *STARTUP-TIME-PHASE* *MODULE* *ADDRESS-REQUEST*
  STANDARD-OUTPUT EOL))

;;; (DEFCLASS getAddressFromName ...)

(CL:DEFCLASS |getAddressFromName| (|XMLObject|)
  ((|nameElement| :ALLOCATION :INSTANCE :ACCESSOR |%nameElement|)))

(CL:DEFUN |new-getAddressFromName| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |getAddressFromName|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%nameElement| SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |getAddressFromName|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-getAddressFromName|)

(CL:DEFUN |access-getAddressFromName-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-nameElement|)
    (CL:IF SETVALUE? (CL:SETF (|%nameElement| SELF) VALUE)
     (CL:SETQ VALUE (|%nameElement| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS return ...)

(CL:DEFCLASS |return| (|XMLObject|)
  ((|streetNum| :ALLOCATION :INSTANCE :ACCESSOR |%streetNum|)
   (|streetName| :ALLOCATION :INSTANCE :ACCESSOR |%streetName|)
   (|city| :ALLOCATION :INSTANCE :ACCESSOR |%city|)
   (|state| :ALLOCATION :INSTANCE :ACCESSOR |%state|)
   (|zip| :ALLOCATION :INSTANCE :ACCESSOR |%zip|)
   (|phone| :ALLOCATION :INSTANCE :ACCESSOR |%phone|)
   (|type| :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR |%type|)))

(CL:DEFUN |new-return| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |return|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%type| SELF) "ADDRESS-DEMO:address")
   (CL:SETF (|%phone| SELF) NULL) (CL:SETF (|%zip| SELF) NULL)
   (CL:SETF (|%state| SELF) NULL) (CL:SETF (|%city| SELF) NULL)
   (CL:SETF (|%streetName| SELF) NULL)
   (CL:SETF (|%streetNum| SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |return|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-return|)

(CL:DEFUN |access-return-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-streetNum|)
    (CL:IF SETVALUE? (CL:SETF (|%streetNum| SELF) VALUE)
     (CL:SETQ VALUE (|%streetNum| SELF))))
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-streetName|)
    (CL:IF SETVALUE? (CL:SETF (|%streetName| SELF) VALUE)
     (CL:SETQ VALUE (|%streetName| SELF))))
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-city|)
    (CL:IF SETVALUE? (CL:SETF (|%city| SELF) VALUE)
     (CL:SETQ VALUE (|%city| SELF))))
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-state|)
    (CL:IF SETVALUE? (CL:SETF (|%state| SELF) VALUE)
     (CL:SETQ VALUE (|%state| SELF))))
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-zip|)
    (CL:IF SETVALUE? (CL:SETF (|%zip| SELF) VALUE)
     (CL:SETQ VALUE (|%zip| SELF))))
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-phone|)
    (CL:IF SETVALUE? (CL:SETF (|%phone| SELF) VALUE)
     (CL:SETQ VALUE (|%phone| SELF))))
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-XSI-type|)
    (CL:IF SETVALUE? (CL:SETF (|%type| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (|%type| SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS getAddressFromNameResponse ...)

(CL:DEFCLASS |getAddressFromNameResponse| (|XMLObject|)
  ((|return| :ALLOCATION :INSTANCE :ACCESSOR |%return|)))

(CL:DEFUN |new-getAddressFromNameResponse| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF
    (CL:MAKE-INSTANCE (CL:QUOTE |getAddressFromNameResponse|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%return| SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |getAddressFromNameResponse|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-getAddressFromNameResponse|)

(CL:DEFUN |access-getAddressFromNameResponse-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-return|)
    (CL:IF SETVALUE? (CL:SETF (|%return| SELF) VALUE)
     (CL:SETQ VALUE (|%return| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS nameToLookup ...)

(CL:DEFCLASS |nameToLookup| (|XMLObject|)
  ((|type| :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR |%type|)))

(CL:DEFUN |new-nameToLookup| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |nameToLookup|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%type| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |nameToLookup|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-nameToLookup|)

(CL:DEFUN |access-nameToLookup-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-XSI-type|)
    (CL:IF SETVALUE? (CL:SETF (|%type| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (|%type| SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS Address ...)

(CL:DEFCLASS |Address| (|XMLObject|)
  ((|streetNum| :ALLOCATION :INSTANCE :ACCESSOR |%streetNum|)
   (|streetName| :ALLOCATION :INSTANCE :ACCESSOR |%streetName|)
   (|city| :ALLOCATION :INSTANCE :ACCESSOR |%city|)
   (|state| :ALLOCATION :INSTANCE :ACCESSOR |%state|)
   (|zip| :ALLOCATION :INSTANCE :ACCESSOR |%zip|)
   (|phone| :ALLOCATION :INSTANCE :ACCESSOR |%phone|)))

(CL:DEFUN |new-Address| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |Address|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%phone| SELF) NULL) (CL:SETF (|%zip| SELF) NULL)
   (CL:SETF (|%state| SELF) NULL) (CL:SETF (|%city| SELF) NULL)
   (CL:SETF (|%streetName| SELF) NULL)
   (CL:SETF (|%streetNum| SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |Address|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-Address|)

(CL:DEFUN |access-Address-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-streetNum|)
    (CL:IF SETVALUE? (CL:SETF (|%streetNum| SELF) VALUE)
     (CL:SETQ VALUE (|%streetNum| SELF))))
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-streetName|)
    (CL:IF SETVALUE? (CL:SETF (|%streetName| SELF) VALUE)
     (CL:SETQ VALUE (|%streetName| SELF))))
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-city|)
    (CL:IF SETVALUE? (CL:SETF (|%city| SELF) VALUE)
     (CL:SETQ VALUE (|%city| SELF))))
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-state|)
    (CL:IF SETVALUE? (CL:SETF (|%state| SELF) VALUE)
     (CL:SETQ VALUE (|%state| SELF))))
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-zip|)
    (CL:IF SETVALUE? (CL:SETF (|%zip| SELF) VALUE)
     (CL:SETQ VALUE (|%zip| SELF))))
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-phone|)
    (CL:IF SETVALUE? (CL:SETF (|%phone| SELF) VALUE)
     (CL:SETQ VALUE (|%phone| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS StreetNum ...)

(CL:DEFCLASS |StreetNum| (|XMLObject|)
  ())

(CL:DEFUN |new-StreetNum| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |StreetNum|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |StreetNum|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-StreetNum|)

;;; (DEFCLASS StreetName ...)

(CL:DEFCLASS |StreetName| (|XMLObject|)
  ())

(CL:DEFUN |new-StreetName| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |StreetName|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |StreetName|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-StreetName|)

;;; (DEFCLASS City ...)

(CL:DEFCLASS |City| (|XMLObject|)
  ())

(CL:DEFUN |new-City| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |City|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |City|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-City|)

;;; (DEFCLASS State ...)

(CL:DEFCLASS |State| (|XMLObject|)
  ())

(CL:DEFUN |new-State| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |State|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |State|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-State|)

;;; (DEFCLASS Zip ...)

(CL:DEFCLASS |Zip| (|XMLObject|)
  ())

(CL:DEFUN |new-Zip| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |Zip|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |Zip|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-Zip|)

;;; (DEFCLASS PhoneNumber ...)

(CL:DEFCLASS |PhoneNumber| (|XMLObject|)
  ((|areaCode| :ALLOCATION :INSTANCE :ACCESSOR |%areaCode|)
   (|exchange| :ALLOCATION :INSTANCE :ACCESSOR |%exchange|)
   (|number| :ALLOCATION :INSTANCE :ACCESSOR |%number|)))

(CL:DEFUN |new-PhoneNumber| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |PhoneNumber|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%number| SELF) NULL) (CL:SETF (|%exchange| SELF) NULL)
   (CL:SETF (|%areaCode| SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |PhoneNumber|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-PhoneNumber|)

(CL:DEFUN |access-PhoneNumber-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-areaCode|)
    (CL:IF SETVALUE? (CL:SETF (|%areaCode| SELF) VALUE)
     (CL:SETQ VALUE (|%areaCode| SELF))))
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-exchange|)
    (CL:IF SETVALUE? (CL:SETF (|%exchange| SELF) VALUE)
     (CL:SETQ VALUE (|%exchange| SELF))))
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-number|)
    (CL:IF SETVALUE? (CL:SETF (|%number| SELF) VALUE)
     (CL:SETQ VALUE (|%number| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS AreaCode ...)

(CL:DEFCLASS |AreaCode| (|XMLObject|)
  ())

(CL:DEFUN |new-AreaCode| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |AreaCode|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |AreaCode|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-AreaCode|)

;;; (DEFCLASS Exchange ...)

(CL:DEFCLASS |Exchange| (|XMLObject|)
  ())

(CL:DEFUN |new-Exchange| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |Exchange|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |Exchange|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-Exchange|)

;;; (DEFCLASS Number ...)

(CL:DEFCLASS |Number| (|XMLObject|)
  ())

(CL:DEFUN |new-Number| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |Number|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |Number|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-Number|)

;;; (DEFCLASS streetNum ...)

(CL:DEFCLASS |streetNum| (|XMLObject|)
  ((|type| :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR |%type|)))

(CL:DEFUN |new-streetNum| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |streetNum|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%type| SELF) "XSD:int") SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |streetNum|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-streetNum|)

(CL:DEFUN |access-streetNum-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-XSI-type|)
    (CL:IF SETVALUE? (CL:SETF (|%type| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (|%type| SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS streetName ...)

(CL:DEFCLASS |streetName| (|XMLObject|)
  ((|type| :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR |%type|)))

(CL:DEFUN |new-streetName| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |streetName|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%type| SELF) "XSD:string") SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |streetName|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-streetName|)

(CL:DEFUN |access-streetName-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-XSI-type|)
    (CL:IF SETVALUE? (CL:SETF (|%type| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (|%type| SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS city ...)

(CL:DEFCLASS |city| (|XMLObject|)
  ((|type| :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR |%type|)))

(CL:DEFUN |new-city| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |city|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%type| SELF) "XSD:string") SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |city|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-city|)

(CL:DEFUN |access-city-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-XSI-type|)
    (CL:IF SETVALUE? (CL:SETF (|%type| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (|%type| SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS state ...)

(CL:DEFCLASS |state| (|XMLObject|)
  ((|type| :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR |%type|)))

(CL:DEFUN |new-state| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |state|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%type| SELF) "XSD:string") SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |state|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-state|)

(CL:DEFUN |access-state-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-XSI-type|)
    (CL:IF SETVALUE? (CL:SETF (|%type| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (|%type| SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS zip ...)

(CL:DEFCLASS |zip| (|XMLObject|)
  ((|type| :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR |%type|)))

(CL:DEFUN |new-zip| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |zip|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%type| SELF) "XSD:int") SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |zip|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-zip|)

(CL:DEFUN |access-zip-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-XSI-type|)
    (CL:IF SETVALUE? (CL:SETF (|%type| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (|%type| SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS phoneNumber ...)

(CL:DEFCLASS |phoneNumber| (|XMLObject|)
  ((|areaCode| :ALLOCATION :INSTANCE :ACCESSOR |%areaCode|)
   (|exchange| :ALLOCATION :INSTANCE :ACCESSOR |%exchange|)
   (|number| :ALLOCATION :INSTANCE :ACCESSOR |%number|)
   (|type| :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR |%type|)))

(CL:DEFUN |new-phoneNumber| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |phoneNumber|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%type| SELF) "ADDRESS-DEMO:phone")
   (CL:SETF (|%number| SELF) NULL) (CL:SETF (|%exchange| SELF) NULL)
   (CL:SETF (|%areaCode| SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |phoneNumber|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-phoneNumber|)

(CL:DEFUN |access-phoneNumber-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-areaCode|)
    (CL:IF SETVALUE? (CL:SETF (|%areaCode| SELF) VALUE)
     (CL:SETQ VALUE (|%areaCode| SELF))))
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-exchange|)
    (CL:IF SETVALUE? (CL:SETF (|%exchange| SELF) VALUE)
     (CL:SETQ VALUE (|%exchange| SELF))))
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-number|)
    (CL:IF SETVALUE? (CL:SETF (|%number| SELF) VALUE)
     (CL:SETQ VALUE (|%number| SELF))))
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-XSI-type|)
    (CL:IF SETVALUE? (CL:SETF (|%type| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (|%type| SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS areaCode ...)

(CL:DEFCLASS |areaCode| (|XMLObject|)
  ((|type| :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR |%type|)))

(CL:DEFUN |new-areaCode| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |areaCode|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%type| SELF) "XSD:int") SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |areaCode|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-areaCode|)

(CL:DEFUN |access-areaCode-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-XSI-type|)
    (CL:IF SETVALUE? (CL:SETF (|%type| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (|%type| SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS exchange ...)

(CL:DEFCLASS |exchange| (|XMLObject|)
  ((|type| :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR |%type|)))

(CL:DEFUN |new-exchange| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |exchange|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%type| SELF) "XSD:string") SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |exchange|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-exchange|)

(CL:DEFUN |access-exchange-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-XSI-type|)
    (CL:IF SETVALUE? (CL:SETF (|%type| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (|%type| SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS number ...)

(CL:DEFCLASS |number| (|XMLObject|)
  ((|type| :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR |%type|)))

(CL:DEFUN |new-number| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |number|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%type| SELF) "XSD:string") SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |number|))
  |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-number|)

(CL:DEFUN |access-number-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-ADDRESS-EXAMPLE-XSI-type|)
    (CL:IF SETVALUE? (CL:SETF (|%type| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (|%type| SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFUN (getAddressFromName getAddressFromNameResponse) ...)

(CL:DEFUN |getAddressFromName| (|name|)
  (CL:LET* ((|theName| (|%textContent| |name|)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |theName|))
   (CL:LET* ((SELF-000 (|new-areaCode|)))
    (CL:SETF (|%textContent| SELF-000) "789")
    (CL:LET* ((|areaCode| SELF-000))
     (CL:LET* ((SELF-001 (|new-exchange|)))
      (CL:SETF (|%textContent| SELF-001) "654")
      (CL:LET* ((|exchange| SELF-001))
       (CL:LET* ((SELF-002 (|new-number|)))
        (CL:SETF (|%textContent| SELF-002) "3210")
        (CL:LET* ((|number| SELF-002))
         (CL:LET* ((SELF-003 (|new-phoneNumber|)))
          (CL:SETF (|%areaCode| SELF-003) |areaCode|)
          (CL:SETF (|%exchange| SELF-003) |exchange|)
          (CL:SETF (|%number| SELF-003) |number|)
          (CL:LET* ((|phone| SELF-003))
           (CL:LET* ((SELF-004 (|new-streetNum|)))
            (CL:SETF (|%textContent| SELF-004) "919")
            (CL:LET* ((|streetNum| SELF-004))
             (CL:LET* ((SELF-005 (|new-streetName|)))
              (CL:SETF (|%textContent| SELF-005)
               (CONCATENATE "Street for " |theName|))
              (CL:LET* ((|streetName| SELF-005))
               (CL:LET* ((SELF-006 (|new-city|)))
                (CL:SETF (|%textContent| SELF-006) "Sunnytown")
                (CL:LET* ((|city| SELF-006))
                 (CL:LET* ((SELF-007 (|new-state|)))
                  (CL:SETF (|%textContent| SELF-007) "UT")
                  (CL:LET* ((|state| SELF-007))
                   (CL:LET* ((SELF-008 (|new-zip|)))
                    (CL:SETF (|%textContent| SELF-008) "43434")
                    (CL:LET* ((|zip| SELF-008))
                     (CL:LET* ((SELF-009 (|new-return|)))
                      (CL:SETF (|%streetNum| SELF-009) |streetNum|)
                      (CL:SETF (|%streetName| SELF-009) |streetName|)
                      (CL:SETF (|%city| SELF-009) |city|)
                      (CL:SETF (|%state| SELF-009) |state|)
                      (CL:SETF (|%zip| SELF-009) |zip|)
                      (CL:SETF (|%phone| SELF-009) |phone|)
                      (CL:LET* ((|return| SELF-009))
                       (CL:LET*
                        ((SELF-010 (|new-getAddressFromNameResponse|)))
                        (CL:SETF (|%return| SELF-010) |return|)
                        (CL:LET* ((|result| SELF-010))
                         |result|))))))))))))))))))))))))

;;; (DEFUN (MAKE-REQUEST-OBJECT1 getAddressFromName) ...)

(CL:DEFUN MAKE-REQUEST-OBJECT1 ()
  (CL:LET* ((SELF-000 (|new-nameToLookup|)))
   (CL:SETF (|%textContent| SELF-000) "John B. Good")
   (CL:LET* ((|nameToLookup| SELF-000))
    (CL:LET* ((SELF-001 (|new-getAddressFromName|)))
     (CL:SETF (|%nameElement| SELF-001) |nameToLookup|)
     (CL:LET* ((|requestObject| SELF-001))
      (CL:SETF (|%type| |nameToLookup|) "XSD:string")
      |requestObject|)))))

;;; (DEFUN ADDRESS-TEST1 ...)

(CL:DEFUN ADDRESS-TEST1 ()
  (CL:LET* ((|result| (NEW-OUTPUT-STRING-STREAM)))
   (PROCESS-SOAP-RPC-REQUEST *ADDRESS-REQUEST* CL:NIL |result|)
   (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
    "Retrieved envelope is: " EOL
    (TO-XML-STRING (FROM-XML-STRING (THE-STRING-READER |result|))))))

;;; (DEFUN ADDRESS-TEST2 ...)

(CL:DEFUN ADDRESS-TEST2 ()
  (CL:LET*
   ((|resultString|
     (%DO-HTTP-REQUEST "http://localhost:8012/ploom/soap-rpc"
      (CONS-LIST KWD-ADDRESS-EXAMPLE-METHOD KWD-ADDRESS-EXAMPLE-POST
       KWD-ADDRESS-EXAMPLE-CONTENT (WRAP-STRING *ADDRESS-REQUEST*)))))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |resultString|))
   (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
    "Retrieved envelope is: " EOL |resultString|)))

;;; (DEFUN GET-APACHE-RESPONSE1 ...)

(CL:DEFUN GET-APACHE-RESPONSE1 ()
  (CL:LET*
   ((|url| "http://localhost:8080/soap/servlet/rpcrouter")
    (|headers| (NEW-PROPERTY-LIST)) (|response| STELLA::NULL-STRING)
    (|responseEnvelope| NULL) (|address| NULL)
    (|addressString| STELLA::NULL-STRING))
   (CL:DECLARE
    (CL:TYPE CL:SIMPLE-STRING |url| |response| |addressString|))
   (INSERT-AT |headers| (WRAP-STRING "content-type")
    (WRAP-STRING "text/xml; charset=utf-8"))
   (CL:SETQ |response|
    (%DO-HTTP-REQUEST |url|
     (CONS-LIST KWD-ADDRESS-EXAMPLE-METHOD KWD-ADDRESS-EXAMPLE-POST
      KWD-ADDRESS-EXAMPLE-HEADERS |headers| KWD-ADDRESS-EXAMPLE-CONTENT
      (WRAP-STRING *ADDRESS-REQUEST*))))
   (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "Response: " EOL
    |response| EOL)
   (CL:SETQ |responseEnvelope| (FROM-XML-STRING |response|))
   (CL:SETQ |address| (|%contents| (|%body| |responseEnvelope|)))
   (CL:LET* ((*SUPRESS-NAMESPACES?* CL:T))
    (CL:DECLARE (CL:SPECIAL *SUPRESS-NAMESPACES?*))
    (CL:SETQ |addressString| (TO-XML-STRING |address|))
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     "Retrieved Address is: " EOL |addressString|))))

;;; (DEFUN GET-APACHE-RESPONSE2 ...)

(CL:DEFUN GET-APACHE-RESPONSE2 ()
  (CL:LET*
   ((|url| "http://tubular.isi.edu:8080/soap/servlet/rpcrouter")
    (|requestObject| (MAKE-REQUEST-OBJECT1))
    (|responseObject| (CALL-WEBSERVICE |requestObject| |url|)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |url|))
   (CL:LET* ((*SUPRESS-NAMESPACES?* CL:T))
    (CL:DECLARE (CL:SPECIAL *SUPRESS-NAMESPACES?*))
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     "Retrieved Response object is: " EOL
     (TO-XML-STRING |responseObject|) EOL EOL)
    (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE |responseObject|)))
     (CL:COND
      ((SUBTYPE-OF? TEST-VALUE-000
        |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-getAddressFromNameResponse|)
       (CL:PROGN
        (CL:LET*
         ((|streetName|
           (|%textContent|
            (|%streetName| (|%return| |responseObject|)))))
         (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |streetName|))
         (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
          "Retrieved Street Name is: " |streetName| EOL))))
      ((SUBTYPE-OF? TEST-VALUE-000
        |SGT-ADDRESS-EXAMPLE-SOAP-ENV-Fault|)
       (CL:PROGN
        (CL:LET*
         ((|code| (|%textContent| (|%faultcode| |responseObject|)))
          (|string| (|%textContent| (|%faultstring| |responseObject|)))
          (|actor| (|%textContent| (|%faultactor| |responseObject|))))
         (CL:DECLARE
          (CL:TYPE CL:SIMPLE-STRING |code| |string| |actor|))
         (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
          "Received SOAP Fault:" EOL)
         (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) " CODE   : "
          |code| EOL)
         (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) " STRING : "
          |string| EOL)
         (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) " ACTOR  : "
          |actor| EOL))))
      (CL:T
       (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
        (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" TEST-VALUE-000
         "' is not a valid case option")
        (CL:ERROR
         (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))))))

;;; (DEFGLOBAL *ADDRESS-REQUEST* ...)

(CL:DEFVAR *ADDRESS-REQUEST* "<?xml version='1.0' encoding='UTF-8'?>
<SOAP-ENV:Envelope xmlns:SOAP-ENV=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">
<SOAP-ENV:Body>
<ns1:getAddressFromName xmlns:ns1=\"urn:AddressFetcher\" SOAP-ENV:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">
<ns1:nameToLookup xsi:type=\"xsd:string\">John B. Good</ns1:nameToLookup>
</ns1:getAddressFromName>
</SOAP-ENV:Body>
</SOAP-ENV:Envelope>
")
(CL:DECLAIM (CL:TYPE CL:SIMPLE-STRING *ADDRESS-REQUEST*))

(CL:DEFUN HELP-STARTUP-ADDRESS-EXAMPLE1 ()
  (CL:PROGN
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-getAddressFromName|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "getAddressFromName" NULL 1))
   (CL:SETQ |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-nameElement|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "nameElement" NULL 0))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-return|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "return" NULL 1))
   (CL:SETQ |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-streetNum|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "streetNum" NULL 0))
   (CL:SETQ |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-streetName|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "streetName" NULL 0))
   (CL:SETQ |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-city|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "city" NULL 0))
   (CL:SETQ |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-state|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "state" NULL 0))
   (CL:SETQ |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-zip|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "zip" NULL 0))
   (CL:SETQ |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-phone|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "phone" NULL 0))
   (CL:SETQ |SYM-ADDRESS-EXAMPLE-XSI-type|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "type"
     (GET-STELLA-MODULE "/STELLA/XML-OBJECTS/XSI" CL:T) 0))
   (CL:SETQ
    |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-getAddressFromNameResponse|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "getAddressFromNameResponse" NULL
     1))
   (CL:SETQ |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-return|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "return" NULL 0))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-nameToLookup|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "nameToLookup" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-Address|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "Address" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-StreetNum|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "StreetNum" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-StreetName|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "StreetName" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-City|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "City" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-State|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "State" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-Zip|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "Zip" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-PhoneNumber|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PhoneNumber" NULL 1))
   (CL:SETQ |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-areaCode|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "areaCode" NULL 0))
   (CL:SETQ |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-exchange|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "exchange" NULL 0))
   (CL:SETQ |SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-number|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "number" NULL 0))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-AreaCode|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "AreaCode" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-Exchange|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "Exchange" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-Number|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "Number" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-streetNum|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "streetNum" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-streetName|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "streetName" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-city|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "city" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-state|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "state" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-zip|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "zip" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-phoneNumber|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "phoneNumber" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-areaCode|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "areaCode" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-exchange|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "exchange" NULL 1))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-number|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "number" NULL 1))
   (CL:SETQ KWD-ADDRESS-EXAMPLE-METHOD
    (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD" NULL 2))
   (CL:SETQ KWD-ADDRESS-EXAMPLE-POST
    (INTERN-RIGID-SYMBOL-WRT-MODULE "POST" NULL 2))
   (CL:SETQ KWD-ADDRESS-EXAMPLE-CONTENT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONTENT" NULL 2))
   (CL:SETQ KWD-ADDRESS-EXAMPLE-HEADERS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "HEADERS" NULL 2))
   (CL:SETQ |SGT-ADDRESS-EXAMPLE-SOAP-ENV-Fault|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "Fault"
     (GET-STELLA-MODULE "/STELLA/XML-OBJECTS/SOAP-ENV" CL:T) 1))
   (CL:SETQ SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-STARTUP-ADDRESS-EXAMPLE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-ADDRESS-EXAMPLE" NULL 0))
   (CL:SETQ SYM-ADDRESS-EXAMPLE-STELLA-METHOD-STARTUP-CLASSNAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))))

(CL:DEFUN STARTUP-ADDRESS-EXAMPLE ()
  (CL:LET*
   ((*MODULE*
     (GET-STELLA-MODULE "/STELLA/XML-OBJECTS/ADDRESS-EXAMPLE"
      (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2)
    (HELP-STARTUP-ADDRESS-EXAMPLE1))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 5)
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "getAddressFromName"
        "(DEFCLASS getAddressFromName (XMLObject) :PUBLIC-SLOTS ((nameElement :TYPE nameToLookup)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-getAddressFromName|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-getAddressFromName-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "return"
        "(DEFCLASS return (XMLObject) :PUBLIC-SLOTS ((streetNum :TYPE streetNum) (streetName :TYPE streetName) (city :TYPE city) (state :TYPE state) (zip :TYPE zip) (phone :TYPE phoneNumber) (/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"ADDRESS-DEMO:address\")))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-return|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-return-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE
        "getAddressFromNameResponse"
        "(DEFCLASS getAddressFromNameResponse (XMLObject) :PUBLIC-SLOTS ((return :TYPE /STELLA/XML-OBJECTS/ADDRESS-DEMO/return)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-getAddressFromNameResponse|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-getAddressFromNameResponse-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "nameToLookup"
        "(DEFCLASS nameToLookup (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-nameToLookup|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-nameToLookup-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "Address"
        "(DEFCLASS Address (XMLObject) :PUBLIC-SLOTS ((streetNum :TYPE StreetNum) (streetName :TYPE StreetName) (city :TYPE City) (state :TYPE State) (zip :TYPE Zip) (phone :TYPE PhoneNumber)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-Address|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-Address-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "StreetNum"
        "(DEFCLASS StreetNum (XMLObject))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-StreetNum|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "StreetName"
        "(DEFCLASS StreetName (XMLObject))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-StreetName|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "City"
        "(DEFCLASS City (XMLObject))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-City|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "State"
        "(DEFCLASS State (XMLObject))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-State|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "Zip"
        "(DEFCLASS Zip (XMLObject))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS) (CL:FUNCTION |new-Zip|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "PhoneNumber"
        "(DEFCLASS PhoneNumber (XMLObject) :PUBLIC-SLOTS ((areaCode :TYPE AreaCode) (exchange :TYPE Exchange) (number :TYPE Number)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-PhoneNumber|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-PhoneNumber-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "AreaCode"
        "(DEFCLASS AreaCode (XMLObject))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-AreaCode|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "Exchange"
        "(DEFCLASS Exchange (XMLObject))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-Exchange|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "Number"
        "(DEFCLASS Number (XMLObject))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-Number|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "streetNum"
        "(DEFCLASS streetNum (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:int\")))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-streetNum|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-streetNum-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "streetName"
        "(DEFCLASS streetName (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:string\")))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-streetName|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-streetName-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "city"
        "(DEFCLASS city (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:string\")))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS) (CL:FUNCTION |new-city|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-city-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "state"
        "(DEFCLASS state (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:string\")))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-state|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-state-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "zip"
        "(DEFCLASS zip (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:int\")))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS) (CL:FUNCTION |new-zip|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-zip-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "phoneNumber"
        "(DEFCLASS phoneNumber (XMLObject) :PUBLIC-SLOTS ((areaCode :TYPE areaCode) (exchange :TYPE exchange) (number :TYPE number) (/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"ADDRESS-DEMO:phone\")))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-phoneNumber|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-phoneNumber-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "areaCode"
        "(DEFCLASS areaCode (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:int\")))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-areaCode|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-areaCode-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "exchange"
        "(DEFCLASS exchange (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:string\")))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-exchange|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-exchange-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "number"
        "(DEFCLASS number (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:string\")))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-number|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-number-Slot-Value|))))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7)
    (DEFINE-FUNCTION-OBJECT "getAddressFromName"
     "(DEFUN (getAddressFromName getAddressFromNameResponse) ((name nameToLookup)))"
     (CL:FUNCTION |getAddressFromName|) NULL)
    (DEFINE-FUNCTION-OBJECT "MAKE-REQUEST-OBJECT1"
     "(DEFUN (MAKE-REQUEST-OBJECT1 getAddressFromName) ())"
     (CL:FUNCTION MAKE-REQUEST-OBJECT1) NULL)
    (DEFINE-FUNCTION-OBJECT "ADDRESS-TEST1" "(DEFUN ADDRESS-TEST1 ())"
     (CL:FUNCTION ADDRESS-TEST1) NULL)
    (DEFINE-FUNCTION-OBJECT "ADDRESS-TEST2" "(DEFUN ADDRESS-TEST2 ())"
     (CL:FUNCTION ADDRESS-TEST2) NULL)
    (DEFINE-FUNCTION-OBJECT "GET-APACHE-RESPONSE1"
     "(DEFUN GET-APACHE-RESPONSE1 ())"
     (CL:FUNCTION GET-APACHE-RESPONSE1) NULL)
    (DEFINE-FUNCTION-OBJECT "GET-APACHE-RESPONSE2"
     "(DEFUN GET-APACHE-RESPONSE2 ())"
     (CL:FUNCTION GET-APACHE-RESPONSE2) NULL)
    (DEFINE-FUNCTION-OBJECT "STARTUP-ADDRESS-EXAMPLE"
     "(DEFUN STARTUP-ADDRESS-EXAMPLE () :PUBLIC? TRUE)"
     (CL:FUNCTION STARTUP-ADDRESS-EXAMPLE) NULL)
    (CL:LET*
     ((FUNCTION
       (LOOKUP-FUNCTION
        SYM-ADDRESS-EXAMPLE-ADDRESS-EXAMPLE-STARTUP-ADDRESS-EXAMPLE)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-ADDRESS-EXAMPLE-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupAddressExample") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "ADDRESS-EXAMPLE")))
    (INSERT-AT *NAMESPACE-PREFIX-URI-TABLE*
     (WRAP-STRING "ADDRESS-EXAMPLE")
     (WRAP-STRING "urn:AddressFetcher"))
    (INSERT-AT *NAMESPACE-URI-PREFIX-TABLE*
     (WRAP-STRING "urn:AddressFetcher")
     (WRAP-STRING "ADDRESS-EXAMPLE"))
    (CL:SETQ *INVISIBLE-NAMESPACES-ON-OUTPUT*
     (CONS (WRAP-STRING "ADDRESS-EXAMPLE")
      *INVISIBLE-NAMESPACES-ON-OUTPUT*))
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *ADDRESS-REQUEST* STRING \"<?xml version='1.0' encoding='UTF-8'?>
<SOAP-ENV:Envelope xmlns:SOAP-ENV=\\\"http://schemas.xmlsoap.org/soap/envelope/\\\" xmlns:xsi=\\\"http://www.w3.org/2001/XMLSchema-instance\\\" xmlns:xsd=\\\"http://www.w3.org/2001/XMLSchema\\\">
<SOAP-ENV:Body>
<ns1:getAddressFromName xmlns:ns1=\\\"urn:AddressFetcher\\\" SOAP-ENV:encodingStyle=\\\"http://schemas.xmlsoap.org/soap/encoding/\\\">
<ns1:nameToLookup xsi:type=\\\"xsd:string\\\">John B. Good</ns1:nameToLookup>
</ns1:getAddressFromName>
</SOAP-ENV:Body>
</SOAP-ENV:Envelope>
\")" NULL))))
