//  -*- Mode: C++ -*-

// inference-caches.cc

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

boolean worldStateP(Context* self) {
  if (subtypeOfP(safePrimaryType(self), SGT_INFERENCE_CACHES_STELLA_WORLD)) {
    { Context* self000 = self;
      World* self = ((World*)(self000));

      return ((!((boolean)(((Context*)(dynamicSlotValue(self->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_INFERENCE_CACHE_OF, NULL)))))) &&
          (!((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_MONOTONICp, FALSE_WRAPPER)))->wrapperValue));
    }
  }
  else {
    return (true);
  }
}

Context* getWorldState(Context* self) {
  return ((worldStateP(self) ? self : ((World*)(self))->baseModule));
}

World* lookupInferenceCache(Context* context, Keyword* kind) {
  { Context* cacheworld = NULL;

    if (kind == KWD_INFERENCE_CACHES_JUST_IN_TIME) {
      cacheworld = ((World*)(dynamicSlotValue(context->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_JUST_IN_TIME_INFERENCE_CACHE, NULL)));
    }
    else if (kind == KWD_INFERENCE_CACHES_META) {
      cacheworld = ((World*)(dynamicSlotValue(context->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_META_INFERENCE_CACHE, NULL)));
    }
    else if (kind == KWD_INFERENCE_CACHES_TMS) {
      cacheworld = ((World*)(dynamicSlotValue(context->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_TRUTH_MAINTAINED_INFERENCE_CACHE, NULL)));
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << kind << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    return (((World*)(cacheworld)));
  }
}

void initializeInferenceWorld(World* world) {
}

World* createInferenceCache(Context* context, Keyword* kind) {
  { World* world = createWorld((getQuotedTree("((:JUST-IN-TIME :TMS) \"/LOGIC\")", "/LOGIC")->memberP(kind) ? getInferenceCache(context, KWD_INFERENCE_CACHES_META) : context), NULL);

    if (kind == KWD_INFERENCE_CACHES_JUST_IN_TIME) {
      setDynamicSlotValue(context->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_JUST_IN_TIME_INFERENCE_CACHE, world, NULL);
    }
    else if (kind == KWD_INFERENCE_CACHES_META) {
      setDynamicSlotValue(context->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_META_INFERENCE_CACHE, world, NULL);
    }
    else if (kind == KWD_INFERENCE_CACHES_TMS) {
      setDynamicSlotValue(context->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_TRUTH_MAINTAINED_INFERENCE_CACHE, world, NULL);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << kind << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    setDynamicSlotValue(world->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_INFERENCE_CACHE_OF, context, NULL);
    initializeInferenceWorld(world);
    return (world);
  }
}

boolean justInTimeInferenceCacheP(Context* self) {
  // Return true if `self' is the JIT cache of some world state.
  if (subtypeOfP(safePrimaryType(self), SGT_INFERENCE_CACHES_STELLA_WORLD)) {
    { Context* self000 = self;
      World* self = ((World*)(self000));

      { Context* worldstate = ((Context*)(dynamicSlotValue(self->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_INFERENCE_CACHE_OF, NULL)));

        return (((boolean)(worldstate)) &&
            (((World*)(dynamicSlotValue(worldstate->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_JUST_IN_TIME_INFERENCE_CACHE, NULL))) == self));
      }
    }
  }
  else {
    return (false);
  }
}

boolean metaInferenceCacheP(Context* self) {
  // Return true if `self' is the meta-JIT cache of some world state.
  if (subtypeOfP(safePrimaryType(self), SGT_INFERENCE_CACHES_STELLA_WORLD)) {
    { Context* self000 = self;
      World* self = ((World*)(self000));

      { Context* worldstate = ((Context*)(dynamicSlotValue(self->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_INFERENCE_CACHE_OF, NULL)));

        return (((boolean)(worldstate)) &&
            (((World*)(dynamicSlotValue(worldstate->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_META_INFERENCE_CACHE, NULL))) == self));
      }
    }
  }
  else {
    return (false);
  }
}

World* getInferenceCache(Context* context, Keyword* kind) {
  if (!worldStateP(context)) {
    return (((World*)(context)));
  }
  { World* world = lookupInferenceCache(context, kind);

    if (((boolean)(world))) {
      return (world);
    }
    processCheckTypesAgenda();
    world = createInferenceCache(context, kind);
    if (kind == KWD_INFERENCE_CACHES_JUST_IN_TIME) {
    }
    else if ((kind == KWD_INFERENCE_CACHES_META) ||
        (kind == KWD_INFERENCE_CACHES_TMS)) {
      { Module* parentmodule = NULL;
        Cons* iter000 = context->baseModule->parentModules->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          parentmodule = ((Module*)(iter000->value));
          inheritCachedInferences(lookupInferenceCache(parentmodule, kind), world);
        }
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << kind << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    return (world);
  }
}

void destroyInferenceCache(Context* context, Keyword* kind) {
  { World* cache = NULL;

    if (kind == KWD_INFERENCE_CACHES_JUST_IN_TIME) {
      cache = ((World*)(dynamicSlotValue(context->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_JUST_IN_TIME_INFERENCE_CACHE, NULL)));
      setDynamicSlotValue(context->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_JUST_IN_TIME_INFERENCE_CACHE, NULL, NULL);
    }
    else if (kind == KWD_INFERENCE_CACHES_META) {
      cache = ((World*)(dynamicSlotValue(context->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_META_INFERENCE_CACHE, NULL)));
      setDynamicSlotValue(context->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_META_INFERENCE_CACHE, NULL, NULL);
    }
    else if (kind == KWD_INFERENCE_CACHES_TMS) {
      cache = ((World*)(dynamicSlotValue(context->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_TRUTH_MAINTAINED_INFERENCE_CACHE, NULL)));
      setDynamicSlotValue(context->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_TRUTH_MAINTAINED_INFERENCE_CACHE, NULL, NULL);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << kind << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    if (((boolean)(cache)) &&
        (!cache->deletedP())) {
      destroyWorld(cache);
    }
  }
}

void destroyAllInferenceCaches(Context* context, Keyword* kind) {
  destroyInferenceCache(context, kind);
  { Context* child = NULL;
    AllPurposeIterator* iter000 = allSubcontexts(oCONTEXTo, KWD_INFERENCE_CACHES_PREORDER);

    for (; iter000->nextP(); ) {
      child = ((Context*)(iter000->value));
      if (worldStateP(child)) {
        destroyInferenceCache(child, kind);
      }
    }
  }
}

void unlinkInferenceCache(World* self) {
  if (((boolean)(((Context*)(dynamicSlotValue(self->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_INFERENCE_CACHE_OF, NULL)))))) {
    { Context* worldstate = ((Context*)(dynamicSlotValue(self->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_INFERENCE_CACHE_OF, NULL)));

      if (self == ((World*)(dynamicSlotValue(worldstate->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_JUST_IN_TIME_INFERENCE_CACHE, NULL)))) {
        setDynamicSlotValue(worldstate->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_JUST_IN_TIME_INFERENCE_CACHE, NULL, NULL);
      }
      else if (self == ((World*)(dynamicSlotValue(worldstate->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_META_INFERENCE_CACHE, NULL)))) {
        setDynamicSlotValue(worldstate->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_META_INFERENCE_CACHE, NULL, NULL);
      }
      else if (self == ((World*)(dynamicSlotValue(worldstate->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_TRUTH_MAINTAINED_INFERENCE_CACHE, NULL)))) {
        setDynamicSlotValue(worldstate->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_TRUTH_MAINTAINED_INFERENCE_CACHE, NULL, NULL);
      }
      setDynamicSlotValue(self->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_INFERENCE_CACHE_OF, NULL, NULL);
    }
  }
}

void destroyInferenceCaches(Context* context) {
  destroyInferenceCache(context, KWD_INFERENCE_CACHES_JUST_IN_TIME);
  destroyInferenceCache(context, KWD_INFERENCE_CACHES_META);
  destroyInferenceCache(context, KWD_INFERENCE_CACHES_TMS);
}

// Used to signal an assertion that doesn't
// blow away inference caches.
DEFINE_STELLA_SPECIAL(oINVISIBLEASSERTIONpo, boolean , false);

boolean metaPropositionP(Proposition* proposition) {
  // Return TRUE if 'proposition' is tied only to at least one meta object
  // and no other objects except literals or function terms that are itself meta objects.
  if (!((boolean)(proposition))) {
    return (false);
  }
  { Vector* arguments = proposition->arguments;
    boolean pointstometaobjectP = false;

    { Object* arg = NULL;
      Vector* vector000 = arguments;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = (vector000->theArray)[index000];
        { Surrogate* testValue000 = safePrimaryType(arg);

          if (subtypeOfP(testValue000, SGT_INFERENCE_CACHES_LOGIC_DESCRIPTION)) {
            { Object* arg000 = arg;
              Description* arg = ((Description*)(arg000));

              pointstometaobjectP = true;
            }
          }
          else if (subtypeOfP(testValue000, SGT_INFERENCE_CACHES_STELLA_LITERAL_WRAPPER)) {
            { Object* arg001 = arg;
              LiteralWrapper* arg = ((LiteralWrapper*)(arg001));

            }
          }
          else if (subtypeOfP(testValue000, SGT_INFERENCE_CACHES_LOGIC_SKOLEM)) {
            { Object* arg002 = arg;
              Skolem* arg = ((Skolem*)(arg002));

              if ((arg == arguments->last()) &&
                  (proposition->kind == KWD_INFERENCE_CACHES_FUNCTION)) {
              }
              else if (((boolean)(arg->definingProposition)) &&
                  metaPropositionP(arg->definingProposition)) {
                pointstometaobjectP = true;
              }
              else {
                return (false);
              }
            }
          }
          else {
            return (false);
          }
        }
      }
    }
    return (pointstometaobjectP);
  }
}

void handleOutOfDateInferenceCache(Keyword* assertorretract, Proposition* proposition) {
  if (worldStateP(oCONTEXTo)) {
    if ((!((boolean)(lookupInferenceCache(oCONTEXTo, KWD_INFERENCE_CACHES_META)))) ||
        (((boolean)(oQUERYITERATORo)) ||
         (descriptionModeP() ||
          oINVISIBLEASSERTIONpo))) {
      return;
    }
    { NamedDescription* description = (((boolean)(proposition)) ? getDescription(((Surrogate*)(proposition->operatoR))) : ((NamedDescription*)(NULL)));

      if (((boolean)(description)) &&
          testPropertyP(description, SGT_INFERENCE_CACHES_PL_KERNEL_KB_HIDDEN_RELATION)) {
        return;
      }
    }
    if (metaPropositionP(proposition) &&
        ((assertorretract == KWD_INFERENCE_CACHES_RETRACT) &&
         (!((BooleanWrapper*)(dynamicSlotValue(lookupInferenceCache(oCONTEXTo, KWD_INFERENCE_CACHES_META)->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_TRUTH_MAINTAINEDp, FALSE_WRAPPER)))->wrapperValue))) {
      if (((boolean)(oTRACED_KEYWORDSo)) &&
          oTRACED_KEYWORDSo->membP(KWD_INFERENCE_CACHES_PERFORMANCE_CLUES)) {
        std::cout << "DELETING META CACHE" << std::endl;
      }
      destroyInferenceCache(oCONTEXTo, KWD_INFERENCE_CACHES_META);
    }
    else if (oJUST_IN_TIME_FORWARD_INFERENCEpo) {
      if (((boolean)(((World*)(dynamicSlotValue(oCONTEXTo->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_JUST_IN_TIME_INFERENCE_CACHE, NULL)))))) {
        if (((boolean)(oTRACED_KEYWORDSo)) &&
            oTRACED_KEYWORDSo->membP(KWD_INFERENCE_CACHES_PERFORMANCE_CLUES)) {
          std::cout << "DELETING JIT CACHE" << std::endl;
        }
        destroyAllInferenceCaches(oCONTEXTo, KWD_INFERENCE_CACHES_JUST_IN_TIME);
      }
    }
    else {
      { World* cache = lookupInferenceCache(oCONTEXTo, KWD_INFERENCE_CACHES_TMS);

        if (((boolean)(cache)) &&
            (!((BooleanWrapper*)(dynamicSlotValue(cache->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_TRUTH_MAINTAINEDp, FALSE_WRAPPER)))->wrapperValue)) {
          destroyInferenceCache(oCONTEXTo, KWD_INFERENCE_CACHES_TMS);
        }
      }
    }
    return;
  }
  { World* world = ((World*)(oCONTEXTo));

    if (((BooleanWrapper*)(dynamicSlotValue(world->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_MONOTONICp, FALSE_WRAPPER)))->wrapperValue &&
        (assertorretract == KWD_INFERENCE_CACHES_RETRACT)) {
      if (((boolean)(proposition))) {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "Retraction of " << "`" << proposition << "'" << " occurred in world " << "`" << world << "'" << " which is marked monotonic." << std::endl;
      }
      else {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "Retraction occurred in world " << "`" << world << "'" << " which is marked monotonic." << std::endl;
      }
    }
    if (!((BooleanWrapper*)(dynamicSlotValue(world->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_TRUTH_MAINTAINEDp, FALSE_WRAPPER)))->wrapperValue) {
      setDynamicSlotValue(world->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_UP_TO_DATE_INFERENCESp, FALSE_WRAPPER, FALSE_WRAPPER);
    }
  }
}

World* bestInferenceCache(Context* context) {
  if (oJUST_IN_TIME_FORWARD_INFERENCEpo) {
    return (getInferenceCache(context, KWD_INFERENCE_CACHES_JUST_IN_TIME));
  }
  { World* cache = lookupInferenceCache(context, KWD_INFERENCE_CACHES_TMS);

    if (((boolean)(cache))) {
      return (cache);
    }
    else {
      return (lookupInferenceCache(context, KWD_INFERENCE_CACHES_META));
    }
  }
}

Context* getQueryContext() {
  if (!worldStateP(oCONTEXTo)) {
    return (oCONTEXTo);
  }
  { World* cache = bestInferenceCache(oCONTEXTo);

    return ((((boolean)(cache)) ? cache : oCONTEXTo));
  }
}

Context* getPropertyTestContext() {
  { World* constraintpropagationworld = lookupConstraintPropagationWorld(oCONTEXTo);

    if (!((boolean)(constraintpropagationworld))) {
      return (oCONTEXTo);
    }
    else {
      return (constraintpropagationworld);
    }
  }
}

Context* getInferableTestContext() {
  if (!worldStateP(oCONTEXTo)) {
    return (oCONTEXTo);
  }
  else {
    { World* temp000 = lookupInferenceCache(oCONTEXTo, KWD_INFERENCE_CACHES_META);

      { Context* value000 = (((boolean)(temp000)) ? temp000 : oCONTEXTo);

        return (value000);
      }
    }
  }
}

Context* getTopLevelUpdateContext() {
  return (getWorldState(oCONTEXTo));
}

World* lookupConstraintPropagationWorld(Context* self) {
  if (worldStateP(self)) {
    if (oJUST_IN_TIME_FORWARD_INFERENCEpo) {
      if (((boolean)(oQUERYITERATORo))) {
        return (getInferenceCache(self, KWD_INFERENCE_CACHES_JUST_IN_TIME));
      }
      else {
        return (lookupInferenceCache(self, KWD_INFERENCE_CACHES_JUST_IN_TIME));
      }
    }
    else {
      return (lookupInferenceCache(self, KWD_INFERENCE_CACHES_TMS));
    }
  }
  else {
    return (((World*)(self)));
  }
}

void inheritCachedInferences(World* fromworld, World* toworld) {
  toworld = toworld;
  if (!((boolean)(fromworld))) {
    return;
  }
}

void inheritTruthValueUpdate(Proposition* proposition, World* toworld) {
}

void inheritVariableValueUpdate(Skolem* skolem, World* toworld) {
}

void callPropagateConstraints(Context* context) {
  // OBSOLETE: use `call-run-forward-rules' instead.
  callRunForwardRules(context, true, false);
}

void propagateConstraints(Cons* name) {
  // OBSOLETE: use `run-forward-rules' instead.
  { Cons* optionalname = name;
    Module* module = NULL;

    if (((boolean)(optionalname->value))) {
      module = coerceToModule(optionalname->value, true);
    }
    if (!((boolean)(module))) {
      module = oMODULEo;
    }
    callRunForwardRules(module, true, false);
  }
}

void propagateConstraintsEvaluatorWrapper(Cons* arguments) {
  propagateConstraints(arguments);
}

void repropagateConstraints(Cons* name) {
  // OBSOLETE: use `run-forward-rules' instead.
  { Cons* optionalname = name;
    Module* context = coerceToModule(optionalname->value, true);

    if (!((boolean)(context))) {
      context = ((Module*)(oCONTEXTo));
    }
    callRunForwardRules(context, true, true);
  }
}

void repropagateConstraintsEvaluatorWrapper(Cons* arguments) {
  repropagateConstraints(arguments);
}

void callRunForwardRules(Context* context, boolean localP, boolean forceP) {
  // Callable implementation for `run-forward-rules' (which see).
  if (!((boolean)(context))) {
    context = oCONTEXTo;
  }
  finalizeObjects();
  processCheckTypesAgenda();
  { Context* worldstate = getWorldState(context);
    World* propworld = NULL;
    PropagationEnvironment* propenv = NULL;

    if (forceP) {
      destroyInferenceCaches(getWorldState(context));
    }
    getInferenceCache(worldstate, KWD_INFERENCE_CACHES_JUST_IN_TIME);
    propworld = bestInferenceCache(worldstate);
    propenv = getPropagationEnvironment(propworld);
    { 
      BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_INFERENCE_CACHES_EXTENSIONAL_ASSERTION);
      BIND_STELLA_SPECIAL(oINHIBITOBJECTFINALIZATIONpo, boolean, true);
      BIND_STELLA_SPECIAL(oQUERYITERATORo, QueryIterator*, NULL);
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, propworld);
      if (((BooleanWrapper*)(dynamicSlotValue(propworld->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_UP_TO_DATE_INFERENCESp, FALSE_WRAPPER)))->wrapperValue) {
        return;
      }
      try {
        { 
          BIND_STELLA_SPECIAL(oFILLINGCONSTRAINTPROPAGATIONQUEUESpo, boolean, true);
          BIND_STELLA_SPECIAL(oDEFERINGDEFAULTFORWARDINFERENCESpo, boolean, true);
          { Proposition* prop = NULL;
            Iterator* iter000 = allPropositions(((Module*)(worldstate)), localP);

            for (; iter000->nextP(); ) {
              prop = ((Proposition*)(iter000->value));
              if ((!prop->deletedP()) &&
                  ((oREVERSEPOLARITYpo ? falseP(prop) : (trueP(prop) ||
                  functionWithDefinedValueP(prop))))) {
                reactToKbUpdate(propworld, prop);
                { Object* arg = NULL;
                  Vector* vector000 = prop->arguments;
                  int index000 = 0;
                  int length000 = vector000->length();

                  for  (; index000 < length000; 
                        index000 = index000 + 1) {
                    arg = (vector000->theArray)[index000];
                    if (isaP(arg, SGT_INFERENCE_CACHES_LOGIC_LOGIC_OBJECT) &&
                        (!propenv->elaboratedObjects->memberP(arg))) {
                      propenv->elaboratedObjects->insert(arg);
                    }
                  }
                }
              }
            }
          }
          executeConstraintPropagationQueues();
          { Proposition* prop = NULL;
            Cons* iter001 = propenv->deferredDefaultPropositions->theConsList;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              prop = ((Proposition*)(iter001->value));
              assignTruthValue(prop, DEFAULT_TRUE_TRUTH_VALUE);
              { Object* arg = NULL;
                Vector* vector001 = prop->arguments;
                int index001 = 0;
                int length001 = vector001->length();

                for  (; index001 < length001; 
                      index001 = index001 + 1) {
                  arg = (vector001->theArray)[index001];
                  if (isaP(arg, SGT_INFERENCE_CACHES_LOGIC_LOGIC_OBJECT) &&
                      (!propenv->elaboratedObjects->memberP(arg))) {
                    propenv->elaboratedObjects->insert(arg);
                  }
                }
              }
            }
          }
          propenv->deferredDefaultPropositions->clear();
          oDEFERINGDEFAULTFORWARDINFERENCESpo = false;
          executeConstraintPropagationQueues();
        }
      }
      catch (Clash& _e) {
        Clash* e = &_e;

        { ExceptionRecord* self000 = newExceptionRecord();

          self000->exception = e;
          self000->context = oCONTEXTo;
          self000->module = oMODULEo;
          oCLASH_EXCEPTIONSo->push(self000);
        }
        *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
        std::cout << "   One or more facts need to be retracted to eliminate the inconsistency." << std::endl;
      }
      setDynamicSlotValue(propworld->dynamicSlots, SYM_INFERENCE_CACHES_LOGIC_UP_TO_DATE_INFERENCESp, TRUE_WRAPPER, FALSE_WRAPPER);
    }
  }
}

void runForwardRules(Cons* options) {
  // Run forward inference rules in the module defined by the :module option (which
  // defaults to the current module).  If forward inferencing is already up-to-date
  // in the designated module, no additional inferencing will occur, unless the :force?
  // option is specified as TRUE, in which case all forward rules are run or rerun (for
  // backwards compatibility, this command also supports the old <module> :force arguments
  // specified with a non-standard keyword notation).  If :local? is TRUE (the default),
  // only propositions asserted locally in the module will be posted for forward inference,
  // otherwise, all true propositions visible in the module will be posted.
  // 
  // Calling `run-forward-rules' with :disable-jit? TRUE will disable future just-in-time
  // forward inference which will preserve cached forward inference in case of monotonic
  // assertions that do not clip (implicitly retract) any existing values.  Subsequent calls
  // can then trigger new inferences based on these updates only.  If the JIT stays enabled,
  // even monotonic updates will throw away the JIT cache.  Also, once any retractions have
  // been performed, all cached inferences will be thrown away and forward inference has to
  // be rerun from scratch or just-in-time forward inference needs to be enabled again.
  { Cons* optionslist = options;
    PropertyList* theoptions = parseOptions((keywordP(optionslist->value) ? optionslist : consList(4, KWD_INFERENCE_CACHES_MODULE, optionslist->value, KWD_INFERENCE_CACHES_FORCEp, ((optionslist->rest->value == KWD_INFERENCE_CACHES_FORCE) ? TRUE_WRAPPER : FALSE_WRAPPER))), listO(9, KWD_INFERENCE_CACHES_MODULE, SGT_INFERENCE_CACHES_STELLA_MODULE, KWD_INFERENCE_CACHES_LOCALp, SGT_INFERENCE_CACHES_STELLA_BOOLEAN, KWD_INFERENCE_CACHES_FORCEp, SGT_INFERENCE_CACHES_STELLA_BOOLEAN, KWD_INFERENCE_CACHES_DISABLE_JITp, SGT_INFERENCE_CACHES_STELLA_BOOLEAN, NIL), true, false);
    Module* themodule = ((Module*)(theoptions->lookupWithDefault(KWD_INFERENCE_CACHES_MODULE, oMODULEo)));
    boolean localP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_INFERENCE_CACHES_LOCALp, TRUE_WRAPPER))));
    boolean forceP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_INFERENCE_CACHES_FORCEp, FALSE_WRAPPER))));
    boolean disablejitP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_INFERENCE_CACHES_DISABLE_JITp, FALSE_WRAPPER))));

    if (oJUST_IN_TIME_FORWARD_INFERENCEpo &&
        disablejitP) {
      unsetPowerloomFeature(KWD_INFERENCE_CACHES_JUST_IN_TIME_INFERENCE);
      std::cout << "Disabled just-in-time forward inference" << std::endl;
    }
    callRunForwardRules(themodule, localP, forceP);
  }
}

void runForwardRulesEvaluatorWrapper(Cons* arguments) {
  runForwardRules(arguments);
}

void helpStartupInferenceCaches1() {
  {
    SGT_INFERENCE_CACHES_STELLA_WORLD = ((Surrogate*)(internRigidSymbolWrtModule("WORLD", getStellaModule("/STELLA", true), 1)));
    SYM_INFERENCE_CACHES_LOGIC_INFERENCE_CACHE_OF = ((Symbol*)(internRigidSymbolWrtModule("INFERENCE-CACHE-OF", NULL, 0)));
    SYM_INFERENCE_CACHES_LOGIC_MONOTONICp = ((Symbol*)(internRigidSymbolWrtModule("MONOTONIC?", NULL, 0)));
    KWD_INFERENCE_CACHES_JUST_IN_TIME = ((Keyword*)(internRigidSymbolWrtModule("JUST-IN-TIME", NULL, 2)));
    SYM_INFERENCE_CACHES_LOGIC_JUST_IN_TIME_INFERENCE_CACHE = ((Symbol*)(internRigidSymbolWrtModule("JUST-IN-TIME-INFERENCE-CACHE", NULL, 0)));
    KWD_INFERENCE_CACHES_META = ((Keyword*)(internRigidSymbolWrtModule("META", NULL, 2)));
    SYM_INFERENCE_CACHES_LOGIC_META_INFERENCE_CACHE = ((Symbol*)(internRigidSymbolWrtModule("META-INFERENCE-CACHE", NULL, 0)));
    KWD_INFERENCE_CACHES_TMS = ((Keyword*)(internRigidSymbolWrtModule("TMS", NULL, 2)));
    SYM_INFERENCE_CACHES_LOGIC_TRUTH_MAINTAINED_INFERENCE_CACHE = ((Symbol*)(internRigidSymbolWrtModule("TRUTH-MAINTAINED-INFERENCE-CACHE", NULL, 0)));
    KWD_INFERENCE_CACHES_PREORDER = ((Keyword*)(internRigidSymbolWrtModule("PREORDER", NULL, 2)));
    SGT_INFERENCE_CACHES_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 1)));
    SGT_INFERENCE_CACHES_STELLA_LITERAL_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_INFERENCE_CACHES_LOGIC_SKOLEM = ((Surrogate*)(internRigidSymbolWrtModule("SKOLEM", NULL, 1)));
    KWD_INFERENCE_CACHES_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SGT_INFERENCE_CACHES_PL_KERNEL_KB_HIDDEN_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("HIDDEN-RELATION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_INFERENCE_CACHES_RETRACT = ((Keyword*)(internRigidSymbolWrtModule("RETRACT", NULL, 2)));
    SYM_INFERENCE_CACHES_LOGIC_TRUTH_MAINTAINEDp = ((Symbol*)(internRigidSymbolWrtModule("TRUTH-MAINTAINED?", NULL, 0)));
    KWD_INFERENCE_CACHES_PERFORMANCE_CLUES = ((Keyword*)(internRigidSymbolWrtModule("PERFORMANCE-CLUES", NULL, 2)));
    SYM_INFERENCE_CACHES_LOGIC_UP_TO_DATE_INFERENCESp = ((Symbol*)(internRigidSymbolWrtModule("UP-TO-DATE-INFERENCES?", NULL, 0)));
    KWD_INFERENCE_CACHES_EXTENSIONAL_ASSERTION = ((Keyword*)(internRigidSymbolWrtModule("EXTENSIONAL-ASSERTION", NULL, 2)));
    SGT_INFERENCE_CACHES_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", NULL, 1)));
    KWD_INFERENCE_CACHES_MODULE = ((Keyword*)(internRigidSymbolWrtModule("MODULE", NULL, 2)));
    KWD_INFERENCE_CACHES_FORCEp = ((Keyword*)(internRigidSymbolWrtModule("FORCE?", NULL, 2)));
    KWD_INFERENCE_CACHES_FORCE = ((Keyword*)(internRigidSymbolWrtModule("FORCE", NULL, 2)));
    SGT_INFERENCE_CACHES_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", getStellaModule("/STELLA", true), 1)));
    KWD_INFERENCE_CACHES_LOCALp = ((Keyword*)(internRigidSymbolWrtModule("LOCAL?", NULL, 2)));
    SGT_INFERENCE_CACHES_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", getStellaModule("/STELLA", true), 1)));
    KWD_INFERENCE_CACHES_DISABLE_JITp = ((Keyword*)(internRigidSymbolWrtModule("DISABLE-JIT?", NULL, 2)));
    KWD_INFERENCE_CACHES_JUST_IN_TIME_INFERENCE = ((Keyword*)(internRigidSymbolWrtModule("JUST-IN-TIME-INFERENCE", NULL, 2)));
    SYM_INFERENCE_CACHES_LOGIC_STARTUP_INFERENCE_CACHES = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-INFERENCE-CACHES", NULL, 0)));
    SYM_INFERENCE_CACHES_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void startupInferenceCaches() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupInferenceCaches1();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("WORLD-STATE?", "(DEFUN (WORLD-STATE? BOOLEAN) ((SELF CONTEXT)) :PUBLIC? TRUE)", ((cpp_function_code)(&worldStateP)), NULL);
      defineFunctionObject("GET-WORLD-STATE", "(DEFUN (GET-WORLD-STATE CONTEXT) ((SELF CONTEXT)) :PUBLIC? TRUE)", ((cpp_function_code)(&getWorldState)), NULL);
      defineExternalSlotFromStringifiedSource("(DEFSLOT CONTEXT META-INFERENCE-CACHE :TYPE WORLD :ALLOCATION :DYNAMIC)");
      defineExternalSlotFromStringifiedSource("(DEFSLOT CONTEXT TRUTH-MAINTAINED-INFERENCE-CACHE :TYPE WORLD :ALLOCATION :DYNAMIC)");
      defineExternalSlotFromStringifiedSource("(DEFSLOT CONTEXT JUST-IN-TIME-INFERENCE-CACHE :TYPE WORLD :ALLOCATION :DYNAMIC)");
      defineExternalSlotFromStringifiedSource("(DEFSLOT WORLD INFERENCE-CACHE-OF :TYPE CONTEXT :PUBLIC? TRUE :ALLOCATION :DYNAMIC)");
      defineFunctionObject("LOOKUP-INFERENCE-CACHE", "(DEFUN (LOOKUP-INFERENCE-CACHE WORLD) ((CONTEXT CONTEXT) (KIND KEYWORD)) :PUBLIC? TRUE)", ((cpp_function_code)(&lookupInferenceCache)), NULL);
      defineFunctionObject("INITIALIZE-INFERENCE-WORLD", "(DEFUN INITIALIZE-INFERENCE-WORLD ((WORLD WORLD)))", ((cpp_function_code)(&initializeInferenceWorld)), NULL);
      defineFunctionObject("CREATE-INFERENCE-CACHE", "(DEFUN (CREATE-INFERENCE-CACHE WORLD) ((CONTEXT CONTEXT) (KIND KEYWORD)) :PUBLIC? TRUE)", ((cpp_function_code)(&createInferenceCache)), NULL);
      defineFunctionObject("JUST-IN-TIME-INFERENCE-CACHE?", "(DEFUN (JUST-IN-TIME-INFERENCE-CACHE? BOOLEAN) ((SELF CONTEXT)) :DOCUMENTATION \"Return true if `self' is the JIT cache of some world state.\" :PUBLIC? TRUE)", ((cpp_function_code)(&justInTimeInferenceCacheP)), NULL);
      defineFunctionObject("META-INFERENCE-CACHE?", "(DEFUN (META-INFERENCE-CACHE? BOOLEAN) ((SELF CONTEXT)) :DOCUMENTATION \"Return true if `self' is the meta-JIT cache of some world state.\" :PUBLIC? TRUE)", ((cpp_function_code)(&metaInferenceCacheP)), NULL);
      defineFunctionObject("GET-INFERENCE-CACHE", "(DEFUN (GET-INFERENCE-CACHE WORLD) ((CONTEXT CONTEXT) (KIND KEYWORD)) :PUBLIC? TRUE)", ((cpp_function_code)(&getInferenceCache)), NULL);
      defineFunctionObject("DESTROY-INFERENCE-CACHE", "(DEFUN DESTROY-INFERENCE-CACHE ((CONTEXT CONTEXT) (KIND KEYWORD)) :PUBLIC? TRUE)", ((cpp_function_code)(&destroyInferenceCache)), NULL);
      defineFunctionObject("DESTROY-ALL-INFERENCE-CACHES", "(DEFUN DESTROY-ALL-INFERENCE-CACHES ((CONTEXT CONTEXT) (KIND KEYWORD)) :PUBLIC? TRUE)", ((cpp_function_code)(&destroyAllInferenceCaches)), NULL);
      defineFunctionObject("UNLINK-INFERENCE-CACHE", "(DEFUN UNLINK-INFERENCE-CACHE ((SELF WORLD)))", ((cpp_function_code)(&unlinkInferenceCache)), NULL);
      defineFunctionObject("DESTROY-INFERENCE-CACHES", "(DEFUN DESTROY-INFERENCE-CACHES ((CONTEXT CONTEXT)) :PUBLIC? TRUE)", ((cpp_function_code)(&destroyInferenceCaches)), NULL);
      defineFunctionObject("META-PROPOSITION?", "(DEFUN (META-PROPOSITION? BOOLEAN) ((PROPOSITION PROPOSITION)) :DOCUMENTATION \"Return TRUE if 'proposition' is tied only to at least one meta object\nand no other objects except literals or function terms that are itself meta objects.\" :PUBLIC? TRUE)", ((cpp_function_code)(&metaPropositionP)), NULL);
      defineFunctionObject("HANDLE-OUT-OF-DATE-INFERENCE-CACHE", "(DEFUN HANDLE-OUT-OF-DATE-INFERENCE-CACHE ((ASSERTORRETRACT KEYWORD) (PROPOSITION PROPOSITION)))", ((cpp_function_code)(&handleOutOfDateInferenceCache)), NULL);
      defineFunctionObject("BEST-INFERENCE-CACHE", "(DEFUN (BEST-INFERENCE-CACHE WORLD) ((CONTEXT CONTEXT)))", ((cpp_function_code)(&bestInferenceCache)), NULL);
      defineFunctionObject("GET-QUERY-CONTEXT", "(DEFUN (GET-QUERY-CONTEXT CONTEXT) () :PUBLIC? TRUE)", ((cpp_function_code)(&getQueryContext)), NULL);
      defineFunctionObject("GET-PROPERTY-TEST-CONTEXT", "(DEFUN (GET-PROPERTY-TEST-CONTEXT CONTEXT) ())", ((cpp_function_code)(&getPropertyTestContext)), NULL);
      defineFunctionObject("GET-INFERABLE-TEST-CONTEXT", "(DEFUN (GET-INFERABLE-TEST-CONTEXT CONTEXT) ())", ((cpp_function_code)(&getInferableTestContext)), NULL);
      defineFunctionObject("GET-TOP-LEVEL-UPDATE-CONTEXT", "(DEFUN (GET-TOP-LEVEL-UPDATE-CONTEXT CONTEXT) ())", ((cpp_function_code)(&getTopLevelUpdateContext)), NULL);
      defineFunctionObject("LOOKUP-CONSTRAINT-PROPAGATION-WORLD", "(DEFUN (LOOKUP-CONSTRAINT-PROPAGATION-WORLD WORLD) ((SELF CONTEXT)))", ((cpp_function_code)(&lookupConstraintPropagationWorld)), NULL);
      defineFunctionObject("INHERIT-CACHED-INFERENCES", "(DEFUN INHERIT-CACHED-INFERENCES ((FROMWORLD WORLD) (TOWORLD WORLD)))", ((cpp_function_code)(&inheritCachedInferences)), NULL);
      defineFunctionObject("INHERIT-TRUTH-VALUE-UPDATE", "(DEFUN INHERIT-TRUTH-VALUE-UPDATE ((PROPOSITION PROPOSITION) (TOWORLD WORLD)))", ((cpp_function_code)(&inheritTruthValueUpdate)), NULL);
      defineFunctionObject("INHERIT-VARIABLE-VALUE-UPDATE", "(DEFUN INHERIT-VARIABLE-VALUE-UPDATE ((SKOLEM SKOLEM) (TOWORLD WORLD)))", ((cpp_function_code)(&inheritVariableValueUpdate)), NULL);
      defineFunctionObject("CALL-PROPAGATE-CONSTRAINTS", "(DEFUN CALL-PROPAGATE-CONSTRAINTS ((CONTEXT CONTEXT)) :DOCUMENTATION \"OBSOLETE: use `call-run-forward-rules' instead.\")", ((cpp_function_code)(&callPropagateConstraints)), NULL);
      defineFunctionObject("PROPAGATE-CONSTRAINTS", "(DEFUN PROPAGATE-CONSTRAINTS (|&REST| (NAME NAME)) :DOCUMENTATION \"OBSOLETE: use `run-forward-rules' instead.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&propagateConstraints)), ((cpp_function_code)(&propagateConstraintsEvaluatorWrapper)));
      defineFunctionObject("REPROPAGATE-CONSTRAINTS", "(DEFUN REPROPAGATE-CONSTRAINTS (|&REST| (NAME NAME)) :DOCUMENTATION \"OBSOLETE: use `run-forward-rules' instead.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&repropagateConstraints)), ((cpp_function_code)(&repropagateConstraintsEvaluatorWrapper)));
      defineFunctionObject("CALL-RUN-FORWARD-RULES", "(DEFUN CALL-RUN-FORWARD-RULES ((CONTEXT CONTEXT) (LOCAL? BOOLEAN) (FORCE? BOOLEAN)) :DOCUMENTATION \"Callable implementation for `run-forward-rules' (which see).\" :PUBLIC? TRUE)", ((cpp_function_code)(&callRunForwardRules)), NULL);
      defineFunctionObject("RUN-FORWARD-RULES", "(DEFUN RUN-FORWARD-RULES (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Run forward inference rules in the module defined by the :module option (which\ndefaults to the current module).  If forward inferencing is already up-to-date\nin the designated module, no additional inferencing will occur, unless the :force?\noption is specified as TRUE, in which case all forward rules are run or rerun (for\nbackwards compatibility, this command also supports the old <module> :force arguments\nspecified with a non-standard keyword notation).  If :local? is TRUE (the default),\nonly propositions asserted locally in the module will be posted for forward inference,\notherwise, all true propositions visible in the module will be posted.\n\nCalling `run-forward-rules' with :disable-jit? TRUE will disable future just-in-time\nforward inference which will preserve cached forward inference in case of monotonic\nassertions that do not clip (implicitly retract) any existing values.  Subsequent calls\ncan then trigger new inferences " "based on these updates only.  If the JIT stays enabled,\neven monotonic updates will throw away the JIT cache.  Also, once any retractions have\nbeen performed, all cached inferences will be thrown away and forward inference has to\nbe rerun from scratch or just-in-time forward inference needs to be enabled again.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&runForwardRules)), ((cpp_function_code)(&runForwardRulesEvaluatorWrapper)));
      defineFunctionObject("STARTUP-INFERENCE-CACHES", "(DEFUN STARTUP-INFERENCE-CACHES () :PUBLIC? TRUE)", ((cpp_function_code)(&startupInferenceCaches)), NULL);
      { MethodSlot* function = lookupFunction(SYM_INFERENCE_CACHES_LOGIC_STARTUP_INFERENCE_CACHES);

        setDynamicSlotValue(function->dynamicSlots, SYM_INFERENCE_CACHES_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupInferenceCaches"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFSPECIAL *INVISIBLEASSERTION?* BOOLEAN FALSE :DOCUMENTATION \"Used to signal an assertion that doesn't\nblow away inference caches.\")", &oINVISIBLEASSERTIONpo);
    }
  }
}

Surrogate* SGT_INFERENCE_CACHES_STELLA_WORLD = NULL;

Symbol* SYM_INFERENCE_CACHES_LOGIC_INFERENCE_CACHE_OF = NULL;

Symbol* SYM_INFERENCE_CACHES_LOGIC_MONOTONICp = NULL;

Keyword* KWD_INFERENCE_CACHES_JUST_IN_TIME = NULL;

Symbol* SYM_INFERENCE_CACHES_LOGIC_JUST_IN_TIME_INFERENCE_CACHE = NULL;

Keyword* KWD_INFERENCE_CACHES_META = NULL;

Symbol* SYM_INFERENCE_CACHES_LOGIC_META_INFERENCE_CACHE = NULL;

Keyword* KWD_INFERENCE_CACHES_TMS = NULL;

Symbol* SYM_INFERENCE_CACHES_LOGIC_TRUTH_MAINTAINED_INFERENCE_CACHE = NULL;

Keyword* KWD_INFERENCE_CACHES_PREORDER = NULL;

Surrogate* SGT_INFERENCE_CACHES_LOGIC_DESCRIPTION = NULL;

Surrogate* SGT_INFERENCE_CACHES_STELLA_LITERAL_WRAPPER = NULL;

Surrogate* SGT_INFERENCE_CACHES_LOGIC_SKOLEM = NULL;

Keyword* KWD_INFERENCE_CACHES_FUNCTION = NULL;

Surrogate* SGT_INFERENCE_CACHES_PL_KERNEL_KB_HIDDEN_RELATION = NULL;

Keyword* KWD_INFERENCE_CACHES_RETRACT = NULL;

Symbol* SYM_INFERENCE_CACHES_LOGIC_TRUTH_MAINTAINEDp = NULL;

Keyword* KWD_INFERENCE_CACHES_PERFORMANCE_CLUES = NULL;

Symbol* SYM_INFERENCE_CACHES_LOGIC_UP_TO_DATE_INFERENCESp = NULL;

Keyword* KWD_INFERENCE_CACHES_EXTENSIONAL_ASSERTION = NULL;

Surrogate* SGT_INFERENCE_CACHES_LOGIC_LOGIC_OBJECT = NULL;

Keyword* KWD_INFERENCE_CACHES_MODULE = NULL;

Keyword* KWD_INFERENCE_CACHES_FORCEp = NULL;

Keyword* KWD_INFERENCE_CACHES_FORCE = NULL;

Surrogate* SGT_INFERENCE_CACHES_STELLA_MODULE = NULL;

Keyword* KWD_INFERENCE_CACHES_LOCALp = NULL;

Surrogate* SGT_INFERENCE_CACHES_STELLA_BOOLEAN = NULL;

Keyword* KWD_INFERENCE_CACHES_DISABLE_JITp = NULL;

Keyword* KWD_INFERENCE_CACHES_JUST_IN_TIME_INFERENCE = NULL;

Symbol* SYM_INFERENCE_CACHES_LOGIC_STARTUP_INFERENCE_CACHES = NULL;

Symbol* SYM_INFERENCE_CACHES_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
