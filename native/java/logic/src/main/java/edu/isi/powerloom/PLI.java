//  -*- Mode: Java -*-
//
// PLI.java

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

package edu.isi.powerloom;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.powerloom.logic.*;
import edu.isi.stella.*;

public class PLI {
  public static boolean $POWERLOOM_INITIALIZEDp$ = false;

  public static Surrogate SGT_PLI_ENVIRONMENT = null;

  public static Symbol SYM_LOGIC_LEVEL = null;

  public static Environment ASSERTION_ENV = null;

  public static Environment TAXONOMIC_ENV = null;

  public static Environment INFERENCE_ENV = null;

  public static Surrogate SGT_PLI_PL_ITERATOR = null;

  /** Iterator that generates no values.
   */
  static PlIterator EMPTY_PL_ITERATOR = null;

  static NamedDescription $LITERAL_CONCEPT$ = null;

  static NamedDescription $STRING_CONCEPT$ = null;

  static NamedDescription $INTEGER_CONCEPT$ = null;

  static NamedDescription $FLOAT_CONCEPT$ = null;

  public static Symbol SYM_PLI_pR = null;

  public static Symbol SYM_PLI_pI = null;

  public static Symbol SYM_PLI_pV = null;

  public static Symbol SYM_PLI_F_GET_INFERRED_BINARY_PROPOSITION_VALUES_QUERY_000 = null;

  public static Symbol SYM_PLI_PROPER_SUBRELATION = null;

  public static Keyword KWD_CASE_SENSITIVEp = null;

  public static Keyword KWD_SUBSET_OF = null;

  public static Surrogate SGT_PL_KERNEL_KB_NTH_DOMAIN = null;

  public static Surrogate SGT_PLI_OBJECT_REGISTRY_LIST = null;

  public static Symbol SYM_PLI_REGISTRY_LENGTH = null;

  public static Symbol SYM_PLI_N_FREE_CELLS = null;

  public static ObjectRegistryList $OBJECT_REGISTRY$ = null;

  public static Symbol SYM_PLI_STARTUP_PLI = null;

  /** Initialize the PowerLoom logic system.  This function
   * needs to be called by all applications before using PowerLoom.  If it
   * is called more than once, every call after the first one is a no-op.
   */
  public static void initialize() {
    synchronized (Stella.$BOOTSTRAP_LOCK$) {
      if (!PLI.$POWERLOOM_INITIALIZEDp$) {
        StartupLogicSystem.startupLogicSystem();
      }
    }
  }

  /** Reset PowerLoom to its initial state.
   * CAUTION: This will destroy all loaded knowledge bases and might break other
   * loaded STELLA systems if they do reference PowerLoom symbols in their code.
   */
  public static void resetPowerloom() {
    synchronized (Logic.$POWERLOOM_LOCK$) {
      Logic.resetPowerloom();
    }
  }

  /** Clear all query and memoization caches.
   */
  public static void clearCaches() {
    synchronized (Logic.$POWERLOOM_LOCK$) {
      Logic.clearCaches();
    }
  }

  /** Convert a STELLA cons list into an API iterator.
   * @param self
   * @return PlIterator
   */
  public static PlIterator consToPlIterator(Cons self) {
    if (self == Stella.NIL) {
      return (PLI.EMPTY_PL_ITERATOR);
    }
    else {
      { PlIterator self001 = PlIterator.newPlIterator();

        self001.cursor = self;
        { PlIterator value000 = self001;

          return (value000);
        }
      }
    }
  }

  /** Convert a STELLA list into an API iterator.
   * @param self
   * @return PlIterator
   */
  public static PlIterator listToPlIterator(List self) {
    if (self.emptyP()) {
      return (PLI.EMPTY_PL_ITERATOR);
    }
    else {
      return (PLI.consToPlIterator(self.theConsList));
    }
  }

  /** Convert an arbitrary STELLA iterator into an API iterator.
   * This will first exhaust <code>self</code> and then create an API iterator that will
   * iterate over the previously generated values.
   * @param self
   * @return PlIterator
   */
  public static PlIterator iteratorToPlIterator(Iterator self) {
    return (PLI.consToPlIterator(self.consify()));
  }

  /** Create a STELLA CONS-cell whose value points to <code>first</code> and tail points to <code>rest</code>.
   * If <code>rest</code> is NULL, it will point to the empty list (available as a constructor in C).
   * @param first
   * @param rest
   * @return Cons
   */
  public static Cons createCons(Stella_Object first, Cons rest) {
    if (rest == null) {
      rest = Stella.NIL;
    }
    return (Cons.cons(first, rest));
  }

  /** Create a STELLA CONS-list of <code>length</code> with elements initialized to NULL (available as a constructor in C).
   * @param length
   * @return Cons
   */
  public static Cons createConsList(int length) {
    { Cons list = Stella.NIL;

      while (length > 0) {
        list = Cons.cons(null, list);
        length = length - 1;
      }
      return (list);
    }
  }

  /** Return the length of the CONS-list <code>self</code> (available to support access in C).
   * @param self
   * @return int
   */
  public static int consLength(Cons self) {
    return (self.length());
  }

  /** Return TRUE if the CONS-list <code>self</code> is empty (available to support access in C).
   * @param self
   * @return boolean
   */
  public static boolean consIsEmpty(Cons self) {
    return (self == Stella.NIL);
  }

  /** Access the first element of the CONS-list <code>self</code> (available to support access in C).
   * @param self
   * @return Stella_Object
   */
  public static Stella_Object consFirst(Cons self) {
    return (self.value);
  }

  /** Access the rest (tail) of the CONS-list <code>self</code> (available to support access in C).
   * @param self
   * @return Cons
   */
  public static Cons consRest(Cons self) {
    return (self.rest);
  }

  /** Access the <code>n</code>-th element of the CONS-list <code>self</code> (available to support access in C).
   * @param self
   * @param n
   * @return Stella_Object
   */
  public static Stella_Object consNth(Cons self, int n) {
    return (self.nth(n));
  }

  /** Access the <code>n</code>-th rest (tail) of the CONS-list <code>self</code> (available to support access in C).
   * @param self
   * @param n
   * @return Cons
   */
  public static Cons consNthRest(Cons self, int n) {
    return (self.nthRest(n));
  }

  /** Set the first element of the CONS-list <code>self</code> to <code>value</code> (available to support access in C).
   * @param self
   * @param value
   */
  public static void consSetFirst(Cons self, Stella_Object value) {
    self.value = value;
  }

  /** Set the rest (tail) of the CONS-list <code>self</code> to <code>rest</code> (available to support access in C).
   * If <code>rest</code> is NULL, it will point to the empty list.
   * @param self
   * @param rest
   */
  public static void consSetRest(Cons self, Cons rest) {
    if (rest == null) {
      rest = Stella.NIL;
    }
    self.rest = rest;
  }

  /** Set the <code>n</code>-th element of the CONS-list <code>self</code> to <code>value</code> (available to support access in C).
   * The run-time complexity of this operation is O(n).
   * @param self
   * @param n
   * @param value
   */
  public static void consSetNth(Cons self, int n, Stella_Object value) {
    self.nthSetter(value, n);
  }

  /** Set the <code>n</code>-th rest (tail) of the CONS-list <code>self</code> to <code>rest</code> (available to support access in C).
   * If <code>rest</code> is NULL, it will point to the empty list.  The run-time complexity of this operation is O(n).
   * @param self
   * @param n
   * @param rest
   */
  public static void consSetNthRest(Cons self, int n, Cons rest) {
    if (rest == null) {
      rest = Stella.NIL;
    }
    self.nthRestSetter(rest, n);
  }

  /** Access the first element of the list <code>self</code> (available to support access in C).
   * @param self
   * @return Stella_Object
   */
  public static Stella_Object listFirst(List self) {
    return (self.first());
  }

  /** Access the rest (tail) of the list <code>self</code> (available to support access in C).
   * NOTE: the rest of a STELLA list is a CONS-list not a LIST.
   * @param self
   * @return Cons
   */
  public static Cons listRest(List self) {
    return (self.rest());
  }

  /** Access the <code>n</code>-th element of the list <code>self</code> (available to support access in C).
   * @param self
   * @param n
   * @return Stella_Object
   */
  public static Stella_Object listNth(List self, int n) {
    return (self.nth(n));
  }

  /** Create a PowerLoom copy of the string <code>content</code> which uses PowerLoom memory
   * management and garbage collection.  This is primarily necessary in C environments when a string
   * is passed to a PowerLoom PLI function which might then be pointed to by a PowerLoom result
   * object such as a string wrapper.  If such an argument string is later explicitly freed or
   * overwritten, the result object would have a dangling reference or its content destroyed.
   * @param content
   * @return String
   */
  public static String createString(String content) {
    return (Native.string_copy(content));
  }

  /** Create a STELLA string wrapper for <code>self</code>.  This automatically copies <code>self</code>
   * before the wrapper is allocated to avoid garbage collection issues in case <code>self</code> is freed.
   * @param self
   * @return StringWrapper
   */
  public static StringWrapper createStringWrapper(String self) {
    return (StringWrapper.wrapString(Native.string_copy(self)));
  }

  /** Create a STELLA string wrapper for <code>self</code>.  This wraps <code>self</code> directly
   * and does not allocate a PowerLoom copy first, hence, memory management of <code>self</code> needs to
   * be carefully handled by the caller.
   * @param self
   * @return StringWrapper
   */
  public static StringWrapper createDirectStringWrapper(String self) {
    return (StringWrapper.wrapString(self));
  }

  /** Create a STELLA integer wrapper for <code>self</code>.
   * @param self
   * @return IntegerWrapper
   */
  public static IntegerWrapper createIntegerWrapper(int self) {
    return (IntegerWrapper.wrapInteger(self));
  }

  /** Create a STELLA long-integer wrapper for <code>self</code>.
   * @param self
   * @return LongIntegerWrapper
   */
  public static LongIntegerWrapper createLongIntegerWrapper(long self) {
    return (Stella.wrapLongInteger(self));
  }

  /** Create a STELLA float wrapper for <code>self</code>.
   * @param self
   * @return FloatWrapper
   */
  public static FloatWrapper createFloatWrapper(double self) {
    return (FloatWrapper.wrapFloat(self));
  }

  /** Create a STELLA boolean wrapper for <code>self</code>.
   * @param self
   * @return BooleanWrapper
   */
  public static BooleanWrapper createBooleanWrapper(boolean self) {
    return ((self ? Stella.TRUE_WRAPPER : Stella.FALSE_WRAPPER));
  }

  static Stella_Object safelyGetObject(String name, Module module, Environment environment) {
    if (name == null) {
      return (null);
    }
    { Stella_Object renamed_Object = PLI.getObject(name, module, environment);

      if (renamed_Object == null) {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("Can't find an object named `" + name + "'");
          throw ((NoSuchObjectException)(NoSuchObjectException.newNoSuchObjectException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
      else {
        return (renamed_Object);
      }
    }
  }

  static Stella_Object safelyGetConcept(String name, Module module, Environment environment) {
    if (name == null) {
      return (null);
    }
    { LogicObject renamed_Object = PLI.getConcept(name, module, environment);

      if (renamed_Object == null) {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("Can't find a concept named `" + name + "'");
          throw ((NoSuchObjectException)(NoSuchObjectException.newNoSuchObjectException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
      else {
        return (renamed_Object);
      }
    }
  }

  static Stella_Object safelyGetRelation(String name, Module module, Environment environment) {
    if (name == null) {
      return (null);
    }
    { LogicObject renamed_Object = PLI.getRelation(name, module, environment);

      if (renamed_Object == null) {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("Can't find a relation named `" + name + "'");
          throw ((NoSuchObjectException)(NoSuchObjectException.newNoSuchObjectException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
      else {
        return (renamed_Object);
      }
    }
  }

  static Context safelyGetModule(String name, Environment environment) {
    environment = environment;
    if ((name == null) ||
        Stella.stringEqlP(name, "")) {
      return (((Module)(Stella.$MODULE$.get())));
    }
    return (Stella.getStellaModule(name, true));
  }

  static Stella_Object safelyGetObjectOrNull(String name, Module module, Environment environment) {
    if ((module == null) ||
        ((name == null) ||
         (Stella.stringEqlP(name, "") ||
          Stella.stringEqualP(name, "null")))) {
      return (null);
    }
    try {
      return (PLI.getObject(name, module, environment));
    } catch (NoSuchObjectException e000) {
      return (null);
    }
  }

  static Cons sequenceToConsList(Stella_Object sequence) {
    { Surrogate testValue000 = Stella_Object.safePrimaryType(sequence);

      if (testValue000 == Logic.SGT_STELLA_CONS) {
        { Cons sequence000 = ((Cons)(sequence));

          return (sequence000);
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_STELLA_LIST)) {
        { List sequence000 = ((List)(sequence));

          return (sequence000.theConsList);
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_STELLA_VECTOR)) {
        { Vector sequence000 = ((Vector)(sequence));

          { Cons result = Stella.NIL;

            { int i = Stella.NULL_INTEGER;
              int iter000 = 0;
              int upperBound000 = sequence000.length();
              Cons collect000 = null;

              for (;iter000 <= upperBound000; iter000 = iter000 + 1) {
                i = iter000;
                if (collect000 == null) {
                  {
                    collect000 = Cons.cons((sequence000.theArray)[i], Stella.NIL);
                    if (result == Stella.NIL) {
                      result = collect000;
                    }
                    else {
                      Cons.addConsToEndOfConsList(result, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000.rest = Cons.cons((sequence000.theArray)[i], Stella.NIL);
                    collect000 = collect000.rest;
                  }
                }
              }
            }
            return (result);
          }
        }
      }
      else {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("Don't know how to convert object of type `" + sequence.primaryType() + "' into a cons list.");
          throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
    }
  }

  static Cons explodeStringList(String stringlist, Module module) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, module);
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        { Cons expression = ((Cons)(Stella.readSExpressionFromString(stringlist)));
          Stella_Object term = null;
          Cons result = Stella.NIL;

          { Stella_Object ref = null;
            Cons iter000 = expression;
            Cons collect000 = null;

            for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
              ref = iter000.value;
              term = ((ref == Logic.SYM_STELLA_NULL) ? null : Logic.evaluateTerm(ref));
              if (collect000 == null) {
                {
                  collect000 = Cons.cons(term, Stella.NIL);
                  if (result == Stella.NIL) {
                    result = collect000;
                  }
                  else {
                    Cons.addConsToEndOfConsList(result, collect000);
                  }
                }
              }
              else {
                {
                  collect000.rest = Cons.cons(term, Stella.NIL);
                  collect000 = collect000.rest;
                }
              }
            }
          }
          return (result);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  static boolean legalOperatorP(Symbol operator) {
    return (Logic.$KIF_SENTENCE_OPERATORS$.memberP(operator) ||
        (Logic.$KIF_TERM_OPERATORS$.memberP(operator) ||
         Stella.getQuotedTree("((<=>> <<=> <<=>> <~> <~>> <<~> <<~>> ABOUT <<= =>> <~ ~> <<~ ~>>) \"/PLI\")", "/PLI").memberP(operator)));
  }

  /** Returns the Stella KEYWORD <code>name</code> if it exists.  Case sensitive.
   * @param name
   * @return Keyword
   */
  public static Keyword getKeyword(String name) {
    return (Keyword.lookupKeyword(name));
  }

  /** Returns the Stella SYMBOL <code>name</code> visible in <code>module</code> if it
   * exists.  <code>name</code> is ALWAYS treated literally and case sensitively.
   * @param name
   * @param module
   * @param environment
   * @return Symbol
   */
  public static Symbol getSymbol(String name, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          return (Symbol.lookupSymbol(name));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Returns the logical operator object (a Stella SYMBOL) for <code>name</code>.
   * If no such operator exists then a <code>noSuchObject</code> exception is thrown.
   * @param name
   * @return Symbol
   */
  public static Symbol getOperator(String name) {
    if (!(Stella.allUpperCaseStringP(name))) {
      name = Native.stringUpcase(name);
    }
    { Symbol operator = Symbol.lookupSymbolInModule(name, Logic.$LOGIC_MODULE$, false);

      if ((operator != null) &&
          PLI.legalOperatorP(operator)) {
        return (operator);
      }
      else {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("No operator named `" + name + "'");
          throw ((NoSuchObjectException)(NoSuchObjectException.newNoSuchObjectException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
    }
  }

  /** Look for an object named <code>name</code> that is local to
   * or visible from the module <code>module</code>.  <code>name</code> is not taken literally
   * but will be parsed first with the PowerLoom symbol reader and, hence,
   * can contain escape characters, module prefixes, etc.
   * @param name
   * @param module
   * @param environment
   * @return Stella_Object
   */
  public static Stella_Object getObject(String name, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          return (Logic.getInstance(Stella.lookupStellaName(name)));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Look for an object named <code>name</code> that is local to
   * or visible from the module <code>moduleName</code>.  A module name of <code>null</code> or the
   * empty string refers to the current module.  If no module can be found
   * with the name <code>moduleName</code>, then a STELLA <code>noSuchContextException</code> is thrown.
   * <code>name</code> is not taken literally but will be parsed first (see <code>getObject</code>).
   * @param name
   * @param moduleName
   * @param environment
   * @return Stella_Object
   */
  public static Stella_Object sGetObject(String name, String moduleName, Environment environment) {
    return (PLI.getObject(name, ((Module)(PLI.safelyGetModule(moduleName, environment))), environment));
  }

  /** Return a class/concept named <code>name</code> that is local to
   * or visible from the module <code>module</code>.  <code>name</code> is not taken literally but
   * will be parsed first (see <code>getObject</code>).
   * @param name
   * @param module
   * @param environment
   * @return LogicObject
   */
  public static LogicObject getConcept(String name, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          return (Logic.getClass(Stella.lookupStellaName(name)));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return a class/concept named <code>name</code> that is local to
   * or visible from the module <code>moduleName</code>.  A module name of <code>null</code> or the
   * empty string refers to the current module.  If no module can be found
   * with the name <code>moduleName</code>, then a Stella <code>noSuchContextException</code> is thrown.
   * <code>name</code> is not taken literally but will be parsed first (see <code>getObject</code>).
   * @param name
   * @param moduleName
   * @param environment
   * @return LogicObject
   */
  public static LogicObject sGetConcept(String name, String moduleName, Environment environment) {
    return (PLI.getConcept(name, ((Module)(PLI.safelyGetModule(moduleName, environment))), environment));
  }

  /** Return a concept or relation named <code>name</code> that is local to
   * or visible from the module <code>module</code>.  <code>name</code> is not taken literally but will
   * be parsed first (see <code>getObject</code>).
   * @param name
   * @param module
   * @param environment
   * @return LogicObject
   */
  public static LogicObject getRelation(String name, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          return (Logic.getRelation(Stella.lookupStellaName(name)));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return a concept or relation named <code>name</code> that is local to
   * or visible from the module <code>moduleName</code>.  A module name of <code>null</code> or the
   * empty string refers to the current module.  If no module can be found
   * with the name <code>moduleName</code>, then a Stella <code>noSuchContextException</code> is thrown.
   * <code>name</code> is not taken literally but will be parsed first (see <code>getObject</code>).
   * @param name
   * @param moduleName
   * @param environment
   * @return LogicObject
   */
  public static LogicObject sGetRelation(String name, String moduleName, Environment environment) {
    return (PLI.getRelation(name, ((Module)(PLI.safelyGetModule(moduleName, environment))), environment));
  }

  /** Return relations that have been referenced but not defined in <code>module</code>.
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getUndefinedRelations(Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          module = ((Module)(Stella.$MODULE$.get()));
          return (PLI.consToPlIterator(Logic.callListUndefinedRelations(module, false)));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return the name, qualified as necessary, so that <code>obj</code> can be found from
   * <code>module</code>.  If there is no name for the object return <code>null</code>.
   * @param obj
   * @param module
   * @param environment
   * @return String
   */
  public static String getNameInModule(Stella_Object obj, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          { Surrogate testValue000 = Stella_Object.safePrimaryType(obj);

            if (Surrogate.subtypeOfP(testValue000, Logic.SGT_LOGIC_SKOLEM)) {
              { Skolem obj000 = ((Skolem)(obj));

                return (null);
              }
            }
            else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_LOGIC_LOGIC_OBJECT)) {
              { LogicObject obj000 = ((LogicObject)(obj));

                return (Native.stringify(Logic.objectName(obj000)));
              }
            }
            else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_STELLA_GENERALIZED_SYMBOL)) {
              { GeneralizedSymbol obj000 = ((GeneralizedSymbol)(obj));

                return (Native.stringify(obj000));
              }
            }
            else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_STELLA_MODULE)) {
              { Module obj000 = ((Module)(obj));

                return (obj000.moduleFullName);
              }
            }
            else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_STELLA_CONTEXT)) {
              { Context obj000 = ((Context)(obj));

                return (obj000.contextName());
              }
            }
            else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_LOGIC_COMPUTED_PROCEDURE)) {
              { ComputedProcedure obj000 = ((ComputedProcedure)(obj));

                return (Native.stringify(obj000.surrogateValueInverse));
              }
            }
            else {
              return (null);
            }
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return the fully qualified name of <code>obj</code>, if it has one.  Otherwise return <code>null</code>.
   * @param obj
   * @return String
   */
  public static String getName(Stella_Object obj) {
    return (PLI.getNameInModule(obj, Stella.$ROOT_MODULE$, null));
  }

  /** Return the short name of <code>obj</code>, if it has one.  Otherwise return <code>null</code>.
   * @param obj
   * @return String
   */
  public static String getShortName(Stella_Object obj) {
    { Surrogate testValue000 = Stella_Object.safePrimaryType(obj);

      if (Surrogate.subtypeOfP(testValue000, Logic.SGT_LOGIC_SKOLEM)) {
        { Skolem obj000 = ((Skolem)(obj));

          return (null);
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_LOGIC_LOGIC_OBJECT)) {
        { LogicObject obj000 = ((LogicObject)(obj));

          return (Logic.objectNameString(obj000));
        }
      }
      else if (Surrogate.subtypeOfKeywordP(testValue000)) {
        { Keyword obj000 = ((Keyword)(obj));

          return (":" + obj000.symbolName);
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_STELLA_GENERALIZED_SYMBOL)) {
        { GeneralizedSymbol obj000 = ((GeneralizedSymbol)(obj));

          return (obj000.symbolName);
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_STELLA_CONTEXT)) {
        { Context obj000 = ((Context)(obj));

          return (obj000.contextName());
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_LOGIC_COMPUTED_PROCEDURE)) {
        { ComputedProcedure obj000 = ((ComputedProcedure)(obj));

          return (obj000.surrogateValueInverse.symbolName);
        }
      }
      else {
        return (null);
      }
    }
  }

  /** Return the fully qualified name of <code>skolem</code>.  Note that skolems are anonymous objects
   * which cannot be referenced by their name in logic expressions, so this function is only useful in special
   * circumstances such as inside specialist computations, etc.
   * @param skolem
   * @return String
   */
  public static String getSkolemName(Skolem skolem) {
    return (PLI.getNameInModule(skolem.skolemName, Stella.$ROOT_MODULE$, null));
  }

  /** Return the unqualified name of <code>skolem</code>.  Note that skolems are anonymous objects which
   * cannot be referenced by their name in logic expressions, so this function is only useful in special
   * circumstances such as inside specialist computations, etc.
   * @param skolem
   * @return String
   */
  public static String getSkolemShortName(Skolem skolem) {
    return (skolem.skolemName.symbolName);
  }

  /** Return the fully qualified name of <code>variable</code>.
   * @param variable
   * @return String
   */
  public static String getVariableName(PatternVariable variable) {
    return (PLI.getNameInModule(variable.skolemName, Stella.$ROOT_MODULE$, null));
  }

  /** Return the unqualified name of <code>variable</code>.
   * @param variable
   * @return String
   */
  public static String getVariableShortName(PatternVariable variable) {
    return (variable.skolemName.symbolName);
  }

  /** Return a printed representation of the term <code>self</code> as a string.
   * @param self
   * @return String
   */
  public static String objectToString(Stella_Object self) {
    if (self == null) {
      return (null);
    }
    else {
      { Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();

        try {
          Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, true);
          { Surrogate testValue000 = Stella_Object.safePrimaryType(self);

            if (Surrogate.subtypeOfStringP(testValue000)) {
              { StringWrapper self000 = ((StringWrapper)(self));

                return (self000.wrapperValue);
              }
            }
            else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_LOGIC_SKOLEM)) {
              { Skolem self000 = ((Skolem)(self));

                { Stella_Object value = Logic.valueOf(self000);

                  if (value == self000) {
                    return (Native.stringify(self000));
                  }
                  else {
                    return (PLI.objectToString(value));
                  }
                }
              }
            }
            else if (Surrogate.subtypeOfP(testValue000, PLI.SGT_PLI_PL_ITERATOR)) {
              { PlIterator self000 = ((PlIterator)(self));

                return (Native.stringify(self000.consify()));
              }
            }
            else {
              return (Native.stringify(self));
            }
          }

        } finally {
          Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
        }
      }
    }
  }

  /** Coerce <code>self</code> to an integer, or throw a Stella Exception if the coersion is not feasible.
   * Floating point values will be coerced by rounding.
   * @param self
   * @return int
   */
  public static int objectToInteger(Stella_Object self) {
    { Surrogate testValue000 = Stella_Object.safePrimaryType(self);

      if (Surrogate.subtypeOfP(testValue000, Logic.SGT_LOGIC_SKOLEM)) {
        { Skolem self000 = ((Skolem)(self));

          { Stella_Object value = Logic.valueOf(self000);

            if (value == self000) {
              { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

                stream000.nativeStream.print("Can't coerce `" + self000 + "' to an integer.");
                throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
              }
            }
            else {
              return (PLI.objectToInteger(value));
            }
          }
        }
      }
      else if (Surrogate.subtypeOfIntegerP(testValue000)) {
        { IntegerWrapper self000 = ((IntegerWrapper)(self));

          return (self000.wrapperValue);
        }
      }
      else if (Surrogate.subtypeOfFloatP(testValue000)) {
        { FloatWrapper self000 = ((FloatWrapper)(self));

          return (Native.round(self000.wrapperValue));
        }
      }
      else {
        { OutputStringStream stream001 = OutputStringStream.newOutputStringStream();

          stream001.nativeStream.print("Can't coerce `" + self + "' to an integer.");
          throw ((StellaException)(StellaException.newStellaException(stream001.theStringReader()).fillInStackTrace()));
        }
      }
    }
  }

  /** Coerce <code>self</code> to a float, or throw a Stella Exception if the coersion is not feasible.
   * @param self
   * @return double
   */
  public static double objectToFloat(Stella_Object self) {
    { Surrogate testValue000 = Stella_Object.safePrimaryType(self);

      if (Surrogate.subtypeOfP(testValue000, Logic.SGT_LOGIC_SKOLEM)) {
        { Skolem self000 = ((Skolem)(self));

          { Stella_Object value = Logic.valueOf(self000);

            if (value == self000) {
              { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

                stream000.nativeStream.print("Can't coerce `" + self000 + "' to a float.");
                throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
              }
            }
            else {
              return (PLI.objectToFloat(value));
            }
          }
        }
      }
      else if (Surrogate.subtypeOfIntegerP(testValue000)) {
        { IntegerWrapper self000 = ((IntegerWrapper)(self));

          return (self000.numberWrapperToFloat());
        }
      }
      else if (Surrogate.subtypeOfFloatP(testValue000)) {
        { FloatWrapper self000 = ((FloatWrapper)(self));

          return (self000.wrapperValue);
        }
      }
      else {
        { OutputStringStream stream001 = OutputStringStream.newOutputStringStream();

          stream001.nativeStream.print("Can't coerce `" + self + "' to a float.");
          throw ((StellaException)(StellaException.newStellaException(stream001.theStringReader()).fillInStackTrace()));
        }
      }
    }
  }

  /** Return a string representing a printed
   * representation of the object <code>self</code>.  Like <code>objectToString</code>, but puts
   * escaped double quotes around strings.
   * @param self
   * @return String
   */
  public static String objectToParsableString(Stella_Object self) {
    if (Surrogate.subtypeOfStringP(Stella_Object.safePrimaryType(self))) {
      { StringWrapper self000 = ((StringWrapper)(self));

        return ("\"" + self000.wrapperValue + "\"");
      }
    }
    else {
      return (PLI.objectToString(self));
    }
  }

  /** Return the name symbol of the STELLA class of which <code>self</code> is a direct instance.
   * @param self
   * @return Symbol
   */
  public static Symbol getStellaType(Stella_Object self) {
    return (Surrogate.typeToSymbol(self.primaryType()));
  }

  /** Return the name symbol of the logic object type of <code>self</code>.  This type describes the basic
   * role this object plays in the logic system such as 'PROPOSITION', 'CONCEPT', 'THING', etc., as indicated by
   * its native object type, it does not have anything to do with type propositions asserted about <code>self</code>.
   * @param self
   * @return Symbol
   */
  public static Symbol getLogicType(Stella_Object self) {
    return (Surrogate.typeToSymbol(Logic.logicalType(self)));
  }

  /** Return the qualified name of the STELLA class of which <code>self</code> is a direct instance.
   * @param self
   * @return String
   */
  public static String getStellaTypeName(Stella_Object self) {
    { Surrogate type = self.primaryType();

      return (Stella.computeFullName(type.symbolName, ((Module)(type.homeContext))));
    }
  }

  /** Return the unqualified name of the STELLA class of which <code>self</code> is a direct instance.
   * @param self
   * @return String
   */
  public static String getStellaTypeShortName(Stella_Object self) {
    return (self.primaryType().symbolName);
  }

  /** Return the qualified name of the logic type of <code>self</code>.
   * @param self
   * @return String
   */
  public static String getLogicTypeName(Stella_Object self) {
    { Surrogate type = Logic.logicalType(self);

      return (Stella.computeFullName(type.symbolName, ((Module)(type.homeContext))));
    }
  }

  /** Return the unqualified name of the logic type of <code>self</code>.
   * @param self
   * @return String
   */
  public static String getLogicTypeShortName(Stella_Object self) {
    return (Logic.logicalType(self).symbolName);
  }

  /** Evaluate <code>string</code> with respect to <code>module</code> and <code>environment</code>
   * and return the corresponding logical term.  <code>type</code> is a concept used to assist the
   * correct interpretation of <code>string</code>.
   * <p>
   * Currently <code>type</code> only has an effect on the interpretation of literal types.
   * @param string
   * @param type
   * @param module
   * @param environment
   * @return Stella_Object
   */
  public static Stella_Object stringToObject(String string, LogicObject type, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          module = ((Module)(Stella.$MODULE$.get()));
          { Stella_Object obj = Stella.readSExpressionFromString(string);

            if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(obj), Logic.SGT_STELLA_LITERAL_WRAPPER)) {
              { LiteralWrapper obj000 = ((LiteralWrapper)(obj));

                if (type == null) {
                  return (obj000);
                }
                { Surrogate testValue000 = Stella_Object.safePrimaryType(obj000);

                  if (Surrogate.subtypeOfStringP(testValue000)) {
                    { StringWrapper obj001 = ((StringWrapper)(obj000));

                      if (NamedDescription.subrelationOfP(((NamedDescription)(type)), PLI.$STRING_CONCEPT$)) {
                        return (obj001);
                      }
                      else {
                        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

                          stream000.nativeStream.print("String argument found, but `" + type + "' is not a subconcept of `" + PLI.$STRING_CONCEPT$ + "'");
                          throw ((ParsingError)(ParsingError.newParsingError(stream000.theStringReader()).fillInStackTrace()));
                        }
                      }
                    }
                  }
                  else if (Surrogate.subtypeOfIntegerP(testValue000)) {
                    { IntegerWrapper obj001 = ((IntegerWrapper)(obj000));

                      if (NamedDescription.subrelationOfP(((NamedDescription)(type)), PLI.$INTEGER_CONCEPT$)) {
                        return (obj001);
                      }
                      else if (NamedDescription.subrelationOfP(((NamedDescription)(type)), PLI.$FLOAT_CONCEPT$)) {
                        return (FloatWrapper.wrapFloat(((double)(obj001.wrapperValue))));
                      }
                      else {
                        return (PLI.getObject(string, module, environment));
                      }
                    }
                  }
                  else if (Surrogate.subtypeOfFloatP(testValue000)) {
                    { FloatWrapper obj001 = ((FloatWrapper)(obj000));

                      if (NamedDescription.subrelationOfP(((NamedDescription)(type)), PLI.$FLOAT_CONCEPT$)) {
                        return (obj001);
                      }
                      else {
                        return (PLI.getObject(string, module, environment));
                      }
                    }
                  }
                  else {
                    { OutputStringStream stream001 = OutputStringStream.newOutputStringStream();

                      stream001.nativeStream.print("`" + testValue000 + "' is not a valid case option");
                      throw ((StellaException)(StellaException.newStellaException(stream001.theStringReader()).fillInStackTrace()));
                    }
                  }
                }
              }
            }
            else {
              if (type == null) {
                return (PLI.getObject(string, module, environment));
              }
              else if (NamedDescription.subrelationOfP(((NamedDescription)(type)), PLI.$STRING_CONCEPT$)) {
                return (StringWrapper.wrapString(Native.string_copy(string)));
              }
              else if (NamedDescription.subrelationOfP(((NamedDescription)(type)), PLI.$LITERAL_CONCEPT$)) {
                { OutputStringStream stream002 = OutputStringStream.newOutputStringStream();

                  stream002.nativeStream.print("`" + string + "' is a non-literal, but `" + type + "' is a subconcept of `" + PLI.$LITERAL_CONCEPT$ + "'");
                  throw ((ParsingError)(ParsingError.newParsingError(stream002.theStringReader()).fillInStackTrace()));
                }
              }
              else {
                return (PLI.getObject(string, module, environment));
              }
            }
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Read the STELLA <code>expression</code> in <code>module</code> and return the result.
   * Raises a reader exception in case of incorrect STELLA syntax.
   * @param expression
   * @param module
   * @param environment
   * @return Stella_Object
   */
  public static Stella_Object stringToStellaExpression(String expression, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          return (Stella.readSExpressionFromString(expression));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  static Cons helpGetTrueExtensionMembers(NamedDescription relation, boolean specializeP) {
    { Cons value000 = Stella.NIL;

      { Stella_Object p = null;
        Iterator iter000 = NamedDescription.allExtensionMembers(relation);
        Cons collect000 = null;

        while (iter000.nextP()) {
          p = iter000.value;
          if ((!((Proposition)(p)).deletedP()) &&
              ((((Boolean)(Logic.$REVERSEPOLARITYp$.get())).booleanValue() ? Proposition.falseP(((Proposition)(p))) : (Proposition.trueP(((Proposition)(p))) ||
              Proposition.functionWithDefinedValueP(((Proposition)(p))))))) {
            if (collect000 == null) {
              {
                collect000 = Cons.cons(p, Stella.NIL);
                if (value000 == Stella.NIL) {
                  value000 = collect000;
                }
                else {
                  Cons.addConsToEndOfConsList(value000, collect000);
                }
              }
            }
            else {
              {
                collect000.rest = Cons.cons(p, Stella.NIL);
                collect000 = collect000.rest;
              }
            }
          }
        }
      }
      { Cons result = value000;

        if (specializeP) {
          { LogicObject sub = null;
            Iterator iter001 = LogicObject.allSubcollections(relation);

            while (iter001.nextP()) {
              sub = ((LogicObject)(iter001.value));
              if (Stella_Object.isaP(sub, Logic.SGT_LOGIC_NAMED_DESCRIPTION)) {
                { Stella_Object p = null;
                  Iterator iter002 = NamedDescription.allExtensionMembers(((NamedDescription)(sub)));

                  while (iter002.nextP()) {
                    p = iter002.value;
                    if ((!((Proposition)(p)).deletedP()) &&
                        ((((Boolean)(Logic.$REVERSEPOLARITYp$.get())).booleanValue() ? Proposition.falseP(((Proposition)(p))) : (Proposition.trueP(((Proposition)(p))) ||
                        Proposition.functionWithDefinedValueP(((Proposition)(p))))))) {
                      result = Cons.cons(p, result);
                    }
                  }
                }
              }
            }
          }
          return (result.removeDuplicates());
        }
        return (result);
      }
    }
  }

  static Cons helpGetPropositions(LogicObject relation, Cons arguments, int limit, Module module, Environment environment) {
    if (relation == null) {
      return (Stella.NIL);
    }
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          { boolean assertionsonlyP = (environment != null) &&
                Stella.stringEqlP(environment.level, "ASSERTION");
            boolean specializeP = !assertionsonlyP;

            { Stella_Object value000 = null;

              { Stella_Object arg = null;
                Cons iter000 = arguments;

                loop000 : for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
                  arg = iter000.value;
                  if ((arg != null) &&
                      Stella_Object.isaP(arg, Logic.SGT_LOGIC_LOGIC_OBJECT)) {
                    value000 = arg;
                    break loop000;
                  }
                }
              }
              { Stella_Object argumentwithbacklinks = value000;
                Iterator iterator = ((argumentwithbacklinks != null) ? ((Iterator)(Logic.allTrueDependentPropositions(argumentwithbacklinks, relation.surrogateValueInverse, specializeP))) : PLI.helpGetTrueExtensionMembers(((NamedDescription)(relation)), specializeP).allocateIterator());
                Cons results = Stella.NIL;

                if (!(assertionsonlyP)) {
                  Native.setSpecial(Stella.$CONTEXT$, Logic.getPropertyTestContext());
                }
                { Proposition p = null;
                  Iterator iter001 = iterator;

                  loop001 : while (iter001.nextP()) {
                    p = ((Proposition)(iter001.value));
                    { boolean testValue000 = false;

                      { boolean alwaysP000 = true;

                        { Stella_Object inputarg = null;
                          Cons iter002 = arguments;
                          Stella_Object arg2 = null;
                          Vector vector000 = p.arguments;
                          int index000 = 0;
                          int length000 = vector000.length();

                          loop002 : for (;(!(iter002 == Stella.NIL)) &&
                                    (index000 < length000); iter002 = iter002.rest, index000 = index000 + 1) {
                            inputarg = iter002.value;
                            arg2 = (vector000.theArray)[index000];
                            if (!((inputarg == null) ||
                                Stella_Object.eqlP(inputarg, Logic.valueOf(arg2)))) {
                              alwaysP000 = false;
                              break loop002;
                            }
                          }
                        }
                        testValue000 = alwaysP000;
                      }
                      if (testValue000) {
                        testValue000 = arguments.length() == p.arguments.length();
                      }
                      if (testValue000) {
                        results = Cons.cons(p, results);
                        limit = limit - 1;
                        if (limit == 0) {
                          break loop001;
                        }
                      }
                    }
                  }
                }
                return (results);
              }
            }
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return a proposition matching <code>relationAndArguments</code> that
   * has been asserted (or inferred by forward chaining).  <code>relationAndArguments</code>
   * is a sequence containing objects and nulls.  The first argument must be the
   * name of a relation.  A null value acts like a wild card.  If more than one 
   * proposition matches the input criteria, the selection among satisficing
   * propositions is arbitrary.  This procedure is normally applied to single-valued
   * relations or functions.
   * @param relationAndArguments
   * @param module
   * @param environment
   * @return Proposition
   */
  public static Proposition getProposition(Stella_Object relationAndArguments, Module module, Environment environment) {
    { Cons list = PLI.sequenceToConsList(relationAndArguments);
      Stella_Object relation = list.value;
      Cons arguments = list.rest;

      return (((Proposition)(PLI.helpGetPropositions(((LogicObject)(relation)), arguments, 1, module, environment).value)));
    }
  }

  /** Return a proposition matching <code>relationAndArguments</code> that
   * has been asserted (or inferred by forward chaining).  <code>relationAndArguments</code>
   * is a string that begins with a left parenthesis, followed by a relation name, 
   * one or more argument identifiers, and terminated by a right parenthesis.  Each
   * argument identifier can be the name of a logical constant, a literal reference
   * such as a number, or the null identifier which acts like a wild card.
   * If more than one proposition matches the input criteria, the selection among
   * satisficing propositions is arbitrary.  This procedure is normally applied to
   * single-valued relations or functions.
   * <p>
   * A module name of <code>null</code> or the empty string refers to the current module.  If no module
   * with name <code>moduleName</code> can be found, a STELLA <code>noSuchContextException</code> is thrown.
   * @param relationAndArguments
   * @param moduleName
   * @param environment
   * @return Proposition
   */
  public static Proposition sGetProposition(String relationAndArguments, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);
      Cons elements = PLI.explodeStringList(relationAndArguments, ((Module)(module)));
      Stella_Object relation = elements.value;
      Cons arguments = elements.rest;

      return (((Proposition)(PLI.helpGetPropositions(((LogicObject)(relation)), arguments, 1, ((Module)(module)), environment).value)));
    }
  }

  /** Return propositions matching <code>relationAndArguments</code> that
   * have been asserted (or inferred by forward chaining).  <code>relationAndArguments</code>
   * is a sequence containing objects and nulls.  The first argument must be the
   * name of a relation.  A null value acts like a wild card.
   * @param relationAndArguments
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getPropositions(Stella_Object relationAndArguments, Module module, Environment environment) {
    { Cons list = PLI.sequenceToConsList(relationAndArguments);
      Stella_Object relation = list.value;
      Cons arguments = list.rest;

      return (PLI.consToPlIterator(PLI.helpGetPropositions(((LogicObject)(relation)), arguments, 0, module, environment)));
    }
  }

  /** Return propositions matching <code>relationAndArguments</code> that
   * have been asserted (or inferred by forward chaining).  <code>relationAndArguments</code>
   * is a string that begins with a left parenthesis, followed by a relation name, 
   * one or more argument identifiers, and terminated by a right parenthesis.  Each
   * argument identifier can be the name of a logical constant, a literal 
   * reference (e.g., a number), or the null identifier which acts like a wild card.
   * <p>
   * A module name of <code>null</code> or the empty string refers to the current module.  If no module
   * with name <code>moduleName</code> can be found, a STELLA <code>noSuchContextException</code> is thrown.
   * @param relationAndArguments
   * @param moduleName
   * @param environment
   * @return PlIterator
   */
  public static PlIterator sGetPropositions(String relationAndArguments, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);
      Cons elements = PLI.explodeStringList(relationAndArguments, ((Module)(module)));
      Stella_Object relation = elements.value;
      Cons arguments = elements.rest;

      return (PLI.consToPlIterator(PLI.helpGetPropositions(((LogicObject)(relation)), arguments, 0, ((Module)(module)), environment)));
    }
  }

  /** Return inconsistent propositions visible in <code>module</code>.
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getInconsistentPropositions(Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          module = ((Module)(Stella.$MODULE$.get()));
          return (PLI.iteratorToPlIterator(Logic.allInconsistentPropositions(module, false)));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return propositions such that (<code>relation</code> <code>arg</code>)
   * is true.  The <code>relation</code> argument must be bound to a relation.  <code>arg</code> may be
   * set to NULL, which is interpreted as a wildcard.
   * @param relation
   * @param arg
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getUnaryPropositions(LogicObject relation, Stella_Object arg, Module module, Environment environment) {
    return (PLI.consToPlIterator(PLI.helpGetPropositions(relation, Cons.consList(Cons.cons(arg, Stella.NIL)), 0, module, environment)));
  }

  /** Return a proposition such that (<code>relation</code> <code>arg1</code> <code>arg2</code>)
   * is true.  The <code>relation</code> argument must be bound to a relation.  One or both
   * of the <code>arg1</code> and <code>arg2</code> arguments may be set to NULL, which is interpreted
   * as a wildcard. If more than one proposition matches the input criteria,
   * the selection is arbitrary.  This procedure is normally applied to single-valued
   * relations or functions.
   * @param relation
   * @param arg1
   * @param arg2
   * @param module
   * @param environment
   * @return Proposition
   */
  public static Proposition getBinaryProposition(LogicObject relation, Stella_Object arg1, Stella_Object arg2, Module module, Environment environment) {
    return (((Proposition)(PLI.helpGetPropositions(relation, Cons.consList(Cons.cons(arg1, Cons.cons(arg2, Stella.NIL))), 1, module, environment).value)));
  }

  /** Return propositions such that (<code>relation</code> <code>arg1</code> <code>arg2</code>)
   * is true.  The <code>relation</code> argument must be bound to a relation.  One or both
   * of the <code>arg1</code> and <code>arg2</code> arguments may be set to NULL, which is interpreted
   * as a wildcard.
   * @param relation
   * @param arg1
   * @param arg2
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getBinaryPropositions(LogicObject relation, Stella_Object arg1, Stella_Object arg2, Module module, Environment environment) {
    return (PLI.consToPlIterator(PLI.helpGetPropositions(relation, Cons.consList(Cons.cons(arg1, Cons.cons(arg2, Stella.NIL))), 0, module, environment)));
  }

  /** Return all values <code>v</code> such that (<code>relation</code> <code>arg</code> <code>v</code>)
   * has been asserted or can be inferred via a general PowerLoom <code>retrieve</code>.
   * Both <code>relation</code> and <code>arg</code> have to be non-NULL.
   * @param relation
   * @param arg
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getInferredBinaryPropositionValues(LogicObject relation, Stella_Object arg, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          if ((relation != null) &&
              (arg != null)) {
            return (PLI.consToPlIterator(Logic.applyCachedRetrieve(Cons.list$(Cons.cons(PLI.SYM_PLI_pR, Cons.cons(PLI.SYM_PLI_pI, Cons.cons(PLI.SYM_PLI_pV, Cons.cons(Stella.NIL, Stella.NIL))))), Cons.list$(Cons.cons(PLI.SYM_PLI_pR, Cons.cons(PLI.SYM_PLI_pI, Cons.cons(PLI.SYM_PLI_pV, Cons.cons(Stella.NIL, Stella.NIL))))), Cons.consList(Cons.cons(relation, Cons.cons(arg, Cons.cons(null, Stella.NIL)))), Cons.consList(Stella.NIL), PLI.SYM_PLI_F_GET_INFERRED_BINARY_PROPOSITION_VALUES_QUERY_000, new Object[2])));
          }
          else {
            return (PLI.EMPTY_PL_ITERATOR);
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return all values <code>v</code> such that (<code>relationName</code> <code>argName</code> <code>v</code>)
   * has been asserted or can be inferred via a general PowerLoom <code>retrieve</code>.
   * <p>
   * A module name of <code>null</code> or the empty string refers to the current module. 
   * If no module can be found with the name <code>moduleName</code>, then a STELLA
   * <code>noSuchContextException</code> is thrown.
   * @param relationName
   * @param argName
   * @param moduleName
   * @param environment
   * @return PlIterator
   */
  public static PlIterator sGetInferredBinaryPropositionValues(String relationName, String argName, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);
      Stella_Object relation = PLI.safelyGetRelation(relationName, ((Module)(module)), environment);
      Stella_Object renamed_Object = PLI.safelyGetObject(argName, ((Module)(module)), environment);

      return (PLI.getInferredBinaryPropositionValues(((LogicObject)(relation)), renamed_Object, ((Module)(module)), environment));
    }
  }

  /** Return all propositions that have <code>renamed_Object</code> among their arguments,
   * and that are TRUE in the scope of the module <code>module</code>.
   * @param renamed_Object
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getPropositionsOf(LogicObject renamed_Object, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          if (renamed_Object != null) {
            return (PLI.listToPlIterator(Logic.allFactsOfInstance(renamed_Object, false, false)));
          }
          else {
            return (PLI.EMPTY_PL_ITERATOR);
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return all propositions that have the object named <code>objectName</code> among
   * their arguments, and that are TRUE in the scope of the module <code>moduleName</code>.
   * A module name of <code>null</code> or the empty string refers to the current module. 
   * If no module can be found with the name <code>moduleName</code>, then a Stella 
   * <code>noSuchContextException</code> is thrown.
   * @param objectName
   * @param moduleName
   * @param environment
   * @return PlIterator
   */
  public static PlIterator sGetPropositionsOf(String objectName, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);
      Stella_Object renamed_Object = PLI.safelyGetObject(objectName, ((Module)(module)), environment);

      return (PLI.getPropositionsOf(((LogicObject)(renamed_Object)), ((Module)(module)), environment));
    }
  }

  /** Return propositions that have been locally conceived in
   * the module <code>module</code> (but are not necessarily true).
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getPropositionsInModule(Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          module = ((Module)(Stella.$MODULE$.get()));
          return (PLI.consToPlIterator(Logic.allPropositions(module, true).consify()));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return TRUE if the proposition (<code>relation</code> <code>arg</code>) has
   * been asserted (or inferred by forward chaining).
   * @param relation
   * @param arg
   * @param module
   * @param environment
   * @return boolean
   */
  public static boolean isTrueUnaryProposition(LogicObject relation, Stella_Object arg, Module module, Environment environment) {
    return (!(PLI.helpGetPropositions(relation, Cons.consList(Cons.cons(arg, Stella.NIL)), 1, module, environment) == Stella.NIL));
  }

  /** Return TRUE if the proposition (<code>relation</code> <code>arg</code> <code>value</code>) has
   * been asserted (or inferred by forward chaining).
   * @param relation
   * @param arg
   * @param value
   * @param module
   * @param environment
   * @return boolean
   */
  public static boolean isTrueBinaryProposition(LogicObject relation, Stella_Object arg, Stella_Object value, Module module, Environment environment) {
    return (PLI.getBinaryProposition(relation, arg, value, module, environment) != null);
  }

  /** Return TRUE if a proposition (<code>relation</code> <code>args</code>) has
   * been asserted (or inferred by forward chaining).
   * @param relationAndArguments
   * @param module
   * @param environment
   * @return boolean
   */
  public static boolean isTrueNaryProposition(Stella_Object relationAndArguments, Module module, Environment environment) {
    return (PLI.getProposition(relationAndArguments, module, environment) != null);
  }

  /** Return TRUE if a proposition that prints as the string
   * <code>relationAndArguments</code> is true in the module named <code>moduleName</code>.
   * A module name of <code>null</code> or the empty string refers to the current module. 
   * If no module can be found with the name <code>moduleName</code>, then a Stella 
   * <code>noSuchContextException</code> is thrown.
   * @param relationAndArguments
   * @param moduleName
   * @param environment
   * @return boolean
   */
  public static boolean sIsTrueNaryProposition(String relationAndArguments, String moduleName, Environment environment) {
    return (PLI.sGetProposition(relationAndArguments, moduleName, environment) != null);
  }

  /** Return TRUE if <code>proposition</code> is TRUE in the module <code>module</code>.
   * @param proposition
   * @param module
   * @param environment
   * @return boolean
   */
  public static boolean isTrueProposition(Proposition proposition, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          return ((!proposition.deletedP()) &&
              ((((Boolean)(Logic.$REVERSEPOLARITYp$.get())).booleanValue() ? Proposition.falseP(proposition) : (Proposition.trueP(proposition) ||
              Proposition.functionWithDefinedValueP(proposition)))));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return TRUE if <code>sub</code> is a subconcept/subrelation of <code>renamed_Super</code>.
   * @param sub
   * @param renamed_Super
   * @param module
   * @param environment
   * @return boolean
   */
  public static boolean isSubrelation(LogicObject sub, LogicObject renamed_Super, Module module, Environment environment) {
    if ((sub == null) ||
        (renamed_Super == null)) {
      return (false);
    }
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          return (TruthValue.trueTruthValueP(Description.descriptionSpecializesDescriptionP(((Description)(sub)), ((Description)(renamed_Super)))));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return relations that specialize <code>relation</code>.
   * Non-reflexive.
   * @param relation
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getProperSubrelations(LogicObject relation, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          return (PLI.consToPlIterator(NamedDescription.allSubrelations(((NamedDescription)(relation)), true)));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return relations that directly specialize <code>relation</code>.
   * Non-reflexive.
   * @param relation
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getDirectSubrelations(LogicObject relation, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          return (PLI.consToPlIterator(NamedDescription.allDirectSubrelations(((NamedDescription)(relation)), true)));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return relations that generalize <code>relation</code>.
   * Non-reflexive.
   * @param relation
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getProperSuperrelations(LogicObject relation, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          return (PLI.consToPlIterator(NamedDescription.allSuperrelations(((NamedDescription)(relation)), true)));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return relations that directly generalize <code>relation</code>.
   * Non-reflexive.
   * @param relation
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getDirectSuperrelations(LogicObject relation, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          return (PLI.consToPlIterator(NamedDescription.allDirectSuperrelations(((NamedDescription)(relation)), true)));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return TRUE if <code>renamed_Object</code> is an instance of the concept <code>concept</code>.  This uses subsumption inference only.
   * @param renamed_Object
   * @param concept
   * @param module
   * @param environment
   * @return boolean
   */
  public static boolean isInstance(Stella_Object renamed_Object, LogicObject concept, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          return (Logic.testIsaP(renamed_Object, concept.surrogateValueInverse));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Deprecated - use <code>isInstance</code> instead.
   * @param renamed_Object
   * @param concept
   * @param module
   * @param environment
   * @return boolean
   */
  public static boolean isA(Stella_Object renamed_Object, LogicObject concept, Module module, Environment environment) {
    return (PLI.isInstance(renamed_Object, concept, module, environment));
  }

  /** Return instances of the concept <code>concept</code>.
   * Include instances of subconcepts of <code>concept</code>.  Depending on <code>concept</code>,
   * the return values could be (wrapped) literals.
   * @param concept
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getConceptInstances(LogicObject concept, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          module = ((Module)(Stella.$MODULE$.get()));
          if ((environment != null) &&
              Stella.stringEqlP(environment.level, "ASSERTION")) {
            return (PLI.listToPlIterator(Logic.assertedCollectionMembers(concept, false).removeDeletedMembers()));
          }
          else {
            return (PLI.retrieve(Cons.list$(Cons.cons(Logic.SYM_LOGIC_ALL, Cons.cons(Logic.SYM_LOGIC_pX, Cons.cons(Cons.cons(Logic.objectName(concept), Cons.cons(Logic.SYM_LOGIC_pX, Stella.NIL)), Cons.cons(Stella.NIL, Stella.NIL))))), module, environment));
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return instances of concept <code>conceptName</code>.
   * Include instances of subconcepts of <code>conceptName</code>.  Depending on <code>conceptName</code>,
   * the return values could be (wrapped) literals.
   * <p>
   * A module name of <code>null</code> or the empty string refers to the current module. 
   * If no module can be found with the name <code>moduleName</code>, then a Stella 
   * <code>noSuchContextException</code> is thrown.
   * @param conceptName
   * @param moduleName
   * @param environment
   * @return PlIterator
   */
  public static PlIterator sGetConceptInstances(String conceptName, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);
      Stella_Object concept = PLI.safelyGetConcept(conceptName, ((Module)(module)), environment);

      if ((module != null) &&
          (concept != null)) {
        return (PLI.getConceptInstances(((LogicObject)(concept)), ((Module)(module)), environment));
      }
      else {
        return (PLI.EMPTY_PL_ITERATOR);
      }
    }
  }

  /** Return instances of concept <code>concept</code>.
   * Exclude instances of subconcepts of <code>concept</code>.  Depending on <code>concept</code>,
   * the return values could be (wrapped) literals.
   * @param concept
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getDirectConceptInstances(LogicObject concept, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          module = ((Module)(Stella.$MODULE$.get()));
          if ((environment != null) &&
              Stella.stringEqlP(environment.level, "ASSERTION")) {
            return (PLI.listToPlIterator(Logic.assertedCollectionMembers(concept, true).removeDeletedMembers()));
          }
          else {
            return (PLI.retrieve(Cons.list$(Cons.cons(Logic.SYM_LOGIC_ALL, Cons.cons(Logic.SYM_LOGIC_pX, Cons.cons(Cons.list$(Cons.cons(Logic.SYM_STELLA_AND, Cons.cons(Cons.cons(Logic.objectName(concept), Cons.cons(Logic.SYM_LOGIC_pX, Stella.NIL)), Cons.cons(Cons.list$(Cons.cons(Logic.SYM_LOGIC_FAIL, Cons.cons(Cons.list$(Cons.cons(Logic.SYM_STELLA_EXISTS, Cons.cons(Cons.cons(Logic.SYM_LOGIC_pY, Stella.NIL), Cons.cons(Cons.list$(Cons.cons(Logic.SYM_STELLA_AND, Cons.cons(Cons.list$(Cons.cons(PLI.SYM_PLI_PROPER_SUBRELATION, Cons.cons(Logic.objectName(concept), Cons.cons(Cons.cons(Logic.SYM_LOGIC_pY, Stella.NIL), Stella.NIL)))), Cons.cons(Cons.list$(Cons.cons(Logic.SYM_LOGIC_pY, Cons.cons(Logic.SYM_LOGIC_pX, Cons.cons(Stella.NIL, Stella.NIL)))), Cons.cons(Stella.NIL, Stella.NIL))))), Cons.cons(Stella.NIL, Stella.NIL))))), Cons.cons(Stella.NIL, Stella.NIL)))), Cons.cons(Stella.NIL, Stella.NIL))))), Cons.cons(Stella.NIL, Stella.NIL))))), module, environment));
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return instances of concept <code>conceptName</code>.
   * Exclude instances of subconcepts of <code>conceptName</code>.  Depending on <code>conceptName</code>,
   * the return values could be (wrapped) literals.
   * <p>
   * A module name of <code>null</code> or the empty string refers to the current module. 
   * If no module can be found with the name <code>moduleName</code>, then a Stella 
   * <code>noSuchContextException</code> is thrown.
   * @param conceptName
   * @param moduleName
   * @param environment
   * @return PlIterator
   */
  public static PlIterator sGetDirectConceptInstances(String conceptName, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);
      Stella_Object concept = PLI.safelyGetConcept(conceptName, ((Module)(module)), environment);

      if (concept != null) {
        return (PLI.getDirectConceptInstances(((LogicObject)(concept)), ((Module)(module)), environment));
      }
      else {
        return (PLI.EMPTY_PL_ITERATOR);
      }
    }
  }

  /** Return members of concept <code>concept</code> that
   * have an attribute matching <code>value</code> for the binary relation <code>relation</code>, i.e.,
   * <code>_relationLresultGValue_</code> holds.
   * @param concept
   * @param relation
   * @param value
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getConceptInstancesMatchingValue(LogicObject concept, LogicObject relation, Stella_Object value, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          module = ((Module)(Stella.$MODULE$.get()));
          { PlIterator instances = PLI.getConceptInstances(concept, module, environment);
            Cons answers = Stella.NIL;

            { Stella_Object i = null;
              PlIterator iter000 = instances;

              while (iter000.nextP()) {
                i = iter000.value;
                if (PLI.isTrueBinaryProposition(relation, i, value, module, environment)) {
                  answers = Cons.cons(i, answers);
                }
              }
            }
            return (PLI.consToPlIterator(answers));
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return a member of concept <code>concept</code> that
   * has an attribute matching <code>value</code> for the binary relation <code>relation</code>, i.e.,
   * <code>_relationLresultGValue_</code> holds.
   * @param concept
   * @param relation
   * @param value
   * @param module
   * @param environment
   * @return Stella_Object
   */
  public static Stella_Object getConceptInstanceMatchingValue(LogicObject concept, LogicObject relation, Stella_Object value, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          module = ((Module)(Stella.$MODULE$.get()));
          { PlIterator instances = PLI.getConceptInstances(concept, module, environment);

            { Stella_Object i = null;
              PlIterator iter000 = instances;

              while (iter000.nextP()) {
                i = iter000.value;
                if (PLI.isTrueBinaryProposition(relation, i, value, module, environment)) {
                  return (i);
                }
              }
            }
            return (null);
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  static Cons helpGetTypes(LogicObject renamed_Object, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          { Cons derivabletypes = Stella.NIL;

            if ((environment == null) ||
                ((environment != null) &&
                 Stella.stringEqlP(environment.level, "INFERENCE"))) {
              derivabletypes = Logic.allTypes(renamed_Object);
            }
            else if ((environment != null) &&
                Stella.stringEqlP(environment.level, "ASSERTION")) {
              derivabletypes = Logic.allAssertedTypes(renamed_Object);
            }
            else if ((environment != null) &&
                Stella.stringEqlP(environment.level, "TAXONOMIC")) {
              derivabletypes = Logic.allTaxonomicTypes(renamed_Object);
            }
            return (derivabletypes);
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return all named concepts that <code>renamed_Object</code> belongs to.
   * @param renamed_Object
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getTypes(LogicObject renamed_Object, Module module, Environment environment) {
    return (PLI.consToPlIterator(PLI.helpGetTypes(renamed_Object, module, environment)));
  }

  /** Return most specific concepts that <code>renamed_Object</code> belongs to.
   * @param renamed_Object
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getDirectTypes(LogicObject renamed_Object, Module module, Environment environment) {
    return (PLI.consToPlIterator(Logic.mostSpecificNamedDescriptions(Cons.copyConsList(PLI.helpGetTypes(renamed_Object, module, environment)))));
  }

  /** Return propositions that satisfy <code>relation</code>.
   * Include propositions that satisfy subrelations of <code>relation</code>.
   * @param relation
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getRelationExtension(LogicObject relation, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          return (PLI.consToPlIterator(PLI.helpGetTrueExtensionMembers(((NamedDescription)(relation)), !((environment != null) &&
              Stella.stringEqlP(environment.level, "ASSERTION")))));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Return propositions that satisfy the relation named
   * <code>relationName</code>.  Include propositions that satisfy subrelations of the relation.
   * @param relationName
   * @param moduleName
   * @param environment
   * @return PlIterator
   */
  public static PlIterator sGetRelationExtension(String relationName, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);
      Stella_Object relation = PLI.safelyGetRelation(relationName, ((Module)(module)), environment);

      if (relation != null) {
        return (PLI.getRelationExtension(((LogicObject)(relation)), ((Module)(module)), environment));
      }
      else {
        return (PLI.EMPTY_PL_ITERATOR);
      }
    }
  }

  /** Return a module named <code>name</code> or NULL if no such module exists.
   * @param name
   * @param environment
   * @return Module
   */
  public static Module getModule(String name, Environment environment) {
    environment = environment;
    return (Stella.getStellaModule(name, false));
  }

  /** Return the module named <code>name</code> or raise a STELLA <code>noSuchContextException</code> if it doesn't exist.
   * @param name
   * @param environment
   * @return Module
   */
  public static Module getExistingModule(String name, Environment environment) {
    environment = environment;
    return (Stella.getStellaModule(name, true));
  }

  /** Return the module in which <code>renamed_Object</code> was created.
   * @param renamed_Object
   * @return Module
   */
  public static Module getHomeModule(LogicObject renamed_Object) {
    return (renamed_Object.homeModule());
  }

  /** Return all modules currently loaded into PowerLoom.  If <code>kbModulesOnlyP</code>
   * is <code>true</code>, then Stella modules that are used only for program code are
   * not included in the list.
   * @param kbModulesOnlyP
   * @return PlIterator
   */
  public static PlIterator getModules(boolean kbModulesOnlyP) {
    return (PLI.consToPlIterator(Stella.listModules(kbModulesOnlyP)));
  }

  /** Creates a new module <code>name</code> as a child of <code>parent</code>.  The flag
   * <code>caseSensitiveP</code> controls whether names read in this module will be
   * case sensitive or not.
   * @param name
   * @param parent
   * @param caseSensitiveP
   * @return Module
   */
  public static Module createModule(String name, Module parent, boolean caseSensitiveP) {
    { String fullName = ((parent != null) ? (parent.moduleFullName + "/" + name) : name);
      Symbol caseSensitiveSymbol = (caseSensitiveP ? Logic.SYM_STELLA_TRUE : Logic.SYM_STELLA_FALSE);

      return (Module.defineModule(fullName, Cons.list$(Cons.cons(PLI.KWD_CASE_SENSITIVEp, Cons.cons(caseSensitiveSymbol, Cons.cons(Stella.NIL, Stella.NIL))))));
    }
  }

  /** Creates a new module <code>name</code> as a child of <code>parentName</code>.  The flag
   * <code>caseSensitiveP</code> controls whether names read in this module will be
   * case sensitive or not.
   * @param name
   * @param parentName
   * @param caseSensitiveP
   * @param environment
   * @return Module
   */
  public static Module sCreateModule(String name, String parentName, boolean caseSensitiveP, Environment environment) {
    return (PLI.createModule(name, ((Module)(PLI.safelyGetModule(parentName, environment))), caseSensitiveP));
  }

  /** Set the current module to <code>module</code> and return it.
   * If <code>module</code> is <code>null</code>, then no switch is performed and the current
   * module is returned.
   * @param module
   * @return Module
   */
  public static Module changeModule(Module module) {
    if (module == null) {
      return (((Module)(Stella.$MODULE$.get())));
    }
    return (module.changeModule());
  }

  /** Set the current module to the module named <code>name</code>.
   * The return value is the module named <code>name</code> unless <code>name</code> is null or
   * the empty string.  In that case, the current module is returned.
   * If no module named <code>name</code> exists, a Stella <code>noSuchContextException</code>
   * is thrown.
   * @param name
   * @param environment
   * @return Module
   */
  public static Module sChangeModule(String name, Environment environment) {
    return (PLI.changeModule(((Module)(PLI.safelyGetModule(name, environment)))));
  }

  /** Destroy the contents of the module <code>module</code> as well as
   * the contents of all of its children, recursively.
   * @param module
   * @return Module
   */
  public static Module clearModule(Module module) {
    Stella.callClearModule(Cons.cons(module, Stella.NIL));
    return (module);
  }

  /** Destroy the contents of the module named <code>name</code>, as
   * well as the contents of all of its children, recursively.  If no module
   * named <code>name</code> exists, a Stella <code>noSuchContextException</code> is thrown.
   * @param name
   * @param environment
   * @return Module
   */
  public static Module sClearModule(String name, Environment environment) {
    { Context module = PLI.safelyGetModule(name, environment);

      Stella.callClearModule(Cons.cons(module, Stella.NIL));
      return (((Module)(module)));
    }
  }

  /** Return the modules that are immediate children of <code>module</code>.
   * @param module
   * @return PlIterator
   */
  public static PlIterator getChildModules(Module module) {
    { Cons directsubmodules = Stella.NIL;

      { Context child = null;
        Cons iter000 = module.childContexts.theConsList;
        Cons collect000 = null;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          child = ((Context)(iter000.value));
          if (Stella_Object.isaP(child, Logic.SGT_STELLA_MODULE)) {
            if (collect000 == null) {
              {
                collect000 = Cons.cons(child, Stella.NIL);
                if (directsubmodules == Stella.NIL) {
                  directsubmodules = collect000;
                }
                else {
                  Cons.addConsToEndOfConsList(directsubmodules, collect000);
                }
              }
            }
            else {
              {
                collect000.rest = Cons.cons(child, Stella.NIL);
                collect000 = collect000.rest;
              }
            }
          }
        }
      }
      return (PLI.consToPlIterator(directsubmodules));
    }
  }

  /** Return the modules that are immediate children of module <code>name</code>.
   * If no module named <code>name</code> exists, a Stella <code>noSuchContextException</code>
   * is thrown.
   * @param name
   * @param environment
   * @return PlIterator
   */
  public static PlIterator sGetChildModules(String name, Environment environment) {
    return (PLI.getChildModules(((Module)(PLI.safelyGetModule(name, environment)))));
  }

  /** Return the modules that are immediate parents of <code>module</code>.
   * @param module
   * @return PlIterator
   */
  public static PlIterator getParentModules(Module module) {
    return (PLI.listToPlIterator(module.parentModules));
  }

  /** Return the modules that are immediate parents of module <code>name</code>.
   * If no module named <code>name</code> exists, a Stella <code>noSuchContextException</code>
   * is thrown.
   * @param name
   * @param environment
   * @return PlIterator
   */
  public static PlIterator sGetParentModules(String name, Environment environment) {
    return (PLI.getParentModules(((Module)(PLI.safelyGetModule(name, environment)))));
  }

  /** Generates a name based on <code>prefix</code> with a number appended that
   * is not currently in use in <code>moduleD</code>  In a non-case-sensitive module, the returned
   * name will be all upper case (This latter feature may change!)
   * @param prefix
   * @param module
   * @param environment
   * @return String
   */
  public static String generateUniqueName(String prefix, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          module = ((Module)(Stella.$MODULE$.get()));
          if (!(module.caseSensitiveP ||
              Stella.allUpperCaseStringP(prefix))) {
            prefix = Native.stringUpcase(prefix);
          }
          return (Stella.yieldUniqueGensymName(prefix, module));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Returns the Stella keyword <code>name</code>, creating it if
   * necessary.  <code>name</code> is treated literally and case-sensitively.
   * This should generally not be necessary to do.
   * @param name
   * @return Keyword
   */
  public static Keyword createKeyword(String name) {
    return (((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule(name, ((Module)(Stella.$MODULE$.get())), Stella.KEYWORD_SYM))));
  }

  /** Returns the Stella symbol <code>name</code> visible in <code>module</code>,
   * creating it if necessary.  <code>name</code> is treated literally and ALWAYS case-sensitively,
   * even if <code>module</code> is case insensitive. This should generally not be necessary to do.
   * @param name
   * @param module
   * @param environment
   * @return Symbol
   */
  public static Symbol createSymbol(String name, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          module = ((Module)(Stella.$MODULE$.get()));
          return (Symbol.internSymbolInModule(name, module, false));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Create an object named <code>name</code> of type <code>concept</code> in the designated
   * module.  Both <code>name</code> and <code>concept</code> can be <code>null</code>.  If <code>name</code> is <code>null</code> then an
   * object will be created with a new, non-conflicting name based on the name of
   * <code>concept</code>, or system-generated if no concept is specified.  If <code>concept</code> is
   * <code>null</code>, then the object will be of type THING.  It is an error to create an
   * object with the same name as an existing object.
   * <p>
   * Note that the string can be a qualified name, in which case the object
   * will be created in the module specified, but with a name as determined
   * by the qualified name.  Vertical bars in the name string are interpreted
   * as Stella escape characters.
   * <p>
   * Note that because names in modules that are not case-sensitive are
   * canonicalized, the name of the returned object may not match <code>name</code>
   * exactly.
   * <p>
   * Return the object.
   * @param name
   * @param concept
   * @param module
   * @param environment
   * @return LogicObject
   */
  public static LogicObject createObject(String name, LogicObject concept, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          module = ((Module)(Stella.$MODULE$.get()));
          { LogicObject renamed_Object = null;
            Symbol nameSymbol = null;
            Surrogate objectSurrogate = null;

            if (name != null) {
              nameSymbol = ((Symbol)(Stella.internStellaName(name)));
            }
            else if (concept != null) {
              nameSymbol = Symbol.internSymbol(PLI.getShortName(concept));
              nameSymbol = Symbol.internSymbolInModule(PLI.generateUniqueName(nameSymbol.symbolName, ((Module)(nameSymbol.homeContext)), null), ((Module)(nameSymbol.homeContext)), true);
            }
            else {
              nameSymbol = Symbol.internSymbolInModule(PLI.generateUniqueName("I", null, null), module, true);
            }
            objectSurrogate = Surrogate.lookupSurrogateInModule(nameSymbol.symbolName, ((Module)(nameSymbol.homeContext)), false);
            if (objectSurrogate == null) {
              objectSurrogate = Surrogate.internSurrogateInModule(nameSymbol.symbolName, ((Module)(nameSymbol.homeContext)), false);
            }
            renamed_Object = ((LogicObject)(Logic.helpCreateLogicInstance(objectSurrogate, null)));
            if (concept != null) {
              if (PLI.assertUnaryProposition(concept, renamed_Object, module, environment) != null) {
                return (renamed_Object);
              }
              else {
                return (null);
              }
            }
            return (renamed_Object);
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Create an object named <code>name</code> of type <code>conceptName</code> in the designated
   * module.  Both <code>name</code> and <code>conceptName</code> can be null strings.  If <code>name</code> is a null string
   * then an object will be created with a new, non-conflicting name based on <code>conceptName</code>, or
   * system-generated if no concept nameis specified.  If <code>conceptName</code> is the null string, then
   * the object will be of type THING.
   * <p>
   * A module name of <code>null</code> or the empty string refers to the current module. 
   * If no module can be found with the name <code>moduleName</code>, then a Stella 
   * <code>noSuchContextException</code> is thrown.
   * <p>
   * Note that because names in modules that are not case-sensitive are canonicalized,
   * the name of the returned object may not match <code>name</code> exactly.
   * <p>
   * Return the object.
   * @param name
   * @param conceptName
   * @param moduleName
   * @param environment
   * @return LogicObject
   */
  public static LogicObject sCreateObject(String name, String conceptName, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);

      return (PLI.createObject(name, ((LogicObject)(PLI.safelyGetConcept(conceptName, ((Module)(module)), environment))), ((Module)(module)), environment));
    }
  }

  /** Create a concept named <code>name</code> in the designated <code>module</code>, with the
   * designated <code>parent</code> superconcept (which can be left undefined).  Additional
   * superconcepts can be added via assertions of the <code>subsetOf</code> relation.  Note
   * that a specified <code>parent</code> concept needs to be created separately.
   * <p>
   * Note that because names in modules that are not case-sensitive are canonicalized,
   * the name of the returned object may not match <code>name</code> exactly.
   * @param name
   * @param parent
   * @param module
   * @param environment
   * @return LogicObject
   */
  public static LogicObject createConcept(String name, LogicObject parent, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          return (Logic.callDefconcept(Cons.cons(Stella.internStellaName(name), (((parent != null) ? Cons.list$(Cons.cons(PLI.KWD_SUBSET_OF, Cons.cons(Logic.objectName(parent), Cons.cons(Stella.NIL, Stella.NIL)))) : Stella.NIL)).concatenate(Stella.NIL, Stella.NIL))));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Create a concept named <code>name</code> in the designated module, with
   * with the concept named <code>parentName</code> as superconcept (which can be left
   * undefined).  Additional superconcepts can be added via assertions of the
   * <code>subsetOf</code> relation.  Note that a specified parent concept needs to be
   * created separately.
   * <p>
   * A module name of <code>null</code> or the empty string refers to the current module. 
   * If no module can be found with the name <code>moduleName</code>, then a Stella 
   * <code>noSuchContextException</code> is thrown.
   * <p>
   * Note that because names in modules that are not case-sensitive are canonicalized,
   * the name of the returned object may not match <code>name</code> exactly.
   * @param name
   * @param parentName
   * @param moduleName
   * @param environment
   * @return LogicObject
   */
  public static LogicObject sCreateConcept(String name, String parentName, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);

      return (PLI.createConcept(name, ((LogicObject)(PLI.safelyGetConcept(parentName, ((Module)(module)), environment))), ((Module)(module)), environment));
    }
  }

  /** Create a relation named <code>name</code> with arity <code>arity</code> in the
   * designated module.  Domain and range information can be added via assertions
   * of <code>nthDomain</code> (or <code>domain</code> and <code>range</code>) relations.
   * <p>
   * Note that because names in modules that are not case-sensitive are canonicalized,
   * the name of the returned object may not match <code>name</code> exactly.
   * @param name
   * @param arity
   * @param module
   * @param environment
   * @return LogicObject
   */
  public static LogicObject createRelation(String name, int arity, Module module, Environment environment) {
    if (!(arity > 0)) {
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        { Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();

          try {
            Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, true);
            stream000.nativeStream.println("PARSING ERROR: Relations must have arity of at least 1.");
            Logic.helpSignalPropositionError(stream000, Logic.KWD_ERROR);

          } finally {
            Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
          }
        }
        throw ((ParsingError)(ParsingError.newParsingError(stream000.theStringReader()).fillInStackTrace()));
      }
    }
    { Cons args = Stella.NIL;

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          environment = environment;
          synchronized (Logic.$POWERLOOM_LOCK$) {
            module = ((Module)(Stella.$MODULE$.get()));
            { int i = Stella.NULL_INTEGER;
              int iter000 = 0;
              int upperBound000 = arity - 1;
              Cons collect000 = null;

              for (;iter000 <= upperBound000; iter000 = iter000 + 1) {
                i = iter000;
                if (collect000 == null) {
                  {
                    collect000 = Cons.cons(Logic.yieldSystemDefinedParameterName(i, module), Stella.NIL);
                    if (args == Stella.NIL) {
                      args = collect000;
                    }
                    else {
                      Cons.addConsToEndOfConsList(args, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000.rest = Cons.cons(Logic.yieldSystemDefinedParameterName(i, module), Stella.NIL);
                    collect000 = collect000.rest;
                  }
                }
              }
            }
            return (Logic.callDefrelation(Cons.cons(Stella.internStellaName(name), Cons.cons(args, Stella.NIL))));
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Create a relation named <code>name</code> with arity <code>arity</code> in the
   * designated module.  Domain and range information can be added via assertions
   * of <code>nthDomain</code> (or <code>domain</code> and <code>range</code>) relations.
   * <p>
   * A module name of <code>null</code> or the empty string refers to the current module. 
   * If no module can be found with the name <code>moduleName</code>, then a Stella 
   * <code>noSuchContextException</code> is thrown.
   * <p>
   * Note that because names in modules that are not case-sensitive are canonicalized,
   * the name of the returned object may not match <code>name</code> exactly.
   * @param name
   * @param arity
   * @param moduleName
   * @param environment
   * @return LogicObject
   */
  public static LogicObject sCreateRelation(String name, int arity, String moduleName, Environment environment) {
    return (PLI.createRelation(name, arity, ((Module)(PLI.safelyGetModule(moduleName, environment))), environment));
  }

  /** Create a function named <code>name</code> with arity <code>arity</code>  in the designated 
   * <code>module</code>.  Domain and range information can be added via assertions of
   * <code>nthDomain</code> (or <code>domain</code> and <code>range</code>) relations.
   * <p>
   * Note that because names in modules that are not case-sensitive are canonicalized,
   * the name of the returned object may not match <code>name</code> exactly.
   * @param name
   * @param arity
   * @param module
   * @param environment
   * @return LogicObject
   */
  public static LogicObject createFunction(String name, int arity, Module module, Environment environment) {
    if (!(arity > 0)) {
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        { Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();

          try {
            Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, true);
            stream000.nativeStream.println("PARSING ERROR: Functions must have arity of at least 1.");
            Logic.helpSignalPropositionError(stream000, Logic.KWD_ERROR);

          } finally {
            Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
          }
        }
        throw ((ParsingError)(ParsingError.newParsingError(stream000.theStringReader()).fillInStackTrace()));
      }
    }
    { Cons args = Stella.NIL;

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          environment = environment;
          synchronized (Logic.$POWERLOOM_LOCK$) {
            module = ((Module)(Stella.$MODULE$.get()));
            { int i = Stella.NULL_INTEGER;
              int iter000 = 0;
              int upperBound000 = arity - 1;
              Cons collect000 = null;

              for (;iter000 <= upperBound000; iter000 = iter000 + 1) {
                i = iter000;
                if (collect000 == null) {
                  {
                    collect000 = Cons.cons(Logic.yieldSystemDefinedParameterName(i, module), Stella.NIL);
                    if (args == Stella.NIL) {
                      args = collect000;
                    }
                    else {
                      Cons.addConsToEndOfConsList(args, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000.rest = Cons.cons(Logic.yieldSystemDefinedParameterName(i, module), Stella.NIL);
                    collect000 = collect000.rest;
                  }
                }
              }
            }
            return (Logic.callDeffunction(Cons.cons(Stella.internStellaName(name), Cons.cons(args, Stella.NIL))));
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Create a function named <code>name</code> with arity <code>arity</code> in the designated 
   * module.  Domain and range information can be added via assertions of
   * <code>domain</code>, <code>nthDomain</code> and <code>range</code> relations.
   * <p>
   * A module name of <code>null</code> or the empty string refers to the current module. 
   * If no module can be found with the name <code>moduleName</code>, then a Stella 
   * <code>noSuchContextException</code> is thrown.
   * <p>
   * Note that because names in modules that are not case-sensitive are canonicalized,
   * the name of the returned object may not match <code>name</code> exactly.
   * @param name
   * @param arity
   * @param moduleName
   * @param environment
   * @return LogicObject
   */
  public static LogicObject sCreateFunction(String name, int arity, String moduleName, Environment environment) {
    return (PLI.createFunction(name, arity, ((Module)(PLI.safelyGetModule(moduleName, environment))), environment));
  }

  /** Register <code>name</code> as a function name in <code>module</code> which will invoke the
   * native code procedure described by <code>functionReferenceD</code>  The <code>name</code>
   * is a fully-qualified name which will be interpreted by the normal
   * rules for reading names in PowerLoom.  The function must conform
   * to the signature for specialist functions.
   * <p>
   * The exact form of <code>functionReference</code> depends on the underlying
   * programming language.  The following type mappings are used:
   *           C++:  
   *   Common Lisp:  FUNCTION   (result of #' or (FUNCTION ...))
   *          Java:  java.lang.reflect.Method
   * @param name
   * @param functionReference
   * @param module
   * @param environment
   */
  public static void registerSpecialistFunction(String name, java.lang.reflect.Method functionReference, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          Logic.registerSpecialistFunction(name, functionReference);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Register <code>name</code> as a function name in the module named <code>moduleName</code>.
   * This function will the native code named <code>nativeName</code>.  The <code>name</code>
   * is a fully-qualified name which will be interpreted by the normal
   * rules for reading names in PowerLoom.  The <code>nativeName</code> will be
   * processed in a manner that depends on the underlying programming
   * language.  The following type mappings are used:
   *           C++:  Not available.  Error signaled.
   *   Common Lisp:  The native-name is read by READ-FROM-STRING and then
   *                 the SYMBOL-FUNCTION is taken.
   *          Java:  A fully package-qualified name is required.  It is
   *                 looked up using the Reflection tools.
   * The function found must conform to the signature for specialist functions.
   * @param name
   * @param nativeName
   * @param moduleName
   * @param environment
   */
  public static void sRegisterSpecialistFunction(String name, String nativeName, String moduleName, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, null);
        Native.setSpecial(Stella.$CONTEXT$, null);
        { Context temp000 = PLI.safelyGetModule(moduleName, environment);

          Native.setSpecial(Stella.$MODULE$, ((temp000 != null) ? ((Module)(temp000)) : ((Module)(Stella.$MODULE$.get()))));
        }
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          Logic.registerSpecialistFunctionName(name, nativeName);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Register <code>name</code> as a function name in <code>module</code> which will invoke the
   * native code procedure described by <code>functionReferenceD</code>  The <code>name</code>
   * is a fully-qualified name which will be interpreted by the normal
   * rules for reading names in PowerLoom.  The function must conform
   * to the signature for computation functions used by the computation
   * specialist.  Arity specifies the number of arguments the computation
   * accepts.
   * <p>
   * The exact form of <code>functionReference</code> depends on the underlying
   * programming language.  The following type mappings are used:
   *           C++:  cpp_function_code (a pointer to the function code)
   *   Common Lisp:  FUNCTION   (result of #' or (FUNCTION ...))
   *          Java:  java.lang.reflect.Method
   * @param name
   * @param functionReference
   * @param arity
   * @param module
   * @param environment
   */
  public static void registerComputationFunction(String name, java.lang.reflect.Method functionReference, int arity, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          Logic.registerComputationFunction(name, functionReference, arity);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Register <code>name</code> as a function name in the module named <code>moduleName</code>.
   * This function will the native code named <code>nativeName</code>.  The <code>name</code>
   * is a fully-qualified name which will be interpreted by the normal
   * rules for reading names in PowerLoom.  The <code>nativeName</code> will be
   * processed in a manner that depends on the underlying programming
   * language.  The following type mappings are used:
   *           C++:  Not available.  Error signaled.
   *   Common Lisp:  The native-name is read by READ-FROM-STRING and then
   *                 the SYMBOL-FUNCTION is taken.
   *          Java:  A fully package-qualified name is required.  It is
   *                 looked up using the Reflection tools.
   * The function found must conform to the signature for computation functions.
   * Arity specifies the number of arguments the computation accepts.
   * @param name
   * @param nativeName
   * @param arity
   * @param moduleName
   * @param environment
   */
  public static void sRegisterComputationFunction(String name, String nativeName, int arity, String moduleName, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, null);
        Native.setSpecial(Stella.$CONTEXT$, null);
        { Context temp000 = PLI.safelyGetModule(moduleName, environment);

          Native.setSpecial(Stella.$MODULE$, ((temp000 != null) ? ((Module)(temp000)) : ((Module)(Stella.$MODULE$.get()))));
        }
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          Logic.registerComputationFunctionName(name, nativeName, arity);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Create a logical term that denotes a list containing <code>members</code> in
   * <code>module</code> using <code>environment</code>.  Useful for passing lists as arguments
   * to parameterized queries.
   * @param members
   * @param module
   * @param environment
   * @return LogicObject
   */
  public static LogicObject createEnumeratedList(Cons members, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          { List self000 = List.newList();

            self000.theConsList = members;
            { Skolem value000 = Logic.createLogicalList(self000);

              return (value000);
            }
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Create a logical term that denotes the enumerated set containing <code>members</code>
   * in <code>module</code> using <code>environment</code>.
   * @param members
   * @param module
   * @param environment
   * @return LogicObject
   */
  public static LogicObject createEnumeratedSet(Cons members, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          { List self000 = List.newList();

            self000.theConsList = members;
            { Skolem value000 = Logic.createEnumeratedSet(self000);

              return (value000);
            }
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Delete the object <code>renamed_Object</code>, retracting all facts attached to it.
   * @param renamed_Object
   */
  public static void destroyObject(Stella_Object renamed_Object) {
    synchronized (Logic.$POWERLOOM_LOCK$) {
      Logic.destroyObject(renamed_Object);
    }
  }

  /** Delete the object named <code>objectName</code>, retracting all facts
   * attached to it.
   * <p>
   * A module name of <code>null</code> or the empty string refers to the current module. 
   * If no module can be found with the name <code>moduleName</code>, then a Stella 
   * <code>noSuchContextException</code> is thrown.
   * @param objectName
   * @param moduleName
   * @param environment
   */
  public static void sDestroyObject(String objectName, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);
      Stella_Object renamed_Object = PLI.safelyGetObject(objectName, ((Module)(module)), environment);

      if (renamed_Object != null) {
        PLI.destroyObject(renamed_Object);
      }
    }
  }

  /** Assert that the proposition (<code>relation</code> <code>arg</code>) is TRUE in <code>module</code>.  Return the asserted proposition.
   * @param relation
   * @param arg
   * @param module
   * @param environment
   * @return Proposition
   */
  public static Proposition assertUnaryProposition(LogicObject relation, Stella_Object arg, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          if (Logic.classP(relation)) {
            return (Logic.assertIsaProposition(arg, relation.surrogateValueInverse));
          }
          else {
            return (LogicObject.assertProperty(((LogicObject)(arg)), relation.surrogateValueInverse));
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Assert that the proposition (<code>relation</code> <code>arg</code> <code>value</code>) is TRUE
   * in <code>module</code>.  Return the asserted proposition.
   * @param relation
   * @param arg
   * @param value
   * @param module
   * @param environment
   * @return Proposition
   */
  public static Proposition assertBinaryProposition(LogicObject relation, Stella_Object arg, Stella_Object value, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          return (Logic.assertBinaryValue(relation.surrogateValueInverse, arg, value));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Assert that the proposition represented by the list <code>RelationAndArguments</code> satisfies
   * the relation <code>relation</code>.
   * @param relationAndArguments
   * @param module
   * @param environment
   * @return Proposition
   */
  public static Proposition assertNaryProposition(Stella_Object relationAndArguments, Module module, Environment environment) {
    { Cons list = PLI.sequenceToConsList(relationAndArguments);
      NamedDescription relation = ((NamedDescription)(list.value));
      Surrogate relationsurrogate = relation.surrogateValueInverse;
      Cons arguments = list.rest;

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          environment = environment;
          synchronized (Logic.$POWERLOOM_LOCK$) {
            return (Logic.assertTuple(relationsurrogate, arguments));
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Retract that the proposition (<code>relation</code> <code>arg</code>) is TRUE in <code>module</code>.  Return the asserted proposition.
   * @param relation
   * @param arg
   * @param module
   * @param environment
   * @return Proposition
   */
  public static Proposition retractUnaryProposition(LogicObject relation, Stella_Object arg, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          if (Logic.classP(relation)) {
            return (Logic.retractIsaProposition(arg, relation.surrogateValueInverse));
          }
          else {
            return (LogicObject.retractProperty(((LogicObject)(arg)), relation.surrogateValueInverse));
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Retract that the proposition (<code>relation</code> <code>arg</code> <code>value</code>) is TRUE
   * in <code>module</code>.  Return the asserted proposition.
   * @param relation
   * @param arg
   * @param value
   * @param module
   * @param environment
   * @return Proposition
   */
  public static Proposition retractBinaryProposition(LogicObject relation, Stella_Object arg, Stella_Object value, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          return (Logic.retractBinaryValue(relation.surrogateValueInverse, arg, value));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Retract the proposition that <code>arguments</code> satisfies
   * the relation <code>relation</code>.
   * @param relationAndArguments
   * @param module
   * @param environment
   * @return Proposition
   */
  public static Proposition retractNaryProposition(Stella_Object relationAndArguments, Module module, Environment environment) {
    { Cons list = PLI.sequenceToConsList(relationAndArguments);
      NamedDescription relation = ((NamedDescription)(list.value));
      Surrogate relationsurrogate = relation.surrogateValueInverse;
      Cons arguments = list.rest;

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          environment = environment;
          synchronized (Logic.$POWERLOOM_LOCK$) {
            return (Logic.updateTuple(relationsurrogate, arguments, Logic.KWD_RETRACT_TRUE));
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Assert that the proposition <code>proposition</code> is true in <code>module</code>.
   * Return the asserted proposition.
   * @param proposition
   * @param module
   * @param environment
   * @return Proposition
   */
  public static Proposition assertProposition(Proposition proposition, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          Proposition.helpUpdateTopLevelProposition(proposition, Logic.KWD_ASSERT_TRUE);
          return (proposition);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Assert that the logical sentence <code>sentence</code> is true in the module
   * named <code>moduleName</code>.  A module name of <code>null</code> or the empty string refers to the
   * current module.  If no module can be found with the name <code>moduleName</code>,
   * then a Stella <code>noSuchContextException</code> is thrown.
   * <p>
   * Return an iterator of the propositions resulting from sentence.
   * @param sentence
   * @param moduleName
   * @param environment
   * @return PlIterator
   */
  public static PlIterator sAssertProposition(String sentence, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);
      PlIterator propositions = null;
      PlIterator returnValue = null;

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, ((module != null) ? ((Module)(module)) : ((Module)(Stella.$MODULE$.get()))));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          environment = environment;
          synchronized (Logic.$POWERLOOM_LOCK$) {
            propositions = PLI.sConceive(sentence, moduleName, environment);
            returnValue = PLI.consToPlIterator(propositions.cursor);
            { Proposition proposition = null;
              PlIterator iter000 = propositions;

              while (iter000.nextP()) {
                proposition = ((Proposition)(iter000.value));
                Proposition.helpUpdateTopLevelProposition(proposition, Logic.KWD_ASSERT_TRUE);
              }
            }
            return (returnValue);
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Retract the truth of the proposition <code>proposition</code> in <code>module</code>.
   * Return the retracted proposition.
   * @param proposition
   * @param module
   * @param environment
   * @return Proposition
   */
  public static Proposition retractProposition(Proposition proposition, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          Proposition.helpUpdateTopLevelProposition(proposition, Logic.KWD_RETRACT_TRUE);
          return (proposition);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Retract the truth of the logical sentence <code>sentence</code> in the module named
   * <code>moduleName</code>.  A module name of <code>null</code> or the empty string refers to the
   * current module.  If no module can be found with the name <code>moduleName</code>,
   * then a Stella <code>noSuchContextException</code> is thrown.
   * <p>
   * Return an iterator of the retracted propositions resulting from sentence.
   * @param sentence
   * @param moduleName
   * @param environment
   * @return PlIterator
   */
  public static PlIterator sRetractProposition(String sentence, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);
      PlIterator propositions = null;
      PlIterator returnValue = null;

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, ((module != null) ? ((Module)(module)) : ((Module)(Stella.$MODULE$.get()))));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          environment = environment;
          synchronized (Logic.$POWERLOOM_LOCK$) {
            propositions = PLI.sConceive(sentence, moduleName, environment);
            returnValue = PLI.consToPlIterator(propositions.cursor);
            { Proposition proposition = null;
              PlIterator iter000 = propositions;

              while (iter000.nextP()) {
                proposition = ((Proposition)(iter000.value));
                Proposition.helpUpdateTopLevelProposition(proposition, Logic.KWD_RETRACT_TRUE);
              }
            }
            return (returnValue);
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Create one or more proposition objects from the sentence <code>sentence</code>
   * in the  module <code>module</code>.  Return an iterator of the propositions.
   * If any of the new propositions has the same structure as an already existing
   * proposition, an automatic check for duplicates will return the pre-existing
   * proposition.  Multiple propositions may be returned for a single sentence
   * because of normalization of equivalences, conjunctions, etc.
   * <p>
   * Signals a <code>Proposition_Error</code> if PowerLoom could not conceive <code>sentence</code>.
   * @param sentence
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator conceive(Stella_Object sentence, Module module, Environment environment) {
    if (sentence == null) {
      return (null);
    }
    else {
      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          environment = environment;
          synchronized (Logic.$POWERLOOM_LOCK$) {
            { Stella_Object propositions = Logic.conceiveFormula(sentence);

              if (propositions == null) {
                { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

                  { Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();

                    try {
                      Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, true);
                      stream000.nativeStream.println("ERROR: Failed to conceive `" + sentence + "'.");
                      Logic.helpSignalPropositionError(stream000, Logic.KWD_ERROR);

                    } finally {
                      Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
                    }
                  }
                  throw ((PropositionError)(PropositionError.newPropositionError(stream000.theStringReader()).fillInStackTrace()));
                }
              }
              { Surrogate testValue000 = Stella_Object.safePrimaryType(propositions);

                if (Surrogate.subtypeOfP(testValue000, Logic.SGT_LOGIC_PROPOSITION)) {
                  { Proposition propositions000 = ((Proposition)(propositions));

                    return (PLI.consToPlIterator(Cons.cons(propositions000, Stella.NIL)));
                  }
                }
                else if (testValue000 == Logic.SGT_STELLA_CONS) {
                  { Cons propositions000 = ((Cons)(propositions));

                    return (PLI.consToPlIterator(propositions000));
                  }
                }
                else {
                  { OutputStringStream stream001 = OutputStringStream.newOutputStringStream();

                    { Object old$PrintreadablyP$001 = Stella.$PRINTREADABLYp$.get();

                      try {
                        Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, true);
                        stream001.nativeStream.println("ERROR: Formula is not a sentence: `" + sentence + "'.");
                        Logic.helpSignalPropositionError(stream001, Logic.KWD_ERROR);

                      } finally {
                        Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$001);
                      }
                    }
                    throw ((PropositionError)(PropositionError.newPropositionError(stream001.theStringReader()).fillInStackTrace()));
                  }
                }
              }
            }
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Create one or more proposition objects from the sentence <code>sentence</code>
   * in the  module named <code>moduleName</code>.  Return an iterator of the propositions.
   * If any of the new propositions has the same structure as an already existing
   * proposition, an automatic check for duplicates will return the pre-existing
   * proposition.  Multiple propositions may be returned for a single sentence
   * because of normalization of equivalences, conjunctions, etc.
   * <p>
   * A module name of <code>null</code> or the empty string refers to the current module.
   * If no module can be found with the name <code>moduleName</code>, then a Stella
   * <code>No_Such_Context_Exception</code> is thrown.
   * <p>
   * Signals a <code>Proposition_Error</code> if PowerLoom could not conceive <code>sentence</code>.
   * @param sentence
   * @param moduleName
   * @param environment
   * @return PlIterator
   */
  public static PlIterator sConceive(String sentence, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, ((module != null) ? ((Module)(module)) : ((Module)(Stella.$MODULE$.get()))));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          environment = environment;
          synchronized (Logic.$POWERLOOM_LOCK$) {
            module = ((Module)(Stella.$MODULE$.get()));
            return (PLI.conceive(Stella.readSExpressionFromString(sentence), ((Module)(module)), environment));
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Return rules attached to the concept/relation <code>relation</code>
   * in either antecedent or consequent position.
   * @param relation
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator getRules(LogicObject relation, Module module, Environment environment) {
    if (relation == null) {
      return (PLI.EMPTY_PL_ITERATOR);
    }
    else {
      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          environment = environment;
          synchronized (Logic.$POWERLOOM_LOCK$) {
            return (PLI.consToPlIterator(Logic.callGetRules(relation)));
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Return rules attached to the concept/relation named
   * <code>relationName</code> found in the module named <code>moduleName</code>.
   * A module name of <code>null</code> or the empty string refers to the current module.
   * If no module can be found with the name <code>moduleName</code>, then a Stella
   * <code>No_Such_Context_Exception</code> is thrown.
   * @param relationName
   * @param moduleName
   * @param environment
   * @return PlIterator
   */
  public static PlIterator sGetRules(String relationName, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);
      Stella_Object relation = PLI.safelyGetRelation(relationName, ((Module)(module)), environment);

      return (PLI.getRules(((LogicObject)(relation)), ((Module)(module)), environment));
    }
  }

  /** Print rules attached to the concept/relation named <code>name</code>.
   * A module name of <code>null</code> or the empty string refers to the
   * current module.  If no module can be found with the name <code>moduleName</code>,
   * then a Stella <code>noSuchContextException</code> is thrown.
   * @param name
   * @param stream
   * @param moduleName
   * @param environment
   */
  public static void sPrintRules(String name, OutputStream stream, String moduleName, Environment environment) {
    if (stream == null) {
      stream = Stella.STANDARD_OUTPUT;
    }
    { Proposition rule = null;
      PlIterator iter000 = PLI.sGetRules(name, moduleName, environment);

      while (iter000.nextP()) {
        rule = ((Proposition)(iter000.value));
        Logic.printLogicalForm(rule, stream);
        {
          stream.nativeStream.println("");
          stream.nativeStream.println();
        }
;
      }
    }
  }

  /** Run forward inference rules in module <code>module</code> which defaults
   * to the current module.  See <code>runForwardRules</code> command for more information.
   * @param module
   * @param localP
   * @param forceP
   */
  public static void runForwardRules(Stella_Object module, boolean localP, boolean forceP) {
    if (module == null) {
      module = ((Module)(Stella.$MODULE$.get()));
    }
    if (module != null) {
      Logic.callRunForwardRules(((Context)(module)), localP, forceP);
    }
  }

  /** Return the arity of the relation <code>relation</code>.
   * @param relation
   * @return int
   */
  public static int getArity(LogicObject relation) {
    if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(relation), Logic.SGT_LOGIC_DESCRIPTION)) {
      { Description relation000 = ((Description)(relation));

        return (relation000.arity());
      }
    }
    else {
      return (0);
    }
  }

  /** Return the arity of the relation named <code>relationName</code>.
   * <p>
   *  A module name of <code>null</code> or the empty string refers to the
   * current module.  If no module can be found with the name <code>moduleName</code>,
   * then a Stella <code>noSuchContextException</code> is thrown.
   * @param relationName
   * @param moduleName
   * @param environment
   * @return int
   */
  public static int sGetArity(String relationName, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);
      Stella_Object relation = PLI.safelyGetRelation(relationName, ((Module)(module)), environment);

      if (relation != null) {
        return (PLI.getArity(((LogicObject)(relation))));
      }
      else {
        return (Stella.NULL_INTEGER);
      }
    }
  }

  /** Return the type (a concept) for the first argument to the binary
   * relation <code>relation</code>.
   * @param relation
   * @return LogicObject
   */
  public static LogicObject getDomain(LogicObject relation) {
    if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(relation), Logic.SGT_LOGIC_NAMED_DESCRIPTION)) {
      { NamedDescription relation000 = ((NamedDescription)(relation));

        return (PLI.getNthDomain(relation000, 0));
      }
    }
    else {
      return (null);
    }
  }

  /** Return the type (concept) for the first argument to the binary
   * relation <code>relationName</code>.
   * <p>
   * A module name of <code>null</code> or the empty string refers to the
   * current module.  If no module can be found with the name <code>moduleName</code>,
   * then a Stella <code>noSuchContextException</code> is thrown.
   * @param relationName
   * @param moduleName
   * @param environment
   * @return LogicObject
   */
  public static LogicObject sGetDomain(String relationName, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);
      Stella_Object relation = PLI.safelyGetRelation(relationName, ((Module)(module)), environment);

      if (relation != null) {
        return (PLI.getDomain(((LogicObject)(relation))));
      }
      else {
        return (null);
      }
    }
  }

  /** Return the type (a concept) for fillers of the binary relation
   * <code>relation</code>.
   * @param relation
   * @return LogicObject
   */
  public static LogicObject getRange(LogicObject relation) {
    if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(relation), Logic.SGT_LOGIC_NAMED_DESCRIPTION)) {
      { NamedDescription relation000 = ((NamedDescription)(relation));

        return (PLI.getNthDomain(relation000, 1));
      }
    }
    else {
      return (null);
    }
  }

  /** Return the type (a concept) for fillers of the binary relation
   * <code>relationName</code>.
   * <p>
   * A module name of <code>null</code> or the empty string refers to the
   * current module.  If no module can be found with the name <code>moduleName</code>,
   * then a Stella <code>noSuchContextException</code> is thrown.
   * @param relationName
   * @param moduleName
   * @param environment
   * @return LogicObject
   */
  public static LogicObject sGetRange(String relationName, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);
      Stella_Object relation = PLI.safelyGetRelation(relationName, ((Module)(module)), environment);

      if (relation != null) {
        return (PLI.getRange(((LogicObject)(relation))));
      }
      else {
        return (null);
      }
    }
  }

  /** Return the type (a concept) for the the nth argument of the
   * relation <code>relation</code>.  Counting starts at zero.  NOTE: if there are multiple
   * <code>nthDomain</code> propositions for <code>relation</code>, this arbitrarily returns one of them;
   * it does not look for the most specific one (which might have to be created).
   * @param relation
   * @param n
   * @return LogicObject
   */
  public static LogicObject getNthDomain(LogicObject relation, int n) {
    if (Logic.classP(relation)) {
      return (((n == 0) ? relation : null));
    }
    if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(relation), Logic.SGT_LOGIC_NAMED_DESCRIPTION)) {
      { NamedDescription relation000 = ((NamedDescription)(relation));

        if ((n >= 0) &&
            (n < relation000.ioVariableTypes.length())) {
          { Proposition domainprop = ((Proposition)(PLI.helpGetPropositions(((LogicObject)(PLI.SGT_PL_KERNEL_KB_NTH_DOMAIN.surrogateValue)), Cons.cons(relation000, Cons.cons(IntegerWrapper.wrapInteger(n), Cons.cons(null, Stella.NIL))), 1, null, null).value));

            if (domainprop != null) {
              return (((LogicObject)((domainprop.arguments.theArray)[(domainprop.arguments.length() - 1)])));
            }
          }
        }
      }
    }
    else {
    }
    return (null);
  }

  /** Return the type (a concept) for the nth argument of the relation
   * named <code>relationName</code>.  Counting starts at zero.
   * <p>
   * A module name of <code>null</code> or the empty string refers to the
   * current module.  If no module can be found with the name <code>moduleName</code>,
   * then a Stella <code>noSuchContextException</code> is thrown.
   * @param relationName
   * @param n
   * @param moduleName
   * @param environment
   * @return LogicObject
   */
  public static LogicObject sGetNthDomain(String relationName, int n, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);
      Stella_Object relation = PLI.safelyGetRelation(relationName, ((Module)(module)), environment);

      if (relation != null) {
        return (PLI.getNthDomain(((LogicObject)(relation)), n));
      }
      else {
        return (null);
      }
    }
  }

  /** Read logic commands from the file named <code>filename</code> and evaluate them.
   * See <code>load</code> command help for more information.
   * @param filename
   * @param environment
   */
  public static void load(String filename, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((((Module)(Stella.$MODULE$.get())) != null) ? ((Module)(Stella.$MODULE$.get())) : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          Logic.load(filename, Stella.NIL);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Read logic commands from the file named <code>filename</code> and evaluate them.
   * Binds the <code>load</code> command's :module option to <code>module</code>.  See <code>load</code> command help for more information.
   * @param filename
   * @param module
   * @param environment
   */
  public static void loadInModule(String filename, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          module = ((Module)(Stella.$MODULE$.get()));
          Logic.load(filename, Cons.cons(Logic.KWD_MODULE, Cons.cons(module, Stella.NIL)));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Read logic commands from the STELLA stream <code>stream</code> and evaluate them.
   * See <code>load</code> command help for more information.
   * @param stream
   * @param environment
   */
  public static void loadStream(InputStream stream, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((((Module)(Stella.$MODULE$.get())) != null) ? ((Module)(Stella.$MODULE$.get())) : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          Logic.loadStream(stream, Stella.NIL);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Read logic commands from the STELLA stream <code>stream</code> and evaluate them.
   * Binds the <code>load</code> command's :module option to <code>module</code>.  See <code>load</code> command help for more information.
   * @param stream
   * @param module
   * @param environment
   */
  public static void loadStreamInModule(InputStream stream, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          module = ((Module)(Stella.$MODULE$.get()));
          Logic.loadStream(stream, Cons.cons(Logic.KWD_MODULE, Cons.cons(module, Stella.NIL)));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Read logic commands from the native input stream <code>stream</code> and evaluate them.
   * Assumes <code>stream</code> is a line-buffered stream which is a safe compromise but does
   * not generate the best efficiency for block-buffered streams such as files.
   * See <code>load</code> command help for more information.
   * @param stream
   * @param environment
   */
  public static void loadNativeStream(edu.isi.stella.javalib.NativeInputStream stream, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((((Module)(Stella.$MODULE$.get())) != null) ? ((Module)(Stella.$MODULE$.get())) : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          { InputStream self000 = InputStream.newInputStream();

            self000.nativeStream = stream;
            Logic.loadStream(self000, Stella.NIL);
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Read logic commands from the native input stream <code>stream</code> and evaluate them.
   * Assumes <code>stream</code> is a line-buffered stream which is a safe compromise but does
   * not generate the best efficiency for block-buffered streams such as files.
   * Binds the <code>load</code> command's :module option to <code>module</code>.  See <code>load</code> command help for more information.
   * @param stream
   * @param module
   * @param environment
   */
  public static void loadNativeStreamInModule(edu.isi.stella.javalib.NativeInputStream stream, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          module = ((Module)(Stella.$MODULE$.get()));
          { InputStream self000 = InputStream.newInputStream();

            self000.nativeStream = stream;
            Logic.loadStream(self000, Cons.cons(Logic.KWD_MODULE, Cons.cons(module, Stella.NIL)));
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Save the contents of the module <code>mod</code> into a file named <code>filename</code>.
   * If a file named <code>filename</code> already exists, then the action taken depends on the
   * value of <code>ifexists</code>.  Possible values are &quot;ASK&quot;, &quot;REPLACE&quot;, &quot;WARN&quot; and &quot;ERROR&quot;:
   * <p>
   *   REPLACE =&gt; Means overwrite without warning.
   *   WARN    =&gt; Means overwrite with a warning.
   *   ERROR   =&gt; Means don't overwrite, signal an error instead.
   *   ASK     =&gt; Ask the user whether to overwrite or not.  If not overwritten, an 
   *              exception is thrown.
   * @param module
   * @param filename
   * @param ifexists
   * @param environment
   */
  public static void saveModule(Module module, String filename, String ifexists, Environment environment) {
    { boolean existsP = Stella.probeFileP(filename);

      if ((!existsP) ||
          Stella.stringEqualP(ifexists, "REPLACE")) {
      }
      else if (Stella.stringEqualP(ifexists, "ASK")) {
        if (!(Stella.yesOrNoP("File `" + filename + "' already exists.  Overwrite it? (yes or no) "))) {
          Stella.ensureFileDoesNotExist(filename, "save-module");
        }
      }
      else if (Stella.stringEqualP(ifexists, "WARN")) {
        Stella.STANDARD_WARNING.nativeStream.println("Warning: File `" + filename + "' already exists, overwriting.");
      }
      else if (Stella.stringEqualP(ifexists, "ERROR")) {
        Stella.ensureFileDoesNotExist(filename, "save-module");
      }
      else {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("Unrecognized ifexists option `" + ifexists + "'");
          throw ((BadArgumentException)(BadArgumentException.newBadArgumentException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          environment = environment;
          synchronized (Logic.$POWERLOOM_LOCK$) {
            module = ((Module)(Stella.$MODULE$.get()));
            { OutputFileStream stream = null;

              try {
                stream = Stella.openOutputFile(filename, Stella.NIL);
                Logic.doSaveModule(module, stream);

              } finally {
                if (stream != null) {
                  stream.free();
                }
              }
            }
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Save the contents of the module <code>moduleName</code> into a file named <code>filename</code>.
   * If a file named <code>filename</code> already exists, then the action taken depends on the
   * value of <code>ifexists</code>.  Possible values are &quot;ASK&quot;, &quot;REPLACE&quot;, &quot;WARN&quot; and &quot;ERROR&quot;:
   * <p>
   *   REPLACE =&gt; Means overwrite without warning.
   *   WARN    =&gt; Means overwrite with a warning.
   *   ERROR   =&gt; Means don't overwrite, signal an error instead.
   *   ASK     =&gt; Ask the user whether to overwrite or not.  If not overwritten, an
   *              exception is thrown.
   * <p>
   * A module name of <code>null</code> or the empty string refers to the
   * current module.  If no module can be found with the name <code>moduleName</code>,
   * then a Stella <code>noSuchContextException</code> is thrown.
   * @param moduleName
   * @param filename
   * @param ifexists
   * @param environment
   */
  public static void sSaveModule(String moduleName, String filename, String ifexists, Environment environment) {
    PLI.saveModule(((Module)(PLI.safelyGetModule(moduleName, environment))), filename, ifexists, environment);
  }

  /** Return the concept or relation predicate for
   * the proposition <code>prop</code>.
   * @param prop
   * @return LogicObject
   */
  public static LogicObject getPredicate(Proposition prop) {
    { LogicObject relation = Logic.getDescription(((Surrogate)(prop.operator)));

      if (relation == null) {
        relation = ((LogicObject)(((Surrogate)(prop.operator)).surrogateValue));
      }
      return (relation);
    }
  }

  /** Return the number of columns in <code>obj</code>, which must
   * be of type proposition, skolem, cons, vector or PL-iterator.  For a proposition,
   * the number includes both the predicate and arguments. For the PL-iterator
   * case,the number of columns is for the current value of the iterator. For the
   * skolem case, if the skolem is a function term, the column count of its defining
   * proposition will be returned, otherwise it is treated as a non-sequence object.
   * <p>
   * For a null item, the column count is zero.
   * For non sequence objects, the column count is one.
   * @param obj
   * @return int
   */
  public static int getColumnCount(Stella_Object obj) {
    if (obj == null) {
      return (0);
    }
    { Surrogate testValue000 = Stella_Object.safePrimaryType(obj);

      if (Surrogate.subtypeOfP(testValue000, Logic.SGT_LOGIC_PROPOSITION)) {
        { Proposition obj000 = ((Proposition)(obj));

          return (obj000.arguments.length() + 1);
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, PLI.SGT_PLI_PL_ITERATOR)) {
        { PlIterator obj000 = ((PlIterator)(obj));

          return (PLI.getColumnCount(obj000.value));
        }
      }
      else if (testValue000 == Logic.SGT_STELLA_CONS) {
        { Cons obj000 = ((Cons)(obj));

          return (obj000.length());
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_STELLA_VECTOR)) {
        { Vector obj000 = ((Vector)(obj));

          return (obj000.length());
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_LOGIC_SKOLEM)) {
        { Skolem obj000 = ((Skolem)(obj));

          if (Logic.functionOutputSkolemP(obj000)) {
            return (PLI.getColumnCount(obj000.definingProposition));
          }
          else {
            return (1);
          }
        }
      }
      else {
        return (1);
      }
    }
  }

  /** Return the value in the <code>nth</code> column of <code>sequence</code>.
   * Counting starts at zero.  Unless <code>n</code> is zero, <code>sequence</code> must be of type
   * proposition, skolem, cons, vector or PL-iterator.  A zero column number returns
   * a proposition's relational predicate.  For the PL-iterator case, the number
   * of columns is for the current value of the iterator.   For the skolem case,
   * if the skolem is a function term, the nth value of its defining proposition
   * will be returned, otherwise it is treated as a non-sequence object.
   * <p>
   * As a special case, a column number of zero will also return <code>sequence</code> itself
   * if it is not one of the types enumerated above.  This is done to allow the
   * use of <code>getNthValue</code> on PL-iterators with only a single return variable.
   * @param sequence
   * @param n
   * @param module
   * @param environment
   * @return Stella_Object
   */
  public static Stella_Object getNthValue(Stella_Object sequence, int n, Module module, Environment environment) {
    if ((n >= PLI.getColumnCount(sequence)) ||
        (n < 0)) {
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("Column index `" + n + "' is out of range for `" + sequence + "'");
        throw ((LogicException)(LogicException.newLogicException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
    { Surrogate testValue000 = Stella_Object.safePrimaryType(sequence);

      if (Surrogate.subtypeOfP(testValue000, Logic.SGT_LOGIC_PROPOSITION)) {
        { Proposition sequence000 = ((Proposition)(sequence));

          if (n == 0) {
            return (PLI.getPredicate(sequence000));
          }
          else {
            { Stella_Object value = (sequence000.arguments.theArray)[(n - 1)];

              if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(value), Logic.SGT_LOGIC_SKOLEM)) {
                { Skolem value000 = ((Skolem)(value));

                  { Object old$Module$000 = Stella.$MODULE$.get();
                    Object old$Context$000 = Stella.$CONTEXT$.get();

                    try {
                      Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
                      Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
                      environment = environment;
                      synchronized (Logic.$POWERLOOM_LOCK$) {
                        return (Logic.valueOf(value000));
                      }

                    } finally {
                      Stella.$CONTEXT$.set(old$Context$000);
                      Stella.$MODULE$.set(old$Module$000);
                    }
                  }
                }
              }
              else {
                return (value);
              }
            }
          }
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, PLI.SGT_PLI_PL_ITERATOR)) {
        { PlIterator sequence000 = ((PlIterator)(sequence));

          return (PLI.getNthValue(sequence000.value, n, module, environment));
        }
      }
      else if (testValue000 == Logic.SGT_STELLA_CONS) {
        { Cons sequence000 = ((Cons)(sequence));

          return (sequence000.nth(n));
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_STELLA_VECTOR)) {
        { Vector sequence000 = ((Vector)(sequence));

          return ((sequence000.theArray)[n]);
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_LOGIC_SKOLEM)) {
        { Skolem sequence000 = ((Skolem)(sequence));

          if (Logic.functionOutputSkolemP(sequence000)) {
            return (PLI.getNthValue(sequence000.definingProposition, n, module, environment));
          }
          else {
            return (sequence000);
          }
        }
      }
      else {
        return (sequence);
      }
    }
  }

  /** Return a string representation of the value in the <code>nth</code> column of
   * <code>sequence</code>. Counting starts at zero.   Unless <code>n</code> is zero, <code>sequence</code> must be of type
   * proposition, cons, vector or PL-iterator.  A zero column number returns
   * a proposition's relational predicate.  For the PL-iterator case, the
   * the current value pointed to by the iterator is used.  This will always
   * succeed, even if the <code>nth</code> value is not a string object.  In that case, a
   * string reprensentation will be returned.
   * <p>
   * As a special case, a column number of zero will also return <code>sequence</code> itself
   * as a string if it is not one of the types enumerated above.  This is done to 
   * allow the use of <code>getNthString</code> on PL-iterators with only a single return variable.
   * @param sequence
   * @param n
   * @param module
   * @param environment
   * @return String
   */
  public static String getNthString(Stella_Object sequence, int n, Module module, Environment environment) {
    return (PLI.objectToString(PLI.getNthValue(sequence, n, module, environment)));
  }

  /** Return an integer representation of the value in the <code>nth</code> column of
   * <code>sequence</code>. Counting starts at zero.   Unless <code>n</code> is zero, <code>sequence</code> must be of type
   * proposition, cons, vector or PL-iterator.  A zero column number returns
   * a proposition's relational predicate.  For the PL-iterator case, the
   * the current value pointed to by the iterator is used.  If this is not
   * an integer value, then an exception will be thrown.
   * <p>
   * As a special case, a column number of zero will also return the integer
   * value of <code>sequence</code> itself if it is not one of the types enumerated
   * above.   This allows the use of <code>getNthInteger</code> on PL-iterators with
   * only a single return variable.  If  <code>sequence</code> cannot be turned into an
   * integer, an exception will be thrown.
   * @param sequence
   * @param n
   * @param module
   * @param environment
   * @return int
   */
  public static int getNthInteger(Stella_Object sequence, int n, Module module, Environment environment) {
    return (PLI.objectToInteger(PLI.getNthValue(sequence, n, module, environment)));
  }

  /** Return the floating point value in the <code>nth</code> column of
   * <code>sequence</code>. Counting starts at zero.  <code>sequence</code> must be of type
   * proposition, cons, vector or PL-iterator.  A zero column number returns
   * a proposition's relational predicate.  For the PL-iterator case, the
   * the current value pointed to by the iterator is used.  If this is not
   * a floating point value, then an exception will be thrown.
   * <p>
   * As a special case, a column number of zero will also return the floating
   * point value of <code>sequence</code> itself if it is not one of the types enumerated
   * above.  This allows the use of <code>getNthFloat</code> on PL-iterators with only
   * a single return variable.    If  <code>sequence</code> cannot be turned into a floating
   * point value, an exception will be thrown.
   * @param sequence
   * @param n
   * @param module
   * @param environment
   * @return double
   */
  public static double getNthFloat(Stella_Object sequence, int n, Module module, Environment environment) {
    return (PLI.objectToFloat(PLI.getNthValue(sequence, n, module, environment)));
  }

  /** Return a logic object representation of the value in the <code>nth</code> column
   * of <code>sequence</code>.  Counting starts at zero.   Unless <code>n</code> is zero, <code>sequence</code> must be of type
   * proposition, cons, vector or PL-iterator.  A zero column number returns
   * a proposition's relational predicate.  For the PL-iterator case, the
   * the current value pointed to by the iterator is used.  A zero column number
   * returns the proposition's relational predicate.  If the return value is
   * not a LOGIC-OBJECT, an exception is thrown.
   * <p>
   * As a special case, a column number of zero will also return <code>sequence</code> itself
   * if it is not one of the types enumerated above.  This is done to allow the
   * use of <code>getNthValue</code> on PL-iterators with only a single return variable.
   * If <code>sequence</code> is not a LOGIC-OBJECT, an exception is thrown.
   * @param sequence
   * @param n
   * @param module
   * @param environment
   * @return LogicObject
   */
  public static LogicObject getNthLogicObject(Stella_Object sequence, int n, Module module, Environment environment) {
    { Stella_Object value = PLI.getNthValue(sequence, n, module, environment);

      if (Stella_Object.isaP(value, Logic.SGT_LOGIC_LOGIC_OBJECT)) {
        return (((LogicObject)(value)));
      }
      else {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("Can't coerce `" + value + "' to a LOGIC-OBJECT.");
          throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
    }
  }

  /** Returns the members of an enumerated collection.  This works on all types
   * of collection, i.e., sets and lists
   * @param collection
   * @param module
   * @param environment
   * @return Cons
   */
  public static Cons getEnumeratedCollectionMembers(Stella_Object collection, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          { List members = Logic.assertedCollectionMembers(collection, true);

            if (members != null) {
              return (members.theConsList);
            }
            else {
              return (null);
            }
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Evaluate the command <code>command</code> within <code>module</code> and return
   * the result. Currently, only the evaluation of (possibly nested) commands and
   * global variables is supported.  Commands are simple to program in Common Lisp,
   * since they are built into the language, and relatively awkward in Java and C++.
   * Users of either of those languages are more likely to want to call <code>sEvaluate</code>.
   * @param command
   * @param module
   * @param environment
   * @return Stella_Object
   */
  public static Stella_Object evaluate(Stella_Object command, Module module, Environment environment) {
    if (command != null) {
      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          environment = environment;
          synchronized (Logic.$POWERLOOM_LOCK$) {
            return (Stella_Object.evaluate(command));
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
    return (null);
  }

  /** Evaluate the command represented by the string <code>command</code> within <code>module</code> and
   * return the result.  Currently, only the evaluation of (possibly nested) commands and
   * global variables is supported.
   * <p>
   *  A module name of <code>null</code> or the empty string refers to the
   * current module.  If no module can be found with the name <code>moduleName</code>,
   * then a Stella <code>noSuchContextException</code> is thrown.
   * @param command
   * @param moduleName
   * @param environment
   * @return Stella_Object
   */
  public static Stella_Object sEvaluate(String command, String moduleName, Environment environment) {
    { Context module = PLI.safelyGetModule(moduleName, environment);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, ((module != null) ? ((Module)(module)) : ((Module)(Stella.$MODULE$.get()))));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          environment = environment;
          synchronized (Logic.$POWERLOOM_LOCK$) {
            module = ((Module)(Stella.$MODULE$.get()));
            return (PLI.evaluate(Stella.readSExpressionFromString(command), ((Module)(module)), environment));
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Run the PowerLoom read/eval/print loop.
   * @param module
   * @param environment
   */
  public static void powerloom(Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          Logic.powerloom();
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Test whether <code>obj</code> is of type LOGIC-OBJECT
   * @param obj
   * @return boolean
   */
  public static boolean isLogicObject(Stella_Object obj) {
    return (Stella_Object.isaP(obj, Logic.SGT_LOGIC_LOGIC_OBJECT));
  }

  /** Test whether <code>obj</code> is of type SKOLEM (which subsumes pattern variables).
   * @param obj
   * @return boolean
   */
  public static boolean isSkolem(Stella_Object obj) {
    return (Stella_Object.isaP(obj, Logic.SGT_LOGIC_SKOLEM));
  }

  /** Test whether <code>obj</code> is of type PATTERN-VARIABLE.
   * @param obj
   * @return boolean
   */
  public static boolean isVariable(Stella_Object obj) {
    return (Stella_Object.isaP(obj, Logic.SGT_LOGIC_PATTERN_VARIABLE));
  }

  /** Test whether <code>obj</code> is of type INTEGER
   * @param obj
   * @return boolean
   */
  public static boolean isInteger(Stella_Object obj) {
    return (Stella_Object.isaP(obj, Logic.SGT_STELLA_INTEGER_WRAPPER));
  }

  /** Test whether <code>obj</code> is of type FLOAT (double)
   * @param obj
   * @return boolean
   */
  public static boolean isFloat(Stella_Object obj) {
    return (Stella_Object.isaP(obj, Logic.SGT_STELLA_FLOAT_WRAPPER));
  }

  /** Test whether <code>obj</code> is of type NUMBER.  This can
   * be either an integer or a floating point number.  One key characteristic
   * is that 'object-to-integer' and <code>objectToFloat</code> will both work on it.
   * @param obj
   * @return boolean
   */
  public static boolean isNumber(Stella_Object obj) {
    return (Stella_Object.isaP(obj, Logic.SGT_STELLA_NUMBER_WRAPPER));
  }

  /** Test whether <code>obj</code> is of type STRING
   * @param obj
   * @return boolean
   */
  public static boolean isString(Stella_Object obj) {
    return (Stella_Object.isaP(obj, Logic.SGT_STELLA_STRING_WRAPPER));
  }

  /** Test whether <code>obj</code> is an enumerated collection.  This
   * subsumes both sets and lists.
   * @param obj
   * @return boolean
   */
  public static boolean isEnumeratedCollection(Stella_Object obj) {
    return (Logic.logicalCollectionP(obj));
  }

  /** Test whether <code>obj</code> is an enumerated set.
   * @param obj
   * @return boolean
   */
  public static boolean isEnumeratedSet(Stella_Object obj) {
    return (Logic.enumeratedSetP(obj));
  }

  /** Test whether <code>obj</code> is an enumerated list
   * @param obj
   * @return boolean
   */
  public static boolean isEnumeratedList(Stella_Object obj) {
    return (Logic.enumeratedListP(obj));
  }

  /** Tests whether <code>tv</code> is a true truth value.  It can be true
   * either absolutely or by default.
   * @param tv
   * @return boolean
   */
  public static boolean isTrue(TruthValue tv) {
    return ((tv == Logic.TRUE_TRUTH_VALUE) ||
        (tv == Logic.DEFAULT_TRUE_TRUTH_VALUE));
  }

  /** Tests whether <code>tv</code> is a false truth value.  It can be false
   * either absolutely or by default.
   * @param tv
   * @return boolean
   */
  public static boolean isFalse(TruthValue tv) {
    return ((tv == Logic.FALSE_TRUTH_VALUE) ||
        (tv == Logic.DEFAULT_FALSE_TRUTH_VALUE));
  }

  /** Tests whether <code>tv</code> is an unknown truth value.
   * @param tv
   * @return boolean
   */
  public static boolean isUnknown(TruthValue tv) {
    return ((tv == Logic.UNKNOWN_TRUTH_VALUE) ||
        (tv == null));
  }

  /** Tests whether <code>tv</code> is a known truth value (i.e., true or false).
   * @param tv
   * @return boolean
   */
  public static boolean isKnown(TruthValue tv) {
    return (TruthValue.knownTruthValueP(tv));
  }

  /** Tests whether <code>tv</code> is an inconsistent truth value.
   * @param tv
   * @return boolean
   */
  public static boolean isInconsistent(TruthValue tv) {
    return (tv == Logic.INCONSISTENT_TRUTH_VALUE);
  }

  /** Tests whether <code>tv</code> is a strict (non-default) truth value.
   * @param tv
   * @return boolean
   */
  public static boolean isStrict(TruthValue tv) {
    return ((tv == Logic.TRUE_TRUTH_VALUE) ||
        (tv == Logic.FALSE_TRUTH_VALUE));
  }

  /** Tests whether <code>tv</code> is a default truth value.
   * @param tv
   * @return boolean
   */
  public static boolean isDefault(TruthValue tv) {
    return ((tv == Logic.DEFAULT_TRUE_TRUTH_VALUE) ||
        (tv == Logic.DEFAULT_FALSE_TRUTH_VALUE));
  }

  /** Returns a truth value for <code>query</code> in <code>module</code> and <code>environment</code>.
   * <code>query</code> has the same syntax as the PowerLoom <code>ask</code> command (which see)
   * but with the <code>ask</code> operator omitted.  For example, here are some legal
   * <code>query</code> arguments:
   * 	 
   *     ((happy Fred))
   *     ((happy Fred) :inference-level :assertion)
   *     ((happy Fred) :inference-level :assertion :timeout 1.0)
   * 	
   * As a convenience, a <code>query</code> argument whose first element is a symbol is
   * interpreted as a sentence that is queried without any options.  For example:
   * 	 
   *     (happy Fred)
   * 	
   * is a legal <code>query</code> argument.  Note that for a sentence whose relation is a list
   * itself, e.g., <code>__FruitFn_BananaTree__MyBanana_</code> this shortcut is not available,
   * that is, in that case an extra level of list nesting is always necessary.
   * The returned truth value represents the logical truth of the queried sentence
   * as determined by PowerLoom.  It can be be tested via the functions <code>isTrue</code>,
   * <code>isFalse</code> and <code>isUnknown</code> (which see).
   * @param query
   * @param module
   * @param environment
   * @return TruthValue
   */
  public static TruthValue ask(Cons query, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          query = ((Cons)(Logic.deobjectifyTree(query)));
          if (Stella_Object.symbolP(query.value)) {
            query = Cons.cons(query, Stella.NIL);
          }
          return (Logic.callAsk(query));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Returns a truth value for <code>query</code> in module <code>moduleName</code> and <code>environment</code>.
   * <code>query</code> has the same syntax as the PowerLoom <code>ask</code> command (which see) but
   * with the <code>ask</code> operator omitted.  Different from the PLI <code>ask</code> function, <code>sAsk</code>
   * does not expect a top-level pair of parentheses.  For example, here are some legal
   * <code>query</code> arguments:
   * 	 
   *     &quot;(happy Fred)&quot;
   *     &quot;(happy Fred) :inference-level :assertion&quot;
   *     &quot;(happy Fred) :inference-level :assertion :timeout 1.0&quot;
   * 	
   * Names in <code>query</code> will be interpreted relative to module <code>moduleName</code>.
   * A null <code>moduleName</code> or the empty string refers to the current module.
   * If no module can be found with the name <code>moduleName</code>, then a STELLA
   * <code>noSuchContextException</code> is thrown.
   * The returned truth value represents the logical truth of the queried sentence
   * as determined by PowerLoom.  It can be be tested via the functions <code>isTrue</code>,
   * <code>isFalse</code> and <code>isUnknown</code> (which see).
   * @param query
   * @param moduleName
   * @param environment
   * @return TruthValue
   */
  public static TruthValue sAsk(String query, String moduleName, Environment environment) {
    { Cons queryform = Stella.NIL;
      Context module = PLI.safelyGetModule(moduleName, environment);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, ((module != null) ? ((Module)(module)) : ((Module)(Stella.$MODULE$.get()))));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          environment = environment;
          synchronized (Logic.$POWERLOOM_LOCK$) {
            { Stella_Object sexp = null;
              SExpressionIterator iter000 = InputStream.sExpressions(InputStringStream.newInputStringStream(query));
              Cons collect000 = null;

              while (iter000.nextP()) {
                sexp = iter000.value;
                if (collect000 == null) {
                  {
                    collect000 = Cons.cons(sexp, Stella.NIL);
                    if (queryform == Stella.NIL) {
                      queryform = collect000;
                    }
                    else {
                      Cons.addConsToEndOfConsList(queryform, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000.rest = Cons.cons(sexp, Stella.NIL);
                    collect000 = collect000.rest;
                  }
                }
              }
            }
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
      return (PLI.ask(queryform, ((Module)(PLI.safelyGetModule(moduleName, environment))), environment));
    }
  }

  /** Returns an iterator of variable bindings that when substituted for the
   * open variables in <code>query</code> satisfy the query proposition.  The query is
   * run in <code>module</code> and relative to <code>environment</code>.  <code>query</code> has the same syntax
   * as the PowerLoom <code>retrieve</code> command (which see) but with the <code>retrieve</code>
   * operator omitted.    For example, here are some legal <code>query</code> arguments:
   * 	 
   *     ((happy ?x))
   *     (10 (happy ?x))
   *     (all (happy ?x))
   *     (all ?x (happy ?x))
   *     (10 (happy ?x) :inference-level :assertion)
   *     (10 (happy ?x) :inference-level :assertion :timeout 1.0)
   * 	
   * If there is only a single output variable (as in all the examples above)
   * each element generated by the returned iterator will be a binding for
   * that variable - unless, the output variable was declared with a surrounding
   * pair of parentheses.  For example:
   * 	 
   *     (all (?x) (happy ?x))
   * 	
   * In that case, the generated elements will be one-element lists.  If there
   * are multiple output variables, each element generated by the returned
   * iterator will be a list of variable bindings that can be accessed using
   * the various <code>getNthDDD</code> functions.  The list of output variables does
   * not need to be declared in which case they are taken to be the open variables
   * in the query proposition in the order in which they were encountered.  If
   * order does matter or should be different from its default, it can be forced
   * by declaring the set of output variables.
   * @param query
   * @param module
   * @param environment
   * @return PlIterator
   */
  public static PlIterator retrieve(Cons query, Module module, Environment environment) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        environment = environment;
        synchronized (Logic.$POWERLOOM_LOCK$) {
          query = ((Cons)(Logic.deobjectifyTree(query)));
          return (PLI.consToPlIterator(Logic.callRetrieve(query).consifyCurrentSolutions()));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Returns an iterator of variable bindings that when substituted for the
   * open variables in <code>query</code> satisfy the query proposition.  The query is
   * run in <code>module</code> and relative to <code>environment</code>.  <code>query</code> has the same syntax
   * as the PowerLoom <code>retrieve</code> command (which see) but with the <code>retrieve</code>
   * operator omitted.  Different from the PLI <code>retrieve</code> function, <code>sRetrieve</code>
   * does not expect a top-level pair of parentheses.  For example, here are some
   * legal <code>query</code> arguments:
   * 	 
   *     &quot;(happy ?x)&quot;
   *     &quot;10 (happy ?x)&quot;
   *     &quot;all (happy ?x)&quot;
   *     &quot;all ?x (happy ?x)&quot;
   *     &quot;10 (happy ?x) :inference-level :assertion&quot;
   *     &quot;10 (happy ?x) :inference-level :assertion :timeout 1.0&quot;
   * 	
   * If there is only a single output variable (as in all the examples above)
   * each element generated by the returned iterator will be a binding for
   * that variable - unless, the output variable was declared with a surrounding
   * pair of parentheses.  For example:
   * 	 
   *     &quot;all (?x) (happy ?x)&quot;
   * 	
   * In that case, the generated elements will be one-element lists.  If there
   * are multiple output variables, each element generated by the returned
   * iterator will be a list of variable bindings that can be accessed using
   * the various <code>getNthDDD</code> functions.  The list of output variables does
   * not need to be declared in which case they are taken to be the open variables
   * in the query proposition in the order in which they were encountered.  If
   * order does matter or should be different from its default, it can be forced
   * by declaring the set of output variables.
   * <p>
   * Names in <code>query</code> will be interpreted relative to module <code>moduleName</code>.
   * A null <code>moduleName</code> or the empty string refers to the current module.
   * If no module can be found with the name <code>moduleName</code>, then a STELLA
   * <code>noSuchContextException</code> is thrown.
   * @param query
   * @param moduleName
   * @param environment
   * @return PlIterator
   */
  public static PlIterator sRetrieve(String query, String moduleName, Environment environment) {
    { Cons queryform = Stella.NIL;
      Context module = PLI.safelyGetModule(moduleName, environment);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, ((module != null) ? ((Module)(module)) : ((Module)(Stella.$MODULE$.get()))));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          environment = environment;
          synchronized (Logic.$POWERLOOM_LOCK$) {
            { Stella_Object sexp = null;
              SExpressionIterator iter000 = InputStream.sExpressions(InputStringStream.newInputStringStream(query));
              Cons collect000 = null;

              while (iter000.nextP()) {
                sexp = iter000.value;
                if (collect000 == null) {
                  {
                    collect000 = Cons.cons(sexp, Stella.NIL);
                    if (queryform == Stella.NIL) {
                      queryform = collect000;
                    }
                    else {
                      Cons.addConsToEndOfConsList(queryform, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000.rest = Cons.cons(sexp, Stella.NIL);
                    collect000 = collect000.rest;
                  }
                }
              }
            }
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
      return (PLI.retrieve(queryform, ((Module)(module)), environment));
    }
  }

  /** Return the proposition currently being inferred by this control <code>frame</code>.
   * This proposition will generally have bound and/or unbound pattern variables as its arguments.
   * @param frame
   * @return Proposition
   */
  public static Proposition getFrameProposition(ControlFrame frame) {
    return (frame.proposition);
  }

  /** Return the arity of the proposition currently being inferred by <code>frame</code>.
   * This will be the actual number of arguments, even if the proposition is of variable arity.
   * @param frame
   * @return int
   */
  public static int getFrameArity(ControlFrame frame) {
    return (frame.proposition.arguments.length());
  }

  /** Return the iterator generating successive bindings for the proposition
   * that is currently being inferred by <code>frame</code>.
   * @param frame
   * @return PlIterator
   */
  public static PlIterator getFrameIterator(ControlFrame frame) {
    return (((PlIterator)(((Iterator)(KeyValueList.dynamicSlotValue(frame.dynamicSlots, Logic.SYM_STELLA_ITERATOR, null))))));
  }

  /** Set the iterator for generating successive bindings for the proposition
   * that is currently being inferred by <code>frame</code> to <code>iterator</code>.
   * @param frame
   * @param iterator
   */
  public static void setFrameIterator(ControlFrame frame, PlIterator iterator) {
    KeyValueList.setDynamicSlotValue(frame.dynamicSlots, Logic.SYM_STELLA_ITERATOR, iterator, null);
  }

  /** Return the <code>n</code>-th argument of the proposition that is currently being inferred
   * by <code>frame</code>.  This will generally be a pattern variable that might be unbound or bound.
   * @param frame
   * @param n
   * @return Stella_Object
   */
  public static Stella_Object getNthFrameArgument(ControlFrame frame, int n) {
    { Vector args = frame.proposition.arguments;

      if ((n >= 0) &&
          (n < args.length())) {
        return ((args.theArray)[n]);
      }
      else {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("Argument index `" + n + "' is out of range for `" + frame.proposition + "'");
          throw ((LogicException)(LogicException.newLogicException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
    }
  }

  /** Return the binding of the <code>n</code>-th argument of the proposition that is currently
   * being inferred by <code>frame</code>.  This will be NULL if the argument is unbound, otherwise, the object
   * bound to the variable.
   * @param frame
   * @param n
   * @return Stella_Object
   */
  public static Stella_Object getNthFrameBinding(ControlFrame frame, int n) {
    { Vector args = frame.proposition.arguments;

      if ((n >= 0) &&
          (n < args.length())) {
        return (Logic.safeArgumentBoundTo((args.theArray)[n]));
      }
      else {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("Argument index `" + n + "' is out of range for `" + frame.proposition + "'");
          throw ((LogicException)(LogicException.newLogicException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
    }
  }

  /** Set the binding of the <code>n</code>-th argument of the proposition that is currently
   * being inferred by <code>frame</code> to <code>value</code>.  If the binding was successful, that is if the argument
   * was unbound or is already bound to <code>binding</code>, the function returns TRUE.  Otherwise, the
   * argument will keep its current binding and FALSE will be returned.
   * @param frame
   * @param n
   * @param value
   * @return boolean
   */
  public static boolean setNthFrameBinding(ControlFrame frame, int n, Stella_Object value) {
    { Vector args = frame.proposition.arguments;

      if ((n >= 0) &&
          (n < args.length())) {
        return (Logic.bindArgumentToValueP((args.theArray)[n], value, true));
      }
      else {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("Argument index `" + n + "' is out of range for `" + frame.proposition + "'");
          throw ((LogicException)(LogicException.newLogicException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
    }
  }

  /** Return TRUE if the arguments of <code>frame</code> are bound according to <code>pattern</code>.
   * Each character in pattern corresponds to an argument at the particular position and  must be
   * either <code>B</code> (for bound) or <code>_</code> for unbound.  The function returns TRUE if <code>frame</code> has at least
   * as many arguments as <code>pattern</code> has characters and their bindings match <code>pattern</code>.  If <code>frame</code>
   * has additional arguments, they will be ignored.  If <code>pattern</code> has more positions than <code>frame</code>
   * has arguments, the function returns FALSE.
   * @param frame
   * @param pattern
   * @return boolean
   */
  public static boolean isFrameBindingPattern(ControlFrame frame, String pattern) {
    { Vector args = frame.proposition.arguments;

      if (pattern.length() <= args.length()) {
        { char ch = Stella.NULL_CHARACTER;
          String vector000 = pattern;
          int index000 = 0;
          int length000 = vector000.length();
          Stella_Object arg = null;
          Vector vector001 = args;
          int index001 = 0;
          int length001 = vector001.length();

          for (;(index000 < length000) &&
                    (index001 < length001); index000 = index000 + 1, index001 = index001 + 1) {
            ch = vector000.charAt(index000);
            arg = (vector001.theArray)[index001];
            switch (ch) {
              case 'B': 
                if (Logic.safeArgumentBoundTo(arg) == null) {
                  return (false);
                }
              break;
              case '_': 
                if (Logic.safeArgumentBoundTo(arg) != null) {
                  return (false);
                }
              break;
              default:
                { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

                  stream000.nativeStream.print("Illegal binding pattern: `" + pattern + "'");
                  throw ((LogicException)(LogicException.newLogicException(stream000.theStringReader()).fillInStackTrace()));
                }
            }
          }
        }
        return (true);
      }
      else {
        return (false);
      }
    }
  }

  /** Return a string representation of the argument binding pattern of <code>frame</code>.
   * The syntax of the pattern is the same as used for <code>isFrameBindingPattern</code> (which see).
   * @param frame
   * @return String
   */
  public static String getFrameBindingPattern(ControlFrame frame) {
    { Vector args = frame.proposition.arguments;
      StringBuffer pattern = Stella.makeRawMutableString(args.length());

      { Stella_Object arg = null;
        Vector vector000 = args;
        int index000 = 0;
        int length000 = vector000.length();
        int i = Stella.NULL_INTEGER;
        int iter000 = 0;

        for (;index000 < length000; index000 = index000 + 1, iter000 = iter000 + 1) {
          arg = (vector000.theArray)[index000];
          i = iter000;
          if (Logic.safeArgumentBoundTo(arg) != null) {
            edu.isi.stella.javalib.Native.mutableString_nthSetter(pattern, 'B', i);
          }
          else {
            edu.isi.stella.javalib.Native.mutableString_nthSetter(pattern, '_', i);
          }
        }
      }
      return (pattern.toString());
    }
  }

  /** Return a frame variable binding stack state that can be used to unbind
   * all frame variables to the state they were in when the binding stack state was recorded.
   * @param frame
   * @return Cons
   */
  public static Cons getFrameBindingState(ControlFrame frame) {
    { PatternRecord patternrecord = ((QueryIterator)(Logic.$QUERYITERATOR$.get())).currentPatternRecord;
      int ubstackoffset = patternrecord.topUnbindingStackOffset;

      return (Cons.cons(patternrecord, Cons.cons(IntegerWrapper.wrapInteger(ubstackoffset), Stella.NIL)));
    }
  }

  /** Reset the frame variable binding stack state to <code>state</code>.  This will set
   * all frame variables to the state they were in when the binding stack state was recorded.
   * @param frame
   * @param state
   */
  public static void setFrameBindingState(ControlFrame frame, Cons state) {
    PatternRecord.unbindVariablesBeginningAt(((PatternRecord)(state.value)), ((int)(((NumberWrapper)(state.rest.value)).numberWrapperToFloat() + 1)));
  }

  /** Return the value of the global STELLA configuration <code>property</code>
   * or <code>defaultvalue</code> if it is undefined.
   * @param property
   * @param defaultvalue
   * @return Stella_Object
   */
  public static Stella_Object getPropertyObject(String property, Stella_Object defaultvalue) {
    return (Stella_Object.getProperty(StringWrapper.wrapString(property), Cons.cons(defaultvalue, Stella.NIL)));
  }

  /** Return the value of the global STELLA configuration <code>property</code>
   * as a string or <code>defaultvalue</code> if it is undefined.
   * @param property
   * @param defaultvalue
   * @return String
   */
  public static String getPropertyString(String property, String defaultvalue) {
    return (PLI.objectToString(Stella_Object.getProperty(StringWrapper.wrapString(property), Cons.cons(StringWrapper.wrapString(defaultvalue), Stella.NIL))));
  }

  /** Synonym for <code>getPropertyString</code> (which see).
   * @param property
   * @param defaultvalue
   * @return String
   */
  public static String getProperty(String property, String defaultvalue) {
    return (PLI.getPropertyString(property, defaultvalue));
  }

  /** Return the value of the global STELLA configuration <code>property</code>
   * as an integer or <code>defaultvalue</code> if it is undefined.  Raises an error if the defined
   * value is not an integer.
   * @param property
   * @param defaultvalue
   * @return int
   */
  public static int getPropertyInteger(String property, int defaultvalue) {
    return (PLI.objectToInteger(Stella_Object.getProperty(StringWrapper.wrapString(property), Cons.cons(IntegerWrapper.wrapInteger(defaultvalue), Stella.NIL))));
  }

  /** Return the value of the global STELLA configuration <code>property</code>
   * as a float or <code>defaultvalue</code> if it is undefined.  Raises an error if the defined
   * value is not a float.
   * @param property
   * @param defaultvalue
   * @return double
   */
  public static double getPropertyFloat(String property, double defaultvalue) {
    return (PLI.objectToFloat(Stella_Object.getProperty(StringWrapper.wrapString(property), Cons.cons(FloatWrapper.wrapFloat(defaultvalue), Stella.NIL))));
  }

  /** Return the value of the global STELLA configuration <code>property</code>
   * as a boolean or <code>defaultvalue</code> if it is undefined.  Raises an error if the defined
   * value is not a boolean.
   * @param property
   * @param defaultvalue
   * @return boolean
   */
  public static boolean getPropertyBoolean(String property, boolean defaultvalue) {
    return (BooleanWrapper.coerceWrappedBooleanToBoolean(Stella_Object.coerceToBoolean(Stella_Object.getProperty(StringWrapper.wrapString(property), Cons.cons((defaultvalue ? Stella.TRUE_WRAPPER : Stella.FALSE_WRAPPER), Stella.NIL)))));
  }

  /** Set the global STELLA configuration <code>property</code> to <code>value</code>.
   * @param property
   * @param value
   */
  public static void setPropertyObject(String property, Stella_Object value) {
    Stella_Object.setProperty(StringWrapper.wrapString(Native.string_copy(property)), value);
  }

  /** Set the global STELLA configuration <code>property</code> to a string <code>value</code>.
   * @param property
   * @param value
   */
  public static void setPropertyString(String property, String value) {
    Stella_Object.setProperty(StringWrapper.wrapString(Native.string_copy(property)), StringWrapper.wrapString(Native.string_copy(value)));
  }

  /** Synonym for <code>setPropertyString</code> (which see).
   * @param property
   * @param value
   */
  public static void setProperty(String property, String value) {
    PLI.setPropertyString(property, value);
  }

  /** Set the global STELLA configuration <code>property</code> to an integer <code>value</code>.
   * @param property
   * @param value
   */
  public static void setPropertyInteger(String property, int value) {
    Stella_Object.setProperty(StringWrapper.wrapString(Native.string_copy(property)), IntegerWrapper.wrapInteger(value));
  }

  /** Set the global STELLA configuration <code>property</code> to a float <code>value</code>.
   * @param property
   * @param value
   */
  public static void setPropertyFloat(String property, double value) {
    Stella_Object.setProperty(StringWrapper.wrapString(Native.string_copy(property)), FloatWrapper.wrapFloat(value));
  }

  /** Set the global STELLA configuration <code>property</code> to a boolean <code>value</code>.
   * @param property
   * @param value
   */
  public static void setPropertyBoolean(String property, boolean value) {
    Stella_Object.setProperty(StringWrapper.wrapString(Native.string_copy(property)), (value ? Stella.TRUE_WRAPPER : Stella.FALSE_WRAPPER));
  }

  /** Return TRUE if <code>property</code> has a defined value.
   * @param property
   * @return boolean
   */
  public static boolean isDefinedProperty(String property) {
    { Stella_Object value = Stella_Object.getProperty(StringWrapper.wrapString(property), Stella.NIL);

      return ((value != null) &&
          (!Logic.nullWrapperP(value)));
    }
  }

  /** Print all currently defined STELLA configuration properties and values.
   */
  public static void printProperties() {
    Stella.printProperties();
  }

  public static java.lang.reflect.Method getExceptionHandler() {
    return (Stella.getGlobalExceptionHandler());
  }

  public static void setExceptionHandler(java.lang.reflect.Method handler) {
    Stella.setGlobalExceptionHandler(handler);
  }

  /** Register <code>renamed_Object</code> to prevent it from being garbage-collected by the PowerLoom GC.
   * The result of registration is a handle for <code>renamed_Object</code> which can later be used to unregister it.
   * Currently it is assumed that calling this immediately after an object was returned by a PLI function
   * is safe; however, we might have to handle registration in PLI functions before objects are returned.
   * This is not thread safe and needs to be explicitly synchronized in a threaded environment.
   * @param renamed_Object
   * @return Cons
   */
  public static Cons registerObject(Stella_Object renamed_Object) {
    { ObjectRegistryList registry = PLI.$OBJECT_REGISTRY$;

      registry.push(renamed_Object);
      registry.registryLength = registry.registryLength + 1;
      return (registry.theConsList);
    }
  }

  /** Unregister the object whose registered handle is <code>objecthandle</code> to make it available
   * for PowerLoom garbage collection.  This also is not thread safe and needs to be explicitly synchronized
   * in a threaded environment.
   * @param objecthandle
   */
  public static void unregisterObject(Cons objecthandle) {
    { ObjectRegistryList registry = PLI.$OBJECT_REGISTRY$;
      int nfree = registry.nFreeCells;

      objecthandle.value = null;
      nfree = nfree + 1;
      if ((nfree > 1000) &&
          (nfree >= ((registry.registryLength) >> 1))) {
        registry.remove(null);
        registry.registryLength = registry.registryLength - nfree;
        nfree = 0;
      }
      registry.nFreeCells = nfree;
    }
  }

  public static void main(String[] argv063) {
    Stella.STANDARD_OUTPUT.nativeStream.println("Initializing STELLA...");
    StartupStellaSystem.startupStellaSystem();
    Stella.STANDARD_OUTPUT.nativeStream.println("Initializing PowerLoom...");
    StartupLogicSystem.startupLogicSystem();
    Stella.string_changeModule("PL-USER");
    Logic.powerloom();
  }

}
