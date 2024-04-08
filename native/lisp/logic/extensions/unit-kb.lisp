;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; unit-kb.lisp

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
|#

(CL:IN-PACKAGE "STELLA")

;;; Auxiliary variables:

(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-MEASURE NULL)
(CL:DEFVAR KWD-UNIT-KB-DOCUMENTATION NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-BASE-MEASURE NULL)
(CL:DEFVAR KWD-UNIT-KB-AXIOMS NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-MEASURE-UNIT NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-VALUE-MEASURE NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-NUMERATOR-MEASURES NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-DENOMINATOR-MEASURES NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-COMENSURATE-UNITS NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-UNITS NULL)
(CL:DEFVAR KWD-UNIT-KB--> NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-SUPPORT-?DIM NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-U+ NULL)
(CL:DEFVAR SYM-UNIT-KB-LOGIC-?Z NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-U- NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-U* NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-U-DIV NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-U-ABS NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-U-SIGNUM NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-U-WITHIN-DELTA NULL)
(CL:DEFVAR KWD-UNIT-KB-=> NULL)
(CL:DEFVAR KWD-UNIT-KB-<= NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-U-WITHIN-FACTOR NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-U-MINIMUM-VALUE NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-U-MAXIMUM-VALUE NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-KB-U-SUM NULL)
(CL:DEFVAR SYM-UNIT-KB-UNIT-SUPPORT-STARTUP-UNIT-KB NULL)
(CL:DEFVAR SYM-UNIT-KB-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM (CL:SPECIAL *STARTUP-TIME-PHASE* *MODULE*))

(CL:DEFUN STARTUP-UNIT-KB ()
  (CL:LET*
   ((*MODULE*
     (GET-STELLA-MODULE "/UNIT-SUPPORT" (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2)
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-MEASURE
     (INTERN-RIGID-SYMBOL-WRT-MODULE "MEASURE"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ KWD-UNIT-KB-DOCUMENTATION
     (INTERN-RIGID-SYMBOL-WRT-MODULE "DOCUMENTATION" NULL 2))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-BASE-MEASURE
     (INTERN-RIGID-SYMBOL-WRT-MODULE "BASE-MEASURE"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ KWD-UNIT-KB-AXIOMS
     (INTERN-RIGID-SYMBOL-WRT-MODULE "AXIOMS" NULL 2))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-MEASURE-UNIT
     (INTERN-RIGID-SYMBOL-WRT-MODULE "MEASURE-UNIT"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-VALUE-MEASURE
     (INTERN-RIGID-SYMBOL-WRT-MODULE "VALUE-MEASURE"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-NUMERATOR-MEASURES
     (INTERN-RIGID-SYMBOL-WRT-MODULE "NUMERATOR-MEASURES"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-DENOMINATOR-MEASURES
     (INTERN-RIGID-SYMBOL-WRT-MODULE "DENOMINATOR-MEASURES"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-COMENSURATE-UNITS
     (INTERN-RIGID-SYMBOL-WRT-MODULE "COMENSURATE-UNITS"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-UNITS
     (INTERN-RIGID-SYMBOL-WRT-MODULE "UNITS"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ KWD-UNIT-KB-->
     (INTERN-RIGID-SYMBOL-WRT-MODULE "->" NULL 2))
    (CL:SETQ SYM-UNIT-KB-UNIT-SUPPORT-?DIM
     (INTERN-RIGID-SYMBOL-WRT-MODULE "?DIM" NULL 0))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-U+
     (INTERN-RIGID-SYMBOL-WRT-MODULE "U+"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ SYM-UNIT-KB-LOGIC-?Z
     (INTERN-RIGID-SYMBOL-WRT-MODULE "?Z"
      (GET-STELLA-MODULE "/LOGIC" CL:T) 0))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-U-
     (INTERN-RIGID-SYMBOL-WRT-MODULE "U-"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-U*
     (INTERN-RIGID-SYMBOL-WRT-MODULE "U*"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-U-DIV
     (INTERN-RIGID-SYMBOL-WRT-MODULE "U-DIV"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-U-ABS
     (INTERN-RIGID-SYMBOL-WRT-MODULE "U-ABS"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-U-SIGNUM
     (INTERN-RIGID-SYMBOL-WRT-MODULE "U-SIGNUM"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-U-WITHIN-DELTA
     (INTERN-RIGID-SYMBOL-WRT-MODULE "U-WITHIN-DELTA"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ KWD-UNIT-KB-=>
     (INTERN-RIGID-SYMBOL-WRT-MODULE "=>" NULL 2))
    (CL:SETQ KWD-UNIT-KB-<=
     (INTERN-RIGID-SYMBOL-WRT-MODULE "<=" NULL 2))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-U-WITHIN-FACTOR
     (INTERN-RIGID-SYMBOL-WRT-MODULE "U-WITHIN-FACTOR"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-U-MINIMUM-VALUE
     (INTERN-RIGID-SYMBOL-WRT-MODULE "U-MINIMUM-VALUE"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-U-MAXIMUM-VALUE
     (INTERN-RIGID-SYMBOL-WRT-MODULE "U-MAXIMUM-VALUE"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ SYM-UNIT-KB-UNIT-KB-U-SUM
     (INTERN-RIGID-SYMBOL-WRT-MODULE "U-SUM"
      (GET-STELLA-MODULE "/UNIT-KB" CL:T) 0))
    (CL:SETQ SYM-UNIT-KB-UNIT-SUPPORT-STARTUP-UNIT-KB
     (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-UNIT-KB" NULL 0))
    (CL:SETQ SYM-UNIT-KB-STELLA-METHOD-STARTUP-CLASSNAME
     (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7)
    (DEFINE-FUNCTION-OBJECT "STARTUP-UNIT-KB"
     "(DEFUN STARTUP-UNIT-KB () :PUBLIC? TRUE)"
     (CL:FUNCTION STARTUP-UNIT-KB) NULL)
    (CL:LET*
     ((FUNCTION
       (LOOKUP-FUNCTION SYM-UNIT-KB-UNIT-SUPPORT-STARTUP-UNIT-KB)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-UNIT-KB-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupUnitKb") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "UNIT-SUPPORT")))
    (CL:LET*
     ((*MODULE* (GET-STELLA-MODULE "PL-KERNEL-KB" CL:T))
      (*CONTEXT* *MODULE*))
     (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
     (%DEFCONCEPT
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-MEASURE)
       (COPY-CONS-TREE NIL) KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING
         "A (pre-defined) measure of some physical quantity."))))
     (%DEFCONCEPT
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-BASE-MEASURE)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE "((?M /UNIT-KB/MEASURE) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING
         "A base measure.  One that defines fundamental units which
are not composed of any other units."))
       KWD-UNIT-KB-AXIOMS
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((CLOSED /UNIT-KB/BASE-MEASURE) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFRELATION
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-MEASURE-UNIT)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "(((?M /UNIT-KB/MEASURE) (?U STRING)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING
         "A mapping between a Measure and the unit names that belong
to that measure."))
       KWD-UNIT-KB-AXIOMS
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((CLOSED /UNIT-KB/MEASURE-UNIT) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFFUNCTION
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-VALUE-MEASURE)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((?DIM (?M /UNIT-KB/MEASURE)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING
         "A mapping from a dimensioned value to the corresponding measure.
It may not, in fact, exist for dimensions that are formed by ad hoc
combinations of units or by arithmetic manipulations of dimensions."))
       KWD-UNIT-KB-AXIOMS
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((AND (COMPUTED /UNIT-KB/VALUE-MEASURE) (CLOSED /UNIT-KB/VALUE-MEASURE) (RELATION-SPECIALIST /UNIT-KB/VALUE-MEASURE U-VALUE-MEASURE-SPECIALIST)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFFUNCTION
      (CONS-LIST
       (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-NUMERATOR-MEASURES)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((?DIM (?M /PL-KERNEL-KB/LIST)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING "A mapping from a dimensioned value or a measure to
a list of the base measures in the numerator of the expression.
The measures will be in a canonical order."))
       KWD-UNIT-KB-AXIOMS
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((AND (COMPUTED /UNIT-KB/NUMERATOR-MEASURES) (RELATION-SPECIALIST /UNIT-KB/NUMERATOR-MEASURES U-BASE-MEASURES-SPECIALIST)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFFUNCTION
      (CONS-LIST
       (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-DENOMINATOR-MEASURES)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((?DIM (?M /PL-KERNEL-KB/LIST)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING "A mapping from a dimensioned value or a measure to
a list of the base measures in the denominator of the expression.
The measures will be in a canonical order."))
       KWD-UNIT-KB-AXIOMS
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((AND (COMPUTED /UNIT-KB/DENOMINATOR-MEASURES) (RELATION-SPECIALIST /UNIT-KB/DENOMINATOR-MEASURES U-BASE-MEASURES-SPECIALIST)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFRELATION
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-COMENSURATE-UNITS)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE "((?X ?Y) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING
         "A (computed) relation between units expressions that are
comensurate.  That means they can be compared with one another,
added or subtracted.  Works with either dimensioned quantities or
unit expressions (strings)"))
       KWD-UNIT-KB-AXIOMS
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((AND (COMPUTED /UNIT-KB/COMENSURATE-UNITS) (RELATION-SPECIALIST /UNIT-KB/COMENSURATE-UNITS COMENSURATE-UNITS-SPECIALIST) (HANDLES-REVERSE-POLARITY COMENSURATE-UNITS-SPECIALIST)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFFUNCTION
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-UNITS)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "(((?M NUMBER) (?U STRING)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB--> (COPY-CONS-TREE SYM-UNIT-KB-UNIT-SUPPORT-?DIM)
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING
         "Connects a MAGNITUDE STRING representation of a dimensioned number
 to the actual
internal representation."))
       KWD-UNIT-KB-AXIOMS
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((AND (COMPUTED /UNIT-KB/UNITS) (RELATION-EVALUATOR /UNIT-KB/UNITS UNITS-EVALUATOR) (RELATION-SPECIALIST /UNIT-KB/UNITS UNITS-SPECIALIST) (GOES-TRUE-DEMON /UNIT-KB/UNITS UNITS-EVALUATOR)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFFUNCTION
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-U+)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE "((?X ?Y) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB--> (COPY-CONS-TREE SYM-UNIT-KB-LOGIC-?Z)
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING "Function that adds two dim numbers."))
       KWD-UNIT-KB-AXIOMS
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((AND (COMPUTED /UNIT-KB/U+) (RELATION-CONSTRAINT /UNIT-KB/U+ U-PLUS-CONSTRAINT) (RELATION-SPECIALIST /UNIT-KB/U+ /PL-KERNEL-KB/CONSTRAINT-SPECIALIST)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFFUNCTION
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-U-)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE "((?X ?Y) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB--> (COPY-CONS-TREE SYM-UNIT-KB-LOGIC-?Z)
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING "Function that subtracts two dim numbers."))
       KWD-UNIT-KB-AXIOMS
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((AND (COMPUTED /UNIT-KB/U-) (RELATION-CONSTRAINT /UNIT-KB/U- U-MINUS-CONSTRAINT) (RELATION-SPECIALIST /UNIT-KB/U- /PL-KERNEL-KB/CONSTRAINT-SPECIALIST)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFFUNCTION
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-U*)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE "((?X ?Y) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB--> (COPY-CONS-TREE SYM-UNIT-KB-LOGIC-?Z)
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING "Function that multiplies two dim numbers."))
       KWD-UNIT-KB-AXIOMS
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((AND (COMPUTED /UNIT-KB/U*) (RELATION-CONSTRAINT /UNIT-KB/U* U-TIMES-CONSTRAINT) (RELATION-SPECIALIST /UNIT-KB/U* /PL-KERNEL-KB/CONSTRAINT-SPECIALIST)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFFUNCTION
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-U-DIV)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE "((?X ?Y) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB--> (COPY-CONS-TREE SYM-UNIT-KB-LOGIC-?Z)
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING "Function that divides two dim numbers."))
       KWD-UNIT-KB-AXIOMS
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((AND (COMPUTED /UNIT-KB/U-DIV) (RELATION-CONSTRAINT /UNIT-KB/U-DIV U-DIVIDE-CONSTRAINT) (RELATION-SPECIALIST /UNIT-KB/U-DIV /PL-KERNEL-KB/CONSTRAINT-SPECIALIST)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFFUNCTION
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-U-ABS)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE "((?X) \"/UNIT-SUPPORT\")" "/UNIT-SUPPORT"))
       KWD-UNIT-KB--> (COPY-CONS-TREE SYM-UNIT-KB-LOGIC-?Z)
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE (WRAP-STRING "Absolute value of dim number."))
       KWD-UNIT-KB-AXIOMS
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((AND (COMPUTED /UNIT-KB/U-ABS) (RELATION-SPECIALIST /UNIT-KB/U-ABS U-ABS-SPECIALIST)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFFUNCTION
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-U-SIGNUM)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE "((?X) \"/UNIT-SUPPORT\")" "/UNIT-SUPPORT"))
       KWD-UNIT-KB-->
       (COPY-CONS-TREE
        (GET-QUOTED-TREE "((?Z INTEGER) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE (WRAP-STRING "Signum function of dim number."))
       KWD-UNIT-KB-AXIOMS
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((AND (COMPUTED /UNIT-KB/U-SIGNUM) (RELATION-SPECIALIST /UNIT-KB/U-SIGNUM U-SIGNUM-SPECIALIST)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFRELATION
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-U-WITHIN-DELTA)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE "((?X ?Y ?Z) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING "?X and ?Y do not differ in value by more than ?Z.
?Z must be positive.

For example (/unit-kb/u-within-delta (units 10.0 \"ft\") (units 3.0 \"m\") (units 2 \"in\"))
is true.  This relation is useful for numeric comparisons where floating point
computations (or other rounding errors) introduce minor inaccuracies
that prevent a straight equality test from succeeding."))
       KWD-UNIT-KB-=>
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((>= (/UNIT-KB/U-SIGNUM ?Z) 0) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB-<=
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((=< (/UNIT-KB/U-ABS (/UNIT-KB/U- ?X ?Y)) ?Z) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFRELATION
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-U-WITHIN-FACTOR)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE "((?X ?Y ?Z) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING "?X and ?Y are with factor ?Z of each other.  The
factor is applied relative to ?X.  ?Z must be positive.

That means (/unit-kb/u-within-factor (units 100 \"km\") (units 60 \"km\") (units 0.5 \"\"))
is true (60km is in the range 50km-150km), but the converse
  (/unit-kb/u-within-factor (units 60 \"km\") (units 100 \"km\") (units 50 \"%\"))
is not (100km is not in the range 30km-90km)."))
       KWD-UNIT-KB-=>
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((>= (/UNIT-KB/U-SIGNUM ?Z) 0) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB-<=
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((=< (/UNIT-KB/U-ABS (/UNIT-KB/U- ?X ?Y)) (/UNIT-KB/U* ?Z (/UNIT-KB/U-ABS ?X))) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFRELATION
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-U-MINIMUM-VALUE)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "(((?L /PL-KERNEL-KB/COLLECTION) ?MIN) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING
         "Binds ?min to the minimum of the dimensioned numbers in the list ?l."))
       KWD-UNIT-KB-AXIOMS
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((AND (RELATION-SPECIALIST /UNIT-KB/U-MINIMUM-VALUE MINIMUM-OF-UNITS-SPECIALIST) (SINGLE-VALUED /UNIT-KB/U-MINIMUM-VALUE)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFRELATION
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-U-MAXIMUM-VALUE)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "(((?L /PL-KERNEL-KB/COLLECTION) ?MAX) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING
         "Binds ?max to the maximum of the dimensioned numbers in the list ?l."))
       KWD-UNIT-KB-AXIOMS
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((AND (RELATION-SPECIALIST /UNIT-KB/U-MAXIMUM-VALUE MAXIMUM-OF-UNITS-SPECIALIST) (SINGLE-VALUED /UNIT-KB/U-MAXIMUM-VALUE)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%DEFRELATION
      (CONS-LIST (COPY-CONS-TREE SYM-UNIT-KB-UNIT-KB-U-SUM)
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "(((?L /PL-KERNEL-KB/COLLECTION) ?SUM) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))
       KWD-UNIT-KB-DOCUMENTATION
       (COPY-CONS-TREE
        (WRAP-STRING
         "Binds ?sum to the sum of the dimensioned numbers in the list ?l."))
       KWD-UNIT-KB-AXIOMS
       (COPY-CONS-TREE
        (GET-QUOTED-TREE
         "((AND (RELATION-SPECIALIST /UNIT-KB/U-SUM SUM-OF-UNITS-SPECIALIST) (SINGLE-VALUED /UNIT-KB/U-SUM)) \"/UNIT-SUPPORT\")"
         "/UNIT-SUPPORT"))))
     (%ASSERT
      (COPY-CONS-TREE
       (GET-QUOTED-TREE
        "((AND (COMPUTED-PROCEDURE UNITS-EVALUATOR) (COMPUTED-PROCEDURE UNITS-SPECIALIST) (COMPUTED-PROCEDURE U-ABS-SPECIALIST) (COMPUTED-PROCEDURE U-SIGNUM-SPECIALIST) (COMPUTED-PROCEDURE MINIMUM-OF-UNITS-SPECIALIST) (COMPUTED-PROCEDURE MAXIMUM-OF-UNITS-SPECIALIST) (COMPUTED-PROCEDURE SUM-OF-UNITS-SPECIALIST) (COMPUTED-PROCEDURE U-VALUE-MEASURE-SPECIALIST) (COMPUTED-PROCEDURE U-BASE-MEASURES-SPECIALIST) (COMPUTED-PROCEDURE COMENSURATE-UNITS-SPECIALIST)) \"/UNIT-SUPPORT\")"
        "/UNIT-SUPPORT")))
     (INITIALIZE-MEASURE-CONCEPTS) (PROCESS-DEFINITIONS)))))
