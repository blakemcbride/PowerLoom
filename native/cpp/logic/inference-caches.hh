//  -*- Mode: C++ -*-

// inference-caches.hh

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



namespace logic {
  using namespace stella;

// Global declarations:
extern DECLARE_STELLA_SPECIAL(oINVISIBLEASSERTIONpo, boolean );

// Function signatures:
boolean worldStateP(Context* self);
Context* getWorldState(Context* self);
World* lookupInferenceCache(Context* context, Keyword* kind);
void initializeInferenceWorld(World* world);
World* createInferenceCache(Context* context, Keyword* kind);
boolean justInTimeInferenceCacheP(Context* self);
boolean metaInferenceCacheP(Context* self);
World* getInferenceCache(Context* context, Keyword* kind);
void destroyInferenceCache(Context* context, Keyword* kind);
void destroyAllInferenceCaches(Context* context, Keyword* kind);
void unlinkInferenceCache(World* self);
void destroyInferenceCaches(Context* context);
boolean metaPropositionP(Proposition* proposition);
void handleOutOfDateInferenceCache(Keyword* assertorretract, Proposition* proposition);
World* bestInferenceCache(Context* context);
Context* getQueryContext();
Context* getPropertyTestContext();
Context* getInferableTestContext();
Context* getTopLevelUpdateContext();
World* lookupConstraintPropagationWorld(Context* self);
void inheritCachedInferences(World* fromworld, World* toworld);
void inheritTruthValueUpdate(Proposition* proposition, World* toworld);
void inheritVariableValueUpdate(Skolem* skolem, World* toworld);
void callPropagateConstraints(Context* context);
void propagateConstraints(Cons* name);
void propagateConstraintsEvaluatorWrapper(Cons* arguments);
void repropagateConstraints(Cons* name);
void repropagateConstraintsEvaluatorWrapper(Cons* arguments);
void callRunForwardRules(Context* context, boolean localP, boolean forceP);
void runForwardRules(Cons* options);
void runForwardRulesEvaluatorWrapper(Cons* arguments);
void helpStartupInferenceCaches1();
void startupInferenceCaches();

// Auxiliary global declarations:
extern Surrogate* SGT_INFERENCE_CACHES_STELLA_WORLD;
extern Symbol* SYM_INFERENCE_CACHES_LOGIC_INFERENCE_CACHE_OF;
extern Symbol* SYM_INFERENCE_CACHES_LOGIC_MONOTONICp;
extern Keyword* KWD_INFERENCE_CACHES_JUST_IN_TIME;
extern Symbol* SYM_INFERENCE_CACHES_LOGIC_JUST_IN_TIME_INFERENCE_CACHE;
extern Keyword* KWD_INFERENCE_CACHES_META;
extern Symbol* SYM_INFERENCE_CACHES_LOGIC_META_INFERENCE_CACHE;
extern Keyword* KWD_INFERENCE_CACHES_TMS;
extern Symbol* SYM_INFERENCE_CACHES_LOGIC_TRUTH_MAINTAINED_INFERENCE_CACHE;
extern Keyword* KWD_INFERENCE_CACHES_PREORDER;
extern Surrogate* SGT_INFERENCE_CACHES_LOGIC_DESCRIPTION;
extern Surrogate* SGT_INFERENCE_CACHES_STELLA_LITERAL_WRAPPER;
extern Surrogate* SGT_INFERENCE_CACHES_LOGIC_SKOLEM;
extern Keyword* KWD_INFERENCE_CACHES_FUNCTION;
extern Surrogate* SGT_INFERENCE_CACHES_PL_KERNEL_KB_HIDDEN_RELATION;
extern Keyword* KWD_INFERENCE_CACHES_RETRACT;
extern Symbol* SYM_INFERENCE_CACHES_LOGIC_TRUTH_MAINTAINEDp;
extern Keyword* KWD_INFERENCE_CACHES_PERFORMANCE_CLUES;
extern Symbol* SYM_INFERENCE_CACHES_LOGIC_UP_TO_DATE_INFERENCESp;
extern Keyword* KWD_INFERENCE_CACHES_EXTENSIONAL_ASSERTION;
extern Surrogate* SGT_INFERENCE_CACHES_LOGIC_LOGIC_OBJECT;
extern Keyword* KWD_INFERENCE_CACHES_MODULE;
extern Keyword* KWD_INFERENCE_CACHES_FORCEp;
extern Keyword* KWD_INFERENCE_CACHES_FORCE;
extern Surrogate* SGT_INFERENCE_CACHES_STELLA_MODULE;
extern Keyword* KWD_INFERENCE_CACHES_LOCALp;
extern Surrogate* SGT_INFERENCE_CACHES_STELLA_BOOLEAN;
extern Keyword* KWD_INFERENCE_CACHES_DISABLE_JITp;
extern Keyword* KWD_INFERENCE_CACHES_JUST_IN_TIME_INFERENCE;
extern Symbol* SYM_INFERENCE_CACHES_LOGIC_STARTUP_INFERENCE_CACHES;
extern Symbol* SYM_INFERENCE_CACHES_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
