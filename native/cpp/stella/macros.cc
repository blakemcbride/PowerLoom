//  -*- Mode: C++ -*-

// macros.cc

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

Object* pushq(Symbol* variable, Object* value) {
  // Push 'value' onto the cons list 'variable'.
  return (listO(3, SYM_MACROS_STELLA_SETQ, variable, cons(listO(3, SYM_MACROS_STELLA_CONS, value, cons(variable, NIL)), NIL)));
}

Object* popq(Symbol* variable) {
  // Pops a value from the cons list 'variable'.
  { Symbol* valuevar = localGensym("HEAD");

    return (listO(5, SYM_MACROS_STELLA_VRLET, cons(cons(valuevar, cons(listO(3, SYM_MACROS_STELLA_VALUE, variable, NIL), NIL)), NIL), listO(3, SYM_MACROS_STELLA_SETQ, variable, cons(listO(3, SYM_MACROS_STELLA_REST, variable, NIL), NIL)), valuevar, NIL));
  }
}

Object* pushf(Cons* place, Object* value) {
  // Push 'value' onto the cons list 'place'.
  { Cons* placecopy = ((Cons*)(copyConsTree(place)));

    return (listO(3, SYM_MACROS_STELLA_SETF, place, cons(listO(3, SYM_MACROS_STELLA_CONS, value, cons(placecopy, NIL)), NIL)));
  }
}

Object* pushqNew(Symbol* variable, Object* value) {
  // Push `value' onto the cons list `variable', unless `value'
  // is already a member of the list.
  if (consP(value)) {
    { Symbol* valuevar = localGensym("VALUE");

      return (listO(4, SYM_MACROS_STELLA_VRLET, cons(cons(valuevar, cons(value, NIL)), NIL), listO(3, SYM_MACROS_STELLA_SETQ, variable, cons(listO(4, SYM_MACROS_STELLA_CHOOSE, listO(3, SYM_MACROS_STELLA_MEMBERp, variable, cons(valuevar, NIL)), variable, cons(listO(3, SYM_MACROS_STELLA_CONS, valuevar, cons(variable, NIL)), NIL)), NIL)), NIL));
    }
  }
  else {
    return (listO(3, SYM_MACROS_STELLA_SETQ, variable, cons(listO(4, SYM_MACROS_STELLA_CHOOSE, listO(3, SYM_MACROS_STELLA_MEMBERp, variable, cons(value, NIL)), variable, cons(listO(3, SYM_MACROS_STELLA_CONS, value, cons(variable, NIL)), NIL)), NIL)));
  }
}

Object* stella_Increment(Object* place, Cons* increment) {
  // Increment the value of `place' and return the result.
  // `place' can be either a variable name or a slot reference.  Increment by
  // the optional `increment' (which can be a float) or 1 otherwise.
  { Object* incr = increment->value;

    if (!(symbolP(place) ||
        consP(place))) {
      if (!((boolean)(place))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing place in `++' expression" << "." << std::endl;
          }
        }
      }
      else {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal place in `++' expression: " << "`" << deUglifyParseTree(place) << "'" << "." << std::endl;
          }
        }
      }
      return (NIL);
    }
    if (!((boolean)(incr))) {
      incr = ONE_WRAPPER;
    }
    return ((symbolP(place) ? listO(3, SYM_MACROS_STELLA_SETQ, place, cons(listO(3, SYM_MACROS_STELLA_i, place, cons(incr, NIL)), NIL)) : listO(3, SYM_MACROS_STELLA_SETF, place, cons(listO(3, SYM_MACROS_STELLA_i, copyConsTree(place), cons(incr, NIL)), NIL))));
  }
}

Object* stella_Decrement(Object* place, Cons* decrement) {
  // Decrement the value of `place' and return the result.
  // `place' can be either a variable name or a slot reference.  Decrement by
  // the optional `decrement' (which can be a float) or 1 otherwise.
  { Object* decr = decrement->value;

    if (!(symbolP(place) ||
        consP(place))) {
      if (!((boolean)(place))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing place in `--' expression" << "." << std::endl;
          }
        }
      }
      else {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal place in `--' expression: " << "`" << deUglifyParseTree(place) << "'" << "." << std::endl;
          }
        }
      }
      return (NIL);
    }
    if (!((boolean)(decr))) {
      decr = ONE_WRAPPER;
    }
    return ((symbolP(place) ? listO(3, SYM_MACROS_STELLA_SETQ, place, cons(listO(3, SYM_MACROS_STELLA__, place, cons(decr, NIL)), NIL)) : listO(3, SYM_MACROS_STELLA_SETF, place, cons(listO(3, SYM_MACROS_STELLA__, copyConsTree(place), cons(decr, NIL)), NIL))));
  }
}

Object* oneI(Object* expression) {
  // Add 1 to 'expression' and return the result.
  return (listO(3, SYM_MACROS_STELLA_i, expression, cons(wrapInteger(1), NIL)));
}

Object* one(Object* expression) {
  // Subtract 1 from 'expression' and return the result.
  return (listO(3, SYM_MACROS_STELLA__, expression, cons(wrapInteger(1), NIL)));
}

Object* setqP(Symbol* variable, Cons* expression) {
  // Assign 'variable' the result of evaluating 'expression', 
  // and return TRUE if 'expression' is not NULL else return FALSE.
  return (listO(5, SYM_MACROS_STELLA_VRLET, NIL, listO(3, SYM_MACROS_STELLA_SETQ, variable, cons(expression, NIL)), listO(3, SYM_MACROS_STELLA_DEFINEDp, variable, NIL), NIL));
}

Object* firstDefined(Cons* forms) {
  // Return the result of the first form in `forms' whose value is defined
  // or NULL otherwise.
  switch (forms->length()) {
    case 0: 
      return (SYM_MACROS_STELLA_NULL);
    case 1: 
      return (forms->value);
    case 2: 
      if (symbolP(forms->value)) {
        return (listO(4, SYM_MACROS_STELLA_CHOOSE, listO(3, SYM_MACROS_STELLA_DEFINEDp, forms->value, NIL), forms->value, cons(forms->rest->value, NIL)));
      }
      else {
        { Symbol* letvariable = localGensym("TEMP");

          return (listO(4, SYM_MACROS_STELLA_VRLET, cons(cons(letvariable, cons(forms->value, NIL)), NIL), listO(4, SYM_MACROS_STELLA_CHOOSE, listO(3, SYM_MACROS_STELLA_DEFINEDp, letvariable, NIL), letvariable, cons(forms->rest->value, NIL)), NIL));
        }
      }
      break;
    default:
      return (listO(3, SYM_MACROS_STELLA_FIRST_DEFINED, forms->value, cons(cons(SYM_MACROS_STELLA_FIRST_DEFINED, forms->rest->concatenate(NIL, 0)), NIL)));
  }
}

Object* allDefinedP(Cons* forms) {
  // Evaluate each of the forms in 'forms', and
  // return TRUE if none of them are NULL.
  switch (forms->length()) {
    case 0: 
      return (SYM_MACROS_STELLA_TRUE);
    case 1: 
      return (listO(3, SYM_MACROS_STELLA_DEFINEDp, forms->value, NIL));
    default:
      { Cons* tests = NIL;

        { Object* f = NULL;
          Cons* iter000 = forms;
          Cons* collect000 = NULL;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest) {
            f = iter000->value;
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(listO(3, SYM_MACROS_STELLA_DEFINEDp, f, NIL), NIL);
                if (tests == NIL) {
                  tests = collect000;
                }
                else {
                  addConsToEndOfConsList(tests, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(listO(3, SYM_MACROS_STELLA_DEFINEDp, f, NIL), NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        return (cons(SYM_MACROS_STELLA_AND, tests->concatenate(NIL, 0)));
      }
      break;
  }
}

Object* either(Object* value1, Object* value2) {
  // If 'value1' is defined, return that, else return 'value2'.
  return (listO(3, SYM_MACROS_STELLA_FIRST_DEFINED, value1, cons(value2, NIL)));
}

Object* collect(Cons* body) {
  // Use a VRLET to collect values.  Input can have one of
  // the following forms:
  // 	 
  //   (collect <var> in <expression> [where <test> <var>])
  //   (collect <collect-expression>
  //            foreach <var> in <expression>
  //            {as ...}*
  //            [where <test> <var>]
  //            [do ...])
  // 	
  // The second form really accepts an arbitrary `foreach' expression following
  // the `foreach' keyword.
  { Symbol* collection = localGensym("VALUE");

    if (body->rest->value == SYM_MACROS_STELLA_FOREACH) {
      return (listO(5, SYM_MACROS_STELLA_VRLET, cons(cons(collection, cons(SYM_MACROS_STELLA_NIL, NIL)), NIL), cons(SYM_MACROS_STELLA_FOREACH, body->rest->rest->concatenate(listO(3, SYM_MACROS_STELLA_COLLECT, body->value, listO(3, SYM_MACROS_STELLA_INTO, collection, NIL)), 0)), collection, NIL));
    }
    else {
      return (listO(5, SYM_MACROS_STELLA_VRLET, cons(cons(collection, cons(SYM_MACROS_STELLA_NIL, NIL)), NIL), listO(3, SYM_MACROS_STELLA_FOREACH, body->value, body->rest->concatenate(listO(3, SYM_MACROS_STELLA_COLLECT, body->value, listO(3, SYM_MACROS_STELLA_INTO, collection, NIL)), 0)), collection, NIL));
    }
  }
}

Object* withPermanentObjects(Cons* body) {
  // Allocate 'permanent' (as opposed to 'transient')
  // objects within the scope of this declaration.
  return (listO(3, SYM_MACROS_STELLA_SPECIAL, cons(listO(3, SYM_MACROS_STELLA_oTRANSIENTOBJECTSpo, SYM_MACROS_STELLA_FALSE, NIL), NIL), body->concatenate(NIL, 0)));
}

Object* withTransientObjects(Cons* body) {
  // Allocate 'transient' (as opposed to 'permanent')
  // objects within the scope of this declaration.
  // CAUTION: The default assumption is the allocation of permanent objects.
  // The scope of `with-transient-objects' should be as small as possible, and
  // the user has to make sure that code that wasn't explicitly written to
  // account for transient objects will continue to work correctly.
  return (listO(3, SYM_MACROS_STELLA_SPECIAL, cons(listO(3, SYM_MACROS_STELLA_oTRANSIENTOBJECTSpo, SYM_MACROS_STELLA_TRUE, NIL), NIL), body->concatenate(NIL, 0)));
}

Object* ignore(Cons* variables) {
  // Ignore unused 'variables' with NoOp 'setq' statements.
  { Cons* ignoretrees = NIL;

    { Object* variable = NULL;
      Cons* iter000 = variables;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        variable = iter000->value;
        setLocalVariableInfo(((Symbol*)(variable)), KWD_MACROS_READ_ONLYp, FALSE_WRAPPER);
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(listO(3, SYM_MACROS_STELLA_SETQ, variable, cons(variable, NIL)), NIL);
            if (ignoretrees == NIL) {
              ignoretrees = collect000;
            }
            else {
              addConsToEndOfConsList(ignoretrees, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(listO(3, SYM_MACROS_STELLA_SETQ, variable, cons(variable, NIL)), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (prognify(ignoretrees));
  }
}

Object* onlyIf(Object* test, Object* expression) {
  // If 'test' is TRUE, return the result of evaluating 
  // 'expression'.
  return (listO(3, SYM_MACROS_STELLA_CHOOSE, test, cons(expression, cons(SYM_MACROS_STELLA_NULL, NIL))));
}

Object* phaseToInteger(Keyword* startuptimephase) {
  // Expands into the integer representing 'startupTimePhase'.
  return (wrapInteger(encodeStartupTimePhase(startuptimephase)));
}

Object* ifOutputLanguage(Keyword* language, Object* thenform, Object* elseform) {
  // Expand to 'thenForm' if the current translator output
  // language equals 'language'.  Otherwise, expand to 'elseForm'.  This can
  // be used to conditionally translate Stella code.
  if (language == oTRANSLATOROUTPUTLANGUAGEo) {
    return (((thenform == SYM_MACROS_STELLA_NULL) ? NULL : thenform));
  }
  else {
    return (((elseform == SYM_MACROS_STELLA_NULL) ? NULL : elseform));
  }
}

Object* ifStellaFeature(Keyword* feature, Object* thenform, Object* elseform) {
  // Expand to 'thenForm' if 'feature' is a currently enabled
  // STELLA environment feature.  Otherwise, expand to 'elseForm'.  This can
  // be used to conditionally translate Stella code.
  if (oCURRENT_STELLA_FEATURESo->membP(feature)) {
    return (((thenform == SYM_MACROS_STELLA_NULL) ? NULL : thenform));
  }
  else {
    return (((elseform == SYM_MACROS_STELLA_NULL) ? NULL : elseform));
  }
}

Object* withinWorld(Object* worldform, Cons* body) {
  // Execute `body' within the world resulting from `worldForm'.
  return (listO(4, SYM_MACROS_STELLA_SPECIAL, cons(listO(3, SYM_MACROS_STELLA_oCONTEXTo, worldform, NIL), NIL), listO(7, SYM_MACROS_STELLA_SAFETY, wrapInteger(3), listO(4, SYM_MACROS_STELLA_EQLp, listO(3, SYM_MACROS_STELLA_BASE_MODULE, listO(4, SYM_MACROS_STELLA_CAST, SYM_MACROS_STELLA_oCONTEXTo, SYM_MACROS_STELLA_WORLD, NIL), NIL), SYM_MACROS_STELLA_oMODULEo, NIL), wrapString("within-world: The base module of world "), SYM_MACROS_STELLA_oCONTEXTo, wrapString(" does not match the current module."), NIL), body->concatenate(NIL, 0)));
}

Object* withinContext(Object* contextform, Cons* body) {
  // Execute `body' within the context resulting from `contextForm'.
  return (listO(3, SYM_MACROS_STELLA_SPECIAL, listO(3, listO(3, SYM_MACROS_STELLA_oCONTEXTo, contextform, NIL), listO(3, SYM_MACROS_STELLA_oMODULEo, listO(3, SYM_MACROS_STELLA_BASE_MODULE, SYM_MACROS_STELLA_oCONTEXTo, NIL), NIL), NIL), body->concatenate(NIL, 0)));
}

Object* withinModule(Object* moduleform, Cons* body) {
  // Execute `body' within the module resulting from `moduleForm'.
  // `*module*' is an acceptable `moduleForm'.  It will locally rebind 
  // `*module*' and `*context*' and shield the outer bindings from changes.
  return (listO(3, SYM_MACROS_STELLA_SPECIAL, listO(3, listO(3, SYM_MACROS_STELLA_oMODULEo, moduleform, NIL), listO(3, SYM_MACROS_STELLA_oCONTEXTo, SYM_MACROS_STELLA_oMODULEo, NIL), NIL), body->concatenate(NIL, 0)));
}

Object* coerceARestToCons(Symbol* restvariable) {
  // Coerce the argument list variable `restVariable' into a CONS
  // list containing all its elements (uses argument list iteration to do so).  If
  // `restVariable' already is a CONS due to argument listification, this is a no-op.
  { StandardObject* dummy1;

    if (passVariableArgumentsAsListP(oMETHODBEINGWALKEDo)) {
      return (sysTree(walkWithoutTypeTree(restvariable), yieldListifiedVariableArgumentsType(oMETHODBEINGWALKEDo), dummy1));
    }
    else {
      { Symbol* argvar = localGensym("ARG");
        Symbol* listvar = localGensym("ARGLIST");

        return (listO(5, SYM_MACROS_STELLA_VRLET, cons(cons(listvar, cons(yieldListifiedVariableArgumentsType(oMETHODBEINGWALKEDo), cons(SYM_MACROS_STELLA_NIL, NIL))), NIL), listO(3, SYM_MACROS_STELLA_FOREACH, argvar, listO(3, SYM_MACROS_STELLA_IN, restvariable, listO(3, SYM_MACROS_STELLA_COLLECT, argvar, listO(3, SYM_MACROS_STELLA_INTO, listvar, NIL)))), listvar, NIL));
      }
    }
  }
}

Object* withSystemDefinition(Object* systemnameexpression, Cons* body) {
  // Set *currentSystemDefinition* to the system definition named `system'.
  // Set *currentSystemDefinitionSubdirectory* to match. Execute `body' within
  // that scope.
  return (listO(4, SYM_MACROS_STELLA_SPECIAL, listO(3, listO(3, SYM_MACROS_STELLA_oCURRENTSYSTEMDEFINITIONo, listO(3, SYM_MACROS_STELLA_GET_SYSTEM_DEFINITION, systemnameexpression, cons(SYM_MACROS_STELLA_TRUE, NIL)), NIL), listO(3, SYM_MACROS_STELLA_oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo, listO(3, SYM_MACROS_STELLA_DIRECTORY, SYM_MACROS_STELLA_oCURRENTSYSTEMDEFINITIONo, NIL), NIL), NIL), cons(SYM_MACROS_STELLA_PROGN, body->concatenate(NIL, 0)), NIL));
}

Object* defmain(Cons* varlist, Cons* body) {
  // Defines a function called MAIN which will have the appropriate
  // signature for the target translation language.  The signature will be:
  //   C++:   public static int main (int v1, char** v2) {<body>}
  //   Java:  public static void main (String [] v2) {<body>}
  //   Lisp:  (defun main (&rest args) <body>)
  // The argument `varList' must have two symbols, which will be the names for the
  // INTEGER argument count and an array of STRINGs with the argument values.  It
  // can also be empty to indicate that no command line arguments will be handled.
  // The startup function for the containing system will automatically be called
  // before `body' is executed unless the option :STARTUP-SYSTEM? was supplied as
  // FALSE.  There can only be one DEFMAIN per module.
  { boolean processcmdlineargsP = !(varlist == NIL);
    Symbol* v1Name = ((Symbol*)(varlist->value));
    Symbol* v2Name = ((Symbol*)(varlist->rest->value));
    Symbol* mainname = internSymbolInModule("MAIN", oMODULEo, true);
    Cons* bodywithheader = cons(NULL, body);

    { PropertyList* self000 = newPropertyList();

      self000->thePlist = extractOptions(bodywithheader, NULL);
      { PropertyList* options = self000;
        Cons* startupfunctioncall = ((((boolean)(oCURRENTSYSTEMDEFINITIONo)) &&
            (!(options->lookup(KWD_MACROS_STARTUP_SYSTEMp) == SYM_MACROS_STELLA_FALSE))) ? cons(cons(systemStartupFunctionSymbol(oCURRENTSYSTEMDEFINITIONo), NIL), NIL) : NIL);

        startupfunctioncall = cons(listO(5, SYM_MACROS_STELLA_IF_STELLA_FEATURE, KWD_MACROS_SUPPORT_UNEXEC, listO(6, SYM_MACROS_STELLA_VERBATIM, KWD_MACROS_CPP, wrapString("freopen (\"/dev/tty\",\"w\",stdout); freopen (\"/dev/tty\",\"w\",stderr); freopen (\"/dev/tty\",\"r\",stdin)"), KWD_MACROS_OTHERWISE, SYM_MACROS_STELLA_NULL, NIL), SYM_MACROS_STELLA_NULL, NIL), startupfunctioncall->concatenate(NIL, 0));
        options->removeAt(KWD_MACROS_STARTUP_SYSTEMp);
        options->removeAt(KWD_MACROS_PUBLICp);
        body = options->thePlist->concatenate(bodywithheader->rest, 0);
        if (!processcmdlineargsP) {
          if (oTRANSLATOROUTPUTLANGUAGEo == KWD_MACROS_COMMON_LISP) {
            return (listO(3, SYM_MACROS_STELLA_DEFUN, mainname, listO(4, NIL, KWD_MACROS_PUBLICp, SYM_MACROS_STELLA_TRUE, startupfunctioncall->concatenate(body->concatenate(NIL, 0), 0))));
          }
          else if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_MACROS_CPP) ||
              ((oTRANSLATOROUTPUTLANGUAGEo == KWD_MACROS_CPP_STANDALONE) ||
               (oTRANSLATOROUTPUTLANGUAGEo == KWD_MACROS_IDL))) {
            return (listO(6, SYM_MACROS_STELLA_DEFUN, cons(mainname, cons(SYM_MACROS_STELLA_INTEGER, NIL)), NIL, KWD_MACROS_PUBLICp, SYM_MACROS_STELLA_TRUE, startupfunctioncall->concatenate(body->concatenate(cons(listO(3, SYM_MACROS_STELLA_RETURN, wrapInteger(1), NIL), NIL), 0), 0)));
          }
          else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_MACROS_JAVA) {
            return (listO(3, SYM_MACROS_STELLA_DEFUN, mainname, listO(4, cons(cons(localGensym("ARGV"), cons(listO(5, SYM_MACROS_STELLA_ARRAY, NIL, SYM_MACROS_STELLA_OF, SYM_MACROS_STELLA_STRING, NIL), NIL)), NIL), KWD_MACROS_PUBLICp, SYM_MACROS_STELLA_TRUE, startupfunctioncall->concatenate(body->concatenate(NIL, 0), 0))));
          }
          else {
          }
        }
        else {
          if (oTRANSLATOROUTPUTLANGUAGEo == KWD_MACROS_COMMON_LISP) {
            return (listO(3, SYM_MACROS_STELLA_DEFUN, mainname, listO(5, listO(3, SYM_MACROS_STELLA_aREST, listO(3, SYM_MACROS_STELLA_rrARGS, SYM_MACROS_STELLA_STRING, NIL), NIL), KWD_MACROS_PUBLICp, SYM_MACROS_STELLA_TRUE, listO(3, SYM_MACROS_STELLA_LET, listO(3, cons(v1Name, listO(3, SYM_MACROS_STELLA_INTEGER, listO(4, SYM_MACROS_STELLA_VERBATIM, KWD_MACROS_COMMON_LISP, listO(3, internCommonLispSymbol("LENGTH"), SYM_MACROS_STELLA_rrARGS, NIL), NIL), NIL)), cons(v2Name, listO(3, listO(5, SYM_MACROS_STELLA_ARRAY, NIL, SYM_MACROS_STELLA_OF, SYM_MACROS_STELLA_STRING, NIL), listO(4, SYM_MACROS_STELLA_VERBATIM, KWD_MACROS_COMMON_LISP, listO(5, internCommonLispSymbol("MAKE-ARRAY"), listO(3, internCommonLispSymbol("LENGTH"), SYM_MACROS_STELLA_rrARGS, NIL), KWD_MACROS_INITIAL_CONTENTS, SYM_MACROS_STELLA_rrARGS, NIL), NIL), NIL)), NIL), startupfunctioncall->concatenate(body->concatenate(NIL, 0), 0)), NIL)));
          }
          else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_MACROS_JAVA) {
            return (listO(3, SYM_MACROS_STELLA_DEFUN, mainname, listO(5, cons(cons(v2Name, cons(listO(5, SYM_MACROS_STELLA_ARRAY, NIL, SYM_MACROS_STELLA_OF, SYM_MACROS_STELLA_STRING, NIL), NIL)), NIL), KWD_MACROS_PUBLICp, SYM_MACROS_STELLA_TRUE, listO(3, SYM_MACROS_STELLA_LET, cons(cons(v1Name, listO(3, SYM_MACROS_STELLA_INTEGER, listO(4, SYM_MACROS_STELLA_VERBATIM, KWD_MACROS_JAVA, wrapString(stringConcatenate(javaTranslateName(v2Name)->wrapperValue, ".length", 0)), NIL), NIL)), NIL), startupfunctioncall->concatenate(body->concatenate(NIL, 0), 0)), NIL)));
          }
          else if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_MACROS_CPP) ||
              ((oTRANSLATOROUTPUTLANGUAGEo == KWD_MACROS_CPP_STANDALONE) ||
               (oTRANSLATOROUTPUTLANGUAGEo == KWD_MACROS_IDL))) {
            return (listO(6, SYM_MACROS_STELLA_DEFUN, cons(mainname, cons(SYM_MACROS_STELLA_INTEGER, NIL)), listO(3, cons(v1Name, cons(SYM_MACROS_STELLA_INTEGER, NIL)), cons(v2Name, cons(listO(5, SYM_MACROS_STELLA_ARRAY, NIL, SYM_MACROS_STELLA_OF, SYM_MACROS_STELLA_STRING, NIL), NIL)), NIL), KWD_MACROS_PUBLICp, SYM_MACROS_STELLA_TRUE, startupfunctioncall->concatenate(body->concatenate(cons(listO(3, SYM_MACROS_STELLA_RETURN, wrapInteger(1), NIL), NIL), 0), 0)));
          }
          else {
          }
        }
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "`defmain' is not supported for " << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << "." << std::endl;
          }
        }
        return (NULL);
      }
    }
  }
}

void helpStartupMacros1() {
  {
    SYM_MACROS_STELLA_SETQ = ((Symbol*)(internRigidSymbolWrtModule("SETQ", NULL, 0)));
    SYM_MACROS_STELLA_CONS = ((Symbol*)(internRigidSymbolWrtModule("CONS", NULL, 0)));
    SYM_MACROS_STELLA_VRLET = ((Symbol*)(internRigidSymbolWrtModule("VRLET", NULL, 0)));
    SYM_MACROS_STELLA_VALUE = ((Symbol*)(internRigidSymbolWrtModule("VALUE", NULL, 0)));
    SYM_MACROS_STELLA_REST = ((Symbol*)(internRigidSymbolWrtModule("REST", NULL, 0)));
    SYM_MACROS_STELLA_SETF = ((Symbol*)(internRigidSymbolWrtModule("SETF", NULL, 0)));
    SYM_MACROS_STELLA_CHOOSE = ((Symbol*)(internRigidSymbolWrtModule("CHOOSE", NULL, 0)));
    SYM_MACROS_STELLA_MEMBERp = ((Symbol*)(internRigidSymbolWrtModule("MEMBER?", NULL, 0)));
    SYM_MACROS_STELLA_i = ((Symbol*)(internRigidSymbolWrtModule("+", NULL, 0)));
    SYM_MACROS_STELLA___ = ((Symbol*)(internRigidSymbolWrtModule("--", NULL, 0)));
    KWD_MACROS_JAVA = ((Keyword*)(internRigidSymbolWrtModule("JAVA", NULL, 2)));
    KWD_MACROS_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SYM_MACROS_STELLA__ = ((Symbol*)(internRigidSymbolWrtModule("-", NULL, 0)));
    SYM_MACROS_STELLA_DEFINEDp = ((Symbol*)(internRigidSymbolWrtModule("DEFINED?", NULL, 0)));
    SYM_MACROS_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
    SYM_MACROS_STELLA_FIRST_DEFINED = ((Symbol*)(internRigidSymbolWrtModule("FIRST-DEFINED", NULL, 0)));
    SYM_MACROS_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    SYM_MACROS_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", NULL, 0)));
    SYM_MACROS_STELLA_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("FOREACH", NULL, 0)));
    SYM_MACROS_STELLA_NIL = ((Symbol*)(internRigidSymbolWrtModule("NIL", NULL, 0)));
    SYM_MACROS_STELLA_COLLECT = ((Symbol*)(internRigidSymbolWrtModule("COLLECT", NULL, 0)));
    SYM_MACROS_STELLA_INTO = ((Symbol*)(internRigidSymbolWrtModule("INTO", NULL, 0)));
    SYM_MACROS_STELLA_SPECIAL = ((Symbol*)(internRigidSymbolWrtModule("SPECIAL", NULL, 0)));
    SYM_MACROS_STELLA_oTRANSIENTOBJECTSpo = ((Symbol*)(internRigidSymbolWrtModule("*TRANSIENTOBJECTS?*", NULL, 0)));
    SYM_MACROS_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", NULL, 0)));
    KWD_MACROS_READ_ONLYp = ((Keyword*)(internRigidSymbolWrtModule("READ-ONLY?", NULL, 2)));
    SYM_MACROS_STELLA_oCONTEXTo = ((Symbol*)(internRigidSymbolWrtModule("*CONTEXT*", NULL, 0)));
    SYM_MACROS_STELLA_SAFETY = ((Symbol*)(internRigidSymbolWrtModule("SAFETY", NULL, 0)));
    SYM_MACROS_STELLA_EQLp = ((Symbol*)(internRigidSymbolWrtModule("EQL?", NULL, 0)));
    SYM_MACROS_STELLA_BASE_MODULE = ((Symbol*)(internRigidSymbolWrtModule("BASE-MODULE", NULL, 0)));
    SYM_MACROS_STELLA_CAST = ((Symbol*)(internRigidSymbolWrtModule("CAST", NULL, 0)));
    SYM_MACROS_STELLA_WORLD = ((Symbol*)(internRigidSymbolWrtModule("WORLD", NULL, 0)));
    SYM_MACROS_STELLA_oMODULEo = ((Symbol*)(internRigidSymbolWrtModule("*MODULE*", NULL, 0)));
    SYM_MACROS_STELLA_IN = ((Symbol*)(internRigidSymbolWrtModule("IN", NULL, 0)));
    SYM_MACROS_STELLA_oCURRENTSYSTEMDEFINITIONo = ((Symbol*)(internRigidSymbolWrtModule("*CURRENTSYSTEMDEFINITION*", NULL, 0)));
    SYM_MACROS_STELLA_GET_SYSTEM_DEFINITION = ((Symbol*)(internRigidSymbolWrtModule("GET-SYSTEM-DEFINITION", NULL, 0)));
    SYM_MACROS_STELLA_oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo = ((Symbol*)(internRigidSymbolWrtModule("*CURRENTSYSTEMDEFINITIONSUBDIRECTORY*", NULL, 0)));
    SYM_MACROS_STELLA_DIRECTORY = ((Symbol*)(internRigidSymbolWrtModule("DIRECTORY", NULL, 0)));
    SYM_MACROS_STELLA_PROGN = ((Symbol*)(internRigidSymbolWrtModule("PROGN", NULL, 0)));
    KWD_MACROS_STARTUP_SYSTEMp = ((Keyword*)(internRigidSymbolWrtModule("STARTUP-SYSTEM?", NULL, 2)));
    SYM_MACROS_STELLA_IF_STELLA_FEATURE = ((Symbol*)(internRigidSymbolWrtModule("IF-STELLA-FEATURE", NULL, 0)));
    KWD_MACROS_SUPPORT_UNEXEC = ((Keyword*)(internRigidSymbolWrtModule("SUPPORT-UNEXEC", NULL, 2)));
    SYM_MACROS_STELLA_VERBATIM = ((Symbol*)(internRigidSymbolWrtModule("VERBATIM", NULL, 0)));
    KWD_MACROS_CPP = ((Keyword*)(internRigidSymbolWrtModule("CPP", NULL, 2)));
    KWD_MACROS_OTHERWISE = ((Keyword*)(internRigidSymbolWrtModule("OTHERWISE", NULL, 2)));
    KWD_MACROS_PUBLICp = ((Keyword*)(internRigidSymbolWrtModule("PUBLIC?", NULL, 2)));
    KWD_MACROS_COMMON_LISP = ((Keyword*)(internRigidSymbolWrtModule("COMMON-LISP", NULL, 2)));
    SYM_MACROS_STELLA_DEFUN = ((Symbol*)(internRigidSymbolWrtModule("DEFUN", NULL, 0)));
    KWD_MACROS_CPP_STANDALONE = ((Keyword*)(internRigidSymbolWrtModule("CPP-STANDALONE", NULL, 2)));
    KWD_MACROS_IDL = ((Keyword*)(internRigidSymbolWrtModule("IDL", NULL, 2)));
    SYM_MACROS_STELLA_INTEGER = ((Symbol*)(internRigidSymbolWrtModule("INTEGER", NULL, 0)));
    SYM_MACROS_STELLA_RETURN = ((Symbol*)(internRigidSymbolWrtModule("RETURN", NULL, 0)));
    SYM_MACROS_STELLA_ARRAY = ((Symbol*)(internRigidSymbolWrtModule("ARRAY", NULL, 0)));
    SYM_MACROS_STELLA_OF = ((Symbol*)(internRigidSymbolWrtModule("OF", NULL, 0)));
    SYM_MACROS_STELLA_STRING = ((Symbol*)(internRigidSymbolWrtModule("STRING", NULL, 0)));
    SYM_MACROS_STELLA_aREST = ((Symbol*)(internRigidSymbolWrtModule("&REST", NULL, 0)));
    SYM_MACROS_STELLA_rrARGS = ((Symbol*)(internRigidSymbolWrtModule("%%ARGS", NULL, 0)));
    SYM_MACROS_STELLA_LET = ((Symbol*)(internRigidSymbolWrtModule("LET", NULL, 0)));
    KWD_MACROS_INITIAL_CONTENTS = ((Keyword*)(internRigidSymbolWrtModule("INITIAL-CONTENTS", NULL, 2)));
    SYM_MACROS_STELLA_STARTUP_MACROS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-MACROS", NULL, 0)));
  }
}

void startupMacros() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupMacros1();
      SYM_MACROS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("PUSHQ", "(DEFUN PUSHQ ((VARIABLE SYMBOL) (VALUE OBJECT)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Push 'value' onto the cons list 'variable'.\")", ((cpp_function_code)(&pushq)), NULL);
      defineFunctionObject("POPQ", "(DEFUN POPQ ((VARIABLE SYMBOL)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Pops a value from the cons list 'variable'.\")", ((cpp_function_code)(&popq)), NULL);
      defineFunctionObject("PUSHF", "(DEFUN PUSHF ((PLACE CONS) (VALUE OBJECT)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Push 'value' onto the cons list 'place'.\")", ((cpp_function_code)(&pushf)), NULL);
      defineFunctionObject("PUSHQ-NEW", "(DEFUN PUSHQ-NEW ((VARIABLE SYMBOL) (VALUE OBJECT)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Push `value' onto the cons list `variable', unless `value'\nis already a member of the list.\" :PUBLIC? TRUE)", ((cpp_function_code)(&pushqNew)), NULL);
      defineFunctionObject("++", "(DEFUN ++ ((PLACE OBJECT) |&BODY| (INCREMENT CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Increment the value of `place' and return the result.\n`place' can be either a variable name or a slot reference.  Increment by\nthe optional `increment' (which can be a float) or 1 otherwise.\")", ((cpp_function_code)(&stella_Increment)), NULL);
      defineFunctionObject("--", "(DEFUN -- ((PLACE OBJECT) |&BODY| (DECREMENT CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Decrement the value of `place' and return the result.\n`place' can be either a variable name or a slot reference.  Decrement by\nthe optional `decrement' (which can be a float) or 1 otherwise.\")", ((cpp_function_code)(&stella_Decrement)), NULL);
      defineFunctionObject("1+", "(DEFUN 1+ ((EXPRESSION OBJECT)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Add 1 to 'expression' and return the result.\")", ((cpp_function_code)(&oneI)), NULL);
      defineFunctionObject("1-", "(DEFUN 1- ((EXPRESSION OBJECT)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Subtract 1 from 'expression' and return the result.\")", ((cpp_function_code)(&one)), NULL);
      defineFunctionObject("SETQ?", "(DEFUN SETQ? ((VARIABLE SYMBOL) (EXPRESSION CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Assign 'variable' the result of evaluating 'expression', \nand return TRUE if 'expression' is not NULL else return FALSE.\")", ((cpp_function_code)(&setqP)), NULL);
      defineFunctionObject("FIRST-DEFINED", "(DEFUN FIRST-DEFINED (|&BODY| (FORMS CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Return the result of the first form in `forms' whose value is defined\nor NULL otherwise.\")", ((cpp_function_code)(&firstDefined)), NULL);
      defineFunctionObject("ALL-DEFINED?", "(DEFUN ALL-DEFINED? (|&BODY| (FORMS CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Evaluate each of the forms in 'forms', and\nreturn TRUE if none of them are NULL.\")", ((cpp_function_code)(&allDefinedP)), NULL);
      defineFunctionObject("EITHER", "(DEFUN EITHER ((VALUE1 OBJECT) (VALUE2 OBJECT)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"If 'value1' is defined, return that, else return 'value2'.\")", ((cpp_function_code)(&either)), NULL);
      defineFunctionObject("COLLECT", "(DEFUN COLLECT (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Use a VRLET to collect values.  Input can have one of\nthe following forms:\n	 \n  (collect <var> in <expression> [where <test> <var>])\n  (collect <collect-expression>\n           foreach <var> in <expression>\n           {as ...}*\n           [where <test> <var>]\n           [do ...])\n	\nThe second form really accepts an arbitrary `foreach' expression following\nthe `foreach' keyword.\")", ((cpp_function_code)(&collect)), NULL);
      defineFunctionObject("WITH-PERMANENT-OBJECTS", "(DEFUN WITH-PERMANENT-OBJECTS (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Allocate 'permanent' (as opposed to 'transient')\nobjects within the scope of this declaration.\" :PUBLIC? TRUE)", ((cpp_function_code)(&withPermanentObjects)), NULL);
      defineFunctionObject("WITH-TRANSIENT-OBJECTS", "(DEFUN WITH-TRANSIENT-OBJECTS (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Allocate 'transient' (as opposed to 'permanent')\nobjects within the scope of this declaration.\nCAUTION: The default assumption is the allocation of permanent objects.\nThe scope of `with-transient-objects' should be as small as possible, and\nthe user has to make sure that code that wasn't explicitly written to\naccount for transient objects will continue to work correctly.\" :PUBLIC? TRUE)", ((cpp_function_code)(&withTransientObjects)), NULL);
      defineFunctionObject("IGNORE", "(DEFUN IGNORE (|&BODY| (VARIABLES CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Ignore unused 'variables' with NoOp 'setq' statements.\")", ((cpp_function_code)(&ignore)), NULL);
      defineFunctionObject("ONLY-IF", "(DEFUN ONLY-IF ((TEST OBJECT) (EXPRESSION OBJECT)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"If 'test' is TRUE, return the result of evaluating \n'expression'.\")", ((cpp_function_code)(&onlyIf)), NULL);
      defineFunctionObject("PHASE-TO-INTEGER", "(DEFUN PHASE-TO-INTEGER ((STARTUPTIMEPHASE KEYWORD)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Expands into the integer representing 'startupTimePhase'.\")", ((cpp_function_code)(&phaseToInteger)), NULL);
      defineFunctionObject("IF-OUTPUT-LANGUAGE", "(DEFUN IF-OUTPUT-LANGUAGE ((LANGUAGE KEYWORD) (THENFORM OBJECT) (ELSEFORM OBJECT)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Expand to 'thenForm' if the current translator output\nlanguage equals 'language'.  Otherwise, expand to 'elseForm'.  This can\nbe used to conditionally translate Stella code.\")", ((cpp_function_code)(&ifOutputLanguage)), NULL);
      defineFunctionObject("IF-STELLA-FEATURE", "(DEFUN IF-STELLA-FEATURE ((FEATURE KEYWORD) (THENFORM OBJECT) (ELSEFORM OBJECT)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Expand to 'thenForm' if 'feature' is a currently enabled\nSTELLA environment feature.  Otherwise, expand to 'elseForm'.  This can\nbe used to conditionally translate Stella code.\")", ((cpp_function_code)(&ifStellaFeature)), NULL);
      defineFunctionObject("WITHIN-WORLD", "(DEFUN WITHIN-WORLD ((WORLDFORM OBJECT) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Execute `body' within the world resulting from `worldForm'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&withinWorld)), NULL);
      defineFunctionObject("WITHIN-CONTEXT", "(DEFUN WITHIN-CONTEXT ((CONTEXTFORM OBJECT) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Execute `body' within the context resulting from `contextForm'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&withinContext)), NULL);
      defineFunctionObject("WITHIN-MODULE", "(DEFUN WITHIN-MODULE ((MODULEFORM OBJECT) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Execute `body' within the module resulting from `moduleForm'.\n`*module*' is an acceptable `moduleForm'.  It will locally rebind \n`*module*' and `*context*' and shield the outer bindings from changes.\" :PUBLIC? TRUE)", ((cpp_function_code)(&withinModule)), NULL);
      defineFunctionObject(" |COERCE-&REST-TO-CONS|", "(DEFUN |COERCE-&REST-TO-CONS| ((RESTVARIABLE SYMBOL)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Coerce the argument list variable `restVariable' into a CONS\nlist containing all its elements (uses argument list iteration to do so).  If\n`restVariable' already is a CONS due to argument listification, this is a no-op.\" :PUBLIC? TRUE)", ((cpp_function_code)(&coerceARestToCons)), NULL);
      defineFunctionObject("WITH-SYSTEM-DEFINITION", "(DEFUN WITH-SYSTEM-DEFINITION ((SYSTEMNAMEEXPRESSION OBJECT) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Set *currentSystemDefinition* to the system definition named `system'.\nSet *currentSystemDefinitionSubdirectory* to match. Execute `body' within\nthat scope.\" :PUBLIC? TRUE)", ((cpp_function_code)(&withSystemDefinition)), NULL);
      defineFunctionObject("DEFMAIN", "(DEFUN DEFMAIN ((VARLIST CONS) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Defines a function called MAIN which will have the appropriate\nsignature for the target translation language.  The signature will be:\n  C++:   public static int main (int v1, char** v2) {<body>}\n  Java:  public static void main (String [] v2) {<body>}\n  Lisp:  (defun main (&rest args) <body>)\nThe argument `varList' must have two symbols, which will be the names for the\nINTEGER argument count and an array of STRINGs with the argument values.  It\ncan also be empty to indicate that no command line arguments will be handled.\nThe startup function for the containing system will automatically be called\nbefore `body' is executed unless the option :STARTUP-SYSTEM? was supplied as\nFALSE.  There can only be one DEFMAIN per module.\" :PUBLIC? TRUE :LISP-MACRO? TRUE)", ((cpp_function_code)(&defmain)), NULL);
      defineFunctionObject("STARTUP-MACROS", "(DEFUN STARTUP-MACROS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupMacros)), NULL);
      { MethodSlot* function = lookupFunction(SYM_MACROS_STELLA_STARTUP_MACROS);

        setDynamicSlotValue(function->dynamicSlots, SYM_MACROS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupMacros"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      registerNativeName(SYM_MACROS_STELLA___, KWD_MACROS_JAVA, KWD_MACROS_FUNCTION);
    }
  }
}

Symbol* SYM_MACROS_STELLA_SETQ = NULL;

Symbol* SYM_MACROS_STELLA_CONS = NULL;

Symbol* SYM_MACROS_STELLA_VRLET = NULL;

Symbol* SYM_MACROS_STELLA_VALUE = NULL;

Symbol* SYM_MACROS_STELLA_REST = NULL;

Symbol* SYM_MACROS_STELLA_SETF = NULL;

Symbol* SYM_MACROS_STELLA_CHOOSE = NULL;

Symbol* SYM_MACROS_STELLA_MEMBERp = NULL;

Symbol* SYM_MACROS_STELLA_i = NULL;

Symbol* SYM_MACROS_STELLA___ = NULL;

Keyword* KWD_MACROS_JAVA = NULL;

Keyword* KWD_MACROS_FUNCTION = NULL;

Symbol* SYM_MACROS_STELLA__ = NULL;

Symbol* SYM_MACROS_STELLA_DEFINEDp = NULL;

Symbol* SYM_MACROS_STELLA_NULL = NULL;

Symbol* SYM_MACROS_STELLA_FIRST_DEFINED = NULL;

Symbol* SYM_MACROS_STELLA_TRUE = NULL;

Symbol* SYM_MACROS_STELLA_AND = NULL;

Symbol* SYM_MACROS_STELLA_FOREACH = NULL;

Symbol* SYM_MACROS_STELLA_NIL = NULL;

Symbol* SYM_MACROS_STELLA_COLLECT = NULL;

Symbol* SYM_MACROS_STELLA_INTO = NULL;

Symbol* SYM_MACROS_STELLA_SPECIAL = NULL;

Symbol* SYM_MACROS_STELLA_oTRANSIENTOBJECTSpo = NULL;

Symbol* SYM_MACROS_STELLA_FALSE = NULL;

Keyword* KWD_MACROS_READ_ONLYp = NULL;

Symbol* SYM_MACROS_STELLA_oCONTEXTo = NULL;

Symbol* SYM_MACROS_STELLA_SAFETY = NULL;

Symbol* SYM_MACROS_STELLA_EQLp = NULL;

Symbol* SYM_MACROS_STELLA_BASE_MODULE = NULL;

Symbol* SYM_MACROS_STELLA_CAST = NULL;

Symbol* SYM_MACROS_STELLA_WORLD = NULL;

Symbol* SYM_MACROS_STELLA_oMODULEo = NULL;

Symbol* SYM_MACROS_STELLA_IN = NULL;

Symbol* SYM_MACROS_STELLA_oCURRENTSYSTEMDEFINITIONo = NULL;

Symbol* SYM_MACROS_STELLA_GET_SYSTEM_DEFINITION = NULL;

Symbol* SYM_MACROS_STELLA_oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo = NULL;

Symbol* SYM_MACROS_STELLA_DIRECTORY = NULL;

Symbol* SYM_MACROS_STELLA_PROGN = NULL;

Keyword* KWD_MACROS_STARTUP_SYSTEMp = NULL;

Symbol* SYM_MACROS_STELLA_IF_STELLA_FEATURE = NULL;

Keyword* KWD_MACROS_SUPPORT_UNEXEC = NULL;

Symbol* SYM_MACROS_STELLA_VERBATIM = NULL;

Keyword* KWD_MACROS_CPP = NULL;

Keyword* KWD_MACROS_OTHERWISE = NULL;

Keyword* KWD_MACROS_PUBLICp = NULL;

Keyword* KWD_MACROS_COMMON_LISP = NULL;

Symbol* SYM_MACROS_STELLA_DEFUN = NULL;

Keyword* KWD_MACROS_CPP_STANDALONE = NULL;

Keyword* KWD_MACROS_IDL = NULL;

Symbol* SYM_MACROS_STELLA_INTEGER = NULL;

Symbol* SYM_MACROS_STELLA_RETURN = NULL;

Symbol* SYM_MACROS_STELLA_ARRAY = NULL;

Symbol* SYM_MACROS_STELLA_OF = NULL;

Symbol* SYM_MACROS_STELLA_STRING = NULL;

Symbol* SYM_MACROS_STELLA_aREST = NULL;

Symbol* SYM_MACROS_STELLA_rrARGS = NULL;

Symbol* SYM_MACROS_STELLA_LET = NULL;

Keyword* KWD_MACROS_INITIAL_CONTENTS = NULL;

Symbol* SYM_MACROS_STELLA_STARTUP_MACROS = NULL;

Symbol* SYM_MACROS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
