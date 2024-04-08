//  -*- Mode: C++ -*-

// stella-in.cc

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

// If `true', always redefine classes, even if an
//                   identical class exists
boolean oREDEFINE_IDENTICAL_CLASSESpo = false;

Object* permanentifyForm(Object* form) {
  { Surrogate* testValue000 = safePrimaryType(form);

    if (subtypeOfSymbolP(testValue000)) {
      { Object* form000 = form;
        Symbol* form = ((Symbol*)(form000));

        if (form == SYM_STELLA_IN_STELLA_TRUE) {
          return (form);
        }
        else if (form == SYM_STELLA_IN_STELLA_FALSE) {
          return (form);
        }
        else {
          return (((Symbol*)(form->permanentify())));
        }
      }
    }
    else if (testValue000 == SGT_STELLA_IN_STELLA_CONS) {
      { Object* form001 = form;
        Cons* form = ((Cons*)(form001));

        return (permanentCopy(form));
      }
    }
    else {
      return (form->permanentify());
    }
  }
}

Object* transientifyForm(Object* form) {
  return (copyConsTree(form));
}

const char* stringifyInModule(Object* tree, Module* module) {
  // Stringify a parse `tree' relative to `module', or
  // `*module*' if no module is specified.
  if (!((boolean)(module))) {
    module = oMODULEo;
  }
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, module);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    return (stringify(tree));
  }
}

Object* unstringifyInModule(const char* string, Module* module) {
  // Unstringify relative to `module', or `*MODULE*' if no
  // module is specified.
  if (!((boolean)(module))) {
    module = oMODULEo;
  }
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, module);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    return (readSExpressionFromString(string));
  }
}

Object* unstringifyStellaSource(const char* source, Module* module) {
  // Unstringify a STELLA `source' string relative to `module',
  // or `*MODULE*' if no module is specified.  This function allocates transient
  // objects as opposed to `unstringify-in-module' or the regular `unstringify'.
  { Object* result = NULL;

    { 
      BIND_STELLA_SPECIAL(oTRANSIENTOBJECTSpo, boolean, true);
      result = unstringifyInModule(source, module);
    }
    return (result);
  }
}

List* collectFeatureList(Object* tree) {
  if (safePrimaryType(tree) == SGT_STELLA_IN_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      { List* result = NULL;

        if (tree->length() > 0) {
          result = newList();
        }
        { Object* feature = NULL;
          Cons* iter000 = tree;
          Cons* collect000 = NULL;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest) {
            feature = iter000->value;
            if (!isaP(feature, SGT_STELLA_IN_STELLA_GENERALIZED_SYMBOL)) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Ignoring illegal feature " << "`" << deUglifyParseTree(feature) << "'" << " in feature list: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
                }
              }
              continue;
            }
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(feature->permanentify(), NIL);
                if (result->theConsList == NIL) {
                  result->theConsList = collect000;
                }
                else {
                  addConsToEndOfConsList(result->theConsList, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(feature->permanentify(), NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        return (result);
      }
    }
  }
  else {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal atomic feature list: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
      }
    }
    return (NULL);
  }
}

KeyValueList* collectKeyValueList(Object* tree) {
  if (safePrimaryType(tree) == SGT_STELLA_IN_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      { int length = tree->length();
        Cons* cursor = tree;
        Object* key = NULL;
        Object* value = NULL;
        KeyValueList* result = NULL;

        if (length == 0) {
          return (NULL);
        }
        if ((length % 2)) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Unbalanced keys and values in key-value list: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
            }
          }
          return (NULL);
        }
        result = newKeyValueList();
        while (!(cursor == NIL)) {
          key = cursor->value;
          value = cursor->rest->value;
          cursor = cursor->rest->rest;
          if (!isaP(key, SGT_STELLA_IN_STELLA_GENERALIZED_SYMBOL)) {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Ignoring illegal key " << "`" << deUglifyParseTree(key) << "'" << " in key-value list: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
              }
            }
            continue;
          }
          if ((value == SYM_STELLA_IN_STELLA_TRUE) ||
              (value == SYM_STELLA_IN_STELLA_FALSE)) {
            value = coerceToBoolean(value);
          }
          else {
            value = permanentCopy(value);
          }
          result->insertAt(key->permanentify(), value);
        }
        return (result);
      }
    }
  }
  else {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal atomic key-value list: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
      }
    }
    return (NULL);
  }
}

MethodSlot* defineInlineMethod(Symbol* name, Cons* parametersandbody) {
  { boolean dummy1;

    { Cons* parsetree = NULL;
      MethodSlot* method = NULL;

      parsetree = listO(3, SYM_STELLA_IN_STELLA_DEFMETHOD, name, parametersandbody->concatenate(NIL, 0));
      method = helpDefineMethodFromParseTree(parsetree, stringify(parsetree), dummy1);
      return (method);
    }
  }
}

Class* helpDefineClassFromParseTree(Cons* parsetree, const char* stringifiedsource) {
  { Cons* treedefinition = parsetree->rest;
    Cons* thesupers = ((Cons*)(treedefinition->rest->value));
    PropertyList* theoptions = newPropertyList();
    Surrogate* classtype = typify(treedefinition->value);
    List* directsupers = newList();
    List* slots = newList();
    KeywordKeyValueList* classoptions = newKeywordKeyValueList();
    Keyword* key = NULL;
    List* parameters = NULL;
    Cons* slottree = NULL;

    theoptions->thePlist = treedefinition->rest->rest;
    { Object* s = NULL;
      Cons* iter000 = thesupers;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        s = iter000->value;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(typify(s), NIL);
            if (directsupers->theConsList == NIL) {
              directsupers->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(directsupers->theConsList, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(typify(s), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    { Object* thekey = NULL;
      Object* thevalue = NULL;
      Cons* iter001 = theoptions->thePlist;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest->rest) {
        thekey = iter001->value;
        thevalue = iter001->rest->value;
        key = ((Keyword*)(thekey->permanentify()));
        if ((key == KWD_STELLA_IN_PUBLIC_SLOTS) ||
            (key == KWD_STELLA_IN_SLOTS)) {
          { Slot* localslot = NULL;

            { Object* slotdef = NULL;
              Cons* iter002 = ((Cons*)(thevalue));
              Cons* collect001 = NULL;

              for  (; !(iter002 == NIL); 
                    iter002 = iter002->rest) {
                slotdef = iter002->value;
                if (!consP(slotdef)) {
                  { 
                    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                    signalTranslationNote();
                    if (!(suppressWarningsP())) {
                      printErrorContext(">> NOTE: ", STANDARD_OUTPUT);
                      std::cout << std::endl << " " << "Illegal slot definition:" << std::endl << "   " << "`" << deUglifyParseTree(slotdef) << "'" << std::endl << "." << std::endl;
                    }
                  }
                  continue;
                }
                localslot = defineStorageSlotFromParseTree(((Cons*)(slotdef)), classtype);
                if (key == KWD_STELLA_IN_PUBLIC_SLOTS) {
                  localslot->slotPublicP = true;
                }
                if (!((boolean)(collect001))) {
                  {
                    collect001 = cons(localslot, NIL);
                    if (slots->theConsList == NIL) {
                      slots->theConsList = collect001;
                    }
                    else {
                      addConsToEndOfConsList(slots->theConsList, collect001);
                    }
                  }
                }
                else {
                  {
                    collect001->rest = cons(localslot, NIL);
                    collect001 = collect001->rest;
                  }
                }
              }
            }
          }
        }
        else if ((key == KWD_STELLA_IN_PUBLIC_METHODS) ||
            (key == KWD_STELLA_IN_METHODS)) {
          { Slot* localslot = NULL;

            { Cons* methoddef = NULL;
              Cons* iter003 = ((Cons*)(thevalue));
              Cons* collect002 = NULL;

              for  (; !(iter003 == NIL); 
                    iter003 = iter003->rest) {
                methoddef = ((Cons*)(iter003->value));
                if (!consP(methoddef)) {
                  { 
                    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                    signalTranslationNote();
                    if (!(suppressWarningsP())) {
                      printErrorContext(">> NOTE: ", STANDARD_OUTPUT);
                      std::cout << std::endl << " " << "Illegal inline method definition:" << std::endl << "   " << "`" << deUglifyParseTree(methoddef) << "'" << std::endl << "." << std::endl;
                    }
                  }
                  continue;
                }
                localslot = defineInlineMethod(((Symbol*)(methoddef->value)), methoddef->rest);
                if (key == KWD_STELLA_IN_PUBLIC_METHODS) {
                  localslot->slotPublicP = true;
                }
                if (!(localslot->slotOwner == classtype)) {
                  { 
                    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                    signalTranslationError();
                    if (!(suppressWarningsP())) {
                      printErrorContext(">> ERROR: ", STANDARD_ERROR);
                      *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Defining a method for the class " << "`" << localslot->slotOwner << "'" << " inside of the class " << "`" << deUglifyParseTree(classtype) << "'" << "." << std::endl;
                    }
                  }
                }
                if (!((boolean)(collect002))) {
                  {
                    collect002 = cons(localslot, NIL);
                    if (slots->theConsList == NIL) {
                      slots->theConsList = collect002;
                    }
                    else {
                      addConsToEndOfConsList(slots->theConsList, collect002);
                    }
                  }
                }
                else {
                  {
                    collect002->rest = cons(localslot, NIL);
                    collect002 = collect002->rest;
                  }
                }
              }
            }
          }
        }
        else if (key == KWD_STELLA_IN_PARAMETERS) {
          parameters = newList();
          { Object* slotdef = NULL;
            Cons* iter004 = ((Cons*)(thevalue));
            Cons* collect003 = NULL;

            for  (; !(iter004 == NIL); 
                  iter004 = iter004->rest) {
              slotdef = iter004->value;
              if (!((boolean)(collect003))) {
                {
                  collect003 = cons(defineStorageSlotFromParseTree(((Cons*)(slotdef)), classtype), NIL);
                  if (parameters->theConsList == NIL) {
                    parameters->theConsList = collect003;
                  }
                  else {
                    addConsToEndOfConsList(parameters->theConsList, collect003);
                  }
                }
              }
              else {
                {
                  collect003->rest = cons(defineStorageSlotFromParseTree(((Cons*)(slotdef)), classtype), NIL);
                  collect003 = collect003->rest;
                }
              }
            }
          }
          classoptions->insertAt(key, parameters);
        }
        else if (key == KWD_STELLA_IN_KEY) {
          if (!consP(thevalue)) {
            thevalue = cons(thekey, NIL);
          }
          inPlaceObjectsToSymbols(((Cons*)(thevalue)));
          classoptions->insertAt(key, ((Cons*)(thevalue)));
        }
        else if (key == KWD_STELLA_IN_SYNONYMS) {
          if (!consP(thevalue)) {
            thevalue = cons(thekey, NIL);
          }
          inPlaceObjectsToTypes(((Cons*)(thevalue)));
          classoptions->insertAt(key, ((Cons*)(thevalue)));
        }
        else if ((key == KWD_STELLA_IN_DOCUMENTATION) ||
            ((key == KWD_STELLA_IN_CL_NATIVE_TYPE) ||
             ((key == KWD_STELLA_IN_CPP_NATIVE_TYPE) ||
              ((key == KWD_STELLA_IN_JAVA_NATIVE_TYPE) ||
               (key == KWD_STELLA_IN_IDL_NATIVE_TYPE))))) {
          classoptions->insertAt(key, thevalue);
        }
        else if ((key == KWD_STELLA_IN_ABSTRACTp) ||
            ((key == KWD_STELLA_IN_ACTIVEp) ||
             ((key == KWD_STELLA_IN_PUBLICp) ||
              ((key == KWD_STELLA_IN_CL_STRUCTp) ||
               (key == KWD_STELLA_IN_MIXINp))))) {
          classoptions->insertAt(key, coerceToBoolean(thevalue));
        }
        else if (key == KWD_STELLA_IN_RECYCLE_METHOD) {
          thevalue = thevalue->permanentify();
          classoptions->insertAt(key, thevalue);
          if (getQuotedTree("((:SWEEP-LIST :FREE-AND-SWEEP-LIST) \"/STELLA\")", "/STELLA")->memberP(thevalue)) {
            slottree = listO(4, SYM_STELLA_IN_STELLA_NEXT_SWEEP_LIST_OBJECT, KWD_STELLA_IN_TYPE, treedefinition->value, NIL);
            slots->push(defineStorageSlotFromParseTree(slottree, classtype));
          }
        }
        else if ((key == KWD_STELLA_IN_EXTENSION) ||
            ((key == KWD_STELLA_IN_CREATOR) ||
             ((key == KWD_STELLA_IN_DESTRUCTOR) ||
              ((key == KWD_STELLA_IN_INITIALIZER) ||
               ((key == KWD_STELLA_IN_TERMINATOR) ||
                (key == KWD_STELLA_IN_EQUALITY_TEST)))))) {
          classoptions->insertAt(key, thevalue->permanentify());
        }
        else if ((key == KWD_STELLA_IN_INITIAL_VALUE) ||
            (key == KWD_STELLA_IN_PRINT_FORM)) {
          classoptions->insertAt(key, permanentifyForm(thevalue));
        }
        else if (key == KWD_STELLA_IN_PROPERTIES) {
          classoptions->insertAt(key, collectFeatureList(thevalue));
        }
        else if (key == KWD_STELLA_IN_META_ATTRIBUTES) {
          classoptions->insertAt(key, collectKeyValueList(thevalue));
        }
        else if (key == KWD_STELLA_IN_CHILDREN) {
          if (safePrimaryType(thevalue) == SGT_STELLA_IN_STELLA_CONS) {
            { Object* thevalue000 = thevalue;
              Cons* thevalue = ((Cons*)(thevalue000));

              { List* children = newList();

                { Object* child = NULL;
                  Cons* iter005 = thevalue;
                  Cons* collect004 = NULL;

                  for  (; !(iter005 == NIL); 
                        iter005 = iter005->rest) {
                    child = iter005->value;
                    if (symbolP(child)) {
                      if (!((boolean)(collect004))) {
                        {
                          collect004 = cons(typify(child), NIL);
                          if (children->theConsList == NIL) {
                            children->theConsList = collect004;
                          }
                          else {
                            addConsToEndOfConsList(children->theConsList, collect004);
                          }
                        }
                      }
                      else {
                        {
                          collect004->rest = cons(typify(child), NIL);
                          collect004 = collect004->rest;
                        }
                      }
                    }
                  }
                }
                classoptions->insertAt(key, children);
              }
            }
          }
          else {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal :children specification: " << "`" << deUglifyParseTree(thevalue) << "'" << "." << std::endl;
              }
            }
          }
        }
        else {
          classoptions->insertAt(key, thevalue);
        }
      }
    }
    theoptions->thePlist = NULL;
    { Class* clasS = defineStellaClass(classtype, directsupers, slots, ((KeywordKeyValueList*)(classoptions->reverse())));

      if (((boolean)(clasS))) {
        clasS->classStringifiedSource = stringifiedsource;
      }
      return (clasS);
    }
  }
}

StorageSlot* defineStorageSlotFromParseTree(Cons* slotdef, Surrogate* owner) {
  { Object* name = slotdef->value->permanentify();
    Surrogate* basetype = NULL;
    Cons* typeexpression = NIL;
    PropertyList* theoptions = newPropertyList();
    KeywordKeyValueList* slotoptions = newKeywordKeyValueList();
    Keyword* key = NULL;
    StorageSlot* slot = NULL;

    theoptions->thePlist = slotdef->rest;
    { Object* thekey = NULL;
      Object* thevalue = NULL;
      Cons* iter000 = theoptions->thePlist;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest->rest) {
        thekey = iter000->value;
        thevalue = iter000->rest->value;
        key = ((Keyword*)(thekey->permanentify()));
        if ((key == KWD_STELLA_IN_INITIALLY) ||
            (key == KWD_STELLA_IN_DEFAULT)) {
          slotoptions->insertAt(key, permanentifyForm(thevalue));
        }
        else if (key == KWD_STELLA_IN_TYPE) {
          if (safePrimaryType(thevalue) == SGT_STELLA_IN_STELLA_CONS) {
            { Object* thevalue000 = thevalue;
              Cons* thevalue = ((Cons*)(thevalue000));

              typeexpression = thevalue;
              if (thevalue->value == SYM_STELLA_IN_STELLA_LIKE) {
                basetype = NULL;
              }
              else {
                basetype = typify(thevalue->value);
              }
            }
          }
          else {
            basetype = typify(thevalue);
            if (definedTypeP(basetype)) {
              { StandardObject* realtype = thevalue->yieldTypeSpecifier();

                basetype = typeSpecToBaseType(realtype);
                if (!(typeP(realtype))) {
                  typeexpression = ((Cons*)(yieldTypeSpecTree(realtype)));
                }
              }
            }
          }
        }
        else if (key == KWD_STELLA_IN_ALLOCATION) {
          slotoptions->insertAt(key, thevalue->permanentify());
        }
        else if (key == KWD_STELLA_IN_READER) {
          slotoptions->insertAt(key, thevalue->permanentify());
        }
        else if (key == KWD_STELLA_IN_WRITER) {
          slotoptions->insertAt(key, thevalue->permanentify());
        }
        else if ((key == KWD_STELLA_IN_INVERSE) ||
            (key == KWD_STELLA_IN_RENAMES)) {
          slotoptions->insertAt(key, thevalue->permanentify());
        }
        else if ((key == KWD_STELLA_IN_PUBLICp) ||
            ((key == KWD_STELLA_IN_REQUIREDp) ||
             ((key == KWD_STELLA_IN_COMPONENTp) ||
              ((key == KWD_STELLA_IN_READ_ONLYp) ||
               ((key == KWD_STELLA_IN_ACTIVEp) ||
                ((key == KWD_STELLA_IN_CONTEXT_SENSITIVEp) ||
                 ((key == KWD_STELLA_IN_HARDWIREDp) ||
                  (key == KWD_STELLA_IN_ABSTRACTp)))))))) {
          slotoptions->insertAt(key, coerceToBoolean(thevalue));
        }
        else if (key == KWD_STELLA_IN_DOCUMENTATION) {
          slotoptions->insertAt(key, thevalue);
        }
        else if (key == KWD_STELLA_IN_PROPERTIES) {
          slotoptions->insertAt(key, collectFeatureList(thevalue));
        }
        else if (key == KWD_STELLA_IN_META_ATTRIBUTES) {
          slotoptions->insertAt(key, collectKeyValueList(thevalue));
        }
        else if ((key == KWD_STELLA_IN_OPTION_KEYWORD) ||
            (key == KWD_STELLA_IN_OPTION_HANDLER)) {
          slotoptions->insertAt(key, thevalue->permanentify());
        }
        else {
          slotoptions->insertAt(key, thevalue);
        }
      }
    }
    theoptions->thePlist = NULL;
    slot = ((StorageSlot*)(defineStellaSlot(((Symbol*)(name)), owner, basetype, typeexpression, ((KeywordKeyValueList*)(slotoptions->reverse())))));
    recordSlotHomeModule(slot);
    return (slot);
  }
}

Module* recordSlotHomeModule(Slot* self) {
  { Symbol* name = self->slotName;
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
      setDynamicSlotValue(self->dynamicSlots, SYM_STELLA_IN_STELLA_SLOT_HOME_MODULE, homemodule, NULL);
    }
    return (homemodule);
  }
}

boolean explicitlyQualifiedNameP(GeneralizedSymbol* name, Module* definitionmodule) {
  { Module* namemodule = ((Module*)(name->homeContext));
    GeneralizedSymbol* shadow = NULL;

    if (namemodule == definitionmodule) {
      {
        return (false);
      }
    }
    else {
      if (!visibleFromP(namemodule, definitionmodule)) {
        {
          return (true);
        }
      }
      else {
        { boolean testValue000 = false;

          { 
            shadow = lookupSymbolInModule(name->symbolName, definitionmodule, true);
            testValue000 = ((boolean)(shadow));
          }
          if (testValue000) {
            testValue000 = !(shadow == name);
          }
          if (testValue000) {
            {
              return (true);
            }
          }
          else {
            {
              return (false);
            }
          }
        }
      }
    }
  }
}

Class* getIdenticalClass(const char* classname, const char* stringifiedsource) {
  { Surrogate* surrogate = lookupSurrogate(classname);
    Object* oldvalue = (((boolean)(surrogate)) ? surrogate->surrogateValue : ((Object*)(NULL)));

    if (((boolean)(oldvalue))) {
      if (subtypeOfClassP(safePrimaryType(oldvalue))) {
        { Object* oldvalue000 = oldvalue;
          Class* oldvalue = ((Class*)(oldvalue000));

          if ((oldvalue->classStringifiedSource != NULL) &&
              (stringEqlP(oldvalue->classStringifiedSource, stringifiedsource) &&
               (((Module*)(surrogate->homeContext)) == oMODULEo))) {
            return (oldvalue);
          }
        }
      }
      else {
      }
    }
    return (NULL);
  }
}

Class* defineClassFromParseTree(Cons* parsetree) {
  if (badArgumentRangeP(parsetree, 2, NULL_INTEGER)) {
    return (NULL);
  }
  if (!(symbolP(parsetree->rest->value) &&
      consP(parsetree->rest->rest->value))) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal class definition: " << "`" << deUglifyParseTree(parsetree) << "'" << "." << std::endl;
      }
    }
    return (NULL);
  }
  { Symbol* classname = ((Symbol*)(parsetree->rest->value));
    const char* stringifiedsource = stringify(parsetree);
    Class* oldclass = getIdenticalClass(classname->symbolName, stringifiedsource);

    if (((boolean)(oldclass)) &&
        (!oREDEFINE_IDENTICAL_CLASSESpo)) {
      return (oldclass);
    }
    return (helpDefineClassFromParseTree(parsetree, stringifiedsource));
  }
}

Class* defineClassFromStringifiedSource(const char* classname, const char* stringifiedsource) {
  { Class* oldclass = getIdenticalClass(classname, stringifiedsource);
    Class* newclass = NULL;

    if (((boolean)(oldclass)) &&
        (!oREDEFINE_IDENTICAL_CLASSESpo)) {
      return (oldclass);
    }
    newclass = helpDefineClassFromParseTree(((Cons*)(unstringifyStellaSource(stringifiedsource, NULL))), stringifiedsource);
    return (newclass);
  }
}

Cons* extractOptions(Cons* tree, KeyValueList* optionstable) {
  { Cons* options = NULL;
    Cons* tail = NULL;

    while ((!(tree->rest == NIL)) &&
        (!keywordP(tree->rest->value))) {
      tree = tree->rest;
    }
    if ((tree->rest == NIL) ||
        (tree->rest->rest == NIL)) {
      return (NIL);
    }
    if (((boolean)(optionstable))) {
      optionstable->insertAt(tree->rest->value, tree->rest->rest->value);
    }
    options = tree->rest;
    tail = tree->rest->rest;
    while ((!(tail->rest->rest == NIL)) &&
        keywordP(tail->rest->value)) {
      if (((boolean)(optionstable))) {
        optionstable->insertAt(tail->rest->value, tail->rest->rest->value);
      }
      tail = tail->rest->rest;
    }
    tree->rest = tail->rest;
    tail->rest = NIL;
    return (options);
  }
}

Object* destructureDefmethodTree(Cons* methodTree, KeyValueList* optionsTable, Cons*& _Return1, Cons*& _Return2) {
  // Return three parse trees representing the name,
  // parameters, and code body of the parse tree `method-tree'.  Fill
  // `options-table' with a dictionary of method options.
  // Storage note:  Options are treated specially because the other return
  // values are subtrees of `method-tree', while `options-table' is a newly-created
  // cons tree.  Note also, the parameter and body trees are destructively
  // removed from `method-tree'.
  { Object* nametree = methodTree->rest->value;
    Object* parameterstree = methodTree->rest->rest->value;

    if (!consP(parameterstree)) {
      if (!((boolean)(parameterstree))) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Missing parameter list" << "." << std::endl;
          }
        }
      }
      else {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal parameter list: " << "`" << deUglifyParseTree(parameterstree) << "'" << "." << std::endl;
          }
        }
      }
      parameterstree = NIL;
    }
    extractOptions(methodTree, optionsTable);
    { Object* _Return0 = nametree;

      _Return1 = ((Cons*)(parameterstree));
      _Return2 = methodTree->nthRest(3);
      return (_Return0);
    }
  }
}

Symbol* yieldSetterMethodName(Symbol* methodname) {
  { const char* baseName = methodname->symbolName;
    const char* suffix = (allUpperCaseStringP(baseName) ? "-SETTER" : "-Setter");

    return (internDerivedSymbol(methodname, stringConcatenate(baseName, suffix, 0)));
  }
}

Symbol* destructureMethodNameTree(Object* nametree, Cons*& _Return1) {
  { Surrogate* testValue000 = safePrimaryType(nametree);

    if (testValue000 == SGT_STELLA_IN_STELLA_CONS) {
      { Object* nametree000 = nametree;
        Cons* nametree = ((Cons*)(nametree000));

        if (!symbolP(nametree->value)) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal method name: " << "`" << deUglifyParseTree(nametree) << "'" << "." << std::endl;
            }
          }
          _Return1 = NULL;
          return (NULL);
        }
        if (nametree->rest->value == SYM_STELLA_IN_STELLA_SETTER) {
          { Symbol* _Return0 = yieldSetterMethodName(((Symbol*)(nametree->value)));

            _Return1 = NIL;
            return (_Return0);
          }
        }
        else {
          _Return1 = nametree->rest;
          return (((Symbol*)(nametree->value)));
        }
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* nametree001 = nametree;
        Symbol* nametree = ((Symbol*)(nametree001));

        _Return1 = NIL;
        return (nametree);
      }
    }
    else {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal method name: " << "`" << deUglifyParseTree(nametree) << "'" << "." << std::endl;
        }
      }
      _Return1 = NULL;
      return (NULL);
    }
  }
}

void inPlaceNormalizeMethodOptions(KeywordKeyValueList* methodoptions, Symbol* methodname) {
  methodname = methodname;
  { Keyword* key = NULL;
    Object* value = NULL;
    KvListIterator* iter000 = ((KvListIterator*)(methodoptions->allocateIterator()));

    for  (; iter000->nextP(); ) {
      key = ((Keyword*)(iter000->key));
      value = iter000->value;
      if ((key == KWD_STELLA_IN_TYPE) ||
          (key == KWD_STELLA_IN_RETURN_TYPES)) {
      }
      else if ((key == KWD_STELLA_IN_RENAMES) ||
          ((key == KWD_STELLA_IN_STORAGE_SLOT) ||
           (key == KWD_STELLA_IN_INHERITS_THROUGH))) {
        methodoptions->insertAt(key, value->permanentify());
      }
      else if ((key == KWD_STELLA_IN_PUBLICp) ||
          ((key == KWD_STELLA_IN_ABSTRACTp) ||
           ((key == KWD_STELLA_IN_SETTERp) ||
            ((key == KWD_STELLA_IN_NATIVEp) ||
             ((key == KWD_STELLA_IN_CONSTRUCTORp) ||
              ((key == KWD_STELLA_IN_AUXILIARYp) ||
               ((key == KWD_STELLA_IN_GLOBALLY_INLINEp) ||
                ((key == KWD_STELLA_IN_COMMANDp) ||
                 ((key == KWD_STELLA_IN_LISP_MACROp) ||
                  ((key == KWD_STELLA_IN_EVALUATE_ARGUMENTSp) ||
                   (key == KWD_STELLA_IN_C_CALLABLEp))))))))))) {
        methodoptions->insertAt(key, coerceToBoolean(value));
      }
      else if (key == KWD_STELLA_IN_DOCUMENTATION) {
        methodoptions->insertAt(key, value);
      }
      else if (key == KWD_STELLA_IN_INLINE) {
        { Surrogate* testValue000 = safePrimaryType(value);

          if (subtypeOfSymbolP(testValue000)) {
            { Object* value000 = value;
              Symbol* value = ((Symbol*)(value000));

              methodoptions->insertAt(key, ((Symbol*)(value->permanentify())));
            }
          }
          else if (testValue000 == SGT_STELLA_IN_STELLA_CONS) {
            { Object* value001 = value;
              Cons* value = ((Cons*)(value001));

              { Cons* symbolslist = NIL;

                { Object* symbol = NULL;
                  Cons* iter001 = value;
                  Cons* collect000 = NULL;

                  for  (; !(iter001 == NIL); 
                        iter001 = iter001->rest) {
                    symbol = iter001->value;
                    if (!((boolean)(collect000))) {
                      {
                        collect000 = cons(symbol->permanentify(), NIL);
                        if (symbolslist == NIL) {
                          symbolslist = collect000;
                        }
                        else {
                          addConsToEndOfConsList(symbolslist, collect000);
                        }
                      }
                    }
                    else {
                      {
                        collect000->rest = cons(symbol->permanentify(), NIL);
                        collect000 = collect000->rest;
                      }
                    }
                  }
                }
                methodoptions->insertAt(key, symbolslist);
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
      else if (key == KWD_STELLA_IN_PROPERTIES) {
        methodoptions->insertAt(key, collectFeatureList(value));
      }
      else if (key == KWD_STELLA_IN_META_ATTRIBUTES) {
        methodoptions->insertAt(key, collectKeyValueList(value));
      }
      else {
        methodoptions->insertAt(key, value->permanentify());
      }
    }
  }
  methodoptions->reverse();
}

MethodSlot* getFunctionWithIdenticalSignature(Symbol* name, const char* stringifiedsource) {
  { MethodSlot* oldmethod = lookupFunction(name);

    if (((boolean)(oldmethod)) &&
        stringEqlP(oldmethod->methodStringifiedSource, stringifiedsource)) {
      return (oldmethod);
    }
    return (NULL);
  }
}

MethodSlot* getMethodWithIdenticalSignature(Symbol* name, Cons* parameterstree, const char* stringifiedsource) {
  { Slot* existingslot = NULL;

    if (consP(parameterstree->value)) {
      parameterstree = ((Cons*)(parameterstree->value));
      if (symbolP(parameterstree->last())) {
        existingslot = lookupSlot(typeSpecToClass(parameterstree->last()->yieldTypeSpecifier()), name);
        if (((boolean)(existingslot))) {
          if (subtypeOfMethodSlotP(safePrimaryType(existingslot))) {
            { Slot* existingslot000 = existingslot;
              MethodSlot* existingslot = ((MethodSlot*)(existingslot000));

              if (stringEqlP(existingslot->methodStringifiedSource, stringifiedsource)) {
                return (existingslot);
              }
            }
          }
          else {
          }
        }
      }
    }
    return (NULL);
  }
}

MethodSlot* helpDefineMethodFromParseTree(Cons* inputtree, const char* stringifiedsource, boolean& _Return1) {
  { Object* nametree = NULL;
    Cons* parameterstree = NULL;
    KeywordKeyValueList* methodoptions = newKeywordKeyValueList();
    Cons* bodytree = NULL;
    Symbol* name = NULL;
    Cons* returntypestree = NULL;
    boolean functionP = inputtree->value == SYM_STELLA_IN_STELLA_DEFUN;
    MethodSlot* oldmethod = NULL;
    const char* signaturestring = ((stringifiedsource == NULL) ? stringifyMethodSignature(inputtree) : stringifiedsource);

    nametree = destructureDefmethodTree(inputtree, methodoptions, parameterstree, bodytree);
    name = destructureMethodNameTree(nametree, returntypestree);
    if (!((boolean)(name))) {
      _Return1 = false;
      return (NULL);
    }
    oldmethod = (functionP ? getFunctionWithIdenticalSignature(name, signaturestring) : getMethodWithIdenticalSignature(name, parameterstree, signaturestring));
    if (((boolean)(oldmethod))) {
      _Return1 = true;
      return (oldmethod);
    }
    inPlaceNormalizeMethodOptions(methodoptions, name);
    { MethodSlot* method = defineStellaMethodSlot(name, returntypestree, functionP, parameterstree, methodoptions);

      if (stringifiedsource == NULL) {
        stringifiedsource = (stringifyMethodBodyP(method) ? stringify(((Cons*)(readSExpressionFromString(signaturestring)))->concatenate(bodytree, 0)) : signaturestring);
      }
      method->methodStringifiedSource = stringifiedsource;
      recordSlotHomeModule(method);
      _Return1 = false;
      return (method);
    }
  }
}

MethodSlot* defineMethodFromParseTree(Cons* parsetree) {
  if (badArgumentRangeP(parsetree, 2, NULL_INTEGER)) {
    return (NULL);
  }
  { MethodSlot* method = NULL;
    boolean identicalmethodP = false;

    method = helpDefineMethodFromParseTree(parsetree, NULL, identicalmethodP);
    if (!(identicalmethodP ||
        (!((boolean)(method))))) {
      if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_STELLA_IN_STELLA_SLOT_AUXILIARYp, FALSE_WRAPPER)))->wrapperValue) {
        method->slotExternalP = true;
      }
      else {
        attachMethodSlotToOwner(method);
      }
    }
    return (method);
  }
}

const char* stringifyMethodSignature(Cons* parsetree) {
  { Cons* signature = NIL;
    const char* signaturestring = NULL;
    Cons* optionstree = parsetree->nthRest(3);

    signature = cons(parsetree->value, signature);
    signature = cons(parsetree->rest->value, signature);
    signature = cons(parsetree->rest->rest->value, signature);
    while (keywordP(optionstree->value)) {
      signature = cons(optionstree->value, signature);
      signature = cons(optionstree->rest->value, signature);
      optionstree = optionstree->rest->rest;
    }
    signaturestring = stringify(signature->reverse());
    return (signaturestring);
  }
}

boolean stringifyMethodBodyP(MethodSlot* method) {
  return (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_STELLA_IN_STELLA_METHOD_GLOBALLY_INLINEp, FALSE_WRAPPER)))->wrapperValue ||
      ((!method->methodFunctionP) &&
       ((!((boolean)(((Class*)(method->slotOwner->surrogateValue))))) ||
        ((Class*)(method->slotOwner->surrogateValue))->mixinP)));
}

MethodSlot* defineMethodFromStringifiedSource(const char* methodname, const char* classname, const char* stringifiedsource) {
  {
    methodname = methodname;
    classname = classname;
  }
  { MethodSlot* method = NULL;
    boolean identicalmethodP = false;

    method = helpDefineMethodFromParseTree(((Cons*)(unstringifyStellaSource(stringifiedsource, NULL))), stringifiedsource, identicalmethodP);
    if (!(identicalmethodP ||
        ((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_STELLA_IN_STELLA_SLOT_AUXILIARYp, FALSE_WRAPPER)))->wrapperValue)) {
      attachMethodSlotToOwner(method);
    }
    return (method);
  }
}

void defineMethodObject(const char* definition, CodeWrapper* code, CodeWrapper* wrappercode) {
  wrappercode = wrappercode;
  { MethodSlot* method = defineMethodFromStringifiedSource(NULL, NULL, definition);

    if (((boolean)(method))) {
      if (((boolean)(code))) {
        method->methodCode = code;
      }
    }
  }
}

void defineInlineMethodCode(Surrogate* classtype, Symbol* methodname, CodeWrapper* code, CodeWrapper* wrappercode) {
  wrappercode = wrappercode;
  { MethodSlot* method = ((MethodSlot*)(lookupSlot(((Class*)(classtype->surrogateValue)), methodname)));

    if (((boolean)(method))) {
      if (((boolean)(code))) {
        method->methodCode = code;
      }
    }
  }
}

List* oUNSUPPORTED_EXTERNAL_SLOT_OPTIONSo = NULL;

StorageSlot* defineExternalSlotFromParseTree(Cons* parsetree) {
  if (badArgumentRangeP(parsetree, 2, NULL_INTEGER)) {
    return (NULL);
  }
  if ((!symbolP(parsetree->rest->value)) ||
      ((!symbolP(parsetree->rest->rest->value)) ||
       (!!((parsetree->nthRest(3)->length()) % 2)))) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal external slot definition: " << "`" << deUglifyParseTree(parsetree) << "'" << "." << std::endl;
      }
    }
    return (NULL);
  }
  { Symbol* classname = ((Symbol*)(parsetree->rest->value));
    Surrogate* owner = typify(classname);
    Class* ownerclass = ((Class*)(owner->surrogateValue));
    StorageSlot* slot = NULL;
    Cons* options = parsetree->nthRest(3);
    Module* marker = oSTELLA_MODULEo;
    boolean abstractP = false;

    if (!((boolean)(ownerclass))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Can't define a slot on the non-existent class " << "`" << deUglifyParseTree(classname) << "'" << "." << std::endl;
        }
      }
      return (NULL);
    }
    while (!(options == NIL)) {
      { Object* option = options->value;
        Object* value = options->rest->value;

        if (oUNSUPPORTED_EXTERNAL_SLOT_OPTIONSo->memberP(option)) {
          if ((!(option == KWD_STELLA_IN_ALLOCATION)) ||
              (!(value == KWD_STELLA_IN_DYNAMIC))) {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationWarning();
              if (!(suppressWarningsP())) {
                printErrorContext(">> WARNING: ", STANDARD_WARNING);
                *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Skipping slot option " << "`" << deUglifyParseTree(option) << "'" << " which is unsupported on external slots" << "." << std::endl;
              }
            }
          }
          options->firstSetter(marker);
          if (((boolean)(value))) {
            options->secondSetter(marker);
          }
        }
        if (((option == KWD_STELLA_IN_ABSTRACTp) &&
            (value == SYM_STELLA_IN_STELLA_TRUE)) ||
            (option == KWD_STELLA_IN_RENAMES)) {
          abstractP = true;
        }
      }
      options = options->rest->rest;
    }
    if ((!abstractP) &&
        (ownerclass->classFinalizedP &&
         (!subtypeOfP(owner, SGT_STELLA_IN_STELLA_DYNAMIC_SLOTS_MIXIN)))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Can't define a non-abstract external slot on class " << "`" << deUglifyParseTree(classname) << "'" << "," << std::endl << " since it does not inherit DYNAMIC-SLOTS-MIXIN" << "." << std::endl;
        }
      }
      return (NULL);
    }
    parsetree = parsetree->remove(marker);
    if (!(abstractP)) {
      parsetree = parsetree->concatenate(listO(3, KWD_STELLA_IN_ALLOCATION, KWD_STELLA_IN_DYNAMIC, NIL), 0);
    }
    slot = defineStorageSlotFromParseTree(parsetree->rest->rest, owner);
    if (((boolean)(slot))) {
      attachSlotToOwner(slot);
    }
    return (slot);
  }
}

StorageSlot* defineExternalSlotFromStringifiedSource(const char* stringifiedsource) {
  return (defineExternalSlotFromParseTree(((Cons*)(readSExpressionFromString(stringifiedsource)))));
}

StorageSlot* lookupSlotFromOptionKeyword(Surrogate* owner, Keyword* keyword) {
  { Class* ownerclass = ((Class*)(owner->surrogateValue));

    if (((boolean)(ownerclass))) {
      { Slot* slot = NULL;
        Iterator* iter000 = ownerclass->classSlots();

        for (; iter000->nextP(); ) {
          slot = ((Slot*)(iter000->value));
          if (storageSlotP(slot) &&
              (((Keyword*)(dynamicSlotValue(((StorageSlot*)(slot))->dynamicSlots, SYM_STELLA_IN_STELLA_SLOT_OPTION_KEYWORD, NULL))) == keyword)) {
            return (((StorageSlot*)(slot)));
          }
        }
      }
    }
    return (NULL);
  }
}

MethodSlot* oDEFAULT_OPTION_HANDLERo = NULL;

MethodSlot* lookupOptionHandler(StorageSlot* slot) {
  { Symbol* handlername = ((Symbol*)(dynamicSlotValue(slot->dynamicSlots, SYM_STELLA_IN_STELLA_SLOT_OPTION_HANDLER, NULL)));
    MethodSlot* handler = NULL;

    if (!((boolean)(handlername))) {
      if (((boolean)(oDEFAULT_OPTION_HANDLERo))) {
        return (oDEFAULT_OPTION_HANDLERo);
      }
      else {
        return (lookupFunction(SYM_STELLA_IN_STELLA_DEFAULT_OPTION_HANDLER));
      }
    }
    handler = lookupFunction(handlername);
    if ((oSAFETYo >= 2) &&
        (((boolean)(handler)) &&
         ((!(handlername == SYM_STELLA_IN_STELLA_DEFAULT_OPTION_HANDLER)) &&
          (!handler->conformingSignaturesP(oDEFAULT_OPTION_HANDLERo))))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "The signature of slot option handler " << "`" << handlername << "'" << " does not conform to that of 'default-option-handler'.";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    return (handler);
  }
}

boolean runOptionHandlerP(Object* object, Keyword* option, Object* valuetree) {
  { StorageSlot* slot = lookupSlotFromOptionKeyword(object->primaryType(), option);
    MethodSlot* handler = (((boolean)(slot)) ? lookupOptionHandler(slot) : ((MethodSlot*)(NULL)));

    if (((boolean)(handler))) {
      ((void  (*) (Object*, StorageSlot*, Object*))handler->functionCode)(object, slot, valuetree);
      return (true);
    }
    return (false);
  }
}

void defaultOptionHandler(Object* self, StorageSlot* slot, Object* tree) {
  { Object* parsedvalue = NULL;

    if (slot->type() == SGT_STELLA_IN_STELLA_BOOLEAN) {
      parsedvalue = coerceToBoolean(tree);
    }
    else {
      if (((boolean)(tree))) {
        parsedvalue = permanentCopy(tree);
      }
    }
    if ((oSAFETYo >= 2) &&
        ((boolean)(parsedvalue))) {
      if (!isaP(parsedvalue, slot->type()->typeToWrappedType())) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal value for " << "`" << ((Keyword*)(dynamicSlotValue(slot->dynamicSlots, SYM_STELLA_IN_STELLA_SLOT_OPTION_KEYWORD, NULL))) << "'" << " option: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
          }
        }
        return;
      }
    }
    writeSlotValue(((StandardObject*)(self)), slot, parsedvalue);
  }
}

void helpStartupStellaIn1() {
  {
    SYM_STELLA_IN_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    SYM_STELLA_IN_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", NULL, 0)));
    SGT_STELLA_IN_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SGT_STELLA_IN_STELLA_GENERALIZED_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("GENERALIZED-SYMBOL", NULL, 1)));
    SYM_STELLA_IN_STELLA_DEFMETHOD = ((Symbol*)(internRigidSymbolWrtModule("DEFMETHOD", NULL, 0)));
    KWD_STELLA_IN_PUBLIC_SLOTS = ((Keyword*)(internRigidSymbolWrtModule("PUBLIC-SLOTS", NULL, 2)));
    KWD_STELLA_IN_SLOTS = ((Keyword*)(internRigidSymbolWrtModule("SLOTS", NULL, 2)));
    KWD_STELLA_IN_PUBLIC_METHODS = ((Keyword*)(internRigidSymbolWrtModule("PUBLIC-METHODS", NULL, 2)));
    KWD_STELLA_IN_METHODS = ((Keyword*)(internRigidSymbolWrtModule("METHODS", NULL, 2)));
    KWD_STELLA_IN_PARAMETERS = ((Keyword*)(internRigidSymbolWrtModule("PARAMETERS", NULL, 2)));
    KWD_STELLA_IN_KEY = ((Keyword*)(internRigidSymbolWrtModule("KEY", NULL, 2)));
    KWD_STELLA_IN_SYNONYMS = ((Keyword*)(internRigidSymbolWrtModule("SYNONYMS", NULL, 2)));
    KWD_STELLA_IN_DOCUMENTATION = ((Keyword*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 2)));
    KWD_STELLA_IN_CL_NATIVE_TYPE = ((Keyword*)(internRigidSymbolWrtModule("CL-NATIVE-TYPE", NULL, 2)));
    KWD_STELLA_IN_CPP_NATIVE_TYPE = ((Keyword*)(internRigidSymbolWrtModule("CPP-NATIVE-TYPE", NULL, 2)));
    KWD_STELLA_IN_JAVA_NATIVE_TYPE = ((Keyword*)(internRigidSymbolWrtModule("JAVA-NATIVE-TYPE", NULL, 2)));
    KWD_STELLA_IN_IDL_NATIVE_TYPE = ((Keyword*)(internRigidSymbolWrtModule("IDL-NATIVE-TYPE", NULL, 2)));
    KWD_STELLA_IN_ABSTRACTp = ((Keyword*)(internRigidSymbolWrtModule("ABSTRACT?", NULL, 2)));
    KWD_STELLA_IN_ACTIVEp = ((Keyword*)(internRigidSymbolWrtModule("ACTIVE?", NULL, 2)));
    KWD_STELLA_IN_PUBLICp = ((Keyword*)(internRigidSymbolWrtModule("PUBLIC?", NULL, 2)));
    KWD_STELLA_IN_CL_STRUCTp = ((Keyword*)(internRigidSymbolWrtModule("CL-STRUCT?", NULL, 2)));
    KWD_STELLA_IN_MIXINp = ((Keyword*)(internRigidSymbolWrtModule("MIXIN?", NULL, 2)));
    KWD_STELLA_IN_RECYCLE_METHOD = ((Keyword*)(internRigidSymbolWrtModule("RECYCLE-METHOD", NULL, 2)));
    SYM_STELLA_IN_STELLA_NEXT_SWEEP_LIST_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("NEXT-SWEEP-LIST-OBJECT", NULL, 0)));
    KWD_STELLA_IN_TYPE = ((Keyword*)(internRigidSymbolWrtModule("TYPE", NULL, 2)));
    KWD_STELLA_IN_EXTENSION = ((Keyword*)(internRigidSymbolWrtModule("EXTENSION", NULL, 2)));
    KWD_STELLA_IN_CREATOR = ((Keyword*)(internRigidSymbolWrtModule("CREATOR", NULL, 2)));
    KWD_STELLA_IN_DESTRUCTOR = ((Keyword*)(internRigidSymbolWrtModule("DESTRUCTOR", NULL, 2)));
    KWD_STELLA_IN_INITIALIZER = ((Keyword*)(internRigidSymbolWrtModule("INITIALIZER", NULL, 2)));
    KWD_STELLA_IN_TERMINATOR = ((Keyword*)(internRigidSymbolWrtModule("TERMINATOR", NULL, 2)));
    KWD_STELLA_IN_EQUALITY_TEST = ((Keyword*)(internRigidSymbolWrtModule("EQUALITY-TEST", NULL, 2)));
    KWD_STELLA_IN_INITIAL_VALUE = ((Keyword*)(internRigidSymbolWrtModule("INITIAL-VALUE", NULL, 2)));
    KWD_STELLA_IN_PRINT_FORM = ((Keyword*)(internRigidSymbolWrtModule("PRINT-FORM", NULL, 2)));
    KWD_STELLA_IN_PROPERTIES = ((Keyword*)(internRigidSymbolWrtModule("PROPERTIES", NULL, 2)));
    KWD_STELLA_IN_META_ATTRIBUTES = ((Keyword*)(internRigidSymbolWrtModule("META-ATTRIBUTES", NULL, 2)));
    KWD_STELLA_IN_CHILDREN = ((Keyword*)(internRigidSymbolWrtModule("CHILDREN", NULL, 2)));
    KWD_STELLA_IN_INITIALLY = ((Keyword*)(internRigidSymbolWrtModule("INITIALLY", NULL, 2)));
    KWD_STELLA_IN_DEFAULT = ((Keyword*)(internRigidSymbolWrtModule("DEFAULT", NULL, 2)));
    SYM_STELLA_IN_STELLA_LIKE = ((Symbol*)(internRigidSymbolWrtModule("LIKE", NULL, 0)));
    KWD_STELLA_IN_ALLOCATION = ((Keyword*)(internRigidSymbolWrtModule("ALLOCATION", NULL, 2)));
    KWD_STELLA_IN_READER = ((Keyword*)(internRigidSymbolWrtModule("READER", NULL, 2)));
    KWD_STELLA_IN_WRITER = ((Keyword*)(internRigidSymbolWrtModule("WRITER", NULL, 2)));
    KWD_STELLA_IN_INVERSE = ((Keyword*)(internRigidSymbolWrtModule("INVERSE", NULL, 2)));
    KWD_STELLA_IN_RENAMES = ((Keyword*)(internRigidSymbolWrtModule("RENAMES", NULL, 2)));
    KWD_STELLA_IN_REQUIREDp = ((Keyword*)(internRigidSymbolWrtModule("REQUIRED?", NULL, 2)));
    KWD_STELLA_IN_COMPONENTp = ((Keyword*)(internRigidSymbolWrtModule("COMPONENT?", NULL, 2)));
    KWD_STELLA_IN_READ_ONLYp = ((Keyword*)(internRigidSymbolWrtModule("READ-ONLY?", NULL, 2)));
    KWD_STELLA_IN_CONTEXT_SENSITIVEp = ((Keyword*)(internRigidSymbolWrtModule("CONTEXT-SENSITIVE?", NULL, 2)));
    KWD_STELLA_IN_HARDWIREDp = ((Keyword*)(internRigidSymbolWrtModule("HARDWIRED?", NULL, 2)));
    KWD_STELLA_IN_OPTION_KEYWORD = ((Keyword*)(internRigidSymbolWrtModule("OPTION-KEYWORD", NULL, 2)));
    KWD_STELLA_IN_OPTION_HANDLER = ((Keyword*)(internRigidSymbolWrtModule("OPTION-HANDLER", NULL, 2)));
    SYM_STELLA_IN_STELLA_SLOT_HOME_MODULE = ((Symbol*)(internRigidSymbolWrtModule("SLOT-HOME-MODULE", NULL, 0)));
    SYM_STELLA_IN_STELLA_SETTER = ((Symbol*)(internRigidSymbolWrtModule("SETTER", NULL, 0)));
    KWD_STELLA_IN_RETURN_TYPES = ((Keyword*)(internRigidSymbolWrtModule("RETURN-TYPES", NULL, 2)));
    KWD_STELLA_IN_STORAGE_SLOT = ((Keyword*)(internRigidSymbolWrtModule("STORAGE-SLOT", NULL, 2)));
    KWD_STELLA_IN_INHERITS_THROUGH = ((Keyword*)(internRigidSymbolWrtModule("INHERITS-THROUGH", NULL, 2)));
    KWD_STELLA_IN_SETTERp = ((Keyword*)(internRigidSymbolWrtModule("SETTER?", NULL, 2)));
    KWD_STELLA_IN_NATIVEp = ((Keyword*)(internRigidSymbolWrtModule("NATIVE?", NULL, 2)));
    KWD_STELLA_IN_CONSTRUCTORp = ((Keyword*)(internRigidSymbolWrtModule("CONSTRUCTOR?", NULL, 2)));
    KWD_STELLA_IN_AUXILIARYp = ((Keyword*)(internRigidSymbolWrtModule("AUXILIARY?", NULL, 2)));
  }
}

void helpStartupStellaIn2() {
  {
    KWD_STELLA_IN_GLOBALLY_INLINEp = ((Keyword*)(internRigidSymbolWrtModule("GLOBALLY-INLINE?", NULL, 2)));
    KWD_STELLA_IN_COMMANDp = ((Keyword*)(internRigidSymbolWrtModule("COMMAND?", NULL, 2)));
    KWD_STELLA_IN_LISP_MACROp = ((Keyword*)(internRigidSymbolWrtModule("LISP-MACRO?", NULL, 2)));
    KWD_STELLA_IN_EVALUATE_ARGUMENTSp = ((Keyword*)(internRigidSymbolWrtModule("EVALUATE-ARGUMENTS?", NULL, 2)));
    KWD_STELLA_IN_C_CALLABLEp = ((Keyword*)(internRigidSymbolWrtModule("C-CALLABLE?", NULL, 2)));
    KWD_STELLA_IN_INLINE = ((Keyword*)(internRigidSymbolWrtModule("INLINE", NULL, 2)));
    SYM_STELLA_IN_STELLA_DEFUN = ((Symbol*)(internRigidSymbolWrtModule("DEFUN", NULL, 0)));
    SYM_STELLA_IN_STELLA_SLOT_AUXILIARYp = ((Symbol*)(internRigidSymbolWrtModule("SLOT-AUXILIARY?", NULL, 0)));
    SYM_STELLA_IN_STELLA_METHOD_GLOBALLY_INLINEp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-GLOBALLY-INLINE?", NULL, 0)));
    KWD_STELLA_IN_DYNAMIC = ((Keyword*)(internRigidSymbolWrtModule("DYNAMIC", NULL, 2)));
    SGT_STELLA_IN_STELLA_DYNAMIC_SLOTS_MIXIN = ((Surrogate*)(internRigidSymbolWrtModule("DYNAMIC-SLOTS-MIXIN", NULL, 1)));
    SYM_STELLA_IN_STELLA_SLOT_OPTION_KEYWORD = ((Symbol*)(internRigidSymbolWrtModule("SLOT-OPTION-KEYWORD", NULL, 0)));
    SYM_STELLA_IN_STELLA_DEFAULT_OPTION_HANDLER = ((Symbol*)(internRigidSymbolWrtModule("DEFAULT-OPTION-HANDLER", NULL, 0)));
    SYM_STELLA_IN_STELLA_SLOT_OPTION_HANDLER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-OPTION-HANDLER", NULL, 0)));
    SGT_STELLA_IN_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 1)));
    SYM_STELLA_IN_STELLA_STARTUP_STELLA_IN = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-STELLA-IN", NULL, 0)));
    SYM_STELLA_IN_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void startupStellaIn() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupStellaIn1();
      helpStartupStellaIn2();
    }
    if (currentStartupTimePhaseP(4)) {
      oUNSUPPORTED_EXTERNAL_SLOT_OPTIONSo = list(4, KWD_STELLA_IN_ALLOCATION, KWD_STELLA_IN_INITIALLY, KWD_STELLA_IN_CONTEXT_SENSITIVEp, KWD_STELLA_IN_HARDWIREDp);
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("PERMANENTIFY-FORM", "(DEFUN (PERMANENTIFY-FORM OBJECT) ((FORM OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&permanentifyForm)), NULL);
      defineFunctionObject("TRANSIENTIFY-FORM", "(DEFUN (TRANSIENTIFY-FORM OBJECT) ((FORM OBJECT)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (COPY-CONS-TREE FORM)))", ((cpp_function_code)(&transientifyForm)), NULL);
      defineFunctionObject("STRINGIFY-IN-MODULE", "(DEFUN (STRINGIFY-IN-MODULE STRING) ((TREE OBJECT) (MODULE MODULE)) :DOCUMENTATION \"Stringify a parse `tree' relative to `module', or\n`*module*' if no module is specified.\" :PUBLIC? TRUE)", ((cpp_function_code)(&stringifyInModule)), NULL);
      defineFunctionObject("UNSTRINGIFY-IN-MODULE", "(DEFUN (UNSTRINGIFY-IN-MODULE OBJECT) ((STRING STRING) (MODULE MODULE)) :DOCUMENTATION \"Unstringify relative to `module', or `*MODULE*' if no\nmodule is specified.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unstringifyInModule)), NULL);
      defineFunctionObject("UNSTRINGIFY-STELLA-SOURCE", "(DEFUN (UNSTRINGIFY-STELLA-SOURCE OBJECT) ((SOURCE STRING) (MODULE MODULE)) :DOCUMENTATION \"Unstringify a STELLA `source' string relative to `module',\nor `*MODULE*' if no module is specified.  This function allocates transient\nobjects as opposed to `unstringify-in-module' or the regular `unstringify'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unstringifyStellaSource)), NULL);
      defineFunctionObject("COLLECT-FEATURE-LIST", "(DEFUN (COLLECT-FEATURE-LIST (LIST OF GENERALIZED-SYMBOL)) ((TREE OBJECT)))", ((cpp_function_code)(&collectFeatureList)), NULL);
      defineFunctionObject("COLLECT-KEY-VALUE-LIST", "(DEFUN (COLLECT-KEY-VALUE-LIST (KEY-VALUE-LIST OF GENERALIZED-SYMBOL OBJECT)) ((TREE OBJECT)))", ((cpp_function_code)(&collectKeyValueList)), NULL);
      defineFunctionObject("DEFINE-INLINE-METHOD", "(DEFUN (DEFINE-INLINE-METHOD METHOD-SLOT) ((NAME SYMBOL) (PARAMETERSANDBODY CONS)))", ((cpp_function_code)(&defineInlineMethod)), NULL);
      defineFunctionObject("HELP-DEFINE-CLASS-FROM-PARSE-TREE", "(DEFUN (HELP-DEFINE-CLASS-FROM-PARSE-TREE CLASS) ((PARSETREE CONS) (STRINGIFIEDSOURCE STRING)))", ((cpp_function_code)(&helpDefineClassFromParseTree)), NULL);
      defineFunctionObject("DEFINE-STORAGE-SLOT-FROM-PARSE-TREE", "(DEFUN (DEFINE-STORAGE-SLOT-FROM-PARSE-TREE STORAGE-SLOT) ((SLOTDEF CONS) (OWNER TYPE)))", ((cpp_function_code)(&defineStorageSlotFromParseTree)), NULL);
      defineFunctionObject("RECORD-SLOT-HOME-MODULE", "(DEFUN (RECORD-SLOT-HOME-MODULE MODULE) ((SELF SLOT)))", ((cpp_function_code)(&recordSlotHomeModule)), NULL);
      defineFunctionObject("EXPLICITLY-QUALIFIED-NAME?", "(DEFUN (EXPLICITLY-QUALIFIED-NAME? BOOLEAN) ((NAME GENERALIZED-SYMBOL) (DEFINITIONMODULE MODULE)))", ((cpp_function_code)(&explicitlyQualifiedNameP)), NULL);
      defineFunctionObject("GET-IDENTICAL-CLASS", "(DEFUN (GET-IDENTICAL-CLASS CLASS) ((CLASSNAME STRING) (STRINGIFIEDSOURCE STRING)) :PUBLIC? TRUE)", ((cpp_function_code)(&getIdenticalClass)), NULL);
      defineFunctionObject("DEFINE-CLASS-FROM-PARSE-TREE", "(DEFUN (DEFINE-CLASS-FROM-PARSE-TREE CLASS) ((PARSETREE CONS)) :PUBLIC? TRUE)", ((cpp_function_code)(&defineClassFromParseTree)), NULL);
      defineFunctionObject("DEFINE-CLASS-FROM-STRINGIFIED-SOURCE", "(DEFUN (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE CLASS) ((CLASSNAME STRING) (STRINGIFIEDSOURCE STRING)) :PUBLIC? TRUE)", ((cpp_function_code)(&defineClassFromStringifiedSource)), NULL);
      defineFunctionObject("EXTRACT-OPTIONS", "(DEFUN (EXTRACT-OPTIONS CONS) ((TREE CONS) (OPTIONSTABLE KEY-VALUE-LIST)) :PUBLIC? TRUE)", ((cpp_function_code)(&extractOptions)), NULL);
      defineFunctionObject("DESTRUCTURE-DEFMETHOD-TREE", "(DEFUN (DESTRUCTURE-DEFMETHOD-TREE OBJECT CONS CONS) ((METHOD-TREE CONS) (OPTIONS-TABLE KEY-VALUE-LIST)) :PUBLIC? TRUE :DOCUMENTATION \"Return three parse trees representing the name,\nparameters, and code body of the parse tree `method-tree'.  Fill\n`options-table' with a dictionary of method options.\nStorage note:  Options are treated specially because the other return\nvalues are subtrees of `method-tree', while `options-table' is a newly-created\ncons tree.  Note also, the parameter and body trees are destructively\nremoved from `method-tree'.\")", ((cpp_function_code)(&destructureDefmethodTree)), NULL);
      defineFunctionObject("YIELD-SETTER-METHOD-NAME", "(DEFUN (YIELD-SETTER-METHOD-NAME SYMBOL) ((METHODNAME SYMBOL)))", ((cpp_function_code)(&yieldSetterMethodName)), NULL);
      defineFunctionObject("DESTRUCTURE-METHOD-NAME-TREE", "(DEFUN (DESTRUCTURE-METHOD-NAME-TREE SYMBOL CONS) ((NAMETREE OBJECT)))", ((cpp_function_code)(&destructureMethodNameTree)), NULL);
      defineFunctionObject("IN-PLACE-NORMALIZE-METHOD-OPTIONS", "(DEFUN IN-PLACE-NORMALIZE-METHOD-OPTIONS ((METHODOPTIONS KEYWORD-KEY-VALUE-LIST) (METHODNAME SYMBOL)))", ((cpp_function_code)(&inPlaceNormalizeMethodOptions)), NULL);
      defineFunctionObject("GET-FUNCTION-WITH-IDENTICAL-SIGNATURE", "(DEFUN (GET-FUNCTION-WITH-IDENTICAL-SIGNATURE METHOD-SLOT) ((NAME SYMBOL) (STRINGIFIEDSOURCE STRING)))", ((cpp_function_code)(&getFunctionWithIdenticalSignature)), NULL);
      defineFunctionObject("GET-METHOD-WITH-IDENTICAL-SIGNATURE", "(DEFUN (GET-METHOD-WITH-IDENTICAL-SIGNATURE METHOD-SLOT) ((NAME SYMBOL) (PARAMETERSTREE CONS) (STRINGIFIEDSOURCE STRING)))", ((cpp_function_code)(&getMethodWithIdenticalSignature)), NULL);
      defineFunctionObject("HELP-DEFINE-METHOD-FROM-PARSE-TREE", "(DEFUN (HELP-DEFINE-METHOD-FROM-PARSE-TREE METHOD-SLOT BOOLEAN) ((INPUTTREE CONS) (STRINGIFIEDSOURCE STRING)))", ((cpp_function_code)(&helpDefineMethodFromParseTree)), NULL);
      defineFunctionObject("DEFINE-METHOD-FROM-PARSE-TREE", "(DEFUN (DEFINE-METHOD-FROM-PARSE-TREE METHOD-SLOT) ((PARSETREE CONS)))", ((cpp_function_code)(&defineMethodFromParseTree)), NULL);
      defineFunctionObject("STRINGIFY-METHOD-SIGNATURE", "(DEFUN (STRINGIFY-METHOD-SIGNATURE STRING) ((PARSETREE CONS)))", ((cpp_function_code)(&stringifyMethodSignature)), NULL);
      defineFunctionObject("STRINGIFY-METHOD-BODY?", "(DEFUN (STRINGIFY-METHOD-BODY? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&stringifyMethodBodyP)), NULL);
      defineFunctionObject("DEFINE-METHOD-FROM-STRINGIFIED-SOURCE", "(DEFUN (DEFINE-METHOD-FROM-STRINGIFIED-SOURCE METHOD-SLOT) ((METHODNAME STRING) (CLASSNAME STRING) (STRINGIFIEDSOURCE STRING)) :PUBLIC? TRUE)", ((cpp_function_code)(&defineMethodFromStringifiedSource)), NULL);
      defineFunctionObject("DEFINE-METHOD-OBJECT", "(DEFUN DEFINE-METHOD-OBJECT ((DEFINITION STRING) (CODE CODE-WRAPPER) (WRAPPERCODE CODE-WRAPPER)))", ((cpp_function_code)(&defineMethodObject)), NULL);
      defineFunctionObject("DEFINE-INLINE-METHOD-CODE", "(DEFUN DEFINE-INLINE-METHOD-CODE ((CLASSTYPE SURROGATE) (METHODNAME SYMBOL) (CODE CODE-WRAPPER) (WRAPPERCODE CODE-WRAPPER)))", ((cpp_function_code)(&defineInlineMethodCode)), NULL);
      defineFunctionObject("DEFINE-EXTERNAL-SLOT-FROM-PARSE-TREE", "(DEFUN (DEFINE-EXTERNAL-SLOT-FROM-PARSE-TREE STORAGE-SLOT) ((PARSETREE CONS)))", ((cpp_function_code)(&defineExternalSlotFromParseTree)), NULL);
      defineFunctionObject("DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE", "(DEFUN (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE STORAGE-SLOT) ((STRINGIFIEDSOURCE STRING)) :PUBLIC? TRUE)", ((cpp_function_code)(&defineExternalSlotFromStringifiedSource)), NULL);
      defineFunctionObject("LOOKUP-SLOT-FROM-OPTION-KEYWORD", "(DEFUN (LOOKUP-SLOT-FROM-OPTION-KEYWORD STORAGE-SLOT) ((OWNER TYPE) (KEYWORD KEYWORD)))", ((cpp_function_code)(&lookupSlotFromOptionKeyword)), NULL);
      defineFunctionObject("LOOKUP-OPTION-HANDLER", "(DEFUN (LOOKUP-OPTION-HANDLER METHOD-SLOT) ((SLOT STORAGE-SLOT)) :PUBLIC? TRUE)", ((cpp_function_code)(&lookupOptionHandler)), NULL);
      defineFunctionObject("RUN-OPTION-HANDLER?", "(DEFUN (RUN-OPTION-HANDLER? BOOLEAN) ((OBJECT OBJECT) (OPTION KEYWORD) (VALUETREE OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&runOptionHandlerP)), NULL);
      defineFunctionObject("DEFAULT-OPTION-HANDLER", "(DEFUN DEFAULT-OPTION-HANDLER ((SELF OBJECT) (SLOT STORAGE-SLOT) (TREE OBJECT)))", ((cpp_function_code)(&defaultOptionHandler)), NULL);
      defineFunctionObject("STARTUP-STELLA-IN", "(DEFUN STARTUP-STELLA-IN () :PUBLIC? TRUE)", ((cpp_function_code)(&startupStellaIn)), NULL);
      { MethodSlot* function = lookupFunction(SYM_STELLA_IN_STELLA_STARTUP_STELLA_IN);

        setDynamicSlotValue(function->dynamicSlots, SYM_STELLA_IN_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupStellaIn"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *REDEFINE-IDENTICAL-CLASSES?* BOOLEAN FALSE :DOCUMENTATION \"If `true', always redefine classes, even if an\n                  identical class exists\")", &oREDEFINE_IDENTICAL_CLASSESpo);
      defineGlobalVariableObject("(DEFGLOBAL *UNSUPPORTED-EXTERNAL-SLOT-OPTIONS* (LIST OF KEYWORD) (LIST :ALLOCATION :INITIALLY :CONTEXT-SENSITIVE? :HARDWIRED?))", &oUNSUPPORTED_EXTERNAL_SLOT_OPTIONSo);
      defineGlobalVariableObject("(DEFGLOBAL *DEFAULT-OPTION-HANDLER* METHOD-SLOT NULL)", &oDEFAULT_OPTION_HANDLERo);
      oDEFAULT_OPTION_HANDLERo = lookupFunction(SYM_STELLA_IN_STELLA_DEFAULT_OPTION_HANDLER);
    }
  }
}

Symbol* SYM_STELLA_IN_STELLA_TRUE = NULL;

Symbol* SYM_STELLA_IN_STELLA_FALSE = NULL;

Surrogate* SGT_STELLA_IN_STELLA_CONS = NULL;

Surrogate* SGT_STELLA_IN_STELLA_GENERALIZED_SYMBOL = NULL;

Symbol* SYM_STELLA_IN_STELLA_DEFMETHOD = NULL;

Keyword* KWD_STELLA_IN_PUBLIC_SLOTS = NULL;

Keyword* KWD_STELLA_IN_SLOTS = NULL;

Keyword* KWD_STELLA_IN_PUBLIC_METHODS = NULL;

Keyword* KWD_STELLA_IN_METHODS = NULL;

Keyword* KWD_STELLA_IN_PARAMETERS = NULL;

Keyword* KWD_STELLA_IN_KEY = NULL;

Keyword* KWD_STELLA_IN_SYNONYMS = NULL;

Keyword* KWD_STELLA_IN_DOCUMENTATION = NULL;

Keyword* KWD_STELLA_IN_CL_NATIVE_TYPE = NULL;

Keyword* KWD_STELLA_IN_CPP_NATIVE_TYPE = NULL;

Keyword* KWD_STELLA_IN_JAVA_NATIVE_TYPE = NULL;

Keyword* KWD_STELLA_IN_IDL_NATIVE_TYPE = NULL;

Keyword* KWD_STELLA_IN_ABSTRACTp = NULL;

Keyword* KWD_STELLA_IN_ACTIVEp = NULL;

Keyword* KWD_STELLA_IN_PUBLICp = NULL;

Keyword* KWD_STELLA_IN_CL_STRUCTp = NULL;

Keyword* KWD_STELLA_IN_MIXINp = NULL;

Keyword* KWD_STELLA_IN_RECYCLE_METHOD = NULL;

Symbol* SYM_STELLA_IN_STELLA_NEXT_SWEEP_LIST_OBJECT = NULL;

Keyword* KWD_STELLA_IN_TYPE = NULL;

Keyword* KWD_STELLA_IN_EXTENSION = NULL;

Keyword* KWD_STELLA_IN_CREATOR = NULL;

Keyword* KWD_STELLA_IN_DESTRUCTOR = NULL;

Keyword* KWD_STELLA_IN_INITIALIZER = NULL;

Keyword* KWD_STELLA_IN_TERMINATOR = NULL;

Keyword* KWD_STELLA_IN_EQUALITY_TEST = NULL;

Keyword* KWD_STELLA_IN_INITIAL_VALUE = NULL;

Keyword* KWD_STELLA_IN_PRINT_FORM = NULL;

Keyword* KWD_STELLA_IN_PROPERTIES = NULL;

Keyword* KWD_STELLA_IN_META_ATTRIBUTES = NULL;

Keyword* KWD_STELLA_IN_CHILDREN = NULL;

Keyword* KWD_STELLA_IN_INITIALLY = NULL;

Keyword* KWD_STELLA_IN_DEFAULT = NULL;

Symbol* SYM_STELLA_IN_STELLA_LIKE = NULL;

Keyword* KWD_STELLA_IN_ALLOCATION = NULL;

Keyword* KWD_STELLA_IN_READER = NULL;

Keyword* KWD_STELLA_IN_WRITER = NULL;

Keyword* KWD_STELLA_IN_INVERSE = NULL;

Keyword* KWD_STELLA_IN_RENAMES = NULL;

Keyword* KWD_STELLA_IN_REQUIREDp = NULL;

Keyword* KWD_STELLA_IN_COMPONENTp = NULL;

Keyword* KWD_STELLA_IN_READ_ONLYp = NULL;

Keyword* KWD_STELLA_IN_CONTEXT_SENSITIVEp = NULL;

Keyword* KWD_STELLA_IN_HARDWIREDp = NULL;

Keyword* KWD_STELLA_IN_OPTION_KEYWORD = NULL;

Keyword* KWD_STELLA_IN_OPTION_HANDLER = NULL;

Symbol* SYM_STELLA_IN_STELLA_SLOT_HOME_MODULE = NULL;

Symbol* SYM_STELLA_IN_STELLA_SETTER = NULL;

Keyword* KWD_STELLA_IN_RETURN_TYPES = NULL;

Keyword* KWD_STELLA_IN_STORAGE_SLOT = NULL;

Keyword* KWD_STELLA_IN_INHERITS_THROUGH = NULL;

Keyword* KWD_STELLA_IN_SETTERp = NULL;

Keyword* KWD_STELLA_IN_NATIVEp = NULL;

Keyword* KWD_STELLA_IN_CONSTRUCTORp = NULL;

Keyword* KWD_STELLA_IN_AUXILIARYp = NULL;

Keyword* KWD_STELLA_IN_GLOBALLY_INLINEp = NULL;

Keyword* KWD_STELLA_IN_COMMANDp = NULL;

Keyword* KWD_STELLA_IN_LISP_MACROp = NULL;

Keyword* KWD_STELLA_IN_EVALUATE_ARGUMENTSp = NULL;

Keyword* KWD_STELLA_IN_C_CALLABLEp = NULL;

Keyword* KWD_STELLA_IN_INLINE = NULL;

Symbol* SYM_STELLA_IN_STELLA_DEFUN = NULL;

Symbol* SYM_STELLA_IN_STELLA_SLOT_AUXILIARYp = NULL;

Symbol* SYM_STELLA_IN_STELLA_METHOD_GLOBALLY_INLINEp = NULL;

Keyword* KWD_STELLA_IN_DYNAMIC = NULL;

Surrogate* SGT_STELLA_IN_STELLA_DYNAMIC_SLOTS_MIXIN = NULL;

Symbol* SYM_STELLA_IN_STELLA_SLOT_OPTION_KEYWORD = NULL;

Symbol* SYM_STELLA_IN_STELLA_DEFAULT_OPTION_HANDLER = NULL;

Symbol* SYM_STELLA_IN_STELLA_SLOT_OPTION_HANDLER = NULL;

Surrogate* SGT_STELLA_IN_STELLA_BOOLEAN = NULL;

Symbol* SYM_STELLA_IN_STELLA_STARTUP_STELLA_IN = NULL;

Symbol* SYM_STELLA_IN_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
