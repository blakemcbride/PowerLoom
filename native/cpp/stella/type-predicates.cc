//  -*- Mode: C++ -*-

// type-predicates.cc

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

boolean oCLASS_HIERARCHY_BOOTEDpo = false;

Surrogate* safePrimaryType(Object* x) {
  return (((!((boolean)(x))) ? SGT_TYPE_PREDICATES_STELLA_UNKNOWN : x->primaryType()));
}

boolean bootstrapIsaP(Object* x, Surrogate* type) {
  return (((boolean)(x)) &&
      ((x->primaryType() == type) ||
       (((boolean)(type->surrogateValue)) &&
        (((boolean)(x->primaryType()->surrogateValue)) &&
         isaP(x, type)))));
}

boolean bootstrapSubtypeOfP(Surrogate* subtype, Surrogate* supertype) {
  return ((subtype == supertype) ||
      (((boolean)(((Class*)(subtype->surrogateValue)))) &&
       (((boolean)(((Class*)(supertype->surrogateValue)))) &&
        subtypeOfP(subtype, supertype))));
}

boolean booleanP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_BOOLEAN_WRAPPER));
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_BOOLEAN_WRAPPER));
}

boolean subtypeOfBooleanP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (subclassOfP(((Class*)(type->surrogateValue)), ((Class*)(SGT_TYPE_PREDICATES_STELLA_BOOLEAN_WRAPPER->surrogateValue))));
  }
  else {
    return (bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_BOOLEAN_WRAPPER));
  }
}

boolean integerP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_INTEGER_WRAPPER));
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_INTEGER_WRAPPER));
}

boolean subtypeOfIntegerP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (subclassOfP(((Class*)(type->surrogateValue)), ((Class*)(SGT_TYPE_PREDICATES_STELLA_INTEGER_WRAPPER->surrogateValue))));
  }
  else {
    return (bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_INTEGER_WRAPPER));
  }
}

boolean longIntegerP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_LONG_INTEGER_WRAPPER));
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_LONG_INTEGER_WRAPPER));
}

boolean subtypeOfLongIntegerP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (subclassOfP(((Class*)(type->surrogateValue)), ((Class*)(SGT_TYPE_PREDICATES_STELLA_LONG_INTEGER_WRAPPER->surrogateValue))));
  }
  else {
    return (bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_LONG_INTEGER_WRAPPER));
  }
}

boolean floatP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_FLOAT_WRAPPER));
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_FLOAT_WRAPPER));
}

boolean subtypeOfFloatP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (subclassOfP(((Class*)(type->surrogateValue)), ((Class*)(SGT_TYPE_PREDICATES_STELLA_FLOAT_WRAPPER->surrogateValue))));
  }
  else {
    return (bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_FLOAT_WRAPPER));
  }
}

boolean stringP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_STRING_WRAPPER));
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_STRING_WRAPPER) ||
      bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_VERBATIM_STRING_WRAPPER));
}

boolean subtypeOfStringP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (subclassOfP(((Class*)(type->surrogateValue)), ((Class*)(SGT_TYPE_PREDICATES_STELLA_STRING_WRAPPER->surrogateValue))));
  }
  else {
    return (bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_STRING_WRAPPER) ||
        bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_VERBATIM_STRING_WRAPPER));
  }
}

boolean verbatimStringP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_VERBATIM_STRING_WRAPPER));
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_VERBATIM_STRING_WRAPPER));
}

boolean subtypeOfVerbatimStringP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (subclassOfP(((Class*)(type->surrogateValue)), ((Class*)(SGT_TYPE_PREDICATES_STELLA_VERBATIM_STRING_WRAPPER->surrogateValue))));
  }
  else {
    return (bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_VERBATIM_STRING_WRAPPER));
  }
}

boolean characterP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_CHARACTER_WRAPPER));
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_CHARACTER_WRAPPER));
}

boolean subtypeOfCharacterP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (subclassOfP(((Class*)(type->surrogateValue)), ((Class*)(SGT_TYPE_PREDICATES_STELLA_CHARACTER_WRAPPER->surrogateValue))));
  }
  else {
    return (bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_CHARACTER_WRAPPER));
  }
}

boolean wrapperP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_WRAPPER));
  }
  return (booleanP(x) ||
      (integerP(x) ||
       (longIntegerP(x) ||
        (floatP(x) ||
         (stringP(x) ||
          (characterP(x) ||
           bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_WRAPPER)))))));
}

boolean subtypeOfWrapperP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (subclassOfP(((Class*)(type->surrogateValue)), ((Class*)(SGT_TYPE_PREDICATES_STELLA_WRAPPER->surrogateValue))));
  }
  else {
    return (subtypeOfBooleanP(type) ||
        (subtypeOfIntegerP(type) ||
         (subtypeOfLongIntegerP(type) ||
          (subtypeOfFloatP(type) ||
           (subtypeOfStringP(type) ||
            (subtypeOfCharacterP(type) ||
             bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_WRAPPER)))))));
  }
}

boolean surrogateP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_SURROGATE));
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_SURROGATE));
}

boolean subtypeOfSurrogateP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (subclassOfP(((Class*)(type->surrogateValue)), ((Class*)(SGT_TYPE_PREDICATES_STELLA_SURROGATE->surrogateValue))));
  }
  else {
    return (bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_SURROGATE));
  }
}

boolean typeP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_SURROGATE));
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_SURROGATE));
}

boolean subtypeOfTypeP(Surrogate* type) {
  return (subtypeOfSurrogateP(type));
}

boolean symbolP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_SYMBOL));
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_SYMBOL) ||
      bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_TRANSIENT_SYMBOL));
}

boolean subtypeOfSymbolP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (subclassOfP(((Class*)(type->surrogateValue)), ((Class*)(SGT_TYPE_PREDICATES_STELLA_SYMBOL->surrogateValue))));
  }
  else {
    return (bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_SYMBOL) ||
        bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_TRANSIENT_SYMBOL));
  }
}

boolean transientSymbolP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_TRANSIENT_SYMBOL));
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_TRANSIENT_SYMBOL));
}

boolean subtypeOfTransientSymbolP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (subclassOfP(((Class*)(type->surrogateValue)), ((Class*)(SGT_TYPE_PREDICATES_STELLA_TRANSIENT_SYMBOL->surrogateValue))));
  }
  else {
    return (bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_TRANSIENT_SYMBOL));
  }
}

boolean keywordP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_KEYWORD));
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_KEYWORD));
}

boolean subtypeOfKeywordP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (subclassOfP(((Class*)(type->surrogateValue)), ((Class*)(SGT_TYPE_PREDICATES_STELLA_KEYWORD->surrogateValue))));
  }
  else {
    return (bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_KEYWORD));
  }
}

boolean consP(Object* x) {
  if (((boolean)(x))) {
    return (x->primaryType() == SGT_TYPE_PREDICATES_STELLA_CONS);
  }
  else {
    return (false);
  }
}

boolean subtypeOfConsP(Surrogate* type) {
  return (type == SGT_TYPE_PREDICATES_STELLA_CONS);
}

boolean stellaClassP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    if (((boolean)(x))) {
      { Class* typeclass = ((Class*)(x->primaryType()->surrogateValue));

        return (((boolean)(typeclass)) &&
            subclassOfP(typeclass, ((Class*)(SGT_TYPE_PREDICATES_STELLA_CLASS->surrogateValue))));
      }
    }
    else {
      return (false);
    }
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_CLASS));
}

boolean subtypeOfClassP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    { Class* typeclass = ((Class*)(type->surrogateValue));

      return (((boolean)(typeclass)) &&
          subclassOfP(typeclass, ((Class*)(SGT_TYPE_PREDICATES_STELLA_CLASS->surrogateValue))));
    }
  }
  else {
    return (bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_CLASS));
  }
}

boolean storageSlotP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_STORAGE_SLOT));
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_STORAGE_SLOT));
}

boolean subtypeOfStorageSlotP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (subclassOfP(((Class*)(type->surrogateValue)), ((Class*)(SGT_TYPE_PREDICATES_STELLA_STORAGE_SLOT->surrogateValue))));
  }
  else {
    return (bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_STORAGE_SLOT));
  }
}

boolean methodSlotP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_METHOD_SLOT));
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_METHOD_SLOT));
}

boolean subtypeOfMethodSlotP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (subclassOfP(((Class*)(type->surrogateValue)), ((Class*)(SGT_TYPE_PREDICATES_STELLA_METHOD_SLOT->surrogateValue))));
  }
  else {
    return (bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_METHOD_SLOT));
  }
}

boolean anchoredTypeSpecifierP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_ANCHORED_TYPE_SPECIFIER));
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_ANCHORED_TYPE_SPECIFIER));
}

boolean subtypeOfAnchoredTypeSpecifierP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (subclassOfP(((Class*)(type->surrogateValue)), ((Class*)(SGT_TYPE_PREDICATES_STELLA_ANCHORED_TYPE_SPECIFIER->surrogateValue))));
  }
  else {
    return (bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_ANCHORED_TYPE_SPECIFIER));
  }
}

boolean parametricTypeSpecifierP(Object* x) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (((boolean)(x)) &&
        isaP(x, SGT_TYPE_PREDICATES_STELLA_PARAMETRIC_TYPE_SPECIFIER));
  }
  return (bootstrapIsaP(x, SGT_TYPE_PREDICATES_STELLA_PARAMETRIC_TYPE_SPECIFIER));
}

boolean subtypeOfParametricTypeSpecifierP(Surrogate* type) {
  if (oCLASS_HIERARCHY_BOOTEDpo) {
    return (subclassOfP(((Class*)(type->surrogateValue)), ((Class*)(SGT_TYPE_PREDICATES_STELLA_PARAMETRIC_TYPE_SPECIFIER->surrogateValue))));
  }
  else {
    return (bootstrapSubtypeOfP(type, SGT_TYPE_PREDICATES_STELLA_PARAMETRIC_TYPE_SPECIFIER));
  }
}

boolean Object::standardObjectP() {
  { Object* self = this;

    return (false);
  }
}

boolean StandardObject::standardObjectP() {
  { StandardObject* self = this;

    return (true);
  }
}

void helpStartupTypePredicates1() {
  {
    SGT_TYPE_PREDICATES_STELLA_UNKNOWN = ((Surrogate*)(internRigidSymbolWrtModule("UNKNOWN", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_BOOLEAN_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN-WRAPPER", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_INTEGER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER-WRAPPER", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_LONG_INTEGER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("LONG-INTEGER-WRAPPER", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_FLOAT_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT-WRAPPER", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("STRING-WRAPPER", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_VERBATIM_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("VERBATIM-STRING-WRAPPER", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_CHARACTER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("CHARACTER-WRAPPER", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("WRAPPER", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_SURROGATE = ((Surrogate*)(internRigidSymbolWrtModule("SURROGATE", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("SYMBOL", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_TRANSIENT_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("TRANSIENT-SYMBOL", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_KEYWORD = ((Surrogate*)(internRigidSymbolWrtModule("KEYWORD", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_CLASS = ((Surrogate*)(internRigidSymbolWrtModule("CLASS", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_STORAGE_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("STORAGE-SLOT", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_METHOD_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-SLOT", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_ANCHORED_TYPE_SPECIFIER = ((Surrogate*)(internRigidSymbolWrtModule("ANCHORED-TYPE-SPECIFIER", NULL, 1)));
    SGT_TYPE_PREDICATES_STELLA_PARAMETRIC_TYPE_SPECIFIER = ((Surrogate*)(internRigidSymbolWrtModule("PARAMETRIC-TYPE-SPECIFIER", NULL, 1)));
    SYM_TYPE_PREDICATES_STELLA_STARTUP_TYPE_PREDICATES = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-TYPE-PREDICATES", NULL, 0)));
    SYM_TYPE_PREDICATES_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void startupTypePredicates() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupTypePredicates1();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("SAFE-PRIMARY-TYPE", "(DEFUN (SAFE-PRIMARY-TYPE TYPE) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&safePrimaryType)), NULL);
      defineFunctionObject("BOOTSTRAP-ISA?", "(DEFUN (BOOTSTRAP-ISA? BOOLEAN) ((X OBJECT) (TYPE TYPE)))", ((cpp_function_code)(&bootstrapIsaP)), NULL);
      defineFunctionObject("BOOTSTRAP-SUBTYPE-OF?", "(DEFUN (BOOTSTRAP-SUBTYPE-OF? BOOLEAN) ((SUBTYPE TYPE) (SUPERTYPE TYPE)))", ((cpp_function_code)(&bootstrapSubtypeOfP)), NULL);
      defineFunctionObject("BOOLEAN?", "(DEFUN (BOOLEAN? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&booleanP)), NULL);
      defineFunctionObject("SUBTYPE-OF-BOOLEAN?", "(DEFUN (SUBTYPE-OF-BOOLEAN? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfBooleanP)), NULL);
      defineFunctionObject("INTEGER?", "(DEFUN (INTEGER? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&integerP)), NULL);
      defineFunctionObject("SUBTYPE-OF-INTEGER?", "(DEFUN (SUBTYPE-OF-INTEGER? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfIntegerP)), NULL);
      defineFunctionObject("LONG-INTEGER?", "(DEFUN (LONG-INTEGER? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&longIntegerP)), NULL);
      defineFunctionObject("SUBTYPE-OF-LONG-INTEGER?", "(DEFUN (SUBTYPE-OF-LONG-INTEGER? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfLongIntegerP)), NULL);
      defineFunctionObject("FLOAT?", "(DEFUN (FLOAT? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&floatP)), NULL);
      defineFunctionObject("SUBTYPE-OF-FLOAT?", "(DEFUN (SUBTYPE-OF-FLOAT? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfFloatP)), NULL);
      defineFunctionObject("STRING?", "(DEFUN (STRING? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&stringP)), NULL);
      defineFunctionObject("SUBTYPE-OF-STRING?", "(DEFUN (SUBTYPE-OF-STRING? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfStringP)), NULL);
      defineFunctionObject("VERBATIM-STRING?", "(DEFUN (VERBATIM-STRING? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&verbatimStringP)), NULL);
      defineFunctionObject("SUBTYPE-OF-VERBATIM-STRING?", "(DEFUN (SUBTYPE-OF-VERBATIM-STRING? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfVerbatimStringP)), NULL);
      defineFunctionObject("CHARACTER?", "(DEFUN (CHARACTER? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&characterP)), NULL);
      defineFunctionObject("SUBTYPE-OF-CHARACTER?", "(DEFUN (SUBTYPE-OF-CHARACTER? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfCharacterP)), NULL);
      defineFunctionObject("WRAPPER?", "(DEFUN (WRAPPER? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&wrapperP)), NULL);
      defineFunctionObject("SUBTYPE-OF-WRAPPER?", "(DEFUN (SUBTYPE-OF-WRAPPER? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfWrapperP)), NULL);
      defineFunctionObject("SURROGATE?", "(DEFUN (SURROGATE? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&surrogateP)), NULL);
      defineFunctionObject("SUBTYPE-OF-SURROGATE?", "(DEFUN (SUBTYPE-OF-SURROGATE? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfSurrogateP)), NULL);
      defineFunctionObject("TYPE?", "(DEFUN (TYPE? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&typeP)), NULL);
      defineFunctionObject("SUBTYPE-OF-TYPE?", "(DEFUN (SUBTYPE-OF-TYPE? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (SUBTYPE-OF-SURROGATE? TYPE)))", ((cpp_function_code)(&subtypeOfTypeP)), NULL);
      defineFunctionObject("SYMBOL?", "(DEFUN (SYMBOL? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&symbolP)), NULL);
      defineFunctionObject("SUBTYPE-OF-SYMBOL?", "(DEFUN (SUBTYPE-OF-SYMBOL? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfSymbolP)), NULL);
      defineFunctionObject("TRANSIENT-SYMBOL?", "(DEFUN (TRANSIENT-SYMBOL? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&transientSymbolP)), NULL);
      defineFunctionObject("SUBTYPE-OF-TRANSIENT-SYMBOL?", "(DEFUN (SUBTYPE-OF-TRANSIENT-SYMBOL? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfTransientSymbolP)), NULL);
      defineFunctionObject("KEYWORD?", "(DEFUN (KEYWORD? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&keywordP)), NULL);
      defineFunctionObject("SUBTYPE-OF-KEYWORD?", "(DEFUN (SUBTYPE-OF-KEYWORD? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfKeywordP)), NULL);
      defineFunctionObject("CONS?", "(DEFUN (CONS? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&consP)), NULL);
      defineFunctionObject("SUBTYPE-OF-CONS?", "(DEFUN (SUBTYPE-OF-CONS? BOOLEAN) ((TYPE TYPE)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (EQL? TYPE @CONS)))", ((cpp_function_code)(&subtypeOfConsP)), NULL);
      defineFunctionObject("STELLA-CLASS?", "(DEFUN (STELLA-CLASS? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&stellaClassP)), NULL);
      defineFunctionObject("SUBTYPE-OF-CLASS?", "(DEFUN (SUBTYPE-OF-CLASS? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfClassP)), NULL);
      defineFunctionObject("STORAGE-SLOT?", "(DEFUN (STORAGE-SLOT? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&storageSlotP)), NULL);
      defineFunctionObject("SUBTYPE-OF-STORAGE-SLOT?", "(DEFUN (SUBTYPE-OF-STORAGE-SLOT? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfStorageSlotP)), NULL);
      defineFunctionObject("METHOD-SLOT?", "(DEFUN (METHOD-SLOT? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&methodSlotP)), NULL);
      defineFunctionObject("SUBTYPE-OF-METHOD-SLOT?", "(DEFUN (SUBTYPE-OF-METHOD-SLOT? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfMethodSlotP)), NULL);
      defineFunctionObject("ANCHORED-TYPE-SPECIFIER?", "(DEFUN (ANCHORED-TYPE-SPECIFIER? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&anchoredTypeSpecifierP)), NULL);
      defineFunctionObject("SUBTYPE-OF-ANCHORED-TYPE-SPECIFIER?", "(DEFUN (SUBTYPE-OF-ANCHORED-TYPE-SPECIFIER? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfAnchoredTypeSpecifierP)), NULL);
      defineFunctionObject("PARAMETRIC-TYPE-SPECIFIER?", "(DEFUN (PARAMETRIC-TYPE-SPECIFIER? BOOLEAN) ((X OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&parametricTypeSpecifierP)), NULL);
      defineFunctionObject("SUBTYPE-OF-PARAMETRIC-TYPE-SPECIFIER?", "(DEFUN (SUBTYPE-OF-PARAMETRIC-TYPE-SPECIFIER? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfParametricTypeSpecifierP)), NULL);
      defineMethodObject("(DEFMETHOD (STANDARD-OBJECT? BOOLEAN) ((SELF OBJECT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Object::standardObjectP))), NULL);
      defineMethodObject("(DEFMETHOD (STANDARD-OBJECT? BOOLEAN) ((SELF STANDARD-OBJECT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StandardObject::standardObjectP))), NULL);
      defineFunctionObject("STARTUP-TYPE-PREDICATES", "(DEFUN STARTUP-TYPE-PREDICATES () :PUBLIC? TRUE)", ((cpp_function_code)(&startupTypePredicates)), NULL);
      { MethodSlot* function = lookupFunction(SYM_TYPE_PREDICATES_STELLA_STARTUP_TYPE_PREDICATES);

        setDynamicSlotValue(function->dynamicSlots, SYM_TYPE_PREDICATES_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupTypePredicates"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *CLASS-HIERARCHY-BOOTED?* BOOLEAN FALSE)", &oCLASS_HIERARCHY_BOOTEDpo);
    }
  }
}

Surrogate* SGT_TYPE_PREDICATES_STELLA_UNKNOWN = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_BOOLEAN_WRAPPER = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_INTEGER_WRAPPER = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_LONG_INTEGER_WRAPPER = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_FLOAT_WRAPPER = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_STRING_WRAPPER = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_VERBATIM_STRING_WRAPPER = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_CHARACTER_WRAPPER = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_WRAPPER = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_SURROGATE = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_SYMBOL = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_TRANSIENT_SYMBOL = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_KEYWORD = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_CONS = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_CLASS = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_STORAGE_SLOT = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_METHOD_SLOT = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_ANCHORED_TYPE_SPECIFIER = NULL;

Surrogate* SGT_TYPE_PREDICATES_STELLA_PARAMETRIC_TYPE_SPECIFIER = NULL;

Symbol* SYM_TYPE_PREDICATES_STELLA_STARTUP_TYPE_PREDICATES = NULL;

Symbol* SYM_TYPE_PREDICATES_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
