//  -*- Mode: C++ -*-

// api-support.cc

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

boolean classNamesNextP(AllPurposeIterator* self) {
  if (self->firstIterationP) {
    self->firstIterationP = false;
    self->value = ((Class*)(self->iteratorObject))->classType;
    return (true);
  }
  { boolean nextP = self->iteratorNestedIterator->nextP();

    if (nextP) {
      self->value = self->iteratorNestedIterator->value;
    }
    return (nextP);
  }
}

boolean allPropositionsNextP(AllPurposeIterator* self) {
  for (;;) {
    { Iterator* iterator = self->iteratorNestedIterator;
      Module* module = NULL;

      if (iterator->nextP()) {
        self->value = iterator->value;
        return (true);
      }
      module = ((Module*)(((List*)(self->iteratorObject))->pop()));
      if (!((boolean)(module))) {
        self->value = NULL;
        return (false);
      }
      self->iteratorNestedIterator = locallyConceivedPropositions(module)->allocateIterator();
    }
  }
}

Iterator* allPropositions(Module* module, boolean localP) {
  // Iterate over all conceived propositions visible from `module'.
  // Only propositions that haven't been deleted will be considered.
  // If `local?', only return propositions conceived locally in `module'.
  { AllPurposeIterator* self000 = newAllPurposeIterator();

    self000->iteratorObject = (localP ? list(0) : copyConsList(visibleModules(module)->rest)->reverse()->listify());
    self000->iteratorNestedIterator = locallyConceivedPropositions(module)->allocateIterator();
    self000->iteratorNextCode = ((cpp_function_code)(&allPropositionsNextP));
    { AllPurposeIterator* value000 = self000;

      return (value000);
    }
  }
}

boolean filterInconsistentPropositionP(Object* self, AllPurposeIterator* iterator) {
  { Module* module = ((Module*)(iterator->iteratorObject));

    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, NULL);
      BIND_STELLA_SPECIAL(oMODULEo, Module*, NULL);
      { World* temp000 = bestInferenceCache(module);

        oCONTEXTo = (((boolean)(temp000)) ? ((Context*)(temp000)) : ((Context*)(module)));
      }
      oMODULEo = oCONTEXTo->baseModule;
      return (inconsistentP(((Proposition*)(self))));
    }
  }
}

Iterator* allInconsistentPropositions(Module* module, boolean localP) {
  // Iterate over all conceived propositions visible from `module'
  // that have an inconsistent truth value.  If `local?', only return
  // inconsistent propositions conceived locally in `module'.
  { Iterator* propositionsIterator = allPropositions(module, localP);
    AllPurposeIterator* iterator = newAllPurposeIterator();

    iterator->iteratorObject = module;
    iterator->firstIterationP = true;
    iterator->iteratorNestedIterator = propositionsIterator;
    iterator->iteratorNextCode = ((cpp_function_code)(&filteredNestedIteratorNextP));
    iterator->iteratorFilterCode = ((cpp_function_code)(&filterInconsistentPropositionP));
    return (iterator);
  }
}

boolean locallyModifiedPropositionP(Proposition* proposition, Module* module) {
  // Return true if proposition's truth-value has been locally modified in
  // `module' (initialized, asserted, retracted).  This will always succeed for locally conceived
  // propositions regardless of whether their truth value is defined or not.
  { Object* truthvalue = proposition->truthValue;

    if ((!((boolean)(truthvalue))) ||
        isaP(truthvalue, SGT_API_SUPPORT_LOGIC_TRUTH_VALUE)) {
      return (proposition->homeModule() == module);
    }
    else {
      { Object* ctxt = NULL;
        Object* tv = NULL;
        KvCons* iter000 = ((KeyValueList*)(truthvalue))->theKvList;

        for  (; ((boolean)(iter000)); 
              iter000 = iter000->rest) {
          ctxt = iter000->key;
          tv = iter000->value;
          tv = tv;
          if (ctxt == module) {
            return (true);
          }
        }
      }
    }
    return (false);
  }
}

boolean filterLocallyModifiedPropositionP(Object* self, AllPurposeIterator* iterator) {
  return (locallyModifiedPropositionP(((Proposition*)(self)), ((Module*)(iterator->iteratorObject))));
}

Iterator* allLocallyModifiedPropositions(Module* module) {
  // Iterate over all conceived propositions visible from `module' that had their
  // truth value locally modified (initialized, asserted, retracted).  Note, that this
  // will always include all locally conceived propositions.
  { Iterator* propositionsIterator = allPropositions(module, false);
    AllPurposeIterator* iterator = newAllPurposeIterator();

    iterator->iteratorObject = module;
    iterator->firstIterationP = true;
    iterator->iteratorNestedIterator = propositionsIterator;
    iterator->iteratorNextCode = ((cpp_function_code)(&filteredNestedIteratorNextP));
    iterator->iteratorFilterCode = ((cpp_function_code)(&filterLocallyModifiedPropositionP));
    return (iterator);
  }
}

boolean visibleTermP(LogicObject* term, Context* context, boolean localP) {
  return ((localP ? (term->homeContext == context) : visibleFromP(term->homeContext, context)));
}

Iterator* allUnnamedTerms(Module* module, boolean localP) {
  // Iterate over all unnamed terms visible from `module'.  A term can be
  // an instance (or individual) as well as a description.  Only terms that
  // haven't been deleted will be considered.  If `local?', only return
  // terms created locally in `module'.
  { Cons* terms = NIL;
    Cons* termswithduplicates = NIL;
    LogicObject* term = NULL;

    { Proposition* proposition = NULL;
      Iterator* iter000 = allPropositions(module, localP);

      for (; iter000->nextP(); ) {
        proposition = ((Proposition*)(iter000->value));
        { Object* arg = NULL;
          Vector* vector000 = proposition->arguments;
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            arg = (vector000->theArray)[index000];
            if (((boolean)(arg)) &&
                (isaP(arg, SGT_API_SUPPORT_LOGIC_LOGIC_OBJECT) &&
                 (!arg->deletedP()))) {
              term = ((LogicObject*)(arg));
              if ((!visibleTermP(term, module, localP)) ||
                  ((boolean)(term->surrogateValueInverse))) {
                continue;
              }
              { Surrogate* testValue000 = safePrimaryType(term);

                if (subtypeOfP(testValue000, SGT_API_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
                  { LogicObject* term000 = term;
                    PatternVariable* term = ((PatternVariable*)(term000));

                  }
                }
                else if (subtypeOfP(testValue000, SGT_API_SUPPORT_LOGIC_SKOLEM)) {
                  { LogicObject* term001 = term;
                    Skolem* term = ((Skolem*)(term001));

                    if (((boolean)(term->definingProposition))) {
                      if (term->definingProposition == proposition) {
                        terms = cons(term, terms);
                      }
                    }
                    else {
                      termswithduplicates = cons(term, termswithduplicates);
                    }
                  }
                }
                else {
                  termswithduplicates = cons(term, termswithduplicates);
                }
              }
            }
          }
        }
      }
    }
    return (terms->concatenate(termswithduplicates->removeDuplicates(), 0)->allocateIterator());
  }
}

boolean namedTermP(Object* term, AllPurposeIterator* iter) {
  iter = iter;
  { Surrogate* testValue000 = safePrimaryType(term);

    if (subtypeOfP(testValue000, SGT_API_SUPPORT_LOGIC_NAMED_DESCRIPTION)) {
      { Object* term000 = term;
        NamedDescription* term = ((NamedDescription*)(term000));

        return (!term->deletedP());
      }
    }
    else if (subtypeOfP(testValue000, SGT_API_SUPPORT_LOGIC_DESCRIPTION)) {
      { Object* term001 = term;
        Description* term = ((Description*)(term001));

        return (false);
      }
    }
    else if (subtypeOfP(testValue000, SGT_API_SUPPORT_LOGIC_PATTERN_VARIABLE)) {
      { Object* term002 = term;
        PatternVariable* term = ((PatternVariable*)(term002));

        return (false);
      }
    }
    else if (subtypeOfP(testValue000, SGT_API_SUPPORT_LOGIC_LOGIC_OBJECT)) {
      { Object* term003 = term;
        LogicObject* term = ((LogicObject*)(term003));

        return (!term->deletedP());
      }
    }
    else if (subtypeOfP(testValue000, SGT_API_SUPPORT_STELLA_THING)) {
      { Object* term004 = term;
        Thing* term = ((Thing*)(term004));

        return (!term->deletedP());
      }
    }
    else {
      return (false);
    }
  }
}

Iterator* allNamedTerms(Module* module, boolean localP) {
  // Iterate over all named terms visible from `module'.  A term can be an
  // instance (or individual) as well as a description.  Only terms that
  // haven't been deleted will be considered.  If `local?', only return 
  // terms created locally in `module'.
  if (localP) {
    { AllPurposeIterator* self000 = newAllPurposeIterator();

      self000->iteratorNestedIterator = locallyConceivedInstances(module)->allocateIterator();
      self000->iteratorNextCode = ((cpp_function_code)(&filteredNestedIteratorNextP));
      self000->iteratorFilterCode = ((cpp_function_code)(&namedTermP));
      { AllPurposeIterator* value000 = self000;

        return (value000);
      }
    }
  }
  else {
    { Iterator* iterator1 = allNamedTerms(module, true);
      Cons* iteratorlist = NIL;

      { Context* super = NULL;
        Cons* iter000 = module->allSuperContexts;
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          super = ((Context*)(iter000->value));
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(allNamedTerms(((Module*)(super)), true), NIL);
              if (iteratorlist == NIL) {
                iteratorlist = collect000;
              }
              else {
                addConsToEndOfConsList(iteratorlist, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(allNamedTerms(((Module*)(super)), true), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      if (iteratorlist == NIL) {
        return (iterator1);
      }
      else {
        { AllPurposeIterator* self001 = newAllPurposeIterator();

          self001->iteratorNestedIterator = iterator1;
          self001->iteratorConsList = iteratorlist;
          self001->iteratorNextCode = ((cpp_function_code)(&filteredConcatenatedIteratorNextP));
          { AllPurposeIterator* value001 = self001;

            return (value001);
          }
        }
      }
    }
  }
}

Iterator* allTerms(Module* module, boolean localP) {
  // Return a list of all terms visible from `module'.  A term can be an
  // instance (or individual) as well as a description.  Only terms that
  // haven't been deleted will be considered.  If `local?', only return 
  // terms created locally in `module'.
  if (localP) {
    {
      locallyConceivedInstances(module)->removeDeletedMembers();
      return (locallyConceivedInstances(module)->allocateIterator());
    }
  }
  else {
    return (allNamedTerms(module, false)->concatenate(allUnnamedTerms(module, false), 0));
  }
}

boolean filterInstanceP(LogicObject* self, AllPurposeIterator* iterator) {
  iterator = iterator;
  return (!isaP(self, SGT_API_SUPPORT_LOGIC_DESCRIPTION));
}

Iterator* allNamedInstances(Module* module, boolean localP) {
  // Iterate over all named instances (or individuals) visible from `module'.
  // Only instances that haven't been deleted will be considered.  If `local?',
  // only return instances created locally in `module'.
  { AllPurposeIterator* self000 = newAllPurposeIterator();

    self000->iteratorNestedIterator = allNamedTerms(module, localP);
    self000->iteratorNextCode = ((cpp_function_code)(&filteredNestedIteratorNextP));
    self000->iteratorFilterCode = ((cpp_function_code)(&filterInstanceP));
    { AllPurposeIterator* value000 = self000;

      return (value000);
    }
  }
}

Iterator* allInstances(Module* module, boolean localP) {
  // Iterate over all instances (or individuals) visible from `module'.
  // Only instances that haven't been deleted will be considered.  If `local?',
  // only return instances created locally in `module'.
  { Iterator* iterator = allTerms(module, localP);
    AllPurposeIterator* allpurposeiterator = NULL;

    if (localP) {
      { AllPurposeIterator* self000 = newAllPurposeIterator();

        self000->iteratorNestedIterator = iterator;
        self000->iteratorNextCode = ((cpp_function_code)(&filteredNestedIteratorNextP));
        allpurposeiterator = self000;
      }
    }
    else {
      allpurposeiterator = ((AllPurposeIterator*)(iterator));
    }
    allpurposeiterator->iteratorFilterCode = ((cpp_function_code)(&filterInstanceP));
    return (allpurposeiterator);
  }
}

LogicObject* stringToLogicObject(const char* string) {
  { Surrogate* sgt = NULL;
    Iterator* iter000 = allSurrogates(NULL, false);

    for (; iter000->nextP(); ) {
      sgt = ((Surrogate*)(iter000->value));
      if (stringEqlP(sgt->symbolName, string) &&
          (((boolean)(sgt->surrogateValue)) &&
           isaP(sgt->surrogateValue, SGT_API_SUPPORT_LOGIC_LOGIC_OBJECT))) {
        return (((LogicObject*)(sgt->surrogateValue)));
      }
    }
  }
  return (NULL);
}

void startupApiSupport() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SGT_API_SUPPORT_LOGIC_TRUTH_VALUE = ((Surrogate*)(internRigidSymbolWrtModule("TRUTH-VALUE", NULL, 1)));
      SGT_API_SUPPORT_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", NULL, 1)));
      SGT_API_SUPPORT_LOGIC_PATTERN_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("PATTERN-VARIABLE", NULL, 1)));
      SGT_API_SUPPORT_LOGIC_SKOLEM = ((Surrogate*)(internRigidSymbolWrtModule("SKOLEM", NULL, 1)));
      SGT_API_SUPPORT_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", NULL, 1)));
      SGT_API_SUPPORT_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 1)));
      SGT_API_SUPPORT_STELLA_THING = ((Surrogate*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 1)));
      SYM_API_SUPPORT_LOGIC_STARTUP_API_SUPPORT = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-API-SUPPORT", NULL, 0)));
      SYM_API_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("CLASS-NAMES-NEXT?", "(DEFUN (CLASS-NAMES-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&classNamesNextP)), NULL);
      defineFunctionObject("ALL-PROPOSITIONS-NEXT?", "(DEFUN (ALL-PROPOSITIONS-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&allPropositionsNextP)), NULL);
      defineFunctionObject("ALL-PROPOSITIONS", "(DEFUN (ALL-PROPOSITIONS (ITERATOR OF PROPOSITION)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all conceived propositions visible from `module'.\nOnly propositions that haven't been deleted will be considered.\nIf `local?', only return propositions conceived locally in `module'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allPropositions)), NULL);
      defineFunctionObject("FILTER-INCONSISTENT-PROPOSITION?", "(DEFUN (FILTER-INCONSISTENT-PROPOSITION? BOOLEAN) ((SELF OBJECT) (ITERATOR ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&filterInconsistentPropositionP)), NULL);
      defineFunctionObject("ALL-INCONSISTENT-PROPOSITIONS", "(DEFUN (ALL-INCONSISTENT-PROPOSITIONS (ITERATOR OF PROPOSITION)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all conceived propositions visible from `module'\nthat have an inconsistent truth value.  If `local?', only return\ninconsistent propositions conceived locally in `module'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allInconsistentPropositions)), NULL);
      defineFunctionObject("LOCALLY-MODIFIED-PROPOSITION?", "(DEFUN (LOCALLY-MODIFIED-PROPOSITION? BOOLEAN) ((PROPOSITION PROPOSITION) (MODULE MODULE)) :DOCUMENTATION \"Return true if proposition's truth-value has been locally modified in\n`module' (initialized, asserted, retracted).  This will always succeed for locally conceived\npropositions regardless of whether their truth value is defined or not.\" :PUBLIC? TRUE)", ((cpp_function_code)(&locallyModifiedPropositionP)), NULL);
      defineFunctionObject("FILTER-LOCALLY-MODIFIED-PROPOSITION?", "(DEFUN (FILTER-LOCALLY-MODIFIED-PROPOSITION? BOOLEAN) ((SELF OBJECT) (ITERATOR ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&filterLocallyModifiedPropositionP)), NULL);
      defineFunctionObject("ALL-LOCALLY-MODIFIED-PROPOSITIONS", "(DEFUN (ALL-LOCALLY-MODIFIED-PROPOSITIONS (ITERATOR OF PROPOSITION)) ((MODULE MODULE)) :DOCUMENTATION \"Iterate over all conceived propositions visible from `module' that had their\ntruth value locally modified (initialized, asserted, retracted).  Note, that this\nwill always include all locally conceived propositions.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allLocallyModifiedPropositions)), NULL);
      defineFunctionObject("VISIBLE-TERM?", "(DEFUN (VISIBLE-TERM? BOOLEAN) ((TERM LOGIC-OBJECT) (CONTEXT CONTEXT) (LOCAL? BOOLEAN)))", ((cpp_function_code)(&visibleTermP)), NULL);
      defineFunctionObject("ALL-UNNAMED-TERMS", "(DEFUN (ALL-UNNAMED-TERMS ITERATOR) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all unnamed terms visible from `module'.  A term can be\nan instance (or individual) as well as a description.  Only terms that\nhaven't been deleted will be considered.  If `local?', only return\nterms created locally in `module'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allUnnamedTerms)), NULL);
      defineFunctionObject("NAMED-TERM?", "(DEFUN (NAMED-TERM? BOOLEAN) ((TERM OBJECT) (ITER ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&namedTermP)), NULL);
      defineFunctionObject("ALL-NAMED-TERMS", "(DEFUN (ALL-NAMED-TERMS (ITERATOR OF OBJECT)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all named terms visible from `module'.  A term can be an\ninstance (or individual) as well as a description.  Only terms that\nhaven't been deleted will be considered.  If `local?', only return \nterms created locally in `module'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allNamedTerms)), NULL);
      defineFunctionObject("ALL-TERMS", "(DEFUN (ALL-TERMS (ITERATOR OF OBJECT)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Return a list of all terms visible from `module'.  A term can be an\ninstance (or individual) as well as a description.  Only terms that\nhaven't been deleted will be considered.  If `local?', only return \nterms created locally in `module'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allTerms)), NULL);
      defineFunctionObject("FILTER-INSTANCE?", "(DEFUN (FILTER-INSTANCE? BOOLEAN) ((SELF LOGIC-OBJECT) (ITERATOR ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&filterInstanceP)), NULL);
      defineFunctionObject("ALL-NAMED-INSTANCES", "(DEFUN (ALL-NAMED-INSTANCES (ITERATOR OF LOGIC-OBJECT)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all named instances (or individuals) visible from `module'.\nOnly instances that haven't been deleted will be considered.  If `local?',\nonly return instances created locally in `module'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allNamedInstances)), NULL);
      defineFunctionObject("ALL-INSTANCES", "(DEFUN (ALL-INSTANCES (ITERATOR OF LOGIC-OBJECT)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all instances (or individuals) visible from `module'.\nOnly instances that haven't been deleted will be considered.  If `local?',\nonly return instances created locally in `module'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allInstances)), NULL);
      defineFunctionObject("STRING-TO-LOGIC-OBJECT", "(DEFUN (STRING-TO-LOGIC-OBJECT LOGIC-OBJECT) ((STRING STRING)))", ((cpp_function_code)(((LogicObject*  (*) (const char*))(&stringToLogicObject)))), NULL);
      defineFunctionObject("STARTUP-API-SUPPORT", "(DEFUN STARTUP-API-SUPPORT () :PUBLIC? TRUE)", ((cpp_function_code)(&startupApiSupport)), NULL);
      { MethodSlot* function = lookupFunction(SYM_API_SUPPORT_LOGIC_STARTUP_API_SUPPORT);

        setDynamicSlotValue(function->dynamicSlots, SYM_API_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupApiSupport"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      oSTRING_TO_OBJECT_FUNCTIONSo->insertAt(SGT_API_SUPPORT_LOGIC_LOGIC_OBJECT, wrapFunctionCode(((cpp_function_code)(((LogicObject*  (*) (const char*))(&stringToLogicObject))))));
    }
  }
}

Surrogate* SGT_API_SUPPORT_LOGIC_TRUTH_VALUE = NULL;

Surrogate* SGT_API_SUPPORT_LOGIC_LOGIC_OBJECT = NULL;

Surrogate* SGT_API_SUPPORT_LOGIC_PATTERN_VARIABLE = NULL;

Surrogate* SGT_API_SUPPORT_LOGIC_SKOLEM = NULL;

Surrogate* SGT_API_SUPPORT_LOGIC_NAMED_DESCRIPTION = NULL;

Surrogate* SGT_API_SUPPORT_LOGIC_DESCRIPTION = NULL;

Surrogate* SGT_API_SUPPORT_STELLA_THING = NULL;

Symbol* SYM_API_SUPPORT_LOGIC_STARTUP_API_SUPPORT = NULL;

Symbol* SYM_API_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
