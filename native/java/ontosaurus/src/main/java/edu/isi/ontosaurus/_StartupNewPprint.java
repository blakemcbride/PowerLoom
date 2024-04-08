//  -*- Mode: Java -*-
//
// _StartupNewPprint.java

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
 | Portions created by the Initial Developer are Copyright (C) 2000-2023      |
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

package edu.isi.ontosaurus;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.powerloom.logic.*;
import edu.isi.stella.*;

public class _StartupNewPprint {
  static void helpStartupNewPprint1() {
    {
      OntosaurusUtil.SGT_STELLA_LITERAL_WRAPPER = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("LITERAL-WRAPPER", Stella.getStellaModule("/STELLA", true), 1)));
      OntosaurusUtil.SGT_LOGIC_PATTERN_VARIABLE = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PATTERN-VARIABLE", Stella.getStellaModule("/LOGIC", true), 1)));
      OntosaurusUtil.SGT_LOGIC_SKOLEM = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("SKOLEM", Stella.getStellaModule("/LOGIC", true), 1)));
      OntosaurusUtil.SGT_LOGIC_LOGIC_THING = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("LOGIC-THING", Stella.getStellaModule("/LOGIC", true), 1)));
      OntosaurusUtil.SGT_STELLA_THING = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("THING", Stella.getStellaModule("/STELLA", true), 1)));
      OntosaurusUtil.SGT_STELLA_MUTABLE_STRING_WRAPPER = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("MUTABLE-STRING-WRAPPER", Stella.getStellaModule("/STELLA", true), 1)));
      OntosaurusUtil.SGT_LOGIC_NAMED_DESCRIPTION = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("NAMED-DESCRIPTION", Stella.getStellaModule("/LOGIC", true), 1)));
      OntosaurusUtil.SGT_LOGIC_PROPOSITION = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PROPOSITION", Stella.getStellaModule("/LOGIC", true), 1)));
      OntosaurusUtil.SGT_LOGIC_DESCRIPTION = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("DESCRIPTION", Stella.getStellaModule("/LOGIC", true), 1)));
      OntosaurusUtil.SGT_STELLA_COLLECTION = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("COLLECTION", Stella.getStellaModule("/STELLA", true), 1)));
      OntosaurusUtil.SGT_STELLA_CONS = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("CONS", Stella.getStellaModule("/STELLA", true), 1)));
      OntosaurusUtil.SGT_PL_KERNEL_KB_AND = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("AND", Stella.getStellaModule("/PL-KERNEL-KB", true), 1)));
      OntosaurusUtil.SGT_PL_KERNEL_KB_OR = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("OR", Stella.getStellaModule("/PL-KERNEL-KB", true), 1)));
      OntosaurusUtil.SGT_PL_KERNEL_KB_NOT = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("NOT", Stella.getStellaModule("/PL-KERNEL-KB", true), 1)));
      OntosaurusUtil.SGT_PL_KERNEL_KB_FAIL = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("FAIL", Stella.getStellaModule("/PL-KERNEL-KB", true), 1)));
      OntosaurusUtil.SGT_PL_KERNEL_KB_FORALL = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("FORALL", Stella.getStellaModule("/PL-KERNEL-KB", true), 1)));
      OntosaurusUtil.SGT_PL_KERNEL_KB_EXISTS = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("EXISTS", Stella.getStellaModule("/PL-KERNEL-KB", true), 1)));
      OntosaurusUtil.SGT_PL_KERNEL_KB_KAPPA = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("KAPPA", Stella.getStellaModule("/PL-KERNEL-KB", true), 1)));
      OntosaurusUtil.SGT_PL_KERNEL_KB_SUBSET_OF = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("SUBSET-OF", Stella.getStellaModule("/PL-KERNEL-KB", true), 1)));
      OntosaurusUtil.SGT_PL_KERNEL_KB_SETOF = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("SETOF", Stella.getStellaModule("/PL-KERNEL-KB", true), 1)));
      OntosaurusUtil.SGT_PL_KERNEL_KB_LISTOF = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("LISTOF", Stella.getStellaModule("/PL-KERNEL-KB", true), 1)));
      OntosaurusUtil.SGT_PL_KERNEL_KB_BAGOF = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("BAGOF", Stella.getStellaModule("/PL-KERNEL-KB", true), 1)));
      OntosaurusUtil.SGT_STELLA_TRUE = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("TRUE", Stella.getStellaModule("/STELLA", true), 1)));
      OntosaurusUtil.SGT_STELLA_FALSE = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("FALSE", Stella.getStellaModule("/STELLA", true), 1)));
      OntosaurusUtil.SGT_PL_KERNEL_KB_EQUIVALENT = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("EQUIVALENT", Stella.getStellaModule("/PL-KERNEL-KB", true), 1)));
      OntosaurusUtil.KWD_PREDICATE = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("PREDICATE", null, 2)));
      OntosaurusUtil.KWD_ISA = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("ISA", null, 2)));
      OntosaurusUtil.KWD_FUNCTION = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("FUNCTION", null, 2)));
      OntosaurusUtil.KWD_AND = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("AND", null, 2)));
      OntosaurusUtil.KWD_OR = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("OR", null, 2)));
      OntosaurusUtil.KWD_NOT = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("NOT", null, 2)));
      OntosaurusUtil.KWD_EQUIVALENT = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("EQUIVALENT", null, 2)));
      OntosaurusUtil.KWD_FAIL = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("FAIL", null, 2)));
      OntosaurusUtil.KWD_CONSTANT = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("CONSTANT", null, 2)));
      OntosaurusUtil.KWD_EXISTS = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("EXISTS", null, 2)));
      OntosaurusUtil.SYM_LOGIC_IO_VARIABLES = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("IO-VARIABLES", Stella.getStellaModule("/LOGIC", true), 0)));
      OntosaurusUtil.KWD_FORALL = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("FORALL", null, 2)));
      OntosaurusUtil.KWD_IMPLIES = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("IMPLIES", null, 2)));
      OntosaurusUtil.SYM_LOGIC_COMPLEMENT_DESCRIPTION = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("COMPLEMENT-DESCRIPTION", Stella.getStellaModule("/LOGIC", true), 0)));
      OntosaurusUtil.SYM_LOGIC_FORWARD_ONLYp = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("FORWARD-ONLY?", Stella.getStellaModule("/LOGIC", true), 0)));
      OntosaurusUtil.SGT_STELLA_SYMBOL = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("SYMBOL", Stella.getStellaModule("/STELLA", true), 1)));
      OntosaurusUtil.KWD_KIF = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("KIF", null, 2)));
      OntosaurusUtil.KWD_KIF_ONTOSAURUS = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("KIF-ONTOSAURUS", null, 2)));
      OntosaurusUtil.SYM_ONTOSAURUS_STARTUP_NEW_PPRINT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-NEW-PPRINT", null, 0)));
    }
  }

  public static void startupNewPprint() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/ONTOSAURUS", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          _StartupNewPprint.helpStartupNewPprint1();
        }
        if (Stella.currentStartupTimePhaseP(4)) {
          OntosaurusUtil.REUSABLE_SKOLEM_MAPPING_TABLE = ((KeyValueMap)(KeyValueMap.newKeyValueMap()));
          OntosaurusUtil.$PPRINT_ATOMIC_OBJECT_RENDERER$.setDefaultValue(null);
          OntosaurusUtil.$PPRINT_BEFORE_PROPOSITION_FUNCTION$.setDefaultValue(null);
          OntosaurusUtil.$PPRINT_AFTER_PROPOSITION_FUNCTION$.setDefaultValue(null);
          OntosaurusUtil.$PPRINT_BEFORE_DEFINITION_FUNCTION$.setDefaultValue(null);
          OntosaurusUtil.$PPRINT_AFTER_DEFINITION_FUNCTION$.setDefaultValue(null);
          OntosaurusUtil.$PPRINT_INDENT$.setDefaultValue(new Integer(0));
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("PPRINT-NEWLINE", "(DEFUN PPRINT-NEWLINE ((STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintNewline", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-ATOMIC-OBJECT", "(DEFUN PPRINT-ATOMIC-OBJECT ((SELF OBJECT) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintAtomicObject", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-LITERAL-WRAPPER", "(DEFUN PPRINT-LITERAL-WRAPPER ((SELF LITERAL-WRAPPER) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintLiteralWrapper", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.LiteralWrapper"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-AS-ATOMIC-OBJECT?", "(DEFUN (PPRINT-AS-ATOMIC-OBJECT? BOOLEAN) ((SELF OBJECT)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintAsAtomicObjectP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineFunctionObject("PPRINT-COMPOSITE-OBJECT", "(DEFUN PPRINT-COMPOSITE-OBJECT ((SELF OBJECT) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintCompositeObject", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-OBJECT", "(DEFUN PPRINT-OBJECT ((SELF OBJECT) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintObject", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-ARGUMENTS", "(DEFUN PPRINT-ARGUMENTS ((ARGUMENTS ARGUMENTS-VECTOR) (SEPARATELINES? BOOLEAN) (OMITLASTARGUMENT? BOOLEAN) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintArguments", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Vector"), java.lang.Boolean.TYPE, java.lang.Boolean.TYPE, Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("SHORT-TERM?", "(DEFUN (SHORT-TERM? BOOLEAN) ((ARG OBJECT)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "shortTermP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineFunctionObject("OPERATOR-TO-STRING", "(DEFUN (OPERATOR-TO-STRING STRING) ((OPERATOR OBJECT)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "operatorToString", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineFunctionObject("PPRINT-OPERATOR-WITH-ARGUMENTS", "(DEFUN PPRINT-OPERATOR-WITH-ARGUMENTS ((OPERATORNAME STRING) (ARGUMENTS ARGUMENTS-VECTOR) (SEPARATELINES? BOOLEAN) (OMITLASTARGUMENT? BOOLEAN) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintOperatorWithArguments", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.Vector"), java.lang.Boolean.TYPE, java.lang.Boolean.TYPE, Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-RELATION-PROPOSITION", "(DEFUN PPRINT-RELATION-PROPOSITION ((SELF PROPOSITION) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintRelationProposition", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Proposition"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-FUNCTION-TERM", "(DEFUN PPRINT-FUNCTION-TERM ((SELF PROPOSITION) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintFunctionTerm", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Proposition"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-FUNCTION-PROPOSITION", "(DEFUN PPRINT-FUNCTION-PROPOSITION ((SELF PROPOSITION) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintFunctionProposition", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Proposition"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-PROPOSITION", "(DEFUN PPRINT-PROPOSITION ((SELF PROPOSITION) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintProposition", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Proposition"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-QUANTIFIED-VARIABLES", "(DEFUN PPRINT-QUANTIFIED-VARIABLES ((VARIABLES (VECTOR OF SKOLEM)) (INCLUDETYPES? BOOLEAN) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintQuantifiedVariables", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Vector"), java.lang.Boolean.TYPE, Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-NAMED-DESCRIPTION", "(DEFUN PPRINT-NAMED-DESCRIPTION ((SELF NAMED-DESCRIPTION) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintNamedDescription", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.NamedDescription"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-DESCRIPTION", "(DEFUN PPRINT-DESCRIPTION ((SELF DESCRIPTION) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintDescription", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Description"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-DESCRIPTION-BODY", "(DEFUN PPRINT-DESCRIPTION-BODY ((DESCRIPTION DESCRIPTION) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintDescriptionBody", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Description"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-NAMED-DESCRIPTIONS-AS-RULE", "(DEFUN PPRINT-NAMED-DESCRIPTIONS-AS-RULE ((HEAD NAMED-DESCRIPTION) (TAIL NAMED-DESCRIPTION) (OPERATORPREFIX STRING) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintNamedDescriptionsAsRule", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.NamedDescription"), Native.find_java_class("edu.isi.powerloom.logic.NamedDescription"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("HELP-PPRINT-DESCRIPTIONS-AS-RULE", "(DEFUN HELP-PPRINT-DESCRIPTIONS-AS-RULE ((DESC DESCRIPTION) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "helpPprintDescriptionsAsRule", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Description"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-DESCRIPTIONS-AS-RULE", "(DEFUN PPRINT-DESCRIPTIONS-AS-RULE ((HEAD DESCRIPTION) (TAIL DESCRIPTION) (RULE PROPOSITION) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintDescriptionsAsRule", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Description"), Native.find_java_class("edu.isi.powerloom.logic.Description"), Native.find_java_class("edu.isi.powerloom.logic.Proposition"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-IMPLIES-PROPOSITION", "(DEFUN PPRINT-IMPLIES-PROPOSITION ((SELF PROPOSITION) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintImpliesProposition", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Proposition"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-STELLA-COLLECTION", "(DEFUN PPRINT-STELLA-COLLECTION ((SELF COLLECTION) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintStellaCollection", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Collection"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-STELLA-CONS", "(DEFUN PPRINT-STELLA-CONS ((SELF CONS) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintStellaCons", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-DEFINITION", "(DEFUN PPRINT-DEFINITION ((SELF CONS) (HASVARIABLES? BOOLEAN) (STREAM NATIVE-OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintDefinition", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons"), java.lang.Boolean.TYPE, Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}), null);
          Stella.defineFunctionObject("PPRINT-ONTOSAURUS-OBJECT", "(DEFUN PPRINT-ONTOSAURUS-OBJECT ((SELF OBJECT) (STREAM OUTPUT-STREAM)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintOntosaurusObject", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.OutputStream")}), null);
          Stella.defineFunctionObject("STARTUP-NEW-PPRINT", "(DEFUN STARTUP-NEW-PPRINT () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.ontosaurus._StartupNewPprint", "startupNewPprint", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(OntosaurusUtil.SYM_ONTOSAURUS_STARTUP_NEW_PPRINT);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, OntosaurusUtil.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupNewPprint"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("ONTOSAURUS")))));
          Stella.defineGlobalVariableObject("(DEFCONSTANT REUSABLE-SKOLEM-MAPPING-TABLE (ENTITY-MAPPING OF SKOLEM SKOLEM) (NEW ENTITY-MAPPING) :DOCUMENTATION \"Stores reusable key-value list for use by\n'print-descriptions-as-kif-rule'.\")", null);
          Stella.defineGlobalVariableObject("(DEFSPECIAL *PPRINT-ATOMIC-OBJECT-RENDERER* FUNCTION-CODE NULL :PUBLIC? TRUE :DOCUMENTATION \"A function that takes two arguments, a Stella Object\nand a NATIVE-(?) OUTPUT-STREAM, and writes a representation of that\nobject on that stream.  This will only be called on `atomic' Stella\nobjects -- compound objects like Conses, Propositions, etc. are handled\nby the outer code.\")", null);
          Stella.defineGlobalVariableObject("(DEFSPECIAL *PPRINT-BEFORE-PROPOSITION-FUNCTION* FUNCTION-CODE NULL :PUBLIC? TRUE :DOCUMENTATION \"A function that takes two arguments, a Stella Proposition\nand a NATIVE-(?) OUTPUT-STREAM, and writes something that precedes the\nnormal printed representation of a proposition.   This will only be called \non `PROPOSITION' objects.\")", null);
          Stella.defineGlobalVariableObject("(DEFSPECIAL *PPRINT-AFTER-PROPOSITION-FUNCTION* FUNCTION-CODE NULL :PUBLIC? TRUE :DOCUMENTATION \"A function that takes two arguments, a Stella Proposition\nand a NATIVE-(?) OUTPUT-STREAM, and writes something that precedes the\nnormal printed representation of a proposition.   This will only be called \non `PROPOSITION' objects.\")", null);
          Stella.defineGlobalVariableObject("(DEFSPECIAL *PPRINT-BEFORE-DEFINITION-FUNCTION* FUNCTION-CODE NULL :PUBLIC? TRUE :DOCUMENTATION \"A function that takes two arguments, a Stella Definition\nand a NATIVE-(?) OUTPUT-STREAM, and writes something that precedes the\nnormal printed representation of a definition.   This will only be called \non `DEFINITION' objects.\")", null);
          Stella.defineGlobalVariableObject("(DEFSPECIAL *PPRINT-AFTER-DEFINITION-FUNCTION* FUNCTION-CODE NULL :PUBLIC? TRUE :DOCUMENTATION \"A function that takes two arguments, a Stella Definition\nand a NATIVE-(?) OUTPUT-STREAM, and writes something that precedes the\nnormal printed representation of a definition.   This will only be called \non `DEFINITION' objects.\")", null);
          Stella.defineGlobalVariableObject("(DEFSPECIAL *PPRINT-INDENT* INTEGER 0)", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *DOWNCASE-STANDARD-KIF-OPERATORS?* BOOLEAN TRUE)", null);
          Logic.registerLogicDialectPrintFunction(OntosaurusUtil.KWD_KIF_ONTOSAURUS, FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintOntosaurusObject", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.OutputStream")})));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
