//  -*- Mode: C++ -*-

// systems.cc

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

Cons* oFILE_LOAD_PATHo = NULL;

Cons* parseDirectoryPath(const char* path) {
  { char separator = '|';
    int length = strlen(path);
    int start = 0;
    int end = 0;
    Cons* parsedpath = NIL;

    for (;;) {
      end = stringPosition(path, separator, start);
      parsedpath = cons(wrapString(fileNameAsDirectory(stringSubsequence(path, start, end))), parsedpath);
      if ((end != NULL_INTEGER) &&
          (end < (length - 1))) {
        start = end + 1;
      }
      else {
        break;
      }
    }
    return (parsedpath->reverse());
  }
}

Cons* setLoadPath(const char* path) {
  // Set the STELLA load path to the |-separated
  // directories listed in `path'.  Return the resulting load path.
  oFILE_LOAD_PATHo = parseDirectoryPath(path);
  return (oFILE_LOAD_PATHo);
}

Cons* setLoadPathEvaluatorWrapper(Cons* arguments) {
  return (setLoadPath(((StringWrapper*)(arguments->value))->wrapperValue));
}

Cons* getLoadPath() {
  // Return the current STELLA load path.
  return (oFILE_LOAD_PATHo);
}

Cons* pushLoadPath(const char* path) {
  // Add the directories listed in the |-separated
  // `path' to the front of the STELLA load path.  Return the
  // resulting load path.
  oFILE_LOAD_PATHo = parseDirectoryPath(path)->concatenate(oFILE_LOAD_PATHo, 0);
  return (oFILE_LOAD_PATHo);
}

Cons* pushLoadPathEvaluatorWrapper(Cons* arguments) {
  return (pushLoadPath(((StringWrapper*)(arguments->value))->wrapperValue));
}

const char* popLoadPath() {
  // Remove the first element from the STELLA load path
  // and return the removed element.
  { StringWrapper* head000 = ((StringWrapper*)(oFILE_LOAD_PATHo->value));

    oFILE_LOAD_PATHo = oFILE_LOAD_PATHo->rest;
    { StringWrapper* value000 = head000;

      return (value000->wrapperValue);
    }
  }
}

StringWrapper* popLoadPathEvaluatorWrapper(Cons* arguments) {
  arguments = arguments;
  { const char* result = popLoadPath();

    if (result != NULL) {
      return (wrapString(result));
    }
    else {
      return (NULL);
    }
  }
}

Cons* addLoadPath(const char* path) {
  // Append the directories listed in the |-separated
  // `path' to the end of the STELLA load path.  Return the resulting
  // load path.
  oFILE_LOAD_PATHo = oFILE_LOAD_PATHo->concatenate(parseDirectoryPath(path), 0);
  return (oFILE_LOAD_PATHo);
}

Cons* addLoadPathEvaluatorWrapper(Cons* arguments) {
  return (addLoadPath(((StringWrapper*)(arguments->value))->wrapperValue));
}

Cons* dropLoadPath(const char* path) {
  // Remove the directories listed in the |-separated
  // `path' from the PowerLoom load path.
  { StringWrapper* dir = NULL;
    Cons* iter000 = parseDirectoryPath(path);

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      dir = ((StringWrapper*)(iter000->value));
      oFILE_LOAD_PATHo = oFILE_LOAD_PATHo->remove(dir);
    }
  }
  return (oFILE_LOAD_PATHo);
}

Cons* dropLoadPathEvaluatorWrapper(Cons* arguments) {
  return (dropLoadPath(((StringWrapper*)(arguments->value))->wrapperValue));
}

// File extensions to append by default when a
// file is looked up by `find-file-in-load-path'.
Cons* oSTELLA_FILE_EXTENSIONSo = NULL;

const char* findFileInLoadPath(const char* file, Cons* extensions) {
  // Try to find `file' in the current load path and, if found,
  // return its full name.  If `file' can't be found literally, try to find it
  // with any of the listed `extensions' added.  If `extensions' is NULL it defaults
  // to `*stella-file-extensions*', therefore, to not default to any extensions
  // the value has to be supplied as NIL.
  { const char* expandedfile = file;

    if (!((boolean)(extensions))) {
      extensions = oSTELLA_FILE_EXTENSIONSo;
    }
    { Object* dir = NULL;
      Cons* iter000 = cons(wrapString(""), oFILE_LOAD_PATHo);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        dir = iter000->value;
        try {
          expandedfile = stringConcatenate(unwrapString(((StringWrapper*)(dir))), file, 0);
          if (probeFileP(expandedfile)) {
            return (expandedfile);
          }
          { StringWrapper* ext = NULL;
            Cons* iter001 = extensions;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              ext = ((StringWrapper*)(iter001->value));
              expandedfile = stringConcatenate(unwrapString(((StringWrapper*)(dir))), file, 1, ext->wrapperValue);
              if (probeFileP(expandedfile)) {
                return (expandedfile);
              }
            }
          }
        }
        catch (std::exception& _e) {
          std::exception* e = &_e;

          e = e;
        }
      }
    }
    return (NULL);
  }
}

StringWrapper* findFileInLoadPathEvaluatorWrapper(Cons* arguments) {
  { const char* result = findFileInLoadPath(((StringWrapper*)(arguments->value))->wrapperValue, ((Cons*)(arguments->rest->value)));

    if (result != NULL) {
      return (wrapString(result));
    }
    else {
      return (NULL);
    }
  }
}

BooleanWrapper* coerceValueToBoolean(Object* value, boolean errorP) {
  // Return the boolean object represented by `value'.  Return NULL
  // if coercion is not possible or raise an error if `error?' is TRUE.
  if ((value == SYM_SYSTEMS_STELLA_TRUE) ||
      (value == KWD_SYSTEMS_TRUE)) {
    return (TRUE_WRAPPER);
  }
  else if ((value == SYM_SYSTEMS_STELLA_FALSE) ||
      (value == KWD_SYSTEMS_FALSE)) {
    return (FALSE_WRAPPER);
  }
  { Surrogate* testValue000 = safePrimaryType(value);

    if (subtypeOfSymbolP(testValue000)) {
      { Object* value000 = value;
        Symbol* value = ((Symbol*)(value000));

        if (stringEqualP(value->symbolName, "TRUE")) {
          return (TRUE_WRAPPER);
        }
        else if (stringEqualP(value->symbolName, "FALSE")) {
          return (FALSE_WRAPPER);
        }
      }
    }
    else if (subtypeOfKeywordP(testValue000)) {
      { Object* value001 = value;
        Keyword* value = ((Keyword*)(value001));

        if (stringEqualP(value->symbolName, "TRUE")) {
          return (TRUE_WRAPPER);
        }
        else if (stringEqualP(value->symbolName, "FALSE")) {
          return (FALSE_WRAPPER);
        }
      }
    }
    else if (subtypeOfStringP(testValue000)) {
      { Object* value002 = value;
        StringWrapper* value = ((StringWrapper*)(value002));

        if (stringEqualP(value->wrapperValue, "TRUE")) {
          return (TRUE_WRAPPER);
        }
        else if (stringEqualP(value->wrapperValue, "FALSE")) {
          return (FALSE_WRAPPER);
        }
      }
    }
    else if (subtypeOfBooleanP(testValue000)) {
      { Object* value003 = value;
        BooleanWrapper* value = ((BooleanWrapper*)(value003));

        return (value);
      }
    }
    else {
    }
  }
  if (errorP) {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "coerce-value-to-boolean: can't coerce " << "`" << value << "'" << " of type " << "`" << ((((boolean)(value)) ? value->primaryType() : SGT_SYSTEMS_STELLA_UNKNOWN)) << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  else {
    return (NULL);
  }
}

BooleanWrapper* coerceToBoolean(Object* object) {
  // Return the boolean object represented by `object'.
  // Return NULL if coercion is not possible.
  return (coerceValueToBoolean(object, false));
}

const char* coerceValueToString(Object* value, boolean errorP) {
  // Coerce `value' into a string if possible, return NULL
  // otherwise or raise an error if `error?' is true.
  { Surrogate* testValue000 = safePrimaryType(value);

    if (subtypeOfStringP(testValue000)) {
      { Object* value000 = value;
        StringWrapper* value = ((StringWrapper*)(value000));

        return (value->wrapperValue);
      }
    }
    else if (subtypeOfP(testValue000, SGT_SYSTEMS_STELLA_GENERALIZED_SYMBOL)) {
      { Object* value001 = value;
        GeneralizedSymbol* value = ((GeneralizedSymbol*)(value001));

        return (value->symbolName);
      }
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { Object* value002 = value;
        IntegerWrapper* value = ((IntegerWrapper*)(value002));

        return (integerToString(((long long int)(value->wrapperValue))));
      }
    }
    else if (subtypeOfLongIntegerP(testValue000)) {
      { Object* value003 = value;
        LongIntegerWrapper* value = ((LongIntegerWrapper*)(value003));

        return (integerToString(value->wrapperValue));
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { Object* value004 = value;
        FloatWrapper* value = ((FloatWrapper*)(value004));

        return (floatToString(value->wrapperValue));
      }
    }
    else {
    }
  }
  if (errorP) {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "coerce-value-to-string: don't know how to coerce " << "`" << value << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  else {
    return (NULL);
  }
}

const char* coerceToString(Object* object) {
  // Coerce `object' into a string.  If no standard coercion
  // is possible, simply stringify `object'.
  { const char* string = coerceValueToString(object, false);

    if (string == NULL) {
      string = stringify(object);
    }
    return (string);
  }
}

double coerceValueToFloat(Object* value, boolean errorP) {
  // Coerce `value' to a float value if possible, return
  // NULL otherwise or raise an error if `error?' is true.
  { Surrogate* testValue000 = safePrimaryType(value);

    if (subtypeOfIntegerP(testValue000)) {
      { Object* value000 = value;
        IntegerWrapper* value = ((IntegerWrapper*)(value000));

        return (value->wrapperValue * 1.0);
      }
    }
    else if (subtypeOfLongIntegerP(testValue000)) {
      { Object* value001 = value;
        LongIntegerWrapper* value = ((LongIntegerWrapper*)(value001));

        return (value->wrapperValue * 1.0);
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { Object* value002 = value;
        FloatWrapper* value = ((FloatWrapper*)(value002));

        return (value->wrapperValue);
      }
    }
    else {
    }
  }
  if (errorP) {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "coerce-value-to-float: don't know how to coerce " << "`" << value << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  else {
    return (NULL_FLOAT);
  }
}

double coerceToFloat(Object* object) {
  // Coerce `number' to a float value or NULL if not possible.
  return (coerceValueToFloat(object, false));
}

Object* coerceValueToType(Object* value, Surrogate* type, boolean errorP) {
  // Coerce `value' to `type'.  Return NULL if not possible
  // or raise an error if `error?' is TRUE.
  if (type == SGT_SYSTEMS_STELLA_INTEGER) {
    { Surrogate* testValue000 = safePrimaryType(value);

      if (subtypeOfIntegerP(testValue000)) {
        { Object* value000 = value;
          IntegerWrapper* value = ((IntegerWrapper*)(value000));

          return (value);
        }
      }
      else if (subtypeOfFloatP(testValue000)) {
        { Object* value001 = value;
          FloatWrapper* value = ((FloatWrapper*)(value001));

          return (wrapInteger(stella::floor(value->wrapperValue)));
        }
      }
      else if (subtypeOfLongIntegerP(testValue000)) {
        { Object* value002 = value;
          LongIntegerWrapper* value = ((LongIntegerWrapper*)(value002));

          if ((value->wrapperValue >= NULL_INTEGER) &&
              (value->wrapperValue <= MOST_POSITIVE_INTEGER)) {
            return (value);
          }
        }
      }
      else {
      }
    }
  }
  else if (type == SGT_SYSTEMS_STELLA_FLOAT) {
    { double val = coerceValueToFloat(value, errorP);

      if (val != NULL_FLOAT) {
        return (wrapFloat(val));
      }
      else {
        return (NULL);
      }
    }
  }
  else if (type == SGT_SYSTEMS_STELLA_NUMBER) {
    { Surrogate* testValue001 = safePrimaryType(value);

      if (subtypeOfIntegerP(testValue001)) {
        { Object* value003 = value;
          IntegerWrapper* value = ((IntegerWrapper*)(value003));

          return (value);
        }
      }
      else if (subtypeOfLongIntegerP(testValue001)) {
        { Object* value004 = value;
          LongIntegerWrapper* value = ((LongIntegerWrapper*)(value004));

          return (value);
        }
      }
      else if (subtypeOfFloatP(testValue001)) {
        { Object* value005 = value;
          FloatWrapper* value = ((FloatWrapper*)(value005));

          return (value);
        }
      }
      else {
      }
    }
  }
  else if (type == SGT_SYSTEMS_STELLA_STRING) {
    { const char* val = coerceValueToString(value, errorP);

      if (val != NULL) {
        return (wrapString(val));
      }
      else {
        return (NULL);
      }
    }
  }
  else if (type == SGT_SYSTEMS_STELLA_KEYWORD) {
    { Surrogate* testValue002 = safePrimaryType(value);

      if (subtypeOfP(testValue002, SGT_SYSTEMS_STELLA_GENERALIZED_SYMBOL)) {
        { Object* value006 = value;
          GeneralizedSymbol* value = ((GeneralizedSymbol*)(value006));

          return (value->keywordify());
        }
      }
      else if (subtypeOfStringP(testValue002)) {
        { Object* value007 = value;
          StringWrapper* value = ((StringWrapper*)(value007));

          return (value->keywordify());
        }
      }
      else {
      }
    }
  }
  else if (type == SGT_SYSTEMS_STELLA_SYMBOL) {
    { Surrogate* testValue003 = safePrimaryType(value);

      if (subtypeOfKeywordP(testValue003)) {
        { Object* value008 = value;
          Keyword* value = ((Keyword*)(value008));

          return (internSymbol(value->symbolName));
        }
      }
      else if (subtypeOfSurrogateP(testValue003)) {
        { Object* value009 = value;
          Surrogate* value = ((Surrogate*)(value009));

          return (internDerivedSymbol(value, value->symbolName));
        }
      }
      else if (subtypeOfSymbolP(testValue003)) {
        { Object* value010 = value;
          Symbol* value = ((Symbol*)(value010));

          return (value);
        }
      }
      else if (subtypeOfStringP(testValue003)) {
        { Object* value011 = value;
          StringWrapper* value = ((StringWrapper*)(value011));

          return (internSymbol(value->wrapperValue));
        }
      }
      else {
      }
    }
  }
  else if (type == SGT_SYSTEMS_STELLA_BOOLEAN) {
    return (coerceValueToBoolean(value, errorP));
  }
  else if (type == SGT_SYSTEMS_STELLA_MODULE) {
    { Module* module = coerceToModule(value, false);

      if (((boolean)(module))) {
        return (module);
      }
    }
  }
  else {
    if (!((boolean)(type))) {
      return (value);
    }
    else if (isaP(value, type)) {
      return (value);
    }
    else if (isaP(value, type->typeToWrappedType())) {
      return (value);
    }
  }
  if (errorP) {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "coerce-value-to-type: don't know how to coerce " << "`" << value << "'" << " to type " << "`" << type << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  else {
    return (NULL);
  }
}

Object* coerceOptionValue(Object* value, Surrogate* type) {
  // Coerce `value' to `type'.  Return NULL if not possible.
  return (coerceValueToType(value, type, false));
}

PropertyList* vetOptions(Object* plist, Cons* legaloptions) {
  { PropertyList* propertylist = NULL;

    { Surrogate* testValue000 = safePrimaryType(plist);

      if (subtypeOfP(testValue000, SGT_SYSTEMS_STELLA_PROPERTY_LIST)) {
        { Object* plist000 = plist;
          PropertyList* plist = ((PropertyList*)(plist000));

          propertylist = plist;
        }
      }
      else if (testValue000 == SGT_SYSTEMS_STELLA_CONS) {
        { Object* plist001 = plist;
          Cons* plist = ((Cons*)(plist001));

          { PropertyList* self000 = newPropertyList();

            self000->thePlist = plist;
            propertylist = self000;
          }
        }
      }
      else if (subtypeOfP(testValue000, SGT_SYSTEMS_STELLA_LIST)) {
        { Object* plist002 = plist;
          List* plist = ((List*)(plist002));

          { PropertyList* self001 = newPropertyList();

            self001->thePlist = plist->theConsList;
            propertylist = self001;
          }
        }
      }
      else {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "Illegal argument passed to 'vet-options'" << std::endl;
        return (newPropertyList());
      }
    }
    { Object* key = NULL;
      Object* value = NULL;
      Cons* iter000 = propertylist->thePlist;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest->rest) {
        key = iter000->value;
        value = iter000->rest->value;
        if ((!stellaObjectP(key)) ||
            ((!keywordP(key)) ||
             (((boolean)(legaloptions)) &&
              (!legaloptions->memberP(key))))) {
          value = value;
          if (!stellaObjectP(key)) {
            { PropertyList* newplist = newPropertyList();

              { Object* key = NULL;
                Object* value = NULL;
                Cons* iter001 = propertylist->thePlist;

                for  (; !(iter001 == NIL); 
                      iter001 = iter001->rest->rest) {
                  key = iter001->value;
                  value = iter001->rest->value;
                  newplist->insertAt(stellify(key), stellify(value));
                }
              }
              propertylist->thePlist = newplist->thePlist;
            }
            vetOptions(propertylist, legaloptions);
            return (propertylist);
          }
          propertylist->removeAt(key);
          std::cout << "Skipping illegal option: " << "`" << key << "'" << std::endl << std::endl;
          if (keywordP(key)) {
            std::cout << "   Legal options are: " << "`" << legaloptions << "'" << std::endl << std::endl;
          }
          else {
            std::cout << "   Option must be a keyword." << std::endl;
          }
          vetOptions(propertylist, legaloptions);
          return (propertylist);
        }
      }
    }
    return (propertylist);
  }
}

PropertyList* parseOptions(Object* options, Cons* legaloptionsAtypes, boolean coercionerrorP, boolean allowotherkeysP) {
  // Parse `options', check their validity according to
  // `legalOptions&Types' and return the result as a PROPERTY-LIST.
  // `legalOptions&Types' has to either be NULL or a flat list of legal
  // <keyword> <coercionType> pairs.  A type specifcation of @IDENTITY
  // means don't perform any coercion.
  // If `coercionError?' is TRUE, raise an error if a coercion failed.
  // If `allowOtherKeys?' is TRUE options other than those specified in
  // `legalOptions&Types' are allowed but won't be coerced since we don't
  // know their type.  A special implicit :options keyword that does not
  // need to be declared can be used to pass in an already parsed options
  // list from a caller, which will then be analyzed and used instead.
  { PropertyList* self000 = newPropertyList();

    self000->thePlist = legaloptionsAtypes;
    { PropertyList* legaloptions = self000;
      PropertyList* parsedoptions = NULL;
      Object* passedoptions = NULL;
      Surrogate* type = NULL;
      Object* coercedvalue = NULL;

      { Surrogate* testValue000 = safePrimaryType(options);

        if (testValue000 == SGT_SYSTEMS_STELLA_CONS) {
          { Object* options000 = options;
            Cons* options = ((Cons*)(options000));

            if (((options->length()) % 2)) {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "Odd-length options list: " << "`" << options << "'";
                throw *newStellaException(stream000->theStringReader());
              }
            }
            { PropertyList* self003 = newPropertyList();

              self003->thePlist = options;
              parsedoptions = self003;
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_SYSTEMS_STELLA_PROPERTY_LIST)) {
          { Object* options001 = options;
            PropertyList* options = ((PropertyList*)(options001));

            parsedoptions = options;
          }
        }
        else {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "Illegal options specification: " << "`" << options << "'";
            throw *newStellaException(stream001->theStringReader());
          }
        }
      }
      passedoptions = parsedoptions->lookup(KWD_SYSTEMS_OPTIONS);
      if (((boolean)(passedoptions))) {
        return (parseOptions(passedoptions, legaloptionsAtypes, coercionerrorP, allowotherkeysP));
      }
      if (((boolean)(legaloptions))) {
        { Object* key = NULL;
          Object* value = NULL;
          Cons* iter000 = parsedoptions->thePlist;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest->rest) {
            key = iter000->value;
            value = iter000->rest->value;
            type = ((Surrogate*)(legaloptions->lookup(key)));
            if ((!((boolean)(type))) &&
                (!allowotherkeysP)) {
              { OutputStringStream* stream002 = newOutputStringStream();

                *(stream002->nativeStream) << "Illegal option: " << "`" << key << "'";
                throw *newStellaException(stream002->theStringReader());
              }
            }
            if (!((type == SGT_SYSTEMS_STELLA_IDENTITY) ||
                (!((boolean)(value))))) {
              coercedvalue = coerceValueToType(value, type, coercionerrorP);
              parsedoptions->insertAt(key, coercedvalue);
            }
          }
        }
      }
      return (parsedoptions);
    }
  }
}

// Full pathname of file that is currently being loaded (or similar).
DEFINE_STELLA_SPECIAL(oCURRENTLOADFILEo, const char* , NULL);

Object* evaluateCommand(Object* command, boolean finalizeP) {
  { boolean dummy1;

    { 
      BIND_STELLA_SPECIAL(oTRANSLATIONERRORSo, int, 0);
      BIND_STELLA_SPECIAL(oTRANSLATIONWARNINGSo, int, 0);
      BIND_STELLA_SPECIAL(oTRANSLATIONNOTESo, int, 0);
      BIND_STELLA_SPECIAL(oIGNORETRANSLATIONERRORSpo, boolean, false);
      BIND_STELLA_SPECIAL(oTRANSLATIONUNITSo, List*, NULL);
      BIND_STELLA_SPECIAL(oTRANSLATIONPHASEo, Keyword*, KWD_SYSTEMS_DEFINE);
      BIND_STELLA_SPECIAL(oEVALUATIONTREEo, Object*, NULL);
      { Object* operatoR = NULL;
        Object* result = NULL;

        { Surrogate* testValue000 = safePrimaryType(command);

          if (testValue000 == SGT_SYSTEMS_STELLA_CONS) {
            { Object* command000 = command;
              Cons* command = ((Cons*)(command000));

              operatoR = command->value;
              if (subtypeOfSymbolP(safePrimaryType(operatoR))) {
                { Object* operator000 = operatoR;
                  Symbol* operatoR = ((Symbol*)(operator000));

                  if (operatoR == SYM_SYSTEMS_STELLA_IN_MODULE) {
                    handleInModuleTree(command, false, false, dummy1);
                  }
                  else {
                    if (declarationTreeP(command)) {
                      oTRANSLATIONUNITSo = list(0);
                      walkTopLevelTree(command, false);
                      switch (oTRANSLATIONUNITSo->reverse()->length()) {
                        case 0: 
                          { OutputStringStream* stream000 = newOutputStringStream();

                            *(stream000->nativeStream) << "While evaluating '" << oEVALUATIONTREEo;
                            if (((boolean)(oEVALUATIONPARENTTREEo))) {
                              *(stream000->nativeStream) << std::endl << "' inside '" << oEVALUATIONPARENTTREEo;
                            }
                            *(stream000->nativeStream) << "':" << std::endl;
                            *(stream000->nativeStream) << "Couldn't translate " << "`" << command << "'";
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
                    else if (stringEqualP(operatoR->symbolName, "in-package")) {
                    }
                    else {
                      evaluate(command);
                    }
                  }
                }
              }
              else {
                evaluate(command);
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
            evaluate(command);
          }
        }
        if ((!translationErrorsP()) &&
            finalizeP) {
          oTRANSLATIONPHASEo = KWD_SYSTEMS_FINALIZE;
          if (((boolean)(oCURRENTSYSTEMDEFINITIONo))) {
            runSystemFinalization(oCURRENTSYSTEMDEFINITIONo);
          }
          else {
            std::cout << "Can't run finalization because *currentSystemDefinition* is not set." << std::endl;
          }
        }
        return (result);
      }
    }
  }
}

void loadFile(const char* file) {
  // Read STELLA commands from `file' and evaluate them.
  // The file should begin with an `in-module' declaration that specifies
  // the module within which all remaining commands are to be evaluated
  // The remaining commands are evaluated one-by-one, applying the function
  // `evaluate' to each of them.
  { const char* temp000 = findFileInLoadPath(file, NULL);

    file = ((temp000 != NULL) ? temp000 : file);
  }
  ensureFileExists(file, "load-file");
  { boolean toplevelinvocationP = oCURRENTFILENAMEo == NULL;
    boolean skipcommandP = false;
    boolean seeninmoduleP = false;
    Cons* commands = NIL;
    InputFileStream* inputstream = NULL;

    try {
      { 
        BIND_STELLA_SPECIAL(oCURRENTLOADFILEo, const char*, file);
        BIND_STELLA_SPECIAL(oCURRENTFILENAMEo, const char*, fileBaseName(file));
        inputstream = newInputFileStream(file);
        { 
          BIND_STELLA_SPECIAL(oMODULEo, Module*, oMODULEo);
          BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
          { Object* tree = NULL;
            SExpressionIterator* iter000 = sExpressions(inputstream);

            for (; iter000->nextP(); ) {
              tree = iter000->value;
              if (safePrimaryType(tree) == SGT_SYSTEMS_STELLA_CONS) {
                { Object* tree000 = tree;
                  Cons* tree = ((Cons*)(tree000));

                  skipcommandP = handleInModuleTree(tree, seeninmoduleP, true, seeninmoduleP);
                  if (skipcommandP) {
                    continue;
                  }
                  { Object* operatoR = tree->value;

                    if (subtypeOfSymbolP(safePrimaryType(operatoR))) {
                      { Object* operator000 = operatoR;
                        Symbol* operatoR = ((Symbol*)(operator000));

                        if ((operatoR == SYM_SYSTEMS_STELLA_DEFMODULE) ||
                            ((operatoR == SYM_SYSTEMS_STELLA_DEFSYSTEM) ||
                             ((operatoR == SYM_SYSTEMS_STELLA_DEFCLASS) ||
                              ((operatoR == SYM_SYSTEMS_STELLA_DEFSLOT) ||
                               ((operatoR == SYM_SYSTEMS_STELLA_DEFUN) ||
                                (operatoR == SYM_SYSTEMS_STELLA_DEFMETHOD)))))) {
                          evaluateCommand(tree, false);
                        }
                        else {
                          if (((boolean)(lookupCommand(operatoR)))) {
                            commands = cons(tree, commands);
                          }
                          else {
                            evaluateCommand(tree, false);
                          }
                        }
                      }
                    }
                    else {
                      evaluateCommand(tree, false);
                    }
                  }
                }
              }
              else {
                evaluateCommand(tree, false);
              }
            }
          }
          { 
            BIND_STELLA_SPECIAL(oTRANSLATIONPHASEo, Keyword*, KWD_SYSTEMS_FINALIZE);
            runSystemFinalization(oCURRENTSYSTEMDEFINITIONo);
          }
          { boolean finalizeP = ((boolean)(oCURRENTSYSTEMDEFINITIONo));

            { Object* tree = NULL;
              Cons* iter001 = commands->reverse();

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                tree = iter001->value;
                evaluateCommand(tree, finalizeP);
              }
            }
          }
        }
      }
    }
catch (...) {
      if (toplevelinvocationP) {
        sweepTransients();
      }
      if (((boolean)(inputstream))) {
        inputstream->free();
      }
      throw;
    }
    if (toplevelinvocationP) {
      sweepTransients();
    }
    if (((boolean)(inputstream))) {
      inputstream->free();
    }
  }
}

void loadFileEvaluatorWrapper(Cons* arguments) {
  loadFile(((StringWrapper*)(arguments->value))->wrapperValue);
}

// A list of all defined systems.
List* oSYSTEMDEFINITIONSo = NULL;

const char* makeSystemDefinitionFileName(const char* name) {
  // Make a canonical system definition file name for a system named `name'.
  return (stringConcatenate(stringDowncase(name), "-system.ste", 0));
}

Cons* buildStellaSystemsPath() {
  { const char* explicitpathvalue = getenv("STELLA_SYSTEMS_PATH", consList(1, wrapString(":")));
    List* explicitpath = newList();
    List* implicitpath = newList();

    { StringWrapper* dir = NULL;
      Cons* iter000 = splitString(explicitpathvalue, ':');

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        dir = ((StringWrapper*)(iter000->value));
        if (!blankStringP(dir->wrapperValue)) {
          explicitpath->insertNew(dir);
        }
      }
    }
    explicitpath->reverse();
    if (explicitpath->nonEmptyP() &&
        ((!startsWithP(explicitpathvalue, ":", 0)) &&
         (!endsWithP(explicitpathvalue, ":", NULL_INTEGER)))) {
      return (explicitpath->consify());
    }
    implicitpath->insertNew(wrapString(findSystemRootDirectoryFromFile(rootSourceDirectory())));
    implicitpath->insertNew(wrapString(findSystemRootDirectoryFromFile(rootNativeDirectory())));
    implicitpath->insertNew(wrapString(findSystemRootDirectoryFromFile(rootBinaryDirectory())));
    { StringWrapper* dir = NULL;
      Cons* iter001 = systemDefinitionDirectories();

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        dir = ((StringWrapper*)(iter001->value));
        implicitpath->insertNew(dir);
      }
    }
    { SystemDefinition* sys = NULL;
      Cons* iter002 = oSYSTEMDEFINITIONSo->theConsList;

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        sys = ((SystemDefinition*)(iter002->value));
        implicitpath->insertNew(wrapString(findSystemRootDirectory(sys)));
      }
    }
    if (explicitpath->emptyP()) {
      { StringWrapper* dir = NULL;
        Cons* iter003 = implicitpath->copy()->theConsList;

        for (; !(iter003 == NIL); iter003 = iter003->rest) {
          dir = ((StringWrapper*)(iter003->value));
          if ((!blankStringP(dir->wrapperValue)) &&
              probeDirectoryP(dir->wrapperValue)) {
            { const char* systemparentdir = directoryParentDirectory(dir->wrapperValue, 1);
              Cons* systemparentdirfiles = listDirectoryFiles(systemparentdir);

              { StringWrapper* dir = NULL;
                Cons* iter004 = systemparentdirfiles;

                for (; !(iter004 == NIL); iter004 = iter004->rest) {
                  dir = ((StringWrapper*)(iter004->value));
                  dir = wrapString(fileNameAsDirectory(concatenateFileNames(systemparentdir, 1, dir->wrapperValue)));
                  if (probeFileP(dir->wrapperValue) &&
                      topLevelStellaSystemDirectoryP(dir->wrapperValue)) {
                    implicitpath->insertNew(dir);
                  }
                }
              }
            }
          }
        }
      }
    }
    implicitpath->reverse()->remove(NULL_STRING_WRAPPER);
    if (startsWithP(explicitpathvalue, ":", 0)) {
      return (((Cons*)(implicitpath->concatenate(explicitpath, 0)->consify())));
    }
    else {
      return (((Cons*)(explicitpath->concatenate(implicitpath, 0)->consify())));
    }
  }
}

const char* findSystemDefinitionFile(const char* name) {
  // Try to find an existing system definition file for a system named `name'
  // in the current STELLA_SYSTEMS_PATH or built-in implicit systems path.  Return NULL if no
  // such definition file can be found.  See `build-stella-systems-path' on where it looks.
  { const char* systemfilename = makeSystemDefinitionFileName(name);
    const char* systemfile = NULL;
    Cons* relativesystemdirs = consList(3, wrapString(""), wrapString("systems"), wrapString(concatenateFileNames("sources", 1, "systems")));

    { StringWrapper* dir = NULL;
      Cons* iter000 = buildStellaSystemsPath();

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        dir = ((StringWrapper*)(iter000->value));
        if ((!blankStringP(dir->wrapperValue)) &&
            probeDirectoryP(dir->wrapperValue)) {
          { Object* subdir = NULL;
            Cons* iter001 = relativesystemdirs;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              subdir = iter001->value;
              systemfile = concatenateFileNames(dir->wrapperValue, 2, ((StringWrapper*)(subdir))->wrapperValue, systemfilename);
              if (probeFileP(systemfile)) {
                return (systemfile);
              }
            }
          }
        }
      }
    }
    return (NULL);
  }
}

const char* findSystemRootDirectoryFromFile(const char* sysdeffile) {
  // Given a system definition file `sysDefFile' try to determine the root directory
  // of the STELLA installation containing this system by looking for top-level native directories.
  { const char* directory = fileNameDirectory(sysdeffile);
    const char* parent = directory;

    { int level = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = 4;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        level = iter000;
        parent = directoryParentDirectory(directory, level);
        if (topLevelStellaSystemDirectoryP(parent)) {
          return (parent);
        }
      }
    }
    return (NULL);
  }
}

const char* findSystemRootDirectory(SystemDefinition* system) {
  // Given a system definition `system' try to determine the root directory
  // of the STELLA installation containing this system based on its definition file.
  { const char* sysdeffile = system->definitionFile;

    if (sysdeffile != NULL) {
      return (findSystemRootDirectoryFromFile(sysdeffile));
    }
    else {
      return (NULL);
    }
  }
}

void computeSystemRootDirectories(SystemDefinition* system) {
  // Compute any root directories for sources, native and Lisp binary directories
  // in case they were not explicitly specified in `system's definition.  Raises an error in case
  // any of those root directories is missing and can't be computed.
  { const char* systemrootdir = findSystemRootDirectory(system);

    if (systemrootdir != NULL) {
      { SystemDefinition* value000 = NULL;

        { SystemDefinition* sys = NULL;
          Cons* iter000 = oSYSTEMDEFINITIONSo->theConsList;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            sys = ((SystemDefinition*)(iter000->value));
            if (stringEqlP(findSystemRootDirectory(sys), systemrootdir)) {
              value000 = sys;
              break;
            }
          }
        }
        { SystemDefinition* temp000 = value000;

          { SystemDefinition* referencesystem = (((boolean)(temp000)) ? temp000 : system);

            { const char* temp001 = referencesystem->sourceRootDirectory;

              { const char* rootsourcedefault = ((temp001 != NULL) ? temp001 : concatenateFileNames(systemrootdir, 1, relativeUnlogicalizePathname(oDEFAULTROOTSOURCEDIRECTORYo)));

                { const char* temp002 = referencesystem->nativeRootDirectory;

                  { const char* rootnativedefault = translateLogicalPathname(((temp002 != NULL) ? temp002 : concatenateFileNames(systemrootdir, 1, relativeUnlogicalizePathname(oDEFAULTROOTNATIVEDIRECTORYo))));

                    { const char* temp003 = referencesystem->binaryRootDirectory;

                      { const char* rootbinarydefault = translateLogicalPathname(((temp003 != NULL) ? temp003 : concatenateFileNames(systemrootdir, 1, relativeUnlogicalizePathname(oDEFAULTROOTBINARYDIRECTORYo))));

                        { 
                          BIND_STELLA_SPECIAL(oDEFAULTROOTSOURCEDIRECTORYo, const char*, rootsourcedefault);
                          BIND_STELLA_SPECIAL(oDEFAULTROOTNATIVEDIRECTORYo, const char*, rootnativedefault);
                          BIND_STELLA_SPECIAL(oDEFAULTROOTBINARYDIRECTORYo, const char*, rootbinarydefault);
                          if (system->sourceRootDirectory == NULL) {
                            system->sourceRootDirectory = rootSourceDirectory();
                          }
                          if (system->nativeRootDirectory == NULL) {
                            system->nativeRootDirectory = rootNativeDirectory();
                          }
                          if (system->binaryRootDirectory == NULL) {
                            system->binaryRootDirectory = rootBinaryDirectory();
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
    if ((system->sourceRootDirectory == NULL) ||
        ((system->nativeRootDirectory == NULL) ||
         (system->binaryRootDirectory == NULL))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Failed to define or compute one or more of " << "`" << system->name << "'" << "'s root directories";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Cons* parseListOfFilePaths(Cons* files) {
  { Cons* strings = NIL;

    { Object* filespec = NULL;
      Cons* iter000 = files;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        filespec = iter000->value;
        strings = cons(wrapString(implodePathname(filespec)), strings);
      }
    }
    return (strings->reverse());
  }
}

SystemDefinition* defineSystem(Object* name, Cons* options) {
  { const char* stringname = NULL;

    { Surrogate* testValue000 = safePrimaryType(name);

      if (subtypeOfStringP(testValue000)) {
        { Object* name000 = name;
          StringWrapper* name = ((StringWrapper*)(name000));

          stringname = name->wrapperValue;
        }
      }
      else if (subtypeOfSymbolP(testValue000)) {
        { Object* name001 = name;
          Symbol* name = ((Symbol*)(name001));

          stringname = stringDowncase(name->symbolName);
        }
      }
      else {
        std::cout << "Illegal system name: " << name;
        return (NULL);
      }
    }
    { SystemDefinition* self000 = newSystemDefinition();

      self000->name = stringname;
      self000->definitionFile = oCURRENTLOADFILEo;
      { SystemDefinition* system = self000;

        { PropertyList* self001 = newPropertyList();

          self001->thePlist = options;
          { PropertyList* plist = self001;

            { SystemDefinition* value000 = NULL;

              { SystemDefinition* s = NULL;
                Cons* iter000 = oSYSTEMDEFINITIONSo->theConsList;

                for (; !(iter000 == NIL); iter000 = iter000->rest) {
                  s = ((SystemDefinition*)(iter000->value));
                  if (stringEqlP(s->name, stringname)) {
                    value000 = s;
                    break;
                  }
                }
              }
              { SystemDefinition* oldsystem = value000;

                { Object* key = NULL;
                  Object* value = NULL;
                  Cons* iter001 = plist->thePlist;

                  for  (; !(iter001 == NIL); 
                        iter001 = iter001->rest->rest) {
                    key = iter001->value;
                    value = iter001->rest->value;
                    { GeneralizedSymbol* testValue001 = ((GeneralizedSymbol*)(key));

                      if (testValue001 == KWD_SYSTEMS_DIRECTORY) {
                        system->directory = implodePathname(value);
                      }
                      else if (testValue001 == KWD_SYSTEMS_FILES) {
                        system->files = parseListOfFilePaths(((Cons*)(value)));
                      }
                      else if (testValue001 == KWD_SYSTEMS_REQUIRED_SYSTEMS) {
                        system->requiredSystems = ((Cons*)(value));
                        { Object* sys = NULL;
                          Cons* iter002 = ((Cons*)(value));

                          for (; !(iter002 == NIL); iter002 = iter002->rest) {
                            sys = iter002->value;
                            getSystemDefinition(((StringWrapper*)(sys))->wrapperValue, true);
                            if (!systemLoadedOrStartedUpP(((StringWrapper*)(sys))->wrapperValue)) {
                              { PropertyList* currentoptions = ((((boolean)(oCURRENT_SYSTEM_ACTIONo)) ? oCURRENT_SYSTEM_ACTIONo : newPropertyList()))->copy();
                                Object* currentaction = currentoptions->lookupWithDefault(KWD_SYSTEMS_ACTION, KWD_SYSTEMS_LOAD_SYSTEM);
                                Object* currentlanguage = currentoptions->lookupWithDefault(KWD_SYSTEMS_LANGUAGE, runningInLanguage());

                                currentoptions->insertAt(KWD_SYSTEMS_ACTION, currentaction);
                                currentoptions->insertAt(KWD_SYSTEMS_LANGUAGE, currentlanguage);
                                if (((GeneralizedSymbol*)(currentaction)) == KWD_SYSTEMS_MAKE_SYSTEM) {
                                  std::cout << "Making required system " << "`" << unwrapString(((StringWrapper*)(sys))) << "'" << std::endl;
                                  makeSystem(((StringWrapper*)(sys))->wrapperValue, consList(2, KWD_SYSTEMS_OPTIONS, currentoptions));
                                }
                                else {
                                  std::cout << "Loading required system " << "`" << unwrapString(((StringWrapper*)(sys))) << "'" << std::endl;
                                  loadSystem(((StringWrapper*)(sys))->wrapperValue, consList(2, KWD_SYSTEMS_OPTIONS, currentoptions));
                                }
                              }
                            }
                          }
                        }
                      }
                      else if (testValue001 == KWD_SYSTEMS_LISP_ONLY_FILES) {
                        system->lispOnlyFiles = parseListOfFilePaths(((Cons*)(value)));
                      }
                      else if (testValue001 == KWD_SYSTEMS_CPP_ONLY_FILES) {
                        system->cppOnlyFiles = parseListOfFilePaths(((Cons*)(value)));
                      }
                      else if (testValue001 == KWD_SYSTEMS_JAVA_ONLY_FILES) {
                        system->javaOnlyFiles = parseListOfFilePaths(((Cons*)(value)));
                      }
                      else if (testValue001 == KWD_SYSTEMS_DATA_FILES) {
                        system->dataFiles = parseListOfFilePaths(((Cons*)(value)));
                      }
                      else if (testValue001 == KWD_SYSTEMS_PREPROCESSED_FILES) {
                        system->preprocessedFiles = parseListOfFilePaths(((Cons*)(value)));
                      }
                      else if (testValue001 == KWD_SYSTEMS_CARDINAL_MODULE) {
                        system->cardinalModule = ((StringWrapper*)(value))->wrapperValue;
                      }
                      else if (testValue001 == KWD_SYSTEMS_ROOT_SOURCE_DIRECTORY) {
                        system->sourceRootDirectory = ((StringWrapper*)(value))->wrapperValue;
                      }
                      else if (testValue001 == KWD_SYSTEMS_ROOT_NATIVE_DIRECTORY) {
                        system->nativeRootDirectory = ((StringWrapper*)(value))->wrapperValue;
                      }
                      else if (testValue001 == KWD_SYSTEMS_ROOT_BINARY_DIRECTORY) {
                        system->binaryRootDirectory = ((StringWrapper*)(value))->wrapperValue;
                      }
                      else if ((testValue001 == KWD_SYSTEMS_BANNER) ||
                          (testValue001 == KWD_SYSTEMS_COPYRIGHT_HEADER)) {
                        system->banner = ((StringWrapper*)(value))->wrapperValue;
                      }
                      else if (testValue001 == KWD_SYSTEMS_PRODUCTION_SETTINGS) {
                        system->productionSettings = ((Cons*)(value));
                      }
                      else if (testValue001 == KWD_SYSTEMS_DEVELOPMENT_SETTINGS) {
                        system->developmentSettings = ((Cons*)(value));
                      }
                      else if (testValue001 == KWD_SYSTEMS_FINALIZATION_FUNCTION) {
                        system->finalizationFunction = ((Symbol*)(value));
                      }
                      else {
                        if (!(runOptionHandlerP(system, ((Keyword*)(key)), value))) {
                          { 
                            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                            signalTranslationWarning();
                            if (!(suppressWarningsP())) {
                              printErrorContext(">> WARNING: ", STANDARD_WARNING);
                              *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Skipping invalid system option " << "`" << deUglifyParseTree(key) << "'" << " in the definition of system " << "`" << deUglifyParseTree(wrapString(stringname)) << "'" << "." << std::endl;
                            }
                          }
                        }
                      }
                    }
                  }
                }
                if (system->directory == NULL) {
                  system->directory = system->name;
                }
                computeSystemRootDirectories(system);
                oSYSTEMDEFINITIONSo->push(system);
                if (((boolean)(oldsystem))) {
                  std::cout << "Redefining system " << "`" << system->name << "'" << std::endl << std::endl;
                  oSYSTEMDEFINITIONSo->remove(oldsystem);
                }
                return (system);
              }
            }
          }
        }
      }
    }
  }
}

SystemDefinition* defsystem(Symbol* name, Cons* options) {
  // Define a system of files that collectively define
  // a Stella application.
  //    Required options are:
  //    :directory -- the relative path from the respective source/native/binary root directory
  //                  to the directory containing the system files.  Can be a string or a list
  //                  of strings (do not include directory separators).
  //    :files -- a list of files in the system, containing strings and lists
  //              of strings; the latter defines exploded paths to files
  //              in subdirectories.
  //    Optional options are:
  //    :data-files       -- a list of files like the :files keyword, which contain
  //                         data or other content that should not be processed, but
  //                         instead copied verbatim to the native directory
  //    :required-systems -- a list of systems (strings) that should be loaded
  //                         prior to loading this system.
  //    :cardinal-module -- the name (a string) of the principal module for this
  //                        system.
  //    :copyright-header -- string with a header for inclusion into all translated
  //                         files produced by Stella.
  //    :lisp-only-files  -- Like the :files keyword, but these are only included
  //    :cpp-only-files      in the translation for the specific language, namely
  //    :java-only-files     Common Lisp, C++ or Java
  return (defineSystem(name, options));
}

SystemDefinition* defsystemEvaluatorWrapper(Cons* arguments) {
  return (defsystem(((Symbol*)(arguments->value)), arguments->rest));
}

SystemDefinition* getSystemDefinition(const char* name, boolean errorP) {
  // Return a system named 'name'.  If no such system is currently defined,
  // look for a system definition file for `name' in standard locations and try to load it.
  // If no matching system could be found or loaded and `error?' is true, raise an error,
  // otherwise, simply return NULL.
  { SystemDefinition* value000 = NULL;

    { SystemDefinition* s = NULL;
      Cons* iter000 = oSYSTEMDEFINITIONSo->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        s = ((SystemDefinition*)(iter000->value));
        if (stringEqualP(s->name, name)) {
          value000 = s;
          break;
        }
      }
    }
    { SystemDefinition* system = value000;

      if (!((boolean)(system))) {
        { const char* systemfile = findSystemDefinitionFile(name);

          if (systemfile == NULL) {
            if (errorP) {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "Cannot define system " << "`" << name << "'" << " since its system definition file cannot be found";
                throw *newStellaException(stream000->theStringReader());
              }
            }
            return (NULL);
          }
          loadFile(systemfile);
          { SystemDefinition* value001 = NULL;

            { SystemDefinition* s = NULL;
              Cons* iter001 = oSYSTEMDEFINITIONSo->theConsList;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                s = ((SystemDefinition*)(iter001->value));
                if (stringEqualP(s->name, name)) {
                  value001 = s;
                  break;
                }
              }
            }
            system = value001;
          }
          if ((!((boolean)(system))) &&
              errorP) {
            { OutputStringStream* stream001 = newOutputStringStream();

              *(stream001->nativeStream) << "Cannot find a system definition for system " << "`" << name << "'" << " within file " << "`" << systemfile << "'";
              throw *newStellaException(stream001->theStringReader());
            }
          }
        }
      }
      return (system);
    }
  }
}

Module* getCardinalModule(SystemDefinition* system) {
  { const char* name = system->cardinalModule;
    Module* module = NULL;

    if (name != NULL) {
      module = getStellaModule(name, false);
      if (!((boolean)(module))) {
        module = getStellaModule(stringUpcase(name), false);
      }
    }
    if (!((boolean)(module))) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "No cardinal module defined for system: " << "`" << system << "'" << std::endl << std::endl;
    }
    return (module);
  }
}

void helpGetSystemFiles(const char* filename, List* collection, boolean probefileP) {
  if ((!probefileP) ||
      probeFileP(filename)) {
    collection->push(wrapString(filename));
  }
}

List* getSystemFiles(SystemDefinition* system, Keyword* type, boolean probefilesP) {
  { List* files = newList();
    const char* filename = NULL;

    { 
      BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONo, SystemDefinition*, getSystemDefinition(system->name, true));
      BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo, const char*, oCURRENTSYSTEMDEFINITIONo->directory);
      {
        { StringWrapper* f = NULL;
          Cons* iter000 = oCURRENTSYSTEMDEFINITIONo->files;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            f = ((StringWrapper*)(iter000->value));
            if (type == KWD_SYSTEMS_JAVA) {
              filename = javaTranslateClassNamestring(wrapString(stringConcatenate("_STARTUP-", stringUpcase(f->wrapperValue), 0)))->wrapperValue;
            }
            else {
              filename = makeFileNameFromRelativePath(f, type);
            }
            helpGetSystemFiles(filename, files, probefilesP);
          }
        }
        if (type == KWD_SYSTEMS_JAVA) {
          if (!((boolean)(getCardinalModule(oCURRENTSYSTEMDEFINITIONo)))) {
            std::cout << "No cardinal module defined for system " << "`" << system->name << "'" << std::endl << std::endl;
            return (NIL_LIST);
          }
          { Class* clasS = NULL;
            Iterator* iter001 = allClasses(getCardinalModule(oCURRENTSYSTEMDEFINITIONo), true);

            for (; iter001->nextP(); ) {
              clasS = ((Class*)(iter001->value));
              filename = clasS->javaMakeCodeOutputFileName(false);
              helpGetSystemFiles(filename, files, probefilesP);
            }
          }
          filename = stringJavaMakeCodeOutputFileName(javaYieldFlotsamClassName(getCardinalModule(oCURRENTSYSTEMDEFINITIONo)), false);
          helpGetSystemFiles(filename, files, probefilesP);
        }
        else {
        }
      }
    }
    return (files);
  }
}

void cleanSystem(const char* systemname) {
  { SystemDefinition* system = getSystemDefinition(systemname, true);

    { StringWrapper* f = NULL;
      Cons* iter000 = getSystemFiles(system, KWD_SYSTEMS_LISP, true)->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        f = ((StringWrapper*)(iter000->value));
        deleteFile(f->wrapperValue);
      }
    }
    { StringWrapper* f = NULL;
      Cons* iter001 = getSystemFiles(system, KWD_SYSTEMS_JAVA, true)->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        f = ((StringWrapper*)(iter001->value));
        deleteFile(f->wrapperValue);
      }
    }
    { StringWrapper* f = NULL;
      Cons* iter002 = getSystemFiles(system, KWD_SYSTEMS_CPP, true)->theConsList;

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        f = ((StringWrapper*)(iter002->value));
        deleteFile(f->wrapperValue);
      }
    }
    { StringWrapper* f = NULL;
      Cons* iter003 = getSystemFiles(system, KWD_SYSTEMS_LISP_BINARY, true)->theConsList;

      for (; !(iter003 == NIL); iter003 = iter003->rest) {
        f = ((StringWrapper*)(iter003->value));
        deleteFile(f->wrapperValue);
      }
    }
  }
}

void computeOptimizationLevels(SystemDefinition* system, boolean productionmodeP) {
  { Cons* settings = NULL;

    if (productionmodeP) {
      settings = system->productionSettings;
    }
    else {
      settings = system->developmentSettings;
    }
    if (!((boolean)(settings))) {
      settings = getQuotedTree("((3 2 3 3) \"/STELLA\")", "/STELLA");
    }
    setOptimizationLevels(((IntegerWrapper*)(settings->nth(0)))->wrapperValue, ((IntegerWrapper*)(settings->nth(1)))->wrapperValue, ((IntegerWrapper*)(settings->nth(2)))->wrapperValue, ((IntegerWrapper*)(settings->nth(3)))->wrapperValue);
  }
}

// Holds the action and options of the current system action
// such as :make-system, :load-system or :translate-system.  This is used to
// perform the appropriate actions on required systems in `define-system'.
DEFINE_STELLA_SPECIAL(oCURRENT_SYSTEM_ACTIONo, PropertyList* , NULL);

boolean makeSystem(const char* systemname, Cons* languageAoptions) {
  // Translate all out-of-date files of system `systemName'
  // into `language' (the first optional argument of `language&options') and
  // then compile and load them (the latter is only possible for Lisp right now).
  // The following keyword/value `options' are recognized:
  // 
  // `:language': can be used as an alternative to the optional language argument.
  // If not specified, the language of the running implementation is assumed.
  // 
  // `:two-pass?': if true, all files will be scanned twice, once to
  // load the signatures of objects defined in them, and once to actually
  // translate the definitions.  Otherwise, the translator will make one pass in
  // the case that the system is already loaded (and is being remade), and two
  // passes otherwise.
  // 
  // `:development-settings?' (default false): if true translation will favor
  // safe, readable and debuggable code over efficiency (according to the value
  // of `:development-settings' on the system definition).  If false, efficiency
  // will be favored instead (according to the value of `:production-settings'
  // on the system definition).
  // 
  // `:production-settings?' (default true): inverse to `:development-settings?'.
  // 
  // `:force-translation?' (default false): if true, files will be translated
  // whether or not their translations are up-to-date.
  // 
  // `:force-recompilation?' (default false): if true, translated files will be
  // recompiled whether or not their compilations are up-to-date (only supported
  // in Lisp right now).
  // 
  // `:load-system?' (default true): if true, compiled files will be loaded into
  // the current STELLA image (only supported in Lisp and Java right now).
  // 
  // `:startup?' (default true): if true, the system startup function will
  // be called once all files have been loaded.
  // 
  // `:recursive?' (default false): if true, perform `make-system' with the provided
  // options on `systemName' as well as all its required systems and so on.  Required
  // systems will be processed first.  Note that even without this option, any required
  // systems that have not yet been loaded or started up will also be processed, since
  // that is assumed when loading `systemName' and supporting modules from a definition file.
  // 
  // `:root-source-directory', `:root-native-directory', `:root-binary-directory': if
  // specified these directories will be used to override the respective paths provided
  // in system definitions or computed as defaults from a system's home location.
  { Cons* options = languageAoptions;

    if (!(getQuotedTree("((:COMMON-LISP :CPP :JAVA) \"/STELLA\")", "/STELLA")->memberP(options->value))) {
      options = cons(runningInLanguage(), options);
    }
    { PropertyList* theoptions = parseOptions(options->rest, listO(29, KWD_SYSTEMS_TWO_PASSp, SGT_SYSTEMS_STELLA_BOOLEAN, KWD_SYSTEMS_DEVELOPMENT_SETTINGSp, SGT_SYSTEMS_STELLA_BOOLEAN, KWD_SYSTEMS_PRODUCTION_SETTINGSp, SGT_SYSTEMS_STELLA_BOOLEAN, KWD_SYSTEMS_FORCE_TRANSLATIONp, SGT_SYSTEMS_STELLA_BOOLEAN, KWD_SYSTEMS_FORCE_RECOMPILATIONp, SGT_SYSTEMS_STELLA_BOOLEAN, KWD_SYSTEMS_LOAD_SYSTEMp, SGT_SYSTEMS_STELLA_BOOLEAN, KWD_SYSTEMS_STARTUPp, SGT_SYSTEMS_STELLA_BOOLEAN, KWD_SYSTEMS_RECURSIVEp, SGT_SYSTEMS_STELLA_BOOLEAN, KWD_SYSTEMS_LANGUAGE, SGT_SYSTEMS_STELLA_KEYWORD, KWD_SYSTEMS_ACTION, SGT_SYSTEMS_STELLA_KEYWORD, KWD_SYSTEMS_ROOT_SOURCE_DIRECTORY, SGT_SYSTEMS_STELLA_FILE_NAME, KWD_SYSTEMS_ROOT_NATIVE_DIRECTORY, SGT_SYSTEMS_STELLA_FILE_NAME, KWD_SYSTEMS_ROOT_BINARY_DIRECTORY, SGT_SYSTEMS_STELLA_FILE_NAME, KWD_SYSTEMS_PROCESSED, SGT_SYSTEMS_STELLA_LIST, NIL), true, false);
      Keyword* language = ((Keyword*)(theoptions->lookupWithDefault(KWD_SYSTEMS_LANGUAGE, options->value)));
      boolean twopassP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_SYSTEMS_TWO_PASSp, ((!systemLoadedOrStartedUpP(systemname)) ? TRUE_WRAPPER : FALSE_WRAPPER)))));
      boolean productionsettingsP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_SYSTEMS_PRODUCTION_SETTINGSp, TRUE_WRAPPER))));
      boolean developmentsettingsP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_SYSTEMS_DEVELOPMENT_SETTINGSp, ((!productionsettingsP) ? TRUE_WRAPPER : FALSE_WRAPPER)))));
      boolean forcetranslationP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_SYSTEMS_FORCE_TRANSLATIONp, FALSE_WRAPPER))));
      boolean forcerecompilationP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_SYSTEMS_FORCE_RECOMPILATIONp, FALSE_WRAPPER))));
      boolean loadsystemP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_SYSTEMS_LOAD_SYSTEMp, ((language == KWD_SYSTEMS_COMMON_LISP) ? TRUE_WRAPPER : FALSE_WRAPPER)))));
      boolean recursiveP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_SYSTEMS_RECURSIVEp, FALSE_WRAPPER))));
      List* processed = ((List*)(theoptions->lookupWithDefault(KWD_SYSTEMS_PROCESSED, list(0))));
      boolean startupsystemP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_SYSTEMS_STARTUPp, ((language == KWD_SYSTEMS_COMMON_LISP) ? TRUE_WRAPPER : FALSE_WRAPPER)))));
      Object* action = theoptions->lookupWithDefault(KWD_SYSTEMS_ACTION, KWD_SYSTEMS_MAKE_SYSTEM);
      boolean updatedsystemP = false;

      theoptions->insertAt(KWD_SYSTEMS_LANGUAGE, language);
      theoptions->insertAt(KWD_SYSTEMS_ACTION, action);
      theoptions->insertAt(KWD_SYSTEMS_PROCESSED, processed);
      { 
        BIND_STELLA_SPECIAL(oCURRENT_SYSTEM_ACTIONo, PropertyList*, theoptions);
        { 
          BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONo, SystemDefinition*, getSystemDefinition(systemname, true));
          BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo, const char*, oCURRENTSYSTEMDEFINITIONo->directory);
          {
            processed->insertNew(wrapString(systemname));
            if (recursiveP &&
                ((boolean)(oCURRENTSYSTEMDEFINITIONo->requiredSystems))) {
              { StringWrapper* reqsys = NULL;
                Cons* iter000 = oCURRENTSYSTEMDEFINITIONo->requiredSystems;

                for (; !(iter000 == NIL); iter000 = iter000->rest) {
                  reqsys = ((StringWrapper*)(iter000->value));
                  if (!processed->memberP(reqsys)) {
                    std::cout << "Making required system " << "`" << unwrapString(reqsys) << "'" << std::endl;
                    makeSystem(reqsys->wrapperValue, consList(2, KWD_SYSTEMS_OPTIONS, theoptions));
                  }
                }
              }
            }
            if (forcerecompilationP ||
                ((!systemLoadedOrStartedUpP(systemname)) &&
                 (forcetranslationP ||
                  systemNeedsTranslationP(systemname, language)))) {
              loadPreprocessedFiles(systemname);
            }
            updatedsystemP = translateSystem(systemname, consList(17, language, KWD_SYSTEMS_TWO_PASSp, (twopassP ? TRUE_WRAPPER : FALSE_WRAPPER), KWD_SYSTEMS_FORCE_TRANSLATIONp, (forcetranslationP ? TRUE_WRAPPER : FALSE_WRAPPER), KWD_SYSTEMS_DEVELOPMENT_SETTINGSp, (developmentsettingsP ? TRUE_WRAPPER : FALSE_WRAPPER), KWD_SYSTEMS_RECURSIVEp, (recursiveP ? TRUE_WRAPPER : FALSE_WRAPPER), KWD_SYSTEMS_PROCESSED, theoptions->lookup(KWD_SYSTEMS_PROCESSED), KWD_SYSTEMS_ROOT_SOURCE_DIRECTORY, theoptions->lookup(KWD_SYSTEMS_ROOT_SOURCE_DIRECTORY), KWD_SYSTEMS_ROOT_NATIVE_DIRECTORY, theoptions->lookup(KWD_SYSTEMS_ROOT_NATIVE_DIRECTORY), KWD_SYSTEMS_ROOT_BINARY_DIRECTORY, theoptions->lookup(KWD_SYSTEMS_ROOT_BINARY_DIRECTORY)));
            if (loadsystemP &&
                loadSystem(systemname, consList(15, language, KWD_SYSTEMS_FORCE_RECOMPILATIONp, (forcerecompilationP ? TRUE_WRAPPER : FALSE_WRAPPER), KWD_SYSTEMS_STARTUPp, (startupsystemP ? TRUE_WRAPPER : FALSE_WRAPPER), KWD_SYSTEMS_RECURSIVEp, (recursiveP ? TRUE_WRAPPER : FALSE_WRAPPER), KWD_SYSTEMS_PROCESSED, theoptions->lookup(KWD_SYSTEMS_PROCESSED), KWD_SYSTEMS_ROOT_SOURCE_DIRECTORY, theoptions->lookup(KWD_SYSTEMS_ROOT_SOURCE_DIRECTORY), KWD_SYSTEMS_ROOT_NATIVE_DIRECTORY, theoptions->lookup(KWD_SYSTEMS_ROOT_NATIVE_DIRECTORY), KWD_SYSTEMS_ROOT_BINARY_DIRECTORY, theoptions->lookup(KWD_SYSTEMS_ROOT_BINARY_DIRECTORY)))) {
              updatedsystemP = true;
            }
          }
        }
      }
      return (updatedsystemP);
    }
  }
}

BooleanWrapper* makeSystemEvaluatorWrapper(Cons* arguments) {
  return ((makeSystem(((StringWrapper*)(arguments->value))->wrapperValue, arguments->rest) ? TRUE_WRAPPER : FALSE_WRAPPER));
}

void runSystemFinalization(SystemDefinition* system) {
  system = system;
  { const char* fnname = NULL;
    MethodSlot* finalizationfn = NULL;

    if (fnname != NULL) {
      finalizationfn = lookupFunctionByName(fnname);
    }
    if (((boolean)(finalizationfn))) {
      ((void  (*) ())finalizationfn->functionCode)();
    }
  }
}

Cons* systemDefinitionSourceFiles(SystemDefinition* system) {
  { Cons* files = copyConsList(system->files);

    if (oTRANSLATOROUTPUTLANGUAGEo == KWD_SYSTEMS_COMMON_LISP) {
      files = files->subtract(system->javaOnlyFiles);
      files = files->subtract(system->cppOnlyFiles);
    }
    else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_SYSTEMS_JAVA) {
      files = files->subtract(system->lispOnlyFiles);
      files = files->subtract(system->cppOnlyFiles);
    }
    else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_SYSTEMS_CPP) {
      files = files->subtract(system->lispOnlyFiles);
      files = files->subtract(system->javaOnlyFiles);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    return (files);
  }
}

Cons* filesPlusSystemStartup(Cons* files) {
  return (files->concatenate(consList(1, wrapString(systemStartupFileName(NULL))), 0));
}

Cons* systemDefinitionNativeFiles(SystemDefinition* system) {
  { Cons* files = copyConsList(system->files);

    if (oTRANSLATOROUTPUTLANGUAGEo == KWD_SYSTEMS_COMMON_LISP) {
      files = files->unioN(system->lispOnlyFiles);
      if (oCURRENT_STELLA_FEATURESo->membP(KWD_SYSTEMS_USE_COMMON_LISP_STRUCTS)) {
        files = cons(wrapString(clYieldStructClassFileName(system->name)), files);
      }
    }
    else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_SYSTEMS_JAVA) {
      files = files->unioN(system->javaOnlyFiles);
    }
    else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_SYSTEMS_CPP) {
      files = files->unioN(system->cppOnlyFiles);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    return (files);
  }
}

boolean systemLoadedP(const char* name) {
  // Return `true' if system `name' has been loaded.
  { boolean testValue000 = false;

    if (stringEqualP(name, "STELLA")) {
      testValue000 = true;
    }
    else {
      { boolean foundP000 = false;

        { SystemDefinition* sys = NULL;
          Cons* iter000 = oSYSTEMDEFINITIONSo->theConsList;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            sys = ((SystemDefinition*)(iter000->value));
            if (stringEqualP(sys->name, name) &&
                sys->loadedP) {
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

boolean systemLoadedOrStartedUpP(const char* name) {
  // Return `true' if system `name' has either been loaded
  // or initialized with its startup function.
  { boolean testValue000 = false;

    if (stringEqualP(name, "STELLA")) {
      testValue000 = true;
    }
    else {
      { boolean foundP000 = false;

        { SystemDefinition* sys = NULL;
          Cons* iter000 = oSYSTEMDEFINITIONSo->theConsList;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            sys = ((SystemDefinition*)(iter000->value));
            if (stringEqualP(sys->name, name) &&
                (sys->loadedP ||
                 systemStartedUpP(sys->name, sys->cardinalModule))) {
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

void clearSystem(const char* name) {
  // Clears out the system definition named `name'.  If
  // `name' is `null', then clear out all system definitions.  This function
  // is useful when changes have been made to the system definition, and one
  // wants to have it reloaded from the standard location in the file system.
  if (name == NULL) {
    oSYSTEMDEFINITIONSo = newList();
  }
  else {
    { SystemDefinition* value000 = NULL;

      { SystemDefinition* s = NULL;
        Cons* iter000 = oSYSTEMDEFINITIONSo->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          s = ((SystemDefinition*)(iter000->value));
          if (stringEqlP(s->name, name)) {
            value000 = s;
            break;
          }
        }
      }
      { SystemDefinition* sys = value000;

        if (((boolean)(sys))) {
          oSYSTEMDEFINITIONSo->remove(sys);
        }
      }
    }
  }
}

void loadPreprocessedFiles(const char* systemname) {
  if ((!runningAsLispP()) ||
      (!((boolean)(getSystemDefinition(systemname, true)->preprocessedFiles)))) {
    return;
  }
  { 
    BIND_STELLA_SPECIAL(oTRANSLATOROUTPUTLANGUAGEo, Keyword*, KWD_SYSTEMS_COMMON_LISP);
    { 
      BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONo, SystemDefinition*, getSystemDefinition(systemname, true));
      BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo, const char*, oCURRENTSYSTEMDEFINITIONo->directory);
      {
        { Cons* preprocessedfiles = NIL;

          { StringWrapper* f = NULL;
            Cons* iter000 = oCURRENTSYSTEMDEFINITIONo->preprocessedFiles;
            Cons* collect000 = NULL;

            for  (; !(iter000 == NIL); 
                  iter000 = iter000->rest) {
              f = ((StringWrapper*)(iter000->value));
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(wrapString(makeFileName(f->wrapperValue, KWD_SYSTEMS_STELLA, true)), NIL);
                  if (preprocessedfiles == NIL) {
                    preprocessedfiles = collect000;
                  }
                  else {
                    addConsToEndOfConsList(preprocessedfiles, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(wrapString(makeFileName(f->wrapperValue, KWD_SYSTEMS_STELLA, true)), NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
          { 
            BIND_STELLA_SPECIAL(oCURRENT_STELLA_FEATURESo, List*, oCURRENT_STELLA_FEATURESo->copy());
            unsetStellaFeature(consList(1, KWD_SYSTEMS_WARN_ABOUT_UNDEFINED_METHODS));
            { Object* f = NULL;
              Cons* iter001 = preprocessedfiles;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                f = iter001->value;
                translateFile(((StringWrapper*)(f))->wrapperValue, oTRANSLATOROUTPUTLANGUAGEo, false);
              }
            }
          }
          compileAndLoadFiles(oCURRENTSYSTEMDEFINITIONo->preprocessedFiles, oTRANSLATOROUTPUTLANGUAGEo, false);
          if (oCURRENT_STELLA_FEATURESo->membP(KWD_SYSTEMS_USE_COMMON_LISP_STRUCTS)) {
            { StringWrapper* f = NULL;
              Cons* iter002 = oCURRENTSYSTEMDEFINITIONo->preprocessedFiles;

              for (; !(iter002 == NIL); iter002 = iter002->rest) {
                f = ((StringWrapper*)(iter002->value));
                deleteFile(makeFileName(f->wrapperValue, KWD_SYSTEMS_LISP, true));
              }
            }
          }
          { Symbol* startupfn = NULL;
            Cons* iter003 = startupNamesFromFiles(oCURRENTSYSTEMDEFINITIONo->preprocessedFiles);

            for (; !(iter003 == NIL); iter003 = iter003->rest) {
              startupfn = ((Symbol*)(iter003->value));
            }
          }
        }
      }
    }
  }
}

boolean loadSystem(const char* systemname, Cons* languageAoptions) {
  // Natively `language'-compile out-of-date translated files of system
  // `systemName' (only supported for Lisp at the moment) and then load them
  // into the running system.  Return true if at least one file was compiled.
  // The following keyword/value `options' are recognized:
  // 
  // `:language': can be used as an alternative to the optional language argument.
  // If not specified, the language of the running implementation is assumed.
  // 
  // `:force-recompilation?' (default false): if true, files will be compiled
  // whether or not their compilations are up-to-date.
  // 
  // `:startup?' (default true): if true, the system startup function will
  // be called once all files have been loaded.
  // 
  // `:recursive?' (default false): if true, perform `load-system' with the provided
  // options on `systemName' as well as all its required systems and so on.  Required
  // systems will be processed first.  Note that even without this option, any required
  // systems that have not yet been loaded or started up will also be processed, since
  // that is assumed when loading `systemName' and supporting modules from a definition file.
  // 
  // `:root-source-directory', `:root-native-directory', `:root-binary-directory': if
  // specified these directories will be used to override the respective paths provided
  // in system definitions or computed as defaults from a system's home location.
  { Cons* options = languageAoptions;

    if (!(getQuotedTree("((:COMMON-LISP :CPP :JAVA) \"/STELLA\")", "/STELLA")->memberP(options->value))) {
      options = cons(runningInLanguage(), options);
    }
    { PropertyList* theoptions = parseOptions(options->rest, listO(19, KWD_SYSTEMS_FORCE_RECOMPILATIONp, SGT_SYSTEMS_STELLA_BOOLEAN, KWD_SYSTEMS_STARTUPp, SGT_SYSTEMS_STELLA_BOOLEAN, KWD_SYSTEMS_RECURSIVEp, SGT_SYSTEMS_STELLA_BOOLEAN, KWD_SYSTEMS_LANGUAGE, SGT_SYSTEMS_STELLA_KEYWORD, KWD_SYSTEMS_ACTION, SGT_SYSTEMS_STELLA_KEYWORD, KWD_SYSTEMS_ROOT_SOURCE_DIRECTORY, SGT_SYSTEMS_STELLA_FILE_NAME, KWD_SYSTEMS_ROOT_NATIVE_DIRECTORY, SGT_SYSTEMS_STELLA_FILE_NAME, KWD_SYSTEMS_ROOT_BINARY_DIRECTORY, SGT_SYSTEMS_STELLA_FILE_NAME, KWD_SYSTEMS_PROCESSED, SGT_SYSTEMS_STELLA_LIST, NIL), true, true);
      Keyword* language = ((Keyword*)(theoptions->lookupWithDefault(KWD_SYSTEMS_LANGUAGE, options->value)));
      boolean forcerecompilationP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_SYSTEMS_FORCE_RECOMPILATIONp, FALSE_WRAPPER))));
      boolean startupsystemP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_SYSTEMS_STARTUPp, TRUE_WRAPPER))));
      boolean recursiveP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_SYSTEMS_RECURSIVEp, FALSE_WRAPPER))));
      List* processed = ((List*)(theoptions->lookupWithDefault(KWD_SYSTEMS_PROCESSED, list(0))));
      Object* action = theoptions->lookupWithDefault(KWD_SYSTEMS_ACTION, KWD_SYSTEMS_LOAD_SYSTEM);
      boolean translatedfileP = false;

      theoptions->insertAt(KWD_SYSTEMS_LANGUAGE, language);
      theoptions->insertAt(KWD_SYSTEMS_ACTION, action);
      theoptions->insertAt(KWD_SYSTEMS_PROCESSED, processed);
      { 
        BIND_STELLA_SPECIAL(oCURRENT_SYSTEM_ACTIONo, PropertyList*, theoptions);
        { 
          BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONo, SystemDefinition*, getSystemDefinition(systemname, true));
          BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo, const char*, oCURRENTSYSTEMDEFINITIONo->directory);
          {
            if (oCURRENTSYSTEMDEFINITIONo->loadedP) {
              std::cout << "Loading system " << "`" << systemname << "'" << " over top of itself" << std::endl;
            }
            processed->insertNew(wrapString(systemname));
            if (recursiveP &&
                ((boolean)(oCURRENTSYSTEMDEFINITIONo->requiredSystems))) {
              { StringWrapper* reqsys = NULL;
                Cons* iter000 = oCURRENTSYSTEMDEFINITIONo->requiredSystems;

                for (; !(iter000 == NIL); iter000 = iter000->rest) {
                  reqsys = ((StringWrapper*)(iter000->value));
                  if (!processed->memberP(reqsys)) {
                    std::cout << "Loading required system " << "`" << unwrapString(reqsys) << "'" << std::endl;
                    loadSystem(reqsys->wrapperValue, consList(2, KWD_SYSTEMS_OPTIONS, theoptions));
                  }
                }
              }
            }
            if (runningAsLispP()) {
              translatedfileP = compileAndLoadFiles(filesPlusSystemStartup(systemDefinitionNativeFiles(oCURRENTSYSTEMDEFINITIONo)), language, forcerecompilationP);
            }
            oCURRENTSYSTEMDEFINITIONo->loadedP = true;
            if (startupsystemP) {
              runSystemStartupFunction(oCURRENTSYSTEMDEFINITIONo);
            }
          }
        }
        return (translatedfileP);
      }
    }
  }
}

BooleanWrapper* loadSystemEvaluatorWrapper(Cons* arguments) {
  return ((loadSystem(((StringWrapper*)(arguments->value))->wrapperValue, arguments->rest) ? TRUE_WRAPPER : FALSE_WRAPPER));
}

boolean compileAndLoadFiles(Cons* files, Keyword* language, boolean forcerecompilationP) {
  if (language == KWD_SYSTEMS_COMMON_LISP) {
    return (clCompileAndLoadFiles(files, true, forcerecompilationP));
  }
  else {
    std::cout << "'compile-and-load-files' NOT IMPLEMENTED FOR " << language << std::endl;
    return (false);
  }
}

void runSystemStartupFunction(SystemDefinition* system) {
  { Symbol* startupfnsymbol = systemStartupFunctionSymbol(system);

    throw *newStellaException("run-system-startup-function: not yet supported in C++");
  }
}

const char* SystemDefinition::systemStartupFunctionName() {
  { SystemDefinition* system = this;

    return (stringSystemStartupFunctionName(system->name));
  }
}

const char* stringSystemStartupFunctionName(const char* systemname) {
  return (stringConcatenate("STARTUP-", stringUpcase(systemname), 1, "-SYSTEM"));
}

Symbol* systemStartupFunctionSymbol(SystemDefinition* system) {
  return (internSymbolInModule(system->systemStartupFunctionName(), getCardinalModule(system), true));
}

Symbol* startupNameFromFile(const char* file) {
  if (!probeFileP(makeFileName(file, KWD_SYSTEMS_STELLA, true))) {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "STELLA source file " << "`" << makeFileName(file, KWD_SYSTEMS_STELLA, true) << "'" << " does not exist";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  { const char* longname = makeFileName(file, KWD_SYSTEMS_STELLA, true);
    Module* savedmodule = oMODULEo;
    boolean seeninmoduleP = false;
    boolean unusedP = false;
    Symbol* startupfnname = NULL;

    { InputFileStream* inputstream = NULL;

      try {
        inputstream = openInputFile(longname, 0);
        { 
          BIND_STELLA_SPECIAL(oTRANSIENTOBJECTSpo, boolean, true);
          { Object* tree = NULL;
            SExpressionIterator* iter000 = sExpressions(inputstream);

            for (; iter000->nextP(); ) {
              tree = iter000->value;
              { 
                BIND_STELLA_SPECIAL(oTRANSIENTOBJECTSpo, boolean, false);
                if (safePrimaryType(tree) == SGT_SYSTEMS_STELLA_CONS) {
                  { Object* tree000 = tree;
                    Cons* tree = ((Cons*)(tree000));

                    unusedP = handleInModuleTree(tree, seeninmoduleP, true, seeninmoduleP);
                    unusedP = unusedP;
                    if (seeninmoduleP) {
                      startupfnname = yieldStartupFunctionName(file);
                      savedmodule->changeModule();
                      return (startupfnname);
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
    *(STANDARD_WARNING->nativeStream) << "Warning: " << "Missing IN-MODULE declaration for file " << "`" << file << "'" << std::endl << std::endl;
  }
  return (NULL);
}

Cons* startupNamesFromFiles(Cons* files) {
  { Cons* names = NIL;

    { StringWrapper* f = NULL;
      Cons* iter000 = files;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        f = ((StringWrapper*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(startupNameFromFile(f->wrapperValue), NIL);
            if (names == NIL) {
              names = collect000;
            }
            else {
              addConsToEndOfConsList(names, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(startupNameFromFile(f->wrapperValue), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (names);
  }
}

const char* systemStartupFileName(SystemDefinition* system) {
  if (!((boolean)(system))) {
    system = oCURRENTSYSTEMDEFINITIONo;
  }
  if (((boolean)(system))) {
    return ("startup-system");
  }
  else {
    return (NULL);
  }
}

boolean systemStartupFileP(const char* file) {
  if (file == NULL) {
    file = oCURRENTFILENAMEo;
  }
  return ((file != NULL) &&
      stringEqlP(fileBaseName(file), systemStartupFileName(NULL)));
}

boolean systemStartedUpP(const char* systemname, const char* systemmodulename) {
  if (!((boolean)(oFUNCTION_LOOKUP_TABLEo))) {
    return (false);
  }
  if (stringEqualP(systemname, "STELLA")) {
    return (((boolean)(oFUNCTION_LOOKUP_TABLEo)));
  }
  if (!((boolean)(getStellaModule(systemmodulename, false)))) {
    return (false);
  }
  { Symbol* startupfunctionsymbol = lookupSymbolInModule(stringSystemStartupFunctionName(systemname), getStellaModule(systemmodulename, false), true);
    MethodSlot* startupfunction = (((boolean)(startupfunctionsymbol)) ? lookupFunction(startupfunctionsymbol) : ((MethodSlot*)(NULL)));

    return (((boolean)(startupfunction)) &&
        (startupfunction->functionCode != NULL));
  }
}

Cons* yieldStartupRequiredSystems(SystemDefinition* system) {
  { Cons* startupforms = NIL;

    { StringWrapper* systemname = NULL;
      Cons* iter000 = system->requiredSystems;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        systemname = ((StringWrapper*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(listO(4, SYM_SYSTEMS_STELLA_UNLESS, listO(3, SYM_SYSTEMS_STELLA_SYSTEM_STARTED_UPp, systemname, cons(wrapString(getCardinalModule(getSystemDefinition(systemname->wrapperValue, true))->moduleFullName), NIL)), cons(systemStartupFunctionSymbol(getSystemDefinition(systemname->wrapperValue, true)), NIL), NIL), NIL);
            if (startupforms == NIL) {
              startupforms = collect000;
            }
            else {
              addConsToEndOfConsList(startupforms, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(listO(4, SYM_SYSTEMS_STELLA_UNLESS, listO(3, SYM_SYSTEMS_STELLA_SYSTEM_STARTED_UPp, systemname, cons(wrapString(getCardinalModule(getSystemDefinition(systemname->wrapperValue, true))->moduleFullName), NIL)), cons(systemStartupFunctionSymbol(getSystemDefinition(systemname->wrapperValue, true)), NIL), NIL), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (listO(3, SYM_SYSTEMS_STELLA_STARTUP_TIME_PROGN, KWD_SYSTEMS_EARLY_INITS, startupforms->concatenate(NIL, 0)));
  }
}

Cons* collectStartupFormsFromSystemFile(SystemDefinition* system) {
  { const char* systemfilename = system->definitionFile;
    Module* module = NULL;
    Cons* startupform = NULL;
    Cons* startupforms = NIL;

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oMODULEo);
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      { InputFileStream* inputstream = NULL;

        try {
          inputstream = openInputFile(systemfilename, 0);
          { Object* tree = NULL;
            SExpressionIterator* iter000 = sExpressions(inputstream);
            Cons* collect000 = NULL;

            for  (; iter000->nextP(); ) {
              tree = iter000->value;
              startupform = NULL;
              if (safePrimaryType(tree) == SGT_SYSTEMS_STELLA_CONS) {
                { Object* tree000 = tree;
                  Cons* tree = ((Cons*)(tree000));

                  if (tree->value == SYM_SYSTEMS_STELLA_DEFMODULE) {
                    evaluate(tree);
                    module = getStellaModule(coerceToModuleName(tree->rest->value, true), true);
                    if (((boolean)(module))) {
                      startupform = listO(4, SYM_SYSTEMS_STELLA_STARTUP_TIME_PROGN, KWD_SYSTEMS_MODULES, yieldDefineModule(module), NIL);
                    }
                  }
                  if (tree->value == SYM_SYSTEMS_STELLA_IN_MODULE) {
                    evaluate(tree);
                  }
                }
              }
              else {
              }
              if (!((boolean)(startupform))) {
                continue;
              }
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(startupform, NIL);
                  if (startupforms == NIL) {
                    startupforms = collect000;
                  }
                  else {
                    addConsToEndOfConsList(startupforms, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(startupform, NIL);
                  collect000 = collect000->rest;
                }
              }
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
      return (startupforms);
    }
  }
}

Cons* collectDefinedModulesFromSystemFile(SystemDefinition* system) {
  { Cons* startupforms = collectStartupFormsFromSystemFile(system);
    Module* module = NULL;
    Cons* modules = NIL;

    { Cons* form = NULL;
      Cons* iter000 = startupforms;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        form = ((Cons*)(iter000->value));
        if (form->rest->value == KWD_SYSTEMS_MODULES) {
          { Object* def = NULL;
            Cons* iter001 = form->rest->rest;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              def = iter001->value;
              if (consP(def) &&
                  (((Cons*)(def))->value == SYM_SYSTEMS_STELLA_DEFINE_MODULE_FROM_STRINGIFIED_SOURCE)) {
                module = getStellaModule(((StringWrapper*)(((Cons*)(def))->rest->value))->wrapperValue, false);
                if (((boolean)(module))) {
                  modules = cons(module, modules);
                }
              }
            }
          }
        }
      }
    }
    return (modules->reverse());
  }
}

void createSystemStartupFile(SystemDefinition* system) {
  if (!((boolean)(oCURRENTSYSTEMDEFINITIONo))) {
    std::cout << "Must be within a system environment to create startup file " << std::endl << "   for system " << "`" << system->name << "'" << "." << std::endl << std::endl;
    return;
  }
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getCardinalModule(system));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    { const char* file = makeFileName(systemStartupFileName(system), KWD_SYSTEMS_STELLA, true);
      Cons* startupfnnames = NIL;
      Cons* startupforms = NIL;

      { OutputFileStream* outputstream = NULL;

        try {
          outputstream = openOutputFile(file, 0);
          { StringWrapper* f = NULL;
            Cons* iter000 = systemDefinitionSourceFiles(system);
            Cons* collect000 = NULL;

            for  (; !(iter000 == NIL); 
                  iter000 = iter000->rest) {
              f = ((StringWrapper*)(iter000->value));
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(startupNameFromFile(f->wrapperValue), NIL);
                  if (startupfnnames == NIL) {
                    startupfnnames = collect000;
                  }
                  else {
                    addConsToEndOfConsList(startupfnnames, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(startupNameFromFile(f->wrapperValue), NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
          clOutputFileHeader(outputstream, file, false);
          startupforms = cons(listO(3, SYM_SYSTEMS_STELLA_IN_MODULE, wrapString(getCardinalModule(system)->moduleFullName), NIL), startupforms);
          startupforms = cons(listO(3, SYM_SYSTEMS_STELLA_DEFUN, systemStartupFunctionSymbol(system), listO(4, NIL, KWD_SYSTEMS_PUBLICp, SYM_SYSTEMS_STELLA_TRUE, NIL)), startupforms);
          if (stringEqualP(system->name, "STELLA")) {
            startupforms = cons(listO(4, SYM_SYSTEMS_STELLA_STARTUP_TIME_PROGN, KWD_SYSTEMS_EARLY_INITS, listO(4, SYM_SYSTEMS_STELLA_UNLESS, listO(4, SYM_SYSTEMS_STELLA_SYSTEM_STARTED_UPp, wrapString("stella"), wrapString("/STELLA"), NIL), listO(3, SYM_SYSTEMS_STELLA_STARTUP, SYM_SYSTEMS_STELLA_FALSE, NIL), NIL), NIL), startupforms);
          }
          else {
            if (((boolean)(system->requiredSystems))) {
              startupforms = cons(yieldStartupRequiredSystems(system), startupforms);
            }
            { Cons* form = NULL;
              Cons* iter001 = collectStartupFormsFromSystemFile(system);

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                form = ((Cons*)(iter001->value));
                startupforms = cons(form, startupforms);
              }
            }
            { Symbol* startupfn = NULL;
              Cons* iter002 = startupfnnames;

              for (; !(iter002 == NIL); iter002 = iter002->rest) {
                startupfn = ((Symbol*)(iter002->value));
                if (!((boolean)(lookupFunction(startupfn)))) {
                  { 
                    BIND_STELLA_SPECIAL(oMODULEo, Module*, startupfn->homeModule());
                    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
                    defineMethodFromParseTree(listO(3, SYM_SYSTEMS_STELLA_DEFUN, startupfn, listO(4, NIL, KWD_SYSTEMS_PUBLICp, SYM_SYSTEMS_STELLA_TRUE, NIL)));
                  }
                }
              }
            }
            { Cons* startupfncalls = NIL;

              { Symbol* startupfn = NULL;
                Cons* iter003 = startupfnnames;
                Cons* collect001 = NULL;

                for  (; !(iter003 == NIL); 
                      iter003 = iter003->rest) {
                  startupfn = ((Symbol*)(iter003->value));
                  if (!((boolean)(collect001))) {
                    {
                      collect001 = cons(cons(startupfn, NIL), NIL);
                      if (startupfncalls == NIL) {
                        startupfncalls = collect001;
                      }
                      else {
                        addConsToEndOfConsList(startupfncalls, collect001);
                      }
                    }
                  }
                  else {
                    {
                      collect001->rest = cons(cons(startupfn, NIL), NIL);
                      collect001 = collect001->rest;
                    }
                  }
                }
              }
              startupforms = cons(listO(4, SYM_SYSTEMS_STELLA_STARTUP_TIME_PROGN, listO(7, SYM_SYSTEMS_STELLA_FOREACH, SYM_SYSTEMS_STELLA_PHASE, SYM_SYSTEMS_STELLA_IN, listO(4, SYM_SYSTEMS_STELLA_INTERVAL, listO(3, SYM_SYSTEMS_STELLA_PHASE_TO_INTEGER, KWD_SYSTEMS_EARLY_INITS, NIL), listO(3, SYM_SYSTEMS_STELLA_PHASE_TO_INTEGER, KWD_SYSTEMS_FINAL, NIL), NIL), SYM_SYSTEMS_STELLA_DO, listO(4, SYM_SYSTEMS_STELLA_SETQ, SYM_SYSTEMS_STELLA_oSTARTUP_TIME_PHASEo, SYM_SYSTEMS_STELLA_PHASE, NIL), startupfncalls->concatenate(NIL, 0)), listO(4, SYM_SYSTEMS_STELLA_SETQ, SYM_SYSTEMS_STELLA_oSTARTUP_TIME_PHASEo, wrapInteger(999), NIL), NIL), startupforms);
            }
          }
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            BIND_STELLA_SPECIAL(oPRINTPRETTYpo, boolean, true);
            { Cons* form = NULL;
              Cons* iter004 = startupforms->reverse();

              for (; !(iter004 == NIL); iter004 = iter004->rest) {
                form = ((Cons*)(iter004->value));
                *(outputstream->nativeStream) << form << std::endl << std::endl;
              }
            }
          }
        }
catch (...) {
          if (((boolean)(outputstream))) {
            outputstream->free();
          }
          throw;
        }
        if (((boolean)(outputstream))) {
          outputstream->free();
        }
      }
    }
  }
}

List* helpAllRequiredSystems(const char* systemName, List* found) {
  { SystemDefinition* system = getSystemDefinition(systemName, true);

    { Cons* requiredSystemNames = system->requiredSystems;

      if (((boolean)(requiredSystemNames))) {
        { StringWrapper* sys = NULL;
          Cons* iter000 = requiredSystemNames;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            sys = ((StringWrapper*)(iter000->value));
            if (!found->memberP(sys)) {
              helpAllRequiredSystems(sys->wrapperValue, found);
              found->push(sys);
            }
          }
        }
      }
      return (found);
    }
  }
}

Cons* allRequiredSystems(const char* systemName) {
  // Returns a CONS of all of the systems required by `system-name'
  return (helpAllRequiredSystems(systemName, newList())->theConsList);
}

const char* dateToVersionString(CalendarDate* date, Keyword* granularity) {
  // Transform `date' into a version string according to `granularity'
  // which is at least :days and defaults to :seconds.
  { const char* formatstring = "%Y.%m.%d.%H%M%S";

    if (granularity == KWD_SYSTEMS_DAYS) {
      formatstring = "%Y.%m.%d";
    }
    else if (granularity == KWD_SYSTEMS_HOURS) {
      formatstring = "%Y.%m.%d.%H";
    }
    else if (granularity == KWD_SYSTEMS_MINUTES) {
      formatstring = "%Y.%m.%d.%H%M";
    }
    else if (granularity == KWD_SYSTEMS_SECONDS) {
      formatstring = "%Y.%m.%d.%H%M%S";
    }
    else {
    }
    return (formatDate(date, NULL, formatstring));
  }
}

CalendarDate* getSystemLastModifiedDate(SystemDefinition* system) {
  // Compute a last-modified date for `system' based on its most recently modified source file.
  { CalendarDate* date = NULL;

    { 
      BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONo, SystemDefinition*, getSystemDefinition(system->name, true));
      BIND_STELLA_SPECIAL(oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo, const char*, oCURRENTSYSTEMDEFINITIONo->directory);
      {
        { StringWrapper* file = NULL;
          Cons* iter000 = systemDefinitionSourceFiles(system);

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            file = ((StringWrapper*)(iter000->value));
            file = wrapString(makeFileName(file->wrapperValue, KWD_SYSTEMS_STELLA, true));
            if (probeFileP(file->wrapperValue)) {
              if ((!((boolean)(date))) ||
                  fileWriteDate(file->wrapperValue)->greaterP(date)) {
                date = fileWriteDate(file->wrapperValue);
              }
            }
          }
        }
        return (date);
      }
    }
  }
}

const char* getSystemVersionString(SystemDefinition* system) {
  // Compute a version string for `system' which is either based on an explicit :version
  // annotation on `system's definition, the readable value of an existing `*<system>-version[-string]*',
  // variable or on its most recent modification date of any of its source files.
  { const char* name = system->name;
    Module* module = getStellaModule(system->cardinalModule, false);
    const char* versionsymbolname = NULL;
    Symbol* versionsymbol = NULL;
    GlobalVariable* versionvariable = NULL;
    const char* versionstring = ((StringWrapper*)(dynamicSlotValue(system->dynamicSlots, SYM_SYSTEMS_STELLA_SYSTEM_VERSION, NULL_STRING_WRAPPER)))->wrapperValue;

    if ((versionstring == NULL) &&
        ((boolean)(module))) {
      { Object* pattern = NULL;
        Cons* iter000 = consList(2, wrapString("*<name>-version*"), wrapString("*<name>-version-string*"));

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          pattern = iter000->value;
          versionsymbolname = replaceSubstrings(((StringWrapper*)(pattern))->wrapperValue, name, "<name>");
          if (!(module->caseSensitiveP)) {
            versionsymbolname = stringUpcase(versionsymbolname);
          }
          versionsymbol = lookupSymbolInModule(versionsymbolname, module, false);
          if (((boolean)(versionsymbol))) {
            versionvariable = versionsymbol->lookupGlobalVariable();
            if (((boolean)(versionvariable)) &&
                ((versionvariable->type() == SGT_SYSTEMS_STELLA_STRING) &&
                 ((boolean)(readGlobalVariableValue(versionvariable))))) {
              versionstring = ((StringWrapper*)(readGlobalVariableValue(versionvariable)))->wrapperValue;
              if (versionstring != NULL) {
                break;
              }
            }
          }
        }
      }
    }
    if (versionstring == NULL) {
      versionstring = dateToVersionString(getSystemLastModifiedDate(system), KWD_SYSTEMS_SECONDS);
    }
    return (((StringWrapper*)(splitString(versionstring, ' ')->last()))->wrapperValue);
  }
}

cpp_function_code autoload(const char* qualifiedname, const char* systemname, Surrogate* cache, boolean errorP) {
  // Autoload function `qualifiedName' from system `systemName'.
  // If it is already present in the system, simply return its code.  If `cache'
  // is defined, return its value if defined, otherwise, set its value to the
  // function found.  If the function failed to be defined by loading `systemName'
  // and `error?' is true, raise an error.  Otherwise, simply return NULL.
  { cpp_function_code function = NULL;

    if (((boolean)(cache))) {
      { FunctionCodeWrapper* functionwrapper = ((FunctionCodeWrapper*)(cache->surrogateValue));

        if (((boolean)(functionwrapper))) {
          return (functionwrapper->wrapperValue);
        }
      }
    }
    try {
      { const char* functionname = NULL;
        const char* functionmodulename = NULL;
        Keyword* type = NULL;

        functionname = parseStellaName(qualifiedname, false, functionmodulename, type);
        type = type;
        { Module* functionmodule = NULL;
          Symbol* functionnamesymbol = NULL;
          MethodSlot* functionobject = NULL;

          if (functionmodulename != NULL) {
            functionmodule = getStellaModule(functionmodulename, errorP &&
                (systemname == NULL));
          }
          if (((boolean)(functionmodule))) {
            functionnamesymbol = lookupSymbolInModule(functionname, functionmodule, false);
          }
          if (((boolean)(functionnamesymbol))) {
            functionobject = lookupFunction(functionnamesymbol);
          }
          if (((boolean)(functionobject))) {
            function = functionobject->functionCode;
          }
          else if ((systemname != NULL) &&
              (!systemLoadedP(systemname))) {
            { 
              BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
              BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
              loadSystem(systemname, NIL);
            }
            return (autoload(qualifiedname, NULL, cache, errorP));
          }
        }
      }
    }
    catch (StellaException& _e) {
      StellaException* e = &_e;

      if (errorP) {
        if (systemname != NULL) {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "autoload: failed to define " << "`" << qualifiedname << "'" << ": " << "`" << exceptionMessage(e) << "'";
            throw *newStellaException(stream000->theStringReader());
          }
        }
        else {
          throw *e;
        }
      }
    }
    if (function == NULL) {
      if (errorP) {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "autoload: failed to define " << "`" << qualifiedname << "'";
          throw *newStellaException(stream001->theStringReader());
        }
      }
      else {
        return (NULL);
      }
    }
    if (((boolean)(cache))) {
      cache->surrogateValue = wrapFunctionCode(function);
    }
    return (function);
  }
}

void makeStella(boolean forcerecompilationP) {
  makeSystem("STELLA", consList(5, KWD_SYSTEMS_COMMON_LISP, KWD_SYSTEMS_FORCE_TRANSLATIONp, (forcerecompilationP ? TRUE_WRAPPER : FALSE_WRAPPER), KWD_SYSTEMS_DEVELOPMENT_SETTINGSp, FALSE_WRAPPER));
}

StringWrapper* parseConfigurationFileLine(const char* line, Wrapper*& _Return1, Keyword*& _Return2) {
  { int start = 0;
    int hashpos = stringPosition(line, '#', 0);
    int equalpos = stringPosition(line, '=', 0);
    int end = equalpos;
    int length = strlen(line);
    const char* property = NULL;
    const char* valuestring = NULL;
    Object* value = NULL;
    Keyword* operatoR = KWD_SYSTEMS_SET;

    { boolean alwaysP000 = true;

      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = (((hashpos != NULL_INTEGER) ? hashpos : length)) - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          if (!(oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (line[i])] == KWD_SYSTEMS_WHITE_SPACE)) {
            alwaysP000 = false;
            break;
          }
        }
      }
      if (alwaysP000) {
        _Return1 = NULL;
        _Return2 = NULL;
        return (NULL);
      }
    }
    if ((equalpos == NULL_INTEGER) ||
        (equalpos == 0)) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Illegal line in configuration file: " << "`" << line << "'" << std::endl;
      _Return1 = NULL;
      _Return2 = NULL;
      return (NULL);
    }
    while (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (line[start])] == KWD_SYSTEMS_WHITE_SPACE) {
      start = start + 1;
    }
    if (line[(end - 1)] == '+') {
      operatoR = KWD_SYSTEMS_ADD;
      end = end - 1;
    }
    while (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (line[(end - 1)])] == KWD_SYSTEMS_WHITE_SPACE) {
      end = end - 1;
    }
    if (end <= start) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Illegal property in configuration file: " << "`" << line << "'" << std::endl;
      _Return1 = NULL;
      _Return2 = NULL;
      return (NULL);
    }
    property = stringSubsequence(line, start, end);
    valuestring = stringSubsequence(line, equalpos + 1, length);
    if (stringEqualP(valuestring, "TRUE")) {
      value = TRUE_WRAPPER;
    }
    else if (stringEqualP(valuestring, "FALSE")) {
      value = FALSE_WRAPPER;
    }
    else {
      try {
        { Surrogate* testValue000 = safePrimaryType(value = readSExpressionFromString(valuestring));

          if (subtypeOfIntegerP(testValue000) ||
              (subtypeOfLongIntegerP(testValue000) ||
               subtypeOfFloatP(testValue000))) {
          }
          else {
            value = wrapString(valuestring);
          }
        }
      }
      catch (ReadException ) {
        value = wrapString(valuestring);
      }
    }
    { StringWrapper* _Return0 = wrapString(property);

      _Return1 = ((Wrapper*)(value));
      _Return2 = operatoR;
      return (_Return0);
    }
  }
}

KeyValueList* oSYSTEM_CONFIGURATION_TABLEo = NULL;

KeyValueList* loadConfigurationFile(const char* file) {
  // Read a configuration `file' and return its content as a configuration table.
  // Also enter each property read into the global system configuration table.
  // Assumes Java-style property file syntax.  Each property name is represented
  // as a wrapped string and each value as a wrapped string/integer/float or boolean.
  { const char* temp000 = findFileInLoadPath(file, NULL);

    file = ((temp000 != NULL) ? temp000 : file);
  }
  ensureFileExists(file, "load-configuration-file");
  { KeyValueList* configuration = newKeyValueList();

    { InputFileStream* in = NULL;

      try {
        in = openInputFile(file, 0);
        { const char* line = NULL;
          LineIterator* iter000 = lines(in);

          for (; iter000->nextP(); ) {
            line = iter000->value;
            { StringWrapper* key = NULL;
              Wrapper* value = NULL;
              Keyword* operatoR = NULL;

              key = parseConfigurationFileLine(line, value, operatoR);
              if (((boolean)(key))) {
                if (operatoR == KWD_SYSTEMS_SET) {
                  setConfigurationProperty(key->wrapperValue, value, configuration);
                  setConfigurationProperty(key->wrapperValue, value, NULL);
                }
                else if (operatoR == KWD_SYSTEMS_ADD) {
                  addConfigurationProperty(key->wrapperValue, value, configuration);
                  addConfigurationProperty(key->wrapperValue, value, NULL);
                }
                else {
                  { OutputStringStream* stream000 = newOutputStringStream();

                    *(stream000->nativeStream) << "`" << operatoR << "'" << " is not a valid case option";
                    throw *newStellaException(stream000->theStringReader());
                  }
                }
              }
            }
          }
        }
      }
catch (...) {
        if (((boolean)(in))) {
          in->free();
        }
        throw;
      }
      if (((boolean)(in))) {
        in->free();
      }
    }
    return (configuration);
  }
}

KeyValueList* loadConfigurationFileEvaluatorWrapper(Cons* arguments) {
  return (loadConfigurationFile(((StringWrapper*)(arguments->value))->wrapperValue));
}

void saveConfigurationValue(OutputStream* stream, Object* value) {
  // Save `value' to `stream' as a properly formatted configuration
  // value.
  { Surrogate* testValue000 = safePrimaryType(value);

    if (subtypeOfStringP(testValue000)) {
      { Object* value000 = value;
        StringWrapper* value = ((StringWrapper*)(value000));

        *(stream->nativeStream) << value->wrapperValue;
      }
    }
    else if (subtypeOfBooleanP(testValue000)) {
      { Object* value001 = value;
        BooleanWrapper* value = ((BooleanWrapper*)(value001));

        if (value == TRUE_WRAPPER) {
          *(stream->nativeStream) << "true";
        }
        else {
          *(stream->nativeStream) << "false";
        }
      }
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { Object* value002 = value;
        IntegerWrapper* value = ((IntegerWrapper*)(value002));

        *(stream->nativeStream) << integerToString(((long long int)(value->wrapperValue)));
      }
    }
    else if (subtypeOfLongIntegerP(testValue000)) {
      { Object* value003 = value;
        LongIntegerWrapper* value = ((LongIntegerWrapper*)(value003));

        *(stream->nativeStream) << integerToString(value->wrapperValue);
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { Object* value004 = value;
        FloatWrapper* value = ((FloatWrapper*)(value004));

        *(stream->nativeStream) << floatToString(value->wrapperValue);
      }
    }
    else {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream->nativeStream) << value;
      }
    }
  }
}

void saveConfigurationFile(KeyValueList* table, const char* file, const char* title) {
  // Save `table' as a configuration file.  Uses a Java-style property file syntax.
  { 
    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, false);
    { OutputFileStream* out = NULL;

      try {
        out = openOutputFile(file, 0);
        if (title != NULL) {
          *(out->nativeStream) << "# " << title << std::endl;
        }
        { StringWrapper* key = NULL;
          Object* value = NULL;
          KvCons* iter000 = table->theKvList;

          for  (; ((boolean)(iter000)); 
                iter000 = iter000->rest) {
            key = ((StringWrapper*)(iter000->key));
            value = iter000->value;
            if (safePrimaryType(value) == SGT_SYSTEMS_STELLA_CONS) {
              { Object* value000 = value;
                Cons* value = ((Cons*)(value000));

                { Object* v = NULL;
                  Cons* iter001 = value;

                  for (; !(iter001 == NIL); iter001 = iter001->rest) {
                    v = iter001->value;
                    *(out->nativeStream) << unwrapString(key) << " +=";
                    saveConfigurationValue(out, v);
                    *(out->nativeStream) << std::endl;
                  }
                }
              }
            }
            else {
              *(out->nativeStream) << unwrapString(key) << " =";
              saveConfigurationValue(out, value);
              *(out->nativeStream) << std::endl;
            }
          }
        }
      }
catch (...) {
        if (((boolean)(out))) {
          out->free();
        }
        throw;
      }
      if (((boolean)(out))) {
        out->free();
      }
    }
  }
}

Object* lookupConfigurationProperty(const char* property, Object* defaultvalue, KeyValueList* configuration) {
  // Lookup `property' in `configuration' and return its value.
  // Use the global system configuration table if `configuration' is NULL.  Return
  // `defaultValue' if `property' is not defined.
  if (!((boolean)(configuration))) {
    configuration = oSYSTEM_CONFIGURATION_TABLEo;
  }
  { Object* value = configuration->lookup(wrapString(property));

    if (((boolean)(value))) {
      return (value);
    }
    else {
      return (defaultvalue);
    }
  }
}

Cons* lookupConfigurationPropertyValues(const char* property, Object* defaultvalue, KeyValueList* configuration) {
  // Lookup `property' in `configuration', assume it is a multi-valued
  // property and return its value(s) as a list.  Use the global system configuration table
  // if `configuration' is NULL.  Return `defaultValue' if `property' is not defined or
  // NIL is no default value is specified.
  if (!((boolean)(configuration))) {
    configuration = oSYSTEM_CONFIGURATION_TABLEo;
  }
  { Object* value = configuration->lookup(wrapString(property));

    if (((boolean)(value))) {
      return (value->consify());
    }
    else if (((boolean)(defaultvalue))) {
      return (defaultvalue->consify());
    }
    else {
      return (NIL);
    }
  }
}

Object* setConfigurationProperty(const char* property, Object* value, KeyValueList* configuration) {
  // Set `property' in `configuration' to `value' and return it.
  // Use the global system configuration table if `configuration' is NULL.
  if (!((boolean)(configuration))) {
    configuration = oSYSTEM_CONFIGURATION_TABLEo;
  }
  configuration->insertAt(wrapString(property), value);
  runConfigurationPropertyDemon(KWD_SYSTEMS_SET, property, value, configuration);
  return (value);
}

Object* addConfigurationProperty(const char* property, Object* value, KeyValueList* configuration) {
  // Add `value' to `property' in `configuration' and return it.
  // If a previous value exists add `value' to the end (listify the old value
  // if it is not yet a list).  Otherwise, create a new list containing `value'.
  // Use the global system configuration table if `configuration' is NULL.
  if (!((boolean)(configuration))) {
    configuration = oSYSTEM_CONFIGURATION_TABLEo;
  }
  { Object* temp000 = configuration->lookup(wrapString(property));

    configuration->insertAt(wrapString(property), ((((boolean)(temp000)) ? temp000 : NIL))->consify()->concatenate(cons(value, NIL), 0));
  }
  runConfigurationPropertyDemon(KWD_SYSTEMS_ADD, property, value, configuration);
  return (value);
}

Object* clearConfigurationProperty(const char* property, KeyValueList* configuration) {
  // Remove `property' in `configuration' and return the previous
  // value.
  // Use the global system configuration table if `configuration' is NULL.
  if (!((boolean)(configuration))) {
    configuration = oSYSTEM_CONFIGURATION_TABLEo;
  }
  { Object* currentValue = configuration->lookup(wrapString(property));

    configuration->removeAt(wrapString(property));
    runConfigurationPropertyDemon(KWD_SYSTEMS_CLEAR, property, currentValue, configuration);
    return (currentValue);
  }
}

Object* removeConfigurationProperty(const char* property, Object* value, KeyValueList* configuration) {
  // Remove `value' from `property' in `configuration' and return it.
  // Use the global system configuration table if `configuration' is NULL.
  if (!((boolean)(configuration))) {
    configuration = oSYSTEM_CONFIGURATION_TABLEo;
  }
  { Cons* currentValue = ((Cons*)(configuration->lookup(wrapString(property))));

    if (((boolean)(currentValue))) {
      configuration->insertAt(wrapString(property), currentValue->remove(value));
    }
    runConfigurationPropertyDemon(KWD_SYSTEMS_REMOVE, property, value, configuration);
    return (value);
  }
}

void printConfigurationProperties(KeyValueList* configuration, OutputStream* stream) {
  // Print all properties defined in `configuration' to `stream'.
  { 
    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
    { Cons* entry = NULL;
      Cons* iter000 = ((Cons*)(configuration->consify()->sortTuples(0, NULL)));

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        entry = ((Cons*)(iter000->value));
        *(stream->nativeStream) << unwrapString(((StringWrapper*)(entry->value))) << " = ";
        if (stringP(entry->rest->value)) {
          *(stream->nativeStream) << unwrapString(((StringWrapper*)(entry->rest->value))) << std::endl;
        }
        else {
          *(stream->nativeStream) << entry->rest->value << std::endl;
        }
      }
    }
  }
}

// The :root-directory portion of the PL logical host.  This variable
// is primarily defined to allow us to dynamically change this via a configuration demon.
const char* oPL_ROOT_DIRECTORYo = NULL;

const char* OPlRootDirectoryOSetter(const char* value) {
  oPL_ROOT_DIRECTORYo = value;
  defineLogicalHostProperty("PL", KWD_SYSTEMS_ROOT_DIRECTORY, wrapString(value));
  return (value);
}

void configureStella(const char* file) {
  // Perform STELLA run-time configuration.  If supplied, load the
  // configuration file `file' first which should be supplied with a physical pathname.
  if ((file != NULL) &&
      (findFileInLoadPath(file, NULL) != NULL)) {
    loadConfigurationFile(file);
  }
  defineLogicalHostProperty("PL", KWD_SYSTEMS_ROOT_DIRECTORY, ((oPL_ROOT_DIRECTORYo != NULL) ? wrapString(oPL_ROOT_DIRECTORYo) : lookupConfigurationProperty("PowerLoomRootDirectory", NULL, NULL)));
}

void configureStellaEvaluatorWrapper(Cons* arguments) {
  configureStella(((StringWrapper*)(arguments->value))->wrapperValue);
}

Object* getProperty(Object* property, Cons* defaultvalue) {
  // Lookup `property' (a string or symbol) in the configuration
  // table and return its value.  If it is undefined, return the optional `defaultValue'.
  // Note that `property' is evaluated and will need to be quoted if supplied as a
  // symbol.  Symbols will also be upcased if this command is run in a non-case-
  // sensitive module.
  { const char* key = coerceToString(property);
    Object* defaulT = defaultvalue->value;

    return (lookupConfigurationProperty(key, defaulT, oSYSTEM_CONFIGURATION_TABLEo));
  }
}

Object* getPropertyEvaluatorWrapper(Cons* arguments) {
  return (getProperty(arguments->value, arguments->rest));
}

void setProperty(Object* property, Object* value) {
  // Set `property' (a string or symbol) in the configuration
  // table to `value'.  Note that `property' is evaluated and will need to be quoted
  // if supplied as a symbol.  Symbols will also be upcased if this command is run in
  // a non-case-sensitive module.
  { const char* key = coerceToString(property);

    setConfigurationProperty(key, value, oSYSTEM_CONFIGURATION_TABLEo);
  }
}

void addPropertyValue(Object* property, Object* value) {
  // Add `value' to the end of `property's (a string or symbol) value
  // list in the configuration table.  Coerces the current value to a list or initializes
  // the list if it is as yet undefined.  Allows incremental addition of values to
  // list-valued propertys.  Note that `property' is evaluated and will need to be quoted
  // if supplied as a symbol.  Symbols will also be upcased if this command is run in a
  // non-case-sensitive module.
  { const char* key = coerceToString(property);

    addConfigurationProperty(key, value, oSYSTEM_CONFIGURATION_TABLEo);
  }
}

void printProperties() {
  // Print all current configuration property information to
  // standard output.
  std::cout << "------------------------------------------------------------" << std::endl << "# Loaded System Configuration" << std::endl;
  printConfigurationProperties(oSYSTEM_CONFIGURATION_TABLEo, STANDARD_OUTPUT);
  std::cout << "------------------------------------------------------------" << std::endl;
}

KeyValueMap* oREGISTERED_PROPERTY_DEMONSo = NULL;

void registerPropertyDemon(const char* property, Symbol* demonname) {
  // Register the function named `demonName' as the demon for `property'.
  // Demons will be run as after demons on every configuration table update.  Set the
  // property `stella.test.propertyDemon' to see a test demon in action.
  { MappableObject* demon = lookupFunction(demonname);

    if (!((boolean)(demon))) {
      demon = demonname->lookupGlobalVariable();
    }
    if (((boolean)(demon))) {
      oREGISTERED_PROPERTY_DEMONSo->insertAt(wrapString(property), demon);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "register-property-demon: cannot find a function or variable with this name: " << "`" << demonname << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

void unregisterPropertyDemon(const char* property) {
  // Unregister any demon for `property'.
  oREGISTERED_PROPERTY_DEMONSo->removeAt(wrapString(property));
}

MethodSlot* lookupVariableDemonSetter(GlobalVariable* demon) {
  { Symbol* variablename = demon->variableName;
    const char* postfix = (demon->homeModule()->caseSensitiveP ? "-setter" : "-SETTER");
    Symbol* settername = internDerivedSymbol(variablename, stringConcatenate(variablename->symbolName, postfix, 0));

    return (lookupFunction(settername));
  }
}

void runConfigurationPropertyDemon(Keyword* action, const char* property, Object* value, KeyValueList* table) {
  { MappableObject* demon = ((MappableObject*)(oREGISTERED_PROPERTY_DEMONSo->lookup(wrapString(property))));

    { Surrogate* testValue000 = safePrimaryType(demon);

      if (subtypeOfMethodSlotP(testValue000)) {
        { MappableObject* demon000 = demon;
          MethodSlot* demon = ((MethodSlot*)(demon000));

          ((void  (*) (Keyword*, const char*, Object*, KeyValueList*))demon->functionCode)(action, property, value, table);
        }
      }
      else if (subtypeOfP(testValue000, SGT_SYSTEMS_STELLA_GLOBAL_VARIABLE)) {
        { MappableObject* demon001 = demon;
          GlobalVariable* demon = ((GlobalVariable*)(demon001));

          value = lookupConfigurationProperty(property, NULL, table);
          { MethodSlot* setter = lookupVariableDemonSetter(demon);
            Surrogate* variabletype = typeSpecToBaseType(globalVariableTypeSpec(demon));
            Object* coercedvalue = (((boolean)(value)) ? coerceValueToType(value, variabletype, false) : ((Object*)(NULL)));

            if (((boolean)(value)) &&
                (!((boolean)(coercedvalue)))) {
              *(STANDARD_WARNING->nativeStream) << "Warning: " << "run-configuration-property-demon: cannot coerce " << "`" << value << "'" << " to type " << "`" << variabletype << "'" << std::endl;
              return;
            }
            if (((boolean)(setter))) {
              if (variabletype == SGT_SYSTEMS_STELLA_INTEGER) {
                ((void  (*) (int))setter->functionCode)(unwrapInteger(((IntegerWrapper*)(coercedvalue))));
              }
              else if (variabletype == SGT_SYSTEMS_STELLA_LONG_INTEGER) {
                ((void  (*) (long long int))setter->functionCode)(unwrapLongInteger(((LongIntegerWrapper*)(coercedvalue))));
              }
              else if (variabletype == SGT_SYSTEMS_STELLA_FLOAT) {
                ((void  (*) (double))setter->functionCode)(unwrapFloat(((FloatWrapper*)(coercedvalue))));
              }
              else if (variabletype == SGT_SYSTEMS_STELLA_STRING) {
                ((void  (*) (const char*))setter->functionCode)(unwrapString(((StringWrapper*)(coercedvalue))));
              }
              else if (variabletype == SGT_SYSTEMS_STELLA_BOOLEAN) {
                ((void  (*) (boolean))setter->functionCode)(((BooleanWrapper*)(coercedvalue)) == TRUE_WRAPPER);
              }
              else {
                ((void  (*) (Object*))setter->functionCode)(coercedvalue);
              }
            }
            else {
              writeGlobalVariableValue(demon, coercedvalue);
            }
          }
        }
      }
      else {
      }
    }
  }
}

void demonPropertyHandler(MappableObject* demon, StorageSlot* slot, Object* property) {
  defaultOptionHandler(demon, slot, property);
  oREGISTERED_PROPERTY_DEMONSo->insertAt(wrapString(coerceToString(property)), demon);
}

void testPropertyDemon(Keyword* action, const char* property, Object* value, KeyValueList* table) {
  // A test demon for the property demon machinery which simply prints arguments.
  table = table;
  std::cout << "test-property-demon: action=" << action << ", property=" << property << ", value-arg=" << value << ", prop-value=" << lookupConfigurationProperty(property, NULL, table) << std::endl;
}

CmdLineOption* newCmdLineOption() {
  { CmdLineOption* self = NULL;

    self = new CmdLineOption();
    self->errorAction = KWD_SYSTEMS_ERROR;
    self->handler = ((cpp_function_code)(&defaultCmdLineOptionHandler));
    self->configurationProperty = NULL;
    self->defaultValue = NULL;
    self->nArguments = 0;
    self->multiValuedP = false;
    self->valueType = SGT_SYSTEMS_STELLA_STRING;
    self->keys = NIL;
    self->documentation = "Not documented.";
    return (self);
  }
}

Surrogate* CmdLineOption::primaryType() {
  { CmdLineOption* self = this;

    return (SGT_SYSTEMS_STELLA_CMD_LINE_OPTION);
  }
}

Object* accessCmdLineOptionSlotValue(CmdLineOption* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SYSTEMS_STELLA_DOCUMENTATION) {
    if (setvalueP) {
      self->documentation = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->documentation);
    }
  }
  else if (slotname == SYM_SYSTEMS_STELLA_KEYS) {
    if (setvalueP) {
      self->keys = ((Cons*)(value));
    }
    else {
      value = self->keys;
    }
  }
  else if (slotname == SYM_SYSTEMS_STELLA_VALUE_TYPE) {
    if (setvalueP) {
      self->valueType = ((Surrogate*)(value));
    }
    else {
      value = self->valueType;
    }
  }
  else if (slotname == SYM_SYSTEMS_STELLA_MULTI_VALUEDp) {
    if (setvalueP) {
      self->multiValuedP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->multiValuedP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_SYSTEMS_STELLA_N_ARGUMENTS) {
    if (setvalueP) {
      self->nArguments = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->nArguments);
    }
  }
  else if (slotname == SYM_SYSTEMS_STELLA_DEFAULT_VALUE) {
    if (setvalueP) {
      self->defaultValue = value;
    }
    else {
      value = self->defaultValue;
    }
  }
  else if (slotname == SYM_SYSTEMS_STELLA_CONFIGURATION_PROPERTY) {
    if (setvalueP) {
      self->configurationProperty = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->configurationProperty);
    }
  }
  else if (slotname == SYM_SYSTEMS_STELLA_HANDLER) {
    if (setvalueP) {
      self->handler = ((FunctionCodeWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFunctionCode(self->handler);
    }
  }
  else if (slotname == SYM_SYSTEMS_STELLA_ERROR_ACTION) {
    if (setvalueP) {
      self->errorAction = ((Keyword*)(value));
    }
    else {
      value = self->errorAction;
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

KeyValueMap* oREGISTERED_COMMAND_LINE_OPTIONSo = NULL;

void registerCmdLineOption(int options, ...) {
  // Register a command line option.  :key identifies the name of the option which
  // will usually start with a dash such as `-e' or `--eval'.  :key2 and :key3 can be used to supply
  // additional options (e.g., long option formats).  To supply even more keys, a list can be supplied
  // with the :keys option.  If a :property is supplied, this option simply sets or adds to the values
  // of the specified system configuration property.  If a :handler name is specified, its function
  // will be used to interpret the values of the option.  :documentation can be used to supply a
  // documentation string which will be printed by the `help-option-handler' (usually bound to `-?').
  // :value-type describes what type an option value should be coerced to before assigning it to the
  // specified configuration :property.  :n-arguments describes how many arguments this option
  // takes.  This will be 0 for simple switches and can be 1 or greater than one for option handlers
  // that need one or more arguments.  :default-value defines the value to use for zero-argument
  // :property options.  If :multi-valued? is true, values of multiple occurrences of the option will be
  // added to the specified configuration :property.  :error-action can be one of :ignore, :warn or
  // :error to specify what to do in case an error is encountered during option processing.
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
    { PropertyList* theoptions = parseOptions(arglist000, listO(25, KWD_SYSTEMS_DOCUMENTATION, SGT_SYSTEMS_STELLA_STRING, KWD_SYSTEMS_KEY, SGT_SYSTEMS_STELLA_STRING, KWD_SYSTEMS_KEY2, SGT_SYSTEMS_STELLA_STRING, KWD_SYSTEMS_KEY3, SGT_SYSTEMS_STELLA_STRING, KWD_SYSTEMS_KEYS, SGT_SYSTEMS_STELLA_CONS, KWD_SYSTEMS_VALUE_TYPE, SGT_SYSTEMS_STELLA_TYPE, KWD_SYSTEMS_MULTI_VALUEDp, SGT_SYSTEMS_STELLA_BOOLEAN, KWD_SYSTEMS_N_ARGUMENTS, SGT_SYSTEMS_STELLA_INTEGER, KWD_SYSTEMS_DEFAULT_VALUE, SGT_SYSTEMS_STELLA_OBJECT, KWD_SYSTEMS_PROPERTY, SGT_SYSTEMS_STELLA_STRING, KWD_SYSTEMS_HANDLER, SGT_SYSTEMS_STELLA_SYMBOL, KWD_SYSTEMS_ERROR_ACTION, SGT_SYSTEMS_STELLA_KEYWORD, NIL), true, false);
      CmdLineOption* cmdlineoption = newCmdLineOption();
      Object* value = NULL;

      cmdlineoption->documentation = ((StringWrapper*)(theoptions->lookupWithDefault(KWD_SYSTEMS_DOCUMENTATION, wrapString("Not documented."))))->wrapperValue;
      value = theoptions->lookup(KWD_SYSTEMS_KEY);
      if (((boolean)(value))) {
        cmdlineoption->keys = cons(value, cmdlineoption->keys);
      }
      value = theoptions->lookup(KWD_SYSTEMS_KEY2);
      if (((boolean)(value))) {
        cmdlineoption->keys = cons(value, cmdlineoption->keys);
      }
      value = theoptions->lookup(KWD_SYSTEMS_KEY3);
      if (((boolean)(value))) {
        cmdlineoption->keys = cons(value, cmdlineoption->keys);
      }
      { Object* val = NULL;
        Cons* iter001 = ((Cons*)(theoptions->lookupWithDefault(KWD_SYSTEMS_KEYS, NIL)));

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          val = iter001->value;
          value = coerceValueToType(val, SGT_SYSTEMS_STELLA_STRING, true);
          cmdlineoption->keys = cons(value, cmdlineoption->keys);
        }
      }
      cmdlineoption->keys = cmdlineoption->keys->reverse();
      cmdlineoption->valueType = ((Surrogate*)(theoptions->lookupWithDefault(KWD_SYSTEMS_VALUE_TYPE, SGT_SYSTEMS_STELLA_STRING)));
      cmdlineoption->multiValuedP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_SYSTEMS_MULTI_VALUEDp, FALSE_WRAPPER))));
      cmdlineoption->nArguments = ((IntegerWrapper*)(theoptions->lookupWithDefault(KWD_SYSTEMS_N_ARGUMENTS, wrapInteger(0))))->wrapperValue;
      cmdlineoption->defaultValue = theoptions->lookup(KWD_SYSTEMS_DEFAULT_VALUE);
      cmdlineoption->configurationProperty = ((StringWrapper*)(theoptions->lookupWithDefault(KWD_SYSTEMS_PROPERTY, NULL_STRING_WRAPPER)))->wrapperValue;
      value = theoptions->lookup(KWD_SYSTEMS_HANDLER);
      if (((boolean)(value))) {
        value = lookupFunction(((Symbol*)(value)));
        if (!((boolean)(value))) {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "register-cmd-line-option: cannot find handler function: " << "`" << theoptions->lookup(KWD_SYSTEMS_HANDLER) << "'";
            throw *newStellaException(stream000->theStringReader());
          }
        }
        cmdlineoption->handler = ((MethodSlot*)(value))->functionCode;
      }
      cmdlineoption->errorAction = ((Keyword*)(theoptions->lookupWithDefault(KWD_SYSTEMS_ERROR_ACTION, KWD_SYSTEMS_ERROR)));
      { StringWrapper* key = NULL;
        Cons* iter002 = cmdlineoption->keys;

        for (; !(iter002 == NIL); iter002 = iter002->rest) {
          key = ((StringWrapper*)(iter002->value));
          oREGISTERED_COMMAND_LINE_OPTIONSo->insertAt(key, cmdlineoption);
        }
      }
    }
  }
}

void unregisterCmdLineOption(const char* key) {
  // Unregister the command line option identified by `key' under all its keys.
  { CmdLineOption* cmdlineoption = ((CmdLineOption*)(oREGISTERED_COMMAND_LINE_OPTIONSo->lookup(wrapString(key))));

    if (((boolean)(cmdlineoption))) {
      { StringWrapper* registeredkey = NULL;
        Cons* iter000 = cmdlineoption->keys;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          registeredkey = ((StringWrapper*)(iter000->value));
          oREGISTERED_COMMAND_LINE_OPTIONSo->removeAt(registeredkey);
        }
      }
      oREGISTERED_COMMAND_LINE_OPTIONSo->removeAt(wrapString(key));
    }
  }
}

void unregisterAllCmdLineOptions() {
  // Unregister all currently registered command line options.
  oREGISTERED_COMMAND_LINE_OPTIONSo->clear();
}

void defaultCmdLineOptionHandler(CmdLineOption* option, Object* value) {
  // Default handler that tries to set a system property based on `option' and `value'.
  { const char* property = option->configurationProperty;
    Object* defaultvalue = option->defaultValue;

    if (property == NULL) {
      property = "";
      { StringWrapper* key = NULL;
        Cons* iter000 = option->keys;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          key = ((StringWrapper*)(iter000->value));
          if (strlen((unwrapString(key))) > strlen(property)) {
            property = key->wrapperValue;
          }
        }
      }
    }
    if ((!((boolean)(defaultvalue))) &&
        (option->valueType == SGT_SYSTEMS_STELLA_BOOLEAN)) {
      defaultvalue = TRUE_WRAPPER;
    }
    if (!((boolean)(value))) {
      value = defaultvalue;
    }
    if (option->multiValuedP) {
      if (safePrimaryType(value) == SGT_SYSTEMS_STELLA_CONS) {
        { Object* value000 = value;
          Cons* value = ((Cons*)(value000));

          { Object* val = NULL;
            Cons* iter001 = value;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              val = iter001->value;
              addConfigurationProperty(property, val, NULL);
            }
          }
        }
      }
      else {
        addConfigurationProperty(property, value, NULL);
      }
    }
    else {
      setConfigurationProperty(property, value, NULL);
    }
  }
}

Cons* oUNPROCESSED_COMMAND_LINE_ARGUMENTSo = NULL;

void processCommandLineArguments(int count, const char** arguments, Keyword* unhandledoptionaction) {
  // Interpret any command line `arguments' for which handlers have been registered.
  // Leave any remaining unprocessed arguments in `*unprocessed-command-line-arguments*'.
  // If any unprocessed arguments use option syntax (that is they start with a `-'), proceed
  // according to `unhandledOptionAction' which can be one of :ignore, :warn or :error.
  // This ensures that at any point in the option processing, `*unprocessed-command-line-arguments*'
  // accurately reflects the arguments which have been either skipped or not handled yet.
  if (!((boolean)(oUNPROCESSED_COMMAND_LINE_ARGUMENTSo))) {
    oUNPROCESSED_COMMAND_LINE_ARGUMENTSo = consifyCommandLineArguments(count, arguments);
  }
  { Cons* cmdlineargs = copyConsList(oUNPROCESSED_COMMAND_LINE_ARGUMENTSo);
    const char* argument = NULL;
    int nargs = cmdlineargs->length();
    CmdLineOption* option = NULL;
    Object* value = NULL;
    Cons* unprocessedargs = cons(NULL, oUNPROCESSED_COMMAND_LINE_ARGUMENTSo);
    Cons* unprocessedtrailer = unprocessedargs;

    while (!(cmdlineargs == NIL)) {
      { StringWrapper* head000 = ((StringWrapper*)(cmdlineargs->value));

        cmdlineargs = cmdlineargs->rest;
        argument = head000->wrapperValue;
      }
      nargs = nargs - 1;
      option = ((CmdLineOption*)(oREGISTERED_COMMAND_LINE_OPTIONSo->lookup(wrapString(argument))));
      value = NULL;
      if (((boolean)(option))) {
        if (nargs < option->nArguments) {
          { Keyword* testValue000 = option->errorAction;

            if (testValue000 == KWD_SYSTEMS_ERROR) {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "process-command-line-arguments: missing value for option: " << "`" << argument << "'";
                throw *newStellaException(stream000->theStringReader());
              }
            }
            else if (testValue000 == KWD_SYSTEMS_WARN) {
              *(STANDARD_WARNING->nativeStream) << "Warning: " << "process-command-line-arguments: missing value for option: " << "`" << argument << "'" << std::endl;
            }
            else if (testValue000 == KWD_SYSTEMS_IGNORE) {
            }
            else {
              { OutputStringStream* stream001 = newOutputStringStream();

                *(stream001->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
                throw *newStellaException(stream001->theStringReader());
              }
            }
          }
          continue;
        }
        switch (option->nArguments) {
          case 0: 
            break;
          case 1: 
            { StringWrapper* head001 = ((StringWrapper*)(cmdlineargs->value));

              cmdlineargs = cmdlineargs->rest;
              value = head001;
            }
            nargs = nargs - 1;
            break;
          default:
            { Cons* value000 = NIL;

              { StringWrapper* arg = NULL;
                Cons* iter000 = cmdlineargs;
                int i = NULL_INTEGER;
                int iter001 = 1;
                int upperBound000 = option->nArguments;
                boolean unboundedP000 = upperBound000 == NULL_INTEGER;
                Cons* collect000 = NULL;

                for  (; (!(iter000 == NIL)) &&
                          (unboundedP000 ||
                           (iter001 <= upperBound000)); 
                      iter000 = iter000->rest,
                      iter001 = iter001 + 1) {
                  arg = ((StringWrapper*)(iter000->value));
                  i = iter001;
                  if (!((boolean)(collect000))) {
                    {
                      collect000 = cons(arg, NIL);
                      if (value000 == NIL) {
                        value000 = collect000;
                      }
                      else {
                        addConsToEndOfConsList(value000, collect000);
                      }
                    }
                  }
                  else {
                    {
                      collect000->rest = cons(arg, NIL);
                      collect000 = collect000->rest;
                    }
                  }
                }
              }
              value = value000;
            }
            cmdlineargs = cmdlineargs->nthRest(option->nArguments);
            nargs = nargs - option->nArguments;
            break;
        }
        unprocessedtrailer->rest = unprocessedtrailer->nthRest(option->nArguments + 2);
        oUNPROCESSED_COMMAND_LINE_ARGUMENTSo = ((Cons*)(unprocessedargs->rest));
        try {
          ((void  (*) (CmdLineOption*, Object*))option->handler)(option, value);
        }
        catch (std::exception& _e) {
          std::exception* e = &_e;

          { Keyword* testValue001 = option->errorAction;

            if (testValue001 == KWD_SYSTEMS_ERROR) {
              { OutputStringStream* stream002 = newOutputStringStream();

                *(stream002->nativeStream) << "Error during processing of " << "`" << argument << "'" << " option: " << "`" << exceptionMessage(e) << "'";
                throw *newStellaException(stream002->theStringReader());
              }
            }
            else if (testValue001 == KWD_SYSTEMS_WARN) {
              *(STANDARD_WARNING->nativeStream) << "Warning: " << "Error during processing of " << "`" << argument << "'" << " option: " << "`" << exceptionMessage(e) << "'" << std::endl;
            }
            else if (testValue001 == KWD_SYSTEMS_IGNORE) {
            }
            else {
              { OutputStringStream* stream003 = newOutputStringStream();

                *(stream003->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
                throw *newStellaException(stream003->theStringReader());
              }
            }
          }
        }
      }
      else {
        unprocessedtrailer = unprocessedtrailer->rest;
      }
    }
    oUNPROCESSED_COMMAND_LINE_ARGUMENTSo = ((Cons*)(unprocessedargs->rest));
    { StringWrapper* arg = NULL;
      Cons* iter002 = oUNPROCESSED_COMMAND_LINE_ARGUMENTSo;

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        arg = ((StringWrapper*)(iter002->value));
        if (startsWithP(unwrapString(arg), "-", 0)) {
          if (unhandledoptionaction == KWD_SYSTEMS_WARN) {
            *(STANDARD_WARNING->nativeStream) << "Warning: " << "Unhandled command line option: " << "`" << unwrapString(arg) << "'" << std::endl;
          }
          else if (unhandledoptionaction == KWD_SYSTEMS_ERROR) {
            { OutputStringStream* stream004 = newOutputStringStream();

              *(stream004->nativeStream) << "Unhandled command line option: " << "`" << unwrapString(arg) << "'";
              throw *newStellaException(stream004->theStringReader());
            }
          }
          else if (unhandledoptionaction == KWD_SYSTEMS_IGNORE) {
            break;
          }
          else {
            { OutputStringStream* stream005 = newOutputStringStream();

              *(stream005->nativeStream) << "`" << unhandledoptionaction << "'" << " is not a valid case option";
              throw *newStellaException(stream005->theStringReader());
            }
          }
        }
      }
    }
  }
}

Cons* unprocessedCommandLineArguments() {
  // Return all command line arguments which have not yet been processed
  // by (or been ignored by) `process-command-line-arguments'.  If arguments have not yet
  // been processed, this will return NULL.
  return (oUNPROCESSED_COMMAND_LINE_ARGUMENTSo);
}

void evalOptionHandler(CmdLineOption* option, Object* value) {
  // Interpret an --eval option by evaluating `value'.
  option = option;
  evaluate((stringP(value) ? readSExpressionFromString(((StringWrapper*)(value))->wrapperValue) : value));
}

void evalInModuleOptionHandler(CmdLineOption* option, Object* value) {
  // Interpret an --eval-in-module option.  `value' is expected
  // to be of the form `(<module-name> <s-expression>)'.
  if (safePrimaryType(value) == SGT_SYSTEMS_STELLA_CONS) {
    { Object* value000 = value;
      Cons* value = ((Cons*)(value000));

      { 
        BIND_STELLA_SPECIAL(oMODULEo, Module*, coerceToModule(value->value, true));
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
        evalOptionHandler(option, value->rest->value);
      }
    }
  }
  else {
  }
}

void loadPathOptionHandler(CmdLineOption* option, Object* value) {
  // Modify the current file load path according to `option' and `value'.
  if (option->keys->memberP(wrapString("--path="))) {
    setLoadPath(((StringWrapper*)(value))->wrapperValue);
  }
  else if (option->keys->memberP(wrapString("--path=+"))) {
    addLoadPath(((StringWrapper*)(value))->wrapperValue);
  }
  else {
    pushLoadPath(((StringWrapper*)(value))->wrapperValue);
  }
}

void configFileOptionHandler(CmdLineOption* option, Object* value) {
  // Load the configuration file `value'.  This will
  // modify currently set system properties defined in `value' with new
  // values but leave all other currently set properties as they are.
  option = option;
  { KeyValueList* currentconfig = oSYSTEM_CONFIGURATION_TABLEo;

    try {
      oSYSTEM_CONFIGURATION_TABLEo = currentconfig->copy();
      loadConfigurationFile(((StringWrapper*)(value))->wrapperValue);
    }
    catch (std::exception ) {
      oSYSTEM_CONFIGURATION_TABLEo = currentconfig;
    }
  }
}

void loadFileOptionHandler(CmdLineOption* option, Object* value) {
  // Load the file `value' using the STELLA `load-file' command.
  option = option;
  loadFile(((StringWrapper*)(value))->wrapperValue);
}

void definePropertyOptionHandler(CmdLineOption* option, Object* value) {
  option = option;
  { StringWrapper* prop = NULL;
    Wrapper* val = NULL;
    Keyword* op = NULL;

    prop = parseConfigurationFileLine(((StringWrapper*)(value))->wrapperValue, val, op);
    if (op == KWD_SYSTEMS_ADD) {
      addConfigurationProperty(prop->wrapperValue, val, NULL);
    }
    else {
      setConfigurationProperty(prop->wrapperValue, val, NULL);
    }
  }
}

// Documentation to be printed at the beginning of command line help.
const char* oCOMMAND_LINE_HELP_HEADERo = "";

// Documentation to be printed at the end of command line help.
const char* oCOMMAND_LINE_HELP_TRAILERo = "";

void helpOptionHandler(CmdLineOption* option, Object* value) {
  // Print documentation about all currently registered option handlers.
  value = value;
  { Cons* sortedoptions = NIL;

    { StringWrapper* key = NULL;
      CmdLineOption* option = NULL;
      DictionaryIterator* iter000 = ((DictionaryIterator*)(oREGISTERED_COMMAND_LINE_OPTIONSo->allocateIterator()));
      Cons* collect000 = NULL;

      for  (; iter000->nextP(); ) {
        key = ((StringWrapper*)(iter000->key));
        option = ((CmdLineOption*)(iter000->value));
        if (eqlP(key, ((StringWrapper*)(option->keys->value)))) {
          while (startsWithP(key->wrapperValue, "-", 0)) {
            key = wrapString(stringSubsequence(unwrapString(key), 1, NULL_INTEGER));
          }
          key = wrapString(stringDowncase(key->wrapperValue));
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(consList(2, key, option), NIL);
              if (sortedoptions == NIL) {
                sortedoptions = collect000;
              }
              else {
                addConsToEndOfConsList(sortedoptions, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(consList(2, key, option), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    sortedoptions = sortedoptions->removeDuplicates()->sortTuples(0, NULL);
    if (!(blankStringP(oCOMMAND_LINE_HELP_HEADERo))) {
      std::cout << oCOMMAND_LINE_HELP_HEADERo << std::endl;
    }
    std::cout << "The following command line options are supported:" << std::endl;
    { Cons* tuple = NULL;
      Cons* iter001 = sortedoptions;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        tuple = ((Cons*)(iter001->value));
        option = ((CmdLineOption*)(tuple->rest->value));
        { StringWrapper* key = NULL;
          Cons* iter002 = option->keys;
          int i = NULL_INTEGER;
          int iter003 = 1;

          for  (; !(iter002 == NIL); 
                iter002 = iter002->rest,
                iter003 = iter003 + 1) {
            key = ((StringWrapper*)(iter002->value));
            i = iter003;
            if (i > 1) {
              std::cout << ", ";
            }
            std::cout << unwrapString(key);
          }
        }
        std::cout << " ";
        std::cout << option->documentation << std::endl;
      }
    }
    if (!(blankStringP(oCOMMAND_LINE_HELP_TRAILERo))) {
      std::cout << oCOMMAND_LINE_HELP_TRAILERo << std::endl;
    }
    setConfigurationProperty("stella.showInfoOnly", TRUE_WRAPPER, NULL);
  }
}

void helpStartupSystems1() {
  {
    SYM_SYSTEMS_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    KWD_SYSTEMS_TRUE = ((Keyword*)(internRigidSymbolWrtModule("TRUE", NULL, 2)));
    SYM_SYSTEMS_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", NULL, 0)));
    KWD_SYSTEMS_FALSE = ((Keyword*)(internRigidSymbolWrtModule("FALSE", NULL, 2)));
    SGT_SYSTEMS_STELLA_UNKNOWN = ((Surrogate*)(internRigidSymbolWrtModule("UNKNOWN", NULL, 1)));
    SGT_SYSTEMS_STELLA_GENERALIZED_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("GENERALIZED-SYMBOL", NULL, 1)));
    SGT_SYSTEMS_STELLA_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER", NULL, 1)));
    SGT_SYSTEMS_STELLA_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT", NULL, 1)));
    SGT_SYSTEMS_STELLA_NUMBER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER", NULL, 1)));
    SGT_SYSTEMS_STELLA_STRING = ((Surrogate*)(internRigidSymbolWrtModule("STRING", NULL, 1)));
    SGT_SYSTEMS_STELLA_KEYWORD = ((Surrogate*)(internRigidSymbolWrtModule("KEYWORD", NULL, 1)));
    SGT_SYSTEMS_STELLA_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("SYMBOL", NULL, 1)));
    SGT_SYSTEMS_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 1)));
    SGT_SYSTEMS_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", NULL, 1)));
    SGT_SYSTEMS_STELLA_PROPERTY_LIST = ((Surrogate*)(internRigidSymbolWrtModule("PROPERTY-LIST", NULL, 1)));
    SGT_SYSTEMS_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SGT_SYSTEMS_STELLA_LIST = ((Surrogate*)(internRigidSymbolWrtModule("LIST", NULL, 1)));
    KWD_SYSTEMS_OPTIONS = ((Keyword*)(internRigidSymbolWrtModule("OPTIONS", NULL, 2)));
    SGT_SYSTEMS_STELLA_IDENTITY = ((Surrogate*)(internRigidSymbolWrtModule("IDENTITY", NULL, 1)));
    KWD_SYSTEMS_DEFINE = ((Keyword*)(internRigidSymbolWrtModule("DEFINE", NULL, 2)));
    SYM_SYSTEMS_STELLA_IN_MODULE = ((Symbol*)(internRigidSymbolWrtModule("IN-MODULE", NULL, 0)));
    KWD_SYSTEMS_FINALIZE = ((Keyword*)(internRigidSymbolWrtModule("FINALIZE", NULL, 2)));
    SYM_SYSTEMS_STELLA_DEFMODULE = ((Symbol*)(internRigidSymbolWrtModule("DEFMODULE", NULL, 0)));
    SYM_SYSTEMS_STELLA_DEFSYSTEM = ((Symbol*)(internRigidSymbolWrtModule("DEFSYSTEM", NULL, 0)));
    SYM_SYSTEMS_STELLA_DEFCLASS = ((Symbol*)(internRigidSymbolWrtModule("DEFCLASS", NULL, 0)));
    SYM_SYSTEMS_STELLA_DEFSLOT = ((Symbol*)(internRigidSymbolWrtModule("DEFSLOT", NULL, 0)));
    SYM_SYSTEMS_STELLA_DEFUN = ((Symbol*)(internRigidSymbolWrtModule("DEFUN", NULL, 0)));
    SYM_SYSTEMS_STELLA_DEFMETHOD = ((Symbol*)(internRigidSymbolWrtModule("DEFMETHOD", NULL, 0)));
    KWD_SYSTEMS_DOCUMENTATION = ((Keyword*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 2)));
    KWD_SYSTEMS_PUBLICp = ((Keyword*)(internRigidSymbolWrtModule("PUBLIC?", NULL, 2)));
    KWD_SYSTEMS_DIRECTORY = ((Keyword*)(internRigidSymbolWrtModule("DIRECTORY", NULL, 2)));
    KWD_SYSTEMS_FILES = ((Keyword*)(internRigidSymbolWrtModule("FILES", NULL, 2)));
    KWD_SYSTEMS_REQUIRED_SYSTEMS = ((Keyword*)(internRigidSymbolWrtModule("REQUIRED-SYSTEMS", NULL, 2)));
    KWD_SYSTEMS_ACTION = ((Keyword*)(internRigidSymbolWrtModule("ACTION", NULL, 2)));
    KWD_SYSTEMS_LOAD_SYSTEM = ((Keyword*)(internRigidSymbolWrtModule("LOAD-SYSTEM", NULL, 2)));
    KWD_SYSTEMS_LANGUAGE = ((Keyword*)(internRigidSymbolWrtModule("LANGUAGE", NULL, 2)));
    KWD_SYSTEMS_MAKE_SYSTEM = ((Keyword*)(internRigidSymbolWrtModule("MAKE-SYSTEM", NULL, 2)));
    KWD_SYSTEMS_LISP_ONLY_FILES = ((Keyword*)(internRigidSymbolWrtModule("LISP-ONLY-FILES", NULL, 2)));
    KWD_SYSTEMS_CPP_ONLY_FILES = ((Keyword*)(internRigidSymbolWrtModule("CPP-ONLY-FILES", NULL, 2)));
    KWD_SYSTEMS_JAVA_ONLY_FILES = ((Keyword*)(internRigidSymbolWrtModule("JAVA-ONLY-FILES", NULL, 2)));
    KWD_SYSTEMS_DATA_FILES = ((Keyword*)(internRigidSymbolWrtModule("DATA-FILES", NULL, 2)));
    KWD_SYSTEMS_PREPROCESSED_FILES = ((Keyword*)(internRigidSymbolWrtModule("PREPROCESSED-FILES", NULL, 2)));
    KWD_SYSTEMS_CARDINAL_MODULE = ((Keyword*)(internRigidSymbolWrtModule("CARDINAL-MODULE", NULL, 2)));
    KWD_SYSTEMS_ROOT_SOURCE_DIRECTORY = ((Keyword*)(internRigidSymbolWrtModule("ROOT-SOURCE-DIRECTORY", NULL, 2)));
    KWD_SYSTEMS_ROOT_NATIVE_DIRECTORY = ((Keyword*)(internRigidSymbolWrtModule("ROOT-NATIVE-DIRECTORY", NULL, 2)));
    KWD_SYSTEMS_ROOT_BINARY_DIRECTORY = ((Keyword*)(internRigidSymbolWrtModule("ROOT-BINARY-DIRECTORY", NULL, 2)));
    KWD_SYSTEMS_BANNER = ((Keyword*)(internRigidSymbolWrtModule("BANNER", NULL, 2)));
    KWD_SYSTEMS_COPYRIGHT_HEADER = ((Keyword*)(internRigidSymbolWrtModule("COPYRIGHT-HEADER", NULL, 2)));
    KWD_SYSTEMS_PRODUCTION_SETTINGS = ((Keyword*)(internRigidSymbolWrtModule("PRODUCTION-SETTINGS", NULL, 2)));
    KWD_SYSTEMS_DEVELOPMENT_SETTINGS = ((Keyword*)(internRigidSymbolWrtModule("DEVELOPMENT-SETTINGS", NULL, 2)));
    KWD_SYSTEMS_FINALIZATION_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FINALIZATION-FUNCTION", NULL, 2)));
    KWD_SYSTEMS_JAVA = ((Keyword*)(internRigidSymbolWrtModule("JAVA", NULL, 2)));
    KWD_SYSTEMS_LISP = ((Keyword*)(internRigidSymbolWrtModule("LISP", NULL, 2)));
    KWD_SYSTEMS_CPP = ((Keyword*)(internRigidSymbolWrtModule("CPP", NULL, 2)));
    KWD_SYSTEMS_LISP_BINARY = ((Keyword*)(internRigidSymbolWrtModule("LISP-BINARY", NULL, 2)));
    KWD_SYSTEMS_TWO_PASSp = ((Keyword*)(internRigidSymbolWrtModule("TWO-PASS?", NULL, 2)));
    KWD_SYSTEMS_DEVELOPMENT_SETTINGSp = ((Keyword*)(internRigidSymbolWrtModule("DEVELOPMENT-SETTINGS?", NULL, 2)));
    KWD_SYSTEMS_PRODUCTION_SETTINGSp = ((Keyword*)(internRigidSymbolWrtModule("PRODUCTION-SETTINGS?", NULL, 2)));
    KWD_SYSTEMS_FORCE_TRANSLATIONp = ((Keyword*)(internRigidSymbolWrtModule("FORCE-TRANSLATION?", NULL, 2)));
    KWD_SYSTEMS_FORCE_RECOMPILATIONp = ((Keyword*)(internRigidSymbolWrtModule("FORCE-RECOMPILATION?", NULL, 2)));
  }
}

void helpStartupSystems2() {
  {
    KWD_SYSTEMS_LOAD_SYSTEMp = ((Keyword*)(internRigidSymbolWrtModule("LOAD-SYSTEM?", NULL, 2)));
    KWD_SYSTEMS_STARTUPp = ((Keyword*)(internRigidSymbolWrtModule("STARTUP?", NULL, 2)));
    KWD_SYSTEMS_RECURSIVEp = ((Keyword*)(internRigidSymbolWrtModule("RECURSIVE?", NULL, 2)));
    SGT_SYSTEMS_STELLA_FILE_NAME = ((Surrogate*)(internRigidSymbolWrtModule("FILE-NAME", NULL, 1)));
    KWD_SYSTEMS_PROCESSED = ((Keyword*)(internRigidSymbolWrtModule("PROCESSED", NULL, 2)));
    KWD_SYSTEMS_COMMON_LISP = ((Keyword*)(internRigidSymbolWrtModule("COMMON-LISP", NULL, 2)));
    KWD_SYSTEMS_USE_COMMON_LISP_STRUCTS = ((Keyword*)(internRigidSymbolWrtModule("USE-COMMON-LISP-STRUCTS", NULL, 2)));
    KWD_SYSTEMS_STELLA = ((Keyword*)(internRigidSymbolWrtModule("STELLA", NULL, 2)));
    KWD_SYSTEMS_WARN_ABOUT_UNDEFINED_METHODS = ((Keyword*)(internRigidSymbolWrtModule("WARN-ABOUT-UNDEFINED-METHODS", NULL, 2)));
    SYM_SYSTEMS_STELLA_UNLESS = ((Symbol*)(internRigidSymbolWrtModule("UNLESS", NULL, 0)));
    SYM_SYSTEMS_STELLA_SYSTEM_STARTED_UPp = ((Symbol*)(internRigidSymbolWrtModule("SYSTEM-STARTED-UP?", NULL, 0)));
    SYM_SYSTEMS_STELLA_STARTUP_TIME_PROGN = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-TIME-PROGN", NULL, 0)));
    KWD_SYSTEMS_EARLY_INITS = ((Keyword*)(internRigidSymbolWrtModule("EARLY-INITS", NULL, 2)));
    KWD_SYSTEMS_MODULES = ((Keyword*)(internRigidSymbolWrtModule("MODULES", NULL, 2)));
    SYM_SYSTEMS_STELLA_DEFINE_MODULE_FROM_STRINGIFIED_SOURCE = ((Symbol*)(internRigidSymbolWrtModule("DEFINE-MODULE-FROM-STRINGIFIED-SOURCE", NULL, 0)));
    SYM_SYSTEMS_STELLA_STARTUP = ((Symbol*)(internRigidSymbolWrtModule("STARTUP", NULL, 0)));
    SYM_SYSTEMS_STELLA_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("FOREACH", NULL, 0)));
    SYM_SYSTEMS_STELLA_PHASE = ((Symbol*)(internRigidSymbolWrtModule("PHASE", NULL, 0)));
    SYM_SYSTEMS_STELLA_IN = ((Symbol*)(internRigidSymbolWrtModule("IN", NULL, 0)));
    SYM_SYSTEMS_STELLA_INTERVAL = ((Symbol*)(internRigidSymbolWrtModule("INTERVAL", NULL, 0)));
    SYM_SYSTEMS_STELLA_PHASE_TO_INTEGER = ((Symbol*)(internRigidSymbolWrtModule("PHASE-TO-INTEGER", NULL, 0)));
    KWD_SYSTEMS_FINAL = ((Keyword*)(internRigidSymbolWrtModule("FINAL", NULL, 2)));
    SYM_SYSTEMS_STELLA_DO = ((Symbol*)(internRigidSymbolWrtModule("DO", NULL, 0)));
    SYM_SYSTEMS_STELLA_SETQ = ((Symbol*)(internRigidSymbolWrtModule("SETQ", NULL, 0)));
    SYM_SYSTEMS_STELLA_oSTARTUP_TIME_PHASEo = ((Symbol*)(internRigidSymbolWrtModule("*STARTUP-TIME-PHASE*", NULL, 0)));
    KWD_SYSTEMS_DAYS = ((Keyword*)(internRigidSymbolWrtModule("DAYS", NULL, 2)));
    KWD_SYSTEMS_HOURS = ((Keyword*)(internRigidSymbolWrtModule("HOURS", NULL, 2)));
    KWD_SYSTEMS_MINUTES = ((Keyword*)(internRigidSymbolWrtModule("MINUTES", NULL, 2)));
    KWD_SYSTEMS_SECONDS = ((Keyword*)(internRigidSymbolWrtModule("SECONDS", NULL, 2)));
    SYM_SYSTEMS_STELLA_SYSTEM_VERSION = ((Symbol*)(internRigidSymbolWrtModule("SYSTEM-VERSION", NULL, 0)));
    KWD_SYSTEMS_SET = ((Keyword*)(internRigidSymbolWrtModule("SET", NULL, 2)));
    KWD_SYSTEMS_WHITE_SPACE = ((Keyword*)(internRigidSymbolWrtModule("WHITE-SPACE", NULL, 2)));
    KWD_SYSTEMS_ADD = ((Keyword*)(internRigidSymbolWrtModule("ADD", NULL, 2)));
    SYM_SYSTEMS_STELLA_CONFIGURATION_TABLE = ((Symbol*)(internRigidSymbolWrtModule("CONFIGURATION-TABLE", NULL, 0)));
    KWD_SYSTEMS_CLEAR = ((Keyword*)(internRigidSymbolWrtModule("CLEAR", NULL, 2)));
    KWD_SYSTEMS_REMOVE = ((Keyword*)(internRigidSymbolWrtModule("REMOVE", NULL, 2)));
    KWD_SYSTEMS_ROOT_DIRECTORY = ((Keyword*)(internRigidSymbolWrtModule("ROOT-DIRECTORY", NULL, 2)));
    SGT_SYSTEMS_STELLA_GLOBAL_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("GLOBAL-VARIABLE", NULL, 1)));
    SGT_SYSTEMS_STELLA_LONG_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("LONG-INTEGER", NULL, 1)));
    SYM_SYSTEMS_STELLA_TEST_PROPERTY_DEMON = ((Symbol*)(internRigidSymbolWrtModule("TEST-PROPERTY-DEMON", NULL, 0)));
    KWD_SYSTEMS_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    SGT_SYSTEMS_STELLA_CMD_LINE_OPTION = ((Surrogate*)(internRigidSymbolWrtModule("CMD-LINE-OPTION", NULL, 1)));
    SYM_SYSTEMS_STELLA_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 0)));
    SYM_SYSTEMS_STELLA_KEYS = ((Symbol*)(internRigidSymbolWrtModule("KEYS", NULL, 0)));
    SYM_SYSTEMS_STELLA_VALUE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("VALUE-TYPE", NULL, 0)));
    SYM_SYSTEMS_STELLA_MULTI_VALUEDp = ((Symbol*)(internRigidSymbolWrtModule("MULTI-VALUED?", NULL, 0)));
    SYM_SYSTEMS_STELLA_N_ARGUMENTS = ((Symbol*)(internRigidSymbolWrtModule("N-ARGUMENTS", NULL, 0)));
    SYM_SYSTEMS_STELLA_DEFAULT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("DEFAULT-VALUE", NULL, 0)));
    SYM_SYSTEMS_STELLA_CONFIGURATION_PROPERTY = ((Symbol*)(internRigidSymbolWrtModule("CONFIGURATION-PROPERTY", NULL, 0)));
    SYM_SYSTEMS_STELLA_HANDLER = ((Symbol*)(internRigidSymbolWrtModule("HANDLER", NULL, 0)));
    SYM_SYSTEMS_STELLA_ERROR_ACTION = ((Symbol*)(internRigidSymbolWrtModule("ERROR-ACTION", NULL, 0)));
    KWD_SYSTEMS_KEY = ((Keyword*)(internRigidSymbolWrtModule("KEY", NULL, 2)));
    KWD_SYSTEMS_KEY2 = ((Keyword*)(internRigidSymbolWrtModule("KEY2", NULL, 2)));
    KWD_SYSTEMS_KEY3 = ((Keyword*)(internRigidSymbolWrtModule("KEY3", NULL, 2)));
    KWD_SYSTEMS_KEYS = ((Keyword*)(internRigidSymbolWrtModule("KEYS", NULL, 2)));
    KWD_SYSTEMS_VALUE_TYPE = ((Keyword*)(internRigidSymbolWrtModule("VALUE-TYPE", NULL, 2)));
    SGT_SYSTEMS_STELLA_TYPE = ((Surrogate*)(internRigidSymbolWrtModule("TYPE", NULL, 1)));
    KWD_SYSTEMS_MULTI_VALUEDp = ((Keyword*)(internRigidSymbolWrtModule("MULTI-VALUED?", NULL, 2)));
    KWD_SYSTEMS_N_ARGUMENTS = ((Keyword*)(internRigidSymbolWrtModule("N-ARGUMENTS", NULL, 2)));
    KWD_SYSTEMS_DEFAULT_VALUE = ((Keyword*)(internRigidSymbolWrtModule("DEFAULT-VALUE", NULL, 2)));
  }
}

void helpStartupSystems3() {
  {
    SGT_SYSTEMS_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", NULL, 1)));
    KWD_SYSTEMS_PROPERTY = ((Keyword*)(internRigidSymbolWrtModule("PROPERTY", NULL, 2)));
    KWD_SYSTEMS_HANDLER = ((Keyword*)(internRigidSymbolWrtModule("HANDLER", NULL, 2)));
    KWD_SYSTEMS_ERROR_ACTION = ((Keyword*)(internRigidSymbolWrtModule("ERROR-ACTION", NULL, 2)));
    KWD_SYSTEMS_WARN = ((Keyword*)(internRigidSymbolWrtModule("WARN", NULL, 2)));
    KWD_SYSTEMS_IGNORE = ((Keyword*)(internRigidSymbolWrtModule("IGNORE", NULL, 2)));
    SYM_SYSTEMS_STELLA_EVAL_OPTION_HANDLER = ((Symbol*)(internRigidSymbolWrtModule("EVAL-OPTION-HANDLER", NULL, 0)));
    SYM_SYSTEMS_STELLA_EVAL_IN_MODULE_OPTION_HANDLER = ((Symbol*)(internRigidSymbolWrtModule("EVAL-IN-MODULE-OPTION-HANDLER", NULL, 0)));
    SYM_SYSTEMS_STELLA_LOAD_PATH_OPTION_HANDLER = ((Symbol*)(internRigidSymbolWrtModule("LOAD-PATH-OPTION-HANDLER", NULL, 0)));
    SYM_SYSTEMS_STELLA_CONFIG_FILE_OPTION_HANDLER = ((Symbol*)(internRigidSymbolWrtModule("CONFIG-FILE-OPTION-HANDLER", NULL, 0)));
    SYM_SYSTEMS_STELLA_LOAD_FILE_OPTION_HANDLER = ((Symbol*)(internRigidSymbolWrtModule("LOAD-FILE-OPTION-HANDLER", NULL, 0)));
    SYM_SYSTEMS_STELLA_DEFINE_PROPERTY_OPTION_HANDLER = ((Symbol*)(internRigidSymbolWrtModule("DEFINE-PROPERTY-OPTION-HANDLER", NULL, 0)));
    SYM_SYSTEMS_STELLA_HELP_OPTION_HANDLER = ((Symbol*)(internRigidSymbolWrtModule("HELP-OPTION-HANDLER", NULL, 0)));
    SYM_SYSTEMS_STELLA_STARTUP_SYSTEMS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-SYSTEMS", NULL, 0)));
    SYM_SYSTEMS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupSystems4() {
  {
    oFILE_LOAD_PATHo = NIL;
    oSTELLA_FILE_EXTENSIONSo = consList(1, wrapString(".ste"));
    oCURRENTLOADFILEo = NULL;
    oSYSTEMDEFINITIONSo = newList();
    oSYSTEM_CONFIGURATION_TABLEo = newKeyValueList();
    oPL_ROOT_DIRECTORYo = NULL;
    oREGISTERED_PROPERTY_DEMONSo = newKeyValueMap();
    oREGISTERED_COMMAND_LINE_OPTIONSo = newKeyValueMap();
  }
}

void helpStartupSystems5() {
  {
    defineFunctionObject("PARSE-DIRECTORY-PATH", "(DEFUN (PARSE-DIRECTORY-PATH (CONS OF STRING-WRAPPER)) ((PATH STRING)))", ((cpp_function_code)(&parseDirectoryPath)), NULL);
    defineFunctionObject("SET-LOAD-PATH", "(DEFUN (SET-LOAD-PATH (CONS OF STRING-WRAPPER)) ((PATH STRING)) :DOCUMENTATION \"Set the STELLA load path to the |-separated\ndirectories listed in `path'.  Return the resulting load path.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&setLoadPath)), ((cpp_function_code)(&setLoadPathEvaluatorWrapper)));
    defineFunctionObject("GET-LOAD-PATH", "(DEFUN (GET-LOAD-PATH (CONS OF STRING-WRAPPER)) () :DOCUMENTATION \"Return the current STELLA load path.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&getLoadPath)), NULL);
    defineFunctionObject("PUSH-LOAD-PATH", "(DEFUN (PUSH-LOAD-PATH (CONS OF STRING-WRAPPER)) ((PATH STRING)) :DOCUMENTATION \"Add the directories listed in the |-separated\n`path' to the front of the STELLA load path.  Return the\nresulting load path.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&pushLoadPath)), ((cpp_function_code)(&pushLoadPathEvaluatorWrapper)));
    defineFunctionObject("POP-LOAD-PATH", "(DEFUN (POP-LOAD-PATH STRING) () :DOCUMENTATION \"Remove the first element from the STELLA load path\nand return the removed element.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&popLoadPath)), ((cpp_function_code)(&popLoadPathEvaluatorWrapper)));
    defineFunctionObject("ADD-LOAD-PATH", "(DEFUN (ADD-LOAD-PATH (CONS OF STRING-WRAPPER)) ((PATH STRING)) :DOCUMENTATION \"Append the directories listed in the |-separated\n`path' to the end of the STELLA load path.  Return the resulting\nload path.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&addLoadPath)), ((cpp_function_code)(&addLoadPathEvaluatorWrapper)));
    defineFunctionObject("DROP-LOAD-PATH", "(DEFUN (DROP-LOAD-PATH (CONS OF STRING-WRAPPER)) ((PATH STRING)) :DOCUMENTATION \"Remove the directories listed in the |-separated\n`path' from the PowerLoom load path.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&dropLoadPath)), ((cpp_function_code)(&dropLoadPathEvaluatorWrapper)));
    defineFunctionObject("FIND-FILE-IN-LOAD-PATH", "(DEFUN (FIND-FILE-IN-LOAD-PATH STRING) ((FILE STRING) (EXTENSIONS (CONS OF STRING-WRAPPER))) :DOCUMENTATION \"Try to find `file' in the current load path and, if found,\nreturn its full name.  If `file' can't be found literally, try to find it\nwith any of the listed `extensions' added.  If `extensions' is NULL it defaults\nto `*stella-file-extensions*', therefore, to not default to any extensions\nthe value has to be supplied as NIL.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&findFileInLoadPath)), ((cpp_function_code)(&findFileInLoadPathEvaluatorWrapper)));
    defineFunctionObject("COERCE-VALUE-TO-BOOLEAN", "(DEFUN (COERCE-VALUE-TO-BOOLEAN BOOLEAN-WRAPPER) ((VALUE OBJECT) (ERROR? BOOLEAN)) :DOCUMENTATION \"Return the boolean object represented by `value'.  Return NULL\nif coercion is not possible or raise an error if `error?' is TRUE.\" :PUBLIC? TRUE)", ((cpp_function_code)(&coerceValueToBoolean)), NULL);
    defineFunctionObject("COERCE-TO-BOOLEAN", "(DEFUN (COERCE-TO-BOOLEAN BOOLEAN-WRAPPER) ((OBJECT OBJECT)) :DOCUMENTATION \"Return the boolean object represented by `object'.\nReturn NULL if coercion is not possible.\" :PUBLIC? TRUE)", ((cpp_function_code)(&coerceToBoolean)), NULL);
    defineFunctionObject("COERCE-VALUE-TO-STRING", "(DEFUN (COERCE-VALUE-TO-STRING STRING) ((VALUE OBJECT) (ERROR? BOOLEAN)) :DOCUMENTATION \"Coerce `value' into a string if possible, return NULL\notherwise or raise an error if `error?' is true.\" :PUBLIC? TRUE)", ((cpp_function_code)(&coerceValueToString)), NULL);
    defineFunctionObject("COERCE-TO-STRING", "(DEFUN (COERCE-TO-STRING STRING) ((OBJECT OBJECT)) :DOCUMENTATION \"Coerce `object' into a string.  If no standard coercion\nis possible, simply stringify `object'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&coerceToString)), NULL);
    defineFunctionObject("COERCE-VALUE-TO-FLOAT", "(DEFUN (COERCE-VALUE-TO-FLOAT FLOAT) ((VALUE OBJECT) (ERROR? BOOLEAN)) :DOCUMENTATION \"Coerce `value' to a float value if possible, return\nNULL otherwise or raise an error if `error?' is true.\" :PUBLIC? TRUE)", ((cpp_function_code)(&coerceValueToFloat)), NULL);
    defineFunctionObject("COERCE-TO-FLOAT", "(DEFUN (COERCE-TO-FLOAT FLOAT) ((OBJECT OBJECT)) :DOCUMENTATION \"Coerce `number' to a float value or NULL if not possible.\" :PUBLIC? TRUE)", ((cpp_function_code)(&coerceToFloat)), NULL);
    defineFunctionObject("COERCE-VALUE-TO-TYPE", "(DEFUN (COERCE-VALUE-TO-TYPE OBJECT) ((VALUE OBJECT) (TYPE TYPE) (ERROR? BOOLEAN)) :DOCUMENTATION \"Coerce `value' to `type'.  Return NULL if not possible\nor raise an error if `error?' is TRUE.\" :PUBLIC? TRUE)", ((cpp_function_code)(&coerceValueToType)), NULL);
    defineFunctionObject("COERCE-OPTION-VALUE", "(DEFUN (COERCE-OPTION-VALUE OBJECT) ((VALUE OBJECT) (TYPE TYPE)) :DOCUMENTATION \"Coerce `value' to `type'.  Return NULL if not possible.\" :PUBLIC? TRUE)", ((cpp_function_code)(&coerceOptionValue)), NULL);
    defineFunctionObject("VET-OPTIONS", "(DEFUN (VET-OPTIONS PROPERTY-LIST) ((PLIST OBJECT) (LEGALOPTIONS (CONS OF KEYWORD))))", ((cpp_function_code)(&vetOptions)), NULL);
    defineFunctionObject("PARSE-OPTIONS", "(DEFUN (PARSE-OPTIONS PROPERTY-LIST) ((OPTIONS OBJECT) (|LEGALOPTIONS&TYPES| CONS) (COERCIONERROR? BOOLEAN) (ALLOWOTHERKEYS? BOOLEAN)) :DOCUMENTATION \"Parse `options', check their validity according to\n`legalOptions&Types' and return the result as a PROPERTY-LIST.\n`legalOptions&Types' has to either be NULL or a flat list of legal\n<keyword> <coercionType> pairs.  A type specifcation of @IDENTITY\nmeans don't perform any coercion.\nIf `coercionError?' is TRUE, raise an error if a coercion failed.\nIf `allowOtherKeys?' is TRUE options other than those specified in\n`legalOptions&Types' are allowed but won't be coerced since we don't\nknow their type.  A special implicit :options keyword that does not\nneed to be declared can be used to pass in an already parsed options\nlist from a caller, which will then be analyzed and used instead.\" :PUBLIC? TRUE)", ((cpp_function_code)(&parseOptions)), NULL);
    defineFunctionObject("EVALUATE-COMMAND", "(DEFUN (EVALUATE-COMMAND OBJECT) ((COMMAND OBJECT) (FINALIZE? BOOLEAN)))", ((cpp_function_code)(&evaluateCommand)), NULL);
    defineFunctionObject("LOAD-FILE", "(DEFUN LOAD-FILE ((FILE STRING)) :DOCUMENTATION \"Read STELLA commands from `file' and evaluate them.\nThe file should begin with an `in-module' declaration that specifies\nthe module within which all remaining commands are to be evaluated\nThe remaining commands are evaluated one-by-one, applying the function\n`evaluate' to each of them.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&loadFile)), ((cpp_function_code)(&loadFileEvaluatorWrapper)));
    defineFunctionObject("MAKE-SYSTEM-DEFINITION-FILE-NAME", "(DEFUN (MAKE-SYSTEM-DEFINITION-FILE-NAME FILE-NAME) ((NAME STRING)) :DOCUMENTATION \"Make a canonical system definition file name for a system named `name'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&makeSystemDefinitionFileName)), NULL);
    defineFunctionObject("BUILD-STELLA-SYSTEMS-PATH", "(DEFUN (BUILD-STELLA-SYSTEMS-PATH (CONS OF STRING-WRAPPER)) ())", ((cpp_function_code)(&buildStellaSystemsPath)), NULL);
    defineFunctionObject("FIND-SYSTEM-DEFINITION-FILE", "(DEFUN (FIND-SYSTEM-DEFINITION-FILE FILE-NAME) ((NAME STRING)) :DOCUMENTATION \"Try to find an existing system definition file for a system named `name'\nin the current STELLA_SYSTEMS_PATH or built-in implicit systems path.  Return NULL if no\nsuch definition file can be found.  See `build-stella-systems-path' on where it looks.\" :PUBLIC? TRUE)", ((cpp_function_code)(&findSystemDefinitionFile)), NULL);
    defineFunctionObject("FIND-SYSTEM-ROOT-DIRECTORY-FROM-FILE", "(DEFUN (FIND-SYSTEM-ROOT-DIRECTORY-FROM-FILE FILE-NAME) ((SYSDEFFILE FILE-NAME)) :DOCUMENTATION \"Given a system definition file `sysDefFile' try to determine the root directory\nof the STELLA installation containing this system by looking for top-level native directories.\" :PUBLIC? TRUE)", ((cpp_function_code)(&findSystemRootDirectoryFromFile)), NULL);
    defineFunctionObject("FIND-SYSTEM-ROOT-DIRECTORY", "(DEFUN (FIND-SYSTEM-ROOT-DIRECTORY FILE-NAME) ((SYSTEM SYSTEM-DEFINITION)) :DOCUMENTATION \"Given a system definition `system' try to determine the root directory\nof the STELLA installation containing this system based on its definition file.\" :PUBLIC? TRUE)", ((cpp_function_code)(&findSystemRootDirectory)), NULL);
    defineFunctionObject("COMPUTE-SYSTEM-ROOT-DIRECTORIES", "(DEFUN COMPUTE-SYSTEM-ROOT-DIRECTORIES ((SYSTEM SYSTEM-DEFINITION)) :DOCUMENTATION \"Compute any root directories for sources, native and Lisp binary directories\nin case they were not explicitly specified in `system's definition.  Raises an error in case\nany of those root directories is missing and can't be computed.\" :PUBLIC? TRUE)", ((cpp_function_code)(&computeSystemRootDirectories)), NULL);
    defineFunctionObject("PARSE-LIST-OF-FILE-PATHS", "(DEFUN (PARSE-LIST-OF-FILE-PATHS (CONS OF STRING-WRAPPER)) ((FILES CONS)))", ((cpp_function_code)(&parseListOfFilePaths)), NULL);
    defineFunctionObject("DEFINE-SYSTEM", "(DEFUN (DEFINE-SYSTEM SYSTEM-DEFINITION) ((NAME OBJECT) (OPTIONS CONS)))", ((cpp_function_code)(&defineSystem)), NULL);
    defineFunctionObject("DEFSYSTEM", "(DEFUN (DEFSYSTEM SYSTEM-DEFINITION) ((NAME SYMBOL) |&REST| (OPTIONS OBJECT)) :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :PUBLIC? TRUE :DOCUMENTATION \"Define a system of files that collectively define\na Stella application.\n   Required options are:\n   :directory -- the relative path from the respective source/native/binary root directory\n                 to the directory containing the system files.  Can be a string or a list\n                 of strings (do not include directory separators).\n   :files -- a list of files in the system, containing strings and lists\n             of strings; the latter defines exploded paths to files\n             in subdirectories.\n   Optional options are:\n   :data-files       -- a list of files like the :files keyword, which contain\n                        data or other content that should not be processed, but\n                        instead copied verbatim to the native directory\n   :required-systems -- a list of systems (strings) that should be loaded\n          " "              prior to loading this system.\n   :cardinal-module -- the name (a string) of the principal module for this\n                       system.\n   :copyright-header -- string with a header for inclusion into all translated\n                        files produced by Stella.\n   :lisp-only-files  -- Like the :files keyword, but these are only included\n   :cpp-only-files      in the translation for the specific language, namely\n   :java-only-files     Common Lisp, C++ or Java\")", ((cpp_function_code)(&defsystem)), ((cpp_function_code)(&defsystemEvaluatorWrapper)));
    defineFunctionObject("GET-SYSTEM-DEFINITION", "(DEFUN (GET-SYSTEM-DEFINITION SYSTEM-DEFINITION) ((NAME STRING) (ERROR? BOOLEAN)) :DOCUMENTATION \"Return a system named 'name'.  If no such system is currently defined,\nlook for a system definition file for `name' in standard locations and try to load it.\nIf no matching system could be found or loaded and `error?' is true, raise an error,\notherwise, simply return NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getSystemDefinition)), NULL);
    defineFunctionObject("GET-CARDINAL-MODULE", "(DEFUN (GET-CARDINAL-MODULE MODULE) ((SYSTEM SYSTEM-DEFINITION)))", ((cpp_function_code)(&getCardinalModule)), NULL);
    defineFunctionObject("HELP-GET-SYSTEM-FILES", "(DEFUN HELP-GET-SYSTEM-FILES ((FILENAME FILE-NAME) (COLLECTION LIST) (PROBEFILE? BOOLEAN)))", ((cpp_function_code)(&helpGetSystemFiles)), NULL);
    defineFunctionObject("GET-SYSTEM-FILES", "(DEFUN (GET-SYSTEM-FILES (LIST OF STRING-WRAPPER)) ((SYSTEM SYSTEM-DEFINITION) (TYPE KEYWORD) (PROBEFILES? BOOLEAN)))", ((cpp_function_code)(&getSystemFiles)), NULL);
    defineFunctionObject("CLEAN-SYSTEM", "(DEFUN CLEAN-SYSTEM ((SYSTEMNAME STRING)))", ((cpp_function_code)(&cleanSystem)), NULL);
    defineFunctionObject("COMPUTE-OPTIMIZATION-LEVELS", "(DEFUN COMPUTE-OPTIMIZATION-LEVELS ((SYSTEM SYSTEM-DEFINITION) (PRODUCTIONMODE? BOOLEAN)))", ((cpp_function_code)(&computeOptimizationLevels)), NULL);
    defineFunctionObject("MAKE-SYSTEM", "(DEFUN (MAKE-SYSTEM BOOLEAN) ((SYSTEMNAME STRING) |&REST| (|LANGUAGE&OPTIONS| OBJECT)) :DOCUMENTATION \"Translate all out-of-date files of system `systemName'\ninto `language' (the first optional argument of `language&options') and\nthen compile and load them (the latter is only possible for Lisp right now).\nThe following keyword/value `options' are recognized:\n\n`:language': can be used as an alternative to the optional language argument.\nIf not specified, the language of the running implementation is assumed.\n\n`:two-pass?': if true, all files will be scanned twice, once to\nload the signatures of objects defined in them, and once to actually\ntranslate the definitions.  Otherwise, the translator will make one pass in\nthe case that the system is already loaded (and is being remade), and two\npasses otherwise.\n\n`:development-settings?' (default false): if true translation will favor\nsafe, readable and debuggable code over efficiency (according to the value\nof `:development-settings' on the system d" "efinition).  If false, efficiency\nwill be favored instead (according to the value of `:production-settings'\non the system definition).\n\n`:production-settings?' (default true): inverse to `:development-settings?'.\n\n`:force-translation?' (default false): if true, files will be translated\nwhether or not their translations are up-to-date.\n\n`:force-recompilation?' (default false): if true, translated files will be\nrecompiled whether or not their compilations are up-to-date (only supported\nin Lisp right now).\n\n`:load-system?' (default true): if true, compiled files will be loaded into\nthe current STELLA image (only supported in Lisp and Java right now).\n\n`:startup?' (default true): if true, the system startup function will\nbe called once all files have been loaded.\n\n`:recursive?' (default false): if true, perform `make-system' with the provided\noptions on `systemName' as well as all its required systems and so on.  Required\nsystems will be processed first.  Note that even without this option, " "any required\nsystems that have not yet been loaded or started up will also be processed, since\nthat is assumed when loading `systemName' and supporting modules from a definition file.\n\n`:root-source-directory', `:root-native-directory', `:root-binary-directory': if\nspecified these directories will be used to override the respective paths provided\nin system definitions or computed as defaults from a system's home location.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&makeSystem)), ((cpp_function_code)(&makeSystemEvaluatorWrapper)));
    defineFunctionObject("RUN-SYSTEM-FINALIZATION", "(DEFUN RUN-SYSTEM-FINALIZATION ((SYSTEM SYSTEM-DEFINITION)))", ((cpp_function_code)(&runSystemFinalization)), NULL);
    defineFunctionObject("SYSTEM-DEFINITION-SOURCE-FILES", "(DEFUN (SYSTEM-DEFINITION-SOURCE-FILES (CONS OF STRING-WRAPPER)) ((SYSTEM SYSTEM-DEFINITION)))", ((cpp_function_code)(&systemDefinitionSourceFiles)), NULL);
    defineFunctionObject("FILES-PLUS-SYSTEM-STARTUP", "(DEFUN (FILES-PLUS-SYSTEM-STARTUP (CONS OF STRING-WRAPPER)) ((FILES (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&filesPlusSystemStartup)), NULL);
    defineFunctionObject("SYSTEM-DEFINITION-NATIVE-FILES", "(DEFUN (SYSTEM-DEFINITION-NATIVE-FILES (CONS OF STRING-WRAPPER)) ((SYSTEM SYSTEM-DEFINITION)))", ((cpp_function_code)(&systemDefinitionNativeFiles)), NULL);
    defineFunctionObject("SYSTEM-LOADED?", "(DEFUN (SYSTEM-LOADED? BOOLEAN) ((NAME STRING)) :DOCUMENTATION \"Return `true' if system `name' has been loaded.\" :PUBLIC? TRUE)", ((cpp_function_code)(&systemLoadedP)), NULL);
    defineFunctionObject("SYSTEM-LOADED-OR-STARTED-UP?", "(DEFUN (SYSTEM-LOADED-OR-STARTED-UP? BOOLEAN) ((NAME STRING)) :DOCUMENTATION \"Return `true' if system `name' has either been loaded\nor initialized with its startup function.\" :PUBLIC? TRUE)", ((cpp_function_code)(&systemLoadedOrStartedUpP)), NULL);
    defineFunctionObject("CLEAR-SYSTEM", "(DEFUN CLEAR-SYSTEM ((NAME STRING)) :DOCUMENTATION \"Clears out the system definition named `name'.  If\n`name' is `null', then clear out all system definitions.  This function\nis useful when changes have been made to the system definition, and one\nwants to have it reloaded from the standard location in the file system.\" :PUBLIC? TRUE)", ((cpp_function_code)(&clearSystem)), NULL);
    defineFunctionObject("LOAD-PREPROCESSED-FILES", "(DEFUN LOAD-PREPROCESSED-FILES ((SYSTEMNAME STRING)))", ((cpp_function_code)(&loadPreprocessedFiles)), NULL);
    defineFunctionObject("LOAD-SYSTEM", "(DEFUN (LOAD-SYSTEM BOOLEAN) ((SYSTEMNAME STRING) |&REST| (|LANGUAGE&OPTIONS| OBJECT)) :DOCUMENTATION \"Natively `language'-compile out-of-date translated files of system\n`systemName' (only supported for Lisp at the moment) and then load them\ninto the running system.  Return true if at least one file was compiled.\nThe following keyword/value `options' are recognized:\n\n`:language': can be used as an alternative to the optional language argument.\nIf not specified, the language of the running implementation is assumed.\n\n`:force-recompilation?' (default false): if true, files will be compiled\nwhether or not their compilations are up-to-date.\n\n`:startup?' (default true): if true, the system startup function will\nbe called once all files have been loaded.\n\n`:recursive?' (default false): if true, perform `load-system' with the provided\noptions on `systemName' as well as all its required systems and so on.  Required\nsystems will be processed first.  Note that even without this option, any required\ns" "ystems that have not yet been loaded or started up will also be processed, since\nthat is assumed when loading `systemName' and supporting modules from a definition file.\n\n`:root-source-directory', `:root-native-directory', `:root-binary-directory': if\nspecified these directories will be used to override the respective paths provided\nin system definitions or computed as defaults from a system's home location.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&loadSystem)), ((cpp_function_code)(&loadSystemEvaluatorWrapper)));
    defineFunctionObject("COMPILE-AND-LOAD-FILES", "(DEFUN (COMPILE-AND-LOAD-FILES BOOLEAN) ((FILES (CONS OF STRING-WRAPPER)) (LANGUAGE KEYWORD) (FORCERECOMPILATION? BOOLEAN)))", ((cpp_function_code)(&compileAndLoadFiles)), NULL);
    defineFunctionObject("RUN-SYSTEM-STARTUP-FUNCTION", "(DEFUN RUN-SYSTEM-STARTUP-FUNCTION ((SYSTEM SYSTEM-DEFINITION)))", ((cpp_function_code)(&runSystemStartupFunction)), NULL);
    defineMethodObject("(DEFMETHOD (SYSTEM-STARTUP-FUNCTION-NAME STRING) ((SYSTEM SYSTEM-DEFINITION)))", wrapMethodCode(((cpp_method_code)(&SystemDefinition::systemStartupFunctionName))), NULL);
    defineMethodObject("(DEFMETHOD (SYSTEM-STARTUP-FUNCTION-NAME STRING) ((SYSTEMNAME STRING)))", wrapFunctionCode(((cpp_function_code)(((const char*  (*) (const char*))(&stringSystemStartupFunctionName))))), NULL);
    defineFunctionObject("SYSTEM-STARTUP-FUNCTION-SYMBOL", "(DEFUN (SYSTEM-STARTUP-FUNCTION-SYMBOL SYMBOL) ((SYSTEM SYSTEM-DEFINITION)))", ((cpp_function_code)(&systemStartupFunctionSymbol)), NULL);
    defineFunctionObject("STARTUP-NAME-FROM-FILE", "(DEFUN (STARTUP-NAME-FROM-FILE SYMBOL) ((FILE FILE-NAME)))", ((cpp_function_code)(&startupNameFromFile)), NULL);
    defineFunctionObject("STARTUP-NAMES-FROM-FILES", "(DEFUN (STARTUP-NAMES-FROM-FILES (CONS OF SYMBOL)) ((FILES (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&startupNamesFromFiles)), NULL);
    defineFunctionObject("SYSTEM-STARTUP-FILE-NAME", "(DEFUN (SYSTEM-STARTUP-FILE-NAME STRING) ((SYSTEM SYSTEM-DEFINITION)))", ((cpp_function_code)(&systemStartupFileName)), NULL);
    defineFunctionObject("SYSTEM-STARTUP-FILE?", "(DEFUN (SYSTEM-STARTUP-FILE? BOOLEAN) ((FILE FILE-NAME)))", ((cpp_function_code)(&systemStartupFileP)), NULL);
    defineFunctionObject("SYSTEM-STARTED-UP?", "(DEFUN (SYSTEM-STARTED-UP? BOOLEAN) ((SYSTEMNAME STRING) (SYSTEMMODULENAME STRING)))", ((cpp_function_code)(&systemStartedUpP)), NULL);
    defineFunctionObject("YIELD-STARTUP-REQUIRED-SYSTEMS", "(DEFUN (YIELD-STARTUP-REQUIRED-SYSTEMS CONS) ((SYSTEM SYSTEM-DEFINITION)))", ((cpp_function_code)(&yieldStartupRequiredSystems)), NULL);
    defineFunctionObject("COLLECT-STARTUP-FORMS-FROM-SYSTEM-FILE", "(DEFUN (COLLECT-STARTUP-FORMS-FROM-SYSTEM-FILE (CONS OF CONS)) ((SYSTEM SYSTEM-DEFINITION)))", ((cpp_function_code)(&collectStartupFormsFromSystemFile)), NULL);
    defineFunctionObject("COLLECT-DEFINED-MODULES-FROM-SYSTEM-FILE", "(DEFUN (COLLECT-DEFINED-MODULES-FROM-SYSTEM-FILE (CONS OF MODULE)) ((SYSTEM SYSTEM-DEFINITION)))", ((cpp_function_code)(&collectDefinedModulesFromSystemFile)), NULL);
    defineFunctionObject("CREATE-SYSTEM-STARTUP-FILE", "(DEFUN CREATE-SYSTEM-STARTUP-FILE ((SYSTEM SYSTEM-DEFINITION)))", ((cpp_function_code)(&createSystemStartupFile)), NULL);
    defineFunctionObject("HELP-ALL-REQUIRED-SYSTEMS", "(DEFUN (HELP-ALL-REQUIRED-SYSTEMS (LIST OF STRING-WRAPPER)) ((SYSTEM-NAME STRING) (FOUND (LIST OF STRING-WRAPPER))))", ((cpp_function_code)(&helpAllRequiredSystems)), NULL);
  }
}

void helpStartupSystems6() {
  {
    defineFunctionObject("ALL-REQUIRED-SYSTEMS", "(DEFUN (ALL-REQUIRED-SYSTEMS (CONS OF STRING-WRAPPER)) ((SYSTEM-NAME STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Returns a CONS of all of the systems required by `system-name'\")", ((cpp_function_code)(&allRequiredSystems)), NULL);
    defineFunctionObject("DATE-TO-VERSION-STRING", "(DEFUN (DATE-TO-VERSION-STRING STRING) ((DATE CALENDAR-DATE) (GRANULARITY KEYWORD)) :DOCUMENTATION \"Transform `date' into a version string according to `granularity'\nwhich is at least :days and defaults to :seconds.\" :PUBLIC? TRUE)", ((cpp_function_code)(&dateToVersionString)), NULL);
    defineFunctionObject("GET-SYSTEM-LAST-MODIFIED-DATE", "(DEFUN (GET-SYSTEM-LAST-MODIFIED-DATE CALENDAR-DATE) ((SYSTEM SYSTEM-DEFINITION)) :DOCUMENTATION \"Compute a last-modified date for `system' based on its most recently modified source file.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getSystemLastModifiedDate)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT SYSTEM-DEFINITION SYSTEM-VERSION :TYPE STRING :OPTION-KEYWORD :VERSION :DOCUMENTATION \"Explicitly define a version number for this system.\" :ALLOCATION :DYNAMIC)");
    defineFunctionObject("GET-SYSTEM-VERSION-STRING", "(DEFUN (GET-SYSTEM-VERSION-STRING STRING) ((SYSTEM SYSTEM-DEFINITION)) :DOCUMENTATION \"Compute a version string for `system' which is either based on an explicit :version\nannotation on `system's definition, the readable value of an existing `*<system>-version[-string]*',\nvariable or on its most recent modification date of any of its source files.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getSystemVersionString)), NULL);
    defineFunctionObject("AUTOLOAD", "(DEFUN (AUTOLOAD FUNCTION-CODE) ((QUALIFIEDNAME STRING) (SYSTEMNAME STRING) (CACHE SURROGATE) (ERROR? BOOLEAN)) :DOCUMENTATION \"Autoload function `qualifiedName' from system `systemName'.\nIf it is already present in the system, simply return its code.  If `cache'\nis defined, return its value if defined, otherwise, set its value to the\nfunction found.  If the function failed to be defined by loading `systemName'\nand `error?' is true, raise an error.  Otherwise, simply return NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&autoload)), NULL);
    defineFunctionObject("MAKE-STELLA", "(DEFUN MAKE-STELLA ((FORCERECOMPILATION? BOOLEAN)))", ((cpp_function_code)(&makeStella)), NULL);
    defineFunctionObject("PARSE-CONFIGURATION-FILE-LINE", "(DEFUN (PARSE-CONFIGURATION-FILE-LINE STRING-WRAPPER WRAPPER KEYWORD) ((LINE STRING)))", ((cpp_function_code)(&parseConfigurationFileLine)), NULL);
    defineFunctionObject("LOAD-CONFIGURATION-FILE", "(DEFUN (LOAD-CONFIGURATION-FILE CONFIGURATION-TABLE) ((FILE FILE-NAME)) :DOCUMENTATION \"Read a configuration `file' and return its content as a configuration table.\nAlso enter each property read into the global system configuration table.\nAssumes Java-style property file syntax.  Each property name is represented\nas a wrapped string and each value as a wrapped string/integer/float or boolean.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&loadConfigurationFile)), ((cpp_function_code)(&loadConfigurationFileEvaluatorWrapper)));
    defineFunctionObject("SAVE-CONFIGURATION-VALUE", "(DEFUN SAVE-CONFIGURATION-VALUE ((STREAM OUTPUT-STREAM) (VALUE OBJECT)) :DOCUMENTATION \"Save `value' to `stream' as a properly formatted configuration\nvalue.\")", ((cpp_function_code)(&saveConfigurationValue)), NULL);
    defineFunctionObject("SAVE-CONFIGURATION-FILE", "(DEFUN SAVE-CONFIGURATION-FILE ((TABLE CONFIGURATION-TABLE) (FILE FILE-NAME) (TITLE STRING)) :DOCUMENTATION \"Save `table' as a configuration file.  Uses a Java-style property file syntax.\" :PUBLIC? TRUE)", ((cpp_function_code)(&saveConfigurationFile)), NULL);
    defineFunctionObject("LOOKUP-CONFIGURATION-PROPERTY", "(DEFUN (LOOKUP-CONFIGURATION-PROPERTY OBJECT) ((PROPERTY STRING) (DEFAULTVALUE OBJECT) (CONFIGURATION CONFIGURATION-TABLE)) :DOCUMENTATION \"Lookup `property' in `configuration' and return its value.\nUse the global system configuration table if `configuration' is NULL.  Return\n`defaultValue' if `property' is not defined.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupConfigurationProperty)), NULL);
    defineFunctionObject("LOOKUP-CONFIGURATION-PROPERTY-VALUES", "(DEFUN (LOOKUP-CONFIGURATION-PROPERTY-VALUES CONS) ((PROPERTY STRING) (DEFAULTVALUE OBJECT) (CONFIGURATION CONFIGURATION-TABLE)) :DOCUMENTATION \"Lookup `property' in `configuration', assume it is a multi-valued\nproperty and return its value(s) as a list.  Use the global system configuration table\nif `configuration' is NULL.  Return `defaultValue' if `property' is not defined or\nNIL is no default value is specified.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupConfigurationPropertyValues)), NULL);
    defineFunctionObject("SET-CONFIGURATION-PROPERTY", "(DEFUN (SET-CONFIGURATION-PROPERTY OBJECT) ((PROPERTY STRING) (VALUE OBJECT) (CONFIGURATION CONFIGURATION-TABLE)) :DOCUMENTATION \"Set `property' in `configuration' to `value' and return it.\nUse the global system configuration table if `configuration' is NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&setConfigurationProperty)), NULL);
    defineFunctionObject("ADD-CONFIGURATION-PROPERTY", "(DEFUN (ADD-CONFIGURATION-PROPERTY OBJECT) ((PROPERTY STRING) (VALUE OBJECT) (CONFIGURATION CONFIGURATION-TABLE)) :DOCUMENTATION \"Add `value' to `property' in `configuration' and return it.\nIf a previous value exists add `value' to the end (listify the old value\nif it is not yet a list).  Otherwise, create a new list containing `value'.\nUse the global system configuration table if `configuration' is NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&addConfigurationProperty)), NULL);
    defineFunctionObject("CLEAR-CONFIGURATION-PROPERTY", "(DEFUN (CLEAR-CONFIGURATION-PROPERTY OBJECT) ((PROPERTY STRING) (CONFIGURATION CONFIGURATION-TABLE)) :DOCUMENTATION \"Remove `property' in `configuration' and return the previous\nvalue.\nUse the global system configuration table if `configuration' is NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&clearConfigurationProperty)), NULL);
    defineFunctionObject("REMOVE-CONFIGURATION-PROPERTY", "(DEFUN (REMOVE-CONFIGURATION-PROPERTY OBJECT) ((PROPERTY STRING) (VALUE OBJECT) (CONFIGURATION CONFIGURATION-TABLE)) :DOCUMENTATION \"Remove `value' from `property' in `configuration' and return it.\nUse the global system configuration table if `configuration' is NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&removeConfigurationProperty)), NULL);
    defineFunctionObject("PRINT-CONFIGURATION-PROPERTIES", "(DEFUN PRINT-CONFIGURATION-PROPERTIES ((CONFIGURATION CONFIGURATION-TABLE) (STREAM OUTPUT-STREAM)) :DOCUMENTATION \"Print all properties defined in `configuration' to `stream'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&printConfigurationProperties)), NULL);
    defineFunctionObject("*PL-ROOT-DIRECTORY*-SETTER", "(DEFUN (*PL-ROOT-DIRECTORY*-SETTER STRING) ((VALUE STRING)))", ((cpp_function_code)(&OPlRootDirectoryOSetter)), NULL);
    defineFunctionObject("CONFIGURE-STELLA", "(DEFUN CONFIGURE-STELLA ((FILE FILE-NAME)) :DOCUMENTATION \"Perform STELLA run-time configuration.  If supplied, load the\nconfiguration file `file' first which should be supplied with a physical pathname.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&configureStella)), ((cpp_function_code)(&configureStellaEvaluatorWrapper)));
    defineFunctionObject("GET-PROPERTY", "(DEFUN (GET-PROPERTY OBJECT) ((PROPERTY NAME) |&REST| (DEFAULTVALUE OBJECT)) :DOCUMENTATION \"Lookup `property' (a string or symbol) in the configuration\ntable and return its value.  If it is undefined, return the optional `defaultValue'.\nNote that `property' is evaluated and will need to be quoted if supplied as a\nsymbol.  Symbols will also be upcased if this command is run in a non-case-\nsensitive module.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&getProperty)), ((cpp_function_code)(&getPropertyEvaluatorWrapper)));
    defineFunctionObject("SET-PROPERTY", "(DEFUN SET-PROPERTY ((PROPERTY NAME) (VALUE OBJECT)) :DOCUMENTATION \"Set `property' (a string or symbol) in the configuration\ntable to `value'.  Note that `property' is evaluated and will need to be quoted\nif supplied as a symbol.  Symbols will also be upcased if this command is run in\na non-case-sensitive module.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&setProperty)), NULL);
    defineFunctionObject("ADD-PROPERTY-VALUE", "(DEFUN ADD-PROPERTY-VALUE ((PROPERTY NAME) (VALUE OBJECT)) :DOCUMENTATION \"Add `value' to the end of `property's (a string or symbol) value\nlist in the configuration table.  Coerces the current value to a list or initializes\nthe list if it is as yet undefined.  Allows incremental addition of values to\nlist-valued propertys.  Note that `property' is evaluated and will need to be quoted\nif supplied as a symbol.  Symbols will also be upcased if this command is run in a\nnon-case-sensitive module.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&addPropertyValue)), NULL);
    defineFunctionObject("PRINT-PROPERTIES", "(DEFUN PRINT-PROPERTIES () :DOCUMENTATION \"Print all current configuration property information to\nstandard output.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&printProperties)), NULL);
    defineFunctionObject("REGISTER-PROPERTY-DEMON", "(DEFUN REGISTER-PROPERTY-DEMON ((PROPERTY STRING) (DEMONNAME SYMBOL)) :DOCUMENTATION \"Register the function named `demonName' as the demon for `property'.\nDemons will be run as after demons on every configuration table update.  Set the\nproperty `stella.test.propertyDemon' to see a test demon in action.\" :PUBLIC? TRUE)", ((cpp_function_code)(&registerPropertyDemon)), NULL);
    defineFunctionObject("UNREGISTER-PROPERTY-DEMON", "(DEFUN UNREGISTER-PROPERTY-DEMON ((PROPERTY STRING)) :DOCUMENTATION \"Unregister any demon for `property'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unregisterPropertyDemon)), NULL);
    defineFunctionObject("LOOKUP-VARIABLE-DEMON-SETTER", "(DEFUN (LOOKUP-VARIABLE-DEMON-SETTER METHOD-SLOT) ((DEMON GLOBAL-VARIABLE)))", ((cpp_function_code)(&lookupVariableDemonSetter)), NULL);
    defineFunctionObject("RUN-CONFIGURATION-PROPERTY-DEMON", "(DEFUN RUN-CONFIGURATION-PROPERTY-DEMON ((ACTION KEYWORD) (PROPERTY STRING) (VALUE OBJECT) (TABLE CONFIGURATION-TABLE)))", ((cpp_function_code)(&runConfigurationPropertyDemon)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT METHOD-SLOT DEMON-PROPERTY :TYPE STRING :OPTION-KEYWORD :DEMON-PROPERTY :OPTION-HANDLER DEMON-PROPERTY-HANDLER :DOCUMENTATION \"Holds the property monitored by a demon function.  This slot is primarily used\nto allow us the use of the :demon-property option handler for demon registration.\" :ALLOCATION :DYNAMIC)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT GLOBAL-VARIABLE DEMON-PROPERTY :TYPE STRING :OPTION-KEYWORD :DEMON-PROPERTY :OPTION-HANDLER DEMON-PROPERTY-HANDLER :DOCUMENTATION \"Holds the property monitored by a demon for this variable.  This slot is\nprimarily used to allow us the use of the :demon-property option handler for demon registration.\" :ALLOCATION :DYNAMIC)");
    defineFunctionObject("DEMON-PROPERTY-HANDLER", "(DEFUN DEMON-PROPERTY-HANDLER ((DEMON MAPPABLE-OBJECT) (SLOT STORAGE-SLOT) (PROPERTY OBJECT)))", ((cpp_function_code)(&demonPropertyHandler)), NULL);
    defineFunctionObject("TEST-PROPERTY-DEMON", "(DEFUN TEST-PROPERTY-DEMON ((ACTION KEYWORD) (PROPERTY STRING) (VALUE OBJECT) (TABLE CONFIGURATION-TABLE)) :DOCUMENTATION \"A test demon for the property demon machinery which simply prints arguments.\" :PUBLIC? TRUE)", ((cpp_function_code)(&testPropertyDemon)), NULL);
    defineFunctionObject("REGISTER-CMD-LINE-OPTION", "(DEFUN REGISTER-CMD-LINE-OPTION (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Register a command line option.  :key identifies the name of the option which\nwill usually start with a dash such as `-e' or `--eval'.  :key2 and :key3 can be used to supply\nadditional options (e.g., long option formats).  To supply even more keys, a list can be supplied\nwith the :keys option.  If a :property is supplied, this option simply sets or adds to the values\nof the specified system configuration property.  If a :handler name is specified, its function\nwill be used to interpret the values of the option.  :documentation can be used to supply a\ndocumentation string which will be printed by the `help-option-handler' (usually bound to `-?').\n:value-type describes what type an option value should be coerced to before assigning it to the\nspecified configuration :property.  :n-arguments describes how many arguments this option\ntakes.  This will be 0 for simple switches and can be 1 or greater than one for option handlers\nt" "hat need one or more arguments.  :default-value defines the value to use for zero-argument\n:property options.  If :multi-valued? is true, values of multiple occurrences of the option will be\nadded to the specified configuration :property.  :error-action can be one of :ignore, :warn or\n:error to specify what to do in case an error is encountered during option processing.\" :PUBLIC? TRUE)", ((cpp_function_code)(&registerCmdLineOption)), NULL);
    defineFunctionObject("UNREGISTER-CMD-LINE-OPTION", "(DEFUN UNREGISTER-CMD-LINE-OPTION ((KEY STRING)) :DOCUMENTATION \"Unregister the command line option identified by `key' under all its keys.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unregisterCmdLineOption)), NULL);
    defineFunctionObject("UNREGISTER-ALL-CMD-LINE-OPTIONS", "(DEFUN UNREGISTER-ALL-CMD-LINE-OPTIONS () :DOCUMENTATION \"Unregister all currently registered command line options.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unregisterAllCmdLineOptions)), NULL);
    defineFunctionObject("DEFAULT-CMD-LINE-OPTION-HANDLER", "(DEFUN DEFAULT-CMD-LINE-OPTION-HANDLER ((OPTION CMD-LINE-OPTION) (VALUE OBJECT)) :DOCUMENTATION \"Default handler that tries to set a system property based on `option' and `value'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&defaultCmdLineOptionHandler)), NULL);
    defineFunctionObject("PROCESS-COMMAND-LINE-ARGUMENTS", "(DEFUN PROCESS-COMMAND-LINE-ARGUMENTS ((COUNT INTEGER) (ARGUMENTS (ARRAY () OF STRING)) (UNHANDLEDOPTIONACTION KEYWORD)) :DOCUMENTATION \"Interpret any command line `arguments' for which handlers have been registered.\nLeave any remaining unprocessed arguments in `*unprocessed-command-line-arguments*'.\nIf any unprocessed arguments use option syntax (that is they start with a `-'), proceed\naccording to `unhandledOptionAction' which can be one of :ignore, :warn or :error.\nThis ensures that at any point in the option processing, `*unprocessed-command-line-arguments*'\naccurately reflects the arguments which have been either skipped or not handled yet.\" :PUBLIC? TRUE)", ((cpp_function_code)(&processCommandLineArguments)), NULL);
    defineFunctionObject("UNPROCESSED-COMMAND-LINE-ARGUMENTS", "(DEFUN (UNPROCESSED-COMMAND-LINE-ARGUMENTS (CONS OF STRING-WRAPPER)) () :DOCUMENTATION \"Return all command line arguments which have not yet been processed\nby (or been ignored by) `process-command-line-arguments'.  If arguments have not yet\nbeen processed, this will return NULL.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&unprocessedCommandLineArguments)), NULL);
    defineFunctionObject("EVAL-OPTION-HANDLER", "(DEFUN EVAL-OPTION-HANDLER ((OPTION CMD-LINE-OPTION) (VALUE OBJECT)) :DOCUMENTATION \"Interpret an --eval option by evaluating `value'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&evalOptionHandler)), NULL);
    defineFunctionObject("EVAL-IN-MODULE-OPTION-HANDLER", "(DEFUN EVAL-IN-MODULE-OPTION-HANDLER ((OPTION CMD-LINE-OPTION) (VALUE OBJECT)) :DOCUMENTATION \"Interpret an --eval-in-module option.  `value' is expected\nto be of the form `(<module-name> <s-expression>)'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&evalInModuleOptionHandler)), NULL);
    defineFunctionObject("LOAD-PATH-OPTION-HANDLER", "(DEFUN LOAD-PATH-OPTION-HANDLER ((OPTION CMD-LINE-OPTION) (VALUE OBJECT)) :DOCUMENTATION \"Modify the current file load path according to `option' and `value'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&loadPathOptionHandler)), NULL);
    defineFunctionObject("CONFIG-FILE-OPTION-HANDLER", "(DEFUN CONFIG-FILE-OPTION-HANDLER ((OPTION CMD-LINE-OPTION) (VALUE OBJECT)) :DOCUMENTATION \"Load the configuration file `value'.  This will\nmodify currently set system properties defined in `value' with new\nvalues but leave all other currently set properties as they are.\" :PUBLIC? TRUE)", ((cpp_function_code)(&configFileOptionHandler)), NULL);
    defineFunctionObject("LOAD-FILE-OPTION-HANDLER", "(DEFUN LOAD-FILE-OPTION-HANDLER ((OPTION CMD-LINE-OPTION) (VALUE OBJECT)) :DOCUMENTATION \"Load the file `value' using the STELLA `load-file' command.\" :PUBLIC? TRUE)", ((cpp_function_code)(&loadFileOptionHandler)), NULL);
    defineFunctionObject("DEFINE-PROPERTY-OPTION-HANDLER", "(DEFUN DEFINE-PROPERTY-OPTION-HANDLER ((OPTION CMD-LINE-OPTION) (VALUE OBJECT)))", ((cpp_function_code)(&definePropertyOptionHandler)), NULL);
    defineFunctionObject("HELP-OPTION-HANDLER", "(DEFUN HELP-OPTION-HANDLER ((OPTION CMD-LINE-OPTION) (VALUE OBJECT)) :DOCUMENTATION \"Print documentation about all currently registered option handlers.\" :PUBLIC? TRUE)", ((cpp_function_code)(&helpOptionHandler)), NULL);
    defineFunctionObject("STARTUP-SYSTEMS", "(DEFUN STARTUP-SYSTEMS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupSystems)), NULL);
    { MethodSlot* function = lookupFunction(SYM_SYSTEMS_STELLA_STARTUP_SYSTEMS);

      setDynamicSlotValue(function->dynamicSlots, SYM_SYSTEMS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupSystems"), NULL_STRING_WRAPPER);
    }
  }
}

void startupSystems() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupSystems1();
      helpStartupSystems2();
      helpStartupSystems3();
    }
    if (currentStartupTimePhaseP(4)) {
      helpStartupSystems4();
    }
    if (currentStartupTimePhaseP(5)) {
      defineStellaTypeFromStringifiedSource("(DEFTYPE CONFIGURATION-TABLE (KEY-VALUE-LIST OF STRING-WRAPPER OBJECT))");
      { Class* clasS = defineClassFromStringifiedSource("CMD-LINE-OPTION", "(DEFCLASS CMD-LINE-OPTION (STANDARD-OBJECT) :SLOTS ((DOCUMENTATION :TYPE STRING :INITIALLY \"Not documented.\") (KEYS :TYPE (CONS OF STRING-WRAPPER) :INITIALLY NIL) (VALUE-TYPE :TYPE TYPE :INITIALLY @STRING) (MULTI-VALUED? :TYPE BOOLEAN :INITIALLY FALSE) (N-ARGUMENTS :TYPE INTEGER :INITIALLY 0 :DOCUMENTATION \"The number of args expected by this option.\nCommon values are 0 or 1, but certain options might take more than one argument.\") (DEFAULT-VALUE :TYPE OBJECT :DOCUMENTATION \"The value to use for 0-arg options.\nDefaults to TRUE for 0-arg options with boolean value type.\") (CONFIGURATION-PROPERTY :TYPE STRING) (HANDLER :TYPE FUNCTION-CODE :INITIALLY (THE-CODE :FUNCTION DEFAULT-CMD-LINE-OPTION-HANDLER)) (ERROR-ACTION :TYPE KEYWORD :INITIALLY :ERROR :DOCUMENTATION \"One of :ignore, :warn, :error.\")))");

        clasS->classConstructorCode = ((cpp_function_code)(&newCmdLineOption));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessCmdLineOptionSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupSystems5();
      helpStartupSystems6();
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *FILE-LOAD-PATH* (CONS OF STRING-WRAPPER) NIL)", &oFILE_LOAD_PATHo);
      defineGlobalVariableObject("(DEFGLOBAL *STELLA-FILE-EXTENSIONS* CONS (CONS-LIST \".ste\") :DOCUMENTATION \"File extensions to append by default when a\nfile is looked up by `find-file-in-load-path'.\" :PUBLIC? TRUE)", &oSTELLA_FILE_EXTENSIONSo);
      defineGlobalVariableObject("(DEFSPECIAL *CURRENTLOADFILE* STRING NULL :DOCUMENTATION \"Full pathname of file that is currently being loaded (or similar).\" :PUBLIC? TRUE)", &oCURRENTLOADFILEo);
      defineGlobalVariableObject("(DEFGLOBAL *SYSTEMDEFINITIONS* (LIST OF SYSTEM-DEFINITION) (NEW LIST) :DOCUMENTATION \"A list of all defined systems.\")", &oSYSTEMDEFINITIONSo);
      defineGlobalVariableObject("(DEFSPECIAL *CURRENT-SYSTEM-ACTION* PROPERTY-LIST NULL :DOCUMENTATION \"Holds the action and options of the current system action\nsuch as :make-system, :load-system or :translate-system.  This is used to\nperform the appropriate actions on required systems in `define-system'.\")", &oCURRENT_SYSTEM_ACTIONo);
      defineGlobalVariableObject("(DEFGLOBAL *SYSTEM-CONFIGURATION-TABLE* CONFIGURATION-TABLE (NEW CONFIGURATION-TABLE))", &oSYSTEM_CONFIGURATION_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *PL-ROOT-DIRECTORY* STRING NULL :DOCUMENTATION \"The :root-directory portion of the PL logical host.  This variable\nis primarily defined to allow us to dynamically change this via a configuration demon.\" :DEMON-PROPERTY \"stella.plRootDirectory\" :PUBLIC? TRUE)", &oPL_ROOT_DIRECTORYo);
      defineGlobalVariableObject("(DEFGLOBAL *REGISTERED-PROPERTY-DEMONS* (KEY-VALUE-MAP OF STRING-WRAPPER MAPPABLE-OBJECT) (NEW KEY-VALUE-MAP))", &oREGISTERED_PROPERTY_DEMONSo);
      registerPropertyDemon("stella.test.propertyDemon", SYM_SYSTEMS_STELLA_TEST_PROPERTY_DEMON);
      defineGlobalVariableObject("(DEFGLOBAL *REGISTERED-COMMAND-LINE-OPTIONS* (KEY-VALUE-MAP OF STRING-WRAPPER CMD-LINE-OPTION) (NEW KEY-VALUE-MAP))", &oREGISTERED_COMMAND_LINE_OPTIONSo);
      defineGlobalVariableObject("(DEFGLOBAL *UNPROCESSED-COMMAND-LINE-ARGUMENTS* (CONS OF STRING-WRAPPER) NULL)", &oUNPROCESSED_COMMAND_LINE_ARGUMENTSo);
      registerCmdLineOption(14, KWD_SYSTEMS_KEY, wrapString("-e"), KWD_SYSTEMS_KEY2, wrapString("--eval"), KWD_SYSTEMS_KEY3, wrapString("-eval"), KWD_SYSTEMS_DOCUMENTATION, wrapString("<s-expression>\n  Evaluate the STELLA <s-expression> in the current module."), KWD_SYSTEMS_N_ARGUMENTS, wrapInteger(1), KWD_SYSTEMS_HANDLER, SYM_SYSTEMS_STELLA_EVAL_OPTION_HANDLER, KWD_SYSTEMS_ERROR_ACTION, KWD_SYSTEMS_WARN);
      registerCmdLineOption(10, KWD_SYSTEMS_KEY, wrapString("--eval-in-module"), KWD_SYSTEMS_DOCUMENTATION, wrapString("<module-name> <s-expression>\n  Evaluate the STELLA <s-expression> in module <module-name>."), KWD_SYSTEMS_N_ARGUMENTS, wrapInteger(2), KWD_SYSTEMS_HANDLER, SYM_SYSTEMS_STELLA_EVAL_IN_MODULE_OPTION_HANDLER, KWD_SYSTEMS_ERROR_ACTION, KWD_SYSTEMS_WARN);
      registerCmdLineOption(12, KWD_SYSTEMS_KEY, wrapString("--path"), KWD_SYSTEMS_KEY2, wrapString("--path+="), KWD_SYSTEMS_DOCUMENTATION, wrapString("<path>\n  Add <path> to the front of the current file load path."), KWD_SYSTEMS_N_ARGUMENTS, wrapInteger(1), KWD_SYSTEMS_HANDLER, SYM_SYSTEMS_STELLA_LOAD_PATH_OPTION_HANDLER, KWD_SYSTEMS_ERROR_ACTION, KWD_SYSTEMS_WARN);
      registerCmdLineOption(10, KWD_SYSTEMS_KEY, wrapString("--path="), KWD_SYSTEMS_DOCUMENTATION, wrapString("<path>\n  Set the current file load path to <path>."), KWD_SYSTEMS_N_ARGUMENTS, wrapInteger(1), KWD_SYSTEMS_HANDLER, SYM_SYSTEMS_STELLA_LOAD_PATH_OPTION_HANDLER, KWD_SYSTEMS_ERROR_ACTION, KWD_SYSTEMS_WARN);
      registerCmdLineOption(10, KWD_SYSTEMS_KEY, wrapString("--path=+"), KWD_SYSTEMS_DOCUMENTATION, wrapString("<path>\n  Add <path> at the end of the current file load path."), KWD_SYSTEMS_N_ARGUMENTS, wrapInteger(1), KWD_SYSTEMS_HANDLER, SYM_SYSTEMS_STELLA_LOAD_PATH_OPTION_HANDLER, KWD_SYSTEMS_ERROR_ACTION, KWD_SYSTEMS_WARN);
      registerCmdLineOption(12, KWD_SYSTEMS_KEY, wrapString("-c"), KWD_SYSTEMS_KEY2, wrapString("--configuration-file"), KWD_SYSTEMS_DOCUMENTATION, wrapString("<file>\n  Load the STELLA configuration file <file>."), KWD_SYSTEMS_N_ARGUMENTS, wrapInteger(1), KWD_SYSTEMS_HANDLER, SYM_SYSTEMS_STELLA_CONFIG_FILE_OPTION_HANDLER, KWD_SYSTEMS_ERROR_ACTION, KWD_SYSTEMS_WARN);
      registerCmdLineOption(12, KWD_SYSTEMS_KEY, wrapString("-l"), KWD_SYSTEMS_KEY2, wrapString("--load"), KWD_SYSTEMS_DOCUMENTATION, wrapString("<file>\n  Load the STELLA file <file>."), KWD_SYSTEMS_N_ARGUMENTS, wrapInteger(1), KWD_SYSTEMS_HANDLER, SYM_SYSTEMS_STELLA_LOAD_FILE_OPTION_HANDLER, KWD_SYSTEMS_ERROR_ACTION, KWD_SYSTEMS_WARN);
      registerCmdLineOption(10, KWD_SYSTEMS_KEY, wrapString("-D"), KWD_SYSTEMS_KEY2, wrapString("--define"), KWD_SYSTEMS_DOCUMENTATION, wrapString("<property>{=|+=|-=}<value>}\n  Set the STELLA configuration <property> to <value>.  Multi-valued properties can be\n  added to via the `+=' and removed from via the `-=' assignment operator."), KWD_SYSTEMS_N_ARGUMENTS, wrapInteger(1), KWD_SYSTEMS_HANDLER, SYM_SYSTEMS_STELLA_DEFINE_PROPERTY_OPTION_HANDLER);
      defineGlobalVariableObject("(DEFGLOBAL *COMMAND-LINE-HELP-HEADER* STRING \"\" :DOCUMENTATION \"Documentation to be printed at the beginning of command line help.\" :PUBLIC? TRUE)", &oCOMMAND_LINE_HELP_HEADERo);
      defineGlobalVariableObject("(DEFGLOBAL *COMMAND-LINE-HELP-TRAILER* STRING \"\" :DOCUMENTATION \"Documentation to be printed at the end of command line help.\" :PUBLIC? TRUE)", &oCOMMAND_LINE_HELP_TRAILERo);
      registerCmdLineOption(10, KWD_SYSTEMS_KEY, wrapString("-?"), KWD_SYSTEMS_KEY2, wrapString("--help"), KWD_SYSTEMS_DOCUMENTATION, wrapString("\n  Print this command line help message."), KWD_SYSTEMS_N_ARGUMENTS, wrapInteger(0), KWD_SYSTEMS_HANDLER, SYM_SYSTEMS_STELLA_HELP_OPTION_HANDLER);
    }
  }
}

Symbol* SYM_SYSTEMS_STELLA_TRUE = NULL;

Keyword* KWD_SYSTEMS_TRUE = NULL;

Symbol* SYM_SYSTEMS_STELLA_FALSE = NULL;

Keyword* KWD_SYSTEMS_FALSE = NULL;

Surrogate* SGT_SYSTEMS_STELLA_UNKNOWN = NULL;

Surrogate* SGT_SYSTEMS_STELLA_GENERALIZED_SYMBOL = NULL;

Surrogate* SGT_SYSTEMS_STELLA_INTEGER = NULL;

Surrogate* SGT_SYSTEMS_STELLA_FLOAT = NULL;

Surrogate* SGT_SYSTEMS_STELLA_NUMBER = NULL;

Surrogate* SGT_SYSTEMS_STELLA_STRING = NULL;

Surrogate* SGT_SYSTEMS_STELLA_KEYWORD = NULL;

Surrogate* SGT_SYSTEMS_STELLA_SYMBOL = NULL;

Surrogate* SGT_SYSTEMS_STELLA_BOOLEAN = NULL;

Surrogate* SGT_SYSTEMS_STELLA_MODULE = NULL;

Surrogate* SGT_SYSTEMS_STELLA_PROPERTY_LIST = NULL;

Surrogate* SGT_SYSTEMS_STELLA_CONS = NULL;

Surrogate* SGT_SYSTEMS_STELLA_LIST = NULL;

Keyword* KWD_SYSTEMS_OPTIONS = NULL;

Surrogate* SGT_SYSTEMS_STELLA_IDENTITY = NULL;

Keyword* KWD_SYSTEMS_DEFINE = NULL;

Symbol* SYM_SYSTEMS_STELLA_IN_MODULE = NULL;

Keyword* KWD_SYSTEMS_FINALIZE = NULL;

Symbol* SYM_SYSTEMS_STELLA_DEFMODULE = NULL;

Symbol* SYM_SYSTEMS_STELLA_DEFSYSTEM = NULL;

Symbol* SYM_SYSTEMS_STELLA_DEFCLASS = NULL;

Symbol* SYM_SYSTEMS_STELLA_DEFSLOT = NULL;

Symbol* SYM_SYSTEMS_STELLA_DEFUN = NULL;

Symbol* SYM_SYSTEMS_STELLA_DEFMETHOD = NULL;

Keyword* KWD_SYSTEMS_DOCUMENTATION = NULL;

Keyword* KWD_SYSTEMS_PUBLICp = NULL;

Keyword* KWD_SYSTEMS_DIRECTORY = NULL;

Keyword* KWD_SYSTEMS_FILES = NULL;

Keyword* KWD_SYSTEMS_REQUIRED_SYSTEMS = NULL;

Keyword* KWD_SYSTEMS_ACTION = NULL;

Keyword* KWD_SYSTEMS_LOAD_SYSTEM = NULL;

Keyword* KWD_SYSTEMS_LANGUAGE = NULL;

Keyword* KWD_SYSTEMS_MAKE_SYSTEM = NULL;

Keyword* KWD_SYSTEMS_LISP_ONLY_FILES = NULL;

Keyword* KWD_SYSTEMS_CPP_ONLY_FILES = NULL;

Keyword* KWD_SYSTEMS_JAVA_ONLY_FILES = NULL;

Keyword* KWD_SYSTEMS_DATA_FILES = NULL;

Keyword* KWD_SYSTEMS_PREPROCESSED_FILES = NULL;

Keyword* KWD_SYSTEMS_CARDINAL_MODULE = NULL;

Keyword* KWD_SYSTEMS_ROOT_SOURCE_DIRECTORY = NULL;

Keyword* KWD_SYSTEMS_ROOT_NATIVE_DIRECTORY = NULL;

Keyword* KWD_SYSTEMS_ROOT_BINARY_DIRECTORY = NULL;

Keyword* KWD_SYSTEMS_BANNER = NULL;

Keyword* KWD_SYSTEMS_COPYRIGHT_HEADER = NULL;

Keyword* KWD_SYSTEMS_PRODUCTION_SETTINGS = NULL;

Keyword* KWD_SYSTEMS_DEVELOPMENT_SETTINGS = NULL;

Keyword* KWD_SYSTEMS_FINALIZATION_FUNCTION = NULL;

Keyword* KWD_SYSTEMS_JAVA = NULL;

Keyword* KWD_SYSTEMS_LISP = NULL;

Keyword* KWD_SYSTEMS_CPP = NULL;

Keyword* KWD_SYSTEMS_LISP_BINARY = NULL;

Keyword* KWD_SYSTEMS_TWO_PASSp = NULL;

Keyword* KWD_SYSTEMS_DEVELOPMENT_SETTINGSp = NULL;

Keyword* KWD_SYSTEMS_PRODUCTION_SETTINGSp = NULL;

Keyword* KWD_SYSTEMS_FORCE_TRANSLATIONp = NULL;

Keyword* KWD_SYSTEMS_FORCE_RECOMPILATIONp = NULL;

Keyword* KWD_SYSTEMS_LOAD_SYSTEMp = NULL;

Keyword* KWD_SYSTEMS_STARTUPp = NULL;

Keyword* KWD_SYSTEMS_RECURSIVEp = NULL;

Surrogate* SGT_SYSTEMS_STELLA_FILE_NAME = NULL;

Keyword* KWD_SYSTEMS_PROCESSED = NULL;

Keyword* KWD_SYSTEMS_COMMON_LISP = NULL;

Keyword* KWD_SYSTEMS_USE_COMMON_LISP_STRUCTS = NULL;

Keyword* KWD_SYSTEMS_STELLA = NULL;

Keyword* KWD_SYSTEMS_WARN_ABOUT_UNDEFINED_METHODS = NULL;

Symbol* SYM_SYSTEMS_STELLA_UNLESS = NULL;

Symbol* SYM_SYSTEMS_STELLA_SYSTEM_STARTED_UPp = NULL;

Symbol* SYM_SYSTEMS_STELLA_STARTUP_TIME_PROGN = NULL;

Keyword* KWD_SYSTEMS_EARLY_INITS = NULL;

Keyword* KWD_SYSTEMS_MODULES = NULL;

Symbol* SYM_SYSTEMS_STELLA_DEFINE_MODULE_FROM_STRINGIFIED_SOURCE = NULL;

Symbol* SYM_SYSTEMS_STELLA_STARTUP = NULL;

Symbol* SYM_SYSTEMS_STELLA_FOREACH = NULL;

Symbol* SYM_SYSTEMS_STELLA_PHASE = NULL;

Symbol* SYM_SYSTEMS_STELLA_IN = NULL;

Symbol* SYM_SYSTEMS_STELLA_INTERVAL = NULL;

Symbol* SYM_SYSTEMS_STELLA_PHASE_TO_INTEGER = NULL;

Keyword* KWD_SYSTEMS_FINAL = NULL;

Symbol* SYM_SYSTEMS_STELLA_DO = NULL;

Symbol* SYM_SYSTEMS_STELLA_SETQ = NULL;

Symbol* SYM_SYSTEMS_STELLA_oSTARTUP_TIME_PHASEo = NULL;

Keyword* KWD_SYSTEMS_DAYS = NULL;

Keyword* KWD_SYSTEMS_HOURS = NULL;

Keyword* KWD_SYSTEMS_MINUTES = NULL;

Keyword* KWD_SYSTEMS_SECONDS = NULL;

Symbol* SYM_SYSTEMS_STELLA_SYSTEM_VERSION = NULL;

Keyword* KWD_SYSTEMS_SET = NULL;

Keyword* KWD_SYSTEMS_WHITE_SPACE = NULL;

Keyword* KWD_SYSTEMS_ADD = NULL;

Symbol* SYM_SYSTEMS_STELLA_CONFIGURATION_TABLE = NULL;

Keyword* KWD_SYSTEMS_CLEAR = NULL;

Keyword* KWD_SYSTEMS_REMOVE = NULL;

Keyword* KWD_SYSTEMS_ROOT_DIRECTORY = NULL;

Surrogate* SGT_SYSTEMS_STELLA_GLOBAL_VARIABLE = NULL;

Surrogate* SGT_SYSTEMS_STELLA_LONG_INTEGER = NULL;

Symbol* SYM_SYSTEMS_STELLA_TEST_PROPERTY_DEMON = NULL;

Keyword* KWD_SYSTEMS_ERROR = NULL;

Surrogate* SGT_SYSTEMS_STELLA_CMD_LINE_OPTION = NULL;

Symbol* SYM_SYSTEMS_STELLA_DOCUMENTATION = NULL;

Symbol* SYM_SYSTEMS_STELLA_KEYS = NULL;

Symbol* SYM_SYSTEMS_STELLA_VALUE_TYPE = NULL;

Symbol* SYM_SYSTEMS_STELLA_MULTI_VALUEDp = NULL;

Symbol* SYM_SYSTEMS_STELLA_N_ARGUMENTS = NULL;

Symbol* SYM_SYSTEMS_STELLA_DEFAULT_VALUE = NULL;

Symbol* SYM_SYSTEMS_STELLA_CONFIGURATION_PROPERTY = NULL;

Symbol* SYM_SYSTEMS_STELLA_HANDLER = NULL;

Symbol* SYM_SYSTEMS_STELLA_ERROR_ACTION = NULL;

Keyword* KWD_SYSTEMS_KEY = NULL;

Keyword* KWD_SYSTEMS_KEY2 = NULL;

Keyword* KWD_SYSTEMS_KEY3 = NULL;

Keyword* KWD_SYSTEMS_KEYS = NULL;

Keyword* KWD_SYSTEMS_VALUE_TYPE = NULL;

Surrogate* SGT_SYSTEMS_STELLA_TYPE = NULL;

Keyword* KWD_SYSTEMS_MULTI_VALUEDp = NULL;

Keyword* KWD_SYSTEMS_N_ARGUMENTS = NULL;

Keyword* KWD_SYSTEMS_DEFAULT_VALUE = NULL;

Surrogate* SGT_SYSTEMS_STELLA_OBJECT = NULL;

Keyword* KWD_SYSTEMS_PROPERTY = NULL;

Keyword* KWD_SYSTEMS_HANDLER = NULL;

Keyword* KWD_SYSTEMS_ERROR_ACTION = NULL;

Keyword* KWD_SYSTEMS_WARN = NULL;

Keyword* KWD_SYSTEMS_IGNORE = NULL;

Symbol* SYM_SYSTEMS_STELLA_EVAL_OPTION_HANDLER = NULL;

Symbol* SYM_SYSTEMS_STELLA_EVAL_IN_MODULE_OPTION_HANDLER = NULL;

Symbol* SYM_SYSTEMS_STELLA_LOAD_PATH_OPTION_HANDLER = NULL;

Symbol* SYM_SYSTEMS_STELLA_CONFIG_FILE_OPTION_HANDLER = NULL;

Symbol* SYM_SYSTEMS_STELLA_LOAD_FILE_OPTION_HANDLER = NULL;

Symbol* SYM_SYSTEMS_STELLA_DEFINE_PROPERTY_OPTION_HANDLER = NULL;

Symbol* SYM_SYSTEMS_STELLA_HELP_OPTION_HANDLER = NULL;

Symbol* SYM_SYSTEMS_STELLA_STARTUP_SYSTEMS = NULL;

Symbol* SYM_SYSTEMS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
