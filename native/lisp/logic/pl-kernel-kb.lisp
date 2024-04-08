;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; pl-kernel-kb.lisp

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

(CL:DEFVAR |/PL-KERNEL-KB/SGT-PL-KERNEL-KB-PL-KERNEL-KB-CONCEPT| NULL)
(CL:DEFVAR |/PL-KERNEL-KB/KWD-PL-KERNEL-KB-ASSERT-TRUE| NULL)
(CL:DEFVAR |/PL-KERNEL-KB/SGT-PL-KERNEL-KB-PL-KERNEL-KB-CLASS| NULL)
(CL:DEFVAR |/PL-KERNEL-KB/SYM-PL-KERNEL-KB-STELLA-THING| NULL)
(CL:DEFVAR |/PL-KERNEL-KB/SYM-PL-KERNEL-KB-PL-KERNEL-KB-STARTUP-PL-KERNEL-KB| NULL)
(CL:DEFVAR |/PL-KERNEL-KB/SYM-PL-KERNEL-KB-STELLA-METHOD-STARTUP-CLASSNAME| NULL)

;;; Forward declarations:

(CL:DECLAIM (CL:SPECIAL *STARTUP-TIME-PHASE* *MODULE* NIL))

;;; (DEFGLOBAL *PL-KERNEL-KB-DEFINITIONS* ...)

(CL:DEFVAR |/PL-KERNEL-KB/*PL-KERNEL-KB-DEFINITIONS*| NULL)

;;; (DEFUN INITIALIZE-KERNEL-KB ...)

(CL:DEFUN |/PL-KERNEL-KB/INITIALIZE-KERNEL-KB| ()
  "Bootstrap the PowerLoom built-in kernel KB."
  (CL:LET*
   ((KERNELINITFILE
     (LOOKUP-CONFIGURATION-PROPERTY "PLKernelKBInitFile"
      (WRAP-STRING "PL:sources;logic;pl-kernel-kb.plm") NULL))
    (KERNELKBDEFINITIONS
     (COPY-CONS-TREE |/PL-KERNEL-KB/*PL-KERNEL-KB-DEFINITIONS*|))
    (DUMMYCONCEPT NULL))
   (CL:SETQ KERNELINITFILE KERNELINITFILE)
   (CL:LET* ((*WARNIFREDEFINE?* CL:NIL))
    (CL:DECLARE (CL:SPECIAL *WARNIFREDEFINE?*))
    (CL:LET*
     ((*MODULE* (GET-STELLA-MODULE "PL-KERNEL-KB" CL:T))
      (*CONTEXT* *MODULE*))
     (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
     (CL:LET* ((SELF-000 (NEW-NAMED-DESCRIPTION)))
      (CL:SETF (%SURROGATE-VALUE-INVERSE SELF-000)
       |/PL-KERNEL-KB/SGT-PL-KERNEL-KB-PL-KERNEL-KB-CONCEPT|)
      (CL:SETF (%IO-VARIABLE-TYPES SELF-000)
       (LIST |/PL-KERNEL-KB/SGT-PL-KERNEL-KB-PL-KERNEL-KB-CONCEPT|))
      (CL:SETQ DUMMYCONCEPT SELF-000))
     (CL:SETF
      (%SURROGATE-VALUE
       |/PL-KERNEL-KB/SGT-PL-KERNEL-KB-PL-KERNEL-KB-CONCEPT|)
      DUMMYCONCEPT)
     (GET-DESCRIPTION-EXTENSION DUMMYCONCEPT CL:T)
     (UPDATE-ISA-PROPOSITION DUMMYCONCEPT
      |/PL-KERNEL-KB/SGT-PL-KERNEL-KB-PL-KERNEL-KB-CONCEPT|
      |/PL-KERNEL-KB/KWD-PL-KERNEL-KB-ASSERT-TRUE|)
     (CL:SETF
      (%SURROGATE-VALUE
       |/PL-KERNEL-KB/SGT-PL-KERNEL-KB-PL-KERNEL-KB-CLASS|)
      DUMMYCONCEPT)
     (%EVALUATE (%%VALUE KERNELKBDEFINITIONS))
     (CL:SETF
      (%SURROGATE-VALUE
       |/PL-KERNEL-KB/SGT-PL-KERNEL-KB-PL-KERNEL-KB-CLASS|)
      (%SURROGATE-VALUE
       |/PL-KERNEL-KB/SGT-PL-KERNEL-KB-PL-KERNEL-KB-CONCEPT|))
     (CL:LET*
      ((DEFINITION NULL) (ITER-000 (%%REST KERNELKBDEFINITIONS)))
      (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
       (CL:SETQ DEFINITION (%%VALUE ITER-000)) (%EVALUATE DEFINITION)
       (CL:SETQ ITER-000 (%%REST ITER-000))))
     (FINALIZE-OBJECTS)
     (CL:LET* ((MDL NULL) (ITER-001 (ALL-MODULES)))
      (CL:LOOP WHILE (NEXT? ITER-001) DO
       (CL:SETQ MDL (%VALUE ITER-001)) (INTRODUCE-MODULE MDL)))
     (CL:LET*
      ((THING
        (GET-DESCRIPTION
         (GET-STELLA-CLASS
          |/PL-KERNEL-KB/SYM-PL-KERNEL-KB-STELLA-THING| CL:T))))
      (EVALUATE-STRING "(ASSERT (DOCUMENTATION THING  
           \"The class of all things.  `Thing' is the top-most concept
in the concept hierarchy.\"))"))))))

(CL:DEFUN |/PL-KERNEL-KB/STARTUP-PL-KERNEL-KB| ()
  (CL:LET*
   ((*MODULE*
     (GET-STELLA-MODULE "/PL-KERNEL-KB" (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2)
    (CL:SETQ |/PL-KERNEL-KB/SGT-PL-KERNEL-KB-PL-KERNEL-KB-CONCEPT|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "CONCEPT" NULL 1))
    (CL:SETQ |/PL-KERNEL-KB/KWD-PL-KERNEL-KB-ASSERT-TRUE|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "ASSERT-TRUE" NULL 2))
    (CL:SETQ |/PL-KERNEL-KB/SGT-PL-KERNEL-KB-PL-KERNEL-KB-CLASS|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "CLASS" NULL 1))
    (CL:SETQ |/PL-KERNEL-KB/SYM-PL-KERNEL-KB-STELLA-THING|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "THING"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0))
    (CL:SETQ
     |/PL-KERNEL-KB/SYM-PL-KERNEL-KB-PL-KERNEL-KB-STARTUP-PL-KERNEL-KB|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-PL-KERNEL-KB" NULL 0))
    (CL:SETQ
     |/PL-KERNEL-KB/SYM-PL-KERNEL-KB-STELLA-METHOD-STARTUP-CLASSNAME|
     (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7)
    (DEFINE-FUNCTION-OBJECT "INITIALIZE-KERNEL-KB"
     "(DEFUN INITIALIZE-KERNEL-KB () :DOCUMENTATION \"Bootstrap the PowerLoom built-in kernel KB.\" :PUBLIC? TRUE :COMMAND? TRUE)"
     (CL:FUNCTION |/PL-KERNEL-KB/INITIALIZE-KERNEL-KB|) NULL)
    (DEFINE-FUNCTION-OBJECT "STARTUP-PL-KERNEL-KB"
     "(DEFUN STARTUP-PL-KERNEL-KB () :PUBLIC? TRUE)"
     (CL:FUNCTION |/PL-KERNEL-KB/STARTUP-PL-KERNEL-KB|) NULL)
    (CL:LET*
     ((FUNCTION
       (LOOKUP-FUNCTION
        |/PL-KERNEL-KB/SYM-PL-KERNEL-KB-PL-KERNEL-KB-STARTUP-PL-KERNEL-KB|)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      |/PL-KERNEL-KB/SYM-PL-KERNEL-KB-STELLA-METHOD-STARTUP-CLASSNAME|
      (WRAP-STRING "_StartupPlKernelKb") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "PL-KERNEL")))
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *PL-KERNEL-KB-DEFINITIONS* CONS NULL)" NULL)
    (CL:SETQ |/PL-KERNEL-KB/*PL-KERNEL-KB-DEFINITIONS*|
     (GET-QUOTED-TREE
      "(((DEFCONCEPT CONCEPT (?X RELATION) :DOCUMENTATION \"The class of reified unary relations.  The Powerloom
notion of `concept' corresponds to the object-oriented notion of `class'.
From a logic standpoint, the notion of a concept is hard to distinguish
from the notion of `unary relation'.  The conceptual distinction is
best illustrated in the domain of linguistics, where concepts are
identified with collective nouns while unary relations are identified
with adjectives.  For example, `Rock' is a concept, while `rocky' is a
unary relation.\" :AXIOMS (AND (SYNONYM CONCEPT CLASS) (CLOSED CONCEPT))) (DEFCONCEPT RELATION (?X SET) :DOCUMENTATION \"The class of relations.  This includes all concepts and
all functions.\" :AXIOMS (CLOSED RELATION)) (DEFCONCEPT FUNCTION (?R RELATION) :DOCUMENTATION \"A relation is a function if its last argument
is a function of its first n-1 arguments, i.e., if it is a single-valued
relation.  Functions explicitly declared as such differ from relations
in that they may appear syntactically as a term applied to n-1 arguments.
For example, to express the sentence \\\"two plus two equals four\\\", because
`+' is a function we can write `(= (+ 2 2) 4)'.  The same sentence written
in relational syntax would look like `(+ 2 2 4)'.  If a relation is
introduced using the `defrelation' syntax and also declared to be
single-valued, the functional syntax does not apply; only the explicit
use of `deffunction' sanctions the use of that syntax.\" :AXIOMS (CLOSED FUNCTION)) (DEFCONCEPT AGGREGATE (?A) :DOCUMENTATION \"?a is an aggregate\") (DEFCONCEPT COLLECTION (?C AGGREGATE) :DOCUMENTATION \"The class of all collections.  This includes all sets,
lists, concepts, and relations.\" :AXIOMS (ABSTRACT COLLECTION)) (DEFCONCEPT DUPLICATE-FREE-COLLECTION (?C COLLECTION) :DOCUMENTATION \"?c is free of duplicates\" :=>> (DUPLICATE-FREE ?C)) (DEFCONCEPT SET (?S DUPLICATE-FREE-COLLECTION) :DOCUMENTATION \"This class denotes the mathematical notion of a 'set';
a collection that has no duplicates.\") (DEFCONCEPT NUMERIC-SET (?S COLLECTION) :DOCUMENTATION \"?s is a set of numbers\" :AXIOMS (ABSTRACT NUMERIC-SET)) (DEFCONCEPT LIST (?L COLLECTION) :DOCUMENTATION \"A list is an ordered collection of elements.  The range
of the function `listof' consists of elements of type `List'.\" :=>> (ORDERED ?L)) (DEFCONCEPT GROUP (?C DUPLICATE-FREE-COLLECTION) :DOCUMENTATION \"?c is a group\") (DEFCONCEPT STUFF (?S AGGREGATE) :DOCUMENTATION \"?s is stuff\") (DEFCONCEPT SCALAR (?X) :DOCUMENTATION \"The class of scalar quantities.\") (ASSERT (SUBSET-OF NUMBER SCALAR)) (DEFCONCEPT SCALAR-INTERVAL (?X SCALAR) :DOCUMENTATION \"An interval of scalar quantities. \") (ASSERT (SUBSET-OF INTEGER-INTERVAL SCALAR-INTERVAL)) (DEFRELATION PHRASE (?R (?S STRING)) :DOCUMENTATION \"A phrase is a variablized sentence, a template, that
is used to express individual axiomatic facts as natural language
sentences.  By convention, a phrase contains one or more occurrences
of each variable in a relation or concept definition, it does not
begin with a capital letter, and it has no concluding period.
Systematic attachment of phrases to relations can be leveraged by
tools that generate natural language paraphrases of logic sentences.\" :PHRASE \"?r has phrase ?s\") (DEFRELATION LEXEME (?R (?S STRING)) :DOCUMENTATION \"?s is a lexeme for the relation or individual ?r.
A relation or individual ?r can have zero or more lexemes, words that are
natural langage equivalents of a logical constant.  The same lexeme may be
attached to more than one constant.\") (DEFRELATION COMMENT (?X (?S STRING)) :DOCUMENTATION \"?s is a comment attached to ?x.  Comments are
a generalization of other annotations such as `documentation' and
`issue' strings.\") (DEFRELATION DOCUMENTATION (?X (?S STRING)) :DOCUMENTATION \"?s is a documentation string attached to ?x.  Some
of the PowerLoom text processing tools look for documentation strings and 
import them into documents.\" :=> (COMMENT ?X ?S)) (DEFRELATION ISSUE (?X (?S STRING)) :DOCUMENTATION \"?s is an issue attached to ?x.  An issue string 
normally comments on a topic that has not been resolved to everyone's
satisfaction.\" :=> (COMMENT ?X ?S)) (DEFRELATION EXAMPLE ((?R RELATION) ?E) :DOCUMENTATION \"?e is an example of (the use of) ?r.\") (DEFRELATION IMAGE-URL (?X (?URL STRING)) :DOCUMENTATION \"?url is a URL pointing to an image illustrating ?x.
The Ontosaurus browser looks for `image-url' values attached to
objects it is presenting, and displays them prominently, thereby spiffing
up its displays.\") (DEFRELATION RELATION-SPECIALIST ((?R RELATION) (?SP COMPUTED-PROCEDURE)) :DOCUMENTATION \"Names a 'specialist' (a function) that evaluates an (atomic) relation
proposition during query processing.  This defines an extensible
means for computing with the control stack.  The function is passed
a CONTROL-FRAME that contains the proposition, and returns a keyword
:FINAL-SUCCESS, :CONTINUING-SUCCESS, :FAILURE, or :TERMINAL-FAILURE
that controls the result of the computation.\" :AXIOMS (SINGLE-VALUED RELATION-SPECIALIST)) (DEFRELATION RELATION-EVALUATOR ((?R RELATION) (?EV COMPUTED-PROCEDURE)) :DOCUMENTATION \"Names an 'evaluator' (a function) that evaluates an (atomic) relation
proposition during constraint propagation.  This defines an extensible
means for computing using auxiliary data structures.  The function is passed
a proposition for evaluation which might update the proposition, generate
additional assertions or trigger further evaluations.  Evaluators have to
check the truth-value of the passed-in proposition and perform their actions
accordingly.  An evaluated proposition might be true, false or even unknown
in case the propositon was just newly constructed.\" :AXIOMS (SINGLE-VALUED RELATION-EVALUATOR)) (DEFRELATION RELATION-COMPUTATION ((?R RELATION) (?COMPUTATION COMPUTED-PROCEDURE)) :DOCUMENTATION \"Names a 'computation' (a function) that evaluates an (atomic) relation
proposition during query processing.  The function is passed a proposition
for evaluation for which all arguments are bound.  The function
returns a BOOLEAN if it represents a predicate, or some sort of value
if it is a function.\" :=>> (RELATION-SPECIALIST ?R COMPUTATION-SPECIALIST) :AXIOMS (SINGLE-VALUED RELATION-COMPUTATION)) (DEFRELATION RELATION-CONSTRAINT ((?R RELATION) (?COMPUTATION COMPUTED-PROCEDURE)) :DOCUMENTATION \"Names a 'computation' (a function) that evaluates an (atomic) relation
proposition during query processing.  The function is passed a proposition
for evaluation for which at most one argument is unbound.  The function
returns a BOOLEAN if it represents a predicate, or some sort of value
if it is a function.  If all arguments are bound the function computes whether
the constraint holds.  If all but one argument is bound and the unbound
argument is a pattern variable then the missing value is computed.\" :=>> (RELATION-SPECIALIST ?R CONSTRAINT-SPECIALIST) :AXIOMS (SINGLE-VALUED RELATION-CONSTRAINT)) (DEFRELATION HANDLES-REVERSE-POLARITY ((?CP COMPUTED-PROCEDURE)) :DOCUMENTATION \"Very specialized PowerLoom predicate.  Indicates that a computed procedure
used as a relation specialist is programmed to handle reverse
polarity (*reversePolarity?*).\") (DEFRELATION UPDATE-PROPOSITION-DEMON ((?R RELATION) (?COMPUTATION COMPUTED-PROCEDURE)) :DOCUMENTATION \"Names a 'computation' (a function) that is attached (logically)
to ?r  Each time a proposition with predicate ?r has its truth
value updated (even redundantly), the function is applied to that
proposition.\" :AXIOMS (SINGLE-VALUED UPDATE-PROPOSITION-DEMON)) (DEFRELATION GOES-TRUE-DEMON ((?R RELATION) (?COMPUTATION COMPUTED-PROCEDURE)) :DOCUMENTATION \"Names a 'computation' (a function) that is attached (logically)
to ?r  Each time a proposition with predicate ?r becomes
true, the function is applied to that proposition.\" :AXIOMS (SINGLE-VALUED GOES-TRUE-DEMON)) (DEFRELATION GOES-UNKNOWN-DEMON ((?R RELATION) (?COMPUTATION COMPUTED-PROCEDURE)) :DOCUMENTATION \"Names a 'computation' (a function) that is attached (logically)
to ?r  Each time a proposition with predicate ?r becomes
unknown, the function is applied to that proposition.\" :AXIOMS (SINGLE-VALUED GOES-UNKNOWN-DEMON)) (DEFRELATION GOES-FALSE-DEMON ((?R RELATION) (?COMPUTATION COMPUTED-PROCEDURE)) :DOCUMENTATION \"Names a 'computation' (a function) that is attached (logically)
to ?r  Each time a proposition with predicate ?r becomes
false, the function is applied to that proposition.\" :AXIOMS (SINGLE-VALUED GOES-FALSE-DEMON)) (DEFRELATION SYNONYM (?TERM ?SYNONYM) :PHRASE \"?synonym is a synonym for ?term\" :DOCUMENTATION \"Assert that `?synonym' is a synonym of `?term'.  This
causes all references to `?synonym' to be interpreted as references
to `?term'.  Retraction eliminates a synonym relation.\") (ASSERT (AND (GOES-TRUE-DEMON SYNONYM ASSERT-SYNONYM-DEMON) (GOES-UNKNOWN-DEMON SYNONYM RETRACT-SYNONYM-DEMON))) (DEFCONCEPT SKOLEM-FUNCTION (?X FUNCTION) :DOCUMENTATION \"Skolem function meta class to annotate user-defined skolem
functions.  Using this is generally not necessary given the generic `skolem-fn'
definitiont below.\" :=>> (TOTAL ?X)) (DEFFUNCTION SKOLEM-FN (?ID ?ARGS ?SK) :DOCUMENTATION \"A generic skolem function that can be instantiated into
a unique skolem function term by providing an appropriately unique ?id.
?args are the universally quantfied arguments relative to which we postulate
the existence of ?sk.  For example, to represent the rule `every person
has a mother' we could write:
  (=> (and (person ?x) (skolem-fn $skfn ?x ?m)) (mother ?x ?m)).
Note the use of the automatic instance `$skfn' to uniquely identify this
skolem function term.  Any other unique ID could have been used as well.\" :VARIABLE-ARITY TRUE :TOTAL TRUE) (DEFFUNCTION COLLECTIONOF (?M) :-> (?C COLLECTION) :DOCUMENTATION \"Abstract function existing to subsume 'SETOF'
and 'LISTOF'.\" :AXIOMS (VARIABLE-ARITY COLLECTIONOF)) (DEFFUNCTION SETOF (?M) :-> (?C SET) :DOCUMENTATION \"Term-forming function that defines an enumerated set
consisting of all function arguments.  `setof' is like `listof' except
that it removes duplicate values.\" :SUBSET-OF COLLECTIONOF :VARIABLE-ARITY TRUE :TOTAL TRUE :CLOSED TRUE) (DEFFUNCTION LISTOF (?M) :-> (?C LIST) :DOCUMENTATION \"Term-forming function that defines an ordered list
consisting of all function arguments.  Within logical expressions
`listof' is most commonly used in conjunction with the `member-of'
predicate.  For example the query
	 
  (retrieve ?x (member-of ?x (listof a b c)))
	
returns the constants `a', `b', and `c' on successive iterations.\" :SUBSET-OF COLLECTIONOF :VARIABLE-ARITY TRUE :TOTAL TRUE :CLOSED TRUE) (DEFRELATION HOLDS ((?RELATION RELATION) ?ARGUMENTS) :DOCUMENTATION \"True if the tuple '?arguments' is a member of the
relation '?relation'.  `holds' is a variable arity predicate that takes
a relation as its first argument, and zero or more additional arguments.
It returns values equivalent to a subgoal that has the first argument
as a predicate and the remaining arguments shifted one place to the left.
For `holds' to succeed, the (first) relation argument must be bound --
PowerLoom will NOT cycle through all relations searching for ones that
permit the proof to succeed.  However, users can obtain the same effect
if they choose by using other second-order predicates to generate
relation bindings.  For example, the query
	 
   (retrieve all ?x (and (Relation ?r)
                         (holds ?r Fred ?x)))
	
retrieves all constants for which there is some binary relation that
relates `Fred' to that relation.\" :AXIOMS (AND (VARIABLE-ARITY HOLDS) (RELATION-SPECIALIST HOLDS HOLDS-SPECIALIST))) (DEFFUNCTION VALUE ((?FUNCTION FUNCTION) ?ARGUMENTS) :-> ?VALUE :DOCUMENTATION \"True if applying '?function' to '?arguments'
yields the value '?value'.  The `value' predicate is the analog
of `holds', except that it applies to functions instead of relations.\" :VARIABLE-ARITY TRUE :RELATION-SPECIALIST HOLDS-SPECIALIST) (DEFFUNCTION TOTAL-VALUE ((?FUNCTION FUNCTION) ?ARGUMENTS) :-> ?VALUE :DOCUMENTATION \"Identical to `value' but treats ?function as a total function even if
it isn't.  For the case where ?function and all its inputs are bound and no existing
value could be found for the unbound ?value argument, a skolem term will be created and
bound to ?value.  This is useful sometimes to create function terms on the fly in queries
for functions where it isn't generally warranted to mark them as total.\" :VARIABLE-ARITY TRUE :RELATION-SPECIALIST TOTAL-VALUE-SPECIALIST) (DEFRELATION IST ((?CONTEXT CONTEXT) (?P PROPOSITION)) :DOCUMENTATION \"True if proposition '?p' is true in context '?context'.
The `IST' (is true) relation allows one to evaluate a query or rule in more
than one context.  A common use of `IST' is in defining 'lifting axioms'
that import knowledge from one context to another.  For example, below is
a rule that accesses a `patient-record' relation in a module called
`Medical-Kb', 'lifts-out' the `age' column, and imports it into a
`has-age' relation in the current context.
	 
  (<= (has-age ?person ?age)
      (and (has-ssn ?person ?ssn)
           (exists (?1 ?2 ?3 ?4)
              (ist Medical-Kb (patient-record ?ssn ?1 ?2 ?age ?3 ?4)))))
	
\" :AXIOMS (AND (RELATION-SPECIALIST IST IST-SPECIALIST) (HANDLES-REVERSE-POLARITY IST-SPECIALIST))) (DEFRELATION INCOHERENT ((?CONTEXT CONTEXT) (?P PROPOSITION)) :DOCUMENTATION \"True if proposition ?p is inconsistent or otherwise
incoherent in ?context.  This is a system-asserted relation that is
used when inconsistencies are detected during forward inference.  The
main purpose of this relation is to allow one to find inconsistent propositions
via queries and/or to attach a goes-true-demon in case special-purpose handling
of contradictions is needed.\") (DEFFUNCTION PROPOSITION-RELATION ((?P PROPOSITION) (?OP RELATION)) :DOCUMENTATION \"Return the predicate operator ?op of ?p.\" :COMPUTED TRUE :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION PROPOSITION-RELATION-COMPUTATION :CLOSED TRUE) (DEFFUNCTION PROPOSITION-ARGUMENT ((?P PROPOSITION) (?I INTEGER) ?ARG) :DOCUMENTATION \"Return the ?i-th ?arg of ?p (zero-based).  Negative ?i's count
from the end, for example, -1 accesses the last argument of ?p.\" :COMPUTED TRUE :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION PROPOSITION-ARGUMENT-COMPUTATION :CLOSED TRUE) (DEFFUNCTION PROPOSITION-ARGUMENTS ((?P PROPOSITION) (?ARGS LIST)) :DOCUMENTATION \"Return all arguments of ?p as a list ?args.\" :COMPUTED TRUE :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION PROPOSITION-ARGUMENTS-COMPUTATION :CLOSED TRUE) (DEFFUNCTION PROPOSITION-ARITY ((?P PROPOSITION) (?ARITY INTEGER)) :DOCUMENTATION \"Return the number of arguments in ?p.\" :COMPUTED TRUE :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION PROPOSITION-ARITY-COMPUTATION :CLOSED TRUE) (DEFRELATION CONCEIVED-PROPOSITION-TERM ((?GOAL PROPOSITION) (?TERM PROPOSITION)) :DOCUMENTATION \"Retrieves existing conceived proposition objects ?term that match
the proposition ?goal.  The propositions bound to ?term must have been previously
conceived (but not necessarily asserted) and be visible in the current module.
This is a (temporary) kludge to speed up retrieval of nested, modal propositions
using argument keys in the nested proposition.\" :RELATION-SPECIALIST CONCEIVED-PROPOSITION-TERM-SPECIALIST :CLOSED TRUE) (DEFFUNCTION TERM-RELATION (?TERM (?OP RELATION)) :DOCUMENTATION \"Return the function operator ?op defining this function ?term.\" :COMPUTED TRUE :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION PROPOSITION-RELATION-COMPUTATION :CLOSED TRUE) (DEFFUNCTION TERM-ARGUMENT (?TERM (?I INTEGER) ?ARG) :DOCUMENTATION \"Return the ?i-th ?arg defining this function ?term (zero-based).
Negative ?i's count from the end, for example, -1 accesses the last argument of ?term.\" :COMPUTED TRUE :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION PROPOSITION-ARGUMENT-COMPUTATION :CLOSED TRUE) (DEFFUNCTION TERM-ARGUMENTS (?TERM (?ARGS LIST)) :DOCUMENTATION \"Return all arguments defining this function ?term as a list ?args.\" :COMPUTED TRUE :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION PROPOSITION-ARGUMENTS-COMPUTATION :CLOSED TRUE) (DEFFUNCTION TERM-ARITY (?TERM (?ARITY INTEGER)) :DOCUMENTATION \"Return the number of arguments defining this function ?term.\" :COMPUTED TRUE :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION PROPOSITION-ARITY-COMPUTATION :CLOSED TRUE) (DEFRELATION CUT (?ARGUMENTS) :DOCUMENTATION \"Prolog-like CUT.  Succeeds the first time and
then fails.  Side-effect:  Locally disables query optimization.\" :AXIOMS (AND (VARIABLE-ARITY CUT) (RELATION-SPECIALIST CUT CUT-SPECIALIST))) (DEFRELATION BOUND-VARIABLES (?ARGUMENTS) :DOCUMENTATION \"True if all arguments are bound.  The `bound-variables'
predicate is used as a performance enhancer, to prevent other predicates
from backchaining excessively while searching for bindings of certain of
their arguments. Purists will shun the use of this predicate, but some rules
are inherently inefficient without the addition of some kind of control logic.
Because evaluation of the `bound-variables' predicate evaluation of
predicates being 'guarded', using this predicate has the side-effect
of locally disabling query optimization.  (See `collect-into-set' for
an example that uses `bound-variables'.\" :AXIOMS (AND (VARIABLE-ARITY BOUND-VARIABLES) (HANDLES-REVERSE-POLARITY BOUND-VARIABLES-SPECIALIST) (RELATION-SPECIALIST BOUND-VARIABLES BOUND-VARIABLES-SPECIALIST))) (DEFRELATION FORK ((?TEST PROPOSITION) (?THEN PROPOSITION) (?ELSE PROPOSITION)) :DOCUMENTATION \"Fail-based conditional.  If ?test succeeds, evaluates
?then; otherwise evaluates ?else.\" :AXIOMS (RELATION-SPECIALIST FORK FORK-SPECIALIST)) (DEFRELATION QUERY ((?PROP PROPOSITION) ?OPTIONS) :DOCUMENTATION \"Search-control relation that allows one to prove or
retrieve bindings for ?prop with modified search control ?options.  The list
of accepted ?options is currently the same as are legal for a top-level `ask'
or `retrieve' query.  The special option value :INHERIT inherits the option
value from the parent or top-level query.  The option pair :INHERIT :ALL
inherits all parent options which can then be further modified by additional
individual option specifications.  At most how many solutions will be generated
is controlled by the :HOW-MANY option (just like in the top level `retrieve').
The default is 1 which is again the same as for `retrieve' but different from
how normal subgoals behave (those behave in a lazy all solutions mode).
The reason for this is that for partial match subqueries, solutions need to be
generated eagerly, therefore, a default of generating all solutions is not
desirable.\" :VARIABLE-ARITY TRUE :RELATION-SPECIALIST QUERY-SPECIALIST) (DEFRELATION ASSERTION-QUERY ((?PROP PROPOSITION)) :DOCUMENTATION \"Query ?prop with :inference-level set to :assertion.
Equivalent to `(query ?prop :inference-level :assertion)' but more efficient.\" :RELATION-SPECIALIST LEVELED-QUERY-SPECIALIST) (DEFRELATION SHALLOW-QUERY ((?PROP PROPOSITION)) :DOCUMENTATION \"Query ?prop with :inference-level set to :shallow.
Equivalent to `(query ?prop :inference-level :shallow)' but more efficient.\" :RELATION-SPECIALIST LEVELED-QUERY-SPECIALIST) (DEFRELATION SUBSUMPTION-QUERY ((?PROP PROPOSITION)) :DOCUMENTATION \"Query ?prop with :inference-level set to :subsumption.
Equivalent to `(query ?prop :inference-level :subsumption)' but more efficient.\" :RELATION-SPECIALIST LEVELED-QUERY-SPECIALIST) (DEFRELATION BACKTRACKING-QUERY ((?PROP PROPOSITION)) :DOCUMENTATION \"Query ?prop with :inference-level set to :backtracking.
Equivalent to `(query ?prop :inference-level :backtracking)' but more efficient.\" :RELATION-SPECIALIST LEVELED-QUERY-SPECIALIST) (DEFRELATION NORMAL-QUERY ((?PROP PROPOSITION)) :DOCUMENTATION \"Query ?prop with :inference-level set to :normal.
Equivalent to `(query ?prop :inference-level :normal)' but more efficient.\" :RELATION-SPECIALIST LEVELED-QUERY-SPECIALIST) (DEFRELATION REFUTATION-QUERY ((?PROP PROPOSITION)) :DOCUMENTATION \"Query ?prop with :inference-level set to :refutation.
Equivalent to `(query ?prop :inference-level :refutation)' but more efficient.\" :RELATION-SPECIALIST LEVELED-QUERY-SPECIALIST) (DEFRELATION HIDDEN-RELATION ((?R RELATION)) :DOCUMENTATION \"Indicates that ?r is used like an internal data
structure; not for user consumption.\") (DEFFUNCTION OBSERVED-CARDINALITY-OF ((?R RELATION)) :-> (?CARD INTEGER) :DOCUMENTATION \"Used by PowerLoom to record the sizes of class
and relation extensions.  Only filled if the relation extension was
directly accessed by some query.\" :AXIOMS (HIDDEN-RELATION OBSERVED-CARDINALITY-OF)) (DEFRELATION POLYMORPHIC ((?R RELATION)) :DOCUMENTATION \"True if ?r' supports polymorphism.\") (DEFRELATION INSTANCE-OF ((?X THING) (?C COLLECTION)) :DOCUMENTATION \"True if ?x is an instance of ?c.  Can
be used to generate concept values of ?c, given an instance ?x.\" :AXIOMS (RELATION-SPECIALIST INSTANCE-OF INSTANCE-OF-SPECIALIST)) (DEFRELATION DIRECT-INSTANCE-OF ((?X THING) (?C COLLECTION)) :DOCUMENTATION \"True if ?x is a direct instance of ?c which means that ?c is a most specific type of ?x.
Type specificity is determined by chasing implies links, which means the classifier needs to be run to
get those for complex inferrable descriptions.\" :RELATION-SPECIALIST DIRECT-INSTANCE-OF-SPECIALIST) (DEFRELATION ASSERTED-INSTANCE-OF ((?X THING) (?C COLLECTION)) :DOCUMENTATION \"True if ?x has been explicitly asserted in the current module to be of type ?c.
This includes types implicitly asserted by the type checker but excludes types that were inferred
only in the current inference cache or that require subsumption reasoning.\" :RELATION-SPECIALIST ASSERTED-INSTANCE-OF-SPECIALIST) (DEFRELATION TYPE-OF ((?C COLLECTION) (?X THING)) :DOCUMENTATION \"True if ?x is a member of the concept ?c.\" :INVERSE INSTANCE-OF) (DEFRELATION SUBSET-OF ((?SUB COLLECTION) (?SUPER COLLECTION)) :DOCUMENTATION \"True if ?sub is a subset of ?super.  For performance
reasons, the `subset-of' predicate refuses to search for bindings if
both of its variables are unbound.  Implementation note: `subset-of' 
is treated specially internally to PowerLoom, and hence Powerloom does not
permit the augmentation of `subset-of' with additional inference rules.
In otherwords, `subset-of' behaves semantically like an operator instead
of a relation.\" :AXIOMS (RELATION-SPECIALIST SUBSET-OF SUBSET-OF-SPECIALIST)) (DEFRELATION MEMBER-OF ((?X THING) (?C COLLECTION)) :DOCUMENTATION \"TRUE if ?x is a member of collection ?c.  A common use
of `member-of' is for binding a variable to successive members in a list
or set (see `listof' and `setof').\" :AXIOMS (AND (RELATION-SPECIALIST MEMBER-OF MEMBER-OF-SPECIALIST) (HANDLES-REVERSE-POLARITY MEMBER-OF-SPECIALIST) (RELATION-EVALUATOR MEMBER-OF MEMBER-OF-EVALUATOR))) (DEFRELATION PORTION-OF ((?X AGGREGATE) (?Y AGGREGATE)) :PHRASE \"?x is a portion of (a piece of) ?y\" :AXIOMS ((TRANSITIVE PORTION-OF))) (DEFRELATION DOMAIN ((?R RELATION) (?D COLLECTION)) :DOCUMENTATION \"True if for any tuple `T' that satifies ?r, the first
argument of `T' necessarily belongs to the concept ?d.  `domain' exists
for convenience only and is defined in terms of `nth-domain'.  `domain'
assertions should be avoided, since they create redundant `nth-domain'
propositions (use `nth-domain' directly).\" :<<=>> (NTH-DOMAIN ?R 0 ?D) :=>> (=>> (HOLDS ?R ?I ?V) (HOLDS ?D ?I))) (DEFRELATION RANGE ((?R RELATION) (?RNG COLLECTION)) :DOCUMENTATION \"True if for any tuple 'T' that satifies ?r, the last
argument of 'T' necessarily belongs to the concept ?rng.  `range' exists
for convenience only and is defined in terms of `nth-domain'.  `range'
assertions should be avoided, since they create redundant `nth-domain'
propositions (use `nth-domain' directly).\" :<<= (AND (> (ARITY ?R) 1) (NTH-DOMAIN ?R (- (ARITY ?R) 1) ?RNG)) :=>> (NTH-DOMAIN ?R (- (ARITY ?R) 1) ?RNG) :=>> (=>> (HOLDS ?R ?I ?V) (HOLDS ?RNG ?V))) (DEFRELATION NTH-DOMAIN ((?R RELATION) (?I INTEGER) (?D COLLECTION)) :DOCUMENTATION \"True if the nth value for a tuple T satisfying
?r must belong to the concept ?d.  Argument counting starts at zero.\" :AXIOMS (<<= (NTH-DOMAIN ?R 0 ?R) (CONCEPT ?R))) (DEFRELATION CLOSED ((?C COLLECTION)) :PHRASE \"?c is closed\" :DOCUMENTATION \"The collection ?c is closed if all of its members are known.
Asserting that a relation is closed makes certain computations easier.
For example, suppose that the relation `happy' is closed,
implying that all things that are happy will be asserted as such.
To prove `(not (happy Fred))', PowerLoom can use a negation-as-failure 
proof strategy which returns TRUE if `Fred' cannot be proved to be happy.
Also, if the relation `children' is closed, then a value for the expression
`(range-max-cardinality children Fred)' can be inferred merely by
counting the number of fillers of the `children' role on `Fred'.\" :RELATION-SPECIALIST CLOSED-SPECIALIST :AXIOMS (HANDLES-REVERSE-POLARITY CLOSED-SPECIALIST)) (DEFRELATION EMPTY ((?C COLLECTION)) :DOCUMENTATION \"The collection ?c is empty if it has no members.  Note
that for collections possessing open-world semantics, (e.g., most concepts)
the fact that the collection has no known members does not necessarily
imply that it is empty.\" :AXIOMS (AND (RELATION-SPECIALIST EMPTY EMPTY-SPECIALIST) (COMPUTED EMPTY))) (DEFRELATION SINGLE-VALUED ((?C RELATION)) :DOCUMENTATION \"The relation ?c is single-valued if the value of its
last argument is a function of all other arguments.  All functions
are single-valued (see `function').\" :AXIOMS (AND (HANDLES-REVERSE-POLARITY SINGLE-VALUED-SPECIALIST) (RELATION-SPECIALIST SINGLE-VALUED SINGLE-VALUED-SPECIALIST))) (DEFRELATION COMPUTED ((?C RELATION)) :DOCUMENTATION \"?c is computed if it can be evaluated only if all of
its input arguments are bound (or all of them if it is a relation).
Considered by the query optimizer when looking for generators.\") (DEFFUNCTION THE-ROLESET ((?R RELATION) ?I) :-> (?RS SET) :DOCUMENTATION \"Function that defines a mapping from a relation
and instance to the skolem that (intensionally) denotes the
corresponding set of role fillers.\") (DEFFUNCTION FILLERS ((?R RELATION) ?I) :-> (?MEMBERS SET) :DOCUMENTATION \"Given a relation ?r and instance ?i, returns
a set of known fillers of ?r applied to ?i.  IMPORTANT: this also collects
intensional fillers such as skolems that might be identical extensionally.\" :<<= (AND (BOUND-VARIABLES ?R ?I) (COLLECT-INTO-SET (SETOFALL ?V (HOLDS ?R ?I ?V)) ?MEMBERS)) :AXIOMS (COMPUTED FILLERS)) (DEFFUNCTION FILLER ((?R RELATION) ?I) :-> ?V :DOCUMENTATION \"Special-purpose version of `fillers' which accesses the single
filler ?v for the single-valued relation ?r applied to ?i.  This is primarily useful
to enable a functional notation to access the value of a single-valued relation that
is not a function.\" :<<= (AND (BOUND-VARIABLES ?R ?I) (SINGLE-VALUED ?R) (HOLDS ?R ?I ?V)) :COMPUTED TRUE) (DEFFUNCTION CARDINALITY ((?C SET)) :-> (?CARD INTEGER) :DOCUMENTATION \"Function that returns the cardinality of a set.\" :<<= (AND (CLOSED ?C) (COUNT-MEMBERS ?C ?CARD))) (DEFCONCEPT FRAME-PREDICATE ((?C RELATION)) :DOCUMENTATION \"A frame predicate is a second-order relation that
is used to describe constraints on the set of fillers for a binary
relation applied to an instance.  Examples of frame predicates are
`range-cardinality', `range-type', and `numeric-inclusive-minimum'.
Frame predicates are typically used to capture the kinds of relations
manipulated by description logics such as USC/ISI's Loom and W3C's OWL.\") (DEFRELATION RANGE-TYPE ((?R RELATION) ?I (?TYPE COLLECTION)) :DOCUMENTATION \"Relation that specifies a type/range of the relation ?r applied to ?i.
Multiple range types may be asserted for a single pair <?r,?i>.  Technically,
a retrieval of types for a given pair should include all supertypes
(superconcepts) of any type that is produced, but for utility's sake,
only asserted or directly inferrable types are returned.\" :AXIOMS (=>> (AND (RANGE-TYPE ?R ?I ?TYPE) (FAIL (NTH-DOMAIN ?R 1 ?TYPE))) (FORALL ?V (=>> (HOLDS ?R ?I ?V) (HOLDS ?TYPE ?V)))) :<<=>> (SUBSET-OF (THE-ROLESET ?R ?I) ?TYPE) :<<= (AND (BOUND-VARIABLES ?R ?I ?TYPE) (FORK (AND (SINGLE-VALUED ?R) (EXISTS ?V (HOLDS ?R ?I ?V))) (EXISTS ?V (AND (HOLDS ?R ?I ?V) (HOLDS ?TYPE ?V))) (OR (AND (OR (CLOSED ?R) (CLOSED (THE-ROLESET ?R ?I))) (FORALL ?V (=> (HOLDS ?R ?I ?V) (HOLDS ?TYPE ?V)))) (EXISTS (?SUPERR ?SUPERVT) (AND (SUBSET-OF ?R ?SUPERR) (RANGE-TYPE ?SUPERR ?I ?SUPERVT) (SUBSET-OF ?SUPERVT ?TYPE)))))) :COMPUTED TRUE :FRAME-PREDICATE TRUE :RELATION-SPECIALIST RANGE-TYPE-SPECIALIST) (DEFRELATION RANGE-CARDINALITY-LOWER-BOUND ((?R RELATION) ?I (?LB INTEGER)) :DOCUMENTATION \"Relation that specifies a lower bound on the cardinality 
of the set of fillers of the relation ?r applied to ?i.  The difference
between `range-cardinality-lower-bound' and `range-min-cardinality' is
subtle but significant.   Suppose we state that nine is a lower bound
on the number of planets in the solar system, and then ask if eight is
(also) a lower bound:
	 
   (assert (range-cardinality-lower-bound hasPlanets SolarSystem 9))
   (ask (range-cardinality-lower-bound hasPlanets SolarSystem 8))  ==> TRUE
	
PowerLoom will return TRUE.  However if we ask if the minimum cardinality
of the solar system's planets is eight, we get back UNKNOWN
	 
   (ask (range-min-cardinality hasPlanets SolarSystem 8)) ==> UNKNOWN
	
because eight is not the tightest lower bound.\" :AXIOMS (<<= (RANGE-CARDINALITY-LOWER-BOUND ?R ?I ?LB) (AND (BOUND-VARIABLES ?R ?I ?LB) (=< ?LB (RANGE-MIN-CARDINALITY ?R ?I)))) :AXIOMS (=>> (RANGE-CARDINALITY-LOWER-BOUND ?R ?I ?LB) (>= (CARDINALITY (THE-ROLESET ?R ?I)) ?LB)) :AXIOMS (AND (FRAME-PREDICATE RANGE-CARDINALITY-LOWER-BOUND) (RELATION-SPECIALIST RANGE-CARDINALITY-LOWER-BOUND RANGE-MIN-CARDINALITY-SPECIALIST) (HANDLES-REVERSE-POLARITY RANGE-MIN-CARDINALITY-SPECIALIST))) (DEFRELATION RANGE-CARDINALITY-UPPER-BOUND ((?R RELATION) ?I (?UB INTEGER)) :DOCUMENTATION \"Relation that specifies an upper bound on the cardinality 
of the set of fillers of the relation ?r applied to ?i. (see the discussion
for `range-cardinality-lower-bound').\" :AXIOMS (<<= (RANGE-CARDINALITY-UPPER-BOUND ?R ?I ?UB) (AND (BOUND-VARIABLES ?R ?I ?UB) (>= ?UB (RANGE-MAX-CARDINALITY ?R ?I)))) :AXIOMS (=>> (RANGE-CARDINALITY-UPPER-BOUND ?R ?I ?UB) (=< (CARDINALITY (THE-ROLESET ?R ?I)) ?UB)) :AXIOMS (AND (FRAME-PREDICATE RANGE-CARDINALITY-UPPER-BOUND) (RELATION-SPECIALIST RANGE-CARDINALITY-UPPER-BOUND RANGE-MAX-CARDINALITY-SPECIALIST) (HANDLES-REVERSE-POLARITY RANGE-MAX-CARDINALITY-SPECIALIST))) (DEFFUNCTION RANGE-CARDINALITY ((?R RELATION) ?I) :-> (?CARD INTEGER) :DOCUMENTATION \"Function that returns the cardinality of the set
of fillers of the relation ?r applied to ?i.  The cardinality function
returns a value only when the relations `range-min-cardinality' and
`range-max-cardinality' compute identical values, i.e., when the
best lower and upper bounds on the cardinality are equal.  Each of
these bounding functions employs a variety of rules to try and
compute a tight bound.\" :<=> (AND (RANGE-MIN-CARDINALITY ?R ?I ?CARD) (RANGE-MAX-CARDINALITY ?R ?I ?CARD)) :AXIOMS (=>> (RANGE-CARDINALITY ?R ?I ?CARD) (= (CARDINALITY (THE-ROLESET ?R ?I)) ?CARD)) :AXIOMS (AND (FRAME-PREDICATE RANGE-CARDINALITY) (COMPUTED RANGE-CARDINALITY))) (DEFFUNCTION RANGE-MIN-CARDINALITY ((?R RELATION) ?I) :-> (?MINCARD INTEGER) :DOCUMENTATION \"Returns the strictest computable lower bound on the
cardinality of the set of fillers of the relation ?r applied to ?i.
(see the discussion for `range-cardinality-lower-bound').\" :<<= (OR (AND (SINGLE-VALUED ?R) (EXISTS ?V (HOLDS ?R ?I ?V)) (= ?MINCARD 1)) (MAXIMUM-VALUE (COLLECT-INTO-SET (SETOFALL ?M (OR (>= (CARDINALITY (THE-ROLESET ?R ?I)) ?M) (= ?M 0) (LENGTH (FILLERS ?R ?I) ?M) (EXISTS ?SUBR (AND (SUBSET-OF ?SUBR ?R) (>= (CARDINALITY (THE-ROLESET ?SUBR ?I)) ?M)))))) ?MINCARD)) :AXIOMS (AND (FRAME-PREDICATE RANGE-MIN-CARDINALITY))) (DEFFUNCTION RANGE-MAX-CARDINALITY ((?R RELATION) ?I) :-> (?MAXCARD INTEGER) :DOCUMENTATION \"Returns the strictest computable upper bound on the
cardinality of the set of fillers of the relation ?r applied to ?i.
(see the discussion for `range-cardinality-lower-bound').\" :<<= (OR (AND (SINGLE-VALUED ?R) (EXISTS ?V (HOLDS ?R ?I ?V)) (= ?MAXCARD 1)) (MINIMUM-VALUE (COLLECT-INTO-SET (SETOFALL ?M (OR (=< (CARDINALITY (THE-ROLESET ?R ?I)) ?M) (AND (SINGLE-VALUED ?R) (= ?M 1)) (AND (EMPTY (THE-ROLESET ?R ?I)) (= ?M 0)) (AND (CLOSED ?R) (RANGE-MIN-CARDINALITY ?R ?I ?M)) (EXISTS ?SUPERR (AND (SUBSET-OF ?R ?SUPERR) (=< (CARDINALITY (THE-ROLESET ?SUPERR ?I)) ?M)))))) ?MAXCARD)) :AXIOMS (AND (FRAME-PREDICATE RANGE-MAX-CARDINALITY) (=> (EXISTS (?MIN) (AND (RANGE-MIN-CARDINALITY ?R ?I ?MIN) (> ?MIN ?MAX))) (NOT (RANGE-MAX-CARDINALITY ?R ?I ?MAX))))) (DEFRELATION QUALIFIED-RANGE-CARDINALITY-LOWER-BOUND ((?R RELATION) ?I (?Q COLLECTION) (?LB INTEGER)) :DOCUMENTATION \"Lower bound on range cardinality for qualified cardinality restrictions.  Like `range-cardinality-lower-bound'.  NOT IMPLEMENTED YET!\") (DEFRELATION QUALIFIED-RANGE-CARDINALITY-UPPER-BOUND ((?R RELATION) ?I (?Q COLLECTION) (?UB INTEGER)) :DOCUMENTATION \"Upper bound on range cardinality for qualified cardinality restrictions.  Like `range-cardinality-upper-bound'.  NOT IMPLEMENTED YET!\") (DEFFUNCTION QUALIFIED-RANGE-MIN-CARDINALITY ((?R RELATION) ?I (?Q COLLECTION)) :-> (?CARD INTEGER) :DOCUMENTATION \"Function that returns the minimum cardinality of the set of
fillers of type ?q of the relation ?r applied to ?i.  NOT YET IMPLEMENTED.\" :AXIOMS (AND (FRAME-PREDICATE QUALIFIED-RANGE-MIN-CARDINALITY) (COMPUTED QUALIFIED-RANGE-MIN-CARDINALITY))) (DEFFUNCTION QUALIFIED-RANGE-MAX-CARDINALITY ((?R RELATION) ?I (?Q COLLECTION)) :-> (?CARD INTEGER) :DOCUMENTATION \"Function that returns the maximum cardinality of the set of
fillers of type ?q of the relation ?r applied to ?i.  NOT YET IMPLEMENTED.\" :AXIOMS (AND (FRAME-PREDICATE QUALIFIED-RANGE-MAX-CARDINALITY) (COMPUTED QUALIFIED-RANGE-MAX-CARDINALITY))) (DEFFUNCTION QUALIFIED-RANGE-CARDINALITY ((?R RELATION) ?I (?Q COLLECTION)) :-> (?CARD INTEGER) :DOCUMENTATION \"Function that returns the cardinality of the set of
fillers of type ?q of the relation ?r applied to ?i.  The cardinality function
returns a value only when the relations `qualified-range-min-cardinality' and
`qualified-range-max-cardinality' compute identical values, i.e., when the
best lower and upper bounds on the cardinality are equal.  Each of
these bounding functions employs a variety of rules to try and
compute a tight bound.  NOT YET IMPLEMENTED.\" :AXIOMS (AND (FRAME-PREDICATE QUALIFIED-RANGE-CARDINALITY) (COMPUTED QUALIFIED-RANGE-CARDINALITY))) (DEFFUNCTION NUMERIC-INTERVAL ((?X NUMERIC-SET)) :-> (?INTERVAL INTEGER-INTERVAL) :DOCUMENTATION \"Function that returns an interval representing
the range of allowable numeric values for its members.\" :=>> (SCALAR-INTERVAL ?INTERVAL)) (DEFFUNCTION INTERVAL-CACHE-OF (?X) :-> (?B INTERVAL-CACHE) :DOCUMENTATION \"Binds an instance ?x of type NUMBER or QUANTITY to a 
structure that records its tightest lower and upper bounds.\" :AXIOMS (HIDDEN-RELATION INTERVAL-CACHE-OF)) (DEFRELATION NUMERIC-MINIMUM ((?R RELATION) ?I (?N NUMBER)) :DOCUMENTATION \"Relation that specifies a lower bound '?n' on any numeric
value that can belong to the set of fillers of the relation ?r applied to ?i.\" :<<=>> (>= (INTERVAL-LOWER-BOUND (NUMERIC-INTERVAL (THE-ROLESET ?R ?I))) ?N) :AXIOMS (FRAME-PREDICATE NUMERIC-MINIMUM)) (DEFRELATION NUMERIC-MAXIMUM ((?R RELATION) ?I (?N NUMBER)) :DOCUMENTATION \"Relation that specifies an upper bound '?n' on any numeric
value that can belong to the set of fillers of the relation ?r applied to ?i.\" :<<=>> (=< (INTERVAL-UPPER-BOUND (NUMERIC-INTERVAL (THE-ROLESET ?R ?I))) ?N) :AXIOMS (FRAME-PREDICATE NUMERIC-MAXIMUM)) (DEFRELATION DIRECT-SUBRELATION ((?R RELATION) (?SUB RELATION)) :DOCUMENTATION \"True iff ?sub is a direct subrelation of ?r; written
in set notation, ?sub < ?r, and there is no ?s such that ?sub < ?s < ?r.
This relation will generate bindings for at most one unbound argument.\" :AXIOMS (RELATION-SPECIALIST DIRECT-SUBRELATION RELATION-HIERARCHY-SPECIALIST)) (DEFRELATION DIRECT-SUPERRELATION ((?R RELATION) (?SUPER RELATION)) :DOCUMENTATION \"True iff ?super is a direct superrelation of ?r;
in set notation, ?super > ?r, and there is no ?s such that ?super > ?s > ?r.
This relation will generate bindings for at most one unbound argument.\" :AXIOMS (AND (INVERSE DIRECT-SUPERRELATION DIRECT-SUBRELATION) (RELATION-SPECIALIST DIRECT-SUPERRELATION RELATION-HIERARCHY-SPECIALIST))) (DEFRELATION SUBRELATION ((?R RELATION) (?SUB RELATION)) :DOCUMENTATION \"True iff ?sub is a subrelation of ?r; written in set
notation, ?sub =< ?r.  This relation will generate bindings for at most
one unbound argument.\" :AXIOMS (RELATION-SPECIALIST SUBRELATION RELATION-HIERARCHY-SPECIALIST)) (DEFRELATION SUPERRELATION ((?R RELATION) (?SUPER RELATION)) :DOCUMENTATION \"True iff ?super is a superrelation of ?r; written in set
notation, ?super >= ?r.  This relation will generate bindings for at most
one unbound argument.\" :AXIOMS (AND (INVERSE SUPERRELATION SUBRELATION) (RELATION-SPECIALIST SUPERRELATION RELATION-HIERARCHY-SPECIALIST))) (DEFRELATION PROPER-SUBRELATION ((?R RELATION) (?SUB RELATION)) :DOCUMENTATION \"True iff ?sub is a proper subrelation of ?r; written in
set notation, ?sub < ?r.  This relation will generate bindings for at most
one unbound argument.\" :AXIOMS (RELATION-SPECIALIST PROPER-SUBRELATION RELATION-HIERARCHY-SPECIALIST)) (DEFRELATION PROPER-SUPERRELATION ((?R RELATION) (?SUPER RELATION)) :DOCUMENTATION \"True iff ?super is a proper superrelation of ?r; written in
set notation, ?super > ?r.  This relation will generate bindings for at most
one unbound argument.\" :AXIOMS (AND (INVERSE PROPER-SUPERRELATION PROPER-SUBRELATION) (RELATION-SPECIALIST PROPER-SUPERRELATION RELATION-HIERARCHY-SPECIALIST))) (DEFRELATION EQUIVALENT-RELATION ((?R RELATION) (?EQUIV RELATION)) :DOCUMENTATION \"True if ?r is equivalent to ?equiv; written in set notation,
?r = ?equiv.  This relation will generate bindings for at most one unbound
argument.\" :AXIOMS (RELATION-SPECIALIST EQUIVALENT-RELATION RELATION-HIERARCHY-SPECIALIST)) (DEFFUNCTION UNION-OF ((?S1 COLLECTION) (?S2 COLLECTION)) :-> (?UNION SET) :DOCUMENTATION \"True if the union of the collections ?s1 and ?s2 equals ?union.\") (DEFFUNCTION + ((?X NUMBER) (?Y NUMBER)) :-> (?Z NUMBER) :DOCUMENTATION \"Function that adds two numbers.\") (ASSERT (AND (COMPUTED +) (RELATION-CONSTRAINT + PLUS-CONSTRAINT) (RELATION-SPECIALIST + CONSTRAINT-SPECIALIST))) (DEFFUNCTION - ((?X NUMBER) (?Y NUMBER)) :-> (?Z NUMBER) :DOCUMENTATION \"Function that subtracts two numbers.\") (ASSERT (AND (COMPUTED -) (RELATION-CONSTRAINT - MINUS-CONSTRAINT) (RELATION-SPECIALIST - CONSTRAINT-SPECIALIST))) (DEFFUNCTION * ((?X NUMBER) (?Y NUMBER)) :-> (?Z NUMBER) :DOCUMENTATION \"Function that multiplies two numbers.\") (ASSERT (AND (COMPUTED *) (RELATION-CONSTRAINT * TIMES-CONSTRAINT) (RELATION-SPECIALIST * CONSTRAINT-SPECIALIST))) (DEFFUNCTION / ((?X NUMBER) (?Y NUMBER)) :-> (?Z NUMBER) :DOCUMENTATION \"Function that divides two numbers.\") (ASSERT (AND (COMPUTED /) (RELATION-CONSTRAINT / DIVIDE-CONSTRAINT) (RELATION-SPECIALIST / CONSTRAINT-SPECIALIST))) (DEFFUNCTION SQRT ((?X NUMBER)) :-> (?Y NUMBER) :DOCUMENTATION \"Function that returns the positive square root:
?y = sqrt(?x).  For positive and negative roots see relation SQUARE-ROOT\" :AXIOMS (AND (COMPUTED SQRT) (RELATION-CONSTRAINT SQRT SQRT-CONSTRAINT) (RELATION-SPECIALIST SQRT CONSTRAINT-SPECIALIST))) (DEFRELATION SQUARE-ROOT ((?X NUMBER) (?Y NUMBER)) :DOCUMENTATION \"Relation that returns the positive and negative square roots:
?y = sqrt(?x).  For positive roots only see function SQRT.\" :AXIOMS (AND (COMPUTED SQUARE-ROOT) (RELATION-SPECIALIST SQUARE-ROOT SQUARE-ROOT-SPECIALIST))) (DEFFUNCTION ABSOLUTE-VALUE ((?X NUMBER) (?Y NUMBER)) :DOCUMENTATION \"Relation that computes ?y = abs(?x).  If ?x is unbound,
then ?x will get both positive and negative values of the 
magnitude of ?y.\" :AXIOMS (AND (COMPUTED ABSOLUTE-VALUE) (RELATION-SPECIALIST ABSOLUTE-VALUE ABSOLUTE-VALUE-SPECIALIST))) (DEFFUNCTION NEGATE ((?X NUMBER) (?Y NUMBER)) :DOCUMENTATION \"Relation that computes ?y = - ?x.\" :AXIOMS (AND (COMPUTED NEGATE) (RELATION-CONSTRAINT NEGATE NEGATE-CONSTRAINT) (RELATION-SPECIALIST NEGATE CONSTRAINT-SPECIALIST))) (DEFFUNCTION FLOOR ((?X NUMBER) (?Y INTEGER)) :DOCUMENTATION \"Compute the biggest integer ?y <= ?x.\" :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION FLOOR-COMPUTATION) (DEFFUNCTION CEILING ((?X NUMBER) (?Y INTEGER)) :DOCUMENTATION \"Compute the smallest integer ?y >= ?x.\" :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION CEILING-COMPUTATION) (DEFFUNCTION LOG ((?X NUMBER) (?LOG NUMBER)) :DOCUMENTATION \"Compute the natural logarithm (base e) of ?x.\" :RELATION-CONSTRAINT LOG-CONSTRAINT :RELATION-SPECIALIST CONSTRAINT-SPECIALIST) (DEFFUNCTION LOG10 ((?X NUMBER) (?LOG NUMBER)) :DOCUMENTATION \"Compute the base-10 logarithm of ?x.\" :RELATION-CONSTRAINT LOG10-CONSTRAINT :RELATION-SPECIALIST CONSTRAINT-SPECIALIST) (DEFFUNCTION EXP ((?X NUMBER) (?Y NUMBER)) :DOCUMENTATION \"Compute ?y = e to the power ?x.\" :RELATION-CONSTRAINT EXP-CONSTRAINT :RELATION-SPECIALIST CONSTRAINT-SPECIALIST) (DEFFUNCTION EXPT ((?X NUMBER) (?N NUMBER) (?Y NUMBER)) :DOCUMENTATION \"Compute ?y = ?x to the power ?n.\" :RELATION-COMPUTATION EXPT-COMPUTATION) (DEFOBJECT (KAPPA (?X ?Y) (= ?X ?Y)) :DOCUMENTATION \"Represents the extensional identity between ?x and ?y.
Due to PowerLoom's unique names assumption, at least one of those has to
be an intensional skolem object.\" :SYNONYM EQUIVALENT :SYNONYM =) (DEFFUNCTION EQUIVALENT-TERMS (?TERM (?EQUIVS LIST)) :DOCUMENTATION \"Enumerate all currently known equivalents to ?term (including itself)
as a sorted list of ?equivs.  This will not try to do any new equality inference, it simply
collects all equivalents that were directly or indirectly equated to ?term via explicit
assertion or forward inference.  ALERT: this is very tricky and for very special circumstances
only: once two or more terms have been equated, they become more or less indistinguishable
and PowerLoom queries will always produce the current representative only.  For example,
enumerating members of ?equivs will produce only a single representative member, however,
the list will contain all equivalent terms and can still have a length greater than 1.
This is also the reason why we materialize a list instead of generating them one-by-one.
The list of equivalents can then be enumerated programmatically via PLI, for example, or listed
across contexts via `ist' as long as the equalities are not visible in the enumerating context.\" :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION EQUIVALENT-TERMS-COMPUTATION :COMPUTED TRUE) (ASSERT (HANDLES-REVERSE-POLARITY INEQUALITY-SPECIALIST)) (DEFRELATION INEQUALITY (?X ?Y) :DOCUMENTATION \"Abstract superrelation of inequality relations.\" :<<= (=< ?X ?Y) :<<= (>= ?X ?Y) :AXIOMS (ABSTRACT INEQUALITY)) (DEFRELATION < (?X ?Y) :DOCUMENTATION \"True if ?x < ?y.\" :<<= (EXISTS ?Z (AND (< ?X ?Z) (=< ?Z ?Y))) :<<= (EXISTS ?Z (AND (=< ?X ?Z) (< ?Z ?Y)))) (ASSERT (AND (COMPUTED <) (RELATION-SPECIALIST < INEQUALITY-SPECIALIST) (RELATION-EVALUATOR < INEQUALITY-EVALUATOR))) (DEFRELATION =< (?X ?Y) :DOCUMENTATION \"True if ?x <= ?y.\" :<<= (EXISTS ?Z (AND (=< ?X ?Z) (=< ?Z ?Y))) :<<= (< ?X ?Y)) (ASSERT (AND (COMPUTED =<) (RELATION-SPECIALIST =< INEQUALITY-SPECIALIST) (RELATION-EVALUATOR =< INEQUALITY-EVALUATOR))) (DEFRELATION > (?X ?Y) :DOCUMENTATION \"True if ?x > ?y.\" :<<=>> (< ?Y ?X)) (ASSERT (AND (COMPUTED >) (RELATION-SPECIALIST > INEQUALITY-SPECIALIST) (RELATION-EVALUATOR > INEQUALITY-EVALUATOR))) (DEFRELATION >= (?X ?Y) :DOCUMENTATION \"True if ?x >= ?y.\" :<<=>> (=< ?Y ?X) :<<= (> ?X ?Y)) (ASSERT (AND (COMPUTED >=) (RELATION-SPECIALIST >= INEQUALITY-SPECIALIST) (RELATION-EVALUATOR >= INEQUALITY-EVALUATOR))) (DEFFUNCTION COLLECT-INTO-SET ((?C COLLECTION)) :-> (?L SET) :DOCUMENTATION \"Infer as many members of ?c as possible and
collect them into a set ?l.  For example, here is a rule
used to compute bindings for the `fillers' predicate:
	 
  (<= (fillers ?r ?i ?members)
      (and (bound-variables ?r ?i)
           (collect-into-set (setofall ?v (holds ?r ?i ?v)) ?members)))
	
When `?r' and `?i' are bound, the term `(setofall ?v (holds ?r ?i ?v))'
evaluates to a unary relation satisfied for each filler of the relation
in `?r' applied to the instance in `?i'.  `collect-into-set' causes
the extension of this (dynamically-defined) unary relation to be
computed.  Note the use of `bound-variables' to screen out unbound
variables before they are passed to the `setofall' term.\" :RELATION-SPECIALIST COLLECT-MEMBERS-SPECIALIST) (DEFFUNCTION COLLECT-INTO-LIST ((?C COLLECTION)) :-> (?L LIST) :DOCUMENTATION \"Infer as many members of ?c as possible and
collect them into a list ?l.  This is similar to `collect-into-set'
but collects members in the order they are encountered.  If a member
is derived multiple times, all occurrences are kept.  This is
useful, for example, to collect and then sum up number-valued
attributes of objects.\" :RELATION-SPECIALIST COLLECT-MEMBERS-SPECIALIST) (DEFFUNCTION COLLECT-INTO-ORDERED-SET ((?C COLLECTION)) :-> (?L LIST) :DOCUMENTATION \"This is similar to `collect-into-list', but if a
member is derived multiple times, only the first occurrence is kept
- hence, the name, even though ordered sets are represented as lists.\" :RELATION-SPECIALIST COLLECT-MEMBERS-SPECIALIST) (DEFFUNCTION COUNT-MEMBERS ((?C COLLECTION)) :-> (?CARD INTEGER) :DOCUMENTATION \"This is similar to `collect-into-set', but instead of creating
a set term containing all members, it returns the number of unique members found.
This will work for KAPPA's as well and, thus, can be used to count n-ary relations.\" :RELATION-SPECIALIST COLLECT-MEMBERS-SPECIALIST) (DEFFUNCTION COLLECT-INTO-ASCENDING-SET ((?C COLLECTION) (?SORTBY RELATION) (?ORDEREDSET LIST)) :DOCUMENTATION \"Collect elements of ?c into an ascending ?orderedSet where the position of each
element is determined by the value computed for it by the ?sortBy relation.  Ordering is done via
sorting (as opposed to using a comparison relation) similar to the :sort-by option to the `retrieve'
command.  If ?sortBy is not single-valued, the position of an element is determined by its largest
?sortBy value.  Note that, similar to other `collect-into-...' functions, ?c can be a named concept,
a `setofall' or an enumerated collection, and ?sortBy can be a named relation or a `kappa'.\" :<<= (COLLECT-INTO-ORDERED-SET (SETOFALL (?ELEMENT) (EXISTS ?VALUE (QUERY (AND (FAIL (BOUND-VARIABLES ?VALUE)) (MEMBER-OF ?ELEMENT ?C) (HOLDS ?SORTBY ?ELEMENT ?VALUE)) :HOW-MANY :ALL :SORT-BY :VALUES-ASCENDING :MAXIMUM-DEPTH :INHERIT))) ?ORDEREDSET) :COMPUTED TRUE) (DEFFUNCTION COLLECT-INTO-DESCENDING-SET ((?C COLLECTION) (?SORTBY RELATION) (?ORDEREDSET LIST)) :DOCUMENTATION \"Collect elements of ?c into a descending ?orderedSet where the position of each
element is determined by the value computed for it by the ?sortBy relation.  Ordering is done via
sorting (as opposed to using a comparison relation) similar to the :sort-by option to the `retrieve'
command.  If ?sortBy is not single-valued, the position of an element is determined by its largest
?sortBy value.  Note that, similar to other `collect-into-...' functions, ?c can be a named concept,
a `setofall' or an enumerated collection, and ?sortBy can be a named relation or a `kappa'.\" :<<= (COLLECT-INTO-ORDERED-SET (SETOFALL (?ELEMENT) (EXISTS ?VALUE (QUERY (AND (FAIL (BOUND-VARIABLES ?VALUE)) (MEMBER-OF ?ELEMENT ?C) (HOLDS ?SORTBY ?ELEMENT ?VALUE)) :HOW-MANY :ALL :SORT-BY :VALUES-DESCENDING :MAXIMUM-DEPTH :INHERIT))) ?ORDEREDSET) :COMPUTED TRUE) (DEFRELATION MINIMUM-ELEMENT ((?C COLLECTION) (?SORTBY RELATION) ?ELEMENT) :DOCUMENTATION \"Find those ?element(s) of ?c with the minimum ?sortBy value, for example,
`(retrieve (minimum-element relation arity ?x))' (see also `collect-into-ascending-set').\" :<<= (EXISTS (?ORDEREDSET ?FIRSTELEMENT ?MINVALUE) (AND (COLLECT-INTO-ASCENDING-SET ?C ?SORTBY ?ORDEREDSET) (NTH-ELEMENT ?ORDEREDSET 0 ?FIRSTELEMENT) (FORK (SINGLE-VALUED ?SORTBY) (HOLDS ?SORTBY ?FIRSTELEMENT ?MINVALUE) (AND (QUERY (HOLDS ?SORTBY ?FIRSTELEMENT ?MINVALUE) :HOW-MANY :ALL :SORT-BY :VALUES-ASCENDING :MAXIMUM-DEPTH :INHERIT) (CUT))) (MEMBER-OF ?ELEMENT ?ORDEREDSET) (HOLDS ?SORTBY ?ELEMENT ?MINVALUE))) :COMPUTED TRUE) (DEFRELATION MAXIMUM-ELEMENT ((?C COLLECTION) (?SORTBY RELATION) ?ELEMENT) :DOCUMENTATION \"Find those ?element(s) of ?c with the maximum ?sortBy value, for example,
`(retrieve (maximum-element relation arity ?x))' (see also `collect-into-descending-set').\" :<<= (EXISTS (?ORDEREDSET ?FIRSTELEMENT ?MAXVALUE) (AND (COLLECT-INTO-DESCENDING-SET ?C ?SORTBY ?ORDEREDSET) (NTH-ELEMENT ?ORDEREDSET 0 ?FIRSTELEMENT) (FORK (SINGLE-VALUED ?SORTBY) (HOLDS ?SORTBY ?FIRSTELEMENT ?MAXVALUE) (AND (QUERY (HOLDS ?SORTBY ?FIRSTELEMENT ?MAXVALUE) :HOW-MANY :ALL :SORT-BY :VALUES-DESCENDING :MAXIMUM-DEPTH :INHERIT) (CUT))) (MEMBER-OF ?ELEMENT ?ORDEREDSET) (HOLDS ?SORTBY ?ELEMENT ?MAXVALUE))) :COMPUTED TRUE) (DEFFUNCTION NTH-ELEMENT ((?L COLLECTION) (?N INTEGER) (?E THING)) :DOCUMENTATION \"Return the ?n-th element ?e of ?l (zero-based).
Count from end of the list if ?n is negative.  If ?n is unbound
and ?e is bound, this computes all positions of ?e.  If both are
unbound, collection elements and their respective positions will
be enumerated.\" :RELATION-SPECIALIST NTH-ELEMENT-SPECIALIST :CLOSED TRUE) (DEFFUNCTION FIRST-ELEMENT ((?L COLLECTION) (?E THING)) :DOCUMENTATION \"Return the first element ?e of ?l.\" :COMPUTED TRUE :<<=>> (NTH-ELEMENT ?L 0 ?E) :CLOSED TRUE) (DEFFUNCTION SECOND-ELEMENT ((?L COLLECTION) (?E THING)) :DOCUMENTATION \"Return the second element ?e of ?l.\" :COMPUTED TRUE :<<=>> (NTH-ELEMENT ?L 1 ?E) :CLOSED TRUE) (DEFFUNCTION THIRD-ELEMENT ((?L COLLECTION) (?E THING)) :DOCUMENTATION \"Return the third element ?e of ?l.\" :COMPUTED TRUE :<<=>> (NTH-ELEMENT ?L 2 ?E) :CLOSED TRUE) (DEFFUNCTION FOURTH-ELEMENT ((?L COLLECTION) (?E THING)) :DOCUMENTATION \"Return the fourth element ?e of ?l.\" :COMPUTED TRUE :<<=>> (NTH-ELEMENT ?L 3 ?E) :CLOSED TRUE) (DEFFUNCTION FIFTH-ELEMENT ((?L COLLECTION) (?E THING)) :DOCUMENTATION \"Return the fifth element ?e of ?l.\" :COMPUTED TRUE :<<=>> (NTH-ELEMENT ?L 4 ?E) :CLOSED TRUE) (DEFFUNCTION NTH-HEAD ((?L LIST) (?N INTEGER) (?H LIST)) :DOCUMENTATION \"Return the ?n head elements ?h of ?l.
Count from end of the list if ?n is negative.\" :COMPUTED TRUE :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION NTH-HEAD-COMPUTATION :CLOSED TRUE) (DEFFUNCTION NTH-REST ((?L LIST) (?N INTEGER) (?R LIST)) :DOCUMENTATION \"Return the ?n-th rest ?r of ?l (zero-based).
Count from end of the list if ?n is negative.\" :COMPUTED TRUE :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION NTH-REST-COMPUTATION :CLOSED TRUE) (DEFFUNCTION INSERT-ELEMENT ((?L LIST) (?N INTEGER) (?E THING) (?R LIST)) :DOCUMENTATION \"Add ?e at position ?n (zero-based) to ?l to construct ?r
 (shifts the remaining elements right).  Count from end of the list and shift
left if ?n is  negative such that -1 inserts at the end of the list, -2 second
to last, etc.\" :COMPUTED TRUE :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION INSERT-ELEMENT-COMPUTATION :CLOSED TRUE) (DEFFUNCTION LIST-CONCATENATE ((?X COLLECTION) (?Y COLLECTION) (?R LIST)) :DOCUMENTATION \"Concatenate lists ?x and ?y into ?r.  If ?x and/or ?y
are not lists but sets or more general collections, the order of the
elements in the result list ?r will be arbitrary.\" :<<= (COLLECT-INTO-LIST (SETOFALL ?E (OR (MEMBER-OF ?E ?X) (MEMBER-OF ?E ?Y))) ?R) :COMPUTED TRUE :CLOSED TRUE) (DEFRELATION MINIMUM-VALUE ((?L COLLECTION) (?MIN NUMBER)) :DOCUMENTATION \"Binds ?min to the minimum of the numbers in the list ?l.\" :AXIOMS (AND (RELATION-SPECIALIST MINIMUM-VALUE MINIMUM-OF-NUMBERS-SPECIALIST) (SINGLE-VALUED MINIMUM-VALUE)) :CLOSED TRUE) (DEFRELATION MAXIMUM-VALUE ((?L COLLECTION) (?MAX NUMBER)) :DOCUMENTATION \"Binds ?max to the maximum of the numbers in the list ?l.\" :AXIOMS (AND (RELATION-SPECIALIST MAXIMUM-VALUE MAXIMUM-OF-NUMBERS-SPECIALIST) (SINGLE-VALUED MAXIMUM-VALUE)) :CLOSED TRUE) (DEFRELATION SUM ((?L COLLECTION) (?SUM NUMBER)) :DOCUMENTATION \"Binds ?sum to the sum of the numbers in the list ?l.\" :AXIOMS (AND (RELATION-SPECIALIST SUM SUM-OF-NUMBERS-SPECIALIST) (SINGLE-VALUED SUM)) :CLOSED TRUE) (DEFFUNCTION PROJECT-COLUMN ((?I INTEGER) (?C COLLECTION)) :-> (?L LIST) :DOCUMENTATION \"Project elements in column ?i (zero-based) of the tuples
of ?c and collect them into a list ?l. \" :AXIOMS (RELATION-SPECIALIST PROJECT-COLUMN PROJECT-COLUMN-SPECIALIST) :CLOSED TRUE) (DEFRELATION MEAN-VALUE ((?L COLLECTION) (?MEAN NUMBER)) :DOCUMENTATION \"Binds ?mean to the mean of the numbers in ?l.\" :AXIOMS (AND (COMPUTED MEAN-VALUE) (RELATION-SPECIALIST MEAN-VALUE MEAN-OF-NUMBERS-SPECIALIST) (SINGLE-VALUED MEAN-VALUE)) :CLOSED TRUE) (DEFRELATION MEDIAN-VALUE ((?L COLLECTION) (?MEDIAN NUMBER)) :DOCUMENTATION \"Binds ?median to the median of the numbers in ?l.\" :AXIOMS (AND (COMPUTED MEDIAN-VALUE) (RELATION-SPECIALIST MEDIAN-VALUE MEDIAN-OF-NUMBERS-SPECIALIST) (SINGLE-VALUED MEDIAN-VALUE)) :CLOSED TRUE) (DEFRELATION STANDARD-DEVIATION ((?L COLLECTION) (?SD NUMBER)) :DOCUMENTATION \"Binds ?sd to the standard deviation of the numbers in ?l.\" :AXIOMS (AND (COMPUTED STANDARD-DEVIATION) (RELATION-SPECIALIST STANDARD-DEVIATION STANDARD-DEVIATION-SPECIALIST) (SINGLE-VALUED STANDARD-DEVIATION)) :CLOSED TRUE) (DEFRELATION VARIANCE ((?L COLLECTION) (?VARIANCE NUMBER)) :DOCUMENTATION \"Binds ?variance to the variance of the numbers in ?l.\" :AXIOMS (AND (COMPUTED VARIANCE) (RELATION-SPECIALIST VARIANCE VARIANCE-SPECIALIST) (SINGLE-VALUED VARIANCE)) :CLOSED TRUE) (DEFFUNCTION STRING-CONCATENATE ((?X THING) (?Y THING)) :-> (?Z STRING) :DOCUMENTATION \"Concatenate ?x and zero or more strings ?y (variable arity)
and bind ?z to the result.  Coerces any type argument to a string if necessary.\" :VARIABLE-ARITY TRUE :COMPUTED TRUE :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION STRING-CONCATENATE-COMPUTATION :CLOSED TRUE) (DEFFUNCTION SUBSTRING ((?S THING) (?START INTEGER) (?END INTEGER)) :-> (?SUB THING) :DOCUMENTATION \"Generate the substring ?sub of ?s starting at position ?start (zero-based)
and ending just before position ?end.  This is the PowerLoom equivalent to the STELLA method
`subsequence'.  Supplying negative numbers for ?start or ?end counts from the end of the
string where -1 indicates the end of ?s, -2 is one character from the end, etc.
If ?s and/or ?sub are not strings, they will be coerced first if possible.  This function
supports any binding pattern where at most one input is unbound (except for ?s), or
where both ?start and ?end are unbound in which case it can locate all occurrences of the
?sub string in ?s.  For example:
	 
      (retrieve all (?start ?end) (substring \\\"foo\\\" ?start ?end \\\"o\\\"))
   ==>  ?start = 1, ?end = 2,
        ?start = 2, ?end = 3
	
Additional examples can be found in the test suite.\" :AXIOMS (AND (COMPUTED SUBSTRING) (RELATION-SPECIALIST SUBSTRING SUBSEQUENCE-SPECIALIST)) :CLOSED TRUE) (DEFFUNCTION STRING-MATCH ((?PATTERN STRING) (?OBJECT THING) (?START INTEGER) (?END INTEGER)) :-> (?MATCH-POSITION INTEGER) :DOCUMENTATION \"Match ?pattern against ?object between ?start and ?end (zero-based),
and return the position of the first match or fail if no match exists.  Supplying negative
numbers for ?start or ?end counts from the end of the string (see `substring').  ?object can
be a named logic object or a string.  ?pattern will eventually support regular expressions,
currently it only handles string literals.  Apart from doing to-string coercion on ?object
this is somewhat redundant, since `substring' can generate ?start/?end pairs if its string
and substring arguments are bound.\" :AXIOMS (AND (COMPUTED STRING-MATCH) (RELATION-COMPUTATION STRING-MATCH STRING-MATCH-COMPUTATION) (RELATION-SPECIALIST STRING-MATCH COMPUTATION-SPECIALIST)) :CLOSED TRUE) (DEFFUNCTION STRING-MATCH-IGNORE-CASE ((?PATTERN STRING) (?OBJECT THING) (?START INTEGER) (?END INTEGER)) :-> (?MATCH-POSITION INTEGER) :DOCUMENTATION \"Case-insensitive version of `string-match' (which see).\" :AXIOMS (AND (COMPUTED STRING-MATCH-IGNORE-CASE) (RELATION-COMPUTATION STRING-MATCH-IGNORE-CASE STRING-MATCH-IGNORE-CASE-COMPUTATION) (RELATION-SPECIALIST STRING-MATCH-IGNORE-CASE COMPUTATION-SPECIALIST)) :CLOSED TRUE) (DEFFUNCTION STRING-UPCASE ((?OBJECT THING) (?START INTEGER) (?END INTEGER)) :-> (?UPCASED-STRING STRING) :DOCUMENTATION \"Upcase all characers of ?object between ?start and ?end and return the result.
Supplying negative numbers for ?start or ?end counts from the end of the string (see `substring').  ?object
can be a named logic object or a string.  Note that this function can also be used to test whether a string
or one of its subsequences is all uppercase by binding ?upcased-string to ?object.\" :COMPUTED TRUE :RELATION-COMPUTATION STRING-UPCASE-COMPUTATION :RELATION-SPECIALIST COMPUTATION-SPECIALIST :CLOSED TRUE) (DEFFUNCTION STRING-DOWNCASE ((?OBJECT THING) (?START INTEGER) (?END INTEGER)) :-> (?DOWNCASED-STRING STRING) :DOCUMENTATION \"Downcase all characers of ?object between ?start and ?end and return the result.
Supplying negative numbers for ?start or ?end counts from the end of the string (see `substring').  ?object
can be a named logic object or a string.  Note that this function can also be used to test whether a string
or one of its subsequences is all lowercase by binding ?downcased-string to ?object.\" :COMPUTED TRUE :RELATION-COMPUTATION STRING-DOWNCASE-COMPUTATION :RELATION-SPECIALIST COMPUTATION-SPECIALIST :CLOSED TRUE) (DEFFUNCTION STRING-CAPITALIZE ((?OBJECT THING) (?START INTEGER) (?END INTEGER)) :-> (?CAPITALIZED-STRING STRING) :DOCUMENTATION \"Capitalize the substring of ?object between ?start and ?end and return the result.
The first letter in the substring will be made uppercase and all others will be made lowercase.
Supplying negative numbers for ?start or ?end counts from the end of the string (see `substring').  ?object
can be a named logic object or a string.  Note that this function can also be used to test whether a string
or one of its subsequences is capitalized by binding ?capitalized-string to ?object.\" :COMPUTED TRUE :RELATION-COMPUTATION STRING-CAPITALIZE-COMPUTATION :RELATION-SPECIALIST COMPUTATION-SPECIALIST :CLOSED TRUE) (DEFFUNCTION STRING-REPLACE ((?OBJECT THING) (?FROM STRING) (?TO STRING) (?START INTEGER) (?END INTEGER)) :-> (?RESULT STRING) :DOCUMENTATION \"Replace all occurrances of ?from in ?object between ?start and ?end with ?to and return
the ?result. Supplying negative numbers for ?start or ?end counts from the end of the string (see `substring').
?object can be a named logic object or a string.\" :COMPUTED TRUE :RELATION-COMPUTATION STRING-REPLACE-COMPUTATION :RELATION-SPECIALIST COMPUTATION-SPECIALIST :CLOSED TRUE) (DEFFUNCTION STRING-COMPARE ((?O1 THING) (?O2 THING) (?START1 INTEGER) (?END1 INTEGER) (?START2 INTEGER) (?END2 INTEGER)) :-> (?RESULT INTEGER) :DOCUMENTATION \"Perform a lexicographic comparison between ?o1 and ?o2 within their respective substrings
?start1 to ?end1 and ?start2 to ?end2.  The ?result will be -1 if ?o1 comes before ?o2, 0 if they are equal,
and 1 if ?o2 comes before ?o1.  Supplying negative numbers for start or end pointers counts from the end of
the respective string (see `substring').  Both ?o1 and ?o2 can be a named logic object or a string.\" :COMPUTED TRUE :RELATION-COMPUTATION STRING-COMPARE-COMPUTATION :RELATION-SPECIALIST COMPUTATION-SPECIALIST :CLOSED TRUE) (DEFFUNCTION STRING-COMPARE-IGNORE-CASE ((?O1 THING) (?O2 THING) (?START1 INTEGER) (?END1 INTEGER) (?START2 INTEGER) (?END2 INTEGER)) :-> (?RESULT INTEGER) :DOCUMENTATION \"Just like `string-compare' (which see) but ignores case.\" :COMPUTED TRUE :RELATION-COMPUTATION STRING-COMPARE-IGNORE-CASE-COMPUTATION :RELATION-SPECIALIST COMPUTATION-SPECIALIST :CLOSED TRUE) (DEFFUNCTION STRING-TO-NUMBER ((?OBJECT THING) (?START INTEGER) (?END INTEGER)) :-> (?NUMBER NUMBER) :DOCUMENTATION \"If the part of ?object between ?start and ?end names a decimal number such as an integer
or float, convert it (that part) into the number it names.  Supplying negative numbers for ?start or ?end
counts from the end of the string (see `substring').  ?object can be a named logic object or a string.\" :COMPUTED TRUE :RELATION-COMPUTATION STRING-TO-NUMBER-COMPUTATION :RELATION-SPECIALIST COMPUTATION-SPECIALIST :CLOSED TRUE) (DEFFUNCTION LENGTH ((?X THING)) :-> (?Z INTEGER) :DOCUMENTATION \"Function that returns the length of a string or a logical list.\" :AXIOMS (AND (COMPUTED LENGTH) (RELATION-COMPUTATION LENGTH LENGTH-COMPUTATION) (RELATION-SPECIALIST LENGTH COMPUTATION-SPECIALIST)) :SYNONYM LENGTH-OF-LIST) (ASSERT (COMPUTED-PROCEDURE COMPUTATION-SPECIALIST)) (ASSERT (HANDLES-REVERSE-POLARITY COMPUTATION-SPECIALIST)) (ASSERT (COMPUTED-PROCEDURE CONSTRAINT-SPECIALIST)) (ASSERT (HANDLES-REVERSE-POLARITY CONSTRAINT-SPECIALIST)) (DEFFUNCTION OBJECT-NAME (?X) :-> (?C STRING) :DOCUMENTATION \"The name of the object ?X as a string.  This is just the
name, with module prefixes NOT included.\" :COMPUTED TRUE :RELATION-COMPUTATION OBJECT-NAME-COMPUTATION :RELATION-SPECIALIST COMPUTATION-SPECIALIST) (DEFFUNCTION OBJECT-PRINT-NAME (?X) :-> (?C STRING) :DOCUMENTATION \"The print name of the object ?X as a string relative to the
current module.  This will include module prefixes as well as escape characters
if necessary.\" :COMPUTED TRUE :RELATION-COMPUTATION OBJECT-PRINT-NAME-COMPUTATION :RELATION-SPECIALIST COMPUTATION-SPECIALIST) (DEFFUNCTION NAME-TO-OBJECT (?N) :-> ?O :DOCUMENTATION \"Find or create the PowerLoom logic object ?o named by
the name ?n in the current module.  We are interpreting the name ?n literally
here, i.e., it is not a print name as assumed by PLI functions and an object
with exactly that name will be looked up or created.  If ?n is not a string,
this will coerce it to a string first.  We are intentionally
using a separate function here (instead of folding this into `object-name'),
since we might want to be able to look for an object with a certain name
but not create one if it doesn't exist.\" :COMPUTED TRUE :RELATION-COMPUTATION NAME-TO-OBJECT-COMPUTATION :RELATION-SPECIALIST COMPUTATION-SPECIALIST) (DEFFUNCTION PRINT-NAME-TO-OBJECT (?N) :-> ?O :DOCUMENTATION \"Find or create the PowerLoom logic object ?o named by
the print name ?n in the current module.  This is just like `name-to-object'
but interprets ?n as a possibly qualified print name with escape characters.
Note that this will simply fail when given a name with incorrect read syntax
or a non-existing module.\" :COMPUTED TRUE :RELATION-COMPUTATION PRINT-NAME-TO-OBJECT-COMPUTATION :RELATION-SPECIALIST COMPUTATION-SPECIALIST) (DEFFUNCTION ARITY ((?R RELATION)) :-> (?ARITY INTEGER) :DOCUMENTATION \"The number of arguments/domains of the relation '?r'.\") (ASSERT (AND (COMPUTED ARITY) (RELATION-SPECIALIST ARITY ARITY-SPECIALIST) (HANDLES-REVERSE-POLARITY ARITY-SPECIALIST))) (DEFRELATION VARIABLE-ARITY ((?R RELATION)) :DOCUMENTATION \"Asserts that the relation ?r can take a variable number of arguments.\" :AXIOMS (CLOSED VARIABLE-ARITY)) (DEFCONCEPT BINARY-RELATION (?R RELATION) :DOCUMENTATION \"The class of binary relations.\" :<<= (AND (RELATION ?R) (ARITY ?R 2))) (DEFFUNCTION INVERSE ((?R BINARY-RELATION)) :-> ?INVERSERELATION :DOCUMENTATION \"Function that returns the inverse relation for ?r.
PERFORMANCE NOTE: for best results there should be only one `(inverse R I)'
assertion per relation pair `R' and `I'.  In that case `R' is viewed as the
canonical relation and `I' simply provides a different access mechanism to
the canonical relation.  In a logic-based KR paradigm inverse relations are
redundant and do not add anything that couldn't be represented or queried
without them, however, sometimes they can provide some extra convenience for
users.  Asserting `(inverse I R)' also will not cause an error but can degrade
backward inference performance due to the extra redundant rule that gets
generated.  If domain rules will be written in terms of both `R' and `I' (as
opposed to only `R'), `(inverse I R)' should be asserted also to get full
inferential connectivity between the two relations.\" :=>> (BINARY-RELATION ?INVERSERELATION) :=>> (<<=>> (HOLDS ?INVERSERELATION ?Y ?X) (HOLDS ?R ?X ?Y)) :AXIOMS (SYMMETRIC INVERSE)) (DEFRELATION DUPLICATE-FREE ((?C COLLECTION)) :DOCUMENTATION \"?c is duplicate-free if no two members
denote the same object.\") (DEFRELATION DIFFERENT (?X ?Y) :DOCUMENTATION \"True if no two arguments are the same.  This is equivalent to
`(duplicate-free (list-of ?x ?y ...))' but without the need to generate a
collection object.  The main use for this is to state and test pairwise
inequalities between N entities without having to generate O(N**2) statements.\" :VARIABLE-ARITY TRUE :COMPUTED TRUE :RELATION-SPECIALIST DIFFERENT-SPECIALIST :AXIOMS (HANDLES-REVERSE-POLARITY DIFFERENT-SPECIALIST)) (DEFRELATION ORDERED ((?C COLLECTION)) :DOCUMENTATION \"?c is ordered if the ordering of its
members is significant.  Lists are ordered, while sets are not.\") (DEFRELATION COMMUTATIVE ((?R RELATION)) :DOCUMENTATION \"A relation ?r is commutative if its truth value is
invariant with any permutation of its arguments.\" :AXIOMS (=>> (AND (COMMUTATIVE ?R) (= (ARITY ?R) 2)) (SYMMETRIC ?R))) (DEFRELATION REFLEXIVE ((?R RELATION)) :DOCUMENTATION \"A binary relation ?r is reflexive if it is always true when
both of its arguments are identical.\" :=>> (BINARY-RELATION ?R) :=> (NOT (IRREFLEXIVE ?R)) :<= (AND (BINARY-RELATION ?R) (FORALL ?X (HOLDS ?R ?X ?X))) :=> (RELATION-SPECIALIST ?R REFLEXIVE-RELATION-SPECIALIST) :AXIOMS (HANDLES-REVERSE-POLARITY REFLEXIVE-RELATION-SPECIALIST)) (DEFRELATION IRREFLEXIVE ((?R RELATION)) :DOCUMENTATION \"A binary relation ?r is irreflexive if it is false when both
of its arguments are identical.\" :=>> (BINARY-RELATION ?R) :=> (NOT (REFLEXIVE ?R)) :<= (AND (BINARY-RELATION ?R) (FORALL ?X (NOT (HOLDS ?R ?X ?X)))) :=> (RELATION-SPECIALIST ?R IRREFLEXIVE-RELATION-SPECIALIST) :AXIOMS (HANDLES-REVERSE-POLARITY IRREFLEXIVE-RELATION-SPECIALIST)) (DEFRELATION SYMMETRIC ((?R RELATION)) :DOCUMENTATION \"A binary relation ?r is symmetric if it is commutative.\" :=>> (BINARY-RELATION ?R) :=>> (COMMUTATIVE ?R) :=>> (FORALL (?X ?Y) (<<= (HOLDS ?R ?X ?Y) (HOLDS ?R ?Y ?X))) :=> (NOT (ANTISYMMETRIC ?R))) (DEFRELATION ANTISYMMETRIC ((?R RELATION)) :DOCUMENTATION \"A binary relation ?r is antisymmetric if whenever (?r ?x ?y)
is true (?r ?y ?x) is false unless ?x equals ?y.\" :=>> (BINARY-RELATION ?R) :=> (NOT (SYMMETRIC ?R)) :=> (FORALL (?X ?Y) (=> (AND (HOLDS ?R ?X ?Y) (NOT (= ?X ?Y))) (NOT (?R ?Y ?X))))) (DEFRELATION TRANSITIVE ((?R RELATION)) :DOCUMENTATION \"A binary relation ?r is transitive if (?r ?x ?y)
and (?r ?y ?z) implies that (?r ?x ?z).  Note that functions cannot
be transitive, since their single-valuedness would not allow multiple
different values such as (?r ?x ?y) and (?r ?x ?z) due to the Unique
Names Assumption made by PowerLoom.\" :=>> (AND (BINARY-RELATION ?R) (NOT (FUNCTION ?R))) :=>> (=> (AND (BINARY-RELATION ?R) (?R ?X ?Y) (?R ?Y ?Z)) (?R ?X ?Z))) (DEFRELATION TOTAL ((?R FUNCTION)) :DOCUMENTATION \"True if the function '?r' is defined for all
combinations of inputs.  By default, functions are not assumed to
be total (unlike Prolog, which 'does' make such an assumption.
For example, if we define a two-argument function `foo' and then retrieve
its value applied to some random instances `a' and `b', we get nothing
back:
	 
   (deffunction foo (?x ?y) :-> ?z)
   (retrieve ?x (= ?x (foo a b)))
	
However, if we assert that `foo' is total, then we get a skolem back
when we execute the same retrieve:
	 
   (assert (total foo))
   (retrieve ?x (= ?x (foo a b)))
	
\") (DEFRELATION ABSTRACT ((?R RELATION)) :DOCUMENTATION \"True if there are no direct assertions made
to the relation ?r.\") (DEFFUNCTION CONCEPT-PROTOTYPE ((?C CONCEPT)) :-> ?I :DOCUMENTATION \"Function that, given a concept, returns a prototypical
instance that inherits all constraints that apply to any concept member,
and has no additional constraints.\" :RELATION-SPECIALIST CONCEPT-PROTOTYPE-SPECIALIST :TOTAL TRUE :CLOSED TRUE :SYNONYM CLASS-PROTOTYPE) (DEFRULE \"'Not instance-of' rule\" (<= (NOT (INSTANCE-OF ?X ?C)) (AND (COLLECTION ?C) (CLOSED ?C) (FAIL (INSTANCE-OF ?X ?C))))) (DEFRULE \"Forward 'instance-of' rule\" (=> (INSTANCE-OF ?X ?C) (AND (CONCEPT ?C) (HOLDS ?C ?X))) :FORWARD? TRUE) (DEFCONCEPT USER-THING (?X) :DOCUMENTATION \"The class of user-defined things.\") (DEFRELATION CASE-MATCH ((?X THING) (?Y THING))) (DEFRULE CASE-MATCH-RULE (FORALL ((?X THING) (?Y THING)) (=> (= ?X ?Y) (CASE-MATCH ?X ?Y)))) (DEFRELATION SOFT-EQ ((?X THING) (?Y THING))) (DEFRULE SOFT-EQ-RULE (FORALL ((?X THING) (?Y THING)) (=> (= ?X ?Y) (SOFT-EQ ?X ?Y)))) (DEFFUNCTION OBJECT-CONTEXT (?X) :-> (?C CONTEXT) :DOCUMENTATION \"Retrieve the home context of ?x where it was first referenced or defined.\" :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION OBJECT-CONTEXT-COMPUTATION :COMPUTED TRUE :SYNONYM CONTEXT-OF) (DEFFUNCTION OBJECT-NAME-CONTEXT (?X) :-> (?C CONTEXT) :DOCUMENTATION \"Retrieve the home context of ?x's name which might be different than the home
context of ?x, for example, for objects named by semantic web namespaces such as OWL/sameAs, etc.\" :RELATION-SPECIALIST COMPUTATION-SPECIALIST :RELATION-COMPUTATION OBJECT-NAME-CONTEXT-COMPUTATION :COMPUTED TRUE) (DEFRELATION DISJOINT ((?C1 COLLECTION) (?C2 COLLECTION)) :DOCUMENTATION \"True if the intersection of ?c1 and ?c2 is empty.\" :IRREFLEXIVE TRUE :<<= (CHEAP-DISJOINT ?C1 ?C2)) (DEFRELATION MUTUALLY-DISJOINT-COLLECTION ((?S SET)) :DOCUMENTATION \"True if the members of ?s are pair-wise disjoint.  Used
most often to expresse disjointness constraints between concepts.  For
example
	 
   (mutually-disjoint-collection (setof MAN WOMAN))
	
states that the concepts MAN and WOMAN are disjoint.
\" :=>> (=> (AND (MEMBER-OF ?C1 ?S) (MEMBER-OF ?C2 ?S) (NOT (= ?C1 ?C2))) (DISJOINT ?C1 ?C2))) (DEFRELATION COVERING ((?C COLLECTION) (?COVER SET)) :DOCUMENTATION \"True if ?c is a subset of the union of all
collections in the set ?cover (see `disjoint-covering').\") (DEFRELATION DISJOINT-COVERING ((?C COLLECTION) (?DISJOINTCOVER SET)) :DOCUMENTATION \"True if ?c is covered by the collections in ?disjointCover
and if the member sets in ?disjointCover are mutually-disjoint.  For
example the concepts `Igneous-Rock', `Metamorphic-Rock', and
`Sedimentary-Rock' together form a disjoint covering of the concept `Rock'.\" :<<= (AND (COVERING ?C ?DISJOINTCOVER) (MUTUALLY-DISJOINT-COLLECTION ?DISJOINTCOVER))) (DEFRELATION CHEAP-DISJOINT ((?C1 COLLECTION) (?C2 COLLECTION)) :DOCUMENTATION \"Find proof of disjointness without using refutation.\" :<<= (AND (HAS-PARTITION-MEMBERSHIP ?C1) (HAS-PARTITION-MEMBERSHIP ?C2) (EXISTS (?PROPOSITION ?PARTITION1 ?PARTITION2) (AND (PARTITION-MEMBERSHIP ?C1 ?PROPOSITION ?PARTITION1) (PARTITION-MEMBERSHIP ?C2 ?PROPOSITION ?PARTITION2) (NOT (= ?PARTITION1 ?PARTITION2)))))) (DEFRELATION REFUTATION-DISJOINT ((?C1 COLLECTION) (?C2 COLLECTION)) :DOCUMENTATION \"Assume that an instance belongs to both ?c1 and ?c2
and look for a clash.\" :AXIOMS (RELATION-SPECIALIST REFUTATION-DISJOINT REFUTATION-DISJOINT-SPECIALIST)) (DEFRELATION HAS-PARTITION-MEMBERSHIP ((?C COLLECTION)) :DOCUMENTATION \"TRUE if one or more PARTITION-MEMBERSHIP tuples
exist with ?c as the first argument.  FALSE if none exists.
Unknown if a derivation of PARTITION-MEMBERSHIP tuples has not
occurred.  A specialist for this relation creates PARTITION-MEMBERSHIP
tuples as a side-effect of querying this predicate.\" :AXIOMS (AND (HIDDEN-RELATION HAS-PARTITION-MEMBERSHIP) (RELATION-SPECIALIST HAS-PARTITION-MEMBERSHIP HAS-PARTITION-MEMBERSHIP-SPECIALIST))) (DEFRELATION PARTITION-MEMBERSHIP ((?C COLLECTION) (?PROPOSITION PROPOSITION) (?PARTITION COLLECTION)) :DOCUMENTATION \"Caches the fact that ?partition is a partition of
a mutually-disjoint collection, and that ?c is a subset of ?partition.
Used to support rapid computation of pairwise disjointness.\" :AXIOMS (HIDDEN-RELATION PARTITION-MEMBERSHIP))) \"/PL-KERNEL-KB\")"
      "/PL-KERNEL-KB"))
    (|/PL-KERNEL-KB/INITIALIZE-KERNEL-KB|))))
