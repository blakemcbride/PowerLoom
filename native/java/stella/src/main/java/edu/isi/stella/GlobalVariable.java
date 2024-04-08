//  -*- Mode: Java -*-
//
// GlobalVariable.java

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

public class GlobalVariable extends MappableObject {
    public String documentation;
    public Symbol variableName;
    public Surrogate variableType;
    public boolean variableSpecialP;
    public boolean variableConstantP;
    public boolean variablePublicP;
    public boolean variableAuxiliaryP;
    /** Points to a handle that can be used to access the native value.
     */
    public Object variableNativeObject;
    public String variableStringifiedSource;

  public static GlobalVariable newGlobalVariable() {
    { GlobalVariable self = null;

      self = new GlobalVariable();
      self.dynamicSlots = KeyValueList.newKeyValueList();
      self.variableStringifiedSource = null;
      self.documentation = null;
      self.variableNativeObject = null;
      self.variableAuxiliaryP = false;
      self.variablePublicP = true;
      self.variableConstantP = false;
      self.variableSpecialP = false;
      self.variableType = null;
      self.variableName = null;
      return (self);
    }
  }

  public static StringWrapper cppTranslateGlobalVariableAddress(GlobalVariable global) {
    return (StringWrapper.wrapString("&" + GlobalVariable.cppTranslateGlobalVariableName(global).wrapperValue));
  }

  public static StringWrapper cppTranslateGlobalVariableName(GlobalVariable global) {
    return (Symbol.cppTranslateGlobalName(Symbol.cppFixupNameSymbol(global.variableName, global.homeModule())));
  }

  public static MethodSlot lookupVariableDemonSetter(GlobalVariable demon) {
    { Symbol variablename = demon.variableName;
      String postfix = (demon.homeModule().caseSensitiveP ? "-setter" : "-SETTER");
      Symbol settername = Symbol.internDerivedSymbol(variablename, variablename.symbolName + postfix);

      return (Symbol.lookupFunction(settername));
    }
  }

  public static Cons clYieldGlobalVariableTypeDeclarationTree(GlobalVariable global) {
    { Stella_Object cltype = StandardObject.lookupClTypeFromStellaType(GlobalVariable.globalVariableTypeSpec(global));

      if (cltype != null) {
        return (((Cons)(Stella_Object.clConditionalizeTypeDeclarationTree(Cons.list$(Cons.cons(Stella.internCommonLispSymbol("TYPE"), Cons.cons(cltype, Cons.cons(Cons.cons(Symbol.clTranslateGlobalSymbol(global.variableName), Stella.NIL), Stella.NIL))))))));
      }
      else {
        return (null);
      }
    }
  }

  public static Cons yieldGlobalVariableCSignature(GlobalVariable global) {
    { Cons sig = GlobalVariable.yieldGlobalVariableCppSignature(global, true);
      StringWrapper cppname = ((StringWrapper)(((Cons)(sig.value)).value));
      StringWrapper cpptype = ((StringWrapper)(((Cons)(sig.value)).rest.value));

      ((Cons)(sig.value)).firstSetter(StringWrapper.wrapString(Stella.replaceSubstrings(cppname.wrapperValue, "_", "::")));
      ((Cons)(sig.value)).secondSetter(StringWrapper.wrapString(Stella.cppTypeToCType(cpptype.wrapperValue)));
      return (sig);
    }
  }

  public static Cons yieldGlobalVariableCppSignature(GlobalVariable global, boolean qualifyP) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, (qualifyP ? Stella.$ROOT_MODULE$ : global.homeModule()));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        { Cons cppsig = Cons.cons(Cons.cons(GlobalVariable.cppTranslateGlobalVariableName(global), Cons.cons(StandardObject.cppTranslateAndPointerizeTypeSpec(GlobalVariable.globalVariableTypeSpec(global)), Cons.cons(StringWrapper.wrapString(Native.stringify(StandardObject.typeSpecToBaseType(GlobalVariable.globalVariableTypeSpec(global)))), Stella.NIL))), Stella.NIL);

          return (cppsig);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Interpreted global <code>variable</code> writer which sets its native value to <code>value</code>
   * unwrappig it if necessary.  This will change the current value at the top of the special stack.
   * @param variable
   * @param value
   */
  public static void writeGlobalVariableValue(GlobalVariable variable, Stella_Object value) {
    Stella.writeNativeVariableValue(GlobalVariable.getGlobalVariableNativeObject(variable), variable.variableType, value);
  }

  /** Interpreted global <code>variable</code> reader which reads and returns its native value
   * which will be wrapped if necessary.  This will access the value at the top of the special stack.
   * @param variable
   * @return Stella_Object
   */
  public static Stella_Object readGlobalVariableValue(GlobalVariable variable) {
    return (Stella.readNativeVariableValue(GlobalVariable.getGlobalVariableNativeObject(variable), variable.variableType));
  }

  /** Return the native object of <code>variable</code> which can be used to access its runtime value.
   * In Lisp this is the Lisp symbol which holds the variable value, in C++ this is the address of the variable,
   * and in Java this is the declared Field object.  For C++ native object addresses are initialized at startup
   * time, for Lisp and Java native objects will be accessed upon first call and then cached in the slot.
   * @param variable
   * @return Object
   */
  public static Object getGlobalVariableNativeObject(GlobalVariable variable) {
    { Object varobj = variable.variableNativeObject;

      if (!(varobj == null)) {
        return (varobj);
      }
      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, variable.homeModule());
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          { String varname = Symbol.javaTranslateGlobalName(variable.variableName, true).wrapperValue;
            String classname = Module.javaYieldFlotsamClassName(((Module)(Stella.$MODULE$.get())));
            String pkgname = Module.javaPackagePrefix(((Module)(Stella.$MODULE$.get())), ".");
            String errmsg = null;

            try { varobj = Class.forName(pkgname + classname).getDeclaredField(varname); }
             catch (Exception e) { errmsg = e.getMessage(); }
;
            if (errmsg != null) {
              { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

                stream000.nativeStream.print("`" + errmsg + "'");
                throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
              }
            }
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
      variable.variableNativeObject = varobj;
      return (varobj);
    }
  }

  public static void destroyGlobalVariable(GlobalVariable variable) {
    { Symbol variablename = variable.variableName;
      GlobalVariable realvariable = variablename.lookupGlobalVariable();

      if (variable == realvariable) {
        Stella.$GLOBAL_VARIABLE_LOOKUP_TABLE$.removeAt(variablename);
      }
      variable.deletedPSetter(true);
      variable.free();
    }
  }

  public static Module recordVariableHomeModule(GlobalVariable self) {
    { Symbol name = self.variableName;
      Module namemodule = ((Module)(name.homeContext));
      Module definitionmodule = ((Module)(Stella.$MODULE$.get()));
      Module homemodule = namemodule;

      if (GeneralizedSymbol.explicitlyQualifiedNameP(name, definitionmodule)) {
        homemodule = namemodule;
      }
      else {
        homemodule = definitionmodule;
      }
      if (!(homemodule == namemodule)) {
        KeyValueList.setDynamicSlotValue(self.dynamicSlots, Stella.SYM_STELLA_VARIABLE_HOME_MODULE, homemodule, null);
      }
      return (homemodule);
    }
  }

  /** Return the type spec for the global variable <code>global</code>.
   * @param global
   * @return StandardObject
   */
  public static StandardObject globalVariableTypeSpec(GlobalVariable global) {
    { StandardObject type = ((StandardObject)(KeyValueList.dynamicSlotValue(global.dynamicSlots, Stella.SYM_STELLA_VARIABLE_TYPE_SPECIFIER, null)));

      if (type != null) {
        return (type);
      }
      else {
        return (global.variableType);
      }
    }
  }

  public static GlobalVariable internGlobalVariable(GlobalVariable global) {
    { Symbol name = global.variableName;
      GlobalVariable oldglobal = name.lookupGlobalVariable();

      if (oldglobal != null) {
        if (Stella.stringEqlP(global.variableStringifiedSource, oldglobal.variableStringifiedSource)) {
          global.free();
          return (oldglobal);
        }
        else {
          Stella.STANDARD_OUTPUT.nativeStream.println("Redefining the global variable `" + global.variableName + "'");
          oldglobal.free();
        }
      }
      Stella.$GLOBAL_VARIABLE_LOOKUP_TABLE$.insertAt(name, global);
      return (global);
    }
  }

  public static Stella_Object accessGlobalVariableSlotValue(GlobalVariable self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == Stella.SYM_STELLA_DOCUMENTATION) {
      if (setvalueP) {
        self.documentation = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.documentation);
      }
    }
    else if (slotname == Stella.SYM_STELLA_VARIABLE_NAME) {
      if (setvalueP) {
        self.variableName = ((Symbol)(value));
      }
      else {
        value = self.variableName;
      }
    }
    else if (slotname == Stella.SYM_STELLA_VARIABLE_TYPE) {
      if (setvalueP) {
        self.variableType = ((Surrogate)(value));
      }
      else {
        value = self.variableType;
      }
    }
    else if (slotname == Stella.SYM_STELLA_VARIABLE_SPECIALp) {
      if (setvalueP) {
        self.variableSpecialP = BooleanWrapper.coerceWrappedBooleanToBoolean(((BooleanWrapper)(value)));
      }
      else {
        value = (self.variableSpecialP ? Stella.TRUE_WRAPPER : Stella.FALSE_WRAPPER);
      }
    }
    else if (slotname == Stella.SYM_STELLA_VARIABLE_CONSTANTp) {
      if (setvalueP) {
        self.variableConstantP = BooleanWrapper.coerceWrappedBooleanToBoolean(((BooleanWrapper)(value)));
      }
      else {
        value = (self.variableConstantP ? Stella.TRUE_WRAPPER : Stella.FALSE_WRAPPER);
      }
    }
    else if (slotname == Stella.SYM_STELLA_VARIABLE_PUBLICp) {
      if (setvalueP) {
        self.variablePublicP = BooleanWrapper.coerceWrappedBooleanToBoolean(((BooleanWrapper)(value)));
      }
      else {
        value = (self.variablePublicP ? Stella.TRUE_WRAPPER : Stella.FALSE_WRAPPER);
      }
    }
    else if (slotname == Stella.SYM_STELLA_VARIABLE_AUXILIARYp) {
      if (setvalueP) {
        self.variableAuxiliaryP = BooleanWrapper.coerceWrappedBooleanToBoolean(((BooleanWrapper)(value)));
      }
      else {
        value = (self.variableAuxiliaryP ? Stella.TRUE_WRAPPER : Stella.FALSE_WRAPPER);
      }
    }
    else if (slotname == Stella.SYM_STELLA_VARIABLE_DOCUMENTATION) {
      if (setvalueP) {
        self.documentation = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.documentation);
      }
    }
    else if (slotname == Stella.SYM_STELLA_VARIABLE_STRINGIFIED_SOURCE) {
      if (setvalueP) {
        self.variableStringifiedSource = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.variableStringifiedSource);
      }
    }
    else {
      if (setvalueP) {
        KeyValueList.setDynamicSlotValue(self.dynamicSlots, slotname, value, null);
      }
      else {
        value = self.dynamicSlots.lookup(slotname);
      }
    }
    return (value);
  }

  public Module homeModule() {
    { GlobalVariable self = this;

      { Module module = ((Module)(KeyValueList.dynamicSlotValue(self.dynamicSlots, Stella.SYM_STELLA_VARIABLE_HOME_MODULE, null)));

        if (module != null) {
          return (module);
        }
        else {
          return (((Module)(self.variableName.homeContext)));
        }
      }
    }
  }

  public Surrogate type() {
    { GlobalVariable self = this;

      return (self.variableType);
    }
  }

  public String name() {
    { GlobalVariable self = this;

      return (self.variableName.symbolName);
    }
  }

  public Surrogate primaryType() {
    { GlobalVariable self = this;

      return (Stella.SGT_STELLA_GLOBAL_VARIABLE);
    }
  }

}

