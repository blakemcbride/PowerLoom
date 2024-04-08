//  -*- Mode: Java -*-
//
// _StartupMethods.java

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

package edu.isi.stella;

import edu.isi.stella.javalib.*;

public class _StartupMethods {
  static void helpStartupMethods1() {
    {
      Stella.SYM_STELLA_LIKE = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("LIKE", null, 0)));
      Stella.SYM_STELLA_UNKNOWN = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("UNKNOWN", null, 0)));
      Stella.SYM_STELLA_OF = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("OF", null, 0)));
      Stella.SGT_STELLA_ARRAY = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("ARRAY", null, 1)));
      Stella.SYM_STELLA_OUT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("OUT", null, 0)));
      Stella.SYM_STELLA_INOUT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("INOUT", null, 0)));
      Stella.SYM_STELLA_ARGUMENT_LIST = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("ARGUMENT-LIST", null, 0)));
      Stella.SYM_STELLA_aREST = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("&REST", null, 0)));
      Stella.SYM_STELLA_METHOD_VARIABLE_ARGUMENTSp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD-VARIABLE-ARGUMENTS?", null, 0)));
      Stella.SYM_STELLA_aBODY = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("&BODY", null, 0)));
      Stella.SYM_STELLA_METHOD_BODY_ARGUMENTp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD-BODY-ARGUMENT?", null, 0)));
      Stella.KWD_RETURN_TYPES = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("RETURN-TYPES", null, 2)));
      Stella.KWD_NATIVEp = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("NATIVE?", null, 2)));
      Stella.SYM_STELLA_METHOD_NATIVEp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD-NATIVE?", null, 0)));
      Stella.KWD_CONSTRUCTORp = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("CONSTRUCTOR?", null, 2)));
      Stella.SYM_STELLA_METHOD_CONSTRUCTORp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD-CONSTRUCTOR?", null, 0)));
      Stella.KWD_GLOBALLY_INLINEp = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("GLOBALLY-INLINE?", null, 2)));
      Stella.SYM_STELLA_METHOD_GLOBALLY_INLINEp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD-GLOBALLY-INLINE?", null, 0)));
      Stella.KWD_INLINE = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("INLINE", null, 2)));
      Stella.KWD_RETURNS = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("RETURNS", null, 2)));
      Stella.KWD_STORAGE_SLOT = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("STORAGE-SLOT", null, 2)));
      Stella.KWD_INHERITS_THROUGH = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("INHERITS-THROUGH", null, 2)));
      Stella.SYM_STELLA_METHOD_INHERITS_THROUGH = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD-INHERITS-THROUGH", null, 0)));
      Stella.KWD_COMMANDp = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("COMMAND?", null, 2)));
      Stella.SYM_STELLA_METHOD_COMMANDp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD-COMMAND?", null, 0)));
      Stella.KWD_LISP_MACROp = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("LISP-MACRO?", null, 2)));
      Stella.SYM_STELLA_METHOD_LISP_MACROp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD-LISP-MACRO?", null, 0)));
      Stella.KWD_EVALUATE_ARGUMENTSp = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("EVALUATE-ARGUMENTS?", null, 2)));
      Stella.KWD_C_CALLABLEp = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("C-CALLABLE?", null, 2)));
      Stella.SYM_STELLA_METHOD_C_CALLABLEp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD-C-CALLABLE?", null, 0)));
      Stella.SYM_STELLA_DEFINE_FUNCTION_OBJECT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("DEFINE-FUNCTION-OBJECT", null, 0)));
      Stella.SYM_STELLA_THE_CODE = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("THE-CODE", null, 0)));
      Stella.SYM_STELLA_DEFINE_INLINE_METHOD_CODE = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("DEFINE-INLINE-METHOD-CODE", null, 0)));
      Stella.SYM_STELLA_QUOTE = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("QUOTE", null, 0)));
      Stella.KWD_METHOD = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD", null, 2)));
      Stella.SYM_STELLA_DEFINE_METHOD_OBJECT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("DEFINE-METHOD-OBJECT", null, 0)));
      Stella.SYM_STELLA_SUPER_CLASSES = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("SUPER-CLASSES", null, 0)));
      Stella.SYM_STELLA_EQUIVALENT_SLOT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("EQUIVALENT-SLOT", null, 0)));
      Stella.SYM_STELLA_SLOT_VALUE = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("SLOT-VALUE", null, 0)));
      Stella.SYM_STELLA_LOOP = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("LOOP", null, 0)));
      Stella.SYM_STELLA_IF = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("IF", null, 0)));
      Stella.SYM_STELLA_FIRST = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("FIRST", null, 0)));
      Stella.SYM_STELLA_VARIABLE_ARITY_TABLEp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("VARIABLE-ARITY-TABLE?", null, 0)));
      Stella.SYM_STELLA_EVALUATOR_WRAPPER_CODE = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("EVALUATOR-WRAPPER-CODE", null, 0)));
      Stella.SYM_STELLA_VARIABLE_TYPE_SPECIFIER = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("VARIABLE-TYPE-SPECIFIER", null, 0)));
      Stella.SYM_STELLA_DEFSPECIAL = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("DEFSPECIAL", null, 0)));
      Stella.SYM_STELLA_DEFCONSTANT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("DEFCONSTANT", null, 0)));
      Stella.KWD_UNBOUND_SPECIAL_VARIABLE = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("UNBOUND-SPECIAL-VARIABLE", null, 2)));
      Stella.SGT_STELLA_LITERAL = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("LITERAL", null, 1)));
      Stella.SYM_STELLA_STARTUP_METHODS = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-METHODS", null, 0)));
    }
  }

  static void helpStartupMethods2() {
    {
      Stella.defineFunctionObject("APPLY", "(DEFUN (APPLY OBJECT) ((CODE FUNCTION-CODE) (ARGUMENTS (CONS OF OBJECT))) :DOCUMENTATION \"Apply `code' to `arguments', returning a value of type OBJECT.\nCurrently limited to at most 10 `arguments'.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Stella", "apply", new java.lang.Class [] {Native.find_java_class("java.lang.reflect.Method"), Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("APPLY-METHOD", "(DEFUN (APPLY-METHOD OBJECT) ((CODE METHOD-CODE) (ARGUMENTS (CONS OF OBJECT))) :DOCUMENTATION \"Apply `code' to `arguments', returning a value of type\nOBJECT.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Stella", "applyMethod", new java.lang.Class [] {Native.find_java_class("java.lang.reflect.Method"), Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("APPLY-INTEGER-METHOD", "(DEFUN (APPLY-INTEGER-METHOD INTEGER) ((CODE METHOD-CODE) (ARGUMENTS (CONS OF OBJECT))) :DOCUMENTATION \"Apply `code' to `arguments', returning a value of type\nINTEGER.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Stella", "applyIntegerMethod", new java.lang.Class [] {Native.find_java_class("java.lang.reflect.Method"), Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("APPLY-LONG-INTEGER-METHOD", "(DEFUN (APPLY-LONG-INTEGER-METHOD LONG-INTEGER) ((CODE METHOD-CODE) (ARGUMENTS (CONS OF OBJECT))) :DOCUMENTATION \"Apply `code' to `arguments', returning a value of type\nLONG-INTEGER.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Stella", "applyLongIntegerMethod", new java.lang.Class [] {Native.find_java_class("java.lang.reflect.Method"), Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("APPLY-STRING-METHOD", "(DEFUN (APPLY-STRING-METHOD STRING) ((CODE METHOD-CODE) (ARGUMENTS (CONS OF OBJECT))) :DOCUMENTATION \"Apply `code' to `arguments', returning a value of type\nSTRING.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Stella", "applyStringMethod", new java.lang.Class [] {Native.find_java_class("java.lang.reflect.Method"), Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("APPLY-BOOLEAN-METHOD", "(DEFUN (APPLY-BOOLEAN-METHOD BOOLEAN) ((CODE METHOD-CODE) (ARGUMENTS (CONS OF OBJECT))) :DOCUMENTATION \"Apply `code' to `arguments', returning a value of type\nBOOLEAN.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Stella", "applyBooleanMethod", new java.lang.Class [] {Native.find_java_class("java.lang.reflect.Method"), Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("APPLY-FLOAT-METHOD", "(DEFUN (APPLY-FLOAT-METHOD FLOAT) ((CODE METHOD-CODE) (ARGUMENTS (CONS OF OBJECT))) :DOCUMENTATION \"Apply `code' to `arguments', returning a value of type\nFLOAT.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Stella", "applyFloatMethod", new java.lang.Class [] {Native.find_java_class("java.lang.reflect.Method"), Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("DEFINED-TYPE?", "(DEFUN (DEFINED-TYPE? BOOLEAN) ((TYPE TYPE)) :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Surrogate", "definedTypeP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Surrogate")}), null);
      Stella.defineFunctionObject("REAL-TYPE-SPECIFIER", "(DEFUN (REAL-TYPE-SPECIFIER TYPE-SPEC) ((TYPE TYPE)))", Native.find_java_method("edu.isi.stella.Surrogate", "realTypeSpecifier", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Surrogate")}), null);
      Stella.defineFunctionObject("CANONICAL-TYPE", "(DEFUN (CANONICAL-TYPE TYPE) ((TYPE TYPE)))", Native.find_java_method("edu.isi.stella.Surrogate", "canonicalType", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Surrogate")}), null);
      Stella.defineMethodObject("(DEFMETHOD (YIELD-TYPE-SPECIFIER TYPE-SPEC) ((TYPESPECTREE TYPE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.Surrogate", "yieldTypeSpecifier", new java.lang.Class [] {})), null);
      Stella.defineMethodObject("(DEFMETHOD (YIELD-TYPE-SPECIFIER TYPE-SPEC) ((TYPESPECTREE SYMBOL)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.Symbol", "yieldTypeSpecifier", new java.lang.Class [] {})), null);
      Stella.defineMethodObject("(DEFMETHOD (YIELD-TYPE-SPECIFIER TYPE-SPEC) ((TYPESPECTREE PARAMETRIC-TYPE-SPECIFIER)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.ParametricTypeSpecifier", "yieldTypeSpecifier", new java.lang.Class [] {})), null);
      Stella.defineMethodObject("(DEFMETHOD (YIELD-TYPE-SPECIFIER TYPE-SPEC) ((TYPESPECTREE ANCHORED-TYPE-SPECIFIER)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.AnchoredTypeSpecifier", "yieldTypeSpecifier", new java.lang.Class [] {})), null);
      Stella.defineMethodObject("(DEFMETHOD (YIELD-TYPE-SPECIFIER TYPE-SPEC) ((TYPESPECTREE OBJECT)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.Stella_Object", "yieldTypeSpecifier", new java.lang.Class [] {})), null);
      Stella.defineMethodObject("(DEFMETHOD (YIELD-TYPE-SPECIFIER TYPE-SPEC) ((TYPESPECTREE CONS)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.Cons", "yieldTypeSpecifier", new java.lang.Class [] {})), null);
      Stella.defineFunctionObject("YIELD-PARAMETRIC-TYPE-SPECIFIER", "(DEFUN (YIELD-PARAMETRIC-TYPE-SPECIFIER PARAMETRIC-TYPE-SPECIFIER) ((TYPESPECTREE CONS)))", Native.find_java_method("edu.isi.stella.Cons", "yieldParametricTypeSpecifier", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("PARSE-ARRAY-DIMENSIONS-SPEC", "(DEFUN (PARSE-ARRAY-DIMENSIONS-SPEC (LIST OF INTEGER-WRAPPER)) ((DIMENSIONSSPEC OBJECT)))", Native.find_java_method("edu.isi.stella.Stella_Object", "parseArrayDimensionsSpec", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
      Stella.defineFunctionObject("YIELD-ARRAY-DIMENSIONS-TREE", "(DEFUN (YIELD-ARRAY-DIMENSIONS-TREE CONS) ((ARRAYTYPE PARAMETRIC-TYPE-SPECIFIER)))", Native.find_java_method("edu.isi.stella.ParametricTypeSpecifier", "yieldArrayDimensionsTree", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.ParametricTypeSpecifier")}), null);
      Stella.defineFunctionObject("ARRAY-TYPE-SPECIFIER?", "(DEFUN (ARRAY-TYPE-SPECIFIER? BOOLEAN) ((TYPESPEC TYPE-SPEC)))", Native.find_java_method("edu.isi.stella.StandardObject", "arrayTypeSpecifierP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject")}), null);
      Stella.defineFunctionObject("ARRAY-TYPE-RANK", "(DEFUN (ARRAY-TYPE-RANK INTEGER) ((ARRAYTYPE PARAMETRIC-TYPE-SPECIFIER)))", Native.find_java_method("edu.isi.stella.ParametricTypeSpecifier", "arrayTypeRank", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.ParametricTypeSpecifier")}), null);
      Stella.defineFunctionObject("ARRAY-TYPE-DIMENSIONS", "(DEFUN (ARRAY-TYPE-DIMENSIONS (LIST OF INTEGER-WRAPPER)) ((ARRAYTYPE PARAMETRIC-TYPE-SPECIFIER)))", Native.find_java_method("edu.isi.stella.ParametricTypeSpecifier", "arrayTypeDimensions", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.ParametricTypeSpecifier")}), null);
      Stella.defineFunctionObject("INDEFINITE-ARRAY-TYPE?", "(DEFUN (INDEFINITE-ARRAY-TYPE? BOOLEAN) ((ARRAYTYPE PARAMETRIC-TYPE-SPECIFIER)))", Native.find_java_method("edu.isi.stella.ParametricTypeSpecifier", "indefiniteArrayTypeP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.ParametricTypeSpecifier")}), null);
      Stella.defineFunctionObject("YIELD-ANCHORED-TYPE-SPECIFIER", "(DEFUN (YIELD-ANCHORED-TYPE-SPECIFIER ANCHORED-TYPE-SPECIFIER) ((TYPESPECTREE CONS)))", Native.find_java_method("edu.isi.stella.Cons", "yieldAnchoredTypeSpecifier", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("INCORPORATE-INPUT-PARAMETERS", "(DEFUN INCORPORATE-INPUT-PARAMETERS ((METHOD METHOD-SLOT) (PARAMETERS CONS)))", Native.find_java_method("edu.isi.stella.MethodSlot", "incorporateInputParameters", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.MethodSlot"), Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("INCORPORATE-FIRST-INPUT-PARAMETER", "(DEFUN INCORPORATE-FIRST-INPUT-PARAMETER ((METHOD METHOD-SLOT)))", Native.find_java_method("edu.isi.stella.MethodSlot", "incorporateFirstInputParameter", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.MethodSlot")}), null);
      Stella.defineFunctionObject("DEFINE-STELLA-METHOD-SLOT", "(DEFUN (DEFINE-STELLA-METHOD-SLOT METHOD-SLOT) ((INPUTNAME SYMBOL) (RETURNTYPES CONS) (FUNCTION? BOOLEAN) (INPUTPARAMETERS CONS) (OPTIONS KEYWORD-KEY-VALUE-LIST)) :DOCUMENTATION \"Define a new Stella method object (a slot), and attach it\nto the class identified by the first parameter in 'inputParameters'.\")", Native.find_java_method("edu.isi.stella.Symbol", "defineStellaMethodSlot", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Cons"), java.lang.Boolean.TYPE, Native.find_java_class("edu.isi.stella.Cons"), Native.find_java_class("edu.isi.stella.KeywordKeyValueList")}), null);
      Stella.defineFunctionObject("ATTACH-METHOD-SLOT-TO-OWNER", "(DEFUN (ATTACH-METHOD-SLOT-TO-OWNER METHOD-SLOT) ((NEWMETHOD METHOD-SLOT)))", Native.find_java_method("edu.isi.stella.MethodSlot", "attachMethodSlotToOwner", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.MethodSlot")}), null);
      Stella.defineFunctionObject("YIELD-STRING-CONSTANT-TREE", "(DEFUN (YIELD-STRING-CONSTANT-TREE OBJECT) ((STRING STRING)))", Native.find_java_method("edu.isi.stella.Stella", "yieldStringConstantTree", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
      Stella.defineFunctionObject("DEFINE-FUNCTION-OBJECT-EAGERLY?", "(DEFUN (DEFINE-FUNCTION-OBJECT-EAGERLY? BOOLEAN) ((FUNCTION METHOD-SLOT)))", Native.find_java_method("edu.isi.stella.MethodSlot", "defineFunctionObjectEagerlyP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.MethodSlot")}), null);
      Stella.defineFunctionObject("YIELD-DEFINE-STELLA-METHOD-OBJECT", "(DEFUN (YIELD-DEFINE-STELLA-METHOD-OBJECT CONS) ((METHOD METHOD-SLOT) (CODEMETHOD METHOD-SLOT) (WRAPPERMETHOD METHOD-SLOT)))", Native.find_java_method("edu.isi.stella.MethodSlot", "yieldDefineStellaMethodObject", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.MethodSlot"), Native.find_java_class("edu.isi.stella.MethodSlot"), Native.find_java_class("edu.isi.stella.MethodSlot")}), null);
      Stella.defineFunctionObject("YIELD-CLASS-PARAMETER-TYPES", "(DEFUN (YIELD-CLASS-PARAMETER-TYPES (CONS OF TYPE)) ((CLASS CLASS)))", Native.find_java_method("edu.isi.stella.Stella_Class", "yieldClassParameterTypes", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Class")}), null);
      Stella.defineFunctionObject("OPTIMISTIC-SUBTYPE-OF?", "(DEFUN (OPTIMISTIC-SUBTYPE-OF? BOOLEAN) ((SUBTYPE TYPE) (SUPERTYPE TYPE)))", Native.find_java_method("edu.isi.stella.Surrogate", "optimisticSubtypeOfP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Surrogate"), Native.find_java_class("edu.isi.stella.Surrogate")}), null);
      Stella.defineFunctionObject("WARN-OF-PARAMETER-MISMATCH", "(DEFUN WARN-OF-PARAMETER-MISMATCH ((SELF PARAMETRIC-TYPE-SPECIFIER) (MESSAGE STRING)))", Native.find_java_method("edu.isi.stella.ParametricTypeSpecifier", "warnOfParameterMismatch", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.ParametricTypeSpecifier"), Native.find_java_class("java.lang.String")}), null);
      Stella.defineFunctionObject("VALIDATE-TYPE-SPECIFIER", "(DEFUN (VALIDATE-TYPE-SPECIFIER TYPE) ((SELF TYPE-SPEC) (ANCHORCLASS CLASS) (SKIPANCHOREDTYPE? BOOLEAN)))", Native.find_java_method("edu.isi.stella.StandardObject", "validateTypeSpecifier", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject"), Native.find_java_class("edu.isi.stella.Stella_Class"), java.lang.Boolean.TYPE}), null);
      Stella.defineFunctionObject("SYNTHESIZE-METHOD-BODY", "(DEFUN (SYNTHESIZE-METHOD-BODY CONS) ((METHOD METHOD-SLOT)))", Native.find_java_method("edu.isi.stella.MethodSlot", "synthesizeMethodBody", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.MethodSlot")}), null);
      Stella.defineMethodObject("(DEFMETHOD FINALIZE-SLOT-TYPE-COMPUTATIONS ((SELF METHOD-SLOT)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.MethodSlot", "finalizeSlotTypeComputations", new java.lang.Class [] {})), null);
      Stella.defineMethodObject("(DEFMETHOD HELP-FINALIZE-LOCAL-SLOT ((SELF METHOD-SLOT)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.MethodSlot", "helpFinalizeLocalSlot", new java.lang.Class [] {})), null);
      Stella.defineMethodObject("(DEFMETHOD UNFINALIZE-LOCAL-SLOT ((SELF METHOD-SLOT)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.MethodSlot", "unfinalizeLocalSlot", new java.lang.Class [] {})), null);
      Stella.defineFunctionObject("UNDEFINE-EXTERNAL-SLOTS", "(DEFUN UNDEFINE-EXTERNAL-SLOTS ((NAME SYMBOL)))", Native.find_java_method("edu.isi.stella.Symbol", "undefineExternalSlots", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Symbol")}), null);
      Stella.defineFunctionObject("DESTROY-EXTERNAL-SLOT", "(DEFUN DESTROY-EXTERNAL-SLOT ((SELF SLOT)))", Native.find_java_method("edu.isi.stella.Slot", "destroyExternalSlot", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Slot")}), null);
      Stella.defineFunctionObject("DESTROY-METHOD", "(DEFUN DESTROY-METHOD ((SELF METHOD-SLOT)))", Native.find_java_method("edu.isi.stella.MethodSlot", "destroyMethod", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.MethodSlot")}), null);
      Stella.defineMethodObject("(DEFMETHOD (METHOD-ARGUMENT-COUNT INTEGER) ((SELF SLOT)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.Slot", "methodArgumentCount", new java.lang.Class [] {})), null);
      Stella.defineMethodObject("(DEFMETHOD (METHOD-ARGUMENT-COUNT INTEGER) ((SELF STORAGE-SLOT)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.StorageSlot", "methodArgumentCount", new java.lang.Class [] {})), null);
      Stella.defineMethodObject("(DEFMETHOD (METHOD-ARGUMENT-COUNT INTEGER) ((SELF METHOD-SLOT)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.MethodSlot", "methodArgumentCount", new java.lang.Class [] {})), null);
      Stella.defineMethodObject("(DEFMETHOD (METHOD-ARGUMENT-COUNT INTEGER) ((SELF TABLE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.Table", "methodArgumentCount", new java.lang.Class [] {})), null);
      Stella.defineMethodObject("(DEFMETHOD (METHOD-VARIABLE-ARGUMENTS? BOOLEAN) ((SELF STORAGE-SLOT)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.StorageSlot", "methodVariableArgumentsP", new java.lang.Class [] {})), null);
      Stella.defineMethodObject("(DEFMETHOD (METHOD-BODY-ARGUMENT? BOOLEAN) ((SELF STORAGE-SLOT)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.StorageSlot", "methodBodyArgumentP", new java.lang.Class [] {})), null);
      Stella.defineMethodObject("(DEFMETHOD (ARITY INTEGER) ((SELF STORAGE-SLOT)) :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.StorageSlot", "arity", new java.lang.Class [] {})), null);
      Stella.defineMethodObject("(DEFMETHOD (ARITY INTEGER) ((SELF METHOD-SLOT)) :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.MethodSlot", "arity", new java.lang.Class [] {})), null);
      Stella.defineMethodObject("(DEFMETHOD (ARITY INTEGER) ((SELF TABLE)) :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.Table", "arity", new java.lang.Class [] {})), null);
      Stella.defineFunctionObject("TYPE-SPEC-TO-BASE-TYPE", "(DEFUN (TYPE-SPEC-TO-BASE-TYPE TYPE) ((SELF TYPE-SPEC)) :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.StandardObject", "typeSpecToBaseType", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject")}), null);
      Stella.defineFunctionObject("BASE-TYPE-TO-TYPE-SPEC", "(DEFUN (BASE-TYPE-TO-TYPE-SPEC TYPE-SPEC) ((SELF TYPE-SPEC)))", Native.find_java_method("edu.isi.stella.StandardObject", "baseTypeToTypeSpec", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject")}), null);
      Stella.defineFunctionObject("TYPE-SPEC-TO-CLASS", "(DEFUN (TYPE-SPEC-TO-CLASS CLASS) ((SELF TYPE-SPEC)) :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.StandardObject", "typeSpecToClass", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject")}), null);
      Stella.defineFunctionObject("COMPATIBLE-PARAMETER-TYPES?", "(DEFUN (COMPATIBLE-PARAMETER-TYPES? BOOLEAN) ((SUBTYPE TYPE-SPEC) (SUPERTYPE TYPE-SPEC)) :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.StandardObject", "compatibleParameterTypesP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject"), Native.find_java_class("edu.isi.stella.StandardObject")}), null);
      Stella.defineFunctionObject("SUB-TYPE-SPEC-OF?", "(DEFUN (SUB-TYPE-SPEC-OF? BOOLEAN) ((SUBTYPE TYPE-SPEC) (SUPERTYPE TYPE-SPEC)))", Native.find_java_method("edu.isi.stella.StandardObject", "subTypeSpecOfP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject"), Native.find_java_class("edu.isi.stella.StandardObject")}), null);
      Stella.defineFunctionObject("VOID?", "(DEFUN (VOID? BOOLEAN) ((TYPE TYPE-SPEC)) :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.StandardObject", "voidP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject")}), null);
      Stella.defineFunctionObject("EXTRACT-PARAMETER-TYPE", "(DEFUN (EXTRACT-PARAMETER-TYPE TYPE-SPEC BOOLEAN) ((SELF TYPE-SPEC) (PARAMETER SYMBOL)) :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.StandardObject", "extractParameterType", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("[Ljava.lang.Object;")}), null);
      Stella.defineFunctionObject("COMPUTE-ANCHORED-TYPE-SPEC", "(DEFUN (COMPUTE-ANCHORED-TYPE-SPEC TYPE-SPEC) ((OWNERTYPE TYPE-SPEC) (RELTYPE ANCHORED-TYPE-SPECIFIER)))", Native.find_java_method("edu.isi.stella.StandardObject", "computeAnchoredTypeSpec", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject"), Native.find_java_class("edu.isi.stella.AnchoredTypeSpecifier")}), null);
      Stella.defineFunctionObject("COMPUTE-RELATIVE-TYPE-SPEC", "(DEFUN (COMPUTE-RELATIVE-TYPE-SPEC TYPE-SPEC) ((RELATIVETYPE TYPE-SPEC) (OWNERTYPE TYPE-SPEC)))", Native.find_java_method("edu.isi.stella.StandardObject", "computeRelativeTypeSpec", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject"), Native.find_java_class("edu.isi.stella.StandardObject")}), null);
    }
  }

  public static void startupMethods() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.$STELLA_MODULE$);
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          _StartupMethods.helpStartupMethods1();
        }
        if (Stella.currentStartupTimePhaseP(4)) {
          Stella.$FUNCTION_LOOKUP_TABLE$ = HashTable.newHashTable();
          Stella.$GLOBAL_VARIABLE_LOOKUP_TABLE$ = HashTable.newHashTable();
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          _StartupMethods.helpStartupMethods2();
          Stella.defineMethodObject("(DEFMETHOD (COMPUTE-RETURN-TYPE-SPEC TYPE-SPEC) ((SELF SLOT) (FIRSTARGTYPE TYPE-SPEC)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.Slot", "computeReturnTypeSpec", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject")})), null);
          Stella.defineMethodObject("(DEFMETHOD (COMPUTE-RETURN-TYPE-SPEC TYPE-SPEC) ((SELF METHOD-SLOT) (FIRSTARGTYPE TYPE-SPEC)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.MethodSlot", "computeReturnTypeSpec", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject")})), null);
          Stella.defineMethodObject("(DEFMETHOD (COMPUTE-RETURN-TYPE-SPEC TYPE-SPEC) ((SELF STORAGE-SLOT) (FIRSTARGTYPE TYPE-SPEC)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.StorageSlot", "computeReturnTypeSpec", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject")})), null);
          Stella.defineFunctionObject("YIELD-TYPE-SPEC-TREE", "(DEFUN (YIELD-TYPE-SPEC-TREE OBJECT) ((SELF TYPE-SPEC)))", Native.find_java_method("edu.isi.stella.StandardObject", "yieldTypeSpecTree", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StandardObject")}), null);
          Stella.defineFunctionObject("ATTACH-FUNCTION", "(DEFUN (ATTACH-FUNCTION METHOD-SLOT) ((NEWFUNCTION METHOD-SLOT)))", Native.find_java_method("edu.isi.stella.MethodSlot", "attachFunction", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.MethodSlot")}), null);
          Stella.defineFunctionObject("LOOKUP-FUNCTION", "(DEFUN (LOOKUP-FUNCTION FUNCTION) ((FUNCTIONSYMBOL SYMBOL)) :DOCUMENTATION \"Return the function defined for 'functionSymbol', if it exists.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Symbol", "lookupFunction", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Symbol")}), null);
          Stella.defineFunctionObject("LOOKUP-FUNCTION-BY-NAME", "(DEFUN (LOOKUP-FUNCTION-BY-NAME FUNCTION) ((NAME STRING)) :DOCUMENTATION \"Return a function with name 'name' visible from the current module.\nScan all visible symbols looking for one that has a function defined for it.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Stella", "lookupFunctionByName", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("LOOKUP-FUNCTION-BY-QUALIFIED-NAME", "(DEFUN (LOOKUP-FUNCTION-BY-QUALIFIED-NAME METHOD-SLOT) ((QUALIFIEDNAME STRING)) :DOCUMENTATION \"Variant of `lookup-function-by-name' that can specify a starting\nmodule through a `qualifiedName'.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Stella", "lookupFunctionByQualifiedName", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("LOOKUP-FUNCTION-OR-STELLA-FUNCTION", "(DEFUN (LOOKUP-FUNCTION-OR-STELLA-FUNCTION FUNCTION) ((FUNCTIONSYMBOL SYMBOL)) :GLOBALLY-INLINE? TRUE (RETURN (LOOKUP-FUNCTION FUNCTIONSYMBOL)))", Native.find_java_method("edu.isi.stella.Symbol", "lookupFunctionOrStellaFunction", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Symbol")}), null);
          Stella.defineFunctionObject("LOOKUP-FUNCTION-HOME-MODULE", "(DEFUN (LOOKUP-FUNCTION-HOME-MODULE MODULE) ((FUNCTIONSYMBOL SYMBOL)))", Native.find_java_method("edu.isi.stella.Symbol", "lookupFunctionHomeModule", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Symbol")}), null);
          Stella.defineFunctionObject("UNDEFINE-FUNCTION", "(DEFUN UNDEFINE-FUNCTION ((NAME SYMBOL)))", Native.find_java_method("edu.isi.stella.Symbol", "undefineFunction", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Symbol")}), null);
          Stella.defineFunctionObject("DESTROY-FUNCTION", "(DEFUN DESTROY-FUNCTION ((FUNCTION METHOD-SLOT)))", Native.find_java_method("edu.isi.stella.MethodSlot", "destroyFunction", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.MethodSlot")}), null);
          Stella.defineFunctionObject("UNDEFINE-CONFLICTING-DEFINITIONS?", "(DEFUN (UNDEFINE-CONFLICTING-DEFINITIONS? BOOLEAN) ((NEWSLOT METHOD-SLOT)))", Native.find_java_method("edu.isi.stella.MethodSlot", "undefineConflictingDefinitionsP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.MethodSlot")}), null);
          Stella.defineFunctionObject("DEFINE-FUNCTION-OBJECT", "(DEFUN DEFINE-FUNCTION-OBJECT ((NAME STRING) (DEFINITION STRING) (CODE FUNCTION-CODE) (WRAPPERCODE FUNCTION-CODE)))", Native.find_java_method("edu.isi.stella.Stella", "defineFunctionObject", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.reflect.Method"), Native.find_java_class("java.lang.reflect.Method")}), null);
          Stella.defineFunctionObject("INTERN-GLOBAL-VARIABLE", "(DEFUN (INTERN-GLOBAL-VARIABLE GLOBAL-VARIABLE) ((GLOBAL GLOBAL-VARIABLE)))", Native.find_java_method("edu.isi.stella.GlobalVariable", "internGlobalVariable", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.GlobalVariable")}), null);
          Stella.defineMethodObject("(DEFMETHOD (LOOKUP-GLOBAL-VARIABLE GLOBAL-VARIABLE) ((SELF GENERALIZED-SYMBOL)) :PUBLIC? TRUE :DOCUMENTATION \"Return a global variable with name 'self'.\")", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.GeneralizedSymbol", "lookupGlobalVariable", new java.lang.Class [] {})), null);
          Stella.defineMethodObject("(DEFMETHOD (LOOKUP-GLOBAL-VARIABLE GLOBAL-VARIABLE) ((SELF SURROGATE)) :PUBLIC? TRUE :DOCUMENTATION \"Return a global variable with name 'self'.\")", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.Surrogate", "lookupGlobalVariable", new java.lang.Class [] {})), null);
          Stella.defineMethodObject("(DEFMETHOD (LOOKUP-GLOBAL-VARIABLE GLOBAL-VARIABLE) ((SELF STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Return a global variable with name 'self'.\")", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.stella.Stella", "string_lookupGlobalVariable", new java.lang.Class [] {Native.find_java_class("java.lang.String")})), null);
          Stella.defineFunctionObject("LOOKUP-GLOBAL-VARIABLE-BY-NAME", "(DEFUN (LOOKUP-GLOBAL-VARIABLE-BY-NAME GLOBAL-VARIABLE) ((NAME STRING)) :DOCUMENTATION \"Return a global variable with `name' visible from the current module.\nScan all visible symbols looking for one that has a global variable defined for it.\nNOTE: this is more robust than STRING.lookup-global-variable which will fail if there\nis a local symbol with `name' which shadows one higher up that is the name of a global.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Stella", "lookupGlobalVariableByName", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("LOOKUP-GLOBAL-VARIABLE-BY-QUALIFIED-NAME", "(DEFUN (LOOKUP-GLOBAL-VARIABLE-BY-QUALIFIED-NAME GLOBAL-VARIABLE) ((QUALIFIEDNAME STRING)) :DOCUMENTATION \"Variant of `lookup-global-variable-by-name' that can specify a starting\nmodule through a `qualifiedName'.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Stella", "lookupGlobalVariableByQualifiedName", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("GLOBAL-VARIABLE-TYPE-SPEC", "(DEFUN (GLOBAL-VARIABLE-TYPE-SPEC TYPE-SPEC) ((GLOBAL GLOBAL-VARIABLE)) :DOCUMENTATION \"Return the type spec for the global variable `global'.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.GlobalVariable", "globalVariableTypeSpec", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.GlobalVariable")}), null);
          Stella.defineFunctionObject("LOOKUP-GLOBAL-VARIABLE-TYPE", "(DEFUN (LOOKUP-GLOBAL-VARIABLE-TYPE TYPE-SPEC) ((NAME SYMBOL)) :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Symbol", "lookupGlobalVariableType", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Symbol")}), null);
          Stella.defineFunctionObject("DEFINE-STELLA-GLOBAL-VARIABLE-FROM-PARSE-TREE", "(DEFUN (DEFINE-STELLA-GLOBAL-VARIABLE-FROM-PARSE-TREE GLOBAL-VARIABLE OBJECT) ((TREE CONS) (STRINGIFIEDSOURCE STRING)))", Native.find_java_method("edu.isi.stella.Cons", "defineStellaGlobalVariableFromParseTree", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons"), Native.find_java_class("java.lang.String"), Native.find_java_class("[Ljava.lang.Object;")}), null);
          Stella.defineFunctionObject("DEFINE-STELLA-GLOBAL-VARIABLE-FROM-STRINGIFIED-SOURCE", "(DEFUN DEFINE-STELLA-GLOBAL-VARIABLE-FROM-STRINGIFIED-SOURCE ((STRINGIFIEDSOURCE STRING)) :DOCUMENTATION \"Define a stella global variable using a parse tree derived from 'stringifiedSource'.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Stella", "defineStellaGlobalVariableFromStringifiedSource", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("DEFINE-GLOBAL-VARIABLE-OBJECT", "(DEFUN DEFINE-GLOBAL-VARIABLE-OBJECT ((DEFINITION STRING) (NATIVEOBJECT NATIVE-OBJECT-POINTER)) :DOCUMENTATION \"Define a STELLA global variable object based on `definition', and initialize\nits variable-native-object slot to `nativeObject' (which is primarily needed for C++).\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Stella", "defineGlobalVariableObject", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.Object")}), null);
          Stella.defineFunctionObject("RECORD-VARIABLE-HOME-MODULE", "(DEFUN (RECORD-VARIABLE-HOME-MODULE MODULE) ((SELF GLOBAL-VARIABLE)))", Native.find_java_method("edu.isi.stella.GlobalVariable", "recordVariableHomeModule", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.GlobalVariable")}), null);
          Stella.defineFunctionObject("DESTROY-GLOBAL-VARIABLE", "(DEFUN DESTROY-GLOBAL-VARIABLE ((VARIABLE GLOBAL-VARIABLE)))", Native.find_java_method("edu.isi.stella.GlobalVariable", "destroyGlobalVariable", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.GlobalVariable")}), null);
          Stella.defineFunctionObject("GET-GLOBAL-VARIABLE-NATIVE-OBJECT", "(DEFUN (GET-GLOBAL-VARIABLE-NATIVE-OBJECT NATIVE-OBJECT-POINTER) ((VARIABLE GLOBAL-VARIABLE)) :DOCUMENTATION \"Return the native object of `variable' which can be used to access its runtime value.\nIn Lisp this is the Lisp symbol which holds the variable value, in C++ this is the address of the variable,\nand in Java this is the declared Field object.  For C++ native object addresses are initialized at startup\ntime, for Lisp and Java native objects will be accessed upon first call and then cached in the slot.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.GlobalVariable", "getGlobalVariableNativeObject", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.GlobalVariable")}), null);
          Stella.defineFunctionObject("READ-NATIVE-VARIABLE-VALUE", "(DEFUN (READ-NATIVE-VARIABLE-VALUE OBJECT) ((VAR NATIVE-OBJECT-POINTER) (TYPE TYPE)) :DOCUMENTATION \"Interpreted variable reader which reads a native code variable represented by\n`var' of type `type' and returns its value which will be wrapped if necessary.  If `var' is a\nspecial variable, this will access the current dynamic value at the top of the special stack.\nThis relies upon `type' being completely accurate and bad things will happen if it is not.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Stella", "readNativeVariableValue", new java.lang.Class [] {Native.find_java_class("java.lang.Object"), Native.find_java_class("edu.isi.stella.Surrogate")}), null);
          Stella.defineFunctionObject("WRITE-NATIVE-VARIABLE-VALUE", "(DEFUN WRITE-NATIVE-VARIABLE-VALUE ((VAR NATIVE-OBJECT-POINTER) (TYPE TYPE) (VALUE OBJECT)) :DOCUMENTATION \"Interpreted variable writer which sets a native code variable represented by\n`var' of type `type' to `value' which will be unwrapped if necessary.  If `var' is a special\nvariable, this will change the current dynamic value at the top of the special stack.  This\nrelies upon `type' being completely accurate and bad things will happen if it is not.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Stella", "writeNativeVariableValue", new java.lang.Class [] {Native.find_java_class("java.lang.Object"), Native.find_java_class("edu.isi.stella.Surrogate"), Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineFunctionObject("READ-GLOBAL-VARIABLE-VALUE", "(DEFUN (READ-GLOBAL-VARIABLE-VALUE OBJECT) ((VARIABLE GLOBAL-VARIABLE)) :DOCUMENTATION \"Interpreted global `variable' reader which reads and returns its native value\nwhich will be wrapped if necessary.  This will access the value at the top of the special stack.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.GlobalVariable", "readGlobalVariableValue", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.GlobalVariable")}), null);
          Stella.defineFunctionObject("WRITE-GLOBAL-VARIABLE-VALUE", "(DEFUN WRITE-GLOBAL-VARIABLE-VALUE ((VARIABLE GLOBAL-VARIABLE) (VALUE OBJECT)) :DOCUMENTATION \"Interpreted global `variable' writer which sets its native value to `value'\nunwrappig it if necessary.  This will change the current value at the top of the special stack.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.GlobalVariable", "writeGlobalVariableValue", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.GlobalVariable"), Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineFunctionObject("DEFINE-STELLA-TYPE-FROM-PARSE-TREE", "(DEFUN (DEFINE-STELLA-TYPE-FROM-PARSE-TREE TYPE) ((TREE CONS)) :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Cons", "defineStellaTypeFromParseTree", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
          Stella.defineFunctionObject("DEFINE-STELLA-TYPE-FROM-STRINGIFIED-SOURCE", "(DEFUN DEFINE-STELLA-TYPE-FROM-STRINGIFIED-SOURCE ((STRINGIFIEDSOURCE STRING)) :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella.Stella", "defineStellaTypeFromStringifiedSource", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("STARTUP-METHODS", "(DEFUN STARTUP-METHODS () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.stella._StartupMethods", "startupMethods", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(Stella.SYM_STELLA_STARTUP_METHODS);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, Stella.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupMethods"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("/STELLA")))));
          Stella.defineGlobalVariableObject("(DEFGLOBAL *MAXIMUM-STRING-CONSTANT-SIZE* INTEGER 4000 :DOCUMENTATION \"Maximum size for a string constant in the target language.\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *FUNCTION-LOOKUP-TABLE* (HASH-TABLE OF SYMBOL STANDARD-OBJECT) (NEW (HASH-TABLE OF SYMBOL FUNCTION)) :DOCUMENTATION \"Lookup table for functions.\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *GLOBAL-VARIABLE-LOOKUP-TABLE* (HASH-TABLE OF SYMBOL GLOBAL-VARIABLE) (NEW (HASH-TABLE OF SYMBOL GLOBAL-VARIABLE)) :DOCUMENTATION \"Lookup table for global variables.\" :PUBLIC? TRUE)", null);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
