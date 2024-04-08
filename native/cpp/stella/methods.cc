//  -*- Mode: C++ -*-

// methods.cc

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

Object* apply(cpp_function_code code, Cons* arguments) {
  // Apply `code' to `arguments', returning a value of type OBJECT.
  // Currently limited to at most 10 `arguments'.
  if (arguments == NIL) {
    return (((Object*  (*) ())code)());
  }
  else {
    { Object* arg1 = arguments->value;

      arguments = arguments->rest;
      if (arguments == NIL) {
        return (((Object*  (*) (Object*))code)(arg1));
      }
      { Object* arg2 = arguments->value;

        arguments = arguments->rest;
        if (arguments == NIL) {
          return (((Object*  (*) (Object*, Object*))code)(arg1, arg2));
        }
        { Object* arg3 = arguments->value;

          arguments = arguments->rest;
          if (arguments == NIL) {
            return (((Object*  (*) (Object*, Object*, Object*))code)(arg1, arg2, arg3));
          }
          { Object* arg4 = arguments->value;

            arguments = arguments->rest;
            if (arguments == NIL) {
              return (((Object*  (*) (Object*, Object*, Object*, Object*))code)(arg1, arg2, arg3, arg4));
            }
            { Object* arg5 = arguments->value;

              arguments = arguments->rest;
              if (arguments == NIL) {
                return (((Object*  (*) (Object*, Object*, Object*, Object*, Object*))code)(arg1, arg2, arg3, arg4, arg5));
              }
              { Object* arg6 = arguments->value;

                arguments = arguments->rest;
                if (arguments == NIL) {
                  return (((Object*  (*) (Object*, Object*, Object*, Object*, Object*, Object*))code)(arg1, arg2, arg3, arg4, arg5, arg6));
                }
                { Object* arg7 = arguments->value;

                  arguments = arguments->rest;
                  if (arguments == NIL) {
                    return (((Object*  (*) (Object*, Object*, Object*, Object*, Object*, Object*, Object*))code)(arg1, arg2, arg3, arg4, arg5, arg6, arg7));
                  }
                  { Object* arg8 = arguments->value;

                    arguments = arguments->rest;
                    if (arguments == NIL) {
                      return (((Object*  (*) (Object*, Object*, Object*, Object*, Object*, Object*, Object*, Object*))code)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8));
                    }
                    { Object* arg9 = arguments->value;

                      arguments = arguments->rest;
                      if (arguments == NIL) {
                        return (((Object*  (*) (Object*, Object*, Object*, Object*, Object*, Object*, Object*, Object*, Object*))code)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9));
                      }
                      { Object* arg10 = arguments->value;

                        arguments = arguments->rest;
                        if (arguments == NIL) {
                          return (((Object*  (*) (Object*, Object*, Object*, Object*, Object*, Object*, Object*, Object*, Object*, Object*))code)(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10));
                        }
                        { OutputStringStream* stream000 = newOutputStringStream();

                          *(stream000->nativeStream) << "Too many function arguments in `apply'." << "Maximum is 10.";
                          throw *newStellaException(stream000->theStringReader());
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

Object* applyMethod(cpp_method_code code, Cons* arguments) {
  // Apply `code' to `arguments', returning a value of type
  // OBJECT.
  switch (arguments->length()) {
    case 0: 
      throw *newStellaException("Can't call method code on 0 arguments.");
      break;
    case 1: 
      return ((arguments->value->*((Object*  (Object::*) ()) code)) ());
    case 2: 
      return ((arguments->value->*((Object*  (Object::*) (Object*)) code)) (arguments->rest->value));
    case 3: 
      return ((arguments->value->*((Object*  (Object::*) (Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2)));
    case 4: 
      return ((arguments->value->*((Object*  (Object::*) (Object*, Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2), arguments->nth(3)));
    case 5: 
      return ((arguments->value->*((Object*  (Object::*) (Object*, Object*, Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2), arguments->nth(3), arguments->nth(4)));
    default:
      throw *newStellaException("Too many function arguments in `apply'.  Max is 5.");
      break;
  }
}

int applyIntegerMethod(cpp_method_code code, Cons* arguments) {
  // Apply `code' to `arguments', returning a value of type
  // INTEGER.
  switch (arguments->length()) {
    case 0: 
      throw *newStellaException("Can't call method code on 0 arguments.");
      break;
    case 1: 
      return ((arguments->value->*((int  (Object::*) ()) code)) ());
    case 2: 
      return ((arguments->value->*((int  (Object::*) (Object*)) code)) (arguments->rest->value));
    case 3: 
      return ((arguments->value->*((int  (Object::*) (Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2)));
    case 4: 
      return ((arguments->value->*((int  (Object::*) (Object*, Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2), arguments->nth(3)));
    case 5: 
      return ((arguments->value->*((int  (Object::*) (Object*, Object*, Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2), arguments->nth(3), arguments->nth(4)));
    default:
      throw *newStellaException("Too many function arguments in `apply'.  Max is 5.");
      break;
  }
}

long long int applyLongIntegerMethod(cpp_method_code code, Cons* arguments) {
  // Apply `code' to `arguments', returning a value of type
  // LONG-INTEGER.
  switch (arguments->length()) {
    case 0: 
      throw *newStellaException("Can't call method code on 0 arguments.");
      break;
    case 1: 
      return ((arguments->value->*((long long int  (Object::*) ()) code)) ());
    case 2: 
      return ((arguments->value->*((long long int  (Object::*) (Object*)) code)) (arguments->rest->value));
    case 3: 
      return ((arguments->value->*((long long int  (Object::*) (Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2)));
    case 4: 
      return ((arguments->value->*((long long int  (Object::*) (Object*, Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2), arguments->nth(3)));
    case 5: 
      return ((arguments->value->*((long long int  (Object::*) (Object*, Object*, Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2), arguments->nth(3), arguments->nth(4)));
    default:
      throw *newStellaException("Too many function arguments in `apply'.  Max is 5.");
      break;
  }
}

const char* applyStringMethod(cpp_method_code code, Cons* arguments) {
  // Apply `code' to `arguments', returning a value of type
  // STRING.
  switch (arguments->length()) {
    case 0: 
      throw *newStellaException("Can't call method code on 0 arguments.");
      break;
    case 1: 
      return ((arguments->value->*((const char*  (Object::*) ()) code)) ());
    case 2: 
      return ((arguments->value->*((const char*  (Object::*) (Object*)) code)) (arguments->rest->value));
    case 3: 
      return ((arguments->value->*((const char*  (Object::*) (Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2)));
    case 4: 
      return ((arguments->value->*((const char*  (Object::*) (Object*, Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2), arguments->nth(3)));
    case 5: 
      return ((arguments->value->*((const char*  (Object::*) (Object*, Object*, Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2), arguments->nth(3), arguments->nth(4)));
    default:
      throw *newStellaException("Too many function arguments in `apply'.  Max is 5.");
      break;
  }
}

boolean applyBooleanMethod(cpp_method_code code, Cons* arguments) {
  // Apply `code' to `arguments', returning a value of type
  // BOOLEAN.
  switch (arguments->length()) {
    case 0: 
      throw *newStellaException("Can't call method code on 0 arguments.");
      break;
    case 1: 
      return ((arguments->value->*((boolean  (Object::*) ()) code)) ());
    case 2: 
      return ((arguments->value->*((boolean  (Object::*) (Object*)) code)) (arguments->rest->value));
    case 3: 
      return ((arguments->value->*((boolean  (Object::*) (Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2)));
    case 4: 
      return ((arguments->value->*((boolean  (Object::*) (Object*, Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2), arguments->nth(3)));
    case 5: 
      return ((arguments->value->*((boolean  (Object::*) (Object*, Object*, Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2), arguments->nth(3), arguments->nth(4)));
    default:
      throw *newStellaException("Too many function arguments in `apply'.  Max is 5.");
      break;
  }
}

double applyFloatMethod(cpp_method_code code, Cons* arguments) {
  // Apply `code' to `arguments', returning a value of type
  // FLOAT.
  switch (arguments->length()) {
    case 0: 
      throw *newStellaException("Can't call method code on 0 arguments.");
      break;
    case 1: 
      return ((arguments->value->*((double  (Object::*) ()) code)) ());
    case 2: 
      return ((arguments->value->*((double  (Object::*) (Object*)) code)) (arguments->rest->value));
    case 3: 
      return ((arguments->value->*((double  (Object::*) (Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2)));
    case 4: 
      return ((arguments->value->*((double  (Object::*) (Object*, Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2), arguments->nth(3)));
    case 5: 
      return ((arguments->value->*((double  (Object::*) (Object*, Object*, Object*, Object*)) code)) (arguments->rest->value, arguments->nth(2), arguments->nth(3), arguments->nth(4)));
    default:
      throw *newStellaException("Too many function arguments in `apply'.  Max is 5.");
      break;
  }
}

boolean definedTypeP(Surrogate* type) {
  { Object* value = type->surrogateValue;
    Surrogate* valuetype = NULL;

    if (((boolean)(value))) {
      valuetype = value->primaryType();
      return ((SGT_METHODS_STELLA_SURROGATE == valuetype) ||
          ((SGT_METHODS_STELLA_PARAMETRIC_TYPE_SPECIFIER == valuetype) ||
           (SGT_METHODS_STELLA_ANCHORED_TYPE_SPECIFIER == valuetype)));
    }
    return (false);
  }
}

StandardObject* realTypeSpecifier(Surrogate* type) {
  { Object* value = type->surrogateValue;

    if (definedTypeP(type)) {
      if (typeP(value)) {
        return (realTypeSpecifier(((Surrogate*)(value))));
      }
      else {
        return (((StandardObject*)(value)));
      }
    }
    else {
      return (type);
    }
  }
}

Surrogate* canonicalType(Surrogate* type) {
  { Class* clasS = ((Class*)(type->surrogateValue));

    if (((boolean)(clasS))) {
      return (clasS->classType);
    }
    else {
      return (type);
    }
  }
}

StandardObject* Surrogate::yieldTypeSpecifier() {
  { Surrogate* typespectree = this;

    return (realTypeSpecifier(typespectree));
  }
}

StandardObject* Symbol::yieldTypeSpecifier() {
  { Symbol* typespectree = this;

    return (realTypeSpecifier(typify(typespectree)));
  }
}

StandardObject* ParametricTypeSpecifier::yieldTypeSpecifier() {
  { ParametricTypeSpecifier* typespectree = this;

    return (typespectree);
  }
}

StandardObject* AnchoredTypeSpecifier::yieldTypeSpecifier() {
  { AnchoredTypeSpecifier* typespectree = this;

    return (typespectree);
  }
}

StandardObject* Object::yieldTypeSpecifier() {
  { Object* typespectree = this;

    std::cerr << "Illegal type specification " << "`" << typespectree << "'";
    return (SGT_METHODS_STELLA_OBJECT);
  }
}

StandardObject* Cons::yieldTypeSpecifier() {
  { Cons* typespectree = this;

    if (typespectree == NIL) {
      return (SGT_METHODS_STELLA_VOID);
    }
    else if (typespectree->value == SYM_METHODS_STELLA_LIKE) {
      return (yieldAnchoredTypeSpecifier(typespectree));
    }
    else {
      return (yieldParametricTypeSpecifier(typespectree));
    }
  }
}

ParametricTypeSpecifier* yieldParametricTypeSpecifier(Cons* typespectree) {
  { ParametricTypeSpecifier* typespec = newParametricTypeSpecifier();
    StandardObject* parametertypespec = NULL;
    Cons* cursor = typespectree;

    { Object* head000 = cursor->value;

      cursor = cursor->rest;
      { Surrogate* basetype = typify(head000);
        StandardObject* realbasetypespec = realTypeSpecifier(basetype);
        boolean definedbasetypeP = !(basetype == realbasetypespec);

        { Object* head001 = cursor->value;

          cursor = cursor->rest;
          { Object* operatoR = head001;
            boolean arraytypeP = false;

            if (definedbasetypeP) {
              basetype = typeSpecToBaseType(realbasetypespec);
            }
            typespec->specifierBaseType = verifyType(basetype);
            if (arrayTypeSpecifierP(typespec)) {
              if (operatoR == SYM_METHODS_STELLA_SIZE) {
                { Object* head002 = cursor->value;

                  cursor = cursor->rest;
                  operatoR = head002;
                }
              }
              arraytypeP = true;
              typespec->specifierDimensions = parseArrayDimensionsSpec(operatoR);
              { Object* head003 = cursor->value;

                cursor = cursor->rest;
                operatoR = head003;
              }
            }
            if (arraytypeP &&
                (!((boolean)(typespec->specifierDimensions)))) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal array type specifier dimensions: " << "`" << deUglifyParseTree(typespectree) << "'" << "." << std::endl;
                }
              }
              return (yieldParametricTypeSpecifier(listO(3, SYM_METHODS_STELLA_UNKNOWN, SYM_METHODS_STELLA_OF, NIL)));
            }
            if (!(operatoR == SYM_METHODS_STELLA_OF)) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Bad type specifier " << "`" << deUglifyParseTree(typespectree) << "'" << "." << std::endl;
                }
              }
              return (yieldParametricTypeSpecifier(listO(3, SYM_METHODS_STELLA_UNKNOWN, SYM_METHODS_STELLA_OF, NIL)));
            }
            { Object* p = NULL;
              Cons* iter000 = cursor;
              List* into000 = typespec->specifierParameterTypes;
              Cons* collect000 = NULL;

              for  (; !(iter000 == NIL); 
                    iter000 = iter000->rest) {
                p = iter000->value;
                parametertypespec = p->yieldTypeSpecifier();
                if (arrayTypeSpecifierP(parametertypespec)) {
                  { 
                    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                    signalTranslationError();
                    if (!(suppressWarningsP())) {
                      printErrorContext(">> ERROR: ", STANDARD_ERROR);
                      *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal nested array type specifier: " << std::endl << "   " << "`" << deUglifyParseTree(typespectree) << "'" << std::endl << "   Use multi-dimensional arrays instead" << "." << std::endl;
                    }
                  }
                  return (yieldParametricTypeSpecifier(listO(3, SYM_METHODS_STELLA_UNKNOWN, SYM_METHODS_STELLA_OF, NIL)));
                }
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(parametertypespec, NIL);
                    if (into000->theConsList == NIL) {
                      into000->theConsList = collect000;
                    }
                    else {
                      addConsToEndOfConsList(into000->theConsList, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000->rest = cons(parametertypespec, NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
            if (definedbasetypeP) {
              if (subtypeOfParametricTypeSpecifierP(safePrimaryType(realbasetypespec))) {
                { StandardObject* realbasetypespec000 = realbasetypespec;
                  ParametricTypeSpecifier* realbasetypespec = ((ParametricTypeSpecifier*)(realbasetypespec000));

                  { boolean testValue000 = false;

                    testValue000 = realbasetypespec->specifierParameterTypes->length() == typespec->specifierParameterTypes->length();
                    if (testValue000) {
                      { boolean alwaysP000 = true;

                        { StandardObject* partype = NULL;
                          Cons* iter001 = typespec->specifierParameterTypes->theConsList;
                          StandardObject* rpartype = NULL;
                          Cons* iter002 = realbasetypespec->specifierParameterTypes->theConsList;

                          for  (; (!(iter001 == NIL)) &&
                                    (!(iter002 == NIL)); 
                                iter001 = iter001->rest,
                                iter002 = iter002->rest) {
                            partype = ((StandardObject*)(iter001->value));
                            rpartype = ((StandardObject*)(iter002->value));
                            if (!optimisticSubtypeOfP(typeSpecToBaseType(partype), typeSpecToBaseType(rpartype))) {
                              alwaysP000 = false;
                              break;
                            }
                          }
                        }
                        testValue000 = alwaysP000;
                      }
                    }
                    if (!(testValue000)) {
                      { 
                        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                        signalTranslationError();
                        if (!(suppressWarningsP())) {
                          printErrorContext(">> ERROR: ", STANDARD_ERROR);
                          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Parameter types of " << "`" << deUglifyParseTree(typespectree) << "'" << " are incompatible " << std::endl << " with parameter types of defined type " << "`" << typespectree->value << "'" << "." << std::endl;
                        }
                      }
                      return (yieldParametricTypeSpecifier(listO(3, SYM_METHODS_STELLA_UNKNOWN, SYM_METHODS_STELLA_OF, NIL)));
                    }
                  }
                }
              }
              else {
              }
            }
            return (typespec);
          }
        }
      }
    }
  }
}

List* parseArrayDimensionsSpec(Object* dimensionsspec) {
  { List* dimensions = newList();

    if (!((boolean)(dimensionsspec))) {
      return (NULL);
    }
    if (!(consP(dimensionsspec) &&
        (!(dimensionsspec == NIL)))) {
      dimensionsspec = cons(dimensionsspec, NIL);
    }
    { Object* dimspec = NULL;
      Cons* iter000 = ((Cons*)(dimensionsspec));
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        dimspec = iter000->value;
        if (consP(dimspec)) {
          dimspec = ((Cons*)(dimspec))->value;
        }
        if ((dimspec == NULL) ||
            (dimspec == SYM_METHODS_STELLA_NULL)) {
          dimspec = NULL;
        }
        else if (integerP(dimspec)) {
        }
        else {
          return (NULL);
        }
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(dimspec, NIL);
            if (dimensions->theConsList == NIL) {
              dimensions->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(dimensions->theConsList, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(dimspec, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (dimensions);
  }
}

Cons* yieldArrayDimensionsTree(ParametricTypeSpecifier* arraytype) {
  { List* dimensions = arraytype->specifierDimensions;
    Cons* result = NIL;

    if (!((boolean)(dimensions))) {
      return (NULL);
    }
    { Object* dim = NULL;
      Cons* iter000 = dimensions->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        dim = iter000->value;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(((!((boolean)(dim))) ? NIL : cons(dim, NIL)), NIL);
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
            collect000->rest = cons(((!((boolean)(dim))) ? NIL : cons(dim, NIL)), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    if (result->length() == 1) {
      return (((Cons*)(result->value)));
    }
    else {
      return (result);
    }
  }
}

boolean arrayTypeSpecifierP(StandardObject* typespec) {
  if (subtypeOfParametricTypeSpecifierP(safePrimaryType(typespec))) {
    { StandardObject* typespec000 = typespec;
      ParametricTypeSpecifier* typespec = ((ParametricTypeSpecifier*)(typespec000));

      { Surrogate* basetype = typespec->specifierBaseType;

        if (basetype == SGT_METHODS_STELLA_ARRAY) {
          return (true);
        }
      }
    }
  }
  else {
  }
  return (false);
}

int arrayTypeRank(ParametricTypeSpecifier* arraytype) {
  { List* dimensions = arraytype->specifierDimensions;

    if (!((boolean)(dimensions))) {
      return (NULL_INTEGER);
    }
    else {
      return (dimensions->length());
    }
  }
}

List* arrayTypeDimensions(ParametricTypeSpecifier* arraytype) {
  return (((List*)(arraytype->specifierDimensions)));
}

boolean indefiniteArrayTypeP(ParametricTypeSpecifier* arraytype) {
  { List* dimensions = arraytype->specifierDimensions;

    if (!((boolean)(dimensions))) {
      return (true);
    }
    else {
      { Object* dim = NULL;
        Cons* iter000 = dimensions->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          dim = iter000->value;
          if (!((boolean)(dim))) {
            return (true);
          }
        }
      }
    }
    return (false);
  }
}

AnchoredTypeSpecifier* yieldAnchoredTypeSpecifier(Cons* typespectree) {
  { AnchoredTypeSpecifier* typespec = newAnchoredTypeSpecifier();
    Object* likeargument = typespectree->rest->value;

    if (!(likeargument == SYM_METHODS_STELLA_SELF)) {
      typespec->specifierParameterName = ((Symbol*)(((Cons*)(likeargument))->value->permanentify()));
    }
    return (typespec);
  }
}

void incorporateInputParameters(MethodSlot* method, Cons* parameters) {
  if (parameters == NIL) {
    return;
  }
  { Symbol* name = NULL;
    StandardObject* ts = NULL;
    Symbol* direction = NULL;
    boolean variableargsP = false;

    method->methodParameterNames = newList();
    method->methodParameterTypeSpecifiers = newList();
    { Object* p = NULL;
      Cons* iter000 = parameters;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        p = iter000->value;
        { Surrogate* testValue000 = safePrimaryType(p);

          if (testValue000 == SGT_METHODS_STELLA_CONS) {
            { Object* p000 = p;
              Cons* p = ((Cons*)(p000));

              switch (p->length()) {
                case 2: 
                  direction = SYM_METHODS_STELLA_IN;
                  break;
                case 3: 
                  if ((p->value == SYM_METHODS_STELLA_IN) ||
                      ((p->value == SYM_METHODS_STELLA_OUT) ||
                       (p->value == SYM_METHODS_STELLA_INOUT))) {
                    direction = ((Symbol*)(p->value));
                    if (nullListP(method->methodParameterDirections_reader())) {
                      setDynamicSlotValue(method->dynamicSlots, SYM_METHODS_STELLA_METHOD_PARAMETER_DIRECTIONS, newList(), NULL);
                      { Object* par = NULL;
                        Cons* iter001 = parameters;

                        for (; !(iter001 == NIL); iter001 = iter001->rest) {
                          par = iter001->value;
                          if (par == p) {
                            goto loopExit091;
                          }
                          else {
                            method->methodParameterDirections_reader()->insert(SYM_METHODS_STELLA_IN);
                          }
                        }
                      }
                      loopExit091:;
                    }
                  }
                  else {
                    { 
                      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                      signalTranslationError();
                      if (!(suppressWarningsP())) {
                        printErrorContext(">> ERROR: ", STANDARD_ERROR);
                        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal direction for method parameter: " << "`" << deUglifyParseTree(p) << "'" << "." << std::endl;
                      }
                    }
                    direction = SYM_METHODS_STELLA_IN;
                  }
                  p = p->rest;
                  break;
                default:
                  { 
                    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                    signalTranslationError();
                    if (!(suppressWarningsP())) {
                      printErrorContext(">> ERROR: ", STANDARD_ERROR);
                      *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal method parameter: " << "`" << deUglifyParseTree(p) << "'" << "." << std::endl;
                    }
                  }
                  continue;
                  break;
              }
              if (variableargsP) {
                { Cons* varargtype = listO(4, SYM_METHODS_STELLA_ARGUMENT_LIST, SYM_METHODS_STELLA_OF, p->rest->value, NIL);

                  name = ((Symbol*)(p->value));
                  ts = varargtype->yieldTypeSpecifier();
                }
              }
              else {
                {
                  if (!(symbolP(p->value) &&
                      (symbolP(p->rest->value) ||
                       (surrogateP(p->rest->value) ||
                        consP(p->rest->value))))) {
                    { 
                      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                      signalTranslationError();
                      if (!(suppressWarningsP())) {
                        printErrorContext(">> ERROR: ", STANDARD_ERROR);
                        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal method parameter: " << "`" << deUglifyParseTree(p) << "'" << "." << std::endl;
                      }
                    }
                    continue;
                  }
                  name = ((Symbol*)(p->value));
                  ts = p->rest->value->yieldTypeSpecifier();
                }
              }
            }
          }
          else if (subtypeOfSymbolP(testValue000)) {
            { Object* p001 = p;
              Symbol* p = ((Symbol*)(p001));

              if (p == SYM_METHODS_STELLA_aREST) {
                setDynamicSlotValue(method->dynamicSlots, SYM_METHODS_STELLA_METHOD_VARIABLE_ARGUMENTSp, TRUE_WRAPPER, FALSE_WRAPPER);
                variableargsP = true;
                continue;
              }
              else if (p == SYM_METHODS_STELLA_aBODY) {
                setDynamicSlotValue(method->dynamicSlots, SYM_METHODS_STELLA_METHOD_BODY_ARGUMENTp, TRUE_WRAPPER, FALSE_WRAPPER);
                continue;
              }
              else {
                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  signalTranslationError();
                  if (!(suppressWarningsP())) {
                    printErrorContext(">> ERROR: ", STANDARD_ERROR);
                    *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Untyped parameter in parameter list: " << "`" << deUglifyParseTree(parameters) << "'" << "." << std::endl;
                  }
                }
                name = p;
                ts = SGT_METHODS_STELLA_UNKNOWN;
              }
            }
          }
          else {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal parameter list: " << "`" << deUglifyParseTree(parameters) << "'" << "." << std::endl;
              }
            }
            continue;
          }
        }
        method->methodParameterTypeSpecifiers_reader()->insert(ts);
        method->methodParameterNames_reader()->insert(((Symbol*)(name->permanentify())));
        if (definedListP(method->methodParameterDirections_reader())) {
          method->methodParameterDirections_reader()->insert(direction);
        }
      }
    }
    method->methodParameterNames_reader()->reverse();
    method->methodParameterTypeSpecifiers_reader()->reverse();
    method->methodParameterDirections_reader()->reverse();
  }
}

void incorporateFirstInputParameter(MethodSlot* method) {
  { List* parametertypespecs = method->methodParameterTypeSpecifiers_reader();
    StandardObject* firstargtype = ((StandardObject*)(parametertypespecs->first()));

    if (!method->methodFunctionP) {
      if (parametertypespecs->emptyP()) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Method has no input parameters, converting it into a function" << "." << std::endl;
          }
        }
        method->methodFunctionP = true;
        return;
      }
      else if (((boolean)(firstargtype)) &&
          (!typeP(firstargtype))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal complex argument type for the first method parameter: " << std::endl << "   " << "`" << deUglifyParseTree(firstargtype) << "'" << "." << std::endl;
          }
        }
        if (anchoredTypeSpecifierP(firstargtype)) {
          method->methodParameterTypeSpecifiers_reader()->firstSetter(SGT_METHODS_STELLA_UNKNOWN);
          firstargtype = SGT_METHODS_STELLA_UNKNOWN;
        }
      }
    }
    method->slotOwner = (((boolean)(firstargtype)) ? typeSpecToBaseType(firstargtype) : NULL);
  }
}

MethodSlot* defineStellaMethodSlot(Symbol* inputname, Cons* returntypes, boolean functionP, Cons* inputparameters, KeywordKeyValueList* options) {
  // Define a new Stella method object (a slot), and attach it
  // to the class identified by the first parameter in 'inputParameters'.
  { MethodSlot* newmethod = newMethodSlot();
    Symbol* name = ((Symbol*)(inputname->permanentify()));

    newmethod->slotName = name;
    newmethod->methodFunctionP = functionP;
    incorporateInputParameters(newmethod, inputparameters);
    incorporateFirstInputParameter(newmethod);
    if (returntypes == NIL) {
      if (((boolean)(options->lookup(KWD_METHODS_TYPE)))) {
        returntypes = cons(options->lookup(KWD_METHODS_TYPE), NIL);
      }
      else if (((boolean)(options->lookup(KWD_METHODS_RETURN_TYPES)))) {
        returntypes = cons(options->lookup(KWD_METHODS_RETURN_TYPES), NIL);
      }
    }
    { StandardObject* typespec = ((returntypes == NIL) ? SGT_METHODS_STELLA_VOID : ((StandardObject*)(returntypes->value->yieldTypeSpecifier())));

      if (typeP(typespec)) {
        newmethod->slotBaseType = ((Surrogate*)(typespec));
      }
      else {
        setDynamicSlotValue(newmethod->dynamicSlots, SYM_METHODS_STELLA_SLOT_TYPE_SPECIFIER, ((CompoundTypeSpecifier*)(typespec)), NULL);
      }
    }
    if (!(returntypes == NIL)) {
      newmethod->methodReturnTypeSpecifiers = newList();
    }
    { Object* ts = NULL;
      Cons* iter000 = returntypes;
      List* into000 = newmethod->methodReturnTypeSpecifiers_reader();
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        ts = iter000->value;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(ts->yieldTypeSpecifier(), NIL);
            if (into000->theConsList == NIL) {
              into000->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(into000->theConsList, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(ts->yieldTypeSpecifier(), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    { Keyword* key = NULL;
      Object* value = NULL;
      KvListIterator* iter001 = ((KvListIterator*)(options->allocateIterator()));

      for  (; iter001->nextP(); ) {
        key = ((Keyword*)(iter001->key));
        value = iter001->value;
        { Keyword* testValue000 = ((Keyword*)(key));

          if (testValue000 == KWD_METHODS_PUBLICp) {
            newmethod->slotPublicP = ((BooleanWrapper*)(value))->wrapperValue;
          }
          else if (testValue000 == KWD_METHODS_ABSTRACTp) {
            newmethod->abstractP = ((BooleanWrapper*)(value))->wrapperValue;
          }
          else if (testValue000 == KWD_METHODS_NATIVEp) {
            setDynamicSlotValue(newmethod->dynamicSlots, SYM_METHODS_STELLA_METHOD_NATIVEp, (((BooleanWrapper*)(value))->wrapperValue ? TRUE_WRAPPER : FALSE_WRAPPER), FALSE_WRAPPER);
          }
          else if (testValue000 == KWD_METHODS_CONSTRUCTORp) {
            setDynamicSlotValue(newmethod->dynamicSlots, SYM_METHODS_STELLA_METHOD_CONSTRUCTORp, (((BooleanWrapper*)(value))->wrapperValue ? TRUE_WRAPPER : FALSE_WRAPPER), FALSE_WRAPPER);
          }
          else if (testValue000 == KWD_METHODS_GLOBALLY_INLINEp) {
            setDynamicSlotValue(newmethod->dynamicSlots, SYM_METHODS_STELLA_METHOD_GLOBALLY_INLINEp, (((BooleanWrapper*)(value))->wrapperValue ? TRUE_WRAPPER : FALSE_WRAPPER), FALSE_WRAPPER);
          }
          else if (testValue000 == KWD_METHODS_INLINE) {
            if (newmethod->methodInlinedFunctions_reader()->emptyP()) {
              setDynamicSlotValue(newmethod->dynamicSlots, SYM_METHODS_STELLA_METHOD_INLINED_FUNCTIONS, newList(), NULL);
            }
            { Surrogate* testValue001 = safePrimaryType(value);

              if (testValue001 == SGT_METHODS_STELLA_CONS) {
                { Object* value000 = value;
                  Cons* value = ((Cons*)(value000));

                  { Object* fnname = NULL;
                    Cons* iter002 = value;

                    for (; !(iter002 == NIL); iter002 = iter002->rest) {
                      fnname = iter002->value;
                      newmethod->methodInlinedFunctions_reader()->insert(((Symbol*)(fnname)));
                    }
                  }
                }
              }
              else if (subtypeOfSymbolP(testValue001)) {
                { Object* value001 = value;
                  Symbol* value = ((Symbol*)(value001));

                  newmethod->methodInlinedFunctions_reader()->insert(value);
                }
              }
              else {
                *(STANDARD_WARNING->nativeStream) << "Warning: " << "Illegal :inline argument: " << "`" << value << "'" << std::endl;
              }
            }
          }
          else if (testValue000 == KWD_METHODS_AUXILIARYp) {
            setDynamicSlotValue(newmethod->dynamicSlots, SYM_METHODS_STELLA_SLOT_AUXILIARYp, (((BooleanWrapper*)(value))->wrapperValue ? TRUE_WRAPPER : FALSE_WRAPPER), FALSE_WRAPPER);
          }
          else if (testValue000 == KWD_METHODS_DOCUMENTATION) {
            setDynamicSlotValue(newmethod->dynamicSlots, SYM_METHODS_STELLA_DOCUMENTATION, wrapString(((StringWrapper*)(value))->wrapperValue), NULL_STRING_WRAPPER);
          }
          else if ((testValue000 == KWD_METHODS_TYPE) ||
              (testValue000 == KWD_METHODS_RETURNS)) {
          }
          else if (testValue000 == KWD_METHODS_STORAGE_SLOT) {
            setDynamicSlotValue(newmethod->dynamicSlots, SYM_METHODS_STELLA_STORAGE_SLOT, ((Symbol*)(((Symbol*)(value))->permanentify())), NULL);
          }
          else if (testValue000 == KWD_METHODS_INHERITS_THROUGH) {
            setDynamicSlotValue(newmethod->dynamicSlots, SYM_METHODS_STELLA_METHOD_INHERITS_THROUGH, ((Symbol*)(((Symbol*)(value))->permanentify())), NULL);
          }
          else if (testValue000 == KWD_METHODS_PROPERTIES) {
            setDynamicSlotValue(newmethod->dynamicSlots, SYM_METHODS_STELLA_PROPERTIES, ((List*)(value)), NULL);
          }
          else if (testValue000 == KWD_METHODS_META_ATTRIBUTES) {
            setDynamicSlotValue(newmethod->dynamicSlots, SYM_METHODS_STELLA_META_ATTRIBUTES, ((KeyValueList*)(value)), NULL);
          }
          else if (testValue000 == KWD_METHODS_COMMANDp) {
            setDynamicSlotValue(newmethod->dynamicSlots, SYM_METHODS_STELLA_METHOD_COMMANDp, (((BooleanWrapper*)(value))->wrapperValue ? TRUE_WRAPPER : FALSE_WRAPPER), FALSE_WRAPPER);
          }
          else if (testValue000 == KWD_METHODS_LISP_MACROp) {
            setDynamicSlotValue(newmethod->dynamicSlots, SYM_METHODS_STELLA_METHOD_LISP_MACROp, (((BooleanWrapper*)(value))->wrapperValue ? TRUE_WRAPPER : FALSE_WRAPPER), NULL);
          }
          else if (testValue000 == KWD_METHODS_EVALUATE_ARGUMENTSp) {
            setDynamicSlotValue(newmethod->dynamicSlots, SYM_METHODS_STELLA_METHOD_EVALUATE_ARGUMENTSp, (((BooleanWrapper*)(value))->wrapperValue ? TRUE_WRAPPER : FALSE_WRAPPER), FALSE_WRAPPER);
          }
          else if (testValue000 == KWD_METHODS_C_CALLABLEp) {
            setDynamicSlotValue(newmethod->dynamicSlots, SYM_METHODS_STELLA_METHOD_C_CALLABLEp, (((BooleanWrapper*)(value))->wrapperValue ? TRUE_WRAPPER : FALSE_WRAPPER), FALSE_WRAPPER);
          }
          else {
            if (!(runOptionHandlerP(newmethod, key, value))) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationWarning();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> WARNING: ", STANDARD_WARNING);
                  *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Skipping invalid method option " << "`" << deUglifyParseTree(key) << "'" << std::endl << "in the definition of method " << "`" << newmethod->slotOwner << "'" << "." << "`" << deUglifyParseTree(name) << "'" << "." << std::endl;
                }
              }
            }
          }
        }
      }
    }
    return (newmethod);
  }
}

MethodSlot* attachMethodSlotToOwner(MethodSlot* newmethod) {
  if (newmethod->methodFunctionP) {
    return (attachFunction(newmethod));
  }
  if (!((boolean)(newmethod->slotOwner->surrogateValue))) {
    return (newmethod);
  }
  if (!undefineConflictingDefinitionsP(newmethod)) {
    return (NULL);
  }
  return (((MethodSlot*)(attachSlotToOwner(newmethod))));
}

// Maximum size for a string constant in the target language.
int oMAXIMUM_STRING_CONSTANT_SIZEo = 4000;

Object* yieldStringConstantTree(const char* string) {
  { int length = strlen(string);
    Cons* chunks = NIL;
    int start = 0;
    Object* stringtree = NULL;

    if (length <= oMAXIMUM_STRING_CONSTANT_SIZEo) {
      return (wrapString(string));
    }
    while ((start + oMAXIMUM_STRING_CONSTANT_SIZEo) < length) {
      chunks = cons(wrapString(stringSubsequence(string, start, start + oMAXIMUM_STRING_CONSTANT_SIZEo)), chunks);
      start = start + oMAXIMUM_STRING_CONSTANT_SIZEo;
    }
    if (start < length) {
      chunks = cons(wrapString(stringSubsequence(string, start, length)), chunks);
    }
    stringtree = chunks->value;
    { Object* chunk = NULL;
      Cons* iter000 = chunks->rest;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        chunk = iter000->value;
        stringtree = listO(3, SYM_METHODS_STELLA_CONCATENATE, chunk, cons(stringtree, NIL));
      }
    }
    return (stringtree);
  }
}

boolean defineFunctionObjectEagerlyP(MethodSlot* function) {
  { Class* methodclass = ((Class*)(SGT_METHODS_STELLA_METHOD_SLOT->surrogateValue));
    StorageSlot* slot = NULL;

    { Object* slotname = NULL;
      Object* value = NULL;
      KvCons* iter000 = function->dynamicSlots->theKvList;

      for  (; ((boolean)(iter000)); 
            iter000 = iter000->rest) {
        slotname = iter000->key;
        value = iter000->value;
        value = value;
        slot = ((StorageSlot*)(lookupSlot(methodclass, ((Symbol*)(slotname)))));
        if (((boolean)(slot)) &&
            ((boolean)(((Symbol*)(dynamicSlotValue(slot->dynamicSlots, SYM_METHODS_STELLA_SLOT_OPTION_HANDLER, NULL)))))) {
          return (true);
        }
      }
    }
    return (false);
  }
}

Cons* yieldDefineStellaMethodObject(MethodSlot* method, MethodSlot* codemethod, MethodSlot* wrappermethod) {
  { Object* name = wrapString(stringify(method->slotName));

    if (method->methodFunctionP) {
      if (defineFunctionObjectEagerlyP(method)) {
        name = SYM_METHODS_STELLA_NULL;
      }
      else if (!eqlToStringP(name, method->slotName->symbolName)) {
        name = wrapString(stringConcatenate(" ", ((StringWrapper*)(name))->wrapperValue, 0));
      }
      return (listO(3, SYM_METHODS_STELLA_DEFINE_FUNCTION_OBJECT, name, cons(yieldStringConstantTree(method->methodStringifiedSource), cons((((boolean)(codemethod)) ? ((StandardObject*)(listO(4, SYM_METHODS_STELLA_THE_CODE, KWD_METHODS_FUNCTION, codemethod->slotName, NIL))) : ((StandardObject*)(SYM_METHODS_STELLA_NULL))), cons((((boolean)(wrappermethod)) ? ((StandardObject*)(listO(4, SYM_METHODS_STELLA_THE_CODE, KWD_METHODS_FUNCTION, wrappermethod->slotName, cons(wrappermethod, NIL)))) : ((StandardObject*)(SYM_METHODS_STELLA_NULL))), NIL)))));
    }
    else if (inlineMethodP(method)) {
      return (listO(3, SYM_METHODS_STELLA_DEFINE_INLINE_METHOD_CODE, method->slotOwner, listO(3, listO(3, SYM_METHODS_STELLA_QUOTE, method->slotName, NIL), (((boolean)(codemethod)) ? ((StandardObject*)(listO(4, SYM_METHODS_STELLA_THE_CODE, KWD_METHODS_METHOD, codemethod->slotOwner, cons(codemethod->slotName, NIL)))) : ((StandardObject*)(SYM_METHODS_STELLA_NULL))), cons(SYM_METHODS_STELLA_NULL, NIL))));
    }
    else {
      return (listO(3, SYM_METHODS_STELLA_DEFINE_METHOD_OBJECT, yieldStringConstantTree(method->methodStringifiedSource), cons((((boolean)(codemethod)) ? ((StandardObject*)(listO(4, SYM_METHODS_STELLA_THE_CODE, KWD_METHODS_METHOD, codemethod->slotOwner, cons(codemethod->slotName, NIL)))) : ((StandardObject*)(SYM_METHODS_STELLA_NULL))), cons(SYM_METHODS_STELLA_NULL, NIL))));
    }
  }
}

Cons* yieldClassParameterTypes(Class* clasS) {
  { Cons* types = NIL;

    { Symbol* pname = NULL;
      Cons* iter000 = clasS->parameters()->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        pname = ((Symbol*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(lookupSlot(clasS, pname)->slotBaseType, NIL);
            if (types == NIL) {
              types = collect000;
            }
            else {
              addConsToEndOfConsList(types, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(lookupSlot(clasS, pname)->slotBaseType, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (types);
  }
}

boolean optimisticSubtypeOfP(Surrogate* subtype, Surrogate* supertype) {
  if (((boolean)(((Class*)(subtype->surrogateValue)))) &&
      (((boolean)(((Class*)(supertype->surrogateValue)))) &&
       ((Class*)(subtype->surrogateValue))->classFinalizedP)) {
    return (subtypeOfP(subtype, supertype));
  }
  else {
    return (true);
  }
}

void warnOfParameterMismatch(ParametricTypeSpecifier* self, const char* message) {
  { Cons* inheritedtypes = yieldClassParameterTypes(((Class*)(self->specifierBaseType->surrogateValue)));

    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "`" << message << "'" << std::endl << "Type " << "`" << self->specifierBaseType << "'" << " takes parameters of type " << std::endl << "`" << inheritedtypes << "'" << " but was modified by a list of types " << "`" << self->specifierParameterTypes->theConsList << "'" << std::endl;
    }
  }
}

Surrogate* validateTypeSpecifier(StandardObject* self, Class* anchorclass, boolean skipanchoredtypeP) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfParametricTypeSpecifierP(testValue000)) {
      { StandardObject* self000 = self;
        ParametricTypeSpecifier* self = ((ParametricTypeSpecifier*)(self000));

        if (!((boolean)(((Class*)(self->specifierBaseType->surrogateValue))))) {
          return (SGT_METHODS_STELLA_UNKNOWN);
        }
        { int parameterdifferential = self->specifierParameterTypes->length() - ((Class*)(self->specifierBaseType->surrogateValue))->parameters()->length();

          if (parameterdifferential > 0) {
            warnOfParameterMismatch(self, "Too many parameters in type specification.");
          }
          else if (parameterdifferential < 0) {
            warnOfParameterMismatch(self, "Not enough parameters in type specification.");
          }
          else {
            { Class* baseclass = ((Class*)(typeSpecToBaseType(self)->surrogateValue));

              if (baseclass->classSlotsFinalizedP) {
                { Cons* inheritedtypes = yieldClassParameterTypes(baseclass);

                  { Surrogate* supertype = NULL;
                    Cons* iter000 = inheritedtypes;
                    StandardObject* subtypespec = NULL;
                    Cons* iter001 = self->specifierParameterTypes->theConsList;

                    for  (; (!(iter000 == NIL)) &&
                              (!(iter001 == NIL)); 
                          iter000 = iter000->rest,
                          iter001 = iter001->rest) {
                      supertype = ((Surrogate*)(iter000->value));
                      subtypespec = ((StandardObject*)(iter001->value));
                      if ((!anchoredTypeSpecifierP(subtypespec)) &&
                          ((!(supertype == SGT_METHODS_STELLA_UNKNOWN)) &&
                           (!optimisticSubtypeOfP(typeSpecToBaseType(subtypespec), supertype)))) {
                        warnOfParameterMismatch(self, "Parametric subtype(s) don't specialize supertype(s)");
                      }
                    }
                  }
                }
              }
            }
          }
          return (self->specifierBaseType);
        }
      }
    }
    else if (subtypeOfAnchoredTypeSpecifierP(testValue000)) {
      { StandardObject* self001 = self;
        AnchoredTypeSpecifier* self = ((AnchoredTypeSpecifier*)(self001));

        if (skipanchoredtypeP) {
          return (NULL);
        }
        if (!((boolean)(anchorclass))) {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "Illegal use of anchored type for function that has no first\nargument (and hence nothing to anchor onto)." << std::endl;
          return (NULL);
        }
        { Symbol* slotname = self->specifierParameterName;
          Slot* anchorslot = NULL;

          if (!((boolean)(slotname))) {
            return (anchorclass->classType);
          }
          { 
            anchorslot = lookupSlot(anchorclass, slotname);
            if (!(((boolean)(anchorslot)))) {
              std::cerr << "Can't find a slot named " << "`" << slotname << "'" << " on the class " << "`" << className(anchorclass) << "'";
            }
          }
          return (anchorslot->slotBaseType);
        }
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { StandardObject* self002 = self;
        Surrogate* self = ((Surrogate*)(self002));

        return (self);
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "validate-type-specifier: Not defined on " << "`" << self << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Cons* synthesizeMethodBody(MethodSlot* method) {
  if (!((boolean)(((Class*)(SGT_METHODS_STELLA_BOOLEAN->surrogateValue))))) {
    return (NIL);
  }
  { Symbol* storageslotname = ((Symbol*)(dynamicSlotValue(method->dynamicSlots, SYM_METHODS_STELLA_STORAGE_SLOT, NULL)));
    Symbol* inheritanceslotname = ((Symbol*)(dynamicSlotValue(method->dynamicSlots, SYM_METHODS_STELLA_METHOD_INHERITS_THROUGH, NULL)));
    StorageSlot* storageslot = NULL;
    Slot* inheritanceslot = NULL;
    Object* defaultvalue = NULL;

    if (inheritanceslotname == SYM_METHODS_STELLA_SUPER_CLASSES) {
      inheritanceslotname = SYM_METHODS_STELLA_CLASS_ALL_SUPER_CLASSES;
    }
    else if (inheritanceslotname == SYM_METHODS_STELLA_EQUIVALENT_SLOT) {
      inheritanceslotname = SYM_METHODS_STELLA_SLOT_DIRECT_EQUIVALENT;
    }
    else {
    }
    storageslot = ((StorageSlot*)(lookupSlot(((Class*)(method->slotOwner->surrogateValue)), storageslotname)));
    if (!((boolean)(storageslot))) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << ":storage-slot references non-existent slot " << "`" << storageslotname << "'" << " on the class " << "`" << method->slotOwner << "'" << std::endl;
      return (NIL);
    }
    inheritanceslot = lookupSlot(((Class*)(method->slotOwner->surrogateValue)), inheritanceslotname);
    if (!((boolean)(inheritanceslot))) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << ":inherits-through references non-existent slot " << "`" << inheritanceslotname << "'" << " on the class " << "`" << method->slotOwner << "'" << std::endl;
      return (NIL);
    }
    defaultvalue = storageslot->systemDefaultValue();
    return (cons(listO(4, SYM_METHODS_STELLA_LET, listO(3, listO(3, SYM_METHODS_STELLA_CURSOR, SYM_METHODS_STELLA_SELF, NIL), listO(3, SYM_METHODS_STELLA_VALUE, listO(4, SYM_METHODS_STELLA_SLOT_VALUE, SYM_METHODS_STELLA_CURSOR, storageslotname, NIL), NIL), NIL), listO(5, SYM_METHODS_STELLA_LOOP, cons(SYM_METHODS_STELLA_WHEN, ((subtypeOfP(storageslot->type(), SGT_METHODS_STELLA_BOOLEAN) ? cons(SYM_METHODS_STELLA_VALUE, NIL) : cons(listO(3, SYM_METHODS_STELLA_DEFINEDp, SYM_METHODS_STELLA_VALUE, NIL), NIL)))->concatenate(cons(listO(3, SYM_METHODS_STELLA_RETURN, SYM_METHODS_STELLA_VALUE, NIL), NIL), 0)), listO(4, SYM_METHODS_STELLA_SETQ, SYM_METHODS_STELLA_CURSOR, ((subtypeOfP(inheritanceslot->type(), SGT_METHODS_STELLA_COLLECTION) ||
        subtypeOfP(inheritanceslot->type(), SGT_METHODS_STELLA_CONS)) ? listO(3, SYM_METHODS_STELLA_FIRST, cons(inheritanceslotname, cons(SYM_METHODS_STELLA_CURSOR, NIL)), NIL) : cons(inheritanceslotname, cons(SYM_METHODS_STELLA_CURSOR, NIL))), NIL), listO(5, SYM_METHODS_STELLA_IF, listO(3, SYM_METHODS_STELLA_DEFINEDp, SYM_METHODS_STELLA_CURSOR, NIL), listO(4, SYM_METHODS_STELLA_SETQ, SYM_METHODS_STELLA_VALUE, listO(4, SYM_METHODS_STELLA_SLOT_VALUE, SYM_METHODS_STELLA_CURSOR, storageslotname, NIL), NIL), listO(3, SYM_METHODS_STELLA_RETURN, (((boolean)(defaultvalue)) ? defaultvalue : SYM_METHODS_STELLA_NULL), NIL), NIL), NIL), NIL), NIL));
  }
}

void MethodSlot::finalizeSlotTypeComputations() {
  { MethodSlot* self = this;

    { Class* ownerclass = (((boolean)(self->slotOwner)) ? ((Class*)(self->slotOwner->surrogateValue)) : ((Class*)(NULL)));

      { StandardObject* ts = NULL;
        Cons* iter000 = self->methodParameterTypeSpecifiers_reader()->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          ts = ((StandardObject*)(iter000->value));
          validateTypeSpecifier(ts, ownerclass, false);
        }
      }
      if (((boolean)(((CompoundTypeSpecifier*)(dynamicSlotValue(self->dynamicSlots, SYM_METHODS_STELLA_SLOT_TYPE_SPECIFIER, NULL)))))) {
        self->slotBaseType = validateTypeSpecifier(((CompoundTypeSpecifier*)(dynamicSlotValue(self->dynamicSlots, SYM_METHODS_STELLA_SLOT_TYPE_SPECIFIER, NULL))), ownerclass, false);
      }
      { StandardObject* ts = NULL;
        Cons* iter001 = self->methodReturnTypeSpecifiers_reader()->rest();

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          ts = ((StandardObject*)(iter001->value));
          validateTypeSpecifier(ts, ownerclass, false);
        }
      }
    }
  }
}

void MethodSlot::helpFinalizeLocalSlot() {
  { MethodSlot* self = this;

  }
}

void MethodSlot::unfinalizeLocalSlot() {
  { MethodSlot* self = this;

  }
}

void undefineExternalSlots(Symbol* name) {
  { Cons* slots = NIL;

    { Module* module = NULL;
      Iterator* iter000 = allModules();

      for (; iter000->nextP(); ) {
        module = ((Module*)(iter000->value));
        { Slot* slot = NULL;
          Iterator* iter001 = allSlots(module, true);
          Cons* collect000 = NULL;

          for  (; iter001->nextP(); ) {
            slot = ((Slot*)(iter001->value));
            if ((slot->slotName == name) &&
                slot->slotExternalP) {
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(slot, NIL);
                  if (slots == NIL) {
                    slots = collect000;
                  }
                  else {
                    addConsToEndOfConsList(slots, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(slot, NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
        }
      }
    }
    { Object* slot = NULL;
      Cons* iter002 = slots;

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        slot = iter002->value;
        destroyExternalSlot(((Slot*)(slot)));
      }
    }
  }
}

void destroyExternalSlot(Slot* self) {
  if (!(self->deletedP() ||
      (coerceWrappedBooleanToBoolean(self->badP_reader()) ||
       (!self->slotExternalP)))) {
    { Class* ownerclass = ((Class*)(self->slotOwner->surrogateValue));

      if (((boolean)(ownerclass))) {
        ownerclass->classLocalSlots->remove(self);
        unfinalizeClassSlots(ownerclass);
        self->deletedPSetter(true);
      }
    }
  }
}

void destroyMethod(MethodSlot* self) {
  destroyExternalSlot(self);
}

int Slot::methodArgumentCount() {
  { Slot* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "method-argument-count: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

int StorageSlot::methodArgumentCount() {
  { StorageSlot* self = this;

    return (1);
  }
}

int MethodSlot::methodArgumentCount() {
  { MethodSlot* self = this;

    return (self->methodParameterNames_reader()->length());
  }
}

int Table::methodArgumentCount() {
  { Table* self = this;

    return (self->tupleDomains->length() - 1);
  }
}

boolean StorageSlot::methodVariableArgumentsP() {
  { StorageSlot* self = this;

    return (false);
  }
}

boolean StorageSlot::methodBodyArgumentP() {
  { StorageSlot* self = this;

    return (false);
  }
}

int StorageSlot::arity() {
  { StorageSlot* self = this;

    return (2);
  }
}

int MethodSlot::arity() {
  { MethodSlot* self = this;

    if (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_METHODS_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue) {
      return (NULL_INTEGER);
    }
    { int returntypecount = self->methodReturnTypeSpecifiers_reader()->length();
      int result = self->methodParameterTypeSpecifiers_reader()->length() + returntypecount;

      switch (returntypecount) {
        case 1: 
          if (((StandardObject*)(self->methodReturnTypeSpecifiers_reader()->first())) == SGT_METHODS_STELLA_BOOLEAN) {
            return (result - 1);
          }
          else {
            return (result);
          }
          break;
        case 0: 
          return (result);
        default:
          if (((StandardObject*)(self->methodReturnTypeSpecifiers_reader()->last())) == SGT_METHODS_STELLA_BOOLEAN) {
            return (result - 1);
          }
          else {
            return (result);
          }
          break;
      }
    }
  }
}

int Table::arity() {
  { Table* self = this;

    if (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_METHODS_STELLA_VARIABLE_ARITY_TABLEp, FALSE_WRAPPER)))->wrapperValue) {
      return (NULL_INTEGER);
    }
    else {
      return (self->tupleDomains->length());
    }
  }
}

Surrogate* typeSpecToBaseType(StandardObject* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfSurrogateP(testValue000)) {
      { StandardObject* self000 = self;
        Surrogate* self = ((Surrogate*)(self000));

        return (self);
      }
    }
    else if (subtypeOfParametricTypeSpecifierP(testValue000)) {
      { StandardObject* self001 = self;
        ParametricTypeSpecifier* self = ((ParametricTypeSpecifier*)(self001));

        return (self->specifierBaseType);
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "type-spec-to-base-type: Not defined on " << "`" << self << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

StandardObject* baseTypeToTypeSpec(StandardObject* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfSurrogateP(testValue000)) {
      { StandardObject* self000 = self;
        Surrogate* self = ((Surrogate*)(self000));

        { Class* clasS = ((Class*)(self->surrogateValue));
          List* parameters = clasS->parameters();
          StandardObject* parametertype = NULL;
          List* parametertypes = NULL;

          if (parameters->nonEmptyP()) {
            parametertypes = newList();
            { Symbol* parameter = NULL;
              Cons* iter000 = parameters->theConsList;
              Cons* collect000 = NULL;

              for  (; !(iter000 == NIL); 
                    iter000 = iter000->rest) {
                parameter = ((Symbol*)(iter000->value));
                parametertype = lookupSlot(clasS, parameter)->computeReturnTypeSpec(self);
                if (unknownTypeP(((Surrogate*)(parametertype)))) {
                  return (self);
                }
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(parametertype, NIL);
                    if (parametertypes->theConsList == NIL) {
                      parametertypes->theConsList = collect000;
                    }
                    else {
                      addConsToEndOfConsList(parametertypes->theConsList, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000->rest = cons(parametertype, NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
            { ParametricTypeSpecifier* self003 = newParametricTypeSpecifier();

              self003->specifierBaseType = self;
              self003->specifierParameterTypes = parametertypes;
              { ParametricTypeSpecifier* value000 = self003;

                return (value000);
              }
            }
          }
          return (self);
        }
      }
    }
    else if (subtypeOfParametricTypeSpecifierP(testValue000)) {
      { StandardObject* self001 = self;
        ParametricTypeSpecifier* self = ((ParametricTypeSpecifier*)(self001));

        return (self);
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "base-type-to-type-spec: Not defined on " << "`" << self << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Class* typeSpecToClass(StandardObject* self) {
  return (((Class*)(typeSpecToBaseType(self)->surrogateValue)));
}

boolean compatibleParameterTypesP(StandardObject* subtype, StandardObject* supertype) {
  { boolean dummy1;
    boolean dummy2;

    if (typeP(subtype) ||
        typeP(supertype)) {
      return (true);
    }
    { Class* subclass = NULL;
      Class* superclass = NULL;

      { Surrogate* testValue000 = safePrimaryType(subtype);

        if (subtypeOfSurrogateP(testValue000)) {
          { StandardObject* subtype000 = subtype;
            Surrogate* subtype = ((Surrogate*)(subtype000));

            subclass = ((Class*)(subtype->surrogateValue));
          }
        }
        else if (subtypeOfParametricTypeSpecifierP(testValue000)) {
          { StandardObject* subtype001 = subtype;
            ParametricTypeSpecifier* subtype = ((ParametricTypeSpecifier*)(subtype001));

            subclass = ((Class*)(subtype->specifierBaseType->surrogateValue));
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      { Surrogate* testValue001 = safePrimaryType(supertype);

        if (subtypeOfSurrogateP(testValue001)) {
          { StandardObject* supertype000 = supertype;
            Surrogate* supertype = ((Surrogate*)(supertype000));

            superclass = ((Class*)(supertype->surrogateValue));
          }
        }
        else if (subtypeOfParametricTypeSpecifierP(testValue001)) {
          { StandardObject* supertype001 = supertype;
            ParametricTypeSpecifier* supertype = ((ParametricTypeSpecifier*)(supertype001));

            superclass = ((Class*)(supertype->specifierBaseType->surrogateValue));
          }
        }
        else {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
            throw *newStellaException(stream001->theStringReader());
          }
        }
      }
      { Symbol* suppar = NULL;
        Cons* iter000 = superclass->parameters()->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          suppar = ((Symbol*)(iter000->value));
          { boolean foundP000 = false;

            { Symbol* subpar = NULL;
              Cons* iter001 = subclass->parameters()->theConsList;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                subpar = ((Symbol*)(iter001->value));
                if (suppar == subpar) {
                  foundP000 = true;
                  break;
                }
              }
            }
            if (!(foundP000)) {
              return (false);
            }
          }
          { StandardObject* subpartype = extractParameterType(subtype, suppar, dummy1);
            StandardObject* suppartype = extractParameterType(supertype, suppar, dummy2);

            if (subpartype == suppartype) {
              continue;
            }
            if ((!anchoredTypeSpecifierP(subpartype)) &&
                (!((boolean)(((Class*)(typeSpecToBaseType(subpartype)->surrogateValue)))))) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Parameter type " << "`" << typeSpecToBaseType(subpartype) << "'" << " of " << "`" << deUglifyParseTree(subtype) << "'" << " is not yet defined" << "." << std::endl;
                }
              }
              return (false);
            }
            if ((!anchoredTypeSpecifierP(suppartype)) &&
                (!((boolean)(((Class*)(typeSpecToBaseType(suppartype)->surrogateValue)))))) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Parameter type " << "`" << typeSpecToBaseType(suppartype) << "'" << " of " << "`" << deUglifyParseTree(supertype) << "'" << " is not yet defined" << "." << std::endl;
                }
              }
              return (false);
            }
            if (!(subTypeSpecOfP(subpartype, suppartype))) {
              return (false);
            }
          }
        }
      }
      return (true);
    }
  }
}

boolean subTypeSpecOfP(StandardObject* subtype, StandardObject* supertype) {
  if (subtype == supertype) {
    return (true);
  }
  { Surrogate* testValue000 = safePrimaryType(subtype);

    if (subtypeOfSurrogateP(testValue000)) {
      { StandardObject* subtype000 = subtype;
        Surrogate* subtype = ((Surrogate*)(subtype000));

        { Surrogate* testValue001 = safePrimaryType(supertype);

          if (subtypeOfSurrogateP(testValue001)) {
            { StandardObject* supertype000 = supertype;
              Surrogate* supertype = ((Surrogate*)(supertype000));

              return (subtypeOfP(subtype, supertype) &&
                  compatibleParameterTypesP(subtype, supertype));
            }
          }
          else if (subtypeOfParametricTypeSpecifierP(testValue001)) {
            { StandardObject* supertype001 = supertype;
              ParametricTypeSpecifier* supertype = ((ParametricTypeSpecifier*)(supertype001));

              return (subtypeOfP(subtype, supertype->specifierBaseType) &&
                  compatibleParameterTypesP(subtype, supertype));
            }
          }
          else {
            return (false);
          }
        }
      }
    }
    else if (subtypeOfParametricTypeSpecifierP(testValue000)) {
      { StandardObject* subtype001 = subtype;
        ParametricTypeSpecifier* subtype = ((ParametricTypeSpecifier*)(subtype001));

        { Surrogate* testValue002 = safePrimaryType(supertype);

          if (subtypeOfSurrogateP(testValue002)) {
            { StandardObject* supertype002 = supertype;
              Surrogate* supertype = ((Surrogate*)(supertype002));

              return (subtypeOfP(subtype->specifierBaseType, supertype) &&
                  compatibleParameterTypesP(subtype, supertype));
            }
          }
          else if (subtypeOfParametricTypeSpecifierP(testValue002)) {
            { StandardObject* supertype003 = supertype;
              ParametricTypeSpecifier* supertype = ((ParametricTypeSpecifier*)(supertype003));

              return (subtypeOfP(subtype->specifierBaseType, supertype->specifierBaseType) &&
                  compatibleParameterTypesP(subtype, supertype));
            }
          }
          else {
            return (false);
          }
        }
      }
    }
    else if (subtypeOfAnchoredTypeSpecifierP(testValue000)) {
      { StandardObject* subtype002 = subtype;
        AnchoredTypeSpecifier* subtype = ((AnchoredTypeSpecifier*)(subtype002));

        return (anchoredTypeSpecifierP(supertype) &&
            (subtype->specifierParameterName == ((AnchoredTypeSpecifier*)(supertype))->specifierParameterName));
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "sub-type-spec-of?: Not defined on " << "`" << subtype << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

boolean voidP(StandardObject* type) {
  return (type == SGT_METHODS_STELLA_VOID);
}

StandardObject* extractParameterType(StandardObject* self, Symbol* parameter, boolean& _Return1) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfSurrogateP(testValue000)) {
      { StandardObject* self000 = self;
        Surrogate* self = ((Surrogate*)(self000));

        { Slot* slot = lookupSlot(((Class*)(self->surrogateValue)), parameter);

          if (((boolean)(slot))) {
            { StandardObject* _Return0 = slot->type();

              _Return1 = true;
              return (_Return0);
            }
          }
          else {
            _Return1 = false;
            return (SGT_METHODS_STELLA_OBJECT);
          }
        }
      }
    }
    else if (subtypeOfParametricTypeSpecifierP(testValue000)) {
      { StandardObject* self001 = self;
        ParametricTypeSpecifier* self = ((ParametricTypeSpecifier*)(self001));

        { Symbol* pname = NULL;
          Cons* iter000 = ((Class*)(self->specifierBaseType->surrogateValue))->parameters()->theConsList;
          StandardObject* ptype = NULL;
          Cons* iter001 = self->specifierParameterTypes->theConsList;

          for  (; (!(iter000 == NIL)) &&
                    (!(iter001 == NIL)); 
                iter000 = iter000->rest,
                iter001 = iter001->rest) {
            pname = ((Symbol*)(iter000->value));
            ptype = ((StandardObject*)(iter001->value));
            if (pname == parameter) {
              _Return1 = true;
              return (ptype);
            }
          }
        }
        _Return1 = false;
        return (SGT_METHODS_STELLA_OBJECT);
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "extract-parameter-type: Not defined on " << "`" << self << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

StandardObject* computeAnchoredTypeSpec(StandardObject* ownertype, AnchoredTypeSpecifier* reltype) {
  { Surrogate* testValue000 = safePrimaryType(ownertype);

    if (subtypeOfSurrogateP(testValue000)) {
      { StandardObject* ownertype000 = ownertype;
        Surrogate* ownertype = ((Surrogate*)(ownertype000));

        if (!((boolean)(reltype->specifierParameterName))) {
          return (ownertype);
        }
        { Slot* slot = lookupSlot(((Class*)(ownertype->surrogateValue)), reltype->specifierParameterName);

          if (!((boolean)(slot))) {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing :parameter named " << "`" << reltype->specifierParameterName << "'" << std::endl << "   for the class " << "`" << deUglifyParseTree(ownertype) << "'" << std::endl << "." << std::endl;
              }
            }
            return (SGT_METHODS_STELLA_OBJECT);
          }
          return ((((boolean)(((CompoundTypeSpecifier*)(dynamicSlotValue(slot->dynamicSlots, SYM_METHODS_STELLA_SLOT_TYPE_SPECIFIER, NULL))))) ? ((StandardObject*)(computeRelativeTypeSpec(((CompoundTypeSpecifier*)(dynamicSlotValue(slot->dynamicSlots, SYM_METHODS_STELLA_SLOT_TYPE_SPECIFIER, NULL))), ownertype))) : slot->slotBaseType));
        }
      }
    }
    else if (subtypeOfParametricTypeSpecifierP(testValue000)) {
      { StandardObject* ownertype001 = ownertype;
        ParametricTypeSpecifier* ownertype = ((ParametricTypeSpecifier*)(ownertype001));

        if (!((boolean)(reltype->specifierParameterName))) {
          return (ownertype);
        }
        { Symbol* pname = NULL;
          Cons* iter000 = ((Class*)(ownertype->specifierBaseType->surrogateValue))->parameters()->theConsList;
          StandardObject* ptype = NULL;
          Cons* iter001 = ownertype->specifierParameterTypes->theConsList;

          for  (; (!(iter000 == NIL)) &&
                    (!(iter001 == NIL)); 
                iter000 = iter000->rest,
                iter001 = iter001->rest) {
            pname = ((Symbol*)(iter000->value));
            ptype = ((StandardObject*)(iter001->value));
            if (pname == reltype->specifierParameterName) {
              return (ptype);
            }
          }
        }
        return (computeAnchoredTypeSpec(ownertype->specifierBaseType, reltype));
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "compute-anchored-type-spec: Not defined on " << "`" << ownertype << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

StandardObject* computeRelativeTypeSpec(StandardObject* relativetype, StandardObject* ownertype) {
  { Surrogate* testValue000 = safePrimaryType(relativetype);

    if (subtypeOfParametricTypeSpecifierP(testValue000)) {
      { StandardObject* relativetype000 = relativetype;
        ParametricTypeSpecifier* relativetype = ((ParametricTypeSpecifier*)(relativetype000));

        { boolean alwaysP000 = true;

          { StandardObject* ts = NULL;
            Cons* iter000 = relativetype->specifierParameterTypes->theConsList;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              ts = ((StandardObject*)(iter000->value));
              if (!typeP(ts)) {
                alwaysP000 = false;
                break;
              }
            }
          }
          if (alwaysP000) {
            return (relativetype);
          }
        }
        { List* typeslist = newList();
          StandardObject* relativets = NULL;
          boolean foundrelativistictypeP = false;

          { StandardObject* ts = NULL;
            Cons* iter001 = relativetype->specifierParameterTypes->theConsList;
            Cons* collect000 = NULL;

            for  (; !(iter001 == NIL); 
                  iter001 = iter001->rest) {
              ts = ((StandardObject*)(iter001->value));
              relativets = computeRelativeTypeSpec(ts, ownertype);
              if (!(relativets == ts)) {
                foundrelativistictypeP = true;
              }
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(relativets, NIL);
                  if (typeslist->theConsList == NIL) {
                    typeslist->theConsList = collect000;
                  }
                  else {
                    addConsToEndOfConsList(typeslist->theConsList, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(relativets, NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
          if (foundrelativistictypeP) {
            { ParametricTypeSpecifier* newts = newParametricTypeSpecifier();

              newts->specifierBaseType = relativetype->specifierBaseType;
              newts->specifierParameterTypes = typeslist;
              newts->specifierDimensions = relativetype->specifierDimensions;
              return (newts);
            }
          }
          else {
            {
              typeslist->free();
              return (relativetype);
            }
          }
        }
      }
    }
    else if (subtypeOfAnchoredTypeSpecifierP(testValue000)) {
      { StandardObject* relativetype001 = relativetype;
        AnchoredTypeSpecifier* relativetype = ((AnchoredTypeSpecifier*)(relativetype001));

        return (computeAnchoredTypeSpec(ownertype, relativetype));
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { StandardObject* relativetype002 = relativetype;
        Surrogate* relativetype = ((Surrogate*)(relativetype002));

        return (relativetype);
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "compute-relative-type-spec: Not defined on " << "`" << relativetype << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

StandardObject* Slot::computeReturnTypeSpec(StandardObject* firstargtype) {
  { Slot* self = this;

    firstargtype = firstargtype;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "compute-return-type-spec: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

StandardObject* MethodSlot::computeReturnTypeSpec(StandardObject* firstargtype) {
  { MethodSlot* self = this;

    if (!((boolean)(((CompoundTypeSpecifier*)(dynamicSlotValue(self->dynamicSlots, SYM_METHODS_STELLA_SLOT_TYPE_SPECIFIER, NULL)))))) {
      return (self->slotBaseType);
    }
    else {
      return (computeRelativeTypeSpec(((CompoundTypeSpecifier*)(dynamicSlotValue(self->dynamicSlots, SYM_METHODS_STELLA_SLOT_TYPE_SPECIFIER, NULL))), firstargtype));
    }
  }
}

StandardObject* StorageSlot::computeReturnTypeSpec(StandardObject* firstargtype) {
  { StorageSlot* self = this;

    if (!((boolean)(((CompoundTypeSpecifier*)(dynamicSlotValue(self->dynamicSlots, SYM_METHODS_STELLA_SLOT_TYPE_SPECIFIER, NULL)))))) {
      return (self->type());
    }
    else {
      return (computeRelativeTypeSpec(((CompoundTypeSpecifier*)(dynamicSlotValue(self->dynamicSlots, SYM_METHODS_STELLA_SLOT_TYPE_SPECIFIER, NULL))), firstargtype));
    }
  }
}

Object* yieldTypeSpecTree(StandardObject* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfSurrogateP(testValue000)) {
      { StandardObject* self000 = self;
        Surrogate* self = ((Surrogate*)(self000));

        return (internSymbolInModule(self->symbolName, ((Module*)(self->homeContext)), true));
      }
    }
    else if (subtypeOfParametricTypeSpecifierP(testValue000)) {
      { StandardObject* self001 = self;
        ParametricTypeSpecifier* self = ((ParametricTypeSpecifier*)(self001));

        { Cons* listoftypes = NIL;

          { StandardObject* ts = NULL;
            Cons* iter000 = self->specifierParameterTypes->theConsList;
            Cons* collect000 = NULL;

            for  (; !(iter000 == NIL); 
                  iter000 = iter000->rest) {
              ts = ((StandardObject*)(iter000->value));
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(yieldTypeSpecTree(ts), NIL);
                  if (listoftypes == NIL) {
                    listoftypes = collect000;
                  }
                  else {
                    addConsToEndOfConsList(listoftypes, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(yieldTypeSpecTree(ts), NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
          return (cons(internSymbolInModule(self->specifierBaseType->symbolName, ((Module*)(self->specifierBaseType->homeContext)), true), ((arrayTypeSpecifierP(self) ? listO(3, SYM_METHODS_STELLA_SIZE, yieldArrayDimensionsTree(self), NIL) : NIL))->concatenate(cons(SYM_METHODS_STELLA_OF, listoftypes->concatenate(NIL, 0)), 0)));
        }
      }
    }
    else if (subtypeOfAnchoredTypeSpecifierP(testValue000)) {
      { StandardObject* self002 = self;
        AnchoredTypeSpecifier* self = ((AnchoredTypeSpecifier*)(self002));

        if (((boolean)(self->specifierParameterName))) {
          return (listO(3, SYM_METHODS_STELLA_LIKE, cons(self->specifierParameterName, cons(SYM_METHODS_STELLA_SELF, NIL)), NIL));
        }
        else {
          return (listO(3, SYM_METHODS_STELLA_LIKE, SYM_METHODS_STELLA_SELF, NIL));
        }
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "validate-type-specifier: Not defined on " << "`" << self << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

// Lookup table for functions.
HashTable* oFUNCTION_LOOKUP_TABLEo = NULL;

MethodSlot* attachFunction(MethodSlot* newfunction) {
  { Symbol* name = newfunction->slotName;
    MethodSlot* oldfunction = lookupFunction(name);

    if (!undefineConflictingDefinitionsP(newfunction)) {
      return (NULL);
    }
    oFUNCTION_LOOKUP_TABLEo->insertAt(name, newfunction);
    unregisterSlotName(newfunction);
    newfunction->slotExternalP = true;
    newfunction->finalizeSlotTypeComputations();
    if (((boolean)(oldfunction))) {
      runHooks(oREDEFINE_RELATION_HOOKSo, list(2, oldfunction, newfunction));
      oldfunction->free();
    }
    return (newfunction);
  }
}

MethodSlot* lookupFunction(Symbol* functionsymbol) {
  // Return the function defined for 'functionSymbol', if it exists.
  functionsymbol = functionsymbol->softPermanentify();
  { StandardObject* function = ((StandardObject*)(oFUNCTION_LOOKUP_TABLEo->lookup(functionsymbol)));

    if (((boolean)(function)) &&
        (function->primaryType() == SGT_METHODS_STELLA_VECTOR)) {
      { Vector* record = ((Vector*)(function));
        const char* definition = ((StringWrapper*)((record->theArray)[0]))->wrapperValue;
        MethodSlot* oldfunction = ((MethodSlot*)((record->theArray)[1]));
        const char* modulename = ((StringWrapper*)((record->theArray)[2]))->wrapperValue;
        cpp_function_code code = (((boolean)((record->theArray)[3])) ? ((FunctionCodeWrapper*)((record->theArray)[3]))->wrapperValue : NULL);
        cpp_function_code wrappercode = ((record->length() >= 5) ? ((FunctionCodeWrapper*)((record->theArray)[4]))->wrapperValue : NULL);

        oFUNCTION_LOOKUP_TABLEo->insertAt(functionsymbol, oldfunction);
        { 
          BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule(modulename, true));
          BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
          function = defineMethodFromStringifiedSource(functionsymbol->symbolName, NULL, definition);
        }
        if (((boolean)(function))) {
          if (code != NULL) {
            ((MethodSlot*)(function))->functionCode = code;
          }
          if (wrappercode != NULL) {
            setDynamicSlotValue(((MethodSlot*)(function))->dynamicSlots, SYM_METHODS_STELLA_EVALUATOR_WRAPPER_CODE, wrapFunctionCode(wrappercode), NULL_FUNCTION_CODE_WRAPPER);
          }
        }
      }
    }
    return (((MethodSlot*)(function)));
  }
}

MethodSlot* lookupFunctionByName(const char* name) {
  // Return a function with name 'name' visible from the current module.
  // Scan all visible symbols looking for one that has a function defined for it.
  { MethodSlot* function = NULL;
    Symbol* symbol = NULL;

    { Module* module = NULL;
      Cons* iter000 = visibleModules(oMODULEo);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        module = ((Module*)(iter000->value));
        { boolean testValue000 = false;

          { 
            symbol = lookupSymbolInModule(name, module, true);
            testValue000 = ((boolean)(symbol));
          }
          if (testValue000) {
            { 
              function = lookupFunction(symbol);
              testValue000 = ((boolean)(function));
            }
          }
          if (testValue000) {
            return (function);
          }
        }
      }
    }
    return (NULL);
  }
}

MethodSlot* lookupFunctionByQualifiedName(const char* qualifiedname) {
  // Variant of `lookup-function-by-name' that can specify a starting
  // module through a `qualifiedName'.
  { const char* functionname = NULL;
    const char* modulename = NULL;
    Keyword* kind = NULL;

    functionname = parseStellaName(qualifiedname, true, modulename, kind);
    kind = kind;
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, ((modulename != NULL) ? getStellaModule(modulename, true) : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      return (lookupFunctionByName(functionname));
    }
  }
}

MethodSlot* lookupFunctionOrStellaFunction(Symbol* functionsymbol) {
  return (lookupFunction(functionsymbol));
}

Module* lookupFunctionHomeModule(Symbol* functionsymbol) {
  functionsymbol = functionsymbol->softPermanentify();
  { StandardObject* function = ((StandardObject*)(oFUNCTION_LOOKUP_TABLEo->lookup(functionsymbol)));

    if (!((boolean)(function))) {
      return (NULL);
    }
    { Surrogate* testValue000 = function->primaryType();

      if (testValue000 == SGT_METHODS_STELLA_VECTOR) {
        return (getStellaModule(((StringWrapper*)((((Vector*)(function))->theArray)[2]))->wrapperValue, true));
      }
      else if (testValue000 == SGT_METHODS_STELLA_METHOD_SLOT) {
        return (function->homeModule());
      }
      else {
        return (NULL);
      }
    }
  }
}

void undefineFunction(Symbol* name) {
  { MethodSlot* function = lookupFunction(name);

    if (((boolean)(function))) {
      destroyFunction(function);
    }
  }
}

void destroyFunction(MethodSlot* function) {
  { Symbol* functionname = function->slotName;
    Surrogate* slotref = function->slotSlotref;
    MethodSlot* realfunction = lookupFunction(functionname);

    if (function == realfunction) {
      oFUNCTION_LOOKUP_TABLEo->removeAt(functionname);
    }
    if (((boolean)(slotref)) &&
        (function == ((Slot*)(slotref->surrogateValue)))) {
      slotref->surrogateValue = NULL;
    }
    function->deletedPSetter(true);
    function->free();
  }
}

boolean undefineConflictingDefinitionsP(MethodSlot* newslot) {
  if (newslot->methodFunctionP) {
    if (warnAboutFunctionShadowingSlotsP(newslot)) {
      if (!(yOrNP("Do you want to remove the conflicting method definitions? "))) {
        return (false);
      }
      undefineExternalSlots(newslot->slotName);
      unregisterSlotName(newslot);
    }
    if (((boolean)(lookupMacro(newslot->slotName)))) {
      if (!((BooleanWrapper*)(dynamicSlotValue(newslot->dynamicSlots, SYM_METHODS_STELLA_METHOD_MACROp, FALSE_WRAPPER)))->wrapperValue) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationWarning();
          if (!(suppressWarningsP())) {
            printErrorContext(">> WARNING: ", STANDARD_WARNING);
            *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Function " << "`" << deUglifyParseTree(newslot) << "'" << " redefines an exisiting macro of the same name" << "." << std::endl;
          }
        }
      }
      else {
        if (!(newslot->functionCode != NULL)) {
          newslot->functionCode = lookupMacro(newslot->slotName)->functionCode;
        }
      }
    }
    else if (((boolean)(lookupFunction(newslot->slotName)))) {
      if (((BooleanWrapper*)(dynamicSlotValue(newslot->dynamicSlots, SYM_METHODS_STELLA_METHOD_MACROp, FALSE_WRAPPER)))->wrapperValue) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationWarning();
          if (!(suppressWarningsP())) {
            printErrorContext(">> WARNING: ", STANDARD_WARNING);
            *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Macro " << "`" << deUglifyParseTree(newslot) << "'" << " redefines an exisiting function of the same name" << "." << std::endl;
          }
        }
      }
    }
  }
  else {
    if (warnAboutSlotShadowedByAFunctionP(newslot)) {
      std::cout << " Removing the preexisting function definition." << std::endl;
      undefineFunction(newslot->slotName);
    }
  }
  return (true);
}

void defineFunctionObject(const char* name, const char* definition, cpp_function_code code, cpp_function_code wrappercode) {
  if (name == NULL) {
    { MethodSlot* function = defineMethodFromStringifiedSource(NULL, NULL, definition);

      if (((boolean)(function))) {
        if (code != NULL) {
          function->functionCode = code;
        }
        if (wrappercode != NULL) {
          setDynamicSlotValue(function->dynamicSlots, SYM_METHODS_STELLA_EVALUATOR_WRAPPER_CODE, wrapFunctionCode(wrappercode), NULL_FUNCTION_CODE_WRAPPER);
        }
        oFUNCTION_LOOKUP_TABLEo->insertAt(function->slotName, function);
      }
    }
  }
  else {
    { Object* namesymbol = ((name[0] == ' ') ? readSExpressionFromString(name) : internSymbolInModule(name, NULL, false));
      StandardObject* oldfunction = ((StandardObject*)(oFUNCTION_LOOKUP_TABLEo->lookup(((Symbol*)(namesymbol)))));
      Vector* record = stella::newVector(((wrappercode != NULL) ? 5 : 4));

      if (((boolean)(oldfunction)) &&
          (oldfunction->primaryType() == SGT_METHODS_STELLA_VECTOR)) {
        oldfunction = NULL;
      }
      (record->theArray)[0] = (wrapString(definition));
      (record->theArray)[1] = oldfunction;
      (record->theArray)[2] = (wrapString(oMODULEo->moduleFullName));
      if (code != NULL) {
        (record->theArray)[3] = (wrapFunctionCode(code));
      }
      if (wrappercode != NULL) {
        (record->theArray)[4] = (wrapFunctionCode(wrappercode));
      }
      oFUNCTION_LOOKUP_TABLEo->insertAt(((Symbol*)(namesymbol)), record);
    }
  }
}

// Lookup table for global variables.
HashTable* oGLOBAL_VARIABLE_LOOKUP_TABLEo = NULL;

GlobalVariable* internGlobalVariable(GlobalVariable* global) {
  { Symbol* name = global->variableName;
    GlobalVariable* oldglobal = name->lookupGlobalVariable();

    if (((boolean)(oldglobal))) {
      if (stringEqlP(global->variableStringifiedSource, oldglobal->variableStringifiedSource)) {
        global->free();
        return (oldglobal);
      }
      else {
        std::cout << "Redefining the global variable " << "`" << global->variableName << "'" << std::endl;
        oldglobal->free();
      }
    }
    oGLOBAL_VARIABLE_LOOKUP_TABLEo->insertAt(name, global);
    return (global);
  }
}

GlobalVariable* GeneralizedSymbol::lookupGlobalVariable() {
  // Return a global variable with name 'self'.
  { GeneralizedSymbol* self = this;

    return (((GlobalVariable*)(oGLOBAL_VARIABLE_LOOKUP_TABLEo->lookup(((Symbol*)(self))))));
  }
}

GlobalVariable* Surrogate::lookupGlobalVariable() {
  // Return a global variable with name 'self'.
  { Surrogate* self = this;

    { Symbol* symbol = ((Symbol*)(lookupRigidSymbolWrtModule(self->symbolName, ((Module*)(self->homeContext)), SYMBOL_SYM)));

      if (((boolean)(symbol))) {
        return (symbol->lookupGlobalVariable());
      }
      else {
        return (NULL);
      }
    }
  }
}

GlobalVariable* stringLookupGlobalVariable(const char* self) {
  // Return a global variable with name 'self'.
  { Symbol* symbol = lookupSymbol(self);

    if (((boolean)(symbol))) {
      return (symbol->lookupGlobalVariable());
    }
    else {
      return (NULL);
    }
  }
}

GlobalVariable* lookupGlobalVariableByName(const char* name) {
  // Return a global variable with `name' visible from the current module.
  // Scan all visible symbols looking for one that has a global variable defined for it.
  // NOTE: this is more robust than STRING.lookup-global-variable which will fail if there
  // is a local symbol with `name' which shadows one higher up that is the name of a global.
  { GlobalVariable* global = NULL;
    Symbol* symbol = NULL;

    { Module* module = NULL;
      Cons* iter000 = visibleModules(oMODULEo);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        module = ((Module*)(iter000->value));
        { boolean testValue000 = false;

          { 
            symbol = lookupSymbolInModule(name, module, true);
            testValue000 = ((boolean)(symbol));
          }
          if (testValue000) {
            { 
              global = symbol->lookupGlobalVariable();
              testValue000 = ((boolean)(global));
            }
          }
          if (testValue000) {
            return (global);
          }
        }
      }
    }
    return (NULL);
  }
}

GlobalVariable* lookupGlobalVariableByQualifiedName(const char* qualifiedname) {
  // Variant of `lookup-global-variable-by-name' that can specify a starting
  // module through a `qualifiedName'.
  { const char* globalname = NULL;
    const char* modulename = NULL;
    Keyword* kind = NULL;

    globalname = parseStellaName(qualifiedname, true, modulename, kind);
    kind = kind;
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, ((modulename != NULL) ? getStellaModule(modulename, true) : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      return (lookupGlobalVariableByName(globalname));
    }
  }
}

StandardObject* globalVariableTypeSpec(GlobalVariable* global) {
  // Return the type spec for the global variable `global'.
  { StandardObject* type = ((StandardObject*)(dynamicSlotValue(global->dynamicSlots, SYM_METHODS_STELLA_VARIABLE_TYPE_SPECIFIER, NULL)));

    if (((boolean)(type))) {
      return (type);
    }
    else {
      return (global->variableType);
    }
  }
}

StandardObject* lookupGlobalVariableType(Symbol* name) {
  { GlobalVariable* global = name->lookupGlobalVariable();

    if (((boolean)(global))) {
      return (globalVariableTypeSpec(global));
    }
    else {
      return (NULL);
    }
  }
}

GlobalVariable* defineStellaGlobalVariableFromParseTree(Cons* tree, const char* stringifiedsource, Object*& _Return1) {
  { Object* typetree = tree->rest->rest->value;
    Object* initialvaluetree = tree->fourth();
    Cons* optionstree = tree->nthRest(4);
    boolean specialP = tree->value == SYM_METHODS_STELLA_DEFSPECIAL;
    boolean constantP = tree->value == SYM_METHODS_STELLA_DEFCONSTANT;
    boolean noinitialvalueP = false;
    GlobalVariable* global = newGlobalVariable();
    GlobalVariable* internedglobal = NULL;

    if ((tree->length() <= 3) ||
        (getQuotedTree("((:DOCUMENTATION :PUBLIC? :AUXILIARY?) \"/STELLA\")", "/STELLA")->memberP(initialvaluetree) &&
         ((optionstree->length()) % 2))) {
      noinitialvalueP = true;
      initialvaluetree = (specialP ? KWD_METHODS_UNBOUND_SPECIAL_VARIABLE : NULL);
      optionstree = tree->nthRest(3);
    }
    global->variableName = ((Symbol*)(tree->rest->value->permanentify()));
    global->variableStringifiedSource = stringifiedsource;
    internedglobal = internGlobalVariable(global);
    recordVariableHomeModule(internedglobal);
    if (noinitialvalueP &&
        (!specialP)) {
      if (constantP) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing value in constant declaration" << "." << std::endl;
          }
        }
      }
      else {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing initial value in variable declaration" << "." << std::endl;
          }
        }
      }
      _Return1 = initialvaluetree;
      return (internedglobal);
    }
    if (!(global == internedglobal)) {
      _Return1 = initialvaluetree;
      return (internedglobal);
    }
    typetree = typetree->yieldTypeSpecifier();
    validateTypeSpecifier(((StandardObject*)(typetree)), NULL, true);
    if (typeP(typetree)) {
      global->variableType = ((Surrogate*)(typetree));
    }
    else {
      {
        setDynamicSlotValue(global->dynamicSlots, SYM_METHODS_STELLA_VARIABLE_TYPE_SPECIFIER, ((StandardObject*)(typetree)), NULL);
        global->variableType = typeSpecToBaseType(((StandardObject*)(typetree)));
      }
    }
    global->variableSpecialP = specialP;
    global->variableConstantP = constantP;
    if (!(optionstree == NIL)) {
      { PropertyList* options = newPropertyList();

        options->thePlist = optionstree;
        { Object* key = NULL;
          Object* value = NULL;
          Cons* iter000 = options->thePlist;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest->rest) {
            key = iter000->value;
            value = iter000->rest->value;
            { Keyword* testValue000 = ((Keyword*)(key));

              if (testValue000 == KWD_METHODS_DOCUMENTATION) {
                global->documentation = ((StringWrapper*)(value))->wrapperValue;
              }
              else if (testValue000 == KWD_METHODS_PUBLICp) {
                global->variablePublicP = coerceWrappedBooleanToBoolean(coerceToBoolean(value));
              }
              else if (testValue000 == KWD_METHODS_AUXILIARYp) {
                global->variableAuxiliaryP = coerceWrappedBooleanToBoolean(coerceToBoolean(value));
              }
              else {
                if (!(runOptionHandlerP(global, ((Keyword*)(key)), value))) {
                  { 
                    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                    signalTranslationWarning();
                    if (!(suppressWarningsP())) {
                      printErrorContext(">> WARNING: ", STANDARD_WARNING);
                      *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Skipping invalid variable option " << "`" << deUglifyParseTree(key) << "'" << std::endl << "in the definition of variable " << "`" << global->variableName << "'" << "." << std::endl;
                    }
                  }
                }
              }
            }
          }
        }
        options->thePlist = NULL;
      }
    }
    _Return1 = initialvaluetree;
    return (global);
  }
}

void defineStellaGlobalVariableFromStringifiedSource(const char* stringifiedsource) {
  // Define a stella global variable using a parse tree derived from 'stringifiedSource'.
  { Object* dummy1;

    defineStellaGlobalVariableFromParseTree(((Cons*)(unstringifyStellaSource(stringifiedsource, NULL))), stringifiedsource, dummy1);
  }
}

void defineGlobalVariableObject(const char* definition, void* nativeobject) {
  // Define a STELLA global variable object based on `definition', and initialize
  // its variable-native-object slot to `nativeObject' (which is primarily needed for C++).
  { Object* dummy1;

    { GlobalVariable* global = defineStellaGlobalVariableFromParseTree(((Cons*)(unstringifyStellaSource(definition, NULL))), definition, dummy1);

      global->variableNativeObject = nativeobject;
    }
  }
}

Module* recordVariableHomeModule(GlobalVariable* self) {
  { Symbol* name = self->variableName;
    Module* namemodule = ((Module*)(name->homeContext));
    Module* definitionmodule = oMODULEo;
    Module* homemodule = namemodule;

    if (explicitlyQualifiedNameP(name, definitionmodule)) {
      homemodule = namemodule;
    }
    else {
      homemodule = definitionmodule;
    }
    if (!(homemodule == namemodule)) {
      setDynamicSlotValue(self->dynamicSlots, SYM_METHODS_STELLA_VARIABLE_HOME_MODULE, homemodule, NULL);
    }
    return (homemodule);
  }
}

void destroyGlobalVariable(GlobalVariable* variable) {
  { Symbol* variablename = variable->variableName;
    GlobalVariable* realvariable = variablename->lookupGlobalVariable();

    if (variable == realvariable) {
      oGLOBAL_VARIABLE_LOOKUP_TABLEo->removeAt(variablename);
    }
    variable->deletedPSetter(true);
    variable->free();
  }
}

void* getGlobalVariableNativeObject(GlobalVariable* variable) {
  // Return the native object of `variable' which can be used to access its runtime value.
  // In Lisp this is the Lisp symbol which holds the variable value, in C++ this is the address of the variable,
  // and in Java this is the declared Field object.  For C++ native object addresses are initialized at startup
  // time, for Lisp and Java native objects will be accessed upon first call and then cached in the slot.
  { void* varobj = variable->variableNativeObject;

    if (!(varobj == NULL)) {
      return (varobj);
    }
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, variable->homeModule());
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    }
    variable->variableNativeObject = varobj;
    return (varobj);
  }
}

Object* readNativeVariableValue(void* var, Surrogate* type) {
  // Interpreted variable reader which reads a native code variable represented by
  // `var' of type `type' and returns its value which will be wrapped if necessary.  If `var' is a
  // special variable, this will access the current dynamic value at the top of the special stack.
  // This relies upon `type' being completely accurate and bad things will happen if it is not.
  if (subtypeOfP(type, SGT_METHODS_STELLA_LITERAL)) {
    if (type == SGT_METHODS_STELLA_STRING) {
      return (wrapString(*(const char**)var));
    }
    else if (type == SGT_METHODS_STELLA_BOOLEAN) {
      return ((*(boolean*)var ? TRUE_WRAPPER : FALSE_WRAPPER));
    }
    else if (type == SGT_METHODS_STELLA_INTEGER) {
      return (wrapInteger(*(int*)var));
    }
    else if (type == SGT_METHODS_STELLA_FLOAT) {
      return (wrapFloat(*(double*)var));
    }
    else if (type == SGT_METHODS_STELLA_LONG_INTEGER) {
      return (wrapLongInteger(*(long long int*)var));
    }
    else if (type == SGT_METHODS_STELLA_CHARACTER) {
      return (wrapCharacter(*(char*)var));
    }
    else if (type == SGT_METHODS_STELLA_MUTABLE_STRING) {
      return (wrapMutableString(*(char**)var));
    }
    else if (type == SGT_METHODS_STELLA_FUNCTION_CODE) {
      return (wrapFunctionCode(*(cpp_function_code*)var));
    }
    else if (type == SGT_METHODS_STELLA_METHOD_CODE) {
      return (wrapMethodCode(*(cpp_method_code*)var));
    }
    else {
    }
  }
  else if (subtypeOfP(type, SGT_METHODS_STELLA_OBJECT)) {
    return (*(Object**)var);
  }
  { OutputStringStream* stream000 = newOutputStringStream();

    *(stream000->nativeStream) << "Cannot read variables of type: " << "`" << type << "'";
    throw *newStellaException(stream000->theStringReader());
  }
}

void writeNativeVariableValue(void* var, Surrogate* type, Object* value) {
  // Interpreted variable writer which sets a native code variable represented by
  // `var' of type `type' to `value' which will be unwrapped if necessary.  If `var' is a special
  // variable, this will change the current dynamic value at the top of the special stack.  This
  // relies upon `type' being completely accurate and bad things will happen if it is not.
  { Surrogate* valuetype = (((boolean)(value)) ? value->primaryType() : type);

    if (subtypeOfP(type, SGT_METHODS_STELLA_LITERAL)) {
      if (!(subtypeOfP(valuetype, SGT_METHODS_STELLA_WRAPPER) &&
          subtypeOfP(wrappedTypeToType(valuetype), type))) {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Variable type " << "`" << type << "'" << " not compatible with value type " << "`" << wrappedTypeToType(valuetype) << "'";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      if (type == SGT_METHODS_STELLA_STRING) {
        { const char* val = unwrapString(((StringWrapper*)(value)));

          *(const char**)var = val;
          return;
        }
      }
      else if (type == SGT_METHODS_STELLA_BOOLEAN) {
        { boolean val = ((BooleanWrapper*)(value)) == TRUE_WRAPPER;

          *(boolean*)var = val;
          return;
        }
      }
      else if (type == SGT_METHODS_STELLA_INTEGER) {
        { int val = unwrapInteger(((IntegerWrapper*)(value)));

          *(int*)var = val;
          return;
        }
      }
      else if (type == SGT_METHODS_STELLA_FLOAT) {
        { double val = unwrapFloat(((FloatWrapper*)(value)));

          *(double*)var = val;
          return;
        }
      }
      else if (type == SGT_METHODS_STELLA_LONG_INTEGER) {
        { long long int val = unwrapLongInteger(((LongIntegerWrapper*)(value)));

          *(long long int*)var = val;
          return;
        }
      }
      else if (type == SGT_METHODS_STELLA_CHARACTER) {
        { char val = unwrapCharacter(((CharacterWrapper*)(value)));

          *(char*)var = val;
          return;
        }
      }
      else if (type == SGT_METHODS_STELLA_MUTABLE_STRING) {
        { char* val = unwrapMutableString(((MutableStringWrapper*)(value)));

          *(char**)var = val;
          return;
        }
      }
      else if (type == SGT_METHODS_STELLA_FUNCTION_CODE) {
        { cpp_function_code val = unwrapFunctionCode(((FunctionCodeWrapper*)(value)));

          *(cpp_function_code*)var = val;
          return;
        }
      }
      else if (type == SGT_METHODS_STELLA_METHOD_CODE) {
        { cpp_method_code val = unwrapMethodCode(((MethodCodeWrapper*)(value)));

          *(cpp_method_code*)var = val;
          return;
        }
      }
      else {
      }
    }
    else if (subtypeOfP(type, SGT_METHODS_STELLA_OBJECT)) {
      if (!(subtypeOfP(valuetype, type))) {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "Variable type " << "`" << type << "'" << " not compatible with value type " << "`" << valuetype << "'";
          throw *newStellaException(stream001->theStringReader());
        }
      }
      *(Object**)var = value;
      return;
    }
    { OutputStringStream* stream002 = newOutputStringStream();

      *(stream002->nativeStream) << "Cannot write variables of type: " << "`" << type << "'";
      throw *newStellaException(stream002->theStringReader());
    }
  }
}

Object* readGlobalVariableValue(GlobalVariable* variable) {
  // Interpreted global `variable' reader which reads and returns its native value
  // which will be wrapped if necessary.  This will access the value at the top of the special stack.
  return (readNativeVariableValue(getGlobalVariableNativeObject(variable), variable->variableType));
}

void writeGlobalVariableValue(GlobalVariable* variable, Object* value) {
  // Interpreted global `variable' writer which sets its native value to `value'
  // unwrappig it if necessary.  This will change the current value at the top of the special stack.
  writeNativeVariableValue(getGlobalVariableNativeObject(variable), variable->variableType, value);
}

Surrogate* defineStellaTypeFromParseTree(Cons* tree) {
  { Object* typenamE = tree->rest->value;
    StandardObject* typedefinition = tree->rest->rest->value->yieldTypeSpecifier();
    Surrogate* type = NULL;

    if (subtypeOfSymbolP(safePrimaryType(typenamE))) {
      { Object* typename000 = typenamE;
        Symbol* typenamE = ((Symbol*)(typename000));

        type = typify(typenamE);
        if ((!definedTypeP(type)) &&
            ((boolean)(type->surrogateValue))) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Cannot define type " << "`" << deUglifyParseTree(typenamE) << "'" << ", since " << "`" << deUglifyParseTree(type) << "'" << std::endl << "   already points to " << "`" << type->surrogateValue << "'" << "." << std::endl;
            }
          }
          return (NULL);
        }
        type->surrogateValue = typedefinition;
        return (type);
      }
    }
    else {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal type name: " << "`" << deUglifyParseTree(typenamE) << "'" << "." << std::endl;
        }
      }
      return (NULL);
    }
  }
}

void defineStellaTypeFromStringifiedSource(const char* stringifiedsource) {
  defineStellaTypeFromParseTree(((Cons*)(unstringifyStellaSource(stringifiedsource, NULL))));
}

void helpStartupMethods1() {
  {
    SGT_METHODS_STELLA_SURROGATE = ((Surrogate*)(internRigidSymbolWrtModule("SURROGATE", NULL, 1)));
    SGT_METHODS_STELLA_PARAMETRIC_TYPE_SPECIFIER = ((Surrogate*)(internRigidSymbolWrtModule("PARAMETRIC-TYPE-SPECIFIER", NULL, 1)));
    SGT_METHODS_STELLA_ANCHORED_TYPE_SPECIFIER = ((Surrogate*)(internRigidSymbolWrtModule("ANCHORED-TYPE-SPECIFIER", NULL, 1)));
    SGT_METHODS_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", NULL, 1)));
    SGT_METHODS_STELLA_VOID = ((Surrogate*)(internRigidSymbolWrtModule("VOID", NULL, 1)));
    SYM_METHODS_STELLA_LIKE = ((Symbol*)(internRigidSymbolWrtModule("LIKE", NULL, 0)));
    SYM_METHODS_STELLA_SIZE = ((Symbol*)(internRigidSymbolWrtModule("SIZE", NULL, 0)));
    SYM_METHODS_STELLA_UNKNOWN = ((Symbol*)(internRigidSymbolWrtModule("UNKNOWN", NULL, 0)));
    SYM_METHODS_STELLA_OF = ((Symbol*)(internRigidSymbolWrtModule("OF", NULL, 0)));
    SYM_METHODS_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
    SGT_METHODS_STELLA_ARRAY = ((Surrogate*)(internRigidSymbolWrtModule("ARRAY", NULL, 1)));
    SYM_METHODS_STELLA_SELF = ((Symbol*)(internRigidSymbolWrtModule("SELF", NULL, 0)));
    SGT_METHODS_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SYM_METHODS_STELLA_IN = ((Symbol*)(internRigidSymbolWrtModule("IN", NULL, 0)));
    SYM_METHODS_STELLA_OUT = ((Symbol*)(internRigidSymbolWrtModule("OUT", NULL, 0)));
    SYM_METHODS_STELLA_INOUT = ((Symbol*)(internRigidSymbolWrtModule("INOUT", NULL, 0)));
    SYM_METHODS_STELLA_METHOD_PARAMETER_DIRECTIONS = ((Symbol*)(internRigidSymbolWrtModule("METHOD-PARAMETER-DIRECTIONS", NULL, 0)));
    SYM_METHODS_STELLA_ARGUMENT_LIST = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENT-LIST", NULL, 0)));
    SYM_METHODS_STELLA_aREST = ((Symbol*)(internRigidSymbolWrtModule("&REST", NULL, 0)));
    SYM_METHODS_STELLA_METHOD_VARIABLE_ARGUMENTSp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-VARIABLE-ARGUMENTS?", NULL, 0)));
    SYM_METHODS_STELLA_aBODY = ((Symbol*)(internRigidSymbolWrtModule("&BODY", NULL, 0)));
    SYM_METHODS_STELLA_METHOD_BODY_ARGUMENTp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-BODY-ARGUMENT?", NULL, 0)));
    SGT_METHODS_STELLA_UNKNOWN = ((Surrogate*)(internRigidSymbolWrtModule("UNKNOWN", NULL, 1)));
    KWD_METHODS_TYPE = ((Keyword*)(internRigidSymbolWrtModule("TYPE", NULL, 2)));
    KWD_METHODS_RETURN_TYPES = ((Keyword*)(internRigidSymbolWrtModule("RETURN-TYPES", NULL, 2)));
    SYM_METHODS_STELLA_SLOT_TYPE_SPECIFIER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-TYPE-SPECIFIER", NULL, 0)));
    KWD_METHODS_PUBLICp = ((Keyword*)(internRigidSymbolWrtModule("PUBLIC?", NULL, 2)));
    KWD_METHODS_ABSTRACTp = ((Keyword*)(internRigidSymbolWrtModule("ABSTRACT?", NULL, 2)));
    KWD_METHODS_NATIVEp = ((Keyword*)(internRigidSymbolWrtModule("NATIVE?", NULL, 2)));
    SYM_METHODS_STELLA_METHOD_NATIVEp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-NATIVE?", NULL, 0)));
    KWD_METHODS_CONSTRUCTORp = ((Keyword*)(internRigidSymbolWrtModule("CONSTRUCTOR?", NULL, 2)));
    SYM_METHODS_STELLA_METHOD_CONSTRUCTORp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-CONSTRUCTOR?", NULL, 0)));
    KWD_METHODS_GLOBALLY_INLINEp = ((Keyword*)(internRigidSymbolWrtModule("GLOBALLY-INLINE?", NULL, 2)));
    SYM_METHODS_STELLA_METHOD_GLOBALLY_INLINEp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-GLOBALLY-INLINE?", NULL, 0)));
    KWD_METHODS_INLINE = ((Keyword*)(internRigidSymbolWrtModule("INLINE", NULL, 2)));
    SYM_METHODS_STELLA_METHOD_INLINED_FUNCTIONS = ((Symbol*)(internRigidSymbolWrtModule("METHOD-INLINED-FUNCTIONS", NULL, 0)));
    KWD_METHODS_AUXILIARYp = ((Keyword*)(internRigidSymbolWrtModule("AUXILIARY?", NULL, 2)));
    SYM_METHODS_STELLA_SLOT_AUXILIARYp = ((Symbol*)(internRigidSymbolWrtModule("SLOT-AUXILIARY?", NULL, 0)));
    KWD_METHODS_DOCUMENTATION = ((Keyword*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 2)));
    SYM_METHODS_STELLA_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 0)));
    KWD_METHODS_RETURNS = ((Keyword*)(internRigidSymbolWrtModule("RETURNS", NULL, 2)));
    KWD_METHODS_STORAGE_SLOT = ((Keyword*)(internRigidSymbolWrtModule("STORAGE-SLOT", NULL, 2)));
    SYM_METHODS_STELLA_STORAGE_SLOT = ((Symbol*)(internRigidSymbolWrtModule("STORAGE-SLOT", NULL, 0)));
    KWD_METHODS_INHERITS_THROUGH = ((Keyword*)(internRigidSymbolWrtModule("INHERITS-THROUGH", NULL, 2)));
    SYM_METHODS_STELLA_METHOD_INHERITS_THROUGH = ((Symbol*)(internRigidSymbolWrtModule("METHOD-INHERITS-THROUGH", NULL, 0)));
    KWD_METHODS_PROPERTIES = ((Keyword*)(internRigidSymbolWrtModule("PROPERTIES", NULL, 2)));
    SYM_METHODS_STELLA_PROPERTIES = ((Symbol*)(internRigidSymbolWrtModule("PROPERTIES", NULL, 0)));
    KWD_METHODS_META_ATTRIBUTES = ((Keyword*)(internRigidSymbolWrtModule("META-ATTRIBUTES", NULL, 2)));
    SYM_METHODS_STELLA_META_ATTRIBUTES = ((Symbol*)(internRigidSymbolWrtModule("META-ATTRIBUTES", NULL, 0)));
    KWD_METHODS_COMMANDp = ((Keyword*)(internRigidSymbolWrtModule("COMMAND?", NULL, 2)));
    SYM_METHODS_STELLA_METHOD_COMMANDp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-COMMAND?", NULL, 0)));
    KWD_METHODS_LISP_MACROp = ((Keyword*)(internRigidSymbolWrtModule("LISP-MACRO?", NULL, 2)));
    SYM_METHODS_STELLA_METHOD_LISP_MACROp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-LISP-MACRO?", NULL, 0)));
    KWD_METHODS_EVALUATE_ARGUMENTSp = ((Keyword*)(internRigidSymbolWrtModule("EVALUATE-ARGUMENTS?", NULL, 2)));
    SYM_METHODS_STELLA_METHOD_EVALUATE_ARGUMENTSp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-EVALUATE-ARGUMENTS?", NULL, 0)));
    KWD_METHODS_C_CALLABLEp = ((Keyword*)(internRigidSymbolWrtModule("C-CALLABLE?", NULL, 2)));
    SYM_METHODS_STELLA_METHOD_C_CALLABLEp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-C-CALLABLE?", NULL, 0)));
    SYM_METHODS_STELLA_CONCATENATE = ((Symbol*)(internRigidSymbolWrtModule("CONCATENATE", NULL, 0)));
    SGT_METHODS_STELLA_METHOD_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-SLOT", NULL, 1)));
    SYM_METHODS_STELLA_SLOT_OPTION_HANDLER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-OPTION-HANDLER", NULL, 0)));
  }
}

void helpStartupMethods2() {
  {
    SYM_METHODS_STELLA_DEFINE_FUNCTION_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("DEFINE-FUNCTION-OBJECT", NULL, 0)));
    SYM_METHODS_STELLA_THE_CODE = ((Symbol*)(internRigidSymbolWrtModule("THE-CODE", NULL, 0)));
    KWD_METHODS_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SYM_METHODS_STELLA_DEFINE_INLINE_METHOD_CODE = ((Symbol*)(internRigidSymbolWrtModule("DEFINE-INLINE-METHOD-CODE", NULL, 0)));
    SYM_METHODS_STELLA_QUOTE = ((Symbol*)(internRigidSymbolWrtModule("QUOTE", NULL, 0)));
    KWD_METHODS_METHOD = ((Keyword*)(internRigidSymbolWrtModule("METHOD", NULL, 2)));
    SYM_METHODS_STELLA_DEFINE_METHOD_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("DEFINE-METHOD-OBJECT", NULL, 0)));
    SGT_METHODS_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 1)));
    SYM_METHODS_STELLA_SUPER_CLASSES = ((Symbol*)(internRigidSymbolWrtModule("SUPER-CLASSES", NULL, 0)));
    SYM_METHODS_STELLA_EQUIVALENT_SLOT = ((Symbol*)(internRigidSymbolWrtModule("EQUIVALENT-SLOT", NULL, 0)));
    SYM_METHODS_STELLA_CLASS_ALL_SUPER_CLASSES = ((Symbol*)(internRigidSymbolWrtModule("CLASS-ALL-SUPER-CLASSES", NULL, 0)));
    SYM_METHODS_STELLA_SLOT_DIRECT_EQUIVALENT = ((Symbol*)(internRigidSymbolWrtModule("SLOT-DIRECT-EQUIVALENT", NULL, 0)));
    SYM_METHODS_STELLA_LET = ((Symbol*)(internRigidSymbolWrtModule("LET", NULL, 0)));
    SYM_METHODS_STELLA_CURSOR = ((Symbol*)(internRigidSymbolWrtModule("CURSOR", NULL, 0)));
    SYM_METHODS_STELLA_VALUE = ((Symbol*)(internRigidSymbolWrtModule("VALUE", NULL, 0)));
    SYM_METHODS_STELLA_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SLOT-VALUE", NULL, 0)));
    SYM_METHODS_STELLA_LOOP = ((Symbol*)(internRigidSymbolWrtModule("LOOP", NULL, 0)));
    SYM_METHODS_STELLA_WHEN = ((Symbol*)(internRigidSymbolWrtModule("WHEN", NULL, 0)));
    SYM_METHODS_STELLA_RETURN = ((Symbol*)(internRigidSymbolWrtModule("RETURN", NULL, 0)));
    SYM_METHODS_STELLA_SETQ = ((Symbol*)(internRigidSymbolWrtModule("SETQ", NULL, 0)));
    SYM_METHODS_STELLA_IF = ((Symbol*)(internRigidSymbolWrtModule("IF", NULL, 0)));
    SYM_METHODS_STELLA_DEFINEDp = ((Symbol*)(internRigidSymbolWrtModule("DEFINED?", NULL, 0)));
    SGT_METHODS_STELLA_COLLECTION = ((Surrogate*)(internRigidSymbolWrtModule("COLLECTION", NULL, 1)));
    SYM_METHODS_STELLA_FIRST = ((Symbol*)(internRigidSymbolWrtModule("FIRST", NULL, 0)));
    SYM_METHODS_STELLA_VARIABLE_ARITY_TABLEp = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-ARITY-TABLE?", NULL, 0)));
    SGT_METHODS_STELLA_VECTOR = ((Surrogate*)(internRigidSymbolWrtModule("VECTOR", NULL, 1)));
    SYM_METHODS_STELLA_EVALUATOR_WRAPPER_CODE = ((Symbol*)(internRigidSymbolWrtModule("EVALUATOR-WRAPPER-CODE", NULL, 0)));
    SYM_METHODS_STELLA_METHOD_MACROp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-MACRO?", NULL, 0)));
    SYM_METHODS_STELLA_VARIABLE_TYPE_SPECIFIER = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-TYPE-SPECIFIER", NULL, 0)));
    SYM_METHODS_STELLA_DEFSPECIAL = ((Symbol*)(internRigidSymbolWrtModule("DEFSPECIAL", NULL, 0)));
    SYM_METHODS_STELLA_DEFCONSTANT = ((Symbol*)(internRigidSymbolWrtModule("DEFCONSTANT", NULL, 0)));
    KWD_METHODS_UNBOUND_SPECIAL_VARIABLE = ((Keyword*)(internRigidSymbolWrtModule("UNBOUND-SPECIAL-VARIABLE", NULL, 2)));
    SYM_METHODS_STELLA_VARIABLE_HOME_MODULE = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-HOME-MODULE", NULL, 0)));
    SGT_METHODS_STELLA_LITERAL = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL", NULL, 1)));
    SGT_METHODS_STELLA_STRING = ((Surrogate*)(internRigidSymbolWrtModule("STRING", NULL, 1)));
    SGT_METHODS_STELLA_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER", NULL, 1)));
    SGT_METHODS_STELLA_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT", NULL, 1)));
    SGT_METHODS_STELLA_LONG_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("LONG-INTEGER", NULL, 1)));
    SGT_METHODS_STELLA_CHARACTER = ((Surrogate*)(internRigidSymbolWrtModule("CHARACTER", NULL, 1)));
    SGT_METHODS_STELLA_MUTABLE_STRING = ((Surrogate*)(internRigidSymbolWrtModule("MUTABLE-STRING", NULL, 1)));
    SGT_METHODS_STELLA_FUNCTION_CODE = ((Surrogate*)(internRigidSymbolWrtModule("FUNCTION-CODE", NULL, 1)));
    SGT_METHODS_STELLA_METHOD_CODE = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-CODE", NULL, 1)));
    SGT_METHODS_STELLA_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("WRAPPER", NULL, 1)));
    SYM_METHODS_STELLA_STARTUP_METHODS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-METHODS", NULL, 0)));
    SYM_METHODS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupMethods3() {
  {
    defineFunctionObject("APPLY", "(DEFUN (APPLY OBJECT) ((CODE FUNCTION-CODE) (ARGUMENTS (CONS OF OBJECT))) :DOCUMENTATION \"Apply `code' to `arguments', returning a value of type OBJECT.\nCurrently limited to at most 10 `arguments'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&apply)), NULL);
    defineFunctionObject("APPLY-METHOD", "(DEFUN (APPLY-METHOD OBJECT) ((CODE METHOD-CODE) (ARGUMENTS (CONS OF OBJECT))) :DOCUMENTATION \"Apply `code' to `arguments', returning a value of type\nOBJECT.\" :PUBLIC? TRUE)", ((cpp_function_code)(&applyMethod)), NULL);
    defineFunctionObject("APPLY-INTEGER-METHOD", "(DEFUN (APPLY-INTEGER-METHOD INTEGER) ((CODE METHOD-CODE) (ARGUMENTS (CONS OF OBJECT))) :DOCUMENTATION \"Apply `code' to `arguments', returning a value of type\nINTEGER.\" :PUBLIC? TRUE)", ((cpp_function_code)(&applyIntegerMethod)), NULL);
    defineFunctionObject("APPLY-LONG-INTEGER-METHOD", "(DEFUN (APPLY-LONG-INTEGER-METHOD LONG-INTEGER) ((CODE METHOD-CODE) (ARGUMENTS (CONS OF OBJECT))) :DOCUMENTATION \"Apply `code' to `arguments', returning a value of type\nLONG-INTEGER.\" :PUBLIC? TRUE)", ((cpp_function_code)(&applyLongIntegerMethod)), NULL);
    defineFunctionObject("APPLY-STRING-METHOD", "(DEFUN (APPLY-STRING-METHOD STRING) ((CODE METHOD-CODE) (ARGUMENTS (CONS OF OBJECT))) :DOCUMENTATION \"Apply `code' to `arguments', returning a value of type\nSTRING.\" :PUBLIC? TRUE)", ((cpp_function_code)(&applyStringMethod)), NULL);
    defineFunctionObject("APPLY-BOOLEAN-METHOD", "(DEFUN (APPLY-BOOLEAN-METHOD BOOLEAN) ((CODE METHOD-CODE) (ARGUMENTS (CONS OF OBJECT))) :DOCUMENTATION \"Apply `code' to `arguments', returning a value of type\nBOOLEAN.\" :PUBLIC? TRUE)", ((cpp_function_code)(&applyBooleanMethod)), NULL);
    defineFunctionObject("APPLY-FLOAT-METHOD", "(DEFUN (APPLY-FLOAT-METHOD FLOAT) ((CODE METHOD-CODE) (ARGUMENTS (CONS OF OBJECT))) :DOCUMENTATION \"Apply `code' to `arguments', returning a value of type\nFLOAT.\" :PUBLIC? TRUE)", ((cpp_function_code)(&applyFloatMethod)), NULL);
    defineFunctionObject("DEFINED-TYPE?", "(DEFUN (DEFINED-TYPE? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&definedTypeP)), NULL);
    defineFunctionObject("REAL-TYPE-SPECIFIER", "(DEFUN (REAL-TYPE-SPECIFIER TYPE-SPEC) ((TYPE TYPE)))", ((cpp_function_code)(&realTypeSpecifier)), NULL);
    defineFunctionObject("CANONICAL-TYPE", "(DEFUN (CANONICAL-TYPE TYPE) ((TYPE TYPE)))", ((cpp_function_code)(&canonicalType)), NULL);
    defineMethodObject("(DEFMETHOD (YIELD-TYPE-SPECIFIER TYPE-SPEC) ((TYPESPECTREE TYPE)))", wrapMethodCode(((cpp_method_code)(&Surrogate::yieldTypeSpecifier))), NULL);
    defineMethodObject("(DEFMETHOD (YIELD-TYPE-SPECIFIER TYPE-SPEC) ((TYPESPECTREE SYMBOL)))", wrapMethodCode(((cpp_method_code)(&Symbol::yieldTypeSpecifier))), NULL);
    defineMethodObject("(DEFMETHOD (YIELD-TYPE-SPECIFIER TYPE-SPEC) ((TYPESPECTREE PARAMETRIC-TYPE-SPECIFIER)))", wrapMethodCode(((cpp_method_code)(&ParametricTypeSpecifier::yieldTypeSpecifier))), NULL);
    defineMethodObject("(DEFMETHOD (YIELD-TYPE-SPECIFIER TYPE-SPEC) ((TYPESPECTREE ANCHORED-TYPE-SPECIFIER)))", wrapMethodCode(((cpp_method_code)(&AnchoredTypeSpecifier::yieldTypeSpecifier))), NULL);
    defineMethodObject("(DEFMETHOD (YIELD-TYPE-SPECIFIER TYPE-SPEC) ((TYPESPECTREE OBJECT)))", wrapMethodCode(((cpp_method_code)(&Object::yieldTypeSpecifier))), NULL);
    defineMethodObject("(DEFMETHOD (YIELD-TYPE-SPECIFIER TYPE-SPEC) ((TYPESPECTREE CONS)))", wrapMethodCode(((cpp_method_code)(&Cons::yieldTypeSpecifier))), NULL);
    defineFunctionObject("YIELD-PARAMETRIC-TYPE-SPECIFIER", "(DEFUN (YIELD-PARAMETRIC-TYPE-SPECIFIER PARAMETRIC-TYPE-SPECIFIER) ((TYPESPECTREE CONS)))", ((cpp_function_code)(&yieldParametricTypeSpecifier)), NULL);
    defineFunctionObject("PARSE-ARRAY-DIMENSIONS-SPEC", "(DEFUN (PARSE-ARRAY-DIMENSIONS-SPEC (LIST OF INTEGER-WRAPPER)) ((DIMENSIONSSPEC OBJECT)))", ((cpp_function_code)(&parseArrayDimensionsSpec)), NULL);
    defineFunctionObject("YIELD-ARRAY-DIMENSIONS-TREE", "(DEFUN (YIELD-ARRAY-DIMENSIONS-TREE CONS) ((ARRAYTYPE PARAMETRIC-TYPE-SPECIFIER)))", ((cpp_function_code)(&yieldArrayDimensionsTree)), NULL);
    defineFunctionObject("ARRAY-TYPE-SPECIFIER?", "(DEFUN (ARRAY-TYPE-SPECIFIER? BOOLEAN) ((TYPESPEC TYPE-SPEC)))", ((cpp_function_code)(((boolean  (*) (StandardObject*))(&arrayTypeSpecifierP)))), NULL);
    defineFunctionObject("ARRAY-TYPE-RANK", "(DEFUN (ARRAY-TYPE-RANK INTEGER) ((ARRAYTYPE PARAMETRIC-TYPE-SPECIFIER)))", ((cpp_function_code)(((int  (*) (ParametricTypeSpecifier*))(&arrayTypeRank)))), NULL);
    defineFunctionObject("ARRAY-TYPE-DIMENSIONS", "(DEFUN (ARRAY-TYPE-DIMENSIONS (LIST OF INTEGER-WRAPPER)) ((ARRAYTYPE PARAMETRIC-TYPE-SPECIFIER)))", ((cpp_function_code)(((List*  (*) (ParametricTypeSpecifier*))(&arrayTypeDimensions)))), NULL);
    defineFunctionObject("INDEFINITE-ARRAY-TYPE?", "(DEFUN (INDEFINITE-ARRAY-TYPE? BOOLEAN) ((ARRAYTYPE PARAMETRIC-TYPE-SPECIFIER)))", ((cpp_function_code)(&indefiniteArrayTypeP)), NULL);
    defineFunctionObject("YIELD-ANCHORED-TYPE-SPECIFIER", "(DEFUN (YIELD-ANCHORED-TYPE-SPECIFIER ANCHORED-TYPE-SPECIFIER) ((TYPESPECTREE CONS)))", ((cpp_function_code)(&yieldAnchoredTypeSpecifier)), NULL);
    defineFunctionObject("INCORPORATE-INPUT-PARAMETERS", "(DEFUN INCORPORATE-INPUT-PARAMETERS ((METHOD METHOD-SLOT) (PARAMETERS CONS)))", ((cpp_function_code)(&incorporateInputParameters)), NULL);
    defineFunctionObject("INCORPORATE-FIRST-INPUT-PARAMETER", "(DEFUN INCORPORATE-FIRST-INPUT-PARAMETER ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&incorporateFirstInputParameter)), NULL);
    defineFunctionObject("DEFINE-STELLA-METHOD-SLOT", "(DEFUN (DEFINE-STELLA-METHOD-SLOT METHOD-SLOT) ((INPUTNAME SYMBOL) (RETURNTYPES CONS) (FUNCTION? BOOLEAN) (INPUTPARAMETERS CONS) (OPTIONS KEYWORD-KEY-VALUE-LIST)) :DOCUMENTATION \"Define a new Stella method object (a slot), and attach it\nto the class identified by the first parameter in 'inputParameters'.\")", ((cpp_function_code)(&defineStellaMethodSlot)), NULL);
    defineFunctionObject("ATTACH-METHOD-SLOT-TO-OWNER", "(DEFUN (ATTACH-METHOD-SLOT-TO-OWNER METHOD-SLOT) ((NEWMETHOD METHOD-SLOT)))", ((cpp_function_code)(&attachMethodSlotToOwner)), NULL);
    defineFunctionObject("YIELD-STRING-CONSTANT-TREE", "(DEFUN (YIELD-STRING-CONSTANT-TREE OBJECT) ((STRING STRING)))", ((cpp_function_code)(&yieldStringConstantTree)), NULL);
    defineFunctionObject("DEFINE-FUNCTION-OBJECT-EAGERLY?", "(DEFUN (DEFINE-FUNCTION-OBJECT-EAGERLY? BOOLEAN) ((FUNCTION METHOD-SLOT)))", ((cpp_function_code)(&defineFunctionObjectEagerlyP)), NULL);
    defineFunctionObject("YIELD-DEFINE-STELLA-METHOD-OBJECT", "(DEFUN (YIELD-DEFINE-STELLA-METHOD-OBJECT CONS) ((METHOD METHOD-SLOT) (CODEMETHOD METHOD-SLOT) (WRAPPERMETHOD METHOD-SLOT)))", ((cpp_function_code)(&yieldDefineStellaMethodObject)), NULL);
    defineFunctionObject("YIELD-CLASS-PARAMETER-TYPES", "(DEFUN (YIELD-CLASS-PARAMETER-TYPES (CONS OF TYPE)) ((CLASS CLASS)))", ((cpp_function_code)(&yieldClassParameterTypes)), NULL);
    defineFunctionObject("OPTIMISTIC-SUBTYPE-OF?", "(DEFUN (OPTIMISTIC-SUBTYPE-OF? BOOLEAN) ((SUBTYPE TYPE) (SUPERTYPE TYPE)))", ((cpp_function_code)(&optimisticSubtypeOfP)), NULL);
    defineFunctionObject("WARN-OF-PARAMETER-MISMATCH", "(DEFUN WARN-OF-PARAMETER-MISMATCH ((SELF PARAMETRIC-TYPE-SPECIFIER) (MESSAGE STRING)))", ((cpp_function_code)(&warnOfParameterMismatch)), NULL);
    defineFunctionObject("VALIDATE-TYPE-SPECIFIER", "(DEFUN (VALIDATE-TYPE-SPECIFIER TYPE) ((SELF TYPE-SPEC) (ANCHORCLASS CLASS) (SKIPANCHOREDTYPE? BOOLEAN)))", ((cpp_function_code)(&validateTypeSpecifier)), NULL);
    defineFunctionObject("SYNTHESIZE-METHOD-BODY", "(DEFUN (SYNTHESIZE-METHOD-BODY CONS) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&synthesizeMethodBody)), NULL);
    defineMethodObject("(DEFMETHOD FINALIZE-SLOT-TYPE-COMPUTATIONS ((SELF METHOD-SLOT)))", wrapMethodCode(((cpp_method_code)(&MethodSlot::finalizeSlotTypeComputations))), NULL);
    defineMethodObject("(DEFMETHOD HELP-FINALIZE-LOCAL-SLOT ((SELF METHOD-SLOT)))", wrapMethodCode(((cpp_method_code)(&MethodSlot::helpFinalizeLocalSlot))), NULL);
    defineMethodObject("(DEFMETHOD UNFINALIZE-LOCAL-SLOT ((SELF METHOD-SLOT)))", wrapMethodCode(((cpp_method_code)(&MethodSlot::unfinalizeLocalSlot))), NULL);
    defineFunctionObject("UNDEFINE-EXTERNAL-SLOTS", "(DEFUN UNDEFINE-EXTERNAL-SLOTS ((NAME SYMBOL)))", ((cpp_function_code)(&undefineExternalSlots)), NULL);
    defineFunctionObject("DESTROY-EXTERNAL-SLOT", "(DEFUN DESTROY-EXTERNAL-SLOT ((SELF SLOT)))", ((cpp_function_code)(&destroyExternalSlot)), NULL);
    defineFunctionObject("DESTROY-METHOD", "(DEFUN DESTROY-METHOD ((SELF METHOD-SLOT)))", ((cpp_function_code)(&destroyMethod)), NULL);
    defineMethodObject("(DEFMETHOD (METHOD-ARGUMENT-COUNT INTEGER) ((SELF SLOT)))", wrapMethodCode(((cpp_method_code)(&Slot::methodArgumentCount))), NULL);
    defineMethodObject("(DEFMETHOD (METHOD-ARGUMENT-COUNT INTEGER) ((SELF STORAGE-SLOT)))", wrapMethodCode(((cpp_method_code)(&StorageSlot::methodArgumentCount))), NULL);
    defineMethodObject("(DEFMETHOD (METHOD-ARGUMENT-COUNT INTEGER) ((SELF METHOD-SLOT)))", wrapMethodCode(((cpp_method_code)(&MethodSlot::methodArgumentCount))), NULL);
    defineMethodObject("(DEFMETHOD (METHOD-ARGUMENT-COUNT INTEGER) ((SELF TABLE)))", wrapMethodCode(((cpp_method_code)(&Table::methodArgumentCount))), NULL);
    defineMethodObject("(DEFMETHOD (METHOD-VARIABLE-ARGUMENTS? BOOLEAN) ((SELF STORAGE-SLOT)))", wrapMethodCode(((cpp_method_code)(&StorageSlot::methodVariableArgumentsP))), NULL);
    defineMethodObject("(DEFMETHOD (METHOD-BODY-ARGUMENT? BOOLEAN) ((SELF STORAGE-SLOT)))", wrapMethodCode(((cpp_method_code)(&StorageSlot::methodBodyArgumentP))), NULL);
    defineMethodObject("(DEFMETHOD (ARITY INTEGER) ((SELF STORAGE-SLOT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StorageSlot::arity))), NULL);
    defineMethodObject("(DEFMETHOD (ARITY INTEGER) ((SELF METHOD-SLOT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&MethodSlot::arity))), NULL);
    defineMethodObject("(DEFMETHOD (ARITY INTEGER) ((SELF TABLE)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Table::arity))), NULL);
    defineFunctionObject("TYPE-SPEC-TO-BASE-TYPE", "(DEFUN (TYPE-SPEC-TO-BASE-TYPE TYPE) ((SELF TYPE-SPEC)) :PUBLIC? TRUE)", ((cpp_function_code)(&typeSpecToBaseType)), NULL);
    defineFunctionObject("BASE-TYPE-TO-TYPE-SPEC", "(DEFUN (BASE-TYPE-TO-TYPE-SPEC TYPE-SPEC) ((SELF TYPE-SPEC)))", ((cpp_function_code)(&baseTypeToTypeSpec)), NULL);
    defineFunctionObject("TYPE-SPEC-TO-CLASS", "(DEFUN (TYPE-SPEC-TO-CLASS CLASS) ((SELF TYPE-SPEC)) :PUBLIC? TRUE)", ((cpp_function_code)(&typeSpecToClass)), NULL);
    defineFunctionObject("COMPATIBLE-PARAMETER-TYPES?", "(DEFUN (COMPATIBLE-PARAMETER-TYPES? BOOLEAN) ((SUBTYPE TYPE-SPEC) (SUPERTYPE TYPE-SPEC)) :PUBLIC? TRUE)", ((cpp_function_code)(&compatibleParameterTypesP)), NULL);
    defineFunctionObject("SUB-TYPE-SPEC-OF?", "(DEFUN (SUB-TYPE-SPEC-OF? BOOLEAN) ((SUBTYPE TYPE-SPEC) (SUPERTYPE TYPE-SPEC)))", ((cpp_function_code)(&subTypeSpecOfP)), NULL);
    defineFunctionObject("VOID?", "(DEFUN (VOID? BOOLEAN) ((TYPE TYPE-SPEC)) :PUBLIC? TRUE)", ((cpp_function_code)(&voidP)), NULL);
    defineFunctionObject("EXTRACT-PARAMETER-TYPE", "(DEFUN (EXTRACT-PARAMETER-TYPE TYPE-SPEC BOOLEAN) ((SELF TYPE-SPEC) (PARAMETER SYMBOL)) :PUBLIC? TRUE)", ((cpp_function_code)(&extractParameterType)), NULL);
    defineFunctionObject("COMPUTE-ANCHORED-TYPE-SPEC", "(DEFUN (COMPUTE-ANCHORED-TYPE-SPEC TYPE-SPEC) ((OWNERTYPE TYPE-SPEC) (RELTYPE ANCHORED-TYPE-SPECIFIER)))", ((cpp_function_code)(&computeAnchoredTypeSpec)), NULL);
    defineFunctionObject("COMPUTE-RELATIVE-TYPE-SPEC", "(DEFUN (COMPUTE-RELATIVE-TYPE-SPEC TYPE-SPEC) ((RELATIVETYPE TYPE-SPEC) (OWNERTYPE TYPE-SPEC)))", ((cpp_function_code)(&computeRelativeTypeSpec)), NULL);
  }
}

void startupMethods() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupMethods1();
      helpStartupMethods2();
    }
    if (currentStartupTimePhaseP(4)) {
      oFUNCTION_LOOKUP_TABLEo = newHashTable();
      oGLOBAL_VARIABLE_LOOKUP_TABLEo = newHashTable();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupMethods3();
      defineMethodObject("(DEFMETHOD (COMPUTE-RETURN-TYPE-SPEC TYPE-SPEC) ((SELF SLOT) (FIRSTARGTYPE TYPE-SPEC)))", wrapMethodCode(((cpp_method_code)(&Slot::computeReturnTypeSpec))), NULL);
      defineMethodObject("(DEFMETHOD (COMPUTE-RETURN-TYPE-SPEC TYPE-SPEC) ((SELF METHOD-SLOT) (FIRSTARGTYPE TYPE-SPEC)))", wrapMethodCode(((cpp_method_code)(&MethodSlot::computeReturnTypeSpec))), NULL);
      defineMethodObject("(DEFMETHOD (COMPUTE-RETURN-TYPE-SPEC TYPE-SPEC) ((SELF STORAGE-SLOT) (FIRSTARGTYPE TYPE-SPEC)))", wrapMethodCode(((cpp_method_code)(&StorageSlot::computeReturnTypeSpec))), NULL);
      defineFunctionObject("YIELD-TYPE-SPEC-TREE", "(DEFUN (YIELD-TYPE-SPEC-TREE OBJECT) ((SELF TYPE-SPEC)))", ((cpp_function_code)(&yieldTypeSpecTree)), NULL);
      defineFunctionObject("ATTACH-FUNCTION", "(DEFUN (ATTACH-FUNCTION METHOD-SLOT) ((NEWFUNCTION METHOD-SLOT)))", ((cpp_function_code)(&attachFunction)), NULL);
      defineFunctionObject("LOOKUP-FUNCTION", "(DEFUN (LOOKUP-FUNCTION FUNCTION) ((FUNCTIONSYMBOL SYMBOL)) :DOCUMENTATION \"Return the function defined for 'functionSymbol', if it exists.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupFunction)), NULL);
      defineFunctionObject("LOOKUP-FUNCTION-BY-NAME", "(DEFUN (LOOKUP-FUNCTION-BY-NAME FUNCTION) ((NAME STRING)) :DOCUMENTATION \"Return a function with name 'name' visible from the current module.\nScan all visible symbols looking for one that has a function defined for it.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupFunctionByName)), NULL);
      defineFunctionObject("LOOKUP-FUNCTION-BY-QUALIFIED-NAME", "(DEFUN (LOOKUP-FUNCTION-BY-QUALIFIED-NAME METHOD-SLOT) ((QUALIFIEDNAME STRING)) :DOCUMENTATION \"Variant of `lookup-function-by-name' that can specify a starting\nmodule through a `qualifiedName'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupFunctionByQualifiedName)), NULL);
      defineFunctionObject("LOOKUP-FUNCTION-OR-STELLA-FUNCTION", "(DEFUN (LOOKUP-FUNCTION-OR-STELLA-FUNCTION FUNCTION) ((FUNCTIONSYMBOL SYMBOL)) :GLOBALLY-INLINE? TRUE (RETURN (LOOKUP-FUNCTION FUNCTIONSYMBOL)))", ((cpp_function_code)(&lookupFunctionOrStellaFunction)), NULL);
      defineFunctionObject("LOOKUP-FUNCTION-HOME-MODULE", "(DEFUN (LOOKUP-FUNCTION-HOME-MODULE MODULE) ((FUNCTIONSYMBOL SYMBOL)))", ((cpp_function_code)(&lookupFunctionHomeModule)), NULL);
      defineFunctionObject("UNDEFINE-FUNCTION", "(DEFUN UNDEFINE-FUNCTION ((NAME SYMBOL)))", ((cpp_function_code)(&undefineFunction)), NULL);
      defineFunctionObject("DESTROY-FUNCTION", "(DEFUN DESTROY-FUNCTION ((FUNCTION METHOD-SLOT)))", ((cpp_function_code)(&destroyFunction)), NULL);
      defineFunctionObject("UNDEFINE-CONFLICTING-DEFINITIONS?", "(DEFUN (UNDEFINE-CONFLICTING-DEFINITIONS? BOOLEAN) ((NEWSLOT METHOD-SLOT)))", ((cpp_function_code)(&undefineConflictingDefinitionsP)), NULL);
      defineFunctionObject("DEFINE-FUNCTION-OBJECT", "(DEFUN DEFINE-FUNCTION-OBJECT ((NAME STRING) (DEFINITION STRING) (CODE FUNCTION-CODE) (WRAPPERCODE FUNCTION-CODE)))", ((cpp_function_code)(&defineFunctionObject)), NULL);
      defineFunctionObject("INTERN-GLOBAL-VARIABLE", "(DEFUN (INTERN-GLOBAL-VARIABLE GLOBAL-VARIABLE) ((GLOBAL GLOBAL-VARIABLE)))", ((cpp_function_code)(&internGlobalVariable)), NULL);
      defineMethodObject("(DEFMETHOD (LOOKUP-GLOBAL-VARIABLE GLOBAL-VARIABLE) ((SELF GENERALIZED-SYMBOL)) :PUBLIC? TRUE :DOCUMENTATION \"Return a global variable with name 'self'.\")", wrapMethodCode(((cpp_method_code)(&GeneralizedSymbol::lookupGlobalVariable))), NULL);
      defineMethodObject("(DEFMETHOD (LOOKUP-GLOBAL-VARIABLE GLOBAL-VARIABLE) ((SELF SURROGATE)) :PUBLIC? TRUE :DOCUMENTATION \"Return a global variable with name 'self'.\")", wrapMethodCode(((cpp_method_code)(&Surrogate::lookupGlobalVariable))), NULL);
      defineMethodObject("(DEFMETHOD (LOOKUP-GLOBAL-VARIABLE GLOBAL-VARIABLE) ((SELF STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Return a global variable with name 'self'.\")", wrapFunctionCode(((cpp_function_code)(((GlobalVariable*  (*) (const char*))(&stringLookupGlobalVariable))))), NULL);
      defineFunctionObject("LOOKUP-GLOBAL-VARIABLE-BY-NAME", "(DEFUN (LOOKUP-GLOBAL-VARIABLE-BY-NAME GLOBAL-VARIABLE) ((NAME STRING)) :DOCUMENTATION \"Return a global variable with `name' visible from the current module.\nScan all visible symbols looking for one that has a global variable defined for it.\nNOTE: this is more robust than STRING.lookup-global-variable which will fail if there\nis a local symbol with `name' which shadows one higher up that is the name of a global.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupGlobalVariableByName)), NULL);
      defineFunctionObject("LOOKUP-GLOBAL-VARIABLE-BY-QUALIFIED-NAME", "(DEFUN (LOOKUP-GLOBAL-VARIABLE-BY-QUALIFIED-NAME GLOBAL-VARIABLE) ((QUALIFIEDNAME STRING)) :DOCUMENTATION \"Variant of `lookup-global-variable-by-name' that can specify a starting\nmodule through a `qualifiedName'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupGlobalVariableByQualifiedName)), NULL);
      defineFunctionObject("GLOBAL-VARIABLE-TYPE-SPEC", "(DEFUN (GLOBAL-VARIABLE-TYPE-SPEC TYPE-SPEC) ((GLOBAL GLOBAL-VARIABLE)) :DOCUMENTATION \"Return the type spec for the global variable `global'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&globalVariableTypeSpec)), NULL);
      defineFunctionObject("LOOKUP-GLOBAL-VARIABLE-TYPE", "(DEFUN (LOOKUP-GLOBAL-VARIABLE-TYPE TYPE-SPEC) ((NAME SYMBOL)) :PUBLIC? TRUE)", ((cpp_function_code)(&lookupGlobalVariableType)), NULL);
      defineFunctionObject("DEFINE-STELLA-GLOBAL-VARIABLE-FROM-PARSE-TREE", "(DEFUN (DEFINE-STELLA-GLOBAL-VARIABLE-FROM-PARSE-TREE GLOBAL-VARIABLE OBJECT) ((TREE CONS) (STRINGIFIEDSOURCE STRING)))", ((cpp_function_code)(&defineStellaGlobalVariableFromParseTree)), NULL);
      defineFunctionObject("DEFINE-STELLA-GLOBAL-VARIABLE-FROM-STRINGIFIED-SOURCE", "(DEFUN DEFINE-STELLA-GLOBAL-VARIABLE-FROM-STRINGIFIED-SOURCE ((STRINGIFIEDSOURCE STRING)) :DOCUMENTATION \"Define a stella global variable using a parse tree derived from 'stringifiedSource'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&defineStellaGlobalVariableFromStringifiedSource)), NULL);
      defineFunctionObject("DEFINE-GLOBAL-VARIABLE-OBJECT", "(DEFUN DEFINE-GLOBAL-VARIABLE-OBJECT ((DEFINITION STRING) (NATIVEOBJECT NATIVE-OBJECT-POINTER)) :DOCUMENTATION \"Define a STELLA global variable object based on `definition', and initialize\nits variable-native-object slot to `nativeObject' (which is primarily needed for C++).\" :PUBLIC? TRUE)", ((cpp_function_code)(&defineGlobalVariableObject)), NULL);
      defineFunctionObject("RECORD-VARIABLE-HOME-MODULE", "(DEFUN (RECORD-VARIABLE-HOME-MODULE MODULE) ((SELF GLOBAL-VARIABLE)))", ((cpp_function_code)(&recordVariableHomeModule)), NULL);
      defineFunctionObject("DESTROY-GLOBAL-VARIABLE", "(DEFUN DESTROY-GLOBAL-VARIABLE ((VARIABLE GLOBAL-VARIABLE)))", ((cpp_function_code)(&destroyGlobalVariable)), NULL);
      defineFunctionObject("GET-GLOBAL-VARIABLE-NATIVE-OBJECT", "(DEFUN (GET-GLOBAL-VARIABLE-NATIVE-OBJECT NATIVE-OBJECT-POINTER) ((VARIABLE GLOBAL-VARIABLE)) :DOCUMENTATION \"Return the native object of `variable' which can be used to access its runtime value.\nIn Lisp this is the Lisp symbol which holds the variable value, in C++ this is the address of the variable,\nand in Java this is the declared Field object.  For C++ native object addresses are initialized at startup\ntime, for Lisp and Java native objects will be accessed upon first call and then cached in the slot.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getGlobalVariableNativeObject)), NULL);
      defineFunctionObject("READ-NATIVE-VARIABLE-VALUE", "(DEFUN (READ-NATIVE-VARIABLE-VALUE OBJECT) ((VAR NATIVE-OBJECT-POINTER) (TYPE TYPE)) :DOCUMENTATION \"Interpreted variable reader which reads a native code variable represented by\n`var' of type `type' and returns its value which will be wrapped if necessary.  If `var' is a\nspecial variable, this will access the current dynamic value at the top of the special stack.\nThis relies upon `type' being completely accurate and bad things will happen if it is not.\" :PUBLIC? TRUE)", ((cpp_function_code)(&readNativeVariableValue)), NULL);
      defineFunctionObject("WRITE-NATIVE-VARIABLE-VALUE", "(DEFUN WRITE-NATIVE-VARIABLE-VALUE ((VAR NATIVE-OBJECT-POINTER) (TYPE TYPE) (VALUE OBJECT)) :DOCUMENTATION \"Interpreted variable writer which sets a native code variable represented by\n`var' of type `type' to `value' which will be unwrapped if necessary.  If `var' is a special\nvariable, this will change the current dynamic value at the top of the special stack.  This\nrelies upon `type' being completely accurate and bad things will happen if it is not.\" :PUBLIC? TRUE)", ((cpp_function_code)(&writeNativeVariableValue)), NULL);
      defineFunctionObject("READ-GLOBAL-VARIABLE-VALUE", "(DEFUN (READ-GLOBAL-VARIABLE-VALUE OBJECT) ((VARIABLE GLOBAL-VARIABLE)) :DOCUMENTATION \"Interpreted global `variable' reader which reads and returns its native value\nwhich will be wrapped if necessary.  This will access the value at the top of the special stack.\" :PUBLIC? TRUE)", ((cpp_function_code)(&readGlobalVariableValue)), NULL);
      defineFunctionObject("WRITE-GLOBAL-VARIABLE-VALUE", "(DEFUN WRITE-GLOBAL-VARIABLE-VALUE ((VARIABLE GLOBAL-VARIABLE) (VALUE OBJECT)) :DOCUMENTATION \"Interpreted global `variable' writer which sets its native value to `value'\nunwrappig it if necessary.  This will change the current value at the top of the special stack.\" :PUBLIC? TRUE)", ((cpp_function_code)(&writeGlobalVariableValue)), NULL);
      defineFunctionObject("DEFINE-STELLA-TYPE-FROM-PARSE-TREE", "(DEFUN (DEFINE-STELLA-TYPE-FROM-PARSE-TREE TYPE) ((TREE CONS)) :PUBLIC? TRUE)", ((cpp_function_code)(&defineStellaTypeFromParseTree)), NULL);
      defineFunctionObject("DEFINE-STELLA-TYPE-FROM-STRINGIFIED-SOURCE", "(DEFUN DEFINE-STELLA-TYPE-FROM-STRINGIFIED-SOURCE ((STRINGIFIEDSOURCE STRING)) :PUBLIC? TRUE)", ((cpp_function_code)(&defineStellaTypeFromStringifiedSource)), NULL);
      defineFunctionObject("STARTUP-METHODS", "(DEFUN STARTUP-METHODS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupMethods)), NULL);
      { MethodSlot* function = lookupFunction(SYM_METHODS_STELLA_STARTUP_METHODS);

        setDynamicSlotValue(function->dynamicSlots, SYM_METHODS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupMethods"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *MAXIMUM-STRING-CONSTANT-SIZE* INTEGER 4000 :DOCUMENTATION \"Maximum size for a string constant in the target language.\")", &oMAXIMUM_STRING_CONSTANT_SIZEo);
      defineGlobalVariableObject("(DEFGLOBAL *FUNCTION-LOOKUP-TABLE* (HASH-TABLE OF SYMBOL STANDARD-OBJECT) (NEW (HASH-TABLE OF SYMBOL FUNCTION)) :DOCUMENTATION \"Lookup table for functions.\")", &oFUNCTION_LOOKUP_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *GLOBAL-VARIABLE-LOOKUP-TABLE* (HASH-TABLE OF SYMBOL GLOBAL-VARIABLE) (NEW (HASH-TABLE OF SYMBOL GLOBAL-VARIABLE)) :DOCUMENTATION \"Lookup table for global variables.\" :PUBLIC? TRUE)", &oGLOBAL_VARIABLE_LOOKUP_TABLEo);
    }
  }
}

Surrogate* SGT_METHODS_STELLA_SURROGATE = NULL;

Surrogate* SGT_METHODS_STELLA_PARAMETRIC_TYPE_SPECIFIER = NULL;

Surrogate* SGT_METHODS_STELLA_ANCHORED_TYPE_SPECIFIER = NULL;

Surrogate* SGT_METHODS_STELLA_OBJECT = NULL;

Surrogate* SGT_METHODS_STELLA_VOID = NULL;

Symbol* SYM_METHODS_STELLA_LIKE = NULL;

Symbol* SYM_METHODS_STELLA_SIZE = NULL;

Symbol* SYM_METHODS_STELLA_UNKNOWN = NULL;

Symbol* SYM_METHODS_STELLA_OF = NULL;

Symbol* SYM_METHODS_STELLA_NULL = NULL;

Surrogate* SGT_METHODS_STELLA_ARRAY = NULL;

Symbol* SYM_METHODS_STELLA_SELF = NULL;

Surrogate* SGT_METHODS_STELLA_CONS = NULL;

Symbol* SYM_METHODS_STELLA_IN = NULL;

Symbol* SYM_METHODS_STELLA_OUT = NULL;

Symbol* SYM_METHODS_STELLA_INOUT = NULL;

Symbol* SYM_METHODS_STELLA_METHOD_PARAMETER_DIRECTIONS = NULL;

Symbol* SYM_METHODS_STELLA_ARGUMENT_LIST = NULL;

Symbol* SYM_METHODS_STELLA_aREST = NULL;

Symbol* SYM_METHODS_STELLA_METHOD_VARIABLE_ARGUMENTSp = NULL;

Symbol* SYM_METHODS_STELLA_aBODY = NULL;

Symbol* SYM_METHODS_STELLA_METHOD_BODY_ARGUMENTp = NULL;

Surrogate* SGT_METHODS_STELLA_UNKNOWN = NULL;

Keyword* KWD_METHODS_TYPE = NULL;

Keyword* KWD_METHODS_RETURN_TYPES = NULL;

Symbol* SYM_METHODS_STELLA_SLOT_TYPE_SPECIFIER = NULL;

Keyword* KWD_METHODS_PUBLICp = NULL;

Keyword* KWD_METHODS_ABSTRACTp = NULL;

Keyword* KWD_METHODS_NATIVEp = NULL;

Symbol* SYM_METHODS_STELLA_METHOD_NATIVEp = NULL;

Keyword* KWD_METHODS_CONSTRUCTORp = NULL;

Symbol* SYM_METHODS_STELLA_METHOD_CONSTRUCTORp = NULL;

Keyword* KWD_METHODS_GLOBALLY_INLINEp = NULL;

Symbol* SYM_METHODS_STELLA_METHOD_GLOBALLY_INLINEp = NULL;

Keyword* KWD_METHODS_INLINE = NULL;

Symbol* SYM_METHODS_STELLA_METHOD_INLINED_FUNCTIONS = NULL;

Keyword* KWD_METHODS_AUXILIARYp = NULL;

Symbol* SYM_METHODS_STELLA_SLOT_AUXILIARYp = NULL;

Keyword* KWD_METHODS_DOCUMENTATION = NULL;

Symbol* SYM_METHODS_STELLA_DOCUMENTATION = NULL;

Keyword* KWD_METHODS_RETURNS = NULL;

Keyword* KWD_METHODS_STORAGE_SLOT = NULL;

Symbol* SYM_METHODS_STELLA_STORAGE_SLOT = NULL;

Keyword* KWD_METHODS_INHERITS_THROUGH = NULL;

Symbol* SYM_METHODS_STELLA_METHOD_INHERITS_THROUGH = NULL;

Keyword* KWD_METHODS_PROPERTIES = NULL;

Symbol* SYM_METHODS_STELLA_PROPERTIES = NULL;

Keyword* KWD_METHODS_META_ATTRIBUTES = NULL;

Symbol* SYM_METHODS_STELLA_META_ATTRIBUTES = NULL;

Keyword* KWD_METHODS_COMMANDp = NULL;

Symbol* SYM_METHODS_STELLA_METHOD_COMMANDp = NULL;

Keyword* KWD_METHODS_LISP_MACROp = NULL;

Symbol* SYM_METHODS_STELLA_METHOD_LISP_MACROp = NULL;

Keyword* KWD_METHODS_EVALUATE_ARGUMENTSp = NULL;

Symbol* SYM_METHODS_STELLA_METHOD_EVALUATE_ARGUMENTSp = NULL;

Keyword* KWD_METHODS_C_CALLABLEp = NULL;

Symbol* SYM_METHODS_STELLA_METHOD_C_CALLABLEp = NULL;

Symbol* SYM_METHODS_STELLA_CONCATENATE = NULL;

Surrogate* SGT_METHODS_STELLA_METHOD_SLOT = NULL;

Symbol* SYM_METHODS_STELLA_SLOT_OPTION_HANDLER = NULL;

Symbol* SYM_METHODS_STELLA_DEFINE_FUNCTION_OBJECT = NULL;

Symbol* SYM_METHODS_STELLA_THE_CODE = NULL;

Keyword* KWD_METHODS_FUNCTION = NULL;

Symbol* SYM_METHODS_STELLA_DEFINE_INLINE_METHOD_CODE = NULL;

Symbol* SYM_METHODS_STELLA_QUOTE = NULL;

Keyword* KWD_METHODS_METHOD = NULL;

Symbol* SYM_METHODS_STELLA_DEFINE_METHOD_OBJECT = NULL;

Surrogate* SGT_METHODS_STELLA_BOOLEAN = NULL;

Symbol* SYM_METHODS_STELLA_SUPER_CLASSES = NULL;

Symbol* SYM_METHODS_STELLA_EQUIVALENT_SLOT = NULL;

Symbol* SYM_METHODS_STELLA_CLASS_ALL_SUPER_CLASSES = NULL;

Symbol* SYM_METHODS_STELLA_SLOT_DIRECT_EQUIVALENT = NULL;

Symbol* SYM_METHODS_STELLA_LET = NULL;

Symbol* SYM_METHODS_STELLA_CURSOR = NULL;

Symbol* SYM_METHODS_STELLA_VALUE = NULL;

Symbol* SYM_METHODS_STELLA_SLOT_VALUE = NULL;

Symbol* SYM_METHODS_STELLA_LOOP = NULL;

Symbol* SYM_METHODS_STELLA_WHEN = NULL;

Symbol* SYM_METHODS_STELLA_RETURN = NULL;

Symbol* SYM_METHODS_STELLA_SETQ = NULL;

Symbol* SYM_METHODS_STELLA_IF = NULL;

Symbol* SYM_METHODS_STELLA_DEFINEDp = NULL;

Surrogate* SGT_METHODS_STELLA_COLLECTION = NULL;

Symbol* SYM_METHODS_STELLA_FIRST = NULL;

Symbol* SYM_METHODS_STELLA_VARIABLE_ARITY_TABLEp = NULL;

Surrogate* SGT_METHODS_STELLA_VECTOR = NULL;

Symbol* SYM_METHODS_STELLA_EVALUATOR_WRAPPER_CODE = NULL;

Symbol* SYM_METHODS_STELLA_METHOD_MACROp = NULL;

Symbol* SYM_METHODS_STELLA_VARIABLE_TYPE_SPECIFIER = NULL;

Symbol* SYM_METHODS_STELLA_DEFSPECIAL = NULL;

Symbol* SYM_METHODS_STELLA_DEFCONSTANT = NULL;

Keyword* KWD_METHODS_UNBOUND_SPECIAL_VARIABLE = NULL;

Symbol* SYM_METHODS_STELLA_VARIABLE_HOME_MODULE = NULL;

Surrogate* SGT_METHODS_STELLA_LITERAL = NULL;

Surrogate* SGT_METHODS_STELLA_STRING = NULL;

Surrogate* SGT_METHODS_STELLA_INTEGER = NULL;

Surrogate* SGT_METHODS_STELLA_FLOAT = NULL;

Surrogate* SGT_METHODS_STELLA_LONG_INTEGER = NULL;

Surrogate* SGT_METHODS_STELLA_CHARACTER = NULL;

Surrogate* SGT_METHODS_STELLA_MUTABLE_STRING = NULL;

Surrogate* SGT_METHODS_STELLA_FUNCTION_CODE = NULL;

Surrogate* SGT_METHODS_STELLA_METHOD_CODE = NULL;

Surrogate* SGT_METHODS_STELLA_WRAPPER = NULL;

Symbol* SYM_METHODS_STELLA_STARTUP_METHODS = NULL;

Symbol* SYM_METHODS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
