;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; marshaller.lisp

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

(CL:DEFVAR SGT-MARSHALLER-STELLA-CONS NULL)
(CL:DEFVAR |SGT-MARSHALLER-XML-OBJECTS-XMLObject| NULL)
(CL:DEFVAR |SYM-MARSHALLER-XML-OBJECTS-textContent| NULL)
(CL:DEFVAR SGT-MARSHALLER-XML-OBJECTS-ID-PARENT-STRUCT NULL)
(CL:DEFVAR |SYM-MARSHALLER-XML-OBJECTS-id| NULL)
(CL:DEFVAR |SYM-MARSHALLER-XML-OBJECTS-parents| NULL)
(CL:DEFVAR SGT-MARSHALLER-STELLA-XML-ELEMENT NULL)
(CL:DEFVAR SGT-MARSHALLER-STELLA-STRING NULL)
(CL:DEFVAR SGT-MARSHALLER-STELLA-LIST NULL)
(CL:DEFVAR SYM-MARSHALLER-XML-OBJECTS-ENCODING-SCHEME NULL)
(CL:DEFVAR KWD-MARSHALLER-BASE64 NULL)
(CL:DEFVAR KWD-MARSHALLER-PLAIN NULL)
(CL:DEFVAR SGT-MARSHALLER-XML-OBJECTS-A NULL)
(CL:DEFVAR |SYM-MARSHALLER-XML-OBJECTS-b| NULL)
(CL:DEFVAR |SYM-MARSHALLER-XML-OBJECTS-c| NULL)
(CL:DEFVAR SGT-MARSHALLER-XML-OBJECTS-B NULL)
(CL:DEFVAR |SYM-MARSHALLER-XML-OBJECTS-d| NULL)
(CL:DEFVAR SGT-MARSHALLER-XML-OBJECTS-C NULL)
(CL:DEFVAR |SYM-MARSHALLER-XML-OBJECTS-e| NULL)
(CL:DEFVAR SGT-MARSHALLER-XML-OBJECTS-D NULL)
(CL:DEFVAR |SYM-MARSHALLER-XML-OBJECTS-f| NULL)
(CL:DEFVAR SGT-MARSHALLER-XML-OBJECTS-E NULL)
(CL:DEFVAR SGT-MARSHALLER-XML-OBJECTS-F NULL)
(CL:DEFVAR SYM-MARSHALLER-XML-OBJECTS-STARTUP-MARSHALLER NULL)
(CL:DEFVAR SYM-MARSHALLER-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM
 (CL:SPECIAL *STARTUP-TIME-PHASE* NULL-CHARACTER *MODULE*
  *NAMESPACE-URI-PREFIX-TABLE* NULL-STRING-WRAPPER STANDARD-OUTPUT EOL
  *INVISIBLE-NAMESPACES-ON-OUTPUT* *NAMESPACE-PREFIX-URI-TABLE* NIL
  NULL-INTEGER NULL-FLOAT))

;;; (DEFUN (SLOT-VALUE-IS-NULL? BOOLEAN) ...)

(CL:DEFUN SLOT-VALUE-IS-NULL? (|parentObject| |slot|)
  (CL:LET* ((|value| (GET-OBJECT-SLOT-VALUE |parentObject| |slot|)))
   (CL:WHEN (CL:EQ |value| NULL)
    (CL:RETURN-FROM SLOT-VALUE-IS-NULL? CL:T))
   (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE |value|)))
    (CL:COND
     ((SUBTYPE-OF-INTEGER? TEST-VALUE-000)
      (CL:PROGN (CL:= (%WRAPPER-VALUE |value|) NULL-INTEGER)))
     ((SUBTYPE-OF-FLOAT? TEST-VALUE-000)
      (CL:PROGN (CL:= (%WRAPPER-VALUE |value|) NULL-FLOAT)))
     ((SUBTYPE-OF-STRING? TEST-VALUE-000)
      (CL:PROGN (CL:EQ (%WRAPPER-VALUE |value|) STELLA::NULL-STRING)))
     ((SUBTYPE-OF-CHARACTER? TEST-VALUE-000)
      (CL:PROGN (NULL? (%WRAPPER-VALUE |value|))))
     (CL:T CL:NIL)))))

;;; (DEFUN (SLOT-VALUE-IS-NULL-OR-EMPTY? BOOLEAN) ...)

(CL:DEFUN SLOT-VALUE-IS-NULL-OR-EMPTY? (|parentObject| |slot|)
  (CL:LET* ((|value| (GET-OBJECT-SLOT-VALUE |parentObject| |slot|)))
   (CL:OR (CL:EQ |value| NULL) (EMPTY? |value|))))

;;; (DEFSPECIAL *SUPRESS-NAMESPACES?* ...)

(CL:DEFVAR *SUPRESS-NAMESPACES?* CL:NIL
  "If TRUE, don't output namespace declarations and prefixes")

;;; (DEFMETHOD (TO-XML-STRING STRING) ...)

(CL:DEFMETHOD TO-XML-STRING ((|object| |XMLObject|))
  "Convert `object' into it's XML Representation as a string"
  (STRINGIFY-XML (TO-XML |object| NIL)))

;;; (DEFMETHOD TO-XML-STREAM ...)

(CL:DEFMETHOD TO-XML-STREAM ((|object| |XMLObject|) |out|)
  "Write `object' in  it's XML Representation to `out'."
  (PRINT-XML-EXPRESSION |out| (TO-XML |object| NIL) 0))

;;; (DEFMETHOD (TO-XML CONS) ...)

(CL:DEFMETHOD TO-XML ((|object| |XMLObject|) |namespaceStack|)
  (CL:LET*
   ((|objectTag| (MAKE-ELEMENT-TAG |object|))
    (|slots| (GET-MAPPED-SLOTS |object|))
    (|objectNamespace| (GET-NAMESPACE-PREFIX |object|))
    (|newNamespaceStack| |namespaceStack|)
    (|attributeNamespaceName| NULL)
    (|attributeValueNamespaceName| NULL) (|namespaceURI| NULL)
    (|namespaceAttributes| NIL) (|attributes| NIL) (|elements| NIL)
    (|collections| NIL))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |objectNamespace|))
   (CL:WHEN
    (CL:NOT
     (MEMBER? |newNamespaceStack| (WRAP-STRING |objectNamespace|)))
    (CL:SETQ |newNamespaceStack|
     (CONS (WRAP-STRING |objectNamespace|) |newNamespaceStack|))
    (CL:SETQ |namespaceURI|
     (LOOKUP *NAMESPACE-PREFIX-URI-TABLE*
      (WRAP-STRING |objectNamespace|)))
    (CL:WHEN (CL:NOT (CL:EQ |namespaceURI| NULL))
     (CL:SETQ |namespaceAttributes|
      (CONS (MAKE-NAMESPACE-ATTRIBUTE |objectNamespace|)
       |namespaceAttributes|))
     (CL:SETQ |namespaceAttributes|
      (CONS |namespaceURI| |namespaceAttributes|))))
   (CL:LET* ((|slot| NULL) (ITER-000 (%THE-CONS-LIST |slots|)))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ |slot| (%%VALUE ITER-000))
     (CL:WHEN
      (CL:AND (ATTRIBUTE-SLOT? |slot|)
       (CL:NOT (SLOT-VALUE-IS-NULL? |object| |slot|)))
      (CL:SETQ |attributes|
       (APPEND (MAKE-REVERSED-ATTRIBUTE |object| |slot|) |attributes|))
      (CL:SETQ |attributeNamespaceName|
       (WRAP-STRING
        (%MODULE-NAME (%HOME-CONTEXT (%SLOT-NAME |slot|)))))
      (CL:WHEN
       (CL:NOT (MEMBER? |newNamespaceStack| |attributeNamespaceName|))
       (CL:SETQ |newNamespaceStack|
        (CONS |attributeNamespaceName| |newNamespaceStack|))
       (CL:SETQ |namespaceURI|
        (LOOKUP *NAMESPACE-PREFIX-URI-TABLE* |attributeNamespaceName|))
       (CL:WHEN (CL:NOT (CL:EQ |namespaceURI| NULL))
        (CL:SETQ |namespaceAttributes|
         (CONS
          (MAKE-NAMESPACE-ATTRIBUTE
           (%WRAPPER-VALUE |attributeNamespaceName|))
          |namespaceAttributes|))
        (CL:SETQ |namespaceAttributes|
         (CONS |namespaceURI| |namespaceAttributes|))))
      (CL:SETQ |attributeValueNamespaceName|
       (GET-ATTRIBUTE-VALUE-NAMESPACE-NAME |object| |slot|))
      (CL:WHEN
       (CL:NOT
        (CL:OR (CL:EQ |attributeValueNamespaceName| NULL)
         (MEMBER? |newNamespaceStack| |attributeValueNamespaceName|)))
       (CL:SETQ |newNamespaceStack|
        (CONS |attributeValueNamespaceName| |newNamespaceStack|))
       (CL:SETQ |namespaceURI|
        (LOOKUP *NAMESPACE-PREFIX-URI-TABLE*
         |attributeValueNamespaceName|))
       (CL:WHEN (CL:NOT (CL:EQ |namespaceURI| NULL))
        (CL:SETQ |namespaceAttributes|
         (CONS
          (MAKE-NAMESPACE-ATTRIBUTE
           (%WRAPPER-VALUE |attributeValueNamespaceName|))
          |namespaceAttributes|))
        (CL:SETQ |namespaceAttributes|
         (CONS |namespaceURI| |namespaceAttributes|)))))
     (CL:SETQ ITER-000 (%%REST ITER-000))))
   (CL:LET* ((|slot| NULL) (ITER-001 (%THE-CONS-LIST |slots|)))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
     (CL:SETQ |slot| (%%VALUE ITER-001))
     (CL:COND
      ((ELEMENT-SLOT? |slot|)
       (CL:WHEN (CL:NOT (SLOT-VALUE-IS-NULL? |object| |slot|))
        (CL:SETQ |elements|
         (CONS (MAKE-ELEMENT |object| |slot| |newNamespaceStack|)
          |elements|))))
      ((COLLECTION-SLOT? |slot|)
       (CL:WHEN (CL:NOT (SLOT-VALUE-IS-NULL-OR-EMPTY? |object| |slot|))
        (CL:SETQ |collections|
         (CONS (MAKE-COLLECTION |object| |slot| |newNamespaceStack|)
          |collections|)))))
     (CL:SETQ ITER-001 (%%REST ITER-001))))
   (CONS |objectTag|
    (CONS
     (CONCATENATE (REVERSE |namespaceAttributes|)
      (CONCATENATE (REVERSE |attributes|) NIL))
     (CONCATENATE (REVERSE |elements|)
      (CONCATENATE (REVERSE |collections|)
       (CONCATENATE (MAKE-CONTENT-EXPRESSION |object|) NIL)))))))

;;; (DEFUN (GET-NAMESPACE-PREFIX STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T) CL:SIMPLE-STRING) GET-NAMESPACE-PREFIX))
(CL:DEFUN GET-NAMESPACE-PREFIX (|object|)
  (CL:LET*
   ((|theClass| (%SURROGATE-VALUE (PRIMARY-TYPE |object|)))
    (|module| (HOME-MODULE |theClass|)))
   (%MODULE-NAME |module|)))

;;; (DEFUN (GET-NAMESPACE-URI STRING-WRAPPER) ...)

(CL:DEFUN GET-NAMESPACE-URI (|namespacePrefix|)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |namespacePrefix|))
  #+MCL
  (CL:CHECK-TYPE |namespacePrefix| CL:SIMPLE-STRING)
  (CL:LET*
   ((|uri|
     (LOOKUP *NAMESPACE-PREFIX-URI-TABLE*
      (WRAP-STRING |namespacePrefix|))))
   (CL:IF (CL:NOT (CL:EQ |uri| NULL)) |uri| NULL)))

;;; (DEFUN (MAKE-CONTENT-EXPRESSION CONS) ...)

(CL:DEFUN MAKE-CONTENT-EXPRESSION (|object|)
  (CL:LET*
   ((|result| NIL) (|content| (|%textContent| |object|))
    (|cdata| (|%cdataContent| |object|)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |content| |cdata|))
   (CL:WHEN (CL:NOT (CL:EQ |content| STELLA::NULL-STRING))
    (CL:SETQ |result| (CONS (WRAP-STRING |content|) |result|)))
   (CL:WHEN (CL:NOT (CL:EQ |cdata| STELLA::NULL-STRING))
    (CL:SETQ |result| (CONS (MAKE-XML-CDATA-FORM |cdata|) |result|)))
   |result|))

;;; (DEFUN (MAKE-ELEMENT-TAG XML-ELEMENT) ...)

(CL:DEFUN MAKE-ELEMENT-TAG (|object|)
  (CL:LET*
   ((|tagType| (GET-ELEMENT-NAME-FROM-OBJECT |object|))
    (|namespacePrefix| (GET-NAMESPACE-PREFIX |object|))
    (|namespaceURI| (GET-NAMESPACE-URI |namespacePrefix|)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |tagType| |namespacePrefix|))
   (CL:IF
    (CL:OR (CL:EQ |namespaceURI| NULL)
     (CL:AND *SUPRESS-NAMESPACES?*
      (MEMBER? *INVISIBLE-NAMESPACES-ON-OUTPUT*
       (WRAP-STRING |namespacePrefix|))))
    (CL:LET* ((SELF-000 (NEW-XML-ELEMENT)))
     (CL:SETF (%NAME SELF-000) |tagType|)
     (CL:SETF (%SURFACE-FORM SELF-000) |tagType|)
     (CL:LET* ((VALUE-000 SELF-000)) VALUE-000))
    (CL:LET* ((SELF-001 (NEW-XML-ELEMENT)))
     (CL:SETF (%NAME SELF-001) |tagType|)
     (CL:SETF (%SURFACE-FORM SELF-001)
      (CONCATENATE |namespacePrefix| ":" |tagType|))
     (CL:SETF (%NAMESPACE-NAME SELF-001) |namespacePrefix|)
     (CL:SETF (%NAMESPACE-URI SELF-001)
      (%WRAPPER-VALUE |namespaceURI|))
     (CL:LET* ((VALUE-001 SELF-001)) VALUE-001)))))

;;; (DEFUN (MAKE-NAMESPACE-ATTRIBUTE XML-ATTRIBUTE) ...)

(CL:DEFUN MAKE-NAMESPACE-ATTRIBUTE (|namespaceName|)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |namespaceName|))
  #+MCL
  (CL:CHECK-TYPE |namespaceName| CL:SIMPLE-STRING)
  (CL:LET* ((SELF-000 (NEW-XML-GLOBAL-ATTRIBUTE)))
   (CL:SETF (%SURFACE-FORM SELF-000)
    (CONCATENATE "xmlns:" |namespaceName|))
   (CL:SETF (%NAME SELF-000) |namespaceName|)
   (CL:SETF (%NAMESPACE-NAME SELF-000) "xmlns")
   (CL:LET* ((VALUE-000 SELF-000)) VALUE-000)))

;;; (DEFUN (GET-ATTRIBUTE-VALUE-NAMESPACE-NAME STRING-WRAPPER) ...)

(CL:DEFUN GET-ATTRIBUTE-VALUE-NAMESPACE-NAME (|parentObject| |slot|)
  (CL:LET*
   ((|attributeValue|
     (UNWRAP-STRING (GET-OBJECT-SLOT-VALUE |parentObject| |slot|))))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |attributeValue|))
   (CL:WHEN (CL:NOT (CL:EQ |attributeValue| STELLA::NULL-STRING))
    (CL:LET*
     ((|valueNamespaceName|
       (GET-VALUE-NAMESPACE-PREFIX |attributeValue|)))
     (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |valueNamespaceName|))
     (CL:WHEN
      (CL:AND (CL:NOT (CL:EQ |valueNamespaceName| STELLA::NULL-STRING))
       (CL:NOT
        (CL:EQ
         (LOOKUP *NAMESPACE-PREFIX-URI-TABLE*
          (WRAP-STRING |valueNamespaceName|))
         NULL)))
      (CL:RETURN-FROM GET-ATTRIBUTE-VALUE-NAMESPACE-NAME
       (WRAP-STRING |valueNamespaceName|)))))
   NULL))

;;; (DEFUN (GET-VALUE-NAMESPACE-PREFIX STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:SIMPLE-STRING) CL:SIMPLE-STRING)
  GET-VALUE-NAMESPACE-PREFIX))
(CL:DEFUN GET-VALUE-NAMESPACE-PREFIX (|valueString|)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |valueString|))
  #+MCL
  (CL:CHECK-TYPE |valueString| CL:SIMPLE-STRING)
  (CL:LET* ((|colonPos| (STRING-SEARCH |valueString| ":" 0)))
   (CL:DECLARE (CL:TYPE CL:FIXNUM |colonPos|))
   (CL:WHEN (CL:NOT (CL:= |colonPos| NULL-INTEGER))
    (CL:RETURN-FROM GET-VALUE-NAMESPACE-PREFIX
     (SUBSEQUENCE |valueString| 0 |colonPos|)))
   STELLA::NULL-STRING))

;;; (DEFUN (MAKE-REVERSED-ATTRIBUTE CONS) ...)

(CL:DEFUN MAKE-REVERSED-ATTRIBUTE (|parentObject| |slot|)
  (CL:LET*
   ((|attributeName| (%SLOT-NAME |slot|))
    (|namespacePrefix| (%MODULE-NAME (%HOME-CONTEXT |attributeName|)))
    (|attributeValue| (GET-OBJECT-SLOT-VALUE |parentObject| |slot|))
    (|namespaceURI| (GET-NAMESPACE-URI |namespacePrefix|)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |namespacePrefix|))
   (CL:LET* ((CHOOSE-VALUE-000 NULL))
    (CL:IF
     (CL:OR (CL:EQ |namespaceURI| NULL)
      (CL:AND *SUPRESS-NAMESPACES?*
       (MEMBER? *INVISIBLE-NAMESPACES-ON-OUTPUT*
        (WRAP-STRING |namespacePrefix|))))
     (CL:LET* ((SELF-000 (NEW-XML-LOCAL-ATTRIBUTE)))
      (CL:SETF (%NAME SELF-000) (%SYMBOL-NAME |attributeName|))
      (CL:SETF (%SURFACE-FORM SELF-000) (%SYMBOL-NAME |attributeName|))
      (CL:SETQ CHOOSE-VALUE-000 SELF-000))
     (CL:LET* ((SELF-001 (NEW-XML-GLOBAL-ATTRIBUTE)))
      (CL:SETF (%NAME SELF-001) (%SYMBOL-NAME |attributeName|))
      (CL:SETF (%SURFACE-FORM SELF-001)
       (CONCATENATE |namespacePrefix| ":"
        (%SYMBOL-NAME |attributeName|)))
      (CL:SETF (%NAMESPACE-NAME SELF-001) |namespacePrefix|)
      (CL:SETF (%NAMESPACE-URI SELF-001)
       (%WRAPPER-VALUE |namespaceURI|))
      (CL:SETQ CHOOSE-VALUE-000 SELF-001)))
    (CL:LET* ((|attribute| CHOOSE-VALUE-000))
     (CONS |attributeValue| (CONS |attribute| NIL))))))

;;; (DEFUN (MAKE-ELEMENT CONS) ...)

(CL:DEFUN MAKE-ELEMENT (|parentObject| |slot| |namespaceStack|)
  (TO-XML (GET-OBJECT-SLOT-VALUE |parentObject| |slot|)
   |namespaceStack|))

;;; (DEFUN (MAKE-COLLECTION CONS) ...)

(CL:DEFUN MAKE-COLLECTION (|parentObject| |slot| |namespaceStack|)
  (CL:LET*
   ((|elements| (GET-OBJECT-SLOT-VALUE |parentObject| |slot|))
    (|result| NIL))
   (CL:LET*
    ((|element| NULL) (ITER-000 (%THE-CONS-LIST |elements|))
     (COLLECT-000 NULL))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ |element| (%%VALUE ITER-000))
     (CL:IF (CL:EQ COLLECT-000 NULL)
      (CL:PROGN
       (CL:SETQ COLLECT-000
        (CONS (TO-XML |element| |namespaceStack|) NIL))
       (CL:IF (CL:EQ |result| NIL) (CL:SETQ |result| COLLECT-000)
        (ADD-CONS-TO-END-OF-CONS-LIST |result| COLLECT-000)))
      (CL:PROGN
       (CL:SETF (%%REST COLLECT-000)
        (CONS (TO-XML |element| |namespaceStack|) NIL))
       (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))
     (CL:SETQ ITER-000 (%%REST ITER-000))))
   |result|))

;;; (DEFUN (FROM-XML-STRING XMLObject) ...)

(CL:DEFUN FROM-XML-STRING (|xmlString|)
  "Convert XML into an object."
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |xmlString|))
  #+MCL
  (CL:CHECK-TYPE |xmlString| CL:SIMPLE-STRING)
  (FROM-XML (PARSE-XML |xmlString| CL:T)))

;;; (DEFUN (FROM-XML-STREAM XMLObject) ...)

(CL:DEFUN FROM-XML-STREAM (|in|)
  "Convert XML into an object."
  (FROM-XML (PARSE-XML-FROM-STREAM |in| CL:T)))

;;; (DEFUN (FROM-XML XMLObject) ...)

(CL:DEFUN FROM-XML (|expr|)
  (CL:LET*
   ((|elementName| (GET-ELEMENT-NAME-FROM-EXPR |expr|))
    (|elementNamespaceName|
     (GET-ELEMENT-NAMESPACE-PREFIX-FROM-EXPR |expr|))
    (|elementNamespaceURI|
     (GET-ELEMENT-NAMESPACE-URI-FROM-EXPR |expr|))
    (|attributeExpressions| (%%VALUE (%%REST |expr|)))
    (|elementExpressions| (%%REST (%%REST |expr|)))
    (|theObject|
     (MAKE-XML-OBJECT (%WRAPPER-VALUE |elementName|)
      (%WRAPPER-VALUE |elementNamespaceName|)
      (%WRAPPER-VALUE |elementNamespaceURI|))))
   (SET-ATTRIBUTES |theObject| |attributeExpressions|)
   (SET-ELEMENTS |theObject| |elementExpressions|)
   (SET-COLLECTIONS |theObject| |elementExpressions|) |theObject|))

;;; (DEFUN SET-ELEMENTS ...)

(CL:DEFUN SET-ELEMENTS (|object| |elementExprs|)
  (CL:LET* ((|expr| NULL) (ITER-000 |elementExprs|))
   (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
    (CL:SETQ |expr| (%%VALUE ITER-000))
    (CL:COND
     ((SUBTYPE-OF-STRING? (SAFE-PRIMARY-TYPE |expr|))
      (CL:PROGN
       (SET-OBJECT-SLOT-VALUE |object| (LOOKUP-CONTENT-SLOT |object|)
        |expr|)))
     (CL:T
      (CL:IF
       (CL:AND (ISA? |expr| SGT-MARSHALLER-STELLA-CONS)
        (XML-CDATA? (%%VALUE |expr|)))
       (CL:SETF (|%cdataContent| |object|)
        (UNWRAP-STRING (%%VALUE (%%VALUE (%%REST |expr|)))))
       (CL:LET*
        ((|matchingSlot| (LOOKUP-ELEMENT-SLOT |object| |expr|)))
        (CL:WHEN (CL:NOT (CL:EQ |matchingSlot| NULL))
         (CL:LET* ((|value| (FROM-XML |expr|)))
          (SET-OBJECT-SLOT-VALUE |object| |matchingSlot| |value|)))))))
    (CL:SETQ ITER-000 (%%REST ITER-000)))))

;;; (DEFUN SET-ATTRIBUTES ...)

(CL:DEFUN SET-ATTRIBUTES (|object| |attributeExprs|)
  (CL:LET* ((SELF-000 (NEW-PROPERTY-LIST)))
   (CL:SETF (%THE-PLIST SELF-000) |attributeExprs|)
   (CL:LET* ((|plist| SELF-000))
    (CL:LET*
     ((|attribute| NULL) (|value| NULL)
      (ITER-000 (%THE-PLIST |plist|)))
     (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
      (CL:SETQ |attribute| (%%VALUE ITER-000))
      (CL:SETQ |value| (%%VALUE (%%REST ITER-000)))
      (CL:LET*
       ((|matchingSlot| (LOOKUP-ATTRIBUTE-SLOT |object| |attribute|)))
       (CL:WHEN (CL:NOT (CL:EQ |matchingSlot| NULL))
        (SET-OBJECT-SLOT-VALUE |object| |matchingSlot| |value|)))
      (CL:SETQ ITER-000 (%%REST (%%REST ITER-000))))))))

;;; (DEFUN SET-COLLECTIONS ...)

(CL:DEFUN SET-COLLECTIONS (|object| |elementExprs|)
  (CL:LET* ((|expr| NULL) (ITER-000 |elementExprs|))
   (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
    (CL:SETQ |expr| (%%VALUE ITER-000))
    (CL:COND
     ((SUBTYPE-OF-STRING? (SAFE-PRIMARY-TYPE |expr|)) (CL:PROGN))
     (CL:T
      (CL:LET*
       ((|matchingSlot| (LOOKUP-COLLECTION-SLOT |object| |expr|)))
       (CL:WHEN (CL:NOT (CL:EQ |matchingSlot| NULL))
        (CL:LET* ((|value| (FROM-XML |expr|)))
         (SET-COLLECTION-SLOT-VALUE |object| |matchingSlot|
          |value|))))))
    (CL:SETQ ITER-000 (%%REST ITER-000)))))

;;; (DEFUN (GET-MAPPED-SLOTS (LIST OF SLOT)) ...)

(CL:DEFUN GET-MAPPED-SLOTS (|object|)
  (%CLASS-LOCAL-SLOTS (%SURROGATE-VALUE (PRIMARY-TYPE |object|))))

;;; (DEFUN (SLOT-REPRESENTS-TAG? BOOLEAN) ...)

(CL:DEFUN SLOT-REPRESENTS-TAG? (|slot| |tag| |useType?| |useParametricType?|)
  (CL:LET* ((|name| (%NAME |tag|)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |name|))
   (CL:WHEN (STRING-EQL? |name| (%SYMBOL-NAME (%SLOT-NAME |slot|)))
    (CL:RETURN-FROM SLOT-REPRESENTS-TAG? CL:T))
   (CL:WHEN (CL:OR |useType?| |useParametricType?|)
    (CL:LET* ((|slotType| NULL) (|slotParametricType| NULL))
     (CL:MULTIPLE-VALUE-SETQ (|slotType| |slotParametricType|)
      (SLOT-BASE-AND-PARAMETER-TYPE |slot|))
     (CL:WHEN
      (CL:AND |useType?|
       (STRING-EQL? |name| (%SYMBOL-NAME |slotType|)))
      (CL:RETURN-FROM SLOT-REPRESENTS-TAG? CL:T))
     (CL:WHEN
      (CL:AND |useParametricType?|
       (STRING-EQL? |name| (%SYMBOL-NAME |slotParametricType|)))
      (CL:RETURN-FROM SLOT-REPRESENTS-TAG? CL:T))))
   CL:NIL))

;;; (DEFUN (LOOKUP-ELEMENT-SLOT STORAGE-SLOT) ...)

(CL:DEFUN LOOKUP-ELEMENT-SLOT (|object| |elementExpr|)
  (CL:LET* ((|tag| (%%VALUE |elementExpr|)) (|general-slots| NIL))
   (CL:LET*
    ((|slot| NULL)
     (ITER-000 (%THE-CONS-LIST (GET-MAPPED-SLOTS |object|))))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ |slot| (%%VALUE ITER-000))
     (CL:WHEN (ELEMENT-SLOT? |slot|)
      (CL:COND
       ((SLOT-REPRESENTS-TAG? |slot| |tag| CL:T CL:NIL)
        (CL:RETURN-FROM LOOKUP-ELEMENT-SLOT |slot|))
       ((CL:EQ (TYPE-SPECIFIER |slot|)
         |SGT-MARSHALLER-XML-OBJECTS-XMLObject|)
        (CL:SETQ |general-slots| (CONS |slot| |general-slots|)))
       (CL:T)))
     (CL:SETQ ITER-000 (%%REST ITER-000))))
   (CL:COND ((CL:EQ |general-slots| NIL) NULL)
    ((CL:EQ (%%REST |general-slots|) NIL) (%%VALUE |general-slots|))
    (CL:T NULL))))

;;; (DEFUN (LOOKUP-ATTRIBUTE-SLOT STORAGE-SLOT) ...)

(CL:DEFUN LOOKUP-ATTRIBUTE-SLOT (|object| |attribute|)
  (CL:LET*
   ((|slot| NULL)
    (ITER-000 (%THE-CONS-LIST (GET-MAPPED-SLOTS |object|))))
   (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
    (CL:SETQ |slot| (%%VALUE ITER-000))
    (CL:WHEN
     (CL:AND (ATTRIBUTE-SLOT? |slot|)
      (SLOT-REPRESENTS-TAG? |slot| |attribute| CL:NIL CL:NIL))
     (CL:RETURN-FROM LOOKUP-ATTRIBUTE-SLOT |slot|))
    (CL:SETQ ITER-000 (%%REST ITER-000))))
  NULL)

;;; (DEFUN (LOOKUP-COLLECTION-SLOT STORAGE-SLOT) ...)

(CL:DEFUN LOOKUP-COLLECTION-SLOT (|object| |elementExpr|)
  (CL:LET* ((|tag| (%%VALUE |elementExpr|)))
   (CL:LET*
    ((|slot| NULL)
     (ITER-000 (%THE-CONS-LIST (GET-MAPPED-SLOTS |object|))))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ |slot| (%%VALUE ITER-000))
     (CL:WHEN
      (CL:AND (COLLECTION-SLOT? |slot|)
       (SLOT-REPRESENTS-TAG? |slot| |tag| CL:NIL CL:T))
      (CL:RETURN-FROM LOOKUP-COLLECTION-SLOT |slot|))
     (CL:SETQ ITER-000 (%%REST ITER-000))))
   NULL))

;;; (DEFUN (LOOKUP-CONTENT-SLOT STORAGE-SLOT) ...)

(CL:DEFUN LOOKUP-CONTENT-SLOT (|object|)
  (LOOKUP-SLOT (PRIMARY-CLASS |object|)
   |SYM-MARSHALLER-XML-OBJECTS-textContent|))

;;; (DEFCLASS ID-PARENT-STRUCT ...)

(CL:DEFCLASS ID-PARENT-STRUCT (OBJECT)
  ((|id| :TYPE CL:FIXNUM :INITFORM NULL-INTEGER :ALLOCATION :INSTANCE
    :ACCESSOR |%id|)
   (|parents| :ALLOCATION :INSTANCE :ACCESSOR |%parents|)))

(CL:DEFUN NEW-ID-PARENT-STRUCT ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE ID-PARENT-STRUCT)))
   (CL:SETF (|%parents| SELF) NULL) (CL:SETF (|%id| SELF) NULL-INTEGER)
   SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF ID-PARENT-STRUCT))
  SGT-MARSHALLER-XML-OBJECTS-ID-PARENT-STRUCT)

(CL:DEFUN ACCESS-ID-PARENT-STRUCT-SLOT-VALUE (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-MARSHALLER-XML-OBJECTS-id|)
    (CL:IF SETVALUE? (CL:SETF (|%id| SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-INTEGER (|%id| SELF)))))
   ((CL:EQ SLOTNAME |SYM-MARSHALLER-XML-OBJECTS-parents|)
    (CL:IF SETVALUE? (CL:SETF (|%parents| SELF) VALUE)
     (CL:SETQ VALUE (|%parents| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFGLOBAL *NODE-PARENTS-TABLE* ...)

(CL:DEFVAR *NODE-PARENTS-TABLE* NULL)

;;; (DEFGLOBAL *NODE-ID-PARENTS-TABLE* ...)

(CL:DEFVAR *NODE-ID-PARENTS-TABLE* NULL)

;;; (DEFGLOBAL *CURRENT-ID* ...)

(CL:DEFVAR *CURRENT-ID* 0)
(CL:DECLAIM (CL:TYPE CL:FIXNUM *CURRENT-ID*))

;;; (DEFUN RESET-MULTIREF-TABLES ...)

(CL:DEFUN RESET-MULTIREF-TABLES ()
  (CL:SETQ *NODE-PARENTS-TABLE* (NEW-PROPERTY-LIST))
  (CL:SETQ *NODE-ID-PARENTS-TABLE* (NEW-HASH-TABLE))
  (CL:SETQ *CURRENT-ID* 0))

;;; (DEFUN (GET-NEXT-ID INTEGER) ...)

(CL:DECLAIM (CL:FTYPE (CL:FUNCTION () CL:FIXNUM) GET-NEXT-ID))
(CL:DEFUN GET-NEXT-ID ()
  (CL:LET* ((|currentID| *CURRENT-ID*))
   (CL:DECLARE (CL:TYPE CL:FIXNUM |currentID|))
   (CL:SETQ *CURRENT-ID* (CL:1+ *CURRENT-ID*)) |currentID|))

;;; (DEFUN (INSERT-NODE-PARENTS-TABLE BOOLEAN) ...)

(CL:DEFUN INSERT-NODE-PARENTS-TABLE (|node| |parent|)
  (CL:WHEN (CL:EQ |parent| NULL)
   (CL:RETURN-FROM INSERT-NODE-PARENTS-TABLE CL:T))
  (CL:LET*
   ((|parents| (LOOKUP *NODE-PARENTS-TABLE* |node|)) (|result| CL:NIL))
   (CL:WHEN (CL:EQ |parents| NULL) (CL:SETQ |result| CL:T)
    (CL:SETQ |parents| (NEW-LIST))
    (INSERT-AT *NODE-PARENTS-TABLE* |node| |parents|))
   (INSERT |parents| |parent|) |result|))

;;; (DEFUN INSERT-NODE-ID-PARENTS-TABLE ...)

(CL:DEFUN INSERT-NODE-ID-PARENTS-TABLE (|node| |parent|)
  (CL:LET*
   ((|idParentStruct| (LOOKUP *NODE-ID-PARENTS-TABLE* |node|))
    (|parents| NULL))
   (CL:IF (CL:EQ |idParentStruct| NULL)
    (CL:PROGN (CL:SETQ |idParentStruct| (NEW-ID-PARENT-STRUCT))
     (CL:SETQ |parents| (NEW-LIST))
     (CL:SETF (|%id| |idParentStruct|) (GET-NEXT-ID))
     (CL:SETF (|%parents| |idParentStruct|) |parents|)
     (INSERT-AT *NODE-ID-PARENTS-TABLE* |node| |idParentStruct|))
    (CL:SETQ |parents| (|%parents| |idParentStruct|)))
   (INSERT |parents| |parent|)))

;;; (DEFUN (GET-CHILDREN (CONS OF XMLObject)) ...)

(CL:DEFUN GET-CHILDREN (|node|)
  (CL:LET* ((|result| NIL))
   (CL:LET*
    ((|slot| NULL)
     (ITER-000 (%THE-CONS-LIST (GET-MAPPED-SLOTS |node|))))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ |slot| (%%VALUE ITER-000))
     (CL:WHEN
      (CL:AND (ELEMENT-SLOT? |slot|)
       (CL:NOT (SLOT-VALUE-IS-NULL? |node| |slot|)))
      (CL:SETQ |result|
       (CONS (GET-OBJECT-SLOT-VALUE |node| |slot|) |result|)))
     (CL:SETQ ITER-000 (%%REST ITER-000))))
   |result|))

;;; (DEFUN POPULATE-NODE-PARENTS-TABLE ...)

(CL:DEFUN POPULATE-NODE-PARENTS-TABLE (|node|)
  (HELP-POPULATE-NODE-PARENTS-TABLE |node| NULL))

;;; (DEFUN HELP-POPULATE-NODE-PARENTS-TABLE ...)

(CL:DEFUN HELP-POPULATE-NODE-PARENTS-TABLE (|node| |parent|)
  (CL:LET*
   ((|children| (GET-CHILDREN |node|))
    (|firstVisit?| (INSERT-NODE-PARENTS-TABLE |node| |parent|)))
   (CL:WHEN |firstVisit?|
    (CL:LET* ((|child| NULL) (ITER-000 |children|))
     (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
      (CL:SETQ |child| (%%VALUE ITER-000))
      (HELP-POPULATE-NODE-PARENTS-TABLE |child| |node|)
      (CL:SETQ ITER-000 (%%REST ITER-000)))))))

;;; (DEFUN CREATE-NODE-ID-PARENT-TABLE ...)

(CL:DEFUN CREATE-NODE-ID-PARENT-TABLE ()
  (CL:LET*
   ((|node| NULL) (|parents| NULL)
    (ITER-000 (%THE-PLIST *NODE-PARENTS-TABLE*)))
   (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
    (CL:SETQ |node| (%%VALUE ITER-000))
    (CL:SETQ |parents| (%%VALUE (%%REST ITER-000)))
    (CL:PROGN
     (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "node = " |node|
      ", parents = " |parents| EOL)
     (CL:WHEN (CL:> (LENGTH |parents|) 1)
      (CL:LET* ((|parent| NULL) (ITER-001 (%THE-CONS-LIST |parents|)))
       (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
        (CL:SETQ |parent| (%%VALUE ITER-001))
        (INSERT-NODE-ID-PARENTS-TABLE |node| |parent|)
        (CL:SETQ ITER-001 (%%REST ITER-001))))))
    (CL:SETQ ITER-000 (%%REST (%%REST ITER-000))))))

;;; (DEFUN SIMULATE-MULTIREF-OUTPUT ...)

(CL:DEFUN SIMULATE-MULTIREF-OUTPUT (|node|)
  (HELP-SIMULATE-MULTIREF-OUTPUT |node| NULL 0))

;;; (DEFUN (FIRST-PARENT-FOR-MULTIREF-NODE? BOOLEAN) ...)

(CL:DEFUN FIRST-PARENT-FOR-MULTIREF-NODE? (|node| |parent|)
  (CL:LET*
   ((|idParentsStruct| (LOOKUP *NODE-ID-PARENTS-TABLE* |node|)))
   (CL:AND (CL:NOT (CL:EQ |idParentsStruct| NULL))
    (CL:EQ (FIRST (|%parents| |idParentsStruct|)) |parent|))))

;;; (DEFUN (NTH-PARENT-FOR-MULTIREF-NODE? BOOLEAN) ...)

(CL:DEFUN NTH-PARENT-FOR-MULTIREF-NODE? (|node| |parent|)
  (CL:LET*
   ((|idParentsStruct| (LOOKUP *NODE-ID-PARENTS-TABLE* |node|)))
   (CL:AND (CL:NOT (CL:EQ |idParentsStruct| NULL))
    (CL:NOT (CL:EQ (FIRST (|%parents| |idParentsStruct|)) |parent|)))))

;;; (DEFUN (GET-NODE-ID INTEGER) ...)

(CL:DECLAIM (CL:FTYPE (CL:FUNCTION (CL:T) CL:FIXNUM) GET-NODE-ID))
(CL:DEFUN GET-NODE-ID (|node|)
  (CL:LET*
   ((|idParentsStruct| (LOOKUP *NODE-ID-PARENTS-TABLE* |node|)))
   (|%id| |idParentsStruct|)))

;;; (DEFUN HELP-SIMULATE-MULTIREF-OUTPUT ...)

(CL:DEFUN HELP-SIMULATE-MULTIREF-OUTPUT (|node| |parent| |indent|)
  (CL:DECLARE (CL:TYPE CL:FIXNUM |indent|))
  #+MCL
  (CL:CHECK-TYPE |indent| CL:FIXNUM)
  (CL:LET*
   ((|nodeName| (GET-ELEMENT-NAME-FROM-OBJECT |node|))
    (|children| (GET-CHILDREN |node|)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |nodeName|))
   (CL:LET*
    ((I NULL-INTEGER) (ITER-000 1) (UPPER-BOUND-000 |indent|)
     (UNBOUNDED?-000 (CL:= UPPER-BOUND-000 NULL-INTEGER)))
    (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-000 UPPER-BOUND-000))
    (CL:LOOP WHILE
     (CL:OR UNBOUNDED?-000 (CL:<= ITER-000 UPPER-BOUND-000)) DO
     (CL:SETQ I ITER-000) (CL:SETQ I I)
     (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) " ")
     (CL:SETQ ITER-000 (CL:1+ ITER-000))))
   (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) |nodeName|)
   (CL:COND
    ((FIRST-PARENT-FOR-MULTIREF-NODE? |node| |parent|)
     (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) " id="
      (GET-NODE-ID |node|)))
    ((NTH-PARENT-FOR-MULTIREF-NODE? |node| |parent|)
     (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) " href="
      (GET-NODE-ID |node|))))
   (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) EOL)
   (CL:LET* ((|child| NULL) (ITER-001 |children|))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
     (CL:SETQ |child| (%%VALUE ITER-001))
     (HELP-SIMULATE-MULTIREF-OUTPUT |child| |node| (CL:+ |indent| 2))
     (CL:SETQ ITER-001 (%%REST ITER-001))))))

;;; (DEFUN (SLOT-BASE-AND-PARAMETER-TYPE TYPE TYPE-SPEC) ...)

(CL:DEFUN SLOT-BASE-AND-PARAMETER-TYPE (|slot|)
  (CL:LET* ((|typeSpec| (TYPE-SPECIFIER |slot|)))
   (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE |typeSpec|)))
    (CL:COND
     ((SUBTYPE-OF-SURROGATE? TEST-VALUE-000)
      (CL:PROGN (CL:VALUES |typeSpec| NULL)))
     ((SUBTYPE-OF-PARAMETRIC-TYPE-SPECIFIER? TEST-VALUE-000)
      (CL:PROGN
       (CL:VALUES (%SPECIFIER-BASE-TYPE |typeSpec|)
        (FIRST (%SPECIFIER-PARAMETER-TYPES |typeSpec|)))))
     (CL:T (CL:VALUES (TYPE |slot|) NULL))))))

;;; (DEFUN (PARSE-XML-FROM-STREAM CONS) ...)

(CL:DEFUN PARSE-XML-FROM-STREAM (|in| |skipFrontmatter?|)
  (CL:LET* ((|item| NULL) (ITER-000 (XML-EXPRESSIONS |in| NULL)))
   (CL:LOOP WHILE (NEXT? ITER-000) DO
    (CL:SETQ |item| (%VALUE ITER-000))
    (CL:WHEN
     (CL:OR (CL:NOT |skipFrontmatter?|)
      (CL:AND (ISA? |item| SGT-MARSHALLER-STELLA-CONS)
       (ISA? (%%VALUE |item|) SGT-MARSHALLER-STELLA-XML-ELEMENT))
      (CL:AND (ISA? |item| SGT-MARSHALLER-STELLA-CONS)
       (XML-CDATA? (%%VALUE |item|))))
     (CL:RETURN-FROM PARSE-XML-FROM-STREAM |item|))))
  NIL)

;;; (DEFUN (PARSE-XML CONS) ...)

(CL:DEFUN PARSE-XML (|string| |skipFrontmatter?|)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |string|))
  #+MCL
  (CL:CHECK-TYPE |string| CL:SIMPLE-STRING)
  (PARSE-XML-FROM-STREAM (NEW-INPUT-STRING-STREAM |string|)
   |skipFrontmatter?|))

;;; (DEFUN (FIND-SLOT SLOT) ...)

(CL:DEFUN FIND-SLOT (|name| |slots| |useParametricType?| |useType?|)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |name|))
  #+MCL
  (CL:CHECK-TYPE |name| CL:SIMPLE-STRING)
  (CL:WHEN
   (CL:AND |useType?| (CL:= (LENGTH |slots|) 1)
    (CL:EQ (SLOT-BASE-AND-PARAMETER-TYPE (FIRST |slots|))
     |SGT-MARSHALLER-XML-OBJECTS-XMLObject|))
   (CL:RETURN-FROM FIND-SLOT (FIRST |slots|)))
  (CL:LET* ((|result| NULL))
   (CL:LET* ((|slot| NULL) (ITER-000 (%THE-CONS-LIST |slots|)))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ |slot| (%%VALUE ITER-000))
     (CL:LET* ((|slotType| NULL) (|slotParametricType| NULL))
      (CL:MULTIPLE-VALUE-SETQ (|slotType| |slotParametricType|)
       (SLOT-BASE-AND-PARAMETER-TYPE |slot|))
      (CL:WHEN
       (CL:OR
        (CL:AND |useType?|
         (STRING-EQL? |name| (%SYMBOL-NAME |slotType|)))
        (CL:AND |useParametricType?|
         (STRING-EQL? |name| (%SYMBOL-NAME |slotParametricType|)))
        (STRING-EQL? |name| (%SYMBOL-NAME (%SLOT-NAME |slot|))))
       (CL:SETQ |result| |slot|) (CL:RETURN)))
     (CL:SETQ ITER-000 (%%REST ITER-000))))
   |result|))

;;; (DEFUN (GET-ELEMENT-NAME-FROM-EXPR STRING-WRAPPER) ...)

(CL:DEFUN GET-ELEMENT-NAME-FROM-EXPR (|expression|)
  (WRAP-STRING (%NAME (%%VALUE |expression|))))

;;; (DEFUN (GET-ELEMENT-NAMESPACE-PREFIX-FROM-EXPR STRING-WRAPPER) ...)

(CL:DEFUN GET-ELEMENT-NAMESPACE-PREFIX-FROM-EXPR (|expression|)
  (CL:LET*
   ((|lookupResult|
     (LOOKUP *NAMESPACE-URI-PREFIX-TABLE*
      (GET-ELEMENT-NAMESPACE-URI-FROM-EXPR |expression|))))
   (CL:IF (CL:NOT (CL:EQ |lookupResult| NULL)) |lookupResult|
    NULL-STRING-WRAPPER)))

;;; (DEFUN (GET-ELEMENT-NAMESPACE-URI-FROM-EXPR STRING-WRAPPER) ...)

(CL:DEFUN GET-ELEMENT-NAMESPACE-URI-FROM-EXPR (|expression|)
  (WRAP-STRING (%NAMESPACE-URI (%%VALUE |expression|))))

;;; (DEFUN (GET-ELEMENT-NAME-FROM-OBJECT STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T) CL:SIMPLE-STRING)
  GET-ELEMENT-NAME-FROM-OBJECT))
(CL:DEFUN GET-ELEMENT-NAME-FROM-OBJECT (|object|)
  (CL:LET* ((|className| (%SYMBOL-NAME (PRIMARY-TYPE |object|))))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |className|)) |className|))

;;; (DEFUN (STRINGIFY-XML STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T) CL:SIMPLE-STRING) STRINGIFY-XML))
(CL:DEFUN STRINGIFY-XML (|expression|)
  (CL:LET* ((|ss| (NEW-OUTPUT-STRING-STREAM)))
   (PRINT-XML-EXPRESSION |ss| |expression| 0) (THE-STRING-READER |ss|)))

;;; (DEFSPECIAL *DEFAULT-XML-OBJECT-MODULE* ...)

(CL:DEFVAR *DEFAULT-XML-OBJECT-MODULE* NULL
  "Default module for the creation of XMLObject instances when converting
from XML to the object representation.  Used unless there is a more
specific namespace-mapping defined.")

;;; (DEFUN (LOOKUP-OBJECT-CREATION-MODULE MODULE) ...)

(CL:DEFUN LOOKUP-OBJECT-CREATION-MODULE (|namespacePrefix|)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |namespacePrefix|))
  #+MCL
  (CL:CHECK-TYPE |namespacePrefix| CL:SIMPLE-STRING)
  (CL:LET* ((|creationModule| NULL))
   (CL:WHEN
    (CL:AND (CL:NOT (CL:EQ |namespacePrefix| STELLA::NULL-STRING))
     (CL:NOT (STRING-EQL? |namespacePrefix| "")))
    (CL:SETQ |creationModule|
     (GET-STELLA-CONTEXT |namespacePrefix| CL:NIL)))
   (CL:WHEN (CL:EQ |creationModule| NULL)
    (CL:IF (CL:NOT (CL:EQ *DEFAULT-XML-OBJECT-MODULE* NULL))
     (CL:SETQ |creationModule| *DEFAULT-XML-OBJECT-MODULE*)
     (CL:SETQ |creationModule| *MODULE*)))
   |creationModule|))

;;; (DEFUN (MAKE-XML-OBJECT OBJECT) ...)

(CL:DEFUN MAKE-XML-OBJECT (|className| |namespacePrefix| |namespaceURI|)
  (CL:DECLARE
   (CL:TYPE CL:SIMPLE-STRING |className| |namespacePrefix|
    |namespaceURI|))
  #+MCL
  (CL:CHECK-TYPE |className| CL:SIMPLE-STRING)
  #+MCL
  (CL:CHECK-TYPE |namespacePrefix| CL:SIMPLE-STRING)
  #+MCL
  (CL:CHECK-TYPE |namespaceURI| CL:SIMPLE-STRING)
  (CL:SETQ |namespaceURI| |namespaceURI|)
  (CL:LET*
   ((|theType|
     (LOOKUP-SURROGATE-IN-MODULE |className|
      (LOOKUP-OBJECT-CREATION-MODULE |namespacePrefix|) CL:T)))
   (CL:WHEN (CL:EQ |theType| NULL)
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
      "Couldn't find a class for `" |className| "' in target module `"
      (LOOKUP-OBJECT-CREATION-MODULE |namespacePrefix|) "'")
     (CL:ERROR
      (NEW-NO-SUCH-OBJECT-EXCEPTION (THE-STRING-READER STREAM-000)))))
   (CL:LET*
    ((|theClass| (%SURROGATE-VALUE |theType|))
     (|theConstructor| (%CLASS-CONSTRUCTOR-CODE |theClass|)))
    (APPLY |theConstructor| NIL))))

;;; (DEFUN (ATTRIBUTE-SLOT? BOOLEAN) ...)

(CL:DEFUN ATTRIBUTE-SLOT? (|slot|)
  (CL:LET*
   ((|stringType| SGT-MARSHALLER-STELLA-STRING)
    (|slotType| (TYPE |slot|)))
   (CL:AND
    (CL:NOT
     (CL:EQ (%SLOT-NAME |slot|)
      |SYM-MARSHALLER-XML-OBJECTS-textContent|))
    (SUBTYPE-OF? |slotType| |stringType|))))

;;; (DEFUN (ELEMENT-SLOT? BOOLEAN) ...)

(CL:DEFUN ELEMENT-SLOT? (|slot|)
  (CL:LET*
   ((|rootXMLType| |SGT-MARSHALLER-XML-OBJECTS-XMLObject|)
    (|slotType| (TYPE |slot|)))
   (SUBTYPE-OF? |slotType| |rootXMLType|)))

;;; (DEFUN (COLLECTION-SLOT? BOOLEAN) ...)

(CL:DEFUN COLLECTION-SLOT? (|slot|)
  (CL:LET*
   ((|listType| SGT-MARSHALLER-STELLA-LIST) (|slotType| (TYPE |slot|)))
   (SUBTYPE-OF? |slotType| |listType|)))

;;; (DEFUN (GET-OBJECT-SLOT-VALUE OBJECT) ...)

(CL:DEFUN GET-OBJECT-SLOT-VALUE (|object| |slot|)
  (ENCODE-SLOT-VALUE |slot| (READ-SLOT-VALUE |object| |slot|)))

;;; (DEFUN SET-OBJECT-SLOT-VALUE ...)

(CL:DEFUN SET-OBJECT-SLOT-VALUE (|object| |slot| |value|)
  (WRITE-SLOT-VALUE |object| |slot| (DECODE-SLOT-VALUE |slot| |value|)))

;;; (DEFUN SET-COLLECTION-SLOT-VALUE ...)

(CL:DEFUN SET-COLLECTION-SLOT-VALUE (|object| |slot| |value|)
  (CL:LET* ((|valueList| (GET-OBJECT-SLOT-VALUE |object| |slot|)))
   (CL:WHEN (CL:EQ |valueList| NULL) (CL:SETQ |valueList| (NEW-LIST))
    (SET-OBJECT-SLOT-VALUE |object| |slot| |valueList|))
   (INSERT-LAST |valueList| |value|)))

;;; (DEFUN (DECODE-SLOT-VALUE OBJECT) ...)

(CL:DEFUN DECODE-SLOT-VALUE (|slot| |value|)
  (CL:LET*
   ((|encoding|
     (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS |slot|)
      SYM-MARSHALLER-XML-OBJECTS-ENCODING-SCHEME NULL)))
   (CL:WHEN (CL:NOT (CL:EQ |encoding| NULL))
    (CL:COND
     ((CL:EQ |encoding| KWD-MARSHALLER-BASE64)
      (CL:IF (STRING? |value|)
       (CL:SETQ |value|
        (WRAP-STRING (BASE64-DECODE-STRING (%WRAPPER-VALUE |value|))))
       (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
        (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
         "Don't know how to base64-decode this object: `" |value| "'")
        (CL:ERROR
         (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
     ((CL:EQ |encoding| KWD-MARSHALLER-PLAIN))
     (CL:T
      (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
       (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001)
        "Unknown encoding scheme: `" |encoding| "'")
       (CL:ERROR
        (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-001)))))))
   |value|))

;;; (DEFUN (ENCODE-SLOT-VALUE OBJECT) ...)

(CL:DEFUN ENCODE-SLOT-VALUE (|slot| |value|)
  (CL:LET*
   ((|encoding|
     (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS |slot|)
      SYM-MARSHALLER-XML-OBJECTS-ENCODING-SCHEME NULL)))
   (CL:WHEN (CL:NOT (CL:EQ |encoding| NULL))
    (CL:COND
     ((CL:EQ |encoding| KWD-MARSHALLER-BASE64)
      (CL:IF (STRING? |value|)
       (CL:SETQ |value|
        (WRAP-STRING (BASE64-ENCODE-STRING (%WRAPPER-VALUE |value|))))
       (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
        (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
         "Don't know how to base64-encode this object: `" |value| "'")
        (CL:ERROR
         (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
     ((CL:EQ |encoding| KWD-MARSHALLER-PLAIN))
     (CL:T
      (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
       (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001)
        "unknown encoding scheme: `" |encoding| "'")
       (CL:ERROR
        (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-001)))))))
   |value|))

;;; (DEFGLOBAL *BASE64-ENCODING-TABLE* ...)

(CL:DEFVAR *BASE64-ENCODING-TABLE* "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/")
(CL:DECLAIM (CL:TYPE CL:SIMPLE-STRING *BASE64-ENCODING-TABLE*))

;;; (DEFGLOBAL *BASE64-DECODING-TABLE* ...)

(CL:DEFVAR *BASE64-DECODING-TABLE* STELLA::NULL-1D-ARRAY)
(CL:DECLAIM (CL:TYPE CL:SIMPLE-VECTOR *BASE64-DECODING-TABLE*))

;;; (DEFUN (INITIALIZE-BASE64-DECODING-TABLE (ARRAY () OF INTEGER)) ...)

(CL:DEFUN INITIALIZE-BASE64-DECODING-TABLE ()
  (CL:LET* ((|buffer| (CL:MAKE-ARRAY 256)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-VECTOR |buffer|))
   (CL:LET* ((|i| NULL-INTEGER) (ITER-000 0) (UPPER-BOUND-000 255))
    (CL:DECLARE (CL:TYPE CL:FIXNUM |i| ITER-000 UPPER-BOUND-000))
    (CL:LOOP WHILE (CL:<= ITER-000 UPPER-BOUND-000) DO
     (CL:SETQ |i| ITER-000) (CL:SETF (CL:AREF |buffer| |i|) -1)
     (CL:SETQ ITER-000 (CL:1+ ITER-000))))
   (CL:LET*
    ((|ch| NULL-CHARACTER) (VECTOR-000 *BASE64-ENCODING-TABLE*)
     (INDEX-000 0)
     (LENGTH-000 (CL:THE CL:FIXNUM (CL:LENGTH VECTOR-000)))
     (|code| NULL-INTEGER) (ITER-001 0) (UPPER-BOUND-001 63))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING VECTOR-000)
     (CL:TYPE CL:FIXNUM INDEX-000 LENGTH-000 |code| ITER-001
      UPPER-BOUND-001))
    (CL:LOOP WHILE
     (CL:AND (CL:< INDEX-000 LENGTH-000)
      (CL:<= ITER-001 UPPER-BOUND-001))
     DO
     (CL:SETQ |ch|
      (CL:LET ((SELF VECTOR-000) (POSITION INDEX-000))
       (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
        (CL:TYPE CL:FIXNUM POSITION))
       (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
        (CL:THE CL:FIXNUM POSITION))))
     (CL:SETQ |code| ITER-001)
     (CL:SETF (CL:AREF |buffer| (CL:THE CL:FIXNUM (CL:CHAR-CODE |ch|)))
      |code|)
     (CL:SETQ INDEX-000 (CL:1+ INDEX-000))
     (CL:SETQ ITER-001 (CL:1+ ITER-001))))
   |buffer|))

;;; (DEFUN (BASE64-ENCODE-STRING STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:SIMPLE-STRING) CL:SIMPLE-STRING)
  BASE64-ENCODE-STRING))
(CL:DEFUN BASE64-ENCODE-STRING (|input|)
  "Base-64 encode `input' and return the result."
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |input|))
  #+MCL
  (CL:CHECK-TYPE |input| CL:SIMPLE-STRING)
  (CL:LET*
   ((|inputLength| (CL:THE CL:FIXNUM (CL:LENGTH |input|)))
    (|codeLength| (CL:* (CEILING (CL:/ |inputLength| 3.0d0)) 4))
    (|nofLines| (CEILING (CL:/ |codeLength| 76.0d0)))
    (|outputLength| (CL:+ |codeLength| (CL:* |nofLines| 2)))
    (|output| (MAKE-RAW-MUTABLE-STRING |outputLength|))
    (|encodingTable| *BASE64-ENCODING-TABLE*) (|triple| 0)
    (|inputCursor| 0) (|outputCursor| 0) (|eolPosition| 76)
    (|nofPads| 0))
   (CL:DECLARE
    (CL:TYPE CL:FIXNUM |inputLength| |codeLength| |nofLines|
     |outputLength| |triple| |inputCursor| |outputCursor| |eolPosition|
     |nofPads|)
    (CL:TYPE CL:SIMPLE-STRING |output| |encodingTable|))
   (CL:LOOP (CL:WHEN (CL:= |inputCursor| |inputLength|) (CL:RETURN))
    (CL:SETQ |triple|
     (CL:THE CL:FIXNUM
      (CL:CHAR-CODE
       (CL:LET ((SELF |input|) (POSITION |inputCursor|))
        (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
         (CL:TYPE CL:FIXNUM POSITION))
        (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
         (CL:THE CL:FIXNUM POSITION))))))
    (CL:SETQ |inputCursor| (CL:1+ |inputCursor|))
    (CL:COND
     ((CL:= |inputCursor| |inputLength|)
      (CL:SETQ |triple| (CL:THE CL:FIXNUM (CL:ASH |triple| 16))))
     (CL:T
      (CL:SETQ |triple|
       (CL:THE CL:FIXNUM
        (CL:LOGIOR (CL:THE CL:FIXNUM (CL:ASH |triple| 8))
         (CL:THE CL:FIXNUM
          (CL:CHAR-CODE
           (CL:LET ((SELF |input|) (POSITION |inputCursor|))
            (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
             (CL:TYPE CL:FIXNUM POSITION))
            (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
             (CL:THE CL:FIXNUM POSITION))))))))
      (CL:SETQ |inputCursor| (CL:1+ |inputCursor|))
      (CL:COND
       ((CL:= |inputCursor| |inputLength|)
        (CL:SETQ |triple| (CL:THE CL:FIXNUM (CL:ASH |triple| 8))))
       (CL:T
        (CL:SETQ |triple|
         (CL:THE CL:FIXNUM
          (CL:LOGIOR (CL:THE CL:FIXNUM (CL:ASH |triple| 8))
           (CL:THE CL:FIXNUM
            (CL:CHAR-CODE
             (CL:LET ((SELF |input|) (POSITION |inputCursor|))
              (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
               (CL:TYPE CL:FIXNUM POSITION))
              (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
               (CL:THE CL:FIXNUM POSITION))))))))
        (CL:SETQ |inputCursor| (CL:1+ |inputCursor|))))))
    (CL:LET
     ((SELF |output|)
      (CH
       (CL:LET
        ((SELF |encodingTable|)
         (POSITION
          (CL:LET ((ARG |triple|) (COUNT 18))
           (CL:DECLARE (CL:TYPE CL:FIXNUM ARG COUNT))
           (CL:THE CL:FIXNUM
            (CL:ASH ARG (CL:THE CL:FIXNUM (CL:- COUNT)))))))
        (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
         (CL:TYPE CL:FIXNUM POSITION))
        (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
         (CL:THE CL:FIXNUM POSITION))))
      (POSITION |outputCursor|))
     (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
      (CL:TYPE CL:FIXNUM POSITION))
     (SETF
      (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
       (CL:THE CL:FIXNUM POSITION))
      (CL:THE CL:CHARACTER CH)))
    (CL:SETQ |outputCursor| (CL:1+ |outputCursor|))
    (CL:LET
     ((SELF |output|)
      (CH
       (CL:LET
        ((SELF |encodingTable|)
         (POSITION
          (CL:THE CL:FIXNUM
           (CL:LOGAND
            (CL:THE CL:FIXNUM
             (CL:LET ((ARG |triple|) (COUNT 12))
              (CL:DECLARE (CL:TYPE CL:FIXNUM ARG COUNT))
              (CL:THE CL:FIXNUM
               (CL:ASH ARG (CL:THE CL:FIXNUM (CL:- COUNT))))))
            63))))
        (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
         (CL:TYPE CL:FIXNUM POSITION))
        (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
         (CL:THE CL:FIXNUM POSITION))))
      (POSITION |outputCursor|))
     (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
      (CL:TYPE CL:FIXNUM POSITION))
     (SETF
      (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
       (CL:THE CL:FIXNUM POSITION))
      (CL:THE CL:CHARACTER CH)))
    (CL:SETQ |outputCursor| (CL:1+ |outputCursor|))
    (CL:LET
     ((SELF |output|)
      (CH
       (CL:LET
        ((SELF |encodingTable|)
         (POSITION
          (CL:THE CL:FIXNUM
           (CL:LOGAND
            (CL:THE CL:FIXNUM
             (CL:LET ((ARG |triple|) (COUNT 6))
              (CL:DECLARE (CL:TYPE CL:FIXNUM ARG COUNT))
              (CL:THE CL:FIXNUM
               (CL:ASH ARG (CL:THE CL:FIXNUM (CL:- COUNT))))))
            63))))
        (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
         (CL:TYPE CL:FIXNUM POSITION))
        (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
         (CL:THE CL:FIXNUM POSITION))))
      (POSITION |outputCursor|))
     (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
      (CL:TYPE CL:FIXNUM POSITION))
     (SETF
      (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
       (CL:THE CL:FIXNUM POSITION))
      (CL:THE CL:CHARACTER CH)))
    (CL:SETQ |outputCursor| (CL:1+ |outputCursor|))
    (CL:LET
     ((SELF |output|)
      (CH
       (CL:LET
        ((SELF |encodingTable|)
         (POSITION (CL:THE CL:FIXNUM (CL:LOGAND |triple| 63))))
        (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
         (CL:TYPE CL:FIXNUM POSITION))
        (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
         (CL:THE CL:FIXNUM POSITION))))
      (POSITION |outputCursor|))
     (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
      (CL:TYPE CL:FIXNUM POSITION))
     (SETF
      (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
       (CL:THE CL:FIXNUM POSITION))
      (CL:THE CL:CHARACTER CH)))
    (CL:SETQ |outputCursor| (CL:1+ |outputCursor|))
    (CL:WHEN (CL:= |outputCursor| |eolPosition|)
     (CL:SETQ |eolPosition| (CL:+ |eolPosition| 78))
     (CL:LET ((SELF |output|) (CH #\Return) (POSITION |outputCursor|))
      (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
       (CL:TYPE CL:FIXNUM POSITION))
      (SETF
       (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
        (CL:THE CL:FIXNUM POSITION))
       (CL:THE CL:CHARACTER CH)))
     (CL:SETQ |outputCursor| (CL:1+ |outputCursor|))
     (CL:LET
      ((SELF |output|) (CH #\Linefeed) (POSITION |outputCursor|))
      (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
       (CL:TYPE CL:FIXNUM POSITION))
      (SETF
       (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
        (CL:THE CL:FIXNUM POSITION))
       (CL:THE CL:CHARACTER CH)))
     (CL:SETQ |outputCursor| (CL:1+ |outputCursor|))))
   (CL:ECASE (CL:THE CL:FIXNUM (CL:REM |inputLength| 3))
    (0 (CL:SETQ |nofPads| 0)) (1 (CL:SETQ |nofPads| 2))
    (2 (CL:SETQ |nofPads| 1)))
   (CL:LET*
    ((|i| NULL-INTEGER) (ITER-000 1) (UPPER-BOUND-000 |nofPads|)
     (UNBOUNDED?-000 (CL:= UPPER-BOUND-000 NULL-INTEGER)))
    (CL:DECLARE (CL:TYPE CL:FIXNUM |i| ITER-000 UPPER-BOUND-000))
    (CL:LOOP WHILE
     (CL:OR UNBOUNDED?-000 (CL:<= ITER-000 UPPER-BOUND-000)) DO
     (CL:SETQ |i| ITER-000)
     (CL:LET
      ((SELF |output|) (CH #\=) (POSITION (CL:- |outputLength| |i| 2)))
      (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
       (CL:TYPE CL:FIXNUM POSITION))
      (SETF
       (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
        (CL:THE CL:FIXNUM POSITION))
       (CL:THE CL:CHARACTER CH)))
     (CL:SETQ ITER-000 (CL:1+ ITER-000))))
   (CL:WHEN (CL:>= |outputLength| 2)
    (CL:LET
     ((SELF |output|) (CH #\Return) (POSITION (CL:- |outputLength| 2)))
     (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
      (CL:TYPE CL:FIXNUM POSITION))
     (SETF
      (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
       (CL:THE CL:FIXNUM POSITION))
      (CL:THE CL:CHARACTER CH)))
    (CL:LET
     ((SELF |output|) (CH #\Linefeed)
      (POSITION (CL:1- |outputLength|)))
     (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
      (CL:TYPE CL:FIXNUM POSITION))
     (SETF
      (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
       (CL:THE CL:FIXNUM POSITION))
      (CL:THE CL:CHARACTER CH))))
   (CL:LET ((S |output|)) (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING S))
    (CL:THE CL:SIMPLE-STRING S))))

;;; (DEFUN (BASE64-DECODE-STRING STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:SIMPLE-STRING) CL:SIMPLE-STRING)
  BASE64-DECODE-STRING))
(CL:DEFUN BASE64-DECODE-STRING (|input|)
  "Base-64 decode `input' and return the result."
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |input|))
  #+MCL
  (CL:CHECK-TYPE |input| CL:SIMPLE-STRING)
  (CL:LET*
   ((|inputLength| (CL:THE CL:FIXNUM (CL:LENGTH |input|)))
    (|outputLength|
     (CL:*
      (CL:LET ((X |inputLength|) (Y 4))
       (CL:DECLARE (CL:TYPE CL:FIXNUM X Y))
       (CL:THE CL:FIXNUM (CL:VALUES (CL:TRUNCATE X Y))))
      3))
    (|output| (MAKE-RAW-MUTABLE-STRING |outputLength|))
    (|decodingTable| *BASE64-DECODING-TABLE*) (|code| 0) (|triple| 0)
    (|nofPads| 0) (|inputCursor| 0) (|outputCursor| 0))
   (CL:DECLARE
    (CL:TYPE CL:FIXNUM |inputLength| |outputLength| |code| |triple|
     |nofPads| |inputCursor| |outputCursor|)
    (CL:TYPE CL:SIMPLE-STRING |output|)
    (CL:TYPE CL:SIMPLE-VECTOR |decodingTable|))
   (CL:LOOP
    (CL:LOOP (CL:WHEN (CL:= |inputCursor| |inputLength|) (CL:RETURN))
     (CL:SETQ |code|
      (CL:AREF |decodingTable|
       (CL:THE CL:FIXNUM
        (CL:CHAR-CODE
         (CL:LET ((SELF |input|) (POSITION |inputCursor|))
          (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
           (CL:TYPE CL:FIXNUM POSITION))
          (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
           (CL:THE CL:FIXNUM POSITION)))))))
     (CL:SETQ |inputCursor| (CL:1+ |inputCursor|))
     (CL:WHEN (CL:NOT (CL:= |code| -1)) (CL:RETURN)))
    (CL:WHEN (CL:= |inputCursor| |inputLength|) (CL:RETURN))
    (CL:SETQ |triple| |code|)
    (CL:SETQ |triple|
     (CL:THE CL:FIXNUM
      (CL:LOGIOR (CL:THE CL:FIXNUM (CL:ASH |triple| 6))
       (CL:THE CL:FIXNUM
        (CL:AREF |decodingTable|
         (CL:THE CL:FIXNUM
          (CL:CHAR-CODE
           (CL:LET ((SELF |input|) (POSITION |inputCursor|))
            (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
             (CL:TYPE CL:FIXNUM POSITION))
            (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
             (CL:THE CL:FIXNUM POSITION))))))))))
    (CL:SETQ |inputCursor| (CL:1+ |inputCursor|))
    (CL:SETQ |code|
     (CL:AREF |decodingTable|
      (CL:THE CL:FIXNUM
       (CL:CHAR-CODE
        (CL:LET ((SELF |input|) (POSITION |inputCursor|))
         (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
          (CL:TYPE CL:FIXNUM POSITION))
         (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
          (CL:THE CL:FIXNUM POSITION)))))))
    (CL:SETQ |inputCursor| (CL:1+ |inputCursor|))
    (CL:COND
     ((CL:= |code| -1) (CL:SETQ |nofPads| 2)
      (CL:SETQ |triple| (CL:THE CL:FIXNUM (CL:ASH |triple| 12))))
     (CL:T
      (CL:SETQ |triple|
       (CL:THE CL:FIXNUM
        (CL:LOGIOR (CL:THE CL:FIXNUM (CL:ASH |triple| 6)) |code|)))
      (CL:SETQ |code|
       (CL:AREF |decodingTable|
        (CL:THE CL:FIXNUM
         (CL:CHAR-CODE
          (CL:LET ((SELF |input|) (POSITION |inputCursor|))
           (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
            (CL:TYPE CL:FIXNUM POSITION))
           (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
            (CL:THE CL:FIXNUM POSITION)))))))
      (CL:SETQ |inputCursor| (CL:1+ |inputCursor|))
      (CL:COND
       ((CL:= |code| -1) (CL:SETQ |nofPads| 1)
        (CL:SETQ |triple| (CL:THE CL:FIXNUM (CL:ASH |triple| 6))))
       (CL:T
        (CL:SETQ |triple|
         (CL:THE CL:FIXNUM
          (CL:LOGIOR (CL:THE CL:FIXNUM (CL:ASH |triple| 6))
           |code|)))))))
    (CL:COND
     ((CL:= |nofPads| 0)
      (CL:LET
       ((SELF |output|)
        (CH
         (CL:CODE-CHAR
          (CL:THE CL:FIXNUM
           (CL:LET ((ARG |triple|) (COUNT 16))
            (CL:DECLARE (CL:TYPE CL:FIXNUM ARG COUNT))
            (CL:THE CL:FIXNUM
             (CL:ASH ARG (CL:THE CL:FIXNUM (CL:- COUNT))))))))
        (POSITION |outputCursor|))
       (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
        (CL:TYPE CL:FIXNUM POSITION))
       (SETF
        (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
         (CL:THE CL:FIXNUM POSITION))
        (CL:THE CL:CHARACTER CH)))
      (CL:SETQ |outputCursor| (CL:1+ |outputCursor|))
      (CL:LET
       ((SELF |output|)
        (CH
         (CL:CODE-CHAR
          (CL:THE CL:FIXNUM
           (CL:LOGAND
            (CL:THE CL:FIXNUM
             (CL:LET ((ARG |triple|) (COUNT 8))
              (CL:DECLARE (CL:TYPE CL:FIXNUM ARG COUNT))
              (CL:THE CL:FIXNUM
               (CL:ASH ARG (CL:THE CL:FIXNUM (CL:- COUNT))))))
            255))))
        (POSITION |outputCursor|))
       (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
        (CL:TYPE CL:FIXNUM POSITION))
       (SETF
        (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
         (CL:THE CL:FIXNUM POSITION))
        (CL:THE CL:CHARACTER CH)))
      (CL:SETQ |outputCursor| (CL:1+ |outputCursor|))
      (CL:LET
       ((SELF |output|)
        (CH (CL:CODE-CHAR (CL:THE CL:FIXNUM (CL:LOGAND |triple| 255))))
        (POSITION |outputCursor|))
       (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
        (CL:TYPE CL:FIXNUM POSITION))
       (SETF
        (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
         (CL:THE CL:FIXNUM POSITION))
        (CL:THE CL:CHARACTER CH)))
      (CL:SETQ |outputCursor| (CL:1+ |outputCursor|)))
     (CL:T
      (CL:LET
       ((SELF |output|)
        (CH
         (CL:CODE-CHAR
          (CL:THE CL:FIXNUM
           (CL:LET ((ARG |triple|) (COUNT 16))
            (CL:DECLARE (CL:TYPE CL:FIXNUM ARG COUNT))
            (CL:THE CL:FIXNUM
             (CL:ASH ARG (CL:THE CL:FIXNUM (CL:- COUNT))))))))
        (POSITION |outputCursor|))
       (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
        (CL:TYPE CL:FIXNUM POSITION))
       (SETF
        (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
         (CL:THE CL:FIXNUM POSITION))
        (CL:THE CL:CHARACTER CH)))
      (CL:SETQ |outputCursor| (CL:1+ |outputCursor|))
      (CL:WHEN (CL:= |nofPads| 1)
       (CL:LET
        ((SELF |output|)
         (CH
          (CL:CODE-CHAR
           (CL:THE CL:FIXNUM
            (CL:LOGAND
             (CL:THE CL:FIXNUM
              (CL:LET ((ARG |triple|) (COUNT 8))
               (CL:DECLARE (CL:TYPE CL:FIXNUM ARG COUNT))
               (CL:THE CL:FIXNUM
                (CL:ASH ARG (CL:THE CL:FIXNUM (CL:- COUNT))))))
             255))))
         (POSITION |outputCursor|))
        (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
         (CL:TYPE CL:FIXNUM POSITION))
        (SETF
         (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
          (CL:THE CL:FIXNUM POSITION))
         (CL:THE CL:CHARACTER CH)))
       (CL:SETQ |outputCursor| (CL:1+ |outputCursor|))))))
   (CL:IF (CL:< |outputCursor| |outputLength|)
    (SUBSEQUENCE |output| 0 |outputCursor|)
    (CL:LET ((S |output|)) (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING S))
     (CL:THE CL:SIMPLE-STRING S)))))

;;; (DEFUN (READ-XML OBJECT) ...)

(CL:DEFUN READ-XML (|xmlString|)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING |xmlString|))
  #+MCL
  (CL:CHECK-TYPE |xmlString| CL:SIMPLE-STRING)
  (CL:LET* ((|inputStream| (NEW-INPUT-STRING-STREAM |xmlString|)))
   (READ-XML-EXPRESSION |inputStream| NULL)))

;;; (DEFCLASS A ...)

(CL:DEFCLASS A (|XMLObject|)
  ((|b| :ALLOCATION :INSTANCE :ACCESSOR |%b|)
   (|c| :ALLOCATION :INSTANCE :ACCESSOR |%c|)))

(CL:DEFUN NEW-A ()
  (CL:LET* ((SELF NULL)) (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE A)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%c| SELF) NULL) (CL:SETF (|%b| SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF A))
  SGT-MARSHALLER-XML-OBJECTS-A)

(CL:DEFUN ACCESS-A-SLOT-VALUE (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-MARSHALLER-XML-OBJECTS-b|)
    (CL:IF SETVALUE? (CL:SETF (|%b| SELF) VALUE)
     (CL:SETQ VALUE (|%b| SELF))))
   ((CL:EQ SLOTNAME |SYM-MARSHALLER-XML-OBJECTS-c|)
    (CL:IF SETVALUE? (CL:SETF (|%c| SELF) VALUE)
     (CL:SETQ VALUE (|%c| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS B ...)

(CL:DEFCLASS B (|XMLObject|)
  ((|d| :ALLOCATION :INSTANCE :ACCESSOR |%d|)))

(CL:DEFUN NEW-B ()
  (CL:LET* ((SELF NULL)) (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE B)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%d| SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF B))
  SGT-MARSHALLER-XML-OBJECTS-B)

(CL:DEFUN ACCESS-B-SLOT-VALUE (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-MARSHALLER-XML-OBJECTS-d|)
    (CL:IF SETVALUE? (CL:SETF (|%d| SELF) VALUE)
     (CL:SETQ VALUE (|%d| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS C ...)

(CL:DEFCLASS C (|XMLObject|)
  ((|d| :ALLOCATION :INSTANCE :ACCESSOR |%d|)
   (|e| :ALLOCATION :INSTANCE :ACCESSOR |%e|)))

(CL:DEFUN NEW-C ()
  (CL:LET* ((SELF NULL)) (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE C)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%e| SELF) NULL) (CL:SETF (|%d| SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF C))
  SGT-MARSHALLER-XML-OBJECTS-C)

(CL:DEFUN ACCESS-C-SLOT-VALUE (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-MARSHALLER-XML-OBJECTS-d|)
    (CL:IF SETVALUE? (CL:SETF (|%d| SELF) VALUE)
     (CL:SETQ VALUE (|%d| SELF))))
   ((CL:EQ SLOTNAME |SYM-MARSHALLER-XML-OBJECTS-e|)
    (CL:IF SETVALUE? (CL:SETF (|%e| SELF) VALUE)
     (CL:SETQ VALUE (|%e| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS D ...)

(CL:DEFCLASS D (|XMLObject|)
  ((|f| :ALLOCATION :INSTANCE :ACCESSOR |%f|)))

(CL:DEFUN NEW-D ()
  (CL:LET* ((SELF NULL)) (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE D)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%f| SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF D))
  SGT-MARSHALLER-XML-OBJECTS-D)

(CL:DEFUN ACCESS-D-SLOT-VALUE (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-MARSHALLER-XML-OBJECTS-f|)
    (CL:IF SETVALUE? (CL:SETF (|%f| SELF) VALUE)
     (CL:SETQ VALUE (|%f| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS E ...)

(CL:DEFCLASS E (|XMLObject|)
  ((|f| :ALLOCATION :INSTANCE :ACCESSOR |%f|)))

(CL:DEFUN NEW-E ()
  (CL:LET* ((SELF NULL)) (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE E)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%f| SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF E))
  SGT-MARSHALLER-XML-OBJECTS-E)

(CL:DEFUN ACCESS-E-SLOT-VALUE (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME |SYM-MARSHALLER-XML-OBJECTS-f|)
    (CL:IF SETVALUE? (CL:SETF (|%f| SELF) VALUE)
     (CL:SETQ VALUE (|%f| SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS F ...)

(CL:DEFCLASS F (|XMLObject|)
  ())

(CL:DEFUN NEW-F ()
  (CL:LET* ((SELF NULL)) (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE F)))
   (CL:SETF (|%cdataContent| SELF) STELLA::NULL-STRING)
   (CL:SETF (|%textContent| SELF) STELLA::NULL-STRING) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF F))
  SGT-MARSHALLER-XML-OBJECTS-F)

;;; (DEFUN MULTIREF-TEST1 ...)

(CL:DEFUN MULTIREF-TEST1 ()
  (CL:LET* ((|f| (NEW-F)))
   (CL:LET* ((SELF-001 (NEW-E))) (CL:SETF (|%f| SELF-001) |f|)
    (CL:LET* ((|e| SELF-001))
     (CL:LET* ((SELF-002 (NEW-D))) (CL:SETF (|%f| SELF-002) |f|)
      (CL:LET* ((|d| SELF-002))
       (CL:LET* ((SELF-003 (NEW-C))) (CL:SETF (|%d| SELF-003) |d|)
        (CL:SETF (|%e| SELF-003) |e|)
        (CL:LET* ((|c| SELF-003))
         (CL:LET* ((SELF-004 (NEW-B))) (CL:SETF (|%d| SELF-004) |d|)
          (CL:LET* ((|b| SELF-004))
           (CL:LET* ((SELF-005 (NEW-A))) (CL:SETF (|%b| SELF-005) |b|)
            (CL:SETF (|%c| SELF-005) |c|)
            (CL:LET* ((|a| SELF-005)) (RESET-MULTIREF-TABLES)
             (POPULATE-NODE-PARENTS-TABLE |a|)
             (CREATE-NODE-ID-PARENT-TABLE)
             (SIMULATE-MULTIREF-OUTPUT |a|)))))))))))))

(CL:DEFUN HELP-STARTUP-MARSHALLER1 ()
  (CL:PROGN
   (CL:SETQ SGT-MARSHALLER-STELLA-CONS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONS"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ |SGT-MARSHALLER-XML-OBJECTS-XMLObject|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "XMLObject" NULL 1))
   (CL:SETQ |SYM-MARSHALLER-XML-OBJECTS-textContent|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "textContent" NULL 0))
   (CL:SETQ SGT-MARSHALLER-XML-OBJECTS-ID-PARENT-STRUCT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ID-PARENT-STRUCT" NULL 1))
   (CL:SETQ |SYM-MARSHALLER-XML-OBJECTS-id|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "id" NULL 0))
   (CL:SETQ |SYM-MARSHALLER-XML-OBJECTS-parents|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "parents" NULL 0))
   (CL:SETQ SGT-MARSHALLER-STELLA-XML-ELEMENT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "XML-ELEMENT"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ SGT-MARSHALLER-STELLA-STRING
    (INTERN-RIGID-SYMBOL-WRT-MODULE "STRING"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ SGT-MARSHALLER-STELLA-LIST
    (INTERN-RIGID-SYMBOL-WRT-MODULE "LIST"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ SYM-MARSHALLER-XML-OBJECTS-ENCODING-SCHEME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ENCODING-SCHEME" NULL 0))
   (CL:SETQ KWD-MARSHALLER-BASE64
    (INTERN-RIGID-SYMBOL-WRT-MODULE "BASE64" NULL 2))
   (CL:SETQ KWD-MARSHALLER-PLAIN
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PLAIN" NULL 2))
   (CL:SETQ SGT-MARSHALLER-XML-OBJECTS-A
    (INTERN-RIGID-SYMBOL-WRT-MODULE "A" NULL 1))
   (CL:SETQ |SYM-MARSHALLER-XML-OBJECTS-b|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "b" NULL 0))
   (CL:SETQ |SYM-MARSHALLER-XML-OBJECTS-c|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "c" NULL 0))
   (CL:SETQ SGT-MARSHALLER-XML-OBJECTS-B
    (INTERN-RIGID-SYMBOL-WRT-MODULE "B" NULL 1))
   (CL:SETQ |SYM-MARSHALLER-XML-OBJECTS-d|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "d" NULL 0))
   (CL:SETQ SGT-MARSHALLER-XML-OBJECTS-C
    (INTERN-RIGID-SYMBOL-WRT-MODULE "C" NULL 1))
   (CL:SETQ |SYM-MARSHALLER-XML-OBJECTS-e|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "e" NULL 0))
   (CL:SETQ SGT-MARSHALLER-XML-OBJECTS-D
    (INTERN-RIGID-SYMBOL-WRT-MODULE "D" NULL 1))
   (CL:SETQ |SYM-MARSHALLER-XML-OBJECTS-f|
    (INTERN-RIGID-SYMBOL-WRT-MODULE "f" NULL 0))
   (CL:SETQ SGT-MARSHALLER-XML-OBJECTS-E
    (INTERN-RIGID-SYMBOL-WRT-MODULE "E" NULL 1))
   (CL:SETQ SGT-MARSHALLER-XML-OBJECTS-F
    (INTERN-RIGID-SYMBOL-WRT-MODULE "F" NULL 1))
   (CL:SETQ SYM-MARSHALLER-XML-OBJECTS-STARTUP-MARSHALLER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-MARSHALLER" NULL 0))
   (CL:SETQ SYM-MARSHALLER-STELLA-METHOD-STARTUP-CLASSNAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))))

(CL:DEFUN HELP-STARTUP-MARSHALLER2 ()
  (CL:PROGN
   (CL:LET*
    ((CLASS
      (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "ID-PARENT-STRUCT"
       "(DEFCLASS ID-PARENT-STRUCT (OBJECT) :PUBLIC-SLOTS ((id :TYPE INTEGER) (parents :TYPE (LIST OF XMLObject))))")))
    (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
     (CL:FUNCTION NEW-ID-PARENT-STRUCT))
    (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
     (CL:FUNCTION ACCESS-ID-PARENT-STRUCT-SLOT-VALUE)))
   (CL:LET*
    ((CLASS
      (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "A"
       "(DEFCLASS A (XMLObject) :PUBLIC-SLOTS ((b :TYPE B) (c :TYPE C)))")))
    (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS) (CL:FUNCTION NEW-A))
    (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
     (CL:FUNCTION ACCESS-A-SLOT-VALUE)))
   (CL:LET*
    ((CLASS
      (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "B"
       "(DEFCLASS B (XMLObject) :PUBLIC-SLOTS ((d :TYPE D)))")))
    (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS) (CL:FUNCTION NEW-B))
    (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
     (CL:FUNCTION ACCESS-B-SLOT-VALUE)))
   (CL:LET*
    ((CLASS
      (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "C"
       "(DEFCLASS C (XMLObject) :PUBLIC-SLOTS ((d :TYPE D) (e :TYPE E)))")))
    (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS) (CL:FUNCTION NEW-C))
    (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
     (CL:FUNCTION ACCESS-C-SLOT-VALUE)))
   (CL:LET*
    ((CLASS
      (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "D"
       "(DEFCLASS D (XMLObject) :PUBLIC-SLOTS ((f :TYPE F)))")))
    (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS) (CL:FUNCTION NEW-D))
    (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
     (CL:FUNCTION ACCESS-D-SLOT-VALUE)))
   (CL:LET*
    ((CLASS
      (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "E"
       "(DEFCLASS E (XMLObject) :PUBLIC-SLOTS ((f :TYPE F)))")))
    (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS) (CL:FUNCTION NEW-E))
    (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
     (CL:FUNCTION ACCESS-E-SLOT-VALUE)))
   (CL:LET*
    ((CLASS
      (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "F"
       "(DEFCLASS F (XMLObject))")))
    (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS) (CL:FUNCTION NEW-F)))))

(CL:DEFUN HELP-STARTUP-MARSHALLER3 ()
  (CL:PROGN
   (DEFINE-FUNCTION-OBJECT "SLOT-VALUE-IS-NULL?"
    "(DEFUN (SLOT-VALUE-IS-NULL? BOOLEAN) ((parentObject XMLObject) (slot SLOT)))"
    (CL:FUNCTION SLOT-VALUE-IS-NULL?) NULL)
   (DEFINE-FUNCTION-OBJECT "SLOT-VALUE-IS-NULL-OR-EMPTY?"
    "(DEFUN (SLOT-VALUE-IS-NULL-OR-EMPTY? BOOLEAN) ((parentObject XMLObject) (slot SLOT)))"
    (CL:FUNCTION SLOT-VALUE-IS-NULL-OR-EMPTY?) NULL)
   (DEFINE-METHOD-OBJECT
    "(DEFMETHOD (TO-XML-STRING STRING) ((object XMLObject)) :PUBLIC? TRUE :DOCUMENTATION \"Convert `object' into it's XML Representation as a string\")"
    (WRAP-METHOD-CODE (CL:FUNCTION TO-XML-STRING)) NULL)
   (DEFINE-METHOD-OBJECT
    "(DEFMETHOD TO-XML-STREAM ((object XMLObject) (out OUTPUT-STREAM)) :PUBLIC? TRUE :DOCUMENTATION \"Write `object' in  it's XML Representation to `out'.\")"
    (WRAP-METHOD-CODE (CL:FUNCTION TO-XML-STREAM)) NULL)
   (DEFINE-METHOD-OBJECT
    "(DEFMETHOD (TO-XML CONS) ((object XMLObject) (namespaceStack (CONS OF STRING-WRAPPER))))"
    (WRAP-METHOD-CODE (CL:FUNCTION TO-XML)) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-NAMESPACE-PREFIX"
    "(DEFUN (GET-NAMESPACE-PREFIX STRING) ((object XMLObject)))"
    (CL:FUNCTION GET-NAMESPACE-PREFIX) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-NAMESPACE-URI"
    "(DEFUN (GET-NAMESPACE-URI STRING-WRAPPER) ((namespacePrefix STRING)))"
    (CL:FUNCTION GET-NAMESPACE-URI) NULL)
   (DEFINE-FUNCTION-OBJECT "MAKE-CONTENT-EXPRESSION"
    "(DEFUN (MAKE-CONTENT-EXPRESSION CONS) ((object XMLObject)))"
    (CL:FUNCTION MAKE-CONTENT-EXPRESSION) NULL)
   (DEFINE-FUNCTION-OBJECT "MAKE-ELEMENT-TAG"
    "(DEFUN (MAKE-ELEMENT-TAG XML-ELEMENT) ((object XMLObject)))"
    (CL:FUNCTION MAKE-ELEMENT-TAG) NULL)
   (DEFINE-FUNCTION-OBJECT "MAKE-NAMESPACE-ATTRIBUTE"
    "(DEFUN (MAKE-NAMESPACE-ATTRIBUTE XML-ATTRIBUTE) ((namespaceName STRING)))"
    (CL:FUNCTION MAKE-NAMESPACE-ATTRIBUTE) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-ATTRIBUTE-VALUE-NAMESPACE-NAME"
    "(DEFUN (GET-ATTRIBUTE-VALUE-NAMESPACE-NAME STRING-WRAPPER) ((parentObject XMLObject) (slot STORAGE-SLOT)))"
    (CL:FUNCTION GET-ATTRIBUTE-VALUE-NAMESPACE-NAME) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-VALUE-NAMESPACE-PREFIX"
    "(DEFUN (GET-VALUE-NAMESPACE-PREFIX STRING) ((valueString STRING)))"
    (CL:FUNCTION GET-VALUE-NAMESPACE-PREFIX) NULL)
   (DEFINE-FUNCTION-OBJECT "MAKE-REVERSED-ATTRIBUTE"
    "(DEFUN (MAKE-REVERSED-ATTRIBUTE CONS) ((parentObject XMLObject) (slot STORAGE-SLOT)))"
    (CL:FUNCTION MAKE-REVERSED-ATTRIBUTE) NULL)
   (DEFINE-FUNCTION-OBJECT "MAKE-ELEMENT"
    "(DEFUN (MAKE-ELEMENT CONS) ((parentObject XMLObject) (slot SLOT) (namespaceStack CONS)))"
    (CL:FUNCTION MAKE-ELEMENT) NULL)
   (DEFINE-FUNCTION-OBJECT "MAKE-COLLECTION"
    "(DEFUN (MAKE-COLLECTION CONS) ((parentObject XMLObject) (slot SLOT) (namespaceStack CONS)))"
    (CL:FUNCTION MAKE-COLLECTION) NULL)
   (DEFINE-FUNCTION-OBJECT "FROM-XML-STRING"
    "(DEFUN (FROM-XML-STRING XMLObject) ((xmlString STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Convert XML into an object.\")"
    (CL:FUNCTION FROM-XML-STRING) NULL)
   (DEFINE-FUNCTION-OBJECT "FROM-XML-STREAM"
    "(DEFUN (FROM-XML-STREAM XMLObject) ((in INPUT-STREAM)) :PUBLIC? TRUE :DOCUMENTATION \"Convert XML into an object.\")"
    (CL:FUNCTION FROM-XML-STREAM) NULL)
   (DEFINE-FUNCTION-OBJECT "FROM-XML"
    "(DEFUN (FROM-XML XMLObject) ((expr CONS)))" (CL:FUNCTION FROM-XML)
    NULL)
   (DEFINE-FUNCTION-OBJECT "SET-ELEMENTS"
    "(DEFUN SET-ELEMENTS ((object XMLObject) (elementExprs CONS)))"
    (CL:FUNCTION SET-ELEMENTS) NULL)
   (DEFINE-FUNCTION-OBJECT "SET-ATTRIBUTES"
    "(DEFUN SET-ATTRIBUTES ((object XMLObject) (attributeExprs CONS)))"
    (CL:FUNCTION SET-ATTRIBUTES) NULL)
   (DEFINE-FUNCTION-OBJECT "SET-COLLECTIONS"
    "(DEFUN SET-COLLECTIONS ((object XMLObject) (elementExprs CONS)))"
    (CL:FUNCTION SET-COLLECTIONS) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-MAPPED-SLOTS"
    "(DEFUN (GET-MAPPED-SLOTS (LIST OF SLOT)) ((object XMLObject)))"
    (CL:FUNCTION GET-MAPPED-SLOTS) NULL)
   (DEFINE-FUNCTION-OBJECT "SLOT-REPRESENTS-TAG?"
    "(DEFUN (SLOT-REPRESENTS-TAG? BOOLEAN) ((slot SLOT) (tag XML-OBJECT) (useType? BOOLEAN) (useParametricType? BOOLEAN)))"
    (CL:FUNCTION SLOT-REPRESENTS-TAG?) NULL)
   (DEFINE-FUNCTION-OBJECT "LOOKUP-ELEMENT-SLOT"
    "(DEFUN (LOOKUP-ELEMENT-SLOT STORAGE-SLOT) ((object XMLObject) (elementExpr CONS)))"
    (CL:FUNCTION LOOKUP-ELEMENT-SLOT) NULL)
   (DEFINE-FUNCTION-OBJECT "LOOKUP-ATTRIBUTE-SLOT"
    "(DEFUN (LOOKUP-ATTRIBUTE-SLOT STORAGE-SLOT) ((object XMLObject) (attribute XML-ATTRIBUTE)))"
    (CL:FUNCTION LOOKUP-ATTRIBUTE-SLOT) NULL)
   (DEFINE-FUNCTION-OBJECT "LOOKUP-COLLECTION-SLOT"
    "(DEFUN (LOOKUP-COLLECTION-SLOT STORAGE-SLOT) ((object XMLObject) (elementExpr CONS)))"
    (CL:FUNCTION LOOKUP-COLLECTION-SLOT) NULL)
   (DEFINE-FUNCTION-OBJECT "LOOKUP-CONTENT-SLOT"
    "(DEFUN (LOOKUP-CONTENT-SLOT STORAGE-SLOT) ((object XMLObject)))"
    (CL:FUNCTION LOOKUP-CONTENT-SLOT) NULL)
   (DEFINE-FUNCTION-OBJECT "RESET-MULTIREF-TABLES"
    "(DEFUN RESET-MULTIREF-TABLES ())"
    (CL:FUNCTION RESET-MULTIREF-TABLES) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-NEXT-ID"
    "(DEFUN (GET-NEXT-ID INTEGER) ())" (CL:FUNCTION GET-NEXT-ID) NULL)
   (DEFINE-FUNCTION-OBJECT "INSERT-NODE-PARENTS-TABLE"
    "(DEFUN (INSERT-NODE-PARENTS-TABLE BOOLEAN) ((node XMLObject) (parent XMLObject)))"
    (CL:FUNCTION INSERT-NODE-PARENTS-TABLE) NULL)
   (DEFINE-FUNCTION-OBJECT "INSERT-NODE-ID-PARENTS-TABLE"
    "(DEFUN INSERT-NODE-ID-PARENTS-TABLE ((node XMLObject) (parent XMLObject)))"
    (CL:FUNCTION INSERT-NODE-ID-PARENTS-TABLE) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-CHILDREN"
    "(DEFUN (GET-CHILDREN (CONS OF XMLObject)) ((node XMLObject)))"
    (CL:FUNCTION GET-CHILDREN) NULL)
   (DEFINE-FUNCTION-OBJECT "POPULATE-NODE-PARENTS-TABLE"
    "(DEFUN POPULATE-NODE-PARENTS-TABLE ((node XMLObject)))"
    (CL:FUNCTION POPULATE-NODE-PARENTS-TABLE) NULL)
   (DEFINE-FUNCTION-OBJECT "HELP-POPULATE-NODE-PARENTS-TABLE"
    "(DEFUN HELP-POPULATE-NODE-PARENTS-TABLE ((node XMLObject) (parent XMLObject)))"
    (CL:FUNCTION HELP-POPULATE-NODE-PARENTS-TABLE) NULL)
   (DEFINE-FUNCTION-OBJECT "CREATE-NODE-ID-PARENT-TABLE"
    "(DEFUN CREATE-NODE-ID-PARENT-TABLE ())"
    (CL:FUNCTION CREATE-NODE-ID-PARENT-TABLE) NULL)
   (DEFINE-FUNCTION-OBJECT "SIMULATE-MULTIREF-OUTPUT"
    "(DEFUN SIMULATE-MULTIREF-OUTPUT ((node XMLObject)))"
    (CL:FUNCTION SIMULATE-MULTIREF-OUTPUT) NULL)
   (DEFINE-FUNCTION-OBJECT "FIRST-PARENT-FOR-MULTIREF-NODE?"
    "(DEFUN (FIRST-PARENT-FOR-MULTIREF-NODE? BOOLEAN) ((node XMLObject) (parent XMLObject)))"
    (CL:FUNCTION FIRST-PARENT-FOR-MULTIREF-NODE?) NULL)
   (DEFINE-FUNCTION-OBJECT "NTH-PARENT-FOR-MULTIREF-NODE?"
    "(DEFUN (NTH-PARENT-FOR-MULTIREF-NODE? BOOLEAN) ((node XMLObject) (parent XMLObject)))"
    (CL:FUNCTION NTH-PARENT-FOR-MULTIREF-NODE?) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-NODE-ID"
    "(DEFUN (GET-NODE-ID INTEGER) ((node XMLObject)))"
    (CL:FUNCTION GET-NODE-ID) NULL)
   (DEFINE-FUNCTION-OBJECT "HELP-SIMULATE-MULTIREF-OUTPUT"
    "(DEFUN HELP-SIMULATE-MULTIREF-OUTPUT ((node XMLObject) (parent XMLObject) (indent INTEGER)))"
    (CL:FUNCTION HELP-SIMULATE-MULTIREF-OUTPUT) NULL)
   (DEFINE-FUNCTION-OBJECT "SLOT-BASE-AND-PARAMETER-TYPE"
    "(DEFUN (SLOT-BASE-AND-PARAMETER-TYPE TYPE TYPE-SPEC) ((slot SLOT)))"
    (CL:FUNCTION SLOT-BASE-AND-PARAMETER-TYPE) NULL)
   (DEFINE-FUNCTION-OBJECT "PARSE-XML-FROM-STREAM"
    "(DEFUN (PARSE-XML-FROM-STREAM CONS) ((in INPUT-STREAM) (skipFrontmatter? BOOLEAN)))"
    (CL:FUNCTION PARSE-XML-FROM-STREAM) NULL)
   (DEFINE-FUNCTION-OBJECT "PARSE-XML"
    "(DEFUN (PARSE-XML CONS) ((string STRING) (skipFrontmatter? BOOLEAN)))"
    (CL:FUNCTION PARSE-XML) NULL)
   (DEFINE-FUNCTION-OBJECT "FIND-SLOT"
    "(DEFUN (FIND-SLOT SLOT) ((name STRING) (slots (LIST OF SLOT)) (useParametricType? BOOLEAN) (useType? BOOLEAN)))"
    (CL:FUNCTION FIND-SLOT) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-ELEMENT-NAME-FROM-EXPR"
    "(DEFUN (GET-ELEMENT-NAME-FROM-EXPR STRING-WRAPPER) ((expression CONS)))"
    (CL:FUNCTION GET-ELEMENT-NAME-FROM-EXPR) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-ELEMENT-NAMESPACE-PREFIX-FROM-EXPR"
    "(DEFUN (GET-ELEMENT-NAMESPACE-PREFIX-FROM-EXPR STRING-WRAPPER) ((expression CONS)))"
    (CL:FUNCTION GET-ELEMENT-NAMESPACE-PREFIX-FROM-EXPR) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-ELEMENT-NAMESPACE-URI-FROM-EXPR"
    "(DEFUN (GET-ELEMENT-NAMESPACE-URI-FROM-EXPR STRING-WRAPPER) ((expression CONS)))"
    (CL:FUNCTION GET-ELEMENT-NAMESPACE-URI-FROM-EXPR) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-ELEMENT-NAME-FROM-OBJECT"
    "(DEFUN (GET-ELEMENT-NAME-FROM-OBJECT STRING) ((object XMLObject)))"
    (CL:FUNCTION GET-ELEMENT-NAME-FROM-OBJECT) NULL)
   (DEFINE-FUNCTION-OBJECT "STRINGIFY-XML"
    "(DEFUN (STRINGIFY-XML STRING) ((expression CONS)))"
    (CL:FUNCTION STRINGIFY-XML) NULL)
   (DEFINE-FUNCTION-OBJECT "LOOKUP-OBJECT-CREATION-MODULE"
    "(DEFUN (LOOKUP-OBJECT-CREATION-MODULE MODULE) ((namespacePrefix STRING)))"
    (CL:FUNCTION LOOKUP-OBJECT-CREATION-MODULE) NULL)
   (DEFINE-FUNCTION-OBJECT "MAKE-XML-OBJECT"
    "(DEFUN (MAKE-XML-OBJECT OBJECT) ((className STRING) (namespacePrefix STRING) (namespaceURI STRING)))"
    (CL:FUNCTION MAKE-XML-OBJECT) NULL)
   (DEFINE-FUNCTION-OBJECT "ATTRIBUTE-SLOT?"
    "(DEFUN (ATTRIBUTE-SLOT? BOOLEAN) ((slot SLOT)))"
    (CL:FUNCTION ATTRIBUTE-SLOT?) NULL)
   (DEFINE-FUNCTION-OBJECT "ELEMENT-SLOT?"
    "(DEFUN (ELEMENT-SLOT? BOOLEAN) ((slot SLOT)))"
    (CL:FUNCTION ELEMENT-SLOT?) NULL)
   (DEFINE-FUNCTION-OBJECT "COLLECTION-SLOT?"
    "(DEFUN (COLLECTION-SLOT? BOOLEAN) ((slot SLOT)))"
    (CL:FUNCTION COLLECTION-SLOT?) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-OBJECT-SLOT-VALUE"
    "(DEFUN (GET-OBJECT-SLOT-VALUE OBJECT) ((object XMLObject) (slot STORAGE-SLOT)))"
    (CL:FUNCTION GET-OBJECT-SLOT-VALUE) NULL)
   (DEFINE-FUNCTION-OBJECT "SET-OBJECT-SLOT-VALUE"
    "(DEFUN SET-OBJECT-SLOT-VALUE ((object XMLObject) (slot STORAGE-SLOT) (value OBJECT)))"
    (CL:FUNCTION SET-OBJECT-SLOT-VALUE) NULL)
   (DEFINE-FUNCTION-OBJECT "SET-COLLECTION-SLOT-VALUE"
    "(DEFUN SET-COLLECTION-SLOT-VALUE ((object XMLObject) (slot STORAGE-SLOT) (value OBJECT)))"
    (CL:FUNCTION SET-COLLECTION-SLOT-VALUE) NULL)
   (DEFINE-FUNCTION-OBJECT "DECODE-SLOT-VALUE"
    "(DEFUN (DECODE-SLOT-VALUE OBJECT) ((slot STORAGE-SLOT) (value OBJECT)))"
    (CL:FUNCTION DECODE-SLOT-VALUE) NULL)
   (DEFINE-FUNCTION-OBJECT "ENCODE-SLOT-VALUE"
    "(DEFUN (ENCODE-SLOT-VALUE OBJECT) ((slot STORAGE-SLOT) (value OBJECT)))"
    (CL:FUNCTION ENCODE-SLOT-VALUE) NULL)
   (DEFINE-FUNCTION-OBJECT "INITIALIZE-BASE64-DECODING-TABLE"
    "(DEFUN (INITIALIZE-BASE64-DECODING-TABLE (ARRAY () OF INTEGER)) ())"
    (CL:FUNCTION INITIALIZE-BASE64-DECODING-TABLE) NULL)))

(CL:DEFUN STARTUP-MARSHALLER ()
  (CL:LET*
   ((*MODULE*
     (GET-STELLA-MODULE "/STELLA/XML-OBJECTS"
      (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2) (HELP-STARTUP-MARSHALLER1))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 4)
    (CL:SETQ *NODE-PARENTS-TABLE* (NEW-PROPERTY-LIST))
    (CL:SETQ *NODE-ID-PARENTS-TABLE* (NEW-HASH-TABLE))
    (CL:SETQ *BASE64-DECODING-TABLE*
     (INITIALIZE-BASE64-DECODING-TABLE)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 5) (HELP-STARTUP-MARSHALLER2))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7) (HELP-STARTUP-MARSHALLER3)
    (DEFINE-FUNCTION-OBJECT "BASE64-ENCODE-STRING"
     "(DEFUN (BASE64-ENCODE-STRING STRING) ((input STRING)) :DOCUMENTATION \"Base-64 encode `input' and return the result.\" :PUBLIC? TRUE)"
     (CL:FUNCTION BASE64-ENCODE-STRING) NULL)
    (DEFINE-FUNCTION-OBJECT "BASE64-DECODE-STRING"
     "(DEFUN (BASE64-DECODE-STRING STRING) ((input STRING)) :DOCUMENTATION \"Base-64 decode `input' and return the result.\" :PUBLIC? TRUE)"
     (CL:FUNCTION BASE64-DECODE-STRING) NULL)
    (DEFINE-FUNCTION-OBJECT "READ-XML"
     "(DEFUN (READ-XML OBJECT) ((xmlString STRING)))"
     (CL:FUNCTION READ-XML) NULL)
    (DEFINE-FUNCTION-OBJECT "MULTIREF-TEST1"
     "(DEFUN MULTIREF-TEST1 ())" (CL:FUNCTION MULTIREF-TEST1) NULL)
    (DEFINE-FUNCTION-OBJECT "STARTUP-MARSHALLER"
     "(DEFUN STARTUP-MARSHALLER () :PUBLIC? TRUE)"
     (CL:FUNCTION STARTUP-MARSHALLER) NULL)
    (CL:LET*
     ((FUNCTION
       (LOOKUP-FUNCTION
        SYM-MARSHALLER-XML-OBJECTS-STARTUP-MARSHALLER)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-MARSHALLER-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupMarshaller") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "XML-OBJECTS")))
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFSPECIAL *SUPRESS-NAMESPACES?* BOOLEAN FALSE :DOCUMENTATION \"If TRUE, don't output namespace declarations and prefixes\")"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *NODE-PARENTS-TABLE* (PROPERTY-LIST OF XMLObject (LIST OF XMLObject)) (NEW PROPERTY-LIST))"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *NODE-ID-PARENTS-TABLE* (HASH-TABLE OF XMLObject ID-PARENT-STRUCT) (NEW HASH-TABLE))"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT "(DEFGLOBAL *CURRENT-ID* INTEGER 0)"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFSPECIAL *DEFAULT-XML-OBJECT-MODULE* MODULE NULL :PUBLIC? TRUE :DOCUMENTATION \"Default module for the creation of XMLObject instances when converting
from XML to the object representation.  Used unless there is a more
specific namespace-mapping defined.\")" NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *BASE64-ENCODING-TABLE* STRING \"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/\")"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *BASE64-DECODING-TABLE* (ARRAY () OF INTEGER) (INITIALIZE-BASE64-DECODING-TABLE))"
     NULL))))
