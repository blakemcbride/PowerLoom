//  -*- Mode: C++ -*-

// loom-to-kif.cc

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
*/

#include "logic/logic-system.hh"

namespace logic {
  using namespace stella;

Object* loomArgumentDescriptionToKif(Object* tree, Keyword* arity) {
  if (safePrimaryType(tree) == SGT_LOOM_TO_KIF_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if ((tree->value == SYM_LOOM_TO_KIF_STELLA_INVERSE) ||
          (tree->value == SYM_LOOM_TO_KIF_PL_KERNEL_KB_INVERSE)) {
        return (listO(3, SYM_LOOM_TO_KIF_PL_KERNEL_KB_INVERSE, loomArgumentDescriptionToKif(tree->rest->value, KWD_LOOM_TO_KIF_BINARY), NIL));
      }
      { Symbol* x = ((Symbol*)(SYSTEM_DEFINED_ARGUMENT_NAMES->nth(0)));
        Symbol* y = ((Symbol*)(SYSTEM_DEFINED_ARGUMENT_NAMES->nth(1)));
        Cons* kappaargs = ((arity == KWD_LOOM_TO_KIF_UNARY) ? consList(1, x) : consList(2, x, y));
        Cons* implicitargs = copyConsList(kappaargs);

        return (listO(3, SYM_LOOM_TO_KIF_LOGIC_KAPPA, kappaargs, cons(loomDescriptionToKif(tree, implicitargs), NIL)));
      }
    }
  }
  else {
    return (tree);
  }
}

Cons* loomRestrictionToKif(Cons* tree, Symbol* implicitvariable) {
  { Symbol* operatoR = ((Symbol*)(tree->value));
    Object* role = NULL;
    Object* argument = NULL;
    Symbol* existsvariable = NULL;
    Object* qualification = tree->fourth();

    if (getQuotedTree("((AT-LEAST AT-MOST EXACTLY) \"/LOGIC\")", "/LOGIC")->memberP(operatoR)) {
      {
        argument = tree->rest->value;
        role = tree->rest->rest->value;
      }
    }
    else {
      {
        role = tree->rest->value;
        argument = tree->rest->rest->value;
      }
    }
    if ((operatoR == SYM_LOOM_TO_KIF_LOGIC_AT_LEAST) ||
        ((operatoR == SYM_LOOM_TO_KIF_LOGIC_AT_MOST) ||
         (operatoR == SYM_LOOM_TO_KIF_LOGIC_EXACTLY))) {
      if (((boolean)(qualification))) {
        if (operatoR == SYM_LOOM_TO_KIF_LOGIC_AT_LEAST) {
          operatoR = SYM_LOOM_TO_KIF_PL_KERNEL_KB_QUALIFIED_RANGE_CARDINALITY_LOWER_BOUND;
        }
        else if (operatoR == SYM_LOOM_TO_KIF_LOGIC_AT_MOST) {
          operatoR = SYM_LOOM_TO_KIF_PL_KERNEL_KB_QUALIFIED_RANGE_CARDINALITY_UPPER_BOUND;
        }
        else if (operatoR == SYM_LOOM_TO_KIF_LOGIC_EXACTLY) {
          operatoR = SYM_LOOM_TO_KIF_PL_KERNEL_KB_QUALIFIED_RANGE_CARDINALITY;
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << operatoR << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      else {
        if (operatoR == SYM_LOOM_TO_KIF_LOGIC_AT_LEAST) {
          operatoR = SYM_LOOM_TO_KIF_PL_KERNEL_KB_RANGE_CARDINALITY_LOWER_BOUND;
        }
        else if (operatoR == SYM_LOOM_TO_KIF_LOGIC_AT_MOST) {
          operatoR = SYM_LOOM_TO_KIF_PL_KERNEL_KB_RANGE_CARDINALITY_UPPER_BOUND;
        }
        else if (operatoR == SYM_LOOM_TO_KIF_LOGIC_EXACTLY) {
          operatoR = SYM_LOOM_TO_KIF_PL_KERNEL_KB_RANGE_CARDINALITY;
        }
        else {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "`" << operatoR << "'" << " is not a valid case option";
            throw *newStellaException(stream001->theStringReader());
          }
        }
      }
      return (cons(operatoR, cons(loomArgumentDescriptionToKif(role, KWD_LOOM_TO_KIF_BINARY), cons(implicitvariable, cons(argument, ((((boolean)(qualification)) ? consList(1, loomArgumentDescriptionToKif(qualification, KWD_LOOM_TO_KIF_UNARY)) : NIL))->concatenate(NIL, 0))))));
    }
    else if (operatoR == SYM_LOOM_TO_KIF_LOGIC_ALL) {
      if (((boolean)(qualification))) {
        {
          { Symbol* v = NULL;
            Cons* iter000 = SYSTEM_DEFINED_ARGUMENT_NAMES;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              v = ((Symbol*)(iter000->value));
              if (!(implicitvariable == v)) {
                existsvariable = v;
                break;
              }
            }
          }
          return (listO(4, SYM_LOOM_TO_KIF_STELLA_EXISTS, cons(existsvariable, NIL), listO(4, SYM_LOOM_TO_KIF_STELLA_eg, listO(4, SYM_LOOM_TO_KIF_STELLA_AND, cons(loomArgumentDescriptionToKif(role, KWD_LOOM_TO_KIF_BINARY), cons(implicitvariable, cons(existsvariable, NIL))), cons(loomArgumentDescriptionToKif(qualification, KWD_LOOM_TO_KIF_UNARY), cons(existsvariable, NIL)), NIL), cons(loomArgumentDescriptionToKif(argument, KWD_LOOM_TO_KIF_UNARY), cons(((Symbol*)(SYSTEM_DEFINED_ARGUMENT_NAMES->nth(0))), NIL)), NIL), NIL));
        }
      }
      else {
        return (listO(3, SYM_LOOM_TO_KIF_PL_KERNEL_KB_RANGE_TYPE, loomArgumentDescriptionToKif(role, KWD_LOOM_TO_KIF_BINARY), cons(implicitvariable, cons(loomArgumentDescriptionToKif(argument, KWD_LOOM_TO_KIF_UNARY), NIL))));
      }
    }
    else if (operatoR == SYM_LOOM_TO_KIF_STELLA_SOME) {
      return (loomRestrictionToKif(listO(4, SYM_LOOM_TO_KIF_LOGIC_AT_LEAST, wrapInteger(1), role, cons(argument, NIL)), implicitvariable));
    }
    else if (operatoR == SYM_LOOM_TO_KIF_LOGIC_THE) {
      return (loomDescriptionToKif(listO(4, SYM_LOOM_TO_KIF_STELLA_AND, listO(4, SYM_LOOM_TO_KIF_LOGIC_EXACTLY, wrapInteger(1), role, NIL), listO(3, SYM_LOOM_TO_KIF_LOGIC_ALL, role, cons(argument, NIL)), NIL), consList(1, implicitvariable)));
    }
    else if ((operatoR == SYM_LOOM_TO_KIF_LOGIC_FILLED_BY) ||
        (operatoR == SYM_LOOM_TO_KIF_LOGIC_FILLERS)) {
      { Cons* clauses = NIL;
        Object* translatedrole = loomArgumentDescriptionToKif(role, KWD_LOOM_TO_KIF_BINARY);

        { Object* filler = NULL;
          Cons* iter001 = tree->rest->rest;
          Cons* collect000 = NULL;

          for  (; !(iter001 == NIL); 
                iter001 = iter001->rest) {
            filler = iter001->value;
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(cons(translatedrole, cons(implicitvariable, cons(filler, NIL))), NIL);
                if (clauses == NIL) {
                  clauses = collect000;
                }
                else {
                  addConsToEndOfConsList(clauses, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(cons(translatedrole, cons(implicitvariable, cons(filler, NIL))), NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        return (((Cons*)(conjoinSentences(clauses))));
      }
    }
    else if (operatoR == SYM_LOOM_TO_KIF_LOGIC_NOT_FILLED_BY) {
      { Cons* clauses = NIL;
        Object* translatedrole = loomArgumentDescriptionToKif(role, KWD_LOOM_TO_KIF_BINARY);

        { Object* filler = NULL;
          Cons* iter002 = tree->rest->rest;
          Cons* collect001 = NULL;

          for  (; !(iter002 == NIL); 
                iter002 = iter002->rest) {
            filler = iter002->value;
            if (!((boolean)(collect001))) {
              {
                collect001 = cons(listO(3, SYM_LOOM_TO_KIF_STELLA_NOT, cons(translatedrole, cons(implicitvariable, cons(filler, NIL))), NIL), NIL);
                if (clauses == NIL) {
                  clauses = collect001;
                }
                else {
                  addConsToEndOfConsList(clauses, collect001);
                }
              }
            }
            else {
              {
                collect001->rest = cons(listO(3, SYM_LOOM_TO_KIF_STELLA_NOT, cons(translatedrole, cons(implicitvariable, cons(filler, NIL))), NIL), NIL);
                collect001 = collect001->rest;
              }
            }
          }
        }
        return (((Cons*)(conjoinSentences(clauses))));
      }
    }
    else {
      { OutputStringStream* stream002 = newOutputStringStream();

        *(stream002->nativeStream) << "`" << operatoR << "'" << " is not a valid case option";
        throw *newStellaException(stream002->theStringReader());
      }
    }
  }
}

Cons* loomRelatesToKif(Cons* tree, Cons* implicitvariables) {
  if (tree->value == SYM_LOOM_TO_KIF_LOGIC_RELATES) {
    tree = tree->rest;
  }
  { Cons* clauses = NIL;
    Cons* existsvariables = NIL;
    Cons* arguments = NIL;
    Cons* skolemvariables = NIL;

    { Symbol* v = NULL;
      Cons* iter000 = SYSTEM_DEFINED_ARGUMENT_NAMES;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        v = ((Symbol*)(iter000->value));
        if ((!implicitvariables->memberP(v)) &&
            (skolemvariables->length() < (tree->length() - 1))) {
          skolemvariables = cons(v, skolemvariables);
        }
      }
    }
    { Object* arg = NULL;
      Cons* iter001 = tree->rest;
      Object* v = NULL;
      Cons* iter002 = skolemvariables;
      Cons* collect000 = NULL;

      for  (; (!(iter001 == NIL)) &&
                (!(iter002 == NIL)); 
            iter001 = iter001->rest,
            iter002 = iter002->rest) {
        arg = iter001->value;
        v = iter002->value;
        if (isaP(arg, SGT_LOOM_TO_KIF_STELLA_NUMBER_WRAPPER)) {
          arguments = cons(arg, arguments);
          continue;
        }
        arguments = cons(v, arguments);
        existsvariables = cons(v, existsvariables);
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(loomDescriptionToKif(arg, consList(2, ((Symbol*)(implicitvariables->value)), v)), NIL);
            if (clauses == NIL) {
              clauses = collect000;
            }
            else {
              addConsToEndOfConsList(clauses, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(loomDescriptionToKif(arg, consList(2, ((Symbol*)(implicitvariables->value)), v)), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (listO(3, SYM_LOOM_TO_KIF_STELLA_EXISTS, existsvariables->reverse(), cons(cons(SYM_LOOM_TO_KIF_STELLA_AND, clauses->concatenate(cons(loomDescriptionToKif(tree->value, arguments->reverse()), NIL), 0)), NIL)));
  }
}

void substituteVariablesInTree(Cons* tree, Cons* substitution) {
  { Object* operatoR = tree->value;

    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(operatoR));

      if ((testValue000 == SYM_LOOM_TO_KIF_STELLA_EXISTS) ||
          ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_FOR_SOME) ||
           (testValue000 == SYM_LOOM_TO_KIF_STELLA_FORALL))) {
        if (operatoR == SYM_LOOM_TO_KIF_LOGIC_FOR_SOME) {
          tree->firstSetter(SYM_LOOM_TO_KIF_STELLA_EXISTS);
        }
        { Object* variables = tree->rest->value;

          if (!consP(variables)) {
            variables = consList(1, variables);
          }
          { Object* v1 = NULL;
            Cons* iter000 = ((Cons*)(variables));

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              v1 = iter000->value;
              if (substitution->memberP(v1)) {
                { Symbol* v2 = NULL;
                  Cons* iter001 = SYSTEM_DEFINED_ARGUMENT_NAMES;

                  for (; !(iter001 == NIL); iter001 = iter001->rest) {
                    v2 = ((Symbol*)(iter001->value));
                    if (!substitution->memberP(v2)) {
                      substitution = cons(v2, substitution);
                      substitution = cons(v1, substitution);
                      break;
                    }
                  }
                }
              }
            }
          }
        }
        substituteVariablesInTree(tree->rest, substitution);
      }
      else {
        { ConsIterator* it1 = tree->allocateIterator();

          for (; it1->nextP(); ) {
            { Object* arg = it1->value;

              { Surrogate* testValue001 = safePrimaryType(arg);

                if (subtypeOfSymbolP(testValue001)) {
                  { Object* arg000 = arg;
                    Symbol* arg = ((Symbol*)(arg000));

                    if (questionMarkSymbolP(arg)) {
                      { ConsIterator* it2 = substitution->allocateIterator();

                        for (; it2->nextP(); ) {
                          if (it2->value == arg) {
                            it2->nextP();
                            it1->valueSetter(it2->value);
                            break;
                          }
                        }
                      }
                    }
                  }
                }
                else if (testValue001 == SGT_LOOM_TO_KIF_STELLA_CONS) {
                  { Object* arg001 = arg;
                    Cons* arg = ((Cons*)(arg001));

                    substituteVariablesInTree(arg, substitution);
                  }
                }
                else {
                }
              }
            }
          }
        }
      }
    }
  }
}

Cons* loomThroughToKif(Cons* tree, Cons* implicitvariables) {
  { Object* lowerbound = tree->rest->value;
    Object* upperbound = tree->rest->rest->value;
    Cons* clauses = NIL;

    if (isaP(upperbound, SGT_LOOM_TO_KIF_STELLA_NUMBER_WRAPPER)) {
      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

        if ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_THROUGH) ||
            ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_INTERVALii) ||
             (testValue000 == SYM_LOOM_TO_KIF_LOGIC_INTERVALi_))) {
          clauses = cons(listO(3, SYM_LOOM_TO_KIF_STELLA_el, ((Symbol*)(implicitvariables->value)), cons(upperbound, NIL)), clauses);
        }
        else if ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_INTERVAL_i) ||
            (testValue000 == SYM_LOOM_TO_KIF_LOGIC_INTERVAL__)) {
          clauses = cons(listO(3, SYM_LOOM_TO_KIF_STELLA_l, ((Symbol*)(implicitvariables->value)), cons(upperbound, NIL)), clauses);
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
    if (isaP(lowerbound, SGT_LOOM_TO_KIF_STELLA_NUMBER_WRAPPER)) {
      { GeneralizedSymbol* testValue001 = ((GeneralizedSymbol*)(tree->value));

        if ((testValue001 == SYM_LOOM_TO_KIF_LOGIC_THROUGH) ||
            ((testValue001 == SYM_LOOM_TO_KIF_LOGIC_INTERVALii) ||
             (testValue001 == SYM_LOOM_TO_KIF_LOGIC_INTERVAL_i))) {
          clauses = cons(listO(3, SYM_LOOM_TO_KIF_STELLA_ge, ((Symbol*)(implicitvariables->value)), cons(lowerbound, NIL)), clauses);
        }
        else if ((testValue001 == SYM_LOOM_TO_KIF_LOGIC_INTERVALi_) ||
            (testValue001 == SYM_LOOM_TO_KIF_LOGIC_INTERVAL__)) {
          clauses = cons(listO(3, SYM_LOOM_TO_KIF_STELLA_g, ((Symbol*)(implicitvariables->value)), cons(lowerbound, NIL)), clauses);
        }
        else {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
            throw *newStellaException(stream001->theStringReader());
          }
        }
      }
    }
    return (((Cons*)(conjoinSentences(clauses))));
  }
}

Cons* loomSatisfiesToKif(Cons* tree, Cons* implicitvariables) {
  { Object* iovariables = tree->rest->value;
    Object* body = tree->rest->rest->value;
    Cons* substitution = NIL;

    if (!consP(iovariables)) {
      iovariables = consList(1, iovariables);
    }
    { Object* v1 = NULL;
      Cons* iter000 = ((Cons*)(iovariables));
      Symbol* v2 = NULL;
      Cons* iter001 = implicitvariables;

      for  (; (!(iter000 == NIL)) &&
                (!(iter001 == NIL)); 
            iter000 = iter000->rest,
            iter001 = iter001->rest) {
        v1 = iter000->value;
        v2 = ((Symbol*)(iter001->value));
        substitution = cons(v2, substitution);
        substitution = cons(v1, substitution);
      }
    }
    substituteVariablesInTree(((Cons*)(body)), substitution);
    return (((Cons*)(body)));
  }
}

Cons* loomDescriptionToKif(Object* tree, Cons* implicitvariables) {
  if (safePrimaryType(tree) == SGT_LOOM_TO_KIF_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      { Object* operatoR = tree->value;

        { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(operatoR));

          if ((testValue000 == SYM_LOOM_TO_KIF_STELLA_AND) ||
              ((testValue000 == SYM_LOOM_TO_KIF_STELLA_OR) ||
               (testValue000 == SYM_LOOM_TO_KIF_STELLA_NOT))) {
            { Cons* clauses = NIL;

              { Object* arg = NULL;
                Cons* iter000 = tree->rest;
                Cons* collect000 = NULL;

                for  (; !(iter000 == NIL); 
                      iter000 = iter000->rest) {
                  arg = iter000->value;
                  if (!((boolean)(collect000))) {
                    {
                      collect000 = cons(loomDescriptionToKif(arg, implicitvariables), NIL);
                      if (clauses == NIL) {
                        clauses = collect000;
                      }
                      else {
                        addConsToEndOfConsList(clauses, collect000);
                      }
                    }
                  }
                  else {
                    {
                      collect000->rest = cons(loomDescriptionToKif(arg, implicitvariables), NIL);
                      collect000 = collect000->rest;
                    }
                  }
                }
              }
              return (cons(operatoR, clauses->concatenate(NIL, 0)));
            }
          }
          else if ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_AT_LEAST) ||
              ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_AT_MOST) ||
               ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_EXACTLY) ||
                ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_ALL) ||
                 ((testValue000 == SYM_LOOM_TO_KIF_STELLA_SOME) ||
                  ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_THE) ||
                   ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_FILLED_BY) ||
                    (testValue000 == SYM_LOOM_TO_KIF_LOGIC_FILLERS)))))))) {
            return (loomRestrictionToKif(tree, ((Symbol*)(implicitvariables->value))));
          }
          else if (testValue000 == SYM_LOOM_TO_KIF_LOGIC_SAME_AS) {
            { Symbol* selfvariable = ((Symbol*)(implicitvariables->value));
              Symbol* y = NULL;

              { Symbol* v = NULL;
                Cons* iter001 = SYSTEM_DEFINED_ARGUMENT_NAMES;

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  v = ((Symbol*)(iter001->value));
                  if (!(v == selfvariable)) {
                    y = v;
                    break;
                  }
                }
              }
              { Cons* localimplicitvariables = consList(2, selfvariable, y);
                Cons* clauses = NIL;

                { Object* arg = NULL;
                  Cons* iter002 = tree->rest;
                  Cons* collect001 = NULL;

                  for  (; !(iter002 == NIL); 
                        iter002 = iter002->rest) {
                    arg = iter002->value;
                    if (!((boolean)(collect001))) {
                      {
                        collect001 = cons(loomDescriptionToKif(arg, localimplicitvariables), NIL);
                        if (clauses == NIL) {
                          clauses = collect001;
                        }
                        else {
                          addConsToEndOfConsList(clauses, collect001);
                        }
                      }
                    }
                    else {
                      {
                        collect001->rest = cons(loomDescriptionToKif(arg, localimplicitvariables), NIL);
                        collect001 = collect001->rest;
                      }
                    }
                  }
                }
                return (listO(3, SYM_LOOM_TO_KIF_STELLA_EXISTS, y, cons(cons(SYM_LOOM_TO_KIF_STELLA_AND, clauses->concatenate(NIL, 0)), NIL)));
              }
            }
          }
          else if ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_RELATES) ||
              ((testValue000 == SYM_LOOM_TO_KIF_STELLA_g) ||
               ((testValue000 == SYM_LOOM_TO_KIF_STELLA_l) ||
                ((testValue000 == SYM_LOOM_TO_KIF_STELLA_ge) ||
                 ((testValue000 == SYM_LOOM_TO_KIF_STELLA_le) ||
                  ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_lg) ||
                   (testValue000 == SYM_LOOM_TO_KIF_STELLA_e))))))) {
            return (loomRelatesToKif(tree, implicitvariables));
          }
          else if (testValue000 == SYM_LOOM_TO_KIF_LOGIC_ONE_OF) {
            return (cons(SYM_LOOM_TO_KIF_PL_KERNEL_KB_MEMBER_OF, copyConsList(implicitvariables)->concatenate(cons(cons(SYM_LOOM_TO_KIF_PL_KERNEL_KB_SETOF, tree->rest->concatenate(NIL, 0)), NIL), 0)));
          }
          else if (testValue000 == SYM_LOOM_TO_KIF_LOGIC_THE_ORDERED_SET) {
            return (cons(SYM_LOOM_TO_KIF_PL_KERNEL_KB_MEMBER_OF, copyConsList(implicitvariables)->concatenate(cons(cons(SYM_LOOM_TO_KIF_PL_KERNEL_KB_LISTOF, tree->rest->concatenate(NIL, 0)), NIL), 0)));
          }
          else if ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_THROUGH) ||
              ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_INTERVALii) ||
               ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_INTERVALi_) ||
                ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_INTERVAL_i) ||
                 (testValue000 == SYM_LOOM_TO_KIF_LOGIC_INTERVAL__))))) {
            return (loomThroughToKif(tree, implicitvariables));
          }
          else if (testValue000 == SYM_LOOM_TO_KIF_LOGIC_SATISFIES) {
            return (loomSatisfiesToKif(tree, implicitvariables));
          }
          else if (testValue000 == SYM_LOOM_TO_KIF_LOGIC_DOMAIN) {
            return (loomDescriptionToKif(tree->rest->value, consList(1, ((Symbol*)(implicitvariables->value)))));
          }
          else if (testValue000 == SYM_LOOM_TO_KIF_STELLA_DOMAINS) {
            { Cons* clauses = NIL;

              { Object* domain = NULL;
                Cons* iter003 = tree->rest;
                Symbol* var = NULL;
                Cons* iter004 = implicitvariables;
                Cons* collect002 = NULL;

                for  (; (!(iter003 == NIL)) &&
                          (!(iter004 == NIL)); 
                      iter003 = iter003->rest,
                      iter004 = iter004->rest) {
                  domain = iter003->value;
                  var = ((Symbol*)(iter004->value));
                  if (!((boolean)(collect002))) {
                    {
                      collect002 = cons(loomDescriptionToKif(domain, consList(1, var)), NIL);
                      if (clauses == NIL) {
                        clauses = collect002;
                      }
                      else {
                        addConsToEndOfConsList(clauses, collect002);
                      }
                    }
                  }
                  else {
                    {
                      collect002->rest = cons(loomDescriptionToKif(domain, consList(1, var)), NIL);
                      collect002 = collect002->rest;
                    }
                  }
                }
              }
              return (((Cons*)(conjoinSentences(clauses))));
            }
          }
          else if (testValue000 == SYM_LOOM_TO_KIF_LOGIC_RANGE) {
            return (loomDescriptionToKif(tree->rest->value, consList(1, ((Symbol*)(implicitvariables->last())))));
          }
          else if ((testValue000 == SYM_LOOM_TO_KIF_STELLA_INVERSE) ||
              (testValue000 == SYM_LOOM_TO_KIF_PL_KERNEL_KB_INVERSE)) {
            { Cons* inverseimplicitvariables = consList(2, ((Symbol*)(implicitvariables->rest->value)), ((Symbol*)(implicitvariables->value)));

              return (loomDescriptionToKif(tree->rest->value, inverseimplicitvariables));
            }
          }
          else if (testValue000 == SYM_LOOM_TO_KIF_LOGIC_COMPOSE) {
            { Cons* chain = cons(tree->rest->value, cons(((Symbol*)(implicitvariables->value)), NIL));

              { Object* function = NULL;
                Cons* iter005 = tree->rest->rest;

                for (; !(iter005 == NIL); iter005 = iter005->rest) {
                  function = iter005->value;
                  chain = cons(function, cons(chain, NIL));
                }
              }
              return (chain->concatenate(cons(((Symbol*)(implicitvariables->rest->value)), NIL), 0));
            }
          }
          else {
            std::cout << "Illegal or unimplemented Loom operator cannot be translated to KIF." << std::endl << "   Problem expression:  " << "`" << tree << "'" << std::endl << std::endl;
            return (NIL);
          }
        }
      }
    }
  }
  else {
    if (((GeneralizedSymbol*)(tree)) == SYM_LOOM_TO_KIF_LOGIC_lg) {
      return (listO(3, SYM_LOOM_TO_KIF_STELLA_NOT, cons(SYM_LOOM_TO_KIF_STELLA_e, copyConsList(implicitvariables)->concatenate(NIL, 0)), NIL));
    }
    else {
      return (cons(tree, copyConsList(implicitvariables)->concatenate(NIL, 0)));
    }
  }
}

boolean loomDescriptionOperatorP(Object* self) {
  return (getQuotedTree("((AND OR NOT AT-LEAST AT-MOST EXACTLY ALL SOME THE FILLED-BY FILLERS SAME-AS RELATES ONE-OF THROUGH) \"/LOGIC\")", "/LOGIC")->memberP(self));
}

Object* loomSentenceToKif(Object* tree) {
  if (safePrimaryType(tree) == SGT_LOOM_TO_KIF_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if (!symbolP(tree->value)) {
        { OutputStringStream* stream000 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream000->nativeStream) << "ERROR: " << "Illegal clause " << "`" << tree << "'" << " in Loom formula." << "." << std::endl;
            helpSignalPropositionError(stream000, KWD_LOOM_TO_KIF_ERROR);
          }
          throw *newPropositionError(stream000->theStringReader());
        }
      }
      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

        if ((testValue000 == SYM_LOOM_TO_KIF_STELLA_AND) ||
            ((testValue000 == SYM_LOOM_TO_KIF_STELLA_OR) ||
             (testValue000 == SYM_LOOM_TO_KIF_STELLA_NOT))) {
          { Cons* clauses = NIL;

            { Object* arg = NULL;
              Cons* iter000 = tree->rest;
              Cons* collect000 = NULL;

              for  (; !(iter000 == NIL); 
                    iter000 = iter000->rest) {
                arg = iter000->value;
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(loomSentenceToKif(arg), NIL);
                    if (clauses == NIL) {
                      clauses = collect000;
                    }
                    else {
                      addConsToEndOfConsList(clauses, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000->rest = cons(loomSentenceToKif(arg), NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
            clauses = clauses->reverse();
            clauses = cons(tree->value, clauses);
            return (clauses);
          }
        }
        else if (testValue000 == SYM_LOOM_TO_KIF_LOGIC_ABOUT) {
          { Cons* aboutclauses = NIL;
            Cons* implicitvariables = NULL;

            { Object* clause = NULL;
              Cons* iter001 = tree->rest->rest;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                clause = iter001->value;
                implicitvariables = consList(1, tree->rest->value);
                if (!consP(clause)) {
                  aboutclauses = cons(cons(clause, implicitvariables->concatenate(NIL, 0)), aboutclauses);
                }
                else if (loomDescriptionOperatorP(((Cons*)(clause))->value)) {
                  aboutclauses = cons(loomDescriptionToKif(clause, implicitvariables), aboutclauses);
                }
                else {
                  { Cons* expression = ((Cons*)(clause));

                    aboutclauses = cons(cons(expression->value, implicitvariables->concatenate(copyConsList(expression->rest)->concatenate(NIL, 0), 0)), aboutclauses);
                  }
                }
              }
            }
            return (conjoinSentences(aboutclauses->reverse()));
          }
        }
        else if (testValue000 == SYM_LOOM_TO_KIF_LOGIC_CREATE) {
          return (translateLoomCreateClause(tree->rest));
        }
        else {
          return (tree);
        }
      }
    }
  }
  else {
    return (tree);
  }
}

int computeLoomDescriptionArity(Object* tree) {
  { Surrogate* testValue000 = safePrimaryType(tree);

    if (subtypeOfSymbolP(testValue000)) {
      { Object* tree000 = tree;
        Symbol* tree = ((Symbol*)(tree000));

        { NamedDescription* description = getDescription(tree);

          if (((boolean)(description))) {
            return (description->arity());
          }
        }
      }
    }
    else if (testValue000 == SGT_LOOM_TO_KIF_STELLA_CONS) {
      { Object* tree001 = tree;
        Cons* tree = ((Cons*)(tree001));

        { GeneralizedSymbol* testValue001 = ((GeneralizedSymbol*)(tree->value));

          if ((testValue001 == SYM_LOOM_TO_KIF_STELLA_AND) ||
              (testValue001 == SYM_LOOM_TO_KIF_STELLA_OR)) {
            { Object* arg = NULL;
              Cons* iter000 = tree->rest;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                arg = iter000->value;
                { int guess = computeLoomDescriptionArity(arg);

                  if (guess > 0) {
                    return (guess);
                  }
                }
              }
            }
          }
          else if ((testValue001 == SYM_LOOM_TO_KIF_LOGIC_AT_LEAST) ||
              ((testValue001 == SYM_LOOM_TO_KIF_LOGIC_AT_MOST) ||
               ((testValue001 == SYM_LOOM_TO_KIF_LOGIC_ALL) ||
                (testValue001 == SYM_LOOM_TO_KIF_LOGIC_SAME_AS)))) {
            return (1);
          }
          else if ((testValue001 == SYM_LOOM_TO_KIF_LOGIC_DOMAIN) ||
              ((testValue001 == SYM_LOOM_TO_KIF_LOGIC_RANGE) ||
               ((testValue001 == SYM_LOOM_TO_KIF_STELLA_INVERSE) ||
                ((testValue001 == SYM_LOOM_TO_KIF_PL_KERNEL_KB_INVERSE) ||
                 (testValue001 == SYM_LOOM_TO_KIF_LOGIC_COMPOSE))))) {
            return (2);
          }
          else if ((testValue001 == SYM_LOOM_TO_KIF_STELLA_g) ||
              ((testValue001 == SYM_LOOM_TO_KIF_STELLA_l) ||
               ((testValue001 == SYM_LOOM_TO_KIF_STELLA_ge) ||
                ((testValue001 == SYM_LOOM_TO_KIF_STELLA_le) ||
                 ((testValue001 == SYM_LOOM_TO_KIF_LOGIC_lg) ||
                  (testValue001 == SYM_LOOM_TO_KIF_STELLA_e)))))) {
            return (tree->rest->length());
          }
          else if (testValue001 == SYM_LOOM_TO_KIF_LOGIC_RELATES) {
            return (tree->rest->rest->length());
          }
          else if (testValue001 == SYM_LOOM_TO_KIF_LOGIC_SATISFIES) {
            { Object* variables = tree->rest->value;

              if (consP(variables)) {
                return (((Cons*)(variables))->length());
              }
              else {
                return (1);
              }
            }
          }
          else {
          }
        }
      }
    }
    else {
    }
  }
  return (-1);
}

Object* eliminateLoomKeywords(Object* tree) {
  { Surrogate* testValue000 = safePrimaryType(tree);

    if (subtypeOfKeywordP(testValue000)) {
      { Object* tree000 = tree;
        Keyword* tree = ((Keyword*)(tree000));

        return (internSymbolInModule(tree->symbolName, oLOGIC_MODULEo, false));
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* tree001 = tree;
        Symbol* tree = ((Symbol*)(tree001));

        if ((tree == SYM_LOOM_TO_KIF_LOGIC_SUPERRELATIONS) ||
            (tree == SYM_LOOM_TO_KIF_LOGIC_SUPERCONCEPTS)) {
          return (SYM_LOOM_TO_KIF_PL_KERNEL_KB_SUBSET_OF);
        }
        else {
        }
        if (stringEqlP(tree->symbolName, "/=")) {
          return (SYM_LOOM_TO_KIF_LOGIC_lg);
        }
      }
    }
    else if (testValue000 == SGT_LOOM_TO_KIF_STELLA_CONS) {
      { Object* tree002 = tree;
        Cons* tree = ((Cons*)(tree002));

        { ConsIterator* it = tree->allocateIterator();

          for (; it->nextP(); ) {
            it->valueSetter(eliminateLoomKeywords(it->value));
          }
        }
        if ((!((boolean)(tree->value))) ||
            (!symbolP(tree->value))) {
          return (tree);
        }
        { Symbol* operatoR = ((Symbol*)(tree->value));

          if (operatoR == SYM_LOOM_TO_KIF_STELLA_QUOTE) {
            return (tree->rest->value);
          }
          else {
          }
        }
      }
    }
    else {
    }
  }
  return (tree);
}

Cons* yieldImplicitVariables(int arity) {
  { Cons* variables = NIL;

    { IntegerIntervalIterator* i = interval(1, arity);
      Symbol* v = NULL;
      Cons* iter000 = SYSTEM_DEFINED_ARGUMENT_NAMES;
      Cons* collect000 = NULL;

      for  (; i->nextP() &&
                (!(iter000 == NIL)); 
            iter000 = iter000->rest) {
        v = ((Symbol*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(v, NIL);
            if (variables == NIL) {
              variables = collect000;
            }
            else {
              addConsToEndOfConsList(variables, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(v, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (variables);
  }
}

Cons* helpTranslateLoomDescriptionToKif(Object* tree, Cons* implicitvariables) {
  return (loomDescriptionToKif(eliminateLoomKeywords(tree), implicitvariables));
}

Cons* translateLoomDescriptionToKif(Object* tree) {
  try {
    { int arity = computeLoomDescriptionArity(tree);
      Cons* implicitvariables = yieldImplicitVariables(((arity > 0) ? arity : 1));

      return (listO(3, SYM_LOOM_TO_KIF_LOGIC_KAPPA, implicitvariables, cons(helpTranslateLoomDescriptionToKif(tree, implicitvariables), NIL)));
    }
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
    return (NULL);
  }
}

Object* translateLoomSentenceToKif(Object* tree) {
  try {
    return (loomSentenceToKif(eliminateLoomKeywords(tree)));
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
    return (NULL);
  }
}

Cons* translateLoomAssertions(Cons* tree, boolean retractP) {
  if (tree->rest == NIL) {
    tree = ((Cons*)(tree->value));
  }
  else {
    tree = cons(SYM_LOOM_TO_KIF_STELLA_AND, tree);
  }
  { Symbol* verb = (retractP ? SYM_LOOM_TO_KIF_STELLA_RETRACT : SYM_LOOM_TO_KIF_STELLA_ASSERT);
    Object* proposition = translateLoomSentenceToKif(tree);

    if (((boolean)(tree))) {
      return (cons(verb, cons(proposition, NIL)));
    }
    else {
      return (NULL);
    }
  }
}

Cons* translateLoomAsk(Cons* tree) {
  { Object* sentence = translateLoomSentenceToKif(tree->rest->value);

    { PropertyList* self000 = newPropertyList();

      self000->thePlist = tree->rest->rest;
      { PropertyList* options = self000;

        { Object* keyword = NULL;
          Object* value = NULL;
          Cons* iter000 = options->thePlist;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest->rest) {
            keyword = iter000->value;
            value = iter000->rest->value;
            if (((GeneralizedSymbol*)(keyword)) == KWD_LOOM_TO_KIF_3_VALUED_P) {
              value = value;
              std::cout << "Sorry, 3-valued 'ask' not yet implemented in PowerLoom." << std::endl << "Please complain to your PowerLoom dealer." << std::endl << std::endl;
            }
            else {
              std::cout << "Illegal or unimplemented option to 'ask': " << "`" << keyword << "'" << std::endl;
            }
          }
        }
        if (((boolean)(sentence))) {
          return (listO(3, SYM_LOOM_TO_KIF_STELLA_ASK, sentence, NIL));
        }
        else {
          return (NULL);
        }
      }
    }
  }
}

Cons* translateLoomRetrieve(Cons* tree) {
  { Object* variables = tree->rest->value;
    Object* querybody = translateLoomSentenceToKif(tree->rest->rest->value);

    { PropertyList* self000 = newPropertyList();

      self000->thePlist = tree->nthRest(3);
      { PropertyList* options = self000;
        Cons* nulls = NIL;

        if (!options->emptyP()) {
          std::cout << "'loom::retrieve' options not yet implemented" << std::endl;
        }
        { ConsIterator* i = ((Cons*)(variables))->allocateIterator();

          for (; i->nextP(); ) {
            nulls = cons(SYM_LOOM_TO_KIF_STELLA_NULL, nulls);
          }
        }
        return (listO(3, SYM_LOOM_TO_KIF_STELLA_CONSIFY, listO(4, SYM_LOOM_TO_KIF_STELLA_RETRIEVE, SYM_LOOM_TO_KIF_LOGIC_ALL, variables, cons(querybody, NIL)), NIL));
      }
    }
  }
}

Cons* translateOneLoomForm(Object* tree) {
  if (safePrimaryType(tree) == SGT_LOOM_TO_KIF_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

        if ((testValue000 == SYM_LOOM_TO_KIF_STELLA_PROGN) ||
            (testValue000 == SYM_LOOM_TO_KIF_LOGIC_EVAL_WHEN)) {
          { Cons* forms = NIL;
            Cons* translation = NULL;

            { Object* item = NULL;
              Cons* iter000 = tree->rest;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                item = iter000->value;
                translation = translateOneLoomForm(item);
                if (((boolean)(translation))) {
                  if (isaP(translation->value, SGT_LOOM_TO_KIF_STELLA_CONS)) {
                    { Object* subform = NULL;
                      Cons* iter001 = translation;

                      for (; !(iter001 == NIL); iter001 = iter001->rest) {
                        subform = iter001->value;
                        forms = cons(subform, forms);
                      }
                    }
                  }
                  else {
                    forms = cons(translation, forms);
                  }
                }
              }
            }
            return (forms->reverse());
          }
        }
        else if ((testValue000 == SYM_LOOM_TO_KIF_STELLA_ASK) ||
            ((testValue000 == SYM_LOOM_TO_KIF_STELLA_RETRIEVE) ||
             ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_TELL) ||
              ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_FORGET) ||
               ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_TELLM) ||
                (testValue000 == SYM_LOOM_TO_KIF_LOGIC_FORGETM)))))) {
          return (translateLoomStatement(tree));
        }
        else if ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_CREATE) ||
            (testValue000 == SYM_LOOM_TO_KIF_LOGIC_CREATEM)) {
          destructivelyUnquoteTopLevel(tree);
          return (translateLoomStatement(tree));
        }
        else if ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_DEFCONCEPT) ||
            ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_DEFSET) ||
             ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_DEFRELATION) ||
              (testValue000 == SYM_LOOM_TO_KIF_LOGIC_DEFPROPERTY)))) {
          return (translateLoomDefinition(tree));
        }
        else if ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_DEFCONTEXT) ||
            ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_ADD_VALUE) ||
             ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_SET_VALUE) ||
              (testValue000 == SYM_LOOM_TO_KIF_LOGIC_FADD_VALUE)))) {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "Translation of " << "`" << tree->value << "'" << " is not implemented yet!" << std::endl;
          return (NULL);
        }
        else if (testValue000 == SYM_LOOM_TO_KIF_STELLA_CHANGE_CONTEXT) {
          return (translateLoomContextChange(tree, true));
        }
        else if ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_IN_CONTEXT) ||
            (testValue000 == SYM_LOOM_TO_KIF_LOGIC_IN_KB)) {
          return (translateLoomContextChange(tree, false));
        }
        else if (testValue000 == SYM_LOOM_TO_KIF_STELLA_CC) {
          if (((boolean)(tree->rest->value))) {
            return (translateLoomContextChange(tree, false));
          }
          else {
            return (NULL);
          }
        }
        else {
          return (NULL);
        }
      }
    }
  }
  else {
    return (NULL);
  }
}

Object* safeGetNextSExpression(SExpressionIterator* iter) {
  { boolean continueP = true;
    Object* result = NULL;

    while (continueP) {
      try {
        if (iter->nextP()) {
          result = iter->value;
        }
        continueP = false;
      }
      catch (ReadException& _e) {
        ReadException* e = &_e;

        *(STANDARD_WARNING->nativeStream) << "Warning: " << "Read Exception " << "`" << exceptionMessage(e) << "'" << std::endl << std::endl;
      }
    }
    return (result);
  }
}

void destructivelyUnquoteTopLevel(Cons* tree) {
  while (!(tree == NIL)) {
    if (isaP(tree->value, SGT_LOOM_TO_KIF_STELLA_CONS) &&
        (SYM_LOOM_TO_KIF_STELLA_QUOTE == ((Cons*)(tree->value))->value)) {
      tree->firstSetter(((Cons*)(tree->value))->rest->value);
      if (tree->value == SYM_LOOM_TO_KIF_STELLA_NIL) {
        tree->firstSetter(NIL);
      }
    }
    tree = tree->rest;
  }
}

void translateLoomFile(const char* input, const char* output) {
  // Translate the Loom file `input' to PowerLoom and write the
  // translation to the file `output'.  Note that this will only
  // work for fairly vanilla Loom files that do not contain any
  // Lisp-isms.  It might require to clean the Loom file manually
  // before this translation will work.
  { 
    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
    BIND_STELLA_SPECIAL(oPRINTPRETTYpo, boolean, true);
    { InputFileStream* in = NULL;

      try {
        in = openInputFile(input, 0);
        { OutputFileStream* out = NULL;

          try {
            out = openOutputFile(output, 0);
            { Cons* translation = NIL;
              SExpressionIterator* iter = sExpressions(in);
              Object* form = safeGetNextSExpression(iter);
              boolean dialectEmittedP = false;

              *(out->nativeStream) << ";; Automatic Translation for file " << input << std::endl << std::endl;
              while (((boolean)(form))) {
                translation = translateOneLoomForm(form);
                if (!((boolean)(translation))) {
                }
                else if (translation == NIL) {
                }
                else if (isaP(translation->value, SGT_LOOM_TO_KIF_STELLA_CONS)) {
                  dialectEmittedP = true;
                  *(out->nativeStream) << listO(3, SYM_LOOM_TO_KIF_LOGIC_IN_DIALECT, KWD_LOOM_TO_KIF_KIF, NIL) << std::endl << std::endl;
                  { Object* subform = NULL;
                    Cons* iter000 = translation;

                    for (; !(iter000 == NIL); iter000 = iter000->rest) {
                      subform = iter000->value;
                      *(out->nativeStream) << subform << std::endl << std::endl;
                    }
                  }
                }
                else {
                  if ((!dialectEmittedP) &&
                      (!(translation->value == SYM_LOOM_TO_KIF_STELLA_IN_MODULE))) {
                    dialectEmittedP = true;
                    *(out->nativeStream) << listO(3, SYM_LOOM_TO_KIF_LOGIC_IN_DIALECT, KWD_LOOM_TO_KIF_KIF, NIL) << std::endl << std::endl;
                  }
                  *(out->nativeStream) << translation << std::endl << std::endl;
                }
                form = safeGetNextSExpression(iter);
              }
            }
          }
catch (...) {
            if (((boolean)(out))) {
              out->free();
            }
            throw;
          }
          if (((boolean)(out))) {
            out->free();
          }
        }
      }
catch (...) {
        if (((boolean)(in))) {
          in->free();
        }
        throw;
      }
      if (((boolean)(in))) {
        in->free();
      }
    }
  }
}

void translateLoomFileEvaluatorWrapper(Cons* arguments) {
  translateLoomFile(((StringWrapper*)(arguments->value))->wrapperValue, ((StringWrapper*)(arguments->rest->value))->wrapperValue);
}

Cons* translateLoomStatement(Cons* tree) {
  { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

    if (testValue000 == SYM_LOOM_TO_KIF_STELLA_ASK) {
      return (translateLoomAsk(tree));
    }
    else if (testValue000 == SYM_LOOM_TO_KIF_STELLA_RETRIEVE) {
      return (translateLoomRetrieve(tree));
    }
    else if ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_TELL) ||
        (testValue000 == SYM_LOOM_TO_KIF_LOGIC_TELLM)) {
      return (translateLoomAssertions(tree->rest, false));
    }
    else if ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_FORGET) ||
        (testValue000 == SYM_LOOM_TO_KIF_LOGIC_FORGETM)) {
      return (translateLoomAssertions(tree->rest, true));
    }
    else if ((testValue000 == SYM_LOOM_TO_KIF_LOGIC_CREATE) ||
        (testValue000 == SYM_LOOM_TO_KIF_LOGIC_CREATEM)) {
      return (translateLoomAssertions(consList(1, translateLoomCreateClause(tree->rest)), true));
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Cons* translateLoomCreateClause(Cons* tree) {
  if (tree->rest->value == NIL) {
    return (listO(3, SYM_LOOM_TO_KIF_STELLA_THING, tree->value, NIL));
  }
  else {
    return (cons(tree->rest->value, cons(tree->value, NIL)));
  }
}

int guessLoomDefinitionArity(int arity, Object* definition, Cons* constraints) {
  if ((arity == -1) &&
      ((boolean)(definition))) {
    arity = computeLoomDescriptionArity(definition);
  }
  if (arity == -1) {
    { Object* c = NULL;
      Cons* iter000 = constraints;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        c = iter000->value;
        arity = computeLoomDescriptionArity(c);
        if (arity > 0) {
          break;
        }
      }
    }
  }
  if (arity == -1) {
    arity = 2;
  }
  return (arity);
}

Object* conjoinSentences(Cons* sentences) {
  sentences = sentences->remove(NIL);
  if (sentences == NIL) {
    return (NIL);
  }
  else if (sentences->rest == NIL) {
    return (sentences->value);
  }
  else {
    sentences = cons(SYM_LOOM_TO_KIF_STELLA_AND, sentences);
    return (sentences);
  }
}

Cons* translateLoomPartitions(Object* partitions, boolean exhaustiveP, Symbol* parentconcept) {
  { Cons* axioms = NIL;
    Cons* partitionList = NIL;

    if (!consP(partitions)) {
      partitions = consList(1, partitions);
    }
    if (consP(((Cons*)(partitions))->value)) {
      partitionList = ((Cons*)(partitions));
    }
    else {
      { Object* clause = NULL;
        Cons* iter000 = ((Cons*)(partitions));

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          clause = iter000->value;
          partitionList = cons(consList(1, clause), partitionList);
        }
      }
    }
    { Cons* clause = NULL;
      Cons* iter001 = partitionList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        clause = ((Cons*)(iter001->value));
        { Object* name = clause->value;
          Cons* concepts = ((Cons*)(clause->rest->value));
          Cons* localaxioms = NIL;

          localaxioms = cons(listO(3, SYM_LOOM_TO_KIF_PL_KERNEL_KB_MUTUALLY_DISJOINT_COLLECTION, name, NIL), localaxioms);
          if (((boolean)(concepts))) {
            localaxioms = cons(listO(3, SYM_LOOM_TO_KIF_STELLA_e, name, cons(cons(SYM_LOOM_TO_KIF_PL_KERNEL_KB_SETOF, concepts->concatenate(NIL, 0)), NIL)), localaxioms);
          }
          if (exhaustiveP) {
            localaxioms = cons(listO(3, SYM_LOOM_TO_KIF_PL_KERNEL_KB_COVERING, name, cons(parentconcept, NIL)), localaxioms);
          }
          axioms = cons(conjoinSentences(localaxioms->reverse()), axioms);
        }
      }
    }
    return (axioms);
  }
}

Cons* translateLoomCharacteristics(Object* characteristics, Symbol* name) {
  { Cons* axioms = NIL;

    if (!consP(characteristics)) {
      characteristics = consList(1, characteristics);
    }
    { Object* ch = NULL;
      Cons* iter000 = ((Cons*)(characteristics));

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        ch = iter000->value;
        { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(ch));

          if (testValue000 == KWD_LOOM_TO_KIF_SINGLE_VALUED) {
          }
          else if (testValue000 == KWD_LOOM_TO_KIF_CLOSED_WORLD) {
            axioms = cons(listO(3, SYM_LOOM_TO_KIF_PL_KERNEL_KB_CLOSED, name, NIL), axioms);
          }
          else if (testValue000 == KWD_LOOM_TO_KIF_COMMUTATIVE) {
            axioms = cons(listO(3, SYM_LOOM_TO_KIF_PL_KERNEL_KB_COMMUTATIVE, name, NIL), axioms);
          }
          else if (testValue000 == KWD_LOOM_TO_KIF_SYMMETRIC) {
            axioms = cons(listO(3, SYM_LOOM_TO_KIF_PL_KERNEL_KB_SYMMETRIC, name, NIL), axioms);
          }
          else if ((testValue000 == KWD_LOOM_TO_KIF_CLOS_CLASS) ||
              ((testValue000 == KWD_LOOM_TO_KIF_MULTIPLE_VALUED) ||
               ((testValue000 == KWD_LOOM_TO_KIF_HASH_ON_DOMAINS) ||
                ((testValue000 == KWD_LOOM_TO_KIF_NON_EXPORTED) ||
                 ((testValue000 == KWD_LOOM_TO_KIF_PERFECT) ||
                  ((testValue000 == KWD_LOOM_TO_KIF_CLOSED_ON_CONSTANTS) ||
                   ((testValue000 == KWD_LOOM_TO_KIF_BACKWARD_CHAINING) ||
                    ((testValue000 == KWD_LOOM_TO_KIF_MONOTONIC) ||
                     (testValue000 == KWD_LOOM_TO_KIF_TEMPORAL))))))))) {
          }
          else {
            std::cout << "Skipping unimplemented relation characteristic: " << "`" << ch << "'" << std::endl << "   in Loom definition of: " << "`" << name << "'" << std::endl << std::endl;
          }
        }
      }
    }
    return (((Cons*)(conjoinSentences(axioms))));
  }
}

Cons* translateLoomAnnotations(Object* annotations, Symbol* name) {
  if (!consP(annotations)) {
    annotations = consList(1, annotations);
  }
  { Cons* axioms = NIL;

    { Object* term = NULL;
      Cons* iter000 = ((Cons*)(annotations));

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        term = iter000->value;
        if (!consP(term)) {
          term = consList(1, term);
        }
        { Cons* clause = ((Cons*)(term));

          axioms = cons(cons(clause->value, cons(name, clause->rest->concatenate(NIL, 0))), axioms);
        }
      }
    }
    return (((Cons*)(conjoinSentences(axioms))));
  }
}

Cons* translateLoomDefaults(Object* defaultTree, Cons* variables) {
  return (listO(3, SYM_LOOM_TO_KIF_LOGIC_tg, helpTranslateLoomDescriptionToKif(defaultTree, variables), NIL));
}

Keyword* simplifyTopLevelLoomKeywords(Keyword* keyword) {
  if (keyword == KWD_LOOM_TO_KIF_ATTRIBUTES) {
    return (KWD_LOOM_TO_KIF_CHARACTERISTICS);
  }
  else if (keyword == KWD_LOOM_TO_KIF_PARTITION) {
    return (KWD_LOOM_TO_KIF_PARTITIONS);
  }
  else if (keyword == KWD_LOOM_TO_KIF_IMPLIES) {
    return (KWD_LOOM_TO_KIF_CONSTRAINTS);
  }
  else if (keyword == KWD_LOOM_TO_KIF_EXHAUSTIVE_PARTITION) {
    return (KWD_LOOM_TO_KIF_EXHAUSTIVE_PARTITIONS);
  }
  else {
    return (keyword);
  }
}

Cons* translateLoomDefinition(Cons* tree) {
  { Symbol* operatoR = ((Symbol*)(tree->value));
    Symbol* name = ((Symbol*)(tree->rest->value));
    StringWrapper* docstring = NULL;
    PropertyList* options = NULL;
    int arity = -1;
    Object* definition = NULL;
    Cons* constraints = NIL;
    Cons* defaults = NIL;
    Cons* axioms = NIL;
    Object* kifdefinition = NULL;
    Object* kifconstraint = NULL;
    Object* kifaxiom = NULL;

    if (((boolean)(tree->rest->rest->value)) &&
        isaP(tree->rest->rest->value, SGT_LOOM_TO_KIF_STELLA_STRING_WRAPPER)) {
      {
        docstring = ((StringWrapper*)(tree->rest->rest->value));
        { PropertyList* self000 = newPropertyList();

          self000->thePlist = tree->rest->rest->rest;
          options = self000;
        }
      }
    }
    else {
      { PropertyList* self001 = newPropertyList();

        self001->thePlist = tree->rest->rest;
        options = self001;
      }
    }
    if (getQuotedTree("((DEFCONCEPT DEFSET) \"/LOGIC\")", "/LOGIC")->memberP(operatoR)) {
      arity = 1;
      operatoR = SYM_LOOM_TO_KIF_LOGIC_DEFCONCEPT;
    }
    if (operatoR == SYM_LOOM_TO_KIF_LOGIC_DEFPROPERTY) {
      operatoR = SYM_LOOM_TO_KIF_LOGIC_DEFRELATION;
      arity = 1;
    }
    { Object* keyword = NULL;
      Object* value = NULL;
      Cons* iter000 = options->thePlist;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest->rest) {
        keyword = iter000->value;
        value = iter000->rest->value;
        keyword = simplifyTopLevelLoomKeywords(((Keyword*)(keyword)));
        { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(keyword));

          if (testValue000 == KWD_LOOM_TO_KIF_IS_PRIMITIVE) {
            constraints = cons(value, constraints);
          }
          else if (testValue000 == KWD_LOOM_TO_KIF_IS) {
            definition = value;
          }
          else if (testValue000 == KWD_LOOM_TO_KIF_CONSTRAINTS) {
            constraints = cons(value, constraints);
          }
          else if (testValue000 == KWD_LOOM_TO_KIF_DEFAULTS) {
            defaults = cons(value, defaults);
          }
          else if (testValue000 == KWD_LOOM_TO_KIF_DOMAIN) {
            constraints = cons(listO(3, SYM_LOOM_TO_KIF_LOGIC_DOMAIN, value, NIL), constraints);
            if (arity < 0) {
              arity = 2;
            }
          }
          else if (testValue000 == KWD_LOOM_TO_KIF_DOMAINS) {
            constraints = cons(cons(SYM_LOOM_TO_KIF_STELLA_DOMAINS, ((Cons*)(value))->concatenate(NIL, 0)), constraints);
            if (arity < 0) {
              arity = ((Cons*)(value))->length() + 1;
            }
          }
          else if (testValue000 == KWD_LOOM_TO_KIF_RANGE) {
            constraints = cons(listO(3, SYM_LOOM_TO_KIF_LOGIC_RANGE, value, NIL), constraints);
            if (arity < 0) {
              arity = 2;
            }
          }
          else if (testValue000 == KWD_LOOM_TO_KIF_ARITY) {
            arity = ((IntegerWrapper*)(value))->wrapperValue;
          }
          else if ((testValue000 == KWD_LOOM_TO_KIF_PARTITIONS) ||
              (testValue000 == KWD_LOOM_TO_KIF_EXHAUSTIVE_PARTITIONS)) {
            { Object* p = NULL;
              Cons* iter001 = translateLoomPartitions(value, keyword == KWD_LOOM_TO_KIF_EXHAUSTIVE_PARTITIONS, name);

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                p = iter001->value;
                axioms = cons(p, axioms);
              }
            }
          }
          else if (testValue000 == KWD_LOOM_TO_KIF_IN_PARTITION) {
            axioms = cons(listO(3, SYM_LOOM_TO_KIF_PL_KERNEL_KB_MEMBER_OF, name, cons(value, NIL)), axioms);
          }
          else if ((testValue000 == KWD_LOOM_TO_KIF_CHARACTERISTICS) ||
              (testValue000 == KWD_LOOM_TO_KIF_ATTRIBUTES)) {
            axioms = cons(translateLoomCharacteristics(value, name), axioms);
          }
          else if (testValue000 == KWD_LOOM_TO_KIF_ANNOTATIONS) {
            axioms = cons(translateLoomAnnotations(value, name), axioms);
          }
          else if (testValue000 == KWD_LOOM_TO_KIF_ROLES) {
            std::cout << ":roles OPTION NOT YET IMPLEMENTED" << std::endl;
          }
          else if (testValue000 == KWD_LOOM_TO_KIF_NAME) {
          }
          else if (testValue000 == KWD_LOOM_TO_KIF_IDENTIFIER) {
            std::cout << "Note: Definition " << "`" << name << "'" << " is also known as " << "`" << value << "'" << std::endl << std::endl;
          }
          else {
            std::cout << "Skipping unimplemented keyword: " << "`" << keyword << "'" << std::endl << "   in Loom definition: " << "`" << tree << "'" << std::endl << std::endl;
          }
        }
      }
    }
    arity = guessLoomDefinitionArity(arity, definition, constraints);
    { Cons* variables = yieldImplicitVariables(arity);
      Object* characteristics = options->lookup(KWD_LOOM_TO_KIF_CHARACTERISTICS);
      boolean converttofunctionP = ((boolean)(characteristics)) &&
          ((characteristics == KWD_LOOM_TO_KIF_SINGLE_VALUED) ||
           (consP(characteristics) &&
            ((Cons*)(characteristics))->memberP(KWD_LOOM_TO_KIF_SINGLE_VALUED)));
      Cons* resultclause = NIL;

      if (!(constraints == NIL)) {
        kifconstraint = helpTranslateLoomDescriptionToKif(conjoinSentences(constraints), variables);
      }
      { Object* defaulT = NULL;
        Cons* iter002 = defaults;

        for (; !(iter002 == NIL); iter002 = iter002->rest) {
          defaulT = iter002->value;
          axioms = cons(translateLoomDefaults(defaulT, variables), axioms);
        }
      }
      if (!(axioms == NIL)) {
        kifaxiom = conjoinSentences(axioms);
        if (kifaxiom == NIL) {
          kifaxiom = NULL;
        }
      }
      if (((boolean)(definition))) {
        kifdefinition = helpTranslateLoomDescriptionToKif(definition, variables);
      }
      if (converttofunctionP) {
        operatoR = SYM_LOOM_TO_KIF_LOGIC_DEFFUNCTION;
        resultclause = listO(3, KWD_LOOM_TO_KIF__g, ((Symbol*)(variables->last())), NIL);
        variables = variables->butLast()->consify();
      }
      return (cons(operatoR, cons(name, cons(variables, resultclause->concatenate(((((boolean)(docstring)) ? listO(3, KWD_LOOM_TO_KIF_DOCUMENTATION, docstring, NIL) : NIL))->concatenate(((((boolean)(kifdefinition)) ? listO(3, KWD_LOOM_TO_KIF_llegg, kifdefinition, NIL) : NIL))->concatenate(((((boolean)(kifconstraint)) ? listO(3, KWD_LOOM_TO_KIF_egg, kifconstraint, NIL) : NIL))->concatenate(((((boolean)(kifaxiom)) ? listO(3, KWD_LOOM_TO_KIF_AXIOMS, kifaxiom, NIL) : NIL))->concatenate(NIL, 0), 0), 0), 0), 0)))));
    }
  }
}

Cons* translateLoomContextChange(Cons* tree, boolean needsquoteP) {
  { Object* contextform = tree->rest->value;

    { Surrogate* testValue000 = safePrimaryType(contextform);

      if (subtypeOfStringP(testValue000)) {
        { Object* contextform000 = contextform;
          StringWrapper* contextform = ((StringWrapper*)(contextform000));

          return (listO(3, SYM_LOOM_TO_KIF_STELLA_IN_MODULE, contextform, NIL));
        }
      }
      else if (subtypeOfSymbolP(testValue000)) {
        { Object* contextform001 = contextform;
          Symbol* contextform = ((Symbol*)(contextform001));

          if (needsquoteP) {
            {
              if (!(stringEqlP(contextform->symbolName, "SAVEDCONTEXT"))) {
                *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't translate " << "`" << tree << "'" << " with a non-constant argument" << std::endl;
              }
              return (NULL);
            }
          }
          else {
            return (listO(3, SYM_LOOM_TO_KIF_STELLA_IN_MODULE, wrapString(contextform->symbolName), NIL));
          }
        }
      }
      else if (testValue000 == SGT_LOOM_TO_KIF_STELLA_CONS) {
        { Object* contextform002 = contextform;
          Cons* contextform = ((Cons*)(contextform002));

          return (translateLoomContextChange(contextform, false));
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
}

void helpStartupLoomToKif1() {
  {
    SGT_LOOM_TO_KIF_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
    SYM_LOOM_TO_KIF_STELLA_INVERSE = ((Symbol*)(internRigidSymbolWrtModule("INVERSE", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_INVERSE = ((Symbol*)(internRigidSymbolWrtModule("INVERSE", getStellaModule("/PL-KERNEL-KB", true), 0)));
    KWD_LOOM_TO_KIF_BINARY = ((Keyword*)(internRigidSymbolWrtModule("BINARY", NULL, 2)));
    KWD_LOOM_TO_KIF_UNARY = ((Keyword*)(internRigidSymbolWrtModule("UNARY", NULL, 2)));
    SYM_LOOM_TO_KIF_LOGIC_KAPPA = ((Symbol*)(internRigidSymbolWrtModule("KAPPA", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_AT_LEAST = ((Symbol*)(internRigidSymbolWrtModule("AT-LEAST", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_AT_MOST = ((Symbol*)(internRigidSymbolWrtModule("AT-MOST", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_EXACTLY = ((Symbol*)(internRigidSymbolWrtModule("EXACTLY", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_ALL = ((Symbol*)(internRigidSymbolWrtModule("ALL", NULL, 0)));
    SYM_LOOM_TO_KIF_STELLA_SOME = ((Symbol*)(internRigidSymbolWrtModule("SOME", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_LOGIC_THE = ((Symbol*)(internRigidSymbolWrtModule("THE", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_FILLED_BY = ((Symbol*)(internRigidSymbolWrtModule("FILLED-BY", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_FILLERS = ((Symbol*)(internRigidSymbolWrtModule("FILLERS", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_NOT_FILLED_BY = ((Symbol*)(internRigidSymbolWrtModule("NOT-FILLED-BY", NULL, 0)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_QUALIFIED_RANGE_CARDINALITY_LOWER_BOUND = ((Symbol*)(internRigidSymbolWrtModule("QUALIFIED-RANGE-CARDINALITY-LOWER-BOUND", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_QUALIFIED_RANGE_CARDINALITY_UPPER_BOUND = ((Symbol*)(internRigidSymbolWrtModule("QUALIFIED-RANGE-CARDINALITY-UPPER-BOUND", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_QUALIFIED_RANGE_CARDINALITY = ((Symbol*)(internRigidSymbolWrtModule("QUALIFIED-RANGE-CARDINALITY", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_RANGE_CARDINALITY_LOWER_BOUND = ((Symbol*)(internRigidSymbolWrtModule("RANGE-CARDINALITY-LOWER-BOUND", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_RANGE_CARDINALITY_UPPER_BOUND = ((Symbol*)(internRigidSymbolWrtModule("RANGE-CARDINALITY-UPPER-BOUND", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_RANGE_CARDINALITY = ((Symbol*)(internRigidSymbolWrtModule("RANGE-CARDINALITY", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_TO_KIF_STELLA_EXISTS = ((Symbol*)(internRigidSymbolWrtModule("EXISTS", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_STELLA_eg = ((Symbol*)(internRigidSymbolWrtModule("=>", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_RANGE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("RANGE-TYPE", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_TO_KIF_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_LOGIC_RELATES = ((Symbol*)(internRigidSymbolWrtModule("RELATES", NULL, 0)));
    SGT_LOOM_TO_KIF_STELLA_NUMBER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SYM_LOOM_TO_KIF_LOGIC_FOR_SOME = ((Symbol*)(internRigidSymbolWrtModule("FOR-SOME", NULL, 0)));
    SYM_LOOM_TO_KIF_STELLA_FORALL = ((Symbol*)(internRigidSymbolWrtModule("FORALL", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_LOGIC_THROUGH = ((Symbol*)(internRigidSymbolWrtModule("THROUGH", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_INTERVALii = ((Symbol*)(internRigidSymbolWrtModule("INTERVAL++", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_INTERVALi_ = ((Symbol*)(internRigidSymbolWrtModule("INTERVAL+-", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_INTERVAL_i = ((Symbol*)(internRigidSymbolWrtModule("INTERVAL-+", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_INTERVAL__ = ((Symbol*)(internRigidSymbolWrtModule("INTERVAL--", NULL, 0)));
    SYM_LOOM_TO_KIF_STELLA_el = ((Symbol*)(internRigidSymbolWrtModule("=<", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_STELLA_l = ((Symbol*)(internRigidSymbolWrtModule("<", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_STELLA_ge = ((Symbol*)(internRigidSymbolWrtModule(">=", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_STELLA_g = ((Symbol*)(internRigidSymbolWrtModule(">", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_STELLA_OR = ((Symbol*)(internRigidSymbolWrtModule("OR", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_LOGIC_SAME_AS = ((Symbol*)(internRigidSymbolWrtModule("SAME-AS", NULL, 0)));
    SYM_LOOM_TO_KIF_STELLA_le = ((Symbol*)(internRigidSymbolWrtModule("<=", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_LOGIC_lg = ((Symbol*)(internRigidSymbolWrtModule("<>", NULL, 0)));
    SYM_LOOM_TO_KIF_STELLA_e = ((Symbol*)(internRigidSymbolWrtModule("=", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_LOGIC_ONE_OF = ((Symbol*)(internRigidSymbolWrtModule("ONE-OF", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_THE_ORDERED_SET = ((Symbol*)(internRigidSymbolWrtModule("THE-ORDERED-SET", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_SATISFIES = ((Symbol*)(internRigidSymbolWrtModule("SATISFIES", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_DOMAIN = ((Symbol*)(internRigidSymbolWrtModule("DOMAIN", NULL, 0)));
    SYM_LOOM_TO_KIF_STELLA_DOMAINS = ((Symbol*)(internRigidSymbolWrtModule("DOMAINS", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_LOGIC_RANGE = ((Symbol*)(internRigidSymbolWrtModule("RANGE", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_COMPOSE = ((Symbol*)(internRigidSymbolWrtModule("COMPOSE", NULL, 0)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_MEMBER_OF = ((Symbol*)(internRigidSymbolWrtModule("MEMBER-OF", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_SETOF = ((Symbol*)(internRigidSymbolWrtModule("SETOF", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_LISTOF = ((Symbol*)(internRigidSymbolWrtModule("LISTOF", getStellaModule("/PL-KERNEL-KB", true), 0)));
    KWD_LOOM_TO_KIF_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    SYM_LOOM_TO_KIF_LOGIC_ABOUT = ((Symbol*)(internRigidSymbolWrtModule("ABOUT", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_CREATE = ((Symbol*)(internRigidSymbolWrtModule("CREATE", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_SUPERRELATIONS = ((Symbol*)(internRigidSymbolWrtModule("SUPERRELATIONS", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_SUPERCONCEPTS = ((Symbol*)(internRigidSymbolWrtModule("SUPERCONCEPTS", NULL, 0)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_SUBSET_OF = ((Symbol*)(internRigidSymbolWrtModule("SUBSET-OF", getStellaModule("/PL-KERNEL-KB", true), 0)));
  }
}

void helpStartupLoomToKif2() {
  {
    SYM_LOOM_TO_KIF_STELLA_QUOTE = ((Symbol*)(internRigidSymbolWrtModule("QUOTE", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_STELLA_RETRACT = ((Symbol*)(internRigidSymbolWrtModule("RETRACT", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_STELLA_ASSERT = ((Symbol*)(internRigidSymbolWrtModule("ASSERT", getStellaModule("/STELLA", true), 0)));
    KWD_LOOM_TO_KIF_3_VALUED_P = ((Keyword*)(internRigidSymbolWrtModule("3-VALUED-P", NULL, 2)));
    SYM_LOOM_TO_KIF_STELLA_ASK = ((Symbol*)(internRigidSymbolWrtModule("ASK", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_STELLA_CONSIFY = ((Symbol*)(internRigidSymbolWrtModule("CONSIFY", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_STELLA_RETRIEVE = ((Symbol*)(internRigidSymbolWrtModule("RETRIEVE", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_STELLA_PROGN = ((Symbol*)(internRigidSymbolWrtModule("PROGN", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_LOGIC_EVAL_WHEN = ((Symbol*)(internRigidSymbolWrtModule("EVAL-WHEN", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_TELL = ((Symbol*)(internRigidSymbolWrtModule("TELL", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_FORGET = ((Symbol*)(internRigidSymbolWrtModule("FORGET", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_TELLM = ((Symbol*)(internRigidSymbolWrtModule("TELLM", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_FORGETM = ((Symbol*)(internRigidSymbolWrtModule("FORGETM", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_CREATEM = ((Symbol*)(internRigidSymbolWrtModule("CREATEM", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_DEFCONCEPT = ((Symbol*)(internRigidSymbolWrtModule("DEFCONCEPT", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_DEFSET = ((Symbol*)(internRigidSymbolWrtModule("DEFSET", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_DEFRELATION = ((Symbol*)(internRigidSymbolWrtModule("DEFRELATION", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_DEFPROPERTY = ((Symbol*)(internRigidSymbolWrtModule("DEFPROPERTY", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_DEFCONTEXT = ((Symbol*)(internRigidSymbolWrtModule("DEFCONTEXT", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_ADD_VALUE = ((Symbol*)(internRigidSymbolWrtModule("ADD-VALUE", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_SET_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SET-VALUE", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_FADD_VALUE = ((Symbol*)(internRigidSymbolWrtModule("FADD-VALUE", NULL, 0)));
    SYM_LOOM_TO_KIF_STELLA_CHANGE_CONTEXT = ((Symbol*)(internRigidSymbolWrtModule("CHANGE-CONTEXT", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_LOGIC_IN_CONTEXT = ((Symbol*)(internRigidSymbolWrtModule("IN-CONTEXT", NULL, 0)));
    SYM_LOOM_TO_KIF_LOGIC_IN_KB = ((Symbol*)(internRigidSymbolWrtModule("IN-KB", NULL, 0)));
    SYM_LOOM_TO_KIF_STELLA_CC = ((Symbol*)(internRigidSymbolWrtModule("CC", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_STELLA_NIL = ((Symbol*)(internRigidSymbolWrtModule("NIL", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_LOGIC_IN_DIALECT = ((Symbol*)(internRigidSymbolWrtModule("IN-DIALECT", NULL, 0)));
    KWD_LOOM_TO_KIF_KIF = ((Keyword*)(internRigidSymbolWrtModule("KIF", NULL, 2)));
    SYM_LOOM_TO_KIF_STELLA_IN_MODULE = ((Symbol*)(internRigidSymbolWrtModule("IN-MODULE", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_STELLA_THING = ((Symbol*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_MUTUALLY_DISJOINT_COLLECTION = ((Symbol*)(internRigidSymbolWrtModule("MUTUALLY-DISJOINT-COLLECTION", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_COVERING = ((Symbol*)(internRigidSymbolWrtModule("COVERING", getStellaModule("/PL-KERNEL-KB", true), 0)));
    KWD_LOOM_TO_KIF_SINGLE_VALUED = ((Keyword*)(internRigidSymbolWrtModule("SINGLE-VALUED", NULL, 2)));
    KWD_LOOM_TO_KIF_CLOSED_WORLD = ((Keyword*)(internRigidSymbolWrtModule("CLOSED-WORLD", NULL, 2)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_CLOSED = ((Symbol*)(internRigidSymbolWrtModule("CLOSED", getStellaModule("/PL-KERNEL-KB", true), 0)));
    KWD_LOOM_TO_KIF_COMMUTATIVE = ((Keyword*)(internRigidSymbolWrtModule("COMMUTATIVE", NULL, 2)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_COMMUTATIVE = ((Symbol*)(internRigidSymbolWrtModule("COMMUTATIVE", getStellaModule("/PL-KERNEL-KB", true), 0)));
    KWD_LOOM_TO_KIF_SYMMETRIC = ((Keyword*)(internRigidSymbolWrtModule("SYMMETRIC", NULL, 2)));
    SYM_LOOM_TO_KIF_PL_KERNEL_KB_SYMMETRIC = ((Symbol*)(internRigidSymbolWrtModule("SYMMETRIC", getStellaModule("/PL-KERNEL-KB", true), 0)));
    KWD_LOOM_TO_KIF_CLOS_CLASS = ((Keyword*)(internRigidSymbolWrtModule("CLOS-CLASS", NULL, 2)));
    KWD_LOOM_TO_KIF_MULTIPLE_VALUED = ((Keyword*)(internRigidSymbolWrtModule("MULTIPLE-VALUED", NULL, 2)));
    KWD_LOOM_TO_KIF_HASH_ON_DOMAINS = ((Keyword*)(internRigidSymbolWrtModule("HASH-ON-DOMAINS", NULL, 2)));
    KWD_LOOM_TO_KIF_NON_EXPORTED = ((Keyword*)(internRigidSymbolWrtModule("NON-EXPORTED", NULL, 2)));
    KWD_LOOM_TO_KIF_PERFECT = ((Keyword*)(internRigidSymbolWrtModule("PERFECT", NULL, 2)));
    KWD_LOOM_TO_KIF_CLOSED_ON_CONSTANTS = ((Keyword*)(internRigidSymbolWrtModule("CLOSED-ON-CONSTANTS", NULL, 2)));
    KWD_LOOM_TO_KIF_BACKWARD_CHAINING = ((Keyword*)(internRigidSymbolWrtModule("BACKWARD-CHAINING", NULL, 2)));
    KWD_LOOM_TO_KIF_MONOTONIC = ((Keyword*)(internRigidSymbolWrtModule("MONOTONIC", NULL, 2)));
    KWD_LOOM_TO_KIF_TEMPORAL = ((Keyword*)(internRigidSymbolWrtModule("TEMPORAL", NULL, 2)));
    SYM_LOOM_TO_KIF_LOGIC_tg = ((Symbol*)(internRigidSymbolWrtModule("~>", NULL, 0)));
    KWD_LOOM_TO_KIF_ATTRIBUTES = ((Keyword*)(internRigidSymbolWrtModule("ATTRIBUTES", NULL, 2)));
    KWD_LOOM_TO_KIF_CHARACTERISTICS = ((Keyword*)(internRigidSymbolWrtModule("CHARACTERISTICS", NULL, 2)));
    KWD_LOOM_TO_KIF_PARTITION = ((Keyword*)(internRigidSymbolWrtModule("PARTITION", NULL, 2)));
    KWD_LOOM_TO_KIF_PARTITIONS = ((Keyword*)(internRigidSymbolWrtModule("PARTITIONS", NULL, 2)));
    KWD_LOOM_TO_KIF_IMPLIES = ((Keyword*)(internRigidSymbolWrtModule("IMPLIES", NULL, 2)));
    KWD_LOOM_TO_KIF_CONSTRAINTS = ((Keyword*)(internRigidSymbolWrtModule("CONSTRAINTS", NULL, 2)));
    KWD_LOOM_TO_KIF_EXHAUSTIVE_PARTITION = ((Keyword*)(internRigidSymbolWrtModule("EXHAUSTIVE-PARTITION", NULL, 2)));
    KWD_LOOM_TO_KIF_EXHAUSTIVE_PARTITIONS = ((Keyword*)(internRigidSymbolWrtModule("EXHAUSTIVE-PARTITIONS", NULL, 2)));
    SGT_LOOM_TO_KIF_STELLA_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("STRING-WRAPPER", getStellaModule("/STELLA", true), 1)));
  }
}

void startupLoomToKif() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupLoomToKif1();
      helpStartupLoomToKif2();
      KWD_LOOM_TO_KIF_IS_PRIMITIVE = ((Keyword*)(internRigidSymbolWrtModule("IS-PRIMITIVE", NULL, 2)));
      KWD_LOOM_TO_KIF_IS = ((Keyword*)(internRigidSymbolWrtModule("IS", NULL, 2)));
      KWD_LOOM_TO_KIF_DEFAULTS = ((Keyword*)(internRigidSymbolWrtModule("DEFAULTS", NULL, 2)));
      KWD_LOOM_TO_KIF_DOMAIN = ((Keyword*)(internRigidSymbolWrtModule("DOMAIN", NULL, 2)));
      KWD_LOOM_TO_KIF_DOMAINS = ((Keyword*)(internRigidSymbolWrtModule("DOMAINS", NULL, 2)));
      KWD_LOOM_TO_KIF_RANGE = ((Keyword*)(internRigidSymbolWrtModule("RANGE", NULL, 2)));
      KWD_LOOM_TO_KIF_ARITY = ((Keyword*)(internRigidSymbolWrtModule("ARITY", NULL, 2)));
      KWD_LOOM_TO_KIF_IN_PARTITION = ((Keyword*)(internRigidSymbolWrtModule("IN-PARTITION", NULL, 2)));
      KWD_LOOM_TO_KIF_ANNOTATIONS = ((Keyword*)(internRigidSymbolWrtModule("ANNOTATIONS", NULL, 2)));
      KWD_LOOM_TO_KIF_ROLES = ((Keyword*)(internRigidSymbolWrtModule("ROLES", NULL, 2)));
      KWD_LOOM_TO_KIF_NAME = ((Keyword*)(internRigidSymbolWrtModule("NAME", NULL, 2)));
      KWD_LOOM_TO_KIF_IDENTIFIER = ((Keyword*)(internRigidSymbolWrtModule("IDENTIFIER", NULL, 2)));
      SYM_LOOM_TO_KIF_LOGIC_DEFFUNCTION = ((Symbol*)(internRigidSymbolWrtModule("DEFFUNCTION", NULL, 0)));
      KWD_LOOM_TO_KIF__g = ((Keyword*)(internRigidSymbolWrtModule("->", NULL, 2)));
      KWD_LOOM_TO_KIF_DOCUMENTATION = ((Keyword*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 2)));
      KWD_LOOM_TO_KIF_llegg = ((Keyword*)(internRigidSymbolWrtModule("<<=>>", NULL, 2)));
      KWD_LOOM_TO_KIF_egg = ((Keyword*)(internRigidSymbolWrtModule("=>>", NULL, 2)));
      KWD_LOOM_TO_KIF_AXIOMS = ((Keyword*)(internRigidSymbolWrtModule("AXIOMS", NULL, 2)));
      SYM_LOOM_TO_KIF_LOGIC_STARTUP_LOOM_TO_KIF = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-LOOM-TO-KIF", NULL, 0)));
      SYM_LOOM_TO_KIF_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("LOOM-ARGUMENT-DESCRIPTION-TO-KIF", "(DEFUN (LOOM-ARGUMENT-DESCRIPTION-TO-KIF OBJECT) ((TREE OBJECT) (ARITY KEYWORD)))", ((cpp_function_code)(&loomArgumentDescriptionToKif)), NULL);
      defineFunctionObject("LOOM-RESTRICTION-TO-KIF", "(DEFUN (LOOM-RESTRICTION-TO-KIF CONS) ((TREE CONS) (IMPLICITVARIABLE SYMBOL)))", ((cpp_function_code)(&loomRestrictionToKif)), NULL);
      defineFunctionObject("LOOM-RELATES-TO-KIF", "(DEFUN (LOOM-RELATES-TO-KIF CONS) ((TREE CONS) (IMPLICITVARIABLES (CONS OF SYMBOL))))", ((cpp_function_code)(&loomRelatesToKif)), NULL);
      defineFunctionObject("SUBSTITUTE-VARIABLES-IN-TREE", "(DEFUN SUBSTITUTE-VARIABLES-IN-TREE ((TREE CONS) (SUBSTITUTION CONS)))", ((cpp_function_code)(&substituteVariablesInTree)), NULL);
      defineFunctionObject("LOOM-THROUGH-TO-KIF", "(DEFUN (LOOM-THROUGH-TO-KIF CONS) ((TREE CONS) (IMPLICITVARIABLES (CONS OF SYMBOL))))", ((cpp_function_code)(&loomThroughToKif)), NULL);
      defineFunctionObject("LOOM-SATISFIES-TO-KIF", "(DEFUN (LOOM-SATISFIES-TO-KIF CONS) ((TREE CONS) (IMPLICITVARIABLES (CONS OF SYMBOL))))", ((cpp_function_code)(&loomSatisfiesToKif)), NULL);
      defineFunctionObject("LOOM-DESCRIPTION-TO-KIF", "(DEFUN (LOOM-DESCRIPTION-TO-KIF CONS) ((TREE OBJECT) (IMPLICITVARIABLES (CONS OF SYMBOL))))", ((cpp_function_code)(&loomDescriptionToKif)), NULL);
      defineFunctionObject("LOOM-DESCRIPTION-OPERATOR?", "(DEFUN (LOOM-DESCRIPTION-OPERATOR? BOOLEAN) ((SELF OBJECT)))", ((cpp_function_code)(&loomDescriptionOperatorP)), NULL);
      defineFunctionObject("LOOM-SENTENCE-TO-KIF", "(DEFUN (LOOM-SENTENCE-TO-KIF OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&loomSentenceToKif)), NULL);
      defineFunctionObject("COMPUTE-LOOM-DESCRIPTION-ARITY", "(DEFUN (COMPUTE-LOOM-DESCRIPTION-ARITY INTEGER) ((TREE OBJECT)))", ((cpp_function_code)(&computeLoomDescriptionArity)), NULL);
      defineFunctionObject("ELIMINATE-LOOM-KEYWORDS", "(DEFUN (ELIMINATE-LOOM-KEYWORDS OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&eliminateLoomKeywords)), NULL);
      defineFunctionObject("YIELD-IMPLICIT-VARIABLES", "(DEFUN (YIELD-IMPLICIT-VARIABLES (CONS OF SYMBOL)) ((ARITY INTEGER)))", ((cpp_function_code)(&yieldImplicitVariables)), NULL);
      defineFunctionObject("HELP-TRANSLATE-LOOM-DESCRIPTION-TO-KIF", "(DEFUN (HELP-TRANSLATE-LOOM-DESCRIPTION-TO-KIF CONS) ((TREE OBJECT) (IMPLICITVARIABLES (CONS OF SYMBOL))))", ((cpp_function_code)(&helpTranslateLoomDescriptionToKif)), NULL);
      defineFunctionObject("TRANSLATE-LOOM-DESCRIPTION-TO-KIF", "(DEFUN (TRANSLATE-LOOM-DESCRIPTION-TO-KIF CONS) ((TREE OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&translateLoomDescriptionToKif)), NULL);
      defineFunctionObject("TRANSLATE-LOOM-SENTENCE-TO-KIF", "(DEFUN (TRANSLATE-LOOM-SENTENCE-TO-KIF OBJECT) ((TREE OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&translateLoomSentenceToKif)), NULL);
      defineFunctionObject("TRANSLATE-LOOM-ASSERTIONS", "(DEFUN (TRANSLATE-LOOM-ASSERTIONS CONS) ((TREE CONS) (RETRACT? BOOLEAN)) :PUBLIC? TRUE)", ((cpp_function_code)(&translateLoomAssertions)), NULL);
      defineFunctionObject("TRANSLATE-LOOM-ASK", "(DEFUN (TRANSLATE-LOOM-ASK CONS) ((TREE CONS)) :PUBLIC? TRUE)", ((cpp_function_code)(&translateLoomAsk)), NULL);
      defineFunctionObject("TRANSLATE-LOOM-RETRIEVE", "(DEFUN (TRANSLATE-LOOM-RETRIEVE CONS) ((TREE CONS)) :PUBLIC? TRUE)", ((cpp_function_code)(&translateLoomRetrieve)), NULL);
      defineFunctionObject("TRANSLATE-ONE-LOOM-FORM", "(DEFUN (TRANSLATE-ONE-LOOM-FORM CONS) ((TREE OBJECT)))", ((cpp_function_code)(&translateOneLoomForm)), NULL);
      defineFunctionObject("SAFE-GET-NEXT-S-EXPRESSION", "(DEFUN (SAFE-GET-NEXT-S-EXPRESSION OBJECT) ((ITER S-EXPRESSION-ITERATOR)))", ((cpp_function_code)(&safeGetNextSExpression)), NULL);
      defineFunctionObject("DESTRUCTIVELY-UNQUOTE-TOP-LEVEL", "(DEFUN DESTRUCTIVELY-UNQUOTE-TOP-LEVEL ((TREE CONS)))", ((cpp_function_code)(&destructivelyUnquoteTopLevel)), NULL);
      defineFunctionObject("TRANSLATE-LOOM-FILE", "(DEFUN TRANSLATE-LOOM-FILE ((INPUT FILE-NAME) (OUTPUT FILE-NAME)) :DOCUMENTATION \"Translate the Loom file `input' to PowerLoom and write the\ntranslation to the file `output'.  Note that this will only\nwork for fairly vanilla Loom files that do not contain any\nLisp-isms.  It might require to clean the Loom file manually\nbefore this translation will work.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&translateLoomFile)), ((cpp_function_code)(&translateLoomFileEvaluatorWrapper)));
      defineFunctionObject("TRANSLATE-LOOM-STATEMENT", "(DEFUN (TRANSLATE-LOOM-STATEMENT CONS) ((TREE CONS)) :PUBLIC? TRUE)", ((cpp_function_code)(&translateLoomStatement)), NULL);
      defineFunctionObject("TRANSLATE-LOOM-CREATE-CLAUSE", "(DEFUN (TRANSLATE-LOOM-CREATE-CLAUSE CONS) ((TREE CONS)))", ((cpp_function_code)(&translateLoomCreateClause)), NULL);
      defineFunctionObject("GUESS-LOOM-DEFINITION-ARITY", "(DEFUN (GUESS-LOOM-DEFINITION-ARITY INTEGER) ((ARITY INTEGER) (DEFINITION OBJECT) (CONSTRAINTS CONS)))", ((cpp_function_code)(&guessLoomDefinitionArity)), NULL);
      defineFunctionObject("CONJOIN-SENTENCES", "(DEFUN (CONJOIN-SENTENCES OBJECT) ((SENTENCES CONS)))", ((cpp_function_code)(&conjoinSentences)), NULL);
      defineFunctionObject("TRANSLATE-LOOM-PARTITIONS", "(DEFUN (TRANSLATE-LOOM-PARTITIONS CONS) ((PARTITIONS OBJECT) (EXHAUSTIVE? BOOLEAN) (PARENTCONCEPT SYMBOL)))", ((cpp_function_code)(&translateLoomPartitions)), NULL);
      defineFunctionObject("TRANSLATE-LOOM-CHARACTERISTICS", "(DEFUN (TRANSLATE-LOOM-CHARACTERISTICS CONS) ((CHARACTERISTICS OBJECT) (NAME SYMBOL)))", ((cpp_function_code)(&translateLoomCharacteristics)), NULL);
      defineFunctionObject("TRANSLATE-LOOM-ANNOTATIONS", "(DEFUN (TRANSLATE-LOOM-ANNOTATIONS CONS) ((ANNOTATIONS OBJECT) (NAME SYMBOL)))", ((cpp_function_code)(&translateLoomAnnotations)), NULL);
      defineFunctionObject("TRANSLATE-LOOM-DEFAULTS", "(DEFUN (TRANSLATE-LOOM-DEFAULTS CONS) ((DEFAULT-TREE OBJECT) (VARIABLES CONS)))", ((cpp_function_code)(&translateLoomDefaults)), NULL);
      defineFunctionObject("SIMPLIFY-TOP-LEVEL-LOOM-KEYWORDS", "(DEFUN (SIMPLIFY-TOP-LEVEL-LOOM-KEYWORDS KEYWORD) ((KEYWORD KEYWORD)))", ((cpp_function_code)(&simplifyTopLevelLoomKeywords)), NULL);
      defineFunctionObject("TRANSLATE-LOOM-DEFINITION", "(DEFUN (TRANSLATE-LOOM-DEFINITION CONS) ((TREE CONS)) :PUBLIC? TRUE)", ((cpp_function_code)(&translateLoomDefinition)), NULL);
      defineFunctionObject("TRANSLATE-LOOM-CONTEXT-CHANGE", "(DEFUN (TRANSLATE-LOOM-CONTEXT-CHANGE CONS) ((TREE CONS) (NEEDSQUOTE? BOOLEAN)))", ((cpp_function_code)(&translateLoomContextChange)), NULL);
      defineFunctionObject("STARTUP-LOOM-TO-KIF", "(DEFUN STARTUP-LOOM-TO-KIF () :PUBLIC? TRUE)", ((cpp_function_code)(&startupLoomToKif)), NULL);
      { MethodSlot* function = lookupFunction(SYM_LOOM_TO_KIF_LOGIC_STARTUP_LOOM_TO_KIF);

        setDynamicSlotValue(function->dynamicSlots, SYM_LOOM_TO_KIF_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupLoomToKif"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
    }
  }
}

Surrogate* SGT_LOOM_TO_KIF_STELLA_CONS = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_INVERSE = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_INVERSE = NULL;

Keyword* KWD_LOOM_TO_KIF_BINARY = NULL;

Keyword* KWD_LOOM_TO_KIF_UNARY = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_KAPPA = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_AT_LEAST = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_AT_MOST = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_EXACTLY = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_ALL = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_SOME = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_THE = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_FILLED_BY = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_FILLERS = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_NOT_FILLED_BY = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_QUALIFIED_RANGE_CARDINALITY_LOWER_BOUND = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_QUALIFIED_RANGE_CARDINALITY_UPPER_BOUND = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_QUALIFIED_RANGE_CARDINALITY = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_RANGE_CARDINALITY_LOWER_BOUND = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_RANGE_CARDINALITY_UPPER_BOUND = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_RANGE_CARDINALITY = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_EXISTS = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_eg = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_AND = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_RANGE_TYPE = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_NOT = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_RELATES = NULL;

Surrogate* SGT_LOOM_TO_KIF_STELLA_NUMBER_WRAPPER = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_FOR_SOME = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_FORALL = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_THROUGH = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_INTERVALii = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_INTERVALi_ = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_INTERVAL_i = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_INTERVAL__ = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_el = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_l = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_ge = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_g = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_OR = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_SAME_AS = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_le = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_lg = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_e = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_ONE_OF = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_THE_ORDERED_SET = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_SATISFIES = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_DOMAIN = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_DOMAINS = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_RANGE = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_COMPOSE = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_MEMBER_OF = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_SETOF = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_LISTOF = NULL;

Keyword* KWD_LOOM_TO_KIF_ERROR = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_ABOUT = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_CREATE = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_SUPERRELATIONS = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_SUPERCONCEPTS = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_SUBSET_OF = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_QUOTE = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_RETRACT = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_ASSERT = NULL;

Keyword* KWD_LOOM_TO_KIF_3_VALUED_P = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_ASK = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_NULL = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_CONSIFY = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_RETRIEVE = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_PROGN = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_EVAL_WHEN = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_TELL = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_FORGET = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_TELLM = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_FORGETM = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_CREATEM = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_DEFCONCEPT = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_DEFSET = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_DEFRELATION = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_DEFPROPERTY = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_DEFCONTEXT = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_ADD_VALUE = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_SET_VALUE = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_FADD_VALUE = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_CHANGE_CONTEXT = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_IN_CONTEXT = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_IN_KB = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_CC = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_NIL = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_IN_DIALECT = NULL;

Keyword* KWD_LOOM_TO_KIF_KIF = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_IN_MODULE = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_THING = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_MUTUALLY_DISJOINT_COLLECTION = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_COVERING = NULL;

Keyword* KWD_LOOM_TO_KIF_SINGLE_VALUED = NULL;

Keyword* KWD_LOOM_TO_KIF_CLOSED_WORLD = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_CLOSED = NULL;

Keyword* KWD_LOOM_TO_KIF_COMMUTATIVE = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_COMMUTATIVE = NULL;

Keyword* KWD_LOOM_TO_KIF_SYMMETRIC = NULL;

Symbol* SYM_LOOM_TO_KIF_PL_KERNEL_KB_SYMMETRIC = NULL;

Keyword* KWD_LOOM_TO_KIF_CLOS_CLASS = NULL;

Keyword* KWD_LOOM_TO_KIF_MULTIPLE_VALUED = NULL;

Keyword* KWD_LOOM_TO_KIF_HASH_ON_DOMAINS = NULL;

Keyword* KWD_LOOM_TO_KIF_NON_EXPORTED = NULL;

Keyword* KWD_LOOM_TO_KIF_PERFECT = NULL;

Keyword* KWD_LOOM_TO_KIF_CLOSED_ON_CONSTANTS = NULL;

Keyword* KWD_LOOM_TO_KIF_BACKWARD_CHAINING = NULL;

Keyword* KWD_LOOM_TO_KIF_MONOTONIC = NULL;

Keyword* KWD_LOOM_TO_KIF_TEMPORAL = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_tg = NULL;

Keyword* KWD_LOOM_TO_KIF_ATTRIBUTES = NULL;

Keyword* KWD_LOOM_TO_KIF_CHARACTERISTICS = NULL;

Keyword* KWD_LOOM_TO_KIF_PARTITION = NULL;

Keyword* KWD_LOOM_TO_KIF_PARTITIONS = NULL;

Keyword* KWD_LOOM_TO_KIF_IMPLIES = NULL;

Keyword* KWD_LOOM_TO_KIF_CONSTRAINTS = NULL;

Keyword* KWD_LOOM_TO_KIF_EXHAUSTIVE_PARTITION = NULL;

Keyword* KWD_LOOM_TO_KIF_EXHAUSTIVE_PARTITIONS = NULL;

Surrogate* SGT_LOOM_TO_KIF_STELLA_STRING_WRAPPER = NULL;

Keyword* KWD_LOOM_TO_KIF_IS_PRIMITIVE = NULL;

Keyword* KWD_LOOM_TO_KIF_IS = NULL;

Keyword* KWD_LOOM_TO_KIF_DEFAULTS = NULL;

Keyword* KWD_LOOM_TO_KIF_DOMAIN = NULL;

Keyword* KWD_LOOM_TO_KIF_DOMAINS = NULL;

Keyword* KWD_LOOM_TO_KIF_RANGE = NULL;

Keyword* KWD_LOOM_TO_KIF_ARITY = NULL;

Keyword* KWD_LOOM_TO_KIF_IN_PARTITION = NULL;

Keyword* KWD_LOOM_TO_KIF_ANNOTATIONS = NULL;

Keyword* KWD_LOOM_TO_KIF_ROLES = NULL;

Keyword* KWD_LOOM_TO_KIF_NAME = NULL;

Keyword* KWD_LOOM_TO_KIF_IDENTIFIER = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_DEFFUNCTION = NULL;

Keyword* KWD_LOOM_TO_KIF__g = NULL;

Keyword* KWD_LOOM_TO_KIF_DOCUMENTATION = NULL;

Keyword* KWD_LOOM_TO_KIF_llegg = NULL;

Keyword* KWD_LOOM_TO_KIF_egg = NULL;

Keyword* KWD_LOOM_TO_KIF_AXIOMS = NULL;

Symbol* SYM_LOOM_TO_KIF_LOGIC_STARTUP_LOOM_TO_KIF = NULL;

Symbol* SYM_LOOM_TO_KIF_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
