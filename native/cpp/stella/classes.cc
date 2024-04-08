//  -*- Mode: C++ -*-

// classes.cc

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

const char* className(Class* clasS) {
  return (clasS->classType->symbolName);
}

Surrogate* classSurrogate(Class* clasS) {
  return (clasS->classType);
}

Symbol* classSymbol(Class* clasS) {
  return (internSymbolInModule(clasS->classType->symbolName, ((Module*)(clasS->classType->homeContext)), true));
}

Class* Object::primaryClass() {
  { Object* self = this;

    if (((boolean)(self->primaryType()))) {
      return (((Class*)(self->primaryType()->surrogateValue)));
    }
    return (NULL);
  }
}

extern "C" Class* stella_objectPrimaryClass(Object* self) {
  // C-callable wrapper for `Object::primaryClass'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(self->primaryClass()));
    return (((Class*)(oC_API_RESULT_BUFFERo)));
  }
}

Class* stringLookupClass(const char* name) {
  // Return a class with name `name'.  Scan all
  // visible surrogates looking for one that has a class defined for it.
  { Object* clasS = NULL;
    Surrogate* surrogate = NULL;

    { Module* module = NULL;
      Cons* iter000 = visibleModules(oMODULEo);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        module = ((Module*)(iter000->value));
        { boolean testValue000 = false;

          { 
            surrogate = ((Surrogate*)(lookupRigidSymbolLocally(name, module, SURROGATE_SYM)));
            testValue000 = ((boolean)(surrogate));
          }
          if (testValue000) {
            { 
              clasS = surrogate->surrogateValue;
              testValue000 = ((boolean)(clasS));
            }
            if (testValue000) {
              testValue000 = isaP(clasS, SGT_CLASSES_STELLA_CLASS);
            }
          }
          if (testValue000) {
            return (((Class*)(clasS)));
          }
        }
      }
    }
    return (NULL);
  }
}

Class* Symbol::lookupClass() {
  // Return a class with name `name'.  Scan all
  // visible surrogates looking for one that has a class defined for it.
  { Symbol* name = this;

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, ((Module*)(name->homeContext)));
      return (stringLookupClass(name->symbolName));
    }
  }
}

Class* lookupClassByQualifiedName(const char* qualifiedname) {
  // Variant of `string.lookup-class' that can specify a
  // starting module through a `qualifiedName'.
  { const char* classname = NULL;
    const char* modulename = NULL;
    Keyword* kind = NULL;

    classname = parseStellaName(qualifiedname, true, modulename, kind);
    kind = kind;
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, ((modulename != NULL) ? getStellaModule(modulename, true) : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      return (stringLookupClass(classname));
    }
  }
}

Class* typeToClass(Surrogate* type) {
  return (((Class*)(type->surrogateValue)));
}

Class* Surrogate::getStellaClass(boolean errorP) {
  // Return a class with name `class-name'.  If none exists, break
  // if `error?', else return `null'.
  { Surrogate* className = this;

    { Object* clasS = className->surrogateValue;

      if (((boolean)(clasS)) &&
          stellaClassP(clasS)) {
        return (((Class*)(clasS)));
      }
      if (errorP) {
        std::cerr << "Class " << "`" << className << "'" << " does not exist.";
      }
      return (NULL);
    }
  }
}

Class* stringGetStellaClass(const char* className, boolean errorP) {
  // Return a class with name `class-name'.  If none exists, break
  // if `error?', else return `null'.
  { Surrogate* type = lookupSurrogate(className);

    if (((boolean)(type))) {
      return (type->getStellaClass(errorP));
    }
    if (errorP) {
      std::cerr << "Class " << "`" << className << "'" << " does not exist.";
    }
    return (NULL);
  }
}

Class* Symbol::getStellaClass(boolean errorP) {
  // Return a class with name `class-name'.  If non exists, break
  // if `error?', else return `null'.
  { Symbol* className = this;

    return (stringGetStellaClass(className->symbolName, errorP));
  }
}

// If set, warn about each redefinition.
DEFINE_STELLA_SPECIAL(oWARNIFREDEFINEpo, boolean , true);

boolean bindToSurrogateP(Object* self, const char* name, boolean clipoldvalueP, boolean askforpermissionP, Object*& _Return1, Surrogate*& _Return2) {
  { Surrogate* oldsurrogate = lookupSurrogate(name);
    Object* oldvalue = (((boolean)(oldsurrogate)) ? oldsurrogate->surrogateValue : ((Object*)(NULL)));
    Surrogate* surrogate = shadowSurrogate(name);
    Module* oldmodule = NULL;

    if (!((boolean)(oldvalue))) {
      surrogate->surrogateValue = self;
      _Return1 = NULL;
      _Return2 = surrogate;
      return (true);
    }
    if (eqlP(oldvalue, self)) {
      _Return1 = NULL;
      _Return2 = surrogate;
      return (true);
    }
    oldmodule = ((Module*)(oldsurrogate->homeContext));
    if (!(oldmodule == oMODULEo)) {
      surrogate->surrogateValue = self;
      if (askforpermissionP) {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "Shadowing the " << "`" << self->primaryType()->symbolName << "'" << " named " << "`" << name << "'" << std::endl;
        std::cout << "CAUTION: Automatic shadowing can be dangerous, because forward " << std::endl << "   references to a shadowed object may be bound to the now-shadowed " << std::endl << "   object.  Suggestion: Explicitly shadow the name using" << std::endl << "   DEFMODULE's `:shadow' option." << std::endl;
        if (yesOrNoP("Do it anyway? ")) {
          surrogate->surrogateValue = self;
          _Return1 = oldvalue;
          _Return2 = surrogate;
          return (true);
        }
      }
      _Return1 = NULL;
      _Return2 = surrogate;
      return (true);
    }
    else if (clipoldvalueP) {
      if (oWARNIFREDEFINEpo) {
        std::cout << "Redefining the " << "`" << self->primaryType()->symbolName << "'" << " named " << "`" << name << "'" << std::endl;
      }
      surrogate->surrogateValue = self;
      if (!(self->primaryType() == oldvalue->primaryType())) {
        oldvalue = NULL;
      }
      _Return1 = oldvalue;
      _Return2 = surrogate;
      return (true);
    }
    else {
      if (askforpermissionP) {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't define the " << "`" << self->primaryType()->symbolName << "'" << " named " << "`" << name << "'" << " in module " << "`" << oMODULEo << "'" << std::endl << "   because that term is already bound to " << "`" << oldvalue << "'" << std::endl << std::endl;
        if (yesOrNoP("Do it anyway? ")) {
          surrogate->surrogateValue = self;
          _Return1 = oldvalue;
          _Return2 = surrogate;
          return (true);
        }
      }
      _Return1 = NULL;
      _Return2 = surrogate;
      return (false);
    }
  }
}

void Class::unbindFromSurrogate() {
  { Class* self = this;

    { Surrogate* surrogate = self->classType;

      if (((boolean)(surrogate))) {
        surrogate->surrogateValue = NULL;
        self->classType = NULL;
      }
    }
  }
}

Symbol* shadowSymbol(const char* name) {
  return (((Symbol*)(internRigidSymbolLocally(name, oMODULEo, SYMBOL_SYM))));
}

Surrogate* shadowSurrogate(const char* name) {
  shadowSymbol(name);
  return (((Surrogate*)(internRigidSymbolLocally(name, oMODULEo, SURROGATE_SYM))));
}

boolean shadowedSymbolP(GeneralizedSymbol* symbol) {
  // Return `true' if `symbol' is shadowed in its home module.
  { const char* symbolname = symbol->symbolName;
    Module* module = ((Module*)(symbol->homeContext));

    { boolean testValue000 = false;

      testValue000 = ((boolean)(module));
      if (testValue000) {
        { boolean foundP000 = false;

          { Surrogate* shadow = NULL;
            Cons* iter000 = module->shadowedSurrogates_reader()->theConsList;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              shadow = ((Surrogate*)(iter000->value));
              if (stringEqlP(shadow->symbolName, symbolname)) {
                foundP000 = true;
                break;
              }
            }
          }
          testValue000 = foundP000;
        }
      }
      { boolean value000 = testValue000;

        return (value000);
      }
    }
  }
}

cpp_function_code getConstructor(Class* clasS, boolean warnP) {
  { cpp_function_code constructor = clasS->classConstructorCode;

    if (constructor != NULL) {
      return (constructor);
    }
    if (warnP) {
      if (clasS->abstractP) {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "The abstract class " << "`" << classSymbol(clasS) << "'" << " cannot have a constructor." << std::endl;
        return (NULL);
      }
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "The " << "`" << ((clasS->privateP() ? "private " : "")) << "'" << "class " << "`" << classSymbol(clasS) << "'" << " does not have a callable constructor." << std::endl;
    }
    return (NULL);
  }
}

Object* createObject(Surrogate* type, int initialValuePairs, ...) {
  // Funcallable version of the `new' operator.
  // Return an instance of the class named by `type'.  If `initial-value-pairs'
  // is supplied, it has to be a key/value list similar to what's accepted by `new'
  // and the named slots will be initialized with the supplied values.  Similar to
  // `new', all required arguments for `type' must be included.  Since all the
  // slot initialization, etc. is handled dynamically at run time, `create-object'
  // is much slower than `new'; therefore, it should only be used if `type' cannot
  // be known at translation time.
  { Class* clasS = type->getStellaClass(true);
    cpp_function_code constructorcode = getConstructor(clasS, true);

    { PropertyList* chooseValue000 = NULL;

      if (initialValuePairs == 0) {
        chooseValue000 = NULL;
      }
      else {
        { PropertyList* self000 = newPropertyList();

          { Cons* arglist000 = NIL;

            { va_list iter000;
              int iter000Count = initialValuePairs;
              Object* arg000 = NULL;
              Cons* collect000 = NULL;

              va_start(iter000, initialValuePairs);
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
            self000->thePlist = arglist000;
          }
          chooseValue000 = self000;
        }
      }
      { PropertyList* initialvalues = chooseValue000;
        List* requiredslots = clasS->classRequiredSlotNames_reader();
        Cons* requiredslotvalues = NIL;
        Object* slotvalue = NULL;
        Slot* slot = NULL;
        Object* object = NULL;

        if (!(constructorcode != NULL)) {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "create-object: no funcallable constructor available for " << "`" << type << "'";
            throw *newStellaException(stream000->theStringReader());
          }
        }
        if (requiredslots->nonEmptyP()) {
          if (!((boolean)(initialvalues))) {
            { OutputStringStream* stream001 = newOutputStringStream();

              *(stream001->nativeStream) << "create-object: missing initial values for " << "`" << type << "'" << "'s required slots";
              throw *newStellaException(stream001->theStringReader());
            }
          }
          { Symbol* reqslotname = NULL;
            Cons* iter001 = requiredslots->theConsList;
            Cons* collect001 = NULL;

            for  (; !(iter001 == NIL); 
                  iter001 = iter001->rest) {
              reqslotname = ((Symbol*)(iter001->value));
              slot = lookupSlot(clasS, reqslotname);
              if (!(subtypeOfP(slot->type(), SGT_CLASSES_STELLA_OBJECT))) {
                { OutputStringStream* stream002 = newOutputStringStream();

                  *(stream002->nativeStream) << "create-object: can't yet initialize required slot " << "`" << type << "'" << "." << "`" << reqslotname << "'" << ", since its type is not a subtype of OBJECT";
                  throw *newStellaException(stream002->theStringReader());
                }
              }
              slotvalue = initialvalues->lookup(reqslotname->keywordify());
              initialvalues->removeAt(reqslotname->keywordify());
              if (!((boolean)(slotvalue))) {
                { OutputStringStream* stream003 = newOutputStringStream();

                  *(stream003->nativeStream) << "create-object: missing initial value for required slot " << "`" << type << "'" << "." << "`" << reqslotname << "'";
                  throw *newStellaException(stream003->theStringReader());
                }
              }
              if (!((boolean)(collect001))) {
                {
                  collect001 = cons(slotvalue, NIL);
                  if (requiredslotvalues == NIL) {
                    requiredslotvalues = collect001;
                  }
                  else {
                    addConsToEndOfConsList(requiredslotvalues, collect001);
                  }
                }
              }
              else {
                {
                  collect001->rest = cons(slotvalue, NIL);
                  collect001 = collect001->rest;
                }
              }
            }
          }
        }
        object = apply(constructorcode, requiredslotvalues);
        if (((boolean)(initialvalues))) {
          { Object* slotname = NULL;
            Object* value = NULL;
            Cons* iter002 = initialvalues->thePlist;

            for  (; !(iter002 == NIL); 
                  iter002 = iter002->rest->rest) {
              slotname = iter002->value;
              value = iter002->rest->value;
              if (subtypeOfKeywordP(safePrimaryType(slotname))) {
                { Object* slotname000 = slotname;
                  Keyword* slotname = ((Keyword*)(slotname000));

                  slot = lookupSlot(clasS, internDerivedSymbol(type, slotname->symbolName));
                  if (!storageSlotP(slot)) {
                    { OutputStringStream* stream004 = newOutputStringStream();

                      *(stream004->nativeStream) << "create-object: slot " << "`" << slotname << "'" << " does not exist on class " << "`" << type << "'";
                      throw *newStellaException(stream004->theStringReader());
                    }
                  }
                  putSlotValue(((StandardObject*)(object)), ((StorageSlot*)(slot)), value);
                }
              }
              else {
                { OutputStringStream* stream005 = newOutputStringStream();

                  *(stream005->nativeStream) << "create-object: illegal initialization option: " << "`" << slotname << "'";
                  throw *newStellaException(stream005->theStringReader());
                }
              }
            }
          }
        }
        return (object);
      }
    }
  }
}

void Object::free() {
  // Default method.  Deallocate storage for `self'.
  { Object* self = this;

    unmake(self);
  }
}

void ActiveObject::free() {
  // Remove all pointers between `self' and other objects,
  // and then deallocate the storage for self.
  { ActiveObject* self = this;

    unmake(self);
  }
}

Class* defineStellaClass(Surrogate* name, List* supers, List* slots, KeywordKeyValueList* options) {
  // Return a Stella class with name `name'.
  // Caution:  If the class already exists, the Stella class object gets
  // redefined, but the native C++ class is not redefined.
  { Class* clasS = newClass();
    List* parameterslots = ((List*)(options->lookup(KWD_CLASSES_PARAMETERS)));
    Object* oldclass = NULL;
    boolean successP = false;

    if ((!(name->homeContext == oMODULEo)) &&
        (!visibleFromP(name->homeContext, oMODULEo))) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't define a class named " << "`" << name << "'" << " because the module " << std::endl << "   " << "`" << name->homeContext->contextName() << "'" << " is not visible from the current module " << "`" << oMODULEo->contextName() << "'" << "." << std::endl << std::endl;
      return (NULL);
    }
    { boolean value000 = false;
      Object* value001 = NULL;
      Surrogate* value002 = NULL;

      value000 = bindToSurrogateP(clasS, name->symbolName, true, true, value001, value002);
      {
        successP = value000;
        oldclass = value001;
        name = value002;
      }
    }
    if (!successP) {
      return (NULL);
    }
    clasS->classType = name;
    if (((boolean)(parameterslots))) {
      { Slot* s = NULL;
        Cons* iter000 = parameterslots->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          s = ((Slot*)(iter000->value));
          s->abstractP = true;
          slots->insertLast(s);
        }
      }
    }
    initializeSlotAndMethodCache(clasS);
    { Surrogate* s = NULL;
      Cons* iter001 = supers->theConsList;
      List* into000 = clasS->classDirectSupers;
      Cons* collect000 = NULL;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest) {
        s = ((Surrogate*)(iter001->value));
        if ((!stellaClassP(s->surrogateValue)) &&
            ((!(((Module*)(s->homeContext)) == oMODULEo)) &&
             visibleFromP(((Module*)(s->homeContext)), oMODULEo))) {
          if (oDEBUGLEVELo >= 3) {
            std::cout << "Automatically shadowing bogus super " << "`" << s << "'" << " of class " << "`" << name << "'" << std::endl;
          }
          s = shadowSurrogate(s->symbolName);
        }
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(s, NIL);
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
            collect000->rest = cons(s, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    incorporateClassOptions(clasS, options);
    { boolean testValue000 = false;

      testValue000 = !clasS->primitiveP();
      if (testValue000) {
        { boolean foundP000 = false;

          { Slot* slot = NULL;
            Cons* iter002 = slots->theConsList;

            for (; !(iter002 == NIL); iter002 = iter002->rest) {
              slot = ((Slot*)(iter002->value));
              if (slot->primitiveP()) {
                foundP000 = true;
                break;
              }
            }
          }
          testValue000 = foundP000;
        }
      }
      if (testValue000) {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "Defined class " << "`" << clasS << "'" << " illegally specifies primitive slots." << std::endl;
      }
    }
    clasS->classLocalSlots = slots;
    if (((boolean)(oldclass)) &&
        isaP(oldclass, SGT_CLASSES_STELLA_CLASS)) {
      undefineOldClass(((Class*)(oldclass)), clasS);
    }
    if (!((boolean)(clasS->classTaxonomyNode))) {
      clasS->classTaxonomyNode = createTaxonomyNode(oCLASS_TAXONOMY_GRAPHo, NULL, clasS, clasS->classDirectSupers->emptyP());
    }
    { Slot* slot = NULL;
      Cons* iter003 = slots->theConsList;

      for (; !(iter003 == NIL); iter003 = iter003->rest) {
        slot = ((Slot*)(iter003->value));
        registerSlotName(slot);
      }
    }
    rememberUnfinalizedClass(clasS, true);
    return (clasS);
  }
}

Slot* defineStellaSlot(Symbol* name, Surrogate* owner, Surrogate* basetype, Cons* typespecifier, KeywordKeyValueList* options) {
  { StorageSlot* slot = newStorageSlot();

    slot->slotName = name;
    slot->slotOwner = owner;
    slot->slotBaseType = basetype;
    if (!(typespecifier == NIL)) {
      setDynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_TYPE_SPECIFIER, ((CompoundTypeSpecifier*)(typespecifier->yieldTypeSpecifier())), NULL);
    }
    { Keyword* key = NULL;
      Object* value = NULL;
      KvListIterator* iter000 = ((KvListIterator*)(options->allocateIterator()));

      for  (; iter000->nextP(); ) {
        key = ((Keyword*)(iter000->key));
        value = iter000->value;
        if (key == KWD_CLASSES_PUBLICp) {
          slot->slotPublicP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
        }
        else if (key == KWD_CLASSES_REQUIREDp) {
          slot->slotRequiredP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
        }
        else if (key == KWD_CLASSES_COMPONENTp) {
          slot->slotComponentP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
        }
        else if (key == KWD_CLASSES_READ_ONLYp) {
          slot->slotReadOnlyP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
        }
        else if (key == KWD_CLASSES_ACTIVEp) {
          setDynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_STORED_ACTIVEp, ((BooleanWrapper*)(value)), NULL);
        }
        else if (key == KWD_CLASSES_CONTEXT_SENSITIVEp) {
          slot->slotContextSensitiveP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
        }
        else if (key == KWD_CLASSES_HARDWIREDp) {
          slot->slotHardwiredP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
        }
        else if (key == KWD_CLASSES_ABSTRACTp) {
          slot->abstractP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
        }
        else if (key == KWD_CLASSES_ALLOCATION) {
          if (value == KWD_CLASSES_CLASS) {
            *(STANDARD_WARNING->nativeStream) << "Warning: " << "In definition of slot " << "`" << slot << "'" << ": ':class' allocation is unsupported right now." << std::endl << " Maybe use ':hardwired? TRUE' for read-only slots." << std::endl;
          }
          else {
            setDynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_ALLOCATION, ((Keyword*)(value)), NULL);
          }
        }
        else if (key == KWD_CLASSES_INITIALLY) {
          setDynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_INITIAL_VALUE, value, NULL);
        }
        else if (key == KWD_CLASSES_DEFAULT) {
          setDynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_DEFAULT_EXPRESSION, value, NULL);
        }
        else if (key == KWD_CLASSES_READER) {
          setDynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_READER, ((Symbol*)(value)), NULL);
        }
        else if (key == KWD_CLASSES_WRITER) {
          setDynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_WRITER, ((Symbol*)(value)), NULL);
        }
        else if (key == KWD_CLASSES_INVERSE) {
          setDynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_INVERSE, ((Symbol*)(value)), NULL);
        }
        else if (key == KWD_CLASSES_RENAMES) {
          setDynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_RENAMES, ((Symbol*)(value)), NULL);
        }
        else if (key == KWD_CLASSES_DOCUMENTATION) {
          setDynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_DOCUMENTATION, wrapString(((StringWrapper*)(value))->wrapperValue), NULL_STRING_WRAPPER);
        }
        else if (key == KWD_CLASSES_PROPERTIES) {
          setDynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_PROPERTIES, ((List*)(value)), NULL);
        }
        else if (key == KWD_CLASSES_META_ATTRIBUTES) {
          setDynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_META_ATTRIBUTES, ((KeyValueList*)(value)), NULL);
        }
        else if (key == KWD_CLASSES_OPTION_KEYWORD) {
          setDynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_OPTION_KEYWORD, ((Keyword*)(value)), NULL);
        }
        else if (key == KWD_CLASSES_OPTION_HANDLER) {
          setDynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_OPTION_HANDLER, ((Symbol*)(value)), NULL);
        }
        else {
          if (!(runOptionHandlerP(slot, key, value))) {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationWarning();
              if (!(suppressWarningsP())) {
                printErrorContext(">> WARNING: ", STANDARD_WARNING);
                *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Skipping invalid slot option " << "`" << deUglifyParseTree(key) << "'" << std::endl << "in the definition of slot " << "`" << internSymbolInModule(owner->symbolName, ((Module*)(owner->homeContext)), true) << "'" << "." << "`" << deUglifyParseTree(name) << "'" << "." << std::endl;
              }
            }
          }
        }
      }
    }
    if ((!((boolean)(slot->slotAllocation_reader()))) &&
        (basetype == SGT_CLASSES_STELLA_BOOLEAN)) {
      setDynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_ALLOCATION, KWD_CLASSES_BIT, NULL);
    }
    return (slot);
  }
}

void incorporateClassOptions(Class* clasS, KeywordKeyValueList* options) {
  { Keyword* key = NULL;
    Object* value = NULL;
    KvListIterator* iter000 = ((KvListIterator*)(options->allocateIterator()));

    for  (; iter000->nextP(); ) {
      key = ((Keyword*)(iter000->key));
      value = iter000->value;
      if (key == KWD_CLASSES_DOCUMENTATION) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_DOCUMENTATION, wrapString(((StringWrapper*)(value))->wrapperValue), NULL_STRING_WRAPPER);
      }
      else if (key == KWD_CLASSES_CL_NATIVE_TYPE) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_CL_NATIVE_TYPE, wrapString(((StringWrapper*)(value))->wrapperValue), NULL_STRING_WRAPPER);
      }
      else if (key == KWD_CLASSES_CPP_NATIVE_TYPE) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_CPP_NATIVE_TYPE, wrapString(((StringWrapper*)(value))->wrapperValue), NULL_STRING_WRAPPER);
      }
      else if (key == KWD_CLASSES_IDL_NATIVE_TYPE) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_IDL_NATIVE_TYPE, wrapString(((StringWrapper*)(value))->wrapperValue), NULL_STRING_WRAPPER);
      }
      else if (key == KWD_CLASSES_JAVA_NATIVE_TYPE) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_JAVA_NATIVE_TYPE, wrapString(((StringWrapper*)(value))->wrapperValue), NULL_STRING_WRAPPER);
      }
      else if (key == KWD_CLASSES_PUBLICp) {
        clasS->classPublicP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
      }
      else if (key == KWD_CLASSES_ABSTRACTp) {
        clasS->abstractP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
      }
      else if (key == KWD_CLASSES_ACTIVEp) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_STORED_ACTIVEp, ((BooleanWrapper*)(value)), NULL);
      }
      else if (key == KWD_CLASSES_CL_STRUCTp) {
        clasS->clStructP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
      }
      else if (key == KWD_CLASSES_MIXINp) {
        clasS->mixinP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
        if (clasS->mixinP) {
          clasS->abstractP = true;
        }
      }
      else if (key == KWD_CLASSES_RECYCLE_METHOD) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_RECYCLE_METHOD, ((Keyword*)(value)), NULL);
      }
      else if (key == KWD_CLASSES_EXTENSION) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_EXTENSION_NAME, ((Symbol*)(value)), NULL);
      }
      else if (key == KWD_CLASSES_CREATOR) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_CREATOR, ((Symbol*)(value)), NULL);
      }
      else if (key == KWD_CLASSES_INITIALIZER) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_INITIALIZER, ((Symbol*)(value)), NULL);
      }
      else if (key == KWD_CLASSES_TERMINATOR) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_TERMINATOR, ((Symbol*)(value)), NULL);
      }
      else if (key == KWD_CLASSES_DESTRUCTOR) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_DESTRUCTOR, ((Symbol*)(value)), NULL);
      }
      else if (key == KWD_CLASSES_INITIAL_VALUE) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_INITIAL_VALUE, value, NULL);
      }
      else if (key == KWD_CLASSES_PRINT_FORM) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_PRINT_FORM, value, NULL);
      }
      else if (key == KWD_CLASSES_EQUALITY_TEST) {
      }
      else if (key == KWD_CLASSES_KEY) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_KEY, newList(), NULL);
        { Object* slotname = NULL;
          Cons* iter001 = ((Cons*)(value));
          List* into000 = clasS->classKey_reader();
          Cons* collect000 = NULL;

          for  (; !(iter001 == NIL); 
                iter001 = iter001->rest) {
            slotname = iter001->value;
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(slotname, NIL);
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
                collect000->rest = cons(slotname, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
      }
      else if (key == KWD_CLASSES_PARAMETERS) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_PARAMETERS, newList(), NULL);
        { Slot* slot = NULL;
          Cons* iter002 = ((List*)(value))->theConsList;
          List* into001 = clasS->classParameters_reader();
          Cons* collect001 = NULL;

          for  (; !(iter002 == NIL); 
                iter002 = iter002->rest) {
            slot = ((Slot*)(iter002->value));
            if (!((boolean)(collect001))) {
              {
                collect001 = cons(slot->slotName, NIL);
                if (into001->theConsList == NIL) {
                  into001->theConsList = collect001;
                }
                else {
                  addConsToEndOfConsList(into001->theConsList, collect001);
                }
              }
            }
            else {
              {
                collect001->rest = cons(slot->slotName, NIL);
                collect001 = collect001->rest;
              }
            }
          }
        }
      }
      else if (key == KWD_CLASSES_SYNONYMS) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_SYNONYMS, newList(), NULL);
        { Surrogate* type = NULL;
          Cons* iter003 = ((Cons*)(value));
          List* into002 = clasS->classSynonyms_reader();
          Cons* collect002 = NULL;

          for  (; !(iter003 == NIL); 
                iter003 = iter003->rest) {
            type = ((Surrogate*)(iter003->value));
            if (!((boolean)(collect002))) {
              {
                collect002 = cons(type, NIL);
                if (into002->theConsList == NIL) {
                  into002->theConsList = collect002;
                }
                else {
                  addConsToEndOfConsList(into002->theConsList, collect002);
                }
              }
            }
            else {
              {
                collect002->rest = cons(type, NIL);
                collect002 = collect002->rest;
              }
            }
          }
        }
      }
      else if (key == KWD_CLASSES_PROPERTIES) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_PROPERTIES, ((List*)(value)), NULL);
      }
      else if (key == KWD_CLASSES_META_ATTRIBUTES) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_META_ATTRIBUTES, ((KeyValueList*)(value)), NULL);
      }
      else if (key == KWD_CLASSES_CHILDREN) {
        clasS->classDirectSubs = ((List*)(value));
        oCLASSES_WITH_UNRESOLVED_CHILDREN_REFERENCESo->push(clasS);
      }
      else {
        if (!(runOptionHandlerP(clasS, key, value))) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationWarning();
            if (!(suppressWarningsP())) {
              printErrorContext(">> WARNING: ", STANDARD_WARNING);
              *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Skipping invalid class option " << "`" << deUglifyParseTree(key) << "'" << std::endl << "in the definition of class " << "`" << classSymbol(clasS) << "'" << "." << std::endl;
            }
          }
        }
      }
    }
  }
}

boolean inlineMethodP(Slot* slot) {
  return ((!slot->slotExternalP) &&
      (isaP(slot, SGT_CLASSES_STELLA_METHOD_SLOT) &&
       (!((MethodSlot*)(slot))->methodFunctionP)));
}

void transferExternalSlotToNewClass(Slot* externalslot, Class* newclass) {
  { Slot* newclassslot = lookupLocalSlot(newclass, externalslot->slotName);

    if (!((boolean)(newclassslot))) {
      newclass->classLocalSlots->insert(externalslot);
    }
    else if (inlineMethodP(newclassslot) ||
        ((!(newclassslot->primaryType() == externalslot->primaryType())) ||
         false)) {
    }
    else {
      newclass->classLocalSlots->substitute(externalslot, newclassslot);
      newclassslot->free();
    }
  }
}

void transferDemonsFromOldclass(Class* oldclass, Class* newclass) {
  { Slot* newslot = NULL;

    { Slot* oldslot = NULL;
      Cons* iter000 = oldclass->classLocalSlots->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        oldslot = ((Slot*)(iter000->value));
        { 
          newslot = lookupLocalSlot(newclass, oldslot->slotName);
          if (((boolean)(newslot))) {
            if (subtypeOfStorageSlotP(safePrimaryType(oldslot))) {
              { Slot* oldslot000 = oldslot;
                StorageSlot* oldslot = ((StorageSlot*)(oldslot000));

                if (subtypeOfStorageSlotP(safePrimaryType(newslot))) {
                  { Slot* newslot000 = newslot;
                    StorageSlot* newslot = ((StorageSlot*)(newslot000));

                    setDynamicSlotValue(newslot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_GUARD_DEMONS, oldslot->slotGuardDemons_reader(), NULL);
                    setDynamicSlotValue(oldslot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_GUARD_DEMONS, NULL, NULL);
                    setDynamicSlotValue(newslot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_DEMONS, oldslot->slotDemons_reader(), NULL);
                    setDynamicSlotValue(oldslot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_DEMONS, NULL, NULL);
                  }
                }
                else {
                }
              }
            }
            else {
            }
          }
        }
      }
    }
  }
  setDynamicSlotValue(newclass->dynamicSlots, SYM_CLASSES_STELLA_CLASS_CONSTRUCTOR_DEMONS, oldclass->classConstructorDemons_reader(), NULL);
  setDynamicSlotValue(oldclass->dynamicSlots, SYM_CLASSES_STELLA_CLASS_CONSTRUCTOR_DEMONS, NULL, NULL);
  setDynamicSlotValue(newclass->dynamicSlots, SYM_CLASSES_STELLA_CLASS_GUARD_CONSTRUCTOR_DEMONS, oldclass->classGuardConstructorDemons_reader(), NULL);
  setDynamicSlotValue(oldclass->dynamicSlots, SYM_CLASSES_STELLA_CLASS_GUARD_CONSTRUCTOR_DEMONS, NULL, NULL);
  setDynamicSlotValue(newclass->dynamicSlots, SYM_CLASSES_STELLA_CLASS_DESTRUCTOR_DEMONS, oldclass->classDestructorDemons_reader(), NULL);
  setDynamicSlotValue(oldclass->dynamicSlots, SYM_CLASSES_STELLA_CLASS_DESTRUCTOR_DEMONS, NULL, NULL);
  setDynamicSlotValue(newclass->dynamicSlots, SYM_CLASSES_STELLA_CLASS_GUARD_DESTRUCTOR_DEMONS, oldclass->classGuardDestructorDemons_reader(), NULL);
  setDynamicSlotValue(oldclass->dynamicSlots, SYM_CLASSES_STELLA_CLASS_GUARD_DESTRUCTOR_DEMONS, NULL, NULL);
}

void undefineOldClass(Class* oldclass, Class* newclass) {
  { Cons* newsubs = copyConsList(newclass->classDirectSubs->theConsList);

    unfinalizeClassAndSubclasses(oldclass);
    forgetUnfinalizedClass(oldclass);
    { Surrogate* oldsub = NULL;
      Cons* iter000 = oldclass->classDirectSubs->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        oldsub = ((Surrogate*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(oldsub, NIL);
            if (newsubs == NIL) {
              newsubs = collect000;
            }
            else {
              addConsToEndOfConsList(newsubs, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(oldsub, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    newclass->classDirectSubs->clear();
    newclass->classDirectSubs->theConsList = newsubs->removeDuplicates();
    oldclass->classDirectSubs->clear();
  }
  { TaxonomyNode* taxonomynode = oldclass->classTaxonomyNode;

    { Surrogate* super = NULL;
      Cons* iter001 = oldclass->classDirectSupers->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        super = ((Surrogate*)(iter001->value));
        if (((boolean)(((Class*)(super->surrogateValue)))) &&
            (!newclass->classDirectSupers->memberP(super))) {
          unlinkTaxonomyNodes(oCLASS_TAXONOMY_GRAPHo, ((Class*)(super->surrogateValue))->classTaxonomyNode, taxonomynode);
        }
      }
    }
    newclass->classTaxonomyNode = taxonomynode;
    oldclass->classTaxonomyNode = NULL;
  }
  { Slot* oldslot = NULL;
    Cons* iter002 = oldclass->classLocalSlots->theConsList;

    for (; !(iter002 == NIL); iter002 = iter002->rest) {
      oldslot = ((Slot*)(iter002->value));
      if (oldslot->slotExternalP) {
        transferExternalSlotToNewClass(oldslot, newclass);
      }
    }
  }
  newclass->classConstructorCode = oldclass->classConstructorCode;
  transferDemonsFromOldclass(oldclass, newclass);
  runHooks(oREDEFINE_RELATION_HOOKSo, list(2, oldclass, newclass));
  oldclass->free();
}

void Class::destroyClass() {
  // Destroy the Stella class `self'.  
  // Unfinalize its subclasses (if it has any).
  { Class* self = this;

    if (self->deletedP()) {
      return;
    }
    if (self->classType->homeContext == oSTELLA_MODULEo) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't delete STELLA class " << "`" << className(self) << "'" << "." << std::endl;
      return;
    }
    unfinalizeClassAndSubclasses(self);
    self->unbindFromSurrogate();
    if (((boolean)(self->classTaxonomyNode))) {
      removeTaxonomyNode(oCLASS_TAXONOMY_GRAPHo, self->classTaxonomyNode);
    }
    self->deletedPSetter(true);
    self->free();
  }
}

void Surrogate::destroyClass() {
  { Surrogate* self = this;

    { Class* clasS = ((Class*)(self->surrogateValue));

      if (!((boolean)(clasS))) {
        std::cout << "Can't destroy non-existent class " << "`" << self << "'" << "." << std::endl;
      }
      else {
        clasS->destroyClass();
      }
    }
  }
}

void destroyClassAndSubclasses(Class* self) {
  // Destroy the Stella class `self' and all its subclasses.
  { Surrogate* subtype = NULL;
    Cons* iter000 = self->classDirectSubs->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      subtype = ((Surrogate*)(iter000->value));
      if (((boolean)(((Class*)(subtype->surrogateValue))))) {
        destroyClassAndSubclasses(((Class*)(subtype->surrogateValue)));
      }
    }
  }
  self->destroyClass();
}

boolean Relation::primitiveP() {
  // Return `true' if `self' is not a defined relation.
  { Relation* self = this;

    return (true);
  }
}

void insertPrimitiveSuper(Surrogate* newsuper, List* supers) {
  { boolean foundP000 = false;

    { Surrogate* sup = NULL;
      Cons* iter000 = supers->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        sup = ((Surrogate*)(iter000->value));
        if (subtypeOfP(newsuper, sup)) {
          foundP000 = true;
          break;
        }
      }
    }
    if (!(foundP000)) {
      { Surrogate* subsumedsuper = NULL;

        for (;;) {
          { 
            { Surrogate* value000 = NULL;

              { Surrogate* sup = NULL;
                Cons* iter001 = supers->theConsList;

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  sup = ((Surrogate*)(iter001->value));
                  if (subtypeOfP(sup, newsuper)) {
                    value000 = sup;
                    break;
                  }
                }
              }
              subsumedsuper = value000;
            }
            if (!(((boolean)(subsumedsuper)))) {
              break;
            }
          }
          supers = ((List*)(supers->remove(subsumedsuper)));
        }
        supers->insert(newsuper);
      }
    }
  }
}

void collectMostSpecificPrimitiveSupers(Class* clasS, List* supers) {
  { Surrogate* super = NULL;
    Cons* iter000 = clasS->classDirectSupers->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      super = ((Surrogate*)(iter000->value));
      if (typeToClass(super)->primitiveP()) {
        insertPrimitiveSuper(super, supers);
      }
      else {
        collectMostSpecificPrimitiveSupers(typeToClass(super), supers);
      }
    }
  }
}

List* mostSpecificPrimitiveSupers(Class* clasS) {
  { List* supers = newList();

    collectMostSpecificPrimitiveSupers(clasS, supers);
    return (supers->reverse());
  }
}

List* classNativeSupers(Class* clasS) {
  { boolean alwaysP000 = true;

    { Surrogate* super = NULL;
      Cons* iter000 = clasS->classDirectSupers->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        super = ((Surrogate*)(iter000->value));
        if (!typeToClass(super)->primitiveP()) {
          alwaysP000 = false;
          break;
        }
      }
    }
    if (alwaysP000) {
      return (clasS->classDirectSupers);
    }
    else {
      return (mostSpecificPrimitiveSupers(clasS));
    }
  }
}

// List of classes whose class or slot inheritance is
// currently unfinalized.
List* oUNFINALIZED_CLASSESo = NULL;

// Set to `true' by `remember-unfinalized-class'; set
// to `false' by `cleanup-unfinalized-classes'.  Minimizes the time that
// `finalize-classes' spends searching for classes to finalize.
boolean oNEWLY_UNFINALIZED_CLASSESpo = false;

// List of classes defined with a :children option
// which still have some of their children references unresolved.
List* oCLASSES_WITH_UNRESOLVED_CHILDREN_REFERENCESo = NULL;

void rememberUnfinalizedClass(Class* clasS, boolean forceP) {
  if (forceP ||
      (clasS->classFinalizedP &&
       clasS->classSlotsFinalizedP)) {
    oUNFINALIZED_CLASSESo->push(clasS);
    oNEWLY_UNFINALIZED_CLASSESpo = true;
  }
}

void forgetUnfinalizedClass(Class* clasS) {
  if (!(clasS->classFinalizedP &&
      clasS->classSlotsFinalizedP)) {
    oUNFINALIZED_CLASSESo->remove(clasS);
  }
}

void finalizeClasses() {
  // Finalize all currently unfinalized classes.
  if (!oNEWLY_UNFINALIZED_CLASSESpo) {
    return;
  }
  { boolean hierarchymighthavechangedP = false;

    oUNFINALIZED_CLASSESo->removeDeletedMembers();
    resolveChildrenReferences();
    { Class* clasS = NULL;
      Cons* iter000 = oUNFINALIZED_CLASSESo->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        clasS = ((Class*)(iter000->value));
        if ((!clasS->classFinalizedP) &&
            (!coerceWrappedBooleanToBoolean(clasS->badP_reader()))) {
          finalizeClass(clasS);
          hierarchymighthavechangedP = true;
        }
      }
    }
    if (hierarchymighthavechangedP) {
      finalizeTaxonomyGraph(oCLASS_TAXONOMY_GRAPHo);
    }
  }
}

void resolveChildrenReferences() {
  if (oCLASSES_WITH_UNRESOLVED_CHILDREN_REFERENCESo->emptyP() ||
      oUNFINALIZED_CLASSESo->emptyP()) {
    return;
  }
  { Cons* unresolvableclasses = NIL;

    oCLASSES_WITH_UNRESOLVED_CHILDREN_REFERENCESo->removeDeletedMembers();
    { Class* clasS = NULL;
      Cons* iter000 = oCLASSES_WITH_UNRESOLVED_CHILDREN_REFERENCESo->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        clasS = ((Class*)(iter000->value));
        addDirectSubsBackLinks(clasS);
        { boolean foundP000 = false;

          { Surrogate* sub = NULL;
            Cons* iter001 = clasS->classDirectSubs->theConsList;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              sub = ((Surrogate*)(iter001->value));
              if (!((boolean)(typeToClass(sub)))) {
                foundP000 = true;
                break;
              }
            }
          }
          if (foundP000) {
            unresolvableclasses = cons(clasS, unresolvableclasses);
          }
        }
      }
    }
    oCLASSES_WITH_UNRESOLVED_CHILDREN_REFERENCESo->clear();
    oCLASSES_WITH_UNRESOLVED_CHILDREN_REFERENCESo->theConsList = unresolvableclasses;
  }
}

void finalizeSlots() {
  // Finalize all currently unfinalized slots.
  if (!oNEWLY_UNFINALIZED_CLASSESpo) {
    return;
  }
  { Class* clasS = NULL;
    Cons* iter000 = oUNFINALIZED_CLASSESo->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      clasS = ((Class*)(iter000->value));
      if (clasS->classFinalizedP &&
          ((!clasS->classSlotsFinalizedP) &&
           (!coerceWrappedBooleanToBoolean(clasS->badP_reader())))) {
        finalizeClassSlots(clasS);
      }
    }
  }
}

void cleanupUnfinalizedClasses() {
  // Remove all finalized classes from `*UNFINALIZED-CLASSES*',
  // and set `*NEWLY-UNFINALIZED-CLASSES?*' to `false'.
  { Cons* unfinalizedclasses = NIL;

    { Class* clasS = NULL;
      Cons* iter000 = oUNFINALIZED_CLASSESo->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        clasS = ((Class*)(iter000->value));
        if ((!clasS->classFinalizedP) ||
            (!clasS->classSlotsFinalizedP)) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(clasS, NIL);
              if (unfinalizedclasses == NIL) {
                unfinalizedclasses = collect000;
              }
              else {
                addConsToEndOfConsList(unfinalizedclasses, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(clasS, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    oUNFINALIZED_CLASSESo->clear();
    oUNFINALIZED_CLASSESo->theConsList = unfinalizedclasses;
    oNEWLY_UNFINALIZED_CLASSESpo = false;
  }
}

void finalizeClassesAndSlots() {
  // Finalize all currently unfinalized classes and slots.
  finalizeClasses();
  finalizeSlots();
  cleanupUnfinalizedClasses();
}

void activateClass(Class* clasS) {
  { Class* activeobjectclass = typeToClass(SGT_CLASSES_STELLA_ACTIVE_OBJECT);
    List* supers = clasS->classDirectSupers;

    if (((boolean)(activeobjectclass)) &&
        subclassOfP(clasS, activeobjectclass)) {
      return;
    }
    if (supers->length() == 0) {
      supers->insert(SGT_CLASSES_STELLA_ACTIVE_OBJECT);
    }
    else if ((supers->length() == 1) &&
        ((((Surrogate*)(supers->first())) == SGT_CLASSES_STELLA_OBJECT) ||
         (((Surrogate*)(supers->first())) == SGT_CLASSES_STELLA_STANDARD_OBJECT))) {
      removeDirectSupersBackLinks(clasS);
      supers->clear();
      supers->insert(SGT_CLASSES_STELLA_ACTIVE_OBJECT);
    }
    else {
      setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_STORED_ACTIVEp, FALSE_WRAPPER, NULL);
      if (((boolean)(((Symbol*)(dynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_EXTENSION_NAME, NULL)))))) {
        setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_EXTENSION_NAME, NULL, NULL);
      }
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Cannot convert " << "`" << clasS << "'" << " into an ACTIVE-OBJECT." << std::endl << "You have to modify its superclasses by hand." << std::endl;
      return;
    }
    addDirectSupersBackLinks(clasS);
    inheritSuperclasses(clasS);
  }
}

void addPrimaryType(Class* clasS) {
  { Surrogate* classtype = clasS->classType;
    Cons* slottree = NULL;

    { boolean testValue000 = false;

      testValue000 = !clasS->abstractP;
      if (testValue000) {
        testValue000 = subtypeOfP(classtype, SGT_CLASSES_STELLA_OBJECT);
        if (testValue000) {
          { boolean foundP000 = false;

            { Slot* slot = NULL;
              Cons* iter000 = clasS->classLocalSlots->theConsList;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                slot = ((Slot*)(iter000->value));
                if (slot->slotName == SYM_CLASSES_STELLA_PRIMARY_TYPE) {
                  foundP000 = true;
                  break;
                }
              }
            }
            testValue000 = foundP000;
          }
          testValue000 = !testValue000;
        }
      }
      if (testValue000) {
        slottree = listO(7, cons(listO(3, SYM_CLASSES_STELLA_SELF, internSymbolInModule(classtype->symbolName, ((Module*)(classtype->homeContext)), true), NIL), NIL), KWD_CLASSES_TYPE, SYM_CLASSES_STELLA_TYPE, KWD_CLASSES_AUXILIARYp, SYM_CLASSES_STELLA_TRUE, listO(3, SYM_CLASSES_STELLA_RETURN, classtype, NIL), NIL);
        clasS->classLocalSlots->push(defineInlineMethod(SYM_CLASSES_STELLA_PRIMARY_TYPE, slottree));
      }
    }
  }
}

void finalizeOneClass(Class* clasS) {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, clasS->homeModule());
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (((boolean)(((Symbol*)(dynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_EXTENSION_NAME, NULL)))))) {
      setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_STORED_ACTIVEp, TRUE_WRAPPER, NULL);
    }
    addDirectSupersBackLinks(clasS);
    inheritSuperclasses(clasS);
    if (((boolean)(((BooleanWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_STORED_ACTIVEp, NULL))))) &&
        coerceWrappedBooleanToBoolean(((BooleanWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_STORED_ACTIVEp, NULL))))) {
      activateClass(clasS);
    }
    addPrimaryType(clasS);
    { Surrogate* alias = NULL;
      Cons* iter000 = clasS->classSynonyms_reader()->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        alias = ((Surrogate*)(iter000->value));
        if (((boolean)(((Class*)(alias->surrogateValue)))) &&
            ((!(((Class*)(alias->surrogateValue)) == clasS)) &&
             (!stringEqlP(className(((Class*)(alias->surrogateValue))), className(clasS))))) {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "Alias " << "`" << internSymbolInModule(alias->symbolName, ((Module*)(alias->homeContext)), true) << "'" << " can't point to " << "`" << classSymbol(clasS) << "'" << " because it already points to " << std::endl << "the class " << "`" << classSymbol(((Class*)(alias->surrogateValue))) << "'" << "." << std::endl;
        }
        else {
          alias->surrogateValue = clasS;
        }
      }
    }
    if (((boolean)(((Symbol*)(dynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_EXTENSION_NAME, NULL))))) &&
        (!((boolean)(((ClassExtension*)(dynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_EXTENSION, NULL))))))) {
      setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_EXTENSION, newClassExtension(), NULL);
    }
    runHooks(oFINALIZE_RELATION_HOOKSo, clasS);
    clasS->classFinalizedP = true;
  }
}

boolean finalizeClass(Class* clasS) {
  return (helpFinalizeClass(clasS, NULL));
}

boolean helpFinalizeClass(Class* clasS, Surrogate* finalizedparent) {
  if (clasS->classFinalizedP) {
    return (true);
  }
  setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_BADp, TRUE_WRAPPER, NULL);
  { Surrogate* super = NULL;
    Cons* iter000 = clasS->classDirectSupers->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      super = ((Surrogate*)(iter000->value));
      if (!(super == finalizedparent)) {
        { Class* superclass = typeToClass(super);

          if (((boolean)(superclass))) {
            if (!(helpFinalizeClass(superclass, NULL))) {
              return (false);
            }
          }
          else {
            return (false);
          }
        }
      }
    }
  }
  if (clasS->classFinalizedP) {
    setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_BADp, NULL, NULL);
    return (true);
  }
  finalizeOneClass(clasS);
  { Surrogate* sub = NULL;
    Cons* iter001 = clasS->classDirectSubs->theConsList;

    for (; !(iter001 == NIL); iter001 = iter001->rest) {
      sub = ((Surrogate*)(iter001->value));
      { Class* subclass = typeToClass(sub);

        if (((boolean)(subclass))) {
          helpFinalizeClass(subclass, clasS->classType);
        }
      }
    }
  }
  setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_BADp, NULL, NULL);
  return (true);
}

void unfinalizeClassAndSubclasses(Class* clasS) {
  if (!clasS->classFinalizedP) {
    return;
  }
  removeDirectSupersBackLinks(clasS);
  { List* subs = clasS->classDirectSubs->copy();

    { Surrogate* subtype = NULL;
      Cons* iter000 = subs->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        subtype = ((Surrogate*)(iter000->value));
        if (((boolean)(((Class*)(subtype->surrogateValue))))) {
          unfinalizeClassAndSubclasses(((Class*)(subtype->surrogateValue)));
        }
      }
    }
    subs->free();
  }
  { Surrogate* alias = NULL;
    Cons* iter001 = clasS->classSynonyms_reader()->theConsList;

    for (; !(iter001 == NIL); iter001 = iter001->rest) {
      alias = ((Surrogate*)(iter001->value));
      if (((Class*)(alias->surrogateValue)) == clasS) {
        alias->surrogateValue = NULL;
      }
    }
  }
  uninheritSuperclasses(clasS);
  unfinalizeClassSlots(clasS);
  rememberUnfinalizedClass(clasS, false);
  clasS->classFinalizedP = false;
}

Slot* attachSlotToOwner(Slot* newslot) {
  { Symbol* name = newslot->slotName;
    Class* ownerclass = ((Class*)(newslot->slotOwner->surrogateValue));
    Slot* oldslot = lookupLocalSlot(ownerclass, name);

    newslot->slotExternalP = true;
    registerSlotName(newslot);
    if (!((boolean)(oldslot))) {
      ownerclass->classLocalSlots->insert(newslot);
      unfinalizeClassSlots(ownerclass);
      return (newslot);
    }
    else if (!localSlotP(oldslot, ownerclass)) {
      ownerclass->classLocalSlots->insert(newslot);
      unfinalizeClassSlots(ownerclass);
      return (newslot);
    }
    else if (!(newslot->primaryType() == oldslot->primaryType())) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't define a " << "`" << newslot->primaryType() << "'" << " named " << "`" << name << "'" << " on the class " << "`" << className(ownerclass) << "'" << std::endl << "because it already has a " << "`" << oldslot->primaryType() << "'" << " with the same name." << std::endl;
      return (NULL);
    }
    else {
      ownerclass->classLocalSlots->substitute(newslot, oldslot);
      runHooks(oREDEFINE_RELATION_HOOKSo, list(2, oldslot, newslot));
      oldslot->free();
      helpUnfinalizeClassSlots(ownerclass);
      return (newslot);
    }
  }
}

void computeSlotDirectEquivalent(Slot* self) {
  { Class* clasS = ((Class*)(self->slotOwner->surrogateValue));
    Symbol* slotname = self->slotName;
    Symbol* slotrenames = ((Symbol*)(dynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_RENAMES, NULL)));
    Slot* renamesslot = NULL;

    if (((boolean)(slotrenames))) {
      { Slot* value000 = NULL;

        { Slot* s = NULL;
          Iterator* iter000 = clasS->classSlots();

          for (; iter000->nextP(); ) {
            s = ((Slot*)(iter000->value));
            if (s->slotName == slotrenames) {
              value000 = s;
              break;
            }
          }
        }
        renamesslot = value000;
      }
      if (((boolean)(renamesslot))) {
        self->slotDirectEquivalent = renamesslot;
        renamesslot->slotRenamedP = true;
      }
      else {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "Slot " << "`" << slotname << "'" << " renames a non-existent self: " << "`" << slotrenames << "'" << "." << std::endl << "Cancelling the renames option." << std::endl;
        setDynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_RENAMES, NULL, NULL);
      }
    }
    else {
      { Slot* value001 = NULL;

        { Slot* s = NULL;
          Iterator* iter001 = clasS->classSlots();

          for (; iter001->nextP(); ) {
            s = ((Slot*)(iter001->value));
            if ((!(s == self)) &&
                (s->slotName == slotname)) {
              value001 = s;
              break;
            }
          }
        }
        self->slotDirectEquivalent = value001;
      }
    }
  }
}

void checkConformanceOfSlotSignature(Slot* self) {
  { Slot* equivalentslot = self->slotDirectEquivalent;

    if (((boolean)(equivalentslot)) &&
        (!self->conformingSignaturesP(equivalentslot))) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "The signature of slot " << "`" << self << "'" << " does not conform to the" << std::endl << "   signature of the inherited slot " << "`" << equivalentslot << "'" << std::endl;
    }
  }
}

Surrogate* collectionToActiveCollection(Surrogate* type) {
  if ((type == SGT_CLASSES_STELLA_SET) ||
      (type == SGT_CLASSES_STELLA_ACTIVE_SET)) {
    return (SGT_CLASSES_STELLA_ACTIVE_SET);
  }
  else if ((type == SGT_CLASSES_STELLA_LIST) ||
      (type == SGT_CLASSES_STELLA_ACTIVE_LIST)) {
    return (SGT_CLASSES_STELLA_ACTIVE_LIST);
  }
  else {
    return (NULL);
  }
}

void activateSlot(StorageSlot* self) {
  if (self->collectionValuedP()) {
    { Surrogate* activecollection = collectionToActiveCollection(self->slotBaseType);

      if (!((boolean)(activecollection))) {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "No active collection defined for " << "`" << self->slotBaseType << "'" << "." << std::endl << "   Cannot activate slot " << "`" << self << "'" << "." << std::endl;
        setDynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_STORED_ACTIVEp, FALSE_WRAPPER, NULL);
        return;
      }
      self->slotBaseType = collectionToActiveCollection(self->slotBaseType);
    }
  }
  setDynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_STORED_ACTIVEp, TRUE_WRAPPER, NULL);
}

void Slot::finalizeSlotTypeComputations() {
  { Slot* self = this;

  }
}

void StorageSlot::finalizeSlotTypeComputations() {
  { StorageSlot* self = this;

    if (((boolean)(((CompoundTypeSpecifier*)(dynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_TYPE_SPECIFIER, NULL)))))) {
      self->slotBaseType = validateTypeSpecifier(((CompoundTypeSpecifier*)(dynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_TYPE_SPECIFIER, NULL))), ((Class*)(self->slotOwner->surrogateValue)), false);
    }
    if (!((boolean)(self->slotBaseType))) {
      self->slotBaseType = self->type();
    }
    if (!((boolean)(self->slotBaseType))) {
      if (!self->abstractP) {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "Missing type specification for the slot " << "`" << self << "'" << std::endl;
      }
      self->slotBaseType = SGT_CLASSES_STELLA_UNKNOWN;
      return;
    }
    if (self->activeP()) {
      activateSlot(self);
    }
  }
}

boolean multiValuedSlotWithDuplicatesP(Slot* self) {
  return (subtypeOfP(self->type(), SGT_CLASSES_STELLA_COLLECTION) &&
      (!subtypeOfP(self->type(), SGT_CLASSES_STELLA_SET_MIXIN)));
}

void computeSlotInverses(Slot* self) {
  if (!((boolean)(((Symbol*)(dynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_INVERSE, NULL)))))) {
    return;
  }
  if (multiValuedSlotWithDuplicatesP(self)) {
    *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't define an inverse on slot " << "`" << self << "'" << " because it allows duplicate values." << std::endl;
    setDynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_INVERSE, NULL, NULL);
    return;
  }
  { Class* inverseclass = ((Class*)(self->type()->surrogateValue));
    Slot* inverseslot = lookupSlot(inverseclass, ((Symbol*)(dynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_INVERSE, NULL))));

    if (((boolean)(inverseslot))) {
      if (multiValuedSlotWithDuplicatesP(inverseslot)) {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't define an inverse on slot " << "`" << inverseslot << "'" << " because it allows duplicate values." << std::endl;
        setDynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_INVERSE, NULL, NULL);
        setDynamicSlotValue(inverseslot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_INVERSE, NULL, NULL);
        return;
      }
      if (!inverseslot->activeP()) {
        setDynamicSlotValue(inverseslot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_INVERSE, self->slotName, NULL);
        inverseslot->finalizeSlotTypeComputations();
      }
      setDynamicSlotValue(inverseslot->dynamicSlots, SYM_CLASSES_STELLA_INVERSE, self, NULL);
      attachInverseSlotDemon(self);
      setDynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_INVERSE, inverseslot, NULL);
      attachInverseSlotDemon(inverseslot);
      return;
    }
    if (!((boolean)(inverseclass))) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't finalize inverse slot computation for slot " << "`" << self << "'" << std::endl << " because the class " << "`" << self->type() << "'" << " is not defined." << std::endl;
    }
    else {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't finalize inverse slot computation for slot " << "`" << self << "'" << std::endl << " because the inverse slot " << "`" << ((Symbol*)(dynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_INVERSE, NULL))) << "'" << " does not exist." << std::endl;
    }
  }
}

void Slot::helpFinalizeLocalSlot() {
  { Slot* self = this;

  }
}

void StorageSlot::helpFinalizeLocalSlot() {
  { StorageSlot* self = this;

    { Class* owner = ((Class*)(self->slotOwner->surrogateValue));

      if ((self->allocation() == KWD_CLASSES_DYNAMIC) &&
          ((!subtypeOfP(owner->classType, SGT_CLASSES_STELLA_DYNAMIC_SLOTS_MIXIN)) &&
           (!owner->abstractP))) {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "Slot " << "`" << self->slotName << "'" << " on the class " << "`" << classSymbol(owner) << "'" << std::endl << "   can't have :dynamic slot allocation because the class doesn't" << std::endl << "   inherit the class `DYNAMIC-SLOTS-MIXIN'.  Resetting the" << std::endl << "   allocation to ':instance'." << std::endl;
        setDynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_ALLOCATION, KWD_CLASSES_INSTANCE, NULL);
      }
      if (((boolean)(((Symbol*)(dynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_RENAMES, NULL)))))) {
        { StorageSlot* renamesslot = ((StorageSlot*)(lookupSlot(owner, ((Symbol*)(dynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_RENAMES, NULL))))));

          if (!(self->primaryType() == renamesslot->primaryType())) {
            *(STANDARD_WARNING->nativeStream) << "Warning: " << "Slot " << "`" << self->slotName << "'" << " renames a slot of a different kind" << std::endl << "   (e.g., a storage slot renaming a method slot, or vice-versa)." << std::endl << "  Cancelling the renames option." << std::endl;
            setDynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_RENAMES, NULL, NULL);
          }
          else if (!(self->allocation() == renamesslot->allocation())) {
            *(STANDARD_WARNING->nativeStream) << "Warning: " << "Slot " << "`" << self->slotName << "'" << " renames a slot with a different" << std::endl << "   allocation.  Changing its allocation to " << "`" << renamesslot->allocation() << "'" << "." << std::endl;
            setDynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_ALLOCATION, renamesslot->allocation(), NULL);
          }
        }
      }
      if (self->slotContextSensitiveP &&
          ((!subtypeOfP(self->slotOwner, SGT_CLASSES_STELLA_CONTEXT_SENSITIVE_OBJECT)) &&
           (!subtypeOfP(owner->classType, SGT_CLASSES_STELLA_CONTEXT_SENSITIVE_MIXIN)))) {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Class " << "`" << self->slotOwner->symbolName << "'" << " must inherit either the " << "class CONTEXT-SENSITIVE-OBJECT" << std::endl << "   or the class CONTEXT-SENSITIVE-MIXIN because it contains the" << std::endl << "   context sensitive slot " << "`" << self->slotName << "'" << " " << std::endl;
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

void finalizeLocalSlot(Slot* self) {
  computeSlotDirectEquivalent(self);
  self->finalizeSlotTypeComputations();
  checkConformanceOfSlotSignature(self);
  computeSlotInverses(self);
  self->helpFinalizeLocalSlot();
  runHooks(oFINALIZE_RELATION_HOOKSo, self);
}

void Slot::unfinalizeLocalSlot() {
  { Slot* self = this;

  }
}

void StorageSlot::unfinalizeLocalSlot() {
  { StorageSlot* self = this;

  }
}

void finalizeClassSlots(Class* clasS) {
  setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_BADp, TRUE_WRAPPER, NULL);
  { Surrogate* super = NULL;
    Cons* iter000 = clasS->classDirectSupers->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      super = ((Surrogate*)(iter000->value));
      if (!((Class*)(super->surrogateValue))->classSlotsFinalizedP) {
        finalizeClassSlots(((Class*)(super->surrogateValue)));
      }
    }
  }
  computeRequiredSlotNames(clasS);
  { Surrogate* classtype = clasS->classType;

    { Slot* slot = NULL;
      Cons* iter001 = clasS->classLocalSlots->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        slot = ((Slot*)(iter001->value));
        registerSlotName(slot);
        slot->slotOwner = classtype;
      }
    }
  }
  { Slot* slot = NULL;
    Cons* iter002 = clasS->classLocalSlots->theConsList;

    for (; !(iter002 == NIL); iter002 = iter002->rest) {
      slot = ((Slot*)(iter002->value));
      finalizeLocalSlot(slot);
    }
  }
  clasS->classSlotsFinalizedP = true;
  setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_BADp, NULL, NULL);
}

void unfinalizeClassSlots(Class* clasS) {
  if (!clasS->classSlotsFinalizedP) {
    clearSlotAndMethodCache(clasS);
    return;
  }
  { Surrogate* subtype = NULL;
    Cons* iter000 = clasS->classDirectSubs->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      subtype = ((Surrogate*)(iter000->value));
      if (((boolean)(((Class*)(subtype->surrogateValue))))) {
        unfinalizeClassSlots(((Class*)(subtype->surrogateValue)));
      }
    }
  }
  helpUnfinalizeClassSlots(clasS);
}

void helpUnfinalizeClassSlots(Class* clasS) {
  clearSlotAndMethodCache(clasS);
  if (!clasS->classSlotsFinalizedP) {
    return;
  }
  freeRequiredSlotNames(clasS);
  { Slot* slot = NULL;
    Cons* iter000 = clasS->localSlots()->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      slot = ((Slot*)(iter000->value));
      slot->unfinalizeLocalSlot();
    }
  }
  rememberUnfinalizedClass(clasS, false);
  clasS->classSlotsFinalizedP = false;
}

boolean Class::multipleParentsP() {
  // Return `true' if `class' has more than one direct superclass.
  { Class* clasS = this;

    return (!(clasS->classDirectSupers->rest() == NIL));
  }
}

void addDirectSupersBackLinks(Class* clasS) {
  { List* directsupers = clasS->classDirectSupers;
    Surrogate* classtype = clasS->classType;

    directsupers->removeDuplicates();
    { Surrogate* supertype = NULL;
      Cons* iter000 = directsupers->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        supertype = ((Surrogate*)(iter000->value));
        if (((boolean)(((Class*)(supertype->surrogateValue))))) {
          { Class* superclass = ((Class*)(supertype->surrogateValue));

            superclass->classDirectSubs->insertNew(classtype);
            linkTaxonomyNodes(oCLASS_TAXONOMY_GRAPHo, ((Class*)(supertype->surrogateValue))->classTaxonomyNode, clasS->classTaxonomyNode);
          }
        }
      }
    }
  }
}

void addDirectSubsBackLinks(Class* clasS) {
  { List* directsubs = clasS->classDirectSubs;
    Surrogate* classtype = clasS->classType;

    directsubs->removeDuplicates();
    { Surrogate* subtype = NULL;
      Cons* iter000 = directsubs->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        subtype = ((Surrogate*)(iter000->value));
        if (((boolean)(((Class*)(subtype->surrogateValue))))) {
          { Class* subclass = ((Class*)(subtype->surrogateValue));

            if (subclass->classFinalizedP) {
              if (!(subclass->classAllSuperClasses->memberP(clasS))) {
                subclass->classDirectSupers->insert(classtype);
                unfinalizeClassAndSubclasses(clasS);
              }
            }
            else {
              subclass->classDirectSupers->insertNew(classtype);
            }
          }
        }
      }
    }
  }
}

void removeDirectSupersBackLinks(Class* clasS) {
  { Surrogate* classtype = clasS->classType;

    { Surrogate* supertype = NULL;
      Cons* iter000 = clasS->classDirectSupers->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        supertype = ((Surrogate*)(iter000->value));
        if (((boolean)(((Class*)(supertype->surrogateValue))))) {
          ((Class*)(supertype->surrogateValue))->classDirectSubs->remove(classtype);
        }
      }
    }
  }
}

void collectDirectSuperClasses(Class* clasS, List* parents) {
  { List* directsupertypes = clasS->classDirectSupers;
    List* nondirectparents = newList();

    { Surrogate* supertype = NULL;
      Cons* iter000 = directsupertypes->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        supertype = ((Surrogate*)(iter000->value));
        if (((boolean)(((Class*)(supertype->surrogateValue))))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(((Class*)(supertype->surrogateValue)), NIL);
              if (parents->theConsList == NIL) {
                parents->theConsList = collect000;
              }
              else {
                addConsToEndOfConsList(parents->theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(((Class*)(supertype->surrogateValue)), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    { Class* superclass = NULL;
      Cons* iter001 = parents->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        superclass = ((Class*)(iter001->value));
        { Class* othersuperclass = NULL;
          Cons* iter002 = parents->theConsList;

          for (; !(iter002 == NIL); iter002 = iter002->rest) {
            othersuperclass = ((Class*)(iter002->value));
            if (!(othersuperclass == superclass)) {
              if (superclass->classAllSuperClasses->memberP(othersuperclass)) {
                nondirectparents->insert(othersuperclass);
              }
            }
          }
        }
      }
    }
    { Class* p = NULL;
      Cons* iter003 = nondirectparents->theConsList;

      for (; !(iter003 == NIL); iter003 = iter003->rest) {
        p = ((Class*)(iter003->value));
        parents->remove(p);
      }
    }
    nondirectparents->free();
  }
}

void inheritSuperclasses(Class* clasS) {
  { List* parentclasses = newList();

    collectDirectSuperClasses(clasS, parentclasses);
    if (!clasS->multipleParentsP()) {
      { Class* onlyparent = ((Class*)(parentclasses->first()));

        if (!((boolean)(onlyparent))) {
          return;
        }
        clasS->classAllSuperClasses = cons(onlyparent, onlyparent->classAllSuperClasses);
        return;
      }
    }
    parentclasses = parentclasses->reverse();
    { Cons* allsuperclasses = NIL;
      Cons* sublist = NULL;

      { Class* parent = NULL;
        Cons* iter000 = parentclasses->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          parent = ((Class*)(iter000->value));
          sublist = NIL;
          { Class* ancestor = NULL;
            Cons* iter001 = parent->classAllSuperClasses;
            Cons* collect000 = NULL;

            for  (; !(iter001 == NIL); 
                  iter001 = iter001->rest) {
              ancestor = ((Class*)(iter001->value));
              if (!allsuperclasses->memberP(ancestor)) {
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(ancestor, NIL);
                    if (sublist == NIL) {
                      sublist = collect000;
                    }
                    else {
                      addConsToEndOfConsList(sublist, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000->rest = cons(ancestor, NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
          }
          sublist = cons(parent, sublist);
          allsuperclasses = sublist->concatenate(allsuperclasses, 0);
        }
      }
      clasS->classAllSuperClasses = allsuperclasses;
    }
  }
}

void uninheritSuperclasses(Class* clasS) {
  clasS->classAllSuperClasses = NIL;
}

Class* twoArgumentLeastCommonSuperclass(Class* class1, Class* class2) {
  // Return the most specific class that is a superclass of
  // both `class1' and `class2'.  If there is more than one, arbitrarily pick one.
  // If there is none, return `null'.
  if (subclassOfP(class1, class2)) {
    return (class2);
  }
  if (subclassOfP(class2, class1)) {
    return (class1);
  }
  { Class* c = NULL;
    Cons* iter000 = class1->classAllSuperClasses;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      c = ((Class*)(iter000->value));
      c->classMarkedP = false;
    }
  }
  { Class* c = NULL;
    Cons* iter001 = class2->classAllSuperClasses;

    for (; !(iter001 == NIL); iter001 = iter001->rest) {
      c = ((Class*)(iter001->value));
      c->classMarkedP = true;
    }
  }
  { Class* c = NULL;
    Cons* iter002 = class1->classAllSuperClasses;

    for (; !(iter002 == NIL); iter002 = iter002->rest) {
      c = ((Class*)(iter002->value));
      if (c->classMarkedP) {
        return (c);
      }
    }
  }
  return (NULL);
}

StandardObject* twoArgumentLeastCommonSupertype(StandardObject* type1, StandardObject* type2) {
  // Return the most specific type that is a supertype of
  // both `type1' and `type2'.  If there is more than one, arbitrarily pick one.
  // If there is none, return @VOID.  If one or both types are parametric,
  // also try to generalize parameter types if necessary.
  { boolean dummy1;

    if (type1 == type2) {
      return (type1);
    }
    { Surrogate* basetype1 = typeSpecToBaseType(type1);
      Surrogate* basetype2 = typeSpecToBaseType(type2);
      Class* superclass = twoArgumentLeastCommonSuperclass(((Class*)(basetype1->surrogateValue)), ((Class*)(basetype2->surrogateValue)));

      if (!((boolean)(superclass))) {
        return (SGT_CLASSES_STELLA_VOID);
      }
      if ((type1 == basetype1) &&
          (type2 == basetype2)) {
        return (superclass->classType);
      }
      { Surrogate* supertype = superclass->classType;
        StandardObject* supertypespec = baseTypeToTypeSpec(supertype);
        List* parameters = superclass->parameters();
        List* parametertypes = NULL;
        StandardObject* sptype = NULL;
        StandardObject* ptype1 = NULL;
        StandardObject* ptype2 = NULL;
        boolean parameterexistsP = false;
        ParametricTypeSpecifier* result = NULL;

        if (parameters->emptyP()) {
          return (supertype);
        }
        parametertypes = newList();
        { Symbol* parameter = NULL;
          Cons* iter000 = parameters->theConsList;
          Cons* collect000 = NULL;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest) {
            parameter = ((Symbol*)(iter000->value));
            ptype1 = extractParameterType(type1, parameter, parameterexistsP);
            if ((!parameterexistsP) ||
                unknownTypeP(typeSpecToBaseType(ptype1))) {
              return (supertype);
            }
            ptype2 = extractParameterType(type2, parameter, parameterexistsP);
            if ((!parameterexistsP) ||
                unknownTypeP(typeSpecToBaseType(ptype2))) {
              return (supertype);
            }
            sptype = twoArgumentLeastCommonSupertype(ptype1, ptype2);
            if ((!(supertype == supertypespec)) &&
                (!subTypeSpecOfP(sptype, extractParameterType(supertype, parameter, dummy1)))) {
              return (supertype);
            }
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(sptype, NIL);
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
                collect000->rest = cons(sptype, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        { ParametricTypeSpecifier* self001 = newParametricTypeSpecifier();

          self001->specifierBaseType = supertype;
          self001->specifierParameterTypes = parametertypes;
          result = self001;
        }
        if (arrayTypeSpecifierP(type1) &&
            arrayTypeSpecifierP(type2)) {
          if (!equalConsTreesP(arrayTypeDimensions(((ParametricTypeSpecifier*)(type1)))->theConsList, arrayTypeDimensions(((ParametricTypeSpecifier*)(type2)))->theConsList)) {
            return (supertype);
          }
          result->specifierDimensions = ((ParametricTypeSpecifier*)(type1))->specifierDimensions;
        }
        return (result);
      }
    }
  }
}

void inheritSlots(Class* clasS) {
  { Cons* slots = copyConsList(clasS->classLocalSlots->theConsList);

    if (clasS->classDirectSupers->emptyP()) {
    }
    else if (clasS->multipleParentsP()) {
      { Surrogate* supertype = NULL;
        Cons* iter000 = clasS->classDirectSupers->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          supertype = ((Surrogate*)(iter000->value));
          slots = slots->concatenate(copyConsList(((Class*)(supertype->surrogateValue))->classAllSlots), 0);
        }
      }
      slots = slots->reverse();
      slots->removeDuplicates();
      slots = slots->reverse();
    }
    else {
      { Cons* parentslots = ((Class*)(((Surrogate*)(clasS->classDirectSupers->first()))->surrogateValue))->classAllSlots;

        slots = slots->concatenate(parentslots, 0);
      }
    }
    clasS->classAllSlots = slots;
  }
}

boolean localSlotP(Slot* slot, Class* clasS) {
  return (slot->slotOwner->surrogateValue == clasS);
}

void uninheritSlots(Class* clasS) {
  { Cons* slotscursor = clasS->classAllSlots;

    if (((boolean)(slotscursor))) {
      if (!(clasS->multipleParentsP())) {
        { Slot* slot = NULL;
          Cons* iter000 = clasS->classAllSlots;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            slot = ((Slot*)(iter000->value));
            if ((!(slotscursor->rest == NIL)) &&
                localSlotP(((Slot*)(slotscursor->rest->value)), clasS)) {
              slotscursor = slotscursor->rest;
            }
            else {
              break;
            }
          }
        }
        slotscursor->rest = NIL;
      }
      clasS->classAllSlots = NULL;
    }
  }
}

int oSYMBOL_SLOT_OFFSET_COUNTERo = 0;

int oSLOT_CACHE_SIZEo = 20;

void initializeSlotAndMethodCache(Class* clasS) {
  clasS->classSlotAndMethodCache = stella::newVector(oSLOT_CACHE_SIZEo + 1);
}

void registerSlotName(Slot* slot) {
  // Register the name symbol of `slot' as a slot name, and
  // initialize its `symbol-slot-offset' so that it can be used by `lookup-slot'.
  warnAboutSlotShadowedByAFunctionP(slot);
  slot->slotName->symbolSlotOffset = 0;
}

void unregisterSlotName(Slot* slot) {
  // Unregister the name symbol of `slot' as a slot name,
  // so that it can no longer be used by `lookup-slot'.
  slot->slotName->symbolSlotOffset = NULL_INTEGER;
}

boolean registeredSlotNameP(Symbol* slotName) {
  // Return `true' if `slot-name' is the name of some registered;
  // slot in the system.
  return (slotName->symbolSlotOffset != NULL_INTEGER);
}

boolean warnAboutSlotShadowedByAFunctionP(Slot* slot) {
  { Symbol* name = slot->slotName;

    if (!(name->symbolSlotOffset != NULL_INTEGER)) {
      if (((boolean)(lookupMacro(name)))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationWarning();
          if (!(suppressWarningsP())) {
            printErrorContext(">> WARNING: ", STANDARD_WARNING);
            *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Slot " << "`" << deUglifyParseTree(slot) << "'" << " is shadowed by the macro " << "`" << deUglifyParseTree(name) << "'" << "." << std::endl;
          }
        }
        return (true);
      }
      if (((boolean)(lookupFunction(name)))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationWarning();
          if (!(suppressWarningsP())) {
            printErrorContext(">> WARNING: ", STANDARD_WARNING);
            *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Slot " << "`" << deUglifyParseTree(slot) << "'" << " is shadowed by the function " << "`" << deUglifyParseTree(name) << "'" << "." << std::endl;
          }
        }
        return (true);
      }
    }
    return (false);
  }
}

boolean warnAboutFunctionShadowingSlotsP(MethodSlot* function) {
  { Symbol* name = function->slotName;

    if (name->symbolSlotOffset != NULL_INTEGER) {
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
                if (slot->slotName == name) {
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
        if (((BooleanWrapper*)(dynamicSlotValue(function->dynamicSlots, SYM_CLASSES_STELLA_METHOD_MACROp, FALSE_WRAPPER)))->wrapperValue) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationWarning();
            if (!(suppressWarningsP())) {
              printErrorContext(">> WARNING: ", STANDARD_WARNING);
              *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Macro " << "`" << deUglifyParseTree(name) << "'" << " shadows the following methods/slots:" << std::endl << "    " << "`" << deUglifyParseTree(slots) << "'" << "." << std::endl;
            }
          }
        }
        else {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationWarning();
            if (!(suppressWarningsP())) {
              printErrorContext(">> WARNING: ", STANDARD_WARNING);
              *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Function " << "`" << deUglifyParseTree(name) << "'" << " shadows the following methods/slots:" << std::endl << "    " << "`" << deUglifyParseTree(slots) << "'" << "." << std::endl;
            }
          }
        }
        return (true);
      }
    }
    return (false);
  }
}

Slot* lookupSlot(Class* clasS, Symbol* slotName) {
  // Return a slot owned by the class `class' with name `slot-name'.
  // Multiply inherited slots are disambiguated by a left-to-right class
  // precedence order for classes with multiple parents (similar to CLOS).
  if (!((boolean)(clasS))) {
    return (NULL);
  }
  { int offset = slotName->symbolSlotOffset;
    Slot* cachedslot = NULL;

    if (offset != NULL_INTEGER) {
      cachedslot = ((Slot*)((clasS->classSlotAndMethodCache->theArray)[(slotName->symbolSlotOffset)]));
      if (((boolean)(cachedslot)) &&
          (cachedslot->slotName == slotName)) {
        return (cachedslot);
      }
    }
    cachedslot = NULL;
    { Slot* slot = NULL;
      Iterator* iter000 = clasS->classSlots();

      for (; iter000->nextP(); ) {
        slot = ((Slot*)(iter000->value));
        if (slot->slotName == slotName) {
          cachedslot = slot;
          break;
        }
      }
    }
    if (!((boolean)(cachedslot))) {
      return (NULL);
    }
    { int newoffset = ((oSYMBOL_SLOT_OFFSET_COUNTERo + 1) % oSLOT_CACHE_SIZEo);

      oSYMBOL_SLOT_OFFSET_COUNTERo = newoffset;
      slotName->symbolSlotOffset = newoffset;
      clasS->classSlotAndMethodCache->insertAt(newoffset, cachedslot);
      clasS->classSlotAndMethodCache->insertAt(oSLOT_CACHE_SIZEo, cachedslot);
      return (cachedslot);
    }
  }
}

Slot* safeLookupSlot(Class* clasS, Symbol* slotName) {
  // Alias for `lookup-slot'.  Kept for backwards compatibility.
  return (lookupSlot(clasS, slotName));
}

Slot* lookupVisibleSlot(Class* clasS, Object* slotName) {
  { Slot* slot = NULL;
    const char* slotnamestring = NULL;
    Module* module = oMODULEo;

    { Surrogate* testValue000 = safePrimaryType(slotName);

      if (subtypeOfSymbolP(testValue000)) {
        { Object* slotName000 = slotName;
          Symbol* slotName = ((Symbol*)(slotName000));

          slot = lookupSlot(clasS, slotName);
          if (((boolean)(slot))) {
            return (slot);
          }
          slotnamestring = slotName->symbolName;
          module = ((Module*)(slotName->homeContext));
        }
      }
      else if (subtypeOfSurrogateP(testValue000)) {
        { Object* slotName001 = slotName;
          Surrogate* slotName = ((Surrogate*)(slotName001));

          slotnamestring = slotName->symbolName;
          module = ((Module*)(slotName->homeContext));
        }
      }
      else if (subtypeOfKeywordP(testValue000)) {
        { Object* slotName002 = slotName;
          Keyword* slotName = ((Keyword*)(slotName002));

          slotnamestring = slotName->symbolName;
        }
      }
      else if (subtypeOfStringP(testValue000)) {
        { Object* slotName003 = slotName;
          StringWrapper* slotName = ((StringWrapper*)(slotName003));

          slotnamestring = slotName->wrapperValue;
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Illegal slot name: " << "`" << slotName << "'";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    { Symbol* symbol = NULL;
      Cons* iter000 = lookupVisibleSymbolsInModule(slotnamestring, module, true);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        symbol = ((Symbol*)(iter000->value));
        slot = lookupSlot(clasS, symbol);
        if (((boolean)(slot))) {
          return (slot);
        }
      }
    }
    return (NULL);
  }
}

Slot* lookupLocalSlot(Class* clasS, Symbol* slotName) {
  // Lookup a local slot with `slot-name' on `class'.
  { Slot* slot = NULL;
    Cons* iter000 = clasS->classLocalSlots->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      slot = ((Slot*)(iter000->value));
      if (slot->slotName == slotName) {
        return (slot);
      }
    }
  }
  return (NULL);
}

void clearSlotAndMethodCache(Class* clasS) {
  if (((boolean)(((Slot*)((clasS->classSlotAndMethodCache->theArray)[oSLOT_CACHE_SIZEo]))))) {
    clasS->classSlotAndMethodCache->clear();
  }
}

void resizeSlotCaches(int size) {
  // Reset all slot caches to have size `size'.
  oSLOT_CACHE_SIZEo = size;
  { Class* c = NULL;
    Iterator* iter000 = allClasses(NULL, false);

    for (; iter000->nextP(); ) {
      c = ((Class*)(iter000->value));
      c->classSlotAndMethodCache = stella::newVector(size);
      { Slot* s = NULL;
        Cons* iter001 = c->localSlots()->theConsList;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          s = ((Slot*)(iter001->value));
          s->slotName->symbolSlotOffset = 0;
        }
      }
    }
  }
}

Slot* getSlot(StandardObject* self, Symbol* slotName) {
  // Return the slot named `slot-name' on the class
  // representing the type of `self'.
  return (lookupSlot(self->primaryClass(), slotName));
}

Slot* lookupSlotAndClassByQualifiedName(const char* qualifiedname, Class*& _Return1) {
  // Lookup a slot via dotted notation with a possibly qualified class name.
  // Examples: "cons.first" or "stella/cons.first".  This is a variant of `string-to-slot'
  // in describe.ste that actually obeys the class module if it is given.  This also returns
  // the specified class as a second value which might differ from the slot's owner class.
  { const char* dummy1;
    Keyword* dummy2;

    { int dotpos = stringPosition(qualifiedname, '.', 0);
      Class* clasS = NULL;
      Symbol* slotname = NULL;
      Slot* slot = NULL;

      while (dotpos != NULL_INTEGER) {
        clasS = lookupClassByQualifiedName(stringSubsequence(qualifiedname, 0, dotpos));
        if (((boolean)(clasS))) {
          try {
            slotname = lookupSymbolInModule(parseStellaName(stringSubsequence(qualifiedname, dotpos + 1, NULL_INTEGER), true, dummy1, dummy2), clasS->homeModule(), false);
          }
          catch (ReadException ) {
          }
          if (((boolean)(slotname))) {
            slot = lookupSlot(clasS, slotname);
            if (((boolean)(slot))) {
              break;
            }
          }
        }
        dotpos = stringPosition(qualifiedname, '.', dotpos + 1);
      }
      _Return1 = clasS;
      return (slot);
    }
  }
}

Slot* lookupSlotByQualifiedName(const char* qualifiedname) {
  // Lookup a slot via dotted notation with a possibly qualified class name.
  // Examples: "cons.first" or "stella/cons.first".  This is a variant of `string-to-slot'
  // in describe.ste that actually obeys the class module if it is given.
  { Class* dummy1;

    return (lookupSlotAndClassByQualifiedName(qualifiedname, dummy1));
  }
}

boolean conformingTypeSpecP(StandardObject* subTypeSpec, StandardObject* superTypeSpec) {
  return ((!((boolean)(subTypeSpec))) ||
      ((subTypeSpec == SGT_CLASSES_STELLA_UNKNOWN) ||
       ((typeP(subTypeSpec) &&
      (!((boolean)(((Class*)(((Surrogate*)(subTypeSpec))->surrogateValue)))))) ||
        (anchoredTypeSpecifierP(subTypeSpec) ||
         ((!((boolean)(superTypeSpec))) ||
          ((superTypeSpec == SGT_CLASSES_STELLA_UNKNOWN) ||
           ((typeP(superTypeSpec) &&
      (!((boolean)(((Class*)(((Surrogate*)(superTypeSpec))->surrogateValue)))))) ||
            (anchoredTypeSpecifierP(superTypeSpec) ||
             subTypeSpecOfP(subTypeSpec, superTypeSpec)))))))));
}

boolean Slot::conformingSignaturesP(Slot* superslot) {
  { Slot* self = this;

    superslot = superslot;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "conforming-signatures?: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

boolean StorageSlot::conformingSignaturesP(Slot* superslot) {
  { StorageSlot* self = this;

    return (conformingTypeSpecP(self->slotBaseType, superslot->type()) &&
        (conformingTypeSpecP(((CompoundTypeSpecifier*)(dynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_TYPE_SPECIFIER, NULL))), ((CompoundTypeSpecifier*)(dynamicSlotValue(superslot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_TYPE_SPECIFIER, NULL)))) &&
         (superslot->methodArgumentCount() == 1)));
  }
}

boolean MethodSlot::conformingSignaturesP(Slot* superslot) {
  { MethodSlot* self = this;

    if (conformingTypeSpecP(self->slotBaseType, superslot->type()) &&
        (conformingTypeSpecP(((CompoundTypeSpecifier*)(dynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_TYPE_SPECIFIER, NULL))), ((CompoundTypeSpecifier*)(dynamicSlotValue(superslot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_TYPE_SPECIFIER, NULL)))) &&
         (self->methodArgumentCount() == superslot->methodArgumentCount()))) {
      { Surrogate* testValue000 = safePrimaryType(superslot);

        if (subtypeOfStorageSlotP(testValue000)) {
          { Slot* superslot000 = superslot;
            StorageSlot* superslot = ((StorageSlot*)(superslot000));

            return (self->methodReturnTypeSpecifiers_reader()->length() == 1);
          }
        }
        else if (subtypeOfMethodSlotP(testValue000)) {
          { Slot* superslot001 = superslot;
            MethodSlot* superslot = ((MethodSlot*)(superslot001));

            { boolean testValue001 = false;

              { boolean alwaysP000 = true;

                { StandardObject* ts1 = NULL;
                  Cons* iter000 = self->methodParameterTypeSpecifiers_reader()->rest();
                  StandardObject* ts2 = NULL;
                  Cons* iter001 = superslot->methodParameterTypeSpecifiers_reader()->rest();

                  for  (; (!(iter000 == NIL)) &&
                            (!(iter001 == NIL)); 
                        iter000 = iter000->rest,
                        iter001 = iter001->rest) {
                    ts1 = ((StandardObject*)(iter000->value));
                    ts2 = ((StandardObject*)(iter001->value));
                    if (!conformingTypeSpecP(ts2, ts1)) {
                      alwaysP000 = false;
                      break;
                    }
                  }
                }
                testValue001 = alwaysP000;
              }
              if (testValue001) {
                { boolean alwaysP001 = true;

                  { StandardObject* ts1 = NULL;
                    Cons* iter002 = self->methodReturnTypeSpecifiers_reader()->theConsList;
                    StandardObject* ts2 = NULL;
                    Cons* iter003 = superslot->methodReturnTypeSpecifiers_reader()->theConsList;

                    for  (; (!(iter002 == NIL)) &&
                              (!(iter003 == NIL)); 
                          iter002 = iter002->rest,
                          iter003 = iter003->rest) {
                      ts1 = ((StandardObject*)(iter002->value));
                      ts2 = ((StandardObject*)(iter003->value));
                      if (!conformingTypeSpecP(ts1, ts2)) {
                        alwaysP001 = false;
                        break;
                      }
                    }
                  }
                  testValue001 = alwaysP001;
                }
              }
              { boolean value000 = testValue001;

                return (value000);
              }
            }
          }
        }
        else {
        }
      }
    }
    return (false);
  }
}

boolean Table::conformingSignaturesP(Slot* superslot) {
  { Table* self = this;

    if (conformingTypeSpecP(self->slotBaseType, superslot->type()) &&
        (conformingTypeSpecP(((CompoundTypeSpecifier*)(dynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_TYPE_SPECIFIER, NULL))), ((CompoundTypeSpecifier*)(dynamicSlotValue(superslot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_TYPE_SPECIFIER, NULL)))) &&
         (self->methodArgumentCount() == superslot->methodArgumentCount()))) {
      if (subtypeOfP(safePrimaryType(superslot), SGT_CLASSES_STELLA_TABLE)) {
        { Slot* superslot000 = superslot;
          Table* superslot = ((Table*)(superslot000));

          { boolean alwaysP000 = true;

            { StandardObject* ts1 = NULL;
              Cons* iter000 = self->tupleDomains->rest();
              StandardObject* ts2 = NULL;
              Cons* iter001 = superslot->tupleDomains->rest();

              for  (; (!(iter000 == NIL)) &&
                        (!(iter001 == NIL)); 
                    iter000 = iter000->rest,
                    iter001 = iter001->rest) {
                ts1 = ((StandardObject*)(iter000->value));
                ts2 = ((StandardObject*)(iter001->value));
                if (!conformingTypeSpecP(ts2, ts1)) {
                  alwaysP000 = false;
                  break;
                }
              }
            }
            { boolean value000 = alwaysP000;

              return (value000);
            }
          }
        }
      }
      else {
      }
    }
    return (false);
  }
}

boolean identicalSignaturesP(MethodSlot* method1, MethodSlot* method2) {
  { boolean testValue000 = false;

    { boolean alwaysP000 = true;

      { StandardObject* ts1 = NULL;
        Cons* iter000 = method1->methodParameterTypeSpecifiers_reader()->rest();
        StandardObject* ts2 = NULL;
        Cons* iter001 = method2->methodParameterTypeSpecifiers_reader()->rest();

        for  (; (!(iter000 == NIL)) &&
                  (!(iter001 == NIL)); 
              iter000 = iter000->rest,
              iter001 = iter001->rest) {
          ts1 = ((StandardObject*)(iter000->value));
          ts2 = ((StandardObject*)(iter001->value));
          if (!(subTypeSpecOfP(ts1 = computeRelativeTypeSpec(ts1, method1->slotOwner), ts2 = computeRelativeTypeSpec(ts2, method2->slotOwner)) &&
              subTypeSpecOfP(ts2, ts1))) {
            alwaysP000 = false;
            break;
          }
        }
      }
      testValue000 = alwaysP000;
    }
    if (testValue000) {
      { boolean alwaysP001 = true;

        { StandardObject* ts1 = NULL;
          Cons* iter002 = method1->methodReturnTypeSpecifiers_reader()->theConsList;
          StandardObject* ts2 = NULL;
          Cons* iter003 = method2->methodReturnTypeSpecifiers_reader()->theConsList;

          for  (; (!(iter002 == NIL)) &&
                    (!(iter003 == NIL)); 
                iter002 = iter002->rest,
                iter003 = iter003->rest) {
            ts1 = ((StandardObject*)(iter002->value));
            ts2 = ((StandardObject*)(iter003->value));
            if (!(subTypeSpecOfP(ts1 = computeRelativeTypeSpec(ts1, method1->slotOwner), ts2 = computeRelativeTypeSpec(ts2, method2->slotOwner)) &&
                subTypeSpecOfP(ts2, ts1))) {
              alwaysP001 = false;
              break;
            }
          }
        }
        testValue000 = alwaysP001;
      }
    }
    { boolean value000 = testValue000;

      return (value000);
    }
  }
}

void computeRequiredSlotNames(Class* clasS) {
  { List* slotnames = newList();

    { Slot* slot = NULL;
      Iterator* iter000 = clasS->classSlots();

      for (; iter000->nextP(); ) {
        slot = ((Slot*)(iter000->value));
        if (storageSlotP(slot) &&
            (((StorageSlot*)(slot))->slotRequiredP &&
             (!slotnames->memberP(slot->slotName)))) {
          slotnames->push(slot->slotName);
        }
      }
    }
    if (slotnames->emptyP()) {
      slotnames->free();
    }
    else {
      setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_REQUIRED_SLOT_NAMES, slotnames->reverse(), NULL);
    }
  }
}

void freeRequiredSlotNames(Class* clasS) {
  if (clasS->classRequiredSlotNames_reader()->nonEmptyP()) {
    clasS->classRequiredSlotNames_reader()->free();
    setDynamicSlotValue(clasS->dynamicSlots, SYM_CLASSES_STELLA_CLASS_REQUIRED_SLOT_NAMES, NULL, NULL);
  }
}

boolean StorageSlot::dynamicStorageP() {
  { StorageSlot* self = this;

    { Keyword* allocation = self->allocation();

      return ((allocation == KWD_CLASSES_DYNAMIC) ||
          (allocation == KWD_CLASSES_BIT));
    }
  }
}

boolean Relation::privateP() {
  // Return `true' if `self' is not public.
  { Relation* self = this;

    return (!self->publicP());
  }
}

boolean Slot::publicP() {
  // True if `self' or one it its ancestors is marked public.
  { Slot* self = this;

    return (self->slotPublicP ||
        (((boolean)(self->slotDirectEquivalent)) &&
         self->slotDirectEquivalent->publicP()));
  }
}

Iterator* Class::publicSlots() {
  // Return an iterator over public slots of `self'.
  { Class* self = this;

    { Cons* publicslots = ((Cons*)(NIL));
      AllPurposeIterator* iterator = newAllPurposeIterator();

      { Slot* slot = NULL;
        Iterator* iter000 = self->classSlots();

        for (; iter000->nextP(); ) {
          slot = ((Slot*)(iter000->value));
          { boolean testValue000 = false;

            testValue000 = slot->slotPublicP;
            if (testValue000) {
              { boolean foundP000 = false;

                { Slot* ps = NULL;
                  Cons* iter001 = publicslots;

                  for (; !(iter001 == NIL); iter001 = iter001->rest) {
                    ps = ((Slot*)(iter001->value));
                    if (ps->slotName == slot->slotName) {
                      foundP000 = true;
                      break;
                    }
                  }
                }
                testValue000 = foundP000;
              }
              testValue000 = !testValue000;
            }
            if (testValue000) {
              publicslots = ((Cons*)(cons(slot, publicslots)));
            }
          }
        }
      }
      iterator->iteratorNextCode = ((cpp_function_code)(&iteratorConsListNextP));
      iterator->iteratorConsList = publicslots;
      iterator->firstIterationP = true;
      return (iterator);
    }
  }
}

Iterator* Object::publicSlots() {
  // Return an iterator over public slots of `self'.
  { Object* self = this;

    return (self->primaryClass()->publicSlots());
  }
}

AllClassSlotsIterator* newAllClassSlotsIterator() {
  { AllClassSlotsIterator* self = NULL;

    self = new AllClassSlotsIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->iteratorObject = NULL;
    self->iteratorConsList = NULL;
    return (self);
  }
}

Surrogate* AllClassSlotsIterator::primaryType() {
  { AllClassSlotsIterator* self = this;

    return (SGT_CLASSES_STELLA_ALL_CLASS_SLOTS_ITERATOR);
  }
}

Object* accessAllClassSlotsIteratorSlotValue(AllClassSlotsIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_CLASSES_STELLA_ITERATOR_CONS_LIST) {
    if (setvalueP) {
      self->iteratorConsList = ((Cons*)(value));
    }
    else {
      value = self->iteratorConsList;
    }
  }
  else if (slotname == SYM_CLASSES_STELLA_ITERATOR_OBJECT) {
    if (setvalueP) {
      self->iteratorObject = value;
    }
    else {
      value = self->iteratorObject;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

Iterator* Class::allClassSlots() {
  { Class* self = this;

    { AllClassSlotsIterator* iterator = newAllClassSlotsIterator();

      iterator->iteratorConsList = self->classLocalSlots->theConsList;
      iterator->iteratorObject = self->classAllSuperClasses;
      iterator->firstIterationP = true;
      return (iterator);
    }
  }
}

boolean AllClassSlotsIterator::nextP() {
  { AllClassSlotsIterator* self = this;

    { Cons* localslots = self->iteratorConsList;

      if (localslots == NIL) {
        { Cons* classes = ((Cons*)(self->iteratorObject));

          while ((!(classes == NIL)) &&
              (localslots == NIL)) {
            localslots = ((Class*)(classes->value))->classLocalSlots->theConsList;
            classes = classes->rest;
          }
          if (classes == NIL) {
            if (localslots == NIL) {
              self->value = NULL;
              self->iteratorObject = NULL;
              return (false);
            }
          }
          self->iteratorObject = classes;
          self->value = ((Slot*)(localslots->value));
          self->iteratorConsList = localslots->rest;
          return (true);
        }
      }
      else {
        self->value = ((Slot*)(localslots->value));
        self->iteratorConsList = localslots->rest;
        return (true);
      }
    }
  }
}

Iterator* Class::classSlots() {
  { Class* self = this;

    return (self->allClassSlots());
  }
}

List* Class::localSlots() {
  { Class* self = this;

    return (self->classLocalSlots);
  }
}

Iterator* Class::directSuperClasses() {
  // Returns an iterator that generates all direct super classes of `self'.
  { Class* self = this;

    return (newTypesToClassesIterator(self->classDirectSupers->theConsList));
  }
}

Iterator* Class::superClasses() {
  // Returns an iterator that generates all proper super classes of `self'.
  { Class* self = this;

    return (self->classAllSuperClasses->allocateIterator());
  }
}

boolean Slot::activeP() {
  { Slot* slot = this;

    return ((((boolean)(((BooleanWrapper*)(dynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_STORED_ACTIVEp, NULL))))) ? coerceWrappedBooleanToBoolean(((BooleanWrapper*)(dynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_STORED_ACTIVEp, NULL)))) : (((boolean)(((Class*)(SGT_CLASSES_STELLA_COLLECTION->surrogateValue)))) &&
        (((boolean)(((Class*)(slot->slotBaseType->surrogateValue)))) &&
         (((boolean)(((Class*)(slot->slotOwner->surrogateValue)))) &&
          (slot->primitiveP() &&
           (((boolean)(((Symbol*)(dynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_INVERSE, NULL))))) ||
            (((boolean)(slot->slotDirectEquivalent)) &&
             slot->slotDirectEquivalent->activeP()))))))));
  }
}

Object* StorageSlot::initialValue() {
  // Return an initial value for `self', or `null'.  The
  // initial value can be defined by the slot itself, inherited from an
  // equivalent slot, or inherit from the :initial-value option for the 
  // class representing the type of `self'.
  { StorageSlot* self = this;

    { StorageSlot* slot = self;
      Object* value = dynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_INITIAL_VALUE, NULL);

      for (;;) {
        if (((boolean)(value))) {
          return (value);
        }
        slot = ((StorageSlot*)(slot->slotDirectEquivalent));
        if (((boolean)(slot))) {
          value = dynamicSlotValue(slot->dynamicSlots, SYM_CLASSES_STELLA_SLOT_INITIAL_VALUE, NULL);
        }
        else {
          break;
        }
      }
      return (dynamicSlotValue(((Class*)(self->type()->surrogateValue))->dynamicSlots, SYM_CLASSES_STELLA_CLASS_INITIAL_VALUE, NULL));
    }
  }
}

Object* Slot::systemDefaultValue() {
  // Return a default value expression, or if `self'
  // has dynamic storage, an initial value expression.
  { Slot* self = this;

    return (dynamicSlotValue(((Class*)(self->type()->surrogateValue))->dynamicSlots, SYM_CLASSES_STELLA_CLASS_INITIAL_VALUE, NULL));
  }
}

Object* StorageSlot::systemDefaultValue() {
  // Return a default value expression, or if `self'
  // has dynamic storage, an initial value expression.
  { StorageSlot* self = this;

    { Object* value = self->defaultForm();

      if (((boolean)(value))) {
        return (value);
      }
      else if (self->dynamicStorageP() &&
          ((boolean)(((Class*)(self->type()->surrogateValue))))) {
        return (dynamicSlotValue(((Class*)(self->type()->surrogateValue))->dynamicSlots, SYM_CLASSES_STELLA_CLASS_INITIAL_VALUE, NULL));
      }
      else {
        return (NULL);
      }
    }
  }
}

Object* StorageSlot::initially() {
  // Defines the value of a slot before it has been assigned
  // a value.
  { StorageSlot* self = this;

    { Object* value = dynamicSlotValue(self->dynamicSlots, SYM_CLASSES_STELLA_SLOT_INITIAL_VALUE, NULL);

      if (((boolean)(value))) {
        return (value);
      }
      else if (((boolean)(self->slotDirectEquivalent))) {
        return (((StorageSlot*)(self->slotDirectEquivalent))->initially());
      }
      else if (self->slotBaseType == SGT_CLASSES_STELLA_BOOLEAN) {
        return (SYM_CLASSES_STELLA_FALSE);
      }
      else {
        return (NULL);
      }
    }
  }
}

void repairSlots() {
  { Class* top = ((Class*)(SGT_CLASSES_STELLA_OBJECT->surrogateValue));

    unfinalizeClassSlots(top);
    finalizeClassesAndSlots();
  }
}

void disconnectClasses() {
  { Surrogate* surrogate = NULL;
    Iterator* iter000 = allSurrogates(oMODULEo, false);

    for (; iter000->nextP(); ) {
      surrogate = ((Surrogate*)(iter000->value));
      if (((boolean)(surrogate->surrogateValue)) &&
          stellaClassP(surrogate->surrogateValue)) {
        surrogate->surrogateValue = NULL;
      }
    }
  }
}

boolean filterUnboundSurrogateP(Surrogate* self, AllPurposeIterator* iterator) {
  iterator = iterator;
  return (!((boolean)(self->surrogateValue)));
}

Iterator* unboundSurrogates(Module* module, boolean localP) {
  // Iterate over all unbound surrogates visible from `module'.
  // Look at all modules if `module' is `null'.  If `local?', only consider
  // surrogates interned in `module'.
  { AllPurposeIterator* iterator = newAllPurposeIterator();

    iterator->iteratorNestedIterator = allSurrogates(module, localP);
    iterator->iteratorNextCode = ((cpp_function_code)(&filteredNestedIteratorNextP));
    iterator->iteratorFilterCode = ((cpp_function_code)(&filterUnboundSurrogateP));
    return (iterator);
  }
}

const char* nameToString(Object* name) {
  // Return the string represented by `name'.  Return `null'
  // if `name' is undefined or does not represent a string.
  if (((boolean)(name))) {
    { Surrogate* testValue000 = safePrimaryType(name);

      if (subtypeOfP(testValue000, SGT_CLASSES_STELLA_GENERALIZED_SYMBOL)) {
        { Object* name000 = name;
          GeneralizedSymbol* name = ((GeneralizedSymbol*)(name000));

          return (name->symbolName);
        }
      }
      else if (subtypeOfStringP(testValue000)) {
        { Object* name001 = name;
          StringWrapper* name = ((StringWrapper*)(name001));

          return (name->wrapperValue);
        }
      }
      else {
      }
    }
  }
  return (NULL);
}

void printUnboundSurrogates(Cons* args) {
  // Print all unbound surrogates visible from the module named by the first
  // argument (a symbol or string).  Look at all modules if no module name or
  // `null' was supplied.  If the second argument is `true', only consider
  // surrogates interned in the specified module.
  { Cons* arglist = args;
    const char* name = nameToString(arglist->value);
    Module* module = ((name != NULL) ? getStellaModule(name, true) : ((Module*)(NULL)));
    boolean localP = false;

    if (arglist->rest->value == SYM_CLASSES_STELLA_TRUE) {
      localP = true;
    }
    { Surrogate* surrogate = NULL;
      Iterator* iter000 = unboundSurrogates(module, localP);

      for (; iter000->nextP(); ) {
        surrogate = ((Surrogate*)(iter000->value));
        std::cout << surrogate << std::endl;
      }
    }
  }
}

void printUnboundSurrogatesEvaluatorWrapper(Cons* arguments) {
  printUnboundSurrogates(arguments);
}

GeneralizedSymbol* coerceToSymbol(Object* name) {
  // Return the (generalized) symbol represented by `name'.
  // Return `null' if `name' is undefined or does not represent a string.
  if (((boolean)(name))) {
    { Surrogate* testValue000 = safePrimaryType(name);

      if (subtypeOfP(testValue000, SGT_CLASSES_STELLA_GENERALIZED_SYMBOL)) {
        { Object* name000 = name;
          GeneralizedSymbol* name = ((GeneralizedSymbol*)(name000));

          return (name);
        }
      }
      else if (subtypeOfStringP(testValue000)) {
        { Object* name001 = name;
          StringWrapper* name = ((StringWrapper*)(name001));

          return (lookupSymbol(name->wrapperValue));
        }
      }
      else {
      }
    }
  }
  return (NULL);
}

void printUndefinedSuperClasses(Object* clasS) {
  // Print all undefined or bad (indirect) super classes of `class'.
  { Surrogate* type = typify(coerceToSymbol(clasS));
    List* badones = newList();

    if (!((boolean)(type))) {
      std::cout << "Illegal class name: " << clasS << std::endl;
      return;
    }
    collectBadSuperClasses(type, badones);
    if (badones->memberP(type)) {
      if (!((boolean)(type->surrogateValue))) {
        std::cout << type << " is itself undefined." << std::endl;
      }
      else {
        std::cout << type << " itself points to non-class " << type->surrogateValue << std::endl;
      }
      return;
    }
    { boolean foundP000 = false;

      { Surrogate* super = NULL;
        Cons* iter000 = badones->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          super = ((Surrogate*)(iter000->value));
          if (!((boolean)(super->surrogateValue))) {
            foundP000 = true;
            break;
          }
        }
      }
      if (foundP000) {
        std::cout << "The following (indirect) super(s) of " << type << " are undefined:" << std::endl;
        { Surrogate* super = NULL;
          Cons* iter001 = badones->theConsList;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            super = ((Surrogate*)(iter001->value));
            if (!((boolean)(super->surrogateValue))) {
              std::cout << "    " << super << std::endl;
            }
          }
        }
      }
    }
    { boolean foundP001 = false;

      { Surrogate* super = NULL;
        Cons* iter002 = badones->theConsList;

        for (; !(iter002 == NIL); iter002 = iter002->rest) {
          super = ((Surrogate*)(iter002->value));
          if (((boolean)(super->surrogateValue))) {
            foundP001 = true;
            break;
          }
        }
      }
      if (foundP001) {
        std::cout << "The following (indirect) super(s) of " << type << " point to non-classes:" << std::endl;
        { Surrogate* super = NULL;
          Cons* iter003 = badones->theConsList;

          for (; !(iter003 == NIL); iter003 = iter003->rest) {
            super = ((Surrogate*)(iter003->value));
            if (((boolean)(super->surrogateValue))) {
              std::cout << "    " << super << " points to " << super->surrogateValue << std::endl;
            }
          }
        }
      }
    }
  }
}

List* collectBadSuperClasses(Surrogate* type, List* badones) {
  { Object* value = type->surrogateValue;

    if (stellaClassP(value)) {
      { Surrogate* super = NULL;
        Cons* iter000 = ((Class*)(value))->classDirectSupers->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          super = ((Surrogate*)(iter000->value));
          collectBadSuperClasses(super, badones);
        }
      }
    }
    else {
      badones->insertNew(type);
    }
    return (badones);
  }
}

boolean rootClassP(Class* clasS) {
  return (clasS->classDirectSupers->emptyP() &&
      (!clasS->mixinP));
}

TaxonomyGraph* oCLASS_TAXONOMY_GRAPHo = NULL;

void createClassTaxonomy() {
  { TaxonomyGraph* graph = oCLASS_TAXONOMY_GRAPHo;

    if (!((boolean)(graph))) {
      graph = newTaxonomyGraph();
    }
    else {
      initializeTaxonomyGraph(graph);
    }
    { Class* clasS = NULL;
      Iterator* iter000 = allClasses(NULL, false);

      for (; iter000->nextP(); ) {
        clasS = ((Class*)(iter000->value));
        clasS->classTaxonomyNode = createTaxonomyNode(graph, clasS->classTaxonomyNode, clasS, clasS->classDirectSupers->emptyP());
      }
    }
    { Class* clasS = NULL;
      Iterator* iter001 = allClasses(NULL, false);

      for (; iter001->nextP(); ) {
        clasS = ((Class*)(iter001->value));
        { Surrogate* sub = NULL;
          Cons* iter002 = clasS->classDirectSubs->theConsList;

          for (; !(iter002 == NIL); iter002 = iter002->rest) {
            sub = ((Surrogate*)(iter002->value));
            if (((boolean)(((Class*)(sub->surrogateValue))))) {
              linkTaxonomyNodes(graph, clasS->classTaxonomyNode, ((Class*)(sub->surrogateValue))->classTaxonomyNode);
            }
          }
        }
      }
    }
    finalizeTaxonomyGraph(graph);
    oCLASS_TAXONOMY_GRAPHo = graph;
  }
}

boolean subclassOfP(Class* subclass, Class* superclass) {
  // Return `true' if `subClass' is a subclass of `superClass'.
  if (subclass == superclass) {
    return (true);
  }
  { TaxonomyNode* subnode = subclass->classTaxonomyNode;
    TaxonomyNode* supernode = superclass->classTaxonomyNode;
    int sublabel = NULL_INTEGER;

    if ((!((boolean)(subnode))) ||
        ((!((boolean)(supernode))) ||
         ((sublabel = subnode->label) == NULL_INTEGER))) {
      return (subclass->classAllSuperClasses->membP(superclass));
    }
    { Interval* interval = NULL;
      Cons* iter000 = supernode->intervals;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        interval = ((Interval*)(iter000->value));
        if ((sublabel >= interval->lowerBound) &&
            (sublabel <= interval->upperBound)) {
          return (true);
        }
      }
    }
    return (false);
  }
}

boolean fastSubclassOfP(Class* subclass, Class* superclass) {
  { int sublabel = subclass->classTaxonomyNode->label;

    { Interval* interval = NULL;
      Cons* iter000 = superclass->classTaxonomyNode->intervals;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        interval = ((Interval*)(iter000->value));
        if ((sublabel >= interval->lowerBound) &&
            (sublabel <= interval->upperBound)) {
          return (true);
        }
      }
    }
    return (false);
  }
}

boolean subtypeOfP(Surrogate* subType, Surrogate* superType) {
  // Return `true' iff the class named `sub-type' is a subclass 
  // of the class named `super-type'.
  // inline method
  { Class* subclass = typeToClass(subType);
    Class* superclass = typeToClass(superType);

    if (!((boolean)(subclass))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Reference to non-existent class: " << "`" << deUglifyParseTree(subType) << "'" << std::endl << "." << std::endl;
        }
      }
      return (false);
    }
    if (!((boolean)(superclass))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Reference to non-existent class: " << "`" << deUglifyParseTree(superType) << "'" << std::endl << "." << std::endl;
        }
      }
      return (false);
    }
    return (subclassOfP(subclass, superclass));
  }
}

boolean isaP(Object* object, Surrogate* type) {
  // Return `true' iff `object' is an instance of the class named `type'.
  return (subclassOfP(((Class*)(object->primaryType()->surrogateValue)), ((Class*)(type->surrogateValue))));
}

boolean taxonomySubclassOfP(Class* subclass, Class* superclass) {
  return (subclassOfP(subclass, superclass));
}

boolean taxonomyIsaP(Object* object, Surrogate* type) {
  return (isaP(object, type));
}

Surrogate* internSlotref(const char* classname, const char* slotname) {
  return (internSurrogate(stringConcatenate(classname, stringConcatenate(".", slotname, 0), 0)));
}

Surrogate* lookupSlotref(Surrogate* self, Symbol* slotname) {
  self = ((Surrogate*)(realTypeSpecifier(self)));
  { Class* clasS = ((Class*)(self->surrogateValue));
    Slot* slot = NULL;
    Surrogate* slotref = NULL;

    slot = lookupFunction(slotname);
    if (!((boolean)(slot))) {
      slot = lookupSlot(clasS, slotname);
    }
    if (!((boolean)(slot))) {
      if (((boolean)(clasS))) {
        return (NULL);
      }
    }
    else {
      self = slot->slotOwner;
      if (!((boolean)(self))) {
        self = SGT_CLASSES_STELLA_ANY;
      }
      slotref = slot->slotSlotref;
    }
    if (!((boolean)(slotref))) {
      { 
        BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(slot)) ? slot->homeModule() : ((Module*)(((Symbol*)(slotname->permanentify()))->homeContext))));
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
        slotref = internSlotref(self->symbolName, slotname->symbolName);
      }
      slotref->surrogateValue = slot;
      if (((boolean)(slot))) {
        slot->slotSlotref = slotref;
      }
    }
    return (slotref);
  }
}

boolean slotrefP(Surrogate* self) {
  return (stringPosition(self->symbolName, '.', 0) != NULL_INTEGER);
}

Slot* lookupSlotFromSlotref(Surrogate* slotref) {
  { Object* value = slotref->surrogateValue;

    if (((boolean)(value))) {
      if (isaP(value, SGT_CLASSES_STELLA_SLOT)) {
        return (((Slot*)(value)));
      }
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "lookup-slot-from-slotref: " << "`" << slotref << "'" << " already points to non-slot " << "`" << value << "'" << std::endl;
      return (NULL);
    }
  }
  { const char* slotrefname = slotref->symbolName;
    Module* slotrefmodule = ((Module*)(slotref->homeContext));
    int dotposition = stringPosition(slotrefname, '.', 0);
    Surrogate* type = NULL;
    Symbol* slotname = NULL;
    Slot* slot = NULL;

    if (dotposition != NULL_INTEGER) {
      type = lookupSurrogateInModule(stringSubsequence(slotrefname, 0, dotposition), slotrefmodule, false);
    }
    else {
      type = SGT_CLASSES_STELLA_ANY;
      dotposition = -1;
    }
    if (((boolean)(type))) {
      type = ((Surrogate*)(realTypeSpecifier(type)));
    }
    if (((boolean)(type)) &&
        stellaClassP(type->surrogateValue)) {
      slotname = lookupSymbolInModule(stringSubsequence(slotrefname, dotposition + 1, NULL_INTEGER), slotrefmodule, false);
      if (((boolean)(slotname))) {
        slot = lookupFunction(slotname);
        if (!((boolean)(slot))) {
          slot = lookupSlot(((Class*)(type->surrogateValue)), slotname);
        }
        if (((boolean)(slot))) {
          if (!((boolean)(slot->slotSlotref))) {
            lookupSlotref(((!((boolean)(slot->slotOwner))) ? SGT_CLASSES_STELLA_ANY : slot->slotOwner), slot->slotName);
          }
          slotref->surrogateValue = slot;
        }
      }
    }
    return (slot);
  }
}

Surrogate* slotrefType(Surrogate* slotref) {
  return (((Slot*)(slotref->surrogateValue))->type());
}

void helpStartupClasses1() {
  {
    SGT_CLASSES_STELLA_CLASS = ((Surrogate*)(internRigidSymbolWrtModule("CLASS", NULL, 1)));
    SGT_CLASSES_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", NULL, 1)));
    KWD_CLASSES_PUBLICp = ((Keyword*)(internRigidSymbolWrtModule("PUBLIC?", NULL, 2)));
    KWD_CLASSES_PARAMETERS = ((Keyword*)(internRigidSymbolWrtModule("PARAMETERS", NULL, 2)));
    SYM_CLASSES_STELLA_SLOT_TYPE_SPECIFIER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-TYPE-SPECIFIER", NULL, 0)));
    KWD_CLASSES_REQUIREDp = ((Keyword*)(internRigidSymbolWrtModule("REQUIRED?", NULL, 2)));
    KWD_CLASSES_COMPONENTp = ((Keyword*)(internRigidSymbolWrtModule("COMPONENT?", NULL, 2)));
    KWD_CLASSES_READ_ONLYp = ((Keyword*)(internRigidSymbolWrtModule("READ-ONLY?", NULL, 2)));
    KWD_CLASSES_ACTIVEp = ((Keyword*)(internRigidSymbolWrtModule("ACTIVE?", NULL, 2)));
    SYM_CLASSES_STELLA_STORED_ACTIVEp = ((Symbol*)(internRigidSymbolWrtModule("STORED-ACTIVE?", NULL, 0)));
    KWD_CLASSES_CONTEXT_SENSITIVEp = ((Keyword*)(internRigidSymbolWrtModule("CONTEXT-SENSITIVE?", NULL, 2)));
    KWD_CLASSES_HARDWIREDp = ((Keyword*)(internRigidSymbolWrtModule("HARDWIRED?", NULL, 2)));
    KWD_CLASSES_ABSTRACTp = ((Keyword*)(internRigidSymbolWrtModule("ABSTRACT?", NULL, 2)));
    KWD_CLASSES_ALLOCATION = ((Keyword*)(internRigidSymbolWrtModule("ALLOCATION", NULL, 2)));
    KWD_CLASSES_CLASS = ((Keyword*)(internRigidSymbolWrtModule("CLASS", NULL, 2)));
    SYM_CLASSES_STELLA_SLOT_ALLOCATION = ((Symbol*)(internRigidSymbolWrtModule("SLOT-ALLOCATION", NULL, 0)));
    KWD_CLASSES_INITIALLY = ((Keyword*)(internRigidSymbolWrtModule("INITIALLY", NULL, 2)));
    SYM_CLASSES_STELLA_SLOT_INITIAL_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SLOT-INITIAL-VALUE", NULL, 0)));
    KWD_CLASSES_DEFAULT = ((Keyword*)(internRigidSymbolWrtModule("DEFAULT", NULL, 2)));
    SYM_CLASSES_STELLA_SLOT_DEFAULT_EXPRESSION = ((Symbol*)(internRigidSymbolWrtModule("SLOT-DEFAULT-EXPRESSION", NULL, 0)));
    KWD_CLASSES_READER = ((Keyword*)(internRigidSymbolWrtModule("READER", NULL, 2)));
    SYM_CLASSES_STELLA_SLOT_READER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-READER", NULL, 0)));
    KWD_CLASSES_WRITER = ((Keyword*)(internRigidSymbolWrtModule("WRITER", NULL, 2)));
    SYM_CLASSES_STELLA_SLOT_WRITER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-WRITER", NULL, 0)));
    KWD_CLASSES_INVERSE = ((Keyword*)(internRigidSymbolWrtModule("INVERSE", NULL, 2)));
    SYM_CLASSES_STELLA_SLOT_INVERSE = ((Symbol*)(internRigidSymbolWrtModule("SLOT-INVERSE", NULL, 0)));
    KWD_CLASSES_RENAMES = ((Keyword*)(internRigidSymbolWrtModule("RENAMES", NULL, 2)));
    SYM_CLASSES_STELLA_SLOT_RENAMES = ((Symbol*)(internRigidSymbolWrtModule("SLOT-RENAMES", NULL, 0)));
    KWD_CLASSES_DOCUMENTATION = ((Keyword*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 2)));
    SYM_CLASSES_STELLA_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 0)));
    KWD_CLASSES_PROPERTIES = ((Keyword*)(internRigidSymbolWrtModule("PROPERTIES", NULL, 2)));
    SYM_CLASSES_STELLA_PROPERTIES = ((Symbol*)(internRigidSymbolWrtModule("PROPERTIES", NULL, 0)));
    KWD_CLASSES_META_ATTRIBUTES = ((Keyword*)(internRigidSymbolWrtModule("META-ATTRIBUTES", NULL, 2)));
    SYM_CLASSES_STELLA_META_ATTRIBUTES = ((Symbol*)(internRigidSymbolWrtModule("META-ATTRIBUTES", NULL, 0)));
    KWD_CLASSES_OPTION_KEYWORD = ((Keyword*)(internRigidSymbolWrtModule("OPTION-KEYWORD", NULL, 2)));
    SYM_CLASSES_STELLA_SLOT_OPTION_KEYWORD = ((Symbol*)(internRigidSymbolWrtModule("SLOT-OPTION-KEYWORD", NULL, 0)));
    KWD_CLASSES_OPTION_HANDLER = ((Keyword*)(internRigidSymbolWrtModule("OPTION-HANDLER", NULL, 2)));
    SYM_CLASSES_STELLA_SLOT_OPTION_HANDLER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-OPTION-HANDLER", NULL, 0)));
    SGT_CLASSES_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 1)));
    KWD_CLASSES_BIT = ((Keyword*)(internRigidSymbolWrtModule("BIT", NULL, 2)));
    KWD_CLASSES_CL_NATIVE_TYPE = ((Keyword*)(internRigidSymbolWrtModule("CL-NATIVE-TYPE", NULL, 2)));
    SYM_CLASSES_STELLA_CLASS_CL_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CL-NATIVE-TYPE", NULL, 0)));
    KWD_CLASSES_CPP_NATIVE_TYPE = ((Keyword*)(internRigidSymbolWrtModule("CPP-NATIVE-TYPE", NULL, 2)));
    SYM_CLASSES_STELLA_CLASS_CPP_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CPP-NATIVE-TYPE", NULL, 0)));
    KWD_CLASSES_IDL_NATIVE_TYPE = ((Keyword*)(internRigidSymbolWrtModule("IDL-NATIVE-TYPE", NULL, 2)));
    SYM_CLASSES_STELLA_CLASS_IDL_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-IDL-NATIVE-TYPE", NULL, 0)));
    KWD_CLASSES_JAVA_NATIVE_TYPE = ((Keyword*)(internRigidSymbolWrtModule("JAVA-NATIVE-TYPE", NULL, 2)));
    SYM_CLASSES_STELLA_CLASS_JAVA_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-JAVA-NATIVE-TYPE", NULL, 0)));
    KWD_CLASSES_CL_STRUCTp = ((Keyword*)(internRigidSymbolWrtModule("CL-STRUCT?", NULL, 2)));
    KWD_CLASSES_MIXINp = ((Keyword*)(internRigidSymbolWrtModule("MIXIN?", NULL, 2)));
    KWD_CLASSES_RECYCLE_METHOD = ((Keyword*)(internRigidSymbolWrtModule("RECYCLE-METHOD", NULL, 2)));
    SYM_CLASSES_STELLA_CLASS_RECYCLE_METHOD = ((Symbol*)(internRigidSymbolWrtModule("CLASS-RECYCLE-METHOD", NULL, 0)));
    KWD_CLASSES_EXTENSION = ((Keyword*)(internRigidSymbolWrtModule("EXTENSION", NULL, 2)));
    SYM_CLASSES_STELLA_CLASS_EXTENSION_NAME = ((Symbol*)(internRigidSymbolWrtModule("CLASS-EXTENSION-NAME", NULL, 0)));
    KWD_CLASSES_CREATOR = ((Keyword*)(internRigidSymbolWrtModule("CREATOR", NULL, 2)));
    SYM_CLASSES_STELLA_CLASS_CREATOR = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CREATOR", NULL, 0)));
    KWD_CLASSES_INITIALIZER = ((Keyword*)(internRigidSymbolWrtModule("INITIALIZER", NULL, 2)));
    SYM_CLASSES_STELLA_CLASS_INITIALIZER = ((Symbol*)(internRigidSymbolWrtModule("CLASS-INITIALIZER", NULL, 0)));
    KWD_CLASSES_TERMINATOR = ((Keyword*)(internRigidSymbolWrtModule("TERMINATOR", NULL, 2)));
    SYM_CLASSES_STELLA_CLASS_TERMINATOR = ((Symbol*)(internRigidSymbolWrtModule("CLASS-TERMINATOR", NULL, 0)));
  }
}

void helpStartupClasses2() {
  {
    KWD_CLASSES_DESTRUCTOR = ((Keyword*)(internRigidSymbolWrtModule("DESTRUCTOR", NULL, 2)));
    SYM_CLASSES_STELLA_CLASS_DESTRUCTOR = ((Symbol*)(internRigidSymbolWrtModule("CLASS-DESTRUCTOR", NULL, 0)));
    KWD_CLASSES_INITIAL_VALUE = ((Keyword*)(internRigidSymbolWrtModule("INITIAL-VALUE", NULL, 2)));
    SYM_CLASSES_STELLA_CLASS_INITIAL_VALUE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-INITIAL-VALUE", NULL, 0)));
    KWD_CLASSES_PRINT_FORM = ((Keyword*)(internRigidSymbolWrtModule("PRINT-FORM", NULL, 2)));
    SYM_CLASSES_STELLA_PRINT_FORM = ((Symbol*)(internRigidSymbolWrtModule("PRINT-FORM", NULL, 0)));
    KWD_CLASSES_EQUALITY_TEST = ((Keyword*)(internRigidSymbolWrtModule("EQUALITY-TEST", NULL, 2)));
    KWD_CLASSES_KEY = ((Keyword*)(internRigidSymbolWrtModule("KEY", NULL, 2)));
    SYM_CLASSES_STELLA_CLASS_KEY = ((Symbol*)(internRigidSymbolWrtModule("CLASS-KEY", NULL, 0)));
    SYM_CLASSES_STELLA_CLASS_PARAMETERS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-PARAMETERS", NULL, 0)));
    KWD_CLASSES_SYNONYMS = ((Keyword*)(internRigidSymbolWrtModule("SYNONYMS", NULL, 2)));
    SYM_CLASSES_STELLA_CLASS_SYNONYMS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-SYNONYMS", NULL, 0)));
    KWD_CLASSES_CHILDREN = ((Keyword*)(internRigidSymbolWrtModule("CHILDREN", NULL, 2)));
    SGT_CLASSES_STELLA_METHOD_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-SLOT", NULL, 1)));
    SYM_CLASSES_STELLA_SLOT_GUARD_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("SLOT-GUARD-DEMONS", NULL, 0)));
    SYM_CLASSES_STELLA_SLOT_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("SLOT-DEMONS", NULL, 0)));
    SYM_CLASSES_STELLA_CLASS_CONSTRUCTOR_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CONSTRUCTOR-DEMONS", NULL, 0)));
    SYM_CLASSES_STELLA_CLASS_GUARD_CONSTRUCTOR_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-GUARD-CONSTRUCTOR-DEMONS", NULL, 0)));
    SYM_CLASSES_STELLA_CLASS_DESTRUCTOR_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-DESTRUCTOR-DEMONS", NULL, 0)));
    SYM_CLASSES_STELLA_CLASS_GUARD_DESTRUCTOR_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-GUARD-DESTRUCTOR-DEMONS", NULL, 0)));
    SGT_CLASSES_STELLA_ACTIVE_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("ACTIVE-OBJECT", NULL, 1)));
    SGT_CLASSES_STELLA_STANDARD_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("STANDARD-OBJECT", NULL, 1)));
    SYM_CLASSES_STELLA_PRIMARY_TYPE = ((Symbol*)(internRigidSymbolWrtModule("PRIMARY-TYPE", NULL, 0)));
    SYM_CLASSES_STELLA_SELF = ((Symbol*)(internRigidSymbolWrtModule("SELF", NULL, 0)));
    KWD_CLASSES_TYPE = ((Keyword*)(internRigidSymbolWrtModule("TYPE", NULL, 2)));
    SYM_CLASSES_STELLA_TYPE = ((Symbol*)(internRigidSymbolWrtModule("TYPE", NULL, 0)));
    KWD_CLASSES_AUXILIARYp = ((Keyword*)(internRigidSymbolWrtModule("AUXILIARY?", NULL, 2)));
    SYM_CLASSES_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    SYM_CLASSES_STELLA_RETURN = ((Symbol*)(internRigidSymbolWrtModule("RETURN", NULL, 0)));
    SYM_CLASSES_STELLA_CLASS_EXTENSION = ((Symbol*)(internRigidSymbolWrtModule("CLASS-EXTENSION", NULL, 0)));
    SYM_CLASSES_STELLA_BADp = ((Symbol*)(internRigidSymbolWrtModule("BAD?", NULL, 0)));
    SGT_CLASSES_STELLA_SET = ((Surrogate*)(internRigidSymbolWrtModule("SET", NULL, 1)));
    SGT_CLASSES_STELLA_ACTIVE_SET = ((Surrogate*)(internRigidSymbolWrtModule("ACTIVE-SET", NULL, 1)));
    SGT_CLASSES_STELLA_LIST = ((Surrogate*)(internRigidSymbolWrtModule("LIST", NULL, 1)));
    SGT_CLASSES_STELLA_ACTIVE_LIST = ((Surrogate*)(internRigidSymbolWrtModule("ACTIVE-LIST", NULL, 1)));
    SGT_CLASSES_STELLA_UNKNOWN = ((Surrogate*)(internRigidSymbolWrtModule("UNKNOWN", NULL, 1)));
    SGT_CLASSES_STELLA_COLLECTION = ((Surrogate*)(internRigidSymbolWrtModule("COLLECTION", NULL, 1)));
    SGT_CLASSES_STELLA_SET_MIXIN = ((Surrogate*)(internRigidSymbolWrtModule("SET-MIXIN", NULL, 1)));
    SYM_CLASSES_STELLA_INVERSE = ((Symbol*)(internRigidSymbolWrtModule("INVERSE", NULL, 0)));
    KWD_CLASSES_DYNAMIC = ((Keyword*)(internRigidSymbolWrtModule("DYNAMIC", NULL, 2)));
    SGT_CLASSES_STELLA_DYNAMIC_SLOTS_MIXIN = ((Surrogate*)(internRigidSymbolWrtModule("DYNAMIC-SLOTS-MIXIN", NULL, 1)));
    KWD_CLASSES_INSTANCE = ((Keyword*)(internRigidSymbolWrtModule("INSTANCE", NULL, 2)));
    SGT_CLASSES_STELLA_CONTEXT_SENSITIVE_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("CONTEXT-SENSITIVE-OBJECT", NULL, 1)));
    SGT_CLASSES_STELLA_CONTEXT_SENSITIVE_MIXIN = ((Surrogate*)(internRigidSymbolWrtModule("CONTEXT-SENSITIVE-MIXIN", NULL, 1)));
    SGT_CLASSES_STELLA_VOID = ((Surrogate*)(internRigidSymbolWrtModule("VOID", NULL, 1)));
    SYM_CLASSES_STELLA_METHOD_MACROp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-MACRO?", NULL, 0)));
    SGT_CLASSES_STELLA_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("TABLE", NULL, 1)));
    SYM_CLASSES_STELLA_CLASS_REQUIRED_SLOT_NAMES = ((Symbol*)(internRigidSymbolWrtModule("CLASS-REQUIRED-SLOT-NAMES", NULL, 0)));
    SGT_CLASSES_STELLA_ALL_CLASS_SLOTS_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("ALL-CLASS-SLOTS-ITERATOR", NULL, 1)));
    SYM_CLASSES_STELLA_ITERATOR_CONS_LIST = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR-CONS-LIST", NULL, 0)));
    SYM_CLASSES_STELLA_ITERATOR_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR-OBJECT", NULL, 0)));
    SYM_CLASSES_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", NULL, 0)));
    SGT_CLASSES_STELLA_GENERALIZED_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("GENERALIZED-SYMBOL", NULL, 1)));
    SYM_CLASSES_STELLA_ANY = ((Symbol*)(internRigidSymbolWrtModule("ANY", NULL, 0)));
    SGT_CLASSES_STELLA_ANY = ((Surrogate*)(internRigidSymbolWrtModule("ANY", NULL, 1)));
    SGT_CLASSES_STELLA_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("SLOT", NULL, 1)));
    SYM_CLASSES_STELLA_STARTUP_CLASSES = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-CLASSES", NULL, 0)));
    SYM_CLASSES_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupClasses3() {
  {
    defineFunctionObject("CLASS-NAME", "(DEFUN (CLASS-NAME STRING) ((CLASS CLASS)) :PUBLIC? TRUE)", ((cpp_function_code)(&className)), NULL);
    defineFunctionObject("CLASS-SURROGATE", "(DEFUN (CLASS-SURROGATE SURROGATE) ((CLASS CLASS)) :PUBLIC? TRUE)", ((cpp_function_code)(&classSurrogate)), NULL);
    defineFunctionObject("CLASS-SYMBOL", "(DEFUN (CLASS-SYMBOL SYMBOL) ((CLASS CLASS)) :PUBLIC? TRUE)", ((cpp_function_code)(&classSymbol)), NULL);
    defineMethodObject("(DEFMETHOD (PRIMARY-CLASS CLASS) ((SELF OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE)", wrapMethodCode(((cpp_method_code)(&Object::primaryClass))), NULL);
    defineMethodObject("(DEFMETHOD (LOOKUP-CLASS CLASS) ((NAME STRING)) :DOCUMENTATION \"Return a class with name `name'.  Scan all\nvisible surrogates looking for one that has a class defined for it.\" :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((Class*  (*) (const char*))(&stringLookupClass))))), NULL);
    defineMethodObject("(DEFMETHOD (LOOKUP-CLASS CLASS) ((NAME SYMBOL)) :DOCUMENTATION \"Return a class with name `name'.  Scan all\nvisible surrogates looking for one that has a class defined for it.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Symbol::lookupClass))), NULL);
    defineFunctionObject("LOOKUP-CLASS-BY-QUALIFIED-NAME", "(DEFUN (LOOKUP-CLASS-BY-QUALIFIED-NAME CLASS) ((QUALIFIEDNAME STRING)) :DOCUMENTATION \"Variant of `string.lookup-class' that can specify a\nstarting module through a `qualifiedName'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupClassByQualifiedName)), NULL);
    defineFunctionObject("TYPE-TO-CLASS", "(DEFUN (TYPE-TO-CLASS CLASS) ((TYPE TYPE)))", ((cpp_function_code)(&typeToClass)), NULL);
    defineMethodObject("(DEFMETHOD (GET-STELLA-CLASS CLASS) ((CLASS-NAME TYPE) (ERROR? BOOLEAN)) :DOCUMENTATION \"Return a class with name `class-name'.  If none exists, break\nif `error?', else return `null'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Surrogate::getStellaClass))), NULL);
    defineMethodObject("(DEFMETHOD (GET-STELLA-CLASS CLASS) ((CLASS-NAME STRING) (ERROR? BOOLEAN)) :DOCUMENTATION \"Return a class with name `class-name'.  If none exists, break\nif `error?', else return `null'.\" :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((Class*  (*) (const char*, boolean))(&stringGetStellaClass))))), NULL);
    defineMethodObject("(DEFMETHOD (GET-STELLA-CLASS CLASS) ((CLASS-NAME SYMBOL) (ERROR? BOOLEAN)) :DOCUMENTATION \"Return a class with name `class-name'.  If non exists, break\nif `error?', else return `null'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Symbol::getStellaClass))), NULL);
    defineFunctionObject("BIND-TO-SURROGATE?", "(DEFUN (BIND-TO-SURROGATE? BOOLEAN OBJECT SURROGATE) ((SELF OBJECT) (NAME STRING) (CLIPOLDVALUE? BOOLEAN) (ASKFORPERMISSION? BOOLEAN)) :PUBLIC? TRUE)", ((cpp_function_code)(&bindToSurrogateP)), NULL);
    defineMethodObject("(DEFMETHOD UNBIND-FROM-SURROGATE ((SELF CLASS)))", wrapMethodCode(((cpp_method_code)(&Class::unbindFromSurrogate))), NULL);
    defineFunctionObject("SHADOW-SYMBOL", "(DEFUN (SHADOW-SYMBOL SYMBOL) ((NAME STRING)) :PUBLIC? TRUE)", ((cpp_function_code)(&shadowSymbol)), NULL);
    defineFunctionObject("SHADOW-SURROGATE", "(DEFUN (SHADOW-SURROGATE SURROGATE) ((NAME STRING)) :PUBLIC? TRUE)", ((cpp_function_code)(&shadowSurrogate)), NULL);
    defineFunctionObject("SHADOWED-SYMBOL?", "(DEFUN (SHADOWED-SYMBOL? BOOLEAN) ((SYMBOL GENERALIZED-SYMBOL)) :DOCUMENTATION \"Return `true' if `symbol' is shadowed in its home module.\" :PUBLIC? TRUE)", ((cpp_function_code)(&shadowedSymbolP)), NULL);
    defineFunctionObject("GET-CONSTRUCTOR", "(DEFUN (GET-CONSTRUCTOR FUNCTION-CODE) ((CLASS CLASS) (WARN? BOOLEAN)))", ((cpp_function_code)(&getConstructor)), NULL);
    defineFunctionObject("CREATE-OBJECT", "(DEFUN (CREATE-OBJECT OBJECT) ((TYPE TYPE) |&REST| (INITIAL-VALUE-PAIRS OBJECT)) :DOCUMENTATION \"Funcallable version of the `new' operator.\nReturn an instance of the class named by `type'.  If `initial-value-pairs'\nis supplied, it has to be a key/value list similar to what's accepted by `new'\nand the named slots will be initialized with the supplied values.  Similar to\n`new', all required arguments for `type' must be included.  Since all the\nslot initialization, etc. is handled dynamically at run time, `create-object'\nis much slower than `new'; therefore, it should only be used if `type' cannot\nbe known at translation time.\" :PUBLIC? TRUE)", ((cpp_function_code)(&createObject)), NULL);
    defineMethodObject("(DEFMETHOD FREE ((SELF OBJECT)) :DOCUMENTATION \"Default method.  Deallocate storage for `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Object::free))), NULL);
    defineMethodObject("(DEFMETHOD FREE ((SELF ACTIVE-OBJECT)) :DOCUMENTATION \"Remove all pointers between `self' and other objects,\nand then deallocate the storage for self.\")", wrapMethodCode(((cpp_method_code)(&ActiveObject::free))), NULL);
    defineFunctionObject("DEFINE-STELLA-CLASS", "(DEFUN (DEFINE-STELLA-CLASS CLASS) ((NAME TYPE) (SUPERS (LIST OF TYPE)) (SLOTS (LIST OF SLOT)) (OPTIONS KEYWORD-KEY-VALUE-LIST)) :DOCUMENTATION \"Return a Stella class with name `name'.\nCaution:  If the class already exists, the Stella class object gets\nredefined, but the native C++ class is not redefined.\" :PUBLIC? TRUE)", ((cpp_function_code)(&defineStellaClass)), NULL);
    defineFunctionObject("DEFINE-STELLA-SLOT", "(DEFUN (DEFINE-STELLA-SLOT SLOT) ((NAME SYMBOL) (OWNER TYPE) (BASETYPE TYPE) (TYPESPECIFIER CONS) (OPTIONS KEYWORD-KEY-VALUE-LIST)))", ((cpp_function_code)(&defineStellaSlot)), NULL);
    defineFunctionObject("INCORPORATE-CLASS-OPTIONS", "(DEFUN INCORPORATE-CLASS-OPTIONS ((CLASS CLASS) (OPTIONS KEYWORD-KEY-VALUE-LIST)))", ((cpp_function_code)(&incorporateClassOptions)), NULL);
    defineFunctionObject("INLINE-METHOD?", "(DEFUN (INLINE-METHOD? BOOLEAN) ((SLOT SLOT)))", ((cpp_function_code)(&inlineMethodP)), NULL);
    defineFunctionObject("TRANSFER-EXTERNAL-SLOT-TO-NEW-CLASS", "(DEFUN TRANSFER-EXTERNAL-SLOT-TO-NEW-CLASS ((EXTERNALSLOT SLOT) (NEWCLASS CLASS)))", ((cpp_function_code)(&transferExternalSlotToNewClass)), NULL);
    defineFunctionObject("TRANSFER-DEMONS-FROM-OLDCLASS", "(DEFUN TRANSFER-DEMONS-FROM-OLDCLASS ((OLDCLASS CLASS) (NEWCLASS CLASS)))", ((cpp_function_code)(&transferDemonsFromOldclass)), NULL);
    defineFunctionObject("UNDEFINE-OLD-CLASS", "(DEFUN UNDEFINE-OLD-CLASS ((OLDCLASS CLASS) (NEWCLASS CLASS)))", ((cpp_function_code)(&undefineOldClass)), NULL);
    defineMethodObject("(DEFMETHOD DESTROY-CLASS ((SELF CLASS)) :DOCUMENTATION \"Destroy the Stella class `self'.  \nUnfinalize its subclasses (if it has any).\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Class::destroyClass))), NULL);
    defineMethodObject("(DEFMETHOD DESTROY-CLASS ((SELF TYPE)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Surrogate::destroyClass))), NULL);
    defineFunctionObject("DESTROY-CLASS-AND-SUBCLASSES", "(DEFUN DESTROY-CLASS-AND-SUBCLASSES ((SELF CLASS)) :DOCUMENTATION \"Destroy the Stella class `self' and all its subclasses.\")", ((cpp_function_code)(&destroyClassAndSubclasses)), NULL);
    defineMethodObject("(DEFMETHOD (PRIMITIVE? BOOLEAN) ((SELF RELATION)) :DOCUMENTATION \"Return `true' if `self' is not a defined relation.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Relation::primitiveP))), NULL);
    defineFunctionObject("INSERT-PRIMITIVE-SUPER", "(DEFUN INSERT-PRIMITIVE-SUPER ((NEWSUPER TYPE) (SUPERS (LIST OF TYPE))))", ((cpp_function_code)(&insertPrimitiveSuper)), NULL);
    defineFunctionObject("COLLECT-MOST-SPECIFIC-PRIMITIVE-SUPERS", "(DEFUN COLLECT-MOST-SPECIFIC-PRIMITIVE-SUPERS ((CLASS CLASS) (SUPERS (LIST OF TYPE))))", ((cpp_function_code)(&collectMostSpecificPrimitiveSupers)), NULL);
    defineFunctionObject("MOST-SPECIFIC-PRIMITIVE-SUPERS", "(DEFUN (MOST-SPECIFIC-PRIMITIVE-SUPERS (LIST OF TYPE)) ((CLASS CLASS)))", ((cpp_function_code)(&mostSpecificPrimitiveSupers)), NULL);
    defineFunctionObject("CLASS-NATIVE-SUPERS", "(DEFUN (CLASS-NATIVE-SUPERS (LIST OF TYPE)) ((CLASS CLASS)))", ((cpp_function_code)(&classNativeSupers)), NULL);
    defineFunctionObject("REMEMBER-UNFINALIZED-CLASS", "(DEFUN REMEMBER-UNFINALIZED-CLASS ((CLASS CLASS) (FORCE? BOOLEAN)))", ((cpp_function_code)(&rememberUnfinalizedClass)), NULL);
    defineFunctionObject("FORGET-UNFINALIZED-CLASS", "(DEFUN FORGET-UNFINALIZED-CLASS ((CLASS CLASS)))", ((cpp_function_code)(&forgetUnfinalizedClass)), NULL);
    defineFunctionObject("FINALIZE-CLASSES", "(DEFUN FINALIZE-CLASSES () :DOCUMENTATION \"Finalize all currently unfinalized classes.\" :PUBLIC? TRUE)", ((cpp_function_code)(&finalizeClasses)), NULL);
    defineFunctionObject("RESOLVE-CHILDREN-REFERENCES", "(DEFUN RESOLVE-CHILDREN-REFERENCES ())", ((cpp_function_code)(&resolveChildrenReferences)), NULL);
    defineFunctionObject("FINALIZE-SLOTS", "(DEFUN FINALIZE-SLOTS () :PUBLIC? TRUE :DOCUMENTATION \"Finalize all currently unfinalized slots.\")", ((cpp_function_code)(&finalizeSlots)), NULL);
    defineFunctionObject("CLEANUP-UNFINALIZED-CLASSES", "(DEFUN CLEANUP-UNFINALIZED-CLASSES () :PUBLIC? TRUE :DOCUMENTATION \"Remove all finalized classes from `*UNFINALIZED-CLASSES*',\nand set `*NEWLY-UNFINALIZED-CLASSES?*' to `false'.\")", ((cpp_function_code)(&cleanupUnfinalizedClasses)), NULL);
    defineFunctionObject("FINALIZE-CLASSES-AND-SLOTS", "(DEFUN FINALIZE-CLASSES-AND-SLOTS () :PUBLIC? TRUE :DOCUMENTATION \"Finalize all currently unfinalized classes and slots.\")", ((cpp_function_code)(&finalizeClassesAndSlots)), NULL);
    defineFunctionObject("ACTIVATE-CLASS", "(DEFUN ACTIVATE-CLASS ((CLASS CLASS)))", ((cpp_function_code)(&activateClass)), NULL);
    defineFunctionObject("ADD-PRIMARY-TYPE", "(DEFUN ADD-PRIMARY-TYPE ((CLASS CLASS)))", ((cpp_function_code)(&addPrimaryType)), NULL);
    defineFunctionObject("FINALIZE-ONE-CLASS", "(DEFUN FINALIZE-ONE-CLASS ((CLASS CLASS)))", ((cpp_function_code)(&finalizeOneClass)), NULL);
    defineFunctionObject("FINALIZE-CLASS", "(DEFUN (FINALIZE-CLASS BOOLEAN) ((CLASS CLASS)))", ((cpp_function_code)(&finalizeClass)), NULL);
    defineFunctionObject("HELP-FINALIZE-CLASS", "(DEFUN (HELP-FINALIZE-CLASS BOOLEAN) ((CLASS CLASS) (FINALIZEDPARENT TYPE)))", ((cpp_function_code)(&helpFinalizeClass)), NULL);
    defineFunctionObject("UNFINALIZE-CLASS-AND-SUBCLASSES", "(DEFUN UNFINALIZE-CLASS-AND-SUBCLASSES ((CLASS CLASS)))", ((cpp_function_code)(&unfinalizeClassAndSubclasses)), NULL);
    defineFunctionObject("ATTACH-SLOT-TO-OWNER", "(DEFUN (ATTACH-SLOT-TO-OWNER SLOT) ((NEWSLOT SLOT)) :PUBLIC? TRUE)", ((cpp_function_code)(&attachSlotToOwner)), NULL);
    defineFunctionObject("COMPUTE-SLOT-DIRECT-EQUIVALENT", "(DEFUN COMPUTE-SLOT-DIRECT-EQUIVALENT ((SELF SLOT)))", ((cpp_function_code)(&computeSlotDirectEquivalent)), NULL);
    defineFunctionObject("CHECK-CONFORMANCE-OF-SLOT-SIGNATURE", "(DEFUN CHECK-CONFORMANCE-OF-SLOT-SIGNATURE ((SELF SLOT)))", ((cpp_function_code)(&checkConformanceOfSlotSignature)), NULL);
    defineFunctionObject("COLLECTION-TO-ACTIVE-COLLECTION", "(DEFUN (COLLECTION-TO-ACTIVE-COLLECTION TYPE) ((TYPE TYPE)))", ((cpp_function_code)(&collectionToActiveCollection)), NULL);
    defineFunctionObject("ACTIVATE-SLOT", "(DEFUN ACTIVATE-SLOT ((SELF STORAGE-SLOT)))", ((cpp_function_code)(&activateSlot)), NULL);
    defineMethodObject("(DEFMETHOD FINALIZE-SLOT-TYPE-COMPUTATIONS ((SELF SLOT)))", wrapMethodCode(((cpp_method_code)(&Slot::finalizeSlotTypeComputations))), NULL);
    defineMethodObject("(DEFMETHOD FINALIZE-SLOT-TYPE-COMPUTATIONS ((SELF STORAGE-SLOT)))", wrapMethodCode(((cpp_method_code)(&StorageSlot::finalizeSlotTypeComputations))), NULL);
    defineFunctionObject("MULTI-VALUED-SLOT-WITH-DUPLICATES?", "(DEFUN (MULTI-VALUED-SLOT-WITH-DUPLICATES? BOOLEAN) ((SELF SLOT)))", ((cpp_function_code)(&multiValuedSlotWithDuplicatesP)), NULL);
    defineFunctionObject("COMPUTE-SLOT-INVERSES", "(DEFUN COMPUTE-SLOT-INVERSES ((SELF SLOT)))", ((cpp_function_code)(&computeSlotInverses)), NULL);
    defineMethodObject("(DEFMETHOD HELP-FINALIZE-LOCAL-SLOT ((SELF SLOT)))", wrapMethodCode(((cpp_method_code)(&Slot::helpFinalizeLocalSlot))), NULL);
    defineMethodObject("(DEFMETHOD HELP-FINALIZE-LOCAL-SLOT ((SELF STORAGE-SLOT)))", wrapMethodCode(((cpp_method_code)(&StorageSlot::helpFinalizeLocalSlot))), NULL);
    defineFunctionObject("FINALIZE-LOCAL-SLOT", "(DEFUN FINALIZE-LOCAL-SLOT ((SELF SLOT)))", ((cpp_function_code)(&finalizeLocalSlot)), NULL);
  }
}

void helpStartupClasses4() {
  {
    defineMethodObject("(DEFMETHOD UNFINALIZE-LOCAL-SLOT ((SELF SLOT)))", wrapMethodCode(((cpp_method_code)(&Slot::unfinalizeLocalSlot))), NULL);
    defineMethodObject("(DEFMETHOD UNFINALIZE-LOCAL-SLOT ((SELF STORAGE-SLOT)))", wrapMethodCode(((cpp_method_code)(&StorageSlot::unfinalizeLocalSlot))), NULL);
    defineFunctionObject("FINALIZE-CLASS-SLOTS", "(DEFUN FINALIZE-CLASS-SLOTS ((CLASS CLASS)))", ((cpp_function_code)(&finalizeClassSlots)), NULL);
    defineFunctionObject("UNFINALIZE-CLASS-SLOTS", "(DEFUN UNFINALIZE-CLASS-SLOTS ((CLASS CLASS)))", ((cpp_function_code)(&unfinalizeClassSlots)), NULL);
    defineFunctionObject("HELP-UNFINALIZE-CLASS-SLOTS", "(DEFUN HELP-UNFINALIZE-CLASS-SLOTS ((CLASS CLASS)))", ((cpp_function_code)(&helpUnfinalizeClassSlots)), NULL);
    defineMethodObject("(DEFMETHOD (MULTIPLE-PARENTS? BOOLEAN) ((CLASS CLASS)) :DOCUMENTATION \"Return `true' if `class' has more than one direct superclass.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Class::multipleParentsP))), NULL);
    defineFunctionObject("ADD-DIRECT-SUPERS-BACK-LINKS", "(DEFUN ADD-DIRECT-SUPERS-BACK-LINKS ((CLASS CLASS)))", ((cpp_function_code)(&addDirectSupersBackLinks)), NULL);
    defineFunctionObject("ADD-DIRECT-SUBS-BACK-LINKS", "(DEFUN ADD-DIRECT-SUBS-BACK-LINKS ((CLASS CLASS)))", ((cpp_function_code)(&addDirectSubsBackLinks)), NULL);
    defineFunctionObject("REMOVE-DIRECT-SUPERS-BACK-LINKS", "(DEFUN REMOVE-DIRECT-SUPERS-BACK-LINKS ((CLASS CLASS)))", ((cpp_function_code)(&removeDirectSupersBackLinks)), NULL);
    defineFunctionObject("COLLECT-DIRECT-SUPER-CLASSES", "(DEFUN COLLECT-DIRECT-SUPER-CLASSES ((CLASS CLASS) (PARENTS (LIST OF CLASS))))", ((cpp_function_code)(&collectDirectSuperClasses)), NULL);
    defineFunctionObject("INHERIT-SUPERCLASSES", "(DEFUN INHERIT-SUPERCLASSES ((CLASS CLASS)))", ((cpp_function_code)(&inheritSuperclasses)), NULL);
    defineFunctionObject("UNINHERIT-SUPERCLASSES", "(DEFUN UNINHERIT-SUPERCLASSES ((CLASS CLASS)))", ((cpp_function_code)(&uninheritSuperclasses)), NULL);
    defineFunctionObject("TWO-ARGUMENT-LEAST-COMMON-SUPERCLASS", "(DEFUN (TWO-ARGUMENT-LEAST-COMMON-SUPERCLASS CLASS) ((CLASS1 CLASS) (CLASS2 CLASS)) :DOCUMENTATION \"Return the most specific class that is a superclass of\nboth `class1' and `class2'.  If there is more than one, arbitrarily pick one.\nIf there is none, return `null'.\")", ((cpp_function_code)(&twoArgumentLeastCommonSuperclass)), NULL);
    defineFunctionObject("TWO-ARGUMENT-LEAST-COMMON-SUPERTYPE", "(DEFUN (TWO-ARGUMENT-LEAST-COMMON-SUPERTYPE TYPE-SPEC) ((TYPE1 TYPE-SPEC) (TYPE2 TYPE-SPEC)) :DOCUMENTATION \"Return the most specific type that is a supertype of\nboth `type1' and `type2'.  If there is more than one, arbitrarily pick one.\nIf there is none, return @VOID.  If one or both types are parametric,\nalso try to generalize parameter types if necessary.\")", ((cpp_function_code)(&twoArgumentLeastCommonSupertype)), NULL);
    defineFunctionObject("INHERIT-SLOTS", "(DEFUN INHERIT-SLOTS ((CLASS CLASS)))", ((cpp_function_code)(&inheritSlots)), NULL);
    defineFunctionObject("LOCAL-SLOT?", "(DEFUN (LOCAL-SLOT? BOOLEAN) ((SLOT SLOT) (CLASS CLASS)))", ((cpp_function_code)(&localSlotP)), NULL);
    defineFunctionObject("UNINHERIT-SLOTS", "(DEFUN UNINHERIT-SLOTS ((CLASS CLASS)))", ((cpp_function_code)(&uninheritSlots)), NULL);
    defineFunctionObject("INITIALIZE-SLOT-AND-METHOD-CACHE", "(DEFUN INITIALIZE-SLOT-AND-METHOD-CACHE ((CLASS CLASS)))", ((cpp_function_code)(&initializeSlotAndMethodCache)), NULL);
    defineFunctionObject("REGISTER-SLOT-NAME", "(DEFUN REGISTER-SLOT-NAME ((SLOT SLOT)) :PUBLIC? TRUE :DOCUMENTATION \"Register the name symbol of `slot' as a slot name, and\ninitialize its `symbol-slot-offset' so that it can be used by `lookup-slot'.\")", ((cpp_function_code)(&registerSlotName)), NULL);
    defineFunctionObject("UNREGISTER-SLOT-NAME", "(DEFUN UNREGISTER-SLOT-NAME ((SLOT SLOT)) :PUBLIC? TRUE :DOCUMENTATION \"Unregister the name symbol of `slot' as a slot name,\nso that it can no longer be used by `lookup-slot'.\")", ((cpp_function_code)(&unregisterSlotName)), NULL);
    defineFunctionObject("REGISTERED-SLOT-NAME?", "(DEFUN (REGISTERED-SLOT-NAME? BOOLEAN) ((SLOT-NAME SYMBOL)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Return `true' if `slot-name' is the name of some registered;\nslot in the system.\" (RETURN (DEFINED? (SYMBOL-SLOT-OFFSET SLOT-NAME))))", ((cpp_function_code)(&registeredSlotNameP)), NULL);
    defineFunctionObject("WARN-ABOUT-SLOT-SHADOWED-BY-A-FUNCTION?", "(DEFUN (WARN-ABOUT-SLOT-SHADOWED-BY-A-FUNCTION? BOOLEAN) ((SLOT SLOT)))", ((cpp_function_code)(&warnAboutSlotShadowedByAFunctionP)), NULL);
    defineFunctionObject("WARN-ABOUT-FUNCTION-SHADOWING-SLOTS?", "(DEFUN (WARN-ABOUT-FUNCTION-SHADOWING-SLOTS? BOOLEAN) ((FUNCTION METHOD-SLOT)))", ((cpp_function_code)(&warnAboutFunctionShadowingSlotsP)), NULL);
    defineFunctionObject("LOOKUP-SLOT", "(DEFUN (LOOKUP-SLOT SLOT) ((CLASS CLASS) (SLOT-NAME SYMBOL)) :DOCUMENTATION \"Return a slot owned by the class `class' with name `slot-name'.\nMultiply inherited slots are disambiguated by a left-to-right class\nprecedence order for classes with multiple parents (similar to CLOS).\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupSlot)), NULL);
    defineFunctionObject("SAFE-LOOKUP-SLOT", "(DEFUN (SAFE-LOOKUP-SLOT SLOT) ((CLASS CLASS) (SLOT-NAME SYMBOL)) :DOCUMENTATION \"Alias for `lookup-slot'.  Kept for backwards compatibility.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (LOOKUP-SLOT CLASS SLOT-NAME)))", ((cpp_function_code)(&safeLookupSlot)), NULL);
    defineFunctionObject("LOOKUP-VISIBLE-SLOT", "(DEFUN (LOOKUP-VISIBLE-SLOT SLOT) ((CLASS CLASS) (SLOT-NAME OBJECT)))", ((cpp_function_code)(&lookupVisibleSlot)), NULL);
    defineFunctionObject("LOOKUP-LOCAL-SLOT", "(DEFUN (LOOKUP-LOCAL-SLOT SLOT) ((CLASS CLASS) (SLOT-NAME SYMBOL)) :DOCUMENTATION \"Lookup a local slot with `slot-name' on `class'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupLocalSlot)), NULL);
    defineFunctionObject("CLEAR-SLOT-AND-METHOD-CACHE", "(DEFUN CLEAR-SLOT-AND-METHOD-CACHE ((CLASS CLASS)))", ((cpp_function_code)(&clearSlotAndMethodCache)), NULL);
    defineFunctionObject("RESIZE-SLOT-CACHES", "(DEFUN RESIZE-SLOT-CACHES ((SIZE INTEGER)) :DOCUMENTATION \"Reset all slot caches to have size `size'.\")", ((cpp_function_code)(&resizeSlotCaches)), NULL);
    defineFunctionObject("GET-SLOT", "(DEFUN (GET-SLOT SLOT) ((SELF STANDARD-OBJECT) (SLOT-NAME SYMBOL)) :DOCUMENTATION \"Return the slot named `slot-name' on the class\nrepresenting the type of `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getSlot)), NULL);
    defineFunctionObject("LOOKUP-SLOT-AND-CLASS-BY-QUALIFIED-NAME", "(DEFUN (LOOKUP-SLOT-AND-CLASS-BY-QUALIFIED-NAME SLOT CLASS) ((QUALIFIEDNAME STRING)) :DOCUMENTATION \"Lookup a slot via dotted notation with a possibly qualified class name.\nExamples: \\\"cons.first\\\" or \\\"stella/cons.first\\\".  This is a variant of `string-to-slot'\nin describe.ste that actually obeys the class module if it is given.  This also returns\nthe specified class as a second value which might differ from the slot's owner class.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupSlotAndClassByQualifiedName)), NULL);
    defineFunctionObject("LOOKUP-SLOT-BY-QUALIFIED-NAME", "(DEFUN (LOOKUP-SLOT-BY-QUALIFIED-NAME SLOT) ((QUALIFIEDNAME STRING)) :DOCUMENTATION \"Lookup a slot via dotted notation with a possibly qualified class name.\nExamples: \\\"cons.first\\\" or \\\"stella/cons.first\\\".  This is a variant of `string-to-slot'\nin describe.ste that actually obeys the class module if it is given.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupSlotByQualifiedName)), NULL);
    defineFunctionObject("CONFORMING-TYPE-SPEC?", "(DEFUN (CONFORMING-TYPE-SPEC? BOOLEAN) ((SUB-TYPE-SPEC TYPE-SPEC) (SUPER-TYPE-SPEC TYPE-SPEC)))", ((cpp_function_code)(&conformingTypeSpecP)), NULL);
    defineMethodObject("(DEFMETHOD (CONFORMING-SIGNATURES? BOOLEAN) ((SELF SLOT) (SUPERSLOT SLOT)))", wrapMethodCode(((cpp_method_code)(&Slot::conformingSignaturesP))), NULL);
    defineMethodObject("(DEFMETHOD (CONFORMING-SIGNATURES? BOOLEAN) ((SELF STORAGE-SLOT) (SUPERSLOT SLOT)))", wrapMethodCode(((cpp_method_code)(&StorageSlot::conformingSignaturesP))), NULL);
    defineMethodObject("(DEFMETHOD (CONFORMING-SIGNATURES? BOOLEAN) ((SELF METHOD-SLOT) (SUPERSLOT SLOT)))", wrapMethodCode(((cpp_method_code)(&MethodSlot::conformingSignaturesP))), NULL);
    defineMethodObject("(DEFMETHOD (CONFORMING-SIGNATURES? BOOLEAN) ((SELF TABLE) (SUPERSLOT SLOT)))", wrapMethodCode(((cpp_method_code)(&Table::conformingSignaturesP))), NULL);
    defineFunctionObject("IDENTICAL-SIGNATURES?", "(DEFUN (IDENTICAL-SIGNATURES? BOOLEAN) ((METHOD1 METHOD-SLOT) (METHOD2 METHOD-SLOT)))", ((cpp_function_code)(&identicalSignaturesP)), NULL);
    defineFunctionObject("COMPUTE-REQUIRED-SLOT-NAMES", "(DEFUN COMPUTE-REQUIRED-SLOT-NAMES ((CLASS CLASS)))", ((cpp_function_code)(&computeRequiredSlotNames)), NULL);
    defineFunctionObject("FREE-REQUIRED-SLOT-NAMES", "(DEFUN FREE-REQUIRED-SLOT-NAMES ((CLASS CLASS)))", ((cpp_function_code)(&freeRequiredSlotNames)), NULL);
    defineMethodObject("(DEFMETHOD (DYNAMIC-STORAGE? BOOLEAN) ((SELF STORAGE-SLOT)))", wrapMethodCode(((cpp_method_code)(&StorageSlot::dynamicStorageP))), NULL);
    defineMethodObject("(DEFMETHOD (PRIVATE? BOOLEAN) ((SELF RELATION)) :DOCUMENTATION \"Return `true' if `self' is not public.\" :PUBLIC? TRUE :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Relation::privateP))), NULL);
    defineMethodObject("(DEFMETHOD (PUBLIC? BOOLEAN) ((SELF SLOT)) :DOCUMENTATION \"True if `self' or one it its ancestors is marked public.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Slot::publicP))), NULL);
    defineMethodObject("(DEFMETHOD (PUBLIC-SLOTS (ITERATOR OF SLOT)) ((SELF CLASS)) :DOCUMENTATION \"Return an iterator over public slots of `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Class::publicSlots))), NULL);
    defineMethodObject("(DEFMETHOD (PUBLIC-SLOTS (ITERATOR OF SLOT)) ((SELF OBJECT)) :DOCUMENTATION \"Return an iterator over public slots of `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Object::publicSlots))), NULL);
    defineMethodObject("(DEFMETHOD (ALL-CLASS-SLOTS (ITERATOR OF SLOT)) ((SELF CLASS)))", wrapMethodCode(((cpp_method_code)(&Class::allClassSlots))), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF ALL-CLASS-SLOTS-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&AllClassSlotsIterator::nextP))), NULL);
    defineMethodObject("(DEFMETHOD (CLASS-SLOTS (ITERATOR OF SLOT)) ((SELF CLASS)))", wrapMethodCode(((cpp_method_code)(&Class::classSlots))), NULL);
    defineMethodObject("(DEFMETHOD (LOCAL-SLOTS (LIST OF SLOT)) ((SELF CLASS)))", wrapMethodCode(((cpp_method_code)(&Class::localSlots))), NULL);
    defineMethodObject("(DEFMETHOD (DIRECT-SUPER-CLASSES (ITERATOR OF CLASS)) ((SELF CLASS)) :DOCUMENTATION \"Returns an iterator that generates all direct super classes of `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Class::directSuperClasses))), NULL);
    defineMethodObject("(DEFMETHOD (SUPER-CLASSES (ITERATOR OF CLASS)) ((SELF CLASS)) :DOCUMENTATION \"Returns an iterator that generates all proper super classes of `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Class::superClasses))), NULL);
    defineMethodObject("(DEFMETHOD (ACTIVE? BOOLEAN) ((SLOT SLOT)))", wrapMethodCode(((cpp_method_code)(&Slot::activeP))), NULL);
    defineMethodObject("(DEFMETHOD (INITIAL-VALUE OBJECT) ((SELF STORAGE-SLOT)) :DOCUMENTATION \"Return an initial value for `self', or `null'.  The\ninitial value can be defined by the slot itself, inherited from an\nequivalent slot, or inherit from the :initial-value option for the \nclass representing the type of `self'.\")", wrapMethodCode(((cpp_method_code)(&StorageSlot::initialValue))), NULL);
    defineMethodObject("(DEFMETHOD (SYSTEM-DEFAULT-VALUE OBJECT) ((SELF SLOT)) :DOCUMENTATION \"Return a default value expression, or if `self'\nhas dynamic storage, an initial value expression.\")", wrapMethodCode(((cpp_method_code)(&Slot::systemDefaultValue))), NULL);
    defineMethodObject("(DEFMETHOD (SYSTEM-DEFAULT-VALUE OBJECT) ((SELF STORAGE-SLOT)) :DOCUMENTATION \"Return a default value expression, or if `self'\nhas dynamic storage, an initial value expression.\")", wrapMethodCode(((cpp_method_code)(&StorageSlot::systemDefaultValue))), NULL);
    defineMethodObject("(DEFMETHOD (INITIALLY OBJECT) ((SELF STORAGE-SLOT)) :DOCUMENTATION \"Defines the value of a slot before it has been assigned\na value.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StorageSlot::initially))), NULL);
    defineFunctionObject("REPAIR-SLOTS", "(DEFUN REPAIR-SLOTS ())", ((cpp_function_code)(&repairSlots)), NULL);
    defineFunctionObject("DISCONNECT-CLASSES", "(DEFUN DISCONNECT-CLASSES ())", ((cpp_function_code)(&disconnectClasses)), NULL);
    defineFunctionObject("FILTER-UNBOUND-SURROGATE?", "(DEFUN (FILTER-UNBOUND-SURROGATE? BOOLEAN) ((SELF SURROGATE) (ITERATOR ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&filterUnboundSurrogateP)), NULL);
    defineFunctionObject("UNBOUND-SURROGATES", "(DEFUN (UNBOUND-SURROGATES (ITERATOR OF SURROGATE)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :PUBLIC? TRUE :DOCUMENTATION \"Iterate over all unbound surrogates visible from `module'.\nLook at all modules if `module' is `null'.  If `local?', only consider\nsurrogates interned in `module'.\")", ((cpp_function_code)(&unboundSurrogates)), NULL);
  }
}

void startupClasses() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupClasses1();
      helpStartupClasses2();
    }
    if (currentStartupTimePhaseP(4)) {
      oUNFINALIZED_CLASSESo = newList();
      oCLASSES_WITH_UNRESOLVED_CHILDREN_REFERENCESo = newList();
      oCLASS_TAXONOMY_GRAPHo = newTaxonomyGraph();
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("ALL-CLASS-SLOTS-ITERATOR", "(DEFCLASS ALL-CLASS-SLOTS-ITERATOR (ITERATOR) :PARAMETERS ((ANY-VALUE :TYPE SLOT)) :SLOTS ((ITERATOR-CONS-LIST :TYPE CONS) (ITERATOR-OBJECT :TYPE OBJECT)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newAllClassSlotsIterator));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessAllClassSlotsIteratorSlotValue));
      }
      defineStellaTypeFromStringifiedSource("(DEFTYPE ANY UNKNOWN)");
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupClasses3();
      helpStartupClasses4();
      defineFunctionObject("NAME-TO-STRING", "(DEFUN (NAME-TO-STRING STRING) ((NAME OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Return the string represented by `name'.  Return `null'\nif `name' is undefined or does not represent a string.\")", ((cpp_function_code)(&nameToString)), NULL);
      defineFunctionObject("PRINT-UNBOUND-SURROGATES", "(DEFUN PRINT-UNBOUND-SURROGATES (|&REST| (ARGS OBJECT)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Print all unbound surrogates visible from the module named by the first\nargument (a symbol or string).  Look at all modules if no module name or\n`null' was supplied.  If the second argument is `true', only consider\nsurrogates interned in the specified module.\")", ((cpp_function_code)(&printUnboundSurrogates)), ((cpp_function_code)(&printUnboundSurrogatesEvaluatorWrapper)));
      defineFunctionObject("COERCE-TO-SYMBOL", "(DEFUN (COERCE-TO-SYMBOL GENERALIZED-SYMBOL) ((NAME NAME)) :PUBLIC? TRUE :DOCUMENTATION \"Return the (generalized) symbol represented by `name'.\nReturn `null' if `name' is undefined or does not represent a string.\")", ((cpp_function_code)(&coerceToSymbol)), NULL);
      defineFunctionObject("PRINT-UNDEFINED-SUPER-CLASSES", "(DEFUN PRINT-UNDEFINED-SUPER-CLASSES ((CLASS NAME)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Print all undefined or bad (indirect) super classes of `class'.\")", ((cpp_function_code)(&printUndefinedSuperClasses)), NULL);
      defineFunctionObject("COLLECT-BAD-SUPER-CLASSES", "(DEFUN (COLLECT-BAD-SUPER-CLASSES (LIST OF TYPE)) ((TYPE TYPE) (BADONES (LIST OF TYPE))) :PUBLIC? TRUE)", ((cpp_function_code)(&collectBadSuperClasses)), NULL);
      defineFunctionObject("ROOT-CLASS?", "(DEFUN (ROOT-CLASS? BOOLEAN) ((CLASS CLASS)))", ((cpp_function_code)(&rootClassP)), NULL);
      defineFunctionObject("CREATE-CLASS-TAXONOMY", "(DEFUN CREATE-CLASS-TAXONOMY ())", ((cpp_function_code)(&createClassTaxonomy)), NULL);
      defineFunctionObject("SUBCLASS-OF?", "(DEFUN (SUBCLASS-OF? BOOLEAN) ((SUBCLASS CLASS) (SUPERCLASS CLASS)) :DOCUMENTATION \"Return `true' if `subClass' is a subclass of `superClass'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&subclassOfP)), NULL);
      defineFunctionObject("FAST-SUBCLASS-OF?", "(DEFUN (FAST-SUBCLASS-OF? BOOLEAN) ((SUBCLASS CLASS) (SUPERCLASS CLASS)))", ((cpp_function_code)(&fastSubclassOfP)), NULL);
      defineFunctionObject("SUBTYPE-OF?", "(DEFUN (SUBTYPE-OF? BOOLEAN) ((SUB-TYPE TYPE) (SUPER-TYPE TYPE)) :DOCUMENTATION \"Return `true' iff the class named `sub-type' is a subclass \nof the class named `super-type'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&subtypeOfP)), NULL);
      defineFunctionObject("ISA?", "(DEFUN (ISA? BOOLEAN) ((OBJECT OBJECT) (TYPE TYPE)) :DOCUMENTATION \"Return `true' iff `object' is an instance of the class named `type'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&isaP)), NULL);
      defineFunctionObject("TAXONOMY-SUBCLASS-OF?", "(DEFUN (TAXONOMY-SUBCLASS-OF? BOOLEAN) ((SUBCLASS CLASS) (SUPERCLASS CLASS)) :GLOBALLY-INLINE? TRUE (RETURN (SUBCLASS-OF? SUBCLASS SUPERCLASS)))", ((cpp_function_code)(&taxonomySubclassOfP)), NULL);
      defineFunctionObject("TAXONOMY-ISA?", "(DEFUN (TAXONOMY-ISA? BOOLEAN) ((OBJECT OBJECT) (TYPE TYPE)) :GLOBALLY-INLINE? TRUE (RETURN (ISA? OBJECT TYPE)))", ((cpp_function_code)(&taxonomyIsaP)), NULL);
      defineFunctionObject("INTERN-SLOTREF", "(DEFUN (INTERN-SLOTREF SLOTREF) ((CLASSNAME STRING) (SLOTNAME STRING)))", ((cpp_function_code)(&internSlotref)), NULL);
      defineFunctionObject("LOOKUP-SLOTREF", "(DEFUN (LOOKUP-SLOTREF SLOTREF) ((SELF TYPE) (SLOTNAME SYMBOL)) :PUBLIC? TRUE)", ((cpp_function_code)(&lookupSlotref)), NULL);
      defineFunctionObject("SLOTREF?", "(DEFUN (SLOTREF? BOOLEAN) ((SELF SURROGATE)))", ((cpp_function_code)(&slotrefP)), NULL);
      defineFunctionObject("LOOKUP-SLOT-FROM-SLOTREF", "(DEFUN (LOOKUP-SLOT-FROM-SLOTREF SLOT) ((SLOTREF SLOTREF)))", ((cpp_function_code)(&lookupSlotFromSlotref)), NULL);
      defineFunctionObject("SLOTREF-TYPE", "(DEFUN (SLOTREF-TYPE TYPE) ((SLOTREF SLOTREF)))", ((cpp_function_code)(&slotrefType)), NULL);
      defineFunctionObject("STARTUP-CLASSES", "(DEFUN STARTUP-CLASSES () :PUBLIC? TRUE)", ((cpp_function_code)(&startupClasses)), NULL);
      { MethodSlot* function = lookupFunction(SYM_CLASSES_STELLA_STARTUP_CLASSES);

        setDynamicSlotValue(function->dynamicSlots, SYM_CLASSES_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupClasses"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFSPECIAL *WARNIFREDEFINE?* BOOLEAN TRUE :DOCUMENTATION \"If set, warn about each redefinition.\" :PUBLIC? TRUE)", &oWARNIFREDEFINEpo);
      defineGlobalVariableObject("(DEFGLOBAL *UNFINALIZED-CLASSES* (LIST OF CLASS) (NEW LIST) :DOCUMENTATION \"List of classes whose class or slot inheritance is\ncurrently unfinalized.\")", &oUNFINALIZED_CLASSESo);
      defineGlobalVariableObject("(DEFGLOBAL *NEWLY-UNFINALIZED-CLASSES?* BOOLEAN FALSE :DOCUMENTATION \"Set to `true' by `remember-unfinalized-class'; set\nto `false' by `cleanup-unfinalized-classes'.  Minimizes the time that\n`finalize-classes' spends searching for classes to finalize.\")", &oNEWLY_UNFINALIZED_CLASSESpo);
      defineGlobalVariableObject("(DEFGLOBAL *CLASSES-WITH-UNRESOLVED-CHILDREN-REFERENCES* (LIST OF CLASS) (NEW LIST) :DOCUMENTATION \"List of classes defined with a :children option\nwhich still have some of their children references unresolved.\")", &oCLASSES_WITH_UNRESOLVED_CHILDREN_REFERENCESo);
      defineGlobalVariableObject("(DEFGLOBAL *SYMBOL-SLOT-OFFSET-COUNTER* INTEGER 0)", &oSYMBOL_SLOT_OFFSET_COUNTERo);
      defineGlobalVariableObject("(DEFGLOBAL *SLOT-CACHE-SIZE* INTEGER 20)", &oSLOT_CACHE_SIZEo);
      defineGlobalVariableObject("(DEFGLOBAL *CLASS-TAXONOMY-GRAPH* TAXONOMY-GRAPH (NEW TAXONOMY-GRAPH))", &oCLASS_TAXONOMY_GRAPHo);
    }
  }
}

Surrogate* SGT_CLASSES_STELLA_CLASS = NULL;

Surrogate* SGT_CLASSES_STELLA_OBJECT = NULL;

Keyword* KWD_CLASSES_PUBLICp = NULL;

Keyword* KWD_CLASSES_PARAMETERS = NULL;

Symbol* SYM_CLASSES_STELLA_SLOT_TYPE_SPECIFIER = NULL;

Keyword* KWD_CLASSES_REQUIREDp = NULL;

Keyword* KWD_CLASSES_COMPONENTp = NULL;

Keyword* KWD_CLASSES_READ_ONLYp = NULL;

Keyword* KWD_CLASSES_ACTIVEp = NULL;

Symbol* SYM_CLASSES_STELLA_STORED_ACTIVEp = NULL;

Keyword* KWD_CLASSES_CONTEXT_SENSITIVEp = NULL;

Keyword* KWD_CLASSES_HARDWIREDp = NULL;

Keyword* KWD_CLASSES_ABSTRACTp = NULL;

Keyword* KWD_CLASSES_ALLOCATION = NULL;

Keyword* KWD_CLASSES_CLASS = NULL;

Symbol* SYM_CLASSES_STELLA_SLOT_ALLOCATION = NULL;

Keyword* KWD_CLASSES_INITIALLY = NULL;

Symbol* SYM_CLASSES_STELLA_SLOT_INITIAL_VALUE = NULL;

Keyword* KWD_CLASSES_DEFAULT = NULL;

Symbol* SYM_CLASSES_STELLA_SLOT_DEFAULT_EXPRESSION = NULL;

Keyword* KWD_CLASSES_READER = NULL;

Symbol* SYM_CLASSES_STELLA_SLOT_READER = NULL;

Keyword* KWD_CLASSES_WRITER = NULL;

Symbol* SYM_CLASSES_STELLA_SLOT_WRITER = NULL;

Keyword* KWD_CLASSES_INVERSE = NULL;

Symbol* SYM_CLASSES_STELLA_SLOT_INVERSE = NULL;

Keyword* KWD_CLASSES_RENAMES = NULL;

Symbol* SYM_CLASSES_STELLA_SLOT_RENAMES = NULL;

Keyword* KWD_CLASSES_DOCUMENTATION = NULL;

Symbol* SYM_CLASSES_STELLA_DOCUMENTATION = NULL;

Keyword* KWD_CLASSES_PROPERTIES = NULL;

Symbol* SYM_CLASSES_STELLA_PROPERTIES = NULL;

Keyword* KWD_CLASSES_META_ATTRIBUTES = NULL;

Symbol* SYM_CLASSES_STELLA_META_ATTRIBUTES = NULL;

Keyword* KWD_CLASSES_OPTION_KEYWORD = NULL;

Symbol* SYM_CLASSES_STELLA_SLOT_OPTION_KEYWORD = NULL;

Keyword* KWD_CLASSES_OPTION_HANDLER = NULL;

Symbol* SYM_CLASSES_STELLA_SLOT_OPTION_HANDLER = NULL;

Surrogate* SGT_CLASSES_STELLA_BOOLEAN = NULL;

Keyword* KWD_CLASSES_BIT = NULL;

Keyword* KWD_CLASSES_CL_NATIVE_TYPE = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_CL_NATIVE_TYPE = NULL;

Keyword* KWD_CLASSES_CPP_NATIVE_TYPE = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_CPP_NATIVE_TYPE = NULL;

Keyword* KWD_CLASSES_IDL_NATIVE_TYPE = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_IDL_NATIVE_TYPE = NULL;

Keyword* KWD_CLASSES_JAVA_NATIVE_TYPE = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_JAVA_NATIVE_TYPE = NULL;

Keyword* KWD_CLASSES_CL_STRUCTp = NULL;

Keyword* KWD_CLASSES_MIXINp = NULL;

Keyword* KWD_CLASSES_RECYCLE_METHOD = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_RECYCLE_METHOD = NULL;

Keyword* KWD_CLASSES_EXTENSION = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_EXTENSION_NAME = NULL;

Keyword* KWD_CLASSES_CREATOR = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_CREATOR = NULL;

Keyword* KWD_CLASSES_INITIALIZER = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_INITIALIZER = NULL;

Keyword* KWD_CLASSES_TERMINATOR = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_TERMINATOR = NULL;

Keyword* KWD_CLASSES_DESTRUCTOR = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_DESTRUCTOR = NULL;

Keyword* KWD_CLASSES_INITIAL_VALUE = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_INITIAL_VALUE = NULL;

Keyword* KWD_CLASSES_PRINT_FORM = NULL;

Symbol* SYM_CLASSES_STELLA_PRINT_FORM = NULL;

Keyword* KWD_CLASSES_EQUALITY_TEST = NULL;

Keyword* KWD_CLASSES_KEY = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_KEY = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_PARAMETERS = NULL;

Keyword* KWD_CLASSES_SYNONYMS = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_SYNONYMS = NULL;

Keyword* KWD_CLASSES_CHILDREN = NULL;

Surrogate* SGT_CLASSES_STELLA_METHOD_SLOT = NULL;

Symbol* SYM_CLASSES_STELLA_SLOT_GUARD_DEMONS = NULL;

Symbol* SYM_CLASSES_STELLA_SLOT_DEMONS = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_CONSTRUCTOR_DEMONS = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_GUARD_CONSTRUCTOR_DEMONS = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_DESTRUCTOR_DEMONS = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_GUARD_DESTRUCTOR_DEMONS = NULL;

Surrogate* SGT_CLASSES_STELLA_ACTIVE_OBJECT = NULL;

Surrogate* SGT_CLASSES_STELLA_STANDARD_OBJECT = NULL;

Symbol* SYM_CLASSES_STELLA_PRIMARY_TYPE = NULL;

Symbol* SYM_CLASSES_STELLA_SELF = NULL;

Keyword* KWD_CLASSES_TYPE = NULL;

Symbol* SYM_CLASSES_STELLA_TYPE = NULL;

Keyword* KWD_CLASSES_AUXILIARYp = NULL;

Symbol* SYM_CLASSES_STELLA_TRUE = NULL;

Symbol* SYM_CLASSES_STELLA_RETURN = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_EXTENSION = NULL;

Symbol* SYM_CLASSES_STELLA_BADp = NULL;

Surrogate* SGT_CLASSES_STELLA_SET = NULL;

Surrogate* SGT_CLASSES_STELLA_ACTIVE_SET = NULL;

Surrogate* SGT_CLASSES_STELLA_LIST = NULL;

Surrogate* SGT_CLASSES_STELLA_ACTIVE_LIST = NULL;

Surrogate* SGT_CLASSES_STELLA_UNKNOWN = NULL;

Surrogate* SGT_CLASSES_STELLA_COLLECTION = NULL;

Surrogate* SGT_CLASSES_STELLA_SET_MIXIN = NULL;

Symbol* SYM_CLASSES_STELLA_INVERSE = NULL;

Keyword* KWD_CLASSES_DYNAMIC = NULL;

Surrogate* SGT_CLASSES_STELLA_DYNAMIC_SLOTS_MIXIN = NULL;

Keyword* KWD_CLASSES_INSTANCE = NULL;

Surrogate* SGT_CLASSES_STELLA_CONTEXT_SENSITIVE_OBJECT = NULL;

Surrogate* SGT_CLASSES_STELLA_CONTEXT_SENSITIVE_MIXIN = NULL;

Surrogate* SGT_CLASSES_STELLA_VOID = NULL;

Symbol* SYM_CLASSES_STELLA_METHOD_MACROp = NULL;

Surrogate* SGT_CLASSES_STELLA_TABLE = NULL;

Symbol* SYM_CLASSES_STELLA_CLASS_REQUIRED_SLOT_NAMES = NULL;

Surrogate* SGT_CLASSES_STELLA_ALL_CLASS_SLOTS_ITERATOR = NULL;

Symbol* SYM_CLASSES_STELLA_ITERATOR_CONS_LIST = NULL;

Symbol* SYM_CLASSES_STELLA_ITERATOR_OBJECT = NULL;

Symbol* SYM_CLASSES_STELLA_FALSE = NULL;

Surrogate* SGT_CLASSES_STELLA_GENERALIZED_SYMBOL = NULL;

Symbol* SYM_CLASSES_STELLA_ANY = NULL;

Surrogate* SGT_CLASSES_STELLA_ANY = NULL;

Surrogate* SGT_CLASSES_STELLA_SLOT = NULL;

Symbol* SYM_CLASSES_STELLA_STARTUP_CLASSES = NULL;

Symbol* SYM_CLASSES_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
