//  -*- Mode: C++ -*-

// logic-in.cc

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

// List of PowerLoom environment features.
List* oAVAILABLE_POWERLOOM_FEATURESo = NULL;

// List of currently enabled PowerLoom environment features.
List* oCURRENT_POWERLOOM_FEATURESo = NULL;

// List of PowerLoom environment features enabled upon call to
// 'reset-features'.
List* oDEFAULT_POWERLOOM_FEATURESo = NULL;

void printFeatures() {
  // Print the currently enabled and available PowerLoom environment features.
  std::cout << "Currently enabled PowerLoom features:" << std::endl << "   " << oCURRENT_POWERLOOM_FEATURESo << std::endl << std::endl << "Available PowerLoom features:" << std::endl << "   " << oAVAILABLE_POWERLOOM_FEATURESo << std::endl;
}

List* listFeatures() {
  // Return a list containing two lists, a list of currently enabled PowerLoom
  // features, and a list of all available PowerLoom features.
  return (list(2, oCURRENT_POWERLOOM_FEATURESo, oAVAILABLE_POWERLOOM_FEATURESo));
}

void setPowerloomFeature(Keyword* feature) {
  // Enable the PowerLoom environment feature `feature'.
  if (!(oCURRENT_POWERLOOM_FEATURESo->memberP(feature))) {
    if (feature == KWD_LOGIC_IN_TRACE_SUBGOALS) {
      clearCaches();
      addTrace(consList(1, KWD_LOGIC_IN_GOAL_TREE));
    }
    else if (feature == KWD_LOGIC_IN_TRACE_SOLUTIONS) {
      clearCaches();
      addTrace(consList(1, KWD_LOGIC_IN_TRACE_SOLUTIONS));
    }
    else if (feature == KWD_LOGIC_IN_TRACE_CLASSIFIER) {
      clearCaches();
      addTrace(consList(1, KWD_LOGIC_IN_CLASSIFIER_INFERENCES));
    }
    else if (feature == KWD_LOGIC_IN_CLOSED_WORLD) {
    }
    else if (feature == KWD_LOGIC_IN_ITERATIVE_DEEPENING) {
      oITERATIVE_DEEPENING_MODEpo = true;
    }
    else if (feature == KWD_LOGIC_IN_JUSTIFICATIONS) {
      oRECORD_JUSTIFICATIONSpo = true;
    }
    else if (feature == KWD_LOGIC_IN_JUST_IN_TIME_INFERENCE) {
      oJUST_IN_TIME_FORWARD_INFERENCEpo = true;
    }
    else if (feature == KWD_LOGIC_IN_EMIT_THINKING_DOTS) {
      oEMIT_THINKING_DOTSpo = true;
    }
    else {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "No such PowerLoom environment feature: " << "`" << feature << "'" << std::endl;
      printFeatures();
      return;
    }
    oCURRENT_POWERLOOM_FEATURESo->insert(feature);
  }
}

List* setFeature(Cons* features) {
  // Enable the PowerLoom environment feature(s) named by `features'.
  // Return the list of enabled features.  Calling `set-feature' without any
  // arguments can be used to display the currently enabled features.
  // The following features are supported:
  // 
  // `just-in-time-inference': Enables interleaving of forward chaining inference
  // within backward chaining queries.
  // 
  // `iterative-deepening': Tells the query processor to use iterative deepening
  // instead of a depth-first search to find answers.  This is less efficient
  // but necessary for some kinds of highly recursive queries.
  // 
  // `trace-subgoals': Enables the generation of subgoaling trace information during
  // backchaining inference.
  // 
  // `trace-solutions': Prints newly found solutions during retrieval right when they
  // are generated as opposed to when the query terminates.
  // 
  // `trace-classifier': Tells the classifier to describe the inferences it draws.
  // 
  // `justifications': Enables the generation of justifications during inference,
  // which is a prerequiste for the generation of explanations with `(why)'.
  // 
  // `emit-thinking-dots': Tells PowerLoom to annotate its inference progress by
  // outputting characters indicating the completion of individual reasoning steps.
  // 
  // By default, the features `emit-thinking-dots' and `just-in-time-inference'
  // are enabled, and the others are disabled.
  // 
  try {
    { Object* featurename = NULL;
      Cons* iter000 = features;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        featurename = iter000->value;
        setPowerloomFeature(stringKeywordify(coerceToString(featurename)));
      }
    }
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
  }
  return (oCURRENT_POWERLOOM_FEATURESo);
}

List* setFeatureEvaluatorWrapper(Cons* arguments) {
  return (setFeature(arguments));
}

void unsetPowerloomFeature(Keyword* feature) {
  // Disable the PowerLoom environment feature `feature'.
  if (oCURRENT_POWERLOOM_FEATURESo->memberP(feature)) {
    if (feature == KWD_LOGIC_IN_TRACE_SUBGOALS) {
      dropTrace(consList(1, KWD_LOGIC_IN_GOAL_TREE));
    }
    else if (feature == KWD_LOGIC_IN_TRACE_SOLUTIONS) {
      dropTrace(consList(1, KWD_LOGIC_IN_TRACE_SOLUTIONS));
    }
    else if (feature == KWD_LOGIC_IN_TRACE_CLASSIFIER) {
      dropTrace(consList(1, KWD_LOGIC_IN_CLASSIFIER_INFERENCES));
    }
    else if (feature == KWD_LOGIC_IN_CLOSED_WORLD) {
    }
    else if (feature == KWD_LOGIC_IN_ITERATIVE_DEEPENING) {
      oITERATIVE_DEEPENING_MODEpo = false;
    }
    else if (feature == KWD_LOGIC_IN_JUSTIFICATIONS) {
      oRECORD_JUSTIFICATIONSpo = false;
    }
    else if (feature == KWD_LOGIC_IN_JUST_IN_TIME_INFERENCE) {
      oJUST_IN_TIME_FORWARD_INFERENCEpo = false;
    }
    else if (feature == KWD_LOGIC_IN_EMIT_THINKING_DOTS) {
      oEMIT_THINKING_DOTSpo = false;
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << feature << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
  else {
    if (!oAVAILABLE_POWERLOOM_FEATURESo->memberP(feature)) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "No such PowerLoom environment feature: " << "`" << feature << "'" << std::endl;
      printFeatures();
    }
  }
  oCURRENT_POWERLOOM_FEATURESo->remove(feature);
}

List* unsetFeature(Cons* features) {
  // Disable the PowerLoom environment feature(s) named by `features'.
  // Return the list of enabled features.  Calling `unset-feature' without any
  // arguments can be used to display the currently enabled features.
  // See `set-feature' for a description of supported features.
  try {
    { Object* featurename = NULL;
      Cons* iter000 = features;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        featurename = iter000->value;
        unsetPowerloomFeature(stringKeywordify(coerceToString(featurename)));
      }
    }
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
  }
  return (oCURRENT_POWERLOOM_FEATURESo);
}

List* unsetFeatureEvaluatorWrapper(Cons* arguments) {
  return (unsetFeature(arguments));
}

List* resetFeatures() {
  // Reset the PowerLoom environment features to their default settings.
  { Keyword* f = NULL;
    Cons* iter000 = oCURRENT_POWERLOOM_FEATURESo->copy()->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      f = ((Keyword*)(iter000->value));
      if (!oDEFAULT_POWERLOOM_FEATURESo->memberP(f)) {
        unsetPowerloomFeature(f);
      }
    }
  }
  { Keyword* f = NULL;
    Cons* iter001 = oDEFAULT_POWERLOOM_FEATURESo->theConsList;

    for (; !(iter001 == NIL); iter001 = iter001->rest) {
      f = ((Keyword*)(iter001->value));
      if (!oCURRENT_POWERLOOM_FEATURESo->memberP(f)) {
        setPowerloomFeature(f);
      }
    }
  }
  return (oCURRENT_POWERLOOM_FEATURESo);
}

boolean enabledPowerloomFeatureP(Keyword* feature) {
  // Return true if the STELLA `feature' is currently enabled.
  return (oCURRENT_POWERLOOM_FEATURESo->membP(feature));
}

boolean disabledPowerloomFeatureP(Keyword* feature) {
  // Return true if the STELLA `feature' is currently disabled.
  return (!oCURRENT_POWERLOOM_FEATURESo->membP(feature));
}

PropertyList* parseLogicCommandOptions(Object* options, Cons* legaloptionsAtypes, boolean coercionerrorP, boolean allowotherkeysP) {
  // This is simply a wrapper to `parse-options' (which see).
  // We keep this alias in case we ever want to add any logic-specific extensions.
  return (parseOptions(options, legaloptionsAtypes, coercionerrorP, allowotherkeysP));
}

// The prompt used by the PowerLoom listener.
const char* oLOGIC_PROMPTo = "|= ";

// Flag to control whether the logic prompt shows the module name.
DEFINE_STELLA_SPECIAL(oPROMPT_SHOW_MODULEpo, boolean , true);

void printLogicPrompt() {
  if (oPROMPT_SHOW_MODULEpo) {
    std::cout << oMODULEo->moduleName << " ";
  }
  std::cout << oLOGIC_PROMPTo;
}

const char* oLOGIC_COMMAND_RESULT_INDENTo = "";

void printLogicCommandResult(Object* result) {
  { World* temp000 = lookupConstraintPropagationWorld(oCONTEXTo);

    { Context* printcontext = (((boolean)(temp000)) ? temp000 : oCONTEXTo);

      { 
        BIND_STELLA_SPECIAL(oPRINTMODEo, Keyword*, KWD_LOGIC_IN_REALISTIC);
        BIND_STELLA_SPECIAL(oPRETTYPRINTLOGICALFORMSpo, boolean, true);
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, printcontext);
        if (((boolean)(result))) {
          std::cout << oLOGIC_COMMAND_RESULT_INDENTo << result << std::endl;
        }
      }
    }
  }
}

// If TRUE exiting from the logic-command loop (or PowerLoom
// listener) will be protected by a confirmation dialog.  This is mainly useful
// for C++ and Java where exiting the listener will also exit the program.
DEFINE_STELLA_SPECIAL(oCONFIRM_INTERACTIVE_EXITpo, boolean , true);

boolean logicCommandLoopExitP(Object* command, boolean& _Return1) {
  { boolean exitP = false;

    { Surrogate* testValue000 = safePrimaryType(command);

      if (subtypeOfKeywordP(testValue000)) {
        { Object* command000 = command;
          Keyword* command = ((Keyword*)(command000));

          if ((command == KWD_LOGIC_IN_BYE) ||
              ((command == KWD_LOGIC_IN_EXIT) ||
               ((command == KWD_LOGIC_IN_HALT) ||
                ((command == KWD_LOGIC_IN_QUIT) ||
                 (command == KWD_LOGIC_IN_STOP))))) {
            exitP = true;
          }
          else {
          }
        }
      }
      else if (subtypeOfSymbolP(testValue000)) {
        { Object* command001 = command;
          Symbol* command = ((Symbol*)(command001));

          { const char* testValue001 = command->symbolName;

            if (stringEqlP(testValue001, "BYE") ||
                (stringEqlP(testValue001, "EXIT") ||
                 (stringEqlP(testValue001, "HALT") ||
                  (stringEqlP(testValue001, "QUIT") ||
                   (stringEqlP(testValue001, "STOP") ||
                    (stringEqlP(testValue001, "bye") ||
                     (stringEqlP(testValue001, "exit") ||
                      (stringEqlP(testValue001, "halt") ||
                       (stringEqlP(testValue001, "quit") ||
                        stringEqlP(testValue001, "stop")))))))))) {
              exitP = true;
            }
            else {
            }
          }
        }
      }
      else {
      }
    }
    if (exitP &&
        oCONFIRM_INTERACTIVE_EXITpo) {
      exitP = yesOrNoP("Really exit? (yes or no) ");
      if (exitP) {
        std::cout << std::endl;
      }
      _Return1 = true;
      return (exitP);
    }
    _Return1 = exitP;
    return (exitP);
  }
}

void logicCommandLoop(Module* module) {
  { Object* command = NULL;
    Object* result = NULL;
    boolean eofP = false;
    boolean exitP = false;
    boolean exitcommandP = false;

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      clearInput(STANDARD_INPUT);
      for (;;) {
        try {
          std::cout << std::endl;
          printLogicPrompt();
          command = readSExpression(STANDARD_INPUT, eofP);
          if (eofP) {
            std::cout << "End of File encountered.  Exiting." << std::endl;
            break;
          }
          std::cout << std::endl;
          exitP = logicCommandLoopExitP(command, exitcommandP);
          if (exitP) {
            break;
          }
          if (exitcommandP) {
            continue;
          }
          result = evaluateLogicCommand(command, false);
          printLogicCommandResult(result);
        }
        catch (LogicException& _le) {
          LogicException* le = &_le;

          *(STANDARD_ERROR->nativeStream) << ">> Error: " << exceptionMessage(le);
        }
        catch (StellaException& _e) {
          StellaException* e = &_e;

          *(STANDARD_ERROR->nativeStream) << ">> Internal Error: " << exceptionMessage(e);
          printExceptionContext(e, STANDARD_ERROR);
        }
      }
    }
  }
}

Object* evaluateLogicCommand(Object* command, boolean finalizeP) {
  { boolean dummy1;

    { 
      BIND_STELLA_SPECIAL(oTRANSLATIONERRORSo, int, 0);
      BIND_STELLA_SPECIAL(oTRANSLATIONWARNINGSo, int, 0);
      BIND_STELLA_SPECIAL(oIGNORETRANSLATIONERRORSpo, boolean, false);
      BIND_STELLA_SPECIAL(oTRANSLATIONUNITSo, List*, NULL);
      BIND_STELLA_SPECIAL(oTRANSLATIONPHASEo, Keyword*, KWD_LOGIC_IN_DEFINE);
      BIND_STELLA_SPECIAL(oEVALUATIONTREEo, Object*, NULL);
      { Object* operatoR = NULL;
        const char* operatorname = NULL;
        Object* result = NULL;

        { Surrogate* testValue000 = safePrimaryType(command);

          if (testValue000 == SGT_LOGIC_IN_STELLA_CONS) {
            { Object* command000 = command;
              Cons* command = ((Cons*)(command000));

              operatoR = command->value;
              if (subtypeOfSymbolP(safePrimaryType(operatoR))) {
                { Object* operator000 = operatoR;
                  Symbol* operatoR = ((Symbol*)(operator000));

                  operatorname = operatoR->symbolName;
                  if (stringEqualP(operatorname, "DEFMODULE")) {
                    operatoR = SYM_LOGIC_IN_STELLA_DEFMODULE;
                    command->value = operatoR;
                  }
                  if (stringEqualP(operatorname, "IN-MODULE")) {
                    handleInModuleTree(command, false, false, dummy1);
                  }
                  else if (stringEqualP(operatorname, "IN-PACKAGE")) {
                  }
                  else if (declarationTreeP(command)) {
                    oTRANSLATIONUNITSo = list(0);
                    walkTopLevelTree(command, false);
                    switch (oTRANSLATIONUNITSo->reverse()->length()) {
                      case 0: 
                        { OutputStringStream* stream000 = newOutputStringStream();

                          *(stream000->nativeStream) << "Translation failed: " << "`" << command << "'";
                          throw *newEvaluationException(stream000->theStringReader());
                        }
                        break;
                      case 1: 
                        result = ((TranslationUnit*)(oTRANSLATIONUNITSo->first()))->theObject;
                        break;
                      default:
                        { Cons* results = NIL;

                          { TranslationUnit* unit = NULL;
                            Cons* iter000 = oTRANSLATIONUNITSo->theConsList;
                            Cons* collect000 = NULL;

                            for  (; !(iter000 == NIL); 
                                  iter000 = iter000->rest) {
                              unit = ((TranslationUnit*)(iter000->value));
                              if (!((boolean)(collect000))) {
                                {
                                  collect000 = cons(unit->theObject, NIL);
                                  if (results == NIL) {
                                    results = collect000;
                                  }
                                  else {
                                    addConsToEndOfConsList(results, collect000);
                                  }
                                }
                              }
                              else {
                                {
                                  collect000->rest = cons(unit->theObject, NIL);
                                  collect000 = collect000->rest;
                                }
                              }
                            }
                          }
                          result = results;
                        }
                        break;
                    }
                  }
                  else {
                    // Should be synchronized on process lock oPOWERLOOM_LOCKo
                    {
                      result = evaluate(command);
                    }
                  }
                }
              }
              else {
                // Should be synchronized on process lock oPOWERLOOM_LOCKo
                {
                  result = evaluate(command);
                }
              }
            }
          }
          else if (subtypeOfKeywordP(testValue000)) {
            { Object* command001 = command;
              Keyword* command = ((Keyword*)(command001));

              result = command;
            }
          }
          else if (subtypeOfSurrogateP(testValue000)) {
            { Object* command002 = command;
              Surrogate* command = ((Surrogate*)(command002));

              result = command;
            }
          }
          else {
            // Should be synchronized on process lock oPOWERLOOM_LOCKo
            {
              result = evaluate(command);
            }
          }
        }
        if ((!translationErrorsP()) &&
            finalizeP) {
          oTRANSLATIONPHASEo = KWD_LOGIC_IN_FINALIZE;
          finalizeObjects();
        }
        return (result);
      }
    }
  }
}

// If the extension of a KB file is unspecified in a
// `load' or `demo' command, try to find it with one of these extensions.
Cons* oPOWERLOOM_KB_FILE_EXTENSIONSo = NULL;

// If non-NULL, definition axioms and assertions will be evaluated
// in this module instead of the IN-MODULE of a file, which allows us to separate
// vocabulary definitions and their definitional constraints.
DEFINE_STELLA_SPECIAL(oASSERTION_MODULEo, Module* , NULL);

void load(const char* file, Cons* options) {
  // Read logic commands from `file' and evaluate them.
  // By default, this will check for each asserted proposition whether an
  // equivalent proposition already exists and, if so, not assert the
  // duplicate.  These duplicate checks are somewhat expensive though and
  // can be skipped by setting the option :check-duplicates? to false.
  // This can save time when loading large KBs where it is known that no
  // duplicate assertions exist in a file.
  // 
  // Also, by setting the :module option, the module in which the file
  // contents will be loaded will be set.  This will only affect files
  // that do NOT have an `in-module' declaration as part of the file.
  // If this is not set, and no `in-module' declaration is in the file,
  // the file will be loaded into the current module.
  // 
  // The option :assertion-module can be used to have assertions and
  // definitional axioms be asserted in a different module than the
  // top-level module where definitions are evaluated.  This is useful
  // in some cases where vocabulary definitions and their associated
  // axioms and assertions need to be separate for inference or efficiency
  // reasons.  The assertion module can be given as a name in case it is
  // defined in the loaded file.  Obviously, it needs to be a child of the
  // top-level module where vocabulary definitions are created.
  // 
  // Loading is done in two passes: in the first pass all definitional
  // commands such as `defmodule', `defconcept', etc. are evaluated but not
  // yet finalized, that is, their definitional axioms are parsed but not
  // yet asserted.  In the second pass all definitional commands are finalized
  // and then all commands in the file are executed in order (which will be
  // no-ops for the definitions already processed).  This scheme tries to
  // maintain some order independence for the commands in the file, since
  // relation definitions need to be performed before they can be used in
  // assertions.  At any point `process-definitions' can be called to finalize
  // all unfinalized definitions queued up so far.  Future versions might also
  // support a :one-pass? option for added efficiency.
  { const char* temp000 = findFileInLoadPath(file, oPOWERLOOM_KB_FILE_EXTENSIONSo);

    file = ((temp000 != NULL) ? temp000 : file);
  }
  ensureFileExists(file, "load");
  { boolean toplevelinvocationP = oCURRENTFILENAMEo == NULL;

    { 
      BIND_STELLA_SPECIAL(oCURRENTLOADFILEo, const char*, file);
      BIND_STELLA_SPECIAL(oCURRENTFILENAMEo, const char*, fileBaseName(file));
      { InputFileStream* inputstream = NULL;

        try {
          inputstream = openInputFile(file, 0);
          loadStream(inputstream, 2, KWD_LOGIC_IN_OPTIONS, options);
        }
catch (...) {
          if (((boolean)(inputstream))) {
            inputstream->free();
          }
          throw;
        }
        if (((boolean)(inputstream))) {
          inputstream->free();
        }
      }
    }
    if (toplevelinvocationP) {
      sweepTransients();
    }
  }
}

void loadEvaluatorWrapper(Cons* arguments) {
  load(((StringWrapper*)(arguments->value))->wrapperValue, arguments->rest);
}

boolean definitionNameP(Symbol* name) {
  { const char* nameString = name->symbolName;

    return ((strlen(nameString) > 2) &&
        ((nameString[0] == 'D') &&
         ((nameString[1] == 'E') &&
          (nameString[2] == 'F'))));
  }
}

Keyword* loadCommandEvalPhase(Object* tree) {
  // Analyze a command `tree' in a load file and determine when it should be processed.
  if (safePrimaryType(tree) == SGT_LOGIC_IN_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      { Object* operatoR = tree->value;

        if (subtypeOfSymbolP(safePrimaryType(operatoR))) {
          { Object* operator000 = operatoR;
            Symbol* operatoR = ((Symbol*)(operator000));

            if ((operatoR == SYM_LOGIC_IN_STELLA_DEFMODULE) ||
                ((operatoR == SYM_LOGIC_IN_STELLA_CLEAR_MODULE) ||
                 ((operatoR == SYM_LOGIC_IN_STELLA_DEFCLASS) ||
                  ((operatoR == SYM_LOGIC_IN_STELLA_DEFSLOT) ||
                   ((operatoR == SYM_LOGIC_IN_STELLA_DEFUN) ||
                    ((operatoR == SYM_LOGIC_IN_STELLA_DEFMETHOD) ||
                     ((operatoR == SYM_LOGIC_IN_LOGIC_DEFCONCEPT) ||
                      ((operatoR == SYM_LOGIC_IN_LOGIC_DEFFUNCTION) ||
                       ((operatoR == SYM_LOGIC_IN_LOGIC_DEFRELATION) ||
                        ((operatoR == SYM_LOGIC_IN_LOGIC_DEFOBJECT) ||
                         ((operatoR == SYM_LOGIC_IN_LOGIC_DEFINSTANCE) ||
                          (operatoR == SYM_LOGIC_IN_LOGIC_DESTROY)))))))))))) {
              return (KWD_LOGIC_IN_IMMEDIATE);
            }
            else if ((operatoR == SYM_LOGIC_IN_LOGIC_IN_DIALECT) ||
                (operatoR == SYM_LOGIC_IN_STELLA_CC)) {
              return (KWD_LOGIC_IN_ALWAYS);
            }
            else {
              if ((!definitionNameP(operatoR)) &&
                  ((boolean)(lookupCommand(operatoR)))) {
                return (KWD_LOGIC_IN_DEFERRED);
              }
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
  return (KWD_LOGIC_IN_IMMEDIATE);
}

void loadStream(InputStream* stream, int options, ...) {
  // Read logic commands from `stream' and evaluate them.
  // Does the actual work for `load' (which see for a description of options).
  { Cons* arglist000 = NIL;

    { va_list iter000;
      int iter000Count = options;
      Object* arg000 = NULL;
      Cons* collect000 = NULL;

      va_start(iter000, options);
            for  (; (iter000Count--) > 0; ) {
        arg000 = va_arg(iter000, Object*);
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(arg000, NIL);
            if (arglist000 == NIL) {
              arglist000 = collect000;
            }
            else {
              addConsToEndOfConsList(arglist000, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(arg000, NIL);
            collect000 = collect000->rest;
          }
        }
      }
      va_end(iter000);
    }
    { PropertyList* theoptions = parseLogicCommandOptions(arglist000, listO(7, KWD_LOGIC_IN_CHECK_DUPLICATESp, SGT_LOGIC_IN_STELLA_BOOLEAN, KWD_LOGIC_IN_MODULE, SGT_LOGIC_IN_STELLA_MODULE, KWD_LOGIC_IN_ASSERTION_MODULE, SGT_LOGIC_IN_STELLA_IDENTITY, NIL), true, false);
      Keyword* currentdialect = oLOGIC_DIALECTo;
      Object* loadmodule = theoptions->lookupWithDefault(KWD_LOGIC_IN_MODULE, oMODULEo);
      boolean skipcommandP = false;
      boolean seeninmoduleP = ((boolean)(loadmodule));
      Cons* commands = NIL;

      { 
        BIND_STELLA_SPECIAL(oDONT_CHECK_FOR_DUPLICATE_PROPOSITIONSpo, boolean, !coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_LOGIC_IN_CHECK_DUPLICATESp, TRUE_WRAPPER)))));
        BIND_STELLA_SPECIAL(oASSERTION_MODULEo, Module*, NULL);
        BIND_STELLA_SPECIAL(oLOGIC_DIALECTo, Keyword*, currentdialect);
        BIND_STELLA_SPECIAL(oTRANSLATIONERRORSo, int, 0);
        BIND_STELLA_SPECIAL(oTRANSLATIONWARNINGSo, int, 0);
        BIND_STELLA_SPECIAL(oTRANSLATIONNOTESo, int, 0);
        { 
          BIND_STELLA_SPECIAL(oMODULEo, Module*, ((Module*)(loadmodule)));
          BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
          { Object* tree = NULL;
            SExpressionIterator* iter001 = sExpressions(stream);

            for (; iter001->nextP(); ) {
              tree = iter001->value;
              if (consP(tree)) {
                skipcommandP = handleInModuleTree(((Cons*)(tree)), seeninmoduleP, false, seeninmoduleP);
                if (skipcommandP) {
                  continue;
                }
              }
              { Keyword* testValue000 = loadCommandEvalPhase(tree);

                if (testValue000 == KWD_LOGIC_IN_IMMEDIATE) {
                  evaluateLogicCommand(tree, false);
                }
                else if (testValue000 == KWD_LOGIC_IN_ALWAYS) {
                  evaluateLogicCommand(tree, false);
                  commands = cons(tree, commands);
                }
                else if (testValue000 == KWD_LOGIC_IN_DEFERRED) {
                  commands = cons(tree, commands);
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
          if (((boolean)(theoptions->lookup(KWD_LOGIC_IN_ASSERTION_MODULE)))) {
            oASSERTION_MODULEo = coerceToModule(theoptions->lookup(KWD_LOGIC_IN_ASSERTION_MODULE), true);
            oMODULEo = oASSERTION_MODULEo;
            oCONTEXTo = oASSERTION_MODULEo;
          }
          { 
            BIND_STELLA_SPECIAL(oTRANSLATIONPHASEo, Keyword*, KWD_LOGIC_IN_FINALIZE);
            finalizeObjects();
          }
          { Object* tree = NULL;
            Cons* iter002 = commands->reverse();

            for (; !(iter002 == NIL); iter002 = iter002->rest) {
              tree = iter002->value;
              if (((boolean)(oASSERTION_MODULEo))) {
                oMODULEo = oASSERTION_MODULEo;
                oCONTEXTo = oASSERTION_MODULEo;
              }
              evaluateLogicCommand(tree, true);
            }
          }
        }
        if (!(ignoreTranslationErrorsP())) {
          summarizeTranslationErrors();
        }
      }
    }
  }
}

void loadStreamInModule(InputStream* stream, Module* module) {
  // Read logic commands from `stream' and evaluate them in `module'.
  // This is a backwards-compatibility wrapper.  Note that `module' will not override
  // any `in-module' declarations in `stream'.
  loadStream(stream, 2, KWD_LOGIC_IN_MODULE, module);
}

void loadDirectory(const char* directory) {
  // Load all PowerLoom files (*.plm) in `directory' in alphabetic sort order.
  plLog(KWD_LOGIC_IN_LOW, 3, wrapString("Loading PowerLoom files from directory "), wrapString(directory), wrapString("..."));
  bumpLogIndent();
  directory = fileNameAsDirectory(directory);
  { StringWrapper* file = NULL;
    Cons* iter000 = listDirectoryFiles(directory);

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      file = ((StringWrapper*)(iter000->value));
      { boolean foundP000 = false;

        { Object* ext = NULL;
          Cons* iter001 = oPOWERLOOM_KB_FILE_EXTENSIONSo;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            ext = iter001->value;
            if (endsWithP(file->wrapperValue, ((StringWrapper*)(ext))->wrapperValue, NULL_INTEGER)) {
              foundP000 = true;
              break;
            }
          }
        }
        if (foundP000) {
          plLog(KWD_LOGIC_IN_MEDIUM, 2, wrapString("Loading file "), file);
          load(stringConcatenate(directory, file->wrapperValue, 0), NIL);
        }
      }
    }
  }
  unbumpLogIndent();
  processDefinitions();
}

void loadDirectoryEvaluatorWrapper(Cons* arguments) {
  loadDirectory(((StringWrapper*)(arguments->value))->wrapperValue);
}

void loadCmdLineFiles() {
  // Loads all PowerLoom files specified on the command line.
  // If directories are listed, all PowerLoom files in those directories are loaded.
  // Since when this is called we might still have unprocessed command line args,
  // this only looks at files which are to the right of the last argument that
  // starts with a `-' character.
  { Cons* unprocessedargs = unprocessedCommandLineArguments();
    const char* file = NULL;

    if (((boolean)(unprocessedargs))) {
      unprocessedargs = copyConsList(unprocessedCommandLineArguments())->reverse();
      { StringWrapper* arg = NULL;
        Cons* iter000 = unprocessedargs;
        int i = NULL_INTEGER;
        int iter001 = 0;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest,
              iter001 = iter001 + 1) {
          arg = ((StringWrapper*)(iter000->value));
          i = iter001;
          if (startsWithP(arg->wrapperValue, "-", NULL_INTEGER)) {
            if (i == 0) {
              unprocessedargs = NIL;
            }
            else {
              unprocessedargs->nthRestSetter(NIL, i);
            }
            break;
          }
        }
      }
      plLog(KWD_LOGIC_IN_LOW, 1, wrapString("Loading command line PowerLoom files..."));
      bumpLogIndent();
      { StringWrapper* arg = NULL;
        Cons* iter002 = unprocessedargs->reverse();

        for (; !(iter002 == NIL); iter002 = iter002->rest) {
          arg = ((StringWrapper*)(iter002->value));
          { boolean foundP000 = false;

            { Object* ext = NULL;
              Cons* iter003 = oPOWERLOOM_KB_FILE_EXTENSIONSo;

              for (; !(iter003 == NIL); iter003 = iter003->rest) {
                ext = iter003->value;
                if (endsWithP(arg->wrapperValue, ((StringWrapper*)(ext))->wrapperValue, NULL_INTEGER)) {
                  foundP000 = true;
                  break;
                }
              }
            }
            if (foundP000) {
              {
                { const char* temp000 = findFileInLoadPath(arg->wrapperValue, NULL);

                  file = ((temp000 != NULL) ? temp000 : arg->wrapperValue);
                }
                plLog(KWD_LOGIC_IN_MEDIUM, 2, wrapString("Loading file "), wrapString(file));
                load(file, NIL);
              }
            }
            else {
              if (probeFileP(fileNameAsDirectory(arg->wrapperValue))) {
                loadDirectory(arg->wrapperValue);
              }
            }
          }
        }
      }
      unbumpLogIndent();
    }
  }
}

DEFINE_STELLA_SPECIAL(oDEMO_LEVELo, int , 0);

void printDemoPrompt() {
  std::cout << oLOGIC_PROMPTo;
}

boolean demoSkipToCommand(InputStream* stream) {
  { char ch = NULL_CHARACTER;
    boolean eofP = false;
    boolean echoP = false;
    OutputStream* echostream = stream->echoStream;

    for (;;) {
      stream->echoStream = NULL;
      ch = readCharacter(stream, eofP);
      if (eofP) {
        return (true);
      }
      if (echoP) {
        stream->echoStream = echostream;
      }
      if (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) ch] == KWD_LOGIC_IN_WHITE_SPACE) {
        if (echoP) {
          *(echostream->nativeStream) << ch;
        }
      }
      else if (ch == ';') {
        echoP = true;
        stream->echoStream = echostream;
        *(echostream->nativeStream) << ch;
        eofP = nativeReadLine(stream) == NULL;
        if (eofP) {
          return (true);
        }
      }
      else {
        stream->echoStream = echostream;
        unreadCharacter(ch, stream);
        break;
      }
    }
    return (false);
  }
}

boolean demoPauseP(boolean pauseP, boolean& _Return1) {
  { boolean exitP = false;
    const char* input = NULL;

    if (pauseP) {
      std::cout << "------ pause ------";
      input = readLine(STANDARD_INPUT);
      std::cout << std::endl;
      if (strlen(input) > 0) {
        switch (oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) (input[0]))]) {
          case 'C': 
            pauseP = false;
            break;
          case 'Q': 
            if (yOrNP("Really exit demo? (y or n) ")) {
              pauseP = false;
              exitP = true;
            }
            break;
          case 'H': 
          case '?': 
            std::cout << "Type `c' to continue without pausing," << std::endl << "     `q' to quit from this demo," << std::endl << "     `?' or `h' to get this message," << std::endl << "     or any other key to continue." << std::endl;
            return (demoPauseP(pauseP, _Return1));
          default:
            break;
        }
      }
    }
    else {
      std::cout << std::endl;
    }
    _Return1 = exitP;
    return (pauseP);
  }
}

void demoFile(const char* file, boolean pauseP) {
  { boolean dummy1;

    { const char* temp000 = findFileInLoadPath(file, oPOWERLOOM_KB_FILE_EXTENSIONSo);

      file = ((temp000 != NULL) ? temp000 : file);
    }
    ensureFileExists(file, "demo-file");
    { int currentlevel = oDEMO_LEVELo;
      Object* command = NULL;
      Object* result = NULL;
      boolean exitP = false;

      { InputFileStream* inputstream = NULL;

        try {
          inputstream = openInputFile(file, 0);
          { 
            BIND_STELLA_SPECIAL(oCONFIRM_INTERACTIVE_EXITpo, boolean, false);
            BIND_STELLA_SPECIAL(oDEMO_LEVELo, int, currentlevel + 1);
            inputstream->echoStream = STANDARD_OUTPUT;
            { 
              BIND_STELLA_SPECIAL(oMODULEo, Module*, oMODULEo);
              BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
              if (pauseP) {
                std::cout << "Now reading from `" << file << "'." << std::endl << "Type `?' at the pause prompt for a list of available commands." << std::endl;
              }
              for (;;) {
                try {
                  std::cout << std::endl;
                  exitP = demoSkipToCommand(inputstream);
                  printDemoPrompt();
                  if (!(exitP)) {
                    command = readSExpression(inputstream, exitP);
                  }
                  if (exitP ||
                      logicCommandLoopExitP(command, dummy1)) {
                    break;
                  }
                  pauseP = demoPauseP(pauseP, exitP);
                  if (exitP) {
                    break;
                  }
                  result = evaluateLogicCommand(command, false);
                  printLogicCommandResult(result);
                }
                catch (EvaluationException& _e) {
                  EvaluationException* e = &_e;

                  *(STANDARD_ERROR->nativeStream) << ">> Error: " << exceptionMessage(e);
                }
              }
              std::cout << std::endl << std::endl << oLOGIC_COMMAND_RESULT_INDENTo << "Finished demo `" << file << "'." << std::endl;
            }
          }
        }
catch (...) {
          if (((boolean)(inputstream))) {
            inputstream->free();
          }
          throw;
        }
        if (((boolean)(inputstream))) {
          inputstream->free();
        }
      }
    }
  }
}

// List of example demo files.
// Each entry is a `(<file> <description>)' pair.
Cons* oDEMO_FILESo = NULL;

const char* demoEntryFile(Cons* demoentry) {
  { const char* demobasefile = ((StringWrapper*)(demoentry->value))->wrapperValue;

    { const char* temp000 = findFileInLoadPath(demobasefile, oPOWERLOOM_KB_FILE_EXTENSIONSo);

      { const char* value000 = ((temp000 != NULL) ? temp000 : demobasefile);

        return (value000);
      }
    }
  }
}

const char* demoEntryDescription(Cons* demoentry) {
  return ((((boolean)(((StringWrapper*)(demoentry->rest->value)))) ? ((StringWrapper*)(demoentry->rest->value))->wrapperValue : ((StringWrapper*)(demoentry->value))->wrapperValue));
}

boolean demoEntryTestSuiteP(Cons* demoentry) {
  return (stringP(((StringWrapper*)(demoentry->rest->rest->value))) &&
      stringEqlP(((StringWrapper*)(demoentry->rest->rest->value))->wrapperValue, "test-suite"));
}

const char* selectExampleDemo(int index) {
  { Cons* entry = ((Cons*)(oDEMO_FILESo->nth(index - 1)));

    if (((boolean)(entry))) {
      return (demoEntryFile(entry));
    }
    else {
      return (NULL);
    }
  }
}

const char* selectExampleDemoFromMenu() {
  { boolean dummy1;

    std::cout << "Choose a demo:" << std::endl;
    { Cons* entry = NULL;
      Cons* iter000 = oDEMO_FILESo;
      int i = NULL_INTEGER;
      int iter001 = 1;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        entry = ((Cons*)(iter000->value));
        i = iter001;
        std::cout << "       " << i << ".  ";
        if (i < 10) {
          std::cout << " ";
        }
        std::cout << demoEntryDescription(entry) << std::endl;
      }
    }
    std::cout << "       " << "Q.   Quit demoing" << std::endl;
    std::cout << "Your choice: ";
    { Object* selection = readSExpression(STANDARD_INPUT, dummy1);
      const char* file = NULL;

      if (subtypeOfIntegerP(safePrimaryType(selection))) {
        { Object* selection000 = selection;
          IntegerWrapper* selection = ((IntegerWrapper*)(selection000));

          file = selectExampleDemo(selection->wrapperValue);
          if (file != NULL) {
            return (file);
          }
        }
      }
      else {
        if (stringEqualP(stringify(selection), "Q")) {
          return (NULL);
        }
      }
      std::cout << ">> ERROR: Illegal choice `" << selection << "'; enter a number between 1 and " << oDEMO_FILESo->length() << "!" << std::endl << std::endl;
      return (selectExampleDemoFromMenu());
    }
  }
}

void demoExampleDemos() {
  { const char* file = NULL;

    for (;;) {
      std::cout << std::endl;
      file = selectExampleDemoFromMenu();
      if (file == NULL) {
        return;
      }
      std::cout << std::endl;
      demoFile(file, true);
    }
  }
}

void demo(Cons* fileandpause) {
  // Read logic commands from a file, echo them verbatimly to standard output,
  // and evaluate them just as if they had been typed in interactively.
  // When called with no arguments, present a menu of example demos, otherwise,
  // use the first argument as the name of the file to demo.
  // Pause for user confirmation after each expression has been read but
  // before it is evaluated.  Pausing can be turned off by suppling FALSE
  // as the optional second argument, or by typing `c' at the pause prompt.
  // Typing `?' at the pause prompt prints a list of available commands.
  { Cons* thefileandpause = fileandpause;
    Object* filespec = thefileandpause->value;
    boolean pauseP = !eqlP(thefileandpause->rest->value, FALSE_WRAPPER);
    const char* file = NULL;

    if (integerP(filespec)) {
      file = selectExampleDemo(((IntegerWrapper*)(filespec))->wrapperValue);
      if (file != NULL) {
        filespec = wrapString(file);
      }
      else {
        filespec = NULL;
      }
    }
    if (!((boolean)(filespec))) {
      demoExampleDemos();
    }
    else {
      if (subtypeOfStringP(safePrimaryType(filespec))) {
        { Object* filespec000 = filespec;
          StringWrapper* filespec = ((StringWrapper*)(filespec000));

          demoFile(filespec->wrapperValue, pauseP);
        }
      }
      else {
        std::cout << ">> ERROR: Illegal file specification: " << filespec;
      }
    }
  }
}

void demoEvaluatorWrapper(Cons* arguments) {
  demo(arguments);
}

void testLogicFile(const char* file) {
  { boolean dummy1;

    ensureFileExists(file, "test-logic-file");
    { int currentlevel = oDEMO_LEVELo;
      Object* command = NULL;
      Object* result = NULL;
      boolean exitP = false;
      InputStream* inputstream = newInputFileStream(file);
      const char* filebasename = fileNameWithoutDirectory(file);

      { 
        BIND_STELLA_SPECIAL(oCONFIRM_INTERACTIVE_EXITpo, boolean, false);
        BIND_STELLA_SPECIAL(oDEMO_LEVELo, int, currentlevel + 1);
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        BIND_STELLA_SPECIAL(oPRINTPRETTYpo, boolean, false);
        { 
          BIND_STELLA_SPECIAL(oMODULEo, Module*, oMODULEo);
          BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
          std::cout << std::endl << "Now testing file `" << filebasename << "':" << std::endl;
          for (;;) {
            try {
              std::cout << std::endl;
              printDemoPrompt();
              if (!(exitP)) {
                command = readSExpression(inputstream, exitP);
              }
              if (exitP ||
                  logicCommandLoopExitP(command, dummy1)) {
                break;
              }
              std::cout << command << std::endl << std::endl;
              result = evaluateLogicCommand(command, false);
              printLogicCommandResult(result);
            }
            catch (EvaluationException& _e) {
              EvaluationException* e = &_e;

              *(STANDARD_ERROR->nativeStream) << ">> Error: " << exceptionMessage(e);
            }
          }
          inputstream->free();
          std::cout << std::endl << std::endl << oLOGIC_COMMAND_RESULT_INDENTo << "Finished testing file `" << filebasename << "'." << std::endl;
        }
      }
    }
  }
}

const char* getFormattedDateAndTime() {
  return (makeCurrentDateTime()->calendarDateToString(getLocalTimeZone(), false, true));
}

void runPowerloomTests() {
  // Run the PowerLoom test suite.  Currently this simply runs all demos and
  // echos commands and their results to standard output.  The output can then
  // be diffed with previously validated runs to find deviations.
  { Module* pluser = getStellaModule("PL-USER", true);
    CalendarDate* startTime = makeCurrentDateTime();
    CalendarDate* finishTime = NULL;
    Object* loglevel = lookupLoggingParameter("PowerLoom", KWD_LOGIC_IN_LEVEL, KWD_LOGIC_IN_LOW);

    setLoggingParameters("PowerLoom", consList(2, KWD_LOGIC_IN_LEVEL, KWD_LOGIC_IN_NONE));
    std::cout << "RUNNING POWERLOOM TEST SUITE" << std::endl << "============================" << std::endl << std::endl;
    std::cout << "STELLA version:    " << oSTELLA_VERSION_STRINGo << std::endl << "PowerLoom version: " << oPOWERLOOM_VERSION_STRINGo << std::endl << "Start time:        " << startTime->calendarDateToString(getLocalTimeZone(), false, true) << std::endl << std::endl;
    clearContext(pluser);
    { Context* child = NULL;
      Cons* iter000 = pluser->childContexts->copy()->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        child = ((Context*)(iter000->value));
        child->destroyContext();
      }
    }
    oSKOLEM_ID_COUNTERo = 0;
    { Cons* entry = NULL;
      Cons* iter001 = oDEMO_FILESo;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        entry = ((Cons*)(iter001->value));
        if (demoEntryTestSuiteP(entry)) {
          testLogicFile(demoEntryFile(entry));
        }
      }
    }
    finishTime = makeCurrentDateTime();
    std::cout << std::endl << "FINISHED RUNNING POWERLOOM TEST SUITE" << std::endl << "=====================================" << std::endl << "Finish time:   " << finishTime->calendarDateToString(getLocalTimeZone(), false, true) << std::endl << "Elapsed time:  " << ((TimeDuration*)(timeSubtract(finishTime, startTime)))->timeDurationToString() << std::endl << std::endl;
    setLoggingParameters("PowerLoom", consList(2, KWD_LOGIC_IN_LEVEL, loglevel));
  }
}

Object* timeCommand(Cons* command) {
  // Execute `command', measure and report its CPU and elapsed time
  // needed for its execution, and then return its result.
  { CalendarDate* starttime = makeCurrentDateTime();
    clock_t startcpu = getTicktock();
    Object* result = evaluate(command);
    clock_t endcpu = getTicktock();
    TimeDuration* elapsedtime = ((TimeDuration*)(timeSubtract(makeCurrentDateTime(), starttime)));

    std::cout << "CPU Time:     " << ticktockDifference(startcpu, endcpu) << " secs" << std::endl;
    std::cout << "Elapsed Time: ";
    if (elapsedtime->days > 0) {
      std::cout << elapsedtime->days << " days, ";
    }
    std::cout << stella::round(elapsedtime->millis / 1000.0) << " secs" << std::endl;
    return (result);
  }
}

const char* getHttpServerSystem() {
  return ("webtools");
}

void startOntosaurus(Cons* options) {
  // Start the PowerLoom HTTP server at :port (defaults to 9090).  Loads
  // the required support systems in Lisp and Java if necessary (C++ is not yet supported).
  { PropertyList* theoptions = parseLogicCommandOptions(options, listO(3, KWD_LOGIC_IN_PORT, SGT_LOGIC_IN_STELLA_INTEGER, NIL), true, false);
    int port = ((IntegerWrapper*)(theoptions->lookupWithDefault(KWD_LOGIC_IN_PORT, wrapInteger(0))))->wrapperValue;
    const char* address = NULL;

    autoload("ONTOSAURUS/CONTROL-PANEL-HANDLER", "ontosaurus", NULL, true);
    address = ((const char*  (*) (int))autoload("HTTP/START-HTTP-SERVER", getHttpServerSystem(), NULL, true))(port);
    plLog(KWD_LOGIC_IN_LOW, 3, wrapString("Started Ontosaurus, point your browser to `"), wrapString(address), wrapString("ploom/ontosaurus/'"));
  }
}

void startOntosaurusEvaluatorWrapper(Cons* arguments) {
  startOntosaurus(arguments);
}

void stopOntosaurus() {
  // Stop the PowerLoom HTTP server and free up any bound ports.
  // This is a no-op if no server is running or the server is not supported.
  ((void  (*) ())autoload("HTTP/STOP-HTTP-SERVER", getHttpServerSystem(), NULL, true))();
}

void startPowerloomServer(Cons* options) {
  // Start the PowerLoom HTTP server at :port (defaults to 9090).  Loads
  // the required support systems in Lisp and Java if necessary (C++ is not yet supported).
  { PropertyList* theoptions = parseLogicCommandOptions(options, listO(3, KWD_LOGIC_IN_PORT, SGT_LOGIC_IN_STELLA_INTEGER, NIL), true, false);
    int port = ((IntegerWrapper*)(theoptions->lookupWithDefault(KWD_LOGIC_IN_PORT, wrapInteger(0))))->wrapperValue;
    const char* address = NULL;

    autoload("GUI-SERVER/GUI-REQUEST-HANDLER", "powerloom-server", NULL, true);
    address = ((const char*  (*) (int))autoload("HTTP/START-HTTP-SERVER", getHttpServerSystem(), NULL, true))(port);
    plLog(KWD_LOGIC_IN_LOW, 3, wrapString("Started PowerLoom server at `"), wrapString(address), wrapString("ploom/soap-rpc/...'"));
  }
}

void startPowerloomServerEvaluatorWrapper(Cons* arguments) {
  startPowerloomServer(arguments);
}

void stopPowerloomServer() {
  // Stop the PowerLoom HTTP server and free up any bound ports.
  // This is a no-op if no server is running or the server is not supported.
  ((void  (*) ())autoload("HTTP/STOP-HTTP-SERVER", getHttpServerSystem(), NULL, true))();
}

void startPowerloomGui(Cons* options) {
  // Start the PowerLoom server at :port (defaults to 9090) and launches
  // the GUI which will communicate with the server at that port.  If :host is specified,
  // the GUI will try to communicate with a server at `host:port' instead of the local
  // embedded server (note, you can always point the GUI manually to a different server
  // from its `Connect to Server' menu item).  Loads the required support systems if necessary.
  // Embedded calls to the GUI are currently only supported in Java; however, when the GUI is
  // run in standalone mode, it can communicate with any PowerLoom installation that supports
  // an HTTP server (currently Lisp and Java).
  { PropertyList* theoptions = parseLogicCommandOptions(options, listO(7, KWD_LOGIC_IN_HOST, SGT_LOGIC_IN_STELLA_STRING, KWD_LOGIC_IN_PORT, SGT_LOGIC_IN_STELLA_INTEGER, KWD_LOGIC_IN_DEBUG_LEVEL, SGT_LOGIC_IN_STELLA_INTEGER, NIL), true, false);
    const char* host = ((StringWrapper*)(theoptions->lookupWithDefault(KWD_LOGIC_IN_HOST, wrapString("localhost"))))->wrapperValue;
    int port = ((IntegerWrapper*)(theoptions->lookupWithDefault(KWD_LOGIC_IN_PORT, wrapInteger(9090))))->wrapperValue;
    int debuglevel = ((IntegerWrapper*)(theoptions->lookupWithDefault(KWD_LOGIC_IN_DEBUG_LEVEL, wrapInteger(1))))->wrapperValue;
    const char* guiclass = "edu.isi.powerloom.gui.components.PowerloomApp";
    cpp_function_code guifn = NULL;
    const char** guifnargs = new (GC)const char*[6];

    {
      {
        host = host;
        port = port;
        debuglevel = debuglevel;
        guiclass = guiclass;
        guifn = guifn;
        guifnargs = guifnargs;
      }
      throw *newLogicException("PowerLoom GUI only available in Java version of PowerLoom");
    }
  }
}

void startPowerloomGuiEvaluatorWrapper(Cons* arguments) {
  startPowerloomGui(arguments);
}

void stopPowerloomGui() {
  // Closes the PowerLoom GUI application if it is currently visible.
  // This is a no-op if the GUI is not running or if it is not supported.
  { const char* guiclass = "edu.isi.powerloom.gui.components.PowerloomApp";
    cpp_function_code exitfn = NULL;

    guiclass = guiclass;
    if (exitfn != NULL) {
      ((void  (*) ())exitfn)();
    }
  }
}

void powerloomGuiExitHook(Object* ignore) {
  // Exit hook to stop the PowerLoom GUI if it is running.
  ignore = ignore;
  try {
    stopPowerloomGui();
  }
  catch (std::exception ) {
  }
}

// Points to the source of the relation being parsed.
DEFINE_STELLA_SPECIAL(oTERMSOURCEBEINGPARSEDo, const char* , NULL);

// Pofints to a description or its parse tree which
// is the input to the description being constructed.
DEFINE_STELLA_SPECIAL(oDESCRIPTIONUNDERCONSTRUCTIONo, Object* , NULL);

// Points to the parse tree which is the input to the
// proposition being constructed.
DEFINE_STELLA_SPECIAL(oTERMUNDERCONSTRUCTIONo, Object* , NULL);

// Limit on how big an s-expression we will print within
// an error message.
int oEXPRESSION_SIZE_CUTOFFo = 300;

void printFormulaContainingError(Object* self, OutputStream* stream) {
  { OutputStringStream* temp = newOutputStringStream();
    const char* expressionstring = NULL;

    *(temp->nativeStream) << self;
    expressionstring = temp->theStringReader();
    if (strlen(expressionstring) > oEXPRESSION_SIZE_CUTOFFo) {
      expressionstring = stringConcatenate(stringSubsequence(expressionstring, 0, oEXPRESSION_SIZE_CUTOFFo), " ......)", 0);
    }
    *(stream->nativeStream) << expressionstring;
  }
}

void helpSignalPropositionError(OutputStream* stream, Keyword* warningorerror) {
  { Object* bestoutputobject = oTERMUNDERCONSTRUCTIONo;
    const char* typenamE = (((boolean)(bestoutputobject)) ? "proposition" : "relation");

    if (!((boolean)(bestoutputobject))) {
      bestoutputobject = oDESCRIPTIONUNDERCONSTRUCTIONo;
    }
    if ((!((boolean)(bestoutputobject))) &&
        (oTERMSOURCEBEINGPARSEDo != NULL)) {
      bestoutputobject = wrapString(oTERMSOURCEBEINGPARSEDo);
    }
    if (((boolean)(bestoutputobject))) {
      *(stream->nativeStream) << "   ";
      if (warningorerror == KWD_LOGIC_IN_ERROR) {
        *(stream->nativeStream) << "Error";
      }
      else if (warningorerror == KWD_LOGIC_IN_WARNING) {
        *(stream->nativeStream) << "Warning";
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << warningorerror << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      *(stream->nativeStream) << " occurred while parsing the " << typenamE << ": ";
      { Surrogate* testValue000 = safePrimaryType(bestoutputobject);

        if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_NAMED_DESCRIPTION)) {
          { Object* bestoutputobject000 = bestoutputobject;
            NamedDescription* bestoutputobject = ((NamedDescription*)(bestoutputobject000));

            *(stream->nativeStream) << relationName(bestoutputobject) << std::endl;
            return;
          }
        }
        else if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_PROPOSITION)) {
          { Object* bestoutputobject001 = bestoutputobject;
            Proposition* bestoutputobject = ((Proposition*)(bestoutputobject001));

            *(stream->nativeStream) << std::endl << "   ";
            printFormulaContainingError(oTERMUNDERCONSTRUCTIONo, stream);
          }
        }
        else if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_DESCRIPTION)) {
          { Object* bestoutputobject002 = bestoutputobject;
            Description* bestoutputobject = ((Description*)(bestoutputobject002));

            *(stream->nativeStream) << std::endl << "   ";
            printFormulaContainingError(oTERMUNDERCONSTRUCTIONo, stream);
          }
        }
        else if (testValue000 == SGT_LOGIC_IN_STELLA_CONS) {
          { Object* bestoutputobject003 = bestoutputobject;
            Cons* bestoutputobject = ((Cons*)(bestoutputobject003));

            *(stream->nativeStream) << std::endl << "   ";
            printFormulaContainingError(oTERMUNDERCONSTRUCTIONo, stream);
          }
        }
        else if (subtypeOfStringP(testValue000)) {
          { Object* bestoutputobject004 = bestoutputobject;
            StringWrapper* bestoutputobject = ((StringWrapper*)(bestoutputobject004));

            *(stream->nativeStream) << std::endl;
            { Object* sexpression = readSExpressionFromString(bestoutputobject->wrapperValue);

              printFormulaContainingError(sexpression, stream);
            }
          }
        }
        else {
        }
      }
      *(stream->nativeStream) << std::endl;
    }
  }
}

Keyword* logicDialect(Object* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_LOGIC_IN_STELLA_RELATION)) {
      { Object* self000 = self;
        Relation* self = ((Relation*)(self000));

        return (logicDialect(self->homeModule()));
      }
    }
    else if (subtypeOfP(testValue000, SGT_LOGIC_IN_STELLA_MODULE)) {
      { Object* self001 = self;
        Module* self = ((Module*)(self001));

        { Keyword* dialect = ((Keyword*)(dynamicSlotValue(self->dynamicSlots, SYM_LOGIC_IN_LOGIC_MODULE_LOGIC_DIALECT, NULL)));

          if (((boolean)(dialect))) {
            return (dialect);
          }
          else {
            return (KWD_LOGIC_IN_KIF);
          }
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

Surrogate* lookupLogicObjectSurrogate(Symbol* name, Module* definitionmodule) {
  definitionmodule = (((boolean)(definitionmodule)) ? definitionmodule : oMODULEo);
  if (explicitlyQualifiedLogicObjectNameP(name, definitionmodule)) {
    return (lookupSurrogateInModule(name->symbolName, ((Module*)(name->homeContext)), true));
  }
  else {
    return (lookupSurrogate(name->symbolName));
  }
}

Surrogate* internLogicObjectSurrogate(Symbol* name) {
  if (!oMODULEo->clearableP_reader()) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "ERROR: " << "Can't define the term " << "`" << name << "'" << " in the unclearable module " << "`" << oMODULEo->moduleFullName << "'" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_LOGIC_IN_ERROR);
      }
      throw *newPropositionError(stream000->theStringReader());
    }
  }
  { Surrogate* oldsurrogate = lookupLogicObjectSurrogate(name, oMODULEo);
    Object* oldvalue = (((boolean)(oldsurrogate)) ? oldsurrogate->surrogateValue : ((Object*)(NULL)));
    Module* oldmodule = (((boolean)(oldvalue)) ? oldvalue->homeModule() : ((Module*)(NULL)));

    if (((boolean)(oldvalue)) &&
        (!(oldmodule == oMODULEo))) {
      if (oWARNIFREDEFINEpo) {
        std::cout << "Defining " << "`" << name << "'" << " would cause a term with the same name" << std::endl << "   of type " << "`" << nameObjectMetaclass(oldvalue) << "'" << " in module " << "`" << oldmodule->moduleFullName << "'" << " to be shadowed." << std::endl;
        std::cout << "CAUTION: Automatic shadowing can be dangerous, because forward " << std::endl << "   references to a shadowed object may be bound to the now shadowed " << std::endl << "   object.  Suggestion: Explicitly shadow the name using" << std::endl << "   DEFMODULE's `:shadow' option." << std::endl;
        if (!(yesOrNoP("Do it anyway? "))) {
          { OutputStringStream* stream001 = newOutputStringStream();

            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              *(stream001->nativeStream) << "ERROR: " << "Couldn't shadow name " << "`" << name << "'" << " in " << "`" << oMODULEo->moduleFullName << "'" << "." << std::endl;
              helpSignalPropositionError(stream001, KWD_LOGIC_IN_ERROR);
            }
            throw *newPropositionError(stream001->theStringReader());
          }
        }
      }
    }
    if (explicitlyQualifiedLogicObjectNameP(name, oMODULEo)) {
      { 
        BIND_STELLA_SPECIAL(oMODULEo, Module*, ((Module*)(name->homeContext)));
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
        return (shadowSurrogate(name->symbolName));
      }
    }
    else {
      return (shadowSurrogate(name->symbolName));
    }
  }
}

const char* nameObjectMetaclass(Object* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_DESCRIPTION)) {
      { Object* self000 = self;
        Description* self = ((Description*)(self000));

        if (classP(self)) {
          return ("concept");
        }
        else if (functionP(self)) {
          return ("function");
        }
        else {
          return ("relation");
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_LOGIC_OBJECT)) {
      { Object* self001 = self;
        LogicObject* self = ((LogicObject*)(self001));

        return ("logic object");
      }
    }
    else {
      return (stringDowncase(self->primaryType()->symbolName));
    }
  }
}

Keyword* logicObjectDefinitionType(Symbol* name, Object* oldobject, Object* newobject) {
  if (!((boolean)(oldobject))) {
    return (KWD_LOGIC_IN_DEFINITION);
  }
  { const char* oldkind = nameObjectMetaclass(oldobject);
    const char* newkind = nameObjectMetaclass(newobject);

    { Surrogate* testValue000 = safePrimaryType(oldobject);

      if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_NAMED_DESCRIPTION)) {
        { Object* oldobject000 = oldobject;
          NamedDescription* oldobject = ((NamedDescription*)(oldobject000));

          if (!(stringEqlP(oldkind, newkind))) {
            { OutputStringStream* stream000 = newOutputStringStream();

              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                *(stream000->nativeStream) << "ERROR: " << "Can't redefine " << "`" << oldkind << "'" << " " << "`" << name << "'" << " with a " << "`" << newkind << "'" << "." << std::endl << "   Explicitly destroy the old object first before you redefine it" << "." << std::endl;
                helpSignalPropositionError(stream000, KWD_LOGIC_IN_ERROR);
              }
              throw *newPropositionError(stream000->theStringReader());
            }
          }
          if (!((oldobject->arity() == ((NamedDescription*)(newobject))->arity()) ||
              ((stringifiedSource(newobject) != NULL) &&
               (stringSearch(stringifiedSource(newobject), "VARIABLE-ARITY", 0) != NULL_INTEGER)))) {
            { OutputStringStream* stream001 = newOutputStringStream();

              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                *(stream001->nativeStream) << "ERROR: " << "Can't redefine " << "`" << oldkind << "'" << " " << "`" << name << "'" << " with a different arity." << std::endl << "   Explicitly destroy the old object first before you redefine it" << "." << std::endl;
                helpSignalPropositionError(stream001, KWD_LOGIC_IN_ERROR);
              }
              throw *newPropositionError(stream001->theStringReader());
            }
          }
          return (KWD_LOGIC_IN_REDEFINITION);
        }
      }
      else if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_LOGIC_OBJECT)) {
        { Object* oldobject001 = oldobject;
          LogicObject* oldobject = ((LogicObject*)(oldobject001));

          { Surrogate* testValue001 = safePrimaryType(newobject);

            if (subtypeOfP(testValue001, SGT_LOGIC_IN_LOGIC_NAMED_DESCRIPTION)) {
              { Object* newobject000 = newobject;
                NamedDescription* newobject = ((NamedDescription*)(newobject000));

                return (KWD_LOGIC_IN_PROPER_DEFINITION);
              }
            }
            else if (subtypeOfP(testValue001, SGT_LOGIC_IN_LOGIC_LOGIC_OBJECT)) {
              { Object* newobject001 = newobject;
                LogicObject* newobject = ((LogicObject*)(newobject001));

                return (KWD_LOGIC_IN_REDEFINITION);
              }
            }
            else {
            }
          }
        }
      }
      else {
        if (oldobject->primaryType() == newobject->primaryType()) {
          return (KWD_LOGIC_IN_REDEFINITION);
        }
      }
    }
    { OutputStringStream* stream002 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream002->nativeStream) << "ERROR: " << "Can't redefine " << "`" << oldkind << "'" << " " << "`" << name << "'" << " with a " << "`" << newkind << "'" << "." << std::endl << "   Explicitly destroy the old object first before you redefine it" << "." << std::endl;
        helpSignalPropositionError(stream002, KWD_LOGIC_IN_ERROR);
      }
      throw *newPropositionError(stream002->theStringReader());
    }
  }
}

void bindLogicObjectToSurrogate(Symbol* name, Object* object) {
  { Surrogate* testValue000 = safePrimaryType(object);

    if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_LOGIC_OBJECT)) {
      { Object* object000 = object;
        LogicObject* object = ((LogicObject*)(object000));

      }
    }
    else if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_PROPOSITION)) {
      { Object* object001 = object;
        Proposition* object = ((Proposition*)(object001));

      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "INTERNAL ERROR: Can't yet define logic objects of type " << "`" << object->primaryType() << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
  { Surrogate* namesurrogate = internLogicObjectSurrogate(name);
    Surrogate* objectsurrogate = objectSurrogate(object);
    Object* oldobject = namesurrogate->surrogateValue;
    Keyword* definitiontype = NULL;

    if (((boolean)(oldobject)) &&
        oldobject->deletedP()) {
      oldobject = NULL;
      namesurrogate->surrogateValue = NULL;
    }
    if (oWARNIFREDEFINEpo &&
        (((boolean)(objectsurrogate)) &&
         (!(objectsurrogate == namesurrogate)))) {
      std::cout << "The " << "`" << nameObjectMetaclass(object) << "'" << " now named " << "`" << name << "'" << " used to be named " << "`" << internSymbolInModule(objectsurrogate->symbolName, ((Module*)(objectsurrogate->homeContext)), false) << "'" << "." << std::endl << "    Unlinking it from its old name." << std::endl;
      objectsurrogate->surrogateValue = NULL;
    }
    objectSurrogateSetter(object, namesurrogate);
    definitiontype = logicObjectDefinitionType(name, oldobject, object);
    namesurrogate->surrogateValue = object;
    if (((boolean)(oldobject)) &&
        (!eqlP(oldobject, object))) {
      objectSurrogateSetter(oldobject, NULL);
    }
    if (definitiontype == KWD_LOGIC_IN_DEFINITION) {
    }
    else if (definitiontype == KWD_LOGIC_IN_PROPER_DEFINITION) {
      transferPropositionsAndBacklinks(oldobject, object);
      { Surrogate* testValue001 = safePrimaryType(oldobject);

        if (subtypeOfP(testValue001, SGT_LOGIC_IN_LOGIC_LOGIC_OBJECT)) {
          { Object* oldobject000 = oldobject;
            LogicObject* oldobject = ((LogicObject*)(oldobject000));

            oldobject->deletedPSetter(true);
          }
        }
        else if (subtypeOfP(testValue001, SGT_LOGIC_IN_LOGIC_PROPOSITION)) {
          { Object* oldobject001 = oldobject;
            Proposition* oldobject = ((Proposition*)(oldobject001));

            oldobject->deletedPSetter(true);
          }
        }
        else {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
            throw *newStellaException(stream001->theStringReader());
          }
        }
      }
    }
    else if (definitiontype == KWD_LOGIC_IN_REDEFINITION) {
      redefineLogicObject(name, oldobject, object);
    }
    else {
      { OutputStringStream* stream002 = newOutputStringStream();

        *(stream002->nativeStream) << "`" << definitiontype << "'" << " is not a valid case option";
        throw *newStellaException(stream002->theStringReader());
      }
    }
  }
}

void redefineLogicObject(Symbol* name, Object* oldobject, Object* newobject) {
  { List* originatedprops = originatedPropositions(oldobject)->removeDeletedMembers();
    List* exceptprops = originatedprops->copy();

    { Proposition* prop = NULL;
      Cons* iter000 = originatedprops->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        prop = ((Proposition*)(iter000->value));
        { Proposition* satellite = NULL;
          Cons* iter001 = prop->satellitePropositions_reader()->theConsList;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            satellite = ((Proposition*)(iter001->value));
            exceptprops->insertNew(satellite);
          }
        }
      }
    }
    if (oWARNIFREDEFINEpo &&
        (!stringEqlP(stringifiedSource(oldobject), stringifiedSource(newobject)))) {
      plLog(KWD_LOGIC_IN_LOW, 4, wrapString("Redefining the "), wrapString(nameObjectMetaclass(oldobject)), wrapString(" named "), name);
    }
    transferSynonyms(oldobject, newobject);
    transferPropositionsExceptFor(oldobject, newobject, exceptprops);
    if (isaP(oldobject, SGT_LOGIC_IN_LOGIC_NAMED_DESCRIPTION)) {
      transferDescriptionExtension(((NamedDescription*)(oldobject)), ((NamedDescription*)(newobject)));
    }
    { Proposition* prop = NULL;
      Cons* iter002 = originatedprops->theConsList;

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        prop = ((Proposition*)(iter002->value));
        destroyProposition(prop);
      }
    }
    if (!(eqlP(oldobject, newobject))) {
      destroyObject(oldobject);
    }
  }
}

boolean oHANDLE_EXPLICITLY_QUALIFIED_LOGIC_OBJECTSpo = true;

boolean explicitlyQualifiedLogicObjectNameP(GeneralizedSymbol* objectname, Module* definitionmodule) {
  if (oHANDLE_EXPLICITLY_QUALIFIED_LOGIC_OBJECTSpo) {
    definitionmodule = (((boolean)(definitionmodule)) ? definitionmodule : oMODULEo);
    return (!visibleFromP(((Module*)(objectname->homeContext)), definitionmodule));
  }
  return (false);
}

Surrogate* coerceToBoundOrLocalSurrogate(GeneralizedSymbol* self) {
  { Surrogate* surrogate = NULL;

    if (explicitlyQualifiedLogicObjectNameP(self, oMODULEo)) {
      { 
        BIND_STELLA_SPECIAL(oMODULEo, Module*, ((Module*)(self->homeContext)));
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
        return (coerceToBoundOrLocalSurrogate(self));
      }
    }
    { Surrogate* testValue000 = safePrimaryType(self);

      if (subtypeOfSurrogateP(testValue000)) {
        { GeneralizedSymbol* self000 = self;
          Surrogate* self = ((Surrogate*)(self000));

          surrogate = self;
        }
      }
      else if (subtypeOfSymbolP(testValue000)) {
        { GeneralizedSymbol* self001 = self;
          Symbol* self = ((Symbol*)(self001));

          surrogate = lookupSurrogateInModule(self->symbolName, ((Module*)(self->homeContext)), false);
          if ((!((boolean)(surrogate))) &&
              (!(((Module*)(self->homeContext)) == oMODULEo))) {
            surrogate = lookupSurrogateInModule(self->symbolName, oMODULEo, false);
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
    if (((boolean)(surrogate)) &&
        ((boolean)(surrogate->surrogateValue))) {
      return (surrogate);
    }
    return (shadowSurrogate(self->symbolName));
  }
}

Cons* axioms(Object* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_LOGIC_OBJECT)) {
      { Object* self000 = self;
        LogicObject* self = ((LogicObject*)(self000));

        return (((Cons*)(dynamicSlotValue(self->dynamicSlots, SYM_LOGIC_IN_LOGIC_OBJECT_AXIOMS, NULL))));
      }
    }
    else if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_PROPOSITION)) {
      { Object* self001 = self;
        Proposition* self = ((Proposition*)(self001));

        return (((Cons*)(dynamicSlotValue(self->dynamicSlots, SYM_LOGIC_IN_LOGIC_PROPOSITION_AXIOMS, NULL))));
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

Object* axiomsSetter(Object* self, Cons* axioms) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_LOGIC_OBJECT)) {
      { Object* self000 = self;
        LogicObject* self = ((LogicObject*)(self000));

        setDynamicSlotValue(self->dynamicSlots, SYM_LOGIC_IN_LOGIC_OBJECT_AXIOMS, axioms, NULL);
      }
    }
    else if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_PROPOSITION)) {
      { Object* self001 = self;
        Proposition* self = ((Proposition*)(self001));

        setDynamicSlotValue(self->dynamicSlots, SYM_LOGIC_IN_LOGIC_PROPOSITION_AXIOMS, axioms, NULL);
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
  return (axioms);
}

void definitionAxiomsHandler(Object* self, StorageSlot* slot, Object* theaxioms) {
  slot = slot;
  if (stringP(theaxioms)) {
    theaxioms = unstringifyInModule(((StringWrapper*)(theaxioms))->wrapperValue, self->homeModule());
  }
  axiomsSetter(self, combineAxiomLists(axioms(self), theaxioms));
}

void definitionHalfRuleHandler(NamedDescription* self, StorageSlot* slot, Object* body) {
  { Keyword* keyword = ((Keyword*)(dynamicSlotValue(slot->dynamicSlots, SYM_LOGIC_IN_STELLA_SLOT_OPTION_KEYWORD, NULL)));
    Symbol* arrow = internSymbolInModule(keyword->symbolName, getStellaModule("PL-KERNEL-KB", true), false);
    Object* newrule = NULL;

    if (!((boolean)(body))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream000->nativeStream) << "ERROR: " << "Missing value for arrow keyword" << "." << std::endl;
          helpSignalPropositionError(stream000, KWD_LOGIC_IN_ERROR);
        }
        throw *newPropositionError(stream000->theStringReader());
      }
    }
    if (stringP(body)) {
      body = unstringifyInModule(((StringWrapper*)(body))->wrapperValue, self->homeModule());
    }
    newrule = completeRuleDefinition(self, body, arrow);
    axiomsSetter(self, combineAxiomLists(axioms(self), newrule));
  }
}

Cons* combineAxiomLists(Cons* oldaxioms, Object* newaxioms) {
  if (!((boolean)(oldaxioms))) {
    oldaxioms = NIL;
  }
  if (!((boolean)(newaxioms))) {
    newaxioms = NIL;
  }
  { Cons* normalizednewaxioms = NIL;

    if (safePrimaryType(newaxioms) == SGT_LOGIC_IN_STELLA_CONS) {
      { Object* newaxioms000 = newaxioms;
        Cons* newaxioms = ((Cons*)(newaxioms000));

        { boolean alwaysP000 = true;

          { Object* elt = NULL;
            Cons* iter000 = newaxioms;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              elt = iter000->value;
              if (!consP(elt)) {
                alwaysP000 = false;
                break;
              }
            }
          }
          if (alwaysP000) {
            {
              normalizednewaxioms = newaxioms;
            }
          }
          else {
            if (newaxioms->value == SYM_LOGIC_IN_STELLA_AND) {
              {
                normalizednewaxioms = newaxioms->rest;
              }
            }
            else {
              {
                normalizednewaxioms = cons(newaxioms, NIL);
              }
            }
          }
        }
      }
    }
    else {
      normalizednewaxioms = cons(newaxioms, NIL);
    }
    return (oldaxioms->concatenate(normalizednewaxioms, 0));
  }
}

Cons* yieldRelationParametersTree(NamedDescription* self, boolean dropfunctionparameterP, boolean typedP) {
  { Cons* parameterlist = NIL;
    Object* parameter = NULL;

    { Symbol* pname = NULL;
      Cons* iter000 = self->ioVariableNames->theConsList;
      Surrogate* ptype = NULL;
      Cons* iter001 = self->ioVariableTypes->theConsList;

      for  (; (!(iter000 == NIL)) &&
                (!(iter001 == NIL)); 
            iter000 = iter000->rest,
            iter001 = iter001->rest) {
        pname = ((Symbol*)(iter000->value));
        ptype = ((Surrogate*)(iter001->value));
        parameter = pname;
        if (typedP &&
            (!(ptype == SGT_LOGIC_IN_STELLA_THING))) {
          parameter = cons(parameter, cons(internSymbolInModule(ptype->symbolName, ((Module*)(ptype->homeContext)), true), NIL));
        }
        parameterlist = cons(parameter, parameterlist);
      }
    }
    if (dropfunctionparameterP &&
        functionDescriptionP(self)) {
      parameterlist = parameterlist->rest;
    }
    return (parameterlist->reverse());
  }
}

Object* completeRuleDefinition(NamedDescription* self, Object* body, Symbol* arrow) {
  { Cons* parameters = yieldRelationParametersTree(self, false, false);

    return (listO(3, SYM_LOGIC_IN_STELLA_FORALL, parameters, cons(cons(arrow, listO(3, cons(self->descriptionName(), parameters->concatenate(NIL, 0)), wrapKifWithForall(body, parameters), NIL)), NIL)));
  }
}

void definitionKeywordAxiomsHandler(Object* self, Symbol* selfname, Keyword* key, Object* value) {
  axiomsSetter(self, combineAxiomLists(axioms(self), helpDefineKeywordAxioms(selfname, key, value)));
}

Cons* helpDefineKeywordAxioms(Symbol* selfname, Keyword* key, Object* value) {
  { Cons* axioms = NIL;
    Symbol* relationname = internSymbol(key->symbolName);

    if (symbolP(value) &&
        stringEqualP(((Symbol*)(value))->symbolName, "TRUE")) {
      axioms = cons(relationname, cons(selfname, NIL));
    }
    else if (symbolP(value) &&
        stringEqualP(((Symbol*)(value))->symbolName, "FALSE")) {
      axioms = listO(3, SYM_LOGIC_IN_STELLA_NOT, cons(relationname, cons(selfname, NIL)), NIL);
    }
    else if (consP(value) &&
        (!getQuotedTree("((SETOFALL KAPPA SETOF LISTOF) \"/LOGIC\")", "/LOGIC")->membP(((Cons*)(value))->value))) {
      { Cons* values = ((Cons*)(value));
        Symbol* selfarg = NULL;

        { Object* val = NULL;
          Cons* iter000 = values;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            val = iter000->value;
            if (symbolP(val) &&
                stringEqualP(((Symbol*)(val))->symbolName, "?SELF")) {
              selfarg = ((Symbol*)(val));
              break;
            }
          }
        }
        if (((boolean)(selfarg))) {
          axioms = cons(relationname, copyConsList(values)->substitute(selfname, selfarg));
        }
        else {
          { Object* val = NULL;
            Cons* iter001 = values;
            Cons* collect000 = NULL;

            for  (; !(iter001 == NIL); 
                  iter001 = iter001->rest) {
              val = iter001->value;
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(cons(relationname, cons(selfname, cons(val, NIL))), NIL);
                  if (axioms == NIL) {
                    axioms = collect000;
                  }
                  else {
                    addConsToEndOfConsList(axioms, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(cons(relationname, cons(selfname, cons(val, NIL))), NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
        }
      }
    }
    else {
      axioms = cons(relationname, cons(selfname, cons(value, NIL)));
    }
    return (axioms);
  }
}

void assertKeywordAxiom(Object* self, Symbol* selfname, Keyword* key, Object* value) {
  { Object* axiom = NULL;
    Cons* iter000 = combineAxiomLists(NIL, helpDefineKeywordAxioms(selfname, key, value));

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      axiom = iter000->value;
      { Cons* props = updateProposition(axiom, KWD_LOGIC_IN_ASSERT_TRUE);

        if (((boolean)(props))) {
          { Proposition* p = NULL;
            Cons* iter001 = props;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              p = ((Proposition*)(iter001->value));
              { Surrogate* testValue000 = safePrimaryType(self);

                if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_LOGIC_OBJECT)) {
                  { Object* self000 = self;
                    LogicObject* self = ((LogicObject*)(self000));

                    linkOriginatedProposition(self, p);
                  }
                }
                else if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_PROPOSITION)) {
                  { Object* self001 = self;
                    Proposition* self = ((Proposition*)(self001));

                    linkOriginatedProposition(self, p);
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

// List of objects whose definitions and/or associated
// axioms and constraints are not yet processed.
List* oUNFINALIZED_OBJECTSo = NULL;

DEFINE_STELLA_SPECIAL(oFINALIZEOBJECTSIMMEDIATELYpo, boolean , false);

void registerUnfinalizedObject(Object* object) {
  { Surrogate* testValue000 = safePrimaryType(object);

    if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_LOGIC_OBJECT)) {
      { Object* object000 = object;
        LogicObject* object = ((LogicObject*)(object000));

        oUNFINALIZED_OBJECTSo->push(object);
      }
    }
    else if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_PROPOSITION)) {
      { Object* object001 = object;
        Proposition* object = ((Proposition*)(object001));

        oUNFINALIZED_OBJECTSo->push(object);
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "INTERNAL ERROR: can't register objects of type " << "`" << object->primaryType() << "'" << " for finalization";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
  if (oFINALIZEOBJECTSIMMEDIATELYpo) {
    finalizeObjects();
  }
}

void cleanupUnfinalizedObjects() {
  oUNFINALIZED_OBJECTSo->removeDeletedMembers();
}

void linkOriginatedProposition(Object* object, Proposition* proposition) {
  { List* propositions = originatedPropositions(object);

    if (nullListP(propositions)) {
      propositions = newList();
      originatedPropositionsSetter(object, propositions);
    }
    propositions->push(proposition);
  }
}

Cons* helpFinalizeObjectAxioms(Cons* theaxioms) {
  if (!((boolean)(theaxioms))) {
    return (NIL);
  }
  else {
    { Cons* propositions = NIL;
      Object* result = NULL;

      { Object* axiom = NULL;
        Cons* iter000 = theaxioms;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          axiom = iter000->value;
          result = updateProposition(axiom, KWD_LOGIC_IN_ASSERT_TRUE);
          { Surrogate* testValue000 = safePrimaryType(result);

            if (testValue000 == SGT_LOGIC_IN_STELLA_CONS) {
              { Object* result000 = result;
                Cons* result = ((Cons*)(result000));

                { Object* r = NULL;
                  Cons* iter001 = result;

                  for (; !(iter001 == NIL); iter001 = iter001->rest) {
                    r = iter001->value;
                    propositions = cons(r, propositions);
                  }
                }
              }
            }
            else if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_PROPOSITION)) {
              { Object* result001 = result;
                Proposition* result = ((Proposition*)(result001));

                propositions = cons(result, propositions);
              }
            }
            else {
              return (NIL);
            }
          }
        }
      }
      return (propositions->reverse());
    }
  }
}

void finalizeObjectAxioms(Object* self) {
  { 
    BIND_STELLA_SPECIAL(oTERMSOURCEBEINGPARSEDo, const char*, NULL);
    BIND_STELLA_SPECIAL(oLOGIC_DIALECTo, Keyword*, KWD_LOGIC_IN_KIF);
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(oASSERTION_MODULEo)) ? oASSERTION_MODULEo : self->homeModule()));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      { Surrogate* testValue000 = safePrimaryType(self);

        if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_LOGIC_OBJECT)) {
          { Object* self000 = self;
            LogicObject* self = ((LogicObject*)(self000));

            oTERMSOURCEBEINGPARSEDo = stringifiedSource(self);
            if (!((boolean)(axioms(self)))) {
              return;
            }
            setDynamicSlotValue(self->dynamicSlots, SYM_LOGIC_IN_STELLA_BADp, TRUE_WRAPPER, NULL);
            { Cons* theaxioms = helpFinalizeObjectAxioms(axioms(self));

              if (theaxioms == NIL) {
                return;
              }
              else {
                { Proposition* p = NULL;
                  Cons* iter000 = theaxioms;

                  for (; !(iter000 == NIL); iter000 = iter000->rest) {
                    p = ((Proposition*)(iter000->value));
                    linkOriginatedProposition(self, p);
                  }
                }
              }
            }
            axiomsSetter(self, NULL);
            setDynamicSlotValue(self->dynamicSlots, SYM_LOGIC_IN_STELLA_BADp, NULL, NULL);
          }
        }
        else if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_PROPOSITION)) {
          { Object* self001 = self;
            Proposition* self = ((Proposition*)(self001));

            oTERMSOURCEBEINGPARSEDo = stringifiedSource(self);
            if (!((boolean)(axioms(self)))) {
              return;
            }
            setDynamicSlotValue(self->dynamicSlots, SYM_LOGIC_IN_STELLA_BADp, TRUE_WRAPPER, NULL);
            { Cons* theaxioms = helpFinalizeObjectAxioms(axioms(self));

              if (theaxioms == NIL) {
                return;
              }
              else {
                { Proposition* p = NULL;
                  Cons* iter001 = theaxioms;

                  for (; !(iter001 == NIL); iter001 = iter001->rest) {
                    p = ((Proposition*)(iter001->value));
                    linkOriginatedProposition(self, p);
                  }
                }
              }
            }
            axiomsSetter(self, NULL);
            setDynamicSlotValue(self->dynamicSlots, SYM_LOGIC_IN_STELLA_BADp, NULL, NULL);
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
}

void checkDescriptionArgumentTypes(NamedDescription* self) {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, self->homeModule());
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    { Surrogate* type = NULL;
      Cons* iter000 = self->ioVariableTypes->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        type = ((Surrogate*)(iter000->value));
        { NamedDescription* clasS = getDescription(type);

          if (!((boolean)(clasS))) {
            { OutputStringStream* stream000 = newOutputStringStream();

              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                *(stream000->nativeStream) << "ERROR: " << "Undefined class " << "`" << type->symbolName << "'" << " appears as argument type" << std::endl << "   in the definition of relation " << "`" << self->descriptionName() << "'" << "." << std::endl << "." << std::endl;
                helpSignalPropositionError(stream000, KWD_LOGIC_IN_ERROR);
              }
              throw *newPropositionError(stream000->theStringReader());
            }
          }
          if (!classDescriptionP(clasS)) {
            std::cout << "Non-class " << "`" << type->symbolName << "'" << " appears as argument type" << std::endl << "in the definition of relation " << "`" << self->descriptionName() << "'" << "." << std::endl << std::endl;
          }
        }
      }
    }
  }
}

void finalizeObject(Object* self) {
  if (self->deletedP() ||
      finalizedObjectP(self)) {
    return;
  }
  try {
    { Surrogate* testValue000 = safePrimaryType(self);

      if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_NAMED_DESCRIPTION)) {
        { Object* self000 = self;
          NamedDescription* self = ((NamedDescription*)(self000));

          { boolean testValue001 = false;

            if (coerceWrappedBooleanToBoolean(self->badP_reader())) {
              testValue001 = true;
            }
            else {
              { boolean foundP000 = false;

                { Surrogate* type = NULL;
                  Cons* iter000 = self->ioVariableTypes->theConsList;

                  for (; !(iter000 == NIL); iter000 = iter000->rest) {
                    type = ((Surrogate*)(iter000->value));
                    if (type->symbolId == -1) {
                      foundP000 = true;
                      break;
                    }
                  }
                }
                testValue001 = foundP000;
              }
            }
            if (testValue001) {
              return;
            }
          }
          finalizeObjectAxioms(self);
          checkDescriptionArgumentTypes(self);
        }
      }
      else if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_LOGIC_OBJECT)) {
        { Object* self001 = self;
          LogicObject* self = ((LogicObject*)(self001));

          if (coerceWrappedBooleanToBoolean(self->badP_reader())) {
            return;
          }
          finalizeObjectAxioms(self);
        }
      }
      else if (subtypeOfP(testValue000, SGT_LOGIC_IN_LOGIC_PROPOSITION)) {
        { Object* self002 = self;
          Proposition* self = ((Proposition*)(self002));

          if (coerceWrappedBooleanToBoolean(self->badP_reader())) {
            return;
          }
          finalizeObjectAxioms(self);
        }
      }
      else {
      }
    }
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
  }
}

boolean finalizedObjectP(Object* self) {
  return (!((boolean)(axioms(self))));
}

boolean objectsAreFinalizedP() {
  return (oUNFINALIZED_OBJECTSo->theConsList == NIL);
}

// Used to prevent finalization from triggering in the
// middle of 'delicate' computations.  Also used to prevent recursive
// invocation of 'finalize-objects'.
DEFINE_STELLA_SPECIAL(oINHIBITOBJECTFINALIZATIONpo, boolean , false);

void finalizeObjects() {
  // Finalize all currently unfinalized objects.
  // The user-level entry point for this is `(process-definitions)'.
  if (oINHIBITOBJECTFINALIZATIONpo ||
      ((oUNFINALIZED_OBJECTSo->theConsList == NIL) ||
       (!worldStateP(oCONTEXTo)))) {
    return;
  }
  { 
    BIND_STELLA_SPECIAL(oINHIBITOBJECTFINALIZATIONpo, boolean, true);
    BIND_STELLA_SPECIAL(oTERMSOURCEBEINGPARSEDo, const char*, NULL);
    BIND_STELLA_SPECIAL(oDESCRIPTIONUNDERCONSTRUCTIONo, Object*, NULL);
    BIND_STELLA_SPECIAL(oTERMUNDERCONSTRUCTIONo, Object*, NULL);
    finalizeClassesAndSlots();
    { Object* object = NULL;
      Cons* iter000 = oUNFINALIZED_OBJECTSo->reverse()->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        object = iter000->value;
        finalizeObject(object);
      }
    }
    oUNFINALIZED_OBJECTSo->clear();
  }
}

NamedDescription* helpDefineRelationFromParseTree(Cons* tree, const char* stringifiedsource) {
  { Symbol* operatoR = ((Symbol*)(tree->value));
    Symbol* name = ((Symbol*)(tree->rest->value));
    Cons* parameters = ((Cons*)(tree->rest->rest->value));
    Cons* options = tree->nthRest(3);
    boolean classP = operatoR == SYM_LOGIC_IN_LOGIC_DEFCONCEPT;
    boolean functionP = operatoR == SYM_LOGIC_IN_LOGIC_DEFFUNCTION;
    NamedDescription* description = NULL;

    description = getIdenticalRelation(name, stringifiedsource);
    if (((boolean)(description))) {
      return (description);
    }
    { List* parameternames = NULL;
      List* parametertypes = NULL;
      boolean variablearityP = false;

      parameternames = parseRelationParametersTree(parameters, parametertypes, variablearityP);
      description = createPrimitiveDescription(parameternames, parametertypes, variablearityP, classP, functionP, oMODULEo);
      oDESCRIPTIONUNDERCONSTRUCTIONo = description;
      stringifiedSourceSetter(description, stringifiedsource);
      setDynamicSlotValue(description->dynamicSlots, SYM_LOGIC_IN_STELLA_BADp, TRUE_WRAPPER, NULL);
      bindLogicObjectToSurrogate(name, description);
      ensureDescriptionBody(description);
      description->processDefinitionOptions(options);
      setDynamicSlotValue(description->dynamicSlots, SYM_LOGIC_IN_STELLA_BADp, NULL, NULL);
      registerUnfinalizedObject(description);
      return (description);
    }
  }
}

List* parseRelationParametersTree(Cons* parameters, List*& _Return1, boolean& _Return2) {
  if (!((boolean)(parameters))) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "ERROR: " << "Missing concept or relation parameters" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_LOGIC_IN_ERROR);
      }
      throw *newPropositionError(stream000->theStringReader());
    }
  }
  { Symbol* name = NULL;
    Object* type = NULL;
    List* parameternames = newList();
    List* parametertypes = newList();
    boolean variablearityP = false;

    { Object* p = NULL;
      Cons* iter000 = parameters;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        p = iter000->value;
        { Surrogate* testValue000 = safePrimaryType(p);

          if (testValue000 == SGT_LOGIC_IN_STELLA_CONS) {
            { Object* p000 = p;
              Cons* p = ((Cons*)(p000));

              if (!((p->length() == 2) &&
                  (symbolP(p->value) &&
                   symbolP(p->rest->value)))) {
                { OutputStringStream* stream001 = newOutputStringStream();

                  { 
                    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                    *(stream001->nativeStream) << "ERROR: " << "Illegal parameter: " << "`" << p << "'" << "." << std::endl;
                    helpSignalPropositionError(stream001, KWD_LOGIC_IN_ERROR);
                  }
                  throw *newPropositionError(stream001->theStringReader());
                }
              }
              name = ((Symbol*)(p->value));
              if (!questionMarkSymbolP(name)) {
                { OutputStringStream* stream002 = newOutputStringStream();

                  { 
                    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                    *(stream002->nativeStream) << "ERROR: " << "Expected a question mark variable: " << "`" << name << "'" << "." << std::endl;
                    helpSignalPropositionError(stream002, KWD_LOGIC_IN_ERROR);
                  }
                  throw *newPropositionError(stream002->theStringReader());
                }
              }
              type = p->rest->value;
            }
          }
          else if (subtypeOfSymbolP(testValue000)) {
            { Object* p001 = p;
              Symbol* p = ((Symbol*)(p001));

              name = p;
              if (!questionMarkSymbolP(name)) {
                { OutputStringStream* stream003 = newOutputStringStream();

                  { 
                    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                    *(stream003->nativeStream) << "ERROR: " << "Expected a question mark variable: " << "`" << name << "'" << "." << std::endl;
                    helpSignalPropositionError(stream003, KWD_LOGIC_IN_ERROR);
                  }
                  throw *newPropositionError(stream003->theStringReader());
                }
              }
              type = SGT_LOGIC_IN_STELLA_THING;
            }
          }
          else {
            { OutputStringStream* stream004 = newOutputStringStream();

              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                *(stream004->nativeStream) << "ERROR: " << "Illegal parameter: " << "`" << p << "'" << "." << std::endl;
                helpSignalPropositionError(stream004, KWD_LOGIC_IN_ERROR);
              }
              throw *newPropositionError(stream004->theStringReader());
            }
          }
        }
        if (sequenceVariableSymbolP(name)) {
          variablearityP = true;
        }
        if (parameternames->memberP(name)) {
          { OutputStringStream* stream005 = newOutputStringStream();

            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              *(stream005->nativeStream) << "ERROR: " << "Duplicate relation parameter name: " << "`" << name << "'" << "." << std::endl;
              helpSignalPropositionError(stream005, KWD_LOGIC_IN_ERROR);
            }
            throw *newPropositionError(stream005->theStringReader());
          }
        }
        parameternames->push(name);
        parametertypes->push(coerceToBoundOrLocalSurrogate(((GeneralizedSymbol*)(type))));
        if (variablearityP) {
          break;
        }
      }
    }
    if (!((boolean)(parametertypes))) {
      { OutputStringStream* stream006 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream006->nativeStream) << "ERROR: " << "Missing relation parameter list" << "." << std::endl;
          helpSignalPropositionError(stream006, KWD_LOGIC_IN_ERROR);
        }
        throw *newPropositionError(stream006->theStringReader());
      }
    }
    if (parametertypes->emptyP()) {
      { OutputStringStream* stream007 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream007->nativeStream) << "ERROR: " << "Empty relation parameter list" << "." << std::endl;
          helpSignalPropositionError(stream007, KWD_LOGIC_IN_ERROR);
        }
        throw *newPropositionError(stream007->theStringReader());
      }
    }
    { List* _Return0 = parameternames->reverse();

      _Return1 = parametertypes->reverse();
      _Return2 = variablearityP;
      return (_Return0);
    }
  }
}

NamedDescription* getIdenticalRelation(Symbol* name, const char* stringifiedsource) {
  { Surrogate* surrogate = lookupLogicObjectSurrogate(name, oMODULEo);
    Object* surrogatevalue = (((boolean)(surrogate)) ? surrogate->surrogateValue : ((Object*)(NULL)));
    NamedDescription* description = NULL;

    if (((boolean)(surrogatevalue)) &&
        isaP(surrogatevalue, SGT_LOGIC_IN_LOGIC_NAMED_DESCRIPTION)) {
      description = ((NamedDescription*)(surrogatevalue));
    }
    if (((boolean)(description))) {
      if ((!coerceWrappedBooleanToBoolean(description->badP_reader())) &&
          stringEqlP(stringifiedSource(description), stringifiedsource)) {
        return (description);
      }
    }
    return (NULL);
  }
}

void NamedDescription::processDefinitionOptions(Object* options) {
  { NamedDescription* self = this;

    { Object* key = NULL;
      Object* value = NULL;
      Cons* iter000 = vetOptions(options, NULL)->thePlist;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest->rest) {
        key = iter000->value;
        value = iter000->rest->value;
        if (!runOptionHandlerP(self, ((Keyword*)(key)), value)) {
          definitionKeywordAxiomsHandler(self, self->descriptionName(), ((Keyword*)(key)), value);
        }
      }
    }
    if (!(classP(self))) {
      { Symbol* name = self->descriptionName();
        Vector* iovariables = self->ioVariables;
        List* iovariabletypes = self->ioVariableTypes;
        Cons* theaxioms = axioms(self);
        Cons* typedarguments = NIL;
        Object* operatoR = NULL;
        Object* firstarg = NULL;
        Cons* argumenttypeaxioms = NIL;

        if (((boolean)(theaxioms)) &&
            iovariabletypes->membP(SGT_LOGIC_IN_STELLA_THING)) {
          { Object* axiom = NULL;
            Cons* iter001 = theaxioms;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              axiom = iter001->value;
              if (safePrimaryType(axiom) == SGT_LOGIC_IN_STELLA_CONS) {
                { Object* axiom000 = axiom;
                  Cons* axiom = ((Cons*)(axiom000));

                  operatoR = axiom->value;
                  firstarg = axiom->rest->value;
                  if ((operatoR == SYM_LOGIC_IN_PL_KERNEL_KB_NTH_DOMAIN) &&
                      ((firstarg == name) &&
                       integerP(axiom->rest->rest->value))) {
                    typedarguments = cons(((PatternVariable*)((iovariables->theArray)[(((IntegerWrapper*)(axiom->rest->rest->value))->wrapperValue)])), typedarguments);
                  }
                  else if ((operatoR == SYM_LOGIC_IN_PL_KERNEL_KB_DOMAIN) &&
                      (firstarg == name)) {
                    typedarguments = cons(((PatternVariable*)((iovariables->theArray)[0])), typedarguments);
                  }
                  else if ((operatoR == SYM_LOGIC_IN_PL_KERNEL_KB_RANGE) &&
                      (firstarg == name)) {
                    typedarguments = cons(((PatternVariable*)(iovariables->last())), typedarguments);
                  }
                }
              }
              else {
              }
            }
          }
        }
        { Surrogate* type = NULL;
          Cons* iter002 = iovariabletypes->theConsList;
          PatternVariable* var = NULL;
          Vector* vector000 = iovariables;
          int index000 = 0;
          int length000 = vector000->length();
          int i = NULL_INTEGER;
          int iter003 = 0;
          Cons* collect000 = NULL;

          for  (; (!(iter002 == NIL)) &&
                    (index000 < length000); 
                iter002 = iter002->rest,
                index000 = index000 + 1,
                iter003 = iter003 + 1) {
            type = ((Surrogate*)(iter002->value));
            var = ((PatternVariable*)((vector000->theArray)[index000]));
            i = iter003;
            if (((boolean)(type)) &&
                ((!(type == SGT_LOGIC_IN_STELLA_THING)) ||
                 (!typedarguments->membP(var)))) {
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(listO(3, SYM_LOGIC_IN_PL_KERNEL_KB_NTH_DOMAIN, name, cons(wrapInteger(i), cons(internSymbolInModule(type->symbolName, ((Module*)(type->homeContext)), false), NIL))), NIL);
                  if (argumenttypeaxioms == NIL) {
                    argumenttypeaxioms = collect000;
                  }
                  else {
                    addConsToEndOfConsList(argumenttypeaxioms, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(listO(3, SYM_LOGIC_IN_PL_KERNEL_KB_NTH_DOMAIN, name, cons(wrapInteger(i), cons(internSymbolInModule(type->symbolName, ((Module*)(type->homeContext)), false), NIL))), NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
        }
        if (!(argumenttypeaxioms == NIL)) {
          axiomsSetter(self, combineAxiomLists(argumenttypeaxioms, theaxioms));
        }
      }
    }
  }
}

NamedDescription* deffunction(Cons* args) {
  // Define (or redefine) a logic function.  The accepted syntax is:
  // 	 
  //  (deffunction <funconst> (<vardecl>+) [:-> <vardecl>]
  //     [:documentation <string>]
  //     [:<= <sentence>] | [:=> <sentence>] |
  //     [:<<= <sentence>] | [:=>> <sentence>] | 
  //     [:<=> <sentence>] | [:<=>> <sentence>] |
  //     [:<<=> <sentence>] | [:<<=>> <sentence>] |
  //     [:axioms {<sentence> | (<sentence>+)}]
  //     [<keyword-option>*])
  // 	
  // Function parameters can be typed or untyped.  If the `:->' option is
  // supplied, it specifies the output variable of the function.  Otherwise,
  // the last variable in the parameter list is used as the output variable.
  // See `defrelation' for a description of `<keyword-option>'s.
  // 
  try {
    return (callDeffunction(args));
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
    return (NULL);
  }
}

NamedDescription* deffunctionEvaluatorWrapper(Cons* arguments) {
  return (deffunction(arguments));
}

NamedDescription* callDeffunction(Cons* arguments) {
  // Callable version of the `deffunction' command (which see).
  // Expects the same arguments as `deffunction' but supplied as a list.
  { Cons* definition = cons(SYM_LOGIC_IN_LOGIC_DEFFUNCTION, arguments->concatenate(NIL, 0));

    { 
      BIND_STELLA_SPECIAL(oTERMSOURCEBEINGPARSEDo, const char*, stringify(definition));
      BIND_STELLA_SPECIAL(oDESCRIPTIONUNDERCONSTRUCTIONo, Object*, NULL);
      definition->rest = normalizeDeffunctionArguments(arguments);
      internLogicObjectSurrogate(((Symbol*)(definition->rest->value)));
      return (helpDefineRelationFromParseTree(definition, oTERMSOURCEBEINGPARSEDo));
    }
  }
}

Cons* normalizeDeffunctionArguments(Cons* arguments) {
  { Object* name = arguments->value;
    Object* parameters = arguments->rest->value;
    Cons* options = arguments->rest->rest;

    if (!(symbolP(name))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream000->nativeStream) << "ERROR: " << "Illegal function name where symbol expected: " << "`" << name << "'" << "." << std::endl;
          helpSignalPropositionError(stream000, KWD_LOGIC_IN_ERROR);
        }
        throw *newPropositionError(stream000->theStringReader());
      }
    }
    if (safePrimaryType(parameters) == SGT_LOGIC_IN_STELLA_CONS) {
      { Object* parameters000 = parameters;
        Cons* parameters = ((Cons*)(parameters000));

        while (!(options == NIL)) {
          if ((options->value == KWD_LOGIC_IN__g) &&
              ((boolean)(options->rest->value))) {
            parameters = parameters->concatenate(cons(options->rest->value, NIL), 0);
            arguments->secondSetter(parameters);
            options->firstSetter(NULL);
            options->secondSetter(NULL);
            options = arguments->rest->rest->remove(NULL);
            arguments->rest->rest = options;
            break;
          }
          options = options->rest->rest;
        }
        if (parameters == NIL) {
          { OutputStringStream* stream001 = newOutputStringStream();

            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              *(stream001->nativeStream) << "ERROR: " << "Cannot have 0-arity functions" << "." << std::endl;
              helpSignalPropositionError(stream001, KWD_LOGIC_IN_ERROR);
            }
            throw *newPropositionError(stream001->theStringReader());
          }
        }
      }
    }
    else {
      { OutputStringStream* stream002 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream002->nativeStream) << "ERROR: " << "Illegal parameter list: " << "`" << parameters << "'" << "." << std::endl;
          helpSignalPropositionError(stream002, KWD_LOGIC_IN_ERROR);
        }
        throw *newPropositionError(stream002->theStringReader());
      }
    }
    return (arguments);
  }
}

NamedDescription* defrelation(Cons* args) {
  // Define (or redefine) a logic relation.  The accepted syntax is:
  // 	 
  //  (defrelation <relconst> (<vardecl>+)
  //     [:documentation <string>]
  //     [:<= <sentence>] | [:=> <sentence>] |
  //     [:<<= <sentence>] | [:=>> <sentence>] | 
  //     [:<=> <sentence>] | [:<=>> <sentence>] |
  //     [:<<=> <sentence>] | [:<<=>> <sentence>] |
  //     [:axioms {<sentence> | (<sentence>+)}]
  //     [<keyword-option>*])
  // 	
  // Relation parameters can be typed or untyped.
  // `<keyword-option>' represents a keyword followed by a value that states an
  // assertion about `<relconst>'.  For example, including the option `:foo bar'
  // states that the proposition `(foo <relconst> bar)' is true.  `:foo (bar fum)'
  // states that both `(foo <relconst> bar)' and `(foo <relconst> fum)' are true.
  // `:foo true' states that `(foo <relconst>)' is true, `:foo false' states that
  // `(not (foo <relconst>))' is true.
  // 
  try {
    return (callDefrelation(args));
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
    return (NULL);
  }
}

NamedDescription* defrelationEvaluatorWrapper(Cons* arguments) {
  return (defrelation(arguments));
}

NamedDescription* callDefrelation(Cons* arguments) {
  // Callable version of the `defrelation' command (which see).
  // Expects the same arguments as `defrelation' but supplied as a list.
  { Cons* definition = cons(SYM_LOGIC_IN_LOGIC_DEFRELATION, arguments->concatenate(NIL, 0));

    { 
      BIND_STELLA_SPECIAL(oTERMSOURCEBEINGPARSEDo, const char*, stringify(definition));
      BIND_STELLA_SPECIAL(oDESCRIPTIONUNDERCONSTRUCTIONo, Object*, NULL);
      definition->rest = normalizeDefrelationArguments(arguments);
      internLogicObjectSurrogate(((Symbol*)(definition->rest->value)));
      return (helpDefineRelationFromParseTree(definition, oTERMSOURCEBEINGPARSEDo));
    }
  }
}

Cons* normalizeDefrelationArguments(Cons* arguments) {
  { Object* name = arguments->value;
    Object* parameters = arguments->rest->value;
    Cons* options = arguments->rest->rest;

    if (!(symbolP(name))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream000->nativeStream) << "ERROR: " << "Illegal relation name where symbol expected: " << "`" << name << "'" << "." << std::endl;
          helpSignalPropositionError(stream000, KWD_LOGIC_IN_ERROR);
        }
        throw *newPropositionError(stream000->theStringReader());
      }
    }
    if (!(consP(parameters))) {
      { OutputStringStream* stream001 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream001->nativeStream) << "ERROR: " << "Illegal parameter list: " << "`" << parameters << "'" << "." << std::endl;
          helpSignalPropositionError(stream001, KWD_LOGIC_IN_ERROR);
        }
        throw *newPropositionError(stream001->theStringReader());
      }
    }
    if (((Cons*)(parameters)) == NIL) {
      { OutputStringStream* stream002 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream002->nativeStream) << "ERROR: " << "Cannot have 0-arity relations" << "." << std::endl;
          helpSignalPropositionError(stream002, KWD_LOGIC_IN_ERROR);
        }
        throw *newPropositionError(stream002->theStringReader());
      }
    }
    if (options->memberP(KWD_LOGIC_IN__g)) {
      { OutputStringStream* stream003 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream003->nativeStream) << "ERROR: " << "'defrelation' does not allow a return value (':->') clause" << "." << std::endl;
          helpSignalPropositionError(stream003, KWD_LOGIC_IN_ERROR);
        }
        throw *newPropositionError(stream003->theStringReader());
      }
    }
    return (arguments);
  }
}

NamedDescription* defconcept(Cons* args) {
  // Define (or redefine) a concept.  The accepted syntax is:
  // 	 
  //  (defconcept <conceptconst> [(<var> <parent>*)]
  //     [:documentation <string>]
  //     [:<= <sentence>] | [:=> <sentence>] |
  //     [:<<= <sentence>] | [:=>> <sentence>] | 
  //     [:<=> <sentence>] | [:<=>> <sentence>] | [:<<=> <sentence>] |
  //     [:<<=>> <sentence>] |
  //     [:axioms {<sentence> | (<sentence>+)}] |
  //     <keyword-option>*)
  // 	
  // Declaration of a concept variable `<var>' is optional, unless any
  // implication (arrow) options are supplied that need to reference it.  A
  // possibly empty list of concept names following `<var>' is taken as the list
  // of parents of `<conceptconst>'.  Alternatively, parents can be specified
  // via the `:=>' option.  If no parents are specified, the parent of
  // `<conceptconst>' is taken to be THING.  `<keyword-option>' represents a
  // keyword followed by a value that states an assertion about `<conceptconst>'.
  // See `defrelation' for a description of `<keyword-option>'s.
  // 
  try {
    return (callDefconcept(args));
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
    return (NULL);
  }
}

NamedDescription* defconceptEvaluatorWrapper(Cons* arguments) {
  return (defconcept(arguments));
}

NamedDescription* callDefconcept(Cons* arguments) {
  // Callable version of the `defconcept' command (which see).
  // Expects the same arguments as `defconcept' but supplied as a list.
  { Cons* definition = cons(SYM_LOGIC_IN_LOGIC_DEFCONCEPT, arguments->concatenate(NIL, 0));

    { 
      BIND_STELLA_SPECIAL(oTERMSOURCEBEINGPARSEDo, const char*, stringify(definition));
      BIND_STELLA_SPECIAL(oDESCRIPTIONUNDERCONSTRUCTIONo, Object*, NULL);
      definition->rest = normalizeDefconceptArguments(arguments);
      internLogicObjectSurrogate(((Symbol*)(definition->rest->value)));
      return (helpDefineRelationFromParseTree(definition, oTERMSOURCEBEINGPARSEDo));
    }
  }
}

Cons* normalizeDefconceptArguments(Cons* arguments) {
  { Object* name = arguments->value;
    Cons* parameters = NULL;
    Symbol* selfvariable = SYM_LOGIC_IN_LOGIC_pSELF;
    Cons* supers = NIL;
    Cons* impliesrules = NIL;

    if (!(symbolP(name))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream000->nativeStream) << "ERROR: " << "Illegal concept name where symbol expected: " << "`" << name << "'" << "." << std::endl;
          helpSignalPropositionError(stream000, KWD_LOGIC_IN_ERROR);
        }
        throw *newPropositionError(stream000->theStringReader());
      }
    }
    if (consP(arguments->rest->value)) {
      parameters = ((Cons*)(arguments->rest->value));
    }
    if (((boolean)(parameters))) {
      if (consP(parameters->value)) {
        parameters = ((Cons*)(parameters->value));
      }
      if (parameters == NIL) {
        supers = NIL;
      }
      else if (questionMarkSymbolP(parameters->value)) {
        selfvariable = ((Symbol*)(parameters->value));
        supers = parameters->rest;
      }
      else if (symbolP(parameters->value)) {
        supers = parameters;
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream001->nativeStream) << "ERROR: " << "Illegal parameter list: " << "`" << arguments->rest->value << "'" << "." << std::endl;
            helpSignalPropositionError(stream001, KWD_LOGIC_IN_ERROR);
          }
          throw *newPropositionError(stream001->theStringReader());
        }
      }
      { Object* super = NULL;
        Cons* iter000 = supers;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          super = iter000->value;
          impliesrules = cons(KWD_LOGIC_IN_eg, impliesrules);
          impliesrules = cons(cons(super, cons(selfvariable, NIL)), impliesrules);
        }
      }
      impliesrules = impliesrules->reverse();
      arguments->rest = cons(cons(cons(selfvariable, cons(name, NIL)), NIL), impliesrules->concatenate(arguments->rest->rest->concatenate(NIL, 0), 0));
    }
    else if (arguments->rest == NIL) {
      arguments->rest = cons(cons(cons(selfvariable, cons(name, NIL)), NIL), NIL);
    }
    else if (keywordP(arguments->rest->value)) {
      arguments->rest->rest = cons(arguments->rest->value, arguments->rest->rest->concatenate(NIL, 0));
      arguments->secondSetter(cons(cons(selfvariable, cons(name, NIL)), NIL));
    }
    return (arguments);
  }
}

NamedDescription* defineRelationFromParseTree(Cons* tree) {
  { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

    if (testValue000 == SYM_LOGIC_IN_LOGIC_DEFCONCEPT) {
      return (callDefconcept(tree->rest));
    }
    else if (testValue000 == SYM_LOGIC_IN_LOGIC_DEFRELATION) {
      return (callDefrelation(tree->rest));
    }
    else if (testValue000 == SYM_LOGIC_IN_LOGIC_DEFFUNCTION) {
      return (callDeffunction(tree->rest));
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

LogicObject* defobject(Cons* args) {
  // Define (or redefine) a logic instance.  The accepted syntax is:
  // 	 
  //  (defobject <constant>
  //     [:documentation <string>]
  //     [<keyword-option>*])
  // 	
  // `<keyword-option>' represents a keyword followed by a value
  // that states an assertion about <constant>.  See `defrelation' for a
  // description of `<keyword-option>'s.
  // 
  // `defobject' provides a sugar-coated way to assert a collection of facts
  // about a logic constant, but otherwise adds nothing in terms of functionality.
  // 
  try {
    return (callDefobject(args));
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
    return (NULL);
  }
}

LogicObject* defobjectEvaluatorWrapper(Cons* arguments) {
  return (defobject(arguments));
}

LogicObject* definstance(Cons* args) {
  // Define (or redefine) a logic instance (`definstance' is an alias
  // for `defobject' which see).
  try {
    return (callDefobject(args));
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
    return (NULL);
  }
}

LogicObject* definstanceEvaluatorWrapper(Cons* arguments) {
  return (definstance(arguments));
}

LogicObject* callDefobject(Cons* arguments) {
  // Callable version of the `defobject' command (which see).
  // Expects the same arguments as `defobject' but supplied as a list.
  { Cons* definition = cons(SYM_LOGIC_IN_LOGIC_DEFOBJECT, arguments->concatenate(NIL, 0));
    Symbol* name = NULL;
    Cons* options = NIL;
    Object* term = NULL;

    { 
      BIND_STELLA_SPECIAL(oTERMSOURCEBEINGPARSEDo, const char*, stringify(definition));
      arguments = normalizeDefobjectArguments(arguments);
      options = arguments->rest;
      if (consP(arguments->value)) {
        name = internSymbol(stringify(arguments->value));
        term = conceiveTerm(arguments->value);
        if (!((boolean)(term))) {
          { OutputStringStream* stream000 = newOutputStringStream();

            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              *(stream000->nativeStream) << "ERROR: " << "Illegal object name or term: " << "`" << name << "'" << "." << std::endl;
              helpSignalPropositionError(stream000, KWD_LOGIC_IN_ERROR);
            }
            throw *newPropositionError(stream000->theStringReader());
          }
        }
      }
      else {
        name = ((Symbol*)(arguments->value));
        internLogicObjectSurrogate(name);
        term = createLogicInstance(NULL, NULL);
      }
      if (subtypeOfP(safePrimaryType(term), SGT_LOGIC_IN_LOGIC_LOGIC_OBJECT)) {
        { Object* term000 = term;
          LogicObject* term = ((LogicObject*)(term000));

          stringifiedSourceSetter(term, oTERMSOURCEBEINGPARSEDo);
          bindLogicObjectToSurrogate(name, term);
          term->processDefinitionOptions(options);
          registerUnfinalizedObject(term);
        }
      }
      else {
        bindLogicObjectToSurrogate(name, term);
        { 
          BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(oASSERTION_MODULEo)) ? oASSERTION_MODULEo : oMODULEo));
          BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
          { Object* key = NULL;
            Object* value = NULL;
            Cons* iter000 = vetOptions(options, NULL)->thePlist;

            for  (; !(iter000 == NIL); 
                  iter000 = iter000->rest->rest) {
              key = iter000->value;
              value = iter000->rest->value;
              assertKeywordAxiom(term, name, ((Keyword*)(key)), value);
            }
          }
        }
      }
      return (((LogicObject*)(term)));
    }
  }
}

Cons* normalizeDefobjectArguments(Cons* arguments) {
  { Object* name = arguments->value;
    Cons* options = arguments->rest;

    if (!(symbolP(name) ||
        consP(name))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream000->nativeStream) << "ERROR: " << "Illegal object name where symbol or function term expected: " << "`" << name << "'" << "." << std::endl;
          helpSignalPropositionError(stream000, KWD_LOGIC_IN_ERROR);
        }
        throw *newPropositionError(stream000->theStringReader());
      }
    }
    options = options;
    return (arguments);
  }
}

void LogicObject::processDefinitionOptions(Object* options) {
  { LogicObject* self = this;

    { Object* key = NULL;
      Object* value = NULL;
      Cons* iter000 = vetOptions(options, NULL)->thePlist;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest->rest) {
        key = iter000->value;
        value = iter000->rest->value;
        if (!runOptionHandlerP(self, ((Keyword*)(key)), value)) {
          definitionKeywordAxiomsHandler(self, objectName(self), ((Keyword*)(key)), value);
        }
      }
    }
  }
}

Proposition* defproposition(Cons* args) {
  // Define (or redefine) a named proposition.  The accepted syntax is:
  // 	 
  //  (defproposition <name> <sentence>
  //     [:documentation <string>]
  //     [:forward-only? {true | false}]
  //     [:backward-only? {true | false}]
  //     [:dont-optimize? {true | false}]
  //     [:confidence-level {:strict | :default}]
  //     [<keyword-option>*])
  // 	
  // <sentence> can be any sentence that is legal as a top-level assertion.
  // <name> can be a string or symbol and will be bound to the asserted
  // proposition represented by <sentence>.  After this definition every
  // occurrence of <name> will be replaced by the associated proposition.
  // 
  // The options :forward-only? and :backward-only? can be used to tell the
  // inference engine to only use the rule in forward or backward direction
  // (this can also be achieved by using the `<<=' or `=>>' implication
  // arrows).  :dont-optimize?  tells the inference engine to not rearrange
  // the order of clauses in the antecedent of a rule and instead evaluate
  // them in their original order.  :confidence-level can be used to mark a
  // proposition as default only.
  // 
  // `<keyword-option>' represents a keyword followed by a value
  // that states an assertion about the proposition <name>.  See `defrelation'
  // for a description of `<keyword-option>'s.
  // 
  try {
    return (callDefproposition(args));
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
    return (NULL);
  }
}

Proposition* defpropositionEvaluatorWrapper(Cons* arguments) {
  return (defproposition(arguments));
}

Proposition* defrule(Cons* args) {
  // Define (or redefine) a named rule (`defrule' is an alias
  // for `defproposition' which see).
  try {
    return (callDefproposition(args));
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
    return (NULL);
  }
}

Proposition* defruleEvaluatorWrapper(Cons* arguments) {
  return (defrule(arguments));
}

Proposition* callDefproposition(Cons* arguments) {
  // Callable version of the `defproposition' command (which see).
  // Expects the same arguments as `defproposition' but supplied as a list.
  { Cons* definition = cons(SYM_LOGIC_IN_LOGIC_DEFPROPOSITION, arguments->concatenate(NIL, 0));
    Symbol* name = NULL;
    Cons* options = NIL;
    Object* conception = NULL;
    Proposition* proposition = NULL;
    TruthValue* oldtruthvalue = NULL;

    { 
      BIND_STELLA_SPECIAL(oTERMSOURCEBEINGPARSEDo, const char*, stringify(definition));
      arguments = normalizeDefpropositionArguments(arguments);
      name = ((Symbol*)(arguments->value));
      internLogicObjectSurrogate(name);
      conception = smartUpdateProposition(arguments->rest->value, KWD_LOGIC_IN_CONCEIVE);
      if (!((boolean)(conception))) {
        return (NULL);
      }
      else if (consP(conception)) {
        proposition = conjoinPropositions(((Cons*)(conception)));
        proposition = fastenDownOneProposition(proposition, false);
      }
      else {
        proposition = ((Proposition*)(conception));
      }
      options = arguments->rest->rest;
      stringifiedSourceSetter(proposition, oTERMSOURCEBEINGPARSEDo);
      setDynamicSlotValue(proposition->dynamicSlots, SYM_LOGIC_IN_STELLA_BADp, TRUE_WRAPPER, NULL);
      bindLogicObjectToSurrogate(name, proposition);
      proposition->processDefinitionOptions(options);
      if (proposition->kind == KWD_LOGIC_IN_FORALL) {
        { Proposition* satellite = NULL;
          Cons* iter000 = proposition->satellitePropositions_reader()->theConsList;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            satellite = ((Proposition*)(iter000->value));
            destroyProposition(satellite);
          }
        }
        setDynamicSlotValue(proposition->dynamicSlots, SYM_LOGIC_IN_LOGIC_SATELLITE_PROPOSITIONS, NULL, NULL);
      }
      oldtruthvalue = ((TruthValue*)(accessInContext(proposition->truthValue, proposition->homeContext, false)));
      if (lookupAnnotation(proposition, KWD_LOGIC_IN_CONFIDENCE_LEVEL) == KWD_LOGIC_IN_DEFAULT) {
        removeAnnotation(proposition, KWD_LOGIC_IN_CONFIDENCE_LEVEL);
        updatePropositionTruthValue(proposition, KWD_LOGIC_IN_PRESUME_TRUE);
      }
      else {
        updatePropositionTruthValue(proposition, KWD_LOGIC_IN_ASSERT_TRUE);
      }
      if (oldtruthvalue == ((TruthValue*)(accessInContext(proposition->truthValue, proposition->homeContext, false)))) {
        runGoesTrueDemons(proposition);
      }
      setDynamicSlotValue(proposition->dynamicSlots, SYM_LOGIC_IN_STELLA_BADp, NULL, NULL);
      registerUnfinalizedObject(proposition);
      return (proposition);
    }
  }
}

Cons* normalizeDefpropositionArguments(Cons* arguments) {
  { Object* name = arguments->value;
    Object* proposition = arguments->rest->value;
    PropertyList* options = NULL;
    Object* value = NULL;
    Cons* annotations = NIL;

    { Surrogate* testValue000 = safePrimaryType(arguments->value);

      if (subtypeOfSymbolP(testValue000)) {
      }
      else if (subtypeOfStringP(testValue000)) {
        name = internSymbol(((StringWrapper*)(arguments->value))->wrapperValue);
        arguments->firstSetter(name);
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream000->nativeStream) << "ERROR: " << "Illegal proposition name where symbol or string expected: " << "`" << name << "'" << "." << std::endl;
            helpSignalPropositionError(stream000, KWD_LOGIC_IN_ERROR);
          }
          throw *newPropositionError(stream000->theStringReader());
        }
      }
    }
    options = vetOptions(arguments->rest->rest, NULL);
    value = options->lookup(KWD_LOGIC_IN_FORWARDp);
    if (((boolean)(value))) {
      options->removeAt(KWD_LOGIC_IN_FORWARDp);
      options->insertAt(KWD_LOGIC_IN_FORWARD_ONLYp, value);
    }
    value = options->lookup(KWD_LOGIC_IN_BACKWARDp);
    if (((boolean)(value))) {
      options->removeAt(KWD_LOGIC_IN_BACKWARDp);
      options->insertAt(KWD_LOGIC_IN_BACKWARD_ONLYp, value);
    }
    value = options->lookup(KWD_LOGIC_IN_CONFIDENCE_LEVEL);
    if (((boolean)(value))) {
      annotations = annotations->concatenate(listO(3, KWD_LOGIC_IN_CONFIDENCE_LEVEL, value, NIL), 0);
      options->removeAt(KWD_LOGIC_IN_CONFIDENCE_LEVEL);
    }
    value = options->lookup(KWD_LOGIC_IN_WEIGHT);
    if (((boolean)(value))) {
      annotations = annotations->concatenate(listO(3, KWD_LOGIC_IN_WEIGHT, value, NIL), 0);
      options->removeAt(KWD_LOGIC_IN_WEIGHT);
    }
    if (!(annotations == NIL)) {
      arguments->secondSetter(listO(3, SYM_LOGIC_IN_LOGIC_ABOUT, proposition, annotations->concatenate(NIL, 0)));
    }
    arguments->rest->rest = options->thePlist;
    return (arguments);
  }
}

void Proposition::processDefinitionOptions(Object* options) {
  { Proposition* self = this;

    axiomsSetter(self, NULL);
    { Object* key = NULL;
      Object* value = NULL;
      Cons* iter000 = vetOptions(options, NULL)->thePlist;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest->rest) {
        key = iter000->value;
        value = iter000->rest->value;
        if (!runOptionHandlerP(self, ((Keyword*)(key)), value)) {
          definitionKeywordAxiomsHandler(self, objectName(self), ((Keyword*)(key)), value);
        }
      }
    }
  }
}

Cons* oLOGIC_RELEVANT_STELLA_COMMANDSo = NULL;

boolean commandL(MethodSlot* command1, MethodSlot* command2) {
  return (stringLessP(command1->slotName->visibleName(false), command2->slotName->visibleName(false)));
}

List* listLogicCommands() {
  { List* commands = newList();

    { MethodSlot* function = NULL;
      Iterator* iter000 = allFunctions(getStellaModule("/LOGIC", true), true);
      Cons* collect000 = NULL;

      for  (; iter000->nextP(); ) {
        function = ((MethodSlot*)(iter000->value));
        if (((BooleanWrapper*)(dynamicSlotValue(function->dynamicSlots, SYM_LOGIC_IN_STELLA_METHOD_COMMANDp, FALSE_WRAPPER)))->wrapperValue &&
            function->publicP()) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(function, NIL);
              if (commands->theConsList == NIL) {
                commands->theConsList = collect000;
              }
              else {
                addConsToEndOfConsList(commands->theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(function, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    { Symbol* stellacommand = NULL;
      Cons* iter001 = oLOGIC_RELEVANT_STELLA_COMMANDSo;
      Cons* collect001 = NULL;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest) {
        stellacommand = ((Symbol*)(iter001->value));
        if (!((boolean)(collect001))) {
          {
            collect001 = cons(lookupCommand(stellacommand), NIL);
            if (commands->theConsList == NIL) {
              commands->theConsList = collect001;
            }
            else {
              addConsToEndOfConsList(commands->theConsList, collect001);
            }
          }
        }
        else {
          {
            collect001->rest = cons(lookupCommand(stellacommand), NIL);
            collect001 = collect001->rest;
          }
        }
      }
    }
    return (commands->sort(((cpp_function_code)(&commandL))));
  }
}

void help(Cons* commands) {
  // Describe specific commands, or print a list of available commands.
  { Cons* thecommands = commands;

    if (thecommands == NIL) {
      std::cout << "The following commands are available " << "(type `(help <command>+)'" << std::endl << "to get command-specific documentation):" << std::endl << std::endl;
      { List* allcommands = listLogicCommands();

        { MethodSlot* command = NULL;
          Cons* iter000 = allcommands->theConsList;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            command = ((MethodSlot*)(iter000->value));
            if (((StringWrapper*)(dynamicSlotValue(command->dynamicSlots, SYM_LOGIC_IN_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue != NULL) {
              command->printDocumentation(STANDARD_OUTPUT, true);
            }
          }
        }
        std::cout << std::endl << "Undocumented Commands:" << std::endl << std::endl;
        { MethodSlot* command = NULL;
          Cons* iter001 = allcommands->theConsList;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            command = ((MethodSlot*)(iter001->value));
            if (!(((StringWrapper*)(dynamicSlotValue(command->dynamicSlots, SYM_LOGIC_IN_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue != NULL)) {
              std::cout << command->slotName << ":" << std::endl;
            }
          }
        }
      }
    }
    else {
      { Symbol* commandname = NULL;
        Cons* iter002 = thecommands;

        for (; !(iter002 == NIL); iter002 = iter002->rest) {
          commandname = ((Symbol*)(iter002->value));
          { MethodSlot* command = lookupCommand(commandname);

            if (((boolean)(command))) {
              command->printDocumentation(STANDARD_OUTPUT, false);
            }
            else {
              std::cout << "Undefined command: " << "`" << commandname << "'" << std::endl;
            }
          }
        }
      }
    }
  }
}

void helpEvaluatorWrapper(Cons* arguments) {
  help(arguments);
}

void helpStartupLogicIn1() {
  {
    KWD_LOGIC_IN_TRACE_SUBGOALS = ((Keyword*)(internRigidSymbolWrtModule("TRACE-SUBGOALS", NULL, 2)));
    KWD_LOGIC_IN_TRACE_SOLUTIONS = ((Keyword*)(internRigidSymbolWrtModule("TRACE-SOLUTIONS", NULL, 2)));
    KWD_LOGIC_IN_TRACE_CLASSIFIER = ((Keyword*)(internRigidSymbolWrtModule("TRACE-CLASSIFIER", NULL, 2)));
    KWD_LOGIC_IN_ITERATIVE_DEEPENING = ((Keyword*)(internRigidSymbolWrtModule("ITERATIVE-DEEPENING", NULL, 2)));
    KWD_LOGIC_IN_JUSTIFICATIONS = ((Keyword*)(internRigidSymbolWrtModule("JUSTIFICATIONS", NULL, 2)));
    KWD_LOGIC_IN_JUST_IN_TIME_INFERENCE = ((Keyword*)(internRigidSymbolWrtModule("JUST-IN-TIME-INFERENCE", NULL, 2)));
    KWD_LOGIC_IN_EMIT_THINKING_DOTS = ((Keyword*)(internRigidSymbolWrtModule("EMIT-THINKING-DOTS", NULL, 2)));
    KWD_LOGIC_IN_GOAL_TREE = ((Keyword*)(internRigidSymbolWrtModule("GOAL-TREE", NULL, 2)));
    KWD_LOGIC_IN_CLASSIFIER_INFERENCES = ((Keyword*)(internRigidSymbolWrtModule("CLASSIFIER-INFERENCES", NULL, 2)));
    KWD_LOGIC_IN_CLOSED_WORLD = ((Keyword*)(internRigidSymbolWrtModule("CLOSED-WORLD", NULL, 2)));
    KWD_LOGIC_IN_REALISTIC = ((Keyword*)(internRigidSymbolWrtModule("REALISTIC", NULL, 2)));
    KWD_LOGIC_IN_BYE = ((Keyword*)(internRigidSymbolWrtModule("BYE", NULL, 2)));
    KWD_LOGIC_IN_EXIT = ((Keyword*)(internRigidSymbolWrtModule("EXIT", NULL, 2)));
    KWD_LOGIC_IN_HALT = ((Keyword*)(internRigidSymbolWrtModule("HALT", NULL, 2)));
    KWD_LOGIC_IN_QUIT = ((Keyword*)(internRigidSymbolWrtModule("QUIT", NULL, 2)));
    KWD_LOGIC_IN_STOP = ((Keyword*)(internRigidSymbolWrtModule("STOP", NULL, 2)));
    KWD_LOGIC_IN_DEFINE = ((Keyword*)(internRigidSymbolWrtModule("DEFINE", NULL, 2)));
    SGT_LOGIC_IN_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
    SYM_LOGIC_IN_STELLA_DEFMODULE = ((Symbol*)(internRigidSymbolWrtModule("DEFMODULE", getStellaModule("/STELLA", true), 0)));
    KWD_LOGIC_IN_FINALIZE = ((Keyword*)(internRigidSymbolWrtModule("FINALIZE", NULL, 2)));
    KWD_LOGIC_IN_OPTIONS = ((Keyword*)(internRigidSymbolWrtModule("OPTIONS", NULL, 2)));
    SYM_LOGIC_IN_STELLA_CLEAR_MODULE = ((Symbol*)(internRigidSymbolWrtModule("CLEAR-MODULE", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_IN_STELLA_DEFCLASS = ((Symbol*)(internRigidSymbolWrtModule("DEFCLASS", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_IN_STELLA_DEFSLOT = ((Symbol*)(internRigidSymbolWrtModule("DEFSLOT", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_IN_STELLA_DEFUN = ((Symbol*)(internRigidSymbolWrtModule("DEFUN", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_IN_STELLA_DEFMETHOD = ((Symbol*)(internRigidSymbolWrtModule("DEFMETHOD", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_IN_LOGIC_DEFCONCEPT = ((Symbol*)(internRigidSymbolWrtModule("DEFCONCEPT", NULL, 0)));
    SYM_LOGIC_IN_LOGIC_DEFFUNCTION = ((Symbol*)(internRigidSymbolWrtModule("DEFFUNCTION", NULL, 0)));
    SYM_LOGIC_IN_LOGIC_DEFRELATION = ((Symbol*)(internRigidSymbolWrtModule("DEFRELATION", NULL, 0)));
    SYM_LOGIC_IN_LOGIC_DEFOBJECT = ((Symbol*)(internRigidSymbolWrtModule("DEFOBJECT", NULL, 0)));
    SYM_LOGIC_IN_LOGIC_DEFINSTANCE = ((Symbol*)(internRigidSymbolWrtModule("DEFINSTANCE", NULL, 0)));
    SYM_LOGIC_IN_LOGIC_DESTROY = ((Symbol*)(internRigidSymbolWrtModule("DESTROY", NULL, 0)));
    SYM_LOGIC_IN_LOGIC_IN_DIALECT = ((Symbol*)(internRigidSymbolWrtModule("IN-DIALECT", NULL, 0)));
    SYM_LOGIC_IN_STELLA_CC = ((Symbol*)(internRigidSymbolWrtModule("CC", getStellaModule("/STELLA", true), 0)));
    KWD_LOGIC_IN_IMMEDIATE = ((Keyword*)(internRigidSymbolWrtModule("IMMEDIATE", NULL, 2)));
    KWD_LOGIC_IN_ALWAYS = ((Keyword*)(internRigidSymbolWrtModule("ALWAYS", NULL, 2)));
    KWD_LOGIC_IN_DEFERRED = ((Keyword*)(internRigidSymbolWrtModule("DEFERRED", NULL, 2)));
    KWD_LOGIC_IN_CHECK_DUPLICATESp = ((Keyword*)(internRigidSymbolWrtModule("CHECK-DUPLICATES?", NULL, 2)));
    SGT_LOGIC_IN_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", getStellaModule("/STELLA", true), 1)));
    KWD_LOGIC_IN_MODULE = ((Keyword*)(internRigidSymbolWrtModule("MODULE", NULL, 2)));
    SGT_LOGIC_IN_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", getStellaModule("/STELLA", true), 1)));
    KWD_LOGIC_IN_ASSERTION_MODULE = ((Keyword*)(internRigidSymbolWrtModule("ASSERTION-MODULE", NULL, 2)));
    SGT_LOGIC_IN_STELLA_IDENTITY = ((Surrogate*)(internRigidSymbolWrtModule("IDENTITY", getStellaModule("/STELLA", true), 1)));
    KWD_LOGIC_IN_LOW = ((Keyword*)(internRigidSymbolWrtModule("LOW", NULL, 2)));
    KWD_LOGIC_IN_MEDIUM = ((Keyword*)(internRigidSymbolWrtModule("MEDIUM", NULL, 2)));
    KWD_LOGIC_IN_WHITE_SPACE = ((Keyword*)(internRigidSymbolWrtModule("WHITE-SPACE", NULL, 2)));
    KWD_LOGIC_IN_LEVEL = ((Keyword*)(internRigidSymbolWrtModule("LEVEL", NULL, 2)));
    KWD_LOGIC_IN_NONE = ((Keyword*)(internRigidSymbolWrtModule("NONE", NULL, 2)));
    KWD_LOGIC_IN_PORT = ((Keyword*)(internRigidSymbolWrtModule("PORT", NULL, 2)));
    SGT_LOGIC_IN_STELLA_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER", getStellaModule("/STELLA", true), 1)));
    KWD_LOGIC_IN_HOST = ((Keyword*)(internRigidSymbolWrtModule("HOST", NULL, 2)));
    SGT_LOGIC_IN_STELLA_STRING = ((Surrogate*)(internRigidSymbolWrtModule("STRING", getStellaModule("/STELLA", true), 1)));
    KWD_LOGIC_IN_DEBUG_LEVEL = ((Keyword*)(internRigidSymbolWrtModule("DEBUG-LEVEL", NULL, 2)));
    KWD_LOGIC_IN_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    KWD_LOGIC_IN_WARNING = ((Keyword*)(internRigidSymbolWrtModule("WARNING", NULL, 2)));
    SGT_LOGIC_IN_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", NULL, 1)));
    SGT_LOGIC_IN_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    SGT_LOGIC_IN_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 1)));
    SGT_LOGIC_IN_STELLA_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("RELATION", getStellaModule("/STELLA", true), 1)));
    SYM_LOGIC_IN_LOGIC_MODULE_LOGIC_DIALECT = ((Symbol*)(internRigidSymbolWrtModule("MODULE-LOGIC-DIALECT", NULL, 0)));
  }
}

void helpStartupLogicIn2() {
  {
    KWD_LOGIC_IN_KIF = ((Keyword*)(internRigidSymbolWrtModule("KIF", NULL, 2)));
    SGT_LOGIC_IN_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", NULL, 1)));
    KWD_LOGIC_IN_DEFINITION = ((Keyword*)(internRigidSymbolWrtModule("DEFINITION", NULL, 2)));
    KWD_LOGIC_IN_REDEFINITION = ((Keyword*)(internRigidSymbolWrtModule("REDEFINITION", NULL, 2)));
    KWD_LOGIC_IN_PROPER_DEFINITION = ((Keyword*)(internRigidSymbolWrtModule("PROPER-DEFINITION", NULL, 2)));
    SYM_LOGIC_IN_LOGIC_OBJECT_AXIOMS = ((Symbol*)(internRigidSymbolWrtModule("OBJECT-AXIOMS", NULL, 0)));
    SYM_LOGIC_IN_LOGIC_PROPOSITION_AXIOMS = ((Symbol*)(internRigidSymbolWrtModule("PROPOSITION-AXIOMS", NULL, 0)));
    SYM_LOGIC_IN_STELLA_SLOT_OPTION_KEYWORD = ((Symbol*)(internRigidSymbolWrtModule("SLOT-OPTION-KEYWORD", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_IN_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", getStellaModule("/STELLA", true), 0)));
    SGT_LOGIC_IN_STELLA_THING = ((Surrogate*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 1)));
    SYM_LOGIC_IN_STELLA_FORALL = ((Symbol*)(internRigidSymbolWrtModule("FORALL", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_IN_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", getStellaModule("/STELLA", true), 0)));
    KWD_LOGIC_IN_ASSERT_TRUE = ((Keyword*)(internRigidSymbolWrtModule("ASSERT-TRUE", NULL, 2)));
    SYM_LOGIC_IN_STELLA_BADp = ((Symbol*)(internRigidSymbolWrtModule("BAD?", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_IN_PL_KERNEL_KB_NTH_DOMAIN = ((Symbol*)(internRigidSymbolWrtModule("NTH-DOMAIN", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOGIC_IN_PL_KERNEL_KB_DOMAIN = ((Symbol*)(internRigidSymbolWrtModule("DOMAIN", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOGIC_IN_PL_KERNEL_KB_RANGE = ((Symbol*)(internRigidSymbolWrtModule("RANGE", getStellaModule("/PL-KERNEL-KB", true), 0)));
    KWD_LOGIC_IN__g = ((Keyword*)(internRigidSymbolWrtModule("->", NULL, 2)));
    SYM_LOGIC_IN_LOGIC_pSELF = ((Symbol*)(internRigidSymbolWrtModule("?SELF", NULL, 0)));
    KWD_LOGIC_IN_eg = ((Keyword*)(internRigidSymbolWrtModule("=>", NULL, 2)));
    SYM_LOGIC_IN_LOGIC_DEFPROPOSITION = ((Symbol*)(internRigidSymbolWrtModule("DEFPROPOSITION", NULL, 0)));
    KWD_LOGIC_IN_CONCEIVE = ((Keyword*)(internRigidSymbolWrtModule("CONCEIVE", NULL, 2)));
    KWD_LOGIC_IN_FORALL = ((Keyword*)(internRigidSymbolWrtModule("FORALL", NULL, 2)));
    SYM_LOGIC_IN_LOGIC_SATELLITE_PROPOSITIONS = ((Symbol*)(internRigidSymbolWrtModule("SATELLITE-PROPOSITIONS", NULL, 0)));
    KWD_LOGIC_IN_CONFIDENCE_LEVEL = ((Keyword*)(internRigidSymbolWrtModule("CONFIDENCE-LEVEL", NULL, 2)));
    KWD_LOGIC_IN_DEFAULT = ((Keyword*)(internRigidSymbolWrtModule("DEFAULT", NULL, 2)));
    KWD_LOGIC_IN_PRESUME_TRUE = ((Keyword*)(internRigidSymbolWrtModule("PRESUME-TRUE", NULL, 2)));
    KWD_LOGIC_IN_FORWARDp = ((Keyword*)(internRigidSymbolWrtModule("FORWARD?", NULL, 2)));
    KWD_LOGIC_IN_FORWARD_ONLYp = ((Keyword*)(internRigidSymbolWrtModule("FORWARD-ONLY?", NULL, 2)));
    KWD_LOGIC_IN_BACKWARDp = ((Keyword*)(internRigidSymbolWrtModule("BACKWARD?", NULL, 2)));
    KWD_LOGIC_IN_BACKWARD_ONLYp = ((Keyword*)(internRigidSymbolWrtModule("BACKWARD-ONLY?", NULL, 2)));
    KWD_LOGIC_IN_WEIGHT = ((Keyword*)(internRigidSymbolWrtModule("WEIGHT", NULL, 2)));
    SYM_LOGIC_IN_LOGIC_ABOUT = ((Symbol*)(internRigidSymbolWrtModule("ABOUT", NULL, 0)));
    SYM_LOGIC_IN_STELLA_IN_MODULE = ((Symbol*)(internRigidSymbolWrtModule("IN-MODULE", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_IN_STELLA_LIST_MODULES = ((Symbol*)(internRigidSymbolWrtModule("LIST-MODULES", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_IN_STELLA_METHOD_COMMANDp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-COMMAND?", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_IN_STELLA_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("DOCUMENTATION", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_IN_LOGIC_STARTUP_LOGIC_IN = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-LOGIC-IN", NULL, 0)));
    SYM_LOGIC_IN_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupLogicIn3() {
  {
    oAVAILABLE_POWERLOOM_FEATURESo = list(7, KWD_LOGIC_IN_TRACE_SUBGOALS, KWD_LOGIC_IN_TRACE_SOLUTIONS, KWD_LOGIC_IN_TRACE_CLASSIFIER, KWD_LOGIC_IN_ITERATIVE_DEEPENING, KWD_LOGIC_IN_JUSTIFICATIONS, KWD_LOGIC_IN_JUST_IN_TIME_INFERENCE, KWD_LOGIC_IN_EMIT_THINKING_DOTS);
    oCURRENT_POWERLOOM_FEATURESo = list(0);
    oDEFAULT_POWERLOOM_FEATURESo = list(2, KWD_LOGIC_IN_JUST_IN_TIME_INFERENCE, KWD_LOGIC_IN_EMIT_THINKING_DOTS);
    resetFeatures();
    oPOWERLOOM_KB_FILE_EXTENSIONSo = getQuotedTree("((\".plm\" \".ploom\") \"/LOGIC\")", "/LOGIC");
    oDEMO_FILESo = listO(22, listO(4, wrapString("basics"), wrapString("Basic PowerLoom commands"), wrapString("test-suite"), NIL), listO(4, wrapString("classes"), wrapString("Primitive and defined classes"), wrapString("test-suite"), NIL), listO(4, wrapString("collections"), wrapString("Reasoning with collections"), wrapString("test-suite"), NIL), listO(4, wrapString("append"), wrapString("Prolog-style `append'"), wrapString("test-suite"), NIL), listO(4, wrapString("inequalities"), wrapString("Reasoning with inequalities"), wrapString("test-suite"), NIL), listO(4, wrapString("recursion"), wrapString("Reasoning with recursive rules"), wrapString("test-suite"), NIL), listO(4, wrapString("negation"), wrapString("Reasoning with negation"), wrapString("test-suite"), NIL), listO(4, wrapString("constraints"), wrapString("Constraint propagation"), wrapString("test-suite"), NIL), listO(4, wrapString("equations"), wrapString("Simple equational reasoning"), wrapString("test-suite"), NIL), listO(4, wrapString("subsumption"), wrapString("Simple subsumption reasoning"), wrapString("test-suite"), NIL), listO(4, wrapString("family"), wrapString("Subsumption reasoning within a family ontology"), wrapString("test-suite"), NIL), listO(4, wrapString("relation-hierarchy"), wrapString("Finding sub, super and equivalent concepts and relations"), wrapString("test-suite"), NIL), listO(4, wrapString("defaults"), wrapString("Default reasoning with Tweety and friends"), wrapString("test-suite"), NIL), listO(4, wrapString("defaults2"), wrapString("More default reasoning"), wrapString("test-suite"), NIL), listO(4, wrapString("definition-syntax"), wrapString("The whole scoop on relation definition, funny arrows, etc."), wrapString("test-suite"), NIL), listO(4, wrapString("meta-relations"), wrapString("Using meta-properties and relations"), wrapString("test-suite"), NIL), listO(4, wrapString("partial-match"), wrapString("Reasoning with partial information"), wrapString("test-suite"), NIL), listO(4, wrapString("probability-learning"), wrapString("Learning to answer probabilistic queries"), wrapString("test-suite"), NIL), listO(3, wrapString("regression-demo"), wrapString("Learning to predict functions"), NIL), listO(3, wrapString("rule-induction-demo"), wrapString("Learning inference rules"), NIL), listO(4, wrapString("test-suite"), wrapString("PowerLoom test suite"), wrapString("test-suite"), NIL), NIL);
    oTERMSOURCEBEINGPARSEDo = NULL;
    oUNFINALIZED_OBJECTSo = list(0);
    oLOGIC_RELEVANT_STELLA_COMMANDSo = listO(6, SYM_LOGIC_IN_STELLA_CC, SYM_LOGIC_IN_STELLA_CLEAR_MODULE, SYM_LOGIC_IN_STELLA_DEFMODULE, SYM_LOGIC_IN_STELLA_IN_MODULE, SYM_LOGIC_IN_STELLA_LIST_MODULES, NIL);
  }
}

void helpStartupLogicIn4() {
  {
    defineFunctionObject("PRINT-FEATURES", "(DEFUN PRINT-FEATURES () :COMMAND? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Print the currently enabled and available PowerLoom environment features.\")", ((cpp_function_code)(&printFeatures)), NULL);
    defineFunctionObject("LIST-FEATURES", "(DEFUN (LIST-FEATURES LIST) () :COMMAND? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Return a list containing two lists, a list of currently enabled PowerLoom\nfeatures, and a list of all available PowerLoom features.\")", ((cpp_function_code)(&listFeatures)), NULL);
    defineFunctionObject("SET-POWERLOOM-FEATURE", "(DEFUN SET-POWERLOOM-FEATURE ((FEATURE KEYWORD)) :DOCUMENTATION \"Enable the PowerLoom environment feature `feature'.\")", ((cpp_function_code)(&setPowerloomFeature)), NULL);
    defineFunctionObject("SET-FEATURE", "(DEFUN (SET-FEATURE (LIST OF KEYWORD)) (|&REST| (FEATURES NAME)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Enable the PowerLoom environment feature(s) named by `features'.\nReturn the list of enabled features.  Calling `set-feature' without any\narguments can be used to display the currently enabled features.\nThe following features are supported:\n\n`just-in-time-inference': Enables interleaving of forward chaining inference\nwithin backward chaining queries.\n\n`iterative-deepening': Tells the query processor to use iterative deepening\ninstead of a depth-first search to find answers.  This is less efficient\nbut necessary for some kinds of highly recursive queries.\n\n`trace-subgoals': Enables the generation of subgoaling trace information during\nbackchaining inference.\n\n`trace-solutions': Prints newly found solutions during retrieval right when they\nare generated as opposed to when the query terminates.\n\n`trace-classifier': Tells the classifier to describe the inferen" "ces it draws.\n\n`justifications': Enables the generation of justifications during inference,\nwhich is a prerequiste for the generation of explanations with `(why)'.\n\n`emit-thinking-dots': Tells PowerLoom to annotate its inference progress by\noutputting characters indicating the completion of individual reasoning steps.\n\nBy default, the features `emit-thinking-dots' and `just-in-time-inference'\nare enabled, and the others are disabled.\n\")", ((cpp_function_code)(&setFeature)), ((cpp_function_code)(&setFeatureEvaluatorWrapper)));
    defineFunctionObject("UNSET-POWERLOOM-FEATURE", "(DEFUN UNSET-POWERLOOM-FEATURE ((FEATURE KEYWORD)) :DOCUMENTATION \"Disable the PowerLoom environment feature `feature'.\")", ((cpp_function_code)(&unsetPowerloomFeature)), NULL);
    defineFunctionObject("UNSET-FEATURE", "(DEFUN (UNSET-FEATURE (LIST OF KEYWORD)) (|&REST| (FEATURES NAME)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Disable the PowerLoom environment feature(s) named by `features'.\nReturn the list of enabled features.  Calling `unset-feature' without any\narguments can be used to display the currently enabled features.\nSee `set-feature' for a description of supported features.\")", ((cpp_function_code)(&unsetFeature)), ((cpp_function_code)(&unsetFeatureEvaluatorWrapper)));
    defineFunctionObject("RESET-FEATURES", "(DEFUN (RESET-FEATURES (LIST OF KEYWORD)) () :COMMAND? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Reset the PowerLoom environment features to their default settings.\")", ((cpp_function_code)(&resetFeatures)), NULL);
    defineFunctionObject("ENABLED-POWERLOOM-FEATURE?", "(DEFUN (ENABLED-POWERLOOM-FEATURE? BOOLEAN) ((FEATURE KEYWORD)) :DOCUMENTATION \"Return true if the STELLA `feature' is currently enabled.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (MEMB? *CURRENT-POWERLOOM-FEATURES* FEATURE)))", ((cpp_function_code)(&enabledPowerloomFeatureP)), NULL);
    defineFunctionObject("DISABLED-POWERLOOM-FEATURE?", "(DEFUN (DISABLED-POWERLOOM-FEATURE? BOOLEAN) ((FEATURE KEYWORD)) :DOCUMENTATION \"Return true if the STELLA `feature' is currently disabled.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (NOT (MEMB? *CURRENT-POWERLOOM-FEATURES* FEATURE))))", ((cpp_function_code)(&disabledPowerloomFeatureP)), NULL);
    defineFunctionObject("PARSE-LOGIC-COMMAND-OPTIONS", "(DEFUN (PARSE-LOGIC-COMMAND-OPTIONS PROPERTY-LIST) ((OPTIONS OBJECT) (|LEGALOPTIONS&TYPES| CONS) (COERCIONERROR? BOOLEAN) (ALLOWOTHERKEYS? BOOLEAN)) :DOCUMENTATION \"This is simply a wrapper to `parse-options' (which see).\nWe keep this alias in case we ever want to add any logic-specific extensions.\" :PUBLIC? TRUE)", ((cpp_function_code)(&parseLogicCommandOptions)), NULL);
    defineFunctionObject("PRINT-LOGIC-PROMPT", "(DEFUN PRINT-LOGIC-PROMPT ())", ((cpp_function_code)(&printLogicPrompt)), NULL);
    defineFunctionObject("PRINT-LOGIC-COMMAND-RESULT", "(DEFUN PRINT-LOGIC-COMMAND-RESULT ((RESULT OBJECT)))", ((cpp_function_code)(&printLogicCommandResult)), NULL);
    defineFunctionObject("LOGIC-COMMAND-LOOP-EXIT?", "(DEFUN (LOGIC-COMMAND-LOOP-EXIT? BOOLEAN BOOLEAN) ((COMMAND OBJECT)))", ((cpp_function_code)(&logicCommandLoopExitP)), NULL);
    defineFunctionObject("LOGIC-COMMAND-LOOP", "(DEFUN LOGIC-COMMAND-LOOP ((MODULE MODULE)))", ((cpp_function_code)(&logicCommandLoop)), NULL);
    defineFunctionObject("EVALUATE-LOGIC-COMMAND", "(DEFUN (EVALUATE-LOGIC-COMMAND OBJECT) ((COMMAND OBJECT) (FINALIZE? BOOLEAN)))", ((cpp_function_code)(&evaluateLogicCommand)), NULL);
    defineFunctionObject("LOAD", "(DEFUN LOAD ((FILE STRING) |&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Read logic commands from `file' and evaluate them.\nBy default, this will check for each asserted proposition whether an\nequivalent proposition already exists and, if so, not assert the\nduplicate.  These duplicate checks are somewhat expensive though and\ncan be skipped by setting the option :check-duplicates? to false.\nThis can save time when loading large KBs where it is known that no\nduplicate assertions exist in a file.\n\nAlso, by setting the :module option, the module in which the file\ncontents will be loaded will be set.  This will only affect files\nthat do NOT have an `in-module' declaration as part of the file.\nIf this is not set, and no `in-module' declaration is in the file,\nthe file will be loaded into the current module.\n\nThe option :assertion-module can be used to have assertions and\ndefinitional axioms be asserted in a different module than the\ntop-level module where definitions are evaluated.  This is useful\nin" " some cases where vocabulary definitions and their associated\naxioms and assertions need to be separate for inference or efficiency\nreasons.  The assertion module can be given as a name in case it is\ndefined in the loaded file.  Obviously, it needs to be a child of the\ntop-level module where vocabulary definitions are created.\n\nLoading is done in two passes: in the first pass all definitional\ncommands such as `defmodule', `defconcept', etc. are evaluated but not\nyet finalized, that is, their definitional axioms are parsed but not\nyet asserted.  In the second pass all definitional commands are finalized\nand then all commands in the file are executed in order (which will be\nno-ops for the definitions already processed).  This scheme tries to\nmaintain some order independence for the commands in the file, since\nrelation definitions need to be performed before they can be used in\nassertions.  At any point `process-definitions' can be called to finalize\nall unfinalized definitions queued up so far. " " Future versions might also\nsupport a :one-pass? option for added efficiency.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&load)), ((cpp_function_code)(&loadEvaluatorWrapper)));
    defineFunctionObject("DEFINITION-NAME?", "(DEFUN (DEFINITION-NAME? BOOLEAN) ((NAME SYMBOL)) :PUBLIC? FALSE)", ((cpp_function_code)(&definitionNameP)), NULL);
    defineFunctionObject("LOAD-COMMAND-EVAL-PHASE", "(DEFUN (LOAD-COMMAND-EVAL-PHASE KEYWORD) ((TREE OBJECT)) :DOCUMENTATION \"Analyze a command `tree' in a load file and determine when it should be processed.\" :PUBLIC? TRUE)", ((cpp_function_code)(&loadCommandEvalPhase)), NULL);
    defineFunctionObject("LOAD-STREAM", "(DEFUN LOAD-STREAM ((STREAM INPUT-STREAM) |&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Read logic commands from `stream' and evaluate them.\nDoes the actual work for `load' (which see for a description of options).\" :PUBLIC? TRUE)", ((cpp_function_code)(&loadStream)), NULL);
    defineFunctionObject("LOAD-STREAM-IN-MODULE", "(DEFUN LOAD-STREAM-IN-MODULE ((STREAM INPUT-STREAM) (MODULE MODULE)) :DOCUMENTATION \"Read logic commands from `stream' and evaluate them in `module'.\nThis is a backwards-compatibility wrapper.  Note that `module' will not override\nany `in-module' declarations in `stream'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&loadStreamInModule)), NULL);
    defineFunctionObject("LOAD-DIRECTORY", "(DEFUN LOAD-DIRECTORY ((DIRECTORY STRING)) :DOCUMENTATION \"Load all PowerLoom files (*.plm) in `directory' in alphabetic sort order.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&loadDirectory)), ((cpp_function_code)(&loadDirectoryEvaluatorWrapper)));
    defineFunctionObject("LOAD-CMD-LINE-FILES", "(DEFUN LOAD-CMD-LINE-FILES () :DOCUMENTATION \"Loads all PowerLoom files specified on the command line.\nIf directories are listed, all PowerLoom files in those directories are loaded.\nSince when this is called we might still have unprocessed command line args,\nthis only looks at files which are to the right of the last argument that\nstarts with a `-' character.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&loadCmdLineFiles)), NULL);
    defineFunctionObject("PRINT-DEMO-PROMPT", "(DEFUN PRINT-DEMO-PROMPT ())", ((cpp_function_code)(&printDemoPrompt)), NULL);
    defineFunctionObject("DEMO-SKIP-TO-COMMAND", "(DEFUN (DEMO-SKIP-TO-COMMAND BOOLEAN) ((STREAM INPUT-STREAM)))", ((cpp_function_code)(&demoSkipToCommand)), NULL);
    defineFunctionObject("DEMO-PAUSE?", "(DEFUN (DEMO-PAUSE? BOOLEAN BOOLEAN) ((PAUSE? BOOLEAN)))", ((cpp_function_code)(&demoPauseP)), NULL);
    defineFunctionObject("DEMO-FILE", "(DEFUN DEMO-FILE ((FILE FILE-NAME) (PAUSE? BOOLEAN)))", ((cpp_function_code)(&demoFile)), NULL);
    defineFunctionObject("DEMO-ENTRY-FILE", "(DEFUN (DEMO-ENTRY-FILE STRING) ((DEMOENTRY (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&demoEntryFile)), NULL);
    defineFunctionObject("DEMO-ENTRY-DESCRIPTION", "(DEFUN (DEMO-ENTRY-DESCRIPTION STRING) ((DEMOENTRY (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&demoEntryDescription)), NULL);
    defineFunctionObject("DEMO-ENTRY-TEST-SUITE?", "(DEFUN (DEMO-ENTRY-TEST-SUITE? BOOLEAN) ((DEMOENTRY (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&demoEntryTestSuiteP)), NULL);
    defineFunctionObject("SELECT-EXAMPLE-DEMO", "(DEFUN (SELECT-EXAMPLE-DEMO STRING) ((INDEX INTEGER)))", ((cpp_function_code)(&selectExampleDemo)), NULL);
    defineFunctionObject("SELECT-EXAMPLE-DEMO-FROM-MENU", "(DEFUN (SELECT-EXAMPLE-DEMO-FROM-MENU STRING) ())", ((cpp_function_code)(&selectExampleDemoFromMenu)), NULL);
    defineFunctionObject("DEMO-EXAMPLE-DEMOS", "(DEFUN DEMO-EXAMPLE-DEMOS ())", ((cpp_function_code)(&demoExampleDemos)), NULL);
    defineFunctionObject("DEMO", "(DEFUN DEMO (|&REST| (FILEANDPAUSE OBJECT)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? TRUE :DOCUMENTATION \"Read logic commands from a file, echo them verbatimly to standard output,\nand evaluate them just as if they had been typed in interactively.\nWhen called with no arguments, present a menu of example demos, otherwise,\nuse the first argument as the name of the file to demo.\nPause for user confirmation after each expression has been read but\nbefore it is evaluated.  Pausing can be turned off by suppling FALSE\nas the optional second argument, or by typing `c' at the pause prompt.\nTyping `?' at the pause prompt prints a list of available commands.\")", ((cpp_function_code)(&demo)), ((cpp_function_code)(&demoEvaluatorWrapper)));
    defineFunctionObject("TEST-LOGIC-FILE", "(DEFUN TEST-LOGIC-FILE ((FILE FILE-NAME)))", ((cpp_function_code)(&testLogicFile)), NULL);
    defineFunctionObject("GET-FORMATTED-DATE-AND-TIME", "(DEFUN (GET-FORMATTED-DATE-AND-TIME STRING) ())", ((cpp_function_code)(&getFormattedDateAndTime)), NULL);
    defineFunctionObject("RUN-POWERLOOM-TESTS", "(DEFUN RUN-POWERLOOM-TESTS () :COMMAND? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Run the PowerLoom test suite.  Currently this simply runs all demos and\nechos commands and their results to standard output.  The output can then\nbe diffed with previously validated runs to find deviations.\")", ((cpp_function_code)(&runPowerloomTests)), NULL);
    defineFunctionObject("TIME-COMMAND", "(DEFUN (TIME-COMMAND OBJECT) ((COMMAND CONS)) :DOCUMENTATION \"Execute `command', measure and report its CPU and elapsed time\nneeded for its execution, and then return its result.\" :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&timeCommand)), NULL);
    defineFunctionObject("GET-HTTP-SERVER-SYSTEM", "(DEFUN (GET-HTTP-SERVER-SYSTEM STRING) ())", ((cpp_function_code)(&getHttpServerSystem)), NULL);
    defineFunctionObject("START-ONTOSAURUS", "(DEFUN START-ONTOSAURUS (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Start the PowerLoom HTTP server at :port (defaults to 9090).  Loads\nthe required support systems in Lisp and Java if necessary (C++ is not yet supported).\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&startOntosaurus)), ((cpp_function_code)(&startOntosaurusEvaluatorWrapper)));
    defineFunctionObject("STOP-ONTOSAURUS", "(DEFUN STOP-ONTOSAURUS () :DOCUMENTATION \"Stop the PowerLoom HTTP server and free up any bound ports.\nThis is a no-op if no server is running or the server is not supported.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&stopOntosaurus)), NULL);
    defineFunctionObject("START-POWERLOOM-SERVER", "(DEFUN START-POWERLOOM-SERVER (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Start the PowerLoom HTTP server at :port (defaults to 9090).  Loads\nthe required support systems in Lisp and Java if necessary (C++ is not yet supported).\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&startPowerloomServer)), ((cpp_function_code)(&startPowerloomServerEvaluatorWrapper)));
    defineFunctionObject("STOP-POWERLOOM-SERVER", "(DEFUN STOP-POWERLOOM-SERVER () :DOCUMENTATION \"Stop the PowerLoom HTTP server and free up any bound ports.\nThis is a no-op if no server is running or the server is not supported.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&stopPowerloomServer)), NULL);
    defineFunctionObject("START-POWERLOOM-GUI", "(DEFUN START-POWERLOOM-GUI (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Start the PowerLoom server at :port (defaults to 9090) and launches\nthe GUI which will communicate with the server at that port.  If :host is specified,\nthe GUI will try to communicate with a server at `host:port' instead of the local\nembedded server (note, you can always point the GUI manually to a different server\nfrom its `Connect to Server' menu item).  Loads the required support systems if necessary.\nEmbedded calls to the GUI are currently only supported in Java; however, when the GUI is\nrun in standalone mode, it can communicate with any PowerLoom installation that supports\nan HTTP server (currently Lisp and Java).\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&startPowerloomGui)), ((cpp_function_code)(&startPowerloomGuiEvaluatorWrapper)));
    defineFunctionObject("STOP-POWERLOOM-GUI", "(DEFUN STOP-POWERLOOM-GUI () :DOCUMENTATION \"Closes the PowerLoom GUI application if it is currently visible.\nThis is a no-op if the GUI is not running or if it is not supported.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&stopPowerloomGui)), NULL);
    defineFunctionObject("POWERLOOM-GUI-EXIT-HOOK", "(DEFUN POWERLOOM-GUI-EXIT-HOOK ((IGNORE OBJECT)) :DOCUMENTATION \"Exit hook to stop the PowerLoom GUI if it is running.\" :PUBLIC? TRUE)", ((cpp_function_code)(&powerloomGuiExitHook)), NULL);
    defineFunctionObject("PRINT-FORMULA-CONTAINING-ERROR", "(DEFUN PRINT-FORMULA-CONTAINING-ERROR ((SELF OBJECT) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&printFormulaContainingError)), NULL);
    defineFunctionObject("HELP-SIGNAL-PROPOSITION-ERROR", "(DEFUN HELP-SIGNAL-PROPOSITION-ERROR ((STREAM OUTPUT-STREAM) (WARNINGORERROR KEYWORD)))", ((cpp_function_code)(&helpSignalPropositionError)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION PERMUTATION-TABLE :TYPE (KEY-VALUE-LIST OF VECTOR SLOT) :OPTION-KEYWORD :PERMUTATION-TABLE :ALLOCATION :DYNAMIC)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT TABLE RELATION-PARAMETER-TYPE-SPECIFIERS :RENAMES TUPLE-DOMAINS)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT MODULE MODULE-LOGIC-DIALECT :TYPE KEYWORD :DEFAULT NULL :OPTION-KEYWORD :LOGIC-DIALECT :PUBLIC? TRUE :ALLOCATION :DYNAMIC)");
    defineFunctionObject("LOGIC-DIALECT", "(DEFUN (LOGIC-DIALECT KEYWORD) ((SELF OBJECT)))", ((cpp_function_code)(&logicDialect)), NULL);
    defineFunctionObject("LOOKUP-LOGIC-OBJECT-SURROGATE", "(DEFUN (LOOKUP-LOGIC-OBJECT-SURROGATE SURROGATE) ((NAME SYMBOL) (DEFINITIONMODULE MODULE)))", ((cpp_function_code)(&lookupLogicObjectSurrogate)), NULL);
    defineFunctionObject("INTERN-LOGIC-OBJECT-SURROGATE", "(DEFUN (INTERN-LOGIC-OBJECT-SURROGATE SURROGATE) ((NAME SYMBOL)))", ((cpp_function_code)(&internLogicObjectSurrogate)), NULL);
    defineFunctionObject("NAME-OBJECT-METACLASS", "(DEFUN (NAME-OBJECT-METACLASS STRING) ((SELF OBJECT)))", ((cpp_function_code)(&nameObjectMetaclass)), NULL);
    defineFunctionObject("LOGIC-OBJECT-DEFINITION-TYPE", "(DEFUN (LOGIC-OBJECT-DEFINITION-TYPE KEYWORD) ((NAME SYMBOL) (OLDOBJECT OBJECT) (NEWOBJECT OBJECT)))", ((cpp_function_code)(&logicObjectDefinitionType)), NULL);
    defineFunctionObject("BIND-LOGIC-OBJECT-TO-SURROGATE", "(DEFUN BIND-LOGIC-OBJECT-TO-SURROGATE ((NAME SYMBOL) (OBJECT OBJECT)))", ((cpp_function_code)(&bindLogicObjectToSurrogate)), NULL);
    defineFunctionObject("REDEFINE-LOGIC-OBJECT", "(DEFUN REDEFINE-LOGIC-OBJECT ((NAME SYMBOL) (OLDOBJECT OBJECT) (NEWOBJECT OBJECT)))", ((cpp_function_code)(&redefineLogicObject)), NULL);
    defineFunctionObject("EXPLICITLY-QUALIFIED-LOGIC-OBJECT-NAME?", "(DEFUN (EXPLICITLY-QUALIFIED-LOGIC-OBJECT-NAME? BOOLEAN) ((OBJECTNAME GENERALIZED-SYMBOL) (DEFINITIONMODULE MODULE)))", ((cpp_function_code)(&explicitlyQualifiedLogicObjectNameP)), NULL);
    defineFunctionObject("COERCE-TO-BOUND-OR-LOCAL-SURROGATE", "(DEFUN (COERCE-TO-BOUND-OR-LOCAL-SURROGATE SURROGATE) ((SELF GENERALIZED-SYMBOL)))", ((cpp_function_code)(&coerceToBoundOrLocalSurrogate)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT LOGIC-OBJECT OBJECT-AXIOMS :TYPE CONS :DEFAULT NULL :READER AXIOMS :OPTION-KEYWORD :AXIOMS :OPTION-HANDLER DEFINITION-AXIOMS-HANDLER :ALLOCATION :DYNAMIC)");
  }
}

void helpStartupLogicIn5() {
  {
    defineExternalSlotFromStringifiedSource("(DEFSLOT PROPOSITION PROPOSITION-AXIOMS :TYPE CONS :DEFAULT NULL :WRITER AXIOMS-SETTER :OPTION-KEYWORD :AXIOMS :OPTION-HANDLER DEFINITION-AXIOMS-HANDLER :ALLOCATION :DYNAMIC)");
    defineFunctionObject("AXIOMS", "(DEFUN (AXIOMS CONS) ((SELF OBJECT)))", ((cpp_function_code)(&axioms)), NULL);
    defineFunctionObject("AXIOMS-SETTER", "(DEFUN (AXIOMS-SETTER OBJECT) ((SELF OBJECT) (AXIOMS CONS)))", ((cpp_function_code)(&axiomsSetter)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS1 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<= :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS2 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :=> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS3 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<<= :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS4 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :=>> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS5 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<=> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS6 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<=>> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS7 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<<=> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS8 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<<=>> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS9 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<~ :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS10 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :~> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS11 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<<~ :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS12 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :~>> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS13 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<~> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS14 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<~>> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS15 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<<~> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS16 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<<~>> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)");
    defineFunctionObject("DEFINITION-AXIOMS-HANDLER", "(DEFUN DEFINITION-AXIOMS-HANDLER ((SELF OBJECT) (SLOT STORAGE-SLOT) (THEAXIOMS OBJECT)))", ((cpp_function_code)(&definitionAxiomsHandler)), NULL);
    defineFunctionObject("DEFINITION-HALF-RULE-HANDLER", "(DEFUN DEFINITION-HALF-RULE-HANDLER ((SELF NAMED-DESCRIPTION) (SLOT STORAGE-SLOT) (BODY OBJECT)))", ((cpp_function_code)(&definitionHalfRuleHandler)), NULL);
    defineFunctionObject("COMBINE-AXIOM-LISTS", "(DEFUN (COMBINE-AXIOM-LISTS CONS) ((OLDAXIOMS CONS) (NEWAXIOMS OBJECT)))", ((cpp_function_code)(&combineAxiomLists)), NULL);
    defineFunctionObject("YIELD-RELATION-PARAMETERS-TREE", "(DEFUN (YIELD-RELATION-PARAMETERS-TREE CONS) ((SELF NAMED-DESCRIPTION) (DROPFUNCTIONPARAMETER? BOOLEAN) (TYPED? BOOLEAN)))", ((cpp_function_code)(&yieldRelationParametersTree)), NULL);
    defineFunctionObject("COMPLETE-RULE-DEFINITION", "(DEFUN (COMPLETE-RULE-DEFINITION OBJECT) ((SELF NAMED-DESCRIPTION) (BODY OBJECT) (ARROW SYMBOL)))", ((cpp_function_code)(&completeRuleDefinition)), NULL);
    defineFunctionObject("DEFINITION-KEYWORD-AXIOMS-HANDLER", "(DEFUN DEFINITION-KEYWORD-AXIOMS-HANDLER ((SELF OBJECT) (SELFNAME SYMBOL) (KEY KEYWORD) (VALUE OBJECT)))", ((cpp_function_code)(&definitionKeywordAxiomsHandler)), NULL);
    defineFunctionObject("HELP-DEFINE-KEYWORD-AXIOMS", "(DEFUN (HELP-DEFINE-KEYWORD-AXIOMS CONS) ((SELFNAME SYMBOL) (KEY KEYWORD) (VALUE OBJECT)))", ((cpp_function_code)(&helpDefineKeywordAxioms)), NULL);
    defineFunctionObject("ASSERT-KEYWORD-AXIOM", "(DEFUN ASSERT-KEYWORD-AXIOM ((SELF OBJECT) (SELFNAME SYMBOL) (KEY KEYWORD) (VALUE OBJECT)))", ((cpp_function_code)(&assertKeywordAxiom)), NULL);
    defineFunctionObject("REGISTER-UNFINALIZED-OBJECT", "(DEFUN REGISTER-UNFINALIZED-OBJECT ((OBJECT OBJECT)))", ((cpp_function_code)(&registerUnfinalizedObject)), NULL);
    defineFunctionObject("CLEANUP-UNFINALIZED-OBJECTS", "(DEFUN CLEANUP-UNFINALIZED-OBJECTS ())", ((cpp_function_code)(&cleanupUnfinalizedObjects)), NULL);
    defineFunctionObject("LINK-ORIGINATED-PROPOSITION", "(DEFUN LINK-ORIGINATED-PROPOSITION ((OBJECT OBJECT) (PROPOSITION PROPOSITION)))", ((cpp_function_code)(&linkOriginatedProposition)), NULL);
    defineFunctionObject("HELP-FINALIZE-OBJECT-AXIOMS", "(DEFUN (HELP-FINALIZE-OBJECT-AXIOMS (CONS OF PROPOSITION)) ((THEAXIOMS CONS)))", ((cpp_function_code)(&helpFinalizeObjectAxioms)), NULL);
    defineFunctionObject("FINALIZE-OBJECT-AXIOMS", "(DEFUN FINALIZE-OBJECT-AXIOMS ((SELF OBJECT)))", ((cpp_function_code)(&finalizeObjectAxioms)), NULL);
    defineFunctionObject("CHECK-DESCRIPTION-ARGUMENT-TYPES", "(DEFUN CHECK-DESCRIPTION-ARGUMENT-TYPES ((SELF NAMED-DESCRIPTION)))", ((cpp_function_code)(&checkDescriptionArgumentTypes)), NULL);
    defineFunctionObject("FINALIZE-OBJECT", "(DEFUN FINALIZE-OBJECT ((SELF OBJECT)))", ((cpp_function_code)(&finalizeObject)), NULL);
    defineFunctionObject("FINALIZED-OBJECT?", "(DEFUN (FINALIZED-OBJECT? BOOLEAN) ((SELF OBJECT)))", ((cpp_function_code)(&finalizedObjectP)), NULL);
    defineFunctionObject("OBJECTS-ARE-FINALIZED?", "(DEFUN (OBJECTS-ARE-FINALIZED? BOOLEAN) () :GLOBALLY-INLINE? TRUE (RETURN (EMPTY? (THE-CONS-LIST *UNFINALIZED-OBJECTS*))))", ((cpp_function_code)(&objectsAreFinalizedP)), NULL);
    defineFunctionObject("FINALIZE-OBJECTS", "(DEFUN FINALIZE-OBJECTS () :DOCUMENTATION \"Finalize all currently unfinalized objects.\nThe user-level entry point for this is `(process-definitions)'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&finalizeObjects)), NULL);
    defineFunctionObject("HELP-DEFINE-RELATION-FROM-PARSE-TREE", "(DEFUN (HELP-DEFINE-RELATION-FROM-PARSE-TREE NAMED-DESCRIPTION) ((TREE CONS) (STRINGIFIEDSOURCE STRING)))", ((cpp_function_code)(&helpDefineRelationFromParseTree)), NULL);
    defineFunctionObject("PARSE-RELATION-PARAMETERS-TREE", "(DEFUN (PARSE-RELATION-PARAMETERS-TREE (LIST OF SYMBOL) (LIST OF TYPE) BOOLEAN) ((PARAMETERS CONS)))", ((cpp_function_code)(&parseRelationParametersTree)), NULL);
    defineFunctionObject("GET-IDENTICAL-RELATION", "(DEFUN (GET-IDENTICAL-RELATION NAMED-DESCRIPTION) ((NAME SYMBOL) (STRINGIFIEDSOURCE STRING)))", ((cpp_function_code)(&getIdenticalRelation)), NULL);
    defineMethodObject("(DEFMETHOD PROCESS-DEFINITION-OPTIONS ((SELF NAMED-DESCRIPTION) (OPTIONS OBJECT)))", wrapMethodCode(((cpp_method_code)(&NamedDescription::processDefinitionOptions))), NULL);
    defineFunctionObject("DEFFUNCTION", "(DEFUN (DEFFUNCTION NAMED-DESCRIPTION) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a logic function.  The accepted syntax is:\n	 \n (deffunction <funconst> (<vardecl>+) [:-> <vardecl>]\n    [:documentation <string>]\n    [:<= <sentence>] | [:=> <sentence>] |\n    [:<<= <sentence>] | [:=>> <sentence>] | \n    [:<=> <sentence>] | [:<=>> <sentence>] |\n    [:<<=> <sentence>] | [:<<=>> <sentence>] |\n    [:axioms {<sentence> | (<sentence>+)}]\n    [<keyword-option>*])\n	\nFunction parameters can be typed or untyped.  If the `:->' option is\nsupplied, it specifies the output variable of the function.  Otherwise,\nthe last variable in the parameter list is used as the output variable.\nSee `defrelation' for a description of `<keyword-option>'s.\n\")", ((cpp_function_code)(&deffunction)), ((cpp_function_code)(&deffunctionEvaluatorWrapper)));
    defineFunctionObject("CALL-DEFFUNCTION", "(DEFUN (CALL-DEFFUNCTION NAMED-DESCRIPTION) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of the `deffunction' command (which see).\nExpects the same arguments as `deffunction' but supplied as a list.\" :PUBLIC? TRUE)", ((cpp_function_code)(&callDeffunction)), NULL);
    defineFunctionObject("NORMALIZE-DEFFUNCTION-ARGUMENTS", "(DEFUN (NORMALIZE-DEFFUNCTION-ARGUMENTS CONS) ((ARGUMENTS CONS)))", ((cpp_function_code)(&normalizeDeffunctionArguments)), NULL);
    defineFunctionObject("DEFRELATION", "(DEFUN (DEFRELATION NAMED-DESCRIPTION) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a logic relation.  The accepted syntax is:\n	 \n (defrelation <relconst> (<vardecl>+)\n    [:documentation <string>]\n    [:<= <sentence>] | [:=> <sentence>] |\n    [:<<= <sentence>] | [:=>> <sentence>] | \n    [:<=> <sentence>] | [:<=>> <sentence>] |\n    [:<<=> <sentence>] | [:<<=>> <sentence>] |\n    [:axioms {<sentence> | (<sentence>+)}]\n    [<keyword-option>*])\n	\nRelation parameters can be typed or untyped.\n`<keyword-option>' represents a keyword followed by a value that states an\nassertion about `<relconst>'.  For example, including the option `:foo bar'\nstates that the proposition `(foo <relconst> bar)' is true.  `:foo (bar fum)'\nstates that both `(foo <relconst> bar)' and `(foo <relconst> fum)' are true.\n`:foo true' states that `(foo <relconst>)' is true, `:foo false' states that\n`(not (foo <relconst>))' is true.\n\")", ((cpp_function_code)(&defrelation)), ((cpp_function_code)(&defrelationEvaluatorWrapper)));
    defineFunctionObject("CALL-DEFRELATION", "(DEFUN (CALL-DEFRELATION NAMED-DESCRIPTION) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of the `defrelation' command (which see).\nExpects the same arguments as `defrelation' but supplied as a list.\" :PUBLIC? TRUE)", ((cpp_function_code)(&callDefrelation)), NULL);
    defineFunctionObject("NORMALIZE-DEFRELATION-ARGUMENTS", "(DEFUN (NORMALIZE-DEFRELATION-ARGUMENTS CONS) ((ARGUMENTS CONS)))", ((cpp_function_code)(&normalizeDefrelationArguments)), NULL);
    defineFunctionObject("DEFCONCEPT", "(DEFUN (DEFCONCEPT NAMED-DESCRIPTION) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a concept.  The accepted syntax is:\n	 \n (defconcept <conceptconst> [(<var> <parent>*)]\n    [:documentation <string>]\n    [:<= <sentence>] | [:=> <sentence>] |\n    [:<<= <sentence>] | [:=>> <sentence>] | \n    [:<=> <sentence>] | [:<=>> <sentence>] | [:<<=> <sentence>] |\n    [:<<=>> <sentence>] |\n    [:axioms {<sentence> | (<sentence>+)}] |\n    <keyword-option>*)\n	\nDeclaration of a concept variable `<var>' is optional, unless any\nimplication (arrow) options are supplied that need to reference it.  A\npossibly empty list of concept names following `<var>' is taken as the list\nof parents of `<conceptconst>'.  Alternatively, parents can be specified\nvia the `:=>' option.  If no parents are specified, the parent of\n`<conceptconst>' is taken to be THING.  `<keyword-option>' represents a\nkeyword followed by a value that states an assertion abo" "ut `<conceptconst>'.\nSee `defrelation' for a description of `<keyword-option>'s.\n\")", ((cpp_function_code)(&defconcept)), ((cpp_function_code)(&defconceptEvaluatorWrapper)));
    defineFunctionObject("CALL-DEFCONCEPT", "(DEFUN (CALL-DEFCONCEPT NAMED-DESCRIPTION) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of the `defconcept' command (which see).\nExpects the same arguments as `defconcept' but supplied as a list.\" :PUBLIC? TRUE)", ((cpp_function_code)(&callDefconcept)), NULL);
    defineFunctionObject("NORMALIZE-DEFCONCEPT-ARGUMENTS", "(DEFUN (NORMALIZE-DEFCONCEPT-ARGUMENTS CONS) ((ARGUMENTS CONS)))", ((cpp_function_code)(&normalizeDefconceptArguments)), NULL);
    defineFunctionObject("DEFINE-RELATION-FROM-PARSE-TREE", "(DEFUN (DEFINE-RELATION-FROM-PARSE-TREE NAMED-DESCRIPTION) ((TREE CONS)))", ((cpp_function_code)(&defineRelationFromParseTree)), NULL);
    defineFunctionObject("DEFOBJECT", "(DEFUN (DEFOBJECT LOGIC-OBJECT) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a logic instance.  The accepted syntax is:\n	 \n (defobject <constant>\n    [:documentation <string>]\n    [<keyword-option>*])\n	\n`<keyword-option>' represents a keyword followed by a value\nthat states an assertion about <constant>.  See `defrelation' for a\ndescription of `<keyword-option>'s.\n\n`defobject' provides a sugar-coated way to assert a collection of facts\nabout a logic constant, but otherwise adds nothing in terms of functionality.\n\")", ((cpp_function_code)(&defobject)), ((cpp_function_code)(&defobjectEvaluatorWrapper)));
    defineFunctionObject("DEFINSTANCE", "(DEFUN (DEFINSTANCE LOGIC-OBJECT) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a logic instance (`definstance' is an alias\nfor `defobject' which see).\")", ((cpp_function_code)(&definstance)), ((cpp_function_code)(&definstanceEvaluatorWrapper)));
    defineFunctionObject("CALL-DEFOBJECT", "(DEFUN (CALL-DEFOBJECT LOGIC-OBJECT) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of the `defobject' command (which see).\nExpects the same arguments as `defobject' but supplied as a list.\" :PUBLIC? TRUE)", ((cpp_function_code)(&callDefobject)), NULL);
    defineFunctionObject("NORMALIZE-DEFOBJECT-ARGUMENTS", "(DEFUN (NORMALIZE-DEFOBJECT-ARGUMENTS CONS) ((ARGUMENTS CONS)))", ((cpp_function_code)(&normalizeDefobjectArguments)), NULL);
    defineMethodObject("(DEFMETHOD PROCESS-DEFINITION-OPTIONS ((SELF LOGIC-OBJECT) (OPTIONS OBJECT)))", wrapMethodCode(((cpp_method_code)(&LogicObject::processDefinitionOptions))), NULL);
    defineFunctionObject("DEFPROPOSITION", "(DEFUN (DEFPROPOSITION PROPOSITION) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a named proposition.  The accepted syntax is:\n	 \n (defproposition <name> <sentence>\n    [:documentation <string>]\n    [:forward-only? {true | false}]\n    [:backward-only? {true | false}]\n    [:dont-optimize? {true | false}]\n    [:confidence-level {:strict | :default}]\n    [<keyword-option>*])\n	\n<sentence> can be any sentence that is legal as a top-level assertion.\n<name> can be a string or symbol and will be bound to the asserted\nproposition represented by <sentence>.  After this definition every\noccurrence of <name> will be replaced by the associated proposition.\n\nThe options :forward-only? and :backward-only? can be used to tell the\ninference engine to only use the rule in forward or backward direction\n(this can also be achieved by using the `<<=' or `=>>' implication\narrows).  :dont-optimize?  tells the inference engine to not rearr" "ange\nthe order of clauses in the antecedent of a rule and instead evaluate\nthem in their original order.  :confidence-level can be used to mark a\nproposition as default only.\n\n`<keyword-option>' represents a keyword followed by a value\nthat states an assertion about the proposition <name>.  See `defrelation'\nfor a description of `<keyword-option>'s.\n\")", ((cpp_function_code)(&defproposition)), ((cpp_function_code)(&defpropositionEvaluatorWrapper)));
    defineFunctionObject("DEFRULE", "(DEFUN (DEFRULE PROPOSITION) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a named rule (`defrule' is an alias\nfor `defproposition' which see).\")", ((cpp_function_code)(&defrule)), ((cpp_function_code)(&defruleEvaluatorWrapper)));
    defineFunctionObject("CALL-DEFPROPOSITION", "(DEFUN (CALL-DEFPROPOSITION PROPOSITION) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of the `defproposition' command (which see).\nExpects the same arguments as `defproposition' but supplied as a list.\" :PUBLIC? TRUE)", ((cpp_function_code)(&callDefproposition)), NULL);
    defineFunctionObject("NORMALIZE-DEFPROPOSITION-ARGUMENTS", "(DEFUN (NORMALIZE-DEFPROPOSITION-ARGUMENTS CONS) ((ARGUMENTS CONS)))", ((cpp_function_code)(&normalizeDefpropositionArguments)), NULL);
  }
}

void startupLogicIn() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupLogicIn1();
      helpStartupLogicIn2();
    }
    if (currentStartupTimePhaseP(4)) {
      helpStartupLogicIn3();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupLogicIn4();
      helpStartupLogicIn5();
      defineMethodObject("(DEFMETHOD PROCESS-DEFINITION-OPTIONS ((SELF PROPOSITION) (OPTIONS OBJECT)))", wrapMethodCode(((cpp_method_code)(&Proposition::processDefinitionOptions))), NULL);
      defineFunctionObject("COMMAND<", "(DEFUN (COMMAND< BOOLEAN) ((COMMAND1 METHOD-SLOT) (COMMAND2 METHOD-SLOT)))", ((cpp_function_code)(&commandL)), NULL);
      defineFunctionObject("LIST-LOGIC-COMMANDS", "(DEFUN (LIST-LOGIC-COMMANDS (LIST OF METHOD-SLOT)) ())", ((cpp_function_code)(&listLogicCommands)), NULL);
      defineFunctionObject("HELP", "(DEFUN HELP (|&REST| (COMMANDS SYMBOL)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Describe specific commands, or print a list of available commands.\")", ((cpp_function_code)(&help)), ((cpp_function_code)(&helpEvaluatorWrapper)));
      defineFunctionObject("STARTUP-LOGIC-IN", "(DEFUN STARTUP-LOGIC-IN () :PUBLIC? TRUE)", ((cpp_function_code)(&startupLogicIn)), NULL);
      { MethodSlot* function = lookupFunction(SYM_LOGIC_IN_LOGIC_STARTUP_LOGIC_IN);

        setDynamicSlotValue(function->dynamicSlots, SYM_LOGIC_IN_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupLogicIn"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFGLOBAL *AVAILABLE-POWERLOOM-FEATURES* (LIST OF KEYWORD) (LIST :TRACE-SUBGOALS :TRACE-SOLUTIONS :TRACE-CLASSIFIER :ITERATIVE-DEEPENING :JUSTIFICATIONS :JUST-IN-TIME-INFERENCE :EMIT-THINKING-DOTS) :DOCUMENTATION \"List of PowerLoom environment features.\")", &oAVAILABLE_POWERLOOM_FEATURESo);
      defineGlobalVariableObject("(DEFGLOBAL *CURRENT-POWERLOOM-FEATURES* (LIST OF KEYWORD) (LIST) :DOCUMENTATION \"List of currently enabled PowerLoom environment features.\")", &oCURRENT_POWERLOOM_FEATURESo);
      defineGlobalVariableObject("(DEFGLOBAL *DEFAULT-POWERLOOM-FEATURES* (LIST OF KEYWORD) (LIST :JUST-IN-TIME-INFERENCE :EMIT-THINKING-DOTS) :DOCUMENTATION \"List of PowerLoom environment features enabled upon call to\n'reset-features'.\")", &oDEFAULT_POWERLOOM_FEATURESo);
      defineGlobalVariableObject("(DEFGLOBAL *LOGIC-PROMPT* STRING \"|= \" :DOCUMENTATION \"The prompt used by the PowerLoom listener.\" :PUBLIC? TRUE)", &oLOGIC_PROMPTo);
      defineGlobalVariableObject("(DEFSPECIAL *PROMPT-SHOW-MODULE?* BOOLEAN TRUE :DOCUMENTATION \"Flag to control whether the logic prompt shows the module name.\" :PUBLIC? TRUE)", &oPROMPT_SHOW_MODULEpo);
      defineGlobalVariableObject("(DEFGLOBAL *LOGIC-COMMAND-RESULT-INDENT* STRING \"\")", &oLOGIC_COMMAND_RESULT_INDENTo);
      defineGlobalVariableObject("(DEFSPECIAL *CONFIRM-INTERACTIVE-EXIT?* BOOLEAN (VERBATIM :COMMON-LISP FALSE :OTHERWISE TRUE) :DOCUMENTATION \"If TRUE exiting from the logic-command loop (or PowerLoom\nlistener) will be protected by a confirmation dialog.  This is mainly useful\nfor C++ and Java where exiting the listener will also exit the program.\" :PUBLIC? TRUE :DEMON-PROPERTY \"powerloom.confirmInteractiveExit\")", &oCONFIRM_INTERACTIVE_EXITpo);
      defineGlobalVariableObject("(DEFGLOBAL *POWERLOOM-KB-FILE-EXTENSIONS* CONS (QUOTE (\".plm\" \".ploom\")) :DOCUMENTATION \"If the extension of a KB file is unspecified in a\n`load' or `demo' command, try to find it with one of these extensions.\" :PUBLIC? TRUE)", &oPOWERLOOM_KB_FILE_EXTENSIONSo);
      addLoadPath("PL:kbs;");
      defineGlobalVariableObject("(DEFSPECIAL *ASSERTION-MODULE* MODULE NULL :DOCUMENTATION \"If non-NULL, definition axioms and assertions will be evaluated\nin this module instead of the IN-MODULE of a file, which allows us to separate\nvocabulary definitions and their definitional constraints.\")", &oASSERTION_MODULEo);
      defineGlobalVariableObject("(DEFSPECIAL *DEMO-LEVEL* INTEGER 0)", &oDEMO_LEVELo);
      addLoadPath("PL:sources;logic;demos;");
      defineGlobalVariableObject("(DEFGLOBAL *DEMO-FILES* (CONS OF (CONS OF STRING-WRAPPER)) (BQUOTE ((\"basics\" \"Basic PowerLoom commands\" \"test-suite\") (\"classes\" \"Primitive and defined classes\" \"test-suite\") (\"collections\" \"Reasoning with collections\" \"test-suite\") (\"append\" \"Prolog-style `append'\" \"test-suite\") (\"inequalities\" \"Reasoning with inequalities\" \"test-suite\") (\"recursion\" \"Reasoning with recursive rules\" \"test-suite\") (\"negation\" \"Reasoning with negation\" \"test-suite\") (\"constraints\" \"Constraint propagation\" \"test-suite\") (\"equations\" \"Simple equational reasoning\" \"test-suite\") (\"subsumption\" \"Simple subsumption reasoning\" \"test-suite\") (\"family\" \"Subsumption reasoning within a family ontology\" \"test-suite\") (\"relation-hierarchy\" \"Finding sub, super and equivalent concepts and relations\" \"test-suite\") (\"defaults\" \"Default reasoning with Tweety and friends\" \"test-suite\") (\"defaults2\" \"More default reasoning\" \"test-suite\") (\"definition-syntax\" \"" "The whole scoop on relation definition, funny arrows, etc.\" \"test-suite\") (\"meta-relations\" \"Using meta-properties and relations\" \"test-suite\") (\"partial-match\" \"Reasoning with partial information\" \"test-suite\") (\"probability-learning\" \"Learning to answer probabilistic queries\" \"test-suite\") (\"regression-demo\" \"Learning to predict functions\") (\"rule-induction-demo\" \"Learning inference rules\") (\"test-suite\" \"PowerLoom test suite\" \"test-suite\"))) :DOCUMENTATION \"List of example demo files.\nEach entry is a `(<file> <description>)' pair.\")", &oDEMO_FILESo);
      defineGlobalVariableObject("(DEFSPECIAL *TERMSOURCEBEINGPARSED* STRING NULL :DOCUMENTATION \"Points to the source of the relation being parsed.\")", &oTERMSOURCEBEINGPARSEDo);
      defineGlobalVariableObject("(DEFSPECIAL *DESCRIPTIONUNDERCONSTRUCTION* OBJECT NULL :DOCUMENTATION \"Pofints to a description or its parse tree which\nis the input to the description being constructed.\")", &oDESCRIPTIONUNDERCONSTRUCTIONo);
      defineGlobalVariableObject("(DEFSPECIAL *TERMUNDERCONSTRUCTION* OBJECT NULL :DOCUMENTATION \"Points to the parse tree which is the input to the\nproposition being constructed.\")", &oTERMUNDERCONSTRUCTIONo);
      defineGlobalVariableObject("(DEFGLOBAL *EXPRESSION-SIZE-CUTOFF* INTEGER 300 :DOCUMENTATION \"Limit on how big an s-expression we will print within\nan error message.\")", &oEXPRESSION_SIZE_CUTOFFo);
      defineGlobalVariableObject("(DEFGLOBAL *HANDLE-EXPLICITLY-QUALIFIED-LOGIC-OBJECTS?* BOOLEAN TRUE)", &oHANDLE_EXPLICITLY_QUALIFIED_LOGIC_OBJECTSpo);
      defineGlobalVariableObject("(DEFGLOBAL *UNFINALIZED-OBJECTS* LIST (LIST) :DOCUMENTATION \"List of objects whose definitions and/or associated\naxioms and constraints are not yet processed.\")", &oUNFINALIZED_OBJECTSo);
      defineGlobalVariableObject("(DEFSPECIAL *FINALIZEOBJECTSIMMEDIATELY?* BOOLEAN FALSE)", &oFINALIZEOBJECTSIMMEDIATELYpo);
      defineGlobalVariableObject("(DEFSPECIAL *INHIBITOBJECTFINALIZATION?* BOOLEAN FALSE :DOCUMENTATION \"Used to prevent finalization from triggering in the\nmiddle of 'delicate' computations.  Also used to prevent recursive\ninvocation of 'finalize-objects'.\")", &oINHIBITOBJECTFINALIZATIONpo);
      defineGlobalVariableObject("(DEFGLOBAL *LOGIC-RELEVANT-STELLA-COMMANDS* (CONS OF SYMBOL) (BQUOTE (CC CLEAR-MODULE DEFMODULE IN-MODULE LIST-MODULES)))", &oLOGIC_RELEVANT_STELLA_COMMANDSo);
    }
  }
}

Keyword* KWD_LOGIC_IN_TRACE_SUBGOALS = NULL;

Keyword* KWD_LOGIC_IN_TRACE_SOLUTIONS = NULL;

Keyword* KWD_LOGIC_IN_TRACE_CLASSIFIER = NULL;

Keyword* KWD_LOGIC_IN_ITERATIVE_DEEPENING = NULL;

Keyword* KWD_LOGIC_IN_JUSTIFICATIONS = NULL;

Keyword* KWD_LOGIC_IN_JUST_IN_TIME_INFERENCE = NULL;

Keyword* KWD_LOGIC_IN_EMIT_THINKING_DOTS = NULL;

Keyword* KWD_LOGIC_IN_GOAL_TREE = NULL;

Keyword* KWD_LOGIC_IN_CLASSIFIER_INFERENCES = NULL;

Keyword* KWD_LOGIC_IN_CLOSED_WORLD = NULL;

Keyword* KWD_LOGIC_IN_REALISTIC = NULL;

Keyword* KWD_LOGIC_IN_BYE = NULL;

Keyword* KWD_LOGIC_IN_EXIT = NULL;

Keyword* KWD_LOGIC_IN_HALT = NULL;

Keyword* KWD_LOGIC_IN_QUIT = NULL;

Keyword* KWD_LOGIC_IN_STOP = NULL;

Keyword* KWD_LOGIC_IN_DEFINE = NULL;

Surrogate* SGT_LOGIC_IN_STELLA_CONS = NULL;

Symbol* SYM_LOGIC_IN_STELLA_DEFMODULE = NULL;

Keyword* KWD_LOGIC_IN_FINALIZE = NULL;

Keyword* KWD_LOGIC_IN_OPTIONS = NULL;

Symbol* SYM_LOGIC_IN_STELLA_CLEAR_MODULE = NULL;

Symbol* SYM_LOGIC_IN_STELLA_DEFCLASS = NULL;

Symbol* SYM_LOGIC_IN_STELLA_DEFSLOT = NULL;

Symbol* SYM_LOGIC_IN_STELLA_DEFUN = NULL;

Symbol* SYM_LOGIC_IN_STELLA_DEFMETHOD = NULL;

Symbol* SYM_LOGIC_IN_LOGIC_DEFCONCEPT = NULL;

Symbol* SYM_LOGIC_IN_LOGIC_DEFFUNCTION = NULL;

Symbol* SYM_LOGIC_IN_LOGIC_DEFRELATION = NULL;

Symbol* SYM_LOGIC_IN_LOGIC_DEFOBJECT = NULL;

Symbol* SYM_LOGIC_IN_LOGIC_DEFINSTANCE = NULL;

Symbol* SYM_LOGIC_IN_LOGIC_DESTROY = NULL;

Symbol* SYM_LOGIC_IN_LOGIC_IN_DIALECT = NULL;

Symbol* SYM_LOGIC_IN_STELLA_CC = NULL;

Keyword* KWD_LOGIC_IN_IMMEDIATE = NULL;

Keyword* KWD_LOGIC_IN_ALWAYS = NULL;

Keyword* KWD_LOGIC_IN_DEFERRED = NULL;

Keyword* KWD_LOGIC_IN_CHECK_DUPLICATESp = NULL;

Surrogate* SGT_LOGIC_IN_STELLA_BOOLEAN = NULL;

Keyword* KWD_LOGIC_IN_MODULE = NULL;

Surrogate* SGT_LOGIC_IN_STELLA_MODULE = NULL;

Keyword* KWD_LOGIC_IN_ASSERTION_MODULE = NULL;

Surrogate* SGT_LOGIC_IN_STELLA_IDENTITY = NULL;

Keyword* KWD_LOGIC_IN_LOW = NULL;

Keyword* KWD_LOGIC_IN_MEDIUM = NULL;

Keyword* KWD_LOGIC_IN_WHITE_SPACE = NULL;

Keyword* KWD_LOGIC_IN_LEVEL = NULL;

Keyword* KWD_LOGIC_IN_NONE = NULL;

Keyword* KWD_LOGIC_IN_PORT = NULL;

Surrogate* SGT_LOGIC_IN_STELLA_INTEGER = NULL;

Keyword* KWD_LOGIC_IN_HOST = NULL;

Surrogate* SGT_LOGIC_IN_STELLA_STRING = NULL;

Keyword* KWD_LOGIC_IN_DEBUG_LEVEL = NULL;

Keyword* KWD_LOGIC_IN_ERROR = NULL;

Keyword* KWD_LOGIC_IN_WARNING = NULL;

Surrogate* SGT_LOGIC_IN_LOGIC_NAMED_DESCRIPTION = NULL;

Surrogate* SGT_LOGIC_IN_LOGIC_PROPOSITION = NULL;

Surrogate* SGT_LOGIC_IN_LOGIC_DESCRIPTION = NULL;

Surrogate* SGT_LOGIC_IN_STELLA_RELATION = NULL;

Symbol* SYM_LOGIC_IN_LOGIC_MODULE_LOGIC_DIALECT = NULL;

Keyword* KWD_LOGIC_IN_KIF = NULL;

Surrogate* SGT_LOGIC_IN_LOGIC_LOGIC_OBJECT = NULL;

Keyword* KWD_LOGIC_IN_DEFINITION = NULL;

Keyword* KWD_LOGIC_IN_REDEFINITION = NULL;

Keyword* KWD_LOGIC_IN_PROPER_DEFINITION = NULL;

Symbol* SYM_LOGIC_IN_LOGIC_OBJECT_AXIOMS = NULL;

Symbol* SYM_LOGIC_IN_LOGIC_PROPOSITION_AXIOMS = NULL;

Symbol* SYM_LOGIC_IN_STELLA_SLOT_OPTION_KEYWORD = NULL;

Symbol* SYM_LOGIC_IN_STELLA_AND = NULL;

Surrogate* SGT_LOGIC_IN_STELLA_THING = NULL;

Symbol* SYM_LOGIC_IN_STELLA_FORALL = NULL;

Symbol* SYM_LOGIC_IN_STELLA_NOT = NULL;

Keyword* KWD_LOGIC_IN_ASSERT_TRUE = NULL;

Symbol* SYM_LOGIC_IN_STELLA_BADp = NULL;

Symbol* SYM_LOGIC_IN_PL_KERNEL_KB_NTH_DOMAIN = NULL;

Symbol* SYM_LOGIC_IN_PL_KERNEL_KB_DOMAIN = NULL;

Symbol* SYM_LOGIC_IN_PL_KERNEL_KB_RANGE = NULL;

Keyword* KWD_LOGIC_IN__g = NULL;

Symbol* SYM_LOGIC_IN_LOGIC_pSELF = NULL;

Keyword* KWD_LOGIC_IN_eg = NULL;

Symbol* SYM_LOGIC_IN_LOGIC_DEFPROPOSITION = NULL;

Keyword* KWD_LOGIC_IN_CONCEIVE = NULL;

Keyword* KWD_LOGIC_IN_FORALL = NULL;

Symbol* SYM_LOGIC_IN_LOGIC_SATELLITE_PROPOSITIONS = NULL;

Keyword* KWD_LOGIC_IN_CONFIDENCE_LEVEL = NULL;

Keyword* KWD_LOGIC_IN_DEFAULT = NULL;

Keyword* KWD_LOGIC_IN_PRESUME_TRUE = NULL;

Keyword* KWD_LOGIC_IN_FORWARDp = NULL;

Keyword* KWD_LOGIC_IN_FORWARD_ONLYp = NULL;

Keyword* KWD_LOGIC_IN_BACKWARDp = NULL;

Keyword* KWD_LOGIC_IN_BACKWARD_ONLYp = NULL;

Keyword* KWD_LOGIC_IN_WEIGHT = NULL;

Symbol* SYM_LOGIC_IN_LOGIC_ABOUT = NULL;

Symbol* SYM_LOGIC_IN_STELLA_IN_MODULE = NULL;

Symbol* SYM_LOGIC_IN_STELLA_LIST_MODULES = NULL;

Symbol* SYM_LOGIC_IN_STELLA_METHOD_COMMANDp = NULL;

Symbol* SYM_LOGIC_IN_STELLA_DOCUMENTATION = NULL;

Symbol* SYM_LOGIC_IN_LOGIC_STARTUP_LOGIC_IN = NULL;

Symbol* SYM_LOGIC_IN_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
