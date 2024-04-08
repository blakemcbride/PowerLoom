;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; sample-contents.lisp

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

(CL:DEFVAR |SGT-SAMPLE-CONTENTS-SAMPLE-SampleContents| NULL)
(CL:DEFVAR |SYM-SAMPLE-CONTENTS-SAMPLE-sampleAttr| NULL)
(CL:DEFVAR |SYM-SAMPLE-CONTENTS-SAMPLE-sub| NULL)
(CL:DEFVAR |SYM-SAMPLE-CONTENTS-SAMPLE-SampleListItem| NULL)
(CL:DEFVAR |SGT-SAMPLE-CONTENTS-SAMPLE-SampleNested| NULL)
(CL:DEFVAR |SYM-SAMPLE-CONTENTS-SAMPLE-nestedAttr| NULL)
(CL:DEFVAR |SGT-SAMPLE-CONTENTS-SAMPLE-SampleListItem| NULL)
(CL:DEFVAR |SYM-SAMPLE-CONTENTS-SAMPLE-itemID| NULL)
(CL:DEFVAR SYM-SAMPLE-CONTENTS-SAMPLE-STARTUP-SAMPLE-CONTENTS NULL)
(CL:DEFVAR SYM-SAMPLE-CONTENTS-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM (CL:SPECIAL *STARTUP-TIME-PHASE* *MODULE*))

;;; (DEFCLASS SampleContents ...)

(CL:DEFCLASS |SampleContents| (|XMLObject|)
  ((|sampleAttr| :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR |%sampleAttr|)
   (|sub| :ALLOCATION :INSTANCE :ACCESSOR |%sub|)
   (|SampleListItem| :ALLOCATION :INSTANCE :ACCESSOR |%SampleListItem|)))

(CL:DEFUN |new-SampleContents| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |SampleContents|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%SampleListItem| SELF) NULL) (CL:SETF (|%sub| SELF) NULL)
   (CL:SETF (|%sampleAttr| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |SampleContents|))
  |SGT-SAMPLE-CONTENTS-SAMPLE-SampleContents|)

(CL:DEFUN |access-SampleContents-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-SAMPLE-CONTENTS-SAMPLE-sampleAttr|)
    (CL:IF SETVALUE?
     (CL:SETF (|%sampleAttr| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (|%sampleAttr| SELF)))))
   ((CL:EQ SLOTNAME |SYM-SAMPLE-CONTENTS-SAMPLE-sub|)
    (CL:IF SETVALUE? (CL:SETF (|%sub| SELF) VALUE)
     (CL:SETQ VALUE (|%sub| SELF))))
   ((CL:EQ SLOTNAME |SYM-SAMPLE-CONTENTS-SAMPLE-SampleListItem|)
    (CL:IF SETVALUE? (CL:SETF (|%SampleListItem| SELF) VALUE)
     (CL:SETQ VALUE (|%SampleListItem| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS SampleNested ...)

(CL:DEFCLASS |SampleNested| (|XMLObject|)
  ((|nestedAttr| :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR |%nestedAttr|)))

(CL:DEFUN |new-SampleNested| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |SampleNested|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%nestedAttr| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |SampleNested|))
  |SGT-SAMPLE-CONTENTS-SAMPLE-SampleNested|)

(CL:DEFUN |access-SampleNested-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-SAMPLE-CONTENTS-SAMPLE-nestedAttr|)
    (CL:IF SETVALUE?
     (CL:SETF (|%nestedAttr| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (|%nestedAttr| SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS SampleListItem ...)

(CL:DEFCLASS |SampleListItem| (|XMLObject|)
  ((|itemID| :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR |%itemID|)))

(CL:DEFUN |new-SampleListItem| ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE |SampleListItem|)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%itemID| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF |SampleListItem|))
  |SGT-SAMPLE-CONTENTS-SAMPLE-SampleListItem|)

(CL:DEFUN |access-SampleListItem-Slot-Value| (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-SAMPLE-CONTENTS-SAMPLE-itemID|)
    (CL:IF SETVALUE? (CL:SETF (|%itemID| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (|%itemID| SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

(CL:DEFUN STARTUP-SAMPLE-CONTENTS ()
  (CL:LET*
   ((*MODULE*
     (GET-STELLA-MODULE "/STELLA/XML-OBJECTS/SAMPLE"
      (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2)
    (CL:SETQ |SGT-SAMPLE-CONTENTS-SAMPLE-SampleContents|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "SampleContents" NULL 1))
    (CL:SETQ |SYM-SAMPLE-CONTENTS-SAMPLE-sampleAttr|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "sampleAttr" NULL 0))
    (CL:SETQ |SYM-SAMPLE-CONTENTS-SAMPLE-sub|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "sub" NULL 0))
    (CL:SETQ |SYM-SAMPLE-CONTENTS-SAMPLE-SampleListItem|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "SampleListItem" NULL 0))
    (CL:SETQ |SGT-SAMPLE-CONTENTS-SAMPLE-SampleNested|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "SampleNested" NULL 1))
    (CL:SETQ |SYM-SAMPLE-CONTENTS-SAMPLE-nestedAttr|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "nestedAttr" NULL 0))
    (CL:SETQ |SGT-SAMPLE-CONTENTS-SAMPLE-SampleListItem|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "SampleListItem" NULL 1))
    (CL:SETQ |SYM-SAMPLE-CONTENTS-SAMPLE-itemID|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "itemID" NULL 0))
    (CL:SETQ SYM-SAMPLE-CONTENTS-SAMPLE-STARTUP-SAMPLE-CONTENTS
     (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-SAMPLE-CONTENTS" NULL 0))
    (CL:SETQ SYM-SAMPLE-CONTENTS-STELLA-METHOD-STARTUP-CLASSNAME
     (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 5)
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "SampleContents"
        "(DEFCLASS SampleContents (XMLObject) :PUBLIC-SLOTS ((sampleAttr :TYPE STRING) (sub :TYPE SampleNested) (SampleListItem :TYPE (LIST OF SampleListItem))))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-SampleContents|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-SampleContents-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "SampleNested"
        "(DEFCLASS SampleNested (XMLObject) :PUBLIC-SLOTS ((nestedAttr :TYPE STRING)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-SampleNested|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-SampleNested-Slot-Value|)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "SampleListItem"
        "(DEFCLASS SampleListItem (XMLObject) :PUBLIC-SLOTS ((itemID :TYPE STRING)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION |new-SampleListItem|))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION |access-SampleListItem-Slot-Value|))))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7)
    (DEFINE-FUNCTION-OBJECT "STARTUP-SAMPLE-CONTENTS"
     "(DEFUN STARTUP-SAMPLE-CONTENTS () :PUBLIC? TRUE)"
     (CL:FUNCTION STARTUP-SAMPLE-CONTENTS) NULL)
    (CL:LET*
     ((FUNCTION
       (LOOKUP-FUNCTION
        SYM-SAMPLE-CONTENTS-SAMPLE-STARTUP-SAMPLE-CONTENTS)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-SAMPLE-CONTENTS-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupSampleContents") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "SAMPLE")))
    (INSERT-AT *NAMESPACE-PREFIX-URI-TABLE* (WRAP-STRING "SAMPLE")
     (WRAP-STRING "http://www.isi.edu/powerloom/sample/"))
    (INSERT-AT *NAMESPACE-URI-PREFIX-TABLE*
     (WRAP-STRING "http://www.isi.edu/powerloom/sample/")
     (WRAP-STRING "SAMPLE")))))
