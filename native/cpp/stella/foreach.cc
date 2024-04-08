//  -*- Mode: C++ -*-

// foreach.cc

/*
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
*/

#include "stella/stella-system.hh"

namespace stella {

Cons* extractOneInClause(Cons* tail, Cons*& _Return1) {
  { Object* variable = tail->value;
    Object* operatoR = tail->rest->value;
    Cons* clause = tail;

    if (!((symbolP(variable) ||
        consP(variable)) &&
        (getQuotedTree("((IN ON ISA) \"/STELLA\")", "/STELLA")->memberP(operatoR) &&
         ((boolean)(tail->rest->rest->value))))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal syntax where 'IN', 'ON', or 'ISA' clause expected:" << std::endl << "   " << "`" << deUglifyParseTree(tail) << "'" << "." << std::endl;
        }
      }
      _Return1 = NIL;
      return (NULL);
    }
    clause->firstSetter(operatoR);
    clause->secondSetter(variable);
    tail = tail->rest->rest->rest;
    clause->rest->rest->rest = NIL;
    _Return1 = tail;
    return (clause);
  }
}

Cons* extractOneGeneratorTerm(Cons* tail, Cons*& _Return1) {
  { Cons* inclause = NULL;
    Cons* residue = NULL;
    Cons* parallelterms = NULL;

    inclause = extractOneInClause(tail, residue);
    if (!(residue->value == SYM_FOREACH_STELLA_AS)) {
      _Return1 = residue;
      return (inclause);
    }
    parallelterms = cons(inclause, cons(SYM_FOREACH_STELLA_AS, NIL));
    while (residue->value == SYM_FOREACH_STELLA_AS) {
      residue = residue->rest;
      inclause = extractOneInClause(residue, residue);
      parallelterms = cons(inclause, parallelterms);
    }
    { Cons* _Return0 = parallelterms->reverse();

      _Return1 = residue;
      return (_Return0);
    }
  }
}

Cons* extractGeneratorsClause(Cons* tail, Cons*& _Return1) {
  { Cons* generatorterm = NULL;
    Cons* residue = NULL;
    Cons* generatorsclause = NULL;

    generatorterm = extractOneGeneratorTerm(tail, residue);
    if (!(residue->value == SYM_FOREACH_STELLA_COMMA)) {
      _Return1 = residue;
      return (generatorterm);
    }
    generatorsclause = cons(generatorterm, cons(SYM_FOREACH_STELLA_COMMA, NIL));
    while (residue->value == SYM_FOREACH_STELLA_COMMA) {
      generatorterm = extractOneGeneratorTerm(residue->rest, residue);
      generatorsclause = cons(generatorterm, generatorsclause);
    }
    { Cons* _Return0 = generatorsclause->reverse();

      _Return1 = residue;
      return (_Return0);
    }
  }
}

Object* extractOptionAndResidue(Symbol* option, Cons* tail, Cons*& _Return1) {
  if (!(tail->value == option)) {
    _Return1 = tail;
    return (NULL);
  }
  { Object* argument = NULL;
    Cons* residue = NULL;

    argument = tail->rest->value;
    residue = tail->rest->rest;
    _Return1 = residue;
    return (argument);
  }
}

Cons* extractDoClause(Cons* tail, Cons*& _Return1) {
  { StandardObject* dummy1;

    if (!(tail->value == SYM_FOREACH_STELLA_DO)) {
      _Return1 = tail;
      return (NULL);
    }
    { Cons* doclause = tail;
      Cons* lastdocons = NULL;

      tail = tail->rest;
      while ((!(tail == NIL)) &&
          (!(tail->value == SYM_FOREACH_STELLA_COLLECT))) {
        lastdocons = tail;
        tail = tail->rest;
      }
      if (!((boolean)(lastdocons))) {
        {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing arguments to DO separator" << "." << std::endl;
            }
          }
          doclause->rest = consList(1, walkDontCallMeTree(NIL, SGT_FOREACH_STELLA_VOID, dummy1));
        }
      }
      else {
        lastdocons->rest = NIL;
      }
      _Return1 = tail;
      return (doclause);
    }
  }
}

Cons* foreachToPrefixForeachTree(Cons* foreachtree) {
  { StandardObject* dummy1;
    StandardObject* dummy2;
    StandardObject* dummy3;

    { Cons* generatorsclause = NULL;
      Object* filterclause = NULL;
      Cons* doclause = NULL;
      Object* collectclause = NULL;
      Object* intoclause = NULL;
      Cons* residue = ((Cons*)(foreachtree->rest));
      Cons* otree = NULL;

      generatorsclause = extractGeneratorsClause(residue, residue);
      if (!((boolean)(generatorsclause))) {
        return (listO(4, SYM_FOREACH_STELLA_PREFIX_FOREACH, listO(4, SYM_FOREACH_STELLA_IN, SYM_FOREACH_STELLA_X, SYM_FOREACH_STELLA_NIL, NIL), listO(3, SYM_FOREACH_STELLA_DO, walkDontCallMeTree(otree, SGT_FOREACH_STELLA_VOID, dummy1), NIL), NIL));
      }
      filterclause = extractOptionAndResidue(SYM_FOREACH_STELLA_WHERE, residue, residue);
      if (((boolean)(filterclause))) {
        filterclause = listO(3, SYM_FOREACH_STELLA_WHERE, filterclause, NIL);
      }
      doclause = extractDoClause(residue, residue);
      collectclause = extractOptionAndResidue(SYM_FOREACH_STELLA_COLLECT, residue, residue);
      intoclause = extractOptionAndResidue(SYM_FOREACH_STELLA_INTO, residue, residue);
      if (((boolean)(collectclause)) ||
          ((boolean)(intoclause))) {
        collectclause = listO(3, SYM_FOREACH_STELLA_COLLECT_INTO, collectclause, cons(intoclause, NIL));
      }
      otree = listO(3, SYM_FOREACH_STELLA_PREFIX_FOREACH, generatorsclause, ((((boolean)(filterclause)) ? cons(filterclause, NIL) : NIL))->concatenate(((((boolean)(doclause)) ? cons(doclause, NIL) : NIL))->concatenate(((((boolean)(collectclause)) ? cons(collectclause, NIL) : NIL))->concatenate(NIL, 0), 0), 0));
      if ((((boolean)(collectclause)) &&
          (!((boolean)(intoclause)))) ||
          (((boolean)(intoclause)) &&
           (!((boolean)(collectclause))))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing COLLECT or INTO clause in" << "." << std::endl;
          }
        }
        return (listO(4, SYM_FOREACH_STELLA_PREFIX_FOREACH, listO(4, SYM_FOREACH_STELLA_IN, SYM_FOREACH_STELLA_X, SYM_FOREACH_STELLA_NIL, NIL), listO(3, SYM_FOREACH_STELLA_DO, walkDontCallMeTree(otree, SGT_FOREACH_STELLA_VOID, dummy2), NIL), NIL));
      }
      if (!(residue == NIL)) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Extra expressions at the end of foreach statement: " << "`" << deUglifyParseTree(residue) << "'" << "." << std::endl;
          }
        }
        return (listO(4, SYM_FOREACH_STELLA_PREFIX_FOREACH, listO(4, SYM_FOREACH_STELLA_IN, SYM_FOREACH_STELLA_X, SYM_FOREACH_STELLA_NIL, NIL), listO(3, SYM_FOREACH_STELLA_DO, walkDontCallMeTree(otree, SGT_FOREACH_STELLA_VOID, dummy3), NIL), NIL));
      }
      return (otree);
    }
  }
}

Cons* walkForeachTree(Cons* tree, StandardObject*& _Return1) {
  { 
    BIND_STELLA_SPECIAL(oNOFSPECIALSATLOOPENTRYo, int, oSPECIALVARIABLESTACKo->length());
    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

      if (testValue000 == SYM_FOREACH_STELLA_FOREACH) {
        return (walkPrefixForeachTree(foreachToPrefixForeachTree(tree), _Return1));
      }
      else if (testValue000 == SYM_FOREACH_STELLA_EXISTS) {
        return (walkExistsTree(tree, _Return1));
      }
      else if (testValue000 == SYM_FOREACH_STELLA_FORALL) {
        return (walkForallTree(tree, _Return1));
      }
      else if (testValue000 == SYM_FOREACH_STELLA_SOME) {
        return (walkSomeTree(tree, _Return1));
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

Object* walkCollectionTree(Object* tree, boolean dontoptimizeP, StandardObject*& _Return1) {
  if (safePrimaryType(tree) == SGT_FOREACH_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if ((!dontoptimizeP) &&
          ((tree->value == SYM_FOREACH_STELLA_INTERVAL) &&
           (tree->length() == 3))) {
        _Return1 = SGT_FOREACH_STELLA_INTEGER_INTERVAL;
        return (tree);
      }
    }
  }
  else {
  }
  { Object* otree = NULL;
    StandardObject* otype = NULL;

    otree = walkExpressionTree(tree, SGT_FOREACH_STELLA_UNKNOWN, SYM_FOREACH_STELLA_FOREACH, false, otype);
    return (sysTree(otree, otype, _Return1));
  }
}

Cons* yieldInCursorClauses(Cons* intree, boolean dontoptimizeP, Cons*& _Return1, Cons*& _Return2, Object*& _Return3) {
  { Object* vartree = intree->rest->value;
    Symbol* keyvar = NULL;
    Symbol* valuevar = NULL;
    Surrogate* collectionbasetype = NULL;

    { Object* collectiontree = NULL;
      StandardObject* collectiontype = NULL;

      collectiontree = walkCollectionTree(intree->rest->rest->value, dontoptimizeP, collectiontype);
      intree->thirdSetter(NULL);
      collectionbasetype = typeSpecToBaseType(collectiontype);
      if (dontoptimizeP &&
          (!safeSubtypeOfP(collectionbasetype, SGT_FOREACH_STELLA_ABSTRACT_ITERATOR))) {
        collectiontree = walkCollectionTree(listO(3, SYM_FOREACH_STELLA_ALLOCATE_ITERATOR, collectiontree, NIL), true, collectiontype);
        collectionbasetype = typeSpecToBaseType(collectiontype);
      }
      if (safePrimaryType(vartree) == SGT_FOREACH_STELLA_CONS) {
        { Object* vartree000 = vartree;
          Cons* vartree = ((Cons*)(vartree000));

          if (!(vartree->length() == 2)) {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal number of variables in IN clause: " << "`" << deUglifyParseTree(intree) << "'" << "." << std::endl;
              }
            }
            _Return1 = NIL;
            _Return2 = NIL;
            _Return3 = SYM_FOREACH_STELLA_FALSE;
            return (NIL);
          }
          keyvar = ((Symbol*)(vartree->value));
          valuevar = ((Symbol*)(vartree->rest->value));
        }
      }
      else {
        valuevar = ((Symbol*)(vartree));
      }
      if (collectionbasetype == SGT_FOREACH_STELLA_INTEGER_INTERVAL) {
        return (yieldInCursorClausesForIntegerInterval(((Cons*)(collectiontree)), collectiontype, keyvar, valuevar, _Return1, _Return2, _Return3));
      }
      else if (collectionbasetype == SGT_FOREACH_STELLA_ARGUMENT_LIST) {
        return (yieldInCursorClausesForArgumentList(collectiontree, collectiontype, keyvar, valuevar, _Return1, _Return2, _Return3));
      }
      else {
        if (useVectorStyleIterationP(collectionbasetype)) {
          return (yieldInCursorClausesForVector(collectiontree, collectiontype, keyvar, valuevar, _Return1, _Return2, _Return3));
        }
        else {
          return (yieldInCursorClausesForGeneralCollection(collectiontree, collectiontype, keyvar, valuevar, _Return1, _Return2, _Return3));
        }
      }
    }
  }
}

boolean useVectorStyleIterationP(Surrogate* collectiontype) {
  return ((collectiontype == SGT_FOREACH_STELLA_STRING) ||
      ((collectiontype == SGT_FOREACH_STELLA_MUTABLE_STRING) ||
       (safeSubtypeOfP(collectiontype, SGT_FOREACH_STELLA_VECTOR) ||
        (safeSubtypeOfP(collectiontype, SGT_FOREACH_STELLA_SEQUENCE_MIXIN) &&
         ((boolean)(lookupSlot(((Class*)(collectiontype->surrogateValue)), SYM_FOREACH_STELLA_THE_ARRAY)))))));
}

Cons* yieldInCursorClausesForGeneralCollection(Object* collectiontree, StandardObject* collectiontype, Symbol* keyvar, Symbol* valuevar, Cons*& _Return1, Cons*& _Return2, Object*& _Return3) {
  { boolean dummy1;

    { Surrogate* collectionbasetype = typeSpecToBaseType(collectiontype);
      Symbol* iteratorvar = localGensym("ITER");
      Cons* iteratorclauses = NIL;
      Cons* valueclauses = NIL;
      Object* continuationtest = NULL;
      Cons* keytree = NIL;
      Cons* valuetree = NIL;
      Cons* bumptrees = NIL;

      if (collectionbasetype == SGT_FOREACH_STELLA_LIST) {
        iteratorclauses = cons(cons(iteratorvar, listO(3, SGT_FOREACH_STELLA_CONS, listO(3, SYM_FOREACH_STELLA_THE_CONS_LIST, collectiontree, NIL), NIL)), NIL);
        collectionbasetype = SGT_FOREACH_STELLA_CONS;
      }
      else if (collectionbasetype == SGT_FOREACH_STELLA_KEY_VALUE_LIST) {
        iteratorclauses = cons(cons(iteratorvar, listO(3, SGT_FOREACH_STELLA_KV_CONS, listO(3, SYM_FOREACH_STELLA_THE_KV_LIST, collectiontree, NIL), NIL)), NIL);
        collectionbasetype = SGT_FOREACH_STELLA_KV_CONS;
      }
      else if (collectionbasetype == SGT_FOREACH_STELLA_PROPERTY_LIST) {
        iteratorclauses = cons(cons(iteratorvar, listO(3, SGT_FOREACH_STELLA_CONS, listO(3, SYM_FOREACH_STELLA_THE_PLIST, collectiontree, NIL), NIL)), NIL);
      }
      else if ((collectionbasetype == SGT_FOREACH_STELLA_CONS) ||
          (collectionbasetype == SGT_FOREACH_STELLA_KV_CONS)) {
        iteratorclauses = cons(cons(iteratorvar, cons(collectionbasetype, cons(collectiontree, NIL))), NIL);
      }
      else {
        if (!(safeSubtypeOfP(collectionbasetype, SGT_FOREACH_STELLA_ABSTRACT_ITERATOR))) {
          collectiontree = listO(3, SYM_FOREACH_STELLA_ALLOCATE_ITERATOR, collectiontree, NIL);
        }
        iteratorclauses = cons(cons(iteratorvar, listO(3, SGT_FOREACH_STELLA_ABSTRACT_ITERATOR, collectiontree, NIL)), NIL);
        collectionbasetype = SGT_FOREACH_STELLA_ABSTRACT_ITERATOR;
      }
      if (((boolean)(keyvar))) {
        keytree = listO(3, SYM_FOREACH_STELLA_KEY, iteratorvar, NIL);
      }
      valuetree = listO(3, SYM_FOREACH_STELLA_VALUE, iteratorvar, NIL);
      if (collectionbasetype == SGT_FOREACH_STELLA_CONS) {
        bumptrees = cons(listO(3, SYM_FOREACH_STELLA_SETQ, iteratorvar, cons(listO(3, SYM_FOREACH_STELLA_REST, iteratorvar, NIL), NIL)), NIL);
        continuationtest = listO(3, SYM_FOREACH_STELLA_NOT, listO(3, SYM_FOREACH_STELLA_NILp, iteratorvar, NIL), NIL);
      }
      else if (collectionbasetype == SGT_FOREACH_STELLA_KV_CONS) {
        bumptrees = cons(listO(3, SYM_FOREACH_STELLA_SETQ, iteratorvar, cons(listO(3, SYM_FOREACH_STELLA_REST, iteratorvar, NIL), NIL)), NIL);
        continuationtest = listO(3, SYM_FOREACH_STELLA_DEFINEDp, iteratorvar, NIL);
      }
      else if (collectionbasetype == SGT_FOREACH_STELLA_PROPERTY_LIST) {
        if (((boolean)(keyvar))) {
          keytree = listO(3, SYM_FOREACH_STELLA_VALUE, iteratorvar, NIL);
        }
        valuetree = listO(3, SYM_FOREACH_STELLA_VALUE, listO(3, SYM_FOREACH_STELLA_REST, iteratorvar, NIL), NIL);
        bumptrees = cons(listO(3, SYM_FOREACH_STELLA_SETQ, iteratorvar, cons(listO(3, SYM_FOREACH_STELLA_REST, listO(3, SYM_FOREACH_STELLA_REST, iteratorvar, NIL), NIL), NIL)), NIL);
        continuationtest = listO(3, SYM_FOREACH_STELLA_NOT, listO(3, SYM_FOREACH_STELLA_NILp, iteratorvar, NIL), NIL);
      }
      else if (collectionbasetype == SGT_FOREACH_STELLA_ABSTRACT_ITERATOR) {
        bumptrees = NIL;
        continuationtest = listO(3, SYM_FOREACH_STELLA_NEXTp, iteratorvar, NIL);
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << collectionbasetype << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      iteratorclauses = cons(cons(valuevar, cons(extractParameterType(collectiontype, SYM_FOREACH_STELLA_ANY_VALUE, dummy1), cons(SYM_FOREACH_STELLA_NULL, NIL))), iteratorclauses);
      valueclauses = cons(listO(3, SYM_FOREACH_STELLA_SETQ, valuevar, cons(valuetree, NIL)), valueclauses);
      if (((boolean)(keyvar))) {
        { StandardObject* keytype = NULL;
          boolean parameterexistsP = false;

          keytype = extractParameterType(collectiontype, SYM_FOREACH_STELLA_ANY_KEY, parameterexistsP);
          if (parameterexistsP) {
            iteratorclauses = cons(cons(keyvar, cons(keytype, cons(SYM_FOREACH_STELLA_NULL, NIL))), iteratorclauses);
            valueclauses = cons(listO(3, SYM_FOREACH_STELLA_SETQ, keyvar, cons(keytree, NIL)), valueclauses);
          }
          else {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal key variable specified for keyless collection " << "`" << deUglifyParseTree(collectiontype) << "'" << "." << std::endl;
              }
            }
            _Return1 = NIL;
            _Return2 = NIL;
            _Return3 = SYM_FOREACH_STELLA_FALSE;
            return (NIL);
          }
        }
      }
      _Return1 = valueclauses;
      _Return2 = bumptrees;
      _Return3 = continuationtest;
      return (iteratorclauses);
    }
  }
}

boolean oAGGRESSIVELY_OPTIMIZE_INTERVAL_FOREACHpo = false;

Cons* yieldInCursorClausesForIntegerInterval(Cons* collectiontree, StandardObject* collectiontype, Symbol* keyvar, Symbol* valuevar, Cons*& _Return1, Cons*& _Return2, Object*& _Return3) {
  { StandardObject* dummy1;

    if (((boolean)(keyvar))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal key variable specified for INTEGER-INTERVAL" << "." << std::endl;
        }
      }
      _Return1 = NIL;
      _Return2 = NIL;
      _Return3 = SYM_FOREACH_STELLA_FALSE;
      return (NIL);
    }
    if (oAGGRESSIVELY_OPTIMIZE_INTERVAL_FOREACHpo) {
      return (yieldOptimizedInCursorClausesForIntegerInterval(collectiontree, collectiontype, keyvar, valuevar, _Return1, _Return2, _Return3));
    }
    { Object* upperbound = collectiontree->rest->rest->value;
      boolean knownunboundedP = (upperbound == SYM_FOREACH_STELLA_NULL) ||
          (upperbound == SYM_FOREACH_STELLA_NULL_INTEGER);
      boolean knownboundedP = (!knownunboundedP) &&
          (isaP(walkExpressionTree(copyConsTree(upperbound), SGT_FOREACH_STELLA_INTEGER, SYM_FOREACH_STELLA_FOREACH, false, dummy1), SGT_FOREACH_STELLA_NUMBER_WRAPPER) ||
           (consP(upperbound) &&
            getQuotedTree("((+ - * / 1+ 1- ++ -- LENGTH) \"/STELLA\")", "/STELLA")->memberP(((Cons*)(upperbound))->value)));
      Symbol* iteratorvar = localGensym("ITER");
      Symbol* upperboundvar = (knownunboundedP ? ((Symbol*)(NULL)) : localGensym("UPPER-BOUND"));
      Symbol* unboundedvar = ((knownunboundedP ||
          knownboundedP) ? ((Symbol*)(NULL)) : localGensym("UNBOUNDED?"));

      { Cons* _Return0 = listO(3, cons(valuevar, listO(3, SGT_FOREACH_STELLA_INTEGER, SYM_FOREACH_STELLA_NULL, NIL)), cons(iteratorvar, listO(3, SGT_FOREACH_STELLA_INTEGER, collectiontree->rest->value, NIL)), ((knownunboundedP ? NIL : cons(cons(upperboundvar, listO(3, SGT_FOREACH_STELLA_INTEGER, upperbound, NIL)), NIL)))->concatenate((((knownunboundedP ||
            knownboundedP) ? NIL : cons(cons(unboundedvar, listO(3, SGT_FOREACH_STELLA_BOOLEAN, listO(3, SYM_FOREACH_STELLA_NULLp, upperboundvar, NIL), NIL)), NIL)))->concatenate(NIL, 0), 0));

        _Return1 = cons(listO(3, SYM_FOREACH_STELLA_SETQ, valuevar, cons(iteratorvar, NIL)), NIL);
        _Return2 = cons(listO(3, SYM_FOREACH_STELLA_ii, iteratorvar, NIL), NIL);
        _Return3 = (knownunboundedP ? ((StandardObject*)(SYM_FOREACH_STELLA_TRUE)) : ((StandardObject*)((knownboundedP ? listO(3, SYM_FOREACH_STELLA_le, iteratorvar, cons(upperboundvar, NIL)) : listO(3, SYM_FOREACH_STELLA_OR, unboundedvar, cons(listO(3, SYM_FOREACH_STELLA_le, iteratorvar, cons(upperboundvar, NIL)), NIL))))));
        return (_Return0);
      }
    }
  }
}

Cons* yieldOptimizedInCursorClausesForIntegerInterval(Cons* collectiontree, StandardObject* collectiontype, Symbol* keyvar, Symbol* valuevar, Cons*& _Return1, Cons*& _Return2, Object*& _Return3) {
  { StandardObject* dummy1;
    StandardObject* dummy2;

    {
      collectiontype = collectiontype;
      keyvar = keyvar;
    }
    { Object* upperbound = collectiontree->rest->rest->value;
      boolean unboundedP = (upperbound == SYM_FOREACH_STELLA_NULL) ||
          (upperbound == SYM_FOREACH_STELLA_NULL_INTEGER);
      Symbol* iteratorvar = valuevar;
      Symbol* upperboundvar = NULL;
      Symbol* testoperator = SYM_FOREACH_STELLA_le;

      if (!(unboundedP)) {
        if (consP(upperbound)) {
          { Cons* ub = ((Cons*)(upperbound));

            if ((ub->value == SYM_FOREACH_STELLA_1_) ||
                ((ub->value == SYM_FOREACH_STELLA__) &&
                 (eqlP(ub->rest->value, ONE_WRAPPER) &&
                  (ub->rest->rest->rest == NIL)))) {
              upperbound = ub->rest->value;
              testoperator = SYM_FOREACH_STELLA_l;
            }
          }
        }
        upperbound = sysTree(walkExpressionTree(upperbound, SGT_FOREACH_STELLA_INTEGER, SYM_FOREACH_STELLA_FOREACH, false, dummy2), SGT_FOREACH_STELLA_INTEGER, dummy1);
        if (!(atomicExpressionP(upperbound))) {
          upperboundvar = localGensym("UPPER-BOUND");
        }
      }
      { Cons* _Return0 = cons(cons(iteratorvar, listO(3, SGT_FOREACH_STELLA_INTEGER, collectiontree->rest->value, NIL)), ((((boolean)(upperboundvar)) ? cons(cons(upperboundvar, listO(3, SGT_FOREACH_STELLA_INTEGER, upperbound, NIL)), NIL) : NIL))->concatenate(NIL, 0));

        _Return1 = NIL;
        _Return2 = cons(listO(3, SYM_FOREACH_STELLA_ii, iteratorvar, NIL), NIL);
        _Return3 = (unboundedP ? ((StandardObject*)(SYM_FOREACH_STELLA_TRUE)) : ((StandardObject*)(cons(testoperator, cons(iteratorvar, cons((((boolean)(upperboundvar)) ? upperboundvar : upperbound), NIL))))));
        return (_Return0);
      }
    }
  }
}

Cons* yieldInCursorClausesForVector(Object* collectiontree, StandardObject* collectiontype, Symbol* keyvar, Symbol* valuevar, Cons*& _Return1, Cons*& _Return2, Object*& _Return3) {
  { boolean dummy1;

    if (((boolean)(keyvar))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal key variable specified for " << "`" << deUglifyParseTree(collectiontype) << "'" << "." << std::endl;
        }
      }
      _Return1 = NIL;
      _Return2 = NIL;
      _Return3 = SYM_FOREACH_STELLA_FALSE;
      return (NIL);
    }
    { Symbol* vectorvar = localGensym("VECTOR");
      Symbol* indexvar = localGensym("INDEX");
      Symbol* lengthvar = localGensym("LENGTH");

      { Cons* _Return0 = listO(5, cons(valuevar, cons((((collectiontype == SGT_FOREACH_STELLA_STRING) ||
            (collectiontype == SGT_FOREACH_STELLA_MUTABLE_STRING)) ? SGT_FOREACH_STELLA_CHARACTER : ((StandardObject*)(extractParameterType(collectiontype, SYM_FOREACH_STELLA_ANY_VALUE, dummy1)))), cons(SYM_FOREACH_STELLA_NULL, NIL))), cons(vectorvar, cons(collectiontype, cons(collectiontree, NIL))), cons(indexvar, listO(3, SGT_FOREACH_STELLA_INTEGER, wrapInteger(0), NIL)), cons(lengthvar, listO(3, SGT_FOREACH_STELLA_INTEGER, listO(3, SYM_FOREACH_STELLA_LENGTH, vectorvar, NIL), NIL)), NIL);

        _Return1 = cons(listO(3, SYM_FOREACH_STELLA_SETQ, valuevar, cons(listO(3, SYM_FOREACH_STELLA_NTH, vectorvar, cons(indexvar, NIL)), NIL)), NIL);
        _Return2 = cons(listO(3, SYM_FOREACH_STELLA_ii, indexvar, NIL), NIL);
        _Return3 = listO(3, SYM_FOREACH_STELLA_l, indexvar, cons(lengthvar, NIL));
        return (_Return0);
      }
    }
  }
}

Cons* yieldInCursorClausesForArgumentList(Object* collectiontree, StandardObject* collectiontype, Symbol* keyvar, Symbol* valuevar, Cons*& _Return1, Cons*& _Return2, Object*& _Return3) {
  { boolean dummy1;
    StandardObject* dummy2;
    boolean dummy3;
    StandardObject* dummy4;

    if (((boolean)(keyvar))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal key variable specified for " << "`" << deUglifyParseTree(collectiontype) << "'" << "." << std::endl;
        }
      }
      _Return1 = NIL;
      _Return2 = NIL;
      _Return3 = SYM_FOREACH_STELLA_FALSE;
      return (NIL);
    }
    if (!passVariableArgumentsAsListP(oMETHODBEINGWALKEDo)) {
      { ParametricTypeSpecifier* self000 = newParametricTypeSpecifier();

        self000->specifierBaseType = SGT_FOREACH_STELLA_ARGUMENT_LIST_ITERATOR;
        self000->specifierParameterTypes = list(1, extractParameterType(collectiontype, SYM_FOREACH_STELLA_ANY_VALUE, dummy1));
        { ParametricTypeSpecifier* iteratortype = self000;

          return (yieldInCursorClausesForGeneralCollection(sysTree(listO(5, SYM_FOREACH_STELLA_SYS_CALL_METHOD, SGT_FOREACH_STELLA_ARGUMENT_LIST_ITERATOR, SYM_FOREACH_STELLA_ALLOCATE_ITERATOR, walkWithoutTypeTree(collectiontree), NIL), iteratortype, dummy2), iteratortype, keyvar, valuevar, _Return1, _Return2, _Return3));
        }
      }
    }
    { StandardObject* listifiedtype = yieldListifiedVariableArgumentsType(oMETHODBEINGWALKEDo);
      StandardObject* elementtype = extractParameterType(collectiontype, SYM_FOREACH_STELLA_ANY_VALUE, dummy3);

      { Cons* iteratorclauses = NULL;
        Cons* valueclauses = NULL;
        Cons* bumpclauses = NULL;
        Object* continuationtest = NULL;

        iteratorclauses = yieldInCursorClausesForGeneralCollection(sysTree(collectiontree, listifiedtype, dummy4), listifiedtype, keyvar, valuevar, valueclauses, bumpclauses, continuationtest);
        if (subTypeSpecOfP(elementtype, SGT_FOREACH_STELLA_LITERAL)) {
          { Cons* clause = NULL;
            Cons* iter000 = ((Cons*)(iteratorclauses));

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              clause = ((Cons*)(iter000->value));
              if (clause->value == valuevar) {
                clause->secondSetter(elementtype);
                break;
              }
            }
          }
        }
        _Return1 = valueclauses;
        _Return2 = bumpclauses;
        _Return3 = continuationtest;
        return (iteratorclauses);
      }
    }
  }
}

Cons* yieldOnCursorClauses(Cons* ontree, Cons*& _Return1, Cons*& _Return2, Object*& _Return3) {
  { Object* iteratorvar = ontree->rest->value;

    if (!symbolP(iteratorvar)) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal ON clause with non-atomic variable: " << "`" << deUglifyParseTree(ontree) << "'" << "." << std::endl;
        }
      }
      _Return1 = NIL;
      _Return2 = NIL;
      _Return3 = SYM_FOREACH_STELLA_FALSE;
      return (NIL);
    }
    { Object* collectiontree = NULL;
      StandardObject* collectiontype = NULL;

      collectiontree = walkCollectionTree(ontree->rest->rest->value, true, collectiontype);
      if (subTypeSpecOfP(collectiontype, SGT_FOREACH_STELLA_ARGUMENT_LIST)) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "ON iteration not supported for ARGUMENT-LISTs: " << "`" << deUglifyParseTree(ontree) << "'" << "." << std::endl;
          }
        }
        _Return1 = NIL;
        _Return2 = NIL;
        _Return3 = SYM_FOREACH_STELLA_FALSE;
        return (NIL);
      }
      ontree->thirdSetter(NULL);
      if (!safeSubtypeOfP(typeSpecToBaseType(collectiontype), SGT_FOREACH_STELLA_ABSTRACT_ITERATOR)) {
        collectiontree = listO(3, SYM_FOREACH_STELLA_ALLOCATE_ITERATOR, collectiontree, NIL);
      }
      { Cons* _Return0 = cons(cons(iteratorvar, listO(3, SGT_FOREACH_STELLA_ABSTRACT_ITERATOR, collectiontree, NIL)), NIL);

        _Return1 = NIL;
        _Return2 = NIL;
        _Return3 = listO(3, SYM_FOREACH_STELLA_NEXTp, iteratorvar, NIL);
        return (_Return0);
      }
    }
  }
}

Cons* collectCursorClauses(Cons* cursorstree, boolean dontoptimizeP, Cons*& _Return1, Cons*& _Return2, Object*& _Return3) {
  { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(cursorstree->value));

    if (testValue000 == SYM_FOREACH_STELLA_IN) {
      return (yieldInCursorClauses(cursorstree, dontoptimizeP, _Return1, _Return2, _Return3));
    }
    else if (testValue000 == SYM_FOREACH_STELLA_ON) {
      return (yieldOnCursorClauses(cursorstree, _Return1, _Return2, _Return3));
    }
    else if (testValue000 == SYM_FOREACH_STELLA_AS) {
      { Cons* alliteratorclauses = NIL;
        Cons* allvalueclauses = NIL;
        Cons* allbumpclauses = NIL;
        Cons* continuationtests = NIL;

        { Object* clause = NULL;
          Cons* iter000 = cursorstree->rest;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            clause = iter000->value;
            { Cons* iteratorclauses = NULL;
              Cons* valueclauses = NULL;
              Cons* bumpclauses = NULL;
              Object* continuationtest = NULL;

              iteratorclauses = collectCursorClauses(((Cons*)(clause)), dontoptimizeP, valueclauses, bumpclauses, continuationtest);
              alliteratorclauses = alliteratorclauses->concatenate(iteratorclauses, 0);
              allvalueclauses = allvalueclauses->concatenate(valueclauses, 0);
              allbumpclauses = allbumpclauses->concatenate(bumpclauses, 0);
              continuationtests = cons(continuationtest, continuationtests);
            }
          }
        }
        { Cons* _Return0 = alliteratorclauses;

          _Return1 = allvalueclauses;
          _Return2 = allbumpclauses;
          _Return3 = ((continuationtests->length() == 1) ? continuationtests->value : cons(SYM_FOREACH_STELLA_AND, continuationtests->reverse()->remove(SYM_FOREACH_STELLA_TRUE)->concatenate(NIL, 0)));
          return (_Return0);
        }
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Cons* walkCursorsTree(Cons* cursorstree, boolean dontoptimizeP, Cons*& _Return1, Cons*& _Return2, Object*& _Return3) {
  { StandardObject* dummy1;

    { Cons* iteratorclauses = NULL;
      Cons* valueclauses = NULL;
      Cons* bumpclauses = NULL;
      Object* continuationtest = NULL;

      iteratorclauses = collectCursorClauses(cursorstree, dontoptimizeP, valueclauses, bumpclauses, continuationtest);
      { Cons* clause = NULL;
        Cons* iter000 = ((Cons*)(iteratorclauses));

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          clause = ((Cons*)(iter000->value));
          { Object* iteratortree = NULL;
            StandardObject* iteratortype = NULL;

            iteratortree = walkExpressionTree(clause->rest->rest->value, ((StandardObject*)(clause->rest->value)), SYM_FOREACH_STELLA_FOREACH, false, iteratortype);
            clause->secondSetter(iteratortype);
            clause->thirdSetter(coerceATree(iteratortree, iteratortype, iteratortype, dummy1));
          }
          pushVariableBinding(((Symbol*)(clause->value)), ((StandardObject*)(clause->rest->value)));
        }
      }
      valueclauses = walkListOfTrees(valueclauses);
      bumpclauses = walkListOfTrees(bumpclauses);
      continuationtest = walkWithoutTypeTree(continuationtest);
      { int i = NULL_INTEGER;
        int iter001 = 1;
        int upperBound000 = iteratorclauses->length();

        for  (; iter001 <= upperBound000; 
              iter001 = iter001 + 1) {
          i = iter001;
          i = i;
          popVariableBinding();
        }
      }
      _Return1 = valueclauses;
      _Return2 = bumpclauses;
      _Return3 = continuationtest;
      return (iteratorclauses);
    }
  }
}

Cons* yieldCollectIntoListCode(Symbol* collectvariable, Object* intovariable, Object* collecttree) {
  return (cons(listO(5, SYM_FOREACH_STELLA_IF, listO(3, SYM_FOREACH_STELLA_NULLp, collectvariable, NIL), listO(4, SYM_FOREACH_STELLA_PROGN, listO(3, SYM_FOREACH_STELLA_SETQ, collectvariable, cons(listO(3, SYM_FOREACH_STELLA_CONS, collecttree, cons(SYM_FOREACH_STELLA_NIL, NIL)), NIL)), listO(5, SYM_FOREACH_STELLA_IF, listO(3, SYM_FOREACH_STELLA_EMPTYp, listO(3, SYM_FOREACH_STELLA_THE_CONS_LIST, intovariable, NIL), NIL), listO(4, SYM_FOREACH_STELLA_SETF, listO(3, SYM_FOREACH_STELLA_THE_CONS_LIST, intovariable, NIL), collectvariable, NIL), listO(4, SYM_FOREACH_STELLA_ADD_CONS_TO_END_OF_CONS_LIST, listO(3, SYM_FOREACH_STELLA_THE_CONS_LIST, intovariable, NIL), collectvariable, NIL), NIL), NIL), listO(4, SYM_FOREACH_STELLA_PROGN, listO(4, SYM_FOREACH_STELLA_SETF, listO(3, SYM_FOREACH_STELLA_REST, collectvariable, NIL), listO(3, SYM_FOREACH_STELLA_CONS, copyConsTree(collecttree), cons(SYM_FOREACH_STELLA_NIL, NIL)), NIL), listO(3, SYM_FOREACH_STELLA_SETQ, collectvariable, cons(listO(3, SYM_FOREACH_STELLA_REST, collectvariable, NIL), NIL)), NIL), NIL), NIL));
}

Cons* yieldCollectIntoConsCode(Symbol* collectvariable, Object* intovariable, Object* collecttree) {
  return (cons(listO(5, SYM_FOREACH_STELLA_IF, listO(3, SYM_FOREACH_STELLA_NULLp, collectvariable, NIL), listO(4, SYM_FOREACH_STELLA_PROGN, listO(3, SYM_FOREACH_STELLA_SETQ, collectvariable, cons(listO(3, SYM_FOREACH_STELLA_CONS, collecttree, cons(SYM_FOREACH_STELLA_NIL, NIL)), NIL)), listO(5, SYM_FOREACH_STELLA_IF, listO(3, SYM_FOREACH_STELLA_NILp, intovariable, NIL), listO(3, SYM_FOREACH_STELLA_SETQ, intovariable, cons(collectvariable, NIL)), listO(3, SYM_FOREACH_STELLA_ADD_CONS_TO_END_OF_CONS_LIST, intovariable, cons(collectvariable, NIL)), NIL), NIL), listO(4, SYM_FOREACH_STELLA_PROGN, listO(4, SYM_FOREACH_STELLA_SETF, listO(3, SYM_FOREACH_STELLA_REST, collectvariable, NIL), listO(3, SYM_FOREACH_STELLA_CONS, copyConsTree(collecttree), cons(SYM_FOREACH_STELLA_NIL, NIL)), NIL), listO(3, SYM_FOREACH_STELLA_SETQ, collectvariable, cons(listO(3, SYM_FOREACH_STELLA_REST, collectvariable, NIL), NIL)), NIL), NIL), NIL));
}

Cons* yieldCollectCode(Symbol* collectvariable, Object* intovariable, Object* collecttree) {
  { StandardObject* dummy1;

    { Surrogate* intovariabletype = typeSpecToBaseType(lookupVariableType(((Symbol*)(intovariable))));

      if (subtypeOfP(intovariabletype, SGT_FOREACH_STELLA_LIST)) {
        return (yieldCollectIntoListCode(collectvariable, intovariable, collecttree));
      }
      else if (subtypeOfP(intovariabletype, SGT_FOREACH_STELLA_CONS)) {
        return (yieldCollectIntoConsCode(collectvariable, intovariable, collecttree));
      }
      else if (intovariabletype == SGT_FOREACH_STELLA_UNKNOWN) {
        return (cons(listO(5, SYM_FOREACH_STELLA_IF, listO(3, SYM_FOREACH_STELLA_NULLp, collectvariable, NIL), listO(4, SYM_FOREACH_STELLA_PROGN, listO(3, SYM_FOREACH_STELLA_SETQ, collectvariable, cons(listO(3, SYM_FOREACH_STELLA_CONS, collecttree, cons(SYM_FOREACH_STELLA_NIL, NIL)), NIL)), listO(5, SYM_FOREACH_STELLA_COND, listO(3, listO(3, SYM_FOREACH_STELLA_NILp, intovariable, NIL), listO(3, SYM_FOREACH_STELLA_SETQ, intovariable, cons(collectvariable, NIL)), NIL), listO(3, listO(3, SYM_FOREACH_STELLA_CONSp, intovariable, NIL), listO(3, SYM_FOREACH_STELLA_ADD_CONS_TO_END_OF_CONS_LIST, intovariable, cons(collectvariable, NIL)), NIL), listO(3, SYM_FOREACH_STELLA_OTHERWISE, listO(5, SYM_FOREACH_STELLA_IF, listO(3, SYM_FOREACH_STELLA_EMPTYp, listO(3, SYM_FOREACH_STELLA_THE_CONS_LIST, intovariable, NIL), NIL), listO(4, SYM_FOREACH_STELLA_SETF, listO(3, SYM_FOREACH_STELLA_THE_CONS_LIST, intovariable, NIL), collectvariable, NIL), listO(4, SYM_FOREACH_STELLA_ADD_CONS_TO_END_OF_CONS_LIST, listO(3, SYM_FOREACH_STELLA_THE_CONS_LIST, intovariable, NIL), collectvariable, NIL), NIL), NIL), NIL), NIL), listO(4, SYM_FOREACH_STELLA_PROGN, listO(4, SYM_FOREACH_STELLA_SETF, listO(3, SYM_FOREACH_STELLA_REST, collectvariable, NIL), listO(3, SYM_FOREACH_STELLA_CONS, copyConsTree(collecttree), cons(SYM_FOREACH_STELLA_NIL, NIL)), NIL), listO(3, SYM_FOREACH_STELLA_SETQ, collectvariable, cons(listO(3, SYM_FOREACH_STELLA_REST, collectvariable, NIL), NIL)), NIL), NIL), NIL));
      }
      else {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Can't collect into a datatype other than LIST or CONS." << "." << std::endl;
          }
        }
        return (walkDontCallMeTree(collecttree, SGT_FOREACH_STELLA_VOID, dummy1));
      }
    }
  }
}

Cons* walkPrefixCollectIntoTree(Cons* collectintotree, Cons* iterators, Cons* docode, Cons*& _Return1) {
  { Object* collecttree = collectintotree->rest->value;
    Object* intotree = collectintotree->rest->rest->value;
    Symbol* collectvariable = localGensym("COLLECT");
    Cons* collectintobindings = cons(cons(collectvariable, listO(3, SGT_FOREACH_STELLA_CONS, SYM_FOREACH_STELLA_NULL, NIL)), NIL);
    Cons* collectcode = NULL;
    Symbol* intovariable = NULL;
    StandardObject* intovariabletype = NULL;

    if (symbolP(intotree)) {
      {
        intovariable = ((Symbol*)(intotree));
        collectcode = yieldCollectCode(collectvariable, intovariable, collecttree);
      }
    }
    else {
      {
        { Cons* d = NULL;
          Cons* iter000 = iterators;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            d = ((Cons*)(iter000->value));
            pushVariableBinding(((Symbol*)(d->value)), ((StandardObject*)(d->rest->value)));
          }
        }
        intotree = walkExpressionTree(intotree, NULL, SYM_FOREACH_STELLA_FOREACH, false, intovariabletype);
        { Cons* d = NULL;
          Cons* iter001 = iterators;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            d = ((Cons*)(iter001->value));
            d = d;
            popVariableBinding();
          }
        }
        intovariable = localGensym("INTO");
        collectintobindings = cons(consList(3, intovariable, intovariabletype, intotree), collectintobindings);
        pushVariableBinding(intovariable, intovariabletype);
        collectcode = yieldCollectCode(collectvariable, intovariable, collecttree);
        popVariableBinding();
      }
    }
    { Cons* _Return0 = iterators->concatenate(collectintobindings, 0);

      _Return1 = docode->concatenate(collectcode, 0);
      return (_Return0);
    }
  }
}

Cons* wrapWhereTest(Object* wheretest, Cons* actions) {
  if (((boolean)(wheretest))) {
    return (cons(listO(3, SYM_FOREACH_STELLA_WHEN, wheretest, actions->concatenate(NIL, 0)), NIL));
  }
  else {
    return (actions);
  }
}

Cons* walkPrefixForeachBody(Cons* iteratorclauses, Object* wheretest, Cons* doactions) {
  { Cons* otree = NULL;

    { Cons* c = NULL;
      Cons* iter000 = ((Cons*)(iteratorclauses));

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        c = ((Cons*)(iter000->value));
        pushVariableBinding(((Symbol*)(c->value)), ((StandardObject*)(c->rest->value)));
        c->firstSetter(trueVariableName(((Symbol*)(c->value))));
      }
    }
    otree = walkListOfTrees(wrapWhereTest(wheretest, doactions));
    { Object* c = NULL;
      Cons* iter001 = iteratorclauses;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        c = iter001->value;
        c = c;
        popVariableBinding();
      }
    }
    return (otree);
  }
}

Cons* walkPrefixForeachTree(Cons* tree, StandardObject*& _Return1) {
  { Cons* tail = NULL;
    Cons* iteratorclauses = NULL;
    Cons* valueclauses = NULL;
    Cons* bumpclauses = NULL;
    Object* continuationtest = NULL;
    Object* wheretest = NULL;
    Cons* doactions = NIL;

    iteratorclauses = walkCursorsTree(((Cons*)(tree->rest->value)), false, valueclauses, bumpclauses, continuationtest);
    tail = ((Cons*)(tree->rest->rest));
    if (((Cons*)(tail->value))->value == SYM_FOREACH_STELLA_WHERE) {
      wheretest = ((Cons*)(tail->value))->rest->value;
      tail = tail->rest;
    }
    if (((Cons*)(tail->value))->value == SYM_FOREACH_STELLA_DO) {
      doactions = ((Cons*)(tail->value))->rest;
      tail = tail->rest;
    }
    if (!(tail == NIL)) {
      iteratorclauses = walkPrefixCollectIntoTree(((Cons*)(tail->value)), iteratorclauses, doactions, doactions);
    }
    { Cons* _Return0 = listO(3, SYM_FOREACH_STELLA_SYS_FOREACH, iteratorclauses, cons(valueclauses, cons(bumpclauses, cons(continuationtest, walkPrefixForeachBody(iteratorclauses, wheretest, doactions)->concatenate(NIL, 0)))));

      _Return1 = SGT_FOREACH_STELLA_VOID;
      return (_Return0);
    }
  }
}

Cons* walkExistsTree(Cons* tree, StandardObject*& _Return1) {
  { Symbol* foundP = localGensym("FOUND?");
    Cons* otree = listO(5, SYM_FOREACH_STELLA_VRLET, cons(cons(foundP, cons(SYM_FOREACH_STELLA_FALSE, NIL)), NIL), cons(SYM_FOREACH_STELLA_FOREACH, tree->rest->concatenate(listO(4, SYM_FOREACH_STELLA_DO, listO(3, SYM_FOREACH_STELLA_SETQ, foundP, cons(SYM_FOREACH_STELLA_TRUE, NIL)), cons(SYM_FOREACH_STELLA_BREAK, NIL), NIL), 0)), foundP, NIL);

    return (walkAConsTree(otree, _Return1));
  }
}

Cons* walkForallTree(Cons* tree, StandardObject*& _Return1) {
  { Symbol* alwaysP = localGensym("ALWAYS?");
    Cons* iteratorsandwhere = NIL;
    Object* alwaystest = NIL;
    Cons* precursor = NIL;
    Cons* cursor = tree;

    while (!(cursor == NIL)) {
      if (cursor->value == SYM_FOREACH_STELLA_ALWAYS) {
        alwaystest = cursor->rest->value;
        precursor->rest = NIL;
        break;
      }
      precursor = cursor;
      cursor = cursor->rest;
    }
    iteratorsandwhere = tree->rest;
    { Cons* _Return0 = ((Cons*)(listO(5, SYM_FOREACH_STELLA_VRLET, cons(cons(alwaysP, cons(SYM_FOREACH_STELLA_TRUE, NIL)), NIL), cons(SYM_FOREACH_STELLA_FOREACH, iteratorsandwhere->concatenate(listO(3, SYM_FOREACH_STELLA_DO, listO(5, SYM_FOREACH_STELLA_WHEN, listO(3, SYM_FOREACH_STELLA_NOT, alwaystest, NIL), listO(3, SYM_FOREACH_STELLA_SETQ, alwaysP, cons(SYM_FOREACH_STELLA_FALSE, NIL)), cons(SYM_FOREACH_STELLA_BREAK, NIL), NIL), NIL), 0)), alwaysP, NIL)));

      _Return1 = SGT_FOREACH_STELLA_BOOLEAN;
      return (_Return0);
    }
  }
}

Cons* walkSomeTree(Cons* tree, StandardObject*& _Return1) {
  { boolean dummy1;

    { Symbol* valuevar = localGensym("VALUE");
      Object* iterationvar = tree->rest->value;
      Cons* otree = NULL;

      { Object* sequenceref = NULL;
        StandardObject* sequencetype = NULL;

        sequenceref = walkATree(tree->fourth(), sequencetype);
        tree->fourthSetter(sequenceref);
        otree = listO(5, SYM_FOREACH_STELLA_VRLET, cons(cons(valuevar, cons(extractParameterType(sequencetype, SYM_FOREACH_STELLA_ANY_VALUE, dummy1), cons(SYM_FOREACH_STELLA_NULL, NIL))), NIL), cons(SYM_FOREACH_STELLA_FOREACH, tree->rest->concatenate(listO(4, SYM_FOREACH_STELLA_DO, listO(3, SYM_FOREACH_STELLA_SETQ, valuevar, cons(iterationvar, NIL)), cons(SYM_FOREACH_STELLA_BREAK, NIL), NIL), 0)), valuevar, NIL);
        return (walkAConsTree(otree, _Return1));
      }
    }
  }
}

void helpStartupForeach1() {
  {
    SYM_FOREACH_STELLA_AS = ((Symbol*)(internRigidSymbolWrtModule("AS", NULL, 0)));
    SYM_FOREACH_STELLA_COMMA = ((Symbol*)(internRigidSymbolWrtModule("COMMA", NULL, 0)));
    SYM_FOREACH_STELLA_DO = ((Symbol*)(internRigidSymbolWrtModule("DO", NULL, 0)));
    SYM_FOREACH_STELLA_COLLECT = ((Symbol*)(internRigidSymbolWrtModule("COLLECT", NULL, 0)));
    SGT_FOREACH_STELLA_VOID = ((Surrogate*)(internRigidSymbolWrtModule("VOID", NULL, 1)));
    SYM_FOREACH_STELLA_PREFIX_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("PREFIX-FOREACH", NULL, 0)));
    SYM_FOREACH_STELLA_IN = ((Symbol*)(internRigidSymbolWrtModule("IN", NULL, 0)));
    SYM_FOREACH_STELLA_X = ((Symbol*)(internRigidSymbolWrtModule("X", NULL, 0)));
    SYM_FOREACH_STELLA_NIL = ((Symbol*)(internRigidSymbolWrtModule("NIL", NULL, 0)));
    SYM_FOREACH_STELLA_WHERE = ((Symbol*)(internRigidSymbolWrtModule("WHERE", NULL, 0)));
    SYM_FOREACH_STELLA_INTO = ((Symbol*)(internRigidSymbolWrtModule("INTO", NULL, 0)));
    SYM_FOREACH_STELLA_COLLECT_INTO = ((Symbol*)(internRigidSymbolWrtModule("COLLECT-INTO", NULL, 0)));
    SYM_FOREACH_STELLA_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("FOREACH", NULL, 0)));
    SYM_FOREACH_STELLA_EXISTS = ((Symbol*)(internRigidSymbolWrtModule("EXISTS", NULL, 0)));
    SYM_FOREACH_STELLA_FORALL = ((Symbol*)(internRigidSymbolWrtModule("FORALL", NULL, 0)));
    SYM_FOREACH_STELLA_SOME = ((Symbol*)(internRigidSymbolWrtModule("SOME", NULL, 0)));
    SGT_FOREACH_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SYM_FOREACH_STELLA_INTERVAL = ((Symbol*)(internRigidSymbolWrtModule("INTERVAL", NULL, 0)));
    SGT_FOREACH_STELLA_INTEGER_INTERVAL = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER-INTERVAL", NULL, 1)));
    SGT_FOREACH_STELLA_UNKNOWN = ((Surrogate*)(internRigidSymbolWrtModule("UNKNOWN", NULL, 1)));
    SGT_FOREACH_STELLA_ABSTRACT_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("ABSTRACT-ITERATOR", NULL, 1)));
    SYM_FOREACH_STELLA_ALLOCATE_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("ALLOCATE-ITERATOR", NULL, 0)));
    SYM_FOREACH_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", NULL, 0)));
    SGT_FOREACH_STELLA_ARGUMENT_LIST = ((Surrogate*)(internRigidSymbolWrtModule("ARGUMENT-LIST", NULL, 1)));
    SGT_FOREACH_STELLA_STRING = ((Surrogate*)(internRigidSymbolWrtModule("STRING", NULL, 1)));
    SGT_FOREACH_STELLA_MUTABLE_STRING = ((Surrogate*)(internRigidSymbolWrtModule("MUTABLE-STRING", NULL, 1)));
    SGT_FOREACH_STELLA_VECTOR = ((Surrogate*)(internRigidSymbolWrtModule("VECTOR", NULL, 1)));
    SGT_FOREACH_STELLA_SEQUENCE_MIXIN = ((Surrogate*)(internRigidSymbolWrtModule("SEQUENCE-MIXIN", NULL, 1)));
    SYM_FOREACH_STELLA_THE_ARRAY = ((Symbol*)(internRigidSymbolWrtModule("THE-ARRAY", NULL, 0)));
    SGT_FOREACH_STELLA_LIST = ((Surrogate*)(internRigidSymbolWrtModule("LIST", NULL, 1)));
    SYM_FOREACH_STELLA_THE_CONS_LIST = ((Symbol*)(internRigidSymbolWrtModule("THE-CONS-LIST", NULL, 0)));
    SGT_FOREACH_STELLA_KEY_VALUE_LIST = ((Surrogate*)(internRigidSymbolWrtModule("KEY-VALUE-LIST", NULL, 1)));
    SGT_FOREACH_STELLA_KV_CONS = ((Surrogate*)(internRigidSymbolWrtModule("KV-CONS", NULL, 1)));
    SYM_FOREACH_STELLA_THE_KV_LIST = ((Symbol*)(internRigidSymbolWrtModule("THE-KV-LIST", NULL, 0)));
    SGT_FOREACH_STELLA_PROPERTY_LIST = ((Surrogate*)(internRigidSymbolWrtModule("PROPERTY-LIST", NULL, 1)));
    SYM_FOREACH_STELLA_THE_PLIST = ((Symbol*)(internRigidSymbolWrtModule("THE-PLIST", NULL, 0)));
    SYM_FOREACH_STELLA_KEY = ((Symbol*)(internRigidSymbolWrtModule("KEY", NULL, 0)));
    SYM_FOREACH_STELLA_VALUE = ((Symbol*)(internRigidSymbolWrtModule("VALUE", NULL, 0)));
    SYM_FOREACH_STELLA_SETQ = ((Symbol*)(internRigidSymbolWrtModule("SETQ", NULL, 0)));
    SYM_FOREACH_STELLA_REST = ((Symbol*)(internRigidSymbolWrtModule("REST", NULL, 0)));
    SYM_FOREACH_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", NULL, 0)));
    SYM_FOREACH_STELLA_NILp = ((Symbol*)(internRigidSymbolWrtModule("NIL?", NULL, 0)));
    SYM_FOREACH_STELLA_DEFINEDp = ((Symbol*)(internRigidSymbolWrtModule("DEFINED?", NULL, 0)));
    SYM_FOREACH_STELLA_NEXTp = ((Symbol*)(internRigidSymbolWrtModule("NEXT?", NULL, 0)));
    SYM_FOREACH_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
    SYM_FOREACH_STELLA_ANY_VALUE = ((Symbol*)(internRigidSymbolWrtModule("ANY-VALUE", NULL, 0)));
    SYM_FOREACH_STELLA_ANY_KEY = ((Symbol*)(internRigidSymbolWrtModule("ANY-KEY", NULL, 0)));
    SYM_FOREACH_STELLA_NULL_INTEGER = ((Symbol*)(internRigidSymbolWrtModule("NULL-INTEGER", NULL, 0)));
    SGT_FOREACH_STELLA_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER", NULL, 1)));
    SGT_FOREACH_STELLA_NUMBER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER-WRAPPER", NULL, 1)));
    SGT_FOREACH_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 1)));
    SYM_FOREACH_STELLA_NULLp = ((Symbol*)(internRigidSymbolWrtModule("NULL?", NULL, 0)));
    SYM_FOREACH_STELLA_ii = ((Symbol*)(internRigidSymbolWrtModule("++", NULL, 0)));
    SYM_FOREACH_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    SYM_FOREACH_STELLA_le = ((Symbol*)(internRigidSymbolWrtModule("<=", NULL, 0)));
    SYM_FOREACH_STELLA_OR = ((Symbol*)(internRigidSymbolWrtModule("OR", NULL, 0)));
    SYM_FOREACH_STELLA_1_ = ((Symbol*)(internRigidSymbolWrtModule("1-", NULL, 0)));
    SYM_FOREACH_STELLA__ = ((Symbol*)(internRigidSymbolWrtModule("-", NULL, 0)));
    SYM_FOREACH_STELLA_l = ((Symbol*)(internRigidSymbolWrtModule("<", NULL, 0)));
    SYM_FOREACH_STELLA_LENGTH = ((Symbol*)(internRigidSymbolWrtModule("LENGTH", NULL, 0)));
  }
}

void startupForeach() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupForeach1();
      SGT_FOREACH_STELLA_CHARACTER = ((Surrogate*)(internRigidSymbolWrtModule("CHARACTER", NULL, 1)));
      SYM_FOREACH_STELLA_NTH = ((Symbol*)(internRigidSymbolWrtModule("NTH", NULL, 0)));
      SGT_FOREACH_STELLA_ARGUMENT_LIST_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("ARGUMENT-LIST-ITERATOR", NULL, 1)));
      SYM_FOREACH_STELLA_SYS_CALL_METHOD = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-METHOD", NULL, 0)));
      SGT_FOREACH_STELLA_LITERAL = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL", NULL, 1)));
      SYM_FOREACH_STELLA_ON = ((Symbol*)(internRigidSymbolWrtModule("ON", NULL, 0)));
      SYM_FOREACH_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", NULL, 0)));
      SYM_FOREACH_STELLA_IF = ((Symbol*)(internRigidSymbolWrtModule("IF", NULL, 0)));
      SYM_FOREACH_STELLA_PROGN = ((Symbol*)(internRigidSymbolWrtModule("PROGN", NULL, 0)));
      SYM_FOREACH_STELLA_CONS = ((Symbol*)(internRigidSymbolWrtModule("CONS", NULL, 0)));
      SYM_FOREACH_STELLA_EMPTYp = ((Symbol*)(internRigidSymbolWrtModule("EMPTY?", NULL, 0)));
      SYM_FOREACH_STELLA_SETF = ((Symbol*)(internRigidSymbolWrtModule("SETF", NULL, 0)));
      SYM_FOREACH_STELLA_ADD_CONS_TO_END_OF_CONS_LIST = ((Symbol*)(internRigidSymbolWrtModule("ADD-CONS-TO-END-OF-CONS-LIST", NULL, 0)));
      SYM_FOREACH_STELLA_COND = ((Symbol*)(internRigidSymbolWrtModule("COND", NULL, 0)));
      SYM_FOREACH_STELLA_CONSp = ((Symbol*)(internRigidSymbolWrtModule("CONS?", NULL, 0)));
      SYM_FOREACH_STELLA_OTHERWISE = ((Symbol*)(internRigidSymbolWrtModule("OTHERWISE", NULL, 0)));
      SYM_FOREACH_STELLA_WHEN = ((Symbol*)(internRigidSymbolWrtModule("WHEN", NULL, 0)));
      SYM_FOREACH_STELLA_SYS_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("SYS-FOREACH", NULL, 0)));
      SYM_FOREACH_STELLA_VRLET = ((Symbol*)(internRigidSymbolWrtModule("VRLET", NULL, 0)));
      SYM_FOREACH_STELLA_BREAK = ((Symbol*)(internRigidSymbolWrtModule("BREAK", NULL, 0)));
      SYM_FOREACH_STELLA_ALWAYS = ((Symbol*)(internRigidSymbolWrtModule("ALWAYS", NULL, 0)));
      SYM_FOREACH_STELLA_STARTUP_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-FOREACH", NULL, 0)));
      SYM_FOREACH_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("EXTRACT-ONE-IN-CLAUSE", "(DEFUN (EXTRACT-ONE-IN-CLAUSE CONS CONS) ((TAIL CONS)))", ((cpp_function_code)(&extractOneInClause)), NULL);
      defineFunctionObject("EXTRACT-ONE-GENERATOR-TERM", "(DEFUN (EXTRACT-ONE-GENERATOR-TERM CONS CONS) ((TAIL CONS)))", ((cpp_function_code)(&extractOneGeneratorTerm)), NULL);
      defineFunctionObject("EXTRACT-GENERATORS-CLAUSE", "(DEFUN (EXTRACT-GENERATORS-CLAUSE CONS CONS) ((TAIL CONS)) :PUBLIC? TRUE)", ((cpp_function_code)(&extractGeneratorsClause)), NULL);
      defineFunctionObject("EXTRACT-OPTION-AND-RESIDUE", "(DEFUN (EXTRACT-OPTION-AND-RESIDUE OBJECT CONS) ((OPTION SYMBOL) (TAIL CONS)) :PUBLIC? TRUE)", ((cpp_function_code)(&extractOptionAndResidue)), NULL);
      defineFunctionObject("EXTRACT-DO-CLAUSE", "(DEFUN (EXTRACT-DO-CLAUSE CONS CONS) ((TAIL CONS)))", ((cpp_function_code)(&extractDoClause)), NULL);
      defineFunctionObject("FOREACH-TO-PREFIX-FOREACH-TREE", "(DEFUN (FOREACH-TO-PREFIX-FOREACH-TREE CONS) ((FOREACHTREE CONS)))", ((cpp_function_code)(&foreachToPrefixForeachTree)), NULL);
      defineFunctionObject("WALK-FOREACH-TREE", "(DEFUN (WALK-FOREACH-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkForeachTree)), NULL);
      defineFunctionObject("WALK-COLLECTION-TREE", "(DEFUN (WALK-COLLECTION-TREE OBJECT TYPE-SPEC) ((TREE OBJECT) (DONTOPTIMIZE? BOOLEAN)))", ((cpp_function_code)(&walkCollectionTree)), NULL);
      defineFunctionObject("YIELD-IN-CURSOR-CLAUSES", "(DEFUN (YIELD-IN-CURSOR-CLAUSES CONS CONS CONS OBJECT) ((INTREE CONS) (DONTOPTIMIZE? BOOLEAN)))", ((cpp_function_code)(&yieldInCursorClauses)), NULL);
      defineFunctionObject("USE-VECTOR-STYLE-ITERATION?", "(DEFUN (USE-VECTOR-STYLE-ITERATION? BOOLEAN) ((COLLECTIONTYPE TYPE)))", ((cpp_function_code)(&useVectorStyleIterationP)), NULL);
      defineFunctionObject("YIELD-IN-CURSOR-CLAUSES-FOR-GENERAL-COLLECTION", "(DEFUN (YIELD-IN-CURSOR-CLAUSES-FOR-GENERAL-COLLECTION CONS CONS CONS OBJECT) ((COLLECTIONTREE OBJECT) (COLLECTIONTYPE TYPE-SPEC) (KEYVAR SYMBOL) (VALUEVAR SYMBOL)))", ((cpp_function_code)(&yieldInCursorClausesForGeneralCollection)), NULL);
      defineFunctionObject("YIELD-IN-CURSOR-CLAUSES-FOR-INTEGER-INTERVAL", "(DEFUN (YIELD-IN-CURSOR-CLAUSES-FOR-INTEGER-INTERVAL CONS CONS CONS OBJECT) ((COLLECTIONTREE CONS) (COLLECTIONTYPE TYPE-SPEC) (KEYVAR SYMBOL) (VALUEVAR SYMBOL)))", ((cpp_function_code)(&yieldInCursorClausesForIntegerInterval)), NULL);
      defineFunctionObject("YIELD-OPTIMIZED-IN-CURSOR-CLAUSES-FOR-INTEGER-INTERVAL", "(DEFUN (YIELD-OPTIMIZED-IN-CURSOR-CLAUSES-FOR-INTEGER-INTERVAL CONS CONS CONS OBJECT) ((COLLECTIONTREE CONS) (COLLECTIONTYPE TYPE-SPEC) (KEYVAR SYMBOL) (VALUEVAR SYMBOL)))", ((cpp_function_code)(&yieldOptimizedInCursorClausesForIntegerInterval)), NULL);
      defineFunctionObject("YIELD-IN-CURSOR-CLAUSES-FOR-VECTOR", "(DEFUN (YIELD-IN-CURSOR-CLAUSES-FOR-VECTOR CONS CONS CONS OBJECT) ((COLLECTIONTREE OBJECT) (COLLECTIONTYPE TYPE-SPEC) (KEYVAR SYMBOL) (VALUEVAR SYMBOL)))", ((cpp_function_code)(&yieldInCursorClausesForVector)), NULL);
      defineFunctionObject("YIELD-IN-CURSOR-CLAUSES-FOR-ARGUMENT-LIST", "(DEFUN (YIELD-IN-CURSOR-CLAUSES-FOR-ARGUMENT-LIST CONS CONS CONS OBJECT) ((COLLECTIONTREE OBJECT) (COLLECTIONTYPE TYPE-SPEC) (KEYVAR SYMBOL) (VALUEVAR SYMBOL)))", ((cpp_function_code)(&yieldInCursorClausesForArgumentList)), NULL);
      defineFunctionObject("YIELD-ON-CURSOR-CLAUSES", "(DEFUN (YIELD-ON-CURSOR-CLAUSES CONS CONS CONS OBJECT) ((ONTREE CONS)))", ((cpp_function_code)(&yieldOnCursorClauses)), NULL);
      defineFunctionObject("COLLECT-CURSOR-CLAUSES", "(DEFUN (COLLECT-CURSOR-CLAUSES CONS CONS CONS OBJECT) ((CURSORSTREE CONS) (DONTOPTIMIZE? BOOLEAN)))", ((cpp_function_code)(&collectCursorClauses)), NULL);
      defineFunctionObject("WALK-CURSORS-TREE", "(DEFUN (WALK-CURSORS-TREE CONS CONS CONS OBJECT) ((CURSORSTREE CONS) (DONTOPTIMIZE? BOOLEAN)))", ((cpp_function_code)(&walkCursorsTree)), NULL);
      defineFunctionObject("YIELD-COLLECT-INTO-LIST-CODE", "(DEFUN (YIELD-COLLECT-INTO-LIST-CODE CONS) ((COLLECTVARIABLE SYMBOL) (INTOVARIABLE OBJECT) (COLLECTTREE OBJECT)))", ((cpp_function_code)(&yieldCollectIntoListCode)), NULL);
      defineFunctionObject("YIELD-COLLECT-INTO-CONS-CODE", "(DEFUN (YIELD-COLLECT-INTO-CONS-CODE CONS) ((COLLECTVARIABLE SYMBOL) (INTOVARIABLE OBJECT) (COLLECTTREE OBJECT)))", ((cpp_function_code)(&yieldCollectIntoConsCode)), NULL);
      defineFunctionObject("YIELD-COLLECT-CODE", "(DEFUN (YIELD-COLLECT-CODE CONS) ((COLLECTVARIABLE SYMBOL) (INTOVARIABLE OBJECT) (COLLECTTREE OBJECT)))", ((cpp_function_code)(&yieldCollectCode)), NULL);
      defineFunctionObject("WALK-PREFIX-COLLECT-INTO-TREE", "(DEFUN (WALK-PREFIX-COLLECT-INTO-TREE CONS CONS) ((COLLECTINTOTREE CONS) (ITERATORS (CONS OF CONS)) (DOCODE CONS)))", ((cpp_function_code)(&walkPrefixCollectIntoTree)), NULL);
      defineFunctionObject("WRAP-WHERE-TEST", "(DEFUN (WRAP-WHERE-TEST CONS) ((WHERETEST OBJECT) (ACTIONS CONS)))", ((cpp_function_code)(&wrapWhereTest)), NULL);
      defineFunctionObject("WALK-PREFIX-FOREACH-BODY", "(DEFUN (WALK-PREFIX-FOREACH-BODY CONS) ((ITERATORCLAUSES CONS) (WHERETEST OBJECT) (DOACTIONS CONS)))", ((cpp_function_code)(&walkPrefixForeachBody)), NULL);
      defineFunctionObject("WALK-PREFIX-FOREACH-TREE", "(DEFUN (WALK-PREFIX-FOREACH-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkPrefixForeachTree)), NULL);
      defineFunctionObject("WALK-EXISTS-TREE", "(DEFUN (WALK-EXISTS-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkExistsTree)), NULL);
      defineFunctionObject("WALK-FORALL-TREE", "(DEFUN (WALK-FORALL-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkForallTree)), NULL);
      defineFunctionObject("WALK-SOME-TREE", "(DEFUN (WALK-SOME-TREE CONS TYPE-SPEC) ((TREE CONS)))", ((cpp_function_code)(&walkSomeTree)), NULL);
      defineFunctionObject("STARTUP-FOREACH", "(DEFUN STARTUP-FOREACH () :PUBLIC? TRUE)", ((cpp_function_code)(&startupForeach)), NULL);
      { MethodSlot* function = lookupFunction(SYM_FOREACH_STELLA_STARTUP_FOREACH);

        setDynamicSlotValue(function->dynamicSlots, SYM_FOREACH_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupForeach"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *AGGRESSIVELY-OPTIMIZE-INTERVAL-FOREACH?* BOOLEAN FALSE)", &oAGGRESSIVELY_OPTIMIZE_INTERVAL_FOREACHpo);
    }
  }
}

Symbol* SYM_FOREACH_STELLA_AS = NULL;

Symbol* SYM_FOREACH_STELLA_COMMA = NULL;

Symbol* SYM_FOREACH_STELLA_DO = NULL;

Symbol* SYM_FOREACH_STELLA_COLLECT = NULL;

Surrogate* SGT_FOREACH_STELLA_VOID = NULL;

Symbol* SYM_FOREACH_STELLA_PREFIX_FOREACH = NULL;

Symbol* SYM_FOREACH_STELLA_IN = NULL;

Symbol* SYM_FOREACH_STELLA_X = NULL;

Symbol* SYM_FOREACH_STELLA_NIL = NULL;

Symbol* SYM_FOREACH_STELLA_WHERE = NULL;

Symbol* SYM_FOREACH_STELLA_INTO = NULL;

Symbol* SYM_FOREACH_STELLA_COLLECT_INTO = NULL;

Symbol* SYM_FOREACH_STELLA_FOREACH = NULL;

Symbol* SYM_FOREACH_STELLA_EXISTS = NULL;

Symbol* SYM_FOREACH_STELLA_FORALL = NULL;

Symbol* SYM_FOREACH_STELLA_SOME = NULL;

Surrogate* SGT_FOREACH_STELLA_CONS = NULL;

Symbol* SYM_FOREACH_STELLA_INTERVAL = NULL;

Surrogate* SGT_FOREACH_STELLA_INTEGER_INTERVAL = NULL;

Surrogate* SGT_FOREACH_STELLA_UNKNOWN = NULL;

Surrogate* SGT_FOREACH_STELLA_ABSTRACT_ITERATOR = NULL;

Symbol* SYM_FOREACH_STELLA_ALLOCATE_ITERATOR = NULL;

Symbol* SYM_FOREACH_STELLA_FALSE = NULL;

Surrogate* SGT_FOREACH_STELLA_ARGUMENT_LIST = NULL;

Surrogate* SGT_FOREACH_STELLA_STRING = NULL;

Surrogate* SGT_FOREACH_STELLA_MUTABLE_STRING = NULL;

Surrogate* SGT_FOREACH_STELLA_VECTOR = NULL;

Surrogate* SGT_FOREACH_STELLA_SEQUENCE_MIXIN = NULL;

Symbol* SYM_FOREACH_STELLA_THE_ARRAY = NULL;

Surrogate* SGT_FOREACH_STELLA_LIST = NULL;

Symbol* SYM_FOREACH_STELLA_THE_CONS_LIST = NULL;

Surrogate* SGT_FOREACH_STELLA_KEY_VALUE_LIST = NULL;

Surrogate* SGT_FOREACH_STELLA_KV_CONS = NULL;

Symbol* SYM_FOREACH_STELLA_THE_KV_LIST = NULL;

Surrogate* SGT_FOREACH_STELLA_PROPERTY_LIST = NULL;

Symbol* SYM_FOREACH_STELLA_THE_PLIST = NULL;

Symbol* SYM_FOREACH_STELLA_KEY = NULL;

Symbol* SYM_FOREACH_STELLA_VALUE = NULL;

Symbol* SYM_FOREACH_STELLA_SETQ = NULL;

Symbol* SYM_FOREACH_STELLA_REST = NULL;

Symbol* SYM_FOREACH_STELLA_NOT = NULL;

Symbol* SYM_FOREACH_STELLA_NILp = NULL;

Symbol* SYM_FOREACH_STELLA_DEFINEDp = NULL;

Symbol* SYM_FOREACH_STELLA_NEXTp = NULL;

Symbol* SYM_FOREACH_STELLA_NULL = NULL;

Symbol* SYM_FOREACH_STELLA_ANY_VALUE = NULL;

Symbol* SYM_FOREACH_STELLA_ANY_KEY = NULL;

Symbol* SYM_FOREACH_STELLA_NULL_INTEGER = NULL;

Surrogate* SGT_FOREACH_STELLA_INTEGER = NULL;

Surrogate* SGT_FOREACH_STELLA_NUMBER_WRAPPER = NULL;

Surrogate* SGT_FOREACH_STELLA_BOOLEAN = NULL;

Symbol* SYM_FOREACH_STELLA_NULLp = NULL;

Symbol* SYM_FOREACH_STELLA_ii = NULL;

Symbol* SYM_FOREACH_STELLA_TRUE = NULL;

Symbol* SYM_FOREACH_STELLA_le = NULL;

Symbol* SYM_FOREACH_STELLA_OR = NULL;

Symbol* SYM_FOREACH_STELLA_1_ = NULL;

Symbol* SYM_FOREACH_STELLA__ = NULL;

Symbol* SYM_FOREACH_STELLA_l = NULL;

Symbol* SYM_FOREACH_STELLA_LENGTH = NULL;

Surrogate* SGT_FOREACH_STELLA_CHARACTER = NULL;

Symbol* SYM_FOREACH_STELLA_NTH = NULL;

Surrogate* SGT_FOREACH_STELLA_ARGUMENT_LIST_ITERATOR = NULL;

Symbol* SYM_FOREACH_STELLA_SYS_CALL_METHOD = NULL;

Surrogate* SGT_FOREACH_STELLA_LITERAL = NULL;

Symbol* SYM_FOREACH_STELLA_ON = NULL;

Symbol* SYM_FOREACH_STELLA_AND = NULL;

Symbol* SYM_FOREACH_STELLA_IF = NULL;

Symbol* SYM_FOREACH_STELLA_PROGN = NULL;

Symbol* SYM_FOREACH_STELLA_CONS = NULL;

Symbol* SYM_FOREACH_STELLA_EMPTYp = NULL;

Symbol* SYM_FOREACH_STELLA_SETF = NULL;

Symbol* SYM_FOREACH_STELLA_ADD_CONS_TO_END_OF_CONS_LIST = NULL;

Symbol* SYM_FOREACH_STELLA_COND = NULL;

Symbol* SYM_FOREACH_STELLA_CONSp = NULL;

Symbol* SYM_FOREACH_STELLA_OTHERWISE = NULL;

Symbol* SYM_FOREACH_STELLA_WHEN = NULL;

Symbol* SYM_FOREACH_STELLA_SYS_FOREACH = NULL;

Symbol* SYM_FOREACH_STELLA_VRLET = NULL;

Symbol* SYM_FOREACH_STELLA_BREAK = NULL;

Symbol* SYM_FOREACH_STELLA_ALWAYS = NULL;

Symbol* SYM_FOREACH_STELLA_STARTUP_FOREACH = NULL;

Symbol* SYM_FOREACH_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
