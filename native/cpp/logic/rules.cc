//  -*- Mode: C++ -*-

// rules.cc

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

List* findMatchableGoals(Proposition* forallprop, Keyword* headortail) {
  { int index = ((headortail == KWD_RULES_HEAD) ? 1 : 0);
    Proposition* proposition = ((Proposition*)((forallprop->arguments->theArray)[index]));
    Cons* variables = NIL;
    List* resultlist = newList();

    { PatternVariable* v = NULL;
      Vector* vector000 = ((Vector*)(dynamicSlotValue(forallprop->dynamicSlots, SYM_RULES_LOGIC_IO_VARIABLES, NULL)));
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        v = ((PatternVariable*)((vector000->theArray)[index000]));
        variables = cons(v, variables);
      }
    }
    if (variables->length() > 1) {
      if (headortail == KWD_RULES_TAIL) {
        { Keyword* testValue000 = proposition->kind;

          if (testValue000 == KWD_RULES_AND) {
            { Object* g = NULL;
              Vector* vector001 = proposition->arguments;
              int index001 = 0;
              int length001 = vector001->length();

              for  (; index001 < length001; 
                    index001 = index001 + 1) {
                g = (vector001->theArray)[index001];
                collectMatchingRuleGoals(((Proposition*)(g)), variables, KWD_RULES_TAIL, resultlist);
              }
            }
            return (resultlist);
          }
          else if (testValue000 == KWD_RULES_EXISTS) {
            { Proposition* existsbody = ((Proposition*)((proposition->arguments->theArray)[0]));

              if (existsbody->kind == KWD_RULES_AND) {
                { Object* g = NULL;
                  Vector* vector002 = existsbody->arguments;
                  int index002 = 0;
                  int length002 = vector002->length();

                  for  (; index002 < length002; 
                        index002 = index002 + 1) {
                    g = (vector002->theArray)[index002];
                    collectMatchingRuleGoals(((Proposition*)(g)), variables, KWD_RULES_TAIL, resultlist);
                  }
                }
              }
            }
            return (resultlist);
          }
          else {
          }
        }
      }
      else {
      }
    }
    collectMatchingRuleGoals(proposition, variables, headortail, resultlist);
    return (resultlist);
  }
}

void collectMatchingRuleGoals(Proposition* proposition, Cons* toplevelvars, Keyword* headortail, List* collection) {
  { Keyword* testValue000 = proposition->kind;

    if ((testValue000 == KWD_RULES_AND) ||
        (testValue000 == KWD_RULES_OR)) {
      if (headortail == KWD_RULES_HEAD) {
        { Object* arg = NULL;
          Vector* vector000 = proposition->arguments;
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            arg = (vector000->theArray)[index000];
            collectMatchingRuleGoals(((Proposition*)(arg)), toplevelvars, headortail, collection);
          }
        }
      }
      else if (headortail == KWD_RULES_TAIL) {
        { int goalcount = collection->length();

          { Object* arg = NULL;
            Vector* vector001 = proposition->arguments;
            int index001 = 0;
            int length001 = vector001->length();

            for  (; index001 < length001; 
                  index001 = index001 + 1) {
              arg = (vector001->theArray)[index001];
              collectMatchingRuleGoals(((Proposition*)(arg)), toplevelvars, headortail, collection);
            }
          }
          if (goalcount == collection->length()) {
            { Object* arg = NULL;
              Vector* vector002 = proposition->arguments;
              int index002 = 0;
              int length002 = vector002->length();

              for  (; index002 < length002; 
                    index002 = index002 + 1) {
                arg = (vector002->theArray)[index002];
                collectMatchingRuleGoals(((Proposition*)(arg)), toplevelvars, headortail, collection);
              }
            }
          }
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << headortail << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    else if (testValue000 == KWD_RULES_EXISTS) {
      if (headortail == KWD_RULES_HEAD) {
        collectMatchingRuleGoals(((Proposition*)((proposition->arguments->theArray)[0])), toplevelvars, headortail, collection);
      }
      else if (headortail == KWD_RULES_TAIL) {
        { PatternVariable* v = NULL;
          Vector* vector003 = ((Vector*)(dynamicSlotValue(proposition->dynamicSlots, SYM_RULES_LOGIC_IO_VARIABLES, NULL)));
          int index003 = 0;
          int length003 = vector003->length();

          for  (; index003 < length003; 
                index003 = index003 + 1) {
            v = ((PatternVariable*)((vector003->theArray)[index003]));
            toplevelvars = cons(v, toplevelvars);
          }
        }
        collectMatchingRuleGoals(((Proposition*)((proposition->arguments->theArray)[0])), toplevelvars, headortail, collection);
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "`" << headortail << "'" << " is not a valid case option";
          throw *newStellaException(stream001->theStringReader());
        }
      }
    }
    else if (testValue000 == KWD_RULES_FORALL) {
      if (headortail == KWD_RULES_HEAD) {
        { PatternVariable* v = NULL;
          Vector* vector004 = ((Vector*)(dynamicSlotValue(proposition->dynamicSlots, SYM_RULES_LOGIC_IO_VARIABLES, NULL)));
          int index004 = 0;
          int length004 = vector004->length();

          for  (; index004 < length004; 
                index004 = index004 + 1) {
            v = ((PatternVariable*)((vector004->theArray)[index004]));
            toplevelvars = cons(v, toplevelvars);
          }
        }
        collectMatchingRuleGoals(((Proposition*)((proposition->arguments->theArray)[1])), toplevelvars, headortail, collection);
      }
      else if (headortail == KWD_RULES_TAIL) {
      }
      else {
        { OutputStringStream* stream002 = newOutputStringStream();

          *(stream002->nativeStream) << "`" << headortail << "'" << " is not a valid case option";
          throw *newStellaException(stream002->theStringReader());
        }
      }
    }
    else if ((testValue000 == KWD_RULES_ISA) ||
        ((testValue000 == KWD_RULES_PREDICATE) ||
         ((testValue000 == KWD_RULES_FUNCTION) ||
          ((testValue000 == KWD_RULES_NOT) ||
           (testValue000 == KWD_RULES_IMPLIES))))) {
      { boolean testValue001 = false;

        { boolean alwaysP000 = true;

          { Object* a = NULL;
            Cons* iter000 = extractGoalArguments(proposition);

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              a = iter000->value;
              if (!(toplevelvars->memberP(a) ||
                  (!isaP(a, SGT_RULES_LOGIC_PATTERN_VARIABLE)))) {
                alwaysP000 = false;
                break;
              }
            }
          }
          testValue001 = alwaysP000;
        }
        if (testValue001) {
          testValue001 = ((boolean)(extractGoalDescription(proposition, headortail))) &&
              (!(proposition->operatoR == SGT_RULES_PL_KERNEL_KB_HOLDS));
        }
        if (testValue001) {
          collection->insert(proposition);
        }
      }
    }
    else {
    }
  }
}

boolean atomicForallArgumentP(Proposition* forallprop, Keyword* headortail) {
  return (atomicGoalPropositionP(((headortail == KWD_RULES_HEAD) ? ((Proposition*)((forallprop->arguments->theArray)[1])) : ((Proposition*)((forallprop->arguments->theArray)[0])))));
}

boolean atomicGoalPropositionP(Proposition* proposition) {
  { Keyword* testValue000 = proposition->kind;

    if ((testValue000 == KWD_RULES_ISA) ||
        ((testValue000 == KWD_RULES_PREDICATE) ||
         ((testValue000 == KWD_RULES_FUNCTION) ||
          (testValue000 == KWD_RULES_IMPLIES)))) {
      return (((boolean)(extractGoalDescription(proposition, NULL))));
    }
    else if (testValue000 == KWD_RULES_NOT) {
      return (((boolean)(extractGoalDescription(((Proposition*)((proposition->arguments->theArray)[0])), NULL))));
    }
    else if (testValue000 == KWD_RULES_AND) {
      { int count = 0;

        { Proposition* conjunct = NULL;
          Vector* vector000 = ((Vector*)(proposition->arguments));
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            conjunct = ((Proposition*)((vector000->theArray)[index000]));
            if ((!(conjunct->kind == KWD_RULES_AND)) &&
                atomicGoalPropositionP(conjunct)) {
              count = count + 1;
            }
            else {
              return (false);
            }
          }
        }
        return (count == 1);
      }
    }
    else {
      return (false);
    }
  }
}

boolean atomicGoalDescriptionP(Description* description) {
  if (namedDescriptionP(description)) {
    return (true);
  }
  { Description* complement = ((Description*)(dynamicSlotValue(description->dynamicSlots, SYM_RULES_LOGIC_COMPLEMENT_DESCRIPTION, NULL)));

    if (((boolean)(complement)) &&
        namedDescriptionP(complement)) {
      return (true);
    }
    else {
      return (atomicGoalPropositionP(description->proposition));
    }
  }
}

boolean variableArityGoalPropositionP(Proposition* proposition) {
  { Keyword* testValue000 = proposition->kind;

    if ((testValue000 == KWD_RULES_PREDICATE) ||
        (testValue000 == KWD_RULES_FUNCTION)) {
      { Description* description = extractGoalDescription(proposition, NULL);

        return (((boolean)(description)) &&
            variableArityP(description));
      }
    }
    else {
    }
  }
  return (false);
}

boolean chainableRelationP(NamedDescription* description, Keyword* headortail) {
  if (!((boolean)(headortail))) {
    return (true);
  }
  { Cons* nonpermittedpredicates = NULL;

    if (headortail == KWD_RULES_TAIL) {
      nonpermittedpredicates = getQuotedTree("((/PL-KERNEL-KB/@HOLDS /PL-KERNEL-KB/@MEMBER-OF /PL-KERNEL-KB/@INSTANCE-OF /PL-KERNEL-KB/@SUBSET-OF @NUMBER-WRAPPER.PLUS @NUMBER-WRAPPER.MINUS @NUMBER-WRAPPER.TIMES @NUMBER-WRAPPER.DIVIDE) \"/LOGIC\")", "/LOGIC");
    }
    else if (headortail == KWD_RULES_HEAD) {
      nonpermittedpredicates = getQuotedTree("((@NUMBER-WRAPPER.PLUS @NUMBER-WRAPPER.MINUS @NUMBER-WRAPPER.TIMES @NUMBER-WRAPPER.DIVIDE) \"/LOGIC\")", "/LOGIC");
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << headortail << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    return (!nonpermittedpredicates->memberP(description->surrogateValueInverse));
  }
}

Description* extractGoalDescription(Proposition* goal, Keyword* headortail) {
  { Vector* arguments = goal->arguments;

    { Keyword* testValue000 = goal->kind;

      if ((testValue000 == KWD_RULES_ISA) ||
          ((testValue000 == KWD_RULES_PREDICATE) ||
           ((testValue000 == KWD_RULES_FUNCTION) ||
            (testValue000 == KWD_RULES_IMPLIES)))) {
        if (isaP(goal->operatoR, SGT_RULES_STELLA_SURROGATE)) {
          { NamedDescription* description = getDescription(((Surrogate*)(goal->operatoR)));

            if (!((boolean)(description))) {
              { OutputStringStream* stream000 = newOutputStringStream();

                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  *(stream000->nativeStream) << "ERROR: " << "Can't finalize relations because relation " << "`" << ((Surrogate*)(goal->operatoR))->symbolName << "'" << " is undefined." << "." << std::endl;
                  helpSignalPropositionError(stream000, KWD_RULES_ERROR);
                }
                throw *newPropositionError(stream000->theStringReader());
              }
            }
            if (chainableRelationP(description, headortail)) {
              return (description);
            }
          }
        }
      }
      else if (testValue000 == KWD_RULES_NOT) {
        { Description* argumentdescription = extractGoalDescription(((Proposition*)((arguments->theArray)[0])), headortail);

          if (((boolean)(argumentdescription))) {
            return (getComplementOfGoalDescription(((NamedDescription*)(argumentdescription))));
          }
        }
      }
      else {
      }
    }
    return (NULL);
  }
}

Cons* extractGoalArguments(Proposition* goal) {
  { Vector* arguments = goal->arguments;

    { Keyword* testValue000 = goal->kind;

      if ((testValue000 == KWD_RULES_ISA) ||
          ((testValue000 == KWD_RULES_PREDICATE) ||
           ((testValue000 == KWD_RULES_FUNCTION) ||
            (testValue000 == KWD_RULES_IMPLIES)))) {
        { Cons* result = NIL;

          { Object* arg = NULL;
            Vector* vector000 = arguments;
            int index000 = 0;
            int length000 = vector000->length();
            Cons* collect000 = NULL;

            for  (; index000 < length000; 
                  index000 = index000 + 1) {
              arg = (vector000->theArray)[index000];
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(arg, NIL);
                  if (result == NIL) {
                    result = collect000;
                  }
                  else {
                    addConsToEndOfConsList(result, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(arg, NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
          return (result);
        }
      }
      else if (testValue000 == KWD_RULES_NOT) {
        return (extractGoalArguments(((Proposition*)((arguments->theArray)[0]))));
      }
      else {
        return (NIL);
      }
    }
  }
}

Proposition* substituteProposition(Proposition* proposition, Proposition* outprop, Proposition* inprop) {
  if (proposition == outprop) {
    return (inprop);
  }
  { Object* arg = NULL;
    Vector* vector000 = proposition->arguments;
    int index000 = 0;
    int length000 = vector000->length();
    int i = NULL_INTEGER;
    int iter000 = 0;

    for  (; index000 < length000; 
          index000 = index000 + 1,
          iter000 = iter000 + 1) {
      arg = (vector000->theArray)[index000];
      i = iter000;
      if (arg == outprop) {
        (proposition->arguments->theArray)[i] = inprop;
      }
      else if (isaP(arg, SGT_RULES_LOGIC_PROPOSITION)) {
        substituteProposition(((Proposition*)(arg)), outprop, inprop);
      }
    }
  }
  return (proposition);
}

Proposition* extractInvertedGoal(Proposition* proposition, Proposition* goal) {
  if (goal->kind == KWD_RULES_NOT) {
    return (extractInvertedGoal(proposition, ((Proposition*)((goal->arguments->theArray)[0]))));
  }
  { Keyword* testValue000 = proposition->kind;

    if (testValue000 == KWD_RULES_NOT) {
      if (equivalentPropositionsP(((Proposition*)((proposition->arguments->theArray)[0])), goal, NULL)) {
        return (proposition);
      }
      else {
        return (extractInvertedGoal(((Proposition*)((proposition->arguments->theArray)[0])), goal));
      }
    }
    else if ((testValue000 == KWD_RULES_AND) ||
        (testValue000 == KWD_RULES_OR)) {
      { Proposition* result = NULL;

        { Object* arg = NULL;
          Vector* vector000 = proposition->arguments;
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            arg = (vector000->theArray)[index000];
            result = extractInvertedGoal(((Proposition*)(arg)), goal);
            if (((boolean)(result))) {
              return (result);
            }
          }
        }
      }
    }
    else {
      if (equivalentPropositionsP(proposition, goal, NULL)) {
        return (proposition);
      }
    }
  }
  return (NULL);
}

Proposition* invertForallAroundGoal(Proposition* forallprop, Proposition* goal, Keyword* headortail, boolean contrapositiveP) {
  { KeyValueMap* mapping = newKeyValueMap();
    Proposition* invertedforall = copyProposition(forallprop, mapping);
    Object* oldhead = (invertedforall->arguments->theArray)[1];
    Object* oldtail = (invertedforall->arguments->theArray)[0];
    Proposition* newgoal = ((Proposition*)(mapping->lookup(goal)));
    Cons* newgoalarguments = extractGoalArguments(newgoal);
    Proposition* headprime = NULL;
    Proposition* tailprime = NULL;
    Proposition* newhead = NULL;
    Proposition* newtail = NULL;

    if (contrapositiveP) {
      oldhead = invertProposition(((Proposition*)(oldhead)));
      oldtail = invertProposition(((Proposition*)(oldtail)));
      newgoal = extractInvertedGoal(((headortail == KWD_RULES_HEAD) ? ((Proposition*)(oldhead)) : ((Proposition*)(oldtail))), newgoal);
      if (!((boolean)(newgoal))) {
        std::cout << "Unable to generate contrapositive rule for goal " << "`" << goal << "'" << std::endl << "in " << "`" << forallprop << "'" << std::endl;
        return (NULL);
      }
      (invertedforall->arguments->theArray)[0] = oldhead;
      (invertedforall->arguments->theArray)[1] = oldtail;
      oldhead = oldtail;
      oldtail = (invertedforall->arguments->theArray)[0];
      headortail = ((headortail == KWD_RULES_HEAD) ? KWD_RULES_TAIL : KWD_RULES_HEAD);
    }
    { boolean testValue000 = false;

      testValue000 = newgoal == (((headortail == KWD_RULES_HEAD) ? oldhead : oldtail));
      if (testValue000) {
        { boolean alwaysP000 = true;

          { Object* arg = NULL;
            Cons* iter000 = newgoalarguments;
            PatternVariable* v = NULL;
            Vector* vector000 = ((Vector*)(dynamicSlotValue(invertedforall->dynamicSlots, SYM_RULES_LOGIC_IO_VARIABLES, NULL)));
            int index000 = 0;
            int length000 = vector000->length();

            for  (; (!(iter000 == NIL)) &&
                      (index000 < length000); 
                  iter000 = iter000->rest,
                  index000 = index000 + 1) {
              arg = iter000->value;
              v = ((PatternVariable*)((vector000->theArray)[index000]));
              if (!(arg == v)) {
                alwaysP000 = false;
                break;
              }
            }
          }
          testValue000 = alwaysP000;
        }
        if (testValue000) {
          testValue000 = newgoalarguments->length() == ((Vector*)(dynamicSlotValue(invertedforall->dynamicSlots, SYM_RULES_LOGIC_IO_VARIABLES, NULL)))->length();
        }
      }
      if (testValue000) {
        return (invertedforall);
      }
    }
    if (headortail == KWD_RULES_HEAD) {
      headprime = substituteProposition(((Proposition*)(oldhead)), newgoal, FALSE_PROPOSITION);
      normalizeProposition(headprime);
      if (headprime->operatoR == SGT_RULES_STELLA_FALSE) {
        newtail = ((Proposition*)(oldtail));
      }
      else {
        {
          oldtail = invertProposition(((Proposition*)(oldtail)));
          newtail = disjoinPropositions(consList(2, oldtail, headprime));
          newtail = invertProposition(newtail);
          normalizeProposition(newtail);
        }
      }
      (invertedforall->arguments->theArray)[0] = newtail;
      (invertedforall->arguments->theArray)[1] = newgoal;
    }
    else if (headortail == KWD_RULES_TAIL) {
      tailprime = substituteProposition(((Proposition*)(oldtail)), newgoal, TRUE_PROPOSITION);
      normalizeProposition(tailprime);
      if (tailprime->operatoR == SGT_RULES_STELLA_TRUE) {
        newhead = ((Proposition*)(oldhead));
      }
      else {
        { Cons* residuevariables = NIL;

          tailprime = invertProposition(tailprime);
          newhead = disjoinPropositions(consList(2, tailprime, oldhead));
          { PatternVariable* vbl = NULL;
            Vector* vector001 = ((Vector*)(dynamicSlotValue(invertedforall->dynamicSlots, SYM_RULES_LOGIC_IO_VARIABLES, NULL)));
            int index001 = 0;
            int length001 = vector001->length();
            Cons* collect000 = NULL;

            for  (; index001 < length001; 
                  index001 = index001 + 1) {
              vbl = ((PatternVariable*)((vector001->theArray)[index001]));
              if (!newgoalarguments->memberP(vbl)) {
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(vbl, NIL);
                    if (residuevariables == NIL) {
                      residuevariables = collect000;
                    }
                    else {
                      addConsToEndOfConsList(residuevariables, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000->rest = cons(vbl, NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
          }
          if (!(residuevariables == NIL)) {
            { Proposition* nestedforall = createProposition(SYM_RULES_STELLA_FORALL, 2);

              setDynamicSlotValue(nestedforall->dynamicSlots, SYM_RULES_LOGIC_IO_VARIABLES, copyConsListToVariablesVector(residuevariables), NULL);
              (nestedforall->arguments->theArray)[0] = TRUE_PROPOSITION;
              (nestedforall->arguments->theArray)[1] = newhead;
              newhead = nestedforall;
            }
          }
          normalizeProposition(newhead);
        }
      }
      (invertedforall->arguments->theArray)[0] = newgoal;
      (invertedforall->arguments->theArray)[1] = newhead;
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << headortail << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    { Cons* newvariables = extractGoalArguments(newgoal);

      { Object* v = NULL;
        Cons* iter001 = newvariables;
        int i = NULL_INTEGER;
        int iter002 = 0;

        for  (; !(iter001 == NIL); 
              iter001 = iter001->rest,
              iter002 = iter002 + 1) {
          v = iter001->value;
          i = iter002;
          if (!isaP(v, SGT_RULES_LOGIC_PATTERN_VARIABLE)) {
            { PatternVariable* constantvbl = createVariable(NULL, NULL, false);

              updateSkolemType(constantvbl, logicalType(v));
              newvariables->nthSetter(constantvbl, i);
              if (headortail == KWD_RULES_HEAD) {
                (invertedforall->arguments->theArray)[0] = (conjoinTwoPropositions(createEquivalenceProposition(constantvbl, v), ((Proposition*)((invertedforall->arguments->theArray)[0]))));
              }
              else if (headortail == KWD_RULES_TAIL) {
                { Proposition* negatedequivalence = createEquivalenceProposition(constantvbl, v);

                  invertProposition(negatedequivalence);
                  (invertedforall->arguments->theArray)[1] = (disjoinPropositions(consList(2, negatedequivalence, (invertedforall->arguments->theArray)[1])));
                }
              }
              else {
                { OutputStringStream* stream001 = newOutputStringStream();

                  *(stream001->nativeStream) << "`" << headortail << "'" << " is not a valid case option";
                  throw *newStellaException(stream001->theStringReader());
                }
              }
              normalizeProposition(((Proposition*)((invertedforall->arguments->theArray)[0])));
            }
          }
        }
      }
      setDynamicSlotValue(invertedforall->dynamicSlots, SYM_RULES_LOGIC_IO_VARIABLES, copyConsListToVariablesVector(newvariables), NULL);
    }
    recursivelyFastenDownPropositions(invertedforall, false);
    return (invertedforall);
  }
}

Description* constructDescriptionFromForallProposition(Proposition* forallprop, Keyword* headortail) {
  { Description* description = newDescription();

    description->proposition = ((Proposition*)((forallprop->arguments->theArray)[(((headortail == KWD_RULES_HEAD) ? 1 : 0))]));
    description->ioVariables = ((Vector*)(dynamicSlotValue(forallprop->dynamicSlots, SYM_RULES_LOGIC_IO_VARIABLES, NULL)))->copy();
    { 
      BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_RULES_DESCRIPTION);
      return (finishBuildingDescription(description, true, headortail));
    }
  }
}

void markAsForwardRule(Proposition* impliesprop) {
  { Description* head = ((Description*)((impliesprop->arguments->theArray)[1]));

    if ((!namedDescriptionP(head)) &&
        (!((boolean)(((Description*)(dynamicSlotValue(head->dynamicSlots, SYM_RULES_LOGIC_COMPLEMENT_DESCRIPTION, NULL))))))) {
      setDynamicSlotValue(impliesprop->dynamicSlots, SYM_RULES_LOGIC_FORWARD_ONLYp, TRUE_WRAPPER, FALSE_WRAPPER);
    }
  }
}

void deriveOneSatelliteRule(Proposition* masterforall, Proposition* goal, Keyword* headortail, boolean contrapositiveP) {
  { Proposition* invertedforall = NULL;
    Description* head = NULL;
    Description* tail = NULL;
    boolean overrideforwardonlyP = false;

    if ((headortail == KWD_RULES_TAIL) &&
        (((!atomicGoalPropositionP(((Proposition*)((masterforall->arguments->theArray)[0])))) ||
        variableArityGoalPropositionP(((Proposition*)((masterforall->arguments->theArray)[0])))) &&
         (!contrapositiveP))) {
      deriveComplexForwardRule(goal, masterforall);
      return;
    }
    { 
      BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_RULES_DESCRIPTION);
      invertedforall = invertForallAroundGoal(masterforall, goal, headortail, contrapositiveP);
    }
    if (!((boolean)(invertedforall))) {
      return;
    }
    if (contrapositiveP) {
      if (headortail == KWD_RULES_HEAD) {
        headortail = KWD_RULES_TAIL;
      }
      else if (headortail == KWD_RULES_TAIL) {
        headortail = KWD_RULES_HEAD;
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << headortail << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    if (headortail == KWD_RULES_HEAD) {
      head = extractGoalDescription(((Proposition*)((invertedforall->arguments->theArray)[1])), NULL);
      tail = constructDescriptionFromForallProposition(invertedforall, KWD_RULES_TAIL);
    }
    else if (headortail == KWD_RULES_TAIL) {
      tail = extractGoalDescription(((Proposition*)((invertedforall->arguments->theArray)[0])), NULL);
      head = constructDescriptionFromForallProposition(invertedforall, KWD_RULES_HEAD);
    }
    else {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "`" << headortail << "'" << " is not a valid case option";
        throw *newStellaException(stream001->theStringReader());
      }
    }
    if (((BooleanWrapper*)(dynamicSlotValue(masterforall->dynamicSlots, SYM_RULES_LOGIC_FORWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue &&
        (headortail == KWD_RULES_HEAD)) {
      overrideforwardonlyP = namedDescriptionP(head) &&
          (namedDescriptionP(tail) &&
           (head->arity() == tail->arity()));
      if (!overrideforwardonlyP) {
        return;
      }
    }
    { Proposition* impliesprop = createImpliesProposition(tail, head);

      { 
        BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_RULES_EXTENSIONAL_ASSERTION);
        { Proposition* duplicate = recursivelyFastenDownPropositions(impliesprop, false);

          if (!(duplicate == impliesprop)) {
            impliesprop = duplicate;
          }
          else if (headortail == KWD_RULES_TAIL) {
            markAsForwardRule(impliesprop);
          }
        }
      }
      if (masterforall->satellitePropositions_reader()->emptyP()) {
        setDynamicSlotValue(masterforall->dynamicSlots, SYM_RULES_LOGIC_SATELLITE_PROPOSITIONS, newList(), NULL);
      }
      masterforall->satellitePropositions_reader()->insertNew(impliesprop);
      setDynamicSlotValue(impliesprop->dynamicSlots, SYM_RULES_LOGIC_MASTER_PROPOSITION, masterforall, NULL);
      if (((BooleanWrapper*)(dynamicSlotValue(masterforall->dynamicSlots, SYM_RULES_LOGIC_FORWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue &&
          (!overrideforwardonlyP)) {
        if (contrapositiveP) {
          setDynamicSlotValue(impliesprop->dynamicSlots, SYM_RULES_LOGIC_BACKWARD_ONLYp, TRUE_WRAPPER, FALSE_WRAPPER);
        }
        else {
          setDynamicSlotValue(impliesprop->dynamicSlots, SYM_RULES_LOGIC_FORWARD_ONLYp, TRUE_WRAPPER, FALSE_WRAPPER);
        }
      }
      if (((BooleanWrapper*)(dynamicSlotValue(masterforall->dynamicSlots, SYM_RULES_LOGIC_BACKWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue) {
        if (contrapositiveP) {
          setDynamicSlotValue(impliesprop->dynamicSlots, SYM_RULES_LOGIC_FORWARD_ONLYp, TRUE_WRAPPER, FALSE_WRAPPER);
        }
        else {
          setDynamicSlotValue(impliesprop->dynamicSlots, SYM_RULES_LOGIC_BACKWARD_ONLYp, TRUE_WRAPPER, FALSE_WRAPPER);
        }
      }
      if (((BooleanWrapper*)(dynamicSlotValue(masterforall->dynamicSlots, SYM_RULES_LOGIC_DONT_OPTIMIZEp, FALSE_WRAPPER)))->wrapperValue) {
        setDynamicSlotValue(impliesprop->dynamicSlots, SYM_RULES_LOGIC_DONT_OPTIMIZEp, TRUE_WRAPPER, FALSE_WRAPPER);
        tail = ((Description*)((impliesprop->arguments->theArray)[0]));
        if (!((boolean)(tail->nativeRelation()))) {
          setDynamicSlotValue(tail->dynamicSlots, SYM_RULES_LOGIC_DONT_OPTIMIZEp, TRUE_WRAPPER, FALSE_WRAPPER);
        }
        head = ((Description*)((impliesprop->arguments->theArray)[1]));
        if (!((boolean)(head->nativeRelation()))) {
          setDynamicSlotValue(head->dynamicSlots, SYM_RULES_LOGIC_DONT_OPTIMIZEp, TRUE_WRAPPER, FALSE_WRAPPER);
        }
      }
    }
  }
}

// If true, inversion of forall propositions happens lazily.
// I.e., satellite rules are generated on-demand during inference only if they
// are actually needed.
boolean oLAZY_SATELLITE_RULESpo = false;

boolean deriveSatelliteRulesForGoalP(Proposition* forallprop, Description* goaldescription, Keyword* direction, boolean lazysatellitesP) {
  finalizeObjects();
  { boolean createdsatellitesP = false;
    Description* goaldesc = NULL;
    boolean positiveonlyP = direction == KWD_RULES_POSITIVE;
    boolean contrapositiveonlyP = direction == KWD_RULES_CONTRAPOSITIVE;

    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, forallprop->homeContext);
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
      { Proposition* goal = NULL;
        Cons* iter000 = findMatchableGoals(forallprop, KWD_RULES_HEAD)->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          goal = ((Proposition*)(iter000->value));
          if ((!((boolean)(goaldescription))) ||
              (goaldescription == extractGoalDescription(goal, KWD_RULES_HEAD))) {
            createdsatellitesP = true;
            if (lazysatellitesP) {
              if (!((boolean)(goaldescription))) {
                goaldesc = extractGoalDescription(goal, KWD_RULES_HEAD);
              }
              else {
                goaldesc = goaldescription;
              }
              if (!((boolean)(((SequenceIndex*)(dynamicSlotValue(goaldesc->dynamicSlots, SYM_RULES_LOGIC_RULES_WITH_DEFERRED_SATELLITES, NULL)))))) {
                setDynamicSlotValue(goaldesc->dynamicSlots, SYM_RULES_LOGIC_RULES_WITH_DEFERRED_SATELLITES, createSequenceIndex(KWD_RULES_NON_PAGING, NIL), NULL);
              }
              ((SequenceIndex*)(dynamicSlotValue(goaldesc->dynamicSlots, SYM_RULES_LOGIC_RULES_WITH_DEFERRED_SATELLITES, NULL)))->insert(forallprop);
            }
            else if (!contrapositiveonlyP) {
              deriveOneSatelliteRule(forallprop, goal, KWD_RULES_HEAD, false);
            }
            if ((!positiveonlyP) &&
                ((!((BooleanWrapper*)(dynamicSlotValue(forallprop->dynamicSlots, SYM_RULES_LOGIC_BACKWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue) &&
                 (!atomicForallArgumentP(forallprop, KWD_RULES_TAIL)))) {
              if (lazysatellitesP) {
                setDynamicSlotValue(goaldesc->dynamicSlots, SYM_RULES_LOGIC_DEFERRED_CONTRAPOSITIVESp, TRUE_WRAPPER, NULL);
              }
              else {
                deriveOneSatelliteRule(forallprop, goal, KWD_RULES_HEAD, true);
              }
            }
          }
        }
      }
      if (((BooleanWrapper*)(dynamicSlotValue(forallprop->dynamicSlots, SYM_RULES_LOGIC_BACKWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue &&
          ((!((boolean)(goaldescription))) &&
           findMatchableGoals(forallprop, KWD_RULES_HEAD)->emptyP())) {
        createdsatellitesP = true;
        skolemizeRule(forallprop);
      }
      if ((!((BooleanWrapper*)(dynamicSlotValue(forallprop->dynamicSlots, SYM_RULES_LOGIC_BACKWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue) &&
          (atomicForallArgumentP(forallprop, KWD_RULES_TAIL) ||
           ((!atomicForallArgumentP(forallprop, KWD_RULES_HEAD)) ||
            ((BooleanWrapper*)(dynamicSlotValue(forallprop->dynamicSlots, SYM_RULES_LOGIC_FORWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue))) {
        { Proposition* goal = NULL;
          Cons* iter001 = findMatchableGoals(forallprop, KWD_RULES_TAIL)->theConsList;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            goal = ((Proposition*)(iter001->value));
            if ((!((boolean)(goaldescription))) ||
                (goaldescription == extractGoalDescription(goal, KWD_RULES_TAIL))) {
              createdsatellitesP = true;
              if (lazysatellitesP) {
                if (!((boolean)(goaldescription))) {
                  goaldesc = extractGoalDescription(goal, KWD_RULES_TAIL);
                }
                else {
                  goaldesc = goaldescription;
                }
                if (!((boolean)(((SequenceIndex*)(dynamicSlotValue(goaldesc->dynamicSlots, SYM_RULES_LOGIC_RULES_WITH_DEFERRED_SATELLITES, NULL)))))) {
                  setDynamicSlotValue(goaldesc->dynamicSlots, SYM_RULES_LOGIC_RULES_WITH_DEFERRED_SATELLITES, createSequenceIndex(KWD_RULES_NON_PAGING, NIL), NULL);
                }
                ((SequenceIndex*)(dynamicSlotValue(goaldesc->dynamicSlots, SYM_RULES_LOGIC_RULES_WITH_DEFERRED_SATELLITES, NULL)))->insert(forallprop);
              }
              else if (!contrapositiveonlyP) {
                deriveOneSatelliteRule(forallprop, goal, KWD_RULES_TAIL, false);
              }
              if ((!positiveonlyP) &&
                  ((!((BooleanWrapper*)(dynamicSlotValue(forallprop->dynamicSlots, SYM_RULES_LOGIC_FORWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue) &&
                   (!atomicForallArgumentP(forallprop, KWD_RULES_HEAD)))) {
                if (lazysatellitesP) {
                  setDynamicSlotValue(goaldesc->dynamicSlots, SYM_RULES_LOGIC_DEFERRED_CONTRAPOSITIVESp, TRUE_WRAPPER, NULL);
                }
                else {
                  deriveOneSatelliteRule(forallprop, goal, KWD_RULES_TAIL, true);
                }
              }
            }
          }
        }
      }
    }
    if (createdsatellitesP &&
        ((boolean)(((TruthValue*)(accessInContext(forallprop->truthValue, forallprop->homeContext, false)))))) {
      { 
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oCONTEXTo);
        BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
        { 
          BIND_STELLA_SPECIAL(oINVISIBLEASSERTIONpo, boolean, true);
          { Proposition* satellite = NULL;
            Cons* iter002 = forallprop->satellitePropositions_reader()->theConsList;

            for (; !(iter002 == NIL); iter002 = iter002->rest) {
              satellite = ((Proposition*)(iter002->value));
              assignTruthValue(satellite, ((TruthValue*)(accessInContext(forallprop->truthValue, forallprop->homeContext, false))));
            }
          }
        }
      }
    }
    return (createdsatellitesP);
  }
}

void deriveSatelliteRules(Proposition* forallprop) {
  if (!deriveSatelliteRulesForGoalP(forallprop, NULL, (naturalDeductionModeP() ? KWD_RULES_POSITIVE : KWD_RULES_POSITIVE_AND_CONTRAPOSITIVE), oLAZY_SATELLITE_RULESpo)) {
    if (oCYC_KLUDGES_ENABLEDpo) {
      if (isaP((forallprop->arguments->theArray)[1], SGT_RULES_LOGIC_PROPOSITION) &&
          (((Proposition*)((forallprop->arguments->theArray)[1]))->kind == KWD_RULES_EXISTS)) {
        return;
      }
    }
    *(STANDARD_WARNING->nativeStream) << "Warning: " << "PowerLoom can't index the rule:" << std::endl << "   " << "`" << forallprop << "'" << std::endl << std::endl;
  }
}

DEFINE_STELLA_SPECIAL(oDERIVE_DEFERRED_SATELLITE_RULES_INVOCATIONSo, List* , NULL);

void deriveDeferredSatelliteRules(Description* self) {
  if (oLAZY_SATELLITE_RULESpo) {
    { 
      BIND_STELLA_SPECIAL(oDERIVE_DEFERRED_SATELLITE_RULES_INVOCATIONSo, List*, ((List*)(((!((boolean)(oDERIVE_DEFERRED_SATELLITE_RULES_INVOCATIONSo))) ? newList() : oDERIVE_DEFERRED_SATELLITE_RULES_INVOCATIONSo))));
      if (oDERIVE_DEFERRED_SATELLITE_RULES_INVOCATIONSo->membP(self)) {
        return;
      }
      oDERIVE_DEFERRED_SATELLITE_RULES_INVOCATIONSo->insert(self);
      if ((!((boolean)(((SequenceIndex*)(dynamicSlotValue(self->dynamicSlots, SYM_RULES_LOGIC_RULES_WITH_DEFERRED_SATELLITES, NULL)))))) &&
          (!((boolean)(((Description*)(dynamicSlotValue(self->dynamicSlots, SYM_RULES_LOGIC_COMPLEMENT_DESCRIPTION, NULL))))))) {
        return;
      }
      { SequenceIndex* queuedrules = ((SequenceIndex*)(dynamicSlotValue(self->dynamicSlots, SYM_RULES_LOGIC_RULES_WITH_DEFERRED_SATELLITES, NULL)));
        Description* complement = ((Description*)(dynamicSlotValue(self->dynamicSlots, SYM_RULES_LOGIC_COMPLEMENT_DESCRIPTION, NULL)));

        if (((boolean)(queuedrules))) {
          { Proposition* forallprop = NULL;
            Iterator* iter000 = queuedrules->allocateIterator();

            for (; iter000->nextP(); ) {
              forallprop = ((Proposition*)(iter000->value));
              deriveSatelliteRulesForGoalP(forallprop, self, ((!((boolean)(complement))) ? KWD_RULES_POSITIVE : KWD_RULES_POSITIVE_AND_CONTRAPOSITIVE), false);
            }
          }
          if (((boolean)(complement))) {
            setDynamicSlotValue(self->dynamicSlots, SYM_RULES_LOGIC_DEFERRED_CONTRAPOSITIVESp, NULL, NULL);
          }
          setDynamicSlotValue(self->dynamicSlots, SYM_RULES_LOGIC_RULES_WITH_DEFERRED_SATELLITES, NULL, NULL);
        }
        if (((boolean)(complement)) &&
            ((boolean)(((SequenceIndex*)(dynamicSlotValue(complement->dynamicSlots, SYM_RULES_LOGIC_RULES_WITH_DEFERRED_SATELLITES, NULL)))))) {
          deriveDeferredSatelliteRules(complement);
        }
      }
    }
  }
}

void deriveDeferredContrapositiveSatelliteRules(Description* self) {
  if (oLAZY_SATELLITE_RULESpo) {
    if (coerceWrappedBooleanToBoolean(self->deferredContrapositivesP_reader())) {
      { Proposition* masterproposition = NULL;
        List* queuedrules = newList();

        { Proposition* prop = NULL;
          Iterator* iter000 = unfilteredDependentImpliesPropositions(self)->allocateIterator();

          for (; iter000->nextP(); ) {
            prop = ((Proposition*)(iter000->value));
            if (prop->kind == KWD_RULES_IMPLIES) {
              masterproposition = ((Proposition*)(dynamicSlotValue(prop->dynamicSlots, SYM_RULES_LOGIC_MASTER_PROPOSITION, NULL)));
              if (((boolean)(masterproposition)) &&
                  (!masterproposition->deletedP())) {
                queuedrules->insertNew(masterproposition);
              }
            }
          }
        }
        { Proposition* forallprop = NULL;
          Cons* iter001 = queuedrules->theConsList;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            forallprop = ((Proposition*)(iter001->value));
            deriveSatelliteRulesForGoalP(forallprop, self, KWD_RULES_CONTRAPOSITIVE, false);
          }
        }
      }
    }
  }
}

Description* getInferableComplementDescription(Description* self) {
  { Description* complement = ((Description*)(dynamicSlotValue(self->dynamicSlots, SYM_RULES_LOGIC_COMPLEMENT_DESCRIPTION, NULL)));

    if (oLAZY_SATELLITE_RULESpo) {
      if ((!((boolean)(complement))) &&
          coerceWrappedBooleanToBoolean(self->deferredContrapositivesP_reader())) {
        complement = getComplementOfGoalDescription(((NamedDescription*)(self)));
      }
      if (coerceWrappedBooleanToBoolean(self->deferredContrapositivesP_reader())) {
        deriveDeferredSatelliteRules(self);
        setDynamicSlotValue(self->dynamicSlots, SYM_RULES_LOGIC_DEFERRED_CONTRAPOSITIVESp, NULL, NULL);
      }
    }
    return (complement);
  }
}

Proposition* deriveImpliesFromForall(Proposition* forallprop) {
  { List* heads = findMatchableGoals(forallprop, KWD_RULES_HEAD);
    List* tails = findMatchableGoals(forallprop, KWD_RULES_TAIL);
    Proposition* headgoal = ((Proposition*)(heads->first()));
    Proposition* tailgoal = ((Proposition*)(tails->first()));
    Proposition* headproposition = ((Proposition*)((forallprop->arguments->theArray)[1]));
    Proposition* tailproposition = ((Proposition*)((forallprop->arguments->theArray)[0]));

    { boolean testValue000 = false;

      testValue000 = heads->length() == 1;
      if (testValue000) {
        testValue000 = tails->length() == 1;
        if (testValue000) {
          { boolean alwaysP000 = true;

            { Object* hv = NULL;
              Vector* vector000 = headgoal->arguments;
              int index000 = 0;
              int length000 = vector000->length();
              Object* tv = NULL;
              Vector* vector001 = tailgoal->arguments;
              int index001 = 0;
              int length001 = vector001->length();

              for  (; (index000 < length000) &&
                        (index001 < length001); 
                    index000 = index000 + 1,
                    index001 = index001 + 1) {
                hv = (vector000->theArray)[index000];
                tv = (vector001->theArray)[index001];
                if (!(eqlP(hv, tv) &&
                    isaP(hv, SGT_RULES_LOGIC_PATTERN_VARIABLE))) {
                  alwaysP000 = false;
                  break;
                }
              }
            }
            testValue000 = alwaysP000;
          }
          if (testValue000) {
            testValue000 = headgoal->arguments->length() == tailgoal->arguments->length();
            if (testValue000) {
              testValue000 = ((Proposition*)(heads->first())) == headproposition;
              if (testValue000) {
                if (((Proposition*)(tails->first())) == tailproposition) {
                  testValue000 = true;
                }
                else {
                  {
                    testValue000 = tailproposition->kind == KWD_RULES_AND;
                    if (testValue000) {
                      { boolean alwaysP001 = true;

                        { Object* arg = NULL;
                          Vector* vector002 = tailproposition->arguments;
                          int index002 = 0;
                          int length002 = vector002->length();

                          for  (; index002 < length002; 
                                index002 = index002 + 1) {
                            arg = (vector002->theArray)[index002];
                            if (!(arg == tailgoal)) {
                              alwaysP001 = false;
                              break;
                            }
                          }
                        }
                        testValue000 = alwaysP001;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      if (testValue000) {
        return (createImpliesProposition(extractGoalDescription(tailgoal, NULL), extractGoalDescription(headgoal, NULL)));
      }
      else {
        return (NULL);
      }
    }
  }
}

Cons* deconstructForallTree(Cons* foralltree, Object*& _Return1, Cons*& _Return2) {
  { Cons* antecedent = ((Cons*)(foralltree->rest->rest->value));
    Object* ifclause = antecedent->rest->value;

    if (ifclause == SYM_RULES_STELLA_TRUE) {
      ifclause = getQuotedTree("((AND) \"/LOGIC\")", "/LOGIC");
    }
    _Return1 = ifclause;
    _Return2 = ((Cons*)(antecedent->rest->rest->value));
    return (((Cons*)(foralltree->rest->value)));
  }
}

ForwardChainingIndex* createForwardChainingIndex(Proposition* goal, Proposition* masterforall) {
  { ForwardChainingIndex* index = newForwardChainingIndex();
    KeyValueMap* mapping = newKeyValueMap();
    Proposition* forallcopy = copyProposition(masterforall, mapping);
    Object* goalcopy = mapping->lookup(goal);

    forallcopy = substituteProposition(forallcopy, ((Proposition*)(goalcopy)), TRUE_PROPOSITION);
    { Vector* iovariables = ((Vector*)(dynamicSlotValue(forallcopy->dynamicSlots, SYM_RULES_LOGIC_IO_VARIABLES, NULL)));
      Cons* iovariablenames = NULL;
      List* goalvariablelist = list(0);
      Cons* goalvariablenames = NIL;
      Cons* existvariablenames = NIL;
      Cons* querybody = NULL;
      Cons* consequenttree = NULL;

      { Cons* value000 = NULL;
        Object* value001 = NULL;
        Cons* value002 = NULL;

        value000 = deconstructForallTree(((Cons*)(generateProposition(forallcopy))), value001, value002);
        {
          iovariablenames = value000;
          querybody = ((Cons*)(value001));
          consequenttree = value002;
        }
      }
      collectFreeVariables(goal, goalvariablelist, list(0), list(0));
      { Cons* value003 = NIL;

        { Object* arg = NULL;
          Cons* iter000 = goalvariablelist->theConsList;
          Cons* collect000 = NULL;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest) {
            arg = iter000->value;
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(((PatternVariable*)(arg))->skolemName, NIL);
                if (value003 == NIL) {
                  value003 = collect000;
                }
                else {
                  addConsToEndOfConsList(value003, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(((PatternVariable*)(arg))->skolemName, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        goalvariablenames = value003;
      }
      { Object* v = NULL;
        Cons* iter001 = iovariablenames;
        int i = NULL_INTEGER;
        int iter002 = 0;
        Cons* collect001 = NULL;

        for  (; !(iter001 == NIL); 
              iter001 = iter001->rest,
              iter002 = iter002 + 1) {
          v = iter001->value;
          i = iter002;
          if (!searchConsTreeP(consequenttree, v)) {
            (iovariables->theArray)[i] = NULL;
            if (!((boolean)(collect001))) {
              {
                collect001 = cons(v, NIL);
                if (existvariablenames == NIL) {
                  existvariablenames = collect001;
                }
                else {
                  addConsToEndOfConsList(existvariablenames, collect001);
                }
              }
            }
            else {
              {
                collect001->rest = cons(v, NIL);
                collect001 = collect001->rest;
              }
            }
          }
        }
      }
      iovariablenames = iovariablenames->subtract(existvariablenames);
      iovariables = removeNullsInVariablesVector(iovariables);
      setDynamicSlotValue(forallcopy->dynamicSlots, SYM_RULES_LOGIC_IO_VARIABLES, iovariables, NULL);
      index->consequent = constructDescriptionFromForallProposition(forallcopy, KWD_RULES_HEAD);
      existvariablenames = existvariablenames->subtract(goalvariablenames);
      if (!(existvariablenames == NIL)) {
        querybody = listO(3, SYM_RULES_STELLA_EXISTS, existvariablenames, cons(querybody, NIL));
      }
      iovariablenames = goalvariablenames->concatenate(iovariablenames, 0);
      index->ioVariables = iovariablenames;
      index->queryBody = querybody;
      { Cons* value004 = NIL;

        { Object* v = NULL;
          Cons* iter003 = iovariablenames;
          Cons* collect002 = NULL;

          for  (; !(iter003 == NIL); 
                iter003 = iter003->rest) {
            v = iter003->value;
            if (((boolean)(v))) {
              if (!((boolean)(collect002))) {
                {
                  collect002 = cons(NULL, NIL);
                  if (value004 == NIL) {
                    value004 = collect002;
                  }
                  else {
                    addConsToEndOfConsList(value004, collect002);
                  }
                }
              }
              else {
                {
                  collect002->rest = cons(NULL, NIL);
                  collect002 = collect002->rest;
                }
              }
            }
          }
        }
        index->inputBindings = value004;
      }
    }
    index->forwardGoal = goal;
    index->masterRule = masterforall;
    index->cacheId = gensym("FWD-QUERY");
    return (index);
  }
}

void deriveComplexForwardRule(Proposition* goal, Proposition* masterforall) {
  { Description* goaldescription = ((goal->kind == KWD_RULES_NOT) ? getComplementOfGoalDescription(surrogateToDescription(((Surrogate*)(((Proposition*)((goal->arguments->theArray)[0]))->operatoR)))) : surrogateToDescription(((Surrogate*)(goal->operatoR))));
    ForwardChainingIndex* duplicate = NULL;

    { ForwardChainingIndex* idx = NULL;
      Cons* iter000 = goaldescription->forwardChainingIndices_reader()->removeDeletedMembers()->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        idx = ((ForwardChainingIndex*)(iter000->value));
        if (goal == idx->forwardGoal) {
          duplicate = idx;
        }
      }
    }
    if (((boolean)(duplicate))) {
      goaldescription->forwardChainingIndices_reader()->remove(duplicate);
    }
    if (goaldescription->forwardChainingIndices_reader() == NIL_LIST) {
      setDynamicSlotValue(goaldescription->dynamicSlots, SYM_RULES_LOGIC_FORWARD_CHAINING_INDICES, list(0), NULL);
    }
    goaldescription->forwardChainingIndices_reader()->insert(createForwardChainingIndex(goal, masterforall));
  }
}

void skolemizeRule(Proposition* rule) {
  if (!((rule->kind == KWD_RULES_FORALL) &&
      (((BooleanWrapper*)(dynamicSlotValue(rule->dynamicSlots, SYM_RULES_LOGIC_BACKWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue &&
       (((Proposition*)((rule->arguments->theArray)[1]))->kind == KWD_RULES_EXISTS)))) {
    return;
  }
  { Symbol* arrow = NULL;
    Cons* antecedent = NIL;
    Cons* consequents = NIL;
    Cons* antvars = NIL;
    Cons* cqvars = NIL;
    Cons* ruletree = NIL;
    Module* module = rule->homeModule();
    Symbol* skolemfnid = internSymbolInModule(yieldUniqueGensymName("skfn", module), module, true);
    Proposition* satellite = NULL;

    ruletree = ((Cons*)(generateTerm(rule)));
    arrow = ((Symbol*)(consTreeNth(ruletree, 2, 2, 0)));
    antvars = ((Cons*)(ruletree->rest->value));
    if ((arrow->symbolName)[0] == '<') {
      antecedent = ((Cons*)(consTreeNth(ruletree, 2, 2, 2)));
      cqvars = ((Cons*)(consTreeNth(ruletree, 3, 2, 1, 1)));
      consequents = ((Cons*)(consTreeNth(ruletree, 3, 2, 1, 2)));
    }
    else {
      antecedent = ((Cons*)(consTreeNth(ruletree, 2, 2, 1)));
      cqvars = ((Cons*)(consTreeNth(ruletree, 3, 2, 2, 1)));
      consequents = ((Cons*)(consTreeNth(ruletree, 3, 2, 2, 2)));
    }
    if (consequents->value == SYM_RULES_STELLA_AND) {
      consequents = consequents->rest;
    }
    else {
      consequents = cons(consequents, NIL);
    }
    { Object* goal = NULL;
      Cons* iter000 = consequents;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        goal = iter000->value;
        satellite = ((Proposition*)(updateProposition(skolemizeRuleForGoal(((Cons*)(goal)), antecedent, antvars, cqvars, skolemfnid), KWD_RULES_CONCEIVE)->value));
        if (rule->satellitePropositions_reader()->emptyP()) {
          setDynamicSlotValue(rule->dynamicSlots, SYM_RULES_LOGIC_SATELLITE_PROPOSITIONS, newList(), NULL);
        }
        rule->satellitePropositions_reader()->insertNew(satellite);
        setDynamicSlotValue(satellite->dynamicSlots, SYM_RULES_LOGIC_MASTER_PROPOSITION, rule, NULL);
      }
    }
  }
}

Cons* skolemizeRuleForGoal(Cons* goal, Cons* antecedent, Cons* forallvars, Cons* existsvars, Symbol* skolemfnid) {
  { Cons* skolemclauses = NIL;
    Cons* skolemizedrule = NIL;

    { Symbol* var = NULL;
      Cons* iter000 = existsvars;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        var = ((Symbol*)(iter000->value));
        if (searchConsTreeP(goal, var)) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(listO(3, SYM_RULES_PL_KERNEL_KB_SKOLEM_FN, skolemfnid, cons(wrapString(var->symbolName), copyConsList(forallvars)->concatenate(cons(var, NIL), 0))), NIL);
              if (skolemclauses == NIL) {
                skolemclauses = collect000;
              }
              else {
                addConsToEndOfConsList(skolemclauses, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(listO(3, SYM_RULES_PL_KERNEL_KB_SKOLEM_FN, skolemfnid, cons(wrapString(var->symbolName), copyConsList(forallvars)->concatenate(cons(var, NIL), 0))), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    if (skolemclauses == NIL) {
      skolemizedrule = listO(3, SYM_RULES_LOGIC_lle, goal, cons(antecedent, NIL));
    }
    else {
      skolemizedrule = listO(3, SYM_RULES_LOGIC_lle, goal, cons(listO(3, SYM_RULES_STELLA_AND, antecedent, skolemclauses->concatenate(NIL, 0)), NIL));
    }
    return (((Cons*)(copyConsTree(skolemizedrule))));
  }
}

Cons* helpGetForwardChainingRules(Description* description) {
  { Cons* rules = NIL;

    { ForwardChainingIndex* idx = NULL;
      Cons* iter000 = description->forwardChainingIndices_reader()->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        idx = ((ForwardChainingIndex*)(iter000->value));
        if (!idx->masterRule->deletedP()) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(idx->masterRule, NIL);
              if (rules == NIL) {
                rules = collect000;
              }
              else {
                addConsToEndOfConsList(rules, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(idx->masterRule, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    return (rules);
  }
}

Cons* callGetRules(Object* relationref) {
  { LogicObject* description = getDescription(relationref);
    Cons* rules = NIL;

    if (!((boolean)(description))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't find a relation named " << "`" << relationref << "'";
        throw *newNoSuchObjectException(stream000->theStringReader());
      }
    }
    if (subtypeOfP(safePrimaryType(description), SGT_RULES_LOGIC_NAMED_DESCRIPTION)) {
      { LogicObject* description000 = description;
        NamedDescription* description = ((NamedDescription*)(description000));

        rules = applicableRulesOfDescription(description, KWD_RULES_FORWARD, false)->concatenate(applicableRulesOfDescription(description, KWD_RULES_BACKWARD, false), 1, helpGetForwardChainingRules(description));
        { Description* complement = ((Description*)(dynamicSlotValue(description->dynamicSlots, SYM_RULES_LOGIC_COMPLEMENT_DESCRIPTION, NULL)));

          if (((boolean)(complement))) {
            rules = rules->concatenate(applicableRulesOfDescription(complement, KWD_RULES_FORWARD, false), 2, applicableRulesOfDescription(complement, KWD_RULES_BACKWARD, false), helpGetForwardChainingRules(complement));
          }
        }
      }
    }
    else {
    }
    return (rules);
  }
}

Cons* getRules(Object* relation) {
  // Return the list of rules associated with `relation'.
  processDefinitions();
  return (callGetRules(relation));
}

void deleteRules(Object* relation) {
  // Delete the list of rules associated with `relation'.
  // This function is included mainly for debugging purposes, when
  // a user wants to verify the behavior of different sets of rules.
  processDefinitions();
  { Proposition* r = NULL;
    Cons* iter000 = callGetRules(relation);

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      r = ((Proposition*)(iter000->value));
      destroyProposition(r);
    }
  }
}

void printRules(Object* relation) {
  // Print the list of true rules associated with `relation'.
  processDefinitions();
  { 
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getQueryContext());
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
    { Proposition* rule = NULL;
      Cons* iter000 = callGetRules(relation);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        rule = ((Proposition*)(iter000->value));
        if ((!rule->deletedP()) &&
            ((oREVERSEPOLARITYpo ? falseP(rule) : (trueP(rule) ||
            functionWithDefinedValueP(rule))))) {
          prettyPrintLogicalForm(rule, STANDARD_OUTPUT);
          std::cout << std::endl << std::endl;
        }
      }
    }
  }
}

void printSatellites(Proposition* forallprop) {
  { Proposition* rule = NULL;
    Cons* iter000 = forallprop->satellitePropositions_reader()->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      rule = ((Proposition*)(iter000->value));
      std::cout << rule << std::endl;
    }
  }
}

boolean propositionHasStrengthP(Proposition* self, TruthValue* minimalstrength) {
  // Return true if the truth-value of `self' satisfies `minimalStrength'.
  if (!((boolean)(minimalstrength))) {
    return (true);
  }
  else if ((minimalstrength == TRUE_TRUTH_VALUE) ||
      (minimalstrength == FALSE_TRUTH_VALUE)) {
    if (!(strictTruthValueP(((TruthValue*)(accessInContext(self->truthValue, self->homeContext, false)))))) {
      return (false);
    }
  }
  else if ((minimalstrength == DEFAULT_TRUE_TRUTH_VALUE) ||
      (minimalstrength == DEFAULT_FALSE_TRUTH_VALUE)) {
    if (unknownTruthValueP(((TruthValue*)(accessInContext(self->truthValue, self->homeContext, false))))) {
      return (false);
    }
  }
  return (true);
}

Proposition* getRule(Object* rulename) {
  { Object* object = getInstance(rulename);

    if ((!((boolean)(object))) ||
        (!isaP(object, SGT_RULES_LOGIC_PROPOSITION))) {
      std::cout << "Can't find a rule named " << "`" << rulename << "'" << std::endl << std::endl;
      return (NULL);
    }
    return (((Proposition*)(object)));
  }
}

Proposition* findRule(Object* rulename) {
  // Search for a rule named 'ruleName'.  Like 'get-rule',
  // but 'find-rule' implicity quotes its input argument.
  return (getRule(rulename));
}

Proposition* assertRule(Object* rulename) {
  // Set the truth value of the rule named 'ruleName' to 
  // TRUE.  The proposition having the name 'ruleName' may be
  // any arbitrary proposition, although we expect that it is probably
  // a material implication.  (See `retract-rule').
  { Proposition* proposition = getRule(rulename);

    if (!((boolean)(proposition))) {
      return (NULL);
    }
    updatePropositionTruthValue(proposition, KWD_RULES_ASSERT_TRUE);
    return (proposition);
  }
}

Proposition* retractRule(Object* rulename) {
  // If it is currently TRUE, set the truth value 
  // of the rule named 'ruleName' to UNKNOWN  This
  // command may be used alternately with `assert-rule' to
  // observe the effects of querying with or without a particular (named) rule
  // being asserted within the current context. The proposition having the name
  // 'ruleName' may be any arbitrary proposition, although we expect that it is
  // probably a material implication.
  { Proposition* proposition = getRule(rulename);

    if (!((boolean)(proposition))) {
      return (NULL);
    }
    updatePropositionTruthValue(proposition, KWD_RULES_RETRACT_TRUE);
    return (proposition);
  }
}

void deleteRuleCachesOnRelation(Relation* relation) {
  { Proposition* rule = NULL;
    Cons* iter000 = callGetRules(relation);

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      rule = ((Proposition*)(iter000->value));
      { Object* arg = NULL;
        Vector* vector000 = rule->arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          arg = (vector000->theArray)[index000];
          if (((boolean)(((Description*)(arg))->queryPatterns))) {
            { KvListIterator* it = ((KvListIterator*)(((Description*)(arg))->queryPatterns->allocateIterator()));

              for (; it->nextP(); ) {
                it->valueSetter(NULL);
              }
            }
          }
        }
      }
    }
  }
}

void resetQueryCaches() {
  // Zero out all caches managed by the query optimizer,
  // so that it will reoptimize subgoal queries upon next invocation.
  { Slot* slot = NULL;
    Iterator* iter000 = allSlots(NULL, true);

    for (; iter000->nextP(); ) {
      slot = ((Slot*)(iter000->value));
      if (((boolean)(((NamedDescription*)(dynamicSlotValue(slot->dynamicSlots, SYM_RULES_LOGIC_DESCRIPTION, NULL)))))) {
        deleteRuleCachesOnRelation(slot);
      }
    }
  }
  { NamedDescription* description = NULL;
    Iterator* iter001 = allNamedDescriptions(NULL, true);

    for (; iter001->nextP(); ) {
      description = ((NamedDescription*)(iter001->value));
      if (((boolean)(description->queryPatterns))) {
        { KvListIterator* it = ((KvListIterator*)(description->queryPatterns->allocateIterator()));

          for (; it->nextP(); ) {
            it->valueSetter(NULL);
          }
        }
      }
    }
  }
}

void helpStartupRules1() {
  {
    KWD_RULES_HEAD = ((Keyword*)(internRigidSymbolWrtModule("HEAD", NULL, 2)));
    SYM_RULES_LOGIC_IO_VARIABLES = ((Symbol*)(internRigidSymbolWrtModule("IO-VARIABLES", NULL, 0)));
    KWD_RULES_TAIL = ((Keyword*)(internRigidSymbolWrtModule("TAIL", NULL, 2)));
    KWD_RULES_AND = ((Keyword*)(internRigidSymbolWrtModule("AND", NULL, 2)));
    KWD_RULES_EXISTS = ((Keyword*)(internRigidSymbolWrtModule("EXISTS", NULL, 2)));
    KWD_RULES_OR = ((Keyword*)(internRigidSymbolWrtModule("OR", NULL, 2)));
    KWD_RULES_FORALL = ((Keyword*)(internRigidSymbolWrtModule("FORALL", NULL, 2)));
    KWD_RULES_ISA = ((Keyword*)(internRigidSymbolWrtModule("ISA", NULL, 2)));
    KWD_RULES_PREDICATE = ((Keyword*)(internRigidSymbolWrtModule("PREDICATE", NULL, 2)));
    KWD_RULES_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    KWD_RULES_NOT = ((Keyword*)(internRigidSymbolWrtModule("NOT", NULL, 2)));
    KWD_RULES_IMPLIES = ((Keyword*)(internRigidSymbolWrtModule("IMPLIES", NULL, 2)));
    SGT_RULES_PL_KERNEL_KB_HOLDS = ((Surrogate*)(internRigidSymbolWrtModule("HOLDS", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_RULES_LOGIC_PATTERN_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("PATTERN-VARIABLE", NULL, 1)));
    SYM_RULES_LOGIC_COMPLEMENT_DESCRIPTION = ((Symbol*)(internRigidSymbolWrtModule("COMPLEMENT-DESCRIPTION", NULL, 0)));
    SGT_RULES_STELLA_SURROGATE = ((Surrogate*)(internRigidSymbolWrtModule("SURROGATE", getStellaModule("/STELLA", true), 1)));
    KWD_RULES_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    SGT_RULES_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    SGT_RULES_STELLA_FALSE = ((Surrogate*)(internRigidSymbolWrtModule("FALSE", getStellaModule("/STELLA", true), 1)));
    SGT_RULES_STELLA_TRUE = ((Surrogate*)(internRigidSymbolWrtModule("TRUE", getStellaModule("/STELLA", true), 1)));
    SYM_RULES_STELLA_FORALL = ((Symbol*)(internRigidSymbolWrtModule("FORALL", getStellaModule("/STELLA", true), 0)));
    KWD_RULES_DESCRIPTION = ((Keyword*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 2)));
    SYM_RULES_LOGIC_FORWARD_ONLYp = ((Symbol*)(internRigidSymbolWrtModule("FORWARD-ONLY?", NULL, 0)));
    KWD_RULES_EXTENSIONAL_ASSERTION = ((Keyword*)(internRigidSymbolWrtModule("EXTENSIONAL-ASSERTION", NULL, 2)));
    SYM_RULES_LOGIC_SATELLITE_PROPOSITIONS = ((Symbol*)(internRigidSymbolWrtModule("SATELLITE-PROPOSITIONS", NULL, 0)));
    SYM_RULES_LOGIC_MASTER_PROPOSITION = ((Symbol*)(internRigidSymbolWrtModule("MASTER-PROPOSITION", NULL, 0)));
    SYM_RULES_LOGIC_BACKWARD_ONLYp = ((Symbol*)(internRigidSymbolWrtModule("BACKWARD-ONLY?", NULL, 0)));
    SYM_RULES_LOGIC_DONT_OPTIMIZEp = ((Symbol*)(internRigidSymbolWrtModule("DONT-OPTIMIZE?", NULL, 0)));
    KWD_RULES_POSITIVE = ((Keyword*)(internRigidSymbolWrtModule("POSITIVE", NULL, 2)));
    KWD_RULES_CONTRAPOSITIVE = ((Keyword*)(internRigidSymbolWrtModule("CONTRAPOSITIVE", NULL, 2)));
    SYM_RULES_LOGIC_RULES_WITH_DEFERRED_SATELLITES = ((Symbol*)(internRigidSymbolWrtModule("RULES-WITH-DEFERRED-SATELLITES", NULL, 0)));
    KWD_RULES_NON_PAGING = ((Keyword*)(internRigidSymbolWrtModule("NON-PAGING", NULL, 2)));
    SYM_RULES_LOGIC_DEFERRED_CONTRAPOSITIVESp = ((Symbol*)(internRigidSymbolWrtModule("DEFERRED-CONTRAPOSITIVES?", NULL, 0)));
    KWD_RULES_POSITIVE_AND_CONTRAPOSITIVE = ((Keyword*)(internRigidSymbolWrtModule("POSITIVE-AND-CONTRAPOSITIVE", NULL, 2)));
    SYM_RULES_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", getStellaModule("/STELLA", true), 0)));
    SYM_RULES_STELLA_EXISTS = ((Symbol*)(internRigidSymbolWrtModule("EXISTS", getStellaModule("/STELLA", true), 0)));
    SYM_RULES_LOGIC_FORWARD_CHAINING_INDICES = ((Symbol*)(internRigidSymbolWrtModule("FORWARD-CHAINING-INDICES", NULL, 0)));
    SYM_RULES_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", getStellaModule("/STELLA", true), 0)));
    KWD_RULES_CONCEIVE = ((Keyword*)(internRigidSymbolWrtModule("CONCEIVE", NULL, 2)));
    SYM_RULES_PL_KERNEL_KB_SKOLEM_FN = ((Symbol*)(internRigidSymbolWrtModule("SKOLEM-FN", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_RULES_LOGIC_lle = ((Symbol*)(internRigidSymbolWrtModule("<<=", NULL, 0)));
    SGT_RULES_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", NULL, 1)));
    KWD_RULES_FORWARD = ((Keyword*)(internRigidSymbolWrtModule("FORWARD", NULL, 2)));
    KWD_RULES_BACKWARD = ((Keyword*)(internRigidSymbolWrtModule("BACKWARD", NULL, 2)));
    KWD_RULES_ASSERT_TRUE = ((Keyword*)(internRigidSymbolWrtModule("ASSERT-TRUE", NULL, 2)));
    KWD_RULES_RETRACT_TRUE = ((Keyword*)(internRigidSymbolWrtModule("RETRACT-TRUE", NULL, 2)));
    SYM_RULES_LOGIC_DESCRIPTION = ((Symbol*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 0)));
    SYM_RULES_LOGIC_STARTUP_RULES = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-RULES", NULL, 0)));
    SYM_RULES_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void startupRules() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupRules1();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("FIND-MATCHABLE-GOALS", "(DEFUN (FIND-MATCHABLE-GOALS (LIST OF PROPOSITION)) ((FORALLPROP PROPOSITION) (HEADORTAIL KEYWORD)))", ((cpp_function_code)(&findMatchableGoals)), NULL);
      defineFunctionObject("COLLECT-MATCHING-RULE-GOALS", "(DEFUN COLLECT-MATCHING-RULE-GOALS ((PROPOSITION PROPOSITION) (TOPLEVELVARS CONS) (HEADORTAIL KEYWORD) (COLLECTION (LIST OF PROPOSITION))))", ((cpp_function_code)(&collectMatchingRuleGoals)), NULL);
      defineFunctionObject("ATOMIC-FORALL-ARGUMENT?", "(DEFUN (ATOMIC-FORALL-ARGUMENT? BOOLEAN) ((FORALLPROP PROPOSITION) (HEADORTAIL KEYWORD)))", ((cpp_function_code)(&atomicForallArgumentP)), NULL);
      defineFunctionObject("ATOMIC-GOAL-PROPOSITION?", "(DEFUN (ATOMIC-GOAL-PROPOSITION? BOOLEAN) ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&atomicGoalPropositionP)), NULL);
      defineFunctionObject("ATOMIC-GOAL-DESCRIPTION?", "(DEFUN (ATOMIC-GOAL-DESCRIPTION? BOOLEAN) ((DESCRIPTION DESCRIPTION)))", ((cpp_function_code)(&atomicGoalDescriptionP)), NULL);
      defineFunctionObject("VARIABLE-ARITY-GOAL-PROPOSITION?", "(DEFUN (VARIABLE-ARITY-GOAL-PROPOSITION? BOOLEAN) ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&variableArityGoalPropositionP)), NULL);
      defineFunctionObject("CHAINABLE-RELATION?", "(DEFUN (CHAINABLE-RELATION? BOOLEAN) ((DESCRIPTION NAMED-DESCRIPTION) (HEADORTAIL KEYWORD)))", ((cpp_function_code)(&chainableRelationP)), NULL);
      defineFunctionObject("EXTRACT-GOAL-DESCRIPTION", "(DEFUN (EXTRACT-GOAL-DESCRIPTION DESCRIPTION) ((GOAL PROPOSITION) (HEADORTAIL KEYWORD)))", ((cpp_function_code)(&extractGoalDescription)), NULL);
      defineFunctionObject("EXTRACT-GOAL-ARGUMENTS", "(DEFUN (EXTRACT-GOAL-ARGUMENTS CONS) ((GOAL PROPOSITION)))", ((cpp_function_code)(&extractGoalArguments)), NULL);
      defineFunctionObject("SUBSTITUTE-PROPOSITION", "(DEFUN (SUBSTITUTE-PROPOSITION PROPOSITION) ((PROPOSITION PROPOSITION) (OUTPROP PROPOSITION) (INPROP PROPOSITION)))", ((cpp_function_code)(&substituteProposition)), NULL);
      defineFunctionObject("EXTRACT-INVERTED-GOAL", "(DEFUN (EXTRACT-INVERTED-GOAL PROPOSITION) ((PROPOSITION PROPOSITION) (GOAL PROPOSITION)))", ((cpp_function_code)(&extractInvertedGoal)), NULL);
      defineFunctionObject("INVERT-FORALL-AROUND-GOAL", "(DEFUN (INVERT-FORALL-AROUND-GOAL PROPOSITION) ((FORALLPROP PROPOSITION) (GOAL PROPOSITION) (HEADORTAIL KEYWORD) (CONTRAPOSITIVE? BOOLEAN)))", ((cpp_function_code)(&invertForallAroundGoal)), NULL);
      defineFunctionObject("CONSTRUCT-DESCRIPTION-FROM-FORALL-PROPOSITION", "(DEFUN (CONSTRUCT-DESCRIPTION-FROM-FORALL-PROPOSITION DESCRIPTION) ((FORALLPROP PROPOSITION) (HEADORTAIL KEYWORD)))", ((cpp_function_code)(&constructDescriptionFromForallProposition)), NULL);
      defineFunctionObject("MARK-AS-FORWARD-RULE", "(DEFUN MARK-AS-FORWARD-RULE ((IMPLIESPROP PROPOSITION)))", ((cpp_function_code)(&markAsForwardRule)), NULL);
      defineFunctionObject("DERIVE-ONE-SATELLITE-RULE", "(DEFUN DERIVE-ONE-SATELLITE-RULE ((MASTERFORALL PROPOSITION) (GOAL PROPOSITION) (HEADORTAIL KEYWORD) (CONTRAPOSITIVE? BOOLEAN)))", ((cpp_function_code)(&deriveOneSatelliteRule)), NULL);
      defineFunctionObject("DERIVE-SATELLITE-RULES-FOR-GOAL?", "(DEFUN (DERIVE-SATELLITE-RULES-FOR-GOAL? BOOLEAN) ((FORALLPROP PROPOSITION) (GOALDESCRIPTION DESCRIPTION) (DIRECTION KEYWORD) (LAZYSATELLITES? BOOLEAN)))", ((cpp_function_code)(&deriveSatelliteRulesForGoalP)), NULL);
      defineFunctionObject("DERIVE-SATELLITE-RULES", "(DEFUN DERIVE-SATELLITE-RULES ((FORALLPROP PROPOSITION)))", ((cpp_function_code)(&deriveSatelliteRules)), NULL);
      defineFunctionObject("DERIVE-DEFERRED-SATELLITE-RULES", "(DEFUN DERIVE-DEFERRED-SATELLITE-RULES ((SELF DESCRIPTION)))", ((cpp_function_code)(&deriveDeferredSatelliteRules)), NULL);
      defineFunctionObject("DERIVE-DEFERRED-CONTRAPOSITIVE-SATELLITE-RULES", "(DEFUN DERIVE-DEFERRED-CONTRAPOSITIVE-SATELLITE-RULES ((SELF DESCRIPTION)))", ((cpp_function_code)(&deriveDeferredContrapositiveSatelliteRules)), NULL);
      defineFunctionObject("GET-INFERABLE-COMPLEMENT-DESCRIPTION", "(DEFUN (GET-INFERABLE-COMPLEMENT-DESCRIPTION DESCRIPTION) ((SELF DESCRIPTION)))", ((cpp_function_code)(&getInferableComplementDescription)), NULL);
      defineFunctionObject("DERIVE-IMPLIES-FROM-FORALL", "(DEFUN (DERIVE-IMPLIES-FROM-FORALL PROPOSITION) ((FORALLPROP PROPOSITION)))", ((cpp_function_code)(&deriveImpliesFromForall)), NULL);
      defineFunctionObject("DECONSTRUCT-FORALL-TREE", "(DEFUN (DECONSTRUCT-FORALL-TREE CONS OBJECT CONS) ((FORALLTREE CONS)))", ((cpp_function_code)(&deconstructForallTree)), NULL);
      defineFunctionObject("CREATE-FORWARD-CHAINING-INDEX", "(DEFUN (CREATE-FORWARD-CHAINING-INDEX FORWARD-CHAINING-INDEX) ((GOAL PROPOSITION) (MASTERFORALL PROPOSITION)))", ((cpp_function_code)(&createForwardChainingIndex)), NULL);
      defineFunctionObject("DERIVE-COMPLEX-FORWARD-RULE", "(DEFUN DERIVE-COMPLEX-FORWARD-RULE ((GOAL PROPOSITION) (MASTERFORALL PROPOSITION)))", ((cpp_function_code)(&deriveComplexForwardRule)), NULL);
      defineFunctionObject("SKOLEMIZE-RULE", "(DEFUN SKOLEMIZE-RULE ((RULE PROPOSITION)))", ((cpp_function_code)(&skolemizeRule)), NULL);
      defineFunctionObject("SKOLEMIZE-RULE-FOR-GOAL", "(DEFUN (SKOLEMIZE-RULE-FOR-GOAL CONS) ((GOAL CONS) (ANTECEDENT CONS) (FORALLVARS (CONS OF SYMBOL)) (EXISTSVARS (CONS OF SYMBOL)) (SKOLEMFNID SYMBOL)))", ((cpp_function_code)(&skolemizeRuleForGoal)), NULL);
      defineFunctionObject("HELP-GET-FORWARD-CHAINING-RULES", "(DEFUN (HELP-GET-FORWARD-CHAINING-RULES (CONS OF PROPOSITION)) ((DESCRIPTION DESCRIPTION)))", ((cpp_function_code)(&helpGetForwardChainingRules)), NULL);
      defineFunctionObject("CALL-GET-RULES", "(DEFUN (CALL-GET-RULES (CONS OF PROPOSITION)) ((RELATIONREF OBJECT)))", ((cpp_function_code)(&callGetRules)), NULL);
      defineFunctionObject("GET-RULES", "(DEFUN (GET-RULES (CONS OF PROPOSITION)) ((RELATION NAME)) :DOCUMENTATION \"Return the list of rules associated with `relation'.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&getRules)), NULL);
      defineFunctionObject("DELETE-RULES", "(DEFUN DELETE-RULES ((RELATION NAME)) :DOCUMENTATION \"Delete the list of rules associated with `relation'.\nThis function is included mainly for debugging purposes, when\na user wants to verify the behavior of different sets of rules.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&deleteRules)), NULL);
      defineFunctionObject("PRINT-RULES", "(DEFUN PRINT-RULES ((RELATION OBJECT)) :DOCUMENTATION \"Print the list of true rules associated with `relation'.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&printRules)), NULL);
      defineFunctionObject("PRINT-SATELLITES", "(DEFUN PRINT-SATELLITES ((FORALLPROP PROPOSITION)))", ((cpp_function_code)(&printSatellites)), NULL);
      defineFunctionObject("PROPOSITION-HAS-STRENGTH?", "(DEFUN (PROPOSITION-HAS-STRENGTH? BOOLEAN) ((SELF PROPOSITION) (MINIMALSTRENGTH TRUTH-VALUE)) :DOCUMENTATION \"Return true if the truth-value of `self' satisfies `minimalStrength'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&propositionHasStrengthP)), NULL);
      defineFunctionObject("GET-RULE", "(DEFUN (GET-RULE PROPOSITION) ((RULENAME NAME)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? TRUE)", ((cpp_function_code)(&getRule)), NULL);
      defineFunctionObject("FIND-RULE", "(DEFUN (FIND-RULE PROPOSITION) ((RULENAME NAME)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Search for a rule named 'ruleName'.  Like 'get-rule',\nbut 'find-rule' implicity quotes its input argument.\")", ((cpp_function_code)(&findRule)), NULL);
      defineFunctionObject("ASSERT-RULE", "(DEFUN (ASSERT-RULE PROPOSITION) ((RULENAME NAME)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Set the truth value of the rule named 'ruleName' to \nTRUE.  The proposition having the name 'ruleName' may be\nany arbitrary proposition, although we expect that it is probably\na material implication.  (See `retract-rule').\")", ((cpp_function_code)(&assertRule)), NULL);
      defineFunctionObject("RETRACT-RULE", "(DEFUN (RETRACT-RULE PROPOSITION) ((RULENAME NAME)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"If it is currently TRUE, set the truth value \nof the rule named 'ruleName' to UNKNOWN  This\ncommand may be used alternately with `assert-rule' to\nobserve the effects of querying with or without a particular (named) rule\nbeing asserted within the current context. The proposition having the name\n'ruleName' may be any arbitrary proposition, although we expect that it is\nprobably a material implication.\")", ((cpp_function_code)(&retractRule)), NULL);
      defineFunctionObject("DELETE-RULE-CACHES-ON-RELATION", "(DEFUN DELETE-RULE-CACHES-ON-RELATION ((RELATION RELATION)))", ((cpp_function_code)(&deleteRuleCachesOnRelation)), NULL);
      defineFunctionObject("RESET-QUERY-CACHES", "(DEFUN RESET-QUERY-CACHES () :DOCUMENTATION \"Zero out all caches managed by the query optimizer,\nso that it will reoptimize subgoal queries upon next invocation.\")", ((cpp_function_code)(&resetQueryCaches)), NULL);
      defineFunctionObject("STARTUP-RULES", "(DEFUN STARTUP-RULES () :PUBLIC? TRUE)", ((cpp_function_code)(&startupRules)), NULL);
      { MethodSlot* function = lookupFunction(SYM_RULES_LOGIC_STARTUP_RULES);

        setDynamicSlotValue(function->dynamicSlots, SYM_RULES_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupRules"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFGLOBAL *LAZY-SATELLITE-RULES?* BOOLEAN FALSE :DOCUMENTATION \"If true, inversion of forall propositions happens lazily.\nI.e., satellite rules are generated on-demand during inference only if they\nare actually needed.\" :PUBLIC? TRUE)", &oLAZY_SATELLITE_RULESpo);
      defineGlobalVariableObject("(DEFSPECIAL *DERIVE-DEFERRED-SATELLITE-RULES-INVOCATIONS* (LIST OF DESCRIPTION) NULL)", &oDERIVE_DEFERRED_SATELLITE_RULES_INVOCATIONSo);
    }
  }
}

Keyword* KWD_RULES_HEAD = NULL;

Symbol* SYM_RULES_LOGIC_IO_VARIABLES = NULL;

Keyword* KWD_RULES_TAIL = NULL;

Keyword* KWD_RULES_AND = NULL;

Keyword* KWD_RULES_EXISTS = NULL;

Keyword* KWD_RULES_OR = NULL;

Keyword* KWD_RULES_FORALL = NULL;

Keyword* KWD_RULES_ISA = NULL;

Keyword* KWD_RULES_PREDICATE = NULL;

Keyword* KWD_RULES_FUNCTION = NULL;

Keyword* KWD_RULES_NOT = NULL;

Keyword* KWD_RULES_IMPLIES = NULL;

Surrogate* SGT_RULES_PL_KERNEL_KB_HOLDS = NULL;

Surrogate* SGT_RULES_LOGIC_PATTERN_VARIABLE = NULL;

Symbol* SYM_RULES_LOGIC_COMPLEMENT_DESCRIPTION = NULL;

Surrogate* SGT_RULES_STELLA_SURROGATE = NULL;

Keyword* KWD_RULES_ERROR = NULL;

Surrogate* SGT_RULES_LOGIC_PROPOSITION = NULL;

Surrogate* SGT_RULES_STELLA_FALSE = NULL;

Surrogate* SGT_RULES_STELLA_TRUE = NULL;

Symbol* SYM_RULES_STELLA_FORALL = NULL;

Keyword* KWD_RULES_DESCRIPTION = NULL;

Symbol* SYM_RULES_LOGIC_FORWARD_ONLYp = NULL;

Keyword* KWD_RULES_EXTENSIONAL_ASSERTION = NULL;

Symbol* SYM_RULES_LOGIC_SATELLITE_PROPOSITIONS = NULL;

Symbol* SYM_RULES_LOGIC_MASTER_PROPOSITION = NULL;

Symbol* SYM_RULES_LOGIC_BACKWARD_ONLYp = NULL;

Symbol* SYM_RULES_LOGIC_DONT_OPTIMIZEp = NULL;

Keyword* KWD_RULES_POSITIVE = NULL;

Keyword* KWD_RULES_CONTRAPOSITIVE = NULL;

Symbol* SYM_RULES_LOGIC_RULES_WITH_DEFERRED_SATELLITES = NULL;

Keyword* KWD_RULES_NON_PAGING = NULL;

Symbol* SYM_RULES_LOGIC_DEFERRED_CONTRAPOSITIVESp = NULL;

Keyword* KWD_RULES_POSITIVE_AND_CONTRAPOSITIVE = NULL;

Symbol* SYM_RULES_STELLA_TRUE = NULL;

Symbol* SYM_RULES_STELLA_EXISTS = NULL;

Symbol* SYM_RULES_LOGIC_FORWARD_CHAINING_INDICES = NULL;

Symbol* SYM_RULES_STELLA_AND = NULL;

Keyword* KWD_RULES_CONCEIVE = NULL;

Symbol* SYM_RULES_PL_KERNEL_KB_SKOLEM_FN = NULL;

Symbol* SYM_RULES_LOGIC_lle = NULL;

Surrogate* SGT_RULES_LOGIC_NAMED_DESCRIPTION = NULL;

Keyword* KWD_RULES_FORWARD = NULL;

Keyword* KWD_RULES_BACKWARD = NULL;

Keyword* KWD_RULES_ASSERT_TRUE = NULL;

Keyword* KWD_RULES_RETRACT_TRUE = NULL;

Symbol* SYM_RULES_LOGIC_DESCRIPTION = NULL;

Symbol* SYM_RULES_LOGIC_STARTUP_RULES = NULL;

Symbol* SYM_RULES_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
