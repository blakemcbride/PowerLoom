//  -*- Mode: C++ -*-

// manuals.cc

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
| Portions created by the Initial Developer are Copyright (C) 2001-2023      |
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

#include "utilities/utilities-system.hh"

namespace stella_utilities {
  using namespace stella;

// A list of features that can modulate some aspects of
// how certain objects are described.  Currently understood features:
// :INFIX-PARAMETER-LISTS.
List* oTEXINFO_STYLE_FEATURESo = NULL;

boolean texinfoSpecialCharacterP(char ch) {
  return (stringMemberP("@{}", ch));
}

const char* texinfoEscapeString(const char* string) {
  { int nOfSpecialChars = 0;
    char* escapedString = strcpy(new (GC) char[strlen(string)+1], string);

    { char ch = NULL_CHARACTER;
      const char* vector000 = string;
      int index000 = 0;
      int length000 = strlen(vector000);

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        ch = vector000[index000];
        if (texinfoSpecialCharacterP(ch)) {
          nOfSpecialChars = nOfSpecialChars + 1;
        }
      }
    }
    if (nOfSpecialChars > 0) {
      escapedString = stringToMutableString(makeString(strlen(string) + nOfSpecialChars, NULL_CHARACTER));
      { int i = 0;

        { char ch = NULL_CHARACTER;
          const char* vector001 = string;
          int index001 = 0;
          int length001 = strlen(vector001);

          for  (; index001 < length001; 
                index001 = index001 + 1) {
            ch = vector001[index001];
            if (texinfoSpecialCharacterP(ch)) {
              escapedString[i] = '@';
              i = i + 1;
            }
            escapedString[i] = ch;
            i = i + 1;
          }
        }
      }
    }
    return (escapedString);
  }
}

const char* yieldTexinfoTypeSpec(Object* typeSpec) {
  { Object* tree = typeSpec;

    { Surrogate* testValue000 = safePrimaryType(typeSpec);

      if (testValue000 == SGT_MANUALS_STELLA_CONS) {
        { Object* typeSpec000 = typeSpec;
          Cons* typeSpec = ((Cons*)(typeSpec000));

          typeSpec = typeSpec;
        }
      }
      else if (subtypeOfSymbolP(testValue000)) {
        { Object* typeSpec001 = typeSpec;
          Symbol* typeSpec = ((Symbol*)(typeSpec001));

          tree = wrapString(typeSpec->symbolName);
        }
      }
      else if (subtypeOfSurrogateP(testValue000)) {
        { Object* typeSpec002 = typeSpec;
          Surrogate* typeSpec = ((Surrogate*)(typeSpec002));

          tree = wrapString(typeSpec->symbolName);
        }
      }
      else if (subtypeOfP(testValue000, SGT_MANUALS_STELLA_TYPE_SPEC)) {
        { Object* typeSpec003 = typeSpec;
          StandardObject* typeSpec = ((StandardObject*)(typeSpec003));

          tree = yieldTypeSpecTree(typeSpec);
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    return (stringConcatenate("@sc{", texinfoEscapeString(stringDowncase((stringP(tree) ? ((StringWrapper*)(tree))->wrapperValue : stringify(tree)))), 1, "}"));
  }
}

const char* yieldTexinfoBareName(Object* name) {
  { Surrogate* testValue000 = safePrimaryType(name);

    if (subtypeOfStringP(testValue000)) {
      { Object* name000 = name;
        StringWrapper* name = ((StringWrapper*)(name000));

        return (name->wrapperValue);
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* name001 = name;
        Symbol* name = ((Symbol*)(name001));

        return (texinfoEscapeString(stringDowncase(name->symbolName)));
      }
    }
    else if (testValue000 == SGT_MANUALS_STELLA_CONS) {
      { Object* name002 = name;
        Cons* name = ((Cons*)(name002));

        return (yieldTexinfoBareName(name->value));
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

const char* yieldTexinfoParameterName(const char* name) {
  { boolean testValue000 = false;

    { boolean foundP000 = false;

      { char ch = NULL_CHARACTER;
        const char* vector000 = name;
        int index000 = 0;
        int length000 = strlen(vector000);

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          ch = vector000[index000];
          if (!(ch == oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) ch)])) {
            foundP000 = true;
            break;
          }
        }
      }
      testValue000 = foundP000;
    }
    testValue000 = !testValue000;
    if (testValue000) {
      name = stringDowncase(name);
    }
  }
  return (texinfoEscapeString(name));
}

const char* yieldTexinfoConstant(Symbol* name) {
  return (stringConcatenate("@code{", stringConcatenate(texinfoEscapeString(stringDowncase(name->symbolName)), "}", 0), 0));
}

const char* oTEXINFO_WORD_DELIMITERSo = NULL;

const char* texinfoGetParagraphCommand(const char* string, int start) {
  { int commandIndex = 0;

    for (;;) {
      start = start + 1;
      switch (string[start]) {
        case ' ': 
          commandIndex = commandIndex + 1;
          break;
        case '\n': 
        case '\r': 
          goto loopExit008;
          break;
        default:
          return (NULL);
      }
    }
    loopExit008:;
    switch (commandIndex) {
      case 0: 
        return ("end");
      case 1: 
        return ("example");
      default:
        return ("unknown");
    }
  }
}

void texinfoDescribeDocumentationString(Object* object, const char* documentation, OutputStream* stream, List* parameters) {
  { const char* quotedName = NULL;
    int closingQuotePosition = NULL_INTEGER;
    boolean beginningOfLineP = true;
    boolean insideExampleP = false;
    const char* paragraphCommand = NULL;
    List* pendingParagraphCommands = list(0);

    if (!((boolean)(parameters))) {
      parameters = NIL_LIST;
    }
    if (documentation == NULL) {
      documentation = "Not documented.";
    }
    if (documentation != NULL) {
      { char ch = NULL_CHARACTER;
        const char* vector000 = documentation;
        int index000 = 0;
        int length000 = strlen(vector000);
        int i = NULL_INTEGER;
        int iter000 = 0;

        for  (; index000 < length000; 
              index000 = index000 + 1,
              iter000 = iter000 + 1) {
          ch = vector000[index000];
          i = iter000;
          switch (ch) {
            case '`': 
            case '\'': 
              if (!(insideExampleP)) {
                if (i == closingQuotePosition) {
                  *(stream->nativeStream) << "}";
                  continue;
                }
                else if ((i == 0) ||
                    stringMemberP(oTEXINFO_WORD_DELIMITERSo, documentation[(i - 1)])) {
                  closingQuotePosition = stringPosition(documentation, '\'', i + 1);
                  if (closingQuotePosition != NULL_INTEGER) {
                    quotedName = stringUpcase(stringSubsequence(documentation, i + 1, closingQuotePosition));
                    { boolean foundP000 = false;

                      { Symbol* pname = NULL;
                        Cons* iter001 = parameters->theConsList;

                        for (; !(iter001 == NIL); iter001 = iter001->rest) {
                          pname = ((Symbol*)(iter001->value));
                          if (stringEqlP(pname->symbolName, quotedName)) {
                            foundP000 = true;
                            goto loopExit009;
                          }
                        }
                      }
                      loopExit009:;
                      if (foundP000) {
                        *(stream->nativeStream) << "@var{";
                      }
                      else {
                        *(stream->nativeStream) << "@code{";
                      }
                    }
                    continue;
                  }
                }
              }
              *(stream->nativeStream) << ch;
              break;
            case '\n': 
            case '\r': 
              beginningOfLineP = true;
              *(stream->nativeStream) << ch;
              continue;
              break;
            case '\t': 
              { boolean testValue000 = false;

                testValue000 = beginningOfLineP;
                if (testValue000) {
                  { 
                    paragraphCommand = texinfoGetParagraphCommand(documentation, i);
                    testValue000 = paragraphCommand != NULL;
                  }
                }
                if (testValue000) {
                  {
                    if (stringEqlP(paragraphCommand, "end")) {
                      if (pendingParagraphCommands->emptyP()) {
                        {
                          *(STANDARD_WARNING->nativeStream) << "Warning: " << "Mismatched @end command on " << "`" << object << "'" << std::endl;
                          paragraphCommand = "mismatched @end command";
                        }
                      }
                      else {
                        paragraphCommand = ((StringWrapper*)(pendingParagraphCommands->pop()))->wrapperValue;
                      }
                      *(stream->nativeStream) << "@end " << paragraphCommand << std::endl;
                      if (stringEqlP(paragraphCommand, "example")) {
                        insideExampleP = false;
                      }
                    }
                    else {
                      pendingParagraphCommands->push(wrapString(paragraphCommand));
                      if (stringEqlP(paragraphCommand, "example")) {
                        insideExampleP = true;
                      }
                      *(stream->nativeStream) << std::endl << "@" << paragraphCommand;
                    }
                  }
                }
                else {
                  {
                    *(stream->nativeStream) << ch;
                  }
                }
              }
              break;
            default:
              if (texinfoSpecialCharacterP(ch)) {
                *(stream->nativeStream) << "@" << ch;
              }
              else {
                *(stream->nativeStream) << ch;
              }
              break;
          }
          beginningOfLineP = false;
        }
      }
    }
    *(stream->nativeStream) << std::endl;
  }
}

void texinfoDescribeVariable(GlobalVariable* variable, OutputStream* stream) {
  *(stream->nativeStream) << "@defvr ";
  if (variable->variableConstantP) {
    *(stream->nativeStream) << "Constant ";
  }
  else if (variable->variableSpecialP) {
    *(stream->nativeStream) << "@w{Special Variable} ";
  }
  else {
    *(stream->nativeStream) << "Variable ";
  }
  *(stream->nativeStream) << yieldTexinfoBareName(variable->variableName) << " : " << yieldTexinfoTypeSpec((((boolean)(((StandardObject*)(dynamicSlotValue(variable->dynamicSlots, SYM_MANUALS_STELLA_VARIABLE_TYPE_SPECIFIER, NULL))))) ? ((StandardObject*)(((StandardObject*)(dynamicSlotValue(variable->dynamicSlots, SYM_MANUALS_STELLA_VARIABLE_TYPE_SPECIFIER, NULL))))) : variable->variableType)) << std::endl;
  texinfoDescribeDocumentationString(variable, variable->documentation, stream, NULL);
  *(stream->nativeStream) << "@end defvr" << std::endl;
}

void texinfoDescribeClass(Class* clasS, OutputStream* stream) {
  *(stream->nativeStream) << "@deftp Class " << yieldTexinfoTypeSpec(classSymbol(clasS));
  { Surrogate* super = NULL;
    Cons* iter000 = clasS->classDirectSupers->theConsList;
    int i = NULL_INTEGER;
    int iter001 = 1;

    for  (; !(iter000 == NIL); 
          iter000 = iter000->rest,
          iter001 = iter001 + 1) {
      super = ((Surrogate*)(iter000->value));
      i = iter001;
      if (i == 1) {
        *(stream->nativeStream) << " : ";
      }
      else {
        *(stream->nativeStream) << ", ";
      }
      *(stream->nativeStream) << yieldTexinfoTypeSpec(super);
    }
  }
  *(stream->nativeStream) << std::endl;
  texinfoDescribeDocumentationString(clasS, ((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_MANUALS_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue, stream, NIL_LIST);
  { Slot* slot = NULL;
    Cons* iter002 = clasS->classLocalSlots->theConsList;

    for (; !(iter002 == NIL); iter002 = iter002->rest) {
      slot = ((Slot*)(iter002->value));
      if (storageSlotP(slot) &&
          parameterSlotP(((StorageSlot*)(slot)))) {
        texinfoDescribeSlot(((StorageSlot*)(slot)), stream);
      }
    }
  }
  { Slot* slot = NULL;
    Cons* iter003 = clasS->classLocalSlots->theConsList;

    for (; !(iter003 == NIL); iter003 = iter003->rest) {
      slot = ((Slot*)(iter003->value));
      if (storageSlotP(slot) &&
          nativeSlotP(((StorageSlot*)(slot)))) {
        texinfoDescribeSlot(((StorageSlot*)(slot)), stream);
      }
    }
  }
  *(stream->nativeStream) << "@end deftp" << std::endl;
}

void texinfoDescribeSlot(StorageSlot* slot, OutputStream* stream) {
  { const char* category = "Slot";

    { CompoundTypeSpecifier* temp000 = ((CompoundTypeSpecifier*)(dynamicSlotValue(slot->dynamicSlots, SYM_MANUALS_STELLA_SLOT_TYPE_SPECIFIER, NULL)));

      { StandardObject* type = (((boolean)(temp000)) ? ((StandardObject*)(temp000)) : ((StandardObject*)(slot->slotBaseType)));

        if (parameterSlotP(slot)) {
          category = "@w{Class Parameter}";
        }
        else if (slot->abstractP) {
          category = "@w{Abstract Slot}";
        }
        *(stream->nativeStream) << "@defcv " << category << " " << "{}" << " " << yieldTexinfoBareName(slot->slotName) << " : " << yieldTexinfoTypeSpec(type) << std::endl;
        texinfoDescribeDocumentationString(slot, ((StringWrapper*)(dynamicSlotValue(slot->dynamicSlots, SYM_MANUALS_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue, stream, NIL_LIST);
        *(stream->nativeStream) << "@end defcv" << std::endl;
      }
    }
  }
}

List* texinfoGetRealMethodParameterNames(MethodSlot* method) {
  { List* result = list(0);
    const char* documentation = ((StringWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_MANUALS_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue;
    const char* pName = NULL;
    int pNameLength = NULL_INTEGER;
    int start = NULL_INTEGER;
    int end = NULL_INTEGER;

    if (documentation == NULL) {
      documentation = "";
    }
    end = strlen(documentation) - 1;
    { Symbol* parameter = NULL;
      Cons* iter000 = method->methodParameterNames_reader()->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        parameter = ((Symbol*)(iter000->value));
        pName = parameter->symbolName;
        pNameLength = strlen(pName);
        { int value000 = NULL_INTEGER;

          { int i = NULL_INTEGER;
            IntegerIntervalIterator* iter001 = interval(1, end - pNameLength);

            for (; iter001->nextP(); ) {
              i = iter001->value;
              { boolean testValue000 = false;

                testValue000 = (documentation[(i - 1)] == '`') ||
                    (documentation[(i - 1)] == '\'');
                if (testValue000) {
                  testValue000 = documentation[(i + pNameLength)] == '\'';
                  if (testValue000) {
                    { boolean alwaysP000 = true;

                      { char ch = NULL_CHARACTER;
                        const char* vector000 = pName;
                        int index000 = 0;
                        int length000 = strlen(vector000);
                        int j = NULL_INTEGER;
                        int iter002 = 0;
                        int upperBound000 = pNameLength - 1;

                        for  (; (index000 < length000) &&
                                  (iter002 <= upperBound000); 
                              index000 = index000 + 1,
                              iter002 = iter002 + 1) {
                          ch = vector000[index000];
                          j = iter002;
                          if (!(oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) ch)] == oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) (documentation[(i + j)]))])) {
                            alwaysP000 = false;
                            break;
                          }
                        }
                      }
                      testValue000 = alwaysP000;
                    }
                  }
                }
                if (testValue000) {
                  value000 = i;
                  break;
                }
              }
            }
          }
          start = value000;
        }
        if (start != NULL_INTEGER) {
          pName = stringSubsequence(documentation, start, start + pNameLength);
        }
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(wrapString(pName), NIL);
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
            collect000->rest = cons(wrapString(pName), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (result);
  }
}

List* texinfoGetRealMethodParametersAndTypes(MethodSlot* method, List*& _Return1, List*& _Return2) {
  { const char* stringifiedSource = method->methodStringifiedSource;
    List* realParameterNames = texinfoGetRealMethodParameterNames(method);
    List* realParameterTypes = list(0);
    List* realReturnTypes = list(0);
    Cons* definitionTree = NULL;
    Cons* returnTypesTree = NIL;
    Cons* parametersTree = NIL;

    { StandardObject* pType = NULL;
      Cons* iter000 = method->methodParameterTypeSpecifiers_reader()->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        pType = ((StandardObject*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(yieldTypeSpecTree(pType), NIL);
            if (realParameterTypes->theConsList == NIL) {
              realParameterTypes->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(realParameterTypes->theConsList, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(yieldTypeSpecTree(pType), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    { StandardObject* rtype = NULL;
      Cons* iter001 = method->methodReturnTypeSpecifiers_reader()->theConsList;
      Cons* collect001 = NULL;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest) {
        rtype = ((StandardObject*)(iter001->value));
        if (!((boolean)(collect001))) {
          {
            collect001 = cons(yieldTypeSpecTree(rtype), NIL);
            if (realReturnTypes->theConsList == NIL) {
              realReturnTypes->theConsList = collect001;
            }
            else {
              addConsToEndOfConsList(realReturnTypes->theConsList, collect001);
            }
          }
        }
        else {
          {
            collect001->rest = cons(yieldTypeSpecTree(rtype), NIL);
            collect001 = collect001->rest;
          }
        }
      }
    }
    if (stringifiedSource != NULL) {
      definitionTree = ((Cons*)(readSExpressionFromString(stringifiedSource)));
      if (consP(definitionTree->rest->value)) {
        returnTypesTree = ((Cons*)(definitionTree->rest->value))->rest;
      }
      parametersTree = ((Cons*)(definitionTree->rest->rest->value));
      parametersTree = parametersTree->remove(SYM_MANUALS_STELLA_aREST);
      parametersTree = parametersTree->remove(SYM_MANUALS_STELLA_aBODY);
      { Cons* ptree = NULL;
        Cons* iter002 = parametersTree;
        ListIterator* it = ((ListIterator*)(realParameterTypes->allocateIterator()));

        for  (; (!(iter002 == NIL)) &&
                  it->nextP(); 
              iter002 = iter002->rest) {
          ptree = ((Cons*)(iter002->value));
          it->valueSetter(ptree->last());
        }
      }
      { Object* rtree = NULL;
        Cons* iter003 = returnTypesTree;
        ListIterator* it = ((ListIterator*)(realReturnTypes->allocateIterator()));

        for  (; (!(iter003 == NIL)) &&
                  it->nextP(); 
              iter003 = iter003->rest) {
          rtree = iter003->value;
          it->valueSetter(rtree);
        }
      }
    }
    _Return1 = realParameterTypes;
    _Return2 = realReturnTypes;
    return (realParameterNames);
  }
}

void texinfoDescribeMethod(MethodSlot* method, OutputStream* stream) {
  { const char* category = "Function";
    const char* endcmd = "@end deffn";

    if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_MANUALS_STELLA_METHOD_MACROp, FALSE_WRAPPER)))->wrapperValue) {
      category = "Macro";
    }
    else if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_MANUALS_STELLA_METHOD_COMMANDp, FALSE_WRAPPER)))->wrapperValue) {
      category = "Command";
    }
    else if (!method->methodFunctionP) {
      category = "Method";
    }
    if (!(method->methodEvaluateArgumentsP_reader() ||
        ((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_MANUALS_STELLA_METHOD_MACROp, FALSE_WRAPPER)))->wrapperValue)) {
      category = stringConcatenate("N-", category, 0);
    }
    if (!method->methodFunctionP) {
      *(stream->nativeStream) << "@defmethod " << yieldTexinfoTypeSpec(method->owner()) << " " << yieldTexinfoBareName(method->slotName) << " ";
      endcmd = "@end defmethod";
    }
    else {
      *(stream->nativeStream) << "@deffn " << category << " " << yieldTexinfoBareName(method->slotName) << " ";
      endcmd = "@end deffn";
    }
    *(stream->nativeStream) << "(";
    { List* parameterNames = NULL;
      List* parameterTypes = NULL;
      List* returntypes = NULL;

      parameterNames = texinfoGetRealMethodParametersAndTypes(method, parameterTypes, returntypes);
      { int nOfArguments = parameterNames->length();
        const char* modifier = NULL;

        { StringWrapper* pName = NULL;
          Cons* iter000 = parameterNames->theConsList;
          Object* pType = NULL;
          Cons* iter001 = parameterTypes->theConsList;
          int i = NULL_INTEGER;
          int iter002 = 1;

          for  (; (!(iter000 == NIL)) &&
                    (!(iter001 == NIL)); 
                iter000 = iter000->rest,
                iter001 = iter001->rest,
                iter002 = iter002 + 1) {
            pName = ((StringWrapper*)(iter000->value));
            pType = iter001->value;
            i = iter002;
            modifier = NULL;
            if (i == nOfArguments) {
              if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_MANUALS_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue) {
                modifier = "&rest";
              }
              if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_MANUALS_STELLA_METHOD_BODY_ARGUMENTp, FALSE_WRAPPER)))->wrapperValue) {
                modifier = "&body";
              }
            }
            if ((i == 1) &&
                stringEqlP(category, "Method")) {
              *(stream->nativeStream) << yieldTexinfoParameterName(pName->wrapperValue);
            }
            else {
              texinfoDescribeTypeDeclaration(pName->wrapperValue, ((StandardObject*)(pType)), modifier, stream);
            }
            if (i < nOfArguments) {
              if (oTEXINFO_STYLE_FEATURESo->memberP(KWD_MANUALS_INFIX_PARAMETER_LISTS)) {
                *(stream->nativeStream) << ", ";
              }
              else {
                *(stream->nativeStream) << " ";
              }
            }
          }
        }
        *(stream->nativeStream) << ")";
        *(stream->nativeStream) << " : ";
        { Object* rtype = NULL;
          Cons* iter003 = returntypes->theConsList;

          for (; !(iter003 == NIL); iter003 = iter003->rest) {
            rtype = iter003->value;
            *(stream->nativeStream) << yieldTexinfoTypeSpec(rtype) << " ";
          }
        }
        *(stream->nativeStream) << std::endl;
        texinfoDescribeDocumentationString(method, ((StringWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_MANUALS_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue, stream, method->methodParameterNames_reader());
        *(stream->nativeStream) << endcmd << std::endl;
      }
    }
  }
}

void texinfoDescribeTypeDeclaration(const char* parameter, StandardObject* type, const char* modifier, OutputStream* stream) {
  *(stream->nativeStream) << "@w{";
  if (modifier != NULL) {
    *(stream->nativeStream) << modifier << " ";
  }
  { 
    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
    if (oTEXINFO_STYLE_FEATURESo->memberP(KWD_MANUALS_INFIX_PARAMETER_LISTS)) {
      *(stream->nativeStream) << yieldTexinfoParameterName(parameter) << " : " << yieldTexinfoTypeSpec(type);
    }
    else {
      *(stream->nativeStream) << "(" << yieldTexinfoParameterName(parameter) << " " << yieldTexinfoTypeSpec(type) << ")";
    }
    *(stream->nativeStream) << "}";
  }
}

void texinfoDescribeUnimplementedObject(Object* specification, OutputStream* stream) {
  *(stream->nativeStream) << "@deffn ??? " << yieldTexinfoBareName(specification) << std::endl << "Not yet implemented." << std::endl << "@end deffn" << std::endl;
}

DEFINE_STELLA_SPECIAL(oMANUAL_OUTPUT_LANGUAGEo, Keyword* , NULL);

HashTable* oDOCUMENTED_OBJECTS_REGISTRYo = NULL;

void registerDocumentedObject(Object* object) {
  oDOCUMENTED_OBJECTS_REGISTRYo->insertAt(object, object);
}

boolean alreadyDocumentedObjectP(Object* object) {
  return (((boolean)(oDOCUMENTED_OBJECTS_REGISTRYo->lookup(object))));
}

void clearDocumentedObjectsRegistry() {
  oDOCUMENTED_OBJECTS_REGISTRYo->initializeHashTable();
}

Object* lookupObjectFromSpecification(Object* specification) {
  { Object* object = NULL;

    { Surrogate* testValue000 = safePrimaryType(specification);

      if (subtypeOfSurrogateP(testValue000)) {
        { Object* specification000 = specification;
          Surrogate* specification = ((Surrogate*)(specification000));

          object = ((Class*)(specification->surrogateValue));
        }
      }
      else if (subtypeOfSymbolP(testValue000)) {
        { Object* specification001 = specification;
          Symbol* specification = ((Symbol*)(specification001));

          object = lookupFunction(specification);
          if (!((boolean)(object))) {
            object = specification->lookupGlobalVariable();
          }
          if (!((boolean)(object))) {
            object = specification->lookupClass();
          }
          if (!((boolean)(object))) {
            object = stringGetObject(specification->symbolName, NULL);
          }
        }
      }
      else if (testValue000 == SGT_MANUALS_STELLA_CONS) {
        { Object* specification002 = specification;
          Cons* specification = ((Cons*)(specification002));

          { Symbol* classsymbol = ((Symbol*)(specification->rest->value));
            Class* clasS = NULL;

            { 
              BIND_STELLA_SPECIAL(oMODULEo, Module*, ((Module*)(classsymbol->homeContext)));
              BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
              clasS = ((Symbol*)(specification->rest->value))->getStellaClass(false);
            }
            if (!((boolean)(clasS))) {
              std::cout << "Can't find a class named " << specification->rest->value;
              return (NULL);
            }
            return (lookupSlot(clasS, ((Symbol*)(specification->value))));
          }
        }
      }
      else if (subtypeOfStringP(testValue000)) {
        { Object* specification003 = specification;
          StringWrapper* specification = ((StringWrapper*)(specification003));

          object = getStellaModule(specification->wrapperValue, false);
        }
      }
      else {
      }
    }
    return (object);
  }
}

boolean texinfoObjectL(Object* object1, Object* object2) {
  { const char* name1 = NULL;
    const char* name2 = NULL;

    { Surrogate* testValue000 = safePrimaryType(object1);

      if (subtypeOfP(testValue000, SGT_MANUALS_STELLA_SLOT)) {
        { Object* object1000 = object1;
          Slot* object1 = ((Slot*)(object1000));

          name1 = object1->slotName->visibleName(false);
        }
      }
      else if (subtypeOfP(testValue000, SGT_MANUALS_STELLA_GLOBAL_VARIABLE)) {
        { Object* object1001 = object1;
          GlobalVariable* object1 = ((GlobalVariable*)(object1001));

          name1 = object1->variableName->visibleName(false);
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    { Surrogate* testValue001 = safePrimaryType(object2);

      if (subtypeOfP(testValue001, SGT_MANUALS_STELLA_SLOT)) {
        { Object* object2000 = object2;
          Slot* object2 = ((Slot*)(object2000));

          name2 = object2->slotName->visibleName(false);
        }
      }
      else if (subtypeOfP(testValue001, SGT_MANUALS_STELLA_GLOBAL_VARIABLE)) {
        { Object* object2001 = object2;
          GlobalVariable* object2 = ((GlobalVariable*)(object2001));

          name2 = object2->variableName->visibleName(false);
        }
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
          throw *newStellaException(stream001->theStringReader());
        }
      }
    }
    return (stringL(name1, name2));
  }
}

void manualDescribeUncategorizedObjects(Module* module, OutputStream* stream) {
  { List* methods = newList();

    { MethodSlot* function = NULL;
      Iterator* iter000 = allFunctions(module, true);
      Cons* collect000 = NULL;

      for  (; iter000->nextP(); ) {
        function = ((MethodSlot*)(iter000->value));
        if ((((StringWrapper*)(dynamicSlotValue(function->dynamicSlots, SYM_MANUALS_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue != NULL) &&
            (!alreadyDocumentedObjectP(function))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(function, NIL);
              if (methods->theConsList == NIL) {
                methods->theConsList = collect000;
              }
              else {
                addConsToEndOfConsList(methods->theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(function, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    { MethodSlot* method = NULL;
      Iterator* iter001 = allMethods(module, true);
      Cons* collect001 = NULL;

      for  (; iter001->nextP(); ) {
        method = ((MethodSlot*)(iter001->value));
        if ((((StringWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_MANUALS_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue != NULL) &&
            (!alreadyDocumentedObjectP(method))) {
          if (!((boolean)(collect001))) {
            {
              collect001 = cons(method, NIL);
              if (methods->theConsList == NIL) {
                methods->theConsList = collect001;
              }
              else {
                addConsToEndOfConsList(methods->theConsList, collect001);
              }
            }
          }
          else {
            {
              collect001->rest = cons(method, NIL);
              collect001 = collect001->rest;
            }
          }
        }
      }
    }
    methods->sort(((cpp_function_code)(&texinfoObjectL)));
    { MethodSlot* method = NULL;
      Cons* iter002 = methods->theConsList;

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        method = ((MethodSlot*)(iter002->value));
        manualDescribeObject(method, NULL, stream);
        *(stream->nativeStream) << std::endl;
      }
    }
  }
}

void manualDescribeObject(Object* object, Object* specification, OutputStream* stream) {
  if (!((boolean)(object))) {
    object = lookupObjectFromSpecification(specification);
  }
  if (oMANUAL_OUTPUT_LANGUAGEo == KWD_MANUALS_TEXINFO) {
    if (!((boolean)(object))) {
      if (((boolean)(specification))) {
        texinfoDescribeUnimplementedObject(specification, stream);
      }
    }
    else {
      { Surrogate* testValue000 = safePrimaryType(object);

        if (subtypeOfP(testValue000, SGT_MANUALS_STELLA_GLOBAL_VARIABLE)) {
          { Object* object000 = object;
            GlobalVariable* object = ((GlobalVariable*)(object000));

            texinfoDescribeVariable(object, stream);
          }
        }
        else if (subtypeOfClassP(testValue000)) {
          { Object* object001 = object;
            Class* object = ((Class*)(object001));

            texinfoDescribeClass(object, stream);
          }
        }
        else if (subtypeOfMethodSlotP(testValue000)) {
          { Object* object002 = object;
            MethodSlot* object = ((MethodSlot*)(object002));

            texinfoDescribeMethod(object, stream);
          }
        }
        else if (subtypeOfP(testValue000, SGT_MANUALS_STELLA_MODULE)) {
          { Object* object003 = object;
            Module* object = ((Module*)(object003));

            manualDescribeUncategorizedObjects(object, stream);
          }
        }
        else {
          { Symbol* handlername = internSymbolInModule(stringConcatenate("TEXINFO-DESCRIBE-", object->primaryType()->symbolName, 0), ((Module*)(SYM_MANUALS_UTILITIES_MANUAL_DESCRIBE_OBJECT->homeContext)), true);
            MethodSlot* handler = lookupFunction(handlername);

            if (((boolean)(handler))) {
              ((void  (*) (Object*, OutputStream*))handler->functionCode)(object, stream);
            }
          }
        }
      }
      registerDocumentedObject(object);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << oMANUAL_OUTPUT_LANGUAGEo << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void generateManual(Cons* manualSpec) {
  // Generate a TEXINFO file containing a list of
  // documented commands.  'manual-spec' is a CONS list of entries, where each
  // entry is of the following form:
  // 
  //       (<filename> <object-spec1> <object-spec2> ... <object-specN>)
  // 
  // The objects specified by <object-spec>s will be documented in sequence onto
  // file <filename>.  An object spec can be a simple symbol to name a function,
  // macro or variable, a dotted symbol to name a method or slot, a surrogate
  // to name a class, or a string (pathname) to name a module.  If a module is
  // specified, all as yet undocumented objects in that module that have a
  // documentation string defined will be documented (this is a catch-all option).
  { OutputFileStream* stream = NULL;

    clearDocumentedObjectsRegistry();
    { Cons* filespec = NULL;
      Cons* iter000 = manualSpec;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        filespec = ((Cons*)(iter000->value));
        stream = newOutputFileStream(((StringWrapper*)(filespec->value))->wrapperValue);
        { Object* spec = NULL;
          Cons* iter001 = filespec->rest;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            spec = iter001->value;
            manualDescribeObject(NULL, spec, stream);
            *(stream->nativeStream) << std::endl;
          }
        }
        stream->free();
      }
    }
  }
}

DEFINE_STELLA_SPECIAL(oMANUAL_OUTPUT_STREAMo, OutputStream* , NULL);

const char* oMANUAL_TEMPLATE_COMMAND_PREFIXo = "#$";

void generateManualFromTemplate(const char* templatefile, const char* outputfile) {
  { OutputFileStream* outStream = NULL;

    try {
      outStream = openOutputFile(outputfile, 0);
      { 
        BIND_STELLA_SPECIAL(oMANUAL_OUTPUT_STREAMo, OutputStream*, outStream);
        { InputFileStream* inStream = NULL;

          try {
            inStream = openInputFile(templatefile, 0);
            { const char* line = NULL;
              LineIterator* iter000 = lines(inStream);

              for (; iter000->nextP(); ) {
                line = iter000->value;
                *(oMANUAL_OUTPUT_STREAMo->nativeStream) << manualExpandTemplateCommands(line) << std::endl;
              }
            }
          }
catch (...) {
            if (((boolean)(inStream))) {
              inStream->free();
            }
            throw;
          }
          if (((boolean)(inStream))) {
            inStream->free();
          }
        }
      }
    }
catch (...) {
      if (((boolean)(outStream))) {
        outStream->free();
      }
      throw;
    }
    if (((boolean)(outStream))) {
      outStream->free();
    }
  }
}

const char* manualExpandTemplateCommands(const char* line) {
  { boolean dummy1;

    { int commandstart = stringSearch(line, oMANUAL_TEMPLATE_COMMAND_PREFIXo, 0);

      if (commandstart == NULL_INTEGER) {
        return (line);
      }
      try {
        { const char* prefix = stringSubsequence(line, 0, commandstart);
          InputStringStream* restline = newInputStringStream(stringSubsequence(line, commandstart + strlen(oMANUAL_TEMPLATE_COMMAND_PREFIXo), NULL_INTEGER));
          Object* expression = readSExpression(restline, dummy1);

          { 
            BIND_STELLA_SPECIAL(oMANUAL_OUTPUT_STREAMo, OutputStream*, newOutputStringStream());
            evaluate(expression);
            line = readLine(restline);
            if (line == NULL) {
              line = "";
            }
            return (stringConcatenate(prefix, ((OutputStringStream*)(oMANUAL_OUTPUT_STREAMo))->theStringReader(), 1, manualExpandTemplateCommands(line)));
          }
        }
      }
      catch (std::exception& _e) {
        std::exception* e = &_e;

        std::cout << "*** ERROR while expanding template command: " << exceptionMessage(e) << std::endl << "    Error occured in line: `" << line << "'" << std::endl;
        return (line);
      }
    }
  }
}

void texinfoInsertDoc(Object* spec) {
  { 
    BIND_STELLA_SPECIAL(oMANUAL_OUTPUT_LANGUAGEo, Keyword*, KWD_MANUALS_TEXINFO);
    manualDescribeObject(NULL, spec, oMANUAL_OUTPUT_STREAMo);
  }
}

void texinfoInsertPreamble() {
  { 
    BIND_STELLA_SPECIAL(oMANUAL_OUTPUT_LANGUAGEo, Keyword*, KWD_MANUALS_TEXINFO);
    *(oMANUAL_OUTPUT_STREAMo->nativeStream) << "@c DO NOT MODIFY THIS FILE, " << "IT WAS GENERATED AUTOMATICALLY FROM A TEMPLATE!";
  }
}

void helpStartupManuals1() {
  {
    SGT_MANUALS_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
    SGT_MANUALS_STELLA_TYPE_SPEC = ((Surrogate*)(internRigidSymbolWrtModule("TYPE-SPEC", getStellaModule("/STELLA", true), 1)));
    SYM_MANUALS_STELLA_VARIABLE_TYPE_SPECIFIER = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-TYPE-SPECIFIER", getStellaModule("/STELLA", true), 0)));
    SYM_MANUALS_STELLA_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("DOCUMENTATION", getStellaModule("/STELLA", true), 0)));
    SYM_MANUALS_STELLA_SLOT_TYPE_SPECIFIER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-TYPE-SPECIFIER", getStellaModule("/STELLA", true), 0)));
    SYM_MANUALS_STELLA_aREST = ((Symbol*)(internRigidSymbolWrtModule("&REST", getStellaModule("/STELLA", true), 0)));
    SYM_MANUALS_STELLA_aBODY = ((Symbol*)(internRigidSymbolWrtModule("&BODY", getStellaModule("/STELLA", true), 0)));
    SYM_MANUALS_STELLA_METHOD_MACROp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-MACRO?", getStellaModule("/STELLA", true), 0)));
    SYM_MANUALS_STELLA_METHOD_COMMANDp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-COMMAND?", getStellaModule("/STELLA", true), 0)));
    SYM_MANUALS_STELLA_METHOD_VARIABLE_ARGUMENTSp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-VARIABLE-ARGUMENTS?", getStellaModule("/STELLA", true), 0)));
    SYM_MANUALS_STELLA_METHOD_BODY_ARGUMENTp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-BODY-ARGUMENT?", getStellaModule("/STELLA", true), 0)));
    KWD_MANUALS_INFIX_PARAMETER_LISTS = ((Keyword*)(internRigidSymbolWrtModule("INFIX-PARAMETER-LISTS", NULL, 2)));
    KWD_MANUALS_TEXINFO = ((Keyword*)(internRigidSymbolWrtModule("TEXINFO", NULL, 2)));
    SGT_MANUALS_STELLA_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("SLOT", getStellaModule("/STELLA", true), 1)));
    SGT_MANUALS_STELLA_GLOBAL_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("GLOBAL-VARIABLE", getStellaModule("/STELLA", true), 1)));
    SGT_MANUALS_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", getStellaModule("/STELLA", true), 1)));
    SYM_MANUALS_UTILITIES_MANUAL_DESCRIBE_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("MANUAL-DESCRIBE-OBJECT", NULL, 0)));
    SYM_MANUALS_UTILITIES_STARTUP_MANUALS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-MANUALS", NULL, 0)));
    SYM_MANUALS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void startupManuals() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/UTILITIES", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupManuals1();
    }
    if (currentStartupTimePhaseP(4)) {
      oTEXINFO_STYLE_FEATURESo = list(0);
      oTEXINFO_WORD_DELIMITERSo = NULL;
      oMANUAL_OUTPUT_LANGUAGEo = KWD_MANUALS_TEXINFO;
      oDOCUMENTED_OBJECTS_REGISTRYo = newHashTable();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("TEXINFO-SPECIAL-CHARACTER?", "(DEFUN (TEXINFO-SPECIAL-CHARACTER? BOOLEAN) ((CH CHARACTER)))", ((cpp_function_code)(&texinfoSpecialCharacterP)), NULL);
      defineFunctionObject("TEXINFO-ESCAPE-STRING", "(DEFUN (TEXINFO-ESCAPE-STRING STRING) ((STRING STRING)))", ((cpp_function_code)(&texinfoEscapeString)), NULL);
      defineFunctionObject("YIELD-TEXINFO-TYPE-SPEC", "(DEFUN (YIELD-TEXINFO-TYPE-SPEC STRING) ((TYPE-SPEC OBJECT)))", ((cpp_function_code)(&yieldTexinfoTypeSpec)), NULL);
      defineFunctionObject("YIELD-TEXINFO-BARE-NAME", "(DEFUN (YIELD-TEXINFO-BARE-NAME STRING) ((NAME OBJECT)))", ((cpp_function_code)(&yieldTexinfoBareName)), NULL);
      defineFunctionObject("YIELD-TEXINFO-PARAMETER-NAME", "(DEFUN (YIELD-TEXINFO-PARAMETER-NAME STRING) ((NAME STRING)))", ((cpp_function_code)(&yieldTexinfoParameterName)), NULL);
      defineFunctionObject("YIELD-TEXINFO-CONSTANT", "(DEFUN (YIELD-TEXINFO-CONSTANT STRING) ((NAME SYMBOL)))", ((cpp_function_code)(&yieldTexinfoConstant)), NULL);
      defineFunctionObject("TEXINFO-GET-PARAGRAPH-COMMAND", "(DEFUN (TEXINFO-GET-PARAGRAPH-COMMAND STRING) ((STRING STRING) (START INTEGER)))", ((cpp_function_code)(&texinfoGetParagraphCommand)), NULL);
      defineFunctionObject("TEXINFO-DESCRIBE-DOCUMENTATION-STRING", "(DEFUN TEXINFO-DESCRIBE-DOCUMENTATION-STRING ((OBJECT OBJECT) (DOCUMENTATION STRING) (STREAM OUTPUT-STREAM) (PARAMETERS (LIST OF SYMBOL))))", ((cpp_function_code)(&texinfoDescribeDocumentationString)), NULL);
      defineFunctionObject("TEXINFO-DESCRIBE-VARIABLE", "(DEFUN TEXINFO-DESCRIBE-VARIABLE ((VARIABLE GLOBAL-VARIABLE) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&texinfoDescribeVariable)), NULL);
      defineFunctionObject("TEXINFO-DESCRIBE-CLASS", "(DEFUN TEXINFO-DESCRIBE-CLASS ((CLASS CLASS) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&texinfoDescribeClass)), NULL);
      defineFunctionObject("TEXINFO-DESCRIBE-SLOT", "(DEFUN TEXINFO-DESCRIBE-SLOT ((SLOT STORAGE-SLOT) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&texinfoDescribeSlot)), NULL);
      defineFunctionObject("TEXINFO-GET-REAL-METHOD-PARAMETER-NAMES", "(DEFUN (TEXINFO-GET-REAL-METHOD-PARAMETER-NAMES (LIST OF STRING-WRAPPER)) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&texinfoGetRealMethodParameterNames)), NULL);
      defineFunctionObject("TEXINFO-GET-REAL-METHOD-PARAMETERS-AND-TYPES", "(DEFUN (TEXINFO-GET-REAL-METHOD-PARAMETERS-AND-TYPES (LIST OF STRING-WRAPPER) LIST LIST) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&texinfoGetRealMethodParametersAndTypes)), NULL);
      defineFunctionObject("TEXINFO-DESCRIBE-METHOD", "(DEFUN TEXINFO-DESCRIBE-METHOD ((METHOD METHOD-SLOT) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&texinfoDescribeMethod)), NULL);
      defineFunctionObject("TEXINFO-DESCRIBE-TYPE-DECLARATION", "(DEFUN TEXINFO-DESCRIBE-TYPE-DECLARATION ((PARAMETER STRING) (TYPE TYPE-SPEC) (MODIFIER STRING) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&texinfoDescribeTypeDeclaration)), NULL);
      defineFunctionObject("TEXINFO-DESCRIBE-UNIMPLEMENTED-OBJECT", "(DEFUN TEXINFO-DESCRIBE-UNIMPLEMENTED-OBJECT ((SPECIFICATION OBJECT) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&texinfoDescribeUnimplementedObject)), NULL);
      defineFunctionObject("REGISTER-DOCUMENTED-OBJECT", "(DEFUN REGISTER-DOCUMENTED-OBJECT ((OBJECT OBJECT)))", ((cpp_function_code)(&registerDocumentedObject)), NULL);
      defineFunctionObject("ALREADY-DOCUMENTED-OBJECT?", "(DEFUN (ALREADY-DOCUMENTED-OBJECT? BOOLEAN) ((OBJECT OBJECT)))", ((cpp_function_code)(&alreadyDocumentedObjectP)), NULL);
      defineFunctionObject("CLEAR-DOCUMENTED-OBJECTS-REGISTRY", "(DEFUN CLEAR-DOCUMENTED-OBJECTS-REGISTRY ())", ((cpp_function_code)(&clearDocumentedObjectsRegistry)), NULL);
      defineFunctionObject("LOOKUP-OBJECT-FROM-SPECIFICATION", "(DEFUN (LOOKUP-OBJECT-FROM-SPECIFICATION OBJECT) ((SPECIFICATION OBJECT)))", ((cpp_function_code)(&lookupObjectFromSpecification)), NULL);
      defineFunctionObject("TEXINFO-OBJECT<", "(DEFUN (TEXINFO-OBJECT< BOOLEAN) ((OBJECT1 OBJECT) (OBJECT2 OBJECT)))", ((cpp_function_code)(&texinfoObjectL)), NULL);
      defineFunctionObject("MANUAL-DESCRIBE-UNCATEGORIZED-OBJECTS", "(DEFUN MANUAL-DESCRIBE-UNCATEGORIZED-OBJECTS ((MODULE MODULE) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&manualDescribeUncategorizedObjects)), NULL);
      defineFunctionObject("MANUAL-DESCRIBE-OBJECT", "(DEFUN MANUAL-DESCRIBE-OBJECT ((OBJECT OBJECT) (SPECIFICATION OBJECT) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&manualDescribeObject)), NULL);
      defineFunctionObject("GENERATE-MANUAL", "(DEFUN GENERATE-MANUAL ((MANUAL-SPEC (CONS OF CONS))) :DOCUMENTATION \"Generate a TEXINFO file containing a list of\ndocumented commands.  'manual-spec' is a CONS list of entries, where each\nentry is of the following form:\n\n      (<filename> <object-spec1> <object-spec2> ... <object-specN>)\n\nThe objects specified by <object-spec>s will be documented in sequence onto\nfile <filename>.  An object spec can be a simple symbol to name a function,\nmacro or variable, a dotted symbol to name a method or slot, a surrogate\nto name a class, or a string (pathname) to name a module.  If a module is\nspecified, all as yet undocumented objects in that module that have a\ndocumentation string defined will be documented (this is a catch-all option).\")", ((cpp_function_code)(&generateManual)), NULL);
      defineFunctionObject("GENERATE-MANUAL-FROM-TEMPLATE", "(DEFUN GENERATE-MANUAL-FROM-TEMPLATE ((TEMPLATEFILE FILE-NAME) (OUTPUTFILE FILE-NAME)))", ((cpp_function_code)(&generateManualFromTemplate)), NULL);
      defineFunctionObject("MANUAL-EXPAND-TEMPLATE-COMMANDS", "(DEFUN (MANUAL-EXPAND-TEMPLATE-COMMANDS STRING) ((LINE STRING)))", ((cpp_function_code)(&manualExpandTemplateCommands)), NULL);
      defineFunctionObject("TEXINFO-INSERT-DOC", "(DEFUN TEXINFO-INSERT-DOC ((SPEC OBJECT)) :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&texinfoInsertDoc)), NULL);
      defineFunctionObject("TEXINFO-INSERT-PREAMBLE", "(DEFUN TEXINFO-INSERT-PREAMBLE () :COMMAND? TRUE)", ((cpp_function_code)(&texinfoInsertPreamble)), NULL);
      defineFunctionObject("STARTUP-MANUALS", "(DEFUN STARTUP-MANUALS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupManuals)), NULL);
      { MethodSlot* function = lookupFunction(SYM_MANUALS_UTILITIES_STARTUP_MANUALS);

        setDynamicSlotValue(function->dynamicSlots, SYM_MANUALS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupManuals"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("UTILITIES")))));
      defineGlobalVariableObject("(DEFGLOBAL *TEXINFO-STYLE-FEATURES* (LIST OF KEYWORD) (LIST) :DOCUMENTATION \"A list of features that can modulate some aspects of\nhow certain objects are described.  Currently understood features:\n:INFIX-PARAMETER-LISTS.\")", &oTEXINFO_STYLE_FEATURESo);
      defineGlobalVariableObject("(DEFGLOBAL *TEXINFO-WORD-DELIMITERS* STRING NULL)", &oTEXINFO_WORD_DELIMITERSo);
      { char* delimiters = strcpy(new (GC) char[strlen("     .:;,!?()[]{}\"")+1], "     .:;,!?()[]{}\"");

        delimiters[0] = ' ';
        delimiters[1] = '\t';
        delimiters[2] = '\n';
        delimiters[3] = '\r';
        delimiters[4] = '\f';
        oTEXINFO_WORD_DELIMITERSo = delimiters;
      }
      defineGlobalVariableObject("(DEFSPECIAL *MANUAL-OUTPUT-LANGUAGE* KEYWORD :TEXINFO)", &oMANUAL_OUTPUT_LANGUAGEo);
      defineGlobalVariableObject("(DEFGLOBAL *DOCUMENTED-OBJECTS-REGISTRY* HASH-TABLE (NEW HASH-TABLE))", &oDOCUMENTED_OBJECTS_REGISTRYo);
      defineGlobalVariableObject("(DEFSPECIAL *MANUAL-OUTPUT-STREAM* OUTPUT-STREAM NULL)", &oMANUAL_OUTPUT_STREAMo);
      defineGlobalVariableObject("(DEFGLOBAL *MANUAL-TEMPLATE-COMMAND-PREFIX* STRING \"#$\")", &oMANUAL_TEMPLATE_COMMAND_PREFIXo);
    }
  }
}

Surrogate* SGT_MANUALS_STELLA_CONS = NULL;

Surrogate* SGT_MANUALS_STELLA_TYPE_SPEC = NULL;

Symbol* SYM_MANUALS_STELLA_VARIABLE_TYPE_SPECIFIER = NULL;

Symbol* SYM_MANUALS_STELLA_DOCUMENTATION = NULL;

Symbol* SYM_MANUALS_STELLA_SLOT_TYPE_SPECIFIER = NULL;

Symbol* SYM_MANUALS_STELLA_aREST = NULL;

Symbol* SYM_MANUALS_STELLA_aBODY = NULL;

Symbol* SYM_MANUALS_STELLA_METHOD_MACROp = NULL;

Symbol* SYM_MANUALS_STELLA_METHOD_COMMANDp = NULL;

Symbol* SYM_MANUALS_STELLA_METHOD_VARIABLE_ARGUMENTSp = NULL;

Symbol* SYM_MANUALS_STELLA_METHOD_BODY_ARGUMENTp = NULL;

Keyword* KWD_MANUALS_INFIX_PARAMETER_LISTS = NULL;

Keyword* KWD_MANUALS_TEXINFO = NULL;

Surrogate* SGT_MANUALS_STELLA_SLOT = NULL;

Surrogate* SGT_MANUALS_STELLA_GLOBAL_VARIABLE = NULL;

Surrogate* SGT_MANUALS_STELLA_MODULE = NULL;

Symbol* SYM_MANUALS_UTILITIES_MANUAL_DESCRIBE_OBJECT = NULL;

Symbol* SYM_MANUALS_UTILITIES_STARTUP_MANUALS = NULL;

Symbol* SYM_MANUALS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella_utilities
